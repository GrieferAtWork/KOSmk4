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
#ifndef _LIBDL_API_H
#define _LIBDL_API_H 1

#include <__crt.h>
#include <__stdinc.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBDL_CC  __ATTR_FASTCALL
#define LIBDL_VCC __ATTR_CDECL
#else /* __i386__ && !__x86_64__ */
#define LIBDL_CC  __LIBKCALL
#define LIBDL_VCC __VLIBKCALL
#endif /* !__i386__ || __x86_64__ */

#ifndef __DLFCN_CC
#define __DLFCN_CC  __LIBCCALL
#define __DLFCN_VCC __VLIBCCALL
#endif /* !__DLFCN_CC */

#if 0
#define LIBDL_WANT_PROTOTYPES
#endif

#ifdef __LIBDL_STATIC
#define LIBDL_DECL __INTDEF
#else /* ... */
#define LIBDL_DECL __IMPDEF
#endif /* !... */

/* Library name for use with `dlopen(3D)' */
#define LIBDL_LIBRARY_NAME "libdl.so"

#endif /* !_LIBDL_API_H */
