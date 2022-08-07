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
#ifndef _KOS_KERNEL_ASM_PAGING_H
#define _KOS_KERNEL_ASM_PAGING_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#undef KERNELSPACE_BASE
#undef KERNEL_CORE_BASE

#undef KERNELSPACE_END
#undef KERNELSPACE_LOWMEM
#define KERNELSPACE_HIGHMEM 1

#if __SIZEOF_POINTER__ >= 8
#define USERSPACE_END    __UINT64_C(0x0000800000000000) /* Upper address space limit for user-space (first invalid address) */
#define KERNELSPACE_BASE __UINT64_C(0xffff800000000000) /* Lower address space limit for kernel-space */
#define KERNEL_CORE_BASE __UINT64_C(0xffffffff80000000) /* Load address of the kernel core. (-2GB) */
#else /* __SIZEOF_POINTER__ >= 8 */
#define USERSPACE_END    __UINT32_C(0xc0000000) /* Upper address space limit for user-space */
#define KERNELSPACE_BASE __UINT32_C(0xc0000000) /* lower address space limit for kernel-space */
#define KERNEL_CORE_BASE __UINT32_C(0xc0000000) /* Load address of the kernel core. */
#endif /* __SIZEOF_POINTER__ < 8 */

#endif /* !_KOS_KERNEL_ASM_PAGING_H */
