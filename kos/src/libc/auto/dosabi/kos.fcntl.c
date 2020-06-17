/* HASH CRC-32:0xaa5ef3a8 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_KOS_FCNTL_C
#define GUARD_LIBC_AUTO_DOSABI_KOS_FCNTL_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/kos.fcntl.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.except.io.utility") __STDC_INT_AS_SSIZE_T
(VLIBDCALL libd_Fcntl)(fd_t fd,
                       int cmd,
                       ...) THROWS(...) {
	va_list args;
	void *v0;
	va_start(args, cmd);
	v0 = va_arg(args, void *);
	va_end(args);
	return libc_Fcntl(fd, cmd, v0);
}
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") WUNUSED NONNULL((1)) fd_t
(VLIBDCALL libd_Open)(char const *filename,
                      oflag_t oflags,
                      ...) THROWS(...) {
	va_list args;
	mode_t v0_mode_t;
	va_start(args, oflags);
	v0_mode_t = va_arg(args, mode_t);
	va_end(args);
	return libc_Open(filename, oflags, v0_mode_t);
}
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") WUNUSED NONNULL((1)) fd_t
(LIBDCALL libd_Creat)(char const *filename,
                      mode_t mode) THROWS(...) {
	return libc_Creat(filename, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") WUNUSED NONNULL((1)) fd_t
(VLIBDCALL libd_Open64)(char const *filename,
                        oflag_t oflags,
                        ...) THROWS(...) {
	va_list args;
	mode_t v0_mode_t;
	va_start(args, oflags);
	v0_mode_t = va_arg(args, mode_t);
	va_end(args);
	return libc_Open64(filename, oflags, v0_mode_t);
}
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") WUNUSED NONNULL((1)) fd_t
(LIBDCALL libd_Creat64)(char const *filename,
                        mode_t mode) THROWS(...) {
	return libc_Creat64(filename, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") WUNUSED NONNULL((2)) fd_t
(VLIBDCALL libd_OpenAt)(fd_t dirfd,
                        char const *filename,
                        oflag_t oflags,
                        ...) THROWS(...) {
	va_list args;
	mode_t v0_mode_t;
	va_start(args, oflags);
	v0_mode_t = va_arg(args, mode_t);
	va_end(args);
	return libc_OpenAt(dirfd, filename, oflags, v0_mode_t);
}
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") WUNUSED NONNULL((2)) fd_t
(VLIBDCALL libd_OpenAt64)(fd_t dirfd,
                          char const *filename,
                          oflag_t oflags,
                          ...) THROWS(...) {
	va_list args;
	mode_t v0_mode_t;
	va_start(args, oflags);
	v0_mode_t = va_arg(args, mode_t);
	va_end(args);
	return libc_OpenAt64(dirfd, filename, oflags, v0_mode_t);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$Fcntl, libd_Fcntl);
DEFINE_PUBLIC_ALIAS(DOS$Open, libd_Open);
DEFINE_PUBLIC_ALIAS(DOS$Creat, libd_Creat);
DEFINE_PUBLIC_ALIAS(DOS$Open64, libd_Open64);
DEFINE_PUBLIC_ALIAS(DOS$Creat64, libd_Creat64);
DEFINE_PUBLIC_ALIAS(DOS$OpenAt, libd_OpenAt);
DEFINE_PUBLIC_ALIAS(DOS$OpenAt64, libd_OpenAt64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_KOS_FCNTL_C */
