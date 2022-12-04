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
#ifndef GUARD_LIBUNWIND_ARCH_I386_COMPAT_C_INL
#define GUARD_LIBUNWIND_ARCH_I386_COMPAT_C_INL 1
#define _KOS_SOURCE 1

#include "../../api.h"
/**/

#include <libunwind/arch-register.h>

#if (defined(LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER) || defined(__DEEMON__))
#include <hybrid/compiler.h>

#include <libunwind/cfi.h>
#include <libunwind/cfi/i386.h>
#include <libunwind/cfi/x86_64.h>
#include <libunwind/unwind.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_getreg_compat)(/*struct unwind_getreg_compat_data **/ void const *arg, unwind_regno_t regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unwind_errno_t NOTHROW_NCX(CC libuw_unwind_setreg_compat)(/*struct unwind_setreg_compat_data **/ void *arg, unwind_regno_t regno, void const *__restrict src);

/*[[[deemon
import fs;
import * from deemon;
import * from .....misc.libgen.strendN;
import * from .....misc.libgen.converter;
local macros: {string: int} = Dict();
function loadMacros(m: {string: string}) {
	for (local name, value: m) {
		if (name.startswith("CFI_386_UNWIND_REGISTER_E") || name.startswith("CFI_386_UNWIND_REGISTER_R"))
			name = "CFI_386_UNWIND_REGISTER_P" + name[#"CFI_386_UNWIND_REGISTER_E":];
		if (name.startswith("CFI_X86_64_UNWIND_REGISTER_E") || name.startswith("CFI_X86_64_UNWIND_REGISTER_R"))
			name = "CFI_X86_64_UNWIND_REGISTER_P" + name[#"CFI_X86_64_UNWIND_REGISTER_R":];
		macros[name] = value;
	}
}
loadMacros(enumerateIntegerMacrosFromFile(fs.headof(__FILE__) + "/../../../../include/libunwind/cfi/i386.h"));
loadMacros(enumerateIntegerMacrosFromFile(fs.headof(__FILE__) + "/../../../../include/libunwind/cfi/x86_64.h"));
del macros["CFI_386_UNWIND_GPR_REGISTER_SIZE"];
del macros["CFI_X86_64_UNWIND_GPR_REGISTER_SIZE"];
printArrayDefineMacro("DEFINE_386_to_amd64",
	generateArrayMapping(macros, "CFI_386_UNWIND_REGISTER_", "CFI_X86_64_UNWIND_REGISTER_"));
]]]*/
#define DEFINE_386_to_amd64(name)                                                                                      \
	__UINT8_TYPE__ const name[102] = { 0,   2,   1,   3,   7,   6,   4,   5,   16,  49,  255, 33,  34,  35,  36,  37,  \
	                                   38,  39,  40,  255, 255, 17,  18,  19,  20,  21,  22,  23,  24,  41,  42,  43,  \
	                                   44,  45,  46,  47,  48,  65,  66,  64,  50,  51,  52,  53,  54,  55,  255, 255, \
	                                   62,  63,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
	                                   255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 118, 119, 120, \
	                                   121, 122, 123, 124, 125, 126 }
/*[[[end]]]*/

/* Convert a given `CFI_386_UNWIND_REGISTER_*' register number to `CFI_X86_64_UNWIND_REGISTER_*' */
PRIVATE ATTR_CONST WUNUSED unwind_regno_t
NOTHROW(CC regno_i386_to_amd64)(unwind_regno_t regno) {
	unwind_regno_t result;
	PRIVATE DEFINE_386_to_amd64(i386_to_amd64);
	result = CFI_X86_64_UNWIND_REGISTER_COUNT;
	if likely(regno < lengthof(i386_to_amd64))
		result = i386_to_amd64[regno];
	return result;
}


INTERN NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_getreg_compat)(/*struct unwind_getreg_compat_data **/ void const *arg,
                                           unwind_regno_t regno, void *__restrict dst) {
	unwind_errno_t result;
	struct unwind_getreg_compat_data const *me;
	me     = (struct unwind_getreg_compat_data const *)arg;
	regno  = regno_i386_to_amd64(regno);
	result = (*me->ugcd_getreg)(me->ugcd_arg, regno, dst);
	return result;
}

#if 1
/* Abuse  the fact that getreg/setreg are actually the same here, and
 * the only difference lies in what's the deal with the function that
 * is being called. */
static_assert(offsetof(struct unwind_setreg_compat_data, uscd_setreg) ==
              offsetof(struct unwind_getreg_compat_data, ugcd_getreg));
static_assert(offsetof(struct unwind_setreg_compat_data, uscd_arg) ==
              offsetof(struct unwind_getreg_compat_data, ugcd_arg));
DEFINE_INTERN_ALIAS(libuw_unwind_setreg_compat, libuw_unwind_getreg_compat);
#else
INTERN NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_setreg_compat)(/*struct unwind_setreg_compat_data **/ void *arg,
                                           unwind_regno_t regno, void const *__restrict src) {
	unwind_errno_t result;
	struct unwind_setreg_compat_data const *me;
	me     = (struct unwind_setreg_compat_data const *)arg;
	regno  = regno_i386_to_amd64(regno);
	result = (*me->uscd_setreg)(me->uscd_arg, regno, src);
	return result;
}
#endif


DEFINE_PUBLIC_ALIAS(unwind_getreg_compat, libuw_unwind_getreg_compat);
DEFINE_PUBLIC_ALIAS(unwind_setreg_compat, libuw_unwind_setreg_compat);

DECL_END
#endif /* LIBUNWIND_WANT_COMPAT_REGISTER_WRAPPER */

#endif /* !GUARD_LIBUNWIND_ARCH_I386_COMPAT_C_INL */
