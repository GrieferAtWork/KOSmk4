/* HASH CRC-32:0xf2c31c9c */
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
#ifndef __local__pipe_defined
#if defined(__CRT_HAVE__pipe) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE_pipe2)
#define __local__pipe_defined 1
#include <bits/types.h>
/* Dependency: "pipe2" from "unistd" */
#ifndef ____localdep_pipe2_defined
#define ____localdep_pipe2_defined 1
#ifdef __CRT_HAVE_pipe2
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pipe2,(__fd_t __pipedes[2], __oflag_t __flags),pipe2,(__pipedes,__flags))
#elif defined(__CRT_HAVE__pipe) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe)
#include <local/unistd/pipe2.h>
#define __localdep_pipe2 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pipe2))
#else /* CUSTOM: pipe2 */
#undef ____localdep_pipe2_defined
#endif /* pipe2... */
#endif /* !____localdep_pipe2_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_pipe) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_pipe))(__fd_t __pipedes[2],
                                                   __UINT32_TYPE__ __pipesize,
                                                   __oflag_t __textmode) {
#line 219 "kos/src/libc/magic/io.c"
	(void)__pipesize;
	return __localdep_pipe2(__pipedes, __textmode);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE__pipe || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE_pipe2 */
#endif /* !__local__pipe_defined */
