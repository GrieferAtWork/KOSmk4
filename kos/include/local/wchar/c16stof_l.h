/* HASH CRC-32:0x2e914963 */
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
#ifndef __local_c16stof_l_defined
#define __local_c16stof_l_defined 1
/* Dependency: "wcstof" from "wchar" */
#ifndef ____localdep_c16stof_defined
#define ____localdep_c16stof_defined 1
#if defined(__CRT_HAVE_wcstof) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),float,__NOTHROW_NCX,__localdep_c16stof,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr),wcstof,(__nptr,__endptr))
#elif defined(__CRT_HAVE_DOS$wcstof)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_NONNULL((1)),float,__NOTHROW_NCX,__localdep_c16stof,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr),wcstof,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcstof.h>
#define __localdep_c16stof(nptr, endptr) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))((__WCHAR_TYPE__ const *)(nptr), (__WCHAR_TYPE__ **)(endptr))
#else /* LIBC: c16stof */
#include <local/wchar/c16stof.h>
#define __localdep_c16stof (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stof))
#endif /* c16stof... */
#endif /* !____localdep_c16stof_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16stof_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16stof_l))(__CHAR16_TYPE__ const *__restrict __nptr,
                                                       __CHAR16_TYPE__ **__endptr,
                                                       __locale_t __locale) {
#line 1500 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_c16stof(__nptr, __endptr);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16stof_l_defined */
