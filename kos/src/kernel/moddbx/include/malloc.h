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
#ifndef GUARD_MODDBX_INCLUDE_MALLOC_H
#define GUARD_MODDBX_INCLUDE_MALLOC_H 1

/* DeBug eXtensions: Malloc function.
 *
 * Behaves  just like the normal kmalloc, except that this one can only be used
 * from within the debugger, and all memory allocated is forcibly released when
 * the debugger is reset/exited. Additionally, none of these functions make use
 * of exceptions, but always return `NULL' if an allocation failed.
 */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

#include <kernel/heap.h>
#include <kernel/types.h>

#include <hybrid/typecore.h>

DECL_BEGIN

#if defined(__clang_tidy__) && !defined(NO_INSTRUMENT_KMALLOC)
#define dbx_malloc(num_bytes)       __builtin_malloc(num_bytes)
#define dbx_realloc(ptr, num_bytes) __builtin_realloc(ptr, num_bytes)
#define dbx_malloc_usable_size(ptr) __builtin_malloc_usable_size(ptr)
#define dbx_free(ptr)               __builtin_free(ptr)
#else /* __clang_tidy__ && !NO_INSTRUMENT_KMALLOC */
/* High-level malloc functions. */
FUNDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) ATTR_ASSUME_ALIGNED(__SIZEOF_POINTER__) void *
NOTHROW(FCALL dbx_malloc)(size_t num_bytes);
FUNDEF WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_ASSUME_ALIGNED(__SIZEOF_POINTER__) void *
NOTHROW(FCALL dbx_realloc)(void *ptr, size_t num_bytes);
FUNDEF ATTR_PURE WUNUSED size_t NOTHROW(FCALL dbx_malloc_usable_size)(void *ptr);
FUNDEF void NOTHROW(FCALL dbx_free)(void *ptr);
#endif /* !__clang_tidy__ || NO_INSTRUMENT_KMALLOC */

/* Low-level heap alloc/free functions. */
FUNDEF WUNUSED heapptr_t NOTHROW(FCALL dbx_heap_alloc)(size_t num_bytes);
FUNDEF void NOTHROW(FCALL dbx_heap_free)(void *base, size_t num_bytes);
/* Try  to allocate at least `num_bytes' at `addr',
 * and return the actual amount that was allocated. */
FUNDEF WUNUSED size_t NOTHROW(FCALL dbx_heap_allocat)(void *addr, size_t num_bytes);

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_MALLOC_H */
