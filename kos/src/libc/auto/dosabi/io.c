/* HASH CRC-32:0x8f14a328 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_IO_C
#define GUARD_LIBC_AUTO_DOSABI_IO_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/io.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.fs.property") NONNULL((1)) errno_t
NOTHROW_RPC(LIBDCALL libd__access_s)(char const *filename,
                                     int type) {
	return libc__access_s(filename, type);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") int
NOTHROW_NCX(LIBDCALL libd__findclose)(intptr_t findfd) {
	return libc__findclose(findfd);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBDCALL libd__findfirst32)(char const *__restrict filename,
                                        struct _finddata32_t *__restrict finddata) {
	return libc__findfirst32(filename, finddata);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBDCALL libd__findfirst32i64)(char const *__restrict filename,
                                           struct _finddata32i64_t *__restrict finddata) {
	return libc__findfirst32i64(filename, finddata);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED NONNULL((1, 2)) intptr_t
NOTHROW_RPC(LIBDCALL libd__findfirst64)(char const *__restrict filename,
                                        struct __finddata64_t *__restrict finddata) {
	return libc__findfirst64(filename, finddata);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd__findnext32)(intptr_t findfd,
                                       struct _finddata32_t *__restrict finddata) {
	return libc__findnext32(findfd, finddata);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd__findnext32i64)(intptr_t findfd,
                                          struct _finddata32i64_t *__restrict finddata) {
	return libc__findnext32i64(findfd, finddata);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.dir") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd__findnext64)(intptr_t findfd,
                                       struct __finddata64_t *__restrict finddata) {
	return libc__findnext64(findfd, finddata);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBDCALL libd__sopen_s)(fd_t *fd,
                                    char const *filename,
                                    oflag_t oflags,
                                    int sflags,
                                    mode_t mode) {
	return libc__sopen_s(fd, filename, oflags, sflags, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__mktemp_s)(char *template_,
                                     size_t size) {
	return libc__mktemp_s(template_, size);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.io") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd__pipe)(fd_t pipedes[2],
                                 uint32_t pipesize,
                                 oflag_t textmode) {
	return libc__pipe(pipedes, pipesize, textmode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED int64_t
NOTHROW_NCX(LIBDCALL libd__filelengthi64)(fd_t fd) {
	return libc__filelengthi64(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED int64_t
NOTHROW_NCX(LIBDCALL libd__telli64)(fd_t fd) {
	return libc__telli64(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") errno_t
NOTHROW_NCX(LIBDCALL libd_umask_s)(mode_t newmode,
                                   mode_t *oldmode) {
	return libc_umask_s(newmode, oldmode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") int
NOTHROW_RPC(LIBDCALL libd___lock_fhandle)(fd_t fd) {
	return libc___lock_fhandle(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") void
NOTHROW_NCX(LIBDCALL libd__unlock_fhandle)(fd_t fd) {
	libc__unlock_fhandle(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_PURE WUNUSED intptr_t
NOTHROW_NCX(LIBDCALL libd__get_osfhandle)(fd_t fd) {
	return libc__get_osfhandle(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED fd_t
NOTHROW_NCX(LIBDCALL libd__open_osfhandle)(intptr_t osfd,
                                           oflag_t flags) {
	return libc__open_osfhandle(osfd, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.io") oflag_t
NOTHROW_NCX(LIBDCALL libd_setmode)(fd_t fd,
                                   oflag_t mode) {
	return libc_setmode(fd, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.io") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(VLIBDCALL libd_sopen)(char const *filename,
                                  oflag_t oflags,
                                  int sflags,
                                  ...) {
	va_list args;
	mode_t v0_mode_t;
	va_start(args, sflags);
	v0_mode_t = va_arg(args, mode_t);
	va_end(args);
	return libc_sopen(filename, oflags, sflags, v0_mode_t);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED __LONG32_TYPE__
NOTHROW_NCX(LIBDCALL libd__filelength)(fd_t fd) {
	return libc__filelength(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED __LONG32_TYPE__
NOTHROW_NCX(LIBDCALL libd__tell)(fd_t fd) {
	return libc__tell(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") WUNUSED int
NOTHROW_NCX(LIBDCALL libd__eof)(fd_t fd) {
	return libc__eof(fd);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$_access_s, libd__access_s);
DEFINE_PUBLIC_ALIAS(DOS$_findclose, libd__findclose);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst, libd__findfirst32);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst32, libd__findfirst32);
DEFINE_PUBLIC_ALIAS(DOS$_findfirsti64, libd__findfirst32i64);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst32i64, libd__findfirst32i64);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst64i32, libd__findfirst64);
DEFINE_PUBLIC_ALIAS(DOS$_findfirst64, libd__findfirst64);
DEFINE_PUBLIC_ALIAS(DOS$_findnext, libd__findnext32);
DEFINE_PUBLIC_ALIAS(DOS$_findnext32, libd__findnext32);
DEFINE_PUBLIC_ALIAS(DOS$_findnexti64, libd__findnext32i64);
DEFINE_PUBLIC_ALIAS(DOS$_findnext32i64, libd__findnext32i64);
DEFINE_PUBLIC_ALIAS(DOS$_findnext64i32, libd__findnext64);
DEFINE_PUBLIC_ALIAS(DOS$_findnext64, libd__findnext64);
DEFINE_PUBLIC_ALIAS(DOS$_sopen_s_nolock, libd__sopen_s);
DEFINE_PUBLIC_ALIAS(DOS$_sopen_s, libd__sopen_s);
DEFINE_PUBLIC_ALIAS(DOS$_mktemp_s, libd__mktemp_s);
DEFINE_PUBLIC_ALIAS(DOS$_pipe, libd__pipe);
DEFINE_PUBLIC_ALIAS(DOS$_filelengthi64, libd__filelengthi64);
DEFINE_PUBLIC_ALIAS(DOS$_telli64, libd__telli64);
DEFINE_PUBLIC_ALIAS(DOS$umask_s, libd_umask_s);
DEFINE_PUBLIC_ALIAS(DOS$__lock_fhandle, libd___lock_fhandle);
DEFINE_PUBLIC_ALIAS(DOS$_unlock_fhandle, libd__unlock_fhandle);
DEFINE_PUBLIC_ALIAS(DOS$_get_osfhandle, libd__get_osfhandle);
DEFINE_PUBLIC_ALIAS(DOS$_open_osfhandle, libd__open_osfhandle);
DEFINE_PUBLIC_ALIAS(DOS$_setmode, libd_setmode);
DEFINE_PUBLIC_ALIAS(DOS$setmode, libd_setmode);
DEFINE_PUBLIC_ALIAS(DOS$_sopen, libd_sopen);
DEFINE_PUBLIC_ALIAS(DOS$sopen, libd_sopen);
DEFINE_PUBLIC_ALIAS(DOS$_filelength, libd__filelength);
DEFINE_PUBLIC_ALIAS(DOS$_tell, libd__tell);
DEFINE_PUBLIC_ALIAS(DOS$_eof, libd__eof);

#endif /* !GUARD_LIBC_AUTO_DOSABI_IO_C */
