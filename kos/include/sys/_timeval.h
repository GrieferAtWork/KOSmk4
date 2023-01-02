/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/_timeval.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/_timeval.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/_timeval.h) */
/* (#) Portability: FreeBSD       (/sys/sys/_timeval.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/_timeval.h) */
#ifndef _SYS__TIMEVAL_H
#define _SYS__TIMEVAL_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/os/timeval.h>
#include <bits/types.h>
#include <sys/_types.h>

#ifdef __CC__
__DECL_BEGIN

#define	_TIME_T_DECLARED
#define _SUSECONDS_T_DECLARED
#define _TIMEVAL_DEFINED

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
#endif /* !__time_t_defined */

#ifndef __suseconds_t_defined
#define __suseconds_t_defined
typedef __suseconds_t suseconds_t;
#endif /* !__suseconds_t_defined */

__DECL_END
#endif /* __CC__ */

#ifdef __USE_BSD
/* Only need:
 *  - timerclear
 *  - timerisset
 *  - timercmp
 *  - timeradd
 *  - timersub */
#include <sys/time.h>
#endif /* __USE_BSD */

#endif /* !_SYS__TIMEVAL_H */
