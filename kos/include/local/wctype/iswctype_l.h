/* HASH CRC-32:0x6437365a */
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
#ifndef __local_iswctype_l_defined
#define __local_iswctype_l_defined 1
/* Dependency: "iswctype" from "wctype" */
#ifndef ____localdep_iswctype_defined
#define ____localdep_iswctype_defined 1
#ifdef __CRT_HAVE_iswctype
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_iswctype,(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_is_wctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_iswctype,(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE___iswctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_iswctype,(__WINT_TYPE__ __wc, __WCTYPE_TYPE__ __desc),__iswctype,(__wc,__desc))
#else /* LIBC: iswctype */
#include <local/wctype/iswctype.h>
#define __localdep_iswctype (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype))
#endif /* iswctype... */
#endif /* !____localdep_iswctype_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(iswctype_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(iswctype_l))(__WINT_TYPE__ __wc,
                                                        __WCTYPE_TYPE__ __type,
                                                        __locale_t __locale) {
#line 315 "kos/src/libc/magic/wctype.c"
	(void)__locale;
	__COMPILER_IMPURE();
	return __localdep_iswctype(__wc, __type);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_iswctype_l_defined */
