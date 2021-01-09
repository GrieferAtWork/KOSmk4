/* HASH CRC-32:0x77044b39 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fdwalk_defined
#define __local_fdwalk_defined 1
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl)) && defined(__F_NEXT)
#ifndef ____fdwalk_func_t_defined
#define ____fdwalk_func_t_defined 1
typedef int (__LIBKCALL *__fdwalk_func_t)(void *__cookie, __fd_t __fd);
#endif /* !____fdwalk_func_t_defined */
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fcntl from fcntl */
#ifndef __local___localdep_fcntl_defined
#define __local___localdep_fcntl_defined 1
#ifdef __CRT_HAVE_fcntl
__NAMESPACE_LOCAL_END
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd),fcntl,(__fd,__cmd),__cmd,1,(void *))
#elif defined(__CRT_HAVE___fcntl)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd),__fcntl,(__fd,__cmd),__cmd,1,(void *))
#else /* ... */
#undef __local___localdep_fcntl_defined
#endif /* !... */
#endif /* !__local___localdep_fcntl_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Enumerate all open file descriptors by invoking `(*func)(cookie, FD)' for each of them
 * If during any of these invocations, `(*func)(...)' returns non-zero, enumeration stops,
 * and `fdwalk()' returns with that same value. If `(*func)(...)' is never called, or all
 * invocations return 0, `fdwalk()' will also return 0. */
__LOCAL_LIBC(fdwalk) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fdwalk))(__fdwalk_func_t __func, void *__cookie) {
	int __result = 0;
#ifdef __libc_geterrno
	__errno_t __saved_err;
#endif /* __libc_geterrno */
	__fd_t __fd = 0;
	for (;;) {
#ifdef __libc_geterrno
		__saved_err = __libc_geterrno();
#endif /* __libc_geterrno */
		/* fcntl(F_NEXT) returns the next valid (i.e.
		 * currently open) FD that is >= the given FD. */
		__fd = __localdep_fcntl(__fd, __F_NEXT);
		if (__fd < 0) {
#ifdef __libc_geterrno
			__libc_seterrno(__saved_err);
#endif /* __libc_geterrno */
			break;
		}
		__result = (*__func)(__cookie, __fd);
		if (__result != 0)
			break;
		++__fd;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fdwalk_defined
#define __local___localdep_fdwalk_defined 1
#define __localdep_fdwalk __LIBC_LOCAL_NAME(fdwalk)
#endif /* !__local___localdep_fdwalk_defined */
#else /* (__CRT_HAVE_fcntl || __CRT_HAVE___fcntl) && __F_NEXT */
#undef __local_fdwalk_defined
#endif /* (!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl) || !__F_NEXT */
#endif /* !__local_fdwalk_defined */
