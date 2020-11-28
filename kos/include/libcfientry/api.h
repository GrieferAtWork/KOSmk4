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
#ifndef _LIBCFIENTRY_API_H
#define _LIBCFIENTRY_API_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBCFIENTRY_CC __ATTR_STDCALL
#else /* ... */
#define LIBCFIENTRY_CC /* nothing */
#endif /* !... */

/* Feature test macro: `LIBUNWIND_CC' and `LIBCFIENTRY_CC' are the same. */
#define LIBCFIENTRY_CC_IS_LIBUNWIND_CC 1

#if 0
#define LIBCFIENTRY_WANT_PROTOTYPES 1
#endif

#ifdef __LIBCFIENTRY_STATIC
#define LIBCFIENTRY_DECL __INTDEF
#else /* __LIBCFIENTRY_STATIC */
#define LIBCFIENTRY_DECL __IMPDEF
#endif /* !__LIBCFIENTRY_STATIC */

/* Library name for use with `dlopen()' */
#define LIBCFIENTRY_LIBRARY_NAME "libcfientry.so"

#endif /* !_LIBCFIENTRY_API_H */
