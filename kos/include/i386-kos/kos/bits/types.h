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
#ifndef _I386_KOS_KOS_BITS_TYPES_H
#define _I386_KOS_KOS_BITS_TYPES_H 1

#include <__stdinc.h>
#include <bits/types.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#define __SIZEOF_VM_VPAGE_T__   __SIZEOF_POINTER__ /* DEPRECATED; REMOVE ME */
#define __SIZEOF_VM_PPAGE_T__   __SIZEOF_POINTER__ /* DEPRECATED; REMOVE ME */
#define __SIZEOF_VM_SPAGE_T__   __SIZEOF_POINTER__ /* DEPRECATED; REMOVE ME */
#define __SIZEOF_VM_VIRT_T__    __SIZEOF_POINTER__ /* DEPRECATED; REMOVE ME */
#define __SIZEOF_VM_PHYS_T__    8

#ifdef __CC__
__SYSDECL_BEGIN


#ifndef ____le8_defined
#define ____le8_defined 1
#ifdef __INTELLISENSE__
#include <hybrid/__byteorder.h>
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__,__UINT8_TYPE__> __le8;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__,__UINT8_TYPE__> __be8;
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__,__UINT16_TYPE__> __le16;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__,__UINT16_TYPE__> __be16;
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__,__UINT32_TYPE__> __le32;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__,__UINT32_TYPE__> __be32;
#ifdef __UINT64_TYPE__
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__,__UINT64_TYPE__> __le64;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__,__UINT64_TYPE__> __be64;
#endif /* __UINT64_TYPE__ */
#else

#ifndef __bitwise__
#ifdef __CHECKER__
#   define __bitwise__ __attribute__((bitwise))
#else /* __CHECKER__ */
#   define __bitwise__
#endif /* !__CHECKER__ */
#endif /* !__bitwise__ */

#ifndef __bitwise
#ifdef __CHECK_ENDIAN__
#   define __bitwise __bitwise__
#else /* __CHECK_ENDIAN__ */
#   define __bitwise
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
#endif
#endif /* !____le8_defined */
#ifdef __KERNEL__
#include <hybrid/__altint.h>
__HYBRID_ALTINT_TYPEDEF(__ULONGPTR_TYPE__, __vm_vpage_t, false); /* Virtual memory page index (`virtual_address / PAGESIZE'). */ /* DEPRECATED; REMOVE ME */
__HYBRID_ALTINT_TYPEDEF(__ULONGPTR_TYPE__, __pageptr_t, false);  /* Physical memory page index (`physical_address / PAGESIZE'). */
__HYBRID_ALTINT_TYPEDEF(__ULONGPTR_TYPE__, __vm_spage_t, false); /* Swap memory page index (`swap_address / PAGESIZE'). */ /* DEPRECATED; REMOVE ME */
__HYBRID_ALTINT_TYPEDEF(__ULONGPTR_TYPE__, __vm_virt_t, false);  /* A virtual memory pointer. */ /* DEPRECATED; REMOVE ME */
__HYBRID_ALTINT_TYPEDEF(__UINT64_TYPE__, __vm_phys_t, false);    /* A physical memory pointer. */ /* TODO: Rename to `__phys_t' */
#else /* __KERNEL__ */
typedef /*VIRT*/ __ULONGPTR_TYPE__ __vm_vpage_t; /* Virtual memory page index (`virtual_address / PAGESIZE'). */ /* DEPRECATED; REMOVE ME */
typedef /*PHYS*/ __ULONGPTR_TYPE__ __pageptr_t;  /* Physical memory page index (`physical_address / PAGESIZE'). */
typedef /*SWAP*/ __ULONGPTR_TYPE__ __vm_spage_t; /* Swap memory page index (`swap_address / PAGESIZE'). */ /* DEPRECATED; REMOVE ME */
typedef /*VIRT*/ __ULONGPTR_TYPE__ __vm_virt_t;  /* A virtual memory pointer. */ /* DEPRECATED; REMOVE ME */
typedef /*PHYS*/ __UINT64_TYPE__   __vm_phys_t;  /* A physical memory pointer. */ /* TODO: Rename to `phys_t'; TODO: Move into <kernel/arch/paging.h> */
#endif /* !__KERNEL__ */

#if __SIZEOF_LONG__ >= 8
typedef __vm_vpage_t __vm_vpage64_t; /* DEPRECATED; REMOVE ME */
#elif defined(__KERNEL__)
#include <hybrid/__altint.h>
__HYBRID_ALTINT_TYPEDEF(__UINT64_TYPE__, __vm_vpage64_t, false); /* DEPRECATED; REMOVE ME */
#else
typedef __UINT64_TYPE__ __vm_vpage64_t; /* DEPRECATED; REMOVE ME */
#endif


__SYSDECL_END
#endif /* __CC__ */


/* TODO: Re-write the vpage system to work more efficiently in regards
 *       to the whole pointer-sign-extension thingy on x86_64.
 * Also: On x86_64 we're actually dealing with:
 *       36-bit vpage indices (36 == X86_64_ADDRBUS_CANONBITS - PAGESHIFT):
 *       >> #define __VM_VPAGE_MAX __CCAST(__vm_vpage_t)__UINT64_C(0xfffffffff)
 *       40-bit ppage indices (40 == popcount(P64_PAGE_FADDR_4KIB)):
 *       >> #define __VM_PPAGE_MAX __CCAST(__vm_vpage_t)__UINT64_C(0xffffffffff)
 */

#ifdef __x86_64__
#define __VM_VPAGE_MAX __CCAST(__vm_vpage_t)__UINT64_C(0xfffffffffffff) /* (4096Tib / 4096) - 1 */ /* DEPRECATED; REMOVE ME */
#define __VM_PPAGE_MAX __CCAST(__pageptr_t)__UINT64_C(0xfffffffffffff) /* (4096Tib / 4096) - 1 */ /* DEPRECATED; REMOVE ME */
#else /* __x86_64__ */
#define __VM_VPAGE_MAX __CCAST(__vm_vpage_t)0xfffff  /* (4Gib / 4096) - 1 */ /* DEPRECATED; REMOVE ME */
#define __VM_PPAGE_MAX __CCAST(__pageptr_t)0xffffff /* (64Gib / 4096) - 1 */ /* DEPRECATED; REMOVE ME */
#endif /* !__x86_64__ */



#ifdef __INTELLISENSE__
namespace __intern {extern "C++" {
__UINTPTR_TYPE__ ____intellisense_vm_page2addr(__UINTPTR_TYPE__ __x);
__vm_virt_t ____intellisense_vm_page2addr(__vm_vpage_t __x);
__vm_phys_t ____intellisense_vm_ppage2addr(__pageptr_t __x);
__UINTPTR_TYPE__ ____intellisense_vm_addr2page(__UINTPTR_TYPE__ __x);
__vm_vpage_t ____intellisense_vm_addr2page(__vm_virt_t __x);
__pageptr_t ____intellisense_vm_addr2page(__vm_phys_t __x);
#if __SIZEOF_POINTER__ != 8
__INTPTR_TYPE__ ____intellisense_vm_addr2page(__INTPTR_TYPE__ __x);
__INT64_TYPE__ ____intellisense_vm_addr2page(__INT64_TYPE__ __x);
__UINT64_TYPE__ ____intellisense_vm_addr2page(__UINT64_TYPE__ __x);
#endif /* __SIZEOF_POINTER__ != 8 */
}}
#define __VM_PPAGE2ADDR  __intern::____intellisense_vm_ppage2addr /* DEPRECATED; REMOVE ME */
#define __VM_PAGE2ADDR   __intern::____intellisense_vm_page2addr /* DEPRECATED; REMOVE ME */
#define __VM_ADDR2PAGE   __intern::____intellisense_vm_addr2page /* DEPRECATED; REMOVE ME */
#else
#define __VM_PPAGE2ADDR(page)   (__CCAST(__vm_phys_t)(page)*4096) /* DEPRECATED; REMOVE ME */
#define __VM_PAGE2ADDR(page)    ((page)*4096) /* DEPRECATED; REMOVE ME */
#define __VM_ADDR2PAGE(addr)    ((addr)/4096) /* DEPRECATED; REMOVE ME */
#endif

#endif /* !_I386_KOS_KOS_BITS_TYPES_H */
