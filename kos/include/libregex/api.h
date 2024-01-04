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
#ifndef _LIBREGEX_API_H
#define _LIBREGEX_API_H 1

#ifndef LIBREGEX_NO_SYSTEM_INCLUDES
#include <__stdinc.h>
#include <hybrid/host.h>
#endif /* !LIBREGEX_NO_SYSTEM_INCLUDES */

#ifndef LIBREGEX_CC
#if defined(__i386__) && !defined(__x86_64__)
#define LIBREGEX_CC __ATTR_FASTCALL
#else /* ... */
#define LIBREGEX_CC /* nothing */
#endif /* !... */
#endif /* !LIBREGEX_CC */

#if 0
#define LIBREGEX_WANT_PROTOTYPES
#endif

#ifndef LIBREGEX_DECL
#ifdef __LIBREGEX_STATIC
#define LIBREGEX_DECL __INTDEF
#else /* ... */
#define LIBREGEX_DECL __IMPDEF
#endif /* !... */
#endif /* !LIBREGEX_DECL */

/* Library name for use with `dlopen(3D)' */
#define LIBREGEX_LIBRARY_NAME "libregex.so"

#endif /* !_LIBREGEX_API_H */
