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
#ifndef _SYS_SCHED_H
#define _SYS_SCHED_H 1

/* API_LEVEL: newlib */

#include <__stdinc.h>

#include <asm/sched.h>
#include <bits/sched_param.h>
#include <sys/_timespec.h>

#ifdef __SCHED_OTHER
#define SCHED_OTHER __SCHED_OTHER /* ... */
#endif /* __SCHED_OTHER */
#ifdef __SCHED_FIFO
#define SCHED_FIFO __SCHED_FIFO /* ... */
#endif /* __SCHED_FIFO */
#ifdef __SCHED_RR
#define SCHED_RR __SCHED_RR /* ... */
#endif /* __SCHED_RR */
#ifdef __SCHED_SPORADIC
#define SCHED_SPORADIC __SCHED_SPORADIC /* ... */
#endif /* __SCHED_SPORADIC */

#endif /* !_SYS_SCHED_H */
