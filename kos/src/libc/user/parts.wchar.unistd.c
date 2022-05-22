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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C
#define GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C 1
#define _UTF_SOURCE 1

#include "../api.h"
/**/

#include <sys/utsname.h>

#include <fcntl.h>
#include <format-printer.h>
#include <malloc.h>
#include <stdio.h> /* L_ctermid */
#include <string.h>
#include <uchar.h>
#include <unicode.h>
#include "unistd.h"

#include "parts.wchar.unistd.h"

DECL_BEGIN

/*[[[head:libc_wttyname_r,hash:CRC-32=0xfe95219]]]*/
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_ACCESS_WRS(2, 3) int
NOTHROW_RPC(LIBKCALL libc_wttyname_r)(fd_t fd,
                                      char32_t *buf,
                                      size_t buflen)
/*[[[body:libc_wttyname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("wttyname_r(%" PRIxN(__SIZEOF_FD_T__) ", %p, %Ix)", fd, buf, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_wttyname_r]]]*/

/*[[[head:libd_wttyname_r,hash:CRC-32=0xbe374bc5]]]*/
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unsorted") ATTR_ACCESS_WRS(2, 3) int
NOTHROW_RPC(LIBDCALL libd_wttyname_r)(fd_t fd,
                                      char16_t *buf,
                                      size_t buflen)
/*[[[body:libd_wttyname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("DOS$wttyname_r(%" PRIxN(__SIZEOF_FD_T__) ", %p, %Ix)", fd, buf, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_wttyname_r]]]*/

/*[[[head:libc_wreadlinkat,hash:CRC-32=0xe546ad90]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(3, 4) ssize_t
NOTHROW_RPC(LIBKCALL libc_wreadlinkat)(fd_t dfd,
                                       char32_t const *path,
                                       char32_t *buf,
                                       size_t buflen)
/*[[[body:libc_wreadlinkat]]]*/
{
	return libc_wfreadlinkat(dfd, path, buf, buflen, 0);
}
/*[[[end:libc_wreadlinkat]]]*/

/*[[[head:libd_wreadlinkat,hash:CRC-32=0xce246e64]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(3, 4) ssize_t
NOTHROW_RPC(LIBDCALL libd_wreadlinkat)(fd_t dfd,
                                       char16_t const *path,
                                       char16_t *buf,
                                       size_t buflen)
/*[[[body:libd_wreadlinkat]]]*/
{
	return libd_wfreadlinkat(dfd, path, buf, buflen, 0);
}
/*[[[end:libd_wreadlinkat]]]*/

/*[[[head:libc_wfreadlinkat,hash:CRC-32=0xe1dd4dd3]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(3, 4) ssize_t
NOTHROW_RPC(LIBKCALL libc_wfreadlinkat)(fd_t dfd,
                                        char32_t const *path,
                                        char32_t *buf,
                                        size_t buflen,
                                        atflag_t flags)
/*[[[body:libc_wfreadlinkat]]]*/
/*AUTO*/{
	(void)dfd;
	(void)path;
	(void)buf;
	(void)buflen;
	(void)flags;
	CRT_UNIMPLEMENTEDF("wfreadlinkat(%" PRIxN(__SIZEOF_FD_T__) ", %p, %p, %Ix, %" PRIxN(__SIZEOF_ATFLAG_T__) ")", dfd, path, buf, buflen, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_wfreadlinkat]]]*/

/*[[[head:libd_wfreadlinkat,hash:CRC-32=0xa4710097]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(3, 4) ssize_t
NOTHROW_RPC(LIBDCALL libd_wfreadlinkat)(fd_t dfd,
                                        char16_t const *path,
                                        char16_t *buf,
                                        size_t buflen,
                                        atflag_t flags)
/*[[[body:libd_wfreadlinkat]]]*/
/*AUTO*/{
	(void)dfd;
	(void)path;
	(void)buf;
	(void)buflen;
	(void)flags;
	CRT_UNIMPLEMENTEDF("DOS$wfreadlinkat(%" PRIxN(__SIZEOF_FD_T__) ", %p, %p, %Ix, %" PRIxN(__SIZEOF_ATFLAG_T__) ")", dfd, path, buf, buflen, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_wfreadlinkat]]]*/

/*[[[head:libc_wreadlink,hash:CRC-32=0x2483886e]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.property") ATTR_ACCESS_RO(1) ATTR_ACCESS_WRS(2, 3) ssize_t
NOTHROW_RPC(LIBKCALL libc_wreadlink)(char32_t const *path,
                                     char32_t *buf,
                                     size_t buflen)
/*[[[body:libc_wreadlink]]]*/
{
	return libc_wfreadlinkat(AT_FDCWD, path, buf, buflen, 0);
}
/*[[[end:libc_wreadlink]]]*/

/*[[[head:libd_wreadlink,hash:CRC-32=0x868144e0]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.property") ATTR_ACCESS_RO(1) ATTR_ACCESS_WRS(2, 3) ssize_t
NOTHROW_RPC(LIBDCALL libd_wreadlink)(char16_t const *path,
                                     char16_t *buf,
                                     size_t buflen)
/*[[[body:libd_wreadlink]]]*/
{
	return libd_wfreadlinkat(AT_FDCWD, path, buf, buflen, 0);
}
/*[[[end:libd_wreadlink]]]*/





/*[[[start:exports,hash:CRC-32=0x8b0c53b2]]]*/
DEFINE_PUBLIC_ALIAS(DOS$wttyname_r, libd_wttyname_r);
DEFINE_PUBLIC_ALIAS(wttyname_r, libc_wttyname_r);
DEFINE_PUBLIC_ALIAS(DOS$wreadlinkat, libd_wreadlinkat);
DEFINE_PUBLIC_ALIAS(wreadlinkat, libc_wreadlinkat);
DEFINE_PUBLIC_ALIAS(DOS$wfreadlinkat, libd_wfreadlinkat);
DEFINE_PUBLIC_ALIAS(wfreadlinkat, libc_wfreadlinkat);
DEFINE_PUBLIC_ALIAS(DOS$wreadlink, libd_wreadlink);
DEFINE_PUBLIC_ALIAS(wreadlink, libc_wreadlink);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C */
