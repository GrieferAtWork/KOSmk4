/* HASH CRC-32:0x4c2ce53e */
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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/swap.h) */
/* (#) Portability: NetBSD        (/sys/sys/swap.h) */
/* (#) Portability: OpenBSD       (/sys/sys/swap.h) */
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
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_swapon
/* >> swapon(2)
 * @param swapflags: Set of `SWAP_FLAG_*' */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,swapon,(char const *__path, __STDC_INT_AS_UINT_T __swapflags),(__path,__swapflags))
#elif defined(__CRT_HAVE___swapon)
/* >> swapon(2)
 * @param swapflags: Set of `SWAP_FLAG_*' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,swapon,(char const *__path, __STDC_INT_AS_UINT_T __swapflags),__swapon,(__path,__swapflags))
#elif defined(__CRT_HAVE___libc_swapon)
/* >> swapon(2)
 * @param swapflags: Set of `SWAP_FLAG_*' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,swapon,(char const *__path, __STDC_INT_AS_UINT_T __swapflags),__libc_swapon,(__path,__swapflags))
#endif /* ... */
#ifdef __CRT_HAVE_swapoff
/* >> swapoff(2) */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,swapoff,(char const *__path),(__path))
#elif defined(__CRT_HAVE___swapoff)
/* >> swapoff(2) */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,swapoff,(char const *__path),__swapoff,(__path))
#elif defined(__CRT_HAVE___libc_swapoff)
/* >> swapoff(2) */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,swapoff,(char const *__path),__libc_swapoff,(__path))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SWAP_H */
