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
#ifndef _I386_KOS_BITS_OS_KOS_SYSINFO64_H
#define _I386_KOS_BITS_OS_KOS_SYSINFO64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#ifdef __x86_64__
#define __sysinfox64  sysinfo
#define SI_LOAD_SHIFT __SIX64_LOAD_SHIFT
#endif /* __x86_64__ */

#define __SIX64_LOAD_SHIFT 16

#ifdef __CC__
__DECL_BEGIN

#ifdef __USE_KOS_KERNEL
#define sysinfox64 __sysinfox64
#endif /* __USE_KOS_KERNEL */

struct __sysinfox64 {
	__LONG64_TYPE__  uptime;    /* Seconds since boot. */
	__ULONG64_TYPE__ loads[3];  /* 1, 5, and 15 minute load averages .*/
	__ULONG64_TYPE__ totalram;  /* Total usable main memory size. */
	__ULONG64_TYPE__ freeram;   /* Available memory size. */
	__ULONG64_TYPE__ sharedram; /* Amount of shared memory. */
	__ULONG64_TYPE__ bufferram; /* Memory used by buffers. */
	__ULONG64_TYPE__ totalswap; /* Total swap space size. */
	__ULONG64_TYPE__ freeswap;  /* swap space still available. */
	__UINT16_TYPE__  procs;     /* Number of current processes. */
	__UINT16_TYPE__  pad;       /* Explicit padding for m68k. */
	__UINT32_TYPE__  __si_pad2; /* ... */
	__ULONG64_TYPE__ totalhigh; /* Total high memory size. */
	__ULONG64_TYPE__ freehigh;  /* Available high memory size. */
	__UINT32_TYPE__  mem_unit;  /* Memory unit size in bytes. */
	char _f[20 - 2 * sizeof(__ULONG64_TYPE__) - sizeof(__u32)]; /* Padding: libc5 uses this... */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_OS_KOS_SYSINFO64_H */
