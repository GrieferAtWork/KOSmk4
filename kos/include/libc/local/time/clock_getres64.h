/* HASH CRC-32:0xe2e8e70e */
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
#ifndef __local_clock_getres64_defined
#define __local_clock_getres64_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_clock_getres) || defined(__CRT_HAVE___clock_getres)
#include <bits/types.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_clock_getres32_defined
#define __local___localdep_clock_getres32_defined 1
#ifdef __CRT_HAVE_clock_getres
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_getres32,(__clockid_t __clock_id, struct __timespec32 *__res),clock_getres,(__clock_id,__res))
#elif defined(__CRT_HAVE___clock_getres)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_clock_getres32,(__clockid_t __clock_id, struct __timespec32 *__res),__clock_getres,(__clock_id,__res))
#else /* ... */
#undef __local___localdep_clock_getres32_defined
#endif /* !... */
#endif /* !__local___localdep_clock_getres32_defined */
__LOCAL_LIBC(clock_getres64) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(clock_getres64))(__clockid_t __clock_id, struct __timespec64 *__res) {
	int __result;
	struct __timespec32 __res32;
	__result = __localdep_clock_getres32(__clock_id, &__res32);
	if (!__result) {
		__res->tv_sec  = (__time64_t)__res32.tv_sec;
		__res->tv_nsec = __res32.tv_nsec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_clock_getres64_defined
#define __local___localdep_clock_getres64_defined 1
#define __localdep_clock_getres64 __LIBC_LOCAL_NAME(clock_getres64)
#endif /* !__local___localdep_clock_getres64_defined */
#else /* __CRT_HAVE_clock_getres || __CRT_HAVE___clock_getres */
#undef __local_clock_getres64_defined
#endif /* !__CRT_HAVE_clock_getres && !__CRT_HAVE___clock_getres */
#endif /* !__local_clock_getres64_defined */
