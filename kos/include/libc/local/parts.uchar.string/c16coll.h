/* HASH CRC-32:0xb6127897 */
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
#ifndef __local_c16coll_defined
#define __local_c16coll_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16cmp_defined
#define __local___localdep_c16cmp_defined
#if defined(__CRT_HAVE_wcscmp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16cmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif defined(__CRT_HAVE_DOS$wcscmp)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16cmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2),wcscmp,(__s1,__s2))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16cmp __NAMESPACE_LOCAL_TYPEHAX(int(__LIBDCALL*)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *),int(__LIBDCALL&)(__CHAR16_TYPE__ const *,__CHAR16_TYPE__ const *),wcscmp)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16cmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16cmp __LIBC_LOCAL_NAME(c16cmp)
#endif /* !... */
#endif /* !__local___localdep_c16cmp_defined */
__LOCAL_LIBC(c16coll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16coll))(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2) {
	return (__NAMESPACE_LOCAL_SYM __localdep_c16cmp)(__s1, __s2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16coll_defined
#define __local___localdep_c16coll_defined
#define __localdep_c16coll __LIBC_LOCAL_NAME(c16coll)
#endif /* !__local___localdep_c16coll_defined */
#endif /* !__local_c16coll_defined */
