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
#ifndef GUARD_LIBC_LIBC_ARCH_ARM_RPC_C
#define GUARD_LIBC_LIBC_ARCH_ARM_RPC_C 1
#define _KOS_SOURCE 1

#include "../../../api.h"
/**/

#include <hybrid/host.h>

#include <kos/rpc.h>

#include <assert.h>
#include <stddef.h>

#include <libunwind/cfi/arm.h>

DECL_BEGIN

/* These offsets are assumed by code in `rpc.S' */
static_assert(offsetof(struct rpc_context, rc_context) == 0 * __SIZEOF_POINTER__);
static_assert(offsetof(struct rpc_context, rc_state) == 1 * __SIZEOF_POINTER__);
static_assert(offsetof(struct rpc_context, rc_scinfo) == 2 * __SIZEOF_POINTER__);


/* Restorer wrapper function for `rpc_exec_program' and `rpc_interrupt_program' */
INTDEF void ASMCALL libc_arm_rpc_restorer(void);


PRIVATE ATTR_SECTION(".data.crt.sched.rpc") byte_t
rpc_exec_program[] = {
/*[[[rpc{arch='arm'}
	push   %sp  #  Save original %sp

	# Save registers by pushing a `struct ucpustate'
	sp.pushl %cpsr
	sp.pushl %pc
	sp.pushl %lr
	sp.pushl pop    # sp
	sp.pushl %r12
	sp.pushl %r11
	sp.pushl %r10
	sp.pushl %r9
	sp.pushl %r8
	sp.pushl %r7
	sp.pushl %r6
	sp.pushl %r5
	sp.pushl %r4
	sp.pushl %r3
	sp.pushl %r2
	sp.pushl %r1
	sp.pushl %r0

]]]*/
	93,146,128,1,127,126,5,124,123,122,121,120,119,118,117,116,
	115,114,113,112
/*[[[end]]]*/
	,
	/* Push the address of a custom wrapper to which the RPC program will return */
	RPC_OP_const4u,
	0,0,0,0,
	RPC_OP_popreg0 + CFI_ARM_UNWIND_REGISTER_LR,
	RPC_OP_ret
};

#define _rpc_exec_program_offsetof_restorer \
	(lengthof(rpc_exec_program) - (2 + sizeof(void *)))
#define _rpc_exec_program_restorer \
	(*(void **)(rpc_exec_program + _rpc_exec_program_offsetof_restorer))


ATTR_SECTION(".text.crt.sched.rpc")
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED void const *LIBCCALL
libc_get_rpc_exec_program(void) {
	if (_rpc_exec_program_restorer == NULL)
		_rpc_exec_program_restorer = (void *)&libc_arm_rpc_restorer;
	return rpc_exec_program;
}



PRIVATE ATTR_SECTION(".data.crt.sched.rpc") byte_t
rpc_interrupt_program[] = {
/*[[[rpc{arch='arm'}
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
	push   %sp  #  Save original %sp

	# Save registers by pushing a `struct ucpustate'
	sp.pushl %cpsr
	sp.pushl %pc
	sp.pushl %lr
	sp.pushl pop    # sp
	sp.pushl %r12
	sp.pushl %r11
	sp.pushl %r10
	sp.pushl %r9
	sp.pushl %r8
	sp.pushl %r7
	sp.pushl %r6
	sp.pushl %r5
	sp.pushl %r4
	sp.pushl %r3
	sp.pushl %r2
	sp.pushl %r1
	sp.pushl %r0

	push   %sp  # Remember the address of the `struct ucpustate'

	# Construct the on-stack `struct rpc_context'
	sppush_sc_info     # `struct rpc_context::rc_scinfo'
	sp.pushP pop       # `struct rpc_context::rc_state'
	sp.pushP *reason   # `struct rpc_context::rc_context'

	# Since no RPC function gets invoked, no need to load proper arguments.
]]]*/
	40,1,0,0,93,146,128,1,127,126,5,124,123,122,121,120,
	119,118,117,116,115,114,113,112,93,164,5,160,5
/*[[[end]]]*/
	,

	/* Set `%Pip' to the address of the restorer function. */
	RPC_OP_const4u,
	0,0,0,0,
	RPC_OP_popreg0 + CFI_ARM_UNWIND_REGISTER_PC,
	RPC_OP_ret
};

#define _rpc_interrupt_program_offsetof_restorer \
	(lengthof(rpc_interrupt_program) - (2 + sizeof(void *)))
#define _rpc_interrupt_program_restorer \
	(*(void **)(rpc_interrupt_program + _rpc_interrupt_program_offsetof_restorer))



ATTR_SECTION(".text.crt.sched.rpc")
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED void const *LIBCCALL
libc_get_rpc_interrupt_program(void) {
	if (_rpc_interrupt_program_restorer == NULL)
		_rpc_interrupt_program_restorer = (void *)&libc_arm_rpc_restorer;
	return rpc_interrupt_program;
}


DECL_END

#endif /* GUARD_LIBC_LIBC_ARCH_ARM_RPC_C */
