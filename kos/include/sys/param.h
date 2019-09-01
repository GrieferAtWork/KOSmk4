/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H 1

#include <__stdinc.h>
#include <bits/param.h>
#include <endian.h>
#include <limits.h>
#include <signal.h>
#include <sys/types.h>
#include <hybrid/minmax.h>

__SYSDECL_BEGIN

#ifndef NULL
#define NULL __NULLPTR
#endif

#define NBBY              CHAR_BIT
#if !defined(NGROUPS) && defined(NGROUPS_MAX)
#   define NGROUPS        NGROUPS_MAX
#endif
#if !defined(MAXSYMLINKS) && defined(SYMLOOP_MAX)
#   define MAXSYMLINKS    SYMLOOP_MAX
#endif
#if !defined(CANBSIZ) && defined(MAX_CANON)
#   define CANBSIZ        MAX_CANON
#endif
#if !defined(MAXPATHLEN) && defined(PATH_MAX)
#   define MAXPATHLEN     PATH_MAX
#endif
#if !defined(NOFILE) && defined(OPEN_MAX)
#   define NOFILE         OPEN_MAX
#endif
#if !defined(MAXHOSTNAMELEN) && defined(HOST_NAME_MAX)
#   define MAXHOSTNAMELEN HOST_NAME_MAX
#endif
#ifndef NCARGS
#ifdef ARG_MAX
#   define NCARGS         ARG_MAX
#else
#   define NCARGS         INT_MAX
#endif
#endif
#ifndef NOGROUP
#   define NOGROUP    65535
#endif
#ifndef NODEV
#   define NODEV     ((dev_t)-1)
#endif
#ifndef DEV_BSIZE
#   define DEV_BSIZE   512
#endif

#ifndef setbit
#define setbit(a,i)     ((a)[(i)/NBBY]|=1<<((i)%NBBY))
#endif /* !setbit */
#ifndef clrbit
#define clrbit(a,i)     ((a)[(i)/NBBY]&=~(1<<((i)%NBBY)))
#endif /* !clrbit */
#ifndef isset
#define isset(a,i)      ((a)[(i)/NBBY]&(1<<((i)%NBBY)))
#endif /* !isset */
#ifndef isclr
#define isclr(a,i)    (!((a)[(i)/NBBY]&(1<<((i)%NBBY))))
#endif /* !isclr */
#ifndef howmany
#define howmany(x,y)  (((x)+((y)-1))/(y))
#endif /* !howmany */
#ifndef powerof2
#define powerof2(x)      (!(((x)-1)&(x)))
#endif /* !powerof2 */
#ifndef roundup
#ifndef __NO_builtin_constant_p
#   define roundup(x,y)  (__builtin_constant_p(y) && powerof2(y) ? \
                         (((x)+(y)-1)&~((y)-1)) : ((((x)+((y)-1))/(y))*(y)))
#else /* !__NO_builtin_constant_p */
#   define roundup(x,y)  ((((x)+((y)-1))/(y))*(y))
#endif /* __NO_builtin_constant_p */
#endif /* !roundup */

__SYSDECL_END

#endif /* !_SYS_PARAM_H */
