/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_UNMAP_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_UNMAP_C 1
#define __WANT_MNODE__mn_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifndef __INTELLISENSE__
#define DEFINE_mman_unmap
#include "mman-unmap.c.inl"
#define DEFINE_mman_protect
#include "mman-unmap.c.inl"
#define DEFINE_mman_madvise
#include "mman-unmap.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_UNMAP_C */
