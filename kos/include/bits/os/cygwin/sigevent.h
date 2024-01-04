/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_CYGWIN_SIGEVENT_H
#define _BITS_OS_CYGWIN_SIGEVENT_H 1

/* File:
 *    <bits/os/cygwin/sigevent.h>
 *
 * Definitions:
 *    - struct __sigevent_cygwin { ... };
 * #ifdef __CRT_CYG_PRIMARY
 *    - struct sigevent { ... };
 * #endif
 */

#include <__crt.h> /* __CRT_CYG_PRIMARY */
#include <__stdinc.h>

#include <hybrid/typecore.h> /* __INT32_TYPE__ */

#include <bits/os/sigval.h> /* union sigval */

#ifdef __CRT_CYG_PRIMARY
#define __sigevent_cygwin                   sigevent
#define __OFFSET_SIGEVENT_VALUE             __OFFSET_SIGEVENT_CYGWIN_VALUE
#define __OFFSET_SIGEVENT_SIGNO             __OFFSET_SIGEVENT_CYGWIN_SIGNO
#define __OFFSET_SIGEVENT_NOTIFY            __OFFSET_SIGEVENT_CYGWIN_NOTIFY
#define __OFFSET_SIGEVENT_NOTIFY_FUNCTION   __OFFSET_SIGEVENT_CYGWIN_NOTIFY_FUNCTION
#define __OFFSET_SIGEVENT_NOTIFY_ATTRIBUTES __OFFSET_SIGEVENT_CYGWIN_NOTIFY_ATTRIBUTES
#define __SIZEOF_SIGEVENT                   __SIZEOF_SIGEVENT_CYGWIN
#endif /* __CRT_CYG_PRIMARY */

#define __OFFSET_SIGEVENT_CYGWIN_VALUE              0
#define __OFFSET_SIGEVENT_CYGWIN_SIGNO              __SIZEOF_POINTER__
#define __OFFSET_SIGEVENT_CYGWIN_NOTIFY            (__SIZEOF_POINTER__+4)
#define __OFFSET_SIGEVENT_CYGWIN_NOTIFY_FUNCTION   (__SIZEOF_POINTER__+8)
#define __OFFSET_SIGEVENT_CYGWIN_NOTIFY_ATTRIBUTES (__SIZEOF_POINTER__*2+8)
#define __SIZEOF_SIGEVENT_CYGWIN                   (__SIZEOF_POINTER__*3+8)
#ifdef __CC__
__DECL_BEGIN

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
union __pthread_attr;
struct __sigevent_cygwin /*[NAME(sigevent_cygwin)][PREFIX(sigev_)]*/ {
	union sigval          sigev_value;
	__INT32_TYPE__        sigev_signo;
	__INT32_TYPE__        sigev_notify; /* One of `SIGEV_*' */
	void                (*sigev_notify_function)(union sigval);
	union __pthread_attr *sigev_notify_attributes;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("sigev_notify_attributes")
#pragma pop_macro("sigev_notify_function")
#pragma pop_macro("sigev_notify")
#pragma pop_macro("sigev_signo")
#pragma pop_macro("sigev_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_CYGWIN_SIGEVENT_H */
