/* HASH CRC-32:0x9334db43 */
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
#ifndef __local_wcstoimax_l_defined
#define __local_wcstoimax_l_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcstoimax from inttypes */
#ifndef __local___localdep_wcstoimax_defined
#define __local___localdep_wcstoimax_defined 1
#ifdef __CRT_HAVE_wcstoimax
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_wcstoimax,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstoimax (*(__INTMAX_TYPE__(__LIBCCALL *)(__WCHAR_TYPE__ const *__restrict, __WCHAR_TYPE__ **, __STDC_INT_AS_UINT_T))&__LIBC_LOCAL_NAME(wcsto64))
#elif __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstoimax (*(__INTMAX_TYPE__(__LIBCCALL *)(__WCHAR_TYPE__ const *__restrict, __WCHAR_TYPE__ **, __STDC_INT_AS_UINT_T))&__LIBC_LOCAL_NAME(wcsto32))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/inttypes/wcstoimax.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstoimax __LIBC_LOCAL_NAME(wcstoimax)
#endif /* !... */
#endif /* !__local___localdep_wcstoimax_defined */
__LOCAL_LIBC(wcstoimax_l) __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstoimax_l))(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) {
	(void)__locale;
	return __localdep_wcstoimax(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcstoimax_l_defined
#define __local___localdep_wcstoimax_l_defined 1
#define __localdep_wcstoimax_l __LIBC_LOCAL_NAME(wcstoimax_l)
#endif /* !__local___localdep_wcstoimax_l_defined */
#endif /* !__local_wcstoimax_l_defined */
