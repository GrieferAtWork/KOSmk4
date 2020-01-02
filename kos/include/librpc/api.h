/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBRPC_API_H
#define _LIBRPC_API_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#if defined(__i386__) && !defined(__x86_64__)
#define LIBRPC_CC  __ATTR_STDCALL
#define LIBRPC_VCC __ATTR_CDECL
#else
#define LIBRPC_CC  /* nothing */
#define LIBRPC_VCC /* nothing */
#endif

#if 0
#define LIBRPC_WANT_PROTOTYPES 1
#endif

#if defined(__LIBRPC_STATIC)
#define LIBRPC_DECL __INTDEF
#else
#define LIBRPC_DECL __IMPDEF
#endif

/* Library name for use with `dlopen()' */
#define LIBRPC_LIBRARY_NAME     "librpc.so"

#endif /* !_LIBRPC_API_H */
