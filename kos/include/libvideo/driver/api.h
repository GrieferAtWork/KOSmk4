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
#ifndef _LIBVIDEO_DRIVER_API_H
#define _LIBVIDEO_DRIVER_API_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBVIDEO_DRIVER_CC __ATTR_STDCALL
#else /* ... */
#define LIBVIDEO_DRIVER_CC /* nothing */
#endif /* !... */

#if (!defined(LIBVIDEO_DRIVER_WANT_PROTOTYPES) && \
     defined(__KOS__) && defined(__KERNEL__))
#define LIBVIDEO_DRIVER_WANT_PROTOTYPES
#endif /* ... */

#if (defined(__KOS__) && defined(__KERNEL__) && \
     defined(BUILDING_KERNEL_CORE))
#define LIBVIDEO_DRIVER_DECL __PUBDEF
#elif defined(__LIBVIDEO_DRIVER_STATIC)
#define LIBVIDEO_DRIVER_DECL __INTDEF
#else /* ... */
#define LIBVIDEO_DRIVER_DECL __IMPDEF
#endif /* !... */

/* Library name for use with `dlopen(3D)' */
#define LIBVIDEO_DRIVER_LIBRARY_NAME "libvideo-driver.so"

#endif /* !_LIBVIDEO_DRIVER_API_H */
