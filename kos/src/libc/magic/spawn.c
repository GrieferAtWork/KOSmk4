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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]
%[define_replacement(posix_spawnattr_t = "struct __posix_spawnattr")]
%[define_replacement(posix_spawn_file_actions_t = "struct __posix_spawn_file_actions")]
%[default:section(".text.crt{|.dos}.fs.exec.posix_spawn")]


%{
#include <features.h>

}%[insert:prefix(
#include <asm/crt/posix_spawn.h>
)]%[insert:prefix(
#include <bits/crt/posix_spawn.h>
)]%{
#include <bits/sched_param.h>
#include <bits/sigset.h> /* struct __sigset_struct */
#include <bits/types.h>
#include <sys/types.h>

#ifdef __USE_GLIBC
#include <sched.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

/* Flags to be set in the `posix_spawnattr_t'. */

#ifdef __POSIX_SPAWN_RESETIDS
#define POSIX_SPAWN_RESETIDS __POSIX_SPAWN_RESETIDS /* Perform 2 calls `seteuid(getuid())' and `setegid(getgid())' */
#endif /* __POSIX_SPAWN_RESETIDS */
#ifdef __POSIX_SPAWN_SETPGROUP
#define POSIX_SPAWN_SETPGROUP __POSIX_SPAWN_SETPGROUP /* s.a. `posix_spawnattr_setpgroup(3)' */
#endif /* __POSIX_SPAWN_SETPGROUP */
#ifdef __POSIX_SPAWN_SETSIGDEF
#define POSIX_SPAWN_SETSIGDEF __POSIX_SPAWN_SETSIGDEF /* s.a. `posix_spawnattr_setsigdefault(3)' */
#endif /* __POSIX_SPAWN_SETSIGDEF */
#ifdef __POSIX_SPAWN_SETSIGMASK
#define POSIX_SPAWN_SETSIGMASK __POSIX_SPAWN_SETSIGMASK /* s.a. `posix_spawnattr_setsigmask(3)' */
#endif /* __POSIX_SPAWN_SETSIGMASK */
#ifdef __POSIX_SPAWN_SETSCHEDPARAM
#define POSIX_SPAWN_SETSCHEDPARAM __POSIX_SPAWN_SETSCHEDPARAM /* s.a. `posix_spawnattr_setschedparam(3)' */
#endif /* __POSIX_SPAWN_SETSCHEDPARAM */
#ifdef __POSIX_SPAWN_SETSCHEDULER
#define POSIX_SPAWN_SETSCHEDULER __POSIX_SPAWN_SETSCHEDULER /* s.a. `posix_spawnattr_setschedpolicy(3)' */
#endif /* __POSIX_SPAWN_SETSCHEDULER */
#ifdef __USE_GNU
#ifdef __POSIX_SPAWN_USEVFORK
#define POSIX_SPAWN_USEVFORK __POSIX_SPAWN_USEVFORK /* Ignored */
#endif /* __POSIX_SPAWN_USEVFORK */
#endif /* __USE_GNU */

#ifdef __POSIX_SPAWN_NOEXECERR
#define POSIX_SPAWN_NOEXECERR_NP __POSIX_SPAWN_NOEXECERR /* Don't propagate exec() error, and leave the
                                                          * child as unreaped with exit status `127' */
#endif /* __POSIX_SPAWN_NOEXECERR */


#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !pid_t_defined */

#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* ! */
#endif /* !__TARGV */

typedef struct __posix_spawnattr posix_spawnattr_t;
typedef struct __posix_spawn_file_actions posix_spawn_file_actions_t;

}

%[define(DEFINE_TARGV =
@@pp_ifndef __TARGV@@
@@pp_ifdef __USE_DOS@@
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
@@pp_else@@
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
@@pp_endif@@
@@pp_endif@@
)]


[[ignore, nocrt, alias("posix_spawn")]]
[[argument_names(pid, path, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
$errno_t crt_posix_spawn([[nonnull]] pid_t *__restrict pid,
                         [[nonnull]] char const *__restrict path,
                         [[nullable]] posix_spawn_file_actions_t const *file_actions,
                         [[nullable]] posix_spawnattr_t const *attrp,
                         [[nonnull]] __TARGV, [[nonnull]] __TENVP);


%#ifdef __USE_KOS

@@>> posix_fspawn_np(3)
@@Implementation for the fastest possible method of (safely) doing fork(2)+fexecve(2)
@@in order to spawn a new process from the given `execfd' file descriptor.
@@For this purpose, any error that may happen during either the fork(3), the fexecve(2)
@@or any of the numerous additional system calls that may be performed in-between will
@@be returned by this function to the parent process, while the function itself never
@@actually returns in the child process.
@@For this purpose, this function tries to make use of `vfork(2)' in combination
@@with `__ARCH_HAVE_SHARED_VM_VFORK', and if that isn't available, a temporary pipe
@@is used to communicate process initialization errors, as well as to await a successful
@@exec call by using the fact that a successful exec will close all `O_CLOEXEC' files,
@@with the pipe having been given that flag, and that a pipe without both ends still open
@@will always have its read immediately return (which is used to indicate success)
@@@param: pid:          Store the PID of the newly spawned child process here
@@@param: execfd:       The file descriptor pointing to the file that should be executed
@@@param: file_actions: [0..1] A set of additional actions to perform in regards to file-
@@                             handle operations. Can be used to (e.g.) re-direct stdout
@@                             for the new process
@@@param: attrp:        [0..1] Additional process attributes to set for the child process
@@@param: argv:         Same as the `argv' accepted by `fexecve(2)'
@@@param: envp:         Same as the `envp' accepted by `fexecve(2)'
@@@return: 0 :          Success. (The child process's PID has been stored in `*pid')
@@@return: * :          Error errno-code describing the reason of failure
[[argument_names(pid, execfd, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[impl_include("<bits/sigaction-struct.h>", "<libc/errno.h>")]]
[[impl_include("<asm/vfork.h>", "<asm/oflags.h>", "<asm/os/signal.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>", "<asm/vfork.h>")]]
[[requires((defined(__POSIX_SPAWN_USE_KOS) && 
            ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)) ||
             ($has_function(fork) && ($has_function(pipe2) && defined(O_CLOEXEC)) &&
              $has_function(read) && $has_function(write) && $has_function(close))) &&
            $has_function(fexecve) && $has_function(waitpid)) ||
           $has_function(crt_posix_spawn))]]
$errno_t posix_fspawn_np([[nonnull]] pid_t *__restrict pid, $fd_t execfd,
                         [[nullable]] posix_spawn_file_actions_t const *file_actions,
                         [[nullable]] posix_spawnattr_t const *attrp,
                         [[nonnull]] __TARGV, [[nonnull]] __TENVP) {
@@pp_if defined(__POSIX_SPAWN_USE_KOS) && 
        ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)) ||
         ($has_function(fork) && ($has_function(pipe2) && defined(O_CLOEXEC)) &&
          $has_function(read) && $has_function(write) && $has_function(close))) &&
        $has_function(fexecve) && $has_function(waitpid)@@
	int status;
@@pp_if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || !$has_function(vfork)@@
	fd_t pipes[2];
	ssize_t temp;
@@pp_endif@@
	errno_t result, old_errno;
	pid_t child;
	old_errno = __libc_geterrno_or(0);
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
	__libc_seterrno(0);
	child = vfork();
	if (child == 0)
		goto do_exec;
	/* Check if the vfork() from the child returned success, but left
	 * our (vm-shared) errno as non-zero (which would indicate that the
	 * child encountered an error at some point after vfork() already
	 * succeeded) */
	result = __libc_geterrno_or(0);
	if (result != 0)
		goto err_join_zombie_child;
	/* Restore the old errno */
	__libc_seterrno(old_errno);
	/* Write back the child's PID */
	*pid = child;
	return result;
@@pp_else@@
	/* Create a pair of pipes for temporary communication. */
	if (pipe2(pipes, O_CLOEXEC)) {
		result = __libc_geterrno_or(0);
		__libc_seterrno(old_errno);
		return result;
	}
	child = fork();
	if (child == 0)
		goto do_exec;
	/* Read from the communication pipe
	 * (NOTE: If exec() succeeds, the pipe will be
	 *        closed and read() returns ZERO(0)) */
	close(pipes[1]); /* Close the writer. */
	temp = read(pipes[0], &result, sizeof(result));
	close(pipes[0]); /* Close the reader. */
	if (temp < 0)
		goto err_join_zombie_child;
	/* This means that `fexecve()' below closed the pipe during a successful exec(). */
	if (temp != sizeof(result)) {
		*pid = child;
		__libc_seterrno(old_errno);
		return 0;
	}
@@pp_endif@@
err_join_zombie_child:
	/* Unless the child was already spawned as detached,
	 * we still have to re-join it, or else it will be
	 * left dangling as a zombie process! */
	if (waitpid(child, &status, 0) < 0) {
@@pp_ifdef EINTR@@
		if (__libc_geterrno() == EINTR)
			goto err_join_zombie_child;
@@pp_endif@@
	}
	__libc_seterrno(old_errno);
	return result;
do_exec:
	/* Perform additional actions within the child. */
	if (file_actions) {
		unsigned int i;
		for (i = 0; i < file_actions->@__used@; ++i) {
			struct __spawn_action *act;
			act = &file_actions->@__actions@[i];
			switch (act->@__sa_tag@) {
#undef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION

@@pp_if !$has_function(close)@@
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
@@pp_else@@
			case __POSIX_SPAWN_ACTION_CLOSE:
				/* Close a file handle */
				if unlikely(close(act->@__sa_action@.@__sa_close_action@.@__sa_fd@))
					goto child_error;
				break;
@@pp_endif@@


@@pp_if !$has_function(dup2)@@
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
@@pp_else@@
			case __POSIX_SPAWN_ACTION_DUP2:
				/* Duplicate a file handle */
				if unlikely(dup2(act->@__sa_action@.@__sa_dup2_action@.@__sa_oldfd@,
				                 act->@__sa_action@.@__sa_dup2_action@.@__sa_newfd@))
					goto child_error;
				break;
@@pp_endif@@


@@pp_if !($has_function(open) && $has_function(dup2) && $has_function(close))@@
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
@@pp_else@@
			case __POSIX_SPAWN_ACTION_OPEN: {
				/* Open a file using `open(2)' */
				fd_t tempfd;
				tempfd = open(act->@__sa_action@.@__sa_open_action@.@__sa_path@,
				              act->@__sa_action@.@__sa_open_action@.@__sa_oflag@,
				              act->@__sa_action@.@__sa_open_action@.@__sa_mode@);
				if unlikely(tempfd < 0)
					goto child_error;
				if likely(tempfd != act->@__sa_action@.@__sa_open_action@.@__sa_fd@) {
					if unlikely(dup2(tempfd, act->@__sa_action@.@__sa_open_action@.@__sa_fd@))
						goto child_error;
					close(tempfd);
				}
			}	break;
@@pp_endif@@


@@pp_ifdef __POSIX_SPAWN_ACTION_TCSETPGRP@@
@@pp_if !$has_function(tcsetpgrp)@@
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
@@pp_else@@
			case __POSIX_SPAWN_ACTION_TCSETPGRP:
				/* NOTE: Passing `0' as second argument to `tcsetpgrp()' is the same as `getpid()' */
				if unlikely(tcsetpgrp(act->@__sa_action@.@__sa_tcsetpgrp_action@.@__sa_fd@, 0))
					goto child_error;
				break;
@@pp_endif@@
@@pp_endif@@


@@pp_ifdef __POSIX_SPAWN_ACTION_CLOSEFROM@@
@@pp_if !$has_function(closefrom)@@
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
@@pp_else@@
			case __POSIX_SPAWN_ACTION_CLOSEFROM:
				closefrom(act->@__sa_action@.@__sa_closefrom_action@.@__sa_fd@);
				break;
@@pp_endif@@
@@pp_endif@@


@@pp_ifdef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION@@
#undef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
			default:
@@pp_ifdef ENOSYS@@
				__libc_seterrno(ENOSYS);
@@pp_elif defined(EPERM)@@
				__libc_seterrno(EPERM);
@@pp_else@@
				__libc_seterrno(1);
@@pp_endif@@
				goto child_error;
@@pp_else@@
			default:
				__builtin_unreachable();
@@pp_endif@@
			}
		}
	}
	if (attrp) {
		if (attrp->@__flags@ & __POSIX_SPAWN_RESETIDS) {
@@pp_if ($has_function(seteuid) && $has_function(getuid)) || ($has_function(setegid) && $has_function(getgid))@@
@@pp_if $has_function(seteuid) && $has_function(getuid)@@
			if (seteuid(getuid()))
				goto child_error;
@@pp_endif@@
@@pp_if $has_function(setegid) && $has_function(getgid)@@
			if (setegid(getgid()))
				goto child_error;
@@pp_endif@@
@@pp_else@@
@@pp_ifdef ENOSYS@@
			__libc_seterrno(ENOSYS);
@@pp_elif defined(EPERM)@@
			__libc_seterrno(EPERM);
@@pp_else@@
			__libc_seterrno(1);
@@pp_endif@@
			goto child_error;
@@pp_endif@@
		}
		if (attrp->@__flags@ & __POSIX_SPAWN_SETPGROUP) {
@@pp_if $has_function(setpgid)@@
			/* HINT: Passing `0' as first argument is the same as passing `getpid()'! */
			if unlikely(setpgid(0, attrp->@__pgrp@))
				goto child_error;
@@pp_else@@
@@pp_ifdef ENOSYS@@
			__libc_seterrno(ENOSYS);
@@pp_elif defined(EPERM)@@
			__libc_seterrno(EPERM);
@@pp_else@@
			__libc_seterrno(1);
@@pp_endif@@
			goto child_error;
@@pp_endif@@
		}
		if (attrp->@__flags@ & __POSIX_SPAWN_SETSIGDEF) {
@@pp_if $has_function(sigaction) && defined(__SIG_DFL)@@
			signo_t i;
			struct @sigaction@ sa;
			sa.@sa_handler@ = (@__sighandler_t@)@__SIG_DFL@;
			sa.@sa_flags@   = 0;
			sigemptyset(&sa.@sa_mask@);
			for (i = 0; (unsigned int)i < (unsigned int)(sizeof(attrp->@__sd@) / 8); ++i) {
				if (!sigismember(&attrp->@__sd@, i))
					continue;
				if unlikely(sigaction(i, &sa, NULL))
					goto child_error;
			}
@@pp_else@@
@@pp_ifdef ENOSYS@@
			__libc_seterrno(ENOSYS);
@@pp_elif defined(EPERM)@@
			__libc_seterrno(EPERM);
@@pp_else@@
			__libc_seterrno(1);
@@pp_endif@@
			goto child_error;
@@pp_endif@@
		}
		if (attrp->@__flags@ & __POSIX_SPAWN_SETSIGMASK) {
@@pp_if $has_function(sigprocmask) && defined(__SIG_SETMASK)@@
			if unlikely(sigprocmask(__SIG_SETMASK, &attrp->@__ss@, NULL))
				goto child_error;
@@pp_else@@
@@pp_ifdef ENOSYS@@
			__libc_seterrno(ENOSYS);
@@pp_elif defined(EPERM)@@
			__libc_seterrno(EPERM);
@@pp_else@@
			__libc_seterrno(1);
@@pp_endif@@
			goto child_error;
@@pp_endif@@
		}
		if (attrp->@__flags@ & (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) {
@@pp_if $has_function(sched_setscheduler) && $has_function(sched_setparam) && $has_function(sched_getparam)@@
			int error;
			if ((attrp->@__flags@ & (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) ==
			    /*               */ (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) {
				error = sched_setscheduler(0, attrp->@__policy@, &attrp->@__sp@);
			} else if (attrp->@__flags@ & __POSIX_SPAWN_SETSCHEDPARAM) {
				error = sched_setparam(0, &attrp->@__sp@);
			} else {
				struct sched_param param;
				error = sched_getparam(0, &param);
				if likely(error == 0)
					error = sched_setscheduler(0, attrp->@__policy@, &param);
			}
			if unlikely(error)
				goto child_error;
@@pp_else@@
@@pp_ifdef ENOSYS@@
			__libc_seterrno(ENOSYS);
@@pp_elif defined(EPERM)@@
			__libc_seterrno(EPERM);
@@pp_else@@
			__libc_seterrno(1);
@@pp_endif@@
			goto child_error;
@@pp_endif@@
		}
	}
	/* When the exec succeeds, the pipe is auto-
	 * closed because it's marked as O_CLOEXEC! */
	fexecve(execfd, ___argv, ___envp);
@@pp_ifdef __POSIX_SPAWN_NOEXECERR@@
	if (attrp && attrp->@__flags@ & __POSIX_SPAWN_NOEXECERR) {
		/* Suppress the exec error. */
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
		__libc_seterrno(0);
@@pp_endif@@
	} else
@@pp_endif@@
	{
child_error:
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
		/* If the exec fails, it will have modified `errno' to indicate this fact.
		 * And since we're sharing VMs with our parent process, the error reason
		 * will have already been written back to our parent's VM, so there's
		 * actually nothing left for us to do, but to simply exit! */
		;
@@pp_else@@
		/* Write the exec-error back to our parent. */
@@pp_ifdef ENOENT@@
		error = __libc_geterrno_or(ENOENT);
@@pp_else@@
		error = __libc_geterrno_or(1);
@@pp_endif@@
		/* Communicate back why this failed. */
		write(pipes[1], &error, sizeof(error));
		/* No need to close the pipe, it's auto-closed by the kernel! */
@@pp_endif@@
	}
	_Exit(127);
@@pp_else@@
	char buf[32];
	sprintf(buf, "/proc/self/fd/%d", execfd);
	return crt_posix_spawn(pid, buf, file_actions, attrp, ___argv, ___envp);
@@pp_endif@@
}
%#endif /* __USE_KOS */



@@>> posix_spawn(3)
@@Implementation for the fastest possible method of (safely) doing fork(2)+execve(2)
@@in order to spawn a new process from the given `path' program.
@@For this purpose, any error that may happen during either the fork(3), the execve(2)
@@or any of the numerous additional system calls that may be performed in-between will
@@be returned by this function to the parent process, while the function itself never
@@actually returns in the child process.
@@For this purpose, this function tries to make use of `vfork(2)' in combination
@@with `__ARCH_HAVE_SHARED_VM_VFORK', and if that isn't available, a temporary pipe
@@is used to communicate process initialization errors, as well as to await a successful
@@exec call by using the fact that a successful exec will close all `O_CLOEXEC' files,
@@with the pipe having been given that flag, and that a pipe without both ends still open
@@will always have its read immediately return (which is used to indicate success)
@@@param: pid:          Store the PID of the newly spawned child process here
@@@param: path:         The pathname of the program that should be executed
@@@param: file_actions: [0..1] A set of additional actions to perform in regards to file-
@@                             handle operations. Can be used to (e.g.) re-direct stdout
@@                             for the new process
@@@param: attrp:        [0..1] Additional process attributes to set for the child process
@@@param: argv:         Same as the `argv' accepted by `execve(2)'
@@@param: envp:         Same as the `envp' accepted by `execve(2)'
@@@return: 0 :          Success. (The child process's PID has been stored in `*pid')
@@@return: * :          Error errno-code describing the reason of failure
[[requires_function(open, posix_fspawn_np), impl_include("<asm/oflags.h>")]]
[[argument_names(pid, path, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
$errno_t posix_spawn([[nonnull]] pid_t *__restrict pid,
                     [[nonnull]] char const *__restrict path,
                     [[nullable]] posix_spawn_file_actions_t const *file_actions,
                     [[nullable]] posix_spawnattr_t const *attrp,
                     [[nonnull]] __TARGV, [[nonnull]] __TENVP) {
	fd_t fd;
	pid_t result = -1;
@@pp_if defined(O_RDONLY) && defined(O_CLOEXEC)@@
	fd = open(path, O_RDONLY | O_CLOEXEC);
@@pp_elif defined(O_RDONLY)@@
	fd = open(path, O_RDONLY);
@@pp_else@@
	fd = open(path, 0);
@@pp_endif@@
	if likely(fd >= 0) {
		result = posix_fspawn_np(pid, fd, file_actions, attrp, ___argv, ___envp);
@@pp_if $has_function(close)@@
		close(fd);
@@pp_endif@@
	}
	return result;
}



@@>> posix_spawnp(3)
@@Same as `posix_spawn(3)', but search `getenv("PATH")' for `file', rather than
@@directly making use of `file' as the absolute filename of the file to execute.
@@Note however that when `file' contains any slashes, `$PATH' won't be searched
@@either, but instead, `file' is used as-is. (same as with `execve(2)' vs. `execvpe(3)')
[[requires_include("<hybrid/__alloca.h>")]]
[[requires($has_function(getenv) && $has_function(posix_spawn) && defined(__hybrid_alloca))]]
[[argument_names(pid, file, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<libc/errno.h>")]]
[[impl_prefix(
@@push_namespace(local)@@
__LOCAL_LIBC(__posix_spawnp_impl) __ATTR_NOINLINE __ATTR_NONNULL((1, 2, 4, 8, 9)) $errno_t
(__LIBCCALL __posix_spawnp_impl)($pid_t *__restrict pid,
                                 char const *__restrict path, $size_t path_len,
                                 char const *__restrict file, $size_t file_len,
                                 posix_spawn_file_actions_t const *file_actions,
                                 posix_spawnattr_t const *attrp,
                                 __TARGV, __TENVP) {
	char *fullpath, *dst;
@@pp_ifdef _WIN32@@
	while (path_len && (path[path_len - 1] == '/' ||
	                    path[path_len - 1] == '\\'))
		--path_len;
@@pp_else@@
	while (path_len && path[path_len - 1] == '/')
		--path_len;
@@pp_endif@@
	fullpath = (char *)__hybrid_alloca((path_len + 1 + file_len + 1) *
	                                   sizeof(char));
	dst = (char *)mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return posix_spawn(pid, fullpath, file_actions, attrp, ___argv, ___envp);
}
@@pop_namespace@@
)]]
$errno_t posix_spawnp([[nonnull]] pid_t *__restrict pid,
                      [[nonnull]] const char *__restrict file,
                      [[nullable]] posix_spawn_file_actions_t const *file_actions,
                      [[nullable]] posix_spawnattr_t const *attrp,
                      [[nonnull]] __TARGV, [[nonnull]] __TENVP) {
	errno_t result;
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the specified
	 * pathname is executed.
	 * [...] */
@@pp_ifdef _WIN32@@
	if (strchr(file, '/') || strchr(file, '\\'))
@@pp_else@@
	if (strchr(file, '/'))
@@pp_endif@@
	{
		return posix_spawn(pid, file, file_actions, attrp, ___argv, ___envp);
	}
	env_path = getenv("PATH");
@@pp_ifdef ENOENT@@
	result = ENOENT;
@@pp_else@@
	result = 1;
@@pp_endif@@
	if (env_path && *env_path) {
		size_t filelen;
		filelen  = strlen(file);
		for (;;) {
			char *path_end;
@@pp_ifdef _WIN32@@
			path_end = strchrnul(env_path, ';');
@@pp_else@@
			path_end = strchrnul(env_path, ':');
@@pp_endif@@
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


@@>> posix_spawnattr_init(3)
@@Initialize a given set of spawn attributes to all zero
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
$errno_t posix_spawnattr_init([[nonnull]] posix_spawnattr_t *__restrict attr) {
	memset(attr, 0, sizeof(*attr));
	return 0;
}

@@>> posix_spawnattr_destroy(3)
@@Destroy a given set of spawn attributes
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
$errno_t posix_spawnattr_destroy([[nonnull]] posix_spawnattr_t *__restrict attr) {
@@pp_ifndef NDEBUG@@
	memset(attr, 0xcc, sizeof(*attr));
@@pp_endif@@
	return 0;
}


@@>> posix_spawnattr_setflags(3)
@@Get the set of flags previously specified by `posix_spawnattr_setflags()'
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getflags([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                  [[nonnull]] short int *__restrict pflags) {
	*pflags = (short int)(unsigned short int)attr->@__flags@;
	return 0;
}

@@>> posix_spawnattr_setflags(3)
@@Specify the set of additional operations to-be performed by the
@@child process prior to being started. The given `flags' is a set of:
@@  - POSIX_SPAWN_RESETIDS:      Perform 2 calls `seteuid(getuid())' and `setegid(getgid())'
@@  - POSIX_SPAWN_SETSIGDEF:     s.a. posix_spawnattr_setsigdefault(3)
@@  - POSIX_SPAWN_SETSIGMASK:    s.a. posix_spawnattr_setsigmask(3)
@@  - POSIX_SPAWN_SETPGROUP:     s.a. posix_spawnattr_setpgroup(3)
@@  - POSIX_SPAWN_SETSCHEDULER:  s.a. posix_spawnattr_setschedpolicy(3)
@@  - POSIX_SPAWN_SETSCHEDPARAM: s.a. posix_spawnattr_setschedparam(3)
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setflags([[nonnull]] posix_spawnattr_t *__restrict attr,
                                  short int flags) {
	attr->@__flags@ = (uint16_t)(unsigned short int)flags;
	return 0;
}


@@>> posix_spawnattr_getsigdefault(3)
@@Get the set of signal handler that are reset of `SIG_DFL' by
@@the child process when `POSIX_SPAWN_SETSIGDEF' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sigset.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getsigdefault([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                       [[nonnull]] sigset_t *__restrict sigdefault) {
	memcpy(sigdefault, &attr->@__sd@, sizeof(sigset_t));
	return 0;
}

@@>> posix_spawnattr_setsigdefault(3)
@@Set the set of signal handler that are reset of `SIG_DFL' by
@@the child process when `POSIX_SPAWN_SETSIGDEF' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sigset.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setsigdefault([[nonnull]] posix_spawnattr_t *__restrict attr,
                                       [[nonnull]] sigset_t const *__restrict sigdefault) {
	memcpy(&attr->@__sd@, sigdefault, sizeof(sigset_t));
	return 0;
}

@@>> posix_spawnattr_getsigmask(3)
@@Get the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
@@that the child process will perform when `POSIX_SPAWN_SETSIGMASK' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sigset.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getsigmask([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                    [[nonnull]] sigset_t *__restrict sigmask) {
	memcpy(sigmask, &attr->@__ss@, sizeof(sigset_t));
	return 0;
}

@@>> posix_spawnattr_getsigmask(3)
@@Set the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
@@that the child process will perform when `POSIX_SPAWN_SETSIGMASK' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sigset.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setsigmask([[nonnull]] posix_spawnattr_t *__restrict attr,
                                    [[nonnull]] sigset_t const *__restrict sigmask) {
	memcpy(&attr->@__ss@, sigmask, sizeof(sigset_t));
	return 0;
}

@@>> posix_spawnattr_getpgroup(3)
@@Get the `pgid' argument of a call `setpgid(getpid(), pgid)' that
@@the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getpgroup([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                   [[nonnull]] pid_t *__restrict pgroup) {
	*pgroup = attr->@__pgrp@;
	return 0;
}

@@>> posix_spawnattr_getschedparam(3)
@@Set the `pgid' argument of a call `setpgid(getpid(), pgid)' that
@@the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
@@HINT: A call `setpgid(getpid(), 0)' is the same as `setpgid(getpid(), getpid())'!
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setpgroup([[nonnull]] posix_spawnattr_t *__restrict attr, pid_t pgroup) {
	attr->@__pgrp@ = pgroup;
	return 0;
}

@@>> posix_spawnattr_getschedparam(3)
@@Get the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
@@that the child process will perform when `POSIX_SPAWN_SETSCHEDULER' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getschedpolicy([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                        [[nonnull]] int *__restrict schedpolicy) {
	*schedpolicy = attr->@__policy@;
	return 0;
}

@@>> posix_spawnattr_getschedparam(3)
@@Set the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
@@that the child process will perform when `POSIX_SPAWN_SETSCHEDULER' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setschedpolicy([[nonnull]] posix_spawnattr_t *__restrict attr,
                                        int schedpolicy) {
	attr->@__policy@ = schedpolicy;
	return 0;
}

@@>> posix_spawnattr_getschedparam(3)
@@Get the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
@@that the child process will perform when `POSIX_SPAWN_SETSCHEDPARAM' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sched_param.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getschedparam([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                       [[nonnull]] struct sched_param *__restrict schedparam) {
	memcpy(schedparam, &attr->__sp, sizeof(struct sched_param));
	return 0;
}

@@>> posix_spawnattr_setschedparam(3)
@@Set the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
@@that the child process will perform when `POSIX_SPAWN_SETSCHEDPARAM' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sched_param.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setschedparam([[nonnull]] posix_spawnattr_t *__restrict attr,
                                       [[nonnull]] struct sched_param const *__restrict schedparam) {
	memcpy(&attr->__sp, schedparam, sizeof(struct sched_param));
	return 0;
}





@@>> posix_spawn_file_actions_init(3)
@@Initialize the given spawn-file-actions object `file_actions'
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
$errno_t posix_spawn_file_actions_init([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions) {
	memset(file_actions, 0, sizeof(*file_actions));
	return 0;
}

@@>> posix_spawn_file_actions_destroy(3)
@@Finalize the given spawn-file-actions object `file_actions'
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawn_file_actions_destroy([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions) {
@@pp_if $has_function(free)@@
	unsigned int i;
	for (i = 0; i < (unsigned int)file_actions->@__used@; ++i) {
		struct __spawn_action *act;
		act = &file_actions->@__actions@[i];
		switch (act->@__sa_tag@) {

		case __POSIX_SPAWN_ACTION_OPEN:
			free(act->@__sa_action@.@__sa_open_action@.@__sa_path@);
			break;

		default:
			break;
		}
	}
	free(file_actions->@__actions@);
@@pp_endif@@
@@pp_ifndef NDEBUG@@
	memset(file_actions, 0xcc, sizeof(*file_actions));
@@pp_endif@@
	return 0;
}


@@Helper functions for allocating an a new file-spawn action entry
[[static, wunused]]
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && $has_function(realloc))]]
struct __spawn_action *posix_spawn_file_actions_alloc([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions) {
	struct __spawn_action *result;
	result = file_actions->@__actions@;
	if ((unsigned int)file_actions->@__used@ >= (unsigned int)file_actions->@__allocated@) {
		unsigned int newalloc;
		newalloc = (unsigned int)file_actions->@__used@ + 8;
		result   = (struct __spawn_action *)realloc(result, newalloc * sizeof(struct __spawn_action));
		if unlikely(!result) {
			newalloc = (unsigned int)file_actions->@__used@ + 1;
			result = file_actions->@__actions@;
			result = (struct __spawn_action *)realloc(result, newalloc * sizeof(struct __spawn_action));
			if unlikely(!result)
				return NULL;
		}
		file_actions->@__actions@   = result;
		file_actions->@__allocated@ = newalloc;
	}
	result += file_actions->@__used@++;
	return result;
}


@@>> posix_spawn_file_actions_addopen(3)
@@Enqueue a call `dup2(open(path, oflags, mode), fd)' to be performed by the child process
@@Note though that the intermediate file returned by `open()' will not remain open!
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<libc/errno.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && $has_function(strdup) && $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_addopen([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions,
                                          $fd_t fd, [[nonnull]] char const *__restrict path,
                                          $oflag_t oflags, mode_t mode) {
	struct __spawn_action *action;
	if unlikely((path = strdup(path)) == NULL)
		goto err;
	action = posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err_path;
	/* Fill in the new mode. */
	action->@__sa_tag@ = __POSIX_SPAWN_ACTION_OPEN;
	action->@__sa_action@.@__sa_open_action@.@__sa_fd@    = fd;
	action->@__sa_action@.@__sa_open_action@.@__sa_path@  = (char *)path;
	action->@__sa_action@.@__sa_open_action@.@__sa_oflag@ = oflags;
	action->@__sa_action@.@__sa_open_action@.@__sa_mode@  = mode;
	return 0;
err_path:
@@pp_if $has_function(free)@@
	free((char *)path);
@@pp_endif@@
err:
@@pp_ifdef ENOMEM@@
	return ENOMEM;
@@pp_else@@
	return 1;
@@pp_endif@@
}

@@>> posix_spawn_file_actions_addclose(3)
@@Enqueue a call `close(fd)' to be performed by the child process
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_addclose([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions,
                                           $fd_t fd) {
	struct __spawn_action *action;
	action = posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->@__sa_tag@ = __POSIX_SPAWN_ACTION_CLOSE;
	action->@__sa_action@.@__sa_close_action@.@__sa_fd@ = fd;
	return 0;
err:
@@pp_ifdef ENOMEM@@
	return ENOMEM;
@@pp_else@@
	return 1;
@@pp_endif@@
}

@@>> posix_spawn_file_actions_adddup2(3)
@@Enqueue a call `dup2(oldfd, newfd)' to be performed by the child process
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_adddup2([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions,
                                          $fd_t oldfd, $fd_t newfd) {
	struct __spawn_action *action;
	action = posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->@__sa_tag@ = __POSIX_SPAWN_ACTION_DUP2;
	action->@__sa_action@.@__sa_dup2_action@.@__sa_oldfd@ = oldfd;
	action->@__sa_action@.@__sa_dup2_action@.@__sa_newfd@ = newfd;
	return 0;
err:
@@pp_ifdef ENOMEM@@
	return ENOMEM;
@@pp_else@@
	return 1;
@@pp_endif@@
}

%#ifdef __USE_KOS
@@>> posix_spawn_file_actions_addtcsetpgrp_np(3)
@@Enqueue a call `tcsetpgrp(fd, getpid())' to be performed by the child process
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>", "<bits/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && defined(__POSIX_SPAWN_ACTION_TCSETPGRP) &&
           $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_addtcsetpgrp_np([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions,
                                                  $fd_t fd) {
	struct __spawn_action *action;
	action = posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->@__sa_tag@ = __POSIX_SPAWN_ACTION_TCSETPGRP;
	action->@__sa_action@.@__sa_tcsetpgrp_action@.@__sa_fd@ = fd;
	return 0;
err:
@@pp_ifdef ENOMEM@@
	return ENOMEM;
@@pp_else@@
	return 1;
@@pp_endif@@
}
%#endif /* __USE_KOS */

%#ifdef __USE_SOLARIS
@@>> posix_spawn_file_actions_addclosefrom_np(3)
@@Enqueue a call `closefrom(lowfd)' to be performed by the child process
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>", "<bits/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && defined(__POSIX_SPAWN_ACTION_CLOSEFROM) &&
           $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_addclosefrom_np([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions,
                                                  $fd_t lowfd) {
	struct __spawn_action *action;
	action = posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->@__sa_tag@ = __POSIX_SPAWN_ACTION_CLOSEFROM;
	action->@__sa_action@.@__sa_closefrom_action@.@__sa_fd@ = lowfd;
	return 0;
err:
@@pp_ifdef ENOMEM@@
	return ENOMEM;
@@pp_else@@
	return 1;
@@pp_endif@@
}
%#endif /* __USE_SOLARIS */


/* XXX:
 *   - POSIX_SPAWN_NOSIGCHLD_NP
 *   - POSIX_SPAWN_WAITPID_NP
 *   - POSIX_SPAWN_SETSIGIGN_NP 
 *   - posix_spawnattr_getsigignore_np
 *   - posix_spawnattr_setsigignore_np
 */


%{

#endif /* __CC__ */

__SYSDECL_END

}