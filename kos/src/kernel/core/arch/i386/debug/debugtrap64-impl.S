/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#include <kernel/compiler.h>

#include <cfi.h>
#include <asm/cpu-flags.h>


.section .xdata
/* struct CPUSTATE *FCALL kernel_debugtrap_r_CPUSTATE(struct CPUSTATE *state,
 *                                                    struct debugtrap_reason const *reason); */
PUBLIC_FUNCTION(PP_CAT2(kernel_debugtrap_r_,CPUSTATE))
	.cfi_startproc
	.byte 0xe9       /* jmp 1f; 1: */
INTERN_BEGIN(PP_CAT3(__x86_kernel_debugtrap_r_,CPUSTATE,_jmp_offset))
	.long 0x00000000
END(PP_CAT3(__x86_kernel_debugtrap_r_,CPUSTATE,_jmp_offset))
	movq  %rdi, %rax
	ret
	.cfi_endproc
END(PP_CAT2(kernel_debugtrap_r_,CPUSTATE))



.section .xdata
/* ATTR_NORETURN void FCALL trigger_debugtrap_CPUSTATE(struct CPUSTATE *state,
 *                                                     struct debugtrap_reason const *reason); */
INTERN_FUNCTION(PP_CAT2(trigger_debugtrap_,CPUSTATE))
	.cfi_startproc
	.byte  0xe8        /* call PP_CAT2(kernel_debugtrap_r_,CPUSTATE) */
INTERN_BEGIN(PP_CAT3(__x86_trigger_debugtrap_,CPUSTATE,_call_offset))
	.reloc ., R_X86_64_PC32, PP_CAT2(kernel_debugtrap_r_,CPUSTATE)
	.long  -4
END(PP_CAT3(__x86_trigger_debugtrap_,CPUSTATE,_call_offset))
#if defined(CPUSTATE_IS_ICPUSTATE) || defined(CPUSTATE_IS_SCPUSTATE)
	movq   %rax, %rsp
	EXTERN(PP_CAT3(cpu_apply_,CPUSTATE,_rsp))
	jmp    PP_CAT3(cpu_apply_,CPUSTATE,_rsp)
#else /* CPUSTATE_IS_ICPUSTATE || CPUSTATE_IS_SCPUSTATE */
	movq   %rax, %rdi
	EXTERN(PP_CAT2(cpu_apply_,CPUSTATE))
	jmp    PP_CAT2(cpu_apply_,CPUSTATE)
#endif /* !CPUSTATE_IS_ICPUSTATE && !CPUSTATE_IS_SCPUSTATE */
	.cfi_endproc
END(PP_CAT2(trigger_debugtrap_,CPUSTATE))



#undef CPUSTATE
#undef CPUSTATE_IS_SCPUSTATE
#undef CPUSTATE_IS_ICPUSTATE
