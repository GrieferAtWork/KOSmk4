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
#ifndef _I386_KOS_KOS_BITS_THREAD_H
#define _I386_KOS_KOS_BITS_THREAD_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <asm/intrin.h>

/* In i386 user-space, try to use `arch_prctl(2)' to get/set  %fs/&gs.base
 * Note that we could still use `wr(fs|gs)base' in this case (because it's
 * emulated  by the kernel), but that method  is still a little bit slower
 * since it involves the kernel having to decode a faulting instruction.
 *
 * As such, when we know that the CPU won't be able to natively execute
 * the (rd|wr)(fs|gs)base instructions, then we always link against the
 * equivalent system calls. */
#if !defined(__KERNEL__) && (defined(__KOS__) || !defined(__x86_64__))
#if !defined(__x86_64__) || defined(CONFIG_NO_X86_NATIVE_RDWRFSGSBASE)
#include <asm/prctl.h>
#include <kos/syscalls.h>
#if __CRT_HAVE_XSC(arch_prctl)
#ifdef ARCH_GET_FS
#define __x86_fast_rdfsbase(r) (void)sys_Xarch_prctl(ARCH_GET_FS, (uintptr_t *)&(r))
#endif /* ARCH_GET_FS */
#ifdef ARCH_SET_FS
#define __x86_fast_wrfsbase(v) (void)sys_Xarch_prctl(ARCH_SET_FS, (uintptr_t *)(v))
#endif /* ARCH_SET_FS */
#ifdef ARCH_GET_GS
#define __x86_fast_rdgsbase(r) (void)sys_Xarch_prctl(ARCH_GET_GS, (uintptr_t *)&(r))
#endif /* ARCH_GET_GS */
#ifdef ARCH_SET_GS
#define __x86_fast_wrgsbase(v) (void)sys_Xarch_prctl(ARCH_SET_GS, (uintptr_t *)(v))
#endif /* ARCH_SET_GS */
#endif /* __CRT_HAVE_XSC(arch_prctl) */
#endif /* !__x86_64__ */
#endif /* __KOS__ && !__x86_64__ */

/* Because of ABI requirements, we can determine the %fs/%gs base by reading at offset=0 */
#if defined(__KOS__) && defined(__KERNEL__)
#ifdef __x86_64__
#define __x86_abi_rdgsbase(r) (void)((r) = __rdgsptr(0))
#else /* __x86_64__ */
#define __x86_abi_rdfsbase(r) (void)((r) = __rdfsptr(0))
#endif /* !__x86_64__ */
#elif defined(__x86_64__)
#define __x86_abi_rdfsbase(r) (void)((r) = __rdfsptr(0))
#else /* ... */
#define __x86_abi_rdgsbase(r) (void)((r) = __rdgsptr(0))
#endif /* !... */


/* Fallback definitions for fast fs/gs base access */
#ifndef __x86_fast_rdfsbase
#define __x86_fast_rdfsbase(r) (void)((r) = __rdfsbase())
#endif /* !__x86_fast_rdfsbase */
#ifndef __x86_fast_wrfsbase
#define __x86_fast_wrfsbase(v) __wrfsbase(v)
#endif /* !__x86_fast_wrfsbase */
#ifndef __x86_fast_rdgsbase
#define __x86_fast_rdgsbase(r) (void)((r) = __rdgsbase())
#endif /* !__x86_fast_rdgsbase */
#ifndef __x86_fast_wrgsbase
#define __x86_fast_wrgsbase(v) __wrgsbase(v)
#endif /* !__x86_fast_wrgsbase */


/* Fallback definitions for ABI fs/gs base access */
#ifndef __x86_abi_rdfsbase
#define __x86_abi_rdfsbase __x86_fast_rdfsbase
#endif /* !__x86_abi_rdfsbase */
#ifndef __x86_abi_rdgsbase
#define __x86_abi_rdgsbase __x86_fast_rdgsbase
#endif /* !__x86_abi_rdgsbase */


/* Define the actual high-level TLS get/set macros.
 * Note the following mapping:
 * ```
 * +--------+------+------+
 * | TLS    | Kern | User |
 * +--------+------+------+
 * | i386   | FS   | GS   |
 * | x86_64 | GS   | FS   |
 * +--------+------+------+
 * ```
 */

#if defined(__x86_64__) == defined(__KERNEL__)
/* Use GS for TLS */
#define RD_TLS_BASE_REGISTER   __x86_abi_rdgsbase
#define RD_TLS_BASE_REGISTER_S __x86_fast_rdgsbase
#define WR_TLS_BASE_REGISTER   __x86_fast_wrgsbase
#else /* ... */
/* Use FS for TLS */
#define RD_TLS_BASE_REGISTER   __x86_abi_rdfsbase
#define RD_TLS_BASE_REGISTER_S __x86_fast_rdfsbase
#define WR_TLS_BASE_REGISTER   __x86_fast_wrfsbase
#endif /* !... */

#endif /* !_I386_KOS_KOS_BITS_THREAD_H */
