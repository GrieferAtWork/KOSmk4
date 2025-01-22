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
#ifndef _KOS_KERNEL_BITS_CPU_STATE_H
#define _KOS_KERNEL_BITS_CPU_STATE_H 1

#include <__stdinc.h>

#include <bits/types.h>

/* The following macros may be defined to indicate aliases.
 * NOTE: Don't define macros to transitive aliases; iow: at most 1
 *       `XCPUSTATE_IS_*' should be defined for every `XCPUSTATE'! */
#if 0
#define LCPUSTATE_IS_UCPUSTATE

#define KCPUSTATE_IS_UCPUSTATE
#define KCPUSTATE_IS_LCPUSTATE

#define ICPUSTATE_IS_UCPUSTATE
#define ICPUSTATE_IS_LCPUSTATE
#define ICPUSTATE_IS_KCPUSTATE

#define SCPUSTATE_IS_UCPUSTATE
#define SCPUSTATE_IS_LCPUSTATE
#define SCPUSTATE_IS_KCPUSTATE
#define SCPUSTATE_IS_ICPUSTATE

#define FCPUSTATE_IS_UCPUSTATE
#define FCPUSTATE_IS_LCPUSTATE
#define FCPUSTATE_IS_KCPUSTATE
#define FCPUSTATE_IS_ICPUSTATE
#define FCPUSTATE_IS_SCPUSTATE
#endif

#ifdef __CC__
__SYSDECL_BEGIN

struct ucpustate { /* u -- User */
	__uintptr_t __u_pad[128];
};

struct lcpustate { /* l -- Little */
	__uintptr_t __l_pad[128];
};

struct kcpustate { /* k -- Kernel */
	/* A CPU state used to describe a known, valid register state in kernel-space.
	 * This  kind of state is also used  by exception handling, and the associated
	 * stack unwinding. */
	__uintptr_t __k_pad[128];
};

struct icpustate { /* i -- Interrupts */
	/* A  CPU state that is used by  hardware interrupts (other than those used
	 * by scheduling, which generate `scpustate' instead), in order to describe
	 * the interrupted text location.
	 * Also the primary CPU state used by RPC handlers. */
	__uintptr_t __i_pad[128];
};


struct scpustate { /* s -- Scheduling */
	/* CPU state, as used to store the state of a thread that isn't currently running. */
	__uintptr_t __s_pad[128];
};

struct fcpustate { /* f -- Full */
	__uintptr_t __f_pad[128];
};

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_KERNEL_BITS_CPU_STATE_H */
