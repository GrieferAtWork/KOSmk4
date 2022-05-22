/* HASH CRC-32:0x74bc1a7d */
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
#ifndef GUARD_LIBC_AUTO_KOS_RPC_H
#define GUARD_LIBC_AUTO_KOS_RPC_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/rpc.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread may terminate  before the conditions  for the RPC  to be served  are
 * ever met. Note that these conditions depend on the given `mode'. Note  that
 * on multi-arch platforms (such as x86), the register numbers, as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 *
 * NOTE: This function is a cancellation point when `RPC_JOIN_WAITFOR' is given!
 *
 * @param: target_tid:      The TID of the targeted thread
 * @param: mode:            One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                          one of `RPC_SYSRESTART_*', optionally or'd with
 *                          one of `RPC_PRIORITY_*',  optionally or'd  with
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
 *                             The RPC program contains illegal instructions.
 * @throws: E_PROCESS_EXITED:  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
INTDEF ATTR_IN(3) ATTR_INS(4, 5) int NOTHROW_RPC(LIBDCALL libd_rpc_schedule)(pid_t target_tid, unsigned int mode, void const *program, void const *const *params, size_t max_param_count);
/* >> rpc_exec(3)
 * Send an RPC to `target_tid' (which must be a thread within the  current
 * process). The RPC will modify  the target thread's register state  such
 * that `func' will be executed before (upon its return) execution resumes
 * within that thread.
 * How/when exactly the RPC is served depends on the given `mode'.
 * WARNING: Unless special conditions are met, trying to use this function to send
 *          an RPC to another process  (read: different mman), will probably  fail
 *          due  to the address  of `func' mapping to  a different location within
 *          that other process.
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_PRIORITY_*',  optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :                Success
 * @return: -1: [errno=ESRCH]  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
INTDEF NONNULL((3)) int NOTHROW_RPC(LIBDCALL libd_rpc_exec)(pid_t target_tid, unsigned int mode, prpc_exec_callback_t func, void *cookie);
/* >> rpc_interrupt(3)
 * Send an RPC to `target_tid' (which must be a thread within the current
 * process).  The RPC won't do anything except causing an in-progress (or
 * upcoming) system  call to  fail with  `errno=EINTR' (so-long  as  that
 * system call isn't marked as [restart(dont)]).
 *
 * This function can be used to send sporadic interrupts to other threads within
 * the  current process, as well as allow  one to stop in-progress, but blocking
 * system calls performed by  those threads. This function  is a no-op when  the
 * given `target_tid == gettid()'.
 *
 * NOTE: This function is a cancellation point when `RPC_JOIN_WAITFOR' is given!
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_PRIORITY_*',  optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :               Success
 * @return: -1: [errno=ESRCH] The  target thread has already terminated, or
 *                            doesn't exist.  Note though  that unless  the
 *                            thread is part of your own process, there are
 *                            still many  reasons outside  of your  control
 *                            for why  it may  terminate immediately  after
 *                            the RPC program finished. */
INTDEF int NOTHROW_RPC(LIBDCALL libd_rpc_interrupt)(pid_t target_tid, unsigned int mode);
/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread may terminate  before the conditions  for the RPC  to be served  are
 * ever met. Note that these conditions depend on the given `mode'. Note  that
 * on multi-arch platforms (such as x86), the register numbers, as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 *
 * NOTE: This function is a cancellation point when `RPC_JOIN_WAITFOR' is given!
 *
 * @param: target_tid:      The TID of the targeted thread
 * @param: mode:            One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                          one of `RPC_SYSRESTART_*', optionally or'd with
 *                          one of `RPC_PRIORITY_*',  optionally or'd  with
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
 *                             The RPC program contains illegal instructions.
 * @throws: E_PROCESS_EXITED:  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
INTDEF ATTR_IN(3) ATTR_INS(4, 5) void (LIBDCALL libd_RpcSchedule)(pid_t target_tid, unsigned int mode, void const *program, void const *const *params, size_t max_param_count) THROWS(...);
/* >> rpc_exec(3)
 * Send an RPC to `target_tid' (which must be a thread within the  current
 * process). The RPC will modify  the target thread's register state  such
 * that `func' will be executed before (upon its return) execution resumes
 * within that thread.
 * How/when exactly the RPC is served depends on the given `mode'.
 * WARNING: Unless special conditions are met, trying to use this function to send
 *          an RPC to another process  (read: different mman), will probably  fail
 *          due  to the address  of `func' mapping to  a different location within
 *          that other process.
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_PRIORITY_*',  optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :                Success
 * @return: -1: [errno=ESRCH]  The  target thread has already terminated, or
 *                             doesn't exist.  Note though  that unless  the
 *                             thread is part of your own process, there are
 *                             still many  reasons outside  of your  control
 *                             for why  it may  terminate immediately  after
 *                             the RPC program finished. */
INTDEF NONNULL((3)) void (LIBDCALL libd_RpcExec)(pid_t target_tid, unsigned int mode, prpc_exec_callback_t func, void *cookie) THROWS(...);
/* >> rpc_interrupt(3)
 * Send an RPC to `target_tid' (which must be a thread within the current
 * process).  The RPC won't do anything except causing an in-progress (or
 * upcoming) system  call to  fail with  `errno=EINTR' (so-long  as  that
 * system call isn't marked as [restart(dont)]).
 *
 * This function can be used to send sporadic interrupts to other threads within
 * the  current process, as well as allow  one to stop in-progress, but blocking
 * system calls performed by  those threads. This function  is a no-op when  the
 * given `target_tid == gettid()'.
 *
 * NOTE: This function is a cancellation point when `RPC_JOIN_WAITFOR' is given!
 *
 * @param: target_tid: The TID of the targeted thread
 * @param: mode:       One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                     one of `RPC_SYSRESTART_*', optionally or'd with
 *                     one of `RPC_PRIORITY_*',  optionally or'd  with
 *                     one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                     one of `RPC_JOIN_*'
 * @return: 0 :               Success
 * @return: -1: [errno=ESRCH] The  target thread has already terminated, or
 *                            doesn't exist.  Note though  that unless  the
 *                            thread is part of your own process, there are
 *                            still many  reasons outside  of your  control
 *                            for why  it may  terminate immediately  after
 *                            the RPC program finished. */
INTDEF void (LIBDCALL libd_RpcInterrupt)(pid_t target_tid, unsigned int mode) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_RPC_H */
