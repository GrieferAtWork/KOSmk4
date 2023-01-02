/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

/* Disable WRMSR user-emulation if there is nothing to emulate. */
#if (EMU86_EMULATE_CONFIG_WANT_WRMSR_EMULATED && \
     (!defined(EMU86_SETFSBASE) && !defined(EMU86_SETGSBASE)))
#undef EMU86_EMULATE_CONFIG_WANT_WRMSR_EMULATED
#define EMU86_EMULATE_CONFIG_WANT_WRMSR_EMULATED 1
#endif /* EMU86_EMULATE_CONFIG_WANT_WRMSR_EMULATED && !... */

EMU86_INTELLISENSE_BEGIN(msr) {

#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDMSR || \
     EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED)
case EMU86_OPCODE_ENCODE(0x0f32): {
	/* 0F 32     RDMSR     Read MSR specified by ECX into EDX:EAX. */


	/* Emulate rdmsr for certain registers */
#if EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED
	u32 index = EMU86_GETECX();
	u64 value;

	/* ==== IA32_TIME_STAMP_COUNTER ==== */
#if defined(EMU86_EMULATE_RDTSC_INDIRECT) && !defined(EMU86_GETCR4_TSD_IS_ONE)
	if (index == IA32_TIME_STAMP_COUNTER) {
#if EMU86_EMULATE_CONFIG_CHECKUSER && !defined(EMU86_GETCR4_TSD_IS_ZERO)
		if (!EMU86_GETCR4_TSD() || !EMU86_ISUSER())
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_GETCR4_TSD_IS_ZERO */
		{
			value = EMU86_EMULATE_RDTSC_INDIRECT();
			goto rdmsr_do_set_value;
#define NEED_rdmsr_do_set_value
		}
	}
#endif /* EMU86_EMULATE_RDTSC_INDIRECT && !EMU86_GETCR4_TSD_IS_ONE */

	/* ==== IA32_TSC_AUX ==== */
#if defined(EMU86_EMULATE_RDPID) && !defined(EMU86_GETCR4_TSD_IS_ONE)
	if (index == IA32_TSC_AUX) {
#if EMU86_EMULATE_CONFIG_CHECKUSER && !defined(EMU86_GETCR4_TSD_IS_ZERO)
		if (!EMU86_GETCR4_TSD() && EMU86_ISUSER())
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
		{
			value = (u64)(u32)EMU86_EMULATE_RDPID();
			goto rdmsr_do_set_value;
#define NEED_rdmsr_do_set_value
		}
	}
#endif /* EMU86_EMULATE_RDPID && !EMU86_GETCR4_TSD_IS_ONE */

#if EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED_FSGSBASE
	/* ==== IA32_FS_BASE ==== */
	if (index == IA32_FS_BASE) {
		value = (u64)(uintptr_t)EMU86_GETFSBASE();
		goto rdmsr_do_set_value;
#define NEED_rdmsr_do_set_value
	}
#endif /* EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED_FSGSBASE */

	/* ==== IA32_GS_BASE ==== */
#if EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED_FSGSBASE
	if (index == IA32_GS_BASE) {
		value = (u64)(uintptr_t)EMU86_GETGSBASE();
#undef NEED_rdmsr_do_set_value
rdmsr_do_set_value:
		EMU86_SETEAX((u32)(value));
		EMU86_SETEDX((u32)(value >> 32));
		goto done;
	}
#elif defined(NEED_rdmsr_do_set_value)
#undef NEED_rdmsr_do_set_value
	__IF0 {
rdmsr_do_set_value:
		EMU86_SETEAX((u32)(value));
		EMU86_SETEDX((u32)(value >> 32));
		goto done;
	}
#endif /* ... */
#endif /* EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED */

	/* Emulate the instruction */
#if EMU86_EMULATE_CONFIG_WANT_RDMSR && defined(EMU86_EMULATE_RDMSR)
#if EMU86_EMULATE_CONFIG_CHECKUSER
	if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
#if EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
		                                                 X86_REGISTER_MSR, index, 0, 0);
#else /* EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED */
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
		                                                 X86_REGISTER_MSR, EMU86_GETECX(), 0, 0);
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED */
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
	{
#if !EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED
		u64 value;
		u32 index = EMU86_GETECX();
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED */
		value = EMU86_EMULATE_RDMSR(index);
#if EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED
		goto rdmsr_do_set_value;
#else /* EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED */
		EMU86_SETEAX((u32)(value));
		EMU86_SETEDX((u32)(value >> 32));
		goto done;
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED */
	}
#else /* EMU86_EMULATE_CONFIG_WANT_RDMSR && EMU86_EMULATE_RDMSR */
	/* Bad MSR register index. */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
#if EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED
	EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(EMU86_ISUSER() ? E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV
	                                                                : E_ILLEGAL_INSTRUCTION_REGISTER_RDINV,
	                                                 X86_REGISTER_MSR, index, 0, 0);
#else /* EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED */
	EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(EMU86_ISUSER() ? E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV
	                                                                : E_ILLEGAL_INSTRUCTION_REGISTER_RDINV,
	                                                 X86_REGISTER_MSR, EMU86_GETECX(), 0, 0);
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED */
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDMSR || !EMU86_EMULATE_RDMSR */
}
#endif /* EMU86_EMULATE_CONFIG_(CHECKERROR|WANT_RDMSR|WANT_RDMSR_USEREMU) */




#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_WRMSR || \
     EMU86_EMULATE_CONFIG_WANT_WRMSR_EMULATED)
case EMU86_OPCODE_ENCODE(0x0f30): {
	u32 index;
	u64 value;
	/* 0F 30     WRMSR     Write the value in EDX:EAX to MSR specified by ECX. */
	index = EMU86_GETECX();
	value = (u64)EMU86_GETEAX() | ((u64)EMU86_GETEDX() << 32);
	(void)index;
	(void)value;

	/* A  couple  of MSR  registers can  throw #GP  if the  written value
	 * is a  non-canonical pointer.  Since  KOS throws  `E_SEGFAULT'  for
	 * this case, manually check if we're dealing with one of these MSRs,
	 * and the written value is such a pointer.
	 * s.a. Intel instruction set reference for `WRMSR' (Vol. 2C) */
#if LIBEMU86_CONFIG_WANT_64BIT && !defined(EMU86_VALIDATE_CANONICAL_IS_NOOP)
	if (EMU86_F_IS64(op_flags)) {
		if (index == IA32_DS_AREA || index == IA32_FS_BASE ||
		    index == IA32_GS_BASE || index == IA32_KERNEL_GS_BASE ||
		    index == IA32_LSTAR || index == IA32_SYSENTER_EIP ||
		    index == IA32_SYSENTER_ESP)
			EMU86_VALIDATE_CANONICAL(value);
	}
#endif /* LIBEMU86_CONFIG_WANT_64BIT && !EMU86_VALIDATE_CANONICAL_IS_NOOP */

	/* Emulate wrmsr for certain registers */
#if EMU86_EMULATE_CONFIG_WANT_WRMSR_EMULATED
	/* ==== IA32_FS_BASE ==== */
#ifdef EMU86_SETFSBASE
	if (index == IA32_FS_BASE) {
		EMU86_SETFSBASE((uintptr_t)value);
		goto done;
	}
#endif /* EMU86_SETFSBASE */

	/* ==== IA32_GS_BASE ==== */
#ifdef EMU86_SETGSBASE
	if (index == IA32_GS_BASE) {
		EMU86_SETGSBASE((uintptr_t)value);
		goto done;
	}
#endif /* EMU86_SETGSBASE */
#endif /* EMU86_EMULATE_CONFIG_WANT_WRMSR_EMULATED */

	/* Emulate the instruction */
#if EMU86_EMULATE_CONFIG_WANT_WRMSR && defined(EMU86_EMULATE_WRMSR)
#if EMU86_EMULATE_CONFIG_CHECKUSER
	if (EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
		                                                 X86_REGISTER_MSR, index,
		                                                 (u32)value, (u32)(value >> 32));
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
	EMU86_EMULATE_WRMSR(index, value);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_WRMSR && EMU86_EMULATE_WRMSR */
	/* Bad MSR register index, or access from user-space. */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
	EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(EMU86_ISUSER() ? E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
	                                                                : E_ILLEGAL_INSTRUCTION_REGISTER_WRINV,
	                                                 X86_REGISTER_MSR, index,
	                                                 (u32)value, (u32)(value >> 32));
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* !EMU86_EMULATE_CONFIG_WANT_WRMSR || !EMU86_EMULATE_WRMSR */
}
#endif /* EMU86_EMULATE_CONFIG_(CHECKERROR|WANT_WRMSR|WANT_WRMSR_USEREMU) */



#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDTSC
case EMU86_OPCODE_ENCODE(0x0f31): {
	/* 0F 31     RDTSC     Read time-stamp counter into EDX:EAX. */
#if EMU86_EMULATE_CONFIG_CHECKUSER
#ifndef EMU86_GETCR4_TSD_IS_ZERO
	if (EMU86_GETCR4_TSD() && EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
		                                                 X86_REGISTER_MSR,
		                                                 IA32_TIME_STAMP_COUNTER, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#endif /* !EMU86_GETCR4_TSD_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
#if EMU86_EMULATE_CONFIG_WANT_RDTSC && defined(EMU86_EMULATE_RDTSC)
	{
		u64 value = EMU86_EMULATE_RDTSC();
		EMU86_SETEAX((u32)(value));
		EMU86_SETEDX((u32)(value >> 32));
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_RDTSC && EMU86_EMULATE_RDTSC */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
	EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG(E_ILLEGAL_INSTRUCTION_REGISTER_RDINV,
	                                                       X86_REGISTER_MSR,
	                                                       IA32_TIME_STAMP_COUNTER, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDTSC || !EMU86_EMULATE_RDTSC */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDTSC */




#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDPMC
case EMU86_OPCODE_ENCODE(0x0f33): {
	/* 0F 33     RDPMC     Read performance-monitoring counter specified by ECX into EDX:EAX. */
#if EMU86_EMULATE_CONFIG_CHECKUSER && !defined(EMU86_GETCR4_PCE_IS_ONE)
	if (!EMU86_GETCR4_PCE() && EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
		                                                 X86_REGISTER_PCR, EMU86_GETECX(), 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER && !EMU86_GETCR4_PCE_IS_ONE */

	/* Emulate the instruction */
#if EMU86_EMULATE_CONFIG_WANT_RDPMC && defined(EMU86_EMULATE_RDPMC)
	{
		u64 value;
		u32 index = EMU86_GETECX();
		value = EMU86_EMULATE_RDPMC(index);
		EMU86_SETEAX((u32)(value));
		EMU86_SETEDX((u32)(value >> 32));
	}
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_RDPMC && EMU86_EMULATE_RDPMC */
	/* Bad PCR register index. */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
	EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDINV,
	                                                 X86_REGISTER_PCR, EMU86_GETECX(), 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
	goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDPMC || !EMU86_EMULATE_RDPMC */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDPMC */





}
EMU86_INTELLISENSE_END

#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
