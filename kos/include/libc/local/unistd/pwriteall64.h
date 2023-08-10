/* HASH CRC-32:0xae00b077 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_pwriteall64_defined
#define __local_pwriteall64_defined
#include <__crt.h>
#include <bits/types.h>
#include <asm/os/stdio.h>
#include <features.h>
#if defined(__CRT_HAVE_pwrite64) || defined(__CRT_HAVE___pwrite64) || defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pwrite64_defined
#define __local___localdep_pwrite64_defined
#if defined(__CRT_HAVE_pwrite) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite64,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pwrite,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite64)
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite64,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pwrite64)
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwrite64,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset),__pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/pwrite64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pwrite64 __LIBC_LOCAL_NAME(pwrite64)
#else /* ... */
#undef __local___localdep_pwrite64_defined
#endif /* !... */
#endif /* !__local___localdep_pwrite64_defined */
__LOCAL_LIBC(pwriteall64) __ATTR_FDWRITE(1) __ATTR_INS(2, 3) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pwriteall64))(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __PIO_OFFSET64 __offset) {
	__SSIZE_TYPE__ __result, __temp;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_pwrite64)(__fd, __buf, __bufsize, __offset);
	if (__result > 0 && (__SIZE_TYPE__)__result < __bufsize) {
		/* Keep on writing */
		for (;;) {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_pwrite64)(__fd,
			                (__BYTE_TYPE__ const *)__buf + (__SIZE_TYPE__)__result,
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
#ifndef __local___localdep_pwriteall64_defined
#define __local___localdep_pwriteall64_defined
#define __localdep_pwriteall64 __LIBC_LOCAL_NAME(pwriteall64)
#endif /* !__local___localdep_pwriteall64_defined */
#else /* __CRT_HAVE_pwrite64 || __CRT_HAVE___pwrite64 || __CRT_HAVE_pwrite || ((__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && __SEEK_CUR && __SEEK_SET) */
#undef __local_pwriteall64_defined
#endif /* !__CRT_HAVE_pwrite64 && !__CRT_HAVE___pwrite64 && !__CRT_HAVE_pwrite && ((!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_llseek && !__CRT_HAVE___llseek && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek && !__CRT_HAVE___libc_lseek) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || !__SEEK_CUR || !__SEEK_SET) */
#endif /* !__local_pwriteall64_defined */
