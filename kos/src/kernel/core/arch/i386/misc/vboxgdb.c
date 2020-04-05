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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB_C 1

#include <kernel/compiler.h>

#ifndef CONFIG_NO_VBOXGDB
#include <hybrid/host.h>
#include <kernel/types.h>

DECL_BEGIN

INTDEF byte_t x86_idt_debugtrap[];
INTDEF byte_t _vboxgdb_debugtrap[];

PRIVATE ATTR_SECTION(".rodata.free") char const
_vboxgdb_startup_seq[] = "%{vboxgdb:startup}\n";

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_vboxgdb)(void) {
	__register uintptr_t pcx, pdx, psi;
	/* Inject the int1 step handler. (s.a. vboxgdb:vmSingleStep) */
	x86_idt_debugtrap[0]            = 0xe9; /* jmp32 */
	*(s32 *)(x86_idt_debugtrap + 1) = (s32)((intptr_t)((uintptr_t)_vboxgdb_debugtrap) -
	                                        (intptr_t)((uintptr_t)x86_idt_debugtrap + 5));
	COMPILER_WRITE_BARRIER();
	/* Notify vboxgdb that the initial kernel init has completed
	 * by sending a special control sequence through port:0x504
	 * Afterwards, jump into the vboxgdb step loop to allow any
	 * attached GDB instance to set initial kernel breakpoints. */
	__asm__ __volatile__(""
#ifdef __x86_64__
	                     "movq   %%ss, %%rax\t\n"
	                     "pushq  %%rax\t\n"   /* IRET.SS */
	                     "leaq   8(%%rsp), %%rax\t\n"
	                     "pushq  %%rax\t\n"   /* IRET.RSP */
	                     "pushfq\t\n"         /* IRET.RFLAGS */
	                     "movq   %%cs, %%rax\t\n"
	                     "pushq  %%rax\t\n"   /* IRET.CS */
	                     "pushq  $991f\t\n"   /* IRET.RIP */
#else /* __x86_64__ */
	                     "pushfl\t\n"         /* IRET.EFLAGS */
	                     "pushl  %%cs\t\n"    /* IRET.CS */
	                     "pushl  $991f\t\n"   /* IRET.EIP */
#endif /* !__x86_64__ */
	                     "rep;   outsb\t\n"
	                     ".extern _vboxgdb_steploop\t\n"
	                     "jmp    _vboxgdb_steploop\t\n"
	                     "991:"
	                     : "=c" (pcx)
	                     , "=d" (pdx)
	                     , "=S" (psi)
	                     : "0" (COMPILER_STRLEN(_vboxgdb_startup_seq))
	                     , "1" (0x504)
	                     , "2" (_vboxgdb_startup_seq)
	                     : "memory"
	                     , "cc"
#ifdef __x86_64__
	                     , "%rax"
#endif /* __x86_64__ */
	                     );
}


DECL_END

#endif /* !CONFIG_NO_VBOXGDB */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_VBOXGDB_C */
