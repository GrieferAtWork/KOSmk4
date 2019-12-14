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
#ifndef _KOS_KERNEL_TYPES_H
#define _KOS_KERNEL_TYPES_H 1

#include <hybrid/compiler.h>
#include <bits/types.h>
#include <kos/types.h>
#include <kos/bits/types.h>

DECL_BEGIN

#if __SIZEOF_POINTER__ == 4
#define BITS_PER_POINTER  32
#elif __SIZEOF_POINTER__ == 8
#define BITS_PER_POINTER  64
#elif __SIZEOF_POINTER__ == 2
#define BITS_PER_POINTER  16
#elif __SIZEOF_POINTER__ == 1
#define BITS_PER_POINTER  8
#else
#error "Invalid `__SIZEOF_POINTER__'"
#endif

#ifdef __CC__

#ifndef __s8_defined
#define __s8_defined 1
typedef __s8 s8;
typedef __u8 u8;
typedef __s16 s16;
typedef __u16 u16;
typedef __s32 s32;
typedef __u32 u32;
#ifdef __INT64_TYPE__
typedef __s64 s64;
#endif /* __INT64_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __u64 u64;
#endif /* __UINT64_TYPE__ */
#endif /* !__s8_defined */

#ifndef __le8_defined
#define __le8_defined 1
typedef __le8 le8;
typedef __be8 be8;
typedef __be16 be16;
typedef __le16 le16;
typedef __be32 be32;
typedef __le32 le32;
#ifdef __UINT64_TYPE__
typedef __be64 be64;
typedef __le64 le64;
#endif /* __UINT64_TYPE__ */
#endif /* !__le8_defined */

#ifndef __refcnt_t_defined
#define __refcnt_t_defined 1
typedef __uintptr_t refcnt_t;
#endif /* !__refcnt_t_defined */

#ifndef __pageptr_t_defined
#define __pageptr_t_defined 1
typedef __pageptr_t pageptr_t; /* Physical memory page index (`physical_address / PAGESIZE'). */
#endif /* !__pageptr_t_defined */

typedef /*VIRT*/ __vm_vpage_t   vm_vpage_t;   /* Virtual memory page index (`virtual_address / getpagesize()'). */ /* DEPRECATED; REMOVE ME */
typedef /*VIRT*/ __vm_vpage64_t vm_vpage64_t; /* Virtual memory page index (with at least 64 bits). */ /* DEPRECATED; REMOVE ME */
typedef /*PHYS*/ __vm_spage_t   vm_spage_t;   /* Swap memory page index (`swap_address / getpagesize()'). */ /* DEPRECATED; REMOVE ME */
typedef /*VIRT*/ __vm_virt_t    vm_virt_t;    /* A virtual memory pointer. */ /* DEPRECATED; REMOVE ME */
typedef /*PHYS*/ __vm_phys_t    vm_phys_t;    /* A physical memory pointer. */ /* TODO: Rename to `phys_t'; TODO: Move into <kernel/arch/paging.h> */

#if __SIZEOF_VM_PHYS_T__ >= 8
#define FORMAT_VM_PHYS_T  "%I64p" /* DEPRECATED; REMOVE ME */
#else
#define FORMAT_VM_PHYS_T  "%p" /* DEPRECATED; REMOVE ME */
#endif

#if __SIZEOF_PAGEPTR_T__ >= 8
#define FORMAT_PAGEPTR_T "%I64p" /* DEPRECATED; REMOVE ME */
#else
#define FORMAT_PAGEPTR_T "%p" /* DEPRECATED; REMOVE ME */
#endif

#ifndef VM_VPAGE_MAX
#define VM_VPAGE_MAX       __VM_VPAGE_MAX /* DEPRECATED; REMOVE ME */
#define VM_PPAGE_MAX       __VM_PPAGE_MAX /* DEPRECATED; REMOVE ME */
#endif /* !VM_VPAGE_MAX */
#ifndef VM_PAGE2ADDR
#define VM_PAGE2ADDR(page)  __VM_PAGE2ADDR(page) /* DEPRECATED; REMOVE ME */
#define VM_ADDR2PAGE(addr)  __VM_ADDR2PAGE(addr) /* DEPRECATED; REMOVE ME */
#endif /* !VM_PAGE2ADDR */

#endif /* __CC__ */

DECL_END

#endif /* !_KOS_KERNEL_TYPES_H */
