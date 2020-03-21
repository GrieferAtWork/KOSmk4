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
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(pmode) {


#if (defined(EMU86_EMULATE_SLDT) || defined(EMU86_EMULATE_STR) || \
     defined(EMU86_EMULATE_LLDT) || defined(EMU86_EMULATE_LTR) || \
     defined(EMU86_EMULATE_VERR) || defined(EMU86_EMULATE_VERW))

case 0x0f00: {
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#ifdef EMU86_EMULATE_SLDT
	case 0: {
		/* REX.W + 0F 00 /0     SLDT r/m16     Stores segment selector from LDTR in r64/m16. */
		u16 ldtr;
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f00, 0);
#endif /* EMU86_EMULATE_CHECKUSER */
		ldtr = EMU86_EMULATE_SLDT();
		MODRM_SETRMW(ldtr);
		goto done;
	}
#endif /* EMU86_EMULATE_SLDT */

#ifdef EMU86_EMULATE_STR
	case 1: {
		/* 0F 00 /1     STR r/m16     Stores segment selector from TR in r/m16. */
		u16 tr;
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f00, 1);
#endif /* EMU86_EMULATE_CHECKUSER */
		tr = EMU86_EMULATE_STR();
		MODRM_SETRMW(tr);
		goto done;
	}
#endif /* EMU86_EMULATE_STR */

#ifdef EMU86_EMULATE_LLDT
	case 2: {
		/* 0F 00 /2     LLDT r/m16     Load segment selector r/m16 into LDTR. */
		u16 ldtr;
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f00, 2);
#endif /* EMU86_EMULATE_CHECKUSER */
		ldtr = MODRM_GETRMW();
		EMU86_EMULATE_LLDT(ldtr);
		goto done;
	}
#endif /* EMU86_EMULATE_LLDT */

#ifdef EMU86_EMULATE_LTR
	case 3: {
		/* 0F 00 /3     LTR r/m16     Load r/m16 into task register. */
		u16 tr;
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f00, 3);
#endif /* EMU86_EMULATE_CHECKUSER */
		tr = MODRM_GETRMW();
		EMU86_EMULATE_LTR(tr);
		goto done;
	}
#endif /* EMU86_EMULATE_LTR */

#ifdef EMU86_EMULATE_VERR
	case 4: {
		/* 0F 00 /4     VERR r/m16     Set ZF=1 if segment specified with r/m16 can be read. */
		bool ok;
		u16 segment_index;
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
		segment_index = MODRM_GETRMW();
		ok = EMU86_EMULATE_VERW(segment_index);
		EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		goto done;
	}
#endif /* EMU86_EMULATE_VERW */

	default:
		break;
	}
	goto return_unknown_instruction;
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
#ifndef EMU86_EMULATE_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			EMU86_EMULATE_THROW_MODRM_EXPECTED_MEMORY_RMREG(0x0f01, 0);
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f01, 0);
#endif /* EMU86_EMULATE_CHECKUSER */
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
#ifndef EMU86_EMULATE_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			EMU86_EMULATE_THROW_MODRM_EXPECTED_MEMORY_RMREG(0x0f01, 1);
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f01, 1);
#endif /* EMU86_EMULATE_CHECKUSER */
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
#ifndef EMU86_EMULATE_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			EMU86_EMULATE_THROW_MODRM_EXPECTED_MEMORY_RMREG(0x0f01, 2);
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f01, 2);
#endif /* EMU86_EMULATE_CHECKUSER */
		IF_64BIT(if (EMU86_F_IS64(op_flags)) {
			EMU86_READ_USER_MEMORY(rmaddr, 10);
			limit = EMU86_MEMREADW(rmaddr + 0);
			base  = EMU86_MEMREADQ(rmaddr + 2);
		} else) {
			EMU86_READ_USER_MEMORY(rmaddr, 6);
			limit = EMU86_MEMREADW(rmaddr + 0);
			base  = EMU86_MEMREADL(rmaddr + 2);
		}
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
#ifndef EMU86_EMULATE_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			EMU86_EMULATE_THROW_MODRM_EXPECTED_MEMORY_RMREG(0x0f01, 3);
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f01, 3);
#endif /* EMU86_EMULATE_CHECKUSER */
		IF_64BIT(if (EMU86_F_IS64(op_flags)) {
			EMU86_READ_USER_MEMORY(rmaddr, 10);
			limit = EMU86_MEMREADW(rmaddr + 0);
			base  = EMU86_MEMREADQ(rmaddr + 2);
		} else) {
			EMU86_READ_USER_MEMORY(rmaddr, 6);
			limit = EMU86_MEMREADW(rmaddr + 0);
			base  = EMU86_MEMREADL(rmaddr + 2);
		}
		EMU86_EMULATE_LIDT(limit, base);
		goto done;
	}
#endif /* EMU86_EMULATE_LIDT */

#ifdef EMU86_EMULATE_SMSW
	case 4: {
		/* 0F 01 /4     SMSW r/m16     Store machine status word to r/m16. */
		u16 msw;
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f01, 4);
#endif /* EMU86_EMULATE_CHECKUSER */
		msw = EMU86_EMULATE_SMSW();
		MODRM_SETRMW(msw);
		goto done;
	}
#endif /* EMU86_EMULATE_SMSW */

#ifdef EMU86_EMULATE_LMSW
	case 6: {
		/* 0F 01 /6     LMSW r/m16     Loads r/m16 in machine status word of CR0. */
		u16 msw;
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f01, 6);
#endif /* EMU86_EMULATE_CHECKUSER */
		msw = MODRM_GETRMW();
		EMU86_EMULATE_LMSW(msw);
		goto done;
	}
#endif /* EMU86_EMULATE_LMSW */

#ifdef EMU86_EMULATE_INVLPG
	case 7: {
		/* 0F 01 /7     INVLPG m      Invalidate TLB entries for page containing m. */
		byte_t *addr;
#ifndef EMU86_EMULATE_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			EMU86_EMULATE_THROW_MODRM_EXPECTED_MEMORY_RMREG(0x0f01, 7);
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
#if EMU86_EMULATE_CHECKUSER
		if (EMU86_ISUSER())
			EMU86_EMULATE_THROW_PRIVILEGED_INSTRUCTION_RMREG(0x0f01, 7);
#endif /* EMU86_EMULATE_CHECKUSER */
		addr = MODRM_MEMADDR();
		EMU86_EMULATE_INVLPG(addr);
		goto done;
	}
#endif /* EMU86_EMULATE_INVLPG */

	default:
		break;
	}
	goto return_unknown_instruction;
}
#endif /* EMU86_EMULATE_... */


}
EMU86_INTELLISENSE_END
