/* HASH CRC-32:0x762efdaf */
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
#ifndef __local_select_defined
#define __local_select_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_select64) || defined(__CRT_HAVE_select) || defined(__CRT_HAVE___select)
#include <features.h>
#include <bits/os/timeval.h>
#include <bits/os/fd_set.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_select32_defined
#define __local___localdep_select32_defined
#ifdef __CRT_HAVE_select
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_select32,(__STDC_INT_AS_SIZE_T __nfds, struct __fd_set_struct *__restrict __readfds, struct __fd_set_struct *__restrict __writefds, struct __fd_set_struct *__restrict __exceptfds, struct __timeval32 *__restrict __timeout),select,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE___select)
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_select32,(__STDC_INT_AS_SIZE_T __nfds, struct __fd_set_struct *__restrict __readfds, struct __fd_set_struct *__restrict __writefds, struct __fd_set_struct *__restrict __exceptfds, struct __timeval32 *__restrict __timeout),__select,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#else /* ... */
#undef __local___localdep_select32_defined
#endif /* !... */
#endif /* !__local___localdep_select32_defined */
#ifndef __local___localdep_select64_defined
#define __local___localdep_select64_defined
#if defined(__CRT_HAVE_select) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_select64,(__STDC_INT_AS_SIZE_T __nfds, struct __fd_set_struct *__restrict __readfds, struct __fd_set_struct *__restrict __writefds, struct __fd_set_struct *__restrict __exceptfds, struct __timeval64 *__restrict __timeout),select,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select64)
__CREDIRECT(__ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_select64,(__STDC_INT_AS_SIZE_T __nfds, struct __fd_set_struct *__restrict __readfds, struct __fd_set_struct *__restrict __writefds, struct __fd_set_struct *__restrict __exceptfds, struct __timeval64 *__restrict __timeout),select64,(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#elif defined(__CRT_HAVE_select) || defined(__CRT_HAVE___select)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.select/select64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_select64 __LIBC_LOCAL_NAME(select64)
#else /* ... */
#undef __local___localdep_select64_defined
#endif /* !... */
#endif /* !__local___localdep_select64_defined */
__LOCAL_LIBC(select) __ATTR_INOUT_OPT(2) __ATTR_INOUT_OPT(3) __ATTR_INOUT_OPT(4) __ATTR_INOUT_OPT(5) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(select))(__STDC_INT_AS_SIZE_T __nfds, struct __fd_set_struct *__restrict __readfds, struct __fd_set_struct *__restrict __writefds, struct __fd_set_struct *__restrict __exceptfds, struct timeval *__restrict __timeout) {

	struct __timeval64 __tmv;
	if (!__timeout)
		return (__NAMESPACE_LOCAL_SYM __localdep_select64)(__nfds, __readfds, __writefds, __exceptfds, __NULLPTR);
	__tmv.tv_sec  = (__time64_t)__timeout->tv_sec;
	__tmv.tv_usec = __timeout->tv_usec;
	return (__NAMESPACE_LOCAL_SYM __localdep_select64)(__nfds, __readfds, __writefds, __exceptfds, &__tmv);








}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_select_defined
#define __local___localdep_select_defined
#define __localdep_select __LIBC_LOCAL_NAME(select)
#endif /* !__local___localdep_select_defined */
#else /* __CRT_HAVE_select64 || __CRT_HAVE_select || __CRT_HAVE___select */
#undef __local_select_defined
#endif /* !__CRT_HAVE_select64 && !__CRT_HAVE_select && !__CRT_HAVE___select */
#endif /* !__local_select_defined */
