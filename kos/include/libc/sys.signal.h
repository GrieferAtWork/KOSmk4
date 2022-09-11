/* HASH CRC-32:0xe9114e0d */
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
#ifndef _LIBC_SYS_SIGNAL_H
#define _LIBC_SYS_SIGNAL_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include "core/sys.signal.h"

#if !defined(____libc_sigblockall_defined) && defined(____libc_core_sigblockall_defined)
#define ____libc_sigblockall_defined
#define __libc_sigblockall __libc_core_sigblockall
#endif /* !____libc_sigblockall_defined && ____libc_core_sigblockall_defined */
#if !defined(____libc_sigunblockall_defined) && defined(____libc_core_sigunblockall_defined)
#define ____libc_sigunblockall_defined
#define __libc_sigunblockall __libc_core_sigunblockall
#endif /* !____libc_sigunblockall_defined && ____libc_core_sigunblockall_defined */

#endif /* __CC__ */

#endif /* !_LIBC_SYS_SIGNAL_H */
