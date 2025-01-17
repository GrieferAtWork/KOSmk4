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
#ifndef GUARD_LIBINSTRLEN_INSTRLEN_H
#define GUARD_LIBINSTRLEN_INSTRLEN_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libinstrlen/instrlen.h>

DECL_BEGIN

/* Return the length of an instruction that starts at `pc'
 * WARNING: This function may trigger a segmentation fault when `pc' is an invalid pointer.
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT')
 * @return: 0 : The pointed-to instruction wasn't recognized. */
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(CC libil_instruction_length)(void const *pc, isa_t isa);

/* Return a pointer to the successor/predecessor instruction of `pc',
 * assuming  that `pc'  points to  the start  of another instruction.
 * WARNING: These functions may trigger a segmentation fault when `pc' is an invalid pointer.
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT')
 * @return: NULL: The pointed-to instruction wasn't recognized. */
INTDEF ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_succ)(void const *pc, isa_t isa);
INTDEF ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_pred)(void const *pc, isa_t isa);

/* Same as above, but handle E_SEGFAULT (and E_WOULDBLOCK in kernel-space) by returning `NULL'
 * Other  exceptions are propagated normally (which could  happen due to VIO access emulation)
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT') */
INTDEF ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_succ_nx)(void const *pc, isa_t isa);
INTDEF ATTR_PURE WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_pred_nx)(void const *pc, isa_t isa);

/* Same as `instruction_(succ|pred)_nx', but return pc +/- 1 instead of NULL.
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT') */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_trysucc)(void const *pc, isa_t isa);
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *
NOTHROW_NCX(CC libil_instruction_trypred)(void const *pc, isa_t isa);


DECL_END

#endif /* !GUARD_LIBINSTRLEN_INSTRLEN_H */
