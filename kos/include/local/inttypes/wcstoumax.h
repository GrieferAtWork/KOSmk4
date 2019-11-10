/* HASH CRC-32:0x294547b3 */
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
#ifndef __local_wcstoumax_defined
#define __local_wcstoumax_defined 1
/* Dependency: "wcstou32" from "wchar" */
#ifndef ____localdep_wcstou32_defined
#define ____localdep_wcstou32_defined 1
#ifdef __CRT_HAVE_wcstou32
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_wcstou32,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_wcstou32,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_wcstou32,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_wcstou32,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_wcstou32,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#else /* LIBC: wcstou32 */
#include <local/wchar/wcstou32.h>
#define __localdep_wcstou32 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))
#endif /* wcstou32... */
#endif /* !____localdep_wcstou32_defined */

/* Dependency: "wcstou64" from "wchar" */
#ifndef ____localdep_wcstou64_defined
#define ____localdep_wcstou64_defined 1
#ifdef __CRT_HAVE_wcstou64
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_wcstou64,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_wcstou64,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_wcstou64,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_wcstou64,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_wcstou64,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_wcstou64,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#else /* LIBC: wcstou64 */
#include <local/wchar/wcstou64.h>
#define __localdep_wcstou64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))
#endif /* wcstou64... */
#endif /* !____localdep_wcstou64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcstoumax) __ATTR_PURE __ATTR_NONNULL((1)) __UINTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstoumax))(__WCHAR_TYPE__ const *__restrict __nptr,
                                                       __WCHAR_TYPE__ **__endptr,
                                                       int __base) {
#line 509 "kos/src/libc/magic/inttypes.c"
#if __SIZEOF_INTMAX_T__ <= 4
	return (__UINTMAX_TYPE__)__localdep_wcstou32(__nptr, __endptr, __base);
#else /* __SIZEOF_INTMAX_T__ <= 4 */
	return (__UINTMAX_TYPE__)__localdep_wcstou64(__nptr, __endptr, __base);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcstoumax_defined */
