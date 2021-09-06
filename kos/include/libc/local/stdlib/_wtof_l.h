/* HASH CRC-32:0x783a18ac */
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
#ifndef __local__wtof_l_defined
#define __local__wtof_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstod_l_defined
#define __local___localdep_wcstod_l_defined 1
#ifdef __CRT_HAVE_wcstod_l
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,__localdep_wcstod_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,__localdep_wcstod_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,__localdep_wcstod_l,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstod_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstod_l __LIBC_LOCAL_NAME(wcstod_l)
#endif /* !... */
#endif /* !__local___localdep_wcstod_l_defined */
__LOCAL_LIBC(_wtof_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wtof_l))(__WCHAR_TYPE__ const *__nptr, __locale_t __locale) {
	return __localdep_wcstod_l(__nptr, __NULLPTR, __locale);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wtof_l_defined
#define __local___localdep__wtof_l_defined 1
#define __localdep__wtof_l __LIBC_LOCAL_NAME(_wtof_l)
#endif /* !__local___localdep__wtof_l_defined */
#endif /* !__local__wtof_l_defined */
