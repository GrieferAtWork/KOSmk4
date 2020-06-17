/* HASH CRC-32:0xf5509d40 */
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
#ifndef _SPAWN_H
#define _SPAWN_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

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


#ifdef __CRT_HAVE_posix_spawn
/* Spawn a new process executing PATH with the attributes describes in *ATTRP.
 * Before running the process perform the actions described in FILE-ACTIONS.
 * This function is a possible cancellation point and therefore not marked with __THROW */
__CDECLARE(__ATTR_NONNULL((1, 2, 5, 6)),int,__NOTHROW_RPC,posix_spawn,(pid_t *__restrict __pid, char const *__restrict __path, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP),(__pid,__path,__file_actions,__attrp,___argv,___envp))
#endif /* __CRT_HAVE_posix_spawn */

#ifdef __CRT_HAVE_posix_spawnp
/* Similar to `posix_spawn' but search for FILE in the PATH.
 * This function is a possible cancellation point and therefore not marked with __THROW */
__CDECLARE(__ATTR_NONNULL((1, 2, 5, 6)),int,__NOTHROW_RPC,posix_spawnp,(pid_t *__restrict __pid, const char *__restrict __file, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP),(__pid,__file,__file_actions,__attrp,___argv,___envp))
#endif /* __CRT_HAVE_posix_spawnp */

#ifdef __CRT_HAVE_posix_spawnattr_init
/* Initialize data structure with attributes for `spawn' to default values */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_init,(posix_spawnattr_t *__restrict __attr),(__attr))
#endif /* __CRT_HAVE_posix_spawnattr_init */

#ifdef __CRT_HAVE_posix_spawnattr_destroy
/* Free resources associated with ATTR */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_destroy,(posix_spawnattr_t *__restrict __attr),(__attr))
#endif /* __CRT_HAVE_posix_spawnattr_destroy */

#ifdef __CRT_HAVE_posix_spawnattr_getsigdefault
/* Store signal mask for signals with default handling from ATTR in SIGDEFAULT */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getsigdefault,(posix_spawnattr_t const *__restrict __attr, sigset_t *__restrict __sigdefault),(__attr,__sigdefault))
#endif /* __CRT_HAVE_posix_spawnattr_getsigdefault */

#ifdef __CRT_HAVE_posix_spawnattr_setsigdefault
/* Set signal mask for signals with default handling in ATTR to SIGDEFAULT */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_setsigdefault,(posix_spawnattr_t *__restrict __attr, sigset_t const *__restrict __sigdefault),(__attr,__sigdefault))
#endif /* __CRT_HAVE_posix_spawnattr_setsigdefault */

#ifdef __CRT_HAVE_posix_spawnattr_getsigmask
/* Store signal mask for the new process from ATTR in SIGMASK */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getsigmask,(posix_spawnattr_t const *__restrict __attr, sigset_t *__restrict __sigmask),(__attr,__sigmask))
#endif /* __CRT_HAVE_posix_spawnattr_getsigmask */

#ifdef __CRT_HAVE_posix_spawnattr_setsigmask
/* Set signal mask for the new process in ATTR to SIGMASK */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_setsigmask,(posix_spawnattr_t *__restrict __attr, sigset_t const *__restrict __sigmask),(__attr,__sigmask))
#endif /* __CRT_HAVE_posix_spawnattr_setsigmask */

#ifdef __CRT_HAVE_posix_spawnattr_getflags
/* Get flag word from the attribute structure */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getflags,(posix_spawnattr_t const *__restrict __attr, __INT16_TYPE__ *__restrict __flags),(__attr,__flags))
#endif /* __CRT_HAVE_posix_spawnattr_getflags */

#ifdef __CRT_HAVE_posix_spawnattr_setflags
/* Store flags in the attribute structure */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_setflags,(posix_spawnattr_t *__restrict __attr, short int __flags),(__attr,__flags))
#endif /* __CRT_HAVE_posix_spawnattr_setflags */

#ifdef __CRT_HAVE_posix_spawnattr_getpgroup
/* Get process group ID from the attribute structure */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getpgroup,(posix_spawnattr_t const *__restrict __attr, pid_t *__restrict __pgroup),(__attr,__pgroup))
#endif /* __CRT_HAVE_posix_spawnattr_getpgroup */

#ifdef __CRT_HAVE_posix_spawnattr_setpgroup
/* Store rocess group ID in the attribute structure */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_setpgroup,(posix_spawnattr_t *__restrict __attr, pid_t __pgroup),(__attr,__pgroup))
#endif /* __CRT_HAVE_posix_spawnattr_setpgroup */

#ifdef __CRT_HAVE_posix_spawnattr_getschedpolicy
/* Get scheduling policy from the attribute structure */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getschedpolicy,(posix_spawnattr_t const *__restrict __attr, int *__restrict __schedpolicy),(__attr,__schedpolicy))
#endif /* __CRT_HAVE_posix_spawnattr_getschedpolicy */

#ifdef __CRT_HAVE_posix_spawnattr_setschedpolicy
/* Store scheduling policy in the attribute structure */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawnattr_setschedpolicy,(posix_spawnattr_t *__restrict __attr, int __schedpolicy),(__attr,__schedpolicy))
#endif /* __CRT_HAVE_posix_spawnattr_setschedpolicy */

#ifdef __CRT_HAVE_posix_spawnattr_getschedparam
/* Get scheduling parameters from the attribute structure */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_getschedparam,(posix_spawnattr_t const *__restrict __attr, struct sched_param *__restrict __schedparam),(__attr,__schedparam))
#endif /* __CRT_HAVE_posix_spawnattr_getschedparam */

#ifdef __CRT_HAVE_posix_spawnattr_setschedparam
/* Store scheduling parameters in the attribute structure */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,posix_spawnattr_setschedparam,(posix_spawnattr_t *__restrict __attr, struct sched_param const *__restrict __schedparam),(__attr,__schedparam))
#endif /* __CRT_HAVE_posix_spawnattr_setschedparam */

#ifdef __CRT_HAVE_posix_spawn_file_actions_init
/* Initialize data structure for file attribute for `spawn' call */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawn_file_actions_init,(posix_spawn_file_actions_t *__restrict __file_actions),(__file_actions))
#endif /* __CRT_HAVE_posix_spawn_file_actions_init */

#ifdef __CRT_HAVE_posix_spawn_file_actions_destroy
/* Free resources associated with FILE-ACTIONS */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawn_file_actions_destroy,(posix_spawn_file_actions_t *__restrict __file_actions),(__file_actions))
#endif /* __CRT_HAVE_posix_spawn_file_actions_destroy */

#ifdef __CRT_HAVE_posix_spawn_file_actions_addopen
/* Add an action to FILE-ACTIONS which tells the implementation
 * to call `open' for the given file during the `spawn' call */
__CDECLARE(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,posix_spawn_file_actions_addopen,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd, char const *__restrict __path, __oflag_t __oflags, mode_t __mode),(__file_actions,__fd,__path,__oflags,__mode))
#endif /* __CRT_HAVE_posix_spawn_file_actions_addopen */

#ifdef __CRT_HAVE_posix_spawn_file_actions_addclose
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `close' for the given file descriptor during the `spawn' call */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawn_file_actions_addclose,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd),(__file_actions,__fd))
#endif /* __CRT_HAVE_posix_spawn_file_actions_addclose */

#ifdef __CRT_HAVE_posix_spawn_file_actions_adddup2
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `dup2' for the given file descriptors during the `spawn' call */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_spawn_file_actions_adddup2,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd, __fd_t __newfd),(__file_actions,__fd,__newfd))
#endif /* __CRT_HAVE_posix_spawn_file_actions_adddup2 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SPAWN_H */
