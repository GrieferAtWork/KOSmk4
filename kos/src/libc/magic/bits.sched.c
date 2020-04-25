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

%[define_replacement(cpu_set_t = __cpu_set_t)]

%(user){

#ifndef __cpu_set_t_defined
#define __cpu_set_t_defined 1
typedef __cpu_set_t    cpu_set_t;
#endif /* !__cpu_set_t_defined */

}

%{
#include <features.h>

#include <hybrid/__bit.h>

#include <asm/sched.h>
#include <bits/types.h>

#include <libc/malloc.h>
#include <libc/string.h>

#ifdef __USE_KOS
#include <hybrid/host.h>

#include <bits/signum-values.h>
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
	 __PRIVATE_CLONE_IO)

/* Same flags as used by fork() */
#ifdef __SIGCHLD
#define CLONE_NEW_PROCESS (__SIGCHLD)
#else /* __SIGCHLD */
#define CLONE_NEW_PROCESS 0
#endif /* !__SIGCHLD */

#endif /* __USE_KOS */
#endif /* __USE_GNU || __USE_KOS */



#ifndef __CPU_SETSIZE
#define __CPU_SETSIZE       256
#endif /* !__CPU_SETSIZE */

#define __SIZEOF_CPU_SET_T__  (__CPU_SETSIZE / 8)
#define __NCPUBITS            (8*sizeof(__cpu_mask))
#define __SIZEOF_CPU_MASK__    4
#define __CPUELT(cpuno)         ((cpuno)/__NCPUBITS)
#define __CPUMASK(cpuno)        ((__cpu_mask)1 << ((cpuno)%__NCPUBITS))
#ifdef __CC__
typedef __UINT32_TYPE__ __cpu_mask;
typedef struct __cpu_set_struct {
	__cpu_mask __bits[__CPU_SETSIZE / __NCPUBITS];
} __cpu_set_t;
#endif /* __CC__ */
#define __CPU_SETNONE   { { [0 ... __CPUELT(__CPU_SETSIZE) - 1] = 0 } }
#define __CPU_SETALL    { { [0 ... __CPUELT(__CPU_SETSIZE) - 1] = (__cpu_mask)-1 } }
#if defined(__GNUC__) && 0
#define __CPU_SETONE(i)                                                               \
	_Pragma("GCC diagnostic push")                                                    \
	_Pragma("GCC diagnostic ignored \"-Woverride-init\"")                             \
		{ { [0 ... __CPUELT(__CPU_SETSIZE) - 1] = 0, [__CPUELT(i)] = __CPUMASK(i) } } \
	_Pragma("GCC diagnostic pop")
#elif 1
#define __CPU_SETONE(i)                                                                                          \
	{                                                                                                            \
		{                                                                                                        \
			[0 ... ((i) < __NCPUBITS ? 0 : __CPUELT(i) - 1)] = (i) < __NCPUBITS ? __CPUMASK(i) : 0,              \
			[((i) < __NCPUBITS ? 1 : __CPUELT(i)) ... (((i) < __NCPUBITS || (i) >= (__CPU_SETSIZE - __NCPUBITS)) \
			                                           ? __CPUELT(__CPU_SETSIZE) - 2                             \
			                                           : __CPUELT(i))] =                                         \
				((i) < __NCPUBITS || (i) >= (__CPU_SETSIZE - __NCPUBITS)) ? 0 : __CPUMASK(i),                    \
			[(((i) < __NCPUBITS || (i) >= (__CPU_SETSIZE - __NCPUBITS))                                          \
			  ? __CPUELT(__CPU_SETSIZE) - 1                                                                      \
			  : __CPUELT(i) + 1) ...  __CPUELT(__CPU_SETSIZE) - 1] =                                             \
				(i) >= (__CPU_SETSIZE - __NCPUBITS) ? __CPUMASK(i) : 0                                           \
		}                                                                                                        \
	}
#else /* ... */
#define __CPU_SETONE(i) \
	{{[0 ... __CPUELT(__CPU_SETSIZE)-1] = 0, [__CPUELT(i)] = __CPUMASK(i)}}
#endif /* !... */

#if __SIZEOF_CPU_MASK__ <= 1
#define __CPUMASK_POPCOUNT __hybrid_popcount8
#elif __SIZEOF_CPU_MASK__ <= 2
#define __CPUMASK_POPCOUNT __hybrid_popcount16
#elif __SIZEOF_CPU_MASK__ <= 4
#define __CPUMASK_POPCOUNT __hybrid_popcount32
#elif __SIZEOF_CPU_MASK__ <= 8
#define __CPUMASK_POPCOUNT __hybrid_popcount64
#else /* ... */
#error "Unsupported __SIZEOF_CPU_MASK__"
#endif /* !... */

#define __CPU_FILL_S(setsize, cpusetp) __libc_memset(cpusetp, 0xff, setsize)
#define __CPU_ZERO_S(setsize, cpusetp) __libc_memset(cpusetp, 0x00, setsize)
#ifndef __NO_XBLOCK
#define __CPU_SET_S(cpuno, setsize, cpusetp)                                           \
	__XBLOCK({                                                                         \
		__size_t const __cs_cpuno = (cpuno);                                           \
		__XRETURN((__cs_cpuno / 8 < (setsize))                                         \
		          ? ((cpusetp)->__bits[__CPUELT(__cs_cpuno)] |= __CPUMASK(__cs_cpuno)) \
		          : 0);                                                                \
	})
#define __CPU_CLR_S(cpuno, setsize, cpusetp)                                            \
	__XBLOCK({                                                                          \
		__size_t const __cs_cpuno = (cpuno);                                            \
		__XRETURN((__cs_cpuno / 8 < (setsize))                                          \
		          ? ((cpusetp)->__bits[__CPUELT(__cs_cpuno)] &= ~__CPUMASK(__cs_cpuno)) \
		          : 0);                                                                 \
	})
#define __CPU_ISSET_S(cpuno, setsize, cpusetp)                                        \
	__XBLOCK({                                                                        \
		__size_t const __cs_cpuno = (cpuno);                                          \
		__XRETURN((__cs_cpuno / 8 < (setsize)) &&                                     \
		          ((cpusetp)->__bits[__CPUELT(__cs_cpuno)] & __CPUMASK(__cs_cpuno))); \
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

#define __PRIVATE_CPU_OP_S(setsize, destset, srcset1, srcset2, op)  \
	__XBLOCK({                                                      \
		__cpu_set_t *const __dest      = (destset);                 \
		__cpu_mask const *const __arr1 = (srcset1)->__bits;         \
		__cpu_mask const *const __arr2 = (srcset2)->__bits;         \
		__SIZE_TYPE__ __i, __imax = (setsize) / sizeof(__cpu_mask); \
		for (__i = 0; __i < __imax; ++__i)                          \
			__dest->__bits[__i] = __arr1[__i] op __arr2[__i];       \
		__XRETURN __dest;                                           \
	})
#define __CPU_AND_S(setsize, destset, srcset1, srcset2) __PRIVATE_CPU_OP_S(setsize, destset, srcset1, srcset2, &)
#define __CPU_OR_S(setsize, destset, srcset1, srcset2)  __PRIVATE_CPU_OP_S(setsize, destset, srcset1, srcset2, |)
#define __CPU_XOR_S(setsize, destset, srcset1, srcset2) __PRIVATE_CPU_OP_S(setsize, destset, srcset1, srcset2, ^)
#else /* !__NO_XBLOCK */
#define __CPU_SET_S(cpuno, setsize, cpusetp)                    \
	(((cpuno) / 8 < (setsize))                                  \
	 ? ((cpusetp)->__bits[__CPUELT(cpuno)] |= __CPUMASK(cpuno)) \
	 : 0)
#define __CPU_CLR_S(cpuno, setsize, cpusetp)                     \
	(((cpuno) / 8 < (setsize))                                   \
	 ? ((cpusetp)->__bits[__CPUELT(cpuno)] &= ~__CPUMASK(cpuno)) \
	 : 0)
#define __CPU_ISSET_S(cpuno, setsize, cpusetp) \
	(((cpuno) / 8 < (setsize)) && ((cpusetp)->__bits[__CPUELT(cpuno)] & __CPUMASK(cpuno)))
__LOCAL __ATTR_PURE __STDC_INT_AS_SIZE_T
(__cpu_count_s_impl)(__SIZE_TYPE__ __count, __cpu_mask const *__cpusetp) {
	__STDC_INT_AS_SIZE_T __res = 0;
	__cpu_mask const *__iter, *__end;
	__end = (__iter = __cpusetp) + (__count / sizeof(__cpu_mask));
	for (; __iter < __end; ++__iter)
		__res += __CPUMASK_POPCOUNT(*__iter);
	return __res;
}
#define __CPU_COUNT_S(setsize, cpusetp) \
	__cpu_count_s_impl((__SIZE_TYPE__)(setsize), (cpusetp)->__bits)
__LOCAL __ATTR_PURE int
(__cpu_isempty_s_impl)(__SIZE_TYPE__ __count, __cpu_mask const *__cpusetp) {
	__cpu_mask const *__iter, *__end;
	__end = (__iter = __cpusetp) + (__count / sizeof(__cpu_mask));
	for (; __iter < __end; ++__iter) {
		if (*__iter)
			return 0;
	}
	return 1;
}
#define __CPU_ISEMPTY_S(setsize, cpusetp) \
	__cpu_isempty_s_impl((__SIZE_TYPE__)(setsize), (cpusetp)->__bits)
#define __PRIVATE_DEFINE_CPU_OP_S(name, op)                                           \
	__LOCAL __cpu_set_t *(name)(__SIZE_TYPE__ __count, __cpu_set_t *__dest,           \
	                            __cpu_mask const *__arr1, __cpu_mask const *__arr2) { \
		__SIZE_TYPE__ __i, __imax = __count / sizeof(__cpu_mask);                     \
		for (__i = 0; __i < __imax; ++__i)                                            \
			__dest->__bits[__i] = __arr1[__i] op __arr2[__i];                         \
		return __dest;                                                                \
	}
__PRIVATE_DEFINE_CPU_OP_S(__cpu_and_s_impl, &)
__PRIVATE_DEFINE_CPU_OP_S(__cpu_or_s_impl, |)
__PRIVATE_DEFINE_CPU_OP_S(__cpu_xor_s_impl, ^)
#undef __PRIVATE_DEFINE_CPU_OP_S
#define __CPU_AND_S(setsize, destset, srcset1, srcset2) \
	__cpu_and_s_impl((__SIZE_TYPE__)(setsize), destset, (srcset1)->__bits, (srcset2)->__bits)
#define __CPU_OR_S(setsize, destset, srcset1, srcset2) \
	__cpu_or_s_impl((__SIZE_TYPE__)(setsize), destset, (srcset1)->__bits, (srcset2)->__bits)
#define __CPU_XOR_S(setsize, destset, srcset1, srcset2) \
	__cpu_xor_s_impl((__SIZE_TYPE__)(setsize), destset, (srcset1)->__bits, (srcset2)->__bits)
#endif /* __NO_XBLOCK */
#define __CPU_EQUAL_S(setsize, cpusetp1, cpusetp2) \
	(__libc_memcmp(cpusetp1, cpusetp2, setsize) == 0)
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

}

%[default_impl_section(.text.crt.sched.utility)]

%#if defined(__USE_GNU) || defined(__USE_KOS)
%typedef int (__LIBCCALL *__clone_func_t)(void *__arg);

[section(.text.crt.sched.access)]
[vartypes($pid_t,void *,$pid_t)][export_alias(__clone)]
clone:([nonnull] __clone_func_t fn, void *child_stack, int flags,
       void *arg, ... /* pid_t *ptid, void *newtls, pid_t *ctid */) -> $pid_t;

@@>> unshare(2)
@@Unshare certain components of the calling thread that may be shared with other
@@threads or processes, such as the filesystem, or opened file descriptors.
@@When being unshared, the calling thread's descriptor for a specific component
@@is replaced with a copy of its previous contents at that moment in time, with
@@the notable exception of certain KOS-specific extensions, where specifically
@@marked data will be deleted (s.a. `O_CLOFORK' and `PROT_LOOSE')
@@The behavior and meaning of individual bits in `flags' matches their meaning
@@when passed to `clone()', except that for certain flags the meaning is reversed.
@@For example: Passing `CLONE_FILES' to `clone(2)' will cause handles to be shared,
@@             but passing it to `unshare(2)' will cause handles to be unshared.
@@@param: flags: Set of `CLONE_*' flags:
@@                - CLONE_FILES:     Unshare handles (and close all marked as `O_CLOFORK')
@@                - CLONE_FS:        Unshare umask(), chroot(), chdir(), fsmode() and drive-cwds
@@                - CLONE_NEWCGROUP: ...
@@                - CLONE_NEWIPC:    ...
@@                - CLONE_NEWNET:    ...
@@                - CLONE_NEWNS:     Unshare the mount namespace
@@                - CLONE_NEWPID:    Unshare the PID namespace
@@                - CLONE_NEWUSER:   ...
@@                - CLONE_NEWUTS:    ...
@@                - CLONE_SYSVSEM:   ...
@@                - CLONE_VM:        Unshare the current VM (KOS extension)
@@                - CLONE_SIGHAND:   Unshare signal handlers (KOS extension)
unshare:(int flags) -> int;

@@>> sched_getcpu(3)
@@Returns the number of the CPU for the calling thread.
@@Note that due to unforeseeable scheduling conditions, this may change at any
@@moment, even before this function returns, or before the caller was able to
@@act on its return value. For that reason, this function must only be taken
@@as a hint
sched_getcpu:() -> int;

@@>> setns(2)
@@With `FD' referring to a namespace, reassociate the calling thread with that namespace.
@@For this purpose, `FD' was opened for one of the files in `/proc/[pid]/ns/'
@@@param: nstype: The type of namespace to re-associate (either 0 to allow any
@@                type of namespace, or one of `CLONE_NEWCGROUP', `CLONE_NEWIPC',
@@               `CLONE_NEWNET', `CLONE_NEWNS', `CLONE_NEWPID', `CLONE_NEWUSER',
@@               `CLONE_NEWUTS')
setns:($fd_t fd, int nstype) -> int;

%
%#ifdef __USE_KOS
@@Exits the current thread by invoking the SYS_exit system call,
@@after performing some additional cleanup not done by the kernel.
@@Assuming that the calling thread was constructed by `clone()',
@@calling this function has the same effect as returning `EXIT_CODE'
@@from `clone()'s `FN' callback
[section(.text.crt.sched.access)]
[ATTR_NORETURN] exit_thread:(int exit_code);
%#endif /* __USE_KOS */
%#endif /* __USE_GNU || __USE_KOS */


%{
#endif /* __CC__ */

__SYSDECL_END

}