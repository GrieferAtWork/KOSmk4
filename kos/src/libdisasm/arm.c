/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBDISASM_ARM_C
#define GUARD_LIBDISASM_ARM_C 1
#define DISABLE_BRANCH_PROFILING
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <libdisasm/disassembler.h>
/**/

/* Only compile this file if X86 should be supported as a target */
#if (DISASSEMBLER_TARGET_SUPPORTED(DISASSEMBLER_TARGET_ARM_A32) || \
     DISASSEMBLER_TARGET_SUPPORTED(DISASSEMBLER_TARGET_ARM_T32))
#include "arm.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>
#include <inttypes.h>

DECL_BEGIN

INTERN NONNULL((1)) void CC
libda_single_arm(struct disassembler *__restrict self) {
	/* TODO: Properly disassemble instructions */

	if (DAARM_ISARM(self)) {
		uint32_t opcode;
print_32bit:
		opcode = UNALIGNED_GET32(self->d_pc);
		disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_PREFIX);
		disasm_print(self, ".word", 5);
		disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_SUFFIX);
		disasm_printf(self, " %#.8" PRIx32, opcode);
	} else {
		uint16_t thumb_opcode;
		thumb_opcode = UNALIGNED_GET16(self->d_pc);
		if ((thumb_opcode & 0x1800) != 0x0000)
			goto print_32bit;
		disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_PREFIX);
		disasm_print(self, ".2byte", 5);
		disasm_print_format(self, DISASSEMBLER_FORMAT_PSEUDOOP_SUFFIX);
		disasm_printf(self, " %#.4" PRIx16, thumb_opcode);
	}
}


DECL_END
#endif /* DISASSEMBLER_TARGET_SUPPORTED(arm...) */

#endif /* !GUARD_LIBDISASM_ARM_C */
