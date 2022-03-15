/* HASH CRC-32:0xee7dbb4b */
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
#ifndef __local__c16ctime32_defined
#define __local__c16ctime32_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__c16ctime64_defined
#define __local___localdep__c16ctime64_defined
#if defined(__CRT_HAVE__wctime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep__c16ctime64,(__time64_t const *__timer),_wctime64,(__timer))
#elif defined(__CRT_HAVE_DOS$_wctime64)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep__c16ctime64,(__time64_t const *__timer),_wctime64,(__timer))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wtime/_wctime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__c16ctime64 __NAMESPACE_LOCAL_TYPEHAX(__CHAR16_TYPE__ *(__LIBDCALL*)(__time64_t const *),__CHAR16_TYPE__ *(__LIBDCALL&)(__time64_t const *),_wctime64)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.time/_c16ctime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__c16ctime64 __LIBC_LOCAL_NAME(_c16ctime64)
#endif /* !... */
#endif /* !__local___localdep__c16ctime64_defined */
__LOCAL_LIBC(_c16ctime32) __ATTR_WUNUSED __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_c16ctime32))(__time32_t const *__timer) {
	__time64_t __timer64 = (__time64_t)*__timer;
	return (__NAMESPACE_LOCAL_SYM __localdep__c16ctime64)(&__timer64);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__c16ctime32_defined
#define __local___localdep__c16ctime32_defined
#define __localdep__c16ctime32 __LIBC_LOCAL_NAME(_c16ctime32)
#endif /* !__local___localdep__c16ctime32_defined */
#endif /* !__local__c16ctime32_defined */
