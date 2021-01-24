/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_HANDLE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/handle-proto.h>
#include <kernel/iovec.h>
#include <kernel/mman/mfile.h>

#include <kos/except.h>

#include <assert.h>

DECL_BEGIN

/* Handle operators for `HANDLE_TYPE_MFILE' (`struct mfile') */
DEFINE_HANDLE_REFCNT_FUNCTIONS(mfile, struct mfile);

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_read(struct mfile *__restrict self,
                  USER CHECKED void *dst,
                  size_t num_bytes, iomode_t mode)
		THROWS(...) {
	/* TODO: Dedicated operator in `self->mf_ops' */
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_write(struct mfile *__restrict self,
                   USER CHECKED void const *src,
                   size_t num_bytes, iomode_t mode)
		THROWS(...) {
	/* TODO: Dedicated operator in `self->mf_ops' */
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_readv(struct mfile *__restrict self,
                   struct aio_buffer *__restrict dst,
                   size_t UNUSED(num_bytes), iomode_t mode)
		THROWS(...) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH(ent, dst) {
		temp = handle_mfile_read(self, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp < ent.ab_size)
			break;
	}
	return result;
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_writev(struct mfile *__restrict self,
                    struct aio_buffer *__restrict src,
                    size_t num_bytes, iomode_t mode)
		THROWS(...) {
	size_t temp, result = 0;
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH(ent, src) {
		temp = handle_mfile_write(self, ent.ab_base, ent.ab_size, mode);
		result += temp;
		if (temp < ent.ab_size)
			break;
	}
	return result;
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_pread(struct mfile *__restrict self,
                   USER CHECKED void *dst, size_t num_bytes,
                   pos_t addr, iomode_t UNUSED(mode))
		THROWS(...) {
	mfile_read(self, dst, num_bytes, addr);
	return num_bytes;
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_pwrite(struct mfile *__restrict self,
                    USER CHECKED void const *src,
                    size_t num_bytes, pos_t addr,
                    iomode_t mode)
		THROWS(...) {
	mfile_write(self, src, num_bytes, addr);
	return num_bytes;
}


INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_preadv(struct mfile *__restrict self,
                    struct aio_buffer *__restrict dst,
                    size_t num_bytes, pos_t addr,
                    iomode_t mode) THROWS(...) {
	mfile_readv(self, dst);
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_mfile_pwritev(struct mfile *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_mfile_readdir(struct mfile *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTERN NONNULL((1)) pos_t KCALL
handle_mfile_seek(struct mfile *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTERN NONNULL((1)) syscall_slong_t KCALL
handle_mfile_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTERN NONNULL((1)) void KCALL
handle_mfile_truncate(struct mfile *__restrict self, pos_t new_size) THROWS(...);
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4, 5)) REF struct mfile *KCALL
handle_mfile_mmap(struct mfile *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes, REF struct path **__restrict  pmfile_fspath, REF struct directory_entry **__restrict pmfile_fsname) THROWS(...);
INTERN NONNULL((1)) pos_t KCALL
handle_mfile_allocate(struct mfile *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTERN NONNULL((1)) void KCALL
handle_mfile_sync(struct mfile *__restrict self) THROWS(...);
INTERN NONNULL((1)) void KCALL
handle_mfile_datasync(struct mfile *__restrict self) THROWS(...);
INTERN NONNULL((1)) void KCALL
handle_mfile_stat(struct mfile *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTERN NONNULL((1)) void KCALL
handle_mfile_pollconnect(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
INTERN WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_mfile_polltest(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
INTERN NONNULL((1)) syscall_slong_t KCALL
handle_mfile_hop(struct mfile *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTERN NONNULL((1)) REF void *KCALL
handle_mfile_tryas(struct mfile *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_HANDLE_C */
