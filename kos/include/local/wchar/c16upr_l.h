/* HASH CRC-32:0xe3a4036b */
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
#ifndef __local_c16upr_l_defined
#define __local_c16upr_l_defined 1
/* Dependency: "towupper_l" from "wctype" */
#ifndef ____localdep_towupper_l_defined
#define ____localdep_towupper_l_defined 1
#if defined(__CRT_HAVE_towupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),towupper_l,(__wc,__locale))
#elif defined(__CRT_HAVE__towupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),_towupper_l,(__wc,__locale))
#elif defined(__CRT_HAVE___towupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towupper_l,(__WINT_TYPE__ __wc, __locale_t __locale),__towupper_l,(__wc,__locale))
#else /* LIBC: towupper_l */
#include <local/wctype/towupper_l.h>
#define __localdep_towupper_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper_l))
#endif /* towupper_l... */
#endif /* !____localdep_towupper_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16upr_l) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16upr_l))(__CHAR16_TYPE__ *__restrict __str,
                                                      __locale_t __locale) {
#line 4274 "kos/src/libc/magic/string.c"
	__CHAR16_TYPE__ *__iter, __ch;
	for (__iter = __str; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__CHAR16_TYPE__)__localdep_towupper_l(__ch, __locale);
	return __str;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16upr_l_defined */
