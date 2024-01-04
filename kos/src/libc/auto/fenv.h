/* HASH CRC-32:0xfc7023bc */
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
#ifndef GUARD_LIBC_AUTO_FENV_H
#define GUARD_LIBC_AUTO_FENV_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fenv.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*' */
INTDEF int NOTHROW(LIBDCALL libd_feclearexcept)(int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*' */
INTDEF int NOTHROW(LIBCCALL libc_feclearexcept)(int excepts);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*' */
INTDEF int (LIBDCALL libd_feraiseexcept)(int excepts) THROWS(...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*' */
INTDEF int (LIBCCALL libc_feraiseexcept)(int excepts) THROWS(...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fegetexceptflag(3) */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_fegetexceptflag)(fexcept_t *flagp, int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fegetexceptflag(3) */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_fegetexceptflag)(fexcept_t *flagp, int excepts);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fesetexceptflag(3) */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_fesetexceptflag)(fexcept_t const *flagp, int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fesetexceptflag(3) */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_fesetexceptflag)(fexcept_t const *flagp, int excepts);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fetestexcept(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBDCALL libd_fetestexcept)(int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fetestexcept(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBCCALL libc_fetestexcept)(int excepts);
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBCCALL libc_fegetround)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTDEF int NOTHROW(LIBDCALL libd_fesetround)(int rounding_direction);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTDEF int NOTHROW(LIBCCALL libc_fesetround)(int rounding_direction);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fegetenv(3) */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_fegetenv)(fenv_t *envp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fegetenv(3) */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_fegetenv)(fenv_t *envp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> feholdexcept(3) */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_feholdexcept)(fenv_t *envp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> feholdexcept(3) */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_feholdexcept)(fenv_t *envp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fesetenv(3) */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_fesetenv)(fenv_t const *envp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fesetenv(3) */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_fesetenv)(fenv_t const *envp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> feupdateenv(3) */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_feupdateenv)(fenv_t const *envp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> feupdateenv(3) */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_feupdateenv)(fenv_t const *envp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> feenableexcept(3) */
INTDEF int NOTHROW(LIBDCALL libd_feenableexcept)(int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> feenableexcept(3) */
INTDEF int NOTHROW(LIBCCALL libc_feenableexcept)(int excepts);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fedisableexcept(3) */
INTDEF int NOTHROW(LIBDCALL libd_fedisableexcept)(int excepts);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fedisableexcept(3) */
INTDEF int NOTHROW(LIBCCALL libc_fedisableexcept)(int excepts);
/* >> fegetexcept(3) */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBCCALL libc_fegetexcept)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd_fesetexcept)(int excepts);
INTDEF int NOTHROW_NCX(LIBDCALL libd_fetestexceptflag)(fexcept_t const *flagp, int excepts);
INTDEF int NOTHROW_NCX(LIBDCALL libd_fegetmode)(femode_t *modep);
INTDEF int NOTHROW_NCX(LIBDCALL libd_fesetmode)(femode_t const *modep);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FENV_H */
