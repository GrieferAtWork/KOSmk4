/* HASH CRC-32:0x6220e910 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_TIME_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_TIME_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.time.h"

DECL_BEGIN

/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_gettimeofday)(struct timeval *__restrict tv,
                                        __timezone_ptr_t tz) {
	return libc_gettimeofday(tv, tz);
}
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_getitimer)(__itimer_which_t which,
                                     struct itimerval *curr_value) {
	return libc_getitimer(which, curr_value);
}
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_setitimer)(__itimer_which_t which,
                                     struct itimerval const *newval,
                                     struct itimerval *oldval) {
	return libc_setitimer(which, newval, oldval);
}
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_utimes)(char const *file,
                                  struct timeval const tvp[2]) {
	return libc_utimes(file, tvp);
}
/* Same as `utimes', but takes an open file descriptor instead of a name */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_futimesat)(fd_t fd,
                                     char const *file,
                                     struct timeval const tvp[2]) {
	return libc_futimesat(fd, file, tvp);
}
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
INTERN ATTR_SECTION(".text.crt.dos.system.adjtime") int
NOTHROW_NCX(LIBDCALL libd_settimeofday)(struct timeval const *tv,
                                        struct timezone const *tz) {
	return libc_settimeofday(tv, tz);
}
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
INTERN ATTR_SECTION(".text.crt.dos.system.adjtime") int
NOTHROW_NCX(LIBDCALL libd_adjtime)(struct timeval const *delta,
                                   struct timeval *olddelta) {
	return libc_adjtime(delta, olddelta);
}
/* Same as `utimes', but does not follow symbolic links */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_lutimes)(char const *file,
                                   struct timeval const tvp[2]) {
	return libc_lutimes(file, tvp);
}
/* Same as `utimes', but takes an open file descriptor instead of a name */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") int
NOTHROW_NCX(LIBDCALL libd_futimes)(fd_t fd,
                                   struct timeval const tvp[2]) {
	return libc_futimes(fd, tvp);
}
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_gettimeofday64)(struct timeval64 *__restrict tv,
                                          __timezone_ptr_t tz) {
	return libc_gettimeofday64(tv, tz);
}
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_getitimer64)(__itimer_which_t which,
                                       struct itimerval64 *curr_value) {
	return libc_getitimer64(which, curr_value);
}
/* Set the timer WHICH to *NEWVAL. If OLDVAL is not NULL, set *OLDVAL to the old value of timer WHICH.
 * Returns 0 on success, -1 on errors */
INTERN ATTR_SECTION(".text.crt.dos.time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_setitimer64)(__itimer_which_t which,
                                       struct itimerval64 const *newval,
                                       struct itimerval64 *oldval) {
	return libc_setitimer64(which, newval, oldval);
}
/* Change the access time of FILE to TVP[0] and the modification time of
 * FILE to TVP[1]. If TVP is a null pointer, use the current time instead.
 * Returns 0 on success, -1 on errors */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_utimes64)(char const *file,
                                    struct timeval64 const tvp[2]) {
	return libc_utimes64(file, tvp);
}
/* Set the current time of day and timezone information.
 * This call is restricted to the super-user */
INTERN ATTR_SECTION(".text.crt.dos.system.adjtime") int
NOTHROW_NCX(LIBDCALL libd_settimeofday64)(struct timeval64 const *tv,
                                          struct timezone const *tz) {
	return libc_settimeofday64(tv, tz);
}
/* Adjust the current time of day by the amount in DELTA.
 * If OLDDELTA is not NULL, it is filled in with the amount of time
 * adjustment remaining to be done from the last `adjtime' call.
 * This call is restricted to the super-user */
INTERN ATTR_SECTION(".text.crt.dos.system.adjtime") int
NOTHROW_NCX(LIBDCALL libd_adjtime64)(struct timeval64 const *delta,
                                     struct timeval64 *olddelta) {
	return libc_adjtime64(delta, olddelta);
}
/* Same as `utimes', but does not follow symbolic links */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_lutimes64)(char const *file,
                                     struct timeval64 const tvp[2]) {
	return libc_lutimes64(file, tvp);
}
/* Same as `utimes', but does not follow symbolic links */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") int
NOTHROW_NCX(LIBDCALL libd_futimes64)(fd_t fd,
                                     struct timeval64 const tvp[2]) {
	return libc_futimes64(fd, tvp);
}
/* Same as `utimes', but takes an open file descriptor instead of a name */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_futimesat64)(fd_t fd,
                                       char const *file,
                                       struct timeval64 const tvp[2]) {
	return libc_futimesat64(fd, file, tvp);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__gettimeofday, libd_gettimeofday);
DEFINE_PUBLIC_ALIAS(DOS$gettimeofday, libd_gettimeofday);
DEFINE_PUBLIC_ALIAS(DOS$getitimer, libd_getitimer);
DEFINE_PUBLIC_ALIAS(DOS$setitimer, libd_setitimer);
DEFINE_PUBLIC_ALIAS(DOS$utimes, libd_utimes);
DEFINE_PUBLIC_ALIAS(DOS$futimesat, libd_futimesat);
DEFINE_PUBLIC_ALIAS(DOS$settimeofday, libd_settimeofday);
DEFINE_PUBLIC_ALIAS(DOS$adjtime, libd_adjtime);
DEFINE_PUBLIC_ALIAS(DOS$lutimes, libd_lutimes);
DEFINE_PUBLIC_ALIAS(DOS$futimes, libd_futimes);
DEFINE_PUBLIC_ALIAS(DOS$gettimeofday64, libd_gettimeofday64);
DEFINE_PUBLIC_ALIAS(DOS$getitimer64, libd_getitimer64);
DEFINE_PUBLIC_ALIAS(DOS$setitimer64, libd_setitimer64);
DEFINE_PUBLIC_ALIAS(DOS$utimes64, libd_utimes64);
DEFINE_PUBLIC_ALIAS(DOS$settimeofday64, libd_settimeofday64);
DEFINE_PUBLIC_ALIAS(DOS$adjtime64, libd_adjtime64);
DEFINE_PUBLIC_ALIAS(DOS$lutimes64, libd_lutimes64);
DEFINE_PUBLIC_ALIAS(DOS$futimes64, libd_futimes64);
DEFINE_PUBLIC_ALIAS(DOS$futimesat64, libd_futimesat64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_TIME_C */
