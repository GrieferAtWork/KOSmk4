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

#include <asm/crt/posix_spawn.h>
#include <bits/crt/posix_spawn.h>
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
#define POSIX_SPAWN_RESETIDS __POSIX_SPAWN_RESETIDS
#endif /* __POSIX_SPAWN_RESETIDS */
#ifdef __POSIX_SPAWN_SETPGROUP
#define POSIX_SPAWN_SETPGROUP __POSIX_SPAWN_SETPGROUP
#endif /* __POSIX_SPAWN_SETPGROUP */
#ifdef __POSIX_SPAWN_SETSIGDEF
#define POSIX_SPAWN_SETSIGDEF __POSIX_SPAWN_SETSIGDEF
#endif /* __POSIX_SPAWN_SETSIGDEF */
#ifdef __POSIX_SPAWN_SETSIGMASK
#define POSIX_SPAWN_SETSIGMASK __POSIX_SPAWN_SETSIGMASK
#endif /* __POSIX_SPAWN_SETSIGMASK */
#ifdef __POSIX_SPAWN_SETSCHEDPARAM
#define POSIX_SPAWN_SETSCHEDPARAM __POSIX_SPAWN_SETSCHEDPARAM
#endif /* __POSIX_SPAWN_SETSCHEDPARAM */
#ifdef __POSIX_SPAWN_SETSCHEDULER
#define POSIX_SPAWN_SETSCHEDULER __POSIX_SPAWN_SETSCHEDULER
#endif /* __POSIX_SPAWN_SETSCHEDULER */
#ifdef __USE_GNU
#ifdef __POSIX_SPAWN_USEVFORK
#define POSIX_SPAWN_USEVFORK __POSIX_SPAWN_USEVFORK
#endif /* __POSIX_SPAWN_USEVFORK */
#endif /* __USE_GNU */


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


%
@@Spawn a new process executing PATH with the attributes describes in *ATTRP.
@@Before running the process perform the actions described in FILE-ACTIONS.
@@This function is a possible cancellation point and therefore not marked with __THROW
[[cp, decl_prefix(DEFINE_TARGV), decl_include("<bits/crt/posix_spawn.h>")]]
[[argument_names(pid, path, file_actions, attrp, ___argv, ___envp)]]
int posix_spawn([[nonnull]] pid_t *__restrict pid,
                [[nonnull]] char const *__restrict path,
                [[nullable]] posix_spawn_file_actions_t const *file_actions,
                [[nullable]] posix_spawnattr_t const *attrp,
                [[nonnull]] __TARGV, [[nonnull]] __TENVP);

%
@@Similar to `posix_spawn' but search for FILE in the PATH.
@@This function is a possible cancellation point and therefore not marked with __THROW
[[cp, decl_prefix(DEFINE_TARGV), decl_include("<bits/crt/posix_spawn.h>")]]
[[argument_names(pid, file, file_actions, attrp, ___argv, ___envp)]]
int posix_spawnp([[nonnull]] pid_t *__restrict pid,
                 [[nonnull]] const char *__restrict file,
                 [[nullable]] posix_spawn_file_actions_t const *file_actions,
                 [[nullable]] posix_spawnattr_t const *attrp,
                 [[nonnull]] __TARGV, [[nonnull]] __TENVP);

%
@@Initialize data structure with attributes for `spawn' to default values
[[decl_include("<bits/crt/posix_spawn.h>")]]
int posix_spawnattr_init([[nonnull]] posix_spawnattr_t *__restrict attr);

%
@@Free resources associated with ATTR
[[decl_include("<bits/crt/posix_spawn.h>")]]
int posix_spawnattr_destroy([[nonnull]] posix_spawnattr_t *__restrict attr);

%
@@Store signal mask for signals with default handling from ATTR in SIGDEFAULT
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sigset.h>")]]
int posix_spawnattr_getsigdefault([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                  [[nonnull]] sigset_t *__restrict sigdefault);

%
@@Set signal mask for signals with default handling in ATTR to SIGDEFAULT
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sigset.h>")]]
int posix_spawnattr_setsigdefault([[nonnull]] posix_spawnattr_t *__restrict attr,
                                  [[nonnull]] sigset_t const *__restrict sigdefault);

%
@@Store signal mask for the new process from ATTR in SIGMASK
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sigset.h>")]]
int posix_spawnattr_getsigmask([[nonnull]] posix_spawnattr_t const *__restrict attr,
                               [[nonnull]] sigset_t *__restrict sigmask);

%
@@Set signal mask for the new process in ATTR to SIGMASK
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sigset.h>")]]
int posix_spawnattr_setsigmask([[nonnull]] posix_spawnattr_t *__restrict attr,
                               [[nonnull]] sigset_t const *__restrict sigmask);

%
@@Get flag word from the attribute structure
[[decl_include("<bits/crt/posix_spawn.h>")]]
int posix_spawnattr_getflags([[nonnull]] posix_spawnattr_t const *__restrict attr,
                             [[nonnull]] $int16_t *__restrict flags);

%
@@Store flags in the attribute structure
[[decl_include("<bits/crt/posix_spawn.h>")]]
int posix_spawnattr_setflags([[nonnull]] posix_spawnattr_t *__restrict attr,
                             $int16_t flags);

%
@@Get process group ID from the attribute structure
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
int posix_spawnattr_getpgroup([[nonnull]] posix_spawnattr_t const *__restrict attr,
                              [[nonnull]] pid_t *__restrict pgroup);

%
@@Store rocess group ID in the attribute structure
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
int posix_spawnattr_setpgroup([[nonnull]] posix_spawnattr_t *__restrict attr, pid_t pgroup);

%
@@Get scheduling policy from the attribute structure
[[decl_include("<bits/crt/posix_spawn.h>")]]
int posix_spawnattr_getschedpolicy([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                   [[nonnull]] int *__restrict schedpolicy);

%
@@Store scheduling policy in the attribute structure
[[decl_include("<bits/crt/posix_spawn.h>")]]
int posix_spawnattr_setschedpolicy([[nonnull]] posix_spawnattr_t *__restrict attr,
                                   int schedpolicy);

%
@@Get scheduling parameters from the attribute structure
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sched_param.h>")]]
int posix_spawnattr_getschedparam([[nonnull]] posix_spawnattr_t const *__restrict attr,
                                  [[nonnull]] struct sched_param *__restrict schedparam);

%
@@Store scheduling parameters in the attribute structure
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/sched_param.h>")]]
int posix_spawnattr_setschedparam([[nonnull]] posix_spawnattr_t *__restrict attr,
                                  [[nonnull]] struct sched_param const *__restrict schedparam);


%
@@Initialize data structure for file attribute for `spawn' call
[[decl_include("<bits/crt/posix_spawn.h>")]]
int posix_spawn_file_actions_init([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions);

%
@@Free resources associated with FILE-ACTIONS
[[decl_include("<bits/crt/posix_spawn.h>")]]
int posix_spawn_file_actions_destroy([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions);

%
@@Add an action to FILE-ACTIONS which tells the implementation
@@to call `open' for the given file during the `spawn' call
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
int posix_spawn_file_actions_addopen([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions,
                                     $fd_t fd, [[nonnull]] char const *__restrict path,
                                     $oflag_t oflags, mode_t mode);

%
@@Add an action to FILE-ACTIONS which tells the implementation to
@@call `close' for the given file descriptor during the `spawn' call
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
int posix_spawn_file_actions_addclose([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions, $fd_t fd);

%
@@Add an action to FILE-ACTIONS which tells the implementation to
@@call `dup2' for the given file descriptors during the `spawn' call
[[decl_include("<bits/crt/posix_spawn.h>", "<bits/types.h>")]]
int posix_spawn_file_actions_adddup2([[nonnull]] posix_spawn_file_actions_t *__restrict file_actions,
                                     $fd_t fd, $fd_t newfd);


%{

#endif /* __CC__ */

__SYSDECL_END

}