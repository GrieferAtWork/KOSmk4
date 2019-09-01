/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CTYPE_C
#define GUARD_LIBC_USER_CTYPE_C 1

#include "../api.h"
#include "ctype.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:__locale_ctype_ptr,hash:0xcf1917f4]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.__locale_ctype_ptr") char const *
NOTHROW(LIBCCALL libc___locale_ctype_ptr)(void)
/*[[[body:__locale_ctype_ptr]]]*/
{
	CRT_UNIMPLEMENTED("__locale_ctype_ptr"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__locale_ctype_ptr]]]*/

/*[[[head:__locale_ctype_ptr_l,hash:0xd19a7943]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype.__locale_ctype_ptr_l") char const *
NOTHROW_NCX(LIBCCALL libc___locale_ctype_ptr_l)(locale_t locale)
/*[[[body:__locale_ctype_ptr_l]]]*/
{
	CRT_UNIMPLEMENTED("__locale_ctype_ptr_l"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__locale_ctype_ptr_l]]]*/

/*[[[head:__ctype_b_loc,hash:0xc0267634]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.__ctype_b_loc") uint16_t const **
NOTHROW(LIBCCALL libc___ctype_b_loc)(void)
/*[[[body:__ctype_b_loc]]]*/
{
	CRT_UNIMPLEMENTED("__ctype_b_loc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__ctype_b_loc]]]*/

/*[[[head:__ctype_tolower_loc,hash:0x4d520164]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.__ctype_tolower_loc") int32_t const **
NOTHROW(LIBCCALL libc___ctype_tolower_loc)(void)
/*[[[body:__ctype_tolower_loc]]]*/
{
	CRT_UNIMPLEMENTED("__ctype_tolower_loc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__ctype_tolower_loc]]]*/

/*[[[head:__ctype_toupper_loc,hash:0x77292242]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype.__ctype_toupper_loc") int32_t const **
NOTHROW(LIBCCALL libc___ctype_toupper_loc)(void)
/*[[[body:__ctype_toupper_loc]]]*/
{
	CRT_UNIMPLEMENTED("__ctype_toupper_loc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__ctype_toupper_loc]]]*/

/*[[[head:_isctype,hash:0xfb7154a4]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.ctype._isctype") int
NOTHROW(LIBCCALL libc__isctype)(int ch,
                                int mask)
/*[[[body:_isctype]]]*/
{
	CRT_UNIMPLEMENTED("_isctype"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_isctype]]]*/

/*[[[head:_isctype_l,hash:0x81c961da]]]*/
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.ctype._isctype_l") int
NOTHROW_NCX(LIBCCALL libc__isctype_l)(int ch,
                                      int mask,
                                      locale_t locale)
/*[[[body:_isctype_l]]]*/
{
	CRT_UNIMPLEMENTED("_isctype_l"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_isctype_l]]]*/


/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x89b6ae44]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(__locale_ctype_ptr, libc___locale_ctype_ptr);
DEFINE_PUBLIC_WEAK_ALIAS(__locale_ctype_ptr_l, libc___locale_ctype_ptr_l);
DEFINE_PUBLIC_WEAK_ALIAS(__ctype_b_loc, libc___ctype_b_loc);
DEFINE_PUBLIC_WEAK_ALIAS(__ctype_tolower_loc, libc___ctype_tolower_loc);
DEFINE_PUBLIC_WEAK_ALIAS(__ctype_toupper_loc, libc___ctype_toupper_loc);
DEFINE_PUBLIC_WEAK_ALIAS(_isctype, libc__isctype);
DEFINE_PUBLIC_WEAK_ALIAS(_isctype_l, libc__isctype_l);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CTYPE_C */
