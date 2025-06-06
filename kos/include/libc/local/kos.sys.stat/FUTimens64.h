/* HASH CRC-32:0x3e89139e */
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
#ifndef __local_FUTimens64_defined
#define __local_FUTimens64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_FUTimens
#include <kos/anno.h>
#include <bits/os/timespec.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_FUTimens32_defined
#define __local___localdep_FUTimens32_defined
__CREDIRECT_VOID(__ATTR_FDARG(1),__THROWING(...),__localdep_FUTimens32,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),FUTimens,(__fd,__times))
#endif /* !__local___localdep_FUTimens32_defined */
__LOCAL_LIBC(FUTimens64) __ATTR_FDARG(1) __ATTR_IN_OPT(2) void
(__LIBCCALL __LIBC_LOCAL_NAME(FUTimens64))(__fd_t __fd, struct __timespec64 const __times[2 /*or:3*/]) __THROWS(...) {
	struct __timespec32 __tms[2];
	if (!__times) {
		(__NAMESPACE_LOCAL_SYM __localdep_FUTimens32)(__fd, __NULLPTR);
	} else {
		__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
		__tms[0].tv_nsec = __times[0].tv_nsec;
		__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
		__tms[1].tv_nsec = __times[1].tv_nsec;
		(__NAMESPACE_LOCAL_SYM __localdep_FUTimens32)(__fd, __tms);
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_FUTimens64_defined
#define __local___localdep_FUTimens64_defined
#define __localdep_FUTimens64 __LIBC_LOCAL_NAME(FUTimens64)
#endif /* !__local___localdep_FUTimens64_defined */
#else /* __CRT_HAVE_FUTimens */
#undef __local_FUTimens64_defined
#endif /* !__CRT_HAVE_FUTimens */
#endif /* !__local_FUTimens64_defined */
