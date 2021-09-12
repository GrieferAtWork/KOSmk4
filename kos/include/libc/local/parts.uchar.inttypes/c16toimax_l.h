/* HASH CRC-32:0x2974fc42 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16toimax_l_defined
#define __local_c16toimax_l_defined 1
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16toimax_defined
#define __local___localdep_c16toimax_defined 1
#if defined(__CRT_HAVE_wcstoimax) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoimax)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcstoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$_wcstoi64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_DOS$wcsto32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_c16toimax,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8 && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16toimax __NAMESPACE_LOCAL_TYPEHAX(__INTMAX_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),__INTMAX_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),wcsto64)
#elif __SIZEOF_INTMAX_T__ == 4 && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16toimax __NAMESPACE_LOCAL_TYPEHAX(__INTMAX_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),__INTMAX_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),wcsto32)
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/inttypes/wcstoimax.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16toimax __NAMESPACE_LOCAL_TYPEHAX(__INTMAX_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),__INTMAX_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T),wcstoimax)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.inttypes/c16toimax.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16toimax __LIBC_LOCAL_NAME(c16toimax)
#endif /* !... */
#endif /* !__local___localdep_c16toimax_defined */
__LOCAL_LIBC(c16toimax_l) __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16toimax_l))(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) {
	(void)__locale;
	return __NAMESPACE_LOCAL_SYM __localdep_c16toimax(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16toimax_l_defined
#define __local___localdep_c16toimax_l_defined 1
#define __localdep_c16toimax_l __LIBC_LOCAL_NAME(c16toimax_l)
#endif /* !__local___localdep_c16toimax_l_defined */
#endif /* !__local_c16toimax_l_defined */
