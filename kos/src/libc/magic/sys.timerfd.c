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

%[define_replacement(fd_t = __fd_t)]
%[default_impl_section(".text.crt.timer")]

%{
#include <time.h>
#include <bits/timerfd.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/timerfd.h */
/* Copyright (C) 2008-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* Bits to be set in the FLAGS parameter of `timerfd_settime'.  */
#ifdef __COMPILER_PREFERR_ENUMS
enum {
	TFD_TIMER_ABSTIME = 1
#define TFD_TIMER_ABSTIME TFD_TIMER_ABSTIME
};
#else /* __COMPILER_PREFERR_ENUMS */
#define TFD_TIMER_ABSTIME 1
#endif /* !__COMPILER_PREFERR_ENUMS */


#ifdef __CC__

}


[[doc_alias("timerfd_settime"), ignore, nocrt, alias("timerfd_settime")]]
int timerfd_settime32($fd_t ufd, int flags,
                      [[nonnull]] struct __itimerspec32 const *utmr,
                      [[nullable]] struct __itimerspec32 *otmr);

[[doc_alias("timerfd_gettime"), ignore, nocrt, alias("timerfd_gettime")]]
int timerfd_gettime32($fd_t ufd, [[nonnull]] struct __itimerspec32 *__restrict otmr);


@@Return file descriptor for new interval timer source
[[nothrow]]
$fd_t timerfd_create(clockid_t clock_id, int flags);

@@Set next expiration time of interval timer source UFD to UTMR.
@@If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout utmr
@@is absolute. Optionally return the old expiration time in OTMR
[[no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("timerfd_settime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("timerfd_settime")]]
[[userimpl, requires($has_function(timerfd_settime32) || $has_function(timerfd_settime64))]]
int timerfd_settime($fd_t ufd, int flags,
                     [[nonnull]] struct itimerspec const *utmr,
                     [[nullable]] struct itimerspec *otmr) {
@@pp_if $has_function(timerfd_settime32)@@
	int result;
	struct __itimerspec32 utmr32, otmr32;
	utmr32.it_interval.tv_sec  = (__time32_t)utmr->it_interval.tv_sec;
	utmr32.it_interval.tv_nsec = utmr->it_interval.tv_nsec;
	utmr32.it_value.tv_sec     = (__time32_t)utmr->it_value.tv_sec;
	utmr32.it_value.tv_nsec    = utmr->it_value.tv_nsec;
	result = timerfd_settime32(ufd, flags, &utmr32, otmr ? &otmr32 : NULL);
	if (!result && otmr) {
		otmr->it_interval.tv_sec  = (__time64_t)otmr32.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr32.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (__time64_t)otmr32.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr32.it_value.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct __itimerspec64 utmr64, otmr64;
	utmr64.it_interval.tv_sec  = (__time64_t)utmr->it_interval.tv_sec;
	utmr64.it_interval.tv_nsec = utmr->it_interval.tv_nsec;
	utmr64.it_value.tv_sec     = (__time64_t)utmr->it_value.tv_sec;
	utmr64.it_value.tv_nsec    = utmr->it_value.tv_nsec;
	result = timerfd_settime64(timerid, flags, &utmr64, otmr ? &otmr64 : NULL);
	if (!result && otmr) {
		otmr->it_interval.tv_sec  = (__time32_t)otmr64.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr64.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (__time32_t)otmr64.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr64.it_value.tv_nsec;
	}
	return result;
@@pp_endif@@
}

@@Return the next expiration time of UFD
[[no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("timerfd_gettime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("timerfd_gettime")]]
[[userimpl, requires($has_function(timerfd_gettime32) || $has_function(timerfd_gettime64))]]
int timerfd_gettime($fd_t ufd, [[nonnull]] struct itimerspec *__restrict otmr) {
@@pp_if $has_function(timerfd_gettime32)@@
	int result;
	struct __itimerspec32 otmr32;
	result = timerfd_gettime32(timerid, &otmr32);
	if (!result) {
		otmr->it_interval.tv_sec  = (__time64_t)otmr32.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr32.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (__time64_t)otmr32.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr32.it_value.tv_nsec;
	}
	return result;
@@pp_else@@
	int result;
	struct __itimerspec64 otmr64;
	result = timerfd_gettime64(timerid, &otmr64);
	if (!result) {
		otmr->it_interval.tv_sec  = (__time32_t)otmr64.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr64.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (__time32_t)otmr64.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr64.it_value.tv_nsec;
	}
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64

[[time64_variant_of(timerfd_settime)]]
[[userimpl, requires_function(timerfd_settime32)]]
int timerfd_settime64($fd_t ufd, int flags,
                      [[nonnull]] struct itimerspec64 const *utmr,
                      [[nullable]] struct itimerspec64 *otmr) {
	int result;
	struct __itimerspec32 utmr32, otmr32;
	utmr32.it_interval.tv_sec  = (__time32_t)utmr->it_interval.tv_sec;
	utmr32.it_interval.tv_nsec = utmr->it_interval.tv_nsec;
	utmr32.it_value.tv_sec     = (__time32_t)utmr->it_value.tv_sec;
	utmr32.it_value.tv_nsec    = utmr->it_value.tv_nsec;
	result = timerfd_settime32(ufd, flags, &utmr32, otmr ? &otmr32 : NULL);
	if (!result && otmr) {
		otmr->it_interval.tv_sec  = (__time64_t)otmr32.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr32.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (__time64_t)otmr32.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr32.it_value.tv_nsec;
	}
	return result;
}

[[time64_variant_of(timerfd_gettime)]]
[[userimpl, requires_function(timerfd_gettime32)]]
int timerfd_gettime64($fd_t ufd, [[nonnull]] struct itimerspec64 *__restrict otmr) {
	int result;
	struct __itimerspec32 otmr32;
	result = timerfd_gettime32(timerid, &otmr32);
	if (!result) {
		otmr->it_interval.tv_sec  = (__time64_t)otmr32.it_interval.tv_sec;
		otmr->it_interval.tv_nsec = otmr32.it_interval.tv_nsec;
		otmr->it_value.tv_sec     = (__time64_t)otmr32.it_value.tv_sec;
		otmr->it_value.tv_nsec    = otmr32.it_value.tv_nsec;
	}
	return result;
}

%#endif /* __USE_TIME64 */

%{
#endif /* __CC__ */

__SYSDECL_END

}