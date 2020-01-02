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
#ifndef _LIBINSTRLEN_INSTRLEN_H
#define _LIBINSTRLEN_INSTRLEN_H 1

#include "api.h"
#include <bits/types.h>
#include <hybrid/host.h>

#undef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
#if defined(__arm__)
#define LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH 4
#endif

#ifdef __CC__
__DECL_BEGIN


/* Return the length of an instruction that starts at `pc'
 * WARNING: This function may trigger a segmentation fault when `pc' is an invalid pointer.
 * @return: 0 : The pointed-to instruction wasn't recognized. */
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED __size_t (LIBINSTRLEN_CC *PINSTRUCTION_LENGTH)(void const *pc);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __size_t __NOTHROW_NCX(LIBINSTRLEN_CC instruction_length)(void const *pc);
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

/* Return a pointer to the successor/predecessor instruction of `pc',
 * assuming that `pc' points to the start of another instruction.
 * WARNING: These functions may trigger a segmentation fault when `pc' is an invalid pointer.
 * @return: NULL: The pointed-to instruction wasn't recognized. */
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED void const *(LIBINSTRLEN_CC *PINSTRUCTION_SUCC)(void const *pc);
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED void const *(LIBINSTRLEN_CC *PINSTRUCTION_PRED)(void const *pc);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED void const *__NOTHROW_NCX(LIBINSTRLEN_CC instruction_succ)(void const *pc);
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED void const *__NOTHROW_NCX(LIBINSTRLEN_CC instruction_pred)(void const *pc);
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

/* Same as above, but return pc +/- 1, and discard a SEGFAULT and restore any old
 * exception when `pc' is invalid invalid pointer, or when `arch_instruction_(curr|pred)'
 * would have returned `NULL'. */
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED void const * /*__NOTHROW*/ (LIBINSTRLEN_CC *PINSTRUCTION_TRYSUCC)(void const *pc);
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED void const * /*__NOTHROW*/ (LIBINSTRLEN_CC *PINSTRUCTION_TRYPRED)(void const *pc);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED void const *__NOTHROW(LIBINSTRLEN_CC instruction_trysucc)(void const *pc);
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED void const *__NOTHROW(LIBINSTRLEN_CC instruction_trypred)(void const *pc);
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

#ifdef LIBINSTRLEN_WANT_PROTOTYPES
#ifdef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
#define instruction_length(pc)    ((void)(pc),LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH)
#define instruction_succ(pc)      ((void const *)((__byte_t *)(pc) + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH))
#define instruction_pred(pc)      ((void const *)((__byte_t *)(pc) + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH))
#define instruction_trysucc(pc)   ((void const *)((__byte_t *)(pc) + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH))
#define instruction_trypred(pc)   ((void const *)((__byte_t *)(pc) + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH))
#endif /* LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBINSTRLEN_INSTRLEN_H */
