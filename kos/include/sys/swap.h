/* HASH CRC-32:0x67a5c848 */
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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/[...]/sys/swap.h) */
/* (#) Portability: NetBSD        (/sys/sys/swap.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/swap.h) */
/* (#) Portability: diet libc     (/include/sys/swap.h) */
/* (#) Portability: musl libc     (/include/sys/swap.h) */
/* (#) Portability: uClibc        (/include/sys/swap.h) */
#ifndef _SYS_SWAP_H
#define _SYS_SWAP_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/os/swap.h>

__SYSDECL_BEGIN

/* The swap priority is encoded as:
 *  - (prio << SWAP_FLAG_PRIO_SHIFT) & SWAP_FLAG_PRIO_MASK */
#ifdef __SWAP_FLAG_PREFER
#define SWAP_FLAG_PREFER __SWAP_FLAG_PREFER /* Set if swap priority is specified. */
#endif /* __SWAP_FLAG_PREFER */
#ifdef __SWAP_FLAG_PRIO_MASK
#define SWAP_FLAG_PRIO_MASK __SWAP_FLAG_PRIO_MASK
#endif /* __SWAP_FLAG_PRIO_MASK */
#ifdef __SWAP_FLAG_PRIO_SHIFT
#define SWAP_FLAG_PRIO_SHIFT __SWAP_FLAG_PRIO_SHIFT
#endif /* __SWAP_FLAG_PRIO_SHIFT */
#ifdef __SWAP_FLAG_DISCARD
#define SWAP_FLAG_DISCARD __SWAP_FLAG_DISCARD /* Discard swap cluster after use. */
#endif /* __SWAP_FLAG_DISCARD */

#ifdef __CC__

/* @param swapflags: Set of `SWAP_FLAG_*' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,swapon,(char const *__path, __STDC_INT_AS_UINT_T __swapflags),(__path,__swapflags))
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,swapoff,(char const *__path),(__path))

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SWAP_H */
