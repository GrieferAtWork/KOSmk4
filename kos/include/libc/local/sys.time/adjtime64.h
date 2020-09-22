/* HASH CRC-32:0x19fa6f79 */
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
#ifndef __local_adjtime64_defined
#define __local_adjtime64_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_adjtime
__NAMESPACE_LOCAL_BEGIN
/* Dependency: adjtime32 from sys.time */
#ifndef __local___localdep_adjtime32_defined
#define __local___localdep_adjtime32_defined 1
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_adjtime32,(struct __timeval32 const *__delta, struct __timeval32 *__olddelta),adjtime,(__delta,__olddelta))
#endif /* !__local___localdep_adjtime32_defined */
__LOCAL_LIBC(adjtime64) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(adjtime64))(struct __timeval64 const *__delta, struct __timeval64 *__olddelta) {
	int __result;
	struct __timeval32 __delta32, __olddelta32;
	if (__delta) {
		__delta32.tv_sec  = (__time32_t)__delta->tv_sec;
		__delta32.tv_usec = __delta->tv_usec;
	}
	__result = __localdep_adjtime32(__which, __delta ? &__delta32 : __NULLPTR, __olddelta ? &__olddelta32 : __NULLPTR);
	if (__likely(!__result) && __olddelta) {
		__olddelta->tv_sec  = (__time64_t)__olddelta32.tv_sec;
		__olddelta->tv_usec = __olddelta32.tv_usec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_adjtime64_defined
#define __local___localdep_adjtime64_defined 1
#define __localdep_adjtime64 __LIBC_LOCAL_NAME(adjtime64)
#endif /* !__local___localdep_adjtime64_defined */
#else /* __CRT_HAVE_adjtime */
#undef __local_adjtime64_defined
#endif /* !__CRT_HAVE_adjtime */
#endif /* !__local_adjtime64_defined */
