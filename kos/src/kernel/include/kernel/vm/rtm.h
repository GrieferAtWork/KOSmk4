/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_RTM_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_RTM_H 1

#include <kernel/compiler.h>

#include <kernel/arch/vm-rtm.h>

#ifdef ARCH_VM_HAVE_RTM
#include <kernel/driver.h>
#include <misc/atomic-ref.h>

DECL_BEGIN

#ifdef __CC__

#ifndef ARCH_VM_DEFINES_VM_RTM_HOOKS_STRUCT
struct icpustate;
struct vm_rtm_hooks_struct {
	/* [1..1] Begin transactional execution. */
	ATTR_RETNONNULL NONNULL((1)) struct icpustate *
	(FCALL *rh_rtm_begin)(struct icpustate *__restrict state);
};

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL vm_rtm_set_nosys)(struct icpustate *__restrict state);

/* Execute code pointed-to by `state' in transactional execution mode.
 * This function will operate such that `state' will be updated to
 * reflect the proper RTM execution error code within the default system
 * call return register, which are defined in `<kos/asm/rtm.h>'
 * This function is used to implement the `sys_rtm_begin()' system call,
 * in the event that said system call is available for the current
 * architecture. */
LOCAL ATTR_RETNONNULL NONNULL((1, 2)) struct icpustate *FCALL
vm_rtm_execute(struct vm_rtm_hooks_struct const *__restrict hooks,
               struct icpustate *__restrict state) {
	return (*hooks->rh_rtm_begin)(state);
}
#endif /* !ARCH_VM_DEFINES_VM_RTM_HOOKS_STRUCT */

struct driver;
struct vm_rtm_driver_hooks {
	WEAK struct driver        *rdh_driver; /* [1..1] The driver implementing these hooks. */
	struct vm_rtm_hooks_struct rdh_hooks;  /* [const] (possibly) arch-specific function pointers. */
};
#define vm_rtm_driver_hooks_destroy(self) driver_destroy((self)->rdh_driver)
DEFINE_REFCOUNT_FUNCTIONS(struct vm_rtm_driver_hooks, rdh_driver->d_refcnt, vm_rtm_driver_hooks_destroy)

/* [0..1] The currently installed RTM driver hooks. */
DATDEF XATOMIC_WEAKLYREF(struct vm_rtm_driver_hooks) vm_rtm_hooks;

#endif /* __CC__ */

DECL_END
#endif /* ARCH_VM_HAVE_RTM */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_RTM_H */
