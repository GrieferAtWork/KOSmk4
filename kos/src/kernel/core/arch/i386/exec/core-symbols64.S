/*[[[magic
local d = import("deemon");
local f = step.toolchain.config.BUILD_PATH + "/kernel-symtab.S";
(try d.File.open(f, "wronly,creat,excl") catch (...) none)
	<< "#define NO_SYMTAB\n";
options.setdefault("COMPILE.macros", d.Dict(()))["SYMTAB"] = repr("../../../../../../../" + f);
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_EXEC_CORE_SYMBOLS64_S
#define GUARD_KERNEL_CORE_ARCH_I386_EXEC_CORE_SYMBOLS64_S 1

#include SYMTAB

#ifdef NO_SYMTAB
.section .rodata.kernel_symtab
.global kernel_symbol_table
.type kernel_symbol_table, "object"
kernel_symbol_table:
	.quad 0
	/* Symbol table */
	.quad 0
	.quad 0
	.quad 0
	.quad 0
.size kernel_symbol_table, 40
.section .rodata.kernel_strtab
#endif /* NO_SYMTAB */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_EXEC_CORE_SYMBOLS64_S */
