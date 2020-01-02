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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ARCH_PAGING_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ARCH_PAGING_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <asm/pagesize.h>
#include <kos/kernel/paging.h>

#undef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT
#undef CONFIG_HAVE_PAGEDIR_CHANGED
#undef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
#define CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE 1
#undef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT
#undef CONFIG_HAVE_PAGEDIR_CHANGED
#undef CONFIG_HAVE_PAGEDIR_UNWRITE
#undef CONFIG_PAGEDIR_GETSET_USES_POINTER
#undef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_GETSET

DECL_BEGIN

#ifndef PAGEDIR_MAPHINT_ALIGNMENT
#define PAGEDIR_MAPHINT_ALIGNMENT  8 /* Guess... */
#endif /* !PAGEDIR_MAPHINT_ALIGNMENT */

#ifdef __CC__
typedef struct ATTR_ALIGNED(__ARCH_PAGESIZE) {
	byte_t __pd_data[__ARCH_PAGESIZE];
} pagedir_t;
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ARCH_PAGING_H */
