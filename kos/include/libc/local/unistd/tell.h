/* HASH CRC-32:0x1927d9eb */
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
#ifndef __local_tell_defined
#define __local_tell_defined
#include <__crt.h>
#include <asm/os/stdio.h>
#include <features.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR)
__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(tell) __ATTR_WUNUSED __off_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tell))(__fd_t __fd) {
	return (__NAMESPACE_LOCAL_SYM __localdep_lseek)(__fd, 0, __SEEK_CUR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tell_defined
#define __local___localdep_tell_defined
#define __localdep_tell __LIBC_LOCAL_NAME(tell)
#endif /* !__local___localdep_tell_defined */
#else /* (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_CUR */
#undef __local_tell_defined
#endif /* (!__CRT_HAVE_lseek64 && !__CRT_HAVE__lseeki64 && !__CRT_HAVE_llseek && !__CRT_HAVE___llseek && !__CRT_HAVE_lseek && !__CRT_HAVE__lseek && !__CRT_HAVE___lseek && !__CRT_HAVE___libc_lseek) || !__SEEK_CUR */
#endif /* !__local_tell_defined */
