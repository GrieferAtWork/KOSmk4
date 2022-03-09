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
#ifndef _ASM_OS_KOS_RESOURCE_H
#define _ASM_OS_KOS_RESOURCE_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __RLIMIT_CPU        0  /* ??? */
#define __RLIMIT_FSIZE      1  /* ??? */
#define __RLIMIT_DATA       2  /* ??? */
#define __RLIMIT_STACK      3  /* ??? */
#define __RLIMIT_CORE       4  /* ??? */
#define __RLIMIT_RSS        5  /* ??? */
#define __RLIMIT_NPROC      6  /* ??? */
#define __RLIMIT_NOFILE     7  /* Max # of open file descriptors (total; does not affect greatest usable FD number) */
#define __RLIMIT_MEMLOCK    8  /* ??? */
#define __RLIMIT_AS         9  /* ??? */
#define __RLIMIT_LOCKS      10 /* ??? */
#define __RLIMIT_SIGPENDING 11 /* ??? */
#define __RLIMIT_MSGQUEUE   12 /* ??? */
#define __RLIMIT_NICE       13 /* ??? */
#define __RLIMIT_RTPRIO     14 /* ??? */
#define __RLIMIT_RTTIME     15 /* ??? */
#define __RLIMIT_NLIMITS    16 /* Total # of (standard) resource limits */

#ifdef __KOS__
#define __RLIMIT_MAXFILE 1024 /* greatest usable FD number */
#endif /* __KOS__ */

/* ??? */
#define __PRIO_PROCESS 0 /* ??? */
#define __PRIO_PGRP    1 /* ??? */
#define __PRIO_USER    2 /* ??? */

/* ??? */
#define __RUSAGE_SELF     0    /* ??? */
#define __RUSAGE_CHILDREN (-1) /* ??? */
#define __RUSAGE_THREAD   1    /* ??? */

/* Min/max thread/process priority */
#define __PRIO_MIN (-20) /* Minimum priority */
#define __PRIO_MAX 20    /* Maximum priority */

#endif /* !_ASM_OS_KOS_RESOURCE_H */
