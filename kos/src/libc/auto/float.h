/* HASH CRC-32:0x9010d9a7 */
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
#ifndef GUARD_LIBC_AUTO_FLOAT_H
#define GUARD_LIBC_AUTO_FLOAT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <float.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBCCALL libc___fpe_flt_rounds)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF uint32_t NOTHROW_NCX(LIBDCALL libd__controlfp)(uint32_t newval, uint32_t mask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF uint32_t NOTHROW_NCX(LIBCCALL libc__controlfp)(uint32_t newval, uint32_t mask);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd__set_controlfp)(uint32_t newval, uint32_t mask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc__set_controlfp)(uint32_t newval, uint32_t mask);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd__controlfp_s)(uint32_t *pcurrent, uint32_t newval, uint32_t mask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc__controlfp_s)(uint32_t *pcurrent, uint32_t newval, uint32_t mask);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd__statusfp2)(uint32_t *x86_stat, uint32_t *sse2_stat);
INTDEF uint32_t NOTHROW_NCX(LIBDCALL libd__control87)(uint32_t newval, uint32_t mask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF uint32_t NOTHROW_NCX(LIBCCALL libc__control87)(uint32_t newval, uint32_t mask);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd___control87_2)(uint32_t newval, uint32_t mask, uint32_t *x86_control_word, uint32_t *sse2_control_word);
/* >> _fpclass(3)
 * @return: * : Set of `_FPCLASS_*' */
INTDEF ATTR_CONST WUNUSED int NOTHROW(LIBDCALL libd__fpclass)(double x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FLOAT_H */
