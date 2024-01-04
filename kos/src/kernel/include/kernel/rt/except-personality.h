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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_PERSONALIY_H
#define GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_PERSONALIY_H 1

/* Kernel exception handling personality definitions.
 * aka. `.cfi_personality',  `__gcc_personality_v0()' */

#include <kernel/compiler.h>

#include <kernel/arch/rt/except-personality.h> /* arch-override for `EXCEPT_PERSONALITY_CC' */


/* Return values for `except_personality_t' */
#define EXCEPT_PERSONALITY_EXECUTE_HANDLER     0 /* An exception handler was found, and `state' was updated */
#define EXCEPT_PERSONALITY_EXECUTE_HANDLER_NOW 1 /* Same as `EXCEPT_PERSONALITY_EXECUTE_HANDLER', but don't adjust for `DW_CFA_GNU_args_size' */
#define EXCEPT_PERSONALITY_CONTINUE_UNWIND     2 /* Continue unwinding to search for an exception handler. */
#define EXCEPT_PERSONALITY_ABORT_SEARCH        3 /* Abort the search for exception handlers, and panic(). */

#ifdef __CC__
DECL_BEGIN

#ifndef EXCEPT_PERSONALITY_CC
#define EXCEPT_PERSONALITY_CC KCALL
#endif /* !EXCEPT_PERSONALITY_CC */

struct unwind_fde_struct;
struct kcpustate;

/* The prototype by which custom personality function must abide within the KOS kernel.
 * When called, `state' refers to the state _within_ the associated function. - Not the
 * state after that function has been unwound!
 * NOTES:
 *   - `.cfi_personality 0, <some-function-implemented-as-except_personality_t>'
 *   - The value specified by `.cfi_lsda 0, <lsda-value>' can be read from `fde->f_lsdaaddr'
 *   - The PC-register of `state' is set to point _AFTER_ the instruction
 *     that  caused/propagated  an  exception (aka.  the  return address)
 * @param: fde: The FDE pointing to @this personality function.
 * @return: * : One of `DWARF_PERSO_*' */
typedef ABNORMAL_RETURN NONNULL_T((1, 2)) unsigned int
NOTHROW_T(EXCEPT_PERSONALITY_CC *except_personality_t)(struct unwind_fde_struct *__restrict fde,
                                                       struct kcpustate *__restrict state);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_PERSONALIY_H */
