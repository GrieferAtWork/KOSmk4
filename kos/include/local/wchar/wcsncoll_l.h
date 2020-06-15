/* HASH CRC-32:0xaa0b5de2 */
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
#ifndef __local_wcsncoll_l_defined
#define __local_wcsncoll_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcsncoll from wchar */
#ifndef __local___localdep_wcsncoll_defined
#define __local___localdep_wcsncoll_defined 1
#ifdef __CRT_HAVE_wcsncoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncoll,(__s1,__s2,__maxlen))
#else /* __CRT_HAVE_wcsncoll */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsncoll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsncoll __LIBC_LOCAL_NAME(wcsncoll)
#endif /* !__CRT_HAVE_wcsncoll */
#endif /* !__local___localdep_wcsncoll_defined */
__LOCAL_LIBC(wcsncoll_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsncoll_l))(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) {
	(void)__locale;
	return __localdep_wcsncoll(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsncoll_l_defined
#define __local___localdep_wcsncoll_l_defined 1
#define __localdep_wcsncoll_l __LIBC_LOCAL_NAME(wcsncoll_l)
#endif /* !__local___localdep_wcsncoll_l_defined */
#endif /* !__local_wcsncoll_l_defined */
