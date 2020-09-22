/* HASH CRC-32:0xcbaa780 */
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
#ifndef __local_remque_defined
#define __local_remque_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: link from unistd */
#ifndef __local___localdep_link_defined
#define __local___localdep_link_defined 1
#ifdef __CRT_HAVE_link
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_link,(char const *__from, char const *__to),link,(__from,__to))
#else /* __CRT_HAVE_link */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_linkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/link.h>
__NAMESPACE_LOCAL_BEGIN
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
#define __localdep_link __LIBC_LOCAL_NAME(link)
#else /* __AT_FDCWD && __CRT_HAVE_linkat */
#undef __local___localdep_link_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_linkat */
#endif /* !__CRT_HAVE_link */
#endif /* !__local___localdep_link_defined */
/* Unlink ELEM from the doubly-linked list that it is in */
__LOCAL_LIBC(remque) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(remque))(void *__restrict __elem) {
	struct __localdep_link {
		struct __localdep_link *__l_forw; /* [0..1] Forward link */
		struct __localdep_link *__l_back; /* [0..1] Backward link */
	};
	struct __localdep_link *__prev, *__next;
	__prev = ((struct __localdep_link *)__elem)->__l_back;
	__next = ((struct __localdep_link *)__elem)->__l_forw;
	if (__prev)
		__prev->__l_forw = __next;
	if (__next)
		__next->__l_back = __prev;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_remque_defined
#define __local___localdep_remque_defined 1
#define __localdep_remque __LIBC_LOCAL_NAME(remque)
#endif /* !__local___localdep_remque_defined */
#endif /* !__local_remque_defined */
