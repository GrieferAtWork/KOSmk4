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
#ifndef _I386_KOS_BIT_SIGEVENT_CYGWIN_H
#define _I386_KOS_BIT_SIGEVENT_CYGWIN_H 1

#include <__crt.h> /* __CRT_CYG_PRIMARY */
#include <__stdinc.h>

#include <hybrid/typecore.h> /* __INT32_TYPE__ */

#include <bits/sigval.h> /* sigval_t */

__SYSDECL_BEGIN

#ifdef __CRT_CYG_PRIMARY
#define sigevent_cygwin   sigevent
#define sigevent_cygwin_t sigevent_t
#define __OFFSET_SIGEVENT_VALUE             __OFFSET_SIGEVENT_CYGWIN_VALUE
#define __OFFSET_SIGEVENT_SIGNO             __OFFSET_SIGEVENT_CYGWIN_SIGNO
#define __OFFSET_SIGEVENT_NOTIFY            __OFFSET_SIGEVENT_CYGWIN_NOTIFY
#define __OFFSET_SIGEVENT_NOTIFY_FUNCTION   __OFFSET_SIGEVENT_CYGWIN_NOTIFY_FUNCTION
#define __OFFSET_SIGEVENT_NOTIFY_ATTRIBUTES __OFFSET_SIGEVENT_CYGWIN_NOTIFY_ATTRIBUTES
#define __SIZEOF_SIGEVENT                   __SIZEOF_SIGEVENT_CYGWIN
#define SIGEV_SIGNAL      SIGEV_CYGWIN_SIGNAL
#define SIGEV_NONE        SIGEV_CYGWIN_NONE  
#define SIGEV_THREAD      SIGEV_CYGWIN_THREAD
#endif /* __CRT_CYG_PRIMARY */

#ifdef __CC__
#ifndef __pthread_attr_t_defined
#define __pthread_attr_t_defined 1
typedef union pthread_attr_t pthread_attr_t;
#endif /* !__pthread_attr_t_defined */
#endif /* __CC__ */


#define __OFFSET_SIGEVENT_CYGWIN_VALUE              0
#define __OFFSET_SIGEVENT_CYGWIN_SIGNO              __SIZEOF_POINTER__
#define __OFFSET_SIGEVENT_CYGWIN_NOTIFY            (__SIZEOF_POINTER__+4)
#define __OFFSET_SIGEVENT_CYGWIN_NOTIFY_FUNCTION   (__SIZEOF_POINTER__+8)
#define __OFFSET_SIGEVENT_CYGWIN_NOTIFY_ATTRIBUTES (__SIZEOF_POINTER__*2+8)
#define __SIZEOF_SIGEVENT_CYGWIN                   (__SIZEOF_POINTER__*3+8)
#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("sigev_value")
#pragma push_macro("sigev_signo")
#pragma push_macro("sigev_notify")
#pragma push_macro("sigev_notify_function")
#pragma push_macro("sigev_notify_attributes")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef sigev_value
#undef sigev_signo
#undef sigev_notify
#undef sigev_notify_function
#undef sigev_notify_attributes
typedef struct sigevent_cygwin /*[PREFIX(sigev_)]*/ {
	sigval_t        sigev_value;
	__INT32_TYPE__  sigev_signo;
	__INT32_TYPE__  sigev_notify;
	void          (*sigev_notify_function)(sigval_t);
	pthread_attr_t *sigev_notify_attributes;
} sigevent_cygwin_t;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("sigev_notify_attributes")
#pragma pop_macro("sigev_notify_function")
#pragma pop_macro("sigev_notify")
#pragma pop_macro("sigev_signo")
#pragma pop_macro("sigev_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

/* `sigev_notify' values. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	SIGEV_CYGWIN_SIGNAL    = 0, /* Notify via signal. */
	SIGEV_CYGWIN_NONE      = 1, /* Other notification: meaningless. */
	SIGEV_CYGWIN_THREAD    = 2, /* Deliver via thread creation. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define SIGEV_CYGWIN_SIGNAL SIGEV_CYGWIN_SIGNAL /* Notify via signal. */
#define SIGEV_CYGWIN_NONE   SIGEV_CYGWIN_NONE   /* Other notification: meaningless. */
#define SIGEV_CYGWIN_THREAD SIGEV_CYGWIN_THREAD /* Deliver via thread creation. */
#else /* __COMPILER_PREFERR_ENUMS */
#define SIGEV_CYGWIN_SIGNAL 0 /* Notify via signal. */
#define SIGEV_CYGWIN_NONE   1 /* Other notification: meaningless. */
#define SIGEV_CYGWIN_THREAD 2 /* Deliver via thread creation. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

__SYSDECL_END

#endif /* !_I386_KOS_BIT_SIGEVENT_CYGWIN_H */
