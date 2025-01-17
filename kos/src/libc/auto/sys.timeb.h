/* HASH CRC-32:0xd1fca3fd */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_SYS_TIMEB_H
#define GUARD_LIBC_AUTO_SYS_TIMEB_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/timeb.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd__ftime32)(struct timeb32 *timebuf);
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd__ftime64)(struct timeb64 *timebuf);
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd__ftime32_s)(struct timeb32 *timebuf);
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd__ftime64_s)(struct timeb64 *timebuf);
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_ftime)(struct timeb *timebuf);
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_ftime64)(struct timeb64 *timebuf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_TIMEB_H */
