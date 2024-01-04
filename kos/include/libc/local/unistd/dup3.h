/* HASH CRC-32:0xd3099962 */
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
#ifndef __local_dup3_defined
#define __local_dup3_defined
#include <__crt.h>
#if defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dup2_defined
#define __local___localdep_dup2_defined
#ifdef __CRT_HAVE_dup2
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___libc_dup2)
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__libc_dup2,(__oldfd,__newfd))
#else /* ... */
#undef __local___localdep_dup2_defined
#endif /* !... */
#endif /* !__local___localdep_dup2_defined */
__LOCAL_LIBC(dup3) __ATTR_FDARG(1) __fd_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dup3))(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags) {
	/* TODO: Document which `flags' actually do anything */
	/* TODO: Emulate using dup2()+fcntl() */
	(void)__flags;
	return __newfd != __oldfd ? (__NAMESPACE_LOCAL_SYM __localdep_dup2)(__oldfd, __newfd) : -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dup3_defined
#define __local___localdep_dup3_defined
#define __localdep_dup3 __LIBC_LOCAL_NAME(dup3)
#endif /* !__local___localdep_dup3_defined */
#else /* __CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2 */
#undef __local_dup3_defined
#endif /* !__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2 */
#endif /* !__local_dup3_defined */
