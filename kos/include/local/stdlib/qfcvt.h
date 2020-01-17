/* HASH CRC-32:0xe8f63987 */
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
#ifndef __local_qfcvt_defined
#define __local_qfcvt_defined 1
#ifndef __CRT_QCVT_BUFFER_DEFINED
#define __CRT_QCVT_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__qcvt_buffer) char __qcvt_buffer[32] = {0};
__NAMESPACE_LOCAL_END
#endif /* !__CRT_QCVT_BUFFER_DEFINED */
/* Dependency: "qfcvt_r" from "stdlib" */
#ifndef ____localdep_qfcvt_r_defined
#define ____localdep_qfcvt_r_defined 1
#ifdef __CRT_HAVE_qfcvt_r
__CREDIRECT(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,__localdep_qfcvt_r,(long double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),qfcvt_r,(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* LIBC: qfcvt_r */
#include <local/stdlib/qfcvt_r.h>
#define __localdep_qfcvt_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(qfcvt_r))
#endif /* qfcvt_r... */
#endif /* !____localdep_qfcvt_r_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(qfcvt) __ATTR_WUNUSED __ATTR_NONNULL((3, 4)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(qfcvt))(long double __val,
                                                   int __ndigit,
                                                   int *__restrict __decptr,
                                                   int *__restrict __sign) {
#line 1274 "kos/src/libc/magic/stdlib.c"
	if (__localdep_qfcvt_r(__val, __ndigit, __decptr, __sign, __NAMESPACE_LOCAL_SYM __qcvt_buffer, sizeof(__NAMESPACE_LOCAL_SYM __qcvt_buffer)))
		return __NULLPTR;
	return __NAMESPACE_LOCAL_SYM __qcvt_buffer;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_qfcvt_defined */
