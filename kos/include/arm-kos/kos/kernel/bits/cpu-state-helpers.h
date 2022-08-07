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
#ifndef _ARM_KOS_KOS_KERNEL_BITS_CPU_STATE_HELPERS_H
#define _ARM_KOS_KOS_KERNEL_BITS_CPU_STATE_HELPERS_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/kernel/cpu-state.h>
#include <asm/cpu-flags.h>

#ifndef __INTELLISENSE__
#include <asm/intrin.h>
#endif /* !__INTELLISENSE__ */

 /* These are the cpu-state helpers that may be used portably across all architectures:
 * - pc: Program Counter
 * - sp: Stack Pointer
 *
 * Architectures may define additional macros to get/set arch-specific registers.
 */
#ifdef __CC__
__DECL_BEGIN

#define __ARM_CPSR_PREEMPTION 0x80 /* [bit(7)] IRQ enabled */

/************************************************************************/
/* FCPUSTATE                                                            */
/************************************************************************/

/* Accessors for individual registers for fcpustate */
#define fcpustate_getcpsr(self)       (*_fcpustate_p_cpsr(self))
#define fcpustate_setcpsr(self, cpsr) (void)(*_fcpustate_p_cpsr(self) = (cpsr))

/* Test for current execution mode */
#define fcpustate_isusr(self) ((fcpustate_getcpsr(self) & CPSR_M) == CPSR_M_USR)
#define fcpustate_isfiq(self) ((fcpustate_getcpsr(self) & CPSR_M) == CPSR_M_FIQ)
#define fcpustate_isirq(self) ((fcpustate_getcpsr(self) & CPSR_M) == CPSR_M_IRQ)
#define fcpustate_issvc(self) ((fcpustate_getcpsr(self) & CPSR_M) == CPSR_M_SVC)
#define fcpustate_isabt(self) ((fcpustate_getcpsr(self) & CPSR_M) == CPSR_M_ABT)
#define fcpustate_isund(self) ((fcpustate_getcpsr(self) & CPSR_M) == CPSR_M_UND)

/* Pointer-to-register */
#define _fcpustate_p_r0(self)       (&(self)->fcs_usr.ucs_r0)
#define _fcpustate_p_r1(self)       (&(self)->fcs_usr.ucs_r1)
#define _fcpustate_p_r2(self)       (&(self)->fcs_usr.ucs_r2)
#define _fcpustate_p_r3(self)       (&(self)->fcs_usr.ucs_r3)
#define _fcpustate_p_r4(self)       (&(self)->fcs_usr.ucs_r4)
#define _fcpustate_p_r5(self)       (&(self)->fcs_usr.ucs_r5)
#define _fcpustate_p_r6(self)       (&(self)->fcs_usr.ucs_r6)
#define _fcpustate_p_r7(self)       (&(self)->fcs_usr.ucs_r7)
#define _fcpustate_p_pc(self)       (&(self)->fcs_usr.ucs_pc)
#define _fcpustate_p_cpsr(self)     (&(self)->fcs_usr.ucs_cpsr)
#define _fcpustate_p_r8_usr(self)   (&(self)->fcs_usr.ucs_r8)
#define _fcpustate_p_r9_usr(self)   (&(self)->fcs_usr.ucs_r9)
#define _fcpustate_p_r10_usr(self)  (&(self)->fcs_usr.ucs_r10)
#define _fcpustate_p_r11_usr(self)  (&(self)->fcs_usr.ucs_r11)
#define _fcpustate_p_r12_usr(self)  (&(self)->fcs_usr.ucs_r12)
#define _fcpustate_p_sp_usr(self)   (&(self)->fcs_usr.ucs_sp)
#define _fcpustate_p_lr_usr(self)   (&(self)->fcs_usr.ucs_lr)
#define _fcpustate_p_r8_fiq(self)   (&(self)->fcs_R8_fiq)
#define _fcpustate_p_r9_fiq(self)   (&(self)->fcs_R9_fiq)
#define _fcpustate_p_r10_fiq(self)  (&(self)->fcs_R10_fiq)
#define _fcpustate_p_r11_fiq(self)  (&(self)->fcs_R11_fiq)
#define _fcpustate_p_r12_fiq(self)  (&(self)->fcs_R12_fiq)
#define _fcpustate_p_sp_fiq(self)   (&(self)->fcs_SP_fiq)
#define _fcpustate_p_lr_fiq(self)   (&(self)->fcs_LR_fiq)
#define _fcpustate_p_spsr_fiq(self) (&(self)->fcs_SPSR_fiq)
#define _fcpustate_p_sp_irq(self)   (&(self)->fcs_SP_irq)
#define _fcpustate_p_lr_irq(self)   (&(self)->fcs_LR_irq)
#define _fcpustate_p_spsr_irq(self) (&(self)->fcs_SPSR_irq)
#define _fcpustate_p_sp_svc(self)   (&(self)->fcs_SP_svc)
#define _fcpustate_p_lr_svc(self)   (&(self)->fcs_LR_svc)
#define _fcpustate_p_spsr_svc(self) (&(self)->fcs_SPSR_svc)
#define _fcpustate_p_sp_abt(self)   (&(self)->fcs_SP_abt)
#define _fcpustate_p_lr_abt(self)   (&(self)->fcs_LR_abt)
#define _fcpustate_p_spsr_abt(self) (&(self)->fcs_SPSR_abt)
#define _fcpustate_p_sp_und(self)   (&(self)->fcs_SP_und)
#define _fcpustate_p_lr_und(self)   (&(self)->fcs_LR_und)
#define _fcpustate_p_spsr_und(self) (&(self)->fcs_SPSR_und)

/* Automatic register bank selection */
#define _fcpustate_p_r8(self)     (fcpustate_isfiq(self) ? _fcpustate_p_r8_fiq(self) : _fcpustate_p_r8_usr(self))
#define _fcpustate_p_r9(self)     (fcpustate_isfiq(self) ? _fcpustate_p_r9_fiq(self) : _fcpustate_p_r9_usr(self))
#define _fcpustate_p_r10(self)    (fcpustate_isfiq(self) ? _fcpustate_p_r10_fiq(self) : _fcpustate_p_r10_usr(self))
#define _fcpustate_p_r11(self)    (fcpustate_isfiq(self) ? _fcpustate_p_r11_fiq(self) : _fcpustate_p_r11_usr(self))
#define _fcpustate_p_r12(self)    (fcpustate_isfiq(self) ? _fcpustate_p_r12_fiq(self) : _fcpustate_p_r12_usr(self))
#define _fcpustate_p_sp(self)     (_fcpustate_p_banked(self) + 0)
#define _fcpustate_p_lr(self)     (_fcpustate_p_banked(self) + 1)
#define _fcpustate_p_spsr(self)   (_fcpustate_p_banked(self) + 2) /* Only use if `fcpustate_have_spsr(self)' */
#define fcpustate_have_spsr(self) (!fcpustate_isusr(self))


/* Return a pointer to the register-triple `SP,LR,SPSR', as currently selected.
 * NOTE: Only valid for modes represented in `struct fcpustate'
 * NOTE: `SPSR' is only valid for modes that have said register (iow: it's not valid in USR-mode) */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __uint32_t *
__NOTHROW_NCX(_fcpustate_p_banked)(struct fcpustate const *__restrict __self) {
#ifdef NDEBUG
#define _FCPUSTATE_P_BANKED_UNDEF __builtin_offsetof(struct fcpustate, fcs_usr.ucs_sp)
#else /* NDEBUG */
#define _FCPUSTATE_P_BANKED_UNDEF 0xff /* Cause unaligned memory access */
#endif /* !NDEBUG */
	static __uint8_t const _fcpustate_bank_offsets[16] = {
		/* [CPSR_M_USR & 0xf] = */ __builtin_offsetof(struct fcpustate, fcs_usr.ucs_sp),
		/* [CPSR_M_FIQ & 0xf] = */ __builtin_offsetof(struct fcpustate, fcs_SP_fiq),
		/* [CPSR_M_IRQ & 0xf] = */ __builtin_offsetof(struct fcpustate, fcs_SP_irq),
		/* [CPSR_M_SVC & 0xf] = */ __builtin_offsetof(struct fcpustate, fcs_SP_svc),
		/* [0x00000014 & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
		/* [0x00000015 & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
		/* [CPSR_M_MON & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
		/* [CPSR_M_ABT & 0xf] = */ __builtin_offsetof(struct fcpustate, fcs_SP_abt),
		/* [0x00000018 & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
		/* [0x00000019 & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
		/* [CPSR_M_HYP & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
		/* [CPSR_M_UND & 0xf] = */ __builtin_offsetof(struct fcpustate, fcs_SP_und),
		/* [0x0000001c & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
		/* [0x0000001d & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
		/* [0x0000001e & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
		/* [CPSR_M_SYS & 0xf] = */ _FCPUSTATE_P_BANKED_UNDEF,
	};
#undef _FCPUSTATE_P_BANKED_UNDEF
	return (__uint32_t *)((__byte_t *)__self + _fcpustate_bank_offsets[__self->fcs_usr.ucs_cpsr & 0xf]);
}


/* Getter/setters for individual registers. */
#define fcpustate_getr0(self)                 (*_fcpustate_p_r0(self))
#define fcpustate_setr0(self, r0)             (void)(*_fcpustate_p_r0(self) = (r0))
#define fcpustate_getr1(self)                 (*_fcpustate_p_r1(self))
#define fcpustate_setr1(self, r1)             (void)(*_fcpustate_p_r1(self) = (r1))
#define fcpustate_getr2(self)                 (*_fcpustate_p_r2(self))
#define fcpustate_setr2(self, r2)             (void)(*_fcpustate_p_r2(self) = (r2))
#define fcpustate_getr3(self)                 (*_fcpustate_p_r3(self))
#define fcpustate_setr3(self, r3)             (void)(*_fcpustate_p_r3(self) = (r3))
#define fcpustate_getr4(self)                 (*_fcpustate_p_r4(self))
#define fcpustate_setr4(self, r4)             (void)(*_fcpustate_p_r4(self) = (r4))
#define fcpustate_getr5(self)                 (*_fcpustate_p_r5(self))
#define fcpustate_setr5(self, r5)             (void)(*_fcpustate_p_r5(self) = (r5))
#define fcpustate_getr6(self)                 (*_fcpustate_p_r6(self))
#define fcpustate_setr6(self, r6)             (void)(*_fcpustate_p_r6(self) = (r6))
#define fcpustate_getr7(self)                 (*_fcpustate_p_r7(self))
#define fcpustate_setr7(self, r7)             (void)(*_fcpustate_p_r7(self) = (r7))
#define fcpustate_getpc(self)                 (__byte_t const *)(*_fcpustate_p_pc(self))
#define fcpustate_setpc(self, pc)             (void)(*_fcpustate_p_pc(self) = (__uint32_t)__COMPILER_REQTYPE(void const *, pc))
#define fcpustate_getcpsr(self)               (*_fcpustate_p_cpsr(self))
#define fcpustate_setcpsr(self, cpsr)         (void)(*_fcpustate_p_cpsr(self) = (cpsr))
#define fcpustate_getr8_usr(self)             (*_fcpustate_p_r8_usr(self))
#define fcpustate_setr8_usr(self, r8_usr)     (void)(*_fcpustate_p_r8_usr(self) = (r8_usr))
#define fcpustate_getr9_usr(self)             (*_fcpustate_p_r9_usr(self))
#define fcpustate_setr9_usr(self, r9_usr)     (void)(*_fcpustate_p_r9_usr(self) = (r9_usr))
#define fcpustate_getr10_usr(self)            (*_fcpustate_p_r10_usr(self))
#define fcpustate_setr10_usr(self, r10_usr)   (void)(*_fcpustate_p_r10_usr(self) = (r10_usr))
#define fcpustate_getr11_usr(self)            (*_fcpustate_p_r11_usr(self))
#define fcpustate_setr11_usr(self, r11_usr)   (void)(*_fcpustate_p_r11_usr(self) = (r11_usr))
#define fcpustate_getr12_usr(self)            (*_fcpustate_p_r12_usr(self))
#define fcpustate_setr12_usr(self, r12_usr)   (void)(*_fcpustate_p_r12_usr(self) = (r12_usr))
#define fcpustate_getsp_usr(self)             (__byte_t *)(*_fcpustate_p_sp_usr(self))
#define fcpustate_setsp_usr(self, sp_usr)     (void)(*_fcpustate_p_sp_usr(self) = (__uint32_t)__COMPILER_REQTYPE(void *, sp_usr))
#define fcpustate_getlr_usr(self)             (__byte_t const *)(*_fcpustate_p_lr_usr(self))
#define fcpustate_setlr_usr(self, lr_usr)     (void)(*_fcpustate_p_lr_usr(self) = (__uint32_t)__COMPILER_REQTYPE(void const *, lr_usr))
#define fcpustate_getr8_fiq(self)             (*_fcpustate_p_r8_fiq(self))
#define fcpustate_setr8_fiq(self, r8_fiq)     (void)(*_fcpustate_p_r8_fiq(self) = (r8_fiq))
#define fcpustate_getr9_fiq(self)             (*_fcpustate_p_r9_fiq(self))
#define fcpustate_setr9_fiq(self, r9_fiq)     (void)(*_fcpustate_p_r9_fiq(self) = (r9_fiq))
#define fcpustate_getr10_fiq(self)            (*_fcpustate_p_r10_fiq(self))
#define fcpustate_setr10_fiq(self, r10_fiq)   (void)(*_fcpustate_p_r10_fiq(self) = (r10_fiq))
#define fcpustate_getr11_fiq(self)            (*_fcpustate_p_r11_fiq(self))
#define fcpustate_setr11_fiq(self, r11_fiq)   (void)(*_fcpustate_p_r11_fiq(self) = (r11_fiq))
#define fcpustate_getr12_fiq(self)            (*_fcpustate_p_r12_fiq(self))
#define fcpustate_setr12_fiq(self, r12_fiq)   (void)(*_fcpustate_p_r12_fiq(self) = (r12_fiq))
#define fcpustate_getsp_fiq(self)             (__byte_t *)(*_fcpustate_p_sp_fiq(self))
#define fcpustate_setsp_fiq(self, sp_fiq)     (void)(*_fcpustate_p_sp_fiq(self) = (__uint32_t)__COMPILER_REQTYPE(void *, sp_fiq))
#define fcpustate_getlr_fiq(self)             (__byte_t const *)(*_fcpustate_p_lr_fiq(self))
#define fcpustate_setlr_fiq(self, lr_fiq)     (void)(*_fcpustate_p_lr_fiq(self) = (__uint32_t)__COMPILER_REQTYPE(void const *, lr_fiq))
#define fcpustate_getspsr_fiq(self)           (*_fcpustate_p_spsr_fiq(self))
#define fcpustate_setspsr_fiq(self, spsr_fiq) (void)(*_fcpustate_p_spsr_fiq(self) = (spsr_fiq))
#define fcpustate_getsp_irq(self)             (__byte_t *)(*_fcpustate_p_sp_irq(self))
#define fcpustate_setsp_irq(self, sp_irq)     (void)(*_fcpustate_p_sp_irq(self) = (__uint32_t)__COMPILER_REQTYPE(void *, sp_irq))
#define fcpustate_getlr_irq(self)             (__byte_t const *)(*_fcpustate_p_lr_irq(self))
#define fcpustate_setlr_irq(self, lr_irq)     (void)(*_fcpustate_p_lr_irq(self) = (__uint32_t)__COMPILER_REQTYPE(void const *, lr_irq))
#define fcpustate_getspsr_irq(self)           (*_fcpustate_p_spsr_irq(self))
#define fcpustate_setspsr_irq(self, spsr_irq) (void)(*_fcpustate_p_spsr_irq(self) = (spsr_irq))
#define fcpustate_getsp_svc(self)             (__byte_t *)(*_fcpustate_p_sp_svc(self))
#define fcpustate_setsp_svc(self, sp_svc)     (void)(*_fcpustate_p_sp_svc(self) = (__uint32_t)__COMPILER_REQTYPE(void *, sp_svc))
#define fcpustate_getlr_svc(self)             (__byte_t const *)(*_fcpustate_p_lr_svc(self))
#define fcpustate_setlr_svc(self, lr_svc)     (void)(*_fcpustate_p_lr_svc(self) = (__uint32_t)__COMPILER_REQTYPE(void const *, lr_svc))
#define fcpustate_getspsr_svc(self)           (*_fcpustate_p_spsr_svc(self))
#define fcpustate_setspsr_svc(self, spsr_svc) (void)(*_fcpustate_p_spsr_svc(self) = (spsr_svc))
#define fcpustate_getsp_abt(self)             (__byte_t *)(*_fcpustate_p_sp_abt(self))
#define fcpustate_setsp_abt(self, sp_abt)     (void)(*_fcpustate_p_sp_abt(self) = (__uint32_t)__COMPILER_REQTYPE(void *, sp_abt))
#define fcpustate_getlr_abt(self)             (__byte_t const *)(*_fcpustate_p_lr_abt(self))
#define fcpustate_setlr_abt(self, lr_abt)     (void)(*_fcpustate_p_lr_abt(self) = (__uint32_t)__COMPILER_REQTYPE(void const *, lr_abt))
#define fcpustate_getspsr_abt(self)           (*_fcpustate_p_spsr_abt(self))
#define fcpustate_setspsr_abt(self, spsr_abt) (void)(*_fcpustate_p_spsr_abt(self) = (spsr_abt))
#define fcpustate_getsp_und(self)             (__byte_t *)(*_fcpustate_p_sp_und(self))
#define fcpustate_setsp_und(self, sp_und)     (void)(*_fcpustate_p_sp_und(self) = (__uint32_t)__COMPILER_REQTYPE(void *, sp_und))
#define fcpustate_getlr_und(self)             (__byte_t const *)(*_fcpustate_p_lr_und(self))
#define fcpustate_setlr_und(self, lr_und)     (void)(*_fcpustate_p_lr_und(self) = (__uint32_t)__COMPILER_REQTYPE(void const *, lr_und))
#define fcpustate_getspsr_und(self)           (*_fcpustate_p_spsr_und(self))
#define fcpustate_setspsr_und(self, spsr_und) (void)(*_fcpustate_p_spsr_und(self) = (spsr_und))
#define fcpustate_getr8(self)                 (*_fcpustate_p_r8(self))
#define fcpustate_setr8(self, r8)             (void)(*_fcpustate_p_r8(self) = (r8))
#define fcpustate_getr9(self)                 (*_fcpustate_p_r9(self))
#define fcpustate_setr9(self, r9)             (void)(*_fcpustate_p_r9(self) = (r9))
#define fcpustate_getr10(self)                (*_fcpustate_p_r10(self))
#define fcpustate_setr10(self, r10)           (void)(*_fcpustate_p_r10(self) = (r10))
#define fcpustate_getr11(self)                (*_fcpustate_p_r11(self))
#define fcpustate_setr11(self, r11)           (void)(*_fcpustate_p_r11(self) = (r11))
#define fcpustate_getr12(self)                (*_fcpustate_p_r12(self))
#define fcpustate_setr12(self, r12)           (void)(*_fcpustate_p_r12(self) = (r12))
#define fcpustate_getsp(self)                 (__byte_t *)(*_fcpustate_p_sp(self))
#define fcpustate_setsp(self, sp)             (void)(*_fcpustate_p_sp(self) = (__uint32_t)__COMPILER_REQTYPE(void *, sp))
#define fcpustate_getlr(self)                 (__byte_t const *)(*_fcpustate_p_lr(self))
#define fcpustate_setlr(self, lr)             (void)(*_fcpustate_p_lr(self) = (__uint32_t)__COMPILER_REQTYPE(void const *, lr))
#define fcpustate_getspsr(self)               (*_fcpustate_p_spsr(self))
#define fcpustate_setspsr(self, spsr)         (void)(*_fcpustate_p_spsr(self) = (spsr))

/* Preemption control */
#define fcpustate_getpreemption(self)          ((fcpustate_getcpsr(self) & __ARM_CPSR_PREEMPTION) != 0)
#define fcpustate_setpreemption(self, turn_on) fcpustate_setcpsr(self, (fcpustate_getcpsr(self) & ~__ARM_CPSR_PREEMPTION) | ((turn_on) ? __ARM_CPSR_PREEMPTION : 0))

/* Check for user-space vs. kernel-space */
#define fcpustate_isuser(self) fcpustate_isusr(self)
#define fcpustate_iskern(self) (!fcpustate_isusr(self))

#define fcpustate_foreach_gpregs(self, cb)                                                                               \
	do {                                                                                                                 \
		unsigned int __fcpustate_foreach_i;                                                                              \
		ucpustate_foreach_gpregs(&(self)->fcs_usr, cb);                                                                  \
		for (__fcpustate_foreach_i = 0; __fcpustate_foreach_i < 7; ++__fcpustate_foreach_i) {                            \
			cb(((__UINT32_TYPE__ const *)&(self)->fcs_R8_fiq)[__fcpustate_foreach_i]);                                   \
		}                                                                                                                \
		for (__fcpustate_foreach_i = 0; __fcpustate_foreach_i < 4; ++__fcpustate_foreach_i) {                            \
			unsigned int __fcpustate_foreach_j;                                                                          \
			for (__fcpustate_foreach_j = 0; __fcpustate_foreach_j < 2; ++__fcpustate_foreach_j) {                        \
				cb(((__UINT32_TYPE__ const *)&(self)->fcs_SP_irq)[(__fcpustate_foreach_i * 3) + __fcpustate_foreach_j]); \
			}                                                                                                            \
		}                                                                                                                \
	}	__WHILE0



/************************************************************************/
/* UCPUSTATE                                                            */
/************************************************************************/
/* NOTE: We don't enumerate `pc'! */
#define ucpustate_foreach_gpregs_elem(self) \
	((__UINT32_TYPE__ const *)__COMPILER_REQTYPE(struct ucpustate const *, self))
#define ucpustate_foreach_gpregs_size(self) 15
#define ucpustate_getr0(self)         (self)->ucs_r0
#define ucpustate_setr0(self, r0)     (void)((self)->ucs_r0 = (r0))
#define ucpustate_getr1(self)         (self)->ucs_r1
#define ucpustate_setr1(self, r1)     (void)((self)->ucs_r1 = (r1))
#define ucpustate_getr2(self)         (self)->ucs_r2
#define ucpustate_setr2(self, r2)     (void)((self)->ucs_r2 = (r2))
#define ucpustate_getr3(self)         (self)->ucs_r3
#define ucpustate_setr3(self, r3)     (void)((self)->ucs_r3 = (r3))
#define ucpustate_getr4(self)         (self)->ucs_r4
#define ucpustate_setr4(self, r4)     (void)((self)->ucs_r4 = (r4))
#define ucpustate_getr5(self)         (self)->ucs_r5
#define ucpustate_setr5(self, r5)     (void)((self)->ucs_r5 = (r5))
#define ucpustate_getr6(self)         (self)->ucs_r6
#define ucpustate_setr6(self, r6)     (void)((self)->ucs_r6 = (r6))
#define ucpustate_getr7(self)         (self)->ucs_r7
#define ucpustate_setr7(self, r7)     (void)((self)->ucs_r7 = (r7))
#define ucpustate_getr8(self)         (self)->ucs_r8
#define ucpustate_setr8(self, r8)     (void)((self)->ucs_r8 = (r8))
#define ucpustate_getr9(self)         (self)->ucs_r9
#define ucpustate_setr9(self, r9)     (void)((self)->ucs_r9 = (r9))
#define ucpustate_getr10(self)        (self)->ucs_r10
#define ucpustate_setr10(self, r10)   (void)((self)->ucs_r10 = (r10))
#define ucpustate_getr11(self)        (self)->ucs_r11
#define ucpustate_setr11(self, r11)   (void)((self)->ucs_r11 = (r11))
#define ucpustate_getr12(self)        (self)->ucs_r12
#define ucpustate_setr12(self, r12)   (void)((self)->ucs_r12 = (r12))
#define ucpustate_getsp(self)         (__byte_t *)(self)->ucs_sp
#define ucpustate_setsp(self, sp)     (void)((self)->ucs_sp = (__uint32_t)__COMPILER_REQTYPE(void *, sp))
#define ucpustate_getlr(self)         (__byte_t const *)(self)->ucs_lr
#define ucpustate_setlr(self, lr)     (void)((self)->ucs_lr = (__uint32_t)__COMPILER_REQTYPE(void const *, lr))
#define ucpustate_getpc(self)         (__byte_t const *)(self)->ucs_pc
#define ucpustate_setpc(self, pc)     (void)((self)->ucs_pc = (__uint32_t)__COMPILER_REQTYPE(void const *, pc))
#define ucpustate_getcpsr(self)       (self)->ucs_cpsr
#define ucpustate_setcpsr(self, cpsr) (void)((self)->ucs_cpsr = (cpsr))

/* Test for current execution mode */
#define ucpustate_isusr(self) ((ucpustate_getcpsr(self) & CPSR_M) == CPSR_M_USR)
#define ucpustate_isfiq(self) ((ucpustate_getcpsr(self) & CPSR_M) == CPSR_M_FIQ)
#define ucpustate_isirq(self) ((ucpustate_getcpsr(self) & CPSR_M) == CPSR_M_IRQ)
#define ucpustate_issvc(self) ((ucpustate_getcpsr(self) & CPSR_M) == CPSR_M_SVC)
#define ucpustate_isabt(self) ((ucpustate_getcpsr(self) & CPSR_M) == CPSR_M_ABT)
#define ucpustate_isund(self) ((ucpustate_getcpsr(self) & CPSR_M) == CPSR_M_UND)

/* Preemption control */
#define ucpustate_getpreemption(self)          ((ucpustate_getcpsr(self) & __ARM_CPSR_PREEMPTION) != 0)
#define ucpustate_setpreemption(self, turn_on) ucpustate_setcpsr(self, (ucpustate_getcpsr(self) & ~__ARM_CPSR_PREEMPTION) | ((turn_on) ? __ARM_CPSR_PREEMPTION : 0))

/* Check for user-space vs. kernel-space */
#define ucpustate_isuser(self) ucpustate_isusr(self)
#define ucpustate_iskern(self) (!ucpustate_isusr(self))

/* Aliases for UCPUSTATE */
#define kcpustate_getr0               ucpustate_getr0
#define kcpustate_setr0               ucpustate_setr0
#define kcpustate_getr1               ucpustate_getr1
#define kcpustate_setr1               ucpustate_setr1
#define kcpustate_getr2               ucpustate_getr2
#define kcpustate_setr2               ucpustate_setr2
#define kcpustate_getr3               ucpustate_getr3
#define kcpustate_setr3               ucpustate_setr3
#define kcpustate_getr4               ucpustate_getr4
#define kcpustate_setr4               ucpustate_setr4
#define kcpustate_getr5               ucpustate_getr5
#define kcpustate_setr5               ucpustate_setr5
#define kcpustate_getr6               ucpustate_getr6
#define kcpustate_setr6               ucpustate_setr6
#define kcpustate_getr7               ucpustate_getr7
#define kcpustate_setr7               ucpustate_setr7
#define kcpustate_getr8               ucpustate_getr8
#define kcpustate_setr8               ucpustate_setr8
#define kcpustate_getr9               ucpustate_getr9
#define kcpustate_setr9               ucpustate_setr9
#define kcpustate_getr10              ucpustate_getr10
#define kcpustate_setr10              ucpustate_setr10
#define kcpustate_getr11              ucpustate_getr11
#define kcpustate_setr11              ucpustate_setr11
#define kcpustate_getr12              ucpustate_getr12
#define kcpustate_setr12              ucpustate_setr12
#define kcpustate_getlr               ucpustate_getlr
#define kcpustate_setlr               ucpustate_setlr
#define kcpustate_getcpsr             ucpustate_getcpsr
#define kcpustate_setcpsr             ucpustate_setcpsr
#define icpustate_getr0               ucpustate_getr0
#define icpustate_setr0               ucpustate_setr0
#define icpustate_getr1               ucpustate_getr1
#define icpustate_setr1               ucpustate_setr1
#define icpustate_getr2               ucpustate_getr2
#define icpustate_setr2               ucpustate_setr2
#define icpustate_getr3               ucpustate_getr3
#define icpustate_setr3               ucpustate_setr3
#define icpustate_getr4               ucpustate_getr4
#define icpustate_setr4               ucpustate_setr4
#define icpustate_getr5               ucpustate_getr5
#define icpustate_setr5               ucpustate_setr5
#define icpustate_getr6               ucpustate_getr6
#define icpustate_setr6               ucpustate_setr6
#define icpustate_getr7               ucpustate_getr7
#define icpustate_setr7               ucpustate_setr7
#define icpustate_getr8               ucpustate_getr8
#define icpustate_setr8               ucpustate_setr8
#define icpustate_getr9               ucpustate_getr9
#define icpustate_setr9               ucpustate_setr9
#define icpustate_getr10              ucpustate_getr10
#define icpustate_setr10              ucpustate_setr10
#define icpustate_getr11              ucpustate_getr11
#define icpustate_setr11              ucpustate_setr11
#define icpustate_getr12              ucpustate_getr12
#define icpustate_setr12              ucpustate_setr12
#define icpustate_getlr               ucpustate_getlr
#define icpustate_setlr               ucpustate_setlr
#define icpustate_getcpsr             ucpustate_getcpsr
#define icpustate_setcpsr             ucpustate_setcpsr
#define icpustate_isusr               ucpustate_isusr
#define icpustate_isfiq               ucpustate_isfiq
#define icpustate_isirq               ucpustate_isirq
#define icpustate_issvc               ucpustate_issvc
#define icpustate_isabt               ucpustate_isabt
#define icpustate_isund               ucpustate_isund
#define scpustate_getr0               ucpustate_getr0
#define scpustate_setr0               ucpustate_setr0
#define scpustate_getr1               ucpustate_getr1
#define scpustate_setr1               ucpustate_setr1
#define scpustate_getr2               ucpustate_getr2
#define scpustate_setr2               ucpustate_setr2
#define scpustate_getr3               ucpustate_getr3
#define scpustate_setr3               ucpustate_setr3
#define scpustate_getr4               ucpustate_getr4
#define scpustate_setr4               ucpustate_setr4
#define scpustate_getr5               ucpustate_getr5
#define scpustate_setr5               ucpustate_setr5
#define scpustate_getr6               ucpustate_getr6
#define scpustate_setr6               ucpustate_setr6
#define scpustate_getr7               ucpustate_getr7
#define scpustate_setr7               ucpustate_setr7
#define scpustate_getr8               ucpustate_getr8
#define scpustate_setr8               ucpustate_setr8
#define scpustate_getr9               ucpustate_getr9
#define scpustate_setr9               ucpustate_setr9
#define scpustate_getr10              ucpustate_getr10
#define scpustate_setr10              ucpustate_setr10
#define scpustate_getr11              ucpustate_getr11
#define scpustate_setr11              ucpustate_setr11
#define scpustate_getr12              ucpustate_getr12
#define scpustate_setr12              ucpustate_setr12
#define scpustate_getlr               ucpustate_getlr
#define scpustate_setlr               ucpustate_setlr
#define scpustate_getcpsr             ucpustate_getcpsr
#define scpustate_setcpsr             ucpustate_setcpsr
#define scpustate_isusr               ucpustate_isusr
#define scpustate_isfiq               ucpustate_isfiq
#define scpustate_isirq               ucpustate_isirq
#define scpustate_issvc               ucpustate_issvc
#define scpustate_isabt               ucpustate_isabt
#define scpustate_isund               ucpustate_isund




/************************************************************************/
/* LCPUSTATE                                                            */
/************************************************************************/
/* NOTE: We don't enumerate `pc'! */
#define lcpustate_foreach_gpregs_elem(self) \
	((__UINT32_TYPE__ const *)__COMPILER_REQTYPE(struct lcpustate const *, self))
#define lcpustate_foreach_gpregs_size(self) 10
#define lcpustate_getr4(self)       (self)->lcs_r4
#define lcpustate_setr4(self, r4)   (void)((self)->lcs_r4 = (r4))
#define lcpustate_getr5(self)       (self)->lcs_r5
#define lcpustate_setr5(self, r5)   (void)((self)->lcs_r5 = (r5))
#define lcpustate_getr6(self)       (self)->lcs_r6
#define lcpustate_setr6(self, r6)   (void)((self)->lcs_r6 = (r6))
#define lcpustate_getr7(self)       (self)->lcs_r7
#define lcpustate_setr7(self, r7)   (void)((self)->lcs_r7 = (r7))
#define lcpustate_getr8(self)       (self)->lcs_r8
#define lcpustate_setr8(self, r8)   (void)((self)->lcs_r8 = (r8))
#define lcpustate_getr9(self)       (self)->lcs_r9
#define lcpustate_setr9(self, r9)   (void)((self)->lcs_r9 = (r9))
#define lcpustate_getr10(self)      (self)->lcs_r10
#define lcpustate_setr10(self, r10) (void)((self)->lcs_r10 = (r10))
#define lcpustate_getr11(self)      (self)->lcs_r11
#define lcpustate_setr11(self, r11) (void)((self)->lcs_r11 = (r11))
#define lcpustate_getsp(self)       (__byte_t *)(self)->lcs_sp
#define lcpustate_setsp(self, sp)   (void)((self)->lcs_sp = (__uintptr_t)__COMPILER_REQTYPE(void *, sp))
#define lcpustate_getlr(self)       (__byte_t const *)(self)->lcs_lr
#define lcpustate_setlr(self, lr)   (void)((self)->lcs_lr = (__uintptr_t)__COMPILER_REQTYPE(void const *, lr))
#define lcpustate_getpc(self)       (__byte_t const *)(self)->lcs_pc
#define lcpustate_setpc(self, pc)   (void)((self)->lcs_pc = (__uintptr_t)__COMPILER_REQTYPE(void const *, pc))





/************************************************************************/
/* Get current register state                                           */
/************************************************************************/
#define ucpustate_current ucpustate_current
#define kcpustate_current ucpustate_current
__FORCELOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(ucpustate_current)(struct ucpustate *__restrict __result) {
	/* TODO: I have a feeling that this can be encoded more efficiently using multi-register stores */
	__asm__ __volatile__("str r0, [%1, #0]\n\t"
	                     "str r1, [%1, #4]\n\t"
	                     "str r2, [%1, #8]\n\t"
	                     "str r3, [%1, #12]\n\t"
	                     "str r4, [%1, #16]\n\t"
	                     "str r5, [%1, #20]\n\t"
	                     "str r6, [%1, #24]\n\t"
	                     "str r7, [%1, #28]\n\t"
	                     "str r8, [%1, #32]\n\t"
	                     "str r9, [%1, #36]\n\t"
	                     "str r10, [%1, #40]\n\t"
	                     "str r11, [%1, #44]\n\t"
	                     "str r12, [%1, #48]\n\t"
	                     "str r13, [%1, #52]\n\t"
	                     "str r14, [%1, #56]\n\t"
	                     "str r15, [%1, #60]\n\t"
	                     : "=m" /*0*/ (*__result)
	                     : "r" /*1*/ (__result));
#ifndef __INTELLISENSE__
	__result->ucs_cpsr = __rdcpsr();
#endif /* !__INTELLISENSE__ */
}

#define lcpustate_current lcpustate_current
__FORCELOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(lcpustate_current)(struct lcpustate *__restrict __result) {
	/* TODO: I have a feeling that this can be encoded more efficiently using multi-register stores */
	__asm__ __volatile__("str r4, [%1, #0]\n\t"
	                     "str r5, [%1, #4]\n\t"
	                     "str r6, [%1, #8]\n\t"
	                     "str r7, [%1, #12]\n\t"
	                     "str r8, [%1, #16]\n\t"
	                     "str r9, [%1, #20]\n\t"
	                     "str r10, [%1, #24]\n\t"
	                     "str r11, [%1, #28]\n\t"
	                     "str r13, [%1, #32]\n\t"
	                     "str r14, [%1, #36]\n\t"
	                     "str r15, [%1, #40]\n\t"
	                     : "=m" /*0*/ (*__result)
	                     : "r" /*1*/ (__result));
}



/* Helpful (and portability) aliases */
#define fcpustate_getreturn32(self)      fcpustate_getr0(self)
#define fcpustate_getreturn64(self)      ((__UINT64_TYPE__)fcpustate_getr0(self) | ((__UINT64_TYPE__)fcpustate_getr1(self) << 32))
#define fcpustate_setreturn32(self, v)   fcpustate_setr0(self, v)
#define fcpustate_setreturn64(self, v)   (fcpustate_setr0(self, (__UINT32_TYPE__)(v)), fcpustate_setr1(self, (__UINT32_TYPE__)((__UINT64_TYPE__)(v) >> 32)))

#define ucpustate_getreturn32(self)      ucpustate_getr0(self)
#define ucpustate_getreturn64(self)      ((__UINT64_TYPE__)ucpustate_getr0(self) | ((__UINT64_TYPE__)ucpustate_getr1(self) << 32))
#define ucpustate_setreturn32(self, v)   ucpustate_setr0(self, v)
#define ucpustate_setreturn64(self, v)   (ucpustate_setr0(self, (__UINT32_TYPE__)(v)), ucpustate_setr1(self, (__UINT32_TYPE__)((__UINT64_TYPE__)(v) >> 32)))

/* CPU state converter functions.
 * NOTE: We DON'T define converter functions between aliasing types. Consumers that
 *       use converter functions need to check for `?CPUSTATE_IS_?CPUSTATE' macros!
 * e.g.: we don't define `ucpustate_to_kcpustate' because of `KCPUSTATE_IS_UCPUSTATE' */
#define lcpustate_to_ucpustate(src, dst) TODO
#define lcpustate_to_fcpustate(src, dst) TODO
#define ucpustate_to_lcpustate(src, dst) TODO
#define ucpustate_to_fcpustate(src, dst) TODO
#define fcpustate_to_ucpustate(src, dst) TODO
#define fcpustate_to_lcpustate(src, dst) TODO

/* Aliases that we do have to define (because they're not no-ops) */
#define kcpustate_to_lcpustate ucpustate_to_lcpustate
#define icpustate_to_lcpustate ucpustate_to_lcpustate
#define scpustate_to_lcpustate ucpustate_to_lcpustate

#define lcpustate_to_kcpustate lcpustate_to_ucpustate
#define fcpustate_to_kcpustate fcpustate_to_ucpustate

#define lcpustate_to_icpustate lcpustate_to_ucpustate
#define fcpustate_to_icpustate fcpustate_to_ucpustate

#define lcpustate_to_scpustate lcpustate_to_ucpustate
#define fcpustate_to_scpustate fcpustate_to_ucpustate

#define kcpustate_to_fcpustate ucpustate_to_fcpustate
#define icpustate_to_fcpustate ucpustate_to_fcpustate
#define scpustate_to_fcpustate ucpustate_to_fcpustate

__DECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_KOS_KERNEL_BITS_CPU_STATE_HELPERS_H */
