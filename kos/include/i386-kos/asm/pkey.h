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
#ifndef _I386_KOS_ASM_PKEY_H
#define _I386_KOS_ASM_PKEY_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

/*
 * >> #define __ARCH_HAVE_PKEY
 * Defined if the architecture supports protection keys.
 * When defined, libc will export the following function (in <sys/mman.h>)
 *     >> int pkey_alloc(unsigned int flags, unsigned int access_rights);
 *     >> int pkey_set(int pkey, unsigned int access_rights);
 *     >> int pkey_get(int pkey);
 *     >> int pkey_free(int pkey);
 *     >> int pkey_mprotect(void *addr, size_t len, int prot, int pkey);
 *
 * Arch-specific macros used to implement `pkey_get()' and `pkey_set()'
 * >> #define __arch_pkey_verify_key(pkey)             <BOOLEAN_EXPRESSION>
 * >> #define __arch_pkey_verify_rights(access_rights) <BOOLEAN_EXPRESSION>
 * >> #define __arch_pkey_get(pkey)                    <INTEGER_EXPRESSION>
 * >> #define __arch_pkey_set(pkey, access_rights)     <VOID_EXPRESSION>
 */

#if !defined(__CC__) || defined(__COMPILER_HAVE_GCC_ASM)
#define __ARCH_HAVE_PKEY

#define __arch_pkey_verify_key(pkey)             (__CCAST(unsigned int)(pkey) < 16)
#define __arch_pkey_verify_rights(access_rights) (__CCAST(unsigned int)(access_rights) <= 3)

#ifdef __CC__
#include <asm/intrin.h> /* __rdpkru(), __wrpkru() */
#define __arch_pkey_x86_shft(pkey) (unsigned int)((pkey)*2)
#define __arch_pkey_x86_mask(pkey) ((__UINT32_TYPE__)3 << __arch_pkey_x86_shft(pkey))
#define __arch_pkey_get(pkey) \
	((__rdpkru() >> __arch_pkey_x86_shft(pkey)) & 3)
#define __arch_pkey_set(pkey, access_rights)              \
	__wrpkru((__rdpkru() & ~__arch_pkey_x86_mask(pkey)) | \
	         ((__UINT32_TYPE__)(access_rights) << __arch_pkey_x86_shft(pkey)))
#endif /* __CC__ */
#endif /* !__CC__ || __COMPILER_HAVE_GCC_ASM */

#endif /* !_I386_KOS_ASM_PKEY_H */
