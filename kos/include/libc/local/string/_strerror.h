/* HASH CRC-32:0x665bf221 */
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
#ifndef __local__strerror_defined
#define __local__strerror_defined
#include <__crt.h>
#include <libc/errno.h>
#if defined(__CRT_HAVE__strerror_s) || defined(__libc_geterrno)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__strerror_s_defined
#define __local___localdep__strerror_s_defined
#ifdef __CRT_HAVE__strerror_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_RPC,__localdep__strerror_s,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__message),_strerror_s,(__buf,__buflen,__message))
#elif defined(__libc_geterrno)
__NAMESPACE_LOCAL_END
#include <libc/local/string/_strerror_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__strerror_s __LIBC_LOCAL_NAME(_strerror_s)
#else /* ... */
#undef __local___localdep__strerror_s_defined
#endif /* !... */
#endif /* !__local___localdep__strerror_s_defined */
__LOCAL_LIBC(_strerror) __ATTR_WUNUSED __ATTR_IN_OPT(1) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_strerror))(char const *__message) {
	static char __strerror_buf[64];
	if ((__NAMESPACE_LOCAL_SYM __localdep__strerror_s)(__strerror_buf,
	                __COMPILER_LENOF(__strerror_buf),
	                __message))
		return __NULLPTR;
	return __strerror_buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__strerror_defined
#define __local___localdep__strerror_defined
#define __localdep__strerror __LIBC_LOCAL_NAME(_strerror)
#endif /* !__local___localdep__strerror_defined */
#else /* __CRT_HAVE__strerror_s || __libc_geterrno */
#undef __local__strerror_defined
#endif /* !__CRT_HAVE__strerror_s && !__libc_geterrno */
#endif /* !__local__strerror_defined */
