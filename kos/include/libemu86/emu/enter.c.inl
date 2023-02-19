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

EMU86_INTELLISENSE_BEGIN(enter) {

#if (EMU86_EMULATE_CONFIG_WANT_ENTER || (EMU86_EMULATE_CONFIG_CHECKERROR && !defined(EMU86_UNSUPPORTED_MEMACCESS_IS_NOOP)))
case EMU86_OPCODE_ENCODE(0xc8): {
	/* C8 iw 00     ENTER imm16, 0        Create a stack frame for a procedure.
	 * C8 iw 01     ENTER imm16, 1        Create a stack frame with a nested pointer for a procedure.
	 * C8 iw ib     ENTER imm16, imm8     Create a stack frame with nested pointers for a procedure. */
	EMU86_UREG_TYPE pbp;
#if EMU86_EMULATE_CONFIG_WANT_ENTER
	EMU86_UREG_TYPE frameTemp;
#endif /* EMU86_EMULATE_CONFIG_WANT_ENTER */
	u16 alloc_size;
	u8 nesting_level;
	byte_t *sp;
	alloc_size = UNALIGNED_GETLE16(pc);
	(void)alloc_size;
	pc += 2;
	nesting_level = UNALIGNED_GETLE8(pc);
	pc += 1;
	nesting_level %= 32;
	sp  = EMU86_GETSTACKPTR();
	pbp = EMU86_GETPBP(op_flags);
	if (IS_16BIT()) {
		size_t push_total = 2 * (nesting_level + 1);
		(void)push_total;
		EMU86_EMULATE_PUSH(sp - (push_total + alloc_size), push_total + alloc_size);
#if EMU86_EMULATE_CONFIG_WANT_ENTER
		EMU86_WRITE_USER_MEMORY(sp - push_total, push_total);
		frameTemp = EMU86_GETSP() - 2;
		EMU86_MEMWRITEW(sp, pbp);
#else /* EMU86_EMULATE_CONFIG_WANT_ENTER */
		EMU86_UNSUPPORTED_MEMACCESS(sp - push_total, push_total, false, true);
#endif /* !EMU86_EMULATE_CONFIG_WANT_ENTER */
	} else IF_64BIT(IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
		size_t push_total = 8 * (nesting_level + 1);
		(void)push_total;
		EMU86_EMULATE_PUSH(sp - (push_total + alloc_size), push_total + alloc_size);
#if EMU86_EMULATE_CONFIG_WANT_ENTER
		EMU86_WRITE_USER_MEMORY(sp - push_total, push_total);
		sp -= 8;
		frameTemp = EMU86_GETRSP() - 8;
		EMU86_MEMWRITEQ(sp, pbp);
#else /* EMU86_EMULATE_CONFIG_WANT_ENTER */
		EMU86_UNSUPPORTED_MEMACCESS(sp - push_total, push_total, false, true);
#endif /* !EMU86_EMULATE_CONFIG_WANT_ENTER */
	} IF_16BIT_OR_32BIT(else)) IF_16BIT_OR_32BIT({
		size_t push_total = 4 * (nesting_level + 1);
		(void)push_total;
		EMU86_EMULATE_PUSH(sp - (push_total + alloc_size), push_total + alloc_size);
#if EMU86_EMULATE_CONFIG_WANT_ENTER
		EMU86_WRITE_USER_MEMORY(sp - push_total, push_total);
		sp -= 4;
		frameTemp = EMU86_GETESP() - 4;
		EMU86_MEMWRITEL(sp, pbp);
#else /* EMU86_EMULATE_CONFIG_WANT_ENTER */
		EMU86_UNSUPPORTED_MEMACCESS(sp - push_total, push_total, false, true);
#endif /* !EMU86_EMULATE_CONFIG_WANT_ENTER */
	})
	if (nesting_level != 0) {
		if (nesting_level > 1) {
			byte_t *pbp_addr;
			pbp_addr = EMU86_SEGADDR(EMU86_GETSSBASE(), pbp);
#if !EMU86_EMULATE_CONFIG_WANT_ENTER
			{
				size_t access_total;
				if (IS_16BIT()) {
					access_total = (size_t)(nesting_level - 1) * 2;
				} else IF_64BIT(IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
					access_total = (size_t)(nesting_level - 1) * 8;
				} IF_16BIT_OR_32BIT(else)) IF_16BIT_OR_32BIT({
					access_total = (size_t)(nesting_level - 1) * 4;
				});
				EMU86_UNSUPPORTED_MEMACCESS(pbp_addr - access_total, access_total, true, false);
			}
#else /* !EMU86_EMULATE_CONFIG_WANT_ENTER */
#if EMU86_EMULATE_CONFIG_CHECKUSER
			/* Validate the memory region from which data will be copied.
			 * NOTE: The destination  area was  already validated  above! */
			if (EMU86_ISUSER()) {
				size_t access_total;
				if (IS_16BIT()) {
					access_total = (size_t)(nesting_level - 1) * 2;
				} else IF_64BIT(IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
					access_total = (size_t)(nesting_level - 1) * 8;
				} IF_16BIT_OR_32BIT(else)) IF_16BIT_OR_32BIT({
					access_total = (size_t)(nesting_level - 1) * 4;
				});
				(void)access_total;
				EMU86_VALIDATE_READABLE(pbp_addr - access_total, access_total);
			}
#endif /* EMU86_EMULATE_CONFIG_CHECKUSER */
			{
				u8 i;
				for (i = 1; i < nesting_level; ++i) {
					if (IS_16BIT()) {
						u16 temp;
						pbp_addr -= 2;
						sp -= 2;
						temp = EMU86_MEMREADW(pbp_addr);
						EMU86_MEMWRITEW(sp, temp);
					} else IF_64BIT(IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
						u64 temp;
						pbp_addr -= 8;
						sp -= 8;
						temp = EMU86_MEMREADQ(pbp_addr);
						EMU86_MEMWRITEQ(sp, temp);
					} IF_16BIT_OR_32BIT(else)) IF_16BIT_OR_32BIT({
						u32 temp;
						pbp_addr -= 4;
						sp -= 4;
						temp = EMU86_MEMREADL(pbp_addr);
						EMU86_MEMWRITEL(sp, temp);
					})
				}
			}
#endif /* EMU86_EMULATE_CONFIG_WANT_ENTER */
		}
#if EMU86_EMULATE_CONFIG_WANT_ENTER
		if (IS_16BIT()) {
			sp -= 2;
			EMU86_MEMWRITEW(sp, frameTemp);
		} else IF_64BIT(IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
			sp -= 8;
			EMU86_MEMWRITEQ(sp, frameTemp);
		} IF_16BIT_OR_32BIT(else)) IF_16BIT_OR_32BIT({
			sp -= 4;
			EMU86_MEMWRITEL(sp, frameTemp);
		})
#endif /* EMU86_EMULATE_CONFIG_WANT_ENTER */
	}
#if EMU86_EMULATE_CONFIG_WANT_ENTER
	if (IS_16BIT()) {
		/* The upper 16 bits of RBP/EBP don't get modified by this! */
#if LIBEMU86_CONFIG_WANT_64BIT
		EMU86_SETRBP((EMU86_GETRBP() & ~0xffff) |
		             (frameTemp & 0xffff));
#elif LIBEMU86_CONFIG_WANT_32BIT
		EMU86_SETEBP((EMU86_GETEBP() & ~0xffff) |
		             (frameTemp & 0xffff));
#else /* ... */
		EMU86_SETBP(frameTemp);
#endif /* !... */
	} else IF_64BIT(IF_16BIT_OR_32BIT(if (EMU86_F_IS64(op_flags))) {
		EMU86_SETRBP(frameTemp);
	} IF_16BIT_OR_32BIT(else)) IF_16BIT_OR_32BIT({
		EMU86_SETEBP(frameTemp);
	})
	sp -= alloc_size;
	EMU86_SETSTACKPTR(sp);
	goto done;
#else /* EMU86_EMULATE_CONFIG_WANT_ENTER */
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* !EMU86_EMULATE_CONFIG_WANT_ENTER */
}
#endif /* EMU86_EMULATE_CONFIG_WANT_ENTER || (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_UNSUPPORTED_MEMACCESS_IS_NOOP) */


}
EMU86_INTELLISENSE_END
