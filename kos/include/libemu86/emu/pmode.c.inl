/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#define EMU86_WANT_EMULATE_SLDT 1
#define EMU86_WANT_EMULATE_LLDT 1
#define EMU86_WANT_EMULATE_STR  1
#define EMU86_WANT_EMULATE_LTR  1
#define EMU86_WANT_EMULATE_SGDT 1
#define EMU86_WANT_EMULATE_LGDT 1
#define EMU86_WANT_EMULATE_SIDT 1
#define EMU86_WANT_EMULATE_LIDT 1
#define EMU86_WANT_EMULATE_VERR 1
#define EMU86_WANT_EMULATE_VERW 1
#define EMU86_WANT_EMULATE_SMSW 1
#define EMU86_WANT_EMULATE_LMSW 1
#define EMU86_WANT_EMULATE_INVLPG 1
#define EMU86_WANT_EMULATE_LAR 1
#define EMU86_WANT_EMULATE_LSL 1
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(pmode) {


#if (defined(EMU86_EMULATE_SLDT) || defined(EMU86_EMULATE_STR) ||   \
     defined(EMU86_EMULATE_LLDT) || defined(EMU86_EMULATE_LTR) ||   \
     ((CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT) && \
      (defined(EMU86_EMULATE_VERR) || defined(EMU86_EMULATE_VERW))))

case 0x0f00: {
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#ifdef EMU86_EMULATE_SLDT
	case 0: {
		/* REX.W + 0F 00 /0     SLDT r/m16     Stores segment selector from LDTR in r64/m16. */
		u16 ldtr;
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_MISC_LDT, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		ldtr = EMU86_EMULATE_SLDT();
		MODRM_SETRMW(ldtr);
		goto done;
	}
#endif /* EMU86_EMULATE_SLDT */

#ifdef EMU86_EMULATE_STR
	case 1: {
		/* 0F 00 /1     STR r/m16     Stores segment selector from TR in r/m16. */
		u16 tr;
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_MISC_TR, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		tr = EMU86_EMULATE_STR();
		MODRM_SETRMW(tr);
		goto done;
	}
#endif /* EMU86_EMULATE_STR */

#ifdef EMU86_EMULATE_LLDT
	case 2: {
		/* 0F 00 /2     LLDT r/m16     Load segment selector r/m16 into LDTR. */
		u16 ldtr;
		ldtr = MODRM_GETRMW();
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_MISC_LDT, ldtr, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		EMU86_EMULATE_LLDT(ldtr);
		goto done;
	}
#endif /* EMU86_EMULATE_LLDT */

#ifdef EMU86_EMULATE_LTR
	case 3: {
		/* 0F 00 /3     LTR r/m16     Load r/m16 into task register. */
		u16 tr;
		tr = MODRM_GETRMW();
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_MISC_TR, tr, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		EMU86_EMULATE_LTR(tr);
		goto done;
	}
#endif /* EMU86_EMULATE_LTR */

#if CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT
#ifdef EMU86_EMULATE_VERR
	case 4: {
		/* 0F 00 /4     VERR r/m16     Set ZF=1 if segment specified with r/m16 can be read. */
		bool ok;
		u16 segment_index;
#if CONFIG_LIBEMU86_WANT_16BIT
#define NEED_return_unavailable_instruction
		if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
			goto return_unavailable_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT */
		segment_index = MODRM_GETRMW();
		ok = EMU86_EMULATE_VERR(segment_index);
		EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		goto done;
	}
#endif /* EMU86_EMULATE_VERR */

#ifdef EMU86_EMULATE_VERW
	case 5: {
		/* 0F 00 /5     VERW r/m16     Set ZF=1 if segment specified with r/m16 can be written. */
		bool ok;
		u16 segment_index;
#if CONFIG_LIBEMU86_WANT_16BIT
#define NEED_return_unavailable_instruction
		if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
			goto return_unavailable_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT */
		segment_index = MODRM_GETRMW();
		ok = EMU86_EMULATE_VERW(segment_index);
		EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		goto done;
	}
#endif /* EMU86_EMULATE_VERW */
#endif /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT */

	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;
}
#endif /* EMU86_EMULATE_... */



#if (defined(EMU86_EMULATE_SGDT) || defined(EMU86_EMULATE_SIDT) || \
     defined(EMU86_EMULATE_LGDT) || defined(EMU86_EMULATE_LIDT) || \
     defined(EMU86_EMULATE_SMSW) || defined(EMU86_EMULATE_LMSW) || \
     defined(EMU86_EMULATE_INVLPG))
case 0x0f01: {
	byte_t *rmaddr;
	MODRM_DECODE();
	rmaddr = MODRM_MEMADDR();
	switch (modrm.mi_reg) {

#ifdef EMU86_EMULATE_SGDT
	case 0: {
		/* 0F 01 /0     SGDT m16&32     Store GDTR to m.
		 * 0F 01 /0     SGDT m16&64     Store GDTR to m. */
		u16 limit;
		EMU86_UREG_TYPE base;
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 EMU86_F_IS64(op_flags)
			                                                 ? X86_REGISTER_MISC_GDT_BASEQ
			                                                 : X86_REGISTER_MISC_GDT_BASEL,
			                                                 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		EMU86_EMULATE_SGDT(limit, base);
		IF_64BIT(if (EMU86_F_IS64(op_flags)) {
			EMU86_WRITE_USER_MEMORY(rmaddr, 10);
			EMU86_MEMWRITEW(rmaddr + 0, limit);
			EMU86_MEMWRITEQ(rmaddr + 2, base);
		} else) {
			EMU86_WRITE_USER_MEMORY(rmaddr, 6);
			EMU86_MEMWRITEW(rmaddr + 0, limit);
			EMU86_MEMWRITEL(rmaddr + 2, base);
		}
		goto done;
	}
#endif /* EMU86_EMULATE_SGDT */

#ifdef EMU86_EMULATE_SIDT
	case 1: {
		/* 0F 01 /1     SIDT m16&32     Store IDTR to m.
		 * 0F 01 /1     SIDT m16&64     Store IDTR to m. */
		u16 limit;
		EMU86_UREG_TYPE base;
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 EMU86_F_IS64(op_flags)
			                                                 ? X86_REGISTER_MISC_IDT_BASEQ
			                                                 : X86_REGISTER_MISC_IDT_BASEL,
			                                                 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		EMU86_EMULATE_SIDT(limit, base);
		IF_64BIT(if (EMU86_F_IS64(op_flags)) {
			EMU86_WRITE_USER_MEMORY(rmaddr, 10);
			EMU86_MEMWRITEW(rmaddr + 0, limit);
			EMU86_MEMWRITEQ(rmaddr + 2, base);
		} else) {
			EMU86_WRITE_USER_MEMORY(rmaddr, 6);
			EMU86_MEMWRITEW(rmaddr + 0, limit);
			EMU86_MEMWRITEL(rmaddr + 2, base);
		}
		goto done;
	}
#endif /* EMU86_EMULATE_SIDT */


#ifdef EMU86_EMULATE_LGDT
	case 2: {
		/* 0F 01 /2     LGDT m16&32     Load m into GDTR.
		 * 0F 01 /2     LGDT m16&64     Load m into GDTR. */
		u16 limit;
		EMU86_UREG_TYPE base;
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
		IF_64BIT(if (EMU86_F_IS64(op_flags)) {
			EMU86_READ_USER_MEMORY(rmaddr, 10);
			limit = EMU86_MEMREADW(rmaddr + 0);
			base  = EMU86_MEMREADQ(rmaddr + 2);
		} else) {
			EMU86_READ_USER_MEMORY(rmaddr, 6);
			limit = EMU86_MEMREADW(rmaddr + 0);
			base  = EMU86_MEMREADL(rmaddr + 2);
		}
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 EMU86_F_IS64(op_flags)
			                                                 ? X86_REGISTER_MISC_GDT_BASEQ
			                                                 : X86_REGISTER_MISC_GDT_BASEL,
			                                                 base, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		EMU86_EMULATE_LGDT(limit, base);
		goto done;
	}
#endif /* EMU86_EMULATE_LGDT */


#ifdef EMU86_EMULATE_LIDT
	case 3: {
		/* 0F 01 /3     LIDT m16&32     Load m into IDTR.
		 * 0F 01 /3     LIDT m16&64     Load m into IDTR. */
		u16 limit;
		EMU86_UREG_TYPE base;
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
		IF_64BIT(if (EMU86_F_IS64(op_flags)) {
			EMU86_READ_USER_MEMORY(rmaddr, 10);
			limit = EMU86_MEMREADW(rmaddr + 0);
			base  = EMU86_MEMREADQ(rmaddr + 2);
		} else) {
			EMU86_READ_USER_MEMORY(rmaddr, 6);
			limit = EMU86_MEMREADW(rmaddr + 0);
			base  = EMU86_MEMREADL(rmaddr + 2);
		}
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 EMU86_F_IS64(op_flags)
			                                                 ? X86_REGISTER_MISC_IDT_BASEQ
			                                                 : X86_REGISTER_MISC_IDT_BASEL,
			                                                 base, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		EMU86_EMULATE_LIDT(limit, base);
		goto done;
	}
#endif /* EMU86_EMULATE_LIDT */

#ifdef EMU86_EMULATE_SMSW
	case 4: {
		/* 0F 01 /4     SMSW r/m16     Store machine status word to r/m16. */
		u16 msw;
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_CONTROL_CR0, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		msw = EMU86_EMULATE_SMSW();
		MODRM_SETRMW(msw);
		goto done;
	}
#endif /* EMU86_EMULATE_SMSW */

#ifdef EMU86_EMULATE_LMSW
	case 6: {
		/* 0F 01 /6     LMSW r/m16     Loads r/m16 in machine status word of CR0. */
		u16 msw;
		msw = MODRM_GETRMW();
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_CONTROL_CR0, msw, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#define NEED_return_privileged_instruction_rmreg
			goto return_privileged_instruction_rmreg;
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		EMU86_EMULATE_LMSW(msw);
		goto done;
	}
#endif /* EMU86_EMULATE_LMSW */

#ifdef EMU86_EMULATE_INVLPG
	case 7: {
		/* 0F 01 /7     INVLPG m      Invalidate TLB entries for page containing m. */
		byte_t *addr;
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm_rmreg
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#define NEED_return_privileged_instruction_rmreg
		if (EMU86_ISUSER())
			goto return_privileged_instruction_rmreg;
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		addr = MODRM_MEMADDR();
		EMU86_EMULATE_INVLPG(addr);
		goto done;
	}
#endif /* EMU86_EMULATE_INVLPG */

	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;
}
#endif /* EMU86_EMULATE_... */


#if CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT
#ifdef EMU86_EMULATE_LAR
case 0x0f02: {
	/* 0F 02 /r     LAR r16, r16/m16     r16 := access rights referenced by r16/m16 */
	bool ok;
	u16 segment_index;
	u16 segment_rights;
#if CONFIG_LIBEMU86_WANT_16BIT
#define NEED_return_unavailable_instruction
	if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
		goto return_unavailable_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT */
	MODRM_DECODE();
	segment_index = MODRM_GETRMW();
	ok = EMU86_EMULATE_LAR(segment_index,
	                       segment_rights);
	EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
	if (ok)
		MODRM_SETRMREGW(segment_rights);
	goto done;
}
#endif /* EMU86_EMULATE_LAR */


#ifdef EMU86_EMULATE_LSL
case 0x0f03: {
	/*         0F 03 /r     LSL r16, r16/m16     Load: r16 := segment limit, selector r16/m16.
	 *         0F 03 /r     LSL r32, r32/m16     Load: r32 := segment limit, selector r32/m16.
	 * REX.W + 0F 03 /r     LSL r64, r32/m16     Load: r64 := segment limit, selector r32/m16 */
	bool ok;
	u16 segment_index;
	EMU86_UREG_TYPE limit;
#if CONFIG_LIBEMU86_WANT_16BIT
#define NEED_return_unavailable_instruction
	if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
		goto return_unavailable_instruction;
#endif /* CONFIG_LIBEMU86_WANT_16BIT */
	MODRM_DECODE();
	segment_index = MODRM_GETRMW();
	ok = EMU86_EMULATE_LSL(segment_index, limit);
	EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
	if (ok) {
		IF_64BIT(if (IS_64BIT()) {
			MODRM_SETREGQ(limit);
		} else) if (!IS_16BIT()) {
			MODRM_SETREGL(limit);
		} else {
			MODRM_SETREGW(limit);
		}
	}
	goto done;
}
#endif /* EMU86_EMULATE_LSL */
#endif /* CONFIG_LIBEMU86_WANT_32BIT || CONFIG_LIBEMU86_WANT_64BIT */


}
EMU86_INTELLISENSE_END
