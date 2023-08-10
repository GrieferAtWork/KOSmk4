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
#ifndef GUARD_LIBC_USER_NL_TYPES_C
#define GUARD_LIBC_USER_NL_TYPES_C 1

#include "../api.h"
/**/

#include "nl_types.h"

DECL_BEGIN

/*[[[head:libc_catopen,hash:CRC-32=0x2708d50a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.malloc") ATTR_IN(1) nl_catd
NOTHROW_RPC(LIBCCALL libc_catopen)(char const *cat_name,
                                   int flag)
/*[[[body:libc_catopen]]]*/
/*AUTO*/{
	(void)cat_name;
	(void)flag;
	CRT_UNIMPLEMENTEDF("catopen(cat_name: %q, flag: %x)", cat_name, flag); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_catopen]]]*/

/*[[[head:libc_catgets,hash:CRC-32=0xa02104da]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.malloc") ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_catgets)(nl_catd catalog,
                                   int set,
                                   int number,
                                   char const *string)
/*[[[body:libc_catgets]]]*/
/*AUTO*/{
	(void)catalog;
	(void)set;
	(void)number;
	(void)string;
	CRT_UNIMPLEMENTEDF("catgets(catalog: %p, set: %x, number: %x, string: %q)", catalog, set, number, string); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_catgets]]]*/

/*[[[head:libc_catclose,hash:CRC-32=0xde9e3de2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.heap.malloc") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_catclose)(nl_catd catalog)
/*[[[body:libc_catclose]]]*/
/*AUTO*/{
	(void)catalog;
	CRT_UNIMPLEMENTEDF("catclose(catalog: %p)", catalog); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_catclose]]]*/

/*[[[start:exports,hash:CRC-32=0x62ebdd09]]]*/
DEFINE_PUBLIC_ALIAS(catopen, libc_catopen);
DEFINE_PUBLIC_ALIAS(catgets, libc_catgets);
DEFINE_PUBLIC_ALIAS(catclose, libc_catclose);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NL_TYPES_C */
