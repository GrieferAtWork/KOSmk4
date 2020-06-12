/* HASH CRC-32:0xa4b632b6 */
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
#ifndef GUARD_LIBC_AUTO_IO_C
#define GUARD_LIBC_AUTO_IO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/io.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__pipe)(fd_t pipedes[2],
                                 uint32_t pipesize,
                                 oflag_t textmode) {
	(void)pipesize;
	return pipe2(pipedes, textmode);
}
#include <asm/stdio.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED int64_t
NOTHROW_NCX(LIBCCALL libc__filelengthi64)(fd_t fd) {
	int64_t oldpos, result;
	oldpos = lseek64(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	result = lseek64(fd, 0, SEEK_END);
	if likely(result >= 0)
		lseek64(fd, oldpos, SEEK_SET);
	return result;
}
#include <asm/stdio.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED int64_t
NOTHROW_NCX(LIBCCALL libc__telli64)(fd_t fd) {
	return lseek64(fd, 0, __SEEK_CUR);
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") errno_t
NOTHROW_NCX(LIBCCALL libc_umask_s)(mode_t newmode,
                                   mode_t *oldmode) {
	if (!oldmode) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	*oldmode = umask(newmode);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_PURE WUNUSED intptr_t
NOTHROW_NCX(LIBCCALL libc__get_osfhandle)(fd_t fd) {
	COMPILER_IMPURE();
	return (intptr_t)fd;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc__open_osfhandle)(intptr_t osfd,
                                           oflag_t flags) {
	(void)flags;
	COMPILER_IMPURE();
	return (fd_t)osfd;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.io") oflag_t
NOTHROW_NCX(LIBCCALL libc_setmode)(fd_t fd,
                                   oflag_t mode) {
#ifdef __F_SETFL_XCH
	return fcntl(fd, __F_SETFL_XCH, mode);
#else /* __F_SETFL_XCH */
	oflag_t result;
	result = fcntl(fd, __F_GETFL);
	if unlikely(result < 0)
		return -1;
	return fcntl(fd, __F_SETFL, mode);
#endif /* !__F_SETFL_XCH */
}
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(VLIBCCALL libc_sopen)(char const *filename,
                                  oflag_t oflags,
                                  int sflags,
                                  ...) {
	fd_t result;
	va_list args;
	va_start(args, sflags);
	(void)sflags;
	result = open(filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED __LONG32_TYPE__
NOTHROW_NCX(LIBCCALL libc__filelength)(fd_t fd) {
	__LONG32_TYPE__ oldpos, result;
	oldpos = lseek(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	result = lseek(fd, 0, SEEK_END);
	if likely(result >= 0)
		lseek(fd, oldpos, SEEK_SET);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED __LONG32_TYPE__
NOTHROW_NCX(LIBCCALL libc__tell)(fd_t fd) {
	return lseek(fd, 0, SEEK_CUR);
}
#include <asm/stdio.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__eof)(fd_t fd) {
	int64_t oldpos, endpos;
	oldpos = lseek64(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	endpos = lseek64(fd, 0, SEEK_END);
	if likely(endpos >= 0) {
		if (endpos == oldpos)
			return 1;
		lseek64(fd, oldpos, SEEK_SET);
	}
	return 0;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_pipe, libc__pipe);
DEFINE_PUBLIC_ALIAS(_filelengthi64, libc__filelengthi64);
DEFINE_PUBLIC_ALIAS(_telli64, libc__telli64);
DEFINE_PUBLIC_ALIAS(umask_s, libc_umask_s);
DEFINE_PUBLIC_ALIAS(_get_osfhandle, libc__get_osfhandle);
DEFINE_PUBLIC_ALIAS(_open_osfhandle, libc__open_osfhandle);
DEFINE_PUBLIC_ALIAS(_setmode, libc_setmode);
DEFINE_PUBLIC_ALIAS(setmode, libc_setmode);
DEFINE_PUBLIC_ALIAS(_sopen, libc_sopen);
DEFINE_PUBLIC_ALIAS(sopen, libc_sopen);
DEFINE_PUBLIC_ALIAS(_filelength, libc__filelength);
DEFINE_PUBLIC_ALIAS(_tell, libc__tell);
DEFINE_PUBLIC_ALIAS(_eof, libc__eof);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_IO_C */
