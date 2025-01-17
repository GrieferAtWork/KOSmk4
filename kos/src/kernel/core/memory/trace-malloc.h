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
#ifndef GUARD_KERNEL_SRC_MEMORY_TRACE_MALLOC_H
#define GUARD_KERNEL_SRC_MEMORY_TRACE_MALLOC_H 1

#include <kernel/compiler.h>
#include <kernel/malloc-defs.h>

/*[[[config CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK: int = 4
 * The minimum amount of traceback entries that MALL
 * should attempt to include in debug information of
 * allocated pointers.
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_TRACE_MALLOC_MIN_TRACEBACK
#undef CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK
#define CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK 0
#elif !defined(CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK)
#define CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK 4
#elif (CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK + 0) <= 0
#undef CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK
#define CONFIG_NO_KERNEL_TRACE_MALLOC_MIN_TRACEBACK
#define CONFIG_KERNEL_TRACE_MALLOC_MIN_TRACEBACK 0
#endif /* ... */
/*[[[end]]]*/

/*[[[config CONFIG_KERNEL_MALL_HEAD_PATTERN! = 0x33333333
 * DWORD-pattern used to fill the head of a mall pointer
 * ]]]*/
#ifndef CONFIG_KERNEL_MALL_HEAD_PATTERN
#define CONFIG_KERNEL_MALL_HEAD_PATTERN 0x33333333
#endif /* !CONFIG_KERNEL_MALL_HEAD_PATTERN */
/*[[[end]]]*/

/*[[[config CONFIG_KERNEL_MALL_TAIL_PATTERN! = 0x77777777
 * DWORD-pattern used to fill the tail of a mall pointer
 * ]]]*/
#ifndef CONFIG_KERNEL_MALL_TAIL_PATTERN
#define CONFIG_KERNEL_MALL_TAIL_PATTERN 0x77777777
#endif /* !CONFIG_KERNEL_MALL_TAIL_PATTERN */
/*[[[end]]]*/

/*[[[config CONFIG_KERNEL_MALL_HEAD_SIZE: int = HEAP_ALIGNMENT
 * Size of the head-area of a mall pointer
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_MALL_HEAD_SIZE
#undef CONFIG_KERNEL_MALL_HEAD_SIZE
#define CONFIG_KERNEL_MALL_HEAD_SIZE 0
#elif !defined(CONFIG_KERNEL_MALL_HEAD_SIZE)
#define CONFIG_KERNEL_MALL_HEAD_SIZE HEAP_ALIGNMENT
#elif (CONFIG_KERNEL_MALL_HEAD_SIZE + 0) <= 0
#undef CONFIG_KERNEL_MALL_HEAD_SIZE
#define CONFIG_NO_KERNEL_MALL_HEAD_SIZE
#define CONFIG_KERNEL_MALL_HEAD_SIZE 0
#endif /* ... */
/*[[[end]]]*/

/*[[[config CONFIG_KERNEL_MALL_TAIL_SIZE: int = HEAP_ALIGNMENT
 * Size of the tail-area of a mall pointer
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_MALL_TAIL_SIZE
#undef CONFIG_KERNEL_MALL_TAIL_SIZE
#define CONFIG_KERNEL_MALL_TAIL_SIZE 0
#elif !defined(CONFIG_KERNEL_MALL_TAIL_SIZE)
#define CONFIG_KERNEL_MALL_TAIL_SIZE HEAP_ALIGNMENT
#elif (CONFIG_KERNEL_MALL_TAIL_SIZE + 0) <= 0
#undef CONFIG_KERNEL_MALL_TAIL_SIZE
#define CONFIG_NO_KERNEL_MALL_TAIL_SIZE
#define CONFIG_KERNEL_MALL_TAIL_SIZE 0
#endif /* ... */
/*[[[end]]]*/

#endif /* !GUARD_KERNEL_SRC_MEMORY_TRACE_MALLOC_H */
