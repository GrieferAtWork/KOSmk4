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
#ifndef _I386_KOS_ASM_NOMEM_ARCH_H
#define _I386_KOS_ASM_NOMEM_ARCH_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __x86_64__

#ifdef __KERNEL__
#ifdef __KOS__
/* On KOS, VIO mappings can be placed in the non-canon range, so we just use the page-dir identity range. */
#define __ARCH_NOMEM_BASE __UINT64_C(0xffff808000000000) /* == P64_MMAN_KERNEL_PDIR_IDENTITY_BASE */
#define __ARCH_NOMEM_SIZE __UINT64_C(0x0000008000000000) /* == P64_MMAN_KERNEL_PDIR_IDENTITY_SIZE */
#else /* __KOS__ */
#if 0 /* Technically, this much would be allowed, but this might get less in the future, so better be safe */
#define __ARCH_NOMEM_BASE __UINT64_C(0x0000800000000000) /* == X86_64_ADDRBUS_NONCANON_MIN */
#define __ARCH_NOMEM_SIZE __UINT64_C(0xffff000000000000) /* == (X86_64_ADDRBUS_NONCANON_MAX - X86_64_ADDRBUS_NONCANON_MIN) + 1 */
#else
 /* vvv these will still work for a 63-bit address bus (requiring only the top 2 bits to be sign-extended)
  *     i.e.: this still works with a non-cannon range of `0x4000000000000000 - 0xbfffffffffffffff' */
#define __ARCH_NOMEM_BASE __UINT64_C(0x4000000000000000)
#define __ARCH_NOMEM_SIZE __UINT64_C(0x8000000000000000)
#endif
#endif /* !__KOS__ */
#else /* __KERNEL__ */
/* All kernels ever developed for x86_64 (that I'm aware of) are high-memory kernels.
 * -> As such, user-space can never map the upper half of the address space. */
#define __ARCH_NOMEM_BASE __UINT64_C(0x8000000000000000)
#define __ARCH_NOMEM_SIZE __UINT64_C(0x8000000000000000)
#endif /* !__KERNEL__ */

#else /* __x86_64__ */

#ifdef __KERNEL__
#ifdef __KOS__
#define __ARCH_NOMEM_BASE __UINT32_C(0xffc00000) /* == P32_MMAN_KERNEL_PDIR_RESERVED_BASE */
#define __ARCH_NOMEM_SIZE __UINT32_C(0x00400000) /* == P32_MMAN_KERNEL_PDIR_RESERVED_SIZE */
#else /* __KOS__ */
/* Assume that this kernel also uses the end of the address space as page-dir identity mapping. */
#define __ARCH_NOMEM_BASE __UINT32_C(0xffc00000)
#define __ARCH_NOMEM_SIZE __UINT32_C(0x00400000)
#endif /* !__KOS__ */
#else /* __KERNEL__ */

#if (defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__) ||         \
     defined(__WINDOWS__) || defined(_WIN16) || defined(WIN16) || defined(_WIN32) || \
     defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) ||    \
     defined(__TOS_WIN__) || defined(_WIN32_WCE) || defined(WIN32_WCE))
/* The windows kernel takes up half of the address space. */
#define __ARCH_NOMEM_BASE __UINT32_C(0x80000000)
#define __ARCH_NOMEM_SIZE __UINT32_C(0x80000000)
#else /* ... */
/* Make a safe guess and assume that 1/4 of the address space is used by the kernel. */
/* FIXME: doesn't an x86_64 kernel allow user-space to use the full 4GiB address space? */
#define __ARCH_NOMEM_BASE __UINT32_C(0xc0000000)
#define __ARCH_NOMEM_SIZE __UINT32_C(0x40000000)
#endif /* !... */

#endif /* !__KERNEL__ */

#endif /* !__x86_64__ */

#endif /* !_I386_KOS_ASM_NOMEM_ARCH_H */
