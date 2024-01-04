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
#ifndef _KOS_KERNEL_BITS_CPU_STATE_HELPERS_H
#define _KOS_KERNEL_BITS_CPU_STATE_HELPERS_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/kernel/cpu-state.h>

/* These are the cpu-state helpers that may be used portably across all architectures:
 * - pc: Program Counter
 * - sp: Stack Pointer
 *
 * Architectures may define additional macros to get/set arch-specific registers.
 */
#ifdef __CC__
#define ucpustate_getpc(state)     ((__byte_t const *)(state)->__u_pad[0])
#define ucpustate_setpc(state, pc) (void)((state)->__u_pad[0] = (__uintptr_t)__COMPILER_REQTYPE(void const *, pc))
#define ucpustate_getsp(state)     ((__byte_t *)(state)->__u_pad[1])
#define ucpustate_setsp(state, sp) (void)((state)->__u_pad[1] = (__uintptr_t)__COMPILER_REQTYPE(void const *, sp))

#define lcpustate_getpc(state)     ((__byte_t const *)(state)->__l_pad[0])
#define lcpustate_setpc(state, pc) (void)((state)->__l_pad[0] = (__uintptr_t)__COMPILER_REQTYPE(void const *, pc))
#define lcpustate_getsp(state)     ((__byte_t *)(state)->__l_pad[1])
#define lcpustate_setsp(state, sp) (void)((state)->__l_pad[1] = (__uintptr_t)__COMPILER_REQTYPE(void const *, sp))

#define kcpustate_getpc(state)     ((__byte_t const *)(state)->__k_pad[0])
#define kcpustate_setpc(state, pc) (void)((state)->__k_pad[0] = (__uintptr_t)__COMPILER_REQTYPE(void const *, pc))
#define kcpustate_getsp(state)     ((__byte_t *)(state)->__k_pad[1])
#define kcpustate_setsp(state, sp) (void)((state)->__k_pad[1] = (__uintptr_t)__COMPILER_REQTYPE(void const *, sp))

#define icpustate_getpc(state)     ((__byte_t const *)(state)->__i_pad[0])
#define icpustate_setpc(state, pc) (void)((state)->__i_pad[0] = (__uintptr_t)__COMPILER_REQTYPE(void const *, pc))
#define icpustate_getsp(state)     ((__byte_t *)(state)->__i_pad[1])
#define icpustate_setsp(state, sp) (void)((state)->__i_pad[1] = (__uintptr_t)__COMPILER_REQTYPE(void const *, sp))

#define scpustate_getpc(state)     ((__byte_t const *)(state)->__s_pad[0])
#define scpustate_setpc(state, pc) (void)((state)->__s_pad[0] = (__uintptr_t)__COMPILER_REQTYPE(void const *, pc))
#define scpustate_getsp(state)     ((__byte_t *)(state)->__s_pad[1])
#define scpustate_setsp(state, sp) (void)((state)->__s_pad[1] = (__uintptr_t)__COMPILER_REQTYPE(void const *, sp))

#define fcpustate_getpc(state)     ((__byte_t const *)(state)->__f_pad[0])
#define fcpustate_setpc(state, pc) (void)((state)->__f_pad[0] = (__uintptr_t)__COMPILER_REQTYPE(void const *, pc))
#define fcpustate_getsp(state)     ((__byte_t *)(state)->__f_pad[1])
#define fcpustate_setsp(state, sp) (void)((state)->__f_pad[1] = (__uintptr_t)__COMPILER_REQTYPE(void const *, sp))
#endif /* __CC__ */

#endif /* !_KOS_KERNEL_BITS_CPU_STATE_HELPERS_H */
