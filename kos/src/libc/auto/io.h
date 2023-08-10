/* HASH CRC-32:0x978513af */
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
#ifndef GUARD_LIBC_AUTO_IO_H
#define GUARD_LIBC_AUTO_IO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <io.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_IN(1) errno_t NOTHROW_RPC(LIBDCALL libd__access_s)(char const *filename, __STDC_INT_AS_UINT_T type);
INTDEF ATTR_IN(1) errno_t NOTHROW_RPC(LIBCCALL libc__access_s)(char const *filename, __STDC_INT_AS_UINT_T type);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd__umask_s)(mode_t nmode, mode_t *omode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUT(2) errno_t NOTHROW_NCX(LIBCCALL libc__umask_s)(mode_t nmode, mode_t *omode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_FDARG(1) oflag_t NOTHROW_NCX(LIBDCALL libd__setmode)(fd_t fd, oflag_t mode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_FDARG(1) oflag_t NOTHROW_NCX(LIBCCALL libc__setmode)(fd_t fd, oflag_t mode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd__findclose)(intptr_t findfd);
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBDCALL libd__findnext32)(intptr_t findfd, struct _finddata32_t *__restrict finddata);
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBDCALL libd__findnext32i64)(intptr_t findfd, struct _finddata32i64_t *__restrict finddata);
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBDCALL libd__findnext64)(intptr_t findfd, struct __finddata64_t *__restrict finddata);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBDCALL libd__sopen_s)(fd_t *fd, char const *filename, oflag_t oflags, int sflags, mode_t mode);
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBCCALL libc__sopen_s)(fd_t *fd, char const *filename, oflag_t oflags, int sflags, mode_t mode);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(5) errno_t NOTHROW_RPC(LIBDCALL libd__sopen_dispatch)(char const *filename, oflag_t oflags, int sflags, mode_t mode, fd_t *fd, int bsecure);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(5) errno_t NOTHROW_RPC(LIBCCALL libc__sopen_dispatch)(char const *filename, oflag_t oflags, int sflags, mode_t mode, fd_t *fd, int bsecure);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__mktemp_s)(char *template_, size_t size);
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd__pipe)(fd_t pipedes[2], uint32_t pipesize, oflag_t textmode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc__pipe)(fd_t pipedes[2], uint32_t pipesize, oflag_t textmode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_FDARG(1) int64_t NOTHROW_NCX(LIBDCALL libd__filelengthi64)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_FDARG(1) int64_t NOTHROW_NCX(LIBCCALL libc__filelengthi64)(fd_t fd);
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_umask_s)(mode_t newmode, mode_t *oldmode);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_umask_s)(mode_t newmode, mode_t *oldmode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBDCALL libd___lock_fhandle)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBCCALL libc___lock_fhandle)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_FDARG(1) void NOTHROW_NCX(LIBDCALL libd__unlock_fhandle)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_FDARG(1) void NOTHROW_NCX(LIBCCALL libc__unlock_fhandle)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED ATTR_FDARG(1) intptr_t NOTHROW_NCX(LIBDCALL libd__get_osfhandle)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED ATTR_FDARG(1) intptr_t NOTHROW_NCX(LIBCCALL libc__get_osfhandle)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBDCALL libd__open_osfhandle)(intptr_t osfd, oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBCCALL libc__open_osfhandle)(intptr_t osfd, oflag_t flags);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBDCALL libd_sopen)(char const *filename, oflag_t oflags, int sflags, ...);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBCCALL libc_sopen)(char const *filename, oflag_t oflags, int sflags, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_FDARG(1) __LONG32_TYPE__ NOTHROW_NCX(LIBDCALL libd__filelength)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_FDARG(1) __LONG32_TYPE__ NOTHROW_NCX(LIBCCALL libc__filelength)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd__eof)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_FDARG(1) int NOTHROW_NCX(LIBCCALL libc__eof)(fd_t fd);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_IO_H */
