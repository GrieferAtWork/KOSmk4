/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "../emulate.c.inl"
#endif /* __INTELLISENSE__ */

EMU86_INTELLISENSE_BEGIN(leave) {


#if EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LEAVE
case EMU86_OPCODE_ENCODE(0xc9): {
	/* C9     LEAVE     ZO     Valid    Valid     Set SP to BP, then pop BP.
	 * C9     LEAVE     ZO     N.E.     Valid     Set ESP to EBP, then pop EBP. */
	/* Behavior:
	 *    temp = %Pbp;
	 *    %Pbp = *(void **)temp;
	 *    %Psp = temp + sizeof(void *);
	 */
	if (IS_16BIT()) {
		u16 bp;
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
		u16 orig_bp;
#endif /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
		bp = EMU86_GETBP();
#ifndef EMU86_GETSEGBASE_IS_NOOP_SS
		{
			byte_t *bp_addr;
			bp_addr = EMU86_SEGADDR(EMU86_GETSSBASE(), bp);
			(void)bp_addr;
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
			EMU86_READ_USER_MEMORY(bp_addr, 2);
			orig_bp = EMU86_MEMREADW(bp_addr);
#else /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
			EMU86_UNSUPPORTED_MEMACCESS(bp_addr, 2, true, false);
#endif /* !EMU86_EMULATE_CONFIG_WANT_LEAVE */
		}
#else /* !EMU86_GETSEGBASE_IS_NOOP_SS */
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
		EMU86_READ_USER_MEMORY(bp, 2);
		orig_bp = EMU86_MEMREADW(bp);
#else /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
		EMU86_UNSUPPORTED_MEMACCESS((void *)(uintptr_t)bp, 2, true, false);
#endif /* !EMU86_EMULATE_CONFIG_WANT_LEAVE */
#endif /* EMU86_GETSEGBASE_IS_NOOP_SS */
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
		EMU86_SETBP(orig_bp);
		EMU86_SETSPREG(bp + 2);
#endif /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
	}
#if LIBEMU86_CONFIG_WANT_64BIT
	else IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
		u64 bp;
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
		u64 orig_bp;
#endif /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
		bp = EMU86_GETRBP();
#ifndef EMU86_GETSEGBASE_IS_NOOP_SS
		{
			byte_t *bp_addr;
			bp_addr = EMU86_SEGADDR(EMU86_GETSSBASE(), bp);
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
			EMU86_READ_USER_MEMORY(bp_addr, 8);
			orig_bp = EMU86_MEMREADQ(bp_addr);
#else /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
			EMU86_UNSUPPORTED_MEMACCESS(bp_addr, 8, true, false);
#endif /* !EMU86_EMULATE_CONFIG_WANT_LEAVE */
		}
#else /* !EMU86_GETSEGBASE_IS_NOOP_SS */
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
		EMU86_READ_USER_MEMORY(bp, 8);
		orig_bp = EMU86_MEMREADQ(bp);
#else /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
		EMU86_UNSUPPORTED_MEMACCESS((void *)bp, 8, true, false);
#endif /* !EMU86_EMULATE_CONFIG_WANT_LEAVE */
#endif /* EMU86_GETSEGBASE_IS_NOOP_SS */
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
		EMU86_SETRBP(orig_bp);
		EMU86_SETSPREG(bp + 8);
#endif /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
	}
#endif /* LIBEMU86_CONFIG_WANT_64BIT */
#if LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT
	else {
		u32 bp;
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
		u32 orig_bp;
#endif /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
		bp = EMU86_GETEBP();
#ifndef EMU86_GETSEGBASE_IS_NOOP_SS
		{
			byte_t *bp_addr;
			bp_addr = EMU86_SEGADDR(EMU86_GETSSBASE(), bp);
			(void)bp_addr;
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
			EMU86_READ_USER_MEMORY(bp_addr, 4);
			orig_bp = EMU86_MEMREADL(bp_addr);
#else /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
			EMU86_UNSUPPORTED_MEMACCESS(bp_addr, 4, true, false);
#endif /* !EMU86_EMULATE_CONFIG_WANT_LEAVE */
		}
#else /* !EMU86_GETSEGBASE_IS_NOOP_SS */
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
		EMU86_READ_USER_MEMORY(bp, 4);
		orig_bp = EMU86_MEMREADL(bp);
#else /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
		EMU86_UNSUPPORTED_MEMACCESS((void *)(uintptr_t)bp, 4, true, false);
#endif /* !EMU86_EMULATE_CONFIG_WANT_LEAVE */
#endif /* EMU86_GETSEGBASE_IS_NOOP_SS */
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
		EMU86_SETEBP(orig_bp);
		EMU86_SETSPREG(bp + 4);
#endif /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
	}
#endif /* LIBEMU86_CONFIG_WANT_32BIT || LIBEMU86_CONFIG_WANT_16BIT */
#if EMU86_EMULATE_CONFIG_WANT_LEAVE
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_LEAVE */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_LEAVE */
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_LEAVE */


}
EMU86_INTELLISENSE_END
