/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEV_BLOCK_HANDLE_C
#define GUARD_KERNEL_SRC_DEV_BLOCK_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <fs/node.h>
#include <kernel/aio.h>
#include <kernel/compat.h>
#include <kernel/handle.h>
#include <kernel/user.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/except-inval.h>
#include <kos/hop.h>
#include <kos/io.h>
#include <sys/mount.h>
#include <sys/stat.h>

#include <string.h>

DECL_BEGIN


DEFINE_HANDLE_REFCNT_FUNCTIONS(blockdevice,struct basic_block_device)


INTERN size_t
(KCALL handle_blockdevice_pread)(struct basic_block_device *__restrict self,
                                 USER CHECKED void *dst, size_t num_bytes,
                                 pos_t addr, iomode_t mode) {
	block_device_read(self,
	                  dst,
	                  num_bytes,
	                  addr);
	return num_bytes;
}
INTERN size_t
(KCALL handle_blockdevice_pwrite)(struct basic_block_device *__restrict self,
                                  USER CHECKED void const *src, size_t num_bytes,
                                  pos_t addr, iomode_t mode) {
	block_device_write(self,
	                   src,
	                   num_bytes,
	                   addr);
	return num_bytes;
}

INTERN size_t
(KCALL handle_blockdevice_preadv)(struct basic_block_device *__restrict self,
                                  struct aio_buffer *__restrict dst, size_t num_bytes,
                                  pos_t addr, iomode_t mode) {
	block_device_readv(self,
	                   dst,
	                   num_bytes,
	                   addr);
	return num_bytes;
}
INTERN size_t
(KCALL handle_blockdevice_pwritev)(struct basic_block_device *__restrict self,
                                   struct aio_buffer *__restrict src, size_t num_bytes,
                                   pos_t addr, iomode_t mode) {
	block_device_writev(self,
	                    src,
	                    num_bytes,
	                    addr);
	return num_bytes;
}


INTERN size_t
(KCALL handle_blockdevice_apread)(struct basic_block_device *__restrict self,
                                  USER CHECKED void *dst, size_t num_bytes,
                                  pos_t addr, iomode_t mode,
                                  struct aio_multihandle *__restrict aio) {
	block_device_aread(self,
	                   dst,
	                   num_bytes,
	                   addr,
	                   aio_multihandle_allochandle(aio));
	return num_bytes;
}
INTERN size_t
(KCALL handle_blockdevice_apwrite)(struct basic_block_device *__restrict self,
                                   USER CHECKED void const *src, size_t num_bytes,
                                   pos_t addr, iomode_t mode,
                                   struct aio_multihandle *__restrict aio) {
	block_device_awrite(self,
	                    src,
	                    num_bytes,
	                    addr,
	                    aio_multihandle_allochandle(aio));
	return num_bytes;
}

INTERN size_t
(KCALL handle_blockdevice_apreadv)(struct basic_block_device *__restrict self,
                                   struct aio_buffer *__restrict dst, size_t num_bytes,
                                   pos_t addr, iomode_t mode,
                                   struct aio_multihandle *__restrict aio) {
	block_device_areadv(self,
	                    dst,
	                    num_bytes,
	                    addr,
	                    aio_multihandle_allochandle(aio));
	return num_bytes;
}
INTERN size_t
(KCALL handle_blockdevice_apwritev)(struct basic_block_device *__restrict self,
                                    struct aio_buffer *__restrict src, size_t num_bytes,
                                    pos_t addr, iomode_t mode,
                                    struct aio_multihandle *__restrict aio) {
	block_device_awritev(self,
	                     src,
	                     num_bytes,
	                     addr,
	                     aio_multihandle_allochandle(aio));
	return num_bytes;
}


LOCAL size_t KCALL
block_device_get_readahead(struct basic_block_device *__restrict self) {
	return self->bd_sector_size;
}

LOCAL void KCALL
block_device_set_readahead(struct basic_block_device *__restrict self, size_t value) {
	/* KOS doesn't implement read-ahead on the block-device layer.
	 * Instead, read-ahead (if at all) is only done on a per-file
	 * basis, where we cache them in vm_datapart objects. */
	(void)self;
	(void)value;
}

LOCAL size_t KCALL
block_device_get_fsreadahead(struct basic_block_device *__restrict self) {
	return block_device_get_readahead(self);
}

LOCAL void KCALL
block_device_set_fsreadahead(struct basic_block_device *__restrict self, size_t value) {
	block_device_set_readahead(self, value);
}

LOCAL u16 KCALL
block_device_get_max_sectors_per_request(struct basic_block_device *__restrict self) {
	(void)self;
	/* XXX: Implement me? */
	return (u16)-1;
}

LOCAL void KCALL
block_device_set_max_sectors_per_request(struct basic_block_device *__restrict self, u16 value) {
	(void)self;
	(void)value;
	/* XXX: Implement me? */
}

LOCAL size_t KCALL
block_device_get_sector_size(struct basic_block_device *__restrict self) {
	return self->bd_sector_size;
}

LOCAL void KCALL
block_device_set_sector_size(struct basic_block_device *__restrict self, size_t value) {
	/* XXX: Throw some kind of error when `value != self->bd_sector_size' */
}


INTERN syscall_slong_t KCALL
handle_blockdevice_ioctl(struct basic_block_device *__restrict self,
                         syscall_ulong_t command, USER UNCHECKED void *arg,
                         iomode_t mode) {
	switch (command) {

	case BLKROSET:
	case _IOW(_IOC_TYPE(BLKROSET), _IOC_NR(BLKROSET), int): {
		int value;
		validate_readable(arg, sizeof(value));
		value = *(int *)arg;
		if (value)
			ATOMIC_FETCHOR(self->bd_flags, BLOCK_DEVICE_FLAG_READONLY);
	}	break;

	case BLKROGET:
	case _IOR(_IOC_TYPE(BLKROGET), _IOC_NR(BLKROGET), int): {
		int value;
		validate_writable(arg, sizeof(value));
		value       = ATOMIC_READ(self->bd_flags) & BLOCK_DEVICE_FLAG_READONLY ? 1 : 0;
		*(int *)arg = value;
	}	break;

	case BLKRRPART:
		if (block_device_ispartition(self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_BLOCKDEVICE,
			      0,
			      HANDLE_TYPEKIND_BLOCKDEVICE_DRIVEROOT,
			      0);
		block_device_delparts((struct block_device *)self);
		block_device_autopart(self);
		break;

	case BLKGETSIZE:
#ifdef __ARCH_HAVE_COMPAT
		if (syscall_iscompat())
			goto do_BLKGETSIZE_compat;
		ATTR_FALLTHROUGH
#endif /* __ARCH_HAVE_COMPAT */
	case _IOR(_IOC_TYPE(BLKGETSIZE), _IOC_NR(BLKGETSIZE), uintptr_t):
		validate_writable(arg, sizeof(uintptr_t));
		COMPILER_WRITE_BARRIER();
		*(uintptr_t *)arg = (uintptr_t)(self->bd_total_bytes / 512);
		COMPILER_WRITE_BARRIER();
		break;

#ifdef __ARCH_HAVE_COMPAT
	case _IOR(_IOC_TYPE(BLKGETSIZE), _IOC_NR(BLKGETSIZE), __ARCH_COMPAT_ULONGPTR_TYPE):
do_BLKGETSIZE_compat:
		validate_writable(arg, sizeof(__ARCH_COMPAT_ULONGPTR_TYPE));
		COMPILER_WRITE_BARRIER();
		*(__ARCH_COMPAT_ULONGPTR_TYPE *)arg = (__ARCH_COMPAT_ULONGPTR_TYPE)(self->bd_total_bytes / 512);
		COMPILER_WRITE_BARRIER();
		break;
#endif /* __ARCH_HAVE_COMPAT */


	case BLKFLSBUF:
		block_device_sync(self);
		break;

	case BLKRASET:
#ifdef __ARCH_HAVE_COMPAT
		if (syscall_iscompat())
			goto do_BLKRASET_compat;
		ATTR_FALLTHROUGH
#endif /* __ARCH_HAVE_COMPAT */
	case _IOW(_IOC_TYPE(BLKRASET), _IOC_NR(BLKRASET), uintptr_t):
		validate_readable(arg, sizeof(uintptr_t));
		block_device_set_readahead(self, (size_t)*(uintptr_t *)arg);
		break;
#ifdef __ARCH_HAVE_COMPAT
	case _IOW(_IOC_TYPE(BLKRASET), _IOC_NR(BLKRASET), __ARCH_COMPAT_ULONGPTR_TYPE):
do_BLKRASET_compat:
		validate_readable(arg, sizeof(__ARCH_COMPAT_ULONGPTR_TYPE));
		block_device_set_readahead(self, (size_t)*(__ARCH_COMPAT_ULONGPTR_TYPE *)arg);
		break;
#endif /* __ARCH_HAVE_COMPAT */

	case BLKRAGET:
#ifdef __ARCH_HAVE_COMPAT
		if (syscall_iscompat())
			goto do_BLKRAGET_compat;
		ATTR_FALLTHROUGH
#endif /* __ARCH_HAVE_COMPAT */
	case _IOR(_IOC_TYPE(BLKRAGET), _IOC_NR(BLKRAGET), uintptr_t):
		validate_writable(arg, sizeof(uintptr_t));
		*(uintptr_t *)arg = (uintptr_t)block_device_get_readahead(self);
		break;
#ifdef __ARCH_HAVE_COMPAT
	case _IOR(_IOC_TYPE(BLKRAGET), _IOC_NR(BLKRAGET), __ARCH_COMPAT_ULONGPTR_TYPE):
do_BLKRAGET_compat:
		validate_writable(arg, sizeof(__ARCH_COMPAT_ULONGPTR_TYPE));
		*(__ARCH_COMPAT_ULONGPTR_TYPE *)arg = (__ARCH_COMPAT_ULONGPTR_TYPE)block_device_get_readahead(self);
		break;
#endif /* __ARCH_HAVE_COMPAT */

	case BLKFRASET:
#ifdef __ARCH_HAVE_COMPAT
		if (syscall_iscompat())
			goto do_BLKRASET_compat;
		ATTR_FALLTHROUGH
#endif /* __ARCH_HAVE_COMPAT */
	case _IOW(_IOC_TYPE(BLKFRASET), _IOC_NR(BLKFRASET), uintptr_t):
		validate_readable(arg, sizeof(uintptr_t));
		block_device_set_fsreadahead(self, (size_t)*(uintptr_t *)arg);
		break;
#ifdef __ARCH_HAVE_COMPAT
	case _IOW(_IOC_TYPE(BLKFRASET), _IOC_NR(BLKFRASET), __ARCH_COMPAT_ULONGPTR_TYPE):
do_BLKRASET_compat:
		validate_readable(arg, sizeof(__ARCH_COMPAT_ULONGPTR_TYPE));
		block_device_set_fsreadahead(self, (size_t)*(__ARCH_COMPAT_ULONGPTR_TYPE *)arg);
		break;
#endif /* __ARCH_HAVE_COMPAT */


	case BLKFRAGET:
#ifdef __ARCH_HAVE_COMPAT
		if (syscall_iscompat())
			goto do_BLKRAGET_compat;
		ATTR_FALLTHROUGH
#endif /* __ARCH_HAVE_COMPAT */
	case _IOR(_IOC_TYPE(BLKFRAGET), _IOC_NR(BLKFRAGET), uintptr_t):
		validate_writable(arg, sizeof(uintptr_t));
		*(uintptr_t *)arg = (uintptr_t)block_device_get_fsreadahead(self);
		break;
#ifdef __ARCH_HAVE_COMPAT
	case _IOR(_IOC_TYPE(BLKFRAGET), _IOC_NR(BLKFRAGET), __ARCH_COMPAT_ULONGPTR_TYPE):
do_BLKRAGET_compat:
		validate_writable(arg, sizeof(__ARCH_COMPAT_ULONGPTR_TYPE));
		*(__ARCH_COMPAT_ULONGPTR_TYPE *)arg = (__ARCH_COMPAT_ULONGPTR_TYPE)block_device_get_fsreadahead(self);
		break;
#endif /* __ARCH_HAVE_COMPAT */

	case BLKSECTSET:
	case _IOW(_IOC_TYPE(BLKSECTSET), _IOC_NR(BLKSECTSET), u16):
		validate_readable(arg, sizeof(u16));
		block_device_set_max_sectors_per_request(self, *(u16 *)arg);
		break;

	case BLKSECTGET:
	case _IOR(_IOC_TYPE(BLKSECTGET), _IOC_NR(BLKSECTGET), u16):
		validate_readable(arg, sizeof(u16));
		*(u16 *)arg = block_device_get_max_sectors_per_request(self);
		break;

	case BLKSSZGET:
	case _IOR(_IOC_TYPE(BLKSSZGET), _IOC_NR(BLKSSZGET), unsigned int):
#if __SIZEOF_SIZE_T__ != __SIZEOF_INT__
		validate_writable(arg, sizeof(unsigned int));
		*(unsigned int *)arg = (unsigned int)block_device_get_sector_size(self);
		break;
#else /* __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */
		/* fallthru... */
#endif /* __SIZEOF_SIZE_T__ == __SIZEOF_INT__ */
	case BLKBSZGET:
		validate_writable(arg, sizeof(size_t));
		*(size_t *)arg = block_device_get_sector_size(self);
		break;
#ifdef __ARCH_HAVE_COMPAT
	case _IOR(_IOC_TYPE(BLKBSZGET), _IOC_NR(BLKBSZGET), __ARCH_COMPAT_SIZE_TYPE):
		validate_writable(arg, sizeof(__ARCH_COMPAT_SIZE_TYPE));
		*(__ARCH_COMPAT_SIZE_TYPE *)arg = (__ARCH_COMPAT_SIZE_TYPE)block_device_get_sector_size(self);
		break;
#endif /* __ARCH_HAVE_COMPAT */

	case BLKBSZSET:
		validate_readable(arg, sizeof(size_t));
		block_device_set_sector_size(self, *(size_t *)arg);
		break;
#ifdef __ARCH_HAVE_COMPAT
	case _IOW(_IOC_TYPE(BLKBSZSET), _IOC_NR(BLKBSZSET), __ARCH_COMPAT_SIZE_TYPE):
		validate_readable(arg, sizeof(__ARCH_COMPAT_SIZE_TYPE));
		block_device_set_sector_size(self, (size_t)*(__ARCH_COMPAT_SIZE_TYPE *)arg);
		break;
#endif /* __ARCH_HAVE_COMPAT */

	case BLKGETSIZE64:
#if __SIZEOF_SIZE_T__ != 8
	case _IOR(_IOC_TYPE(BLKGETSIZE64), _IOC_NR(BLKGETSIZE64), u64):
#endif /* __SIZEOF_SIZE_T__ != 8 */
		validate_writable(arg, sizeof(u64));
		*(u64 *)arg = (u64)self->bd_total_bytes;
		break;

#define BLKTRACESETUP    _IOWR(0x12, 115, struct blk_user_trace_setup)
#define BLKTRACESTART    _IO(0x12, 116)
#define BLKTRACESTOP     _IO(0x12, 117)
#define BLKTRACETEARDOWN _IO(0x12, 118)
#define BLKDISCARD       _IO(0x12, 119)
#define BLKIOMIN         _IO(0x12, 120)
#define BLKIOOPT         _IO(0x12, 121)
#define BLKALIGNOFF      _IO(0x12, 122)
#define BLKPBSZGET       _IO(0x12, 123)
#define BLKDISCARDZEROES _IO(0x12, 124)
#define BLKSECDISCARD    _IO(0x12, 125)
#define BLKROTATIONAL    _IO(0x12, 126)
#define BLKZEROOUT       _IO(0x12, 127)

	default:
		if (self->bd_type.dt_ioctl)
			return (*self->bd_type.dt_ioctl)((struct block_device *)self,
			                                 (struct block_device *)self,
			                                 command, arg, mode);
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      command);
	}
	return 0;
}



/* TODO: Load the given address range into the block-device cache. */
INTERN pos_t KCALL
handle_blockdevice_allocate(struct basic_block_device *__restrict self,
                            fallocate_mode_t mode, pos_t start, pos_t length);

INTERN void KCALL
handle_blockdevice_sync(struct basic_block_device *__restrict self) {
	block_device_sync(self);
}
DEFINE_INTERN_ALIAS(handle_blockdevice_datasync,
                    handle_blockdevice_sync);

INTERN void KCALL
handle_blockdevice_stat(struct basic_block_device *__restrict self,
                        USER CHECKED struct stat *result) {
	struct inode *node;
	memset(result, 0, sizeof(*result));
	node = self->bd_devfs_inode;
	if (node)
		inode_stat(node, result);
	result->st_mode = (result->st_mode & ~S_IFMT) | S_IFBLK;
	result->st_dev      = (__dev_t)block_device_devno(self);
	result->st_rdev     = (__dev_t)block_device_devno(self);
	result->st_size64   = (__pos64_t)self->bd_total_bytes;
	result->st_blksize  = (__blksize_t)self->bd_sector_size;
	result->st_blocks64 = (__blkcnt64_t)self->bd_sector_count;
}

INTERN poll_mode_t KCALL
handle_blockdevice_poll(struct basic_block_device *__restrict self, poll_mode_t what) {
	struct block_device *block;
	block = (struct block_device *)self;
	if (block_device_ispartition(self))
		block = ((struct block_device_partition *)self)->bp_master;
	if (what & POLLOUT) {
		if (rwlock_pollwrite(&block->bd_cache_lock))
			return POLLOUT | POLLIN;
	} else if (what & POLLIN) {
		if (rwlock_pollread(&block->bd_cache_lock))
			return POLLIN;
	}
	return 0;
}

INTERN syscall_slong_t
(KCALL handle_blockdevice_hop)(struct basic_block_device *__restrict self,
                               syscall_ulong_t cmd,
                               USER UNCHECKED void *arg,
                               iomode_t mode) {
	switch (cmd) {

	case HOP_BLOCKDEVICE_STAT: {
		struct hop_blockdevice_stat st;
		memset(&st, 0, sizeof(st));
		st.bs_struct_size  = sizeof(st);
		st.bs_total_bytes  = (u64)self->bd_total_bytes;
		st.bs_sector_count = (u64)self->bd_sector_count;
		st.bs_sector_size  = (u64)self->bd_sector_size;
		st.bs_device_flag  = self->bd_flags;
		st.bs_devno        = (u32)block_device_devno(self);
		st.bs_partcount    = 0;
		if (!block_device_ispartition(self)) {
			struct block_device *me;
			struct block_device_partition *iter;
			me = (struct block_device *)self;
			sync_read(&me->bd_parts_lock);
			for (iter = me->bd_parts; iter; iter = iter->bp_parts.ln_next)
				++st.bs_partcount;
			sync_endread(&me->bd_parts_lock);
		}
		memcpy(st.bs_name, self->bd_name,
		       MIN(sizeof(st.bs_name), sizeof(self->bd_name)));
		COMPILER_BARRIER();
		{
			struct hop_blockdevice_stat *info;
			size_t info_size;
			info = (struct hop_blockdevice_stat *)arg;
			validate_writable(info, sizeof(struct hop_blockdevice_stat));
			info_size = ATOMIC_READ(info->bs_struct_size);
			if (info_size != sizeof(struct hop_blockdevice_stat))
				THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_blockdevice_stat), info_size);
			memcpy(info, &st, sizeof(struct hop_blockdevice_stat));
		}
	}	break;

	case HOP_BLOCKDEVICE_SYNC:
		block_device_sync(self);
		break;

	case HOP_BLOCKDEVICE_RDREADONLY:
		validate_writable(arg, sizeof(u32));
		*(u32 *)arg = ATOMIC_READ(self->bd_flags) & BLOCK_DEVICE_FLAG_READONLY ? 1 : 0;
		break;

	case HOP_BLOCKDEVICE_WRREADONLY:
		if (arg)
			ATOMIC_FETCHOR(self->bd_flags, BLOCK_DEVICE_FLAG_READONLY);
		else {
			ATOMIC_FETCHAND(self->bd_flags, ~BLOCK_DEVICE_FLAG_READONLY);
		}
		break;

	case HOP_BLOCKDEVICE_OPENDRIVEROOT: {
		struct handle result_handle;
		result_handle.h_type = HANDLE_TYPE_BLOCKDEVICE;
		result_handle.h_mode = mode;
		result_handle.h_data = self;
		if (block_device_ispartition(self))
			result_handle.h_data = ((struct block_device_partition *)self)->bp_master;
		handle_installhop((struct hop_openfd *)arg, result_handle);
	}	break;

	case HOP_BLOCKDEVICE_OPENDRIVEPART:
		validate_writable(arg, sizeof(struct hop_blockdevice_openpart));
		if (block_device_ispartition(self))
			self = ((struct block_device_partition *)self)->bp_master;
		{
			struct handle result_handle;
			u32 index, count;
			struct block_device_partition *part;
			size_t struct_size = ATOMIC_READ(((struct hop_blockdevice_openpart *)arg)->bop_struct_size);
			if (struct_size != sizeof(struct hop_blockdevice_openpart))
				THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_blockdevice_openpart), struct_size);
			index = ((struct hop_blockdevice_openpart *)arg)->bop_partno;
			COMPILER_BARRIER();
			sync_read(&((struct block_device *)self)->bd_parts_lock);
			part = ((struct block_device *)self)->bd_parts;
			for (count = 0; index-- && part; ++count, part = part->bp_parts.ln_next)
				;
			if unlikely(!part) {
				sync_endread(&((struct block_device *)self)->bd_parts_lock);
				THROW(E_INDEX_ERROR_OUT_OF_BOUNDS, index + count, 0, count - 1);
			}
			incref(part);
			sync_endread(&((struct block_device *)self)->bd_parts_lock);
			result_handle.h_type = HANDLE_TYPE_BLOCKDEVICE;
			result_handle.h_mode = mode;
			result_handle.h_data = part;
			TRY {
				handle_installhop(&((struct hop_blockdevice_openpart *)arg)->bop_openfd, result_handle);
			} EXCEPT {
				decref(part);
				RETHROW();
			}
			decref(part);
		}
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_BLOCK_HANDLE_C */
