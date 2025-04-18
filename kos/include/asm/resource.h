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
/* (#) Portability: Linux (/usr/include/[...]/asm/resource.h) */
/*!always_includes <asm/os/resource.h>*/
#ifndef _ASM_RESOURCE_H
#define _ASM_RESOURCE_H 1

#include <asm/os/resource.h>

#if !defined(RLIMIT_CPU) && defined(__RLIMIT_CPU)
#define RLIMIT_CPU __RLIMIT_CPU /* ??? */
#endif /* !RLIMIT_CPU && __RLIMIT_CPU */
#if !defined(RLIMIT_FSIZE) && defined(__RLIMIT_FSIZE)
#define RLIMIT_FSIZE __RLIMIT_FSIZE /* ??? */
#endif /* !RLIMIT_FSIZE && __RLIMIT_FSIZE */
#if !defined(RLIMIT_DATA) && defined(__RLIMIT_DATA)
#define RLIMIT_DATA __RLIMIT_DATA /* ??? */
#endif /* !RLIMIT_DATA && __RLIMIT_DATA */
#if !defined(RLIMIT_STACK) && defined(__RLIMIT_STACK)
#define RLIMIT_STACK __RLIMIT_STACK /* ??? */
#endif /* !RLIMIT_STACK && __RLIMIT_STACK */
#if !defined(RLIMIT_CORE) && defined(__RLIMIT_CORE)
#define RLIMIT_CORE __RLIMIT_CORE /* ??? */
#endif /* !RLIMIT_CORE && __RLIMIT_CORE */
#if !defined(RLIMIT_RSS) && defined(__RLIMIT_RSS)
#define RLIMIT_RSS __RLIMIT_RSS /* ??? */
#endif /* !RLIMIT_RSS && __RLIMIT_RSS */
#if !defined(RLIMIT_NPROC) && defined(__RLIMIT_NPROC)
#define RLIMIT_NPROC __RLIMIT_NPROC /* ??? */
#endif /* !RLIMIT_NPROC && __RLIMIT_NPROC */
#if !defined(RLIMIT_NOFILE) && defined(__RLIMIT_NOFILE)
#define RLIMIT_NOFILE __RLIMIT_NOFILE /* Max # of open file descriptors (total; does not affect greatest usable FD number) */
#endif /* !RLIMIT_NOFILE && __RLIMIT_NOFILE */
#if !defined(RLIMIT_MEMLOCK) && defined(__RLIMIT_MEMLOCK)
#define RLIMIT_MEMLOCK __RLIMIT_MEMLOCK /* ??? */
#endif /* !RLIMIT_MEMLOCK && __RLIMIT_MEMLOCK */
#if !defined(RLIMIT_AS) && defined(__RLIMIT_AS)
#define RLIMIT_AS __RLIMIT_AS /* ??? */
#endif /* !RLIMIT_AS && __RLIMIT_AS */
#if !defined(RLIMIT_LOCKS) && defined(__RLIMIT_LOCKS)
#define RLIMIT_LOCKS __RLIMIT_LOCKS /* ??? */
#endif /* !RLIMIT_LOCKS && __RLIMIT_LOCKS */
#if !defined(RLIMIT_SIGPENDING) && defined(__RLIMIT_SIGPENDING)
#define RLIMIT_SIGPENDING __RLIMIT_SIGPENDING /* ??? */
#endif /* !RLIMIT_SIGPENDING && __RLIMIT_SIGPENDING */
#if !defined(RLIMIT_MSGQUEUE) && defined(__RLIMIT_MSGQUEUE)
#define RLIMIT_MSGQUEUE __RLIMIT_MSGQUEUE /* ??? */
#endif /* !RLIMIT_MSGQUEUE && __RLIMIT_MSGQUEUE */
#if !defined(RLIMIT_NICE) && defined(__RLIMIT_NICE)
#define RLIMIT_NICE __RLIMIT_NICE /* ??? */
#endif /* !RLIMIT_NICE && __RLIMIT_NICE */
#if !defined(RLIMIT_RTPRIO) && defined(__RLIMIT_RTPRIO)
#define RLIMIT_RTPRIO __RLIMIT_RTPRIO /* ??? */
#endif /* !RLIMIT_RTPRIO && __RLIMIT_RTPRIO */
#if !defined(RLIMIT_RTTIME) && defined(__RLIMIT_RTTIME)
#define RLIMIT_RTTIME __RLIMIT_RTTIME /* ??? */
#endif /* !RLIMIT_RTTIME && __RLIMIT_RTTIME */
#if !defined(RLIM_NLIMITS) && defined(__RLIMIT_NLIMITS)
#define RLIM_NLIMITS __RLIMIT_NLIMITS /* Total # of (standard) resource limits */
#endif /* !RLIM_NLIMITS && __RLIMIT_NLIMITS */

#if !defined(RLIM_INFINITY) && defined(__RLIM_INFINITY)
#define RLIM_INFINITY __RLIM_INFINITY /* Unlimited */
#endif /* !RLIM_INFINITY && __RLIM_INFINITY */

#endif /* !_ASM_RESOURCE_H */
