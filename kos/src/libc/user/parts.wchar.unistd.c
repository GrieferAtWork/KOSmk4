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

/*[[[head:libc_wttyname_r,hash:CRC-32=0xbebbdb5]]]*/
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_OUTS(2, 3) errno_t
NOTHROW_RPC(LIBKCALL libc_wttyname_r)(fd_t fd,
                                      char32_t *buf,
                                      size_t buflen)
/*[[[body:libc_wttyname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("wttyname_r(%" PRIxN(__SIZEOF_FD_T__) ", %p, %Ix)", fd, buf, buflen); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_wttyname_r]]]*/

/*[[[head:libd_wttyname_r,hash:CRC-32=0x714d3267]]]*/
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.unsorted") ATTR_OUTS(2, 3) errno_t
NOTHROW_RPC(LIBDCALL libd_wttyname_r)(fd_t fd,
                                      char16_t *buf,
                                      size_t buflen)
/*[[[body:libd_wttyname_r]]]*/
/*AUTO*/{
	(void)fd;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("DOS$wttyname_r(%" PRIxN(__SIZEOF_FD_T__) ", %p, %Ix)", fd, buf, buflen); /* TODO */
	return ENOSYS;
}
/*[[[end:libd_wttyname_r]]]*/


/*[[[start:exports,hash:CRC-32=0xe1ba2d13]]]*/
DEFINE_PUBLIC_ALIAS(DOS$wttyname_r, libd_wttyname_r);
DEFINE_PUBLIC_ALIAS(wttyname_r, libc_wttyname_r);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_C */
