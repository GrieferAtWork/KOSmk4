/* HASH CRC-32:0x4c4be17f */
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
#ifndef _KOS_BITS_SYSCALL_H
#define _KOS_BITS_SYSCALL_H 1

#include <__stdinc.h>
#include <kos/asm/syscall.h>

#include <bits/iovec-struct.h>
#include <bits/itimerspec.h>
#include <bits/siginfo-struct.h>
#include <bits/timespec.h>
#include <bits/timeval.h>
#include <bits/types.h>


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
#pragma push_macro("timezone")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef timezone

struct __fd_set_struct;
struct __siginfo_struct;
struct __sigset_struct;
struct __timespec;
struct iovec;
struct itimerspec;
struct linux64_stat32;
struct linux_stat32;
struct mmsghdr;
struct pollfd;
struct rusage;
struct timespec;
struct timeval;
struct timezone;

#if __CRT_HAVE_SC(accept)
__CDECLARE_SC(,__errno_t,accept,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(accept) */
#if __CRT_HAVE_SC(bdflush)
__CDECLARE_SC(,__errno_t,bdflush,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(bdflush) */
#if __CRT_HAVE_SC(chown)
__CDECLARE_SC(,__errno_t,chown,(char const *__filename, __uid_t __owner, __gid_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_SC(chown) */
#if __CRT_HAVE_SC(clock_getres)
__CDECLARE_SC(,__errno_t,clock_getres,(__clockid_t __clock_id, struct timespec *__res),(__clock_id,__res))
#endif /* __CRT_HAVE_SC(clock_getres) */
#if __CRT_HAVE_SC(clock_gettime)
__CDECLARE_SC(,__errno_t,clock_gettime,(__clockid_t __clock_id, struct timespec *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_SC(clock_gettime) */
#if __CRT_HAVE_SC(clock_nanosleep)
__CDECLARE_SC(,__errno_t,clock_nanosleep,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct timespec const *__requested_time, struct timespec *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* __CRT_HAVE_SC(clock_nanosleep) */
#if __CRT_HAVE_SC(clock_settime)
__CDECLARE_SC(,__errno_t,clock_settime,(__clockid_t __clock_id, struct timespec const *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_SC(clock_settime) */
#if __CRT_HAVE_SC(clone)
__CDECLARE_SC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __uintptr_t __newtls, __pid_t *__ctid),(__flags,__child_stack,__ptid,__newtls,__ctid))
#endif /* __CRT_HAVE_SC(clone) */
#if __CRT_HAVE_SC(fchown)
__CDECLARE_SC(,__errno_t,fchown,(__fd_t __fd, __uid_t __owner, __gid_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_SC(fchown) */
#if __CRT_HAVE_SC(futex)
__CDECLARE_SC(,__syscall_slong_t,futex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct timespec const *__timeout_or_val2, __uint32_t *__uaddr2, __uint32_t __val3),(__uaddr,__futex_op,__val,__timeout_or_val2,__uaddr2,__val3))
#endif /* __CRT_HAVE_SC(futex) */
#if __CRT_HAVE_SC(futimesat)
__CDECLARE_SC(,__errno_t,futimesat,(__fd_t __dirfd, __const char *__filename, struct timeval const *__times),(__dirfd,__filename,__times))
#endif /* __CRT_HAVE_SC(futimesat) */
#if __CRT_HAVE_SC(getegid)
__CDECLARE_SC(,__gid_t,getegid,(void),())
#endif /* __CRT_HAVE_SC(getegid) */
#if __CRT_HAVE_SC(geteuid)
__CDECLARE_SC(,__uid_t,geteuid,(void),())
#endif /* __CRT_HAVE_SC(geteuid) */
#if __CRT_HAVE_SC(getgid)
__CDECLARE_SC(,__gid_t,getgid,(void),())
#endif /* __CRT_HAVE_SC(getgid) */
#if __CRT_HAVE_SC(getgroups)
__CDECLARE_SC(,__errno_t,getgroups,(__size_t __size, __gid_t *__list),(__size,__list))
#endif /* __CRT_HAVE_SC(getgroups) */
#if __CRT_HAVE_SC(getresgid)
__CDECLARE_SC(,__errno_t,getresgid,(__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_SC(getresgid) */
#if __CRT_HAVE_SC(getresuid)
__CDECLARE_SC(,__errno_t,getresuid,(__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_SC(getresuid) */
#if __CRT_HAVE_SC(gettimeofday)
__CDECLARE_SC(,__errno_t,gettimeofday,(struct timeval *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_SC(gettimeofday) */
#if __CRT_HAVE_SC(getuid)
__CDECLARE_SC(,__uid_t,getuid,(void),())
#endif /* __CRT_HAVE_SC(getuid) */
#if __CRT_HAVE_SC(lchown)
__CDECLARE_SC(,__errno_t,lchown,(char const *__filename, __uid_t __owner, __gid_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_SC(lchown) */
#if __CRT_HAVE_SC(linux_fstat32)
__CDECLARE_SC(,__errno_t,linux_fstat32,(__fd_t __fd, struct linux_stat32 *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_SC(linux_fstat32) */
#if __CRT_HAVE_SC(linux_lstat32)
__CDECLARE_SC(,__errno_t,linux_lstat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(linux_lstat32) */
#if __CRT_HAVE_SC(linux_newfstatat)
__CDECLARE_SC(,__errno_t,linux_newfstatat,(__fd_t __dirfd, char const *__filename, struct linux64_stat32 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* __CRT_HAVE_SC(linux_newfstatat) */
#if __CRT_HAVE_SC(linux_stat32)
__CDECLARE_SC(,__errno_t,linux_stat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_SC(linux_stat32) */
#if __CRT_HAVE_SC(lseek)
__CDECLARE_SC(,__syscall_slong_t,lseek,(__fd_t __fd, __syscall_slong_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* __CRT_HAVE_SC(lseek) */
#if __CRT_HAVE_SC(mmap)
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
__CDECLARE_SC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* __CRT_HAVE_SC(mmap) */
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
#if __CRT_HAVE_SC(nanosleep)
__CDECLARE_SC(,__errno_t,nanosleep,(struct timespec const *__req, struct timespec *__rem),(__req,__rem))
#endif /* __CRT_HAVE_SC(nanosleep) */
#if __CRT_HAVE_SC(oldwait4)
__CDECLARE_SC(,__pid_t,oldwait4,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options, struct rusage *__usage),(__pid,__stat_loc,__options,__usage))
#endif /* __CRT_HAVE_SC(oldwait4) */
#if __CRT_HAVE_SC(ppoll)
__CDECLARE_SC(,__ssize_t,ppoll,(struct pollfd *__fds, __size_t __nfds, struct timespec const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* __CRT_HAVE_SC(ppoll) */
#if __CRT_HAVE_SC(preadv)
__CDECLARE_SC(,__ssize_t,preadv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_SC(preadv) */
#if __CRT_HAVE_SC(process_vm_readv)
__CDECLARE_SC(,__ssize_t,process_vm_readv,(__pid_t __pid, struct iovec const *__lvec, __size_t __liovcnt, struct iovec const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* __CRT_HAVE_SC(process_vm_readv) */
#if __CRT_HAVE_SC(process_vm_writev)
__CDECLARE_SC(,__ssize_t,process_vm_writev,(__pid_t __pid, struct iovec const *__lvec, __size_t __liovcnt, struct iovec const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* __CRT_HAVE_SC(process_vm_writev) */
#if __CRT_HAVE_SC(pselect6)
__CDECLARE_SC(,__ssize_t,pselect6,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct timespec const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#endif /* __CRT_HAVE_SC(pselect6) */
#if __CRT_HAVE_SC(pwritev)
__CDECLARE_SC(,__ssize_t,pwritev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_SC(pwritev) */
#if __CRT_HAVE_SC(readv)
__CDECLARE_SC(,__ssize_t,readv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_SC(readv) */
#if __CRT_HAVE_SC(recv)
__CDECLARE_SC(,__ssize_t,recv,(__fd_t __sockfd, void *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__sockfd,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_SC(recv) */
#if __CRT_HAVE_SC(recvmmsg)
__CDECLARE_SC(,__ssize_t,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct timespec *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#endif /* __CRT_HAVE_SC(recvmmsg) */
#if __CRT_HAVE_SC(rt_sigqueueinfo)
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,rt_sigqueueinfo,(__pid_t __tgid, __syscall_ulong_t __signo, struct __siginfo_struct const *__uinfo),(__tgid,__signo,__uinfo))
#endif /* __CRT_HAVE_SC(rt_sigqueueinfo) */
#if __CRT_HAVE_SC(rt_sigtimedwait)
__CDECLARE_SC(,__syscall_slong_t,rt_sigtimedwait,(struct __sigset_struct const *__set, struct __siginfo_struct *__info, struct timespec const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* __CRT_HAVE_SC(rt_sigtimedwait) */
#if __CRT_HAVE_SC(rt_tgsigqueueinfo)
/* @param: signo: One of `SIG*' */
__CDECLARE_SC(,__errno_t,rt_tgsigqueueinfo,(__pid_t __tgid, __pid_t __tid, __syscall_ulong_t __signo, struct __siginfo_struct const *__uinfo),(__tgid,__tid,__signo,__uinfo))
#endif /* __CRT_HAVE_SC(rt_tgsigqueueinfo) */
#if __CRT_HAVE_SC(sched_rr_get_interval)
__CDECLARE_SC(,__errno_t,sched_rr_get_interval,(__pid_t __pid, struct __timespec *__tms),(__pid,__tms))
#endif /* __CRT_HAVE_SC(sched_rr_get_interval) */
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
/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
__CDECLARE_SC(,__ssize_t,send,(__fd_t __sockfd, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__sockfd,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_SC(send) */
#if __CRT_HAVE_SC(setfsgid)
__CDECLARE_SC(,__errno_t,setfsgid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_SC(setfsgid) */
#if __CRT_HAVE_SC(setfsuid)
__CDECLARE_SC(,__errno_t,setfsuid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_SC(setfsuid) */
#if __CRT_HAVE_SC(setgid)
__CDECLARE_SC(,__errno_t,setgid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_SC(setgid) */
#if __CRT_HAVE_SC(setgroups)
__CDECLARE_SC(,__errno_t,setgroups,(__size_t __count, __gid_t const *__groups),(__count,__groups))
#endif /* __CRT_HAVE_SC(setgroups) */
#if __CRT_HAVE_SC(setregid)
__CDECLARE_SC(,__errno_t,setregid,(__gid_t __rgid, __gid_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_SC(setregid) */
#if __CRT_HAVE_SC(setresgid)
__CDECLARE_SC(,__errno_t,setresgid,(__gid_t __rgid, __gid_t __egid, __gid_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_SC(setresgid) */
#if __CRT_HAVE_SC(setresuid)
__CDECLARE_SC(,__errno_t,setresuid,(__uid_t __ruid, __uid_t __euid, __uid_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_SC(setresuid) */
#if __CRT_HAVE_SC(setreuid)
__CDECLARE_SC(,__errno_t,setreuid,(__uid_t __ruid, __uid_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_SC(setreuid) */
#if __CRT_HAVE_SC(settimeofday)
__CDECLARE_SC(,__errno_t,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_SC(settimeofday) */
#if __CRT_HAVE_SC(setuid)
__CDECLARE_SC(,__errno_t,setuid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_SC(setuid) */
#if __CRT_HAVE_SC(shmat)
__CDECLARE_SC(,__errno_t,shmat,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(shmat) */
#if __CRT_HAVE_SC(shmctl)
__CDECLARE_SC(,__errno_t,shmctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(shmctl) */
#if __CRT_HAVE_SC(shmdt)
__CDECLARE_SC(,__errno_t,shmdt,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(shmdt) */
#if __CRT_HAVE_SC(shmget)
__CDECLARE_SC(,__errno_t,shmget,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_SC(shmget) */
#if __CRT_HAVE_SC(timer_gettime)
__CDECLARE_SC(,__errno_t,timer_gettime,(__timer_t __timerid, struct itimerspec *__value),(__timerid,__value))
#endif /* __CRT_HAVE_SC(timer_gettime) */
#if __CRT_HAVE_SC(timer_settime)
__CDECLARE_SC(,__errno_t,timer_settime,(__timer_t __timerid, __syscall_ulong_t __flags, struct itimerspec const *__value, struct itimerspec *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* __CRT_HAVE_SC(timer_settime) */
#if __CRT_HAVE_SC(timerfd_gettime)
/* Return the next expiration time of UFD */
__CDECLARE_SC(,__errno_t,timerfd_gettime,(__fd_t __ufd, struct itimerspec *__otmr),(__ufd,__otmr))
#endif /* __CRT_HAVE_SC(timerfd_gettime) */
#if __CRT_HAVE_SC(timerfd_settime)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_SC(,__errno_t,timerfd_settime,(__fd_t __ufd, __syscall_ulong_t __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr),(__ufd,__flags,__utmr,__otmr))
#endif /* __CRT_HAVE_SC(timerfd_settime) */
#if __CRT_HAVE_SC(umount)
__CDECLARE_SC(,__errno_t,umount,(char const *__special_file),(__special_file))
#endif /* __CRT_HAVE_SC(umount) */
#if __CRT_HAVE_SC(utimensat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
__CDECLARE_SC(,__errno_t,utimensat,(__fd_t __dirfd, char const *__filename, struct timespec const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* __CRT_HAVE_SC(utimensat) */
#if __CRT_HAVE_SC(utimes)
__CDECLARE_SC(,__errno_t,utimes,(char const *__filename, struct timeval const *__times),(__filename,__times))
#endif /* __CRT_HAVE_SC(utimes) */
#if __CRT_HAVE_SC(vmsplice)
__CDECLARE_SC(,__ssize_t,vmsplice,(__fd_t __fdout, struct iovec const *__iov, __size_t __count, __syscall_ulong_t __flags),(__fdout,__iov,__count,__flags))
#endif /* __CRT_HAVE_SC(vmsplice) */
#if __CRT_HAVE_SC(waitid)
/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
__CDECLARE_SC(,__errno_t,waitid,(__syscall_ulong_t __idtype, __id_t __id, struct __siginfo_struct *__infop, __syscall_ulong_t __options, struct rusage *__ru),(__idtype,__id,__infop,__options,__ru))
#endif /* __CRT_HAVE_SC(waitid) */
#if __CRT_HAVE_SC(writev)
__CDECLARE_SC(,__ssize_t,writev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_SC(writev) */
#if __CRT_HAVE_XSC(accept)
__CDECLARE_XSC(,__errno_t,accept,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(accept) */
#if __CRT_HAVE_XSC(bdflush)
__CDECLARE_XSC(,__errno_t,bdflush,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(bdflush) */
#if __CRT_HAVE_XSC(chown)
__CDECLARE_XSC(,__errno_t,chown,(char const *__filename, __uid_t __owner, __gid_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_XSC(chown) */
#if __CRT_HAVE_XSC(clock_getres)
__CDECLARE_XSC(,__errno_t,clock_getres,(__clockid_t __clock_id, struct timespec *__res),(__clock_id,__res))
#endif /* __CRT_HAVE_XSC(clock_getres) */
#if __CRT_HAVE_XSC(clock_gettime)
__CDECLARE_XSC(,__errno_t,clock_gettime,(__clockid_t __clock_id, struct timespec *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_XSC(clock_gettime) */
#if __CRT_HAVE_XSC(clock_nanosleep)
__CDECLARE_XSC(,__errno_t,clock_nanosleep,(__clockid_t __clock_id, __syscall_ulong_t __flags, struct timespec const *__requested_time, struct timespec *__remaining),(__clock_id,__flags,__requested_time,__remaining))
#endif /* __CRT_HAVE_XSC(clock_nanosleep) */
#if __CRT_HAVE_XSC(clock_settime)
__CDECLARE_XSC(,__errno_t,clock_settime,(__clockid_t __clock_id, struct timespec const *__tp),(__clock_id,__tp))
#endif /* __CRT_HAVE_XSC(clock_settime) */
#if __CRT_HAVE_XSC(clone)
__CDECLARE_XSC(,__pid_t,clone,(__syscall_ulong_t __flags, void *__child_stack, __pid_t *__ptid, __uintptr_t __newtls, __pid_t *__ctid),(__flags,__child_stack,__ptid,__newtls,__ctid))
#endif /* __CRT_HAVE_XSC(clone) */
#if __CRT_HAVE_XSC(fchown)
__CDECLARE_XSC(,__errno_t,fchown,(__fd_t __fd, __uid_t __owner, __gid_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_XSC(fchown) */
#if __CRT_HAVE_XSC(futex)
__CDECLARE_XSC(,__syscall_slong_t,futex,(__uint32_t *__uaddr, __syscall_ulong_t __futex_op, __uint32_t __val, struct timespec const *__timeout_or_val2, __uint32_t *__uaddr2, __uint32_t __val3),(__uaddr,__futex_op,__val,__timeout_or_val2,__uaddr2,__val3))
#endif /* __CRT_HAVE_XSC(futex) */
#if __CRT_HAVE_XSC(futimesat)
__CDECLARE_XSC(,__errno_t,futimesat,(__fd_t __dirfd, __const char *__filename, struct timeval const *__times),(__dirfd,__filename,__times))
#endif /* __CRT_HAVE_XSC(futimesat) */
#if __CRT_HAVE_XSC(getegid)
__CDECLARE_XSC(,__gid_t,getegid,(void),())
#endif /* __CRT_HAVE_XSC(getegid) */
#if __CRT_HAVE_XSC(geteuid)
__CDECLARE_XSC(,__uid_t,geteuid,(void),())
#endif /* __CRT_HAVE_XSC(geteuid) */
#if __CRT_HAVE_XSC(getgid)
__CDECLARE_XSC(,__gid_t,getgid,(void),())
#endif /* __CRT_HAVE_XSC(getgid) */
#if __CRT_HAVE_XSC(getgroups)
__CDECLARE_XSC(,__errno_t,getgroups,(__size_t __size, __gid_t *__list),(__size,__list))
#endif /* __CRT_HAVE_XSC(getgroups) */
#if __CRT_HAVE_XSC(getresgid)
__CDECLARE_XSC(,__errno_t,getresgid,(__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_XSC(getresgid) */
#if __CRT_HAVE_XSC(getresuid)
__CDECLARE_XSC(,__errno_t,getresuid,(__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_XSC(getresuid) */
#if __CRT_HAVE_XSC(gettimeofday)
__CDECLARE_XSC(,__errno_t,gettimeofday,(struct timeval *__tv, struct timezone *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_XSC(gettimeofday) */
#if __CRT_HAVE_XSC(getuid)
__CDECLARE_XSC(,__uid_t,getuid,(void),())
#endif /* __CRT_HAVE_XSC(getuid) */
#if __CRT_HAVE_XSC(lchown)
__CDECLARE_XSC(,__errno_t,lchown,(char const *__filename, __uid_t __owner, __gid_t __group),(__filename,__owner,__group))
#endif /* __CRT_HAVE_XSC(lchown) */
#if __CRT_HAVE_XSC(linux_fstat32)
__CDECLARE_XSC(,__errno_t,linux_fstat32,(__fd_t __fd, struct linux_stat32 *__statbuf),(__fd,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_fstat32) */
#if __CRT_HAVE_XSC(linux_lstat32)
__CDECLARE_XSC(,__errno_t,linux_lstat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_lstat32) */
#if __CRT_HAVE_XSC(linux_newfstatat)
__CDECLARE_XSC(,__errno_t,linux_newfstatat,(__fd_t __dirfd, char const *__filename, struct linux64_stat32 *__statbuf, __atflag_t __flags),(__dirfd,__filename,__statbuf,__flags))
#endif /* __CRT_HAVE_XSC(linux_newfstatat) */
#if __CRT_HAVE_XSC(linux_stat32)
__CDECLARE_XSC(,__errno_t,linux_stat32,(char const *__filename, struct linux_stat32 *__statbuf),(__filename,__statbuf))
#endif /* __CRT_HAVE_XSC(linux_stat32) */
#if __CRT_HAVE_XSC(lseek)
__CDECLARE_XSC(,__syscall_slong_t,lseek,(__fd_t __fd, __syscall_slong_t __offset, __syscall_ulong_t __whence),(__fd,__offset,__whence))
#endif /* __CRT_HAVE_XSC(lseek) */
#if __CRT_HAVE_XSC(mmap)
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
__CDECLARE_XSC(,void *,mmap,(void *__addr, __size_t __len, __syscall_ulong_t __prot, __syscall_ulong_t __flags, __fd_t __fd, __syscall_ulong_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* __CRT_HAVE_XSC(mmap) */
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
#if __CRT_HAVE_XSC(nanosleep)
__CDECLARE_XSC(,__errno_t,nanosleep,(struct timespec const *__req, struct timespec *__rem),(__req,__rem))
#endif /* __CRT_HAVE_XSC(nanosleep) */
#if __CRT_HAVE_XSC(oldwait4)
__CDECLARE_XSC(,__pid_t,oldwait4,(__pid_t __pid, __int32_t *__stat_loc, __syscall_ulong_t __options, struct rusage *__usage),(__pid,__stat_loc,__options,__usage))
#endif /* __CRT_HAVE_XSC(oldwait4) */
#if __CRT_HAVE_XSC(ppoll)
__CDECLARE_XSC(,__ssize_t,ppoll,(struct pollfd *__fds, __size_t __nfds, struct timespec const *__timeout_ts, struct __sigset_struct const *__sigmask, __size_t __sigsetsize),(__fds,__nfds,__timeout_ts,__sigmask,__sigsetsize))
#endif /* __CRT_HAVE_XSC(ppoll) */
#if __CRT_HAVE_XSC(preadv)
__CDECLARE_XSC(,__ssize_t,preadv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_XSC(preadv) */
#if __CRT_HAVE_XSC(process_vm_readv)
__CDECLARE_XSC(,__ssize_t,process_vm_readv,(__pid_t __pid, struct iovec const *__lvec, __size_t __liovcnt, struct iovec const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* __CRT_HAVE_XSC(process_vm_readv) */
#if __CRT_HAVE_XSC(process_vm_writev)
__CDECLARE_XSC(,__ssize_t,process_vm_writev,(__pid_t __pid, struct iovec const *__lvec, __size_t __liovcnt, struct iovec const *__rvec, __size_t __riovcnt, __syscall_ulong_t __flags),(__pid,__lvec,__liovcnt,__rvec,__riovcnt,__flags))
#endif /* __CRT_HAVE_XSC(process_vm_writev) */
#if __CRT_HAVE_XSC(pselect6)
__CDECLARE_XSC(,__ssize_t,pselect6,(__size_t __nfds, struct __fd_set_struct *__readfds, struct __fd_set_struct *__writefds, struct __fd_set_struct *__exceptfds, struct timespec const *__timeout, void const *__sigmask_sigset_and_len),(__nfds,__readfds,__writefds,__exceptfds,__timeout,__sigmask_sigset_and_len))
#endif /* __CRT_HAVE_XSC(pselect6) */
#if __CRT_HAVE_XSC(pwritev)
__CDECLARE_XSC(,__ssize_t,pwritev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count, __uint64_t __offset),(__fd,__iovec,__count,__offset))
#endif /* __CRT_HAVE_XSC(pwritev) */
#if __CRT_HAVE_XSC(readv)
__CDECLARE_XSC(,__ssize_t,readv,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_XSC(readv) */
#if __CRT_HAVE_XSC(recv)
__CDECLARE_XSC(,__ssize_t,recv,(__fd_t __sockfd, void *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__sockfd,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_XSC(recv) */
#if __CRT_HAVE_XSC(recvmmsg)
__CDECLARE_XSC(,__ssize_t,recvmmsg,(__fd_t __sockfd, struct mmsghdr *__vmessages, __size_t __vlen, __syscall_ulong_t __flags, struct timespec *__tmo),(__sockfd,__vmessages,__vlen,__flags,__tmo))
#endif /* __CRT_HAVE_XSC(recvmmsg) */
#if __CRT_HAVE_XSC(rt_sigqueueinfo)
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,rt_sigqueueinfo,(__pid_t __tgid, __syscall_ulong_t __signo, struct __siginfo_struct const *__uinfo),(__tgid,__signo,__uinfo))
#endif /* __CRT_HAVE_XSC(rt_sigqueueinfo) */
#if __CRT_HAVE_XSC(rt_sigtimedwait)
__CDECLARE_XSC(,__syscall_slong_t,rt_sigtimedwait,(struct __sigset_struct const *__set, struct __siginfo_struct *__info, struct timespec const *__timeout, __size_t __sigsetsize),(__set,__info,__timeout,__sigsetsize))
#endif /* __CRT_HAVE_XSC(rt_sigtimedwait) */
#if __CRT_HAVE_XSC(rt_tgsigqueueinfo)
/* @param: signo: One of `SIG*' */
__CDECLARE_XSC(,__errno_t,rt_tgsigqueueinfo,(__pid_t __tgid, __pid_t __tid, __syscall_ulong_t __signo, struct __siginfo_struct const *__uinfo),(__tgid,__tid,__signo,__uinfo))
#endif /* __CRT_HAVE_XSC(rt_tgsigqueueinfo) */
#if __CRT_HAVE_XSC(sched_rr_get_interval)
__CDECLARE_XSC(,__errno_t,sched_rr_get_interval,(__pid_t __pid, struct __timespec *__tms),(__pid,__tms))
#endif /* __CRT_HAVE_XSC(sched_rr_get_interval) */
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
/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
__CDECLARE_XSC(,__ssize_t,send,(__fd_t __sockfd, void const *__buf, __size_t __bufsize, __syscall_ulong_t __flags),(__sockfd,__buf,__bufsize,__flags))
#endif /* __CRT_HAVE_XSC(send) */
#if __CRT_HAVE_XSC(setfsgid)
__CDECLARE_XSC(,__errno_t,setfsgid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_XSC(setfsgid) */
#if __CRT_HAVE_XSC(setfsuid)
__CDECLARE_XSC(,__errno_t,setfsuid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_XSC(setfsuid) */
#if __CRT_HAVE_XSC(setgid)
__CDECLARE_XSC(,__errno_t,setgid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_XSC(setgid) */
#if __CRT_HAVE_XSC(setgroups)
__CDECLARE_XSC(,__errno_t,setgroups,(__size_t __count, __gid_t const *__groups),(__count,__groups))
#endif /* __CRT_HAVE_XSC(setgroups) */
#if __CRT_HAVE_XSC(setregid)
__CDECLARE_XSC(,__errno_t,setregid,(__gid_t __rgid, __gid_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_XSC(setregid) */
#if __CRT_HAVE_XSC(setresgid)
__CDECLARE_XSC(,__errno_t,setresgid,(__gid_t __rgid, __gid_t __egid, __gid_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_XSC(setresgid) */
#if __CRT_HAVE_XSC(setresuid)
__CDECLARE_XSC(,__errno_t,setresuid,(__uid_t __ruid, __uid_t __euid, __uid_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_XSC(setresuid) */
#if __CRT_HAVE_XSC(setreuid)
__CDECLARE_XSC(,__errno_t,setreuid,(__uid_t __ruid, __uid_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_XSC(setreuid) */
#if __CRT_HAVE_XSC(settimeofday)
__CDECLARE_XSC(,__errno_t,settimeofday,(struct timeval const *__tv, struct timezone const *__tz),(__tv,__tz))
#endif /* __CRT_HAVE_XSC(settimeofday) */
#if __CRT_HAVE_XSC(setuid)
__CDECLARE_XSC(,__errno_t,setuid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_XSC(setuid) */
#if __CRT_HAVE_XSC(shmat)
__CDECLARE_XSC(,__errno_t,shmat,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(shmat) */
#if __CRT_HAVE_XSC(shmctl)
__CDECLARE_XSC(,__errno_t,shmctl,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(shmctl) */
#if __CRT_HAVE_XSC(shmdt)
__CDECLARE_XSC(,__errno_t,shmdt,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(shmdt) */
#if __CRT_HAVE_XSC(shmget)
__CDECLARE_XSC(,__errno_t,shmget,(int __TODO_PROTOTYPE),(__TODO_PROTOTYPE))
#endif /* __CRT_HAVE_XSC(shmget) */
#if __CRT_HAVE_XSC(timer_gettime)
__CDECLARE_XSC(,__errno_t,timer_gettime,(__timer_t __timerid, struct itimerspec *__value),(__timerid,__value))
#endif /* __CRT_HAVE_XSC(timer_gettime) */
#if __CRT_HAVE_XSC(timer_settime)
__CDECLARE_XSC(,__errno_t,timer_settime,(__timer_t __timerid, __syscall_ulong_t __flags, struct itimerspec const *__value, struct itimerspec *__ovalue),(__timerid,__flags,__value,__ovalue))
#endif /* __CRT_HAVE_XSC(timer_settime) */
#if __CRT_HAVE_XSC(timerfd_gettime)
/* Return the next expiration time of UFD */
__CDECLARE_XSC(,__errno_t,timerfd_gettime,(__fd_t __ufd, struct itimerspec *__otmr),(__ufd,__otmr))
#endif /* __CRT_HAVE_XSC(timerfd_gettime) */
#if __CRT_HAVE_XSC(timerfd_settime)
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
__CDECLARE_XSC(,__errno_t,timerfd_settime,(__fd_t __ufd, __syscall_ulong_t __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr),(__ufd,__flags,__utmr,__otmr))
#endif /* __CRT_HAVE_XSC(timerfd_settime) */
#if __CRT_HAVE_XSC(umount)
__CDECLARE_XSC(,__errno_t,umount,(char const *__special_file),(__special_file))
#endif /* __CRT_HAVE_XSC(umount) */
#if __CRT_HAVE_XSC(utimensat)
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
__CDECLARE_XSC(,__errno_t,utimensat,(__fd_t __dirfd, char const *__filename, struct timespec const *__times, __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#endif /* __CRT_HAVE_XSC(utimensat) */
#if __CRT_HAVE_XSC(utimes)
__CDECLARE_XSC(,__errno_t,utimes,(char const *__filename, struct timeval const *__times),(__filename,__times))
#endif /* __CRT_HAVE_XSC(utimes) */
#if __CRT_HAVE_XSC(vmsplice)
__CDECLARE_XSC(,__ssize_t,vmsplice,(__fd_t __fdout, struct iovec const *__iov, __size_t __count, __syscall_ulong_t __flags),(__fdout,__iov,__count,__flags))
#endif /* __CRT_HAVE_XSC(vmsplice) */
#if __CRT_HAVE_XSC(waitid)
/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
__CDECLARE_XSC(,__errno_t,waitid,(__syscall_ulong_t __idtype, __id_t __id, struct __siginfo_struct *__infop, __syscall_ulong_t __options, struct rusage *__ru),(__idtype,__id,__infop,__options,__ru))
#endif /* __CRT_HAVE_XSC(waitid) */
#if __CRT_HAVE_XSC(writev)
__CDECLARE_XSC(,__ssize_t,writev,(__fd_t __fd, struct iovec const *__iovec, __size_t __count),(__fd,__iovec,__count))
#endif /* __CRT_HAVE_XSC(writev) */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("timezone")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_SYSCALL_H */
