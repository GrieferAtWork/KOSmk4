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
#ifndef _LIBKEYMAP_API_H
#define _LIBKEYMAP_API_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBKEYMAP_CC __ATTR_FASTCALL
#else /* ... */
#define LIBKEYMAP_CC /* nothing */
#endif /* !... */

#if (!defined(LIBKEYMAP_WANT_PROTOTYPES) && \
     defined(__KOS__) && defined(__KERNEL__))
#define LIBKEYMAP_WANT_PROTOTYPES
#endif /* ... */

#if defined(__LIBKEYMAP_STATIC)
#define LIBKEYMAP_DECL __INTDEF
#else /* ... */
#define LIBKEYMAP_DECL __IMPDEF
#endif /* !... */

/* Library name for use with `dlopen(3D)' */
#define LIBKEYMAP_LIBRARY_NAME "libkeymap.so"

#endif /* !_LIBKEYMAP_API_H */
