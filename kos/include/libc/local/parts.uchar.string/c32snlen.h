/* HASH CRC-32:0x2adc0d97 */
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
#ifndef __local_c32snlen_defined
#define __local_c32snlen_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32snend from parts.uchar.string */
#ifndef __local___localdep_c32snend_defined
#define __local___localdep_c32snend_defined 1
#if defined(__CRT_HAVE_wcsnend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32snend,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnend)
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32snend,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
#define __localdep_c32snend (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsnend))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32snend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
#define __localdep_c32snend __LIBC_LOCAL_NAME(c32snend)
#endif /* !... */
#endif /* !__local___localdep_c32snend_defined */
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__LOCAL_LIBC(c32snlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32snlen))(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen) {
	return (__SIZE_TYPE__)(__localdep_c32snend(__string, __maxlen) - __string);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32snlen_defined
#define __local___localdep_c32snlen_defined 1
#define __localdep_c32snlen __LIBC_LOCAL_NAME(c32snlen)
#endif /* !__local___localdep_c32snlen_defined */
#endif /* !__local_c32snlen_defined */
