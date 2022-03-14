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
#ifndef GUARD_LIBC_USER_MBCTYPE_C
#define GUARD_LIBC_USER_MBCTYPE_C 1

#include "../api.h"
/**/

#include "mbctype.h"

DECL_BEGIN

/*[[[head:libc___p__mbctype,hash:CRC-32=0x1a410524]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") unsigned char *
NOTHROW_NCX(LIBCCALL libc___p__mbctype)(void)
/*[[[body:libc___p__mbctype]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__mbctype"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__mbctype]]]*/

/*[[[head:libc___p__mbcasemap,hash:CRC-32=0x87be1503]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") unsigned char *
NOTHROW_NCX(LIBCCALL libc___p__mbcasemap)(void)
/*[[[body:libc___p__mbcasemap]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__p__mbcasemap"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___p__mbcasemap]]]*/

/*[[[head:libc__setmbcp,hash:CRC-32=0xf6a4740e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") int
NOTHROW_NCX(LIBCCALL libc__setmbcp)(int cp)
/*[[[body:libc__setmbcp]]]*/
/*AUTO*/{
	(void)cp;
	CRT_UNIMPLEMENTEDF("_setmbcp(%x)", cp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__setmbcp]]]*/

/*[[[head:libc__getmbcp,hash:CRC-32=0x7c4da4a0]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__getmbcp)(void)
/*[[[body:libc__getmbcp]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("_getmbcp"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__getmbcp]]]*/

/*[[[head:libc__mbctouni_l,hash:CRC-32=0x26882aee]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED char32_t
NOTHROW_NCX(LIBCCALL libc__mbctouni_l)(unsigned int ch,
                                       locale_t locale)
/*[[[body:libc__mbctouni_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbctouni_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbctouni_l]]]*/

/*[[[head:libc__unitombc_l,hash:CRC-32=0x53209e36]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_PURE WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__unitombc_l)(char32_t ch,
                                       locale_t locale)
/*[[[body:libc__unitombc_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_unitombc_l(%" PRIx32 ", %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__unitombc_l]]]*/

/*[[[start:exports,hash:CRC-32=0x684938f5]]]*/
DEFINE_PUBLIC_ALIAS(__p__mbctype, libc___p__mbctype);
DEFINE_PUBLIC_ALIAS(__p__mbcasemap, libc___p__mbcasemap);
DEFINE_PUBLIC_ALIAS(_setmbcp, libc__setmbcp);
DEFINE_PUBLIC_ALIAS(_getmbcp, libc__getmbcp);
DEFINE_PUBLIC_ALIAS(_mbctouni_l, libc__mbctouni_l);
DEFINE_PUBLIC_ALIAS(_unitombc_l, libc__unitombc_l);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MBCTYPE_C */
