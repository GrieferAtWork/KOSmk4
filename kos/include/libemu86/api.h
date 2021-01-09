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
#ifndef _LIBEMU86_API_H
#define _LIBEMU86_API_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBEMU86_CC __ATTR_FASTCALL
#else
#define LIBEMU86_CC /* nothing */
#endif

#if (!defined(LIBEMU86_WANT_PROTOTYPES) && \
     (defined(__LIBEMU86_STATIC) ||        \
      (defined(__KOS__) && defined(__KERNEL__))))
#define LIBEMU86_WANT_PROTOTYPES 1
#endif

/* Library name for use with `dlopen()' */
#define LIBEMU86_LIBRARY_NAME "libemu86.so"


#ifdef __LIBEMU86_STATIC
#define LIBEMU86_DECL __PRIVATE
#define LIBEMU86_IMPL __PRIVATE

#ifndef CONFIG_LIBEMU86_WANT_16BIT
#define CONFIG_LIBEMU86_WANT_16BIT 0
#endif /* !CONFIG_LIBEMU86_WANT_16BIT */

#ifndef CONFIG_LIBEMU86_WANT_32BIT
#if !defined(__x86_64__) && defined(__i386__)
#define CONFIG_LIBEMU86_WANT_32BIT 1
#else /* !__x86_64__ && __i386__ */
#define CONFIG_LIBEMU86_WANT_32BIT 0
#endif /* __x86_64__ || !__i386__ */
#endif /* !CONFIG_LIBEMU86_WANT_32BIT */

#ifndef CONFIG_LIBEMU86_WANT_64BIT
#ifdef __x86_64__
#define CONFIG_LIBEMU86_WANT_64BIT 1
#else /* __x86_64__ */
#define CONFIG_LIBEMU86_WANT_64BIT 0
#endif /* !__x86_64__ */
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */

#else /* __LIBEMU86_STATIC */
#define LIBEMU86_DECL __IMPDEF
#define LIBEMU86_IMPL __EXPDEF

#ifndef CONFIG_LIBEMU86_WANT_16BIT
#ifdef __x86_64__
#define CONFIG_LIBEMU86_WANT_16BIT 0
#else /* __x86_64__ */
#define CONFIG_LIBEMU86_WANT_16BIT 1
#endif /* !__x86_64__ */
#endif /* !CONFIG_LIBEMU86_WANT_16BIT */

#ifndef CONFIG_LIBEMU86_WANT_32BIT
#define CONFIG_LIBEMU86_WANT_32BIT 1
#endif /* !CONFIG_LIBEMU86_WANT_32BIT */

#ifndef CONFIG_LIBEMU86_WANT_64BIT
#if defined(__x86_64__) || !defined(__i386__)
#define CONFIG_LIBEMU86_WANT_64BIT 1
#else /* __x86_64__ || !__i386__ */
#define CONFIG_LIBEMU86_WANT_64BIT 0
#endif /* !__x86_64__ && __i386__ */
#endif /* !CONFIG_LIBEMU86_WANT_64BIT */

#if ((CONFIG_LIBEMU86_WANT_16BIT != !defined(__x86_64__)) || \
     (CONFIG_LIBEMU86_WANT_32BIT != 1) ||                    \
     (CONFIG_LIBEMU86_WANT_64BIT != (defined(__x86_64__) || !defined(__i386__))))
#error "Invalid configuration for non-static linkage (must enable `__LIBEMU86_STATIC')"
#endif

#endif /* !__LIBEMU86_STATIC */

#if (CONFIG_LIBEMU86_WANT_16BIT + CONFIG_LIBEMU86_WANT_32BIT + CONFIG_LIBEMU86_WANT_64BIT) == 0
#error "Bad configuration: No emulation modes enabled"
#endif /* No modes enabled */

#undef CONFIG_LIBEMU86_NEED_ARCHMODE
#if (CONFIG_LIBEMU86_WANT_16BIT + CONFIG_LIBEMU86_WANT_32BIT + CONFIG_LIBEMU86_WANT_64BIT) > 1
#define CONFIG_LIBEMU86_NEED_ARCHMODE 1
#endif /* More than 1 mode enabled */



#endif /* !_LIBEMU86_API_H */
