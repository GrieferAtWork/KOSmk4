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
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(cmpxchgb) {

case EMU86_OPCODE_ENCODE(0x0fc7):
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 1: {
		/*         0F C7 /1 CMPXCHG8B m64      Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX
		 *                                     into m64. Else, clear ZF and load m64 into EDX:EAX.
		 * REX.W + 0F C7 /1 CMPXCHG16B m128    Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX
		 *                                     into m128. Else, clear ZF and load m128 into RDX:RAX. */
#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#define NEED_return_expected_memory_modrm
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm;
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */
#if CONFIG_LIBEMU86_WANT_64BIT
		if (IS_64BIT()) {
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B && defined(EMU86_MEM_ATOMIC_CMPXCH128)
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
			real_oldval.word128 = EMU86_MEM_ATOMIC_CMPXCH128(addr, want_oldval.word128, newval.word128,
			                                                 (op_flags & EMU86_F_LOCK) != 0);
			if (real_oldval.qwords[0] == want_oldval.qwords[0] &&
			    real_oldval.qwords[1] == want_oldval.qwords[1]) {
				EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
			} else {
				EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
				EMU86_SETRAX(real_oldval.qwords[0]);
				EMU86_SETRDX(real_oldval.qwords[1]);
			}
			goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B && EMU86_MEM_ATOMIC_CMPXCH128 */
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B
			if (!(op_flags & EMU86_F_LOCK)) {
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
			EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(), 16, true, true);
#define NEED_return_unsupported_instruction_rmreg
			goto return_unsupported_instruction_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B || !EMU86_MEM_ATOMIC_CMPXCH128 */
		} else
#endif /* CONFIG_LIBEMU86_WANT_64BIT */
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
			                                             (op_flags & EMU86_F_LOCK) != 0);
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
			if (!(op_flags & EMU86_F_LOCK)) {
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
#if CONFIG_LIBEMU86_WANT_64BIT
				real_oldval.qword = EMU86_MEMREADQ(addr);
#else /* CONFIG_LIBEMU86_WANT_64BIT */
				real_oldval.dwords[0] = EMU86_MEMREADL(addr + 0);
				real_oldval.dwords[1] = EMU86_MEMREADL(addr + 4);
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
#if __SIZEOF_POINTER__ >= 8
				if (real_oldval.qword == want_oldval.qword)
#else /* __SIZEOF_POINTER__ >= 8 */
				if (real_oldval.dwords[0] == want_oldval.dwords[0] &&
				    real_oldval.dwords[1] == want_oldval.dwords[1])
#endif /* __SIZEOF_POINTER__ < 8 */
				{
#if CONFIG_LIBEMU86_WANT_64BIT
					EMU86_MEMWRITEQ(addr, newval.qword);
#else /* CONFIG_LIBEMU86_WANT_64BIT */
					EMU86_MEMWRITEL(addr + 0, newval.dwords[0]);
					EMU86_MEMWRITEL(addr + 4, newval.dwords[1]);
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
					EMU86_MSKFLAGS(~EFLAGS_ZF, EFLAGS_ZF);
				} else {
					EMU86_MSKFLAGS(~EFLAGS_ZF, 0);
					EMU86_SETEAX(real_oldval.dwords[0]);
					EMU86_SETEDX(real_oldval.dwords[1]);
				}
				goto done;
			}
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B */
			EMU86_UNSUPPORTED_MEMACCESS(MODRM_MEMADDR(), 8, true, true);
#define NEED_return_unsupported_instruction_rmreg
			goto return_unsupported_instruction_rmreg;
#endif /* !EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B || !EMU86_MEM_ATOMIC_CMPXCHQ */
		}
		break;
	}

	default:
#define NEED_return_unknown_instruction_rmreg
		goto return_unknown_instruction_rmreg;
	}
	break;


}
EMU86_INTELLISENSE_END
