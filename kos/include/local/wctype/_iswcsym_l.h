/* HASH CRC-32:0x42b6f272 */
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
#ifndef __local__iswcsym_l_defined
#define __local__iswcsym_l_defined 1
/* Dependency: "iswalnum_l" from "wctype" */
#ifndef ____localdep_iswalnum_l_defined
#define ____localdep_iswalnum_l_defined 1
#ifdef __CRT_HAVE_iswalnum_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_iswalnum_l,(__WINT_TYPE__ __wc, __locale_t __locale),iswalnum_l,(__wc,__locale))
#elif defined(__CRT_HAVE__iswalnum_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_iswalnum_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswalnum_l,(__wc,__locale))
#elif defined(__CRT_HAVE___iswalnum_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_iswalnum_l,(__WINT_TYPE__ __wc, __locale_t __locale),__iswalnum_l,(__wc,__locale))
#else /* LIBC: iswalnum_l */
#include <local/wctype/iswalnum_l.h>
#define __localdep_iswalnum_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum_l))
#endif /* iswalnum_l... */
#endif /* !____localdep_iswalnum_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_iswcsym_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_iswcsym_l))(__WINT_TYPE__ __wc,
                                                        __locale_t __locale) {
#line 387 "kos/src/libc/magic/wctype.c"
	return __localdep_iswalnum_l(__wc, __locale) || __wc == '_' || __wc == '$';
}
__NAMESPACE_LOCAL_END
#endif /* !__local__iswcsym_l_defined */
