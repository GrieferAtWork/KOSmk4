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
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(pusha_popa) {


#if (EMU86_EMULATE_CONFIG_CHECKERROR ||  \
     (EMU86_EMULATE_CONFIG_WANT_PUSHA && \
      (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT)))
case EMU86_OPCODE_ENCODE(0x60): {
	/* 60     PUSHA      Push AX, CX, DX, BX, original SP, BP, SI, and DI.
	 * 60     PUSHAD     Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI. */
#if EMU86_EMULATE_CONFIG_WANT_PUSHA && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT)
#if LIBEMU86_CONFIG_WANT_64BIT
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	{
		byte_t *sp;
		sp = EMU86_GETSTACKPTR();
		if (!IS_16BIT()) {
			sp -= 32;
			EMU86_EMULATE_PUSH(sp, 32);
			EMU86_WRITE_USER_MEMORY(sp, 32);
			EMU86_MEMWRITEL(sp + 0x00, EMU86_GETEDI());
			EMU86_MEMWRITEL(sp + 0x04, EMU86_GETESI());
			EMU86_MEMWRITEL(sp + 0x08, EMU86_GETEBP());
			EMU86_MEMWRITEL(sp + 0x0c, EMU86_GETESP());
			EMU86_MEMWRITEL(sp + 0x10, EMU86_GETEBX());
			EMU86_MEMWRITEL(sp + 0x14, EMU86_GETEDX());
			EMU86_MEMWRITEL(sp + 0x18, EMU86_GETECX());
			EMU86_MEMWRITEL(sp + 0x1c, EMU86_GETEAX());
		} else {
			sp -= 16;
			EMU86_EMULATE_PUSH(sp, 16);
			EMU86_WRITE_USER_MEMORY(sp, 16);
			EMU86_MEMWRITEW(sp + 0x0, EMU86_GETDI());
			EMU86_MEMWRITEW(sp + 0x2, EMU86_GETSI());
			EMU86_MEMWRITEW(sp + 0x4, EMU86_GETBP());
			EMU86_MEMWRITEW(sp + 0x6, EMU86_GETSP());
			EMU86_MEMWRITEW(sp + 0x8, EMU86_GETBX());
			EMU86_MEMWRITEW(sp + 0xa, EMU86_GETDX());
			EMU86_MEMWRITEW(sp + 0xc, EMU86_GETCX());
			EMU86_MEMWRITEW(sp + 0xe, EMU86_GETAX());
		}
		EMU86_SETSTACKPTR(sp);
		goto done;
	}
#else /* EMU86_EMULATE_CONFIG_WANT_PUSHA && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT) */
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
	IF_64BIT(if (!EMU86_F_IS64(op_flags))) {
		byte_t *sp;
		sp = EMU86_GETSTACKPTR();
		if (!IS_16BIT()) {
			sp -= 32;
			EMU86_EMULATE_PUSH(sp, 32);
			EMU86_UNSUPPORTED_MEMACCESS(sp, 32, false, true);
		} else {
			sp -= 16;
			EMU86_EMULATE_PUSH(sp, 16);
			EMU86_UNSUPPORTED_MEMACCESS(sp, 16, false, true);
		}
	}
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* !EMU86_EMULATE_CONFIG_WANT_PUSHA || (!LIBEMU86_CONFIG_WANT_32BIT && !LIBEMU86_CONFIG_WANT_16BIT) */
}
#endif /* ... */


#if (EMU86_EMULATE_CONFIG_CHECKERROR ||  \
     (EMU86_EMULATE_CONFIG_WANT_POPA && \
      (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT)))
case EMU86_OPCODE_ENCODE(0x61): {
	/* 61     POPA      Pop DI, SI, BP, BX, DX, CX, and AX.
	 * 61     POPAD     Pop EDI, ESI, EBP, EBX, EDX, ECX, and EAX. */
#if EMU86_EMULATE_CONFIG_WANT_POPA && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT)
#if LIBEMU86_CONFIG_WANT_64BIT
	if (EMU86_F_IS64(op_flags))
		goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
	{
		byte_t *sp;
		sp = EMU86_GETSTACKPTR();
		if (!IS_16BIT()) {
			u32 eax, ecx, edx, ebx, ebp, esi, edi;
			EMU86_EMULATE_POP(sp, 32);
			EMU86_READ_USER_MEMORY(sp, 32);
			edi = EMU86_MEMREADL(sp + 0x00);
			esi = EMU86_MEMREADL(sp + 0x04);
			ebp = EMU86_MEMREADL(sp + 0x08);
/*			esp = EMU86_MEMREADL(sp + 0x0c); */
			ebx = EMU86_MEMREADL(sp + 0x10);
			edx = EMU86_MEMREADL(sp + 0x14);
			ecx = EMU86_MEMREADL(sp + 0x18);
			eax = EMU86_MEMREADL(sp + 0x1c);
			COMPILER_READ_BARRIER();
			EMU86_SETEDI(edi);
			EMU86_SETESI(esi);
			EMU86_SETEBP(ebp);
			EMU86_SETEBX(ebx);
			EMU86_SETEDX(edx);
			EMU86_SETECX(ecx);
			EMU86_SETEAX(eax);
			sp += 32;
		} else {
			u16 ax, cx, dx, bx, bp, si, di;
			EMU86_EMULATE_POP(sp, 16);
			EMU86_READ_USER_MEMORY(sp, 16);
			di = EMU86_MEMREADL(sp + 0x0);
			si = EMU86_MEMREADL(sp + 0x2);
			bp = EMU86_MEMREADL(sp + 0x4);
/*			sp = EMU86_MEMREADL(sp + 0x6); */
			bx = EMU86_MEMREADL(sp + 0x8);
			dx = EMU86_MEMREADL(sp + 0xa);
			cx = EMU86_MEMREADL(sp + 0xc);
			ax = EMU86_MEMREADL(sp + 0xe);
			COMPILER_READ_BARRIER();
			EMU86_SETDI(di);
			EMU86_SETSI(si);
			EMU86_SETBP(bp);
			EMU86_SETBX(bx);
			EMU86_SETDX(dx);
			EMU86_SETCX(cx);
			EMU86_SETAX(ax);
			sp += 16;
		}
		EMU86_SETSTACKPTR(sp);
		goto done;
	}
#else /* EMU86_EMULATE_CONFIG_WANT_POPA && (LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT) */
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
	IF_64BIT(if (!EMU86_F_IS64(op_flags))) {
		byte_t *sp;
		sp = EMU86_GETSTACKPTR();
		(void)sp;
		if (!IS_16BIT()) {
			EMU86_EMULATE_POP(sp, 32);
			EMU86_UNSUPPORTED_MEMACCESS(sp, 32, true, false);
		} else {
			EMU86_EMULATE_POP(sp, 16);
			EMU86_UNSUPPORTED_MEMACCESS(sp, 16, true, false);
		}
	}
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
#define NEED_return_unsupported_instruction
	goto return_unsupported_instruction;
#endif /* !EMU86_EMULATE_CONFIG_WANT_POPA || (!LIBEMU86_CONFIG_WANT_32BIT && !LIBEMU86_CONFIG_WANT_16BIT) */
}
#endif /* ... */


}
EMU86_INTELLISENSE_END
