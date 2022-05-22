/* HASH CRC-32:0xd97c5f78 */
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
#ifndef __local__c16asctime_defined
#define __local__c16asctime_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__c16asctime_s_defined
#define __local___localdep__c16asctime_s_defined
#if defined(__CRT_HAVE__wasctime_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_IN(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,__localdep__c16asctime_s,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __buflen, struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime_s,(__buf,__buflen,__tp))
#elif defined(__CRT_HAVE_DOS$_wasctime_s)
__CREDIRECT_DOS(__ATTR_IN(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,__localdep__c16asctime_s,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __buflen, struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime_s,(__buf,__buflen,__tp))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wtime/_wasctime_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__c16asctime_s __NAMESPACE_LOCAL_TYPEHAX(__errno_t(__LIBDCALL*)(__CHAR16_TYPE__ *,__SIZE_TYPE__,struct __NAMESPACE_STD_SYM tm const *),__errno_t(__LIBDCALL&)(__CHAR16_TYPE__ *,__SIZE_TYPE__,struct __NAMESPACE_STD_SYM tm const *),_wasctime_s)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.time/_c16asctime_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__c16asctime_s __LIBC_LOCAL_NAME(_c16asctime_s)
#endif /* !... */
#endif /* !__local___localdep__c16asctime_s_defined */
__LOCAL_LIBC(_c16asctime) __ATTR_WUNUSED __ATTR_IN(1) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_c16asctime))(struct __NAMESPACE_STD_SYM tm const *__tp) {
	static __CHAR16_TYPE__ __wasctime_retbuf[26] = { 0 };
	return (__NAMESPACE_LOCAL_SYM __localdep__c16asctime_s)(__wasctime_retbuf, 26, __tp) ? __NULLPTR : __wasctime_retbuf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__c16asctime_defined
#define __local___localdep__c16asctime_defined
#define __localdep__c16asctime __LIBC_LOCAL_NAME(_c16asctime)
#endif /* !__local___localdep__c16asctime_defined */
#endif /* !__local__c16asctime_defined */
