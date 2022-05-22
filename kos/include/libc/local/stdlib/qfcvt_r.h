/* HASH CRC-32:0x596b208b */
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
#ifndef __local_qfcvt_r_defined
#define __local_qfcvt_r_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_dos_fcvt_s_defined) && defined(__CRT_HAVE__fcvt_s)
#define __local___localdep_dos_fcvt_s_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(5) __ATTR_OUT(6) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,__localdep_dos_fcvt_s,(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign),_fcvt_s,(__buf,__buflen,__val,__ndigit,__decptr,__sign))
#endif /* !__local___localdep_dos_fcvt_s_defined && __CRT_HAVE__fcvt_s */
__LOCAL_LIBC(qfcvt_r) __ATTR_OUT(3) __ATTR_OUT(4) __ATTR_OUTS(5, 6) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(qfcvt_r))(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len) {
#if defined(__CRT_HAVE__fcvt_s) && !defined(__BUILDING_LIBC)
	return (__NAMESPACE_LOCAL_SYM __localdep_dos_fcvt_s)(__buf, __len, (double)__val, __ndigit, __decptr, __sign) ? -1 : 0;
#else
	/* TODO: Implementation */
	(void)__val;
	(void)__ndigit;
	(void)__decptr;
	(void)__sign;
	(void)__buf;
	(void)__len;
	__COMPILER_IMPURE();
	return 0;
#endif
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_qfcvt_r_defined
#define __local___localdep_qfcvt_r_defined
#define __localdep_qfcvt_r __LIBC_LOCAL_NAME(qfcvt_r)
#endif /* !__local___localdep_qfcvt_r_defined */
#endif /* !__local_qfcvt_r_defined */
