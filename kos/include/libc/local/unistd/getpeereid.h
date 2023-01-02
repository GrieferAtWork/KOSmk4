/* HASH CRC-32:0xf977de8f */
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
#ifndef __local_getpeereid_defined
#define __local_getpeereid_defined
#include <__crt.h>
#include <asm/os/socket.h>
#if defined(__CRT_HAVE_getsockopt) && defined(__SOL_SOCKET) && defined(__SO_PEERCRED)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getsockopt_defined
#define __local___localdep_getsockopt_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(5) __ATTR_OUT(4),int,__NOTHROW_NCX,__localdep_getsockopt,(__fd_t __sockfd, __STDC_INT_AS_UINT_T __level, __STDC_INT_AS_UINT_T __optname, void *__restrict __optval, __socklen_t *__restrict __optlen),getsockopt,(__sockfd,__level,__optname,__optval,__optlen))
#endif /* !__local___localdep_getsockopt_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/ucred.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getpeereid) __ATTR_OUT(2) __ATTR_OUT(3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getpeereid))(__fd_t __sockfd, __uid_t *__euid, __gid_t *__egid) {
	int __result;
	struct ucred __cred;
	__socklen_t __len = sizeof(__cred);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_getsockopt)(__sockfd, __SOL_SOCKET, __SO_PEERCRED, &__cred, &__len);
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
#define __local___localdep_getpeereid_defined
#define __localdep_getpeereid __LIBC_LOCAL_NAME(getpeereid)
#endif /* !__local___localdep_getpeereid_defined */
#else /* __CRT_HAVE_getsockopt && __SOL_SOCKET && __SO_PEERCRED */
#undef __local_getpeereid_defined
#endif /* !__CRT_HAVE_getsockopt || !__SOL_SOCKET || !__SO_PEERCRED */
#endif /* !__local_getpeereid_defined */
