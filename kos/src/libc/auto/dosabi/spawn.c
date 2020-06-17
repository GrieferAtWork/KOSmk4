/* HASH CRC-32:0x2c67634 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SPAWN_C
#define GUARD_LIBC_AUTO_DOSABI_SPAWN_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/spawn.h"

DECL_BEGIN

/* Spawn a new process executing PATH with the attributes describes in *ATTRP.
 * Before running the process perform the actions described in FILE-ACTIONS.
 * This function is a possible cancellation point and therefore not marked with __THROW */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2, 5, 6)) int
NOTHROW_RPC(LIBDCALL libd_posix_spawn)(pid_t *__restrict pid,
                                       char const *__restrict path,
                                       posix_spawn_file_actions_t const *file_actions,
                                       posix_spawnattr_t const *attrp,
                                       __TARGV,
                                       __TENVP) {
	return libc_posix_spawn(pid, path, file_actions, attrp, ___argv, ___envp);
}
/* Similar to `posix_spawn' but search for FILE in the PATH.
 * This function is a possible cancellation point and therefore not marked with __THROW */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2, 5, 6)) int
NOTHROW_RPC(LIBDCALL libd_posix_spawnp)(pid_t *__restrict pid,
                                        const char *__restrict file,
                                        posix_spawn_file_actions_t const *file_actions,
                                        posix_spawnattr_t const *attrp,
                                        __TARGV,
                                        __TENVP) {
	return libc_posix_spawnp(pid, file, file_actions, attrp, ___argv, ___envp);
}
/* Initialize data structure with attributes for `spawn' to default values */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_init)(posix_spawnattr_t *__restrict attr) {
	return libc_posix_spawnattr_init(attr);
}
/* Free resources associated with ATTR */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_destroy)(posix_spawnattr_t *__restrict attr) {
	return libc_posix_spawnattr_destroy(attr);
}
/* Store signal mask for signals with default handling from ATTR in SIGDEFAULT */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getsigdefault)(posix_spawnattr_t const *__restrict attr,
                                                         sigset_t *__restrict sigdefault) {
	return libc_posix_spawnattr_getsigdefault(attr, sigdefault);
}
/* Set signal mask for signals with default handling in ATTR to SIGDEFAULT */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setsigdefault)(posix_spawnattr_t *__restrict attr,
                                                         sigset_t const *__restrict sigdefault) {
	return libc_posix_spawnattr_setsigdefault(attr, sigdefault);
}
/* Store signal mask for the new process from ATTR in SIGMASK */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getsigmask)(posix_spawnattr_t const *__restrict attr,
                                                      sigset_t *__restrict sigmask) {
	return libc_posix_spawnattr_getsigmask(attr, sigmask);
}
/* Set signal mask for the new process in ATTR to SIGMASK */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setsigmask)(posix_spawnattr_t *__restrict attr,
                                                      sigset_t const *__restrict sigmask) {
	return libc_posix_spawnattr_setsigmask(attr, sigmask);
}
/* Get flag word from the attribute structure */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getflags)(posix_spawnattr_t const *__restrict attr,
                                                    int16_t *__restrict flags) {
	return libc_posix_spawnattr_getflags(attr, flags);
}
/* Store flags in the attribute structure */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setflags)(posix_spawnattr_t *__restrict attr,
                                                    short int flags) {
	return libc_posix_spawnattr_setflags(attr, flags);
}
/* Get process group ID from the attribute structure */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getpgroup)(posix_spawnattr_t const *__restrict attr,
                                                     pid_t *__restrict pgroup) {
	return libc_posix_spawnattr_getpgroup(attr, pgroup);
}
/* Store rocess group ID in the attribute structure */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setpgroup)(posix_spawnattr_t *__restrict attr,
                                                     pid_t pgroup) {
	return libc_posix_spawnattr_setpgroup(attr, pgroup);
}
/* Get scheduling policy from the attribute structure */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getschedpolicy)(posix_spawnattr_t const *__restrict attr,
                                                          int *__restrict schedpolicy) {
	return libc_posix_spawnattr_getschedpolicy(attr, schedpolicy);
}
/* Store scheduling policy in the attribute structure */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setschedpolicy)(posix_spawnattr_t *__restrict attr,
                                                          int schedpolicy) {
	return libc_posix_spawnattr_setschedpolicy(attr, schedpolicy);
}
/* Get scheduling parameters from the attribute structure */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getschedparam)(posix_spawnattr_t const *__restrict attr,
                                                         struct sched_param *__restrict schedparam) {
	return libc_posix_spawnattr_getschedparam(attr, schedparam);
}
/* Store scheduling parameters in the attribute structure */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setschedparam)(posix_spawnattr_t *__restrict attr,
                                                         struct sched_param const *__restrict schedparam) {
	return libc_posix_spawnattr_setschedparam(attr, schedparam);
}
/* Initialize data structure for file attribute for `spawn' call */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_init)(posix_spawn_file_actions_t *__restrict file_actions) {
	return libc_posix_spawn_file_actions_init(file_actions);
}
/* Free resources associated with FILE-ACTIONS */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_destroy)(posix_spawn_file_actions_t *__restrict file_actions) {
	return libc_posix_spawn_file_actions_destroy(file_actions);
}
/* Add an action to FILE-ACTIONS which tells the implementation
 * to call `open' for the given file during the `spawn' call */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1, 3)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_addopen)(posix_spawn_file_actions_t *__restrict file_actions,
                                                            fd_t fd,
                                                            char const *__restrict path,
                                                            oflag_t oflags,
                                                            mode_t mode) {
	return libc_posix_spawn_file_actions_addopen(file_actions, fd, path, oflags, mode);
}
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `close' for the given file descriptor during the `spawn' call */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_addclose)(posix_spawn_file_actions_t *__restrict file_actions,
                                                             fd_t fd) {
	return libc_posix_spawn_file_actions_addclose(file_actions, fd);
}
/* Add an action to FILE-ACTIONS which tells the implementation to
 * call `dup2' for the given file descriptors during the `spawn' call */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.posix_spawn") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_adddup2)(posix_spawn_file_actions_t *__restrict file_actions,
                                                            fd_t fd,
                                                            fd_t newfd) {
	return libc_posix_spawn_file_actions_adddup2(file_actions, fd, newfd);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$posix_spawn, libd_posix_spawn);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnp, libd_posix_spawnp);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_init, libd_posix_spawnattr_init);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_destroy, libd_posix_spawnattr_destroy);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getsigdefault, libd_posix_spawnattr_getsigdefault);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setsigdefault, libd_posix_spawnattr_setsigdefault);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getsigmask, libd_posix_spawnattr_getsigmask);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setsigmask, libd_posix_spawnattr_setsigmask);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getflags, libd_posix_spawnattr_getflags);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setflags, libd_posix_spawnattr_setflags);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getpgroup, libd_posix_spawnattr_getpgroup);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setpgroup, libd_posix_spawnattr_setpgroup);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getschedpolicy, libd_posix_spawnattr_getschedpolicy);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setschedpolicy, libd_posix_spawnattr_setschedpolicy);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_getschedparam, libd_posix_spawnattr_getschedparam);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawnattr_setschedparam, libd_posix_spawnattr_setschedparam);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_init, libd_posix_spawn_file_actions_init);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_destroy, libd_posix_spawn_file_actions_destroy);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_addopen, libd_posix_spawn_file_actions_addopen);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_addclose, libd_posix_spawn_file_actions_addclose);
DEFINE_PUBLIC_ALIAS(DOS$posix_spawn_file_actions_adddup2, libd_posix_spawn_file_actions_adddup2);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SPAWN_C */
