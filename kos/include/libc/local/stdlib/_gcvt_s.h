/* HASH CRC-32:0xcf0dec6f */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__gcvt_s_defined
#define __local__gcvt_s_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ecvt_r_defined
#define __local___localdep_ecvt_r_defined
#ifdef __CRT_HAVE_ecvt_r
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(3) __ATTR_OUT(4) __ATTR_OUTS(5, 6),int,__NOTHROW_NCX,__localdep_ecvt_r,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),ecvt_r,(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_ecvt_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/ecvt_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ecvt_r __LIBC_LOCAL_NAME(ecvt_r)
#endif /* !__CRT_HAVE_ecvt_r */
#endif /* !__local___localdep_ecvt_r_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_gcvt_s) __ATTR_OUTS(1, 2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_gcvt_s))(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit) {
	int __a, __b;
	if (!__buf) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	(__NAMESPACE_LOCAL_SYM __localdep_ecvt_r)(__val, __ndigit, &__a, &__b, __buf, __buflen);
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__gcvt_s_defined
#define __local___localdep__gcvt_s_defined
#define __localdep__gcvt_s __LIBC_LOCAL_NAME(_gcvt_s)
#endif /* !__local___localdep__gcvt_s_defined */
#endif /* !__local__gcvt_s_defined */
