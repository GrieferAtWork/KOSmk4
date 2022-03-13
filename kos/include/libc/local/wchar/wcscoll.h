/* HASH CRC-32:0x988ceee2 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcscoll_defined
#define __local_wcscoll_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcscmp_defined
#define __local___localdep_wcscmp_defined
#ifdef __CRT_HAVE_wcscmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#else /* __CRT_HAVE_wcscmp */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcscmp __LIBC_LOCAL_NAME(wcscmp)
#endif /* !__CRT_HAVE_wcscmp */
#endif /* !__local___localdep_wcscmp_defined */
__LOCAL_LIBC(wcscoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscoll))(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2) {
	/* XXX: Implement properly? */
	return (__NAMESPACE_LOCAL_SYM __localdep_wcscmp)(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcscoll_defined
#define __local___localdep_wcscoll_defined
#define __localdep_wcscoll __LIBC_LOCAL_NAME(wcscoll)
#endif /* !__local___localdep_wcscoll_defined */
#endif /* !__local_wcscoll_defined */
