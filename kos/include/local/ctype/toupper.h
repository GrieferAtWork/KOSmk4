/* HASH CRC-32:0x4f9a3ad9 */
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
#ifndef __local_toupper_defined
#define __local_toupper_defined 1
/* Dependency: "__ctype_toupper_loc" from "ctype" */
#ifndef ____localdep___ctype_toupper_loc_defined
#define ____localdep___ctype_toupper_loc_defined 1
#ifdef __CRT_HAVE___ctype_toupper_loc
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__INT32_TYPE__ const **,__NOTHROW,__localdep___ctype_toupper_loc,(void),__ctype_toupper_loc,())
#else /* LIBC: __ctype_toupper_loc */
#undef ____localdep___ctype_toupper_loc_defined
#endif /* __ctype_toupper_loc... */
#endif /* !____localdep___ctype_toupper_loc_defined */

/* Dependency: "islower" from "ctype" */
#ifndef ____localdep_islower_defined
#define ____localdep_islower_defined 1
#if __has_builtin(__builtin_islower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_islower)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_islower)(int __ch) { return __builtin_islower(__ch); }
#elif defined(__CRT_HAVE_islower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_islower,(int __ch),islower,(__ch))
#else /* LIBC: islower */
#include <local/ctype/islower.h>
#define __localdep_islower (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower))
#endif /* islower... */
#endif /* !____localdep_islower_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(toupper) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(toupper))(int __ch) {
#line 299 "kos/src/libc/magic/ctype.c"
#if defined(__CRT_HAVE___ctype_toupper_loc) && defined(__CRT_CYG)
	return __ch >= -128 && __ch < 256 ? (*__localdep___ctype_toupper_loc())[__ch] : __ch;
#else
	return __localdep_islower(__ch) ? ((__UINT8_TYPE__)__ch-0x20) : __ch;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_toupper_defined */
