/* HASH CRC-32:0xa19570c6 */
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
#ifndef __local_timeval_add_defined
#define __local_timeval_add_defined
#include <__crt.h>
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(timeval_add) __ATTR_NONNULL((1, 2, 3)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timeval_add))(struct timeval *__result, struct timeval const *__lhs, struct timeval const *__rhs) {
	__result->tv_sec  = __lhs->tv_sec  + __rhs->tv_sec;
	__result->tv_usec = __lhs->tv_usec + __rhs->tv_usec;
	if ((__suseconds_t)__result->tv_usec >= (__suseconds_t)__UINT32_C(1000000)) {
		__result->tv_usec -= __UINT32_C(1000000);
		++__result->tv_sec;
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timeval_add_defined
#define __local___localdep_timeval_add_defined
#define __localdep_timeval_add __LIBC_LOCAL_NAME(timeval_add)
#endif /* !__local___localdep_timeval_add_defined */
#endif /* !__local_timeval_add_defined */
