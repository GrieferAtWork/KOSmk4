/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LINUX_SYSINFO_H
#define _LINUX_SYSINFO_H 1

/* Taken from '/usr/include/linux/sysinfo.h' before being modified. */

#include <__stdinc.h>
#include "types.h"

__DECL_BEGIN

#define SI_LOAD_SHIFT    16
#ifdef __CC__
struct sysinfo {
	__kernel_long_t  uptime;    /* Seconds since boot. */
	__kernel_ulong_t loads[3];  /* 1, 5, and 15 minute load averages .*/
	__kernel_ulong_t totalram;  /* Total usable main memory size. */
	__kernel_ulong_t freeram;   /* Available memory size. */
	__kernel_ulong_t sharedram; /* Amount of shared memory. */
	__kernel_ulong_t bufferram; /* Memory used by buffers. */
	__kernel_ulong_t totalswap; /* Total swap space size. */
	__kernel_ulong_t freeswap;  /* swap space still available. */
	__u16            procs;     /* Number of current processes. */
	__u16            pad;       /* Explicit padding for m68k. */
	__kernel_ulong_t totalhigh; /* Total high memory size. */
	__kernel_ulong_t freehigh;  /* Available high memory size. */
	__u32            mem_unit;  /* Memory unit size in bytes. */
	char _f[20-2*sizeof(__kernel_ulong_t)-sizeof(__u32)]; /* Padding: libc5 uses this... */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_LINUX_SYSINFO_H */
