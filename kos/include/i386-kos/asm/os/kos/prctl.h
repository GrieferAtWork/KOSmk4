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
#ifndef _I386_KOS_ASM_OS_KOS_PRCTL_H
#define _I386_KOS_ASM_OS_KOS_PRCTL_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

/* Get/Set the %fs / %gs base address.
 *
 * Note that on linux, these codes are only available on x86_64, but
 * under  KOS even the 32-bit kernel implements them. Also note that
 * on KOS, you  can use `__wr(fs|gs)base()'  from <asm/intrin.h>  in
 * order to get/set the %fs/%gs-base register, both in 64-bit--,  as
 * well as in 32-bit mode (the later via instruction emulation).
 *
 * NOTE: Because use of a regular system call is usually faster, the
 *       preferred method of setting the %fs/%gs-base under i386  is
 *       still to use `arch_prctl()' with the below codes. */
#if !defined(__USE_KOS_ALTERATIONS) || defined(__x86_64__) || defined(__KOS__)
#define ARCH_SET_GS 0x1001 /* [void *addr] Set %gs.base */
#define ARCH_SET_FS 0x1002 /* [void *addr] Set %fs.base */
#define ARCH_GET_FS 0x1003 /* [void **addr] Get %fs.base */
#define ARCH_GET_GS 0x1004 /* [void **addr] Set %fs.base */
#endif /* !__USE_KOS_ALTERATIONS || __x86_64__ || __KOS__ */

#define ARCH_GET_CPUID 0x1011 /* [void] Returns 0/1 indicative of `cpuid' being available. */
#define ARCH_SET_CPUID 0x1012 /* [bool arg] Enable/disable use of `cpuid' (when disabled, raise `SIGSEGV')
                               * Preserved across clone(2)/fork(2); reset on exec(2).
                               * @throw: E_UNSUPPORTED_DEVICE: [ENODEV] Not supported by the underlying CPU. */

/* Not supported (used to map the VDSO; -- KOS doesn't have something like that) */
#ifndef __KOS__
#define ARCH_MAP_VDSO_X32 0x2001
#define ARCH_MAP_VDSO_32  0x2002
#define ARCH_MAP_VDSO_64  0x2003
#endif /* !__KOS__ */


#endif /* !_I386_KOS_ASM_OS_KOS_PRCTL_H */
