/* HASH CRC-32:0xf0890020 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_qfcvt_defined
#define __local_qfcvt_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_qfcvt_r_defined
#define __local___localdep_qfcvt_r_defined 1
#ifdef __CRT_HAVE_qfcvt_r
__CREDIRECT(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,__localdep_qfcvt_r,(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),qfcvt_r,(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_qfcvt_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/qfcvt_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_qfcvt_r __LIBC_LOCAL_NAME(qfcvt_r)
#endif /* !__CRT_HAVE_qfcvt_r */
#endif /* !__local___localdep_qfcvt_r_defined */
__LOCAL_LIBC(qfcvt) __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(qfcvt))(__LONGDOUBLE __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) {

	static char __qcvt_buffer[32];

	if ((__NAMESPACE_LOCAL_SYM __localdep_qfcvt_r)(__val, __ndigit, __decptr, __sign, __qcvt_buffer, sizeof(__qcvt_buffer)))
		return __NULLPTR;
	return __qcvt_buffer;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_qfcvt_defined
#define __local___localdep_qfcvt_defined 1
#define __localdep_qfcvt __LIBC_LOCAL_NAME(qfcvt)
#endif /* !__local___localdep_qfcvt_defined */
#endif /* !__local_qfcvt_defined */
