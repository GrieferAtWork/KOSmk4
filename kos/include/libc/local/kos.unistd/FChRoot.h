/* HASH CRC-32:0x94689ec2 */
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
#ifndef __local_FChRoot_defined
#define __local_FChRoot_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_Dup2) && defined(__AT_FDROOT)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_Dup2_defined
#define __local___localdep_Dup2_defined
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__THROWING(...),__localdep_Dup2,(__fd_t __oldfd, __fd_t __newfd),Dup2,(__oldfd,__newfd))
#endif /* !__local___localdep_Dup2_defined */
__LOCAL_LIBC(FChRoot) __ATTR_FDARG(1) void
(__LIBCCALL __LIBC_LOCAL_NAME(FChRoot))(__fd_t __fd) __THROWS(...) {
	(void)(__NAMESPACE_LOCAL_SYM __localdep_Dup2)(__fd, __AT_FDROOT);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_FChRoot_defined
#define __local___localdep_FChRoot_defined
#define __localdep_FChRoot __LIBC_LOCAL_NAME(FChRoot)
#endif /* !__local___localdep_FChRoot_defined */
#else /* __CRT_HAVE_Dup2 && __AT_FDROOT */
#undef __local_FChRoot_defined
#endif /* !__CRT_HAVE_Dup2 || !__AT_FDROOT */
#endif /* !__local_FChRoot_defined */
