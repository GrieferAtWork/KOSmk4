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
#ifndef _PARTS_WAITMACROS_H
#define _PARTS_WAITMACROS_H 1

#include <__stdinc.h>
#include <features.h>

#include <asm/os/wait.h>

/* Bits in the third argument to `waitpid'. */
#ifdef __WNOHANG
#define WNOHANG __WNOHANG /* Don't block waiting. */
#endif /* __WNOHANG */
#ifdef __WUNTRACED
#define WUNTRACED __WUNTRACED /* Report status of stopped children. */
#endif /* __WUNTRACED */

/* Bits in the fourth argument to `waitid'. */
#ifdef __WSTOPPED
#define WSTOPPED __WSTOPPED /* Report stopped child (same as WUNTRACED). */
#endif /* __WSTOPPED */
#ifdef __WEXITED
#define WEXITED __WEXITED /* Report dead child. */
#endif /* __WEXITED */
#ifdef __WCONTINUED
#define WCONTINUED __WCONTINUED /* Report continued child. */
#endif /* __WCONTINUED */
#ifdef __WNOWAIT
#define WNOWAIT __WNOWAIT /* Don't reap, just poll status. */
#endif /* __WNOWAIT */
#ifdef __USE_KOS
#ifdef __WONLYTHREADS
#define WONLYTHREADS __WONLYTHREADS /* Only wait for children created within the current
                                     * process, and  with the  `CLONE_THREAD' flag  set. */
#endif /* __WONLYTHREADS */
#ifdef __WNOWAIT
#define WNOREAP __WNOWAIT /* Don't reap, just poll status (doesn't this name make more sense than `WNOWAIT'?). */
#endif /* __WNOWAIT */
#endif /* __USE_KOS */

#ifdef __USE_KOS_KERNEL
#ifdef __WNOTHREAD
#define WNOTHREAD __WNOTHREAD /* Don't wait on children of other threads in this group */
#endif /* __WNOTHREAD */
#ifdef __WALL
#define WALL __WALL /* Wait for any child. */
#endif /* __WALL */
#ifdef __WCLONE
#define WCLONE __WCLONE /* Wait for cloned process. */
#endif /* __WCLONE */
#endif /* __USE_KOS_KERNEL */

/* The following values are used by the `waitid' function. */
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#if defined(__P_ALL) || defined(__P_PID) || defined(__P_PGID)
/*[[[enum]]]*/
#ifdef __CC__
enum __idtype_enum {
#ifdef __P_ALL
	P_ALL  = __P_ALL, /* Wait for any child. */
#endif /* __P_ALL */
#ifdef __P_PID
	P_PID  = __P_PID, /* Wait for specified process. */
#endif /* __P_PID */
#ifdef __P_PGID
	P_PGID = __P_PGID  /* Wait for members of process group. */
#endif /* __P_PGID */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __P_ALL
#define P_ALL  P_ALL  /* Wait for any child. */
#endif /* __P_ALL */
#ifdef __P_PID
#define P_PID  P_PID  /* Wait for specified process. */
#endif /* __P_PID */
#ifdef __P_PGID
#define P_PGID P_PGID /* Wait for members of process group. */
#endif /* __P_PGID */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __P_ALL
#define P_ALL  __P_ALL  /* Wait for any child. */
#endif /* __P_ALL */
#ifdef __P_PID
#define P_PID  __P_PID  /* Wait for specified process. */
#endif /* __P_PID */
#ifdef __P_PGID
#define P_PGID __P_PGID /* Wait for members of process group. */
#endif /* __P_PGID */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#ifdef __CC__
#ifndef __idtype_t_defined
#define __idtype_t_defined
typedef enum __idtype_enum idtype_t;
#endif /* !__idtype_t_defined */
#endif /* __CC__ */
#else /* __P_ALL || __P_PID || __P_PGID */
#ifdef __CC__
#ifndef __idtype_t_defined
#define __idtype_t_defined
typedef int idtype_t;
#endif /* !__idtype_t_defined */
#endif /* __CC__ */
#endif /* !__P_ALL && !__P_PID && !__P_PGID */
#endif /* ... */


#ifdef __USE_MISC
#include <bits/os/wait.h> /* `union wait' */

#if defined(__GNUC__) && !defined(__cplusplus)
#define __WAIT_INT(status) \
	(__extension__(((union { __typeof__(status) __inval; int __ival; }) { .__inval = (status) }).__ival))
#else /* __GNUC__ && !__cplusplus */
#define __WAIT_INT(status) (*(int *)&(status))
#endif /* !__GNUC__ || __cplusplus */

#ifdef __NO_ATTR_TRANSPARENT_UNION
#define __WAIT_STATUS      void *
#define __WAIT_STATUS_DEFN void *
#else /* __NO_ATTR_TRANSPARENT_UNION */
typedef union {
	union wait *__uptr_;
	int        *__iptr_;
} __WAIT_STATUS __ATTR_TRANSPARENT_UNION;
#define __WAIT_STATUS_DEFN int *
#endif /* !__NO_ATTR_TRANSPARENT_UNION */

#else /* __USE_MISC */
#define __WAIT_INT(status) (status)
#define __WAIT_STATUS      int *
#define __WAIT_STATUS_DEFN int *
#endif /* !__USE_MISC */


#ifdef __WEXITSTATUS
#define WEXITSTATUS(status) __WEXITSTATUS(__WAIT_INT(status))
#endif /* __WEXITSTATUS */
#ifdef __WTERMSIG
#define WTERMSIG(status) __WTERMSIG(__WAIT_INT(status))
#endif /* __WTERMSIG */
#ifdef __WSTOPSIG
#define WSTOPSIG(status) __WSTOPSIG(__WAIT_INT(status))
#endif /* __WSTOPSIG */
#ifdef __WIFEXITED
#define WIFEXITED(status) __WIFEXITED(__WAIT_INT(status))
#endif /* __WIFEXITED */
#ifdef __WIFSIGNALED
#define WIFSIGNALED(status) __WIFSIGNALED(__WAIT_INT(status))
#endif /* __WIFSIGNALED */
#ifdef __WIFSTOPPED
#define WIFSTOPPED(status) __WIFSTOPPED(__WAIT_INT(status))
#endif /* __WIFSTOPPED */
#ifdef __WIFCONTINUED
#define WIFCONTINUED(status) __WIFCONTINUED(__WAIT_INT(status))
#endif /* __WIFCONTINUED */



#endif /* !_PARTS_WAITMACROS_H */
