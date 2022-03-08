/* HASH CRC-32:0x543e8bf2 */
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
#ifndef GUARD_LIBC_AUTO_PROCESS_C
#define GUARD_LIBC_AUTO_PROCESS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/process.h"
#include "../user/fcntl.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "../user/sys.wait.h"
#include "../user/unistd.h"

DECL_BEGIN

#include "../libc/dl.h"
#include "../libc/globals.h"
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.sched.thread") void
NOTHROW_NCX(LIBCCALL libc__endthread)(void) {
	libc__endthreadex(0);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.process") void
(LIBCCALL libc__c_exit)(void) THROWS(...) {
}
#include <dlfcn.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.dlfcn") int
(LIBCCALL libc__unloaddll)(intptr_t hnd) THROWS(...) {
#ifdef __CRT_HAVE_dlclose
	return dlclose((void *)(uintptr_t)hnd);
#else /* __CRT_HAVE_dlclose */
	(void)hnd;
	return 0;
#endif /* !__CRT_HAVE_dlclose */
}
#include <dlfcn.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.dlfcn") __procfun
(LIBCCALL libc__getdllprocaddr)(intptr_t hnd,
                                char __KOS_FIXED_CONST *symname,
                                intptr_t ord) THROWS(...) {
	(void)ord;
	return (__procfun)dlsym((void *)(uintptr_t)hnd, symname);
}
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") pid_t
NOTHROW_RPC(LIBCCALL libc_cwait)(int *tstat,
                                 pid_t pid,
                                 __STDC_INT_AS_UINT_T action) {
	/* This one's pretty simple, because it's literally just a waitpid() system call...
	 * (It even returns the same  thing, that being the  PID of the joined  process...) */
	/* NOTE: Apparently, the `action' argument is completely ignored... */
	(void)action;
	/* NOTE: `waitpid(2)' with `options: 0' means `WEXITED' */
	return libc_waitpid(pid, tstat, 0);
}
#include <libc/template/environ.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnv)(__STDC_INT_AS_UINT_T mode,
                                  char const *__restrict path,
                                  __TARGV) {
	return libc_spawnve(mode, path, ___argv, __LOCAL_environ);
}
#include <libc/template/environ.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnvp)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict file,
                                   __TARGV) {
	return libc_spawnvpe(mode, file, ___argv, __LOCAL_environ);
}
#include <asm/os/oflags.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnve)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict path,
                                   __TARGV,
                                   __TENVP) {
	fd_t fd;
	pid_t result = -1;
#if defined(O_RDONLY) && defined(O_CLOEXEC)
	fd = libc_open(path, O_RDONLY | O_CLOEXEC);
#elif defined(O_RDONLY)
	fd = libc_open(path, O_RDONLY);
#else /* ... */
	fd = libc_open(path, 0);
#endif /* !... */
	if likely(fd >= 0) {
		result = libc_fspawnve(mode, fd, ___argv, ___envp);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
		libc_close(fd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	}
	return result;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__spawnvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((2, 4, 6, 7)) pid_t
(__LIBCCALL __spawnvpe_impl)(__STDC_INT_AS_UINT_T mode,
                             char const *__restrict path, size_t path_len,
                             char const *__restrict file, size_t file_len,
                             __TARGV, __TENVP) {
	char *fullpath, *dst;
#ifdef _WIN32
	while (path_len && (path[path_len - 1] == '/' ||
	                    path[path_len - 1] == '\\'))
		--path_len;
#else /* _WIN32 */
	while (path_len && path[path_len - 1] == '/')
		--path_len;
#endif /* !_WIN32 */
	fullpath = (char *)__hybrid_alloca((path_len + 1 + file_len + 1) *
	                                   sizeof(char));
	dst = (char *)mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return libc_spawnve(mode, fullpath, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnvpe)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict file,
                                    __TARGV,
                                    __TENVP) {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */
#ifdef _WIN32
	if (libc_strchr(file, '/') || libc_strchr(file, '\\'))
		return libc_spawnve(mode, file, ___argv, ___envp);
#else /* _WIN32 */
	if (libc_strchr(file, '/'))
		return libc_spawnve(mode, file, ___argv, ___envp);
#endif /* !_WIN32 */
	env_path = libc_getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen  = libc_strlen(file);
		for (;;) {
			pid_t result;
			char *path_end;
#ifdef _WIN32
			path_end = libc_strchrnul(env_path, ';');
#else /* _WIN32 */
			path_end = libc_strchrnul(env_path, ':');
#endif /* !_WIN32 */
			result = (__NAMESPACE_LOCAL_SYM __spawnvpe_impl)(mode, env_path, (size_t)(path_end - env_path),
			                                                 file, filelen, ___argv, ___envp);
			if (result >= 0)
				return result;
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {
#ifdef ENOENT
		(void)libc_seterrno(ENOENT);
#endif /* ENOENT */
	}
	return -1;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnl)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, libc_spawnv, mode, path, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnl)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, libc_spawnv, mode, path, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlp)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, libc_spawnvp, mode, file, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlp)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, libc_spawnvp, mode, file, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnle)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnve, mode, path, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnle)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnve, mode, path, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlpe)(__STDC_INT_AS_UINT_T mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnvpe, mode, file, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlpe)(__STDC_INT_AS_UINT_T mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnvpe, mode, file, args)
}
#include <asm/crt/process.h>
#include <libc/errno.h>
#include <asm/os/vfork.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") NONNULL((3, 4)) pid_t
NOTHROW_RPC(LIBCCALL libc_fspawnve)(__STDC_INT_AS_UINT_T mode,
                                    fd_t execfd,
                                    __TARGV,
                                    __TENVP) {
	int status;
#if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || (!defined(__CRT_HAVE_vfork) && !defined(__CRT_HAVE___vfork) && !defined(__CRT_HAVE___libc_vfork))
	fd_t pipes[2];
	errno_t error;
	ssize_t temp;
#else /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	errno_t old_errno;
#endif /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	pid_t child;
	if (mode == P_OVERLAY)
		return libc_fexecve(execfd, ___argv, ___envp);
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
	old_errno = libc_geterrno_or(0);
	(void)libc_seterrno(0);
#endif /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
#if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || (!defined(__CRT_HAVE_vfork) && !defined(__CRT_HAVE___vfork) && !defined(__CRT_HAVE___libc_vfork))
	/* Create a pair of pipes for temporary communication. */
	if (libc_pipe2(pipes, O_CLOEXEC))
		goto err;
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	if (mode == P_DETACH) {
		/* Daemonize (detach) the process using detach(2), or double-fork. */
#if defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork)
		if (libc_vfork() == 0)
#else /* __CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork */
		if (libc_fork() == 0)
#endif /* !__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork */
		{
#ifdef __CRT_HAVE_detach
			libc_detach(0); /* Detach myself from my parent. */
			goto do_exec;
#else /* __CRT_HAVE_detach */
#if defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork)
			if (libc_vfork() == 0)
#else /* __CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork */
			if (libc_fork() == 0)
#endif /* !__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork */
				goto do_exec;
			libc__Exit(0); /* Just terminate the intermediate process. */
#endif /* !__CRT_HAVE_detach */
		}
		child = 0;
		goto read_child_errors;
	}
	if (mode == P_WAIT) {
		/* Spawn and join the process */
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
		child = libc_vfork();
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
		child = libc_fork();
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
		if (child == 0)
			goto do_exec;
		if (child < 0)
			goto err;
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
		/* Check for errors that may have happened in  the
		 * child process _after_ we did the vfork() above. */
		if (libc_geterrno_or(0) != 0)
			goto err_join_zombie_child;
		/* Success (but still restore the old errno
		 * since  we  overwrote it  to be  0 above) */
		(void)libc_seterrno(old_errno);
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
		libc_close(pipes[1]); /* Close the writer. */
		temp = libc_read(pipes[0], &error, sizeof(error));
		libc_close(pipes[0]); /* Close the reader. */
		if (temp < 0)
			goto err_join_zombie_child;
		if (temp == sizeof(error)) {
			/* If something was read, then it is the errno value that caused the failure. */
			(void)libc_seterrno(error);
			goto err;
		}
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
		/* Join the child. */
		while (libc_waitpid(child, &status, 0) < 0) {
#ifdef EINTR
			if (__libc_geterrno() == EINTR)
				continue;
#endif /* EINTR */
			goto err;
		}
		return (pid_t)(int)(unsigned int)WEXITSTATUS(status);
	}

	/* Spawn asynchronously. */
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
	child = libc_vfork();
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	child = libc_fork();
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	if (child == 0)
		goto do_exec;
read_child_errors:
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
	/* Check if the vfork() from  the child returned success, but  left
	 * our (vm-shared) errno as non-zero (which would indicate that the
	 * child encountered an error at  some point after vfork()  already
	 * succeeded) */
	if (libc_geterrno_or(0) != 0)
		goto err_join_zombie_child;
	/* Complete success (but we must still restore the old errno from
	 * before we were called) */
	(void)libc_seterrno(old_errno);
	/* Return the child's PID */
	return child;
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	/* Read from the communication pipe
	 * (NOTE: If exec() succeeds, the pipe will be
	 *        closed and  read() returns  ZERO(0)) */
	libc_close(pipes[1]); /* Close the writer. */
	temp = libc_read(pipes[0], &error, sizeof(error));
	libc_close(pipes[0]); /* Close the reader. */
	if (temp < 0)
		goto err_join_zombie_child;
	/* This means that `fexecve()' below closed the pipe during a successful exec(). */
	if (temp != sizeof(error))
		return child;
	/* If something was read, then it is the errno value that caused the failure. */
	(void)libc_seterrno(error);
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
err_join_zombie_child:
	if (mode != P_DETACH) {
		/* Unless the child was already spawned as detached,
		 * we still have to re-join  it, or else it will  be
		 * left dangling as a zombie process! */
		if (libc_waitpid(child, &status, 0) < 0) {
#ifdef EINTR
			if (__libc_geterrno() == EINTR)
				goto err_join_zombie_child;
#endif /* EINTR */
		}
	}
err:
	return -1;
do_exec:
	/* When the exec succeeds, the pipe is auto-
	 * closed because it's marked as  O_CLOEXEC! */
	libc_fexecve(execfd, ___argv, ___envp);
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
	/* If the exec fails, it will have modified `errno' to indicate this fact.
	 * And since we're sharing VMs with  our parent process, the error  reason
	 * will have already  been written  back to  our parent's  VM, so  there's
	 * actually nothing left for us to do, but to simply exit! */
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	/* Write the exec-error back to our parent. */
#ifdef ENOENT
	error = libc_geterrno_or(ENOENT);
#else /* ENOENT */
	error = libc_geterrno_or(1);
#endif /* !ENOENT */
	/* Communicate back why this failed. */
	libc_write(pipes[1], &error, sizeof(error));
	/* No need to close the pipe, it's auto-closed by the kernel! */
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	libc__Exit(127);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_endthread, libc__endthread);
DEFINE_PUBLIC_ALIAS(_c_exit, libc__c_exit);
DEFINE_PUBLIC_ALIAS(_unloaddll, libc__unloaddll);
DEFINE_PUBLIC_ALIAS(_getdllprocaddr, libc__getdllprocaddr);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_cwait, libc_cwait);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(cwait, libc_cwait);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_spawnv, libc_spawnv);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(spawnv, libc_spawnv);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_spawnvp, libc_spawnvp);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(spawnvp, libc_spawnvp);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_spawnve, libc_spawnve);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(spawnve, libc_spawnve);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_spawnvpe, libc_spawnvpe);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(spawnvpe, libc_spawnvpe);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnl, libd_spawnl);
DEFINE_PUBLIC_ALIAS(DOS$spawnl, libd_spawnl);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_spawnl, libc_spawnl);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(spawnl, libc_spawnl);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnlp, libd_spawnlp);
DEFINE_PUBLIC_ALIAS(DOS$spawnlp, libd_spawnlp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_spawnlp, libc_spawnlp);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(spawnlp, libc_spawnlp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnle, libd_spawnle);
DEFINE_PUBLIC_ALIAS(DOS$spawnle, libd_spawnle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_spawnle, libc_spawnle);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(spawnle, libc_spawnle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnlpe, libd_spawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$spawnlpe, libd_spawnlpe);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_spawnlpe, libc_spawnlpe);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(spawnlpe, libc_spawnlpe);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_spawnve, libc_fspawnve);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(fspawnve, libc_fspawnve);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PROCESS_C */
