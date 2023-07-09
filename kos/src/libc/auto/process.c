/* HASH CRC-32:0x15a34868 */
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
#ifndef GUARD_LIBC_AUTO_PROCESS_C
#define GUARD_LIBC_AUTO_PROCESS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/process.h"
#include "../user/fcntl.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.wait.h"
#include "../user/unistd.h"

DECL_BEGIN

#include "../libc/dl.h"
#include "../libc/globals.h"
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnl)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, libd_spawnv, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnl)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, libc_spawnv, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlp)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, libd_spawnvp, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlp)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, libc_spawnvp, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnle)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, libd_spawnve, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnle)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnve, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlpe)(__STDC_INT_AS_UINT_T mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, libd_spawnvpe, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlpe)(__STDC_INT_AS_UINT_T mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnvpe, mode, file, args)
}
#include <libc/template/environ.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) pid_t
NOTHROW_RPC(LIBDCALL libd_spawnv)(__STDC_INT_AS_UINT_T mode,
                                  char const *__restrict path,
                                  __TARGV) {
	return libd_spawnve(mode, path, ___argv, __LOCAL_environ);
}
#include <libc/template/environ.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnv)(__STDC_INT_AS_UINT_T mode,
                                  char const *__restrict path,
                                  __TARGV) {
	return libc_spawnve(mode, path, ___argv, __LOCAL_environ);
}
#include <libc/template/environ.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) pid_t
NOTHROW_RPC(LIBDCALL libd_spawnvp)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict file,
                                   __TARGV) {
	return libd_spawnvpe(mode, file, ___argv, __LOCAL_environ);
}
#include <libc/template/environ.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnvp)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict file,
                                   __TARGV) {
	return libc_spawnvpe(mode, file, ___argv, __LOCAL_environ);
}
#include <asm/os/oflags.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t
NOTHROW_RPC(LIBDCALL libd_spawnve)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict path,
                                   __TARGV,
                                   __TENVP) {
	fd_t fd;
	pid_t result = -1;

	fd = libd_open(path, O_RDONLY | __PRIVATE_O_CLOEXEC);



	if likely(fd >= 0) {
		result = libc_fspawnve(mode, fd, ___argv, ___envp);

		libc_close(fd);

	}
	return result;
}
#include <asm/os/oflags.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnve)(__STDC_INT_AS_UINT_T mode,
                                   char const *__restrict path,
                                   __TARGV,
                                   __TENVP) {
	fd_t fd;
	pid_t result = -1;

	fd = libc_open(path, O_RDONLY | __PRIVATE_O_CLOEXEC);



	if likely(fd >= 0) {
		result = libc_fspawnve(mode, fd, ___argv, ___envp);

		libc_close(fd);

	}
	return result;
}
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__dos_spawnvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((2, 4, 6, 7)) pid_t
(__LIBCCALL __dos_spawnvpe_impl)(__STDC_INT_AS_UINT_T mode,
                                 char const *__restrict path, size_t path_len,
                                 char const *__restrict file, size_t file_len,
                                 __TARGV, __TENVP) {
	char *fullpath, *dst;
	while (path_len && (path[path_len - 1] == '/' ||
	                    path[path_len - 1] == '\\'))
		--path_len;
	fullpath = (char *)__hybrid_alloca((path_len + 1 + file_len + 1) *
	                                   sizeof(char));
	dst = (char *)libc_mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)libc_mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return libd_spawnve(mode, fullpath, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t
NOTHROW_RPC(LIBDCALL libd_spawnvpe)(__STDC_INT_AS_UINT_T mode,
                                    char const *__restrict file,
                                    __TARGV,
                                    __TENVP) {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */
	if (libc_strchr(file, '/') || libc_strchr(file, '\\'))
		return libc_spawnve(mode, file, ___argv, ___envp);
	env_path = libc_getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen  = libc_strlen(file);
		for (;;) {
			pid_t result;
			char *path_end;
			path_end = libc_strchrnul(env_path, ';');
			result = (__NAMESPACE_LOCAL_SYM __dos_spawnvpe_impl)(mode, env_path, (size_t)(path_end - env_path),
			                                                     file, filelen, ___argv, ___envp);
			if (result >= 0)
				return result;
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {

		(void)libc_seterrno(ENOENT);

	}
	return -1;
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
	dst = (char *)libc_mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)libc_mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return libc_spawnve(mode, fullpath, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t
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




	if (libc_strchr(file, '/'))
		return libc_spawnve(mode, file, ___argv, ___envp);

	env_path = libc_getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen  = libc_strlen(file);
		for (;;) {
			pid_t result;
			char *path_end;



			path_end = libc_strchrnul(env_path, ':');

			result = (__NAMESPACE_LOCAL_SYM __spawnvpe_impl)(mode, env_path, (size_t)(path_end - env_path),
			                                                 file, filelen, ___argv, ___envp);
			if (result >= 0)
				return result;
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {

		(void)libc_seterrno(ENOENT);

	}
	return -1;
}
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_OUT_OPT(1) pid_t
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
#include <asm/crt/process.h>
#include <libc/errno.h>
#include <asm/os/vfork.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_IN(3) ATTR_IN(4) pid_t
NOTHROW_RPC(LIBCCALL libc_fspawnve)(__STDC_INT_AS_UINT_T mode,
                                    fd_t execfd,
                                    __TARGV,
                                    __TENVP) {
	int status;





	errno_t old_errno;

	pid_t child;
	if (mode == P_OVERLAY)
		return libc_fexecve(execfd, ___argv, ___envp);

	old_errno = libc_geterrno_or(0);
	(void)libc_seterrno(0);






	if (mode == P_DETACH) {
		/* Daemonize (detach) the process using detach(2), or double-fork. */

		if (libc_vfork() == 0)



		{

			libc_detach(0); /* Detach myself from my parent. */
			goto do_exec;









		}
		child = 0;
		goto read_child_errors;
	}
	if (mode == P_WAIT) {
		/* Spawn and join the process */

		child = libc_vfork();



		if (child == 0)
			goto do_exec;
		if (child < 0)
			goto err;

		/* Check for errors that may have happened in  the
		 * child process _after_ we did the vfork() above. */
		if (libc_geterrno_or(0) != 0)
			goto err_join_zombie_child;
		/* Success (but still restore the old errno
		 * since  we  overwrote it  to be  0 above) */
		(void)libc_seterrno(old_errno);












		/* Join the child. */
		while (libc_waitpid(child, &status, 0) < 0) {

			if (__libc_geterrno() == EINTR)
				continue;

			goto err;
		}
		return (pid_t)(int)(unsigned int)WEXITSTATUS(status);
	}

	/* Spawn asynchronously. */

	child = libc_vfork();



	if (child == 0)
		goto do_exec;
read_child_errors:

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















err_join_zombie_child:
	if (mode != P_DETACH) {
		/* Unless the child was already spawned as detached,
		 * we still have to re-join  it, or else it will  be
		 * left dangling as a zombie process! */
		if (libc_waitpid(child, &status, 0) < 0) {

			if (__libc_geterrno() == EINTR)
				goto err_join_zombie_child;

		}
	}
err:
	return -1;
do_exec:
	/* When the exec succeeds, the pipe is auto-
	 * closed because it's marked as  O_CLOEXEC! */
	libc_fexecve(execfd, ___argv, ___envp);

	/* If the exec fails, it will have modified `errno' to indicate this fact.
	 * And since we're sharing VMs with  our parent process, the error  reason
	 * will have already  been written  back to  our parent's  VM, so  there's
	 * actually nothing left for us to do, but to simply exit! */











	libc__Exit(127);
}
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

	return dlclose((void *)(uintptr_t)hnd);




}
#include <dlfcn.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.dlfcn") ATTR_IN_OPT(2) __procfun
(LIBCCALL libc__getdllprocaddr)(intptr_t hnd,
                                char __KOS_FIXED_CONST *symname,
                                intptr_t ord) THROWS(...) {
	(void)ord;
	return (__procfun)dlsym((void *)(uintptr_t)hnd, symname);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_spawnl, libd_spawnl);
DEFINE_PUBLIC_ALIAS(DOS$spawnl, libd_spawnl);
DEFINE_PUBLIC_ALIAS(spawnl, libc_spawnl);
DEFINE_PUBLIC_ALIAS(DOS$_spawnlp, libd_spawnlp);
DEFINE_PUBLIC_ALIAS(DOS$spawnlp, libd_spawnlp);
DEFINE_PUBLIC_ALIAS(spawnlp, libc_spawnlp);
DEFINE_PUBLIC_ALIAS(DOS$_spawnle, libd_spawnle);
DEFINE_PUBLIC_ALIAS(DOS$spawnle, libd_spawnle);
DEFINE_PUBLIC_ALIAS(spawnle, libc_spawnle);
DEFINE_PUBLIC_ALIAS(DOS$_spawnlpe, libd_spawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$spawnlpe, libd_spawnlpe);
DEFINE_PUBLIC_ALIAS(spawnlpe, libc_spawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$_spawnv, libd_spawnv);
DEFINE_PUBLIC_ALIAS(DOS$spawnv, libd_spawnv);
DEFINE_PUBLIC_ALIAS(spawnv, libc_spawnv);
DEFINE_PUBLIC_ALIAS(DOS$_spawnvp, libd_spawnvp);
DEFINE_PUBLIC_ALIAS(DOS$spawnvp, libd_spawnvp);
DEFINE_PUBLIC_ALIAS(spawnvp, libc_spawnvp);
DEFINE_PUBLIC_ALIAS(DOS$_spawnve, libd_spawnve);
DEFINE_PUBLIC_ALIAS(DOS$spawnve, libd_spawnve);
DEFINE_PUBLIC_ALIAS(spawnve, libc_spawnve);
DEFINE_PUBLIC_ALIAS(DOS$_spawnvpe, libd_spawnvpe);
DEFINE_PUBLIC_ALIAS(DOS$spawnvpe, libd_spawnvpe);
DEFINE_PUBLIC_ALIAS(spawnvpe, libc_spawnvpe);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_cwait, libc_cwait);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(cwait, libc_cwait);
DEFINE_PUBLIC_ALIAS(fspawnve, libc_fspawnve);
DEFINE_PUBLIC_ALIAS(_endthread, libc__endthread);
DEFINE_PUBLIC_ALIAS(_c_exit, libc__c_exit);
DEFINE_PUBLIC_ALIAS(_unloaddll, libc__unloaddll);
DEFINE_PUBLIC_ALIAS(_getdllprocaddr, libc__getdllprocaddr);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PROCESS_C */
