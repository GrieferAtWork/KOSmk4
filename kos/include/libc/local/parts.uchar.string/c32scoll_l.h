/* HASH CRC-32:0x4110f3ab */
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
#ifndef __local_c32scoll_l_defined
#define __local_c32scoll_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32scoll from parts.uchar.string */
#ifndef __local___localdep_c32scoll_defined
#define __local___localdep_c32scoll_defined 1
#if defined(__CRT_HAVE_wcscoll) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32scoll,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscoll,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscoll)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32scoll,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscoll,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscoll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32scoll (*(int(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__ const *))&__LIBC_LOCAL_NAME(wcscoll))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32scoll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32scoll __LIBC_LOCAL_NAME(c32scoll)
#endif /* !... */
#endif /* !__local___localdep_c32scoll_defined */
__LOCAL_LIBC(c32scoll_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32scoll_l))(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __locale_t __locale) {
	(void)__locale;
	return __localdep_c32scoll(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32scoll_l_defined
#define __local___localdep_c32scoll_l_defined 1
#define __localdep_c32scoll_l __LIBC_LOCAL_NAME(c32scoll_l)
#endif /* !__local___localdep_c32scoll_l_defined */
#endif /* !__local_c32scoll_l_defined */
