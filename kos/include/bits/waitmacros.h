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
#ifndef _BITS_WAITMACROS_H
#define _BITS_WAITMACROS_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <features.h>

#include <bits/waitflags.h>
#include <bits/waitstatus.h>

#ifndef __WAIT_MACROS_DEFINED
#define __WAIT_MACROS_DEFINED 1
#ifdef __USE_MISC
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

#endif /* !__WAIT_MACROS_DEFINED */
#endif /* __CC__ */


#endif /* !_BITS_WAITMACROS_H */
