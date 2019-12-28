/* HASH CRC-32:0x76a22a34 */
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
#ifndef _KOS_I386_KOS_SYSCALLS32_H
#define _KOS_I386_KOS_SYSCALLS32_H 1

#include <__stdinc.h>
#include <kos/asm/syscall.h>

#include <bits/iovec-struct32.h>
#include <bits/itimerspec32.h>
#include <bits/itimerval.h>
#include <bits/sigaction.h>
#include <bits/siginfo-struct32.h>
#include <bits/statfs.h>
#include <bits/timespec32.h>
#include <bits/timeval32.h>
#include <bits/types.h>
#include <bits/utimebuf.h>
#include <hybrid/__pointer.h>
#include <hybrid/typecore.h>
#include <kos/bits/debugtrap32.h>
#include <kos/bits/except-handler32.h>
#include <kos/bits/exception_data32.h>
#include <kos/bits/futex-expr32.h>
#include <kos/exec/bits/library-listdef32.h>
#include <kos/kernel/cpu-state32.h>
#include <kos/kernel/fpu-state32.h>
#include <librpc/bits/syscall-info32.h>


#ifndef __CDECLARE_SC
#include <__crt.h>
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

#ifdef __CC__
__SYSDECL_BEGIN

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

struct __fd_set_struct;
struct __itimerspecx32;
struct __itimerspecx32_64;
struct __itimerval64;
struct __siginfo32_struct;
struct __sigset_struct;
struct __timespecx32;
struct __timespecx32_64;
struct __timevalx32;
struct __timevalx32_64;
struct __utimbuf32;
struct __utimbuf64;
struct debugtrap_reason32;
struct dirent;
struct exception_data32;
struct fpustate32;
struct iovec32;
struct lfutexexpr32;
struct library_listdef32;
struct linux_oldolduname;
struct linux_oldstat;
struct linux_olduname;
struct linux_stat32;
struct linux_stat64;
struct mmsghdr;
struct old_linux_dirent;
struct pollfd;
struct rpc_syscall_info32;
struct rusage;
struct sigaction;
struct stat;
struct statfs64;
struct termios;
struct timeb;
struct timezone;
struct ucpustate32;
struct winsize;

#if __CRT_HAVE_SC(_llseek)
__CDECLARE_SC(,__errno_t,_llseek,(__fd_t __fd, __int64_t __offset, __uint64_t *__result, __syscall_ulong_t __whence),(__fd,__offset,__result,__whence))
#endif /* __CRT_HAVE_SC(_llseek) */
#if __CRT_HAVE_SC(_newselect)
__CDECLARE_SC(,__errno_t,_newselect,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(_newselect) */
#if __CRT_HAVE_SC(afs_syscall)
__CDECLARE_SC(,__errno_t,afs_syscall,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(afs_syscall) */
#if __CRT_HAVE_SC(bdflush)
__CDECLARE_SC(,__errno_t,bdflush,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(bdflush) */
#if __CRT_HAVE_SC(break)
__CDECLARE_SC(,__errno_t,break,(void),())
#endif /* __CRT_HAVE_SC(break) */
#if __CRT_HAVE_SC(chown)
__CDECLARE_SC(,__errno_t,chown,(char const *__filename, __uint16_t __owner, __uint16_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_SC(chown) */
#if __CRT_HAVE_SC(chown32)
__CDECLARE_SC(,__errno_t,chown32,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_SC(chown32) */
#if __CRT_HAVE_SC(clock_getres)
__CDECLARE_SC(,__errno_t,clock_getres,(__clockid_t __clock_id, struct __timespecx32 *__res),(__clock_id,__res))
#endif /* __CRT_HAVE_SC(clock_getres) */
#if __CRT_HAVE_SC(clock_getres64)
__CDECLARE_SC(,__errno_t,clock_getres64,(__clockid_t __clock_id, struct __timespecx32_64 *__res),(__clock_id,__res))
#endif /* __CRT_HAVE_SC(clock_getres64) */
#if __CRT_HAVE_SC(clock_gettime)
__CDECLARE_SC(,__errno_t,clock_gettime,(__clockid_t __clock_id, struct __timespecx32 *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_SC(clock_gettime) */
#if __CRT_HAVE_SC(clock_gettime64)
__CDECLARE_SC(,__errno_t,clock_gettime64,(__clockid_t __clock_id, struct __timespecx32_64 *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_SC(clock_gettime64) */
#if __CRT_HAVE_SC(clock_nanosleep)
__CDECLARE_SC(,__errno_t,clock_nanosleep,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct __timespecx32 const *__requested_time, struct __timespecx32 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* __CRT_HAVE_SC(clock_nanosleep) */
#if __CRT_HAVE_SC(clock_nanosleep64)
__CDECLARE_SC(,__errno_t,clock_nanosleep64,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct __timespecx32_64 const *__requested_time, struct __timespecx32_64 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* __CRT_HAVE_SC(clock_nanosleep64) */
#if __CRT_HAVE_SC(clock_settime)
__CDECLARE_SC(,__errno_t,clock_settime,(__clockid_t __clock_id, struct __timespecx32 const *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_SC(clock_settime) */
#if __CRT_HAVE_SC(clock_settime64)
__CDECLARE_SC(,__errno_t,clock_settime64,(__clockid_t __clock_id, struct __timespecx32_64 const *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_SC(clock_settime64) */
#if __CRT_HAVE_SC(clone)
__CDECLARE_SC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __uintptr_t __newtls, __pid_t *__ctid),(__flags,__child_stack,__ptid,__newtls,__ctid))
#endif /* __CRT_HAVE_SC(clone) */
#if __CRT_HAVE_SC(coredump)
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
__CDECLARE_SC(,__errno_t,coredump,(struct ucpustate32 const *__curr_state, struct ucpustate32 const *__orig_state, __HYBRID_PTR32(void) const *__traceback_vector, __size_t __traceback_length, struct exception_data32 const *__exception, __syscall_ulong_t __unwind_error),(__curr_state,__orig_state,__traceback_vector,__traceback_length,__exception,__unwind_error))
#endif /* __CRT_HAVE_SC(coredump) */
#if __CRT_HAVE_SC(create_module)
__CDECLARE_SC(,__errno_t,create_module,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(create_module) */
#if __CRT_HAVE_SC(debugtrap)
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
__CDECLARE_SC(,__errno_t,debugtrap,(struct ucpustate32 const *__state, struct debugtrap_reason32 const *__reason),(__state,__reason))
#endif /* __CRT_HAVE_SC(debugtrap) */
#if __CRT_HAVE_SC(detach)
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
#endif /* __CRT_HAVE_SC(detach) */
#if __CRT_HAVE_SC(fadvise64_64)
__CDECLARE_SC(,__errno_t,fadvise64_64,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(fadvise64_64) */
#if __CRT_HAVE_SC(fallocate64)
__CDECLARE_SC(,__errno_t,fallocate64,(__fd_t __fd, __syscall_ulong_t __mode, __uint64_t __offset, __uint64_t __length),(__fd,__mode,__offset,__length))
#endif /* __CRT_HAVE_SC(fallocate64) */
#if __CRT_HAVE_SC(fchdirat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fchdirat,(__fd_t __dirfd, char const *__path, __atflag_t __flags),(__dirfd,__path,__flags))
#endif /* __CRT_HAVE_SC(fchdirat) */
#if __CRT_HAVE_SC(fchown)
__CDECLARE_SC(,__errno_t,fchown,(__fd_t __fd, __uint16_t __owner, __uint16_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_SC(fchown) */
#if __CRT_HAVE_SC(fchown32)
__CDECLARE_SC(,__errno_t,fchown32,(__fd_t __fd, __uint32_t __owner, __uint32_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_SC(fchown32) */
#if __CRT_HAVE_SC(fcntl64)
__CDECLARE_SC(,__syscall_slong_t,fcntl64,(__fd_t __fd, __syscall_ulong_t __command, void *__arg),(__fd,__command,__arg))
#endif /* __CRT_HAVE_SC(fcntl64) */
#if __CRT_HAVE_SC(fmkdirat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fmkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode, __atflag_t __flags),(__dirfd,__pathname,__mode,__flags))
#endif /* __CRT_HAVE_SC(fmkdirat) */
#if __CRT_HAVE_SC(fmknodat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fmknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),(__dirfd,__nodename,__mode,__dev,__flags))
#endif /* __CRT_HAVE_SC(fmknodat) */
#if __CRT_HAVE_SC(freadlinkat)
/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
__CDECLARE_SC(,__ssize_t,freadlinkat,(__fd_t __dirfd, char const *__path, char *__buf, __size_t __buflen, __atflag_t __flags),(__dirfd,__path,__buf,__buflen,__flags))
#endif /* __CRT_HAVE_SC(freadlinkat) */
#if __CRT_HAVE_SC(frealpath4)
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
__CDECLARE_SC(,__ssize_t,frealpath4,(__fd_t __fd, char *__buf, __size_t __buflen, __atflag_t __flags),(__fd,__buf,__buflen,__flags))
#endif /* __CRT_HAVE_SC(frealpath4) */
#if __CRT_HAVE_SC(frealpathat)
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
__CDECLARE_SC(,__ssize_t,frealpathat,(__fd_t __dirfd, char const *__filename, char *__buf, __size_t __buflen, __atflag_t __flags),(__dirfd,__filename,__buf,__buflen,__flags))
#endif /* __CRT_HAVE_SC(frealpathat) */
#if __CRT_HAVE_SC(frenameat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,frenameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path, __atflag_t __flags),(__oldfd,__oldname,__newfd,__newname_or_path,__flags))
#endif /* __CRT_HAVE_SC(frenameat) */
#if __CRT_HAVE_SC(fsmode)
__CDECLARE_SC(,__uint64_t,fsmode,(__uint64_t __mode),(__mode))
#endif /* __CRT_HAVE_SC(fsmode) */
#if __CRT_HAVE_SC(fstatfs64)
__CDECLARE_SC(,__errno_t,fstatfs64,(__fd_t __file, struct statfs64 *__buf),(__file,__buf))
#endif /* __CRT_HAVE_SC(fstatfs64) */
#if __CRT_HAVE_SC(fsymlinkat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fsymlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__link_text,__tofd,__target_path,__flags))
#endif /* __CRT_HAVE_SC(fsymlinkat) */
#if __CRT_HAVE_SC(ftime)
__CDECLARE_SC(,__errno_t,ftime,(struct timeb *__tp),(__tp))
#endif /* __CRT_HAVE_SC(ftime) */
#if __CRT_HAVE_SC(ftruncate64)
__CDECLARE_SC(,__errno_t,ftruncate64,(__fd_t __fd, __uint64_t __length),(__fd,__length))
#endif /* __CRT_HAVE_SC(ftruncate64) */
#if __CRT_HAVE_SC(futex)
__CDECLARE_SC(,__syscall_slong_t,futex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct __timespecx32 const *__timeout_or_val2, __uint32_t *__uaddr2, __uint32_t __val3),(__uaddr,__futex_op,__val,__timeout_or_val2,__uaddr2,__val3))
#endif /* __CRT_HAVE_SC(futex) */
#if __CRT_HAVE_SC(futimesat)
__CDECLARE_SC(,__errno_t,futimesat,(__fd_t __dirfd, __const char *__filename, struct __timevalx32 const *__times),(__dirfd,__filename,__times))
#endif /* __CRT_HAVE_SC(futimesat) */
#if __CRT_HAVE_SC(futimesat64)
__CDECLARE_SC(,__errno_t,futimesat64,(__fd_t __dirfd, __const char *__filename, struct __timevalx32_64 const *__times),(__dirfd,__filename,__times))
#endif /* __CRT_HAVE_SC(futimesat64) */
#if __CRT_HAVE_SC(get_exception_handler)
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
__CDECLARE_SC(,__errno_t,get_exception_handler,(__ULONG32_TYPE__ *__pmode, __except_handler32_t *__phandler, __HYBRID_PTR32(void) *__phandler_sp),(__pmode,__phandler,__phandler_sp))
#endif /* __CRT_HAVE_SC(get_exception_handler) */
#if __CRT_HAVE_SC(get_kernel_syms)
__CDECLARE_SC(,__errno_t,get_kernel_syms,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(get_kernel_syms) */
#if __CRT_HAVE_SC(get_thread_area)
__CDECLARE_SC(,__errno_t,get_thread_area,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(get_thread_area) */
#if __CRT_HAVE_SC(getdrives)
/* Returns a bitset of all of the currently mounted dos-drives */
__CDECLARE_SC(,__syscall_slong_t,getdrives,(void),())
#endif /* __CRT_HAVE_SC(getdrives) */
#if __CRT_HAVE_SC(getegid)
__CDECLARE_SC(,__uint16_t,getegid,(void),())
#endif /* __CRT_HAVE_SC(getegid) */
#if __CRT_HAVE_SC(getegid32)
__CDECLARE_SC(,__uint32_t,getegid32,(void),())
#endif /* __CRT_HAVE_SC(getegid32) */
#if __CRT_HAVE_SC(geteuid)
__CDECLARE_SC(,__uint16_t,geteuid,(void),())
#endif /* __CRT_HAVE_SC(geteuid) */
#if __CRT_HAVE_SC(geteuid32)
__CDECLARE_SC(,__uint32_t,geteuid32,(void),())
#endif /* __CRT_HAVE_SC(geteuid32) */
#if __CRT_HAVE_SC(getgid)
__CDECLARE_SC(,__uint16_t,getgid,(void),())
#endif /* __CRT_HAVE_SC(getgid) */
#if __CRT_HAVE_SC(getgid32)
__CDECLARE_SC(,__uint32_t,getgid32,(void),())
#endif /* __CRT_HAVE_SC(getgid32) */
#if __CRT_HAVE_SC(getgroups)
__CDECLARE_SC(,__errno_t,getgroups,(__size_t __size, __uint16_t *__list),(__size,__list))
#endif /* __CRT_HAVE_SC(getgroups) */
#if __CRT_HAVE_SC(getgroups32)
__CDECLARE_SC(,__errno_t,getgroups32,(__size_t __size, __uint32_t *__list),(__size,__list))
#endif /* __CRT_HAVE_SC(getgroups32) */
#if __CRT_HAVE_SC(getitimer64)
__CDECLARE_SC(,__errno_t,getitimer64,(__syscall_ulong_t __which, struct __itimerval64 *__curr_value),(__which,__curr_value))
#endif /* __CRT_HAVE_SC(getitimer64) */
#if __CRT_HAVE_SC(getpmsg)
__CDECLARE_SC(,__errno_t,getpmsg,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(getpmsg) */
#if __CRT_HAVE_SC(getresgid)
__CDECLARE_SC(,__errno_t,getresgid,(__uint16_t *__rgid, __uint16_t *__egid, __uint16_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_SC(getresgid) */
#if __CRT_HAVE_SC(getresgid32)
__CDECLARE_SC(,__errno_t,getresgid32,(__uint32_t *__rgid, __uint32_t *__egid, __uint32_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_SC(getresgid32) */
#if __CRT_HAVE_SC(getresuid)
__CDECLARE_SC(,__errno_t,getresuid,(__uint16_t *__ruid, __uint16_t *__euid, __uint16_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_SC(getresuid) */
#if __CRT_HAVE_SC(getresuid32)
__CDECLARE_SC(,__errno_t,getresuid32,(__uint32_t *__ruid, __uint32_t *__euid, __uint32_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_SC(getresuid32) */
#if __CRT_HAVE_SC(gettimeofday)
__CDECLARE_SC(,__errno_t,gettimeofday,(struct __timevalx32 *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_SC(gettimeofday) */
#if __CRT_HAVE_SC(gettimeofday64)
__CDECLARE_SC(,__errno_t,gettimeofday64,(struct __timevalx32_64 *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_SC(gettimeofday64) */
#if __CRT_HAVE_SC(getuid)
__CDECLARE_SC(,__uint16_t,getuid,(void),())
#endif /* __CRT_HAVE_SC(getuid) */
#if __CRT_HAVE_SC(getuid32)
__CDECLARE_SC(,__uint32_t,getuid32,(void),())
#endif /* __CRT_HAVE_SC(getuid32) */
#if __CRT_HAVE_SC(gtty)
__CDECLARE_SC(,__errno_t,gtty,(void),())
#endif /* __CRT_HAVE_SC(gtty) */
#if __CRT_HAVE_SC(hop)
__CDECLARE_SC(,__syscall_slong_t,hop,(__fd_t __fd, __syscall_ulong_t __command, void *__arg),(__fd,__command,__arg))
#endif /* __CRT_HAVE_SC(hop) */
#if __CRT_HAVE_SC(hopf)
__CDECLARE_SC(,__syscall_slong_t,hopf,(__fd_t __fd, __syscall_ulong_t __command, __iomode_t __mode, void *__arg),(__fd,__command,__mode,__arg))
#endif /* __CRT_HAVE_SC(hopf) */
#if __CRT_HAVE_SC(idle)
__CDECLARE_SC(,__errno_t,idle,(void),())
#endif /* __CRT_HAVE_SC(idle) */
#if __CRT_HAVE_SC(ioctlf)
__CDECLARE_SC(,__syscall_slong_t,ioctlf,(__fd_t __fd, __syscall_ulong_t __command, __iomode_t __mode, void *__arg),(__fd,__command,__mode,__arg))
#endif /* __CRT_HAVE_SC(ioctlf) */
#if __CRT_HAVE_SC(ioperm)
__CDECLARE_SC(,__errno_t,ioperm,(__syscall_ulong_t __from, __syscall_ulong_t __num, __syscall_ulong_t __turn_on),(__from,__num,__turn_on))
#endif /* __CRT_HAVE_SC(ioperm) */
#if __CRT_HAVE_SC(iopl)
__CDECLARE_SC(,__errno_t,iopl,(__syscall_ulong_t __level),(__level))
#endif /* __CRT_HAVE_SC(iopl) */
#if __CRT_HAVE_SC(ipc)
__CDECLARE_SC(,__errno_t,ipc,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(ipc) */
#if __CRT_HAVE_SC(kfstat)
__CDECLARE_SC(,__errno_t,kfstat,(__fd_t __fd, struct stat *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_SC(kfstat) */
#if __CRT_HAVE_SC(kfstatat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,kfstatat,(__fd_t __dirfd, char const *__filename, struct stat *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* __CRT_HAVE_SC(kfstatat) */
#if __CRT_HAVE_SC(klstat)
__CDECLARE_SC(,__errno_t,klstat,(char const *__filename, struct stat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(klstat) */
#if __CRT_HAVE_SC(kreaddir)
__CDECLARE_SC(,__ssize_t,kreaddir,(__fd_t __fd, struct dirent *__buf, __size_t __bufsize, __syscall_ulong_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* __CRT_HAVE_SC(kreaddir) */
#if __CRT_HAVE_SC(kreaddirf)
__CDECLARE_SC(,__ssize_t,kreaddirf,(__fd_t __fd, struct dirent *__buf, __size_t __bufsize, __syscall_ulong_t __mode, __iomode_t __iomode),(__fd,__buf,__bufsize,__mode,__iomode))
#endif /* __CRT_HAVE_SC(kreaddirf) */
#if __CRT_HAVE_SC(kstat)
__CDECLARE_SC(,__errno_t,kstat,(char const *__filename, struct stat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(kstat) */
#if __CRT_HAVE_SC(ksysctl)
__CDECLARE_SC(,__syscall_slong_t,ksysctl,(__syscall_ulong_t __command, void *__arg),(__command,__arg))
#endif /* __CRT_HAVE_SC(ksysctl) */
#if __CRT_HAVE_SC(lchown)
__CDECLARE_SC(,__errno_t,lchown,(char const *__filename, __uint16_t __owner, __uint16_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_SC(lchown) */
#if __CRT_HAVE_SC(lchown32)
__CDECLARE_SC(,__errno_t,lchown32,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_SC(lchown32) */
#if __CRT_HAVE_SC(lfutex)
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
__CDECLARE_SC(,__syscall_slong_t,lfutex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct __timespecx32_64 const *__timeout, __uint32_t __val2),(__uaddr,__futex_op,__val,__timeout,__val2))
#endif /* __CRT_HAVE_SC(lfutex) */
#if __CRT_HAVE_SC(lfutexexpr)
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
__CDECLARE_SC(,__errno_t,lfutexexpr,(void *__base, __size_t __exprc, struct lfutexexpr32 const *__exprv, struct __timespecx32_64 const *__timeout, __syscall_ulong_t __timeout_flags),(__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* __CRT_HAVE_SC(lfutexexpr) */
#if __CRT_HAVE_SC(lfutexlockexpr)
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
__CDECLARE_SC(,__errno_t,lfutexlockexpr,(__uint32_t *__ulockaddr, void *__base, __size_t __exprc, struct lfutexexpr32 const *__exprv, struct __timespecx32_64 const *__timeout, __syscall_ulong_t __timeout_flags),(__ulockaddr,__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* __CRT_HAVE_SC(lfutexlockexpr) */
#if __CRT_HAVE_SC(linux_fstat32)
__CDECLARE_SC(,__errno_t,linux_fstat32,(__fd_t __fd, struct linux_stat32 *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_SC(linux_fstat32) */
#if __CRT_HAVE_SC(linux_fstat64)
__CDECLARE_SC(,__errno_t,linux_fstat64,(__fd_t __fd, struct linux_stat64 *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_SC(linux_fstat64) */
#if __CRT_HAVE_SC(linux_fstatat64)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,linux_fstatat64,(__fd_t __dirfd, char const *__filename, struct linux_stat64 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* __CRT_HAVE_SC(linux_fstatat64) */
#if __CRT_HAVE_SC(linux_lstat32)
__CDECLARE_SC(,__errno_t,linux_lstat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(linux_lstat32) */
#if __CRT_HAVE_SC(linux_lstat64)
__CDECLARE_SC(,__errno_t,linux_lstat64,(char const *__filename, struct linux_stat64 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(linux_lstat64) */
#if __CRT_HAVE_SC(linux_oldfstat)
__CDECLARE_SC(,__errno_t,linux_oldfstat,(__fd_t __fd, struct linux_oldstat *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_SC(linux_oldfstat) */
#if __CRT_HAVE_SC(linux_oldlstat)
__CDECLARE_SC(,__errno_t,linux_oldlstat,(char const *__filename, struct linux_oldstat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(linux_oldlstat) */
#if __CRT_HAVE_SC(linux_oldstat)
__CDECLARE_SC(,__errno_t,linux_oldstat,(char const *__filename, struct linux_oldstat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(linux_oldstat) */
#if __CRT_HAVE_SC(linux_stat32)
__CDECLARE_SC(,__errno_t,linux_stat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(linux_stat32) */
#if __CRT_HAVE_SC(linux_stat64)
__CDECLARE_SC(,__errno_t,linux_stat64,(char const *__filename, struct linux_stat64 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(linux_stat64) */
#if __CRT_HAVE_SC(lock)
__CDECLARE_SC(,__errno_t,lock,(void),())
#endif /* __CRT_HAVE_SC(lock) */
#if __CRT_HAVE_SC(lseek)
__CDECLARE_SC(,__syscall_slong_t,lseek,(__fd_t __fd, __syscall_slong_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* __CRT_HAVE_SC(lseek) */
#if __CRT_HAVE_SC(lseek64)
__CDECLARE_SC(,__int64_t,lseek64,(__fd_t __fd, __int64_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* __CRT_HAVE_SC(lseek64) */
#if __CRT_HAVE_SC(maplibrary)
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
#endif /* __CRT_HAVE_SC(maplibrary) */
#if __CRT_HAVE_SC(mktty)
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
__CDECLARE_SC(,__fd_t,mktty,(__fd_t __keyboard, __fd_t __display, char const *__name, __syscall_ulong_t __rsvd),(__keyboard,__display,__name,__rsvd))
#endif /* __CRT_HAVE_SC(mktty) */
#if __CRT_HAVE_SC(mmap)
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
__CDECLARE_SC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* __CRT_HAVE_SC(mmap) */
#if __CRT_HAVE_SC(mmap2)
__CDECLARE_SC(,void *,mmap2,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __pgoffset),(__addr,__len,__prot,__flags,__fd,__pgoffset))
#endif /* __CRT_HAVE_SC(mmap2) */
#if __CRT_HAVE_SC(modify_ldt)
__CDECLARE_SC(,__syscall_slong_t,modify_ldt,(__syscall_ulong_t __func, void *__ptr, __syscall_ulong_t __bytecount),(__func,__ptr,__bytecount))
#endif /* __CRT_HAVE_SC(modify_ldt) */
#if __CRT_HAVE_SC(mpx)
__CDECLARE_SC(,__errno_t,mpx,(void),())
#endif /* __CRT_HAVE_SC(mpx) */
#if __CRT_HAVE_SC(mq_timedreceive)
__CDECLARE_SC(,__ssize_t,mq_timedreceive,(__fd_t __mqdes, char *__msg_ptr, __size_t __msg_len, __uint32_t *__pmsg_prio, struct __timespecx32 const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#endif /* __CRT_HAVE_SC(mq_timedreceive) */
#if __CRT_HAVE_SC(mq_timedreceive64)
__CDECLARE_SC(,__ssize_t,mq_timedreceive64,(__fd_t __mqdes, char *__msg_ptr, __size_t __msg_len, __uint32_t *__pmsg_prio, struct __timespecx32_64 const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#endif /* __CRT_HAVE_SC(mq_timedreceive64) */
#if __CRT_HAVE_SC(mq_timedsend)
__CDECLARE_SC(,__errno_t,mq_timedsend,(__fd_t __mqdes, char const *__msg_ptr, __size_t __msg_len, __uint32_t __msg_prio, struct __timespecx32 const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#endif /* __CRT_HAVE_SC(mq_timedsend) */
#if __CRT_HAVE_SC(mq_timedsend64)
__CDECLARE_SC(,__errno_t,mq_timedsend64,(__fd_t __mqdes, char const *__msg_ptr, __size_t __msg_len, __uint32_t __msg_prio, struct __timespecx32_64 const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#endif /* __CRT_HAVE_SC(mq_timedsend64) */
#if __CRT_HAVE_SC(nanosleep)
__CDECLARE_SC(,__errno_t,nanosleep,(struct __timespecx32 const *__req, struct __timespecx32 *__rem),(__req,__rem))
#endif /* __CRT_HAVE_SC(nanosleep) */
#if __CRT_HAVE_SC(nanosleep64)
__CDECLARE_SC(,__errno_t,nanosleep64,(struct __timespecx32_64 const *__req, struct __timespecx32_64 *__rem),(__req,__rem))
#endif /* __CRT_HAVE_SC(nanosleep64) */
#if __CRT_HAVE_SC(nice)
__CDECLARE_SC(,__errno_t,nice,(__syscall_slong_t __inc),(__inc))
#endif /* __CRT_HAVE_SC(nice) */
#if __CRT_HAVE_SC(oldolduname)
__CDECLARE_SC(,__errno_t,oldolduname,(struct linux_oldolduname *__name),(__name))
#endif /* __CRT_HAVE_SC(oldolduname) */
#if __CRT_HAVE_SC(olduname)
__CDECLARE_SC(,__errno_t,olduname,(struct linux_olduname *__name),(__name))
#endif /* __CRT_HAVE_SC(olduname) */
#if __CRT_HAVE_SC(openpty)
/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
__CDECLARE_SC(,__errno_t,openpty,(__fd_t *__amaster, __fd_t *__aslave, char *__name, struct termios const *__termp, struct winsize const *__winp),(__amaster,__aslave,__name,__termp,__winp))
#endif /* __CRT_HAVE_SC(openpty) */
#if __CRT_HAVE_SC(ppoll)
__CDECLARE_SC(,__ssize_t,ppoll,(struct pollfd *__fds, __size_t __nfds, struct __timespecx32 const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* __CRT_HAVE_SC(ppoll) */
#if __CRT_HAVE_SC(ppoll64)
__CDECLARE_SC(,__ssize_t,ppoll64,(struct pollfd *__fds, __size_t __nfds, struct __timespecx32_64 const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* __CRT_HAVE_SC(ppoll64) */
#if __CRT_HAVE_SC(pread64f)
__CDECLARE_SC(,__ssize_t,pread64f,(__fd_t __fd, void *__buf, __size_t __bufsize, __uint64_t __offset, __iomode_t __mode),(__fd,__buf,__bufsize,__offset,__mode))
#endif /* __CRT_HAVE_SC(pread64f) */
#if __CRT_HAVE_SC(preadv)
__CDECLARE_SC(,__ssize_t,preadv,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_SC(preadv) */
#if __CRT_HAVE_SC(preadvf)
__CDECLARE_SC(,__ssize_t,preadvf,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __uint64_t __offset, __iomode_t __mode),(__fd,__iovec,__count,__offset,__mode))
#endif /* __CRT_HAVE_SC(preadvf) */
#if __CRT_HAVE_SC(process_vm_readv)
__CDECLARE_SC(,__ssize_t,process_vm_readv,(__pid_t __pid, struct iovec32 const *__lvec, __size_t __liovcnt, struct iovec32 const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* __CRT_HAVE_SC(process_vm_readv) */
#if __CRT_HAVE_SC(process_vm_writev)
__CDECLARE_SC(,__ssize_t,process_vm_writev,(__pid_t __pid, struct iovec32 const *__lvec, __size_t __liovcnt, struct iovec32 const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* __CRT_HAVE_SC(process_vm_writev) */
#if __CRT_HAVE_SC(prof)
__CDECLARE_SC(,__errno_t,prof,(void),())
#endif /* __CRT_HAVE_SC(prof) */
#if __CRT_HAVE_SC(profil)
__CDECLARE_SC(,__errno_t,profil,(__uint16_t *__sample_buffer, __size_t __size, __size_t __offset, __syscall_ulong_t __scale),(__sample_buffer,__size,__offset,__scale))
#endif /* __CRT_HAVE_SC(profil) */
#if __CRT_HAVE_SC(pselect6)
__CDECLARE_SC(,__ssize_t,pselect6,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timespecx32 const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#endif /* __CRT_HAVE_SC(pselect6) */
#if __CRT_HAVE_SC(pselect6_64)
__CDECLARE_SC(,__ssize_t,pselect6_64,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timespecx32_64 const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#endif /* __CRT_HAVE_SC(pselect6_64) */
#if __CRT_HAVE_SC(putpmsg)
__CDECLARE_SC(,__errno_t,putpmsg,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(putpmsg) */
#if __CRT_HAVE_SC(pwrite64f)
__CDECLARE_SC(,__ssize_t,pwrite64f,(__fd_t __fd, void const *__buf, __size_t __bufsize, __uint64_t __offset, __iomode_t __mode),(__fd,__buf,__bufsize,__offset,__mode))
#endif /* __CRT_HAVE_SC(pwrite64f) */
#if __CRT_HAVE_SC(pwritev)
__CDECLARE_SC(,__ssize_t,pwritev,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_SC(pwritev) */
#if __CRT_HAVE_SC(pwritevf)
__CDECLARE_SC(,__ssize_t,pwritevf,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __uint64_t __offset, __iomode_t __mode),(__fd,__iovec,__count,__offset,__mode))
#endif /* __CRT_HAVE_SC(pwritevf) */
#if __CRT_HAVE_SC(query_module)
__CDECLARE_SC(,__errno_t,query_module,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(query_module) */
#if __CRT_HAVE_SC(raiseat)
/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
__CDECLARE_SC(,__errno_t,raiseat,(struct ucpustate32 const *__state, struct __siginfo32_struct const *__si),(__state,__si))
#endif /* __CRT_HAVE_SC(raiseat) */
#if __CRT_HAVE_SC(readdir)
/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
__CDECLARE_SC(,__errno_t,readdir,(__fd_t __fd, struct old_linux_dirent *__dirp, __size_t __count),(__fd,__dirp,__count))
#endif /* __CRT_HAVE_SC(readdir) */
#if __CRT_HAVE_SC(readf)
__CDECLARE_SC(,__ssize_t,readf,(__fd_t __fd, void *__buf, __size_t __bufsize, __iomode_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* __CRT_HAVE_SC(readf) */
#if __CRT_HAVE_SC(readv)
__CDECLARE_SC(,__ssize_t,readv,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_SC(readv) */
#if __CRT_HAVE_SC(readvf)
__CDECLARE_SC(,__ssize_t,readvf,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __iomode_t __mode),(__fd,__iovec,__count,__mode))
#endif /* __CRT_HAVE_SC(readvf) */
#if __CRT_HAVE_SC(recvmmsg)
__CDECLARE_SC(,__ssize_t,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct __timespecx32 *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#endif /* __CRT_HAVE_SC(recvmmsg) */
#if __CRT_HAVE_SC(recvmmsg64)
__CDECLARE_SC(,__ssize_t,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct __timespecx32_64 *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#endif /* __CRT_HAVE_SC(recvmmsg64) */
#if __CRT_HAVE_SC(rpc_schedule)
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
__CDECLARE_SC(,__syscall_slong_t,rpc_schedule,(__pid_t __target, __syscall_ulong_t __flags, __uint8_t const *__program, __HYBRID_PTR32(void) *__arguments),(__target,__flags,__program,__arguments))
#endif /* __CRT_HAVE_SC(rpc_schedule) */
#if __CRT_HAVE_SC(rpc_service)
__CDECLARE_SC(,__syscall_slong_t,rpc_service,(void),())
#endif /* __CRT_HAVE_SC(rpc_service) */
#if __CRT_HAVE_SC(rt_sigqueueinfo)
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,rt_sigqueueinfo,(__pid_t __tgid, __syscall_ulong_t __signo, struct __siginfo32_struct const *__uinfo),(__tgid,__signo,__uinfo))
#endif /* __CRT_HAVE_SC(rt_sigqueueinfo) */
#if __CRT_HAVE_SC(rt_sigtimedwait)
__CDECLARE_SC(,__syscall_slong_t,rt_sigtimedwait,(struct __sigset_struct const *__set, struct __siginfo32_struct *__info, struct __timespecx32 const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* __CRT_HAVE_SC(rt_sigtimedwait) */
#if __CRT_HAVE_SC(rt_sigtimedwait64)
__CDECLARE_SC(,__syscall_slong_t,rt_sigtimedwait64,(struct __sigset_struct const *__set, struct __siginfo32_struct *__info, struct __timespecx32_64 const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* __CRT_HAVE_SC(rt_sigtimedwait64) */
#if __CRT_HAVE_SC(rt_tgsigqueueinfo)
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,rt_tgsigqueueinfo,(__pid_t __tgid, __pid_t __tid, __syscall_ulong_t __signo, struct __siginfo32_struct const *__uinfo),(__tgid,__tid,__signo,__uinfo))
#endif /* __CRT_HAVE_SC(rt_tgsigqueueinfo) */
#if __CRT_HAVE_SC(sched_rr_get_interval)
__CDECLARE_SC(,__errno_t,sched_rr_get_interval,(__pid_t __pid, struct __timespecx32 *__tms),(__pid,__tms))
#endif /* __CRT_HAVE_SC(sched_rr_get_interval) */
#if __CRT_HAVE_SC(sched_rr_get_interval64)
__CDECLARE_SC(,__errno_t,sched_rr_get_interval64,(__pid_t __pid, struct __timespecx32_64 *__tms),(__pid,__tms))
#endif /* __CRT_HAVE_SC(sched_rr_get_interval64) */
#if __CRT_HAVE_SC(select)
__CDECLARE_SC(,__ssize_t,select,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timevalx32 *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* __CRT_HAVE_SC(select) */
#if __CRT_HAVE_SC(select64)
__CDECLARE_SC(,__ssize_t,select64,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timevalx32_64 *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* __CRT_HAVE_SC(select64) */
#if __CRT_HAVE_SC(sendfile64)
__CDECLARE_SC(,__ssize_t,sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __uint64_t *__offset, __size_t __count),(__out_fd,__in_fd,__offset,__count))
#endif /* __CRT_HAVE_SC(sendfile64) */
#if __CRT_HAVE_SC(set_exception_handler)
/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
__CDECLARE_SC(,__errno_t,set_exception_handler,(__syscall_ulong_t __mode, __except_handler32_t __handler, void *__handler_sp),(__mode,__handler,__handler_sp))
#endif /* __CRT_HAVE_SC(set_exception_handler) */
#if __CRT_HAVE_SC(set_library_listdef)
/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
__CDECLARE_SC(,__errno_t,set_library_listdef,(struct library_listdef32 const *__listdef),(__listdef))
#endif /* __CRT_HAVE_SC(set_library_listdef) */
#if __CRT_HAVE_SC(set_thread_area)
__CDECLARE_SC(,__errno_t,set_thread_area,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(set_thread_area) */
#if __CRT_HAVE_SC(setfsgid)
__CDECLARE_SC(,__errno_t,setfsgid,(__uint16_t __gid),(__gid))
#endif /* __CRT_HAVE_SC(setfsgid) */
#if __CRT_HAVE_SC(setfsgid32)
__CDECLARE_SC(,__errno_t,setfsgid32,(__uint32_t __gid),(__gid))
#endif /* __CRT_HAVE_SC(setfsgid32) */
#if __CRT_HAVE_SC(setfsuid)
__CDECLARE_SC(,__errno_t,setfsuid,(__uint16_t __uid),(__uid))
#endif /* __CRT_HAVE_SC(setfsuid) */
#if __CRT_HAVE_SC(setfsuid32)
__CDECLARE_SC(,__errno_t,setfsuid32,(__uint32_t __uid),(__uid))
#endif /* __CRT_HAVE_SC(setfsuid32) */
#if __CRT_HAVE_SC(setgid)
__CDECLARE_SC(,__errno_t,setgid,(__uint16_t __gid),(__gid))
#endif /* __CRT_HAVE_SC(setgid) */
#if __CRT_HAVE_SC(setgid32)
__CDECLARE_SC(,__errno_t,setgid32,(__uint32_t __gid),(__gid))
#endif /* __CRT_HAVE_SC(setgid32) */
#if __CRT_HAVE_SC(setgroups)
__CDECLARE_SC(,__errno_t,setgroups,(__size_t __count, __uint16_t const *__groups),(__count,__groups))
#endif /* __CRT_HAVE_SC(setgroups) */
#if __CRT_HAVE_SC(setgroups32)
__CDECLARE_SC(,__errno_t,setgroups32,(__size_t __count, __uint32_t const *__groups),(__count,__groups))
#endif /* __CRT_HAVE_SC(setgroups32) */
#if __CRT_HAVE_SC(setitimer64)
__CDECLARE_SC(,__errno_t,setitimer64,(__syscall_ulong_t __which, struct __itimerval64 const *__newval, struct __itimerval64 *__oldval),(__which,__newval,__oldval))
#endif /* __CRT_HAVE_SC(setitimer64) */
#if __CRT_HAVE_SC(setregid)
__CDECLARE_SC(,__errno_t,setregid,(__uint16_t __rgid, __uint16_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_SC(setregid) */
#if __CRT_HAVE_SC(setregid32)
__CDECLARE_SC(,__errno_t,setregid32,(__uint32_t __rgid, __uint32_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_SC(setregid32) */
#if __CRT_HAVE_SC(setresgid)
__CDECLARE_SC(,__errno_t,setresgid,(__uint16_t __rgid, __uint16_t __egid, __uint16_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_SC(setresgid) */
#if __CRT_HAVE_SC(setresgid32)
__CDECLARE_SC(,__errno_t,setresgid32,(__uint32_t __rgid, __uint32_t __egid, __uint32_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_SC(setresgid32) */
#if __CRT_HAVE_SC(setresuid)
__CDECLARE_SC(,__errno_t,setresuid,(__uint16_t __ruid, __uint16_t __euid, __uint16_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_SC(setresuid) */
#if __CRT_HAVE_SC(setresuid32)
__CDECLARE_SC(,__errno_t,setresuid32,(__uint32_t __ruid, __uint32_t __euid, __uint32_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_SC(setresuid32) */
#if __CRT_HAVE_SC(setreuid)
__CDECLARE_SC(,__errno_t,setreuid,(__uint16_t __ruid, __uint16_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_SC(setreuid) */
#if __CRT_HAVE_SC(setreuid32)
__CDECLARE_SC(,__errno_t,setreuid32,(__uint32_t __ruid, __uint32_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_SC(setreuid32) */
#if __CRT_HAVE_SC(settimeofday)
__CDECLARE_SC(,__errno_t,settimeofday,(struct __timevalx32 const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_SC(settimeofday) */
#if __CRT_HAVE_SC(settimeofday64)
__CDECLARE_SC(,__errno_t,settimeofday64,(struct __timevalx32_64 const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_SC(settimeofday64) */
#if __CRT_HAVE_SC(setuid)
__CDECLARE_SC(,__errno_t,setuid,(__uint16_t __uid),(__uid))
#endif /* __CRT_HAVE_SC(setuid) */
#if __CRT_HAVE_SC(setuid32)
__CDECLARE_SC(,__errno_t,setuid32,(__uint32_t __uid),(__uid))
#endif /* __CRT_HAVE_SC(setuid32) */
#if __CRT_HAVE_SC(sgetmask)
__CDECLARE_SC(,__syscall_ulong_t,sgetmask,(void),())
#endif /* __CRT_HAVE_SC(sgetmask) */
#if __CRT_HAVE_SC(sigaction)
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,sigaction,(__syscall_ulong_t __signo, struct sigaction const *__act, struct sigaction *__oact),(__signo,__act,__oact))
#endif /* __CRT_HAVE_SC(sigaction) */
#if __CRT_HAVE_SC(signal)
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__sighandler_t,signal,(__syscall_ulong_t __signo, __sighandler_t __handler),(__signo,__handler))
#endif /* __CRT_HAVE_SC(signal) */
#if __CRT_HAVE_SC(sigpending)
__CDECLARE_SC(,__errno_t,sigpending,(struct __sigset_struct *__set),(__set))
#endif /* __CRT_HAVE_SC(sigpending) */
#if __CRT_HAVE_SC(sigprocmask)
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE_SC(,__errno_t,sigprocmask,(__syscall_ulong_t __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),(__how,__set,__oset))
#endif /* __CRT_HAVE_SC(sigprocmask) */
#if __CRT_HAVE_SC(sigreturn)
/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
__CDECLARE_VOID_SC(,sigreturn,(struct fpustate32 const *__restore_fpu, __syscall_ulong_t __unused1, __syscall_ulong_t __unused2, struct __sigset_struct const *__restore_sigmask, struct rpc_syscall_info32 *__sc_info, struct ucpustate32 const *__restore_cpu),(__restore_fpu,__unused1,__unused2,__restore_sigmask,__sc_info,__restore_cpu))
#endif /* __CRT_HAVE_SC(sigreturn) */
#if __CRT_HAVE_SC(sigsuspend)
__CDECLARE_SC(,__errno_t,sigsuspend,(struct __sigset_struct const *__set),(__set))
#endif /* __CRT_HAVE_SC(sigsuspend) */
#if __CRT_HAVE_SC(socketcall)
__CDECLARE_SC(,__errno_t,socketcall,(int __call, unsigned long *__args),(__call,__args))
#endif /* __CRT_HAVE_SC(socketcall) */
#if __CRT_HAVE_SC(ssetmask)
__CDECLARE_SC(,__syscall_ulong_t,ssetmask,(__syscall_ulong_t __sigmask),(__sigmask))
#endif /* __CRT_HAVE_SC(ssetmask) */
#if __CRT_HAVE_SC(statfs64)
__CDECLARE_SC(,__errno_t,statfs64,(char const *__file, struct statfs64 *__buf),(__file,__buf))
#endif /* __CRT_HAVE_SC(statfs64) */
#if __CRT_HAVE_SC(stime)
__CDECLARE_SC(,__errno_t,stime,(__time32_t const *__t),(__t))
#endif /* __CRT_HAVE_SC(stime) */
#if __CRT_HAVE_SC(stime64)
__CDECLARE_SC(,__errno_t,stime64,(__time64_t const *__t),(__t))
#endif /* __CRT_HAVE_SC(stime64) */
#if __CRT_HAVE_SC(stty)
__CDECLARE_SC(,__errno_t,stty,(void),())
#endif /* __CRT_HAVE_SC(stty) */
#if __CRT_HAVE_SC(sysfs)
__CDECLARE_SC(,__errno_t,sysfs,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(sysfs) */
#if __CRT_HAVE_SC(time64)
__CDECLARE_SC(,__time64_t,time64,(__time64_t *__timer),(__timer))
#endif /* __CRT_HAVE_SC(time64) */
#if __CRT_HAVE_SC(timer_gettime)
__CDECLARE_SC(,__errno_t,timer_gettime,(__timer_t __timerid, struct __itimerspecx32 *__value),(__timerid,__value))
#endif /* __CRT_HAVE_SC(timer_gettime) */
#if __CRT_HAVE_SC(timer_gettime64)
__CDECLARE_SC(,__errno_t,timer_gettime64,(__timer_t __timerid, struct __itimerspecx32_64 *__value),(__timerid,__value))
#endif /* __CRT_HAVE_SC(timer_gettime64) */
#if __CRT_HAVE_SC(timer_settime)
__CDECLARE_SC(,__errno_t,timer_settime,(__timer_t __timerid, __syscall_ulong_t __flags, struct __itimerspecx32 const *__value, struct __itimerspecx32 *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* __CRT_HAVE_SC(timer_settime) */
#if __CRT_HAVE_SC(timer_settime64)
__CDECLARE_SC(,__errno_t,timer_settime64,(__timer_t __timerid, __syscall_ulong_t __flags, struct __itimerspecx32_64 const *__value, struct __itimerspecx32_64 *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* __CRT_HAVE_SC(timer_settime64) */
#if __CRT_HAVE_SC(timerfd_gettime)
/* Return the next expiration time of UFD */
__CDECLARE_SC(,__errno_t,timerfd_gettime,(__fd_t __ufd, struct __itimerspecx32 *__otmr),(__ufd,__otmr))
#endif /* __CRT_HAVE_SC(timerfd_gettime) */
#if __CRT_HAVE_SC(timerfd_gettime64)
/* Return the next expiration time of UFD */
__CDECLARE_SC(,__errno_t,timerfd_gettime64,(__fd_t __ufd, struct __itimerspecx32_64 *__otmr),(__ufd,__otmr))
#endif /* __CRT_HAVE_SC(timerfd_gettime64) */
#if __CRT_HAVE_SC(timerfd_settime)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_SC(,__errno_t,timerfd_settime,(__fd_t __ufd, __syscall_ulong_t __flags, struct __itimerspecx32 const *__utmr, struct __itimerspecx32 *__otmr),(__ufd,__flags,__utmr,__otmr))
#endif /* __CRT_HAVE_SC(timerfd_settime) */
#if __CRT_HAVE_SC(timerfd_settime64)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_SC(,__errno_t,timerfd_settime64,(__fd_t __ufd, __syscall_ulong_t __flags, struct __itimerspecx32_64 const *__utmr, struct __itimerspecx32_64 *__otmr),(__ufd,__flags,__utmr,__otmr))
#endif /* __CRT_HAVE_SC(timerfd_settime64) */
#if __CRT_HAVE_SC(truncate64)
__CDECLARE_SC(,__errno_t,truncate64,(char const *__filename, __uint64_t __length),(__filename,__length))
#endif /* __CRT_HAVE_SC(truncate64) */
#if __CRT_HAVE_SC(ugetrlimit)
__CDECLARE_SC(,__errno_t,ugetrlimit,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(ugetrlimit) */
#if __CRT_HAVE_SC(ulimit)
__CDECLARE_SC(,__errno_t,ulimit,(void),())
#endif /* __CRT_HAVE_SC(ulimit) */
#if __CRT_HAVE_SC(umount)
__CDECLARE_SC(,__errno_t,umount,(char const *__special_file),(__special_file))
#endif /* __CRT_HAVE_SC(umount) */
#if __CRT_HAVE_SC(utime)
__CDECLARE_SC(,__errno_t,utime,(char const *__filename, struct __utimbuf32 const *__times),(__filename,__times))
#endif /* __CRT_HAVE_SC(utime) */
#if __CRT_HAVE_SC(utime64)
__CDECLARE_SC(,__errno_t,utime64,(char const *__filename, struct __utimbuf64 const *__times),(__filename,__times))
#endif /* __CRT_HAVE_SC(utime64) */
#if __CRT_HAVE_SC(utimensat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,utimensat,(__fd_t __dirfd, char const *__filename, struct __timespecx32 const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* __CRT_HAVE_SC(utimensat) */
#if __CRT_HAVE_SC(utimensat64)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,utimensat64,(__fd_t __dirfd, char const *__filename, struct __timespecx32_64 const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* __CRT_HAVE_SC(utimensat64) */
#if __CRT_HAVE_SC(utimes)
__CDECLARE_SC(,__errno_t,utimes,(char const *__filename, struct __timevalx32 const *__times),(__filename,__times))
#endif /* __CRT_HAVE_SC(utimes) */
#if __CRT_HAVE_SC(utimes64)
__CDECLARE_SC(,__errno_t,utimes64,(char const *__filename, struct __timevalx32_64 const *__times),(__filename,__times))
#endif /* __CRT_HAVE_SC(utimes64) */
#if __CRT_HAVE_SC(vm86)
__CDECLARE_SC(,__errno_t,vm86,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(vm86) */
#if __CRT_HAVE_SC(vm86old)
__CDECLARE_SC(,__errno_t,vm86old,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(vm86old) */
#if __CRT_HAVE_SC(vmsplice)
__CDECLARE_SC(,__ssize_t,vmsplice,(__fd_t __fdout, struct iovec32 const *__iov, __size_t __count, __syscall_ulong_t __flags),(__fdout,__iov,__count,__flags))
#endif /* __CRT_HAVE_SC(vmsplice) */
#if __CRT_HAVE_SC(vserver)
__CDECLARE_SC(,__errno_t,vserver,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(vserver) */
#if __CRT_HAVE_SC(waitid)
/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
__CDECLARE_SC(,__errno_t,waitid,(__syscall_ulong_t __idtype, __id_t __id, struct __siginfo32_struct *__infop, __syscall_ulong_t __options, struct rusage *__ru),(__idtype,__id,__infop,__options,__ru))
#endif /* __CRT_HAVE_SC(waitid) */
#if __CRT_HAVE_SC(waitpid)
/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE_SC(,__pid_t,waitpid,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options),(__pid,__stat_loc,__options))
#endif /* __CRT_HAVE_SC(waitpid) */
#if __CRT_HAVE_SC(writef)
__CDECLARE_SC(,__ssize_t,writef,(__fd_t __fd, void const *__buf, __size_t __bufsize, __iomode_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* __CRT_HAVE_SC(writef) */
#if __CRT_HAVE_SC(writev)
__CDECLARE_SC(,__ssize_t,writev,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_SC(writev) */
#if __CRT_HAVE_SC(writevf)
__CDECLARE_SC(,__ssize_t,writevf,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __iomode_t __mode),(__fd,__iovec,__count,__mode))
#endif /* __CRT_HAVE_SC(writevf) */
#if __CRT_HAVE_XSC(_llseek)
__CDECLARE_XSC(,__errno_t,_llseek,(__fd_t __fd, __int64_t __offset, __uint64_t *__result, __syscall_ulong_t __whence),(__fd,__offset,__result,__whence))
#endif /* __CRT_HAVE_XSC(_llseek) */
#if __CRT_HAVE_XSC(_newselect)
__CDECLARE_XSC(,__errno_t,_newselect,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(_newselect) */
#if __CRT_HAVE_XSC(afs_syscall)
__CDECLARE_XSC(,__errno_t,afs_syscall,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(afs_syscall) */
#if __CRT_HAVE_XSC(bdflush)
__CDECLARE_XSC(,__errno_t,bdflush,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(bdflush) */
#if __CRT_HAVE_XSC(break)
__CDECLARE_XSC(,__errno_t,break,(void),())
#endif /* __CRT_HAVE_XSC(break) */
#if __CRT_HAVE_XSC(chown)
__CDECLARE_XSC(,__errno_t,chown,(char const *__filename, __uint16_t __owner, __uint16_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_XSC(chown) */
#if __CRT_HAVE_XSC(chown32)
__CDECLARE_XSC(,__errno_t,chown32,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_XSC(chown32) */
#if __CRT_HAVE_XSC(clock_getres)
__CDECLARE_XSC(,__errno_t,clock_getres,(__clockid_t __clock_id, struct __timespecx32 *__res),(__clock_id,__res))
#endif /* __CRT_HAVE_XSC(clock_getres) */
#if __CRT_HAVE_XSC(clock_getres64)
__CDECLARE_XSC(,__errno_t,clock_getres64,(__clockid_t __clock_id, struct __timespecx32_64 *__res),(__clock_id,__res))
#endif /* __CRT_HAVE_XSC(clock_getres64) */
#if __CRT_HAVE_XSC(clock_gettime)
__CDECLARE_XSC(,__errno_t,clock_gettime,(__clockid_t __clock_id, struct __timespecx32 *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_XSC(clock_gettime) */
#if __CRT_HAVE_XSC(clock_gettime64)
__CDECLARE_XSC(,__errno_t,clock_gettime64,(__clockid_t __clock_id, struct __timespecx32_64 *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_XSC(clock_gettime64) */
#if __CRT_HAVE_XSC(clock_nanosleep)
__CDECLARE_XSC(,__errno_t,clock_nanosleep,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct __timespecx32 const *__requested_time, struct __timespecx32 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* __CRT_HAVE_XSC(clock_nanosleep) */
#if __CRT_HAVE_XSC(clock_nanosleep64)
__CDECLARE_XSC(,__errno_t,clock_nanosleep64,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct __timespecx32_64 const *__requested_time, struct __timespecx32_64 *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* __CRT_HAVE_XSC(clock_nanosleep64) */
#if __CRT_HAVE_XSC(clock_settime)
__CDECLARE_XSC(,__errno_t,clock_settime,(__clockid_t __clock_id, struct __timespecx32 const *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_XSC(clock_settime) */
#if __CRT_HAVE_XSC(clock_settime64)
__CDECLARE_XSC(,__errno_t,clock_settime64,(__clockid_t __clock_id, struct __timespecx32_64 const *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_XSC(clock_settime64) */
#if __CRT_HAVE_XSC(clone)
__CDECLARE_XSC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __uintptr_t __newtls, __pid_t *__ctid),(__flags,__child_stack,__ptid,__newtls,__ctid))
#endif /* __CRT_HAVE_XSC(clone) */
#if __CRT_HAVE_XSC(coredump)
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
__CDECLARE_XSC(,__errno_t,coredump,(struct ucpustate32 const *__curr_state, struct ucpustate32 const *__orig_state, __HYBRID_PTR32(void) const *__traceback_vector, __size_t __traceback_length, struct exception_data32 const *__exception, __syscall_ulong_t __unwind_error),(__curr_state,__orig_state,__traceback_vector,__traceback_length,__exception,__unwind_error))
#endif /* __CRT_HAVE_XSC(coredump) */
#if __CRT_HAVE_XSC(create_module)
__CDECLARE_XSC(,__errno_t,create_module,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(create_module) */
#if __CRT_HAVE_XSC(debugtrap)
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
__CDECLARE_XSC(,__errno_t,debugtrap,(struct ucpustate32 const *__state, struct debugtrap_reason32 const *__reason),(__state,__reason))
#endif /* __CRT_HAVE_XSC(debugtrap) */
#if __CRT_HAVE_XSC(detach)
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
#endif /* __CRT_HAVE_XSC(detach) */
#if __CRT_HAVE_XSC(fadvise64_64)
__CDECLARE_XSC(,__errno_t,fadvise64_64,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(fadvise64_64) */
#if __CRT_HAVE_XSC(fallocate64)
__CDECLARE_XSC(,__errno_t,fallocate64,(__fd_t __fd, __syscall_ulong_t __mode, __uint64_t __offset, __uint64_t __length),(__fd,__mode,__offset,__length))
#endif /* __CRT_HAVE_XSC(fallocate64) */
#if __CRT_HAVE_XSC(fchdirat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fchdirat,(__fd_t __dirfd, char const *__path, __atflag_t __flags),(__dirfd,__path,__flags))
#endif /* __CRT_HAVE_XSC(fchdirat) */
#if __CRT_HAVE_XSC(fchown)
__CDECLARE_XSC(,__errno_t,fchown,(__fd_t __fd, __uint16_t __owner, __uint16_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_XSC(fchown) */
#if __CRT_HAVE_XSC(fchown32)
__CDECLARE_XSC(,__errno_t,fchown32,(__fd_t __fd, __uint32_t __owner, __uint32_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_XSC(fchown32) */
#if __CRT_HAVE_XSC(fcntl64)
__CDECLARE_XSC(,__syscall_slong_t,fcntl64,(__fd_t __fd, __syscall_ulong_t __command, void *__arg),(__fd,__command,__arg))
#endif /* __CRT_HAVE_XSC(fcntl64) */
#if __CRT_HAVE_XSC(fmkdirat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fmkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode, __atflag_t __flags),(__dirfd,__pathname,__mode,__flags))
#endif /* __CRT_HAVE_XSC(fmkdirat) */
#if __CRT_HAVE_XSC(fmknodat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fmknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),(__dirfd,__nodename,__mode,__dev,__flags))
#endif /* __CRT_HAVE_XSC(fmknodat) */
#if __CRT_HAVE_XSC(freadlinkat)
/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
__CDECLARE_XSC(,__ssize_t,freadlinkat,(__fd_t __dirfd, char const *__path, char *__buf, __size_t __buflen, __atflag_t __flags),(__dirfd,__path,__buf,__buflen,__flags))
#endif /* __CRT_HAVE_XSC(freadlinkat) */
#if __CRT_HAVE_XSC(frealpath4)
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
__CDECLARE_XSC(,__ssize_t,frealpath4,(__fd_t __fd, char *__buf, __size_t __buflen, __atflag_t __flags),(__fd,__buf,__buflen,__flags))
#endif /* __CRT_HAVE_XSC(frealpath4) */
#if __CRT_HAVE_XSC(frealpathat)
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
__CDECLARE_XSC(,__ssize_t,frealpathat,(__fd_t __dirfd, char const *__filename, char *__buf, __size_t __buflen, __atflag_t __flags),(__dirfd,__filename,__buf,__buflen,__flags))
#endif /* __CRT_HAVE_XSC(frealpathat) */
#if __CRT_HAVE_XSC(frenameat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,frenameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path, __atflag_t __flags),(__oldfd,__oldname,__newfd,__newname_or_path,__flags))
#endif /* __CRT_HAVE_XSC(frenameat) */
#if __CRT_HAVE_XSC(fsmode)
__CDECLARE_XSC(,__uint64_t,fsmode,(__uint64_t __mode),(__mode))
#endif /* __CRT_HAVE_XSC(fsmode) */
#if __CRT_HAVE_XSC(fstatfs64)
__CDECLARE_XSC(,__errno_t,fstatfs64,(__fd_t __file, struct statfs64 *__buf),(__file,__buf))
#endif /* __CRT_HAVE_XSC(fstatfs64) */
#if __CRT_HAVE_XSC(fsymlinkat)
/* @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fsymlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__link_text,__tofd,__target_path,__flags))
#endif /* __CRT_HAVE_XSC(fsymlinkat) */
#if __CRT_HAVE_XSC(ftime)
__CDECLARE_XSC(,__errno_t,ftime,(struct timeb *__tp),(__tp))
#endif /* __CRT_HAVE_XSC(ftime) */
#if __CRT_HAVE_XSC(ftruncate64)
__CDECLARE_XSC(,__errno_t,ftruncate64,(__fd_t __fd, __uint64_t __length),(__fd,__length))
#endif /* __CRT_HAVE_XSC(ftruncate64) */
#if __CRT_HAVE_XSC(futex)
__CDECLARE_XSC(,__syscall_slong_t,futex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct __timespecx32 const *__timeout_or_val2, __uint32_t *__uaddr2, __uint32_t __val3),(__uaddr,__futex_op,__val,__timeout_or_val2,__uaddr2,__val3))
#endif /* __CRT_HAVE_XSC(futex) */
#if __CRT_HAVE_XSC(futimesat)
__CDECLARE_XSC(,__errno_t,futimesat,(__fd_t __dirfd, __const char *__filename, struct __timevalx32 const *__times),(__dirfd,__filename,__times))
#endif /* __CRT_HAVE_XSC(futimesat) */
#if __CRT_HAVE_XSC(futimesat64)
__CDECLARE_XSC(,__errno_t,futimesat64,(__fd_t __dirfd, __const char *__filename, struct __timevalx32_64 const *__times),(__dirfd,__filename,__times))
#endif /* __CRT_HAVE_XSC(futimesat64) */
#if __CRT_HAVE_XSC(get_exception_handler)
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
__CDECLARE_XSC(,__errno_t,get_exception_handler,(__ULONG32_TYPE__ *__pmode, __except_handler32_t *__phandler, __HYBRID_PTR32(void) *__phandler_sp),(__pmode,__phandler,__phandler_sp))
#endif /* __CRT_HAVE_XSC(get_exception_handler) */
#if __CRT_HAVE_XSC(get_kernel_syms)
__CDECLARE_XSC(,__errno_t,get_kernel_syms,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(get_kernel_syms) */
#if __CRT_HAVE_XSC(get_thread_area)
__CDECLARE_XSC(,__errno_t,get_thread_area,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(get_thread_area) */
#if __CRT_HAVE_XSC(getdrives)
/* Returns a bitset of all of the currently mounted dos-drives */
__CDECLARE_XSC(,__syscall_slong_t,getdrives,(void),())
#endif /* __CRT_HAVE_XSC(getdrives) */
#if __CRT_HAVE_XSC(getegid)
__CDECLARE_XSC(,__uint16_t,getegid,(void),())
#endif /* __CRT_HAVE_XSC(getegid) */
#if __CRT_HAVE_XSC(getegid32)
__CDECLARE_XSC(,__uint32_t,getegid32,(void),())
#endif /* __CRT_HAVE_XSC(getegid32) */
#if __CRT_HAVE_XSC(geteuid)
__CDECLARE_XSC(,__uint16_t,geteuid,(void),())
#endif /* __CRT_HAVE_XSC(geteuid) */
#if __CRT_HAVE_XSC(geteuid32)
__CDECLARE_XSC(,__uint32_t,geteuid32,(void),())
#endif /* __CRT_HAVE_XSC(geteuid32) */
#if __CRT_HAVE_XSC(getgid)
__CDECLARE_XSC(,__uint16_t,getgid,(void),())
#endif /* __CRT_HAVE_XSC(getgid) */
#if __CRT_HAVE_XSC(getgid32)
__CDECLARE_XSC(,__uint32_t,getgid32,(void),())
#endif /* __CRT_HAVE_XSC(getgid32) */
#if __CRT_HAVE_XSC(getgroups)
__CDECLARE_XSC(,__errno_t,getgroups,(__size_t __size, __uint16_t *__list),(__size,__list))
#endif /* __CRT_HAVE_XSC(getgroups) */
#if __CRT_HAVE_XSC(getgroups32)
__CDECLARE_XSC(,__errno_t,getgroups32,(__size_t __size, __uint32_t *__list),(__size,__list))
#endif /* __CRT_HAVE_XSC(getgroups32) */
#if __CRT_HAVE_XSC(getitimer64)
__CDECLARE_XSC(,__errno_t,getitimer64,(__syscall_ulong_t __which, struct __itimerval64 *__curr_value),(__which,__curr_value))
#endif /* __CRT_HAVE_XSC(getitimer64) */
#if __CRT_HAVE_XSC(getpmsg)
__CDECLARE_XSC(,__errno_t,getpmsg,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(getpmsg) */
#if __CRT_HAVE_XSC(getresgid)
__CDECLARE_XSC(,__errno_t,getresgid,(__uint16_t *__rgid, __uint16_t *__egid, __uint16_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_XSC(getresgid) */
#if __CRT_HAVE_XSC(getresgid32)
__CDECLARE_XSC(,__errno_t,getresgid32,(__uint32_t *__rgid, __uint32_t *__egid, __uint32_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_XSC(getresgid32) */
#if __CRT_HAVE_XSC(getresuid)
__CDECLARE_XSC(,__errno_t,getresuid,(__uint16_t *__ruid, __uint16_t *__euid, __uint16_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_XSC(getresuid) */
#if __CRT_HAVE_XSC(getresuid32)
__CDECLARE_XSC(,__errno_t,getresuid32,(__uint32_t *__ruid, __uint32_t *__euid, __uint32_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_XSC(getresuid32) */
#if __CRT_HAVE_XSC(gettimeofday)
__CDECLARE_XSC(,__errno_t,gettimeofday,(struct __timevalx32 *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_XSC(gettimeofday) */
#if __CRT_HAVE_XSC(gettimeofday64)
__CDECLARE_XSC(,__errno_t,gettimeofday64,(struct __timevalx32_64 *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_XSC(gettimeofday64) */
#if __CRT_HAVE_XSC(getuid)
__CDECLARE_XSC(,__uint16_t,getuid,(void),())
#endif /* __CRT_HAVE_XSC(getuid) */
#if __CRT_HAVE_XSC(getuid32)
__CDECLARE_XSC(,__uint32_t,getuid32,(void),())
#endif /* __CRT_HAVE_XSC(getuid32) */
#if __CRT_HAVE_XSC(gtty)
__CDECLARE_XSC(,__errno_t,gtty,(void),())
#endif /* __CRT_HAVE_XSC(gtty) */
#if __CRT_HAVE_XSC(hop)
__CDECLARE_XSC(,__syscall_slong_t,hop,(__fd_t __fd, __syscall_ulong_t __command, void *__arg),(__fd,__command,__arg))
#endif /* __CRT_HAVE_XSC(hop) */
#if __CRT_HAVE_XSC(hopf)
__CDECLARE_XSC(,__syscall_slong_t,hopf,(__fd_t __fd, __syscall_ulong_t __command, __iomode_t __mode, void *__arg),(__fd,__command,__mode,__arg))
#endif /* __CRT_HAVE_XSC(hopf) */
#if __CRT_HAVE_XSC(idle)
__CDECLARE_XSC(,__errno_t,idle,(void),())
#endif /* __CRT_HAVE_XSC(idle) */
#if __CRT_HAVE_XSC(ioctlf)
__CDECLARE_XSC(,__syscall_slong_t,ioctlf,(__fd_t __fd, __syscall_ulong_t __command, __iomode_t __mode, void *__arg),(__fd,__command,__mode,__arg))
#endif /* __CRT_HAVE_XSC(ioctlf) */
#if __CRT_HAVE_XSC(ioperm)
__CDECLARE_XSC(,__errno_t,ioperm,(__syscall_ulong_t __from, __syscall_ulong_t __num, __syscall_ulong_t __turn_on),(__from,__num,__turn_on))
#endif /* __CRT_HAVE_XSC(ioperm) */
#if __CRT_HAVE_XSC(iopl)
__CDECLARE_XSC(,__errno_t,iopl,(__syscall_ulong_t __level),(__level))
#endif /* __CRT_HAVE_XSC(iopl) */
#if __CRT_HAVE_XSC(ipc)
__CDECLARE_XSC(,__errno_t,ipc,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(ipc) */
#if __CRT_HAVE_XSC(kfstat)
__CDECLARE_XSC(,__errno_t,kfstat,(__fd_t __fd, struct stat *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_XSC(kfstat) */
#if __CRT_HAVE_XSC(kfstatat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,kfstatat,(__fd_t __dirfd, char const *__filename, struct stat *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* __CRT_HAVE_XSC(kfstatat) */
#if __CRT_HAVE_XSC(klstat)
__CDECLARE_XSC(,__errno_t,klstat,(char const *__filename, struct stat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(klstat) */
#if __CRT_HAVE_XSC(kreaddir)
__CDECLARE_XSC(,__ssize_t,kreaddir,(__fd_t __fd, struct dirent *__buf, __size_t __bufsize, __syscall_ulong_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* __CRT_HAVE_XSC(kreaddir) */
#if __CRT_HAVE_XSC(kreaddirf)
__CDECLARE_XSC(,__ssize_t,kreaddirf,(__fd_t __fd, struct dirent *__buf, __size_t __bufsize, __syscall_ulong_t __mode, __iomode_t __iomode),(__fd,__buf,__bufsize,__mode,__iomode))
#endif /* __CRT_HAVE_XSC(kreaddirf) */
#if __CRT_HAVE_XSC(kstat)
__CDECLARE_XSC(,__errno_t,kstat,(char const *__filename, struct stat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(kstat) */
#if __CRT_HAVE_XSC(ksysctl)
__CDECLARE_XSC(,__syscall_slong_t,ksysctl,(__syscall_ulong_t __command, void *__arg),(__command,__arg))
#endif /* __CRT_HAVE_XSC(ksysctl) */
#if __CRT_HAVE_XSC(lchown)
__CDECLARE_XSC(,__errno_t,lchown,(char const *__filename, __uint16_t __owner, __uint16_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_XSC(lchown) */
#if __CRT_HAVE_XSC(lchown32)
__CDECLARE_XSC(,__errno_t,lchown32,(char const *__filename, __uint32_t __owner, __uint32_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_XSC(lchown32) */
#if __CRT_HAVE_XSC(lfutex)
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
__CDECLARE_XSC(,__syscall_slong_t,lfutex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct __timespecx32_64 const *__timeout, __uint32_t __val2),(__uaddr,__futex_op,__val,__timeout,__val2))
#endif /* __CRT_HAVE_XSC(lfutex) */
#if __CRT_HAVE_XSC(lfutexexpr)
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
__CDECLARE_XSC(,__errno_t,lfutexexpr,(void *__base, __size_t __exprc, struct lfutexexpr32 const *__exprv, struct __timespecx32_64 const *__timeout, __syscall_ulong_t __timeout_flags),(__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* __CRT_HAVE_XSC(lfutexexpr) */
#if __CRT_HAVE_XSC(lfutexlockexpr)
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
__CDECLARE_XSC(,__errno_t,lfutexlockexpr,(__uint32_t *__ulockaddr, void *__base, __size_t __exprc, struct lfutexexpr32 const *__exprv, struct __timespecx32_64 const *__timeout, __syscall_ulong_t __timeout_flags),(__ulockaddr,__base,__exprc,__exprv,__timeout,__timeout_flags))
#endif /* __CRT_HAVE_XSC(lfutexlockexpr) */
#if __CRT_HAVE_XSC(linux_fstat32)
__CDECLARE_XSC(,__errno_t,linux_fstat32,(__fd_t __fd, struct linux_stat32 *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_fstat32) */
#if __CRT_HAVE_XSC(linux_fstat64)
__CDECLARE_XSC(,__errno_t,linux_fstat64,(__fd_t __fd, struct linux_stat64 *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_fstat64) */
#if __CRT_HAVE_XSC(linux_fstatat64)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,linux_fstatat64,(__fd_t __dirfd, char const *__filename, struct linux_stat64 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* __CRT_HAVE_XSC(linux_fstatat64) */
#if __CRT_HAVE_XSC(linux_lstat32)
__CDECLARE_XSC(,__errno_t,linux_lstat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_lstat32) */
#if __CRT_HAVE_XSC(linux_lstat64)
__CDECLARE_XSC(,__errno_t,linux_lstat64,(char const *__filename, struct linux_stat64 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_lstat64) */
#if __CRT_HAVE_XSC(linux_oldfstat)
__CDECLARE_XSC(,__errno_t,linux_oldfstat,(__fd_t __fd, struct linux_oldstat *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_oldfstat) */
#if __CRT_HAVE_XSC(linux_oldlstat)
__CDECLARE_XSC(,__errno_t,linux_oldlstat,(char const *__filename, struct linux_oldstat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_oldlstat) */
#if __CRT_HAVE_XSC(linux_oldstat)
__CDECLARE_XSC(,__errno_t,linux_oldstat,(char const *__filename, struct linux_oldstat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_oldstat) */
#if __CRT_HAVE_XSC(linux_stat32)
__CDECLARE_XSC(,__errno_t,linux_stat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_stat32) */
#if __CRT_HAVE_XSC(linux_stat64)
__CDECLARE_XSC(,__errno_t,linux_stat64,(char const *__filename, struct linux_stat64 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_stat64) */
#if __CRT_HAVE_XSC(lock)
__CDECLARE_XSC(,__errno_t,lock,(void),())
#endif /* __CRT_HAVE_XSC(lock) */
#if __CRT_HAVE_XSC(lseek)
__CDECLARE_XSC(,__syscall_slong_t,lseek,(__fd_t __fd, __syscall_slong_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* __CRT_HAVE_XSC(lseek) */
#if __CRT_HAVE_XSC(lseek64)
__CDECLARE_XSC(,__int64_t,lseek64,(__fd_t __fd, __int64_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* __CRT_HAVE_XSC(lseek64) */
#if __CRT_HAVE_XSC(maplibrary)
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
#endif /* __CRT_HAVE_XSC(maplibrary) */
#if __CRT_HAVE_XSC(mktty)
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
__CDECLARE_XSC(,__fd_t,mktty,(__fd_t __keyboard, __fd_t __display, char const *__name, __syscall_ulong_t __rsvd),(__keyboard,__display,__name,__rsvd))
#endif /* __CRT_HAVE_XSC(mktty) */
#if __CRT_HAVE_XSC(mmap)
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
__CDECLARE_XSC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* __CRT_HAVE_XSC(mmap) */
#if __CRT_HAVE_XSC(mmap2)
__CDECLARE_XSC(,void *,mmap2,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __pgoffset),(__addr,__len,__prot,__flags,__fd,__pgoffset))
#endif /* __CRT_HAVE_XSC(mmap2) */
#if __CRT_HAVE_XSC(modify_ldt)
__CDECLARE_XSC(,__syscall_slong_t,modify_ldt,(__syscall_ulong_t __func, void *__ptr, __syscall_ulong_t __bytecount),(__func,__ptr,__bytecount))
#endif /* __CRT_HAVE_XSC(modify_ldt) */
#if __CRT_HAVE_XSC(mpx)
__CDECLARE_XSC(,__errno_t,mpx,(void),())
#endif /* __CRT_HAVE_XSC(mpx) */
#if __CRT_HAVE_XSC(mq_timedreceive)
__CDECLARE_XSC(,__ssize_t,mq_timedreceive,(__fd_t __mqdes, char *__msg_ptr, __size_t __msg_len, __uint32_t *__pmsg_prio, struct __timespecx32 const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#endif /* __CRT_HAVE_XSC(mq_timedreceive) */
#if __CRT_HAVE_XSC(mq_timedreceive64)
__CDECLARE_XSC(,__ssize_t,mq_timedreceive64,(__fd_t __mqdes, char *__msg_ptr, __size_t __msg_len, __uint32_t *__pmsg_prio, struct __timespecx32_64 const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#endif /* __CRT_HAVE_XSC(mq_timedreceive64) */
#if __CRT_HAVE_XSC(mq_timedsend)
__CDECLARE_XSC(,__errno_t,mq_timedsend,(__fd_t __mqdes, char const *__msg_ptr, __size_t __msg_len, __uint32_t __msg_prio, struct __timespecx32 const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#endif /* __CRT_HAVE_XSC(mq_timedsend) */
#if __CRT_HAVE_XSC(mq_timedsend64)
__CDECLARE_XSC(,__errno_t,mq_timedsend64,(__fd_t __mqdes, char const *__msg_ptr, __size_t __msg_len, __uint32_t __msg_prio, struct __timespecx32_64 const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#endif /* __CRT_HAVE_XSC(mq_timedsend64) */
#if __CRT_HAVE_XSC(nanosleep)
__CDECLARE_XSC(,__errno_t,nanosleep,(struct __timespecx32 const *__req, struct __timespecx32 *__rem),(__req,__rem))
#endif /* __CRT_HAVE_XSC(nanosleep) */
#if __CRT_HAVE_XSC(nanosleep64)
__CDECLARE_XSC(,__errno_t,nanosleep64,(struct __timespecx32_64 const *__req, struct __timespecx32_64 *__rem),(__req,__rem))
#endif /* __CRT_HAVE_XSC(nanosleep64) */
#if __CRT_HAVE_XSC(nice)
__CDECLARE_XSC(,__errno_t,nice,(__syscall_slong_t __inc),(__inc))
#endif /* __CRT_HAVE_XSC(nice) */
#if __CRT_HAVE_XSC(oldolduname)
__CDECLARE_XSC(,__errno_t,oldolduname,(struct linux_oldolduname *__name),(__name))
#endif /* __CRT_HAVE_XSC(oldolduname) */
#if __CRT_HAVE_XSC(olduname)
__CDECLARE_XSC(,__errno_t,olduname,(struct linux_olduname *__name),(__name))
#endif /* __CRT_HAVE_XSC(olduname) */
#if __CRT_HAVE_XSC(openpty)
/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
__CDECLARE_XSC(,__errno_t,openpty,(__fd_t *__amaster, __fd_t *__aslave, char *__name, struct termios const *__termp, struct winsize const *__winp),(__amaster,__aslave,__name,__termp,__winp))
#endif /* __CRT_HAVE_XSC(openpty) */
#if __CRT_HAVE_XSC(ppoll)
__CDECLARE_XSC(,__ssize_t,ppoll,(struct pollfd *__fds, __size_t __nfds, struct __timespecx32 const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* __CRT_HAVE_XSC(ppoll) */
#if __CRT_HAVE_XSC(ppoll64)
__CDECLARE_XSC(,__ssize_t,ppoll64,(struct pollfd *__fds, __size_t __nfds, struct __timespecx32_64 const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* __CRT_HAVE_XSC(ppoll64) */
#if __CRT_HAVE_XSC(pread64f)
__CDECLARE_XSC(,__ssize_t,pread64f,(__fd_t __fd, void *__buf, __size_t __bufsize, __uint64_t __offset, __iomode_t __mode),(__fd,__buf,__bufsize,__offset,__mode))
#endif /* __CRT_HAVE_XSC(pread64f) */
#if __CRT_HAVE_XSC(preadv)
__CDECLARE_XSC(,__ssize_t,preadv,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_XSC(preadv) */
#if __CRT_HAVE_XSC(preadvf)
__CDECLARE_XSC(,__ssize_t,preadvf,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __uint64_t __offset, __iomode_t __mode),(__fd,__iovec,__count,__offset,__mode))
#endif /* __CRT_HAVE_XSC(preadvf) */
#if __CRT_HAVE_XSC(process_vm_readv)
__CDECLARE_XSC(,__ssize_t,process_vm_readv,(__pid_t __pid, struct iovec32 const *__lvec, __size_t __liovcnt, struct iovec32 const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* __CRT_HAVE_XSC(process_vm_readv) */
#if __CRT_HAVE_XSC(process_vm_writev)
__CDECLARE_XSC(,__ssize_t,process_vm_writev,(__pid_t __pid, struct iovec32 const *__lvec, __size_t __liovcnt, struct iovec32 const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* __CRT_HAVE_XSC(process_vm_writev) */
#if __CRT_HAVE_XSC(prof)
__CDECLARE_XSC(,__errno_t,prof,(void),())
#endif /* __CRT_HAVE_XSC(prof) */
#if __CRT_HAVE_XSC(profil)
__CDECLARE_XSC(,__errno_t,profil,(__uint16_t *__sample_buffer, __size_t __size, __size_t __offset, __syscall_ulong_t __scale),(__sample_buffer,__size,__offset,__scale))
#endif /* __CRT_HAVE_XSC(profil) */
#if __CRT_HAVE_XSC(pselect6)
__CDECLARE_XSC(,__ssize_t,pselect6,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timespecx32 const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#endif /* __CRT_HAVE_XSC(pselect6) */
#if __CRT_HAVE_XSC(pselect6_64)
__CDECLARE_XSC(,__ssize_t,pselect6_64,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timespecx32_64 const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#endif /* __CRT_HAVE_XSC(pselect6_64) */
#if __CRT_HAVE_XSC(putpmsg)
__CDECLARE_XSC(,__errno_t,putpmsg,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(putpmsg) */
#if __CRT_HAVE_XSC(pwrite64f)
__CDECLARE_XSC(,__ssize_t,pwrite64f,(__fd_t __fd, void const *__buf, __size_t __bufsize, __uint64_t __offset, __iomode_t __mode),(__fd,__buf,__bufsize,__offset,__mode))
#endif /* __CRT_HAVE_XSC(pwrite64f) */
#if __CRT_HAVE_XSC(pwritev)
__CDECLARE_XSC(,__ssize_t,pwritev,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_XSC(pwritev) */
#if __CRT_HAVE_XSC(pwritevf)
__CDECLARE_XSC(,__ssize_t,pwritevf,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __uint64_t __offset, __iomode_t __mode),(__fd,__iovec,__count,__offset,__mode))
#endif /* __CRT_HAVE_XSC(pwritevf) */
#if __CRT_HAVE_XSC(query_module)
__CDECLARE_XSC(,__errno_t,query_module,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(query_module) */
#if __CRT_HAVE_XSC(raiseat)
/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
__CDECLARE_XSC(,__errno_t,raiseat,(struct ucpustate32 const *__state, struct __siginfo32_struct const *__si),(__state,__si))
#endif /* __CRT_HAVE_XSC(raiseat) */
#if __CRT_HAVE_XSC(readdir)
/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
__CDECLARE_XSC(,__errno_t,readdir,(__fd_t __fd, struct old_linux_dirent *__dirp, __size_t __count),(__fd,__dirp,__count))
#endif /* __CRT_HAVE_XSC(readdir) */
#if __CRT_HAVE_XSC(readf)
__CDECLARE_XSC(,__ssize_t,readf,(__fd_t __fd, void *__buf, __size_t __bufsize, __iomode_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* __CRT_HAVE_XSC(readf) */
#if __CRT_HAVE_XSC(readv)
__CDECLARE_XSC(,__ssize_t,readv,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_XSC(readv) */
#if __CRT_HAVE_XSC(readvf)
__CDECLARE_XSC(,__ssize_t,readvf,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __iomode_t __mode),(__fd,__iovec,__count,__mode))
#endif /* __CRT_HAVE_XSC(readvf) */
#if __CRT_HAVE_XSC(recvmmsg)
__CDECLARE_XSC(,__ssize_t,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct __timespecx32 *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#endif /* __CRT_HAVE_XSC(recvmmsg) */
#if __CRT_HAVE_XSC(recvmmsg64)
__CDECLARE_XSC(,__ssize_t,recvmmsg64,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct __timespecx32_64 *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#endif /* __CRT_HAVE_XSC(recvmmsg64) */
#if __CRT_HAVE_XSC(rpc_schedule)
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
__CDECLARE_XSC(,__syscall_slong_t,rpc_schedule,(__pid_t __target, __syscall_ulong_t __flags, __uint8_t const *__program, __HYBRID_PTR32(void) *__arguments),(__target,__flags,__program,__arguments))
#endif /* __CRT_HAVE_XSC(rpc_schedule) */
#if __CRT_HAVE_XSC(rpc_service)
__CDECLARE_XSC(,__syscall_slong_t,rpc_service,(void),())
#endif /* __CRT_HAVE_XSC(rpc_service) */
#if __CRT_HAVE_XSC(rt_sigqueueinfo)
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,rt_sigqueueinfo,(__pid_t __tgid, __syscall_ulong_t __signo, struct __siginfo32_struct const *__uinfo),(__tgid,__signo,__uinfo))
#endif /* __CRT_HAVE_XSC(rt_sigqueueinfo) */
#if __CRT_HAVE_XSC(rt_sigtimedwait)
__CDECLARE_XSC(,__syscall_slong_t,rt_sigtimedwait,(struct __sigset_struct const *__set, struct __siginfo32_struct *__info, struct __timespecx32 const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* __CRT_HAVE_XSC(rt_sigtimedwait) */
#if __CRT_HAVE_XSC(rt_sigtimedwait64)
__CDECLARE_XSC(,__syscall_slong_t,rt_sigtimedwait64,(struct __sigset_struct const *__set, struct __siginfo32_struct *__info, struct __timespecx32_64 const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* __CRT_HAVE_XSC(rt_sigtimedwait64) */
#if __CRT_HAVE_XSC(rt_tgsigqueueinfo)
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,rt_tgsigqueueinfo,(__pid_t __tgid, __pid_t __tid, __syscall_ulong_t __signo, struct __siginfo32_struct const *__uinfo),(__tgid,__tid,__signo,__uinfo))
#endif /* __CRT_HAVE_XSC(rt_tgsigqueueinfo) */
#if __CRT_HAVE_XSC(sched_rr_get_interval)
__CDECLARE_XSC(,__errno_t,sched_rr_get_interval,(__pid_t __pid, struct __timespecx32 *__tms),(__pid,__tms))
#endif /* __CRT_HAVE_XSC(sched_rr_get_interval) */
#if __CRT_HAVE_XSC(sched_rr_get_interval64)
__CDECLARE_XSC(,__errno_t,sched_rr_get_interval64,(__pid_t __pid, struct __timespecx32_64 *__tms),(__pid,__tms))
#endif /* __CRT_HAVE_XSC(sched_rr_get_interval64) */
#if __CRT_HAVE_XSC(select)
__CDECLARE_XSC(,__ssize_t,select,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timevalx32 *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* __CRT_HAVE_XSC(select) */
#if __CRT_HAVE_XSC(select64)
__CDECLARE_XSC(,__ssize_t,select64,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct __timevalx32_64 *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* __CRT_HAVE_XSC(select64) */
#if __CRT_HAVE_XSC(sendfile64)
__CDECLARE_XSC(,__ssize_t,sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __uint64_t *__offset, __size_t __count),(__out_fd,__in_fd,__offset,__count))
#endif /* __CRT_HAVE_XSC(sendfile64) */
#if __CRT_HAVE_XSC(set_exception_handler)
/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
__CDECLARE_XSC(,__errno_t,set_exception_handler,(__syscall_ulong_t __mode, __except_handler32_t __handler, void *__handler_sp),(__mode,__handler,__handler_sp))
#endif /* __CRT_HAVE_XSC(set_exception_handler) */
#if __CRT_HAVE_XSC(set_library_listdef)
/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
__CDECLARE_XSC(,__errno_t,set_library_listdef,(struct library_listdef32 const *__listdef),(__listdef))
#endif /* __CRT_HAVE_XSC(set_library_listdef) */
#if __CRT_HAVE_XSC(set_thread_area)
__CDECLARE_XSC(,__errno_t,set_thread_area,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(set_thread_area) */
#if __CRT_HAVE_XSC(setfsgid)
__CDECLARE_XSC(,__errno_t,setfsgid,(__uint16_t __gid),(__gid))
#endif /* __CRT_HAVE_XSC(setfsgid) */
#if __CRT_HAVE_XSC(setfsgid32)
__CDECLARE_XSC(,__errno_t,setfsgid32,(__uint32_t __gid),(__gid))
#endif /* __CRT_HAVE_XSC(setfsgid32) */
#if __CRT_HAVE_XSC(setfsuid)
__CDECLARE_XSC(,__errno_t,setfsuid,(__uint16_t __uid),(__uid))
#endif /* __CRT_HAVE_XSC(setfsuid) */
#if __CRT_HAVE_XSC(setfsuid32)
__CDECLARE_XSC(,__errno_t,setfsuid32,(__uint32_t __uid),(__uid))
#endif /* __CRT_HAVE_XSC(setfsuid32) */
#if __CRT_HAVE_XSC(setgid)
__CDECLARE_XSC(,__errno_t,setgid,(__uint16_t __gid),(__gid))
#endif /* __CRT_HAVE_XSC(setgid) */
#if __CRT_HAVE_XSC(setgid32)
__CDECLARE_XSC(,__errno_t,setgid32,(__uint32_t __gid),(__gid))
#endif /* __CRT_HAVE_XSC(setgid32) */
#if __CRT_HAVE_XSC(setgroups)
__CDECLARE_XSC(,__errno_t,setgroups,(__size_t __count, __uint16_t const *__groups),(__count,__groups))
#endif /* __CRT_HAVE_XSC(setgroups) */
#if __CRT_HAVE_XSC(setgroups32)
__CDECLARE_XSC(,__errno_t,setgroups32,(__size_t __count, __uint32_t const *__groups),(__count,__groups))
#endif /* __CRT_HAVE_XSC(setgroups32) */
#if __CRT_HAVE_XSC(setitimer64)
__CDECLARE_XSC(,__errno_t,setitimer64,(__syscall_ulong_t __which, struct __itimerval64 const *__newval, struct __itimerval64 *__oldval),(__which,__newval,__oldval))
#endif /* __CRT_HAVE_XSC(setitimer64) */
#if __CRT_HAVE_XSC(setregid)
__CDECLARE_XSC(,__errno_t,setregid,(__uint16_t __rgid, __uint16_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_XSC(setregid) */
#if __CRT_HAVE_XSC(setregid32)
__CDECLARE_XSC(,__errno_t,setregid32,(__uint32_t __rgid, __uint32_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_XSC(setregid32) */
#if __CRT_HAVE_XSC(setresgid)
__CDECLARE_XSC(,__errno_t,setresgid,(__uint16_t __rgid, __uint16_t __egid, __uint16_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_XSC(setresgid) */
#if __CRT_HAVE_XSC(setresgid32)
__CDECLARE_XSC(,__errno_t,setresgid32,(__uint32_t __rgid, __uint32_t __egid, __uint32_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_XSC(setresgid32) */
#if __CRT_HAVE_XSC(setresuid)
__CDECLARE_XSC(,__errno_t,setresuid,(__uint16_t __ruid, __uint16_t __euid, __uint16_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_XSC(setresuid) */
#if __CRT_HAVE_XSC(setresuid32)
__CDECLARE_XSC(,__errno_t,setresuid32,(__uint32_t __ruid, __uint32_t __euid, __uint32_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_XSC(setresuid32) */
#if __CRT_HAVE_XSC(setreuid)
__CDECLARE_XSC(,__errno_t,setreuid,(__uint16_t __ruid, __uint16_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_XSC(setreuid) */
#if __CRT_HAVE_XSC(setreuid32)
__CDECLARE_XSC(,__errno_t,setreuid32,(__uint32_t __ruid, __uint32_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_XSC(setreuid32) */
#if __CRT_HAVE_XSC(settimeofday)
__CDECLARE_XSC(,__errno_t,settimeofday,(struct __timevalx32 const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_XSC(settimeofday) */
#if __CRT_HAVE_XSC(settimeofday64)
__CDECLARE_XSC(,__errno_t,settimeofday64,(struct __timevalx32_64 const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_XSC(settimeofday64) */
#if __CRT_HAVE_XSC(setuid)
__CDECLARE_XSC(,__errno_t,setuid,(__uint16_t __uid),(__uid))
#endif /* __CRT_HAVE_XSC(setuid) */
#if __CRT_HAVE_XSC(setuid32)
__CDECLARE_XSC(,__errno_t,setuid32,(__uint32_t __uid),(__uid))
#endif /* __CRT_HAVE_XSC(setuid32) */
#if __CRT_HAVE_XSC(sgetmask)
__CDECLARE_XSC(,__syscall_ulong_t,sgetmask,(void),())
#endif /* __CRT_HAVE_XSC(sgetmask) */
#if __CRT_HAVE_XSC(sigaction)
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,sigaction,(__syscall_ulong_t __signo, struct sigaction const *__act, struct sigaction *__oact),(__signo,__act,__oact))
#endif /* __CRT_HAVE_XSC(sigaction) */
#if __CRT_HAVE_XSC(signal)
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__sighandler_t,signal,(__syscall_ulong_t __signo, __sighandler_t __handler),(__signo,__handler))
#endif /* __CRT_HAVE_XSC(signal) */
#if __CRT_HAVE_XSC(sigpending)
__CDECLARE_XSC(,__errno_t,sigpending,(struct __sigset_struct *__set),(__set))
#endif /* __CRT_HAVE_XSC(sigpending) */
#if __CRT_HAVE_XSC(sigprocmask)
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE_XSC(,__errno_t,sigprocmask,(__syscall_ulong_t __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),(__how,__set,__oset))
#endif /* __CRT_HAVE_XSC(sigprocmask) */
#if __CRT_HAVE_XSC(sigsuspend)
__CDECLARE_XSC(,__errno_t,sigsuspend,(struct __sigset_struct const *__set),(__set))
#endif /* __CRT_HAVE_XSC(sigsuspend) */
#if __CRT_HAVE_XSC(socketcall)
__CDECLARE_XSC(,__errno_t,socketcall,(int __call, unsigned long *__args),(__call,__args))
#endif /* __CRT_HAVE_XSC(socketcall) */
#if __CRT_HAVE_XSC(ssetmask)
__CDECLARE_XSC(,__syscall_ulong_t,ssetmask,(__syscall_ulong_t __sigmask),(__sigmask))
#endif /* __CRT_HAVE_XSC(ssetmask) */
#if __CRT_HAVE_XSC(statfs64)
__CDECLARE_XSC(,__errno_t,statfs64,(char const *__file, struct statfs64 *__buf),(__file,__buf))
#endif /* __CRT_HAVE_XSC(statfs64) */
#if __CRT_HAVE_XSC(stime)
__CDECLARE_XSC(,__errno_t,stime,(__time32_t const *__t),(__t))
#endif /* __CRT_HAVE_XSC(stime) */
#if __CRT_HAVE_XSC(stime64)
__CDECLARE_XSC(,__errno_t,stime64,(__time64_t const *__t),(__t))
#endif /* __CRT_HAVE_XSC(stime64) */
#if __CRT_HAVE_XSC(stty)
__CDECLARE_XSC(,__errno_t,stty,(void),())
#endif /* __CRT_HAVE_XSC(stty) */
#if __CRT_HAVE_XSC(sysfs)
__CDECLARE_XSC(,__errno_t,sysfs,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(sysfs) */
#if __CRT_HAVE_XSC(time64)
__CDECLARE_XSC(,__time64_t,time64,(__time64_t *__timer),(__timer))
#endif /* __CRT_HAVE_XSC(time64) */
#if __CRT_HAVE_XSC(timer_gettime)
__CDECLARE_XSC(,__errno_t,timer_gettime,(__timer_t __timerid, struct __itimerspecx32 *__value),(__timerid,__value))
#endif /* __CRT_HAVE_XSC(timer_gettime) */
#if __CRT_HAVE_XSC(timer_gettime64)
__CDECLARE_XSC(,__errno_t,timer_gettime64,(__timer_t __timerid, struct __itimerspecx32_64 *__value),(__timerid,__value))
#endif /* __CRT_HAVE_XSC(timer_gettime64) */
#if __CRT_HAVE_XSC(timer_settime)
__CDECLARE_XSC(,__errno_t,timer_settime,(__timer_t __timerid, __syscall_ulong_t __flags, struct __itimerspecx32 const *__value, struct __itimerspecx32 *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* __CRT_HAVE_XSC(timer_settime) */
#if __CRT_HAVE_XSC(timer_settime64)
__CDECLARE_XSC(,__errno_t,timer_settime64,(__timer_t __timerid, __syscall_ulong_t __flags, struct __itimerspecx32_64 const *__value, struct __itimerspecx32_64 *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* __CRT_HAVE_XSC(timer_settime64) */
#if __CRT_HAVE_XSC(timerfd_gettime)
/* Return the next expiration time of UFD */
__CDECLARE_XSC(,__errno_t,timerfd_gettime,(__fd_t __ufd, struct __itimerspecx32 *__otmr),(__ufd,__otmr))
#endif /* __CRT_HAVE_XSC(timerfd_gettime) */
#if __CRT_HAVE_XSC(timerfd_gettime64)
/* Return the next expiration time of UFD */
__CDECLARE_XSC(,__errno_t,timerfd_gettime64,(__fd_t __ufd, struct __itimerspecx32_64 *__otmr),(__ufd,__otmr))
#endif /* __CRT_HAVE_XSC(timerfd_gettime64) */
#if __CRT_HAVE_XSC(timerfd_settime)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_XSC(,__errno_t,timerfd_settime,(__fd_t __ufd, __syscall_ulong_t __flags, struct __itimerspecx32 const *__utmr, struct __itimerspecx32 *__otmr),(__ufd,__flags,__utmr,__otmr))
#endif /* __CRT_HAVE_XSC(timerfd_settime) */
#if __CRT_HAVE_XSC(timerfd_settime64)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_XSC(,__errno_t,timerfd_settime64,(__fd_t __ufd, __syscall_ulong_t __flags, struct __itimerspecx32_64 const *__utmr, struct __itimerspecx32_64 *__otmr),(__ufd,__flags,__utmr,__otmr))
#endif /* __CRT_HAVE_XSC(timerfd_settime64) */
#if __CRT_HAVE_XSC(truncate64)
__CDECLARE_XSC(,__errno_t,truncate64,(char const *__filename, __uint64_t __length),(__filename,__length))
#endif /* __CRT_HAVE_XSC(truncate64) */
#if __CRT_HAVE_XSC(ugetrlimit)
__CDECLARE_XSC(,__errno_t,ugetrlimit,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(ugetrlimit) */
#if __CRT_HAVE_XSC(ulimit)
__CDECLARE_XSC(,__errno_t,ulimit,(void),())
#endif /* __CRT_HAVE_XSC(ulimit) */
#if __CRT_HAVE_XSC(umount)
__CDECLARE_XSC(,__errno_t,umount,(char const *__special_file),(__special_file))
#endif /* __CRT_HAVE_XSC(umount) */
#if __CRT_HAVE_XSC(utime)
__CDECLARE_XSC(,__errno_t,utime,(char const *__filename, struct __utimbuf32 const *__times),(__filename,__times))
#endif /* __CRT_HAVE_XSC(utime) */
#if __CRT_HAVE_XSC(utime64)
__CDECLARE_XSC(,__errno_t,utime64,(char const *__filename, struct __utimbuf64 const *__times),(__filename,__times))
#endif /* __CRT_HAVE_XSC(utime64) */
#if __CRT_HAVE_XSC(utimensat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,utimensat,(__fd_t __dirfd, char const *__filename, struct __timespecx32 const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* __CRT_HAVE_XSC(utimensat) */
#if __CRT_HAVE_XSC(utimensat64)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,utimensat64,(__fd_t __dirfd, char const *__filename, struct __timespecx32_64 const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* __CRT_HAVE_XSC(utimensat64) */
#if __CRT_HAVE_XSC(utimes)
__CDECLARE_XSC(,__errno_t,utimes,(char const *__filename, struct __timevalx32 const *__times),(__filename,__times))
#endif /* __CRT_HAVE_XSC(utimes) */
#if __CRT_HAVE_XSC(utimes64)
__CDECLARE_XSC(,__errno_t,utimes64,(char const *__filename, struct __timevalx32_64 const *__times),(__filename,__times))
#endif /* __CRT_HAVE_XSC(utimes64) */
#if __CRT_HAVE_XSC(vm86)
__CDECLARE_XSC(,__errno_t,vm86,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(vm86) */
#if __CRT_HAVE_XSC(vm86old)
__CDECLARE_XSC(,__errno_t,vm86old,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(vm86old) */
#if __CRT_HAVE_XSC(vmsplice)
__CDECLARE_XSC(,__ssize_t,vmsplice,(__fd_t __fdout, struct iovec32 const *__iov, __size_t __count, __syscall_ulong_t __flags),(__fdout,__iov,__count,__flags))
#endif /* __CRT_HAVE_XSC(vmsplice) */
#if __CRT_HAVE_XSC(vserver)
__CDECLARE_XSC(,__errno_t,vserver,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(vserver) */
#if __CRT_HAVE_XSC(waitid)
/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
__CDECLARE_XSC(,__errno_t,waitid,(__syscall_ulong_t __idtype, __id_t __id, struct __siginfo32_struct *__infop, __syscall_ulong_t __options, struct rusage *__ru),(__idtype,__id,__infop,__options,__ru))
#endif /* __CRT_HAVE_XSC(waitid) */
#if __CRT_HAVE_XSC(waitpid)
/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE_XSC(,__pid_t,waitpid,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options),(__pid,__stat_loc,__options))
#endif /* __CRT_HAVE_XSC(waitpid) */
#if __CRT_HAVE_XSC(writef)
__CDECLARE_XSC(,__ssize_t,writef,(__fd_t __fd, void const *__buf, __size_t __bufsize, __iomode_t __mode),(__fd,__buf,__bufsize,__mode))
#endif /* __CRT_HAVE_XSC(writef) */
#if __CRT_HAVE_XSC(writev)
__CDECLARE_XSC(,__ssize_t,writev,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_XSC(writev) */
#if __CRT_HAVE_XSC(writevf)
__CDECLARE_XSC(,__ssize_t,writevf,(__fd_t __fd, struct iovec32 const *__iovec, __size_t __count, __iomode_t __mode),(__fd,__iovec,__count,__mode))
#endif /* __CRT_HAVE_XSC(writevf) */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("timezone")
#pragma pop_macro("timeb")
#pragma pop_macro("stat")
#pragma pop_macro("dirent")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_I386_KOS_SYSCALLS32_H */
