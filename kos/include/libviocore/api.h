/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBVIOCORE_API_H
#define _LIBVIOCORE_API_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <libvio/api.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBVIOCORE_CC __ATTR_FASTCALL
#else
#define LIBVIOCORE_CC /* nothing */
#endif

#if (!defined(LIBVIOCORE_WANT_PROTOTYPES) &&    \
     defined(__KOS__) && defined(__KERNEL__) && \
     defined(LIBVIO_CONFIG_ENABLED))
#define LIBVIOCORE_WANT_PROTOTYPES 1
#endif

#ifdef __LIBVIOCORE_STATIC
#define LIBVIOCORE_DECL __INTDEF
#else /* __LIBVIOCORE_STATIC */
#define LIBVIOCORE_DECL __IMPDEF
#endif /* !__LIBVIOCORE_STATIC */

/* Library name for use with `dlopen()' */
#define LIBVIOCORE_LIBRARY_NAME "libviocore.so"

#endif /* !_LIBVIOCORE_API_H */
