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
#ifndef _LIBINSTRLEN_INSTRLEN_H
#define _LIBINSTRLEN_INSTRLEN_H 1

#include "api.h"
/**/

#include <hybrid/host.h>

#include <asm/isa.h> /* ISA definitions */
#include <bits/types.h>

#include <libinstrlen/bits/instrlen.h> /* LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */

#ifdef __CC__
__DECL_BEGIN


/* Return the length of an instruction that starts at `pc'
 * WARNING: This function may trigger a segmentation fault when `pc' is an invalid pointer.
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT')
 * @return: 0 : The pointed-to instruction wasn't recognized. */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __size_t
__NOTHROW_NCX_T(LIBINSTRLEN_CC *PINSTRUCTION_LENGTH)(void const *pc, isa_t isa);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __size_t
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_length)(void const *pc, isa_t isa __DFL(ISA_DEFAULT));
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

/* Return a pointer to the successor/predecessor instruction of `pc',
 * assuming  that `pc'  points to  the start  of another instruction.
 * WARNING: These functions may trigger a segmentation fault when `pc' is an invalid pointer.
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT')
 * @return: NULL: The pointed-to instruction wasn't recognized. */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __byte_t *__NOTHROW_NCX_T(LIBINSTRLEN_CC *PINSTRUCTION_SUCC)(void const *pc, isa_t isa);
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __byte_t *__NOTHROW_NCX_T(LIBINSTRLEN_CC *PINSTRUCTION_PRED)(void const *pc, isa_t isa);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_succ)(void const *pc, isa_t isa __DFL(ISA_DEFAULT));
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_pred)(void const *pc, isa_t isa __DFL(ISA_DEFAULT));
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

/* Same as above, but handle E_SEGFAULT (and E_WOULDBLOCK in kernel-space) by returning `NULL'
 * Other  exceptions are propagated normally (which could  happen due to VIO access emulation)
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT') */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __byte_t *
__NOTHROW_NCX_T(LIBINSTRLEN_CC *PINSTRUCTION_SUCC_NX)(void const *pc, isa_t isa);
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __byte_t *
__NOTHROW_NCX_T(LIBINSTRLEN_CC *PINSTRUCTION_PRED_NX)(void const *pc, isa_t isa);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_succ_nx)(void const *pc, isa_t isa __DFL(ISA_DEFAULT));
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_pred_nx)(void const *pc, isa_t isa __DFL(ISA_DEFAULT));
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

/* Same as `instruction_(succ|pred)_nx', but return pc +/- 1 instead of NULL.
 * @param: isa: The ISA type (s.a. `Xcpustate_getisa()' or `ISA_DEFAULT') */
typedef __ATTR_PURE_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __byte_t *
__NOTHROW_NCX_T(LIBINSTRLEN_CC *PINSTRUCTION_TRYSUCC)(void const *pc, isa_t isa);
typedef __ATTR_PURE_T __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __byte_t *
__NOTHROW_NCX_T(LIBINSTRLEN_CC *PINSTRUCTION_TRYPRED)(void const *pc, isa_t isa);
#ifdef LIBINSTRLEN_WANT_PROTOTYPES
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_trysucc)(void const *pc, isa_t isa __DFL(ISA_DEFAULT));
LIBINSTRLEN_DECL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __byte_t *
__NOTHROW_NCX(LIBINSTRLEN_CC instruction_trypred)(void const *pc, isa_t isa __DFL(ISA_DEFAULT));
#endif /* LIBINSTRLEN_WANT_PROTOTYPES */

#ifdef LIBINSTRLEN_WANT_PROTOTYPES
#ifdef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
#define instruction_length(pc, isa)    LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa)
#define instruction_succ(pc, isa)      ((__byte_t *)(pc) + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa))
#define instruction_pred(pc, isa)      ((__byte_t *)(pc) - LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa))
#define instruction_trysucc(pc, isa)   ((__byte_t *)(pc) + LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa))
#define instruction_trypred(pc, isa)   ((__byte_t *)(pc) - LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH(isa))
#endif /* LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */

#ifdef icpustate_getisa
#define instruction_length_icpustate(state)  instruction_length(icpustate_getpc(state), icpustate_getisa(state))
#define instruction_succ_icpustate(state)    instruction_succ(icpustate_getpc(state), icpustate_getisa(state))
#define instruction_pred_icpustate(state)    instruction_pred(icpustate_getpc(state), icpustate_getisa(state))
#define instruction_succ_nx_icpustate(state) instruction_succ_nx(icpustate_getpc(state), icpustate_getisa(state))
#define instruction_pred_nx_icpustate(state) instruction_pred_nx(icpustate_getpc(state), icpustate_getisa(state))
#define instruction_trysucc_icpustate(state) instruction_trysucc(icpustate_getpc(state), icpustate_getisa(state))
#define instruction_trypred_icpustate(state) instruction_trypred(icpustate_getpc(state), icpustate_getisa(state))
#endif /* icpustate_getisa */

#ifdef scpustate_getisa
#define instruction_length_scpustate(state)  instruction_length(scpustate_getpc(state), scpustate_getisa(state))
#define instruction_succ_scpustate(state)    instruction_succ(scpustate_getpc(state), scpustate_getisa(state))
#define instruction_pred_scpustate(state)    instruction_pred(scpustate_getpc(state), scpustate_getisa(state))
#define instruction_succ_nx_scpustate(state) instruction_succ_nx(scpustate_getpc(state), scpustate_getisa(state))
#define instruction_pred_nx_scpustate(state) instruction_pred_nx(scpustate_getpc(state), scpustate_getisa(state))
#define instruction_trysucc_scpustate(state) instruction_trysucc(scpustate_getpc(state), scpustate_getisa(state))
#define instruction_trypred_scpustate(state) instruction_trypred(scpustate_getpc(state), scpustate_getisa(state))
#endif /* scpustate_getisa */

#ifdef ucpustate_getisa
#define instruction_length_ucpustate(state)  instruction_length(ucpustate_getpc(state), ucpustate_getisa(state))
#define instruction_succ_ucpustate(state)    instruction_succ(ucpustate_getpc(state), ucpustate_getisa(state))
#define instruction_pred_ucpustate(state)    instruction_pred(ucpustate_getpc(state), ucpustate_getisa(state))
#define instruction_succ_nx_ucpustate(state) instruction_succ_nx(ucpustate_getpc(state), ucpustate_getisa(state))
#define instruction_pred_nx_ucpustate(state) instruction_pred_nx(ucpustate_getpc(state), ucpustate_getisa(state))
#define instruction_trysucc_ucpustate(state) instruction_trysucc(ucpustate_getpc(state), ucpustate_getisa(state))
#define instruction_trypred_ucpustate(state) instruction_trypred(ucpustate_getpc(state), ucpustate_getisa(state))
#endif /* ucpustate_getisa */

#ifdef kcpustate_getisa
#define instruction_length_kcpustate(state)  instruction_length(kcpustate_getpc(state), kcpustate_getisa(state))
#define instruction_succ_kcpustate(state)    instruction_succ(kcpustate_getpc(state), kcpustate_getisa(state))
#define instruction_pred_kcpustate(state)    instruction_pred(kcpustate_getpc(state), kcpustate_getisa(state))
#define instruction_succ_nx_kcpustate(state) instruction_succ_nx(kcpustate_getpc(state), kcpustate_getisa(state))
#define instruction_pred_nx_kcpustate(state) instruction_pred_nx(kcpustate_getpc(state), kcpustate_getisa(state))
#define instruction_trysucc_kcpustate(state) instruction_trysucc(kcpustate_getpc(state), kcpustate_getisa(state))
#define instruction_trypred_kcpustate(state) instruction_trypred(kcpustate_getpc(state), kcpustate_getisa(state))
#endif /* kcpustate_getisa */

#ifdef lcpustate_getisa
#define instruction_length_lcpustate(state)  instruction_length(lcpustate_getpc(state), lcpustate_getisa(state))
#define instruction_succ_lcpustate(state)    instruction_succ(lcpustate_getpc(state), lcpustate_getisa(state))
#define instruction_pred_lcpustate(state)    instruction_pred(lcpustate_getpc(state), lcpustate_getisa(state))
#define instruction_succ_nx_lcpustate(state) instruction_succ_nx(lcpustate_getpc(state), lcpustate_getisa(state))
#define instruction_pred_nx_lcpustate(state) instruction_pred_nx(lcpustate_getpc(state), lcpustate_getisa(state))
#define instruction_trysucc_lcpustate(state) instruction_trysucc(lcpustate_getpc(state), lcpustate_getisa(state))
#define instruction_trypred_lcpustate(state) instruction_trypred(lcpustate_getpc(state), lcpustate_getisa(state))
#endif /* lcpustate_getisa */

#ifdef fcpustate_getisa
#define instruction_length_fcpustate(state)  instruction_length(fcpustate_getpc(state), fcpustate_getisa(state))
#define instruction_succ_fcpustate(state)    instruction_succ(fcpustate_getpc(state), fcpustate_getisa(state))
#define instruction_pred_fcpustate(state)    instruction_pred(fcpustate_getpc(state), fcpustate_getisa(state))
#define instruction_succ_nx_fcpustate(state) instruction_succ_nx(fcpustate_getpc(state), fcpustate_getisa(state))
#define instruction_pred_nx_fcpustate(state) instruction_pred_nx(fcpustate_getpc(state), fcpustate_getisa(state))
#define instruction_trysucc_fcpustate(state) instruction_trysucc(fcpustate_getpc(state), fcpustate_getisa(state))
#define instruction_trypred_fcpustate(state) instruction_trypred(fcpustate_getpc(state), fcpustate_getisa(state))
#endif /* fcpustate_getisa */

#endif /* LIBINSTRLEN_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBINSTRLEN_INSTRLEN_H */
