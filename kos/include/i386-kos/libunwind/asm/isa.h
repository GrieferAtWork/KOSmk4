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
#ifndef _I386_KOS_LIBUNWIND_ASM_ISA_H
#define _I386_KOS_LIBUNWIND_ASM_ISA_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <asm/isa.h>

#include <libunwind/api.h>
#include <libunwind/errno.h>

/* >> isa_t unwind_getreg_getisa(unwind_getreg_t reg_getter, void *state);
 * Determine and return the ISA code through use of an unwind register getter. */
#ifdef __x86_64__
#include <kos/kernel/x86/gdt.h>
#define unwind_getreg_getisa(reg_getter, state)                                     \
	(__likely(__KOS64_IS_CS64BIT(_isa_getcs_from_unwind_getreg(reg_getter, state))) \
	 ? ISA_X86_64                                                                   \
	 : ISA_I386)
#ifdef __CC__
#include <libunwind/cfi/x86_64.h>
__DECL_BEGIN
__LOCAL __UINTPTR_TYPE__
_isa_getcs_from_unwind_getreg(unwind_errno_t (LIBUNWIND_CC *__reg_getter)(void const *__arg,
                                                                          __UINTPTR_HALF_TYPE__ __dw_regno,
                                                                          void *__restrict __dst),
                              void *__state) {
	__UINTPTR_TYPE__ __result;
	if ((*__reg_getter)(__state, CFI_X86_64_UNWIND_REGISTER_CS, &__result) != UNWIND_SUCCESS)
		__result = SEGMENT_USER_CODE64_RPL;
	return __result;
}
__DECL_END
#endif /* __CC__ */
#else /* __x86_64__ */
#ifdef __I386_NO_VM86
#define unwind_getreg_getisa(reg_getter, state) ISA_I386
#else /* __I386_NO_VM86 */
#define unwind_getreg_getisa(reg_getter, state)                                                                 \
	(__likely(!(_isa_geteflags_from_unwind_getreg(reg_getter, state) & __UINT32_C(0x00020000) /* EFLAGS_VM */)) \
	 ? ISA_I386                                                                                                 \
	 : ISA_8086)
#ifdef __CC__
#include <libunwind/cfi/i386.h>
__DECL_BEGIN
__LOCAL __UINTPTR_TYPE__
_isa_geteflags_from_unwind_getreg(unwind_errno_t (LIBUNWIND_CC *__reg_getter)(void const *__arg,
                                                                              __UINTPTR_HALF_TYPE__ __dw_regno,
                                                                              void *__restrict __dst),
                                  void *__state) {
	__UINTPTR_TYPE__ __result;
	if ((*__reg_getter)(__state, CFI_386_UNWIND_REGISTER_EFLAGS, &__result) != UNWIND_SUCCESS)
		__result = 0;
	return __result;
}
__DECL_END
#endif /* __CC__ */
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */


#endif /* !_I386_KOS_LIBUNWIND_ASM_ISA_H */
