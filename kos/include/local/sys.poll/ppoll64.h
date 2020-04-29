/* HASH CRC-32:0x3702117c */
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
#ifndef __local_ppoll64_defined
#ifdef __CRT_HAVE_ppoll
#define __local_ppoll64_defined 1
/* Dependency: "ppoll32" from "sys.poll" */
#ifndef ____localdep_ppoll32_defined
#define ____localdep_ppoll32_defined 1
#ifdef __CRT_HAVE_ppoll
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_ppoll32,(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, struct __timespec32 const *__timeout, struct __sigset_struct const *__ss),ppoll,(__fds,__nfds,__timeout,__ss))
#else /* LIBC: ppoll */
#undef ____localdep_ppoll32_defined
#endif /* ppoll32... */
#endif /* !____localdep_ppoll32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ppoll64) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(ppoll64))(struct pollfd *__fds,
                                                     __UINTPTR_TYPE__ __nfds,
                                                     struct __timespec64 const *__timeout,
                                                     struct __sigset_struct const *__ss) {
#line 117 "kos/src/libc/magic/sys.poll.c"
	struct __timespec32 __tmo32;
	if (!__timeout)
		return __localdep_ppoll32(__fds, __nfds, __NULLPTR, __ss);
	__tmo32.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tmo32.tv_nsec = __timeout->tv_nsec;
	return __localdep_ppoll32(__fds, __nfds, &__tmo32, __ss);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_ppoll */
#endif /* !__local_ppoll64_defined */
