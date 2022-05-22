/* HASH CRC-32:0xb3b2d471 */
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
#ifndef __local_getpassfd_defined
#define __local_getpassfd_defined
#include <__crt.h>
#if defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_isatty_defined
#define __local___localdep_isatty_defined
#ifdef __CRT_HAVE_isatty
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),isatty,(__fd))
#elif defined(__CRT_HAVE__isatty)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),_isatty,(__fd))
#elif defined(__CRT_HAVE___isatty)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),__isatty,(__fd))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/tty.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/isatty.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isatty __LIBC_LOCAL_NAME(isatty)
#else /* __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA) */
#undef __local___localdep_isatty_defined
#endif /* !__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA) */
#endif /* !... */
#endif /* !__local___localdep_isatty_defined */
#ifndef __local___localdep_isprint_defined
#define __local___localdep_isprint_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isprint) && defined(__CRT_HAVE_isprint)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint,(int __ch),isprint,{ return __crt_isprint(__ch); })
#elif defined(__crt_isprint)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isprint)(int __ch) { return __crt_isprint(__ch); }
#elif __has_builtin(__builtin_isprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isprint)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint,(int __ch),isprint,{ return __builtin_isprint(__ch); })
#elif defined(__CRT_HAVE_isprint)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint,(int __ch),isprint,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isprint.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isprint __LIBC_LOCAL_NAME(isprint)
#endif /* !... */
#endif /* !__local___localdep_isprint_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined
#ifdef __CRT_HAVE_memcmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE___gcc_bcmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),__gcc_bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_memcmp_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined
#ifdef __CRT_HAVE_memcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined
#ifdef __CRT_HAVE_memset
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined
__NAMESPACE_LOCAL_END
#include <asm/os/oflags.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local___localdep_open_defined
#endif /* !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !... */
#endif /* !__local___localdep_open_defined */
#ifndef __local___localdep_poll_defined
#define __local___localdep_poll_defined
#ifdef __CRT_HAVE_poll
__NAMESPACE_LOCAL_END
#include <bits/os/pollfd.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RWS(1, 2),int,__NOTHROW_RPC,__localdep_poll,(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, int __timeout),poll,(__fds,__nfds,__timeout))
#elif defined(__CRT_HAVE___poll)
__NAMESPACE_LOCAL_END
#include <bits/os/pollfd.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RWS(1, 2),int,__NOTHROW_RPC,__localdep_poll,(struct pollfd *__fds, __UINTPTR_TYPE__ __nfds, int __timeout),__poll,(__fds,__nfds,__timeout))
#else /* ... */
#undef __local___localdep_poll_defined
#endif /* !... */
#endif /* !__local___localdep_poll_defined */
#ifndef __local___localdep_raise_defined
#define __local___localdep_raise_defined
#ifdef __CRT_HAVE_raise
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_raise,(__signo_t __signo),raise,(__signo))
#elif ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self))) || ((defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
__NAMESPACE_LOCAL_END
#include <libc/local/signal/raise.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_raise __LIBC_LOCAL_NAME(raise)
#else /* ... */
#undef __local___localdep_raise_defined
#endif /* !... */
#endif /* !__local___localdep_raise_defined */
#ifndef __local___localdep_read_defined
#define __local___localdep_read_defined
#ifdef __CRT_HAVE_read
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__libc_read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
#ifndef __local___localdep_tcgetattr_defined
#define __local___localdep_tcgetattr_defined
#ifdef __CRT_HAVE_tcgetattr
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),tcgetattr,(__fd,__termios_p))
#elif defined(__CRT_HAVE___tcgetattr)
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WR(2),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),__tcgetattr,(__fd,__termios_p))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/tty.h>
__NAMESPACE_LOCAL_BEGIN
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA)
__NAMESPACE_LOCAL_END
#include <libc/local/termios/tcgetattr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tcgetattr __LIBC_LOCAL_NAME(tcgetattr)
#else /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA */
#undef __local___localdep_tcgetattr_defined
#endif /* (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA */
#endif /* !... */
#endif /* !__local___localdep_tcgetattr_defined */
#ifndef __local___localdep_tcsetattr_defined
#define __local___localdep_tcsetattr_defined
#ifdef __CRT_HAVE_tcsetattr
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(3),int,__NOTHROW_NCX,__localdep_tcsetattr,(__fd_t __fd, __STDC_INT_AS_UINT_T __optional_actions, struct termios const *__restrict __termios_p),tcsetattr,(__fd,__optional_actions,__termios_p))
#elif defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)
__NAMESPACE_LOCAL_END
#include <libc/local/termios/tcsetattr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tcsetattr __LIBC_LOCAL_NAME(tcsetattr)
#else /* ... */
#undef __local___localdep_tcsetattr_defined
#endif /* !... */
#endif /* !__local___localdep_tcsetattr_defined */
#ifndef __local___localdep_tolower_defined
#define __local___localdep_tolower_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_tolower) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __crt_tolower(__ch); })
#elif defined(__crt_tolower)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_tolower)(int __ch) { return __crt_tolower(__ch); }
#elif __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/tolower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower __LIBC_LOCAL_NAME(tolower)
#endif /* !... */
#endif /* !__local___localdep_tolower_defined */
#ifndef __local___localdep_toupper_defined
#define __local___localdep_toupper_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_toupper) && defined(__CRT_HAVE_toupper)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),toupper,{ return __crt_toupper(__ch); })
#elif defined(__crt_toupper)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_toupper)(int __ch) { return __crt_toupper(__ch); }
#elif __has_builtin(__builtin_toupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_toupper)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),toupper,{ return __builtin_toupper(__ch); })
#elif defined(__CRT_HAVE_toupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),toupper,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/toupper.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toupper __LIBC_LOCAL_NAME(toupper)
#endif /* !... */
#endif /* !__local___localdep_toupper_defined */
#ifndef __local___localdep_write_defined
#define __local___localdep_write_defined
#ifdef __CRT_HAVE_write
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_write)
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__libc_write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_write_defined
#endif /* !... */
#endif /* !__local___localdep_write_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/stdio.h>
#include <asm/os/oflags.h>
#include <libc/errno.h>
#include <paths.h>
#include <asm/crt/getpassfd.h>
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <asm/os/signal.h>
#include <bits/os/pollfd.h>
#include <asm/os/poll.h>
#include <libc/strings.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getpassfd) __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RO_OPT(4) __ATTR_ACCESS_WR_OPT(2) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpassfd))(char const *__prompt, char *__buf, __SIZE_TYPE__ __buflen, __fd_t __fds[3], __STDC_INT_AS_UINT_T __flags, int __timeout_in_seconds) {
#ifndef __STDIN_FILENO
#define __STDIN_FILENO 0
#endif /* !__STDIN_FILENO */
#ifndef __STDERR_FILENO
#define __STDERR_FILENO 2
#endif /* !__STDERR_FILENO */

#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
	__BOOL __heap_buf;
#endif /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
	char *__result;
	__fd_t __default_fds[3];
	__signo_t __interrupt_signo;

	/* Initialize locals. */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	struct termios __old_ios, __new_ios;
	(__NAMESPACE_LOCAL_SYM __localdep_memset)(&__old_ios, -1, sizeof(__old_ios));
	(__NAMESPACE_LOCAL_SYM __localdep_memset)(&__new_ios, -1, sizeof(__new_ios));
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
	__result          = __NULLPTR;
	__interrupt_signo = 0;
	__default_fds[0]  = __STDIN_FILENO;

	/* Allocate a dynamic buffer if none was given by the caller. */
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
	__heap_buf = 0;
	if (!__buf) {
		__buflen = 512;
		__buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__buflen * sizeof(char));
		if __unlikely(!__buf) {
			__buflen = 1;
			__buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__buflen * sizeof(char));
			if __unlikely(!__buf)
				goto ___out;
		}
		__heap_buf = 1;
	} else
#endif /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
	if (__buflen < 1) {
		/* Invalid buffer length */
#ifdef __EINVAL
		(void)__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
		goto ___out;
	}

	/* Open input files if not provided by the caller. */
	if (!__fds) {
		__fds = __default_fds;
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#ifdef __O_CLOEXEC
#define __PRIVATE_GETPASSFD_O_CLOEXEC __O_CLOEXEC
#else /* __O_CLOEXEC */
#define __PRIVATE_GETPASSFD_O_CLOEXEC 0
#endif /* !__O_CLOEXEC */
#ifdef __O_CLOFORK
#define __PRIVATE_GETPASSFD_O_CLOFORK __O_CLOFORK
#else /* __O_CLOFORK */
#define __PRIVATE_GETPASSFD_O_CLOFORK 0
#endif /* !__O_CLOFORK */
#ifdef __O_RDWR
#define __PRIVATE_GETPASSFD_O_RDWR __O_RDWR
#else /* __O_RDWR */
#define __PRIVATE_GETPASSFD_O_RDWR 0
#endif /* !__O_RDWR */
#if defined(__O_NONBLOCK) && (defined(__CRT_HAVE_poll) || defined(__CRT_HAVE___poll))
#define __PRIVATE_GETPASSFD_O_NONBLOCK __O_NONBLOCK
#else /* __O_NONBLOCK && (__CRT_HAVE_poll || __CRT_HAVE___poll) */
#define __PRIVATE_GETPASSFD_O_NONBLOCK 0
#endif /* !__O_NONBLOCK || (!__CRT_HAVE_poll && !__CRT_HAVE___poll) */
#ifdef _PATH_TTY
#define __PRIVATE_GETPASSFD_PATH_TTY _PATH_TTY
#elif defined(_WIN32)
#define __PRIVATE_GETPASSFD_PATH_TTY "CON"
#else /* ... */
#define __PRIVATE_GETPASSFD_PATH_TTY "/dev/tty"
#endif /* !... */
#if __PRIVATE_GETPASSFD_O_NONBLOCK != 0
		__default_fds[2] = (__NAMESPACE_LOCAL_SYM __localdep_open)(__PRIVATE_GETPASSFD_PATH_TTY,
		                      __PRIVATE_GETPASSFD_O_CLOEXEC |
		                      __PRIVATE_GETPASSFD_O_CLOFORK |
		                      __PRIVATE_GETPASSFD_O_RDWR |
		                      (__timeout_in_seconds != 0 ? __PRIVATE_GETPASSFD_O_NONBLOCK : 0));
#else /* __PRIVATE_GETPASSFD_O_NONBLOCK != 0 */
		__default_fds[2] = (__NAMESPACE_LOCAL_SYM __localdep_open)(__PRIVATE_GETPASSFD_PATH_TTY,
		                      __PRIVATE_GETPASSFD_O_CLOEXEC |
		                      __PRIVATE_GETPASSFD_O_CLOFORK |
		                      __PRIVATE_GETPASSFD_O_RDWR);
#endif /* __PRIVATE_GETPASSFD_O_NONBLOCK == 0 */
		if (__default_fds[2] != -1) {
			__default_fds[0] = __default_fds[2];
			__default_fds[1] = __default_fds[2];
		} else
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
		{
			__default_fds[1] = __STDERR_FILENO;
			__default_fds[2] = __STDERR_FILENO;
		}
	}

	/* Load terminal settings. */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if ((__NAMESPACE_LOCAL_SYM __localdep_tcgetattr)(__fds[0], &__old_ios) == 0) {
		(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(&__new_ios, &__old_ios, sizeof(struct termios));

		/* Configure new settings. */
#if defined(__ECHO) || defined(__ECHOK) || defined(__ECHOE) || defined(__ECHOKE) || defined(__ECHOCTL) || defined(__ISIG) || defined(__ICANON)
		__new_ios.c_lflag &= ~(0 |
#ifdef __ECHO
		                       __ECHO |
#endif /* __ECHO */
#ifdef __ECHOK
		                       __ECHOK |
#endif /* __ECHOK */
#ifdef __ECHOE
		                       __ECHOE |
#endif /* __ECHOE */
#ifdef __ECHOKE
		                       __ECHOKE |
#endif /* __ECHOKE */
#ifdef __ECHOCTL
		                       __ECHOCTL |
#endif /* __ECHOCTL */
#ifdef __ISIG
		                       __ISIG |
#endif /* __ISIG */
#ifdef __ICANON
		                       __ICANON
#endif /* __ICANON */
		                       );
#endif /* __ECHO || __ECHOK || __ECHOE || __ECHOKE || __ECHOCTL || __ISIG || __ICANON */

#ifdef __VMIN
		__new_ios.c_cc[__VMIN] = 1;
#endif /* __VMIN */
#ifdef __VTIME
		__new_ios.c_cc[__VTIME] = 0;
#endif /* __VTIME */

#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		if ((__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__fds[0], __TCSAFLUSH | __TCSASOFT, &__new_ios) != 0)
#elif defined(__TCSAFLUSH)
		if ((__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__fds[0], __TCSAFLUSH, &__new_ios) != 0)
#else /* ... */
		if ((__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__fds[0], 0, &__new_ios) != 0)
#endif /* !... */
		{
			goto ___out;
		}
	} else {
		if (__flags & __GETPASS_NEED_TTY)
			goto ___out; /* tcgetattr() should have already set errno=ENOTTY */
	}
#elif defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty) || defined(__CRT_HAVE___isatty) || defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
	if ((__flags & __GETPASS_NEED_TTY) && !(__NAMESPACE_LOCAL_SYM __localdep_isatty)(__fds[0]))
		goto ___out; /* isatty() should have already set errno=ENOTTY */
#endif /* ... */

	/* Print the given prompt */
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
	if (__prompt && *__prompt) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_write)(__fds[1], __prompt, (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__prompt)) == -1)
			goto ___out;
	}
#else /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
	(void)__prompt;
#endif /* !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write */

	/* The actual interpreter loop for the password reader: */
	{
		unsigned char __ch, *__dst, *__bufend;
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__VLNEXT)
		__BOOL __escape; /* Set to `true' if the next character is escaped. */
		__escape = 0;
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __VLNEXT */
		__dst    = (unsigned char *)__buf;
		__bufend = (unsigned char *)__buf + __buflen - 1;
		for (;;) {

#if defined(__CRT_HAVE_poll) || defined(__CRT_HAVE___poll)
			if (__timeout_in_seconds != 0) {
				int __status;
				struct pollfd __pfd;
				__pfd.fd      = __fds[0];
#if defined(__POLLIN) && defined(__POLLRDNORM)
				__pfd.events  = __POLLIN | __POLLRDNORM;
#elif defined(__POLLIN)
				__pfd.events  = __POLLIN;
#else /* ... */
				__pfd.events  = 0;
#endif /* !... */
				__status = (__NAMESPACE_LOCAL_SYM __localdep_poll)(&__pfd, 1, __timeout_in_seconds * 1000);
				if __unlikely(__status == -1)
					goto ___out; /* Error... */
				if __unlikely(__status == 0) {
#ifdef __ETIMEDOUT
					(void)__libc_seterrno(__ETIMEDOUT);
#else /* __ETIMEDOUT */
					(void)__libc_seterrno(1);
#endif /* !__ETIMEDOUT */
					goto ___out; /* Timeout... */
				}
				/* Assume that data can be read now! */
			}
#else /* __CRT_HAVE_poll || __CRT_HAVE___poll */
			(void)__timeout_in_seconds;
#endif /* !__CRT_HAVE_poll && !__CRT_HAVE___poll */

			/* Actually read the next character. */
			{
				__SSIZE_TYPE__ __status;
				__status = (__NAMESPACE_LOCAL_SYM __localdep_read)(__fds[0], &__ch, sizeof(__ch));
				if (__status < (__SSIZE_TYPE__)sizeof(char)) {
					if (__status < 0)
						goto ___out; /* Error */
#ifdef __VEOF
__handle_eof:
#endif /* __VEOF */
					if (__flags & __GETPASS_FAIL_EOF) {
						/* Error out on regular, old EOF */
#ifdef __ENODATA
						(void)__libc_seterrno(__ENODATA);
#endif /* __ENODATA */
						goto ___out;
					}
					break;
				}
			}

#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__VLNEXT)
			if (__escape) {
				/* Unconditionally add `ch' */
				__escape = 0;
			} else
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __VLNEXT */
			{
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
#if !__VDISABLE
#define __PRIVATE_GETPASSFD_CTRL(__index, __defl) \
	(__new_ios.c_cc[__index] != '\0' ? __new_ios.c_cc[__index] : __CTRL(__defl))
#else /* !__VDISABLE */
#define __PRIVATE_GETPASSFD_CTRL(__index, __defl) \
	((__new_ios.c_cc[__index] != '\0' && __new_ios.c_cc[__index] != __VDISABLE) ? __new_ios.c_cc[__index] : __CTRL(__defl))
#endif /* __VDISABLE */

				/* Check for control characters that should be ignored. */
#ifdef __VREPRINT
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VREPRINT, 'R'))
					continue;
#endif /* __VREPRINT */

#ifdef __VSTART
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VSTART, 'Q'))
					continue;
#endif /* __VSTART */

#ifdef __VSTOP
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VSTOP, 'S'))
					continue;
#endif /* __VSTOP */

#ifdef __VSTATUS
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VSTATUS, 'T'))
					continue;
#endif /* __VSTATUS */

#ifdef __VDISCARD
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VDISCARD, 'O'))
					continue;
#endif /* __VDISCARD */

				/* Check for ^V */
#ifdef __VLNEXT
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VLNEXT, 'V')) {
					__escape = 1;
					continue;
				}
#endif /* __VLNEXT */

				/* Both line- and word-kill are treated as a full reset. */
#if defined(__VKILL) || defined(__VWERASE)
				if (
#ifdef __VKILL
				    __ch == __PRIVATE_GETPASSFD_CTRL(__VKILL, 'U')
#endif /* __VKILL */
#if defined(__VKILL) && defined(__VWERASE)
				    ||
#endif /* __VKILL && __VWERASE */
#ifdef __VWERASE
				    __ch == __PRIVATE_GETPASSFD_CTRL(__VWERASE, 'W')
#endif /* __VWERASE */
				    )
				{
					__libc_explicit_bzero(__buf, __buflen * sizeof(char));
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
					if (__flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
						while (__dst > (unsigned char *)__buf) {
							if ((__NAMESPACE_LOCAL_SYM __localdep_write)(__fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto ___out;
							--__dst;
						}
					}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
					__dst = (unsigned char *)__buf;
					continue;
				}
#endif /* __VKILL || __VWERASE */

				/* Check for end-of-file (via ^D) */
#ifdef __VEOF
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VEOF, 'D'))
					goto __handle_eof;
#endif /* __VEOF */

				/* Check for TTY signal characters. */
#if defined(__VINTR) && defined(__SIGINT)
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VINTR, 'C')) {
					__interrupt_signo = __SIGINT;
					goto ___out;
				}
#endif /* __VINTR && __SIGINT */

#if defined(__VQUIT) && defined(__SIGQUIT)
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VQUIT, '\\')) {
					__interrupt_signo = __SIGQUIT;
					goto ___out;
				}
#endif /* __VQUIT && __SIGQUIT */

#if (defined(__VSUSP) || defined(__VDSUSP)) && defined(__SIGTSTP)
				if (
#ifdef __VSUSP
				    __ch == __PRIVATE_GETPASSFD_CTRL(__VSUSP, 'Z')
#endif /* __VSUSP */
#if defined(__VSUSP) && defined(__VDSUSP)
				    ||
#endif /* __VSUSP && __VDSUSP */
#ifdef __VDSUSP
				    __ch == __PRIVATE_GETPASSFD_CTRL(__VDSUSP, 'Y')
#endif /* __VDSUSP */
				    ) {
					__interrupt_signo = __SIGTSTP;
					goto ___out;
				}
#endif /* (__VSUSP || __VDSUSP) && __SIGTSTP */

				/* Check for custom newline characters. */
#ifdef __VEOL
				if (__new_ios.c_cc[__VEOL] != __VDISABLE && __ch == __new_ios.c_cc[__VEOL])
					break;
#endif /* __VEOL */
#ifdef __VEOL2
				if (__new_ios.c_cc[__VEOL2] != __VDISABLE && __ch == __new_ios.c_cc[__VEOL2])
					break;
#endif /* __VEOL2 */
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */

				/* Check for single-character erase (backspace) */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__VERASE)
				if (__ch == __PRIVATE_GETPASSFD_CTRL(__VERASE, 'H'))
#else /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __VERASE */
				if (__ch == '\b')
#endif /* (!__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA)) || (!__CRT_HAVE_tcsetattr && !__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__VERASE */
				{
					if (__dst > (unsigned char *)__buf) {
						--__dst;
						__libc_explicit_bzero(__dst, sizeof(char));
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
						if (__flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
							if ((__NAMESPACE_LOCAL_SYM __localdep_write)(__fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto ___out;
						}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
						continue;
					}
__maybe_beep:
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
					if (!(__flags & __GETPASS_NO_BEEP)) {
						if ((__NAMESPACE_LOCAL_SYM __localdep_write)(__fds[2], "\7" /*BEL*/, sizeof(char)) == -1)
							goto ___out;
					}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
					continue;
				}

				/* Check for generic newline characters. */
				if (__ch == '\r' || __ch == '\n')
					break;

			} /* if (!escape) */

			/* Special case: _always_ stop when a NUL-character would be appended.
			 * Note  that this is  undocumented behavior, but  is also mirrored by
			 * what is done by NetBSD's implementation in this case. */
			if (__ch == '\0')
				break;

			/* Check if the buffer is full. */
			if (__dst >= __bufend) {
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
				if (__heap_buf) {
					/* Allocate more space. */
					__SIZE_TYPE__ __new_buflen;
					char *__new_buf;
					__new_buflen = __buflen * 2;
					__new_buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__new_buflen * sizeof(char));
					if __unlikely(!__new_buf) {
						__new_buflen = __buflen + 1;
						__new_buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__new_buflen * sizeof(char));
						if __unlikely(!__new_buf)
							goto ___out;
					}
					(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__new_buf, __buf, __buflen, sizeof(char));
					__libc_explicit_bzero(__buf, __buflen * sizeof(char));
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
					(__NAMESPACE_LOCAL_SYM __localdep_free)(__buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
					__dst    = (unsigned char *)__new_buf + (__SIZE_TYPE__)(__dst - (unsigned char *)__buf);
					__bufend = (unsigned char *)__new_buf + __new_buflen - 1;
					__buf    = __new_buf;
				} else
#endif /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
				{
					if (__flags & __GETPASS_BUF_LIMIT)
						goto __maybe_beep;
					continue;
				}
			}

			/* Deal with special character conversions. */
			if (__flags & __GETPASS_7BIT)
				__ch &= 0x7f;
			if (__flags & __GETPASS_FORCE_LOWER)
				__ch = (unsigned char)(__NAMESPACE_LOCAL_SYM __localdep_tolower)((char)__ch);
			if (__flags & __GETPASS_FORCE_UPPER)
				__ch = (unsigned char)(__NAMESPACE_LOCAL_SYM __localdep_toupper)((char)__ch);

			/* Append to the result buffer. */
			*__dst++ = __ch;

#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
			if (__flags & __GETPASS_ECHO_STAR) {
				if ((__NAMESPACE_LOCAL_SYM __localdep_write)(__fds[1], "*", sizeof(char)) == -1)
					goto ___out;
			} else if (__flags & __GETPASS_ECHO) {
				if (!(__NAMESPACE_LOCAL_SYM __localdep_isprint)((char)__ch))
					__ch = (unsigned char)'?';
				if ((__NAMESPACE_LOCAL_SYM __localdep_write)(__fds[1], &__ch, sizeof(char)) == -1)
					goto ___out;
			}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */

		} /* for (;;) */

		/* If requested to do so by the caller, write a trailing '\n' upon success. */
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
		if (__flags & __GETPASS_ECHO_NL) {
			if ((__NAMESPACE_LOCAL_SYM __localdep_write)(__fds[1], "\n", 1) == -1)
				goto ___out;
		}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */

		/* Force NUL-termination of the password buffer. */
		*__dst = '\0';

#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
		if (__heap_buf && __dst < __bufend) {
			/* Try to release unused buffer memory. */
			__SIZE_TYPE__ __new_buflen;
			char *__new_buf;
			__new_buflen = (__SIZE_TYPE__)((__dst + 1) - (unsigned char *)__buf);
			__new_buf    = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__new_buflen * sizeof(char));
			if __likely(__new_buf) {
				(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__new_buf, __buf, __new_buflen, sizeof(char));
				__libc_explicit_bzero(__buf, __buflen * sizeof(char));
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
				(__NAMESPACE_LOCAL_SYM __localdep_free)(__buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
				__buf    = __new_buf;
				__buflen = __new_buflen;
			}
		}
#endif /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */

		/* Indicate success! */
		__result = __buf;
	}
___out:

	/* Restore old terminal settings. */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if ((__NAMESPACE_LOCAL_SYM __localdep_memcmp)(&__old_ios, &__new_ios, sizeof(struct termios)) != 0) {
#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		(void)(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__fds[0], __TCSAFLUSH | __TCSASOFT, &__old_ios);
#elif defined(__TCSAFLUSH)
		(void)(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__fds[0], __TCSAFLUSH, &__old_ios);
#else /* ... */
		(void)(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__fds[0], 0, &__old_ios);
#endif /* !... */
	}
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */

	/* Close our file handle to /dev/tty */
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	if (__default_fds[0] != __STDIN_FILENO)
		(__NAMESPACE_LOCAL_SYM __localdep_close)(__default_fds[0]);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */

	/* Error-only cleanup... */
	if (!__result) {

		/* Don't leave a (possibly incomplete) password dangling in-memory! */
		__libc_explicit_bzero(__buf, __buflen * sizeof(char));

		/* Free a dynamically allocated password buffer. */
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
		if (__heap_buf)
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__buf);
#endif /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free) */

		/* Raise the signal of a given control character, and/or set
		 * `errno'  to indicate that the password-read operation was
		 * interrupted. */
		if (__interrupt_signo != 0) {
#if defined(__CRT_HAVE_raise) || ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self))) || ((defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
			if (!(__flags & __GETPASS_NO_SIGNAL))
				(void)(__NAMESPACE_LOCAL_SYM __localdep_raise)(__interrupt_signo);
#endif /* __CRT_HAVE_raise || ((__CRT_HAVE_pthread_kill || __CRT_HAVE_thr_kill) && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self)) || ((__CRT_HAVE_kill || __CRT_HAVE___kill || __CRT_HAVE___libc_kill) && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid || __CRT_HAVE___libc_getpid)) */
#ifdef __EINTR
			(void)__libc_seterrno(__EINTR);
#endif /* __EINTR */
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpassfd_defined
#define __local___localdep_getpassfd_defined
#define __localdep_getpassfd __LIBC_LOCAL_NAME(getpassfd)
#endif /* !__local___localdep_getpassfd_defined */
#else /* __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read */
#undef __local_getpassfd_defined
#endif /* !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read */
#endif /* !__local_getpassfd_defined */
