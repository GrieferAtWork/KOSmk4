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
/*!replace_with_include <bits/os/sysinfo.h>*/
#ifndef _I386_KOS_BITS_OS_KOS_SYSINFO32_H
#define _I386_KOS_BITS_OS_KOS_SYSINFO32_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#if defined(__i386__) && !defined(__x86_64__)
#define __sysinfox32  sysinfo
#define SI_LOAD_SHIFT __SIX32_LOAD_SHIFT
#endif /* __i386__ && !__x86_64__ */

#define __SIX32_LOAD_SHIFT 16

#ifdef __CC__
__DECL_BEGIN

#ifdef __USE_KOS_KERNEL
#define sysinfox32 __sysinfox32
#endif /* __USE_KOS_KERNEL */

struct __sysinfox32 {
	__LONG32_TYPE__  uptime;    /* Seconds since boot. */
	__ULONG32_TYPE__ loads[3];  /* 1, 5, and 15 minute load averages .*/
	__ULONG32_TYPE__ totalram;  /* Total usable main memory size. */
	__ULONG32_TYPE__ freeram;   /* Available memory size. */
	__ULONG32_TYPE__ sharedram; /* Amount of shared memory. */
	__ULONG32_TYPE__ bufferram; /* Memory used by buffers. */
	__ULONG32_TYPE__ totalswap; /* Total swap space size. */
	__ULONG32_TYPE__ freeswap;  /* swap space still available. */
	__UINT16_TYPE__  procs;     /* Number of current processes. */
	__UINT16_TYPE__  pad;       /* Explicit padding for m68k. */
	__ULONG32_TYPE__ totalhigh; /* Total high memory size. */
	__ULONG32_TYPE__ freehigh;  /* Available high memory size. */
	__UINT32_TYPE__  mem_unit;  /* Memory unit size in bytes. */
	char _f[20 - 2 * sizeof(__ULONG32_TYPE__) - sizeof(__u32)]; /* Padding: libc5 uses this... */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_OS_KOS_SYSINFO32_H */
