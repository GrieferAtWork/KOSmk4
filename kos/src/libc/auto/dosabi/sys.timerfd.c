/* HASH CRC-32:0x30dcc4a0 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_TIMERFD_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_TIMERFD_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.timerfd.h"

DECL_BEGIN

/* Return file descriptor for new interval timer source */
INTERN ATTR_SECTION(".text.crt.dos.timer") fd_t
NOTHROW(LIBDCALL libd_timerfd_create)(clockid_t clock_id,
                                      __STDC_INT_AS_UINT_T flags) {
	return libc_timerfd_create(clock_id, flags);
}
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
INTERN ATTR_SECTION(".text.crt.dos.timer") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_timerfd_settime)(fd_t ufd,
                                           __STDC_INT_AS_UINT_T flags,
                                           struct itimerspec const *utmr,
                                           struct itimerspec *otmr) {
	return libc_timerfd_settime(ufd, flags, utmr, otmr);
}
/* Return the next expiration time of UFD */
INTERN ATTR_SECTION(".text.crt.dos.timer") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_timerfd_gettime)(fd_t ufd,
                                           struct itimerspec *__restrict otmr) {
	return libc_timerfd_gettime(ufd, otmr);
}
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
 * is absolute. Optionally return the old expiration time in OTMR */
INTERN ATTR_SECTION(".text.crt.dos.timer") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_timerfd_settime64)(fd_t ufd,
                                             __STDC_INT_AS_UINT_T flags,
                                             struct itimerspec64 const *utmr,
                                             struct itimerspec64 *otmr) {
	return libc_timerfd_settime64(ufd, flags, utmr, otmr);
}
/* Return the next expiration time of UFD */
INTERN ATTR_SECTION(".text.crt.dos.timer") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_timerfd_gettime64)(fd_t ufd,
                                             struct itimerspec64 *__restrict otmr) {
	return libc_timerfd_gettime64(ufd, otmr);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$timerfd_create, libd_timerfd_create);
DEFINE_PUBLIC_ALIAS(DOS$timerfd_settime, libd_timerfd_settime);
DEFINE_PUBLIC_ALIAS(DOS$timerfd_gettime, libd_timerfd_gettime);
DEFINE_PUBLIC_ALIAS(DOS$timerfd_settime64, libd_timerfd_settime64);
DEFINE_PUBLIC_ALIAS(DOS$timerfd_gettime64, libd_timerfd_gettime64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_TIMERFD_C */
