/* HASH CRC-32:0x256bcc81 */
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
#ifndef __local_c16ncasecoll_defined
#define __local_c16ncasecoll_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16ncasecmp from parts.uchar.string */
#ifndef __local___localdep_c16ncasecmp_defined
#define __local___localdep_c16ncasecmp_defined 1
#if defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,__localdep_c16ncasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16ncasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,__localdep_c16ncasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$_wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16ncasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__LIBDCALL,__localdep_c16ncasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16ncasecmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsncasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16ncasecmp (*(int(__LIBDCALL *)(__CHAR16_TYPE__ const *, __CHAR16_TYPE__ const *, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsncasecmp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16ncasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16ncasecmp __LIBC_LOCAL_NAME(c16ncasecmp)
#endif /* !... */
#endif /* !__local___localdep_c16ncasecmp_defined */
__LOCAL_LIBC(c16ncasecoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16ncasecoll))(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen) {
	return __localdep_c16ncasecmp(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16ncasecoll_defined
#define __local___localdep_c16ncasecoll_defined 1
#define __localdep_c16ncasecoll __LIBC_LOCAL_NAME(c16ncasecoll)
#endif /* !__local___localdep_c16ncasecoll_defined */
#endif /* !__local_c16ncasecoll_defined */
