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
#ifndef _ASM_OS_KOS_LIMITS_H
#define _ASM_OS_KOS_LIMITS_H 1

/* System configuration parameters and limits */

#include <__stdinc.h>

#ifdef __KOS__
/************************************************************************/
/* KOS                                                                  */
/************************************************************************/

/*efine __HZ                 N/A         * Scheduler frequency (N/A because KOS's scheduler is TSC-based,
                                         * so HZ (and a resulting quantum length) can be anything) */
#define __HOST_NAME_MAX      64         /* Max # of characters in a hostname (s.a. `sethostname(2)'). */
#define __NGROUPS_MAX        (-1)       /* Max # of supplemental group IDs that may be set (s.a. `setgroups(2)') */
#define __OPEN_MAX           (-1)       /* Max # of open files handles */
#define __ARG_MAX            131072     /* Max # bytes of args + environ for exec(); */
#define __LINK_MAX           (-1)       /* Max # links a file may have (fs-dependent) */
#define __MAX_CANON          (-1)       /* Max size of the canonical input queue */
#define __MAX_INPUT          (-1)       /* Max size of the type-ahead buffer */
#define __NAME_MAX           65535      /* Max # chars in a file name */
#define __PATH_MAX           (-1)       /* Max # chars in a path name including nul */
#define __PIPE_BUF           4096       /* Max # bytes in atomic write to a pipe (Default value, assuming that backing memory isn't VIO or re-mapped during a write) */
#define __XATTR_NAME_MAX     255        /* Max # chars in an extended attribute name */
#define __XATTR_SIZE_MAX     65536      /* Max size of an extended attribute value (64k) */
#define __XATTR_LIST_MAX     65536      /* Max size of extended attribute namelist (64k) */
#define __RTSIG_MAX          32         /* # of realtime signals */
#define __SYMLOOP_MAX        (-1)       /* Max # of symbolic links to follow before `ELOOP' */
#define __AIO_PRIO_DELTA_MAX 20         /* Maximum amount by which a process can decrease its asynchronous I/O priority level. */
#define __DELAYTIMER_MAX     2147483647 /* Maximum # of timer expiration overruns. */
#define __TTY_NAME_MAX       32         /* Maximum tty name length. */
#define __MQ_PRIO_MAX        32768      /* Maximum message queue priority level. */
#define __IOV_MAX            (-1)       /* Max # of elements in a `struct iovec' vector. */
#define __NZERO              20         /* Default process priority. */

#elif defined(__linux__)
/************************************************************************/
/* LINUX                                                                */
/************************************************************************/

#define __HZ                 100        /* Scheduler frequency */
#define __HOST_NAME_MAX      64         /* Max # of characters in a hostname (s.a. `sethostname(2)'). */
#define __NGROUPS_MAX        65536      /* Max # of supplemental group IDs that may be set (s.a. `setgroups(2)') */
#define __OPEN_MAX           1024       /* Max # of open files handles */
#define __ARG_MAX            131072     /* Max # bytes of args + environ for exec(); */
#define __LINK_MAX           127        /* Max # links a file may have */
#define __MAX_CANON          255        /* Max size of the canonical input queue */
#define __MAX_INPUT          255        /* Max size of the type-ahead buffer */
#define __NAME_MAX           255        /* Max # chars in a file name */
#define __PATH_MAX           4096       /* Max # chars in a path name including nul */
#define __PIPE_BUF           4096       /* Max # bytes in atomic write to a pipe (Default value) */
#define __XATTR_NAME_MAX     255        /* Max # chars in an extended attribute name */
#define __XATTR_SIZE_MAX     65536      /* Max size of an extended attribute value (64k) */
#define __XATTR_LIST_MAX     65536      /* Max size of extended attribute namelist (64k) */
#define __RTSIG_MAX          32         /* # of realtime signals */
#define __SYMLOOP_MAX        20         /* Max # of symbolic links to follow before `ELOOP' */
#define __AIO_PRIO_DELTA_MAX 20         /* Maximum amount by which a process can decrease its asynchronous I/O priority level. */
#define __DELAYTIMER_MAX     2147483647 /* Maximum # of timer expiration overruns. */
#define __TTY_NAME_MAX       32         /* Maximum tty name length. */
#define __MQ_PRIO_MAX        32768      /* Maximum message queue priority level. */
#define __IOV_MAX            1024       /* Max # of elements in a `struct iovec' vector. */
#define __NZERO              20         /* Default process priority. */

#endif /* ... */

#endif /* !_ASM_OS_KOS_LIMITS_H */
