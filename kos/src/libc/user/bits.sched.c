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
#ifndef GUARD_LIBC_USER_BITS_SCHED_C
#define GUARD_LIBC_USER_BITS_SCHED_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>
#include <kos/thread.h>
#include <sys/syscall.h>

#include <dlfcn.h>

#include "bits.sched.h"

DECL_BEGIN

/*[[[start:implementation]]]*/

/* Clone must be implemented in assembly! */
/*[[[skip:clone]]]*/

/*[[[head:unshare,hash:CRC-32=0x1fac0a45]]]*/
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
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.utility.unshare") int
NOTHROW_NCX(LIBCCALL libc_unshare)(int flags)
/*[[[body:unshare]]]*/
{
	errno_t result;
	result = sys_unshare((syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:unshare]]]*/

/*[[[head:sched_getcpu,hash:CRC-32=0x3f296be5]]]*/
/* >> sched_getcpu(3)
 * Returns the number of the CPU for the calling thread.
 * Note that due to unforeseeable scheduling conditions, this may change at any
 * moment, even before this function returns, or before the caller was able to
 * act on its return value. For that reason, this function must only be taken
 * as a hint */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.utility.sched_getcpu") int
NOTHROW_NCX(LIBCCALL libc_sched_getcpu)(void)
/*[[[body:sched_getcpu]]]*/
{
	errno_t error;
	uint32_t res;
	/* XXX: Figure out how linux implements `struct getcpu_cache' */
	error = sys_getcpu(&res, NULL, NULL);
	if (E_ISERR(error)) {
		libc_seterrno(-error);
		return -1;
	}
	return (int)(unsigned int)res;
}
/*[[[end:sched_getcpu]]]*/

/*[[[head:setns,hash:CRC-32=0x2ad1758]]]*/
/* >> setns(2)
 * With `FD' referring to a namespace, reassociate the calling thread with that namespace.
 * For this purpose, `FD' was opened for one of the files in `/proc/[pid]/ns/'
 * @param: nstype: The type of namespace to re-associate (either 0 to allow any
 *                 type of namespace, or one of `CLONE_NEWCGROUP', `CLONE_NEWIPC',
 *                `CLONE_NEWNET', `CLONE_NEWNS', `CLONE_NEWPID', `CLONE_NEWUSER',
 *                `CLONE_NEWUTS') */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.utility.setns") int
NOTHROW_NCX(LIBCCALL libc_setns)(fd_t fd,
                                 int nstype)
/*[[[body:setns]]]*/
{
	errno_t result;
	result = sys_setns(fd,
	                   (syscall_ulong_t)(unsigned int)nstype);
	return libc_seterrno_syserr(result);
}
/*[[[end:setns]]]*/

/*[[[head:exit_thread,hash:CRC-32=0x7d2ac39a]]]*/
/* Exits the current thread by invoking the SYS_exit system call,
 * after performing some additional cleanup not done by the kernel.
 * Assuming that the calling thread was constructed by `clone()',
 * calling this function has the same effect as returning `EXIT_CODE'
 * from `clone()'s `FN' callback */
INTERN ATTR_NORETURN
ATTR_WEAK ATTR_SECTION(".text.crt.sched.access.exit_thread") void
NOTHROW_NCX(LIBCCALL libc_exit_thread)(int exit_code)
/*[[[body:exit_thread]]]*/
{
	/* NOTE: The TLS segment, and stack are explicitly defined when calling the clone() function.
	 *       Seeing this, we'd be wrong to assume and free a DL-based TLS segment, or munmap()
	 *       the current stack, seeing how we cannot know if our current thread actually owns
	 *       them.
	 *       Given these facts, it would seem that this function is fairly pointless, as we can
	 *       only get here if our thread still has a stack, in which case it would see improbable
	 *       that anyone else owns that stack. And given the fact that in order to use libc properly,
	 *       one has to make use of DL-based TLS segments, it would also seem improbable that the
	 *       current thread isn't (or wasn't) using a DL-based TLS segment.
	 *       Oh well...
	 */
	/* Don't let yourself be fooled:
	 *   - sys_exit()       terminated the calling _thread_
	 *   - sys_exit_group() terminated the calling _process_ */
	sys_exit((syscall_ulong_t)(unsigned int)exit_code);
}
/*[[[end:exit_thread]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x79af6541]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(unshare, libc_unshare);
DEFINE_PUBLIC_WEAK_ALIAS(sched_getcpu, libc_sched_getcpu);
DEFINE_PUBLIC_WEAK_ALIAS(setns, libc_setns);
DEFINE_PUBLIC_WEAK_ALIAS(exit_thread, libc_exit_thread);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_BITS_SCHED_C */
