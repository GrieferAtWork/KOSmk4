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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_FPU_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_FPU_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_HAVE_FPU
#include <kernel/types.h>
#include <kos/kernel/fpu-state.h>

#define FPU_STATE_SSTATE 0 /* `struct sfpustate' is used */
#define FPU_STATE_XSTATE 1 /* `struct xfpustate' is used */

#ifdef __CC__
DECL_BEGIN

/* [const] The type of FPU state used (One of `FPU_STATE_*') */
DATDEF unsigned int const x86_fpustate_variant; /* TODO: Refactor documentation -- This should be the "preferred" variant */

/* Save/Load the register state of the FPU unit (always uses `x86_fpustate_variant').
 * NOTE: `x86_fpustate_save()'  may  reset  the active  FPU  context before
 *       returning. - If this isn't intended, `x86_fpustate_save_noreset()'
 *       must  be used, which  will leave the  current FPU state unchanged. */
FUNDEF NOBLOCK void FCALL x86_fpustate_load(struct fpustate const *__restrict state);
FUNDEF NOBLOCK void FCALL x86_fpustate_save(struct fpustate *__restrict state);
FUNDEF NOBLOCK void FCALL x86_fpustate_save_noreset(struct fpustate *__restrict state);
FUNDEF NOBLOCK void NOTHROW(FCALL x86_fpustate_init)(struct fpustate *__restrict state);


/* Same as the instructions  of the same name,  but
 * emulated if those instructions aren't supported.
 * NOTE: On x86_64, `x86_fxsave()' and `x86_fxrstor()' map to the 64-bit variants of the
 *       individual instruction. - To use the 32-bit variants, use the functions  below. */
FUNDEF NOBLOCK void FCALL x86_fxsave(NCX struct xfpustate *state) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void FCALL x86_fxrstor(NCX struct xfpustate const *state) THROWS(E_SEGFAULT);
#ifdef __x86_64__
struct xfpustate32;
FUNDEF NOBLOCK void FCALL x86_fxsave32(NCX struct xfpustate32 *state) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void FCALL x86_fxrstor32(NCX struct xfpustate32 const *state) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void FCALL x86_fxsave64(NCX struct xfpustate *state) THROWS(E_SEGFAULT) ASMNAME("x86_fxsave");
FUNDEF NOBLOCK void FCALL x86_fxrstor64(NCX struct xfpustate const *state) THROWS(E_SEGFAULT) ASMNAME("x86_fxrstor");
#else /* __x86_64__ */
FUNDEF NOBLOCK void FCALL x86_fxsave32(NCX struct xfpustate *state) THROWS(E_SEGFAULT) ASMNAME("x86_fxsave");
FUNDEF NOBLOCK void FCALL x86_fxrstor32(NCX struct xfpustate const *state) THROWS(E_SEGFAULT) ASMNAME("x86_fxrstor");
#endif /* !__x86_64__ */

/* The value that will always be written to `struct xfpustate::fs_mxcsr_mask' */
DATDEF u32 const x86_fxsave_mxcsr_mask;

#ifdef __x86_64__
struct fpustate32;
FUNDEF NOBLOCK void FCALL
fpustate32_loadfrom(NCX struct fpustate32 const *state)
		THROWS(E_SEGFAULT, E_BADALLOC);
FUNDEF NOBLOCK void FCALL
fpustate32_saveinto(NCX struct fpustate32 *state)
		THROWS(E_SEGFAULT);
#define fpustate64_loadfrom fpustate_loadfrom
#define fpustate64_saveinto fpustate_saveinto
#else /* __x86_64__ */
#define fpustate32_loadfrom fpustate_loadfrom
#define fpustate32_saveinto fpustate_saveinto
#endif /* !__x86_64__ */

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_HAVE_FPU */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_FPU_H */
