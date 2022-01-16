/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBSERVICE_API_H
#define _LIBSERVICE_API_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

/* This  is also the calling convention of
 * functions produced by `service_dlsym()' */
#ifdef __x86_64__
#define LIBSERVICE_CC __ATTR_SYSVABI
#elif defined(__i386__)
#define LIBSERVICE_CC __ATTR_CDECL
#else /* ... */
#define LIBSERVICE_CC /* nothing */
#endif /* !... */

#if 0
#define LIBSERVICE_WANT_PROTOTYPES
#endif

#ifdef __LIBSERVICE_STATIC
#define LIBSERVICE_DECL __INTDEF
#else /* __LIBSERVICE_STATIC */
#define LIBSERVICE_DECL __IMPDEF
#endif /* !__LIBSERVICE_STATIC */

/* Library name for use with `dlopen()' */
#define LIBSERVICE_LIBRARY_NAME "libservice.so"

#endif /* !_LIBSERVICE_API_H */
