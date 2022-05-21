/* HASH CRC-32:0xd7ce328e */
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
#ifndef __local_readpassphrase_defined
#define __local_readpassphrase_defined
#include <__crt.h>
#include <asm/os/stdio.h>
#if defined(__STDIN_FILENO) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read))
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined
#ifdef __CRT_HAVE_bzero
__CREDIRECT_VOID(__ATTR_ACCESS_WRS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(__ATTR_ACCESS_WRS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_ACCESS_WRS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_getpid_defined
#define __local___localdep_getpid_defined
#ifdef __CRT_HAVE_getpid
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),getpid,())
#elif defined(__CRT_HAVE__getpid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),_getpid,())
#elif defined(__CRT_HAVE___getpid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__getpid,())
#elif defined(__CRT_HAVE___libc_getpid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,__localdep_getpid,(void),__libc_getpid,())
#else /* ... */
#undef __local___localdep_getpid_defined
#endif /* !... */
#endif /* !__local___localdep_getpid_defined */
#ifndef __local___localdep_kill_defined
#define __local___localdep_kill_defined
#ifdef __CRT_HAVE_kill
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_kill,(__pid_t __pid, __signo_t __signo),kill,(__pid,__signo))
#elif defined(__CRT_HAVE___kill)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_kill,(__pid_t __pid, __signo_t __signo),__kill,(__pid,__signo))
#elif defined(__CRT_HAVE___libc_kill)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_kill,(__pid_t __pid, __signo_t __signo),__libc_kill,(__pid,__signo))
#else /* ... */
#undef __local___localdep_kill_defined
#endif /* !... */
#endif /* !__local___localdep_kill_defined */
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined
#ifdef __CRT_HAVE_memcmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE___gcc_bcmp)
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
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined
__NAMESPACE_LOCAL_END
#include <asm/os/oflags.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
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
#ifndef __local___localdep_raise_defined
#define __local___localdep_raise_defined
#ifdef __CRT_HAVE_raise
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_WRS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__libc_read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
#ifndef __local___localdep_sigaction_defined
#define __local___localdep_sigaction_defined
#ifdef __CRT_HAVE_sigaction
__NAMESPACE_LOCAL_END
#include <bits/types.h>
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),sigaction,(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#else /* ... */
#undef __local___localdep_sigaction_defined
#endif /* !... */
#endif /* !__local___localdep_sigaction_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
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
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),tcgetattr,(__fd,__termios_p))
#elif defined(__CRT_HAVE___tcgetattr)
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),__tcgetattr,(__fd,__termios_p))
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
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,__localdep_tcsetattr,(__fd_t __fd, __STDC_INT_AS_UINT_T __optional_actions, struct termios const *__restrict __termios_p),tcsetattr,(__fd,__optional_actions,__termios_p))
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
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_write)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_ROS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__libc_write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_write_defined
#endif /* !... */
#endif /* !__local___localdep_write_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <asm/os/oflags.h>
#include <libc/errno.h>
#include <paths.h>
#include <asm/crt/readpassphrase.h>
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <asm/os/signal.h>
#include <bits/os/sigaction.h>
#ifndef __LOCAL_READPASSPHRASE_HELPERS_DEFINED
__NAMESPACE_LOCAL_BEGIN
#define __LOCAL_READPASSPHRASE_HELPERS_DEFINED
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
static __signo_t const __rpp_signals[] = {
#ifdef __SIGTTOU
	__SIGTTOU, /* This one _must_ be first! */
#endif /* __SIGTTOU */
#ifdef __SIGALRM
	__SIGALRM,
#endif /* __SIGALRM */
#ifdef __SIGHUP
	__SIGHUP,
#endif /* __SIGHUP */
#ifdef __SIGINT
	__SIGINT,
#endif /* __SIGINT */
#ifdef __SIGPIPE
	__SIGPIPE,
#endif /* __SIGPIPE */
#ifdef __SIGQUIT
	__SIGQUIT,
#endif /* __SIGQUIT */
#ifdef __SIGTERM
	__SIGTERM,
#endif /* __SIGTERM */
#ifdef __SIGTSTP
	__SIGTSTP,
#endif /* __SIGTSTP */
#ifdef __SIGTTIN
	__SIGTTIN,
#endif /* __SIGTTIN */
};
static __SIG_ATOMIC_TYPE__ volatile __rpp_arrived[__COMPILER_LENOF(__rpp_signals)];
static void __LIBCCALL __rpp_handler(int __signo) {
	unsigned int __i;
	for (__i = 0;; ++__i) {
		if (__rpp_signals[__i] == __signo) {
			__rpp_arrived[__i] = 1;
			break;
		}
	}
}
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */
__NAMESPACE_LOCAL_END
#endif /* !__LOCAL_READPASSPHRASE_HELPERS_DEFINED */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(readpassphrase) __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(readpassphrase))(char const *__prompt, char *__buf, __SIZE_TYPE__ __bufsize, __STDC_INT_AS_UINT_T __flags) {
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	__BOOL __must_restart;
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */
	__fd_t __infd, __outfd;
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	struct termios __old_ios, __new_ios;
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	struct sigaction __old_sact[__COMPILER_LENOF(__NAMESPACE_LOCAL_SYM __rpp_signals)];
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */

	/* Validate input arguments. */
	if __unlikely(__buf == __NULLPTR || __bufsize < sizeof(char)) {
#ifdef __EINVAL
		(void)__libc_seterrno(__EINVAL);
#else /* __EINVAL */
		(void)__libc_seterrno(1);
#endif /* !__EINVAL */
		goto __err;
	}

#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
__again:
	__must_restart = 0;
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */
	__infd  = __STDIN_FILENO;
	__outfd = __STDIN_FILENO;

	/* Open the relevant output stream. */
	if (!(__flags & __RPP_STDIN)) {
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#ifdef _PATH_TTY
#ifdef __O_RDWR
		__infd = (__NAMESPACE_LOCAL_SYM __localdep_open)(_PATH_TTY, __O_RDWR);
#else /* __O_RDWR */
		__infd = (__NAMESPACE_LOCAL_SYM __localdep_open)(_PATH_TTY, 0);
#endif /* !__O_RDWR */
#else /* _PATH_TTY */
#ifdef __O_RDWR
		__infd = (__NAMESPACE_LOCAL_SYM __localdep_open)("/dev/tty", __O_RDWR);
#else /* __O_RDWR */
		__infd = (__NAMESPACE_LOCAL_SYM __localdep_open)("/dev/tty", 0);
#endif /* !__O_RDWR */
#endif /* !_PATH_TTY */
		if __unlikely(__infd == -1) {
#ifdef __ENOTTY
			if (__flags & __RPP_REQUIRE_TTY)
				(void)__libc_seterrno(__ENOTTY);
#endif /* __ENOTTY */
			goto __err;
		}
		__outfd = __infd;
#else /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#if defined(__ENOTTY) && defined(__ENOENT)
		(void)__libc_seterrno(__flags & __RPP_REQUIRE_TTY ? __ENOTTY : __ENOENT);
#elif defined(__ENOENT)
		(void)__libc_seterrno(__ENOENT);
#else /* ... */
		(void)__libc_seterrno(1);
#endif /* !... */
		goto __err;
#endif /* !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
	}

	/* Update terminal IOS mode to our liking. */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if ((__NAMESPACE_LOCAL_SYM __localdep_tcgetattr)(__infd, &__old_ios) != 0) {
		if (__flags & __RPP_REQUIRE_TTY) {
#ifdef __ENOTTY
			(void)__libc_seterrno(__ENOTTY);
#endif /* __ENOTTY */
			goto __err_infd;
#define __PRIVATE_WANT_err_infd
		}
		(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(&__new_ios, &__old_ios, sizeof(struct termios));
		if (!(__flags & __RPP_ECHO_ON)) {
#if defined(__ECHO) && defined(__ECHONL)
			__new_ios.c_lflag &= ~(__ECHO | __ECHONL);
#elif defined(__ECHO)
			__new_ios.c_lflag &= ~(__ECHO);
#elif defined(__ECHONL)
			__new_ios.c_lflag &= ~(__ECHONL);
#endif /* ... */
		}
#ifdef __VSTATUS
		if (__term.__c_cc[__VSTATUS] != __VDISABLE)
			__term.__c_cc[__VSTATUS] = __VDISABLE;
#endif /* __VSTATUS */
		if ((__NAMESPACE_LOCAL_SYM __localdep_memcmp)(&__old_ios, &__new_ios, sizeof(struct termios)) != 0) {
#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
			if ((__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__infd, __TCSAFLUSH | __TCSASOFT, &__new_ios) != 0)
				goto __err_infd;
#elif defined(__TCSAFLUSH)
			if ((__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__infd, __TCSAFLUSH, &__new_ios) != 0)
				goto __err_infd;
#else /* ... */
			if ((__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__infd, 0, &__new_ios) != 0)
				goto __err_infd;
#endif /* !... */
#define __PRIVATE_WANT_err_infd
		}
	} else {
		(__NAMESPACE_LOCAL_SYM __localdep_bzero)(&__old_ios, sizeof(struct termios));
		(__NAMESPACE_LOCAL_SYM __localdep_bzero)(&__new_ios, sizeof(struct termios));
#ifdef __ECHO
		__old_ios.c_lflag = __ECHO;
		__new_ios.c_lflag = __ECHO;
#endif /* __ECHO */
	}
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */

	/* Switch out signal handlers
	 * WARNING: The fact that we need to  do this has the (unintended)  side-effect
	 *          that this function as a whole is not thread-safe. Note however that
	 *          within the original  source material, this  function also  modifies
	 *          the process's signal handlers, meaning that the original  reference
	 *          for this function also isn't thread-safe! */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	{
		unsigned int __i;
		struct sigaction __newact;
		(__NAMESPACE_LOCAL_SYM __localdep_bzero)((void *)__NAMESPACE_LOCAL_SYM __rpp_arrived, sizeof(__NAMESPACE_LOCAL_SYM __rpp_arrived));
		(__NAMESPACE_LOCAL_SYM __localdep_bzero)(&__newact, sizeof(__newact));
		__newact.sa_handler = &__NAMESPACE_LOCAL_SYM __rpp_handler;
		for (__i = 0; __i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM __rpp_signals); ++__i) {
			if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sigaction)(__NAMESPACE_LOCAL_SYM __rpp_signals[__i], &__newact, &__old_sact[__i]) != 0) {
				while (__i) {
					--__i;
					(void)(__NAMESPACE_LOCAL_SYM __localdep_sigaction)(__NAMESPACE_LOCAL_SYM __rpp_signals[__i], &__newact, &__old_sact[__i]);
				}
				goto __err_infd_oldios;
#define __PRIVATE_WANT_err_infd_oldios
			}
		}
	}
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */


	/* Write the given `prompt' (if given and possible to write) */
	(void)__prompt;
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
	/* XXX: I don't really understand why the prompt is only printed
	 *      when using /dev/tty as output,  but that's how BSD  does
	 *      this, too... */
	if (__prompt && *__prompt && !(__flags & __RPP_STDIN)) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_write)(__outfd, __prompt, (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__prompt)) == -1)
			goto __err_infd_oldsact_oldios;
	}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */

	/* Read the actual password from input. */
	{
		unsigned char *__dst, *__bufend;
		__dst    = (unsigned char *)__buf;
		__bufend = (unsigned char *)__buf + (__bufsize / sizeof(char)) - 1;
		for (;;) {
			unsigned char __ch;
			__SSIZE_TYPE__ __error;
			__error = (__NAMESPACE_LOCAL_SYM __localdep_read)(__infd, &__ch, sizeof(char));
			if (__error < 1) {
				if (__error >= 0)
					break;
				goto __err_infd_oldsact_oldios;
			}
			if (__ch == '\r' || __ch == '\n')
				break; /* End-of-line... */
			if (__dst < __bufend) {
				/* Append character. */
				if (__flags & __RPP_SEVENBIT)
					__ch &= 0x7f;
				if (__flags & __RPP_FORCELOWER)
					__ch = (unsigned char)(__NAMESPACE_LOCAL_SYM __localdep_tolower)((char)__ch);
				if (__flags & __RPP_FORCEUPPER)
					__ch = (unsigned char)(__NAMESPACE_LOCAL_SYM __localdep_toupper)((char)__ch);
				*__dst++ = __ch;
			}
		}
		*__dst = '\0'; /* Force NUL-termination. */
	}

	/* Write a trailing \n-character if echo was disabled. */
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if (!(__new_ios.c_lflag & __ECHO))
#else /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
	if (!(__flags & __RPP_ECHO_ON))
#endif /* (!__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA)) || (!__CRT_HAVE_tcsetattr && !__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) */
	{
		if ((__NAMESPACE_LOCAL_SYM __localdep_write)(__outfd, "\n", 1) == -1)
			goto __err_infd_oldsact_oldios;
	}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */


	/* Restore terminal IOS configuration */
__done_infd_oldsact_oldios:
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if ((__NAMESPACE_LOCAL_SYM __localdep_memcmp)(&__old_ios, &__new_ios, sizeof(struct termios)) != 0) {
#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		(void)(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__infd, __TCSAFLUSH | __TCSASOFT, &__old_ios);
#elif defined(__TCSAFLUSH)
		(void)(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__infd, __TCSAFLUSH, &__old_ios);
#else /* ... */
		(void)(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__infd, 0, &__old_ios);
#endif /* !... */
	}
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */

	/* Restore signal handlers. */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	{
		unsigned int __i;
		for (__i = 0; __i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM __rpp_signals); ++__i)
			(void)(__NAMESPACE_LOCAL_SYM __localdep_sigaction)(__NAMESPACE_LOCAL_SYM __rpp_signals[__i], &__old_sact[__i], __NULLPTR);
	}
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */

	/* Close the input file handle if we've manually opened `/dev/tty' above. */
#ifdef __PRIVATE_WANT_err_infd
__done_infd:
#endif /* __PRIVATE_WANT_err_infd */
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	if (__infd != __STDIN_FILENO)
		(__NAMESPACE_LOCAL_SYM __localdep_close)(__infd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */

	/* Re-throw signals that arrived in the mean time. */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	{
		unsigned int __i;
		for (__i = 0; __i < __COMPILER_LENOF(__NAMESPACE_LOCAL_SYM __rpp_signals); ++__i) {
			if (!__NAMESPACE_LOCAL_SYM __rpp_arrived[__i])
				continue;
#if (defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid))
			(__NAMESPACE_LOCAL_SYM __localdep_kill)((__NAMESPACE_LOCAL_SYM __localdep_getpid)(), __NAMESPACE_LOCAL_SYM __rpp_signals[__i]);
#elif defined(__CRT_HAVE_raise) || ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self)))
			(__NAMESPACE_LOCAL_SYM __localdep_raise)(__NAMESPACE_LOCAL_SYM __rpp_signals[__i]);
#endif /* ... */

			/* Handle signals for which we must start over when they're received. */
#if defined(__SIGTSTP) || defined(__SIGTTIN) || defined(__SIGTTOU)
			if (0
#ifdef __SIGTSTP
			    || __NAMESPACE_LOCAL_SYM __rpp_signals[__i] == __SIGTSTP
#endif /* __SIGTSTP */
#ifdef __SIGTTIN
			    || __NAMESPACE_LOCAL_SYM __rpp_signals[__i] == __SIGTTIN
#endif /* __SIGTTIN */
#ifdef __SIGTTOU
			    || __NAMESPACE_LOCAL_SYM __rpp_signals[__i] == __SIGTTOU
#endif /* __SIGTTOU */
			    )
				__must_restart = 1;
#endif /* __SIGTSTP || __SIGTTIN || __SIGTTOU */

		}
	}
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */

	/* Check if we have to start over (due to having received certain signals) */
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
	if (__must_restart && __buf != __NULLPTR)
		goto __again;
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */

	/* Done! */
	return __buf;

__err_infd_oldsact_oldios:
	__buf = __NULLPTR;
	goto __done_infd_oldsact_oldios;

#ifdef __PRIVATE_WANT_err_infd_oldios
#undef __PRIVATE_WANT_err_infd_oldios
__err_infd_oldios:
	/* Restore terminal IOS configuration */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if ((__NAMESPACE_LOCAL_SYM __localdep_memcmp)(&__old_ios, &__new_ios, sizeof(struct termios)) != 0) {
#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		(void)(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__infd, __TCSAFLUSH | __TCSASOFT, &__old_ios);
#elif defined(__TCSAFLUSH)
		(void)(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__infd, __TCSAFLUSH, &__old_ios);
#else /* ... */
		(void)(__NAMESPACE_LOCAL_SYM __localdep_tcsetattr)(__infd, 0, &__old_ios);
#endif /* !... */
	}
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
	__buf = __NULLPTR;
	goto __done_infd;
#endif /* __PRIVATE_WANT_err_infd_oldios */

#ifdef __PRIVATE_WANT_err_infd
#undef __PRIVATE_WANT_err_infd
__err_infd:
	__buf = __NULLPTR;
	goto __done_infd;
#endif /* __PRIVATE_WANT_err_infd */

__err:
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_readpassphrase_defined
#define __local___localdep_readpassphrase_defined
#define __localdep_readpassphrase __LIBC_LOCAL_NAME(readpassphrase)
#endif /* !__local___localdep_readpassphrase_defined */
#else /* __STDIN_FILENO && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) */
#undef __local_readpassphrase_defined
#endif /* !__STDIN_FILENO || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) */
#endif /* !__local_readpassphrase_defined */
