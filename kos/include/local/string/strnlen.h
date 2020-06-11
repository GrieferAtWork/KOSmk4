/* HASH CRC-32:0x8ba1da27 */
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
#ifndef __local_strnlen_defined
#define __local_strnlen_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strnend from string */
#ifndef __local___localdep_strnend_defined
#define __local___localdep_strnend_defined 1
#ifdef __CRT_HAVE_strnend
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strnend,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnend,(__string,__maxlen))
#else /* __CRT_HAVE_strnend */
__NAMESPACE_LOCAL_END
#include <local/string/strnend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
#define __localdep_strnend __LIBC_LOCAL_NAME(strnend)
#endif /* !__CRT_HAVE_strnend */
#endif /* !__local___localdep_strnend_defined */
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__LOCAL_LIBC(strnlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnlen))(char const *__restrict __string, __SIZE_TYPE__ __maxlen) {
	return (__SIZE_TYPE__)(__localdep_strnend(__string, __maxlen) - __string);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strnlen_defined
#define __local___localdep_strnlen_defined 1
#define __localdep_strnlen __LIBC_LOCAL_NAME(strnlen)
#endif /* !__local___localdep_strnlen_defined */
#endif /* !__local_strnlen_defined */
