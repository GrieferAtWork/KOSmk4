/* HASH CRC-32:0x25d38b12 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32nlen_defined
#define __local_c32nlen_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32nend_defined
#define __local___localdep_c32nend_defined
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32nend,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnend)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32nend,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32nend __NAMESPACE_LOCAL_TYPEHAX(__CHAR32_TYPE__ *(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__),__CHAR32_TYPE__ *(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__),wcsnend)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32nend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32nend __LIBC_LOCAL_NAME(c32nend)
#endif /* !... */
#endif /* !__local___localdep_c32nend_defined */
__LOCAL_LIBC(c32nlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32nlen))(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen) {
	return (__SIZE_TYPE__)((__NAMESPACE_LOCAL_SYM __localdep_c32nend)(__str, __maxlen) - __str);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32nlen_defined
#define __local___localdep_c32nlen_defined
#define __localdep_c32nlen __LIBC_LOCAL_NAME(c32nlen)
#endif /* !__local___localdep_c32nlen_defined */
#endif /* !__local_c32nlen_defined */
