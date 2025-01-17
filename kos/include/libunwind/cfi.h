/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBUNWIND_CFI_H
#define _LIBUNWIND_CFI_H 1

#ifndef __DEEMON__
#include "api.h"

#include <kos/anno.h>
#include <hybrid/host.h>

#include <bits/types.h>

#include "errno.h"

#if defined(__x86_64__)
#include "cfi/x86_64.h"
#elif defined(__i386__)
#include "cfi/i386.h"
#elif defined(__arm__)
#include "cfi/arm.h"
#else /* Arch... */
#error "Unsupported architecture"
#endif /* !Arch... */
#endif /* !__DEEMON__ */


#ifndef CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_NO_COMMON_UNCOMMON_REGISTERS      1
#define CFI_UNWIND_COMMON_REGISTER_MAXCOUNT          CFI_UNWIND_REGISTER_MAXCOUNT
#define CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT        0
#define CFI_UNWIND_COMMON_REGISTER_SP                CFI_UNWIND_REGISTER_SP
#define cfi_unwind_register_dw2common(dw_regno)      (dw_regno)
#define cfi_unwind_register_dw2uncommon(dw_regno)    0
#define cfi_unwind_register_common2dw(com_regno)     (com_regno)
#define cfi_unwind_register_uncommon2dw(uncom_regno) CFI_UNWIND_REGISTER_MAXCOUNT
#endif /* !CFI_UNWIND_COMMON_REGISTER_MAXCOUNT */

#if (defined(CFI_UNWIND_COMMON_REGISTER_SP) + \
     defined(CFI_UNWIND_UNCOMMON_REGISTER_SP)) != 1
#error "Need exactly one of `CFI_UNWIND_COMMON_REGISTER_SP' or `CFI_UNWIND_UNCOMMON_REGISTER_SP'"
#endif

#ifndef CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS 1
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_MAXCOUNT   CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_MAXCOUNT CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT
#ifdef CFI_UNWIND_COMMON_REGISTER_SP
#define CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP      CFI_UNWIND_COMMON_REGISTER_SP
#else /* CFI_UNWIND_COMMON_REGISTER_SP */
#define CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_SP    CFI_UNWIND_UNCOMMON_REGISTER_SP
#endif /* !CFI_UNWIND_COMMON_REGISTER_SP */
#define cfi_unwind_sigframe_register_dw2common      cfi_unwind_register_dw2common
#define cfi_unwind_sigframe_register_dw2uncommon    cfi_unwind_register_dw2uncommon
#define cfi_unwind_sigframe_register_common2dw      cfi_unwind_register_common2dw
#define cfi_unwind_sigframe_register_uncommon2dw    cfi_unwind_register_uncommon2dw
#endif /* !CFI_UNWIND_COMMON_REGISTER_MAXCOUNT */

#if (defined(CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP) + \
     defined(CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_SP)) != 1
#error "Need exactly one of `CFI_UNWIND_SIGFRAME_COMMON_REGISTER_SP' or `CFI_UNWIND_SIGFRAME_UNCOMMON_REGISTER_SP'"
#endif
#ifndef CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_NO_LANDING_COMMON_UNCOMMON_REGISTERS 1
#define CFI_UNWIND_LANDING_COMMON_REGISTER_MAXCOUNT   CFI_UNWIND_COMMON_REGISTER_MAXCOUNT
#define CFI_UNWIND_LANDING_UNCOMMON_REGISTER_MAXCOUNT CFI_UNWIND_UNCOMMON_REGISTER_MAXCOUNT
#ifdef CFI_UNWIND_COMMON_REGISTER_SP
#define CFI_UNWIND_LANDING_COMMON_REGISTER_SP      CFI_UNWIND_COMMON_REGISTER_SP
#else /* CFI_UNWIND_COMMON_REGISTER_SP */
#define CFI_UNWIND_LANDING_UNCOMMON_REGISTER_SP    CFI_UNWIND_UNCOMMON_REGISTER_SP
#endif /* !CFI_UNWIND_COMMON_REGISTER_SP */
#define cfi_unwind_landing_register_dw2common      cfi_unwind_register_dw2common
#define cfi_unwind_landing_register_dw2uncommon    cfi_unwind_register_dw2uncommon
#define cfi_unwind_landing_register_common2dw      cfi_unwind_register_common2dw
#define cfi_unwind_landing_register_uncommon2dw    cfi_unwind_register_uncommon2dw
#endif /* !CFI_UNWIND_COMMON_REGISTER_MAXCOUNT */

#if (defined(CFI_UNWIND_LANDING_COMMON_REGISTER_SP) + \
     defined(CFI_UNWIND_LANDING_UNCOMMON_REGISTER_SP)) != 1
#error "Need exactly one of `CFI_UNWIND_LANDING_COMMON_REGISTER_SP' or `CFI_UNWIND_LANDING_UNCOMMON_REGISTER_SP'"
#endif





/* HINT: Embedding CFI code that is only meant for the eyes of KOS:
 * >>    .cfi_escape DW_OP_skip, 3, 0
 * >>    .cfi_escape 'K', 'O', 'S'
 * >>    .cfi_escape DW_OP_skip, n, m
 * >>    .cfi_escape ...  // This code (with a size of n + (m << 8)) is only executed under KOS
 */

/*      DW_OP_                     0x00  * ... */
/*      DW_OP_                     0x01  * ... */
/*      DW_OP_                     0x02  * ... */
#define DW_OP_addr                 0x03 /* [+4|8] +uintptr_t constant address */
/*      DW_OP_                     0x04  * ... */
/*      DW_OP_                     0x05  * ... */
#define DW_OP_deref                0x06 /* [+0]   TOP = *(uintptr_t *)TOP; */
/*      DW_OP_                     0x07  * ... */
#define DW_OP_const1u              0x08 /* [+1]   PUSH(*(u8 const *)pc); */
#define DW_OP_const1s              0x09 /* [+1]   PUSH(*(s8 const *)pc); */
#define DW_OP_const2u              0x0a /* [+2]   PUSH(*(u16 const *)pc); */
#define DW_OP_const2s              0x0b /* [+2]   PUSH(*(s16 const *)pc); */
#define DW_OP_const4u              0x0c /* [+4]   PUSH(*(u32 const *)pc); */
#define DW_OP_const4s              0x0d /* [+4]   PUSH(*(s32 const *)pc); */
#define DW_OP_const8u              0x0e /* [+8]   PUSH(*(u64 const *)pc); */
#define DW_OP_const8s              0x0f /* [+8]   PUSH(*(s64 const *)pc); */
#define DW_OP_constu               0x10 /* [+*]   PUSH(dwarf_decode_uleb128(&pc)); */
#define DW_OP_consts               0x11 /* [+*]   PUSH(dwarf_decode_sleb128(&pc)); */
#define DW_OP_dup                  0x12 /* [+0]   PUSH(TOP); */
#define DW_OP_drop                 0x13 /* [+0]   POP(); */
#define DW_OP_over                 0x14 /* [+0]   PUSH(SECOND); */
#define DW_OP_pick                 0x15 /* [+1]   PUSH(NTH(*(u8 const *)pc));  // Where operand=0 is the old TOP */
#define DW_OP_swap                 0x16 /* [+0]   TOP = XCH(SECOND, TOP); */
#define DW_OP_rot                  0x17 /* [+0]   a = TOP; TOP = SECOND; SECOND = THIRD; THIRD = a; */
#define DW_OP_xderef               0x18 /* [+0]   off = POP(); id = POP(); PUSH(*(uintptr_t *)id:off) */
#define DW_OP_abs                  0x19 /* [+0]   a = POP(); PUSH(a < 0 ? -a : a); */
#define DW_OP_and                  0x1a /* [+0]   PUSH(POP(SECOND) & POP(TOP)); */
#define DW_OP_div                  0x1b /* [+0]   PUSH((signed)POP(SECOND) / (signed)POP(TOP)); */
#define DW_OP_minus                0x1c /* [+0]   PUSH(POP(SECOND) - POP(TOP)); */
#define DW_OP_mod                  0x1d /* [+0]   PUSH((signed)POP(SECOND) % (signed)POP(TOP)); */
#define DW_OP_mul                  0x1e /* [+0]   PUSH((signed)POP(SECOND) * (signed)POP(TOP)); */
#define DW_OP_neg                  0x1f /* [+0]   PUSH(-POP()); */
#define DW_OP_not                  0x20 /* [+0]   PUSH(~POP()); */
#define DW_OP_or                   0x21 /* [+0]   PUSH(POP(SECOND) | POP(TOP)); */
#define DW_OP_plus                 0x22 /* [+0]   PUSH(POP(SECOND) + POP(TOP)); */
#define DW_OP_plus_uconst          0x23 /* [+*]   PUSH(POP(TOP) + dwarf_decode_uleb128(&pc)); */
#define DW_OP_shl                  0x24 /* [+0]   PUSH(POP(SECOND) << POP(TOP)); */
#define DW_OP_shr                  0x25 /* [+0]   PUSH((unsigned)POP(SECOND) >> POP(TOP)); */
#define DW_OP_shra                 0x26 /* [+0]   PUSH((signed)POP(SECOND) >> POP(TOP)); */
#define DW_OP_xor                  0x27 /* [+0]   PUSH(POP(SECOND) ^ POP(TOP)); */
#define DW_OP_bra                  0x28 /* [+2]   off = *(s16 const *)pc; pc += 2; if (POP() != 0) pc += off; */
#define DW_OP_eq                   0x29 /* [+0]   PUSH(POP(SECOND) == POP(TOP)); */
#define DW_OP_ge                   0x2a /* [+0]   PUSH((signed)POP(SECOND) >= (signed)POP(TOP)); */
#define DW_OP_gt                   0x2b /* [+0]   PUSH((signed)POP(SECOND) >  (signed)POP(TOP)); */
#define DW_OP_le                   0x2c /* [+0]   PUSH((signed)POP(SECOND) <= (signed)POP(TOP)); */
#define DW_OP_lt                   0x2d /* [+0]   PUSH((signed)POP(SECOND) <  (signed)POP(TOP)); */
#define DW_OP_ne                   0x2e /* [+0]   PUSH(POP(SECOND) != POP(TOP)); */
#define DW_OP_skip                 0x2f /* [+2]   off = *(s16 const *)pc; pc += 2; pc += off; */
#define DW_OP_lit0                 0x30 /* [+0]   PUSH(0); */
#define DW_OP_lit1                 0x31 /* [+0]   PUSH(1); */
#define DW_OP_lit2                 0x32 /* [+0]   PUSH(2); */
#define DW_OP_lit3                 0x33 /* [+0]   PUSH(3); */
#define DW_OP_lit4                 0x34 /* [+0]   PUSH(4); */
#define DW_OP_lit5                 0x35 /* [+0]   PUSH(5); */
#define DW_OP_lit6                 0x36 /* [+0]   PUSH(6); */
#define DW_OP_lit7                 0x37 /* [+0]   PUSH(7); */
#define DW_OP_lit8                 0x38 /* [+0]   PUSH(8); */
#define DW_OP_lit9                 0x39 /* [+0]   PUSH(9); */
#define DW_OP_lit10                0x3a /* [+0]   PUSH(10); */
#define DW_OP_lit11                0x3b /* [+0]   PUSH(11); */
#define DW_OP_lit12                0x3c /* [+0]   PUSH(12); */
#define DW_OP_lit13                0x3d /* [+0]   PUSH(13); */
#define DW_OP_lit14                0x3e /* [+0]   PUSH(14); */
#define DW_OP_lit15                0x3f /* [+0]   PUSH(15); */
#define DW_OP_lit16                0x40 /* [+0]   PUSH(16); */
#define DW_OP_lit17                0x41 /* [+0]   PUSH(17); */
#define DW_OP_lit18                0x42 /* [+0]   PUSH(18); */
#define DW_OP_lit19                0x43 /* [+0]   PUSH(19); */
#define DW_OP_lit20                0x44 /* [+0]   PUSH(20); */
#define DW_OP_lit21                0x45 /* [+0]   PUSH(21); */
#define DW_OP_lit22                0x46 /* [+0]   PUSH(22); */
#define DW_OP_lit23                0x47 /* [+0]   PUSH(23); */
#define DW_OP_lit24                0x48 /* [+0]   PUSH(24); */
#define DW_OP_lit25                0x49 /* [+0]   PUSH(25); */
#define DW_OP_lit26                0x4a /* [+0]   PUSH(26); */
#define DW_OP_lit27                0x4b /* [+0]   PUSH(27); */
#define DW_OP_lit28                0x4c /* [+0]   PUSH(28); */
#define DW_OP_lit29                0x4d /* [+0]   PUSH(29); */
#define DW_OP_lit30                0x4e /* [+0]   PUSH(30); */
#define DW_OP_lit31                0x4f /* [+0]   PUSH(31); */
#define DW_OP_reg0                 0x50 /* [+0]   PUSH(GET_CONTEXT_REGADDR(0)); */
#define DW_OP_reg1                 0x51 /* [+0]   PUSH(GET_CONTEXT_REGADDR(1)); */
#define DW_OP_reg2                 0x52 /* [+0]   PUSH(GET_CONTEXT_REGADDR(2)); */
#define DW_OP_reg3                 0x53 /* [+0]   PUSH(GET_CONTEXT_REGADDR(3)); */
#define DW_OP_reg4                 0x54 /* [+0]   PUSH(GET_CONTEXT_REGADDR(4)); */
#define DW_OP_reg5                 0x55 /* [+0]   PUSH(GET_CONTEXT_REGADDR(5)); */
#define DW_OP_reg6                 0x56 /* [+0]   PUSH(GET_CONTEXT_REGADDR(6)); */
#define DW_OP_reg7                 0x57 /* [+0]   PUSH(GET_CONTEXT_REGADDR(7)); */
#define DW_OP_reg8                 0x58 /* [+0]   PUSH(GET_CONTEXT_REGADDR(8)); */
#define DW_OP_reg9                 0x59 /* [+0]   PUSH(GET_CONTEXT_REGADDR(9)); */
#define DW_OP_reg10                0x5a /* [+0]   PUSH(GET_CONTEXT_REGADDR(10)); */
#define DW_OP_reg11                0x5b /* [+0]   PUSH(GET_CONTEXT_REGADDR(11)); */
#define DW_OP_reg12                0x5c /* [+0]   PUSH(GET_CONTEXT_REGADDR(12)); */
#define DW_OP_reg13                0x5d /* [+0]   PUSH(GET_CONTEXT_REGADDR(13)); */
#define DW_OP_reg14                0x5e /* [+0]   PUSH(GET_CONTEXT_REGADDR(14)); */
#define DW_OP_reg15                0x5f /* [+0]   PUSH(GET_CONTEXT_REGADDR(15)); */
#define DW_OP_reg16                0x60 /* [+0]   PUSH(GET_CONTEXT_REGADDR(16)); */
#define DW_OP_reg17                0x61 /* [+0]   PUSH(GET_CONTEXT_REGADDR(17)); */
#define DW_OP_reg18                0x62 /* [+0]   PUSH(GET_CONTEXT_REGADDR(18)); */
#define DW_OP_reg19                0x63 /* [+0]   PUSH(GET_CONTEXT_REGADDR(19)); */
#define DW_OP_reg20                0x64 /* [+0]   PUSH(GET_CONTEXT_REGADDR(20)); */
#define DW_OP_reg21                0x65 /* [+0]   PUSH(GET_CONTEXT_REGADDR(21)); */
#define DW_OP_reg22                0x66 /* [+0]   PUSH(GET_CONTEXT_REGADDR(22)); */
#define DW_OP_reg23                0x67 /* [+0]   PUSH(GET_CONTEXT_REGADDR(23)); */
#define DW_OP_reg24                0x68 /* [+0]   PUSH(GET_CONTEXT_REGADDR(24)); */
#define DW_OP_reg25                0x69 /* [+0]   PUSH(GET_CONTEXT_REGADDR(25)); */
#define DW_OP_reg26                0x6a /* [+0]   PUSH(GET_CONTEXT_REGADDR(26)); */
#define DW_OP_reg27                0x6b /* [+0]   PUSH(GET_CONTEXT_REGADDR(27)); */
#define DW_OP_reg28                0x6c /* [+0]   PUSH(GET_CONTEXT_REGADDR(28)); */
#define DW_OP_reg29                0x6d /* [+0]   PUSH(GET_CONTEXT_REGADDR(29)); */
#define DW_OP_reg30                0x6e /* [+0]   PUSH(GET_CONTEXT_REGADDR(30)); */
#define DW_OP_reg31                0x6f /* [+0]   PUSH(GET_CONTEXT_REGADDR(31)); */
#define DW_OP_breg0                0x70 /* [+*]   PUSH(GET_CONTEXT_REGVAL(0) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg1                0x71 /* [+*]   PUSH(GET_CONTEXT_REGVAL(1) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg2                0x72 /* [+*]   PUSH(GET_CONTEXT_REGVAL(2) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg3                0x73 /* [+*]   PUSH(GET_CONTEXT_REGVAL(3) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg4                0x74 /* [+*]   PUSH(GET_CONTEXT_REGVAL(4) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg5                0x75 /* [+*]   PUSH(GET_CONTEXT_REGVAL(5) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg6                0x76 /* [+*]   PUSH(GET_CONTEXT_REGVAL(6) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg7                0x77 /* [+*]   PUSH(GET_CONTEXT_REGVAL(7) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg8                0x78 /* [+*]   PUSH(GET_CONTEXT_REGVAL(8) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg9                0x79 /* [+*]   PUSH(GET_CONTEXT_REGVAL(9) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg10               0x7a /* [+*]   PUSH(GET_CONTEXT_REGVAL(10) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg11               0x7b /* [+*]   PUSH(GET_CONTEXT_REGVAL(11) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg12               0x7c /* [+*]   PUSH(GET_CONTEXT_REGVAL(12) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg13               0x7d /* [+*]   PUSH(GET_CONTEXT_REGVAL(13) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg14               0x7e /* [+*]   PUSH(GET_CONTEXT_REGVAL(14) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg15               0x7f /* [+*]   PUSH(GET_CONTEXT_REGVAL(15) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg16               0x80 /* [+*]   PUSH(GET_CONTEXT_REGVAL(16) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg17               0x81 /* [+*]   PUSH(GET_CONTEXT_REGVAL(17) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg18               0x82 /* [+*]   PUSH(GET_CONTEXT_REGVAL(18) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg19               0x83 /* [+*]   PUSH(GET_CONTEXT_REGVAL(19) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg20               0x84 /* [+*]   PUSH(GET_CONTEXT_REGVAL(20) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg21               0x85 /* [+*]   PUSH(GET_CONTEXT_REGVAL(21) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg22               0x86 /* [+*]   PUSH(GET_CONTEXT_REGVAL(22) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg23               0x87 /* [+*]   PUSH(GET_CONTEXT_REGVAL(23) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg24               0x88 /* [+*]   PUSH(GET_CONTEXT_REGVAL(24) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg25               0x89 /* [+*]   PUSH(GET_CONTEXT_REGVAL(25) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg26               0x8a /* [+*]   PUSH(GET_CONTEXT_REGVAL(26) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg27               0x8b /* [+*]   PUSH(GET_CONTEXT_REGVAL(27) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg28               0x8c /* [+*]   PUSH(GET_CONTEXT_REGVAL(28) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg29               0x8d /* [+*]   PUSH(GET_CONTEXT_REGVAL(29) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg30               0x8e /* [+*]   PUSH(GET_CONTEXT_REGVAL(30) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_breg31               0x8f /* [+*]   PUSH(GET_CONTEXT_REGVAL(31) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_regx                 0x90 /* [+*]   PUSH(GET_CONTEXT_REGADDR(dwarf_decode_uleb128(&pc))); */
#define DW_OP_fbreg                0x91 /* [+*]   PUSH(EVAL(CURRENT_FUNCTION.DW_AT_frame_base) + dwarf_decode_sleb128(&pc)) */
#define DW_OP_bregx                0x92 /* [+*]   PUSH(GET_CONTEXT_REGVAL(dwarf_decode_uleb128(&pc)) + dwarf_decode_sleb128(&pc)); */
#define DW_OP_piece                0x93 /* [+*]   num_bytes = dwarf_decode_uleb128(&pc); WRITE_RESULT(POP(), num_bytes * 8); // Assign TOP to `num_bytes' of the variable's value. */
#define DW_OP_deref_size           0x94 /* [+1]   n = *(u8 const *)pc; pc += 1; p = POP(); PUSH(n == 1 ? *(u8 const *)p : n == 2 ? *(u16 const *)p : n == 4 ? *(u32 const *)p : n == 8 ? *(u64 const *)p : UNDEFINED); */
#define DW_OP_xderef_size          0x95 /* [+1]   n = *(u8 const *)pc; pc += 1; p = POP(); id = POP(); PUSH(n == 1 ? *(u8 const *)id:p : n == 2 ? *(u16 const *)id:p : n == 4 ? *(u32 const *)id:p : n == 8 ? *(u64 const *)id:p : UNDEFINED); */
#define DW_OP_nop                  0x96 /* [+0]   Do nothing */
#define DW_OP_push_object_address  0x97 /* [+0]   Push the value of `ue_objaddr' */
#define DW_OP_call2                0x98 /* [+2]   Call another DW expression (the operator is a 2-byte unsigned offset from .debug_info) */
#define DW_OP_call4                0x99 /* [+4]   Call another DW expression (the operator is a 4-byte unsigned offset from .debug_info) */
#define DW_OP_call_ref             0x9a /* [+*]   Call another DW expression (the operator is a dwarf_decode_uleb128 offset from .debug_info) */
#define DW_OP_form_tls_address     0x9b /* [+0]   PUSH(ADDRESS(POP() + ue_tlsbase)) */
#define DW_OP_call_frame_cfa       0x9c /* [+0]   PUSH(CALCULATE_CFA(GET_REGISTER(PC))) */
#define DW_OP_bit_piece            0x9d /* [+*]   size = dwarf_decode_uleb128(&pc); offset = dwarf_decode_uleb128(&pc); WRITE_RESULT((TOP >> offset) & ((1 << size) - 1), size); */
#define DW_OP_implicit_value       0x9e /* [+*]   size = dwarf_decode_uleb128(&pc); PUSH(LVALUE(pc, size)); pc += size; */
#define DW_OP_stack_value          0x9f /* [+0]   TOP = TOP; // Load the value of `TOP' into a stack constant */
#define DW_OP_implicit_pointer     0xa0 /* <Not supported> */
#define DW_OP_addrx                0xa1 /* [+*]   PUSH(*(uintptr_t *)(ues_debug_addr_start + ue_cu->cu_addr_base + dwarf_decode_uleb128(&pc))) */
#define DW_OP_constx               0xa2 /* [+*]   PUSH(*(uintptr_t *)(ues_debug_addr_start + ue_cu->cu_addr_base + dwarf_decode_uleb128(&pc))) */
#define DW_OP_entry_value          0xa3 /* [+*]   size = dwarf_decode_uleb128(&pc); EVAL_DW_OP_CODE_AT_SUBPROGRAM_ENTRY(pc, pc + size); pc += size; */
#define DW_OP_const_type           0xa4 /* [+*]   dwarf_decode_uleb128(&pc); size = *(u8 const *)pc; pc += 1; pc += size; <Not supported> */
#define DW_OP_regval_type          0xa5 /* [+*]   dwarf_decode_uleb128(&pc); dwarf_decode_uleb128(&pc); <Not supported> */
#define DW_OP_deref_type           0xa6 /* [+*]   pc += 1; dwarf_decode_uleb128(&pc); <Not supported> */
#define DW_OP_xderef_type          0xa7 /* [+*]   pc += 1; dwarf_decode_uleb128(&pc); <Not supported> */
#define DW_OP_convert              0xa8 /* [+*]   dwarf_decode_uleb128(&pc); <Not supported> */
#define DW_OP_reinterpret          0xa9 /* [+*]   dwarf_decode_uleb128(&pc); <Not supported> */
/*      DW_OP_                     0xaa  * ... */
/*      DW_OP_                     ...   * ... */
/*      DW_OP_                     0xdf  * ... */
#define DW_OP_lo_user              0xe0 /* First user-defined opcode */
#define DW_OP_hi_user              0xff /* Last user-defined opcode */


/* DW Opcode extensions. */
#define DW_OP_GNU_push_tls_address 0xe0 /* [+0]   PUSH(ADDRESS(POP() + ue_tlsbase))   (Alias for `DW_OP_form_tls_address') */
#define DW_OP_HP_unknown           0xe0 /* ??? */
#define DW_OP_HP_is_value          0xe1 /* <Not supported> */
#define DW_OP_HP_fltconst4         0xe2 /* <Not supported> */
#define DW_OP_HP_fltconst8         0xe3 /* <Not supported> */
#define DW_OP_HP_mod_range         0xe4 /* <Not supported> */
#define DW_OP_HP_unmod_range       0xe5 /* <Not supported> */
#define DW_OP_HP_tls               0xe6 /* <Not supported> */
/*      DW_OP_                     0xe7  * ... */
/*      DW_OP_                     0xe8  * ... */
/*      DW_OP_                     0xe9  * ... */
#define DW_OP_AARCH64_operation    0xea /* ??? */
/*      DW_OP_                     0xea  * ... */
/*      DW_OP_                     0xeb  * ... */
/*      DW_OP_                     0xec  * ... */
/*      DW_OP_                     0xed  * ... */
/*      DW_OP_                     0xee  * ... */
/*      DW_OP_                     0xef  * ... */
#define DW_OP_GNU_uninit           0xf0 /* [+0]   UNINIT? */
#define DW_OP_GNU_encoded_addr     0xf1 /* [+1+*] format = *pc++; PUSH(decode_pointer(format, &pc)); // Format is one of `DW_EH_PE_*' */
#define DW_OP_GNU_implicit_pointer 0xf2 /* <Not supported> */
#define DW_OP_GNU_entry_value      0xf3 /* [+*]   size = dwarf_decode_uleb128(&pc); EVAL_DW_OP_CODE_AT_SUBPROGRAM_ENTRY(pc, pc + size); pc += size; (Alias for `DW_OP_entry_value') */
#define DW_OP_GNU_const_type       0xf4 /* <Not supported> (alias for `DW_OP_const_type') */
#define DW_OP_GNU_regval_type      0xf5 /* <Not supported> (alias for `DW_OP_regval_type') */
#define DW_OP_GNU_deref_type       0xf6 /* <Not supported> (alias for `DW_OP_deref_type') */
#define DW_OP_GNU_convert          0xf7 /* <Not supported> (alias for `DW_OP_convert') */
#define DW_OP_PGI_omp_thread_num   0xf8 /* <Not supported> */
#define DW_OP_GNU_reinterpret      0xf9 /* <Not supported> (alias for `DW_OP_reinterpret') */
#define DW_OP_GNU_parameter_ref    0xfa /* <Not supported> */
#define DW_OP_GNU_addr_index       0xfb /* [+*]   PUSH(*(uintptr_t *)(ues_debug_addr_start + ue_cu->cu_addr_base + dwarf_decode_uleb128(&pc)))  (alias for `DW_OP_addrx') */
#define DW_OP_GNU_const_index      0xfc /* [+*]   PUSH(*(uintptr_t *)(ues_debug_addr_start + ue_cu->cu_addr_base + dwarf_decode_uleb128(&pc)))  (alias for `DW_OP_addrx') */
#define DW_OP_GNU_variable_value   0xfd /* ??? */
/*      DW_OP_                     0xfd  * ... */
/*      DW_OP_                     0xfe  * ... */
/*      DW_OP_                     0xff  * ... */


/* Call Frame Information (section 6.4.1) */
#define DW_CFA_register_rule_undefined      0 /* Register has an undefined value after unwinding (but  should
                                               * really handle the same as `DW_CFA_register_rule_same_value') */
#define DW_CFA_register_rule_same_value     1 /* Register maintains its value after unwinding */
#define DW_CFA_register_rule_offsetn        2 /* Register value is stored at `*(CFA + OFFSET)' */
#define DW_CFA_register_rule_val_offsetn    3 /* Register value is equal to `CFA + OFFSET' */
#define DW_CFA_register_rule_register       4 /* Register value is identical to another register */
#define DW_CFA_register_rule_expression     5 /* Register value is the result of `*eval(EXPR)' */
#define DW_CFA_register_rule_val_expression 6 /* Register value is the result of `eval(EXPR)' */

/* Call Frame Information (section 7.23) */
#define DW_CFA_advance_loc          0x40 /* upc += opcode & 0x3f */
#define DW_CFA_offset               0x80 /* register[opcode & 0x3f] = { DW_CFA_register_rule_offsetn, dwarf_decode_uleb128(&pc) * fde.f_dataalign }; */
#define DW_CFA_restore              0xc0 /* register[opcode & 0x3f] = init_regs[opcode & 0x3f]; */
#define DW_CFA_nop                  0x00 /* nop(); */
#define DW_CFA_set_loc              0x01 /* upc = fde.f_pcstart + dwarf_decode_pointer(&pc, fde.f_ptrenc, ...); */
#define DW_CFA_advance_loc1         0x02 /* upc += *(u8 const *)pc; pc += 1; */
#define DW_CFA_advance_loc2         0x03 /* upc += *(u16 const *)pc; pc += 2; */
#define DW_CFA_advance_loc4         0x04 /* upc += *(u32 const *)pc; pc += 4; */
#define DW_CFA_offset_extended      0x05 /* register[dwarf_decode_uleb128(&pc)] = { DW_CFA_register_rule_offsetn, dwarf_decode_uleb128(&pc) * fde.f_dataalign }; */
#define DW_CFA_restore_extended     0x06 /* r = dwarf_decode_uleb128(&pc); register[r] = init_regs[r]; */
#define DW_CFA_undefined            0x07 /* register[dwarf_decode_uleb128(&pc)] = { DW_CFA_register_rule_undefined }; */
#define DW_CFA_same_value           0x08 /* register[dwarf_decode_uleb128(&pc)] = { DW_CFA_register_rule_same_value }; */
#define DW_CFA_register             0x09 /* register[dwarf_decode_uleb128(&pc)] = { DW_CFA_register_rule_register, dwarf_decode_uleb128(&pc) }; */
#define DW_CFA_remember_state       0x0a /* PUSH({ register, cfa }); */
#define DW_CFA_restore_state        0x0b /* POP({ register, cfa }); */
#define DW_CFA_def_cfa              0x0c /* cfa = { type: UNWIND_CFA_VALUE_REGISTER, reg: dwarf_decode_uleb128(&pc), offset: dwarf_decode_uleb128(&pc) }; */
#define DW_CFA_def_cfa_register     0x0d /* assert(cfa.type == UNWIND_CFA_VALUE_REGISTER); cfa.reg = dwarf_decode_uleb128(&pc); */
#define DW_CFA_def_cfa_offset       0x0e /* assert(cfa.type == UNWIND_CFA_VALUE_REGISTER); cfa.offset = dwarf_decode_uleb128(&pc); */
#define DW_CFA_def_cfa_expression   0x0f /* expr_size = dwarf_decode_uleb128(&pc); cfa = { type: UNWIND_CFA_VALUE_EXPRESSION, expr: { pc, pc + expr_size } }; pc += expr_size; */
#define DW_CFA_expression           0x10 /* reg = dwarf_decode_uleb128(&pc); expr_size = dwarf_decode_uleb128(&pc); register[reg] = { type: DW_CFA_register_rule_expression, expr: { pc, pc + expr_size } }; pc += expr_size; */
#define DW_CFA_offset_extended_sf   0x11 /* register[dwarf_decode_uleb128(&pc)] = { DW_CFA_register_rule_register, dwarf_decode_sleb128(&pc) * fde.f_dataalign }; */
#define DW_CFA_def_cfa_sf           0x12 /* cfa = { type: UNWIND_CFA_VALUE_REGISTER, reg: dwarf_decode_uleb128(&pc), offset: dwarf_decode_sleb128(&pc) * fde.f_dataalign }; */
#define DW_CFA_def_cfa_offset_sf    0x13 /* assert(cfa.type == UNWIND_CFA_VALUE_REGISTER); cfa.offset = dwarf_decode_sleb128(&pc) * fde.f_dataalign; */
#define DW_CFA_val_offset           0x14 /* register[dwarf_decode_uleb128(&pc)] = { DW_CFA_register_rule_val_offsetn, dwarf_decode_uleb128(&pc) }; */
#define DW_CFA_val_offset_sf        0x15 /* register[dwarf_decode_uleb128(&pc)] = { DW_CFA_register_rule_val_offsetn, dwarf_decode_sleb128(&pc) * fde.f_dataalign }; */
#define DW_CFA_val_expression       0x16 /* reg = dwarf_decode_uleb128(&pc); expr_size = dwarf_decode_uleb128(&pc); register[reg] = { type: DW_CFA_register_rule_val_expression, expr: { pc, pc + expr_size } }; pc += expr_size; */
/*      DW_CFA_                     0x17  * ... */
/*      DW_CFA_                     0x18  * ... */
/*      DW_CFA_                     0x19  * ... */
/*      DW_CFA_                     0x1a  * ... */
/*      DW_CFA_                     0x1b  * ... */

/* DWARF Call Frame Instruction (CFI) Extensions (section 10.5.2) */
#define DW_CFA_lo_user                      0x1c /* First extension/custom opcode */
/*      DW_CFA_                             0x1c  * ... */
#define DW_CFA_MIPS_advance_loc8            0x1d /* upc += *(u64 const *)pc; pc += 8; */
/*      DW_CFA_                             0x1e  * ... */
/*      DW_CFA_                             0x1f  * ... */
/*      DW_CFA_                             0x20  * ... */
/*      DW_CFA_                             0x21  * ... */
/*      DW_CFA_                             0x22  * ... */
/*      DW_CFA_                             0x23  * ... */
/*      DW_CFA_                             0x24  * ... */
/*      DW_CFA_                             0x25  * ... */
/*      DW_CFA_                             0x26  * ... */
/*      DW_CFA_                             0x27  * ... */
/*      DW_CFA_                             0x28  * ... */
/*      DW_CFA_                             0x29  * ... */
/*      DW_CFA_                             0x2a  * ... */
/*      DW_CFA_                             0x2b  * ... */
/*      DW_CFA_                             0x2c  * ... */
#define DW_CFA_GNU_window_save              0x2d /* ??? */
#define DW_CFA_AARCH64_negate_ra_state      0x2d /* ??? */
#define DW_CFA_GNU_args_size                0x2e /* landing_pad_adjustment = dwarf_decode_uleb128(&pc); */
#define DW_CFA_GNU_negative_offset_extended 0x2f /* register[dwarf_decode_uleb128(&pc)] = { DW_CFA_register_rule_offsetn, -((signed)dwarf_decode_uleb128(&pc) * fde.f_dataalign) }; */
/*      DW_CFA_                             0x30  * ... */
/*      DW_CFA_                             0x31  * ... */
/*      DW_CFA_                             0x32  * ... */
/*      DW_CFA_                             0x33  * ... */
/*      DW_CFA_                             0x34  * ... */
/*      DW_CFA_                             0x35  * ... */
/*      DW_CFA_                             0x36  * ... */
/*      DW_CFA_                             0x37  * ... */
#define DW_CFA_KOS_startcapsule             0x38 /* Alias for `DW_CFA_remember_state' (except when used in functions with a landing pad) */
#define DW_CFA_KOS_endcapsule               0x39 /* Alias for `DW_CFA_restore_state' (except when used in functions with a landing pad) */
/*      DW_CFA_                             0x3a  * ... */
/*      DW_CFA_                             0x3b  * ... */
/*      DW_CFA_                             0x3c  * ... */
/*      DW_CFA_                             0x3d  * ... */
/*      DW_CFA_                             0x3e  * ... */
/*      DW_CFA_                             0x3f  * ... */
#define DW_CFA_hi_user                      0x3f /* Last extension/custom opcode */




/* Behavior/use for `DW_CFA_KOS_startcapsule' / `DW_CFA_KOS_endcapsule'
 *
 * As  already stated,  these instructions only  have special meaning  when used in
 * functions that also contain a landing pad (similar to how `DW_CFA_GNU_args_size'
 * also only finds special use in such functions)
 *
 * When used, these instructions form "capsules" that can be used to define ranges
 * of CFI instructions that should be executed for the purpose of unwinding,  both
 * during normal unwinding of a function, as well as when unwinding in the context
 * of  jumping to a different location within the same function for the purpose of
 * executing an exception handler. As such, the following is done prior to jumping
 * to any landing pad:
 *
 * >> src_capsule = FIND_INNERMOST_CAPSULE(EXCEPTION_PC);
 * >> if (!src_capsule) {
 * >>     // Capsules aren't used
 * >> } else {
 * >>     // Find the last capsule that should still be unwound
 * >>     dst_capsule  = FIND_INNERMOST_CAPSULE(LANDING_PAD_PC);
 * >>     last_capsule = src_capsule;
 * >>     if (!dst_capsule) {
 * >>         // Unwind until the outer-most capsule.
 * >>         while (last_capsule->parent)
 * >>             last_capsule = last_capsule->parent;
 * >>     } else if (dst_capsule == src_capsule) {
 * >>         // Same capsule (don't unwind anything)
 * >>         goto apply_gnu_args;
 * >>     } else {
 * >>         // Unwind everything until the first capsule shared with the landing pad
 * >>         while (last_capsule->parent !in PARENTS_OF(dst_capsule))
 * >>             last_capsule = last_capsule->parent;
 * >>     }
 * >>
 * >>     // Construct unwinding rules for CFA instrumentation between
 * >>     // last_capsule->dw_cfa_start  (Which points at the byte in .eh_frame after the
 * >>     //                              capsule's `DW_CFA_KOS_startcapsule' opcode byte)
 * >>     // and whatever location marks the end of `EXCEPTION_PC'.
 * >>     // During this construction of rules, the `DW_CFA_KOS_startcapsule'/`DW_CFA_KOS_endcapsule'
 * >>     // opcodes once again behave identical to `DW_CFA_remember_state'/`DW_CFA_restore_state'
 * >>     CONSTRUCT_RULES_FROM_DW_CFA_SUBRANGE(&RULES,
 * >>                                          last_capsule->dw_cfa_start,
 * >>                                          EXCEPTION_PC);
 * >>     UNWIND_WITH_RULES(RULES);
 * >> }
 * >>apply_gnu_args:
 * >> APPLY_GNU_ARGS_SIZE_INSTRUMENTATION(); // DW_CFA_GNU_args_size
 * >> JUMP_TO_LANDING_PAD();
 *
 * Example:
 * >> .Ltry_begin:
 * >>     movq   $0, %rdi
 * >>     movq   $SYS_pipe, %rax
 * >>     std
 * >> .cfi_startcapsule
 * >> .cfi_escape DW_CFA_val_expression               // %rflags.DF = 0
 * >> .cfi_escape CFI_X86_64_UNWIND_REGISTER_RFLAGS
 * >> .cfi_escape 7
 * >> .cfi_escape DW_OP_regx, CFI_X86_64_UNWIND_REGISTER_RFLAGS
 * >> .cfi_escape DW_OP_const2u, EFLAGS_DF & 0xff, EFLAGS_DF >> 8
 * >> .cfi_escape DW_OP_not
 * >> .cfi_escape DW_OP_and
 * >>     syscall
 * >>     cld
 * >> .cfi_endcapsule
 * >> .Ltry_end:
 * >>     ...
 * >> .Lexcept:
 * >>     ...
 *
 * When jumping to `.Lexcept'  as the landing  pad of an  exception thrown by  `syscall',
 * the custom piece  of CFI instrumentation  used to set  `%rflags.DF = 0' will still  be
 * executed,  even though normally  such instrumentation would only  be serviced when the
 * surrounding CFI-proc would get unwound (which isn't the case when `.Lexcept' is jumped
 * to  as the target  of a local landing  pad transition). But  if `.Lexcept' was located
 * within  the same capsule as `syscall' (internally:  .Lexcept would have to be followed
 * by at least 1  additional byte of  program code before  followed by a  .cfi_endcapsule
 * directive), then the  unwind rule  specified by  `.cfi_escape' would  not be  executed
 * (since the landing pad would not leave the capsule)
 *
 * Using capsules, one  is thus  able to  force certain  registers to  be restored  before
 * executing code from a local  landing pad, which is quite  useful when one needs  custom
 * unwinding  behavior for dealing  with exceptions produced by  inline assembly (which is
 * also  the reason  why this extension  was originally created).  Additionally, this also
 * makes it possible to populate registers with custom values based on where in a function
 * an exception originates:
 *
 * >> .cfi_startproc
 * >>
 * >> .Lexcept_begin:
 * >> .cfi_startcapsule
 * >> .cfi_escape ... // Code to unwind %rdi=0
 * >>     call foo
 * >> .cfi_endcapsule
 * >>
 * >> .cfi_startcapsule
 * >> .cfi_escape ... // Code to unwind %rdi=1
 * >>     call bar
 * >> .cfi_endcapsule
 * >>
 * >> .cfi_startcapsule
 * >> .cfi_escape ... // Code to unwind %rdi=2
 * >>     call baz
 * >> .cfi_endcapsule
 * >>
 * >> .Lexcept_end:
 * >>
 * >>     ret
 * >> .Llanding_pad:
 * >>     // The origin of the exception can be deduced from the value of %rdi:
 * >>     //   %rdi == 0: Exception thrown by foo
 * >>     //   %rdi == 1: Exception thrown by bar
 * >>     //   %rdi == 2: Exception thrown by baz
 * >>     ret
 * >> .cfi_endproc
 *
 *
 * Implementation:
 *  - CFI capsules are implemented using 2 new CFI instruction `.cfi_startcapsule' and `.cfi_endcapsule'.
 *  - As far as other tools should be concerned, `.cfi_startcapsule' and `.cfi_endcapsule'
 *    are   just    aliases    for    `.cfi_remember_state'    and    `.cfi_restore_state'
 *  - For compatibility, `DW_CFA_GNU_args_size' instrumentation is not affected by  capsules.
 *    As  such, using capsules to alter the value of the stack-pointer while a non-zero value
 *    for `DW_CFA_GNU_args_size' is in effect results in weak undefined behavior (that is: it
 *    is undefined in which order capsule/DW_CFA_GNU_args_size adjustments are performed)
 *  - CFI capsules may not be used inside of initialization text (f_inittext), but can only
 *    appear inside of eval-text (f_evaltext)
 *
 * A patch to (among other things) enable  support for this extension by binutils  can
 * be found as part of the KOS source tree under /kos/misc/patches/binutils-2.38.patch
 */






/* === The confusing and weird difference between `DW_OP_reg0' and `DW_OP_breg0 $0' ===
 *
 * First and foremost, we're talking about the difference between
 * `UNWIND_STE_REGISTER' and  `UNWIND_STE_REGPOINTER'  here.  For
 * that purpose, take a look at  the 2 listings of how  different
 * stack values are interpreted below.
 *
 * You  should be able  to see that  for unwinding (iow: .eh_frame
 * expressions) and for arithmetic (iow:  when used in as  operand
 * of another instruction such as DW_OP_plus), both register value
 * and register pointer operands behave exactly the same.  However
 * there is a  difference when  these opcodse appear  inside of  a
 * location  expression (iow: .debug_info).  Here, the second list
 * of  interpretations  must  be used,  where  `DW_OP_breg0' would
 * use a register's value (plus addend) as the address of a memory
 * location  that  contains the  associated variable's  value. But
 * `DW_OP_reg0' would specify that  the register's value _is_  the
 * value of the associated variable.
 *
 * Also note that (for some  reason?) GDB _really_ doesn't like  it
 * when you use DW_OP_reg0, and will often refuse to do the unwind.
 */


/* Type codes for `unwind_ste_t::s_type'
 * Effective stack values (for unwinding or arithmetic):
 *   UNWIND_STE_CONSTANT:     s_uconst or s_sconst
 *   UNWIND_STE_STACKVALUE:   s_uconst or s_sconst
 *   UNWIND_STE_REGISTER:     REGISTER[s_register] + s_regoffset
 *   UNWIND_STE_REGPOINTER:   REGISTER[s_register] + s_regoffset
 *   UNWIND_STE_RW_LVALUE:    (byte_t(*)[s_lsize])s_lvalue
 *   UNWIND_STE_RO_LVALUE:    (byte_t(*)[s_lsize])s_lvalue
 *
 * Effective return values (for location expressions):
 *   UNWIND_STE_CONSTANT:     result = *(<unspecified> *)s_uconst
 *   UNWIND_STE_STACKVALUE:   result = s_uconst
 *   UNWIND_STE_REGISTER:     result = *(<unspecified> *)(REGISTER[s_register] + s_regoffset)
 *   UNWIND_STE_REGPOINTER:   result = REGISTER[s_register] + s_regoffset
 *   UNWIND_STE_RW_LVALUE:    result = *(byte_t(*)[s_lsize])s_lvalue
 *   UNWIND_STE_RO_LVALUE:    result = *(byte_t(*)[s_lsize])s_lvalue   // May only be read from
 */
#define UNWIND_STE_CONSTANT   0 /* Constant value */
#define UNWIND_STE_STACKVALUE 1 /* On-stack constant value (Same as `UNWIND_STE_CONSTANT') */
#define UNWIND_STE_REGISTER   2 /* Register value */
#define UNWIND_STE_REGPOINTER 3 /* Pointer-to-register (value is the imaginary address of the register in the register map) */
#define UNWIND_STE_RW_LVALUE  4 /* Read-write l-value */
#define UNWIND_STE_RO_LVALUE  5 /* Read-only l-value */

/* Default value for `ue_bjmprem' */
#define UNWIND_EMULATOR_BJMPREM_DEFAULT 0x800

#ifdef __CC__
__DECL_BEGIN

#ifndef __unwind_regno_t_defined
#define __unwind_regno_t_defined
typedef __UINTPTR_HALF_TYPE__ unwind_regno_t;
#endif /* !__unwind_regno_t_defined */

typedef struct {
	/* Stack entry for unwind expressions. */
	__uint8_t           s_type;      /* Stack entry type (One of `UNWIND_STE_*') */
	__uint8_t           s_pad[(sizeof(__uintptr_t) / 2) - 1];
	union {
		unwind_regno_t  s_lsize;     /* [UNWIND_STE_RW_LVALUE] Size of an L-value expression in bytes (If unknown, set to `0') */
		unwind_regno_t  s_register;  /* [UNWIND_STE_REGISTER] Register ID */
	};
	union {
		__uintptr_t     s_uconst;    /* Unsigned constant value */
		__intptr_t      s_sconst;    /* Signed constant value */
		__intptr_t      s_regoffset; /* Offset added to a register expression */
		__NCX __byte_t *s_lvalue;    /* L-value pointer. */
	};
} unwind_ste_t;

/* Read out the contents of a CFI register `dw_regno' and store their value in `dst'
 * The size of the `dst' buffer depends on `dw_regno' and can be calculated with the
 * arch-specific `CFI_REGISTER_SIZE()' macro.
 * @param: dw_regno: One of `CFI_[ARCH]_UNWIND_REGISTER_[NAME]'
 * @param: dst:      A  buffer  of  `CFI_REGISTER_SIZE(dw_regno)'
 *                   bytes, to-be filled with the register value.
 * @return: UNWIND_SUCCESS:          Success (only in this case will `*dst' be valid / `*src' have been used)
 * @return: UNWIND_INVALID_REGISTER: The given `dw_regno' is invalid/unsupported.
 * @return: UNWIND_OPTIMIZED_AWAY:   Register information has been optimized away.
 * @return: * :                      Some other error (propagate) */
typedef __ATTR_NONNULL_T((3)) unwind_errno_t (LIBUNWIND_CC *unwind_getreg_t)(void const *__arg, unwind_regno_t __dw_regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((3)) unwind_errno_t (LIBUNWIND_CC *unwind_setreg_t)(void *__arg, unwind_regno_t __dw_regno, void const *__restrict __src);

typedef struct unwind_emulator_sections_struct {
	/* NOTE: When individual sections are empty, the associated instructions become illegal
	 * NOTE: The order of members in this struct is important!
	 *       s.a. `Section containers & overlap' in `/kos/include/libdebuginfo/debug_info.h' */
	__NCX __byte_t const *ues_eh_frame_hdr_start;   /* [0..1][const] `.eh_frame_hdr' start (for `DW_OP_call_frame_cfa') */
	__NCX __byte_t const *ues_eh_frame_hdr_end;     /* [0..1][const] `.eh_frame_hdr' end */
	__NCX __byte_t const *ues_eh_frame_start;       /* [0..1][const] `.eh_frame' start (for `DW_OP_call_frame_cfa') */
	__NCX __byte_t const *ues_eh_frame_end;         /* [0..1][const] `.eh_frame' end */
	__NCX __byte_t const *ues_debug_frame_start;    /* [0..1][const] `.debug_frame' start (for `DW_OP_call_frame_cfa') */
	__NCX __byte_t const *ues_debug_frame_end;      /* [0..1][const] `.debug_frame' end */
	__NCX __byte_t const *ues_debug_addr_start;     /* [0..1][const] `.debug_addr' start (for `DW_OP_addrx' / `DW_OP_constx') */
	__NCX __byte_t const *ues_debug_addr_end;       /* [0..1][const] `.debug_addr' end */
	__NCX __byte_t const *ues_debug_loclists_start; /* [0..1][const] `.debug_loclists' start (for `DW_OP_call2' / `DW_OP_call4') */
	__NCX __byte_t const *ues_debug_loclists_end;   /* [0..1][const] `.debug_loclists' end */
	__NCX __byte_t const *ues_debug_loc_start;      /* [0..1][const] `.debug_loc' start (for `DW_OP_call2' / `DW_OP_call4') */
	__NCX __byte_t const *ues_debug_loc_end;        /* [0..1][const] `.debug_loc' end */
	__NCX __byte_t const *ues_debug_abbrev_start;   /* [0..1][const] `.debug_abbrev' start (for `DW_OP_call2' / `DW_OP_call4') */
	__NCX __byte_t const *ues_debug_abbrev_end;     /* [0..1][const] `.debug_abbrev' end */
	__NCX __byte_t const *ues_debug_info_start;     /* [0..1][const] `.debug_info' start (for `DW_OP_call2' / `DW_OP_call4') */
	__NCX __byte_t const *ues_debug_info_end;       /* [0..1][const] `.debug_info' end */
} unwind_emulator_sections_t;

#ifndef __di_debuginfo_location_t_defined
#define __di_debuginfo_location_t_defined
typedef struct di_debuginfo_location_struct {
	__NCX __byte_t const *l_expr;   /* [0..1] Pointer to a CFI expression (for use with `unwind_emulator_exec') for the pointed-to expression. */
	__NCX __byte_t const *l_llist4; /* [0..1] Pointer to a CFI location list (points into the `.debug_loc' section). */
	__NCX __byte_t const *l_llist5; /* [0..1] Pointer to a CFI location list (points into the `.debug_loclists' section). */
} di_debuginfo_location_t;
#endif /* !__di_debuginfo_location_t_defined */

struct unwind_bases {
	__NCX void const *ub_tbase; /* [0..1] Text base address (lazily calculated when set to `NULL'; s.a. `DLAUXCTRL_GET_TEXTBASE') */
	__NCX void const *ub_dbase; /* [0..1] Data base address (lazily calculated when set to `NULL'; s.a. `DLAUXCTRL_GET_DATABASE') */
	__NCX void const *ub_fbase; /* [0..1] Function base address (or `NULL' if unknown or not applicable). */
};


struct di_debuginfo_compile_unit_simple_struct;
typedef struct unwind_emulator_struct {
	unwind_ste_t                     *ue_stack;              /* [0..ue_stacksz|ALLOC(ue_stackmax)][const] Value stack for the emulator. */
	__size_t                          ue_stacksz;            /* Currently used stack size. */
	__size_t                          ue_stackmax;           /* [const] Max available stack size. */
	__NCX __byte_t const             *ue_pc;                 /* [1..1] Program counter position. */
	__NCX __byte_t const             *ue_pc_start;           /* [1..1][const] Program start pointer. */
	__NCX __byte_t const             *ue_pc_end;             /* [1..1][const] Program end pointer. */
	unwind_emulator_sections_t const *ue_sectinfo;           /* [0..1][const] Emulator section information. */
	unwind_getreg_t                   ue_regget;             /* [1..1][const] Callback for reading out the value of a register. */
	unwind_setreg_t                   ue_regset;             /* [0..1][const] Callback for writing the value of a register (or NULL
	                                                          * if registers are read-only; ignored when `ue_piecewrite' is false). */
	void const                       *ue_regget_arg;         /* [?..?][const] Argument passed to `ue_regget'. */
	void                             *ue_regset_arg;         /* [?..?][const] Argument passed to `ue_regset'. */
	di_debuginfo_location_t const    *ue_framebase;          /* [0..1][const] Frame base expression (for use with `DW_OP_fbreg').
	                                                          * Set to NULL to consider `DW_OP_fbreg' as an illegal  instruction. */
	__uintptr_t                       ue_addroffset;         /* [const] Offset added to the value of `DW_OP_addr'. For .eh_frame, this should be `0', but
	                                                          *         for all other purposes, this should be the loadaddr of the associated module. */
	__NCX void                       *ue_objaddr;            /* [0..1][const] Object address value (for use with `DW_OP_push_object_address').
	                                                          * Set to NULL to consider `DW_OP_push_object_address' as an illegal instruction. */
	__uint32_t                        ue_bjmprem;            /* Number of remaining allowed backwards-jumps  (used to prevent infinite  loops,
	                                                          * which  get  terminated  and  cause  `UNWIND_EMULATOR_LOOP'  to  be   returned)
	                                                          * During initialization, you may simply assign `UNWIND_EMULATOR_BJMPREM_DEFAULT'
	                                                          * to this field. */
	__uint8_t                         ue_addrsize;           /* [const] Address size (one of 1,2,4 or 8) (operand size of `DW_OP_addr') */
	__uint8_t                         ue_ptrsize;            /* [const] DWARF pointer size (4 for 32-bit dwarf; 8 for 64-bit dwarf) */
	__uint8_t                         ue_piecewrite;         /* [const] Non-zero if data pieces should be written, rather than read. */
	__uint8_t                         ue_pad;                /* ... */
	__NCX __byte_t                   *ue_piecebuf;           /* [0..ue_piecesiz][const] Pointer to a buffer to receive data from `DW_OP_piece' */
	__size_t                          ue_piecesiz;           /* [const] Size of the `ue_piecebuf' buffer in bytes. */
	__size_t                          ue_piecebits;          /* [<= ue_piecesiz * 8] Number of _BITS_ within the `ue_piecebuf' buffer that are in use. */
	__uintptr_t                       ue_call_frame_cfa;     /* [0..1] Lazily calculated value for the call-frame-CFA of the given register state.
	                                                          * When   set   to   ZERO(0),   this   value   is   calculated   as-needed,    using:
	                                                          *  - unwind_fde_scan(ue_eh_frame_start, ue_eh_frame_end, ...)
	                                                          *  - unwind_fde_exec(...) */
	struct unwind_bases               ue_bases;              /* Base addresses. (may be calculated lazily) */
	struct di_debuginfo_compile_unit_simple_struct const
	                                 *ue_cu;                 /* [0..1][const] The associated CU (when non-NULL, fields that may be used
	                                                          * are  listed  in the  documentation  of `debuginfo_location_getvalue()') */
	__uintptr_t                       ue_module_relative_pc; /* [const] Module-relative program counter position (used for selecting callbacks within expression lists) */
	__NCX __byte_t                   *ue_tlsbase;            /* [0..1] Base to-be added to an offset in order to form a TLS address within the
	                                                          * targeted thread (or `NULL' if unknown, in which case  `DW_OP_form_tls_address'
	                                                          * is considered an illegal instruction, or `(__byte_t *)-1' to lazily calculate) */
} unwind_emulator_t;

/* Execute the CFI expression loaded into the given unwind-emulator  `self'.
 * Upon  success, `self->ue_stacksz' will have been updated to the new stack
 * size, allowing the caller to read the expression's return values from it.
 * NOTE: `unwind_emulator_exec_autostack()'  behaves the same as `unwind_emulator_exec()', but
 *       will automatically  allocated/free the  expression stack  upon entry/return,  pushing
 *       `pentry_stack_top' upon entry, and storing the last stack-entry in `*pexit_stack_top'
 *       before returning  (if  no  such value  exists,  `UNWIND_EMULATOR_NO_RETURN_VALUE'  is
 *       returned). If no  stack of sufficient  size could  be allocated (or  if the  required
 *       stack size  is absurdly  large),  `UNWIND_EMULATOR_STACK_OVERFLOW' will  be  returned
 *       instead.
 * @param: pentry_stack_top:      A value to-be pushed onto the stack upon entry (or NULL).
 * @param: pexit_stack_top:       A value to-be popped off of the stack upon exit (or NULL).
 * @param: pexit_stack_top_const: Same as `pexit_stack_top', but casted into a constant.
 * @return: UNWIND_SUCCESS:          ...
 * @return: UNWIND_INVALID_REGISTER: ...
 * @return: UNWIND_SEGFAULT:         ...
 * @return: UNWIND_BADALLOC:         ...
 * @return: UNWIND_EMULATOR_*:       ... */
typedef __ATTR_NONNULL_T((1)) unwind_errno_t
(LIBUNWIND_CC *PUNWIND_EMULATOR_EXEC)(unwind_emulator_t *__restrict __self);
typedef __ATTR_NONNULL_T((1)) unwind_errno_t
(LIBUNWIND_CC *PUNWIND_EMULATOR_EXEC_AUTOSTACK)(unwind_emulator_t *__restrict __self,
                                                unwind_ste_t const *__pentry_stack_top,
                                                unwind_ste_t *__pexit_stack_top,
                                                __uintptr_t *__pexit_stack_top_const);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1)) unwind_errno_t LIBUNWIND_CC
unwind_emulator_exec(unwind_emulator_t *__restrict __self);
LIBUNWIND_DECL __ATTR_NONNULL((1)) unwind_errno_t LIBUNWIND_CC
unwind_emulator_exec_autostack(unwind_emulator_t *__restrict __self,
                               unwind_ste_t const *__pentry_stack_top,
                               unwind_ste_t *__pexit_stack_top,
                               __uintptr_t *__pexit_stack_top_const);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Load the effective l-value address of `self' into `*p_addr':
 *   UNWIND_STE_CONSTANT:     Write-back s_uconst or s_sconst
 *   UNWIND_STE_STACKVALUE:   Write-back s_uconst or s_sconst
 *   UNWIND_STE_REGISTER:     Write-back REGISTER[s_register] + s_regoffset
 *   UNWIND_STE_REGPOINTER:   Write-back REGISTER[s_register]       (NOTE: Technically, this case isn't allowed)
 *   UNWIND_STE_RW_LVALUE:    Write-back s_lvalue
 *   UNWIND_STE_RO_LVALUE:    Write-back s_lvalue
 * @return: UNWIND_SUCCESS:                      Success.
 * @return: UNWIND_INVALID_REGISTER:             Invalid register referenced by `self'
 * @return: UNWIND_EMULATOR_ILLEGAL_INSTRUCTION: Invalid stack-value type in `self' */
typedef __ATTR_NONNULL_T((1, 2)) __ATTR_OUT_T(4) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_STE_ADDR)(unwind_ste_t const *__restrict __self,
                                                unwind_getreg_t __regget, void const *__regget_arg,
                                                __NCX void **__restrict __p_addr);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 2)) __ATTR_OUT(4) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_ste_addr)(unwind_ste_t const *__restrict __self,
                                            unwind_getreg_t __regget, void const *__regget_arg,
                                            __NCX void **__restrict __p_addr);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Read/write bit-wise data to/from an unwind stack-entry location.
 * @param: self:           The unwind STE-element to/from which to read/write.
 * @param: regget:         Register getter.
 * @param: regget_arg:     Register getter argument.
 * @param: regset:         Register setter.
 * @param: regset_arg:     Register setter argument.
 * @param: dst:            Destination memory buffer.
 * @param: src:            Source memory buffer.
 * @param: num_bits:       The # of bits to read/write to/from `dst' or `src'
 * @param: src_left_shift: The # of leading bits to leave unchanged in the source.
 * @param: dst_left_shift: The # of leading bits to leave unchanged in the destination.
 * @return: UNWIND_SUCCESS:                      Success.
 * @return: UNWIND_INVALID_REGISTER:             Invalid register referenced by `self'
 * @return: UNWIND_EMULATOR_ILLEGAL_INSTRUCTION: Invalid stack-value type in `self'
 * @return: UNWIND_SEGFAULT:                     Attempted to access faulty memory. */
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_STE_READ)(unwind_ste_t const *__restrict __self, __uint8_t __addrsize,
                                                unwind_getreg_t __regget, void const *__regget_arg,
                                                __NCX void *__dst, __size_t __num_bits,
                                                __size_t __dst_left_shift, __size_t __src_left_shift);
typedef __ATTR_NONNULL_T((1, 3)) unwind_errno_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_STE_WRITE)(unwind_ste_t const *__restrict __self, __uint8_t __addrsize,
                                                 /*[1..1]*/ unwind_getreg_t __regget, void const *__regget_arg,
                                                 /*[0..1]*/ unwind_setreg_t __regset, void *__regset_arg,
                                                 __NCX void const *__src, __size_t __num_bits,
                                                 __size_t __dst_left_shift, __size_t __src_left_shift);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_ste_read)(unwind_ste_t const *__restrict __self, __uint8_t __addrsize,
                                            unwind_getreg_t __regget, void const *__regget_arg,
                                            __NCX void *__dst, __size_t __num_bits,
                                            __size_t __dst_left_shift, __size_t __src_left_shift);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unwind_errno_t
__NOTHROW_NCX(LIBUNWIND_CC unwind_ste_write)(unwind_ste_t const *__restrict __self, __uint8_t __addrsize,
                                             /*[1..1]*/ unwind_getreg_t __regget, void const *__regget_arg,
                                             /*[0..1]*/ unwind_setreg_t __regset, void *__regset_arg,
                                             __NCX void const *__src, __size_t __num_bits,
                                             __size_t __dst_left_shift, __size_t __src_left_shift);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Return a pointer to the next unwind instruction following `unwind_pc'
 * -> Useful for dumping unwind instruction without having to take care
 *    of handling all possible instruction  (after all: CFI has a  CISC
 *    instruction set with variable-length instructions)
 * @param: addrsize: Size of a target address.
 * @param: ptrsize:  Size of a DWARF pointer (4 for 32-bit dwarf; 8 for 64-bit dwarf).
 * @return: NULL: The instruction at `unwind_pc' wasn't recognized. */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __NCX __byte_t const *
__NOTHROW_NCX_T(LIBUNWIND_CC *PUNWIND_INSTRUCTION_SUCC)(__NCX __byte_t const *__unwind_pc,
                                                        __uint8_t __addrsize, __uint8_t __ptrsize);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_PURE __ATTR_WUNUSED __NCX __byte_t const *
__NOTHROW_NCX(LIBUNWIND_CC unwind_instruction_succ)(__NCX __byte_t const *__unwind_pc,
                                                    __uint8_t __addrsize, __uint8_t __ptrsize);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

/* Return a pointer to a CFI expression that is applicable for `module_relative_pc'
 * If no such expression exists, return `NULL' instead. */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __ATTR_OUT_T(5) __NCX __byte_t *
__NOTHROW_NCX_T(LIBUNWIND_CC *PDEBUGINFO_LOCATION_SELECT)(di_debuginfo_location_t const *__restrict __self,
                                                          __uintptr_t __cu_base,
                                                          __uintptr_t __module_relative_pc,
                                                          __uint8_t __addrsize,
                                                          __size_t *__restrict __p_expr_length);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_OUT(5) __byte_t *
__NOTHROW_NCX(LIBUNWIND_CC debuginfo_location_select)(di_debuginfo_location_t const *__restrict __self,
                                                      __uintptr_t __cu_base,
                                                      __uintptr_t __module_relative_pc,
                                                      __uint8_t __addrsize,
                                                      __size_t *__restrict __p_expr_length);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



struct di_debuginfo_compile_unit_simple_struct;
/* Read/Write the value associated with a given debuginfo location descriptor.
 * @param: self:                  The debug info location descriptor (s.a. libdebuginfo.so)
 * @param: sectinfo:              Emulator section  information  (to-be  filled in  by  the  caller)
 *                                Optionally,  this argument may  be `NULL', however  if this is the
 *                                case, the function may fail in cases where it would have otherwise
 *                                succeeded.
 * @param: regget:                Register getter callback.
 * @param: regget_arg:            Register getter callback argument.
 * @param: regset:                Register setter callback.
 * @param: regset_arg:            Register setter callback argument.
 * @param: cu:                    Associated compilation unit debug info (or NULL).
 *                                When  non-NULL, the following fields may be used:
 *                                  - cu->cu_ranges.r_startpc
 *                                  - cu->cu_addr_base
 * @param: module_relative_pc:    The module-relative program counter, to-be used to select
 *                                the   appropriate  expression  within  a  location  list.
 * @param: module_addroffset:     The load address of the associated module. (addend for DW_OP_addr)
 * @param: buf:                   Source/target buffer containing the value read from,
 *                                or written to the location expression.
 * @param: bufsize:               Size of the given `buf' in bytes.
 * @param: pnum_written_bits:     The number of _BITS_ (not bytes!) read from the location expression,
 *                                and written to the given `buf'  (any trailing bits of buffer  memory
 *                                that weren't written will be filled with `0' upon success)
 * @param: pnum_read_bits:        The number of _BITS_ (not bytes!) written to the location expression,
 *                                and read from the given `buf'.
 * @param: frame_base_expression: The expression used to calculate the frame-base address (or NULL if unknown)
 * @param: objaddr:               The address of the base-object (used e.g. for structure member expressions)
 * @param: addrsize:              Size of an address (defined by the associated CU, and usually == sizeof(void *))
 * @param: ptrsize:               DWARF pointer size (4 for 32-bit dwarf; 8 for 64-bit dwarf)
 * @return: * :                               One of `UNWIND_*'
 * @return: UNWIND_EMULATOR_NOT_WRITABLE:     Attempted to write to a read-only location expression.
 * @return: UNWIND_EMULATOR_BUFFER_TOO_SMALL: The given `bufsize' is too small.
 * @return: UNWIND_EMULATOR_NO_FUNCTION:      The associated location list is undefined for `module_relative_pc' */
typedef __ATTR_NONNULL_T((1, 3, 10)) unwind_errno_t
(LIBUNWIND_CC *PDEBUGINFO_LOCATION_GETVALUE)(di_debuginfo_location_t const *__restrict __self,
                                             unwind_emulator_sections_t const *__sectinfo,
                                             unwind_getreg_t __regget, void *__regget_arg,
                                             struct di_debuginfo_compile_unit_simple_struct const *__cu,
                                             __uintptr_t __module_relative_pc,
                                             __uintptr_t __module_addroffset,
                                             __NCX void *__buf, __size_t __bufsize,
                                             __size_t *__restrict __pnum_written_bits,
                                             di_debuginfo_location_t const *__frame_base_expression,
                                             __NCX void const *__objaddr, __uint8_t __addrsize, __uint8_t __ptrsize);
typedef __ATTR_NONNULL_T((1, 3, 5, 12)) unwind_errno_t
(LIBUNWIND_CC *PDEBUGINFO_LOCATION_SETVALUE)(di_debuginfo_location_t const *__restrict __self,
                                             unwind_emulator_sections_t const *__sectinfo,
                                             unwind_getreg_t __regget, void *__regget_arg,
                                             unwind_setreg_t __regset, void *__regset_arg,
                                             struct di_debuginfo_compile_unit_simple_struct const *__cu,
                                             __uintptr_t __module_relative_pc,
                                             __uintptr_t __module_addroffset,
                                             __NCX void const *__buf, __size_t __bufsize,
                                             __size_t *__restrict __pnum_read_bits,
                                             di_debuginfo_location_t const *__frame_base_expression,
                                             __NCX void *__objaddr, __uint8_t __addrsize, __uint8_t __ptrsize);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3, 10)) unwind_errno_t LIBUNWIND_CC
debuginfo_location_getvalue(di_debuginfo_location_t const *__restrict __self,
                            unwind_emulator_sections_t const *__sectinfo,
                            unwind_getreg_t __regget, void *__regget_arg,
                            struct di_debuginfo_compile_unit_simple_struct const *__cu,
                            __uintptr_t __module_relative_pc,
                            __uintptr_t __module_addroffset,
                            __NCX void *__buf, __size_t __bufsize,
                            __size_t *__restrict __pnum_written_bits,
                            di_debuginfo_location_t const *__frame_base_expression,
                            __NCX void const *__objaddr, __uint8_t __addrsize, __uint8_t __ptrsize);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3, 5, 12)) unwind_errno_t LIBUNWIND_CC
debuginfo_location_setvalue(di_debuginfo_location_t const *__restrict __self,
                            unwind_emulator_sections_t const *__sectinfo,
                            unwind_getreg_t __regget, void *__regget_arg,
                            unwind_setreg_t __regset, void *__regset_arg,
                            struct di_debuginfo_compile_unit_simple_struct const *__cu,
                            __uintptr_t __module_relative_pc,
                            __uintptr_t __module_addroffset,
                            __NCX void const *__buf, __size_t __bufsize,
                            __size_t *__restrict __pnum_read_bits,
                            di_debuginfo_location_t const *__frame_base_expression,
                            __NCX void *__objaddr, __uint8_t __addrsize, __uint8_t __ptrsize);
#endif /* LIBUNWIND_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */


#endif /* !_LIBUNWIND_CFI_H */
