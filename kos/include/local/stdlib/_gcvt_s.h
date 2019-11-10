/* HASH CRC-32:0xe7643d32 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__gcvt_s_defined
#define __local__gcvt_s_defined 1
#include <parts/errno.h>
/* Dependency: "ecvt_r" from "stdlib" */
#ifndef ____localdep_ecvt_r_defined
#define ____localdep_ecvt_r_defined 1
#ifdef __CRT_HAVE_ecvt_r
__CREDIRECT(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,__localdep_ecvt_r,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),ecvt_r,(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* LIBC: ecvt_r */
#include <local/stdlib/ecvt_r.h>
#define __localdep_ecvt_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ecvt_r))
#endif /* ecvt_r... */
#endif /* !____localdep_ecvt_r_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_gcvt_s) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_gcvt_s))(char *__buf,
                                                     __SIZE_TYPE__ __buflen,
                                                     double __val,
                                                     int __ndigit) {
#line 2624 "kos/src/libc/magic/stdlib.c"
	int __a, __b;
	if (!__buf)
		return __EINVAL;
	__localdep_ecvt_r(__val, __ndigit, &__a, &__b, __buf, __buflen);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__gcvt_s_defined */
