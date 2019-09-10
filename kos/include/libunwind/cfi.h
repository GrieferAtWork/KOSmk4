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
#ifndef _LIBUNWIND_CFI_H
#define _LIBUNWIND_CFI_H 1

#include "api.h"

#include <hybrid/host.h>

#include <bits/types.h>

#if defined(__x86_64__)
#include "cfi/x86_64.h"
#elif defined(__i386__)
#include "cfi/i386.h"
#else /* Arch... */
#error "Unsupported architecture"
#endif /* !Arch... */


#ifndef CFI_UNWIND_COMMON_REGISTER_COUNT
#define CFI_UNWIND_NO_COMMON_UNCOMMON_REGISTERS 1
#define CFI_UNWIND_COMMON_REGISTER_COUNT   CFI_UNWIND_REGISTER_COUNT
#define CFI_UNWIND_UNCOMMON_REGISTER_COUNT 0
#define CFI_UNWIND_COMMON_REGISTER_SP      CFI_UNWIND_REGISTER_SP
#define cfi_unwind_register_dw2common(dw_regno)      (dw_regno)
#define cfi_unwind_register_dw2uncommon(dw_regno)    0
#define cfi_unwind_register_common2dw(com_regno)     (com_regno)
#define cfi_unwind_register_uncommon2dw(uncom_regno) CFI_UNWIND_REGISTER_COUNT
#endif /* !CFI_UNWIND_COMMON_REGISTER_COUNT */

#if (defined(CFI_UNWIND_COMMON_REGISTER_SP) + \
     defined(CFI_UNWIND_UNCOMMON_REGISTER_SP)) != 1
#error "Need exactly one of `CFI_UNWIND_COMMON_REGISTER_SP' or `CFI_UNWIND_UNCOMMON_REGISTER_SP'"
#endif

#ifndef CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT
#define CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS 1
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_COUNT   CFI_UNWIND_COMMON_REGISTER_COUNT
#define CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_COUNT CFI_UNWIND_UNCOMMON_REGISTER_COUNT
#ifdef CFI_UNWIND_COMMON_REGISTER_SP
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP      CFI_UNWIND_COMMON_REGISTER_SP
#else /* CFI_UNWIND_COMMON_REGISTER_SP */
#define CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_SP    CFI_UNWIND_UNCOMMON_REGISTER_SP
#endif /* !CFI_UNWIND_COMMON_REGISTER_SP */
#define cfi_unwind_sigframe_register_dw2common      cfi_unwind_register_dw2common
#define cfi_unwind_sigframe_register_dw2uncommon    cfi_unwind_register_dw2uncommon
#define cfi_unwind_sigframe_register_common2dw      cfi_unwind_register_common2dw
#define cfi_unwind_sigframe_register_uncommon2dw    cfi_unwind_register_uncommon2dw
#endif /* !CFI_UNWIND_COMMON_REGISTER_COUNT */

#if (defined(CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP) + \
     defined(CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_SP)) != 1
#error "Need exactly one of `CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP' or `CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_SP'"
#endif





/* NOTE: Embedding CFI code that is only meant for the eyes of KOS:
 *    .cfi_escape DW_OP_skip, 3, 0
 *    .cfi_escape 'K', 'O', 'S'
 *    .cfi_escape DW_OP_skip, n, m
 *    .cfi_escape ...  // This code (with a size of n + (m << 8)) is only executed in KOS
 */

#define DW_OP_addr                  0x03 /* [+4|8] +uintptr_t constant address */
#define DW_OP_deref                 0x06 /* [+0]   TOP = *(uintptr_t *)TOP; */
#define DW_OP_const1u               0x08 /* [+1]   PUSH(*(u8 *)pc); */
#define DW_OP_const1s               0x09 /* [+1]   PUSH(*(s8 *)pc); */
#define DW_OP_const2u               0x0a /* [+2]   PUSH(*(u16 *)pc); */
#define DW_OP_const2s               0x0b /* [+2]   PUSH(*(s16 *)pc); */
#define DW_OP_const4u               0x0c /* [+4]   PUSH(*(u32 *)pc); */
#define DW_OP_const4s               0x0d /* [+4]   PUSH(*(s32 *)pc); */
#define DW_OP_const8u               0x0e /* [+8]   PUSH(*(u64 *)pc); */
#define DW_OP_const8s               0x0f /* [+8]   PUSH(*(s64 *)pc); */
#define DW_OP_constu                0x10 /* [+*]   PUSH(dwarf_decode_uleb128(&pc)); */
#define DW_OP_consts                0x11 /* [+*]   PUSH(dwarf_decode_sleb128(&pc)); */
#define DW_OP_dup                   0x12 /* [+0]   PUSH(TOP); */
#define DW_OP_drop                  0x13 /* [+0]   POP(); */
#define DW_OP_over                  0x14 /* [+0]   PUSH(SECOND); */
#define DW_OP_pick                  0x15 /* [+1]   PUSH(NTH(*(u8 *)pc));  // Where operand=0 is the old TOP */
#define DW_OP_swap                  0x16 /* [+0]   TOP = XCH(SECOND, TOP); */
#define DW_OP_rot                   0x17 /* [+0]   a = TOP; TOP = SECOND; SECOND = THIRD; THIRD = a; */
#define DW_OP_xderef                0x18 /* [+0]   off = POP(); id = POP(); PUSH(*(uintptr_t *)id:off) */
#define DW_OP_abs                   0x19 /* [+0]   a = POP(); PUSH(a < 0 ? -a : a); */
#define DW_OP_and                   0x1a /* [+0]   PUSH(POP(SECOND) & POP(TOP)); */
#define DW_OP_div                   0x1b /* [+0]   PUSH(POP(SECOND) / POP(TOP)); */
#define DW_OP_minus                 0x1c /* [+0]   PUSH(POP(SECOND) - POP(TOP)); */
#define DW_OP_mod                   0x1d /* [+0]   PUSH(POP(SECOND) % POP(TOP)); */
#define DW_OP_mul                   0x1e /* [+0]   PUSH(POP(SECOND) * POP(TOP)); */
#define DW_OP_neg                   0x1f /* [+0]   PUSH(-POP()); */
#define DW_OP_not                   0x20 /* [+0]   PUSH(~POP()); */
#define DW_OP_or                    0x21 /* [+0]   PUSH(POP(SECOND) | POP(TOP)); */
#define DW_OP_plus                  0x22 /* [+0]   PUSH(POP(SECOND) + POP(TOP)); */
#define DW_OP_plus_uconst           0x23 /* [+*]   PUSH(POP(TOP) + dwarf_decode_uleb128(&pc)); */
#define DW_OP_shl                   0x24 /* [+0]   PUSH(POP(SECOND) << POP(TOP)); */
#define DW_OP_shr                   0x25 /* [+0]   PUSH((unsigned)POP(SECOND) >> POP(TOP)); */
#define DW_OP_shra                  0x26 /* [+0]   PUSH((signed)POP(SECOND) >> POP(TOP)); */
#define DW_OP_xor                   0x27 /* [+0]   PUSH(POP(SECOND) ^ POP(TOP)); */
#define DW_OP_bra                   0x28 /* [+2]   off = *(s16 *)pc; pc += 2; if (POP() != 0) pc += off; */
#define DW_OP_eq                    0x29 /* [+0]   PUSH((signed)POP(SECOND) == (signed)POP(TOP)); */
#define DW_OP_ge                    0x2a /* [+0]   PUSH((signed)POP(SECOND) >= (signed)POP(TOP)); */
#define DW_OP_gt                    0x2b /* [+0]   PUSH((signed)POP(SECOND) >  (signed)POP(TOP)); */
#define DW_OP_le                    0x2c /* [+0]   PUSH((signed)POP(SECOND) <= (signed)POP(TOP)); */
#define DW_OP_lt                    0x2d /* [+0]   PUSH((signed)POP(SECOND) <  (signed)POP(TOP)); */
#define DW_OP_ne                    0x2e /* [+0]   PUSH((signed)POP(SECOND) != (signed)POP(TOP)); */
#define DW_OP_skip                  0x2f /* [+2]   off = *(s16 *)pc; pc += 2; pc += off; */
#define DW_OP_lit0                  0x30 /* [+0]   PUSH(0); */
#define DW_OP_lit1                  0x31 /* [+0]   PUSH(1); */
#define DW_OP_lit2                  0x32 /* [+0]   PUSH(2); */
#define DW_OP_lit3                  0x33 /* [+0]   PUSH(3); */
#define DW_OP_lit4                  0x34 /* [+0]   PUSH(4); */
#define DW_OP_lit5                  0x35 /* [+0]   PUSH(5); */
#define DW_OP_lit6                  0x36 /* [+0]   PUSH(6); */
#define DW_OP_lit7                  0x37 /* [+0]   PUSH(7); */
#define DW_OP_lit8                  0x38 /* [+0]   PUSH(8); */
#define DW_OP_lit9                  0x39 /* [+0]   PUSH(9); */
#define DW_OP_lit10                 0x3a /* [+0]   PUSH(10); */
#define DW_OP_lit11                 0x3b /* [+0]   PUSH(11); */
#define DW_OP_lit12                 0x3c /* [+0]   PUSH(12); */
#define DW_OP_lit13                 0x3d /* [+0]   PUSH(13); */
#define DW_OP_lit14                 0x3e /* [+0]   PUSH(14); */
#define DW_OP_lit15                 0x3f /* [+0]   PUSH(15); */
#define DW_OP_lit16                 0x40 /* [+0]   PUSH(16); */
#define DW_OP_lit17                 0x41 /* [+0]   PUSH(17); */
#define DW_OP_lit18                 0x42 /* [+0]   PUSH(18); */
#define DW_OP_lit19                 0x43 /* [+0]   PUSH(19); */
#define DW_OP_lit20                 0x44 /* [+0]   PUSH(20); */
#define DW_OP_lit21                 0x45 /* [+0]   PUSH(21); */
#define DW_OP_lit22                 0x46 /* [+0]   PUSH(22); */
#define DW_OP_lit23                 0x47 /* [+0]   PUSH(23); */
#define DW_OP_lit24                 0x48 /* [+0]   PUSH(24); */
#define DW_OP_lit25                 0x49 /* [+0]   PUSH(25); */
#define DW_OP_lit26                 0x4a /* [+0]   PUSH(26); */
#define DW_OP_lit27                 0x4b /* [+0]   PUSH(27); */
#define DW_OP_lit28                 0x4c /* [+0]   PUSH(28); */
#define DW_OP_lit29                 0x4d /* [+0]   PUSH(29); */
#define DW_OP_lit30                 0x4e /* [+0]   PUSH(30); */
#define DW_OP_lit31                 0x4f /* [+0]   PUSH(31); */
#define DW_OP_reg0                  0x50 /* [+0]   PUSH(GET_CONTEXT_REGISTER(0)); */
#define DW_OP_reg1                  0x51 /* [+0]   PUSH(GET_CONTEXT_REGISTER(1)); */
#define DW_OP_reg2                  0x52 /* [+0]   PUSH(GET_CONTEXT_REGISTER(2)); */
#define DW_OP_reg3                  0x53 /* [+0]   PUSH(GET_CONTEXT_REGISTER(3)); */
#define DW_OP_reg4                  0x54 /* [+0]   PUSH(GET_CONTEXT_REGISTER(4)); */
#define DW_OP_reg5                  0x55 /* [+0]   PUSH(GET_CONTEXT_REGISTER(5)); */
#define DW_OP_reg6                  0x56 /* [+0]   PUSH(GET_CONTEXT_REGISTER(6)); */
#define DW_OP_reg7                  0x57 /* [+0]   PUSH(GET_CONTEXT_REGISTER(7)); */
#define DW_OP_reg8                  0x58 /* [+0]   PUSH(GET_CONTEXT_REGISTER(8)); */
#define DW_OP_reg9                  0x59 /* [+0]   PUSH(GET_CONTEXT_REGISTER(9)); */
#define DW_OP_reg10                 0x5a /* [+0]   PUSH(GET_CONTEXT_REGISTER(10)); */
#define DW_OP_reg11                 0x5b /* [+0]   PUSH(GET_CONTEXT_REGISTER(11)); */
#define DW_OP_reg12                 0x5c /* [+0]   PUSH(GET_CONTEXT_REGISTER(12)); */
#define DW_OP_reg13                 0x5d /* [+0]   PUSH(GET_CONTEXT_REGISTER(13)); */
#define DW_OP_reg14                 0x5e /* [+0]   PUSH(GET_CONTEXT_REGISTER(14)); */
#define DW_OP_reg15                 0x5f /* [+0]   PUSH(GET_CONTEXT_REGISTER(15)); */
#define DW_OP_reg16                 0x60 /* [+0]   PUSH(GET_CONTEXT_REGISTER(16)); */
#define DW_OP_reg17                 0x61 /* [+0]   PUSH(GET_CONTEXT_REGISTER(17)); */
#define DW_OP_reg18                 0x62 /* [+0]   PUSH(GET_CONTEXT_REGISTER(18)); */
#define DW_OP_reg19                 0x63 /* [+0]   PUSH(GET_CONTEXT_REGISTER(19)); */
#define DW_OP_reg20                 0x64 /* [+0]   PUSH(GET_CONTEXT_REGISTER(20)); */
#define DW_OP_reg21                 0x65 /* [+0]   PUSH(GET_CONTEXT_REGISTER(21)); */
#define DW_OP_reg22                 0x66 /* [+0]   PUSH(GET_CONTEXT_REGISTER(22)); */
#define DW_OP_reg23                 0x67 /* [+0]   PUSH(GET_CONTEXT_REGISTER(23)); */
#define DW_OP_reg24                 0x68 /* [+0]   PUSH(GET_CONTEXT_REGISTER(24)); */
#define DW_OP_reg25                 0x69 /* [+0]   PUSH(GET_CONTEXT_REGISTER(25)); */
#define DW_OP_reg26                 0x6a /* [+0]   PUSH(GET_CONTEXT_REGISTER(26)); */
#define DW_OP_reg27                 0x6b /* [+0]   PUSH(GET_CONTEXT_REGISTER(27)); */
#define DW_OP_reg28                 0x6c /* [+0]   PUSH(GET_CONTEXT_REGISTER(28)); */
#define DW_OP_reg29                 0x6d /* [+0]   PUSH(GET_CONTEXT_REGISTER(29)); */
#define DW_OP_reg30                 0x6e /* [+0]   PUSH(GET_CONTEXT_REGISTER(30)); */
#define DW_OP_reg31                 0x6f /* [+0]   PUSH(GET_CONTEXT_REGISTER(31)); */
#define DW_OP_breg0                 0x70 /* [+*]   PUSH(GET_CONTEXT_REGISTER(0) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg1                 0x71 /* [+*]   PUSH(GET_CONTEXT_REGISTER(1) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg2                 0x72 /* [+*]   PUSH(GET_CONTEXT_REGISTER(2) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg3                 0x73 /* [+*]   PUSH(GET_CONTEXT_REGISTER(3) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg4                 0x74 /* [+*]   PUSH(GET_CONTEXT_REGISTER(4) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg5                 0x75 /* [+*]   PUSH(GET_CONTEXT_REGISTER(5) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg6                 0x76 /* [+*]   PUSH(GET_CONTEXT_REGISTER(6) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg7                 0x77 /* [+*]   PUSH(GET_CONTEXT_REGISTER(7) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg8                 0x78 /* [+*]   PUSH(GET_CONTEXT_REGISTER(8) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg9                 0x79 /* [+*]   PUSH(GET_CONTEXT_REGISTER(9) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg10                0x7a /* [+*]   PUSH(GET_CONTEXT_REGISTER(10) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg11                0x7b /* [+*]   PUSH(GET_CONTEXT_REGISTER(11) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg12                0x7c /* [+*]   PUSH(GET_CONTEXT_REGISTER(12) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg13                0x7d /* [+*]   PUSH(GET_CONTEXT_REGISTER(13) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg14                0x7e /* [+*]   PUSH(GET_CONTEXT_REGISTER(14) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg15                0x7f /* [+*]   PUSH(GET_CONTEXT_REGISTER(15) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg16                0x80 /* [+*]   PUSH(GET_CONTEXT_REGISTER(16) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg17                0x81 /* [+*]   PUSH(GET_CONTEXT_REGISTER(17) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg18                0x82 /* [+*]   PUSH(GET_CONTEXT_REGISTER(18) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg19                0x83 /* [+*]   PUSH(GET_CONTEXT_REGISTER(19) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg20                0x84 /* [+*]   PUSH(GET_CONTEXT_REGISTER(20) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg21                0x85 /* [+*]   PUSH(GET_CONTEXT_REGISTER(21) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg22                0x86 /* [+*]   PUSH(GET_CONTEXT_REGISTER(22) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg23                0x87 /* [+*]   PUSH(GET_CONTEXT_REGISTER(23) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg24                0x88 /* [+*]   PUSH(GET_CONTEXT_REGISTER(24) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg25                0x89 /* [+*]   PUSH(GET_CONTEXT_REGISTER(25) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg26                0x8a /* [+*]   PUSH(GET_CONTEXT_REGISTER(26) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg27                0x8b /* [+*]   PUSH(GET_CONTEXT_REGISTER(27) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg28                0x8c /* [+*]   PUSH(GET_CONTEXT_REGISTER(28) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg29                0x8d /* [+*]   PUSH(GET_CONTEXT_REGISTER(29) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg30                0x8e /* [+*]   PUSH(GET_CONTEXT_REGISTER(30) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg31                0x8f /* [+*]   PUSH(GET_CONTEXT_REGISTER(31) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_regx                  0x90 /* [+*]   PUSH(GET_CONTEXT_REGISTER(dwarf_decode_uleb128(&pc))); */
#define DW_OP_fbreg                 0x91 /* [+*]   PUSH(EVAL(CURRENT_FUNCTION.DW_AT_frame_base) + dwarf_decode_sleb128(&pc)) */
#define DW_OP_bregx                 0x92 /* [+*]   PUSH(GET_CONTEXT_REGISTER(dwarf_decode_uleb128(&pc)) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_piece                 0x93 /* [+*]   num_bytes = dwarf_decode_uleb128(&pc); WRITE_RESULT(POP(), num_bytes * 8); // Assign TOP to `num_bytes' of the variable's value. */
#define DW_OP_deref_size            0x94 /* [+1]   n = *(u8 *)pc; pc += 1; p = POP(); PUSH(n == 1 ? *(u8 *)p : n == 2 ? *(u16 *)p : n == 4 ? *(u32 *)p : n == 8 ? *(u64 *)p : UNDEFINED); */
#define DW_OP_xderef_size           0x95 /* [+1]   n = *(u8 *)pc; pc += 1; p = POP(); id = POP(); PUSH(n == 1 ? *(u8 *)id:p : n == 2 ? *(u16 *)id:p : n == 4 ? *(u32 *)id:p : n == 8 ? *(u64 *)id:p : UNDEFINED); */
#define DW_OP_nop                   0x96 /* [+0]   Do nothing */
#define DW_OP_push_object_address   0x97 /* [+0]   Push the value of `sm_objaddr' */
#define DW_OP_call2                 0x98 /* [+2]   Call another DW expression (the operator is a 2-byte unsigned offset from .debug_info) */
#define DW_OP_call4                 0x99 /* [+4]   Call another DW expression (the operator is a 4-byte unsigned offset from .debug_info) */
#define DW_OP_call_ref              0x9a /* [+*]   Call another DW expression (the operator is a dwarf_decode_uleb128 offset from .debug_info) */
#define DW_OP_form_tls_address      0x9b /* [+0]   PUSH(ADDRESS(POP() + sm_tlsbase)) */
#define DW_OP_call_frame_cfa        0x9c /* [+0]   PUSH(CALCULATE_CFA(GET_REGISTER(PC))) */
#define DW_OP_bit_piece             0x9d /* [+*]   size = dwarf_decode_uleb128(&pc); offset = dwarf_decode_uleb128(&pc); WRITE_RESULT((TOP >> offset) & ((1 << size) - 1), size); */
#define DW_OP_implicit_value        0x9e /* [+*]   size = dwarf_decode_uleb128(&pc); PUSH(LVALUE(pc, size)); pc += size; */
#define DW_OP_stack_value           0x9f /* [+0]   TOP = TOP; // Load the value of `TOP' into a stack constant */
#define DW_OP_lo_user               0xe0
#define DW_OP_hi_user               0xff


/* GNU extensions. */
#define DW_OP_GNU_push_tls_address  0xe0 /* [+0]   PUSH(ADDRESS(sm_tlsbase)) */
#define DW_OP_GNU_uninit            0xf0 /* [+0]   UNINIT? */
//#define DW_OP_GNU_encoded_addr      0xf1 /* [+1+*] format = *pc++; PUSH(decode_pointer(format, &pc)); // Format is one of `DW_EH_PE_*' */
//DW_OP (DW_OP_GNU_implicit_pointer, 0xf2)
//DW_OP (DW_OP_GNU_entry_value, 0xf3)
//DW_OP (DW_OP_GNU_const_type, 0xf4)
//DW_OP (DW_OP_GNU_regval_type, 0xf5)
//DW_OP (DW_OP_GNU_deref_type, 0xf6)
//DW_OP (DW_OP_GNU_convert, 0xf7)
//DW_OP (DW_OP_GNU_reinterpret, 0xf9)
//DW_OP (DW_OP_GNU_parameter_ref, 0xfa)
//DW_OP (DW_OP_GNU_addr_index, 0xfb)
//DW_OP (DW_OP_GNU_const_index, 0xfc)
//DW_OP_DUP (DW_OP_HP_unknown, 0xe0)
//DW_OP (DW_OP_HP_is_value, 0xe1)
//DW_OP (DW_OP_HP_fltconst4, 0xe2)
//DW_OP (DW_OP_HP_fltconst8, 0xe3)
//DW_OP (DW_OP_HP_mod_range, 0xe4)
//DW_OP (DW_OP_HP_unmod_range, 0xe5)
//DW_OP (DW_OP_HP_tls, 0xe6)
//DW_OP (DW_OP_PGI_omp_thread_num, 0xf8)

/* Call Frame Information (section 6.4.1) */
#define DW_CFA_register_rule_undefined      0
#define DW_CFA_register_rule_same_value     1
#define DW_CFA_register_rule_offsetn        2
#define DW_CFA_register_rule_val_offsetn    3
#define DW_CFA_register_rule_register       4
#define DW_CFA_register_rule_expression     5
#define DW_CFA_register_rule_val_expression 6


/* Call Frame Information (section 7.23) */
#define DW_CFA_advance_loc          0x40
#define DW_CFA_offset               0x80
#define DW_CFA_restore              0xc0
#define DW_CFA_nop                  0x00
#define DW_CFA_set_loc              0x01
#define DW_CFA_advance_loc1         0x02
#define DW_CFA_advance_loc2         0x03
#define DW_CFA_advance_loc4         0x04
#define DW_CFA_offset_extended      0x05
#define DW_CFA_restore_extended     0x06
#define DW_CFA_undefined            0x07
#define DW_CFA_same_value           0x08
#define DW_CFA_register             0x09
#define DW_CFA_remember_state       0x0a
#define DW_CFA_restore_state        0x0b
#define DW_CFA_def_cfa              0x0c
#define DW_CFA_def_cfa_register     0x0d
#define DW_CFA_def_cfa_offset       0x0e
#define DW_CFA_def_cfa_expression   0x0f
#define DW_CFA_expression           0x10
#define DW_CFA_offset_extended_sf   0x11
#define DW_CFA_def_cfa_sf           0x12
#define DW_CFA_def_cfa_offset_sf    0x13
#define DW_CFA_val_offset           0x14
#define DW_CFA_val_offset_sf        0x15
#define DW_CFA_val_expression       0x16

/* DWARF Call Frame Instruction (CFI) Extensions (section 10.5.2) */
#define DW_CFA_GNU_args_size                0x2e
#define DW_CFA_GNU_negative_offset_extended 0x2f


/* Type codes for `unwind_ste_t::s_type' */
#define UNWIND_STE_CONSTANT    0
#define UNWIND_STE_STACKVALUE  1 /* On-stack constant value (Same as `UNWIND_STE_CONSTANT') */
#define UNWIND_STE_REGISTER    2
#define UNWIND_STE_RW_LVALUE   3 /* Read-write l-value */
#define UNWIND_STE_RO_LVALUE   4 /* Read-only l-value */
#define UNWIND_STE_ISCONSTANT(x) ((x) <= UNWIND_STE_STACKVALUE)
#define UNWIND_STE_ISLVALUE(x)   ((x) >= UNWIND_STE_RW_LVALUE)
#define UNWIND_STE_ISWRITABLE(x) ((x) == UNWIND_STE_REGISTER || (x) == UNWIND_STE_RW_LVALUE)

/* Default value for `sm_bjmprem' */
#define UNWIND_EMULATOR_BJMPREM_DEFAULT  0x800

#ifdef __CC__
__DECL_BEGIN

typedef struct {
	/* Stack entry for unwind expressions. */
	__uint8_t                 s_type;      /* Stack entry type (One of `UNWIND_STE_*') */
	__uint8_t                 s_pad[(sizeof(__uintptr_t) / 2) - 1];
	union {
		__UINTPTR_HALF_TYPE__ s_lsize;     /* [UNWIND_STE_RW_LVALUE] Size of an L-value expression in bytes (If unknown, set to `0') */
		__UINTPTR_HALF_TYPE__ s_register;  /* [UNWIND_STE_REGISTER] Register ID */
	};
	union {
		__uintptr_t       s_uconst;    /* Unsigned constant value */
		__intptr_t        s_sconst;    /* Signed constant value */
		__intptr_t        s_regoffset; /* Offset added to a register expression */
		__byte_t         *s_lvalue;    /* L-value pointer. */
	};
} unwind_ste_t;

/* Read out the contents of a CFI register `regno' and store their value in `dst'
 * The size of the `dst' buffer depends on `regno' and can be calculated with the
 * arch-specific `CFI_REGISTER_SIZE()' macro.
 * @param: regno:  One of `CFI_[arch]_UNWIND_REGISTER_[name]'
 * @param: dst:    A buffer of `CFI_386_REGISTER_SIZE(regno)' bytes,
 *                 to-be filled with the register value.
 * @return: true:  Processed as `UNWIND_SUCCESS'
 * @return: false: Processed as `UNWIND_INVALID_REGISTER' */
typedef __ATTR_NONNULL((3)) __BOOL (LIBUNWIND_CC *unwind_getreg_t)(void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((3)) __BOOL (LIBUNWIND_CC *unwind_setreg_t)(void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);

typedef struct unwind_emulator_sections_struct {
	__byte_t             *ues_eh_frame_start;     /* [0..1][const] Starting address of the .eh_frame section (used for the `DW_OP_call_frame_cfa' instruction).
	                                               * When set to be equal to `ues_eh_frame_end', consider `DW_OP_call_frame_cfa' as an illegal instruction. */
	__byte_t             *ues_eh_frame_end;       /* [0..1][const] End address of the .eh_frame section. */
	__byte_t             *ues_debug_info_start;   /* [0..1][const] Starting address of the .debug_info section (used for the `DW_OP_call2' / `DW_OP_call4' instructions).
	                                               * When set to be equal to `ues_debug_info_end', consider `DW_OP_call2' / `DW_OP_call4' as illegal instructions. */
	__byte_t             *ues_debug_info_end;     /* [0..1][const] End address of the .debug_info section. */
	__byte_t             *ues_debug_abbrev_start; /* [0..1][const] Starting address of the .debug_abbrev section (used for the `DW_OP_call2' / `DW_OP_call4' instructions).
	                                               * When set to be equal to `ues_debug_abbrev_end', consider `DW_OP_call2' / `DW_OP_call4' as illegal instructions. */
	__byte_t             *ues_debug_abbrev_end;   /* [0..1][const] End address of the .debug_abbrev section. */
	__byte_t             *ues_debug_loc_start;    /* [0..1][const] Starting address of the .debug_loc section. */
	__byte_t             *ues_debug_loc_end;      /* [0..1][const] End address of the .debug_loc section. */
} unwind_emulator_sections_t;

#ifndef __di_debuginfo_location_t_defined
#define __di_debuginfo_location_t_defined 1
typedef struct di_debuginfo_location_struct {
	__byte_t    *l_expr;  /* [0..1] Pointer to a CFI expression (for use with `unwind_emulator_exec') for the pointed-to expression. */
	__byte_t    *l_llist; /* [0..1] Pointer to a CFI location list (points into the `.debug_loc' section). */
} di_debuginfo_location_t;
#endif /* !__di_debuginfo_location_t_defined */

typedef struct unwind_emulator_struct {
	unwind_ste_t           *ue_stack;              /* [0..ue_stacksz|ALLOC(ue_stackmax)][const] Value stack for the emulator. */
	__size_t                ue_stacksz;            /* Currently used stack size. */
	__size_t                ue_stackmax;           /* [const] Max available stack size. */
	__byte_t               *ue_pc;                 /* [1..1] Program counter position. */
	__byte_t               *ue_pc_start;           /* [1..1][const] Program start pointer. */
	__byte_t               *ue_pc_end;             /* [1..1][const] Program end pointer. */
	unwind_emulator_sections_t const
	                       *ue_sectinfo;           /* [0..1][const] Emulator section information. */
	unwind_getreg_t         ue_regget;             /* [1..1][const] Callback for reading out the value of a register. */
	unwind_setreg_t         ue_regset;             /* [0..1][const] Callback for writing the value of a register (or NULL if registers are read-only; ignored when `ue_piecewrite' is false). */
	void const             *ue_regget_arg;         /* [?..?][const] Argument passed to `ue_regget'. */
	void                   *ue_regset_arg;         /* [?..?][const] Argument passed to `ue_regset'. */
	di_debuginfo_location_t const
	                       *ue_framebase;          /* [0..1][const] Frame base expression (for use with `DW_OP_fbreg').
	                                                * Set to NULL to consider `DW_OP_fbreg' as an illegal instruction. */
	void                   *ue_objaddr;            /* [0..1][const] Object address value (for use with `DW_OP_push_object_address').
	                                                * Set to NULL to consider `DW_OP_push_object_address' as an illegal instruction. */
	__UINTPTR_HALF_TYPE__   ue_bjmprem;            /* Number of remaining allowed backwards-jumps (used to prevent infinite loops,
	                                                * which get terminated and cause `UNWIND_EMULATOR_LOOP' to be returned)
	                                                * During initialization, you may simply assign `UNWIND_EMULATOR_BJMPREM_DEFAULT'
	                                                * to this field. */
#if __SIZEOF_POINTER__ > 4
	__uint8_t               ue_pad[(sizeof(void *)/2) - 2];
#endif /* __SIZEOF_POINTER__ > 4 */
	__uint8_t               ue_addrsize;           /* [const] Address size (one of 1,2,4 or 8) (operand size of `DW_OP_addr') */
	__uint8_t               ue_piecewrite;         /* [const] Non-zero if data pieces should be written, rather than read. */
	__byte_t               *ue_piecebuf;           /* [0..sm_piecesiz][const] Pointer to a buffer to receive data from `DW_OP_piece' */
	__size_t                ue_piecesiz;           /* [const] Size of the `sm_piecebuf' buffer in bytes. */
	__size_t                ue_piecebits;          /* [<= sm_piecesiz * 8] Number of _BITS_ within the `sm_piecebuf' buffer that are in use. */
	__uintptr_t             ue_call_frame_cfa;     /* [0..1] Lazily calculated value for the call-frame-CFA of the given register state.
	                                                * When set to ZERO(0), this value is calculated as-needed, using:
	                                                *  - unwind_fde_scan(ue_eh_frame_start,ue_eh_frame_end,...)
	                                                *  - unwind_fde_exec(...) */
	__uintptr_t             ue_module_base;        /* [const] Module base address (used for selecting callbacks within expression lists) */
	__uintptr_t             ue_module_relative_pc; /* [const] Module-relative program counter position (used for selecting callbacks within expression lists) */
	__byte_t               *ue_tlsbase;            /* [0..1] Base to-be added to an offset in order to form a TLS address within the
	                                                * targeted thread (or `NULL' if unknown, in which case `DW_OP_form_tls_address'
	                                                * is considered an illegal instruction, or `(__byte_t *)-1' to lazily calculate) */
} unwind_emulator_t;

/* Execute the CFI expression loaded into the given unwind-emulator `self'.
 * Upon success, `self->ue_stacksz' will have been updated to the new stack
 * size, allowing the caller to read the expression's return values from it.
 * NOTE: `unwind_emulator_exec_autostack()' behaves the same as `unwind_emulator_exec()',
 *        but will automatically allocated/free the expression stack upon entry/return, pushing
 *       `pentry_stack_top' upon entry, and storing the last stack-entry in `*pexit_stack_top'
 *        before returning (if no such value exists, `UNWIND_EMULATOR_NO_RETURN_VALUE' is returned).
 *        If no stack of sufficient size could be allocated (or if the required stack size is
 *        absurdly large), `UNWIND_EMULATOR_STACK_OVERFLOW' will be returned instead.
 * @param: pentry_stack_top:      A value to-be pushed onto the stack upon entry (or NULL).
 * @param: pexit_stack_top:       A value to-be popped off of the stack upon exit (or NULL).
 * @param: pexit_stack_top_const: Same as `pexit_stack_top', but casted into a constant.
 * @return: UNWIND_SUCCESS:          ...
 * @return: UNWIND_INVALID_REGISTER: ...
 * @return: UNWIND_SEGFAULT:         ...
 * @return: UNWIND_BADALLOC:         ...
 * @return: UNWIND_EMULATOR_*:       ... */
typedef __ATTR_NONNULL((1)) unsigned int
(LIBUNWIND_CC *PUNWIND_EMULATOR_EXEC)(unwind_emulator_t *__restrict self);
typedef __ATTR_NONNULL((1)) unsigned int
(LIBUNWIND_CC *PUNWIND_EMULATOR_EXEC_AUTOSTACK)(unwind_emulator_t *__restrict self,
                                                unwind_ste_t const *pentry_stack_top,
                                                unwind_ste_t *pexit_stack_top,
                                                __uintptr_t *pexit_stack_top_const);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1)) unsigned int LIBUNWIND_CC
unwind_emulator_exec(unwind_emulator_t *__restrict self);
LIBUNWIND_DECL __ATTR_NONNULL((1)) unsigned int LIBUNWIND_CC
unwind_emulator_exec_autostack(unwind_emulator_t *__restrict self,
                               unwind_ste_t const *pentry_stack_top,
                               unwind_ste_t *pexit_stack_top,
                               __uintptr_t *pexit_stack_top_const);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Return a pointer to the next unwind instruction following `unwind_pc'
 * -> Useful for dumping unwind instruction without having to take care
 *    of handling all possible instruction (after all: CFI has a CISC
 *    instruction set with variable-length instructions)
 * @return: NULL: The instruction at `unwind_pc' wasn't recognized. */
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED __ATTR_NONNULL((1)) __byte_t const *
(LIBUNWIND_CC *PUNWIND_INSTRUCTION_SUCC)(__byte_t const *__restrict unwind_pc, __uint8_t addrsize);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __byte_t const *
__NOTHROW_NCX(LIBUNWIND_CC unwind_instruction_succ)(__byte_t const *__restrict unwind_pc, __uint8_t addrsize);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

/* Return a pointer to a CFI expression that is applicable for `cu_base + module_relative_pc'
 * If no such expression exists, return `NULL' instead. */
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED __ATTR_NONNULL((1, 5)) __byte_t *
(LIBUNWIND_CC *PDEBUGINFO_LOCATION_SELECT)(di_debuginfo_location_t const *__restrict self,
                                           __uintptr_t cu_base,
                                           __uintptr_t module_relative_pc,
                                           __uint8_t addrsize,
                                           __size_t *__restrict pexpr_length);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 5)) __byte_t *
__NOTHROW_NCX(LIBUNWIND_CC debuginfo_location_select)(di_debuginfo_location_t const *__restrict self,
                                                      __uintptr_t cu_base,
                                                      __uintptr_t module_relative_pc,
                                                      __uint8_t addrsize,
                                                      __size_t *__restrict pexpr_length);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* Read/Write the value associated a given debuginfo location descriptor.
 * @param: self:                  The debug info location descriptor (s.a. libdebuginfo.so)
 * @param: sectinfo:              Emulator section information (to-be filled in by the caller)
 *                                Optionally, this argument may be `NULL', however if this is the
 *                                case, the function may fail in cases where it would have otherwise
 *                                succeeded.
 * @param: regget:                Register getter callback.
 * @param: regget_arg:            Register getter callback argument.
 * @param: regset:                Register setter callback.
 * @param: regset_arg:            Register setter callback argument.
 * @param: cu_base:               Base address of the associated CU (or `0') (== `di_debuginfo_compile_unit_t::cu_ranges::r_startpc')
 * @param: module_relative_pc:    The module-relative program counter, to-be used to select
 *                                the appropriate expression within a location list.
 * @param: buf:                   Source/target buffer containing the value read from,
 *                                or written to the location expression.
 * @param: bufsize:               Size of the given `buf' in bytes.
 * @param: pnum_written_bits:     The number of _BITS_ (not bytes!) read from the location expression,
 *                                and written to the given `buf' (any trailing bits of buffer memory
 *                                that weren't written will be filled with `0' upon success)
 * @param: pnum_read_bits:        The number of _BITS_ (not bytes!) written to the location expression,
 *                                and read from the given `buf'.
 * @param: frame_base_expression: The expression used to calculate the frame-base address (or NULL if unknown)
 * @param: objaddr:               The address of the base-object (used e.g. for structure member expressions)
 * @param: addrsize:              Size of an address (defined by the associated CU, and usually == sizeof(void *))
 * @return: * :                               One of `UNWIND_*'
 * @return: UNWIND_EMULATOR_NOT_WRITABLE:     Attempted to write to a read-only location expression.
 * @return: UNWIND_EMULATOR_BUFFER_TOO_SMALL: The given `bufsize' is too small.
 * @return: UNWIND_EMULATOR_NO_FUNCTION:      The associated location list is undefined for `module_relative_pc' */
typedef __ATTR_NONNULL((1, 3, 7, 9)) unsigned int
(LIBUNWIND_CC *PDEBUGINFO_LOCATION_GETVALUE)(di_debuginfo_location_t const *__restrict self,
                                             unwind_emulator_sections_t const *sectinfo,
                                             unwind_getreg_t regget, void *regget_arg,
                                             __uintptr_t cu_base,
                                             __uintptr_t module_relative_pc,
                                             void *__restrict buf, __size_t bufsize,
                                             __size_t *__restrict pnum_written_bits,
                                             di_debuginfo_location_t const *frame_base_expression,
                                             void *objaddr, __uint8_t addrsize);
typedef __ATTR_NONNULL((1, 3, 5, 9, 11)) unsigned int
(LIBUNWIND_CC *PDEBUGINFO_LOCATION_SETVALUE)(di_debuginfo_location_t const *__restrict self,
                                             unwind_emulator_sections_t const *sectinfo,
                                             unwind_getreg_t regget, void *regget_arg,
                                             unwind_setreg_t regset, void *regset_arg,
                                             __uintptr_t cu_base,
                                             __uintptr_t module_relative_pc,
                                             void const *__restrict buf, __size_t bufsize,
                                             __size_t *__restrict pnum_read_bits,
                                             di_debuginfo_location_t const *frame_base_expression,
                                             void *objaddr, __uint8_t addrsize);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3, 7, 9)) unsigned int LIBUNWIND_CC
debuginfo_location_getvalue(di_debuginfo_location_t const *__restrict self,
                            unwind_emulator_sections_t const *sectinfo,
                            unwind_getreg_t regget, void *regget_arg,
                            __uintptr_t cu_base,
                            __uintptr_t module_relative_pc,
                            void *__restrict buf, __size_t bufsize,
                            __size_t *__restrict pnum_written_bits,
                            di_debuginfo_location_t const *frame_base_expression,
                            void *objaddr, __uint8_t addrsize);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3, 5, 9, 11)) unsigned int LIBUNWIND_CC
debuginfo_location_setvalue(di_debuginfo_location_t const *__restrict self,
                            unwind_emulator_sections_t const *sectinfo,
                            unwind_getreg_t regget, void *regget_arg,
                            unwind_setreg_t regset, void *regset_arg,
                            __uintptr_t cu_base,
                            __uintptr_t module_relative_pc,
                            void const *__restrict buf, __size_t bufsize,
                            __size_t *__restrict pnum_read_bits,
                            di_debuginfo_location_t const *frame_base_expression,
                            void *objaddr, __uint8_t addrsize);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */


#endif /* !_LIBUNWIND_CFI_H */
