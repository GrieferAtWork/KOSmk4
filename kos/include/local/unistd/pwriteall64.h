/* HASH CRC-32:0xab8e6d58 */
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
#ifndef __local_pwriteall64_defined
#if defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE__lseeki64))) || defined(__CRT_HAVE_pwrite64) || (defined(__CRT_HAVE_pwrite) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE___pwrite64)
#define __local_pwriteall64_defined 1
#include <__crt.h>
/* Dependency: "pwrite64" from "unistd" */
#ifndef ____localdep_pwrite64_defined
#define ____localdep_pwrite64_defined 1
#ifdef __CRT_HAVE_pwrite64
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite64,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite64,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pwrite,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pwrite64)
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite64,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),__pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE__lseeki64)))
#include <local/unistd/pwrite64.h>
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
#define __localdep_pwrite64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwrite64))
#else /* CUSTOM: pwrite64 */
#undef ____localdep_pwrite64_defined
#endif /* pwrite64... */
#endif /* !____localdep_pwrite64_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
__LOCAL_LIBC(pwriteall64) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pwriteall64))(__fd_t __fd,
                                                         void *__buf,
                                                         __SIZE_TYPE__ __bufsize,
                                                         __PIO_OFFSET64 __offset) {
#line 1063 "kos/src/libc/magic/unistd.c"
	__SSIZE_TYPE__ __result, __temp;
	__result = __localdep_pwrite64(__fd, __buf, __bufsize, __offset);
	if (__result > 0 && (__SIZE_TYPE__)__result < __bufsize) {
		/* Keep on writing */
		for (;;) {
			__temp = __localdep_pwrite64(__fd,
			                (__BYTE_TYPE__ *)__buf + (__SIZE_TYPE__)__result,
			                __bufsize - (__SIZE_TYPE__)__result,
			                __offset + (__SIZE_TYPE__)__result);
			if (__temp <= 0) {
				__result = __temp;
				break;
			}
			__result += __temp;
			if ((__SIZE_TYPE__)__result >= __bufsize)
				break;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_pread || ((__CRT_HAVE_write || __CRT_HAVE__write) && (__CRT_HAVE_lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE__lseeki64)) || __CRT_HAVE_pwrite64 || (__CRT_HAVE_pwrite && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || __CRT_HAVE___pwrite64 */
#endif /* !__local_pwriteall64_defined */
