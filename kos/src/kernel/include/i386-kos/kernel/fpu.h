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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_FPU_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_FPU_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kos/kernel/fpu-state.h>

DECL_BEGIN

#ifndef CONFIG_NO_FPU
#define CONFIG_FPU 1
#else /* !CONFIG_NO_FPU */
#undef CONFIG_FPU
#endif /* CONFIG_NO_FPU */

#define FPU_STATE_SSTATE 0 /* `struct sfpustate' is used */
#define FPU_STATE_XSTATE 1 /* `struct xfpustate' is used */

#ifndef CONFIG_NO_FPU
#ifdef __CC__

/* [const] The type of FPU state used (One of `FPU_STATE_*') */
DATDEF unsigned int const x86_fpustate_variant;

/* [0..1] The task associated with the current FPU register contents, or NULL if none.
 * NOTE: When accessing this field, preemption must be disabled, as
 *       this field affects the behavior of task state switches. */
DATDEF ATTR_PERCPU struct task *thiscpu_x86_fputhread;

/* [0..1][lock(WRITE_ONCE)][owned]
 * The per-task FPU state (lazily allocated) */
DATDEF ATTR_PERTASK struct fpustate *this_x86_fpustate;

/* Save/Load the register state of the FPU unit.
 * NOTE: `x86_fpustate_save()' may reset the active FPU context before
 *        returning. - If this isn't intended, `x86_fpustate_save_noreset()'
 *        must be used, which will leave the current FPU state unchanged. */
FUNDEF NOBLOCK void FCALL x86_fpustate_load(struct fpustate const *__restrict state);
FUNDEF NOBLOCK void FCALL x86_fpustate_save(struct fpustate *__restrict state);
FUNDEF NOBLOCK void FCALL x86_fpustate_save_noreset(struct fpustate *__restrict state);
FUNDEF NOBLOCK void NOTHROW(FCALL x86_fpustate_init)(struct fpustate *__restrict state);


/* Allocate / free FPU state structures. */
FUNDEF WUNUSED ATTR_RETNONNULL ATTR_MALLOC struct fpustate *KCALL fpustate_alloc(void);
FUNDEF WUNUSED ATTR_MALLOC struct fpustate *NOTHROW(KCALL fpustate_alloc_nx)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL fpustate_free)(struct fpustate *__restrict self);

/* Ensure that `this_x86_fpustate' has been allocated, allocating
 * and initializing it now if it hasn't already. */
FUNDEF void KCALL fpustate_init(void) THROWS(E_BADALLOC);
FUNDEF WUNUSED bool NOTHROW(KCALL fpustate_init_nx)(void);

/* Save the FPU context of the calling thread.
 * This functions are no-ops if the calling thread wasn't the
 * last one to use the FPU, or has never used the FPU at all. */
FUNDEF NOBLOCK void NOTHROW(KCALL fpustate_save)(void);

/* Similar to `fpustate_save()', but save the state of whichever thread is
 * currently holding the active FPU context. - When called, this function
 * will ensure that the most-up-to-date FPU context is written to memory,
 * and will be read back from memory the next time that thread (if any)
 * performs another FPU operation.
 * The main purpose of this function is to aid in implementing FPU support
 * in debuggers, where this function is called when suspending execution of
 * the associated CPU, after which the debugger can read/write FPU information
 * for any thread by simply looking at `PERTASK(thread, this_x86_fpustate)' */
FUNDEF NOBLOCK void NOTHROW(KCALL fpustate_savecpu)(void);


/* Load / Save the FPU context of the calling thread to/from the given `state'
 * If no FPU state had yet to be allocated when `fpustate_loadfrom()' is called,
 * a new state will be allocated before returning. */
FUNDEF NOBLOCK void KCALL fpustate_loadfrom(USER CHECKED struct fpustate const *state) THROWS(E_SEGFAULT, E_BADALLOC);
FUNDEF NOBLOCK void KCALL fpustate_saveinto(USER CHECKED struct fpustate *state) THROWS(E_SEGFAULT);


/* Same as the instructions of the same name, but
 * emulated if those instructions aren't supported.
 * NOTE: On x86_64, `x86_fxsave()' and `x86_fxrstor()' map to the 64-bit variants of the
 *       individual instruction. - To use the 32-bit variants, use the functions below. */
FUNDEF NOBLOCK void FCALL x86_fxsave(USER CHECKED struct xfpustate *state) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void FCALL x86_fxrstor(USER CHECKED struct xfpustate const *state) THROWS(E_SEGFAULT);
#ifdef __x86_64__
struct xfpustate32;
FUNDEF NOBLOCK void FCALL x86_fxsave32(USER CHECKED struct xfpustate32 *state) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void FCALL x86_fxrstor32(USER CHECKED struct xfpustate32 const *state) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void FCALL x86_fxsave64(USER CHECKED struct xfpustate *state) ASMNAME("x86_fxsave") THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void FCALL x86_fxrstor64(USER CHECKED struct xfpustate const *state) ASMNAME("x86_fxrstor") THROWS(E_SEGFAULT);
#else /* __x86_64__ */
FUNDEF NOBLOCK void FCALL x86_fxsave32(USER CHECKED struct xfpustate *state) ASMNAME("x86_fxsave") THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void FCALL x86_fxrstor32(USER CHECKED struct xfpustate const *state) ASMNAME("x86_fxrstor") THROWS(E_SEGFAULT);
#endif /* !__x86_64__ */

/* The value that will always be written to `struct xfpustate::fs_mxcsr_mask' */
DATDEF u32 const x86_fxsave_mxcsr_mask;




#ifdef __x86_64__
struct fpustate32;
FUNDEF NOBLOCK void KCALL fpustate32_loadfrom(USER CHECKED struct fpustate32 const *state) THROWS(E_SEGFAULT, E_BADALLOC);
FUNDEF NOBLOCK void KCALL fpustate32_saveinto(USER CHECKED struct fpustate32 *state) THROWS(E_SEGFAULT);
#else /* __x86_64__ */
#define fpustate32_loadfrom fpustate_loadfrom
#define fpustate32_saveinto fpustate_saveinto
#endif /* !__x86_64__ */


#endif /* __CC__ */
#endif /* !CONFIG_NO_FPU */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_FPU_H */
