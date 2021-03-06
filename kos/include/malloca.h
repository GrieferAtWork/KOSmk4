/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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
 * small  allocations,  but malloc()  for  larger ones.
 * NOTE: In all cases, 'afree()' should be used to clean up a
 *       pointer previously allocated  using 'amalloc()'  and
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

extern "C++" {

/* Allocate a malloca-like data block with `num_bytes' bytes */
__ATTR_WUNUSED __ATTR_MALLOC void *(malloca)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(malloca)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size);
__ATTR_WUNUSED __ATTR_MALLOC void *(calloca)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(calloca)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size);
__ATTR_WUNUSED __ATTR_MALLOC void *(malloca_heap)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(malloca_heap)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size);
__ATTR_WUNUSED __ATTR_MALLOC void *(calloca_heap)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(calloca_heap)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size);
__ATTR_WUNUSED __ATTR_MALLOC void *(malloca_stack)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(malloca_stack)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size);
__ATTR_WUNUSED __ATTR_MALLOC void *(calloca_stack)(__SIZE_TYPE__ __num_bytes);
__ATTR_WUNUSED __ATTR_MALLOC void *(calloca_stack)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size);

/* Try hard to allocate memory, always using stack memory when heap allocation fails. */
template<class __T> void (malloca_tryhard)(__T *&__result, __SIZE_TYPE__ __num_bytes);
template<class __T> void (calloca_tryhard)(__T *&__result, __SIZE_TYPE__ __num_bytes);
} /* extern "C++" */

__DECL_END

#else /* __INTELLISENSE__ */
#include <hybrid/pp/__va_nargs.h>

#define __PRIVATE_malloca_1(num_bytes)                             __malloca(num_bytes)
#define __PRIVATE_malloca_2(elem_count, elem_size)                 __malloca((elem_count) * (elem_size))
#define __PRIVATE_calloca_1(num_bytes)                             __calloca(num_bytes)
#define __PRIVATE_calloca_2(elem_count, elem_size)                 __calloca((elem_count) * (elem_size))
#define __PRIVATE_malloca_tryhard_2(result, num_bytes)             __malloca_tryhard(result, num_bytes)
#define __PRIVATE_malloca_tryhard_3(result, elem_count, elem_size) __malloca_tryhard(result, (elem_count) * (elem_size))
#define __PRIVATE_calloca_tryhard_2(result, num_bytes)             __calloca_tryhard(result, num_bytes)
#define __PRIVATE_calloca_tryhard_3(result, elem_count, elem_size) __calloca_tryhard(result, (elem_count) * (elem_size))

#define freea(ptr)           __freea(ptr)
#define malloca(...)         __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloca_, (__VA_ARGS__))(__VA_ARGS__)
#define calloca(...)         __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloca_, (__VA_ARGS__))(__VA_ARGS__)
#define malloca_tryhard(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloca_tryhard_, (__VA_ARGS__))(__VA_ARGS__)
#define calloca_tryhard(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloca_tryhard_, (__VA_ARGS__))(__VA_ARGS__)

#ifdef __malloca_heap
#define __PRIVATE_malloca_heap_1(num_bytes)             __malloca_heap(num_bytes)
#define __PRIVATE_malloca_heap_2(elem_count, elem_size) __malloca_heap((elem_count) * (elem_size))
#define __PRIVATE_calloca_heap_1(num_bytes)             __calloca_heap(num_bytes)
#define __PRIVATE_calloca_heap_2(elem_count, elem_size) __calloca_heap((elem_count) * (elem_size))
#define malloca_heap(num_bytes) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloca_heap_, (__VA_ARGS__))(__VA_ARGS__)
#define calloca_heap(num_bytes) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloca_heap_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __malloca_heap */
#define __NO_MALLOCA_HEAP 1
#define malloca_heap      malloca
#define calloca_heap      calloca
#endif /* !__malloca_heap */

#ifdef __malloca_stack
#define __PRIVATE_malloca_stack_1(num_bytes)             __malloca_stack(num_bytes)
#define __PRIVATE_malloca_stack_2(elem_count, elem_size) __malloca_stack((elem_count) * (elem_size))
#define __PRIVATE_calloca_stack_1(num_bytes)             __calloca_stack(num_bytes)
#define __PRIVATE_calloca_stack_2(elem_count, elem_size) __calloca_stack((elem_count) * (elem_size))
#define malloca_stack(num_bytes) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloca_stack_, (__VA_ARGS__))(__VA_ARGS__)
#define calloca_stack(num_bytes) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloca_stack_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __malloca_stack */
#define __NO_MALLOCA_STACK 1
#define malloca_stack      malloca
#define calloca_stack      calloca
#endif /* !__malloca_stack */
#endif /* !__INTELLISENSE__ */

#endif /* !_MALLOCA_H */
