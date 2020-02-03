/* HASH CRC-32:0x3a9191b6 */
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
#ifndef _BITS_SCHED_H
#define _BITS_SCHED_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <libc/string.h>
#include <libc/malloc.h>

#ifdef __USE_KOS
#include <bits/signum.h>
#endif /* __USE_KOS */

__SYSDECL_BEGIN

#define SCHED_OTHER         0
#define SCHED_FIFO          1
#define SCHED_RR            2
#ifdef __USE_GNU
#define SCHED_BATCH         3
#define SCHED_IDLE          5
#define SCHED_RESET_ON_FORK 0x40000000
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





/* SERIOUSLY F$CK COMPATIBILITY WITH LINUX!
 * And here's why I'm doing it right, even though I'm breaking compatibility
 * with a system which in its core is ONE BIG RACE CONDITION ABOUT TO HAPPEN:
 *
 * At one point, linux also had a `CLONE_DETACHED' flag.
 * Nowadays that flag barely has any documentation left, but the documentation
 * that still exists states `It's being ignored and its behavior was absorbed
 * by the CLONE_THREAD flag'.
 * What I'm guessing it used to do (and once again does right here and now),
 * is that it allows the thread to >> reap itself when exiting <<.
 * Now why is that important? Well although (possibly intentionally obscured), the
 * `CLONE_THREAD' flag states the following (http://man7.org/linux/man-pages/man2/clone.2.html):
 *  """
 *           When a CLONE_THREAD thread terminates, the thread that created it using
 *           clone() is not sent a SIGCHLD (or other termination) signal; nor can the
 *           status of such a thread be obtained using wait(2).
 *           (The thread is said to be detached.)
 *  """
 * Now what can be gathered from this?
 *  #1  As plainly stated, you can't use wait(2) to join the thread.
 *      OK. Makes sense. - That's the basic idea of what one would
 *      refer to as a detach-mechanism.
 *  #2  Since wait(2) is normally used to reap zombie processes,
 *      this must also mean that the thread will be able to:
 *      >> reap itself when exiting << (see above)
 *      because otherwise we'd end up with a bunch of unreapable
 *      zombies eating up all of our brains (memory), so the kernel
 *      must be able to free the TID descriptor of the thread as
 *      soon as it dies, _without_ any additional input required
 *      from user-space.
 *      OK. Makes sense. - Again, that's what one would expect
 *      from the behavior of a detach-mechanism.
 *
 * Well. The problem here is that this is all implied behavior of
 * the `CLONE_THREAD' flag used to create new threads in linux.
 * However, just so you truly understand what the problem is, take
 * a look at the set of flags used by the pthread library found
 * on any linux system to create new threads using clone(2):
 * >> const int clone_flags = (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SYSVSEM
 * >>                        | CLONE_SIGHAND | CLONE_THREAD          // <<< RIGHT HERE!!
 * >>                        | CLONE_SETTLS | CLONE_PARENT_SETTID
 * >>                        | CLONE_CHILD_CLEARTID
 * >>                        | 0);
 * It's using the `CLONE_THREAD' flag!
 * Now I'm not saying that it shouldn't, but you should realize that
 * as soon as one starts making use of `CLONE_THREAD', the training
 * wheels cleanly come off, and you have no way of safely using the
 * thread's TID in ANY OTHER SYSTEM CALL without running the chance
 * of the following happening:
 *  #1 You read out the TID from wherever you wrote it.
 *     Assuming that you're using the `set_tid_address()'
 *     functionality to have the kernel ZERO it out when the
 *     thread dies, you check if that happened and error out
 *     if what you get is a tid equal to ZERO.
 *  #2 You do the system call, say `tgkill()' as invoked by `pthread_kill()',
 *     but any number of other calls would work just as well, such as
 *     `sched_setaffinity()' invoked by `pthread_setaffinity()', or
 *     `rt_tgsigqueueinfo()' used by `pthread_sigqueue()'
 *  #3 Between the time that you read the TID and the time
 *     that the underlying system call evaluates the TID
 *     in order to translate it back into the kernel's thread
 *     structure (in KOS that would be `struct thread_pid'),
 *     the thread terminates.
 *     Ok. No problem. That would just mean that there'd be
 *     no thread associated with the TID, causing the system
 *     call to fail with ESRCH, as defined by POSIX.
 *    (Again: There won't be anything associated with the TID
 *            because using CLONE_THREAD means that the thread
 *            will have reaped itself when exit(2)ing)
 *     However, consider this:
 *       Another thread was creating a new thread at just the
 *       right time, and just before the kernel was assigning
 *       it a PID, the thread you were trying to access terminates
 *       and releases its PID.
 *       And as a result of this, as is the very principal of
 *       resource allocation, the kernel decides to re-use the
 *       PID, causing your system call (say tgkill invoked by pthread_kill)
 *       to suddenly refer to a brand new, but unrelated process.
 *     AND THERE YOU HAVE IT! A RACE CONDITION OF THE WORST MAGNITUDE!
 *     Because this is a race condition by DESIGN! _This_ can't
 *     easily be fixed by patching a bug. This is a fundamental
 *     flaw in how threads are implemented in linux.
 * -> Now I'm guessing linux tries to hide this problem by trying its
 *    darn hardest not to re-use TIDs for as long as possible, but the
 *    problem still stands, and _COULD_ _HAPPEN_.
 *    And simply never re-using TIDs isn't an answer either. Because
 *    that would mean that eventually it'd run out of IDs to hand out.
 * And if you think this isn't a problem, tell that to this code:
 *
 * Somewhere in the programming of the life support
 * systems of a space station, or whatever:
 * >> void stop_unrelated_workers() {
 * >> 	pthread_kill(unrelated_worker,SIGKILL);
 * >> 	// (Remember what we just learned this could do if
 * >> 	//  the race condition I described were to happen)
 * >> }
 *
 *
 * Meanwhile, in a different part of the code:
 * >> void *vent_open(void *vent) {
 * >> 	while (!try_open_vent(vent))
 * >> 		try_harder("Or people will die :(");
 * >> 	return VENT_OPEN_OK;
 * >> }
 * >> void enable_oxygen_ventilation_system(void) {
 * >> 	pthread_create(&vent_worker_0,&vent_open,get_vent(0));
 * >> 	pthread_create(&vent_worker_1,&vent_open,get_vent(1));
 * >> 	pthread_create(&vent_worker_2,&vent_open,get_vent(2));
 * >> 	pthread_create(&vent_worker_3,&vent_open,get_vent(3));
 * >>
 * >> 	pthread_join(vent_worker_3);
 * >> 	pthread_join(vent_worker_2);
 * >> 	pthread_join(vent_worker_1);
 * >> 	pthread_join(vent_worker_0);
 * >> }
 *
 * Yea. Tell that to the Astronaut that suffocated
 * because their air supply wouldn't engage...
 */

#if defined(__USE_GNU) || defined(__USE_KOS)
/* Cloning flags. */
#define CSIGNAL              0x000000ff /* Signal mask to be sent at exit. */
#define CLONE_VM             0x00000100 /* Set if VM shared between processes. */
#define CLONE_FS             0x00000200 /* Set if fs info shared between processes. */
#define CLONE_FILES          0x00000400 /* Set if open files shared between processes. */
#define CLONE_SIGHAND        0x00000800 /* Set if signal handlers shared. */
/*      CLONE_               0x00001000  * ... */
#define CLONE_PTRACE         0x00002000 /* Set if tracing continues on the child. */
#define CLONE_VFORK          0x00004000 /* Set if the parent wants the child to wake it up on mm_release. */
#define CLONE_PARENT         0x00008000 /* Set if we want to have the same parent as the cloner. */
#define CLONE_THREAD         0x00010000 /* Set to add to same thread group. */
#define CLONE_NEWNS          0x00020000 /* Set to create new namespace. */
#define CLONE_SYSVSEM        0x00040000 /* Set to shared SVID SEM_UNDO semantics. */
#define CLONE_SETTLS         0x00080000 /* Set TLS info. */
#define CLONE_PARENT_SETTID  0x00100000 /* Store TID in userlevel buffer before MM copy. */
#define CLONE_CHILD_CLEARTID 0x00200000 /* Register exit futex and memory location to clear. */
#define CLONE_DETACHED       0x00400000 /* Create clone detached. */
#define CLONE_UNTRACED       0x00800000 /* Set if the tracing process can't force CLONE_PTRACE on this clone. */
#define CLONE_CHILD_SETTID   0x01000000 /* Store TID in userlevel buffer in the child. */
/*      CLONE_               0x02000000  * ... */
#define CLONE_NEWUTS         0x04000000 /* New utsname group. */
#define CLONE_NEWIPC         0x08000000 /* New ipcs. */
#define CLONE_NEWUSER        0x10000000 /* New user namespace. */
#define CLONE_NEWPID         0x20000000 /* New pid namespace. */
#define CLONE_NEWNET         0x40000000 /* New network namespace. */
#define CLONE_IO             0x80000000 /* Clone I/O context. */

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
 *       for simple user-space multithreading that doesn't require -pthread. */
#ifndef CLONE_CHILDSTACK_AUTO
#ifdef __ARCH_STACK_GROWS_UP
#   define CLONE_CHILDSTACK_AUTO ((void *)-1)
#else
#   define CLONE_CHILDSTACK_AUTO ((void *)0)
#endif
#endif /* !CLONE_CHILDSTACK_AUTO */

/* Generic set of clone flags implementing behavior
 * that one would expect for a thread or process. */
#define CLONE_NEW_THREAD    (0|CLONE_THREAD|CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_IO)
#define CLONE_NEW_PROCESS   (SIGCHLD) /* Same flags as used by fork() */

#endif /* __USE_KOS */
#endif /* __USE_GNU || __USE_KOS */



#ifndef __CPU_SETSIZE
#define __CPU_SETSIZE       256
#endif /* !__CPU_SETSIZE */

#define __SIZEOF_CPU_SET_T__  (__CPU_SETSIZE / 8)
#define __NCPUBITS            (8*sizeof(__cpu_mask))
#define __SIZEOF_CPU_MASK__    4
#define __CPUELT(cpu)         ((cpu)/__NCPUBITS)
#define __CPUMASK(cpu)        ((__cpu_mask)1 << ((cpu)%__NCPUBITS))
#ifdef __CC__
typedef __UINT32_TYPE__ __cpu_mask;
typedef struct __cpu_set_struct {
	__cpu_mask __bits[__CPU_SETSIZE / __NCPUBITS];
} __cpu_set_t;
#endif /* __CC__ */
#define __CPU_SETNONE   {{[0 ... __CPUELT(__CPU_SETSIZE)-1] = 0}}
#define __CPU_SETALL    {{[0 ... __CPUELT(__CPU_SETSIZE)-1] = (__cpu_mask)-1}}
#if defined(__GNUC__) && 0
#define __CPU_SETONE(i) \
	_Pragma("GCC diagnostic push") \
	_Pragma("GCC diagnostic ignored \"-Woverride-init\"") \
		{{[0 ... __CPUELT(__CPU_SETSIZE)-1] = 0, [__CPUELT(i)] = __CPUMASK(i)}} \
	_Pragma("GCC diagnostic pop")
#elif 1
#define __CPU_SETONE(i) \
	{{[0 ... ((i) < __NCPUBITS ? 0 : __CPUELT(i)-1)] = (i) < __NCPUBITS ? __CPUMASK(i) : 0, \
		[((i) < __NCPUBITS ? 1 : __CPUELT(i)) ... \
		(((i) < __NCPUBITS || (i) >= (__CPU_SETSIZE-__NCPUBITS)) ? __CPUELT(__CPU_SETSIZE)-2 : __CPUELT(i))] = \
		((i) < __NCPUBITS || (i) >= (__CPU_SETSIZE-__NCPUBITS)) ? 0 : __CPUMASK(i), \
	[(((i) < __NCPUBITS || (i) >= (__CPU_SETSIZE-__NCPUBITS)) \
		? __CPUELT(__CPU_SETSIZE)-1 : __CPUELT(i)+1) ... __CPUELT(__CPU_SETSIZE)-1] = \
		(i) >= (__CPU_SETSIZE-__NCPUBITS) ? __CPUMASK(i) : 0, }}
#else
#define __CPU_SETONE(i) \
	{{[0 ... __CPUELT(__CPU_SETSIZE)-1] = 0, [__CPUELT(i)] = __CPUMASK(i)}}
#endif

#if __SIZEOF_CPU_MASK__ <= __SIZEOF_INT__
#   define __CPUMASK_POPCOUNT __builtin_popcount
#elif __SIZEOF_CPU_MASK__ <= __SIZEOF_LONG__
#   define __CPUMASK_POPCOUNT __builtin_popcountl
#elif __SIZEOF_CPU_MASK__ <= __SIZEOF_LONG_LONG__
#   define __CPUMASK_POPCOUNT __builtin_popcountll
#else
#   error FIXME
#endif

#define __CPU_FILL_S(setsize, cpusetp)         \
	do {                                       \
		__libc_memset(cpusetp, 0xff, setsize); \
	} __WHILE0
#define __CPU_ZERO_S(setsize, cpusetp)         \
	do {                                       \
		__libc_memset(cpusetp, 0x00, setsize); \
	} __WHILE0
#define __CPU_SET_S(cpu, setsize, cpusetp)                                   \
	__XBLOCK({                                                               \
		__size_t const __cpu = (cpu);                                        \
		__XRETURN((__cpu / 8 < (setsize))                                    \
		          ? ((cpusetp)->__bits[__CPUELT(__cpu)] |= __CPUMASK(__cpu)) \
		          : 0);                                                      \
	})
#define __CPU_CLR_S(cpu, setsize, cpusetp)                                    \
	__XBLOCK({                                                                \
		__size_t const __cpu = (cpu);                                         \
		__XRETURN((__cpu / 8 < (setsize))                                     \
		          ? ((cpusetp)->__bits[__CPUELT(__cpu)] &= ~__CPUMASK(__cpu)) \
		          : 0);                                                       \
	})
#define __CPU_ISSET_S(cpu, setsize, cpusetp)                                \
	__XBLOCK({                                                              \
		__size_t const __cpu = (cpu);                                       \
		__XRETURN((__cpu / 8 < (setsize)) &&                                \
		          ((cpusetp)->__bits[__CPUELT(__cpu)] & __CPUMASK(__cpu))); \
	})
#define __CPU_COUNT_S(setsize, cpusetp)                                          \
	__XBLOCK({                                                                   \
		__STDC_INT_AS_SIZE_T __res = 0;                                          \
		__cpu_mask const *__iter, *__end;                                        \
		__end = (__iter = (cpusetp)->__bits) + ((setsize) / sizeof(__cpu_mask)); \
		for (; __iter < __end; ++__iter)                                         \
			__res += __CPUMASK_POPCOUNT(*__iter);                                \
		__XRETURN __res;                                                         \
	})
#define __CPU_ISEMPTY_S(setsize, cpusetp)                                        \
	__XBLOCK({                                                                   \
		int __res = 1;                                                           \
		__cpu_mask const *__iter, *__end;                                        \
		__end = (__iter = (cpusetp)->__bits) + ((setsize) / sizeof(__cpu_mask)); \
		for (; __iter < __end; ++__iter)                                         \
			if (*__iter) {                                                       \
				__res = 0;                                                       \
				break;                                                           \
			}                                                                    \
		__XRETURN __res;                                                         \
	})

#define __CPU_EQUAL_S(setsize, cpusetp1, cpusetp2) \
	(!__libc_memcmp(cpusetp1, cpusetp2, setsize))
#define __CPU_OP_S(setsize, destset, srcset1, srcset2, op)          \
	__XBLOCK({                                                      \
		__cpu_set_t *const __dest      = (destset);                 \
		__cpu_mask const *const __arr1 = (srcset1)->__bits;         \
		__cpu_mask const *const __arr2 = (srcset2)->__bits;         \
		__SIZE_TYPE__ __i, __imax = (setsize) / sizeof(__cpu_mask); \
		for (__i = 0; __i < __imax; ++__i)                          \
			__dest->__bits[__i] = __arr1[__i] op __arr2[__i];       \
		__XRETURN __dest;                                           \
	})
#define __CPU_ALLOC_SIZE(count) \
	((((count) + __NCPUBITS - 1) / __NCPUBITS) * sizeof(__cpu_mask))
#define __CPU_ALLOC(count) \
	((__cpu_set_t *)__libc_calloc(((count) + __NCPUBITS - 1) / __NCPUBITS, sizeof(__cpu_mask)))
#define __CPU_FREE(cpuset) \
	__libc_free(cpuset)


#ifdef __CC__

#ifndef __sched_param_defined
#define __sched_param_defined 1
struct sched_param {
	int __sched_priority;
};
#endif /* !__sched_param_defined */

#if defined(__USE_GNU) || defined(__USE_KOS)
typedef int (__LIBCCALL *__clone_func_t)(void *__arg);
#ifdef __CRT_HAVE_clone
__LIBC __ATTR_NONNULL((1)) __pid_t __NOTHROW_NCX(__VLIBCCALL clone)(__clone_func_t __fn, void *__child_stack, int __flags, void *__arg, ... /* pid_t *ptid, void *newtls, pid_t *ctid */) __CASMNAME_SAME("clone");
#elif defined(__CRT_HAVE___clone)
__CVREDIRECT(__ATTR_NONNULL((1)),__pid_t,__NOTHROW_NCX,clone,(__clone_func_t __fn, void *__child_stack, int __flags, void *__arg),__clone,(__fn,__child_stack,__flags,__arg),__arg,3,(__pid_t,void *,__pid_t))
#endif /* clone... */
#ifdef __CRT_HAVE_unshare
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
__CDECLARE(,int,__NOTHROW_NCX,unshare,(int __flags),(__flags))
#endif /* unshare... */
#ifdef __CRT_HAVE_sched_getcpu
/* >> sched_getcpu(3)
 * Returns the number of the CPU for the calling thread.
 * Note that due to unforeseeable scheduling conditions, this may change at any
 * moment, even before this function returns, or before the caller was able to
 * act on its return value. For that reason, this function must only be taken
 * as a hint */
__CDECLARE(,int,__NOTHROW_NCX,sched_getcpu,(void),())
#endif /* sched_getcpu... */
#ifdef __CRT_HAVE_setns
/* >> setns(2)
 * With `FD' referring to a namespace, reassociate the calling thread with that namespace.
 * For this purpose, `FD' was opened for one of the files in `/proc/[pid]/ns/'
 * @param: nstype: The type of namespace to re-associate (either 0 to allow any
 *                 type of namespace, or one of `CLONE_NEWCGROUP', `CLONE_NEWIPC',
 *                `CLONE_NEWNET', `CLONE_NEWNS', `CLONE_NEWPID', `CLONE_NEWUSER',
 *                `CLONE_NEWUTS') */
__CDECLARE(,int,__NOTHROW_NCX,setns,(__fd_t __fd, int __nstype),(__fd,__nstype))
#endif /* setns... */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_exit_thread
/* Exits the current thread by invoking the SYS_exit system call,
 * after performing some additional cleanup not done by the kernel.
 * Assuming that the calling thread was constructed by `clone()',
 * calling this function has the same effect as returning `EXIT_CODE'
 * from `clone()'s `FN' callback */
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,exit_thread,(int __exit_code),(__exit_code))
#endif /* exit_thread... */
#endif /* __USE_KOS */
#endif /* __USE_GNU || __USE_KOS */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_SCHED_H */
