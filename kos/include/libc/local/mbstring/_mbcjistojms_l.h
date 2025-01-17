/* HASH CRC-32:0xbc3ffdba */
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
#ifndef __local__mbcjistojms_l_defined
#define __local__mbcjistojms_l_defined
#include <__crt.h>
#ifdef __CRT_HAVE__getmbcp
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__getmbcp_l_defined
#define __local___localdep__getmbcp_l_defined
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_getmbcp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__getmbcp_l __LIBC_LOCAL_NAME(_getmbcp_l)
#endif /* !__local___localdep__getmbcp_l_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbcjistojms_l) __ATTR_PURE __ATTR_WUNUSED unsigned int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbcjistojms_l))(unsigned int __ch, __locale_t __locale) {
	unsigned char __c1, __c2, __temp;
	/* Extrapolated from reverse engineering. */
	if ((__NAMESPACE_LOCAL_SYM __localdep__getmbcp_l)(__locale) != 932)
		return __ch;
	__c1 = __ch & 0xff;
	__c2 = __ch >> 8 & 0xff;
	if ((__c1 > 0x7e) || (__c1 < 0x21) ||
	    (__c2 > 0x7e) || (__c2 < 0x21)) {
#ifdef __EILSEQ
		__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
		return 0;
	}
	if (((__ch >> 8) & 1) == 0) {
		__c1 += 0x7e;
	} else {
		__c1 += __c1 < 0x60 ? 0x1f: 0x20;
	}
	__temp = (__c2 - 0x21) >> 1;
	__c2   = __temp + 0x81;
	if (__c2 > 0x9f)
		__c2 = __temp + 0xc1;
	return (__UINT16_TYPE__)__c2 << 8 | __c1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbcjistojms_l_defined
#define __local___localdep__mbcjistojms_l_defined
#define __localdep__mbcjistojms_l __LIBC_LOCAL_NAME(_mbcjistojms_l)
#endif /* !__local___localdep__mbcjistojms_l_defined */
#else /* __CRT_HAVE__getmbcp */
#undef __local__mbcjistojms_l_defined
#endif /* !__CRT_HAVE__getmbcp */
#endif /* !__local__mbcjistojms_l_defined */
