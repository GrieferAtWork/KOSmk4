/* HASH CRC-32:0xc7d1ba7d */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_tolower_defined
#define __local_tolower_defined 1
/* Dependency: "__ctype_tolower_loc" from "ctype" */
#ifndef ____localdep___ctype_tolower_loc_defined
#define ____localdep___ctype_tolower_loc_defined 1
#ifdef __CRT_HAVE___ctype_tolower_loc
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__INT32_TYPE__ const **,__NOTHROW,__localdep___ctype_tolower_loc,(void),__ctype_tolower_loc,())
#else /* LIBC: __ctype_tolower_loc */
#undef ____localdep___ctype_tolower_loc_defined
#endif /* __ctype_tolower_loc... */
#endif /* !____localdep___ctype_tolower_loc_defined */

/* Dependency: "isupper" from "ctype" */
#ifndef ____localdep_isupper_defined
#define ____localdep_isupper_defined 1
#if __has_builtin(__builtin_isupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isupper)
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isupper)(int __ch) { return __builtin_isupper(__ch); }
#elif defined(__CRT_HAVE_isupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isupper,(int __ch),isupper,(__ch))
#else /* LIBC: isupper */
#include <local/ctype/isupper.h>
#define __localdep_isupper (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper))
#endif /* isupper... */
#endif /* !____localdep_isupper_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tolower) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(tolower))(int __ch) {
#line 291 "kos/src/libc/magic/ctype.c"
#if (defined(__CRT_HAVE___ctype_tolower_loc)) && defined(__CRT_CYG)
	return __ch >= -128 && __ch < 256 ? (*__localdep___ctype_tolower_loc())[__ch] : __ch;
#else
	return __localdep_isupper(__ch) ? ((__UINT8_TYPE__)__ch+0x20) : __ch;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_tolower_defined */
