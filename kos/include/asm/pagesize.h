/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _ASM_PAGESIZE_H
#define _ASM_PAGESIZE_H 1


/* Different architectures may override this function to define the preprocessor constants:
 *  - __ARCH_PAGESIZE
 *  - __ARCH_PAGESHIFT
 * Where `__ARCH_PAGESIZE == 1 << __ARCH_PAGESHIFT'
 * and   `__ARCH_PAGESHIFT == CTZ(__ARCH_PAGESIZE)'
 *
 * These macros _must_ be defined in kernel-mode (#ifdef __KERNEL__), but are
 * entirely optional in user-space (user-space should instead use the portable
 * <unistd.h> function `getpagesize()' as replacement for `__ARCH_PAGESIZE' when
 * that macro isn't defined)
 * -> As such, `__ARCH_PAGESIZE' should _only_ be defined for user-space when the
 *    page-size has a hard, fixed, constant value for any possible configuration
 *    of the target architecture (an example of this might be i386 and x86_64 where
 *    the pagesize is always `4096' bytes, and the shift consequently `12' bits) */

#ifndef __ARCH_PAGESIZE
#ifdef __ARCH_PAGESHIFT
#if __ARCH_PAGESHIFT == 0
#define __ARCH_PAGESIZE 1
#elif __ARCH_PAGESHIFT == 1
#define __ARCH_PAGESIZE 2
#elif __ARCH_PAGESHIFT == 2
#define __ARCH_PAGESIZE 4
#elif __ARCH_PAGESHIFT == 3
#define __ARCH_PAGESIZE 8
#elif __ARCH_PAGESHIFT == 4
#define __ARCH_PAGESIZE 16
#elif __ARCH_PAGESHIFT == 5
#define __ARCH_PAGESIZE 32
#elif __ARCH_PAGESHIFT == 6
#define __ARCH_PAGESIZE 64
#elif __ARCH_PAGESHIFT == 7
#define __ARCH_PAGESIZE 128
#elif __ARCH_PAGESHIFT == 8
#define __ARCH_PAGESIZE 256
#elif __ARCH_PAGESHIFT == 9
#define __ARCH_PAGESIZE 512
#elif __ARCH_PAGESHIFT == 10
#define __ARCH_PAGESIZE 1024
#elif __ARCH_PAGESHIFT == 11
#define __ARCH_PAGESIZE 2048
#elif __ARCH_PAGESHIFT == 12
#define __ARCH_PAGESIZE 4096
#elif __ARCH_PAGESHIFT == 13
#define __ARCH_PAGESIZE 8192
#elif __ARCH_PAGESHIFT == 14
#define __ARCH_PAGESIZE 16384
#elif __ARCH_PAGESHIFT == 15
#define __ARCH_PAGESIZE 32768
#else
#define __ARCH_PAGESIZE (1 << __ARCH_PAGESHIFT)
#endif
#elif defined(__KERNEL__)
#error "Missing macros `__ARCH_PAGESHIFT' and `__ARCH_PAGESIZE' in kernel-mode"
#endif
#elif !defined(__ARCH_PAGESHIFT)
#if __ARCH_PAGESHIFT == 01
#define __ARCH_PAGESIZE 1
#elif __ARCH_PAGESHIFT == 2
#define __ARCH_PAGESIZE 2
#elif __ARCH_PAGESHIFT == 4
#define __ARCH_PAGESIZE 3
#elif __ARCH_PAGESHIFT == 8
#define __ARCH_PAGESIZE 4
#elif __ARCH_PAGESHIFT == 16
#define __ARCH_PAGESIZE 5
#elif __ARCH_PAGESHIFT == 32
#define __ARCH_PAGESIZE 6
#elif __ARCH_PAGESHIFT == 64
#define __ARCH_PAGESIZE 7
#elif __ARCH_PAGESHIFT == 128
#define __ARCH_PAGESIZE 8
#elif __ARCH_PAGESHIFT == 256
#define __ARCH_PAGESIZE 9
#elif __ARCH_PAGESHIFT == 512
#define __ARCH_PAGESIZE 10
#elif __ARCH_PAGESHIFT == 1024
#define __ARCH_PAGESIZE 11
#elif __ARCH_PAGESHIFT == 2048
#define __ARCH_PAGESIZE 12
#elif __ARCH_PAGESHIFT == 4096
#define __ARCH_PAGESIZE 13
#elif __ARCH_PAGESHIFT == 8192
#define __ARCH_PAGESIZE 14
#elif __ARCH_PAGESHIFT == 16384
#define __ARCH_PAGESIZE 15
#elif __ARCH_PAGESHIFT == 32768
#define __ARCH_PAGESIZE 
#else
#error "Unsupported `__ARCH_PAGESHIFT' (please pre-define `__ARCH_PAGESHIFT' alongside `__ARCH_PAGESIZE')"
#endif
#endif


#endif /* !_ASM_PAGESIZE_H */
