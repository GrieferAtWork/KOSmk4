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
#ifndef _LIBJSON_API_H
#define _LIBJSON_API_H 1

#ifndef LIBJSON_NO_SYSTEM_INCLUDES
#include <__stdinc.h>
#include <hybrid/host.h>
#endif /* !LIBJSON_NO_SYSTEM_INCLUDES */

#ifndef LIBJSON_CC
#if defined(__i386__) && !defined(__x86_64__)
#define LIBJSON_CC __ATTR_STDCALL
#else /* ... */
#define LIBJSON_CC /* nothing */
#endif /* !... */
#endif /* !LIBJSON_CC */

#if (!defined(LIBJSON_WANT_PROTOTYPES) && \
     defined(__KOS__) && defined(__KERNEL__))
#define LIBJSON_WANT_PROTOTYPES
#endif /* ... */

#ifndef LIBJSON_DECL
#if (defined(__KOS__) && defined(__KERNEL__) && \
     defined(BUILDING_KERNEL_CORE))
#define LIBJSON_DECL __PUBDEF
#elif defined(__LIBJSON_STATIC)
#define LIBJSON_DECL __INTDEF
#else /* ... */
#define LIBJSON_DECL __IMPDEF
#endif /* !... */
#endif /* !LIBJSON_DECL */

/* Library name for use with `dlopen(3D)' */
#define LIBJSON_LIBRARY_NAME "libjson.so"

#endif /* !_LIBJSON_API_H */
