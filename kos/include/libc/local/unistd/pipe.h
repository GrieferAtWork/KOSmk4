/* HASH CRC-32:0xa5d8d1ad */
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
#ifndef __local_pipe_defined
#define __local_pipe_defined
#include <__crt.h>
#ifdef __CRT_HAVE__pipe
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dos_pipe_defined
#define __local___localdep_dos_pipe_defined
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_dos_pipe,(__fd_t __pipedes[2], __UINT32_TYPE__ __pipesize, __oflag_t __textmode),_pipe,(__pipedes,__pipesize,__textmode))
#endif /* !__local___localdep_dos_pipe_defined */
__LOCAL_LIBC(pipe) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pipe))(__fd_t __pipedes[2]) {
	return (__NAMESPACE_LOCAL_SYM __localdep_dos_pipe)(__pipedes, 4096, 0x8000); /* O_BINARY */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pipe_defined
#define __local___localdep_pipe_defined
#define __localdep_pipe __LIBC_LOCAL_NAME(pipe)
#endif /* !__local___localdep_pipe_defined */
#else /* __CRT_HAVE__pipe */
#undef __local_pipe_defined
#endif /* !__CRT_HAVE__pipe */
#endif /* !__local_pipe_defined */
