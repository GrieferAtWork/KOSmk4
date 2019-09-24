/* HASH CRC-32:0xf159ba92 */
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
#ifndef __local_wcstold_l_defined
#define __local_wcstold_l_defined 1
/* Dependency: "wcstold" from "wchar" */
#ifndef ____localdep_wcstold_defined
#define ____localdep_wcstold_defined 1
#ifdef __std___localdep_wcstold_defined
__NAMESPACE_STD_USING(__localdep_wcstold)
#elif defined(__CRT_HAVE_wcstold)
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1)),long double,__NOTHROW_NCX,__localdep_wcstold,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr),wcstold,(__nptr,__endptr))
#else /* LIBC: wcstold */
#include <local/wchar/wcstold.h>
#define __localdep_wcstold (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))
#endif /* wcstold... */
#endif /* !____localdep_wcstold_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcstold_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstold_l))(__WCHAR_TYPE__ const *__restrict __nptr,
                                                       __WCHAR_TYPE__ **__endptr,
                                                       __locale_t __locale) {
#line 1436 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_wcstold(__nptr, __endptr);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcstold_l_defined */
