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
#ifndef _CFI_H
#define _CFI_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>

#include <asm/cfi.h>

#ifndef __COMPILER_NO_GCC_ASM_MACROS
__ASM_BEGIN

#if defined(__GNUC__) && defined(__KOS__)
#ifndef __GCC_HAVE_DWARF2_CFI_ASM
#define __GCC_HAVE_DWARF2_CFI_ASM
#endif /* !__GCC_HAVE_DWARF2_CFI_ASM */
#elif !defined(__GCC_HAVE_DWARF2_CFI_ASM)
/* Delete CFI annotations from generated assembly */
__ASM_L(.macro .cfi_sections args:vararg; .endm)
__ASM_L(.macro .cfi_startproc args:vararg; .endm)
__ASM_L(.macro .cfi_endproc args:vararg; .endm)
__ASM_L(.macro .cfi_personality args:vararg; .endm)
__ASM_L(.macro .cfi_personality_id args:vararg; .endm)
__ASM_L(.macro .cfi_fde_data args:vararg; .endm)
__ASM_L(.macro .cfi_lsda args:vararg; .endm)
__ASM_L(.macro .cfi_inline_lsda args:vararg; .endm)
__ASM_L(.macro .cfi_def_cfa args:vararg; .endm)
__ASM_L(.macro .cfi_def_cfa_register args:vararg; .endm)
__ASM_L(.macro .cfi_def_cfa_offset args:vararg; .endm)
__ASM_L(.macro .cfi_adjust_cfa_offset args:vararg; .endm)
__ASM_L(.macro .cfi_offset args:vararg; .endm)
__ASM_L(.macro .cfi_val_offset args:vararg; .endm)
__ASM_L(.macro .cfi_rel_offset args:vararg; .endm)
__ASM_L(.macro .cfi_register args:vararg; .endm)
__ASM_L(.macro .cfi_restore args:vararg; .endm)
__ASM_L(.macro .cfi_undefined args:vararg; .endm)
__ASM_L(.macro .cfi_same_value args:vararg; .endm)
__ASM_L(.macro .cfi_remember_state args:vararg; .endm)
__ASM_L(.macro .cfi_restore_state args:vararg; .endm)
__ASM_L(.macro .cfi_return_column args:vararg; .endm)
__ASM_L(.macro .cfi_signal_frame args:vararg; .endm)
__ASM_L(.macro .cfi_window_save args:vararg; .endm)
__ASM_L(.macro .cfi_escape args:vararg; .endm)
__ASM_L(.macro .cfi_val_encoded_addr args:vararg; .endm)
#endif /* __GCC_HAVE_DWARF2_CFI_ASM */

/* NOTE: CFI capsules are currently restricted to KOS+!KERNEL.
 *       s.a.          `LIBUNWIND_CONFIG_SUPPORT_CFI_CAPSULES' */
#if defined(__KOS__) && !defined(__KERNEL__)
__ASM_L(.macro .cfi_startcapsule)
__ASM_L(	.cfi_escape 0x38)
__ASM_L(.endm)
__ASM_L(.macro .cfi_endcapsule)
__ASM_L(	.cfi_escape 0x39)
__ASM_L(.endm)
#endif /* __KOS__ && !__KERNEL__ */

__ASM_L(.macro .cfi_escape_uleb128 value:req)
__ASM_L(	.if (__ASM_ARG(\value)) <= 0x7f)
__ASM_L(		.cfi_escape __ASM_ARG(\value))
__ASM_L(	.else)
__ASM_L(		.cfi_escape ((__ASM_ARG(\value)) & 0x7f) | 0x80)
__ASM_L(		.cfi_escape_uleb128 (__ASM_ARG(\value)) >> 7)
__ASM_L(	.endif)
__ASM_L(.endm)

__ASM_L(.macro .cfi_escape_sleb128 value:req)
__ASM_L(	.Lbyte = (__ASM_ARG(\value)) & 0x7f)
__ASM_L(	.if (__ASM_ARG(\value)) >= 0)
__ASM_L(		.Lvalue = (__ASM_ARG(\value)) / 128)
__ASM_L(	.else)
__ASM_L(		.Lvalue = ~(~(__ASM_ARG(\value)) / 128))
__ASM_L(	.endif)
__ASM_L(	.if ((.Lvalue == 0) && ((.Lbyte & 0x40) == 0)) || ((.Lvalue == -1) && ((.Lbyte & 0x40) != 0)))
__ASM_L(		.cfi_escape .Lbyte)
__ASM_L(	.else)
__ASM_L(		.cfi_escape .Lbyte | 0x80)
__ASM_L(		.cfi_escape_sleb128 .Lvalue)
__ASM_L(	.endif)
__ASM_L(.endm)

__ASM_L(.macro __cfi_escape_breg regno:req)
__ASM_L(	.cfi_escape 0x70 + __ASM_ARG(\regno))
__ASM_L(.endm)


/* Encode a CFI register restore: `%dst = *(offset + %src)' */
__ASM_L(.macro .cfi_reg_offset dst:req, offset:req, src:req)
__ASM_L(.ifc __ASM_ARG(\src),%cfa)
__ASM_L(	.cfi_rel_offset __ASM_ARG(\dst), __ASM_ARG(\offset))
__ASM_L(.else)
__ASM_L(	.cfi_escape 0x10) /* DW_CFA_expression */
__ASM_L(	__cfi_decode_register .cfi_escape_uleb128, __ASM_ARG(\dst))
__ASM_L(	.pushsection .discard)
__ASM_L(	.Lcfi_reg_offset_text_start = .)
__ASM_L(		.sleb128 __ASM_ARG(\offset))
__ASM_L(	.Lcfi_reg_offset_text_size = 1 + (. - .Lcfi_reg_offset_text_start))
__ASM_L(	.popsection)
__ASM_L(	.cfi_escape_uleb128 .Lcfi_reg_offset_text_size)
__ASM_L(	__cfi_decode_register __cfi_escape_breg, __ASM_ARG(\src)) /* DW_OP_breg0 + offset */
__ASM_L(	.cfi_escape_sleb128 __ASM_ARG(\offset))
__ASM_L(.endif)
__ASM_L(.endm)

/* Encode a CFI register restore: `%dst = offset + %src' */
__ASM_L(.macro .cfi_reg_value dst:req, offset:req, src:req)
__ASM_L(.ifc __ASM_ARG(\src),%cfa)
__ASM_L(	.cfi_rel_offset __ASM_ARG(\dst), __ASM_ARG(\offset))
__ASM_L(.else)
__ASM_L(	.cfi_escape 0x16) /* DW_CFA_val_expression */
__ASM_L(	__cfi_decode_register .cfi_escape_uleb128, __ASM_ARG(\dst))
__ASM_L(	.pushsection .discard)
__ASM_L(	.Lcfi_reg_offset_text_start = .)
__ASM_L(		.sleb128 __ASM_ARG(\offset))
__ASM_L(	.Lcfi_reg_offset_text_size = 1 + (. - .Lcfi_reg_offset_text_start))
__ASM_L(	.popsection)
__ASM_L(	.cfi_escape_uleb128 .Lcfi_reg_offset_text_size)
__ASM_L(	__cfi_decode_register __cfi_escape_breg, __ASM_ARG(\src)) /* DW_OP_breg0 + offset */
__ASM_L(	.cfi_escape_sleb128 __ASM_ARG(\offset))
__ASM_L(.endif)
__ASM_L(.endm)


/* Encode a CFI register restore: `%dst = value' */
__ASM_L(.macro .cfi_reg_const dst:req, value:req)
__ASM_L(	.cfi_escape 0x16) /* DW_CFA_val_expression */
__ASM_L(	__cfi_decode_register .cfi_escape_uleb128, __ASM_ARG(\dst))
__ASM_L(	.pushsection .discard)
__ASM_L(	.Lcfi_reg_offset_text_start = .)
__ASM_L(		.uleb128 __ASM_ARG(\value))
__ASM_L(	.Lcfi_reg_offset_text_size = 1 + (. - .Lcfi_reg_offset_text_start))
__ASM_L(	.popsection)
__ASM_L(	.cfi_escape_uleb128 .Lcfi_reg_offset_text_size)
__ASM_L(	.cfi_escape 0x10) /* DW_OP_constu */
__ASM_L(	.cfi_escape_uleb128 __ASM_ARG(\value))
__ASM_L(.endm)

__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_CFI_H */
