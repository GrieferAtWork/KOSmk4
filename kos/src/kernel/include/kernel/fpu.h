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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FPU_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FPU_H 1

#include <kernel/compiler.h>

/*[[[config CONFIG_HAVE_FPU = true]]]*/
#ifdef CONFIG_NO_FPU
#undef CONFIG_HAVE_FPU
#elif !defined(CONFIG_HAVE_FPU)
#define CONFIG_HAVE_FPU
#elif (-CONFIG_HAVE_FPU - 1) == -1
#undef CONFIG_HAVE_FPU
#define CONFIG_NO_FPU
#endif /* ... */
/*[[[end]]]*/

#ifdef CONFIG_HAVE_FPU
#include <kernel/arch/fpu.h>
#ifdef CONFIG_HAVE_FPU
#include <kos/kernel/fpu-state.h>

#ifdef __CC__
DECL_BEGIN

struct fpustate;

/* [0..1] The task associated with the current FPU register contents, or NULL if none.
 * NOTE: When accessing this field, preemption must be disabled, as
 *       this field affects  the behavior of  task state  switches. */
#ifndef ARCH_FPU_ARCHHEADER_DEFINES_THISCPU_FPUTHREAD
DATDEF ATTR_PERCPU struct task *thiscpu_fputhread;
#endif /* !ARCH_FPU_ARCHHEADER_DEFINES_THISCPU_FPUTHREAD */

/* [0..1][lock(WRITE_ONCE)][owned]
 * The per-task FPU state (lazily allocated) */
#ifndef ARCH_FPU_ARCHHEADER_DEFINES_THIS_FPUSTATE
DATDEF ATTR_PERTASK struct fpustate *this_fpustate;
#endif /* !ARCH_FPU_ARCHHEADER_DEFINES_THIS_FPUSTATE */


/* Allocate / free FPU state structures. */
#ifndef ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_ALLOC
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED struct fpustate *KCALL fpustate_alloc(void);
FUNDEF ATTR_MALLOC WUNUSED struct fpustate *NOTHROW(KCALL fpustate_alloc_nx)(void);
#endif /* !ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_ALLOC */
#ifndef ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_FREE
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL fpustate_free)(struct fpustate *__restrict self);
#endif /* !ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_FREE */

/* Ensure that `this_fpustate' has been allocated, allocating
 * and initializing it now if that hasn't been done  already. */
#ifndef ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_INIT
FUNDEF void KCALL fpustate_init(void) THROWS(E_BADALLOC);
FUNDEF WUNUSED __BOOL NOTHROW(KCALL fpustate_init_nx)(void);
#endif /* !ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_INIT */

/* Save the FPU context of the calling thread.
 * This functions are no-ops if the calling thread wasn't the
 * last one to use the FPU, or has never used the FPU at all. */
#ifndef ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_SAVE
FUNDEF NOBLOCK void NOTHROW(KCALL fpustate_save)(void);
#endif /* !ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_SAVE */

/* Similar to `fpustate_save()', but save the state of whichever thread is
 * currently  holding the active FPU context. - When called, this function
 * will  ensure that the most-up-to-date FPU context is written to memory,
 * and will be read back  from memory the next  time that thread (if  any)
 * performs another FPU operation.
 * The main purpose  of this function  is to aid  in implementing FPU  support
 * in  debuggers, where this  function is called  when suspending execution of
 * the associated CPU, after which the debugger can read/write FPU information
 * for any thread by simply looking at `FORTASK(thread, this_fpustate)' */
#ifndef ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_SAVECPU
FUNDEF NOBLOCK void NOTHROW(KCALL fpustate_savecpu)(void);
#endif /* !ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_SAVECPU */


/* Load / Save the FPU context of  the calling thread to/from the given  `state'
 * If no FPU state had yet to be allocated when `fpustate_loadfrom()' is called,
 * a new state will be allocated before returning. */
#ifndef ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_LOADFROM
FUNDEF NOBLOCK void KCALL
fpustate_loadfrom(NCX struct fpustate const *state)
		THROWS(E_SEGFAULT, E_BADALLOC);
#endif /* !ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_LOADFROM */
#ifndef ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_SAVEINTO
/* Return the pointer that must eventually be passed to `fpustate_loadfrom()' */
FUNDEF NOBLOCK void KCALL
fpustate_saveinto(NCX struct fpustate *state)
		THROWS(E_SEGFAULT);
#endif /* !ARCH_FPU_ARCHHEADER_DEFINES_FPUSTATE_SAVEINTO */

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_HAVE_FPU */
#endif /* CONFIG_HAVE_FPU */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FPU_H */
