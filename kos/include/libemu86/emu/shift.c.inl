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

EMU86_INTELLISENSE_BEGIN(shift) {


#if EMU86_EMULATE_CONFIG_WANT_SHIFT
	/* The number of bits by which to shift */
	u8 num_bits;

#if EMU86_EMULATE_CONFIG_LOCK_SHIFT /* Extension!!! */
#define EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT(tt, ff) tt
#else /* EMU86_EMULATE_CONFIG_LOCK_SHIFT */
#define EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT(tt, ff) ff
#endif /* !EMU86_EMULATE_CONFIG_LOCK_SHIFT */

#define DEFINE_SHIFT_OPERATIONS_MODRM_reg(bwlq, BWLQ, Nbits, Nbytes, msb_bit_set)   \
	do {                                                                            \
		u32 eflags_addend = 0;                                                      \
		u##Nbits oldval, newval;                                                    \
		num_bits &= (Nbits - 1);                                                    \
		if (!num_bits)                                                              \
			goto done; /* no-op */                                                  \
EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT(do_shift##Nbits:, (void)0);                      \
		oldval = MODRM_GETRM##BWLQ();                                               \
		switch (modrm.mi_reg) {                                                     \
			                                                                        \
		case 0: /* rol r/mN,<num_bits> */                                           \
			if ((oldval << (num_bits - 1)) & msb_bit_set)                           \
				eflags_addend |= EFLAGS_CF;                                         \
			newval = __hybrid_rol##Nbits(oldval, num_bits);                         \
			break;                                                                  \
			                                                                        \
		case 1: /* ror r/mN,<num_bits> */                                           \
			if (oldval & ((u##Nbits)1 << (num_bits - 1)))                           \
				eflags_addend |= EFLAGS_CF;                                         \
			newval = __hybrid_ror##Nbits(oldval, num_bits);                         \
			break;                                                                  \
			                                                                        \
		case 2: /* rcl r/mN,<num_bits> */                                           \
			eflags_addend = EMU86_GETFLAGS() & EFLAGS_CF;                           \
			newval = emu86_rcl##bwlq(oldval, num_bits, &eflags_addend);             \
			break;                                                                  \
			                                                                        \
		case 3: /* rcr r/mN,<num_bits> */                                           \
			eflags_addend = EMU86_GETFLAGS() & EFLAGS_CF;                           \
			newval = emu86_rcr##bwlq(oldval, num_bits, &eflags_addend);             \
			break;                                                                  \
			                                                                        \
		case 4: /* sal r/mN,<num_bits> */                                           \
		case 6: /* shl r/mN,<num_bits> */                                           \
			if ((oldval << (num_bits - 1)) & msb_bit_set)                           \
				eflags_addend |= EFLAGS_CF;                                         \
			newval = oldval << num_bits;                                            \
			break;                                                                  \
			                                                                        \
		case 5: /* shr r/mN,<num_bits> */                                           \
			if (oldval & ((u##Nbits)1 << (num_bits - 1)))                           \
				eflags_addend |= EFLAGS_CF;                                         \
			newval = (u##Nbits)oldval >> num_bits;                                  \
			break;                                                                  \
			                                                                        \
		case 7: /* sar r/mN,<num_bits> */                                           \
			if (oldval & ((u##Nbits)1 << (num_bits - 1)))                           \
				eflags_addend |= EFLAGS_CF;                                         \
			newval = emu86_sar##bwlq(oldval, num_bits);                             \
			break;                                                                  \
			                                                                        \
		default:                                                                    \
			/* In 64-bit mode, REX.B can cause modrm.mi_reg to be > 7 */            \
			IFELSE_64BIT(goto return_unknown_instruction_rmreg,                     \
			             __builtin_unreachable());                                  \
		}                                                                           \
		/* Write-back the new result. */                                            \
		NIF_ONLY_MEMORY(                                                            \
		if (EMU86_MODRM_ISREG(modrm.mi_type)) {                                     \
			MODRM_SETRMREG##BWLQ(newval);                                           \
		} else) {                                                                   \
			byte_t *addr;                                                           \
			addr = MODRM_MEMADDR();                                                 \
			EMU86_WRITE_USER_MEMORY(addr, Nbytes);                                  \
			EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT(                                     \
			if (!EMU86_MEM_ATOMIC_CMPXCH_OR_WRITE##BWLQ(addr, oldval, newval,       \
			                                            EMU86_HASLOCK())) {         \
				EMU86_EMULATE_LOOPHINT();                                           \
				goto do_shift##Nbits;                                               \
			},                                                                      \
			EMU86_MEMWRITE##BWLQ(addr, newval);)                                    \
		}                                                                           \
		/* Update %eflags. */                                                       \
		{                                                                           \
			u32 eflags_mask = EFLAGS_CF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF;        \
			if (num_bits == 1) {                                                    \
				eflags_mask |= EFLAGS_OF;                                           \
				/* Calculate the new value of EFLAGS.OF */                          \
				switch (modrm.mi_reg) {                                             \
				case 0: /* rol */                                                   \
				case 2: /* rcl */                                                   \
					if (!!(newval & msb_bit_set) ^ !!(eflags_addend & EFLAGS_CF))   \
						eflags_addend |= EFLAGS_OF;                                 \
					break;                                                          \
				case 1: /* ror */                                                   \
					if (!!(newval & msb_bit_set) ^ !!(newval & (msb_bit_set >> 1))) \
						eflags_addend |= EFLAGS_OF;                                 \
					break;                                                          \
				case 3: /* rcr */                                                   \
				case 4: /* sal */                                                   \
				case 6: /* shl */                                                   \
					if (!!(oldval & msb_bit_set) ^ !!(eflags_addend & EFLAGS_CF))   \
						eflags_addend |= EFLAGS_OF;                                 \
					break;                                                          \
				case 7: /* sar */                                                   \
					/* EFLAGS.OF = 0 */                                             \
					break;                                                          \
				default:                                                            \
					if (oldval & msb_bit_set)                                       \
						eflags_addend |= EFLAGS_OF;                                 \
					break;                                                          \
				}                                                                   \
			}                                                                       \
			eflags_addend |= emu86_geteflags_test##bwlq(newval);                    \
			EMU86_MSKFLAGS(~eflags_mask, eflags_addend);                            \
		}                                                                           \
	}	__WHILE0
#if LIBEMU86_CONFIG_WANT_64BIT
#define NEED_return_unknown_instruction_rmreg
#endif /* LIBEMU86_CONFIG_WANT_64BIT */


case EMU86_OPCODE_ENCODE(0xd2): {
	/* D2 /0      ROL r/m8,CL      Rotate 8 bits r/m8 left CL times */
	/* D2 /1      ROR r/m8,CL      Rotate 8 bits r/m8 right CL times */
	/* D2 /2      RCL r/m8,CL      Rotate 9 bits (CF, r/m8) left CL times */
	/* D2 /3      RCR r/m8,CL      Rotate 9 bits (CF, r/m8) right CL times */
	/* D2 /4|6    SHL r/m8,CL      Multiply r/m8 by 2, CL times */
	/* D2 /5      SHR r/m8,CL      Unsigned divide r/m8 by 2, CL times */
	/* D2 /6|4    SAL r/m8,CL      Multiply r/m8 by 2, CL times */
	/* D2 /7      SAR r/m8,CL      Signed divide* r/m8 by 2, CL times */
	MODRM_DECODE();
	num_bits = EMU86_GETCL();
do_shift8bit:
	DEFINE_SHIFT_OPERATIONS_MODRM_reg(b, B, 8, 1, UINT8_C(0x80));
	goto done;
}


case EMU86_OPCODE_ENCODE(0xd3): {
	/* D3 /0      ROL r/m16,CL      Rotate 16 bits r/m16 left CL times */
	/* D3 /0      ROL r/m32,CL      Rotate 32 bits r/m32 left CL times */
	/* D3 /0      ROL r/m64,CL      Rotate 64 bits r/m64 left CL times */
	/* D3 /1      ROR r/m16,CL      Rotate 16 bits r/m16 right CL times */
	/* D3 /1      ROR r/m32,CL      Rotate 32 bits r/m32 right CL times */
	/* D3 /1      ROR r/m64,CL      Rotate 64 bits r/m64 right CL times */
	/* D3 /2      RCL r/m16,CL      Rotate 17 bits (CF, r/m16) left CL times */
	/* D3 /2      RCL r/m32,CL      Rotate 33 bits (CF, r/m32) left CL times */
	/* D3 /2      RCL r/m64,CL      Rotate 65 bits (CF, r/m64) left CL times */
	/* D3 /3      RCR r/m16,CL      Rotate 17 bits (CF, r/m16) right CL times */
	/* D3 /3      RCR r/m32,CL      Rotate 33 bits (CF, r/m32) right CL times */
	/* D3 /3      RCR r/m64,CL      Rotate 65 bits (CF, r/m64) right CL times */
	/* D3 /4|6    SHL r/m16,CL      Multiply r/m16 by 2, CL times */
	/* D3 /4|6    SHL r/m32,CL      Multiply r/m32 by 2, CL times */
	/* D3 /4|6    SHL r/m64,CL      Multiply r/m64 by 2, CL times */
	/* D3 /5      SHR r/m16,CL      Unsigned divide r/m16 by 2, CL times */
	/* D3 /5      SHR r/m32,CL      Unsigned divide r/m32 by 2, CL times */
	/* D3 /5      SHR r/m64,CL      Unsigned divide r/m64 by 2, CL times */
	/* D3 /6|4    SAL r/m16,CL      Multiply r/m16 by 2, CL times */
	/* D3 /6|4    SAL r/m32,CL      Multiply r/m32 by 2, CL times */
	/* D3 /6|4    SAL r/m64,CL      Multiply r/m64 by 2, CL times */
	/* D3 /7      SAR r/m16,CL      Signed divide* r/m16 by 2, CL times */
	/* D3 /7      SAR r/m32,CL      Signed divide* r/m32 by 2, CL times */
	/* D3 /7      SAR r/m64,CL      Signed divide* r/m64 by 2, CL times */
	MODRM_DECODE();
	num_bits  = EMU86_GETCL();
do_shift163264bit:
	IF_64BIT(if (IS_64BIT()) {
		DEFINE_SHIFT_OPERATIONS_MODRM_reg(q, Q, 64, 8, UINT64_C(0x8000000000000000));
	} else) if (!IS_16BIT()) {
		DEFINE_SHIFT_OPERATIONS_MODRM_reg(l, L, 32, 4, UINT32_C(0x80000000));
	} else {
		DEFINE_SHIFT_OPERATIONS_MODRM_reg(w, W, 16, 2, UINT16_C(0x8000));
	}
	goto done;
}

case EMU86_OPCODE_ENCODE(0xc0): {
	/* C0 /0   ib     ROL r/m8,imm8      Rotate 8 bits r/m8 left imm8 times */
	/* C0 /1   ib     ROR r/m8,imm8      Rotate 8 bits r/m16 right imm8 times */
	/* C0 /2   ib     RCL r/m8,imm8      Rotate 9 bits (CF, r/m8) left imm8 times */
	/* C0 /3   ib     RCR r/m8,imm8      Rotate 9 bits (CF, r/m8) right imm8 times */
	/* C0 /4|6 ib     SHL r/m8,imm8      Multiply r/m8 by 2, imm8 times */
	/* C0 /5   ib     SHR r/m8,imm8      Unsigned divide r/m8 by 2, imm8 times */
	/* C0 /6|4 ib     SAL r/m8,imm8      Multiply r/m8 by 2, imm8 times */
	/* C0 /7   ib     SAR r/m8,imm8      Signed divide* r/m8 by 2, imm8 times */
	MODRM_DECODE();
	num_bits  = *(u8 const *)pc;
	pc += 1;
	goto do_shift8bit;
}

case EMU86_OPCODE_ENCODE(0xc1): {
	/* D1 /0   ib     ROL r/m16,imm8      Rotate 16 bits r/m16 left imm8 times */
	/* D1 /0   ib     ROL r/m32,imm8      Rotate 32 bits r/m32 left imm8 times */
	/* D1 /0   ib     ROL r/m64,imm8      Rotate 64 bits r/m64 left imm8 times */
	/* D1 /1   ib     ROR r/m16,imm8      Rotate 16 bits r/m16 right imm8 times */
	/* D1 /1   ib     ROR r/m32,imm8      Rotate 32 bits r/m32 right imm8 times */
	/* D1 /1   ib     ROR r/m64,imm8      Rotate 64 bits r/m64 right imm8 times */
	/* D1 /2   ib     RCL r/m16,imm8      Rotate 17 bits (CF, r/m16) left imm8 times */
	/* D1 /2   ib     RCL r/m32,imm8      Rotate 33 bits (CF, r/m32) left imm8 times */
	/* D1 /2   ib     RCL r/m64,imm8      Rotate 65 bits (CF, r/m64) left imm8 times */
	/* D1 /3   ib     RCR r/m16,imm8      Rotate 17 bits (CF, r/m16) right imm8 times */
	/* D1 /3   ib     RCR r/m32,imm8      Rotate 33 bits (CF, r/m32) right imm8 times */
	/* D1 /3   ib     RCR r/m64,imm8      Rotate 65 bits (CF, r/m64) right imm8 times */
	/* D1 /4|6 ib     SHL r/m16,imm8      Multiply r/m16 by 2, imm8 times */
	/* D1 /4|6 ib     SHL r/m32,imm8      Multiply r/m32 by 2, imm8 times */
	/* D1 /4|6 ib     SHL r/m64,imm8      Multiply r/m64 by 2, imm8 times */
	/* D1 /5   ib     SHR r/m16,imm8      Unsigned divide r/m16 by 2, imm8 times */
	/* D1 /5   ib     SHR r/m32,imm8      Unsigned divide r/m32 by 2, imm8 times */
	/* D1 /5   ib     SHR r/m64,imm8      Unsigned divide r/m64 by 2, imm8 times */
	/* D1 /6|4 ib     SAL r/m16,imm8      Multiply r/m16 by 2, imm8 times */
	/* D1 /6|4 ib     SAL r/m32,imm8      Multiply r/m32 by 2, imm8 times */
	/* D1 /6|4 ib     SAL r/m64,imm8      Multiply r/m64 by 2, imm8 times */
	/* D1 /7   ib     SAR r/m16,imm8      Signed divide* r/m16 by 2, imm8 times */
	/* D1 /7   ib     SAR r/m32,imm8      Signed divide* r/m32 by 2, imm8 times */
	/* D1 /7   ib     SAR r/m64,imm8      Signed divide* r/m64 by 2, imm8 times */
	MODRM_DECODE();
	num_bits = *(u8 const *)pc;
	pc += 1;
	goto do_shift163264bit;
}


case EMU86_OPCODE_ENCODE(0xd0): {
	/* D0 /0      ROL r/m8,1      Rotate 8 bits r/m8 left once */
	/* D0 /1      ROR r/m8,1      Rotate 8 bits r/m8 right once */
	/* D0 /2      RCL r/m8,1      Rotate 9 bits (CF, r/m8) left once */
	/* D0 /3      RCR r/m8,1      Rotate 9 bits (CF, r/m8) right once */
	/* D0 /4|6    SHL r/m8,1      Multiply r/m8 by 2, 1 time */
	/* D0 /5      SHR r/m8,1      Unsigned divide r/m8 by 2, 1 time */
	/* D0 /6|4    SAL r/m8,1      Multiply r/m8 by 2, 1 time */
	/* D0 /7      SAR r/m8,1      Signed divide* r/m8 by 2, 1 times */
	MODRM_DECODE();
	num_bits = 1;
	goto do_shift8bit;
}

case EMU86_OPCODE_ENCODE(0xd1): {
	/* D1 /0      ROL r/m16,1      Rotate 16 bits r/m16 left once */
	/* D1 /0      ROL r/m32,1      Rotate 32 bits r/m32 left once */
	/* D1 /0      ROL r/m64,1      Rotate 64 bits r/m64 left once */
	/* D1 /1      ROR r/m16,1      Rotate 16 bits r/m16 right once */
	/* D1 /1      ROR r/m32,1      Rotate 32 bits r/m32 right once */
	/* D1 /1      ROR r/m64,1      Rotate 64 bits r/m64 right once */
	/* D1 /2      RCL r/m16,1      Rotate 17 bits (CF, r/m16) left once */
	/* D1 /2      RCL r/m32,1      Rotate 33 bits (CF, r/m32) left once */
	/* D1 /2      RCL r/m64,1      Rotate 65 bits (CF, r/m64) left once */
	/* D1 /3      RCR r/m16,1      Rotate 17 bits (CF, r/m16) right once */
	/* D1 /3      RCR r/m32,1      Rotate 33 bits (CF, r/m32) right once */
	/* D1 /3      RCR r/m64,1      Rotate 65 bits (CF, r/m64) right once */
	/* D1 /4|6    SHL r/m16,1      Multiply r/m16 by 2, 1 time */
	/* D1 /4|6    SHL r/m32,1      Multiply r/m32 by 2, 1 time */
	/* D1 /4|6    SHL r/m64,1      Multiply r/m64 by 2, 1 time */
	/* D1 /5      SHR r/m16,1      Unsigned divide r/m16 by 2, 1 time */
	/* D1 /5      SHR r/m32,1      Unsigned divide r/m32 by 2, 1 time */
	/* D1 /5      SHR r/m64,1      Unsigned divide r/m64 by 2, 1 time */
	/* D1 /6|4    SAL r/m16,1      Multiply r/m16 by 2, 1 time */
	/* D1 /6|4    SAL r/m32,1      Multiply r/m32 by 2, 1 time */
	/* D1 /6|4    SAL r/m64,1      Multiply r/m64 by 2, 1 time */
	/* D1 /7      SAR r/m16,1      Signed divide* r/m16 by 2, 1 times */
	/* D1 /7      SAR r/m32,1      Signed divide* r/m32 by 2, 1 times */
	/* D1 /7      SAR r/m64,1      Signed divide* r/m64 by 2, 1 times */
	MODRM_DECODE();
	num_bits = 1;
	goto do_shift163264bit;
}

#undef DEFINE_SHIFT_OPERATIONS_MODRM_reg
#undef EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT
#else /* EMU86_EMULATE_CONFIG_WANT_SHIFT */

#if EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0xd2):
case EMU86_OPCODE_ENCODE(0xc0):
case EMU86_OPCODE_ENCODE(0xd0):
	goto notsup_modrm_getsetb;
#define NEED_notsup_modrm_getsetb

case EMU86_OPCODE_ENCODE(0xd3):
case EMU86_OPCODE_ENCODE(0xc1):
case EMU86_OPCODE_ENCODE(0xd1):
	goto notsup_modrm_getsetwlq;
#define NEED_notsup_modrm_getsetwlq
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR */

#endif /* !EMU86_EMULATE_CONFIG_WANT_SHIFT */

}
EMU86_INTELLISENSE_END
