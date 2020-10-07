/* HASH CRC-32:0x91ff7535 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_forkpty_defined
#define __local_forkpty_defined 1
#include <__crt.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_openpty) && (defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)) && (defined(__CRT_HAVE_login_tty) || (defined(__TIOCSCTTY) && defined(__CRT_HAVE_ioctl) && defined(__CRT_HAVE_setsid) && (defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2)))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit))
struct termios;
struct winsize;
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _Exit from stdlib */
#ifndef __local___localdep__Exit_defined
#define __local___localdep__Exit_defined 1
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep__Exit,(int __status),_Exit,{ return __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep__Exit,(int __status),_exit,{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),exit,(__status))
#else /* ... */
#undef __local___localdep__Exit_defined
#endif /* !... */
#endif /* !__local___localdep__Exit_defined */
/* Dependency: close from unistd */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined 1
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a given file descriptor/handle `FD' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a given file descriptor/handle `FD' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a given file descriptor/handle `FD' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
/* Dependency: fork from unistd */
#ifndef __local___localdep_fork_defined
#define __local___localdep_fork_defined 1
#if __has_builtin(__builtin_fork) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fork)
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
__CEIREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,{ return __builtin_fork(); })
#elif defined(__CRT_HAVE_fork)
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,())
#elif defined(__CRT_HAVE___fork)
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__fork,())
#else /* ... */
#undef __local___localdep_fork_defined
#endif /* !... */
#endif /* !__local___localdep_fork_defined */
/* Dependency: login_tty from utmp */
#ifndef __local___localdep_login_tty_defined
#define __local___localdep_login_tty_defined 1
#ifdef __CRT_HAVE_login_tty
/* Make FD be the controlling terminal, stdin, stdout, and stderr;
 * then close FD. Returns 0 on success, nonzero on error */
__CREDIRECT(,int,__NOTHROW_RPC_KOS,__localdep_login_tty,(__fd_t __fd),login_tty,(__fd))
#elif defined(__TIOCSCTTY) && defined(__CRT_HAVE_ioctl) && defined(__CRT_HAVE_setsid) && (defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2))
__NAMESPACE_LOCAL_END
#include <libc/local/utmp/login_tty.h>
__NAMESPACE_LOCAL_BEGIN
/* Make FD be the controlling terminal, stdin, stdout, and stderr;
 * then close FD. Returns 0 on success, nonzero on error */
#define __localdep_login_tty __LIBC_LOCAL_NAME(login_tty)
#else /* ... */
#undef __local___localdep_login_tty_defined
#endif /* !... */
#endif /* !__local___localdep_login_tty_defined */
/* Dependency: openpty from pty */
#ifndef __local___localdep_openpty_defined
#define __local___localdep_openpty_defined 1
/* >> openpty(2)
 * Create a new ptty (psuedo tty), storing the handles for the
 * master/slave adapters in `*amaster' and `*aslave'. Additionally,
 * the caller may specific the initial terminial settings `termp'
 * and window size `winp', as well as a location where the kernel
 * should store the filename of the PTY master socket (as already
 * returned in `*amaster'). Note that the max length of this filename
 * is implementation defined, with no way for the use to specify how
 * much space is is available in the passed buffer. As such, a
 * portable application can only ever pass `NULL' for this value.
 * On KOS, the value written to `name' is the absolute filename of
 * the master-device in the `/dev' filesystem, which usually means
 * that the written filename is something like `/dev/ptyp0'.
 * NOTE: On KOS, this function is a system call, though in other
 *       operating system it is often implemented via `open(2)',
 *       possibly combined with `ioctl(2)'. */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_openpty,(__fd_t *__amaster, __fd_t *__aslave, char *__name, struct termios const *__termp, struct winsize const *__winp),openpty,(__amaster,__aslave,__name,__termp,__winp))
#endif /* !__local___localdep_openpty_defined */
/* >> forkpty(3)
 * A helper for combining `openpty(2)' with `fork(2)' and `login_tty(3)',
 * such that the newly created PTY is open under all std-handles in
 * the newly created child process.
 * Aside from this, this function returns the same as fork(2), that is
 * it returns in both the parent and child processes, returning `0'
 * for the child, and the child's PID for the parent (or -1 in only the
 * parent if something went wrong) */
__LOCAL_LIBC(forkpty) __ATTR_NONNULL((1)) __pid_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(forkpty))(__fd_t *__amaster, char *__name, struct termios const *__termp, struct winsize const *__winp) {
	int __error;
	__fd_t __master, __slave;
	__pid_t __pid;
	__error = __localdep_openpty(&__master, &__slave, __name, __termp, __winp);
	if __unlikely(__error)
		return __error;
	__pid = __localdep_fork();
	if __unlikely(__pid == -1) {
		__localdep_close(__master);
		goto __done_slave;
	}
	if (__pid == 0) {
		/* Child process. */
		__localdep_close(__master);
		if (__localdep_login_tty(__slave))
			__localdep__Exit(1);
		return 0;
	}
	/* Parent process. */
	*__amaster = __master;
__done_slave:
	__localdep_close(__slave);
	return __pid;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_forkpty_defined
#define __local___localdep_forkpty_defined 1
#define __localdep_forkpty __LIBC_LOCAL_NAME(forkpty)
#endif /* !__local___localdep_forkpty_defined */
#else /* __CRT_HAVE_openpty && (__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close) && (__CRT_HAVE_login_tty || (__TIOCSCTTY && __CRT_HAVE_ioctl && __CRT_HAVE_setsid && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2))) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) */
#undef __local_forkpty_defined
#endif /* !__CRT_HAVE_openpty || (!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close) || (!__CRT_HAVE_login_tty && (!__TIOCSCTTY || !__CRT_HAVE_ioctl || !__CRT_HAVE_setsid || (!__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2))) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) */
#endif /* !__local_forkpty_defined */
