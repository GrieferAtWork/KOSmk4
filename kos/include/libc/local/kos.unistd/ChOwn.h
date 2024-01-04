/* HASH CRC-32:0xd9a7e318 */
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
#ifndef __local_ChOwn_defined
#define __local_ChOwn_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_FChOwnAt)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_FChOwnAt_defined
#define __local___localdep_FChOwnAt_defined
__CREDIRECT_VOID(__ATTR_IN(2),__THROWING(...),__localdep_FChOwnAt,(__fd_t __dfd, char const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),FChOwnAt,(__dfd,__file,__owner,__group,__flags))
#endif /* !__local___localdep_FChOwnAt_defined */
__LOCAL_LIBC(ChOwn) __ATTR_IN(1) void
(__LIBCCALL __LIBC_LOCAL_NAME(ChOwn))(char const *__file, __uid_t __owner, __gid_t __group) __THROWS(...) {
	(__NAMESPACE_LOCAL_SYM __localdep_FChOwnAt)(__AT_FDCWD, __file, __owner, __group, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ChOwn_defined
#define __local___localdep_ChOwn_defined
#define __localdep_ChOwn __LIBC_LOCAL_NAME(ChOwn)
#endif /* !__local___localdep_ChOwn_defined */
#else /* __AT_FDCWD && __CRT_HAVE_FChOwnAt */
#undef __local_ChOwn_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_FChOwnAt */
#endif /* !__local_ChOwn_defined */
