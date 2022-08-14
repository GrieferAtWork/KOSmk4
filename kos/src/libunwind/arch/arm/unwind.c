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
#ifndef GUARD_LIBUNWIND_ARCH_ARM_UNWIND_C
#define GUARD_LIBUNWIND_ARCH_ARM_UNWIND_C 1
#define _KOS_KERNEL_SOURCE 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/types.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <libunwind/arch-register.h>
#include <libunwind/cfi.h>
#include <libunwind/cfi/arm.h>
#include <libunwind/unwind.h>

#include "../../unwind.h"

DECL_BEGIN

/* Functions we want to define: */
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate)(struct ucpustate const *self, unwind_regno_t dw_regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate_exclusive)(struct ucpustate const *self, unwind_regno_t dw_regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate)(struct ucpustate *self, unwind_regno_t dw_regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate_exclusive)(struct ucpustate *self, unwind_regno_t dw_regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate)(struct lcpustate const *self, unwind_regno_t dw_regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate_exclusive)(struct lcpustate const *self, unwind_regno_t dw_regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate)(struct lcpustate *self, unwind_regno_t dw_regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate_exclusive)(struct lcpustate *self, unwind_regno_t dw_regno, void const *__restrict src);
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_getreg_fcpustate)(struct fcpustate const *self, unwind_regno_t dw_regno, void *__restrict dst);
INTDEF NONNULL((1, 3)) unsigned int NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate)(struct fcpustate *self, unwind_regno_t dw_regno, void const *__restrict src);

#define wr32(p_ptr, value) (*(uint32_t *)(p_ptr) = (value))
#define rd32(p_ptr)        (*(uint32_t const *)(p_ptr))

/************************************************************************/
/* Implicit register access                                             */
/************************************************************************/
PRIVATE NONNULL((2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_getreg_implicit)(unwind_regno_t dw_regno,
                                             void *__restrict dst) {
	uintptr_t value;
	switch (dw_regno) {

	case CFI_ARM_UNWIND_REGISTER_CPSR:     value = __rdcpsr(); break; /* TODO: If this is privileged in user-space, use `__rdapsr()' instead! */
	case CFI_ARM_UNWIND_REGISTER_SPSR_FIQ: value = __rdSPSR_fiq(); break;
	case CFI_ARM_UNWIND_REGISTER_SPSR_IRQ: value = __rdSPSR_irq(); break;
	case CFI_ARM_UNWIND_REGISTER_SPSR_ABT: value = __rdSPSR_abt(); break;
	case CFI_ARM_UNWIND_REGISTER_SPSR_UND: value = __rdSPSR_und(); break;
	case CFI_ARM_UNWIND_REGISTER_SPSR_SVC: value = __rdSPSR_svc(); break;
	case CFI_ARM_UNWIND_REGISTER_R8_USR:   value = __rdR8_usr(); break;
	case CFI_ARM_UNWIND_REGISTER_R9_USR:   value = __rdR9_usr(); break;
	case CFI_ARM_UNWIND_REGISTER_R10_USR:  value = __rdR10_usr(); break;
	case CFI_ARM_UNWIND_REGISTER_R11_USR:  value = __rdR11_usr(); break;
	case CFI_ARM_UNWIND_REGISTER_R12_USR:  value = __rdR12_usr(); break;
	case CFI_ARM_UNWIND_REGISTER_SP_USR:   value = (uint32_t)__rdSP_usr(); break;
	case CFI_ARM_UNWIND_REGISTER_LR_USR:   value = (uint32_t)__rdLR_usr(); break;
	case CFI_ARM_UNWIND_REGISTER_R8_FIQ:   value = __rdR8_fiq(); break;
	case CFI_ARM_UNWIND_REGISTER_R9_FIQ:   value = __rdR9_fiq(); break;
	case CFI_ARM_UNWIND_REGISTER_R10_FIQ:  value = __rdR10_fiq(); break;
	case CFI_ARM_UNWIND_REGISTER_R11_FIQ:  value = __rdR11_fiq(); break;
	case CFI_ARM_UNWIND_REGISTER_R12_FIQ:  value = __rdR12_fiq(); break;
	case CFI_ARM_UNWIND_REGISTER_SP_FIQ:   value = (uint32_t)__rdSP_fiq(); break;
	case CFI_ARM_UNWIND_REGISTER_LR_FIQ:   value = (uint32_t)__rdLR_fiq(); break;
	case CFI_ARM_UNWIND_REGISTER_SP_IRQ:   value = (uint32_t)__rdSP_irq(); break;
	case CFI_ARM_UNWIND_REGISTER_LR_IRQ:   value = (uint32_t)__rdLR_irq(); break;
	case CFI_ARM_UNWIND_REGISTER_SP_ABT:   value = (uint32_t)__rdSP_abt(); break;
	case CFI_ARM_UNWIND_REGISTER_LR_ABT:   value = (uint32_t)__rdLR_abt(); break;
	case CFI_ARM_UNWIND_REGISTER_SP_UND:   value = (uint32_t)__rdSP_und(); break;
	case CFI_ARM_UNWIND_REGISTER_LR_UND:   value = (uint32_t)__rdLR_und(); break;
	case CFI_ARM_UNWIND_REGISTER_SP_SVC:   value = (uint32_t)__rdSP_svc(); break;
	case CFI_ARM_UNWIND_REGISTER_LR_SVC:   value = (uint32_t)__rdLR_svc(); break;

	default:
		return UNWIND_INVALID_REGISTER;
	}
	wr32(dst, value);
	return UNWIND_SUCCESS;
}

PRIVATE NONNULL((2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_setreg_implicit)(unwind_regno_t dw_regno,
                                             void const *__restrict src) {
	unsigned int result;
	uint32_t expected;
	result = libuw_unwind_getreg_implicit(dw_regno, &expected);
	if (result == UNWIND_SUCCESS && expected != rd32(src))
		result = UNWIND_INVALID_REGISTER;
	return result;
}


/* Only for register numbers CFI_ARM_UNWIND_REGISTER_R0...CFI_ARM_UNWIND_REGISTER_PC: */
#define DWREGNO_TO_UCPUSTATE_OFFSET(dw_regno)                                           \
	((dw_regno) >= CFI_ARM_UNWIND_REGISTER_SP                                           \
	 ? (uintptr_t)(((uintptr_t)CFI_ARM_UNWIND_REGISTER_PC - (uintptr_t)(dw_regno)) * 4) \
	 : (uintptr_t)OFFSET_UCPUSTATE_R0 + (uintptr_t)(4 * (dw_regno)))


/* Register state accessor base functions */
LOCAL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(CC ucpustate_regptr)(struct ucpustate const *self,
                                 unwind_regno_t dw_regno) {
	uint32_t const *result;
	switch (dw_regno) {

	case CFI_ARM_UNWIND_REGISTER_R0 ... CFI_ARM_UNWIND_REGISTER_PC: {
		static_assert(offsetof(struct ucpustate, ucs_r0) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R0));
		static_assert(offsetof(struct ucpustate, ucs_r1) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R1));
		static_assert(offsetof(struct ucpustate, ucs_r2) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R2));
		static_assert(offsetof(struct ucpustate, ucs_r3) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R3));
		static_assert(offsetof(struct ucpustate, ucs_r4) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R4));
		static_assert(offsetof(struct ucpustate, ucs_r5) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R5));
		static_assert(offsetof(struct ucpustate, ucs_r6) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R6));
		static_assert(offsetof(struct ucpustate, ucs_r7) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R7));
		static_assert(offsetof(struct ucpustate, ucs_r8) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R8));
		static_assert(offsetof(struct ucpustate, ucs_r9) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R9));
		static_assert(offsetof(struct ucpustate, ucs_r10) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R10));
		static_assert(offsetof(struct ucpustate, ucs_r11) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R11));
		static_assert(offsetof(struct ucpustate, ucs_r12) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R12));
		static_assert(offsetof(struct ucpustate, ucs_sp) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_SP));
		static_assert(offsetof(struct ucpustate, ucs_lr) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_LR));
		static_assert(offsetof(struct ucpustate, ucs_pc) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_PC));
		result = (uint32_t *)((byte_t *)self + DWREGNO_TO_UCPUSTATE_OFFSET(dw_regno));
	}	break;

	case CFI_ARM_UNWIND_REGISTER_CPSR:
		result = &self->ucs_cpsr;
		break;

	case CFI_ARM_UNWIND_REGISTER_SPSR_FIQ:
		if (!ucpustate_isfiq(self))
			goto badreg;
		result = &self->ucs_cpsr;
		break;

	case CFI_ARM_UNWIND_REGISTER_SPSR_IRQ:
		if (!ucpustate_isirq(self))
			goto badreg;
		result = &self->ucs_cpsr;
		break;

	case CFI_ARM_UNWIND_REGISTER_SPSR_ABT:
		if (!ucpustate_isabt(self))
			goto badreg;
		result = &self->ucs_cpsr;
		break;

	case CFI_ARM_UNWIND_REGISTER_SPSR_UND:
		if (!ucpustate_isund(self))
			goto badreg;
		result = &self->ucs_cpsr;
		break;

	case CFI_ARM_UNWIND_REGISTER_SPSR_SVC:
		if (!ucpustate_issvc(self))
			goto badreg;
		result = &self->ucs_cpsr;
		break;

	case CFI_ARM_UNWIND_REGISTER_R8_USR ... CFI_ARM_UNWIND_REGISTER_LR_USR: {
		static_assert(offsetof(struct ucpustate, ucs_r8) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R8_USR - 136));
		static_assert(offsetof(struct ucpustate, ucs_r9) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R9_USR - 136));
		static_assert(offsetof(struct ucpustate, ucs_r10) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R10_USR - 136));
		static_assert(offsetof(struct ucpustate, ucs_r11) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R11_USR - 136));
		static_assert(offsetof(struct ucpustate, ucs_r12) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R12_USR - 136));
		static_assert(offsetof(struct ucpustate, ucs_sp) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_SP_USR - 136));
		static_assert(offsetof(struct ucpustate, ucs_lr) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_LR_USR - 136));
		if (!ucpustate_isusr(self))
			goto badreg;
		result = (uint32_t *)((byte_t *)self + DWREGNO_TO_UCPUSTATE_OFFSET(dw_regno - 136));
	}	break;

	case CFI_ARM_UNWIND_REGISTER_R8_FIQ ... CFI_ARM_UNWIND_REGISTER_LR_FIQ: {
		static_assert(offsetof(struct ucpustate, ucs_r8) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R8_FIQ - 143));
		static_assert(offsetof(struct ucpustate, ucs_r9) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R9_FIQ - 143));
		static_assert(offsetof(struct ucpustate, ucs_r10) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R10_FIQ - 143));
		static_assert(offsetof(struct ucpustate, ucs_r11) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R11_FIQ - 143));
		static_assert(offsetof(struct ucpustate, ucs_r12) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R12_FIQ - 143));
		static_assert(offsetof(struct ucpustate, ucs_sp) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_SP_FIQ - 143));
		static_assert(offsetof(struct ucpustate, ucs_lr) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_LR_FIQ - 143));
		if (!ucpustate_isfiq(self))
			goto badreg;
		result = (uint32_t *)((byte_t *)self + DWREGNO_TO_UCPUSTATE_OFFSET(dw_regno - 143));
	}	break;

	case CFI_ARM_UNWIND_REGISTER_SP_IRQ:
		if (!ucpustate_isirq(self))
			goto badreg;
		result = &self->ucs_sp;
		break;

	case CFI_ARM_UNWIND_REGISTER_LR_IRQ:
		if (!ucpustate_isirq(self))
			goto badreg;
		result = &self->ucs_lr;
		break;

	case CFI_ARM_UNWIND_REGISTER_SP_ABT:
		if (!ucpustate_isabt(self))
			goto badreg;
		result = &self->ucs_sp;
		break;

	case CFI_ARM_UNWIND_REGISTER_LR_ABT:
		if (!ucpustate_isabt(self))
			goto badreg;
		result = &self->ucs_lr;
		break;

	case CFI_ARM_UNWIND_REGISTER_SP_UND:
		if (!ucpustate_isund(self))
			goto badreg;
		result = &self->ucs_sp;
		break;

	case CFI_ARM_UNWIND_REGISTER_LR_UND:
		if (!ucpustate_isund(self))
			goto badreg;
		result = &self->ucs_lr;
		break;

	case CFI_ARM_UNWIND_REGISTER_SP_SVC:
		if (!ucpustate_issvc(self))
			goto badreg;
		result = &self->ucs_sp;
		break;

	case CFI_ARM_UNWIND_REGISTER_LR_SVC:
		if (!ucpustate_issvc(self))
			goto badreg;
		result = &self->ucs_lr;
		break;

	default:
		goto badreg;
	}
	return (uint32_t *)result;
badreg:
	return NULL;
}


PRIVATE uintptr_t const lcpustate_register_offsets[16] = {
	/* r0  */ (uintptr_t)-1,
	/* r1  */ (uintptr_t)-1,
	/* r2  */ (uintptr_t)-1,
	/* r3  */ (uintptr_t)-1,
	/* r4  */ offsetof(struct lcpustate, lcs_r4),
	/* r5  */ offsetof(struct lcpustate, lcs_r5),
	/* r6  */ offsetof(struct lcpustate, lcs_r6),
	/* r7  */ offsetof(struct lcpustate, lcs_r7),
	/* r8  */ offsetof(struct lcpustate, lcs_r8),
	/* r9  */ offsetof(struct lcpustate, lcs_r9),
	/* r10 */ offsetof(struct lcpustate, lcs_r10),
	/* r11 */ offsetof(struct lcpustate, lcs_r11),
	/* r12 */ (uintptr_t)-1,
	/* sp  */ offsetof(struct lcpustate, lcs_sp),
	/* lr  */ (uintptr_t)-1,
	/* pc  */ offsetof(struct lcpustate, lcs_pc),
};

LOCAL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(CC lcpustate_regptr)(struct lcpustate const *self,
                                 unwind_regno_t dw_regno) {
	uint32_t const *result;
	switch (dw_regno) {

	case CFI_ARM_UNWIND_REGISTER_R0 ... CFI_ARM_UNWIND_REGISTER_PC: {
		static_assert(CFI_ARM_UNWIND_REGISTER_R0 == 0);
		static_assert(CFI_ARM_UNWIND_REGISTER_R1 == 1);
		static_assert(CFI_ARM_UNWIND_REGISTER_R2 == 2);
		static_assert(CFI_ARM_UNWIND_REGISTER_R3 == 3);
		static_assert(CFI_ARM_UNWIND_REGISTER_R4 == 4);
		static_assert(CFI_ARM_UNWIND_REGISTER_R5 == 5);
		static_assert(CFI_ARM_UNWIND_REGISTER_R6 == 6);
		static_assert(CFI_ARM_UNWIND_REGISTER_R7 == 7);
		static_assert(CFI_ARM_UNWIND_REGISTER_R8 == 8);
		static_assert(CFI_ARM_UNWIND_REGISTER_R9 == 9);
		static_assert(CFI_ARM_UNWIND_REGISTER_R10 == 10);
		static_assert(CFI_ARM_UNWIND_REGISTER_R11 == 11);
		static_assert(CFI_ARM_UNWIND_REGISTER_R12 == 12);
		static_assert(CFI_ARM_UNWIND_REGISTER_SP == 13);
		static_assert(CFI_ARM_UNWIND_REGISTER_LR == 14);
		static_assert(CFI_ARM_UNWIND_REGISTER_PC == 15);
		uintptr_t offset = lcpustate_register_offsets[dw_regno];
		if unlikely(offset == (uintptr_t)-1)
			goto badreg;
		result = (uint32_t *)((byte_t *)self + offset);
	}	break;

#ifndef __KERNEL__
	case CFI_ARM_UNWIND_REGISTER_R8_USR ... CFI_ARM_UNWIND_REGISTER_LR_USR: {
		static_assert(8 + (CFI_ARM_UNWIND_REGISTER_R8_USR - CFI_ARM_UNWIND_REGISTER_R8_USR) == 8);
		static_assert(8 + (CFI_ARM_UNWIND_REGISTER_R9_USR - CFI_ARM_UNWIND_REGISTER_R8_USR) == 9);
		static_assert(8 + (CFI_ARM_UNWIND_REGISTER_R10_USR - CFI_ARM_UNWIND_REGISTER_R8_USR) == 10);
		static_assert(8 + (CFI_ARM_UNWIND_REGISTER_R11_USR - CFI_ARM_UNWIND_REGISTER_R8_USR) == 11);
		static_assert(8 + (CFI_ARM_UNWIND_REGISTER_R12_USR - CFI_ARM_UNWIND_REGISTER_R8_USR) == 12);
		static_assert(8 + (CFI_ARM_UNWIND_REGISTER_SP_USR - CFI_ARM_UNWIND_REGISTER_R8_USR) == 13);
		static_assert(8 + (CFI_ARM_UNWIND_REGISTER_LR_USR - CFI_ARM_UNWIND_REGISTER_R8_USR) == 14);
		uintptr_t offset = lcpustate_register_offsets[8 + (dw_regno - CFI_ARM_UNWIND_REGISTER_R8_USR)];
		if unlikely(offset == (uintptr_t)-1)
			goto badreg;
		result = (uint32_t *)((byte_t *)self + offset);
	}	break;
#endif /* !__KERNEL__ */

	default:
		goto badreg;
	}
	return (uint32_t *)result;
badreg:
	return NULL;
}



/************************************************************************/
/* UCPUSTATE                                                            */
/************************************************************************/
INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate_exclusive)(struct ucpustate const *self,
                                                        unwind_regno_t dw_regno,
                                                        void *__restrict dst) {
	uint32_t *regptr = ucpustate_regptr(self, dw_regno);
	if unlikely(!regptr)
		return UNWIND_INVALID_REGISTER;
	wr32(dst, *regptr);
	return UNWIND_SUCCESS;
}

INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate_exclusive)(struct ucpustate *self,
                                                        unwind_regno_t dw_regno,
                                                        void const *__restrict src) {
	uint32_t *regptr = ucpustate_regptr(self, dw_regno);
	if unlikely(!regptr)
		return UNWIND_INVALID_REGISTER;
	*regptr = rd32(src);
	return UNWIND_SUCCESS;
}

INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_getreg_ucpustate)(struct ucpustate const *self,
                                              unwind_regno_t dw_regno,
                                              void *__restrict dst) {
	uint32_t *regptr = ucpustate_regptr(self, dw_regno);
	if likely(regptr) {
		wr32(dst, *regptr);
		return UNWIND_SUCCESS;
	}
	return libuw_unwind_getreg_implicit(dw_regno, dst);
}

INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_setreg_ucpustate)(struct ucpustate *self,
                                              unwind_regno_t dw_regno,
                                              void const *__restrict src) {
	uint32_t *regptr = ucpustate_regptr(self, dw_regno);
	if likely(regptr) {
		*regptr = rd32(src);
		return UNWIND_SUCCESS;
	}
	return libuw_unwind_setreg_implicit(dw_regno, src);
}



/************************************************************************/
/* LCPUSTATE                                                            */
/************************************************************************/
INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate_exclusive)(struct lcpustate const *self,
                                                        unwind_regno_t dw_regno,
                                                        void *__restrict dst) {
	uint32_t *regptr;
	switch (dw_regno) {

	case CFI_ARM_UNWIND_REGISTER_CPSR:
		wr32(dst, (CPSR_MYMODE | CPSR_F | CPSR_I) |
		          (lcpustate_isthumb(self) ? CPSR_T : 0));
		return UNWIND_SUCCESS;

	case CFI_ARM_UNWIND_REGISTER_PC:
		wr32(dst, (uint32_t)lcpustate_getpc(self));
		return UNWIND_SUCCESS;

	default:
		break;
	}
	regptr = lcpustate_regptr(self, dw_regno);
	if unlikely(!regptr)
		return UNWIND_INVALID_REGISTER;
	wr32(dst, *regptr);
	return UNWIND_SUCCESS;
}

INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate_exclusive)(struct lcpustate *self,
                                                        unwind_regno_t dw_regno,
                                                        void const *__restrict src) {
	uint32_t *regptr;
	switch (dw_regno) {

	case CFI_ARM_UNWIND_REGISTER_CPSR:
		self->lcs_pc &= ~1;
		if (rd32(src) & CPSR_T)
			self->lcs_pc |= 1;
		return UNWIND_SUCCESS;

	case CFI_ARM_UNWIND_REGISTER_PC:
		self->lcs_pc &= 1;
		self->lcs_pc |= rd32(src) & ~1;
		return UNWIND_SUCCESS;

	default:
		break;
	}
	regptr = lcpustate_regptr(self, dw_regno);
	if unlikely(!regptr)
		return UNWIND_INVALID_REGISTER;
	*regptr = rd32(src);
	return UNWIND_SUCCESS;
}

INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_getreg_lcpustate)(struct lcpustate const *self,
                                              unwind_regno_t dw_regno,
                                              void *__restrict dst) {
	unsigned int result;
	result = libuw_unwind_getreg_lcpustate_exclusive(self, dw_regno, dst);
	if (result == UNWIND_INVALID_REGISTER)
		result = libuw_unwind_getreg_implicit(dw_regno, dst);
	return result;
}

INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_setreg_lcpustate)(struct lcpustate *self,
                                              unwind_regno_t dw_regno,
                                              void const *__restrict src) {
	unsigned int result;
	result = libuw_unwind_setreg_lcpustate_exclusive(self, dw_regno, src);
	if (result == UNWIND_INVALID_REGISTER)
		result = libuw_unwind_setreg_implicit(dw_regno, src);
	return result;
}



/************************************************************************/
/* FCPUSTATE                                                            */
/************************************************************************/
LOCAL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(CC fcpustate_regptr)(struct fcpustate const *self,
                                 unwind_regno_t dw_regno) {
	uint32_t const *result;
	switch (dw_regno) {

	case CFI_ARM_UNWIND_REGISTER_R0 ... CFI_ARM_UNWIND_REGISTER_R7:
	case CFI_ARM_UNWIND_REGISTER_PC: {
		static_assert(offsetof(struct fcpustate, fcs_usr.ucs_r0) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R0));
		static_assert(offsetof(struct fcpustate, fcs_usr.ucs_r1) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R1));
		static_assert(offsetof(struct fcpustate, fcs_usr.ucs_r2) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R2));
		static_assert(offsetof(struct fcpustate, fcs_usr.ucs_r3) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R3));
		static_assert(offsetof(struct fcpustate, fcs_usr.ucs_r4) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R4));
		static_assert(offsetof(struct fcpustate, fcs_usr.ucs_r5) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R5));
		static_assert(offsetof(struct fcpustate, fcs_usr.ucs_r6) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R6));
		static_assert(offsetof(struct fcpustate, fcs_usr.ucs_r7) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_R7));
		static_assert(offsetof(struct fcpustate, fcs_usr.ucs_pc) == DWREGNO_TO_UCPUSTATE_OFFSET(CFI_ARM_UNWIND_REGISTER_PC));
		result = (uint32_t *)((byte_t *)self + DWREGNO_TO_UCPUSTATE_OFFSET(dw_regno));
	}	break;

	case CFI_ARM_UNWIND_REGISTER_R8:       result = _fcpustate_p_r8(self); break;
	case CFI_ARM_UNWIND_REGISTER_R9:       result = _fcpustate_p_r9(self); break;
	case CFI_ARM_UNWIND_REGISTER_R10:      result = _fcpustate_p_r10(self); break;
	case CFI_ARM_UNWIND_REGISTER_R11:      result = _fcpustate_p_r11(self); break;
	case CFI_ARM_UNWIND_REGISTER_R12:      result = _fcpustate_p_r12(self); break;
	case CFI_ARM_UNWIND_REGISTER_SP:       result = _fcpustate_p_sp(self); break;
	case CFI_ARM_UNWIND_REGISTER_LR:       result = _fcpustate_p_lr(self); break;
	case CFI_ARM_UNWIND_REGISTER_CPSR:     result = _fcpustate_p_cpsr(self); break;
	case CFI_ARM_UNWIND_REGISTER_SPSR_FIQ: result = _fcpustate_p_spsr_fiq(self); break;
	case CFI_ARM_UNWIND_REGISTER_SPSR_IRQ: result = _fcpustate_p_spsr_irq(self); break;
	case CFI_ARM_UNWIND_REGISTER_SPSR_ABT: result = _fcpustate_p_spsr_abt(self); break;
	case CFI_ARM_UNWIND_REGISTER_SPSR_UND: result = _fcpustate_p_spsr_und(self); break;
	case CFI_ARM_UNWIND_REGISTER_SPSR_SVC: result = _fcpustate_p_spsr_svc(self); break;
	case CFI_ARM_UNWIND_REGISTER_R8_USR:   result = _fcpustate_p_r8_usr(self); break;
	case CFI_ARM_UNWIND_REGISTER_R9_USR:   result = _fcpustate_p_r9_usr(self); break;
	case CFI_ARM_UNWIND_REGISTER_R10_USR:  result = _fcpustate_p_r10_usr(self); break;
	case CFI_ARM_UNWIND_REGISTER_R11_USR:  result = _fcpustate_p_r11_usr(self); break;
	case CFI_ARM_UNWIND_REGISTER_R12_USR:  result = _fcpustate_p_r12_usr(self); break;
	case CFI_ARM_UNWIND_REGISTER_SP_USR:   result = _fcpustate_p_sp_usr(self); break;
	case CFI_ARM_UNWIND_REGISTER_LR_USR:   result = _fcpustate_p_lr_usr(self); break;
	case CFI_ARM_UNWIND_REGISTER_R8_FIQ:   result = _fcpustate_p_r8_fiq(self); break;
	case CFI_ARM_UNWIND_REGISTER_R9_FIQ:   result = _fcpustate_p_r9_fiq(self); break;
	case CFI_ARM_UNWIND_REGISTER_R10_FIQ:  result = _fcpustate_p_r10_fiq(self); break;
	case CFI_ARM_UNWIND_REGISTER_R11_FIQ:  result = _fcpustate_p_r11_fiq(self); break;
	case CFI_ARM_UNWIND_REGISTER_R12_FIQ:  result = _fcpustate_p_r12_fiq(self); break;
	case CFI_ARM_UNWIND_REGISTER_SP_FIQ:   result = _fcpustate_p_sp_fiq(self); break;
	case CFI_ARM_UNWIND_REGISTER_LR_FIQ:   result = _fcpustate_p_lr_fiq(self); break;
	case CFI_ARM_UNWIND_REGISTER_SP_IRQ:   result = _fcpustate_p_sp_irq(self); break;
	case CFI_ARM_UNWIND_REGISTER_LR_IRQ:   result = _fcpustate_p_lr_irq(self); break;
	case CFI_ARM_UNWIND_REGISTER_SP_ABT:   result = _fcpustate_p_sp_abt(self); break;
	case CFI_ARM_UNWIND_REGISTER_LR_ABT:   result = _fcpustate_p_lr_abt(self); break;
	case CFI_ARM_UNWIND_REGISTER_SP_UND:   result = _fcpustate_p_sp_und(self); break;
	case CFI_ARM_UNWIND_REGISTER_LR_UND:   result = _fcpustate_p_lr_und(self); break;
	case CFI_ARM_UNWIND_REGISTER_SP_SVC:   result = _fcpustate_p_sp_svc(self); break;
	case CFI_ARM_UNWIND_REGISTER_LR_SVC:   result = _fcpustate_p_lr_svc(self); break;

	default: goto badreg;
	}
	return (uint32_t *)result;
badreg:
	return NULL;
}

INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_getreg_fcpustate)(struct fcpustate const *self,
                                              unwind_regno_t dw_regno,
                                              void *__restrict dst) {
	uint32_t *regptr = fcpustate_regptr(self, dw_regno);
	if unlikely(!regptr)
		return UNWIND_INVALID_REGISTER;
	wr32(dst, *regptr);
	return UNWIND_SUCCESS;
}

INTERN NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_setreg_fcpustate)(struct fcpustate *self,
                                              unwind_regno_t dw_regno,
                                              void const *__restrict src) {
	uint32_t *regptr = fcpustate_regptr(self, dw_regno);
	if unlikely(!regptr)
		return UNWIND_INVALID_REGISTER;
	*regptr = rd32(src);
	return UNWIND_SUCCESS;
}


/* Exports */
DEFINE_PUBLIC_ALIAS(unwind_getreg_ucpustate, libuw_unwind_getreg_ucpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_ucpustate_exclusive, libuw_unwind_getreg_ucpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_setreg_ucpustate, libuw_unwind_setreg_ucpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_ucpustate_exclusive, libuw_unwind_setreg_ucpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_getreg_lcpustate, libuw_unwind_getreg_lcpustate);
DEFINE_PUBLIC_ALIAS(unwind_getreg_lcpustate_exclusive, libuw_unwind_getreg_lcpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_setreg_lcpustate, libuw_unwind_setreg_lcpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_lcpustate_exclusive, libuw_unwind_setreg_lcpustate_exclusive);
DEFINE_PUBLIC_ALIAS(unwind_getreg_fcpustate, libuw_unwind_getreg_fcpustate);
DEFINE_PUBLIC_ALIAS(unwind_setreg_fcpustate, libuw_unwind_setreg_fcpustate);

DECL_END

#endif /* !GUARD_LIBUNWIND_ARCH_ARM_UNWIND_C */
