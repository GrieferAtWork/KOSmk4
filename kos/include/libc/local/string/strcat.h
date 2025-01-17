/* HASH CRC-32:0xa2780b6c */
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
#ifndef __local_strcat_defined
#define __local_strcat_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(strcat) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strcat))(char *__restrict __dst, char const *__restrict __src) {
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)((__NAMESPACE_LOCAL_SYM __localdep_strend)(__dst), __src, ((__NAMESPACE_LOCAL_SYM __localdep_strlen)(__src) + 1) * sizeof(char));
	return __dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strcat_defined
#define __local___localdep_strcat_defined
#define __localdep_strcat __LIBC_LOCAL_NAME(strcat)
#endif /* !__local___localdep_strcat_defined */
#endif /* !__local_strcat_defined */
