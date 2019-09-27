/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

#include <hybrid/compiler.h>
#include <kos/process.h>

/* INTDEF int main(int argc, char *argv[], char *envp[]); */
/* INTDEF ATTR_NORETURN void _start(void); */

.section .text
INTERN_FUNCTION(_start)
	/* The PEB is initialized by the kernel */
	pushl  OFFSET_PROCESS_PEB_ENVP(%EXEC_PEB_REGISTER) /* envp */
	pushl  OFFSET_PROCESS_PEB_ARGV(%EXEC_PEB_REGISTER) /* argv */
	pushl  OFFSET_PROCESS_PEB_ARGC(%EXEC_PEB_REGISTER) /* argc */
	INTERN(main)
	call   main
	movl   %eax, 0(%esp)
	EXTERN(exit)
	/* @PLT requires %ebx to be loaded, so load it now */
	call   1f
1:	popl   %ebx
	addl   $(_GLOBAL_OFFSET_TABLE_ - (. - 1b)), %ebx
	call   exit@PLT
END(_start)


.section .bss.__dso_handle
INTERN_OBJECT(__dso_handle)
	.long 0
END(__dso_handle)

