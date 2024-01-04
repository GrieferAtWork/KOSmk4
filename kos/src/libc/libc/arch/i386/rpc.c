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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_RPC_C
#define GUARD_LIBC_LIBC_ARCH_I386_RPC_C 1
#define _KOS_SOURCE 1

#include "../../../api.h"
/**/

#include <hybrid/host.h>

#include <kos/rpc.h>

#include <assert.h>
#include <stddef.h>

#include <libunwind/cfi/i386.h>
#include <libunwind/cfi/x86_64.h>

DECL_BEGIN

/* These offsets are assumed by code in `rpc.S' */
static_assert(offsetof(struct rpc_context, rc_context) == 0 * __SIZEOF_POINTER__);
static_assert(offsetof(struct rpc_context, rc_state) == 1 * __SIZEOF_POINTER__);
static_assert(offsetof(struct rpc_context, rc_scinfo) == 2 * __SIZEOF_POINTER__);


/* Restorer wrapper function for `rpc_exec_program' and `rpc_interrupt_program' */
INTDEF void ASMCALL libc_x86_rpc_restorer(void);



PRIVATE ATTR_SECTION(".data.crt.sched.rpc") byte_t
rpc_exec_program[] = {
/*[[[rpc{arch='x86'}
	push   %Psp  #  Save original %Psp

	# Save registers by pushing a `struct ucpustate'
	sp.pushP %Pip
	sp.pushP %Pflags
#ifndef __x86_64__
	sp.pushP %ss
	sp.pushP %cs
	sp.pushP %ds
	sp.pushP %es
	sp.pushP %fs
	sp.pushP %gs
#endif // !__x86_64__
	# `struct gpregs'
	sp.pushP %Pax     # gp_rax: [C] Accumulator register
	sp.pushP %Pcx     # gp_rcx: [C] Count register
	sp.pushP %Pdx     # gp_rdx: [C] Data register
	sp.pushP %Pbx     # gp_rbx: [P] Base register
	sp.pushP pop      # gp_rsp: [P] Stack pointer
	sp.pushP %Pbp     # gp_rbp: [P] Frame base pointer
	sp.pushP %Psi     # gp_rsi: [C] Source pointer
	sp.pushP %Pdi     # gp_rdi: [C] Destination pointer
#ifdef __x86_64__
	sp.pushP %r8      # gp_r8:  [C] General purpose register #8
	sp.pushP %r9      # gp_r9:  [C] General purpose register #9
	sp.pushP %r10     # gp_r10: [C] General purpose register #10
	sp.pushP %r11     # gp_r11: [C] General purpose register #11
	sp.pushP %r12     # gp_r12: [P] General purpose register #12
	sp.pushP %r13     # gp_r13: [P] General purpose register #13
	sp.pushP %r14     # gp_r14: [P] General purpose register #14
	sp.pushP %r15     # gp_r15: [P] General purpose register #15
	sp.pushP %ss
	sp.pushP %cs
	sp.pushP %fs.base
	sp.pushP %gs.base
	sp.pushP %ds
	sp.pushP %es
	sp.pushP %fs
	sp.pushP %gs
#endif // __x86_64__

	push   %Psp  # Remember the address of the `struct ucpustate'

	# Construct the on-stack `struct rpc_context'
	push_issyscall
	jf     pop, 1f
	sppush_sc_info     # `struct rpc_context::rc_scinfo'
1:	sp.pushP pop       # `struct rpc_context::rc_state'
	sp.pushP *reason   # `struct rpc_context::rc_context'

	# Load arguments for the RPC function that will be invoked
#ifdef __x86_64__
	movq   *param:$1, %rsi  # prpc_exec_callback_t::cookie
	movq   %Psp,      %rdi  # prpc_exec_callback_t::ctx
#else // __x86_64__
	push   %Psp
	sp.pushl *param:$1  # prpc_exec_callback_t::cookie
	sp.pushl pop        # prpc_exec_callback_t::ctx
#endif // !__x86_64__

	# Load the actual address of the RPC function to invoke
	movP   *param:$0, %Pip

	# If the interrupted system call had exceptions enabled,
	# then %Pflags.DF will still be set at this point. However,
	# all user-space C code may assume that DF=0 (since it's
	# not compiled with `-mcld' like kernel-code is).
	#
	# As such, manually mask the DF bit here
	and    ~$EFLAGS_DF, %Pflags

]]]*/
#ifdef __x86_64__
	87,128,146,49,112,114,113,115,5,118,116,117,120,121,122,123,
	124,125,126,127,146,52,146,51,146,58,146,59,146,53,146,50,
	146,54,146,55,87,162,168,1,0,164,5,160,5,165,1,52,
	87,53,165,0,64,144,49,11,255,251,26,16,49
#else /* __x86_64__ */
	84,120,121,146,42,146,41,146,43,146,40,146,44,146,45,112,
	113,114,115,5,117,118,119,84,162,168,1,0,164,5,160,5,
	84,165,1,5,5,165,0,56,89,11,255,251,26,57
#endif /* !__x86_64__ */
/*[[[end]]]*/
	,
	/* Push the address of a custom wrapper to which the RPC program will return */
	RPC_OP_sppush_const,
#ifdef __x86_64__
	0,0,0,0,0,0,0,0,
#else /* __x86_64__ */
	0,0,0,0,
#endif /* !__x86_64__ */
	RPC_OP_ret
};

#define _rpc_exec_program_offsetof_restorer \
	(lengthof(rpc_exec_program) - (1 + sizeof(void *)))
#define _rpc_exec_program_restorer \
	(*(void **)(rpc_exec_program + _rpc_exec_program_offsetof_restorer))


ATTR_SECTION(".text.crt.sched.rpc")
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED void const *
NOTHROW(LIBCCALL libc_get_rpc_exec_program)(void) {
	if (_rpc_exec_program_restorer == NULL)
		_rpc_exec_program_restorer = (void *)&libc_x86_rpc_restorer;
	return rpc_exec_program;
}



PRIVATE ATTR_SECTION(".data.crt.sched.rpc") byte_t
rpc_interrupt_program[] = {
/*[[[rpc{arch='x86'}
	# The system pre-pushed a value `bool should_restart_syscall'
	# prior to executing the RPC program. Since the whole purpose
	# of this RPC-interrupt program is to "interrupt" system calls,
	# there really shouldn't be a scenario where a system call
	# would need to be restarted. However, since libc allows for
	# full control of the `mode' given to `rpc_interrupt(3)', we
	# have to handle the case where system calls _do_ need to be
	# restarted... (possibly due to `RPC_SYSRESTART_RESTART')
	jt     pop, 1f
	ret
1:
	push   %Psp  #  Save original %Psp

	# Save registers by pushing a `struct ucpustate'
	sp.pushP %Pip
	sp.pushP %Pflags
#ifndef __x86_64__
	sp.pushP %ss
	sp.pushP %cs
	sp.pushP %ds
	sp.pushP %es
	sp.pushP %fs
	sp.pushP %gs
#endif // !__x86_64__
	# `struct gpregs'
	sp.pushP %Pax     # gp_rax: [C] Accumulator register
	sp.pushP %Pcx     # gp_rcx: [C] Count register
	sp.pushP %Pdx     # gp_rdx: [C] Data register
	sp.pushP %Pbx     # gp_rbx: [P] Base register
	sp.pushP pop      # gp_rsp: [P] Stack pointer
	sp.pushP %Pbp     # gp_rbp: [P] Frame base pointer
	sp.pushP %Psi     # gp_rsi: [C] Source pointer
	sp.pushP %Pdi     # gp_rdi: [C] Destination pointer
#ifdef __x86_64__
	sp.pushP %r8      # gp_r8:  [C] General purpose register #8
	sp.pushP %r9      # gp_r9:  [C] General purpose register #9
	sp.pushP %r10     # gp_r10: [C] General purpose register #10
	sp.pushP %r11     # gp_r11: [C] General purpose register #11
	sp.pushP %r12     # gp_r12: [P] General purpose register #12
	sp.pushP %r13     # gp_r13: [P] General purpose register #13
	sp.pushP %r14     # gp_r14: [P] General purpose register #14
	sp.pushP %r15     # gp_r15: [P] General purpose register #15
	sp.pushP %ss
	sp.pushP %cs
	sp.pushP %fs.base
	sp.pushP %gs.base
	sp.pushP %ds
	sp.pushP %es
	sp.pushP %fs
	sp.pushP %gs
#endif // __x86_64__

	push   %Psp  # Remember the address of the `struct ucpustate'

	# Construct the on-stack `struct rpc_context'
	sppush_sc_info     # `struct rpc_context::rc_scinfo'
	sp.pushP pop       # `struct rpc_context::rc_state'
	sp.pushP *reason   # `struct rpc_context::rc_context'

	# Since no RPC function gets invoked, no need to load proper arguments.
#ifndef __x86_64__
	sub    $8, %Psp    # Still need to adjust %Psp on i386, though!
#endif // !__x86_64__
]]]*/
#ifdef __x86_64__
	40,1,0,0,87,128,146,49,112,114,113,115,5,118,116,117,
	120,121,122,123,124,125,126,127,146,52,146,51,146,58,146,59,
	146,53,146,50,146,54,146,55,87,164,5,160,5
#else /* __x86_64__ */
	40,1,0,0,84,120,121,146,42,146,41,146,43,146,40,146,
	44,146,45,112,113,114,115,5,117,118,119,84,164,5,160,5,
	84,9,8,28,52
#endif /* !__x86_64__ */
/*[[[end]]]*/
	,

	/* Set `%Pip' to the address of the restorer function. */
#ifdef __x86_64__
	RPC_OP_const8u,
	0,0,0,0,0,0,0,0,
	RPC_OP_popreg0 + CFI_X86_64_UNWIND_REGISTER_RIP,
#else /* __x86_64__ */
	RPC_OP_const4u,
	0,0,0,0,
	RPC_OP_popreg0 + CFI_386_UNWIND_REGISTER_EIP,
#endif /* !__x86_64__ */
	RPC_OP_ret
};

#define _rpc_interrupt_program_offsetof_restorer \
	(lengthof(rpc_interrupt_program) - (2 + sizeof(void *)))
#define _rpc_interrupt_program_restorer \
	(*(void **)(rpc_interrupt_program + _rpc_interrupt_program_offsetof_restorer))



ATTR_SECTION(".text.crt.sched.rpc")
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED void const *
NOTHROW(LIBCCALL libc_get_rpc_interrupt_program)(void) {
	if (_rpc_interrupt_program_restorer == NULL)
		_rpc_interrupt_program_restorer = (void *)&libc_x86_rpc_restorer;
	return rpc_interrupt_program;
}


DECL_END

#endif /* GUARD_LIBC_LIBC_ARCH_I386_RPC_C */
