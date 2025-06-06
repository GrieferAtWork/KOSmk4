/* HASH CRC-32:0x69934ea4 */
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
#ifndef __local_c32stoul_l_defined
#define __local_c32stoul_l_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32stoul_defined
#define __local___localdep_c32stoul_defined
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoul)
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG__ == 4 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou32) && __SIZEOF_LONG__ == 4
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstou64) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG__ == 8 && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$_wcstoui64) && __SIZEOF_LONG__ == 8
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_KOS$wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT_KOS(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,__localdep_c32stoul,(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstoul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stoul __NAMESPACE_LOCAL_TYPEHAX(unsigned long(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T),unsigned long(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__CHAR32_TYPE__ **,__STDC_INT_AS_UINT_T),wcstoul)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wchar/c32stoul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32stoul __LIBC_LOCAL_NAME(c32stoul)
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_c32stoul_defined */
__LOCAL_LIBC(c32stoul_l) __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32stoul_l))(__CHAR32_TYPE__ const *__restrict __nptr, __CHAR32_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_c32stoul)(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32stoul_l_defined
#define __local___localdep_c32stoul_l_defined
#define __localdep_c32stoul_l __LIBC_LOCAL_NAME(c32stoul_l)
#endif /* !__local___localdep_c32stoul_l_defined */
#endif /* !__local_c32stoul_l_defined */
