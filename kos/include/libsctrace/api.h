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
#ifndef _LIBSCTRACE_API_H
#define _LIBSCTRACE_API_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

/************************************************************************|
|* libsctrace: LibSysCallTrace                                          *|
|*     This is the library that provides capabilities for tracing       *|
|*     system call invocations within the KOS kernel, as well as        *|
|*     user-space                                                       *|
|* NOTE: This library exists as a dynamicaly loadable kernel driver     *|
|*       by the name of `modsctrace', which can also be used to         *|
|*       install a syslog sink for logging every invocation of any      *|
|*       system call (which can also be controlled using the builtin    *|
|*       debugger command `sctrace 0|1')                                *|
|************************************************************************/


#if defined(__i386__) && !defined(__x86_64__)
#define LIBSCTRACE_CC __ATTR_STDCALL
#else /* ... */
#define LIBSCTRACE_CC /* nothing */
#endif /* !... */

#if (!defined(LIBSCTRACE_WANT_PROTOTYPES) && \
     defined(__KOS__) && defined(__KERNEL__))
#define LIBSCTRACE_WANT_PROTOTYPES
#endif /* ... */

#if defined(__KOS__) && defined(__KERNEL__)
#define LIBSCTRACE_DECL __PUBDEF
#elif defined(__LIBSCTRACE_STATIC)
#define LIBSCTRACE_DECL __INTDEF
#else /* ... */
#define LIBSCTRACE_DECL __IMPDEF
#endif /* !... */

/* Library name for use with `dlopen(3D)' */
#define LIBSCTRACE_LIBRARY_NAME "libsctrace.so"

#endif /* !_LIBSCTRACE_API_H */
