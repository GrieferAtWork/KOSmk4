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
#ifndef GUARD_CRT0_I386_CRT064_S
#define GUARD_CRT0_I386_CRT064_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kos/exec/asm/elf64.h>
#include <kos/exec/peb.h>

/* INTDEF int main(int argc, char *argv[], char *envp[]); */
/* INTDEF ATTR_NORETURN void _start(void); */

.section .text
INTERN_FUNCTION(_start)
	/* The PEB is initialized by the kernel */
	movq   OFFSET_PROCESS_PEB_ARGC(%ELF_ARCHX86_64_PEB_REGISTER), %rdi /* argc */
	movq   OFFSET_PROCESS_PEB_ARGV(%ELF_ARCHX86_64_PEB_REGISTER), %rsi /* argv */
	movq   OFFSET_PROCESS_PEB_ENVP(%ELF_ARCHX86_64_PEB_REGISTER), %rdx /* envp */
	INTERN(main)
	call   main
	movq   %rax, %rdi
	EXTERN(exit)
	call   exit@PLT
END(_start)


.section .bss.__dso_handle
INTERN_OBJECT(__dso_handle)
	.quad 0
END(__dso_handle)

#endif /* !GUARD_CRT0_I386_CRT064_S */
