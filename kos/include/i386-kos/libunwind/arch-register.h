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
#ifndef _I386_KOS_LIBUNWIND_ARCH_REGISTER_H
#define _I386_KOS_LIBUNWIND_ARCH_REGISTER_H 1

#include "../../libunwind/api.h"

#ifdef __CC__
__DECL_BEGIN

/* Register accessor callbacks for a variety of known cpu context structures.
 * NOTE: When the intent is to unwind both CPU and FPU registers, you must create
 *       your own custom register get/set functions that call forward to the functions
 *       below:
 * >> bool LIBUNWIND_CC my_getreg(void const *arg, uintptr_half_t regno, void *dst) {
 * >>     struct my_cpustate_with_fpu const *me;
 * >>     me = (struct my_cpustate_with_fpu const *)arg;
 * >>     if (unwind_getreg_xfpustate(me->cs_fpu, regno, dst))
 * >>         return true;
 * >>     if (unwind_getreg_ufpustate(me->cs_cpu, regno, dst))
 * >>         return true;
 * >>     return false;
 * >> }
 * >> bool LIBUNWIND_CC my_setreg(void *arg, uintptr_half_t regno, void const *src) {
 * >>     struct my_cpustate_with_fpu *me;
 * >>     me = (struct my_cpustate_with_fpu *)arg;
 * >>     if (unwind_setreg_xfpustate(me->cs_fpu, regno, src))
 * >>         return true;
 * >>     if (unwind_setreg_ufpustate(me->cs_cpu, regno, src))
 * >>         return true;
 * >>     return false;
 * >> }
 */
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_LCPUSTATE)(/*struct lcpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_LCPUSTATE)(/*struct lcpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_UCPUSTATE)(/*struct ucpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_UCPUSTATE)(/*struct ucpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_KCPUSTATE)(/*struct kcpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_KCPUSTATE)(/*struct kcpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_FCPUSTATE)(/*struct fcpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_FCPUSTATE)(/*struct fcpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_SFPUSTATE)(/*struct sfpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_SFPUSTATE)(/*struct sfpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_XFPUSTATE)(/*struct xfpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_XFPUSTATE)(/*struct xfpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
#ifdef __KERNEL__
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_SCPUSTATE)(/*struct scpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_SCPUSTATE)(/*struct scpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_ICPUSTATE)(/*struct icpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_ICPUSTATE)(/*struct icpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
#endif /* __KERNEL__ */
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_lcpustate)(/*struct lcpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_lcpustate)(/*struct lcpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucpustate)(/*struct ucpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucpustate)(/*struct ucpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_kcpustate)(/*struct kcpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_kcpustate)(/*struct kcpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_fcpustate)(/*struct fcpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_fcpustate)(/*struct fcpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_sfpustate)(/*struct sfpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_sfpustate)(/*struct sfpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_xfpustate)(/*struct xfpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_xfpustate)(/*struct xfpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
#ifdef __KERNEL__
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_scpustate)(/*struct scpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_scpustate)(/*struct scpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_icpustate)(/*struct icpustate*/void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_icpustate)(/*struct icpustate*/void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
#endif /* __KERNEL__ */
#endif /* LIBUNWIND_WANT_PROTOTYPES */




/* Accessor functions for working with the register descriptor used by exception handling. */
#define LIBUNWIND_HAVE_ERROR_REGISTER_STATE_ACCESSORS 1
typedef PUNWIND_GETREG_KCPUSTATE PUNWIND_GETREG_ERROR_REGISTER_STATE;
typedef PUNWIND_SETREG_KCPUSTATE PUNWIND_SETREG_ERROR_REGISTER_STATE;
#define UNWIND_GETREG_ERROR_REGISTER_STATE_NAME "unwind_getreg_kcpustate"
#define UNWIND_SETREG_ERROR_REGISTER_STATE_NAME "unwind_setreg_kcpustate"
#ifdef LIBUNWIND_WANT_PROTOTYPES
#define unwind_getreg_error_register_state       unwind_getreg_kcpustate
#define unwind_setreg_error_register_state       unwind_setreg_kcpustate
#endif /* LIBUNWIND_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_LIBUNWIND_ARCH_REGISTER_H */
