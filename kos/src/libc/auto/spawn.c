/* HASH CRC-32:0xfe707d26 */
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
#ifndef GUARD_LIBC_AUTO_SPAWN_C
#define GUARD_LIBC_AUTO_SPAWN_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "spawn.h"
#include "../user/fcntl.h"
#include "../user/sched.h"
#include "../user/signal.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.wait.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/os/sigaction.h>
#include <libc/errno.h>
#include <hybrid/typecore.h>
#include <asm/os/vfork.h>
#include <asm/os/oflags.h>
#include <asm/os/signal.h>
/* >> posix_fspawn_np(3)
 * Implementation for the fastest possible  method of (safely) doing  fork(2)+fexecve(2)
 * in  order  to  spawn  a  new  process  from  the  given  `execfd'  file   descriptor.
 * For this purpose, any error that may happen during either the fork(3), the fexecve(2)
 * or  any of the numerous additional system calls that may be performed in-between will
 * be returned by this function to the  parent process, while the function itself  never
 * actually returns in the child process.
 * For this  purpose,  this  function tries  to  make  use of  `vfork(2)'  in  combination
 * with  `__ARCH_HAVE_SHARED_VM_VFORK',  and if  that  isn't available,  a  temporary pipe
 * is  used to communicate process initialization errors, as well as to await a successful
 * exec call by using the  fact that a successful exec  will close all `O_CLOEXEC'  files,
 * with the pipe having been given that flag, and that a pipe without both ends still open
 * will always  have its  read immediately  return  (which is  used to  indicate  success)
 * @param: pid:          Store the PID of the newly spawned child process here
 * @param: execfd:       The file descriptor pointing to the file that should be executed
 * @param: file_actions: [0..1] A set of additional actions to perform in regards to file-
 *                              handle operations. Can be used to (e.g.) re-direct  stdout
 *                              for the new process
 * @param: attrp:        [0..1] Additional process attributes to set for the child process
 * @param: argv:         Same as the `argv' accepted by `fexecve(2)'
 * @param: envp:         Same as the `envp' accepted by `fexecve(2)'
 * @return: 0 :          Success. (The child process's PID has been stored in `*pid')
 * @return: * :          Error (errno-code describing the reason of failure) */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_FDREAD(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_posix_fspawn_np)(pid_t *__restrict pid,
                                           fd_t execfd,
                                           posix_spawn_file_actions_t const *file_actions,
                                           posix_spawnattr_t const *attrp,
                                           __TARGV,
                                           __TENVP) {





	int status;




	errno_t result, old_errno;
	pid_t child;
	old_errno = __libc_geterrno_or(0);

	(void)libc_seterrno(0);
	child = libc_vfork();
	if (child == 0)
		goto do_exec;
	/* Check if the vfork() from  the child returned success, but  left
	 * our (vm-shared) errno as non-zero (which would indicate that the
	 * child encountered an error at  some point after vfork()  already
	 * succeeded) */
	result = __libc_geterrno_or(0);
	if (result != 0) {
		if (child < 0) {
			/* The vfork() itself failed. */
			(void)libc_seterrno(old_errno);
			return result;
		}
		/* Something within the child failed after vfork(). */
		goto err_join_zombie_child;
	}
	/* Restore the old errno */
	(void)libc_seterrno(old_errno);
	/* Write back the child's PID */
	*pid = child;
	return result;




























err_join_zombie_child:
	/* Unless the child was already spawned as detached,
	 * we still have to re-join  it, or else it will  be
	 * left dangling as a zombie process! */
	if (libc_waitpid(child, &status, 0) < 0) {

		if (__libc_geterrno() == EINTR)
			goto err_join_zombie_child;

	}
	(void)libc_seterrno(old_errno);
	return result;
do_exec:
	/* Perform additional actions within the child. */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("__used")
#pragma push_macro("__actions")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __used
#undef __actions
	if (file_actions) {
		unsigned int i;
		for (i = 0; i < file_actions->__used; ++i) {
			struct __spawn_action *act;
			act = &file_actions->__actions[i];
			switch (act->__sa_tag) {
#undef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION




			case __POSIX_SPAWN_ACTION_CLOSE:
				/* Close a file handle */
				if unlikely(libc_close(act->__sa_action.__sa_close_action.__sa_fd))
					goto child_error;
				break;






			case __POSIX_SPAWN_ACTION_DUP2:
				/* Duplicate a file handle */
				if unlikely(libc_dup2(act->__sa_action.__sa_dup2_action.__sa_oldfd,
				                 act->__sa_action.__sa_dup2_action.__sa_newfd))
					goto child_error;
				break;






			case __POSIX_SPAWN_ACTION_OPEN: {
				/* Open a file using `open(2)' */
				fd_t tempfd;
				tempfd = libc_open(act->__sa_action.__sa_open_action.__sa_path,
				              act->__sa_action.__sa_open_action.__sa_oflag,
				              act->__sa_action.__sa_open_action.__sa_mode);
				if unlikely(tempfd < 0)
					goto child_error;
				if likely(tempfd != act->__sa_action.__sa_open_action.__sa_fd) {
					if unlikely(libc_dup2(tempfd, act->__sa_action.__sa_open_action.__sa_fd))
						goto child_error;
					libc_close(tempfd);
				}
			}	break;






			case __POSIX_SPAWN_ACTION_CHDIR: {
				/* Change direction using `chdir(2)' */
				int error;
				error = libc_chdir(act->__sa_action.__sa_chdir_action.__sa_path);
				if unlikely(error != 0)
					goto child_error;
			}	break;






			case __POSIX_SPAWN_ACTION_FCHDIR: {
				/* Change direction using `fchdir(2)' */
				int error;
				error = libc_fchdir(act->__sa_action.__sa_fchdir_action.__sa_fd);
				if unlikely(error != 0)
					goto child_error;
			}	break;







			case __POSIX_SPAWN_ACTION_TCSETPGRP:
				/* NOTE: Passing `0' as second argument to `tcsetpgrp()' is the same as `getpid()' */
				if unlikely(libc_tcsetpgrp(act->__sa_action.__sa_tcsetpgrp_action.__sa_fd, 0))
					goto child_error;
				break;








			case __POSIX_SPAWN_ACTION_CLOSEFROM:
				libc_closefrom(act->__sa_action.__sa_closefrom_action.__sa_fd);
				break;




#ifdef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
#undef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
			default:

				(void)libc_seterrno(ENOSYS);





				goto child_error;
#else /* __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION */
			default:
				__builtin_unreachable();
#endif /* !__POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION */
			}
		}
	}
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__actions")
#pragma pop_macro("__used")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
	if (attrp) {
		if (attrp->__flags & __POSIX_SPAWN_RESETIDS) {


			if (libc_seteuid(libc_getuid()))
				goto child_error;


			if (libc_setegid(libc_getgid()))
				goto child_error;











		}
		if (attrp->__flags & __POSIX_SPAWN_SETPGROUP) {

			/* HINT: Passing `0' as first argument is the same as passing `getpid()'! */
			if unlikely(libc_setpgid(0, attrp->__pgrp))
				goto child_error;










		}
		if (attrp->__flags & __POSIX_SPAWN_SETSIGDEF) {

			signo_t i;
			struct sigaction sa;
			sa.sa_handler = (__sighandler_t)__SIG_DFL;
			sa.sa_flags   = 0;
			libc_sigemptyset(&sa.sa_mask);
			for (i = 0; (unsigned int)i < (unsigned int)(sizeof(attrp->__sd) / 8); ++i) {
				if (!libc_sigismember(&attrp->__sd, i))
					continue;
				if unlikely(libc_sigaction(i, &sa, NULL))
					goto child_error;
			}










		}
		if (attrp->__flags & __POSIX_SPAWN_SETSIGMASK) {

			if unlikely(libc_sigprocmask(__SIG_SETMASK, &attrp->__ss, NULL))
				goto child_error;










		}
		if (attrp->__flags & (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) {

			int error;
			if ((attrp->__flags & (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) ==
			    /*               */ (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) {
				error = libc_sched_setscheduler(0, attrp->__policy, &attrp->__sp);
			} else if (attrp->__flags & __POSIX_SPAWN_SETSCHEDPARAM) {
				error = libc_sched_setparam(0, &attrp->__sp);
			} else {
				struct sched_param param;
				error = libc_sched_getparam(0, &param);
				if likely(error == 0)
					error = libc_sched_setscheduler(0, attrp->__policy, &param);
			}
			if unlikely(error)
				goto child_error;










		}
	}
	/* When the exec succeeds, the pipe is auto-
	 * closed because it's marked as  O_CLOEXEC! */
	libc_fexecve(execfd, ___argv, ___envp);

	if (attrp && attrp->__flags & __POSIX_SPAWN_NOEXECERR) {
		/* Suppress the exec error. */

		(void)libc_seterrno(0);

	} else

	{
child_error:

		/* If the exec fails, it will have modified `errno' to indicate this fact.
		 * And since we're sharing VMs with  our parent process, the error  reason
		 * will have already  been written  back to  our parent's  VM, so  there's
		 * actually nothing left for us to do, but to simply exit! */
		;











	}
	libc__Exit(127);













}
#include <asm/os/oflags.h>
/* >> posix_spawn(3)
 * Implementation for the fastest possible method of (safely) doing fork(2)+execve(2)
 * in  order   to   spawn   a   new  process   from   the   given   `path'   program.
 * For this purpose, any error that may happen during either the fork(3), the execve(2)
 * or any of the numerous additional system calls that may be performed in-between will
 * be  returned by this function to the parent process, while the function itself never
 * actually returns in the child process.
 * For this  purpose,  this  function tries  to  make  use of  `vfork(2)'  in  combination
 * with  `__ARCH_HAVE_SHARED_VM_VFORK',  and if  that  isn't available,  a  temporary pipe
 * is  used to communicate process initialization errors, as well as to await a successful
 * exec call by using the  fact that a successful exec  will close all `O_CLOEXEC'  files,
 * with the pipe having been given that flag, and that a pipe without both ends still open
 * will always  have its  read immediately  return  (which is  used to  indicate  success)
 * @param: pid:          Store the PID of the newly spawned child process here
 * @param: path:         The pathname of the program that should be executed
 * @param: file_actions: [0..1] A set of additional actions to perform in regards to file-
 *                              handle operations. Can be used to (e.g.) re-direct  stdout
 *                              for the new process
 * @param: attrp:        [0..1] Additional process attributes to set for the child process
 * @param: argv:         Same as the `argv' accepted by `execve(2)'
 * @param: envp:         Same as the `envp' accepted by `execve(2)'
 * @return: 0 :          Success. (The child process's PID has been stored in `*pid')
 * @return: * :          Error (errno-code describing the reason of failure) */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_posix_spawn)(pid_t *__restrict pid,
                                       char const *__restrict path,
                                       posix_spawn_file_actions_t const *file_actions,
                                       posix_spawnattr_t const *attrp,
                                       __TARGV,
                                       __TENVP) {
	fd_t fd;
	pid_t result = -1;

	fd = libc_open(path, O_RDONLY | O_CLOEXEC);







	if likely(fd >= 0) {
		result = libc_posix_fspawn_np(pid, fd, file_actions, attrp, ___argv, ___envp);

		libc_close(fd);

	}
	return result;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__posix_spawnp_impl) __ATTR_NOINLINE __ATTR_NONNULL((1, 2, 4, 8, 9)) errno_t
(__LIBCCALL __posix_spawnp_impl)(pid_t *__restrict pid,
                                 char const *__restrict path, size_t path_len,
                                 char const *__restrict file, size_t file_len,
                                 posix_spawn_file_actions_t const *file_actions,
                                 posix_spawnattr_t const *attrp,
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
	return libc_posix_spawn(pid, fullpath, file_actions, attrp, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
/* >> posix_spawnp(3)
 * Same  as  `posix_spawn(3)',  but  search  `getenv("PATH")'  for  `file',  rather  than
 * directly making  use of  `file'  as the  absolute filename  of  the file  to  execute.
 * Note however  that  when  `file'  contains any  slashes,  `$PATH'  won't  be  searched
 * either, but instead, `file' is used as-is. (same as with `execve(2)' vs. `execvpe(3)') */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_posix_spawnp)(pid_t *__restrict pid,
                                        const char *__restrict file,
                                        posix_spawn_file_actions_t const *file_actions,
                                        posix_spawnattr_t const *attrp,
                                        __TARGV,
                                        __TENVP) {
	errno_t result;
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */



	if (libc_strchr(file, '/'))

	{
		return libc_posix_spawn(pid, file, file_actions, attrp, ___argv, ___envp);
	}
	env_path = libc_getenv("PATH");

	result = ENOENT;



	if (env_path && *env_path) {
		size_t filelen;
		filelen  = libc_strlen(file);
		for (;;) {
			char *path_end;



			path_end = libc_strchrnul(env_path, ':');

			result = (__NAMESPACE_LOCAL_SYM __posix_spawnp_impl)(pid, env_path, (size_t)(path_end - env_path),
			                                                     file, filelen, file_actions, attrp,
			                                                     ___argv, ___envp);
			if (result == 0)
				break;
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	}
	return result;
}
/* >> posix_spawnattr_init(3)
 * Initialize a given set of spawn attributes to all zero
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_init)(posix_spawnattr_t *__restrict attr) {
	libc_bzero(attr, sizeof(*attr));
	return 0;
}
/* >> posix_spawnattr_destroy(3)
 * Destroy a given set of spawn attributes
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_destroy)(posix_spawnattr_t *__restrict attr) {
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
	libc_memset(attr, 0xcc, sizeof(*attr));
#endif /* !NDEBUG && !NDEBUG_FINI */
	return 0;
}
/* >> posix_spawnattr_setflags(3)
 * Get the set of flags previously specified by `posix_spawnattr_setflags()'
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getflags)(posix_spawnattr_t const *__restrict attr,
                                                    short int *__restrict pflags) {
	*pflags = (short int)(unsigned short int)attr->__flags;
	return 0;
}
/* >> posix_spawnattr_setflags(3)
 * Specify the  set of  additional operations  to-be performed  by  the
 * child process prior to being started. The given `flags' is a set of:
 *   - POSIX_SPAWN_RESETIDS:      Perform 2 calls `seteuid(getuid())' and `setegid(getgid())'
 *   - POSIX_SPAWN_SETSIGDEF:     s.a. posix_spawnattr_setsigdefault(3)
 *   - POSIX_SPAWN_SETSIGMASK:    s.a. posix_spawnattr_setsigmask(3)
 *   - POSIX_SPAWN_SETPGROUP:     s.a. posix_spawnattr_setpgroup(3)
 *   - POSIX_SPAWN_SETSCHEDULER:  s.a. posix_spawnattr_setschedpolicy(3)
 *   - POSIX_SPAWN_SETSCHEDPARAM: s.a. posix_spawnattr_setschedparam(3)
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setflags)(posix_spawnattr_t *__restrict attr,
                                                    short int flags) {
	attr->__flags = (uint16_t)(unsigned short int)flags;
	return 0;
}
/* >> posix_spawnattr_getsigdefault(3)
 * Get the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigdefault)(posix_spawnattr_t const *__restrict attr,
                                                         sigset_t *__restrict sigdefault) {
	libc_memcpy(sigdefault, &attr->__sd, sizeof(sigset_t));
	return 0;
}
/* >> posix_spawnattr_setsigdefault(3)
 * Set the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigdefault)(posix_spawnattr_t *__restrict attr,
                                                         sigset_t const *__restrict sigdefault) {
	libc_memcpy(&attr->__sd, sigdefault, sizeof(sigset_t));
	return 0;
}
/* >> posix_spawnattr_getsigmask(3)
 * Get the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigmask)(posix_spawnattr_t const *__restrict attr,
                                                      sigset_t *__restrict sigmask) {
	libc_memcpy(sigmask, &attr->__ss, sizeof(sigset_t));
	return 0;
}
/* >> posix_spawnattr_getsigmask(3)
 * Set the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigmask)(posix_spawnattr_t *__restrict attr,
                                                      sigset_t const *__restrict sigmask) {
	libc_memcpy(&attr->__ss, sigmask, sizeof(sigset_t));
	return 0;
}
/* >> posix_spawnattr_getpgroup(3)
 * Get the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getpgroup)(posix_spawnattr_t const *__restrict attr,
                                                     pid_t *__restrict pgroup) {
	*pgroup = attr->__pgrp;
	return 0;
}
/* >> posix_spawnattr_getschedparam(3)
 * Set the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * HINT: A call `setpgid(getpid(), 0)' is the same as `setpgid(getpid(), getpid())'!
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setpgroup)(posix_spawnattr_t *__restrict attr,
                                                     pid_t pgroup) {
	attr->__pgrp = pgroup;
	return 0;
}
/* >> posix_spawnattr_getschedparam(3)
 * Get the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedpolicy)(posix_spawnattr_t const *__restrict attr,
                                                          int *__restrict schedpolicy) {
	*schedpolicy = attr->__policy;
	return 0;
}
/* >> posix_spawnattr_getschedparam(3)
 * Set the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedpolicy)(posix_spawnattr_t *__restrict attr,
                                                          int schedpolicy) {
	attr->__policy = schedpolicy;
	return 0;
}
/* >> posix_spawnattr_getschedparam(3)
 * Get the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedparam)(posix_spawnattr_t const *__restrict attr,
                                                         struct sched_param *__restrict schedparam) {
	libc_memcpy(schedparam, &attr->__sp, sizeof(struct sched_param));
	return 0;
}
/* >> posix_spawnattr_setschedparam(3)
 * Set the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedparam)(posix_spawnattr_t *__restrict attr,
                                                         struct sched_param const *__restrict schedparam) {
	libc_memcpy(&attr->__sp, schedparam, sizeof(struct sched_param));
	return 0;
}
/* >> posix_spawn_file_actions_init(3)
 * Initialize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_init)(posix_spawn_file_actions_t *__restrict file_actions) {
	libc_bzero(file_actions, sizeof(*file_actions));
	return 0;
}
/* >> posix_spawn_file_actions_destroy(3)
 * Finalize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_destroy)(posix_spawn_file_actions_t *__restrict file_actions) {

	unsigned int i;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("__used")
#pragma push_macro("__actions")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __used
#undef __actions
	for (i = 0; i < (unsigned int)file_actions->__used; ++i) {
		struct __spawn_action *act;
		act = &file_actions->__actions[i];
		switch (act->__sa_tag) {

		case __POSIX_SPAWN_ACTION_OPEN:
			libc_free(act->__sa_action.__sa_open_action.__sa_path);
			break;

		default:
			break;
		}
	}
	libc_free(file_actions->__actions);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__actions")
#pragma pop_macro("__used")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
	libc_memset(file_actions, 0xcc, sizeof(*file_actions));
#endif /* !NDEBUG && !NDEBUG_FINI */
	return 0;
}
/* Helper functions for allocating an a new file-spawn action entry */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") WUNUSED ATTR_INOUT(1) struct __spawn_action *
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_alloc)(posix_spawn_file_actions_t *__restrict file_actions) {
	struct __spawn_action *result;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("__used")
#pragma push_macro("__actions")
#pragma push_macro("__allocated")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __used
#undef __actions
#undef __allocated
	result = file_actions->__actions;
	if ((unsigned int)file_actions->__used >= (unsigned int)file_actions->__allocated) {
		unsigned int newalloc;
		newalloc = (unsigned int)file_actions->__used + 8;
		result   = (struct __spawn_action *)libc_realloc(result, newalloc * sizeof(struct __spawn_action));
		if unlikely(!result) {
			newalloc = (unsigned int)file_actions->__used + 1;
			result = file_actions->__actions;
			result = (struct __spawn_action *)libc_realloc(result, newalloc * sizeof(struct __spawn_action));
			if unlikely(!result)
				return NULL;
		}
		file_actions->__actions   = result;
		file_actions->__allocated = newalloc;
	}
	result += file_actions->__used++;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__used")
#pragma pop_macro("__actions")
#pragma pop_macro("__allocated")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
	return result;
}
/* >> posix_spawn_file_actions_addopen(3)
 * Enqueue a call `dup2(open(path, oflags, mode), fd)' to be performed by the child process
 * Note though  that the  intermediate file  returned by  `open(2)' will  not remain  open!
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(3) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addopen)(posix_spawn_file_actions_t *__restrict file_actions,
                                                            fd_t fd,
                                                            char const *__restrict path,
                                                            oflag_t oflags,
                                                            mode_t mode) {
	struct __spawn_action *action;
	/* Posix says:
	 * """
	 * The string described by path shall be copied  by
	 * the posix_spawn_file_actions_addopen() function.
	 * """
	 * iow: We need to strdup(path) here! */
	if unlikely((path = libc_strdup(path)) == NULL)
		goto err;
	action = libc_posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err_path;
	/* Fill in the new mode. */
	action->__sa_tag = __POSIX_SPAWN_ACTION_OPEN;
	action->__sa_action.__sa_open_action.__sa_fd    = fd;
	action->__sa_action.__sa_open_action.__sa_path  = (char *)path;
	action->__sa_action.__sa_open_action.__sa_oflag = oflags;
	action->__sa_action.__sa_open_action.__sa_mode  = mode;
	return 0;
err_path:

	libc_free((char *)path);

err:

	return ENOMEM;



}
/* >> posix_spawn_file_actions_addclose(3)
 * Enqueue a call `close(fd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_FDARG(2) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addclose)(posix_spawn_file_actions_t *__restrict file_actions,
                                                             fd_t fd) {
	struct __spawn_action *action;
	action = libc_posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->__sa_tag = __POSIX_SPAWN_ACTION_CLOSE;
	action->__sa_action.__sa_close_action.__sa_fd = fd;
	return 0;
err:

	return ENOMEM;



}
/* >> posix_spawn_file_actions_adddup2(3)
 * Enqueue a call `dup2(oldfd, newfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_FDARG(2) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_adddup2)(posix_spawn_file_actions_t *__restrict file_actions,
                                                            fd_t oldfd,
                                                            fd_t newfd) {
	struct __spawn_action *action;
	action = libc_posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->__sa_tag = __POSIX_SPAWN_ACTION_DUP2;
	action->__sa_action.__sa_dup2_action.__sa_oldfd = oldfd;
	action->__sa_action.__sa_dup2_action.__sa_newfd = newfd;
	return 0;
err:

	return ENOMEM;



}
/* >> posix_spawn_file_actions_addtcsetpgrp_np(3)
 * Enqueue a call `tcsetpgrp(fd, getpid())' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_FDARG(2) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addtcsetpgrp_np)(posix_spawn_file_actions_t *__restrict file_actions,
                                                                    fd_t fd) {
	struct __spawn_action *action;
	action = libc_posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->__sa_tag = __POSIX_SPAWN_ACTION_TCSETPGRP;
	action->__sa_action.__sa_tcsetpgrp_action.__sa_fd = fd;
	return 0;
err:

	return ENOMEM;



}
/* >> posix_spawn_file_actions_addclosefrom_np(3)
 * Enqueue a call `closefrom(lowfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addclosefrom_np)(posix_spawn_file_actions_t *__restrict file_actions,
                                                                    fd_t lowfd) {
	struct __spawn_action *action;
	action = libc_posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->__sa_tag = __POSIX_SPAWN_ACTION_CLOSEFROM;
	action->__sa_action.__sa_closefrom_action.__sa_fd = lowfd;
	return 0;
err:

	return ENOMEM;



}
/* >> posix_spawn_file_actions_addchdir_np(3)
 * Enqueue a call `chdir(path)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addchdir_np)(posix_spawn_file_actions_t *__restrict file_actions,
                                                                const char *__restrict path) {
	struct __spawn_action *action;
	if unlikely((path = libc_strdup(path)) == NULL)
		goto err;
	action = libc_posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err_path;
	/* Fill in the new mode. */
	action->__sa_tag = __POSIX_SPAWN_ACTION_CHDIR;
	action->__sa_action.__sa_chdir_action.__sa_path = (char *)path;
	return 0;
err_path:

	libc_free((char *)path);

err:

	return ENOMEM;



}
/* >> posix_spawn_file_actions_addfchdir_np(3)
 * Enqueue a call `fchdir(dfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_FDARG(2) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addfchdir_np)(posix_spawn_file_actions_t *__restrict file_actions,
                                                                 fd_t dfd) {
	struct __spawn_action *action;
	action = libc_posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->__sa_tag = __POSIX_SPAWN_ACTION_FCHDIR;
	action->__sa_action.__sa_fchdir_action.__sa_fd = dfd;
	return 0;
err:

	return ENOMEM;



}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(posix_fspawn_np, libc_posix_fspawn_np);
DEFINE_PUBLIC_ALIAS(posix_spawn, libc_posix_spawn);
DEFINE_PUBLIC_ALIAS(posix_spawnp, libc_posix_spawnp);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_init, libc_posix_spawnattr_init);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_destroy, libc_posix_spawnattr_destroy);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getflags, libc_posix_spawnattr_getflags);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setflags, libc_posix_spawnattr_setflags);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getsigdefault, libc_posix_spawnattr_getsigdefault);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setsigdefault, libc_posix_spawnattr_setsigdefault);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getsigmask, libc_posix_spawnattr_getsigmask);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setsigmask, libc_posix_spawnattr_setsigmask);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getpgroup, libc_posix_spawnattr_getpgroup);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setpgroup, libc_posix_spawnattr_setpgroup);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getschedpolicy, libc_posix_spawnattr_getschedpolicy);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setschedpolicy, libc_posix_spawnattr_setschedpolicy);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_getschedparam, libc_posix_spawnattr_getschedparam);
DEFINE_PUBLIC_ALIAS(posix_spawnattr_setschedparam, libc_posix_spawnattr_setschedparam);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_init, libc_posix_spawn_file_actions_init);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_destroy, libc_posix_spawn_file_actions_destroy);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_addopen, libc_posix_spawn_file_actions_addopen);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_addclose, libc_posix_spawn_file_actions_addclose);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_adddup2, libc_posix_spawn_file_actions_adddup2);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_addtcsetpgrp_np, libc_posix_spawn_file_actions_addtcsetpgrp_np);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_addclosefrom_np, libc_posix_spawn_file_actions_addclosefrom_np);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_addchdir_np, libc_posix_spawn_file_actions_addchdir_np);
DEFINE_PUBLIC_ALIAS(posix_spawn_file_actions_addfchdir_np, libc_posix_spawn_file_actions_addfchdir_np);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SPAWN_C */
