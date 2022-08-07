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
#ifndef _KOS_ASM_RPC_H
#define _KOS_ASM_RPC_H 1

#ifndef __DEEMON__
#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>
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
 *  - The  stack used by  the below bytecode  consists of pointer-sized words,
 *    and trying to push a register that  is larger than a pointer will  cause
 *    as  many words to  be pushed/popped as  necessary, where push operations
 *    function such that the last-pushed value contains the least  significant
 *    part  of the whole value (if that whole value was interpreted as a base-
 *    2 integer of arbitrary precision), while pop works compatible with this.
 *    When an over-long register is pushed on the user-stack, the same happens
 *    and a variable number of pointer-sized words are pushed.
 *
 *  - Register indices are arch-dependent and the same as those used by CFI:
 *      i386:   One of `CFI_386_UNWIND_REGISTER_*'    (from <libunwind/cfi/i386.h>)
 *      x86_64: One of `CFI_X86_64_UNWIND_REGISTER_*' (from <libunwind/cfi/x86_64.h>)
 *
 *  - RPC  program execution starts with the first instruction, at which point
 *    the stack was set-up to contain a single element equal to what is pushed
 *    by `RPC_OP_push_dorestart'.
 *
 *  - Every  RPC program _must_  include checks regarding  a system call needing
 *    to  be restarted, or never return to  the interrupted location at all. For
 *    this purpose, the stack starts  out with containing information about  the
 *    need to restart a  system call. When a  system call has been  interrupted,
 *    then accessible registers are indicative  of where the interrupted  system
 *    call would have returned to, and the RPC program should modify the program
 *    counter to point  to a  custom landing  pad capable  of saving  registers,
 *    repeating the system call, restoring  registers, and finally returning  to
 *    where the system call would have originally returned to.
 *
 *  - Unaligned  memory access is allowed on all architectures, though if you
 *    have to resort to making use of it, you might be doing something wrong.
 *
 *  - Both register-, memory-, futex- and sigmask modifications will only  become
 *    visible  once the RPC program returns without errors (via `RPC_OP_ret'), at
 *    which  point the RPC can no longer be canceled (though can still be aborted
 *    if writes to VIO memory exist, in which case there is a chance that not all
 *    modifications are applied).
 *    During  execution, a program may arbitrarily be aborted or canceled, where
 *    the former happens when SIGKILL or SIGSTOP signals/RPCs are received while
 *    the  program is executing,  and the later when  the original sender didn't
 *    make  use of `RPC_JOIN_F_ASYNC' and themselves received an unmasked RPC or
 *    posix signal (causing the `sys_rpc_schedule(2)' to return with -EINTR).
 *    - When an RPC is canceled, it won't be restarted but will just be discarded
 *      in its entirety.
 *    - When an RPC is aborted, another attempt to execute it will be made before
 *      the next time the target thread returns to user-space.
 *
 *  - PUSH_ONTO_USER_STACK(value) works as:
 *    >> int spreg = CFI_UNWIND_REGISTER_SP(sizeof(void *));
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
#define RPC_OP_ret            0x00 /* [+0] Indicate successful completion of the RPC program. */
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
#if __SIZEOF_POINTER__ >= 8
#define RPC_OP_const8u        0x0e /* [+8] PUSH(*(u64 const *)pc); */
#define RPC_OP_const8s        0x0f /* [+8] PUSH(*(s64 const *)pc); */
#endif /* __SIZEOF_POINTER__ >= 8 */
#define RPC_OP_popregx        0x10 /* [+*] CFI_REGISTER(dwarf_decode_uleb128(&pc)) = POP(); */
/*      RPC_OP_               0x11  * ... */
#define RPC_OP_dup            0x12 /* [+0] PUSH(TOP); */
#define RPC_OP_drop           0x13 /* [+0] POP(); */
#define RPC_OP_over           0x14 /* [+0] PUSH(SECOND); */
#define RPC_OP_pick           0x15 /* [+1] PUSH(NTH(*(u8 const *)pc));  // Where operand=0 means the old TOP */
#define RPC_OP_swap           0x16 /* [+0] TOP = XCH(SECOND, TOP); */
#define RPC_OP_rot            0x17 /* [+0] a = TOP; TOP = SECOND; SECOND = THIRD; THIRD = a; */
#define RPC_OP_abs            0x19 /* [+0] a = POP(); PUSH(a < 0 ? -a : a); */
#define RPC_OP_and            0x1a /* [+0] PUSH(POP(SECOND) & POP(TOP)); */
#define RPC_OP_div            0x1b /* [+0] PUSH((signed)POP(SECOND) / (signed)POP(TOP)); */
#define RPC_OP_minus          0x1c /* [+0] PUSH(POP(SECOND) - POP(TOP)); */
#define RPC_OP_mod            0x1d /* [+0] PUSH((signed)POP(SECOND) % (signed)POP(TOP)); */
#define RPC_OP_mul            0x1e /* [+0] PUSH((signed)POP(SECOND) * (signed)POP(TOP)); */
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
#define RPC_OP_eq             0x29 /* [+0] PUSH(POP(SECOND) == POP(TOP)); */
#define RPC_OP_ge             0x2a /* [+0] PUSH((signed)POP(SECOND) >= (signed)POP(TOP)); */
#define RPC_OP_gt             0x2b /* [+0] PUSH((signed)POP(SECOND) >  (signed)POP(TOP)); */
#define RPC_OP_le             0x2c /* [+0] PUSH((signed)POP(SECOND) <= (signed)POP(TOP)); */
#define RPC_OP_lt             0x2d /* [+0] PUSH((signed)POP(SECOND) <  (signed)POP(TOP)); */
#define RPC_OP_ne             0x2e /* [+0] PUSH(POP(SECOND) != POP(TOP)); */
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
#define RPC_OP_push_reason    0xa0 /* [+0] PUSH(user_rpc_reason); */
#define RPC_OP_push_dorestart 0xa1 /* [+0] PUSH(user_rpc_reason == RPC_REASONCTX_SYSCALL ? 1 : 0); */
#define RPC_OP_push_issyscall 0xa2 /* [+0] PUSH(user_rpc_reason in [RPC_REASONCTX_SYSCALL,RPC_REASONCTX_SYSINT] ? 1 : 0); */
#define RPC_OP_push_sc_info   0xa3 /* [+1] index = *pc++; PUSH(((uintptr_t *)sc_info)[index]);       // Illegal when `user_rpc_reason !in [RPC_REASONCTX_SYSCALL,RPC_REASONCTX_SYSINT]' */
#define RPC_OP_sppush_sc_info 0xa4 /* [+0] Push the entire `sc_info' descriptor onto the user stack. // Illegal when `user_rpc_reason !in [RPC_REASONCTX_SYSCALL,RPC_REASONCTX_SYSINT]' */
#define RPC_OP_push_param     0xa5 /* [+1] index = *pc++; PUSH(params[index]); // `params' is an argument */
#define RPC_OP_sigblock       0xa6 /* [+0] sigset_t s; sigemptyset(&s); sigaddset(&s, POP()); sigprocmask(SIG_BLOCK, &s, NULL); */
#define RPC_OP_futex_wake     0xa7 /* [+0] count = POP(); addr = POP(); futex_wake(addr, count); */
#define RPC_OP_nbra           0xa8 /* [+2] off = *(s16 const *)pc; pc += 2; if (POP() == 0) pc += off; */
#define RPC_OP_push_sigmask_word 0xa9 /* [+1] index = *pc++; sigset_t s; sigprocmask(SIG_SETMASK, NULL, &s); PUSH(s.__val[index]); */
#define RPC_OP_uge            0xaa /* [+0] PUSH((unsigned)POP(SECOND) >= (unsigned)POP(TOP)); */
#define RPC_OP_ugt            0xab /* [+0] PUSH((unsigned)POP(SECOND) >  (unsigned)POP(TOP)); */
#define RPC_OP_ule            0xac /* [+0] PUSH((unsigned)POP(SECOND) <= (unsigned)POP(TOP)); */
#define RPC_OP_ult            0xad /* [+0] PUSH((unsigned)POP(SECOND) <  (unsigned)POP(TOP)); */
#define RPC_OP_sppush_sigmask 0xae /* [+2] sigsetsz = *(*(u16 **)&pc)++; sigset_t s; sigprocmask(SIG_SETMASK, NULL, &s); PUSH_ONTO_USER_STACK(&s, sigsetsz); */
#define RPC_OP_push_signal    0xaf /* [+0] PUSH(_RPC_GETSIGNO(RPC_MODE)); */
#define RPC_OP_widenz         0xb0 /* [+1] Zero-extend a [OPERAND]-sized integer to full width */
#define RPC_OP_widens         0xb1 /* [+1] Sign-extend a [OPERAND]-sized integer to full width */
/*      RPC_OP_               0xb2  * ... */
/*      RPC_OP_               ...   * ... */
/*      RPC_OP_               0xdf  * ... */
#define RPC_OP_lo_arch        0xe0 /* First arch-specific opcode */
#define RPC_OP_hi_arch        0xff /* Last arch-specific opcode */


/************************************************************************/
/* Arch-specific opcodes                                                */
/************************************************************************/
/* X86 */
#define RPC_OP_x86_push_is32bit    0xe0 /* [+0] i386/x86_64: push  `1' if target  thread is 32-bit;  push `0' if 64-bit.
                                         * Since register numbers (and the  operand of `RPC_OP_sppush_const') is  always
                                         * dependent on the architecture of the _target_ thread (not the sender thread),
                                         * this instruction can be used to write  portable RPC programs that can be  run
                                         * both in the context of a 32-bit and 64-bit target thread. */
/*      RPC_OP_                    0xe1  */
/*      RPC_OP_                    0xe2  */
/*      RPC_OP_                    0xe3  */
#define RPC_OP_386_pushreg_fsbase  0xe4 /* [+0] i386: Push the value of %fs.base */
#define RPC_OP_386_pushreg_gsbase  0xe5 /* [+0] i386: Push the value of %gs.base */
#define RPC_OP_386_popreg_fsbase   0xe6 /* [+0] i386: Pop stack-top into %fs.base */
#define RPC_OP_386_popreg_gsbase   0xe7 /* [+0] i386: Pop stack-top into %gs.base */

/* ARM */
#define RPC_OP_arm_pushreg_tlsbase 0xe0 /* [+0] arm: Push value of user-space tls-base address */
#define RPC_OP_arm_popreg_tlsbase  0xe1 /* [+0] arm: Pop stack-top into user-space tls-base address */
/*========================================*/



#ifdef __KERNEL__
/************************************************************************/
/* RPC context flags */

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
 *       to the RPC function is always either `RPC_REASONCTX_ASYNC_KERN' for kernel
 *       return locations, or `RPC_REASONCTX_SYSRET'  for user-space ones, and  are
 *       always  executed with preemption  disabled. (Note that  all other RPCs are
 *       always executed with preemption enabled)
 *
 *  - RPC_SYNCMODE_F_USER:
 *  - RPC_PRIORITY_F_HIGH:
 *       These flags are accepted and operates as documented below
 *
 *  - RPC_SYNCMODE_F_REQUIRE_SC:
 *       These flags are NOT allowed (but note that `RPC_SYNCMODE_F_USER' is,
 *       which shares its  numerical value with  `RPC_SYNCMODE_F_REQUIRE_SC')
 *
 *  - RPC_SYNCMODE_F_REQUIRE_CP:
 *  - RPC_SYSRESTART_F_AUTO:
 *  - RPC_SYSRESTART_F_DONT:
 *       These flags are NOT allowed (use of it results in kernel panic)
 */
#define RPC_CONTEXT_KERN      0x00080000

/* Flag for use with `RPC_CONTEXT_KERN': the associated function will never
 * throw an exception and is therefor safe to invoke from `task_serve_nx()' */
#define RPC_CONTEXT_NOEXCEPT  0x00040000

/* Flag for use WITHOUT `RPC_CONTEXT_KERN': the associated item is a posix signal. */
#define RPC_CONTEXT_SIGNAL    0x00040000

/* Internally used: RPC is currently inactive. */
#define _RPC_CONTEXT_INACTIVE 0x00020000

/* Flag for use with `RPC_CONTEXT_KERN':
 *  - Don't do `pending_rpc_free()' to free this RPC
 *  - May  only  be  used  with  `RPC_CONTEXT_KERN'!
 *  - Pass the `struct pending_rpc' instead of `k_cookie'
 *  - When set,  the internal  RPC system  will never  make any  further
 *    accesses to the `struct pending_rpc' after the associated `k_func'
 *    is invoked.
 *  - Using  this flag, it  falls upon `k_func'  to free the associated
 *    `struct pending_rpc', but this also makes it possible to allocate
 *    a larger structure to pass more  than one cookie argument to  the
 *    RPC function.
 *  - When this flag  is set, no  fields of `struct pending_rpc'  beyond
 *    `pr_kern.k_func' are ever accessed, meaning that the struct's size
 *    becomes `offsetafter(struct pending_rpc, pr_kern.k_func)'. */
#define _RPC_CONTEXT_DONTFREE 0x00010000
/************************************************************************/
#endif /* __KERNEL__ */



/************************************************************************/
/* RPC Signal encoding                                                  */
#define RPC_SIGNO_MASK   0x00ff  /* Mask for the posix signal number which mustn't be masked for this RPC to be received.
                                  * When  set  to  `0', the  kernel  will fill  in  `SIGRPC' before  scheduling  the RPC. */
#define RPC_SIGNO(signo) (signo) /* Use the given `signo' to determine when/if the RPC may be delivered. */
#define _RPC_GETSIGNO(x) ((x) & RPC_SIGNO_MASK)
/************************************************************************/



/************************************************************************/
/* RPC synchronization flags */
#define RPC_SYNCMODE_F_ALLOW_ASYNC 0x0100 /* FLAG: Allow delivery to threads currently in user-space. */
#define RPC_SYNCMODE_F_REQUIRE_SC  0x0200 /* FLAG: Require that the interrupt is the result of a system call being made.
                                           * When not set, non-RPC_SYNCMODE_F_ALLOW_ASYNC RPCs  can still be handled  as
                                           * the result of a blocking  memory access (e.g. one  that needs to read  from
                                           * disk) */
#define RPC_SYNCMODE_F_REQUIRE_CP  0x0400 /* FLAG: When interrupting a system call, only handle if the system call is a cancellation point. */
#ifdef __KERNEL__
#define RPC_SYNCMODE_F_USER   0x0200 /* For use with `RPC_CONTEXT_KERN': Have `task_serve()' handle the RPC
                                      * as though the `RPC_CONTEXT_KERN' wasn't set. As a consequence, RPCs
                                      * with this flag will only ever be invoked with reasons:
                                      *   - RPC_REASONCTX_SYSRET     (Return to user-space location)
                                      *   - RPC_REASONCTX_SYSCALL    (syscall was unwound)
                                      *   - RPC_REASONCTX_INTERRUPT  (Interrupt was unwound)
                                      *   - RPC_REASONCTX_SHUTDOWN   (Thread is exiting) */
#define RPC_SYNCMODE_F_SYSRET 0x0400 /* Combine with `RPC_SYNCMODE_F_USER': Service the RPC in the sysret path. */
#endif /* __KERNEL__ */


/* RPC synchronization options */

/* RPC  may be executed at any point while the target thread
 * is running in user-space, so-long as SIGRPC isn't masked.
 * While the thread is in kernel-space, behavior is the same
 * as for `RPC_SYNCMODE_SYNC'. As such, this option can also
 * be seen as a flag "ALLOW_DELIVERLY_WHILE_IN_USERSPACE"
 *
 * Handled when (if `RPC_SIGNO(signo=SIGRPC)' isn't masked):
 *   - As soon as possible,  following the same semantics  as
 *     a normal POSIX signal (~ala signal(2) + kill(2)) does.
 *   - This also includes the case where the target thread is
 *     currently in kernel-space, in which case the RPC  will
 *     be executed as soon as a return to user-space is made,
 *     which  is  guarantied  to happen  without  any further
 *     intervention by means of having an active system  call
 *     return with -EINTR, or having it be restarted once the
 *     RPC function returns.
 *     Restart behavior can further be configured by use of
 *     `RPC_SYSRESTART_*' options. */
#define RPC_SYNCMODE_ASYNC RPC_SYNCMODE_F_ALLOW_ASYNC

/* RPC  may only be executed when the target thread is making
 * a system call that  blocks or is otherwise  interruptible,
 * after which that call will be interrupted, the RPC will be
 * executed, and the system call (may) be restarted.
 *
 * Handled when (if `RPC_SIGNO(signo=SIGRPC)' isn't masked):
 *   - Any system call makes a call to `task_serve()'
 *   - _NOT_ handled while  the thread is  in user-space, or  is
 *     only performing operations  that don't  block. Note  that
 *     the exact definition of what is/isn't consider a blocking
 *     operation here (intentionally) isn't well defined.
 *   - If more well-defined behavior is needed, consider making
 *     use of `RPC_SYNCMODE_CP' instead. */
#define RPC_SYNCMODE_SYNC RPC_SYNCMODE_F_REQUIRE_SC

/* RPC is only handled when  interrupting a system call  that
 * has been marked  as a cancellation  point. Otherwise,  the
 * RPC will be marked as inactive until the end of the system
 * call,  such that  it's next  chance at  being handled only
 * comes about the next time a (different) system call  makes
 * a call to `task_serve()'
 *
 * Handled when (if `RPC_SIGNO(signo=SIGRPC)' isn't masked):
 *   - A system call marked as [cp] makes a call to `task_serve()'
 *     IOW: A cancellation point does a blocking operation
 *   - The `sys_rpc_serve(2)' system call is invoked
 *     IOW: You make a call to `pthread_testcancel(3)' */
#define RPC_SYNCMODE_CP (RPC_SYNCMODE_F_REQUIRE_SC | RPC_SYNCMODE_F_REQUIRE_CP)
/************************************************************************/




/************************************************************************/
/* RPC system call restart flags */
#define RPC_SYSRESTART_F_AUTO 0x1000 /* Same as `SA_RESTART' for signal handlers */

/* RPC system call  restart options.  These only apply  to RPCs  delivered
 * while the target thread is in kernel-space and executing a system  call
 * marked as [cp] and something other than [restart(must)], and the system
 * call made a call to `task_serve()' internally. */
#define RPC_SYSRESTART_NORMAL  0x0000                /* [posix:!SA_RESTART] SYSCALL_RESTART_MODE_MUST (default) */
#define RPC_SYSRESTART_RESTART RPC_SYSRESTART_F_AUTO /* [posix: SA_RESTART] SYSCALL_RESTART_MODE_MUST+SYSCALL_RESTART_MODE_AUTO */
/************************************************************************/




/************************************************************************/
/* RPC priority flags */
#define RPC_PRIORITY_F_HIGH 0x4000 /* Try to gift  the target  thread the  remainder
                                    * of  the  calling  thread's  current   quantum.
                                    * Semantically meaningless if `RPC_JOIN_F_ASYNC'
                                    * isn't being used as well. */

/* RPC priority options */
#define RPC_PRIORITY_NORMAL 0x0000              /* Normal priority (default) */
#define RPC_PRIORITY_HIGH   RPC_PRIORITY_F_HIGH /* High priority (try to  gift the target thread  the
                                                 * remainder of the calling thread's current quantum) */
/************************************************************************/




/************************************************************************/
/* RPC domain flags (these _never_ appear in `struct pending_rpc::pr_flags',
 * but  are simply used  by the `sys_rpc_schedule(2)'  system call to select
 * the list into which to insert the RPC descriptor) */
#define RPC_DOMAIN_F_PROC 0x0800 /* Send the RPC to a process as a whole, rather than a specific thread.
                                  * In  this case, `target_tid' is the TID  of any thread of the process
                                  * to which to send the RPC, which  will then be served by some  random
                                  * thread within that process. */

/* RPC domain options */
#define RPC_DOMAIN_THREAD  0x0000            /* Send to a specific thread (default) */
#define RPC_DOMAIN_PROCESS RPC_DOMAIN_F_PROC /* Send to a process (and handle with an arbitrary thread) */
/************************************************************************/




/************************************************************************/
/* RPC join flags (these _never_ appear in `struct pending_rpc::pr_flags',
 * but  are simply used  by the `sys_rpc_schedule(2)'  system call to wait
 * for the RPC program to finish termination) */
#define RPC_JOIN_F_ASYNC 0x8000 /* Don't wait for the RPC program to finish. Instead,  the
                                 * program is allowed to execute asynchronously, though if
                                 * this option is used, any errors relating to the program
                                 * possibly failing to execute are silently discarded.
                                 *
                                 * Unless  this flag is passed, `sys_rpc_schedule(2)' can
                                 * return with -EINTR, in which case the RPC was  aborted
                                 * or was never started. When this flag is given however,
                                 * the  RPC may never end up being executed due to target
                                 * terminating without ever serving RPCs ever again. */

/* RPC join options */
#define RPC_JOIN_WAITFOR 0x0000           /* Wait for the RPC program to finish. (default)
                                           * NOTE: This  does _NOT_ affect  an RPC function (as
                                           * passed to  `rpc_exec(3)'), but  only the  internal
                                           * program used to push that function onto the target
                                           * thread's stack.
                                           *
                                           * NOTE: When sending an RPC to one's own thread  (or
                                           *       process),  this option will cause the RPC to
                                           *       be invoked with `RPC_REASONCTX_SYSINT', even
                                           *       though `sys_rpc_schedule(2)' will return  to
                                           *       indicate success, rather than INTERRUPT.
                                           */
#define RPC_JOIN_ASYNC   RPC_JOIN_F_ASYNC /* Let the RPC program run asynchronously. */
/************************************************************************/






/************************************************************************/
/* RPC program limits                                                   */
/************************************************************************/
#define RPC_PROG_PARAMS_MAX 255    /* Max # of parameters which may be passed to `rpc_schedule(2)' */
#define RPC_PROG_MEMORY_MAX 0xffff /* Max # of unique byte addresses a single RPC program may access */
#define RPC_PROG_STACK_MAX  255    /* Max # of elements which may exist on an RPC program stack */
#define RPC_PROG_FUTEX_MAX  255    /* Max # of futex objects which a single RPC program may access */
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



/************************************************************************/
/* RPC service context codes                                            */
/************************************************************************/
#ifdef __KERNEL__
#define RPC_REASONCTX_SYSRET     0x0000 /* Return to arbitrary user-space location. */
#define RPC_REASONCTX_SYNC       0x0001 /* RPC is being handled from within `task_serve()' */
#define RPC_REASONCTX_SYSCALL    0x0002 /* A syscall called `task_serve()' and  an unwind was forced.  The
                                         * syscall will be restarted unless `RPC_REASONCTX_SYSRET' is set. */
#define RPC_REASONCTX_INTERRUPT  0x0003 /* A non-syscall interrupt called `task_serve()' and an unwind was forced.
                                         * The interrupt will be  restarted unless `RPC_REASONCTX_SYSRET' is  set. */
#define RPC_REASONCTX_ASYNC_KERN 0x0004 /* Kernel-space was interrupted asynchronously. (in this case,
                                         * preemption is unconditionally  disabled and  should not  be
                                         * enabled by the RPC callback) */
#define RPC_REASONCTX_SHUTDOWN   0x0005 /* RPC is invoked because the thread is exiting. */
#define _RPC_REASONCTX_ASYNC     0x0000 /* User-space context: `RPC_REASONCTX_ASYNC' */
#define _RPC_REASONCTX_SYNC      0x0001 /* User-space context: `RPC_REASONCTX_SYNC' */
#define _RPC_REASONCTX_SYSCALL   0x0002 /* User-space context: `RPC_REASONCTX_SYSCALL' */
#define _RPC_REASONCTX_SYSINT    0x0003 /* User-space context: `RPC_REASONCTX_SYSINT' */
#else /* __KERNEL__ */
#define RPC_REASONCTX_ASYNC      0x0000 /* Asynchronous execution in user-space. */
#define RPC_REASONCTX_SYNC       0x0001 /* An interrupt was halted, or RPC is handled as a non-primary callback with
                                         * the primary (which your RPC will eventually return to) being called  with
                                         * either `RPC_REASONCTX_SYSCALL' or `RPC_REASONCTX_SYSINT' */
#define RPC_REASONCTX_SYSCALL    0x0002 /* A syscall was halted, and will be restarted after the RPC returns. */
#define RPC_REASONCTX_SYSINT     0x0003 /* A syscall was halted, and will not be restarted after the RPC returns. */
#endif /* !__KERNEL__ */


#endif /* !_KOS_ASM_RPC_H */
