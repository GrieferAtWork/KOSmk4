/* HASH CRC-32:0x2bf16613 */
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
#ifndef GUARD_LIBC_USER_BITS_SCHED_H
#define GUARD_LIBC_USER_BITS_SCHED_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <bits/sched.h>

DECL_BEGIN


#ifndef __cpu_set_t_defined
#define __cpu_set_t_defined 1
typedef __cpu_set_t    cpu_set_t;
#endif /* !__cpu_set_t_defined */

INTDEF NONNULL((1)) pid_t NOTHROW_NCX(VLIBCCALL libc_clone)(__clone_func_t fn, void *child_stack, int flags, void *arg, ... /* pid_t *ptid, void *newtls, pid_t *ctid */);
/* >> unshare(2)
 * Unshare certain components of the calling thread that may be shared with other
 * threads or processes, such as the filesystem, or opened file descriptors.
 * When being unshared, the calling thread's descriptor for a specific component
 * is replaced with a copy of its previous contents at that moment in time, with
 * the notable exception of certain KOS-specific extensions, where specifically
 * marked data will be deleted (s.a. `O_CLOFORK' and `PROT_LOOSE')
 * The behavior and meaning of individual bits in `flags' matches their meaning
 * when passed to `clone()', except that for certain flags the meaning is reversed.
 * For example: Passing `CLONE_FILES' to `clone(2)' will cause handles to be shared,
 *              but passing it to `unshare(2)' will cause handles to be unshared.
 * @param: flags: Set of `CLONE_*' flags:
 *                 - CLONE_FILES:     Unshare handles (and close all marked as `O_CLOFORK')
 *                 - CLONE_FS:        Unshare umask(), chroot(), chdir(), fsmode() and drive-cwds
 *                 - CLONE_NEWCGROUP: ...
 *                 - CLONE_NEWIPC:    ...
 *                 - CLONE_NEWNET:    ...
 *                 - CLONE_NEWNS:     Unshare the mount namespace
 *                 - CLONE_NEWPID:    Unshare the PID namespace
 *                 - CLONE_NEWUSER:   ...
 *                 - CLONE_NEWUTS:    ...
 *                 - CLONE_SYSVSEM:   ...
 *                 - CLONE_VM:        Unshare the current VM (KOS extension)
 *                 - CLONE_SIGHAND:   Unshare signal handlers (KOS extension) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_unshare)(int flags);
/* >> sched_getcpu(3)
 * Returns the number of the CPU for the calling thread.
 * Note that due to unforseeable scheduling conditions, this may change at any
 * moment, even before this function returns, or before the caller was able to
 * act on its return value. For that reason, this function must only be taken
 * as a hint */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sched_getcpu)(void);
/* >> setns(2)
 * With `FD' referring to a namespace, reassociate the calling thread with that namespace.
 * For this purpose, `FD' was opened for one of the files in `/proc/[pid]/ns/'
 * @param: nstype: The type of namespace to re-associate (either 0 to allow any
 *                 type of namespace, or one of `CLONE_NEWCGROUP', `CLONE_NEWIPC',
 *                `CLONE_NEWNET', `CLONE_NEWNS', `CLONE_NEWPID', `CLONE_NEWUSER',
 *                `CLONE_NEWUTS') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setns)(fd_t fd, int nstype);
/* Exits the current thread by invoking the SYS_exit system call,
 * after performing some additional cleanup not done by the kernel.
 * Assuming that the calling thread was constructed by `clone()',
 * calling this function has the same effect as returning `EXIT_CODE'
 * from `clone()'s `FN' callback */
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBCCALL libc_exit_thread)(int exit_code);

DECL_END

#endif /* !GUARD_LIBC_USER_BITS_SCHED_H */
