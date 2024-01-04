/* HASH CRC-32:0xafbdb6 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_if_indextoname_defined
#define __local_if_indextoname_defined
#include <__crt.h>
#include <asm/os/socket-ioctls.h>
#include <asm/os/socket.h>
#include <features.h>
#include <bits/types.h>
#if ((defined(__CRT_HAVE_socket) || defined(__CRT_HAVE___socket)) && defined(__SOCK_DGRAM) && (defined(__AF_LOCAL) || defined(__AF_INET) || defined(__AF_INET6)) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__SIOCGIFNAME)) || defined(__CRT_HAVE_if_nameindex)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
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
#if defined(__CRT_HAVE_ioctl) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl_time64,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE_ioctl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl_time64)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl_time64,(__fd,__request),__request,1,(void *))
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
__LOCAL_LIBC(if_indextoname) __ATTR_OUT(2) char *
__NOTHROW_RPC_KOS(__LIBCCALL __LIBC_LOCAL_NAME(if_indextoname))(__STDC_UINT_AS_SIZE_T __ifindex, char *__ifname) {
#if (defined(__CRT_HAVE_socket) || defined(__CRT_HAVE___socket)) && defined(__SOCK_DGRAM) && (defined(__AF_LOCAL) || defined(__AF_INET) || defined(__AF_INET6)) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__SIOCGIFNAME)
	int __ok;
	__fd_t __sockfd;
	struct ifreq __req;
	__sockfd = (__NAMESPACE_LOCAL_SYM __localdep_opensock)();
	if __unlikely(__sockfd < 0)
		goto __err;
	__req.ifr_ifindex = __ifindex;
	__ok = (__NAMESPACE_LOCAL_SYM __localdep_ioctl)(__sockfd, __SIOCGIFNAME, &__req);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	(void)(__NAMESPACE_LOCAL_SYM __localdep_close)(__sockfd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	if __unlikely(__ok < 0) {
#if defined(__libc_geterrno) && defined(__ENODEV) && defined(__ENXIO)
		if (__libc_geterrno() == __ENODEV)
			__libc_seterrno(__ENXIO);
#endif /* __libc_geterrno && __ENODEV && __ENXIO */
		goto __err;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_strncpy)(__ifname, __req.ifr_name, __IF_NAMESIZE);
#else /* (__CRT_HAVE_socket || __CRT_HAVE___socket) && __SOCK_DGRAM && (__AF_LOCAL || __AF_INET || __AF_INET6) && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __SIOCGIFNAME */
	__SIZE_TYPE__ __i;
	struct if_nameindex *__index = (__NAMESPACE_LOCAL_SYM __localdep_if_nameindex)();
	if __unlikely(!__index)
		goto __err;
	for (__i = 0; __index[__i].if_name; ++__i) {
		if (__index[__i].if_index == __ifindex) {
			(__NAMESPACE_LOCAL_SYM __localdep_strncpy)(__ifname, __index[__i].if_name, __IF_NAMESIZE);
#if defined(__CRT_HAVE_if_freenameindex) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			(__NAMESPACE_LOCAL_SYM __localdep_if_freenameindex)(__index);
#endif /* __CRT_HAVE_if_freenameindex || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
			return __ifname;
		}
	}
#ifdef __ENXIO
	(void)__libc_seterrno(__ENXIO);
#else /* __ENXIO */
	(void)__libc_seterrno(1);
#endif /* !__ENXIO */
__err_index:
#if defined(__CRT_HAVE_if_freenameindex) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_if_freenameindex)(__index);
#endif /* __CRT_HAVE_if_freenameindex || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#endif /* (!__CRT_HAVE_socket && !__CRT_HAVE___socket) || !__SOCK_DGRAM || (!__AF_LOCAL && !__AF_INET && !__AF_INET6) || (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl && !__CRT_HAVE___ioctl_time64) || !__SIOCGIFNAME */
__err:
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_if_indextoname_defined
#define __local___localdep_if_indextoname_defined
#define __localdep_if_indextoname __LIBC_LOCAL_NAME(if_indextoname)
#endif /* !__local___localdep_if_indextoname_defined */
#else /* ((__CRT_HAVE_socket || __CRT_HAVE___socket) && __SOCK_DGRAM && (__AF_LOCAL || __AF_INET || __AF_INET6) && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __SIOCGIFNAME) || __CRT_HAVE_if_nameindex */
#undef __local_if_indextoname_defined
#endif /* ((!__CRT_HAVE_socket && !__CRT_HAVE___socket) || !__SOCK_DGRAM || (!__AF_LOCAL && !__AF_INET && !__AF_INET6) || (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl && !__CRT_HAVE___ioctl_time64) || !__SIOCGIFNAME) && !__CRT_HAVE_if_nameindex */
#endif /* !__local_if_indextoname_defined */
