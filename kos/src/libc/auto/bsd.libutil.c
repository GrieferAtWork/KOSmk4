/* HASH CRC-32:0x722fb884 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_BSD_LIBUTIL_C
#define GUARD_LIBC_AUTO_BSD_LIBUTIL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "bsd.libutil.h"
#include "../user/fcntl.h"
#include "../user/sys.file.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/fcntl.h>
#include <libc/errno.h>
#include <bits/types.h>
#include <bits/os/stat.h>
INTERN ATTR_SECTION(".text.crt.unsorted") fd_t
NOTHROW_RPC(VLIBCCALL libc_flopen)(const char *path,
                                   oflag_t flags,
                                   ...) {

	mode_t mode;
	va_list args;
	va_start(args, flags);
	mode = va_arg(args, mode_t);
	va_end(args);
	return libc_flopenat(__AT_FDCWD, path, flags, mode);
























































}
#include <asm/os/fcntl.h>
#include <libc/errno.h>
#include <bits/types.h>
#include <bits/os/stat.h>
INTERN ATTR_SECTION(".text.crt.unsorted") fd_t
NOTHROW_RPC(VLIBCCALL libc_flopenat)(fd_t dirfd,
                                     const char *path,
                                     oflag_t flags,
                                     ...) {

	int should_trunc;

	int flock_op;
	fd_t result;
	mode_t mode;
	va_list args;
	va_start(args, flags);
	mode = va_arg(args, mode_t);
	va_end(args);
	flock_op = __LOCK_EX;
#ifdef __O_EXLOCK
	flags &= ~__O_EXLOCK;
#endif /* __O_EXLOCK */
#ifdef __LOCK_NB
	if (flags & __O_NONBLOCK)
		flock_op |= __LOCK_NB;
#endif /* __LOCK_NB */

	should_trunc = flags & __O_TRUNC;
	flags &= ~__O_TRUNC;


again:
	result = libc_openat(dirfd, path, flags, mode);
	if likely(result != -1) {
		struct stat st_path, st_fd;
		if unlikely(libc_flock(result, flock_op))
			goto err_r;
		if unlikely(fstatat(dirfd, path, &st_path, 0))
			goto restart; /* Race condition: file was deleted */
		if unlikely(fstat(result, &st_fd))
			goto restart; /* Shouldn't happen */
		if unlikely(st_path.st_dev != st_fd.st_dev ||
		            st_path.st_ino != st_fd.st_ino)
			goto restart; /* File changed in the mean-time. */

		if (should_trunc && st_fd.st_size != 0) {
			if unlikely(libc_ftruncate(result, 0))
				goto err_r; /* Shouldn't happen */
		}

	}
	return result;
err_r:

	(void)libc_close(result);

	return -1;
restart:

	(void)libc_close(result);

	goto again;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(flopen, libc_flopen);
DEFINE_PUBLIC_ALIAS(flopenat, libc_flopenat);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_BSD_LIBUTIL_C */
