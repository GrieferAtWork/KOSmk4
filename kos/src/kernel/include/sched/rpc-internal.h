/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_RPC_INTERNAL_H
#define GUARD_KERNEL_INCLUDE_SCHED_RPC_INTERNAL_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_RPC
#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/signal.h> /* `struct sig' */

#include <hybrid/sequence/list.h>

#include <bits/os/siginfo.h>
#include <kos/rpc.h>

#define rpc_entry                  pending_rpc        /* !DEPRECATED! */
#define task_free_rpc              pending_rpc_free   /* !DEPRECATED! */
#define task_push_asynchronous_rpc task_asyncrpc_push /* !DEPRECATED! */

#ifdef __CC__
DECL_BEGIN

/* Possible values for `struct pending_user_rpc::pur_status' */
#define PENDING_USER_RPC_STATUS_PENDING  0 /* RPC program is pending execution, or is currently executing */
#define PENDING_USER_RPC_STATUS_COMPLETE 1 /* RPC program has completed successfully */
#define PENDING_USER_RPC_STATUS_CANCELED 2 /* RPC program was canceled.  Can either be ATOMIC_CMPXCH'd  from
                                            * `PENDING_USER_RPC_STATUS_PENDING' by the sender, in which case
                                            * the  RPC program will be aborted and modifications it made are
                                            * silently  discarded, or set by the target thread itself as the
                                            * result of it terminating prior to being able to serve the RPC,
                                            * which  can be checked by testing `this_rpcs' of the target for
                                            * being equal to `THIS_RPCS_TERMINATED'. */

struct pending_rpc;
struct pending_user_rpc {
	WEAK refcnt_t                                        pur_refcnt; /* Reference counter. */
	unsigned int                                         pur_status; /* RPC status (one of `PENDING_USER_RPC_STATUS_*') */
	struct sig                                           pur_stchng; /* Signal broadcast when `pur_status' is changed
	                                                                  * by someone  other than  the original  sender. */
	REF struct mman                                     *pur_mman;   /* [1..1][const] The mman within which `pur_prog' resides. */
	USER CHECKED void const                             *pur_prog;   /* [1..1][const] Userspace RPC program */
	size_t                                               pur_argc;   /* [const] # of program arguments. */
	COMPILER_FLEXIBLE_ARRAY(USER UNCHECKED void const *, pur_argv);  /* [?..?][const] Vector of program arguments. */
};

#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */

#ifndef __sigset_t_defined
#define __sigset_t_defined
struct __sigset_struct;
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

struct pending_rpc {
	SLIST_ENTRY(pending_rpc) pr_link;  /* [0..1][lock(ATOMIC)] Link in the list of pending RPCs */
	uintptr_t                pr_flags; /* [const] RPC flags: RPC_CONTEXT_KERN, ...
	                                    * NOTE: When `RPC_CONTEXT_INACTIVE' is set, then the RPC is inactive. */
	union {
		struct {
			prpc_exec_callback_t k_func;   /* [1..1][const] Function to invoke. */
			void                *k_cookie; /* [?..?][const] Cookie argument for `k_func' */
		}                       pr_kern;   /* [RPC_CONTEXT_KERN] Kernel-mode RPC */
		struct pending_user_rpc pr_user;   /* [!RPC_CONTEXT_KERN && !RPC_CONTEXT_SIGNAL] User-mode RPC */
		siginfo_t               pr_psig;   /* [!RPC_CONTEXT_KERN && RPC_CONTEXT_SIGNAL] Posix signal
		                                    * NOTE: In this case, `pr_flags & RPC_SIGNO_MASK' must encode
		                                    *       the same signal  number as `pr_psig.si_signo'.  Else,
		                                    *       the incorrect signal is used during sigmask checks
		                                    * NOTE: Only thread-specific posix signals appear here! */
	};
};


/* Destroy a "!RPC_CONTEXT_KERN && !RPC_CONTEXT_SIGNAL"-rpc once `self->pr_user.pur_refcnt == 0' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _pending_rpc_destroy_user)(struct pending_rpc *__restrict self);
#define _pending_user_rpc_destroy(self) \
	_pending_rpc_destroy_user(COMPILER_CONTAINER_OF(self, struct pending_rpc, pr_user))
DEFINE_REFCOUNT_FUNCTIONS(struct pending_user_rpc, pur_refcnt, _pending_user_rpc_destroy)

#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */

/* Alloc/free functions used for `struct pending_rpc' */
#define pending_rpc_alloc(size, gfp)    ((struct pending_rpc *)kmalloc(size, gfp))
#define pending_rpc_alloc_nx(size, gfp) ((struct pending_rpc *)kmalloc_nx(size, gfp))
#define pending_rpc_alloc_kern(gfp)     pending_rpc_alloc(COMPILER_OFFSETAFTER(struct pending_rpc, pr_kern), gfp)
#define pending_rpc_alloc_kern_nx(gfp)  pending_rpc_alloc_nx(COMPILER_OFFSETAFTER(struct pending_rpc, pr_kern), gfp)
#define pending_rpc_alloc_psig(gfp)     pending_rpc_alloc(COMPILER_OFFSETAFTER(struct pending_rpc, pr_psig), gfp)
#define pending_rpc_alloc_psig_nx(gfp)  pending_rpc_alloc_nx(COMPILER_OFFSETAFTER(struct pending_rpc, pr_psig), gfp)
#define pending_rpc_free(self)          __os_free(self)


#ifndef __pending_rpc_slist_defined
#define __pending_rpc_slist_defined
SLIST_HEAD(pending_rpc_slist, pending_rpc);
#endif /* !__pending_rpc_slist_defined */

/* [0..n][lock(INSERT(ATOMIC), CLEAR(ATOMIC && THIS_TASK))]
 * Pending RPCs. (Set of `THIS_RPCS_TERMINATED' when RPCs may no longer
 * be executed, and all that were there prior to this becoming the case
 * are/were serviced with `RPC_REASONCTX_SHUTDOWN') */
DATDEF ATTR_PERTASK struct pending_rpc_slist this_rpcs;
#define THIS_RPCS_TERMINATED ((struct pending_rpc *)-1)


/* Schedule the given `rpc' for execution on `thread'.
 * NOTE: Be mindful of the scenario  where `thread == THIS_TASK', in which  case
 *       this function will return like normal, and the RPC will only be noticed
 *       the next time you make a call to `task_serve()'!
 * NOTE: The caller must initialize:
 *       - `rpc->pr_flags'
 *       - `rpc->pr_kern' or `rpc->pr_user' or `rpc->pr_psig'
 * @return: true:  Success. (Even if the thread terminates before the RPC can be served
 *                 normally, it will still  be served as `RPC_REASONCTX_SHUTDOWN'  when
 *                 true has been returned here)
 * @return: false: The target thread has already terminated. */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL
NOTHROW(FCALL task_rpc_schedule)(struct task *__restrict thread,
                                 /*inherit(on_success)*/ struct pending_rpc *__restrict rpc);

/* Same as `task_rpc_schedule()', but schedule the RPC for execution by
 * some arbitrary thread apart of the same process as `thread_in_proc'.
 * NOTE: Process-directed user-RPCs must not make use of `RPC_SYNCMODE_F_REQUIRE_SC'
 *       or `RPC_SYNCMODE_F_REQUIRE_CP'. Attempting to do so causes this function to
 *       trigger an internal assertion check.
 *       All other RPC functionality works as expected, though obviously  RPCs
 *       will be served by some arbitrary thread within the specified process.
 * @return: true:  Success. (Even if the process terminates before the RPC can be served
 *                 normally, it will  still be served  as `RPC_REASONCTX_SHUTDOWN'  when
 *                 true has been returned here)
 * @return: false: The target process was marked as having terminated. */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL
NOTHROW(FCALL proc_rpc_schedule)(struct task *__restrict thread_in_proc,
                                 /*inherit(on_success)*/ struct pending_rpc *__restrict rpc);

/* Gather the set of posix signal numbers used by pending RPCs
 * of calling thread or process.  These functions are used  to
 * implement the `sigpending(2)' system call. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_rpc_pending_sigset)(/*out*/ sigset_t *__restrict result);
FUNDEF NONNULL((1)) void FCALL
proc_rpc_pending_sigset(/*out*/ sigset_t *__restrict result)
		THROWS(E_WOULDBLOCK);

/* Check if an RPCs routed via one of `these' signals is pending. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL task_rpc_pending_oneof)(sigset_t const *__restrict these);
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
proc_rpc_pending_oneof(sigset_t const *__restrict these)
		THROWS(E_WOULDBLOCK);
/* @return: * : One of `PROC_RPC_TRYPENDING_ONEOF_*' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) int
NOTHROW(FCALL proc_rpc_trypending_oneof)(sigset_t const *__restrict these);
#define PROC_RPC_TRYPENDING_ONEOF_NO         0    /* None of `these' are pending */
#define PROC_RPC_TRYPENDING_ONEOF_YES        1    /* (At least) one of `these' is pending */
#define PROC_RPC_TRYPENDING_ONEOF_WOULDBLOCK (-1) /* Operation would block. */



/* Steal pending RPC (that must be a posix signal) with uses a
 * signal number that is a member of `these'. When no such RPC
 * exists, return `NULL' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) /*inherit*/ struct pending_rpc *
NOTHROW(FCALL task_rpc_pending_steal_posix_signal)(sigset_t const *__restrict these);
FUNDEF WUNUSED NONNULL((1)) /*inherit*/ struct pending_rpc *FCALL
proc_rpc_pending_steal_posix_signal(sigset_t const *__restrict these)
		THROWS(E_WOULDBLOCK);

/* Same  as `proc_rpc_pending_steal_posix_signal()', but only _try_ to
 * acquire the  necessary lock  to `THIS_PROCESS_RPCS.ppr_lock'.  When
 * doing so fails, `PROC_RPC_PENDING_TRYSTEAL_POSIX_SIGNAL_WOULDBLOCK'
 * is returned. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) /*inherit*/ struct pending_rpc *
NOTHROW(FCALL proc_rpc_pending_trysteal_posix_signal)(sigset_t const *__restrict these);
#define PROC_RPC_PENDING_TRYSTEAL_POSIX_SIGNAL_WOULDBLOCK ((struct pending_rpc *)-1)



/************************************************************************/
/* Internal RPC execution helpers                                       */
/************************************************************************/

/* Trigger RPC completion for `self' with context `RPC_REASONCTX_SHUTDOWN' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_asyncrpc_destroy_for_shutdown)(struct pending_rpc *__restrict self);
/* Same as `task_asyncrpc_destroy_for_shutdown()', but do an entire list. */
FUNDEF NOBLOCK void NOTHROW(FCALL task_asyncrpc_destroy_list_for_shutdown)(struct pending_rpc *first);

/* Arch-specific function:
 * Execute the given `func' using the register state at the time of
 * the call to this function,  whilst passing the given  `context'. */
FUNDEF NONNULL((1, 2)) void FCALL
task_asyncrpc_execnow(struct rpc_context *__restrict context,
                      prpc_exec_callback_t func, void *cookie DFL(__NULLPTR));

/* Arch-specific function:
 * Alter the given `state' to inject a call to `func'. The context
 * argument passed to  `func' will use  `RPC_REASONCTX_ASYNC_KERN'
 * or `RPC_REASONCTX_SYSRET' as reason. */
FUNDEF NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_asyncrpc_push)(struct scpustate *__restrict state,
                                  prpc_exec_callback_t func,
                                  void *cookie DFL(__NULLPTR));

/* Execute a user-space RPC program
 * @param: reason:  One of `_RPC_REASONCTX_ASYNC', `_RPC_REASONCTX_SYNC' or `_RPC_REASONCTX_SYSCALL'
 * @param: sc_info: [valid_if(reason == _RPC_REASONCTX_SYSCALL)] System call information. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) rpc_cpustate_t *FCALL
task_userrpc_runprogram(rpc_cpustate_t *__restrict state, struct pending_rpc *__restrict rpc,
                        unsigned int reason, struct rpc_syscall_info const *sc_info);

/* Mark  the given `rpc' as canceled. This function is guarantied to
 * not be called at the same time as `task_userrpc_runprogram()', as
 * it is only used to  implement handling for `!RPC_CONTEXT_KERN  &&
 * !RPC_CONTEXT_SIGNAL' RPCs left-over during thread/process exit. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_userrpc_cancelprogram)(struct pending_rpc *__restrict rpc);



DECL_END
#endif /* __CC__ */

#else /* CONFIG_USE_NEW_RPC */
#include <kernel/types.h>

#include "rpc.h"

DECL_BEGIN

/* Flags for `struct rpc_entry::re_kind'
 *
 * HINT (relation of flags/functions in the sense of semantics):
 * ```
 *   == INTERNAL =======    == KERNEL-API ===========    == USER-API ====================
 *   RPC_KIND_INTERRUPT     TASK_USER_RPC_FINTR          ~RPC_SCHEDULE_FLAG_NOINTERRUPT
 *   RPC_KIND_USER_SYNC     TASK_USER_RPC_FSYNC          RPC_SCHEDULE_SYNC, ~RPC_SCHEDULE_ASYNC
 *   RPC_KIND_NONSYSCALL    TASK_USER_RPC_FNONSYSCALL    RPC_SCHEDULE_FLAG_NONSYSCALL
 *   RPC_KIND_NOTHROW       TASK_USER_RPC_FNOTHROW
 *                          <task_waitfor(re_done)>      RPC_SCHEDULE_FLAG_WAITFORSTART
 *                          TASK_RPC_FWAITFOR            RPC_SCHEDULE_FLAG_WAITSMPACK
 *                          TASK_RPC_FDONTWAKE           RPC_SCHEDULE_FLAG_DONTWAKE
 *                          TASK_RPC_FHIGHPRIO           RPC_SCHEDULE_FLAG_HIGHPRIO
 * ```
 */
#define RPC_KIND_SYNC            0x0000 /* Synchronous RPC */
#define RPC_KIND_USER            0x0001 /* User RPC (service before returning to user-space) */
#define RPC_KIND_INTERRUPT       0x0002 /* Interrupting user RPC (throw an `E_INTERRUPT_USER_RPC') */
#define RPC_KIND_USER_INTR       0x0003 /* Interrupting user RPC (== RPC_KIND_USER | RPC_KIND_INTERRUPT) */
#define RPC_KIND_USER_SYNC       0x0004 /* Synchronous user-level RPC (Only service before user-space, and after a call to `task_serve()') */
#define RPC_KIND_USER_INTR_SYNC  0x0007 /* Synchronous user-level RPC (== RPC_KIND_USER | RPC_KIND_INTERRUPT | RPC_KIND_USER_SYNC) */
#define RPC_KIND_MASK            0x000f /* Mask for the RPC kind. */
#define RPC_KIND_NOTHROW         0x0010 /* FLAG: Non-throwing RPC */
#define RPC_KIND_NONSYSCALL      0x0400 /* FLAG: (for `RPC_KIND_USER_INTR_SYNC'): The RPC may be serviced for reasons other than `TASK_RPC_REASON_SYSCALL' */
#define RPC_KIND_CANSERVE        0x0800 /* FLAG: (for `RPC_KIND_USER_INTR_SYNC'): The thread did invoke `task_serve()' (set internally ) */

#ifdef __CC__
struct rpc_entry {
	/* TODO: Replace this with `SLIST_ENTRY(rpc_entry) re_next;' */
	struct rpc_entry *re_next; /* [0..1][const] Next pending RPC function. */
	task_rpc_t        re_func; /* [1..1][const][valid_if(!RPC_KIND_SRPC)] RPC function. */
	void             *re_arg;  /* [?..?][const] RPC argument. */
	uintptr_t         re_kind; /* [const] The kind of RPC (One of `RPC_KIND_*'). */
};


/* Allocate an  RPC entry  for  later delivery  without having  to  deal with  the  possibility
 * of  a  bad   allocation  at   that  later   point  in   time.  (s.a.   `task_deliver_rpc()')
 * These functions behave identical to their `task_schedule_*' counterparts from <sched/rpc.h>,
 * except that the  caller is  not required  to specify the  eventual target  thread just  yet.
 * NOTE: Prior to commiting an RPC allocation by one of these functions through `task_deliver_rpc()',
 *       the caller is free to  make use of the returned  RPC's `re_next' field for whatever  purpose
 *       they deem  useful, allowing  the  caller to  allocate  a number  of  RPCs at  once,  without
 *       having to set up a secondary vector for storing them before using them.
 *    -> The main purpose of  these APIs is  to provide a  means of pre-allocating  synchronous
 *       RPC descriptors beforehand, allowing them  to later be used  in a scenario where  code
 *       would no longer be capable of dealing with a bad allocation error that should normally
 *       arise if the regular `task_schedule_*' functions were to be used.
 * NOTE: The *_nx variants return `NULL' if the allocation failed. */
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED
ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) struct rpc_entry *
(KCALL task_alloc_user_rpc)(task_rpc_t func,
                            void *arg DFL(__NULLPTR),
                            uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_USER_RPC_FNORMAL),
                            gfp_t rpc_gfp DFL(GFP_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) ATTR_MALLOC WUNUSED NONNULL((1)) struct rpc_entry *
NOTHROW(KCALL task_alloc_user_rpc_nx)(task_rpc_t func,
                                      void *arg DFL(__NULLPTR),
                                      uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_USER_RPC_FNORMAL),
                                      gfp_t rpc_gfp DFL(GFP_NORMAL));
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) WUNUSED
ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) struct rpc_entry *
(KCALL task_alloc_synchronous_rpc)(task_rpc_t func,
                                   void *arg DFL(__NULLPTR),
                                   uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_SYNC_RPC_FNORMAL),
                                   gfp_t rpc_gfp DFL(GFP_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) ATTR_MALLOC WUNUSED NONNULL((1)) struct rpc_entry *
NOTHROW(KCALL task_alloc_synchronous_rpc_nx)(task_rpc_t func,
                                             void *arg DFL(__NULLPTR),
                                             uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_SYNC_RPC_FNORMAL),
                                             gfp_t rpc_gfp DFL(GFP_NORMAL));


/* Free a previously allocated RPC that hasn't been (successfully) delivered.
 * This function should be called as an alternative to  `task_deliver_rpc()',
 * as well as in the event that `task_deliver_rpc()' returned an error code. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_free_rpc)(struct rpc_entry *__restrict rpc);



/* Deliver a given `rpc' to the specified `target' thread.
 * @param: target:   The target thread to which to deliver the RPC.
 * @param: rpc:      The rpc to-be delivered (inherited upon success; s.a. possible return values)
 * @param: priority: Set of `TASK_RPC_FNORMAL | TASK_RPC_FDONTWAKE | TASK_RPC_FHIGHPRIO | TASK_RPC_FWAITFOR'
 * @return: TASK_DELIVER_RPC_KERNTHREAD:  Failed to deliver the RPC: `rpc' is a USER-level RPC, and `target' is a kernel thread.
 * @return: TASK_DELIVER_RPC_TERMINATED:  Failed to deliver the RPC: The given `target' has already terminated.
 * @return: TASK_DELIVER_RPC_SUCCESS:     Successfully delivered RPC
 * @return: TASK_DELIVER_RPC_INTERRUPTED: Successfully delivered RPC (but `target' is the caller, and `rpc' is an interrupting
 *                                        USER-level RPC, and  the caller  should return to  user-space as  soon as  possible)
 *                                        NOTE: Only returned when `task_alloc_user_[s]rpc[_nx]()'  was used to create  `rpc'
 *                                        NOTE: Propagation may be performed by throwing an `E_INTERRUPT_USER_RPC' exception. */
FUNDEF NOBLOCK NONNULL((1, 2)) int
NOTHROW(KCALL task_deliver_rpc)(struct task *__restrict target,
                                /*inherit(on_success)*/ struct rpc_entry *__restrict rpc,
                                uintptr_t priority DFL(TASK_RPC_FNORMAL));
#endif /* __CC__ */

#define TASK_DELIVER_RPC_KERNTHREAD  TASK_SCHEDULE_USER_RPC_KERNTHREAD  /* Only for USER-RPCs: The target thread is a kernel thread that never reaches user-space. */
#define TASK_DELIVER_RPC_TERMINATED  TASK_SCHEDULE_USER_RPC_TERMINATED  /* The target thread has already terminated. */
#define TASK_DELIVER_RPC_SUCCESS     TASK_SCHEDULE_USER_RPC_SUCCESS     /* The RPC was successfully delivered. */
#define TASK_DELIVER_RPC_INTERRUPTED TASK_SCHEDULE_USER_RPC_INTERRUPTED /* Only for USER-RPCs: The calling thread is the same as the target, and `TASK_USER_RPC_FINTR' was set
                                                                         * NOTE: This return value still indicates success! */
#define TASK_DELIVER_RPC_WASOK(x)    TASK_SCHEDULE_USER_RPC_WASOK(x)

DECL_END
#endif /* !CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_RPC_INTERNAL_H */
