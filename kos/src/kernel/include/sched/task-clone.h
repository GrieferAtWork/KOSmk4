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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_TASK_CLONE_H
#define GUARD_KERNEL_INCLUDE_SCHED_TASK_CLONE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/arch/task-clone.h>

#include <asm/asmword.h>
#include <asm/os/sched.h>

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
#if !defined(CLONE_CRED) && defined(__CLONE_CRED)
#define CLONE_CRED           __CLONE_CRED           /* Set if credentials (user/group ids and special permissions) are shared. \
                                                     * Note that during  an exec() credentials  are unshared  unconditionally. */
#endif /* !CLONE_CRED && __CLONE_CRED */
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

#ifdef __CC__
DECL_BEGIN

/* High-level implementation for the `clone(2)' system call.
 * @param: init_state:    The CPU state of the thead that called `clone(2)'
 * @param: clone_flags:   Set of `CLONE_*' (as defined in <sched.h>)
 * @param: parent_tidptr: [valid_if(CLONE_PARENT_SETTID)]
 *                        Store child TID here in parent process
 * @param: child_tidptr:  [valid_if(CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID)]
 *                        Store child TID here in child process
 * @param: ARCH_CLONE__PARAMS: Additional, arch-specific parameters */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *KCALL
task_clone(struct icpustate const *__restrict init_state,
           syscall_ulong_t clone_flags,
           USER UNCHECKED pid_t *parent_tidptr,
           USER UNCHECKED pid_t *child_tidptr
           ARCH_CLONE__PARAMS)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);




#ifdef CONFIG_BUILDING_KERNEL_CORE

/* Define a per-task relocation that must be initialized as:
 * >> struct task *thread = THREAD_TO_INITIALIZE;
 * >> *(uintptr_t *)((byte_t *)thread + addr) += (uintptr_t)thread; */
#define DEFINE_PERTASK_RELOCATION(addr)                    \
	__asm__(".pushsection .rodata.pertask.relocations\n\t" \
	        "\t.wordptr %p0\n\t"                           \
	        ".popsection"                                  \
	        : : "X" (addr))

/* Initialize task relocations, as defined by `DEFINE_PERTASK_RELOCATION()' */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _task_init_relocations)(struct task *__restrict self);

/* Do some additional arch-specific initialization that should be
 * done just before `FORTASK(self, this_sstate)' will be assigned.
 *
 * @param: child:    The new thread that is being initialized
 * @param: caller:   The calling thread (THIS_TASK)
 * @param: p_sstate: `struct scpustate **' Pointer to the state
 *                   that will be assigned to `this_sstate' once
 *                   this function returns. */
#ifndef _task_init_arch_sstate
#define _task_init_arch_sstate(child, caller, p_sstate) (void)0
#endif /* !_task_init_arch_sstate */

#endif /* CONFIG_BUILDING_KERNEL_CORE */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_TASK_CLONE_H */
