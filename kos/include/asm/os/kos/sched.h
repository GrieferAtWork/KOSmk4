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
/*!replace_with_include <asm/os/sched.h>*/
#ifndef _ASM_OS_KOS_SCHED_H
#define _ASM_OS_KOS_SCHED_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __CSIGNAL              __UINT32_C(0x000000ff) /* Signal mask to be sent at exit. */
#define __CLONE_VM             __UINT32_C(0x00000100) /* Set to share VM between processes. */
#define __CLONE_FS             __UINT32_C(0x00000200) /* Set to share fs info between processes. */
#define __CLONE_FILES          __UINT32_C(0x00000400) /* Set to share open files between processes. */
#define __CLONE_SIGHAND        __UINT32_C(0x00000800) /* Set to share signal handlers. */
#define __CLONE_PIDFD          __UINT32_C(0x00001000) /* Set to create+store pidfd at `*parent_tidptr' */
#define __CLONE_PTRACE         __UINT32_C(0x00002000) /* Set if tracing continues on the child. */
#define __CLONE_VFORK          __UINT32_C(0x00004000) /* Set if the parent wants the child to wake it up on `exec(2)' or `exit(2)'. */
#define __CLONE_PARENT         __UINT32_C(0x00008000) /* Set if we want to have the same parent as the cloner. */
#define __CLONE_THREAD         __UINT32_C(0x00010000) /* Set to add to same thread group. */
#define __CLONE_NEWNS          __UINT32_C(0x00020000) /* Set to create new namespace. */
#define __CLONE_SYSVSEM        __UINT32_C(0x00040000) /* Set to shared SVID SEM_UNDO semantics. */
#define __CLONE_SETTLS         __UINT32_C(0x00080000) /* Set TLS info. */
#define __CLONE_PARENT_SETTID  __UINT32_C(0x00100000) /* Store TID in userlevel buffer before MM copy. */
#define __CLONE_CHILD_CLEARTID __UINT32_C(0x00200000) /* Register exit futex and memory location to clear. */
#define __CLONE_DETACHED       __UINT32_C(0x00400000) /* Create clone detached. */
#define __CLONE_UNTRACED       __UINT32_C(0x00800000) /* Set if the tracing process can't force CLONE_PTRACE on this clone. */
#define __CLONE_CHILD_SETTID   __UINT32_C(0x01000000) /* Store TID in userlevel buffer in the child. */
#define __CLONE_NEWCGROUP      __UINT32_C(0x02000000) /* New cgroup namespace */
#define __CLONE_NEWUTS         __UINT32_C(0x04000000) /* New utsname group. */
#define __CLONE_NEWIPC         __UINT32_C(0x08000000) /* New ipcs. */
#define __CLONE_NEWUSER        __UINT32_C(0x10000000) /* New user namespace. */
#define __CLONE_NEWPID         __UINT32_C(0x20000000) /* New pid namespace. */
#define __CLONE_NEWNET         __UINT32_C(0x40000000) /* New network namespace. */
#define __CLONE_IO             __UINT32_C(0x80000000) /* Clone I/O context. */

/* For `clone3(2)' */
#define __CLONE_CLEAR_SIGHAND __UINT64_C(0x0000000100000000) /* Set all signal handlers to `SIG_DFL'. */
#define __CLONE_INTO_CGROUP   __UINT64_C(0x0000000200000000) /* Use `clone_args::cgroup' */
#define __CLONE_NEWTIME       __UINT64_C(0x0000000000000080) /* New time namespace */

#ifdef __KOS__
/* Set if credentials (user/group ids and special permissions) are  shared.
 * Note that during an `exec(2)', credentials are unshared unconditionally,
 * so it is impossible for 2 different programs to share credentials,  that
 * is unless you re-implement the kernel ELF loader in user-space and  roll
 * your own `execve(2)'... */
#define __CLONE_CRED          __UINT64_C(0x8000000000000000)
#endif /* __KOS__ */


#define __OFFSET_CLONE_ARGS_FLAGS        0
#define __OFFSET_CLONE_ARGS_PIDFD        8
#define __OFFSET_CLONE_ARGS_CHILD_TID    16
#define __OFFSET_CLONE_ARGS_PARENT_TID   24
#define __OFFSET_CLONE_ARGS_EXIT_SIGNAL  32
#define __OFFSET_CLONE_ARGS_STACK        40
#define __OFFSET_CLONE_ARGS_STACK_SIZE   48
#define __OFFSET_CLONE_ARGS_TLS          56
#define __OFFSET_CLONE_ARGS_SET_TID      64
#define __OFFSET_CLONE_ARGS_SET_TID_SIZE 72
#define __OFFSET_CLONE_ARGS_CGROUP       80
#define __SIZEOF_CLONE_ARGS              88

#ifdef __CC__
__DECL_BEGIN

#if __ALIGNOF_INT64__ < 8
__ATTR_ALIGNED(8)
#endif /* __ALIGNOF_INT64__ < 8 */
struct clone_args {
#if defined(__USE_KOS_ALTERATIONS) && defined(__COMPILER_HAVE_TRANSPARENT_UNION)
	union { __uint64_t     ca_flags; /*       */ __uint64_t __ca_al_flags; /*       */ }; /* Set of `CLONE_*' */
	union { __fd_t        *ca_pidfd; /*       */ __uint64_t __ca_al_pidfd; /*       */ }; /* [valid_if(CLONE_PIDFD)][type(fd_t *)] Where to store pidfd */
	union { __pid_t       *ca_child_tid; /*   */ __uint64_t __ca_al_child_tid; /*   */ }; /* [valid_if(CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID)][type(pid_t *)] Store child TID here in child memory */
	union { __pid_t       *ca_parent_tid; /*  */ __uint64_t __ca_al_parent_tid; /*  */ }; /* [valid_if(CLONE_PARENT_SETTID)][type(pid_t *)] Store child TID here in parent memory */
	union { __signo_t      ca_exit_signal; /* */ __uint64_t __ca_al_exit_signal; /* */ }; /* [type(signo_t)] Signal to send to parent on child exit */
	union { void          *ca_stack; /*       */ __uint64_t __ca_al_stack; /*       */ }; /* [valid_if(ca_stack_size != 0), type(void *)] Child stack base address */
	union { __size_t       ca_stack_size; /*  */ __uint64_t __ca_al_stack_size; /*  */ }; /* [if(CLONE_VM, [!= 0])] Child stack size (must be non-zero unless `CLONE_VM' is given) */
	union { void          *ca_tls; /*         */ __uint64_t __ca_al_tls; /*         */ }; /* [valid_if(CLONE_SETTLS)] Child TLS address */
	union { __pid_t const *ca_set_tid; /*     */ __uint64_t __ca_al_set_tid; /*     */ }; /* [valid_if(ca_set_tid_size != 0)][type(pid_t const *)] set-tid array base */
	union { __size_t       ca_set_tid_size; /**/ __uint64_t __ca_al_set_tid_size; /**/ }; /* [type(size_t)] set-tid array length */
	union { __fd_t         ca_cgroup; /*      */ __uint64_t __ca_al_cgroup; /*      */ }; /* [valid_if(CLONE_INTO_CGROUP)][type(fd_t)] cgroup file descriptor */
#else /* __USE_KOS_ALTERATIONS && __COMPILER_HAVE_TRANSPARENT_UNION */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("flags")
#pragma push_macro("pidfd")
#pragma push_macro("child_tid")
#pragma push_macro("parent_tid")
#pragma push_macro("exit_signal")
#pragma push_macro("stack")
#pragma push_macro("stack_size")
#pragma push_macro("tls")
#pragma push_macro("set_tid")
#pragma push_macro("set_tid_size")
#pragma push_macro("cgroup")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef flags
#undef pidfd
#undef child_tid
#undef parent_tid
#undef exit_signal
#undef stack
#undef stack_size
#undef tls
#undef set_tid
#undef set_tid_size
#undef cgroup
#if defined(__USE_KOS) && defined(__COMPILER_HAVE_TRANSPARENT_UNION)
	union { __uint64_t     ca_flags; /*       */ __uint64_t flags; /*       */ }; /* Set of `CLONE_*' */
	union { __fd_t        *ca_pidfd; /*       */ __uint64_t pidfd; /*       */ }; /* [valid_if(CLONE_PIDFD)][type(fd_t *)] Where to store pidfd */
	union { __pid_t       *ca_child_tid; /*   */ __uint64_t child_tid; /*   */ }; /* [valid_if(CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID)][type(pid_t *)] Store child TID here in child memory */
	union { __pid_t       *ca_parent_tid; /*  */ __uint64_t parent_tid; /*  */ }; /* [valid_if(CLONE_PARENT_SETTID)][type(pid_t *)] Store child TID here in parent memory */
	union { __signo_t      ca_exit_signal; /* */ __uint64_t exit_signal; /* */ }; /* [type(signo_t)] Signal to send to parent on child exit */
	union { void          *ca_stack; /*       */ __uint64_t stack; /*       */ }; /* [valid_if(ca_stack_size != 0), type(void *)] Child stack base address */
	union { __size_t       ca_stack_size; /*  */ __uint64_t stack_size; /*  */ }; /* [if(CLONE_VM, [!= 0])] Child stack size (must be non-zero unless `CLONE_VM' is given) */
	union { void          *ca_tls; /*         */ __uint64_t tls; /*         */ }; /* [valid_if(CLONE_SETTLS)] Child TLS address */
	union { __pid_t const *ca_set_tid; /*     */ __uint64_t set_tid; /*     */ }; /* [valid_if(ca_set_tid_size != 0)][type(pid_t const *)] set-tid array base */
	union { __size_t       ca_set_tid_size; /**/ __uint64_t set_tid_size; /**/ }; /* [type(size_t)] set-tid array length */
	union { __fd_t         ca_cgroup; /*      */ __uint64_t cgroup; /*      */ }; /* [valid_if(CLONE_INTO_CGROUP)][type(fd_t)] cgroup file descriptor */
#else /* __USE_KOS && __COMPILER_HAVE_TRANSPARENT_UNION */
	__uint64_t flags;        /* Set of `CLONE_*' */
	__uint64_t pidfd;        /* [valid_if(CLONE_PIDFD)][type(fd_t *)] Where to store pidfd */
	__uint64_t child_tid;    /* [valid_if(CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID)][type(pid_t *)] Store child TID here in child memory */
	__uint64_t parent_tid;   /* [valid_if(CLONE_PARENT_SETTID)][type(pid_t *)] Store child TID here in parent memory */
	__uint64_t exit_signal;  /* [type(signo_t)] Signal to send to parent on child exit */
	__uint64_t stack;        /* [valid_if(ca_stack_size != 0), type(void *)] Child stack base address */
	__uint64_t stack_size;   /* [if(CLONE_VM, [!= 0])] Child stack size (must be non-zero unless `CLONE_VM' is given) */
	__uint64_t tls;          /* [valid_if(CLONE_SETTLS)] Child TLS address */
	__uint64_t set_tid;      /* [valid_if(ca_set_tid_size != 0)][type(pid_t const *)] set-tid array base */
	__uint64_t set_tid_size; /* [type(size_t)] set-tid array length */
	__uint64_t cgroup;       /* [valid_if(CLONE_INTO_CGROUP)][type(fd_t)] cgroup file descriptor */
#ifdef __USE_KOS
#define ca_flags        flags
#define ca_pidfd        pidfd
#define ca_child_tid    child_tid
#define ca_parent_tid   parent_tid
#define ca_exit_signal  exit_signal
#define ca_stack        stack
#define ca_stack_size   stack_size
#define ca_tls          tls
#define ca_set_tid      set_tid
#define ca_set_tid_size set_tid_size
#define ca_cgroup       cgroup
#endif /* __USE_KOS */
#endif /* !__USE_KOS && !__COMPILER_HAVE_TRANSPARENT_UNION */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("cgroup")
#pragma pop_macro("set_tid_size")
#pragma pop_macro("set_tid")
#pragma pop_macro("tls")
#pragma pop_macro("stack_size")
#pragma pop_macro("stack")
#pragma pop_macro("exit_signal")
#pragma pop_macro("parent_tid")
#pragma pop_macro("child_tid")
#pragma pop_macro("pidfd")
#pragma pop_macro("flags")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__USE_KOS_ALTERATIONS || !__COMPILER_HAVE_TRANSPARENT_UNION */
};

__DECL_END
#endif /* __CC__ */

/* Scheduler policies (for `sched_setscheduler(2)') */
#define __SCHED_OTHER         0x00000000 /* ... */
#define __SCHED_FIFO          0x00000001 /* ... */
#define __SCHED_RR            0x00000002 /* ... */
#define __SCHED_BATCH         0x00000003 /* ... */
#define __SCHED_IDLE          0x00000005 /* ... */
#define __SCHED_RESET_ON_FORK 0x40000000 /* ... */

#endif /* !_ASM_OS_KOS_SCHED_H */
