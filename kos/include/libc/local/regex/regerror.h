/* HASH CRC-32:0x591ff2ee */
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
#ifndef __local_regerror_defined
#define __local_regerror_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/regex.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_regerrordesc_np_defined
#define __local___localdep_regerrordesc_np_defined
#ifdef __CRT_HAVE_regerrordesc_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__localdep_regerrordesc_np,(int __errcode),regerrordesc_np,(__errcode))
#else /* __CRT_HAVE_regerrordesc_np */
__NAMESPACE_LOCAL_END
#include <libc/local/regex/regerrordesc_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_regerrordesc_np __LIBC_LOCAL_NAME(regerrordesc_np)
#endif /* !__CRT_HAVE_regerrordesc_np */
#endif /* !__local___localdep_regerrordesc_np_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(regerror) __ATTR_IN(2) __ATTR_OUTS(3, 4) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(regerror))(int __errcode, struct re_pattern_buffer const *__restrict __self, char *__restrict __errbuf, __SIZE_TYPE__ __errbuf_size) {
	char const *__msg;
	__SIZE_TYPE__ __msglen;
	(void)__self;
	__msg = (__NAMESPACE_LOCAL_SYM __localdep_regerrordesc_np)(__errcode);
	if __unlikely(!__msg)
		__msg = "?";
	__msglen = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__msg);
	if (__errbuf_size > (__msglen + 1))
		__errbuf_size = (__msglen + 1);
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__errbuf, __msg, __errbuf_size);
	return __msglen;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_regerror_defined
#define __local___localdep_regerror_defined
#define __localdep_regerror __LIBC_LOCAL_NAME(regerror)
#endif /* !__local___localdep_regerror_defined */
#endif /* !__local_regerror_defined */
