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
#ifndef _I386_KOS_LIBINSTRLEN_BITS_ISA_H
#define _I386_KOS_LIBINSTRLEN_BITS_ISA_H 1

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <libemu86/emu86.h>
#include <libinstrlen/api.h>
#include <libunwind/api.h>
#ifdef __x86_64__
#include <libunwind/cfi/x86_64.h>
#else /* __x86_64__ */
#include <libunwind/cfi/i386.h>
#endif /* !__x86_64__ */

/* ISA codes. */
#if __SIZEOF_POINTER__ == 8
#define INSTRLEN_ISA_X86_64 0
#define INSTRLEN_ISA_I386   1
#elif __SIZEOF_POINTER__ == 4
#define INSTRLEN_ISA_I386 0
#ifndef __I386_NO_VM86
#define INSTRLEN_ISA_8086 1
#endif /* !__I386_NO_VM86 */
#elif __SIZEOF_POINTER__ == 2
#define INSTRLEN_ISA_8086 0
#endif /* !__x86_64__ */

/* Default ISA type. */
#if __SIZEOF_POINTER__ == 8 && defined(INSTRLEN_ISA_X86_64)
#define INSTRLEN_ISA_DEFAULT INSTRLEN_ISA_X86_64
#elif __SIZEOF_POINTER__ == 4 && defined(INSTRLEN_ISA_I386)
#define INSTRLEN_ISA_DEFAULT INSTRLEN_ISA_I386
#elif __SIZEOF_POINTER__ == 2 && defined(INSTRLEN_ISA_8086)
#define INSTRLEN_ISA_DEFAULT INSTRLEN_ISA_8086
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported __SIZEOF_POINTER__"
#endif /* __SIZEOF_POINTER__ != ... */


/* Return the ISA code, given `emu86_opflags_t flags' */
#ifdef EMU86_F_BITMASK
#if (defined(EMU86_F_32BIT) && defined(EMU86_F_16BIT) && EMU86_F_BITMASK == 1 && \
     defined(INSTRLEN_ISA_I386) && defined(INSTRLEN_ISA_8086) &&                 \
     (EMU86_F_32BIT == INSTRLEN_ISA_I386) && (EMU86_F_16BIT == INSTRLEN_ISA_8086))
#define instrlen_isa_from_emu86_opflags_t(/*emu86_opflags_t*/ flags) ((flags) & 1)
#define instrlen_isa_to_emu86_opflags_t(isa) isa
#elif (defined(EMU86_F_64BIT) && defined(EMU86_F_32BIT) && EMU86_F_BITMASK == 1 && \
       defined(INSTRLEN_ISA_X86_64) && defined(INSTRLEN_ISA_I386) &&               \
       (EMU86_F_64BIT == INSTRLEN_ISA_X86_64) && (EMU86_F_32BIT == INSTRLEN_ISA_I386))
#define instrlen_isa_from_emu86_opflags_t(/*emu86_opflags_t*/ flags) ((flags) & 1)
#define instrlen_isa_to_emu86_opflags_t(isa) isa
#endif
#endif /* EMU86_F_BITMASK */
#ifndef instrlen_isa_from_emu86_opflags_t
#if (LIBEMU86_CONFIG_WANT_16BIT && LIBEMU86_CONFIG_WANT_32BIT && LIBEMU86_CONFIG_WANT_64BIT)
#elif (LIBEMU86_CONFIG_WANT_32BIT && LIBEMU86_CONFIG_WANT_64BIT)
#if defined(INSTRLEN_ISA_X86_64) && defined(INSTRLEN_ISA_I386)
#define instrlen_isa_from_emu86_opflags_t(/*emu86_opflags_t*/ flags) \
	(EMU86_F_IS32(flags) ? INSTRLEN_ISA_I386 : INSTRLEN_ISA_X86_64)
#define instrlen_isa_to_emu86_opflags_t(isa) \
	((isa) == INSTRLEN_ISA_X86_64 ? EMU86_F_64BIT : EMU86_F_32BIT)
#endif /* INSTRLEN_ISA_X86_64 && INSTRLEN_ISA_I386 */
#elif (LIBEMU86_CONFIG_WANT_16BIT && LIBEMU86_CONFIG_WANT_32BIT)
#if defined(INSTRLEN_ISA_8086) && defined(INSTRLEN_ISA_I386)
#define instrlen_isa_from_emu86_opflags_t(/*emu86_opflags_t*/ flags) \
	(EMU86_F_IS32(flags) ? INSTRLEN_ISA_I386 : INSTRLEN_ISA_8086)
#define instrlen_isa_to_emu86_opflags_t(isa) \
	((isa) == INSTRLEN_ISA_I386 ? EMU86_F_32BIT : EMU86_F_16BIT)
#endif /* INSTRLEN_ISA_8086 && INSTRLEN_ISA_I386 */
#elif (LIBEMU86_CONFIG_WANT_16BIT && LIBEMU86_CONFIG_WANT_64BIT)
#if defined(INSTRLEN_ISA_X86_64) && defined(INSTRLEN_ISA_8086)
#define instrlen_isa_from_emu86_opflags_t(/*emu86_opflags_t*/ flags) \
	(EMU86_F_IS64(flags) ? INSTRLEN_ISA_X86_64 : INSTRLEN_ISA_8086)
#define instrlen_isa_to_emu86_opflags_t(isa) \
	((isa) == INSTRLEN_ISA_X86_64 ? EMU86_F_16BIT : EMU86_F_32BIT)
#endif /* INSTRLEN_ISA_X86_64 && INSTRLEN_ISA_8086 */
#elif LIBEMU86_CONFIG_WANT_64BIT
#ifdef INSTRLEN_ISA_X86_64
#define instrlen_isa_from_emu86_opflags_t(/*emu86_opflags_t*/ flags) INSTRLEN_ISA_X86_64
#define instrlen_isa_to_emu86_opflags_t(isa) EMU86_F_64BIT
#endif /* INSTRLEN_ISA_X86_64 */
#elif LIBEMU86_CONFIG_WANT_32BIT
#ifdef INSTRLEN_ISA_I386
#define instrlen_isa_from_emu86_opflags_t(/*emu86_opflags_t*/ flags) INSTRLEN_ISA_I386
#define instrlen_isa_to_emu86_opflags_t(isa) EMU86_F_32BIT
#endif /* INSTRLEN_ISA_I386 */
#elif LIBEMU86_CONFIG_WANT_16BIT
#ifdef INSTRLEN_ISA_8086
#define instrlen_isa_from_emu86_opflags_t(/*emu86_opflags_t*/ flags) INSTRLEN_ISA_8086
#define instrlen_isa_to_emu86_opflags_t(isa) EMU86_F_16BIT
#endif /* INSTRLEN_ISA_8086 */
#else /* ... */
#error "Invalid libemu86 configuration"
#endif /* !... */
#endif /* !instrlen_isa_from_emu86_opflags_t */



#ifdef __CC__
__DECL_BEGIN

/* Return the ISA type, given a CPU state structure. */
#ifdef __x86_64__
#define instrlen_isa_from_icpustate(s) (__likely(icpustate_is64bit(s)) ? INSTRLEN_ISA_X86_64 : INSTRLEN_ISA_I386)
#define instrlen_isa_from_scpustate(s) (__likely(scpustate_is64bit(s)) ? INSTRLEN_ISA_X86_64 : INSTRLEN_ISA_I386)
#define instrlen_isa_from_ucpustate(s) (__likely(ucpustate_is64bit(s)) ? INSTRLEN_ISA_X86_64 : INSTRLEN_ISA_I386)
#define instrlen_isa_from_kcpustate(s) INSTRLEN_ISA_X86_64
#define instrlen_isa_from_lcpustate(s) INSTRLEN_ISA_X86_64
#define instrlen_isa_from_fcpustate(s) (__likely(fcpustate_is64bit(s)) ? INSTRLEN_ISA_X86_64 : INSTRLEN_ISA_I386)
#define instrlen_isa_from_unwind_getreg(reg_getter, state)                                   \
	(__likely(__KOS64_IS_CS64BIT(_instrlen_isa_getcs_from_unwind_getreg(reg_getter, state))) \
	 ? INSTRLEN_ISA_X86_64                                                                   \
	 : INSTRLEN_ISA_I386)
__LOCAL __uintptr_t
_instrlen_isa_getcs_from_unwind_getreg(unsigned int (LIBUNWIND_CC *__reg_getter)(void const *__arg,
                                                                                 __UINTPTR_HALF_TYPE__ __dw_regno,
                                                                                 void *__restrict __dst),
                                       void *__state) {
	__uintptr_t __result;
	if ((*__reg_getter)(__state, CFI_X86_64_UNWIND_REGISTER_CS, &__result) != UNWIND_SUCCESS)
		__result = SEGMENT_USER_CODE64_RPL;
	return __result;
}
#else /* __x86_64__ */
#ifdef __I386_NO_VM86
#define instrlen_isa_from_icpustate(s)                     INSTRLEN_ISA_I386
#define instrlen_isa_from_scpustate(s)                     INSTRLEN_ISA_I386
#define instrlen_isa_from_ucpustate(s)                     INSTRLEN_ISA_I386
#define instrlen_isa_from_fcpustate(s)                     INSTRLEN_ISA_I386
#define instrlen_isa_from_unwind_getreg(reg_getter, state) INSTRLEN_ISA_I386
#else /* __I386_NO_VM86 */
#define instrlen_isa_from_icpustate(s) (__likely(!icpustate_isvm86(s)) ? INSTRLEN_ISA_I386 : INSTRLEN_ISA_8086)
#define instrlen_isa_from_scpustate(s) (__likely(!scpustate_isvm86(s)) ? INSTRLEN_ISA_I386 : INSTRLEN_ISA_8086)
#define instrlen_isa_from_ucpustate(s) (__likely(!ucpustate_isvm86(s)) ? INSTRLEN_ISA_I386 : INSTRLEN_ISA_8086)
#define instrlen_isa_from_fcpustate(s) (__likely(!fcpustate_isvm86(s)) ? INSTRLEN_ISA_I386 : INSTRLEN_ISA_8086)
#define instrlen_isa_from_unwind_getreg(reg_getter, state)                                                               \
	(__likely(!(_instrlen_isa_geteflags_from_unwind_getreg(reg_getter, state) & __UINT32_C(0x00020000) /* EFLAGS_VM */)) \
	 ? INSTRLEN_ISA_I386                                                                                                 \
	 : INSTRLEN_ISA_8086)
#endif /* !__I386_NO_VM86 */
#define instrlen_isa_from_kcpustate(s) INSTRLEN_ISA_I386
#define instrlen_isa_from_lcpustate(s) INSTRLEN_ISA_I386
__LOCAL __uintptr_t
_instrlen_isa_geteflags_from_unwind_getreg(unsigned int (LIBUNWIND_CC *__reg_getter)(void const *__arg,
                                                                                     __UINTPTR_HALF_TYPE__ __dw_regno,
                                                                                     void *__restrict __dst),
                                           void *__state) {
	__uintptr_t __result;
	if ((*__reg_getter)(__state, CFI_386_UNWIND_REGISTER_EFLAGS, &__result) != UNWIND_SUCCESS)
		__result = 0;
	return __result;
}
#endif /* !__x86_64__ */

typedef __uint8_t instrlen_isa_t;

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_LIBINSTRLEN_BITS_ISA_H */
