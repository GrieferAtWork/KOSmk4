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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_RT_EXCEPT_PERSONALITY_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_RT_EXCEPT_PERSONALITY_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

/* Use fastcall on i386 */
#ifdef __x86_64__
#define EXCEPT_PERSONALITY_CC KCALL
#else /* __x86_64__ */
#define EXCEPT_PERSONALITY_CC __ATTR_FASTCALL
#endif /* !__x86_64__ */

#ifdef __CC__
DECL_BEGIN

struct _Unwind_Context;

/* Pre-defined personality functions */
#ifdef BUILDING_KERNEL_CORE
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC x86_syscall_personality_asm32_int80)(struct _Unwind_Context *__restrict context);
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC x86_syscall_personality_asm32_sysenter)(struct _Unwind_Context *__restrict context);
#ifdef __x86_64__
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC x86_syscall_personality_asm64_syscall)(struct _Unwind_Context *__restrict context);
#endif /* __x86_64__ */
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC x86_xintr3_userexcept_personality)(struct _Unwind_Context *__restrict context);
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC x86_xintr2_userexcept_personality)(struct _Unwind_Context *__restrict context);
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC x86_xintr1_userexcept_personality)(struct _Unwind_Context *__restrict context);
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC syscall_emulate_r_personality)(struct _Unwind_Context *__restrict context);
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC driver_initializer_personality)(struct _Unwind_Context *__restrict context);
#endif /* BUILDING_KERNEL_CORE */
FUNDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC x86_asm_except_personality)(struct _Unwind_Context *__restrict context);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_RT_EXCEPT_PERSONALITY_H */
