/* HASH CRC-32:0xc74461d4 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16stod_l_defined
#define __local_c16stod_l_defined 1
/* Dependency: "wcstod" from "wchar" */
#ifndef ____localdep_c16stod_defined
#define ____localdep_c16stod_defined 1
#if defined(__CRT_HAVE_wcstod) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,__localdep_c16stod,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr),wcstod,(__nptr,__endptr))
#elif defined(__CRT_HAVE_DOS$wcstod)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,__localdep_c16stod,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr),wcstod,(__nptr,__endptr))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcstod.h>
#define __localdep_c16stod(nptr, endptr) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))((__WCHAR_TYPE__ const *)(nptr), (__WCHAR_TYPE__ **)(endptr))
#else /* LIBC: c16stod */
#include <local/wchar/c16stod.h>
#define __localdep_c16stod (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16stod))
#endif /* c16stod... */
#endif /* !____localdep_c16stod_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16stod_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) double
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16stod_l))(__CHAR16_TYPE__ const *__restrict __nptr,
                                                       __CHAR16_TYPE__ **__endptr,
                                                       __locale_t __locale) {
#line 1672 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_c16stod(__nptr, __endptr);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16stod_l_defined */
