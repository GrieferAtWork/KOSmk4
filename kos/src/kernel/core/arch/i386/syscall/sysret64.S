/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSRET64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSRET64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall.h>

#include <cfi.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state.h>


/************************************************************************/
/* SYSRET-OPTIMIZED IRET                                                */
/************************************************************************/
.section .text.hot
/* Do the equivalent of `intr_exit', but try to make use of `sysretl' if the register
 * state described by the iret  tail stored at `0(%rsp)' allow  for this to be  done.
 * Note  that  if sysexit  ends  up being  used,  the following  user-space registers
 * will be clobbered (which cannot be prevented):
 *  - %rcx      (Set to OFFSET_IRREGS_RIP(%rsp))
 *  - %r8-%r15  (Undefined, but since these are invisible to 32-bit programs, this shouldn't matter)
 */
PUBLIC_FUNCTION(__x86_32_syscall_iret)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	/* Disable interrupts to prevent any further IRET redirections. */
	cli

	/* sysretl requires that TARGET.%cs == SEGMENT_USER_CODE32_RPL, as
	 * that  is  the effective  %cs that  will  be loaded  by `sysret'
	 * NOTE: If IRET was re-directed, then this check will fail! */
	cmpw   $(SEGMENT_USER_CODE32_RPL), OFFSET_IRREGS_CS(%rsp)
	jne    .Ldo_iret

	/* Load the %rip register into its proper location
	 * Even  if we end up using `iretq'  below, it doesn't matter if we've
	 * clobbered `%ecx' at any point, since we're always allowed to do so.
	 * NOTE: We do a zero-extending move here, which prevents `%rcx' from
	 *       ever becoming a non-canonical  address, thus allowing us  to
	 *       forgo the canon-check that the 64-bit variant must  perform! */
	movzlq OFFSET_IRREGS_RIP(%rsp), %rcx

	/* Confirmed! We can make use of sysret! */
	movq   OFFSET_IRREGS_RFLAGS(%rsp), %r11 /* Load %rflags into %r11 */
	movzlq OFFSET_IRREGS_RSP(%rsp),    %rsp /* Load the user-space stack */

	/* Encode CFI instrumentation for unwinding user-space registers. */
	.cfi_same_value %rsp
	.cfi_register   %rflags, %r11
	.cfi_register   %rip, %rcx
	.cfi_reg_const  %cs, SEGMENT_USER_CODE32_RPL
	.cfi_reg_const  %ss, SEGMENT_USER_DATA32_RPL

	/* Swap %gs.base and do the actual sysret */
	swapgs
	sysretl
	.cfi_endproc
END(__x86_32_syscall_iret)


.section .text.hot
/* Do the equivalent of `intr_exit', but try to make use of `sysretq' if the register
 * state described by the iret  tail stored at `0(%rsp)' allow  for this to be  done.
 * Note  that  if sysexit  ends  up being  used,  the following  user-space registers
 * will be clobbered (which cannot be prevented):
 *  - %rcx      (Set to OFFSET_IRREGS_RIP(%rsp))
 *  - %r11      (Set to OFFSET_IRREGS_RFLAGS(%rsp))
 */
PUBLIC_FUNCTION(__x86_64_syscall_iret)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	/* Disable interrupts to prevent any further IRET redirections. */
	cli

	/* sysretq requires that TARGET.%cs == SEGMENT_USER_CODE64_RPL, as
	 * that  is  the effective  %cs that  will  be loaded  by `sysret'
	 * NOTE: If IRET was re-directed, then this check will fail! */
	cmpw   $(SEGMENT_USER_CODE64_RPL), OFFSET_IRREGS_CS(%rsp)
	jne    .Ldo_iret
	.cfi_remember_state

	/* Load the %rip register into its proper location
	 * Even  if we end up using `iretq'  below, it doesn't matter if we've
	 * clobbered `%rcx' at any point, since we're always allowed to do so. */
	movq   OFFSET_IRREGS_RIP(%rsp), %rcx

	/* Make sure that `%rcx' is a canonical address. - We do this by touching
	 * its pointed-to memory location with a  no-op. if doing this causes  an
	 * exception, then we know that the user-space PC is either:
	 *   - A non-canonical address
	 *   - Not mapped into memory.
	 * In either case, handle this by falling back to doing a regular iret, as
	 * well as discarding the E_SEGFAULT exception.
	 * XXX: This assumes that I never end up adding support for mapping  VIO
	 *      at non-canonical addresses (I had planned this at one point, but
	 *      decided against it because it would add unnecessary overhead  to
	 *      the VM node-tree management). */
.Lsysret64_probe_begin:
	ttest  mask=0, loc=0(%rcx)
.Lsysret64_probe_end:

	/* Confirmed! We can make use of sysret! */
	movq   OFFSET_IRREGS_RFLAGS(%rsp), %r11 /* Load %rflags into %r11 */
	movq   OFFSET_IRREGS_RSP(%rsp),    %rsp /* Load the user-space stack */

	/* Encode CFI instrumentation for unwinding user-space registers. */
	.cfi_same_value %rsp
	.cfi_register   %rflags, %r11
	.cfi_register   %rip, %rcx
	.cfi_reg_const  %cs, SEGMENT_USER_CODE64_RPL
	.cfi_reg_const  %ss, SEGMENT_USER_DATA32_RPL /* Yes! 32-bit data (but that's ok on x86_64) */

	/* Swap %gs.base and do the actual sysret */
	swapgs
	sysretq

	/* Exception handler definitions. */
	EXCEPT_HANDLERS_START
		EXCEPT_HANDLERS_CATCH(E_SEGFAULT_UNMAPPED,
		                      .Lsysret64_probe_begin,
		                      .Lsysret64_probe_end,
		                      .Lsysret64_probe_error)
		EXCEPT_HANDLERS_CATCH(E_SEGFAULT_UNMAPPED,
		                      .Lsysret64_probe_begin2,
		                      .Lsysret64_probe_end2,
		                      .Lsysret64_probe_error)
		EXCEPT_HANDLERS_CATCH(E_WOULDBLOCK,
		                      .Lsysret64_probe_begin,
		                      .Lsysret64_probe_end,
		                      .Lsysret64_probe_wouldblock)
	EXCEPT_HANDLERS_END

.Lsysret64_probe_wouldblock:
	/* Special case: Because the above  code touched  user-space memory  with
	 *               interrupts disabled, there is  a chance that the  system
	 *               call return location was apart of a memory location that
	 *               hadn't yet been loaded into memory.
	 *               When this happens, we get  here and we must handle  this
	 *               case by doing another touch with preemption enabled, and
	 *               then try again. */
	sti
	/* Clear the current exception (else the kernel might panic because
	 * it  would  think  that  we  didn't  nest  exceptions   properly) */
	EXTERN(this_exception_code)
	movq   $(EXCEPT_CODEOF(E_OK)), %gs:this_exception_code
.Lsysret64_probe_begin2:
	ttest  mask=0, loc=0(%rcx)
.Lsysret64_probe_end2:
	jmp    __x86_64_syscall_iret

.Lsysret64_probe_error:
	/* Only handle if the `E_SEGFAULT_CONTEXT_NONCANON' flag was set.
	 * RETHROW()    the   exception   if   that   flag   isn't   set. */
	EXTERN(this_exception_args)
	ttest  mask=E_SEGFAULT_CONTEXT_NONCANON, loc=this_exception_args + 8, seg=%gs
	jnz    .Ldo_iret_clearexcept
	/* RETHROW() the exception. */
	EXTERN(except_rethrow)
	call   except_rethrow
	/* UNREACHABLE */

.Ldo_iret_clearexcept:
	/* Clear the exception before returning to user-space (prevents
	 * problems and potential kernel panics later down the line, as
	 * the next system call might think that exceptions were  being
	 * nested) */
	EXTERN(this_exception_code)
	movq   $(EXCEPT_CODEOF(E_OK)), %gs:this_exception_code

.Ldo_iret:
	.cfi_restore_state
	swapgs_if_user_iret
	iretq
	.cfi_endproc
END(__x86_64_syscall_iret)



#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSRET64_S */
