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
#ifndef _BIT_SIGEVENT_H
#define _BIT_SIGEVENT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/sigval.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#define __SIGEV_MAX_SIZE    64
#if __SIZEOF_POINTER__ <= 4
#define __SIGEV_PAD_SIZE    ((__SIGEV_MAX_SIZE / 4) - 3)
#else /* __SIZEOF_POINTER__ <= 4 */
#define __SIGEV_PAD_SIZE    ((__SIGEV_MAX_SIZE / 4) - 4)
#endif /* __SIZEOF_POINTER__ > 4 */

#ifdef __CC__
#ifndef __pthread_attr_t_defined
#define __pthread_attr_t_defined 1
typedef union __pthread_attr pthread_attr_t;
#endif /* !__pthread_attr_t_defined */
#endif /* __CC__ */

#ifdef __CC__
typedef struct sigevent /*[PREFIX(sigev_)]*/ {
	sigval_t       sigev_value;
	__INT32_TYPE__ sigev_signo;
	__INT32_TYPE__ sigev_notify;
#if defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
    defined(__COMPILER_HAVE_TRANSPARENT_UNION)
#ifndef __USE_KOS
	struct{
#endif /* !__USE_KOS */
	union {
		__INT32_TYPE__ _pad[__SIGEV_PAD_SIZE];
		/* When SIGEV_SIGNAL and SIGEV_THREAD_ID set, LWP ID of the thread to receive the signal. */
		__pid_t _tid;
		struct {
			void (__LIBCCALL *sigev_notify_function)(sigval_t __val); /* Function to start. */
			pthread_attr_t   *sigev_notify_attributes;                /* Thread attributes. */
		};
	};
#ifndef __USE_KOS
	union {
		__INT32_TYPE__ _pad[__SIGEV_PAD_SIZE];
		/* When SIGEV_SIGNAL and SIGEV_THREAD_ID set, LWP ID of the thread to receive the signal. */
		__pid_t _tid;
		struct {
			void (__LIBCCALL *_function)(sigval_t __val); /* Function to start. */
			pthread_attr_t   *_attribute;                 /* Thread attributes. */
		} _sigev_thread;
	} _sigev_un;
	};
#endif /* !__USE_KOS */
#else /* __COMPILER_HAVE_TRANSPARENT_STRUCT && __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		__INT32_TYPE__ _pad[__SIGEV_PAD_SIZE];
		/* When SIGEV_SIGNAL and SIGEV_THREAD_ID set, LWP ID of the thread to receive the signal. */
		__pid_t _tid;
		struct {
			void (__ATTR_CDECL *_function)(sigval_t __val); /* Function to start. */
			pthread_attr_t *_attribute;                     /* Thread attributes. */
		} _sigev_thread;
	} _sigev_un;
#define sigev_notify_function   _sigev_un._sigev_thread._function
#define sigev_notify_attributes _sigev_un._sigev_thread._attribute
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT || !__COMPILER_HAVE_TRANSPARENT_UNION */
} sigevent_t;
#endif /* __CC__ */

/* `sigev_notify' values. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	SIGEV_SIGNAL    = 0, /* Notify via signal. */
	SIGEV_NONE      = 1, /* Other notification: meaningless. */
	SIGEV_THREAD    = 2, /* Deliver via thread creation. */
	SIGEV_THREAD_ID = 4  /* Send signal to specific thread. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define SIGEV_SIGNAL    SIGEV_SIGNAL    /* Notify via signal. */
#define SIGEV_NONE      SIGEV_NONE      /* Other notification: meaningless. */
#define SIGEV_THREAD    SIGEV_THREAD    /* Deliver via thread creation. */
#define SIGEV_THREAD_ID SIGEV_THREAD_ID /* Send signal to specific thread. */
#else /* __COMPILER_PREFERR_ENUMS */
#define SIGEV_SIGNAL    0 /* Notify via signal. */
#define SIGEV_NONE      1 /* Other notification: meaningless. */
#define SIGEV_THREAD    2 /* Deliver via thread creation. */
#define SIGEV_THREAD_ID 4 /* Send signal to specific thread. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

__SYSDECL_END

#endif /* !_BIT_SIGEVENT_H */
