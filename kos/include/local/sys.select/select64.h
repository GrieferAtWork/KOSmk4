/* HASH 0x51ed88d8 */
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
#ifndef __local_select64_defined
#if defined(__CRT_HAVE_select)
#define __local_select64_defined 1
/* Dependency: "select32" from "sys.select" */
#ifndef ____localdep_select32_defined
#define ____localdep_select32_defined 1
#if defined(__CRT_HAVE_select)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_select32,(int __nfds, fd_set *__restrict __readfds, fd_set *__restrict __writefds, fd_set *__restrict __exceptfds, struct __timeval32 *__restrict __timeout),select,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#else /* LIBC: select */
#undef ____localdep_select32_defined
#endif /* select32... */
#endif /* !____localdep_select32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(select64) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(select64))(int __nfds,
                                                      fd_set *__restrict __readfds,
                                                      fd_set *__restrict __writefds,
                                                      fd_set *__restrict __exceptfds,
                                                      struct __timeval64 *__restrict __timeout) {
#line 161 "kos/src/libc/magic/sys.select.c"
	struct __timeval32 __tmv;
	if (!__timeout)
		return __localdep_select32(__nfds, __readfds, __writefds, __exceptfds, __NULLPTR);
	__tmv.tv_sec  = (__time32_t)__timeout->tv_sec;
	__tmv.tv_usec = __timeout->tv_usec;
	return __localdep_select32(__nfds, __readfds, __writefds, __exceptfds, &__tmv);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_select) */
#endif /* !__local_select64_defined */
