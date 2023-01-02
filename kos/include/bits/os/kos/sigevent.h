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
#ifndef _BITS_OS_KOS_SIGEVENT_H
#define _BITS_OS_KOS_SIGEVENT_H 1

/* File:
 *    <bits/os/kos/sigevent.h>
 *
 * Definitions:
 *    - struct sigevent { ... };
 *    - #define __SIGEV_MAX_SIZE ...
 *    - #define __SIGEV_PAD_SIZE ...
 */

#include <__stdinc.h>
#include <features.h> /* __USE_KOS_ALTERATIONS */

#include <hybrid/typecore.h>

#include <bits/os/sigval.h> /* union sigval */
#include <bits/types.h>

#define __SIGEV_MAX_SIZE    64
#if __SIZEOF_POINTER__ <= 4
#define __SIGEV_PAD_SIZE    ((__SIGEV_MAX_SIZE / 4) - 3)
#else /* __SIZEOF_POINTER__ <= 4 */
#define __SIGEV_PAD_SIZE    ((__SIGEV_MAX_SIZE / 4) - 4)
#endif /* __SIZEOF_POINTER__ > 4 */

#ifdef __CC__
__DECL_BEGIN

union __pthread_attr;
struct sigevent /*[PREFIX(sigev_)]*/ {
	union sigval   sigev_value;
	__INT32_TYPE__ sigev_signo;
	__INT32_TYPE__ sigev_notify; /* One of `SIGEV_*' */
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION))
#ifndef __USE_KOS_ALTERATIONS
	struct{
#endif /* !__USE_KOS_ALTERATIONS */
	union {
		__INT32_TYPE__ _pad[__SIGEV_PAD_SIZE];
		/* When SIGEV_SIGNAL and SIGEV_THREAD_ID set, LWP ID of the thread to receive the signal. */
		__pid_t _sigev_tid;
		struct {
			void (__LIBKCALL     *sigev_notify_function)(union sigval __val); /* Function to start. */
			union __pthread_attr *sigev_notify_attributes;                    /* Thread attributes. */
		};
	};
#ifndef __USE_KOS_ALTERATIONS
	union {
		__INT32_TYPE__ _pad[__SIGEV_PAD_SIZE];
		/* When SIGEV_SIGNAL and SIGEV_THREAD_ID set, LWP ID of the thread to receive the signal. */
		__pid_t _sigev_tid;
		struct {
			void (__LIBKCALL     *_function)(union sigval __val); /* Function to start. */
			union __pthread_attr *_attribute;                     /* Thread attributes. */
		} _sigev_thread;
	} _sigev_un;
	};
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __COMPILER_HAVE_TRANSPARENT_STRUCT && __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		__INT32_TYPE__ _pad[__SIGEV_PAD_SIZE];
		/* When SIGEV_SIGNAL and SIGEV_THREAD_ID set, LWP ID of the thread to receive the signal. */
		__pid_t _tid;
		struct {
			void (__ATTR_CDECL   *_function)(union sigval __val); /* Function to start. */
			union __pthread_attr *_attribute;                     /* Thread attributes. */
		} _sigev_thread;
	} _sigev_un;
#define _sigev_tid              _sigev_un._sigev_un
#define sigev_notify_function   _sigev_un._sigev_thread._function
#define sigev_notify_attributes _sigev_un._sigev_thread._attribute
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT || !__COMPILER_HAVE_TRANSPARENT_UNION */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_KOS_SIGEVENT_H */
