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
#ifndef _ARM_KOS_LIBUNWIND_ASM_ISA_H
#define _ARM_KOS_LIBUNWIND_ASM_ISA_H 1

#include <__stdinc.h>

#include <asm/isa.h>

/* >> isa_t unwind_getreg_getisa(unwind_getreg_t reg_getter, void *state);
 * Determine and return the ISA code through use of an unwind register getter. */
#define unwind_getreg_getisa(/*unwind_getreg_t*/ reg_getter, /*void **/ state) \
	((_isa_getcpsr_from_unwind_getreg(reg_getter, state) & CPSR_T)             \
	 ? ISA_THUMB                                                               \
	 : ISA_ARM)

#ifdef __CC__
#include <hybrid/typecore.h>

#include <libunwind/api.h>
#include <libunwind/cfi/arm.h>
#include <libunwind/errno.h>

__DECL_BEGIN

__LOCAL __UINTPTR_TYPE__
_isa_getcpsr_from_unwind_getreg(unwind_errno_t (LIBUNWIND_CC *__reg_getter)(void const *__arg,
                                                                            __UINTPTR_HALF_TYPE__ __dw_regno,
                                                                            void *__restrict __dst),
                                void *__state) {
	__UINTPTR_TYPE__ __result;
	if ((*__reg_getter)(__state, CFI_ARM_UNWIND_REGISTER_CPSR, &__result) != UNWIND_SUCCESS)
		__result = 0;
	return __result;
}

__DECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_LIBUNWIND_ASM_ISA_H */
