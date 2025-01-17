/* HASH CRC-32:0x5e10def3 */
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
#ifndef __local_wcscasecoll_l_defined
#define __local_wcscasecoll_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcscasecoll_defined
#define __local___localdep_wcscasecoll_defined
#ifdef __CRT_HAVE_wcscasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_wcscasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_wcscasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_wcscasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_wcscasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_wcscasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_wcscasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscasecoll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcscasecoll __LIBC_LOCAL_NAME(wcscasecoll)
#endif /* !... */
#endif /* !__local___localdep_wcscasecoll_defined */
__LOCAL_LIBC(wcscasecoll_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscasecoll_l))(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __locale_t __locale) {
	/* XXX: Implement properly? */
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_wcscasecoll)(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcscasecoll_l_defined
#define __local___localdep_wcscasecoll_l_defined
#define __localdep_wcscasecoll_l __LIBC_LOCAL_NAME(wcscasecoll_l)
#endif /* !__local___localdep_wcscasecoll_l_defined */
#endif /* !__local_wcscasecoll_l_defined */
