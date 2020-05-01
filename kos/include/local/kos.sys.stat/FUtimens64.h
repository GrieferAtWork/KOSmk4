/* HASH CRC-32:0xcd9617da */
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
#ifndef __local_FUtimens64_defined
#ifdef __CRT_HAVE_FUtimens
#define __local_FUtimens64_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "FUtimens32" from "kos.sys.stat" */
#ifndef ____localdep_FUtimens32_defined
#define ____localdep_FUtimens32_defined 1
#ifdef __CRT_HAVE_FUtimens
__CREDIRECT_VOID(,,__localdep_FUtimens32,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),FUtimens,(__fd,__times)) __THROWS(...)
#else /* LIBC: FUtimens */
#undef ____localdep_FUtimens32_defined
#endif /* FUtimens32... */
#endif /* !____localdep_FUtimens32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(FUtimens64) void
(__LIBCCALL __LIBC_LOCAL_NAME(FUtimens64))(__fd_t __fd,
                                           struct __timespec64 const __times[2 /*or:3*/]) __THROWS(...) {
#line 298 "kos/src/libc/magic/kos.sys.stat.c"
	struct __timespec32 __tms[2];
	if (!__times) {
		__localdep_FUtimens32(__fd, __NULLPTR);
	} else {
		__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
		__tms[0].tv_nsec = __times[0].tv_nsec;
		__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
		__tms[1].tv_nsec = __times[1].tv_nsec;
		__localdep_FUtimens32(__fd, __tms);
	}
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_FUtimens */
#endif /* !__local_FUtimens64_defined */
