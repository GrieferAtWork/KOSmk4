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
/* (#) Portability: libbsd (/include/bsd/sys/time.h) */
#ifndef _BSD_SYS_TIME_H
#define _BSD_SYS_TIME_H 1

#include <sys/time.h>

#ifdef __CC__
#ifndef TIMEVAL_TO_TIMESPEC
#define TIMEVAL_TO_TIMESPEC(tv, ts) \
	(void)((ts)->tv_sec = (tv)->tv_sec, (ts)->tv_nsec = (tv)->tv_usec * 1000)
#endif /* !TIMEVAL_TO_TIMESPEC */
#ifndef TIMESPEC_TO_TIMEVAL
#define TIMESPEC_TO_TIMEVAL(tv, ts) \
	(void)((tv)->tv_sec = (ts)->tv_sec, (tv)->tv_usec = (ts)->tv_nsec / 1000)
#endif /* !TIMESPEC_TO_TIMEVAL */

#ifndef timerisset
#define timerisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#endif /* !timerisset */
#ifndef timerclear
#define timerclear(tvp) ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#endif /* !timerclear */
#ifndef timercmp
#define timercmp(a, b, CMP)            \
	(((a)->tv_sec == (b)->tv_sec)      \
	 ? ((a)->tv_usec CMP (b)->tv_usec) \
	 : ((a)->tv_sec CMP (b)->tv_sec))
#endif /* !timercmp */
#ifndef timeradd
#define timeradd(a, b, result)                           \
	do {                                                 \
		(result)->tv_sec  = (a)->tv_sec + (b)->tv_sec;   \
		(result)->tv_usec = (a)->tv_usec + (b)->tv_usec; \
		if ((result)->tv_usec >= 1000000) {              \
			++(result)->tv_sec;                          \
			(result)->tv_usec -= 1000000;                \
		}                                                \
	}	__WHILE0
#endif /* !timeradd */
#ifndef timersub
#define timersub(a, b, result)                           \
	do {                                                 \
		(result)->tv_sec  = (a)->tv_sec - (b)->tv_sec;   \
		(result)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
		if ((result)->tv_usec < 0) {                     \
			--(result)->tv_sec;                          \
			(result)->tv_usec += 1000000;                \
		}                                                \
	}	__WHILE0
#endif /* !timersub */
#ifndef timespecisset
#define timespecisset(tsp) ((tsp)->tv_sec || (tsp)->tv_nsec)
#endif /* !timespecisset */
#ifndef timespecclear
#define timespecclear(tsp) ((tsp)->tv_sec = 0, (tsp)->tv_nsec = 0)
#endif /* !timespecclear */
#ifndef timespeccmp
#define timespeccmp(a, b, CMP)         \
	(((a)->tv_sec == (b)->tv_sec)      \
	 ? ((a)->tv_nsec CMP (b)->tv_nsec) \
	 : ((a)->tv_sec CMP (b)->tv_sec))
#endif /* !timespeccmp */
#ifndef timespecadd
#define timespecadd(tsp, usp, vsp)                        \
	do {                                                  \
		(vsp)->tv_sec  = (tsp)->tv_sec + (usp)->tv_sec;   \
		(vsp)->tv_nsec = (tsp)->tv_nsec + (usp)->tv_nsec; \
		if ((vsp)->tv_nsec >= 1000000000L) {              \
			++(vsp)->tv_sec;                              \
			(vsp)->tv_nsec -= 1000000000L;                \
		}                                                 \
	}	__WHILE0
#endif /* !timespecadd */
#ifndef timespecsub
#define timespecsub(tsp, usp, vsp)                        \
	do {                                                  \
		(vsp)->tv_sec  = (tsp)->tv_sec - (usp)->tv_sec;   \
		(vsp)->tv_nsec = (tsp)->tv_nsec - (usp)->tv_nsec; \
		if ((vsp)->tv_nsec < 0) {                         \
			--(vsp)->tv_sec;                              \
			(vsp)->tv_nsec += 1000000000L;                \
		}                                                 \
	}	__WHILE0
#endif /* !timespecsub */
#endif /* __CC__ */

#endif /* !_BSD_SYS_TIME_H */
