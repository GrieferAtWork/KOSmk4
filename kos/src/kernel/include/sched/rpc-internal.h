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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_RPC_INTERNAL_H
#define GUARD_KERNEL_INCLUDE_SCHED_RPC_INTERNAL_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/sig.h> /* `struct sig' */

#include <hybrid/sequence/list.h>

#include <bits/os/siginfo.h>
#include <kos/bits/exception_data.h>
#include <kos/rpc.h>

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
#define PENDING_USER_RPC_STATUS_ERROR    3 /* Program execution failed. (s.a. `pur_error') */

struct pending_rpc;
struct pending_user_rpc {
	WEAK refcnt_t    pur_refcnt; /* Reference counter. */
	uintptr_t        pur_status; /* RPC status (one of `PENDING_USER_RPC_STATUS_*') */
	struct sig       pur_stchng; /* Signal broadcast when `pur_status' is changed
	                              * by someone  other than  the original  sender. */
	REF struct mman *pur_mman;   /* [1..1][const] The mman within which `pur_prog' resides. */
	union {
		struct {
			USER CHECKED void const   *pur_prog;       /* [1..1][const] Userspace RPC program */
			size_t                     pur_argc;       /* [const] # of program arguments. */
			USER UNCHECKED void const *pur_argv[1024]; /* [?..?][pur_argc][const]  Vector   of   program   arguments.
			                                            * Should be flexible, but GCC sucks and doesn't allow that... */
		};
		struct {
			__except_code_t               e_code; /* Exception code. */
			union exception_data_pointers e_args; /* Exception args. */
		} pur_error; /* [valid_if(PENDING_USER_RPC_STATUS_ERROR)] */
	};
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


/* Header needed for ABI compatibility when using `_RPC_CONTEXT_DONTFREE' */
struct pending_rpc_head {
	SLIST_ENTRY(pending_rpc) prh_link;  /* [0..1][lock(ATOMIC)] Link in the list of pending RPCs */
	uintptr_t                prh_flags; /* [const] RPC flags: RPC_CONTEXT_KERN, ...
	                                     * NOTE: When `_RPC_CONTEXT_INACTIVE' is set, then the RPC is inactive.
	                                     * NOTE: In the case of thread-directed RPCs, some flags are non-[const],
	                                     *       but are instead [lock(PRIVATE(THIS_TASK))]. */
	prpc_exec_callback_t     prh_func;  /* [1..1][const] Function to invoke. */
};

#define OFFSET_PENDING_RPC_LINK  0
#define OFFSET_PENDING_RPC_FLAGS __SIZEOF_POINTER__
struct pending_rpc {
	SLIST_ENTRY(pending_rpc) pr_link;  /* [0..1][lock(ATOMIC)] Link in the list of pending RPCs */
	uintptr_t                pr_flags; /* [const] RPC flags: RPC_CONTEXT_KERN, ...
	                                    * NOTE: When `_RPC_CONTEXT_INACTIVE' is set, then the RPC is inactive.
	                                    * NOTE: In the case of thread-directed RPCs, some flags are non-[const],
	                                    *       but are instead [lock(PRIVATE(THIS_TASK))]. */
	union {
		struct {
			prpc_exec_callback_t k_func;   /* [1..1][const] Function to invoke. */
			void                *k_cookie; /* [?..?][const] Cookie argument for `k_func' */
		}                       pr_kern;   /* [RPC_CONTEXT_KERN] Kernel-mode RPC */
		struct pending_user_rpc pr_user;   /* [!RPC_CONTEXT_KERN && !RPC_CONTEXT_SIGNAL] User-mode RPC */
		siginfo_t               pr_psig;   /* [!RPC_CONTEXT_KERN && RPC_CONTEXT_SIGNAL] Posix signal
		                                    * NOTE: In this case, `pr_flags & RPC_SIGNO_MASK' must encode
		                                    *       the same signal  number as `pr_psig.si_signo'.  Else,
		                                    *       the incorrect signal is used during sigmask checks */
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
#define _pending_rpc_maybe_free(self)   (((self)->pr_flags & _RPC_CONTEXT_DONTFREE) ? (void)0 : pending_rpc_free(self))


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

/* [lock(SET(ATOMIC), CLEAR(ATOMIC && THIS_TASK))]
 * Bitset of pending info-less POSIX signals (1-31). Bit#0 becomes set
 * by the thread itself to indicate `THIS_RPCS_TERMINATED'. Once  this
 * bit is set, all other bits become meaningless.
 *
 * To send one of these signals to a thread, do:
 * >> assert(signo >= 1 && signo <= 31);
 * >> ATOMIC_OR(FORTASK(thread, this_rpcs_sigpend), (uint32_t)1 << signo);
 * >> sig_broadcast(&FORTASK(thread, this_rpcs_sig));
 * >> ATOMIC_OR(thread->t_flags, TASK_FRPC);
 * >> userexcept_sysret_inject_and_marksignal_safe(thread, flags); */
DATDEF ATTR_PERTASK uint32_t this_rpcs_sigpend;

/* [lock(PRIVATE(THIS_TASK))]
 * Used internally: inactive set of pending posix signals. */
DATDEF ATTR_PERTASK uint32_t this_rpcs_sigpend_inactive;

/* A  signal that is broadcast whenever something is added to `this_rpcs'
 * This signal is _only_ used  to implement `signalfd(2)', as you're  not
 * normally supposed to "wait" for signals to arrive; you just always get
 * a sporadic interrupt once they do arrive. */
DATDEF ATTR_PERTASK struct sig this_rpcs_sig;


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
#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL
NOTHROW(FCALL task_rpc_schedule)(struct task *__restrict thread,
                                 /*inherit(on_success)*/ struct pending_rpc_head *__restrict rpc)
		ASMNAME("task_rpc_schedule");
} /* extern "C++" */
#endif /* __cplusplus */

/* Schedule a given signal (which must be `>= 1 && <= 31') for `thread'
 * @return: true:  Success.
 * @return: false: The target thread has already terminated. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL task_sig_schedule)(struct task *__restrict thread, signo_t signo);


/* Same as `task_rpc_schedule()', but schedule the RPC for execution
 * by some arbitrary  thread apart of  the process  `proc->tp_pctl'.
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
NOTHROW(FCALL proc_rpc_schedule)(struct taskpid *__restrict proc,
                                 /*inherit(on_success)*/ struct pending_rpc *__restrict rpc);
#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL
NOTHROW(FCALL proc_rpc_schedule)(struct taskpid *__restrict proc,
                                 /*inherit(on_success)*/ struct pending_rpc_head *__restrict rpc)
		ASMNAME("proc_rpc_schedule");
} /* extern "C++" */
#endif /* __cplusplus */

/* Schedule a given signal (which must be `>= 1 && <= 31') for `proc'
 * @return: true:  Success.
 * @return: false: The target process was marked as having terminated. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL proc_sig_schedule)(struct taskpid *__restrict proc, signo_t signo);


/* Gather the set of posix signal numbers used by pending RPCs
 * of calling thread or process.  These functions are used  to
 * implement the `sigpending(2)' system call.
 *
 * NOTE: These functions don't `sigemptyset(result)' beforehand,
 *       but  will blindly `sigaddset()'  all pending signals to
 *       it. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_rpc_pending_sigset)(/*in|out*/ sigset_t *__restrict result);
FUNDEF NONNULL((1)) void FCALL
proc_rpc_pending_sigset(/*in|out*/ sigset_t *__restrict result)
		THROWS(E_WOULDBLOCK);

/* Check if an RPCs routed via one of `these' signals is pending. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL task_rpc_pending_oneof)(sigset_t const *__restrict these);
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) __BOOL FCALL
proc_rpc_pending_oneof(sigset_t const *__restrict these)
		THROWS(E_WOULDBLOCK);

/* @return: * : One of `PROC_RPC_TRYPENDING_ONEOF_*' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) int
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

/* Same as `proc_rpc_pending_steal_posix_signal()',  but only _try_  to
 * acquire the necessary lock to `task_getprocctl()->pc_sig_more'. When
 * doing so fails,  `PROC_RPC_PENDING_TRYSTEAL_POSIX_SIGNAL_WOULDBLOCK'
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
 * @param: reason:  One of `_RPC_REASONCTX_ASYNC', `_RPC_REASONCTX_SYNC', `_RPC_REASONCTX_SYSCALL' or `_RPC_REASONCTX_SYSINT'
 * @param: sc_info: [valid_if(reason == _RPC_REASONCTX_SYSCALL || reason == _RPC_REASONCTX_SYSINT)]
 *                  The  system call that was active at the  time of the RPC being handled. Note that
 *                  this system call only has to be restarted when `reason == _RPC_REASONCTX_SYSCALL'
 * @return: * :   The updated CPU state.
 * @return: NULL: The RPC was canceled before it could be fully executed.
 * @throw: E_INTERRUPT_USER_RPC: Must serve other RPCs first, then try to serve this one again.
 * @throw: * : RPCs serving failed, simply `decref(&rpc->pr_user)'; message passing is already done. */
FUNDEF WUNUSED NONNULL((1, 2)) rpc_cpustate_t *FCALL
task_userrpc_runprogram(rpc_cpustate_t *__restrict state, struct pending_rpc *__restrict rpc,
                        unsigned int reason, struct rpc_syscall_info const *sc_info)
		THROWS(E_INTERRUPT_USER_RPC, ...);

/* Mark  the given `rpc' as canceled. This function is guarantied to
 * not be called at the same time as `task_userrpc_runprogram()', as
 * it is only used to  implement handling for `!RPC_CONTEXT_KERN  &&
 * !RPC_CONTEXT_SIGNAL' RPCs left-over during thread/process exit. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_userrpc_cancelprogram)(struct pending_rpc *__restrict rpc);



DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_RPC_INTERNAL_H */
