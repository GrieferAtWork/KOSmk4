/* HASH CRC-32:0x214cc038 */
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
#ifndef __local_ReadLink_defined
#define __local_ReadLink_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_ReadLinkAt)
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ReadLinkAt_defined
#define __local___localdep_ReadLinkAt_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(3, 4),__SIZE_TYPE__,__THROWING,__localdep_ReadLinkAt,(__fd_t __dfd, char const *__restrict __path, char *__restrict __buf, __SIZE_TYPE__ __buflen),ReadLinkAt,(__dfd,__path,__buf,__buflen))
#endif /* !__local___localdep_ReadLinkAt_defined */
__LOCAL_LIBC(ReadLink) __ATTR_IN(1) __ATTR_OUTS(2, 3) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(ReadLink))(char const *__restrict __path, char *__restrict __buf, __SIZE_TYPE__ __buflen) __THROWS(...) {
	(__NAMESPACE_LOCAL_SYM __localdep_ReadLinkAt)(__AT_FDCWD, __path, __buf, __buflen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ReadLink_defined
#define __local___localdep_ReadLink_defined
#define __localdep_ReadLink __LIBC_LOCAL_NAME(ReadLink)
#endif /* !__local___localdep_ReadLink_defined */
#else /* __AT_FDCWD && __CRT_HAVE_ReadLinkAt */
#undef __local_ReadLink_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_ReadLinkAt */
#endif /* !__local_ReadLink_defined */
