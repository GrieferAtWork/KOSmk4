/* HASH CRC-32:0x117c7984 */
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
#ifndef __local_pwriteall_defined
#define __local_pwriteall_defined 1
#include <__crt.h>
#include <asm/os/stdio.h>
#if defined(__CRT_HAVE_pwriteall64) || (defined(__CRT_HAVE_pwriteall) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_pwrite64) || defined(__CRT_HAVE___pwrite64) || defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(__pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(__off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: pwriteall64 from unistd */
#ifndef __local___localdep_pwriteall64_defined
#define __local___localdep_pwriteall64_defined 1
#ifdef __CRT_HAVE_pwriteall64
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwriteall64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pwriteall64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwriteall) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwriteall64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pwriteall,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite64) || defined(__CRT_HAVE___pwrite64) || defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/pwriteall64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
#define __localdep_pwriteall64 __LIBC_LOCAL_NAME(pwriteall64)
#else /* ... */
#undef __local___localdep_pwriteall64_defined
#endif /* !... */
#endif /* !__local___localdep_pwriteall64_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pwriteall(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__LOCAL_LIBC(pwriteall) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pwriteall))(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET __offset) {
	return __localdep_pwriteall64(__fd, __buf, __bufsize, (__PIO_OFFSET64)__offset);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pwriteall_defined
#define __local___localdep_pwriteall_defined 1
#define __localdep_pwriteall __LIBC_LOCAL_NAME(pwriteall)
#endif /* !__local___localdep_pwriteall_defined */
#else /* __CRT_HAVE_pwriteall64 || (__CRT_HAVE_pwriteall && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || __CRT_HAVE_pwrite64 || __CRT_HAVE___pwrite64 || __CRT_HAVE_pwrite || ((__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && __SEEK_CUR && __SEEK_SET) */
#undef __local_pwriteall_defined
#endif /* !__CRT_HAVE_pwriteall64 && (!__CRT_HAVE_pwriteall || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && !__CRT_HAVE_pwrite64 && !__CRT_HAVE___pwrite64 && !__CRT_HAVE_pwrite && ((!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || !__SEEK_CUR || !__SEEK_SET) */
#endif /* !__local_pwriteall_defined */
