/* HASH CRC-32:0x84a7b935 */
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
#ifndef _SCHED_H
#define _SCHED_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/sched.h>
#include <bits/sched_param.h>
#include <bits/timespec.h>
#include <bits/types.h>

#ifdef __USE_KOS
#include <hybrid/host.h>

#include <asm/signum-values.h> /* __SIGCHLD */
#endif /* __USE_KOS */

__SYSDECL_BEGIN

#ifdef __SCHED_OTHER
#define SCHED_OTHER __SCHED_OTHER /* ... */
#endif /* __SCHED_OTHER */
#ifdef __SCHED_FIFO
#define SCHED_FIFO __SCHED_FIFO /* ... */
#endif /* __SCHED_FIFO */
#ifdef __SCHED_RR
#define SCHED_RR __SCHED_RR /* ... */
#endif /* __SCHED_RR */
#ifdef __USE_GNU
#ifdef __SCHED_BATCH
#define SCHED_BATCH __SCHED_BATCH /* ... */
#endif /* __SCHED_BATCH */
#ifdef __SCHED_IDLE
#define SCHED_IDLE __SCHED_IDLE /* ... */
#endif /* __SCHED_IDLE */
#ifdef __SCHED_RESET_ON_FORK
#define SCHED_RESET_ON_FORK __SCHED_RESET_ON_FORK /* ... */
#endif /* __SCHED_RESET_ON_FORK */
#endif /* __USE_GNU */


/* KOS Interpretation of the `CLONE_DETACHED' and `CLONE_THREAD' flags:
 *   - First off all: Linux's implementation is flawed by design
 *     and includes rare race conditions that have never been
 *     patched and could lead to system calls taking pids, operating
 *     on a thread other than the one intended by the caller.
 *     Additionally, there is no way to circumvent this race condition,
 *     whereas KOS implements a dedicated `detach(2)' system call to
 *     define explicit behavior for dealing with the case resulting in
 *     problems on linux (See the second mile-long comment after this one)
 *
 * CLONE_DETACHED:
 *   - This flag is completely DISCONNECTED from `CLONE_THREAD'
 *     and must be passed explicitly to make use of its behavior.
 *     Note that on linux, its behavior is implied by `CLONE_THREAD'.
 *     - `CLONE_DETACHED' will prevent the thread from
 *       turning into a zombie once it terminates, allowing
 *       it to reap itself.
 *     - Passing this flag has the safe effect as calling `detach(2)'
 *       with the returned PID immediately after `clone(2)' returns.
 *
 * CLONE_THREAD:
 *   - Has _NO_ influence on the behavior of `wait(2)' (unlike in linux)
 *   - Has _NOTHING_ to do with the thread possibly turning into a zombie
 *   - The only thing it does, is control if the thread is added to the
 *     calling process (if set), or be setup as its own process (if not set)
 *   - Will _NOT_ trigger a posix_signal to be sent to the parent process.
 *     Because this is a thread, and thread parents are tracked on a per-process
 *     basis, the parent process mustn't be bothered about this.
 *
 * CLONE_PARENT:
 *   - Setup the new thread as a child of the parent of the calling process,
 *     the same way as it would have been set up if the original fork()-er
 *     that created the calling process had done a second fork() to create
 *     the thread created by the clone() call to which this flag is passed.
 *     On linux, the behavior is the same, but instead of functioning on
 *     a process-parent-basis, it functions on a thread-parent-basis.
 *     It should be noted that KOS does not track thread parents, but
 *     only the parents of whole processes.
 *   - Cannot be used with `CLONE_THREAD'. Attempting to do so anyways will
 *     cause `clone()' to fail with an `E_INVALID_ARGUMENT' exception.
 *
 * CSIGNAL:
 *   - The signal number send upon termination of the thread created by clone(2),
 *     to the any thread apart of the process referred to by its `getppid(2)'
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
 *     aka. the thread created by `fork(2)' or `clone(2)' without
 *     the `CLONE_THREAD' flag being passed.
 *
 * getppid():
 *   - Returns what getpid() would return in the thread did the fork(),
 *     clone() without `CLONE_PARENT', or the thread that created the
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

/* Signal mask to be sent at exit. */
#ifdef __CSIGNAL
#define CSIGNAL __CSIGNAL
#endif /* __CSIGNAL */

/* Set if VM shared between processes. */
#ifdef __CLONE_VM
#define CLONE_VM __CLONE_VM
#endif /* __CLONE_VM */

/* Set if fs info shared between processes. */
#ifdef __CLONE_FS
#define CLONE_FS __CLONE_FS
#endif /* __CLONE_FS */

/* Set if open files shared between processes. */
#ifdef __CLONE_FILES
#define CLONE_FILES __CLONE_FILES
#endif /* __CLONE_FILES */

/* Set if signal handlers shared. */
#ifdef __CLONE_SIGHAND
#define CLONE_SIGHAND __CLONE_SIGHAND
#endif /* __CLONE_SIGHAND */

/* Set if credentials (user/group ids and special permissions) are shared.
 * Note that during an exec() credentials are unshared unconditionalls. */
#ifdef __CLONE_CRED
#define CLONE_CRED __CLONE_CRED
#endif /* __CLONE_CRED */

/* Set if tracing continues on the child. */
#ifdef __CLONE_PTRACE
#define CLONE_PTRACE __CLONE_PTRACE
#endif /* __CLONE_PTRACE */

/* Set if the parent wants the child to wake it up on mm_release. */
#ifdef __CLONE_VFORK
#define CLONE_VFORK __CLONE_VFORK
#endif /* __CLONE_VFORK */

/* Set if we want to have the same parent as the cloner. */
#ifdef __CLONE_PARENT
#define CLONE_PARENT __CLONE_PARENT
#endif /* __CLONE_PARENT */

/* Set to add to same thread group. */
#ifdef __CLONE_THREAD
#define CLONE_THREAD __CLONE_THREAD
#endif /* __CLONE_THREAD */

/* Set to create new namespace. */
#ifdef __CLONE_NEWNS
#define CLONE_NEWNS __CLONE_NEWNS
#endif /* __CLONE_NEWNS */

/* Set to shared SVID SEM_UNDO semantics. */
#ifdef __CLONE_SYSVSEM
#define CLONE_SYSVSEM __CLONE_SYSVSEM
#endif /* __CLONE_SYSVSEM */

/* Set TLS info. */
#ifdef __CLONE_SETTLS
#define CLONE_SETTLS __CLONE_SETTLS
#endif /* __CLONE_SETTLS */

/* Store TID in userlevel buffer before MM copy. */
#ifdef __CLONE_PARENT_SETTID
#define CLONE_PARENT_SETTID __CLONE_PARENT_SETTID
#endif /* __CLONE_PARENT_SETTID */

/* Register exit futex and memory location to clear. */
#ifdef __CLONE_CHILD_CLEARTID
#define CLONE_CHILD_CLEARTID __CLONE_CHILD_CLEARTID
#endif /* __CLONE_CHILD_CLEARTID */

/* Create clone detached. */
#ifdef __CLONE_DETACHED
#define CLONE_DETACHED __CLONE_DETACHED
#endif /* __CLONE_DETACHED */

/* Set if the tracing process can't force CLONE_PTRACE on this clone. */
#ifdef __CLONE_UNTRACED
#define CLONE_UNTRACED __CLONE_UNTRACED
#endif /* __CLONE_UNTRACED */

/* Store TID in userlevel buffer in the child. */
#ifdef __CLONE_CHILD_SETTID
#define CLONE_CHILD_SETTID __CLONE_CHILD_SETTID
#endif /* __CLONE_CHILD_SETTID */

/* New utsname group. */
#ifdef __CLONE_NEWUTS
#define CLONE_NEWUTS __CLONE_NEWUTS
#endif /* __CLONE_NEWUTS */

/* New ipcs. */
#ifdef __CLONE_NEWIPC
#define CLONE_NEWIPC __CLONE_NEWIPC
#endif /* __CLONE_NEWIPC */

/* New user namespace. */
#ifdef __CLONE_NEWUSER
#define CLONE_NEWUSER __CLONE_NEWUSER
#endif /* __CLONE_NEWUSER */

/* New pid namespace. */
#ifdef __CLONE_NEWPID
#define CLONE_NEWPID __CLONE_NEWPID
#endif /* __CLONE_NEWPID */

/* New network namespace. */
#ifdef __CLONE_NEWNET
#define CLONE_NEWNET __CLONE_NEWNET
#endif /* __CLONE_NEWNET */

/* Clone I/O context. */
#ifdef __CLONE_IO
#define CLONE_IO __CLONE_IO
#endif /* __CLONE_IO */


#ifdef __USE_KOS
/* Value passed for 'CHILD_STACK' to 'clone()':
 * When given, let the kernel decide where and how to allocate a new stack for the child.
 * NOTE: The value was chosen due to the fact that it represents the wrap-around address
 *       that would otherwise cause a STACK_FAULT when attempted to be used with push/pop,
 *       meaning that it can't be used for any other meaningful purpose.
 * HINT: The kernel's auto-generated stack will be automatically configured to either be
 *       a copy of the calling thread's stack (at the same address in case CLONE_VM was passed),
 *       or be located at a different address and consist of a pre-mapped portion (e.g.: 4K), as well
 *       as a guard page with the potential of extending the stack some number of times (e.g.: 8)
 *       The stack memory itself will be lazily allocated on access and be pre-initialized
 *       to either all ZEROs or a debug constant such as `0xCC'.
 * NOTE: Of course this auto-generated stack will also be automatically
 *       munmap()'ed once the thread exists, meaning it's the perfect solution
 *       for simple user-space multithreading that doesn't want to use <pthread.h>. */
#ifndef CLONE_CHILDSTACK_AUTO
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define CLONE_CHILDSTACK_AUTO ((void *)0)
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#define CLONE_CHILDSTACK_AUTO ((void *)-1)
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
#endif /* !CLONE_CHILDSTACK_AUTO */

#ifdef __CLONE_THREAD
#define __PRIVATE_CLONE_THREAD __CLONE_THREAD
#else /* __CLONE_THREAD */
#define __PRIVATE_CLONE_THREAD 0
#endif /* !__CLONE_THREAD */
#ifdef __CLONE_VM
#define __PRIVATE_CLONE_VM __CLONE_VM
#else /* __CLONE_VM */
#define __PRIVATE_CLONE_VM 0
#endif /* !__CLONE_VM */
#ifdef __CLONE_FS
#define __PRIVATE_CLONE_FS __CLONE_FS
#else /* __CLONE_FS */
#define __PRIVATE_CLONE_FS 0
#endif /* !__CLONE_FS */
#ifdef __CLONE_FILES
#define __PRIVATE_CLONE_FILES __CLONE_FILES
#else /* __CLONE_FILES */
#define __PRIVATE_CLONE_FILES 0
#endif /* !__CLONE_FILES */
#ifdef __CLONE_SIGHAND
#define __PRIVATE_CLONE_SIGHAND __CLONE_SIGHAND
#else /* __CLONE_SIGHAND */
#define __PRIVATE_CLONE_SIGHAND 0
#endif /* !__CLONE_SIGHAND */
#ifdef __CLONE_CRED
#define __PRIVATE_CLONE_CRED __CLONE_CRED
#else /* __CLONE_CRED */
#define __PRIVATE_CLONE_CRED 0
#endif /* !__CLONE_CRED */
#ifdef __CLONE_IO
#define __PRIVATE_CLONE_IO __CLONE_IO
#else /* __CLONE_IO */
#define __PRIVATE_CLONE_IO 0
#endif /* !__CLONE_IO */

/* Generic set of clone flags implementing behavior
 * that one would expect for a thread or process. */
#define CLONE_NEW_THREAD       \
	(0 |                       \
	 __PRIVATE_CLONE_THREAD |  \
	 __PRIVATE_CLONE_VM |      \
	 __PRIVATE_CLONE_FS |      \
	 __PRIVATE_CLONE_FILES |   \
	 __PRIVATE_CLONE_SIGHAND | \
	 __PRIVATE_CLONE_CRED |    \
	 __PRIVATE_CLONE_IO)

/* Same flags as used by fork() */
#ifdef __SIGCHLD
#define CLONE_NEW_PROCESS (__SIGCHLD)
#else /* __SIGCHLD */
#define CLONE_NEW_PROCESS 0
#endif /* !__SIGCHLD */

#endif /* __USE_KOS */
#endif /* __USE_GNU || __USE_KOS */

#ifdef __CC__

#ifndef sched_priority
#define sched_priority __sched_priority
#endif /* !sched_priority */


#if defined(__USE_GNU) || defined(__USE_KOS)
typedef int (__LIBKCALL *__clone_func_t)(void *__arg);
#ifdef __CRT_HAVE_clone
__LIBC __ATTR_NONNULL((1)) __pid_t __NOTHROW_NCX(__VLIBCCALL clone)(__clone_func_t __fn, void *__child_stack, int __flags, void *__arg, ...) __CASMNAME_SAME("clone");
#elif defined(__CRT_HAVE___clone)
__CVREDIRECT(__ATTR_NONNULL((1)),__pid_t,__NOTHROW_NCX,clone,(__clone_func_t __fn, void *__child_stack, int __flags, void *__arg),__clone,(__fn,__child_stack,__flags,__arg),__arg,3,(__pid_t,void *,__pid_t))
#endif /* ... */
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
__CDECLARE_OPT(,int,__NOTHROW_NCX,unshare,(__STDC_INT_AS_UINT_T __flags),(__flags))
/* >> sched_getcpu(3)
 * Returns the number of the CPU for the calling thread.
 * Note that due to unforeseeable scheduling conditions, this may change at any
 * moment, even before this function returns, or before the caller was able to
 * act on its return value. For that reason, this function must only be taken
 * as a hint */
__CDECLARE_OPT(,__STDC_INT_AS_UINT_T,__NOTHROW_NCX,sched_getcpu,(void),())
/* >> setns(2)
 * With `FD' referring to a namespace, reassociate the calling thread with that namespace.
 * For this purpose, `FD' was opened for one of the files in `/proc/[pid]/ns/'
 * @param: nstype: The type of namespace to re-associate (either 0 to allow any
 *                 type of namespace, or one of `CLONE_NEWCGROUP', `CLONE_NEWIPC',
 *                `CLONE_NEWNET', `CLONE_NEWNS', `CLONE_NEWPID', `CLONE_NEWUSER',
 *                `CLONE_NEWUTS') */
__CDECLARE_OPT(,int,__NOTHROW_NCX,setns,(__fd_t __fd, __STDC_INT_AS_UINT_T __nstype),(__fd,__nstype))

#ifdef __USE_KOS
/* Exits the current thread by invoking the SYS_exit system call,
 * after performing some additional cleanup not done by the kernel.
 * Assuming that the calling thread was constructed by `clone()',
 * calling this function has the same effect as returning `EXIT_CODE'
 * from `clone()'s `FN' callback */
__CDECLARE_VOID_OPT(__ATTR_NORETURN,__NOTHROW_NCX,exit_thread,(int __exit_code),(__exit_code))
#endif /* __USE_KOS */
#endif /* __USE_GNU || __USE_KOS */
#endif /* __CC__ */



#ifdef __USE_GNU

#ifdef __CC__
typedef __cpu_set_t cpu_set_t;
#endif /* __CC__ */

#ifdef __USE_KOS
#define CPU_SETNONE                  __CPU_SETNONE
#define CPU_SETALL                   __CPU_SETALL
#define CPU_SETONE(i)                __CPU_SETONE(i)
#define CPU_ISEMPTY(cpusetp)         __CPU_ISEMPTY_S(sizeof(cpu_set_t), cpusetp)
#define CPU_FILL(cpusetp)            __CPU_FILL_S(sizeof(cpu_set_t), cpusetp)
#define CPU_FILL_S(setsize, cpusetp) __CPU_FILL_S(setsize, cpusetp)
#endif /* __USE_KOS */
#define CPU_SETSIZE   __CPU_SETSIZE

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
__CDECLARE_OPT(,int,__NOTHROW_NCX,sched_setparam,(__pid_t __pid, struct sched_param const *__param),(__pid,__param))
#ifdef __CRT_HAVE_sched_getparam
__CDECLARE(,int,__NOTHROW_NCX,sched_getparam,(__pid_t __pid, struct sched_param *__param),(__pid,__param))
#elif defined(__CRT_HAVE___sched_getparam)
__CREDIRECT(,int,__NOTHROW_NCX,sched_getparam,(__pid_t __pid, struct sched_param *__param),__sched_getparam,(__pid,__param))
#endif /* ... */
#ifdef __CRT_HAVE_sched_setscheduler
__CDECLARE(,int,__NOTHROW_NCX,sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),(__pid,__policy,__param))
#elif defined(__CRT_HAVE___sched_setscheduler)
__CREDIRECT(,int,__NOTHROW_NCX,sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),__sched_setscheduler,(__pid,__policy,__param))
#endif /* ... */
#ifdef __CRT_HAVE_sched_getscheduler
__CDECLARE(,int,__NOTHROW_NCX,sched_getscheduler,(__pid_t __pid),(__pid))
#elif defined(__CRT_HAVE___sched_getscheduler)
__CREDIRECT(,int,__NOTHROW_NCX,sched_getscheduler,(__pid_t __pid),__sched_getscheduler,(__pid))
#endif /* ... */

#ifdef __CRT_HAVE_sched_yield
/* @return: 1: Another thread was executed prior to the function returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CDECLARE(,int,__NOTHROW,sched_yield,(void),())
#elif defined(__CRT_HAVE_thrd_yield)
/* @return: 1: Another thread was executed prior to the function returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),thrd_yield,())
#elif defined(__CRT_HAVE_pthread_yield)
/* @return: 1: Another thread was executed prior to the function returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),pthread_yield,())
#elif defined(__CRT_HAVE___sched_yield)
/* @return: 1: Another thread was executed prior to the function returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),__sched_yield,())
#elif defined(__CRT_HAVE_yield)
/* @return: 1: Another thread was executed prior to the function returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT(,int,__NOTHROW,sched_yield,(void),yield,())
#endif /* ... */
#ifdef __CRT_HAVE_sched_get_priority_max
__CDECLARE(,int,__NOTHROW_NCX,sched_get_priority_max,(__STDC_INT_AS_UINT_T __algorithm),(__algorithm))
#elif defined(__CRT_HAVE___sched_get_priority_max)
__CREDIRECT(,int,__NOTHROW_NCX,sched_get_priority_max,(__STDC_INT_AS_UINT_T __algorithm),__sched_get_priority_max,(__algorithm))
#endif /* ... */
#ifdef __CRT_HAVE_sched_get_priority_min
__CDECLARE(,int,__NOTHROW_NCX,sched_get_priority_min,(__STDC_INT_AS_UINT_T __algorithm),(__algorithm))
#elif defined(__CRT_HAVE___sched_get_priority_min)
__CREDIRECT(,int,__NOTHROW_NCX,sched_get_priority_min,(__STDC_INT_AS_UINT_T __algorithm),__sched_get_priority_min,(__algorithm))
#endif /* ... */
__CDECLARE_OPT(,int,__NOTHROW_NCX,sched_setaffinity,(__pid_t __pid, __SIZE_TYPE__ __cpusetsize, cpu_set_t const *__cpuset),(__pid,__cpusetsize,__cpuset))
__CDECLARE_OPT(,int,__NOTHROW_NCX,sched_getaffinity,(__pid_t __pid, __SIZE_TYPE__ __cpusetsize, cpu_set_t *__cpuset),(__pid,__cpusetsize,__cpuset))
#if defined(__CRT_HAVE_sched_rr_get_interval64) && defined(__USE_TIME_BITS64)
__CREDIRECT(,int,__NOTHROW_NCX,sched_rr_get_interval,(__pid_t __pid, struct timespec *__tms),sched_rr_get_interval64,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval) && !defined(__USE_TIME_BITS64)
__CDECLARE(,int,__NOTHROW_NCX,sched_rr_get_interval,(__pid_t __pid, struct timespec *__tms),(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval64) || defined(__CRT_HAVE_sched_rr_get_interval)
#include <libc/local/sched/sched_rr_get_interval.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sched_rr_get_interval, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL sched_rr_get_interval)(__pid_t __pid, struct timespec *__tms) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sched_rr_get_interval))(__pid, __tms); })
#endif /* ... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_sched_rr_get_interval64
__CDECLARE(,int,__NOTHROW_NCX,sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(,int,__NOTHROW_NCX,sched_rr_get_interval64,(__pid_t __pid, struct __timespec64 *__tms),sched_rr_get_interval,(__pid,__tms))
#elif defined(__CRT_HAVE_sched_rr_get_interval)
#include <libc/local/sched/sched_rr_get_interval64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sched_rr_get_interval64, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL sched_rr_get_interval64)(__pid_t __pid, struct __timespec64 *__tms) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sched_rr_get_interval64))(__pid, __tms); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __CC__ */
#endif /* __USE_GNU */

__SYSDECL_END

#endif /* !_SCHED_H */
