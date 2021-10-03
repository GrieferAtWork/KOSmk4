/* HASH CRC-32:0x97d091d3 */
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
#ifndef _KOS_RPC_H
#define _KOS_RPC_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/asm/rpc.h>
#include <kos/asm/rpc-method.h>    /* `RPC_SYSCALL_INFO_METHOD_*' */
#include <kos/bits/syscall-info.h> /* `struct rpc_syscall_info' */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __KERNEL__
typedef struct icpustate rpc_cpustate_t;
#define PRPC_EXEC_CALLBACK_CC __FCALL
#else /* __KERNEL__ */
typedef struct ucpustate rpc_cpustate_t;
#define PRPC_EXEC_CALLBACK_CC __LIBKCALL
#endif /* !__KERNEL__ */


/* The initial value of `rc_context' depends on how the RPC was scheduled:
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
 *       - RPC_REASONCTX_SYSCALL:  Syscall aborted (set `rc_context = RPC_REASONCTX_SYNC' to prevent restart)
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
	__uintptr_t             rc_context; /* [in|out] Execution context (also  determines is  a system  call
	                                     * or  interrupt  should  be restarted)  One  of `RPC_REASONCTX_*'
	                                     * Possible values (and allowed transitions) are documented above. */
	rpc_cpustate_t         *rc_state;   /* [1..1][in|out] The  register state  that got  interrupted.
	                                     * In the case of an interrupted system call that is supposed
	                                     * to be restarted, this describes  the return state of  that
	                                     * system call. */
	struct rpc_syscall_info rc_scinfo;  /* [valid_if(rc_context == RPC_REASONCTX_SYSCALL)] Syscall info. */
};

/* // Additional restrictions/permissions applicable in kernel-space
#ifdef __KERNEL__
ABNORMAL_RETURN_IF(__ctx->rc_context == RPC_REASONCTX_SYSCALL ||
                   __ctx->rc_context == RPC_REASONCTX_INTERRUPT)
NOBLOCK_IF(__ctx->rc_context == RPC_REASONCTX_ASYNC_KERN ||
           __ctx->rc_context == RPC_REASONCTX_SHUTDOWN)
NOTHROW_IF(__ctx->rc_context == RPC_REASONCTX_ASYNC_KERN) // You also ~shouldn't~ throw under `RPC_REASONCTX_SHUTDOWN'
#endif // __KERNEL__
*/
/* Callback prototype for RPC functions registered by `rpc_exec()' */
typedef __ATTR_NONNULL((1)) void
(PRPC_EXEC_CALLBACK_CC *prpc_exec_callback_t)(struct rpc_context *__restrict __ctx, void *__cookie)
		__THROWS(...);

/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread terminate before the  conditions for the RPC  to be served are  ever
 * met. Note that these  conditions depend on the  given `mode'. Note that  on
 * multi-arch  platforms (such as  x86), the register numbers,  as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 *
 * @param: target_tid:      The TID of the targeted thread
 * @param: mode:            One of  `RPC_SYNCMODE_*', optionally or'd  with
 *                          one of `RPC_SYSRESTART_*', optionally or'd with
 *                          one of  `RPC_PRIORITY_*', optionally or'd  with
 *                          one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                          one of `RPC_JOIN_*'
 * @param: program:         The RPC program to execute (sequences of `RPC_OP_*')
 * @param: params:          RPC program parameters (for `RPC_OP_push_param')
 * @param: max_param_count: The max # of `params' used by `program'
 *
 * @return: 0 :                Success
 * @throws: E_SEGFAULT:        Faulty pointers were given
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE:
 *                             The given `mode' is invalid.
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION:
 *                             The RPC program  contains illegal  instructions.
 *                             In this case, modifications made by instructions
 *                             encountered before the illegal one(s) will still
 *                             have  happened, meaning that the target thread's
 *                             state may have become inconsistent.
 * @throws: E_PROCESS_EXITED:  The target thread has already terminated, or
 *                             doesn't exist. Note  though that unless  the
 *                             thread  is  part  of your  own  process, are
 *                             still many reasons  outside of your  control
 *                             for why it  may terminate immediately  after
 *                             the RPC program finished. */
__CDECLARE_OPT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,rpc_schedule,(__pid_t __target_tid, unsigned int __mode, void const *__program, void const *const *__params, size_t __max_param_count),(__target_tid,__mode,__program,__params,__max_param_count))
/* >> rpc_serve(2)
 * Check for  pending RPCs.  This function  is basically  a cancellation  point in  disguise,
 * in  that it literally _is_ a regular, old cancellation point, with the only addition being
 * it doesn't contain any blocking call. You may also know this one as `pthread_testcancel()'
 * Essentially, this function  just calls  the kernel function  `task_serve()', and  forwards
 * that function's return value.
 * @return: 0:  Nothing was handled.
 * @return: -1: [errno=EINTR] RPCs (or posix signals) were handled. */
__CDECLARE_OPT(,int,__NOTHROW_RPC,rpc_serve,(void),())
/* >> rpc_exec(3)
 * Send a RPC to `target_tid' (which must be a thread within the current process).
 * The RPC will modify  the target thread's register  state such that `func'  will
 * be executed before  (upon its  return), execution resumes  within that  thread.
 * How/when exactly the RPC is served depends on the given `mode'.
 * WARNING: Unless special conditions are met, trying to use this function to send
 *          an RPC to another process  (read: different mman), will probably  fail
 *          due  to the address  of `func' mapping to  a different location within
 *          that other process.
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of  `RPC_SYNCMODE_*', optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of  `RPC_PRIORITY_*', optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :                Success
 * @return: -1: [errno=ESRCH]  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
__CDECLARE_OPT(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,rpc_exec,(__pid_t __target_tid, unsigned int __mode, prpc_exec_callback_t __func, void *__cookie),(__target_tid,__mode,__func,__cookie))
/* >> rpc_interrupt(3)
 * Send  a RPC to `target_tid' (which must be a thread within the current process).
 * The RPC won't do anything except causing an in-progress system call to fail with
 * `errno=EINTR' (so-long as that system call isn't marked as [restart(dont)]).
 *
 * This function can be used to send sporadic interrupts to other threads within
 * the  current process, as well as allow  one to stop in-progress, but blocking
 * system calls performed by  those threads. This function  is a no-op when  the
 * given `target_tid == gettid()'.
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of  `RPC_SYNCMODE_*', optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of  `RPC_PRIORITY_*', optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :               Success
 * @return: -1: [errno=ESRCH] The  target thread has already terminated, or
 *                            doesn't exist.  Note though  that unless  the
 *                            thread is part of your own process, there are
 *                            still many  reasons outside  of your  control
 *                            for why  it may  terminate immediately  after
 *                            the RPC program finished. */
__CDECLARE_OPT(,int,__NOTHROW_NCX,rpc_interrupt,(__pid_t __target_tid, unsigned int __mode),(__target_tid,__mode))
/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread terminate before the  conditions for the RPC  to be served are  ever
 * met. Note that these  conditions depend on the  given `mode'. Note that  on
 * multi-arch  platforms (such as  x86), the register numbers,  as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 *
 * @param: target_tid:      The TID of the targeted thread
 * @param: mode:            One of  `RPC_SYNCMODE_*', optionally or'd  with
 *                          one of `RPC_SYSRESTART_*', optionally or'd with
 *                          one of  `RPC_PRIORITY_*', optionally or'd  with
 *                          one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                          one of `RPC_JOIN_*'
 * @param: program:         The RPC program to execute (sequences of `RPC_OP_*')
 * @param: params:          RPC program parameters (for `RPC_OP_push_param')
 * @param: max_param_count: The max # of `params' used by `program'
 *
 * @return: 0 :                Success
 * @throws: E_SEGFAULT:        Faulty pointers were given
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE:
 *                             The given `mode' is invalid.
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION:
 *                             The RPC program  contains illegal  instructions.
 *                             In this case, modifications made by instructions
 *                             encountered before the illegal one(s) will still
 *                             have  happened, meaning that the target thread's
 *                             state may have become inconsistent.
 * @throws: E_PROCESS_EXITED:  The target thread has already terminated, or
 *                             doesn't exist. Note  though that unless  the
 *                             thread  is  part  of your  own  process, are
 *                             still many reasons  outside of your  control
 *                             for why it  may terminate immediately  after
 *                             the RPC program finished. */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((3)),__THROWING,RpcSchedule,(__pid_t __target_tid, unsigned int __mode, void const *__program, void const *const *__params, size_t __max_param_count),(__target_tid,__mode,__program,__params,__max_param_count))
/* >> rpc_exec(3)
 * Send a RPC to `target_tid' (which must be a thread within the current process).
 * The RPC will modify  the target thread's register  state such that `func'  will
 * be executed before  (upon its  return), execution resumes  within that  thread.
 * How/when exactly the RPC is served depends on the given `mode'.
 * WARNING: Unless special conditions are met, trying to use this function to send
 *          an RPC to another process  (read: different mman), will probably  fail
 *          due  to the address  of `func' mapping to  a different location within
 *          that other process.
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of  `RPC_SYNCMODE_*', optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of  `RPC_PRIORITY_*', optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :                Success
 * @return: -1: [errno=ESRCH]  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((3)),__THROWING,RpcExec,(__pid_t __target_tid, unsigned int __mode, prpc_exec_callback_t __func, void *__cookie),(__target_tid,__mode,__func,__cookie))
/* >> rpc_interrupt(3)
 * Send  a RPC to `target_tid' (which must be a thread within the current process).
 * The RPC won't do anything except causing an in-progress system call to fail with
 * `errno=EINTR' (so-long as that system call isn't marked as [restart(dont)]).
 *
 * This function can be used to send sporadic interrupts to other threads within
 * the  current process, as well as allow  one to stop in-progress, but blocking
 * system calls performed by  those threads. This function  is a no-op when  the
 * given `target_tid == gettid()'.
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of  `RPC_SYNCMODE_*', optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of  `RPC_PRIORITY_*', optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :               Success
 * @return: -1: [errno=ESRCH] The  target thread has already terminated, or
 *                            doesn't exist.  Note though  that unless  the
 *                            thread is part of your own process, there are
 *                            still many  reasons outside  of your  control
 *                            for why  it may  terminate immediately  after
 *                            the RPC program finished. */
__CDECLARE_VOID_OPT(,__THROWING,RpcInterrupt,(__pid_t __target_tid, unsigned int __mode),(__target_tid,__mode))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_RPC_H */
