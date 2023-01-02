/* HASH CRC-32:0x9a6a6629 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_STRINGS_H
#define GUARD_LIBC_AUTO_STRINGS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <strings.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_popcount)(unsigned int i);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_popcount)(unsigned int i);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_popcountl)(unsigned long i);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_popcountl)(unsigned long i);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_popcountll)(__ULONGLONG i);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_popcountll)(__ULONGLONG i);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_popcount32)(uint32_t i);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_popcount32)(uint32_t i);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_popcount64)(uint64_t i);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_popcount64)(uint64_t i);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STRINGS_H */
