/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SCHED_C
#define GUARD_LIBC_USER_SCHED_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <syscall.h>

#include "sched.h"

DECL_BEGIN

/* Clone must be implemented in assembly! */
/*[[[skip:libc_clone]]]*/

/*[[[head:libd_clone,hash:CRC-32=0xcc621642]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.sched.access") NONNULL((1)) pid_t
NOTHROW_NCX(VLIBDCALL libd_clone)(int (LIBDCALL *fn)(void *arg),
                                  void *child_stack,
                                  int flags,
                                  void *arg,
                                  ...)
/*[[[body:libd_clone]]]*/
/*AUTO*/{
	(void)fn;
	(void)child_stack;
	(void)flags;
	(void)arg;
	CRT_UNIMPLEMENTEDF("clone(%p, %p, %x, %p, ...)", fn, child_stack, flags, arg); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_clone]]]*/

/*[[[head:libc_unshare,hash:CRC-32=0x65b4e0cc]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.utility") int
NOTHROW_NCX(LIBCCALL libc_unshare)(__STDC_INT_AS_UINT_T flags)
/*[[[body:libc_unshare]]]*/
{
	errno_t result;
	result = sys_unshare((syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_unshare]]]*/

/*[[[head:libc_sched_getcpu,hash:CRC-32=0x13d68b72]]]*/
/* >> sched_getcpu(3)
 * Returns the number of the CPU for the calling thread.
 * Note that due to unforeseeable scheduling conditions, this may change at any
 * moment, even before this function returns, or before the caller was able  to
 * act on its return value. For that  reason, this function must only be  taken
 * as a hint */
INTERN ATTR_SECTION(".text.crt.sched.utility") __STDC_INT_AS_UINT_T
NOTHROW_NCX(LIBCCALL libc_sched_getcpu)(void)
/*[[[body:libc_sched_getcpu]]]*/
{
	errno_t error;
	uint32_t res;
	/* XXX: Figure out how linux implements `struct getcpu_cache' */
	error = sys_getcpu(&res, NULL, NULL);
	if (E_ISERR(error))
		return libc_seterrno_neg(error);
	return (int)(unsigned int)res;
}
/*[[[end:libc_sched_getcpu]]]*/

/*[[[head:libc_setns,hash:CRC-32=0xf86d6261]]]*/
/* >> setns(2)
 * With `fd' referring to a namespace, reassociate the calling thread with that namespace.
 * For  this  purpose,  `fd'  was  opened  for  one  of  the  files  in  `/proc/[pid]/ns/'
 * @param: nstype: The  type of namespace  to re-associate (either  0 to allow any
 *                 type of namespace, or one of `CLONE_NEWCGROUP', `CLONE_NEWIPC',
 *                `CLONE_NEWNET', `CLONE_NEWNS', `CLONE_NEWPID', `CLONE_NEWUSER',
 *                `CLONE_NEWUTS') */
INTERN ATTR_SECTION(".text.crt.sched.utility") int
NOTHROW_NCX(LIBCCALL libc_setns)(fd_t fd,
                                 __STDC_INT_AS_UINT_T nstype)
/*[[[body:libc_setns]]]*/
{
	errno_t result;
	result = sys_setns(fd,
	                   (syscall_ulong_t)(unsigned int)nstype);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setns]]]*/

/*[[[head:libc_exit_thread,hash:CRC-32=0x4bb38125]]]*/
/* Exits  the current  thread by  invoking the  SYS_exit system call,
 * after performing some additional cleanup  not done by the  kernel.
 * Assuming that  the calling  thread was  constructed by  `clone()',
 * calling this function has the same effect as returning `EXIT_CODE'
 * from `clone()'s `FN' callback */
INTERN ATTR_SECTION(".text.crt.sched.access") ATTR_NORETURN void
NOTHROW_NCX(LIBCCALL libc_exit_thread)(int exit_code)
/*[[[body:libc_exit_thread]]]*/
{
	/* NOTE: The TLS segment, and stack are explicitly defined when calling the clone() function.
	 *       Seeing this, we'd be wrong  to assume and free a  DL-based TLS segment, or  munmap()
	 *       the current stack, seeing  how we cannot  know if our  current thread actually  owns
	 *       them.
	 *       Given these facts,  it would  seem that  this function is  fairly pointless,  as we  can
	 *       only get here if our thread  still has a stack, in  which case it would seem  improbable
	 *       that anyone else owns that stack. And given the fact that in order to use libc properly,
	 *       one has to make  use of DL-based TLS  segments, it would also  seem improbable that  the
	 *       current thread isn't (or wasn't) using a DL-based TLS segment.
	 *       Oh well...
	 */
	/* Don't let yourself be fooled:
	 *   - sys_exit()       terminated the calling _thread_
	 *   - sys_exit_group() terminated the calling _process_ */
	sys_exit((syscall_ulong_t)(unsigned int)exit_code);
}
/*[[[end:libc_exit_thread]]]*/

/*[[[head:libc_sched_setparam,hash:CRC-32=0x50223df]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_sched_setparam)(pid_t pid,
                                          struct sched_param const *param)
/*[[[body:libc_sched_setparam]]]*/
{
	errno_t result;
	result = sys_sched_setparam(pid, param);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_setparam]]]*/

/*[[[head:libc_sched_getparam,hash:CRC-32=0x47e133e7]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_sched_getparam)(pid_t pid,
                                          struct sched_param *param)
/*[[[body:libc_sched_getparam]]]*/
{
	errno_t result;
	result = sys_sched_getparam(pid, param);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_getparam]]]*/

/*[[[head:libc_sched_setscheduler,hash:CRC-32=0x59fa5d37]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") ATTR_IN(3) int
NOTHROW_NCX(LIBCCALL libc_sched_setscheduler)(pid_t pid,
                                              int policy,
                                              struct sched_param const *param)
/*[[[body:libc_sched_setscheduler]]]*/
{
	errno_t result;
	result = sys_sched_setscheduler(pid,
	                                (syscall_ulong_t)(unsigned int)policy,
	                                param);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_setscheduler]]]*/

/*[[[head:libc_sched_getscheduler,hash:CRC-32=0xef7d02fd]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_sched_getscheduler)(pid_t pid)
/*[[[body:libc_sched_getscheduler]]]*/
{
	syscall_slong_t result;
	result = sys_sched_getscheduler(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_getscheduler]]]*/

/*[[[head:libc_sched_yield,hash:CRC-32=0xba0e50a9]]]*/
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
INTERN ATTR_SECTION(".text.crt.sched.thread") int
NOTHROW(LIBCCALL libc_sched_yield)(void)
/*[[[body:libc_sched_yield]]]*/
{
	errno_t result;
	result = sys_sched_yield();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_yield]]]*/

/*[[[head:libc_sched_get_priority_max,hash:CRC-32=0x96f1b2c8]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_sched_get_priority_max)(__STDC_INT_AS_UINT_T algorithm)
/*[[[body:libc_sched_get_priority_max]]]*/
{
	syscall_slong_t result;
	result = sys_sched_get_priority_max((syscall_ulong_t)(unsigned int)algorithm);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_get_priority_max]]]*/

/*[[[head:libc_sched_get_priority_min,hash:CRC-32=0x657c3dde]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_sched_get_priority_min)(__STDC_INT_AS_UINT_T algorithm)
/*[[[body:libc_sched_get_priority_min]]]*/
{
	syscall_slong_t result;
	result = sys_sched_get_priority_min((syscall_ulong_t)(unsigned int)algorithm);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_get_priority_min]]]*/

/*[[[head:libc_sched_setaffinity,hash:CRC-32=0x6bf613dd]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") ATTR_IN_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_sched_setaffinity)(pid_t pid,
                                             size_t cpusetsize,
                                             cpu_set_t const *cpuset)
/*[[[body:libc_sched_setaffinity]]]*/
{
	errno_t result;
	result = sys_sched_setaffinity(pid, cpusetsize, cpuset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_setaffinity]]]*/

/*[[[head:libc_sched_getaffinity,hash:CRC-32=0x863f71a4]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") ATTR_OUT_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_sched_getaffinity)(pid_t pid,
                                             size_t cpusetsize,
                                             cpu_set_t *cpuset)
/*[[[body:libc_sched_getaffinity]]]*/
{
	errno_t result;
	result = sys_sched_getaffinity(pid, cpusetsize, cpuset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_getaffinity]]]*/

/*[[[head:libc_sched_rr_get_interval,hash:CRC-32=0xf2f92ff]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_sched_rr_get_interval)(pid_t pid,
                                                 struct timespec *tms)
/*[[[body:libc_sched_rr_get_interval]]]*/
{
	errno_t result;
	result = sys_sched_rr_get_interval(pid, tms);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_rr_get_interval]]]*/

/*[[[head:libc_sched_rr_get_interval64,hash:CRC-32=0x58524d0e]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_sched_rr_get_interval64, libc_sched_rr_get_interval);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.sched.param") ATTR_OUT_OPT(2) int
NOTHROW_NCX(LIBCCALL libc_sched_rr_get_interval64)(pid_t pid,
                                                   struct timespec64 *tms)
/*[[[body:libc_sched_rr_get_interval64]]]*/
{
	errno_t result;
#ifdef SYS_sched_rr_get_interval64
	result = sys_sched_rr_get_interval64(pid, tms);
#elif defined(SYS_sched_rr_get_interval_time64)
	result = sys_sched_rr_get_interval_time64(pid, tms);
#else /* ... */
#error "No way to implement `sched_rr_get_interval64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_sched_rr_get_interval64]]]*/



/*[[[start:exports,hash:CRC-32=0x8c9c6d34]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$__clone, libd_clone);
DEFINE_PUBLIC_ALIAS(DOS$clone, libd_clone);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(unshare, libc_unshare);
DEFINE_PUBLIC_ALIAS(sched_getcpu, libc_sched_getcpu);
DEFINE_PUBLIC_ALIAS(setns, libc_setns);
DEFINE_PUBLIC_ALIAS(exit_thread, libc_exit_thread);
DEFINE_PUBLIC_ALIAS(__sched_setparam, libc_sched_setparam);
DEFINE_PUBLIC_ALIAS(__libc_sched_setparam, libc_sched_setparam);
DEFINE_PUBLIC_ALIAS(sched_setparam, libc_sched_setparam);
DEFINE_PUBLIC_ALIAS(__sched_getparam, libc_sched_getparam);
DEFINE_PUBLIC_ALIAS(__libc_sched_getparam, libc_sched_getparam);
DEFINE_PUBLIC_ALIAS(sched_getparam, libc_sched_getparam);
DEFINE_PUBLIC_ALIAS(__sched_setscheduler, libc_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(__libc_sched_setscheduler, libc_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(sched_setscheduler, libc_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(__sched_getscheduler, libc_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(__libc_sched_getscheduler, libc_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(sched_getscheduler, libc_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(thrd_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(pthread_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(__sched_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(__libc_sched_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(thr_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(sched_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(__sched_get_priority_max, libc_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(__libc_sched_get_priority_max, libc_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(sched_get_priority_max, libc_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(__sched_get_priority_min, libc_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(__libc_sched_get_priority_min, libc_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(sched_get_priority_min, libc_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(sched_setaffinity, libc_sched_setaffinity);
DEFINE_PUBLIC_ALIAS(sched_getaffinity, libc_sched_getaffinity);
DEFINE_PUBLIC_ALIAS(__sched_rr_get_interval, libc_sched_rr_get_interval);
DEFINE_PUBLIC_ALIAS(__libc_sched_rr_get_interval, libc_sched_rr_get_interval);
DEFINE_PUBLIC_ALIAS(sched_rr_get_interval, libc_sched_rr_get_interval);
DEFINE_PUBLIC_ALIAS(sched_rr_get_interval64, libc_sched_rr_get_interval64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SCHED_C */
