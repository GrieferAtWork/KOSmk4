/* HASH CRC-32:0x39a4a468 */
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
#ifndef __local_itoa_defined
#define __local_itoa_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__itoa_s_defined
#define __local___localdep__itoa_s_defined
#ifdef __CRT_HAVE__itoa_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,__localdep__itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_itoa_s,(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__itoa_s */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE__ltoa_s) && __SIZEOF_INT__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,__localdep__itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ltoa_s,(__val,__buf,__buflen,__radix))
#elif defined(__CRT_HAVE__i64toa_s) && __SIZEOF_INT__ == 8
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,__localdep__itoa_s,(int __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_i64toa_s,(__val,__buf,__buflen,__radix))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_itoa_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__itoa_s __LIBC_LOCAL_NAME(_itoa_s)
#endif /* !... */
#endif /* !__CRT_HAVE__itoa_s */
#endif /* !__local___localdep__itoa_s_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(itoa) __ATTR_OUT(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(itoa))(int __val, char *__buf, int __radix) {
	(__NAMESPACE_LOCAL_SYM __localdep__itoa_s)(__val, __buf, (__SIZE_TYPE__)-1, __radix);
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_itoa_defined
#define __local___localdep_itoa_defined
#define __localdep_itoa __LIBC_LOCAL_NAME(itoa)
#endif /* !__local___localdep_itoa_defined */
#endif /* !__local_itoa_defined */
