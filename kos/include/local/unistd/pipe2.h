/* HASH CRC-32:0x333af07f */
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
#ifndef __local_pipe2_defined
#if defined(__CRT_HAVE__pipe) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe)
#define __local_pipe2_defined 1
#include <__crt.h>
/* Dependency: "pipe" from "unistd" */
#ifndef ____localdep_pipe_defined
#define ____localdep_pipe_defined 1
#ifdef __CRT_HAVE_pipe
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pipe,(__fd_t __pipedes[2]),pipe,(__pipedes))
#elif defined(__CRT_HAVE___pipe)
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pipe,(__fd_t __pipedes[2]),__pipe,(__pipedes))
#elif defined(__CRT_HAVE__pipe)
#include <local/unistd/pipe.h>
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
#define __localdep_pipe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pipe))
#else /* CUSTOM: pipe */
#undef ____localdep_pipe_defined
#endif /* pipe... */
#endif /* !____localdep_pipe_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pipe2) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pipe2))(__fd_t __pipedes[2],
                                                   __oflag_t __flags) {
#line 1116 "kos/src/libc/magic/unistd.c"
	(void)__flags;
	return __localdep_pipe(__pipedes);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE__pipe || __CRT_HAVE_pipe || __CRT_HAVE___pipe */
#endif /* !__local_pipe2_defined */
