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
#ifndef _COMPAT_KOS_ASM_FUTEX_H
#define _COMPAT_KOS_ASM_FUTEX_H 1

#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#include <hybrid/typecore.h>
#if __ARCH_COMPAT_SIZEOF_POINTER >= 8
#define COMPAT_LFUTEX_WAIT_LOCK_TIDMASK  __UINT64_C(0x3fffffffffffffff) /* Mask for the TID. */
#define COMPAT_LFUTEX_WAIT_LOCK_WAITERS  __UINT64_C(0x4000000000000000) /* Flag: Set by the kernel before waiting for the futex. */
#define COMPAT_LFUTEX_WAIT_LOCK_OWNDIED  __UINT64_C(0x8000000000000000) /* Flag: Set by the kernel if a robust futex died. */
#else /* __ARCH_COMPAT_SIZEOF_POINTER >= 8 */
#define COMPAT_LFUTEX_WAIT_LOCK_TIDMASK  __UINT32_C(0x3fffffff) /* Mask for the TID. */
#define COMPAT_LFUTEX_WAIT_LOCK_WAITERS  __UINT32_C(0x40000000) /* Flag: Set by the kernel before waiting for the futex. */
#define COMPAT_LFUTEX_WAIT_LOCK_OWNDIED  __UINT32_C(0x80000000) /* Flag: Set by the kernel if a robust futex died. */
#endif /* __ARCH_COMPAT_SIZEOF_POINTER < 8 */
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_KOS_ASM_FUTEX_H */
