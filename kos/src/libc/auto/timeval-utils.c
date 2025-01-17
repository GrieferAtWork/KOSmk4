/* HASH CRC-32:0xaba4006e */
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
#ifndef GUARD_LIBC_AUTO_TIMEVAL_UTILS_C
#define GUARD_LIBC_AUTO_TIMEVAL_UTILS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "timeval-utils.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/os/timeval.h>
#include <bits/types.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_timeval_add)(struct timeval *result,
                                       struct timeval const *lhs,
                                       struct timeval const *rhs) {
	result->tv_sec  = lhs->tv_sec  + rhs->tv_sec;
	result->tv_usec = lhs->tv_usec + rhs->tv_usec;
	if ((__suseconds_t)result->tv_usec >= (__suseconds_t)__UINT32_C(1000000)) {
		result->tv_usec -= __UINT32_C(1000000);
		++result->tv_sec;
	}
}
#include <bits/os/timeval.h>
#include <bits/types.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_timeval_sub)(struct timeval *result,
                                       struct timeval const *lhs,
                                       struct timeval const *rhs) {
	result->tv_sec  = lhs->tv_sec  - rhs->tv_sec;
	result->tv_usec = lhs->tv_usec - rhs->tv_usec;
	if ((__suseconds_t)result->tv_usec < 0) {
		result->tv_usec += __UINT32_C(1000000);
		--result->tv_sec;
	}
}
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P_VOID(libc_timeval_add64,libc_timeval_add,ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1),NOTHROW_NCX,LIBCCALL,(struct timeval64 *result, struct timeval64 const *lhs, struct timeval64 const *rhs),(result,lhs,rhs));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <bits/os/timeval.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_timeval_add64)(struct timeval64 *result,
                                         struct timeval64 const *lhs,
                                         struct timeval64 const *rhs) {
	result->tv_sec  = lhs->tv_sec  + rhs->tv_sec;
	result->tv_usec = lhs->tv_usec + rhs->tv_usec;
	if ((__suseconds_t)result->tv_usec >= (__suseconds_t)__UINT32_C(1000000)) {
		result->tv_usec -= __UINT32_C(1000000);
		++result->tv_sec;
	}
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS_P_VOID(libc_timeval_sub64,libc_timeval_sub,ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1),NOTHROW_NCX,LIBCCALL,(struct timeval64 *result, struct timeval64 const *lhs, struct timeval64 const *rhs),(result,lhs,rhs));
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#include <bits/os/timeval.h>
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_timeval_sub64)(struct timeval64 *result,
                                         struct timeval64 const *lhs,
                                         struct timeval64 const *rhs) {
	result->tv_sec  = lhs->tv_sec  - rhs->tv_sec;
	result->tv_usec = lhs->tv_usec - rhs->tv_usec;
	if ((__suseconds_t)result->tv_usec < (__suseconds_t)__UINT32_C(1000000)) {
		result->tv_usec += __UINT32_C(1000000);
		--result->tv_sec;
	}
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P_VOID(timeval_add,libc_timeval_add,ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1),NOTHROW_NCX,LIBCCALL,(struct timeval *result, struct timeval const *lhs, struct timeval const *rhs),(result,lhs,rhs));
DEFINE_PUBLIC_ALIAS_P_VOID(timeval_sub,libc_timeval_sub,ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1),NOTHROW_NCX,LIBCCALL,(struct timeval *result, struct timeval const *lhs, struct timeval const *rhs),(result,lhs,rhs));
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P_VOID(timeval_add64,libc_timeval_add64,ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1),NOTHROW_NCX,LIBCCALL,(struct timeval64 *result, struct timeval64 const *lhs, struct timeval64 const *rhs),(result,lhs,rhs));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS_P_VOID(timeval_sub64,libc_timeval_sub64,ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1),NOTHROW_NCX,LIBCCALL,(struct timeval64 *result, struct timeval64 const *lhs, struct timeval64 const *rhs),(result,lhs,rhs));
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_TIMEVAL_UTILS_C */
