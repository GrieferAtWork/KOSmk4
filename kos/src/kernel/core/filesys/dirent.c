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
#ifndef GUARD_KERNEL_CORE_FILESYS_DIRENT_C
#define GUARD_KERNEL_CORE_FILESYS_DIRENT_C 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/handle-proto.h>
#include <kernel/iovec.h>

#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>

#include <sys/stat.h>

#include <format-printer.h>
#include <string.h>

DECL_BEGIN

/* Return the hash of a given directory entry name.
 * This function is used by various APIs related to file lookup.
 * @throw: E_SEGFAULT: Failed to access the given `text'. */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) uintptr_t FCALL
fdirent_hash(CHECKED USER /*utf-8*/ char const *__restrict text, u16 textlen)
		THROWS(E_SEGFAULT) {
	uintptr_t hash = FDIRENT_EMPTY_HASH;
	uintptr_t const *iter, *end;

	/* Setup iterators. */
	iter = (uintptr_t const *)text;
	end  = iter + (textlen / sizeof(uintptr_t));

	/* Hash whole words */
	while (iter < end) {
		hash += UNALIGNED_GET(iter);
		hash *= 9;
		++iter;
	}

	/* Hash trailing word */
	switch (textlen & (sizeof(uintptr_t) - 1)) {
#if __SIZEOF_POINTER__ > 4
	case 7:
		hash += (uintptr_t)((byte_t const *)iter)[6] << 48;
		ATTR_FALLTHROUGH
	case 6:
		hash += (uintptr_t)((byte_t const *)iter)[5] << 40;
		ATTR_FALLTHROUGH
	case 5:
		hash += (uintptr_t)((byte_t const *)iter)[4] << 32;
		ATTR_FALLTHROUGH
	case 4:
		hash += (uintptr_t)((byte_t const *)iter)[3] << 24;
		ATTR_FALLTHROUGH
#endif /* __SIZEOF_POINTER__ > 4 */
	case 3:
		hash += (uintptr_t)((byte_t const *)iter)[2] << 16;
		ATTR_FALLTHROUGH
	case 2:
		hash += (uintptr_t)((byte_t const *)iter)[1] << 8;
		ATTR_FALLTHROUGH
	case 1:
		hash += (uintptr_t)((byte_t const *)iter)[0];
		break;
	default: break;
	}
	return hash;
}



/************************************************************************/
/* Handle operators for `HANDLE_TYPE_FDIRENT'                           */
/************************************************************************/
DEFINE_HANDLE_REFCNT_FUNCTIONS(fdirent, struct fdirent);

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_fdirent_pread(struct fdirent *__restrict self,
                     USER CHECKED void *dst, size_t num_bytes,
                     pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t avail;
	if (addr >= self->fd_namelen)
		return 0;
	avail = self->fd_namelen - (u16)addr;
	if (num_bytes > avail)
		num_bytes = avail;
	memcpy(dst, self->fd_name + (u16)addr, num_bytes);
	return num_bytes;
}

INTERN WUNUSED NONNULL((1, 2)) size_t KCALL
handle_fdirent_preadv(struct fdirent *__restrict self,
                      struct iov_buffer *__restrict dst,
                      size_t UNUSED(num_bytes),
                      pos_t addr, iomode_t mode) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		size_t temp;
		if (!ent.ive_size)
			continue;
		temp = handle_fdirent_pread(self, ent.ive_base,
		                            ent.ive_size, addr,
		                            mode);
		result += temp;
		if (temp < ent.ive_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_fdirent_readdir(struct fdirent *__restrict self,
                       USER CHECKED struct dirent *buf, size_t bufsize,
                       readdir_mode_t readdir_mode, iomode_t UNUSED(mode)) THROWS(...) {
	ssize_t result;
	result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
	                             self->fd_ops->fdo_getino ? 0 : self->fd_ino,
	                             self->fd_type, self->fd_namelen, self->fd_name);
	if (result < 0)
		result = ~result;
	return (size_t)result;
}

INTERN NONNULL((1)) void KCALL
handle_fdirent_stat(struct fdirent *__restrict self,
                    USER CHECKED struct stat *result) THROWS(...) {
	memset(result, 0, sizeof(*result));
	/* NOTE: In this case, we can't invoke the `fdo_getino' operator... :( */
	if (self->fd_ops->fdo_getino == NULL)
		result->st_ino = (typeof(result->st_ino))self->fd_ino;
	result->st_size = (typeof(result->st_size))self->fd_namelen;
}

INTERN ATTR_CONST WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_fdirent_polltest(struct fdirent *__restrict UNUSED(self),
                        poll_mode_t what) THROWS(...) {
	return what & POLLINMASK;
}


INTERN NONNULL((1, 2)) ssize_t KCALL
handle_fdirent_printlink(struct fdirent *__restrict self,
                         pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	return format_printf(printer, arg, "?/%$s",
	                     (size_t)self->fd_namelen,
	                     self->fd_name);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DIRENT_C */
