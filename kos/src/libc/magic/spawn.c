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
%[define_replacement(posix_spawnattr_t = posix_spawnattr_t)]
%[define_replacement(posix_spawn_file_actions_t = posix_spawn_file_actions_t)]
%[default:section(".text.crt.fs.exec.posix_spawn")]


%{
#include <features.h>
#include <sched.h>
#include <bits/sigset.h>
#include <sys/types.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Comments taken from /usr/include/spawn.h of a linux machine.
 * The following is the copyright notice found in the original file. */
/* Definitions for POSIX spawn interface.
   Copyright (C) 2000-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


/* Flags to be set in the `posix_spawnattr_t'. */
#ifdef __CRT_CYG_PRIMARY
#define POSIX_SPAWN_RESETIDS        0x01
#define POSIX_SPAWN_SETPGROUP       0x02
#define POSIX_SPAWN_SETSCHEDPARAM   0x04
#define POSIX_SPAWN_SETSCHEDULER    0x08
#define POSIX_SPAWN_SETSIGDEF       0x10
#define POSIX_SPAWN_SETSIGMASK      0x20
#else /* __CRT_CYG_PRIMARY */
#define POSIX_SPAWN_RESETIDS        0x01
#define POSIX_SPAWN_SETPGROUP       0x02
#define POSIX_SPAWN_SETSIGDEF       0x04
#define POSIX_SPAWN_SETSIGMASK      0x08
#define POSIX_SPAWN_SETSCHEDPARAM   0x10
#define POSIX_SPAWN_SETSCHEDULER    0x20
#ifdef __USE_GNU
#define POSIX_SPAWN_USEVFORK        0x40
#endif /* __USE_GNU */
#endif /* !__CRT_CYG_PRIMARY */


#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !pid_t_defined */


/* Data structure to contain attributes for thread creation. */
typedef struct {
	/* TODO: Cygwin structure layout! */
	short int          __flags;
	pid_t              __pgrp;
	sigset_t           __sd;
	sigset_t           __ss;
	struct sched_param __sp;
	int                __policy;
	int                __pad[16];
} posix_spawnattr_t;


/* Data structure to contain information about the actions to be
 * performed in the new process with respect to file descriptors. */
typedef struct {
	/* TODO: Cygwin structure layout! */
	int                    __allocated;
	int                    __used;
	struct __spawn_action *__actions;
	int                    __pad[16];
} posix_spawn_file_actions_t;

#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* ! */
#endif /* !__TARGV */

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


%
@@Spawn a new process executing PATH with the attributes describes in *ATTRP.
@@Before running the process perform the actions described in FILE-ACTIONS.
@@This function is a possible cancellation point and therefore not marked with __THROW
[[cp, decl_prefix(DEFINE_TARGV)]]
int posix_spawn([[nonnull]] pid_t *__restrict pid,
                [[nonnull]] char const *__restrict path,
                [[nullable]] posix_spawn_file_actions_t const *file_actions,
                [[nullable]] posix_spawnattr_t const *attrp,
                [[nonnull]] __TARGV, [[nonnull]] __TENVP);

%
@@Similar to `posix_spawn' but search for FILE in the PATH.
@@This function is a possible cancellation point and therefore not marked with __THROW
[[cp, decl_prefix(DEFINE_TARGV)]]
int posix_spawnp([[nonnull]] pid_t *__restrict pid,
                 [[nonnull]] const char *__restrict file,
                 [[nullable]] posix_spawn_file_actions_t const *file_actions,
                 [[nullable]] posix_spawnattr_t const *attrp,
                 [[nonnull]] __TARGV, [[nonnull]] __TENVP);

%
@@Initialize data structure with attributes for `spawn' to default values
int posix_spawnattr_init([[nonnull]] posix_spawnattr_t *__restrict attr);

%
@@Free resources associated with ATTR
int posix_spawnattr_destroy([[nonnull]] posix_spawnattr_t *__restrict attr);

%
@@Store signal mask for signals with default handling from ATTR in SIGDEFAULT
int posix_spawnattr_getsigdefault([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                  [[nonnull]] sigset_t *__restrict sigdefault);

%
@@Set signal mask for signals with default handling in ATTR to SIGDEFAULT
int posix_spawnattr_setsigdefault([[nonnull]] posix_spawnattr_t *__restrict attr,
                                  [[nonnull]] sigset_t const *__restrict sigdefault);

%
@@Store signal mask for the new process from ATTR in SIGMASK
int posix_spawnattr_getsigmask([[nonnull]] posix_spawnattr_t const *__restrict attr,
                               [[nonnull]] sigset_t *__restrict sigmask);

%
@@Set signal mask for the new process in ATTR to SIGMASK
int posix_spawnattr_setsigmask([[nonnull]] posix_spawnattr_t *__restrict attr,
                               [[nonnull]] sigset_t const *__restrict sigmask);

%
@@Get flag word from the attribute structure
int posix_spawnattr_getflags([[nonnull]] posix_spawnattr_t const *__restrict attr,
                             [[nonnull]] $int16_t *__restrict flags);

%
@@Store flags in the attribute structure
int posix_spawnattr_setflags([[nonnull]] posix_spawnattr_t *__restrict attr,
                             short int flags);

%
@@Get process group ID from the attribute structure
int posix_spawnattr_getpgroup([[nonnull]] posix_spawnattr_t const *__restrict attr,
                              [[nonnull]] pid_t *__restrict pgroup);

%
@@Store rocess group ID in the attribute structure
int posix_spawnattr_setpgroup([[nonnull]] posix_spawnattr_t *__restrict attr, pid_t pgroup);

%
@@Get scheduling policy from the attribute structure
int posix_spawnattr_getschedpolicy([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                   [[nonnull]] int *__restrict schedpolicy);

%
@@Store scheduling policy in the attribute structure
int posix_spawnattr_setschedpolicy([[nonnull]] posix_spawnattr_t *__restrict attr,
                                   int schedpolicy);

%
@@Get scheduling parameters from the attribute structure
int posix_spawnattr_getschedparam([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                  [[nonnull]] struct sched_param *__restrict schedparam);

%
@@Store scheduling parameters in the attribute structure
int posix_spawnattr_setschedparam([[nonnull]] posix_spawnattr_t *__restrict attr,
                                  [[nonnull]] struct sched_param const *__restrict schedparam);


%
@@Initialize data structure for file attribute for `spawn' call
int posix_spawn_file_actions_init([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions);

%
@@Free resources associated with FILE-ACTIONS
int posix_spawn_file_actions_destroy([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions);

%
@@Add an action to FILE-ACTIONS which tells the implementation
@@to call `open' for the given file during the `spawn' call
int posix_spawn_file_actions_addopen([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions,
                                     $fd_t fd, [[nonnull]] char const *__restrict path,
                                     $oflag_t oflags, mode_t mode);

%
@@Add an action to FILE-ACTIONS which tells the implementation to
@@call `close' for the given file descriptor during the `spawn' call
int posix_spawn_file_actions_addclose([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions, $fd_t fd);

%
@@Add an action to FILE-ACTIONS which tells the implementation to
@@call `dup2' for the given file descriptors during the `spawn' call
int posix_spawn_file_actions_adddup2([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions,
                                     $fd_t fd, $fd_t newfd);


%{

#endif /* __CC__ */

__SYSDECL_END

}