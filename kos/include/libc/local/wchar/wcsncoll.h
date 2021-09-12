/* HASH CRC-32:0xdae033e0 */
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
#ifndef __local_wcsncoll_defined
#define __local_wcsncoll_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcsncmp_defined
#define __local___localdep_wcsncmp_defined 1
#ifdef __CRT_HAVE_wcsncmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#else /* __CRT_HAVE_wcsncmp */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsncmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsncmp __LIBC_LOCAL_NAME(wcsncmp)
#endif /* !__CRT_HAVE_wcsncmp */
#endif /* !__local___localdep_wcsncmp_defined */
__LOCAL_LIBC(wcsncoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsncoll))(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen) {
	return __NAMESPACE_LOCAL_SYM __localdep_wcsncmp(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsncoll_defined
#define __local___localdep_wcsncoll_defined 1
#define __localdep_wcsncoll __LIBC_LOCAL_NAME(wcsncoll)
#endif /* !__local___localdep_wcsncoll_defined */
#endif /* !__local_wcsncoll_defined */
