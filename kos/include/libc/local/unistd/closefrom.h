/* HASH CRC-32:0xde13ff09 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_closefrom_defined
#define __local_closefrom_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if ((defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_CLOSEM)) || defined(__CRT_HAVE_close_range)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_close_range_defined) && defined(__CRT_HAVE_close_range)
#define __local___localdep_close_range_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close_range,(unsigned int __minfd, unsigned int __maxfd, unsigned int __flags),close_range,(__minfd,__maxfd,__flags))
#endif /* !__local___localdep_close_range_defined && __CRT_HAVE_close_range */
#ifndef __local___localdep_fcntl_defined
#define __local___localdep_fcntl_defined
#ifdef __CRT_HAVE_fcntl
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __fcntl_t __cmd),fcntl,(__fd,__cmd),__cmd,1,(void *))
#elif defined(__CRT_HAVE___fcntl)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __fcntl_t __cmd),__fcntl,(__fd,__cmd),__cmd,1,(void *))
#elif defined(__CRT_HAVE___libc_fcntl)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __fcntl_t __cmd),__libc_fcntl,(__fd,__cmd),__cmd,1,(void *))
#else /* ... */
#undef __local___localdep_fcntl_defined
#endif /* !... */
#endif /* !__local___localdep_fcntl_defined */
__LOCAL_LIBC(closefrom) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(closefrom))(__fd_t __lowfd) {
#if (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_CLOSEM)
	(__NAMESPACE_LOCAL_SYM __localdep_fcntl)(__lowfd, __F_CLOSEM);
#else /* (__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_CLOSEM */
	(__NAMESPACE_LOCAL_SYM __localdep_close_range)((unsigned int)__lowfd, (unsigned int)-1, 0);
#endif /* (!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_CLOSEM */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_closefrom_defined
#define __local___localdep_closefrom_defined
#define __localdep_closefrom __LIBC_LOCAL_NAME(closefrom)
#endif /* !__local___localdep_closefrom_defined */
#else /* ((__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_CLOSEM) || __CRT_HAVE_close_range */
#undef __local_closefrom_defined
#endif /* ((!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_CLOSEM) && !__CRT_HAVE_close_range */
#endif /* !__local_closefrom_defined */
