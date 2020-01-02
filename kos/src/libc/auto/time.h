/* HASH CRC-32:0xe777f2c1 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_TIME_H
#define GUARD_LIBC_AUTO_TIME_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <time.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Return the difference between TIME1 and TIME0 */
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBCCALL libc_difftime)(time_t time1, time_t time0);
/* Return the `time_t' representation of TP and normalize TP */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time_t NOTHROW_NCX(LIBCCALL libc_mktime)(__STRUCT_TM __KOS_FIXED_CONST *tp);
/* Equivalent to `asctime (localtime (timer))' */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_ctime)(time_t const *timer);
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *NOTHROW_NCX(LIBCCALL libc_gmtime)(time_t const *timer);
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct tm *NOTHROW_NCX(LIBCCALL libc_localtime)(time_t const *timer);
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBCCALL libc_strftime)(char *__restrict buf, size_t bufsize, char const *__restrict format, __STRUCT_TM const *__restrict tp);
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_asctime)(struct tm const *tp);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_asctime_s)(char *__restrict buf, size_t buflen, struct tm const *__restrict tp);
/* Return the difference between TIME1 and TIME0 */
INTDEF ATTR_CONST WUNUSED double NOTHROW_NCX(LIBCCALL libc_difftime64)(time64_t time1, time64_t time0);
/* Return the `time_t' representation of TP and normalize TP */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time64_t NOTHROW_NCX(LIBCCALL libc_mktime64)(__STRUCT_TM __KOS_FIXED_CONST *tp);
/* Equivalent to `asctime (localtime (timer))' */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_ctime64)(time64_t const *timer);
/* Return the `struct tm' representation of *TIMER
 * in Universal Coordinated Time (aka Greenwich Mean Time) */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_gmtime64)(time64_t const *timer);
/* Return the `struct tm' representation of *TIMER in the local timezone */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_localtime64)(time64_t const *timer);
/* Like `mktime', but for TP represents Universal Time, not local time */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time_t NOTHROW_NCX(LIBCCALL libc_timegm)(__STRUCT_TM *tp);
/* Another name for `mktime' */
#define libc_timelocal libc_mktime
/* Return the number of days in YEAR */
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc_dysize)(int year);
/* Like `mktime', but for TP represents Universal Time, not local time */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) time64_t NOTHROW_NCX(LIBCCALL libc_timegm64)(__STRUCT_TM *tp);
/* Another name for `mktime64' */
#define libc_timelocal64 libc_mktime64
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
INTDEF NONNULL((1, 3, 4)) size_t NOTHROW_NCX(LIBCCALL libc_strftime_l)(char *__restrict buf, size_t bufsize, char const *__restrict format, __STRUCT_TM const *__restrict tp, locale_t locale);
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
INTDEF NONNULL((1, 2, 3)) char *NOTHROW_NCX(LIBCCALL libc_strptime)(char const *__restrict s, char const *__restrict format, __STRUCT_TM *__restrict tp);
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
INTDEF NONNULL((1, 2, 3)) char *NOTHROW_NCX(LIBCCALL libc_strptime_l)(char const *__restrict s, char const *__restrict format, __STRUCT_TM *__restrict tp, locale_t locale);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_getdate_r)(char const *__restrict string, __STRUCT_TM *__restrict resbufp);
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_gmtime_r)(time_t const *__restrict timer, __STRUCT_TM *__restrict tp);
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_localtime_r)(time_t const *__restrict timer, __STRUCT_TM *__restrict tp);
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_ctime_r)(time_t const *__restrict timer, char buf[26]);
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_gmtime64_r)(time64_t const *__restrict timer, __STRUCT_TM *__restrict tp);
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
INTDEF NONNULL((1, 2)) __STRUCT_TM *NOTHROW_NCX(LIBCCALL libc_localtime64_r)(time64_t const *__restrict timer, __STRUCT_TM *__restrict tp);
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_ctime64_r)(time64_t const *__restrict timer, char buf[26]);
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_asctime_r)(__STRUCT_TM const *__restrict tp, char buf[26]);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_TIME_H */
