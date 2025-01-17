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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_H
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_H 1

/* TODO: `handle_breakpoint.c' */
/* TODO: Get rid of this header. - All functionality here should instead come from libemu86! */

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <libemu86/emu86.h>

DECL_BEGIN

/* Instruction flags. */
struct icpustate;

/* @param: regno: One of `R_*' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u16
NOTHROW(FCALL x86_icpustate_get16)(struct icpustate *__restrict state, u8 regno);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u32
NOTHROW(FCALL x86_icpustate_get32)(struct icpustate *__restrict state, u8 regno);
#ifdef __x86_64__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) u64
NOTHROW(FCALL x86_icpustate_get64)(struct icpustate *__restrict state, u8 regno);
#define x86_icpustate_get(state, regno) x86_icpustate_get64(state, regno)
#else /* __x86_64__ */
#define x86_icpustate_get(state, regno) x86_icpustate_get32(state, regno)
#endif /* !__x86_64__ */


INTDEF uintptr_t KCALL
x86_decode_modrmgetmem(struct icpustate *__restrict state,
                       struct emu86_modrm *__restrict modrm,
                       emu86_opflags_t flags);

/* Access the register or memory location described by a MODRM instruction. */
INTDEF u16 KCALL
modrm_getrmw(struct icpustate *__restrict state,
             struct emu86_modrm *__restrict modrm,
             emu86_opflags_t flags) THROWS(E_SEGFAULT);
#define modrm_getregw(state, modrm, flags) x86_icpustate_get16(state, (modrm)->mi_reg)
#define modrm_getregl(state, modrm, flags) x86_icpustate_get32(state, (modrm)->mi_reg)

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_DECODE_H */
