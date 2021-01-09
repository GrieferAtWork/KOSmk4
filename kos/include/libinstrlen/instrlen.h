/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBINSTRLEN_INSTRLEN_H
#define _LIBINSTRLEN_INSTRLEN_H 1

#include "api.h"
/**/

#include <hybrid/host.h>

#include <bits/types.h>

#include <libinstrlen/bits/isa.h>

#undef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
#if defined(__arm__)
#define LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa) 4
#endif /* ... */

#ifdef __CC__
__DECL_BEGIN


/* Return the length of an instruction that starts at `pc'
 * WARNING: This function may trigger a segmentation fault when `pc' is an invalid pointer.
 * @param: isa: The ISA type (s.a. `instrlen_isa_from_Xcpustate()' or `INSTRLEN_ISA_DEFAULT')
 * @return: 0 : The pointed-to instruction wasn't recognized. */
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED __size_t
/*__NOTHROW_NCX*/ (LIBINSTRLEN_CC *PINSTRUCTION_LENGTH)(void const *pc, instrlen_isa_t isa);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __size_t
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_length)(void const *pc, instrlen_isa_t isa __DFL(INSTRLEN_ISA_DEFAULT));
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

/* Return a pointer to the successor/predecessor instruction of `pc',
 * assuming that `pc' points to the start of another instruction.
 * WARNING: These functions may trigger a segmentation fault when `pc' is an invalid pointer.
 * @param: isa: The ISA type (s.a. `instrlen_isa_from_Xcpustate()' or `INSTRLEN_ISA_DEFAULT')
 * @return: NULL: The pointed-to instruction wasn't recognized. */
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED __byte_t *(LIBINSTRLEN_CC *PINSTRUCTION_SUCC)(void const *pc, instrlen_isa_t isa);
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED __byte_t *(LIBINSTRLEN_CC *PINSTRUCTION_PRED)(void const *pc, instrlen_isa_t isa);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_succ)(void const *pc, instrlen_isa_t isa __DFL(INSTRLEN_ISA_DEFAULT));
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_pred)(void const *pc, instrlen_isa_t isa __DFL(INSTRLEN_ISA_DEFAULT));
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

/* Same as above, but handle E_SEGFAULT (and E_WOULDBLOCK in kernel-space) by returning `NULL'
 * Other exceptions are propagated normally (which could happen due to VIO access emulation)
 * @param: isa: The ISA type (s.a. `instrlen_isa_from_Xcpustate()' or `INSTRLEN_ISA_DEFAULT') */
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED __byte_t *
(LIBINSTRLEN_CC *PINSTRUCTION_SUCC_NX)(void const *pc, instrlen_isa_t isa);
typedef /*__ATTR_PURE*/ __ATTR_WUNUSED __byte_t *
(LIBINSTRLEN_CC *PINSTRUCTION_PRED_NX)(void const *pc, instrlen_isa_t isa);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_succ_nx)(void const *pc, instrlen_isa_t isa __DFL(INSTRLEN_ISA_DEFAULT));
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_pred_nx)(void const *pc, instrlen_isa_t isa __DFL(INSTRLEN_ISA_DEFAULT));
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

/* Same as `instruction_(succ|pred)_nx', but return pc +/- 1 instead of NULL.
 * @param: isa: The ISA type (s.a. `instrlen_isa_from_Xcpustate()' or `INSTRLEN_ISA_DEFAULT') */
typedef /*__ATTR_PURE*/ __ATTR_RETNONNULL __ATTR_WUNUSED __byte_t *
/*__NOTHROW_NCX*/ (LIBINSTRLEN_CC *PINSTRUCTION_TRYSUCC)(void const *pc, instrlen_isa_t isa);
typedef /*__ATTR_PURE*/ __ATTR_RETNONNULL __ATTR_WUNUSED __byte_t *
/*__NOTHROW_NCX*/ (LIBINSTRLEN_CC *PINSTRUCTION_TRYPRED)(void const *pc, instrlen_isa_t isa);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_trysucc)(void const *pc, instrlen_isa_t isa __DFL(INSTRLEN_ISA_DEFAULT));
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_trypred)(void const *pc, instrlen_isa_t isa __DFL(INSTRLEN_ISA_DEFAULT));
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

#ifdef LIBINSTRLEN_WANT_PROTOTYPES
#ifdef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
#define instruction_length(pc, isa)    LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa)
#define instruction_succ(pc, isa)      ((__byte_t *)(pc) + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa))
#define instruction_pred(pc, isa)      ((__byte_t *)(pc) - LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa))
#define instruction_trysucc(pc, isa)   ((__byte_t *)(pc) + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa))
#define instruction_trypred(pc, isa)   ((__byte_t *)(pc) - LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa))
#endif /* LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBINSTRLEN_INSTRLEN_H */
