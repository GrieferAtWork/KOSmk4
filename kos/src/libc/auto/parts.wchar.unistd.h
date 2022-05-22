/* HASH CRC-32:0x3e370f0b */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_UNISTD_H
#define GUARD_LIBC_AUTO_PARTS_WCHAR_UNISTD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/unistd.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char16_t *NOTHROW_RPC(LIBDCALL libd_wttyname)(fd_t fd);
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char32_t *NOTHROW_RPC(LIBKCALL libc_wttyname)(fd_t fd);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wchown)(char16_t const *file, uid_t owner, gid_t group);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wchown)(char32_t const *file, uid_t owner, gid_t group);
INTDEF ATTR_IN(1) longptr_t NOTHROW_RPC(LIBDCALL libd_wpathconf)(char16_t const *path, __STDC_INT_AS_UINT_T name);
INTDEF ATTR_IN(1) longptr_t NOTHROW_RPC(LIBKCALL libc_wpathconf)(char32_t const *path, __STDC_INT_AS_UINT_T name);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wlink)(char16_t const *from, char16_t const *to);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wlink)(char32_t const *from, char32_t const *to);
INTDEF WUNUSED ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_waccess)(char16_t const *file, __STDC_INT_AS_UINT_T type);
INTDEF WUNUSED ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_waccess)(char32_t const *file, __STDC_INT_AS_UINT_T type);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wchdir)(char16_t const *path);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wchdir)(char32_t const *path);
INTDEF ATTR_OUTS(1, 2) char16_t *NOTHROW_RPC(LIBDCALL libd_wgetcwd)(char16_t *buf, size_t bufsize);
INTDEF ATTR_OUTS(1, 2) char32_t *NOTHROW_RPC(LIBKCALL libc_wgetcwd)(char32_t *buf, size_t bufsize);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wunlink)(char16_t const *file);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wunlink)(char32_t const *file);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wrmdir)(char16_t const *path);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wrmdir)(char32_t const *path);
INTDEF WUNUSED ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_weuidaccess)(char16_t const *file, __STDC_INT_AS_UINT_T type);
INTDEF WUNUSED ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_weuidaccess)(char32_t const *file, __STDC_INT_AS_UINT_T type);
INTDEF ATTR_MALLOC WUNUSED char16_t *NOTHROW_RPC(LIBDCALL libd_wget_current_dir_name)(void);
INTDEF ATTR_MALLOC WUNUSED char32_t *NOTHROW_RPC(LIBKCALL libc_wget_current_dir_name)(void);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wfaccessat)(fd_t dfd, char16_t const *file, __STDC_INT_AS_UINT_T type, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wfaccessat)(fd_t dfd, char32_t const *file, __STDC_INT_AS_UINT_T type, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wfchownat)(fd_t dfd, char16_t const *file, uid_t owner, gid_t group, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wfchownat)(fd_t dfd, char32_t const *file, uid_t owner, gid_t group, atflag_t flags);
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBDCALL libd_wlinkat)(fd_t fromfd, char16_t const *from, fd_t tofd, char16_t const *to, atflag_t flags);
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBKCALL libc_wlinkat)(fd_t fromfd, char32_t const *from, fd_t tofd, char32_t const *to, atflag_t flags);
INTDEF ATTR_IN(1) ATTR_IN(3) int NOTHROW_RPC(LIBDCALL libd_wsymlinkat)(char16_t const *link_text, fd_t tofd, char16_t const *target_path);
INTDEF ATTR_IN(1) ATTR_IN(3) int NOTHROW_RPC(LIBKCALL libc_wsymlinkat)(char32_t const *link_text, fd_t tofd, char32_t const *target_path);
INTDEF ATTR_IN(1) ATTR_IN(3) int NOTHROW_RPC(LIBDCALL libd_wfsymlinkat)(char16_t const *link_text, fd_t tofd, char16_t const *target_path, atflag_t flags);
INTDEF ATTR_IN(1) ATTR_IN(3) int NOTHROW_RPC(LIBKCALL libc_wfsymlinkat)(char32_t const *link_text, fd_t tofd, char32_t const *target_path, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wunlinkat)(fd_t dfd, char16_t const *file, atflag_t flags);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wunlinkat)(fd_t dfd, char32_t const *file, atflag_t flags);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wlchown)(char16_t const *file, uid_t owner, gid_t group);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wlchown)(char32_t const *file, uid_t owner, gid_t group);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_wtruncate)(char16_t const *file, __PIO_OFFSET length);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBKCALL libc_wtruncate)(char32_t const *file, __PIO_OFFSET length);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_wtruncate64)(char16_t const *file, __PIO_OFFSET64 length);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBKCALL libc_wtruncate64)(char32_t const *file, __PIO_OFFSET64 length);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wsymlink)(char16_t const *link_text, char16_t const *target_path);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wsymlink)(char32_t const *link_text, char32_t const *target_path);
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_wgethostname)(char16_t *name, size_t buflen);
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBKCALL libc_wgethostname)(char32_t *name, size_t buflen);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_wsetlogin)(char16_t const *name);
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBKCALL libc_wsetlogin)(char32_t const *name);
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBDCALL libd_wsethostname)(char16_t const *name, size_t len);
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBKCALL libc_wsethostname)(char32_t const *name, size_t len);
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_wgetdomainname)(char16_t *name, size_t buflen);
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBKCALL libc_wgetdomainname)(char32_t *name, size_t buflen);
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBDCALL libd_wsetdomainname)(char16_t const *name, size_t len);
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBKCALL libc_wsetdomainname)(char32_t const *name, size_t len);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wchroot)(char16_t const *path);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wchroot)(char32_t const *path);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_UNISTD_H */
