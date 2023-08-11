/* HASH CRC-32:0x1cdfe7ca */
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
#ifndef __local_if_nametoindex_defined
#define __local_if_nametoindex_defined
#include <__crt.h>
#include <asm/os/socket-ioctls.h>
#include <asm/os/socket.h>
#if ((defined(__CRT_HAVE_socket) || defined(__CRT_HAVE___socket)) && defined(__SOCK_DGRAM) && (defined(__AF_LOCAL) || defined(__AF_INET) || defined(__AF_INET6)) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__SIOCGIFINDEX)) || defined(__CRT_HAVE_if_nameindex)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_if_freenameindex_defined
#define __local___localdep_if_freenameindex_defined
#ifdef __CRT_HAVE_if_freenameindex
__NAMESPACE_LOCAL_END
#include <bits/crt/if_nameindex.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_if_freenameindex,(struct if_nameindex *__ptr),if_freenameindex,(__ptr))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
__NAMESPACE_LOCAL_END
#include <libc/local/net.if/if_freenameindex.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_if_freenameindex __LIBC_LOCAL_NAME(if_freenameindex)
#else /* ... */
#undef __local___localdep_if_freenameindex_defined
#endif /* !... */
#endif /* !__local___localdep_if_freenameindex_defined */
#if !defined(__local___localdep_if_nameindex_defined) && defined(__CRT_HAVE_if_nameindex)
#define __local___localdep_if_nameindex_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/if_nameindex.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,struct if_nameindex *,__NOTHROW_RPC_KOS,__localdep_if_nameindex,(void),if_nameindex,())
#endif /* !__local___localdep_if_nameindex_defined && __CRT_HAVE_if_nameindex */
#ifndef __local___localdep_ioctl_defined
#define __local___localdep_ioctl_defined
#ifdef __CRT_HAVE_ioctl
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#else /* ... */
#undef __local___localdep_ioctl_defined
#endif /* !... */
#endif /* !__local___localdep_ioctl_defined */
#if !defined(__local___localdep_opensock_defined) && (defined(__CRT_HAVE_socket) || defined(__CRT_HAVE___socket)) && defined(__SOCK_DGRAM) && (defined(__AF_LOCAL) || defined(__AF_INET) || defined(__AF_INET6))
#define __local___localdep_opensock_defined
__NAMESPACE_LOCAL_END
#include <libc/local/net.if/opensock.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_opensock __LIBC_LOCAL_NAME(opensock)
#endif /* !__local___localdep_opensock_defined && (__CRT_HAVE_socket || __CRT_HAVE___socket) && __SOCK_DGRAM && (__AF_LOCAL || __AF_INET || __AF_INET6) */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
#ifndef __local___localdep_strncpy_defined
#define __local___localdep_strncpy_defined
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,{ return __builtin_strncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_strncpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strncpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strncpy __LIBC_LOCAL_NAME(strncpy)
#endif /* !... */
#endif /* !__local___localdep_strncpy_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/net-if.h>
#include <bits/crt/if_nameindex.h>
#include <hybrid/typecore.h>
#include <bits/os/ifreq.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(if_nametoindex) __ATTR_IN(1) __STDC_UINT_AS_SIZE_T
__NOTHROW_RPC_KOS(__LIBCCALL __LIBC_LOCAL_NAME(if_nametoindex))(char const *__ifname) {
#if (defined(__CRT_HAVE_socket) || defined(__CRT_HAVE___socket)) && defined(__SOCK_DGRAM) && (defined(__AF_LOCAL) || defined(__AF_INET) || defined(__AF_INET6)) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__SIOCGIFINDEX)
	int __ok;
	__fd_t __sockfd;
	struct ifreq __req;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_strlen)(__ifname) >= __IF_NAMESIZE) {
#ifdef __ENODEV
		(void)__libc_seterrno(__ENODEV);
#else /* __ENODEV */
		(void)__libc_seterrno(1);
#endif /* !__ENODEV */
		goto __err;
	}
	__sockfd = (__NAMESPACE_LOCAL_SYM __localdep_opensock)();
	if __unlikely(__sockfd < 0)
		goto __err;
	(__NAMESPACE_LOCAL_SYM __localdep_strncpy)(__req.ifr_name, __ifname, __IF_NAMESIZE);
	__ok = (__NAMESPACE_LOCAL_SYM __localdep_ioctl)(__sockfd, __SIOCGIFINDEX, &__req);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	(void)(__NAMESPACE_LOCAL_SYM __localdep_close)(__sockfd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	if __unlikely(__ok < 0)
		goto __err;
	return __req.ifr_ifindex;
#else /* (__CRT_HAVE_socket || __CRT_HAVE___socket) && __SOCK_DGRAM && (__AF_LOCAL || __AF_INET || __AF_INET6) && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __SIOCGIFINDEX */
	__SIZE_TYPE__ __i;
	struct if_nameindex *__index = (__NAMESPACE_LOCAL_SYM __localdep_if_nameindex)();
	if __unlikely(!__index)
		goto __err;
	for (__i = 0; __index[__i].if_name; ++__i) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__index[__i].if_name, __ifname) == 0) {
			__STDC_UINT_AS_SIZE_T __result = __index[__i].if_index;
#if defined(__CRT_HAVE_if_freenameindex) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			(__NAMESPACE_LOCAL_SYM __localdep_if_freenameindex)(__index);
#endif /* __CRT_HAVE_if_freenameindex || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
			return __result;
		}
	}
#ifdef __ENODEV
	(void)__libc_seterrno(__ENODEV);
#else /* __ENODEV */
	(void)__libc_seterrno(1);
#endif /* !__ENODEV */
__err_index:
#if defined(__CRT_HAVE_if_freenameindex) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_if_freenameindex)(__index);
#endif /* __CRT_HAVE_if_freenameindex || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#endif /* (!__CRT_HAVE_socket && !__CRT_HAVE___socket) || !__SOCK_DGRAM || (!__AF_LOCAL && !__AF_INET && !__AF_INET6) || (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__SIOCGIFINDEX */
__err:
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_if_nametoindex_defined
#define __local___localdep_if_nametoindex_defined
#define __localdep_if_nametoindex __LIBC_LOCAL_NAME(if_nametoindex)
#endif /* !__local___localdep_if_nametoindex_defined */
#else /* ((__CRT_HAVE_socket || __CRT_HAVE___socket) && __SOCK_DGRAM && (__AF_LOCAL || __AF_INET || __AF_INET6) && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __SIOCGIFINDEX) || __CRT_HAVE_if_nameindex */
#undef __local_if_nametoindex_defined
#endif /* ((!__CRT_HAVE_socket && !__CRT_HAVE___socket) || !__SOCK_DGRAM || (!__AF_LOCAL && !__AF_INET && !__AF_INET6) || (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__SIOCGIFINDEX) && !__CRT_HAVE_if_nameindex */
#endif /* !__local_if_nametoindex_defined */
