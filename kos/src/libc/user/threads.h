/* HASH CRC-32:0x5edc8a5f */
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
#ifndef GUARD_LIBC_USER_THREADS_H
#define GUARD_LIBC_USER_THREADS_H 1

#include "../api.h"
#include "../auto/threads.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <threads.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBCCALL libc_thrd_sleep)(struct timespec const *time_point, struct timespec *remaining);
/* >> thrd_sleep(3), thrd_sleep64(3)
 * Sleep until a signal is received, or `time_point' has elapsed (s.a. `nanosleep(2)')
 * @return:     0: The (relative) time specified by `time_point' has elapsed
 * @return:    -1: A signal was received while waiting, and `remaining' was filled in (if given)
 * @return: <= -2: Some other error occurred */
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBCCALL libc_thrd_sleep64)(struct timespec64 const *time_point, struct timespec64 *remaining);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_THREADS_H */
