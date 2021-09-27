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

#ifndef __DEEMON__
#include <__crt.h>
#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>
#endif /* !__DEEMON__ */

/* RPC (and posix signal) handling contexts:
 *
 *  - Target thread is in user-space at time of delivery:
 *    - RPC_SYNCMODE_SYNC:  Schedule the RPC as pending until the next call to `task_serve()'
 *    - RPC_SYNCMODE_ASYNC: The RPC is executed immediately.
 *
 *  - Target thread is in kernel-space at time of delivery:
 *    - * : Schedule the RPC as pending until the next call to `task_serve()'
 *
 *  - Target thread makes a call to kernel function `task_serve()':
 *    - Redirect the thread's IRET tail to inject a function
 *      to-be  executed  before  returning  to   user-space.
 *    - Within this function, handle all pending RPCs and posix signals:
 *      >> // Resume execution in user-space
 *      >> #define HANDLE_ACTION_RESUME 0
 *      >> // Restart the interrupt and call `handle_user_rpc'
 *      >> // again before returning to user-space, then using
 *      >> // `RPC_REASONCTX_SYSRET' as the reason for handling.
 *      >> #define HANDLE_ACTION_RESTART_INTERRUPT_AND_SYSRET 1
 *      >>
 *      >> // NOTE: Exceptions thrown by this function are propagated normally,
 *      >> //       but note that the E_INTERRUPT_USER_RPC error that brought
 *      >> //       us here will have already been consumed when this function
 *      >> //       is called!
 *      >> struct icpustate *
 *      >> handle_user_rpc(struct icpustate *state,
 *      >>                 unsigned int reason,
 *      >>                 struct rpc_syscall_info const *sc_info,
 *      >>                 unsigned int *return_mode) {
 *      >>     bool rpc_handled;
 *      >>     bool must_reactivate;
 *      >>     bool user_rpc_handled;
 *      >>     assert(reason == RPC_REASONCTX_SYSRET ||
 *      >>            reason == RPC_REASONCTX_INTERRUPT ||
 *      >>            reason == RPC_REASONCTX_ASYNC);
 *      >>     assert(reason == RPC_REASONCTX_INTERRUPT || sc_info == NULL);
 *      >>     assert(error_code() == ERROR_CODEOF(E_OK));
 *      >>
 *      >>     // Kernel-private RPCs executed before
 *      >>     // return-to-user are also handled here.
 *      >>
 *      >>     rpc_handled = false;
 *      >>     FOREACH(RPC: <pending_rpcs>) {
 *      >>         if (RPC.flags & RPC_CONTEXT_KERN) {
 *      >>             auto func = RPC.func;
 *      >>             CONSUME_RPC(RPC);
 *      >>             // TODO: This function must somehow be able to set `user_rpc_handled = true'!
 *      >>             state = (*func)(state, reason, sc_info);
 *      >>             rpc_handled = true;
 *      >>         }
 *      >>     }
 *      >>
 *      >>     must_reactivate  = false;
 *      >>     user_rpc_handled = false;
 *      >>     if (!IS_MASKED(SIGRPC)) {
 *      >>         FOREACH(RPC: <pending_rpcs>) {
 *      >>             unsigned int user_rpc_reason = RPC_REASONCTX_ASYNC;
 *      >>             bool         user_rpc_restart_syscall = false;
 *      >>             if (reason == RPC_REASONCTX_SYSRET) {
 *      >>                 if (RPC.flags & (RPC_SYNCMODE_F_REQUIRE_SC | RPC_SYNCMODE_F_REQUIRE_CP))
 *      >>                     RPC.active = true; // Re-enable for the next call
 *      >>                 if (!(RPC.flags & RPC_SYNCMODE_F_ALLOW_ASYNC))
 *      >>                     continue; // RPC may not be delivered to asynchronous user-space.
 *      >>             } else {
 *      >>                 if ((RPC.flags & RPC_SYNCMODE_F_REQUIRE_SC) && !sc_info) {
 *      >>                     if (reason == RPC_REASONCTX_INTERRUPT) {
 *      >>                         RPC.active = false; // RPC requires a system call
 *      >>                         must_reactivate = true;
 *      >>                     }
 *      >>                     continue;
 *      >>                 }
 *      >>                 if (sc_info) {
 *      >>                     unsigned int syscall_restart_mode;
 *      >>                     assert(reason == RPC_REASONCTX_INTERRUPT);
 *      >>                     if ((RPC.flags & RPC_SYNCMODE_F_REQUIRE_CP) && !kernel_syscall_iscp(sc_info->rsi_sysno)) {
 *      >>                         assert(reason == RPC_REASONCTX_INTERRUPT);
 *      >>                         RPC.active = false; // The RPC requires a cancellation point.
 *      >>                         must_reactivate = true;
 *      >>                         continue;
 *      >>                     }
 *      >>                     user_rpc_reason      = RPC_REASONCTX_SYNC;
 *      >>                     syscall_restart_mode = kernel_syscall_restartmode(sc_info->rsi_sysno);
 *      >>                     if (syscall_restart_mode == SYSCALL_RESTART_MODE_MUST)
 *      >>                         user_rpc_restart_syscall = true;
 *      >>                     else {
 *      >>                         if ((syscall_restart_mode == SYSCALL_RESTART_MODE_AUTO) && (RPC.flags & RPC_SYSRESTART_F_AUTO))
 *      >>                             user_rpc_restart_syscall = true;
 *      >>                         if ((syscall_restart_mode == SYSCALL_RESTART_MODE_DONT) && (RPC.flags & RPC_SYSRESTART_F_DONT))
 *      >>                             user_rpc_restart_syscall = true;
 *      >>                     }
 *      >>                 } else if (reason == RPC_REASONCTX_ASYNC) {
 *      >>                     if (!(RPC.flags & RPC_SYNCMODE_F_ALLOW_ASYNC)) {
 *      >>                         RPC.active = false; // RPC may not be delivered to asynchronous user-space.
 *      >>                         must_reactivate = true;
 *      >>                         continue;
 *      >>                     }
 *      >>                 } else {
 *      >>                     assert(reason == RPC_REASONCTX_INTERRUPT);
 *      >>                     user_rpc_reason = RPC_REASONCTX_SYNC;
 *      >>                 }
 *      >>             }
 *      >>
 *      >>             // Execute the program associated with `RPC'
 *      >>             if (user_rpc_handled) {
 *      >>                 // Only the first RPC program executed is able to potentially
 *      >>                 // restart a system call. If more programs are executed, then
 *      >>                 // those will simply return the context pushed by the first
 *      >>                 // program.
 *      >>                 state = EXECUTE_RPC_PROGRAM(RPC, state, user_rpc_reason, false, NULL);
 *      >>             } else {
 *      >>                 // NOTE: `user_rpc_restart_syscall' is set to `true' if the
 *      >>                 //       system call described by `sc_info' should be restarted
 *      >>                 //       once the sub-routine pushed by the RPC program returns.
 *      >>                 // NOTE: `user_rpc_reason' is one of `RPC_REASONCTX_ASYNC', `RPC_REASONCTX_SYNC'
 *      >>                 state = EXECUTE_RPC_PROGRAM(RPC, state, user_rpc_reason,
 *      >>                                             user_rpc_restart_syscall, sc_info);
 *      >>             }
 *      >>             user_rpc_handled = true;
 *      >>             rpc_handled      = true;
 *      >>             CONSUME_RPC(RPC);
 *      >>             // RPC programs are able to mask signals. Not just because of
 *      >>             // userprocmask and the fact that programs are able to write
 *      >>             // into user-space memory, but also because
 *      >>             if (IS_MASKED(SIGRPC))
 *      >>                 break;
 *      >>         }
 *      >>     }
 *      >>
 *      >>     // POSIX signals are also handled here, and are always handled like:
 *      >>     //  - `RPC_SYNCMODE_ASYNC | RPC_SYSRESTART_NORMAL'  (without `SA_RESTART')
 *      >>     //  - `RPC_SYNCMODE_ASYNC | RPC_SYSRESTART_MOST'    (with `SA_RESTART')
 *      >>     // Also note that when `user_rpc_handled == true', posix signals are
 *      >>     // handled with `reason = RPC_REASONCTX_ASYNC, sc_info = NULL'.
 *      >>
 *      >>     *return_mode = HANDLE_ACTION_RESUME;
 *      >>     if (rpc_handled) {
 *      >>         // If any RPCs were handled, then we must make sure that all RPCs
 *      >>         // which may have gotten disabled are once again re-enabled. Also
 *      >>         // there's no need to restart the current interrupt in this case!
 *      >>         if (must_reactivate) {
 *      >>             FOREACH(RPC: <pending_rpcs>) {
 *      >>                 if (!RPC.active)
 *      >>                     RPC.active = true;
 *      >>             }
 *      >>         }
 *      >>     } else if (must_reactivate) {
 *      >>         // If any of the RPCs got deactivated, then we must restart the
 *      >>         // interrupt with problematic RPCs disabled. then, once the
 *      >>         // interrupt completes, re-enable the RPCs so they're handled
 *      >>         // the next time the current thread calls `task_serve()'
 *      >>         assert(reason == RPC_REASONCTX_INTERRUPT);
 *      >>         *return_mode = HANDLE_ACTION_RESTART_INTERRUPT_AND_SYSRET;
 *      >>     }
 *      >>     return state;
 *      >> }
 *      NOTE: The `RPC.active' field only affects which RPCs cause `task_serve()' to
 *            throw an `E_INTERRUPT_USER_RPC' exception. The field has no effects on
 *            which  RPCs are enumerated by the `FOREACH' above, which always simply
 *            enumerates all of them.
 *
 *  - The implementation of `task_serve()' looks like this:
 *      >> bool task_serve(void) {
 *      >>     bool result = false;
 *      >>     FOREACH(RPC: <pending_rpcs>) {
 *      >>         if (RPC.flags & RPC_CONTEXT_KERN) {
 *      >>             PREEMPTION_ENABLE();
 *      >>             auto func = RPC.func;
 *      >>             CONSUME_RPC(RPC);
 *      >>             struct icpustate *state = CURRENT_STATE();
 *      >>             state = (*func)(state, reason, sc_info);
 *      >>             SET_CURRENT_STATE(state);
 *      >>             result = true;
 *      >>         } else {
 *      >>             if (RPC.active && !IS_MASKED(SIGRPC)) {
 *      >>                 PREEMPTION_ENABLE();
 *      >>                 THROW(E_INTERRUPT_USER_RPC);
 *      >>             }
 *      >>         }
 *      >>     }
 *      >>     return result;
 *      >> }
 *
 */


/* RPC service context codes */
#define RPC_REASONCTX_ASYNC      0x0000 /* Asynchronous execution in user-space. */
#ifdef __KERNEL__
#define RPC_REASONCTX_SYNC       0x0001 /* RPC is being handled from within `task_serve()' */
#define RPC_REASONCTX_SYSRET     0x0002 /* Return from interrupt. Used to reset `RPC_SYNCMODE_F_REQUIRE_SC' and `RPC_SYNCMODE_F_REQUIRE_CP' RPCs. */
#define RPC_REASONCTX_INTERRUPT  0x0003 /* About  to return to user-space after `task_serve()' found
                                         * some active RPCs that required  the stack to be  unwound.
                                         * The interrupt may be something like  #PF, or it may be  a
                                         * system call. In the case  of a system call, `sc_info'  is
                                         * non-NULL. In either case, the interrupt can be restarted. */
#define RPC_REASONCTX_ASYNC_KERN 0x0004 /* Kernel-space was interrupted asynchronously. (in this case,
                                         * preemption is unconditionally  disabled and  should not  be
                                         * enabled by the RPC callback) */
#define RPC_REASONCTX_SHUTDOWN   0x0005 /* RPC is invoked because the thread is exiting. */
#else /* __KERNEL__ */
#define RPC_REASONCTX_SYNC       0x0001 /* A  blocking operation was interrupted. The operation
                                         * may or may not be restarted, depending on additional
                                         * data which was pushed. */
#endif /* !__KERNEL__ */



#ifdef __KERNEL__
/************************************************************************/
/* RPC context flags */
#define RPC_CONTEXT_USER 0x0000 /* User RPC */

/* FLAG: Kernel  RPC. This flag can only be set  by the kernel itself (it is not
 *       accepted by the RPC enqueue system calls, which will indicate that this
 *       flag  is invalid). When set, it changes  the meaning of other RPC flags
 *       and operational method (instead of  needing an RPC program, a  function
 *       pointer is accepted that will be executed instead of the RPC  program):
 *
 *  - RPC_SYNCMODE_F_ALLOW_ASYNC:
 *       The  RPC is delivered  immediately and completely  bypasses the RPC queue.
 *       Instead, the RPC function is pushed onto the target thread's kernel stack,
 *       where  it will be  executed the next time  the thread gets  a share of its
 *       quantum.  If the  target thread  was sleeping  (s.a. `task_sleep()'), then
 *       sleep is interrupted by means of  a sporadic interrupt. The reason  passed
 *       to the RPC function is  always `RPC_REASONCTX_ASYNC_KERN', and are  always
 *       executed  with preemption disabled.  (Note that all  other RPCs are always
 *       executed with preemption enabled)
 *
 *       If this flag is not set, 1 of 2 things can happen:
 *         - If the thread is currently in user-space, inject a piece of code onto
 *           the kernel stack that immediately invokes the given function with the
 *           reason code `RPC_REASONCTX_SYNC'
 *         - Otherwise,  the RPC  is scheduled for  execution the next  time the thread
 *           calls `task_serve()' or as soon as  the thread returns to user-space.  The
 *           later only  happens when  `TASK_FKERNTHREAD' isn't  set. If  in this  case
 *           the target thread also happens  to be sleeping, it  is woken using a  call
 *           to  `task_wake()'. Note that  here it is assumed  that the introduction of
 *           a sporadic interrupt will either cause the thread to return to  user-space
 *           (at which  point  the RPC  will  be  handled), or  to  re-poll  waited-for
 *           conditions and eventually call `task_serve()', followed by `task_sleep()',
 *           in which case the RPC is also handled.
 *       The complete set of reasons when `RPC_SYNCMODE_F_ALLOW_ASYNC' isn't set is:
 *        - RPC_REASONCTX_ASYNC      (Return to user-space location)
 *        - RPC_REASONCTX_SYNC       (Called from `task_serve()')
 *        - RPC_REASONCTX_SYSRET     (Interrupt-to-userspace or system call was unwound)
 *        - RPC_REASONCTX_INTERRUPT  (Interrupt-to-userspace or system call was unwound)
 *        - RPC_REASONCTX_SHUTDOWN   (Thread is exiting)
 *
 *
 *  - RPC_SYNCMODE_F_USER:
 *  - RPC_PRIORITY_F_HIGH:
 *       This flag is accepted and operates as documented below
 *
 *  - RPC_SYNCMODE_F_REQUIRE_SC:
 *       This flag is NOT allowed (but note that `RPC_SYNCMODE_F_USER' is, which
 *       shares its numerical value with this flag)
 *
 *  - RPC_SYNCMODE_F_REQUIRE_CP:
 *  - RPC_SYSRESTART_F_AUTO:
 *  - RPC_SYSRESTART_F_DONT:
 *       This flag is NOT allowed (use of it results in kernel panic)
 */
#define RPC_CONTEXT_KERN     0x8000

/* Flag for use with `RPC_CONTEXT_KERN': the associated function will never
 * throw an exception and is therefor safe to invoke from `task_serve_nx()' */
#define RPC_CONTEXT_NOEXCEPT 0x4000
#endif /* __KERNEL__ */



/************************************************************************/
/* RPC synchronization flags */
#define RPC_SYNCMODE_F_ALLOW_ASYNC 0x0001 /* FLAG: Allow delivery to threads currently in user-space. */
#define RPC_SYNCMODE_F_REQUIRE_SC  0x0002 /* FLAG: Require that the interrupt is the result of a system call being made. */
#define RPC_SYNCMODE_F_REQUIRE_CP  0x0004 /* FLAG: When interrupting a system call, only handle if the system call is a cancellation point. */
#ifdef __KERNEL__
#define RPC_SYNCMODE_F_USER 0x0002 /* For use with `RPC_CONTEXT_KERN': Have `task_serve()' handle the RPC
                                    * as though the `RPC_CONTEXT_KERN' wasn't set. As a consequence, RPCs
                                    * with this flag will only ever be invoked with reasons:
                                    *   - RPC_REASONCTX_ASYNC      (Return to user-space location)
                                    *   - RPC_REASONCTX_SYSRET     (Interrupt-to-userspace or system call was unwound)
                                    *   - RPC_REASONCTX_INTERRUPT  (Interrupt-to-userspace or system call was unwound)
                                    *   - RPC_REASONCTX_SHUTDOWN   (Thread is exiting) */
#endif /* __KERNEL__ */


/* RPC synchronization options */

/* RPC may only be executed when the target thread is making
 * a system call that is  a cancellation point, after  which
 * that call will be interrupted, the RPC will be  executed,
 * and the system call (may) be restarted. */
#define RPC_SYNCMODE_SYNC  0x0000

/* RPC  may be executed at any point while the target thread
 * is running in user-space, so-long as SIGRPC isn't masked.
 * While the thread is in kernel-space, behavior is the same
 * as for `RPC_SYNCMODE_SYNC'. As such, this option can also
 * be seen as a flag "ALLOW_DELIVERLY_WHILE_IN_USERSPACE" */
#define RPC_SYNCMODE_ASYNC RPC_SYNCMODE_F_ALLOW_ASYNC

/* RPC is only handled when  interrupting a system call  that
 * has been marked  as a cancellation  point. Otherwise,  the
 * RPC will be marked as inactive until the end of the system
 * call,  such that  it's next  chance at  being handled only
 * comes about the next time a (different) system call  makes
 * a call to `task_serve()' */
#define RPC_SYNCMODE_CP (RPC_SYNCMODE_F_REQUIRE_SC | RPC_SYNCMODE_F_REQUIRE_CP)
/************************************************************************/




/************************************************************************/
/* RPC system call restart flags */
#define RPC_SYSRESTART_F_AUTO 0x0010 /* [posix: SA_RESTART] Also restart `SYSCALL_RESTART_MODE_AUTO' */
#define RPC_SYSRESTART_F_DONT 0x0020 /* [posix:          -] Also restart `SYSCALL_RESTART_MODE_DONT' */

/* RPC system call  restart options.  These only apply  to RPCs  delivered
 * while the target thread is in kernel-space and executing a system  call
 * marked as [cp] and something other than [restart(must)], and the system
 * call made a call to `task_serve()' internally. */
#define RPC_SYSRESTART_NORMAL 0x0000                                          /* [posix:!SA_RESTART] SYSCALL_RESTART_MODE_MUST */
#define RPC_SYSRESTART_MOST   RPC_SYSRESTART_F_AUTO                           /* [posix: SA_RESTART] SYSCALL_RESTART_MODE_MUST+SYSCALL_RESTART_MODE_AUTO */
#define RPC_SYSRESTART_ALL    (RPC_SYSRESTART_F_AUTO | RPC_SYSRESTART_F_DONT) /* [posix:          -] SYSCALL_RESTART_MODE_MUST+SYSCALL_RESTART_MODE_AUTO+SYSCALL_RESTART_MODE_DONT */
/************************************************************************/




/************************************************************************/
/* RPC priority flags */
#define RPC_PRIORITY_F_HIGH 0x0040 /* Try to gift the target thread the remainder
                                    * of  the  calling thread's  current quantum. */

/* RPC priority options */
#define RPC_PRIORITY_NORMAL 0x0000              /* Normal priority */
#define RPC_PRIORITY_HIGH   RPC_PRIORITY_F_HIGH /* High priority (try to  gift the target thread  the
                                                 * remainder of the calling thread's current quantum) */
/************************************************************************/






/************************************************************************/
/* RPC system call information                                          */
/************************************************************************/

/* Flags for `struct rpc_syscall_info::rsi_flags' */
#define RPC_SYSCALL_INFO_FNORMAL         0x0000 /* Normal system call flags. */
#define RPC_SYSCALL_INFO_FEXCEPT         0x8000 /* Exceptions were enabled for this system call. */
#define RPC_SYSCALL_INFO_FMETHOD         0x00ff /* Mask for the arch-specific system call invocation method. (One of `RPC_SYSCALL_INFO_METHOD_*') */
#define RPC_SYSCALL_INFO_FREGVALID(i)    (0x0100 << (i)) /* Mask for checking if some given register `i' is valid */
#define RPC_SYSCALL_INFO_FREGVALID_SHIFT 8
#define RPC_SYSCALL_INFO_FREGVALID_MASK  0x7f00
#ifndef __DEEMON__
#include <kos/asm/rpc-method.h>    /* `RPC_SYSCALL_INFO_METHOD_*' */
#include <kos/bits/syscall-info.h> /* `struct rpc_syscall_info' */
#endif /* !__DEEMON__ */





/************************************************************************/
/* RPC program opcodes                                                  */
/************************************************************************/

/* RPC  programs are interpreted using an expression stack similar to that
 * of  CFI programs. The  parallels between this bytecode  and that of CFI
 * should be even more blatantly obvious once you realize that many of the
 * below opcodes share numerical values with DW_OP_* codes with similar or
 * even identical functionality.
 *
 * NOTES:
 *  - Register indices are arch-dependent and the same as those used by CFI:
 *      i386:   One of `CFI_386_UNWIND_REGISTER_*'    (from <libunwind/cfi/i386.h>)
 *      x86_64: One of `CFI_X86_64_UNWIND_REGISTER_*' (from <libunwind/cfi/x86_64.h>)
 *  - RPC  program execution starts with the first instruction, at which point
 *    the stack was set-up to contain a single element equal to what is pushed
 *    by `RPC_OP_push_dorestart'.
 *  - Every RPC program _must_ include checks regarding a system call needing  to
 *    be restarted, or never return to the interrupted location at all. For  this
 *    purpose, the stack starts out with containing information about the need to
 *    restart a system call. When a  system call has been interrupted  restarted,
 *    then accessible registers  are indicative of  where the interrupted  system
 *    call would have returned to, and the RPC program should modify the  program
 *    counter  to  point to  a custom  landing pad  capable of  saving registers,
 *    repeating the system  call, restoring registers,  and finally returning  to
 *    where the system call would have originally returned to.
 *
 *  - PUSH_ONTO_USER_STACK(value) works as:
 *    >> int spreg  = CFI_UNWIND_REGISTER_SP(sizeof(void *));
 *    >> void **sp = GET_REGISTER(spreg);
 *    >> #ifdef __ARCH_STACK_GROWS_DOWNWARDS
 *    >> --sp;
 *    >> #endif // __ARCH_STACK_GROWS_DOWNWARDS
 *    >> validate_writeable(sp, sizeof(*sp));
 *    >> *sp = (void *)value;
 *    >> #ifndef !__ARCH_STACK_GROWS_DOWNWARDS
 *    >> ++sp;
 *    >> #endif // !__ARCH_STACK_GROWS_DOWNWARDS
 *    >> SET_REGISTER(spreg, sp);
 *    iow: `RPC_OP_sppush_pop' is identical to:
 *    >> {
 *    >>     RPC_OP_pushreg0 + CFI_UNWIND_REGISTER_SP(sizeof(void *)),
 *    >> #ifdef __ARCH_STACK_GROWS_DOWNWARDS
 *    >>     RPC_OP_const1u, sizeof(void *), RPC_OP_minus,
 *    >> #endif // __ARCH_STACK_GROWS_DOWNWARDS
 *    >>     RPC_OP_dup, RPC_OP_rot, RPC_OP_swap, RPC_OP_write,
 *    >> #ifndef __ARCH_STACK_GROWS_DOWNWARDS
 *    >>     RPC_OP_const1u, sizeof(void *), RPC_OP_plus,
 *    >> #endif // !__ARCH_STACK_GROWS_DOWNWARDS
 *    >>     RPC_OP_popreg0 + CFI_UNWIND_REGISTER_SP(sizeof(void *)),
 *    >> }
 */

/*========================================*/
/*      RPC_OP_               0x00  * ... */
/*      RPC_OP_               0x01  * ... */
/*      RPC_OP_               0x02  * ... */
#define RPC_OP_sppush_const   0x03 /* [+*] PUSH_ONTO_USER_STACK(*(uintptr_t const *)pc); */
/*      RPC_OP_               0x04  * ... */
#define RPC_OP_sppush_pop     0x05 /* [+0] PUSH_ONTO_USER_STACK(POP()); */
#define RPC_OP_deref          0x06 /* [+0] TOP = *(uintptr_t *)TOP; */
#define RPC_OP_write          0x07 /* [+0] addr = POP(); value = POP(); *(uintptr_t *)addr = value; */
#define RPC_OP_const1u        0x08 /* [+1] PUSH(*(u8 const *)pc); */
#define RPC_OP_const1s        0x09 /* [+1] PUSH(*(s8 const *)pc); */
#define RPC_OP_const2u        0x0a /* [+2] PUSH(*(u16 const *)pc); */
#define RPC_OP_const2s        0x0b /* [+2] PUSH(*(s16 const *)pc); */
#define RPC_OP_const4u        0x0c /* [+4] PUSH(*(u32 const *)pc); */
#define RPC_OP_const4s        0x0d /* [+4] PUSH(*(s32 const *)pc); */
#define RPC_OP_const8u        0x0e /* [+8] PUSH(*(u64 const *)pc); */
#define RPC_OP_const8s        0x0f /* [+8] PUSH(*(s64 const *)pc); */
#define RPC_OP_popregx        0x10 /* [+*] CFI_REGISTER(dwarf_decode_uleb128(&pc)) = POP(); */
/*      RPC_OP_               0x11  * ... */
#define RPC_OP_dup            0x12 /* [+0] PUSH(TOP); */
#define RPC_OP_drop           0x13 /* [+0] POP(); */
#define RPC_OP_over           0x14 /* [+0] PUSH(SECOND); */
#define RPC_OP_pick           0x15 /* [+1] PUSH(NTH(*(u8 const *)pc));  // Where operand=0 is the old TOP */
#define RPC_OP_swap           0x16 /* [+0] TOP = XCH(SECOND, TOP); */
#define RPC_OP_rot            0x17 /* [+0] a = TOP; TOP = SECOND; SECOND = THIRD; THIRD = a; */
#define RPC_OP_abs            0x19 /* [+0] a = POP(); PUSH(a < 0 ? -a : a); */
#define RPC_OP_and            0x1a /* [+0] PUSH(POP(SECOND) & POP(TOP)); */
#define RPC_OP_div            0x1b /* [+0] PUSH(POP(SECOND) / POP(TOP)); */
#define RPC_OP_minus          0x1c /* [+0] PUSH(POP(SECOND) - POP(TOP)); */
#define RPC_OP_mod            0x1d /* [+0] PUSH(POP(SECOND) % POP(TOP)); */
#define RPC_OP_mul            0x1e /* [+0] PUSH(POP(SECOND) * POP(TOP)); */
#define RPC_OP_neg            0x1f /* [+0] PUSH(-POP()); */
#define RPC_OP_not            0x20 /* [+0] PUSH(~POP()); */
#define RPC_OP_or             0x21 /* [+0] PUSH(POP(SECOND) | POP(TOP)); */
#define RPC_OP_plus           0x22 /* [+0] PUSH(POP(SECOND) + POP(TOP)); */
/*      RPC_OP_               0x23  * ... */
#define RPC_OP_shl            0x24 /* [+0] PUSH(POP(SECOND) << POP(TOP)); */
#define RPC_OP_shr            0x25 /* [+0] PUSH((unsigned)POP(SECOND) >> POP(TOP)); */
#define RPC_OP_shra           0x26 /* [+0] PUSH((signed)POP(SECOND) >> POP(TOP)); */
#define RPC_OP_xor            0x27 /* [+0] PUSH(POP(SECOND) ^ POP(TOP)); */
#define RPC_OP_bra            0x28 /* [+2] off = *(s16 const *)pc; pc += 2; if (POP() != 0) pc += off; */
#define RPC_OP_eq             0x29 /* [+0] PUSH((signed)POP(SECOND) == (signed)POP(TOP)); */
#define RPC_OP_ge             0x2a /* [+0] PUSH((signed)POP(SECOND) >= (signed)POP(TOP)); */
#define RPC_OP_gt             0x2b /* [+0] PUSH((signed)POP(SECOND) >  (signed)POP(TOP)); */
#define RPC_OP_le             0x2c /* [+0] PUSH((signed)POP(SECOND) <= (signed)POP(TOP)); */
#define RPC_OP_lt             0x2d /* [+0] PUSH((signed)POP(SECOND) <  (signed)POP(TOP)); */
#define RPC_OP_ne             0x2e /* [+0] PUSH((signed)POP(SECOND) != (signed)POP(TOP)); */
#define RPC_OP_skip           0x2f /* [+2] off = *(s16 const *)pc; pc += 2; pc += off; */
#define RPC_OP_popreg0        0x30 /* [+0] CFI_REGISTER(0) = POP(); */
#define RPC_OP_popreg1        0x31 /* [+0] CFI_REGISTER(1) = POP(); */
#define RPC_OP_popreg2        0x32 /* [+0] CFI_REGISTER(2) = POP(); */
#define RPC_OP_popreg3        0x33 /* [+0] CFI_REGISTER(3) = POP(); */
#define RPC_OP_popreg4        0x34 /* [+0] CFI_REGISTER(4) = POP(); */
#define RPC_OP_popreg5        0x35 /* [+0] CFI_REGISTER(5) = POP(); */
#define RPC_OP_popreg6        0x36 /* [+0] CFI_REGISTER(6) = POP(); */
#define RPC_OP_popreg7        0x37 /* [+0] CFI_REGISTER(7) = POP(); */
#define RPC_OP_popreg8        0x38 /* [+0] CFI_REGISTER(8) = POP(); */
#define RPC_OP_popreg9        0x39 /* [+0] CFI_REGISTER(9) = POP(); */
#define RPC_OP_popreg10       0x3a /* [+0] CFI_REGISTER(10) = POP(); */
#define RPC_OP_popreg11       0x3b /* [+0] CFI_REGISTER(11) = POP(); */
#define RPC_OP_popreg12       0x3c /* [+0] CFI_REGISTER(12) = POP(); */
#define RPC_OP_popreg13       0x3d /* [+0] CFI_REGISTER(13) = POP(); */
#define RPC_OP_popreg14       0x3e /* [+0] CFI_REGISTER(14) = POP(); */
#define RPC_OP_popreg15       0x3f /* [+0] CFI_REGISTER(15) = POP(); */
#define RPC_OP_popreg16       0x40 /* [+0] CFI_REGISTER(16) = POP(); */
#define RPC_OP_popreg17       0x41 /* [+0] CFI_REGISTER(17) = POP(); */
#define RPC_OP_popreg18       0x42 /* [+0] CFI_REGISTER(18) = POP(); */
#define RPC_OP_popreg19       0x43 /* [+0] CFI_REGISTER(19) = POP(); */
#define RPC_OP_popreg20       0x44 /* [+0] CFI_REGISTER(20) = POP(); */
#define RPC_OP_popreg21       0x45 /* [+0] CFI_REGISTER(21) = POP(); */
#define RPC_OP_popreg22       0x46 /* [+0] CFI_REGISTER(22) = POP(); */
#define RPC_OP_popreg23       0x47 /* [+0] CFI_REGISTER(23) = POP(); */
#define RPC_OP_popreg24       0x48 /* [+0] CFI_REGISTER(24) = POP(); */
#define RPC_OP_popreg25       0x49 /* [+0] CFI_REGISTER(25) = POP(); */
#define RPC_OP_popreg26       0x4a /* [+0] CFI_REGISTER(26) = POP(); */
#define RPC_OP_popreg27       0x4b /* [+0] CFI_REGISTER(27) = POP(); */
#define RPC_OP_popreg28       0x4c /* [+0] CFI_REGISTER(28) = POP(); */
#define RPC_OP_popreg29       0x4d /* [+0] CFI_REGISTER(29) = POP(); */
#define RPC_OP_popreg30       0x4e /* [+0] CFI_REGISTER(30) = POP(); */
#define RPC_OP_popreg31       0x4f /* [+0] CFI_REGISTER(31) = POP(); */
#define RPC_OP_pushreg0       0x50 /* [+0] PUSH(CFI_REGISTER(0)); */
#define RPC_OP_pushreg1       0x51 /* [+0] PUSH(CFI_REGISTER(1)); */
#define RPC_OP_pushreg2       0x52 /* [+0] PUSH(CFI_REGISTER(2)); */
#define RPC_OP_pushreg3       0x53 /* [+0] PUSH(CFI_REGISTER(3)); */
#define RPC_OP_pushreg4       0x54 /* [+0] PUSH(CFI_REGISTER(4)); */
#define RPC_OP_pushreg5       0x55 /* [+0] PUSH(CFI_REGISTER(5)); */
#define RPC_OP_pushreg6       0x56 /* [+0] PUSH(CFI_REGISTER(6)); */
#define RPC_OP_pushreg7       0x57 /* [+0] PUSH(CFI_REGISTER(7)); */
#define RPC_OP_pushreg8       0x58 /* [+0] PUSH(CFI_REGISTER(8)); */
#define RPC_OP_pushreg9       0x59 /* [+0] PUSH(CFI_REGISTER(9)); */
#define RPC_OP_pushreg10      0x5a /* [+0] PUSH(CFI_REGISTER(10)); */
#define RPC_OP_pushreg11      0x5b /* [+0] PUSH(CFI_REGISTER(11)); */
#define RPC_OP_pushreg12      0x5c /* [+0] PUSH(CFI_REGISTER(12)); */
#define RPC_OP_pushreg13      0x5d /* [+0] PUSH(CFI_REGISTER(13)); */
#define RPC_OP_pushreg14      0x5e /* [+0] PUSH(CFI_REGISTER(14)); */
#define RPC_OP_pushreg15      0x5f /* [+0] PUSH(CFI_REGISTER(15)); */
#define RPC_OP_pushreg16      0x60 /* [+0] PUSH(CFI_REGISTER(16)); */
#define RPC_OP_pushreg17      0x61 /* [+0] PUSH(CFI_REGISTER(17)); */
#define RPC_OP_pushreg18      0x62 /* [+0] PUSH(CFI_REGISTER(18)); */
#define RPC_OP_pushreg19      0x63 /* [+0] PUSH(CFI_REGISTER(19)); */
#define RPC_OP_pushreg20      0x64 /* [+0] PUSH(CFI_REGISTER(20)); */
#define RPC_OP_pushreg21      0x65 /* [+0] PUSH(CFI_REGISTER(21)); */
#define RPC_OP_pushreg22      0x66 /* [+0] PUSH(CFI_REGISTER(22)); */
#define RPC_OP_pushreg23      0x67 /* [+0] PUSH(CFI_REGISTER(23)); */
#define RPC_OP_pushreg24      0x68 /* [+0] PUSH(CFI_REGISTER(24)); */
#define RPC_OP_pushreg25      0x69 /* [+0] PUSH(CFI_REGISTER(25)); */
#define RPC_OP_pushreg26      0x6a /* [+0] PUSH(CFI_REGISTER(26)); */
#define RPC_OP_pushreg27      0x6b /* [+0] PUSH(CFI_REGISTER(27)); */
#define RPC_OP_pushreg28      0x6c /* [+0] PUSH(CFI_REGISTER(28)); */
#define RPC_OP_pushreg29      0x6d /* [+0] PUSH(CFI_REGISTER(29)); */
#define RPC_OP_pushreg30      0x6e /* [+0] PUSH(CFI_REGISTER(30)); */
#define RPC_OP_pushreg31      0x6f /* [+0] PUSH(CFI_REGISTER(31)); */
#define RPC_OP_sppushreg0     0x70 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(0)); */
#define RPC_OP_sppushreg1     0x71 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(1)); */
#define RPC_OP_sppushreg2     0x72 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(2)); */
#define RPC_OP_sppushreg3     0x73 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(3)); */
#define RPC_OP_sppushreg4     0x74 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(4)); */
#define RPC_OP_sppushreg5     0x75 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(5)); */
#define RPC_OP_sppushreg6     0x76 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(6)); */
#define RPC_OP_sppushreg7     0x77 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(7)); */
#define RPC_OP_sppushreg8     0x78 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(8)); */
#define RPC_OP_sppushreg9     0x79 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(9)); */
#define RPC_OP_sppushreg10    0x7a /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(10)); */
#define RPC_OP_sppushreg11    0x7b /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(11)); */
#define RPC_OP_sppushreg12    0x7c /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(12)); */
#define RPC_OP_sppushreg13    0x7d /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(13)); */
#define RPC_OP_sppushreg14    0x7e /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(14)); */
#define RPC_OP_sppushreg15    0x7f /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(15)); */
#define RPC_OP_sppushreg16    0x80 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(16)); */
#define RPC_OP_sppushreg17    0x81 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(17)); */
#define RPC_OP_sppushreg18    0x82 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(18)); */
#define RPC_OP_sppushreg19    0x83 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(19)); */
#define RPC_OP_sppushreg20    0x84 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(20)); */
#define RPC_OP_sppushreg21    0x85 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(21)); */
#define RPC_OP_sppushreg22    0x86 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(22)); */
#define RPC_OP_sppushreg23    0x87 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(23)); */
#define RPC_OP_sppushreg24    0x88 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(24)); */
#define RPC_OP_sppushreg25    0x89 /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(25)); */
#define RPC_OP_sppushreg26    0x8a /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(26)); */
#define RPC_OP_sppushreg27    0x8b /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(27)); */
#define RPC_OP_sppushreg28    0x8c /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(28)); */
#define RPC_OP_sppushreg29    0x8d /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(29)); */
#define RPC_OP_sppushreg30    0x8e /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(30)); */
#define RPC_OP_sppushreg31    0x8f /* [+0] PUSH_ONTO_USER_STACK(CFI_REGISTER(31)); */
#define RPC_OP_pushregx       0x90 /* [+*] PUSH(CFI_REGISTER(dwarf_decode_uleb128(&pc))); */
/*      RPC_OP_               0x91  * ... */
#define RPC_OP_sppushregx     0x92 /* [+*] PUSH_ONTO_USER_STACK(CFI_REGISTER(dwarf_decode_uleb128(&pc))); */
/*      RPC_OP_               0x93  * ... */
#define RPC_OP_deref_size     0x94 /* [+1] n = *(u8 const *)pc; pc += 1; p = POP(); PUSH(n == 1 ? *(u8 const *)p : n == 2 ? *(u16 const *)p : n == 4 ? *(u32 const *)p : n == 8 ? *(u64 const *)p : UNDEFINED); */
#define RPC_OP_write_size     0x95 /* [+1] n = *(u8 const *)pc; pc += 1; p = POP(); v = POP(); if (n == 1) *(u8 *)p = v; else if (n == 2) *(u16 *)p = v; else if (n == 4) *(u32 *)p = v; else if (n == 8) *(u64 *)p = v; else UNDEFINED; */
#define RPC_OP_nop            0x96 /* [+0] Do nothing */
/*      RPC_OP_               0x96  * ... */
/*      RPC_OP_               0x97  * ... */
/*      RPC_OP_               0x98  * ... */
/*      RPC_OP_               0x99  * ... */
/*      RPC_OP_               0x9a  * ... */
/*      RPC_OP_               0x9b  * ... */
/*      RPC_OP_               0x9c  * ... */
/*      RPC_OP_               0x9d  * ... */
/*      RPC_OP_               0x9e  * ... */
/*      RPC_OP_               0x9f  * ... */
#define RPC_OP_push_reason    0xa0 /* [+0] PUSH(user_rpc_reason); // Either `RPC_REASONCTX_ASYNC' or `RPC_REASONCTX_SYNC' */
#define RPC_OP_push_dorestart 0xa1 /* [+0] PUSH(user_rpc_restart_syscall ? 1 : 0); // If true, implies `sc_info != NULL' */
#define RPC_OP_push_issyscall 0xa2 /* [+0] PUSH(sc_info != NULL ? 1 : 0); */
#define RPC_OP_push_sc_info   0xa3 /* [+1] word = *pc++; PUSH(((uintptr_t *)sc_info)[word]); */
#define RPC_OP_sppush_sc_info 0xa4 /* [+0] Push the entire `sc_info' descriptor onto the user stack. */
#define RPC_OP_push_param     0xa5 /* [+1] word = *pc++; PUSH(params[i]); // `params' is an argument */
#define RPC_OP_push_sigmask   0xa6 /* [+1] sigset_t s; sigprocmask(SIG_SETMASK, NULL, &s); PUSH(s.__val[*pc++]); */
#define RPC_OP_sigblock       0xa7 /* [+1] sigset_t s; sigemptyset(&s); sigaddset(&s, *pc++); sigprocmask(SIG_BLOCK, &s, NULL); */
#define RPC_OP_nbra           0xa8 /* [+2] off = *(s16 const *)pc; pc += 2; if (POP() == 0) pc += off; */
/*      RPC_OP_               ...   * ... */
/*      RPC_OP_               0xdf  * ... */
#define RPC_OP_lo_arch        0xe0 /* First arch-specific opcode */
#define RPC_OP_hi_arch        0xff /* Last arch-specific opcode */

/* Arch-specific opcodes */
#define RPC_OP_386_pushreg_fsbase 0xe0 /* [+0] Push the value of %fs.base */
#define RPC_OP_386_pushreg_gsbase 0xe1 /* [+0] Push the value of %gs.base */
#define RPC_OP_386_popreg_fsbase  0xe2 /* [+0] Pop stack-top into %fs.base */
#define RPC_OP_386_popreg_gsbase  0xe3 /* [+0] Pop stack-top into %gs.base */
/*========================================*/



#ifdef __CC__
__SYSDECL_BEGIN

/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread terminate before the  conditions for the RPC  to be served are  ever
 * met. Note that these  conditions depend on the  given `mode'. Note that  on
 * multi-arch  platforms (such as  x86), the register numbers,  as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of  `RPC_SYNCMODE_*', or'd  with
 *                     one of `RPC_SYSRESTART_*', or'd with
 *                     one of `RPC_PRIORITY_*'
 * @param: program:    The RPC program to execute (sequences of `RPC_OP_*')
 * @param: params:     RPC program parameters (for `RPC_OP_push_param')
 *
 * @return: 0 :                Success
 * @return: -1: [errno=EFAULT] Faulty pointers were given
 * @return: -1: [errno=EINVAL] The RPC program  contains illegal  instructions.
 *                             In this case, modifications made by instructions
 *                             encountered before the illegal one(s) will still
 *                             have  happened, meaning that the target thread's
 *                             state may have become inconsistent.
 * @return: -1: [errno=ESRCH]  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
__CDECLARE_OPT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,rpc_schedule,
               (__pid_t __target_tid, unsigned int __mode, void const *__program, void const *const *__params),
               (__target_tid,__mode,__program,__params))


/* >> rpc_serve(2)
 * Check for  pending RPCs.  This function  is basically  a cancellation  point in  disguise,
 * in  that it literally _is_ a regular, old cancellation point, with the only addition being
 * it doesn't contain any blocking call. You may also know this one as `pthread_testcancel()'
 * Essentially, this function  just calls  the kernel function  `task_serve()', and  forwards
 * that function's return value.
 * @return: 0 : No RPCs were served
 * @return: 1 : At least 1 RPC was served (but note that this may have been an internal,
 *              kernel-level RPC,  rather than  anything relating  to user-space  RPCs). */
__CDECLARE_OPT(,int,__NOTHROW_RPC,rpc_serve,(void),()) /*__THROWS(...)*/


struct ucpustate;

/* Callback prototype for RPC functions registered by `rpc_exec()'
 * @param: state:   The register state that  got interrupted. Note that  this
 *                  isn't necessarily the register state which will be loaded
 *                  once  this function returns,  as (depending on additional
 *                  information not exposed here), a system call as described
 *                  by the given `sc_info' may be repeated prior to returning
 * @param: reason:  Information about the context from which the current
 *                  thread was interrupted in order to service this RPC.
 *                  Either `RPC_REASONCTX_ASYNC' or `RPC_REASONCTX_SYNC'
 * @param: sc_info: Information about a system call that was interrupted in
 *                  order to service this RPC.  Note that this system  call
 *                  may or may not be  restarted once this RPC returns.  If
 *                  this  happens depends on additional information that is
 *                  not exposed to this callback.
 * @param: cookie:  The cookie-argument originally given to `rpc_exec(3)'
 * @return: * :     The new
 * @throw: * :      Exceptions may only be thrown when `reason == RPC_REASONCTX_SYNC',
 *                  as an exception thrown  from an asynchronous instruction  position
 *                  is  unpredictable by nature. However, when `RPC_REASONCTX_SYNC' is
 *                  given, the exception is thrown such that it will appear as  though
 *                  it  was caused by the aborted system  call or interrupt (such as a
 *                  page-fault throwing E_SEGFAULT, an  RPC aborting a page-fault  may
 *                  throw that same, or some completely different exception) */
typedef struct ucpustate *
(__LIBKCALL *prpc_exec_callback_t)(struct ucpustate *__restrict __state, unsigned int __reason,
                                   struct rpc_syscall_info const *__sc_info, void *__cookie)
		__THROWS(...);


/* >> rpc_exec(3)
 * Send a RPC to `target_tid' (which must be a thread within the current process).
 * The RPC will modify  the target thread's register  state such that `func'  will
 * be executed before  (upon its  return), execution resumes  within that  thread.
 * How/when exactly the RPC is served depends on the given `mode'.
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of  `RPC_SYNCMODE_*', or'd  with
 *                     one of `RPC_SYSRESTART_*', or'd with
 *                     one of `RPC_PRIORITY_*'
 * @return: 0 :                Success
 * @return: -1: [errno=ESRCH]  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
__CDECLARE_OPT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,rpc_exec,
               (__pid_t __target_tid, unsigned int __mode, prpc_exec_callback_t __func, void *__cookie),
               (__target_tid,__mode,__program,__params))

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
 * @param: mode:       One of  `RPC_SYNCMODE_*', or'd  with
 *                     one of `RPC_SYSRESTART_*', or'd with
 *                     one of `RPC_PRIORITY_*'
 * @return: 0 :               Success
 * @return: -1: [errno=ESRCH] The  target thread has already terminated, or
 *                            doesn't exist.  Note though  that unless  the
 *                            thread is part of your own process, there are
 *                            still many  reasons outside  of your  control
 *                            for why  it may  terminate immediately  after
 *                            the RPC program finished. */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,rpc_interrupt,
               (__pid_t __target_tid, unsigned int __mode),
               (__target_tid,__mode))





/************************************************************************/
/* Exception-enabled version of the above API                           */
/************************************************************************/

/* @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION: [...] */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1, 2)),__THROWING,RpcSchedule,
                    (__pid_t __target_tid, unsigned int __mode, void const *__program, void const *const *__params),
                    (__target_tid,__mode,__program,__params))
		/*__THROWS(E_SEGFAULT, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_PROCESS_EXITED)*/
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1, 3)),__THROWING,RpcExec,
                    (__pid_t __target_tid, unsigned int __mode, prpc_exec_callback_t __func, void *__cookie),
                    (__target_tid,__mode,__program,__params))
		/*__THROWS(E_PROCESS_EXITED)*/
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1)),__THROWING,RpcInterrupt,
                    (__pid_t __target_tid, unsigned int __mode),
                    (__target_tid,__mode))
		/*__THROWS(E_PROCESS_EXITED)*/



__SYSDECL_END
#endif /* __CC__ */


#endif /* !_KOS_RPC_H */
