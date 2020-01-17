/* HASH CRC-32:0x9b3b6795 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_TIME_H
#define GUARD_LIBC_USER_SYS_TIME_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/time.h>

DECL_BEGIN

/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_gettimeofday)(struct timeval *__restrict tv, __timezone_ptr_t tz);
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_getitimer)(__itimer_which_t which, struct itimerval *curr_value);
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_setitimer)(__itimer_which_t which, struct itimerval const *newval, struct itimerval *oldval);
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_utimes)(char const *file, struct timeval const tvp[2]);
/* Same as `utimes', but takes an open file descriptor instead of a name */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_futimesat)(fd_t fd, char const *file, struct timeval const tvp[2]);
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
INTDEF int NOTHROW_NCX(LIBCCALL libc_settimeofday)(struct timeval const *tv, struct timezone const *tz);
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
INTDEF int NOTHROW_NCX(LIBCCALL libc_adjtime)(struct timeval const *delta, struct timeval *olddelta);
/* Same as `utimes', but does not follow symbolic links */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_lutimes)(char const *file, struct timeval const tvp[2]);
/* Same as `utimes', but takes an open file descriptor instead of a name */
INTDEF int NOTHROW_NCX(LIBCCALL libc_futimes)(fd_t fd, struct timeval const tvp[2]);
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_gettimeofday64)(struct timeval64 *__restrict tv, __timezone_ptr_t tz);
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_getitimer64)(__itimer_which_t which, struct itimerval64 *curr_value);
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_setitimer64)(__itimer_which_t which, struct itimerval64 const *newval, struct itimerval64 *oldval);
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_utimes64)(char const *file, struct timeval64 const tvp[2]);
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
INTDEF int NOTHROW_NCX(LIBCCALL libc_settimeofday64)(struct timeval64 const *tv, struct timezone const *tz);
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
INTDEF int NOTHROW_NCX(LIBCCALL libc_adjtime64)(struct timeval64 const *delta, struct timeval64 *olddelta);
/* Same as `utimes', but does not follow symbolic links */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_lutimes64)(char const *file, struct timeval64 const tvp[2]);
/* Same as `utimes', but does not follow symbolic links */
INTDEF int NOTHROW_NCX(LIBCCALL libc_futimes64)(fd_t fd, struct timeval64 const tvp[2]);
/* Same as `utimes', but takes an open file descriptor instead of a name */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_futimesat64)(fd_t fd, char const *file, struct timeval64 const tvp[2]);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIME_H */
