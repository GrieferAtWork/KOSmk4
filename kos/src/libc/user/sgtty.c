/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SGTTY_C
#define GUARD_LIBC_USER_SGTTY_C 1

#include "../api.h"
#include "sgtty.h"

DECL_BEGIN

/*[[[head:libc_gtty,hash:CRC-32=0x5995acfa]]]*/
INTERN ATTR_SECTION(".text.crt.database.utmpx") ATTR_FDARG(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_gtty)(fd_t fd,
                                struct sgttyb *params)
/*[[[body:libc_gtty]]]*/
/*AUTO*/{
	(void)fd;
	(void)params;
	CRT_UNIMPLEMENTEDF("gtty(fd: %" PRIxN(__SIZEOF_FD_T__) ", params: %p)", fd, params); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_gtty]]]*/

/*[[[head:libc_stty,hash:CRC-32=0x3ac78736]]]*/
INTERN ATTR_SECTION(".text.crt.database.utmpx") ATTR_FDARG(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_stty)(fd_t fd,
                                struct sgttyb const *params)
/*[[[body:libc_stty]]]*/
/*AUTO*/{
	(void)fd;
	(void)params;
	CRT_UNIMPLEMENTEDF("stty(fd: %" PRIxN(__SIZEOF_FD_T__) ", params: %p)", fd, params); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_stty]]]*/





/*[[[start:exports,hash:CRC-32=0x974c9a28]]]*/
DEFINE_PUBLIC_ALIAS(gtty, libc_gtty);
DEFINE_PUBLIC_ALIAS(stty, libc_stty);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SGTTY_C */
