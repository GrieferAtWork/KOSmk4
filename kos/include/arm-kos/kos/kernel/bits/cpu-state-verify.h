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
#ifndef _ARM_KOS_KOS_KERNEL_BITS_CPU_STATE_VERIFY_H
#define _ARM_KOS_KOS_KERNEL_BITS_CPU_STATE_VERIFY_H 1

/* Helper functions for verification of CPU state values. */

#include <bits/types.h>
#include <kos/anno.h>

#ifndef __INTELLISENSE__
#include <asm/cpu-flags.h>
#include <asm/registers.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#endif /* !__INTELLISENSE__ */

#ifdef __CC__
__DECL_BEGIN

/* Verify that only bits masked by APSR differ between `old_cpsr' and `new_cpsr'. */
__LOCAL void (cpustate_verify_apsr)(__uintptr_t __old_cpsr,
                                    __uintptr_t __new_cpsr)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifndef __INTELLISENSE__
	if __unlikely((__old_cpsr & ~CPSR_APSRMASK) !=
	              (__new_cpsr & ~CPSR_APSRMASK)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      ARM_REGISTER_CPSR, __new_cpsr);
	}
#endif /* !__INTELLISENSE__ */
}

__DECL_END
#endif /* __CC__ */


#endif /* !_ARM_KOS_KOS_KERNEL_BITS_CPU_STATE_VERIFY_H */
