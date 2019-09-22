/* HASH CRC-32:0xdb4a04af */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_pipe_defined
#if defined(__CRT_HAVE__pipe)
#define __local_pipe_defined 1
/* Dependency: "dos_pipe" from "unistd" */
#ifndef ____localdep_dos_pipe_defined
#define ____localdep_dos_pipe_defined 1
#if defined(__CRT_HAVE__pipe)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_dos_pipe,(__fd_t __pipedes[2], __UINT32_TYPE__ __pipesize, __oflag_t __textmode),_pipe,(__pipedes,__pipesize,__textmode))
#else /* LIBC: _pipe */
#undef ____localdep_dos_pipe_defined
#endif /* dos_pipe... */
#endif /* !____localdep_dos_pipe_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
__LOCAL_LIBC(pipe) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pipe))(__fd_t __pipedes[2]) {
#line 330 "kos/src/libc/magic/unistd.c"
	return __localdep_dos_pipe(__pipedes, 4096, 0x8000); /* O_BINARY */
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE__pipe) */
#endif /* !__local_pipe_defined */
