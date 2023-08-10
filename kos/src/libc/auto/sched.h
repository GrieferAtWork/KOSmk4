/* HASH CRC-32:0xef8e9deb */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_SCHED_H
#define GUARD_LIBC_AUTO_SCHED_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sched.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unshare(2)
 * Unshare certain components of the calling thread that may be shared with other
 * threads or  processes, such  as the  filesystem, or  opened file  descriptors.
 * When  being unshared, the calling thread's descriptor for a specific component
 * is  replaced with a copy of its previous contents at that moment in time, with
 * the notable exception of  certain KOS-specific extensions, where  specifically
 * marked data will be deleted (s.a. `O_CLOFORK')
 * The  behavior and  meaning of individual  bits in `flags'  matches their meaning
 * when passed to `clone()', except that for certain flags the meaning is reversed.
 * For example: Passing `CLONE_FILES' to `clone(2)' will cause handles to be shared,
 *              but  passing it to  `unshare(2)' will cause  handles to be unshared.
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
INTDEF int NOTHROW_NCX(LIBDCALL libd_unshare)(__STDC_INT_AS_UINT_T flags);
/* >> setns(2)
 * With `fd' referring to a namespace, reassociate the calling thread with that namespace.
 * For  this  purpose,  `fd'  was  opened  for  one  of  the  files  in  `/proc/[pid]/ns/'
 * @param: nstype: The  type of namespace  to re-associate (either  0 to allow any
 *                 type of namespace, or one of `CLONE_NEWCGROUP', `CLONE_NEWIPC',
 *                `CLONE_NEWNET', `CLONE_NEWNS', `CLONE_NEWPID', `CLONE_NEWUSER',
 *                `CLONE_NEWUTS') */
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_setns)(fd_t fd, __STDC_INT_AS_UINT_T nstype);
/* Exits  the current  thread by  invoking the  SYS_exit system call,
 * after performing some additional cleanup  not done by the  kernel.
 * Assuming that  the calling  thread was  constructed by  `clone()',
 * calling this function has the same effect as returning `EXIT_CODE'
 * from `clone()'s `FN' callback */
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBDCALL libd_exit_thread)(int exit_code);
INTDEF ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_sched_setparam)(pid_t pid, struct sched_param const *param);
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_sched_getparam)(pid_t pid, struct sched_param *param);
INTDEF ATTR_IN(3) int NOTHROW_NCX(LIBDCALL libd_sched_setscheduler)(pid_t pid, int policy, struct sched_param const *param);
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_sched_getscheduler)(pid_t pid);
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_sched_get_priority_max)(__STDC_INT_AS_UINT_T algorithm);
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_sched_get_priority_min)(__STDC_INT_AS_UINT_T algorithm);
INTDEF ATTR_IN_OPT(3) int NOTHROW_NCX(LIBDCALL libd_sched_setaffinity)(pid_t pid, size_t cpusetsize, cpu_set_t const *cpuset);
INTDEF ATTR_OUT_OPT(3) int NOTHROW_NCX(LIBDCALL libd_sched_getaffinity)(pid_t pid, size_t cpusetsize, cpu_set_t *cpuset);
INTDEF ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd_sched_rr_get_interval)(pid_t pid, struct timespec *tms);
INTDEF ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd_sched_rr_get_interval64)(pid_t pid, struct timespec64 *tms);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SCHED_H */
