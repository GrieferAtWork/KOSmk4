/* HASH CRC-32:0xc746d273 */
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
#ifndef _LIBC_SIGNAL_H
#define _LIBC_SIGNAL_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include "core/signal.h"

#if !defined(____libc_raise_defined) && defined(____libc_core_raise_defined)
#define ____libc_raise_defined
#define __libc_raise __libc_core_raise
#endif /* !____libc_raise_defined && ____libc_core_raise_defined */
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
#define __libc_sigfillset __libc_core_sigfillset
#if !defined(____libc_sigprocmask_defined) && defined(____libc_core_sigprocmask_defined)
#define ____libc_sigprocmask_defined
#define __libc_sigprocmask __libc_core_sigprocmask
#endif /* !____libc_sigprocmask_defined && ____libc_core_sigprocmask_defined */
#if !defined(____libc_getsigmaskptr_defined) && defined(____libc_core_getsigmaskptr_defined)
#define ____libc_getsigmaskptr_defined
#define __libc_getsigmaskptr __libc_core_getsigmaskptr
#endif /* !____libc_getsigmaskptr_defined && ____libc_core_getsigmaskptr_defined */
#if !defined(____libc_setsigmaskptr_defined) && defined(____libc_core_setsigmaskptr_defined)
#define ____libc_setsigmaskptr_defined
#define __libc_setsigmaskptr __libc_core_setsigmaskptr
#endif /* !____libc_setsigmaskptr_defined && ____libc_core_setsigmaskptr_defined */
#if !defined(____libc_setsigmaskfullptr_defined) && defined(____libc_core_setsigmaskfullptr_defined)
#define ____libc_setsigmaskfullptr_defined
#define __libc_setsigmaskfullptr __libc_core_setsigmaskfullptr
#endif /* !____libc_setsigmaskfullptr_defined && ____libc_core_setsigmaskfullptr_defined */
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
#define __libc_sigisemptyset __libc_core_sigisemptyset

#endif /* __CC__ */

#endif /* !_LIBC_SIGNAL_H */
