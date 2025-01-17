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
#ifndef _I386_KOS_ASM_PAGEID_H
#define _I386_KOS_ASM_PAGEID_H 1

/* Convert  virtual memory addresses  to/form their compressed variants
 * in the form of Page-IDs, where  a Page-ID strips away any  redundant
 * address bits, as well as the unpagable lower `__ARCH_PAGESHIFT' bits
 * The  idea of this mechanism is to use it to define a special address
 * space  mechanism that can be used for encoding/decoding keys for use
 * with an address tree with the purpose of associating additional data
 * with specific addresses/address-ranges.
 * >> uintptr_t pageid  = __ARCH_PAGEID_ENCODE(addr);
 * >> void     *newaddr = __ARCH_PAGEID_DECODE(pageid);
 * Note that following  an encode+decode, the  resulting address is  always
 * floor-aligned  by a  multiple of  `__ARCH_PAGESIZE' (if  defined; if not
 * defined,  this mechanism is  unavailable), and may  not necessary be the
 * same as the floor-page-aligned value  of the original address, as  other
 * redundant  address may have  been stripped (an  example of this behavior
 * would be the  address-space sign-extension found  on x86_64  processors,
 * where these macros simply strip off redundant sign-bits during encoding,
 * but re-add then during decoding) */

#ifndef __ARCH_PAGEID_ENCODE
#include <hybrid/host.h>
#include <hybrid/typecore.h>
#ifdef __x86_64__
#include <__stdinc.h>
#define __ARCH_PAGEID_TYPE_SIZEOF  8
#define __ARCH_PAGEID_TYPE         __UINT64_TYPE__
#define __ARCH_PAGEID_BITS         36 /* 48-bit address space minus 12-bit PAGESHIFT */
#define __ARCH_PAGEID_MAX          __UINT64_C(0xfffffffff) /* 36-bit */
#if defined(__INTELLISENSE__) && defined(__CC__) && defined(__cplusplus)
extern "C++" {
#define __ARCH_PAGEID_ENCODE __ARCH_PAGEID_ENCODE
#define __ARCH_PAGEID_DECODE __ARCH_PAGEID_DECODE
#define __ARCH_PAGEID_DECODE_USER __ARCH_PAGEID_DECODE_USER
#define __ARCH_PAGEID_DECODE_KERNEL __ARCH_PAGEID_DECODE_KERNEL
#define __ARCH_PAGEID_DECODE_ISUSER __ARCH_PAGEID_DECODE_ISUSER
#define __ARCH_PAGEID_DECODE_ISKERNEL __ARCH_PAGEID_DECODE_ISKERNEL
__UINT64_TYPE__ (__ARCH_PAGEID_ENCODE)(void const *addr);
__UINT64_TYPE__ (__ARCH_PAGEID_ENCODE)(__UINTPTR_TYPE__ addr);
void *(__ARCH_PAGEID_DECODE)(__UINT64_TYPE__ pageid);
void *(__ARCH_PAGEID_DECODE_USER)(__UINT64_TYPE__ userspace_pageid);
void *(__ARCH_PAGEID_DECODE_KERNEL)(__UINT64_TYPE__ kernelspace_pageid);
__BOOL (__ARCH_PAGEID_DECODE_ISUSER)(__UINT64_TYPE__ pageid);
__BOOL (__ARCH_PAGEID_DECODE_ISKERNEL)(__UINT64_TYPE__ pageid);
}
#else /* __INTELLISENSE__ && __CC__ && __cplusplus */
#define __ARCH_PAGEID_ENCODE(addr) ((__CCAST(__UINT64_TYPE__)(addr) >> 12) & __ARCH_PAGEID_MAX)
#define __ARCH_PAGEID_DECODE_USER(user_pageid)     __CCAST(void *)((__UINT64_TYPE__)(user_pageid) << 12)
#define __ARCH_PAGEID_DECODE_KERNEL(kernel_pageid) __CCAST(void *)(((__UINT64_TYPE__)(kernel_pageid) << 12) | __UINT64_C(0xffff800000000000))
#define __ARCH_PAGEID_DECODE_ISUSER(pageid)   (((pageid) & __UINT64_C(0x800000000)) == 0)
#define __ARCH_PAGEID_DECODE_ISKERNEL(pageid) (((pageid) & __UINT64_C(0x800000000)) != 0)
/* Re-construct the sign extension for kernel-space addresses */
#ifdef __CC__
#define __ARCH_PAGEID_DECODE(pageid) \
	((void *)(((__INT64_TYPE__)(pageid) << 28) >> 16))
#else /* __CC__ */
#define __ARCH_PAGEID_DECODE(pageid)                             \
	(((((pageid) >> 35) & 1) * __UINT64_C(0xffff800000000000)) | \
	 ((pageid) & __UINT64_C(0x7ffffffff)) << 12)
#endif /* !__CC__ */
#endif /* !__INTELLISENSE__ || !__CC__ || !__cplusplus */
#else /* __x86_64__ */
#define __ARCH_PAGEID_TYPE_SIZEOF    4
#define __ARCH_PAGEID_TYPE           __UINT32_TYPE__
#define __ARCH_PAGEID_BITS           20 /* 32-bit address space minus 12-bit PAGESHIFT */
#define __ARCH_PAGEID_MAX            __UINT64_C(0xfffff) /* 20-bit */
#ifdef __INTELLISENSE__
#include <__stdinc.h>
#if defined(__CC__) && defined(__cplusplus)
extern "C++" {
#define __ARCH_PAGEID_ENCODE __ARCH_PAGEID_ENCODE
#define __ARCH_PAGEID_DECODE __ARCH_PAGEID_DECODE
__UINT32_TYPE__ (__ARCH_PAGEID_ENCODE)(void const *addr);
__UINT32_TYPE__ (__ARCH_PAGEID_ENCODE)(__UINTPTR_TYPE__ addr);
void *(__ARCH_PAGEID_DECODE)(__UINT32_TYPE__ addr);
}
#endif /* __CC__ && __cplusplus */
#endif /* __INTELLISENSE__ */
#ifndef __ARCH_PAGEID_ENCODE
#define __ARCH_PAGEID_ENCODE(addr)   (__CCAST(__UINT32_TYPE__)(addr) >> 12)
#define __ARCH_PAGEID_DECODE(pageid) (__CCAST(void *)(__CCAST(__UINT32_TYPE__)(pageid) << 12))
#endif /* !__ARCH_PAGEID_ENCODE */
#endif /* !__x86_64__ */
#endif /* !__ARCH_PAGEID_ENCODE */

#endif /* !_I386_KOS_ASM_PAGEID_H */
