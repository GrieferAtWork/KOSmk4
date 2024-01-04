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
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

/* SSE's 3-operand shift instructions. */
EMU86_INTELLISENSE_BEGIN(shift2) {

#if EMU86_EMULATE_CONFIG_WANT_SHIFT2
	/* The number of bits by which to shift */
	u8 num_bits;

#if EMU86_EMULATE_CONFIG_LOCK_SHIFT2 /* Extension!!! */
#define EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT2(tt, ff) tt
#else /* EMU86_EMULATE_CONFIG_LOCK_SHIFT2 */
#define EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT2(tt, ff) ff
#endif /* !EMU86_EMULATE_CONFIG_LOCK_SHIFT2 */


#define DEFINE_SHLD_MODRM_rm_reg(bwlq, BWLQ, Nbits, Nbytes, msb_bit_set)     \
	u##Nbits oldval, bitsrc, newval;                                         \
	num_bits &= (Nbits - 1);                                                 \
	if (!num_bits)                                                           \
		goto done;                                                           \
	bitsrc = MODRM_GETREG##BWLQ();                                           \
	NIF_ONLY_MEMORY(if (EMU86_MODRM_ISREG(modrm.mi_type)) {                  \
		oldval = MODRM_GETRMREG##BWLQ();                                     \
		newval = (oldval << num_bits) |                                      \
		         (bitsrc >> (Nbits - num_bits));                             \
		MODRM_SETRMREG##BWLQ(newval);                                        \
	} else) {                                                                \
		byte_t *addr;                                                        \
		addr = MODRM_MEMADDR();                                              \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                               \
		EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT2(                                 \
		for (;;) {                                                           \
			oldval = EMU86_MEMREAD##BWLQ(addr);                              \
			newval = (oldval << num_bits) |                                  \
			         (bitsrc >> (Nbits - num_bits));                         \
			if (EMU86_MEM_ATOMIC_CMPXCH_OR_WRITE##BWLQ(addr, oldval, newval, \
			                                           EMU86_HASLOCK()))     \
				break;                                                       \
			EMU86_EMULATE_LOOPHINT();                                        \
		},                                                                   \
		oldval = EMU86_MEMREAD##BWLQ(addr);                                  \
		newval = (oldval << num_bits) |                                      \
		         (bitsrc >> (Nbits - num_bits));                             \
		EMU86_MEMWRITE##BWLQ(addr, newval);)                                 \
	}                                                                        \
	if ((oldval << (num_bits - 1)) & msb_bit_set)                            \
		eflags_addend |= EFLAGS_CF;                                          \
	if (num_bits == 1) {                                                     \
		eflags_mask |= EFLAGS_OF;                                            \
		if ((oldval & msb_bit_set) != (newval & msb_bit_set))                \
			eflags_addend |= EFLAGS_OF;                                      \
	}                                                                        \
	eflags_addend |= emu86_geteflags_test##bwlq(newval);


case EMU86_OPCODE_ENCODE(0x0fa5): {
	/* 0F A5      SHLD r/m16, r16, CL      Shift r/m16 to left CL places while shifting bits from r16 in from the right
	 * 0F A5      SHLD r/m32, r32, CL      Shift r/m32 to left CL places while shifting bits from r32 in from the right
	 * 0F A5      SHLD r/m64, r64, CL      Shift r/m64 to left CL places while shifting bits from r64 in from the right */
	u32 eflags_addend, eflags_mask;
	MODRM_DECODE();
	num_bits = EMU86_GETCL();
do_shld:
	eflags_addend = 0;
	eflags_mask   = EFLAGS_CF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF;
	IF_64BIT(if (IS_64BIT()) {
		DEFINE_SHLD_MODRM_rm_reg(q, Q, 64, 8, UINT64_C(0x8000000000000000))
	} else) if (!IS_16BIT()) {
		DEFINE_SHLD_MODRM_rm_reg(l, L, 32, 4, UINT32_C(0x80000000))
	} else {
		DEFINE_SHLD_MODRM_rm_reg(w, W, 16, 2, UINT16_C(0x8000))
	}
	EMU86_MSKFLAGS(~eflags_mask, eflags_addend);
	goto done;
}

case EMU86_OPCODE_ENCODE(0x0fa4): {
	/* 0F A4      SHLD r/m16, r16, imm8      Shift r/m16 to left imm8 places while shifting bits from r16 in from the right
	 * 0F A4      SHLD r/m32, r32, imm8      Shift r/m32 to left imm8 places while shifting bits from r32 in from the right
	 * 0F A4      SHLD r/m64, r64, imm8      Shift r/m64 to left imm8 places while shifting bits from r64 in from the right */
	MODRM_DECODE();
	num_bits = *(u8 const *)pc;
	pc += 1;
	goto do_shld;
}

#undef DEFINE_SHLD_MODRM_rm_reg

#define DEFINE_SHRD_MODRM_rm_reg(bwlq, BWLQ, Nbits, Nbytes, msb_bit_set)     \
	u##Nbits oldval, bitsrc, newval;                                         \
	num_bits &= (Nbits - 1);                                                 \
	if (!num_bits)                                                           \
		goto done;                                                           \
	bitsrc = MODRM_GETREG##BWLQ();                                           \
	NIF_ONLY_MEMORY(if (EMU86_MODRM_ISREG(modrm.mi_type)) {                  \
		oldval = MODRM_GETRMREG##BWLQ();                                     \
		newval = (oldval >> num_bits) |                                      \
		         (bitsrc << (Nbits - num_bits));                             \
		MODRM_SETRMREG##BWLQ(newval);                                        \
	} else) {                                                                \
		byte_t *addr;                                                        \
		addr = MODRM_MEMADDR();                                              \
		EMU86_WRITE_USER_MEMORY(addr, Nbytes);                               \
		EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT2(                                 \
		for (;;) {                                                           \
			oldval = EMU86_MEMREAD##BWLQ(addr);                              \
			newval = (oldval >> num_bits) |                                  \
			         (bitsrc << (Nbits - num_bits));                         \
			if (EMU86_MEM_ATOMIC_CMPXCH_OR_WRITE##BWLQ(addr, oldval, newval, \
			                                           EMU86_HASLOCK()))     \
				break;                                                       \
			EMU86_EMULATE_LOOPHINT();                                        \
		},                                                                   \
		oldval = EMU86_MEMREAD##BWLQ(addr);                                  \
		newval = (oldval >> num_bits) |                                      \
		         (bitsrc << (Nbits - num_bits));                             \
		EMU86_MEMWRITE##BWLQ(addr, newval);)                                 \
	}                                                                        \
	if ((oldval >> (num_bits - 1)) & 1)                                      \
		eflags_addend |= EFLAGS_CF;                                          \
	if (num_bits == 1) {                                                     \
		eflags_mask |= EFLAGS_OF;                                            \
		if ((oldval & msb_bit_set) != (newval & msb_bit_set))                \
			eflags_addend |= EFLAGS_OF;                                      \
	}                                                                        \
	eflags_addend |= emu86_geteflags_test##bwlq(newval);


case EMU86_OPCODE_ENCODE(0x0fad): {
	/* 0F AD      SHRD r/m16, r16, CL      Shift r/m16 to right CL places while shifting bits from r16 in from the left
	 * 0F AD      SHRD r/m32, r32, CL      Shift r/m32 to right CL places while shifting bits from r32 in from the left
	 * 0F AD      SHRD r/m64, r64, CL      Shift r/m64 to right CL places while shifting bits from r64 in from the left */
	u32 eflags_addend, eflags_mask;
	MODRM_DECODE();
	num_bits = EMU86_GETCL();
do_shrd:
	eflags_addend = 0;
	eflags_mask   = EFLAGS_CF | EFLAGS_SF | EFLAGS_ZF | EFLAGS_PF;
	IF_64BIT(if (IS_64BIT()) {
		DEFINE_SHRD_MODRM_rm_reg(q, Q, 64, 8, UINT64_C(0x8000000000000000))
	} else) if (!IS_16BIT()) {
		DEFINE_SHRD_MODRM_rm_reg(l, L, 32, 4, UINT32_C(0x80000000))
	} else {
		DEFINE_SHRD_MODRM_rm_reg(w, W, 16, 2, UINT16_C(0x8000))
	}
	EMU86_MSKFLAGS(~eflags_mask, eflags_addend);
	goto done;
}

case EMU86_OPCODE_ENCODE(0x0fac): {
	/* 0F AC      SHRD r/m16, r16, imm8      Shift r/m16 to right imm8 places while shifting bits from r16 in from the left
	 * 0F AC      SHRD r/m32, r32, imm8      Shift r/m32 to right imm8 places while shifting bits from r32 in from the left
	 * 0F AC      SHRD r/m64, r64, imm8      Shift r/m64 to right imm8 places while shifting bits from r64 in from the left */
	MODRM_DECODE();
	num_bits = *(u8 const *)pc;
	pc += 1;
	goto do_shrd;
}

#undef DEFINE_SHRD_MODRM_rm_reg
#undef EMU86_EMULATE_IF_CONFIG_LOCK_SHIFT2
#else /* EMU86_EMULATE_CONFIG_WANT_SHIFT2 */

#if EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fa5):
case EMU86_OPCODE_ENCODE(0x0fa4):
case EMU86_OPCODE_ENCODE(0x0fad):
case EMU86_OPCODE_ENCODE(0x0fac):
	goto notsup_modrm_getsetwlq;
#define NEED_notsup_modrm_getsetwlq
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR */

#endif /* !EMU86_EMULATE_CONFIG_WANT_SHIFT2 */


}
EMU86_INTELLISENSE_END
