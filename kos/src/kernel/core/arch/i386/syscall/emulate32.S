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

#include <kernel/except.h>

#include <asm/cfi.h>
#include <asm/unistd.h>
#include <kos/kernel/cpu-state-asm32.h>
#include <kos/kernel/cpu-state.h>

#include <errno.h>

#include <librpc/rpc.h>


#define TEST_DOUBLE_WIDE(sysno_reg, tempreg_l, tempreg_b, segment_prefix)  \
	cmpl   $(__NR_syscall0_max), sysno_reg;                                \
	ja     1234f;                                                          \
	movl   sysno_reg, tempreg_l;                                           \
	shrl   $1, tempreg_l;                                                  \
	EXTERN(kernel_syscall0_regcnt);                                        \
	movb   segment_prefix kernel_syscall0_regcnt(,tempreg_l,1), tempreg_b; \
	jmp    1235f;                                                          \
1234:                                                                      \
	leal   -__NR_syscall1_min(sysno_reg), tempreg_l;                       \
	shrl   $1, tempreg_l;                                                  \
	EXTERN(kernel_syscall1_regcnt);                                        \
	movb   segment_prefix kernel_syscall1_regcnt(,tempreg_l,1), tempreg_b; \
1235:                                                                      \
	testl  $1, sysno_reg;                                                  \
	jz     1234f;                                                          \
	shrb   $4, tempreg_b;                                                  \
1234:                                                                      \
	testb  $0x8, tempreg_b;


/* Emulate the execution of a system call.
 * NOTE: `syscall_emulate_r()' is the same as `syscall_emulate()', however
 *       will reset the kernel-space stack to `state', and immediately return
 *       to userspace after the system call has returned (or unwind any exception
 *       that was thrown by the system call, also dealing with the possibility
 *       of RPC function handling, as well as system call restarting) */

/* >> FUNDEF ATTR_NORETURN void FCALL
 * >> syscall_emulate_r(struct icpustate *__restrict state,
 * >>                   struct rpc_syscall_info *__restrict sc_info); */
.section .text
PUBLIC_FUNCTION(syscall_emulate_r)
	.cfi_startproc simple
	EXTERN(syscall_emulate_r_personality)
	.cfi_personality 0, syscall_emulate_r_personality
	.cfi_iret_signal_frame
	.cfi_def_cfa  %ecx, OFFSET_ICPUSTATE_IRREGS
	.cfi_restore_iret_ds_or_offset -4
	.cfi_restore_iret_es_or_offset -8
	.cfi_restore_iret_fs_or_offset -12
	ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(OFFSET_ICPUSTATE_GPREGS)
	/* TODO: This is a `jmp 1f; 1:' instruction that is meant to be
	 *       overwritten in order to facilitate system call tracing! */
	.byte 0xe9
	.long 0

	/* Start by copying `sc_info' (%edx) just infront of `state' (%ecx)
	 * Note that that sc_info may already be overlapping with said target
	 * area, meaning that we have to use memmove() semantics copying data
	 * from the top down to the bottom */
	leal   (-4)(%ecx), %edi
	leal   (SIZEOF_RPC_SYSCALL_INFO-4)(%edx), %esi
	movl   $(SIZEOF_RPC_SYSCALL_INFO / 4), %ecx /* It's ok that this clobbers %ecx. - We can just load `%edi+4' once we're done */
	cli    /* Disable interrupts (we're about to do some black voodoo with our stack...) */
	cld    /* Clear direction bit, meaning that movsX now advances downwards */
	rep;   movsl /* memmove((byte_t *)state - SIZEOF_RPC_SYSCALL_INFO, sc_info, SIZEOF_RPC_SYSCALL_INFO); */
	leal   4(%edi), %esp /* Load %esp to point to the start of the copied `sc_info' */
	.cfi_def_cfa  %esp, (SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS)
	sti    /* We can now re-enable interrupt. */
	/* At this point, our stack looks like this:
	 * 0(%esp):                                                 struct rpc_syscall_info sc_info;
	 * SIZEOF_RPC_SYSCALL_INFO(%esp):                           struct icpustate state;
	 * SIZEOF_RPC_SYSCALL_INFO + OFFSET_ICPUSTATE_IRREGS(%esp): <END-OF-STACK> */
INTERN_LABEL(__x86_syscall_emulate_r_protect_start):

	/* Figure out which system call is actually being invoked. */
	movl   OFFSET_RPC_SYSCALL_INFO_SYSNO(%esp), %eax

	/* Push system call arguments. */
	pushl_cfi ((1*4)+OFFSET_RPC_SYSCALL_INFO_ARG(5))(%esp)
	pushl_cfi ((2*4)+OFFSET_RPC_SYSCALL_INFO_ARG(4))(%esp)
	pushl_cfi ((3*4)+OFFSET_RPC_SYSCALL_INFO_ARG(3))(%esp)
	pushl_cfi ((4*4)+OFFSET_RPC_SYSCALL_INFO_ARG(2))(%esp)
	pushl_cfi ((5*4)+OFFSET_RPC_SYSCALL_INFO_ARG(1))(%esp)
	pushl_cfi ((6*4)+OFFSET_RPC_SYSCALL_INFO_ARG(0))(%esp)

	cmpl   $(__NR_syscall0_max), %eax
	ja     .Lcall_sysex
	pushl_cfi $.Lnormal_return
	EXTERN(x86_sysroute0_c)
	jmpl   *x86_sysroute0_c(,%eax,4)
	.cfi_adjust_cfa_offset -4
.Lbad_sysno:
	/* %eax is a system call number that doesn't exist. */
	testl  $(RPC_SYSCALL_INFO_FEXCEPT), (6*4)+OFFSET_RPC_SYSCALL_INFO_FLAGS(%esp)
	jz     .Lbad_sysno_ENOSYS

	/* Throw an actual `E_UNKNOWN_SYSTEMCALL' exception! */
	pushl_cfi %eax                                  /* sysno */
	pushl_cfi ((8*4)+OFFSET_RPC_SYSCALL_INFO_FLAGS)(%esp) /* flags */
	pushl_cfi $(8)                                  /* argc */
	pushl_cfi $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)) /* ecode */
	call   error_thrown
	.cfi_adjust_cfa_offset -12


.Lbad_sysno_ENOSYS:
	/* Just return -ENOSYS (no need to go through all the hassle of throwing an exception) */
	movl   $-ENOSYS, %eax
	movl   $-1, %edx
	jmp    .Lnormal_return

.Lcall_sysex:
	cmpl   $(__NR_syscall1_min), %eax
	jb     .Lbad_sysno
	cmpl   $(__NR_syscall1_max), %eax
	ja     .Lbad_sysno
	EXTERN(x86_sysroute1_c)
	calll  *(x86_sysroute1_c - ((__NR_syscall1_min * 4) & 0xffffffff))(,%eax,4)
.Lnormal_return:


INTERN_LABEL(__x86_syscall_emulate_r_protect_end):
	/* Return to user-space. */
	addl   $(SIZEOF_RPC_SYSCALL_INFO), %esp
	.cfi_adjust_cfa_offset -SIZEOF_RPC_SYSCALL_INFO

	/* Check if we must sign-extend the error return value. */
	TEST_DOUBLE_WIDE(%eax, %ecx, %cl, )
	jz     1f
	movl   %edx, OFFSET_GPREGS_EDX(%esp)
1:
	/* Restore GP registers (except for %eax, which holds the syscall return value) */
	popl_cfi_r %edi /* [P] Destination pointer */
	popl_cfi_r %esi /* [P] Source pointer */
	popl_cfi_r %ebp /* [P] Frame base pointer */
	popl_cfi_r %esp /* [P] Stack pointer */
	popl_cfi_r %ebx /* [P] Base register */
	popl_cfi_r %edx /* [C] Data register */
	popl_cfi_r %ecx /* [C] Count register */
	addl   $4, %esp /* [C] Accumulator register */
	.cfi_adjust_cfa_offset -4

	popl_cfi %fs
	.cfi_restore_iret_fs
	popl_cfi %es
	.cfi_restore_iret_es
	popl_cfi %ds
	.cfi_restore_iret_ds
	iret
	.cfi_endproc
END(syscall_emulate_r)


