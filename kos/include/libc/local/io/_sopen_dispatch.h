/* HASH CRC-32:0xc21d18fb */
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
#ifndef __local__sopen_dispatch_defined
#define __local__sopen_dispatch_defined
#include <__crt.h>
#include <features.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE__sopen_s) || defined(__CRT_HAVE__sopen_s_nolock) || defined(__CRT_HAVE_sopen) || defined(__CRT_HAVE__sopen) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__sopen_s_defined
#define __local___localdep__sopen_s_defined
#ifdef __CRT_HAVE__sopen_s
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__errno_t,__NOTHROW_RPC,__localdep__sopen_s,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),_sopen_s,(__fd,__filename,__oflags,__sflags,__mode))
#elif defined(__CRT_HAVE__sopen_s_nolock)
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__errno_t,__NOTHROW_RPC,__localdep__sopen_s,(__fd_t *__fd, char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode),_sopen_s_nolock,(__fd,__filename,__oflags,__sflags,__mode))
#elif defined(__CRT_HAVE_sopen) || defined(__CRT_HAVE__sopen) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/io/_sopen_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__sopen_s __LIBC_LOCAL_NAME(_sopen_s)
#else /* ... */
#undef __local___localdep__sopen_s_defined
#endif /* !... */
#endif /* !__local___localdep__sopen_s_defined */
__LOCAL_LIBC(_sopen_dispatch) __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR(5) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_sopen_dispatch))(char const *__filename, __oflag_t __oflags, int __sflags, __mode_t __mode, __fd_t *__fd, int __bsecure) {
	(void)__bsecure;
	return (__NAMESPACE_LOCAL_SYM __localdep__sopen_s)(__fd, __filename, __oflags, __sflags, __mode);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__sopen_dispatch_defined
#define __local___localdep__sopen_dispatch_defined
#define __localdep__sopen_dispatch __LIBC_LOCAL_NAME(_sopen_dispatch)
#endif /* !__local___localdep__sopen_dispatch_defined */
#else /* __CRT_HAVE__sopen_s || __CRT_HAVE__sopen_s_nolock || __CRT_HAVE_sopen || __CRT_HAVE__sopen || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local__sopen_dispatch_defined
#endif /* !__CRT_HAVE__sopen_s && !__CRT_HAVE__sopen_s_nolock && !__CRT_HAVE_sopen && !__CRT_HAVE__sopen && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !__local__sopen_dispatch_defined */
