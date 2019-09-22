/* HASH CRC-32:0x9a1212df */
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
#ifndef __local_preadall_defined
#if ((defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64)))) || defined(__CRT_HAVE_pread64) || (defined(__CRT_HAVE_pread) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_preadall64) || (defined(__CRT_HAVE_preadall) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
#define __local_preadall_defined 1
#include <parts/errno.h>
/* Dependency: "preadall64" from "unistd" */
#ifndef ____localdep_preadall64_defined
#define ____localdep_preadall64_defined 1
#if defined(__CRT_HAVE_preadall64)
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadall64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),preadall64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_preadall) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadall64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),preadall,(__fd,__buf,__bufsize,__offset))
#elif (defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64)))) || defined(__CRT_HAVE_pread64) || (defined(__CRT_HAVE_pread) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
#include <local/unistd/preadall64.h>
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
#define __localdep_preadall64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(preadall64))
#else /* CUSTOM: preadall64 */
#undef ____localdep_preadall64_defined
#endif /* preadall64... */
#endif /* !____localdep_preadall64_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__LOCAL_LIBC(preadall) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(preadall))(__fd_t __fd,
                                                      void *__buf,
                                                      __SIZE_TYPE__ __bufsize,
                                                      __PIO_OFFSET __offset) {
#line 899 "kos/src/libc/magic/unistd.c"
	return __localdep_preadall64(__fd, __buf, __bufsize, (__PIO_OFFSET64)__offset);
}
__NAMESPACE_LOCAL_END
#endif /* ((defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64)))) || defined(__CRT_HAVE_pread64) || (defined(__CRT_HAVE_pread) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_preadall64) || (defined(__CRT_HAVE_preadall) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) */
#endif /* !__local_preadall_defined */
