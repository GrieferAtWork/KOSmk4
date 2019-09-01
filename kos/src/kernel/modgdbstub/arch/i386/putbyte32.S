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
#include <asm/cfi.h>

.section .text
/* Same as `GDBRemote_PutByte()', but using the current CPU state.
 * This function is mainly intended for use by communications initializers,
 * where it can happen that an already pending byte must be handled without
 * the help of an interrupt. */
INTERN_FUNCTION(GDBRemote_PutByteFromHere)
	.cfi_startproc
	.cfi_signal_frame
	/* INTERN void NOTHROW(FCALL GDBRemote_PutByteFromHere)(byte_t byte); */
	popl_cfi  %eax
	.cfi_register %eip, %eax
	pushfl_cfi
	pushl_cfi %cs
	pushl_cfi %eax
	pushl_cfi %ds
	pushl_cfi %es
	pushl_cfi %fs
	pushal_cfi

	movl   %ecx, %edx /* GDBRemote_PutByte:byte */
	movl   %esp, %ecx /* GDBRemote_PutByte:state */

	INTERN(GDBRemote_PutByte)
	call   GDBRemote_PutByte

	movl   %eax, %esp

	EXTERN(cpu_apply_icpustate_esp)
	jmp    cpu_apply_icpustate_esp
	.cfi_endproc
END(GDBRemote_PutByteFromHere)

