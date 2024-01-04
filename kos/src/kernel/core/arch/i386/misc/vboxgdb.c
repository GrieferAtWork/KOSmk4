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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB_C 1

#include <kernel/compiler.h>

#include <kernel/vboxgdb.h>

#ifdef CONFIG_HAVE_KERNEL_VBOXGDB
#include <kernel/types.h>

#include <hybrid/host.h>

#include <asm/intrin.h>
#include <asm/redirect.h>
#include <sys/io.h>

#include <string.h>

DECL_BEGIN

INTDEF byte_t x86_idt_debugtrap[];
INTDEF byte_t x86_idt_breakpoint[];
INTDEF byte_t _vboxgdb_debugtrap[];
INTDEF byte_t _vboxgdb_breakpoint[];
DATDEF byte_t _vboxgdb_trap[] ASMNAME("vboxgdb_trap");

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_vboxgdb)(void) {
	/* Inject the int1 and int3 handler. (s.a. vboxgdb:vmResume) */
	__arch_redirect(x86_idt_debugtrap, _vboxgdb_debugtrap);
	__arch_redirect(x86_idt_breakpoint, _vboxgdb_breakpoint);
	_vboxgdb_trap[0] = 0x90; /* nop (overwrite the `0xc3' (`ret') that was written here before now) */
	__flush_instruction_cache();
	COMPILER_WRITE_BARRIER();

	/* Notify vboxgdb that the initial kernel init has completed
	 * by  sending a special control sequence through port:0x504
	 * Afterwards, jump into the vboxgdb step loop to allow  any
	 * attached GDB instance to set initial kernel breakpoints. */
	vboxgdb_trap(FREESTR(VBOXGDB_TRAP_STARTUP));
}


DECL_END

#endif /* CONFIG_HAVE_KERNEL_VBOXGDB */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB_C */
