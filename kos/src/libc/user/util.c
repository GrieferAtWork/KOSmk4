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
#ifndef GUARD_LIBC_USER_UTIL_C
#define GUARD_LIBC_USER_UTIL_C 1

#include "../api.h"
#include "util.h"

DECL_BEGIN

/*[[[head:libc_opendev,hash:CRC-32=0x4f6d6be6]]]*/
/* >> opendev(3)
 * @param: dflags: Set of `0 | OPENDEV_PART | OPENDEV_BLCK' */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED ATTR_IN(1) ATTR_OUT_OPT(4) fd_t
NOTHROW_RPC(LIBCCALL libc_opendev)(char const *path,
                                   oflag_t oflags,
                                   __STDC_INT_AS_UINT_T dflags,
                                   char **realpath)
/*[[[body:libc_opendev]]]*/
/*AUTO*/{
	(void)path;
	(void)oflags;
	(void)dflags;
	(void)realpath;
	CRT_UNIMPLEMENTEDF("opendev(path: %q, oflags: %" PRIxN(__SIZEOF_OFLAG_T__) ", dflags: %x, realpath: %p)", path, oflags, dflags, realpath); /* TODO */
	return (fd_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_opendev]]]*/

/*[[[start:exports,hash:CRC-32=0x631bf773]]]*/
DEFINE_PUBLIC_ALIAS(opendev, libc_opendev);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UTIL_C */
