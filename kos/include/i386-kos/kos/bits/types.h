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

#define __SIZEOF_VM_VPAGE_T__   __SIZEOF_POINTER__
#define __SIZEOF_VM_PPAGE_T__   __SIZEOF_POINTER__
#define __SIZEOF_VM_SPAGE_T__   __SIZEOF_POINTER__
#define __SIZEOF_VM_VIRT_T__    __SIZEOF_POINTER__
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
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef /*VIRT*/ ALTERNATIVE_TYPE(__ULONGPTR_TYPE__) __vm_vpage_t; /* Virtual memory page index (`virtual_address / getpagesize()'). */
typedef /*PHYS*/ ALTERNATIVE_TYPE(__ULONGPTR_TYPE__) __vm_ppage_t; /* Physical memory page index (`physical_address / getpagesize()'). */
typedef /*SWAP*/ ALTERNATIVE_TYPE(__ULONGPTR_TYPE__) __vm_spage_t; /* Swap memory page index (`swap_address / getpagesize()'). */
typedef /*VIRT*/ ALTERNATIVE_TYPE(__ULONGPTR_TYPE__) __vm_virt_t;  /* A virtual memory pointer. */
typedef /*PHYS*/ ALTERNATIVE_TYPE(__UINT64_TYPE__)   __vm_phys_t;  /* A physical memory pointer. */
#else
typedef /*VIRT*/ __ULONGPTR_TYPE__ __vm_vpage_t;                   /* Virtual memory page index (`virtual_address / getpagesize()'). */
typedef /*PHYS*/ __ULONGPTR_TYPE__ __vm_ppage_t;                   /* Physical memory page index (`physical_address / getpagesize()'). */
typedef /*SWAP*/ __ULONGPTR_TYPE__ __vm_spage_t;                   /* Swap memory page index (`swap_address / getpagesize()'). */
typedef /*VIRT*/ __ULONGPTR_TYPE__ __vm_virt_t;                    /* A virtual memory pointer. */
typedef /*PHYS*/ __UINT64_TYPE__   __vm_phys_t;                    /* A physical memory pointer. */
#endif

#if __SIZEOF_LONG__ >= 8
typedef __vm_vpage_t __vm_vpage64_t;
#elif defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__UINT64_TYPE__) __vm_vpage64_t;
#else
typedef __UINT64_TYPE__ __vm_vpage64_t;
#endif


__SYSDECL_END
#endif /* __CC__ */


#ifdef __x86_64__
#define __VM_VPAGE_MAX __CCAST(__vm_vpage_t)__UINT64_C(0xfffffffffffff) /* (4096Tib / 4096) - 1 */
#define __VM_PPAGE_MAX __CCAST(__vm_ppage_t)__UINT64_C(0xfffffffffffff) /* (4096Tib / 4096) - 1 */
#else /* __x86_64__ */
#define __VM_VPAGE_MAX __CCAST(__vm_vpage_t)0xfffff  /* (4Gib / 4096) - 1 */
#define __VM_PPAGE_MAX __CCAST(__vm_ppage_t)0xffffff /* (64Gib / 4096) - 1 */
#endif /* !__x86_64__ */



#ifdef __INTELLISENSE__
namespace __intern {extern "C++" {
__UINTPTR_TYPE__ ____intellisense_vm_page2addr(__UINTPTR_TYPE__ __x);
__vm_virt_t ____intellisense_vm_page2addr(__vm_vpage_t __x);
__vm_phys_t ____intellisense_vm_ppage2addr(__vm_ppage_t __x);
__UINTPTR_TYPE__ ____intellisense_vm_addr2page(__UINTPTR_TYPE__ __x);
__vm_vpage_t ____intellisense_vm_addr2page(__vm_virt_t __x);
__vm_ppage_t ____intellisense_vm_addr2page(__vm_phys_t __x);
#if __SIZEOF_POINTER__ != 8
__INTPTR_TYPE__ ____intellisense_vm_addr2page(__INTPTR_TYPE__ __x);
__INT64_TYPE__ ____intellisense_vm_addr2page(__INT64_TYPE__ __x);
__UINT64_TYPE__ ____intellisense_vm_addr2page(__UINT64_TYPE__ __x);
#endif /* __SIZEOF_POINTER__ != 8 */
}}
#define __VM_PPAGE2ADDR  __intern::____intellisense_vm_ppage2addr
#define __VM_PAGE2ADDR   __intern::____intellisense_vm_page2addr
#define __VM_ADDR2PAGE   __intern::____intellisense_vm_addr2page
#else
#define __VM_PPAGE2ADDR(page)   (__CCAST(__vm_phys_t)(page)*4096)
#define __VM_PAGE2ADDR(page)    ((page)*4096)
#define __VM_ADDR2PAGE(addr)    ((addr)/4096)
#endif

#endif /* !_I386_KOS_KOS_BITS_TYPES_H */
