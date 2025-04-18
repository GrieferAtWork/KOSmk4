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
/*!included_by <locale.h>*/
/*!included_by <time.h>*/
/*!included_by <wchar.h>*/
#ifndef _BITS_CRT_TM_H
#define _BITS_CRT_TM_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <features.h>

#include <hybrid/typecore.h>

#if defined(__CRT_KOS) || defined(__CRT_GLC)
#ifdef __USE_MISC
#define __STRUCT_TM_HAVE_TM_GMTOFF 1
#define __STRUCT_TM_HAVE_TM_ZONE   1
#endif /* __USE_MISC */
#endif /* __CRT_KOS || __CRT_GLC */

#ifdef __CC__
__DECL_BEGIN
__NAMESPACE_STD_BEGIN
struct tm {
	int              tm_sec;      /* seconds [0, 61]. */
	int              tm_min;      /* minutes [0, 59]. */
	int              tm_hour;     /* hour [0, 23]. */
	int              tm_mday;     /* day of month [1, 31]. */
	int              tm_mon;      /* month of year [0, 11]. */
	int              tm_year;     /* years since 1900. */
	int              tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int              tm_yday;     /* day of year [0, 365]. */
	int              tm_isdst;    /* daylight savings flag. */
#if defined(__CRT_KOS) || defined(__CRT_GLC)
#ifdef __USE_MISC
	__LONGPTR_TYPE__ tm_gmtoff;   /* Seconds east of UTC. */
	char const      *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	__LONGPTR_TYPE__ __tm_gmtoff; /* Seconds east of UTC. */
	char const      *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_KOS || __CRT_GLC */
};
__NAMESPACE_STD_END
__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_TM_H */
