/* HASH CRC-32:0x136e94a3 */
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
#ifndef __local_ReadAll_defined
#define __local_ReadAll_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_Read) && (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_Read_defined
#define __local___localdep_Read_defined
__CREDIRECT(__ATTR_OUTS(2, 3),__SIZE_TYPE__,__THROWING,__localdep_Read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),Read,(__fd,__buf,__bufsize))
#endif /* !__local___localdep_Read_defined */
#ifndef __local___localdep_lseek_defined
#define __local___localdep_lseek_defined
#if defined(__CRT_HAVE_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___libc_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),__libc_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),__llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,__off_t,__NOTHROW_NCX,__localdep_lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/lseek.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lseek __LIBC_LOCAL_NAME(lseek)
#endif /* !... */
#endif /* !__local___localdep_lseek_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <kos/except.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ReadAll) __ATTR_OUTS(2, 3) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(ReadAll))(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize) __THROWS(...) {
	__SIZE_TYPE__ __result, __temp;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_Read)(__fd, __buf, __bufsize);
	if (__result != 0 && __result < __bufsize) {
		/* Keep on reading */
		for (;;) {
#ifdef TRY
			TRY
#endif /* TRY */
			{
				__temp = (__NAMESPACE_LOCAL_SYM __localdep_Read)(__fd,
				           (__BYTE_TYPE__ *)__buf + (__SIZE_TYPE__)__result,
				            __bufsize - (__SIZE_TYPE__)__result);
			}
#ifdef TRY
			EXCEPT {
#ifdef __libc_geterrno
				int __old_error = __libc_geterrno();
#endif /* __libc_geterrno */
				/* Try to un-read data that had already been loaded. */
				(__NAMESPACE_LOCAL_SYM __localdep_lseek)(__fd, -(__off_t)(__pos_t)__result, __SEEK_CUR);
#ifdef __libc_geterrno
				(void)__libc_seterrno(__old_error);
#endif /* __libc_geterrno */
				RETHROW();
			}
#endif /* TRY */
			if (!__temp) {
#ifdef __libc_geterrno
				int __old_error = __libc_geterrno();
#endif /* __libc_geterrno */
				/* Try to un-read data that had already been loaded. */
				(__NAMESPACE_LOCAL_SYM __localdep_lseek)(__fd, -(__off_t)(__pos_t)__result, __SEEK_CUR);
#ifdef __libc_geterrno
				(void)__libc_seterrno(__old_error);
#endif /* __libc_geterrno */
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
#ifndef __local___localdep_ReadAll_defined
#define __local___localdep_ReadAll_defined
#define __localdep_ReadAll __LIBC_LOCAL_NAME(ReadAll)
#endif /* !__local___localdep_ReadAll_defined */
#else /* __CRT_HAVE_Read && (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) */
#undef __local_ReadAll_defined
#endif /* !__CRT_HAVE_Read || (!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_llseek && !__CRT_HAVE___llseek && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek && !__CRT_HAVE___libc_lseek) */
#endif /* !__local_ReadAll_defined */
