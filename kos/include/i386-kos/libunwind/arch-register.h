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
#ifndef _I386_KOS_LIBUNWIND_ARCH_REGISTER_H
#define _I386_KOS_LIBUNWIND_ARCH_REGISTER_H 1

#include "../../libunwind/api.h"
/**/

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __unwind_regno_t_defined
#define __unwind_regno_t_defined 1
typedef __UINTPTR_HALF_TYPE__ unwind_regno_t;
#endif /* !__unwind_regno_t_defined */

/* Register accessor callbacks for a variety of known cpu context structures.
 * NOTE: When the intent  is to unwind  both CPU  and FPU registers,  you must  create
 *       your own custom register get/set functions that call forward to the functions
 *       below:
 * >> unsigned int LIBUNWIND_CC my_getreg(void const *arg, uintptr_half_t regno, void *dst) {
 * >>     struct my_cpustate_with_fpu const *me;
 * >>     me = (struct my_cpustate_with_fpu const *)arg;
 * >>     if (unwind_getreg_xfpustate(me->cs_fpu, regno, dst))
 * >>         return UNWIND_SUCCESS;
 * >>     if (unwind_getreg_ufpustate(me->cs_cpu, regno, dst))
 * >>         return UNWIND_SUCCESS;
 * >>     return UNWIND_INVALID_REGISTER;
 * >> }
 * >> unsigned int LIBUNWIND_CC my_setreg(void *arg, uintptr_half_t regno, void const *src) {
 * >>     struct my_cpustate_with_fpu *me;
 * >>     me = (struct my_cpustate_with_fpu *)arg;
 * >>     if (unwind_setreg_xfpustate(me->cs_fpu, regno, src))
 * >>         return UNWIND_SUCCESS;
 * >>     if (unwind_setreg_ufpustate(me->cs_cpu, regno, src))
 * >>         return UNWIND_SUCCESS;
 * >>     return UNWIND_INVALID_REGISTER;
 * >> }
 * NOTE: *_exclusive functions  will always  return  `UNWIND_INVALID_REGISTER' when  attempting  to
 *       access persistent registers that are  not present within the  given CPU state, as  opposed
 *       to reading the current register value during get, and returning `CURRENT_VAL() == new_val'
 *       on set (aka.: setreg()  normally returns true  for untraced registers  when the old  value
 *       matches the new one) */
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_LCPUSTATE)(/*struct lcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_LCPUSTATE)(/*struct lcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_UCPUSTATE)(/*struct ucpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_UCPUSTATE)(/*struct ucpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_KCPUSTATE)(/*struct kcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_KCPUSTATE)(/*struct kcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_FCPUSTATE)(/*struct fcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_FCPUSTATE)(/*struct fcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_SFPUSTATE)(/*struct sfpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_SFPUSTATE)(/*struct sfpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_XFPUSTATE)(/*struct xfpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_XFPUSTATE)(/*struct xfpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_LCPUSTATE_EXCLUSIVE)(/*struct lcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_LCPUSTATE_EXCLUSIVE)(/*struct lcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_UCPUSTATE_EXCLUSIVE)(/*struct ucpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_UCPUSTATE_EXCLUSIVE)(/*struct ucpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_KCPUSTATE_EXCLUSIVE)(/*struct kcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_KCPUSTATE_EXCLUSIVE)(/*struct kcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_FCPUSTATE_EXCLUSIVE)(/*struct fcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_FCPUSTATE_EXCLUSIVE)(/*struct fcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_SFPUSTATE_EXCLUSIVE)(/*struct sfpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_SFPUSTATE_EXCLUSIVE)(/*struct sfpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_XFPUSTATE_EXCLUSIVE)(/*struct xfpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_XFPUSTATE_EXCLUSIVE)(/*struct xfpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#ifdef __KERNEL__
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_SCPUSTATE)(/*struct scpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_ICPUSTATE)(/*struct icpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_SCPUSTATE_EXCLUSIVE)(/*struct scpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_GETREG_ICPUSTATE_EXCLUSIVE)(/*struct icpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
#ifdef __x86_64__
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_SCPUSTATE)(/*struct scpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_ICPUSTATE)(/*struct icpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_SCPUSTATE_EXCLUSIVE)(/*struct scpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_ICPUSTATE_EXCLUSIVE)(/*struct icpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#else /* __x86_64__ */
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_SCPUSTATE_P)(/*struct scpustate ***/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_ICPUSTATE_P)(/*struct icpustate ***/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_SCPUSTATE_EXCLUSIVE_P)(/*struct scpustate ***/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
typedef __ATTR_NONNULL((1, 3)) unsigned int (LIBUNWIND_CC *PUNWIND_SETREG_ICPUSTATE_EXCLUSIVE_P)(/*struct icpustate ***/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !__x86_64__ */
#endif /* __KERNEL__ */
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_lcpustate)(/*struct lcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_lcpustate)(/*struct lcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucpustate)(/*struct ucpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucpustate)(/*struct ucpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_kcpustate)(/*struct kcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_kcpustate)(/*struct kcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_fcpustate)(/*struct fcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fcpustate)(/*struct fcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_sfpustate)(/*struct sfpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_sfpustate)(/*struct sfpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_xfpustate)(/*struct xfpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_xfpustate)(/*struct xfpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_lcpustate_exclusive)(/*struct lcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_lcpustate_exclusive)(/*struct lcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucpustate_exclusive)(/*struct ucpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucpustate_exclusive)(/*struct ucpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_kcpustate_exclusive)(/*struct kcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_kcpustate_exclusive)(/*struct kcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_fcpustate_exclusive)(/*struct fcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fcpustate_exclusive)(/*struct fcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_sfpustate_exclusive)(/*struct sfpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_sfpustate_exclusive)(/*struct sfpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_xfpustate_exclusive)(/*struct xfpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_xfpustate_exclusive)(/*struct xfpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#ifdef __KERNEL__
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_scpustate)(/*struct scpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_icpustate)(/*struct icpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_scpustate_exclusive)(/*struct scpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_icpustate_exclusive)(/*struct icpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
#ifdef __x86_64__
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate)(/*struct scpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate)(/*struct icpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate_exclusive)(/*struct scpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate_exclusive)(/*struct icpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#else /* __x86_64__ */
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate_p)(/*struct scpustate ***/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate_p)(/*struct icpustate ***/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate_exclusive_p)(/*struct scpustate ***/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate_exclusive_p)(/*struct icpustate ***/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#endif /* !__x86_64__ */
#endif /* __KERNEL__ */
#endif /* LIBUNWIND_WANT_PROTOTYPES */



/* Accessor functions for working with the register descriptor used by exception handling. */
#define LIBUNWIND_HAVE_ERROR_REGISTER_STATE_ACCESSORS 1
typedef PUNWIND_GETREG_KCPUSTATE PUNWIND_GETREG_ERROR_REGISTER_STATE;
typedef PUNWIND_SETREG_KCPUSTATE PUNWIND_SETREG_ERROR_REGISTER_STATE;
#define UNWIND_GETREG_ERROR_REGISTER_STATE_NAME "unwind_getreg_kcpustate"
#define UNWIND_SETREG_ERROR_REGISTER_STATE_NAME "unwind_setreg_kcpustate"
#ifdef LIBUNWIND_WANT_PROTOTYPES
#define unwind_getreg_error_register_state unwind_getreg_kcpustate
#define unwind_setreg_error_register_state unwind_setreg_kcpustate
#endif /* LIBUNWIND_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_LIBUNWIND_ARCH_REGISTER_H */
