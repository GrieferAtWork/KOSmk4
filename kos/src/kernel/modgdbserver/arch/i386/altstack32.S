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

#include <kernel/compiler.h>

#include <kernel/paging.h> /* KERNEL_DEBUG_STACKSIZE */

#include <cfi.h>

.section .bss
	.align 4
INTERN_OBJECT(GDB_Main_alternate_stack)
	.skip KERNEL_DEBUG_STACKSIZE
END(GDB_Main_alternate_stack)

.section .text
/* Wrapper for `GDB_Main()' that will invoke said function
 * using   an   alternate,  statically   allocated  stack. */
/* INTDEF void NOTHROW(FCALL GDB_MainWithAlternateStack)(void); */
INTERN_FUNCTION(GDB_MainWithAlternateStack)
	.cfi_startproc
	pushl_cfi_r %ebp
	movl   %esp, %ebp
	.cfi_def_cfa_register %ebp

	/* Load the alternate stack and call the regular GDB_Main() function. */
	movl   $(GDB_Main_alternate_stack + KERNEL_DEBUG_STACKSIZE), %esp
	EXTERN(GDB_Main)
	call   GDB_Main

	leave
	.cfi_restore %ebp
	.cfi_adjust_cfa_offset -4
	.cfi_def_cfa_register %esp
	ret
	.cfi_endproc
END(GDB_MainWithAlternateStack)
