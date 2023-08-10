/* HASH CRC-32:0x41f9788d */
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
#ifndef __local_readall_defined
#define __local_readall_defined
#include <__crt.h>
#include <asm/os/stdio.h>
#include <features.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lseek_defined
#define __local___localdep_lseek_defined
#if defined(__CRT_HAVE_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___libc_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),__libc_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),__llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1),__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/lseek.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lseek __LIBC_LOCAL_NAME(lseek)
#endif /* !... */
#endif /* !__local___localdep_lseek_defined */
#ifndef __local___localdep_lseek64_defined
#define __local___localdep_lseek64_defined
#if defined(__CRT_HAVE_lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___libc_lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__libc_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64)
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64)
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_llseek)
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___llseek)
__CREDIRECT(__ATTR_FDARG(1),__off64_t,__NOTHROW_NCX,__localdep_lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/lseek64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lseek64 __LIBC_LOCAL_NAME(lseek64)
#else /* ... */
#undef __local___localdep_lseek64_defined
#endif /* !... */
#endif /* !__local___localdep_lseek64_defined */
#ifndef __local___localdep_read_defined
#define __local___localdep_read_defined
#ifdef __CRT_HAVE_read
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__libc_read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(readall) __ATTR_FDREAD(1) __ATTR_OUTS(2, 3) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(readall))(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize) {
	__SSIZE_TYPE__ __result, __temp;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_read)(__fd, __buf, __bufsize);
	if (__result > 0 && (__SIZE_TYPE__)__result < __bufsize) {
		/* Keep on reading */
		for (;;) {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_read)(__fd,
			            (__BYTE_TYPE__ *)__buf + (__SIZE_TYPE__)__result,
			            __bufsize - (__SIZE_TYPE__)__result);
			if (__temp <= 0) {
#ifdef __libc_geterrno
				__errno_t __old_error = __libc_geterrno();
#endif /* __libc_geterrno */
				/* Try to un-read data that had already been loaded. */
#if __SIZEOF_SIZE_T__ > __SIZEOF_OFF_T__
				(__NAMESPACE_LOCAL_SYM __localdep_lseek64)(__fd, -(__off_t)(__pos_t)(__SIZE_TYPE__)__result, __SEEK_CUR);
#else /* __SIZEOF_SIZE_T__ > __SIZEOF_OFF_T__ */
				(__NAMESPACE_LOCAL_SYM __localdep_lseek)(__fd, -(__off_t)(__pos_t)(__SIZE_TYPE__)__result, __SEEK_CUR);
#endif /* __SIZEOF_SIZE_T__ <= __SIZEOF_OFF_T__ */
#ifdef __libc_geterrno
				(void)__libc_seterrno(__old_error);
#endif /* __libc_geterrno */
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
#ifndef __local___localdep_readall_defined
#define __local___localdep_readall_defined
#define __localdep_readall __LIBC_LOCAL_NAME(readall)
#endif /* !__local___localdep_readall_defined */
#else /* (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_CUR */
#undef __local_readall_defined
#endif /* (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_llseek && !__CRT_HAVE___llseek && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek && !__CRT_HAVE___libc_lseek) || !__SEEK_CUR */
#endif /* !__local_readall_defined */
