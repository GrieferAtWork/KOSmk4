/* HASH CRC-32:0x82d402a1 */
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
#ifndef __local_c32len_defined
#define __local_c32len_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32end_defined
#define __local___localdep_c32end_defined
#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32end,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif defined(__CRT_HAVE_KOS$wcsend)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32end,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32end __NAMESPACE_LOCAL_TYPEHAX(__CHAR32_TYPE__ *(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict),__CHAR32_TYPE__ *(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict),wcsend)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32end.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32end __LIBC_LOCAL_NAME(c32end)
#endif /* !... */
#endif /* !__local___localdep_c32end_defined */
__LOCAL_LIBC(c32len) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32len))(__CHAR32_TYPE__ const *__restrict __str) {
	return (__SIZE_TYPE__)((__NAMESPACE_LOCAL_SYM __localdep_c32end)(__str) - __str);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32len_defined
#define __local___localdep_c32len_defined
#define __localdep_c32len __LIBC_LOCAL_NAME(c32len)
#endif /* !__local___localdep_c32len_defined */
#endif /* !__local_c32len_defined */
