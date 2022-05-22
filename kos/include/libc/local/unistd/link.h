/* HASH CRC-32:0xede46b8 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_link_defined
#define __local_link_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_linkat)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_linkat_defined
#define __local___localdep_linkat_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(4),int,__NOTHROW_RPC,__localdep_linkat,(__fd_t __fromfd, char const *__from, __fd_t __tofd, char const *__to, __atflag_t __flags),linkat,(__fromfd,__from,__tofd,__to,__flags))
#endif /* !__local___localdep_linkat_defined */
__LOCAL_LIBC(link) __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(link))(char const *__from, char const *__to) {
	/* TODO: Header-implementation for `link()' on DOS (using the windows API) */
	return (__NAMESPACE_LOCAL_SYM __localdep_linkat)(__AT_FDCWD, __from, __AT_FDCWD, __to, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_link_defined
#define __local___localdep_link_defined
#define __localdep_link __LIBC_LOCAL_NAME(link)
#endif /* !__local___localdep_link_defined */
#else /* __AT_FDCWD && __CRT_HAVE_linkat */
#undef __local_link_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_linkat */
#endif /* !__local_link_defined */
