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
#ifndef _MALLOCA_H
#define _MALLOCA_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <parts/malloca.h>

/* A hybrid between alloca and malloc, using alloca for
 * small allocations, but malloc() for larger ones.
 * NOTE: In all cases, 'afree()' should be used to clean up a
 *       pointer previously allocated using 'amalloc()' and
 *       friends. */

#ifdef __malloca_tryhard_mayfail
#define __MALLOCA_TRYHARD_MAYFAIL 1
#endif /* __malloca_tryhard_mayfail */

#ifdef __INTELLISENSE__
#ifndef __malloca_heap
#define __NO_MALLOCA_HEAP 1
#endif /* !__malloca_heap */
#ifndef __malloca_stack
#define __NO_MALLOCA_STACK 1
#endif /* !__malloca_stack */

__DECL_BEGIN

/* Free a pointer previously allocated by `malloca' and friends */
__ATTR_NONNULL((1)) void (freea)(void *__restrict __ptr);

/* Allocate a malloca-like data block with `NUM_BYTES' bytes */
__ATTR_WUNUSED __ATTR_MALLOC void *(malloca)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(calloca)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(malloca_heap)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(calloca_heap)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(malloca_stack)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(calloca_stack)(__SIZE_TYPE__ __num_bytes);

/* Try hard to allocate memory, always using stack memory when heap allocation fails. */
extern "C++" {
template<class __T> void (malloca_tryhard)(__T *&__result, __SIZE_TYPE__ __num_bytes);
template<class __T> void (calloca_tryhard)(__T *&__result, __SIZE_TYPE__ __num_bytes);
}

__DECL_END

#else /* __INTELLISENSE__ */
#define freea(ptr)                        __freea(ptr)
#define malloca(num_bytes)                __malloca(num_bytes)
#define calloca(num_bytes)                __calloca(num_bytes)
#define malloca_tryhard(result,num_bytes) __malloca_tryhard(result,num_bytes)
#define calloca_tryhard(result,num_bytes) __calloca_tryhard(result,num_bytes)
#ifdef __malloca_heap
#define malloca_heap(num_bytes)           __malloca_heap(num_bytes)
#define calloca_heap(num_bytes)           __calloca_heap(num_bytes)
#else /* __malloca_heap */
#define __NO_MALLOCA_HEAP 1
#define malloca_heap(num_bytes)           __malloca(num_bytes)
#define calloca_heap(num_bytes)           __calloca(num_bytes)
#endif /* !__malloca_heap */
#ifdef __malloca_stack
#define malloca_stack(num_bytes)          __malloca_stack(num_bytes)
#define calloca_stack(num_bytes)          __calloca_stack(num_bytes)
#else /* __malloca_stack */
#define __NO_MALLOCA_STACK 1
#define malloca_stack(num_bytes)          __malloca(num_bytes)
#define calloca_stack(num_bytes)          __calloca(num_bytes)
#endif /* !__malloca_stack */
#endif /* !__INTELLISENSE__ */

#endif /* !_MALLOCA_H */
