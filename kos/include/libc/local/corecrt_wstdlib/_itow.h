/* HASH CRC-32:0xce60f6bd */
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
#ifndef __local__itow_defined
#define __local__itow_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__itow_s_defined
#define __local___localdep__itow_s_defined
#ifdef __CRT_HAVE__itow_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_NCX,__localdep__itow_s,(int __val, __WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, int __radix),_itow_s,(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__itow_s */
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wstdlib/_itow_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__itow_s __LIBC_LOCAL_NAME(_itow_s)
#endif /* !__CRT_HAVE__itow_s */
#endif /* !__local___localdep__itow_s_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_itow) __ATTR_OUT(2) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_itow))(int __val, __WCHAR_TYPE__ *__buf, int __radix) {
	(__NAMESPACE_LOCAL_SYM __localdep__itow_s)(__val, __buf, (__SIZE_TYPE__)-1, __radix);
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__itow_defined
#define __local___localdep__itow_defined
#define __localdep__itow __LIBC_LOCAL_NAME(_itow)
#endif /* !__local___localdep__itow_defined */
#endif /* !__local__itow_defined */
