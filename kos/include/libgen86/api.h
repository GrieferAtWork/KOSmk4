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
#ifndef _LIBGEN86_API_H
#define _LIBGEN86_API_H 1

#include <__stdinc.h>

/* Target execution context of generated code:
 *   16: realmode
 *   32: protected mode
 *   64: long mode
 */
#ifndef LIBGEN86_TARGET_BITS
#include <hybrid/host.h>
#ifdef __x86_64__
#define LIBGEN86_TARGET_BITS 64
#elif defined(__i386__)
#define LIBGEN86_TARGET_BITS 32
#else /* ... */
#include <hybrid/typecore.h>
#if __SIZEOF_POINTER__ == 4
#define LIBGEN86_TARGET_BITS 32
#elif __SIZEOF_POINTER__ == 8
#define LIBGEN86_TARGET_BITS 64
#elif __SIZEOF_POINTER__ == 2
#define LIBGEN86_TARGET_BITS 16
#else /* __SIZEOF_POINTER__ == ... */
#define LIBGEN86_TARGET_BITS 32 /* Fallback... */
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* !... */
#endif /* !LIBGEN86_TARGET_BITS */

#endif /* !_LIBGEN86_API_H */
