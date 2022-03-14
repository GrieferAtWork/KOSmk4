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
#ifndef GUARD_LIBC_USER_MBSTRING_C
#define GUARD_LIBC_USER_MBSTRING_C 1

#include "../api.h"
/**/

#include "mbstring.h"

DECL_BEGIN

/*[[[head:libc__mbbtombc_l,hash:CRC-32=0x49887d16]]]*/
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbbtombc_l)(unsigned int ch,
                                       locale_t locale)
/*[[[body:libc__mbbtombc_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbbtombc_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbbtombc_l]]]*/


/*[[[head:libc__mbctombb_l,hash:CRC-32=0xb254bfcd]]]*/
INTERN ATTR_SECTION(".text.crt.dos.mbstring") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctombb_l)(unsigned int ch,
                                       locale_t locale)
/*[[[body:libc__mbctombb_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbctombb_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbctombb_l]]]*/

/*[[[start:exports,hash:CRC-32=0xa191700b]]]*/
DEFINE_PUBLIC_ALIAS(_mbbtombc_l, libc__mbbtombc_l);
DEFINE_PUBLIC_ALIAS(_mbctombb_l, libc__mbctombb_l);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MBSTRING_C */
