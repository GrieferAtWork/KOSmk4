/* HASH CRC-32:0xa0cbe338 */
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
#ifndef __local_getpeereid_defined
#define __local_getpeereid_defined 1
#include <__crt.h>
#include <asm/os/socket.h>
#if defined(__CRT_HAVE_getsockopt) && defined(__SOL_SOCKET) && defined(__SO_PEERCRED)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getsockopt from sys.socket */
#ifndef __local___localdep_getsockopt_defined
#define __local___localdep_getsockopt_defined 1
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getsockopt(2)
 * Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the contents of `optval' are undefined.
 * @return: 0 : Success
 * @return: -1: [errno=ENOPROTOOPT] E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT */
__CREDIRECT(__ATTR_NONNULL((4, 5)),int,__NOTHROW_NCX,__localdep_getsockopt,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __level, __STDC_INT_AS_UINT_T __optname, void *__restrict __optval, __socklen_t *__restrict __optlen),getsockopt,(__sockfd,__level,__optname,__optval,__optlen))
#endif /* !__local___localdep_getsockopt_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/ucred.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
__LOCAL_LIBC(getpeereid) __ATTR_NONNULL((2, 3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getpeereid))(__fd_t __sockfd, __uid_t *__euid, __gid_t *__egid) {
	int __result;
	struct ucred __cred;
	__socklen_t __len = sizeof(__cred);
	__result = __localdep_getsockopt(__sockfd, __SOL_SOCKET, __SO_PEERCRED, &__cred, &__len);
	if (__result == 0) {
		/* Safety check that enough data was read... */
		if (__len < (__COMPILER_OFFSETAFTER(struct ucred, uid) >
		           __COMPILER_OFFSETAFTER(struct ucred, gid)
		           ? __COMPILER_OFFSETAFTER(struct ucred, uid)
		           : __COMPILER_OFFSETAFTER(struct ucred, gid))) {
#ifdef __ENOPROTOOPT
			__result = __libc_seterrno(__ENOPROTOOPT);
#else /* __ENOPROTOOPT */
			__result = __libc_seterrno(1);
#endif /* !__ENOPROTOOPT */
		} else {
			*__euid = __cred.uid;
			*__egid = __cred.gid;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpeereid_defined
#define __local___localdep_getpeereid_defined 1
#define __localdep_getpeereid __LIBC_LOCAL_NAME(getpeereid)
#endif /* !__local___localdep_getpeereid_defined */
#else /* __CRT_HAVE_getsockopt && __SOL_SOCKET && __SO_PEERCRED */
#undef __local_getpeereid_defined
#endif /* !__CRT_HAVE_getsockopt || !__SOL_SOCKET || !__SO_PEERCRED */
#endif /* !__local_getpeereid_defined */
