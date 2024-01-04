/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%[default:section(".text.crt{|.dos}.sched.rpc")]

%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#include <kos/asm/rpc.h>
)]%[insert:prefix(
#include <kos/bits/rpc.h>
)]%[insert:prefix(
#include <kos/asm/rpc-method.h>    /* `RPC_SYSCALL_INFO_METHOD_*' */
)]%[insert:prefix(
#include <kos/bits/syscall-info.h> /* `struct rpc_syscall_info' */
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

typedef __rpc_cpustate_t rpc_cpustate_t;

#ifndef PRPC_EXEC_CALLBACK_CC
#ifdef __KERNEL__
#define PRPC_EXEC_CALLBACK_CC __FCALL
#else /* __KERNEL__ */
#define PRPC_EXEC_CALLBACK_CC __LIBKCALL
#endif /* !__KERNEL__ */
#endif /* !PRPC_EXEC_CALLBACK_CC */


/* The initial value of `rc_context' depends on
 * the `mode' with which the RPC was scheduled:
 *
 * #ifdef __KERNEL__
 *
 *   - `RPC_CONTEXT_KERN | RPC_SYNCMODE_F_ALLOW_ASYNC':
 *       - RPC_REASONCTX_ASYNC_KERN: Thread is currently in kernel-space
 *       - RPC_REASONCTX_SYSRET:     Thread is currently in user-space
 *
 *   - `RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER | RPC_SYNCMODE_F_SYSRET':
 *       - RPC_REASONCTX_SYSRET:    Return to userspace
 *       - RPC_REASONCTX_SHUTDOWN:  Thread is about to terminate
 *
 *   - `RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER':
 *       - RPC_REASONCTX_SYSCALL:   Syscall aborted   (set `rc_context = RPC_REASONCTX_SYSRET' to prevent restart)
 *       - RPC_REASONCTX_INTERRUPT: Interrupt aborted (set `rc_context = RPC_REASONCTX_SYSRET' to prevent restart)
 *       - RPC_REASONCTX_SYSRET:    Return to userspace
 *       - RPC_REASONCTX_SHUTDOWN:  Thread is about to terminate
 *
 *   - `RPC_CONTEXT_KERN':
 *       - RPC_REASONCTX_SYNC:      Direct execution from within `task_serve()'
 *       - RPC_REASONCTX_SHUTDOWN:  Thread is about to terminate
 *       - RPC_REASONCTX_SYSCALL:   Syscall aborted     (treat like `RPC_REASONCTX_SYNC')
 *       - RPC_REASONCTX_INTERRUPT: Interrupt aborted   (treat like `RPC_REASONCTX_SYNC')
 *       - RPC_REASONCTX_SYSRET:    Return to userspace (treat like `RPC_REASONCTX_SYNC')
 *
 * #else // __KERNEL__
 *
 *   - `0':
 *       - RPC_REASONCTX_SYSCALL:  Syscall aborted (set `rc_context = RPC_REASONCTX_SYSINT' to prevent restart)
 *       - RPC_REASONCTX_SYSINT:   Syscall returns with -EINTR / E_INTERRUPT and will not be restarted.
 *       - RPC_REASONCTX_SYNC:     Synchronous interrupt call was aborted
 *
 *   - `RPC_SYNCMODE_F_ALLOW_ASYNC':
 *       - RPC_REASONCTX_ASYNC:    Async userspace
 *       - RPC_REASONCTX_SYSCALL:  Synchronous system call was aborted (but will be restarted)
 *       - RPC_REASONCTX_SYNC:     Synchronous interrupt call was aborted (treat like `RPC_REASONCTX_SYSCALL')
 *
 * #endif // !__KERNEL__
 *
 */

struct rpc_context {
	__uintptr_t             rc_context; /* [in|out] Execution context (also  determines if  a system  call
	                                     * or  interrupt  should  be restarted)  One  of `RPC_REASONCTX_*'
	                                     * Possible values (and allowed transitions) are documented above. */
	rpc_cpustate_t         *rc_state;   /* [1..1][in|out] The  register state  that got  interrupted.
	                                     * In the case of an interrupted system call that is supposed
	                                     * to be restarted, this describes  the return state of  that
	                                     * system call. */
	struct rpc_syscall_info rc_scinfo;  /* #ifdef __KERNEL__
	                                     * [valid_if(rc_context == RPC_REASONCTX_SYSCALL)]
	                                     * #else // __KERNEL__
	                                     * [valid_if(rc_context == RPC_REASONCTX_SYSCALL ||
	                                     *           rc_context == RPC_REASONCTX_SYSINT)]
	                                     * #endif // !__KERNEL__
	                                     * Syscall info. */
};

/* Callback prototype for RPC functions registered by `rpc_exec()' */
#ifndef __prpc_exec_callback_t_defined
#define __prpc_exec_callback_t_defined
/* // Additional restrictions/permissions applicable in kernel-space
#ifdef __KERNEL__
ABNORMAL_RETURN_IF(__ctx->rc_context == RPC_REASONCTX_SYSCALL ||
                   __ctx->rc_context == RPC_REASONCTX_INTERRUPT)
NOBLOCK_IF(__ctx->rc_context == RPC_REASONCTX_ASYNC_KERN ||
           __ctx->rc_context == RPC_REASONCTX_SHUTDOWN)
NOTHROW_IF(__ctx->rc_context == RPC_REASONCTX_ASYNC_KERN) // You also ~shouldn't~ throw under `RPC_REASONCTX_SHUTDOWN'
#endif // __KERNEL__
*/
typedef __ATTR_NONNULL_T((1)) void
(PRPC_EXEC_CALLBACK_CC *prpc_exec_callback_t)(struct rpc_context *__restrict __ctx, void *__cookie)
		__THROWS(...);
#endif /* !__prpc_exec_callback_t_defined */

}

%[define_replacement(prpc_exec_callback_t = prpc_exec_callback_t)]
%[define_type_class(prpc_exec_callback_t = "TP")]



@@>> rpc_schedule(2)
@@Schedule an RPC program to-be executed by some other thread. This  function
@@cannot guaranty that  the RPC  program is  always executed,  as the  target
@@thread may terminate  before the conditions  for the RPC  to be served  are
@@ever met. Note that these conditions depend on the given `mode'. Note  that
@@on multi-arch platforms (such as x86), the register numbers, as well as the
@@address size used by `program' depend on the execution mode of `target_tid'
@@
@@NOTE: This function is a cancellation point when `RPC_JOIN_WAITFOR' is given!
@@
@@@param: target_tid:      The TID of the targeted thread
@@@param: mode:            One of `RPC_SYNCMODE_*',  optionally or'd  with
@@                         one of `RPC_SYSRESTART_*', optionally or'd with
@@                         one of `RPC_PRIORITY_*',  optionally or'd  with
@@                         one of  `RPC_DOMAIN_*',  optionally  or'd  with
@@                         one of `RPC_JOIN_*'
@@@param: program:         The RPC program to execute (sequences of `RPC_OP_*')
@@@param: params:          RPC program parameters (for `RPC_OP_push_param')
@@@param: max_param_count: The max # of `params' used by `program'
@@
@@@return: 0 :                Success
@@@throws: E_SEGFAULT:        Faulty pointers were given
@@@throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE:
@@                            The given `mode' is invalid.
@@@throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION:
@@                            The RPC program contains illegal instructions.
@@@throws: E_PROCESS_EXITED:  The  target thread has already terminated, or
@@                            doesn't exist.  Note though  that unless  the
@@                            thread is part of your own process, there are
@@                            still many  reasons outside  of your  control
@@                            for why  it may  terminate immediately  after
@@                            the RPC program finished.
[[cp, decl_include("<bits/types.h>")]]
int rpc_schedule($pid_t target_tid, unsigned int mode,
                 [[in]] void const *program,
                 [[in(max_param_count)]] void const *const *params,
                 $size_t max_param_count);


@@>> rpc_serve(2)
@@Check for  pending RPCs.  This function  is basically  a cancellation  point in  disguise,
@@in  that it literally _is_ a regular, old cancellation point, with the only addition being
@@it doesn't contain any blocking call. You may also know this one as `pthread_testcancel()'
@@Essentially, this function  just calls  the kernel function  `task_serve()', and  forwards
@@that function's return value.
@@@return: 0:  Nothing was handled.
@@@return: -1: [errno=EINTR] RPCs (or posix signals) were handled.
[[cp]] int rpc_serve(void);


@@>> rpc_exec(3)
@@Send an RPC to `target_tid' (which must be a thread within the  current
@@process). The RPC will modify  the target thread's register state  such
@@that `func' will be executed before (upon its return) execution resumes
@@within that thread.
@@How/when exactly the RPC is served depends on the given `mode'.
@@WARNING: Unless special conditions are met, trying to use this function to send
@@         an RPC to another process  (read: different mman), will probably  fail
@@         due  to the address  of `func' mapping to  a different location within
@@         that other process.
@@
@@@param: target_tid: The TID of the targeted thread
@@@param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
@@                    one of `RPC_SYSRESTART_*', optionally or'd with
@@                    one of `RPC_PRIORITY_*',  optionally or'd  with
@@                    one of  `RPC_DOMAIN_*',  optionally  or'd  with
@@                    one of `RPC_JOIN_*'
@@@return: 0 :                Success
@@@return: -1: [errno=ESRCH]  The  target thread has already terminated, or
@@                            doesn't exist.  Note though  that unless  the
@@                            thread is part of your own process, there are
@@                            still many  reasons outside  of your  control
@@                            for why  it may  terminate immediately  after
@@                            the RPC program finished.
[[cp, decl_include("<bits/types.h>")]]
int rpc_exec($pid_t target_tid, unsigned int mode,
             [[nonnull]] prpc_exec_callback_t func, void *cookie);


@@>> rpc_interrupt(3)
@@Send an RPC to `target_tid' (which must be a thread within the current
@@process).  The RPC won't do anything except causing an in-progress (or
@@upcoming) system  call to  fail with  `errno=EINTR' (so-long  as  that
@@system call isn't marked as [restart(dont)]).
@@
@@This function can be used to send sporadic interrupts to other threads within
@@the  current process, as well as allow  one to stop in-progress, but blocking
@@system calls performed by  those threads. This function  is a no-op when  the
@@given `target_tid == gettid()'.
@@
@@NOTE: This function is a cancellation point when `RPC_JOIN_WAITFOR' is given!
@@
@@@param: target_tid: The TID of the targeted thread
@@@param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
@@                    one of `RPC_SYSRESTART_*', optionally or'd with
@@                    one of `RPC_PRIORITY_*',  optionally or'd  with
@@                    one of  `RPC_DOMAIN_*',  optionally  or'd  with
@@                    one of `RPC_JOIN_*'
@@@return: 0 :               Success
@@@return: -1: [errno=ESRCH] The  target thread has already terminated, or
@@                           doesn't exist.  Note though  that unless  the
@@                           thread is part of your own process, there are
@@                           still many  reasons outside  of your  control
@@                           for why  it may  terminate immediately  after
@@                           the RPC program finished.
[[cp, decl_include("<bits/types.h>")]]
int rpc_interrupt($pid_t target_tid, unsigned int mode);





/************************************************************************/
/* Exception-enabled version of the above API                           */
/************************************************************************/

[[cp, throws, doc_alias("rpc_schedule"), decl_include("<bits/types.h>")]]
void RpcSchedule($pid_t target_tid, unsigned int mode,
                 [[in]] void const *program,
                 [[in(max_param_count)]] void const *const *params,
                 $size_t max_param_count);

[[cp, throws, doc_alias("rpc_exec"), decl_include("<bits/types.h>")]]
void RpcExec($pid_t target_tid, unsigned int mode,
             [[nonnull]] prpc_exec_callback_t func, void *cookie);

[[cp, throws, doc_alias("rpc_interrupt"), decl_include("<bits/types.h>")]]
void RpcInterrupt($pid_t target_tid, unsigned int mode);


%{

__SYSDECL_END
#endif /* __CC__ */

}
