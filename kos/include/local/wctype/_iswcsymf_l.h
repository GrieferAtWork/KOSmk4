/* HASH 0xc62bb93b */
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
#ifndef __local__iswcsymf_l_defined
#define __local__iswcsymf_l_defined 1
/* Dependency: "iswalpha_l" from "wctype" */
#ifndef ____localdep_iswalpha_l_defined
#define ____localdep_iswalpha_l_defined 1
#if defined(__CRT_HAVE_iswalpha_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE,int,__NOTHROW_NCX,__localdep_iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswalpha_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswalpha_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE,int,__NOTHROW_NCX,__localdep_iswalpha_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswalpha_l,(__wc,__locale))
#else /* LIBC: iswalpha_l */
#include <local/wctype/iswalpha_l.h>
#define __localdep_iswalpha_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha_l))
#endif /* iswalpha_l... */
#endif /* !____localdep_iswalpha_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_iswcsymf_l) __ATTR_WUNUSED __ATTR_PURE int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_iswcsymf_l))(__WINT_TYPE__ __wc,
                                                         __locale_t __locale) {
#line 382 "kos/src/libc/magic/wctype.c"
	return __localdep_iswalpha_l(__wc, __locale) || __wc == '_' || __wc == '$';
}
__NAMESPACE_LOCAL_END
#endif /* !__local__iswcsymf_l_defined */
