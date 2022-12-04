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
#ifndef _ARM_KOS_LIBINSTRLEN_ISA_H
#define _ARM_KOS_LIBINSTRLEN_ISA_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/kernel/bits/cpu-state-helpers.h>

/* Default ISA type. */
#define INSTRLEN_ISA_ARM   0
#define INSTRLEN_ISA_THUMB 1

#ifdef __thumb__ /* -mthumb */
#define INSTRLEN_ISA_DEFAULT INSTRLEN_ISA_ARM
#else /* __thumb__ */
#define INSTRLEN_ISA_DEFAULT INSTRLEN_ISA_THUMB
#endif /* !__thumb__ */

/* Return the ISA type, given a CPU state structure. */
#define instrlen_isa_from_icpustate(s) (icpustate_isthumb(s) ? INSTRLEN_ISA_THUMB : INSTRLEN_ISA_ARM)
#define instrlen_isa_from_scpustate(s) (scpustate_isthumb(s) ? INSTRLEN_ISA_THUMB : INSTRLEN_ISA_ARM)
#define instrlen_isa_from_ucpustate(s) (ucpustate_isthumb(s) ? INSTRLEN_ISA_THUMB : INSTRLEN_ISA_ARM)
#define instrlen_isa_from_kcpustate(s) (kcpustate_isthumb(s) ? INSTRLEN_ISA_THUMB : INSTRLEN_ISA_ARM)
#define instrlen_isa_from_lcpustate(s) (lcpustate_isthumb(s) ? INSTRLEN_ISA_THUMB : INSTRLEN_ISA_ARM)
#define instrlen_isa_from_fcpustate(s) (fcpustate_isthumb(s) ? INSTRLEN_ISA_THUMB : INSTRLEN_ISA_ARM)
#define instrlen_isa_from_unwind_getreg(/*unwind_getreg_t*/ reg_getter, /*void **/ state) \
	((_instrlen_isa_getcpsr_from_unwind_getreg(reg_getter, state) & CPSR_T)               \
	 ? INSTRLEN_ISA_THUMB                                                                 \
	 : INSTRLEN_ISA_ARM)

#ifdef __CC__
#include <libunwind/errno.h>
#include <libunwind/cfi/arm.h>

__DECL_BEGIN

typedef __uint8_t instrlen_isa_t;

__LOCAL __uintptr_t
_instrlen_isa_getcpsr_from_unwind_getreg(unsigned int (LIBUNWIND_CC *__reg_getter)(void const *__arg,
                                                                                   __UINTPTR_HALF_TYPE__ __dw_regno,
                                                                                   void *__restrict __dst),
                                         void *__state) {
	__uintptr_t __result;
	if ((*__reg_getter)(__state, CFI_ARM_UNWIND_REGISTER_CPSR, &__result) != UNWIND_SUCCESS)
		__result = 0;
	return __result;
}

__DECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_LIBINSTRLEN_ISA_H */
