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
#ifndef GUARD__VERIFY_ARCH_ARM_ASSERT_TYPES_C
#define GUARD__VERIFY_ARCH_ARM_ASSERT_TYPES_C 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#define __WANT_FULL_STRUCT_STAT 1
#ifndef __KERNEL__
#define _FILE_OFFSET_BITS 32
#define _TIME_T_BITS 32
#endif /* !__KERNEL__ */

#include <hybrid/host.h>

#ifdef __x86_64__
#define __kos_statx32_alias64 __kos_statx32_alias64
#define __kos_statx64_alias64 stat64
#else /* __x86_64__ */
#define __kos_statx32_alias64 stat64
#define __kos_statx64_alias64 __kos_statx64_alias64
#endif /* !__x86_64__ */

#include <hybrid/compiler.h>

#include <assert.h>
#include <ieee754.h>
#include <stdalign.h>
#include <stddef.h>

static_assert(sizeof(union ieee754_float) == 4);
static_assert(alignof(union ieee754_float) == 4);
static_assert(sizeof(union ieee754_double) == 8);
static_assert(alignof(union ieee754_double) == 8);
static_assert(sizeof(union ieee854_long_double) == 16);
static_assert(alignof(union ieee854_long_double) == 16);
static_assert(sizeof(union ieee854_float80) == 10);
static_assert(sizeof(((union ieee854_float80 *)0)->ieee) == 10);
static_assert(sizeof(((union ieee854_float80 *)0)->ieee_nan) == 10);

/*[[[deemon
import * from .....misc.libgen.assert_offsetof;
local files = {
	"../../../../include/arm-kos/kos/kernel/bits/cpu-state.h",
};

local include_prefixes = {
	"../../../../include/arm-kos",
	"../../../../include",
};

function genAsserts(f) {
	for (local pfx: include_prefixes) {
		if (f.startswith(pfx)) {
			print "#include <" + f[#pfx:].lstrip("/") + ">";
			goto do_gen_asserts;
		}
	}
	print "#include", repr(f);
do_gen_asserts:
	generateAssertions(f);
	print;
	print;
	print;
	print;
	print;
}


for (local f: files)
	genAsserts(f);

]]]*/
#include <kos/kernel/bits/cpu-state.h>

/* struct ucpustate */
static_assert(offsetof(struct ucpustate, ucs_cpsr) == OFFSET_UCPUSTATE_CPSR);
static_assert(offsetof(struct ucpustate, ucs_lr) == OFFSET_UCPUSTATE_LR);
static_assert(offsetof(struct ucpustate, ucs_pc) == OFFSET_UCPUSTATE_PC);
static_assert(offsetof(struct ucpustate, ucs_r0) == OFFSET_UCPUSTATE_R0);
static_assert(offsetof(struct ucpustate, ucs_r1) == OFFSET_UCPUSTATE_R1);
static_assert(offsetof(struct ucpustate, ucs_r10) == OFFSET_UCPUSTATE_R10);
static_assert(offsetof(struct ucpustate, ucs_r11) == OFFSET_UCPUSTATE_R11);
static_assert(offsetof(struct ucpustate, ucs_r12) == OFFSET_UCPUSTATE_R12);
static_assert(offsetof(struct ucpustate, ucs_r2) == OFFSET_UCPUSTATE_R2);
static_assert(offsetof(struct ucpustate, ucs_r3) == OFFSET_UCPUSTATE_R3);
static_assert(offsetof(struct ucpustate, ucs_r4) == OFFSET_UCPUSTATE_R4);
static_assert(offsetof(struct ucpustate, ucs_r5) == OFFSET_UCPUSTATE_R5);
static_assert(offsetof(struct ucpustate, ucs_r6) == OFFSET_UCPUSTATE_R6);
static_assert(offsetof(struct ucpustate, ucs_r7) == OFFSET_UCPUSTATE_R7);
static_assert(offsetof(struct ucpustate, ucs_r8) == OFFSET_UCPUSTATE_R8);
static_assert(offsetof(struct ucpustate, ucs_r9) == OFFSET_UCPUSTATE_R9);
static_assert(offsetof(struct ucpustate, ucs_sp) == OFFSET_UCPUSTATE_SP);
static_assert(sizeof(struct ucpustate) == SIZEOF_UCPUSTATE);
static_assert(alignof(struct ucpustate) == ALIGNOF_UCPUSTATE);

/* struct lcpustate */
static_assert(offsetof(struct lcpustate, lcs_pc) == OFFSET_LCPUSTATE_PC);
static_assert(offsetof(struct lcpustate, lcs_r10) == OFFSET_LCPUSTATE_R10);
static_assert(offsetof(struct lcpustate, lcs_r11) == OFFSET_LCPUSTATE_R11);
static_assert(offsetof(struct lcpustate, lcs_r4) == OFFSET_LCPUSTATE_R4);
static_assert(offsetof(struct lcpustate, lcs_r5) == OFFSET_LCPUSTATE_R5);
static_assert(offsetof(struct lcpustate, lcs_r6) == OFFSET_LCPUSTATE_R6);
static_assert(offsetof(struct lcpustate, lcs_r7) == OFFSET_LCPUSTATE_R7);
static_assert(offsetof(struct lcpustate, lcs_r8) == OFFSET_LCPUSTATE_R8);
static_assert(offsetof(struct lcpustate, lcs_r9) == OFFSET_LCPUSTATE_R9);
static_assert(offsetof(struct lcpustate, lcs_sp) == OFFSET_LCPUSTATE_SP);
static_assert(sizeof(struct lcpustate) == SIZEOF_LCPUSTATE);
static_assert(alignof(struct lcpustate) == ALIGNOF_LCPUSTATE);

/* struct fcpustate */
/* ... */
//[[[end]]]

#endif /* !GUARD__VERIFY_ARCH_ARM_ASSERT_TYPES_C */
