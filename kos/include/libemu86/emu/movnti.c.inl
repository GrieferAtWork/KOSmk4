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

EMU86_INTELLISENSE_BEGIN(movnti) {


#if EMU86_EMULATE_CONFIG_WANT_MOVNTI
	/*         0F C3 /r     MOVNTI m32, r32     Move doubleword from r32 to m32 using non-temporal hint.
	 * REX.W + 0F C3 /r     MOVNTI m64, r64     Move quadword from r64 to m64 using non-temporal hint. */
case EMU86_OPCODE_ENCODE(0x0fc3): {
	byte_t *addr;
	MODRM_DECODE_MEMONLY();
#define NEED_return_expected_memory_modrm
	addr = MODRM_MEMADDR();
	/* MOVNTI  has weaker instruction ordering when compared to regular MOV, meaning
	 * that the processor is allowed to re-order MOVNTI with other instructions that
	 * may access memory.
	 * As such, it is safe to simply emulate MOVNTI via a regular MOV. */
	IF_64BIT(if (IS_64BIT()) {
		u64 value;
		value = MODRM_GETREGQ();
		COMPILER_WRITE_BARRIER();
		EMU86_MEMWRITEQ(addr, value);
		COMPILER_WRITE_BARRIER();
	} else) {
		u32 value;
		value = MODRM_GETREGL();
		COMPILER_WRITE_BARRIER();
		EMU86_MEMWRITEL(addr, value);
		COMPILER_WRITE_BARRIER();
	}
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR
case EMU86_OPCODE_ENCODE(0x0fc3):
	goto notsup_modrm_setlq_memonly;
#define NEED_notsup_modrm_setlq_memonly
#endif /* ... */


}
EMU86_INTELLISENSE_END
