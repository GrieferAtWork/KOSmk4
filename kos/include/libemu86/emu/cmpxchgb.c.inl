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

EMU86_INTELLISENSE_BEGIN(cmpxchgb) {

case EMU86_OPCODE_ENCODE(0x0fc7):
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 1: {
		/*         0F C7 /1 CMPXCHG8B m64      Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX
		 *                                     into  m64.  Else,  clear  ZF  and  load  m64  into EDX:EAX.
		 * REX.W + 0F C7 /1 CMPXCHG16B m128    Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX
		 *                                     into m128.  Else,  clear  ZF and  load  m128  into  RDX:RAX. */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm;
#define NEED_return_expected_memory_modrm
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if LIBEMU86_CONFIG_WANT_64BIT
		if (IS_64BIT()) {
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B && defined(EMU86_MEM_ATOMIC_CMPXCHX)
			union {
				uint128_t word128;
				u64 qwords[2];
			} real_oldval, want_oldval, newval;
			byte_t *addr;
			want_oldval.qwords[0] = EMU86_GETRAX();
			want_oldval.qwords[1] = EMU86_GETRDX();
			newval.qwords[0]      = EMU86_GETRBX();
			newval.qwords[1]      = EMU86_GETRCX();
			addr                  = MODRM_MEMADDR();
			EMU86_READWRITE_USER_MEMORY(addr, 16);
			real_oldval.word128 = EMU86_MEM_ATOMIC_CMPXCHX(addr,
			                                               want_oldval.word128,
			                                               newval.word128,
			                                               EMU86_HASLOCK());
			if (real_oldval.qwords[0] == want_oldval.qwords[0] &&
			    real_oldval.qwords[1] == want_oldval.qwords[1]) {
				EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
			} else {
				EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
				EMU86_SETRAX(real_oldval.qwords[0]);
				EMU86_SETRDX(real_oldval.qwords[1]);
			}
			goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B && EMU86_MEM_ATOMIC_CMPXCHX */
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B
#if !EMU86_EMULATE_CONFIG_IGNORE_LOCK
			if (!EMU86_HASLOCK())
#endif /* !EMU86_EMULATE_CONFIG_IGNORE_LOCK */
			{
				/* We can easily emulate the non-atomic variant! */
				union {
					u64 qwords[2];
				} real_oldval, want_oldval, newval;
				byte_t *addr;
				want_oldval.qwords[0] = EMU86_GETRAX();
				want_oldval.qwords[1] = EMU86_GETRDX();
				newval.qwords[0]      = EMU86_GETRBX();
				newval.qwords[1]      = EMU86_GETRCX();
				addr                  = MODRM_MEMADDR();
				EMU86_READWRITE_USER_MEMORY(addr, 16);
				COMPILER_READ_BARRIER();
				real_oldval.qwords[0] = EMU86_MEMREADQ(addr + 0);
				real_oldval.qwords[1] = EMU86_MEMREADQ(addr + 8);
				COMPILER_READ_BARRIER();
				if (real_oldval.qwords[0] == want_oldval.qwords[0] &&
				    real_oldval.qwords[1] == want_oldval.qwords[1]) {
					COMPILER_WRITE_BARRIER();
					EMU86_MEMWRITEQ(addr + 0, newval.qwords[0]);
					EMU86_MEMWRITEQ(addr + 8, newval.qwords[1]);
					COMPILER_WRITE_BARRIER();
					EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
				} else {
					EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
					EMU86_SETRAX(real_oldval.qwords[0]);
					EMU86_SETRDX(real_oldval.qwords[1]);
				}
				goto done;
			}
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B */
#if !EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B || !EMU86_EMULATE_CONFIG_IGNORE_LOCK
			EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(), 16, true, true);
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B || !EMU86_EMULATE_CONFIG_IGNORE_LOCK */
#endif /* !EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B || !EMU86_MEM_ATOMIC_CMPXCHX */
		} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
		{
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B && defined(EMU86_MEM_ATOMIC_CMPXCHQ)
			union {
				u64 qword;
				u32 dwords[2];
			} real_oldval, want_oldval, newval;
			byte_t *addr;
			want_oldval.dwords[0] = EMU86_GETEAX();
			want_oldval.dwords[1] = EMU86_GETEDX();
			newval.dwords[0]      = EMU86_GETEBX();
			newval.dwords[1]      = EMU86_GETECX();
			addr                  = MODRM_MEMADDR();
			EMU86_READWRITE_USER_MEMORY(addr, 8);
			real_oldval.qword = EMU86_MEM_ATOMIC_CMPXCHQ(addr, want_oldval.qword, newval.qword,
			                                             EMU86_HASLOCK());
#if __SIZEOF_POINTER__ >= 8
			if (real_oldval.qword == want_oldval.qword)
#else /* __SIZEOF_POINTER__ >= 8 */
			if (real_oldval.dwords[0] == want_oldval.dwords[0] &&
			    real_oldval.dwords[1] == want_oldval.dwords[1])
#endif /* __SIZEOF_POINTER__ < 8 */
			{
				EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
			} else {
				EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
				EMU86_SETEAX(real_oldval.dwords[0]);
				EMU86_SETEDX(real_oldval.dwords[1]);
			}
			goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B && EMU86_MEM_ATOMIC_CMPXCHQ */
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B
#if !EMU86_EMULATE_CONFIG_IGNORE_LOCK
			if (!EMU86_HASLOCK())
#endif /* !EMU86_EMULATE_CONFIG_IGNORE_LOCK */
			{
				/* We can easily emulate the non-atomic variant! */
				union {
					u64 qword;
					u32 dwords[2];
				} real_oldval, want_oldval, newval;
				byte_t *addr;
				want_oldval.dwords[0] = EMU86_GETEAX();
				want_oldval.dwords[1] = EMU86_GETEDX();
				newval.dwords[0]      = EMU86_GETEBX();
				newval.dwords[1]      = EMU86_GETECX();
				addr                  = MODRM_MEMADDR();
				EMU86_READWRITE_USER_MEMORY(addr, 8);
#if LIBEMU86_CONFIG_WANT_64BIT
				real_oldval.qword = EMU86_MEMREADQ(addr);
#else /* LIBEMU86_CONFIG_WANT_64BIT */
				real_oldval.dwords[0] = EMU86_MEMREADL(addr + 0);
				real_oldval.dwords[1] = EMU86_MEMREADL(addr + 4);
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
#if __SIZEOF_POINTER__ >= 8
				if (real_oldval.qword == want_oldval.qword)
#else /* __SIZEOF_POINTER__ >= 8 */
				if (real_oldval.dwords[0] == want_oldval.dwords[0] &&
				    real_oldval.dwords[1] == want_oldval.dwords[1])
#endif /* __SIZEOF_POINTER__ < 8 */
				{
#if LIBEMU86_CONFIG_WANT_64BIT
					EMU86_MEMWRITEQ(addr, newval.qword);
#else /* LIBEMU86_CONFIG_WANT_64BIT */
					EMU86_MEMWRITEL(addr + 0, newval.dwords[0]);
					EMU86_MEMWRITEL(addr + 4, newval.dwords[1]);
#endif /* !LIBEMU86_CONFIG_WANT_64BIT */
					EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
				} else {
					EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
					EMU86_SETEAX(real_oldval.dwords[0]);
					EMU86_SETEDX(real_oldval.dwords[1]);
				}
				goto done;
			}
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B */
#if !EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B || !EMU86_EMULATE_CONFIG_IGNORE_LOCK
			EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(), 8, true, true);
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B || !EMU86_EMULATE_CONFIG_IGNORE_LOCK */
#endif /* !EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B || !EMU86_MEM_ATOMIC_CMPXCHQ */
		}
		break;
	}


#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY

#if defined(EMU86_EMULATE_RDRAND64) && !defined(EMU86_EMULATE_RDRAND32)
#endif

#if ((EMU86_EMULATE_CONFIG_CHECKERROR &&                 \
      !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || \
     EMU86_EMULATE_CONFIG_WANT_RDRAND)
	case 6: {
		if (op_flags & (EMU86_F_f2 | EMU86_F_f3))
			goto return_unexpected_prefix_rmreg;
#define NEED_return_unexpected_prefix_rmreg
		if (!EMU86_MODRM_ISREG(modrm.mi_type))
			goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
		/* NFx         0F C7 /6 RDRAND r16     Read a 16-bit random number and store in the destination register.
		 * NFx         0F C7 /6 RDRAND r32     Read a 32-bit random number and store in the destination register.
		 * NFx REX.W + 0F C7 /6 RDRAND r64     Read a 64-bit random number and store in the destination register. */
#if (EMU86_EMULATE_CONFIG_WANT_RDRAND &&                                    \
     (defined(EMU86_EMULATE_RDRAND16) || defined(EMU86_EMULATE_RDRAND32) || \
      defined(EMU86_EMULATE_RDRAND64)))
		{
			bool ok;
#if LIBEMU86_CONFIG_WANT_64BIT
			if (IS_64BIT()) {
#ifdef EMU86_EMULATE_RDRAND64
				u64 value;
				ok = EMU86_EMULATE_RDRAND64(value);
				if (!ok)
					value = 0;
				MODRM_SETRMREGQ(value);
#else /* EMU86_EMULATE_RDRAND64 */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_RDRAND64 */
			} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
			{
				if (!IS_16BIT()) {
#ifdef EMU86_EMULATE_RDRAND32
					u32 value;
					ok = EMU86_EMULATE_RDRAND32(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGL(value);
#elif defined(EMU86_EMULATE_RDRAND64)
					u64 value;
					ok = EMU86_EMULATE_RDRAND64(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGL((u32)value);
#else /* ... */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !... */
				} else {
#ifdef EMU86_EMULATE_RDRAND16
					u16 value;
					ok = EMU86_EMULATE_RDRAND16(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGW(value);
#elif defined(EMU86_EMULATE_RDRAND32)
					u32 value;
					ok = EMU86_EMULATE_RDRAND32(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGW((u16)value);
#else /* ... */
					u64 value;
					ok = EMU86_EMULATE_RDRAND64(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGW((u16)value);
#endif /* !... */
				}
			}
			EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_AF | EFLAGS_PF | EFLAGS_CF),
			               ok ? EFLAGS_CF : 0);
			goto done;
		}
#else /* EMU86_EMULATE_CONFIG_WANT_RDRAND && EMU86_EMULATE_RDRANDnn */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDRAND || !EMU86_EMULATE_RDRANDnn */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDRAND */



#if (EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDPID || EMU86_EMULATE_CONFIG_WANT_RDSEED)
	case 7: {
		if (!EMU86_MODRM_ISREG(modrm.mi_type))
			goto return_expected_register_modrm;
#define NEED_return_expected_register_modrm
		if (!(op_flags & EMU86_F_f3)) {
			/* NFx         0F C7 /7 RDSEED r16     Read a 16-bit NIST SP800-90B & C compliant random value and store in the destination register.
			 * NFx         0F C7 /7 RDSEED r32     Read a 32-bit NIST SP800-90B & C compliant random value and store in the destination register.
			 * NFx REX.W + 0F C7 /7 RDSEED r64     Read a 64-bit NIST SP800-90B & C compliant random value and store in the destination register. */
#if (EMU86_EMULATE_CONFIG_WANT_RDSEED &&                                    \
     (defined(EMU86_EMULATE_RDSEED16) || defined(EMU86_EMULATE_RDSEED32) || \
      defined(EMU86_EMULATE_RDSEED64)))
			bool ok;
#if LIBEMU86_CONFIG_WANT_64BIT
			if (IS_64BIT()) {
#ifdef EMU86_EMULATE_RDSEED64
				u64 value;
				ok = EMU86_EMULATE_RDSEED64(value);
				if (!ok)
					value = 0;
				MODRM_SETRMREGQ(value);
#else /* EMU86_EMULATE_RDSEED64 */
				goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_RDSEED64 */
			} else
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
			{
				if (!IS_16BIT()) {
#ifdef EMU86_EMULATE_RDSEED32
					u32 value;
					ok = EMU86_EMULATE_RDSEED32(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGL(value);
#elif defined(EMU86_EMULATE_RDSEED64)
					u64 value;
					ok = EMU86_EMULATE_RDSEED64(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGL((u32)value);
#else /* ... */
					goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !... */
				} else {
#ifdef EMU86_EMULATE_RDSEED16
					u16 value;
					ok = EMU86_EMULATE_RDSEED16(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGW(value);
#elif defined(EMU86_EMULATE_RDSEED32)
					u32 value;
					ok = EMU86_EMULATE_RDSEED32(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGW((u16)value);
#else /* ... */
					u64 value;
					ok = EMU86_EMULATE_RDSEED64(value);
					if (!ok)
						value = 0;
					MODRM_SETRMREGW((u16)value);
#endif /* !... */
				}
			}
			EMU86_MSKFLAGS(~(EFLAGS_OF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_AF | EFLAGS_PF | EFLAGS_CF),
			               ok ? EFLAGS_CF : 0);
			goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_RDSEED && EMU86_EMULATE_RDSEEDnn */
			goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDSEED || !EMU86_EMULATE_RDSEEDnn */
		}

#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDPID
		/* F3 0F C7 /7 RDPID r32     R     Read IA32_TSC_AUX into r32.
		 * F3 0F C7 /7 RDPID r64     R     Read IA32_TSC_AUX into r64. */
#if EMU86_EMULATE_CONFIG_CHECKUSER && 0 /* Intel doesn't document this instruction as checking for permissions... */
#ifndef EMU86_GETCR4_TSD_IS_ZERO
		if (EMU86_GETCR4_TSD() && EMU86_ISUSER()) {
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
			EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV,
			                                                 X86_REGISTER_MSR,
			                                                 IA32_TSC_AUX, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
			goto return_privileged_instruction;
#define NEED_return_privileged_instruction
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		}
#endif /* !EMU86_GETCR4_TSD_IS_ZERO */
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */

#if EMU86_EMULATE_CONFIG_WANT_RDPID && defined(EMU86_EMULATE_RDPID)
		{
			u32 value = EMU86_EMULATE_RDPID();
			MODRM_SETRMREGL(value);
		}
#else /* EMU86_EMULATE_CONFIG_WANT_RDPID && EMU86_EMULATE_RDPID */
#ifdef EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER
		EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG(E_ILLEGAL_INSTRUCTION_REGISTER_RDINV,
		                                                       X86_REGISTER_MSR,
		                                                       IA32_TSC_AUX, 0, 0);
#else /* EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER */
#endif /* !EMU86_EMULATE_CONFIG_WANT_RDPID || !EMU86_EMULATE_RDPID */
#else /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDPID */
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* !EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_WANT_RDPID */
	}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_RDPID || EMU86_EMULATE_CONFIG_WANT_RDSEED */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	break;


}
EMU86_INTELLISENSE_END
