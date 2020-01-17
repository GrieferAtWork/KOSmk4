/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_PANIC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_PANIC_H 1

#include <kernel/compiler.h>

DECL_BEGIN

#ifdef __CC__
struct ucpustate;
struct lcpustate;
struct kcpustate;
struct icpustate;
struct scpustate;

/* Returns non-zero if the kernel has been poisoned.
 * This is the case after any of the panic functions have been called,
 * or an assertion failure/check was triggered. - Basically, it is non-
 * zero when the kernel may be in an inconsistent state. */
#define kernel_poisoned() 0

/* Cause kernel panic. */
FUNDEF ATTR_NORETURN ATTR_COLD void KCALL kernel_panic_here(void);
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic(char const *format, ...);
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic_ucpustate(struct ucpustate *__restrict state, char const *format, ...);
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic_lcpustate(struct lcpustate *__restrict state, char const *format, ...);
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic_kcpustate(struct kcpustate *__restrict state, char const *format, ...);
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic_icpustate(struct icpustate *__restrict state, char const *format, ...);
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic_scpustate(struct scpustate *__restrict state, char const *format, ...);
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic(char const *format, __builtin_va_list args);
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic_ucpustate(struct ucpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic_lcpustate(struct lcpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic_kcpustate(struct kcpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic_icpustate(struct icpustate *__restrict state, char const *format, __builtin_va_list args);
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic_scpustate(struct scpustate *__restrict state, char const *format, __builtin_va_list args);

#ifdef __cplusplus
extern "C++" {
FUNDEF ATTR_NORETURN ATTR_COLD void KCALL kernel_panic(void) ASMNAME("kernel_panic_here");
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic(struct ucpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_ucpustate");
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic(struct lcpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_lcpustate");
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic(struct kcpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_kcpustate");
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic(struct icpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_icpustate");
FUNDEF ATTR_NORETURN ATTR_COLD void VCALL kernel_panic(struct scpustate *__restrict state, char const *format, ...) ASMNAME("kernel_panic_scpustate");
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic(struct ucpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_ucpustate");
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic(struct lcpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_lcpustate");
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic(struct kcpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_kcpustate");
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic(struct icpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_icpustate");
FUNDEF ATTR_NORETURN ATTR_COLD void FCALL kernel_vpanic(struct scpustate *__restrict state, char const *format, __builtin_va_list args) ASMNAME("kernel_vpanic_scpustate");
}
#endif /* __cplusplus */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_PANIC_H */
