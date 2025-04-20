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
#ifndef GUARD_KERNEL_CORE_FILESYS_PATHHANDLE_C
#define GUARD_KERNEL_CORE_FILESYS_PATHHANDLE_C 1

#include <kernel/compiler.h>

#include <kernel/fs/dirnode.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/path.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/mman/mfile.h>

#include <kos/kernel/handle.h>
#include <kos/types.h>

#include <stddef.h>

DECL_BEGIN

/* Handle operators for `HANDLE_TYPE_PATH' (`struct path')
 *
 * All of these are defined such that PATH objects act
 * as shallow  aliases for  the underlying  directory. */
DEFINE_HANDLE_REFCNT_FUNCTIONS(path, struct path);

INTDEF WUNUSED NONNULL((1)) size_t KCALL
handle_path_read(struct path *__restrict self, NCX void *dst,
                 size_t num_bytes, iomode_t mode) THROWS(...) {
	return mfile_uread(self->p_dir, dst, num_bytes, mode);
}

INTDEF WUNUSED NONNULL((1)) size_t KCALL
handle_path_write(struct path *__restrict self, NCX void const *src,
                  size_t num_bytes, iomode_t mode) THROWS(...) {
	return mfile_uwrite(self->p_dir, src, num_bytes, mode);
}

INTDEF WUNUSED NONNULL((1)) size_t KCALL
handle_path_pread(struct path *__restrict self, NCX void *dst,
                  size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	return mfile_upread(self->p_dir, dst, num_bytes, addr, mode);
}

INTDEF WUNUSED NONNULL((1)) size_t KCALL
handle_path_pwrite(struct path *__restrict self, NCX void const *src,
                   size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	return mfile_upwrite(self->p_dir, src, num_bytes, addr, mode);
}

INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL
handle_path_readv(struct path *__restrict self,
                  struct iov_buffer *__restrict dst,
                  size_t num_bytes, iomode_t mode) THROWS(...) {
	return mfile_ureadv(self->p_dir, dst, num_bytes, mode);
}

INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL
handle_path_writev(struct path *__restrict self,
                   struct iov_buffer *__restrict src,
                   size_t num_bytes, iomode_t mode) THROWS(...) {
	return mfile_uwritev(self->p_dir, src, num_bytes, mode);
}

INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL
handle_path_preadv(struct path *__restrict self, struct iov_buffer *__restrict dst,
                   size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	return mfile_upreadv(self->p_dir, dst, num_bytes, addr, mode);
}

INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL
handle_path_pwritev(struct path *__restrict self, struct iov_buffer *__restrict src,
                    size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	return mfile_upwritev(self->p_dir, src, num_bytes, addr, mode);
}

INTDEF NONNULL((1)) pos_t KCALL
handle_path_seek(struct path *__restrict self,
                 off_t offset, unsigned int whence) THROWS(...) {
	return mfile_useek(self->p_dir, offset, whence);
}

INTDEF NONNULL((1)) syscall_slong_t KCALL
handle_path_ioctl(struct path *__restrict self, ioctl_t cmd,
                  NCX UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	return mfile_uioctl(self->p_dir, cmd, arg, mode);
}

INTDEF NONNULL((1)) void KCALL
handle_path_truncate(struct path *__restrict self,
                     pos_t new_size) THROWS(...) {
	mfile_utruncate(self->p_dir, new_size);
}

INTDEF NONNULL((1, 2)) void KCALL
handle_path_mmap(struct path *__restrict self,
                 struct handle_mmap_info *__restrict info) THROWS(...) {
	mfile_ummap(self->p_dir, info);
	if (!path_isroot(self)) {
		if (!info->hmi_fsname && !info->hmi_fspath) {
			path_get_parent_and_name(self,
			                         &info->hmi_fspath,
			                         &info->hmi_fsname);
		} else {
			if (!info->hmi_fsname)
				info->hmi_fsname = path_getname(self);
			if (!info->hmi_fspath)
				info->hmi_fspath = path_getparent(self);
		}
	}
}

INTDEF NONNULL((1)) pos_t KCALL
handle_path_allocate(struct path *__restrict self, fallocate_mode_t mode,
                     pos_t start, pos_t length) THROWS(...) {
	return mfile_uallocate(self->p_dir, mode, start, length);
}

INTDEF NONNULL((1)) void KCALL
handle_path_sync(struct path *__restrict self) THROWS(...) {
	mfile_usync(self->p_dir);
}

INTDEF NONNULL((1)) void KCALL
handle_path_datasync(struct path *__restrict self) THROWS(...) {
	mfile_udatasync(self->p_dir);
}

INTDEF NONNULL((1)) void KCALL
handle_path_stat(struct path *__restrict self,
                 NCX struct stat *result) THROWS(...) {
	mfile_ustat(self->p_dir, result);
}

INTDEF NONNULL((1)) void KCALL
handle_path_pollconnect(struct path *__restrict self,
                        poll_mode_t what) THROWS(...) {
	mfile_upollconnect(self->p_dir, what);
}

INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_path_polltest(struct path *__restrict self,
                     poll_mode_t what) THROWS(...) {
	return mfile_upolltest(self->p_dir, what);
}

INTDEF NONNULL((1)) REF void *KCALL
handle_path_tryas(struct path *__restrict self,
                  uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	/* NOTE: Don't add a casting case for DIRENT!
	 *
	 * Such a function would cause problems with converting general purpose objects  into
	 * their path+name+file triples, the first of which (path) would not be casted as the
	 * caller already got a path. However,  as such they would end  up with a path and  a
	 * directory  entry identical to the last part of the path, which could lead to wrong
	 * representations when trying to print filesystem locations. */
	switch (wanted_type) {

	case HANDLE_TYPE_MFILE:
		return incref(self->p_dir);

	default:
		break;
	}
	return mfile_utryas(self->p_dir, wanted_type);
}

INTERN NONNULL((1, 2)) ssize_t KCALL
handle_path_printlink(struct path *__restrict self,
                      pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	REF struct path *root = fs_getroot(THIS_FS);
	FINALLY_DECREF_UNLIKELY(root);
	return path_print(self, printer, arg, 0, root);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_PATHHANDLE_C */
