/* HASH CRC-32:0xa49edf2d */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32stoumax_l_defined
#define __local_c32stoumax_l_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32stou32_l_defined
#define __local___localdep_c32stou32_l_defined
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstou32_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_c32stou32_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstou32_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stou32_l __NAMESPACE_LOCAL_TYPEHAX(__UINT32_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T,__locale_t),__UINT32_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T,__locale_t),wcstou32_l)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdlib/c32stou32_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stou32_l __LIBC_LOCAL_NAME(c32stou32_l)
#endif /* !... */
#endif /* !__local___localdep_c32stou32_l_defined */
#ifndef __local___localdep_c32stou64_l_defined
#define __local___localdep_c32stou64_l_defined
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstou64_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoui64_l)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_KOS$_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_c32stou64_l,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstou64_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stou64_l __NAMESPACE_LOCAL_TYPEHAX(__UINT64_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T,__locale_t),__UINT64_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T,__locale_t),wcstou64_l)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdlib/c32stou64_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stou64_l __LIBC_LOCAL_NAME(c32stou64_l)
#endif /* !... */
#endif /* !__local___localdep_c32stou64_l_defined */
__LOCAL_LIBC(c32stoumax_l) __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINTMAX_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32stoumax_l))(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) {
#if __SIZEOF_INTMAX_T__ <= 4
	return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_c32stou32_l)(__nptr, __endptr, __base, __locale);
#else /* __SIZEOF_INTMAX_T__ <= 4 */
	return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_c32stou64_l)(__nptr, __endptr, __base, __locale);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32stoumax_l_defined
#define __local___localdep_c32stoumax_l_defined
#define __localdep_c32stoumax_l __LIBC_LOCAL_NAME(c32stoumax_l)
#endif /* !__local___localdep_c32stoumax_l_defined */
#endif /* !__local_c32stoumax_l_defined */
