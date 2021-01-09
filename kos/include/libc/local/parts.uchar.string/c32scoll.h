/* HASH CRC-32:0x34d426bf */
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
#ifndef __local_c32scoll_defined
#define __local_c32scoll_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32scmp from parts.uchar.string */
#ifndef __local___localdep_c32scmp_defined
#define __local___localdep_c32scmp_defined 1
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32scmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_KOS$wcscmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32scmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_c32scmp (*(int(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__ const *))&__LIBC_LOCAL_NAME(wcscmp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32scmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_c32scmp __LIBC_LOCAL_NAME(c32scmp)
#endif /* !... */
#endif /* !__local___localdep_c32scmp_defined */
__LOCAL_LIBC(c32scoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32scoll))(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2) {
	return __localdep_c32scmp(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32scoll_defined
#define __local___localdep_c32scoll_defined 1
#define __localdep_c32scoll __LIBC_LOCAL_NAME(c32scoll)
#endif /* !__local___localdep_c32scoll_defined */
#endif /* !__local_c32scoll_defined */
