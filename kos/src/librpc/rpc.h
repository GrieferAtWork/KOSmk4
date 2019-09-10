/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBRPC_RPC_H
#define GUARD_LIBRPC_RPC_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <librpc/rpc.h>

DECL_BEGIN

/* >> rpc_service(2)
 * Service RPC callbacks (user-space variant of the kernel-space `task_serve()')
 * @return:  1: At least 1 RPC callback was serviced. (though this may
 *              have been a kernel-level RPC that didn't actually affect
 *              user-space)
 * @return:  0: No RPC callbacks were served.
 * @return: -1: Error (s.a. `errno')
 * @throws: * : Anything (RPC callbacks may throw exceptions) */
INTDEF int CC librpc_service(void);

/* >> rpc_schedule_ex(2)
 * Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid.
 * NOTE: The system call of this function is called `sys_rpc_schedule()' */
INTDEF NONNULL((3)) int CC
librpc_schedule_ex(pid_t target, syscall_ulong_t flags,
                   uint8_t const *__restrict program,
                   void **arguments);


/* >> rpc_schedule(3)
 * Portable wrapper for `rpc_schedule_ex()'
 * Schedule a simple RPC for execution on a given `target' thread.
 * The scheduled RPC assumes that `target' has a valid stack, while
 * taking a `callback' to-be invoked, which itself will take `argc'
 * pointer-sized arguments from the variable argument list of this
 * function. (When `RPC_SCHEDULE_FLAG_STATUSFUTEX' is given, `callback'
 * takes `argc - 1' arguments, with the first variable argument being
 * a pointer to the status futex)
 * HINT: This function is entirely implemented using `rpc_schedule_ex()'
 * HINT: On i386, the RPC program used by this function is:
 *       >> psh  %eip                        RPC_PROGRAM_OP_plda | RPC_386_REGISTER_EIP
 *       >> lod  %eip, %arg[0]
 *       >> psh  %eflags                     RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EFLAGS
 *       >> psh  %ebx                        RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EBX
 *       >> psh  %ebp                        RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EBP
 *       >> psh  %edx                        RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_EDX
 *       >> psh  %ecx                        RPC_PROGRAM_OP_pshr | RPC_386_REGISTER_ECX
 *       >> psh  %eax                        RPC_PROGRAM_OP_plda | RPC_386_REGISTER_EAX
 *       >> lod  %eax, %arg[1]
 *       >> mov  %esp, %ebp                  RPC_PROGRAM_OP_mov
 *       >>                                  RPC_PROGRAM_OP_arg | RPC_386_REGISTER_ESP
 *       >>                                  RPC_PROGRAM_OP_arg | RPC_386_REGISTER_EBP
 *       >> psh  syscall_info                RPC_PROGRAM_OP_psh_sys
 *       >> lod  %ebx, reason                RPC_PROGRAM_OP_lod_rsn | RPC_386_REGISTER_EBX
 *       >> rep  %arg[2]                     RPC_PROGRAM_OP_rep_stftx_psha
 *       >> [stftx %arg[3]]
 *       >> psh  %arg[(3|4) + n...]
 *       >> resume                           RPC_PROGRAM_OP_resume
 *       When `callback' returns, an internal wrapper is called that will restore
 *       registers, as well as optionally restart an interrupted system call,
 *       depending on the reason code loaded into `%ebx', before restoring registers
 *       using the data pointed to by `%ebp'
 *       With all of this in mind, the register state when librpc's internal RPC
 *       wrapper is entered looks as follows:
 *        - %ebx:     RPC reason (One of { RPC_REASON_ASYNC, RPC_REASON_SYSCALL })
 *        - %eax:     User-callback to invoke
 *        - 0(%ebp):  Saved EAX
 *        - 4(%ebp):  Saved ECX
 *        - 8(%ebp):  Saved EDX
 *        - 12(%ebp): Saved EBP
 *        - 16(%ebp): Saved EBX
 *        - 20(%ebp): Saved EFLAGS
 *        - 24(%ebp): Saved EIP
 *        - 28(%ebp): <LEA: Old ESP>
 *        - -SIZEOF_RPC_SYSCALL_INFO(%ebp): System call info (if EBX == RPC_REASON_SYSCALL)
 *        - 0(%esp):  ARG[0]
 *        - 4(%esp):  ARG[1]
 *        - 8(%esp):  ...
 * @param: target:   The targeted thread.
 * @param: flags:    RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: callback: The callback to invoke
 * @param: argc:     The number of arguments to-be passed to `callback'
 * @param: ...:      Arguments passed to `callback', potentially preceded by
 *                   the status futex when the `RPC_SCHEDULE_FLAG_STATUSFUTEX'
 *                   flag was set.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
INTDEF NONNULL((3)) int VCC
librpc_schedule(pid_t target, syscall_ulong_t flags, void (*callback)(),
                size_t argc, /* uintptr_t *status_futex */ /* uintptr_t ...args */...);



DECL_END

#endif /* !GUARD_LIBRPC_RPC_H */
