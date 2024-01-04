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
#ifndef GUARD_LIBDL_ARCH_ARM_RT_S
#define GUARD_LIBDL_ARCH_ARM_RT_S 1
#define __ASSEMBLER__ 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include "../../builtin.h"
/**/

INTERN(dl_require_global)

#define DEFINE_GLOBAL_SYMBOL_IMPORT(name) \
	.section .rodata.str.1;               \
	991: .asciz #name;                    \
	.section .text;                       \
	INTERN_FUNCTION(name);                \
		b      .; /* TODO */              \
	END(name)
BUILTIN_GLOBALS_ENUMERATE(DEFINE_GLOBAL_SYMBOL_IMPORT)
#undef DEFINE_GLOBAL_SYMBOL_IMPORT


.section .text
INTERN_FUNCTION(libdl___tls_get_addr)
	b      . /* TODO */
END(libdl___tls_get_addr)
DEFINE_PUBLIC_ALIAS(__tls_get_addr, libdl___tls_get_addr)


.section .text
	/* The heart-piece of lazy symbol relocations:
	 *   - This function is called by user-code the first time an R_386_JMP_SLOT
	 *     relocation is accessed,  at which point  the relocation is  resolved.
	 *   - See the explanation about `PLTGOT' below for how this actually works.
	 */
INTERN_FUNCTION(dl_load_lazy_relocation)
	b      . /* TODO */
END(dl_load_lazy_relocation)

#endif /* !GUARD_LIBDL_ARCH_ARM_RT_S */
