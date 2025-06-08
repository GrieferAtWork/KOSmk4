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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_PERSONALIY_H
#define GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_PERSONALIY_H 1

/* Kernel exception handling personality definitions.
 * aka. `.cfi_personality',  `__gcc_personality_v0()' */

#include <kernel/compiler.h>

#include <kernel/arch/rt/except-personality.h> /* arch-override for `EXCEPT_PERSONALITY_CC' */

#include <hybrid/typecore.h>

#include <libunwind/eh_frame.h>

/* Return values for `except_personality_t' */
#define EXCEPT_PERSONALITY_EXECUTE_HANDLER     0 /* An exception handler was found, and `state' was updated */
#define EXCEPT_PERSONALITY_EXECUTE_HANDLER_NOW 1 /* Same as `EXCEPT_PERSONALITY_EXECUTE_HANDLER', but don't adjust for `DW_CFA_GNU_args_size' */
#define EXCEPT_PERSONALITY_CONTINUE_UNWIND     2 /* Continue unwinding to search for an exception handler. */
#define EXCEPT_PERSONALITY_ABORT_SEARCH        3 /* Abort the search for exception handlers, and panic(). */

#define OFFSET__UNWIND_CONTEXT_FDE            0
#define OFFSET__UNWIND_CONTEXT_STATE          __SIZEOF_UNWIND_FDE
#define OFFSET__UNWIND_CONTEXT_ADJPC          (__SIZEOF_UNWIND_FDE + __SIZEOF_POINTER__)
#define OFFSET__UNWIND_CONTEXT_PC_BEFORE_INSN (__SIZEOF_UNWIND_FDE + (__SIZEOF_POINTER__ * 2))
#define SIZEOF__UNWIND_CONTEXT                (__SIZEOF_UNWIND_FDE + (__SIZEOF_POINTER__ * 3))

#ifdef __CC__
DECL_BEGIN

#ifndef EXCEPT_PERSONALITY_CC
#define EXCEPT_PERSONALITY_CC KCALL
#endif /* !EXCEPT_PERSONALITY_CC */

struct unwind_fde_struct;
struct kcpustate;

struct _Unwind_Context {
	unwind_fde_t      uc_fde;            /* Currently relevant FDE */
	struct kcpustate *uc_state;          /* [1..1] Program state */
	void const       *uc_adjpc;          /* Currently relevant program counter. Same as PC in `uc_state',
	                                      * but already adjusted as per `uc_pc_before_insn' (such that it
	                                      * can always be used in "uc_adjpc >= start && uc_adjpc < end") */
	__BYTE_TYPE__     uc_pc_before_insn; /* Non-zero if the last FDE was a signal frame. */
	__BYTE_TYPE__ _uc_pad[__SIZEOF_POINTER__ - 1]; /* ... */
};


/* The  prototype by which custom personality function  must abide within the KOS kernel.
 * When called, `context->uc_state' refers to the state _within_ the associated function;
 * not the state after that function has been unwound!
 * NOTES:
 *  - `.cfi_personality 0, <some-function-implemented-as-except_personality_t>'
 *  - The value specified by `.cfi_lsda 0, <lsda-value>' can be read from `context->uc_fde.f_lsdaaddr'
 * @param: context: Exception context
 * @return: * : One of `DWARF_PERSO_*' */
typedef ABNORMAL_RETURN NONNULL_T((1)) unsigned int
NOTHROW_T(EXCEPT_PERSONALITY_CC *except_personality_t)(struct _Unwind_Context *__restrict context);

/* Pre-defined personality functions */
FUNDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC __gcc_personality_v0)(struct _Unwind_Context *__restrict context);
FUNDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC __gxx_personality_v0)(struct _Unwind_Context *__restrict context);
#ifdef BUILDING_KERNEL_CORE
INTDEF WUNUSED NONNULL((1)) unsigned int NOTHROW(EXCEPT_PERSONALITY_CC libc_gxx_personality_v0)(struct _Unwind_Context *__restrict context);
#endif /* BUILDING_KERNEL_CORE */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_PERSONALIY_H */
