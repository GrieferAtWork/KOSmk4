/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBINSTRLEN_INSTRLEN_H
#define GUARD_LIBINSTRLEN_INSTRLEN_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libinstrlen/instrlen.h>

DECL_BEGIN

/* Return the length of an instruction that starts at `pc'
 * WARNING: This function may trigger a segmentation fault when `pc' is an invalid pointer.
 * @return: 0 : The pointed-to instruction wasn't recognized. */
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(CC libil_instruction_length)(void const *pc);

/* Return a pointer to the successor/predecessor instruction of `pc',
 * assuming that `pc' points to the start of another instruction.
 * WARNING: These functions may trigger a segmentation fault when `pc' is an invalid pointer.
 * @return: NULL: The pointed-to instruction wasn't recognized. */
INTDEF ATTR_PURE WUNUSED void const *NOTHROW_NCX(CC libil_instruction_succ)(void const *pc);
INTDEF ATTR_PURE WUNUSED void const *NOTHROW_NCX(CC libil_instruction_pred)(void const *pc);

/* Same as above, but return pc +/- 1, and discard a SEGFAULT and restore any old
 * exception when `pc' is invalid invalid pointer, or when `arch_instruction_(curr|pred)'
 * would have returned `NULL'. */
INTDEF ATTR_PURE WUNUSED void const *NOTHROW(CC libil_instruction_trysucc)(void const *pc);
INTDEF ATTR_PURE WUNUSED void const *NOTHROW(CC libil_instruction_trypred)(void const *pc);


DECL_END

#endif /* !GUARD_LIBINSTRLEN_INSTRLEN_H */
