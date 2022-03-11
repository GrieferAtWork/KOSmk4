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
#ifndef _I386_KOS_BITS_CRT_FENV_INLINE_H
#define _I386_KOS_BITS_CRT_FENV_INLINE_H 1

#include <__stdinc.h>

#ifndef __NO_FPU
#include <hybrid/__assert.h>
#include <hybrid/typecore.h>

#include <asm/cpu-flags.h>
#include <asm/intrin-cpuid.h>
#include <asm/intrin-fpu.h>
#include <bits/crt/fenv.h>
#include <kos/kernel/fpu-sstate.h>

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
	__x86_raise_fpu_mask(FSW_OE);
}

__LOCAL void (__x86_raise_fpu_underflow)(void) {
	__x86_raise_fpu_mask(FSW_UE);
}

__LOCAL void (__x86_raise_fpu_inexact)(void) {
	__x86_raise_fpu_mask(FSW_PE);
}

/* @param: EXCEPTS: Set of `FE_*' */
#define __inline_feraiseexcept __inline_feraiseexcept
__LOCAL void (__inline_feraiseexcept)(int __excepts) {
	/* NOTE: The order here is important! */
	if ((__excepts & FE_INVALID) != 0)
		__x86_raise_fpu_invalid();
	if ((__excepts & FE_DIVBYZERO) != 0)
		__x86_raise_fpu_divbyzero();
	if ((__excepts & FE_OVERFLOW) != 0)
		__x86_raise_fpu_overflow();
	if ((__excepts & FE_UNDERFLOW) != 0)
		__x86_raise_fpu_underflow();
	if ((__excepts & FE_INEXACT) != 0)
		__x86_raise_fpu_inexact();
}

/* @param: EXCEPTS: Set of `FE_*' */
#define __inline_feclearexcept __inline_feclearexcept
__LOCAL void __NOTHROW(__inline_feclearexcept)(int __excepts) {
	struct sfpuenv __env;
	__excepts &= FE_ALL_EXCEPT;
	__fnstenv(&__env);
	__env.fe_fsw &= ~__excepts;
	__fldenv(&__env);
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		__mxscr &= ~__excepts;
		__ldmxcsr(__mxscr);
	}
}

#define __inline_fegetenv __inline_fegetenv
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__inline_fegetenv)(struct __fenv_struct *__restrict __envp) {
	__fnstenv((struct sfpuenv *)__envp);
	/* Must reload ENV to restore exception masks.
	 * s.a. doc for `__fnstenv()' */
	__fldenv((struct sfpuenv *)__envp);
	if (__CPU_HAVE_SSE()) {
		/* Need  to  store  the  mxcsr  mask  somewhere.
		 * Mirror what Glibc does and use the EIP field. */
		__envp->__eip = __stmxcsr();
	}
}

#define __inline_fegetexcept __inline_fegetexcept
__LOCAL __ATTR_PURE __ATTR_WUNUSED __UINT16_TYPE__
__NOTHROW(__inline_fegetexcept)(void) {
	return __fstcw() & FE_ALL_EXCEPT;
}

/* @return: * : The old set of enabled exceptions. */
#define __inline_feenableexcept __inline_feenableexcept
__LOCAL int
__NOTHROW(__inline_feenableexcept)(int __excepts) {
	__UINT16_TYPE__ __fcw, __res;
	__excepts &= FE_ALL_EXCEPT;
	__fcw = __fstcw();
	__res = (~__fcw) & FE_ALL_EXCEPT;
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
#define __inline_fedisableexcept __inline_fedisableexcept
__LOCAL int
__NOTHROW(__inline_fedisableexcept)(int __excepts) {
	__UINT16_TYPE__ __fcw, __res;
	__excepts &= FE_ALL_EXCEPT;
	__fcw = __fstcw();
	__res = (~__fcw) & FE_ALL_EXCEPT;
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
#define __inline_fegetround __inline_fegetround
__LOCAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__inline_fegetround)(void) {
	return __fnstcw() & FCW_RC;
}


/* @param: ROUNDING_DIRECTION: One of `FE_TONEAREST', `FE_DOWNWARD', `FE_UPWARD', `FE_TOWARDZERO'.
 * @return: 0 : Success
 * @return: 1 : `ROUNDING_DIRECTION' was invalid. */
#define __inline_fesetround __inline_fesetround
__LOCAL int
__NOTHROW(__inline_fesetround)(int __rounding_direction) {
	__UINT16_TYPE__ __fcw;
	if ((__rounding_direction & ~FCW_RC) != 0)
		return 1; /* Invalid */
	__fcw = __fnstcw();
	__fcw = (__fcw & ~FCW_RC) | __rounding_direction;
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


/* @param: EXCEPTS: Set of `FE_*'
 * @return: * : Set of `FE_*' */
#define __inline_fetestexcept __inline_fetestexcept
__LOCAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__inline_fetestexcept)(int __excepts) {
	__UINT16_TYPE__ __fsw;
	__excepts &= FE_ALL_EXCEPT;
	__fsw = __fnstsw();
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		__fsw |= (__UINT16_TYPE__)__mxscr;
	}
	return __fsw & __excepts;
}

#define __inline_feholdexcept __inline_feholdexcept
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(__inline_feholdexcept)(struct __fenv_struct *__restrict __envp) {
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
}

#define __inline_fesetenv __inline_fesetenv
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(__inline_fesetenv)(struct __fenv_struct const *__restrict __envp) {
	struct sfpuenv __temp;
	__fnstenv(&__temp);
	if (__envp == FE_DFL_ENV) {
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
		if (__envp == FE_DFL_ENV) {
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
}


#define __inline_feupdateenv __inline_feupdateenv
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(__inline_feupdateenv)(struct __fenv_struct const *__restrict __envp) {
	__UINT16_TYPE__ __fsw;
	__fsw = __fnstsw();
	if (__CPU_HAVE_SSE()) {
		__UINT32_TYPE__ __mxscr;
		__mxscr = __stmxcsr();
		__fsw |= (__UINT16_TYPE__)__mxscr;
	}
	__inline_fesetenv(__envp);
	/* Re-raise all previously active exceptions. */
	/*__fsw &= FE_ALL_EXCEPT;*/
	__inline_feraiseexcept(__fsw);
}

__SYSDECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#include "../../../bits/crt/fenv-inline.h"

#endif /* !_I386_KOS_BITS_CRT_FENV_INLINE_H */
