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
/*!included_by <spawn.h>*/
#ifndef _BITS_CRT_POSIX_SPAWN_H
#define _BITS_CRT_POSIX_SPAWN_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <asm/crt/posix_spawn.h>
#include <bits/os/sched.h>  /* struct sched_param */
#include <bits/os/sigset.h> /* struct __sigset_struct */
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/* Data structure to contain attributes for thread creation. */
struct __posix_spawnattr {
#ifdef __POSIX_SPAWN_USE_KOS
	__UINT16_TYPE__        __flags;   /* Spawn attribute flags (set of `__POSIX_SPAWN_*' ) */
#if __SIZEOF_PID_T__ > 2
	__UINT16_TYPE__        __pad1[(sizeof(__pid_t) - 2) / 2];
#endif /* __SIZEOF_PID_T__ > 2 */
	__pid_t                __pgrp;    /* [valid_if(__flags & __POSIX_SPAWN_SETPGROUP)] Value for `setpgrp(0, __pgrp)' */
	struct __sigset_struct __sd;      /* [valid_if(__flags & __POSIX_SPAWN_SETSIGDEF)] Set of signals that should have their disposition reset. */
	struct __sigset_struct __ss;      /* [valid_if(__flags & __POSIX_SPAWN_SETSIGMASK)] Value for `sigprocmask(SIG_SETMASK, &__ss, NULL)' */
	struct sched_param     __sp;      /* [valid_if(__flags & __POSIX_SPAWN_SETSCHEDPARAM)] Value for `sched_setscheduler(0, -1, &__sp)' */
	int                    __policy;  /* [valid_if(__flags & __POSIX_SPAWN_SETSCHEDULER)] Value for `sched_setscheduler(0, __policy, NULL)' */
	int                    __pad[16]; /* ... */
#elif defined(__CRT_CYG)
	/* TODO: Cygwin structure layout! */
	int __placeholder[64];
#else /* ... */
	int __placeholder[64];
#endif /* !... */
};

/* Data structure to contain information about the actions to  be
 * performed in the new process with respect to file descriptors. */
#ifdef __POSIX_SPAWN_USE_KOS
#define __POSIX_SPAWN_ACTION_CLOSE  0 /* Close a file handle */
#define __POSIX_SPAWN_ACTION_DUP2   1 /* Duplicate a file handle */
#define __POSIX_SPAWN_ACTION_OPEN   2 /* Open a file using `open(2)' */
#define __POSIX_SPAWN_ACTION_CHDIR  3 /* Change direction using `chdir(2)' */
#define __POSIX_SPAWN_ACTION_FCHDIR 4 /* Change direction using `fchdir(2)' */
#ifdef __CRT_KOS
#define __POSIX_SPAWN_ACTION_TCSETPGRP 5 /* Call `tcsetpgrp(fd, getpid())' */
#define __POSIX_SPAWN_ACTION_CLOSEFROM 6 /* Call `closefrom(fd)' */
#endif /* __CRT_KOS */
struct __spawn_action {
	unsigned int __sa_tag; /* Action type (one of `__POSIX_SPAWN_ACTION_*') */
	union {

		struct {
			__fd_t __sa_fd;  /* FD to close */
		} __sa_close_action; /* __POSIX_SPAWN_ACTION_CLOSE */

		struct {
			__fd_t __sa_oldfd; /* Old FD */
			__fd_t __sa_newfd; /* New FD */
		} __sa_dup2_action;  /* __POSIX_SPAWN_ACTION_DUP2 */

		struct {
			__fd_t    __sa_fd;    /* FD to open. */
			char     *__sa_path;  /* [1..1][owned] Filename to use. */
			__oflag_t __sa_oflag; /* Open-flags to pass. */
			__mode_t  __sa_mode;  /* Open mode. */
		} __sa_open_action;  /* __POSIX_SPAWN_ACTION_OPEN */

		struct {
			char *__sa_path;  /* [1..1][owned] Path to chdir(2) to. */
		} __sa_chdir_action;  /* __POSIX_SPAWN_ACTION_CHDIR */

		struct {
			__fd_t __sa_fd;   /* Fd to fchdir(2) to. */
		} __sa_fchdir_action; /* __POSIX_SPAWN_ACTION_FCHDIR */

#ifdef __CRT_KOS
		struct {
			__fd_t __sa_fd;  /* `tcsetpgrp(__sa_fd, getpid())' */
		} __sa_tcsetpgrp_action; /* __POSIX_SPAWN_ACTION_TCSETPGRP */

		struct {
			__fd_t __sa_fd;  /* `closefrom(__sa_fd)' */
		} __sa_closefrom_action; /* __POSIX_SPAWN_ACTION_CLOSEFROM */
#endif /* __CRT_KOS */

	} __sa_action; /* Action-specific data. */
};
#endif /* __POSIX_SPAWN_USE_KOS */


struct __posix_spawn_file_actions {
#ifdef __POSIX_SPAWN_USE_KOS
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("__allocated")
#pragma push_macro("__used")
#pragma push_macro("__actions")
#pragma push_macro("__pad")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __allocated
#undef __used
#undef __actions
#undef __pad
	__STDC_INT_AS_UINT_T   __allocated;
	__STDC_INT_AS_UINT_T   __used;
	struct __spawn_action *__actions;
	int                    __pad[16];
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__pad")
#pragma pop_macro("__actions")
#pragma pop_macro("__used")
#pragma pop_macro("__allocated")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#elif defined(__CRT_CYG)
	/* TODO: Cygwin structure layout! */
	int __placeholder[64];
#else /* ... */
	int __placeholder[64];
#endif /* !... */
};


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_POSIX_SPAWN_H */
