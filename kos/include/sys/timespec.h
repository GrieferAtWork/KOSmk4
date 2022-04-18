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
/* (#) Portability: Cygwin    (/newlib/libc/include/sys/timespec.h) */
/* (#) Portability: EMX kLIBC (/libc/include/sys/timespec.h) */
/* (#) Portability: FreeBSD   (/sys/sys/timespec.h) */
/* (#) Portability: NetBSD    (/sys/sys/timespec.h) */
/* (#) Portability: Newlib    (/newlib/libc/include/sys/timespec.h) */
#ifndef _SYS_TIMESPEC_H
#define _SYS_TIMESPEC_H 1

#include <__stdinc.h>
#include <features.h>

#include <sys/_timespec.h>
#include <sys/cdefs.h>

#ifdef __USE_BSD
#ifndef TIMEVAL_TO_TIMESPEC
#define TIMEVAL_TO_TIMESPEC(tv, ts) \
	(void)((ts)->tv_sec = (tv)->tv_sec, (ts)->tv_nsec = (tv)->tv_usec * 1000)
#endif /* !TIMEVAL_TO_TIMESPEC */
#ifndef TIMESPEC_TO_TIMEVAL
#define TIMESPEC_TO_TIMEVAL(tv, ts) \
	(void)((tv)->tv_sec = (ts)->tv_sec, (tv)->tv_usec = (ts)->tv_nsec / 1000)
#endif /* !TIMESPEC_TO_TIMEVAL */
#endif /* __USE_BSD */

#include <bits/os/itimerspec.h> /* struct itimerspec */

#endif /* !_SYS_TIMESPEC_H */
