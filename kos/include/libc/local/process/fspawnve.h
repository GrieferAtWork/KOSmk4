/* HASH CRC-32:0x5d5493b5 */
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
#ifndef __local_fspawnve_defined
#define __local_fspawnve_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))
#include <features.h>
#include <bits/types.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__Exit_defined
#define __local___localdep__Exit_defined
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep__Exit,(int __status),_Exit,{ __builtin__Exit(__status); })
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
#if !defined(__local___localdep_detach_defined) && defined(__CRT_HAVE_detach)
#define __local___localdep_detach_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_detach,(__pid_t __pid),detach,(__pid))
#endif /* !__local___localdep_detach_defined && __CRT_HAVE_detach */
#ifndef __local___localdep_fexecve_defined
#define __local___localdep_fexecve_defined
#ifdef __CRT_HAVE_fexecve
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_fexecve,(__fd_t __execfd, __TARGV, __TENVP),fexecve,(__execfd,___argv,___envp))
#elif defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/fexecve.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fexecve __LIBC_LOCAL_NAME(fexecve)
#else /* ... */
#undef __local___localdep_fexecve_defined
#endif /* !... */
#endif /* !__local___localdep_fexecve_defined */
#ifndef __local___localdep_fork_defined
#define __local___localdep_fork_defined
#if __has_builtin(__builtin_fork) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fork)
__CEIREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,{ return __builtin_fork(); })
#elif defined(__CRT_HAVE_fork)
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,())
#elif defined(__CRT_HAVE___fork)
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__fork,())
#elif defined(__CRT_HAVE___libc_fork)
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__libc_fork,())
#else /* ... */
#undef __local___localdep_fork_defined
#endif /* !... */
#endif /* !__local___localdep_fork_defined */
#ifndef __local___localdep_pipe2_defined
#define __local___localdep_pipe2_defined
#ifdef __CRT_HAVE_pipe2
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_pipe2,(__fd_t __pipedes[2], __oflag_t __flags),pipe2,(__pipedes,__flags))
#elif defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/pipe2.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pipe2 __LIBC_LOCAL_NAME(pipe2)
#else /* ... */
#undef __local___localdep_pipe2_defined
#endif /* !... */
#endif /* !__local___localdep_pipe2_defined */
#ifndef __local___localdep_read_defined
#define __local___localdep_read_defined
#ifdef __CRT_HAVE_read
__CREDIRECT(__ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
__CREDIRECT(__ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
__CREDIRECT(__ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
__CREDIRECT(__ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__libc_read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
#ifndef __local___localdep_vfork_defined
#define __local___localdep_vfork_defined
#ifdef __CRT_HAVE_vfork
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),vfork,())
#elif defined(__CRT_HAVE___vfork)
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),__vfork,())
#elif defined(__CRT_HAVE___libc_vfork)
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),__libc_vfork,())
#else /* ... */
#undef __local___localdep_vfork_defined
#endif /* !... */
#endif /* !__local___localdep_vfork_defined */
#ifndef __local___localdep_waitpid_defined
#define __local___localdep_waitpid_defined
#ifdef __CRT_HAVE_waitpid
__NAMESPACE_LOCAL_END
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),waitpid,(__pid,__stat_loc,__options))
#elif defined(__CRT_HAVE___waitpid)
__NAMESPACE_LOCAL_END
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),__waitpid,(__pid,__stat_loc,__options))
#else /* ... */
#undef __local___localdep_waitpid_defined
#endif /* !... */
#endif /* !__local___localdep_waitpid_defined */
#ifndef __local___localdep_write_defined
#define __local___localdep_write_defined
#ifdef __CRT_HAVE_write
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_write)
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__libc_write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_write_defined
#endif /* !... */
#endif /* !__local___localdep_write_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/process.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fspawnve) __ATTR_IN(3) __ATTR_IN(4) __pid_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fspawnve))(__STDC_INT_AS_UINT_T __mode, __fd_t __execfd, __TARGV, __TENVP) {
	int __status;
#if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || (!defined(__CRT_HAVE_vfork) && !defined(__CRT_HAVE___vfork) && !defined(__CRT_HAVE___libc_vfork))
	__fd_t __pipes[2];
	__errno_t __error;
	__SSIZE_TYPE__ __temp;
#else /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	__errno_t __old_errno;
#endif /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	__pid_t __child;
	if (__mode == __P_OVERLAY)
		return (__NAMESPACE_LOCAL_SYM __localdep_fexecve)(__execfd, ___argv, ___envp);
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
	__old_errno = __libc_geterrno_or(0);
	(void)__libc_seterrno(0);
#endif /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
#if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || (!defined(__CRT_HAVE_vfork) && !defined(__CRT_HAVE___vfork) && !defined(__CRT_HAVE___libc_vfork))
	/* Create a pair of pipes for temporary communication. */
	if ((__NAMESPACE_LOCAL_SYM __localdep_pipe2)(__pipes, __O_CLOEXEC))
		goto __err;
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	if (__mode == __P_DETACH) {
		/* Daemonize (detach) the process using detach(2), or double-fork. */
#if defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork)
		if ((__NAMESPACE_LOCAL_SYM __localdep_vfork)() == 0)
#else /* __CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork */
		if ((__NAMESPACE_LOCAL_SYM __localdep_fork)() == 0)
#endif /* !__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork */
		{
#ifdef __CRT_HAVE_detach
			(__NAMESPACE_LOCAL_SYM __localdep_detach)(0); /* Detach myself from my parent. */
			goto __do_exec;
#else /* __CRT_HAVE_detach */
#if defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork)
			if ((__NAMESPACE_LOCAL_SYM __localdep_vfork)() == 0)
#else /* __CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork */
			if ((__NAMESPACE_LOCAL_SYM __localdep_fork)() == 0)
#endif /* !__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork */
				goto __do_exec;
			(__NAMESPACE_LOCAL_SYM __localdep__Exit)(0); /* Just terminate the intermediate process. */
#endif /* !__CRT_HAVE_detach */
		}
		__child = 0;
		goto __read_child_errors;
	}
	if (__mode == __P_WAIT) {
		/* Spawn and join the process */
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
		__child = (__NAMESPACE_LOCAL_SYM __localdep_vfork)();
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
		__child = (__NAMESPACE_LOCAL_SYM __localdep_fork)();
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
		if (__child == 0)
			goto __do_exec;
		if (__child < 0)
			goto __err;
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
		/* Check for errors that may have happened in  the
		 * child process _after_ we did the vfork() above. */
		if (__libc_geterrno_or(0) != 0)
			goto __err_join_zombie_child;
		/* Success (but still restore the old errno
		 * since  we  overwrote it  to be  0 above) */
		(void)__libc_seterrno(__old_errno);
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
		(__NAMESPACE_LOCAL_SYM __localdep_close)(__pipes[1]); /* Close the writer. */
		__temp = (__NAMESPACE_LOCAL_SYM __localdep_read)(__pipes[0], &__error, sizeof(__error));
		(__NAMESPACE_LOCAL_SYM __localdep_close)(__pipes[0]); /* Close the reader. */
		if (__temp < 0)
			goto __err_join_zombie_child;
		if (__temp == sizeof(__error)) {
			/* If something was read, then it is the errno value that caused the failure. */
			(void)__libc_seterrno(__error);
			goto __err;
		}
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
		/* Join the child. */
		while ((__NAMESPACE_LOCAL_SYM __localdep_waitpid)(__child, &__status, 0) < 0) {
#ifdef __EINTR
			if (__libc_geterrno() == __EINTR)
				continue;
#endif /* __EINTR */
			goto __err;
		}
		return (__pid_t)(int)(unsigned int)__WEXITSTATUS(__status);
	}

	/* Spawn asynchronously. */
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
	__child = (__NAMESPACE_LOCAL_SYM __localdep_vfork)();
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	__child = (__NAMESPACE_LOCAL_SYM __localdep_fork)();
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	if (__child == 0)
		goto __do_exec;
__read_child_errors:
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
	/* Check if the vfork() from  the child returned success, but  left
	 * our (vm-shared) errno as non-zero (which would indicate that the
	 * child encountered an error at  some point after vfork()  already
	 * succeeded) */
	if (__libc_geterrno_or(0) != 0)
		goto __err_join_zombie_child;
	/* Complete success (but we must still restore the old errno from
	 * before we were called) */
	(void)__libc_seterrno(__old_errno);
	/* Return the child's PID */
	return __child;
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	/* Read from the communication pipe
	 * (NOTE: If exec() succeeds, the pipe will be
	 *        closed and  read() returns  ZERO(0)) */
	(__NAMESPACE_LOCAL_SYM __localdep_close)(__pipes[1]); /* Close the writer. */
	__temp = (__NAMESPACE_LOCAL_SYM __localdep_read)(__pipes[0], &__error, sizeof(__error));
	(__NAMESPACE_LOCAL_SYM __localdep_close)(__pipes[0]); /* Close the reader. */
	if (__temp < 0)
		goto __err_join_zombie_child;
	/* This means that `fexecve()' below closed the pipe during a successful exec(). */
	if (__temp != sizeof(__error))
		return __child;
	/* If something was read, then it is the errno value that caused the failure. */
	(void)__libc_seterrno(__error);
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
__err_join_zombie_child:
	if (__mode != __P_DETACH) {
		/* Unless the child was already spawned as detached,
		 * we still have to re-join  it, or else it will  be
		 * left dangling as a zombie process! */
		if ((__NAMESPACE_LOCAL_SYM __localdep_waitpid)(__child, &__status, 0) < 0) {
#ifdef __EINTR
			if (__libc_geterrno() == __EINTR)
				goto __err_join_zombie_child;
#endif /* __EINTR */
		}
	}
__err:
	return -1;
__do_exec:
	/* When the exec succeeds, the pipe is auto-
	 * closed because it's marked as  O_CLOEXEC! */
	(__NAMESPACE_LOCAL_SYM __localdep_fexecve)(__execfd, ___argv, ___envp);
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
	/* If the exec fails, it will have modified `errno' to indicate this fact.
	 * And since we're sharing VMs with  our parent process, the error  reason
	 * will have already  been written  back to  our parent's  VM, so  there's
	 * actually nothing left for us to do, but to simply exit! */
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	/* Write the exec-error back to our parent. */
#ifdef __ENOENT
	__error = __libc_geterrno_or(__ENOENT);
#else /* __ENOENT */
	__error = __libc_geterrno_or(1);
#endif /* !__ENOENT */
	/* Communicate back why this failed. */
	(__NAMESPACE_LOCAL_SYM __localdep_write)(__pipes[1], &__error, sizeof(__error));
	/* No need to close the pipe, it's auto-closed by the kernel! */
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	(__NAMESPACE_LOCAL_SYM __localdep__Exit)(127);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fspawnve_defined
#define __local___localdep_fspawnve_defined
#define __localdep_fspawnve __LIBC_LOCAL_NAME(fspawnve)
#endif /* !__local___localdep_fspawnve_defined */
#else /* (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) */
#undef __local_fspawnve_defined
#endif /* (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) */
#endif /* !__local_fspawnve_defined */
