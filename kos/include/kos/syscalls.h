/* HASH CRC-32:0x9c695183 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_SYSCALL_H
#define _KOS_SYSCALL_H 1

#include <__stdinc.h>
#include <kos/asm/syscall.h>

#include <bits/os/iovec.h>
#include <bits/os/itimerspec.h>
#include <bits/os/itimerval.h>
#include <bits/os/mmsghdr.h>
#include <bits/os/mqueue.h>
#include <bits/os/msghdr.h>
#include <bits/os/pollfd.h>
#include <bits/os/rlimit.h>
#include <bits/os/rusage.h>
#include <bits/os/sigaction.h>
#include <bits/os/sigevent.h>
#include <bits/os/siginfo.h>
#include <bits/os/sigset_with_size.h>
#include <bits/os/sigstack.h>
#include <bits/os/statfs.h>
#include <bits/os/sysinfo.h>
#include <bits/os/timespec.h>
#include <bits/os/timeval.h>
#include <bits/os/timex.h>
#include <bits/os/tms.h>
#include <bits/os/utimbuf.h>
#include <bits/types.h>
#include <kos/compat/linux-dirent.h>
#include <kos/compat/linux-dirent64.h>
#include <kos/compat/linux-stat.h>


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
#ifdef __LCLINT__
#define __CRT_HAVE_SC(name)  1
#define __CRT_HAVE_XSC(name) 1
#else /* __LCLINT__ */
#define __PRIVATE_CRT_HAVE_PLACEHOLDER_ ,
#define __PRIVATE_CRT_HAVE_ARG_IMPL(x, val, ...) val
#define __PRIVATE_CRT_HAVE_ARG(x)  __PRIVATE_CRT_HAVE_ARG_IMPL x
#define __PRIVATE_CRT_HAVE3(...)   __PRIVATE_CRT_HAVE_ARG((__VA_ARGS__ 1,0))
#ifdef __TINYC__
#define __PRIVATE_CRT_ISDEFINED(x) __PRIVATE_CRT_HAVE3(__PRIVATE_CRT_HAVE_PLACEHOLDER_##x)
#else /* __TINYC__ */
#define __PRIVATE_CRT_HAVE2(x)     __PRIVATE_CRT_HAVE3(__PRIVATE_CRT_HAVE_PLACEHOLDER_##x)
#define __PRIVATE_CRT_ISDEFINED(x) __PRIVATE_CRT_HAVE2(x)
#endif /* !__TINYC__ */
#define __CRT_HAVE_SC(name)        __PRIVATE_CRT_ISDEFINED(__CRT_HAVE_sys_##name)
#define __CRT_HAVE_XSC(name)       __PRIVATE_CRT_ISDEFINED(__CRT_HAVE_sys_X##name)
#endif /* !__LCLINT__ */
#endif /* !__CDECLARE_SC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("timezone")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef timezone

struct __cpu_set_struct;
struct __fd_set_struct;
struct __kernel_sigaction;
struct __rlimit64;
struct __siginfo_struct;
struct __sigset_struct;
struct epoll_event;
struct file_handle;
struct getcpu_cache;
struct iovec;
struct itimerspec;
struct itimerval;
struct linux64_stat32;
struct linux_dirent;
struct linux_dirent64;
struct linux_stat;
struct mmsghdr;
struct mq_attr;
struct msghdr;
struct pollfd;
struct rlimit;
struct rusage;
struct sched_param;
struct shmid_ds;
struct sigaltstack;
struct sigevent;
struct sigset_with_size;
struct sockaddr;
struct statfs;
struct sysinfo;
struct timespec;
struct timeval;
struct timex;
struct timezone;
struct tms;
struct ustat;
struct utimbuf;
struct utsname;

#if __CRT_HAVE_SC(_sysctl)
__CDECLARE_SC(,__errno_t,_sysctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(_sysctl) */
#if __CRT_HAVE_SC(accept)
/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The  amount  of required  memory for  the address.
 *                           This  may be  more than  was given,  in which case
 *                           the  address  was  truncated and  may  be invalid.
 *                           If this happens,  the caller  can still  determine
 *                           the correct address through use of `getpeername()'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
__CDECLARE_SC(,__fd_t,accept,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_SC(accept) */
#if __CRT_HAVE_SC(accept4)
/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The  amount  of required  memory for  the address.
 *                            This  may be  more than  was given,  in which case
 *                            the  address  was  truncated and  may  be invalid.
 *                            If this happens,  the caller  can still  determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
__CDECLARE_SC(,__fd_t,accept4,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len, __syscall_ulong_t __sock_flags),(__sockfd,__addr,__addr_len,__sock_flags))
#endif /* __CRT_HAVE_SC(accept4) */
#if __CRT_HAVE_SC(access)
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
__CDECLARE_SC(,__errno_t,access,(char const *__filename, __syscall_ulong_t __type),(__filename,__type))
#endif /* __CRT_HAVE_SC(access) */
#if __CRT_HAVE_SC(acct)
__CDECLARE_SC(,__errno_t,acct,(char const *__filename),(__filename))
#endif /* __CRT_HAVE_SC(acct) */
#if __CRT_HAVE_SC(add_key)
__CDECLARE_SC(,__errno_t,add_key,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(add_key) */
#if __CRT_HAVE_SC(adjtimex)
__CDECLARE_SC(,__errno_t,adjtimex,(struct timex *__ntx),(__ntx))
#endif /* __CRT_HAVE_SC(adjtimex) */
#if __CRT_HAVE_SC(alarm)
__CDECLARE_SC(,__syscall_ulong_t,alarm,(__syscall_ulong_t __seconds),(__seconds))
#endif /* __CRT_HAVE_SC(alarm) */
#if __CRT_HAVE_SC(bdflush)
__CDECLARE_SC(,__errno_t,bdflush,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(bdflush) */
#if __CRT_HAVE_SC(bind)
/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
__CDECLARE_SC(,__errno_t,bind,(__fd_t __sockfd, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_SC(bind) */
#if __CRT_HAVE_SC(bpf)
__CDECLARE_SC(,__errno_t,bpf,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(bpf) */
#if __CRT_HAVE_SC(brk)
__CDECLARE_SC(,__errno_t,brk,(void *__addr),(__addr))
#endif /* __CRT_HAVE_SC(brk) */
#if __CRT_HAVE_SC(capget)
__CDECLARE_SC(,__errno_t,capget,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(capget) */
#if __CRT_HAVE_SC(capset)
__CDECLARE_SC(,__errno_t,capset,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(capset) */
#if __CRT_HAVE_SC(chdir)
__CDECLARE_SC(,__errno_t,chdir,(char const *__path),(__path))
#endif /* __CRT_HAVE_SC(chdir) */
#if __CRT_HAVE_SC(chmod)
__CDECLARE_SC(,__errno_t,chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#endif /* __CRT_HAVE_SC(chmod) */
#if __CRT_HAVE_SC(chown)
__CDECLARE_SC(,__errno_t,chown,(char const *__filename, __uid_t __owner, __gid_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_SC(chown) */
#if __CRT_HAVE_SC(chroot)
__CDECLARE_SC(,__errno_t,chroot,(char const *__path),(__path))
#endif /* __CRT_HAVE_SC(chroot) */
#if __CRT_HAVE_SC(clock_adjtime)
__CDECLARE_SC(,__errno_t,clock_adjtime,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(clock_adjtime) */
#if __CRT_HAVE_SC(clock_getres)
__CDECLARE_SC(,__errno_t,clock_getres,(__clockid_t __clock_id, struct timespec *__res),(__clock_id,__res))
#endif /* __CRT_HAVE_SC(clock_getres) */
#if __CRT_HAVE_SC(clock_gettime)
__CDECLARE_SC(,__errno_t,clock_gettime,(__clockid_t __clock_id, struct timespec *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_SC(clock_gettime) */
#if __CRT_HAVE_SC(clock_nanosleep)
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
__CDECLARE_SC(,__errno_t,clock_nanosleep,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct timespec const *__requested_time, struct timespec *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* __CRT_HAVE_SC(clock_nanosleep) */
#if __CRT_HAVE_SC(clock_settime)
__CDECLARE_SC(,__errno_t,clock_settime,(__clockid_t __clock_id, struct timespec const *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_SC(clock_settime) */
#if __CRT_HAVE_SC(clone)
__CDECLARE_SC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __uintptr_t __newtls, __pid_t *__ctid),(__flags,__child_stack,__ptid,__newtls,__ctid))
#endif /* __CRT_HAVE_SC(clone) */
#if __CRT_HAVE_SC(close)
/* Close a given file descriptor/handle `fd' */
__CDECLARE_SC(,__errno_t,close,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_SC(close) */
#if __CRT_HAVE_SC(connect)
/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that  will implicitly be  used as destination  by `send(2)' and `write(2)'
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_BUFFER_TOO_SMALL   (addr_len is incorrect)
 * @return: 0 : Success */
__CDECLARE_SC(,__errno_t,connect,(__fd_t __sockfd, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_SC(connect) */
#if __CRT_HAVE_SC(creat)
__CDECLARE_SC(,__fd_t,creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#endif /* __CRT_HAVE_SC(creat) */
#if __CRT_HAVE_SC(delete_module)
/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
__CDECLARE_SC(,__errno_t,delete_module,(char const *__name, __oflag_t __flags),(__name,__flags))
#endif /* __CRT_HAVE_SC(delete_module) */
#if __CRT_HAVE_SC(dup)
__CDECLARE_SC(,__fd_t,dup,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_SC(dup) */
#if __CRT_HAVE_SC(dup2)
__CDECLARE_SC(,__fd_t,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#endif /* __CRT_HAVE_SC(dup2) */
#if __CRT_HAVE_SC(dup3)
/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
__CDECLARE_SC(,__fd_t,dup3,(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags),(__oldfd,__newfd,__flags))
#endif /* __CRT_HAVE_SC(dup3) */
#if __CRT_HAVE_SC(epoll_create)
/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_SC(,__fd_t,epoll_create,(__syscall_ulong_t __size),(__size))
#endif /* __CRT_HAVE_SC(epoll_create) */
#if __CRT_HAVE_SC(epoll_create1)
/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
__CDECLARE_SC(,__fd_t,epoll_create1,(__syscall_ulong_t __flags),(__flags))
#endif /* __CRT_HAVE_SC(epoll_create1) */
#if __CRT_HAVE_SC(epoll_ctl)
/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:       One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:       The file descriptor to add/remove/modify
 * @param: info:     The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :      Success
 * @return: -EEXIST: [op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -ENOENT: [op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
__CDECLARE_SC(,__errno_t,epoll_ctl,(__fd_t __epfd, __syscall_ulong_t __op, __fd_t __fd, struct epoll_event *__info),(__epfd,__op,__fd,__info))
#endif /* __CRT_HAVE_SC(epoll_ctl) */
#if __CRT_HAVE_SC(epoll_pwait)
/* >> epoll_pwait(2)
 * Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
 * waiting.  Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @param: ss:        The signal mask to apply while waiting for an event to happen.
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
__CDECLARE_SC(,__ssize_t,epoll_pwait,(__fd_t __epfd, struct epoll_event *__events, __size_t __maxevents, __syscall_slong_t __timeout, struct __sigset_struct const *__ss, __size_t __sigsetsize),(__epfd,__events,__maxevents,__timeout,__ss,__sigsetsize))
#endif /* __CRT_HAVE_SC(epoll_pwait) */
#if __CRT_HAVE_SC(epoll_wait)
/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
__CDECLARE_SC(,__ssize_t,epoll_wait,(__fd_t __epfd, struct epoll_event *__events, __size_t __maxevents, __syscall_slong_t __timeout),(__epfd,__events,__maxevents,__timeout))
#endif /* __CRT_HAVE_SC(epoll_wait) */
#if __CRT_HAVE_SC(eventfd)
__CDECLARE_SC(,__fd_t,eventfd,(__syscall_ulong_t __initval),(__initval))
#endif /* __CRT_HAVE_SC(eventfd) */
#if __CRT_HAVE_SC(eventfd2)
/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
__CDECLARE_SC(,__fd_t,eventfd2,(__syscall_ulong_t __initval, __syscall_ulong_t __flags),(__initval,__flags))
#endif /* __CRT_HAVE_SC(eventfd2) */
#if __CRT_HAVE_SC(execve)
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE_SC(,__errno_t,execve,(char const *__path, char const *const *___argv, char const *const *___envp),(__path,___argv,___envp))
#endif /* __CRT_HAVE_SC(execve) */
#if __CRT_HAVE_SC(execveat)
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,execveat,(__fd_t __dirfd, char const *__pathname, char const *const *___argv, char const *const *___envp, __atflag_t __flags),(__dirfd,__pathname,___argv,___envp,__flags))
#endif /* __CRT_HAVE_SC(execveat) */
#if __CRT_HAVE_SC(exit)
/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
__CDECLARE_VOID_SC(__ATTR_NORETURN,exit,(__syscall_ulong_t __exit_code),(__exit_code))
#endif /* __CRT_HAVE_SC(exit) */
#if __CRT_HAVE_SC(exit_group)
/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
__CDECLARE_VOID_SC(__ATTR_NORETURN,exit_group,(__syscall_ulong_t __exit_code),(__exit_code))
#endif /* __CRT_HAVE_SC(exit_group) */
#if __CRT_HAVE_SC(faccessat)
/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
__CDECLARE_SC(,__errno_t,faccessat,(__fd_t __dirfd, char const *__filename, __syscall_ulong_t __type),(__dirfd,__filename,__type))
#endif /* __CRT_HAVE_SC(faccessat) */
#if __CRT_HAVE_SC(fadvise64)
__CDECLARE_SC(,__errno_t,fadvise64,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(fadvise64) */
#if __CRT_HAVE_SC(fallocate)
/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
__CDECLARE_SC(,__errno_t,fallocate,(__fd_t __fd, __syscall_ulong_t __mode, __syscall_ulong_t __offset, __syscall_ulong_t __length),(__fd,__mode,__offset,__length))
#endif /* __CRT_HAVE_SC(fallocate) */
#if __CRT_HAVE_SC(fanotify_init)
__CDECLARE_SC(,__errno_t,fanotify_init,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(fanotify_init) */
#if __CRT_HAVE_SC(fanotify_mark)
__CDECLARE_SC(,__errno_t,fanotify_mark,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(fanotify_mark) */
#if __CRT_HAVE_SC(fchdir)
__CDECLARE_SC(,__errno_t,fchdir,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_SC(fchdir) */
#if __CRT_HAVE_SC(fchmod)
__CDECLARE_SC(,__errno_t,fchmod,(__fd_t __fd, __mode_t __mode),(__fd,__mode))
#endif /* __CRT_HAVE_SC(fchmod) */
#if __CRT_HAVE_SC(fchmodat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fchmodat,(__fd_t __dirfd, char const *__filename, __mode_t __mode, __atflag_t __flags),(__dirfd,__filename,__mode,__flags))
#endif /* __CRT_HAVE_SC(fchmodat) */
#if __CRT_HAVE_SC(fchown)
__CDECLARE_SC(,__errno_t,fchown,(__fd_t __fd, __uid_t __owner, __gid_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_SC(fchown) */
#if __CRT_HAVE_SC(fchownat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,fchownat,(__fd_t __dirfd, char const *__filename, __uid_t __owner, __gid_t __group, __atflag_t __flags),(__dirfd,__filename,__owner,__group,__flags))
#endif /* __CRT_HAVE_SC(fchownat) */
#if __CRT_HAVE_SC(fcntl)
__CDECLARE_SC(,__syscall_slong_t,fcntl,(__fd_t __fd, __fcntl_t __command, void *__arg),(__fd,__command,__arg))
#endif /* __CRT_HAVE_SC(fcntl) */
#if __CRT_HAVE_SC(fdatasync)
/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CDECLARE_SC(,__errno_t,fdatasync,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_SC(fdatasync) */
#if __CRT_HAVE_SC(fgetxattr)
__CDECLARE_SC(,__ssize_t,fgetxattr,(__fd_t __fd, char const *__name, void *__buf, __size_t __bufsize),(__fd,__name,__buf,__bufsize))
#endif /* __CRT_HAVE_SC(fgetxattr) */
#if __CRT_HAVE_SC(finit_module)
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
__CDECLARE_SC(,__errno_t,finit_module,(__fd_t __fd, char const *__uargs, __syscall_ulong_t __flags),(__fd,__uargs,__flags))
#endif /* __CRT_HAVE_SC(finit_module) */
#if __CRT_HAVE_SC(flistxattr)
__CDECLARE_SC(,__ssize_t,flistxattr,(__fd_t __fd, char *__listbuf, __size_t __listbufsize),(__fd,__listbuf,__listbufsize))
#endif /* __CRT_HAVE_SC(flistxattr) */
#if __CRT_HAVE_SC(flock)
__CDECLARE_SC(,__errno_t,flock,(__fd_t __fd, __syscall_ulong_t __operation),(__fd,__operation))
#endif /* __CRT_HAVE_SC(flock) */
#if __CRT_HAVE_SC(fork)
/* Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
__CDECLARE_SC(,__pid_t,fork,(void),())
#endif /* __CRT_HAVE_SC(fork) */
#if __CRT_HAVE_SC(fremovexattr)
__CDECLARE_SC(,__errno_t,fremovexattr,(__fd_t __fd, char const *__name),(__fd,__name))
#endif /* __CRT_HAVE_SC(fremovexattr) */
#if __CRT_HAVE_SC(fsetxattr)
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
__CDECLARE_SC(,__errno_t,fsetxattr,(__fd_t __fd, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__fd,__name,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_SC(fsetxattr) */
#if __CRT_HAVE_SC(fstat)
__CDECLARE_SC(,__errno_t,fstat,(__fd_t __fd, struct linux_stat *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_SC(fstat) */
#if __CRT_HAVE_SC(fstatfs)
__CDECLARE_SC(,__errno_t,fstatfs,(__fd_t __file, struct statfs *__buf),(__file,__buf))
#endif /* __CRT_HAVE_SC(fstatfs) */
#if __CRT_HAVE_SC(fsync)
/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CDECLARE_SC(,__errno_t,fsync,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_SC(fsync) */
#if __CRT_HAVE_SC(ftruncate)
__CDECLARE_SC(,__errno_t,ftruncate,(__fd_t __fd, __syscall_ulong_t __length),(__fd,__length))
#endif /* __CRT_HAVE_SC(ftruncate) */
#if __CRT_HAVE_SC(futex)
/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
__CDECLARE_SC(,__syscall_slong_t,futex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct timespec const *__timeout_or_val2, __uint32_t *__uaddr2, __uint32_t __val3),(__uaddr,__futex_op,__val,__timeout_or_val2,__uaddr2,__val3))
#endif /* __CRT_HAVE_SC(futex) */
#if __CRT_HAVE_SC(futimesat)
__CDECLARE_SC(,__errno_t,futimesat,(__fd_t __dirfd, char const *__filename, struct timeval const *__times),(__dirfd,__filename,__times))
#endif /* __CRT_HAVE_SC(futimesat) */
#if __CRT_HAVE_SC(get_mempolicy)
__CDECLARE_SC(,__errno_t,get_mempolicy,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(get_mempolicy) */
#if __CRT_HAVE_SC(get_robust_list)
__CDECLARE_SC(,__errno_t,get_robust_list,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(get_robust_list) */
#if __CRT_HAVE_SC(getcpu)
__CDECLARE_SC(,__errno_t,getcpu,(__uint32_t *__cpu, __uint32_t *__node, struct getcpu_cache *__tcache),(__cpu,__node,__tcache))
#endif /* __CRT_HAVE_SC(getcpu) */
#if __CRT_HAVE_SC(getcwd)
__CDECLARE_SC(,__ssize_t,getcwd,(char *__buf, __size_t __size),(__buf,__size))
#endif /* __CRT_HAVE_SC(getcwd) */
#if __CRT_HAVE_SC(getdents)
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
__CDECLARE_SC(,__ssize_t,getdents,(__fd_t __fd, struct linux_dirent *__buf, __size_t __buflen),(__fd,__buf,__buflen))
#endif /* __CRT_HAVE_SC(getdents) */
#if __CRT_HAVE_SC(getdents64)
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
__CDECLARE_SC(,__ssize_t,getdents64,(__fd_t __fd, struct linux_dirent64 *__buf, __size_t __buflen),(__fd,__buf,__buflen))
#endif /* __CRT_HAVE_SC(getdents64) */
#if __CRT_HAVE_SC(getegid)
/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
__CDECLARE_SC(,__gid_t,getegid,(void),())
#endif /* __CRT_HAVE_SC(getegid) */
#if __CRT_HAVE_SC(geteuid)
/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
__CDECLARE_SC(,__uid_t,geteuid,(void),())
#endif /* __CRT_HAVE_SC(geteuid) */
#if __CRT_HAVE_SC(getgid)
/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
__CDECLARE_SC(,__gid_t,getgid,(void),())
#endif /* __CRT_HAVE_SC(getgid) */
#if __CRT_HAVE_SC(getgroups)
/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
__CDECLARE_SC(,__ssize_t,getgroups,(__size_t __count, __gid_t *__list),(__count,__list))
#endif /* __CRT_HAVE_SC(getgroups) */
#if __CRT_HAVE_SC(getitimer)
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
__CDECLARE_SC(,__errno_t,getitimer,(__syscall_ulong_t __which, struct itimerval *__curr_value),(__which,__curr_value))
#endif /* __CRT_HAVE_SC(getitimer) */
#if __CRT_HAVE_SC(getpeername)
/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
__CDECLARE_SC(,__errno_t,getpeername,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_SC(getpeername) */
#if __CRT_HAVE_SC(getpgid)
__CDECLARE_SC(,__pid_t,getpgid,(__pid_t __pid),(__pid))
#endif /* __CRT_HAVE_SC(getpgid) */
#if __CRT_HAVE_SC(getpgrp)
__CDECLARE_SC(,__pid_t,getpgrp,(void),())
#endif /* __CRT_HAVE_SC(getpgrp) */
#if __CRT_HAVE_SC(getpid)
__CDECLARE_SC(,__pid_t,getpid,(void),())
#endif /* __CRT_HAVE_SC(getpid) */
#if __CRT_HAVE_SC(getppid)
__CDECLARE_SC(,__pid_t,getppid,(void),())
#endif /* __CRT_HAVE_SC(getppid) */
#if __CRT_HAVE_SC(getpriority)
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
__CDECLARE_SC(,__syscall_slong_t,getpriority,(__syscall_ulong_t __which, __id_t __who),(__which,__who))
#endif /* __CRT_HAVE_SC(getpriority) */
#if __CRT_HAVE_SC(getrandom)
/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
__CDECLARE_SC(,__ssize_t,getrandom,(void *__buf, __size_t __num_bytes, __syscall_ulong_t __flags),(__buf,__num_bytes,__flags))
#endif /* __CRT_HAVE_SC(getrandom) */
#if __CRT_HAVE_SC(getresgid)
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
__CDECLARE_SC(,__errno_t,getresgid,(__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_SC(getresgid) */
#if __CRT_HAVE_SC(getresuid)
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
__CDECLARE_SC(,__errno_t,getresuid,(__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_SC(getresuid) */
#if __CRT_HAVE_SC(getrlimit)
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
__CDECLARE_SC(,__errno_t,getrlimit,(__syscall_ulong_t __resource, struct rlimit *__rlimits),(__resource,__rlimits))
#endif /* __CRT_HAVE_SC(getrlimit) */
#if __CRT_HAVE_SC(getrusage)
/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
__CDECLARE_SC(,__errno_t,getrusage,(__syscall_slong_t __who, struct rusage *__usage),(__who,__usage))
#endif /* __CRT_HAVE_SC(getrusage) */
#if __CRT_HAVE_SC(getsid)
__CDECLARE_SC(,__pid_t,getsid,(__pid_t __pid),(__pid))
#endif /* __CRT_HAVE_SC(getsid) */
#if __CRT_HAVE_SC(getsockname)
/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This  is usually the  same address as was  previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly  undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * return: 0 : Success */
__CDECLARE_SC(,__errno_t,getsockname,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_SC(getsockname) */
#if __CRT_HAVE_SC(getsockopt)
/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the  contents  of   `optval'  are   undefined.
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
 * @return: 0 : Success */
__CDECLARE_SC(,__errno_t,getsockopt,(__fd_t __sockfd, __syscall_ulong_t __level, __syscall_ulong_t __optname, void *__optval, __socklen_t *__optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* __CRT_HAVE_SC(getsockopt) */
#if __CRT_HAVE_SC(gettid)
__CDECLARE_SC(,__pid_t,gettid,(void),())
#endif /* __CRT_HAVE_SC(gettid) */
#if __CRT_HAVE_SC(gettimeofday)
__CDECLARE_SC(,__errno_t,gettimeofday,(struct timeval *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_SC(gettimeofday) */
#if __CRT_HAVE_SC(getuid)
/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
__CDECLARE_SC(,__uid_t,getuid,(void),())
#endif /* __CRT_HAVE_SC(getuid) */
#if __CRT_HAVE_SC(getxattr)
__CDECLARE_SC(,__ssize_t,getxattr,(char const *__path, char const *__name, void *__buf, __size_t __bufsize),(__path,__name,__buf,__bufsize))
#endif /* __CRT_HAVE_SC(getxattr) */
#if __CRT_HAVE_SC(init_module)
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
__CDECLARE_SC(,__errno_t,init_module,(void const *__module_image, __size_t __len, char const *__uargs),(__module_image,__len,__uargs))
#endif /* __CRT_HAVE_SC(init_module) */
#if __CRT_HAVE_SC(inotify_add_watch)
/* @param: mask: Set of `IN_ALL_EVENTS | ...' */
__CDECLARE_SC(,int,inotify_add_watch,(__fd_t __notify_fd, char const *__pathname, __uint32_t __mask),(__notify_fd,__pathname,__mask))
#endif /* __CRT_HAVE_SC(inotify_add_watch) */
#if __CRT_HAVE_SC(inotify_init)
__CDECLARE_SC(,__fd_t,inotify_init,(void),())
#endif /* __CRT_HAVE_SC(inotify_init) */
#if __CRT_HAVE_SC(inotify_init1)
/* @param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK' */
__CDECLARE_SC(,__fd_t,inotify_init1,(__syscall_ulong_t __flags),(__flags))
#endif /* __CRT_HAVE_SC(inotify_init1) */
#if __CRT_HAVE_SC(inotify_rm_watch)
/* @param: wd: Watch fd (as returned by `inotify_add_watch{_at}') */
__CDECLARE_SC(,__errno_t,inotify_rm_watch,(__fd_t __notify_fd, int __wd),(__notify_fd,__wd))
#endif /* __CRT_HAVE_SC(inotify_rm_watch) */
#if __CRT_HAVE_SC(io_cancel)
__CDECLARE_SC(,__errno_t,io_cancel,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(io_cancel) */
#if __CRT_HAVE_SC(io_destroy)
__CDECLARE_SC(,__errno_t,io_destroy,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(io_destroy) */
#if __CRT_HAVE_SC(io_getevents)
__CDECLARE_SC(,__errno_t,io_getevents,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(io_getevents) */
#if __CRT_HAVE_SC(io_setup)
__CDECLARE_SC(,__errno_t,io_setup,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(io_setup) */
#if __CRT_HAVE_SC(io_submit)
__CDECLARE_SC(,__errno_t,io_submit,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(io_submit) */
#if __CRT_HAVE_SC(ioctl)
__CDECLARE_SC(,__syscall_slong_t,ioctl,(__fd_t __fd, __ioctl_t __command, void *__arg),(__fd,__command,__arg))
#endif /* __CRT_HAVE_SC(ioctl) */
#if __CRT_HAVE_SC(ioprio_get)
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
__CDECLARE_SC(,__syscall_slong_t,ioprio_get,(__syscall_ulong_t __who, __syscall_ulong_t __id),(__who,__id))
#endif /* __CRT_HAVE_SC(ioprio_get) */
#if __CRT_HAVE_SC(ioprio_set)
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
__CDECLARE_SC(,__errno_t,ioprio_set,(__syscall_ulong_t __who, __syscall_ulong_t __id, __syscall_ulong_t __ioprio),(__who,__id,__ioprio))
#endif /* __CRT_HAVE_SC(ioprio_set) */
#if __CRT_HAVE_SC(kcmp)
/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
__CDECLARE_SC(,__syscall_slong_t,kcmp,(__pid_t __pid1, __pid_t __pid2, __syscall_ulong_t __type, __syscall_ulong_t __idx1, __syscall_ulong_t __idx2),(__pid1,__pid2,__type,__idx1,__idx2))
#endif /* __CRT_HAVE_SC(kcmp) */
#if __CRT_HAVE_SC(kexec_load)
__CDECLARE_SC(,__errno_t,kexec_load,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(kexec_load) */
#if __CRT_HAVE_SC(keyctl)
__CDECLARE_SC(,__errno_t,keyctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(keyctl) */
#if __CRT_HAVE_SC(kill)
__CDECLARE_SC(,__errno_t,kill,(__pid_t __pid, __signo_t __signo),(__pid,__signo))
#endif /* __CRT_HAVE_SC(kill) */
#if __CRT_HAVE_SC(lchown)
__CDECLARE_SC(,__errno_t,lchown,(char const *__filename, __uid_t __owner, __gid_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_SC(lchown) */
#if __CRT_HAVE_SC(lgetxattr)
__CDECLARE_SC(,__ssize_t,lgetxattr,(char const *__path, char const *__name, void *__buf, __size_t __bufsize),(__path,__name,__buf,__bufsize))
#endif /* __CRT_HAVE_SC(lgetxattr) */
#if __CRT_HAVE_SC(link)
__CDECLARE_SC(,__errno_t,link,(char const *__existing_file, char const *__link_file),(__existing_file,__link_file))
#endif /* __CRT_HAVE_SC(link) */
#if __CRT_HAVE_SC(linkat)
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,linkat,(__fd_t __fromfd, char const *__existing_file, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__fromfd,__existing_file,__tofd,__target_path,__flags))
#endif /* __CRT_HAVE_SC(linkat) */
#if __CRT_HAVE_SC(listen)
/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
__CDECLARE_SC(,__errno_t,listen,(__fd_t __sockfd, __syscall_ulong_t __max_backlog),(__sockfd,__max_backlog))
#endif /* __CRT_HAVE_SC(listen) */
#if __CRT_HAVE_SC(listxattr)
__CDECLARE_SC(,__ssize_t,listxattr,(char const *__path, char *__listbuf, __size_t __listbufsize),(__path,__listbuf,__listbufsize))
#endif /* __CRT_HAVE_SC(listxattr) */
#if __CRT_HAVE_SC(llistxattr)
__CDECLARE_SC(,__ssize_t,llistxattr,(char const *__path, char *__listbuf, __size_t __listbufsize),(__path,__listbuf,__listbufsize))
#endif /* __CRT_HAVE_SC(llistxattr) */
#if __CRT_HAVE_SC(lookup_dcookie)
__CDECLARE_SC(,__errno_t,lookup_dcookie,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(lookup_dcookie) */
#if __CRT_HAVE_SC(lremovexattr)
__CDECLARE_SC(,__errno_t,lremovexattr,(char const *__path, char const *__name),(__path,__name))
#endif /* __CRT_HAVE_SC(lremovexattr) */
#if __CRT_HAVE_SC(lseek)
__CDECLARE_SC(,__syscall_slong_t,lseek,(__fd_t __fd, __syscall_slong_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* __CRT_HAVE_SC(lseek) */
#if __CRT_HAVE_SC(lsetxattr)
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
__CDECLARE_SC(,__errno_t,lsetxattr,(char const *__path, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__path,__name,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_SC(lsetxattr) */
#if __CRT_HAVE_SC(lstat)
__CDECLARE_SC(,__errno_t,lstat,(char const *__filename, struct linux_stat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(lstat) */
#if __CRT_HAVE_SC(madvise)
__CDECLARE_SC(,__errno_t,madvise,(void *__addr, __size_t __len, __syscall_ulong_t __advice),(__addr,__len,__advice))
#endif /* __CRT_HAVE_SC(madvise) */
#if __CRT_HAVE_SC(mbind)
__CDECLARE_SC(,__errno_t,mbind,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(mbind) */
#if __CRT_HAVE_SC(membarrier)
__CDECLARE_SC(,__errno_t,membarrier,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(membarrier) */
#if __CRT_HAVE_SC(memfd_create)
/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
__CDECLARE_SC(,__fd_t,memfd_create,(char const *__name, __syscall_ulong_t __flags),(__name,__flags))
#endif /* __CRT_HAVE_SC(memfd_create) */
#if __CRT_HAVE_SC(migrate_pages)
__CDECLARE_SC(,__errno_t,migrate_pages,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(migrate_pages) */
#if __CRT_HAVE_SC(mincore)
__CDECLARE_SC(,__errno_t,mincore,(void *__start, __size_t __len, __uint8_t *__vec),(__start,__len,__vec))
#endif /* __CRT_HAVE_SC(mincore) */
#if __CRT_HAVE_SC(mkdir)
__CDECLARE_SC(,__errno_t,mkdir,(char const *__pathname, __mode_t __mode),(__pathname,__mode))
#endif /* __CRT_HAVE_SC(mkdir) */
#if __CRT_HAVE_SC(mkdirat)
__CDECLARE_SC(,__errno_t,mkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode),(__dirfd,__pathname,__mode))
#endif /* __CRT_HAVE_SC(mkdirat) */
#if __CRT_HAVE_SC(mknod)
__CDECLARE_SC(,__errno_t,mknod,(char const *__nodename, __mode_t __mode, __dev_t __dev),(__nodename,__mode,__dev))
#endif /* __CRT_HAVE_SC(mknod) */
#if __CRT_HAVE_SC(mknodat)
__CDECLARE_SC(,__errno_t,mknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev),(__dirfd,__nodename,__mode,__dev))
#endif /* __CRT_HAVE_SC(mknodat) */
#if __CRT_HAVE_SC(mlock)
__CDECLARE_SC(,__errno_t,mlock,(void const *__addr, __size_t __len),(__addr,__len))
#endif /* __CRT_HAVE_SC(mlock) */
#if __CRT_HAVE_SC(mlock2)
__CDECLARE_SC(,__errno_t,mlock2,(void const *__addr, __size_t __length, __syscall_ulong_t __flags),(__addr,__length,__flags))
#endif /* __CRT_HAVE_SC(mlock2) */
#if __CRT_HAVE_SC(mlockall)
/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
__CDECLARE_SC(,__errno_t,mlockall,(__syscall_ulong_t __flags),(__flags))
#endif /* __CRT_HAVE_SC(mlockall) */
#if __CRT_HAVE_SC(mmap)
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED', 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
__CDECLARE_SC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* __CRT_HAVE_SC(mmap) */
#if __CRT_HAVE_SC(mount)
__CDECLARE_SC(,__errno_t,mount,(char const *__special_file, char const *__dir, char const *__fstype, __syscall_ulong_t __mountflags, void const *__data),(__special_file,__dir,__fstype,__mountflags,__data))
#endif /* __CRT_HAVE_SC(mount) */
#if __CRT_HAVE_SC(move_pages)
__CDECLARE_SC(,__errno_t,move_pages,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(move_pages) */
#if __CRT_HAVE_SC(mprotect)
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
__CDECLARE_SC(,__errno_t,mprotect,(void *__addr, __size_t __len, __syscall_ulong_t __prot),(__addr,__len,__prot))
#endif /* __CRT_HAVE_SC(mprotect) */
#if __CRT_HAVE_SC(mq_getsetattr)
__CDECLARE_SC(,__errno_t,mq_getsetattr,(__fd_t __mqdes, struct mq_attr const *__newattr, struct mq_attr *__oldattr),(__mqdes,__newattr,__oldattr))
#endif /* __CRT_HAVE_SC(mq_getsetattr) */
#if __CRT_HAVE_SC(mq_notify)
__CDECLARE_SC(,__errno_t,mq_notify,(__fd_t __mqdes, struct sigevent const *__notification),(__mqdes,__notification))
#endif /* __CRT_HAVE_SC(mq_notify) */
#if __CRT_HAVE_SC(mq_open)
__CDECLARE_SC(,__fd_t,mq_open,(char const *__name, __oflag_t __oflags, __mode_t __mode),(__name,__oflags,__mode))
#endif /* __CRT_HAVE_SC(mq_open) */
#if __CRT_HAVE_SC(mq_timedreceive)
__CDECLARE_SC(,__ssize_t,mq_timedreceive,(__fd_t __mqdes, char *__msg_ptr, __size_t __msg_len, __uint32_t *__pmsg_prio, struct timespec const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#endif /* __CRT_HAVE_SC(mq_timedreceive) */
#if __CRT_HAVE_SC(mq_timedsend)
__CDECLARE_SC(,__errno_t,mq_timedsend,(__fd_t __mqdes, char const *__msg_ptr, __size_t __msg_len, __uint32_t __msg_prio, struct timespec const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#endif /* __CRT_HAVE_SC(mq_timedsend) */
#if __CRT_HAVE_SC(mq_unlink)
__CDECLARE_SC(,__errno_t,mq_unlink,(char const *__name),(__name))
#endif /* __CRT_HAVE_SC(mq_unlink) */
#if __CRT_HAVE_SC(mremap)
/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
__CDECLARE_SC(,void *,mremap,(void *__addr, __size_t __old_len, __size_t __new_len, __syscall_ulong_t __flags, void *__new_address),(__addr,__old_len,__new_len,__flags,__new_address))
#endif /* __CRT_HAVE_SC(mremap) */
#if __CRT_HAVE_SC(msgctl)
__CDECLARE_SC(,__errno_t,msgctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(msgctl) */
#if __CRT_HAVE_SC(msgget)
__CDECLARE_SC(,__errno_t,msgget,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(msgget) */
#if __CRT_HAVE_SC(msgrcv)
__CDECLARE_SC(,__errno_t,msgrcv,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(msgrcv) */
#if __CRT_HAVE_SC(msgsnd)
__CDECLARE_SC(,__errno_t,msgsnd,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(msgsnd) */
#if __CRT_HAVE_SC(msync)
__CDECLARE_SC(,__errno_t,msync,(void *__addr, __size_t __len, __syscall_ulong_t __flags),(__addr,__len,__flags))
#endif /* __CRT_HAVE_SC(msync) */
#if __CRT_HAVE_SC(munlock)
__CDECLARE_SC(,__errno_t,munlock,(void const *__addr, __size_t __len),(__addr,__len))
#endif /* __CRT_HAVE_SC(munlock) */
#if __CRT_HAVE_SC(munlockall)
__CDECLARE_SC(,__errno_t,munlockall,(void),())
#endif /* __CRT_HAVE_SC(munlockall) */
#if __CRT_HAVE_SC(munmap)
__CDECLARE_SC(,__errno_t,munmap,(void *__addr, __size_t __len),(__addr,__len))
#endif /* __CRT_HAVE_SC(munmap) */
#if __CRT_HAVE_SC(name_to_handle_at)
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,name_to_handle_at,(__fd_t __dirfd, char const *__filename, struct file_handle *__handle, __int32_t *__mnt_id, __atflag_t __flags),(__dirfd,__filename,__handle,__mnt_id,__flags))
#endif /* __CRT_HAVE_SC(name_to_handle_at) */
#if __CRT_HAVE_SC(nanosleep)
__CDECLARE_SC(,__errno_t,nanosleep,(struct timespec const *__req, struct timespec *__rem),(__req,__rem))
#endif /* __CRT_HAVE_SC(nanosleep) */
#if __CRT_HAVE_SC(newfstatat)
__CDECLARE_SC(,__errno_t,newfstatat,(__fd_t __dirfd, char const *__filename, struct linux64_stat32 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* __CRT_HAVE_SC(newfstatat) */
#if __CRT_HAVE_SC(nfsservctl)
__CDECLARE_SC(,__errno_t,nfsservctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(nfsservctl) */
#if __CRT_HAVE_SC(oldwait4)
/* @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' */
__CDECLARE_SC(,__pid_t,oldwait4,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options, struct rusage *__usage),(__pid,__stat_loc,__options,__usage))
#endif /* __CRT_HAVE_SC(oldwait4) */
#if __CRT_HAVE_SC(open)
/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CDECLARE_SC(,__fd_t,open,(char const *__filename, __oflag_t __oflags, __mode_t __mode),(__filename,__oflags,__mode))
#endif /* __CRT_HAVE_SC(open) */
#if __CRT_HAVE_SC(open_by_handle_at)
__CDECLARE_SC(,__fd_t,open_by_handle_at,(__fd_t __mountdirfd, struct file_handle const *__handle, __oflag_t __flags),(__mountdirfd,__handle,__flags))
#endif /* __CRT_HAVE_SC(open_by_handle_at) */
#if __CRT_HAVE_SC(openat)
/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CDECLARE_SC(,__fd_t,openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, __mode_t __mode),(__dirfd,__filename,__oflags,__mode))
#endif /* __CRT_HAVE_SC(openat) */
#if __CRT_HAVE_SC(pause)
/* Same as `select(0, NULL, NULL, NULL, NULL)' */
__CDECLARE_SC(,__errno_t,pause,(void),())
#endif /* __CRT_HAVE_SC(pause) */
#if __CRT_HAVE_SC(perf_event_open)
__CDECLARE_SC(,__errno_t,perf_event_open,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(perf_event_open) */
#if __CRT_HAVE_SC(personality)
__CDECLARE_SC(,__errno_t,personality,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(personality) */
#if __CRT_HAVE_SC(pipe)
__CDECLARE_SC(,__errno_t,pipe,(__fd_t *__pipedes),(__pipedes))
#endif /* __CRT_HAVE_SC(pipe) */
#if __CRT_HAVE_SC(pipe2)
__CDECLARE_SC(,__errno_t,pipe2,(__fd_t *__pipedes, __oflag_t __flags),(__pipedes,__flags))
#endif /* __CRT_HAVE_SC(pipe2) */
#if __CRT_HAVE_SC(pivot_root)
__CDECLARE_SC(,__errno_t,pivot_root,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(pivot_root) */
#if __CRT_HAVE_SC(poll)
__CDECLARE_SC(,__ssize_t,poll,(struct pollfd *__fds, __size_t __nfds, __syscall_slong_t __timeout),(__fds,__nfds,__timeout))
#endif /* __CRT_HAVE_SC(poll) */
#if __CRT_HAVE_SC(ppoll)
__CDECLARE_SC(,__ssize_t,ppoll,(struct pollfd *__fds, __size_t __nfds, struct timespec const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* __CRT_HAVE_SC(ppoll) */
#if __CRT_HAVE_SC(prctl)
/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... : Up  to 4 additional arguments (dependent on `command')
 *               Note that some control codes  require you to pass  `0'
 *               for  all seemingly "unused" arguments. In these cases,
 *               the documentation for that command includes the number
 *               of unused, but required trailing 0s in its comment.
 * @return: * :  Return value depends on `command' */
__CDECLARE_SC(,__syscall_slong_t,prctl,(unsigned int __command, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5),(__command,__arg2,__arg3,__arg4,__arg5))
#endif /* __CRT_HAVE_SC(prctl) */
#if __CRT_HAVE_SC(pread64)
__CDECLARE_SC(,__ssize_t,pread64,(__fd_t __fd, void *__buf, __size_t __bufsize, __uint64_t __offset),(__fd,__buf,__bufsize,__offset))
#endif /* __CRT_HAVE_SC(pread64) */
#if __CRT_HAVE_SC(preadv)
/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__CDECLARE_SC(,__ssize_t,preadv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_SC(preadv) */
#if __CRT_HAVE_SC(prlimit64)
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
__CDECLARE_SC(,__errno_t,prlimit64,(__pid_t __pid, __syscall_ulong_t __resource, struct __rlimit64 const *__new_limit, struct __rlimit64 *__old_limit),(__pid,__resource,__new_limit,__old_limit))
#endif /* __CRT_HAVE_SC(prlimit64) */
#if __CRT_HAVE_SC(process_vm_readv)
/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
__CDECLARE_SC(,__ssize_t,process_vm_readv,(__pid_t __pid, struct iovec const *__local_iov, __size_t __liovcnt, struct iovec const *__remote_iov, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__local_iov,__liovcnt,__remote_iov,__riovcnt,__flags))
#endif /* __CRT_HAVE_SC(process_vm_readv) */
#if __CRT_HAVE_SC(process_vm_writev)
/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
__CDECLARE_SC(,__ssize_t,process_vm_writev,(__pid_t __pid, struct iovec const *__local_iov, __size_t __liovcnt, struct iovec const *__remote_iov, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__local_iov,__liovcnt,__remote_iov,__riovcnt,__flags))
#endif /* __CRT_HAVE_SC(process_vm_writev) */
#if __CRT_HAVE_SC(pselect6)
__CDECLARE_SC(,__ssize_t,pselect6,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct timespec const *__timeout, struct sigset_with_size const *__sigmask_sigset_with_size),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_with_size))
#endif /* __CRT_HAVE_SC(pselect6) */
#if __CRT_HAVE_SC(ptrace)
__CDECLARE_SC(,__syscall_slong_t,ptrace,(__syscall_ulong_t __request, __pid_t __pid, void *__addr, void *__data),(__request,__pid,__addr,__data))
#endif /* __CRT_HAVE_SC(ptrace) */
#if __CRT_HAVE_SC(pwrite64)
__CDECLARE_SC(,__ssize_t,pwrite64,(__fd_t __fd, void const *__buf, __size_t __bufsize, __uint64_t __offset),(__fd,__buf,__bufsize,__offset))
#endif /* __CRT_HAVE_SC(pwrite64) */
#if __CRT_HAVE_SC(pwritev)
/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
__CDECLARE_SC(,__ssize_t,pwritev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_SC(pwritev) */
#if __CRT_HAVE_SC(quotactl)
__CDECLARE_SC(,__errno_t,quotactl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(quotactl) */
#if __CRT_HAVE_SC(read)
/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CDECLARE_SC(,__ssize_t,read,(__fd_t __fd, void *__buf, __size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* __CRT_HAVE_SC(read) */
#if __CRT_HAVE_SC(readahead)
__CDECLARE_SC(,__ssize_t,readahead,(__fd_t __fd, __uint64_t __offset, __size_t __count),(__fd,__offset,__count))
#endif /* __CRT_HAVE_SC(readahead) */
#if __CRT_HAVE_SC(readlink)
__CDECLARE_SC(,__ssize_t,readlink,(char const *__path, char *__buf, __size_t __buflen),(__path,__buf,__buflen))
#endif /* __CRT_HAVE_SC(readlink) */
#if __CRT_HAVE_SC(readlinkat)
__CDECLARE_SC(,__ssize_t,readlinkat,(__fd_t __dirfd, char const *__path, char *__buf, __size_t __buflen),(__dirfd,__path,__buf,__buflen))
#endif /* __CRT_HAVE_SC(readlinkat) */
#if __CRT_HAVE_SC(readv)
/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
__CDECLARE_SC(,__ssize_t,readv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_SC(readv) */
#if __CRT_HAVE_SC(reboot)
/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
__CDECLARE_SC(,__errno_t,reboot,(__syscall_ulong_t __how),(__how))
#endif /* __CRT_HAVE_SC(reboot) */
#if __CRT_HAVE_SC(recv)
/* Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @return: * : [<= bufsize] The actual # of received bytes */
__CDECLARE_SC(,__ssize_t,recv,(__fd_t __sockfd, void *__buf, __size_t __bufsize, __syscall_ulong_t __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
#endif /* __CRT_HAVE_SC(recv) */
#if __CRT_HAVE_SC(recvfrom)
/* Receive data over this socket, and store the contents within the given buffer.
 * @param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
 * @param: bufsize:   Max # of bytes to receive
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked)
 * @return: * : [<= bufsize] The actual # of received bytes */
__CDECLARE_SC(,__ssize_t,recvfrom,(__fd_t __sockfd, void *__buf, __size_t __bufsize, __syscall_ulong_t __msg_flags, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
#endif /* __CRT_HAVE_SC(recvfrom) */
#if __CRT_HAVE_SC(recvmmsg)
/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
__CDECLARE_SC(,__ssize_t,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __msg_flags, struct timespec const *__tmo),(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#endif /* __CRT_HAVE_SC(recvmmsg) */
#if __CRT_HAVE_SC(recvmsg)
/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
__CDECLARE_SC(,__ssize_t,recvmsg,(__fd_t __sockfd, struct msghdr *__message, __syscall_ulong_t __msg_flags),(__sockfd,__message,__msg_flags))
#endif /* __CRT_HAVE_SC(recvmsg) */
#if __CRT_HAVE_SC(remap_file_pages)
__CDECLARE_SC(,__errno_t,remap_file_pages,(void *__start, __size_t __size, __syscall_ulong_t __prot, __size_t __pgoff, __syscall_ulong_t __flags),(__start,__size,__prot,__pgoff,__flags))
#endif /* __CRT_HAVE_SC(remap_file_pages) */
#if __CRT_HAVE_SC(removexattr)
__CDECLARE_SC(,__errno_t,removexattr,(char const *__path, char const *__name),(__path,__name))
#endif /* __CRT_HAVE_SC(removexattr) */
#if __CRT_HAVE_SC(rename)
__CDECLARE_SC(,__errno_t,rename,(char const *__oldname, char const *__newname_or_path),(__oldname,__newname_or_path))
#endif /* __CRT_HAVE_SC(rename) */
#if __CRT_HAVE_SC(renameat)
__CDECLARE_SC(,__errno_t,renameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path),(__oldfd,__oldname,__newfd,__newname_or_path))
#endif /* __CRT_HAVE_SC(renameat) */
#if __CRT_HAVE_SC(renameat2)
/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,renameat2,(__fd_t __olddirfd, char const *__oldpath, __fd_t __newdirfd, char const *__newpath, __atflag_t __flags),(__olddirfd,__oldpath,__newdirfd,__newpath,__flags))
#endif /* __CRT_HAVE_SC(renameat2) */
#if __CRT_HAVE_SC(request_key)
__CDECLARE_SC(,__errno_t,request_key,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(request_key) */
#if __CRT_HAVE_SC(restart_syscall)
__CDECLARE_SC(,__errno_t,restart_syscall,(void),())
#endif /* __CRT_HAVE_SC(restart_syscall) */
#if __CRT_HAVE_SC(rmdir)
__CDECLARE_SC(,__errno_t,rmdir,(char const *__path),(__path))
#endif /* __CRT_HAVE_SC(rmdir) */
#if __CRT_HAVE_SC(rt_sigaction)
__CDECLARE_SC(,__errno_t,rt_sigaction,(__signo_t __signo, struct __kernel_sigaction const *__act, struct __kernel_sigaction *__oact, __size_t __sigsetsize),(__signo,__act,__oact,__sigsetsize))
#endif /* __CRT_HAVE_SC(rt_sigaction) */
#if __CRT_HAVE_SC(rt_sigpending)
__CDECLARE_SC(,__errno_t,rt_sigpending,(struct __sigset_struct *__set, __size_t __sigsetsize),(__set,__sigsetsize))
#endif /* __CRT_HAVE_SC(rt_sigpending) */
#if __CRT_HAVE_SC(rt_sigprocmask)
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE_SC(,__errno_t,rt_sigprocmask,(__syscall_ulong_t __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset, __size_t __sigsetsize),(__how,__set,__oset,__sigsetsize))
#endif /* __CRT_HAVE_SC(rt_sigprocmask) */
#if __CRT_HAVE_SC(rt_sigqueueinfo)
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
__CDECLARE_SC(,__errno_t,rt_sigqueueinfo,(__pid_t __pid, __signo_t __usigno, struct __siginfo_struct const *__uinfo),(__pid,__usigno,__uinfo))
#endif /* __CRT_HAVE_SC(rt_sigqueueinfo) */
#if __CRT_HAVE_SC(rt_sigreturn)
__CDECLARE_VOID_SC(,rt_sigreturn,(void),())
#endif /* __CRT_HAVE_SC(rt_sigreturn) */
#if __CRT_HAVE_SC(rt_sigsuspend)
/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__CDECLARE_SC(,__errno_t,rt_sigsuspend,(struct __sigset_struct const *__set, __size_t __sigsetsize),(__set,__sigsetsize))
#endif /* __CRT_HAVE_SC(rt_sigsuspend) */
#if __CRT_HAVE_SC(rt_sigtimedwait)
__CDECLARE_SC(,__syscall_slong_t,rt_sigtimedwait,(struct __sigset_struct const *__set, struct __siginfo_struct *__info, struct timespec const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* __CRT_HAVE_SC(rt_sigtimedwait) */
#if __CRT_HAVE_SC(rt_tgsigqueueinfo)
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
__CDECLARE_SC(,__errno_t,rt_tgsigqueueinfo,(__pid_t __pid, __pid_t __tid, __signo_t __usigno, struct __siginfo_struct const *__uinfo),(__pid,__tid,__usigno,__uinfo))
#endif /* __CRT_HAVE_SC(rt_tgsigqueueinfo) */
#if __CRT_HAVE_SC(sched_get_priority_max)
__CDECLARE_SC(,__syscall_slong_t,sched_get_priority_max,(__syscall_ulong_t __algorithm),(__algorithm))
#endif /* __CRT_HAVE_SC(sched_get_priority_max) */
#if __CRT_HAVE_SC(sched_get_priority_min)
__CDECLARE_SC(,__syscall_slong_t,sched_get_priority_min,(__syscall_ulong_t __algorithm),(__algorithm))
#endif /* __CRT_HAVE_SC(sched_get_priority_min) */
#if __CRT_HAVE_SC(sched_getaffinity)
__CDECLARE_SC(,__errno_t,sched_getaffinity,(__pid_t __pid, __size_t __cpusetsize, struct __cpu_set_struct *__cpuset),(__pid,__cpusetsize,__cpuset))
#endif /* __CRT_HAVE_SC(sched_getaffinity) */
#if __CRT_HAVE_SC(sched_getattr)
__CDECLARE_SC(,__errno_t,sched_getattr,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(sched_getattr) */
#if __CRT_HAVE_SC(sched_getparam)
__CDECLARE_SC(,__errno_t,sched_getparam,(__pid_t __pid, struct sched_param *__param),(__pid,__param))
#endif /* __CRT_HAVE_SC(sched_getparam) */
#if __CRT_HAVE_SC(sched_getscheduler)
__CDECLARE_SC(,__syscall_slong_t,sched_getscheduler,(__pid_t __pid),(__pid))
#endif /* __CRT_HAVE_SC(sched_getscheduler) */
#if __CRT_HAVE_SC(sched_rr_get_interval)
__CDECLARE_SC(,__errno_t,sched_rr_get_interval,(__pid_t __pid, struct timespec *__ts),(__pid,__ts))
#endif /* __CRT_HAVE_SC(sched_rr_get_interval) */
#if __CRT_HAVE_SC(sched_setaffinity)
__CDECLARE_SC(,__errno_t,sched_setaffinity,(__pid_t __pid, __size_t __cpusetsize, struct __cpu_set_struct const *__cpuset),(__pid,__cpusetsize,__cpuset))
#endif /* __CRT_HAVE_SC(sched_setaffinity) */
#if __CRT_HAVE_SC(sched_setattr)
__CDECLARE_SC(,__errno_t,sched_setattr,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(sched_setattr) */
#if __CRT_HAVE_SC(sched_setparam)
__CDECLARE_SC(,__errno_t,sched_setparam,(__pid_t __pid, struct sched_param const *__param),(__pid,__param))
#endif /* __CRT_HAVE_SC(sched_setparam) */
#if __CRT_HAVE_SC(sched_setscheduler)
/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
__CDECLARE_SC(,__errno_t,sched_setscheduler,(__pid_t __pid, __syscall_ulong_t __policy, struct sched_param const *__param),(__pid,__policy,__param))
#endif /* __CRT_HAVE_SC(sched_setscheduler) */
#if __CRT_HAVE_SC(sched_yield)
__CDECLARE_SC(,__errno_t,sched_yield,(void),())
#endif /* __CRT_HAVE_SC(sched_yield) */
#if __CRT_HAVE_SC(seccomp)
__CDECLARE_SC(,__errno_t,seccomp,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(seccomp) */
#if __CRT_HAVE_SC(select)
__CDECLARE_SC(,__ssize_t,select,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct timeval *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* __CRT_HAVE_SC(select) */
#if __CRT_HAVE_SC(semctl)
__CDECLARE_SC(,__errno_t,semctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(semctl) */
#if __CRT_HAVE_SC(semget)
__CDECLARE_SC(,__errno_t,semget,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(semget) */
#if __CRT_HAVE_SC(semop)
__CDECLARE_SC(,__errno_t,semop,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(semop) */
#if __CRT_HAVE_SC(semtimedop)
__CDECLARE_SC(,__errno_t,semtimedop,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(semtimedop) */
#if __CRT_HAVE_SC(send)
/* Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @return: * : [<= bufsize] The actual # of send bytes */
__CDECLARE_SC(,__ssize_t,send,(__fd_t __sockfd, void const *__buf, __size_t __bufsize, __syscall_ulong_t __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
#endif /* __CRT_HAVE_SC(send) */
#if __CRT_HAVE_SC(sendfile)
/* Read up to `num_bytes' from `infd', and write that data to `outfd'
 * Files must be opened with the relevant access permissions (same as
 * would be enforced by `read(2)' and `write(2)')
 * When `pin_offset != NULL', the pointed-to location is used to track
 * the read-position in `infd'. Note that in the event that writing to
 * this address faults, data may  have still been written to  `outfd',
 * so be sure to have this point to writable memory.
 * @param: outfd:      Output file descriptor
 * @param: infd:       Input file descriptor
 * @param: pin_offset: If non-NULL, position from which to start reading,
 *                     and updated to reflect  how much could be  copied.
 * @param: num_bytes:  The max number of bytes to transfer
 * @return: * :        The actual number of bytes transferred */
__CDECLARE_SC(,__ssize_t,sendfile,(__fd_t __outfd, __fd_t __infd, __syscall_ulong_t *__pin_offset, __size_t __num_bytes),(__outfd,__infd,__pin_offset,__num_bytes))
#endif /* __CRT_HAVE_SC(sendfile) */
#if __CRT_HAVE_SC(sendmmsg)
/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
__CDECLARE_SC(,__ssize_t,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __msg_flags),(__sockfd,__vmessages,__vlen,__msg_flags))
#endif /* __CRT_HAVE_SC(sendmmsg) */
#if __CRT_HAVE_SC(sendmsg)
/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
__CDECLARE_SC(,__ssize_t,sendmsg,(__fd_t __sockfd, struct msghdr const *__message, __syscall_ulong_t __msg_flags),(__sockfd,__message,__msg_flags))
#endif /* __CRT_HAVE_SC(sendmsg) */
#if __CRT_HAVE_SC(sendto)
/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for            `send(sockfd, buf, bufsize, msg_flags)'
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @throw: E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
 * @return: * : [<= bufsize] The actual # of send bytes */
__CDECLARE_SC(,__ssize_t,sendto,(__fd_t __sockfd, void const *__buf, __size_t __bufsize, __syscall_ulong_t __msg_flags, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
#endif /* __CRT_HAVE_SC(sendto) */
#if __CRT_HAVE_SC(set_mempolicy)
__CDECLARE_SC(,__errno_t,set_mempolicy,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(set_mempolicy) */
#if __CRT_HAVE_SC(set_robust_list)
__CDECLARE_SC(,__errno_t,set_robust_list,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(set_robust_list) */
#if __CRT_HAVE_SC(set_tid_address)
__CDECLARE_SC(,__pid_t,set_tid_address,(__pid_t *__tidptr),(__tidptr))
#endif /* __CRT_HAVE_SC(set_tid_address) */
#if __CRT_HAVE_SC(setdomainname)
__CDECLARE_SC(,__errno_t,setdomainname,(char const *__name, __size_t __len),(__name,__len))
#endif /* __CRT_HAVE_SC(setdomainname) */
#if __CRT_HAVE_SC(setfsgid)
/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
__CDECLARE_SC(,__errno_t,setfsgid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_SC(setfsgid) */
#if __CRT_HAVE_SC(setfsuid)
/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
__CDECLARE_SC(,__errno_t,setfsuid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_SC(setfsuid) */
#if __CRT_HAVE_SC(setgid)
/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
__CDECLARE_SC(,__errno_t,setgid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_SC(setgid) */
#if __CRT_HAVE_SC(setgroups)
__CDECLARE_SC(,__errno_t,setgroups,(__size_t __count, __gid_t const *__groups),(__count,__groups))
#endif /* __CRT_HAVE_SC(setgroups) */
#if __CRT_HAVE_SC(sethostname)
__CDECLARE_SC(,__errno_t,sethostname,(char const *__name, __size_t __len),(__name,__len))
#endif /* __CRT_HAVE_SC(sethostname) */
#if __CRT_HAVE_SC(setitimer)
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
__CDECLARE_SC(,__errno_t,setitimer,(__syscall_ulong_t __which, struct itimerval const *__newval, struct itimerval *__oldval),(__which,__newval,__oldval))
#endif /* __CRT_HAVE_SC(setitimer) */
#if __CRT_HAVE_SC(setns)
__CDECLARE_SC(,__errno_t,setns,(__fd_t __fd, __syscall_ulong_t __nstype),(__fd,__nstype))
#endif /* __CRT_HAVE_SC(setns) */
#if __CRT_HAVE_SC(setpgid)
__CDECLARE_SC(,__errno_t,setpgid,(__pid_t __pid, __pid_t __pgid),(__pid,__pgid))
#endif /* __CRT_HAVE_SC(setpgid) */
#if __CRT_HAVE_SC(setpriority)
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
__CDECLARE_SC(,__errno_t,setpriority,(__syscall_ulong_t __which, __id_t __who, __syscall_ulong_t __value),(__which,__who,__value))
#endif /* __CRT_HAVE_SC(setpriority) */
#if __CRT_HAVE_SC(setregid)
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
__CDECLARE_SC(,__errno_t,setregid,(__gid_t __rgid, __gid_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_SC(setregid) */
#if __CRT_HAVE_SC(setresgid)
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
__CDECLARE_SC(,__errno_t,setresgid,(__gid_t __rgid, __gid_t __egid, __gid_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_SC(setresgid) */
#if __CRT_HAVE_SC(setresuid)
/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
__CDECLARE_SC(,__errno_t,setresuid,(__uid_t __ruid, __uid_t __euid, __uid_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_SC(setresuid) */
#if __CRT_HAVE_SC(setreuid)
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
__CDECLARE_SC(,__errno_t,setreuid,(__uid_t __ruid, __uid_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_SC(setreuid) */
#if __CRT_HAVE_SC(setrlimit)
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
__CDECLARE_SC(,__errno_t,setrlimit,(__syscall_ulong_t __resource, struct rlimit const *__rlimits),(__resource,__rlimits))
#endif /* __CRT_HAVE_SC(setrlimit) */
#if __CRT_HAVE_SC(setsid)
__CDECLARE_SC(,__pid_t,setsid,(void),())
#endif /* __CRT_HAVE_SC(setsid) */
#if __CRT_HAVE_SC(setsockopt)
/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
__CDECLARE_SC(,__errno_t,setsockopt,(__fd_t __sockfd, __syscall_ulong_t __level, __syscall_ulong_t __optname, void const *__optval, __socklen_t __optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* __CRT_HAVE_SC(setsockopt) */
#if __CRT_HAVE_SC(settimeofday)
__CDECLARE_SC(,__errno_t,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_SC(settimeofday) */
#if __CRT_HAVE_SC(setuid)
/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
__CDECLARE_SC(,__errno_t,setuid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_SC(setuid) */
#if __CRT_HAVE_SC(setxattr)
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
__CDECLARE_SC(,__errno_t,setxattr,(char const *__path, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__path,__name,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_SC(setxattr) */
#if __CRT_HAVE_SC(shmat)
__CDECLARE_SC(,__errno_t,shmat,(__syscall_ulong_t __shmid, void const *__shmaddr, __syscall_ulong_t __shmflg),(__shmid,__shmaddr,__shmflg))
#endif /* __CRT_HAVE_SC(shmat) */
#if __CRT_HAVE_SC(shmctl)
__CDECLARE_SC(,__errno_t,shmctl,(__syscall_ulong_t __shmid, __syscall_ulong_t __cmd, struct shmid_ds *__buf),(__shmid,__cmd,__buf))
#endif /* __CRT_HAVE_SC(shmctl) */
#if __CRT_HAVE_SC(shmdt)
__CDECLARE_SC(,__errno_t,shmdt,(void const *__shmaddr),(__shmaddr))
#endif /* __CRT_HAVE_SC(shmdt) */
#if __CRT_HAVE_SC(shmget)
__CDECLARE_SC(,__errno_t,shmget,(__key_t __key, __size_t __size, __syscall_ulong_t __shmflg),(__key,__size,__shmflg))
#endif /* __CRT_HAVE_SC(shmget) */
#if __CRT_HAVE_SC(shutdown)
/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
__CDECLARE_SC(,__errno_t,shutdown,(__fd_t __sockfd, __syscall_ulong_t __how),(__sockfd,__how))
#endif /* __CRT_HAVE_SC(shutdown) */
#if __CRT_HAVE_SC(sigaltstack)
__CDECLARE_SC(,__errno_t,sigaltstack,(struct sigaltstack const *__ss, struct sigaltstack *__oss),(__ss,__oss))
#endif /* __CRT_HAVE_SC(sigaltstack) */
#if __CRT_HAVE_SC(signalfd)
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
__CDECLARE_SC(,__errno_t,signalfd,(__fd_t __fd, struct __sigset_struct const *__sigmask, __size_t __sigmasksize),(__fd,__sigmask,__sigmasksize))
#endif /* __CRT_HAVE_SC(signalfd) */
#if __CRT_HAVE_SC(signalfd4)
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
__CDECLARE_SC(,__errno_t,signalfd4,(__fd_t __fd, struct __sigset_struct const *__sigmask, __size_t __sigmasksize, __syscall_ulong_t __flags),(__fd,__sigmask,__sigmasksize,__flags))
#endif /* __CRT_HAVE_SC(signalfd4) */
#if __CRT_HAVE_SC(socket)
/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
__CDECLARE_SC(,__fd_t,socket,(__syscall_ulong_t __domain, __syscall_ulong_t __type, __syscall_ulong_t __protocol),(__domain,__type,__protocol))
#endif /* __CRT_HAVE_SC(socket) */
#if __CRT_HAVE_SC(socketpair)
/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
__CDECLARE_SC(,__errno_t,socketpair,(__syscall_ulong_t __domain, __syscall_ulong_t __type, __syscall_ulong_t __protocol, __fd_t *__fds),(__domain,__type,__protocol,__fds))
#endif /* __CRT_HAVE_SC(socketpair) */
#if __CRT_HAVE_SC(splice)
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
__CDECLARE_SC(,__ssize_t,splice,(__fd_t __fdin, __uint64_t *__offin, __fd_t __fdout, __uint64_t *__offout, __size_t __length, __syscall_ulong_t __flags),(__fdin,__offin,__fdout,__offout,__length,__flags))
#endif /* __CRT_HAVE_SC(splice) */
#if __CRT_HAVE_SC(stat)
__CDECLARE_SC(,__errno_t,stat,(char const *__filename, struct linux_stat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(stat) */
#if __CRT_HAVE_SC(statfs)
__CDECLARE_SC(,__errno_t,statfs,(char const *__file, struct statfs *__buf),(__file,__buf))
#endif /* __CRT_HAVE_SC(statfs) */
#if __CRT_HAVE_SC(swapoff)
__CDECLARE_SC(,__errno_t,swapoff,(char const *__pathname),(__pathname))
#endif /* __CRT_HAVE_SC(swapoff) */
#if __CRT_HAVE_SC(swapon)
/* @param: swapflags: Set of `SWAP_FLAG_*' */
__CDECLARE_SC(,__errno_t,swapon,(char const *__pathname, __syscall_ulong_t __swapflags),(__pathname,__swapflags))
#endif /* __CRT_HAVE_SC(swapon) */
#if __CRT_HAVE_SC(symlink)
__CDECLARE_SC(,__errno_t,symlink,(char const *__link_text, char const *__target_path),(__link_text,__target_path))
#endif /* __CRT_HAVE_SC(symlink) */
#if __CRT_HAVE_SC(symlinkat)
__CDECLARE_SC(,__errno_t,symlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path),(__link_text,__tofd,__target_path))
#endif /* __CRT_HAVE_SC(symlinkat) */
#if __CRT_HAVE_SC(sync)
__CDECLARE_SC(,__errno_t,sync,(void),())
#endif /* __CRT_HAVE_SC(sync) */
#if __CRT_HAVE_SC(sync_file_range)
/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
__CDECLARE_SC(,__errno_t,sync_file_range,(__fd_t __fd, __uint64_t __offset, __uint64_t __count, __syscall_ulong_t __flags),(__fd,__offset,__count,__flags))
#endif /* __CRT_HAVE_SC(sync_file_range) */
#if __CRT_HAVE_SC(syncfs)
__CDECLARE_SC(,__errno_t,syncfs,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_SC(syncfs) */
#if __CRT_HAVE_SC(sysinfo)
__CDECLARE_SC(,__errno_t,sysinfo,(struct sysinfo *__info),(__info))
#endif /* __CRT_HAVE_SC(sysinfo) */
#if __CRT_HAVE_SC(syslog)
__CDECLARE_SC(,__ssize_t,syslog,(__syscall_ulong_t __level, char const *__str, __size_t __len),(__level,__str,__len))
#endif /* __CRT_HAVE_SC(syslog) */
#if __CRT_HAVE_SC(tee)
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
__CDECLARE_SC(,__ssize_t,tee,(__fd_t __fdin, __fd_t __fdout, __size_t __length, __syscall_ulong_t __flags),(__fdin,__fdout,__length,__flags))
#endif /* __CRT_HAVE_SC(tee) */
#if __CRT_HAVE_SC(tgkill)
__CDECLARE_SC(,__errno_t,tgkill,(__pid_t __pid, __pid_t __tid, __signo_t __signo),(__pid,__tid,__signo))
#endif /* __CRT_HAVE_SC(tgkill) */
#if __CRT_HAVE_SC(time)
__CDECLARE_SC(,__time32_t,time,(__time32_t *__timer),(__timer))
#endif /* __CRT_HAVE_SC(time) */
#if __CRT_HAVE_SC(timer_create)
__CDECLARE_SC(,__errno_t,timer_create,(__clockid_t __clock_id, struct sigevent *__evp, __timer_t *__timerid),(__clock_id,__evp,__timerid))
#endif /* __CRT_HAVE_SC(timer_create) */
#if __CRT_HAVE_SC(timer_delete)
__CDECLARE_SC(,__errno_t,timer_delete,(__timer_t __timerid),(__timerid))
#endif /* __CRT_HAVE_SC(timer_delete) */
#if __CRT_HAVE_SC(timer_getoverrun)
__CDECLARE_SC(,__syscall_slong_t,timer_getoverrun,(__timer_t __timerid),(__timerid))
#endif /* __CRT_HAVE_SC(timer_getoverrun) */
#if __CRT_HAVE_SC(timer_gettime)
__CDECLARE_SC(,__errno_t,timer_gettime,(__timer_t __timerid, struct itimerspec *__value),(__timerid,__value))
#endif /* __CRT_HAVE_SC(timer_gettime) */
#if __CRT_HAVE_SC(timer_settime)
/* @param: flags: Set of `0 | TIMER_ABSTIME' */
__CDECLARE_SC(,__errno_t,timer_settime,(__timer_t __timerid, __syscall_ulong_t __flags, struct itimerspec const *__value, struct itimerspec *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* __CRT_HAVE_SC(timer_settime) */
#if __CRT_HAVE_SC(timerfd_create)
/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
__CDECLARE_SC(,__fd_t,timerfd_create,(__clockid_t __clock_id, __syscall_ulong_t __flags),(__clock_id,__flags))
#endif /* __CRT_HAVE_SC(timerfd_create) */
#if __CRT_HAVE_SC(timerfd_gettime)
/* Return the next expiration time of UFD */
__CDECLARE_SC(,__errno_t,timerfd_gettime,(__fd_t __timerfd, struct itimerspec *__otmr),(__timerfd,__otmr))
#endif /* __CRT_HAVE_SC(timerfd_gettime) */
#if __CRT_HAVE_SC(timerfd_settime)
/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
__CDECLARE_SC(,__errno_t,timerfd_settime,(__fd_t __timerfd, __syscall_ulong_t __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr),(__timerfd,__flags,__utmr,__otmr))
#endif /* __CRT_HAVE_SC(timerfd_settime) */
#if __CRT_HAVE_SC(times)
__CDECLARE_SC(,__clock_t,times,(struct tms *__buf),(__buf))
#endif /* __CRT_HAVE_SC(times) */
#if __CRT_HAVE_SC(tkill)
__CDECLARE_SC(,__errno_t,tkill,(__pid_t __tid, __signo_t __signo),(__tid,__signo))
#endif /* __CRT_HAVE_SC(tkill) */
#if __CRT_HAVE_SC(truncate)
__CDECLARE_SC(,__errno_t,truncate,(char const *__filename, __syscall_ulong_t __length),(__filename,__length))
#endif /* __CRT_HAVE_SC(truncate) */
#if __CRT_HAVE_SC(umask)
__CDECLARE_SC(,__mode_t,umask,(__mode_t __mode),(__mode))
#endif /* __CRT_HAVE_SC(umask) */
#if __CRT_HAVE_SC(umount)
__CDECLARE_SC(,__errno_t,umount,(char const *__special_file),(__special_file))
#endif /* __CRT_HAVE_SC(umount) */
#if __CRT_HAVE_SC(umount2)
__CDECLARE_SC(,__errno_t,umount2,(char const *__special_file, __syscall_ulong_t __flags),(__special_file,__flags))
#endif /* __CRT_HAVE_SC(umount2) */
#if __CRT_HAVE_SC(uname)
__CDECLARE_SC(,__errno_t,uname,(struct utsname *__name),(__name))
#endif /* __CRT_HAVE_SC(uname) */
#if __CRT_HAVE_SC(unlink)
__CDECLARE_SC(,__errno_t,unlink,(char const *__filename),(__filename))
#endif /* __CRT_HAVE_SC(unlink) */
#if __CRT_HAVE_SC(unlinkat)
/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,unlinkat,(__fd_t __dirfd, char const *__name, __atflag_t __flags),(__dirfd,__name,__flags))
#endif /* __CRT_HAVE_SC(unlinkat) */
#if __CRT_HAVE_SC(unshare)
/* param: what: Set of `CLONE_*' */
__CDECLARE_SC(,__errno_t,unshare,(__syscall_ulong_t __what),(__what))
#endif /* __CRT_HAVE_SC(unshare) */
#if __CRT_HAVE_SC(uselib)
__CDECLARE_SC(,__errno_t,uselib,(char const *__library),(__library))
#endif /* __CRT_HAVE_SC(uselib) */
#if __CRT_HAVE_SC(userfaultfd)
__CDECLARE_SC(,__fd_t,userfaultfd,(__syscall_ulong_t __flags),(__flags))
#endif /* __CRT_HAVE_SC(userfaultfd) */
#if __CRT_HAVE_SC(ustat)
__CDECLARE_SC(,__errno_t,ustat,(__dev_t __dev, struct ustat *__ubuf),(__dev,__ubuf))
#endif /* __CRT_HAVE_SC(ustat) */
#if __CRT_HAVE_SC(utime)
/* @param: times: When NULL, set the current time */
__CDECLARE_SC(,__errno_t,utime,(char const *__filename, struct utimbuf const *__times),(__filename,__times))
#endif /* __CRT_HAVE_SC(utime) */
#if __CRT_HAVE_SC(utimensat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,utimensat,(__fd_t __dirfd, char const *__filename, struct timespec const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* __CRT_HAVE_SC(utimensat) */
#if __CRT_HAVE_SC(utimes)
/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
__CDECLARE_SC(,__errno_t,utimes,(char const *__filename, struct timeval const *__times),(__filename,__times))
#endif /* __CRT_HAVE_SC(utimes) */
#if __CRT_HAVE_SC(vfork)
/* Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `exit(2)'       Terminate the child process
 *   - `exit_group(2)' Terminate the child process
 *   - `execve(2)'     Create a new VM that is populated with the specified process
 *                     image. The parent process will  only be resumed in case  the
 *                     new  program image could  be loaded successfully. Otherwise,
 *                     the call  to  `execve(2)'  returns normally  in  the  child.
 *                     Other functions from the exec()-family behave the same
 * 
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 * 
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
__CDECLARE_SC(,__pid_t,vfork,(void),())
#endif /* __CRT_HAVE_SC(vfork) */
#if __CRT_HAVE_SC(vhangup)
__CDECLARE_SC(,__errno_t,vhangup,(void),())
#endif /* __CRT_HAVE_SC(vhangup) */
#if __CRT_HAVE_SC(vmsplice)
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
__CDECLARE_SC(,__ssize_t,vmsplice,(__fd_t __fdout, struct iovec const *__iov, __size_t __count, __syscall_ulong_t __flags),(__fdout,__iov,__count,__flags))
#endif /* __CRT_HAVE_SC(vmsplice) */
#if __CRT_HAVE_SC(wait4)
/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE_SC(,__pid_t,wait4,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options, struct rusage *__usage),(__pid,__stat_loc,__options,__usage))
#endif /* __CRT_HAVE_SC(wait4) */
#if __CRT_HAVE_SC(waitid)
/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
__CDECLARE_SC(,__errno_t,waitid,(__syscall_ulong_t __idtype, __id_t __id, struct __siginfo_struct *__infop, __syscall_ulong_t __options, struct rusage *__ru),(__idtype,__id,__infop,__options,__ru))
#endif /* __CRT_HAVE_SC(waitid) */
#if __CRT_HAVE_SC(write)
/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CDECLARE_SC(,__ssize_t,write,(__fd_t __fd, void const *__buf, __size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* __CRT_HAVE_SC(write) */
#if __CRT_HAVE_SC(writev)
/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
__CDECLARE_SC(,__ssize_t,writev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_SC(writev) */
#if __CRT_HAVE_XSC(_sysctl)
__CDECLARE_XSC(,__errno_t,_sysctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(_sysctl) */
#if __CRT_HAVE_XSC(accept)
/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The  amount  of required  memory for  the address.
 *                           This  may be  more than  was given,  in which case
 *                           the  address  was  truncated and  may  be invalid.
 *                           If this happens,  the caller  can still  determine
 *                           the correct address through use of `getpeername()'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
__CDECLARE_XSC(,__fd_t,accept,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_XSC(accept) */
#if __CRT_HAVE_XSC(accept4)
/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The  amount  of required  memory for  the address.
 *                            This  may be  more than  was given,  in which case
 *                            the  address  was  truncated and  may  be invalid.
 *                            If this happens,  the caller  can still  determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
__CDECLARE_XSC(,__fd_t,accept4,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len, __syscall_ulong_t __sock_flags),(__sockfd,__addr,__addr_len,__sock_flags))
#endif /* __CRT_HAVE_XSC(accept4) */
#if __CRT_HAVE_XSC(access)
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
__CDECLARE_XSC(,__errno_t,access,(char const *__filename, __syscall_ulong_t __type),(__filename,__type))
#endif /* __CRT_HAVE_XSC(access) */
#if __CRT_HAVE_XSC(acct)
__CDECLARE_XSC(,__errno_t,acct,(char const *__filename),(__filename))
#endif /* __CRT_HAVE_XSC(acct) */
#if __CRT_HAVE_XSC(add_key)
__CDECLARE_XSC(,__errno_t,add_key,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(add_key) */
#if __CRT_HAVE_XSC(adjtimex)
__CDECLARE_XSC(,__errno_t,adjtimex,(struct timex *__ntx),(__ntx))
#endif /* __CRT_HAVE_XSC(adjtimex) */
#if __CRT_HAVE_XSC(alarm)
__CDECLARE_XSC(,__syscall_ulong_t,alarm,(__syscall_ulong_t __seconds),(__seconds))
#endif /* __CRT_HAVE_XSC(alarm) */
#if __CRT_HAVE_XSC(bdflush)
__CDECLARE_XSC(,__errno_t,bdflush,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(bdflush) */
#if __CRT_HAVE_XSC(bind)
/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
__CDECLARE_XSC(,__errno_t,bind,(__fd_t __sockfd, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_XSC(bind) */
#if __CRT_HAVE_XSC(bpf)
__CDECLARE_XSC(,__errno_t,bpf,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(bpf) */
#if __CRT_HAVE_XSC(brk)
__CDECLARE_XSC(,__errno_t,brk,(void *__addr),(__addr))
#endif /* __CRT_HAVE_XSC(brk) */
#if __CRT_HAVE_XSC(capget)
__CDECLARE_XSC(,__errno_t,capget,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(capget) */
#if __CRT_HAVE_XSC(capset)
__CDECLARE_XSC(,__errno_t,capset,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(capset) */
#if __CRT_HAVE_XSC(chdir)
__CDECLARE_XSC(,__errno_t,chdir,(char const *__path),(__path))
#endif /* __CRT_HAVE_XSC(chdir) */
#if __CRT_HAVE_XSC(chmod)
__CDECLARE_XSC(,__errno_t,chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#endif /* __CRT_HAVE_XSC(chmod) */
#if __CRT_HAVE_XSC(chown)
__CDECLARE_XSC(,__errno_t,chown,(char const *__filename, __uid_t __owner, __gid_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_XSC(chown) */
#if __CRT_HAVE_XSC(chroot)
__CDECLARE_XSC(,__errno_t,chroot,(char const *__path),(__path))
#endif /* __CRT_HAVE_XSC(chroot) */
#if __CRT_HAVE_XSC(clock_adjtime)
__CDECLARE_XSC(,__errno_t,clock_adjtime,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(clock_adjtime) */
#if __CRT_HAVE_XSC(clock_getres)
__CDECLARE_XSC(,__errno_t,clock_getres,(__clockid_t __clock_id, struct timespec *__res),(__clock_id,__res))
#endif /* __CRT_HAVE_XSC(clock_getres) */
#if __CRT_HAVE_XSC(clock_gettime)
__CDECLARE_XSC(,__errno_t,clock_gettime,(__clockid_t __clock_id, struct timespec *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_XSC(clock_gettime) */
#if __CRT_HAVE_XSC(clock_nanosleep)
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
__CDECLARE_XSC(,__errno_t,clock_nanosleep,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct timespec const *__requested_time, struct timespec *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* __CRT_HAVE_XSC(clock_nanosleep) */
#if __CRT_HAVE_XSC(clock_settime)
__CDECLARE_XSC(,__errno_t,clock_settime,(__clockid_t __clock_id, struct timespec const *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_XSC(clock_settime) */
#if __CRT_HAVE_XSC(clone)
__CDECLARE_XSC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __uintptr_t __newtls, __pid_t *__ctid),(__flags,__child_stack,__ptid,__newtls,__ctid))
#endif /* __CRT_HAVE_XSC(clone) */
#if __CRT_HAVE_XSC(close)
/* Close a given file descriptor/handle `fd' */
__CDECLARE_XSC(,__errno_t,close,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_XSC(close) */
#if __CRT_HAVE_XSC(connect)
/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that  will implicitly be  used as destination  by `send(2)' and `write(2)'
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_BUFFER_TOO_SMALL   (addr_len is incorrect)
 * @return: 0 : Success */
__CDECLARE_XSC(,__errno_t,connect,(__fd_t __sockfd, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_XSC(connect) */
#if __CRT_HAVE_XSC(creat)
__CDECLARE_XSC(,__fd_t,creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#endif /* __CRT_HAVE_XSC(creat) */
#if __CRT_HAVE_XSC(delete_module)
/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
__CDECLARE_XSC(,__errno_t,delete_module,(char const *__name, __oflag_t __flags),(__name,__flags))
#endif /* __CRT_HAVE_XSC(delete_module) */
#if __CRT_HAVE_XSC(dup)
__CDECLARE_XSC(,__fd_t,dup,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_XSC(dup) */
#if __CRT_HAVE_XSC(dup2)
__CDECLARE_XSC(,__fd_t,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#endif /* __CRT_HAVE_XSC(dup2) */
#if __CRT_HAVE_XSC(dup3)
/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
__CDECLARE_XSC(,__fd_t,dup3,(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags),(__oldfd,__newfd,__flags))
#endif /* __CRT_HAVE_XSC(dup3) */
#if __CRT_HAVE_XSC(epoll_create)
/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_XSC(,__fd_t,epoll_create,(__syscall_ulong_t __size),(__size))
#endif /* __CRT_HAVE_XSC(epoll_create) */
#if __CRT_HAVE_XSC(epoll_create1)
/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
__CDECLARE_XSC(,__fd_t,epoll_create1,(__syscall_ulong_t __flags),(__flags))
#endif /* __CRT_HAVE_XSC(epoll_create1) */
#if __CRT_HAVE_XSC(epoll_ctl)
/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:       One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:       The file descriptor to add/remove/modify
 * @param: info:     The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :      Success
 * @return: -EEXIST: [op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -ENOENT: [op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
__CDECLARE_XSC(,__errno_t,epoll_ctl,(__fd_t __epfd, __syscall_ulong_t __op, __fd_t __fd, struct epoll_event *__info),(__epfd,__op,__fd,__info))
#endif /* __CRT_HAVE_XSC(epoll_ctl) */
#if __CRT_HAVE_XSC(epoll_pwait)
/* >> epoll_pwait(2)
 * Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
 * waiting.  Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @param: ss:        The signal mask to apply while waiting for an event to happen.
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
__CDECLARE_XSC(,__ssize_t,epoll_pwait,(__fd_t __epfd, struct epoll_event *__events, __size_t __maxevents, __syscall_slong_t __timeout, struct __sigset_struct const *__ss, __size_t __sigsetsize),(__epfd,__events,__maxevents,__timeout,__ss,__sigsetsize))
#endif /* __CRT_HAVE_XSC(epoll_pwait) */
#if __CRT_HAVE_XSC(epoll_wait)
/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
__CDECLARE_XSC(,__ssize_t,epoll_wait,(__fd_t __epfd, struct epoll_event *__events, __size_t __maxevents, __syscall_slong_t __timeout),(__epfd,__events,__maxevents,__timeout))
#endif /* __CRT_HAVE_XSC(epoll_wait) */
#if __CRT_HAVE_XSC(eventfd)
__CDECLARE_XSC(,__fd_t,eventfd,(__syscall_ulong_t __initval),(__initval))
#endif /* __CRT_HAVE_XSC(eventfd) */
#if __CRT_HAVE_XSC(eventfd2)
/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
__CDECLARE_XSC(,__fd_t,eventfd2,(__syscall_ulong_t __initval, __syscall_ulong_t __flags),(__initval,__flags))
#endif /* __CRT_HAVE_XSC(eventfd2) */
#if __CRT_HAVE_XSC(execve)
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE_XSC(,__errno_t,execve,(char const *__path, char const *const *___argv, char const *const *___envp),(__path,___argv,___envp))
#endif /* __CRT_HAVE_XSC(execve) */
#if __CRT_HAVE_XSC(execveat)
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,execveat,(__fd_t __dirfd, char const *__pathname, char const *const *___argv, char const *const *___envp, __atflag_t __flags),(__dirfd,__pathname,___argv,___envp,__flags))
#endif /* __CRT_HAVE_XSC(execveat) */
#if __CRT_HAVE_XSC(exit)
/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
__CDECLARE_VOID_XSC(__ATTR_NORETURN,exit,(__syscall_ulong_t __exit_code),(__exit_code))
#endif /* __CRT_HAVE_XSC(exit) */
#if __CRT_HAVE_XSC(exit_group)
/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
__CDECLARE_VOID_XSC(__ATTR_NORETURN,exit_group,(__syscall_ulong_t __exit_code),(__exit_code))
#endif /* __CRT_HAVE_XSC(exit_group) */
#if __CRT_HAVE_XSC(faccessat)
/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
__CDECLARE_XSC(,__errno_t,faccessat,(__fd_t __dirfd, char const *__filename, __syscall_ulong_t __type),(__dirfd,__filename,__type))
#endif /* __CRT_HAVE_XSC(faccessat) */
#if __CRT_HAVE_XSC(fadvise64)
__CDECLARE_XSC(,__errno_t,fadvise64,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(fadvise64) */
#if __CRT_HAVE_XSC(fallocate)
/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
__CDECLARE_XSC(,__errno_t,fallocate,(__fd_t __fd, __syscall_ulong_t __mode, __syscall_ulong_t __offset, __syscall_ulong_t __length),(__fd,__mode,__offset,__length))
#endif /* __CRT_HAVE_XSC(fallocate) */
#if __CRT_HAVE_XSC(fanotify_init)
__CDECLARE_XSC(,__errno_t,fanotify_init,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(fanotify_init) */
#if __CRT_HAVE_XSC(fanotify_mark)
__CDECLARE_XSC(,__errno_t,fanotify_mark,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(fanotify_mark) */
#if __CRT_HAVE_XSC(fchdir)
__CDECLARE_XSC(,__errno_t,fchdir,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_XSC(fchdir) */
#if __CRT_HAVE_XSC(fchmod)
__CDECLARE_XSC(,__errno_t,fchmod,(__fd_t __fd, __mode_t __mode),(__fd,__mode))
#endif /* __CRT_HAVE_XSC(fchmod) */
#if __CRT_HAVE_XSC(fchmodat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fchmodat,(__fd_t __dirfd, char const *__filename, __mode_t __mode, __atflag_t __flags),(__dirfd,__filename,__mode,__flags))
#endif /* __CRT_HAVE_XSC(fchmodat) */
#if __CRT_HAVE_XSC(fchown)
__CDECLARE_XSC(,__errno_t,fchown,(__fd_t __fd, __uid_t __owner, __gid_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_XSC(fchown) */
#if __CRT_HAVE_XSC(fchownat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,fchownat,(__fd_t __dirfd, char const *__filename, __uid_t __owner, __gid_t __group, __atflag_t __flags),(__dirfd,__filename,__owner,__group,__flags))
#endif /* __CRT_HAVE_XSC(fchownat) */
#if __CRT_HAVE_XSC(fcntl)
__CDECLARE_XSC(,__syscall_slong_t,fcntl,(__fd_t __fd, __fcntl_t __command, void *__arg),(__fd,__command,__arg))
#endif /* __CRT_HAVE_XSC(fcntl) */
#if __CRT_HAVE_XSC(fdatasync)
/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CDECLARE_XSC(,__errno_t,fdatasync,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_XSC(fdatasync) */
#if __CRT_HAVE_XSC(fgetxattr)
__CDECLARE_XSC(,__ssize_t,fgetxattr,(__fd_t __fd, char const *__name, void *__buf, __size_t __bufsize),(__fd,__name,__buf,__bufsize))
#endif /* __CRT_HAVE_XSC(fgetxattr) */
#if __CRT_HAVE_XSC(finit_module)
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
__CDECLARE_XSC(,__errno_t,finit_module,(__fd_t __fd, char const *__uargs, __syscall_ulong_t __flags),(__fd,__uargs,__flags))
#endif /* __CRT_HAVE_XSC(finit_module) */
#if __CRT_HAVE_XSC(flistxattr)
__CDECLARE_XSC(,__ssize_t,flistxattr,(__fd_t __fd, char *__listbuf, __size_t __listbufsize),(__fd,__listbuf,__listbufsize))
#endif /* __CRT_HAVE_XSC(flistxattr) */
#if __CRT_HAVE_XSC(flock)
__CDECLARE_XSC(,__errno_t,flock,(__fd_t __fd, __syscall_ulong_t __operation),(__fd,__operation))
#endif /* __CRT_HAVE_XSC(flock) */
#if __CRT_HAVE_XSC(fork)
/* Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
__CDECLARE_XSC(,__pid_t,fork,(void),())
#endif /* __CRT_HAVE_XSC(fork) */
#if __CRT_HAVE_XSC(fremovexattr)
__CDECLARE_XSC(,__errno_t,fremovexattr,(__fd_t __fd, char const *__name),(__fd,__name))
#endif /* __CRT_HAVE_XSC(fremovexattr) */
#if __CRT_HAVE_XSC(fsetxattr)
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
__CDECLARE_XSC(,__errno_t,fsetxattr,(__fd_t __fd, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__fd,__name,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_XSC(fsetxattr) */
#if __CRT_HAVE_XSC(fstat)
__CDECLARE_XSC(,__errno_t,fstat,(__fd_t __fd, struct linux_stat *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_XSC(fstat) */
#if __CRT_HAVE_XSC(fstatfs)
__CDECLARE_XSC(,__errno_t,fstatfs,(__fd_t __file, struct statfs *__buf),(__file,__buf))
#endif /* __CRT_HAVE_XSC(fstatfs) */
#if __CRT_HAVE_XSC(fsync)
/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CDECLARE_XSC(,__errno_t,fsync,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_XSC(fsync) */
#if __CRT_HAVE_XSC(ftruncate)
__CDECLARE_XSC(,__errno_t,ftruncate,(__fd_t __fd, __syscall_ulong_t __length),(__fd,__length))
#endif /* __CRT_HAVE_XSC(ftruncate) */
#if __CRT_HAVE_XSC(futex)
/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
__CDECLARE_XSC(,__syscall_slong_t,futex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct timespec const *__timeout_or_val2, __uint32_t *__uaddr2, __uint32_t __val3),(__uaddr,__futex_op,__val,__timeout_or_val2,__uaddr2,__val3))
#endif /* __CRT_HAVE_XSC(futex) */
#if __CRT_HAVE_XSC(futimesat)
__CDECLARE_XSC(,__errno_t,futimesat,(__fd_t __dirfd, char const *__filename, struct timeval const *__times),(__dirfd,__filename,__times))
#endif /* __CRT_HAVE_XSC(futimesat) */
#if __CRT_HAVE_XSC(get_mempolicy)
__CDECLARE_XSC(,__errno_t,get_mempolicy,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(get_mempolicy) */
#if __CRT_HAVE_XSC(get_robust_list)
__CDECLARE_XSC(,__errno_t,get_robust_list,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(get_robust_list) */
#if __CRT_HAVE_XSC(getcpu)
__CDECLARE_XSC(,__errno_t,getcpu,(__uint32_t *__cpu, __uint32_t *__node, struct getcpu_cache *__tcache),(__cpu,__node,__tcache))
#endif /* __CRT_HAVE_XSC(getcpu) */
#if __CRT_HAVE_XSC(getcwd)
__CDECLARE_XSC(,__ssize_t,getcwd,(char *__buf, __size_t __size),(__buf,__size))
#endif /* __CRT_HAVE_XSC(getcwd) */
#if __CRT_HAVE_XSC(getdents)
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
__CDECLARE_XSC(,__ssize_t,getdents,(__fd_t __fd, struct linux_dirent *__buf, __size_t __buflen),(__fd,__buf,__buflen))
#endif /* __CRT_HAVE_XSC(getdents) */
#if __CRT_HAVE_XSC(getdents64)
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
__CDECLARE_XSC(,__ssize_t,getdents64,(__fd_t __fd, struct linux_dirent64 *__buf, __size_t __buflen),(__fd,__buf,__buflen))
#endif /* __CRT_HAVE_XSC(getdents64) */
#if __CRT_HAVE_XSC(getegid)
/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
__CDECLARE_XSC(,__gid_t,getegid,(void),())
#endif /* __CRT_HAVE_XSC(getegid) */
#if __CRT_HAVE_XSC(geteuid)
/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
__CDECLARE_XSC(,__uid_t,geteuid,(void),())
#endif /* __CRT_HAVE_XSC(geteuid) */
#if __CRT_HAVE_XSC(getgid)
/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
__CDECLARE_XSC(,__gid_t,getgid,(void),())
#endif /* __CRT_HAVE_XSC(getgid) */
#if __CRT_HAVE_XSC(getgroups)
/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
__CDECLARE_XSC(,__ssize_t,getgroups,(__size_t __count, __gid_t *__list),(__count,__list))
#endif /* __CRT_HAVE_XSC(getgroups) */
#if __CRT_HAVE_XSC(getitimer)
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
__CDECLARE_XSC(,__errno_t,getitimer,(__syscall_ulong_t __which, struct itimerval *__curr_value),(__which,__curr_value))
#endif /* __CRT_HAVE_XSC(getitimer) */
#if __CRT_HAVE_XSC(getpeername)
/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
__CDECLARE_XSC(,__errno_t,getpeername,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_XSC(getpeername) */
#if __CRT_HAVE_XSC(getpgid)
__CDECLARE_XSC(,__pid_t,getpgid,(__pid_t __pid),(__pid))
#endif /* __CRT_HAVE_XSC(getpgid) */
#if __CRT_HAVE_XSC(getpgrp)
__CDECLARE_XSC(,__pid_t,getpgrp,(void),())
#endif /* __CRT_HAVE_XSC(getpgrp) */
#if __CRT_HAVE_XSC(getpid)
__CDECLARE_XSC(,__pid_t,getpid,(void),())
#endif /* __CRT_HAVE_XSC(getpid) */
#if __CRT_HAVE_XSC(getppid)
__CDECLARE_XSC(,__pid_t,getppid,(void),())
#endif /* __CRT_HAVE_XSC(getppid) */
#if __CRT_HAVE_XSC(getpriority)
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
__CDECLARE_XSC(,__syscall_slong_t,getpriority,(__syscall_ulong_t __which, __id_t __who),(__which,__who))
#endif /* __CRT_HAVE_XSC(getpriority) */
#if __CRT_HAVE_XSC(getrandom)
/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
__CDECLARE_XSC(,__ssize_t,getrandom,(void *__buf, __size_t __num_bytes, __syscall_ulong_t __flags),(__buf,__num_bytes,__flags))
#endif /* __CRT_HAVE_XSC(getrandom) */
#if __CRT_HAVE_XSC(getresgid)
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
__CDECLARE_XSC(,__errno_t,getresgid,(__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_XSC(getresgid) */
#if __CRT_HAVE_XSC(getresuid)
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
__CDECLARE_XSC(,__errno_t,getresuid,(__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_XSC(getresuid) */
#if __CRT_HAVE_XSC(getrlimit)
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
__CDECLARE_XSC(,__errno_t,getrlimit,(__syscall_ulong_t __resource, struct rlimit *__rlimits),(__resource,__rlimits))
#endif /* __CRT_HAVE_XSC(getrlimit) */
#if __CRT_HAVE_XSC(getrusage)
/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
__CDECLARE_XSC(,__errno_t,getrusage,(__syscall_slong_t __who, struct rusage *__usage),(__who,__usage))
#endif /* __CRT_HAVE_XSC(getrusage) */
#if __CRT_HAVE_XSC(getsid)
__CDECLARE_XSC(,__pid_t,getsid,(__pid_t __pid),(__pid))
#endif /* __CRT_HAVE_XSC(getsid) */
#if __CRT_HAVE_XSC(getsockname)
/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This  is usually the  same address as was  previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly  undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * return: 0 : Success */
__CDECLARE_XSC(,__errno_t,getsockname,(__fd_t __sockfd, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__addr,__addr_len))
#endif /* __CRT_HAVE_XSC(getsockname) */
#if __CRT_HAVE_XSC(getsockopt)
/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the  contents  of   `optval'  are   undefined.
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
 * @return: 0 : Success */
__CDECLARE_XSC(,__errno_t,getsockopt,(__fd_t __sockfd, __syscall_ulong_t __level, __syscall_ulong_t __optname, void *__optval, __socklen_t *__optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* __CRT_HAVE_XSC(getsockopt) */
#if __CRT_HAVE_XSC(gettid)
__CDECLARE_XSC(,__pid_t,gettid,(void),())
#endif /* __CRT_HAVE_XSC(gettid) */
#if __CRT_HAVE_XSC(gettimeofday)
__CDECLARE_XSC(,__errno_t,gettimeofday,(struct timeval *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_XSC(gettimeofday) */
#if __CRT_HAVE_XSC(getuid)
/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
__CDECLARE_XSC(,__uid_t,getuid,(void),())
#endif /* __CRT_HAVE_XSC(getuid) */
#if __CRT_HAVE_XSC(getxattr)
__CDECLARE_XSC(,__ssize_t,getxattr,(char const *__path, char const *__name, void *__buf, __size_t __bufsize),(__path,__name,__buf,__bufsize))
#endif /* __CRT_HAVE_XSC(getxattr) */
#if __CRT_HAVE_XSC(init_module)
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
__CDECLARE_XSC(,__errno_t,init_module,(void const *__module_image, __size_t __len, char const *__uargs),(__module_image,__len,__uargs))
#endif /* __CRT_HAVE_XSC(init_module) */
#if __CRT_HAVE_XSC(inotify_add_watch)
/* @param: mask: Set of `IN_ALL_EVENTS | ...' */
__CDECLARE_XSC(,int,inotify_add_watch,(__fd_t __notify_fd, char const *__pathname, __uint32_t __mask),(__notify_fd,__pathname,__mask))
#endif /* __CRT_HAVE_XSC(inotify_add_watch) */
#if __CRT_HAVE_XSC(inotify_init)
__CDECLARE_XSC(,__fd_t,inotify_init,(void),())
#endif /* __CRT_HAVE_XSC(inotify_init) */
#if __CRT_HAVE_XSC(inotify_init1)
/* @param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK' */
__CDECLARE_XSC(,__fd_t,inotify_init1,(__syscall_ulong_t __flags),(__flags))
#endif /* __CRT_HAVE_XSC(inotify_init1) */
#if __CRT_HAVE_XSC(inotify_rm_watch)
/* @param: wd: Watch fd (as returned by `inotify_add_watch{_at}') */
__CDECLARE_XSC(,__errno_t,inotify_rm_watch,(__fd_t __notify_fd, int __wd),(__notify_fd,__wd))
#endif /* __CRT_HAVE_XSC(inotify_rm_watch) */
#if __CRT_HAVE_XSC(io_cancel)
__CDECLARE_XSC(,__errno_t,io_cancel,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(io_cancel) */
#if __CRT_HAVE_XSC(io_destroy)
__CDECLARE_XSC(,__errno_t,io_destroy,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(io_destroy) */
#if __CRT_HAVE_XSC(io_getevents)
__CDECLARE_XSC(,__errno_t,io_getevents,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(io_getevents) */
#if __CRT_HAVE_XSC(io_setup)
__CDECLARE_XSC(,__errno_t,io_setup,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(io_setup) */
#if __CRT_HAVE_XSC(io_submit)
__CDECLARE_XSC(,__errno_t,io_submit,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(io_submit) */
#if __CRT_HAVE_XSC(ioctl)
__CDECLARE_XSC(,__syscall_slong_t,ioctl,(__fd_t __fd, __ioctl_t __command, void *__arg),(__fd,__command,__arg))
#endif /* __CRT_HAVE_XSC(ioctl) */
#if __CRT_HAVE_XSC(ioprio_get)
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
__CDECLARE_XSC(,__syscall_slong_t,ioprio_get,(__syscall_ulong_t __who, __syscall_ulong_t __id),(__who,__id))
#endif /* __CRT_HAVE_XSC(ioprio_get) */
#if __CRT_HAVE_XSC(ioprio_set)
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
__CDECLARE_XSC(,__errno_t,ioprio_set,(__syscall_ulong_t __who, __syscall_ulong_t __id, __syscall_ulong_t __ioprio),(__who,__id,__ioprio))
#endif /* __CRT_HAVE_XSC(ioprio_set) */
#if __CRT_HAVE_XSC(kcmp)
/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
__CDECLARE_XSC(,__syscall_slong_t,kcmp,(__pid_t __pid1, __pid_t __pid2, __syscall_ulong_t __type, __syscall_ulong_t __idx1, __syscall_ulong_t __idx2),(__pid1,__pid2,__type,__idx1,__idx2))
#endif /* __CRT_HAVE_XSC(kcmp) */
#if __CRT_HAVE_XSC(kexec_load)
__CDECLARE_XSC(,__errno_t,kexec_load,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(kexec_load) */
#if __CRT_HAVE_XSC(keyctl)
__CDECLARE_XSC(,__errno_t,keyctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(keyctl) */
#if __CRT_HAVE_XSC(kill)
__CDECLARE_XSC(,__errno_t,kill,(__pid_t __pid, __signo_t __signo),(__pid,__signo))
#endif /* __CRT_HAVE_XSC(kill) */
#if __CRT_HAVE_XSC(lchown)
__CDECLARE_XSC(,__errno_t,lchown,(char const *__filename, __uid_t __owner, __gid_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_XSC(lchown) */
#if __CRT_HAVE_XSC(lgetxattr)
__CDECLARE_XSC(,__ssize_t,lgetxattr,(char const *__path, char const *__name, void *__buf, __size_t __bufsize),(__path,__name,__buf,__bufsize))
#endif /* __CRT_HAVE_XSC(lgetxattr) */
#if __CRT_HAVE_XSC(link)
__CDECLARE_XSC(,__errno_t,link,(char const *__existing_file, char const *__link_file),(__existing_file,__link_file))
#endif /* __CRT_HAVE_XSC(link) */
#if __CRT_HAVE_XSC(linkat)
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,linkat,(__fd_t __fromfd, char const *__existing_file, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__fromfd,__existing_file,__tofd,__target_path,__flags))
#endif /* __CRT_HAVE_XSC(linkat) */
#if __CRT_HAVE_XSC(listen)
/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
__CDECLARE_XSC(,__errno_t,listen,(__fd_t __sockfd, __syscall_ulong_t __max_backlog),(__sockfd,__max_backlog))
#endif /* __CRT_HAVE_XSC(listen) */
#if __CRT_HAVE_XSC(listxattr)
__CDECLARE_XSC(,__ssize_t,listxattr,(char const *__path, char *__listbuf, __size_t __listbufsize),(__path,__listbuf,__listbufsize))
#endif /* __CRT_HAVE_XSC(listxattr) */
#if __CRT_HAVE_XSC(llistxattr)
__CDECLARE_XSC(,__ssize_t,llistxattr,(char const *__path, char *__listbuf, __size_t __listbufsize),(__path,__listbuf,__listbufsize))
#endif /* __CRT_HAVE_XSC(llistxattr) */
#if __CRT_HAVE_XSC(lookup_dcookie)
__CDECLARE_XSC(,__errno_t,lookup_dcookie,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(lookup_dcookie) */
#if __CRT_HAVE_XSC(lremovexattr)
__CDECLARE_XSC(,__errno_t,lremovexattr,(char const *__path, char const *__name),(__path,__name))
#endif /* __CRT_HAVE_XSC(lremovexattr) */
#if __CRT_HAVE_XSC(lseek)
__CDECLARE_XSC(,__syscall_slong_t,lseek,(__fd_t __fd, __syscall_slong_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* __CRT_HAVE_XSC(lseek) */
#if __CRT_HAVE_XSC(lsetxattr)
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
__CDECLARE_XSC(,__errno_t,lsetxattr,(char const *__path, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__path,__name,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_XSC(lsetxattr) */
#if __CRT_HAVE_XSC(lstat)
__CDECLARE_XSC(,__errno_t,lstat,(char const *__filename, struct linux_stat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(lstat) */
#if __CRT_HAVE_XSC(madvise)
__CDECLARE_XSC(,__errno_t,madvise,(void *__addr, __size_t __len, __syscall_ulong_t __advice),(__addr,__len,__advice))
#endif /* __CRT_HAVE_XSC(madvise) */
#if __CRT_HAVE_XSC(mbind)
__CDECLARE_XSC(,__errno_t,mbind,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(mbind) */
#if __CRT_HAVE_XSC(membarrier)
__CDECLARE_XSC(,__errno_t,membarrier,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(membarrier) */
#if __CRT_HAVE_XSC(memfd_create)
/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
__CDECLARE_XSC(,__fd_t,memfd_create,(char const *__name, __syscall_ulong_t __flags),(__name,__flags))
#endif /* __CRT_HAVE_XSC(memfd_create) */
#if __CRT_HAVE_XSC(migrate_pages)
__CDECLARE_XSC(,__errno_t,migrate_pages,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(migrate_pages) */
#if __CRT_HAVE_XSC(mincore)
__CDECLARE_XSC(,__errno_t,mincore,(void *__start, __size_t __len, __uint8_t *__vec),(__start,__len,__vec))
#endif /* __CRT_HAVE_XSC(mincore) */
#if __CRT_HAVE_XSC(mkdir)
__CDECLARE_XSC(,__errno_t,mkdir,(char const *__pathname, __mode_t __mode),(__pathname,__mode))
#endif /* __CRT_HAVE_XSC(mkdir) */
#if __CRT_HAVE_XSC(mkdirat)
__CDECLARE_XSC(,__errno_t,mkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode),(__dirfd,__pathname,__mode))
#endif /* __CRT_HAVE_XSC(mkdirat) */
#if __CRT_HAVE_XSC(mknod)
__CDECLARE_XSC(,__errno_t,mknod,(char const *__nodename, __mode_t __mode, __dev_t __dev),(__nodename,__mode,__dev))
#endif /* __CRT_HAVE_XSC(mknod) */
#if __CRT_HAVE_XSC(mknodat)
__CDECLARE_XSC(,__errno_t,mknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev),(__dirfd,__nodename,__mode,__dev))
#endif /* __CRT_HAVE_XSC(mknodat) */
#if __CRT_HAVE_XSC(mlock)
__CDECLARE_XSC(,__errno_t,mlock,(void const *__addr, __size_t __len),(__addr,__len))
#endif /* __CRT_HAVE_XSC(mlock) */
#if __CRT_HAVE_XSC(mlock2)
__CDECLARE_XSC(,__errno_t,mlock2,(void const *__addr, __size_t __length, __syscall_ulong_t __flags),(__addr,__length,__flags))
#endif /* __CRT_HAVE_XSC(mlock2) */
#if __CRT_HAVE_XSC(mlockall)
/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
__CDECLARE_XSC(,__errno_t,mlockall,(__syscall_ulong_t __flags),(__flags))
#endif /* __CRT_HAVE_XSC(mlockall) */
#if __CRT_HAVE_XSC(mmap)
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED', 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
__CDECLARE_XSC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* __CRT_HAVE_XSC(mmap) */
#if __CRT_HAVE_XSC(mount)
__CDECLARE_XSC(,__errno_t,mount,(char const *__special_file, char const *__dir, char const *__fstype, __syscall_ulong_t __mountflags, void const *__data),(__special_file,__dir,__fstype,__mountflags,__data))
#endif /* __CRT_HAVE_XSC(mount) */
#if __CRT_HAVE_XSC(move_pages)
__CDECLARE_XSC(,__errno_t,move_pages,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(move_pages) */
#if __CRT_HAVE_XSC(mprotect)
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
__CDECLARE_XSC(,__errno_t,mprotect,(void *__addr, __size_t __len, __syscall_ulong_t __prot),(__addr,__len,__prot))
#endif /* __CRT_HAVE_XSC(mprotect) */
#if __CRT_HAVE_XSC(mq_getsetattr)
__CDECLARE_XSC(,__errno_t,mq_getsetattr,(__fd_t __mqdes, struct mq_attr const *__newattr, struct mq_attr *__oldattr),(__mqdes,__newattr,__oldattr))
#endif /* __CRT_HAVE_XSC(mq_getsetattr) */
#if __CRT_HAVE_XSC(mq_notify)
__CDECLARE_XSC(,__errno_t,mq_notify,(__fd_t __mqdes, struct sigevent const *__notification),(__mqdes,__notification))
#endif /* __CRT_HAVE_XSC(mq_notify) */
#if __CRT_HAVE_XSC(mq_open)
__CDECLARE_XSC(,__fd_t,mq_open,(char const *__name, __oflag_t __oflags, __mode_t __mode),(__name,__oflags,__mode))
#endif /* __CRT_HAVE_XSC(mq_open) */
#if __CRT_HAVE_XSC(mq_timedreceive)
__CDECLARE_XSC(,__ssize_t,mq_timedreceive,(__fd_t __mqdes, char *__msg_ptr, __size_t __msg_len, __uint32_t *__pmsg_prio, struct timespec const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#endif /* __CRT_HAVE_XSC(mq_timedreceive) */
#if __CRT_HAVE_XSC(mq_timedsend)
__CDECLARE_XSC(,__errno_t,mq_timedsend,(__fd_t __mqdes, char const *__msg_ptr, __size_t __msg_len, __uint32_t __msg_prio, struct timespec const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#endif /* __CRT_HAVE_XSC(mq_timedsend) */
#if __CRT_HAVE_XSC(mq_unlink)
__CDECLARE_XSC(,__errno_t,mq_unlink,(char const *__name),(__name))
#endif /* __CRT_HAVE_XSC(mq_unlink) */
#if __CRT_HAVE_XSC(mremap)
/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
__CDECLARE_XSC(,void *,mremap,(void *__addr, __size_t __old_len, __size_t __new_len, __syscall_ulong_t __flags, void *__new_address),(__addr,__old_len,__new_len,__flags,__new_address))
#endif /* __CRT_HAVE_XSC(mremap) */
#if __CRT_HAVE_XSC(msgctl)
__CDECLARE_XSC(,__errno_t,msgctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(msgctl) */
#if __CRT_HAVE_XSC(msgget)
__CDECLARE_XSC(,__errno_t,msgget,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(msgget) */
#if __CRT_HAVE_XSC(msgrcv)
__CDECLARE_XSC(,__errno_t,msgrcv,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(msgrcv) */
#if __CRT_HAVE_XSC(msgsnd)
__CDECLARE_XSC(,__errno_t,msgsnd,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(msgsnd) */
#if __CRT_HAVE_XSC(msync)
__CDECLARE_XSC(,__errno_t,msync,(void *__addr, __size_t __len, __syscall_ulong_t __flags),(__addr,__len,__flags))
#endif /* __CRT_HAVE_XSC(msync) */
#if __CRT_HAVE_XSC(munlock)
__CDECLARE_XSC(,__errno_t,munlock,(void const *__addr, __size_t __len),(__addr,__len))
#endif /* __CRT_HAVE_XSC(munlock) */
#if __CRT_HAVE_XSC(munlockall)
__CDECLARE_XSC(,__errno_t,munlockall,(void),())
#endif /* __CRT_HAVE_XSC(munlockall) */
#if __CRT_HAVE_XSC(munmap)
__CDECLARE_XSC(,__errno_t,munmap,(void *__addr, __size_t __len),(__addr,__len))
#endif /* __CRT_HAVE_XSC(munmap) */
#if __CRT_HAVE_XSC(name_to_handle_at)
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,name_to_handle_at,(__fd_t __dirfd, char const *__filename, struct file_handle *__handle, __int32_t *__mnt_id, __atflag_t __flags),(__dirfd,__filename,__handle,__mnt_id,__flags))
#endif /* __CRT_HAVE_XSC(name_to_handle_at) */
#if __CRT_HAVE_XSC(nanosleep)
__CDECLARE_XSC(,__errno_t,nanosleep,(struct timespec const *__req, struct timespec *__rem),(__req,__rem))
#endif /* __CRT_HAVE_XSC(nanosleep) */
#if __CRT_HAVE_XSC(newfstatat)
__CDECLARE_XSC(,__errno_t,newfstatat,(__fd_t __dirfd, char const *__filename, struct linux64_stat32 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* __CRT_HAVE_XSC(newfstatat) */
#if __CRT_HAVE_XSC(nfsservctl)
__CDECLARE_XSC(,__errno_t,nfsservctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(nfsservctl) */
#if __CRT_HAVE_XSC(oldwait4)
/* @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' */
__CDECLARE_XSC(,__pid_t,oldwait4,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options, struct rusage *__usage),(__pid,__stat_loc,__options,__usage))
#endif /* __CRT_HAVE_XSC(oldwait4) */
#if __CRT_HAVE_XSC(open)
/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CDECLARE_XSC(,__fd_t,open,(char const *__filename, __oflag_t __oflags, __mode_t __mode),(__filename,__oflags,__mode))
#endif /* __CRT_HAVE_XSC(open) */
#if __CRT_HAVE_XSC(open_by_handle_at)
__CDECLARE_XSC(,__fd_t,open_by_handle_at,(__fd_t __mountdirfd, struct file_handle const *__handle, __oflag_t __flags),(__mountdirfd,__handle,__flags))
#endif /* __CRT_HAVE_XSC(open_by_handle_at) */
#if __CRT_HAVE_XSC(openat)
/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
__CDECLARE_XSC(,__fd_t,openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, __mode_t __mode),(__dirfd,__filename,__oflags,__mode))
#endif /* __CRT_HAVE_XSC(openat) */
#if __CRT_HAVE_XSC(pause)
/* Same as `select(0, NULL, NULL, NULL, NULL)' */
__CDECLARE_XSC(,__errno_t,pause,(void),())
#endif /* __CRT_HAVE_XSC(pause) */
#if __CRT_HAVE_XSC(perf_event_open)
__CDECLARE_XSC(,__errno_t,perf_event_open,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(perf_event_open) */
#if __CRT_HAVE_XSC(personality)
__CDECLARE_XSC(,__errno_t,personality,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(personality) */
#if __CRT_HAVE_XSC(pipe)
__CDECLARE_XSC(,__errno_t,pipe,(__fd_t *__pipedes),(__pipedes))
#endif /* __CRT_HAVE_XSC(pipe) */
#if __CRT_HAVE_XSC(pipe2)
__CDECLARE_XSC(,__errno_t,pipe2,(__fd_t *__pipedes, __oflag_t __flags),(__pipedes,__flags))
#endif /* __CRT_HAVE_XSC(pipe2) */
#if __CRT_HAVE_XSC(pivot_root)
__CDECLARE_XSC(,__errno_t,pivot_root,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(pivot_root) */
#if __CRT_HAVE_XSC(poll)
__CDECLARE_XSC(,__ssize_t,poll,(struct pollfd *__fds, __size_t __nfds, __syscall_slong_t __timeout),(__fds,__nfds,__timeout))
#endif /* __CRT_HAVE_XSC(poll) */
#if __CRT_HAVE_XSC(ppoll)
__CDECLARE_XSC(,__ssize_t,ppoll,(struct pollfd *__fds, __size_t __nfds, struct timespec const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* __CRT_HAVE_XSC(ppoll) */
#if __CRT_HAVE_XSC(prctl)
/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... : Up  to 4 additional arguments (dependent on `command')
 *               Note that some control codes  require you to pass  `0'
 *               for  all seemingly "unused" arguments. In these cases,
 *               the documentation for that command includes the number
 *               of unused, but required trailing 0s in its comment.
 * @return: * :  Return value depends on `command' */
__CDECLARE_XSC(,__syscall_slong_t,prctl,(unsigned int __command, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5),(__command,__arg2,__arg3,__arg4,__arg5))
#endif /* __CRT_HAVE_XSC(prctl) */
#if __CRT_HAVE_XSC(pread64)
__CDECLARE_XSC(,__ssize_t,pread64,(__fd_t __fd, void *__buf, __size_t __bufsize, __uint64_t __offset),(__fd,__buf,__bufsize,__offset))
#endif /* __CRT_HAVE_XSC(pread64) */
#if __CRT_HAVE_XSC(preadv)
/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__CDECLARE_XSC(,__ssize_t,preadv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_XSC(preadv) */
#if __CRT_HAVE_XSC(prlimit64)
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
__CDECLARE_XSC(,__errno_t,prlimit64,(__pid_t __pid, __syscall_ulong_t __resource, struct __rlimit64 const *__new_limit, struct __rlimit64 *__old_limit),(__pid,__resource,__new_limit,__old_limit))
#endif /* __CRT_HAVE_XSC(prlimit64) */
#if __CRT_HAVE_XSC(process_vm_readv)
/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
__CDECLARE_XSC(,__ssize_t,process_vm_readv,(__pid_t __pid, struct iovec const *__local_iov, __size_t __liovcnt, struct iovec const *__remote_iov, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__local_iov,__liovcnt,__remote_iov,__riovcnt,__flags))
#endif /* __CRT_HAVE_XSC(process_vm_readv) */
#if __CRT_HAVE_XSC(process_vm_writev)
/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
__CDECLARE_XSC(,__ssize_t,process_vm_writev,(__pid_t __pid, struct iovec const *__local_iov, __size_t __liovcnt, struct iovec const *__remote_iov, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__local_iov,__liovcnt,__remote_iov,__riovcnt,__flags))
#endif /* __CRT_HAVE_XSC(process_vm_writev) */
#if __CRT_HAVE_XSC(pselect6)
__CDECLARE_XSC(,__ssize_t,pselect6,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct timespec const *__timeout, struct sigset_with_size const *__sigmask_sigset_with_size),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_with_size))
#endif /* __CRT_HAVE_XSC(pselect6) */
#if __CRT_HAVE_XSC(ptrace)
__CDECLARE_XSC(,__syscall_slong_t,ptrace,(__syscall_ulong_t __request, __pid_t __pid, void *__addr, void *__data),(__request,__pid,__addr,__data))
#endif /* __CRT_HAVE_XSC(ptrace) */
#if __CRT_HAVE_XSC(pwrite64)
__CDECLARE_XSC(,__ssize_t,pwrite64,(__fd_t __fd, void const *__buf, __size_t __bufsize, __uint64_t __offset),(__fd,__buf,__bufsize,__offset))
#endif /* __CRT_HAVE_XSC(pwrite64) */
#if __CRT_HAVE_XSC(pwritev)
/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
__CDECLARE_XSC(,__ssize_t,pwritev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_XSC(pwritev) */
#if __CRT_HAVE_XSC(quotactl)
__CDECLARE_XSC(,__errno_t,quotactl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(quotactl) */
#if __CRT_HAVE_XSC(read)
/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CDECLARE_XSC(,__ssize_t,read,(__fd_t __fd, void *__buf, __size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* __CRT_HAVE_XSC(read) */
#if __CRT_HAVE_XSC(readahead)
__CDECLARE_XSC(,__ssize_t,readahead,(__fd_t __fd, __uint64_t __offset, __size_t __count),(__fd,__offset,__count))
#endif /* __CRT_HAVE_XSC(readahead) */
#if __CRT_HAVE_XSC(readlink)
__CDECLARE_XSC(,__ssize_t,readlink,(char const *__path, char *__buf, __size_t __buflen),(__path,__buf,__buflen))
#endif /* __CRT_HAVE_XSC(readlink) */
#if __CRT_HAVE_XSC(readlinkat)
__CDECLARE_XSC(,__ssize_t,readlinkat,(__fd_t __dirfd, char const *__path, char *__buf, __size_t __buflen),(__dirfd,__path,__buf,__buflen))
#endif /* __CRT_HAVE_XSC(readlinkat) */
#if __CRT_HAVE_XSC(readv)
/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
__CDECLARE_XSC(,__ssize_t,readv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_XSC(readv) */
#if __CRT_HAVE_XSC(reboot)
/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
__CDECLARE_XSC(,__errno_t,reboot,(__syscall_ulong_t __how),(__how))
#endif /* __CRT_HAVE_XSC(reboot) */
#if __CRT_HAVE_XSC(recv)
/* Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @return: * : [<= bufsize] The actual # of received bytes */
__CDECLARE_XSC(,__ssize_t,recv,(__fd_t __sockfd, void *__buf, __size_t __bufsize, __syscall_ulong_t __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
#endif /* __CRT_HAVE_XSC(recv) */
#if __CRT_HAVE_XSC(recvfrom)
/* Receive data over this socket, and store the contents within the given buffer.
 * @param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
 * @param: bufsize:   Max # of bytes to receive
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked)
 * @return: * : [<= bufsize] The actual # of received bytes */
__CDECLARE_XSC(,__ssize_t,recvfrom,(__fd_t __sockfd, void *__buf, __size_t __bufsize, __syscall_ulong_t __msg_flags, struct sockaddr *__addr, __socklen_t *__addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
#endif /* __CRT_HAVE_XSC(recvfrom) */
#if __CRT_HAVE_XSC(recvmmsg)
/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
__CDECLARE_XSC(,__ssize_t,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __msg_flags, struct timespec const *__tmo),(__sockfd,__vmessages,__vlen,__msg_flags,__tmo))
#endif /* __CRT_HAVE_XSC(recvmmsg) */
#if __CRT_HAVE_XSC(recvmsg)
/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
__CDECLARE_XSC(,__ssize_t,recvmsg,(__fd_t __sockfd, struct msghdr *__message, __syscall_ulong_t __msg_flags),(__sockfd,__message,__msg_flags))
#endif /* __CRT_HAVE_XSC(recvmsg) */
#if __CRT_HAVE_XSC(remap_file_pages)
__CDECLARE_XSC(,__errno_t,remap_file_pages,(void *__start, __size_t __size, __syscall_ulong_t __prot, __size_t __pgoff, __syscall_ulong_t __flags),(__start,__size,__prot,__pgoff,__flags))
#endif /* __CRT_HAVE_XSC(remap_file_pages) */
#if __CRT_HAVE_XSC(removexattr)
__CDECLARE_XSC(,__errno_t,removexattr,(char const *__path, char const *__name),(__path,__name))
#endif /* __CRT_HAVE_XSC(removexattr) */
#if __CRT_HAVE_XSC(rename)
__CDECLARE_XSC(,__errno_t,rename,(char const *__oldname, char const *__newname_or_path),(__oldname,__newname_or_path))
#endif /* __CRT_HAVE_XSC(rename) */
#if __CRT_HAVE_XSC(renameat)
__CDECLARE_XSC(,__errno_t,renameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path),(__oldfd,__oldname,__newfd,__newname_or_path))
#endif /* __CRT_HAVE_XSC(renameat) */
#if __CRT_HAVE_XSC(renameat2)
/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,renameat2,(__fd_t __olddirfd, char const *__oldpath, __fd_t __newdirfd, char const *__newpath, __atflag_t __flags),(__olddirfd,__oldpath,__newdirfd,__newpath,__flags))
#endif /* __CRT_HAVE_XSC(renameat2) */
#if __CRT_HAVE_XSC(request_key)
__CDECLARE_XSC(,__errno_t,request_key,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(request_key) */
#if __CRT_HAVE_XSC(restart_syscall)
__CDECLARE_XSC(,__errno_t,restart_syscall,(void),())
#endif /* __CRT_HAVE_XSC(restart_syscall) */
#if __CRT_HAVE_XSC(rmdir)
__CDECLARE_XSC(,__errno_t,rmdir,(char const *__path),(__path))
#endif /* __CRT_HAVE_XSC(rmdir) */
#if __CRT_HAVE_XSC(rt_sigaction)
__CDECLARE_XSC(,__errno_t,rt_sigaction,(__signo_t __signo, struct __kernel_sigaction const *__act, struct __kernel_sigaction *__oact, __size_t __sigsetsize),(__signo,__act,__oact,__sigsetsize))
#endif /* __CRT_HAVE_XSC(rt_sigaction) */
#if __CRT_HAVE_XSC(rt_sigpending)
__CDECLARE_XSC(,__errno_t,rt_sigpending,(struct __sigset_struct *__set, __size_t __sigsetsize),(__set,__sigsetsize))
#endif /* __CRT_HAVE_XSC(rt_sigpending) */
#if __CRT_HAVE_XSC(rt_sigprocmask)
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE_XSC(,__errno_t,rt_sigprocmask,(__syscall_ulong_t __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset, __size_t __sigsetsize),(__how,__set,__oset,__sigsetsize))
#endif /* __CRT_HAVE_XSC(rt_sigprocmask) */
#if __CRT_HAVE_XSC(rt_sigqueueinfo)
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
__CDECLARE_XSC(,__errno_t,rt_sigqueueinfo,(__pid_t __pid, __signo_t __usigno, struct __siginfo_struct const *__uinfo),(__pid,__usigno,__uinfo))
#endif /* __CRT_HAVE_XSC(rt_sigqueueinfo) */
#if __CRT_HAVE_XSC(rt_sigsuspend)
/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__CDECLARE_XSC(,__errno_t,rt_sigsuspend,(struct __sigset_struct const *__set, __size_t __sigsetsize),(__set,__sigsetsize))
#endif /* __CRT_HAVE_XSC(rt_sigsuspend) */
#if __CRT_HAVE_XSC(rt_sigtimedwait)
__CDECLARE_XSC(,__syscall_slong_t,rt_sigtimedwait,(struct __sigset_struct const *__set, struct __siginfo_struct *__info, struct timespec const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* __CRT_HAVE_XSC(rt_sigtimedwait) */
#if __CRT_HAVE_XSC(rt_tgsigqueueinfo)
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
__CDECLARE_XSC(,__errno_t,rt_tgsigqueueinfo,(__pid_t __pid, __pid_t __tid, __signo_t __usigno, struct __siginfo_struct const *__uinfo),(__pid,__tid,__usigno,__uinfo))
#endif /* __CRT_HAVE_XSC(rt_tgsigqueueinfo) */
#if __CRT_HAVE_XSC(sched_get_priority_max)
__CDECLARE_XSC(,__syscall_slong_t,sched_get_priority_max,(__syscall_ulong_t __algorithm),(__algorithm))
#endif /* __CRT_HAVE_XSC(sched_get_priority_max) */
#if __CRT_HAVE_XSC(sched_get_priority_min)
__CDECLARE_XSC(,__syscall_slong_t,sched_get_priority_min,(__syscall_ulong_t __algorithm),(__algorithm))
#endif /* __CRT_HAVE_XSC(sched_get_priority_min) */
#if __CRT_HAVE_XSC(sched_getaffinity)
__CDECLARE_XSC(,__errno_t,sched_getaffinity,(__pid_t __pid, __size_t __cpusetsize, struct __cpu_set_struct *__cpuset),(__pid,__cpusetsize,__cpuset))
#endif /* __CRT_HAVE_XSC(sched_getaffinity) */
#if __CRT_HAVE_XSC(sched_getattr)
__CDECLARE_XSC(,__errno_t,sched_getattr,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(sched_getattr) */
#if __CRT_HAVE_XSC(sched_getparam)
__CDECLARE_XSC(,__errno_t,sched_getparam,(__pid_t __pid, struct sched_param *__param),(__pid,__param))
#endif /* __CRT_HAVE_XSC(sched_getparam) */
#if __CRT_HAVE_XSC(sched_getscheduler)
__CDECLARE_XSC(,__syscall_slong_t,sched_getscheduler,(__pid_t __pid),(__pid))
#endif /* __CRT_HAVE_XSC(sched_getscheduler) */
#if __CRT_HAVE_XSC(sched_rr_get_interval)
__CDECLARE_XSC(,__errno_t,sched_rr_get_interval,(__pid_t __pid, struct timespec *__ts),(__pid,__ts))
#endif /* __CRT_HAVE_XSC(sched_rr_get_interval) */
#if __CRT_HAVE_XSC(sched_setaffinity)
__CDECLARE_XSC(,__errno_t,sched_setaffinity,(__pid_t __pid, __size_t __cpusetsize, struct __cpu_set_struct const *__cpuset),(__pid,__cpusetsize,__cpuset))
#endif /* __CRT_HAVE_XSC(sched_setaffinity) */
#if __CRT_HAVE_XSC(sched_setattr)
__CDECLARE_XSC(,__errno_t,sched_setattr,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(sched_setattr) */
#if __CRT_HAVE_XSC(sched_setparam)
__CDECLARE_XSC(,__errno_t,sched_setparam,(__pid_t __pid, struct sched_param const *__param),(__pid,__param))
#endif /* __CRT_HAVE_XSC(sched_setparam) */
#if __CRT_HAVE_XSC(sched_setscheduler)
/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
__CDECLARE_XSC(,__errno_t,sched_setscheduler,(__pid_t __pid, __syscall_ulong_t __policy, struct sched_param const *__param),(__pid,__policy,__param))
#endif /* __CRT_HAVE_XSC(sched_setscheduler) */
#if __CRT_HAVE_XSC(sched_yield)
__CDECLARE_XSC(,__errno_t,sched_yield,(void),())
#endif /* __CRT_HAVE_XSC(sched_yield) */
#if __CRT_HAVE_XSC(seccomp)
__CDECLARE_XSC(,__errno_t,seccomp,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(seccomp) */
#if __CRT_HAVE_XSC(select)
__CDECLARE_XSC(,__ssize_t,select,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct timeval *__timeout),(__nfds,__readfds,__writefds,__exceptfds,__timeout))
#endif /* __CRT_HAVE_XSC(select) */
#if __CRT_HAVE_XSC(semctl)
__CDECLARE_XSC(,__errno_t,semctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(semctl) */
#if __CRT_HAVE_XSC(semget)
__CDECLARE_XSC(,__errno_t,semget,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(semget) */
#if __CRT_HAVE_XSC(semop)
__CDECLARE_XSC(,__errno_t,semop,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(semop) */
#if __CRT_HAVE_XSC(semtimedop)
__CDECLARE_XSC(,__errno_t,semtimedop,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(semtimedop) */
#if __CRT_HAVE_XSC(send)
/* Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @return: * : [<= bufsize] The actual # of send bytes */
__CDECLARE_XSC(,__ssize_t,send,(__fd_t __sockfd, void const *__buf, __size_t __bufsize, __syscall_ulong_t __msg_flags),(__sockfd,__buf,__bufsize,__msg_flags))
#endif /* __CRT_HAVE_XSC(send) */
#if __CRT_HAVE_XSC(sendfile)
/* Read up to `num_bytes' from `infd', and write that data to `outfd'
 * Files must be opened with the relevant access permissions (same as
 * would be enforced by `read(2)' and `write(2)')
 * When `pin_offset != NULL', the pointed-to location is used to track
 * the read-position in `infd'. Note that in the event that writing to
 * this address faults, data may  have still been written to  `outfd',
 * so be sure to have this point to writable memory.
 * @param: outfd:      Output file descriptor
 * @param: infd:       Input file descriptor
 * @param: pin_offset: If non-NULL, position from which to start reading,
 *                     and updated to reflect  how much could be  copied.
 * @param: num_bytes:  The max number of bytes to transfer
 * @return: * :        The actual number of bytes transferred */
__CDECLARE_XSC(,__ssize_t,sendfile,(__fd_t __outfd, __fd_t __infd, __syscall_ulong_t *__pin_offset, __size_t __num_bytes),(__outfd,__infd,__pin_offset,__num_bytes))
#endif /* __CRT_HAVE_XSC(sendfile) */
#if __CRT_HAVE_XSC(sendmmsg)
/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
__CDECLARE_XSC(,__ssize_t,sendmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __msg_flags),(__sockfd,__vmessages,__vlen,__msg_flags))
#endif /* __CRT_HAVE_XSC(sendmmsg) */
#if __CRT_HAVE_XSC(sendmsg)
/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
__CDECLARE_XSC(,__ssize_t,sendmsg,(__fd_t __sockfd, struct msghdr const *__message, __syscall_ulong_t __msg_flags),(__sockfd,__message,__msg_flags))
#endif /* __CRT_HAVE_XSC(sendmsg) */
#if __CRT_HAVE_XSC(sendto)
/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for            `send(sockfd, buf, bufsize, msg_flags)'
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @throw: E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
 * @return: * : [<= bufsize] The actual # of send bytes */
__CDECLARE_XSC(,__ssize_t,sendto,(__fd_t __sockfd, void const *__buf, __size_t __bufsize, __syscall_ulong_t __msg_flags, struct sockaddr const *__addr, __socklen_t __addr_len),(__sockfd,__buf,__bufsize,__msg_flags,__addr,__addr_len))
#endif /* __CRT_HAVE_XSC(sendto) */
#if __CRT_HAVE_XSC(set_mempolicy)
__CDECLARE_XSC(,__errno_t,set_mempolicy,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(set_mempolicy) */
#if __CRT_HAVE_XSC(set_robust_list)
__CDECLARE_XSC(,__errno_t,set_robust_list,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(set_robust_list) */
#if __CRT_HAVE_XSC(set_tid_address)
__CDECLARE_XSC(,__pid_t,set_tid_address,(__pid_t *__tidptr),(__tidptr))
#endif /* __CRT_HAVE_XSC(set_tid_address) */
#if __CRT_HAVE_XSC(setdomainname)
__CDECLARE_XSC(,__errno_t,setdomainname,(char const *__name, __size_t __len),(__name,__len))
#endif /* __CRT_HAVE_XSC(setdomainname) */
#if __CRT_HAVE_XSC(setfsgid)
/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
__CDECLARE_XSC(,__errno_t,setfsgid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_XSC(setfsgid) */
#if __CRT_HAVE_XSC(setfsuid)
/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
__CDECLARE_XSC(,__errno_t,setfsuid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_XSC(setfsuid) */
#if __CRT_HAVE_XSC(setgid)
/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
__CDECLARE_XSC(,__errno_t,setgid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_XSC(setgid) */
#if __CRT_HAVE_XSC(setgroups)
__CDECLARE_XSC(,__errno_t,setgroups,(__size_t __count, __gid_t const *__groups),(__count,__groups))
#endif /* __CRT_HAVE_XSC(setgroups) */
#if __CRT_HAVE_XSC(sethostname)
__CDECLARE_XSC(,__errno_t,sethostname,(char const *__name, __size_t __len),(__name,__len))
#endif /* __CRT_HAVE_XSC(sethostname) */
#if __CRT_HAVE_XSC(setitimer)
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
__CDECLARE_XSC(,__errno_t,setitimer,(__syscall_ulong_t __which, struct itimerval const *__newval, struct itimerval *__oldval),(__which,__newval,__oldval))
#endif /* __CRT_HAVE_XSC(setitimer) */
#if __CRT_HAVE_XSC(setns)
__CDECLARE_XSC(,__errno_t,setns,(__fd_t __fd, __syscall_ulong_t __nstype),(__fd,__nstype))
#endif /* __CRT_HAVE_XSC(setns) */
#if __CRT_HAVE_XSC(setpgid)
__CDECLARE_XSC(,__errno_t,setpgid,(__pid_t __pid, __pid_t __pgid),(__pid,__pgid))
#endif /* __CRT_HAVE_XSC(setpgid) */
#if __CRT_HAVE_XSC(setpriority)
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
__CDECLARE_XSC(,__errno_t,setpriority,(__syscall_ulong_t __which, __id_t __who, __syscall_ulong_t __value),(__which,__who,__value))
#endif /* __CRT_HAVE_XSC(setpriority) */
#if __CRT_HAVE_XSC(setregid)
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
__CDECLARE_XSC(,__errno_t,setregid,(__gid_t __rgid, __gid_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_XSC(setregid) */
#if __CRT_HAVE_XSC(setresgid)
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
__CDECLARE_XSC(,__errno_t,setresgid,(__gid_t __rgid, __gid_t __egid, __gid_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_XSC(setresgid) */
#if __CRT_HAVE_XSC(setresuid)
/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
__CDECLARE_XSC(,__errno_t,setresuid,(__uid_t __ruid, __uid_t __euid, __uid_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_XSC(setresuid) */
#if __CRT_HAVE_XSC(setreuid)
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
__CDECLARE_XSC(,__errno_t,setreuid,(__uid_t __ruid, __uid_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_XSC(setreuid) */
#if __CRT_HAVE_XSC(setrlimit)
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
__CDECLARE_XSC(,__errno_t,setrlimit,(__syscall_ulong_t __resource, struct rlimit const *__rlimits),(__resource,__rlimits))
#endif /* __CRT_HAVE_XSC(setrlimit) */
#if __CRT_HAVE_XSC(setsid)
__CDECLARE_XSC(,__pid_t,setsid,(void),())
#endif /* __CRT_HAVE_XSC(setsid) */
#if __CRT_HAVE_XSC(setsockopt)
/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
__CDECLARE_XSC(,__errno_t,setsockopt,(__fd_t __sockfd, __syscall_ulong_t __level, __syscall_ulong_t __optname, void const *__optval, __socklen_t __optlen),(__sockfd,__level,__optname,__optval,__optlen))
#endif /* __CRT_HAVE_XSC(setsockopt) */
#if __CRT_HAVE_XSC(settimeofday)
__CDECLARE_XSC(,__errno_t,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_XSC(settimeofday) */
#if __CRT_HAVE_XSC(setuid)
/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
__CDECLARE_XSC(,__errno_t,setuid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_XSC(setuid) */
#if __CRT_HAVE_XSC(setxattr)
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
__CDECLARE_XSC(,__errno_t,setxattr,(char const *__path, char const *__name, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__path,__name,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_XSC(setxattr) */
#if __CRT_HAVE_XSC(shmat)
__CDECLARE_XSC(,__errno_t,shmat,(__syscall_ulong_t __shmid, void const *__shmaddr, __syscall_ulong_t __shmflg),(__shmid,__shmaddr,__shmflg))
#endif /* __CRT_HAVE_XSC(shmat) */
#if __CRT_HAVE_XSC(shmctl)
__CDECLARE_XSC(,__errno_t,shmctl,(__syscall_ulong_t __shmid, __syscall_ulong_t __cmd, struct shmid_ds *__buf),(__shmid,__cmd,__buf))
#endif /* __CRT_HAVE_XSC(shmctl) */
#if __CRT_HAVE_XSC(shmdt)
__CDECLARE_XSC(,__errno_t,shmdt,(void const *__shmaddr),(__shmaddr))
#endif /* __CRT_HAVE_XSC(shmdt) */
#if __CRT_HAVE_XSC(shmget)
__CDECLARE_XSC(,__errno_t,shmget,(__key_t __key, __size_t __size, __syscall_ulong_t __shmflg),(__key,__size,__shmflg))
#endif /* __CRT_HAVE_XSC(shmget) */
#if __CRT_HAVE_XSC(shutdown)
/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
__CDECLARE_XSC(,__errno_t,shutdown,(__fd_t __sockfd, __syscall_ulong_t __how),(__sockfd,__how))
#endif /* __CRT_HAVE_XSC(shutdown) */
#if __CRT_HAVE_XSC(sigaltstack)
__CDECLARE_XSC(,__errno_t,sigaltstack,(struct sigaltstack const *__ss, struct sigaltstack *__oss),(__ss,__oss))
#endif /* __CRT_HAVE_XSC(sigaltstack) */
#if __CRT_HAVE_XSC(signalfd)
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
__CDECLARE_XSC(,__errno_t,signalfd,(__fd_t __fd, struct __sigset_struct const *__sigmask, __size_t __sigmasksize),(__fd,__sigmask,__sigmasksize))
#endif /* __CRT_HAVE_XSC(signalfd) */
#if __CRT_HAVE_XSC(signalfd4)
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
__CDECLARE_XSC(,__errno_t,signalfd4,(__fd_t __fd, struct __sigset_struct const *__sigmask, __size_t __sigmasksize, __syscall_ulong_t __flags),(__fd,__sigmask,__sigmasksize,__flags))
#endif /* __CRT_HAVE_XSC(signalfd4) */
#if __CRT_HAVE_XSC(socket)
/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
__CDECLARE_XSC(,__fd_t,socket,(__syscall_ulong_t __domain, __syscall_ulong_t __type, __syscall_ulong_t __protocol),(__domain,__type,__protocol))
#endif /* __CRT_HAVE_XSC(socket) */
#if __CRT_HAVE_XSC(socketpair)
/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
__CDECLARE_XSC(,__errno_t,socketpair,(__syscall_ulong_t __domain, __syscall_ulong_t __type, __syscall_ulong_t __protocol, __fd_t *__fds),(__domain,__type,__protocol,__fds))
#endif /* __CRT_HAVE_XSC(socketpair) */
#if __CRT_HAVE_XSC(splice)
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
__CDECLARE_XSC(,__ssize_t,splice,(__fd_t __fdin, __uint64_t *__offin, __fd_t __fdout, __uint64_t *__offout, __size_t __length, __syscall_ulong_t __flags),(__fdin,__offin,__fdout,__offout,__length,__flags))
#endif /* __CRT_HAVE_XSC(splice) */
#if __CRT_HAVE_XSC(stat)
__CDECLARE_XSC(,__errno_t,stat,(char const *__filename, struct linux_stat *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(stat) */
#if __CRT_HAVE_XSC(statfs)
__CDECLARE_XSC(,__errno_t,statfs,(char const *__file, struct statfs *__buf),(__file,__buf))
#endif /* __CRT_HAVE_XSC(statfs) */
#if __CRT_HAVE_XSC(swapoff)
__CDECLARE_XSC(,__errno_t,swapoff,(char const *__pathname),(__pathname))
#endif /* __CRT_HAVE_XSC(swapoff) */
#if __CRT_HAVE_XSC(swapon)
/* @param: swapflags: Set of `SWAP_FLAG_*' */
__CDECLARE_XSC(,__errno_t,swapon,(char const *__pathname, __syscall_ulong_t __swapflags),(__pathname,__swapflags))
#endif /* __CRT_HAVE_XSC(swapon) */
#if __CRT_HAVE_XSC(symlink)
__CDECLARE_XSC(,__errno_t,symlink,(char const *__link_text, char const *__target_path),(__link_text,__target_path))
#endif /* __CRT_HAVE_XSC(symlink) */
#if __CRT_HAVE_XSC(symlinkat)
__CDECLARE_XSC(,__errno_t,symlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path),(__link_text,__tofd,__target_path))
#endif /* __CRT_HAVE_XSC(symlinkat) */
#if __CRT_HAVE_XSC(sync)
__CDECLARE_XSC(,__errno_t,sync,(void),())
#endif /* __CRT_HAVE_XSC(sync) */
#if __CRT_HAVE_XSC(sync_file_range)
/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
__CDECLARE_XSC(,__errno_t,sync_file_range,(__fd_t __fd, __uint64_t __offset, __uint64_t __count, __syscall_ulong_t __flags),(__fd,__offset,__count,__flags))
#endif /* __CRT_HAVE_XSC(sync_file_range) */
#if __CRT_HAVE_XSC(syncfs)
__CDECLARE_XSC(,__errno_t,syncfs,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_XSC(syncfs) */
#if __CRT_HAVE_XSC(sysinfo)
__CDECLARE_XSC(,__errno_t,sysinfo,(struct sysinfo *__info),(__info))
#endif /* __CRT_HAVE_XSC(sysinfo) */
#if __CRT_HAVE_XSC(syslog)
__CDECLARE_XSC(,__ssize_t,syslog,(__syscall_ulong_t __level, char const *__str, __size_t __len),(__level,__str,__len))
#endif /* __CRT_HAVE_XSC(syslog) */
#if __CRT_HAVE_XSC(tee)
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
__CDECLARE_XSC(,__ssize_t,tee,(__fd_t __fdin, __fd_t __fdout, __size_t __length, __syscall_ulong_t __flags),(__fdin,__fdout,__length,__flags))
#endif /* __CRT_HAVE_XSC(tee) */
#if __CRT_HAVE_XSC(tgkill)
__CDECLARE_XSC(,__errno_t,tgkill,(__pid_t __pid, __pid_t __tid, __signo_t __signo),(__pid,__tid,__signo))
#endif /* __CRT_HAVE_XSC(tgkill) */
#if __CRT_HAVE_XSC(time)
__CDECLARE_XSC(,__time32_t,time,(__time32_t *__timer),(__timer))
#endif /* __CRT_HAVE_XSC(time) */
#if __CRT_HAVE_XSC(timer_create)
__CDECLARE_XSC(,__errno_t,timer_create,(__clockid_t __clock_id, struct sigevent *__evp, __timer_t *__timerid),(__clock_id,__evp,__timerid))
#endif /* __CRT_HAVE_XSC(timer_create) */
#if __CRT_HAVE_XSC(timer_delete)
__CDECLARE_XSC(,__errno_t,timer_delete,(__timer_t __timerid),(__timerid))
#endif /* __CRT_HAVE_XSC(timer_delete) */
#if __CRT_HAVE_XSC(timer_getoverrun)
__CDECLARE_XSC(,__syscall_slong_t,timer_getoverrun,(__timer_t __timerid),(__timerid))
#endif /* __CRT_HAVE_XSC(timer_getoverrun) */
#if __CRT_HAVE_XSC(timer_gettime)
__CDECLARE_XSC(,__errno_t,timer_gettime,(__timer_t __timerid, struct itimerspec *__value),(__timerid,__value))
#endif /* __CRT_HAVE_XSC(timer_gettime) */
#if __CRT_HAVE_XSC(timer_settime)
/* @param: flags: Set of `0 | TIMER_ABSTIME' */
__CDECLARE_XSC(,__errno_t,timer_settime,(__timer_t __timerid, __syscall_ulong_t __flags, struct itimerspec const *__value, struct itimerspec *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* __CRT_HAVE_XSC(timer_settime) */
#if __CRT_HAVE_XSC(timerfd_create)
/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
__CDECLARE_XSC(,__fd_t,timerfd_create,(__clockid_t __clock_id, __syscall_ulong_t __flags),(__clock_id,__flags))
#endif /* __CRT_HAVE_XSC(timerfd_create) */
#if __CRT_HAVE_XSC(timerfd_gettime)
/* Return the next expiration time of UFD */
__CDECLARE_XSC(,__errno_t,timerfd_gettime,(__fd_t __timerfd, struct itimerspec *__otmr),(__timerfd,__otmr))
#endif /* __CRT_HAVE_XSC(timerfd_gettime) */
#if __CRT_HAVE_XSC(timerfd_settime)
/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
__CDECLARE_XSC(,__errno_t,timerfd_settime,(__fd_t __timerfd, __syscall_ulong_t __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr),(__timerfd,__flags,__utmr,__otmr))
#endif /* __CRT_HAVE_XSC(timerfd_settime) */
#if __CRT_HAVE_XSC(times)
__CDECLARE_XSC(,__clock_t,times,(struct tms *__buf),(__buf))
#endif /* __CRT_HAVE_XSC(times) */
#if __CRT_HAVE_XSC(tkill)
__CDECLARE_XSC(,__errno_t,tkill,(__pid_t __tid, __signo_t __signo),(__tid,__signo))
#endif /* __CRT_HAVE_XSC(tkill) */
#if __CRT_HAVE_XSC(truncate)
__CDECLARE_XSC(,__errno_t,truncate,(char const *__filename, __syscall_ulong_t __length),(__filename,__length))
#endif /* __CRT_HAVE_XSC(truncate) */
#if __CRT_HAVE_XSC(umask)
__CDECLARE_XSC(,__mode_t,umask,(__mode_t __mode),(__mode))
#endif /* __CRT_HAVE_XSC(umask) */
#if __CRT_HAVE_XSC(umount)
__CDECLARE_XSC(,__errno_t,umount,(char const *__special_file),(__special_file))
#endif /* __CRT_HAVE_XSC(umount) */
#if __CRT_HAVE_XSC(umount2)
__CDECLARE_XSC(,__errno_t,umount2,(char const *__special_file, __syscall_ulong_t __flags),(__special_file,__flags))
#endif /* __CRT_HAVE_XSC(umount2) */
#if __CRT_HAVE_XSC(uname)
__CDECLARE_XSC(,__errno_t,uname,(struct utsname *__name),(__name))
#endif /* __CRT_HAVE_XSC(uname) */
#if __CRT_HAVE_XSC(unlink)
__CDECLARE_XSC(,__errno_t,unlink,(char const *__filename),(__filename))
#endif /* __CRT_HAVE_XSC(unlink) */
#if __CRT_HAVE_XSC(unlinkat)
/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,unlinkat,(__fd_t __dirfd, char const *__name, __atflag_t __flags),(__dirfd,__name,__flags))
#endif /* __CRT_HAVE_XSC(unlinkat) */
#if __CRT_HAVE_XSC(unshare)
/* param: what: Set of `CLONE_*' */
__CDECLARE_XSC(,__errno_t,unshare,(__syscall_ulong_t __what),(__what))
#endif /* __CRT_HAVE_XSC(unshare) */
#if __CRT_HAVE_XSC(uselib)
__CDECLARE_XSC(,__errno_t,uselib,(char const *__library),(__library))
#endif /* __CRT_HAVE_XSC(uselib) */
#if __CRT_HAVE_XSC(userfaultfd)
__CDECLARE_XSC(,__fd_t,userfaultfd,(__syscall_ulong_t __flags),(__flags))
#endif /* __CRT_HAVE_XSC(userfaultfd) */
#if __CRT_HAVE_XSC(ustat)
__CDECLARE_XSC(,__errno_t,ustat,(__dev_t __dev, struct ustat *__ubuf),(__dev,__ubuf))
#endif /* __CRT_HAVE_XSC(ustat) */
#if __CRT_HAVE_XSC(utime)
/* @param: times: When NULL, set the current time */
__CDECLARE_XSC(,__errno_t,utime,(char const *__filename, struct utimbuf const *__times),(__filename,__times))
#endif /* __CRT_HAVE_XSC(utime) */
#if __CRT_HAVE_XSC(utimensat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,utimensat,(__fd_t __dirfd, char const *__filename, struct timespec const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* __CRT_HAVE_XSC(utimensat) */
#if __CRT_HAVE_XSC(utimes)
/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
__CDECLARE_XSC(,__errno_t,utimes,(char const *__filename, struct timeval const *__times),(__filename,__times))
#endif /* __CRT_HAVE_XSC(utimes) */
#if __CRT_HAVE_XSC(vfork)
/* Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `exit(2)'       Terminate the child process
 *   - `exit_group(2)' Terminate the child process
 *   - `execve(2)'     Create a new VM that is populated with the specified process
 *                     image. The parent process will  only be resumed in case  the
 *                     new  program image could  be loaded successfully. Otherwise,
 *                     the call  to  `execve(2)'  returns normally  in  the  child.
 *                     Other functions from the exec()-family behave the same
 * 
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 * 
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
__CDECLARE_XSC(,__pid_t,vfork,(void),())
#endif /* __CRT_HAVE_XSC(vfork) */
#if __CRT_HAVE_XSC(vhangup)
__CDECLARE_XSC(,__errno_t,vhangup,(void),())
#endif /* __CRT_HAVE_XSC(vhangup) */
#if __CRT_HAVE_XSC(vmsplice)
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
__CDECLARE_XSC(,__ssize_t,vmsplice,(__fd_t __fdout, struct iovec const *__iov, __size_t __count, __syscall_ulong_t __flags),(__fdout,__iov,__count,__flags))
#endif /* __CRT_HAVE_XSC(vmsplice) */
#if __CRT_HAVE_XSC(wait4)
/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CDECLARE_XSC(,__pid_t,wait4,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options, struct rusage *__usage),(__pid,__stat_loc,__options,__usage))
#endif /* __CRT_HAVE_XSC(wait4) */
#if __CRT_HAVE_XSC(waitid)
/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
__CDECLARE_XSC(,__errno_t,waitid,(__syscall_ulong_t __idtype, __id_t __id, struct __siginfo_struct *__infop, __syscall_ulong_t __options, struct rusage *__ru),(__idtype,__id,__infop,__options,__ru))
#endif /* __CRT_HAVE_XSC(waitid) */
#if __CRT_HAVE_XSC(write)
/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CDECLARE_XSC(,__ssize_t,write,(__fd_t __fd, void const *__buf, __size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* __CRT_HAVE_XSC(write) */
#if __CRT_HAVE_XSC(writev)
/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
__CDECLARE_XSC(,__ssize_t,writev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_XSC(writev) */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("timezone")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_SYSCALL_H */
