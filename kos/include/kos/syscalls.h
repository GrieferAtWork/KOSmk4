/* HASH CRC-32:0xc844ebcb */
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
#ifndef _KOS_SYSCALLS_H
#define _KOS_SYSCALLS_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <bits/types.h>
#include <bits/timespec.h>
#include <bits/timeval.h>
#include <bits/utimebuf.h>
#include <bits/sigaction.h>
#include <bits/itimerval.h>
#include <kos/bits/except-handler.h>
#include <kos/asm/syscalls.h>
#include <hybrid/host.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("dirent")
#pragma push_macro("stat")
#pragma push_macro("timeb")
#pragma push_macro("timezone")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef dirent
#undef stat
#undef timeb
#undef timezone

#ifndef ____idtype_t_defined
#define ____idtype_t_defined 1
typedef int __idtype_t;
#endif /* !____idtype_t_defined */

#ifndef __CDECLARE_SC
#if 1 /* TODO: cancellation_point-system calls aren't nothrow! - All others are. */
#define __CDECLARE_SC(attr, Treturn, name, param, args)  __CDECLARE(attr,Treturn,,sys_##name,param,args)
#define __CDECLARE_VOID_SC(attr, name, param, args)      __CDECLARE_VOID(attr,,sys_##name,param,args)
#else
#define __CDECLARE_SC(attr, Treturn, name, param, args)  __CDECLARE(attr,Treturn,__NOTHROW,sys_##name,param,args)
#define __CDECLARE_VOID_SC(attr, name, param, args)      __CDECLARE_VOID(attr,__NOTHROW,sys_##name,param,args)
#endif
#define __CDECLARE_XSC(attr, Treturn, name, param, args) __CDECLARE(attr,Treturn,,sys_X##name,param,args)
#define __CDECLARE_VOID_XSC(attr, name, param, args)     __CDECLARE_VOID(attr,,sys_X##name,param,args)
#define __PRIVATE_CRT_HAVE_PLACEHOLDER_1         ,
#define __PRIVATE_CRT_HAVE_ARG_IMPL(x, val, ...) val
#define __PRIVATE_CRT_HAVE_ARG(x)  __PRIVATE_CRT_HAVE_ARG_IMPL x
#define __PRIVATE_CRT_HAVE3(...)   __PRIVATE_CRT_HAVE_ARG((__VA_ARGS__ 1,0))
#define __PRIVATE_CRT_HAVE2(x)     __PRIVATE_CRT_HAVE3(__PRIVATE_CRT_HAVE_PLACEHOLDER_##x)
#define __PRIVATE_CRT_ISDEFINED(x) __PRIVATE_CRT_HAVE2(x)
#define __CRT_HAVE_SC(name)        __PRIVATE_CRT_ISDEFINED(__CRT_HAVE_sys_##name)
#define __CRT_HAVE_XSC(name)       __PRIVATE_CRT_ISDEFINED(__CRT_HAVE_sys_X##name)
#endif /* !__CDECLARE_SC */

/* Forward-declare structure types */
struct __cpu_set_struct;
struct __fd_set_struct;
struct __itimerspec32;
struct __itimerspec64;
struct __itimerval32;
struct __itimerval64;
struct __siginfo_struct;
struct __sigset_struct;
struct __statfs32;
struct __timespec32;
struct __timespec64;
struct __timeval32;
struct __timeval64;
struct __utimbuf32;
struct debugtrap_reason;
struct dirent;
struct epoll_event;
struct exception_data;
struct file_handle;
struct fpustate;
struct getcpu_cache;
struct iovec;
struct lfutexexpr;
struct library_listdef;
struct linux64_stat32;
struct linux_dirent;
struct linux_dirent64;
struct linux_oldolduname;
struct linux_oldstat;
struct linux_olduname;
struct linux_stat32;
struct linux_stat64;
struct mmsghdr;
struct msghdr;
struct old_linux_dirent;
struct pollfd;
struct rlimit;
struct rlimit64;
struct rpc_syscall_info;
struct rusage;
struct sched_param;
struct sigaction;
struct sigaltstack;
struct sigevent;
struct sockaddr;
struct stat;
struct statfs64;
struct sysinfo;
struct termios;
struct timeb;
struct timezone;
struct tms;
struct ucpustate;
struct ustat;
struct utimbuf64;
struct utsname;
struct winsize;



#if __CRT_HAVE_SC(_llseek)
#ifndef __sys__llseek_defined
#define __sys__llseek_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,_llseek,(__fd_t __fd, __int64_t __offset, __uint64_t *__result, __syscall_ulong_t __whence),(__fd,__offset,__result,__whence))
#else /* ... */
#undef __sys__llseek_defined
#endif /* !... */
#endif /* !__sys__llseek_defined */
#endif /* sys__llseek... */
#if __CRT_HAVE_SC(accept4)
#ifndef __sys_accept4_defined
#define __sys_accept4_defined 1
__CDECLARE_SC(,__fd_t,accept4,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len, __syscall_ulong_t __flags),(__sockfd,__addr,__addr_len,__flags))
#endif /* !__sys_accept4_defined */
#endif /* sys_accept4... */
#if __CRT_HAVE_SC(access)
#ifndef __sys_access_defined
#define __sys_access_defined 1
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
__CDECLARE_SC(,__errno_t,access,(char const *__filename, __syscall_ulong_t __type),(__filename,__type))
#endif /* !__sys_access_defined */
#endif /* sys_access... */
#if __CRT_HAVE_SC(acct)
#ifndef __sys_acct_defined
#define __sys_acct_defined 1
__CDECLARE_SC(,__errno_t,acct,(char const *__filename),(__filename))
#endif /* !__sys_acct_defined */
#endif /* sys_acct... */
#if __CRT_HAVE_SC(alarm)
#ifndef __sys_alarm_defined
#define __sys_alarm_defined 1
__CDECLARE_SC(,__syscall_ulong_t,alarm,(__syscall_ulong_t __seconds),(__seconds))
#endif /* !__sys_alarm_defined */
#endif /* sys_alarm... */
#if __CRT_HAVE_SC(bind)
#ifndef __sys_bind_defined
#define __sys_bind_defined 1
__CDECLARE_SC(,__errno_t,bind,(__fd_t __sockfd, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#endif /* !__sys_bind_defined */
#endif /* sys_bind... */
#if __CRT_HAVE_SC(brk)
#ifndef __sys_brk_defined
#define __sys_brk_defined 1
__CDECLARE_SC(,__errno_t,brk,(void *__addr),(__addr))
#endif /* !__sys_brk_defined */
#endif /* sys_brk... */
#if __CRT_HAVE_SC(chdir)
#ifndef __sys_chdir_defined
#define __sys_chdir_defined 1
__CDECLARE_SC(,__errno_t,chdir,(char const *__path),(__path))
#endif /* !__sys_chdir_defined */
#endif /* sys_chdir... */
#if __CRT_HAVE_SC(chmod)
#ifndef __sys_chmod_defined
#define __sys_chmod_defined 1
__CDECLARE_SC(,__errno_t,chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#endif /* !__sys_chmod_defined */
#endif /* sys_chmod... */
#if __CRT_HAVE_SC(chown)
#ifndef __sys_chown_defined
#define __sys_chown_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,chown,(char const *__filename, __uint16_t __owner, __uint16_t __group),(__filename,__owner,__group))
#else /* #elif defined(__x86_64__) */
__CDECLARE_SC(,__errno_t,chown,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#endif /* ... */
#endif /* !__sys_chown_defined */
#endif /* sys_chown... */
#if __CRT_HAVE_SC(chown32)
#ifndef __sys_chown32_defined
#define __sys_chown32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,chown32,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#else /* ... */
#undef __sys_chown32_defined
#endif /* !... */
#endif /* !__sys_chown32_defined */
#endif /* sys_chown32... */
#if __CRT_HAVE_SC(chroot)
#ifndef __sys_chroot_defined
#define __sys_chroot_defined 1
__CDECLARE_SC(,__errno_t,chroot,(char const *__path),(__path))
#endif /* !__sys_chroot_defined */
#endif /* sys_chroot... */
#if __CRT_HAVE_SC(clock_getres)
#ifndef __sys_clock_getres_defined
#define __sys_clock_getres_defined 1
__CDECLARE_SC(,__errno_t,clock_getres,(__clockid_t __clock_id, struct __timespec32 *__res),(__clock_id,__res))
#endif /* !__sys_clock_getres_defined */
#endif /* sys_clock_getres... */
#if __CRT_HAVE_SC(clock_getres64)
#ifndef __sys_clock_getres64_defined
#define __sys_clock_getres64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,clock_getres64,(__clockid_t __clock_id, struct __timespec64 *__res),(__clock_id,__res))
#else /* ... */
#undef __sys_clock_getres64_defined
#endif /* !... */
#endif /* !__sys_clock_getres64_defined */
#endif /* sys_clock_getres64... */
#if __CRT_HAVE_SC(clock_gettime)
#ifndef __sys_clock_gettime_defined
#define __sys_clock_gettime_defined 1
__CDECLARE_SC(,__errno_t,clock_gettime,(__clockid_t __clock_id, struct __timespec32 *__tp),(__clock_id,__tp))
#endif /* !__sys_clock_gettime_defined */
#endif /* sys_clock_gettime... */
#if __CRT_HAVE_SC(clock_gettime64)
#ifndef __sys_clock_gettime64_defined
#define __sys_clock_gettime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,clock_gettime64,(__clockid_t __clock_id, struct __timespec64 *__tp),(__clock_id,__tp))
#else /* ... */
#undef __sys_clock_gettime64_defined
#endif /* !... */
#endif /* !__sys_clock_gettime64_defined */
#endif /* sys_clock_gettime64... */
#if __CRT_HAVE_SC(clock_nanosleep)
#ifndef __sys_clock_nanosleep_defined
#define __sys_clock_nanosleep_defined 1
__CDECLARE_SC(,__errno_t,clock_nanosleep,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct __timespec32 const *__requested_time, struct __timespec32 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* !__sys_clock_nanosleep_defined */
#endif /* sys_clock_nanosleep... */
#if __CRT_HAVE_SC(clock_nanosleep64)
#ifndef __sys_clock_nanosleep64_defined
#define __sys_clock_nanosleep64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,clock_nanosleep64,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct __timespec64 const *__requested_time, struct __timespec64 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#else /* ... */
#undef __sys_clock_nanosleep64_defined
#endif /* !... */
#endif /* !__sys_clock_nanosleep64_defined */
#endif /* sys_clock_nanosleep64... */
#if __CRT_HAVE_SC(clock_settime)
#ifndef __sys_clock_settime_defined
#define __sys_clock_settime_defined 1
__CDECLARE_SC(,__errno_t,clock_settime,(__clockid_t __clock_id, struct __timespec32 const *__tp),(__clock_id,__tp))
#endif /* !__sys_clock_settime_defined */
#endif /* sys_clock_settime... */
#if __CRT_HAVE_SC(clock_settime64)
#ifndef __sys_clock_settime64_defined
#define __sys_clock_settime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,clock_settime64,(__clockid_t __clock_id, struct __timespec64 const *__tp),(__clock_id,__tp))
#else /* ... */
#undef __sys_clock_settime64_defined
#endif /* !... */
#endif /* !__sys_clock_settime64_defined */
#endif /* sys_clock_settime64... */
#if __CRT_HAVE_SC(clone)
#ifndef __sys_clone_defined
#define __sys_clone_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __uintptr_t __newtls, __pid_t *__ctid),(__flags,__child_stack,__ptid,__newtls,__ctid))
#else /* #elif defined(__x86_64__) */
__CDECLARE_SC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __pid_t *__ctid, __uintptr_t __newtls),(__flags,__child_stack,__ptid,__ctid,__newtls))
#endif /* ... */
#endif /* !__sys_clone_defined */
#endif /* sys_clone... */
#if __CRT_HAVE_SC(close)
#ifndef __sys_close_defined
#define __sys_close_defined 1
/* Close a given file descriptor/handle `FD' */
__CDECLARE_SC(,__errno_t,close,(__fd_t __fd),(__fd))
#endif /* !__sys_close_defined */
#endif /* sys_close... */
#if __CRT_HAVE_SC(connect)
#ifndef __sys_connect_defined
#define __sys_connect_defined 1
__CDECLARE_SC(,__errno_t,connect,(__fd_t __sockfd, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#endif /* !__sys_connect_defined */
#endif /* sys_connect... */
#if __CRT_HAVE_SC(coredump)
#ifndef __sys_coredump_defined
#define __sys_coredump_defined 1
/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
__CDECLARE_SC(,__errno_t,coredump,(struct ucpustate const *__curr_state, struct ucpustate const *__orig_state, void const *const *__traceback_vector, __size_t __traceback_length, struct exception_data const *__exception, __syscall_ulong_t __unwind_error),(__curr_state,__orig_state,__traceback_vector,__traceback_length,__exception,__unwind_error))
#endif /* !__sys_coredump_defined */
#endif /* sys_coredump... */
#if __CRT_HAVE_SC(creat)
#ifndef __sys_creat_defined
#define __sys_creat_defined 1
__CDECLARE_SC(,__fd_t,creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#endif /* !__sys_creat_defined */
#endif /* sys_creat... */
#if __CRT_HAVE_SC(debugtrap)
#ifndef __sys_debugtrap_defined
#define __sys_debugtrap_defined 1
/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
__CDECLARE_SC(,__errno_t,debugtrap,(struct ucpustate const *__state, struct debugtrap_reason const *__reason),(__state,__reason))
#endif /* !__sys_debugtrap_defined */
#endif /* sys_debugtrap... */
#if __CRT_HAVE_SC(detach)
#ifndef __sys_detach_defined
#define __sys_detach_defined 1
/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
__CDECLARE_SC(,__errno_t,detach,(__pid_t __pid),(__pid))
#endif /* !__sys_detach_defined */
#endif /* sys_detach... */
#if __CRT_HAVE_SC(dup)
#ifndef __sys_dup_defined
#define __sys_dup_defined 1
__CDECLARE_SC(,__fd_t,dup,(__fd_t __fd),(__fd))
#endif /* !__sys_dup_defined */
#endif /* sys_dup... */
#if __CRT_HAVE_SC(dup2)
#ifndef __sys_dup2_defined
#define __sys_dup2_defined 1
__CDECLARE_SC(,__fd_t,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#endif /* !__sys_dup2_defined */
#endif /* sys_dup2... */
#if __CRT_HAVE_SC(dup3)
#ifndef __sys_dup3_defined
#define __sys_dup3_defined 1
/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
__CDECLARE_SC(,__fd_t,dup3,(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags),(__oldfd,__newfd,__flags))
#endif /* !__sys_dup3_defined */
#endif /* sys_dup3... */
#if __CRT_HAVE_SC(epoll_create)
#ifndef __sys_epoll_create_defined
#define __sys_epoll_create_defined 1
__CDECLARE_SC(,__fd_t,epoll_create,(__syscall_ulong_t __size),(__size))
#endif /* !__sys_epoll_create_defined */
#endif /* sys_epoll_create... */
#if __CRT_HAVE_SC(epoll_create1)
#ifndef __sys_epoll_create1_defined
#define __sys_epoll_create1_defined 1
__CDECLARE_SC(,__fd_t,epoll_create1,(__syscall_ulong_t __flags),(__flags))
#endif /* !__sys_epoll_create1_defined */
#endif /* sys_epoll_create1... */
#if __CRT_HAVE_SC(epoll_ctl)
#ifndef __sys_epoll_ctl_defined
#define __sys_epoll_ctl_defined 1
__CDECLARE_SC(,__errno_t,epoll_ctl,(__fd_t __epfd, __syscall_ulong_t __op, __fd_t __fd, struct epoll_event *__event),(__epfd,__op,__fd,__event))
#endif /* !__sys_epoll_ctl_defined */
#endif /* sys_epoll_ctl... */
#if __CRT_HAVE_SC(epoll_ctl_old)
#ifndef __sys_epoll_ctl_old_defined
#define __sys_epoll_ctl_old_defined 1
#ifdef __x86_64__
__CDECLARE_SC(,__errno_t,epoll_ctl_old,(__fd_t __epfd, __syscall_ulong_t __op, __fd_t __fd, struct epoll_event *__event),(__epfd,__op,__fd,__event))
#else /* ... */
#undef __sys_epoll_ctl_old_defined
#endif /* !... */
#endif /* !__sys_epoll_ctl_old_defined */
#endif /* sys_epoll_ctl_old... */
#if __CRT_HAVE_SC(epoll_pwait)
#ifndef __sys_epoll_pwait_defined
#define __sys_epoll_pwait_defined 1
__CDECLARE_SC(,__errno_t,epoll_pwait,(__fd_t __epfd, struct epoll_event *__events, __syscall_ulong_t __maxevents, __syscall_slong_t __timeout, struct __sigset_struct const *__ss),(__epfd,__events,__maxevents,__timeout,__ss))
#endif /* !__sys_epoll_pwait_defined */
#endif /* sys_epoll_pwait... */
#if __CRT_HAVE_SC(epoll_wait)
#ifndef __sys_epoll_wait_defined
#define __sys_epoll_wait_defined 1
__CDECLARE_SC(,__errno_t,epoll_wait,(__fd_t __epfd, struct epoll_event *__events, __syscall_ulong_t __maxevents, __syscall_slong_t __timeout),(__epfd,__events,__maxevents,__timeout))
#endif /* !__sys_epoll_wait_defined */
#endif /* sys_epoll_wait... */
#if __CRT_HAVE_SC(epoll_wait_old)
#ifndef __sys_epoll_wait_old_defined
#define __sys_epoll_wait_old_defined 1
#ifdef __x86_64__
__CDECLARE_SC(,__errno_t,epoll_wait_old,(__fd_t __epfd, struct epoll_event *__events, __syscall_ulong_t __maxevents, __syscall_slong_t __timeout),(__epfd,__events,__maxevents,__timeout))
#else /* ... */
#undef __sys_epoll_wait_old_defined
#endif /* !... */
#endif /* !__sys_epoll_wait_old_defined */
#endif /* sys_epoll_wait_old... */
#if __CRT_HAVE_SC(eventfd)
#ifndef __sys_eventfd_defined
#define __sys_eventfd_defined 1
__CDECLARE_SC(,__fd_t,eventfd,(__syscall_ulong_t __initval),(__initval))
#endif /* !__sys_eventfd_defined */
#endif /* sys_eventfd... */
#if __CRT_HAVE_SC(eventfd2)
#ifndef __sys_eventfd2_defined
#define __sys_eventfd2_defined 1
__CDECLARE_SC(,__fd_t,eventfd2,(__syscall_ulong_t __initval, __syscall_ulong_t __flags),(__initval,__flags))
#endif /* !__sys_eventfd2_defined */
#endif /* sys_eventfd2... */
#if __CRT_HAVE_SC(execve)
#ifndef __sys_execve_defined
#define __sys_execve_defined 1
__CDECLARE_SC(,__errno_t,execve,(char const *__path, char const *const *___argv, char const *const *___envp),(__path,___argv,___envp))
#endif /* !__sys_execve_defined */
#endif /* sys_execve... */
#if __CRT_HAVE_SC(execveat)
#ifndef __sys_execveat_defined
#define __sys_execveat_defined 1
/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,execveat,(__fd_t __dirfd, char const *__pathname, char const *const *___argv, char const *const *___envp, __atflag_t __flags),(__dirfd,__pathname,___argv,___envp,__flags))
#endif /* !__sys_execveat_defined */
#endif /* sys_execveat... */
#if __CRT_HAVE_SC(exit)
#ifndef __sys_exit_defined
#define __sys_exit_defined 1
__CDECLARE_VOID_SC(__ATTR_NORETURN,exit,(__syscall_ulong_t __status),(__status))
#endif /* !__sys_exit_defined */
#endif /* sys_exit... */
#if __CRT_HAVE_SC(exit_group)
#ifndef __sys_exit_group_defined
#define __sys_exit_group_defined 1
__CDECLARE_VOID_SC(__ATTR_NORETURN,exit_group,(__syscall_ulong_t __exit_code),(__exit_code))
#endif /* !__sys_exit_group_defined */
#endif /* sys_exit_group... */
#if __CRT_HAVE_SC(faccessat)
#ifndef __sys_faccessat_defined
#define __sys_faccessat_defined 1
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,faccessat,(__fd_t __dirfd, char const *__filename, __syscall_ulong_t __type, __atflag_t __flags),(__dirfd,__filename,__type,__flags))
#endif /* !__sys_faccessat_defined */
#endif /* sys_faccessat... */
#if __CRT_HAVE_SC(fallocate)
#ifndef __sys_fallocate_defined
#define __sys_fallocate_defined 1
__CDECLARE_SC(,__errno_t,fallocate,(__fd_t __fd, __syscall_ulong_t __mode, __uint32_t __offset, __uint32_t __length),(__fd,__mode,__offset,__length))
#endif /* !__sys_fallocate_defined */
#endif /* sys_fallocate... */
#if __CRT_HAVE_SC(fallocate64)
#ifndef __sys_fallocate64_defined
#define __sys_fallocate64_defined 1
__CDECLARE_SC(,__errno_t,fallocate64,(__fd_t __fd, __syscall_ulong_t __mode, __uint64_t __offset, __uint64_t __length),(__fd,__mode,__offset,__length))
#endif /* !__sys_fallocate64_defined */
#endif /* sys_fallocate64... */
#if __CRT_HAVE_SC(fchdir)
#ifndef __sys_fchdir_defined
#define __sys_fchdir_defined 1
__CDECLARE_SC(,__errno_t,fchdir,(__fd_t __fd),(__fd))
#endif /* !__sys_fchdir_defined */
#endif /* sys_fchdir... */
#if __CRT_HAVE_SC(fchdirat)
#ifndef __sys_fchdirat_defined
#define __sys_fchdirat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fchdirat,(__fd_t __dirfd, char const *__path, __atflag_t __flags),(__dirfd,__path,__flags))
#endif /* !__sys_fchdirat_defined */
#endif /* sys_fchdirat... */
#if __CRT_HAVE_SC(fchmod)
#ifndef __sys_fchmod_defined
#define __sys_fchmod_defined 1
__CDECLARE_SC(,__errno_t,fchmod,(__fd_t __fd, __mode_t __mode),(__fd,__mode))
#endif /* !__sys_fchmod_defined */
#endif /* sys_fchmod... */
#if __CRT_HAVE_SC(fchmodat)
#ifndef __sys_fchmodat_defined
#define __sys_fchmodat_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fchmodat,(__fd_t __dirfd, char const *__filename, __mode_t __mode, __atflag_t __flags),(__dirfd,__filename,__mode,__flags))
#endif /* !__sys_fchmodat_defined */
#endif /* sys_fchmodat... */
#if __CRT_HAVE_SC(fchown)
#ifndef __sys_fchown_defined
#define __sys_fchown_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,fchown,(__fd_t __fd, __uint16_t __owner, __uint16_t __group),(__fd,__owner,__group))
#else /* #elif defined(__x86_64__) */
__CDECLARE_SC(,__errno_t,fchown,(__fd_t __fd, __uint32_t __owner, __uint32_t __group),(__fd,__owner,__group))
#endif /* ... */
#endif /* !__sys_fchown_defined */
#endif /* sys_fchown... */
#if __CRT_HAVE_SC(fchown32)
#ifndef __sys_fchown32_defined
#define __sys_fchown32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,fchown32,(__fd_t __fd, __uint32_t __owner, __uint32_t __group),(__fd,__owner,__group))
#else /* ... */
#undef __sys_fchown32_defined
#endif /* !... */
#endif /* !__sys_fchown32_defined */
#endif /* sys_fchown32... */
#if __CRT_HAVE_SC(fchownat)
#ifndef __sys_fchownat_defined
#define __sys_fchownat_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fchownat,(__fd_t __dirfd, char const *__filename, __uint32_t __owner, __uint32_t __group, __atflag_t __flags),(__dirfd,__filename,__owner,__group,__flags))
#endif /* !__sys_fchownat_defined */
#endif /* sys_fchownat... */
#if __CRT_HAVE_SC(fcntl)
#ifndef __sys_fcntl_defined
#define __sys_fcntl_defined 1
__CDECLARE_SC(,__syscall_slong_t,fcntl,(__fd_t __fd, __syscall_ulong_t __cmd, void *__arg),(__fd,__cmd,__arg))
#endif /* !__sys_fcntl_defined */
#endif /* sys_fcntl... */
#if __CRT_HAVE_SC(fcntl64)
#ifndef __sys_fcntl64_defined
#define __sys_fcntl64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__syscall_slong_t,fcntl64,(__fd_t __fd, __syscall_ulong_t __command, void *__arg),(__fd,__command,__arg))
#else /* ... */
#undef __sys_fcntl64_defined
#endif /* !... */
#endif /* !__sys_fcntl64_defined */
#endif /* sys_fcntl64... */
#if __CRT_HAVE_SC(fdatasync)
#ifndef __sys_fdatasync_defined
#define __sys_fdatasync_defined 1
__CDECLARE_SC(,__errno_t,fdatasync,(__fd_t __fd),(__fd))
#endif /* !__sys_fdatasync_defined */
#endif /* sys_fdatasync... */
#if __CRT_HAVE_SC(fgetxattr)
#ifndef __sys_fgetxattr_defined
#define __sys_fgetxattr_defined 1
__CDECLARE_SC(,__ssize_t,fgetxattr,(__fd_t __fd, char const *__name, void *__buf, __size_t __bufsize),(__fd,__name,__buf,__bufsize))
#endif /* !__sys_fgetxattr_defined */
#endif /* sys_fgetxattr... */
#if __CRT_HAVE_SC(flistxattr)
#ifndef __sys_flistxattr_defined
#define __sys_flistxattr_defined 1
__CDECLARE_SC(,__ssize_t,flistxattr,(__fd_t __fd, char *__listbuf, __size_t __listbufsize),(__fd,__listbuf,__listbufsize))
#endif /* !__sys_flistxattr_defined */
#endif /* sys_flistxattr... */
#if __CRT_HAVE_SC(flock)
#ifndef __sys_flock_defined
#define __sys_flock_defined 1
__CDECLARE_SC(,__errno_t,flock,(__fd_t __fd, __syscall_ulong_t __operation),(__fd,__operation))
#endif /* !__sys_flock_defined */
#endif /* sys_flock... */
#if __CRT_HAVE_SC(fmkdirat)
#ifndef __sys_fmkdirat_defined
#define __sys_fmkdirat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fmkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode, __atflag_t __flags),(__dirfd,__pathname,__mode,__flags))
#endif /* !__sys_fmkdirat_defined */
#endif /* sys_fmkdirat... */
#if __CRT_HAVE_SC(fmknodat)
#ifndef __sys_fmknodat_defined
#define __sys_fmknodat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fmknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),(__dirfd,__nodename,__mode,__dev,__flags))
#endif /* !__sys_fmknodat_defined */
#endif /* sys_fmknodat... */
#if __CRT_HAVE_SC(fork)
#ifndef __sys_fork_defined
#define __sys_fork_defined 1
__CDECLARE_SC(,__pid_t,fork,(void),())
#endif /* !__sys_fork_defined */
#endif /* sys_fork... */
#if __CRT_HAVE_SC(freadlinkat)
#ifndef __sys_freadlinkat_defined
#define __sys_freadlinkat_defined 1
/* @param: flags: Set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
__CDECLARE_SC(,__ssize_t,freadlinkat,(__fd_t __dirfd, char const *__path, char *__buf, __size_t __buflen, __atflag_t __flags),(__dirfd,__path,__buf,__buflen,__flags))
#endif /* !__sys_freadlinkat_defined */
#endif /* sys_freadlinkat... */
#if __CRT_HAVE_SC(frealpath4)
#ifndef __sys_frealpath4_defined
#define __sys_frealpath4_defined 1
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
__CDECLARE_SC(,__ssize_t,frealpath4,(__fd_t __fd, char *__buf, __size_t __buflen, __atflag_t __flags),(__fd,__buf,__buflen,__flags))
#endif /* !__sys_frealpath4_defined */
#endif /* sys_frealpath4... */
#if __CRT_HAVE_SC(frealpathat)
#ifndef __sys_frealpathat_defined
#define __sys_frealpathat_defined 1
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE|AT_DOSPATH' */
__CDECLARE_SC(,__ssize_t,frealpathat,(__fd_t __dirfd, char const *__filename, char *__buf, __size_t __buflen, __atflag_t __flags),(__dirfd,__filename,__buf,__buflen,__flags))
#endif /* !__sys_frealpathat_defined */
#endif /* sys_frealpathat... */
#if __CRT_HAVE_SC(fremovexattr)
#ifndef __sys_fremovexattr_defined
#define __sys_fremovexattr_defined 1
__CDECLARE_SC(,__errno_t,fremovexattr,(int __fd, char const *__name),(__fd,__name))
#endif /* !__sys_fremovexattr_defined */
#endif /* sys_fremovexattr... */
#if __CRT_HAVE_SC(frenameat)
#ifndef __sys_frenameat_defined
#define __sys_frenameat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,frenameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path, __atflag_t __flags),(__oldfd,__oldname,__newfd,__newname_or_path,__flags))
#endif /* !__sys_frenameat_defined */
#endif /* sys_frenameat... */
#if __CRT_HAVE_SC(fsetxattr)
#ifndef __sys_fsetxattr_defined
#define __sys_fsetxattr_defined 1
__CDECLARE_SC(,__errno_t,fsetxattr,(__fd_t __fd, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__fd,__name,__buf,__bufsize,__flags))
#endif /* !__sys_fsetxattr_defined */
#endif /* sys_fsetxattr... */
#if __CRT_HAVE_SC(fsmode)
#ifndef __sys_fsmode_defined
#define __sys_fsmode_defined 1
__CDECLARE_SC(,__uint64_t,fsmode,(__uint64_t __mode),(__mode))
#endif /* !__sys_fsmode_defined */
#endif /* sys_fsmode... */
#if __CRT_HAVE_SC(fstatat)
#ifndef __sys_fstatat_defined
#define __sys_fstatat_defined 1
#ifdef __x86_64__
__CDECLARE_SC(,__errno_t,fstatat,(__fd_t __dirfd, char const *__filename, struct linux64_stat32 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#else /* ... */
#undef __sys_fstatat_defined
#endif /* !... */
#endif /* !__sys_fstatat_defined */
#endif /* sys_fstatat... */
#if __CRT_HAVE_SC(fstatfs)
#ifndef __sys_fstatfs_defined
#define __sys_fstatfs_defined 1
__CDECLARE_SC(,__errno_t,fstatfs,(__fd_t __file, struct __statfs32 *__buf),(__file,__buf))
#endif /* !__sys_fstatfs_defined */
#endif /* sys_fstatfs... */
#if __CRT_HAVE_SC(fstatfs64)
#ifndef __sys_fstatfs64_defined
#define __sys_fstatfs64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,fstatfs64,(__fd_t __file, struct statfs64 *__buf),(__file,__buf))
#else /* ... */
#undef __sys_fstatfs64_defined
#endif /* !... */
#endif /* !__sys_fstatfs64_defined */
#endif /* sys_fstatfs64... */
#if __CRT_HAVE_SC(fsymlinkat)
#ifndef __sys_fsymlinkat_defined
#define __sys_fsymlinkat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fsymlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__link_text,__tofd,__target_path,__flags))
#endif /* !__sys_fsymlinkat_defined */
#endif /* sys_fsymlinkat... */
#if __CRT_HAVE_SC(fsync)
#ifndef __sys_fsync_defined
#define __sys_fsync_defined 1
__CDECLARE_SC(,__errno_t,fsync,(__fd_t __fd),(__fd))
#endif /* !__sys_fsync_defined */
#endif /* sys_fsync... */
#if __CRT_HAVE_SC(ftime)
#ifndef __sys_ftime_defined
#define __sys_ftime_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,ftime,(struct timeb *__tp),(__tp))
#else /* ... */
#undef __sys_ftime_defined
#endif /* !... */
#endif /* !__sys_ftime_defined */
#endif /* sys_ftime... */
#if __CRT_HAVE_SC(ftruncate)
#ifndef __sys_ftruncate_defined
#define __sys_ftruncate_defined 1
__CDECLARE_SC(,__errno_t,ftruncate,(__fd_t __fd, __syscall_ulong_t __length),(__fd,__length))
#endif /* !__sys_ftruncate_defined */
#endif /* sys_ftruncate... */
#if __CRT_HAVE_SC(ftruncate64)
#ifndef __sys_ftruncate64_defined
#define __sys_ftruncate64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,ftruncate64,(__fd_t __fd, __uint64_t __length),(__fd,__length))
#else /* ... */
#undef __sys_ftruncate64_defined
#endif /* !... */
#endif /* !__sys_ftruncate64_defined */
#endif /* sys_ftruncate64... */
#if __CRT_HAVE_SC(futex)
#ifndef __sys_futex_defined
#define __sys_futex_defined 1
__CDECLARE_SC(,__syscall_slong_t,futex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct __timespec32 const *__timeout_or_val2, __uint32_t *__uaddr2, __uint32_t __val3),(__uaddr,__futex_op,__val,__timeout_or_val2,__uaddr2,__val3))
#endif /* !__sys_futex_defined */
#endif /* sys_futex... */
#if __CRT_HAVE_SC(futimesat)
#ifndef __sys_futimesat_defined
#define __sys_futimesat_defined 1
__CDECLARE_SC(,__errno_t,futimesat,(__fd_t __dirfd, const char *__filename, /*[2]*/ struct __timeval32 const *__times),(__dirfd,__filename,__times))
#endif /* !__sys_futimesat_defined */
#endif /* sys_futimesat... */
#if __CRT_HAVE_SC(futimesat64)
#ifndef __sys_futimesat64_defined
#define __sys_futimesat64_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,futimesat64,(__fd_t __dirfd, const char *__filename, /*[2-3]*/ struct __timeval64 const *__times),(__dirfd,__filename,__times))
#endif /* !__sys_futimesat64_defined */
#endif /* sys_futimesat64... */
#if __CRT_HAVE_SC(get_exception_handler)
#ifndef __sys_get_exception_handler_defined
#define __sys_get_exception_handler_defined 1
/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
__CDECLARE_SC(,__errno_t,get_exception_handler,(__syscall_ulong_t *__pmode, __except_handler_t *__phandler, void **__phandler_sp),(__pmode,__phandler,__phandler_sp))
#endif /* !__sys_get_exception_handler_defined */
#endif /* sys_get_exception_handler... */
#if __CRT_HAVE_SC(getcpu)
#ifndef __sys_getcpu_defined
#define __sys_getcpu_defined 1
__CDECLARE_SC(,__errno_t,getcpu,(__uint32_t *__cpu, __uint32_t *__node, struct getcpu_cache *__tcache),(__cpu,__node,__tcache))
#endif /* !__sys_getcpu_defined */
#endif /* sys_getcpu... */
#if __CRT_HAVE_SC(getcwd)
#ifndef __sys_getcwd_defined
#define __sys_getcwd_defined 1
__CDECLARE_SC(,__ssize_t,getcwd,(char *__buf, __size_t __size),(__buf,__size))
#endif /* !__sys_getcwd_defined */
#endif /* sys_getcwd... */
#if __CRT_HAVE_SC(getdents)
#ifndef __sys_getdents_defined
#define __sys_getdents_defined 1
__CDECLARE_SC(,__ssize_t,getdents,(__fd_t __fd, struct linux_dirent *__dirp, __size_t __count),(__fd,__dirp,__count))
#endif /* !__sys_getdents_defined */
#endif /* sys_getdents... */
#if __CRT_HAVE_SC(getdents64)
#ifndef __sys_getdents64_defined
#define __sys_getdents64_defined 1
__CDECLARE_SC(,__ssize_t,getdents64,(__fd_t __fd, struct linux_dirent64 *__dirp, __size_t __count),(__fd,__dirp,__count))
#endif /* !__sys_getdents64_defined */
#endif /* sys_getdents64... */
#if __CRT_HAVE_SC(getdrives)
#ifndef __sys_getdrives_defined
#define __sys_getdrives_defined 1
/* Returns a bitset of all of the currently mounted dos-drives */
__CDECLARE_SC(,__syscall_slong_t,getdrives,(void),())
#endif /* !__sys_getdrives_defined */
#endif /* sys_getdrives... */
#if __CRT_HAVE_SC(getegid)
#ifndef __sys_getegid_defined
#define __sys_getegid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__uint16_t,getegid,(void),())
#else /* ... */
#undef __sys_getegid_defined
#endif /* !... */
#endif /* !__sys_getegid_defined */
#endif /* sys_getegid... */
#if __CRT_HAVE_SC(getegid32)
#ifndef __sys_getegid32_defined
#define __sys_getegid32_defined 1
__CDECLARE_SC(,__uint32_t,getegid32,(void),())
#endif /* !__sys_getegid32_defined */
#endif /* sys_getegid32... */
#if __CRT_HAVE_SC(geteuid)
#ifndef __sys_geteuid_defined
#define __sys_geteuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__uint16_t,geteuid,(void),())
#else /* ... */
#undef __sys_geteuid_defined
#endif /* !... */
#endif /* !__sys_geteuid_defined */
#endif /* sys_geteuid... */
#if __CRT_HAVE_SC(geteuid32)
#ifndef __sys_geteuid32_defined
#define __sys_geteuid32_defined 1
__CDECLARE_SC(,__uint32_t,geteuid32,(void),())
#endif /* !__sys_geteuid32_defined */
#endif /* sys_geteuid32... */
#if __CRT_HAVE_SC(getgid)
#ifndef __sys_getgid_defined
#define __sys_getgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__uint16_t,getgid,(void),())
#else /* ... */
#undef __sys_getgid_defined
#endif /* !... */
#endif /* !__sys_getgid_defined */
#endif /* sys_getgid... */
#if __CRT_HAVE_SC(getgid32)
#ifndef __sys_getgid32_defined
#define __sys_getgid32_defined 1
__CDECLARE_SC(,__uint32_t,getgid32,(void),())
#endif /* !__sys_getgid32_defined */
#endif /* sys_getgid32... */
#if __CRT_HAVE_SC(getgroups)
#ifndef __sys_getgroups_defined
#define __sys_getgroups_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,getgroups,(__size_t __size, /*[]*/ __uint16_t *__list),(__size,__list))
#else /* ... */
#undef __sys_getgroups_defined
#endif /* !... */
#endif /* !__sys_getgroups_defined */
#endif /* sys_getgroups... */
#if __CRT_HAVE_SC(getgroups32)
#ifndef __sys_getgroups32_defined
#define __sys_getgroups32_defined 1
__CDECLARE_SC(,__errno_t,getgroups32,(__size_t __size, /*[]*/ __uint32_t *__list),(__size,__list))
#endif /* !__sys_getgroups32_defined */
#endif /* sys_getgroups32... */
#if __CRT_HAVE_SC(getitimer)
#ifndef __sys_getitimer_defined
#define __sys_getitimer_defined 1
__CDECLARE_SC(,__errno_t,getitimer,(__syscall_ulong_t __which, struct __itimerval32 *__curr_value),(__which,__curr_value))
#endif /* !__sys_getitimer_defined */
#endif /* sys_getitimer... */
#if __CRT_HAVE_SC(getitimer64)
#ifndef __sys_getitimer64_defined
#define __sys_getitimer64_defined 1
__CDECLARE_SC(,__errno_t,getitimer64,(__syscall_ulong_t __which, struct __itimerval64 *__curr_value),(__which,__curr_value))
#endif /* !__sys_getitimer64_defined */
#endif /* sys_getitimer64... */
#if __CRT_HAVE_SC(getpeername)
#ifndef __sys_getpeername_defined
#define __sys_getpeername_defined 1
__CDECLARE_SC(,__errno_t,getpeername,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* !__sys_getpeername_defined */
#endif /* sys_getpeername... */
#if __CRT_HAVE_SC(getpgid)
#ifndef __sys_getpgid_defined
#define __sys_getpgid_defined 1
__CDECLARE_SC(,__pid_t,getpgid,(__pid_t __pid),(__pid))
#endif /* !__sys_getpgid_defined */
#endif /* sys_getpgid... */
#if __CRT_HAVE_SC(getpgrp)
#ifndef __sys_getpgrp_defined
#define __sys_getpgrp_defined 1
__CDECLARE_SC(,__pid_t,getpgrp,(void),())
#endif /* !__sys_getpgrp_defined */
#endif /* sys_getpgrp... */
#if __CRT_HAVE_SC(getpid)
#ifndef __sys_getpid_defined
#define __sys_getpid_defined 1
__CDECLARE_SC(,__pid_t,getpid,(void),())
#endif /* !__sys_getpid_defined */
#endif /* sys_getpid... */
#if __CRT_HAVE_SC(getppid)
#ifndef __sys_getppid_defined
#define __sys_getppid_defined 1
__CDECLARE_SC(,__pid_t,getppid,(void),())
#endif /* !__sys_getppid_defined */
#endif /* sys_getppid... */
#if __CRT_HAVE_SC(getpriority)
#ifndef __sys_getpriority_defined
#define __sys_getpriority_defined 1
__CDECLARE_SC(,__syscall_slong_t,getpriority,(__syscall_ulong_t __which, __id_t __who),(__which,__who))
#endif /* !__sys_getpriority_defined */
#endif /* sys_getpriority... */
#if __CRT_HAVE_SC(getresgid)
#ifndef __sys_getresgid_defined
#define __sys_getresgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,getresgid,(__uint16_t *__rgid, __uint16_t *__egid, __uint16_t *__sgid),(__rgid,__egid,__sgid))
#else /* ... */
#undef __sys_getresgid_defined
#endif /* !... */
#endif /* !__sys_getresgid_defined */
#endif /* sys_getresgid... */
#if __CRT_HAVE_SC(getresgid32)
#ifndef __sys_getresgid32_defined
#define __sys_getresgid32_defined 1
__CDECLARE_SC(,__errno_t,getresgid32,(__uint32_t *__rgid, __uint32_t *__egid, __uint32_t *__sgid),(__rgid,__egid,__sgid))
#endif /* !__sys_getresgid32_defined */
#endif /* sys_getresgid32... */
#if __CRT_HAVE_SC(getresuid)
#ifndef __sys_getresuid_defined
#define __sys_getresuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,getresuid,(__uint16_t *__ruid, __uint16_t *__euid, __uint16_t *__suid),(__ruid,__euid,__suid))
#else /* ... */
#undef __sys_getresuid_defined
#endif /* !... */
#endif /* !__sys_getresuid_defined */
#endif /* sys_getresuid... */
#if __CRT_HAVE_SC(getresuid32)
#ifndef __sys_getresuid32_defined
#define __sys_getresuid32_defined 1
__CDECLARE_SC(,__errno_t,getresuid32,(__uint32_t *__ruid, __uint32_t *__euid, __uint32_t *__suid),(__ruid,__euid,__suid))
#endif /* !__sys_getresuid32_defined */
#endif /* sys_getresuid32... */
#if __CRT_HAVE_SC(getrlimit)
#ifndef __sys_getrlimit_defined
#define __sys_getrlimit_defined 1
__CDECLARE_SC(,__errno_t,getrlimit,(__syscall_ulong_t __resource, struct rlimit *__rlimits),(__resource,__rlimits))
#endif /* !__sys_getrlimit_defined */
#endif /* sys_getrlimit... */
#if __CRT_HAVE_SC(getrusage)
#ifndef __sys_getrusage_defined
#define __sys_getrusage_defined 1
__CDECLARE_SC(,__errno_t,getrusage,(__syscall_slong_t __who, struct rusage *__usage),(__who,__usage))
#endif /* !__sys_getrusage_defined */
#endif /* sys_getrusage... */
#if __CRT_HAVE_SC(getsid)
#ifndef __sys_getsid_defined
#define __sys_getsid_defined 1
__CDECLARE_SC(,__pid_t,getsid,(__pid_t __pid),(__pid))
#endif /* !__sys_getsid_defined */
#endif /* sys_getsid... */
#if __CRT_HAVE_SC(getsockname)
#ifndef __sys_getsockname_defined
#define __sys_getsockname_defined 1
__CDECLARE_SC(,__errno_t,getsockname,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* !__sys_getsockname_defined */
#endif /* sys_getsockname... */
#if __CRT_HAVE_SC(getsockopt)
#ifndef __sys_getsockopt_defined
#define __sys_getsockopt_defined 1
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
__CDECLARE_SC(,__errno_t,getsockopt,(__fd_t __sockfd, __syscall_ulong_t __level, __syscall_ulong_t __optname, void *__optval, __socklen_t *__optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* !__sys_getsockopt_defined */
#endif /* sys_getsockopt... */
#if __CRT_HAVE_SC(gettid)
#ifndef __sys_gettid_defined
#define __sys_gettid_defined 1
__CDECLARE_SC(,__pid_t,gettid,(void),())
#endif /* !__sys_gettid_defined */
#endif /* sys_gettid... */
#if __CRT_HAVE_SC(gettimeofday)
#ifndef __sys_gettimeofday_defined
#define __sys_gettimeofday_defined 1
__CDECLARE_SC(,__errno_t,gettimeofday,(struct __timeval32 *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* !__sys_gettimeofday_defined */
#endif /* sys_gettimeofday... */
#if __CRT_HAVE_SC(gettimeofday64)
#ifndef __sys_gettimeofday64_defined
#define __sys_gettimeofday64_defined 1
__CDECLARE_SC(,__errno_t,gettimeofday64,(struct __timeval64 *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* !__sys_gettimeofday64_defined */
#endif /* sys_gettimeofday64... */
#if __CRT_HAVE_SC(getuid)
#ifndef __sys_getuid_defined
#define __sys_getuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__uint16_t,getuid,(void),())
#else /* ... */
#undef __sys_getuid_defined
#endif /* !... */
#endif /* !__sys_getuid_defined */
#endif /* sys_getuid... */
#if __CRT_HAVE_SC(getuid32)
#ifndef __sys_getuid32_defined
#define __sys_getuid32_defined 1
__CDECLARE_SC(,__uint32_t,getuid32,(void),())
#endif /* !__sys_getuid32_defined */
#endif /* sys_getuid32... */
#if __CRT_HAVE_SC(getxattr)
#ifndef __sys_getxattr_defined
#define __sys_getxattr_defined 1
__CDECLARE_SC(,__ssize_t,getxattr,(char const *__path, char const *__name, void *__buf, __size_t __bufsize),(__path,__name,__buf,__bufsize))
#endif /* !__sys_getxattr_defined */
#endif /* sys_getxattr... */
#if __CRT_HAVE_SC(hop)
#ifndef __sys_hop_defined
#define __sys_hop_defined 1
__CDECLARE_SC(,__syscall_slong_t,hop,(__fd_t __fd, __syscall_ulong_t __command, void *__arg),(__fd,__command,__arg))
#endif /* !__sys_hop_defined */
#endif /* sys_hop... */
#if __CRT_HAVE_SC(hopf)
#ifndef __sys_hopf_defined
#define __sys_hopf_defined 1
__CDECLARE_SC(,__syscall_slong_t,hopf,(__fd_t __fd, __syscall_ulong_t __command, __iomode_t __mode, void *__arg),(__fd,__command,__mode,__arg))
#endif /* !__sys_hopf_defined */
#endif /* sys_hopf... */
#if __CRT_HAVE_SC(ioctl)
#ifndef __sys_ioctl_defined
#define __sys_ioctl_defined 1
__CDECLARE_SC(,__syscall_slong_t,ioctl,(__fd_t __fd, __syscall_ulong_t __request, void *__arg),(__fd,__request,__arg))
#endif /* !__sys_ioctl_defined */
#endif /* sys_ioctl... */
#if __CRT_HAVE_SC(ioctlf)
#ifndef __sys_ioctlf_defined
#define __sys_ioctlf_defined 1
__CDECLARE_SC(,__syscall_slong_t,ioctlf,(__fd_t __fd, __syscall_ulong_t __command, __iomode_t __mode, void *__arg),(__fd,__command,__mode,__arg))
#endif /* !__sys_ioctlf_defined */
#endif /* sys_ioctlf... */
#if __CRT_HAVE_SC(ioperm)
#ifndef __sys_ioperm_defined
#define __sys_ioperm_defined 1
__CDECLARE_SC(,__errno_t,ioperm,(__syscall_ulong_t __from, __syscall_ulong_t __num, __syscall_ulong_t __turn_on),(__from,__num,__turn_on))
#endif /* !__sys_ioperm_defined */
#endif /* sys_ioperm... */
#if __CRT_HAVE_SC(iopl)
#ifndef __sys_iopl_defined
#define __sys_iopl_defined 1
__CDECLARE_SC(,__errno_t,iopl,(__syscall_ulong_t __level),(__level))
#endif /* !__sys_iopl_defined */
#endif /* sys_iopl... */
#if __CRT_HAVE_SC(ioprio_get)
#ifndef __sys_ioprio_get_defined
#define __sys_ioprio_get_defined 1
__CDECLARE_SC(,__errno_t,ioprio_get,(__syscall_ulong_t __which, __syscall_ulong_t __who),(__which,__who))
#endif /* !__sys_ioprio_get_defined */
#endif /* sys_ioprio_get... */
#if __CRT_HAVE_SC(ioprio_set)
#ifndef __sys_ioprio_set_defined
#define __sys_ioprio_set_defined 1
__CDECLARE_SC(,__errno_t,ioprio_set,(__syscall_ulong_t __which, __syscall_ulong_t __who, __syscall_ulong_t __ioprio),(__which,__who,__ioprio))
#endif /* !__sys_ioprio_set_defined */
#endif /* sys_ioprio_set... */
#if __CRT_HAVE_SC(kcmp)
#ifndef __sys_kcmp_defined
#define __sys_kcmp_defined 1
__CDECLARE_SC(,__syscall_slong_t,kcmp,(__pid_t __pid1, __pid_t __pid2, __syscall_ulong_t __type, __syscall_ulong_t __idx1, __syscall_ulong_t __idx2),(__pid1,__pid2,__type,__idx1,__idx2))
#endif /* !__sys_kcmp_defined */
#endif /* sys_kcmp... */
#if __CRT_HAVE_SC(kfstat)
#ifndef __sys_kfstat_defined
#define __sys_kfstat_defined 1
__CDECLARE_SC(,__errno_t,kfstat,(__fd_t __fd, struct stat *__statbuf),(__fd,__statbuf))
#endif /* !__sys_kfstat_defined */
#endif /* sys_kfstat... */
#if __CRT_HAVE_SC(kfstatat)
#ifndef __sys_kfstatat_defined
#define __sys_kfstatat_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,kfstatat,(__fd_t __dirfd, char const *__filename, struct stat *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* !__sys_kfstatat_defined */
#endif /* sys_kfstatat... */
#if __CRT_HAVE_SC(kill)
#ifndef __sys_kill_defined
#define __sys_kill_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,kill,(__pid_t __pid, __syscall_ulong_t __signo),(__pid,__signo))
#endif /* !__sys_kill_defined */
#endif /* sys_kill... */
#if __CRT_HAVE_SC(klstat)
#ifndef __sys_klstat_defined
#define __sys_klstat_defined 1
__CDECLARE_SC(,__errno_t,klstat,(char const *__filename, struct stat *__statbuf),(__filename,__statbuf))
#endif /* !__sys_klstat_defined */
#endif /* sys_klstat... */
#if __CRT_HAVE_SC(kreaddir)
#ifndef __sys_kreaddir_defined
#define __sys_kreaddir_defined 1
__CDECLARE_SC(,__ssize_t,kreaddir,(__fd_t __fd, struct dirent *__buf, __size_t __bufsize, __syscall_ulong_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* !__sys_kreaddir_defined */
#endif /* sys_kreaddir... */
#if __CRT_HAVE_SC(kreaddirf)
#ifndef __sys_kreaddirf_defined
#define __sys_kreaddirf_defined 1
__CDECLARE_SC(,__ssize_t,kreaddirf,(__fd_t __fd, struct dirent *__buf, __size_t __bufsize, __syscall_ulong_t __mode, __iomode_t __iomode),(__fd,__buf,__bufsize,__mode,__iomode))
#endif /* !__sys_kreaddirf_defined */
#endif /* sys_kreaddirf... */
#if __CRT_HAVE_SC(kstat)
#ifndef __sys_kstat_defined
#define __sys_kstat_defined 1
__CDECLARE_SC(,__errno_t,kstat,(char const *__filename, struct stat *__statbuf),(__filename,__statbuf))
#endif /* !__sys_kstat_defined */
#endif /* sys_kstat... */
#if __CRT_HAVE_SC(lchown)
#ifndef __sys_lchown_defined
#define __sys_lchown_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,lchown,(char const *__filename, __uint16_t __owner, __uint16_t __group),(__filename,__owner,__group))
#else /* #elif defined(__x86_64__) */
__CDECLARE_SC(,__errno_t,lchown,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#endif /* ... */
#endif /* !__sys_lchown_defined */
#endif /* sys_lchown... */
#if __CRT_HAVE_SC(lchown32)
#ifndef __sys_lchown32_defined
#define __sys_lchown32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,lchown32,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#else /* ... */
#undef __sys_lchown32_defined
#endif /* !... */
#endif /* !__sys_lchown32_defined */
#endif /* sys_lchown32... */
#if __CRT_HAVE_SC(lfutex)
#ifndef __sys_lfutex_defined
#define __sys_lfutex_defined 1
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
__CDECLARE_SC(,__syscall_slong_t,lfutex,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val, struct __timespec64 const *__timeout, __uintptr_t __val2),(__uaddr,__futex_op,__val,__timeout,__val2))
#endif /* !__sys_lfutex_defined */
#endif /* sys_lfutex... */
#if __CRT_HAVE_SC(lfutexexpr)
#ifndef __sys_lfutexexpr_defined
#define __sys_lfutexexpr_defined 1
/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CDECLARE_SC(,__errno_t,lfutexexpr,(void *__base, __size_t __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, __syscall_ulong_t __timeout_flags),(__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* !__sys_lfutexexpr_defined */
#endif /* sys_lfutexexpr... */
#if __CRT_HAVE_SC(lfutexlockexpr)
#ifndef __sys_lfutexlockexpr_defined
#define __sys_lfutexlockexpr_defined 1
/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CDECLARE_SC(,__errno_t,lfutexlockexpr,(__uintptr_t *__ulockaddr, void *__base, __size_t __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, __syscall_ulong_t __timeout_flags),(__ulockaddr,__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* !__sys_lfutexlockexpr_defined */
#endif /* sys_lfutexlockexpr... */
#if __CRT_HAVE_SC(lgetxattr)
#ifndef __sys_lgetxattr_defined
#define __sys_lgetxattr_defined 1
__CDECLARE_SC(,__ssize_t,lgetxattr,(char const *__path, char const *__name, void *__buf, __size_t __bufsize),(__path,__name,__buf,__bufsize))
#endif /* !__sys_lgetxattr_defined */
#endif /* sys_lgetxattr... */
#if __CRT_HAVE_SC(link)
#ifndef __sys_link_defined
#define __sys_link_defined 1
__CDECLARE_SC(,__errno_t,link,(char const *__existing_file, char const *__link_file),(__existing_file,__link_file))
#endif /* !__sys_link_defined */
#endif /* sys_link... */
#if __CRT_HAVE_SC(linkat)
#ifndef __sys_linkat_defined
#define __sys_linkat_defined 1
/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,linkat,(__fd_t __fromfd, char const *__existing_file, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__fromfd,__existing_file,__tofd,__target_path,__flags))
#endif /* !__sys_linkat_defined */
#endif /* sys_linkat... */
#if __CRT_HAVE_SC(linux_fstat32)
#ifndef __sys_linux_fstat32_defined
#define __sys_linux_fstat32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,linux_fstat32,(__fd_t __fd, struct linux_stat32 *__statbuf),(__fd,__statbuf))
#else /* ... */
#undef __sys_linux_fstat32_defined
#endif /* !... */
#endif /* !__sys_linux_fstat32_defined */
#endif /* sys_linux_fstat32... */
#if __CRT_HAVE_SC(linux_fstat64)
#ifndef __sys_linux_fstat64_defined
#define __sys_linux_fstat64_defined 1
__CDECLARE_SC(,__errno_t,linux_fstat64,(__fd_t __fd, struct linux_stat64 *__statbuf),(__fd,__statbuf))
#endif /* !__sys_linux_fstat64_defined */
#endif /* sys_linux_fstat64... */
#if __CRT_HAVE_SC(linux_fstatat64)
#ifndef __sys_linux_fstatat64_defined
#define __sys_linux_fstatat64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,linux_fstatat64,(__fd_t __dirfd, char const *__filename, struct linux_stat64 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#else /* ... */
#undef __sys_linux_fstatat64_defined
#endif /* !... */
#endif /* !__sys_linux_fstatat64_defined */
#endif /* sys_linux_fstatat64... */
#if __CRT_HAVE_SC(linux_lstat32)
#ifndef __sys_linux_lstat32_defined
#define __sys_linux_lstat32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,linux_lstat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#else /* ... */
#undef __sys_linux_lstat32_defined
#endif /* !... */
#endif /* !__sys_linux_lstat32_defined */
#endif /* sys_linux_lstat32... */
#if __CRT_HAVE_SC(linux_lstat64)
#ifndef __sys_linux_lstat64_defined
#define __sys_linux_lstat64_defined 1
__CDECLARE_SC(,__errno_t,linux_lstat64,(char const *__filename, struct linux_stat64 *__statbuf),(__filename,__statbuf))
#endif /* !__sys_linux_lstat64_defined */
#endif /* sys_linux_lstat64... */
#if __CRT_HAVE_SC(linux_oldfstat)
#ifndef __sys_linux_oldfstat_defined
#define __sys_linux_oldfstat_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,linux_oldfstat,(__fd_t __fd, struct linux_oldstat *__statbuf),(__fd,__statbuf))
#else /* ... */
#undef __sys_linux_oldfstat_defined
#endif /* !... */
#endif /* !__sys_linux_oldfstat_defined */
#endif /* sys_linux_oldfstat... */
#if __CRT_HAVE_SC(linux_oldlstat)
#ifndef __sys_linux_oldlstat_defined
#define __sys_linux_oldlstat_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,linux_oldlstat,(char const *__filename, struct linux_oldstat *__statbuf),(__filename,__statbuf))
#else /* ... */
#undef __sys_linux_oldlstat_defined
#endif /* !... */
#endif /* !__sys_linux_oldlstat_defined */
#endif /* sys_linux_oldlstat... */
#if __CRT_HAVE_SC(linux_oldstat)
#ifndef __sys_linux_oldstat_defined
#define __sys_linux_oldstat_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,linux_oldstat,(char const *__filename, struct linux_oldstat *__statbuf),(__filename,__statbuf))
#else /* ... */
#undef __sys_linux_oldstat_defined
#endif /* !... */
#endif /* !__sys_linux_oldstat_defined */
#endif /* sys_linux_oldstat... */
#if __CRT_HAVE_SC(linux_stat32)
#ifndef __sys_linux_stat32_defined
#define __sys_linux_stat32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,linux_stat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#else /* ... */
#undef __sys_linux_stat32_defined
#endif /* !... */
#endif /* !__sys_linux_stat32_defined */
#endif /* sys_linux_stat32... */
#if __CRT_HAVE_SC(linux_stat64)
#ifndef __sys_linux_stat64_defined
#define __sys_linux_stat64_defined 1
__CDECLARE_SC(,__errno_t,linux_stat64,(char const *__filename, struct linux_stat64 *__statbuf),(__filename,__statbuf))
#endif /* !__sys_linux_stat64_defined */
#endif /* sys_linux_stat64... */
#if __CRT_HAVE_SC(listen)
#ifndef __sys_listen_defined
#define __sys_listen_defined 1
__CDECLARE_SC(,__errno_t,listen,(__fd_t __sockfd, __syscall_ulong_t __max_backlog),(__sockfd,__max_backlog))
#endif /* !__sys_listen_defined */
#endif /* sys_listen... */
#if __CRT_HAVE_SC(listxattr)
#ifndef __sys_listxattr_defined
#define __sys_listxattr_defined 1
__CDECLARE_SC(,__ssize_t,listxattr,(char const *__path, char *__listbuf, __size_t __listbufsize),(__path,__listbuf,__listbufsize))
#endif /* !__sys_listxattr_defined */
#endif /* sys_listxattr... */
#if __CRT_HAVE_SC(llistxattr)
#ifndef __sys_llistxattr_defined
#define __sys_llistxattr_defined 1
__CDECLARE_SC(,__ssize_t,llistxattr,(char const *__path, char *__listbuf, __size_t __listbufsize),(__path,__listbuf,__listbufsize))
#endif /* !__sys_llistxattr_defined */
#endif /* sys_llistxattr... */
#if __CRT_HAVE_SC(lremovexattr)
#ifndef __sys_lremovexattr_defined
#define __sys_lremovexattr_defined 1
__CDECLARE_SC(,__errno_t,lremovexattr,(char const *__path, char const *__name),(__path,__name))
#endif /* !__sys_lremovexattr_defined */
#endif /* sys_lremovexattr... */
#if __CRT_HAVE_SC(lseek)
#ifndef __sys_lseek_defined
#define __sys_lseek_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__int32_t,lseek,(__fd_t __fd, __int32_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#else /* ... */
#undef __sys_lseek_defined
#endif /* !... */
#endif /* !__sys_lseek_defined */
#endif /* sys_lseek... */
#if __CRT_HAVE_SC(lseek64)
#ifndef __sys_lseek64_defined
#define __sys_lseek64_defined 1
__CDECLARE_SC(,__int64_t,lseek64,(__fd_t __fd, __int64_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* !__sys_lseek64_defined */
#endif /* sys_lseek64... */
#if __CRT_HAVE_SC(lsetxattr)
#ifndef __sys_lsetxattr_defined
#define __sys_lsetxattr_defined 1
__CDECLARE_SC(,__errno_t,lsetxattr,(char const *__path, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__path,__name,__buf,__bufsize,__flags))
#endif /* !__sys_lsetxattr_defined */
#endif /* sys_lsetxattr... */
#if __CRT_HAVE_SC(madvise)
#ifndef __sys_madvise_defined
#define __sys_madvise_defined 1
__CDECLARE_SC(,__errno_t,madvise,(void *__addr, __size_t __len, __syscall_ulong_t __advice),(__addr,__len,__advice))
#endif /* !__sys_madvise_defined */
#endif /* sys_madvise... */
#if __CRT_HAVE_SC(maplibrary)
#ifndef __sys_maplibrary_defined
#define __sys_maplibrary_defined 1
/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
__CDECLARE_SC(,void *,maplibrary,(void *__addr, __syscall_ulong_t __flags, __fd_t __fd, void *__hdrv, __size_t __hdrc),(__addr,__flags,__fd,__hdrv,__hdrc))
#endif /* !__sys_maplibrary_defined */
#endif /* sys_maplibrary... */
#if __CRT_HAVE_SC(mincore)
#ifndef __sys_mincore_defined
#define __sys_mincore_defined 1
__CDECLARE_SC(,__errno_t,mincore,(void *__start, __size_t __len, __uint8_t *__vec),(__start,__len,__vec))
#endif /* !__sys_mincore_defined */
#endif /* sys_mincore... */
#if __CRT_HAVE_SC(mkdir)
#ifndef __sys_mkdir_defined
#define __sys_mkdir_defined 1
__CDECLARE_SC(,__errno_t,mkdir,(char const *__pathname, __mode_t __mode),(__pathname,__mode))
#endif /* !__sys_mkdir_defined */
#endif /* sys_mkdir... */
#if __CRT_HAVE_SC(mkdirat)
#ifndef __sys_mkdirat_defined
#define __sys_mkdirat_defined 1
__CDECLARE_SC(,__errno_t,mkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode),(__dirfd,__pathname,__mode))
#endif /* !__sys_mkdirat_defined */
#endif /* sys_mkdirat... */
#if __CRT_HAVE_SC(mknod)
#ifndef __sys_mknod_defined
#define __sys_mknod_defined 1
__CDECLARE_SC(,__errno_t,mknod,(char const *__nodename, __mode_t __mode, __dev_t __dev),(__nodename,__mode,__dev))
#endif /* !__sys_mknod_defined */
#endif /* sys_mknod... */
#if __CRT_HAVE_SC(mknodat)
#ifndef __sys_mknodat_defined
#define __sys_mknodat_defined 1
__CDECLARE_SC(,__errno_t,mknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev),(__dirfd,__nodename,__mode,__dev))
#endif /* !__sys_mknodat_defined */
#endif /* sys_mknodat... */
#if __CRT_HAVE_SC(mktty)
#ifndef __sys_mktty_defined
#define __sys_mktty_defined 1
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
__CDECLARE_SC(,__fd_t,mktty,(__fd_t __keyboard, __fd_t __display, char const *__name, __syscall_ulong_t __rsvd),(__keyboard,__display,__name,__rsvd))
#endif /* !__sys_mktty_defined */
#endif /* sys_mktty... */
#if __CRT_HAVE_SC(mlock)
#ifndef __sys_mlock_defined
#define __sys_mlock_defined 1
__CDECLARE_SC(,__errno_t,mlock,(void const *__addr, __size_t __len),(__addr,__len))
#endif /* !__sys_mlock_defined */
#endif /* sys_mlock... */
#if __CRT_HAVE_SC(mlockall)
#ifndef __sys_mlockall_defined
#define __sys_mlockall_defined 1
__CDECLARE_SC(,__errno_t,mlockall,(__syscall_ulong_t __flags),(__flags))
#endif /* !__sys_mlockall_defined */
#endif /* sys_mlockall... */
#if __CRT_HAVE_SC(mmap)
#ifndef __sys_mmap_defined
#define __sys_mmap_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
__CDECLARE_SC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#else /* #elif defined(__x86_64__) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
__CDECLARE_SC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* ... */
#endif /* !__sys_mmap_defined */
#endif /* sys_mmap... */
#if __CRT_HAVE_SC(mmap2)
#ifndef __sys_mmap2_defined
#define __sys_mmap2_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,void *,mmap2,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __pgoffset),(__addr,__len,__prot,__flags,__fd,__pgoffset))
#else /* ... */
#undef __sys_mmap2_defined
#endif /* !... */
#endif /* !__sys_mmap2_defined */
#endif /* sys_mmap2... */
#if __CRT_HAVE_SC(modify_ldt)
#ifndef __sys_modify_ldt_defined
#define __sys_modify_ldt_defined 1
__CDECLARE_SC(,__syscall_slong_t,modify_ldt,(__syscall_ulong_t __func, void *__ptr, __syscall_ulong_t __bytecount),(__func,__ptr,__bytecount))
#endif /* !__sys_modify_ldt_defined */
#endif /* sys_modify_ldt... */
#if __CRT_HAVE_SC(mount)
#ifndef __sys_mount_defined
#define __sys_mount_defined 1
__CDECLARE_SC(,__errno_t,mount,(char const *__special_file, char const *__dir, char const *__fstype, __syscall_ulong_t __rwflag, void const *__data),(__special_file,__dir,__fstype,__rwflag,__data))
#endif /* !__sys_mount_defined */
#endif /* sys_mount... */
#if __CRT_HAVE_SC(mprotect)
#ifndef __sys_mprotect_defined
#define __sys_mprotect_defined 1
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
__CDECLARE_SC(,__errno_t,mprotect,(void *__addr, __size_t __len, __syscall_ulong_t __prot),(__addr,__len,__prot))
#endif /* !__sys_mprotect_defined */
#endif /* sys_mprotect... */
#if __CRT_HAVE_SC(mremap)
#ifndef __sys_mremap_defined
#define __sys_mremap_defined 1
/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
__CDECLARE_SC(,void *,mremap,(void *__addr, __size_t __old_len, __size_t __new_len, __syscall_ulong_t __flags, void *__new_address),(__addr,__old_len,__new_len,__flags,__new_address))
#endif /* !__sys_mremap_defined */
#endif /* sys_mremap... */
#if __CRT_HAVE_SC(msync)
#ifndef __sys_msync_defined
#define __sys_msync_defined 1
__CDECLARE_SC(,__errno_t,msync,(void *__addr, __size_t __len, __syscall_ulong_t __flags),(__addr,__len,__flags))
#endif /* !__sys_msync_defined */
#endif /* sys_msync... */
#if __CRT_HAVE_SC(munlock)
#ifndef __sys_munlock_defined
#define __sys_munlock_defined 1
__CDECLARE_SC(,__errno_t,munlock,(void const *__addr, __size_t __len),(__addr,__len))
#endif /* !__sys_munlock_defined */
#endif /* sys_munlock... */
#if __CRT_HAVE_SC(munlockall)
#ifndef __sys_munlockall_defined
#define __sys_munlockall_defined 1
__CDECLARE_SC(,__errno_t,munlockall,(void),())
#endif /* !__sys_munlockall_defined */
#endif /* sys_munlockall... */
#if __CRT_HAVE_SC(munmap)
#ifndef __sys_munmap_defined
#define __sys_munmap_defined 1
__CDECLARE_SC(,__errno_t,munmap,(void *__addr, __size_t __len),(__addr,__len))
#endif /* !__sys_munmap_defined */
#endif /* sys_munmap... */
#if __CRT_HAVE_SC(name_to_handle_at)
#ifndef __sys_name_to_handle_at_defined
#define __sys_name_to_handle_at_defined 1
__CDECLARE_SC(,__errno_t,name_to_handle_at,(__fd_t __dirfd, char const *__name, struct file_handle *__handle, __int32_t *__mnt_id, __syscall_ulong_t __flags),(__dirfd,__name,__handle,__mnt_id,__flags))
#endif /* !__sys_name_to_handle_at_defined */
#endif /* sys_name_to_handle_at... */
#if __CRT_HAVE_SC(nanosleep)
#ifndef __sys_nanosleep_defined
#define __sys_nanosleep_defined 1
__CDECLARE_SC(,__errno_t,nanosleep,(struct __timespec32 const *__req, struct __timespec32 *__rem),(__req,__rem))
#endif /* !__sys_nanosleep_defined */
#endif /* sys_nanosleep... */
#if __CRT_HAVE_SC(nanosleep64)
#ifndef __sys_nanosleep64_defined
#define __sys_nanosleep64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,nanosleep64,(struct __timespec64 const *__req, struct __timespec64 *__rem),(__req,__rem))
#else /* ... */
#undef __sys_nanosleep64_defined
#endif /* !... */
#endif /* !__sys_nanosleep64_defined */
#endif /* sys_nanosleep64... */
#if __CRT_HAVE_SC(nice)
#ifndef __sys_nice_defined
#define __sys_nice_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,nice,(__syscall_slong_t __inc),(__inc))
#else /* ... */
#undef __sys_nice_defined
#endif /* !... */
#endif /* !__sys_nice_defined */
#endif /* sys_nice... */
#if __CRT_HAVE_SC(oldolduname)
#ifndef __sys_oldolduname_defined
#define __sys_oldolduname_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,oldolduname,(struct linux_oldolduname *__name),(__name))
#else /* ... */
#undef __sys_oldolduname_defined
#endif /* !... */
#endif /* !__sys_oldolduname_defined */
#endif /* sys_oldolduname... */
#if __CRT_HAVE_SC(olduname)
#ifndef __sys_olduname_defined
#define __sys_olduname_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,olduname,(struct linux_olduname *__name),(__name))
#else /* ... */
#undef __sys_olduname_defined
#endif /* !... */
#endif /* !__sys_olduname_defined */
#endif /* sys_olduname... */
#if __CRT_HAVE_SC(open)
#ifndef __sys_open_defined
#define __sys_open_defined 1
__CDECLARE_SC(,__fd_t,open,(char const *__filename, __oflag_t __oflags, __mode_t __mode),(__filename,__oflags,__mode))
#endif /* !__sys_open_defined */
#endif /* sys_open... */
#if __CRT_HAVE_SC(open_by_handle_at)
#ifndef __sys_open_by_handle_at_defined
#define __sys_open_by_handle_at_defined 1
__CDECLARE_SC(,__fd_t,open_by_handle_at,(__fd_t __mountdirfd, struct file_handle *__handle, __syscall_ulong_t __flags),(__mountdirfd,__handle,__flags))
#endif /* !__sys_open_by_handle_at_defined */
#endif /* sys_open_by_handle_at... */
#if __CRT_HAVE_SC(openat)
#ifndef __sys_openat_defined
#define __sys_openat_defined 1
__CDECLARE_SC(,__fd_t,openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, __mode_t __mode),(__dirfd,__filename,__oflags,__mode))
#endif /* !__sys_openat_defined */
#endif /* sys_openat... */
#if __CRT_HAVE_SC(openpty)
#ifndef __sys_openpty_defined
#define __sys_openpty_defined 1
/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
__CDECLARE_SC(,__errno_t,openpty,(__fd_t *__amaster, __fd_t *__aslave, char *__name, struct termios const *__termp, struct winsize const *__winp),(__amaster,__aslave,__name,__termp,__winp))
#endif /* !__sys_openpty_defined */
#endif /* sys_openpty... */
#if __CRT_HAVE_SC(pause)
#ifndef __sys_pause_defined
#define __sys_pause_defined 1
__CDECLARE_SC(,__errno_t,pause,(void),())
#endif /* !__sys_pause_defined */
#endif /* sys_pause... */
#if __CRT_HAVE_SC(pipe)
#ifndef __sys_pipe_defined
#define __sys_pipe_defined 1
__CDECLARE_SC(,__errno_t,pipe,(/*[2]*/ __fd_t *__pipedes),(__pipedes))
#endif /* !__sys_pipe_defined */
#endif /* sys_pipe... */
#if __CRT_HAVE_SC(pipe2)
#ifndef __sys_pipe2_defined
#define __sys_pipe2_defined 1
__CDECLARE_SC(,__errno_t,pipe2,(/*[2]*/ __fd_t *__pipedes, __oflag_t __flags),(__pipedes,__flags))
#endif /* !__sys_pipe2_defined */
#endif /* sys_pipe2... */
#if __CRT_HAVE_SC(poll)
#ifndef __sys_poll_defined
#define __sys_poll_defined 1
__CDECLARE_SC(,__ssize_t,poll,(struct pollfd *__fds, __size_t __nfds, __syscall_slong_t __timeout),(__fds,__nfds,__timeout))
#endif /* !__sys_poll_defined */
#endif /* sys_poll... */
#if __CRT_HAVE_SC(ppoll)
#ifndef __sys_ppoll_defined
#define __sys_ppoll_defined 1
__CDECLARE_SC(,__ssize_t,ppoll,(struct pollfd *__fds, __size_t __nfds, struct __timespec32 const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* !__sys_ppoll_defined */
#endif /* sys_ppoll... */
#if __CRT_HAVE_SC(ppoll64)
#ifndef __sys_ppoll64_defined
#define __sys_ppoll64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__ssize_t,ppoll64,(struct pollfd *__fds, __size_t __nfds, struct __timespec64 const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#else /* ... */
#undef __sys_ppoll64_defined
#endif /* !... */
#endif /* !__sys_ppoll64_defined */
#endif /* sys_ppoll64... */
#if __CRT_HAVE_SC(pread64)
#ifndef __sys_pread64_defined
#define __sys_pread64_defined 1
__CDECLARE_SC(,__ssize_t,pread64,(__fd_t __fd, void *__buf, __size_t __bufsize, __uint64_t __offset),(__fd,__buf,__bufsize,__offset))
#endif /* !__sys_pread64_defined */
#endif /* sys_pread64... */
#if __CRT_HAVE_SC(pread64f)
#ifndef __sys_pread64f_defined
#define __sys_pread64f_defined 1
__CDECLARE_SC(,__ssize_t,pread64f,(__fd_t __fd, void *__buf, __size_t __bufsize, __uint64_t __offset, __iomode_t __mode),(__fd,__buf,__bufsize,__offset,__mode))
#endif /* !__sys_pread64f_defined */
#endif /* sys_pread64f... */
#if __CRT_HAVE_SC(preadv)
#ifndef __sys_preadv_defined
#define __sys_preadv_defined 1
__CDECLARE_SC(,__ssize_t,preadv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* !__sys_preadv_defined */
#endif /* sys_preadv... */
#if __CRT_HAVE_SC(preadvf)
#ifndef __sys_preadvf_defined
#define __sys_preadvf_defined 1
__CDECLARE_SC(,__ssize_t,preadvf,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset, __iomode_t __mode),(__fd,__iovec,__count,__offset,__mode))
#endif /* !__sys_preadvf_defined */
#endif /* sys_preadvf... */
#if __CRT_HAVE_SC(prlimit64)
#ifndef __sys_prlimit64_defined
#define __sys_prlimit64_defined 1
/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
__CDECLARE_SC(,__errno_t,prlimit64,(__pid_t __pid, __syscall_ulong_t __resource, struct rlimit64 const *__new_limit, struct rlimit64 *__old_limit),(__pid,__resource,__new_limit,__old_limit))
#endif /* !__sys_prlimit64_defined */
#endif /* sys_prlimit64... */
#if __CRT_HAVE_SC(process_vm_readv)
#ifndef __sys_process_vm_readv_defined
#define __sys_process_vm_readv_defined 1
__CDECLARE_SC(,__ssize_t,process_vm_readv,(__pid_t __pid, struct iovec const *__lvec, __size_t __liovcnt, struct iovec const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* !__sys_process_vm_readv_defined */
#endif /* sys_process_vm_readv... */
#if __CRT_HAVE_SC(process_vm_writev)
#ifndef __sys_process_vm_writev_defined
#define __sys_process_vm_writev_defined 1
__CDECLARE_SC(,__ssize_t,process_vm_writev,(__pid_t __pid, struct iovec const *__lvec, __size_t __liovcnt, struct iovec const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* !__sys_process_vm_writev_defined */
#endif /* sys_process_vm_writev... */
#if __CRT_HAVE_SC(profil)
#ifndef __sys_profil_defined
#define __sys_profil_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,profil,(__uint16_t *__sample_buffer, __size_t __size, __size_t __offset, __syscall_ulong_t __scale),(__sample_buffer,__size,__offset,__scale))
#else /* ... */
#undef __sys_profil_defined
#endif /* !... */
#endif /* !__sys_profil_defined */
#endif /* sys_profil... */
#if __CRT_HAVE_SC(pselect6)
#ifndef __sys_pselect6_defined
#define __sys_pselect6_defined 1
__CDECLARE_SC(,__ssize_t,pselect6,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timespec32 const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#endif /* !__sys_pselect6_defined */
#endif /* sys_pselect6... */
#if __CRT_HAVE_SC(pselect6_64)
#ifndef __sys_pselect6_64_defined
#define __sys_pselect6_64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__ssize_t,pselect6_64,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timespec64 const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#else /* ... */
#undef __sys_pselect6_64_defined
#endif /* !... */
#endif /* !__sys_pselect6_64_defined */
#endif /* sys_pselect6_64... */
#if __CRT_HAVE_SC(ptrace)
#ifndef __sys_ptrace_defined
#define __sys_ptrace_defined 1
__CDECLARE_SC(,__syscall_slong_t,ptrace,(__syscall_ulong_t __request, __pid_t __pid, void *__addr, void *__data),(__request,__pid,__addr,__data))
#endif /* !__sys_ptrace_defined */
#endif /* sys_ptrace... */
#if __CRT_HAVE_SC(pwrite64)
#ifndef __sys_pwrite64_defined
#define __sys_pwrite64_defined 1
__CDECLARE_SC(,__ssize_t,pwrite64,(__fd_t __fd, void const *__buf, __size_t __bufsize, __uint64_t __offset),(__fd,__buf,__bufsize,__offset))
#endif /* !__sys_pwrite64_defined */
#endif /* sys_pwrite64... */
#if __CRT_HAVE_SC(pwrite64f)
#ifndef __sys_pwrite64f_defined
#define __sys_pwrite64f_defined 1
__CDECLARE_SC(,__ssize_t,pwrite64f,(__fd_t __fd, void const *__buf, __size_t __bufsize, __uint64_t __offset, __iomode_t __mode),(__fd,__buf,__bufsize,__offset,__mode))
#endif /* !__sys_pwrite64f_defined */
#endif /* sys_pwrite64f... */
#if __CRT_HAVE_SC(pwritev)
#ifndef __sys_pwritev_defined
#define __sys_pwritev_defined 1
__CDECLARE_SC(,__ssize_t,pwritev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* !__sys_pwritev_defined */
#endif /* sys_pwritev... */
#if __CRT_HAVE_SC(pwritevf)
#ifndef __sys_pwritevf_defined
#define __sys_pwritevf_defined 1
__CDECLARE_SC(,__ssize_t,pwritevf,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset, __iomode_t __mode),(__fd,__iovec,__count,__offset,__mode))
#endif /* !__sys_pwritevf_defined */
#endif /* sys_pwritevf... */
#if __CRT_HAVE_SC(raiseat)
#ifndef __sys_raiseat_defined
#define __sys_raiseat_defined 1
/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
__CDECLARE_SC(,__errno_t,raiseat,(struct ucpustate const *__state, struct __siginfo_struct const *__si),(__state,__si))
#endif /* !__sys_raiseat_defined */
#endif /* sys_raiseat... */
#if __CRT_HAVE_SC(read)
#ifndef __sys_read_defined
#define __sys_read_defined 1
__CDECLARE_SC(,__ssize_t,read,(__fd_t __fd, void *__buf, __size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* !__sys_read_defined */
#endif /* sys_read... */
#if __CRT_HAVE_SC(readahead)
#ifndef __sys_readahead_defined
#define __sys_readahead_defined 1
__CDECLARE_SC(,__ssize_t,readahead,(__fd_t __fd, __uint64_t __offset, __size_t __count),(__fd,__offset,__count))
#endif /* !__sys_readahead_defined */
#endif /* sys_readahead... */
#if __CRT_HAVE_SC(readdir)
#ifndef __sys_readdir_defined
#define __sys_readdir_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
__CDECLARE_SC(,__errno_t,readdir,(__fd_t __fd, struct old_linux_dirent *__dirp, __size_t __count),(__fd,__dirp,__count))
#else /* ... */
#undef __sys_readdir_defined
#endif /* !... */
#endif /* !__sys_readdir_defined */
#endif /* sys_readdir... */
#if __CRT_HAVE_SC(readf)
#ifndef __sys_readf_defined
#define __sys_readf_defined 1
__CDECLARE_SC(,__ssize_t,readf,(__fd_t __fd, void *__buf, __size_t __bufsize, __iomode_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* !__sys_readf_defined */
#endif /* sys_readf... */
#if __CRT_HAVE_SC(readlink)
#ifndef __sys_readlink_defined
#define __sys_readlink_defined 1
__CDECLARE_SC(,__ssize_t,readlink,(char const *__path, char *__buf, __size_t __buflen),(__path,__buf,__buflen))
#endif /* !__sys_readlink_defined */
#endif /* sys_readlink... */
#if __CRT_HAVE_SC(readlinkat)
#ifndef __sys_readlinkat_defined
#define __sys_readlinkat_defined 1
__CDECLARE_SC(,__ssize_t,readlinkat,(__fd_t __dirfd, char const *__path, char *__buf, __size_t __buflen),(__dirfd,__path,__buf,__buflen))
#endif /* !__sys_readlinkat_defined */
#endif /* sys_readlinkat... */
#if __CRT_HAVE_SC(readv)
#ifndef __sys_readv_defined
#define __sys_readv_defined 1
__CDECLARE_SC(,__ssize_t,readv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* !__sys_readv_defined */
#endif /* sys_readv... */
#if __CRT_HAVE_SC(readvf)
#ifndef __sys_readvf_defined
#define __sys_readvf_defined 1
__CDECLARE_SC(,__ssize_t,readvf,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __iomode_t __mode),(__fd,__iovec,__count,__mode))
#endif /* !__sys_readvf_defined */
#endif /* sys_readvf... */
#if __CRT_HAVE_SC(reboot)
#ifndef __sys_reboot_defined
#define __sys_reboot_defined 1
/* @param: howto: One of the `RB_*' constants from <sys/reboot.h> */
__CDECLARE_SC(,__errno_t,reboot,(__syscall_ulong_t __how),(__how))
#endif /* !__sys_reboot_defined */
#endif /* sys_reboot... */
#if __CRT_HAVE_SC(recvfrom)
#ifndef __sys_recvfrom_defined
#define __sys_recvfrom_defined 1
__CDECLARE_SC(,__ssize_t,recvfrom,(__fd_t __sockfd, void *__buf, __size_t __bufsize, __syscall_ulong_t __flags, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__buf,__bufsize,__flags,__addr,__addr_len))
#endif /* !__sys_recvfrom_defined */
#endif /* sys_recvfrom... */
#if __CRT_HAVE_SC(recvmmsg)
#ifndef __sys_recvmmsg_defined
#define __sys_recvmmsg_defined 1
__CDECLARE_SC(,__ssize_t,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct __timespec32 *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#endif /* !__sys_recvmmsg_defined */
#endif /* sys_recvmmsg... */
#if __CRT_HAVE_SC(recvmmsg64)
#ifndef __sys_recvmmsg64_defined
#define __sys_recvmmsg64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__ssize_t,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct __timespec64 *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#else /* ... */
#undef __sys_recvmmsg64_defined
#endif /* !... */
#endif /* !__sys_recvmmsg64_defined */
#endif /* sys_recvmmsg64... */
#if __CRT_HAVE_SC(recvmsg)
#ifndef __sys_recvmsg_defined
#define __sys_recvmsg_defined 1
__CDECLARE_SC(,__ssize_t,recvmsg,(__fd_t __sockfd, struct msghdr *__message, __syscall_ulong_t __flags),(__sockfd,__message,__flags))
#endif /* !__sys_recvmsg_defined */
#endif /* sys_recvmsg... */
#if __CRT_HAVE_SC(remap_file_pages)
#ifndef __sys_remap_file_pages_defined
#define __sys_remap_file_pages_defined 1
__CDECLARE_SC(,__errno_t,remap_file_pages,(void *__start, __size_t __size, __syscall_ulong_t __prot, __size_t __pgoff, __syscall_ulong_t __flags),(__start,__size,__prot,__pgoff,__flags))
#endif /* !__sys_remap_file_pages_defined */
#endif /* sys_remap_file_pages... */
#if __CRT_HAVE_SC(removexattr)
#ifndef __sys_removexattr_defined
#define __sys_removexattr_defined 1
__CDECLARE_SC(,__errno_t,removexattr,(char const *__path, char const *__name),(__path,__name))
#endif /* !__sys_removexattr_defined */
#endif /* sys_removexattr... */
#if __CRT_HAVE_SC(rename)
#ifndef __sys_rename_defined
#define __sys_rename_defined 1
__CDECLARE_SC(,__errno_t,rename,(char const *__oldname, char const *__newname_or_path),(__oldname,__newname_or_path))
#endif /* !__sys_rename_defined */
#endif /* sys_rename... */
#if __CRT_HAVE_SC(renameat)
#ifndef __sys_renameat_defined
#define __sys_renameat_defined 1
__CDECLARE_SC(,__errno_t,renameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path),(__oldfd,__oldname,__newfd,__newname_or_path))
#endif /* !__sys_renameat_defined */
#endif /* sys_renameat... */
#if __CRT_HAVE_SC(renameat2)
#ifndef __sys_renameat2_defined
#define __sys_renameat2_defined 1
/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
__CDECLARE_SC(,__errno_t,renameat2,(__fd_t __olddirfd, char const *__oldpath, __fd_t __newdirfd, char const *__newpath, __syscall_ulong_t __flags),(__olddirfd,__oldpath,__newdirfd,__newpath,__flags))
#endif /* !__sys_renameat2_defined */
#endif /* sys_renameat2... */
#if __CRT_HAVE_SC(rmdir)
#ifndef __sys_rmdir_defined
#define __sys_rmdir_defined 1
__CDECLARE_SC(,__errno_t,rmdir,(char const *__path),(__path))
#endif /* !__sys_rmdir_defined */
#endif /* sys_rmdir... */
#if __CRT_HAVE_SC(rpc_schedule)
#ifndef __sys_rpc_schedule_defined
#define __sys_rpc_schedule_defined 1
/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
__CDECLARE_SC(,__syscall_slong_t,rpc_schedule,(__pid_t __target, __syscall_ulong_t __flags, __uint8_t const *__program, void **__arguments),(__target,__flags,__program,__arguments))
#endif /* !__sys_rpc_schedule_defined */
#endif /* sys_rpc_schedule... */
#if __CRT_HAVE_SC(rpc_service)
#ifndef __sys_rpc_service_defined
#define __sys_rpc_service_defined 1
__CDECLARE_SC(,__syscall_slong_t,rpc_service,(void),())
#endif /* !__sys_rpc_service_defined */
#endif /* sys_rpc_service... */
#if __CRT_HAVE_SC(rt_sigaction)
#ifndef __sys_rt_sigaction_defined
#define __sys_rt_sigaction_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,rt_sigaction,(__syscall_ulong_t __signo, struct sigaction const *__act, struct sigaction *__oact, __size_t __sigsetsize),(__signo,__act,__oact,__sigsetsize))
#endif /* !__sys_rt_sigaction_defined */
#endif /* sys_rt_sigaction... */
#if __CRT_HAVE_SC(rt_sigpending)
#ifndef __sys_rt_sigpending_defined
#define __sys_rt_sigpending_defined 1
__CDECLARE_SC(,__errno_t,rt_sigpending,(struct __sigset_struct *__set, __size_t __sigsetsize),(__set,__sigsetsize))
#endif /* !__sys_rt_sigpending_defined */
#endif /* sys_rt_sigpending... */
#if __CRT_HAVE_SC(rt_sigprocmask)
#ifndef __sys_rt_sigprocmask_defined
#define __sys_rt_sigprocmask_defined 1
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE_SC(,__errno_t,rt_sigprocmask,(__syscall_ulong_t __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset, __size_t __sigsetsize),(__how,__set,__oset,__sigsetsize))
#endif /* !__sys_rt_sigprocmask_defined */
#endif /* sys_rt_sigprocmask... */
#if __CRT_HAVE_SC(rt_sigqueueinfo)
#ifndef __sys_rt_sigqueueinfo_defined
#define __sys_rt_sigqueueinfo_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,rt_sigqueueinfo,(__pid_t __tgid, __syscall_ulong_t __signo, struct __siginfo_struct const *__uinfo),(__tgid,__signo,__uinfo))
#endif /* !__sys_rt_sigqueueinfo_defined */
#endif /* sys_rt_sigqueueinfo... */
#if __CRT_HAVE_SC(rt_sigreturn)
#ifndef __sys_rt_sigreturn_defined
#define __sys_rt_sigreturn_defined 1
#ifdef __x86_64__
__CDECLARE_VOID_SC(,rt_sigreturn,(void),())
#else /* ... */
#undef __sys_rt_sigreturn_defined
#endif /* !... */
#endif /* !__sys_rt_sigreturn_defined */
#endif /* sys_rt_sigreturn... */
#if __CRT_HAVE_SC(rt_sigsuspend)
#ifndef __sys_rt_sigsuspend_defined
#define __sys_rt_sigsuspend_defined 1
__CDECLARE_SC(,__errno_t,rt_sigsuspend,(struct __sigset_struct const *__set, __size_t __sigsetsize),(__set,__sigsetsize))
#endif /* !__sys_rt_sigsuspend_defined */
#endif /* sys_rt_sigsuspend... */
#if __CRT_HAVE_SC(rt_sigtimedwait)
#ifndef __sys_rt_sigtimedwait_defined
#define __sys_rt_sigtimedwait_defined 1
__CDECLARE_SC(,__syscall_slong_t,rt_sigtimedwait,(struct __sigset_struct const *__set, struct __siginfo_struct *__info, struct __timespec32 const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* !__sys_rt_sigtimedwait_defined */
#endif /* sys_rt_sigtimedwait... */
#if __CRT_HAVE_SC(rt_sigtimedwait64)
#ifndef __sys_rt_sigtimedwait64_defined
#define __sys_rt_sigtimedwait64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__syscall_slong_t,rt_sigtimedwait64,(struct __sigset_struct const *__set, struct __siginfo_struct *__info, struct __timespec64 const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#else /* ... */
#undef __sys_rt_sigtimedwait64_defined
#endif /* !... */
#endif /* !__sys_rt_sigtimedwait64_defined */
#endif /* sys_rt_sigtimedwait64... */
#if __CRT_HAVE_SC(rt_tgsigqueueinfo)
#ifndef __sys_rt_tgsigqueueinfo_defined
#define __sys_rt_tgsigqueueinfo_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,rt_tgsigqueueinfo,(__pid_t __tgid, __pid_t __tid, __syscall_ulong_t __signo, struct __siginfo_struct const *__uinfo),(__tgid,__tid,__signo,__uinfo))
#endif /* !__sys_rt_tgsigqueueinfo_defined */
#endif /* sys_rt_tgsigqueueinfo... */
#if __CRT_HAVE_SC(sched_get_priority_max)
#ifndef __sys_sched_get_priority_max_defined
#define __sys_sched_get_priority_max_defined 1
__CDECLARE_SC(,__syscall_slong_t,sched_get_priority_max,(__syscall_ulong_t __algorithm),(__algorithm))
#endif /* !__sys_sched_get_priority_max_defined */
#endif /* sys_sched_get_priority_max... */
#if __CRT_HAVE_SC(sched_get_priority_min)
#ifndef __sys_sched_get_priority_min_defined
#define __sys_sched_get_priority_min_defined 1
__CDECLARE_SC(,__syscall_slong_t,sched_get_priority_min,(__syscall_ulong_t __algorithm),(__algorithm))
#endif /* !__sys_sched_get_priority_min_defined */
#endif /* sys_sched_get_priority_min... */
#if __CRT_HAVE_SC(sched_getaffinity)
#ifndef __sys_sched_getaffinity_defined
#define __sys_sched_getaffinity_defined 1
__CDECLARE_SC(,__errno_t,sched_getaffinity,(__pid_t __pid, __size_t __cpusetsize, struct __cpu_set_struct *__cpuset),(__pid,__cpusetsize,__cpuset))
#endif /* !__sys_sched_getaffinity_defined */
#endif /* sys_sched_getaffinity... */
#if __CRT_HAVE_SC(sched_getparam)
#ifndef __sys_sched_getparam_defined
#define __sys_sched_getparam_defined 1
__CDECLARE_SC(,__errno_t,sched_getparam,(__pid_t __pid, struct sched_param *__param),(__pid,__param))
#endif /* !__sys_sched_getparam_defined */
#endif /* sys_sched_getparam... */
#if __CRT_HAVE_SC(sched_getscheduler)
#ifndef __sys_sched_getscheduler_defined
#define __sys_sched_getscheduler_defined 1
__CDECLARE_SC(,__syscall_slong_t,sched_getscheduler,(__pid_t __pid),(__pid))
#endif /* !__sys_sched_getscheduler_defined */
#endif /* sys_sched_getscheduler... */
#if __CRT_HAVE_SC(sched_rr_get_interval)
#ifndef __sys_sched_rr_get_interval_defined
#define __sys_sched_rr_get_interval_defined 1
__CDECLARE_SC(,__errno_t,sched_rr_get_interval,(__pid_t __pid, struct __timespec32 *__tms),(__pid,__tms))
#endif /* !__sys_sched_rr_get_interval_defined */
#endif /* sys_sched_rr_get_interval... */
#if __CRT_HAVE_SC(sched_rr_get_interval64)
#ifndef __sys_sched_rr_get_interval64_defined
#define __sys_sched_rr_get_interval64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),(__pid,__tms))
#else /* ... */
#undef __sys_sched_rr_get_interval64_defined
#endif /* !... */
#endif /* !__sys_sched_rr_get_interval64_defined */
#endif /* sys_sched_rr_get_interval64... */
#if __CRT_HAVE_SC(sched_setaffinity)
#ifndef __sys_sched_setaffinity_defined
#define __sys_sched_setaffinity_defined 1
__CDECLARE_SC(,__errno_t,sched_setaffinity,(__pid_t __pid, __size_t __cpusetsize, struct __cpu_set_struct const *__cpuset),(__pid,__cpusetsize,__cpuset))
#endif /* !__sys_sched_setaffinity_defined */
#endif /* sys_sched_setaffinity... */
#if __CRT_HAVE_SC(sched_setparam)
#ifndef __sys_sched_setparam_defined
#define __sys_sched_setparam_defined 1
__CDECLARE_SC(,__errno_t,sched_setparam,(__pid_t __pid, struct sched_param const *__param),(__pid,__param))
#endif /* !__sys_sched_setparam_defined */
#endif /* sys_sched_setparam... */
#if __CRT_HAVE_SC(sched_setscheduler)
#ifndef __sys_sched_setscheduler_defined
#define __sys_sched_setscheduler_defined 1
__CDECLARE_SC(,__errno_t,sched_setscheduler,(__pid_t __pid, __syscall_ulong_t __policy, struct sched_param const *__param),(__pid,__policy,__param))
#endif /* !__sys_sched_setscheduler_defined */
#endif /* sys_sched_setscheduler... */
#if __CRT_HAVE_SC(sched_yield)
#ifndef __sys_sched_yield_defined
#define __sys_sched_yield_defined 1
__CDECLARE_SC(,__errno_t,sched_yield,(void),())
#endif /* !__sys_sched_yield_defined */
#endif /* sys_sched_yield... */
#if __CRT_HAVE_SC(select)
#ifndef __sys_select_defined
#define __sys_select_defined 1
__CDECLARE_SC(,__ssize_t,select,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timeval32 *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* !__sys_select_defined */
#endif /* sys_select... */
#if __CRT_HAVE_SC(select64)
#ifndef __sys_select64_defined
#define __sys_select64_defined 1
__CDECLARE_SC(,__ssize_t,select64,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timeval64 *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* !__sys_select64_defined */
#endif /* sys_select64... */
#if __CRT_HAVE_SC(sendfile)
#ifndef __sys_sendfile_defined
#define __sys_sendfile_defined 1
__CDECLARE_SC(,__ssize_t,sendfile,(__fd_t __out_fd, __fd_t __in_fd, __syscall_ulong_t *__offset, __size_t __count),(__out_fd,__in_fd,__offset,__count))
#endif /* !__sys_sendfile_defined */
#endif /* sys_sendfile... */
#if __CRT_HAVE_SC(sendfile64)
#ifndef __sys_sendfile64_defined
#define __sys_sendfile64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__ssize_t,sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __uint64_t *__offset, __size_t __count),(__out_fd,__in_fd,__offset,__count))
#else /* ... */
#undef __sys_sendfile64_defined
#endif /* !... */
#endif /* !__sys_sendfile64_defined */
#endif /* sys_sendfile64... */
#if __CRT_HAVE_SC(sendmmsg)
#ifndef __sys_sendmmsg_defined
#define __sys_sendmmsg_defined 1
__CDECLARE_SC(,__ssize_t,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags),(__sockfd,__vmessages,__vlen,__flags))
#endif /* !__sys_sendmmsg_defined */
#endif /* sys_sendmmsg... */
#if __CRT_HAVE_SC(sendmsg)
#ifndef __sys_sendmsg_defined
#define __sys_sendmsg_defined 1
__CDECLARE_SC(,__ssize_t,sendmsg,(__fd_t __sockfd, struct msghdr const *__message, __syscall_ulong_t __flags),(__sockfd,__message,__flags))
#endif /* !__sys_sendmsg_defined */
#endif /* sys_sendmsg... */
#if __CRT_HAVE_SC(sendto)
#ifndef __sys_sendto_defined
#define __sys_sendto_defined 1
/* param flags: Set of `MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL|MSG_OOB' */
__CDECLARE_SC(,__ssize_t,sendto,(__fd_t __sockfd, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__buf,__bufsize,__flags,__addr,__addr_len))
#endif /* !__sys_sendto_defined */
#endif /* sys_sendto... */
#if __CRT_HAVE_SC(set_exception_handler)
#ifndef __sys_set_exception_handler_defined
#define __sys_set_exception_handler_defined 1
/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
__CDECLARE_SC(,__errno_t,set_exception_handler,(__syscall_ulong_t __mode, __except_handler_t __handler, void *__handler_sp),(__mode,__handler,__handler_sp))
#endif /* !__sys_set_exception_handler_defined */
#endif /* sys_set_exception_handler... */
#if __CRT_HAVE_SC(set_library_listdef)
#ifndef __sys_set_library_listdef_defined
#define __sys_set_library_listdef_defined 1
/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
__CDECLARE_SC(,__errno_t,set_library_listdef,(struct library_listdef const *__listdef),(__listdef))
#endif /* !__sys_set_library_listdef_defined */
#endif /* sys_set_library_listdef... */
#if __CRT_HAVE_SC(set_tid_address)
#ifndef __sys_set_tid_address_defined
#define __sys_set_tid_address_defined 1
__CDECLARE_SC(,__pid_t,set_tid_address,(__pid_t *__tidptr),(__tidptr))
#endif /* !__sys_set_tid_address_defined */
#endif /* sys_set_tid_address... */
#if __CRT_HAVE_SC(setdomainname)
#ifndef __sys_setdomainname_defined
#define __sys_setdomainname_defined 1
__CDECLARE_SC(,__errno_t,setdomainname,(char const *__name, __size_t __len),(__name,__len))
#endif /* !__sys_setdomainname_defined */
#endif /* sys_setdomainname... */
#if __CRT_HAVE_SC(setfsgid)
#ifndef __sys_setfsgid_defined
#define __sys_setfsgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,setfsgid,(__uint16_t __gid),(__gid))
#else /* ... */
#undef __sys_setfsgid_defined
#endif /* !... */
#endif /* !__sys_setfsgid_defined */
#endif /* sys_setfsgid... */
#if __CRT_HAVE_SC(setfsgid32)
#ifndef __sys_setfsgid32_defined
#define __sys_setfsgid32_defined 1
__CDECLARE_SC(,__errno_t,setfsgid32,(__uint32_t __gid),(__gid))
#endif /* !__sys_setfsgid32_defined */
#endif /* sys_setfsgid32... */
#if __CRT_HAVE_SC(setfsuid)
#ifndef __sys_setfsuid_defined
#define __sys_setfsuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,setfsuid,(__uint16_t __uid),(__uid))
#else /* ... */
#undef __sys_setfsuid_defined
#endif /* !... */
#endif /* !__sys_setfsuid_defined */
#endif /* sys_setfsuid... */
#if __CRT_HAVE_SC(setfsuid32)
#ifndef __sys_setfsuid32_defined
#define __sys_setfsuid32_defined 1
__CDECLARE_SC(,__errno_t,setfsuid32,(__uint32_t __uid),(__uid))
#endif /* !__sys_setfsuid32_defined */
#endif /* sys_setfsuid32... */
#if __CRT_HAVE_SC(setgid)
#ifndef __sys_setgid_defined
#define __sys_setgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,setgid,(__uint16_t __gid),(__gid))
#else /* ... */
#undef __sys_setgid_defined
#endif /* !... */
#endif /* !__sys_setgid_defined */
#endif /* sys_setgid... */
#if __CRT_HAVE_SC(setgid32)
#ifndef __sys_setgid32_defined
#define __sys_setgid32_defined 1
__CDECLARE_SC(,__errno_t,setgid32,(__uint32_t __gid),(__gid))
#endif /* !__sys_setgid32_defined */
#endif /* sys_setgid32... */
#if __CRT_HAVE_SC(setgroups)
#ifndef __sys_setgroups_defined
#define __sys_setgroups_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,setgroups,(__size_t __count, __uint16_t const *__groups),(__count,__groups))
#else /* ... */
#undef __sys_setgroups_defined
#endif /* !... */
#endif /* !__sys_setgroups_defined */
#endif /* sys_setgroups... */
#if __CRT_HAVE_SC(setgroups32)
#ifndef __sys_setgroups32_defined
#define __sys_setgroups32_defined 1
__CDECLARE_SC(,__errno_t,setgroups32,(__size_t __count, __uint32_t const *__groups),(__count,__groups))
#endif /* !__sys_setgroups32_defined */
#endif /* sys_setgroups32... */
#if __CRT_HAVE_SC(sethostname)
#ifndef __sys_sethostname_defined
#define __sys_sethostname_defined 1
__CDECLARE_SC(,__errno_t,sethostname,(char const *__name, __size_t __len),(__name,__len))
#endif /* !__sys_sethostname_defined */
#endif /* sys_sethostname... */
#if __CRT_HAVE_SC(setitimer)
#ifndef __sys_setitimer_defined
#define __sys_setitimer_defined 1
__CDECLARE_SC(,__errno_t,setitimer,(__syscall_ulong_t __which, struct __itimerval32 const *__newval, struct __itimerval32 *__oldval),(__which,__newval,__oldval))
#endif /* !__sys_setitimer_defined */
#endif /* sys_setitimer... */
#if __CRT_HAVE_SC(setitimer64)
#ifndef __sys_setitimer64_defined
#define __sys_setitimer64_defined 1
__CDECLARE_SC(,__errno_t,setitimer64,(__syscall_ulong_t __which, struct __itimerval64 const *__newval, struct __itimerval64 *__oldval),(__which,__newval,__oldval))
#endif /* !__sys_setitimer64_defined */
#endif /* sys_setitimer64... */
#if __CRT_HAVE_SC(setns)
#ifndef __sys_setns_defined
#define __sys_setns_defined 1
__CDECLARE_SC(,__errno_t,setns,(__fd_t __fd, __syscall_ulong_t __nstype),(__fd,__nstype))
#endif /* !__sys_setns_defined */
#endif /* sys_setns... */
#if __CRT_HAVE_SC(setpgid)
#ifndef __sys_setpgid_defined
#define __sys_setpgid_defined 1
__CDECLARE_SC(,__errno_t,setpgid,(__pid_t __pid, __pid_t __pgid),(__pid,__pgid))
#endif /* !__sys_setpgid_defined */
#endif /* sys_setpgid... */
#if __CRT_HAVE_SC(setpriority)
#ifndef __sys_setpriority_defined
#define __sys_setpriority_defined 1
__CDECLARE_SC(,__errno_t,setpriority,(__syscall_ulong_t __which, __id_t __who, __syscall_ulong_t __value),(__which,__who,__value))
#endif /* !__sys_setpriority_defined */
#endif /* sys_setpriority... */
#if __CRT_HAVE_SC(setregid)
#ifndef __sys_setregid_defined
#define __sys_setregid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,setregid,(__uint16_t __rgid, __uint16_t __egid),(__rgid,__egid))
#else /* ... */
#undef __sys_setregid_defined
#endif /* !... */
#endif /* !__sys_setregid_defined */
#endif /* sys_setregid... */
#if __CRT_HAVE_SC(setregid32)
#ifndef __sys_setregid32_defined
#define __sys_setregid32_defined 1
__CDECLARE_SC(,__errno_t,setregid32,(__uint32_t __rgid, __uint32_t __egid),(__rgid,__egid))
#endif /* !__sys_setregid32_defined */
#endif /* sys_setregid32... */
#if __CRT_HAVE_SC(setresgid)
#ifndef __sys_setresgid_defined
#define __sys_setresgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,setresgid,(__uint16_t __rgid, __uint16_t __egid, __uint16_t __sgid),(__rgid,__egid,__sgid))
#else /* ... */
#undef __sys_setresgid_defined
#endif /* !... */
#endif /* !__sys_setresgid_defined */
#endif /* sys_setresgid... */
#if __CRT_HAVE_SC(setresgid32)
#ifndef __sys_setresgid32_defined
#define __sys_setresgid32_defined 1
__CDECLARE_SC(,__errno_t,setresgid32,(__uint32_t __rgid, __uint32_t __egid, __uint32_t __sgid),(__rgid,__egid,__sgid))
#endif /* !__sys_setresgid32_defined */
#endif /* sys_setresgid32... */
#if __CRT_HAVE_SC(setresuid)
#ifndef __sys_setresuid_defined
#define __sys_setresuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,setresuid,(__uint16_t __ruid, __uint16_t __euid, __uint16_t __suid),(__ruid,__euid,__suid))
#else /* ... */
#undef __sys_setresuid_defined
#endif /* !... */
#endif /* !__sys_setresuid_defined */
#endif /* sys_setresuid... */
#if __CRT_HAVE_SC(setresuid32)
#ifndef __sys_setresuid32_defined
#define __sys_setresuid32_defined 1
__CDECLARE_SC(,__errno_t,setresuid32,(__uint32_t __ruid, __uint32_t __euid, __uint32_t __suid),(__ruid,__euid,__suid))
#endif /* !__sys_setresuid32_defined */
#endif /* sys_setresuid32... */
#if __CRT_HAVE_SC(setreuid)
#ifndef __sys_setreuid_defined
#define __sys_setreuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,setreuid,(__uint16_t __ruid, __uint16_t __euid),(__ruid,__euid))
#else /* ... */
#undef __sys_setreuid_defined
#endif /* !... */
#endif /* !__sys_setreuid_defined */
#endif /* sys_setreuid... */
#if __CRT_HAVE_SC(setreuid32)
#ifndef __sys_setreuid32_defined
#define __sys_setreuid32_defined 1
__CDECLARE_SC(,__errno_t,setreuid32,(__uint32_t __ruid, __uint32_t __euid),(__ruid,__euid))
#endif /* !__sys_setreuid32_defined */
#endif /* sys_setreuid32... */
#if __CRT_HAVE_SC(setrlimit)
#ifndef __sys_setrlimit_defined
#define __sys_setrlimit_defined 1
__CDECLARE_SC(,__errno_t,setrlimit,(__syscall_ulong_t __resource, struct rlimit const *__rlimits),(__resource,__rlimits))
#endif /* !__sys_setrlimit_defined */
#endif /* sys_setrlimit... */
#if __CRT_HAVE_SC(setsid)
#ifndef __sys_setsid_defined
#define __sys_setsid_defined 1
__CDECLARE_SC(,__pid_t,setsid,(void),())
#endif /* !__sys_setsid_defined */
#endif /* sys_setsid... */
#if __CRT_HAVE_SC(setsockopt)
#ifndef __sys_setsockopt_defined
#define __sys_setsockopt_defined 1
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
__CDECLARE_SC(,__errno_t,setsockopt,(__fd_t __sockfd, __syscall_ulong_t __level, __syscall_ulong_t __optname, void const *__optval, __socklen_t __optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* !__sys_setsockopt_defined */
#endif /* sys_setsockopt... */
#if __CRT_HAVE_SC(settimeofday)
#ifndef __sys_settimeofday_defined
#define __sys_settimeofday_defined 1
__CDECLARE_SC(,__errno_t,settimeofday,(struct __timeval32 const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* !__sys_settimeofday_defined */
#endif /* sys_settimeofday... */
#if __CRT_HAVE_SC(settimeofday64)
#ifndef __sys_settimeofday64_defined
#define __sys_settimeofday64_defined 1
__CDECLARE_SC(,__errno_t,settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* !__sys_settimeofday64_defined */
#endif /* sys_settimeofday64... */
#if __CRT_HAVE_SC(setuid)
#ifndef __sys_setuid_defined
#define __sys_setuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,setuid,(__uint16_t __uid),(__uid))
#else /* ... */
#undef __sys_setuid_defined
#endif /* !... */
#endif /* !__sys_setuid_defined */
#endif /* sys_setuid... */
#if __CRT_HAVE_SC(setuid32)
#ifndef __sys_setuid32_defined
#define __sys_setuid32_defined 1
__CDECLARE_SC(,__errno_t,setuid32,(__uint32_t __uid),(__uid))
#endif /* !__sys_setuid32_defined */
#endif /* sys_setuid32... */
#if __CRT_HAVE_SC(setxattr)
#ifndef __sys_setxattr_defined
#define __sys_setxattr_defined 1
__CDECLARE_SC(,__errno_t,setxattr,(char const *__path, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__path,__name,__buf,__bufsize,__flags))
#endif /* !__sys_setxattr_defined */
#endif /* sys_setxattr... */
#if __CRT_HAVE_SC(sgetmask)
#ifndef __sys_sgetmask_defined
#define __sys_sgetmask_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__syscall_ulong_t,sgetmask,(void),())
#else /* ... */
#undef __sys_sgetmask_defined
#endif /* !... */
#endif /* !__sys_sgetmask_defined */
#endif /* sys_sgetmask... */
#if __CRT_HAVE_SC(shutdown)
#ifndef __sys_shutdown_defined
#define __sys_shutdown_defined 1
/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
__CDECLARE_SC(,__errno_t,shutdown,(__fd_t __sockfd, __syscall_ulong_t __how),(__sockfd,__how))
#endif /* !__sys_shutdown_defined */
#endif /* sys_shutdown... */
#if __CRT_HAVE_SC(sigaction)
#ifndef __sys_sigaction_defined
#define __sys_sigaction_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,sigaction,(__syscall_ulong_t __signo, struct sigaction const *__act, struct sigaction *__oact),(__signo,__act,__oact))
#else /* ... */
#undef __sys_sigaction_defined
#endif /* !... */
#endif /* !__sys_sigaction_defined */
#endif /* sys_sigaction... */
#if __CRT_HAVE_SC(sigaltstack)
#ifndef __sys_sigaltstack_defined
#define __sys_sigaltstack_defined 1
__CDECLARE_SC(,__errno_t,sigaltstack,(struct sigaltstack const *__ss, struct sigaltstack *__oss),(__ss,__oss))
#endif /* !__sys_sigaltstack_defined */
#endif /* sys_sigaltstack... */
#if __CRT_HAVE_SC(signal)
#ifndef __sys_signal_defined
#define __sys_signal_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__sighandler_t,signal,(__syscall_ulong_t __signo, __sighandler_t __handler),(__signo,__handler))
#else /* ... */
#undef __sys_signal_defined
#endif /* !... */
#endif /* !__sys_signal_defined */
#endif /* sys_signal... */
#if __CRT_HAVE_SC(signalfd)
#ifndef __sys_signalfd_defined
#define __sys_signalfd_defined 1
__CDECLARE_SC(,__errno_t,signalfd,(__fd_t __fd, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fd,__sigmask,__sigsetsize))
#endif /* !__sys_signalfd_defined */
#endif /* sys_signalfd... */
#if __CRT_HAVE_SC(signalfd4)
#ifndef __sys_signalfd4_defined
#define __sys_signalfd4_defined 1
__CDECLARE_SC(,__errno_t,signalfd4,(__fd_t __fd, struct __sigset_struct const *__sigmask, __size_t __sigsetsize, __syscall_ulong_t __flags),(__fd,__sigmask,__sigsetsize,__flags))
#endif /* !__sys_signalfd4_defined */
#endif /* sys_signalfd4... */
#if __CRT_HAVE_SC(sigpending)
#ifndef __sys_sigpending_defined
#define __sys_sigpending_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,sigpending,(struct __sigset_struct *__set),(__set))
#else /* ... */
#undef __sys_sigpending_defined
#endif /* !... */
#endif /* !__sys_sigpending_defined */
#endif /* sys_sigpending... */
#if __CRT_HAVE_SC(sigprocmask)
#ifndef __sys_sigprocmask_defined
#define __sys_sigprocmask_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE_SC(,__errno_t,sigprocmask,(__syscall_ulong_t __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),(__how,__set,__oset))
#else /* ... */
#undef __sys_sigprocmask_defined
#endif /* !... */
#endif /* !__sys_sigprocmask_defined */
#endif /* sys_sigprocmask... */
#if __CRT_HAVE_SC(sigreturn)
#ifndef __sys_sigreturn_defined
#define __sys_sigreturn_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
__CDECLARE_VOID_SC(,sigreturn,(struct fpustate const *__restore_fpu, __syscall_ulong_t __unused1, __syscall_ulong_t __unused2, struct __sigset_struct const *__restore_sigmask, struct rpc_syscall_info *__sc_info, struct ucpustate const *__restore_cpu),(__restore_fpu,__unused1,__unused2,__restore_sigmask,__sc_info,__restore_cpu))
#else /* ... */
#undef __sys_sigreturn_defined
#endif /* !... */
#endif /* !__sys_sigreturn_defined */
#endif /* sys_sigreturn... */
#if __CRT_HAVE_SC(sigsuspend)
#ifndef __sys_sigsuspend_defined
#define __sys_sigsuspend_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,sigsuspend,(struct __sigset_struct const *__set),(__set))
#else /* ... */
#undef __sys_sigsuspend_defined
#endif /* !... */
#endif /* !__sys_sigsuspend_defined */
#endif /* sys_sigsuspend... */
#if __CRT_HAVE_SC(socket)
#ifndef __sys_socket_defined
#define __sys_socket_defined 1
__CDECLARE_SC(,__fd_t,socket,(__syscall_ulong_t __domain, __syscall_ulong_t __type, __syscall_ulong_t __protocol),(__domain,__type,__protocol))
#endif /* !__sys_socket_defined */
#endif /* sys_socket... */
#if __CRT_HAVE_SC(socketcall)
#ifndef __sys_socketcall_defined
#define __sys_socketcall_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,socketcall,(int __call, unsigned long *__args),(__call,__args))
#else /* ... */
#undef __sys_socketcall_defined
#endif /* !... */
#endif /* !__sys_socketcall_defined */
#endif /* sys_socketcall... */
#if __CRT_HAVE_SC(socketpair)
#ifndef __sys_socketpair_defined
#define __sys_socketpair_defined 1
__CDECLARE_SC(,__errno_t,socketpair,(__syscall_ulong_t __domain, __syscall_ulong_t __type, __syscall_ulong_t __protocol, /*[2]*/ __fd_t *__fds),(__domain,__type,__protocol,__fds))
#endif /* !__sys_socketpair_defined */
#endif /* sys_socketpair... */
#if __CRT_HAVE_SC(splice)
#ifndef __sys_splice_defined
#define __sys_splice_defined 1
__CDECLARE_SC(,__ssize_t,splice,(__fd_t __fdin, __uint64_t *__offin, __fd_t __fdout, __uint64_t *__offout, __size_t __length, __syscall_ulong_t __flags),(__fdin,__offin,__fdout,__offout,__length,__flags))
#endif /* !__sys_splice_defined */
#endif /* sys_splice... */
#if __CRT_HAVE_SC(ssetmask)
#ifndef __sys_ssetmask_defined
#define __sys_ssetmask_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__syscall_ulong_t,ssetmask,(__syscall_ulong_t __sigmask),(__sigmask))
#else /* ... */
#undef __sys_ssetmask_defined
#endif /* !... */
#endif /* !__sys_ssetmask_defined */
#endif /* sys_ssetmask... */
#if __CRT_HAVE_SC(statfs)
#ifndef __sys_statfs_defined
#define __sys_statfs_defined 1
__CDECLARE_SC(,__errno_t,statfs,(char const *__file, struct __statfs32 *__buf),(__file,__buf))
#endif /* !__sys_statfs_defined */
#endif /* sys_statfs... */
#if __CRT_HAVE_SC(statfs64)
#ifndef __sys_statfs64_defined
#define __sys_statfs64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,statfs64,(char const *__file, struct statfs64 *__buf),(__file,__buf))
#else /* ... */
#undef __sys_statfs64_defined
#endif /* !... */
#endif /* !__sys_statfs64_defined */
#endif /* sys_statfs64... */
#if __CRT_HAVE_SC(stime)
#ifndef __sys_stime_defined
#define __sys_stime_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,stime,(__time32_t const *__t),(__t))
#else /* ... */
#undef __sys_stime_defined
#endif /* !... */
#endif /* !__sys_stime_defined */
#endif /* sys_stime... */
#if __CRT_HAVE_SC(stime64)
#ifndef __sys_stime64_defined
#define __sys_stime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,stime64,(__time64_t const *__t),(__t))
#else /* ... */
#undef __sys_stime64_defined
#endif /* !... */
#endif /* !__sys_stime64_defined */
#endif /* sys_stime64... */
#if __CRT_HAVE_SC(swapoff)
#ifndef __sys_swapoff_defined
#define __sys_swapoff_defined 1
__CDECLARE_SC(,__errno_t,swapoff,(char const *__pathname),(__pathname))
#endif /* !__sys_swapoff_defined */
#endif /* sys_swapoff... */
#if __CRT_HAVE_SC(swapon)
#ifndef __sys_swapon_defined
#define __sys_swapon_defined 1
/* @param: swapflags: Set of `SWAP_FLAG_*' */
__CDECLARE_SC(,__errno_t,swapon,(char const *__pathname, __syscall_ulong_t __swapflags),(__pathname,__swapflags))
#endif /* !__sys_swapon_defined */
#endif /* sys_swapon... */
#if __CRT_HAVE_SC(symlink)
#ifndef __sys_symlink_defined
#define __sys_symlink_defined 1
__CDECLARE_SC(,__errno_t,symlink,(char const *__link_text, char const *__target_path),(__link_text,__target_path))
#endif /* !__sys_symlink_defined */
#endif /* sys_symlink... */
#if __CRT_HAVE_SC(symlinkat)
#ifndef __sys_symlinkat_defined
#define __sys_symlinkat_defined 1
__CDECLARE_SC(,__errno_t,symlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path),(__link_text,__tofd,__target_path))
#endif /* !__sys_symlinkat_defined */
#endif /* sys_symlinkat... */
#if __CRT_HAVE_SC(sync)
#ifndef __sys_sync_defined
#define __sys_sync_defined 1
__CDECLARE_SC(,__errno_t,sync,(void),())
#endif /* !__sys_sync_defined */
#endif /* sys_sync... */
#if __CRT_HAVE_SC(sync_file_range)
#ifndef __sys_sync_file_range_defined
#define __sys_sync_file_range_defined 1
__CDECLARE_SC(,__errno_t,sync_file_range,(__fd_t __fd, __uint64_t __offset, __uint64_t __count, __syscall_ulong_t __flags),(__fd,__offset,__count,__flags))
#endif /* !__sys_sync_file_range_defined */
#endif /* sys_sync_file_range... */
#if __CRT_HAVE_SC(syncfs)
#ifndef __sys_syncfs_defined
#define __sys_syncfs_defined 1
__CDECLARE_SC(,__errno_t,syncfs,(__fd_t __fd),(__fd))
#endif /* !__sys_syncfs_defined */
#endif /* sys_syncfs... */
#if __CRT_HAVE_SC(sysctl)
#ifndef __sys_sysctl_defined
#define __sys_sysctl_defined 1
__CDECLARE_SC(,__syscall_slong_t,sysctl,(__syscall_ulong_t __command, void *__arg),(__command,__arg))
#endif /* !__sys_sysctl_defined */
#endif /* sys_sysctl... */
#if __CRT_HAVE_SC(sysinfo)
#ifndef __sys_sysinfo_defined
#define __sys_sysinfo_defined 1
__CDECLARE_SC(,__errno_t,sysinfo,(struct sysinfo *__info),(__info))
#endif /* !__sys_sysinfo_defined */
#endif /* sys_sysinfo... */
#if __CRT_HAVE_SC(syslog)
#ifndef __sys_syslog_defined
#define __sys_syslog_defined 1
__CDECLARE_SC(,__ssize_t,syslog,(__syscall_ulong_t __level, char const *__str, __size_t __len),(__level,__str,__len))
#endif /* !__sys_syslog_defined */
#endif /* sys_syslog... */
#if __CRT_HAVE_SC(tee)
#ifndef __sys_tee_defined
#define __sys_tee_defined 1
__CDECLARE_SC(,__ssize_t,tee,(__fd_t __fdin, __fd_t __fdout, __size_t __length, __syscall_ulong_t __flags),(__fdin,__fdout,__length,__flags))
#endif /* !__sys_tee_defined */
#endif /* sys_tee... */
#if __CRT_HAVE_SC(tgkill)
#ifndef __sys_tgkill_defined
#define __sys_tgkill_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,tgkill,(__pid_t __tgid, __pid_t __tid, __syscall_ulong_t __signo),(__tgid,__tid,__signo))
#endif /* !__sys_tgkill_defined */
#endif /* sys_tgkill... */
#if __CRT_HAVE_SC(time)
#ifndef __sys_time_defined
#define __sys_time_defined 1
__CDECLARE_SC(,__time32_t,time,(__time32_t *__timer),(__timer))
#endif /* !__sys_time_defined */
#endif /* sys_time... */
#if __CRT_HAVE_SC(time64)
#ifndef __sys_time64_defined
#define __sys_time64_defined 1
__CDECLARE_SC(,__time64_t,time64,(__time64_t *__timer),(__timer))
#endif /* !__sys_time64_defined */
#endif /* sys_time64... */
#if __CRT_HAVE_SC(timer_create)
#ifndef __sys_timer_create_defined
#define __sys_timer_create_defined 1
__CDECLARE_SC(,__errno_t,timer_create,(__clockid_t __clock_id, struct sigevent *__evp, __timer_t *__timerid),(__clock_id,__evp,__timerid))
#endif /* !__sys_timer_create_defined */
#endif /* sys_timer_create... */
#if __CRT_HAVE_SC(timer_delete)
#ifndef __sys_timer_delete_defined
#define __sys_timer_delete_defined 1
__CDECLARE_SC(,__errno_t,timer_delete,(__timer_t __timerid),(__timerid))
#endif /* !__sys_timer_delete_defined */
#endif /* sys_timer_delete... */
#if __CRT_HAVE_SC(timer_getoverrun)
#ifndef __sys_timer_getoverrun_defined
#define __sys_timer_getoverrun_defined 1
__CDECLARE_SC(,__syscall_slong_t,timer_getoverrun,(__timer_t __timerid),(__timerid))
#endif /* !__sys_timer_getoverrun_defined */
#endif /* sys_timer_getoverrun... */
#if __CRT_HAVE_SC(timer_gettime)
#ifndef __sys_timer_gettime_defined
#define __sys_timer_gettime_defined 1
__CDECLARE_SC(,__errno_t,timer_gettime,(__timer_t __timerid, struct __itimerspec32 *__value),(__timerid,__value))
#endif /* !__sys_timer_gettime_defined */
#endif /* sys_timer_gettime... */
#if __CRT_HAVE_SC(timer_gettime64)
#ifndef __sys_timer_gettime64_defined
#define __sys_timer_gettime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,timer_gettime64,(__timer_t __timerid, struct __itimerspec64 *__value),(__timerid,__value))
#else /* ... */
#undef __sys_timer_gettime64_defined
#endif /* !... */
#endif /* !__sys_timer_gettime64_defined */
#endif /* sys_timer_gettime64... */
#if __CRT_HAVE_SC(timer_settime)
#ifndef __sys_timer_settime_defined
#define __sys_timer_settime_defined 1
__CDECLARE_SC(,__errno_t,timer_settime,(__timer_t __timerid, __syscall_ulong_t __flags, struct __itimerspec32 const *__value, struct __itimerspec32 *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* !__sys_timer_settime_defined */
#endif /* sys_timer_settime... */
#if __CRT_HAVE_SC(timer_settime64)
#ifndef __sys_timer_settime64_defined
#define __sys_timer_settime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,timer_settime64,(__timer_t __timerid, __syscall_ulong_t __flags, struct __itimerspec64 const *__value, struct __itimerspec64 *__ovalue),(__timerid,__flags,__value,__ovalue))
#else /* ... */
#undef __sys_timer_settime64_defined
#endif /* !... */
#endif /* !__sys_timer_settime64_defined */
#endif /* sys_timer_settime64... */
#if __CRT_HAVE_SC(timerfd_create)
#ifndef __sys_timerfd_create_defined
#define __sys_timerfd_create_defined 1
/* Return file descriptor for new interval timer source */
__CDECLARE_SC(,__fd_t,timerfd_create,(__clockid_t __clock_id, __syscall_ulong_t __flags),(__clock_id,__flags))
#endif /* !__sys_timerfd_create_defined */
#endif /* sys_timerfd_create... */
#if __CRT_HAVE_SC(timerfd_gettime)
#ifndef __sys_timerfd_gettime_defined
#define __sys_timerfd_gettime_defined 1
/* Return the next expiration time of UFD */
__CDECLARE_SC(,__errno_t,timerfd_gettime,(__fd_t __ufd, struct __itimerspec32 *__otmr),(__ufd,__otmr))
#endif /* !__sys_timerfd_gettime_defined */
#endif /* sys_timerfd_gettime... */
#if __CRT_HAVE_SC(timerfd_gettime64)
#ifndef __sys_timerfd_gettime64_defined
#define __sys_timerfd_gettime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* Return the next expiration time of UFD */
__CDECLARE_SC(,__errno_t,timerfd_gettime64,(__fd_t __ufd, struct __itimerspec64 *__otmr),(__ufd,__otmr))
#else /* ... */
#undef __sys_timerfd_gettime64_defined
#endif /* !... */
#endif /* !__sys_timerfd_gettime64_defined */
#endif /* sys_timerfd_gettime64... */
#if __CRT_HAVE_SC(timerfd_settime)
#ifndef __sys_timerfd_settime_defined
#define __sys_timerfd_settime_defined 1
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_SC(,__errno_t,timerfd_settime,(__fd_t __ufd, __syscall_ulong_t __flags, struct __itimerspec32 const *__utmr, struct __itimerspec32 *__otmr),(__ufd,__flags,__utmr,__otmr))
#endif /* !__sys_timerfd_settime_defined */
#endif /* sys_timerfd_settime... */
#if __CRT_HAVE_SC(timerfd_settime64)
#ifndef __sys_timerfd_settime64_defined
#define __sys_timerfd_settime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_SC(,__errno_t,timerfd_settime64,(__fd_t __ufd, __syscall_ulong_t __flags, struct __itimerspec64 const *__utmr, struct __itimerspec64 *__otmr),(__ufd,__flags,__utmr,__otmr))
#else /* ... */
#undef __sys_timerfd_settime64_defined
#endif /* !... */
#endif /* !__sys_timerfd_settime64_defined */
#endif /* sys_timerfd_settime64... */
#if __CRT_HAVE_SC(times)
#ifndef __sys_times_defined
#define __sys_times_defined 1
__CDECLARE_SC(,__clock_t,times,(struct tms *__buf),(__buf))
#endif /* !__sys_times_defined */
#endif /* sys_times... */
#if __CRT_HAVE_SC(tkill)
#ifndef __sys_tkill_defined
#define __sys_tkill_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,tkill,(__pid_t __tid, __syscall_ulong_t __signo),(__tid,__signo))
#endif /* !__sys_tkill_defined */
#endif /* sys_tkill... */
#if __CRT_HAVE_SC(truncate)
#ifndef __sys_truncate_defined
#define __sys_truncate_defined 1
__CDECLARE_SC(,__errno_t,truncate,(char const *__filename, __syscall_ulong_t __length),(__filename,__length))
#endif /* !__sys_truncate_defined */
#endif /* sys_truncate... */
#if __CRT_HAVE_SC(truncate64)
#ifndef __sys_truncate64_defined
#define __sys_truncate64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,truncate64,(char const *__filename, __uint64_t __length),(__filename,__length))
#else /* ... */
#undef __sys_truncate64_defined
#endif /* !... */
#endif /* !__sys_truncate64_defined */
#endif /* sys_truncate64... */
#if __CRT_HAVE_SC(umask)
#ifndef __sys_umask_defined
#define __sys_umask_defined 1
__CDECLARE_SC(,__mode_t,umask,(__mode_t __mode),(__mode))
#endif /* !__sys_umask_defined */
#endif /* sys_umask... */
#if __CRT_HAVE_SC(umount)
#ifndef __sys_umount_defined
#define __sys_umount_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_SC(,__errno_t,umount,(char const *__special_file),(__special_file))
#else /* ... */
#undef __sys_umount_defined
#endif /* !... */
#endif /* !__sys_umount_defined */
#endif /* sys_umount... */
#if __CRT_HAVE_SC(umount2)
#ifndef __sys_umount2_defined
#define __sys_umount2_defined 1
__CDECLARE_SC(,__errno_t,umount2,(char const *__special_file, __syscall_ulong_t __flags),(__special_file,__flags))
#endif /* !__sys_umount2_defined */
#endif /* sys_umount2... */
#if __CRT_HAVE_SC(uname)
#ifndef __sys_uname_defined
#define __sys_uname_defined 1
__CDECLARE_SC(,__errno_t,uname,(struct utsname *__name),(__name))
#endif /* !__sys_uname_defined */
#endif /* sys_uname... */
#if __CRT_HAVE_SC(unlink)
#ifndef __sys_unlink_defined
#define __sys_unlink_defined 1
__CDECLARE_SC(,__errno_t,unlink,(char const *__filename),(__filename))
#endif /* !__sys_unlink_defined */
#endif /* sys_unlink... */
#if __CRT_HAVE_SC(unlinkat)
#ifndef __sys_unlinkat_defined
#define __sys_unlinkat_defined 1
/* @param: flags: Set of `0|AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,unlinkat,(__fd_t __dirfd, char const *__name, __atflag_t __flags),(__dirfd,__name,__flags))
#endif /* !__sys_unlinkat_defined */
#endif /* sys_unlinkat... */
#if __CRT_HAVE_SC(unshare)
#ifndef __sys_unshare_defined
#define __sys_unshare_defined 1
/* param flags: Set of `CLONE_*' */
__CDECLARE_SC(,__errno_t,unshare,(__syscall_ulong_t __flags),(__flags))
#endif /* !__sys_unshare_defined */
#endif /* sys_unshare... */
#if __CRT_HAVE_SC(ustat)
#ifndef __sys_ustat_defined
#define __sys_ustat_defined 1
__CDECLARE_SC(,__errno_t,ustat,(__dev_t __dev, struct ustat *__ubuf),(__dev,__ubuf))
#endif /* !__sys_ustat_defined */
#endif /* sys_ustat... */
#if __CRT_HAVE_SC(utime)
#ifndef __sys_utime_defined
#define __sys_utime_defined 1
__CDECLARE_SC(,__errno_t,utime,(char const *__filename, struct __utimbuf32 const *__times),(__filename,__times))
#endif /* !__sys_utime_defined */
#endif /* sys_utime... */
#if __CRT_HAVE_SC(utime64)
#ifndef __sys_utime64_defined
#define __sys_utime64_defined 1
__CDECLARE_SC(,__errno_t,utime64,(char const *__filename, struct utimbuf64 const *__times),(__filename,__times))
#endif /* !__sys_utime64_defined */
#endif /* sys_utime64... */
#if __CRT_HAVE_SC(utimensat)
#ifndef __sys_utimensat_defined
#define __sys_utimensat_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,utimensat,(__fd_t __dirfd, char const *__filename, /*[2-3]*/ struct __timespec32 const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* !__sys_utimensat_defined */
#endif /* sys_utimensat... */
#if __CRT_HAVE_SC(utimensat64)
#ifndef __sys_utimensat64_defined
#define __sys_utimensat64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,utimensat64,(__fd_t __dirfd, char const *__filename, /*[2-3]*/ struct __timespec64 const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#else /* ... */
#undef __sys_utimensat64_defined
#endif /* !... */
#endif /* !__sys_utimensat64_defined */
#endif /* sys_utimensat64... */
#if __CRT_HAVE_SC(utimes)
#ifndef __sys_utimes_defined
#define __sys_utimes_defined 1
__CDECLARE_SC(,__errno_t,utimes,(char const *__filename, /*[2]*/ struct __timeval32 const *__times),(__filename,__times))
#endif /* !__sys_utimes_defined */
#endif /* sys_utimes... */
#if __CRT_HAVE_SC(utimes64)
#ifndef __sys_utimes64_defined
#define __sys_utimes64_defined 1
__CDECLARE_SC(,__errno_t,utimes64,(char const *__filename, /*[2]*/ struct __timeval64 const *__times),(__filename,__times))
#endif /* !__sys_utimes64_defined */
#endif /* sys_utimes64... */
#if __CRT_HAVE_SC(vfork)
#ifndef __sys_vfork_defined
#define __sys_vfork_defined 1
__CDECLARE_SC(,__pid_t,vfork,(void),())
#endif /* !__sys_vfork_defined */
#endif /* sys_vfork... */
#if __CRT_HAVE_SC(vhangup)
#ifndef __sys_vhangup_defined
#define __sys_vhangup_defined 1
__CDECLARE_SC(,__errno_t,vhangup,(void),())
#endif /* !__sys_vhangup_defined */
#endif /* sys_vhangup... */
#if __CRT_HAVE_SC(vmsplice)
#ifndef __sys_vmsplice_defined
#define __sys_vmsplice_defined 1
__CDECLARE_SC(,__ssize_t,vmsplice,(__fd_t __fdout, struct iovec const *__iov, __size_t __count, __syscall_ulong_t __flags),(__fdout,__iov,__count,__flags))
#endif /* !__sys_vmsplice_defined */
#endif /* sys_vmsplice... */
#if __CRT_HAVE_SC(wait4)
#ifndef __sys_wait4_defined
#define __sys_wait4_defined 1
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE_SC(,__pid_t,wait4,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options, struct rusage *__usage),(__pid,__stat_loc,__options,__usage))
#endif /* !__sys_wait4_defined */
#endif /* sys_wait4... */
#if __CRT_HAVE_SC(waitid)
#ifndef __sys_waitid_defined
#define __sys_waitid_defined 1
/* @param: options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
__CDECLARE_SC(,__errno_t,waitid,(__idtype_t __idtype, __id_t __id, struct __siginfo_struct *__infop, __syscall_ulong_t __options, struct rusage *__ru),(__idtype,__id,__infop,__options,__ru))
#endif /* !__sys_waitid_defined */
#endif /* sys_waitid... */
#if __CRT_HAVE_SC(waitpid)
#ifndef __sys_waitpid_defined
#define __sys_waitpid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE_SC(,__pid_t,waitpid,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options),(__pid,__stat_loc,__options))
#else /* ... */
#undef __sys_waitpid_defined
#endif /* !... */
#endif /* !__sys_waitpid_defined */
#endif /* sys_waitpid... */
#if __CRT_HAVE_SC(write)
#ifndef __sys_write_defined
#define __sys_write_defined 1
__CDECLARE_SC(,__ssize_t,write,(__fd_t __fd, void const *__buf, __size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* !__sys_write_defined */
#endif /* sys_write... */
#if __CRT_HAVE_SC(writef)
#ifndef __sys_writef_defined
#define __sys_writef_defined 1
__CDECLARE_SC(,__ssize_t,writef,(__fd_t __fd, void const *__buf, __size_t __bufsize, __iomode_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* !__sys_writef_defined */
#endif /* sys_writef... */
#if __CRT_HAVE_SC(writev)
#ifndef __sys_writev_defined
#define __sys_writev_defined 1
__CDECLARE_SC(,__ssize_t,writev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* !__sys_writev_defined */
#endif /* sys_writev... */
#if __CRT_HAVE_SC(writevf)
#ifndef __sys_writevf_defined
#define __sys_writevf_defined 1
__CDECLARE_SC(,__ssize_t,writevf,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __iomode_t __mode),(__fd,__iovec,__count,__mode))
#endif /* !__sys_writevf_defined */
#endif /* sys_writevf... */



#if __CRT_HAVE_XSC(_llseek)
#ifndef __sys_X_llseek_defined
#define __sys_X_llseek_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,_llseek,(__fd_t __fd, __int64_t __offset, __uint64_t *__result, __syscall_ulong_t __whence),(__fd,__offset,__result,__whence))
#else /* ... */
#undef __sys_X_llseek_defined
#endif /* !... */
#endif /* !__sys_X_llseek_defined */
#endif /* sys_X_llseek... */
#if __CRT_HAVE_XSC(accept4)
#ifndef __sys_Xaccept4_defined
#define __sys_Xaccept4_defined 1
__CDECLARE_XSC(,__fd_t,accept4,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len, __syscall_ulong_t __flags),(__sockfd,__addr,__addr_len,__flags))
#endif /* !__sys_Xaccept4_defined */
#endif /* sys_Xaccept4... */
#if __CRT_HAVE_XSC(access)
#ifndef __sys_Xaccess_defined
#define __sys_Xaccess_defined 1
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
__CDECLARE_XSC(,__errno_t,access,(char const *__filename, __syscall_ulong_t __type),(__filename,__type))
#endif /* !__sys_Xaccess_defined */
#endif /* sys_Xaccess... */
#if __CRT_HAVE_XSC(acct)
#ifndef __sys_Xacct_defined
#define __sys_Xacct_defined 1
__CDECLARE_XSC(,__errno_t,acct,(char const *__filename),(__filename))
#endif /* !__sys_Xacct_defined */
#endif /* sys_Xacct... */
#if __CRT_HAVE_XSC(alarm)
#ifndef __sys_Xalarm_defined
#define __sys_Xalarm_defined 1
__CDECLARE_XSC(,__syscall_ulong_t,alarm,(__syscall_ulong_t __seconds),(__seconds))
#endif /* !__sys_Xalarm_defined */
#endif /* sys_Xalarm... */
#if __CRT_HAVE_XSC(bind)
#ifndef __sys_Xbind_defined
#define __sys_Xbind_defined 1
__CDECLARE_XSC(,__errno_t,bind,(__fd_t __sockfd, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#endif /* !__sys_Xbind_defined */
#endif /* sys_Xbind... */
#if __CRT_HAVE_XSC(brk)
#ifndef __sys_Xbrk_defined
#define __sys_Xbrk_defined 1
__CDECLARE_XSC(,__errno_t,brk,(void *__addr),(__addr))
#endif /* !__sys_Xbrk_defined */
#endif /* sys_Xbrk... */
#if __CRT_HAVE_XSC(chdir)
#ifndef __sys_Xchdir_defined
#define __sys_Xchdir_defined 1
__CDECLARE_XSC(,__errno_t,chdir,(char const *__path),(__path))
#endif /* !__sys_Xchdir_defined */
#endif /* sys_Xchdir... */
#if __CRT_HAVE_XSC(chmod)
#ifndef __sys_Xchmod_defined
#define __sys_Xchmod_defined 1
__CDECLARE_XSC(,__errno_t,chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#endif /* !__sys_Xchmod_defined */
#endif /* sys_Xchmod... */
#if __CRT_HAVE_XSC(chown)
#ifndef __sys_Xchown_defined
#define __sys_Xchown_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,chown,(char const *__filename, __uint16_t __owner, __uint16_t __group),(__filename,__owner,__group))
#else /* #elif defined(__x86_64__) */
__CDECLARE_XSC(,__errno_t,chown,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#endif /* ... */
#endif /* !__sys_Xchown_defined */
#endif /* sys_Xchown... */
#if __CRT_HAVE_XSC(chown32)
#ifndef __sys_Xchown32_defined
#define __sys_Xchown32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,chown32,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#else /* ... */
#undef __sys_Xchown32_defined
#endif /* !... */
#endif /* !__sys_Xchown32_defined */
#endif /* sys_Xchown32... */
#if __CRT_HAVE_XSC(chroot)
#ifndef __sys_Xchroot_defined
#define __sys_Xchroot_defined 1
__CDECLARE_XSC(,__errno_t,chroot,(char const *__path),(__path))
#endif /* !__sys_Xchroot_defined */
#endif /* sys_Xchroot... */
#if __CRT_HAVE_XSC(clock_getres)
#ifndef __sys_Xclock_getres_defined
#define __sys_Xclock_getres_defined 1
__CDECLARE_XSC(,__errno_t,clock_getres,(__clockid_t __clock_id, struct __timespec32 *__res),(__clock_id,__res))
#endif /* !__sys_Xclock_getres_defined */
#endif /* sys_Xclock_getres... */
#if __CRT_HAVE_XSC(clock_getres64)
#ifndef __sys_Xclock_getres64_defined
#define __sys_Xclock_getres64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,clock_getres64,(__clockid_t __clock_id, struct __timespec64 *__res),(__clock_id,__res))
#else /* ... */
#undef __sys_Xclock_getres64_defined
#endif /* !... */
#endif /* !__sys_Xclock_getres64_defined */
#endif /* sys_Xclock_getres64... */
#if __CRT_HAVE_XSC(clock_gettime)
#ifndef __sys_Xclock_gettime_defined
#define __sys_Xclock_gettime_defined 1
__CDECLARE_XSC(,__errno_t,clock_gettime,(__clockid_t __clock_id, struct __timespec32 *__tp),(__clock_id,__tp))
#endif /* !__sys_Xclock_gettime_defined */
#endif /* sys_Xclock_gettime... */
#if __CRT_HAVE_XSC(clock_gettime64)
#ifndef __sys_Xclock_gettime64_defined
#define __sys_Xclock_gettime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,clock_gettime64,(__clockid_t __clock_id, struct __timespec64 *__tp),(__clock_id,__tp))
#else /* ... */
#undef __sys_Xclock_gettime64_defined
#endif /* !... */
#endif /* !__sys_Xclock_gettime64_defined */
#endif /* sys_Xclock_gettime64... */
#if __CRT_HAVE_XSC(clock_nanosleep)
#ifndef __sys_Xclock_nanosleep_defined
#define __sys_Xclock_nanosleep_defined 1
__CDECLARE_XSC(,__errno_t,clock_nanosleep,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct __timespec32 const *__requested_time, struct __timespec32 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* !__sys_Xclock_nanosleep_defined */
#endif /* sys_Xclock_nanosleep... */
#if __CRT_HAVE_XSC(clock_nanosleep64)
#ifndef __sys_Xclock_nanosleep64_defined
#define __sys_Xclock_nanosleep64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,clock_nanosleep64,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct __timespec64 const *__requested_time, struct __timespec64 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#else /* ... */
#undef __sys_Xclock_nanosleep64_defined
#endif /* !... */
#endif /* !__sys_Xclock_nanosleep64_defined */
#endif /* sys_Xclock_nanosleep64... */
#if __CRT_HAVE_XSC(clock_settime)
#ifndef __sys_Xclock_settime_defined
#define __sys_Xclock_settime_defined 1
__CDECLARE_XSC(,__errno_t,clock_settime,(__clockid_t __clock_id, struct __timespec32 const *__tp),(__clock_id,__tp))
#endif /* !__sys_Xclock_settime_defined */
#endif /* sys_Xclock_settime... */
#if __CRT_HAVE_XSC(clock_settime64)
#ifndef __sys_Xclock_settime64_defined
#define __sys_Xclock_settime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,clock_settime64,(__clockid_t __clock_id, struct __timespec64 const *__tp),(__clock_id,__tp))
#else /* ... */
#undef __sys_Xclock_settime64_defined
#endif /* !... */
#endif /* !__sys_Xclock_settime64_defined */
#endif /* sys_Xclock_settime64... */
#if __CRT_HAVE_XSC(clone)
#ifndef __sys_Xclone_defined
#define __sys_Xclone_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __uintptr_t __newtls, __pid_t *__ctid),(__flags,__child_stack,__ptid,__newtls,__ctid))
#else /* #elif defined(__x86_64__) */
__CDECLARE_XSC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __pid_t *__ctid, __uintptr_t __newtls),(__flags,__child_stack,__ptid,__ctid,__newtls))
#endif /* ... */
#endif /* !__sys_Xclone_defined */
#endif /* sys_Xclone... */
#if __CRT_HAVE_XSC(close)
#ifndef __sys_Xclose_defined
#define __sys_Xclose_defined 1
/* Close a given file descriptor/handle `FD' */
__CDECLARE_XSC(,__errno_t,close,(__fd_t __fd),(__fd))
#endif /* !__sys_Xclose_defined */
#endif /* sys_Xclose... */
#if __CRT_HAVE_XSC(connect)
#ifndef __sys_Xconnect_defined
#define __sys_Xconnect_defined 1
__CDECLARE_XSC(,__errno_t,connect,(__fd_t __sockfd, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#endif /* !__sys_Xconnect_defined */
#endif /* sys_Xconnect... */
#if __CRT_HAVE_XSC(coredump)
#ifndef __sys_Xcoredump_defined
#define __sys_Xcoredump_defined 1
/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
__CDECLARE_XSC(,__errno_t,coredump,(struct ucpustate const *__curr_state, struct ucpustate const *__orig_state, void const *const *__traceback_vector, __size_t __traceback_length, struct exception_data const *__exception, __syscall_ulong_t __unwind_error),(__curr_state,__orig_state,__traceback_vector,__traceback_length,__exception,__unwind_error))
#endif /* !__sys_Xcoredump_defined */
#endif /* sys_Xcoredump... */
#if __CRT_HAVE_XSC(creat)
#ifndef __sys_Xcreat_defined
#define __sys_Xcreat_defined 1
__CDECLARE_XSC(,__fd_t,creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#endif /* !__sys_Xcreat_defined */
#endif /* sys_Xcreat... */
#if __CRT_HAVE_XSC(debugtrap)
#ifndef __sys_Xdebugtrap_defined
#define __sys_Xdebugtrap_defined 1
/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
__CDECLARE_XSC(,__errno_t,debugtrap,(struct ucpustate const *__state, struct debugtrap_reason const *__reason),(__state,__reason))
#endif /* !__sys_Xdebugtrap_defined */
#endif /* sys_Xdebugtrap... */
#if __CRT_HAVE_XSC(detach)
#ifndef __sys_Xdetach_defined
#define __sys_Xdetach_defined 1
/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
__CDECLARE_XSC(,__errno_t,detach,(__pid_t __pid),(__pid))
#endif /* !__sys_Xdetach_defined */
#endif /* sys_Xdetach... */
#if __CRT_HAVE_XSC(dup)
#ifndef __sys_Xdup_defined
#define __sys_Xdup_defined 1
__CDECLARE_XSC(,__fd_t,dup,(__fd_t __fd),(__fd))
#endif /* !__sys_Xdup_defined */
#endif /* sys_Xdup... */
#if __CRT_HAVE_XSC(dup2)
#ifndef __sys_Xdup2_defined
#define __sys_Xdup2_defined 1
__CDECLARE_XSC(,__fd_t,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#endif /* !__sys_Xdup2_defined */
#endif /* sys_Xdup2... */
#if __CRT_HAVE_XSC(dup3)
#ifndef __sys_Xdup3_defined
#define __sys_Xdup3_defined 1
/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
__CDECLARE_XSC(,__fd_t,dup3,(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags),(__oldfd,__newfd,__flags))
#endif /* !__sys_Xdup3_defined */
#endif /* sys_Xdup3... */
#if __CRT_HAVE_XSC(epoll_create)
#ifndef __sys_Xepoll_create_defined
#define __sys_Xepoll_create_defined 1
__CDECLARE_XSC(,__fd_t,epoll_create,(__syscall_ulong_t __size),(__size))
#endif /* !__sys_Xepoll_create_defined */
#endif /* sys_Xepoll_create... */
#if __CRT_HAVE_XSC(epoll_create1)
#ifndef __sys_Xepoll_create1_defined
#define __sys_Xepoll_create1_defined 1
__CDECLARE_XSC(,__fd_t,epoll_create1,(__syscall_ulong_t __flags),(__flags))
#endif /* !__sys_Xepoll_create1_defined */
#endif /* sys_Xepoll_create1... */
#if __CRT_HAVE_XSC(epoll_ctl)
#ifndef __sys_Xepoll_ctl_defined
#define __sys_Xepoll_ctl_defined 1
__CDECLARE_XSC(,__errno_t,epoll_ctl,(__fd_t __epfd, __syscall_ulong_t __op, __fd_t __fd, struct epoll_event *__event),(__epfd,__op,__fd,__event))
#endif /* !__sys_Xepoll_ctl_defined */
#endif /* sys_Xepoll_ctl... */
#if __CRT_HAVE_XSC(epoll_ctl_old)
#ifndef __sys_Xepoll_ctl_old_defined
#define __sys_Xepoll_ctl_old_defined 1
#ifdef __x86_64__
__CDECLARE_XSC(,__errno_t,epoll_ctl_old,(__fd_t __epfd, __syscall_ulong_t __op, __fd_t __fd, struct epoll_event *__event),(__epfd,__op,__fd,__event))
#else /* ... */
#undef __sys_Xepoll_ctl_old_defined
#endif /* !... */
#endif /* !__sys_Xepoll_ctl_old_defined */
#endif /* sys_Xepoll_ctl_old... */
#if __CRT_HAVE_XSC(epoll_pwait)
#ifndef __sys_Xepoll_pwait_defined
#define __sys_Xepoll_pwait_defined 1
__CDECLARE_XSC(,__errno_t,epoll_pwait,(__fd_t __epfd, struct epoll_event *__events, __syscall_ulong_t __maxevents, __syscall_slong_t __timeout, struct __sigset_struct const *__ss),(__epfd,__events,__maxevents,__timeout,__ss))
#endif /* !__sys_Xepoll_pwait_defined */
#endif /* sys_Xepoll_pwait... */
#if __CRT_HAVE_XSC(epoll_wait)
#ifndef __sys_Xepoll_wait_defined
#define __sys_Xepoll_wait_defined 1
__CDECLARE_XSC(,__errno_t,epoll_wait,(__fd_t __epfd, struct epoll_event *__events, __syscall_ulong_t __maxevents, __syscall_slong_t __timeout),(__epfd,__events,__maxevents,__timeout))
#endif /* !__sys_Xepoll_wait_defined */
#endif /* sys_Xepoll_wait... */
#if __CRT_HAVE_XSC(epoll_wait_old)
#ifndef __sys_Xepoll_wait_old_defined
#define __sys_Xepoll_wait_old_defined 1
#ifdef __x86_64__
__CDECLARE_XSC(,__errno_t,epoll_wait_old,(__fd_t __epfd, struct epoll_event *__events, __syscall_ulong_t __maxevents, __syscall_slong_t __timeout),(__epfd,__events,__maxevents,__timeout))
#else /* ... */
#undef __sys_Xepoll_wait_old_defined
#endif /* !... */
#endif /* !__sys_Xepoll_wait_old_defined */
#endif /* sys_Xepoll_wait_old... */
#if __CRT_HAVE_XSC(eventfd)
#ifndef __sys_Xeventfd_defined
#define __sys_Xeventfd_defined 1
__CDECLARE_XSC(,__fd_t,eventfd,(__syscall_ulong_t __initval),(__initval))
#endif /* !__sys_Xeventfd_defined */
#endif /* sys_Xeventfd... */
#if __CRT_HAVE_XSC(eventfd2)
#ifndef __sys_Xeventfd2_defined
#define __sys_Xeventfd2_defined 1
__CDECLARE_XSC(,__fd_t,eventfd2,(__syscall_ulong_t __initval, __syscall_ulong_t __flags),(__initval,__flags))
#endif /* !__sys_Xeventfd2_defined */
#endif /* sys_Xeventfd2... */
#if __CRT_HAVE_XSC(execve)
#ifndef __sys_Xexecve_defined
#define __sys_Xexecve_defined 1
__CDECLARE_XSC(,__errno_t,execve,(char const *__path, char const *const *___argv, char const *const *___envp),(__path,___argv,___envp))
#endif /* !__sys_Xexecve_defined */
#endif /* sys_Xexecve... */
#if __CRT_HAVE_XSC(execveat)
#ifndef __sys_Xexecveat_defined
#define __sys_Xexecveat_defined 1
/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,execveat,(__fd_t __dirfd, char const *__pathname, char const *const *___argv, char const *const *___envp, __atflag_t __flags),(__dirfd,__pathname,___argv,___envp,__flags))
#endif /* !__sys_Xexecveat_defined */
#endif /* sys_Xexecveat... */
#if __CRT_HAVE_XSC(exit)
#ifndef __sys_Xexit_defined
#define __sys_Xexit_defined 1
__CDECLARE_VOID_XSC(__ATTR_NORETURN,exit,(__syscall_ulong_t __status),(__status))
#endif /* !__sys_Xexit_defined */
#endif /* sys_Xexit... */
#if __CRT_HAVE_XSC(exit_group)
#ifndef __sys_Xexit_group_defined
#define __sys_Xexit_group_defined 1
__CDECLARE_VOID_XSC(__ATTR_NORETURN,exit_group,(__syscall_ulong_t __exit_code),(__exit_code))
#endif /* !__sys_Xexit_group_defined */
#endif /* sys_Xexit_group... */
#if __CRT_HAVE_XSC(faccessat)
#ifndef __sys_Xfaccessat_defined
#define __sys_Xfaccessat_defined 1
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,faccessat,(__fd_t __dirfd, char const *__filename, __syscall_ulong_t __type, __atflag_t __flags),(__dirfd,__filename,__type,__flags))
#endif /* !__sys_Xfaccessat_defined */
#endif /* sys_Xfaccessat... */
#if __CRT_HAVE_XSC(fallocate)
#ifndef __sys_Xfallocate_defined
#define __sys_Xfallocate_defined 1
__CDECLARE_XSC(,__errno_t,fallocate,(__fd_t __fd, __syscall_ulong_t __mode, __uint32_t __offset, __uint32_t __length),(__fd,__mode,__offset,__length))
#endif /* !__sys_Xfallocate_defined */
#endif /* sys_Xfallocate... */
#if __CRT_HAVE_XSC(fallocate64)
#ifndef __sys_Xfallocate64_defined
#define __sys_Xfallocate64_defined 1
__CDECLARE_XSC(,__errno_t,fallocate64,(__fd_t __fd, __syscall_ulong_t __mode, __uint64_t __offset, __uint64_t __length),(__fd,__mode,__offset,__length))
#endif /* !__sys_Xfallocate64_defined */
#endif /* sys_Xfallocate64... */
#if __CRT_HAVE_XSC(fchdir)
#ifndef __sys_Xfchdir_defined
#define __sys_Xfchdir_defined 1
__CDECLARE_XSC(,__errno_t,fchdir,(__fd_t __fd),(__fd))
#endif /* !__sys_Xfchdir_defined */
#endif /* sys_Xfchdir... */
#if __CRT_HAVE_XSC(fchdirat)
#ifndef __sys_Xfchdirat_defined
#define __sys_Xfchdirat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fchdirat,(__fd_t __dirfd, char const *__path, __atflag_t __flags),(__dirfd,__path,__flags))
#endif /* !__sys_Xfchdirat_defined */
#endif /* sys_Xfchdirat... */
#if __CRT_HAVE_XSC(fchmod)
#ifndef __sys_Xfchmod_defined
#define __sys_Xfchmod_defined 1
__CDECLARE_XSC(,__errno_t,fchmod,(__fd_t __fd, __mode_t __mode),(__fd,__mode))
#endif /* !__sys_Xfchmod_defined */
#endif /* sys_Xfchmod... */
#if __CRT_HAVE_XSC(fchmodat)
#ifndef __sys_Xfchmodat_defined
#define __sys_Xfchmodat_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fchmodat,(__fd_t __dirfd, char const *__filename, __mode_t __mode, __atflag_t __flags),(__dirfd,__filename,__mode,__flags))
#endif /* !__sys_Xfchmodat_defined */
#endif /* sys_Xfchmodat... */
#if __CRT_HAVE_XSC(fchown)
#ifndef __sys_Xfchown_defined
#define __sys_Xfchown_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,fchown,(__fd_t __fd, __uint16_t __owner, __uint16_t __group),(__fd,__owner,__group))
#else /* #elif defined(__x86_64__) */
__CDECLARE_XSC(,__errno_t,fchown,(__fd_t __fd, __uint32_t __owner, __uint32_t __group),(__fd,__owner,__group))
#endif /* ... */
#endif /* !__sys_Xfchown_defined */
#endif /* sys_Xfchown... */
#if __CRT_HAVE_XSC(fchown32)
#ifndef __sys_Xfchown32_defined
#define __sys_Xfchown32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,fchown32,(__fd_t __fd, __uint32_t __owner, __uint32_t __group),(__fd,__owner,__group))
#else /* ... */
#undef __sys_Xfchown32_defined
#endif /* !... */
#endif /* !__sys_Xfchown32_defined */
#endif /* sys_Xfchown32... */
#if __CRT_HAVE_XSC(fchownat)
#ifndef __sys_Xfchownat_defined
#define __sys_Xfchownat_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fchownat,(__fd_t __dirfd, char const *__filename, __uint32_t __owner, __uint32_t __group, __atflag_t __flags),(__dirfd,__filename,__owner,__group,__flags))
#endif /* !__sys_Xfchownat_defined */
#endif /* sys_Xfchownat... */
#if __CRT_HAVE_XSC(fcntl)
#ifndef __sys_Xfcntl_defined
#define __sys_Xfcntl_defined 1
__CDECLARE_XSC(,__syscall_slong_t,fcntl,(__fd_t __fd, __syscall_ulong_t __cmd, void *__arg),(__fd,__cmd,__arg))
#endif /* !__sys_Xfcntl_defined */
#endif /* sys_Xfcntl... */
#if __CRT_HAVE_XSC(fcntl64)
#ifndef __sys_Xfcntl64_defined
#define __sys_Xfcntl64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__syscall_slong_t,fcntl64,(__fd_t __fd, __syscall_ulong_t __command, void *__arg),(__fd,__command,__arg))
#else /* ... */
#undef __sys_Xfcntl64_defined
#endif /* !... */
#endif /* !__sys_Xfcntl64_defined */
#endif /* sys_Xfcntl64... */
#if __CRT_HAVE_XSC(fdatasync)
#ifndef __sys_Xfdatasync_defined
#define __sys_Xfdatasync_defined 1
__CDECLARE_XSC(,__errno_t,fdatasync,(__fd_t __fd),(__fd))
#endif /* !__sys_Xfdatasync_defined */
#endif /* sys_Xfdatasync... */
#if __CRT_HAVE_XSC(fgetxattr)
#ifndef __sys_Xfgetxattr_defined
#define __sys_Xfgetxattr_defined 1
__CDECLARE_XSC(,__ssize_t,fgetxattr,(__fd_t __fd, char const *__name, void *__buf, __size_t __bufsize),(__fd,__name,__buf,__bufsize))
#endif /* !__sys_Xfgetxattr_defined */
#endif /* sys_Xfgetxattr... */
#if __CRT_HAVE_XSC(flistxattr)
#ifndef __sys_Xflistxattr_defined
#define __sys_Xflistxattr_defined 1
__CDECLARE_XSC(,__ssize_t,flistxattr,(__fd_t __fd, char *__listbuf, __size_t __listbufsize),(__fd,__listbuf,__listbufsize))
#endif /* !__sys_Xflistxattr_defined */
#endif /* sys_Xflistxattr... */
#if __CRT_HAVE_XSC(flock)
#ifndef __sys_Xflock_defined
#define __sys_Xflock_defined 1
__CDECLARE_XSC(,__errno_t,flock,(__fd_t __fd, __syscall_ulong_t __operation),(__fd,__operation))
#endif /* !__sys_Xflock_defined */
#endif /* sys_Xflock... */
#if __CRT_HAVE_XSC(fmkdirat)
#ifndef __sys_Xfmkdirat_defined
#define __sys_Xfmkdirat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fmkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode, __atflag_t __flags),(__dirfd,__pathname,__mode,__flags))
#endif /* !__sys_Xfmkdirat_defined */
#endif /* sys_Xfmkdirat... */
#if __CRT_HAVE_XSC(fmknodat)
#ifndef __sys_Xfmknodat_defined
#define __sys_Xfmknodat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fmknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),(__dirfd,__nodename,__mode,__dev,__flags))
#endif /* !__sys_Xfmknodat_defined */
#endif /* sys_Xfmknodat... */
#if __CRT_HAVE_XSC(fork)
#ifndef __sys_Xfork_defined
#define __sys_Xfork_defined 1
__CDECLARE_XSC(,__pid_t,fork,(void),())
#endif /* !__sys_Xfork_defined */
#endif /* sys_Xfork... */
#if __CRT_HAVE_XSC(freadlinkat)
#ifndef __sys_Xfreadlinkat_defined
#define __sys_Xfreadlinkat_defined 1
/* @param: flags: Set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
__CDECLARE_XSC(,__ssize_t,freadlinkat,(__fd_t __dirfd, char const *__path, char *__buf, __size_t __buflen, __atflag_t __flags),(__dirfd,__path,__buf,__buflen,__flags))
#endif /* !__sys_Xfreadlinkat_defined */
#endif /* sys_Xfreadlinkat... */
#if __CRT_HAVE_XSC(frealpath4)
#ifndef __sys_Xfrealpath4_defined
#define __sys_Xfrealpath4_defined 1
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
__CDECLARE_XSC(,__ssize_t,frealpath4,(__fd_t __fd, char *__buf, __size_t __buflen, __atflag_t __flags),(__fd,__buf,__buflen,__flags))
#endif /* !__sys_Xfrealpath4_defined */
#endif /* sys_Xfrealpath4... */
#if __CRT_HAVE_XSC(frealpathat)
#ifndef __sys_Xfrealpathat_defined
#define __sys_Xfrealpathat_defined 1
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE|AT_DOSPATH' */
__CDECLARE_XSC(,__ssize_t,frealpathat,(__fd_t __dirfd, char const *__filename, char *__buf, __size_t __buflen, __atflag_t __flags),(__dirfd,__filename,__buf,__buflen,__flags))
#endif /* !__sys_Xfrealpathat_defined */
#endif /* sys_Xfrealpathat... */
#if __CRT_HAVE_XSC(fremovexattr)
#ifndef __sys_Xfremovexattr_defined
#define __sys_Xfremovexattr_defined 1
__CDECLARE_XSC(,__errno_t,fremovexattr,(int __fd, char const *__name),(__fd,__name))
#endif /* !__sys_Xfremovexattr_defined */
#endif /* sys_Xfremovexattr... */
#if __CRT_HAVE_XSC(frenameat)
#ifndef __sys_Xfrenameat_defined
#define __sys_Xfrenameat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,frenameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path, __atflag_t __flags),(__oldfd,__oldname,__newfd,__newname_or_path,__flags))
#endif /* !__sys_Xfrenameat_defined */
#endif /* sys_Xfrenameat... */
#if __CRT_HAVE_XSC(fsetxattr)
#ifndef __sys_Xfsetxattr_defined
#define __sys_Xfsetxattr_defined 1
__CDECLARE_XSC(,__errno_t,fsetxattr,(__fd_t __fd, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__fd,__name,__buf,__bufsize,__flags))
#endif /* !__sys_Xfsetxattr_defined */
#endif /* sys_Xfsetxattr... */
#if __CRT_HAVE_XSC(fsmode)
#ifndef __sys_Xfsmode_defined
#define __sys_Xfsmode_defined 1
__CDECLARE_XSC(,__uint64_t,fsmode,(__uint64_t __mode),(__mode))
#endif /* !__sys_Xfsmode_defined */
#endif /* sys_Xfsmode... */
#if __CRT_HAVE_XSC(fstatat)
#ifndef __sys_Xfstatat_defined
#define __sys_Xfstatat_defined 1
#ifdef __x86_64__
__CDECLARE_XSC(,__errno_t,fstatat,(__fd_t __dirfd, char const *__filename, struct linux64_stat32 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#else /* ... */
#undef __sys_Xfstatat_defined
#endif /* !... */
#endif /* !__sys_Xfstatat_defined */
#endif /* sys_Xfstatat... */
#if __CRT_HAVE_XSC(fstatfs)
#ifndef __sys_Xfstatfs_defined
#define __sys_Xfstatfs_defined 1
__CDECLARE_XSC(,__errno_t,fstatfs,(__fd_t __file, struct __statfs32 *__buf),(__file,__buf))
#endif /* !__sys_Xfstatfs_defined */
#endif /* sys_Xfstatfs... */
#if __CRT_HAVE_XSC(fstatfs64)
#ifndef __sys_Xfstatfs64_defined
#define __sys_Xfstatfs64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,fstatfs64,(__fd_t __file, struct statfs64 *__buf),(__file,__buf))
#else /* ... */
#undef __sys_Xfstatfs64_defined
#endif /* !... */
#endif /* !__sys_Xfstatfs64_defined */
#endif /* sys_Xfstatfs64... */
#if __CRT_HAVE_XSC(fsymlinkat)
#ifndef __sys_Xfsymlinkat_defined
#define __sys_Xfsymlinkat_defined 1
/* @param: flags: Set of `0|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fsymlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__link_text,__tofd,__target_path,__flags))
#endif /* !__sys_Xfsymlinkat_defined */
#endif /* sys_Xfsymlinkat... */
#if __CRT_HAVE_XSC(fsync)
#ifndef __sys_Xfsync_defined
#define __sys_Xfsync_defined 1
__CDECLARE_XSC(,__errno_t,fsync,(__fd_t __fd),(__fd))
#endif /* !__sys_Xfsync_defined */
#endif /* sys_Xfsync... */
#if __CRT_HAVE_XSC(ftime)
#ifndef __sys_Xftime_defined
#define __sys_Xftime_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,ftime,(struct timeb *__tp),(__tp))
#else /* ... */
#undef __sys_Xftime_defined
#endif /* !... */
#endif /* !__sys_Xftime_defined */
#endif /* sys_Xftime... */
#if __CRT_HAVE_XSC(ftruncate)
#ifndef __sys_Xftruncate_defined
#define __sys_Xftruncate_defined 1
__CDECLARE_XSC(,__errno_t,ftruncate,(__fd_t __fd, __syscall_ulong_t __length),(__fd,__length))
#endif /* !__sys_Xftruncate_defined */
#endif /* sys_Xftruncate... */
#if __CRT_HAVE_XSC(ftruncate64)
#ifndef __sys_Xftruncate64_defined
#define __sys_Xftruncate64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,ftruncate64,(__fd_t __fd, __uint64_t __length),(__fd,__length))
#else /* ... */
#undef __sys_Xftruncate64_defined
#endif /* !... */
#endif /* !__sys_Xftruncate64_defined */
#endif /* sys_Xftruncate64... */
#if __CRT_HAVE_XSC(futex)
#ifndef __sys_Xfutex_defined
#define __sys_Xfutex_defined 1
__CDECLARE_XSC(,__syscall_slong_t,futex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct __timespec32 const *__timeout_or_val2, __uint32_t *__uaddr2, __uint32_t __val3),(__uaddr,__futex_op,__val,__timeout_or_val2,__uaddr2,__val3))
#endif /* !__sys_Xfutex_defined */
#endif /* sys_Xfutex... */
#if __CRT_HAVE_XSC(futimesat)
#ifndef __sys_Xfutimesat_defined
#define __sys_Xfutimesat_defined 1
__CDECLARE_XSC(,__errno_t,futimesat,(__fd_t __dirfd, const char *__filename, /*[2]*/ struct __timeval32 const *__times),(__dirfd,__filename,__times))
#endif /* !__sys_Xfutimesat_defined */
#endif /* sys_Xfutimesat... */
#if __CRT_HAVE_XSC(futimesat64)
#ifndef __sys_Xfutimesat64_defined
#define __sys_Xfutimesat64_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,futimesat64,(__fd_t __dirfd, const char *__filename, /*[2-3]*/ struct __timeval64 const *__times),(__dirfd,__filename,__times))
#endif /* !__sys_Xfutimesat64_defined */
#endif /* sys_Xfutimesat64... */
#if __CRT_HAVE_XSC(get_exception_handler)
#ifndef __sys_Xget_exception_handler_defined
#define __sys_Xget_exception_handler_defined 1
/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
__CDECLARE_XSC(,__errno_t,get_exception_handler,(__syscall_ulong_t *__pmode, __except_handler_t *__phandler, void **__phandler_sp),(__pmode,__phandler,__phandler_sp))
#endif /* !__sys_Xget_exception_handler_defined */
#endif /* sys_Xget_exception_handler... */
#if __CRT_HAVE_XSC(getcpu)
#ifndef __sys_Xgetcpu_defined
#define __sys_Xgetcpu_defined 1
__CDECLARE_XSC(,__errno_t,getcpu,(__uint32_t *__cpu, __uint32_t *__node, struct getcpu_cache *__tcache),(__cpu,__node,__tcache))
#endif /* !__sys_Xgetcpu_defined */
#endif /* sys_Xgetcpu... */
#if __CRT_HAVE_XSC(getcwd)
#ifndef __sys_Xgetcwd_defined
#define __sys_Xgetcwd_defined 1
__CDECLARE_XSC(,__ssize_t,getcwd,(char *__buf, __size_t __size),(__buf,__size))
#endif /* !__sys_Xgetcwd_defined */
#endif /* sys_Xgetcwd... */
#if __CRT_HAVE_XSC(getdents)
#ifndef __sys_Xgetdents_defined
#define __sys_Xgetdents_defined 1
__CDECLARE_XSC(,__ssize_t,getdents,(__fd_t __fd, struct linux_dirent *__dirp, __size_t __count),(__fd,__dirp,__count))
#endif /* !__sys_Xgetdents_defined */
#endif /* sys_Xgetdents... */
#if __CRT_HAVE_XSC(getdents64)
#ifndef __sys_Xgetdents64_defined
#define __sys_Xgetdents64_defined 1
__CDECLARE_XSC(,__ssize_t,getdents64,(__fd_t __fd, struct linux_dirent64 *__dirp, __size_t __count),(__fd,__dirp,__count))
#endif /* !__sys_Xgetdents64_defined */
#endif /* sys_Xgetdents64... */
#if __CRT_HAVE_XSC(getdrives)
#ifndef __sys_Xgetdrives_defined
#define __sys_Xgetdrives_defined 1
/* Returns a bitset of all of the currently mounted dos-drives */
__CDECLARE_XSC(,__syscall_slong_t,getdrives,(void),())
#endif /* !__sys_Xgetdrives_defined */
#endif /* sys_Xgetdrives... */
#if __CRT_HAVE_XSC(getegid)
#ifndef __sys_Xgetegid_defined
#define __sys_Xgetegid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__uint16_t,getegid,(void),())
#else /* ... */
#undef __sys_Xgetegid_defined
#endif /* !... */
#endif /* !__sys_Xgetegid_defined */
#endif /* sys_Xgetegid... */
#if __CRT_HAVE_XSC(getegid32)
#ifndef __sys_Xgetegid32_defined
#define __sys_Xgetegid32_defined 1
__CDECLARE_XSC(,__uint32_t,getegid32,(void),())
#endif /* !__sys_Xgetegid32_defined */
#endif /* sys_Xgetegid32... */
#if __CRT_HAVE_XSC(geteuid)
#ifndef __sys_Xgeteuid_defined
#define __sys_Xgeteuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__uint16_t,geteuid,(void),())
#else /* ... */
#undef __sys_Xgeteuid_defined
#endif /* !... */
#endif /* !__sys_Xgeteuid_defined */
#endif /* sys_Xgeteuid... */
#if __CRT_HAVE_XSC(geteuid32)
#ifndef __sys_Xgeteuid32_defined
#define __sys_Xgeteuid32_defined 1
__CDECLARE_XSC(,__uint32_t,geteuid32,(void),())
#endif /* !__sys_Xgeteuid32_defined */
#endif /* sys_Xgeteuid32... */
#if __CRT_HAVE_XSC(getgid)
#ifndef __sys_Xgetgid_defined
#define __sys_Xgetgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__uint16_t,getgid,(void),())
#else /* ... */
#undef __sys_Xgetgid_defined
#endif /* !... */
#endif /* !__sys_Xgetgid_defined */
#endif /* sys_Xgetgid... */
#if __CRT_HAVE_XSC(getgid32)
#ifndef __sys_Xgetgid32_defined
#define __sys_Xgetgid32_defined 1
__CDECLARE_XSC(,__uint32_t,getgid32,(void),())
#endif /* !__sys_Xgetgid32_defined */
#endif /* sys_Xgetgid32... */
#if __CRT_HAVE_XSC(getgroups)
#ifndef __sys_Xgetgroups_defined
#define __sys_Xgetgroups_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,getgroups,(__size_t __size, /*[]*/ __uint16_t *__list),(__size,__list))
#else /* ... */
#undef __sys_Xgetgroups_defined
#endif /* !... */
#endif /* !__sys_Xgetgroups_defined */
#endif /* sys_Xgetgroups... */
#if __CRT_HAVE_XSC(getgroups32)
#ifndef __sys_Xgetgroups32_defined
#define __sys_Xgetgroups32_defined 1
__CDECLARE_XSC(,__errno_t,getgroups32,(__size_t __size, /*[]*/ __uint32_t *__list),(__size,__list))
#endif /* !__sys_Xgetgroups32_defined */
#endif /* sys_Xgetgroups32... */
#if __CRT_HAVE_XSC(getitimer)
#ifndef __sys_Xgetitimer_defined
#define __sys_Xgetitimer_defined 1
__CDECLARE_XSC(,__errno_t,getitimer,(__syscall_ulong_t __which, struct __itimerval32 *__curr_value),(__which,__curr_value))
#endif /* !__sys_Xgetitimer_defined */
#endif /* sys_Xgetitimer... */
#if __CRT_HAVE_XSC(getitimer64)
#ifndef __sys_Xgetitimer64_defined
#define __sys_Xgetitimer64_defined 1
__CDECLARE_XSC(,__errno_t,getitimer64,(__syscall_ulong_t __which, struct __itimerval64 *__curr_value),(__which,__curr_value))
#endif /* !__sys_Xgetitimer64_defined */
#endif /* sys_Xgetitimer64... */
#if __CRT_HAVE_XSC(getpeername)
#ifndef __sys_Xgetpeername_defined
#define __sys_Xgetpeername_defined 1
__CDECLARE_XSC(,__errno_t,getpeername,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* !__sys_Xgetpeername_defined */
#endif /* sys_Xgetpeername... */
#if __CRT_HAVE_XSC(getpgid)
#ifndef __sys_Xgetpgid_defined
#define __sys_Xgetpgid_defined 1
__CDECLARE_XSC(,__pid_t,getpgid,(__pid_t __pid),(__pid))
#endif /* !__sys_Xgetpgid_defined */
#endif /* sys_Xgetpgid... */
#if __CRT_HAVE_XSC(getpgrp)
#ifndef __sys_Xgetpgrp_defined
#define __sys_Xgetpgrp_defined 1
__CDECLARE_XSC(,__pid_t,getpgrp,(void),())
#endif /* !__sys_Xgetpgrp_defined */
#endif /* sys_Xgetpgrp... */
#if __CRT_HAVE_XSC(getpid)
#ifndef __sys_Xgetpid_defined
#define __sys_Xgetpid_defined 1
__CDECLARE_XSC(,__pid_t,getpid,(void),())
#endif /* !__sys_Xgetpid_defined */
#endif /* sys_Xgetpid... */
#if __CRT_HAVE_XSC(getppid)
#ifndef __sys_Xgetppid_defined
#define __sys_Xgetppid_defined 1
__CDECLARE_XSC(,__pid_t,getppid,(void),())
#endif /* !__sys_Xgetppid_defined */
#endif /* sys_Xgetppid... */
#if __CRT_HAVE_XSC(getpriority)
#ifndef __sys_Xgetpriority_defined
#define __sys_Xgetpriority_defined 1
__CDECLARE_XSC(,__syscall_slong_t,getpriority,(__syscall_ulong_t __which, __id_t __who),(__which,__who))
#endif /* !__sys_Xgetpriority_defined */
#endif /* sys_Xgetpriority... */
#if __CRT_HAVE_XSC(getresgid)
#ifndef __sys_Xgetresgid_defined
#define __sys_Xgetresgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,getresgid,(__uint16_t *__rgid, __uint16_t *__egid, __uint16_t *__sgid),(__rgid,__egid,__sgid))
#else /* ... */
#undef __sys_Xgetresgid_defined
#endif /* !... */
#endif /* !__sys_Xgetresgid_defined */
#endif /* sys_Xgetresgid... */
#if __CRT_HAVE_XSC(getresgid32)
#ifndef __sys_Xgetresgid32_defined
#define __sys_Xgetresgid32_defined 1
__CDECLARE_XSC(,__errno_t,getresgid32,(__uint32_t *__rgid, __uint32_t *__egid, __uint32_t *__sgid),(__rgid,__egid,__sgid))
#endif /* !__sys_Xgetresgid32_defined */
#endif /* sys_Xgetresgid32... */
#if __CRT_HAVE_XSC(getresuid)
#ifndef __sys_Xgetresuid_defined
#define __sys_Xgetresuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,getresuid,(__uint16_t *__ruid, __uint16_t *__euid, __uint16_t *__suid),(__ruid,__euid,__suid))
#else /* ... */
#undef __sys_Xgetresuid_defined
#endif /* !... */
#endif /* !__sys_Xgetresuid_defined */
#endif /* sys_Xgetresuid... */
#if __CRT_HAVE_XSC(getresuid32)
#ifndef __sys_Xgetresuid32_defined
#define __sys_Xgetresuid32_defined 1
__CDECLARE_XSC(,__errno_t,getresuid32,(__uint32_t *__ruid, __uint32_t *__euid, __uint32_t *__suid),(__ruid,__euid,__suid))
#endif /* !__sys_Xgetresuid32_defined */
#endif /* sys_Xgetresuid32... */
#if __CRT_HAVE_XSC(getrlimit)
#ifndef __sys_Xgetrlimit_defined
#define __sys_Xgetrlimit_defined 1
__CDECLARE_XSC(,__errno_t,getrlimit,(__syscall_ulong_t __resource, struct rlimit *__rlimits),(__resource,__rlimits))
#endif /* !__sys_Xgetrlimit_defined */
#endif /* sys_Xgetrlimit... */
#if __CRT_HAVE_XSC(getrusage)
#ifndef __sys_Xgetrusage_defined
#define __sys_Xgetrusage_defined 1
__CDECLARE_XSC(,__errno_t,getrusage,(__syscall_slong_t __who, struct rusage *__usage),(__who,__usage))
#endif /* !__sys_Xgetrusage_defined */
#endif /* sys_Xgetrusage... */
#if __CRT_HAVE_XSC(getsid)
#ifndef __sys_Xgetsid_defined
#define __sys_Xgetsid_defined 1
__CDECLARE_XSC(,__pid_t,getsid,(__pid_t __pid),(__pid))
#endif /* !__sys_Xgetsid_defined */
#endif /* sys_Xgetsid... */
#if __CRT_HAVE_XSC(getsockname)
#ifndef __sys_Xgetsockname_defined
#define __sys_Xgetsockname_defined 1
__CDECLARE_XSC(,__errno_t,getsockname,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* !__sys_Xgetsockname_defined */
#endif /* sys_Xgetsockname... */
#if __CRT_HAVE_XSC(getsockopt)
#ifndef __sys_Xgetsockopt_defined
#define __sys_Xgetsockopt_defined 1
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
__CDECLARE_XSC(,__errno_t,getsockopt,(__fd_t __sockfd, __syscall_ulong_t __level, __syscall_ulong_t __optname, void *__optval, __socklen_t *__optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* !__sys_Xgetsockopt_defined */
#endif /* sys_Xgetsockopt... */
#if __CRT_HAVE_XSC(gettid)
#ifndef __sys_Xgettid_defined
#define __sys_Xgettid_defined 1
__CDECLARE_XSC(,__pid_t,gettid,(void),())
#endif /* !__sys_Xgettid_defined */
#endif /* sys_Xgettid... */
#if __CRT_HAVE_XSC(gettimeofday)
#ifndef __sys_Xgettimeofday_defined
#define __sys_Xgettimeofday_defined 1
__CDECLARE_XSC(,__errno_t,gettimeofday,(struct __timeval32 *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* !__sys_Xgettimeofday_defined */
#endif /* sys_Xgettimeofday... */
#if __CRT_HAVE_XSC(gettimeofday64)
#ifndef __sys_Xgettimeofday64_defined
#define __sys_Xgettimeofday64_defined 1
__CDECLARE_XSC(,__errno_t,gettimeofday64,(struct __timeval64 *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* !__sys_Xgettimeofday64_defined */
#endif /* sys_Xgettimeofday64... */
#if __CRT_HAVE_XSC(getuid)
#ifndef __sys_Xgetuid_defined
#define __sys_Xgetuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__uint16_t,getuid,(void),())
#else /* ... */
#undef __sys_Xgetuid_defined
#endif /* !... */
#endif /* !__sys_Xgetuid_defined */
#endif /* sys_Xgetuid... */
#if __CRT_HAVE_XSC(getuid32)
#ifndef __sys_Xgetuid32_defined
#define __sys_Xgetuid32_defined 1
__CDECLARE_XSC(,__uint32_t,getuid32,(void),())
#endif /* !__sys_Xgetuid32_defined */
#endif /* sys_Xgetuid32... */
#if __CRT_HAVE_XSC(getxattr)
#ifndef __sys_Xgetxattr_defined
#define __sys_Xgetxattr_defined 1
__CDECLARE_XSC(,__ssize_t,getxattr,(char const *__path, char const *__name, void *__buf, __size_t __bufsize),(__path,__name,__buf,__bufsize))
#endif /* !__sys_Xgetxattr_defined */
#endif /* sys_Xgetxattr... */
#if __CRT_HAVE_XSC(hop)
#ifndef __sys_Xhop_defined
#define __sys_Xhop_defined 1
__CDECLARE_XSC(,__syscall_slong_t,hop,(__fd_t __fd, __syscall_ulong_t __command, void *__arg),(__fd,__command,__arg))
#endif /* !__sys_Xhop_defined */
#endif /* sys_Xhop... */
#if __CRT_HAVE_XSC(hopf)
#ifndef __sys_Xhopf_defined
#define __sys_Xhopf_defined 1
__CDECLARE_XSC(,__syscall_slong_t,hopf,(__fd_t __fd, __syscall_ulong_t __command, __iomode_t __mode, void *__arg),(__fd,__command,__mode,__arg))
#endif /* !__sys_Xhopf_defined */
#endif /* sys_Xhopf... */
#if __CRT_HAVE_XSC(ioctl)
#ifndef __sys_Xioctl_defined
#define __sys_Xioctl_defined 1
__CDECLARE_XSC(,__syscall_slong_t,ioctl,(__fd_t __fd, __syscall_ulong_t __request, void *__arg),(__fd,__request,__arg))
#endif /* !__sys_Xioctl_defined */
#endif /* sys_Xioctl... */
#if __CRT_HAVE_XSC(ioctlf)
#ifndef __sys_Xioctlf_defined
#define __sys_Xioctlf_defined 1
__CDECLARE_XSC(,__syscall_slong_t,ioctlf,(__fd_t __fd, __syscall_ulong_t __command, __iomode_t __mode, void *__arg),(__fd,__command,__mode,__arg))
#endif /* !__sys_Xioctlf_defined */
#endif /* sys_Xioctlf... */
#if __CRT_HAVE_XSC(ioperm)
#ifndef __sys_Xioperm_defined
#define __sys_Xioperm_defined 1
__CDECLARE_XSC(,__errno_t,ioperm,(__syscall_ulong_t __from, __syscall_ulong_t __num, __syscall_ulong_t __turn_on),(__from,__num,__turn_on))
#endif /* !__sys_Xioperm_defined */
#endif /* sys_Xioperm... */
#if __CRT_HAVE_XSC(iopl)
#ifndef __sys_Xiopl_defined
#define __sys_Xiopl_defined 1
__CDECLARE_XSC(,__errno_t,iopl,(__syscall_ulong_t __level),(__level))
#endif /* !__sys_Xiopl_defined */
#endif /* sys_Xiopl... */
#if __CRT_HAVE_XSC(ioprio_get)
#ifndef __sys_Xioprio_get_defined
#define __sys_Xioprio_get_defined 1
__CDECLARE_XSC(,__errno_t,ioprio_get,(__syscall_ulong_t __which, __syscall_ulong_t __who),(__which,__who))
#endif /* !__sys_Xioprio_get_defined */
#endif /* sys_Xioprio_get... */
#if __CRT_HAVE_XSC(ioprio_set)
#ifndef __sys_Xioprio_set_defined
#define __sys_Xioprio_set_defined 1
__CDECLARE_XSC(,__errno_t,ioprio_set,(__syscall_ulong_t __which, __syscall_ulong_t __who, __syscall_ulong_t __ioprio),(__which,__who,__ioprio))
#endif /* !__sys_Xioprio_set_defined */
#endif /* sys_Xioprio_set... */
#if __CRT_HAVE_XSC(kcmp)
#ifndef __sys_Xkcmp_defined
#define __sys_Xkcmp_defined 1
__CDECLARE_XSC(,__syscall_slong_t,kcmp,(__pid_t __pid1, __pid_t __pid2, __syscall_ulong_t __type, __syscall_ulong_t __idx1, __syscall_ulong_t __idx2),(__pid1,__pid2,__type,__idx1,__idx2))
#endif /* !__sys_Xkcmp_defined */
#endif /* sys_Xkcmp... */
#if __CRT_HAVE_XSC(kfstat)
#ifndef __sys_Xkfstat_defined
#define __sys_Xkfstat_defined 1
__CDECLARE_XSC(,__errno_t,kfstat,(__fd_t __fd, struct stat *__statbuf),(__fd,__statbuf))
#endif /* !__sys_Xkfstat_defined */
#endif /* sys_Xkfstat... */
#if __CRT_HAVE_XSC(kfstatat)
#ifndef __sys_Xkfstatat_defined
#define __sys_Xkfstatat_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,kfstatat,(__fd_t __dirfd, char const *__filename, struct stat *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* !__sys_Xkfstatat_defined */
#endif /* sys_Xkfstatat... */
#if __CRT_HAVE_XSC(kill)
#ifndef __sys_Xkill_defined
#define __sys_Xkill_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,kill,(__pid_t __pid, __syscall_ulong_t __signo),(__pid,__signo))
#endif /* !__sys_Xkill_defined */
#endif /* sys_Xkill... */
#if __CRT_HAVE_XSC(klstat)
#ifndef __sys_Xklstat_defined
#define __sys_Xklstat_defined 1
__CDECLARE_XSC(,__errno_t,klstat,(char const *__filename, struct stat *__statbuf),(__filename,__statbuf))
#endif /* !__sys_Xklstat_defined */
#endif /* sys_Xklstat... */
#if __CRT_HAVE_XSC(kreaddir)
#ifndef __sys_Xkreaddir_defined
#define __sys_Xkreaddir_defined 1
__CDECLARE_XSC(,__ssize_t,kreaddir,(__fd_t __fd, struct dirent *__buf, __size_t __bufsize, __syscall_ulong_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* !__sys_Xkreaddir_defined */
#endif /* sys_Xkreaddir... */
#if __CRT_HAVE_XSC(kreaddirf)
#ifndef __sys_Xkreaddirf_defined
#define __sys_Xkreaddirf_defined 1
__CDECLARE_XSC(,__ssize_t,kreaddirf,(__fd_t __fd, struct dirent *__buf, __size_t __bufsize, __syscall_ulong_t __mode, __iomode_t __iomode),(__fd,__buf,__bufsize,__mode,__iomode))
#endif /* !__sys_Xkreaddirf_defined */
#endif /* sys_Xkreaddirf... */
#if __CRT_HAVE_XSC(kstat)
#ifndef __sys_Xkstat_defined
#define __sys_Xkstat_defined 1
__CDECLARE_XSC(,__errno_t,kstat,(char const *__filename, struct stat *__statbuf),(__filename,__statbuf))
#endif /* !__sys_Xkstat_defined */
#endif /* sys_Xkstat... */
#if __CRT_HAVE_XSC(lchown)
#ifndef __sys_Xlchown_defined
#define __sys_Xlchown_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,lchown,(char const *__filename, __uint16_t __owner, __uint16_t __group),(__filename,__owner,__group))
#else /* #elif defined(__x86_64__) */
__CDECLARE_XSC(,__errno_t,lchown,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#endif /* ... */
#endif /* !__sys_Xlchown_defined */
#endif /* sys_Xlchown... */
#if __CRT_HAVE_XSC(lchown32)
#ifndef __sys_Xlchown32_defined
#define __sys_Xlchown32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,lchown32,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#else /* ... */
#undef __sys_Xlchown32_defined
#endif /* !... */
#endif /* !__sys_Xlchown32_defined */
#endif /* sys_Xlchown32... */
#if __CRT_HAVE_XSC(lfutex)
#ifndef __sys_Xlfutex_defined
#define __sys_Xlfutex_defined 1
/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
__CDECLARE_XSC(,__syscall_slong_t,lfutex,(__uintptr_t *__uaddr, __syscall_ulong_t __futex_op, __uintptr_t __val, struct __timespec64 const *__timeout, __uintptr_t __val2),(__uaddr,__futex_op,__val,__timeout,__val2))
#endif /* !__sys_Xlfutex_defined */
#endif /* sys_Xlfutex... */
#if __CRT_HAVE_XSC(lfutexexpr)
#ifndef __sys_Xlfutexexpr_defined
#define __sys_Xlfutexexpr_defined 1
/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CDECLARE_XSC(,__errno_t,lfutexexpr,(void *__base, __size_t __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, __syscall_ulong_t __timeout_flags),(__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* !__sys_Xlfutexexpr_defined */
#endif /* sys_Xlfutexexpr... */
#if __CRT_HAVE_XSC(lfutexlockexpr)
#ifndef __sys_Xlfutexlockexpr_defined
#define __sys_Xlfutexlockexpr_defined 1
/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
__CDECLARE_XSC(,__errno_t,lfutexlockexpr,(__uintptr_t *__ulockaddr, void *__base, __size_t __exprc, struct lfutexexpr const *__exprv, struct __timespec64 const *__timeout, __syscall_ulong_t __timeout_flags),(__ulockaddr,__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* !__sys_Xlfutexlockexpr_defined */
#endif /* sys_Xlfutexlockexpr... */
#if __CRT_HAVE_XSC(lgetxattr)
#ifndef __sys_Xlgetxattr_defined
#define __sys_Xlgetxattr_defined 1
__CDECLARE_XSC(,__ssize_t,lgetxattr,(char const *__path, char const *__name, void *__buf, __size_t __bufsize),(__path,__name,__buf,__bufsize))
#endif /* !__sys_Xlgetxattr_defined */
#endif /* sys_Xlgetxattr... */
#if __CRT_HAVE_XSC(link)
#ifndef __sys_Xlink_defined
#define __sys_Xlink_defined 1
__CDECLARE_XSC(,__errno_t,link,(char const *__existing_file, char const *__link_file),(__existing_file,__link_file))
#endif /* !__sys_Xlink_defined */
#endif /* sys_Xlink... */
#if __CRT_HAVE_XSC(linkat)
#ifndef __sys_Xlinkat_defined
#define __sys_Xlinkat_defined 1
/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,linkat,(__fd_t __fromfd, char const *__existing_file, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__fromfd,__existing_file,__tofd,__target_path,__flags))
#endif /* !__sys_Xlinkat_defined */
#endif /* sys_Xlinkat... */
#if __CRT_HAVE_XSC(linux_fstat32)
#ifndef __sys_Xlinux_fstat32_defined
#define __sys_Xlinux_fstat32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,linux_fstat32,(__fd_t __fd, struct linux_stat32 *__statbuf),(__fd,__statbuf))
#else /* ... */
#undef __sys_Xlinux_fstat32_defined
#endif /* !... */
#endif /* !__sys_Xlinux_fstat32_defined */
#endif /* sys_Xlinux_fstat32... */
#if __CRT_HAVE_XSC(linux_fstat64)
#ifndef __sys_Xlinux_fstat64_defined
#define __sys_Xlinux_fstat64_defined 1
__CDECLARE_XSC(,__errno_t,linux_fstat64,(__fd_t __fd, struct linux_stat64 *__statbuf),(__fd,__statbuf))
#endif /* !__sys_Xlinux_fstat64_defined */
#endif /* sys_Xlinux_fstat64... */
#if __CRT_HAVE_XSC(linux_fstatat64)
#ifndef __sys_Xlinux_fstatat64_defined
#define __sys_Xlinux_fstatat64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,linux_fstatat64,(__fd_t __dirfd, char const *__filename, struct linux_stat64 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#else /* ... */
#undef __sys_Xlinux_fstatat64_defined
#endif /* !... */
#endif /* !__sys_Xlinux_fstatat64_defined */
#endif /* sys_Xlinux_fstatat64... */
#if __CRT_HAVE_XSC(linux_lstat32)
#ifndef __sys_Xlinux_lstat32_defined
#define __sys_Xlinux_lstat32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,linux_lstat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#else /* ... */
#undef __sys_Xlinux_lstat32_defined
#endif /* !... */
#endif /* !__sys_Xlinux_lstat32_defined */
#endif /* sys_Xlinux_lstat32... */
#if __CRT_HAVE_XSC(linux_lstat64)
#ifndef __sys_Xlinux_lstat64_defined
#define __sys_Xlinux_lstat64_defined 1
__CDECLARE_XSC(,__errno_t,linux_lstat64,(char const *__filename, struct linux_stat64 *__statbuf),(__filename,__statbuf))
#endif /* !__sys_Xlinux_lstat64_defined */
#endif /* sys_Xlinux_lstat64... */
#if __CRT_HAVE_XSC(linux_oldfstat)
#ifndef __sys_Xlinux_oldfstat_defined
#define __sys_Xlinux_oldfstat_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,linux_oldfstat,(__fd_t __fd, struct linux_oldstat *__statbuf),(__fd,__statbuf))
#else /* ... */
#undef __sys_Xlinux_oldfstat_defined
#endif /* !... */
#endif /* !__sys_Xlinux_oldfstat_defined */
#endif /* sys_Xlinux_oldfstat... */
#if __CRT_HAVE_XSC(linux_oldlstat)
#ifndef __sys_Xlinux_oldlstat_defined
#define __sys_Xlinux_oldlstat_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,linux_oldlstat,(char const *__filename, struct linux_oldstat *__statbuf),(__filename,__statbuf))
#else /* ... */
#undef __sys_Xlinux_oldlstat_defined
#endif /* !... */
#endif /* !__sys_Xlinux_oldlstat_defined */
#endif /* sys_Xlinux_oldlstat... */
#if __CRT_HAVE_XSC(linux_oldstat)
#ifndef __sys_Xlinux_oldstat_defined
#define __sys_Xlinux_oldstat_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,linux_oldstat,(char const *__filename, struct linux_oldstat *__statbuf),(__filename,__statbuf))
#else /* ... */
#undef __sys_Xlinux_oldstat_defined
#endif /* !... */
#endif /* !__sys_Xlinux_oldstat_defined */
#endif /* sys_Xlinux_oldstat... */
#if __CRT_HAVE_XSC(linux_stat32)
#ifndef __sys_Xlinux_stat32_defined
#define __sys_Xlinux_stat32_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,linux_stat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#else /* ... */
#undef __sys_Xlinux_stat32_defined
#endif /* !... */
#endif /* !__sys_Xlinux_stat32_defined */
#endif /* sys_Xlinux_stat32... */
#if __CRT_HAVE_XSC(linux_stat64)
#ifndef __sys_Xlinux_stat64_defined
#define __sys_Xlinux_stat64_defined 1
__CDECLARE_XSC(,__errno_t,linux_stat64,(char const *__filename, struct linux_stat64 *__statbuf),(__filename,__statbuf))
#endif /* !__sys_Xlinux_stat64_defined */
#endif /* sys_Xlinux_stat64... */
#if __CRT_HAVE_XSC(listen)
#ifndef __sys_Xlisten_defined
#define __sys_Xlisten_defined 1
__CDECLARE_XSC(,__errno_t,listen,(__fd_t __sockfd, __syscall_ulong_t __max_backlog),(__sockfd,__max_backlog))
#endif /* !__sys_Xlisten_defined */
#endif /* sys_Xlisten... */
#if __CRT_HAVE_XSC(listxattr)
#ifndef __sys_Xlistxattr_defined
#define __sys_Xlistxattr_defined 1
__CDECLARE_XSC(,__ssize_t,listxattr,(char const *__path, char *__listbuf, __size_t __listbufsize),(__path,__listbuf,__listbufsize))
#endif /* !__sys_Xlistxattr_defined */
#endif /* sys_Xlistxattr... */
#if __CRT_HAVE_XSC(llistxattr)
#ifndef __sys_Xllistxattr_defined
#define __sys_Xllistxattr_defined 1
__CDECLARE_XSC(,__ssize_t,llistxattr,(char const *__path, char *__listbuf, __size_t __listbufsize),(__path,__listbuf,__listbufsize))
#endif /* !__sys_Xllistxattr_defined */
#endif /* sys_Xllistxattr... */
#if __CRT_HAVE_XSC(lremovexattr)
#ifndef __sys_Xlremovexattr_defined
#define __sys_Xlremovexattr_defined 1
__CDECLARE_XSC(,__errno_t,lremovexattr,(char const *__path, char const *__name),(__path,__name))
#endif /* !__sys_Xlremovexattr_defined */
#endif /* sys_Xlremovexattr... */
#if __CRT_HAVE_XSC(lseek)
#ifndef __sys_Xlseek_defined
#define __sys_Xlseek_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__int32_t,lseek,(__fd_t __fd, __int32_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#else /* ... */
#undef __sys_Xlseek_defined
#endif /* !... */
#endif /* !__sys_Xlseek_defined */
#endif /* sys_Xlseek... */
#if __CRT_HAVE_XSC(lseek64)
#ifndef __sys_Xlseek64_defined
#define __sys_Xlseek64_defined 1
__CDECLARE_XSC(,__int64_t,lseek64,(__fd_t __fd, __int64_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* !__sys_Xlseek64_defined */
#endif /* sys_Xlseek64... */
#if __CRT_HAVE_XSC(lsetxattr)
#ifndef __sys_Xlsetxattr_defined
#define __sys_Xlsetxattr_defined 1
__CDECLARE_XSC(,__errno_t,lsetxattr,(char const *__path, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__path,__name,__buf,__bufsize,__flags))
#endif /* !__sys_Xlsetxattr_defined */
#endif /* sys_Xlsetxattr... */
#if __CRT_HAVE_XSC(madvise)
#ifndef __sys_Xmadvise_defined
#define __sys_Xmadvise_defined 1
__CDECLARE_XSC(,__errno_t,madvise,(void *__addr, __size_t __len, __syscall_ulong_t __advice),(__addr,__len,__advice))
#endif /* !__sys_Xmadvise_defined */
#endif /* sys_Xmadvise... */
#if __CRT_HAVE_XSC(maplibrary)
#ifndef __sys_Xmaplibrary_defined
#define __sys_Xmaplibrary_defined 1
/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
__CDECLARE_XSC(,void *,maplibrary,(void *__addr, __syscall_ulong_t __flags, __fd_t __fd, void *__hdrv, __size_t __hdrc),(__addr,__flags,__fd,__hdrv,__hdrc))
#endif /* !__sys_Xmaplibrary_defined */
#endif /* sys_Xmaplibrary... */
#if __CRT_HAVE_XSC(mincore)
#ifndef __sys_Xmincore_defined
#define __sys_Xmincore_defined 1
__CDECLARE_XSC(,__errno_t,mincore,(void *__start, __size_t __len, __uint8_t *__vec),(__start,__len,__vec))
#endif /* !__sys_Xmincore_defined */
#endif /* sys_Xmincore... */
#if __CRT_HAVE_XSC(mkdir)
#ifndef __sys_Xmkdir_defined
#define __sys_Xmkdir_defined 1
__CDECLARE_XSC(,__errno_t,mkdir,(char const *__pathname, __mode_t __mode),(__pathname,__mode))
#endif /* !__sys_Xmkdir_defined */
#endif /* sys_Xmkdir... */
#if __CRT_HAVE_XSC(mkdirat)
#ifndef __sys_Xmkdirat_defined
#define __sys_Xmkdirat_defined 1
__CDECLARE_XSC(,__errno_t,mkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode),(__dirfd,__pathname,__mode))
#endif /* !__sys_Xmkdirat_defined */
#endif /* sys_Xmkdirat... */
#if __CRT_HAVE_XSC(mknod)
#ifndef __sys_Xmknod_defined
#define __sys_Xmknod_defined 1
__CDECLARE_XSC(,__errno_t,mknod,(char const *__nodename, __mode_t __mode, __dev_t __dev),(__nodename,__mode,__dev))
#endif /* !__sys_Xmknod_defined */
#endif /* sys_Xmknod... */
#if __CRT_HAVE_XSC(mknodat)
#ifndef __sys_Xmknodat_defined
#define __sys_Xmknodat_defined 1
__CDECLARE_XSC(,__errno_t,mknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev),(__dirfd,__nodename,__mode,__dev))
#endif /* !__sys_Xmknodat_defined */
#endif /* sys_Xmknodat... */
#if __CRT_HAVE_XSC(mktty)
#ifndef __sys_Xmktty_defined
#define __sys_Xmktty_defined 1
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
__CDECLARE_XSC(,__fd_t,mktty,(__fd_t __keyboard, __fd_t __display, char const *__name, __syscall_ulong_t __rsvd),(__keyboard,__display,__name,__rsvd))
#endif /* !__sys_Xmktty_defined */
#endif /* sys_Xmktty... */
#if __CRT_HAVE_XSC(mlock)
#ifndef __sys_Xmlock_defined
#define __sys_Xmlock_defined 1
__CDECLARE_XSC(,__errno_t,mlock,(void const *__addr, __size_t __len),(__addr,__len))
#endif /* !__sys_Xmlock_defined */
#endif /* sys_Xmlock... */
#if __CRT_HAVE_XSC(mlockall)
#ifndef __sys_Xmlockall_defined
#define __sys_Xmlockall_defined 1
__CDECLARE_XSC(,__errno_t,mlockall,(__syscall_ulong_t __flags),(__flags))
#endif /* !__sys_Xmlockall_defined */
#endif /* sys_Xmlockall... */
#if __CRT_HAVE_XSC(mmap)
#ifndef __sys_Xmmap_defined
#define __sys_Xmmap_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
__CDECLARE_XSC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#else /* #elif defined(__x86_64__) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
__CDECLARE_XSC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* ... */
#endif /* !__sys_Xmmap_defined */
#endif /* sys_Xmmap... */
#if __CRT_HAVE_XSC(mmap2)
#ifndef __sys_Xmmap2_defined
#define __sys_Xmmap2_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,void *,mmap2,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __pgoffset),(__addr,__len,__prot,__flags,__fd,__pgoffset))
#else /* ... */
#undef __sys_Xmmap2_defined
#endif /* !... */
#endif /* !__sys_Xmmap2_defined */
#endif /* sys_Xmmap2... */
#if __CRT_HAVE_XSC(modify_ldt)
#ifndef __sys_Xmodify_ldt_defined
#define __sys_Xmodify_ldt_defined 1
__CDECLARE_XSC(,__syscall_slong_t,modify_ldt,(__syscall_ulong_t __func, void *__ptr, __syscall_ulong_t __bytecount),(__func,__ptr,__bytecount))
#endif /* !__sys_Xmodify_ldt_defined */
#endif /* sys_Xmodify_ldt... */
#if __CRT_HAVE_XSC(mount)
#ifndef __sys_Xmount_defined
#define __sys_Xmount_defined 1
__CDECLARE_XSC(,__errno_t,mount,(char const *__special_file, char const *__dir, char const *__fstype, __syscall_ulong_t __rwflag, void const *__data),(__special_file,__dir,__fstype,__rwflag,__data))
#endif /* !__sys_Xmount_defined */
#endif /* sys_Xmount... */
#if __CRT_HAVE_XSC(mprotect)
#ifndef __sys_Xmprotect_defined
#define __sys_Xmprotect_defined 1
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
__CDECLARE_XSC(,__errno_t,mprotect,(void *__addr, __size_t __len, __syscall_ulong_t __prot),(__addr,__len,__prot))
#endif /* !__sys_Xmprotect_defined */
#endif /* sys_Xmprotect... */
#if __CRT_HAVE_XSC(mremap)
#ifndef __sys_Xmremap_defined
#define __sys_Xmremap_defined 1
/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
__CDECLARE_XSC(,void *,mremap,(void *__addr, __size_t __old_len, __size_t __new_len, __syscall_ulong_t __flags, void *__new_address),(__addr,__old_len,__new_len,__flags,__new_address))
#endif /* !__sys_Xmremap_defined */
#endif /* sys_Xmremap... */
#if __CRT_HAVE_XSC(msync)
#ifndef __sys_Xmsync_defined
#define __sys_Xmsync_defined 1
__CDECLARE_XSC(,__errno_t,msync,(void *__addr, __size_t __len, __syscall_ulong_t __flags),(__addr,__len,__flags))
#endif /* !__sys_Xmsync_defined */
#endif /* sys_Xmsync... */
#if __CRT_HAVE_XSC(munlock)
#ifndef __sys_Xmunlock_defined
#define __sys_Xmunlock_defined 1
__CDECLARE_XSC(,__errno_t,munlock,(void const *__addr, __size_t __len),(__addr,__len))
#endif /* !__sys_Xmunlock_defined */
#endif /* sys_Xmunlock... */
#if __CRT_HAVE_XSC(munlockall)
#ifndef __sys_Xmunlockall_defined
#define __sys_Xmunlockall_defined 1
__CDECLARE_XSC(,__errno_t,munlockall,(void),())
#endif /* !__sys_Xmunlockall_defined */
#endif /* sys_Xmunlockall... */
#if __CRT_HAVE_XSC(munmap)
#ifndef __sys_Xmunmap_defined
#define __sys_Xmunmap_defined 1
__CDECLARE_XSC(,__errno_t,munmap,(void *__addr, __size_t __len),(__addr,__len))
#endif /* !__sys_Xmunmap_defined */
#endif /* sys_Xmunmap... */
#if __CRT_HAVE_XSC(name_to_handle_at)
#ifndef __sys_Xname_to_handle_at_defined
#define __sys_Xname_to_handle_at_defined 1
__CDECLARE_XSC(,__errno_t,name_to_handle_at,(__fd_t __dirfd, char const *__name, struct file_handle *__handle, __int32_t *__mnt_id, __syscall_ulong_t __flags),(__dirfd,__name,__handle,__mnt_id,__flags))
#endif /* !__sys_Xname_to_handle_at_defined */
#endif /* sys_Xname_to_handle_at... */
#if __CRT_HAVE_XSC(nanosleep)
#ifndef __sys_Xnanosleep_defined
#define __sys_Xnanosleep_defined 1
__CDECLARE_XSC(,__errno_t,nanosleep,(struct __timespec32 const *__req, struct __timespec32 *__rem),(__req,__rem))
#endif /* !__sys_Xnanosleep_defined */
#endif /* sys_Xnanosleep... */
#if __CRT_HAVE_XSC(nanosleep64)
#ifndef __sys_Xnanosleep64_defined
#define __sys_Xnanosleep64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,nanosleep64,(struct __timespec64 const *__req, struct __timespec64 *__rem),(__req,__rem))
#else /* ... */
#undef __sys_Xnanosleep64_defined
#endif /* !... */
#endif /* !__sys_Xnanosleep64_defined */
#endif /* sys_Xnanosleep64... */
#if __CRT_HAVE_XSC(nice)
#ifndef __sys_Xnice_defined
#define __sys_Xnice_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,nice,(__syscall_slong_t __inc),(__inc))
#else /* ... */
#undef __sys_Xnice_defined
#endif /* !... */
#endif /* !__sys_Xnice_defined */
#endif /* sys_Xnice... */
#if __CRT_HAVE_XSC(oldolduname)
#ifndef __sys_Xoldolduname_defined
#define __sys_Xoldolduname_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,oldolduname,(struct linux_oldolduname *__name),(__name))
#else /* ... */
#undef __sys_Xoldolduname_defined
#endif /* !... */
#endif /* !__sys_Xoldolduname_defined */
#endif /* sys_Xoldolduname... */
#if __CRT_HAVE_XSC(olduname)
#ifndef __sys_Xolduname_defined
#define __sys_Xolduname_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,olduname,(struct linux_olduname *__name),(__name))
#else /* ... */
#undef __sys_Xolduname_defined
#endif /* !... */
#endif /* !__sys_Xolduname_defined */
#endif /* sys_Xolduname... */
#if __CRT_HAVE_XSC(open)
#ifndef __sys_Xopen_defined
#define __sys_Xopen_defined 1
__CDECLARE_XSC(,__fd_t,open,(char const *__filename, __oflag_t __oflags, __mode_t __mode),(__filename,__oflags,__mode))
#endif /* !__sys_Xopen_defined */
#endif /* sys_Xopen... */
#if __CRT_HAVE_XSC(open_by_handle_at)
#ifndef __sys_Xopen_by_handle_at_defined
#define __sys_Xopen_by_handle_at_defined 1
__CDECLARE_XSC(,__fd_t,open_by_handle_at,(__fd_t __mountdirfd, struct file_handle *__handle, __syscall_ulong_t __flags),(__mountdirfd,__handle,__flags))
#endif /* !__sys_Xopen_by_handle_at_defined */
#endif /* sys_Xopen_by_handle_at... */
#if __CRT_HAVE_XSC(openat)
#ifndef __sys_Xopenat_defined
#define __sys_Xopenat_defined 1
__CDECLARE_XSC(,__fd_t,openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, __mode_t __mode),(__dirfd,__filename,__oflags,__mode))
#endif /* !__sys_Xopenat_defined */
#endif /* sys_Xopenat... */
#if __CRT_HAVE_XSC(openpty)
#ifndef __sys_Xopenpty_defined
#define __sys_Xopenpty_defined 1
/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
__CDECLARE_XSC(,__errno_t,openpty,(__fd_t *__amaster, __fd_t *__aslave, char *__name, struct termios const *__termp, struct winsize const *__winp),(__amaster,__aslave,__name,__termp,__winp))
#endif /* !__sys_Xopenpty_defined */
#endif /* sys_Xopenpty... */
#if __CRT_HAVE_XSC(pause)
#ifndef __sys_Xpause_defined
#define __sys_Xpause_defined 1
__CDECLARE_XSC(,__errno_t,pause,(void),())
#endif /* !__sys_Xpause_defined */
#endif /* sys_Xpause... */
#if __CRT_HAVE_XSC(pipe)
#ifndef __sys_Xpipe_defined
#define __sys_Xpipe_defined 1
__CDECLARE_XSC(,__errno_t,pipe,(/*[2]*/ __fd_t *__pipedes),(__pipedes))
#endif /* !__sys_Xpipe_defined */
#endif /* sys_Xpipe... */
#if __CRT_HAVE_XSC(pipe2)
#ifndef __sys_Xpipe2_defined
#define __sys_Xpipe2_defined 1
__CDECLARE_XSC(,__errno_t,pipe2,(/*[2]*/ __fd_t *__pipedes, __oflag_t __flags),(__pipedes,__flags))
#endif /* !__sys_Xpipe2_defined */
#endif /* sys_Xpipe2... */
#if __CRT_HAVE_XSC(poll)
#ifndef __sys_Xpoll_defined
#define __sys_Xpoll_defined 1
__CDECLARE_XSC(,__ssize_t,poll,(struct pollfd *__fds, __size_t __nfds, __syscall_slong_t __timeout),(__fds,__nfds,__timeout))
#endif /* !__sys_Xpoll_defined */
#endif /* sys_Xpoll... */
#if __CRT_HAVE_XSC(ppoll)
#ifndef __sys_Xppoll_defined
#define __sys_Xppoll_defined 1
__CDECLARE_XSC(,__ssize_t,ppoll,(struct pollfd *__fds, __size_t __nfds, struct __timespec32 const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* !__sys_Xppoll_defined */
#endif /* sys_Xppoll... */
#if __CRT_HAVE_XSC(ppoll64)
#ifndef __sys_Xppoll64_defined
#define __sys_Xppoll64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__ssize_t,ppoll64,(struct pollfd *__fds, __size_t __nfds, struct __timespec64 const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#else /* ... */
#undef __sys_Xppoll64_defined
#endif /* !... */
#endif /* !__sys_Xppoll64_defined */
#endif /* sys_Xppoll64... */
#if __CRT_HAVE_XSC(pread64)
#ifndef __sys_Xpread64_defined
#define __sys_Xpread64_defined 1
__CDECLARE_XSC(,__ssize_t,pread64,(__fd_t __fd, void *__buf, __size_t __bufsize, __uint64_t __offset),(__fd,__buf,__bufsize,__offset))
#endif /* !__sys_Xpread64_defined */
#endif /* sys_Xpread64... */
#if __CRT_HAVE_XSC(pread64f)
#ifndef __sys_Xpread64f_defined
#define __sys_Xpread64f_defined 1
__CDECLARE_XSC(,__ssize_t,pread64f,(__fd_t __fd, void *__buf, __size_t __bufsize, __uint64_t __offset, __iomode_t __mode),(__fd,__buf,__bufsize,__offset,__mode))
#endif /* !__sys_Xpread64f_defined */
#endif /* sys_Xpread64f... */
#if __CRT_HAVE_XSC(preadv)
#ifndef __sys_Xpreadv_defined
#define __sys_Xpreadv_defined 1
__CDECLARE_XSC(,__ssize_t,preadv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* !__sys_Xpreadv_defined */
#endif /* sys_Xpreadv... */
#if __CRT_HAVE_XSC(preadvf)
#ifndef __sys_Xpreadvf_defined
#define __sys_Xpreadvf_defined 1
__CDECLARE_XSC(,__ssize_t,preadvf,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset, __iomode_t __mode),(__fd,__iovec,__count,__offset,__mode))
#endif /* !__sys_Xpreadvf_defined */
#endif /* sys_Xpreadvf... */
#if __CRT_HAVE_XSC(prlimit64)
#ifndef __sys_Xprlimit64_defined
#define __sys_Xprlimit64_defined 1
/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
__CDECLARE_XSC(,__errno_t,prlimit64,(__pid_t __pid, __syscall_ulong_t __resource, struct rlimit64 const *__new_limit, struct rlimit64 *__old_limit),(__pid,__resource,__new_limit,__old_limit))
#endif /* !__sys_Xprlimit64_defined */
#endif /* sys_Xprlimit64... */
#if __CRT_HAVE_XSC(process_vm_readv)
#ifndef __sys_Xprocess_vm_readv_defined
#define __sys_Xprocess_vm_readv_defined 1
__CDECLARE_XSC(,__ssize_t,process_vm_readv,(__pid_t __pid, struct iovec const *__lvec, __size_t __liovcnt, struct iovec const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* !__sys_Xprocess_vm_readv_defined */
#endif /* sys_Xprocess_vm_readv... */
#if __CRT_HAVE_XSC(process_vm_writev)
#ifndef __sys_Xprocess_vm_writev_defined
#define __sys_Xprocess_vm_writev_defined 1
__CDECLARE_XSC(,__ssize_t,process_vm_writev,(__pid_t __pid, struct iovec const *__lvec, __size_t __liovcnt, struct iovec const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* !__sys_Xprocess_vm_writev_defined */
#endif /* sys_Xprocess_vm_writev... */
#if __CRT_HAVE_XSC(profil)
#ifndef __sys_Xprofil_defined
#define __sys_Xprofil_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,profil,(__uint16_t *__sample_buffer, __size_t __size, __size_t __offset, __syscall_ulong_t __scale),(__sample_buffer,__size,__offset,__scale))
#else /* ... */
#undef __sys_Xprofil_defined
#endif /* !... */
#endif /* !__sys_Xprofil_defined */
#endif /* sys_Xprofil... */
#if __CRT_HAVE_XSC(pselect6)
#ifndef __sys_Xpselect6_defined
#define __sys_Xpselect6_defined 1
__CDECLARE_XSC(,__ssize_t,pselect6,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timespec32 const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#endif /* !__sys_Xpselect6_defined */
#endif /* sys_Xpselect6... */
#if __CRT_HAVE_XSC(pselect6_64)
#ifndef __sys_Xpselect6_64_defined
#define __sys_Xpselect6_64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__ssize_t,pselect6_64,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timespec64 const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#else /* ... */
#undef __sys_Xpselect6_64_defined
#endif /* !... */
#endif /* !__sys_Xpselect6_64_defined */
#endif /* sys_Xpselect6_64... */
#if __CRT_HAVE_XSC(ptrace)
#ifndef __sys_Xptrace_defined
#define __sys_Xptrace_defined 1
__CDECLARE_XSC(,__syscall_slong_t,ptrace,(__syscall_ulong_t __request, __pid_t __pid, void *__addr, void *__data),(__request,__pid,__addr,__data))
#endif /* !__sys_Xptrace_defined */
#endif /* sys_Xptrace... */
#if __CRT_HAVE_XSC(pwrite64)
#ifndef __sys_Xpwrite64_defined
#define __sys_Xpwrite64_defined 1
__CDECLARE_XSC(,__ssize_t,pwrite64,(__fd_t __fd, void const *__buf, __size_t __bufsize, __uint64_t __offset),(__fd,__buf,__bufsize,__offset))
#endif /* !__sys_Xpwrite64_defined */
#endif /* sys_Xpwrite64... */
#if __CRT_HAVE_XSC(pwrite64f)
#ifndef __sys_Xpwrite64f_defined
#define __sys_Xpwrite64f_defined 1
__CDECLARE_XSC(,__ssize_t,pwrite64f,(__fd_t __fd, void const *__buf, __size_t __bufsize, __uint64_t __offset, __iomode_t __mode),(__fd,__buf,__bufsize,__offset,__mode))
#endif /* !__sys_Xpwrite64f_defined */
#endif /* sys_Xpwrite64f... */
#if __CRT_HAVE_XSC(pwritev)
#ifndef __sys_Xpwritev_defined
#define __sys_Xpwritev_defined 1
__CDECLARE_XSC(,__ssize_t,pwritev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* !__sys_Xpwritev_defined */
#endif /* sys_Xpwritev... */
#if __CRT_HAVE_XSC(pwritevf)
#ifndef __sys_Xpwritevf_defined
#define __sys_Xpwritevf_defined 1
__CDECLARE_XSC(,__ssize_t,pwritevf,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset, __iomode_t __mode),(__fd,__iovec,__count,__offset,__mode))
#endif /* !__sys_Xpwritevf_defined */
#endif /* sys_Xpwritevf... */
#if __CRT_HAVE_XSC(raiseat)
#ifndef __sys_Xraiseat_defined
#define __sys_Xraiseat_defined 1
/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
__CDECLARE_XSC(,__errno_t,raiseat,(struct ucpustate const *__state, struct __siginfo_struct const *__si),(__state,__si))
#endif /* !__sys_Xraiseat_defined */
#endif /* sys_Xraiseat... */
#if __CRT_HAVE_XSC(read)
#ifndef __sys_Xread_defined
#define __sys_Xread_defined 1
__CDECLARE_XSC(,__ssize_t,read,(__fd_t __fd, void *__buf, __size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* !__sys_Xread_defined */
#endif /* sys_Xread... */
#if __CRT_HAVE_XSC(readahead)
#ifndef __sys_Xreadahead_defined
#define __sys_Xreadahead_defined 1
__CDECLARE_XSC(,__ssize_t,readahead,(__fd_t __fd, __uint64_t __offset, __size_t __count),(__fd,__offset,__count))
#endif /* !__sys_Xreadahead_defined */
#endif /* sys_Xreadahead... */
#if __CRT_HAVE_XSC(readdir)
#ifndef __sys_Xreaddir_defined
#define __sys_Xreaddir_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
__CDECLARE_XSC(,__errno_t,readdir,(__fd_t __fd, struct old_linux_dirent *__dirp, __size_t __count),(__fd,__dirp,__count))
#else /* ... */
#undef __sys_Xreaddir_defined
#endif /* !... */
#endif /* !__sys_Xreaddir_defined */
#endif /* sys_Xreaddir... */
#if __CRT_HAVE_XSC(readf)
#ifndef __sys_Xreadf_defined
#define __sys_Xreadf_defined 1
__CDECLARE_XSC(,__ssize_t,readf,(__fd_t __fd, void *__buf, __size_t __bufsize, __iomode_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* !__sys_Xreadf_defined */
#endif /* sys_Xreadf... */
#if __CRT_HAVE_XSC(readlink)
#ifndef __sys_Xreadlink_defined
#define __sys_Xreadlink_defined 1
__CDECLARE_XSC(,__ssize_t,readlink,(char const *__path, char *__buf, __size_t __buflen),(__path,__buf,__buflen))
#endif /* !__sys_Xreadlink_defined */
#endif /* sys_Xreadlink... */
#if __CRT_HAVE_XSC(readlinkat)
#ifndef __sys_Xreadlinkat_defined
#define __sys_Xreadlinkat_defined 1
__CDECLARE_XSC(,__ssize_t,readlinkat,(__fd_t __dirfd, char const *__path, char *__buf, __size_t __buflen),(__dirfd,__path,__buf,__buflen))
#endif /* !__sys_Xreadlinkat_defined */
#endif /* sys_Xreadlinkat... */
#if __CRT_HAVE_XSC(readv)
#ifndef __sys_Xreadv_defined
#define __sys_Xreadv_defined 1
__CDECLARE_XSC(,__ssize_t,readv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* !__sys_Xreadv_defined */
#endif /* sys_Xreadv... */
#if __CRT_HAVE_XSC(readvf)
#ifndef __sys_Xreadvf_defined
#define __sys_Xreadvf_defined 1
__CDECLARE_XSC(,__ssize_t,readvf,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __iomode_t __mode),(__fd,__iovec,__count,__mode))
#endif /* !__sys_Xreadvf_defined */
#endif /* sys_Xreadvf... */
#if __CRT_HAVE_XSC(reboot)
#ifndef __sys_Xreboot_defined
#define __sys_Xreboot_defined 1
/* @param: howto: One of the `RB_*' constants from <sys/reboot.h> */
__CDECLARE_XSC(,__errno_t,reboot,(__syscall_ulong_t __how),(__how))
#endif /* !__sys_Xreboot_defined */
#endif /* sys_Xreboot... */
#if __CRT_HAVE_XSC(recvfrom)
#ifndef __sys_Xrecvfrom_defined
#define __sys_Xrecvfrom_defined 1
__CDECLARE_XSC(,__ssize_t,recvfrom,(__fd_t __sockfd, void *__buf, __size_t __bufsize, __syscall_ulong_t __flags, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__buf,__bufsize,__flags,__addr,__addr_len))
#endif /* !__sys_Xrecvfrom_defined */
#endif /* sys_Xrecvfrom... */
#if __CRT_HAVE_XSC(recvmmsg)
#ifndef __sys_Xrecvmmsg_defined
#define __sys_Xrecvmmsg_defined 1
__CDECLARE_XSC(,__ssize_t,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct __timespec32 *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#endif /* !__sys_Xrecvmmsg_defined */
#endif /* sys_Xrecvmmsg... */
#if __CRT_HAVE_XSC(recvmmsg64)
#ifndef __sys_Xrecvmmsg64_defined
#define __sys_Xrecvmmsg64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__ssize_t,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct __timespec64 *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#else /* ... */
#undef __sys_Xrecvmmsg64_defined
#endif /* !... */
#endif /* !__sys_Xrecvmmsg64_defined */
#endif /* sys_Xrecvmmsg64... */
#if __CRT_HAVE_XSC(recvmsg)
#ifndef __sys_Xrecvmsg_defined
#define __sys_Xrecvmsg_defined 1
__CDECLARE_XSC(,__ssize_t,recvmsg,(__fd_t __sockfd, struct msghdr *__message, __syscall_ulong_t __flags),(__sockfd,__message,__flags))
#endif /* !__sys_Xrecvmsg_defined */
#endif /* sys_Xrecvmsg... */
#if __CRT_HAVE_XSC(remap_file_pages)
#ifndef __sys_Xremap_file_pages_defined
#define __sys_Xremap_file_pages_defined 1
__CDECLARE_XSC(,__errno_t,remap_file_pages,(void *__start, __size_t __size, __syscall_ulong_t __prot, __size_t __pgoff, __syscall_ulong_t __flags),(__start,__size,__prot,__pgoff,__flags))
#endif /* !__sys_Xremap_file_pages_defined */
#endif /* sys_Xremap_file_pages... */
#if __CRT_HAVE_XSC(removexattr)
#ifndef __sys_Xremovexattr_defined
#define __sys_Xremovexattr_defined 1
__CDECLARE_XSC(,__errno_t,removexattr,(char const *__path, char const *__name),(__path,__name))
#endif /* !__sys_Xremovexattr_defined */
#endif /* sys_Xremovexattr... */
#if __CRT_HAVE_XSC(rename)
#ifndef __sys_Xrename_defined
#define __sys_Xrename_defined 1
__CDECLARE_XSC(,__errno_t,rename,(char const *__oldname, char const *__newname_or_path),(__oldname,__newname_or_path))
#endif /* !__sys_Xrename_defined */
#endif /* sys_Xrename... */
#if __CRT_HAVE_XSC(renameat)
#ifndef __sys_Xrenameat_defined
#define __sys_Xrenameat_defined 1
__CDECLARE_XSC(,__errno_t,renameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path),(__oldfd,__oldname,__newfd,__newname_or_path))
#endif /* !__sys_Xrenameat_defined */
#endif /* sys_Xrenameat... */
#if __CRT_HAVE_XSC(renameat2)
#ifndef __sys_Xrenameat2_defined
#define __sys_Xrenameat2_defined 1
/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
__CDECLARE_XSC(,__errno_t,renameat2,(__fd_t __olddirfd, char const *__oldpath, __fd_t __newdirfd, char const *__newpath, __syscall_ulong_t __flags),(__olddirfd,__oldpath,__newdirfd,__newpath,__flags))
#endif /* !__sys_Xrenameat2_defined */
#endif /* sys_Xrenameat2... */
#if __CRT_HAVE_XSC(rmdir)
#ifndef __sys_Xrmdir_defined
#define __sys_Xrmdir_defined 1
__CDECLARE_XSC(,__errno_t,rmdir,(char const *__path),(__path))
#endif /* !__sys_Xrmdir_defined */
#endif /* sys_Xrmdir... */
#if __CRT_HAVE_XSC(rpc_schedule)
#ifndef __sys_Xrpc_schedule_defined
#define __sys_Xrpc_schedule_defined 1
/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
__CDECLARE_XSC(,__syscall_slong_t,rpc_schedule,(__pid_t __target, __syscall_ulong_t __flags, __uint8_t const *__program, void **__arguments),(__target,__flags,__program,__arguments))
#endif /* !__sys_Xrpc_schedule_defined */
#endif /* sys_Xrpc_schedule... */
#if __CRT_HAVE_XSC(rpc_service)
#ifndef __sys_Xrpc_service_defined
#define __sys_Xrpc_service_defined 1
__CDECLARE_XSC(,__syscall_slong_t,rpc_service,(void),())
#endif /* !__sys_Xrpc_service_defined */
#endif /* sys_Xrpc_service... */
#if __CRT_HAVE_XSC(rt_sigaction)
#ifndef __sys_Xrt_sigaction_defined
#define __sys_Xrt_sigaction_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,rt_sigaction,(__syscall_ulong_t __signo, struct sigaction const *__act, struct sigaction *__oact, __size_t __sigsetsize),(__signo,__act,__oact,__sigsetsize))
#endif /* !__sys_Xrt_sigaction_defined */
#endif /* sys_Xrt_sigaction... */
#if __CRT_HAVE_XSC(rt_sigpending)
#ifndef __sys_Xrt_sigpending_defined
#define __sys_Xrt_sigpending_defined 1
__CDECLARE_XSC(,__errno_t,rt_sigpending,(struct __sigset_struct *__set, __size_t __sigsetsize),(__set,__sigsetsize))
#endif /* !__sys_Xrt_sigpending_defined */
#endif /* sys_Xrt_sigpending... */
#if __CRT_HAVE_XSC(rt_sigprocmask)
#ifndef __sys_Xrt_sigprocmask_defined
#define __sys_Xrt_sigprocmask_defined 1
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE_XSC(,__errno_t,rt_sigprocmask,(__syscall_ulong_t __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset, __size_t __sigsetsize),(__how,__set,__oset,__sigsetsize))
#endif /* !__sys_Xrt_sigprocmask_defined */
#endif /* sys_Xrt_sigprocmask... */
#if __CRT_HAVE_XSC(rt_sigqueueinfo)
#ifndef __sys_Xrt_sigqueueinfo_defined
#define __sys_Xrt_sigqueueinfo_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,rt_sigqueueinfo,(__pid_t __tgid, __syscall_ulong_t __signo, struct __siginfo_struct const *__uinfo),(__tgid,__signo,__uinfo))
#endif /* !__sys_Xrt_sigqueueinfo_defined */
#endif /* sys_Xrt_sigqueueinfo... */
#if __CRT_HAVE_XSC(rt_sigreturn)
#ifndef __sys_Xrt_sigreturn_defined
#define __sys_Xrt_sigreturn_defined 1
#ifdef __x86_64__
__CDECLARE_VOID_XSC(,rt_sigreturn,(void),())
#else /* ... */
#undef __sys_Xrt_sigreturn_defined
#endif /* !... */
#endif /* !__sys_Xrt_sigreturn_defined */
#endif /* sys_Xrt_sigreturn... */
#if __CRT_HAVE_XSC(rt_sigsuspend)
#ifndef __sys_Xrt_sigsuspend_defined
#define __sys_Xrt_sigsuspend_defined 1
__CDECLARE_XSC(,__errno_t,rt_sigsuspend,(struct __sigset_struct const *__set, __size_t __sigsetsize),(__set,__sigsetsize))
#endif /* !__sys_Xrt_sigsuspend_defined */
#endif /* sys_Xrt_sigsuspend... */
#if __CRT_HAVE_XSC(rt_sigtimedwait)
#ifndef __sys_Xrt_sigtimedwait_defined
#define __sys_Xrt_sigtimedwait_defined 1
__CDECLARE_XSC(,__syscall_slong_t,rt_sigtimedwait,(struct __sigset_struct const *__set, struct __siginfo_struct *__info, struct __timespec32 const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* !__sys_Xrt_sigtimedwait_defined */
#endif /* sys_Xrt_sigtimedwait... */
#if __CRT_HAVE_XSC(rt_sigtimedwait64)
#ifndef __sys_Xrt_sigtimedwait64_defined
#define __sys_Xrt_sigtimedwait64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__syscall_slong_t,rt_sigtimedwait64,(struct __sigset_struct const *__set, struct __siginfo_struct *__info, struct __timespec64 const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#else /* ... */
#undef __sys_Xrt_sigtimedwait64_defined
#endif /* !... */
#endif /* !__sys_Xrt_sigtimedwait64_defined */
#endif /* sys_Xrt_sigtimedwait64... */
#if __CRT_HAVE_XSC(rt_tgsigqueueinfo)
#ifndef __sys_Xrt_tgsigqueueinfo_defined
#define __sys_Xrt_tgsigqueueinfo_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,rt_tgsigqueueinfo,(__pid_t __tgid, __pid_t __tid, __syscall_ulong_t __signo, struct __siginfo_struct const *__uinfo),(__tgid,__tid,__signo,__uinfo))
#endif /* !__sys_Xrt_tgsigqueueinfo_defined */
#endif /* sys_Xrt_tgsigqueueinfo... */
#if __CRT_HAVE_XSC(sched_get_priority_max)
#ifndef __sys_Xsched_get_priority_max_defined
#define __sys_Xsched_get_priority_max_defined 1
__CDECLARE_XSC(,__syscall_slong_t,sched_get_priority_max,(__syscall_ulong_t __algorithm),(__algorithm))
#endif /* !__sys_Xsched_get_priority_max_defined */
#endif /* sys_Xsched_get_priority_max... */
#if __CRT_HAVE_XSC(sched_get_priority_min)
#ifndef __sys_Xsched_get_priority_min_defined
#define __sys_Xsched_get_priority_min_defined 1
__CDECLARE_XSC(,__syscall_slong_t,sched_get_priority_min,(__syscall_ulong_t __algorithm),(__algorithm))
#endif /* !__sys_Xsched_get_priority_min_defined */
#endif /* sys_Xsched_get_priority_min... */
#if __CRT_HAVE_XSC(sched_getaffinity)
#ifndef __sys_Xsched_getaffinity_defined
#define __sys_Xsched_getaffinity_defined 1
__CDECLARE_XSC(,__errno_t,sched_getaffinity,(__pid_t __pid, __size_t __cpusetsize, struct __cpu_set_struct *__cpuset),(__pid,__cpusetsize,__cpuset))
#endif /* !__sys_Xsched_getaffinity_defined */
#endif /* sys_Xsched_getaffinity... */
#if __CRT_HAVE_XSC(sched_getparam)
#ifndef __sys_Xsched_getparam_defined
#define __sys_Xsched_getparam_defined 1
__CDECLARE_XSC(,__errno_t,sched_getparam,(__pid_t __pid, struct sched_param *__param),(__pid,__param))
#endif /* !__sys_Xsched_getparam_defined */
#endif /* sys_Xsched_getparam... */
#if __CRT_HAVE_XSC(sched_getscheduler)
#ifndef __sys_Xsched_getscheduler_defined
#define __sys_Xsched_getscheduler_defined 1
__CDECLARE_XSC(,__syscall_slong_t,sched_getscheduler,(__pid_t __pid),(__pid))
#endif /* !__sys_Xsched_getscheduler_defined */
#endif /* sys_Xsched_getscheduler... */
#if __CRT_HAVE_XSC(sched_rr_get_interval)
#ifndef __sys_Xsched_rr_get_interval_defined
#define __sys_Xsched_rr_get_interval_defined 1
__CDECLARE_XSC(,__errno_t,sched_rr_get_interval,(__pid_t __pid, struct __timespec32 *__tms),(__pid,__tms))
#endif /* !__sys_Xsched_rr_get_interval_defined */
#endif /* sys_Xsched_rr_get_interval... */
#if __CRT_HAVE_XSC(sched_rr_get_interval64)
#ifndef __sys_Xsched_rr_get_interval64_defined
#define __sys_Xsched_rr_get_interval64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),(__pid,__tms))
#else /* ... */
#undef __sys_Xsched_rr_get_interval64_defined
#endif /* !... */
#endif /* !__sys_Xsched_rr_get_interval64_defined */
#endif /* sys_Xsched_rr_get_interval64... */
#if __CRT_HAVE_XSC(sched_setaffinity)
#ifndef __sys_Xsched_setaffinity_defined
#define __sys_Xsched_setaffinity_defined 1
__CDECLARE_XSC(,__errno_t,sched_setaffinity,(__pid_t __pid, __size_t __cpusetsize, struct __cpu_set_struct const *__cpuset),(__pid,__cpusetsize,__cpuset))
#endif /* !__sys_Xsched_setaffinity_defined */
#endif /* sys_Xsched_setaffinity... */
#if __CRT_HAVE_XSC(sched_setparam)
#ifndef __sys_Xsched_setparam_defined
#define __sys_Xsched_setparam_defined 1
__CDECLARE_XSC(,__errno_t,sched_setparam,(__pid_t __pid, struct sched_param const *__param),(__pid,__param))
#endif /* !__sys_Xsched_setparam_defined */
#endif /* sys_Xsched_setparam... */
#if __CRT_HAVE_XSC(sched_setscheduler)
#ifndef __sys_Xsched_setscheduler_defined
#define __sys_Xsched_setscheduler_defined 1
__CDECLARE_XSC(,__errno_t,sched_setscheduler,(__pid_t __pid, __syscall_ulong_t __policy, struct sched_param const *__param),(__pid,__policy,__param))
#endif /* !__sys_Xsched_setscheduler_defined */
#endif /* sys_Xsched_setscheduler... */
#if __CRT_HAVE_XSC(sched_yield)
#ifndef __sys_Xsched_yield_defined
#define __sys_Xsched_yield_defined 1
__CDECLARE_XSC(,__errno_t,sched_yield,(void),())
#endif /* !__sys_Xsched_yield_defined */
#endif /* sys_Xsched_yield... */
#if __CRT_HAVE_XSC(select)
#ifndef __sys_Xselect_defined
#define __sys_Xselect_defined 1
__CDECLARE_XSC(,__ssize_t,select,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timeval32 *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* !__sys_Xselect_defined */
#endif /* sys_Xselect... */
#if __CRT_HAVE_XSC(select64)
#ifndef __sys_Xselect64_defined
#define __sys_Xselect64_defined 1
__CDECLARE_XSC(,__ssize_t,select64,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timeval64 *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* !__sys_Xselect64_defined */
#endif /* sys_Xselect64... */
#if __CRT_HAVE_XSC(sendfile)
#ifndef __sys_Xsendfile_defined
#define __sys_Xsendfile_defined 1
__CDECLARE_XSC(,__ssize_t,sendfile,(__fd_t __out_fd, __fd_t __in_fd, __syscall_ulong_t *__offset, __size_t __count),(__out_fd,__in_fd,__offset,__count))
#endif /* !__sys_Xsendfile_defined */
#endif /* sys_Xsendfile... */
#if __CRT_HAVE_XSC(sendfile64)
#ifndef __sys_Xsendfile64_defined
#define __sys_Xsendfile64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__ssize_t,sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __uint64_t *__offset, __size_t __count),(__out_fd,__in_fd,__offset,__count))
#else /* ... */
#undef __sys_Xsendfile64_defined
#endif /* !... */
#endif /* !__sys_Xsendfile64_defined */
#endif /* sys_Xsendfile64... */
#if __CRT_HAVE_XSC(sendmmsg)
#ifndef __sys_Xsendmmsg_defined
#define __sys_Xsendmmsg_defined 1
__CDECLARE_XSC(,__ssize_t,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags),(__sockfd,__vmessages,__vlen,__flags))
#endif /* !__sys_Xsendmmsg_defined */
#endif /* sys_Xsendmmsg... */
#if __CRT_HAVE_XSC(sendmsg)
#ifndef __sys_Xsendmsg_defined
#define __sys_Xsendmsg_defined 1
__CDECLARE_XSC(,__ssize_t,sendmsg,(__fd_t __sockfd, struct msghdr const *__message, __syscall_ulong_t __flags),(__sockfd,__message,__flags))
#endif /* !__sys_Xsendmsg_defined */
#endif /* sys_Xsendmsg... */
#if __CRT_HAVE_XSC(sendto)
#ifndef __sys_Xsendto_defined
#define __sys_Xsendto_defined 1
/* param flags: Set of `MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL|MSG_OOB' */
__CDECLARE_XSC(,__ssize_t,sendto,(__fd_t __sockfd, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__buf,__bufsize,__flags,__addr,__addr_len))
#endif /* !__sys_Xsendto_defined */
#endif /* sys_Xsendto... */
#if __CRT_HAVE_XSC(set_exception_handler)
#ifndef __sys_Xset_exception_handler_defined
#define __sys_Xset_exception_handler_defined 1
/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
__CDECLARE_XSC(,__errno_t,set_exception_handler,(__syscall_ulong_t __mode, __except_handler_t __handler, void *__handler_sp),(__mode,__handler,__handler_sp))
#endif /* !__sys_Xset_exception_handler_defined */
#endif /* sys_Xset_exception_handler... */
#if __CRT_HAVE_XSC(set_library_listdef)
#ifndef __sys_Xset_library_listdef_defined
#define __sys_Xset_library_listdef_defined 1
/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
__CDECLARE_XSC(,__errno_t,set_library_listdef,(struct library_listdef const *__listdef),(__listdef))
#endif /* !__sys_Xset_library_listdef_defined */
#endif /* sys_Xset_library_listdef... */
#if __CRT_HAVE_XSC(set_tid_address)
#ifndef __sys_Xset_tid_address_defined
#define __sys_Xset_tid_address_defined 1
__CDECLARE_XSC(,__pid_t,set_tid_address,(__pid_t *__tidptr),(__tidptr))
#endif /* !__sys_Xset_tid_address_defined */
#endif /* sys_Xset_tid_address... */
#if __CRT_HAVE_XSC(setdomainname)
#ifndef __sys_Xsetdomainname_defined
#define __sys_Xsetdomainname_defined 1
__CDECLARE_XSC(,__errno_t,setdomainname,(char const *__name, __size_t __len),(__name,__len))
#endif /* !__sys_Xsetdomainname_defined */
#endif /* sys_Xsetdomainname... */
#if __CRT_HAVE_XSC(setfsgid)
#ifndef __sys_Xsetfsgid_defined
#define __sys_Xsetfsgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,setfsgid,(__uint16_t __gid),(__gid))
#else /* ... */
#undef __sys_Xsetfsgid_defined
#endif /* !... */
#endif /* !__sys_Xsetfsgid_defined */
#endif /* sys_Xsetfsgid... */
#if __CRT_HAVE_XSC(setfsgid32)
#ifndef __sys_Xsetfsgid32_defined
#define __sys_Xsetfsgid32_defined 1
__CDECLARE_XSC(,__errno_t,setfsgid32,(__uint32_t __gid),(__gid))
#endif /* !__sys_Xsetfsgid32_defined */
#endif /* sys_Xsetfsgid32... */
#if __CRT_HAVE_XSC(setfsuid)
#ifndef __sys_Xsetfsuid_defined
#define __sys_Xsetfsuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,setfsuid,(__uint16_t __uid),(__uid))
#else /* ... */
#undef __sys_Xsetfsuid_defined
#endif /* !... */
#endif /* !__sys_Xsetfsuid_defined */
#endif /* sys_Xsetfsuid... */
#if __CRT_HAVE_XSC(setfsuid32)
#ifndef __sys_Xsetfsuid32_defined
#define __sys_Xsetfsuid32_defined 1
__CDECLARE_XSC(,__errno_t,setfsuid32,(__uint32_t __uid),(__uid))
#endif /* !__sys_Xsetfsuid32_defined */
#endif /* sys_Xsetfsuid32... */
#if __CRT_HAVE_XSC(setgid)
#ifndef __sys_Xsetgid_defined
#define __sys_Xsetgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,setgid,(__uint16_t __gid),(__gid))
#else /* ... */
#undef __sys_Xsetgid_defined
#endif /* !... */
#endif /* !__sys_Xsetgid_defined */
#endif /* sys_Xsetgid... */
#if __CRT_HAVE_XSC(setgid32)
#ifndef __sys_Xsetgid32_defined
#define __sys_Xsetgid32_defined 1
__CDECLARE_XSC(,__errno_t,setgid32,(__uint32_t __gid),(__gid))
#endif /* !__sys_Xsetgid32_defined */
#endif /* sys_Xsetgid32... */
#if __CRT_HAVE_XSC(setgroups)
#ifndef __sys_Xsetgroups_defined
#define __sys_Xsetgroups_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,setgroups,(__size_t __count, __uint16_t const *__groups),(__count,__groups))
#else /* ... */
#undef __sys_Xsetgroups_defined
#endif /* !... */
#endif /* !__sys_Xsetgroups_defined */
#endif /* sys_Xsetgroups... */
#if __CRT_HAVE_XSC(setgroups32)
#ifndef __sys_Xsetgroups32_defined
#define __sys_Xsetgroups32_defined 1
__CDECLARE_XSC(,__errno_t,setgroups32,(__size_t __count, __uint32_t const *__groups),(__count,__groups))
#endif /* !__sys_Xsetgroups32_defined */
#endif /* sys_Xsetgroups32... */
#if __CRT_HAVE_XSC(sethostname)
#ifndef __sys_Xsethostname_defined
#define __sys_Xsethostname_defined 1
__CDECLARE_XSC(,__errno_t,sethostname,(char const *__name, __size_t __len),(__name,__len))
#endif /* !__sys_Xsethostname_defined */
#endif /* sys_Xsethostname... */
#if __CRT_HAVE_XSC(setitimer)
#ifndef __sys_Xsetitimer_defined
#define __sys_Xsetitimer_defined 1
__CDECLARE_XSC(,__errno_t,setitimer,(__syscall_ulong_t __which, struct __itimerval32 const *__newval, struct __itimerval32 *__oldval),(__which,__newval,__oldval))
#endif /* !__sys_Xsetitimer_defined */
#endif /* sys_Xsetitimer... */
#if __CRT_HAVE_XSC(setitimer64)
#ifndef __sys_Xsetitimer64_defined
#define __sys_Xsetitimer64_defined 1
__CDECLARE_XSC(,__errno_t,setitimer64,(__syscall_ulong_t __which, struct __itimerval64 const *__newval, struct __itimerval64 *__oldval),(__which,__newval,__oldval))
#endif /* !__sys_Xsetitimer64_defined */
#endif /* sys_Xsetitimer64... */
#if __CRT_HAVE_XSC(setns)
#ifndef __sys_Xsetns_defined
#define __sys_Xsetns_defined 1
__CDECLARE_XSC(,__errno_t,setns,(__fd_t __fd, __syscall_ulong_t __nstype),(__fd,__nstype))
#endif /* !__sys_Xsetns_defined */
#endif /* sys_Xsetns... */
#if __CRT_HAVE_XSC(setpgid)
#ifndef __sys_Xsetpgid_defined
#define __sys_Xsetpgid_defined 1
__CDECLARE_XSC(,__errno_t,setpgid,(__pid_t __pid, __pid_t __pgid),(__pid,__pgid))
#endif /* !__sys_Xsetpgid_defined */
#endif /* sys_Xsetpgid... */
#if __CRT_HAVE_XSC(setpriority)
#ifndef __sys_Xsetpriority_defined
#define __sys_Xsetpriority_defined 1
__CDECLARE_XSC(,__errno_t,setpriority,(__syscall_ulong_t __which, __id_t __who, __syscall_ulong_t __value),(__which,__who,__value))
#endif /* !__sys_Xsetpriority_defined */
#endif /* sys_Xsetpriority... */
#if __CRT_HAVE_XSC(setregid)
#ifndef __sys_Xsetregid_defined
#define __sys_Xsetregid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,setregid,(__uint16_t __rgid, __uint16_t __egid),(__rgid,__egid))
#else /* ... */
#undef __sys_Xsetregid_defined
#endif /* !... */
#endif /* !__sys_Xsetregid_defined */
#endif /* sys_Xsetregid... */
#if __CRT_HAVE_XSC(setregid32)
#ifndef __sys_Xsetregid32_defined
#define __sys_Xsetregid32_defined 1
__CDECLARE_XSC(,__errno_t,setregid32,(__uint32_t __rgid, __uint32_t __egid),(__rgid,__egid))
#endif /* !__sys_Xsetregid32_defined */
#endif /* sys_Xsetregid32... */
#if __CRT_HAVE_XSC(setresgid)
#ifndef __sys_Xsetresgid_defined
#define __sys_Xsetresgid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,setresgid,(__uint16_t __rgid, __uint16_t __egid, __uint16_t __sgid),(__rgid,__egid,__sgid))
#else /* ... */
#undef __sys_Xsetresgid_defined
#endif /* !... */
#endif /* !__sys_Xsetresgid_defined */
#endif /* sys_Xsetresgid... */
#if __CRT_HAVE_XSC(setresgid32)
#ifndef __sys_Xsetresgid32_defined
#define __sys_Xsetresgid32_defined 1
__CDECLARE_XSC(,__errno_t,setresgid32,(__uint32_t __rgid, __uint32_t __egid, __uint32_t __sgid),(__rgid,__egid,__sgid))
#endif /* !__sys_Xsetresgid32_defined */
#endif /* sys_Xsetresgid32... */
#if __CRT_HAVE_XSC(setresuid)
#ifndef __sys_Xsetresuid_defined
#define __sys_Xsetresuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,setresuid,(__uint16_t __ruid, __uint16_t __euid, __uint16_t __suid),(__ruid,__euid,__suid))
#else /* ... */
#undef __sys_Xsetresuid_defined
#endif /* !... */
#endif /* !__sys_Xsetresuid_defined */
#endif /* sys_Xsetresuid... */
#if __CRT_HAVE_XSC(setresuid32)
#ifndef __sys_Xsetresuid32_defined
#define __sys_Xsetresuid32_defined 1
__CDECLARE_XSC(,__errno_t,setresuid32,(__uint32_t __ruid, __uint32_t __euid, __uint32_t __suid),(__ruid,__euid,__suid))
#endif /* !__sys_Xsetresuid32_defined */
#endif /* sys_Xsetresuid32... */
#if __CRT_HAVE_XSC(setreuid)
#ifndef __sys_Xsetreuid_defined
#define __sys_Xsetreuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,setreuid,(__uint16_t __ruid, __uint16_t __euid),(__ruid,__euid))
#else /* ... */
#undef __sys_Xsetreuid_defined
#endif /* !... */
#endif /* !__sys_Xsetreuid_defined */
#endif /* sys_Xsetreuid... */
#if __CRT_HAVE_XSC(setreuid32)
#ifndef __sys_Xsetreuid32_defined
#define __sys_Xsetreuid32_defined 1
__CDECLARE_XSC(,__errno_t,setreuid32,(__uint32_t __ruid, __uint32_t __euid),(__ruid,__euid))
#endif /* !__sys_Xsetreuid32_defined */
#endif /* sys_Xsetreuid32... */
#if __CRT_HAVE_XSC(setrlimit)
#ifndef __sys_Xsetrlimit_defined
#define __sys_Xsetrlimit_defined 1
__CDECLARE_XSC(,__errno_t,setrlimit,(__syscall_ulong_t __resource, struct rlimit const *__rlimits),(__resource,__rlimits))
#endif /* !__sys_Xsetrlimit_defined */
#endif /* sys_Xsetrlimit... */
#if __CRT_HAVE_XSC(setsid)
#ifndef __sys_Xsetsid_defined
#define __sys_Xsetsid_defined 1
__CDECLARE_XSC(,__pid_t,setsid,(void),())
#endif /* !__sys_Xsetsid_defined */
#endif /* sys_Xsetsid... */
#if __CRT_HAVE_XSC(setsockopt)
#ifndef __sys_Xsetsockopt_defined
#define __sys_Xsetsockopt_defined 1
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
__CDECLARE_XSC(,__errno_t,setsockopt,(__fd_t __sockfd, __syscall_ulong_t __level, __syscall_ulong_t __optname, void const *__optval, __socklen_t __optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* !__sys_Xsetsockopt_defined */
#endif /* sys_Xsetsockopt... */
#if __CRT_HAVE_XSC(settimeofday)
#ifndef __sys_Xsettimeofday_defined
#define __sys_Xsettimeofday_defined 1
__CDECLARE_XSC(,__errno_t,settimeofday,(struct __timeval32 const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* !__sys_Xsettimeofday_defined */
#endif /* sys_Xsettimeofday... */
#if __CRT_HAVE_XSC(settimeofday64)
#ifndef __sys_Xsettimeofday64_defined
#define __sys_Xsettimeofday64_defined 1
__CDECLARE_XSC(,__errno_t,settimeofday64,(struct __timeval64 const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* !__sys_Xsettimeofday64_defined */
#endif /* sys_Xsettimeofday64... */
#if __CRT_HAVE_XSC(setuid)
#ifndef __sys_Xsetuid_defined
#define __sys_Xsetuid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,setuid,(__uint16_t __uid),(__uid))
#else /* ... */
#undef __sys_Xsetuid_defined
#endif /* !... */
#endif /* !__sys_Xsetuid_defined */
#endif /* sys_Xsetuid... */
#if __CRT_HAVE_XSC(setuid32)
#ifndef __sys_Xsetuid32_defined
#define __sys_Xsetuid32_defined 1
__CDECLARE_XSC(,__errno_t,setuid32,(__uint32_t __uid),(__uid))
#endif /* !__sys_Xsetuid32_defined */
#endif /* sys_Xsetuid32... */
#if __CRT_HAVE_XSC(setxattr)
#ifndef __sys_Xsetxattr_defined
#define __sys_Xsetxattr_defined 1
__CDECLARE_XSC(,__errno_t,setxattr,(char const *__path, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__path,__name,__buf,__bufsize,__flags))
#endif /* !__sys_Xsetxattr_defined */
#endif /* sys_Xsetxattr... */
#if __CRT_HAVE_XSC(sgetmask)
#ifndef __sys_Xsgetmask_defined
#define __sys_Xsgetmask_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__syscall_ulong_t,sgetmask,(void),())
#else /* ... */
#undef __sys_Xsgetmask_defined
#endif /* !... */
#endif /* !__sys_Xsgetmask_defined */
#endif /* sys_Xsgetmask... */
#if __CRT_HAVE_XSC(shutdown)
#ifndef __sys_Xshutdown_defined
#define __sys_Xshutdown_defined 1
/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
__CDECLARE_XSC(,__errno_t,shutdown,(__fd_t __sockfd, __syscall_ulong_t __how),(__sockfd,__how))
#endif /* !__sys_Xshutdown_defined */
#endif /* sys_Xshutdown... */
#if __CRT_HAVE_XSC(sigaction)
#ifndef __sys_Xsigaction_defined
#define __sys_Xsigaction_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,sigaction,(__syscall_ulong_t __signo, struct sigaction const *__act, struct sigaction *__oact),(__signo,__act,__oact))
#else /* ... */
#undef __sys_Xsigaction_defined
#endif /* !... */
#endif /* !__sys_Xsigaction_defined */
#endif /* sys_Xsigaction... */
#if __CRT_HAVE_XSC(sigaltstack)
#ifndef __sys_Xsigaltstack_defined
#define __sys_Xsigaltstack_defined 1
__CDECLARE_XSC(,__errno_t,sigaltstack,(struct sigaltstack const *__ss, struct sigaltstack *__oss),(__ss,__oss))
#endif /* !__sys_Xsigaltstack_defined */
#endif /* sys_Xsigaltstack... */
#if __CRT_HAVE_XSC(signal)
#ifndef __sys_Xsignal_defined
#define __sys_Xsignal_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__sighandler_t,signal,(__syscall_ulong_t __signo, __sighandler_t __handler),(__signo,__handler))
#else /* ... */
#undef __sys_Xsignal_defined
#endif /* !... */
#endif /* !__sys_Xsignal_defined */
#endif /* sys_Xsignal... */
#if __CRT_HAVE_XSC(signalfd)
#ifndef __sys_Xsignalfd_defined
#define __sys_Xsignalfd_defined 1
__CDECLARE_XSC(,__errno_t,signalfd,(__fd_t __fd, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fd,__sigmask,__sigsetsize))
#endif /* !__sys_Xsignalfd_defined */
#endif /* sys_Xsignalfd... */
#if __CRT_HAVE_XSC(signalfd4)
#ifndef __sys_Xsignalfd4_defined
#define __sys_Xsignalfd4_defined 1
__CDECLARE_XSC(,__errno_t,signalfd4,(__fd_t __fd, struct __sigset_struct const *__sigmask, __size_t __sigsetsize, __syscall_ulong_t __flags),(__fd,__sigmask,__sigsetsize,__flags))
#endif /* !__sys_Xsignalfd4_defined */
#endif /* sys_Xsignalfd4... */
#if __CRT_HAVE_XSC(sigpending)
#ifndef __sys_Xsigpending_defined
#define __sys_Xsigpending_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,sigpending,(struct __sigset_struct *__set),(__set))
#else /* ... */
#undef __sys_Xsigpending_defined
#endif /* !... */
#endif /* !__sys_Xsigpending_defined */
#endif /* sys_Xsigpending... */
#if __CRT_HAVE_XSC(sigprocmask)
#ifndef __sys_Xsigprocmask_defined
#define __sys_Xsigprocmask_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE_XSC(,__errno_t,sigprocmask,(__syscall_ulong_t __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),(__how,__set,__oset))
#else /* ... */
#undef __sys_Xsigprocmask_defined
#endif /* !... */
#endif /* !__sys_Xsigprocmask_defined */
#endif /* sys_Xsigprocmask... */
#if __CRT_HAVE_XSC(sigsuspend)
#ifndef __sys_Xsigsuspend_defined
#define __sys_Xsigsuspend_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,sigsuspend,(struct __sigset_struct const *__set),(__set))
#else /* ... */
#undef __sys_Xsigsuspend_defined
#endif /* !... */
#endif /* !__sys_Xsigsuspend_defined */
#endif /* sys_Xsigsuspend... */
#if __CRT_HAVE_XSC(socket)
#ifndef __sys_Xsocket_defined
#define __sys_Xsocket_defined 1
__CDECLARE_XSC(,__fd_t,socket,(__syscall_ulong_t __domain, __syscall_ulong_t __type, __syscall_ulong_t __protocol),(__domain,__type,__protocol))
#endif /* !__sys_Xsocket_defined */
#endif /* sys_Xsocket... */
#if __CRT_HAVE_XSC(socketcall)
#ifndef __sys_Xsocketcall_defined
#define __sys_Xsocketcall_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,socketcall,(int __call, unsigned long *__args),(__call,__args))
#else /* ... */
#undef __sys_Xsocketcall_defined
#endif /* !... */
#endif /* !__sys_Xsocketcall_defined */
#endif /* sys_Xsocketcall... */
#if __CRT_HAVE_XSC(socketpair)
#ifndef __sys_Xsocketpair_defined
#define __sys_Xsocketpair_defined 1
__CDECLARE_XSC(,__errno_t,socketpair,(__syscall_ulong_t __domain, __syscall_ulong_t __type, __syscall_ulong_t __protocol, /*[2]*/ __fd_t *__fds),(__domain,__type,__protocol,__fds))
#endif /* !__sys_Xsocketpair_defined */
#endif /* sys_Xsocketpair... */
#if __CRT_HAVE_XSC(splice)
#ifndef __sys_Xsplice_defined
#define __sys_Xsplice_defined 1
__CDECLARE_XSC(,__ssize_t,splice,(__fd_t __fdin, __uint64_t *__offin, __fd_t __fdout, __uint64_t *__offout, __size_t __length, __syscall_ulong_t __flags),(__fdin,__offin,__fdout,__offout,__length,__flags))
#endif /* !__sys_Xsplice_defined */
#endif /* sys_Xsplice... */
#if __CRT_HAVE_XSC(ssetmask)
#ifndef __sys_Xssetmask_defined
#define __sys_Xssetmask_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__syscall_ulong_t,ssetmask,(__syscall_ulong_t __sigmask),(__sigmask))
#else /* ... */
#undef __sys_Xssetmask_defined
#endif /* !... */
#endif /* !__sys_Xssetmask_defined */
#endif /* sys_Xssetmask... */
#if __CRT_HAVE_XSC(statfs)
#ifndef __sys_Xstatfs_defined
#define __sys_Xstatfs_defined 1
__CDECLARE_XSC(,__errno_t,statfs,(char const *__file, struct __statfs32 *__buf),(__file,__buf))
#endif /* !__sys_Xstatfs_defined */
#endif /* sys_Xstatfs... */
#if __CRT_HAVE_XSC(statfs64)
#ifndef __sys_Xstatfs64_defined
#define __sys_Xstatfs64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,statfs64,(char const *__file, struct statfs64 *__buf),(__file,__buf))
#else /* ... */
#undef __sys_Xstatfs64_defined
#endif /* !... */
#endif /* !__sys_Xstatfs64_defined */
#endif /* sys_Xstatfs64... */
#if __CRT_HAVE_XSC(stime)
#ifndef __sys_Xstime_defined
#define __sys_Xstime_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,stime,(__time32_t const *__t),(__t))
#else /* ... */
#undef __sys_Xstime_defined
#endif /* !... */
#endif /* !__sys_Xstime_defined */
#endif /* sys_Xstime... */
#if __CRT_HAVE_XSC(stime64)
#ifndef __sys_Xstime64_defined
#define __sys_Xstime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,stime64,(__time64_t const *__t),(__t))
#else /* ... */
#undef __sys_Xstime64_defined
#endif /* !... */
#endif /* !__sys_Xstime64_defined */
#endif /* sys_Xstime64... */
#if __CRT_HAVE_XSC(swapoff)
#ifndef __sys_Xswapoff_defined
#define __sys_Xswapoff_defined 1
__CDECLARE_XSC(,__errno_t,swapoff,(char const *__pathname),(__pathname))
#endif /* !__sys_Xswapoff_defined */
#endif /* sys_Xswapoff... */
#if __CRT_HAVE_XSC(swapon)
#ifndef __sys_Xswapon_defined
#define __sys_Xswapon_defined 1
/* @param: swapflags: Set of `SWAP_FLAG_*' */
__CDECLARE_XSC(,__errno_t,swapon,(char const *__pathname, __syscall_ulong_t __swapflags),(__pathname,__swapflags))
#endif /* !__sys_Xswapon_defined */
#endif /* sys_Xswapon... */
#if __CRT_HAVE_XSC(symlink)
#ifndef __sys_Xsymlink_defined
#define __sys_Xsymlink_defined 1
__CDECLARE_XSC(,__errno_t,symlink,(char const *__link_text, char const *__target_path),(__link_text,__target_path))
#endif /* !__sys_Xsymlink_defined */
#endif /* sys_Xsymlink... */
#if __CRT_HAVE_XSC(symlinkat)
#ifndef __sys_Xsymlinkat_defined
#define __sys_Xsymlinkat_defined 1
__CDECLARE_XSC(,__errno_t,symlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path),(__link_text,__tofd,__target_path))
#endif /* !__sys_Xsymlinkat_defined */
#endif /* sys_Xsymlinkat... */
#if __CRT_HAVE_XSC(sync)
#ifndef __sys_Xsync_defined
#define __sys_Xsync_defined 1
__CDECLARE_XSC(,__errno_t,sync,(void),())
#endif /* !__sys_Xsync_defined */
#endif /* sys_Xsync... */
#if __CRT_HAVE_XSC(sync_file_range)
#ifndef __sys_Xsync_file_range_defined
#define __sys_Xsync_file_range_defined 1
__CDECLARE_XSC(,__errno_t,sync_file_range,(__fd_t __fd, __uint64_t __offset, __uint64_t __count, __syscall_ulong_t __flags),(__fd,__offset,__count,__flags))
#endif /* !__sys_Xsync_file_range_defined */
#endif /* sys_Xsync_file_range... */
#if __CRT_HAVE_XSC(syncfs)
#ifndef __sys_Xsyncfs_defined
#define __sys_Xsyncfs_defined 1
__CDECLARE_XSC(,__errno_t,syncfs,(__fd_t __fd),(__fd))
#endif /* !__sys_Xsyncfs_defined */
#endif /* sys_Xsyncfs... */
#if __CRT_HAVE_XSC(sysctl)
#ifndef __sys_Xsysctl_defined
#define __sys_Xsysctl_defined 1
__CDECLARE_XSC(,__syscall_slong_t,sysctl,(__syscall_ulong_t __command, void *__arg),(__command,__arg))
#endif /* !__sys_Xsysctl_defined */
#endif /* sys_Xsysctl... */
#if __CRT_HAVE_XSC(sysinfo)
#ifndef __sys_Xsysinfo_defined
#define __sys_Xsysinfo_defined 1
__CDECLARE_XSC(,__errno_t,sysinfo,(struct sysinfo *__info),(__info))
#endif /* !__sys_Xsysinfo_defined */
#endif /* sys_Xsysinfo... */
#if __CRT_HAVE_XSC(syslog)
#ifndef __sys_Xsyslog_defined
#define __sys_Xsyslog_defined 1
__CDECLARE_XSC(,__ssize_t,syslog,(__syscall_ulong_t __level, char const *__str, __size_t __len),(__level,__str,__len))
#endif /* !__sys_Xsyslog_defined */
#endif /* sys_Xsyslog... */
#if __CRT_HAVE_XSC(tee)
#ifndef __sys_Xtee_defined
#define __sys_Xtee_defined 1
__CDECLARE_XSC(,__ssize_t,tee,(__fd_t __fdin, __fd_t __fdout, __size_t __length, __syscall_ulong_t __flags),(__fdin,__fdout,__length,__flags))
#endif /* !__sys_Xtee_defined */
#endif /* sys_Xtee... */
#if __CRT_HAVE_XSC(tgkill)
#ifndef __sys_Xtgkill_defined
#define __sys_Xtgkill_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,tgkill,(__pid_t __tgid, __pid_t __tid, __syscall_ulong_t __signo),(__tgid,__tid,__signo))
#endif /* !__sys_Xtgkill_defined */
#endif /* sys_Xtgkill... */
#if __CRT_HAVE_XSC(time)
#ifndef __sys_Xtime_defined
#define __sys_Xtime_defined 1
__CDECLARE_XSC(,__time32_t,time,(__time32_t *__timer),(__timer))
#endif /* !__sys_Xtime_defined */
#endif /* sys_Xtime... */
#if __CRT_HAVE_XSC(time64)
#ifndef __sys_Xtime64_defined
#define __sys_Xtime64_defined 1
__CDECLARE_XSC(,__time64_t,time64,(__time64_t *__timer),(__timer))
#endif /* !__sys_Xtime64_defined */
#endif /* sys_Xtime64... */
#if __CRT_HAVE_XSC(timer_create)
#ifndef __sys_Xtimer_create_defined
#define __sys_Xtimer_create_defined 1
__CDECLARE_XSC(,__errno_t,timer_create,(__clockid_t __clock_id, struct sigevent *__evp, __timer_t *__timerid),(__clock_id,__evp,__timerid))
#endif /* !__sys_Xtimer_create_defined */
#endif /* sys_Xtimer_create... */
#if __CRT_HAVE_XSC(timer_delete)
#ifndef __sys_Xtimer_delete_defined
#define __sys_Xtimer_delete_defined 1
__CDECLARE_XSC(,__errno_t,timer_delete,(__timer_t __timerid),(__timerid))
#endif /* !__sys_Xtimer_delete_defined */
#endif /* sys_Xtimer_delete... */
#if __CRT_HAVE_XSC(timer_getoverrun)
#ifndef __sys_Xtimer_getoverrun_defined
#define __sys_Xtimer_getoverrun_defined 1
__CDECLARE_XSC(,__syscall_slong_t,timer_getoverrun,(__timer_t __timerid),(__timerid))
#endif /* !__sys_Xtimer_getoverrun_defined */
#endif /* sys_Xtimer_getoverrun... */
#if __CRT_HAVE_XSC(timer_gettime)
#ifndef __sys_Xtimer_gettime_defined
#define __sys_Xtimer_gettime_defined 1
__CDECLARE_XSC(,__errno_t,timer_gettime,(__timer_t __timerid, struct __itimerspec32 *__value),(__timerid,__value))
#endif /* !__sys_Xtimer_gettime_defined */
#endif /* sys_Xtimer_gettime... */
#if __CRT_HAVE_XSC(timer_gettime64)
#ifndef __sys_Xtimer_gettime64_defined
#define __sys_Xtimer_gettime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,timer_gettime64,(__timer_t __timerid, struct __itimerspec64 *__value),(__timerid,__value))
#else /* ... */
#undef __sys_Xtimer_gettime64_defined
#endif /* !... */
#endif /* !__sys_Xtimer_gettime64_defined */
#endif /* sys_Xtimer_gettime64... */
#if __CRT_HAVE_XSC(timer_settime)
#ifndef __sys_Xtimer_settime_defined
#define __sys_Xtimer_settime_defined 1
__CDECLARE_XSC(,__errno_t,timer_settime,(__timer_t __timerid, __syscall_ulong_t __flags, struct __itimerspec32 const *__value, struct __itimerspec32 *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* !__sys_Xtimer_settime_defined */
#endif /* sys_Xtimer_settime... */
#if __CRT_HAVE_XSC(timer_settime64)
#ifndef __sys_Xtimer_settime64_defined
#define __sys_Xtimer_settime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,timer_settime64,(__timer_t __timerid, __syscall_ulong_t __flags, struct __itimerspec64 const *__value, struct __itimerspec64 *__ovalue),(__timerid,__flags,__value,__ovalue))
#else /* ... */
#undef __sys_Xtimer_settime64_defined
#endif /* !... */
#endif /* !__sys_Xtimer_settime64_defined */
#endif /* sys_Xtimer_settime64... */
#if __CRT_HAVE_XSC(timerfd_create)
#ifndef __sys_Xtimerfd_create_defined
#define __sys_Xtimerfd_create_defined 1
/* Return file descriptor for new interval timer source */
__CDECLARE_XSC(,__fd_t,timerfd_create,(__clockid_t __clock_id, __syscall_ulong_t __flags),(__clock_id,__flags))
#endif /* !__sys_Xtimerfd_create_defined */
#endif /* sys_Xtimerfd_create... */
#if __CRT_HAVE_XSC(timerfd_gettime)
#ifndef __sys_Xtimerfd_gettime_defined
#define __sys_Xtimerfd_gettime_defined 1
/* Return the next expiration time of UFD */
__CDECLARE_XSC(,__errno_t,timerfd_gettime,(__fd_t __ufd, struct __itimerspec32 *__otmr),(__ufd,__otmr))
#endif /* !__sys_Xtimerfd_gettime_defined */
#endif /* sys_Xtimerfd_gettime... */
#if __CRT_HAVE_XSC(timerfd_gettime64)
#ifndef __sys_Xtimerfd_gettime64_defined
#define __sys_Xtimerfd_gettime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* Return the next expiration time of UFD */
__CDECLARE_XSC(,__errno_t,timerfd_gettime64,(__fd_t __ufd, struct __itimerspec64 *__otmr),(__ufd,__otmr))
#else /* ... */
#undef __sys_Xtimerfd_gettime64_defined
#endif /* !... */
#endif /* !__sys_Xtimerfd_gettime64_defined */
#endif /* sys_Xtimerfd_gettime64... */
#if __CRT_HAVE_XSC(timerfd_settime)
#ifndef __sys_Xtimerfd_settime_defined
#define __sys_Xtimerfd_settime_defined 1
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_XSC(,__errno_t,timerfd_settime,(__fd_t __ufd, __syscall_ulong_t __flags, struct __itimerspec32 const *__utmr, struct __itimerspec32 *__otmr),(__ufd,__flags,__utmr,__otmr))
#endif /* !__sys_Xtimerfd_settime_defined */
#endif /* sys_Xtimerfd_settime... */
#if __CRT_HAVE_XSC(timerfd_settime64)
#ifndef __sys_Xtimerfd_settime64_defined
#define __sys_Xtimerfd_settime64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_XSC(,__errno_t,timerfd_settime64,(__fd_t __ufd, __syscall_ulong_t __flags, struct __itimerspec64 const *__utmr, struct __itimerspec64 *__otmr),(__ufd,__flags,__utmr,__otmr))
#else /* ... */
#undef __sys_Xtimerfd_settime64_defined
#endif /* !... */
#endif /* !__sys_Xtimerfd_settime64_defined */
#endif /* sys_Xtimerfd_settime64... */
#if __CRT_HAVE_XSC(times)
#ifndef __sys_Xtimes_defined
#define __sys_Xtimes_defined 1
__CDECLARE_XSC(,__clock_t,times,(struct tms *__buf),(__buf))
#endif /* !__sys_Xtimes_defined */
#endif /* sys_Xtimes... */
#if __CRT_HAVE_XSC(tkill)
#ifndef __sys_Xtkill_defined
#define __sys_Xtkill_defined 1
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,tkill,(__pid_t __tid, __syscall_ulong_t __signo),(__tid,__signo))
#endif /* !__sys_Xtkill_defined */
#endif /* sys_Xtkill... */
#if __CRT_HAVE_XSC(truncate)
#ifndef __sys_Xtruncate_defined
#define __sys_Xtruncate_defined 1
__CDECLARE_XSC(,__errno_t,truncate,(char const *__filename, __syscall_ulong_t __length),(__filename,__length))
#endif /* !__sys_Xtruncate_defined */
#endif /* sys_Xtruncate... */
#if __CRT_HAVE_XSC(truncate64)
#ifndef __sys_Xtruncate64_defined
#define __sys_Xtruncate64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,truncate64,(char const *__filename, __uint64_t __length),(__filename,__length))
#else /* ... */
#undef __sys_Xtruncate64_defined
#endif /* !... */
#endif /* !__sys_Xtruncate64_defined */
#endif /* sys_Xtruncate64... */
#if __CRT_HAVE_XSC(umask)
#ifndef __sys_Xumask_defined
#define __sys_Xumask_defined 1
__CDECLARE_XSC(,__mode_t,umask,(__mode_t __mode),(__mode))
#endif /* !__sys_Xumask_defined */
#endif /* sys_Xumask... */
#if __CRT_HAVE_XSC(umount)
#ifndef __sys_Xumount_defined
#define __sys_Xumount_defined 1
#if defined(__i386__) && !defined(__x86_64__)
__CDECLARE_XSC(,__errno_t,umount,(char const *__special_file),(__special_file))
#else /* ... */
#undef __sys_Xumount_defined
#endif /* !... */
#endif /* !__sys_Xumount_defined */
#endif /* sys_Xumount... */
#if __CRT_HAVE_XSC(umount2)
#ifndef __sys_Xumount2_defined
#define __sys_Xumount2_defined 1
__CDECLARE_XSC(,__errno_t,umount2,(char const *__special_file, __syscall_ulong_t __flags),(__special_file,__flags))
#endif /* !__sys_Xumount2_defined */
#endif /* sys_Xumount2... */
#if __CRT_HAVE_XSC(uname)
#ifndef __sys_Xuname_defined
#define __sys_Xuname_defined 1
__CDECLARE_XSC(,__errno_t,uname,(struct utsname *__name),(__name))
#endif /* !__sys_Xuname_defined */
#endif /* sys_Xuname... */
#if __CRT_HAVE_XSC(unlink)
#ifndef __sys_Xunlink_defined
#define __sys_Xunlink_defined 1
__CDECLARE_XSC(,__errno_t,unlink,(char const *__filename),(__filename))
#endif /* !__sys_Xunlink_defined */
#endif /* sys_Xunlink... */
#if __CRT_HAVE_XSC(unlinkat)
#ifndef __sys_Xunlinkat_defined
#define __sys_Xunlinkat_defined 1
/* @param: flags: Set of `0|AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,unlinkat,(__fd_t __dirfd, char const *__name, __atflag_t __flags),(__dirfd,__name,__flags))
#endif /* !__sys_Xunlinkat_defined */
#endif /* sys_Xunlinkat... */
#if __CRT_HAVE_XSC(unshare)
#ifndef __sys_Xunshare_defined
#define __sys_Xunshare_defined 1
/* param flags: Set of `CLONE_*' */
__CDECLARE_XSC(,__errno_t,unshare,(__syscall_ulong_t __flags),(__flags))
#endif /* !__sys_Xunshare_defined */
#endif /* sys_Xunshare... */
#if __CRT_HAVE_XSC(ustat)
#ifndef __sys_Xustat_defined
#define __sys_Xustat_defined 1
__CDECLARE_XSC(,__errno_t,ustat,(__dev_t __dev, struct ustat *__ubuf),(__dev,__ubuf))
#endif /* !__sys_Xustat_defined */
#endif /* sys_Xustat... */
#if __CRT_HAVE_XSC(utime)
#ifndef __sys_Xutime_defined
#define __sys_Xutime_defined 1
__CDECLARE_XSC(,__errno_t,utime,(char const *__filename, struct __utimbuf32 const *__times),(__filename,__times))
#endif /* !__sys_Xutime_defined */
#endif /* sys_Xutime... */
#if __CRT_HAVE_XSC(utime64)
#ifndef __sys_Xutime64_defined
#define __sys_Xutime64_defined 1
__CDECLARE_XSC(,__errno_t,utime64,(char const *__filename, struct utimbuf64 const *__times),(__filename,__times))
#endif /* !__sys_Xutime64_defined */
#endif /* sys_Xutime64... */
#if __CRT_HAVE_XSC(utimensat)
#ifndef __sys_Xutimensat_defined
#define __sys_Xutimensat_defined 1
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,utimensat,(__fd_t __dirfd, char const *__filename, /*[2-3]*/ struct __timespec32 const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* !__sys_Xutimensat_defined */
#endif /* sys_Xutimensat... */
#if __CRT_HAVE_XSC(utimensat64)
#ifndef __sys_Xutimensat64_defined
#define __sys_Xutimensat64_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,utimensat64,(__fd_t __dirfd, char const *__filename, /*[2-3]*/ struct __timespec64 const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#else /* ... */
#undef __sys_Xutimensat64_defined
#endif /* !... */
#endif /* !__sys_Xutimensat64_defined */
#endif /* sys_Xutimensat64... */
#if __CRT_HAVE_XSC(utimes)
#ifndef __sys_Xutimes_defined
#define __sys_Xutimes_defined 1
__CDECLARE_XSC(,__errno_t,utimes,(char const *__filename, /*[2]*/ struct __timeval32 const *__times),(__filename,__times))
#endif /* !__sys_Xutimes_defined */
#endif /* sys_Xutimes... */
#if __CRT_HAVE_XSC(utimes64)
#ifndef __sys_Xutimes64_defined
#define __sys_Xutimes64_defined 1
__CDECLARE_XSC(,__errno_t,utimes64,(char const *__filename, /*[2]*/ struct __timeval64 const *__times),(__filename,__times))
#endif /* !__sys_Xutimes64_defined */
#endif /* sys_Xutimes64... */
#if __CRT_HAVE_XSC(vfork)
#ifndef __sys_Xvfork_defined
#define __sys_Xvfork_defined 1
__CDECLARE_XSC(,__pid_t,vfork,(void),())
#endif /* !__sys_Xvfork_defined */
#endif /* sys_Xvfork... */
#if __CRT_HAVE_XSC(vhangup)
#ifndef __sys_Xvhangup_defined
#define __sys_Xvhangup_defined 1
__CDECLARE_XSC(,__errno_t,vhangup,(void),())
#endif /* !__sys_Xvhangup_defined */
#endif /* sys_Xvhangup... */
#if __CRT_HAVE_XSC(vmsplice)
#ifndef __sys_Xvmsplice_defined
#define __sys_Xvmsplice_defined 1
__CDECLARE_XSC(,__ssize_t,vmsplice,(__fd_t __fdout, struct iovec const *__iov, __size_t __count, __syscall_ulong_t __flags),(__fdout,__iov,__count,__flags))
#endif /* !__sys_Xvmsplice_defined */
#endif /* sys_Xvmsplice... */
#if __CRT_HAVE_XSC(wait4)
#ifndef __sys_Xwait4_defined
#define __sys_Xwait4_defined 1
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE_XSC(,__pid_t,wait4,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options, struct rusage *__usage),(__pid,__stat_loc,__options,__usage))
#endif /* !__sys_Xwait4_defined */
#endif /* sys_Xwait4... */
#if __CRT_HAVE_XSC(waitid)
#ifndef __sys_Xwaitid_defined
#define __sys_Xwaitid_defined 1
/* @param: options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
__CDECLARE_XSC(,__errno_t,waitid,(__idtype_t __idtype, __id_t __id, struct __siginfo_struct *__infop, __syscall_ulong_t __options, struct rusage *__ru),(__idtype,__id,__infop,__options,__ru))
#endif /* !__sys_Xwaitid_defined */
#endif /* sys_Xwaitid... */
#if __CRT_HAVE_XSC(waitpid)
#ifndef __sys_Xwaitpid_defined
#define __sys_Xwaitpid_defined 1
#if defined(__i386__) && !defined(__x86_64__)
/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE_XSC(,__pid_t,waitpid,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options),(__pid,__stat_loc,__options))
#else /* ... */
#undef __sys_Xwaitpid_defined
#endif /* !... */
#endif /* !__sys_Xwaitpid_defined */
#endif /* sys_Xwaitpid... */
#if __CRT_HAVE_XSC(write)
#ifndef __sys_Xwrite_defined
#define __sys_Xwrite_defined 1
__CDECLARE_XSC(,__ssize_t,write,(__fd_t __fd, void const *__buf, __size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* !__sys_Xwrite_defined */
#endif /* sys_Xwrite... */
#if __CRT_HAVE_XSC(writef)
#ifndef __sys_Xwritef_defined
#define __sys_Xwritef_defined 1
__CDECLARE_XSC(,__ssize_t,writef,(__fd_t __fd, void const *__buf, __size_t __bufsize, __iomode_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* !__sys_Xwritef_defined */
#endif /* sys_Xwritef... */
#if __CRT_HAVE_XSC(writev)
#ifndef __sys_Xwritev_defined
#define __sys_Xwritev_defined 1
__CDECLARE_XSC(,__ssize_t,writev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* !__sys_Xwritev_defined */
#endif /* sys_Xwritev... */
#if __CRT_HAVE_XSC(writevf)
#ifndef __sys_Xwritevf_defined
#define __sys_Xwritevf_defined 1
__CDECLARE_XSC(,__ssize_t,writevf,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __iomode_t __mode),(__fd,__iovec,__count,__mode))
#endif /* !__sys_Xwritevf_defined */
#endif /* sys_Xwritevf... */



#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("timezone")
#pragma pop_macro("timeb")
#pragma pop_macro("stat")
#pragma pop_macro("dirent")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_SYSCALLS_H */
