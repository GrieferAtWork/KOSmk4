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

EMU86_INTELLISENSE_BEGIN(flush) {

#if !EMU86_EMULATE_CONFIG_ONLY_MEMORY
#if EMU86_EMULATE_CONFIG_WANT_INVD
case EMU86_OPCODE_ENCODE(0x0f08): {
	/* 0F 08     INVD     Flush internal caches; initiate flushing of external caches. */
#ifdef EMU86_EMULATE_INVD
	EMU86_EMULATE_INVD();
#endif /* EMU86_EMULATE_INVD */
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x0f08):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_WBINVD
case EMU86_OPCODE_ENCODE(0x0f09): {
	/* 0F 09     WBINVD     Write back and flush Internal caches; initiate writing-back and flushing of external caches. */
#ifdef EMU86_EMULATE_WBINVD
	EMU86_EMULATE_WBINVD();
#endif /* EMU86_EMULATE_WBINVD */
	goto done;
}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
case EMU86_OPCODE_ENCODE(0x0f09):
	goto return_unsupported_instruction;
#define NEED_return_unsupported_instruction
#endif /* ... */


#if ((EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || \
     EMU86_EMULATE_CONFIG_WANT_PREFETCHW)
case EMU86_OPCODE_ENCODE(0x0f0d): {
	MODRM_DECODE();
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_WANT_PREFETCHW
	case 1: {
		/* 0F 0D /1     PREFETCHW m8     Move data from m8 closer to the processor in anticipation of a write. */
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
#ifdef EMU86_EMULATE_WPREFETCHW
		EMU86_EMULATE_WPREFETCHW(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_WPREFETCHW */
		goto done;
	}
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
	case 1:
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */

	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	break;
}
#endif /* EMU86_EMULATE_CONFIG_CHECKERROR || EMU86_EMULATE_CONFIG_WANT_PREFETCHW */


#if ((EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || \
     EMU86_EMULATE_CONFIG_WANT_PREFETCHNTA || EMU86_EMULATE_CONFIG_WANT_PREFETCH0 ||        \
     EMU86_EMULATE_CONFIG_WANT_PREFETCH1 || EMU86_EMULATE_CONFIG_WANT_PREFETCH2)
case EMU86_OPCODE_ENCODE(0x0f18): {
	/* 0F 18 /0     PREFETCHNTA m8     Move data from m8 closer to the processor using NTA hint.
	 * 0F 18 /1     PREFETCHT0 m8      Move data from m8 closer to the processor using T0 hint.
	 * 0F 18 /2     PREFETCHT1 m8      Move data from m8 closer to the processor using T1 hint.
	 * 0F 18 /3     PREFETCHT2 m8      Move data from m8 closer to the processor using T2 hint. */
	MODRM_DECODE();
	if (!EMU86_MODRM_ISMEM(modrm.mi_type))
		goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_WANT_PREFETCHNTA
	case 0:
#ifdef EMU86_EMULATE_PREFETCHNTA
		EMU86_EMULATE_PREFETCHNTA(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_PREFETCHNTA */
		goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
	case 0:
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_PREFETCH0
	case 1:
#ifdef EMU86_EMULATE_PREFETCH0
		EMU86_EMULATE_PREFETCH0(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_PREFETCH0 */
		goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
	case 1:
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_PREFETCH1
	case 2:
#ifdef EMU86_EMULATE_PREFETCH1
		EMU86_EMULATE_PREFETCH1(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_PREFETCH1 */
		goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
	case 2:
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */


#if EMU86_EMULATE_CONFIG_WANT_PREFETCH2
	case 3:
#ifdef EMU86_EMULATE_PREFETCH2
		EMU86_EMULATE_PREFETCH2(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_PREFETCH2 */
		goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
	case 3:
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */

	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	break;
}
#endif /* ((EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || ... */


#if (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_CLDEMOTE
case EMU86_OPCODE_ENCODE(0x0f1c): {
	MODRM_DECODE();
	if (!EMU86_MODRM_ISMEM(modrm.mi_type))
		goto return_expected_memory_modrm_rmreg;
#define NEED_return_expected_memory_modrm_rmreg
	switch (modrm.mi_reg) {

#if EMU86_EMULATE_CONFIG_WANT_CLDEMOTE
	case 0:
		/* NP 0F 1C /0     CLDEMOTE m8     Hint to hardware to move the cache line containing m8 to a more
		 *                                 distant level  of the  cache without  writing back  to  memory. */
#ifdef EMU86_EMULATE_CLDEMOTE
		EMU86_EMULATE_CLDEMOTE(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_CLDEMOTE */
		goto done;
#elif EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC
	case 0:
		goto return_unsupported_instruction_rmreg;
#define NEED_return_unsupported_instruction_rmreg
#endif /* ... */

	default:
		goto return_unknown_instruction_rmreg;
#define NEED_return_unknown_instruction_rmreg
	}
	break;
}
#endif /* (EMU86_EMULATE_CONFIG_CHECKERROR && !EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC) || EMU86_EMULATE_CONFIG_WANT_CLDEMOTE */
#endif /* !EMU86_EMULATE_CONFIG_ONLY_MEMORY */

}
EMU86_INTELLISENSE_END
