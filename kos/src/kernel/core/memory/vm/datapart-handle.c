/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_DATAPART_HANDLE_C
#define GUARD_KERNEL_SRC_MEMORY_VM_DATAPART_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <kernel/vm/futex.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except/inval.h>
#include <kos/hop/datapart.h>
#include <sys/stat.h>

#include <assert.h>
#include <errno.h>
#include <string.h>

DECL_BEGIN

/* datapart handle operation. */
INTERN NOBLOCK WUNUSED NONNULL((1)) refcnt_t
NOTHROW(FCALL handle_datapart_refcnt)(struct vm_datapart const *__restrict self) {
	return getrefcnt(self);
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handle_datapart_incref)(struct vm_datapart *__restrict self) {
	incref(self);
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL handle_datapart_decref)(REF struct vm_datapart *__restrict self) {
	vm_datapart_decref_and_merge(self);
}

/* TODO */
INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_datapart_pread(struct vm_datapart *__restrict self,
                      USER CHECKED void *dst, size_t num_bytes,
                      pos_t addr, iomode_t UNUSED(mode)) {
#if __FS_SIZEOF(OFF) > __SIZEOF_SIZE_T__
	if (addr > (pos_t)SIZE_MAX)
		return 0;
#endif /* __FS_SIZEOF(OFF) > __SIZEOF_SIZE_T__ */
	return vm_datapart_read(self, dst, num_bytes, (size_t)addr);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_datapart_pwrite(struct vm_datapart *__restrict self,
                       USER CHECKED void const *src, size_t num_bytes,
                       pos_t addr, iomode_t UNUSED(mode)) {
#if __FS_SIZEOF(OFF) > __SIZEOF_SIZE_T__
	if (addr > (pos_t)SIZE_MAX)
		return 0;
#endif /* __FS_SIZEOF(OFF) > __SIZEOF_SIZE_T__ */
	return vm_datapart_write(self, src, num_bytes, num_bytes, (size_t)addr);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_datapart_preadv(struct vm_datapart *__restrict self,
                       struct aio_buffer *__restrict dst,
                       size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) {
	assert(aio_buffer_size(dst) == num_bytes);
#if __FS_SIZEOF(OFF) > __SIZEOF_SIZE_T__
	if (addr > (pos_t)SIZE_MAX)
		return 0;
#endif /* __FS_SIZEOF(OFF) > __SIZEOF_SIZE_T__ */
	return vm_datapart_readv(self, dst, (size_t)addr);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_datapart_pwritev(struct vm_datapart *__restrict self,
                        struct aio_buffer *__restrict src,
                        size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) {
	assert(aio_buffer_size(src) == num_bytes);
#if __FS_SIZEOF(OFF) > __SIZEOF_SIZE_T__
	if (addr > (pos_t)SIZE_MAX)
		return 0;
#endif /* __FS_SIZEOF(OFF) > __SIZEOF_SIZE_T__ */
	return vm_datapart_writev(self, src, num_bytes, (size_t)addr);
}

DEFINE_HANDLE_APREAD_FROM_PREAD(datapart, struct vm_datapart)
DEFINE_HANDLE_APWRITE_FROM_PWRITE(datapart, struct vm_datapart)
DEFINE_HANDLE_APREADV_FROM_PREADV(datapart, struct vm_datapart)
DEFINE_HANDLE_APWRITEV_FROM_PWRITEV(datapart, struct vm_datapart)

LOCAL WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct vm_datablock *KCALL
vm_datapart_get_datablock(struct vm_datapart *__restrict self) {
	REF struct vm_datablock *result;
	sync_read(self);
	result = incref(self->dp_block);
	sync_endread(self);
	return result;
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_datapart_ioctl(struct vm_datapart *__restrict self,
                      syscall_ulong_t cmd,
                      USER UNCHECKED void *arg, iomode_t mode) {
	REF struct vm_datablock *block;
	block = vm_datapart_get_datablock(self);
	{
		FINALLY_DECREF_UNLIKELY(block);
		if (vm_datablock_isinode(block))
			return inode_ioctl((struct inode *)block, cmd, arg, mode);
	}
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}

INTERN NONNULL((1)) void KCALL
handle_datapart_truncate(struct vm_datapart *__restrict self, pos_t new_size) {
#if __SIZEOF_POINTER__ < 8
	if (new_size > (pos_t)((u32)-1))
		return;
#endif /* __SIZEOF_POINTER__ < 8 */
	xdecref(vm_datapart_split(self, (size_t)(new_size / PAGESIZE)));
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL
handle_datapart_mmap(struct vm_datapart *__restrict self,
                     pos_t *__restrict pminoffset,
                     pos_t *__restrict pnumbytes) {
	REF struct vm_datablock *result;
	sync_read(self);
	result      = incref(self->dp_block);
	*pminoffset = vm_datapart_minbyte(self);
	*pnumbytes  = (pos_t)vm_datapart_numbytes(self);
	sync_endread(self);
	return result;
}

//INTERN pos_t KCALL /* TODO: Pre-initialize specified reanges. */
//handle_datapart_allocate(struct vm_datapart *__restrict self,
//                         fallocate_mode_t mode, pos_t start, pos_t length) {
//}

INTERN void KCALL
handle_datapart_sync(struct vm_datapart *__restrict self) {
	vm_datapart_sync(self);
}
DEFINE_INTERN_ALIAS(handle_datapart_datasync, handle_datapart_sync);

INTERN void KCALL
handle_datapart_stat(struct vm_datapart *__restrict self,
                     USER CHECKED struct stat *result) {
	REF struct vm_datablock *block;
	block = vm_datapart_get_datablock(self);
	FINALLY_DECREF_UNLIKELY(block);
	if (vm_datablock_isinode(block)) {
		struct basic_block_device *dev;
		struct inode *ino = (struct inode *)block;
		dev = ino->i_super->s_device;
		result->st_dev   = (__dev_t)(dev ? block_device_devno(dev) : 0);
		result->st_ino   = (__FS_TYPE(ino))ino->i_fileino;
		result->st_mode  = (__mode_t)ino->i_filemode;
		result->st_nlink = (__nlink_t)ino->i_filenlink;
		result->st_uid   = (__uid_t)ino->i_fileuid;
		result->st_gid   = (__gid_t)ino->i_filegid;
		result->st_rdev  = (__dev_t)ino->i_filerdev;
#ifdef __TIMESPEC64_HAVE_TV_PAD
		/* Don't accidentally leak kernel data! */
		{
			struct timespec temp;
			temp.tv_sec   = ino->i_fileatime.tv_sec;
			temp.tv_nsec  = ino->i_fileatime.tv_nsec;
			temp.__tv_pad = 0;
			COMPILER_WRITE_BARRIER();
			result->st_atimespec = temp;

			temp.tv_sec   = ino->i_filemtime.tv_sec;
			temp.tv_nsec  = ino->i_filemtime.tv_nsec;
			temp.__tv_pad = 0;
			COMPILER_WRITE_BARRIER();
			result->st_mtimespec = temp;

			temp.tv_sec   = ino->i_filectime.tv_sec;
			temp.tv_nsec  = ino->i_filectime.tv_nsec;
			temp.__tv_pad = 0;
			COMPILER_WRITE_BARRIER();
			result->st_ctimespec = temp;
		}
#else /* __TIMESPEC64_HAVE_TV_PAD */
		result->st_atimespec = ino->i_fileatime;
		result->st_mtimespec = ino->i_filemtime;
		result->st_ctimespec = ino->i_filectime;
#endif /* !__TIMESPEC64_HAVE_TV_PAD */
	} else {
		result->st_dev   = 0;
		result->st_ino   = 0;
		result->st_mode  = 0;
		result->st_nlink = 0;
		result->st_uid   = 0;
		result->st_gid   = 0;
		result->st_rdev  = 0;
		memset(&result->st_atimespec, 0, sizeof(result->st_atimespec));
		memset(&result->st_mtimespec, 0, sizeof(result->st_mtimespec));
		memset(&result->st_ctimespec, 0, sizeof(result->st_ctimespec));
	}
	result->st_size    = (__FS_TYPE(pos))vm_datapart_numbytes(self);
	result->st_blksize = (__blksize_t)VM_DATABLOCK_PAGESIZE(block);
	result->st_blocks  = (__FS_TYPE(blkcnt))CEILDIV(result->st_size, VM_DATABLOCK_PAGESIZE(block));
}

INTERN syscall_slong_t KCALL
handle_datapart_hop(struct vm_datapart *__restrict self, syscall_ulong_t cmd,
                    USER UNCHECKED void *arg, iomode_t mode) {
	switch (cmd) {

	case HOP_DATAPART_OPEN_DATABLOCK: {
		struct handle hnd;
		hnd.h_type = HANDLE_TYPE_DATABLOCK;
		hnd.h_mode = mode;
		hnd.h_data = vm_datapart_get_datablock(self);
		FINALLY_DECREF_UNLIKELY((struct vm_datablock *)hnd.h_data);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, hnd);
	}	break;

	case HOP_DATAPART_OPEN_FUTEX:
	case HOP_DATAPART_OPEN_FUTEX_EXISTING: {
		size_t struct_size;
		struct hop_datablock_open_futex *data;
		REF struct vm_futex *ftx;
		struct handle hnd;
		validate_writable(arg, sizeof(struct hop_datablock_open_futex));
		data        = (struct hop_datablock_open_futex *)arg;
		struct_size = ATOMIC_READ(data->dof_struct_size);
		if (struct_size != sizeof(struct hop_datablock_open_futex))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_datablock_open_futex), struct_size);
		if (cmd == HOP_DATAPART_OPEN_FUTEX_EXISTING) {
			ftx = vm_datapart_getfutex_existing(self, (uintptr_t)data->dof_address);
			if (!ftx)
				return -ENOENT;
		} else {
			ftx = vm_datapart_getfutex(self, (uintptr_t)data->dof_address);
		}
		if (ftx == VM_DATAPART_GETFUTEX_OUTOFRANGE)
			return -ERANGE;
		FINALLY_DECREF_UNLIKELY(ftx);
		hnd.h_type = HANDLE_TYPE_FUTEX;
		hnd.h_mode = mode;
		hnd.h_data = ftx;
		return handle_installhop(&data->dof_openfd, hnd);
	}	break;

	case HOP_DATAPART_STAT: {
		size_t struct_size;
		struct hop_datapart_stat info;
		struct hop_datapart_stat *data;
		STATIC_ASSERT(HOP_DATAPART_STAT_FEATURE_ISLOCKED == VM_DATAPART_FLAG_LOCKED);
		STATIC_ASSERT(HOP_DATAPART_STAT_FEATURE_HASCHANGED == VM_DATAPART_FLAG_CHANGED);
		STATIC_ASSERT(HOP_DATAPART_STAT_FEATURE_KEEPRAM == VM_DATAPART_FLAG_KEEPRAM);
		STATIC_ASSERT(HOP_DATAPART_STAT_FEATURE_TRKCHNG == VM_DATAPART_FLAG_TRKCHNG);
		STATIC_ASSERT(HOP_DATAPART_STAT_FEATURE_COREPRT == VM_DATAPART_FLAG_COREPRT);
		STATIC_ASSERT(HOP_DATAPART_STAT_FEATURE_KERNPRT == VM_DATAPART_FLAG_KERNPRT);
		STATIC_ASSERT(HOP_DATAPART_STAT_STATE_ABSENT == VM_DATAPART_STATE_ABSENT);
		STATIC_ASSERT(HOP_DATAPART_STAT_STATE_INCORE == VM_DATAPART_STATE_INCORE);
		STATIC_ASSERT(HOP_DATAPART_STAT_STATE_LOCKED == VM_DATAPART_STATE_LOCKED);
#ifdef VM_DATAPART_STATE_INSWAP
		STATIC_ASSERT(HOP_DATAPART_STAT_STATE_INSWAP == VM_DATAPART_STATE_INSWAP);
#endif /* VM_DATAPART_STATE_INSWAP */
#ifdef VM_DATAPART_STATE_VIOPRT
		STATIC_ASSERT(HOP_DATAPART_STAT_STATE_VIOPRT == VM_DATAPART_STATE_VIOPRT);
#endif /* VM_DATAPART_STATE_VIOPRT */
		validate_writable(arg, sizeof(struct hop_datapart_stat));
		data        = (struct hop_datapart_stat *)arg;
		struct_size = ATOMIC_READ(data->ds_struct_size);
		if (struct_size != sizeof(struct hop_datapart_stat))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_datapart_stat), struct_size);
		/* Gather information about the datapart. */
		sync_read(self);
		info.ds_features = self->dp_flags;
		if (self->dp_block->db_parts == VM_DATABLOCK_ANONPARTS)
			info.ds_features |= HOP_DATAPART_STAT_FEATURE_ISANON;
		if (self->dp_futex) {
			info.ds_features |= HOP_DATAPART_STAT_FEATURE_HASFUTEXCTRL;
			if (self->dp_futex->fc_tree != NULL)
				info.ds_features |= HOP_DATAPART_STAT_FEATURE_HASFUTEXLIVE;
		}
		if (self->dp_crefs)
			info.ds_features |= HOP_DATAPART_STAT_FEATURE_HASCMAP;
		if (self->dp_srefs)
			info.ds_features |= HOP_DATAPART_STAT_FEATURE_HASSMAP;
		info.ds_state    = self->dp_state;
		info.ds_minaddr  = (u64)vm_datapart_minbyte(self);
		info.ds_maxaddr  = (u64)vm_datapart_maxbyte(self);
		info.ds_minvpage = (u64)vm_datapart_minvpage(self);
		info.ds_maxvpage = (u64)vm_datapart_maxvpage(self);
		info.ds_mindpage = (u64)vm_datapart_mindpage(self);
		info.ds_maxdpage = (u64)vm_datapart_maxdpage(self);
		sync_endread(self);
		/* Copy collected information to user-space. */
		COMPILER_BARRIER();
		data->ds_features = info.ds_features;
		data->ds_state    = info.ds_state;
		data->ds_minaddr  = info.ds_minaddr;
		data->ds_maxaddr  = info.ds_maxaddr;
		data->ds_minvpage = info.ds_minvpage;
		data->ds_maxvpage = info.ds_maxvpage;
		data->ds_mindpage = info.ds_mindpage;
		data->ds_maxdpage = info.ds_maxdpage;
	}	break;

	case HOP_DATAPART_HASCHANGED: {
		size_t struct_size;
		struct hop_datablock_haschanged *data;
		REF struct vm_datablock *block;
		bool has_changed;
		validate_writable(arg, sizeof(struct hop_datablock_haschanged));
		data        = (struct hop_datablock_haschanged *)arg;
		struct_size = ATOMIC_READ(data->dhc_struct_size);
		if (struct_size != sizeof(struct hop_datablock_haschanged))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_datablock_haschanged), struct_size);
		sync_read(self);
		block = incref(self->dp_block);
		sync_endread(self);
		{
			size_t mindatapage, maxdatapage;
			FINALLY_DECREF_UNLIKELY(block);
			mindatapage = (size_t)data->dhc_minbyte >> VM_DATABLOCK_ADDRSHIFT(block);
			maxdatapage = (((size_t)data->dhc_maxbyte + VM_DATABLOCK_PAGESIZE(block)) >> VM_DATABLOCK_ADDRSHIFT(block)) - 1;
			has_changed = vm_datapart_haschanged(self, mindatapage, maxdatapage);
		}
		COMPILER_WRITE_BARRIER();
		data->dhc_result = has_changed ? HOP_DATABLOCK_HASCHANGED_FLAG_DIDCHANGE
		                               : HOP_DATABLOCK_HASCHANGED_FLAG_UNCHANGED;
	}	break;


	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}




DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_DATAPART_HANDLE_C */
