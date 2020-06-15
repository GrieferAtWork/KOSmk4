/* HASH CRC-32:0xe4c387f4 */
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
#ifndef __local__ui64tow_defined
#define __local__ui64tow_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _ui64tow_s from stdlib */
#ifndef __local___localdep__ui64tow_s_defined
#define __local___localdep__ui64tow_s_defined 1
#ifdef __CRT_HAVE__ui64tow_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),__errno_t,__NOTHROW_NCX,__localdep__ui64tow_s,(__UINT64_TYPE__ __val, __WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, int __radix),_ui64tow_s,(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ui64tow_s */
__NAMESPACE_LOCAL_END
#include <local/stdlib/_ui64tow_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ui64tow_s __LIBC_LOCAL_NAME(_ui64tow_s)
#endif /* !__CRT_HAVE__ui64tow_s */
#endif /* !__local___localdep__ui64tow_s_defined */
__LOCAL_LIBC(_ui64tow) __ATTR_NONNULL((2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ui64tow))(__UINT64_TYPE__ __val, __WCHAR_TYPE__ *__buf, int __radix) {
	__localdep__ui64tow_s(__val, __buf, (__SIZE_TYPE__)-1, __radix);
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ui64tow_defined
#define __local___localdep__ui64tow_defined 1
#define __localdep__ui64tow __LIBC_LOCAL_NAME(_ui64tow)
#endif /* !__local___localdep__ui64tow_defined */
#endif /* !__local__ui64tow_defined */
