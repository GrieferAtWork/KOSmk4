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
#ifndef _I386_KOS_BITS_CRT_FENV_IMPL_H
#define _I386_KOS_BITS_CRT_FENV_IMPL_H 1

#include <__stdinc.h>

#ifndef __NO_FPU
#include <hybrid/__assert.h>
#include <hybrid/typecore.h>

#include <asm/cpu-flags.h>
#include <asm/intrin-cpuid.h>
#include <asm/intrin-fpu.h>
#include <asm/crt/fenv.h>
#include <bits/crt/fenv.h>
#include <kos/kernel/bits/fpu-sstate.h>

#ifdef __CC__
__SYSDECL_BEGIN

__LOCAL void (__x86_raise_fpu_invalid)(void) {
	/* 0.0 / 0.0 */
#ifdef __TINYC__
	__asm__ __volatile__("fldz\n\t" /* push {0.0} */
	                     "fdiv %st(0), %st(0)\n\t"
	                     "fwait");
#else /* __TINYC__ */
	double __temp; /* Needed to force register allocation */
	__asm__ __volatile__("fldz\n\t" /* push {0.0} */
	                     "fdiv %%st(0), %%st(0)\n\t"
	                     "fwait"
	                     : "=t" (__temp));
	(void)__temp;
#endif /* !__TINYC__ */
}

__LOCAL void (__x86_raise_fpu_divbyzero)(void) {
	/* 1.0 / 0.0 */
#ifdef __TINYC__
	__asm__ __volatile__("fldz\n\t" /* push {0.0} */
	                     "fld1\n\t" /* push {1.0} */
	                     "fdiv %st(0), %st(1)\n\t"
	                     "fwait");
#else /* __TINYC__ */
	double __temp; /* Needed to force register allocation */
	__asm__ __volatile__("fldz\n\t" /* push {0.0} */
	                     "fld1\n\t" /* push {1.0} */
	                     "fdiv %%st(0), %%st(1)\n\t"
	                     "fwait"
	                     : "=t" (__temp));
	(void)__temp;
#endif /* !__TINYC__ */
}

__LOCAL void (__x86_raise_fpu_mask)(__UINT16_TYPE__ __mask) {
	struct sfpuenv __env;
	__fnstenv(&__env);
	__env.fe_fsw |= __mask;
	__fldenv(&__env);
	__fwait();
}

__LOCAL void (__x86_raise_fpu_overflow)(void) {
	__x86_raise_fpu_mask(0x0008 /*FSW_OE*/);
}

__LOCAL void (__x86_raise_fpu_underflow)(void) {
	__x86_raise_fpu_mask(0x0010 /*FSW_UE*/);
}

__LOCAL void (__x86_raise_fpu_inexact)(void) {
	__x86_raise_fpu_mask(0x0020 /*FSW_PE*/);
}

#define __arch_feraiseexcept __arch_feraiseexcept
__LOCAL int (__arch_feraiseexcept)(int __excepts) {
	/* NOTE: The order here is important! */
	if ((__excepts & __FE_INVALID) != 0)
		__x86_raise_fpu_invalid();
	if ((__excepts & __FE_DIVBYZERO) != 0)
		__x86_raise_fpu_divbyzero();
	if ((__excepts & __FE_OVERFLOW) != 0)
		__x86_raise_fpu_overflow();
	if ((__excepts & __FE_UNDERFLOW) != 0)
		__x86_raise_fpu_underflow();
	if ((__excepts & __FE_INEXACT) != 0)
		__x86_raise_fpu_inexact();
	return 0;
}

#define __arch_feclearexcept __arch_feclearexcept
__LOCAL int __NOTHROW(__arch_feclearexcept)(int __excepts) {
	struct sfpuenv __env;
	__excepts &= __FE_ALL_EXCEPT;
	__fnstenv(&__env);
	__env.fe_fsw &= ~__excepts;
	__fldenv(&__env);
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		__mxscr &= ~__excepts;
		__ldmxcsr(__mxscr);
	}
	return 0;
}

/* @param: EXCEPTS: Set of `FE_*' */
#define __arch_fesetexcept __arch_fesetexcept
__LOCAL int __NOTHROW(__arch_fesetexcept)(int __excepts) {
	struct sfpuenv __env;
	__excepts &= __FE_ALL_EXCEPT;
	__fnstenv(&__env);
	__env.fe_fsw |= __excepts;
	__fldenv(&__env);
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		__mxscr |= __excepts;
		__ldmxcsr(__mxscr);
	}
	return 0;
}

#define __arch_fesetexceptflag __arch_fesetexceptflag
__LOCAL __ATTR_IN(1) int
__NOTHROW(__arch_fesetexceptflag)(__fexcept_t const *__flagp, int __excepts) {
	struct sfpuenv __env;
	__excepts &= __FE_ALL_EXCEPT;
	__fnstenv(&__env);
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__env.fe_fsw &= ~(__excepts & ~ *__flagp);
		__fldenv(&__env);
		__mxscr = __stmxcsr();
		__mxscr ^= (__mxscr ^ *__flagp) & __excepts;
		__ldmxcsr(__mxscr);
	} else {
		__env.fe_fsw ^= (__env.fe_fsw ^ *__flagp) & __excepts;
		__fldenv(&__env);
	}
	return 0;
}

#define __arch_fegetexcept __arch_fegetexcept
__LOCAL __ATTR_PURE __ATTR_WUNUSED __UINT16_TYPE__
__NOTHROW(__arch_fegetexcept)(void) {
	return __fstcw() & __FE_ALL_EXCEPT;
}

/* @param: EXCEPTS: Set of `FE_*'
 * @return: * : Set of `FE_*' */
#define __arch_fetestexcept __arch_fetestexcept
__LOCAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__arch_fetestexcept)(int __excepts) {
	__UINT16_TYPE__ __fsw;
	__excepts &= __FE_ALL_EXCEPT;
	__fsw = __fnstsw();
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		__fsw |= (__UINT16_TYPE__)__mxscr;
	}
	return __fsw & __excepts;
}



/* @return: * : The old set of enabled exceptions. */
#define __arch_feenableexcept __arch_feenableexcept
__LOCAL int
__NOTHROW(__arch_feenableexcept)(int __excepts) {
	__UINT16_TYPE__ __fcw, __res;
	__excepts &= __FE_ALL_EXCEPT;
	__fcw = __fstcw();
	__res = (~__fcw) & __FE_ALL_EXCEPT;
	__fcw &= ~__excepts;
	__fldcw(__fcw);
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		/* NOTE: 7 == ctz(MXCSR_IM), where `MXCSR_IM' is the first exception mask */
		__mxscr &= ~(__excepts << 7);
		__ldmxcsr(__mxscr);
	}
	return __res;
}

/* @return: * : The old set of enabled exceptions. */
#define __arch_fedisableexcept __arch_fedisableexcept
__LOCAL int
__NOTHROW(__arch_fedisableexcept)(int __excepts) {
	__UINT16_TYPE__ __fcw, __res;
	__excepts &= __FE_ALL_EXCEPT;
	__fcw = __fstcw();
	__res = (~__fcw) & __FE_ALL_EXCEPT;
	__fcw |= __excepts;
	__fldcw(__fcw);
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		/* NOTE: 7 == ctz(MXCSR_IM), where `MXCSR_IM' is the first exception mask */
		__mxscr |= __excepts << 7;
		__ldmxcsr(__mxscr);
	}
	return __res;
}





/* @return: * : One of `FE_TONEAREST', `FE_DOWNWARD', `FE_UPWARD', `FE_TOWARDZERO'. */
#define __arch_fegetround __arch_fegetround
__LOCAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__arch_fegetround)(void) {
	return __fnstcw() & 0x0c00 /*FCW_RC*/;
}

/* @param: ROUNDING_DIRECTION: One of `FE_TONEAREST', `FE_DOWNWARD', `FE_UPWARD', `FE_TOWARDZERO'.
 * @return: 0 : Success
 * @return: 1 : `ROUNDING_DIRECTION' was invalid. */
#define __arch_fesetround __arch_fesetround
__LOCAL int
__NOTHROW(__arch_fesetround)(int __rounding_direction) {
	__UINT16_TYPE__ __fcw;
	if ((__rounding_direction & ~0x0c00 /*FCW_RC*/) != 0)
		return 1; /* Invalid */
	__fcw = __fnstcw();
	__fcw = (__fcw & ~0x0c00 /*FCW_RC*/) | __rounding_direction;
	__fldcw(__fcw);
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		__mxscr &= ~MXCSR_RC;
		/* NOTE: 3 == (ctz(MXCSR_RC) - ctz(FCW_RC)) */
		__mxscr |= __rounding_direction << 3;
		__ldmxcsr(__mxscr);
	}
	return 0;
}




#define __arch_fegetenv __arch_fegetenv
__LOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__arch_fegetenv)(struct __fenv_struct *__restrict __envp) {
	__fnstenv((struct sfpuenv *)__envp);
	/* Must reload ENV to restore exception masks.
	 * s.a. doc for `__fnstenv()' */
	__fldenv((struct sfpuenv *)__envp);
	if (__CPU_HAVE_SSE()) {
		/* Need  to  store  the  mxcsr  mask  somewhere.
		 * Mirror what Glibc does and use the EIP field. */
		__envp->__eip = __stmxcsr();
	}
	return 0;
}

#define __arch_feholdexcept __arch_feholdexcept
__LOCAL __ATTR_NONNULL((1)) int
__NOTHROW(__arch_feholdexcept)(struct __fenv_struct *__restrict __envp) {
	__fnstenv((struct sfpuenv *)__envp);
	__fnclex();
	if (__CPU_HAVE_SSE()) {
		unsigned int xwork;
		__UINT32_TYPE__ __mscsr;
		/* Reminder: For Glibc compatibility, we store the MXCSR mask in EIP */
		__mscsr       = __stmxcsr();
		__envp->__eip = __mscsr;
		/* Disable all exceptions by masking them. */
		__mscsr |= (MXCSR_IM | MXCSR_DM | MXCSR_ZM | MXCSR_OM | MXCSR_UM | MXCSR_PM);
		/* Clear all of the sticky exception bits. */
		__mscsr &= ~(MXCSR_IE | MXCSR_DE | MXCSR_ZE | MXCSR_OE | MXCSR_UE | MXCSR_PE);
		__ldmxcsr(__mscsr);
	}
	return 0;
}

#define __arch_fesetenv __arch_fesetenv
__LOCAL __ATTR_NONNULL((1)) int
__NOTHROW(__arch_fesetenv)(struct __fenv_struct const *__restrict __envp) {
	struct sfpuenv __temp;
	__fnstenv(&__temp);
	if (__envp == __FE_DFL_ENV) {
		__temp.fe_fcw &= ~(FCW_RC_TRUNC);
		__temp.fe_fcw |= (FSW_IE | FSW_DE | FSW_ZE | FSW_OE | FSW_UE | FSW_PE | FCW_PC_EXTEND);
		__temp.fe_fsw &= ~(FSW_IE | FSW_DE | FSW_ZE | FSW_OE | FSW_UE | FSW_PE);
	} else if (__envp == __FE_NOMASK_ENV) {
		__temp.fe_fcw &= ~(FSW_IE | FSW_ZE | FSW_OE | FSW_UE | FSW_PE | FCW_RC_TRUNC);
		__temp.fe_fcw |= (FCW_DM | FCW_PC_EXTEND);
		__temp.fe_fsw &= ~(FSW_IE | FSW_DE | FSW_ZE | FSW_OE | FSW_UE | FSW_PE);
	} else {
		__temp.fe_fcw &= ~(FSW_IE | FSW_DE | FSW_ZE | FSW_OE | FSW_UE | FSW_PE | FCW_RC_TRUNC | FCW_PC_EXTEND);
		__temp.fe_fcw |= (__envp->__control_word & (FSW_IE | FSW_DE | FSW_ZE | FSW_OE | FSW_UE | FSW_PE | FCW_RC_TRUNC | FCW_PC_EXTEND));
		__temp.fe_fsw &= ~(FSW_IE | FSW_DE | FSW_ZE | FSW_OE | FSW_UE | FSW_PE);
		__temp.fe_fsw |= __envp->__status_word & (FSW_IE | FSW_DE | FSW_ZE | FSW_OE | FSW_UE | FSW_PE);
	}
	__temp.fe_fip = 0;
	__temp.fe_fcs = 0;
	__temp.fe_fop = 0;
	__temp.fe_fdp = 0;
	__temp.fe_fds = 0;
	__fldenv(&__temp);
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mscsr;
		__mscsr = __stmxcsr();
		if (__envp == __FE_DFL_ENV) {
			__mscsr &= ~(MXCSR_IE | MXCSR_DE | MXCSR_ZE | MXCSR_OE | MXCSR_UE | MXCSR_PE |
			             MXCSR_RC | MXCSR_FZ | MXCSR_DAZ);
			__mscsr |= (MXCSR_IM | MXCSR_DM | MXCSR_ZM | MXCSR_OM | MXCSR_UM | MXCSR_PM |
			            MXCSR_RC_NEAREST);
		} else if (__envp == __FE_NOMASK_ENV) {
			__mscsr &= ~(MXCSR_IE | MXCSR_DE | MXCSR_ZE | MXCSR_OE | MXCSR_UE | MXCSR_PE |
			             MXCSR_IM | MXCSR_ZM | MXCSR_OM | MXCSR_UM | MXCSR_PM |
			             MXCSR_RC | MXCSR_FZ | MXCSR_DAZ);
			__mscsr |= (MXCSR_DM | MXCSR_RC_NEAREST);
		} else {
			/* Reminder: For Glibc compatibility, we store the MXCSR mask in EIP */
			__mscsr = __envp->__eip;
		}
		__ldmxcsr(__mscsr);
	}
	return 0;
}

#define __arch_feupdateenv __arch_feupdateenv
__LOCAL __ATTR_NONNULL((1)) int
__NOTHROW(__arch_feupdateenv)(struct __fenv_struct const *__restrict __envp) {
	__UINT16_TYPE__ __fsw;
	__fsw = __fnstsw();
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		__fsw |= (__UINT16_TYPE__)__mxscr;
	}
	__arch_fesetenv(__envp);
	/* Re-raise all previously active exceptions. */
	/*__fsw &= __FE_ALL_EXCEPT;*/
	__arch_feraiseexcept(__fsw);
	return 0;
}



#define __arch_fegetmode __arch_fegetmode
__LOCAL __ATTR_OUT(1) int
__NOTHROW_NCX(__arch_fegetmode)(__femode_t *__restrict __modep) {
	__modep->__control_word = __fnstcw();
	if (__CPU_HAVE_SSE())
		__modep->__mxcsr = __stmxcsr();
	return 0;
}

#define __arch_fesetmode __arch_fesetmode
__LOCAL __ATTR_IN(1) int
__NOTHROW_NCX(__arch_fesetmode)(__femode_t const *__restrict __modep) {
	__fldcw((__modep == __FE_DFL_MODE)
	        ? 0x137f /*_FPU_DEFAULT*/
	        : __modep->__control_word);
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxcsr = __stmxcsr();
		__mxcsr &= __FE_ALL_EXCEPT_X86;
		__mxcsr |= (__modep == __FE_DFL_MODE)
		           ? __FE_ALL_EXCEPT_X86 << 7
		           : __modep->__mxcsr & ~__FE_ALL_EXCEPT_X86;
		__ldmxcsr(__mxcsr);
	}
	return 0;
}



__SYSDECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#include "../../../bits/crt/fenv-impl.h"

#endif /* !_I386_KOS_BITS_CRT_FENV_IMPL_H */
