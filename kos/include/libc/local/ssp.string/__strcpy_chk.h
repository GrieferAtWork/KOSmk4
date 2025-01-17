/* HASH CRC-32:0xbb2c926a */
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
#ifndef __local___strcpy_chk_defined
#define __local___strcpy_chk_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strcpy_defined
#define __local___localdep_strcpy_defined
#if __has_builtin(__builtin_strcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_strcpy,(char *__restrict __dst, char const *__restrict __src),strcpy,{ return __builtin_strcpy(__dst, __src); })
#elif defined(__CRT_HAVE_strcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_strcpy,(char *__restrict __dst, char const *__restrict __src),strcpy,(__dst,__src))
#elif defined(__CRT_HAVE__mbscpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_strcpy,(char *__restrict __dst, char const *__restrict __src),_mbscpy,(__dst,__src))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcpy __LIBC_LOCAL_NAME(strcpy)
#endif /* !... */
#endif /* !__local___localdep_strcpy_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__strcpy_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__strcpy_chk))(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize) {
	(void)__dst_objsize; /* TODO */;
	return (__NAMESPACE_LOCAL_SYM __localdep_strcpy)(__dst, __src);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___strcpy_chk_defined
#define __local___localdep___strcpy_chk_defined
#define __localdep___strcpy_chk __LIBC_LOCAL_NAME(__strcpy_chk)
#endif /* !__local___localdep___strcpy_chk_defined */
#endif /* !__local___strcpy_chk_defined */
