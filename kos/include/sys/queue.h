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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/queue.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/queue.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/queue.h) */
/* (#) Portability: FreeBSD       (/sys/sys/queue.h) */
/* (#) Portability: GNU C Library (/misc/sys/queue.h) */
/* (#) Portability: NetBSD        (/sys/sys/queue.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/queue.h) */
/* (#) Portability: OpenBSD       (/sys/sys/queue.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/queue.h) */
/* (#) Portability: libbsd        (/include/bsd/sys/queue.h) */
/* (#) Portability: libc4/5       (/include/sys/queue.h) */
/* (#) Portability: mintlib       (/include/sys/queue.h) */
/* (#) Portability: uClibc        (/include/sys/queue.h) */
#ifndef _SYS_QUEUE_H
#define _SYS_QUEUE_H 1

#include <__stdinc.h>

#ifdef __CC__
#ifndef __GUARD_HYBRID_SEQUENCE_LIST_H
#include <features.h>

#undef __HYBRID_LIST_RESTRICT_API
#if !defined(__USE_KOS) && !defined(__USE_KOS_KERNEL)
#define __HYBRID_LIST_RESTRICT_API
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */

#include <hybrid/sequence/list.h>

/* If API access was restricted, allow <hybrid/sequence/list.h> to be re-included
 * directly in  order  to  unlock  all  APIs  that  haven't  been  exposed,  yet. */
#ifdef __HYBRID_LIST_RESTRICT_API
#undef __GUARD_HYBRID_SEQUENCE_LIST_H
#undef __HYBRID_LIST_RESTRICT_API
#endif /* __HYBRID_LIST_RESTRICT_API */

#endif /* !__GUARD_HYBRID_SEQUENCE_LIST_H */
#endif /* __CC__ */

#endif /* !_SYS_QUEUE_H */
