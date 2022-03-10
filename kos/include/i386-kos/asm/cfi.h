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
#ifndef _I386_KOS_ASM_CFI_H
#define _I386_KOS_ASM_CFI_H 1

#include <__stdinc.h>
#include <hybrid/__asm.h>
#include <hybrid/host.h>

#ifdef __x86_64__
#ifdef __KERNEL__
#include <kernel/x86/fsgsbase.h>
#endif /* __KERNEL__ */
#endif /* __x86_64__ */

/* Reminder on how `pop' functions with a stack-operand:
 * >> #include <stdio.h>
 * >> int main() {
 * >>     int value;
 * >>     __asm__("pushl $0\n"
 * >>             "pushl $42\n"
 * >>             "popl  0(%%esp)\n" // This overrides the `0' above! (meaning the new SP is used as base address)
 * >>             "popl  %0\n"
 * >>             : "=r" (value));
 * >>     printf("value = %d\n",value); // 42
 * >>     return 0;
 * >> }
 */

#ifndef __COMPILER_NO_GCC_ASM_MACROS
__ASM_BEGIN

#if defined(__GNUC__) && defined(__KOS__)
#ifndef __GCC_HAVE_DWARF2_CFI_ASM
#define __GCC_HAVE_DWARF2_CFI_ASM
#endif /* !__GCC_HAVE_DWARF2_CFI_ASM */
#elif !defined(__GCC_HAVE_DWARF2_CFI_ASM)
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

#ifdef __x86_64__
__ASM_L(.macro subq_imm_cfi offset:req, reg:req)
__ASM_L(	subq $(__ASM_ARG(\offset)), __ASM_ARG(\reg))
__ASM_L(	.cfi_adjust_cfa_offset __ASM_ARG(\offset))
__ASM_L(.endm)
__ASM_L(.macro addq_imm_cfi offset:req, reg:req)
__ASM_L(	addq $(__ASM_ARG(\offset)), __ASM_ARG(\reg))
__ASM_L(	.cfi_adjust_cfa_offset -__ASM_ARG(\offset))
__ASM_L(.endm)
#else /* __x86_64__ */
__ASM_L(.macro subl_imm_cfi offset:req, reg:req)
__ASM_L(	subl $(__ASM_ARG(\offset)), __ASM_ARG(\reg))
__ASM_L(	.cfi_adjust_cfa_offset __ASM_ARG(\offset))
__ASM_L(.endm)
__ASM_L(.macro addl_imm_cfi offset:req, reg:req)
__ASM_L(	addl $(__ASM_ARG(\offset)), __ASM_ARG(\reg))
__ASM_L(	.cfi_adjust_cfa_offset -__ASM_ARG(\offset))
__ASM_L(.endm)
#endif /* !__x86_64__ */

#ifdef __x86_64__
__ASM_L(.macro pushq_cfi reg:req; pushq __ASM_ARG(\reg); .cfi_adjust_cfa_offset 8; .endm)
__ASM_L(.macro popq_cfi reg:req; popq __ASM_ARG(\reg); .cfi_adjust_cfa_offset -8; .endm)
__ASM_L(.macro pushq_cfi_r reg:req; pushq __ASM_ARG(\reg); .cfi_adjust_cfa_offset 8; .cfi_rel_offset __ASM_ARG(\reg), 0; .endm)
__ASM_L(.macro popq_cfi_r reg:req; popq __ASM_ARG(\reg); .cfi_adjust_cfa_offset -8; .cfi_restore __ASM_ARG(\reg); .endm)
__ASM_L(.macro pushfq_cfi; pushfq; .cfi_adjust_cfa_offset 8; .endm)
__ASM_L(.macro popfq_cfi; popfq; .cfi_adjust_cfa_offset -8; .endm)
__ASM_L(.macro pushfq_cfi_r; pushfq; .cfi_adjust_cfa_offset 8; .cfi_rel_offset %eflags, 0; .endm)
__ASM_L(.macro popfq_cfi_r; popfq; .cfi_adjust_cfa_offset -8; .cfi_restore %eflags; .endm)

/* Because x86_64 doesn't allow `pushq %ss/%cs/%ds/%es/%fs.base/%gs.base', add a
 * convenience   wrapper   that   uses   an   intermediate   register  `clobber'
 * The  same  also  goes  for  popq,  which  also  gets  a  convenience  wrapper */
__ASM_L(.macro pushq_cfi_seg_r reg:req, clobber:req)
__ASM_L(.ifc __ASM_ARG(\reg),%fs.base)
__ASM_L(	safe_rdfsbase __ASM_ARG(\clobber))
__ASM_L(	pushq  __ASM_ARG(\clobber))
__ASM_L(	.cfi_adjust_cfa_offset 8)
__ASM_L(	.cfi_rel_offset 58, 0)
__ASM_L(.else;.ifc __ASM_ARG(\reg),%gs.base)
__ASM_L(	safe_rdgsbase __ASM_ARG(\clobber))
__ASM_L(	pushq  __ASM_ARG(\clobber))
__ASM_L(	.cfi_adjust_cfa_offset 8)
__ASM_L(	.cfi_rel_offset 59, 0)
__ASM_L(.else;.ifc __ASM_ARG(\reg),%ss;.else)
__ASM_L(.ifc __ASM_ARG(\reg),%cs;.else)
__ASM_L(.ifc __ASM_ARG(\reg),%ds;.else)
__ASM_L(.ifc __ASM_ARG(\reg),%es;.else)
__ASM_L(	.error "pushq_cfi_seg_r cannot be used with \reg (expected one of %ss, %cs, %ds, %es, %fs.base, %gs.base)")
__ASM_L(.endif;.endif;.endif;.endif)
__ASM_L(	movq   __ASM_ARG(\reg), __ASM_ARG(\clobber))
__ASM_L(	pushq  __ASM_ARG(\clobber))
__ASM_L(	.cfi_adjust_cfa_offset 8)
__ASM_L(	.cfi_rel_offset __ASM_ARG(\reg), 0)
__ASM_L(.endif;.endif)
__ASM_L(.endm)

__ASM_L(.macro popq_cfi_seg_r reg:req, clobber:req)
__ASM_L(.ifc __ASM_ARG(\reg),%fs.base)
__ASM_L(	popq   __ASM_ARG(\clobber))
__ASM_L(	.cfi_adjust_cfa_offset -8)
__ASM_L(	.cfi_register 58, __ASM_ARG(\clobber))
__ASM_L(	safe_wrfsbase __ASM_ARG(\clobber))
__ASM_L(	.cfi_same_value 58)
__ASM_L(.else;.ifc __ASM_ARG(\reg),%gs.base)
__ASM_L(	popq   __ASM_ARG(\clobber))
__ASM_L(	.cfi_adjust_cfa_offset -8)
__ASM_L(	.cfi_register 59, __ASM_ARG(\clobber))
__ASM_L(	safe_wrgsbase __ASM_ARG(\clobber))
__ASM_L(	.cfi_same_value 59)
__ASM_L(.else;.ifc __ASM_ARG(\reg),%ss;.else)
__ASM_L(.ifc __ASM_ARG(\reg),%cs;.else)
__ASM_L(.ifc __ASM_ARG(\reg),%ds;.else)
__ASM_L(.ifc __ASM_ARG(\reg),%es;.else)
__ASM_L(	.error "popq_cfi_seg_r cannot be used with \reg (expected one of %ss, %cs, %ds, %es, %fs.base, %gs.base)")
__ASM_L(.endif;.endif;.endif;.endif)
__ASM_L(	popq   __ASM_ARG(\clobber))
__ASM_L(	.cfi_adjust_cfa_offset -8)
__ASM_L(	movq   __ASM_ARG(\clobber), __ASM_ARG(\reg))
__ASM_L(	.cfi_same_value __ASM_ARG(\reg))
__ASM_L(.endif;.endif)
__ASM_L(.endm)
#else /* __x86_64__ */
__ASM_L(.macro pushw_cfi reg:req; pushw __ASM_ARG(\reg); .cfi_adjust_cfa_offset 2; .endm)
__ASM_L(.macro popw_cfi reg:req; popw __ASM_ARG(\reg); .cfi_adjust_cfa_offset -2; .endm)
__ASM_L(.macro pushl_cfi reg:req; pushl __ASM_ARG(\reg); .cfi_adjust_cfa_offset 4; .endm)
__ASM_L(.macro popl_cfi reg:req; popl __ASM_ARG(\reg); .cfi_adjust_cfa_offset -4; .endm)
__ASM_L(.macro pushfl_cfi; pushfl; .cfi_adjust_cfa_offset 4; .endm)
__ASM_L(.macro popfl_cfi; popfl; .cfi_adjust_cfa_offset -4; .endm)
__ASM_L(.macro pushfl_cfi_r; pushfl; .cfi_adjust_cfa_offset 4; .cfi_rel_offset %eflags, 0; .endm)
__ASM_L(.macro popfl_cfi_r; popfl; .cfi_adjust_cfa_offset -4; .cfi_restore %eflags; .endm)
__ASM_L(.macro pushl_cfi_r reg:req; pushl __ASM_ARG(\reg); .cfi_adjust_cfa_offset 4; .cfi_rel_offset __ASM_ARG(\reg), 0; .endm)
__ASM_L(.macro popl_cfi_r reg:req; popl __ASM_ARG(\reg); .cfi_adjust_cfa_offset -4; .cfi_restore __ASM_ARG(\reg); .endm)
__ASM_L(.macro pushal_cfi; pushal; .cfi_adjust_cfa_offset 32; .endm)
__ASM_L(.macro popal_cfi; popal; .cfi_adjust_cfa_offset -32; .endm)
__ASM_L(.macro pushal_cfi_r)
__ASM_L(	pushal)
__ASM_L(	.cfi_adjust_cfa_offset 32)
__ASM_L(	.cfi_rel_offset %edi, 0)
__ASM_L(	.cfi_rel_offset %esi, 4)
__ASM_L(	.cfi_rel_offset %ebp, 8)
/*ASM_L(	.cfi_rel_offset %esp, 12) */
__ASM_L(	.cfi_rel_offset %ebx, 16)
__ASM_L(	.cfi_rel_offset %edx, 20)
__ASM_L(	.cfi_rel_offset %ecx, 24)
__ASM_L(	.cfi_rel_offset %eax, 28)
__ASM_L(.endm)
__ASM_L(.macro popal_cfi_r)
__ASM_L(	popal)
__ASM_L(	.cfi_adjust_cfa_offset -32)
__ASM_L(	.cfi_restore %edi)
__ASM_L(	.cfi_restore %esi)
__ASM_L(	.cfi_restore %ebp)
/*__ASM_L(	.cfi_restore %esp) */
__ASM_L(	.cfi_restore %ebx)
__ASM_L(	.cfi_restore %edx)
__ASM_L(	.cfi_restore %ecx)
__ASM_L(	.cfi_restore %eax)
__ASM_L(.endm)
#endif /* !__x86_64__ */

/* Decode register names and invoke `func' with the effective CFI register ID. */
__ASM_L(.macro __cfi_decode_register func:req, reg:req)
#define __REGISTER_CASE(name,id) __ASM_L(.ifc __ASM_ARG(\reg),name; __ASM_ARG(\func) id; .else)
#ifdef __x86_64__
	__REGISTER_CASE(%rax,0)
	__REGISTER_CASE(%rdx,1)
	__REGISTER_CASE(%rcx,2)
	__REGISTER_CASE(%rbx,3)
	__REGISTER_CASE(%rsi,4)
	__REGISTER_CASE(%rdi,5)
	__REGISTER_CASE(%rbp,6)
	__REGISTER_CASE(%rsp,7)
	__REGISTER_CASE(%r8,8)
	__REGISTER_CASE(%r9,9)
	__REGISTER_CASE(%r10,10)
	__REGISTER_CASE(%r11,11)
	__REGISTER_CASE(%r12,12)
	__REGISTER_CASE(%r13,13)
	__REGISTER_CASE(%r14,14)
	__REGISTER_CASE(%r15,15)
	__REGISTER_CASE(%rip,16)
	__REGISTER_CASE(%xmm0,17)
	__REGISTER_CASE(%xmm1,18)
	__REGISTER_CASE(%xmm2,19)
	__REGISTER_CASE(%xmm3,20)
	__REGISTER_CASE(%xmm4,21)
	__REGISTER_CASE(%xmm5,22)
	__REGISTER_CASE(%xmm6,23)
	__REGISTER_CASE(%xmm7,24)
	__REGISTER_CASE(%xmm8,25)
	__REGISTER_CASE(%xmm9,26)
	__REGISTER_CASE(%xmm10,27)
	__REGISTER_CASE(%xmm11,28)
	__REGISTER_CASE(%xmm12,29)
	__REGISTER_CASE(%xmm13,30)
	__REGISTER_CASE(%xmm14,31)
	__REGISTER_CASE(%xmm15,32)
	__REGISTER_CASE(%st0,33)
	__REGISTER_CASE(%st1,34)
	__REGISTER_CASE(%st2,35)
	__REGISTER_CASE(%st3,36)
	__REGISTER_CASE(%st4,37)
	__REGISTER_CASE(%st5,38)
	__REGISTER_CASE(%st6,39)
	__REGISTER_CASE(%st7,40)
	__REGISTER_CASE(%st(0),33)
	__REGISTER_CASE(%st(1),34)
	__REGISTER_CASE(%st(2),35)
	__REGISTER_CASE(%st(3),36)
	__REGISTER_CASE(%st(4),37)
	__REGISTER_CASE(%st(5),38)
	__REGISTER_CASE(%st(6),39)
	__REGISTER_CASE(%st(7),40)
	__REGISTER_CASE(%mm0,41)
	__REGISTER_CASE(%mm1,42)
	__REGISTER_CASE(%mm2,43)
	__REGISTER_CASE(%mm3,44)
	__REGISTER_CASE(%mm4,45)
	__REGISTER_CASE(%mm5,46)
	__REGISTER_CASE(%mm6,47)
	__REGISTER_CASE(%mm7,48)
	__REGISTER_CASE(%rflags,49)
	__REGISTER_CASE(%es,50)
	__REGISTER_CASE(%cs,51)
	__REGISTER_CASE(%ss,52)
	__REGISTER_CASE(%ds,53)
	__REGISTER_CASE(%fs,54)
	__REGISTER_CASE(%gs,55)
	__REGISTER_CASE(%fs.base,58)
	__REGISTER_CASE(%gs.base,59)
	__REGISTER_CASE(%tr,62)
	__REGISTER_CASE(%ldtr,63)
	__REGISTER_CASE(%mxcsr,64)
	__REGISTER_CASE(%fcw,65)
	__REGISTER_CASE(%fsw,66)
	__REGISTER_CASE(%xmm16,67)
	__REGISTER_CASE(%xmm17,68)
	__REGISTER_CASE(%xmm18,69)
	__REGISTER_CASE(%xmm19,70)
	__REGISTER_CASE(%xmm20,71)
	__REGISTER_CASE(%xmm21,72)
	__REGISTER_CASE(%xmm22,73)
	__REGISTER_CASE(%xmm23,74)
	__REGISTER_CASE(%xmm24,75)
	__REGISTER_CASE(%xmm25,76)
	__REGISTER_CASE(%xmm26,77)
	__REGISTER_CASE(%xmm27,78)
	__REGISTER_CASE(%xmm28,79)
	__REGISTER_CASE(%xmm29,80)
	__REGISTER_CASE(%xmm30,81)
	__REGISTER_CASE(%xmm31,82)
	__REGISTER_CASE(%k0,118)
	__REGISTER_CASE(%k1,119)
	__REGISTER_CASE(%k2,120)
	__REGISTER_CASE(%k3,121)
	__REGISTER_CASE(%k4,122)
	__REGISTER_CASE(%k5,123)
	__REGISTER_CASE(%k6,124)
	__REGISTER_CASE(%k7,125)
__ASM_L(	__ASM_ARG(\func) __ASM_ARG(\reg))
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif)
#else /* __x86_64__ */
	__REGISTER_CASE(%eax,0)
	__REGISTER_CASE(%ecx,1)
	__REGISTER_CASE(%edx,2)
	__REGISTER_CASE(%ebx,3)
	__REGISTER_CASE(%esp,4)
	__REGISTER_CASE(%ebp,5)
	__REGISTER_CASE(%esi,6)
	__REGISTER_CASE(%edi,7)
	__REGISTER_CASE(%eip,8)
	__REGISTER_CASE(%eflags,9)
	__REGISTER_CASE(%st0,11)
	__REGISTER_CASE(%st1,12)
	__REGISTER_CASE(%st2,13)
	__REGISTER_CASE(%st3,14)
	__REGISTER_CASE(%st4,15)
	__REGISTER_CASE(%st5,16)
	__REGISTER_CASE(%st6,17)
	__REGISTER_CASE(%st7,18)
	__REGISTER_CASE(%st(0),11)
	__REGISTER_CASE(%st(1),12)
	__REGISTER_CASE(%st(2),13)
	__REGISTER_CASE(%st(3),14)
	__REGISTER_CASE(%st(4),15)
	__REGISTER_CASE(%st(5),16)
	__REGISTER_CASE(%st(6),17)
	__REGISTER_CASE(%st(7),18)
	__REGISTER_CASE(%xmm0,21)
	__REGISTER_CASE(%xmm1,22)
	__REGISTER_CASE(%xmm2,23)
	__REGISTER_CASE(%xmm3,24)
	__REGISTER_CASE(%xmm4,25)
	__REGISTER_CASE(%xmm5,26)
	__REGISTER_CASE(%xmm6,27)
	__REGISTER_CASE(%xmm7,28)
	__REGISTER_CASE(%mm0,29)
	__REGISTER_CASE(%mm1,30)
	__REGISTER_CASE(%mm2,31)
	__REGISTER_CASE(%mm3,32)
	__REGISTER_CASE(%mm4,33)
	__REGISTER_CASE(%mm5,34)
	__REGISTER_CASE(%mm6,35)
	__REGISTER_CASE(%mm7,36)
	__REGISTER_CASE(%fcw,37)
	__REGISTER_CASE(%fsw,38)
	__REGISTER_CASE(%mxcsr,39)
	__REGISTER_CASE(%es,40)
	__REGISTER_CASE(%cs,41)
	__REGISTER_CASE(%ss,42)
	__REGISTER_CASE(%ds,43)
	__REGISTER_CASE(%fs,44)
	__REGISTER_CASE(%gs,45)
	__REGISTER_CASE(%tr,48)
	__REGISTER_CASE(%ldtr,49)
	__REGISTER_CASE(%k0,93)
	__REGISTER_CASE(%k1,94)
	__REGISTER_CASE(%k2,95)
	__REGISTER_CASE(%k3,96)
	__REGISTER_CASE(%k4,97)
	__REGISTER_CASE(%k5,98)
	__REGISTER_CASE(%k6,99)
	__REGISTER_CASE(%k7,100)
__ASM_L(	__ASM_ARG(\func) __ASM_ARG(\reg))
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif)
#endif /* !__x86_64__ */
#undef __REGISTER_CASE
__ASM_L(.endm)

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


#ifdef __x86_64__

/* NOTE: \iret_offset is the offset of the `struct irregs64' from CFA */
__ASM_L(.macro .cfi_restore_iret_rip iret_offset=0)
__ASM_L(	.cfi_offset %rip, 0+__ASM_ARG(\iret_offset))
__ASM_L(.endm)

__ASM_L(.macro .cfi_restore_iret_cs iret_offset=0)
__ASM_L(	.cfi_offset %cs, 8+__ASM_ARG(\iret_offset))
__ASM_L(.endm)

__ASM_L(.macro .cfi_restore_iret_rflags iret_offset=0)
__ASM_L(	.cfi_offset %rflags, 16+__ASM_ARG(\iret_offset))
__ASM_L(.endm)

__ASM_L(.macro .cfi_restore_iret_rsp iret_offset=0)
__ASM_L(	.cfi_offset %rsp, 24+__ASM_ARG(\iret_offset))
__ASM_L(.endm)

__ASM_L(.macro .cfi_restore_iret_ss iret_offset=0)
__ASM_L(	.cfi_offset %ss, 32+__ASM_ARG(\iret_offset))
__ASM_L(.endm)

__ASM_L(.macro .cfi_restore_iret reg:req iret_offset=0)
__ASM_L(.ifc __ASM_ARG(\reg),%rip; .cfi_restore_iret_rip __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%cs; .cfi_restore_iret_cs __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%rflags; .cfi_restore_iret_rflags __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%rsp; .cfi_restore_iret_rsp __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%ss; .cfi_restore_iret_ss __ASM_ARG(\iret_offset); .else)
__ASM_L(.error "Cannot restore register \reg that is not affected by `iret`")
__ASM_L(.endif;.endif;.endif;.endif;.endif;)
__ASM_L(.endm)

/* Define CFI restore rules to unwind an x86 iret-compatible function:
 * >> .cfi_startproc simple
 * >> .cfi_iret_signal_frame
 * >>     ...
 * >>     iret
 * >> .cfi_endproc
 */
__ASM_L(.macro .cfi_iret_signal_frame iret_offset=0)
__ASM_L(	.cfi_signal_frame)
__ASM_L(	.cfi_restore_iret_rip __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_cs __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_rflags __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_rsp __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_ss __ASM_ARG(\iret_offset))
__ASM_L(.endm)

#else /* __x86_64__ */

/* NOTE: \iret_offset is the offset of the `struct irregs64' from CFA */
__ASM_L(.macro .cfi_restore_iret_eip iret_offset=0)
__ASM_L(	.cfi_offset %eip, 0+__ASM_ARG(\iret_offset))
__ASM_L(.endm)

__ASM_L(.macro .cfi_restore_iret_cs iret_offset=0)
__ASM_L(	.cfi_offset %cs, 4+__ASM_ARG(\iret_offset))
__ASM_L(.endm)

__ASM_L(.macro .cfi_restore_iret_eflags iret_offset=0)
__ASM_L(	.cfi_offset %eflags, 8+__ASM_ARG(\iret_offset))
__ASM_L(.endm)



#ifdef __I386_NO_VM86
__ASM_L(.macro .cfi_restore_iret_esp iret_offset=0)
/*[[[cfi{arch='i386', register='%esp'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_CS+\iret_offset     # CFA, CS
	deref                                     # CFA, [CS]
	and    $3                                 # CFA, [CS] & 3
	jnz    pop, 1f                            # CFA, if (CS & 3) goto 1f;
	# Kernel-space return location (must unwind ESP to point after irregs)
	plus   $SIZEOF_IRREGS_KERNEL+\iret_offset # CFA + SIZEOF_IRREGS_KERNEL
	ret
1:	# User-space or VM86 return location
	plus   $OFFSET_IRREGS_ESP+\iret_offset    # ESP
	deref                                     # [ESP]
]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,17,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,5,0,35,__ASM_ARG(\iret_offset)+12,47,3)
__ASM_L(	.cfi_escape 0,35,__ASM_ARG(\iret_offset)+12,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -12 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,18,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,5,0,35,__ASM_ARG(\iret_offset)+12,47)
__ASM_L(	.cfi_escape 3,0,35,__ASM_ARG(\iret_offset)+12,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 123)
__ASM_L(	.cfi_escape 22,4,19,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,6,0,8,__ASM_ARG(\iret_offset)+12,34,47)
__ASM_L(	.cfi_escape 4,0,8,__ASM_ARG(\iret_offset)+12,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 243)
__ASM_L(	.cfi_escape 22,4,20,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,6,0,8,__ASM_ARG(\iret_offset)+12,34)
__ASM_L(	.cfi_escape 47,4,0,8,__ASM_ARG(\iret_offset)+12,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -132 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,20,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,6,0,9,__ASM_ARG(\iret_offset)+12,34)
__ASM_L(	.cfi_escape 47,4,0,9,__ASM_ARG(\iret_offset)+12,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -140 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,21,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,6,0,9,__ASM_ARG(\iret_offset)+12)
__ASM_L(	.cfi_escape 34,47,4,0,9,__ASM_ARG(\iret_offset)+12,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 251)
__ASM_L(	.cfi_escape 22,4,22,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,7,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8)
__ASM_L(	.cfi_escape 34,47,5,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65523)
__ASM_L(	.cfi_escape 22,4,23,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,7,0,10,(__ASM_ARG(\iret_offset)+12)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,47,5,0,10,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32772 && __ASM_ARG(\iret_offset) <= 32755)
__ASM_L(	.cfi_escape 22,4,23,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,7,0,11,(__ASM_ARG(\iret_offset)+12)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,47,5,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -12 && __ASM_ARG(\iret_offset) <= 32763)
__ASM_L(	.cfi_escape 22,4,23,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,7,0,10,(__ASM_ARG(\iret_offset)+12)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,47,5,0,10,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32780 && __ASM_ARG(\iret_offset) <= 32755)
__ASM_L(	.cfi_escape 22,4,25,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,7,0)
__ASM_L(	.cfi_escape 11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,47,5,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65531)
__ASM_L(	.cfi_escape 22,4,27,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,9,0,13,(__ASM_ARG(\iret_offset)+12)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,13,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 4294967283)
__ASM_L(	.cfi_escape 22,4,29,18,12,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,9,0)
__ASM_L(	.cfi_escape 12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483652 && __ASM_ARG(\iret_offset) <= 2147483635)
__ASM_L(	.cfi_escape 22,4,29,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,9,0)
__ASM_L(	.cfi_escape 13,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,13,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -12 && __ASM_ARG(\iret_offset) <= 2147483643)
__ASM_L(	.cfi_escape 22,4,29,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,9,0)
__ASM_L(	.cfi_escape 12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)


__ASM_L(.macro .cfi_restore_iret_ss iret_offset=0)
/*[[[cfi{arch='i386', register='%ss'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_CS+\iret_offset     # CFA, CS
	deref                                     # CFA, [CS]
	and    $3                                 # CFA, [CS] & 3
	jnz    pop, 1f                            # CFA, if (CS & 3) goto 1f;
	# Kernel-space return location
	push   %ss
	ret
1:	# User-space return location
	plus   $OFFSET_IRREGS_SS+\iret_offset     # SS
	deref                                     # [SS]
]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,18,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,6,0,146,42,0,47)
__ASM_L(	.cfi_escape 3,0,35,__ASM_ARG(\iret_offset)+16,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 123)
__ASM_L(	.cfi_escape 22,42,19,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,6,0,146,42,0,47)
__ASM_L(	.cfi_escape 4,0,8,__ASM_ARG(\iret_offset)+16,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -16 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,19,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,6,0,146,42,0)
__ASM_L(	.cfi_escape 47,3,0,35,__ASM_ARG(\iret_offset)+16,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 239)
__ASM_L(	.cfi_escape 22,42,20,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,6,0,146,42,0)
__ASM_L(	.cfi_escape 47,4,0,8,__ASM_ARG(\iret_offset)+16,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -132 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,20,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,6,0,146,42,0)
__ASM_L(	.cfi_escape 47,4,0,9,__ASM_ARG(\iret_offset)+16,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 251)
__ASM_L(	.cfi_escape 22,42,21,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,6,0,146,42,0)
__ASM_L(	.cfi_escape 47,5,0,11,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -144 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,21,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,6,0,146,42)
__ASM_L(	.cfi_escape 0,47,4,0,9,__ASM_ARG(\iret_offset)+16,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65519)
__ASM_L(	.cfi_escape 22,42,22,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,6,0,146,42)
__ASM_L(	.cfi_escape 0,47,5,0,10,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32772 && __ASM_ARG(\iret_offset) <= 32751)
__ASM_L(	.cfi_escape 22,42,22,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,6,0,146,42)
__ASM_L(	.cfi_escape 0,47,5,0,11,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -16 && __ASM_ARG(\iret_offset) <= 32763)
__ASM_L(	.cfi_escape 22,42,22,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,6,0,146,42)
__ASM_L(	.cfi_escape 0,47,5,0,10,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65531)
__ASM_L(	.cfi_escape 22,42,24,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,6,0,146,42)
__ASM_L(	.cfi_escape 0,47,7,0,13,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32784 && __ASM_ARG(\iret_offset) <= 32751)
__ASM_L(	.cfi_escape 22,42,24,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,6,0)
__ASM_L(	.cfi_escape 146,42,0,47,5,0,11,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 4294967279)
__ASM_L(	.cfi_escape 22,42,26,18,12,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,6,0)
__ASM_L(	.cfi_escape 146,42,0,47,7,0,12,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483652 && __ASM_ARG(\iret_offset) <= 2147483631)
__ASM_L(	.cfi_escape 22,42,26,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,6,0)
__ASM_L(	.cfi_escape 146,42,0,47,7,0,13,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -16 && __ASM_ARG(\iret_offset) <= 2147483643)
__ASM_L(	.cfi_escape 22,42,26,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,6,0)
__ASM_L(	.cfi_escape 146,42,0,47,7,0,12,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)

__ASM_L(.macro .cfi_restore_iret_es iret_offset=0)
__ASM_L(	.cfi_same_value %es)
__ASM_L(.endm)
__ASM_L(.macro .cfi_restore_iret_ds iret_offset=0)
__ASM_L(	.cfi_same_value %ds)
__ASM_L(.endm)
__ASM_L(.macro .cfi_restore_iret_fs iret_offset=0)
__ASM_L(	.cfi_same_value %fs)
__ASM_L(.endm)
__ASM_L(.macro .cfi_restore_iret_gs iret_offset=0)
__ASM_L(	.cfi_same_value %gs)
__ASM_L(.endm)

__ASM_L(.macro .cfi_restore_iret_es_or_offset novm86_offset:req iret_offset=0)
__ASM_L(	.cfi_offset %es, __ASM_ARG(\novm86_offset))
__ASM_L(.endm)
__ASM_L(.macro .cfi_restore_iret_ds_or_offset novm86_offset:req iret_offset=0)
__ASM_L(	.cfi_offset %ds, __ASM_ARG(\novm86_offset))
__ASM_L(.endm)
__ASM_L(.macro .cfi_restore_iret_fs_or_offset novm86_offset:req iret_offset=0)
__ASM_L(	.cfi_offset %fs, __ASM_ARG(\novm86_offset))
__ASM_L(.endm)
__ASM_L(.macro .cfi_restore_iret_gs_or_offset novm86_offset:req iret_offset=0)
__ASM_L(	.cfi_offset %gs, __ASM_ARG(\novm86_offset))
__ASM_L(.endm)
#else /* __I386_NO_VM86 */
__ASM_L(.macro .cfi_restore_iret_esp iret_offset=0)
/*[[[cfi{arch='i386', register='%esp'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_CS+\iret_offset     # CFA, CS
	deref                                     # CFA, [CS]
	and    $3                                 # CFA, [CS] & 3
	jnz    pop, 1f                            # CFA, if (CS & 3) goto 1f;
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # CFA, EFLAGS
	deref                                     # CFA, [EFLAGS]
	and    $EFLAGS_VM                         # CFA, [EFLAGS] & EFLAGS_VM
	jnz    pop, 1f                            # CFA, if (EFLAGS & EFLAGS_VM) goto 1f;
	# Kernel-space return location (must unwind ESP to point after irregs)
	plus   $SIZEOF_IRREGS_KERNEL+\iret_offset # CFA + SIZEOF_IRREGS_KERNEL
	ret
1:	# User-space or VM86 return location
	plus   $OFFSET_IRREGS_ESP+\iret_offset    # ESP
	deref                                     # [ESP]
]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,29,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,17,0,18,35,__ASM_ARG(\iret_offset)+8,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,40,5,0,35,__ASM_ARG(\iret_offset)+12,47,3,0,35,__ASM_ARG(\iret_offset)+12,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,30,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,17,0,18,35,__ASM_ARG(\iret_offset)+8)
__ASM_L(	.cfi_escape 6,16,128,128,8,26,40,5,0,35,__ASM_ARG(\iret_offset)+12,47,3,0,35,__ASM_ARG(\iret_offset)+12)
__ASM_L(	.cfi_escape 6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 119)
__ASM_L(	.cfi_escape 22,4,31,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,18,0,18,35,__ASM_ARG(\iret_offset)+8,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,40,6,0,8,__ASM_ARG(\iret_offset)+12,34,47,4,0,8,__ASM_ARG(\iret_offset)+12)
__ASM_L(	.cfi_escape 34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -12 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,31,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,18,0,18,9,__ASM_ARG(\iret_offset)+8)
__ASM_L(	.cfi_escape 34,6,16,128,128,8,26,40,5,0,35,__ASM_ARG(\iret_offset)+12,47,3,0,35)
__ASM_L(	.cfi_escape __ASM_ARG(\iret_offset)+12,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 123)
__ASM_L(	.cfi_escape 22,4,32,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,19,0,18,8,__ASM_ARG(\iret_offset)+8,34)
__ASM_L(	.cfi_escape 6,16,128,128,8,26,40,6,0,8,__ASM_ARG(\iret_offset)+12,34,47,4,0,8)
__ASM_L(	.cfi_escape __ASM_ARG(\iret_offset)+12,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 243)
__ASM_L(	.cfi_escape 22,4,33,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,19,0,18,8,__ASM_ARG(\iret_offset)+8)
__ASM_L(	.cfi_escape 34,6,16,128,128,8,26,40,6,0,8,__ASM_ARG(\iret_offset)+12,34,47,4,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\iret_offset)+12,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -132 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,33,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,19,0,18,9,__ASM_ARG(\iret_offset)+8)
__ASM_L(	.cfi_escape 34,6,16,128,128,8,26,40,6,0,9,__ASM_ARG(\iret_offset)+12,34,47,4,0)
__ASM_L(	.cfi_escape 9,__ASM_ARG(\iret_offset)+12,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,34,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,19,0,18,9)
__ASM_L(	.cfi_escape __ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0,9,__ASM_ARG(\iret_offset)+12,34,47,4)
__ASM_L(	.cfi_escape 0,9,__ASM_ARG(\iret_offset)+12,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 247)
__ASM_L(	.cfi_escape 22,4,35,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,20,0,18,8,__ASM_ARG(\iret_offset)+8)
__ASM_L(	.cfi_escape 34,6,16,128,128,8,26,40,7,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,47,5)
__ASM_L(	.cfi_escape 0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -140 && __ASM_ARG(\iret_offset) <= 115)
__ASM_L(	.cfi_escape 22,4,35,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,20,0,18,11)
__ASM_L(	.cfi_escape (__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6,0,9,__ASM_ARG(\iret_offset)+12,34,47)
__ASM_L(	.cfi_escape 4,0,9,__ASM_ARG(\iret_offset)+12,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 251)
__ASM_L(	.cfi_escape 22,4,36,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,21,0,18,11,(__ASM_ARG(\iret_offset)+8)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,7,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,47)
__ASM_L(	.cfi_escape 5,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 32763)
__ASM_L(	.cfi_escape 22,4,37,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,21,0,18,10)
__ASM_L(	.cfi_escape (__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,7,0,10,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34)
__ASM_L(	.cfi_escape 47,5,0,10,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65523)
__ASM_L(	.cfi_escape 22,4,37,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,21,0,18,10)
__ASM_L(	.cfi_escape (__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,7,0,10,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34)
__ASM_L(	.cfi_escape 47,5,0,10,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32772 && __ASM_ARG(\iret_offset) <= 32755)
__ASM_L(	.cfi_escape 22,4,37,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,21,0,18,11)
__ASM_L(	.cfi_escape (__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,7,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34)
__ASM_L(	.cfi_escape 47,5,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -12 && __ASM_ARG(\iret_offset) <= 32759)
__ASM_L(	.cfi_escape 22,4,37,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,21,0,18,11)
__ASM_L(	.cfi_escape (__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,7,0,10,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34)
__ASM_L(	.cfi_escape 47,5,0,10,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32755)
__ASM_L(	.cfi_escape 22,4,39,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,21,0)
__ASM_L(	.cfi_escape 18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,7,0,11,(__ASM_ARG(\iret_offset)+12)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,47,5,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65527)
__ASM_L(	.cfi_escape 22,4,41,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,23,0,18,10)
__ASM_L(	.cfi_escape (__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,9,0,13,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,13,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32780 && __ASM_ARG(\iret_offset) <= 32755)
__ASM_L(	.cfi_escape 22,4,41,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,23,0)
__ASM_L(	.cfi_escape 18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,7,0)
__ASM_L(	.cfi_escape 11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,47,5,0,11,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65531)
__ASM_L(	.cfi_escape 22,4,43,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,25,0,18,13)
__ASM_L(	.cfi_escape (__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,9,0,13,(__ASM_ARG(\iret_offset)+12)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,13,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 2147483643)
__ASM_L(	.cfi_escape 22,4,45,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,25,0)
__ASM_L(	.cfi_escape 18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,9,0)
__ASM_L(	.cfi_escape 12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 4294967283)
__ASM_L(	.cfi_escape 22,4,45,18,12,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,25,0)
__ASM_L(	.cfi_escape 18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,9,0)
__ASM_L(	.cfi_escape 12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483652 && __ASM_ARG(\iret_offset) <= 2147483635)
__ASM_L(	.cfi_escape 22,4,45,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,25,0)
__ASM_L(	.cfi_escape 18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,9,0)
__ASM_L(	.cfi_escape 13,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,13,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -12 && __ASM_ARG(\iret_offset) <= 2147483639)
__ASM_L(	.cfi_escape 22,4,45,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,25,0)
__ASM_L(	.cfi_escape 18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,9,0)
__ASM_L(	.cfi_escape 12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,47,7,0,12,(__ASM_ARG(\iret_offset)+12)&0xff,((__ASM_ARG(\iret_offset)+12)&0xff00)>>8,((__ASM_ARG(\iret_offset)+12)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+12)&0xff000000)>>24,34,6)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)


__ASM_L(.macro .cfi_restore_iret_ss iret_offset=0)
/*[[[cfi{arch='i386', register='%ss'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_CS+\iret_offset     # CFA, CS
	deref                                     # CFA, [CS]
	and    $3                                 # CFA, [CS] & 3
	jnz    pop, 1f                            # CFA, if (CS & 3) goto 1f;
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # EFLAGS
	deref                                     # [EFLAGS]
	and    $EFLAGS_VM                         # [EFLAGS] & EFLAGS_VM
	jnz    pop, 1f                            # if (EFLAGS & EFLAGS_VM) goto 1f;
	# Kernel-space return location
	push   %ss
	ret
1:	# User-space or VM86 return location
	plus   $OFFSET_IRREGS_SS+\iret_offset     # SS
	deref                                     # [SS]
]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,29,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,17,0,35,__ASM_ARG(\iret_offset)+8,6,16)
__ASM_L(	.cfi_escape 128,128,8,26,40,6,0,146,42,0,47,3,0,35,__ASM_ARG(\iret_offset)+16,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,30,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,17,0,35,__ASM_ARG(\iret_offset)+8,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,40,6,0,146,42,0,47,3,0,35,__ASM_ARG(\iret_offset)+16)
__ASM_L(	.cfi_escape 6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 119)
__ASM_L(	.cfi_escape 22,42,30,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,17,0,35,__ASM_ARG(\iret_offset)+8,6,16)
__ASM_L(	.cfi_escape 128,128,8,26,40,6,0,146,42,0,47,4,0,8,__ASM_ARG(\iret_offset)+16,34)
__ASM_L(	.cfi_escape 6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 123)
__ASM_L(	.cfi_escape 22,42,31,18,35,__ASM_ARG(\iret_offset)+4,6,51,26,40,18,0,8,__ASM_ARG(\iret_offset)+8,34,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,40,6,0,146,42,0,47,4,0,8,__ASM_ARG(\iret_offset)+16)
__ASM_L(	.cfi_escape 34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -16 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,31,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,18,0,9,__ASM_ARG(\iret_offset)+8,34)
__ASM_L(	.cfi_escape 6,16,128,128,8,26,40,6,0,146,42,0,47,3,0,35)
__ASM_L(	.cfi_escape __ASM_ARG(\iret_offset)+16,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 239)
__ASM_L(	.cfi_escape 22,42,32,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,18,0,8,__ASM_ARG(\iret_offset)+8,34)
__ASM_L(	.cfi_escape 6,16,128,128,8,26,40,6,0,146,42,0,47,4,0,8)
__ASM_L(	.cfi_escape __ASM_ARG(\iret_offset)+16,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -132 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,32,18,9,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,18,0,9,__ASM_ARG(\iret_offset)+8,34)
__ASM_L(	.cfi_escape 6,16,128,128,8,26,40,6,0,146,42,0,47,4,0,9)
__ASM_L(	.cfi_escape __ASM_ARG(\iret_offset)+16,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 247)
__ASM_L(	.cfi_escape 22,42,33,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,18,0,8,__ASM_ARG(\iret_offset)+8,34)
__ASM_L(	.cfi_escape 6,16,128,128,8,26,40,6,0,146,42,0,47,5,0,11)
__ASM_L(	.cfi_escape (__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,33,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,18,0,9,__ASM_ARG(\iret_offset)+8)
__ASM_L(	.cfi_escape 34,6,16,128,128,8,26,40,6,0,146,42,0,47,4,0)
__ASM_L(	.cfi_escape 9,__ASM_ARG(\iret_offset)+16,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 251)
__ASM_L(	.cfi_escape 22,42,34,18,8,__ASM_ARG(\iret_offset)+4,34,6,51,26,40,19,0,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8)
__ASM_L(	.cfi_escape 34,6,16,128,128,8,26,40,6,0,146,42,0,47,5,0)
__ASM_L(	.cfi_escape 11,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -144 && __ASM_ARG(\iret_offset) <= 111)
__ASM_L(	.cfi_escape 22,42,34,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,19,0,11,(__ASM_ARG(\iret_offset)+8)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6,0,146,42,0,47,4)
__ASM_L(	.cfi_escape 0,9,__ASM_ARG(\iret_offset)+16,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 32763)
__ASM_L(	.cfi_escape 22,42,35,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,19,0,10,(__ASM_ARG(\iret_offset)+8)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6,0,146,42,0,47,5)
__ASM_L(	.cfi_escape 0,10,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65519)
__ASM_L(	.cfi_escape 22,42,35,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,19,0,10,(__ASM_ARG(\iret_offset)+8)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6,0,146,42,0,47,5)
__ASM_L(	.cfi_escape 0,10,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32772 && __ASM_ARG(\iret_offset) <= 32751)
__ASM_L(	.cfi_escape 22,42,35,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,19,0,11,(__ASM_ARG(\iret_offset)+8)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6,0,146,42,0,47,5)
__ASM_L(	.cfi_escape 0,11,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -16 && __ASM_ARG(\iret_offset) <= 32759)
__ASM_L(	.cfi_escape 22,42,35,18,11,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,19,0,11,(__ASM_ARG(\iret_offset)+8)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6,0,146,42,0,47,5)
__ASM_L(	.cfi_escape 0,10,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65527)
__ASM_L(	.cfi_escape 22,42,37,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,19,0,10,(__ASM_ARG(\iret_offset)+8)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6,0,146,42,0,47,7)
__ASM_L(	.cfi_escape 0,13,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32751)
__ASM_L(	.cfi_escape 22,42,37,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,19,0)
__ASM_L(	.cfi_escape 11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6,0,146,42,0)
__ASM_L(	.cfi_escape 47,5,0,11,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 65531)
__ASM_L(	.cfi_escape 22,42,39,18,10,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,34,6,51,26,40,21,0,13,(__ASM_ARG(\iret_offset)+8)&0xff)
__ASM_L(	.cfi_escape ((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,6,0,146,42,0)
__ASM_L(	.cfi_escape 47,7,0,13,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32784 && __ASM_ARG(\iret_offset) <= 32751)
__ASM_L(	.cfi_escape 22,42,39,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,21,0)
__ASM_L(	.cfi_escape 13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,6,0,146)
__ASM_L(	.cfi_escape 42,0,47,5,0,11,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 2147483643)
__ASM_L(	.cfi_escape 22,42,41,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,21,0)
__ASM_L(	.cfi_escape 12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,6,0,146)
__ASM_L(	.cfi_escape 42,0,47,7,0,12,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -4 && __ASM_ARG(\iret_offset) <= 4294967279)
__ASM_L(	.cfi_escape 22,42,41,18,12,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,21,0)
__ASM_L(	.cfi_escape 12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,6,0,146)
__ASM_L(	.cfi_escape 42,0,47,7,0,12,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483652 && __ASM_ARG(\iret_offset) <= 2147483631)
__ASM_L(	.cfi_escape 22,42,41,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,21,0)
__ASM_L(	.cfi_escape 13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,6,0,146)
__ASM_L(	.cfi_escape 42,0,47,7,0,13,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -16 && __ASM_ARG(\iret_offset) <= 2147483639)
__ASM_L(	.cfi_escape 22,42,41,18,13,(__ASM_ARG(\iret_offset)+4)&0xff,((__ASM_ARG(\iret_offset)+4)&0xff00)>>8,((__ASM_ARG(\iret_offset)+4)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+4)&0xff000000)>>24,34,6,51,26,40,21,0)
__ASM_L(	.cfi_escape 13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26,40,6,0,146)
__ASM_L(	.cfi_escape 42,0,47,7,0,12,(__ASM_ARG(\iret_offset)+16)&0xff,((__ASM_ARG(\iret_offset)+16)&0xff00)>>8,((__ASM_ARG(\iret_offset)+16)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+16)&0xff000000)>>24,34,6)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)


__ASM_L(.macro .cfi_restore_iret_es iret_offset=0)
/*[[[cfi{arch='i386', register='%es'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # CFA, EFLAGS
	deref                                     # CFA, [EFLAGS]
	and    $EFLAGS_VM                         # CFA, [EFLAGS] & EFLAGS_VM
	not
	jnz    pop, 1f                            # CFA, if (!(EFLAGS & EFLAGS_VM)) goto 1f;
	# VM86 return location
	plus   $OFFSET_IRREGS_ES+\iret_offset     # ES
	deref                                     # [ES]
	ret
1:	push   %es
]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 107)
__ASM_L(	.cfi_escape 22,40,22,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,32,40,6,0)
__ASM_L(	.cfi_escape 35,__ASM_ARG(\iret_offset)+20,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 119)
__ASM_L(	.cfi_escape 22,40,23,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,32,40,7,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\iret_offset)+20,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -20 && __ASM_ARG(\iret_offset) <= 107)
__ASM_L(	.cfi_escape 22,40,23,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,6)
__ASM_L(	.cfi_escape 0,35,__ASM_ARG(\iret_offset)+20,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 235)
__ASM_L(	.cfi_escape 22,40,24,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,7)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\iret_offset)+20,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 107)
__ASM_L(	.cfi_escape 22,40,24,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,7)
__ASM_L(	.cfi_escape 0,9,__ASM_ARG(\iret_offset)+20,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 247)
__ASM_L(	.cfi_escape 22,40,25,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,8)
__ASM_L(	.cfi_escape 0,11,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -148 && __ASM_ARG(\iret_offset) <= 107)
__ASM_L(	.cfi_escape 22,40,25,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 7,0,9,__ASM_ARG(\iret_offset)+20,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65515)
__ASM_L(	.cfi_escape 22,40,26,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,10,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32747)
__ASM_L(	.cfi_escape 22,40,26,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,11,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -20 && __ASM_ARG(\iret_offset) <= 32759)
__ASM_L(	.cfi_escape 22,40,26,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,10,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65527)
__ASM_L(	.cfi_escape 22,40,28,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 10,0,13,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,((__ASM_ARG(\iret_offset)+20)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+20)&0xff000000)>>24,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32788 && __ASM_ARG(\iret_offset) <= 32747)
__ASM_L(	.cfi_escape 22,40,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,8,0,11,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34,6,47,3,0,146,40,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 4294967275)
__ASM_L(	.cfi_escape 22,40,30,18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,12,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,((__ASM_ARG(\iret_offset)+20)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+20)&0xff000000)>>24,34,6,47,3,0,146,40)
__ASM_L(	.cfi_escape 0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483656 && __ASM_ARG(\iret_offset) <= 2147483627)
__ASM_L(	.cfi_escape 22,40,30,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,13,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,((__ASM_ARG(\iret_offset)+20)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+20)&0xff000000)>>24,34,6,47,3,0,146,40)
__ASM_L(	.cfi_escape 0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -20 && __ASM_ARG(\iret_offset) <= 2147483639)
__ASM_L(	.cfi_escape 22,40,30,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,12,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,((__ASM_ARG(\iret_offset)+20)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+20)&0xff000000)>>24,34,6,47,3,0,146,40)
__ASM_L(	.cfi_escape 0)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)


__ASM_L(.macro .cfi_restore_iret_ds iret_offset=0)
/*[[[cfi{arch='i386', register='%ds'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # CFA, EFLAGS
	deref                                     # CFA, [EFLAGS]
	and    $EFLAGS_VM                         # CFA, [EFLAGS] & EFLAGS_VM
	not
	jnz    pop, 1f                            # CFA, if (!(EFLAGS & EFLAGS_VM)) goto 1f;
	# VM86 return location
	plus   $OFFSET_IRREGS_DS+\iret_offset     # DS
	deref                                     # [DS]
	ret
1:	push   %ds
]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 103)
__ASM_L(	.cfi_escape 22,43,22,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,32,40,6,0)
__ASM_L(	.cfi_escape 35,__ASM_ARG(\iret_offset)+24,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 119)
__ASM_L(	.cfi_escape 22,43,23,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,32,40,7,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\iret_offset)+24,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -24 && __ASM_ARG(\iret_offset) <= 103)
__ASM_L(	.cfi_escape 22,43,23,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,6)
__ASM_L(	.cfi_escape 0,35,__ASM_ARG(\iret_offset)+24,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 231)
__ASM_L(	.cfi_escape 22,43,24,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,7)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\iret_offset)+24,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 103)
__ASM_L(	.cfi_escape 22,43,24,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,7)
__ASM_L(	.cfi_escape 0,9,__ASM_ARG(\iret_offset)+24,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 247)
__ASM_L(	.cfi_escape 22,43,25,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,8)
__ASM_L(	.cfi_escape 0,11,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -152 && __ASM_ARG(\iret_offset) <= 103)
__ASM_L(	.cfi_escape 22,43,25,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 7,0,9,__ASM_ARG(\iret_offset)+24,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65511)
__ASM_L(	.cfi_escape 22,43,26,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,10,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32743)
__ASM_L(	.cfi_escape 22,43,26,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,11,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -24 && __ASM_ARG(\iret_offset) <= 32759)
__ASM_L(	.cfi_escape 22,43,26,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,10,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65527)
__ASM_L(	.cfi_escape 22,43,28,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 10,0,13,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,((__ASM_ARG(\iret_offset)+24)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+24)&0xff000000)>>24,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32792 && __ASM_ARG(\iret_offset) <= 32743)
__ASM_L(	.cfi_escape 22,43,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,8,0,11,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34,6,47,3,0,146,43,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 4294967271)
__ASM_L(	.cfi_escape 22,43,30,18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,12,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,((__ASM_ARG(\iret_offset)+24)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+24)&0xff000000)>>24,34,6,47,3,0,146,43)
__ASM_L(	.cfi_escape 0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -24 && __ASM_ARG(\iret_offset) <= 2147483639)
__ASM_L(	.cfi_escape 22,43,30,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,12,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,((__ASM_ARG(\iret_offset)+24)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+24)&0xff000000)>>24,34,6,47,3,0,146,43)
__ASM_L(	.cfi_escape 0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483656 && __ASM_ARG(\iret_offset) <= 2147483623)
__ASM_L(	.cfi_escape 22,43,30,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,13,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,((__ASM_ARG(\iret_offset)+24)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+24)&0xff000000)>>24,34,6,47,3,0,146,43)
__ASM_L(	.cfi_escape 0)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)


__ASM_L(.macro .cfi_restore_iret_fs iret_offset=0)
/*[[[cfi{arch='i386', register='%fs'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # CFA, EFLAGS
	deref                                     # CFA, [EFLAGS]
	and    $EFLAGS_VM                         # CFA, [EFLAGS] & EFLAGS_VM
	not
	jnz    pop, 1f                            # CFA, if (!(EFLAGS & EFLAGS_VM)) goto 1f;
	# VM86 return location
	plus   $OFFSET_IRREGS_FS+\iret_offset     # FS
	deref                                     # [FS]
	ret
1:	push   %fs
]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 99)
__ASM_L(	.cfi_escape 22,44,22,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,32,40,6,0)
__ASM_L(	.cfi_escape 35,__ASM_ARG(\iret_offset)+28,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 119)
__ASM_L(	.cfi_escape 22,44,23,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,32,40,7,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\iret_offset)+28,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -28 && __ASM_ARG(\iret_offset) <= 99)
__ASM_L(	.cfi_escape 22,44,23,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,6)
__ASM_L(	.cfi_escape 0,35,__ASM_ARG(\iret_offset)+28,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 227)
__ASM_L(	.cfi_escape 22,44,24,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,7)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\iret_offset)+28,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 99)
__ASM_L(	.cfi_escape 22,44,24,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,7)
__ASM_L(	.cfi_escape 0,9,__ASM_ARG(\iret_offset)+28,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 247)
__ASM_L(	.cfi_escape 22,44,25,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,8)
__ASM_L(	.cfi_escape 0,11,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -156 && __ASM_ARG(\iret_offset) <= 99)
__ASM_L(	.cfi_escape 22,44,25,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 7,0,9,__ASM_ARG(\iret_offset)+28,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65507)
__ASM_L(	.cfi_escape 22,44,26,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,10,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32739)
__ASM_L(	.cfi_escape 22,44,26,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,11,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -28 && __ASM_ARG(\iret_offset) <= 32759)
__ASM_L(	.cfi_escape 22,44,26,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,10,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65527)
__ASM_L(	.cfi_escape 22,44,28,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 10,0,13,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,((__ASM_ARG(\iret_offset)+28)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+28)&0xff000000)>>24,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32796 && __ASM_ARG(\iret_offset) <= 32739)
__ASM_L(	.cfi_escape 22,44,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,8,0,11,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34,6,47,3,0,146,44,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 4294967267)
__ASM_L(	.cfi_escape 22,44,30,18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,12,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,((__ASM_ARG(\iret_offset)+28)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+28)&0xff000000)>>24,34,6,47,3,0,146,44)
__ASM_L(	.cfi_escape 0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -28 && __ASM_ARG(\iret_offset) <= 2147483639)
__ASM_L(	.cfi_escape 22,44,30,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,12,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,((__ASM_ARG(\iret_offset)+28)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+28)&0xff000000)>>24,34,6,47,3,0,146,44)
__ASM_L(	.cfi_escape 0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483656 && __ASM_ARG(\iret_offset) <= 2147483619)
__ASM_L(	.cfi_escape 22,44,30,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,13,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,((__ASM_ARG(\iret_offset)+28)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+28)&0xff000000)>>24,34,6,47,3,0,146,44)
__ASM_L(	.cfi_escape 0)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)


__ASM_L(.macro .cfi_restore_iret_gs iret_offset=0)
/*[[[cfi{arch='i386', register='%gs'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # CFA, EFLAGS
	deref                                     # CFA, [EFLAGS]
	and    $EFLAGS_VM                         # CFA, [EFLAGS] & EFLAGS_VM
	not
	jnz    pop, 1f                            # CFA, if (!(EFLAGS & EFLAGS_VM)) goto 1f;
	# VM86 return location
	plus   $OFFSET_IRREGS_GS+\iret_offset     # GS
	deref                                     # [GS]
	ret
1:	push   %gs
]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 95)
__ASM_L(	.cfi_escape 22,45,22,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,32,40,6,0)
__ASM_L(	.cfi_escape 35,__ASM_ARG(\iret_offset)+32,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 119)
__ASM_L(	.cfi_escape 22,45,23,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,32,40,7,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\iret_offset)+32,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32 && __ASM_ARG(\iret_offset) <= 95)
__ASM_L(	.cfi_escape 22,45,23,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,6)
__ASM_L(	.cfi_escape 0,35,__ASM_ARG(\iret_offset)+32,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 223)
__ASM_L(	.cfi_escape 22,45,24,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,7)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\iret_offset)+32,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 95)
__ASM_L(	.cfi_escape 22,45,24,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,7)
__ASM_L(	.cfi_escape 0,9,__ASM_ARG(\iret_offset)+32,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 247)
__ASM_L(	.cfi_escape 22,45,25,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,32,40,8)
__ASM_L(	.cfi_escape 0,11,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -160 && __ASM_ARG(\iret_offset) <= 95)
__ASM_L(	.cfi_escape 22,45,25,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 7,0,9,__ASM_ARG(\iret_offset)+32,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65503)
__ASM_L(	.cfi_escape 22,45,26,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,10,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32735)
__ASM_L(	.cfi_escape 22,45,26,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,11,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32 && __ASM_ARG(\iret_offset) <= 32759)
__ASM_L(	.cfi_escape 22,45,26,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 8,0,10,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65527)
__ASM_L(	.cfi_escape 22,45,28,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,32,40)
__ASM_L(	.cfi_escape 10,0,13,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,((__ASM_ARG(\iret_offset)+32)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+32)&0xff000000)>>24,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32800 && __ASM_ARG(\iret_offset) <= 32735)
__ASM_L(	.cfi_escape 22,45,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,8,0,11,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34,6,47,3,0,146,45,0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 4294967263)
__ASM_L(	.cfi_escape 22,45,30,18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,12,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,((__ASM_ARG(\iret_offset)+32)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+32)&0xff000000)>>24,34,6,47,3,0,146,45)
__ASM_L(	.cfi_escape 0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32 && __ASM_ARG(\iret_offset) <= 2147483639)
__ASM_L(	.cfi_escape 22,45,30,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,12,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,((__ASM_ARG(\iret_offset)+32)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+32)&0xff000000)>>24,34,6,47,3,0,146,45)
__ASM_L(	.cfi_escape 0)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483656 && __ASM_ARG(\iret_offset) <= 2147483615)
__ASM_L(	.cfi_escape 22,45,30,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 32,40,10,0,13,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,((__ASM_ARG(\iret_offset)+32)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+32)&0xff000000)>>24,34,6,47,3,0,146,45)
__ASM_L(	.cfi_escape 0)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)



__ASM_L(.macro .cfi_restore_iret_es_or_offset novm86_offset:req iret_offset=0)
/*[[[cfi{arch='i386', register='%es'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # CFA, EFLAGS
	deref                                     # CFA, [EFLAGS]
	and    $EFLAGS_VM                         # CFA, [EFLAGS] & EFLAGS_VM
	jnz    pop, 1f                            # CFA, if (EFLAGS & EFLAGS_VM) goto 1f;
	plus8  \novm86_offset                     # CFA+\novm86_offset
	jmp    2f
1:	# VM86 return location
	plus   $OFFSET_IRREGS_ES+\iret_offset     # ES
2:	deref]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 107 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 127)
__ASM_L(	.cfi_escape 16,40,19,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,40,5,0,35)
__ASM_L(	.cfi_escape __ASM_ARG(\novm86_offset),47,2,0,35,__ASM_ARG(\iret_offset)+20)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 119 && __ASM_ARG(\novm86_offset) >= -128 && __ASM_ARG(\novm86_offset) <= 127)
__ASM_L(	.cfi_escape 16,40,21,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,40,6,0,9)
__ASM_L(	.cfi_escape __ASM_ARG(\novm86_offset),34,47,3,0,8,__ASM_ARG(\iret_offset)+20,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -20 && __ASM_ARG(\iret_offset) <= 107 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,21,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,2,0,35,__ASM_ARG(\iret_offset)+20)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 235 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,22,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,3,0,8,__ASM_ARG(\iret_offset)+20,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 107 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,22,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,3,0,9,__ASM_ARG(\iret_offset)+20,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 247 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,23,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -148 && __ASM_ARG(\iret_offset) <= 107 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,23,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,3,0,9,__ASM_ARG(\iret_offset)+20,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65515 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,24,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,10,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32747 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,24,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -20 && __ASM_ARG(\iret_offset) <= 32759 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,24,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,10,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65527 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,26,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,6,0,13,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,((__ASM_ARG(\iret_offset)+20)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+20)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32788 && __ASM_ARG(\iret_offset) <= 32747 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,26,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 4294967275 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,28,18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,12,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,((__ASM_ARG(\iret_offset)+20)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+20)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483656 && __ASM_ARG(\iret_offset) <= 2147483627 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,13,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,((__ASM_ARG(\iret_offset)+20)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+20)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -20 && __ASM_ARG(\iret_offset) <= 2147483639 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,40,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,12,(__ASM_ARG(\iret_offset)+20)&0xff,((__ASM_ARG(\iret_offset)+20)&0xff00)>>8,((__ASM_ARG(\iret_offset)+20)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+20)&0xff000000)>>24,34)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)


__ASM_L(.macro .cfi_restore_iret_ds_or_offset novm86_offset:req iret_offset=0)
/*[[[cfi{arch='i386', register='%ds'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # CFA, EFLAGS
	deref                                     # CFA, [EFLAGS]
	and    $EFLAGS_VM                         # CFA, [EFLAGS] & EFLAGS_VM
	jnz    pop, 1f                            # CFA, if (EFLAGS & EFLAGS_VM) goto 1f;
	plus8  \novm86_offset                     # CFA+\novm86_offset
	jmp    2f
1:	# VM86 return location
	plus   $OFFSET_IRREGS_DS+\iret_offset     # DS
2:	deref]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 103 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 127)
__ASM_L(	.cfi_escape 16,43,19,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,40,5,0,35)
__ASM_L(	.cfi_escape __ASM_ARG(\novm86_offset),47,2,0,35,__ASM_ARG(\iret_offset)+24)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 119 && __ASM_ARG(\novm86_offset) >= -128 && __ASM_ARG(\novm86_offset) <= 127)
__ASM_L(	.cfi_escape 16,43,21,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,40,6,0,9)
__ASM_L(	.cfi_escape __ASM_ARG(\novm86_offset),34,47,3,0,8,__ASM_ARG(\iret_offset)+24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -24 && __ASM_ARG(\iret_offset) <= 103 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,21,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,2,0,35,__ASM_ARG(\iret_offset)+24)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 231 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,22,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,3,0,8,__ASM_ARG(\iret_offset)+24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 103 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,22,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,3,0,9,__ASM_ARG(\iret_offset)+24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 247 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,23,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -152 && __ASM_ARG(\iret_offset) <= 103 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,23,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,3,0,9,__ASM_ARG(\iret_offset)+24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65511 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,24,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,10,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32743 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,24,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -24 && __ASM_ARG(\iret_offset) <= 32759 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,24,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,10,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65527 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,26,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,6,0,13,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,((__ASM_ARG(\iret_offset)+24)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+24)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32792 && __ASM_ARG(\iret_offset) <= 32743 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,26,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 4294967271 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,28,18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,12,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,((__ASM_ARG(\iret_offset)+24)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+24)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -24 && __ASM_ARG(\iret_offset) <= 2147483639 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,12,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,((__ASM_ARG(\iret_offset)+24)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+24)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483656 && __ASM_ARG(\iret_offset) <= 2147483623 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,43,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,13,(__ASM_ARG(\iret_offset)+24)&0xff,((__ASM_ARG(\iret_offset)+24)&0xff00)>>8,((__ASM_ARG(\iret_offset)+24)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+24)&0xff000000)>>24,34)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)


__ASM_L(.macro .cfi_restore_iret_fs_or_offset novm86_offset:req iret_offset=0)
/*[[[cfi{arch='i386', register='%fs'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # CFA, EFLAGS
	deref                                     # CFA, [EFLAGS]
	and    $EFLAGS_VM                         # CFA, [EFLAGS] & EFLAGS_VM
	jnz    pop, 1f                            # CFA, if (EFLAGS & EFLAGS_VM) goto 1f;
	plus8  \novm86_offset                     # CFA+\novm86_offset
	jmp    2f
1:	# VM86 return location
	plus   $OFFSET_IRREGS_FS+\iret_offset     # FS
2:	deref]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 99 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 127)
__ASM_L(	.cfi_escape 16,44,19,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,40,5,0,35)
__ASM_L(	.cfi_escape __ASM_ARG(\novm86_offset),47,2,0,35,__ASM_ARG(\iret_offset)+28)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 119 && __ASM_ARG(\novm86_offset) >= -128 && __ASM_ARG(\novm86_offset) <= 127)
__ASM_L(	.cfi_escape 16,44,21,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,40,6,0,9)
__ASM_L(	.cfi_escape __ASM_ARG(\novm86_offset),34,47,3,0,8,__ASM_ARG(\iret_offset)+28,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -28 && __ASM_ARG(\iret_offset) <= 99 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,21,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,2,0,35,__ASM_ARG(\iret_offset)+28)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 227 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,22,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,3,0,8,__ASM_ARG(\iret_offset)+28,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 99 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,22,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,3,0,9,__ASM_ARG(\iret_offset)+28,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 247 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,23,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -156 && __ASM_ARG(\iret_offset) <= 99 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,23,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,3,0,9,__ASM_ARG(\iret_offset)+28,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65507 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,24,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,10,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32739 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,24,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -28 && __ASM_ARG(\iret_offset) <= 32759 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,24,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,10,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65527 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,26,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,6,0,13,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,((__ASM_ARG(\iret_offset)+28)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+28)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32796 && __ASM_ARG(\iret_offset) <= 32739 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,26,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 4294967267 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,28,18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,12,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,((__ASM_ARG(\iret_offset)+28)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+28)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -28 && __ASM_ARG(\iret_offset) <= 2147483639 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,12,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,((__ASM_ARG(\iret_offset)+28)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+28)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483656 && __ASM_ARG(\iret_offset) <= 2147483619 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,44,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,13,(__ASM_ARG(\iret_offset)+28)&0xff,((__ASM_ARG(\iret_offset)+28)&0xff00)>>8,((__ASM_ARG(\iret_offset)+28)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+28)&0xff000000)>>24,34)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)


__ASM_L(.macro .cfi_restore_iret_gs_or_offset novm86_offset:req iret_offset=0)
/*[[[cfi{arch='i386', register='%gs'}
	dup                                       # CFA, CFA
	plus   $OFFSET_IRREGS_EFLAGS+\iret_offset # CFA, EFLAGS
	deref                                     # CFA, [EFLAGS]
	and    $EFLAGS_VM                         # CFA, [EFLAGS] & EFLAGS_VM
	jnz    pop, 1f                            # CFA, if (EFLAGS & EFLAGS_VM) goto 1f;
	plus8  \novm86_offset                     # CFA+\novm86_offset
	jmp    2f
1:	# VM86 return location
	plus   $OFFSET_IRREGS_GS+\iret_offset     # GS
2:	deref]]]*/
__ASM_L(.if __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 95 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 127)
__ASM_L(	.cfi_escape 16,45,19,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,40,5,0,35)
__ASM_L(	.cfi_escape __ASM_ARG(\novm86_offset),47,2,0,35,__ASM_ARG(\iret_offset)+32)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 119 && __ASM_ARG(\novm86_offset) >= -128 && __ASM_ARG(\novm86_offset) <= 127)
__ASM_L(	.cfi_escape 16,45,21,18,35,__ASM_ARG(\iret_offset)+8,6,16,128,128,8,26,40,6,0,9)
__ASM_L(	.cfi_escape __ASM_ARG(\novm86_offset),34,47,3,0,8,__ASM_ARG(\iret_offset)+32,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32 && __ASM_ARG(\iret_offset) <= 95 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,21,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,2,0,35,__ASM_ARG(\iret_offset)+32)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 223 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,22,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,3,0,8,__ASM_ARG(\iret_offset)+32,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -136 && __ASM_ARG(\iret_offset) <= 95 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,22,18,9,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,3,0,9,__ASM_ARG(\iret_offset)+32,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 247 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,23,18,8,__ASM_ARG(\iret_offset)+8,34,6,16,128,128,8,26,40,6,0)
__ASM_L(	.cfi_escape 8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -160 && __ASM_ARG(\iret_offset) <= 95 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,23,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,3,0,9,__ASM_ARG(\iret_offset)+32,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65503 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,24,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,10,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32776 && __ASM_ARG(\iret_offset) <= 32735 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,24,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32 && __ASM_ARG(\iret_offset) <= 32759 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,24,18,11,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,4,0,10,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 65527 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,26,18,10,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,34,6,16,128,128,8,26,40,6)
__ASM_L(	.cfi_escape 0,8,__ASM_ARG(\novm86_offset),34,47,6,0,13,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,((__ASM_ARG(\iret_offset)+32)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+32)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32800 && __ASM_ARG(\iret_offset) <= 32735 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,26,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,4,0,11,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -8 && __ASM_ARG(\iret_offset) <= 4294967263 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,28,18,12,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,12,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,((__ASM_ARG(\iret_offset)+32)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+32)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -32 && __ASM_ARG(\iret_offset) <= 2147483639 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,12,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,((__ASM_ARG(\iret_offset)+32)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+32)&0xff000000)>>24,34)
__ASM_L(.elseif __ASM_ARG(\iret_offset) >= -2147483656 && __ASM_ARG(\iret_offset) <= 2147483615 && __ASM_ARG(\novm86_offset) >= 0 && __ASM_ARG(\novm86_offset) <= 255)
__ASM_L(	.cfi_escape 16,45,28,18,13,(__ASM_ARG(\iret_offset)+8)&0xff,((__ASM_ARG(\iret_offset)+8)&0xff00)>>8,((__ASM_ARG(\iret_offset)+8)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+8)&0xff000000)>>24,34,6,16,128,128,8,26)
__ASM_L(	.cfi_escape 40,6,0,8,__ASM_ARG(\novm86_offset),34,47,6,0,13,(__ASM_ARG(\iret_offset)+32)&0xff,((__ASM_ARG(\iret_offset)+32)&0xff00)>>8,((__ASM_ARG(\iret_offset)+32)&0xff0000)>>16,((__ASM_ARG(\iret_offset)+32)&0xff000000)>>24,34)
__ASM_L(.else)
__ASM_L(	.error "Input arguments too large")
__ASM_L(.endif)
/*[[[end]]]*/
__ASM_L(.endm)
#endif /* !__I386_NO_VM86 */



__ASM_L(.macro .cfi_restore_iret reg:req iret_offset=0)
__ASM_L(.ifc __ASM_ARG(\reg),%eip; .cfi_restore_iret_eip __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%cs; .cfi_restore_iret_cs __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%eflags; .cfi_restore_iret_eflags __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%esp; .cfi_restore_iret_esp __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%ss; .cfi_restore_iret_ss __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%es; .cfi_restore_iret_es __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%ds; .cfi_restore_iret_ds __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%fs; .cfi_restore_iret_fs __ASM_ARG(\iret_offset); .else)
__ASM_L(.ifc __ASM_ARG(\reg),%gs; .cfi_restore_iret_gs __ASM_ARG(\iret_offset); .else)
__ASM_L(.error "Cannot restore register \reg that is not affected by `iret`")
__ASM_L(.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(.endm)

/* Define CFI restore rules to unwind an x86 iret-compatible function:
 * >> .cfi_startproc simple
 * >> .cfi_iret_signal_frame
 * >>     ...
 * >>     iret
 * >> .cfi_endproc
 */
__ASM_L(.macro .cfi_iret_signal_frame iret_offset=0)
__ASM_L(	.cfi_signal_frame)
__ASM_L(	.cfi_restore_iret_eip __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_cs __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_eflags __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_esp __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_ss __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_es __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_ds __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_fs __ASM_ARG(\iret_offset))
__ASM_L(	.cfi_restore_iret_gs __ASM_ARG(\iret_offset))
__ASM_L(.endm)

#endif /* !__x86_64__ */

__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_I386_KOS_ASM_CFI_H */
