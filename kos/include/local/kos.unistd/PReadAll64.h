/* HASH CRC-32:0xaebfe0ce */
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
#ifndef __local_PReadAll64_defined
#if defined(__CRT_HAVE_PRead) || defined(__CRT_HAVE_PRead64)
#define __local_PReadAll64_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "PRead64" from "kos.unistd" */
#ifndef ____localdep_PRead64_defined
#define ____localdep_PRead64_defined 1
#ifdef __CRT_HAVE_PRead64
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__THROWING,__localdep_PRead64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PRead64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__THROWING,__localdep_PRead64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PRead,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead)
#include <local/kos.unistd/PRead64.h>
/* >> pread64(2)
 * Read data from a file at a specific offset */
#define __localdep_PRead64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PRead64))
#else /* CUSTOM: PRead64 */
#undef ____localdep_PRead64_defined
#endif /* PRead64... */
#endif /* !____localdep_PRead64_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__LOCAL_LIBC(PReadAll64) __ATTR_NONNULL((2)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(PReadAll64))(__fd_t __fd,
                                           void *__buf,
                                           __SIZE_TYPE__ __bufsize,
                                           __pos64_t __offset) __THROWS(...) {
#line 377 "kos/src/libc/magic/kos.unistd.c"
	__SIZE_TYPE__ __result, __temp;
	__result = __localdep_PRead64(__fd, __buf, __bufsize, __offset);
	if (__result != 0 && (__SIZE_TYPE__)__result < __bufsize) {
		/* Keep on reading */
		for (;;) {
			__temp = __localdep_PRead64(__fd,
			              (__BYTE_TYPE__ *)__buf + __result,
			               __bufsize - __result,
			               __offset + __result);
			if (!__temp) {
				__result = 0;
				break;
			}
			__result += __temp;
			if (__result >= __bufsize)
				break;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_PRead || __CRT_HAVE_PRead64 */
#endif /* !__local_PReadAll64_defined */
