/* HASH CRC-32:0x6fc75ac9 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SPAWN_H
#define GUARD_LIBC_USER_SPAWN_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <spawn.h>

DECL_BEGIN

/* Spawn a new process executing PATH with the attributes describes in *ATTRP.
 * Before running the process perform the actions described in FILE-ACTIONS.
 * This function is a possible cancellation point and therefore not marked with __THROW */
INTDEF NONNULL((1, 2, 5, 6)) int NOTHROW_RPC(LIBCCALL libc_posix_spawn)(pid_t *__restrict pid, char const *__restrict path, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
/* Similar to `posix_spawn' but search for FILE in the PATH.
 * This function is a possible cancellation point and therefore not marked with __THROW */
INTDEF NONNULL((1, 2, 5, 6)) int NOTHROW_RPC(LIBCCALL libc_posix_spawnp)(pid_t *__restrict pid, const char *__restrict file, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
/* Initialize data structure with attributes for `spawn' to default values */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_init)(posix_spawnattr_t *__restrict attr);
/* Free resources associated with ATTR */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_destroy)(posix_spawnattr_t *__restrict attr);
/* Store signal mask for signals with default handling from ATTR in SIGDEFAULT */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigdefault)(posix_spawnattr_t const * __restrict attr, sigset_t *__restrict sigdefault);
/* Set signal mask for signals with default handling in ATTR to SIGDEFAULT */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigdefault)(posix_spawnattr_t *__restrict attr, sigset_t const *__restrict sigdefault);
/* Store signal mask for the new process from ATTR in SIGMASK */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigmask)(posix_spawnattr_t const *__restrict attr, sigset_t *__restrict sigmask);
/* Set signal mask for the new process in ATTR to SIGMASK */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigmask)(posix_spawnattr_t *__restrict attr, sigset_t const *__restrict sigmask);
/* Get flag word from the attribute structure */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getflags)(posix_spawnattr_t const *__restrict attr, int16_t *__restrict flags);
/* Store flags in the attribute structure */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setflags)(posix_spawnattr_t *__restrict attr, short int flags);
/* Get process group ID from the attribute structure */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getpgroup)(posix_spawnattr_t const *__restrict attr, pid_t *__restrict pgroup);
/* Store process group ID in the attribute structure */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setpgroup)(posix_spawnattr_t *__restrict attr, pid_t pgroup);
/* Get scheduling policy from the attribute structure */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedpolicy)(posix_spawnattr_t const *__restrict attr, int *__restrict schedpolicy);
/* Store scheduling policy in the attribute structure */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedpolicy)(posix_spawnattr_t *__restrict attr, int schedpolicy);
/* Get scheduling parameters from the attribute structure */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedparam)(posix_spawnattr_t const *__restrict attr, struct sched_param *__restrict schedparam);
/* Store scheduling parameters in the attribute structure */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedparam)(posix_spawnattr_t *__restrict attr, struct sched_param const *__restrict schedparam);
/* Initialize data structure for file attribute for `spawn' call */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_init)(posix_spawn_file_actions_t *__restrict file_actions);
/* Free resources associated with FILE-ACTIONS */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_destroy)(posix_spawn_file_actions_t *__restrict file_actions);
/* Add an action to FILE-ACTIONS which tells the implementation
 * to call `open' for the given file during the `spawn' call */
INTDEF NONNULL((1, 3)) int NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addopen)(posix_spawn_file_actions_t *__restrict file_actions, fd_t fd, char const *__restrict path, oflag_t oflags, mode_t mode);
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `close' for the given file descriptor during the `spawn' call */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addclose)(posix_spawn_file_actions_t *__restrict file_actions, fd_t fd);
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `dup2' for the given file descriptors during the `spawn' call */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_adddup2)(posix_spawn_file_actions_t *__restrict file_actions, fd_t fd, fd_t newfd);

DECL_END

#endif /* !GUARD_LIBC_USER_SPAWN_H */
