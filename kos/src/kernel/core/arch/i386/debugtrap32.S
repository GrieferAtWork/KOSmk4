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
#include <asm/cpu-flags.h>


.section .xdata
PUBLIC_FUNCTION(kernel_debugtrap)
	/* PUBLIC void FCALL
	 * kernel_debugtrap(struct debugtrap_reason const *reason); */
	.cfi_startproc
	.cfi_signal_frame
	.byte 0xc3 /* ret */
	popl_cfi  %eax
	.cfi_register %eip, %eax
	pushfl_cfi_r
	pushl_cfi_r %cs
	pushl_cfi %eax
	.cfi_rel_offset %eip, 0
	pushl_cfi_r %ds
	pushl_cfi_r %es
	pushl_cfi_r %fs
	pushal_cfi_r
	movl   %ecx, %edx   /* struct debugtrap_reason const *reason */
	movl   %esp, %ecx   /* struct icpustate *state */
	EXTERN(kernel_debugtrap_icpustate)
	call   kernel_debugtrap_icpustate
	nop /* Aid with unwinding */
	.cfi_endproc
END(kernel_debugtrap)


.section .text
INTERN_FUNCTION(driver_invoke_initializer)
	.cfi_startproc
	INTERN(driver_initializer_personality)
	.cfi_personality 0, driver_initializer_personality
	call   *%ecx
	ret
	.cfi_endproc
END(driver_invoke_initializer)




#define CPUSTATE_IS_ICPUSTATE
#define CPUSTATE icpustate
#include "debugtrap32-impl.S"

#define CPUSTATE_IS_SCPUSTATE
#define CPUSTATE scpustate
#include "debugtrap32-impl.S"

#define CPUSTATE ucpustate
#include "debugtrap32-impl.S"

#define CPUSTATE kcpustate
#include "debugtrap32-impl.S"

#define CPUSTATE lcpustate
#include "debugtrap32-impl.S"

#define CPUSTATE fcpustate
#include "debugtrap32-impl.S"

