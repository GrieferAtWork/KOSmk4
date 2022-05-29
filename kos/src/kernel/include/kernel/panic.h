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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_PANIC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_PANIC_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#include <hybrid/typecore.h>

DECL_BEGIN

#ifdef __CC__
struct ucpustate;
struct lcpustate;
struct kcpustate;
struct icpustate;
struct scpustate;
struct fcpustate;

/* Set of kernel poison flags. When the kernel panics, all bits
 * of this variable are set to 1, but some can be cleared  once
 * again as the result of certain actions being performed. */
DATDEF __UINT8_TYPE__ const _kernel_poisoned;
#define _KERNEL_POISON_PANIC       0x01 /* Kernel poison bit: Use this to restrict system  functions
                                         *                    and select less error-prone code path.
                                         * This bit can be cleared by the debugger `unpanic' command. */
#define _KERNEL_POISON_FORCEDELMOD 0x40 /* Module unload was forced. (s.a. `DRIVER_DELMOD_F_FORCE') */
#define _KERNEL_POISON_NO_WARRANTY 0x80 /* System warranty expired. Don't use this to restrict access,
                                         * but do use it if  you're looking for reasons why  something
                                         * about your code failed. If this bit is set, the system  was
                                         * in  an unstable state to begin with, and stuff breaking may
                                         * not be your fault.
                                         * Unlike other bits, this one _cannot_ be cleared (or at least
                                         * isn't meant to ever be cleared once set), and should be used
                                         * to choose more-stable/free-standing  algorithms over  others
                                         * that may be faster/more-integrated.
                                         * But DONT use this bit to turn an optional function into a
                                         * no-op!  Use  `_KERNEL_POISON_PANIC'  for  that   purpose! */

/* Returns non-zero if the kernel has been poisoned.
 * This is the case after any of the panic functions have been  called,
 * or an assertion failure/check was triggered. - Basically, it is non-
 * zero when the kernel may be in an inconsistent state. */
#define kernel_poisoned() (_kernel_poisoned & _KERNEL_POISON_PANIC)

/* Check if system warranty has expired. Warranty expires the first
 * time the kernel panics and cannot (or rather: should not) be re-
 * enabled.
 * In most cases, you should use `kernel_poisoned()' instead!
 * @return: true:  System warranty is still OK
 * @return: false: At one point, the system experienced a panic. */
#define kernel_warranty() (!(_kernel_poisoned & _KERNEL_POISON_NO_WARRANTY))


/* Poison the kernel.
 * This operation cannot be undone and may (under rare  circumstances)
 * itself cause the kernel to crash (due to race conditions with other
 * CPUs).  Use  with  caution,  or  better  yet:  Don't  use  at  all!
 * Additionally, this function will attempt to fix some common  system
 * integrity violations in order to  allow other kernel panic code  to
 * at least somewhat function correctly. (as far as that may still  be
 * possible,  given that  this function is  meant to be  used when the
 * kernel has become unstable) */
FUNDEF NOBLOCK ATTR_COLD void NOTHROW(KCALL _kernel_poison)(void);

#ifdef CONFIG_HAVE_DEBUGGER
#define ATTR_KERNEL_PANIC_NORETURN /* nothing */
#else /* CONFIG_HAVE_DEBUGGER */
#define ATTR_KERNEL_PANIC_NORETURN ATTR_NORETURN
#endif /* !CONFIG_HAVE_DEBUGGER */

/* Set kernel poison bits. */
#define kernel_poison(what) __hybrid_atomic_or(_kernel_private_poisoned_wr, what, __ATOMIC_SEQ_CST)
DATDEF __UINT8_TYPE__ _kernel_private_poisoned_wr ASMNAME("_kernel_poisoned");


/* Cause kernel panic. */
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void FCALL kernel_panic_here(void);
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void FCALL kernel_panic_here_n(unsigned int n_skip);
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void VCALL kernel_panic(char const *format, ...);
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void VCALL kernel_panic_n(unsigned int n_skip, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic_ucpustate)(struct ucpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic_ucpustate_n)(unsigned int n_skip, struct ucpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic_lcpustate)(struct lcpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic_lcpustate_n)(unsigned int n_skip, struct lcpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic_kcpustate)(struct kcpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic_kcpustate_n)(unsigned int n_skip, struct kcpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic_icpustate)(struct icpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic_icpustate_n)(unsigned int n_skip, struct icpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic_scpustate)(struct scpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic_scpustate_n)(unsigned int n_skip, struct scpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic_fcpustate)(struct fcpustate *__restrict state, char const *format, ...);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic_fcpustate_n)(unsigned int n_skip, struct fcpustate *__restrict state, char const *format, ...);
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void FCALL kernel_vpanic(char const *format, __builtin_va_list args);
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void FCALL kernel_vpanic_n(unsigned int n_skip, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic_ucpustate)(struct ucpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic_ucpustate_n)(unsigned int n_skip, struct ucpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic_lcpustate)(struct lcpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic_lcpustate_n)(unsigned int n_skip, struct lcpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic_kcpustate)(struct kcpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic_kcpustate_n)(unsigned int n_skip, struct kcpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic_icpustate)(struct icpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic_icpustate_n)(unsigned int n_skip, struct icpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic_scpustate)(struct scpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic_scpustate_n)(unsigned int n_skip, struct scpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic_fcpustate)(struct fcpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic_fcpustate_n)(unsigned int n_skip, struct fcpustate *__restrict state, char const *format, __builtin_va_list args);

#ifdef __cplusplus
extern "C++" {
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void FCALL kernel_panic(void) ASMNAME("kernel_panic_here");
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void FCALL kernel_panic(unsigned int n_skip) ASMNAME("kernel_panic_here_n");
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void VCALL kernel_panic(unsigned int n_skip, char const *format, ...) ASMNAME("kernel_panic_n");
FUNDEF ATTR_KERNEL_PANIC_NORETURN ATTR_COLD void FCALL kernel_vpanic(unsigned int n_skip, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic)(struct ucpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_ucpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic)(unsigned int n_skip, struct ucpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_ucpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic)(struct lcpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_lcpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic)(unsigned int n_skip, struct lcpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_lcpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic)(struct kcpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_kcpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic)(unsigned int n_skip, struct kcpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_kcpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic)(struct icpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_icpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic)(unsigned int n_skip, struct icpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_icpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic)(struct scpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_scpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic)(unsigned int n_skip, struct scpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_scpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(VCALL kernel_panic)(struct fcpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_fcpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(VCALL kernel_panic)(unsigned int n_skip, struct fcpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_fcpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic)(struct ucpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_ucpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic)(unsigned int n_skip, struct ucpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_ucpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic)(struct lcpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_lcpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic)(unsigned int n_skip, struct lcpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_lcpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic)(struct kcpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_kcpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic)(unsigned int n_skip, struct kcpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_kcpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic)(struct icpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_icpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic)(unsigned int n_skip, struct icpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_icpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic)(struct scpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_scpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic)(unsigned int n_skip, struct scpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_scpustate_n");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((1)) void NOTHROW(FCALL kernel_vpanic)(struct fcpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_fcpustate");
FUNDEF ABNORMAL_RETURN ATTR_COLD ATTR_NORETURN NONNULL((2)) void NOTHROW(FCALL kernel_vpanic)(unsigned int n_skip, struct fcpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_fcpustate_n");
} /* extern "C++" */
#endif /* __cplusplus */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_PANIC_H */
