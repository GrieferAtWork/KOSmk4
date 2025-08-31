/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/newlib/libc/include/spawn.h) */
/* (#) Portability: DragonFly BSD (/include/spawn.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/spawn.h) */
/* (#) Portability: FreeBSD       (/include/spawn.h) */
/* (#) Portability: GNU C Library (/posix/spawn.h) */
/* (#) Portability: GNU Hurd      (/usr/include/spawn.h) */
/* (#) Portability: NetBSD        (/include/spawn.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/spawn.h) */
/* (#) Portability: OpenBSD       (/include/spawn.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/spawn.h) */
/* (#) Portability: libc6         (/include/spawn.h) */
/* (#) Portability: musl libc     (/include/spawn.h) */
/* (#) Portability: uClibc        (/include/spawn.h) */
}

%[define_decl_include_implication("<bits/crt/posix_spawn.h>" => [
	"<bits/types.h>",
	"<bits/os/sched.h>",
	"<bits/os/sigset.h>",
])]
%[define_decl_include("<bits/crt/posix_spawn.h>": [
	"struct __posix_spawnattr",
	"struct __spawn_action",
	"struct __posix_spawn_file_actions",
])]

%[define_decl_include_implication("<bits/os/sigset.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/sigset.h>": ["struct __sigset_struct"])]
%[define_replacement(sigset_t = "struct __sigset_struct")]

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]
%[define_replacement(posix_spawnattr_t = "struct __posix_spawnattr")]
%[define_replacement(posix_spawn_file_actions_t = "struct __posix_spawn_file_actions")]
%[default:section(".text.crt{|.dos}.fs.exec.posix_spawn")]

%[assume_defined_in_kos_userspace(__POSIX_SPAWN_USE_KOS)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_ACTION_CLOSE)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_ACTION_DUP2)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_ACTION_OPEN)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_ACTION_CHDIR)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_ACTION_FCHDIR)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_ACTION_TCSETPGRP)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_ACTION_CLOSEFROM)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_RESETIDS)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_SETPGROUP)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_SETSIGDEF)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_SETSIGMASK)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_SETSCHEDPARAM)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_SETSCHEDULER)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_USEVFORK)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_SETSID)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_SETCGROUP)]
%[assume_defined_in_kos_userspace(__POSIX_SPAWN_NOEXECERR)]


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/posix_spawn.h>
)]%[insert:prefix(
#include <bits/crt/posix_spawn.h>
)]%[insert:prefix(
#include <bits/os/sched.h>
)]%[insert:prefix(
#include <bits/os/sigset.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <sys/types.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <sched.h>
#endif /* __USE_GLIBC_BLOAT */

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
#define POSIX_SPAWN_USEVFORK __POSIX_SPAWN_USEVFORK /* Ignored on KOS, which always uses vfork(2) */
#endif /* __POSIX_SPAWN_USEVFORK */
#ifdef __POSIX_SPAWN_SETSID
#define POSIX_SPAWN_SETSID __POSIX_SPAWN_SETSID /* Call `setsid(2)' within the context of the new process */
#endif /* __POSIX_SPAWN_SETSID */
#ifdef __POSIX_SPAWN_SETCGROUP
#define POSIX_SPAWN_SETCGROUP __POSIX_SPAWN_SETCGROUP /* Set `CLONE_INTO_CGROUP' when spawning a new process (Not implemented on KOS) */
#endif /* __POSIX_SPAWN_SETCGROUP */
#endif /* __USE_GNU */

#ifdef __POSIX_SPAWN_NOEXECERR
#define POSIX_SPAWN_NOEXECERR_NP __POSIX_SPAWN_NOEXECERR /* Don't propagate exec() error, and leave the
                                                          * child as  unreaped with  exit status  `127' */
#endif /* __POSIX_SPAWN_NOEXECERR */


#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !pid_t_defined */

#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */

typedef struct __posix_spawnattr posix_spawnattr_t;
typedef struct __posix_spawn_file_actions posix_spawn_file_actions_t;

}

%[define(DEFINE_TARGV =
@@pp_ifndef __TARGV@@
@@pp_ifdef __USE_DOS_ALTERATIONS@@
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
@@pp_else@@
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
@@pp_endif@@
@@pp_endif@@
)]


%[define(POSIX_SPAWN_TYPE_EXECVE = 0)]  /* execve((char const *)exec_arg, ___argv, ___envp) */
%[define(POSIX_SPAWN_TYPE_EXECVPE = 1)] /* execvpe((char const *)exec_arg, ___argv, ___envp) */
%[define(POSIX_SPAWN_TYPE_FEXECVE = 2)] /* fexecve((fd_t)(uintptr_t)exec_arg, ___argv, ___envp) */
%[define(POSIX_SPAWN_TYPE_CUSTOM = 3)]  /* (*(void (LIBCCALL *)(char **, char **))exec_arg)(___argv, ___envp) */

[[static]]
[[argument_names(exec_type, exec_arg, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[impl_include("<bits/os/sigaction.h>", "<libc/errno.h>", "<hybrid/typecore.h>")]]
[[impl_include("<asm/os/oflags.h>", "<asm/os/signal.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) &&
           ($has_function(fexecve) || $has_function(execve) || $has_function(execvpe)))]]
$errno_t posix_spawn_child(unsigned int exec_type, void *exec_arg,
                           [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                           [[in_opt]] posix_spawnattr_t const *attrp,
                           [[in]] __TARGV, [[in]] __TENVP) {

	/* Perform additional actions within the child. */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("__used")
#pragma @push_macro@("__actions")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @__used@
#undef @__actions@
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
					goto err_errno;
				break;
@@pp_endif@@


@@pp_if !$has_function(dup2)@@
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
@@pp_else@@
			case __POSIX_SPAWN_ACTION_DUP2:
				/* Duplicate a file handle */
				if unlikely(dup2(act->@__sa_action@.@__sa_dup2_action@.@__sa_oldfd@,
				                 act->@__sa_action@.@__sa_dup2_action@.@__sa_newfd@))
					goto err_errno;
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
					goto err_errno;
				if likely(tempfd != act->@__sa_action@.@__sa_open_action@.@__sa_fd@) {
					if unlikely(dup2(tempfd, act->@__sa_action@.@__sa_open_action@.@__sa_fd@))
						goto err_errno;
					(void)close(tempfd);
				}
			}	break;
@@pp_endif@@


@@pp_ifdef __POSIX_SPAWN_ACTION_CHDIR@@
@@pp_if         !$has_function(chdir)@@
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
@@pp_else@@
			case __POSIX_SPAWN_ACTION_CHDIR: {
				/* Change direction using `chdir(2)' */
				if unlikely(chdir(act->@__sa_action@.@__sa_chdir_action@.@__sa_path@))
					goto err_errno;
			}	break;
@@pp_endif@@
@@pp_endif@@


@@pp_ifdef __POSIX_SPAWN_ACTION_FCHDIR@@
@@pp_if         !$has_function(fchdir)@@
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
@@pp_else@@
			case __POSIX_SPAWN_ACTION_FCHDIR: {
				/* Change direction using `fchdir(2)' */
				if unlikely(fchdir(act->@__sa_action@.@__sa_fchdir_action@.@__sa_fd@))
					goto err_errno;
			}	break;
@@pp_endif@@
@@pp_endif@@


@@pp_ifdef __POSIX_SPAWN_ACTION_TCSETPGRP@@
@@pp_if         !$has_function(tcsetpgrp)@@
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
@@pp_else@@
			case __POSIX_SPAWN_ACTION_TCSETPGRP:
				/* NOTE: Passing `0' as second argument to `tcsetpgrp()' is the same as `getpid()' */
				if unlikely(tcsetpgrp(act->@__sa_action@.@__sa_tcsetpgrp_action@.@__sa_fd@, 0))
					goto err_errno;
				break;
@@pp_endif@@
@@pp_endif@@


@@pp_ifdef __POSIX_SPAWN_ACTION_CLOSEFROM@@
@@pp_if         !$has_function(closefrom)@@
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
				return ENOSYS;
@@pp_elif defined(EPERM)@@
				return EPERM;
@@pp_else@@
				return 1;
@@pp_endif@@
@@pp_else@@
			default:
				__builtin_unreachable();
@@pp_endif@@
			}
		}
	}
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("__actions")
#pragma @pop_macro@("__used")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
	if (attrp) {
		if (attrp->@__flags@ & __POSIX_SPAWN_RESETIDS) {
@@pp_if ($has_function(seteuid) && $has_function(getuid)) || ($has_function(setegid) && $has_function(getgid))@@
@@pp_if $has_function(seteuid) && $has_function(getuid)@@
			if (seteuid(getuid()))
				goto err_errno;
@@pp_endif@@
@@pp_if $has_function(setegid) && $has_function(getgid)@@
			if (setegid(getgid()))
				goto err_errno;
@@pp_endif@@
@@pp_else@@
@@pp_ifdef ENOSYS@@
			return ENOSYS;
@@pp_elif defined(EPERM)@@
			return EPERM;
@@pp_else@@
			return 1;
@@pp_endif@@
@@pp_endif@@
		}
		if (attrp->@__flags@ & __POSIX_SPAWN_SETPGROUP) {
@@pp_if $has_function(setpgid)@@
			/* HINT: Passing `0' as first argument is the same as passing `getpid()'! */
			if unlikely(setpgid(0, attrp->@__pgrp@))
				goto err_errno;
@@pp_else@@
@@pp_ifdef ENOSYS@@
			return ENOSYS;
@@pp_elif defined(EPERM)@@
			return EPERM;
@@pp_else@@
			return 1;
@@pp_endif@@
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
					goto err_errno;
			}
@@pp_else@@
@@pp_ifdef ENOSYS@@
			return ENOSYS;
@@pp_elif defined(EPERM)@@
			return EPERM;
@@pp_else@@
			return 1;
@@pp_endif@@
@@pp_endif@@
		}
		if (attrp->@__flags@ & __POSIX_SPAWN_SETSIGMASK) {
@@pp_if $has_function(sigprocmask) && defined(__SIG_SETMASK)@@
			if unlikely(sigprocmask(__SIG_SETMASK, &attrp->@__ss@, NULL))
				goto err_errno;
@@pp_else@@
@@pp_ifdef ENOSYS@@
			return ENOSYS;
@@pp_elif defined(EPERM)@@
			return EPERM;
@@pp_else@@
			return 1;
@@pp_endif@@
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
				goto err_errno;
@@pp_else@@
@@pp_ifdef ENOSYS@@
			return ENOSYS;
@@pp_elif defined(EPERM)@@
			return EPERM;
@@pp_else@@
			return 1;
@@pp_endif@@
@@pp_endif@@
		}
@@pp_if defined(__POSIX_SPAWN_SETSID) && $has_function(setsid)@@
		if (attrp->@__flags@ & __POSIX_SPAWN_SETSID) {
			if unlikely(setsid() < 0)
				goto err_errno;
		}
@@pp_endif@@
	}

	switch (exec_type) {
@@pp_if $has_function(execve)@@
	case POSIX_SPAWN_TYPE_EXECVE:
		execve((char const *)exec_arg, ___argv, ___envp);
		break;
@@pp_endif@@
@@pp_if $has_function(execvpe)@@
	case POSIX_SPAWN_TYPE_EXECVPE:
		execvpe((char const *)exec_arg, ___argv, ___envp);
		break;
@@pp_endif@@
@@pp_if $has_function(fexecve)@@
	case POSIX_SPAWN_TYPE_FEXECVE:
		fexecve((fd_t)(uintptr_t)exec_arg, ___argv, ___envp);
		break;
@@pp_endif@@
	case POSIX_SPAWN_TYPE_CUSTOM:
		(*(void (__LIBCCALL *)(char **, char **))exec_arg)((char **)___argv, (char **)___envp);
		break;
	default: __builtin_unreachable();
	}

@@pp_ifdef __POSIX_SPAWN_NOEXECERR@@
	if (attrp && attrp->@__flags@ & __POSIX_SPAWN_NOEXECERR)
		return 0; /* Suppress the exec error. */
@@pp_endif@@

err_errno:
@@pp_ifdef ENOENT@@
	return __libc_geterrno_or(ENOENT);
@@pp_else@@
	return __libc_geterrno_or(1);
@@pp_endif@@
}

[[static]]
[[argument_names(pid, exec_type, exec_arg, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[impl_include("<bits/os/sigaction.h>", "<libc/errno.h>", "<hybrid/typecore.h>")]]
[[impl_include("<asm/os/vfork.h>", "<asm/os/oflags.h>", "<asm/os/signal.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>", "<asm/os/vfork.h>", "<asm/os/features.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) &&
           ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)) ||
            ($has_function(fork) && ($has_function(pipe2) && defined(O_CLOEXEC)) &&
             $has_function(read) && $has_function(write) && $has_function(close))) &&
           $has_function(posix_spawn_child) && $has_function(waitpid))]]
$errno_t posix_spawn_impl([[out]] pid_t *__restrict pid, unsigned int exec_type, void *exec_arg,
                          [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                          [[in_opt]] posix_spawnattr_t const *attrp,
                          [[in]] __TARGV, [[in]] __TENVP) {
	int status;
@@pp_if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || !$has_function(vfork)@@
	fd_t pipes[2];
	ssize_t temp;
@@pp_endif@@
	errno_t result, error, old_errno;
	pid_t child;
	old_errno = __libc_geterrno_or(0);
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
	(void)libc_seterrno(0);
	child = vfork();
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
@@pp_else@@
	/* Create a pair of pipes for temporary communication. */
	if (pipe2(pipes, O_CLOEXEC)) {
err_without_child:
		result = __libc_geterrno_or(0);
		(void)libc_seterrno(old_errno);
		return result;
	}
	child = fork();
	if (child == 0)
		goto do_exec;
	if (child < 0)
		goto err_without_child; /* The fork() itself failed. */
	/* Read from the communication pipe
	 * (NOTE: If exec() succeeds, the pipe will be
	 *        closed and  read() returns  ZERO(0)) */
	close(pipes[1]); /* Close the writer. */
	temp = read(pipes[0], &result, sizeof(result));
	close(pipes[0]); /* Close the reader. */
	if (temp < 0)
		goto err_join_zombie_child;
	/* This means that `fexecve()' below closed the pipe during a successful exec(). */
	if (temp != sizeof(result)) {
		*pid = child;
		(void)libc_seterrno(old_errno);
		return 0;
	}
@@pp_endif@@
err_join_zombie_child:
	/* Unless the child was already spawned as detached,
	 * we still have to re-join  it, or else it will  be
	 * left dangling as a zombie process! */
	if (waitpid(child, &status, 0) < 0) {
@@pp_ifdef EINTR@@
		if (__libc_geterrno() == EINTR)
			goto err_join_zombie_child;
@@pp_endif@@
	}
	(void)libc_seterrno(old_errno);
	return result;
do_exec:
	/* Perform additional actions within the child.
	 *
	 * NOTE: When the exec succeeds, the pipe is auto-
	 *       closed because it's marked as  O_CLOEXEC! */
	error = posix_spawn_child(exec_type, exec_arg, file_actions, attrp, ___argv, ___envp);
	if (error != 0) {
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
		/* If the exec fails, it will have modified `errno' to indicate this fact.
		 * And since we're sharing VMs with  our parent process, the error  reason
		 * will have already  been written  back to  our parent's  VM, so  there's
		 * actually nothing left for us to do, but to simply exit! */
		__libc_seterrno(error);
@@pp_else@@
		/* Write the exec-error back to our parent. */
		write(pipes[1], &error, sizeof(error));
		/* No need to close the pipe, it's auto-closed by the kernel! */
@@pp_endif@@
	}
	_Exit(127);
}



%#ifdef __USE_KOS
[[ignore, nocrt, alias("posix_spawn")]]
[[argument_names(pid, path, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
$errno_t crt_posix_spawn([[out]] pid_t *__restrict pid,
                         [[in]] char const *__restrict path,
                         [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                         [[in_opt]] posix_spawnattr_t const *attrp,
                         [[in]] __TARGV, [[in]] __TENVP);

@@>> posix_fspawn_np(3)
@@Implementation for the fastest possible  method of (safely) doing  fork(2)+fexecve(2)
@@in  order  to  spawn  a  new  process  from  the  given  `execfd'  file   descriptor.
@@For this purpose, any error that may happen during either the fork(3), the fexecve(2)
@@or  any of the numerous additional system calls that may be performed in-between will
@@be returned by this function to the  parent process, while the function itself  never
@@actually returns in the child process.
@@For this  purpose,  this  function tries  to  make  use of  `vfork(2)'  in  combination
@@with  `__ARCH_HAVE_SHARED_VM_VFORK',  and if  that  isn't available,  a  temporary pipe
@@is  used to communicate process initialization errors, as well as to await a successful
@@exec call by using the  fact that a successful exec  will close all `O_CLOEXEC'  files,
@@with the pipe having been given that flag, and that a pipe without both ends still open
@@will always  have its  read immediately  return  (which is  used to  indicate  success)
@@@param: pid:          Store the PID of the newly spawned child process here
@@@param: execfd:       The file descriptor pointing to the file that should be executed
@@@param: file_actions: [0..1] A set of additional actions to perform in regards to file-
@@                             handle operations. Can be used to (e.g.) re-direct  stdout
@@                             for the new process
@@@param: attrp:        [0..1] Additional process attributes to set for the child process
@@@param: argv:         Same as the `argv' accepted by `fexecve(2)'
@@@param: envp:         Same as the `envp' accepted by `fexecve(2)'
@@@return: 0 :          Success. (The child process's PID has been stored in `*pid')
@@@return: * :          Error (errno-code describing the reason of failure)
[[argument_names(pid, execfd, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[impl_include("<bits/os/sigaction.h>", "<libc/errno.h>", "<hybrid/typecore.h>")]]
[[impl_include("<asm/os/vfork.h>", "<asm/os/oflags.h>", "<asm/os/signal.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>", "<asm/os/vfork.h>", "<asm/os/features.h>")]]
[[requires($has_function(posix_spawn_impl, fexecve) ||
           (defined(__OS_HAVE_PROCFS_SELF_FD) && $has_function(crt_posix_spawn)))]]
$errno_t posix_fspawn_np([[out]] pid_t *__restrict pid, [[fdread]] $fd_t execfd,
                         [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                         [[in_opt]] posix_spawnattr_t const *attrp,
                         [[in]] __TARGV, [[in]] __TENVP) {
@@pp_if $has_function(posix_spawn_impl, fexecve)@@
	return posix_spawn_impl(pid, POSIX_SPAWN_TYPE_FEXECVE, (void *)(uintptr_t)execfd, file_actions, attrp, ___argv, ___envp);
@@pp_else@@
@@pp_if __SIZEOF_INT__ == 4@@
	char buf[COMPILER_LNEOF("/proc/self/fd/-2147483648")];
@@pp_elif __SIZEOF_INT__ == 8@@
	char buf[COMPILER_LNEOF("/proc/self/fd/-9223372036854775808")];
@@pp_elif __SIZEOF_INT__ == 2@@
	char buf[COMPILER_LNEOF("/proc/self/fd/-32768")];
@@pp_else@@
	char buf[COMPILER_LNEOF("/proc/self/fd/-128")];
@@pp_endif@@
	sprintf(buf, "/proc/self/fd/%d", execfd);
	return crt_posix_spawn(pid, buf, file_actions, attrp, ___argv, ___envp);
@@pp_endif@@
}

%#endif /* __USE_KOS */



@@>> posix_spawn(3)
@@Implementation for the fastest possible method of (safely) doing fork(2)+execve(2)
@@in  order   to   spawn   a   new  process   from   the   given   `path'   program.
@@For this purpose, any error that may happen during either the fork(3), the execve(2)
@@or any of the numerous additional system calls that may be performed in-between will
@@be  returned by this function to the parent process, while the function itself never
@@actually returns in the child process.
@@For this  purpose,  this  function tries  to  make  use of  `vfork(2)'  in  combination
@@with  `__ARCH_HAVE_SHARED_VM_VFORK',  and if  that  isn't available,  a  temporary pipe
@@is  used to communicate process initialization errors, as well as to await a successful
@@exec call by using the  fact that a successful exec  will close all `O_CLOEXEC'  files,
@@with the pipe having been given that flag, and that a pipe without both ends still open
@@will always  have its  read immediately  return  (which is  used to  indicate  success)
@@@param: pid:          Store the PID of the newly spawned child process here
@@@param: path:         The pathname of the program that should be executed
@@@param: file_actions: [0..1] A set of additional actions to perform in regards to file-
@@                             handle operations. Can be used to (e.g.) re-direct  stdout
@@                             for the new process
@@@param: attrp:        [0..1] Additional process attributes to set for the child process
@@@param: argv:         Same as the `argv' accepted by `execve(2)'
@@@param: envp:         Same as the `envp' accepted by `execve(2)'
@@@return: 0 :          Success. (The child process's PID has been stored in `*pid')
@@@return: * :          Error (errno-code describing the reason of failure)
[[impl_include("<asm/os/oflags.h>")]]
[[requires($has_function(posix_spawn_impl, execve) || $has_function(open, posix_fspawn_np))]]
[[argument_names(pid, path, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
$errno_t posix_spawn([[out]] pid_t *__restrict pid,
                     [[in]] char const *__restrict path,
                     [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                     [[in_opt]] posix_spawnattr_t const *attrp,
                     [[in]] __TARGV, [[in]] __TENVP) {
@@pp_if $has_function(posix_spawn_impl, execve)@@
	return posix_spawn_impl(pid, POSIX_SPAWN_TYPE_EXECVE, (void *)path, file_actions, attrp, ___argv, ___envp);
@@pp_else@@
	fd_t fd;
	pid_t result = -1;
@@pp_if defined(O_RDONLY) && defined(O_CLOEXEC)@@
	fd = open(path, O_RDONLY | O_CLOEXEC);
@@pp_elif defined(O_RDONLY)@@
	fd = open(path, O_RDONLY);
@@pp_elif defined(O_CLOEXEC)@@
	fd = open(path, O_CLOEXEC);
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
@@pp_endif@@
}



@@>> posix_spawnp(3)
@@Same  as  `posix_spawn(3)',  but  search  `getenv("PATH")'  for  `file',  rather  than
@@directly making  use of  `file'  as the  absolute filename  of  the file  to  execute.
@@Note however  that  when  `file'  contains any  slashes,  `$PATH'  won't  be  searched
@@either, but instead, `file' is used as-is. (same as with `execve(2)' vs. `execvpe(3)')
[[requires_include("<hybrid/__alloca.h>")]]
[[requires($has_function(posix_spawn_impl, execvpe) ||
           ($has_function(getenv, posix_spawn) && defined(__hybrid_alloca)))]]
[[argument_names(pid, file, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<libc/errno.h>")]]
[[impl_prefix(
@@pp_if !$has_function(posix_spawn_impl, execvpe)@@
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
@@pp_endif@@
)]]
$errno_t posix_spawnp([[out]] pid_t *__restrict pid,
                      [[in]] char const *__restrict file,
                      [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                      [[in_opt]] posix_spawnattr_t const *attrp,
                      [[in]] __TARGV, [[in]] __TENVP) {
@@pp_if $has_function(posix_spawn_impl, execvpe)@@
	return posix_spawn_impl(pid, POSIX_SPAWN_TYPE_EXECVPE, (void *)file, file_actions, attrp, ___argv, ___envp);
@@pp_else@@
	errno_t result;
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
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
@@pp_endif@@
}


@@>> posix_spawnattr_init(3)
@@Initialize a given set of spawn attributes to all zero
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
$errno_t posix_spawnattr_init([[out]] posix_spawnattr_t *__restrict attr) {
	bzero(attr, sizeof(*attr));
	return 0;
}

%[define_replacement(NDEBUG      = NDEBUG)]
%[define_replacement(NDEBUG_FINI = NDEBUG_FINI)]

@@>> posix_spawnattr_destroy(3)
@@Destroy a given set of spawn attributes
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
$errno_t posix_spawnattr_destroy([[inout]] posix_spawnattr_t *__restrict attr) {
@@pp_if !defined(NDEBUG) && !defined(NDEBUG_FINI)@@
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
$errno_t posix_spawnattr_getflags([[in]] posix_spawnattr_t const *__restrict attr,
                                  [[out]] short int *__restrict pflags) {
	*pflags = (short int)(unsigned short int)attr->@__flags@;
	return 0;
}

@@>> posix_spawnattr_setflags(3)
@@Specify the  set of  additional operations  to-be performed  by  the
@@child process prior to being started. The given `flags' is a set of:
@@  - POSIX_SPAWN_RESETIDS:      Perform 2 calls `seteuid(getuid())' and `setegid(getgid())'
@@  - POSIX_SPAWN_SETSIGDEF:     s.a. posix_spawnattr_setsigdefault(3)
@@  - POSIX_SPAWN_SETSIGMASK:    s.a. posix_spawnattr_setsigmask(3)
@@  - POSIX_SPAWN_SETPGROUP:     s.a. posix_spawnattr_setpgroup(3)
@@  - POSIX_SPAWN_SETSCHEDULER:  s.a. posix_spawnattr_setschedpolicy(3)
@@  - POSIX_SPAWN_SETSCHEDPARAM: s.a. posix_spawnattr_setschedparam(3)
@@@return: 0 : Success
@@@return: EINVAL: The given `flags' has unknown/unsupported bits set
[[decl_include("<bits/crt/posix_spawn.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[impl_include("<asm/crt/posix_spawn.h>")]]
[[impl_include("<asm/os/errno.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setflags([[inout]] posix_spawnattr_t *__restrict attr,
                                  short int flags) {
	enum {
		ALL_FLAGS = 0
#ifdef __POSIX_SPAWN_RESETIDS
		| __POSIX_SPAWN_RESETIDS
#endif /* __POSIX_SPAWN_RESETIDS */
#ifdef __POSIX_SPAWN_SETPGROUP
		| __POSIX_SPAWN_SETPGROUP
#endif /* __POSIX_SPAWN_SETPGROUP */
#ifdef __POSIX_SPAWN_SETSIGDEF
		| __POSIX_SPAWN_SETSIGDEF
#endif /* __POSIX_SPAWN_SETSIGDEF */
#ifdef __POSIX_SPAWN_SETSIGMASK
		| __POSIX_SPAWN_SETSIGMASK
#endif /* __POSIX_SPAWN_SETSIGMASK */
#ifdef __POSIX_SPAWN_SETSCHEDPARAM
		| __POSIX_SPAWN_SETSCHEDPARAM
#endif /* __POSIX_SPAWN_SETSCHEDPARAM */
#ifdef __POSIX_SPAWN_SETSCHEDULER
		| __POSIX_SPAWN_SETSCHEDULER
#endif /* __POSIX_SPAWN_SETSCHEDULER */
#ifdef __POSIX_SPAWN_USEVFORK
		| __POSIX_SPAWN_USEVFORK
#endif /* __POSIX_SPAWN_USEVFORK */
#ifdef __POSIX_SPAWN_SETSID
		| __POSIX_SPAWN_SETSID
#endif /* __POSIX_SPAWN_SETSID */
#ifdef __POSIX_SPAWN_SETCGROUP
		| __POSIX_SPAWN_SETCGROUP
#endif /* __POSIX_SPAWN_SETCGROUP */
#ifdef __POSIX_SPAWN_NOEXECERR
		| __POSIX_SPAWN_NOEXECERR
#endif /* __POSIX_SPAWN_NOEXECERR */
	};
	if unlikely((unsigned short int)flags & ~(unsigned short int)ALL_FLAGS) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	attr->@__flags@ = (uint16_t)(unsigned short int)flags;
	return 0;
}


@@>> posix_spawnattr_getsigdefault(3)
@@Get the set of signal handler that are reset of `SIG_DFL' by
@@the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/os/sigset.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getsigdefault([[in]] posix_spawnattr_t const *__restrict attr,
                                       [[out]] sigset_t *__restrict sigdefault) {
	memcpy(sigdefault, &attr->@__sd@, sizeof(sigset_t));
	return 0;
}

@@>> posix_spawnattr_setsigdefault(3)
@@Set the set of signal handler that are reset of `SIG_DFL' by
@@the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/os/sigset.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setsigdefault([[inout]] posix_spawnattr_t *__restrict attr,
                                       [[in]] sigset_t const *__restrict sigdefault) {
	memcpy(&attr->@__sd@, sigdefault, sizeof(sigset_t));
	return 0;
}

@@>> posix_spawnattr_getsigmask(3)
@@Get the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
@@that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/os/sigset.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getsigmask([[in]] posix_spawnattr_t const *__restrict attr,
                                    [[out]] sigset_t *__restrict sigmask) {
	memcpy(sigmask, &attr->@__ss@, sizeof(sigset_t));
	return 0;
}

@@>> posix_spawnattr_getsigmask(3)
@@Set the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
@@that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/os/sigset.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setsigmask([[inout]] posix_spawnattr_t *__restrict attr,
                                    [[in]] sigset_t const *__restrict sigmask) {
	memcpy(&attr->@__ss@, sigmask, sizeof(sigset_t));
	return 0;
}

@@>> posix_spawnattr_getpgroup(3)
@@Get the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
@@the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getpgroup([[in]] posix_spawnattr_t const *__restrict attr,
                                   [[out]] pid_t *__restrict pgroup) {
	*pgroup = attr->@__pgrp@;
	return 0;
}

@@>> posix_spawnattr_getschedparam(3)
@@Set the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
@@the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
@@HINT: A call `setpgid(getpid(), 0)' is the same as `setpgid(getpid(), getpid())'!
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setpgroup([[inout]] posix_spawnattr_t *__restrict attr, pid_t pgroup) {
	attr->@__pgrp@ = pgroup;
	return 0;
}

@@>> posix_spawnattr_getschedparam(3)
@@Get the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
@@that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getschedpolicy([[in]] posix_spawnattr_t const *__restrict attr,
                                        [[out]] int *__restrict schedpolicy) {
	*schedpolicy = attr->@__policy@;
	return 0;
}

@@>> posix_spawnattr_getschedparam(3)
@@Set the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
@@that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setschedpolicy([[inout]] posix_spawnattr_t *__restrict attr,
                                        int schedpolicy) {
	attr->@__policy@ = schedpolicy;
	return 0;
}

@@>> posix_spawnattr_getschedparam(3)
@@Get the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
@@that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/os/sched.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_getschedparam([[in]] posix_spawnattr_t const *__restrict attr,
                                       [[out]] struct sched_param *__restrict schedparam) {
	memcpy(schedparam, &attr->__sp, sizeof(struct sched_param));
	return 0;
}

@@>> posix_spawnattr_setschedparam(3)
@@Set the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
@@that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/os/sched.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawnattr_setschedparam([[inout]] posix_spawnattr_t *__restrict attr,
                                       [[in]] struct sched_param const *__restrict schedparam) {
	memcpy(&attr->__sp, schedparam, sizeof(struct sched_param));
	return 0;
}





@@>> posix_spawn_file_actions_init(3)
@@Initialize the given spawn-file-actions object `file_actions'
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
$errno_t posix_spawn_file_actions_init([[out]] posix_spawn_file_actions_t *__restrict file_actions) {
	bzero(file_actions, sizeof(*file_actions));
	return 0;
}

@@>> posix_spawn_file_actions_destroy(3)
@@Finalize the given spawn-file-actions object `file_actions'
@@@return: 0 : Success
[[decl_include("<bits/crt/posix_spawn.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS))]]
$errno_t posix_spawn_file_actions_destroy([[inout]] posix_spawn_file_actions_t *__restrict file_actions) {
@@pp_if $has_function(free)@@
	unsigned int i;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("__used")
#pragma @push_macro@("__actions")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @__used@
#undef @__actions@
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
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("__actions")
#pragma @pop_macro@("__used")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
@@pp_endif@@
@@pp_if !defined(NDEBUG) && !defined(NDEBUG_FINI)@@
	memset(file_actions, 0xcc, sizeof(*file_actions));
@@pp_endif@@
	return 0;
}


@@Helper functions for allocating an a new file-spawn action entry
[[static, wunused]]
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && $has_function(realloc))]]
struct __spawn_action *posix_spawn_file_actions_alloc([[inout]] posix_spawn_file_actions_t *__restrict file_actions) {
	struct __spawn_action *result;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("__used")
#pragma @push_macro@("__actions")
#pragma @push_macro@("__allocated")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @__used@
#undef @__actions@
#undef @__allocated@
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
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("__used")
#pragma @pop_macro@("__actions")
#pragma @pop_macro@("__allocated")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
	return result;
}


@@>> posix_spawn_file_actions_addopen(3)
@@Enqueue a call `dup2(open(path, oflags, mode), fd)' to be performed by the child process
@@Note though  that the  intermediate file  returned by  `open(2)' will  not remain  open!
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<libc/errno.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && $has_function(strdup) && $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_addopen([[inout]] posix_spawn_file_actions_t *__restrict file_actions,
                                          [[no_fdarg]] $fd_t fd, [[in]] char const *__restrict path,
                                          $oflag_t oflags, mode_t mode) {
	struct __spawn_action *action;
	/* Posix says:
	 * """
	 * The string described by path shall be copied  by
	 * the posix_spawn_file_actions_addopen() function.
	 * """
	 * iow: We need to strdup(path) here! */
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
$errno_t posix_spawn_file_actions_addclose([[inout]] posix_spawn_file_actions_t *__restrict file_actions,
                                           [[fdarg]] $fd_t fd) {
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
$errno_t posix_spawn_file_actions_adddup2([[inout]] posix_spawn_file_actions_t *__restrict file_actions,
                                          [[fdarg]] $fd_t oldfd, [[no_fdarg]] $fd_t newfd) {
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

%
%#if defined(__USE_MISC) || defined(__USE_KOS)
@@>> posix_spawn_file_actions_addtcsetpgrp_np(3)
@@Enqueue a call `tcsetpgrp(fd, getpid())' to be performed by the child process
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>", "<bits/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && defined(__POSIX_SPAWN_ACTION_TCSETPGRP) &&
           $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_addtcsetpgrp_np([[inout]] posix_spawn_file_actions_t *__restrict file_actions,
                                                  [[fdarg]] $fd_t fd) {
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
%#endif /* __USE_MISC || __USE_KOS */

%
%#if defined(__USE_MISC) || defined(__USE_SOLARIS)
@@>> posix_spawn_file_actions_addclosefrom_np(3)
@@Enqueue a call `closefrom(lowfd)' to be performed by the child process
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>", "<bits/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && defined(__POSIX_SPAWN_ACTION_CLOSEFROM) &&
           $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_addclosefrom_np([[inout]] posix_spawn_file_actions_t *__restrict file_actions,
                                                  [[no_fdarg]] $fd_t lowfd) {
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
%#endif /* __USE_MISC || __USE_SOLARIS */


%
%#if defined(__USE_MISC) || defined(__USE_GNU)
@@>> posix_spawn_file_actions_addchdir_np(3)
@@Enqueue a call `chdir(path)' to be performed by the child process
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_addchdir_np([[inout]] posix_spawn_file_actions_t *__restrict file_actions,
                                              [[in]] char const *__restrict path) {
	struct __spawn_action *action;
	if unlikely((path = strdup(path)) == NULL)
		goto err;
	action = posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err_path;
	/* Fill in the new mode. */
	action->@__sa_tag@ = __POSIX_SPAWN_ACTION_CHDIR;
	action->@__sa_action@.@__sa_chdir_action@.@__sa_path@ = (char *)path;
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

@@>> posix_spawn_file_actions_addfchdir_np(3)
@@Enqueue a call `fchdir(dfd)' to be performed by the child process
@@@return: 0     : Success
@@@return: ENOMEM: Insufficient memory to enqueue the action
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
[[requires_include("<asm/crt/posix_spawn.h>")]]
[[requires(defined(__POSIX_SPAWN_USE_KOS) && $has_function(posix_spawn_file_actions_alloc))]]
$errno_t posix_spawn_file_actions_addfchdir_np([[inout]] posix_spawn_file_actions_t *__restrict file_actions,
                                               [[fdarg]] $fd_t dfd) {
	struct __spawn_action *action;
	action = posix_spawn_file_actions_alloc(file_actions);
	if unlikely(!action)
		goto err;
	/* Fill in the new mode. */
	action->@__sa_tag@ = __POSIX_SPAWN_ACTION_FCHDIR;
	action->@__sa_action@.@__sa_fchdir_action@.@__sa_fd@ = dfd;
	return 0;
err:
@@pp_ifdef ENOMEM@@
	return ENOMEM;
@@pp_else@@
	return 1;
@@pp_endif@@
}
%#endif /* __USE_MISC || __USE_GNU */



%
%#ifdef __USE_MISC

[[static]] /* Not implemented in magic -- only implemented in "userimpl" */
[[argument_names(pidfd, exec_type, exec_arg, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
$errno_t pidfd_spawn_impl([[out]] $fd_t *__restrict pidfd, unsigned int exec_type, void *exec_arg,
                          [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                          [[in_opt]] posix_spawnattr_t const *attrp,
                          [[in]] __TARGV, [[in]] __TENVP);


@@>> pidfd_spawn(3)
@@Same as `posix_spawn(3)', except that the linux/kos-specific "PIDfd" mechanism is
@@used  to return a reference to the child process in the form of a file descriptor
@@stored in `*pidfd'.
@@@param: pidfd:        Store the PIDfd of the newly spawned child process here
@@@param: path:         The pathname of the program that should be executed
@@@param: file_actions: [0..1] A set of additional actions to perform in regards to file-
@@                             handle operations. Can be used to (e.g.) re-direct  stdout
@@                             for the new process
@@@param: attrp:        [0..1] Additional process attributes to set for the child process
@@@param: argv:         Same as the `argv' accepted by `execve(2)'
@@@param: envp:         Same as the `envp' accepted by `execve(2)'
@@@return: 0 :          Success. (The child process's PID has been stored in `*pid')
@@@return: * :          Error (errno-code describing the reason of failure)
[[argument_names(pidfd, path, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[no_local, requires_function(pidfd_spawn_impl)]]
$errno_t pidfd_spawn([[out]] $fd_t *__restrict pidfd,
                     [[in]] char const *__restrict path,
                     [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                     [[in_opt]] posix_spawnattr_t const *attrp,
                     [[in]] __TARGV, [[in]] __TENVP) {
	return pidfd_spawn_impl(pidfd, POSIX_SPAWN_TYPE_EXECVE, (void *)path, file_actions, attrp, ___argv, ___envp);
}

@@>> pidfd_spawnp(3)
@@Same as `posix_spawnp(3)', but use a "PIDfd" like `pidfd_spawn(3)'
[[argument_names(pidfd, file, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[no_local, requires_function(pidfd_spawn_impl)]]
$errno_t pidfd_spawnp([[out]] $fd_t *__restrict pidfd,
                      [[in]] char const *__restrict file,
                      [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                      [[in_opt]] posix_spawnattr_t const *attrp,
                      [[in]] __TARGV, [[in]] __TENVP) {
	return pidfd_spawn_impl(pidfd, POSIX_SPAWN_TYPE_EXECVPE, (void *)file, file_actions, attrp, ___argv, ___envp);
}


@@>> pidfd_fspawn_np(3)
@@Same as `posix_fspawn_np(3)', but use a "PIDfd" like `pidfd_spawn(3)'
[[argument_names(pidfd, execfd, file_actions, attrp, ___argv, ___envp)]]
[[cp, decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>", "<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[no_local, requires_function(pidfd_spawn_impl)]]
$errno_t pidfd_fspawn_np([[out]] $fd_t *__restrict pidfd, [[fdread]] $fd_t execfd,
                         [[in_opt]] posix_spawn_file_actions_t const *file_actions,
                         [[in_opt]] posix_spawnattr_t const *attrp,
                         [[in]] __TARGV, [[in]] __TENVP) {
	return pidfd_spawn_impl(pidfd, POSIX_SPAWN_TYPE_FEXECVE, (void *)(uintptr_t)execfd, file_actions, attrp, ___argv, ___envp);
}

%#endif /* __USE_MISC */


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
