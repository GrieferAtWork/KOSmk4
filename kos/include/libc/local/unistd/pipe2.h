/* HASH CRC-32:0x3b0829b */
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
#ifndef __local_pipe2_defined
#define __local_pipe2_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pipe_defined
#define __local___localdep_pipe_defined
#ifdef __CRT_HAVE_pipe
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_pipe,(__fd_t __pipedes[2]),pipe,(__pipedes))
#elif defined(__CRT_HAVE___pipe)
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_pipe,(__fd_t __pipedes[2]),__pipe,(__pipedes))
#elif defined(__CRT_HAVE___libc_pipe)
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_pipe,(__fd_t __pipedes[2]),__libc_pipe,(__pipedes))
#elif defined(__CRT_HAVE__pipe)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/pipe.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pipe __LIBC_LOCAL_NAME(pipe)
#else /* ... */
#undef __local___localdep_pipe_defined
#endif /* !... */
#endif /* !__local___localdep_pipe_defined */
__LOCAL_LIBC(pipe2) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pipe2))(__fd_t __pipedes[2], __oflag_t __flags) {
	/* TODO: Emulate using pipe()+fcntl() */
	(void)__flags;
	return (__NAMESPACE_LOCAL_SYM __localdep_pipe)(__pipedes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pipe2_defined
#define __local___localdep_pipe2_defined
#define __localdep_pipe2 __LIBC_LOCAL_NAME(pipe2)
#endif /* !__local___localdep_pipe2_defined */
#else /* __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe */
#undef __local_pipe2_defined
#endif /* !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe */
#endif /* !__local_pipe2_defined */
