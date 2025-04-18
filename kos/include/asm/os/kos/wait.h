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
/*!replace_with_include <asm/os/wait.h>*/
#ifndef _ASM_OS_KOS_WAIT_H
#define _ASM_OS_KOS_WAIT_H 1

#include <__stdinc.h>

/* Bits in the third argument to `waitpid'. */
#define __WNOHANG      0x00000001 /* Don't block waiting. */
#define __WUNTRACED    0x00000002 /* Report status of stopped children. */

/* Bits in the fourth argument to `waitid'. */
#define __WSTOPPED     0x00000002 /* Report stopped child (same as WUNTRACED). */
#define __WEXITED      0x00000004 /* Report dead child. */
#define __WCONTINUED   0x00000008 /* Report continued child. */
#if defined(__KOS__) && __KOS_VERSION__ >= 300 && __KOS_VERSION__ < 400
#define __WONLYTHREADS 0x00008000 /* Only wait for children created within the current
                                   * process, and  with the  `CLONE_THREAD' flag  set. */
#endif /* __KOS__ && __KOS_VERSION__ >= 300 && __KOS_VERSION__ < 400 */
#define __WNOWAIT      0x01000000 /* Don't reap, just poll status. */
#define __WNOTHREAD    0x20000000 /* Don't wait on children of other threads in this group */
#define __WALL         0x40000000 /* Wait for any child. */
#define __WCLONE       0x80000000 /* Wait for cloned process. */

/* The following values are used by the `waitid' function. */
#define __P_ALL  0 /* Wait for any child. */
#define __P_PID  1 /* Wait for specified process. */
#define __P_PGID 2 /* Wait for members of process group. */


#define __WAIT_ANY    (-1) /* Any process. */
#define __WAIT_MYPGRP 0    /* Any process in my process group. */

/* Macros for constructing wait status values. */
#define __W_EXITCODE(ret, sig) ((ret) << 8 | (sig))
#define __W_STOPCODE(sig)      ((sig) << 8 | 0x7f)
#define __W_CONTINUED          0xffff
#define __WCOREFLAG            0x80

#define __WEXITSTATUS(status)  (((status)&0xff00) >> 8)                               /* If WIFEXITED(STATUS), the low-order 8 bits of the status. */
#define __WTERMSIG(status)     ((status)&0x7f)                                        /* If WIFSIGNALED(STATUS), the terminating signal. */
#define __WSTOPSIG(status)     __WEXITSTATUS(status)                                  /* If WIFSTOPPED(STATUS), the signal that stopped the child. */
#define __WIFEXITED(status)    (__WTERMSIG(status) == 0)                              /* Nonzero if STATUS indicates normal termination. */
#define __WIFSIGNALED(status)  ((__CCAST(signed char)(((status)&0x7f) + 1) >> 1) > 0) /* Nonzero if STATUS indicates termination by a signal. */
#define __WIFSTOPPED(status)   (((status)&0xff) == 0x7f)                              /* Nonzero if STATUS indicates the child is stopped. */
#define __WCOREDUMP(status)    ((status)&__WCOREFLAG)                                 /* Nonzero if STATUS indicates the child dumped core. */
#define __WIFCONTINUED(status) ((status) == __W_CONTINUED)                            /* Nonzero if STATUS indicates the child continued after a stop. */

#endif /* !_ASM_OS_KOS_WAIT_H */
