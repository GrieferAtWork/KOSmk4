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
#ifndef _I386_KOS_KOS_BITS_TYPES_H
#define _I386_KOS_KOS_BITS_TYPES_H 1

#include <__stdinc.h>
#include <bits/types.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#define __SIZEOF_VM_VPAGE_T__   __SIZEOF_POINTER__ /* DEPRECATED; REMOVE ME */
#define __SIZEOF_VM_VIRT_T__    __SIZEOF_POINTER__ /* DEPRECATED; REMOVE ME */
#define __SIZEOF_VM_SPAGE_T__   __SIZEOF_POINTER__ /* DEPRECATED; REMOVE ME */
#define __SIZEOF_PAGEPTR_T__    __SIZEOF_POINTER__
#define __SIZEOF_VM_PHYS_T__    8

#ifdef __CC__
__SYSDECL_BEGIN


#ifndef ____le8_defined
#define ____le8_defined 1
#ifdef __INTELLISENSE__
#include <hybrid/__byteorder.h>
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__, __UINT8_TYPE__> __le8;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__, __UINT8_TYPE__> __be8;
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__, __UINT16_TYPE__> __le16;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__, __UINT16_TYPE__> __be16;
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__, __UINT32_TYPE__> __le32;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__, __UINT32_TYPE__> __be32;
#ifdef __UINT64_TYPE__
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__, __UINT64_TYPE__> __le64;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__, __UINT64_TYPE__> __be64;
#endif /* __UINT64_TYPE__ */
#else /* __INTELLISENSE__ */

#ifndef __bitwise__
#ifdef __CHECKER__
#define __bitwise__ __attribute__((bitwise))
#else /* __CHECKER__ */
#define __bitwise__
#endif /* !__CHECKER__ */
#endif /* !__bitwise__ */

#ifndef __bitwise
#ifdef __CHECK_ENDIAN__
#define __bitwise __bitwise__
#else /* __CHECK_ENDIAN__ */
#define __bitwise
#endif /* !__CHECK_ENDIAN__ */
#endif /* !__bitwise */

typedef __bitwise __UINT8_TYPE__ __le8;
typedef __bitwise __UINT8_TYPE__ __be8;
typedef __bitwise __UINT16_TYPE__ __le16;
typedef __bitwise __UINT16_TYPE__ __be16;
typedef __bitwise __UINT32_TYPE__ __le32;
typedef __bitwise __UINT32_TYPE__ __be32;
#ifdef __UINT64_TYPE__
typedef __bitwise __UINT64_TYPE__ __le64;
typedef __bitwise __UINT64_TYPE__ __be64;
#endif /* __UINT64_TYPE__ */
#endif /* !__INTELLISENSE__ */
#endif /* !____le8_defined */

#ifdef __KERNEL__
#include <hybrid/__altint.h>
__HYBRID_ALTINT_TYPEDEF(__ULONGPTR_TYPE__, __vm_virt_t, false);  /* A virtual memory pointer. */ /* DEPRECATED; REMOVE ME */
__HYBRID_ALTINT_TYPEDEF(__ULONGPTR_TYPE__, __vm_spage_t, false); /* Swap memory page index (`swap_address / PAGESIZE'). */ /* DEPRECATED; REMOVE ME */
__HYBRID_ALTINT_TYPEDEF(__ULONGPTR_TYPE__, __pageptr_t, false);  /* Physical memory page index (`physical_address / PAGESIZE'). */
__HYBRID_ALTINT_TYPEDEF(__UINT64_TYPE__, __vm_phys_t, false);    /* A physical memory pointer. */ /* TODO: Rename to `__phys_t' */
#else /* __KERNEL__ */
typedef /*VIRT*/ __ULONGPTR_TYPE__ __vm_virt_t;  /* A virtual memory pointer. */ /* DEPRECATED; REMOVE ME */
typedef /*SWAP*/ __ULONGPTR_TYPE__ __vm_spage_t; /* Swap memory page index (`swap_address / PAGESIZE'). */ /* DEPRECATED; REMOVE ME */
typedef /*PHYS*/ __ULONGPTR_TYPE__ __pageptr_t;  /* Physical memory page index (`physical_address / PAGESIZE'). */
typedef /*PHYS*/ __UINT64_TYPE__ __vm_phys_t;  /* A physical memory pointer. */ /* TODO: Rename to `phys_t'; TODO: Move into <kernel/arch/paging.h> */
#endif /* !__KERNEL__ */

#if defined(__KERNEL__)
#include <hybrid/__altint.h>
__HYBRID_ALTINT_TYPEDEF(__UINT64_TYPE__, __vm_vpage64_t, false); /* DEPRECATED; REMOVE ME */
#else
typedef __UINT64_TYPE__ __vm_vpage64_t; /* DEPRECATED; REMOVE ME */
#endif


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_BITS_TYPES_H */
