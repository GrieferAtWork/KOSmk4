/* HASH CRC-32:0x45691815 */
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
#ifndef __local___strncpy_chk_defined
#define __local___strncpy_chk_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strncpy_defined
#define __local___localdep_strncpy_defined 1
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,{ return __builtin_strncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_strncpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strncpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strncpy __LIBC_LOCAL_NAME(strncpy)
#endif /* !... */
#endif /* !__local___localdep_strncpy_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__strncpy_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__strncpy_chk))(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __buflen, __SIZE_TYPE__ __dst_objsize) {
	(void)__dst_objsize; /* TODO */;
	return __localdep_strncpy(__dst, __src, __buflen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___strncpy_chk_defined
#define __local___localdep___strncpy_chk_defined 1
#define __localdep___strncpy_chk __LIBC_LOCAL_NAME(__strncpy_chk)
#endif /* !__local___localdep___strncpy_chk_defined */
#endif /* !__local___strncpy_chk_defined */
