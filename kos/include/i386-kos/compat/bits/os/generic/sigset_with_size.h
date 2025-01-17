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
#ifndef _I386_KOS_COMPAT_BITS_OS_GENERIC_SIGSET_WITH_SIZE_H
#define _I386_KOS_COMPAT_BITS_OS_GENERIC_SIGSET_WITH_SIZE_H 1

#include <hybrid/host.h>
#ifdef __x86_64__
#include <bits/os/generic/sigset_with_size32.h>
#define compat_sigset_with_size                 __sigset_with_sizex32
#define __OFFSET_COMPAT_SIGSET_WITH_SIZE_SIGSET __OFFSET_SIGSET_WITH_SIZEX32_SIGSET
#define __OFFSET_COMPAT_SIGSET_WITH_SIZE_SIGSIZ __OFFSET_SIGSET_WITH_SIZEX32_SIGSIZ
#define __SIZEOF_COMPAT_SIGSET_WITH_SIZE        __SIZEOF_SIGSET_WITH_SIZEX32
#define __ALIGNOF_COMPAT_SIGSET_WITH_SIZE       __ALIGNOF_SIGSET_WITH_SIZEX32
#endif /* __x86_64__ */

#endif /* !_I386_KOS_COMPAT_BITS_OS_GENERIC_SIGSET_WITH_SIZE_H */
