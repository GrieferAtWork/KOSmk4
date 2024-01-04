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
#ifdef __INTELLISENSE__
#define EMU86_EMULATE_CONFIG_WANT_SLDT    1
#define EMU86_EMULATE_CONFIG_WANT_LLDT    1
#define EMU86_EMULATE_CONFIG_WANT_STR     1
#define EMU86_EMULATE_CONFIG_WANT_LTR     1
#define EMU86_EMULATE_CONFIG_WANT_SGDT    1
#define EMU86_EMULATE_CONFIG_WANT_LGDT    1
#define EMU86_EMULATE_CONFIG_WANT_SIDT    1
#define EMU86_EMULATE_CONFIG_WANT_LIDT    1
#define EMU86_EMULATE_CONFIG_WANT_VERR    1
#define EMU86_EMULATE_CONFIG_WANT_VERW    1
#define EMU86_EMULATE_CONFIG_WANT_SMSW    1
#define EMU86_EMULATE_CONFIG_WANT_LMSW    1
#define EMU86_EMULATE_CONFIG_WANT_MONITOR 1
#define EMU86_EMULATE_CONFIG_WANT_MWAIT   1
#define EMU86_EMULATE_CONFIG_WANT_ENCLS   1
#define EMU86_EMULATE_CONFIG_WANT_STGI    1
#define EMU86_EMULATE_CONFIG_WANT_CLGI    1
#define EMU86_EMULATE_CONFIG_WANT_INVLPG  1
#define EMU86_EMULATE_CONFIG_WANT_RDTSCP  1
#define EMU86_EMULATE_CONFIG_WANT_SWAPGS  1
#define EMU86_EMULATE_CONFIG_WANT_MCOMMIT 1
#define EMU86_EMULATE_CONFIG_WANT_CLZERO  1
#define EMU86_EMULATE_CONFIG_WANT_XGETBV  1
#define EMU86_EMULATE_CONFIG_WANT_XSETBV  1
#define EMU86_EMULATE_CONFIG_WANT_LAR     1
#define EMU86_EMULATE_CONFIG_WANT_LSL     1
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(pmode) {


#if (EMU86_EMULATE_CONFIG_CHECKERROR ||                                 \
     EMU86_EMULATE_CONFIG_WANT_SLDT || EMU86_EMULATE_CONFIG_WANT_STR || \
     EMU86_EMULATE_CONFIG_WANT_LLDT || EMU86_EMULATE_CONFIG_WANT_LTR || \
     ((LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_64BIT) &&     \
      (EMU86_EMULATE_CONFIG_WANT_VERR || EMU86_EMULATE_CONFIG_WANT_VERW)))

case EMU86_OPCODE_ENCODE(0x0f00): {
	MODRM_DECODE();
	switch (modrm.mi_reg) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SLDT
	case 0: {
		/* REX.W + 0F 00 /0     SLDT r/m16     Stores segment selector from LDTR in r64/m16. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_MISC_LDT, 0, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_SLDT && defined(EMU86_EMULATE_SLDT)
		{
			u16 ldtr;
			ldtr = EMU86_EMULATE_SLDT();
			MODRM_SETRMW(ldtr);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SLDT && EMU86_EMULATE_SLDT */
		MODRM_NOSUP_SETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_SLDT || !EMU86_EMULATE_SLDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SLDT */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STR
	case 1: {
		/* 0F 00 /1     STR r/m16     Stores segment selector from TR in r/m16. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_MISC_TR, 0, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_STR && defined(EMU86_EMULATE_STR)
		{
			u16 tr;
			tr = EMU86_EMULATE_STR();
			MODRM_SETRMW(tr);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_STR && EMU86_EMULATE_STR */
		MODRM_NOSUP_SETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_STR || !EMU86_EMULATE_STR */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STR */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LLDT
	case 2: {
		/* 0F 00 /2     LLDT r/m16     Load segment selector r/m16 into LDTR. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LLDT
		u16 ldtr;
		ldtr = MODRM_GETRMW();
#else /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LLDT */
		MODRM_NOSUP_GETRMW();
#endif /* !EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_WANT_LLDT */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_MISC_LDT, 0, ldtr, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LLDT && defined(EMU86_EMULATE_LLDT)
		EMU86_EMULATE_LLDT(ldtr);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LLDT && EMU86_EMULATE_LLDT */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LLDT || !EMU86_EMULATE_LLDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LLDT */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LTR
	case 3: {
		/* 0F 00 /3     LTR r/m16     Load r/m16 into task register. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LTR
		u16 tr;
		tr = MODRM_GETRMW();
#else /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LTR */
		MODRM_NOSUP_GETRMW();
#endif /* !EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_WANT_LTR */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_MISC_TR, 0, tr, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LTR && defined(EMU86_EMULATE_LTR)
		EMU86_EMULATE_LTR(tr);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LTR && EMU86_EMULATE_LTR */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LTR || !EMU86_EMULATE_LTR */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LTR */


#if (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_64BIT || \
     (EMU86_EMULATE_CONFIG_CHECKERROR && LIBEMU86_CONFIG_WANT_16BIT))
#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_VERR
	case 4: {
		/* 0F 00 /4     VERR r/m16     Set ZF=1 if segment specified with r/m16 can be read. */
#if LIBEMU86_CONFIG_WANT_16BIT
		if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
			goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* LIBEMU86_CONFIG_WANT_16BIT */
#if EMU86_EMULATE_CONFIG_WANT_VERR && defined(EMU86_EMULATE_VERR)
		{
			bool ok;
			u16 segment_index;
			segment_index = MODRM_GETRMW();
			ok = EMU86_EMULATE_VERR(segment_index);
			EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_VERR && EMU86_EMULATE_VERR */
		MODRM_NOSUP_GETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_VERR || !EMU86_EMULATE_VERR */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_VERR */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_VERW
	case 5: {
		/* 0F 00 /5     VERW r/m16     Set ZF=1 if segment specified with r/m16 can be written. */
#if LIBEMU86_CONFIG_WANT_16BIT
		if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
			goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* LIBEMU86_CONFIG_WANT_16BIT */
#if EMU86_EMULATE_CONFIG_WANT_VERW && defined(EMU86_EMULATE_VERW)
		{
			bool ok;
			u16 segment_index;
			segment_index = MODRM_GETRMW();
			ok = EMU86_EMULATE_VERW(segment_index);
			EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_VERW && EMU86_EMULATE_VERW */
		MODRM_NOSUP_GETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_VERW || !EMU86_EMULATE_VERW */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_VERW */
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_64BIT || (EMU86_EMULATE_CONFIG_CHECKERROR && LIBEMU86_CONFIG_WANT_16BIT) */


	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	break;
}
#endif /* EMU86_EMULATE_... */






#if (EMU86_EMULATE_CONFIG_WANT_SGDT || EMU86_EMULATE_CONFIG_WANT_SIDT ||        \
     EMU86_EMULATE_CONFIG_WANT_LGDT || EMU86_EMULATE_CONFIG_WANT_LIDT ||        \
     EMU86_EMULATE_CONFIG_WANT_SMSW || EMU86_EMULATE_CONFIG_WANT_LMSW ||        \
     EMU86_EMULATE_CONFIG_WANT_INVLPG || EMU86_EMULATE_CONFIG_CHECKERROR ||     \
     (!EMU86_EMULATE_CONFIG_ONLY_MEMORY &&                                      \
      (EMU86_EMULATE_CONFIG_WANT_STAC || EMU86_EMULATE_CONFIG_WANT_CLAC ||      \
       EMU86_EMULATE_CONFIG_WANT_MONITOR || EMU86_EMULATE_CONFIG_WANT_MWAIT ||  \
       EMU86_EMULATE_CONFIG_WANT_ENCLS || EMU86_EMULATE_CONFIG_WANT_XEND ||     \
       EMU86_EMULATE_CONFIG_WANT_XTEST || EMU86_EMULATE_CONFIG_WANT_RDTSCP ||   \
       EMU86_EMULATE_CONFIG_WANT_MCOMMIT || EMU86_EMULATE_CONFIG_WANT_CLZERO || \
       EMU86_EMULATE_CONFIG_WANT_XGETBV || EMU86_EMULATE_CONFIG_WANT_XSETBV ||  \
       EMU86_EMULATE_CONFIG_WANT_STGI || EMU86_EMULATE_CONFIG_WANT_CLGI ||      \
       (EMU86_EMULATE_CONFIG_WANT_SWAPGS && LIBEMU86_CONFIG_WANT_64BIT))))
case EMU86_OPCODE_ENCODE(0x0f01): {
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SGDT
	case 0: {
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if (EMU86_EMULATE_CONFIG_CHECKERROR && \
     (EMU86_EMULATE_CONFIG_CHECKUSER || !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC))
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {
			switch (modrm.mi_rm) {

			case 1: /* 0F 01 C1     VMCALL       Call to VM monitor by causing VM exit. */
			case 2: /* 0F 01 C2     VMLAUNCH     Launch virtual machine managed by current VMCS. */
			case 3: /* 0F 01 C3     VMRESUME     Resume virtual machine managed by current VMCS. */
			case 4: /* 0F 01 C4     VMXOFF       Leaves VMX operation. */
				if (EMU86_ISUSER())
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg

			default: break;
			}
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

		/* 0F 01 /0     SGDT m16&32     Store GDTR to m.
		 * 0F 01 /0     SGDT m16&64     Store GDTR to m. */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 IF_64BIT(EMU86_F_IS64(op_flags)
			                                                 ?  X86_REGISTER_MISC_GDT_BASEQ
			                                                 :) X86_REGISTER_MISC_GDT_BASEL,
			                                                 0, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_SGDT && defined(EMU86_EMULATE_SGDT)
		{
			byte_t *rmaddr;
			u16 limit;
			EMU86_UREG_TYPE base;
			EMU86_EMULATE_SGDT(limit, base);
			rmaddr = MODRM_MEMADDR();
			IF_64BIT(if (EMU86_F_IS64(op_flags)) {
				EMU86_WRITE_USER_MEMORY(rmaddr, 10);
				EMU86_MEMWRITEW(rmaddr + 0, limit);
				EMU86_MEMWRITEQ(rmaddr + 2, base);
			} else) {
				EMU86_WRITE_USER_MEMORY(rmaddr, 6);
				EMU86_MEMWRITEW(rmaddr + 0, limit);
				EMU86_MEMWRITEL(rmaddr + 2, base);
			}
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SGDT && EMU86_EMULATE_SGDT */
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            EMU86_F_IS64(op_flags) ? 10 : 6,
		                            false, true);
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_SGDT || !EMU86_EMULATE_SGDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SGDT */


#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SIDT ||      \
     (!EMU86_EMULATE_CONFIG_ONLY_MEMORY &&                                     \
      (EMU86_EMULATE_CONFIG_WANT_STAC || EMU86_EMULATE_CONFIG_WANT_CLAC ||     \
       EMU86_EMULATE_CONFIG_WANT_MONITOR || EMU86_EMULATE_CONFIG_WANT_MWAIT || \
       EMU86_EMULATE_CONFIG_WANT_ENCLS)))
	case 1: {
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if ((EMU86_EMULATE_CONFIG_CHECKERROR &&                                                     \
      (EMU86_EMULATE_CONFIG_CHECKUSER || !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC)) || \
     EMU86_EMULATE_CONFIG_WANT_STAC || EMU86_EMULATE_CONFIG_WANT_CLAC ||                     \
     EMU86_EMULATE_CONFIG_WANT_MONITOR || EMU86_EMULATE_CONFIG_WANT_MWAIT ||                 \
     EMU86_EMULATE_CONFIG_WANT_ENCLS)
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {
			switch (modrm.mi_rm) {

#if ((EMU86_EMULATE_CONFIG_CHECKERROR && defined(EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER)) || \
     (EMU86_EMULATE_CONFIG_WANT_MONITOR && defined(EMU86_EMULATE_MONITOR)))
#define EMU86_EMULATE_HAVE_MONITOR
			case 0:
				/* 0F 01 C8     MONITOR     Sets up a linear address range to be monitored by hardware  and
				 *                          activates the monitor. The address range should be a write-back
				 *                          memory caching type. The address is DS:RAX/EAX/AX. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (EMU86_ISUSER()) {
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_MONITOR && defined(EMU86_EMULATE_MONITOR)
				EMU86_EMULATE_MONITOR(EMU86_SEGADDR(EMU86_GETDSBASE(), EMU86_GETPAX()),
				                      EMU86_GETECX(), EMU86_GETEDX());
				goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MONITOR && EMU86_EMULATE_MONITOR */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
				if (EMU86_GETECX() != 0) {
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,
					                                                 X86_REGISTER_MISC_MONITOR, 0,
					                                                 EMU86_GETECX(), 0);
				}
#endif /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_MONITOR || !EMU86_EMULATE_MONITOR */
#endif /* ... */


#if ((EMU86_EMULATE_CONFIG_CHECKERROR && defined(EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER)) || \
     (EMU86_EMULATE_CONFIG_WANT_MWAIT && defined(EMU86_EMULATE_WAIT)))
#define EMU86_EMULATE_HAVE_MWAIT
			case 1:
				/* 0F 01 C9     MWAIT     A hint that allows the processor to stop instruction execution
				 *                        and enter  an implementation-dependent  optimized state  until
				 *                        occurrence of a class of events. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (EMU86_ISUSER()) {
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
				{
					u32 ecx = EMU86_GETECX();
					if ((ecx & ~1) != 0) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
						EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,
						                                                 X86_REGISTER_MISC_MWAIT, 0, ecx, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
						goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
					}
#if EMU86_EMULATE_CONFIG_WANT_MWAIT && defined(EMU86_EMULATE_MWAIT)
					EMU86_EMULATE_MWAIT(ecx, EMU86_GETEAX());
					goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_MWAIT && EMU86_EMULATE_MWAIT */
					goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_MWAIT || !EMU86_EMULATE_MWAIT */
				}
#endif /* ... */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_CLAC
#define EMU86_EMULATE_HAVE_CLAC
			case 2:
				/* 0F 01 CA     CLAC     Clear the AC flag in the EFLAGS register. */
#if EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_ALLOW_USER_STAC_CLAC
				if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
					                                                 IF_64BIT(EMU86_F_IS64(op_flags)
					                                                 ?  X86_REGISTER_MISC_RFLAGS
					                                                 :) X86_REGISTER_MISC_EFLAGS,
					                                                 0, ~EFLAGS_AC, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_ALLOW_USER_STAC_CLAC */
#if EMU86_EMULATE_CONFIG_WANT_CLAC
				{
					u32 eflags;
					eflags = EMU86_GETFLAGS();
					eflags &= ~EFLAGS_AC;
					EMU86_SETFLAGS(eflags);
				}
				goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_CLAC */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_CLAC */
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_CLAC */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STAC
#define EMU86_EMULATE_HAVE_STAC
			case 3:
				/* 0F 01 CB     STAC     Set the AC flag in the EFLAGS register. */
#if EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_ALLOW_USER_STAC_CLAC
				if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
					                                                 IF_64BIT(EMU86_F_IS64(op_flags)
					                                                 ?  X86_REGISTER_MISC_RFLAGS
					                                                 :) X86_REGISTER_MISC_EFLAGS,
					                                                 0, ~EFLAGS_AC, EFLAGS_AC);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_ALLOW_USER_STAC_CLAC */
#if EMU86_EMULATE_CONFIG_WANT_STAC
				{
					u32 eflags;
					eflags = EMU86_GETFLAGS();
					eflags |= EFLAGS_AC;
					EMU86_SETFLAGS(eflags);
				}
				goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_STAC */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_STAC */
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STAC */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_ENCLS
#define EMU86_EMULATE_HAVE_ENCLS
			case 7:
				if (op_flags & (EMU86_F_f2 | EMU86_F_f3 | EMU86_F_66))
					goto return_unexpected_prefix_rmreg;
#define NEED_return_unexpected_prefix_rmreg
				/* 0F 01 CF     ENCLS     This instruction is  used to execute  privileged Intel SGX  leaf
				 *                        functions that are used for managing and debugging the enclaves. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (EMU86_ISUSER()) {
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_ENCLS && defined(EMU86_EMULATE_ENCLS)
				EMU86_EMULATE_ENCLS(EMU86_GETEAX());
				goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ENCLS && EMU86_EMULATE_ENCLS */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
				EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,
				                                                 X86_REGISTER_MISC_ENCLS, 0,
				                                                 EMU86_GETEAX(), 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* !EMU86_EMULATE_CONFIG_WANT_ENCLS || !EMU86_EMULATE_ENCLS */
				break;
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_ENCLS */


#if (EMU86_EMULATE_CONFIG_CHECKERROR && \
     (EMU86_EMULATE_CONFIG_CHECKUSER || !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC))
#ifndef EMU86_EMULATE_HAVE_MONITOR
#define EMU86_EMULATE_HAVE_0F01_1_FALLBACK
			case 0:
				/* 0F 01 C8     MONITOR     Sets up a linear address range to be monitored by hardware  and
				 *                          activates the monitor. The address range should be a write-back
				 *                          memory caching type. The address is DS:RAX/EAX/AX. */
#endif /* !EMU86_EMULATE_HAVE_MONITOR */
#undef EMU86_EMULATE_HAVE_MONITOR
#ifndef EMU86_EMULATE_HAVE_MWAIT
#define EMU86_EMULATE_HAVE_0F01_1_FALLBACK
			case 1:
				/* 0F 01 C9     MWAIT     A hint that allows the processor to stop instruction execution
				 *                        and enter  an implementation-dependent  optimized state  until
				 *                        occurrence of a class of events. */
#endif /* !EMU86_EMULATE_HAVE_MWAIT */
#undef EMU86_EMULATE_HAVE_MWAIT
#ifndef EMU86_EMULATE_HAVE_CLAC
#define EMU86_EMULATE_HAVE_0F01_1_FALLBACK
			case 2:
				/* 0F 01 CA     CLAC     Clear the AC flag in the EFLAGS register. */
#endif /* !EMU86_EMULATE_HAVE_CLAC */
#undef EMU86_EMULATE_HAVE_CLAC
#ifndef EMU86_EMULATE_HAVE_STAC
#define EMU86_EMULATE_HAVE_0F01_1_FALLBACK
			case 3:
				/* 0F 01 CB     STAC     Set the AC flag in the EFLAGS register. */
#endif /* !EMU86_EMULATE_HAVE_STAC */
#undef EMU86_EMULATE_HAVE_STAC
#ifndef EMU86_EMULATE_HAVE_ENCLS
			case 7:
#define EMU86_EMULATE_HAVE_0F01_1_FALLBACK
				/* 0F 01 CF     ENCLS     This instruction is  used to execute  privileged Intel SGX  leaf
				 *                        functions that are used for managing and debugging the enclaves. */
#endif /* !EMU86_EMULATE_HAVE_ENCLS */
#undef EMU86_EMULATE_HAVE_ENCLS
#ifdef EMU86_EMULATE_HAVE_0F01_1_FALLBACK
#undef EMU86_EMULATE_HAVE_0F01_1_FALLBACK
				if (EMU86_ISUSER())
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* EMU86_EMULATE_HAVE_0F01_1_FALLBACK */
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR && (EMU86_EMULATE_CONFIG_CHECKUSER || !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) */

			default: break;
			}
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SIDT
		/* 0F 01 /1     SIDT m16&32     Store IDTR to m.
		 * 0F 01 /1     SIDT m16&64     Store IDTR to m. */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 IF_64BIT(EMU86_F_IS64(op_flags)
			                                                 ?  X86_REGISTER_MISC_IDT_BASEQ
			                                                 :) X86_REGISTER_MISC_IDT_BASEL,
			                                                 0, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_SIDT && defined(EMU86_EMULATE_SIDT)
		{
			u16 limit;
			byte_t *rmaddr;
			EMU86_UREG_TYPE base;
			EMU86_EMULATE_SIDT(limit, base);
			rmaddr = MODRM_MEMADDR();
			IF_64BIT(if (EMU86_F_IS64(op_flags)) {
				EMU86_WRITE_USER_MEMORY(rmaddr, 10);
				EMU86_MEMWRITEW(rmaddr + 0, limit);
				EMU86_MEMWRITEQ(rmaddr + 2, base);
			} else) {
				EMU86_WRITE_USER_MEMORY(rmaddr, 6);
				EMU86_MEMWRITEW(rmaddr + 0, limit);
				EMU86_MEMWRITEL(rmaddr + 2, base);
			}
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SIDT && EMU86_EMULATE_SIDT */
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            EMU86_F_IS64(op_flags) ? 10 : 6,
		                            false, true);
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_SIDT || !EMU86_EMULATE_SIDT */
#else /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SIDT */
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_WANT_SIDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SIDT || (WANT_<0F01h/1/0-7>) */


#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LGDT ||   \
     (!EMU86_EMULATE_CONFIG_ONLY_MEMORY &&                                  \
      (EMU86_EMULATE_CONFIG_WANT_XEND || EMU86_EMULATE_CONFIG_WANT_XTEST || \
       EMU86_EMULATE_CONFIG_WANT_XGETBV || EMU86_EMULATE_CONFIG_WANT_XSETBV)))
	case 2: {
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT
		u16 limit;
		EMU86_UREG_TYPE base;
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT */

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if ((EMU86_EMULATE_CONFIG_CHECKERROR &&                                                     \
      (EMU86_EMULATE_CONFIG_CHECKUSER || !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC)) || \
     (EMU86_EMULATE_CONFIG_WANT_XEND || EMU86_EMULATE_CONFIG_WANT_XTEST ||                   \
      EMU86_EMULATE_CONFIG_WANT_XGETBV || EMU86_EMULATE_CONFIG_WANT_XSETBV))
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {
			switch (modrm.mi_rm) {

#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XGETBV
#define EMU86_EMULATE_HAVE_XGETBV
			case 0:
				/* NP 0F 01 D0     XGETBV     Reads an XCR specified by ECX into EDX:EAX. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
					                                                 X86_REGISTER_XCR, EMU86_GETECX(), 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_XGETBV && defined(EMU86_EMULATE_XGETBV)
				{
					u64 value;
					value = EMU86_EMULATE_XGETBV(EMU86_GETECX());
					EMU86_SETEAX((u32)(value));
					EMU86_SETEDX((u32)(value >> 32));
					goto done;
				}
#else /* EMU86_EMULATE_CONFIG_WANT_XGETBV && EMU86_EMULATE_XGETBV */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
				EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDINV,
				                                                 X86_REGISTER_XCR, EMU86_GETECX(), 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* !EMU86_EMULATE_CONFIG_WANT_XGETBV || !EMU86_EMULATE_XGETBV */
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XGETBV */



#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XSETBV
#define EMU86_EMULATE_HAVE_XSETBV
			case 1:
				/* NP 0F 01 D1     XSETBV     Write the value in EDX:EAX to the XCR specified by ECX. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
					                                                 X86_REGISTER_XCR, EMU86_GETECX(),
					                                                 EMU86_GETEAX(), EMU86_GETEDX());
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_XSETBV && defined(EMU86_EMULATE_XSETBV)
				EMU86_EMULATE_XSETBV(EMU86_GETECX(),
				                     ((u64)EMU86_GETEAX()) |
				                     ((u64)EMU86_GETEDX() << 32));
				goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_XSETBV && EMU86_EMULATE_XSETBV */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
				EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRINV,
				                                                 X86_REGISTER_XCR, EMU86_GETECX(),
				                                                 EMU86_GETEAX(), EMU86_GETEDX());
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* !EMU86_EMULATE_CONFIG_WANT_XSETBV || !EMU86_EMULATE_XSETBV */
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XSETBV */



#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XEND
			case 5: /* 0F 01 D5     XEND       Specifies the end of an RTM code region. */
				/* XEND is supposed to RAISE a #GP(0) when executed outside of a transaction
				 * Since we always choose the fallback-branch, this instruction should never
				 * be encountered during normal execution, and  as such is considered to  be
				 * unsupported (during said normal execution) */
#if !defined(EMU86_EMULATE_XTEST_IS_ONE) && !defined(EMU86_EMULATE_XTEST_IS_ZERO)
				if (EMU86_EMULATE_XTEST())
#endif /* !EMU86_EMULATE_XTEST_IS_ONE && !EMU86_EMULATE_XTEST_IS_ZERO */
				{
#ifndef EMU86_EMULATE_XTEST_IS_ZERO
#ifdef EMU86_EMULATE_RETURN_AFTER_XEND
					EMU86_SETPCPTR(REAL_IP());
					EMU86_EMULATE_RETURN_AFTER_XEND();
#else /* EMU86_EMULATE_RETURN_AFTER_XEND */
					goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_RETURN_AFTER_XEND */
#endif /* !EMU86_EMULATE_XTEST_IS_ZERO */
				}
#if !defined(EMU86_EMULATE_XTEST_IS_ONE) && !defined(EMU86_EMULATE_XTEST_IS_ZERO)
				else
#endif /* !EMU86_EMULATE_XTEST_IS_ONE && !EMU86_EMULATE_XTEST_IS_ZERO */
				{
#ifndef EMU86_EMULATE_XTEST_IS_ONE
#ifdef EMU86_EMULATE_RETURN_AFTER_INT
					EMU86_SETPCPTR(REAL_IP());
					EMU86_EMULATE_RETURN_AFTER_INT(0x0d); /* #GP */
#else /* EMU86_EMULATE_RETURN_AFTER_INT */
					goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_RETURN_AFTER_INT */
#endif /* !EMU86_EMULATE_XTEST_IS_ONE */
				}
				__builtin_unreachable();
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_XEND */


#if EMU86_EMULATE_CONFIG_WANT_XTEST
			case 6: /* 0F 01 D6     XTEST      Test if executing in a transactional region */
				/* XTEST clears EFLAGS.ZF if inside of a transaction, and sets it if outside. */
				{
					u32 eflags;
					eflags = EMU86_GETFLAGS();
#ifdef EMU86_EMULATE_XTEST_IS_ZERO
					/* xtest() should always indicate outside-of-rtm */
					eflags |= EFLAGS_ZF;
#elif defined(EMU86_EMULATE_XTEST_IS_ONE)
					/* xtest() should always indicate inside-of-rtm */
					eflags &= ~EFLAGS_ZF;
#else /* ... */
					eflags &= ~EFLAGS_ZF;
					if (EMU86_EMULATE_XTEST())
						eflags |= EFLAGS_ZF;
#endif /* !... */
					/* Intel documents that these flags are always cleared... */
					eflags &= ~(EFLAGS_CF | EFLAGS_OF | EFLAGS_SF | EFLAGS_PF | EFLAGS_AF);
					EMU86_SETFLAGS(eflags);
				}
				goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR
			case 6: /* 0F 01 D6     XTEST      Test if executing in a transactional region */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */



#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_ENCLU
#define EMU86_EMULATE_HAVE_ENCLU
			case 7:
				if (op_flags & (EMU86_F_f2 | EMU86_F_f3 | EMU86_F_66))
					goto return_unexpected_prefix_rmreg;
#define NEED_return_unexpected_prefix_rmreg
				/* 0F 01 D7     ENCLU      This instruction is used to execute non-privileged Intel SGX leaf functions. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (!EMU86_ISUSER()) { /* Only allowed in user-space... */
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_ENCLU && defined(EMU86_EMULATE_ENCLU)
				EMU86_EMULATE_ENCLU(EMU86_GETEAX());
				goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ENCLU && EMU86_EMULATE_ENCLU */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
				EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,
				                                                 X86_REGISTER_MISC_ENCLU, 0,
				                                                 EMU86_GETEAX(), 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* !EMU86_EMULATE_CONFIG_WANT_ENCLU || !EMU86_EMULATE_ENCLU */
				break;
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_ENCLU */


#if (EMU86_EMULATE_CONFIG_CHECKERROR && \
     (EMU86_EMULATE_CONFIG_CHECKUSER || !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC))
#ifndef EMU86_EMULATE_HAVE_XGETBV
			case 0: /* 0F 01 D0     XGETBV     Reads an XCR specified by ECX into EDX:EAX. */
#endif /* !EMU86_EMULATE_HAVE_XGETBV */
#undef EMU86_EMULATE_HAVE_XGETBV
#ifndef EMU86_EMULATE_HAVE_XSETBV
			case 1: /* 0F 01 D1     XSETBV     Write the value in EDX:EAX to the XCR specified by ECX. */
#endif /* !EMU86_EMULATE_HAVE_XSETBV */
#undef EMU86_EMULATE_HAVE_XSETBV
			case 4: /* 0F 01 D4     VMFUNC     Invoke VM function specified in EAX. */
#ifndef EMU86_EMULATE_HAVE_ENCLU
			case 7: /* 0F 01 D7     ENCLU      This instruction is used to execute non-privileged Intel SGX leaf functions. */
#endif /* !EMU86_EMULATE_HAVE_ENCLU */
#undef EMU86_EMULATE_HAVE_ENCLU
				if (EMU86_ISUSER())
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR && ... */

			default: break;
			}
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */


		/* 0F 01 /2     LGDT m16&32     Load m into GDTR.
		 * 0F 01 /2     LGDT m16&64     Load m into GDTR. */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT
		{
			byte_t *rmaddr;
			rmaddr = MODRM_MEMADDR();
			IF_64BIT(if (EMU86_F_IS64(op_flags)) {
				EMU86_READ_USER_MEMORY(rmaddr, 10);
				limit = EMU86_MEMREADW(rmaddr + 0);
				base  = EMU86_MEMREADQ(rmaddr + 2);
			} else) {
				EMU86_READ_USER_MEMORY(rmaddr, 6);
				limit = EMU86_MEMREADW(rmaddr + 0);
				base  = EMU86_MEMREADL(rmaddr + 2);
			}
		}
		(void)limit;
		(void)base;
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LGDT */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 IF_64BIT(EMU86_F_IS64(op_flags)
			                                                 ?  X86_REGISTER_MISC_GDT_BASEQ
			                                                 :) X86_REGISTER_MISC_GDT_BASEL,
			                                                 limit, base, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LGDT && defined(EMU86_EMULATE_LGDT)
		EMU86_EMULATE_LGDT(limit, base);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LGDT && EMU86_EMULATE_LGDT */
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            EMU86_F_IS64(op_flags) ? 10 : 6,
		                            true, false);
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LGDT || !EMU86_EMULATE_LGDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LGDT || ... */


#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LIDT || \
     (!EMU86_EMULATE_CONFIG_ONLY_MEMORY &&                                \
      (EMU86_EMULATE_CONFIG_WANT_STGI || EMU86_EMULATE_CONFIG_WANT_CLGI)))
	case 3: {
		/* 0F 01 /3     LIDT m16&32     Load m into IDTR.
		 * 0F 01 /3     LIDT m16&64     Load m into IDTR. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LIDT
		u16 limit;
		EMU86_UREG_TYPE base;
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LIDT */

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if ((EMU86_EMULATE_CONFIG_CHECKERROR &&                                                     \
      (EMU86_EMULATE_CONFIG_CHECKUSER || !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC)) || \
     (EMU86_EMULATE_CONFIG_WANT_STGI || EMU86_EMULATE_CONFIG_WANT_CLGI))
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {
			switch (modrm.mi_rm) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || (EMU86_EMULATE_CONFIG_WANT_STGI || EMU86_EMULATE_CONFIG_WANT_CLGI)
#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STGI
#define EMU86_EMULATE_HAVE_STGI
			case 4: /* stgi */
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_STGI */
#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_CLGI
#define EMU86_EMULATE_HAVE_CLGI
			case 5: /* clgi */
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_CLGI */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
#if EMU86_EMULATE_CONFIG_CHECKERROR || (EMU86_EMULATE_CONFIG_WANT_STGI && EMU86_EMULATE_CONFIG_WANT_CLGI)
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
					                                                 X86_REGISTER_MISC_GI, 0,
					                                                 modrm.mi_rm == 4, 0);
#elif EMU86_EMULATE_CONFIG_WANT_STGI
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
					                                                 X86_REGISTER_MISC_GI, 0, 1, 0);
#else /* ... */
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
					                                                 X86_REGISTER_MISC_GI, 0, 0, 0);
#endif /* !... */
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_CHECKERROR || (EMU86_EMULATE_CONFIG_WANT_STGI && EMU86_EMULATE_CONFIG_WANT_CLGI)
#if defined(EMU86_EMULATE_STGI) || defined(EMU86_EMULATE_CLGI)
				if (modrm.mi_rm == 4) {
#ifdef EMU86_EMULATE_STGI
					EMU86_EMULATE_STGI();
					goto done;
#else /* EMU86_EMULATE_STGI */
#define EMU86_EMULATE_STGICLGI_NEED_UNSUPPORTED
#endif /* !EMU86_EMULATE_STGI */
				} else {
#ifdef EMU86_EMULATE_CLGI
					EMU86_EMULATE_CLGI();
					goto done;
#else /* EMU86_EMULATE_CLGI */
#define EMU86_EMULATE_STGICLGI_NEED_UNSUPPORTED
#endif /* !EMU86_EMULATE_CLGI */
				}
#else /* EMU86_EMULATE_STGI || EMU86_EMULATE_CLGI */
#define EMU86_EMULATE_STGICLGI_NEED_UNSUPPORTED
#endif /* !EMU86_EMULATE_STGI && !EMU86_EMULATE_CLGI */
#elif EMU86_EMULATE_CONFIG_WANT_STGI
#ifdef EMU86_EMULATE_STGI
				EMU86_EMULATE_STGI();
				goto done;
#else /* EMU86_EMULATE_STGI */
#define EMU86_EMULATE_STGICLGI_NEED_UNSUPPORTED
#endif /* !EMU86_EMULATE_STGI */
#else /* ... */
#ifdef EMU86_EMULATE_CLGI
				EMU86_EMULATE_CLGI();
				goto done;
#else /* EMU86_EMULATE_CLGI */
#define EMU86_EMULATE_STGICLGI_NEED_UNSUPPORTED
#endif /* !EMU86_EMULATE_CLGI */
#endif /* !... */
#ifdef EMU86_EMULATE_STGICLGI_NEED_UNSUPPORTED
#undef EMU86_EMULATE_STGICLGI_NEED_UNSUPPORTED
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
#if EMU86_EMULATE_CONFIG_WANT_STGI && EMU86_EMULATE_CONFIG_WANT_CLGI
				EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRINV,
				                                                 X86_REGISTER_MISC_GI, 0,
				                                                 modrm.mi_rm == 4, 0);
#elif EMU86_EMULATE_CONFIG_WANT_STGI
				EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRINV,
				                                                 X86_REGISTER_MISC_GI, 0, 1, 0);
#else /* ... */
				EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRINV,
				                                                 X86_REGISTER_MISC_GI, 0, 0, 0);
#endif /* !... */
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* EMU86_EMULATE_STGICLGI_NEED_UNSUPPORTED */
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || (EMU86_EMULATE_CONFIG_WANT_STGI || EMU86_EMULATE_CONFIG_WANT_CLGI) */


			case 0: /* vmrun */
			case 1: /* vmmcall */
			case 2: /* vmload */
			case 3: /* vmsave */
#ifndef EMU86_EMULATE_HAVE_STGI
			case 4: /* stgi */
#endif /* !EMU86_EMULATE_HAVE_STGI */
#undef EMU86_EMULATE_HAVE_STGI
#ifndef EMU86_EMULATE_HAVE_CLGI
			case 5: /* clgi */
#endif /* !EMU86_EMULATE_HAVE_CLGI */
#undef EMU86_EMULATE_HAVE_CLGI
			case 6: /* skinit */
			case 7: /* invlpga */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (EMU86_ISUSER())
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg

			default: break;
			}
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */


#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LIDT
		{
			byte_t *rmaddr;
			rmaddr = MODRM_MEMADDR();
			IF_64BIT(if (EMU86_F_IS64(op_flags)) {
				EMU86_READ_USER_MEMORY(rmaddr, 10);
				limit = EMU86_MEMREADW(rmaddr + 0);
				base  = EMU86_MEMREADQ(rmaddr + 2);
			} else) {
				EMU86_READ_USER_MEMORY(rmaddr, 6);
				limit = EMU86_MEMREADW(rmaddr + 0);
				base  = EMU86_MEMREADL(rmaddr + 2);
			}
		}
		(void)limit;
		(void)base;
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LIDT */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 IF_64BIT(EMU86_F_IS64(op_flags)
			                                                 ?  X86_REGISTER_MISC_IDT_BASEQ
			                                                 :) X86_REGISTER_MISC_IDT_BASEL,
			                                                 limit, base, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LIDT && defined(EMU86_EMULATE_LIDT)
		EMU86_EMULATE_LIDT(limit, base);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LIDT && EMU86_EMULATE_LIDT */
		EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(),
		                            EMU86_F_IS64(op_flags) ? 10 : 6,
		                            true, false);
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LIDT || !EMU86_EMULATE_LIDT */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LIDT */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SMSW
	case 4: {
		/* 0F 01 /4     SMSW r/m16     Store machine status word to r/m16. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_UMIP_IS_ZERO
		if (EMU86_ISUSER() && EMU86_GETCR4_UMIP()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_CONTROL_CR0, 0, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_UMIP_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_SMSW && defined(EMU86_EMULATE_SMSW)
		{
			u16 msw;
			msw = EMU86_EMULATE_SMSW();
			MODRM_SETRMW(msw);
		}
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SMSW && EMU86_EMULATE_SMSW */
		MODRM_NOSUP_SETRMW();
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_SMSW || !EMU86_EMULATE_SMSW */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_SMSW */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LMSW
	case 6: {
		/* 0F 01 /6     LMSW r/m16     Loads r/m16 in machine status word of CR0. */
#if EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LMSW
		u16 msw;
		msw = MODRM_GETRMW();
#else /* EMU86_EMULATE_CONFIG_CHECKUSER || EMU86_EMULATE_CONFIG_WANT_LMSW */
		MODRM_NOSUP_GETRMW();
#endif /* !EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_EMULATE_CONFIG_WANT_LMSW */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
			                                                 X86_REGISTER_CONTROL_CR0, 0, msw, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LMSW && defined(EMU86_EMULATE_LMSW)
		EMU86_EMULATE_LMSW(msw);
		goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LMSW && EMU86_EMULATE_LMSW */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LMSW || !EMU86_EMULATE_LMSW */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LMSW */


#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_INVLPG ||     \
     (!EMU86_EMULATE_CONFIG_ONLY_MEMORY &&                                      \
      (EMU86_EMULATE_CONFIG_WANT_RDTSCP || EMU86_EMULATE_CONFIG_WANT_MCOMMIT || \
       (EMU86_EMULATE_CONFIG_WANT_SWAPGS && LIBEMU86_CONFIG_WANT_64BIT))))
	case 7: {
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if (EMU86_EMULATE_CONFIG_WANT_RDTSCP || EMU86_EMULATE_CONFIG_WANT_MCOMMIT || \
     EMU86_EMULATE_CONFIG_WANT_CLZERO ||                                      \
     (EMU86_EMULATE_CONFIG_WANT_SWAPGS && LIBEMU86_CONFIG_WANT_64BIT) ||      \
     (EMU86_EMULATE_CONFIG_CHECKERROR &&                                      \
      (EMU86_EMULATE_CONFIG_CHECKUSER || !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC)))
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {
			switch (modrm.mi_rm) {

#undef EMU86_EMULATE_HAVE_RDTSCP
#if EMU86_EMULATE_CONFIG_WANT_RDTSCP || (EMU86_EMULATE_CONFIG_CHECKERROR && EMU86_EMULATE_CONFIG_CHECKUSER)
#define EMU86_EMULATE_HAVE_RDTSCP
			case 1: {
				/* 0F 01 F9     RDTSCP     Read 64-bit time-stamp counter and IA32_TSC_AUX value into EDX:EAX and ECX. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_TSD_IS_ZERO
				if (EMU86_GETCR4_TSD() && EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
					                                                       X86_REGISTER_MSR,
					                                                       IA32_TIME_STAMP_COUNTER, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG */
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG */
				}
#endif /* !EMU86_GETCR4_TSD_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
				/* Allow the privisioning of `EMU86_EMULATE_RDTSCP()'
				 * in order to prevent a race condition when the hosting CPU changes
				 * between   reading   its   performance   counter,   and   its  ID. */
#ifdef EMU86_EMULATE_RDTSCP
				{
					u64 tsc;
					u32 tsc_aux;
					tsc = EMU86_EMULATE_RDTSCP(tsc_aux);
					EMU86_SETEAX((u32)(tsc));
					EMU86_SETEDX((u32)(tsc >> 32));
					EMU86_SETECX(tsc_aux);
				}
				goto done;
#else /* EMU86_EMULATE_RDTSCP */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_RDTSCP */
			}
#endif /* EMU86_EMULATE_CONFIG_WANT_RDTSCP || (EMU86_EMULATE_CONFIG_CHECKERROR && EMU86_EMULATE_CONFIG_CHECKUSER) */



#undef EMU86_EMULATE_HAVE_SWAPGS
#if (LIBEMU86_CONFIG_WANT_64BIT &&        \
     (EMU86_EMULATE_CONFIG_WANT_SWAPGS || \
      (EMU86_EMULATE_CONFIG_CHECKERROR && EMU86_EMULATE_CONFIG_CHECKUSER)))
#define EMU86_EMULATE_HAVE_SWAPGS
			case 0: {
				/* 0F 01 F8     SWAPGS     Exchanges the current GS base register value with the value contained in MSR address C0000102H. */
#if LIBEMU86_CONFIG_WANT_64BIT
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
				if (!EMU86_F_IS64(op_flags)) {
					goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
				}
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG
					EMU86_UREG_TYPE gsbase = (EMU86_UREG_TYPE)(uintptr_t)EMU86_GETGSBASE();
#if LIBEMU86_CONFIG_WANT_64BIT
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
					                                                       X86_REGISTER_MSR,
					                                                       IA32_KERNEL_GS_BASE,
					                                                       (u32)(gsbase),
					                                                       (u32)(gsbase >> 32));
#else /* LIBEMU86_CONFIG_WANT_64BIT */
					EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
					                                                       X86_REGISTER_MSR,
					                                                       IA32_KERNEL_GS_BASE,
					                                                       (u32)(gsbase),
					                                                       0);
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG */
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG */
				}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_SWAPGS && defined(EMU86_EMULATE_SWAPGS)
				EMU86_EMULATE_SWAPGS();
				goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_SWAPGS && EMU86_EMULATE_SWAPGS */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_SWAPGS || !EMU86_EMULATE_SWAPGS */
#else /* LIBEMU86_CONFIG_WANT_64BIT */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
			}
#endif /* (LIBEMU86_CONFIG_WANT_64BIT && (EMU86_EMULATE_CONFIG_WANT_SWAPGS || (EMU86_EMULATE_CONFIG_CHECKERROR && EMU86_EMULATE_CONFIG_CHECKUSER))) */

			case 2:
#if EMU86_EMULATE_CONFIG_WANT_MCOMMIT
				if (op_flags & EMU86_F_f3) {
					/* mcommit */
#ifdef EMU86_EMULATE_MCOMMIT
					EMU86_EMULATE_MCOMMIT();
					goto done;
#else /* EMU86_EMULATE_MCOMMIT */
					goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_MCOMMIT */
				}
#endif /* EMU86_EMULATE_CONFIG_WANT_MCOMMIT */
				/* monitorx */
				ATTR_FALLTHROUGH
#ifndef EMU86_EMULATE_HAVE_SWAPGS
			case 0: /* 0F 01 F8     SWAPGS     Exchanges the current GS base register value with the value contained in MSR address C0000102H. */
#endif /* !EMU86_EMULATE_HAVE_SWAPGS */
#undef EMU86_EMULATE_HAVE_SWAPGS
#ifndef EMU86_EMULATE_HAVE_RDTSCP
			case 1: /* 0F 01 F9     RDTSCP     Read 64-bit time-stamp counter and IA32_TSC_AUX value into EDX:EAX and ECX. */
#endif /* !EMU86_EMULATE_HAVE_RDTSCP */
#undef EMU86_EMULATE_HAVE_RDTSCP
			case 3: /* mwaitx */
			case 5: /* rdpru */
#if EMU86_EMULATE_CONFIG_CHECKUSER
				if (EMU86_ISUSER())
					goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg

#if EMU86_EMULATE_CONFIG_WANT_CLZERO
			case 4: /* clzero */
#ifdef EMU86_EMULATE_CLZERO
				{
					void *addr;
					IF_64BIT(if (EMU86_F_IS64(op_flags)) {
						addr = (void *)(uintptr_t)EMU86_GETRAX();
					} else) {
						addr = (void *)(uintptr_t)EMU86_GETEAX();
					}
					EMU86_EMULATE_CLZERO(addr);
				}
#endif /* EMU86_EMULATE_CLZERO */
				goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_CLZERO */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_CLZERO */

			default: break;
			}
		}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_... */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */


		/* 0F 01 /7     INVLPG m      Invalidate TLB entries for page containing m. */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if EMU86_EMULATE_CONFIG_CHECKUSER
		if (EMU86_ISUSER())
			goto return_privileged_instruction_rmreg;
#define NEED_return_privileged_instruction_rmreg
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_LMSW && defined(EMU86_EMULATE_INVLPG)
		{
			byte_t *addr;
			addr = MODRM_MEMADDR();
			EMU86_EMULATE_INVLPG(addr);
		}
#else /* EMU86_EMULATE_CONFIG_WANT_LMSW && EMU86_EMULATE_INVLPG */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_LMSW || !EMU86_EMULATE_INVLPG */
		goto done;
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_INVLPG */


	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	break;
}
#endif /* EMU86_EMULATE_... */



#if (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_64BIT || \
     (EMU86_EMULATE_CONFIG_CHECKERROR && LIBEMU86_CONFIG_WANT_16BIT))
#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LAR
case EMU86_OPCODE_ENCODE(0x0f02): {
	/* 0F 02 /r     LAR r16, r16/m16     r16 := access rights referenced by r16/m16 */
#if LIBEMU86_CONFIG_WANT_16BIT
	if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* LIBEMU86_CONFIG_WANT_16BIT */
	MODRM_DECODE();
#if EMU86_EMULATE_CONFIG_WANT_LAR && defined(EMU86_EMULATE_LAR)
	{
		bool ok;
		u16 segment_index;
		u16 segment_rights;
		segment_index = MODRM_GETRMW();
		ok = EMU86_EMULATE_LAR(segment_index,
		                       segment_rights);
		EMU86_MSKFLAGS(~EFLAGS_ZF, ok ? EFLAGS_ZF : 0);
		if (ok)
			MODRM_SETRMREGW(segment_rights);
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LAR && EMU86_EMULATE_LAR */
	MODRM_NOSUP_GETRMW();
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_LAR || !EMU86_EMULATE_LAR */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LAR */


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LSL
case EMU86_OPCODE_ENCODE(0x0f03): {
	/*         0F 03 /r     LSL r16, r16/m16     Load: r16 := segment limit, selector r16/m16.
	 *         0F 03 /r     LSL r32, r32/m16     Load: r32 := segment limit, selector r32/m16.
	 * REX.W + 0F 03 /r     LSL r64, r32/m16     Load: r64 := segment limit, selector r32/m16 */
#if LIBEMU86_CONFIG_WANT_16BIT
	if (EMU86_F_IS16(op_flags)) /* This also includes vm86! */
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* LIBEMU86_CONFIG_WANT_16BIT */
	MODRM_DECODE();
#if EMU86_EMULATE_CONFIG_WANT_LSL && defined(EMU86_EMULATE_LSL)
	{
		bool ok;
		u16 segment_index;
		EMU86_UREG_TYPE limit;
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
#else /* EMU86_EMULATE_CONFIG_WANT_LSL && EMU86_EMULATE_LSL */
	MODRM_NOSUP_GETRMW();
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_LSL || !EMU86_EMULATE_LSL */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LSL */
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_64BIT || (EMU86_EMULATE_CONFIG_CHECKERROR && LIBEMU86_CONFIG_WANT_16BIT) */


}
EMU86_INTELLISENSE_END
