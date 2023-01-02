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
#ifndef _COMPAT_BITS_OS_GENERIC_SIGSET_WITH_SIZE_H
#define _COMPAT_BITS_OS_GENERIC_SIGSET_WITH_SIZE_H 1

#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#include <bits/os/sigset_with_size.h>
#define compat_sigset_with_size                 sigset_with_size
#define __OFFSET_COMPAT_SIGSET_WITH_SIZE_SIGSET __OFFSET_SIGSET_WITH_SIZE_SIGSET
#define __OFFSET_COMPAT_SIGSET_WITH_SIZE_SIGSIZ __OFFSET_SIGSET_WITH_SIZE_SIGSIZ
#define __SIZEOF_COMPAT_SIGSET_WITH_SIZE        __SIZEOF_SIGSET_WITH_SIZE
#define __ALIGNOF_COMPAT_SIGSET_WITH_SIZE       __ALIGNOF_SIGSET_WITH_SIZE
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_BITS_OS_GENERIC_SIGSET_WITH_SIZE_H */
