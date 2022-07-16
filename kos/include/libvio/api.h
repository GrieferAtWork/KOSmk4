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
#ifndef _LIBVIO_API_H
#define _LIBVIO_API_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#ifdef __KERNEL__
/*[[[config CONFIG_HAVE_KERNEL_VIO = true]]]*/
#ifdef CONFIG_NO_KERNEL_VIO
#undef CONFIG_HAVE_KERNEL_VIO
#elif !defined(CONFIG_HAVE_KERNEL_VIO)
#define CONFIG_HAVE_KERNEL_VIO
#elif (-CONFIG_HAVE_KERNEL_VIO - 1) == -1
#undef CONFIG_HAVE_KERNEL_VIO
#define CONFIG_NO_KERNEL_VIO
#endif /* ... */
/*[[[end]]]*/
#endif /* __KERNEL__ */


/* Configure optional features based on architecture */
#undef LIBVIO_CONFIG_ENABLED
#if !defined(__KERNEL__) || !defined(CONFIG_NO_KERNEL_VIO)
#define LIBVIO_CONFIG_ENABLED 1
#endif /* !__KERNEL__ || !CONFIG_NO_KERNEL_VIO */

#undef LIBVIO_CONFIG_HAVE_QWORD
#undef LIBVIO_CONFIG_HAVE_QWORD_CMPXCH
#undef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#ifdef LIBVIO_CONFIG_ENABLED
#if defined(__x86_64__)
#define LIBVIO_CONFIG_HAVE_QWORD        1
#define LIBVIO_CONFIG_HAVE_QWORD_CMPXCH 1
#define LIBVIO_CONFIG_HAVE_XWORD_CMPXCH 1 /* Because of the `cmpxchg16b' instruction */
#elif defined(__i386__)
#define LIBVIO_CONFIG_HAVE_QWORD_CMPXCH 1 /* Because of the `cmpxchg8b' instruction */
#else /* Arch... */
#include <hybrid/typecore.h>
#if __SIZEOF_POINTER__ >= 8
#define LIBVIO_CONFIG_HAVE_QWORD 1
#define LIBVIO_CONFIG_HAVE_QWORD_CMPXCH 1
#endif /* __SIZEOF_POINTER__ >= 8 */
#endif /* !Arch... */
#endif /* LIBVIO_CONFIG_ENABLED */


#if defined(__i386__) && !defined(__x86_64__)
#define LIBVIO_CC __ATTR_FASTCALL
#else /* ... */
#define LIBVIO_CC /* nothing */
#endif /* !... */

#if (!defined(LIBVIO_WANT_PROTOTYPES) && \
     defined(__KERNEL__) && defined(LIBVIO_CONFIG_ENABLED))
#define LIBVIO_WANT_PROTOTYPES
#endif /* __KERNEL__ && LIBVIO_CONFIG_ENABLED */

#ifdef LIBVIO_WANT_PROTOTYPES
#define LIBVIO_DECL __PUBDEF
#elif defined(__LIBVIO_STATIC)
#define LIBVIO_DECL __INTDEF
#else /* ... */
#define LIBVIO_DECL __IMPDEF
#endif /* !... */

/* Library name for use with `dlopen()' */
#define LIBVIO_LIBRARY_NAME "libvio.so"

#endif /* !_LIBVIO_API_H */
