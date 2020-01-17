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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_AUXV_H
#define _BITS_AUXV_H 1

#include <__stdinc.h>

#ifndef AT_NULL
/* Legal values for a_type (entry type). */
#define AT_NULL         0               /* End of vector */
#define AT_IGNORE       1               /* Entry should be ignored */
#define AT_EXECFD       2               /* File descriptor of program */
#define AT_PHDR         3               /* Program headers for program */
#define AT_PHENT        4               /* Size of program header entry */
#define AT_PHNUM        5               /* Number of program headers */
#define AT_PAGESZ       6               /* System page size */
#define AT_BASE         7               /* Base address of interpreter */
#define AT_FLAGS        8               /* Flags */
#define AT_ENTRY        9               /* Entry point of program */
#define AT_NOTELF       10              /* Program is not ELF */
#define AT_UID          11              /* Real uid */
#define AT_EUID         12              /* Effective uid */
#define AT_GID          13              /* Real gid */
#define AT_EGID         14              /* Effective gid */
#define AT_CLKTCK       17              /* Frequency of times() */

/* Some more special a_type values describing the hardware. */
#define AT_PLATFORM     15              /* String identifying platform. */
#define AT_HWCAP        16              /* Machine dependent hints about processor capabilities. */

/* This entry gives some information about the
 * FPU initialization performed by the kernel. */
#define AT_FPUCW        18              /* Used FPU control word. */

/* Cache block sizes. */
#define AT_DCACHEBSIZE  19              /* Data cache block size. */
#define AT_ICACHEBSIZE  20              /* Instruction cache block size. */
#define AT_UCACHEBSIZE  21              /* Unified cache block size. */

/* A special ignored value for PPC, used by the kernel to
 * control the interpretation of the AUXV. Must be > 16. */
#define AT_IGNOREPPC    22              /* Entry should be ignored. */
#define AT_SECURE       23              /* Boolean, was exec setuid-like?  */
#define AT_BASE_PLATFORM 24             /* String identifying real platforms.*/

/* Pointer to the global system page used for system calls and other nice things. */
#define AT_SYSINFO      32
#define AT_SYSINFO_EHDR 33

/* Shapes of the caches.  Bits 0-3 contains associativity; bits 4-7
 * contains log2 of line size; mask those to get cache size. */
#define AT_L1I_CACHESHAPE       34
#define AT_L1D_CACHESHAPE       35
#define AT_L2_CACHESHAPE        36
#define AT_L3_CACHESHAPE        37
#endif /* !AT_NULL */


#endif /* _BITS_AUXV_H */
