/* HASH CRC-32:0xf7bb5a6d */
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
#ifndef __local_system_defined
#define __local_system_defined 1
#include <__crt.h>
#include <libc/local/environ.h>
#if (defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _Exit from stdlib */
#ifndef __local___localdep__Exit_defined
#define __local___localdep__Exit_defined 1
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
/* Dependency: fork from unistd */
#ifndef __local___localdep_fork_defined
#define __local___localdep_fork_defined 1
#if __has_builtin(__builtin_fork) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
/* Dependency: shexec from stdlib */
#ifndef __local___localdep_shexec_defined
#define __local___localdep_shexec_defined 1
#ifdef __CRT_HAVE_shexec
/* >> shexec(3)
 * Execute command with the system interpreter (such as: `/bin/sh -c $command')
 * This function is used to implement `system(3)' and `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have been
 * replaced by the system shell)
 * The shell paths attempted by this function are system-dependent, but before
 * any of them are tested, this function will try to use `getenv("SHELL")', if
 * and only if that variable is defined and starts with a '/'-character. */
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_shexec,(char const *__command),shexec,(__command))
#elif defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/shexec.h>
__NAMESPACE_LOCAL_BEGIN
/* >> shexec(3)
 * Execute command with the system interpreter (such as: `/bin/sh -c $command')
 * This function is used to implement `system(3)' and `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have been
 * replaced by the system shell)
 * The shell paths attempted by this function are system-dependent, but before
 * any of them are tested, this function will try to use `getenv("SHELL")', if
 * and only if that variable is defined and starts with a '/'-character. */
#define __localdep_shexec __LIBC_LOCAL_NAME(shexec)
#else /* ... */
#undef __local___localdep_shexec_defined
#endif /* !... */
#endif /* !__local___localdep_shexec_defined */
/* Dependency: vfork from unistd */
#ifndef __local___localdep_vfork_defined
#define __local___localdep_vfork_defined 1
#ifdef __CRT_HAVE_vfork
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> vfork(2)
 * Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the parent process remaining suspended until the
 * child process invokes one of the following system calls:
 *   - `_exit(2)'  Terminate the child process. Be sure to use `_exit' (or `_Exit')
 *                 instead of the regular `exit(3)', since the later would include
 *                 the invocation of `atexit(3)' handlers, which would then run in
 *                 the context of a VM that isn't actually about to be destroyed.
 *   - `execve(2)' Create a new VM that is populated with the specified process
 *                 image. The parent process will only be resumed in case the
 *                 new program image could be loaded successfully. Otherwise,
 *                 the call to `execve(2)' returns normally in the child.
 *                 Other functions from the exec()-family behave the same
 *
 * Care must be taken when using this system call, since you have to make sure that
 * the child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in the parent process. The same also goes for heap
 * functions, but generally speaking: you really shouldn't do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3), which
 * is something that KOS intentionally doesn't do, since I feel like doing so only
 * adds unnecessary bloat to code that doesn't rely on this)
 *
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which case the parent process will not actually get suspended until the child
 * process performs any of the actions above. */
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),vfork,())
#elif defined(__CRT_HAVE___vfork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> vfork(2)
 * Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the parent process remaining suspended until the
 * child process invokes one of the following system calls:
 *   - `_exit(2)'  Terminate the child process. Be sure to use `_exit' (or `_Exit')
 *                 instead of the regular `exit(3)', since the later would include
 *                 the invocation of `atexit(3)' handlers, which would then run in
 *                 the context of a VM that isn't actually about to be destroyed.
 *   - `execve(2)' Create a new VM that is populated with the specified process
 *                 image. The parent process will only be resumed in case the
 *                 new program image could be loaded successfully. Otherwise,
 *                 the call to `execve(2)' returns normally in the child.
 *                 Other functions from the exec()-family behave the same
 *
 * Care must be taken when using this system call, since you have to make sure that
 * the child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in the parent process. The same also goes for heap
 * functions, but generally speaking: you really shouldn't do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3), which
 * is something that KOS intentionally doesn't do, since I feel like doing so only
 * adds unnecessary bloat to code that doesn't rely on this)
 *
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which case the parent process will not actually get suspended until the child
 * process performs any of the actions above. */
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),__vfork,())
#else /* ... */
#undef __local___localdep_vfork_defined
#endif /* !... */
#endif /* !__local___localdep_vfork_defined */
/* Dependency: waitpid from sys.wait */
#ifndef __local___localdep_waitpid_defined
#define __local___localdep_waitpid_defined 1
#ifdef __CRT_HAVE_waitpid
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <features.h>
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
/* >> waitpid(2)
 * Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),waitpid,(__pid,__stat_loc,__options))
#elif defined(__CRT_HAVE___waitpid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <features.h>
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
/* >> waitpid(2)
 * Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),__waitpid,(__pid,__stat_loc,__options))
#else /* ... */
#undef __local___localdep_waitpid_defined
#endif /* !... */
#endif /* !__local___localdep_waitpid_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/wait.h>
__NAMESPACE_LOCAL_BEGIN
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The return value is the exit status after running `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When no system interpreter is available, `127' is returned. */
__LOCAL_LIBC(system) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(system))(char const *__command) {
	int __status;
	__pid_t __cpid, __error;
#if defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork)
	__cpid = __localdep_vfork();
#else /* __CRT_HAVE_vfork || __CRT_HAVE___vfork */
	__cpid = __localdep_fork();
#endif /* !__CRT_HAVE_vfork && !__CRT_HAVE___vfork */
	if (__cpid == 0) {
		__localdep_shexec(__command);
		/* NOTE: system() must return ZERO(0) if no command processor is available. */
		__localdep__Exit(__command ? 127 : 0);
	}
	if (__cpid < 0)
		return -1;
	for (;;) {
		__error = __localdep_waitpid(__cpid, &__status, 0);
		if (__error == __cpid)
			break;
		if (__error >= 0)
			continue;
#if defined(__libc_geterrno) && defined(__EINTR)
		if (__libc_geterrno() != __EINTR)
			return -1;
#else /* __libc_geterrno && __EINTR */
		return -1;
#endif /* !__libc_geterrno || !__EINTR */
	}
#ifdef __WIFEXITED
	if (!__WIFEXITED(__status))
		return 1;
#endif /* __WIFEXITED */
#ifdef __WEXITSTATUS
	return __WEXITSTATUS(__status);
#else /* __WEXITSTATUS */
	return __status;
#endif /* !__WEXITSTATUS */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_system_defined
#define __local___localdep_system_defined 1
#define __localdep_system __LIBC_LOCAL_NAME(system)
#endif /* !__local___localdep_system_defined */
#else /* (__CRT_HAVE_shexec || __CRT_HAVE_execl || __CRT_HAVE__execl || __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __LOCAL_environ)) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE_fork || __CRT_HAVE___fork) */
#undef __local_system_defined
#endif /* (!__CRT_HAVE_shexec && !__CRT_HAVE_execl && !__CRT_HAVE__execl && !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__LOCAL_environ)) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE_fork && !__CRT_HAVE___fork) */
#endif /* !__local_system_defined */
