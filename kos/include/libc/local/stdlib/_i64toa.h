/* HASH CRC-32:0x64d848dd */
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
#ifndef __local__i64toa_defined
#define __local__i64toa_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__i64toa_s_defined
#define __local___localdep__i64toa_s_defined
#ifdef __CRT_HAVE__i64toa_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,__localdep__i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_i64toa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__ltoa_s) && __SIZEOF_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,__localdep__i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ltoa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__itoa_s) && __SIZEOF_INT__ == 8
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,__localdep__i64toa_s,(__INT64_TYPE__ __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_itoa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_i64toa_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__i64toa_s __LIBC_LOCAL_NAME(_i64toa_s)
#endif /* !... */
#endif /* !__local___localdep__i64toa_s_defined */
__LOCAL_LIBC(_i64toa) __ATTR_OUT(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_i64toa))(__INT64_TYPE__ __val, char *__buf, int __radix) {
	(__NAMESPACE_LOCAL_SYM __localdep__i64toa_s)(__val, __buf, (__SIZE_TYPE__)-1, __radix);
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__i64toa_defined
#define __local___localdep__i64toa_defined
#define __localdep__i64toa __LIBC_LOCAL_NAME(_i64toa)
#endif /* !__local___localdep__i64toa_defined */
#endif /* !__local__i64toa_defined */
