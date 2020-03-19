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

#include "pushpop-util.h"

EMU86_INTELLISENSE_BEGIN(pushpop_segments) {

#if CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT

/************************************************************************/
/* PUSH ES                                                              */
/************************************************************************/
case 0x06: {
	EMU86_PUSH1632(u16, EMU86_GETES());
	goto done;
}


/************************************************************************/
/* POP ES                                                               */
/************************************************************************/
case 0x07: {
	EMU86_POP1632(u16, EMU86_SETES);
	goto done;
}


/************************************************************************/
/* PUSH CS                                                              */
/************************************************************************/
case 0x0e: {
	EMU86_PUSH1632(u16, EMU86_GETCS());
	goto done;
}


/************************************************************************/
/* PUSH SS                                                              */
/************************************************************************/
case 0x16: {
	EMU86_PUSH1632(u16, EMU86_GETSS());
	goto done;
}


/************************************************************************/
/* POP SS                                                               */
/************************************************************************/
case 0x17: {
	EMU86_POP1632(u16, EMU86_SETSS);
	goto done;
}


/************************************************************************/
/* PUSH DS                                                              */
/************************************************************************/
case 0x1e: {
	EMU86_PUSH1632(u16, EMU86_GETDS());
	goto done;
}


/************************************************************************/
/* POP DS                                                               */
/************************************************************************/
case 0x1f: {
	EMU86_POP1632(u16, EMU86_SETDS);
	goto done;
}

#endif /* CONFIG_LIBEMU86_WANT_16BIT || CONFIG_LIBEMU86_WANT_32BIT */



/************************************************************************/
/* PUSH FS                                                              */
/************************************************************************/
case 0x0fa0: {
	EMU86_PUSH163264(EMU86_GETFS(),
	                 EMU86_GETFS(),
	                 EMU86_GETFS());
	goto done;
}


/************************************************************************/
/* POP FS                                                              */
/************************************************************************/
case 0x0fa1: {
	EMU86_POP163264(EMU86_SETFS,
	                EMU86_SETFS,
	                EMU86_SETFS);
	goto done;
}



/************************************************************************/
/* PUSH GS                                                              */
/************************************************************************/
case 0x0fa8: {
	EMU86_PUSH163264(EMU86_GETGS(),
	                 EMU86_GETGS(),
	                 EMU86_GETGS());
	goto done;
}


/************************************************************************/
/* POP GS                                                              */
/************************************************************************/
case 0x0fa9: {
	EMU86_POP163264(EMU86_SETGS,
	                EMU86_SETGS,
	                EMU86_SETGS);
	goto done;
}




case 0x50 ... 0x57: {
	/* 50+rw     PUSH r16     Push r16.
	 * 50+rd     PUSH r32     Push r32.
	 * 50+rd     PUSH r64     Push r64. */
	u8 regno = (u8)(opcode - 0x50);
	EMU86_PUSH163264(EMU86_GETREGW(regno),
	                 EMU86_GETREGL(regno),
	                 EMU86_GETREGQ(regno));
	goto done;
}
	
case 0x58 ... 0x5f: {
	/* 50+rw     POP r16     Pop r16.
	 * 50+rd     POP r32     Pop r32.
	 * 50+rd     POP r64     Pop r64. */
	u8 regno = (u8)(opcode - 0x50);
#define SETREGW(v) EMU86_SETREGW(regno, v)
#define SETREGL(v) EMU86_SETREGL(regno, v)
#define SETREGQ(v) EMU86_SETREGQ(regno, v)
	EMU86_POP163264(SETREGW,
	                SETREGL,
	                SETREGQ);
#undef SETREGQ
#undef SETREGL
#undef SETREGW
	goto done;
}



case 0x8f: {
	MODRM_DECODE();
	if (modrm.mi_reg != 0)
		goto return_unknown_instruction;
	/* 8F /0     POP r/m16     Pop top of stack into m16; increment stack pointer.
	 * 8F /0     POP r/m32     Pop top of stack into m32; increment stack pointer.
	 * 8F /0     POP r/m64     Pop top of stack into m64; increment stack pointer.
	 *                         Cannot encode 32-bit operand size. */
	EMU86_POP163264(MODRM_SETRMW,
	                MODRM_SETRML,
	                MODRM_SETRMQ);
	goto done;
}


{
#if CONFIG_LIBEMU86_WANT_64BIT
#define IMM_STYPE s64
#define IMM_UTYPE u64
#else /* CONFIG_LIBEMU86_WANT_64BIT */
#define IMM_STYPE s32
#define IMM_UTYPE u32
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */
	IMM_UTYPE imm;
case 0x6a:
	imm = (IMM_UTYPE)(IMM_STYPE)*(s8 *)pc;
	pc += 1;
	goto do_push_imm;
case 0x68:
	/* 6A ib     PUSH imm8      Push imm8.
	 * 68 iw     PUSH imm16     Push imm16.
	 * 68 id     PUSH imm32     Push imm32. */
	if (IS_16BIT()) {
		imm = (IMM_UTYPE)(IMM_STYPE)(s16)UNALIGNED_GET16((u16 *)pc);
		pc += 2;
	} else {
		imm = (IMM_UTYPE)(IMM_STYPE)(s32)UNALIGNED_GET32((u32 *)pc);
		pc += 4;
	}
do_push_imm:
	EMU86_PUSH163264((u16)imm,
	                 (u32)imm,
	                 (u64)imm);
	goto done;
#undef IMM_UTYPE
#undef IMM_STYPE
}


}
EMU86_INTELLISENSE_END
