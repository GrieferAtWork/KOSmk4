/* HASH CRC-32:0x479f7dfd */
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
#ifndef __local_c16sncoll_defined
#define __local_c16sncoll_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16sncmp from parts.uchar.string */
#ifndef __local___localdep_c16sncmp_defined
#define __local___localdep_c16sncmp_defined 1
#if defined(__CRT_HAVE_wcsncmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16sncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16sncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsncmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
#define __localdep_c16sncmp (*(int(__LIBDCALL *)(__CHAR16_TYPE__ const *, __CHAR16_TYPE__ const *, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsncmp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16sncmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
#define __localdep_c16sncmp __LIBC_LOCAL_NAME(c16sncmp)
#endif /* !... */
#endif /* !__local___localdep_c16sncmp_defined */
__LOCAL_LIBC(c16sncoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16sncoll))(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen) {
	return __localdep_c16sncmp(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16sncoll_defined
#define __local___localdep_c16sncoll_defined 1
#define __localdep_c16sncoll __LIBC_LOCAL_NAME(c16sncoll)
#endif /* !__local___localdep_c16sncoll_defined */
#endif /* !__local_c16sncoll_defined */
