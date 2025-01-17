/* HASH CRC-32:0x838cf936 */
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
#ifndef __local_c16casecoll_l_defined
#define __local_c16casecoll_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16casecoll_defined
#define __local___localdep_c16casecoll_defined
#if defined(__CRT_HAVE_wcscasecoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicoll)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscasecmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$_wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcsicmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_c16casecoll,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcsicmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscasecoll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16casecoll __NAMESPACE_LOCAL_TYPEHAX(int(__LIBDCALL*)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *),int(__LIBDCALL&)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *),wcscasecoll)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16casecoll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16casecoll __LIBC_LOCAL_NAME(c16casecoll)
#endif /* !... */
#endif /* !__local___localdep_c16casecoll_defined */
__LOCAL_LIBC(c16casecoll_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16casecoll_l))(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __locale_t __locale) {
	/* XXX: Implement properly? */
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_c16casecoll)(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16casecoll_l_defined
#define __local___localdep_c16casecoll_l_defined
#define __localdep_c16casecoll_l __LIBC_LOCAL_NAME(c16casecoll_l)
#endif /* !__local___localdep_c16casecoll_l_defined */
#endif /* !__local_c16casecoll_l_defined */
