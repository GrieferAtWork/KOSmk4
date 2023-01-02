/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_COMPAT_BITS_OS_MCONTEXT_H
#define _I386_KOS_COMPAT_BITS_OS_MCONTEXT_H 1

#include <hybrid/host.h>

#ifdef __x86_64__
#ifdef __KOS__
#include <bits/os/kos/mcontext32.h>
#define __COMPAT_MCONTEXT_NGREG __MCONTEXTX32_NGREG
#define compat_mcontext         __mcontextx32
#elif defined(__linux__)
#include <bits/os/linux/mcontext32.h>
#define __COMPAT_MCONTEXT_NGREG __MCONTEXT_LINUX32_NGREG
#define compat_mcontext         __mcontext_linux32
#else /* ... */
#include <__crt.h>
#ifdef __CRT_CYG_PRIMARY
#include <bits/os/cygwin/mcontext32.h>
#define compat_mcontext __cygwin32_mcontext
#endif /* __CRT_CYG_PRIMARY */
#endif /* !... */
#endif /* __x86_64__ */

#endif /* !_I386_KOS_COMPAT_BITS_OS_MCONTEXT_H */
