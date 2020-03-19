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

EMU86_INTELLISENSE_BEGIN(flush) {

case 0x0fae:
	MODRM_DECODE();
	switch (modrm.mi_reg) {

	case 7:
		/* 0F AE /7      CLFLUSH m8      Flushes cache line containing m8 */
#ifndef EMU86_EMULATE_ONLY_MEMORY
		if (!EMU86_MODRM_ISMEM(modrm.mi_type))
			goto return_unknown_instruction;
#endif /* !EMU86_EMULATE_ONLY_MEMORY */
#ifdef EMU86_EMULATE_CLFLUSH
		EMU86_EMULATE_CLFLUSH(MODRM_MEMADDR());
#endif /* EMU86_EMULATE_CLFLUSH */
		break;

	default:
		break;
	}
	goto return_unknown_instruction;

}
EMU86_INTELLISENSE_END
