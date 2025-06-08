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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_PERSONALITY_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_PERSONALITY_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-personality.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <cfi.h>
#include <asm/instr/compat.h>
#include <kos/bits/syscall-info.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */


/* Personality function for `syscall_emulate_r' */
.section .text
INTERN_FUNCTION(syscall_emulate_r_personality)
	.cfi_startproc

	/* Check if the exception happened while actually in the process of
	 * servicing the system call.
	 * Technically, there shouldn't  be a chance  of an exception  happening
	 * for another reason, but better be careful and do this check properly,
	 * since otherwise we might use nonsense for `sc_info'.
	 * >> if (kcpustate_getpc(state) <= __x86_syscall_emulate_r_protect_start)
	 * >>     goto .Loutside_protected_area;
	 * >> if (kcpustate_getpc(state) > __x86_syscall_emulate_r_protect_end)
	 * >>     goto .Loutside_protected_area; */
	movP   OFFSET_KCPUSTATE_PIP(%R_fcall1P), %Pax
	EXTERN(__x86_syscall_emulate_r_protect_start)
	cmpP   $(__x86_syscall_emulate_r_protect_start), %Pax
	jbe    .Loutside_protected_area
	EXTERN(__x86_syscall_emulate_r_protect_end)
	cmpP   $(__x86_syscall_emulate_r_protect_end), %Pax
	ja     .Loutside_protected_area

	/* Load cpu state structures from the base of the kernel stack. */
#ifdef __x86_64__
	movP   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_PBX(%R_fcall1P), %R_fcall1P /* struct rpc_syscall_info *sc_info */
#else /* __x86_64__ */
	movP   OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_PDI(%R_fcall1P), %R_fcall1P
	addP   $(SIZEOF_POINTER), %R_fcall1P /* struct rpc_syscall_info *sc_info */
#endif /* !__x86_64__ */
	leaP   SIZEOF_RPC_SYSCALL_INFO(%R_fcall1P), %R_fcall0P
	.cfi_remember_state

	/* Unwind the stack all the way until `sc_info' */
	movP   %R_fcall1P, %Psp
	.cfi_def_cfa %Psp, OFFSET_ICPUSTATE_IRREGS
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(-OFFSET_ICPUSTATE_IRREGS)

	/* With the stack restored and everything set-up, handle the current exception. */
	EXTERN(userexcept_handler)
	call   userexcept_handler

	/* `userexcept_handler()' only returns when the system call should be restarted.
	 * We can easily do this by setting registers and jumping to `syscall_emulate_r' */
	movP   %Psp, %R_fcall1P /* sc_info */
	movP   %Pax, %R_fcall0P /* state (as returned by `userexcept_handler()') */
	jmp    syscall_emulate_r

	.cfi_restore_state
.Loutside_protected_area:
	movP   $(EXCEPT_PERSONALITY_CONTINUE_UNWIND), %Pax
	ret
	.cfi_endproc
END(syscall_emulate_r_personality)




/************************************************************************/
/* Personality functions for restartable interrupt handlers             */
/************************************************************************/
.section .text

#ifdef __x86_64__
#define R_lsdaP r12
#else /* __x86_64__ */
#define R_lsdaP Pdi
#endif /* !__x86_64__ */

/* The following registers are passed (unmodified) to LSDA: %Pbx, %Pbp
 * LSDA   is   passed   via   register:   [i386:'%edi', x86_64:'%r12'] */
	.cfi_startproc
	.cfi_def_cfa %R_fcall0P, OFFSET_ICPUSTATE_IRREGS
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(-OFFSET_ICPUSTATE_IRREGS)
INTERN_FUNCTION(_x86_xintr_userexcept_unwind)
	movP   %R_fcall0P, %Psp /* %R_fcall0P: struct icpustate *st; */
	.cfi_def_cfa_register %Psp
	xorP   %R_fcall1P, %R_fcall1P
	EXTERN(userexcept_handler)
	call   userexcept_handler
	movP   %Pax, %Psp
	jmpP   *%R_lsdaP
END(_x86_xintr_userexcept_unwind)
#ifndef __x86_64__
INTERN_FUNCTION(_x86_xintr3_userexcept_unwind)
	.cfi_def_cfa_register %R_fcall0P
	movP   %R_fcall0P, %Psp /* %R_fcall0P: struct icpustate *st; */
	.cfi_def_cfa_register %Psp
	xorP   %R_fcall1P, %R_fcall1P
	EXTERN(userexcept_handler)
	call   userexcept_handler
	movP   %Pax, %Psp
	pushP_cfi %Pbp
	jmpP   *%R_lsdaP
END(_x86_xintr3_userexcept_unwind)
#endif /* !__x86_64__ */
	.cfi_endproc

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_PERSONALITY_S */
