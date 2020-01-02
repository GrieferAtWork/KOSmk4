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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BIT_SIGEVENT_H
#define _I386_KOS_BIT_SIGEVENT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __CRT_CYG_PRIMARY
#include "sigevent-cygwin.h"
#else /* __CRT_CYG_PRIMARY */

#include <hybrid/host.h>

#ifdef __x86_64__
#include "sigevent64.h"
#else /* __x86_64__ */
#include "sigevent32.h"
#endif /* !__x86_64__ */

__SYSDECL_BEGIN

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

#endif /* !__CRT_CYG_PRIMARY */

#endif /* !_I386_KOS_BIT_SIGEVENT_H */
