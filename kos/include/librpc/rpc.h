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
#ifndef _LIBRPC_RPC_H
#define _LIBRPC_RPC_H 1

#include <bits/types.h>

#include <librpc/bits/rpc.h>
#include <librpc/bits/syscall-info.h>

#include "api.h"

__SYSDECL_BEGIN

/* User-space thread Remote Procedure Calls
 * Using these, user-space  can deliver custom  interrupts to arbitrary  threads
 * which may then be used to execute custom code, or even terminate the targeted
 * thread.
 * For  this purpose, the kernel defines a set of system calls that may be used
 * as cancellation points for synchronous RPCs, whilst asynchronous RPCs may be
 * serviced anytime.
 * WARNING: Synchronous  are only checked  when the target  thread is about to
 *          perform some a low-level blocking  operation such as acquiring  an
 *          already  locked mutex. -  They are however not  checked if a mutex
 *          wasn't locked already, or if the target thread was able to perform
 *          its current operation without blocking!
 *          However,  if the  target thread was  already blocking when  the RPC was
 *          scheduled,  it  will stop  blocking  and service  the  RPC immediately.
 *          Unrelated  to  this,  the target  thread  may also  manually  check for
 *          pending, synchronous RPCs by  calling the `rpc_service()' system  call.
 *          Additionally,  when it comes  to system calls,  only a specific sub-set
 *          of calls can actually be used to service user-level RPCs, meaning  that
 *          calls such as close() or munmap() are guarantied to complete atomically
 *          without being interruptible by synchronous RPCs.
 *          This set of system calls is also known as those marked as [cp] (Cancellation Points).
 * HINT: Any function that may (under circumstances) service synchronous RPCs
 *       is declared as `__NOTHROW_RPC' (or [rpc], et.al.)
 *
 * To allow for maximum flexibility, irregardless of what state a targeted  thread
 * may be in at the time when an RPC gets serviced, low-level RPC invocations must
 * define  a small program that describes how  the state of the interrupted thread
 * should be modified before an interrupt routine is invoked. */



/* Opcodes used to describe how to transform the environment of a
 * target thread in order to be able to service some custom  RPC.
 * NOTE: Modifications made by such a program are atomic in  regards
 *       to normal user-space code execution, as well as other RPCs.
 * NOTE: These opcodes intentionally aren't anywhere near turing-complete,
 *       mainly  because they're only intended for limited transformations
 *       that  should  be performed  in  order to  schedule  arbitrary RPC
 *       callbacks, whilst allowing for any or no assumptions at all being
 *       made on the target thread's state.
 * Upon program start, `i = 0' and `newreg' is a mirror copy of `oldreg'
 * Example (RPC definition):
 * >>     psh   %eip           // Return address
 * >>     lod   %eip, %arg[0]  // Redirected
 * >>     psh   %ecx           // Preserve ECX
 * >>     lod   %ecx, %arg[1]  // Load ECX
 * >>     psh   %edx           // Preserve EDX
 * >>     lod   %edx, %arg[2]  // Load EDX
 * Example (Assembly entry override == arg[1]):
 * >> rpc_entry:
 * >>     call  *%ecx
 * >>     popl  %edx
 * >>     popl  %ecx
 * >>     ret
 * Example (C-invocation):
 * >> void ATTR_FASTCALL my_rpc(void *arg) {
 * >>     ...
 * >> }
 * >> void send_rpc(pid_t target, void *arg) {
 * >>     PRIVATE uint8_t const program[] = {
 * >>         RPC_PROGRAM_OP_plda | RPC_386_REGISTER_EIP,
 * >>         RPC_PROGRAM_OP_plda | RPC_386_REGISTER_ECX,
 * >>         RPC_PROGRAM_OP_plda | RPC_386_REGISTER_EDX,
 * >>         RPC_PROGRAM_OP_resume,
 * >>     };
 * >>     void *argv[3];
 * >>     argv[0] = &rpc_entry;
 * >>     argv[1] = &my_rpc;
 * >>     argv[2] = arg;
 * >>     rpc_schedule_ex(target,
 * >>                     program,
 * >>                     argv,
 * >>                     SCHEDULE_RPC_FNORMAL);
 * >> }
 */
#define RPC_PROGRAM_OP_resume   0x00 /* `resume' -- Modifications complete - resume execution (required to terminate an RPC program) */
#define RPC_PROGRAM_OP_psha     0x01 /* `psh  %arg[i++]'               -- Push the next argument onto the stack (data size == sizeof(void *)). */
#define RPC_PROGRAM_OP_psh_rsn  0x02 /* `psh  reason'                  -- Push the reason for the interrupt (one of `RPC_REASON_*') (data size == sizeof(void *)). */
#define RPC_PROGRAM_OP_psh_sys  0x03 /* `psh  syscall_info'            -- Push system call information (when `RPC_REASON_SYSCALL', as a `struct rpc_syscall_info'); (no data is pushed if the RPC had any other reason) */
#define RPC_PROGRAM_OP_rep_psha 0x04 /* `rep(%arg[i++]) psh %arg[i++]' -- Push a variable number of arguments onto the stack. */
#define RPC_PROGRAM_OP_mov      0x05 /* `mov  %oldreg(a), %newreg(a)'  -- Copy register `a'          (this opcode must be followed by 1 `RPC_PROGRAM_OP_arg' with operands `a').
                                      * `mov  %oldreg(a), %newreg(b)'  -- Copy register `a' into `b' (this opcode must be followed by 2 `RPC_PROGRAM_OP_arg' with operands `a' and `b' (in that order)). */
#define RPC_PROGRAM_OP_xita     0x06 /* `xit  %arg[i++]'               -- Terminate the targeted thread by throwing an `E_EXIT_THREAD' exception with `%arg[i]' as argument
                                      *                                   WARNING: This instruction does not terminate the RPC program and must still be followed by `RPC_PROGRAM_OP_resume' */
#define RPC_PROGRAM_OP_xipa     0x07 /* `xip  %arg[i++]'               -- Terminate the targeted process by throwing an `E_EXIT_PROCESS' exception with `%arg[i]' as argument
                                      *                                   WARNING: This instruction does not terminate the RPC program and must still be followed by `RPC_PROGRAM_OP_resume' */
#define RPC_PROGRAM_OP_zero     0x08 /* `zero %newreg(a)'                                       -- %newreg(a) = 0 */
#define RPC_PROGRAM_OP_ifthen   0x08 /* `ifthen %newreg(b), %newreg(a)'                         -- %newreg(a) = %newreg(b) != 0 ? %newreg(b) : %newreg(a)
                                      * `ifthen %newreg(c), %newreg(b), %newreg(a)'             -- %newreg(a) = %newreg(b) != 0 ? %newreg(c) : %newreg(a)
                                      * `ifthen %newreg(d), %newreg(c), %newreg(b), %newreg(a)' -- %newreg(a) = %newreg(b) != 0 ? %newreg(c) : %newreg(d) */
#define RPC_PROGRAM_OP_stftx    0x09 /* `[stftx %arg[i++]]'            -- Take the address of the status futex from arguments (Ignored if the `RPC_SCHEDULE_FLAG_STATUSFUTEX' flag isn't set) */
#define RPC_PROGRAM_OP_rep_stftx_psha 0x0a /* `rep(%arg[i++]); [stftx %arg[i++]]; psh %arg[i++]' -- An intermingled variant of `stftx + rep_psha' that takes arguments in the order { argc, stftx, args...*argc } */
/*      RPC_PROGRAM_OP_         0x0a /* ... */
/*      RPC_PROGRAM_OP_         0x0b /* ... */
/*      RPC_PROGRAM_OP_         0x0c /* ... */
/*      RPC_PROGRAM_OP_         0x0d /* ... */
/*      RPC_PROGRAM_OP_         0x0e /* ... */
#define RPC_PROGRAM_OP_ext      0x0f /* Extended opcode prefix (must be followed by 1 or more `RPC_PROGRAM_OP_arg' opcodes, the first of which contains the actual opcode as operand) */
#define RPC_PROGRAM_OP_add      0x10 /* >> add  %arg[i++],  %newreg(a)             #          -- %newreg(a) = %newreg(a) + %arg[i++]
                                      * >> add  %arg[i++],  %newreg(b), %newreg(a) #          -- %newreg(a) = %newreg(b) + %arg[i++]
                                      * >> add  %newreg(c), %newreg(b), %newreg(a) #          -- %newreg(a) = %newreg(b) + %newreg(c) */
#define RPC_PROGRAM_OP_sub      0x11 /* >> sub  %arg[i++],  %newreg(a)             #          -- %newreg(a) = %newreg(a) - %arg[i++]
                                      * >> sub  %arg[i++],  %newreg(b), %newreg(a) #          -- %newreg(a) = %newreg(b) - %arg[i++]
                                      * >> sub  %newreg(c), %newreg(b), %newreg(a) #          -- %newreg(a) = %newreg(b) - %newreg(c) */
#define RPC_PROGRAM_OP_arith    0x11 /* >> mul  %newreg(c), %newreg(b), %newreg(a) # + d=0x00 -- %newreg(a) = %newreg(b) * %newreg(c)
                                      * >> div  %newreg(c), %newreg(b), %newreg(a) # + d=0x01 -- %newreg(a) = %newreg(b) / %newreg(c)
                                      * >> mod  %newreg(c), %newreg(b), %newreg(a) # + d=0x02 -- %newreg(a) = %newreg(b) % %newreg(c)
                                      * >> shl  %newreg(c), %newreg(b), %newreg(a) # + d=0x03 -- %newreg(a) = %newreg(b) << %newreg(c)
                                      * >> shr  %newreg(c), %newreg(b), %newreg(a) # + d=0x04 -- %newreg(a) = %newreg(b) >> %newreg(c)
                                      * >> sar  %newreg(c), %newreg(b), %newreg(a) # + d=0x05 -- %newreg(a) = (signed)%newreg(b) >> %newreg(c)
                                      * >> and  %newreg(c), %newreg(b), %newreg(a) # + d=0x06 -- %newreg(a) = %newreg(b) & %newreg(c)
                                      * >> andn %newreg(c), %newreg(b), %newreg(a) # + d=0x07 -- %newreg(a) = %newreg(b) & ~%newreg(c)
                                      * >> or   %newreg(c), %newreg(b), %newreg(a) # + d=0x08 -- %newreg(a) = %newreg(b) | %newreg(c)
                                      * >> orn  %newreg(c), %newreg(b), %newreg(a) # + d=0x09 -- %newreg(a) = %newreg(b) | ~%newreg(c)
                                      * >> xor  %newreg(c), %newreg(b), %newreg(a) # + d=0x0a -- %newreg(a) = %newreg(b) ^ %newreg(c)
                                      * >> xorn %newreg(c), %newreg(b), %newreg(a) # + d=0x0b -- %newreg(a) = %newreg(b) ^ ~%newreg(c)
                                      * NOTE: Divide-by-zero will set the `RPC_STATUS_BADARGUMENTS' status (as will modulo-by-zero). */

/*      RPC_PROGRAM_OP_         0x16 /* ... */
/*      RPC_PROGRAM_OP_         0x17 /* ... */
#define RPC_PROGRAM_OP_padd     0x18 /* >> psh  add  %newreg(a), %arg[i++]  #           -- `push(%newreg(a) + %arg[i++]);'
                                      * >> psh  add  %newreg(b), %newreg(a) #           -- `push(%newreg(a) + %newreg(b));' */
#define RPC_PROGRAM_OP_psub     0x19 /* >> psh  sub  %newreg(a), %arg[i++]  #           -- `push(%newreg(a) - %arg[i++]);'
                                      * >> psh  sub  %newreg(b), %newreg(a) #           -- `push(%newreg(a) - %newreg(b));' */
#define RPC_PROGRAM_OP_parith   0x19 /* >> psh  mul  %newreg(b), %newreg(a) # + c=0x00  -- `push(%newreg(a) * %newreg(b));'
                                      * >> psh  div  %newreg(b), %newreg(a) # + c=0x01  -- `push(%newreg(a) / %newreg(b));'
                                      * >> psh  mod  %newreg(b), %newreg(a) # + c=0x02  -- `push(%newreg(a) % %newreg(b));'
                                      * >> psh  shl  %newreg(b), %newreg(a) # + c=0x03  -- `push(%newreg(a) << %newreg(b));'
                                      * >> psh  shr  %newreg(b), %newreg(a) # + c=0x04  -- `push(%newreg(a) >> %newreg(b));'
                                      * >> psh  sar  %newreg(b), %newreg(a) # + c=0x05  -- `push((signed)%newreg(a) >> %newreg(b));'
                                      * >> psh  and  %newreg(b), %newreg(a) # + c=0x06  -- `push(%newreg(a) & %newreg(b));'
                                      * >> psh  andn %newreg(b), %newreg(a) # + c=0x07  -- `push(%newreg(a) & ~%newreg(b));'
                                      * >> psh  or   %newreg(b), %newreg(a) # + c=0x08  -- `push(%newreg(a) | %newreg(b));'
                                      * >> psh  orn  %newreg(b), %newreg(a) # + c=0x09  -- `push(%newreg(a) | ~%newreg(b));'
                                      * >> psh  xor  %newreg(b), %newreg(a) # + c=0x0a  -- `push(%newreg(a) ^ %newreg(b));'
                                      * >> psh  xorn %newreg(b), %newreg(a) # + c=0x0b  -- `push(%newreg(a) ^ ~%newreg(b));'
                                      * NOTE: Divide-by-zero will set the `RPC_STATUS_BADARGUMENTS' status. */
/*      RPC_PROGRAM_OP_         0x1d /* ... */
/*      RPC_PROGRAM_OP_         0x1e /* ... */
/*      RPC_PROGRAM_OP_         0x1f /* ... */
#define RPC_PROGRAM_OP_pshr     0x20 /* `psh  %oldreg(opcode & 0x1f)'                -- Push a register onto a stack `%newreg(<STACK_POINTER>)' */
#define RPC_PROGRAM_OP_loda     0x40 /* `lod  %newreg(opcode & 0x1f), %arg[i++]'     -- Load the next argument into a register. */
#define RPC_PROGRAM_OP_plda     0x60 /* Combination of psh+lod for the register `opcode & 0x1f' */
#define RPC_PROGRAM_OP_lod_rsn  0x80 /* `lod  %newreg(opcode & 0x1f), reason'        -- Load the interrupt reason (one of `RPC_REASON_*') into a register. */
/*      RPC_PROGRAM_OP_         0xc0 /* ... */
#define RPC_PROGRAM_OP_nop      0xe0 /* `nop'  -- No-op (though `opcode & 0x1f' may be used as operand by a preceding opcode) */
#define RPC_PROGRAM_OP_arg      0xe0 /* Argument for the preceding opcode */


/* Arithmetic opcodes (used to encode operation codes for `RPC_PROGRAM_OP_arith' / `RPC_PROGRAM_OP_parith') */
#define RPC_PROGRAM_OP_ARITH_MUL  (RPC_PROGRAM_OP_arg|0x00)
#define RPC_PROGRAM_OP_ARITH_DIV  (RPC_PROGRAM_OP_arg|0x01)
#define RPC_PROGRAM_OP_ARITH_MOD  (RPC_PROGRAM_OP_arg|0x02)
#define RPC_PROGRAM_OP_ARITH_SHL  (RPC_PROGRAM_OP_arg|0x03)
#define RPC_PROGRAM_OP_ARITH_SHR  (RPC_PROGRAM_OP_arg|0x04)
#define RPC_PROGRAM_OP_ARITH_SAR  (RPC_PROGRAM_OP_arg|0x05)
#define RPC_PROGRAM_OP_ARITH_AND  (RPC_PROGRAM_OP_arg|0x06)
#define RPC_PROGRAM_OP_ARITH_ANDN (RPC_PROGRAM_OP_arg|0x07)
#define RPC_PROGRAM_OP_ARITH_OR   (RPC_PROGRAM_OP_arg|0x08)
#define RPC_PROGRAM_OP_ARITH_ORN  (RPC_PROGRAM_OP_arg|0x09)
#define RPC_PROGRAM_OP_ARITH_XOR  (RPC_PROGRAM_OP_arg|0x0a)
#define RPC_PROGRAM_OP_ARITH_XORN (RPC_PROGRAM_OP_arg|0x0b)


/* RPC reason codes (used to describe the state of a target at the time of an interrupt) */
#define RPC_REASON_ASYNC       0x0000 /* Arbitrary user-space code was interrupted. */
#define RPC_REASON_SYSCALL     0x0001 /* FLAG: A system call was interrupted, and should be restarted once the RPC callback returns/completes. */
#define RPC_REASON_CONTEXTMASK 0x00ff /* Mask for RPC reason context codes (unmasked bits are unused/reserved for flags) */


/* RPC scheduling flags:
 *   A: Flag may be used for asynchronous RPCs
 *   S: Flag may be used for synchronous RPCs
 * HINT (how kernel-space RPCs are mapped):
 *   - USER_RPC:                       RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NOINTERRUPT
 *   - USER_RPC_INTERRUPT:             RPC_SCHEDULE_ASYNC
 *   - USER_RPC_SYNC_INTERRUPT:        RPC_SCHEDULE_SYNC
 *   - USER_RPC_SYNC_INTERRUPT_NONSYS: RPC_SCHEDULE_SYNC|RPC_SCHEDULE_FLAG_NONSYSCALL
 */
#define RPC_SCHEDULE_SYNC               0x0000 /* [S] Schedule the RPC as synchronous (Only allow S-flags; disallow A-flags).
                                                * NOTE: Only synchronous RPCs may return by means other than directly returning  to
                                                *       the interrupted location. - I.e. Only synchronous RPCs may throw exception!
                                                * Also: Be aware that while in the context of another thread, you should respect that
                                                *       thread's expectations of  the severity  of modifications made  to globals  by
                                                *       certain function, as well as their reach.
                                                *       For example: You probably shouldn't clobber `errno', or load/unload libraries,
                                                *                    or make  similarly  drastic  changes the  global  program  state.
                                                *       However, in theory, you are allowed to perform (most) blocking operations  based
                                                *       on assumption that since  it was a  blocking operation that  allowed the RPC  to
                                                *       be serviced, the program is in a state where (most) blocking is possible without
                                                *       running the risk of causing a dead-lock  (though still be careful in regards  to
                                                *       things  like recursive- or  atomic locks, as well  as preventing combinations of
                                                *       locks that were never meant to interact  with- or be combined with each  other). */
#define RPC_SCHEDULE_ASYNC              0x0001 /* [A] Schedule the RPC as asynchronous (Only allow A-flags; disallow S-flags).
                                                * NOTE: An  asynchronous  RPC  should never  do  anything that  may  potentially block.
                                                *       This excludes operations that could only feasibly block whilst in kernel-space,
                                                *       meaning that pretty  much every  system call  is still  allowed, though  pretty
                                                *       much all user-space functions aren't. */
#define RPC_SCHEDULE_FLAG_NOINTERRUPT   0x0002 /* [A] Don't force the target to return to user-space (don't throw
                                                * an `E_INTERRUPT_USER_RPC'  to  unwind  kernel-space  execution) */
#define RPC_SCHEDULE_FLAG_NONSYSCALL    0x0002 /* [S] Allow  synchronous  RPCs  to  be  serviced  for  reasons   other
                                                * than RPC_REASON_SYSCALL.  - This  can e.g.  happen when  the  target
                                                * thread accesses VIO memory, or a memory-mapped file needs to acquire
                                                * a blocking lock in order to be able to load data from disk. */
/*      RPC_SCHEDULE_FLAG_              0x0004 /* ... */
/*      RPC_SCHEDULE_FLAG_              0x0008 /* ... */
/*      RPC_SCHEDULE_FLAG_              0x0010 /* ... */
#define RPC_SCHEDULE_FLAG_WAITFORSTART  0x0020 /* [A|S] Blocking wait for the RPC to reach a state of being able to start.
                                                * NOTE: If the target terminates before servicing can start, `rpc_schedule_ex()'
                                                *       will  return  to  indicate  that  the  target  thread  has   terminated. */
#define RPC_SCHEDULE_FLAG_STATUSFUTEX   0x0040 /* [A|S] Allow the program to define a futex pointer to which the pointer-sized
                                                * RPC  state  will  be  written,  as  one  of  the  `RPC_STATUS_*'  constants. */
/*      RPC_SCHEDULE_FLAG_              0x0080 /* ... */
#define RPC_SCHEDULE_FLAG_SYSRESTART    0x0100 /* [A|S] Always restart interrupted system calls (Always indicate `RPC_REASON_SYSCALL' as reason for system calls).
                                                * This flag behaves identical to the `SA_RESTART' flag for signal handlers. */
#define RPC_SCHEDULE_FLAG_NOSYSRESTART  0x0200 /* [A|S] Never restart interrupted system calls (Always indicate `RPC_REASON_ASYNC' as reason). */
/*      RPC_SCHEDULE_FLAG_              0x0400 /* ... */
/*      RPC_SCHEDULE_FLAG_              0x0800 /* ... */
#define RPC_SCHEDULE_FLAG_WAITSMPACK    0x1000 /* [A|S] In an SMP environment, wait for the target's CPU to acknowledge a potential IPI. */
#define RPC_SCHEDULE_FLAG_DONTWAKE      0x2000 /* [A|S] Don't trigger a  sporadic wake-up of  the target  thread (don't force  the target  to
                                                * begin a quantum when IDLE before, but keep it idle until something else causes an wake-up).
                                                * Note that a sporadic wake-up is likely to not be noticeable from user-space. */
#define RPC_SCHEDULE_FLAG_HIGHPRIO      0x4000 /* [A|S] Schedule the RPC with high priority (if the target is hosted by the same
                                                * CPU as the caller, preempt the caller's current quantum and immediately switch
                                                * to the targeted thread to service the RPC) */


/* RPC futex status values. */
#define RPC_STATUS_PENDING       0x0000 /* Initial value that should be set by the caller: The RPC is pending. */
#define RPC_STATUS_SERVICED      0x0001 /* SUCCESS: The RPC has been successfully serviced. */
#define RPC_STATUS_TERMINATED    0x0002 /* ERROR:   The target thread has terminated before the RPC could be serviced.
                                         * NOTE: This status is only set if the target terminates _after_ `rpc_schedule_ex()'
                                         *       has returned  indicating success.  -  Not when  `rpc_schedule_ex()'  already
                                         *       indicated that  the  target has  terminated,  and  also not  if  the  target
                                         *       terminates after servicing of the RPC has begun. */
/* Special error return codes. */
#define RPC_STATUS_BADPROGRAM    0x8000 /* The given program contains an illegal/unknown instruction */
#define RPC_STATUS_BADARGUMENTS  0x8001 /* Attempted to load a register with an invalid value (e.g. CS = KERNEL_CS) */
#define RPC_STATUS_BADPOINTER    0x8002 /* The program or arguments pointer is faulty within the context of the VM of `target'
                                         * NOTE: With  the exception of  `RPC_SCHEDULE_FLAG_STATUSFUTEX', both the `program',
                                         *       as well as the `arguments' and `arguments[i]' pointers need to be valid both
                                         *       within the context of the VM of the calling thread, as well as the VM of the
                                         *       targeted thread. */



#define RPC_SYSCALL_INFO_FNORMAL         0x0000 /* Normal system call flags. */
#define RPC_SYSCALL_INFO_FEXCEPT         0x8000 /* Exceptions were enabled for this system call. */
#define RPC_SYSCALL_INFO_FMETHOD         0x00ff /* Mask for the arch-specific system call invocation method. (One of `SYSCALL_INFO_METHOD_*') */
#define RPC_SYSCALL_INFO_FREGVALID(i)    (0x0100 << (i)) /* Mask for checking if some given register `i' is valid */
#define RPC_SYSCALL_INFO_FREGVALID_SHIFT 8
#define RPC_SYSCALL_INFO_FREGVALID_MASK  0x7f00



#ifdef __CC__
/* >> rpc_service(2)
 * Service RPC callbacks (user-space variant of the kernel-space `task_serve()')
 * @return:  1: At least 1 RPC callback  was serviced. (though this  may
 *              have been a kernel-level RPC that didn't actually affect
 *              user-space)
 * @return:  0: No RPC callbacks were served.
 * @return: -1: Error (s.a. `errno')
 * @throws: * : Anything (RPC callbacks may throw exceptions) */
typedef int (LIBRPC_CC *PRPC_SERVICE)(void);
#ifdef LIBRPC_WANT_PROTOTYPES
LIBRPC_DECL int LIBRPC_CC rpc_service(void);
#endif /* LIBRPC_WANT_PROTOTYPES */

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
typedef __ATTR_NONNULL((3)) int
(LIBRPC_CC *PRPC_SCHEDULE_EX)(__pid_t target, __syscall_ulong_t flags,
                              __uint8_t const *__restrict program,
                              void **arguments);
#ifdef LIBRPC_WANT_PROTOTYPES
LIBRPC_DECL __ATTR_NONNULL((3)) int LIBRPC_CC
rpc_schedule_ex(__pid_t target, __syscall_ulong_t flags,
                __uint8_t const *__restrict program,
                void **arguments);
#endif /* LIBRPC_WANT_PROTOTYPES */


/* >> rpc_schedule(3)
 * Portable wrapper for `rpc_schedule_ex()'
 * Schedule a  simple RPC  for execution  on a  given `target'  thread.
 * The scheduled RPC  assumes that  `target' has a  valid stack,  while
 * taking  a `callback'  to-be invoked,  which itself  will take `argc'
 * pointer-sized arguments  from the  variable  argument list  of  this
 * function. (When `RPC_SCHEDULE_FLAG_STATUSFUTEX' is given, `callback'
 * takes `argc - 1' arguments, with  the first variable argument  being
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
 *       When  `callback' returns, an  internal wrapper is  called that will restore
 *       registers, as  well  as  optionally restart  an  interrupted  system  call,
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
 * @param: ...:      Arguments passed to  `callback', potentially preceded  by
 *                   the status futex when the `RPC_SCHEDULE_FLAG_STATUSFUTEX'
 *                   flag was set.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
typedef __ATTR_NONNULL((3)) int
(LIBRPC_VCC *PRPC_SCHEDULE)(__pid_t target, __syscall_ulong_t flags, void (*callback)(),
                            __size_t argc, /* uintptr_t *status_futex */ /* uintptr_t ...args */...);
#ifdef LIBRPC_WANT_PROTOTYPES
LIBRPC_DECL __ATTR_NONNULL((3)) int LIBRPC_VCC
rpc_schedule(__pid_t target, __syscall_ulong_t flags, void (*callback)(),
             __size_t argc, /* uintptr_t *status_futex */ /* uintptr_t ...args */...);
#endif /* LIBRPC_WANT_PROTOTYPES */


#endif /* __CC__ */

__SYSDECL_END

#endif /* !_LIBRPC_RPC_H */
