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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_MMAN_RTM_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_MMAN_RTM_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/host.h>

#include <asm/rtm.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

/* Enable RTM support in MMan data structures.
 * Note however that RTM emulation is not actually implemented
 * as  part of  the kernel core,  but is loaded  as a separate
 * driver `/os/drivers/rtm' upon first use.
 * HINT: RTM    stands    for   RestrictedTransactionalMemory.
 *       To get an overview on what this is, and how it works,
 *       you may take a look at `/kos/src/kernel/modrtm/rtm.h' */
#undef ARCH_HAVE_RTM
#define ARCH_HAVE_RTM 1

#undef ARCH_RTM_DRIVER_NAME
#define ARCH_RTM_DRIVER_NAME "rtm"

#undef ARCH_RTM_DEFINES_MRTM_HOOKS_STRUCT
#define ARCH_RTM_DEFINES_MRTM_HOOKS_STRUCT 1

DECL_BEGIN

#ifdef __CC__

struct icpustate;
struct mrtm_hooks_struct {
	/* [1..1] Hook for the `xbegin' instruction.
	 * When invoked, `state' will point to the first instruction to-be executed
	 * in transactional  execution mode,  whilst  `fallback_ip' points  to  the
	 * instruction  to which to  jump in the event  of the transaction failing. */
	ATTR_RETNONNULL_T NONNULL_T((1)) struct icpustate *
	(FCALL *rh_xbegin)(struct icpustate *__restrict state,
	                   void const *fallback_ip);
};

#ifdef __x86_64__
#define mrtm_setnosys(state) (void)((state)->ics_gpregs.gp_rax = RTM_NOSYS)
#else /* __x86_64__ */
#define mrtm_setnosys(state) (void)((state)->ics_gpregs.gp_eax = RTM_NOSYS)
#endif /* !__x86_64__ */

/* Execute code pointed-to by  `state' in transactional execution  mode.
 * This  function  will operate  such that  `state'  will be  updated to
 * reflect the proper RTM execution error code within the default system
 * call   return  register,  which   are  defined  in  `<kos/asm/rtm.h>'
 * This function is used to implement the `sys_rtm_begin()' system call,
 * in  the  event that  said system  call is  available for  the current
 * architecture. */
LOCAL ATTR_RETNONNULL NONNULL((1, 2)) struct icpustate *FCALL
mrtm_exec(struct mrtm_hooks_struct const *__restrict hooks,
          struct icpustate *__restrict state) {
	gpregs_setpax(&state->ics_gpregs, _XBEGIN_STARTED);
	return (*hooks->rh_xbegin)(state, icpustate_getpc(state));
}

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_MMAN_RTM_H */
