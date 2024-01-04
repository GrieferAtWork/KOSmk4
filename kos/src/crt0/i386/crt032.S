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
#ifndef GUARD_CRT0_I386_CRT032_S
#define GUARD_CRT0_I386_CRT032_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kos/exec/asm/elf32.h>
#include <kos/exec/peb.h>

/* INTDEF int main(int argc, char *argv[], char *envp[]); */
/* INTDEF ATTR_NORETURN void _start(void); */

.section .text
INTERN_FUNCTION(_start)
	/* The PEB is initialized by the kernel */
	pushl  OFFSET_PROCESS_PEB_ENVP(%ELF_ARCH386_PEB_REGISTER) /* envp */
	pushl  OFFSET_PROCESS_PEB_ARGV(%ELF_ARCH386_PEB_REGISTER) /* argv */
	pushl  OFFSET_PROCESS_PEB_ARGC(%ELF_ARCH386_PEB_REGISTER) /* argc */
	INTERN(main)
	call   main
	movl   %eax, 0(%esp)

	/* %ebx isn't required when we're not generating position-independent code. */
#if defined(__pic__) || defined(__PIC__) || defined(__pie__) || defined(__PIE__)
	/* @PLT requires %ebx to be loaded, so load it now */
	call   1f
1:	popl   %ebx
	addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), %ebx
#endif /* ... */

	EXTERN(exit)
	call   exit@PLT
END(_start)


.section .bss.__dso_handle
INTERN_OBJECT(__dso_handle)
	.long 0
END(__dso_handle)

#endif /* !GUARD_CRT0_I386_CRT032_S */
