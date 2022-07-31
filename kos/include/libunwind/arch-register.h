/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBUNWIND_ARCH_REGISTER_H
#define _LIBUNWIND_ARCH_REGISTER_H 1

#include "api.h"

#include <kos/bits/except.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/fpu-state.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __unwind_regno_t_defined
#define __unwind_regno_t_defined
typedef __UINTPTR_HALF_TYPE__ unwind_regno_t;
#endif /* !__unwind_regno_t_defined */

/* Register accessor callbacks for a variety of known cpu context structures.
 * NOTE: When the intent  is to unwind  both CPU  and FPU registers,  you must  create
 *       your own custom register get/set functions that call forward to the functions
 *       below:
 * >> unsigned int LIBUNWIND_CC my_getreg(void const *arg, uintptr_half_t regno, void *dst) {
 * >>     unsigned int error;
 * >>     struct my_cpustate_with_fpu const *me;
 * >>     me = (struct my_cpustate_with_fpu const *)arg;
 * >>     if ((error = unwind_getreg_xfpustate(me->cs_fpu, regno, dst)) != UNWIND_INVALID_REGISTER)
 * >>         return error;
 * >>     if ((error = unwind_getreg_ufpustate(me->cs_cpu, regno, dst)) != UNWIND_INVALID_REGISTER)
 * >>         return error;
 * >>     return UNWIND_INVALID_REGISTER;
 * >> }
 * >> unsigned int LIBUNWIND_CC my_setreg(void *arg, uintptr_half_t regno, void const *src) {
 * >>     unsigned int error;
 * >>     struct my_cpustate_with_fpu *me;
 * >>     me = (struct my_cpustate_with_fpu *)arg;
 * >>     if ((error = unwind_setreg_xfpustate(me->cs_fpu, regno, src)) != UNWIND_INVALID_REGISTER)
 * >>         return error;
 * >>     if ((error = unwind_setreg_ufpustate(me->cs_cpu, regno, src)) != UNWIND_INVALID_REGISTER)
 * >>         return error;
 * >>     return UNWIND_INVALID_REGISTER;
 * >> }
 * NOTE: *_exclusive functions  will always  return  `UNWIND_INVALID_REGISTER' when  attempting  to
 *       access persistent registers that are  not present within the  given CPU state, as  opposed
 *       to reading the current register value during get, and returning `CURRENT_VAL() == new_val'
 *       on set (aka.: setreg()  normally returns true  for untraced registers  when the old  value
 *       matches the new one) */
typedef __ATTR_NONNULL_T((1, 3)) unsigned int __NOTHROW_NCX_T(LIBUNWIND_CC *_PUNWIND_GETREG_XCPUSTATE)(/*struct lcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
typedef __ATTR_NONNULL_T((1, 3)) unsigned int __NOTHROW_NCX_T(LIBUNWIND_CC *_PUNWIND_SETREG_XCPUSTATE)(/*struct lcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);

#define PUNWIND_GETREG_UCPUSTATE           _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_UCPUSTATE           _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_LCPUSTATE           _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_LCPUSTATE           _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_KCPUSTATE           _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_KCPUSTATE           _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_FCPUSTATE           _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_FCPUSTATE           _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_SFPUSTATE           _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_SFPUSTATE           _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_XFPUSTATE           _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_XFPUSTATE           _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_UCPUSTATE_EXCLUSIVE _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_UCPUSTATE_EXCLUSIVE _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_LCPUSTATE_EXCLUSIVE _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_LCPUSTATE_EXCLUSIVE _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_KCPUSTATE_EXCLUSIVE _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_KCPUSTATE_EXCLUSIVE _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_FCPUSTATE_EXCLUSIVE _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_FCPUSTATE_EXCLUSIVE _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_SFPUSTATE_EXCLUSIVE _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_SFPUSTATE_EXCLUSIVE _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_XFPUSTATE_EXCLUSIVE _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_XFPUSTATE_EXCLUSIVE _PUNWIND_SETREG_XCPUSTATE
#ifdef __KERNEL__
#define PUNWIND_GETREG_SCPUSTATE           _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_GETREG_ICPUSTATE           _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_SETREG_SCPUSTATE           _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_ICPUSTATE           _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_GETREG_SCPUSTATE_EXCLUSIVE _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_GETREG_ICPUSTATE_EXCLUSIVE _PUNWIND_SETREG_XCPUSTATE
#define PUNWIND_SETREG_SCPUSTATE_EXCLUSIVE _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_ICPUSTATE_EXCLUSIVE _PUNWIND_SETREG_XCPUSTATE
#endif /* __KERNEL__ */

#ifdef LCPUSTATE_IS_UCPUSTATE
#define unwind_getreg_lcpustate                unwind_getreg_ucpustate
#define unwind_setreg_lcpustate                unwind_setreg_ucpustate
#define unwind_getreg_lcpustate_exclusive      unwind_getreg_ucpustate_exclusive
#define unwind_setreg_lcpustate_exclusive      unwind_setreg_ucpustate_exclusive
#define UNWIND_GETREG_LCPUSTATE_NAME           UNWIND_GETREG_UCPUSTATE_NAME
#define UNWIND_SETREG_LCPUSTATE_NAME           UNWIND_SETREG_UCPUSTATE_NAME
#define UNWIND_GETREG_LCPUSTATE_EXCLUSIVE_NAME UNWIND_GETREG_UCPUSTATE_EXCLUSIVE_NAME
#define UNWIND_SETREG_LCPUSTATE_EXCLUSIVE_NAME UNWIND_SETREG_UCPUSTATE_EXCLUSIVE_NAME
#endif /* LCPUSTATE_IS_UCPUSTATE */

#ifdef KCPUSTATE_IS_UCPUSTATE
#define unwind_getreg_kcpustate                unwind_getreg_ucpustate
#define unwind_setreg_kcpustate                unwind_setreg_ucpustate
#define unwind_getreg_kcpustate_exclusive      unwind_getreg_ucpustate_exclusive
#define unwind_setreg_kcpustate_exclusive      unwind_setreg_ucpustate_exclusive
#define UNWIND_GETREG_KCPUSTATE_NAME           UNWIND_GETREG_UCPUSTATE_NAME
#define UNWIND_SETREG_KCPUSTATE_NAME           UNWIND_SETREG_UCPUSTATE_NAME
#define UNWIND_GETREG_KCPUSTATE_EXCLUSIVE_NAME UNWIND_GETREG_UCPUSTATE_EXCLUSIVE_NAME
#define UNWIND_SETREG_KCPUSTATE_EXCLUSIVE_NAME UNWIND_SETREG_UCPUSTATE_EXCLUSIVE_NAME
#elif defined(KCPUSTATE_IS_LCPUSTATE)
#define unwind_getreg_kcpustate                unwind_getreg_lcpustate
#define unwind_setreg_kcpustate                unwind_setreg_lcpustate
#define unwind_getreg_kcpustate_exclusive      unwind_getreg_lcpustate_exclusive
#define unwind_setreg_kcpustate_exclusive      unwind_setreg_lcpustate_exclusive
#define UNWIND_GETREG_KCPUSTATE_NAME           UNWIND_GETREG_LCPUSTATE_NAME
#define UNWIND_SETREG_KCPUSTATE_NAME           UNWIND_SETREG_LCPUSTATE_NAME
#define UNWIND_GETREG_KCPUSTATE_exclusive_NAME UNWIND_GETREG_LCPUSTATE_exclusive_NAME
#define UNWIND_SETREG_KCPUSTATE_exclusive_NAME UNWIND_SETREG_LCPUSTATE_exclusive_NAME
#endif /* ... */

#ifdef __KERNEL__
#ifdef ICPUSTATE_IS_UCPUSTATE
#define unwind_getreg_icpustate                unwind_getreg_ucpustate
#define unwind_setreg_icpustate                unwind_setreg_ucpustate
#define unwind_getreg_icpustate_exclusive      unwind_getreg_ucpustate_exclusive
#define unwind_setreg_icpustate_exclusive      unwind_setreg_ucpustate_exclusive
#define UNWIND_GETREG_ICPUSTATE_NAME           UNWIND_GETREG_UCPUSTATE_NAME
#define UNWIND_SETREG_ICPUSTATE_NAME           UNWIND_SETREG_UCPUSTATE_NAME
#define UNWIND_GETREG_ICPUSTATE_EXCLUSIVE_NAME UNWIND_GETREG_UCPUSTATE_EXCLUSIVE_NAME
#define UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_NAME UNWIND_SETREG_UCPUSTATE_EXCLUSIVE_NAME
#elif defined(ICPUSTATE_IS_LCPUSTATE)
#define unwind_getreg_icpustate                unwind_getreg_lcpustate
#define unwind_setreg_icpustate                unwind_setreg_lcpustate
#define unwind_getreg_icpustate_exclusive      unwind_getreg_lcpustate_exclusive
#define unwind_setreg_icpustate_exclusive      unwind_setreg_lcpustate_exclusive
#define UNWIND_GETREG_ICPUSTATE_NAME           UNWIND_GETREG_LCPUSTATE_NAME
#define UNWIND_SETREG_ICPUSTATE_NAME           UNWIND_SETREG_LCPUSTATE_NAME
#define UNWIND_GETREG_ICPUSTATE_EXCLUSIVE_NAME UNWIND_GETREG_LCPUSTATE_EXCLUSIVE_NAME
#define UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_NAME UNWIND_SETREG_LCPUSTATE_EXCLUSIVE_NAME
#elif defined(ICPUSTATE_IS_KCPUSTATE)
#define unwind_getreg_icpustate                unwind_getreg_kcpustate
#define unwind_setreg_icpustate                unwind_setreg_kcpustate
#define unwind_getreg_icpustate_exclusive      unwind_getreg_kcpustate_exclusive
#define unwind_setreg_icpustate_exclusive      unwind_setreg_kcpustate_exclusive
#define UNWIND_GETREG_ICPUSTATE_NAME           UNWIND_GETREG_KCPUSTATE_NAME
#define UNWIND_SETREG_ICPUSTATE_NAME           UNWIND_SETREG_KCPUSTATE_NAME
#define UNWIND_GETREG_ICPUSTATE_EXCLUSIVE_NAME UNWIND_GETREG_KCPUSTATE_EXCLUSIVE_NAME
#define UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_NAME UNWIND_SETREG_KCPUSTATE_EXCLUSIVE_NAME
#endif /* ... */
#ifdef SCPUSTATE_IS_UCPUSTATE
#define unwind_getreg_scpustate                unwind_getreg_ucpustate
#define unwind_setreg_scpustate                unwind_setreg_ucpustate
#define unwind_getreg_scpustate_exclusive      unwind_getreg_ucpustate_exclusive
#define unwind_setreg_scpustate_exclusive      unwind_setreg_ucpustate_exclusive
#define UNWIND_GETREG_SCPUSTATE_NAME           UNWIND_GETREG_UCPUSTATE_NAME
#define UNWIND_SETREG_SCPUSTATE_NAME           UNWIND_SETREG_UCPUSTATE_NAME
#define UNWIND_GETREG_SCPUSTATE_EXCLUSIVE_NAME UNWIND_GETREG_UCPUSTATE_EXCLUSIVE_NAME
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_NAME UNWIND_SETREG_UCPUSTATE_EXCLUSIVE_NAME
#elif defined(SCPUSTATE_IS_LCPUSTATE)
#define unwind_getreg_scpustate                unwind_getreg_lcpustate
#define unwind_setreg_scpustate                unwind_setreg_lcpustate
#define unwind_getreg_scpustate_exclusive      unwind_getreg_lcpustate_exclusive
#define unwind_setreg_scpustate_exclusive      unwind_setreg_lcpustate_exclusive
#define UNWIND_GETREG_SCPUSTATE_NAME           UNWIND_GETREG_LCPUSTATE_NAME
#define UNWIND_SETREG_SCPUSTATE_NAME           UNWIND_SETREG_LCPUSTATE_NAME
#define UNWIND_GETREG_SCPUSTATE_EXCLUSIVE_NAME UNWIND_GETREG_LCPUSTATE_EXCLUSIVE_NAME
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_NAME UNWIND_SETREG_LCPUSTATE_EXCLUSIVE_NAME
#elif defined(SCPUSTATE_IS_KCPUSTATE)
#define unwind_getreg_scpustate                unwind_getreg_kcpustate
#define unwind_setreg_scpustate                unwind_setreg_kcpustate
#define unwind_getreg_scpustate_exclusive      unwind_getreg_kcpustate_exclusive
#define unwind_setreg_scpustate_exclusive      unwind_setreg_kcpustate_exclusive
#define UNWIND_GETREG_SCPUSTATE_NAME           UNWIND_GETREG_KCPUSTATE_NAME
#define UNWIND_SETREG_SCPUSTATE_NAME           UNWIND_SETREG_KCPUSTATE_NAME
#define UNWIND_GETREG_SCPUSTATE_EXCLUSIVE_NAME UNWIND_GETREG_KCPUSTATE_EXCLUSIVE_NAME
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_NAME UNWIND_SETREG_KCPUSTATE_EXCLUSIVE_NAME
#elif defined(SCPUSTATE_IS_ICPUSTATE)
#define unwind_getreg_scpustate                unwind_getreg_icpustate
#define unwind_setreg_scpustate                unwind_setreg_icpustate
#define unwind_getreg_scpustate_exclusive      unwind_getreg_icpustate_exclusive
#define unwind_setreg_scpustate_exclusive      unwind_setreg_icpustate_exclusive
#define UNWIND_GETREG_SCPUSTATE_NAME           UNWIND_GETREG_ICPUSTATE_NAME
#define UNWIND_SETREG_SCPUSTATE_NAME           UNWIND_SETREG_ICPUSTATE_NAME
#define UNWIND_GETREG_SCPUSTATE_EXCLUSIVE_NAME UNWIND_GETREG_ICPUSTATE_EXCLUSIVE_NAME
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_NAME UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_NAME
#endif /* ... */
#endif /* __KERNEL__ */

#ifdef FCPUSTATE_IS_UCPUSTATE
#define unwind_getreg_fcpustate      unwind_getreg_ucpustate
#define unwind_setreg_fcpustate      unwind_setreg_ucpustate
#define UNWIND_GETREG_FCPUSTATE_NAME UNWIND_GETREG_UCPUSTATE_NAME
#define UNWIND_SETREG_FCPUSTATE_NAME UNWIND_SETREG_UCPUSTATE_NAME
#elif defined(FCPUSTATE_IS_LCPUSTATE)
#define unwind_getreg_fcpustate      unwind_getreg_lcpustate
#define unwind_setreg_fcpustate      unwind_setreg_lcpustate
#define UNWIND_GETREG_FCPUSTATE_NAME UNWIND_GETREG_LCPUSTATE_NAME
#define UNWIND_SETREG_FCPUSTATE_NAME UNWIND_SETREG_LCPUSTATE_NAME
#elif defined(FCPUSTATE_IS_KCPUSTATE)
#define unwind_getreg_fcpustate      unwind_getreg_kcpustate
#define unwind_setreg_fcpustate      unwind_setreg_kcpustate
#define UNWIND_GETREG_FCPUSTATE_NAME UNWIND_GETREG_KCPUSTATE_NAME
#define UNWIND_SETREG_FCPUSTATE_NAME UNWIND_SETREG_KCPUSTATE_NAME
#elif defined(FCPUSTATE_IS_ICPUSTATE) && defined(__KERNEL__)
#define unwind_getreg_fcpustate      unwind_getreg_icpustate
#define unwind_setreg_fcpustate      unwind_setreg_icpustate
#define UNWIND_GETREG_FCPUSTATE_NAME UNWIND_GETREG_ICPUSTATE_NAME
#define UNWIND_SETREG_FCPUSTATE_NAME UNWIND_SETREG_ICPUSTATE_NAME
#elif defined(FCPUSTATE_IS_SCPUSTATE) && defined(__KERNEL__)
#define unwind_getreg_fcpustate      unwind_getreg_scpustate
#define unwind_setreg_fcpustate      unwind_setreg_scpustate
#define UNWIND_GETREG_FCPUSTATE_NAME UNWIND_GETREG_SCPUSTATE_NAME
#define UNWIND_SETREG_FCPUSTATE_NAME UNWIND_SETREG_SCPUSTATE_NAME
#endif /* ... */

#define UNWIND_GETREG_UCPUSTATE_NAME           "unwind_getreg_ucpustate"
#define UNWIND_SETREG_UCPUSTATE_NAME           "unwind_setreg_ucpustate"
#ifdef FCPUSTATE_IS_UCPUSTATE
#define unwind_getreg_ucpustate_exclusive      unwind_getreg_ucpustate
#define unwind_setreg_ucpustate_exclusive      unwind_setreg_ucpustate
#define UNWIND_GETREG_UCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_ucpustate"
#define UNWIND_SETREG_UCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_ucpustate"
#else /* FCPUSTATE_IS_UCPUSTATE */
#define UNWIND_GETREG_UCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_ucpustate_exclusive"
#define UNWIND_SETREG_UCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_ucpustate_exclusive"
#endif /* !FCPUSTATE_IS_UCPUSTATE */
#ifndef UNWIND_GETREG_LCPUSTATE_NAME
#define UNWIND_GETREG_LCPUSTATE_NAME           "unwind_getreg_lcpustate"
#define UNWIND_SETREG_LCPUSTATE_NAME           "unwind_setreg_lcpustate"
#ifdef FCPUSTATE_IS_LCPUSTATE
#define unwind_getreg_lcpustate_exclusive      unwind_getreg_lcpustate
#define unwind_setreg_lcpustate_exclusive      unwind_setreg_lcpustate
#define UNWIND_GETREG_LCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_lcpustate"
#define UNWIND_SETREG_LCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_lcpustate"
#else /* FCPUSTATE_IS_LCPUSTATE */
#define UNWIND_GETREG_LCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_lcpustate_exclusive"
#define UNWIND_SETREG_LCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_lcpustate_exclusive"
#endif /* !FCPUSTATE_IS_LCPUSTATE */
#endif /* !UNWIND_GETREG_LCPUSTATE_NAME */
#ifndef UNWIND_GETREG_KCPUSTATE_NAME
#define UNWIND_GETREG_KCPUSTATE_NAME           "unwind_getreg_kcpustate"
#define UNWIND_SETREG_KCPUSTATE_NAME           "unwind_setreg_kcpustate"
#ifdef FCPUSTATE_IS_KCPUSTATE
#define unwind_getreg_kcpustate_exclusive      unwind_getreg_kcpustate
#define unwind_setreg_kcpustate_exclusive      unwind_setreg_kcpustate
#define UNWIND_GETREG_KCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_kcpustate"
#define UNWIND_SETREG_KCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_kcpustate"
#else /* FCPUSTATE_IS_KCPUSTATE */
#define UNWIND_GETREG_KCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_kcpustate_exclusive"
#define UNWIND_SETREG_KCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_kcpustate_exclusive"
#endif /* !FCPUSTATE_IS_KCPUSTATE */
#endif /* !UNWIND_GETREG_KCPUSTATE_NAME */
#ifndef UNWIND_GETREG_FCPUSTATE_NAME
#define UNWIND_GETREG_FCPUSTATE_NAME "unwind_getreg_fcpustate"
#define UNWIND_SETREG_FCPUSTATE_NAME "unwind_setreg_fcpustate"
#endif /* !UNWIND_GETREG_FCPUSTATE_NAME */
#ifdef __KERNEL__
#ifndef UNWIND_GETREG_SCPUSTATE_NAME
#define UNWIND_GETREG_SCPUSTATE_NAME           "unwind_getreg_scpustate"
#define UNWIND_SETREG_SCPUSTATE_NAME           "unwind_setreg_scpustate"
#ifdef FCPUSTATE_IS_SCPUSTATE
#define unwind_getreg_scpustate_exclusive      unwind_getreg_scpustate
#define unwind_setreg_scpustate_exclusive      unwind_setreg_scpustate
#define UNWIND_GETREG_SCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_scpustate"
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_scpustate"
#else /* FCPUSTATE_IS_SCPUSTATE */
#define UNWIND_GETREG_SCPUSTATE_EXCLUSIVE_NAME "unwind_getreg_scpustate_exclusive"
#define UNWIND_SETREG_SCPUSTATE_EXCLUSIVE_NAME "unwind_setreg_scpustate_exclusive"
#endif /* !FCPUSTATE_IS_SCPUSTATE */
#endif /* !UNWIND_GETREG_SCPUSTATE_NAME */
#ifndef UNWIND_GETREG_ICPUSTATE_NAME
#define UNWIND_GETREG_ICPUSTATE_NAME           "unwind_getreg_icpustate"
#define UNWIND_SETREG_ICPUSTATE_NAME           "unwind_setreg_icpustate"
#ifdef FCPUSTATE_IS_ICPUSTATE
#define unwind_getreg_icpustate_exclusive      unwind_getreg_icpustate
#define unwind_setreg_icpustate_exclusive      unwind_setreg_icpustate
#define UNWIND_GETREG_ICPUSTATE_EXCLUSIVE_NAME "unwind_getreg_icpustate"
#define UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_NAME "unwind_setreg_icpustate"
#else /* FCPUSTATE_IS_ICPUSTATE */
#define UNWIND_GETREG_ICPUSTATE_EXCLUSIVE_NAME "unwind_getreg_icpustate_exclusive"
#define UNWIND_SETREG_ICPUSTATE_EXCLUSIVE_NAME "unwind_setreg_icpustate_exclusive"
#endif /* !FCPUSTATE_IS_ICPUSTATE */
#endif /* !UNWIND_GETREG_ICPUSTATE_EXCLUSIVE_NAME */
#endif /* __KERNEL__ */


#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucpustate)(/*struct ucpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucpustate_exclusive)(/*struct ucpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucpustate)(/*struct ucpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucpustate_exclusive)(/*struct ucpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_lcpustate)(/*struct lcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_lcpustate_exclusive)(/*struct lcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_lcpustate)(/*struct lcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_lcpustate_exclusive)(/*struct lcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_kcpustate)(/*struct kcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_kcpustate_exclusive)(/*struct kcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_kcpustate)(/*struct kcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_kcpustate_exclusive)(/*struct kcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_fcpustate)(/*struct fcpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fcpustate)(/*struct fcpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#ifdef __KERNEL__
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_scpustate)(/*struct scpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_scpustate_exclusive)(/*struct scpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_icpustate)(/*struct icpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_icpustate_exclusive)(/*struct icpustate **/ void const *__arg, unwind_regno_t __regno, void *__restrict __dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate)(/*struct scpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate_exclusive)(/*struct scpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate)(/*struct icpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) unsigned int __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate_exclusive)(/*struct icpustate **/ void *__arg, unwind_regno_t __regno, void const *__restrict __src);
#endif /* __KERNEL__ */
#else  /* LIBUNWIND_WANT_PROTOTYPES */
#undef unwind_getreg_ucpustate
#undef unwind_getreg_ucpustate_exclusive
#undef unwind_setreg_ucpustate
#undef unwind_setreg_ucpustate_exclusive
#undef unwind_getreg_lcpustate
#undef unwind_getreg_lcpustate_exclusive
#undef unwind_setreg_lcpustate
#undef unwind_setreg_lcpustate_exclusive
#undef unwind_getreg_kcpustate
#undef unwind_getreg_kcpustate_exclusive
#undef unwind_setreg_kcpustate
#undef unwind_setreg_kcpustate_exclusive
#undef unwind_getreg_fcpustate
#undef unwind_getreg_fcpustate_exclusive
#undef unwind_setreg_fcpustate
#undef unwind_setreg_fcpustate_exclusive
#ifdef __KERNEL__
#undef unwind_getreg_scpustate
#undef unwind_getreg_scpustate_exclusive
#undef unwind_getreg_icpustate
#undef unwind_getreg_icpustate_exclusive
#undef unwind_setreg_scpustate
#undef unwind_setreg_scpustate_exclusive
#undef unwind_setreg_icpustate
#undef unwind_setreg_icpustate_exclusive
#endif /* __KERNEL__ */
#endif /* !LIBUNWIND_WANT_PROTOTYPES */



/* Accessor functions for working with the register descriptor used by exception handling. */
#define PUNWIND_GETREG_EXCEPT_REGISTER_STATE _PUNWIND_GETREG_XCPUSTATE
#define PUNWIND_SETREG_EXCEPT_REGISTER_STATE _PUNWIND_SETREG_XCPUSTATE
#undef LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS
#ifdef __EXCEPT_REGISTER_STATE_TYPE_IS_LCPUSTATE
#define LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_LCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_LCPUSTATE_NAME
#define unwind_getreg_except_register_state      unwind_getreg_lcpustate
#define unwind_setreg_except_register_state      unwind_setreg_lcpustate
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_UCPUSTATE)
#define LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_UCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_UCPUSTATE_NAME
#define unwind_getreg_except_register_state      unwind_getreg_ucpustate
#define unwind_setreg_except_register_state      unwind_setreg_ucpustate
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE)
#define LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_KCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_KCPUSTATE_NAME
#define unwind_getreg_except_register_state      unwind_getreg_kcpustate
#define unwind_setreg_except_register_state      unwind_setreg_kcpustate
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_ICPUSTATE) && defined(__KERNEL__)
#define LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_ICPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_ICPUSTATE_NAME
#define unwind_getreg_except_register_state      unwind_getreg_icpustate
#define unwind_setreg_except_register_state      unwind_setreg_icpustate
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_SCPUSTATE) && defined(__KERNEL__)
#define LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_SCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_SCPUSTATE_NAME
#define unwind_getreg_except_register_state      unwind_getreg_scpustate
#define unwind_setreg_except_register_state      unwind_setreg_scpustate
#elif defined(__EXCEPT_REGISTER_STATE_TYPE_IS_FCPUSTATE)
#define LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS
#define UNWIND_GETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_GETREG_FCPUSTATE_NAME
#define UNWIND_SETREG_EXCEPT_REGISTER_STATE_NAME UNWIND_SETREG_FCPUSTATE_NAME
#define unwind_getreg_except_register_state      unwind_getreg_fcpustate
#define unwind_setreg_except_register_state      unwind_setreg_fcpustate
#endif /* ... */

#ifdef LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS
#ifndef LIBUNWIND_WANT_PROTOTYPES
#undef unwind_getreg_except_register_state
#undef unwind_setreg_except_register_state
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#else /* LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS */
#undef PUNWIND_GETREG_EXCEPT_REGISTER_STATE
#undef PUNWIND_SETREG_EXCEPT_REGISTER_STATE
#endif /* !LIBUNWIND_HAVE_EXCEPT_REGISTER_STATE_ACCESSORS */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBUNWIND_ARCH_REGISTER_H */
