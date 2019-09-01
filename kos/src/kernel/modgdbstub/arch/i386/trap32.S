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

#include <kernel/compiler.h>
#include <kos/kernel/paging.h> /* KERNEL_DEBUG_STACKSIZE */
#include <asm/cfi.h>

.section .text
INTERN_FUNCTION(GDB_TrapWithState)
	.cfi_startproc
	/* INTERN void *
	 * NOTHROW(FCALL GDB_TrapWithState)(void *__restrict state, syscall_ulong_t trapno,
	 *                                  char const *trap_regs, unsigned int encoding); */
	pushl_cfi_r %ebp
	movl   %esp, %ebp
	.cfi_def_cfa_register %ebp
	INTERN(GDB_TrapStack)
	movl   $(GDB_TrapStack + KERNEL_DEBUG_STACKSIZE), %esp

	pushl  12(%ebp) /* unsigned int encoding */
	pushl  8(%ebp)  /* char const *trap_regs */
	INTERN(GDB_TrapWithStateImpl)
	call   GDB_TrapWithStateImpl

	leave
	.cfi_restore %ebp
	.cfi_def_cfa %esp, 4
	ret    $8
	.cfi_endproc
END(GDB_TrapWithState)

