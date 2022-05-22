/* HASH CRC-32:0x243d6d69 */
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
#ifndef __local_ultoa_defined
#define __local_ultoa_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ultoa_s_defined
#define __local___localdep__ultoa_s_defined
#ifdef __CRT_HAVE__ultoa_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__errno_t,__NOTHROW_NCX,__localdep__ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ultoa_s,(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ultoa_s */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE__ui64toa_s) && __SIZEOF_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__errno_t,__NOTHROW_NCX,__localdep__ultoa_s,(unsigned long __val, char *__buf, __SIZE_TYPE__ __buflen, int __radix),_ui64toa_s,(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ui64toa_s && __SIZEOF_LONG__ == 8 */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_ultoa_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ultoa_s __LIBC_LOCAL_NAME(_ultoa_s)
#endif /* !__CRT_HAVE__ui64toa_s || __SIZEOF_LONG__ != 8 */
#endif /* !__CRT_HAVE__ultoa_s */
#endif /* !__local___localdep__ultoa_s_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ultoa) __ATTR_ACCESS_WR(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ultoa))(unsigned long __val, char *__buf, int __radix) {
	(__NAMESPACE_LOCAL_SYM __localdep__ultoa_s)(__val, __buf, (__SIZE_TYPE__)-1, __radix);
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ultoa_defined
#define __local___localdep_ultoa_defined
#define __localdep_ultoa __LIBC_LOCAL_NAME(ultoa)
#endif /* !__local___localdep_ultoa_defined */
#endif /* !__local_ultoa_defined */
