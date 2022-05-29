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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN__ARCHINIT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN__ARCHINIT_H 1

#include <kernel/compiler.h>

#ifdef __CC__
#ifdef CONFIG_BUILDING_KERNEL_CORE
#include <kernel/mman.h>
#include <kernel/paging.h>

DECL_BEGIN

#ifdef CONFIG_USE_RWLOCK_FOR_MMAN
#define _MMAN_KERNEL_INIT_MM_LOCK ATOMIC_RWLOCK_INIT
#else /* CONFIG_USE_RWLOCK_FOR_MMAN */
#define _MMAN_KERNEL_INIT_MM_LOCK ATOMIC_LOCK_INIT
#endif /* !CONFIG_USE_RWLOCK_FOR_MMAN */

#ifndef CONFIG_NO_SMP
#define _MMAN_KERNEL_INIT_MM_THREADSLOCK .mm_threadslock = ATOMIC_LOCK_INIT,
#else /* !CONFIG_NO_SMP */
#define _MMAN_KERNEL_INIT_MM_THREADSLOCK /* nothing */
#endif /* CONFIG_NO_SMP */

/* Field initializers for the  kernel mman (but excluding  `mm_pagedir')
 * This macro is used by the arch-specific initializer for `mman_kernel' */
#define _MMAN_KERNEL_INIT                                                                    \
	.mm_refcnt      = 4, /* mman_kernel, this_mman@{boottask,bootidle,asyncwork} */          \
	.mm_weakrefcnt  = 1,                                                                     \
	.mm_lock        = _MMAN_KERNEL_INIT_MM_LOCK,                                             \
	_MMAN_INIT_WRLOCKPC_                                                                     \
	.mm_mappings    = __NULLPTR, /* XXX: Statically initialize the initial mappings tree? */ \
	.mm_pagedir_p   = pagedir_kernel_phys,                                                   \
	.mm_writable    = LIST_HEAD_INITIALIZER(&mman_kernel.mm_writable),                       \
	.mm_threads     = LIST_HEAD_INITIALIZER(&mman_kernel.mm_threads),                        \
	_MMAN_KERNEL_INIT_MM_THREADSLOCK

DECL_END
#endif /* CONFIG_BUILDING_KERNEL_CORE */
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN__ARCHINIT_H */
