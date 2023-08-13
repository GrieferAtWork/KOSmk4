/* HASH CRC-32:0x5d65721f */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_qecvt_defined
#define __local_qecvt_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_qecvt_r_defined
#define __local___localdep_qecvt_r_defined
#ifdef __CRT_HAVE_qecvt_r
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(3) __ATTR_OUT(4) __ATTR_OUTS(5, 6),int,__NOTHROW_NCX,__localdep_qecvt_r,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),qecvt_r,(__val,__ndigit,__decptr,__sign,__buf,__len))
#elif defined(__CRT_HAVE_ecvt_r) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(3) __ATTR_OUT(4) __ATTR_OUTS(5, 6),int,__NOTHROW_NCX,__localdep_qecvt_r,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),ecvt_r,(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/qecvt_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_qecvt_r __LIBC_LOCAL_NAME(qecvt_r)
#endif /* !... */
#endif /* !__local___localdep_qecvt_r_defined */
__LOCAL_LIBC(qecvt) __ATTR_WUNUSED __ATTR_OUT(3) __ATTR_OUT(4) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(qecvt))(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) {
	static char __qcvt_buf[32] = {0};
	if ((__NAMESPACE_LOCAL_SYM __localdep_qecvt_r)(__val, __ndigit, __decptr, __sign,  __qcvt_buf, sizeof(__qcvt_buf)))
		return __NULLPTR;
	return __qcvt_buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_qecvt_defined
#define __local___localdep_qecvt_defined
#define __localdep_qecvt __LIBC_LOCAL_NAME(qecvt)
#endif /* !__local___localdep_qecvt_defined */
#endif /* !__local_qecvt_defined */
