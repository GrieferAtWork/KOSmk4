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
#ifndef _LIBDEBUGINFO_API_H
#define _LIBDEBUGINFO_API_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBDEBUGINFO_CC __ATTR_STDCALL
#else /* ... */
#define LIBDEBUGINFO_CC /* nothing */
#endif /* !... */

/* Feature test macro: `LIBUNWIND_CC' and `LIBDEBUGINFO_CC' are the same. */
#define LIBDEBUGINFO_CC_IS_LIBUNWIND_CC 1

#if (!defined(LIBDEBUGINFO_WANT_PROTOTYPES) && \
     defined(__KOS__) && defined(__KERNEL__))
#define LIBDEBUGINFO_WANT_PROTOTYPES
#endif /* ... */

#if (defined(__KOS__) && defined(__KERNEL__) && \
     defined(BUILDING_KERNEL_CORE))
#define LIBDEBUGINFO_DECL __PUBDEF
#elif defined(__LIBDEBUGINFO_STATIC)
#define LIBDEBUGINFO_DECL __INTDEF
#else /* ... */
#define LIBDEBUGINFO_DECL __IMPDEF
#endif /* !... */

/* Library name for use with `dlopen()' */
#define LIBDEBUGINFO_LIBRARY_NAME "libdebuginfo.so"

/* Debug info error codes. */
#define DEBUG_INFO_ERROR_SUCCESS 0 /* Function completed successfully. */
#define DEBUG_INFO_ERROR_NOFRAME 1 /* No debug information associated with the given location. */
#define DEBUG_INFO_ERROR_CORRUPT 2 /* Debug information has been corrupted. */

#endif /* !_LIBDEBUGINFO_API_H */
