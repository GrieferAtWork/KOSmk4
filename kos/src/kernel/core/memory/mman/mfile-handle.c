/* Copyright (c) 2019-2025 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_HANDLE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <kernel/except.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/iovec.h>
#include <kernel/mman/mfile-misaligned.h>
#include <kernel/mman/mfile-subregion.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/pertask.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <kos/ioctl/file.h>
#include <kos/kernel/handle.h>
#include <kos/kernel/types.h>
#include <kos/types.h>
#include <linux/fs.h>
#include <sys/filio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include <assert.h>
#include <atomic.h>
#include <ctime>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

/* Default ioctl(2) operator for mfile-s. Implements:
 *  - FS_IOC_GETFLAGS, FS_IOC_SETFLAGS
 *  - FS_IOC_GETFSLABEL, FS_IOC_SETFSLABEL
 *  - BLKROSET, BLKROGET, BLKFLSBUF
 *  - BLKSSZGET, BLKBSZGET,
 *  - BLKGETSIZE, BLKGETSIZE64
 *  - FILE_IOC_BLKSHIFT
 *  - FILE_IOC_MSALIGN
 *  - FILE_IOC_SUBREGION
 *  - FILE_IOC_DELREGION
 *  - FILE_IOC_TAILREAD
 *  - FILE_IOC_TRIM
 *  - FILE_IOC_GETFS*
 */
PUBLIC BLOCKING NONNULL((1)) syscall_slong_t KCALL
mfile_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
              NCX UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	/* Generate offset table for attributes referenced by ioctl codes. */
	enum {
		USER_ATTRIB_MINID = MIN_C(_IOC_NR(FILE_IOC_GETFSLINKMAX), _IOC_NR(FILE_IOC_GETFSNAMEMAX),
		                          _IOC_NR(FILE_IOC_GETFSSIZBITS), _IOC_NR(FILE_IOC_GETFSXFERINC),
		                          _IOC_NR(FILE_IOC_GETFSXFERMAX), _IOC_NR(FILE_IOC_GETFSXFERMIN),
		                          _IOC_NR(FILE_IOC_GETFSXFERALN), _IOC_NR(FILE_IOC_GETFSSYMMAX))
	};
	static uint16_t const super_attrib_offsets[] = {
		[(_IOC_NR(FILE_IOC_GETFSLINKMAX) - USER_ATTRIB_MINID)] = offsetof(struct fsuper, fs_feat.sf_link_max),
		[(_IOC_NR(FILE_IOC_GETFSNAMEMAX) - USER_ATTRIB_MINID)] = offsetof(struct fsuper, fs_feat.sf_name_max),
		[(_IOC_NR(FILE_IOC_GETFSSIZBITS) - USER_ATTRIB_MINID)] = offsetof(struct fsuper, fs_feat.sf_filesizebits),
		[(_IOC_NR(FILE_IOC_GETFSXFERINC) - USER_ATTRIB_MINID)] = offsetof(struct fsuper, fs_feat.sf_rec_incr_xfer_size),
		[(_IOC_NR(FILE_IOC_GETFSXFERMAX) - USER_ATTRIB_MINID)] = offsetof(struct fsuper, fs_feat.sf_rec_max_xfer_size),
		[(_IOC_NR(FILE_IOC_GETFSXFERMIN) - USER_ATTRIB_MINID)] = offsetof(struct fsuper, fs_feat.sf_rec_min_xfer_size),
		[(_IOC_NR(FILE_IOC_GETFSXFERALN) - USER_ATTRIB_MINID)] = offsetof(struct fsuper, fs_feat.sf_rec_xfer_align),
		[(_IOC_NR(FILE_IOC_GETFSSYMMAX) - USER_ATTRIB_MINID)]  = offsetof(struct fsuper, fs_feat.sf_symlink_max),
	};

	switch (cmd) {

	case _IO_WITHTYPE(FS_IOC_GETFLAGS, u32):
	case _IO_WITHTYPE(FS_IOC_GETFLAGS, u64): {
		uintptr_t mfile_flags, flags = 0;
		if unlikely(!IO_CANREAD(mode))
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_GETPROPERTY, mode);
		mfile_flags = atomic_read(&self->mf_flags);
		if (mfile_flags & MFILE_F_READONLY)
			flags |= FS_IMMUTABLE_FL;
		if (mfile_flags & MFILE_F_NOATIME)
			flags |= FS_NOATIME_FL;
		arg = validate_writable(arg, _IOC_SIZE(cmd));
		if (_IOC_SIZE(cmd) == sizeof(u32)) {
			UNALIGNED_SET32(arg, (u32)flags);
		} else {
			UNALIGNED_SET64(arg, (u64)flags);
		}
		return 0;
	}	break;

	case _IO_WITHTYPE(FS_IOC_SETFLAGS, u32):
	case _IO_WITHTYPE(FS_IOC_SETFLAGS, u64): {
		uintptr_t mask, flag, inode_flags;
		if unlikely(!IO_CANWRITE(mode))
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_SETPROPERTY, mode);
		arg = (NCX void *)validate_readable(arg, _IOC_SIZE(cmd));
		if (_IOC_SIZE(cmd) == sizeof(u32)) {
			inode_flags = (uintptr_t)UNALIGNED_GET32(arg);
		} else {
			inode_flags = (uintptr_t)UNALIGNED_GET64(arg);
		}
		mask = ~(uintptr_t)(MFILE_F_READONLY | MFILE_FN_ATTRREADONLY | MFILE_F_NOATIME);
		flag = 0;
		if (inode_flags & FS_IMMUTABLE_FL)
			flag |= MFILE_F_READONLY | MFILE_FN_ATTRREADONLY;
		if (inode_flags & FS_NOATIME_FL)
			flag |= MFILE_F_NOATIME;
		/* Other flags are ignored (for now...) */

		/* Set new flags. */
		mfile_chflags(self, mask, flag, /*check_permissions:*/ true);
		return 0;
	}	break;

	case FILE_IOC_BLKSHIFT: {
		NCX struct file_blkshift *info;
		/* Query ioctl for buffer requirements of `O_DIRECT' */
		info = (NCX struct file_blkshift *)validate_writable(arg, sizeof(struct file_blkshift));
		COMPILER_WRITE_BARRIER();
		info->fbs_blck = self->mf_blockshift;
		info->fbs_ioba = self->mf_iobashift;
		return 0;
	}	break;

	case FILE_IOC_MSALIGN: {
		NCX struct file_msalign *info;
		REF struct mfile *ma_wrapper;
		REF struct filehandle *ma_handle;
		struct handle hand;
		pos_t offset;
		info   = (NCX struct file_msalign *)validate_readwrite(arg, sizeof(struct file_msalign));
		offset = (pos_t)info->fmsa_offset;
		COMPILER_READ_BARRIER();

		/* Ensure that the caller has read-access for `self'.
		 * Since the resulting wrapper will be usable for reading, we have to prevent
		 * this ioctl from be  ing (ab-)used to gain  read-access to files that  were
		 * previously opened as write-only. */
		if unlikely(!IO_CANREAD(mode))
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_READ, mode);

		/* Ensure that the file supports "Raw I/O". `mfile_create_misaligned_wrapper()'
		 * will assert the same thing,  but if it detects this  to not be the case,  it
		 * will  cause kernel panic. -- Since we get called from user-space, we need to
		 * throw an exception in this situation. */
		if unlikely(!mfile_hasrawio(self))
			THROW(E_ILLEGAL_OPERATION, E_ILLEGAL_OPERATION_CONTEXT_MSALIGN_NO_RAW_IO);

		/* Create the misalignment wrapper. */
		ma_wrapper = mfile_create_misaligned_wrapper(self, &offset);

		/* Wrap the new mfile in a `struct filehandle'. */
		{
			REF struct path *fh_path;
			REF struct fdirent *fh_dent;
			FINALLY_DECREF_UNLIKELY(ma_wrapper);
			fh_path = (REF struct path *)mfile_utryas(self, HANDLE_TYPE_PATH);
			FINALLY_XDECREF_UNLIKELY(fh_path);
			fh_dent = (REF struct fdirent *)mfile_utryas(self, HANDLE_TYPE_DIRENT);
			FINALLY_XDECREF_UNLIKELY(fh_dent);
			ma_handle = filehandle_new(ma_wrapper, fh_path, fh_dent);
		}
		FINALLY_DECREF_UNLIKELY(ma_handle);

		/* Write-back the adjusted file offset. */
		COMPILER_WRITE_BARRIER();
		info->fmsa_offset = (uint64_t)offset;

		/* Set-up and install the new object as a handle. */
		hand.h_type = HANDLE_TYPE_FILEHANDLE;
		hand.h_data = ma_handle;
		hand.h_mode = IO_RDONLY;
		return handles_install_openfd(hand, &info->fmsa_resfd);
	}	break;

	case FILE_IOC_SUBREGION: {
		NCX struct file_subregion *info;
		REF struct mfile *subregion;
		struct handle hand;
		pos_t minaddr, maxaddr;
		info   = (NCX struct file_subregion *)validate_readwrite(arg, sizeof(struct file_subregion));
		minaddr = (pos_t)info->fsr_minaddr;
		maxaddr = (pos_t)info->fsr_maxaddr;
		COMPILER_READ_BARRIER();

		/* The resulting wrapper can be used for reading and writing, so require both. */
		if unlikely(!IO_CANREADWRITE(mode))
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_MMAP, mode);

		/* Create the misalignment wrapper. */
		subregion = mfile_subregion(self, minaddr, maxaddr);
		FINALLY_DECREF_UNLIKELY(subregion);

		/* Set-up and install the new object as a handle. */
		hand.h_type = HANDLE_TYPE_MFILE;
		hand.h_data = subregion;
		hand.h_mode = IO_RDWR;
		return handles_install_openfd(hand, &info->fsr_resfd);
	}	break;

	case FILE_IOC_DELREGION:
		/* Assert that "self" is a sub-region mfile */
		if (self->mf_ops != &mfile_subregion_ops) {
			THROW(E_ILLEGAL_OPERATION,
			      E_ILLEGAL_OPERATION_CONTEXT_NOT_A_SUBREGION);
		}
		mfile_subregion_delete(self);
		return 0;

	case FILE_IOC_TAILREAD: {
		pos_t offset;
		size_t num_bytes;
		NCX void *buf;
		NCX struct file_tailread *info;
		info = (NCX struct file_tailread *)validate_readwrite(arg, sizeof(struct file_tailread));
		/* Load arguments. */
		buf       = info->ftr_buf;
		num_bytes = info->ftr_siz;
		offset    = (pos_t)info->ftr_pos;
		COMPILER_READ_BARRIER();
		validate_writable(buf, num_bytes);

		/* Check if the file supports tail reading. */
		if (mfile_hasrawio(self) &&
		    (self->mf_ops->mo_stream == NULL ||
		     (self->mf_ops->mo_stream->mso_pread == NULL &&
		      self->mf_ops->mo_stream->mso_preadv == NULL))) {
			/* Reminder: when `offset >= mfile_getsize(self)',  this
			 *           blocks until at least 1 byte could be read. */
			num_bytes = mfile_tailread(self, buf, num_bytes, offset);
		} else {
			/* Fallback: do a normal pread() with non-block. */
			num_bytes = mfile_upread(self, buf, num_bytes, offset,
			                         mode | IO_NONBLOCK);
		}

		/* Write-back the # of read bytes. */
		COMPILER_WRITE_BARRIER();
		info->ftr_siz = num_bytes;
		return 0;
	}	break;

	case FILE_IOC_TRIM: {
		NCX struct file_trim *info;
		uint64_t fpos, size;
		uint32_t mode;
		info = (NCX struct file_trim *)validate_readwrite(arg, sizeof(struct file_trim));
		/* Load arguments. */
		fpos = info->ft_fpos;
		size = info->ft_size;
		mode = info->ft_mode;
		COMPILER_READ_BARRIER();
		if likely(size) {
			pos_t result;
			/* Special handling for the no-op case */
			if unlikely(mode == FILE_TRIM_MODE_NONE) {
				result = 0;
			} else {
				static unsigned int const modes[] = {
					[FILE_TRIM_MODE_UNMAPPED - 1]      = MPART_TRIM_MODE_UNMAPPED,
					[FILE_TRIM_MODE_UNINITIALIZED - 1] = MPART_TRIM_MODE_UNINITIALIZED,
					[FILE_TRIM_MODE_UNCHANGED - 1]     = MPART_TRIM_MODE_UNCHANGED,
					[FILE_TRIM_MODE_SYNC - 1]          = MPART_TRIM_MODE_UNCHANGED | MPART_TRIM_FLAG_SYNC,
					[FILE_TRIM_MODE_ALL - 1]           = MPART_TRIM_MODE_UNCHANGED | MPART_TRIM_FLAG_SYNC | MPART_TRIM_FLAG_SWAP,
					[FILE_TRIM_MODE_FREE - 1]          = MPART_TRIM_MODE_UNCHANGED | MPART_TRIM_FLAG_SYNC | MPART_TRIM_FLAG_FREE,
				};
				pos_t minaddr = (pos_t)fpos;
				pos_t maxaddr;
				--mode;
				if unlikely(mode >= lengthof(modes)) {
					THROW(E_INVALID_ARGUMENT_BAD_VALUE,
					      E_INVALID_ARGUMENT_CONTEXT_FILE_TRIM_MODE,
					      mode + 1);
				}
				mode = modes[mode];
				if (OVERFLOW_UADD(minaddr, size - 1, &maxaddr))
					maxaddr = (pos_t)-1;

				/* Do the trim operation. */
				result = mfile_trimparts(self, minaddr, maxaddr, mode);
			}

			/* Write-back the # of trimmed bytes. */
			COMPILER_WRITE_BARRIER();
			info->ft_size = (uint64_t)result;
		}
		return 0;
	}	break;

		/* All of the following ioctls are used to read attributes from the superblock. */
#ifndef __OPTIMIZE_SIZE__
	case _IO_WITHTYPE(FILE_IOC_GETFSLINKMAX, typeof_field(struct fsuper, fs_feat.sf_link_max)):
	case _IO_WITHTYPE(FILE_IOC_GETFSNAMEMAX, typeof_field(struct fsuper, fs_feat.sf_name_max)):
	case _IO_WITHTYPE(FILE_IOC_GETFSSIZBITS, typeof_field(struct fsuper, fs_feat.sf_filesizebits)):
	case _IO_WITHTYPE(FILE_IOC_GETFSXFERINC, typeof_field(struct fsuper, fs_feat.sf_rec_incr_xfer_size)):
	case _IO_WITHTYPE(FILE_IOC_GETFSXFERMAX, typeof_field(struct fsuper, fs_feat.sf_rec_max_xfer_size)):
	case _IO_WITHTYPE(FILE_IOC_GETFSXFERMIN, typeof_field(struct fsuper, fs_feat.sf_rec_min_xfer_size)):
	case _IO_WITHTYPE(FILE_IOC_GETFSXFERALN, typeof_field(struct fsuper, fs_feat.sf_rec_xfer_align)):
	case _IO_WITHTYPE(FILE_IOC_GETFSSYMMAX,  typeof_field(struct fsuper, fs_feat.sf_symlink_max)): {
		struct fsuper *super;
		if (!mfile_isnode(self))
			break; /* These ioctls are only supported for fnode-based files. */
		super = mfile_asnode(self)->fn_super;
		/* Copy attribute into user-provided buffer. */
		memcpy(validate_writable(arg, _IOC_SIZE(cmd)),
		       (byte_t *)super + super_attrib_offsets[_IOC_NR(cmd) - USER_ATTRIB_MINID],
		       _IOC_SIZE(cmd));
		return 0;
	}	break;
#endif /* !__OPTIMIZE_SIZE__ */

	default:
		break;
	}

	/* Also implement a couple of BLK* ioctl commands
	 * Mainly because on KOS pretty much any file can
	 * be used as a block device (for mounting and so
	 * on...) */
	switch (_IO_WITHSIZE(cmd, 0)) {

	case _IO_WITHSIZE(BLKROSET, 0): { /* aka. `FILE_IOC_SETRO' */
		/* NOTE: Permission checks are done inside of `mfile_chflags()'! */
		uintptr_t newflags = ioctl_intarg_getbool(cmd, arg) ? MFILE_F_READONLY
		                                                    : MFILE_F_NORMAL;
		mfile_chflags(self, ~MFILE_F_READONLY, newflags, /*check_permissions:*/ true);
		return 0;
	}	break;

	case _IO_WITHSIZE(BLKROGET, 0): /* aka. `FILE_IOC_GETRO' */
		return ioctl_intarg_setbool(cmd, arg, self->mf_flags & MFILE_F_READONLY ? 1 : 0);

	case _IO_WITHSIZE(BLKGETSIZE, 0): /* aka. `FILE_IOC_GETSIZE512' */
		return ioctl_intarg_setsize(cmd, arg, (size_t)(mfile_getsize(self) / 512));

	case _IO_WITHSIZE(BLKFLSBUF, 0): /* aka. `FILE_IOC_FLSBUF' */
		/*require(CAP_SYS_ADMIN);*/ /* Linux does this... Why? */
		mfile_udatasync(self);
		/* TODO: `BLKFLSBUF' also acts as a sort of minature system_cc() that will unload
		 *       any  mem-parts associated  with a  non-anonymous file,  so-long as those
		 *       parts aren't being mapped, or otherwise externally referenced.
		 * >> if (part->mp_flags & MPART_F_GLOBAL_REF) CLEAR(MPART_F_GLOBAL_REF);
		 * >> if (!atomic_cmpxch(&part->mp_refcnt, 1, 0)) SET(MPART_F_GLOBAL_REF);
		 * >> else mpart_destory(part);
		 *
		 * Supposedly, this command is meant to be used before `BLKRRPART' in  those
		 * cases where a process may have modified the partition table, possibly  by
		 * means of O_DIRECT, in which case the mpart I/O cache may differ from what
		 * was actually written to disk, even when modified caches were synced.
		 *
		 * Though honestly, on KOS this wouldn't even be necessary since this would not
		 * only require use of O_DIRECT for writing, but even in that case flushing the
		 * cache isn't necessary because `blkdev_repart()' already tries to bypass  the
		 * I/O buffer, meaning that in most cases it wouldn't even make use of possibly
		 * outdated part caches... */
		return 0;

	case _IO_WITHSIZE(BLKSSZGET, 0): /* aka. `_FILE_IOC_BLOCKSIZE' */
		cmd = _IO_WITHSIZE(BLKBSZGET, sizeof(int)); /* Yes: sizeof(int) is correct here! */
		ATTR_FALLTHROUGH
	case _IO_WITHSIZE(BLKBSZGET, 0): /* aka. `FILE_IOC_BLOCKSIZE' */
		return ioctl_intarg_setsize(cmd, arg, mfile_getblocksize(self));

	case _IO_WITHSIZE(BLKGETSIZE64, 0): /* aka. `FILE_IOC_GETSIZE' */
		cmd = _IO_WITHSIZE(BLKGETSIZE64, sizeof(u64)); /* The ioctl code of this one is screwed up... */
		return ioctl_intarg_setu64(cmd, arg, (uint64_t)mfile_getsize(self));

	case _IO_WITHSIZE(FILE_IOC_DELETED, 0):
		return ioctl_intarg_setbool(cmd, arg, (atomic_read(&self->mf_flags) & MFILE_F_DELETED) != 0);

	case _IO_WITHSIZE(FILE_IOC_HASRAWIO, 0):
		return ioctl_intarg_setbool(cmd, arg, mfile_hasrawio(self));

	case _IO_WITHSIZE(FILE_IOC_DCHANGED, 0):
		return ioctl_intarg_setbool(cmd, arg, mfile_haschanged(self));

	case _IO_WITHSIZE(FILE_IOC_CHANGED, 0): {
		uintptr_t flags;
		flags = atomic_read(&self->mf_flags);
		flags &= (MFILE_F_DELETED | MFILE_F_CHANGED | MFILE_F_ATTRCHANGED);
		return ioctl_intarg_setbool(cmd, arg, flags != 0 && !(flags & MFILE_F_DELETED));
	}	break;

	case _IO_WITHSIZE(FILE_IOC_GETFSLINKMAX, 0):
	case _IO_WITHSIZE(FILE_IOC_GETFSNAMEMAX, 0):
	case _IO_WITHSIZE(FILE_IOC_GETFSSIZBITS, 0):
	case _IO_WITHSIZE(FILE_IOC_GETFSXFERINC, 0):
	case _IO_WITHSIZE(FILE_IOC_GETFSXFERMAX, 0):
	case _IO_WITHSIZE(FILE_IOC_GETFSXFERMIN, 0):
	case _IO_WITHSIZE(FILE_IOC_GETFSXFERALN, 0):
	case _IO_WITHSIZE(FILE_IOC_GETFSSYMMAX, 0): {
		struct fsuper *super;
		uint64_t value;
		byte_t *pvalue;
		size_t dsize;
		if (!mfile_isnode(self))
			break; /* These ioctls are only supported for fnode-based files. */
		super = mfile_asnode(self)->fn_super;

		/* Copy attribute into user-provided buffer. */
		pvalue = (byte_t *)super + super_attrib_offsets[_IOC_NR(cmd) - USER_ATTRIB_MINID];
		switch (_IOC_NR(cmd)) {
#define DEFINE_FIELD(ioc, s, m)                              \
		case _IOC_NR(ioc):                                   \
			value = (uint64_t)*(typeof_field(s, m) *)pvalue; \
			dsize = sizeof_field(s, m);                      \
			break
		DEFINE_FIELD(FILE_IOC_GETFSLINKMAX, struct fsuper, fs_feat.sf_link_max);
		DEFINE_FIELD(FILE_IOC_GETFSNAMEMAX, struct fsuper, fs_feat.sf_name_max);
		DEFINE_FIELD(FILE_IOC_GETFSSIZBITS, struct fsuper, fs_feat.sf_filesizebits);
		DEFINE_FIELD(FILE_IOC_GETFSXFERINC, struct fsuper, fs_feat.sf_rec_incr_xfer_size);
		DEFINE_FIELD(FILE_IOC_GETFSXFERMAX, struct fsuper, fs_feat.sf_rec_max_xfer_size);
		DEFINE_FIELD(FILE_IOC_GETFSXFERMIN, struct fsuper, fs_feat.sf_rec_min_xfer_size);
		DEFINE_FIELD(FILE_IOC_GETFSXFERALN, struct fsuper, fs_feat.sf_rec_xfer_align);
		DEFINE_FIELD(FILE_IOC_GETFSSYMMAX, struct fsuper, fs_feat.sf_symlink_max);
#undef DEFINE_FIELD
		default: __builtin_unreachable();
		}
		if (_IOC_SIZE(cmd) == 0)
			cmd = _IO_WITHSIZE(cmd, dsize);
		return ioctl_intarg_setu64(cmd, arg, value);
	}	break;

	case _IO_WITHSIZE(FS_IOC_GETFSLABEL, 0):
		if (mfile_isnode(self)) {
			struct fsuper *super;
			size_t maxlen = _IOC_SIZE(cmd); /* Usually `sizeof(char[FSLABEL_MAX])' */
			(void)maxlen;
			super = mfile_asnode(self)->fn_super;
			if (fsuper_getlabel(super, (NCX char *)validate_writable(arg, maxlen)))
				return 0;
		}
		break;

	case _IO_WITHSIZE(FS_IOC_SETFSLABEL, 0):
		if (mfile_isnode(self)) {
			struct fsuper *super;
			NCX char const *labelname;
			size_t labelsize = _IOC_SIZE(cmd); /* Usually `sizeof(char[FSLABEL_MAX])' */
			super = mfile_asnode(self)->fn_super;
			labelname = (NCX char const *)validate_readable(arg, 1);
			labelsize = strnlen(labelname, labelsize / sizeof(char));
			/* As per the specs, only a SYS_ADMIN can issue this command! */
			require(CAP_SYS_ADMIN);
			if (fsuper_setlabel(super, labelname, labelsize))
				return 0;
		}
		break;

	case _IO_WITHSIZE(FIODTYPE, 0): {
		unsigned int type = 0;
		if (mfile_isblkdev(self))
			type |= D_DISK;
		if (mfile_istty(self))
			type |= D_TTY;
		return ioctl_intarg_setuint(cmd, arg, type);
	}	break;

	default:
		break;
	}

	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
#undef sizeof_field
#undef typeof_field
}



/* Constructs a wrapper object that implements seeking, allowing normal reads/writes to
 * be dispatched via `mfile_upread()' and `mfile_upwrite()' (which uses the `mso_pread'
 * and `mso_pwrite' operators, with `mfile_read()' and `mfile_write()' as fallback, so-
 * long as `MFILE_F_NOUSRIO' isn't set)
 *
 * The operators of the following system calls are forwarded 1-on-1 to `mfile_u*':
 *   - pread(2), preadv(2), pwrite(2), pwritev(2)
 *   - ioctl(2), truncate(2), mmap(2), fallocate(2)
 *   - fsync(2), fdatasync(2), stat(2), poll(2)
 * As stated, `lseek(2)', `read(2)' and `write(2)' are dispatched via pread/pwrite
 *
 * This function is actually used when trying to open a mem-file with neither
 * `mso_read'/`mso_readv', nor `mso_write'/`mso_writev' pre-defined. As such,
 * open(2)-ing a generic mfile object uses `mfile_open()' (see below). */
PUBLIC NONNULL((1, 2)) void KCALL
mfile_v_open(struct mfile *__restrict self,
             /*in|out*/ REF struct handle *__restrict hand,
             struct path *access_path, struct fdirent *access_dent,
             oflag_t UNUSED(oflags))
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct filehandle *fh;
	assert(hand->h_type == HANDLE_TYPE_MFILE);
	assert(hand->h_data == self);

	/* Construct the filehandle wrapper object. */
	fh = filehandle_new(self, access_path, access_dent);

	/* Write-back the file-handle wrapper. */
	hand->h_type = HANDLE_TYPE_FILEHANDLE;
	hand->h_data = fh;   /* Inherit reference */
	decref_nokill(self); /* Old reference from `hand->h_data' */
}


/* Generic open function for arbitrary  mem-file objects. This function  is
 * unconditionally invoked during a call to `open(2)' in order to construct
 * wrapper objects and the like. This function is implemented as:
 *
 * >> struct mfile_stream_ops const *stream = self->mf_ops->mo_stream;
 * >> if (!stream) {
 * >>     mfile_v_open(self, hand, access_path, access_dent, oflags);
 * >> } else if (stream->mso_open) {
 * >>     (*stream->mso_open)(self, hand, access_path, access_dent, oflags);
 * >> } else if (!stream->mso_read && !stream->mso_readv &&
 * >>            !stream->mso_write && !stream->mso_writev) {
 * >>     mfile_v_open(self, hand, access_path, access_dent, oflags);
 * >> } else {
 * >>     // Open mfile itself (iow: `hand->h_data == self')
 * >> } */
PUBLIC BLOCKING NONNULL((1, 2)) void KCALL
mfile_open(struct mfile *__restrict self, struct handle *__restrict hand,
           struct path *access_path, struct fdirent *access_dent,
           oflag_t oflags)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...) {
	struct mfile_stream_ops const *stream = self->mf_ops->mo_stream;
	if (!stream) {
		mfile_v_open(self, hand, access_path, access_dent, oflags);
	} else if (stream->mso_open) {
		(*stream->mso_open)(self, hand, access_path, access_dent, oflags);
	} else if (!stream->mso_read && !stream->mso_readv &&
	           !stream->mso_write && !stream->mso_writev) {
		mfile_v_open(self, hand, access_path, access_dent, oflags);
	} else {
		/* Open mfile itself (iow: `hand->h_data == self') */
	}
}


/* User-visible mem-file access API. (same as the handle access API) */
DEFINE_PUBLIC_ALIAS(mfile_uread, handle_mfile_read);
DEFINE_PUBLIC_ALIAS(mfile_uwrite, handle_mfile_write);
DEFINE_PUBLIC_ALIAS(mfile_upread, handle_mfile_pread);
DEFINE_PUBLIC_ALIAS(mfile_upwrite, handle_mfile_pwrite);
DEFINE_PUBLIC_ALIAS(mfile_ureadv, handle_mfile_readv);
DEFINE_PUBLIC_ALIAS(mfile_uwritev, handle_mfile_writev);
DEFINE_PUBLIC_ALIAS(mfile_upreadv, handle_mfile_preadv);
DEFINE_PUBLIC_ALIAS(mfile_upwritev, handle_mfile_pwritev);
DEFINE_PUBLIC_ALIAS(mfile_useek, handle_mfile_seek);
DEFINE_PUBLIC_ALIAS(mfile_uioctl, handle_mfile_ioctl);
DEFINE_PUBLIC_ALIAS(mfile_utruncate, handle_mfile_truncate);
DEFINE_PUBLIC_ALIAS(mfile_ummap, handle_mfile_mmap);
DEFINE_PUBLIC_ALIAS(mfile_uallocate, handle_mfile_allocate);
DEFINE_PUBLIC_ALIAS(mfile_usync, handle_mfile_sync);
DEFINE_PUBLIC_ALIAS(mfile_udatasync, handle_mfile_datasync);
DEFINE_PUBLIC_ALIAS(mfile_ustat, handle_mfile_stat);
DEFINE_PUBLIC_ALIAS(mfile_upollconnect, handle_mfile_pollconnect);
DEFINE_PUBLIC_ALIAS(mfile_upolltest, handle_mfile_polltest);
DEFINE_PUBLIC_ALIAS(mfile_utryas, handle_mfile_tryas);
DEFINE_PUBLIC_ALIAS(mfile_uprintlink, handle_mfile_printlink);


/* MFILE HANDLE OPERATIONS */
DEFINE_HANDLE_REFCNT_FUNCTIONS(mfile, struct mfile);

/************************************************************************/
/* Handle-specific operator wrappers for `struct mfile'                 */
/************************************************************************/

INTERN BLOCKING WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_read(struct mfile *__restrict self,
                  NCX void *dst,
                  size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if likely(stream->mso_read)
			return (*stream->mso_read)(self, dst, num_bytes, mode);
		if likely(stream->mso_readv) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, dst, num_bytes);
			return (*stream->mso_readv)(self, &iov, num_bytes, mode);
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_READ);
}

INTERN BLOCKING WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_write(struct mfile *__restrict self,
                   NCX void const *src,
                   size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if likely(stream->mso_write)
			return (*stream->mso_write)(self, src, num_bytes, mode);
		if likely(stream->mso_writev) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, src, num_bytes);
			return (*stream->mso_writev)(self, &iov, num_bytes, mode);
		}
	}
	if likely((mode & IO_APPEND) && !(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_tailwrite(self, src, num_bytes);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

PUBLIC WUNUSED NONNULL((1)) size_t KCALL
mfile_utailwrite(struct mfile *__restrict self,
                 NCX void const *src,
                 size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if likely(stream->mso_write)
			return (*stream->mso_write)(self, src, num_bytes, mode | IO_APPEND);
		if likely(stream->mso_writev) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, src, num_bytes);
			return (*stream->mso_writev)(self, &iov, num_bytes, mode | IO_APPEND);
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_tailwrite(self, src, num_bytes);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

/* Check if a bad-usage O_DIRECT exception should get handled */
PRIVATE WUNUSED bool
NOTHROW(FCALL shoud_handle_direct_io_bad_usage)(iomode_t mode) {
	syscall_ulong_t context;

	/* Only handle bad-usage O_DIRECT when direct I/O is optional */
	if (!(mode & IO_OPTDIRECT))
		return false;

	/* Check that the current exception indicates bad API usage for direct-I/O */
	if (!was_thrown(E_INVALID_ARGUMENT_BAD_ALIGNMENT))
		return false;
	context = PERTASK_GET(this_exception_args.e_invalid_argument.ia_context);
	if (context == E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BADPOS ||
	    context == E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BADSIZ ||
	    context == E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BADBUF)
		return true;
	return false;
}

INTERN BLOCKING WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_pread(struct mfile *__restrict self,
                   NCX void *dst, size_t num_bytes,
                   pos_t addr, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL) {
		if (stream->mso_pread)
			return (*stream->mso_pread)(self, dst, num_bytes, addr, mode);
		if (stream->mso_preadv) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, dst, num_bytes);
			return (*stream->mso_preadv)(self, &iov, num_bytes, addr, mode);
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO)) {
		if unlikely(mode & IO_DIRECT) {
			TRY {
				return mfile_direct_read(self, dst, num_bytes, addr);
			} EXCEPT {
				if (!shoud_handle_direct_io_bad_usage(mode))
					RETHROW();
				/* Fallthru to doing normal (non-direct) file I/O */
			}
		}
		return mfile_read(self, dst, num_bytes, addr);
	}
	if (stream != NULL && addr == 0) {
		if (stream->mso_read)
			return (*stream->mso_read)(self, dst, num_bytes, mode);
		if (stream->mso_readv) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, dst, num_bytes);
			return (*stream->mso_readv)(self, &iov, num_bytes, mode);
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PREAD);
}

INTERN BLOCKING WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_pwrite(struct mfile *__restrict self,
                    NCX void const *src, size_t num_bytes,
                    pos_t addr, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL) {
		if (stream->mso_pwrite)
			return (*stream->mso_pwrite)(self, src, num_bytes, addr, mode);
		if (stream->mso_pwritev) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, src, num_bytes);
			return (*stream->mso_pwritev)(self, &iov, num_bytes, addr, mode);
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO)) {
		if unlikely(mode & IO_DIRECT) {
			TRY {
				return mfile_direct_write(self, src, num_bytes, addr);
			} EXCEPT {
				if (!shoud_handle_direct_io_bad_usage(mode))
					RETHROW();
				/* Fallthru to doing normal (non-direct) file I/O */
			}
		}
		return mfile_write(self, src, num_bytes, addr);
	}
	if (stream != NULL && addr == 0) {
		if (stream->mso_write)
			return (*stream->mso_write)(self, src, num_bytes, mode);
		if (stream->mso_writev) {
			struct iov_buffer iov;
			iov_buffer_initone(&iov, src, num_bytes);
			return (*stream->mso_writev)(self, &iov, num_bytes, mode);
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PWRITE);
}

INTERN BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_readv(struct mfile *__restrict self,
                   struct iov_buffer *__restrict dst,
                   size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if (stream->mso_readv)
			return (*stream->mso_readv)(self, dst, num_bytes, mode);
		if (stream->mso_read) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, dst) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_read)(self, ent.ive_base,
					                           ent.ive_size, mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_read;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_read:
			return result;
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_READ);
}

INTERN BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_writev(struct mfile *__restrict self,
                    struct iov_buffer *__restrict src,
                    size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if (stream->mso_writev)
			return (*stream->mso_writev)(self, src, num_bytes, mode);
		if (stream->mso_write) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, src) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_write)(self, ent.ive_base,
					                            ent.ive_size, mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_write;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_write:
			return result;
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO) && (mode & IO_APPEND))
		return mfile_tailwritev(self, src, 0, num_bytes);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

PUBLIC WUNUSED NONNULL((1, 2)) size_t KCALL
mfile_utailwritev(struct mfile *__restrict self,
                  struct iov_buffer *__restrict src,
                  size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL) {
		if (stream->mso_writev)
			return (*stream->mso_writev)(self, src, num_bytes, mode | IO_APPEND);
		if (stream->mso_write) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, src) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_write)(self, ent.ive_base,
					                            ent.ive_size,
					                            mode | IO_APPEND);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_write;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_write:
			return result;
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO))
		return mfile_tailwritev(self, src, 0, num_bytes);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

INTERN BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_preadv(struct mfile *__restrict self,
                    struct iov_buffer *__restrict dst,
                    size_t num_bytes, pos_t addr, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL) {
		if (stream->mso_preadv)
			return (*stream->mso_preadv)(self, dst, num_bytes, addr, mode);
		if (stream->mso_pread) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, dst) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_pread)(self, ent.ive_base,
					                            ent.ive_size, addr,
					                            mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_pread;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				addr += part;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_pread:
			return result;
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO)) {
		if unlikely(mode & IO_DIRECT) {
			TRY {
				return mfile_direct_readv(self, dst, 0, num_bytes, addr);
			} EXCEPT {
				if (!shoud_handle_direct_io_bad_usage(mode))
					RETHROW();
				/* Fallthru to doing normal (non-direct) file I/O */
			}
		}
		return mfile_readv(self, dst, 0, num_bytes, addr);
	}
	if (stream != NULL && addr == 0) {
		if (stream->mso_readv)
			return (*stream->mso_readv)(self, dst, num_bytes, mode);
		if (stream->mso_read) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, dst) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_read)(self, ent.ive_base,
					                           ent.ive_size, mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_read;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_read:
			return result;
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PREAD);
}

INTERN BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_pwritev(struct mfile *__restrict self,
                     struct iov_buffer *__restrict src,
                     size_t num_bytes, pos_t addr, iomode_t mode)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL) {
		if (stream->mso_pwritev)
			return (*stream->mso_pwritev)(self, src, num_bytes, addr, mode);
		if (stream->mso_pwrite) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, src) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_pwrite)(self, ent.ive_base,
					                             ent.ive_size, addr,
					                             mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_pwrite;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				addr += part;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_pwrite:
			return result;
		}
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO)) {
		if unlikely(mode & IO_DIRECT) {
			TRY {
				return mfile_direct_writev(self, src, 0, num_bytes, addr);
			} EXCEPT {
				if (!shoud_handle_direct_io_bad_usage(mode))
					RETHROW();
				/* Fallthru to doing normal (non-direct) file I/O */
			}
		}
		return mfile_writev(self, src, 0, num_bytes, addr);
	}
	if (stream != NULL && addr == 0) {
		if (stream->mso_writev)
			return (*stream->mso_writev)(self, src, num_bytes, mode);
		if (stream->mso_write) {
			size_t result = 0;
			struct iov_entry ent;
			IOV_BUFFER_FOREACH(ent, src) {
				size_t part;
				if (!ent.ive_size)
					continue;
				TRY {
					part = (*stream->mso_write)(self, ent.ive_base,
					                            ent.ive_size, mode);
				} EXCEPT {
					if ((was_thrown(E_INTERRUPT_USER_RPC) ||
					     was_thrown(E_WOULDBLOCK)) &&
					    result != 0)
						goto done_write;
					RETHROW();
				}
				result += part;
				if (part < ent.ive_size)
					break;
				/* Don't block for the remainder */
				mode |= IO_NONBLOCK | IO_NODATAZERO;
			}
done_write:
			return result;
		}
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PWRITE);
}

INTERN BLOCKING NONNULL((1)) pos_t KCALL
handle_mfile_seek(struct mfile *__restrict self,
                  off_t offset, unsigned int whence)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if likely(stream != NULL && stream->mso_seek)
		return (*stream->mso_seek)(self, offset, whence);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_SEEK);
}

INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
handle_mfile_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                   NCX UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	BLOCKING NONNULL_T((1)) syscall_slong_t
	(KCALL *mso_ioctl)(struct mfile *__restrict self, ioctl_t cmd,
	                   NCX UNCHECKED void *arg, iomode_t mode);
	struct mfile_stream_ops const *stream;
	mso_ioctl = &mfile_v_ioctl;
	stream    = self->mf_ops->mo_stream;
	if (stream != NULL && stream->mso_ioctl)
		mso_ioctl = stream->mso_ioctl;
	return (*mso_ioctl)(self, cmd, arg, mode);
}

INTERN BLOCKING NONNULL((1)) void KCALL
handle_mfile_truncate(struct mfile *__restrict self,
                      pos_t new_size)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL && stream->mso_truncate) {
		(*stream->mso_truncate)(self, new_size);
		return;
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO)) {
		mfile_truncate(self, new_size);
		return;
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_TRUNC);
}

INTERN BLOCKING NONNULL((1, 2)) void KCALL
handle_mfile_mmap(struct mfile *__restrict self,
                  struct handle_mmap_info *__restrict info)
		THROWS(...) {
	struct mfile_stream_ops const *stream;

	/* Special case for device files (which have fixed filesystem names) */
	if (mfile_isdevice(self)) {
		if (!info->hmi_fsname) {
			struct device *dev = mfile_asdevice(self);
			devfs_byname_read();
			if (dev->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED)
				info->hmi_fsname = incref(&dev->dv_dirent->dd_dirent);
			devfs_byname_endread();
		}
		if (!info->hmi_fspath)
			info->hmi_fspath = vfs_mount_location(THIS_VFS, &devfs.fs_root);
	}

	/* Invoke the optional streams override operator. */
	stream = self->mf_ops->mo_stream;
	if (stream != NULL && stream->mso_mmap) {
		(*stream->mso_mmap)(self, info);
		return;
	}

	/* Fallback: any mfile can be mmap'd (because that's what they're there for)
	 *           However, the `MFILE_F_NOUSRMMAP' flag can be used to deny user-
	 *           space the right to do that. */
	if likely(!(self->mf_flags & MFILE_F_NOUSRMMAP)) {
		info->hmi_file = incref(self);
		return;
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_MMAP);
}

INTERN BLOCKING NONNULL((1)) pos_t KCALL
handle_mfile_allocate(struct mfile *__restrict self,
                      fallocate_mode_t mode,
                      pos_t start, pos_t length)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream != NULL && stream->mso_allocate) {
		return (*stream->mso_allocate)(self, mode, start, length);
	}
	if likely(!(self->mf_flags & MFILE_F_NOUSRIO)) {
		/* TODO: mfile_allocate()   (pre-load parts of the file into memory) */
		return 0;
	}
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_ALLOCATE);
}

PRIVATE NONNULL((1)) void KCALL
mfile_sync_generic(struct mfile *__restrict self)
		THROWS(...) {
	struct mfile_stream_ops const *stream_ops;
	mfile_sync(self);
	stream_ops = self->mf_ops->mo_stream;
	if (stream_ops != NULL && stream_ops->mso_sync != NULL)
		(*stream_ops->mso_sync)(self);
}

INTERN BLOCKING NONNULL((1)) void KCALL
handle_mfile_sync(struct mfile *__restrict self)
		THROWS(...) {
	if (mfile_isnode(self)) {
		struct fnode *node;
		node = mfile_asnode(self);
		fnode_syncdata(node);
		fnode_syncattr(node);
	} else {
		mfile_sync_generic(self);
	}
}

INTERN BLOCKING NONNULL((1)) void KCALL
handle_mfile_datasync(struct mfile *__restrict self)
		THROWS(...) {
	if (mfile_isnode(self)) {
		struct fnode *node;
		node = mfile_asnode(self);
		fnode_syncdata(node);
	} else {
		mfile_sync_generic(self);
	}
}

INTERN BLOCKING NONNULL((1)) void KCALL
handle_mfile_stat(struct mfile *__restrict self,
                  NCX struct stat *result)
		THROWS(...) {
	dev_t st_dev;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	pos_t st_size;
	blksize_t st_blksize;
	struct timespec st_atim;
	struct timespec st_mtim;
	struct timespec st_ctim;
	struct timespec st_btim;

	mfile_tslock_acquire(self);
	st_size = mfile_getsize(self);
	if (mfile_isanon(self))
		st_size = 0;
	st_blksize = (blksize_t)self->mf_part_amask + 1;

	memcpy(&st_atim, &self->mf_atime, sizeof(struct timespec));
	memcpy(&st_mtim, &self->mf_mtime, sizeof(struct timespec));
	memcpy(&st_ctim, &self->mf_ctime, sizeof(struct timespec));
	memcpy(&st_btim, &self->mf_btime, sizeof(struct timespec));

	st_dev = st_rdev = 0;
	if (mfile_isnode(self)) {
		struct fnode *me  = mfile_asnode(self);
		struct mfile *dev = me->fn_super->fs_dev;
		/* Fill in extended file-node information */
		if (dev && mfile_isdevnode(dev))
			st_dev = mfile_asdevnode(dev)->dn_devno;
		st_ino   = me->fn_ino;
		st_mode  = me->fn_mode;
		st_nlink = me->fn_nlink;
		st_uid   = me->fn_uid;
		st_gid   = me->fn_gid;
		if (fnode_isdevnode(me))
			st_rdev = fnode_asdevnode(me)->dn_devno;
	} else {
		st_ino   = 0;
		st_mode  = 0777 | S_IFBLK;
		st_nlink = 1;
		st_uid   = 0;
		st_gid   = 0;
	}
	mfile_tslock_release(self);

	/* If defined, invoke the get-file-node-owner override operator. */
	if (mfile_isnode(self)) {
		struct fnode *me = mfile_asnode(self);
		struct fnode_perm_ops const *perm_ops;
		perm_ops = fnode_getops(me)->no_perm;
		if (perm_ops && perm_ops->npo_getown)
			(*perm_ops->npo_getown)(me, &st_uid, &st_gid);
	}

	/* Check if the file has been deleted. If it has, timestamps are invalid. */
	if (atomic_read(&self->mf_flags) & MFILE_F_DELETED) {
		bzero(&st_atim, sizeof(struct timespec));
		bzero(&st_mtim, sizeof(struct timespec));
		bzero(&st_ctim, sizeof(struct timespec));
		bzero(&st_btim, sizeof(struct timespec));
	}

	/* Fill in generic default information */
	result->st_dev       = (typeof(result->st_dev))st_dev;
	result->st_ino       = (typeof(result->st_ino))st_ino;
	result->st_mode      = (typeof(result->st_mode))st_mode;
	result->st_nlink     = (typeof(result->st_nlink))st_nlink;
	result->st_uid       = (typeof(result->st_uid))st_uid;
	result->st_gid       = (typeof(result->st_gid))st_gid;
	result->st_rdev      = (typeof(result->st_rdev))st_rdev;
	result->st_size      = (typeof(result->st_size))st_size;
	result->st_blksize   = (typeof(result->st_blksize))st_blksize;
	result->st_blocks    = (typeof(result->st_blocks))CEILDIV(st_size, st_blksize);
	result->st_atime     = st_atim.tv_sec;
	result->st_atimensec = st_atim.tv_nsec;
	result->st_mtime     = st_mtim.tv_sec;
	result->st_mtimensec = st_mtim.tv_nsec;
	result->st_ctime     = st_ctim.tv_sec;
	result->st_ctimensec = st_ctim.tv_nsec;
	result->st_btime     = st_btim.tv_sec;
	result->st_btimensec = st_btim.tv_nsec;

	/* If defined, invoke a stat information override callback. */
	{
		struct mfile_stream_ops const *stream;
		stream = self->mf_ops->mo_stream;
		if (stream && stream->mso_stat)
			(*stream->mso_stat)(self, result);
	}
}

INTERN BLOCKING NONNULL((1)) void KCALL
handle_mfile_pollconnect(struct mfile *__restrict self,
                         poll_mode_t what)
		THROWS(...) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream && stream->mso_pollconnect)
		(*stream->mso_pollconnect)(self, what);
}

INTERN BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_mfile_polltest(struct mfile *__restrict self,
                      poll_mode_t what)
		THROWS(...) {
	poll_mode_t result;
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream && stream->mso_polltest) {
		result = (*stream->mso_polltest)(self, what);
	} else {
		result = what & (POLLINMASK | POLLOUTMASK);
		if (self->mf_flags & MFILE_F_NOUSRIO) {
			result = 0;
			if (stream) {
				if (stream->mso_read || stream->mso_readv)
					result |= what & POLLINMASK;
				if (stream->mso_write || stream->mso_writev)
					result |= what & POLLOUTMASK;
			}
		}
	}
	return result;
}

INTERN BLOCKING NONNULL((1)) REF void *KCALL
handle_mfile_tryas(struct mfile *__restrict self,
                   uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	struct mfile_stream_ops const *stream;
	assert(wanted_type != HANDLE_TYPE_MFILE);
	stream = self->mf_ops->mo_stream;
	if (stream && stream->mso_tryas)
		return (*stream->mso_tryas)(self, wanted_type);
	return NULL;
}

INTERN BLOCKING NONNULL((1, 2)) ssize_t KCALL
handle_mfile_printlink(struct mfile *__restrict self,
                       pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK) {
	struct mfile_stream_ops const *stream;
	stream = self->mf_ops->mo_stream;
	if (stream && stream->mso_printlink)
		return (*stream->mso_printlink)(self, printer, arg);

	/* Special handling for known special node types. */
	if (mfile_isnode(self)) {
		struct fnode *node = mfile_asnode(self);

		/* Devfs device files. */
		if (fnode_isdevice(node)) {
			REF struct devdirent *devname;
			REF struct path *devpath;
			struct device *dev = fnode_asdevice(node);
			device_getname_lock_acquire(dev);
			devname = incref(dev->dv_dirent);
			device_getname_lock_release(dev);
			FINALLY_DECREF_UNLIKELY(devname);
			devpath = vfs_mount_location(THIS_VFS, &devfs.fs_root);
			if (devpath) {
				REF struct path *root;
				FINALLY_DECREF_UNLIKELY(devpath);
				root = fs_getroot(THIS_FS);
				FINALLY_DECREF_UNLIKELY(root);
				return path_printent(devpath, devname->dd_dirent.fd_name,
				                     devname->dd_dirent.fd_namelen, printer, arg,
				                     AT_PATHPRINT_INCTRAIL, root);
			}
			return format_printf(printer, arg, "devfs:/%$s",
			                     (size_t)devname->dd_dirent.fd_namelen,
			                     devname->dd_dirent.fd_name);
		}
	}
	return format_printf(printer, arg,
	                     "anon_inode:[mfile:%" PRIuPTR "]",
	                     skew_kernel_pointer(self));
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_HANDLE_C */
