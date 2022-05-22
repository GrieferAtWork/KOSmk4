/* HASH CRC-32:0xde0408be */
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
#ifndef __local__c16ctime64_s_defined
#define __local__c16ctime64_s_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ctime64_r_defined
#define __local___localdep_ctime64_r_defined
#if defined(__CRT_HAVE_ctime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),char *,__NOTHROW_NCX,__localdep_ctime64_r,(__time64_t const *__restrict __timer, char __buf[26]),ctime_r,(__timer,__buf))
#elif defined(__CRT_HAVE_ctime64_r)
__NAMESPACE_LOCAL_END
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(2),char *,__NOTHROW_NCX,__localdep_ctime64_r,(__time64_t const *__restrict __timer, char __buf[26]),ctime64_r,(__timer,__buf))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/ctime64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ctime64_r __LIBC_LOCAL_NAME(ctime64_r)
#endif /* !... */
#endif /* !__local___localdep_ctime64_r_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_c16ctime64_s) __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) __errno_t
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_c16ctime64_s))(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __time64_t const *__timer) {
	char __abuf[26], *__ptr;
	unsigned int __i;
	if __unlikely(__buflen < 26)
		return __ERANGE;
	__ptr = (__NAMESPACE_LOCAL_SYM __localdep_ctime64_r)(__timer, __abuf);

	if __unlikely(!__ptr)
		return __libc_geterrno_or(1);

	for (__i = 0; __i < 26; ++__i)
		__buf[__i] = (__CHAR16_TYPE__)__ptr[__i]; /* Guarantied no unicode in here! */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__c16ctime64_s_defined
#define __local___localdep__c16ctime64_s_defined
#define __localdep__c16ctime64_s __LIBC_LOCAL_NAME(_c16ctime64_s)
#endif /* !__local___localdep__c16ctime64_s_defined */
#endif /* !__local__c16ctime64_s_defined */
