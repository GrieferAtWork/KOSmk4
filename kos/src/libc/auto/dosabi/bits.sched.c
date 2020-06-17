/* HASH CRC-32:0xd17ad2e0 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_BITS_SCHED_C
#define GUARD_LIBC_AUTO_DOSABI_BITS_SCHED_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/bits.sched.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.sched.access") NONNULL((1)) pid_t
NOTHROW_NCX(VLIBDCALL libd_clone)(__clone_func_t fn,
                                  void *child_stack,
                                  int flags,
                                  void *arg,
                                  ...) {
	va_list args;
	pid_t v0_pid_t;
	void *v1;
	pid_t v2_pid_t;
	va_start(args, arg);
	v0_pid_t = va_arg(args, pid_t);
	v1       = va_arg(args, void *);
	v2_pid_t = va_arg(args, pid_t);
	va_end(args);
	return libc_clone(fn, child_stack, flags, arg, v0_pid_t, v1, v2_pid_t);
}
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
INTERN ATTR_SECTION(".text.crt.dos.sched.utility") int
NOTHROW_NCX(LIBDCALL libd_unshare)(int flags) {
	return libc_unshare(flags);
}
/* >> setns(2)
 * With `FD' referring to a namespace, reassociate the calling thread with that namespace.
 * For this purpose, `FD' was opened for one of the files in `/proc/[pid]/ns/'
 * @param: nstype: The type of namespace to re-associate (either 0 to allow any
 *                 type of namespace, or one of `CLONE_NEWCGROUP', `CLONE_NEWIPC',
 *                `CLONE_NEWNET', `CLONE_NEWNS', `CLONE_NEWPID', `CLONE_NEWUSER',
 *                `CLONE_NEWUTS') */
INTERN ATTR_SECTION(".text.crt.dos.sched.utility") int
NOTHROW_NCX(LIBDCALL libd_setns)(fd_t fd,
                                 int nstype) {
	return libc_setns(fd, nstype);
}
/* Exits the current thread by invoking the SYS_exit system call,
 * after performing some additional cleanup not done by the kernel.
 * Assuming that the calling thread was constructed by `clone()',
 * calling this function has the same effect as returning `EXIT_CODE'
 * from `clone()'s `FN' callback */
INTERN ATTR_SECTION(".text.crt.dos.sched.access") ATTR_NORETURN void
NOTHROW_NCX(LIBDCALL libd_exit_thread)(int exit_code) {
	libc_exit_thread(exit_code);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__clone, libd_clone);
DEFINE_PUBLIC_ALIAS(DOS$clone, libd_clone);
DEFINE_PUBLIC_ALIAS(DOS$unshare, libd_unshare);
DEFINE_PUBLIC_ALIAS(DOS$setns, libd_setns);
DEFINE_PUBLIC_ALIAS(DOS$exit_thread, libd_exit_thread);

#endif /* !GUARD_LIBC_AUTO_DOSABI_BITS_SCHED_C */
