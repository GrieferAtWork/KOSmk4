/* HASH CRC-32:0x90d7773f */
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
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sched.h) */
/* (#) Portability: GNU C Library (/posix/sched.h) */
/* (#) Portability: GNU Hurd      (/usr/include/sched.h) */
/* (#) Portability: MinGW         (/mingw-w64-libraries/winpthreads/include/sched.h) */
/* (#) Portability: NetBSD        (/include/sched.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sched.h) */
/* (#) Portability: OpenBSD       (/include/sched.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/sched.h) */
/* (#) Portability: diet libc     (/include/sched.h) */
/* (#) Portability: libc6         (/include/sched.h) */
/* (#) Portability: mintlib       (/include/sched.h) */
/* (#) Portability: musl libc     (/include/sched.h) */
/* (#) Portability: uClibc        (/include/sched.h) */
#ifndef _SCHED_H
#define _SCHED_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/os/sched.h>
#include <bits/os/cpu_set.h>
#include <bits/os/sched.h>
#include <bits/os/timespec.h>
#include <bits/types.h>

#ifdef __USE_KOS
#include <hybrid/host.h>
#include <asm/os/signal.h> /* __SIGCHLD */
#endif /* __USE_KOS */

/* Scheduler policies (for `sched_setscheduler(2)') */
#if !defined(SCHED_OTHER) && defined(__SCHED_OTHER)
#define SCHED_OTHER         __SCHED_OTHER         /* ... */
#endif /* !SCHED_OTHER && __SCHED_OTHER */
#if !defined(SCHED_FIFO) && defined(__SCHED_FIFO)
#define SCHED_FIFO          __SCHED_FIFO          /* ... */
#endif /* !SCHED_FIFO && __SCHED_FIFO */
#if !defined(SCHED_RR) && defined(__SCHED_RR)
#define SCHED_RR            __SCHED_RR            /* ... */
#endif /* !SCHED_RR && __SCHED_RR */
#ifdef __USE_GNU
#if !defined(SCHED_BATCH) && defined(__SCHED_BATCH)
#define SCHED_BATCH         __SCHED_BATCH         /* ... */
#endif /* !SCHED_BATCH && __SCHED_BATCH */
#if !defined(SCHED_IDLE) && defined(__SCHED_IDLE)
#define SCHED_IDLE          __SCHED_IDLE          /* ... */
#endif /* !SCHED_IDLE && __SCHED_IDLE */
#if !defined(SCHED_RESET_ON_FORK) && defined(__SCHED_RESET_ON_FORK)
#define SCHED_RESET_ON_FORK __SCHED_RESET_ON_FORK /* ... */
#endif /* !SCHED_RESET_ON_FORK && __SCHED_RESET_ON_FORK */
#endif /* __USE_GNU */


/* KOS Interpretation of the `CLONE_DETACHED' and `CLONE_THREAD' flags:
 *   - First  off  all:  Linux's   implementation  is  flawed  by   design
 *     and  includes   rare  race   conditions   that  have   never   been
 *     patched  and  could lead  to  system calls  taking  pids, operating
 *     on   a  thread  other   than  the  one   intended  by  the  caller.
 *     Additionally, there is  no way to  circumvent this race  condition,
 *     whereas KOS  implements  a  dedicated `detach(2)'  system  call  to
 *     define  explicit behavior  for dealing  with the  case resulting in
 *     problems on linux (See the second mile-long comment after this one)
 *
 * CLONE_DETACHED:
 *   - This  flag  is  completely  DISCONNECTED  from  `CLONE_THREAD'
 *     and must be  passed explicitly  to make use  of its  behavior.
 *     Note that on linux, its behavior is implied by `CLONE_THREAD'.
 *     - `CLONE_DETACHED'  will  prevent  the  thread  from
 *       turning into a zombie once it terminates, allowing
 *       it to reap itself.
 *     - Passing this flag has the safe effect as calling `detach(2)'
 *       with  the returned PID immediately after `clone(2)' returns.
 *
 * CLONE_THREAD:
 *   - Has _NO_ influence on the behavior of `wait(2)' (unlike in linux)
 *   - Has _NOTHING_ to do with the thread possibly turning into a zombie
 *   - The only thing  it does, is  control if  the thread is  added to  the
 *     calling process (if set), or be setup as its own process (if not set)
 *   - Will  _NOT_  trigger a  posix_signal to  be sent  to the  parent process.
 *     Because this is a thread, and thread parents are tracked on a per-process
 *     basis, the parent process mustn't be bothered about this.
 *
 * CLONE_PARENT:
 *   - Setup the new thread as a child of the parent of the calling process,
 *     the same way as it would have  been set up if the original  fork()-er
 *     that created the calling process had  done a second fork() to  create
 *     the thread created by the clone() call to which this flag is  passed.
 *     On  linux, the  behavior is the  same, but instead  of functioning on
 *     a   process-parent-basis,  it  functions  on  a  thread-parent-basis.
 *     It  should  be noted  that  KOS does  not  track thread  parents, but
 *     only the parents of whole processes.
 *   - Cannot be used with `CLONE_THREAD'. Attempting to do so anyways will
 *     cause  `clone()'  to  fail with  an  `E_INVALID_ARGUMENT' exception.
 *
 * CSIGNAL:
 *   - The signal number send upon termination of the thread created by clone(2),
 *     to the any  thread apart of  the process referred  to by its  `getppid(2)'
 *   - When ZERO(0), no signal is sent, but `wait(2)' is _NOT_ affected (unlike in linux)
 *   - _NEVER_ Has any influence on the behavior of `wait(2)' (unlike in linux)
 *   - It doesn't make any difference if `SIGCHLD' is used, or some other signal. (unlike in linux)
 *   - Ignored when `CLONE_THREAD' is set.
 *
 * gettid():
 *   - Your own TID
 *
 * getpid():
 *   - Returns the TID of the leader of the current process.
 *   - That leader is the first thread that was added to the process,
 *     aka. the  thread created  by `fork(2)'  or `clone(2)'  without
 *     the `CLONE_THREAD' flag being passed.
 *
 * getppid():
 *   - Returns what getpid() would return in the thread did the fork(),
 *     clone() without `CLONE_PARENT', or  the thread that created  the
 *     thread that created you using clone() with `CLONE_PARENT'.
 *
 * __WNOTHREAD / __WALL / __WCLONE:
 *   - Currently not allowed (none of them have any place in KOS's interpretation of POSIX)
 *
 * NOTES (that should hopefully clear up this mess):
 *   - Process (pid):       A group of threads
 *   - Thread (tid):        A SINGLE F-ING THREAD! WHAT'S SO HARD ABOUT THIS?
 *   - Thread Group (tgid): Did you mean process? Because there is no such thing as a tgid, lol!
 *   - A PID is always the TID of the leader of that process!
 *   - A PGID is always the PID of the leader of that group!
 *   - An SID is always the GPID of the leader of that session!
 */

#if defined(__USE_GNU) || defined(__USE_KOS)
/* Cloning flags. */

#if !defined(CSIGNAL) && defined(__CSIGNAL)
#define CSIGNAL              __CSIGNAL              /* Signal mask to be sent at exit. */
#endif /* !CSIGNAL && __CSIGNAL */
#if !defined(CLONE_VM) && defined(__CLONE_VM)
#define CLONE_VM             __CLONE_VM             /* Set if VM shared between processes. */
#endif /* !CLONE_VM && __CLONE_VM */
#if !defined(CLONE_FS) && defined(__CLONE_FS)
#define CLONE_FS             __CLONE_FS             /* Set if fs info shared between processes. */
#endif /* !CLONE_FS && __CLONE_FS */
#if !defined(CLONE_FILES) && defined(__CLONE_FILES)
#define CLONE_FILES          __CLONE_FILES          /* Set if open files shared between processes. */
#endif /* !CLONE_FILES && __CLONE_FILES */
#if !defined(CLONE_SIGHAND) && defined(__CLONE_SIGHAND)
#define CLONE_SIGHAND        __CLONE_SIGHAND        /* Set if signal handlers shared. */
#endif /* !CLONE_SIGHAND && __CLONE_SIGHAND */
#if !defined(CLONE_PIDFD) && defined(__CLONE_PIDFD)
#define CLONE_PIDFD          __CLONE_PIDFD          /* Set to create+store pidfd at `*parent_tidptr' */
#endif /* !CLONE_PIDFD && __CLONE_PIDFD */
#if !defined(CLONE_PTRACE) && defined(__CLONE_PTRACE)
#define CLONE_PTRACE         __CLONE_PTRACE         /* Set if tracing continues on the child. */
#endif /* !CLONE_PTRACE && __CLONE_PTRACE */
#if !defined(CLONE_VFORK) && defined(__CLONE_VFORK)
#define CLONE_VFORK          __CLONE_VFORK          /* Set if the parent wants the child to wake it up on mm_release. */
#endif /* !CLONE_VFORK && __CLONE_VFORK */
#if !defined(CLONE_PARENT) && defined(__CLONE_PARENT)
#define CLONE_PARENT         __CLONE_PARENT         /* Set if we want to have the same parent as the cloner. */
#endif /* !CLONE_PARENT && __CLONE_PARENT */
#if !defined(CLONE_THREAD) && defined(__CLONE_THREAD)
#define CLONE_THREAD         __CLONE_THREAD         /* Set to add to same thread group. */
#endif /* !CLONE_THREAD && __CLONE_THREAD */
#if !defined(CLONE_NEWNS) && defined(__CLONE_NEWNS)
#define CLONE_NEWNS          __CLONE_NEWNS          /* Set to create new namespace. */
#endif /* !CLONE_NEWNS && __CLONE_NEWNS */
#if !defined(CLONE_SYSVSEM) && defined(__CLONE_SYSVSEM)
#define CLONE_SYSVSEM        __CLONE_SYSVSEM        /* Set to shared SVID SEM_UNDO semantics. */
#endif /* !CLONE_SYSVSEM && __CLONE_SYSVSEM */
#if !defined(CLONE_SETTLS) && defined(__CLONE_SETTLS)
#define CLONE_SETTLS         __CLONE_SETTLS         /* Set TLS info. */
#endif /* !CLONE_SETTLS && __CLONE_SETTLS */
#if !defined(CLONE_PARENT_SETTID) && defined(__CLONE_PARENT_SETTID)
#define CLONE_PARENT_SETTID  __CLONE_PARENT_SETTID  /* Store TID in userlevel buffer before MM copy. */
#endif /* !CLONE_PARENT_SETTID && __CLONE_PARENT_SETTID */
#if !defined(CLONE_CHILD_CLEARTID) && defined(__CLONE_CHILD_CLEARTID)
#define CLONE_CHILD_CLEARTID __CLONE_CHILD_CLEARTID /* Register exit futex and memory location to clear. */
#endif /* !CLONE_CHILD_CLEARTID && __CLONE_CHILD_CLEARTID */
#if !defined(CLONE_DETACHED) && defined(__CLONE_DETACHED)
#define CLONE_DETACHED       __CLONE_DETACHED       /* Create clone detached. */
#endif /* !CLONE_DETACHED && __CLONE_DETACHED */
#if !defined(CLONE_UNTRACED) && defined(__CLONE_UNTRACED)
#define CLONE_UNTRACED       __CLONE_UNTRACED       /* Set if the tracing process can't force CLONE_PTRACE on this clone. */
#endif /* !CLONE_UNTRACED && __CLONE_UNTRACED */
#if !defined(CLONE_CHILD_SETTID) && defined(__CLONE_CHILD_SETTID)
#define CLONE_CHILD_SETTID   __CLONE_CHILD_SETTID   /* Store TID in userlevel buffer in the child. */
#endif /* !CLONE_CHILD_SETTID && __CLONE_CHILD_SETTID */
#if !defined(CLONE_NEWCGROUP) && defined(__CLONE_NEWCGROUP)
#define CLONE_NEWCGROUP      __CLONE_NEWCGROUP      /* New cgroup namespace */
#endif /* !CLONE_NEWCGROUP && __CLONE_NEWCGROUP */
#if !defined(CLONE_NEWUTS) && defined(__CLONE_NEWUTS)
#define CLONE_NEWUTS         __CLONE_NEWUTS         /* New utsname group. */
#endif /* !CLONE_NEWUTS && __CLONE_NEWUTS */
#if !defined(CLONE_NEWIPC) && defined(__CLONE_NEWIPC)
#define CLONE_NEWIPC         __CLONE_NEWIPC         /* New ipcs. */
#endif /* !CLONE_NEWIPC && __CLONE_NEWIPC */
#if !defined(CLONE_NEWUSER) && defined(__CLONE_NEWUSER)
#define CLONE_NEWUSER        __CLONE_NEWUSER        /* New user namespace. */
#endif /* !CLONE_NEWUSER && __CLONE_NEWUSER */
#if !defined(CLONE_NEWPID) && defined(__CLONE_NEWPID)
#define CLONE_NEWPID         __CLONE_NEWPID         /* New pid namespace. */
#endif /* !CLONE_NEWPID && __CLONE_NEWPID */
#if !defined(CLONE_NEWNET) && defined(__CLONE_NEWNET)
#define CLONE_NEWNET         __CLONE_NEWNET         /* New network namespace. */
#endif /* !CLONE_NEWNET && __CLONE_NEWNET */
#if !defined(CLONE_IO) && defined(__CLONE_IO)
#define CLONE_IO             __CLONE_IO             /* Clone I/O context. */
#endif /* !CLONE_IO && __CLONE_IO */

/* For `clone3(2)' */
#if !defined(CLONE_CLEAR_SIGHAND) && defined(__CLONE_CLEAR_SIGHAND)
#define CLONE_CLEAR_SIGHAND __CLONE_CLEAR_SIGHAND   /* Set all signal handlers to `SIG_DFL'. */
#endif /* !CLONE_CLEAR_SIGHAND && __CLONE_CLEAR_SIGHAND */
#if !defined(CLONE_INTO_CGROUP) && defined(__CLONE_INTO_CGROUP)
#define CLONE_INTO_CGROUP   __CLONE_INTO_CGROUP     /* Use `clone_args::cgroup' */
#endif /* !CLONE_INTO_CGROUP && __CLONE_INTO_CGROUP */
#if !defined(CLONE_NEWTIME) && defined(__CLONE_NEWTIME)
#define CLONE_NEWTIME       __CLONE_NEWTIME         /* New time namespace */
#endif /* !CLONE_NEWTIME && __CLONE_NEWTIME */
#endif /* __USE_GNU || __USE_KOS */

#ifdef __USE_KOS
/* For `clone3(2)' */
#if !defined(CLONE_CRED) && defined(__CLONE_CRED)
#define CLONE_CRED           __CLONE_CRED           /* Set if credentials (user/group ids and special permissions) are  shared.
                                                     * Note that during an `exec(2)', credentials are unshared unconditionally,
                                                     * so it is impossible for 2 different programs to share credentials,  that
                                                     * is unless you re-implement the kernel ELF loader in user-space and  roll
                                                     * your own `execve(2)'... */
#endif /* !CLONE_CRED && __CLONE_CRED */
#endif /* __USE_KOS */

__SYSDECL_BEGIN

#ifdef __CC__
#if defined(__USE_GNU) || defined(__USE_KOS)
#ifdef __CRT_HAVE_clone
__LIBC __ATTR_NONNULL((1)) __pid_t __NOTHROW_NCX(__VLIBCCALL clone)(int (__LIBCCALL *__fn)(void *__arg), void *__child_stack, int __flags, void *__arg, ...) __CASMNAME_SAME("clone");
#elif defined(__CRT_HAVE___clone)
__CVREDIRECT(__ATTR_NONNULL((1)),__pid_t,__NOTHROW_NCX,clone,(int (__LIBCCALL *__fn)(void *__arg), void *__child_stack, int __flags, void *__arg),__clone,(__fn,__child_stack,__flags,__arg),__arg,3,(__pid_t,void *,__pid_t))
#endif /* ... */
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
__CDECLARE_OPT(,int,__NOTHROW_NCX,unshare,(__STDC_INT_AS_UINT_T __flags),(__flags))
/* >> sched_getcpu(3)
 * Returns the number of the CPU for the calling thread.
 * Note that due to unforeseeable scheduling conditions, this may change at any
 * moment, even before this function returns, or before the caller was able  to
 * act on its return value. For that  reason, this function must only be  taken
 * as a hint */
__CDECLARE_OPT(,__STDC_INT_AS_UINT_T,__NOTHROW_NCX,sched_getcpu,(void),())
/* >> setns(2)
 * With `fd' referring to a namespace, reassociate the calling thread with that namespace.
 * For  this  purpose,  `fd'  was  opened  for  one  of  the  files  in  `/proc/[pid]/ns/'
 * @param: nstype: The  type of namespace  to re-associate (either  0 to allow any
 *                 type of namespace, or one of `CLONE_NEWCGROUP', `CLONE_NEWIPC',
 *                `CLONE_NEWNET', `CLONE_NEWNS', `CLONE_NEWPID', `CLONE_NEWUSER',
 *                `CLONE_NEWUTS') */
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_NCX,setns,(__fd_t __fd, __STDC_INT_AS_UINT_T __nstype),(__fd,__nstype))

#ifdef __USE_KOS
/* Exits  the current  thread by  invoking the  SYS_exit system call,
 * after performing some additional cleanup  not done by the  kernel.
 * Assuming that  the calling  thread was  constructed by  `clone()',
 * calling this function has the same effect as returning `EXIT_CODE'
 * from `clone()'s `FN' callback */
__CDECLARE_VOID_OPT(__ATTR_NORETURN,__NOTHROW_NCX,exit_thread,(int __exit_code),(__exit_code))
#endif /* __USE_KOS */
#endif /* __USE_GNU || __USE_KOS */
#endif /* __CC__ */



#ifdef __USE_GNU

#ifdef __CC__
#ifndef __cpu_set_t_defined
#define __cpu_set_t_defined
typedef struct __cpu_set_struct cpu_set_t;
#endif /* !__cpu_set_t_defined */
#endif /* __CC__ */

#ifdef __USE_KOS
#define CPU_SETNONE                  __CPU_SETNONE
#define CPU_SETALL                   __CPU_SETALL
#define CPU_SETONE(i)                __CPU_SETONE(i)
#define CPU_ISEMPTY(cpusetp)         __CPU_ISEMPTY_S(sizeof(cpu_set_t), cpusetp)
#define CPU_FILL(cpusetp)            __CPU_FILL_S(sizeof(cpu_set_t), cpusetp)
#define CPU_FILL_S(setsize, cpusetp) __CPU_FILL_S(setsize, cpusetp)
#endif /* __USE_KOS */
#define CPU_SETSIZE __CPU_SETSIZE

#define CPU_SET(cpu, cpusetp)                         __CPU_SET_S(cpu, sizeof(cpu_set_t), cpusetp)
#define CPU_CLR(cpu, cpusetp)                         __CPU_CLR_S(cpu, sizeof(cpu_set_t), cpusetp)
#define CPU_ISSET(cpu, cpusetp)                       __CPU_ISSET_S(cpu, sizeof(cpu_set_t), cpusetp)
#define CPU_ZERO(cpusetp)                             __CPU_ZERO_S(sizeof(cpu_set_t), cpusetp)
#define CPU_COUNT(cpusetp)                            __CPU_COUNT_S(sizeof(cpu_set_t), cpusetp)
#define CPU_SET_S(cpu, setsize, cpusetp)              __CPU_SET_S(cpu, setsize, cpusetp)
#define CPU_CLR_S(cpu, setsize, cpusetp)              __CPU_CLR_S(cpu, setsize, cpusetp)
#define CPU_ISSET_S(cpu, setsize, cpusetp)            __CPU_ISSET_S(cpu, setsize, cpusetp)
#define CPU_ZERO_S(setsize, cpusetp)                  __CPU_ZERO_S(setsize, cpusetp)
#define CPU_COUNT_S(setsize, cpusetp)                 __CPU_COUNT_S(setsize, cpusetp)
#define CPU_EQUAL(cpusetp1, cpusetp2)                 __CPU_EQUAL_S(sizeof(cpu_set_t), cpusetp1, cpusetp2)
#define CPU_EQUAL_S(setsize, cpusetp1, cpusetp2)      __CPU_EQUAL_S(setsize, cpusetp1, cpusetp2)
#define CPU_AND(destset, srcset1, srcset2)            __CPU_AND_S(sizeof(cpu_set_t), destset, srcset1, srcset2)
#define CPU_OR(destset, srcset1, srcset2)             __CPU_OR_S(sizeof(cpu_set_t), destset, srcset1, srcset2)
#define CPU_XOR(destset, srcset1, srcset2)            __CPU_XOR_S(sizeof(cpu_set_t), destset, srcset1, srcset2)
#define CPU_AND_S(setsize, destset, srcset1, srcset2) __CPU_AND_S(setsize, destset, srcset1, srcset2)
#define CPU_OR_S(setsize, destset, srcset1, srcset2)  __CPU_OR_S(setsize, destset, srcset1, srcset2)
#define CPU_XOR_S(setsize, destset, srcset1, srcset2) __CPU_XOR_S(setsize, destset, srcset1, srcset2)
#define CPU_ALLOC_SIZE(count)                         __CPU_ALLOC_SIZE(count)
#ifdef __CPU_ALLOC
#define CPU_ALLOC(count) __CPU_ALLOC(count)
#endif /* __CPU_ALLOC */
#define CPU_FREE(cpuset) __CPU_FREE(cpuset)

#ifdef __CC__
#ifdef __CRT_HAVE_sched_setparam
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_NCX,sched_setparam,(__pid_t __pid, struct sched_param const *__param),(__pid,__param))
#elif defined(__CRT_HAVE___sched_setparam)
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,sched_setparam,(__pid_t __pid, struct sched_param const *__param),__sched_setparam,(__pid,__param))
#elif defined(__CRT_HAVE___libc_sched_setparam)
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,sched_setparam,(__pid_t __pid, struct sched_param const *__param),__libc_sched_setparam,(__pid,__param))
#endif /* ... */
#ifdef __CRT_HAVE_sched_getparam
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_NCX,sched_getparam,(__pid_t __pid, struct sched_param *__param),(__pid,__param))
#elif defined(__CRT_HAVE___sched_getparam)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,sched_getparam,(__pid_t __pid, struct sched_param *__param),__sched_getparam,(__pid,__param))
#elif defined(__CRT_HAVE___libc_sched_getparam)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,sched_getparam,(__pid_t __pid, struct sched_param *__param),__libc_sched_getparam,(__pid,__param))
#endif /* ... */
#ifdef __CRT_HAVE_sched_setscheduler
__CDECLARE(__ATTR_IN(3),int,__NOTHROW_NCX,sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),(__pid,__policy,__param))
#elif defined(__CRT_HAVE___sched_setscheduler)
__CREDIRECT(__ATTR_IN(3),int,__NOTHROW_NCX,sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),__sched_setscheduler,(__pid,__policy,__param))
#elif defined(__CRT_HAVE___libc_sched_setscheduler)
__CREDIRECT(__ATTR_IN(3),int,__NOTHROW_NCX,sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),__libc_sched_setscheduler,(__pid,__policy,__param))
#endif /* ... */
#ifdef __CRT_HAVE_sched_getscheduler
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,sched_getscheduler,(__pid_t __pid),(__pid))
#elif defined(__CRT_HAVE___sched_getscheduler)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,sched_getscheduler,(__pid_t __pid),__sched_getscheduler,(__pid))
#elif defined(__CRT_HAVE___libc_sched_getscheduler)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,sched_getscheduler,(__pid_t __pid),__libc_sched_getscheduler,(__pid))
#endif /* ... */

#ifdef __CRT_HAVE_sched_yield
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CDECLARE(,int,__NOTHROW,sched_yield,(void),())
#elif defined(__CRT_HAVE_thrd_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),thrd_yield,())
#elif defined(__CRT_HAVE_pthread_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),pthread_yield,())
#elif defined(__CRT_HAVE___sched_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),__sched_yield,())
#elif defined(__CRT_HAVE___libc_sched_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),__libc_sched_yield,())
#elif defined(__CRT_HAVE_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),yield,())
#elif defined(__CRT_HAVE_thr_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),thr_yield,())
#elif defined(__CRT_HAVE_cthread_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),cthread_yield,())
#endif /* ... */
#ifdef __CRT_HAVE_sched_get_priority_max
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,sched_get_priority_max,(__STDC_INT_AS_UINT_T __algorithm),(__algorithm))
#elif defined(__CRT_HAVE___sched_get_priority_max)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,sched_get_priority_max,(__STDC_INT_AS_UINT_T __algorithm),__sched_get_priority_max,(__algorithm))
#elif defined(__CRT_HAVE___libc_sched_get_priority_max)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,sched_get_priority_max,(__STDC_INT_AS_UINT_T __algorithm),__libc_sched_get_priority_max,(__algorithm))
#endif /* ... */
#ifdef __CRT_HAVE_sched_get_priority_min
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,sched_get_priority_min,(__STDC_INT_AS_UINT_T __algorithm),(__algorithm))
#elif defined(__CRT_HAVE___sched_get_priority_min)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,sched_get_priority_min,(__STDC_INT_AS_UINT_T __algorithm),__sched_get_priority_min,(__algorithm))
#elif defined(__CRT_HAVE___libc_sched_get_priority_min)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,sched_get_priority_min,(__STDC_INT_AS_UINT_T __algorithm),__libc_sched_get_priority_min,(__algorithm))
#endif /* ... */
__CDECLARE_OPT(__ATTR_IN_OPT(3),int,__NOTHROW_NCX,sched_setaffinity,(__pid_t __pid, __SIZE_TYPE__ __cpusetsize, cpu_set_t const *__cpuset),(__pid,__cpusetsize,__cpuset))
__CDECLARE_OPT(__ATTR_OUT_OPT(3),int,__NOTHROW_NCX,sched_getaffinity,(__pid_t __pid, __SIZE_TYPE__ __cpusetsize, cpu_set_t *__cpuset),(__pid,__cpusetsize,__cpuset))
#if defined(__CRT_HAVE_sched_rr_get_interval) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CDECLARE(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval,(__pid_t __pid, struct timespec *__tms),(__pid,__tms))
#elif defined(__CRT_HAVE___sched_rr_get_interval) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval,(__pid_t __pid, struct timespec *__tms),__sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE___libc_sched_rr_get_interval) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval,(__pid_t __pid, struct timespec *__tms),__libc_sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval,(__pid_t __pid, struct timespec *__tms),sched_rr_get_interval64,(__pid,__tms))
#elif defined(__CRT_HAVE___sched_rr_get_interval64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval,(__pid_t __pid, struct timespec *__tms),__sched_rr_get_interval64,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval64) || defined(__CRT_HAVE___sched_rr_get_interval64) || defined(__CRT_HAVE_sched_rr_get_interval) || defined(__CRT_HAVE___sched_rr_get_interval) || defined(__CRT_HAVE___libc_sched_rr_get_interval)
#include <libc/local/sched/sched_rr_get_interval.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sched_rr_get_interval, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(2) int __NOTHROW_NCX(__LIBCCALL sched_rr_get_interval)(__pid_t __pid, struct timespec *__tms) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sched_rr_get_interval))(__pid, __tms); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_sched_rr_get_interval) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval64,(__pid_t __pid, struct timespec64 *__tms),sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE___sched_rr_get_interval) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval64,(__pid_t __pid, struct timespec64 *__tms),__sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE___libc_sched_rr_get_interval) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval64,(__pid_t __pid, struct timespec64 *__tms),__libc_sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval64)
__CDECLARE(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval64,(__pid_t __pid, struct timespec64 *__tms),(__pid,__tms))
#elif defined(__CRT_HAVE___sched_rr_get_interval64)
__CREDIRECT(__ATTR_OUT_OPT(2),int,__NOTHROW_NCX,sched_rr_get_interval64,(__pid_t __pid, struct timespec64 *__tms),__sched_rr_get_interval64,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval) || defined(__CRT_HAVE___sched_rr_get_interval) || defined(__CRT_HAVE___libc_sched_rr_get_interval)
#include <libc/local/sched/sched_rr_get_interval64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sched_rr_get_interval64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(2) int __NOTHROW_NCX(__LIBCCALL sched_rr_get_interval64)(__pid_t __pid, struct timespec64 *__tms) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sched_rr_get_interval64))(__pid, __tms); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __CC__ */
#endif /* __USE_GNU */

__SYSDECL_END

#endif /* !_SCHED_H */
