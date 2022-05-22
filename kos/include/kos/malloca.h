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
#ifndef _KOS_MALLOCA_H
#define _KOS_MALLOCA_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <kos/anno.h>
#include <kos/parts/malloca.h>
#include <parts/malloca.h>

#include <malloca.h>

/* A hybrid between alloca and Malloc, using alloca for
 * small  allocations,  but Malloc()  for  larger ones.
 * NOTE: In all cases, 'freea()' should be used to clean up a
 *       pointer previously allocated  using 'Malloca()'  and
 *       friends. */

#ifdef __INTELLISENSE__
__DECL_BEGIN

extern "C++" {
/* Allocate a malloca-like data block with `num_bytes' bytes */
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(Malloca)(__SIZE_TYPE__ __num_bytes) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(Malloca)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(Calloca)(__SIZE_TYPE__ __num_bytes) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(Calloca)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(MallocaHeap)(__SIZE_TYPE__ __num_bytes) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(MallocaHeap)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(CallocaHeap)(__SIZE_TYPE__ __num_bytes) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(CallocaHeap)(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) __THROWS(E_BADALLOC);
} /* extern "C++" */

__DECL_END

#else /* __INTELLISENSE__ */
#include <hybrid/pp/__va_nargs.h>

#ifdef __HYBRID_PP_VA_OVERLOAD
#define __PRIVATE_Malloca_1(num_bytes)                             __malloca(num_bytes)
#define __PRIVATE_Malloca_2(elem_count, elem_size)                 __malloca((elem_count) * (elem_size))
#define __PRIVATE_Calloca_1(num_bytes)                             __calloca(num_bytes)
#define __PRIVATE_Calloca_2(elem_count, elem_size)                 __calloca((elem_count) * (elem_size))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define Malloca(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_Malloca_, (__VA_ARGS__))(__VA_ARGS__)
#define Calloca(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_Calloca_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define Malloca(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_Malloca_, (args))(args)
#define Calloca(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_Calloca_, (args))(args)
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#else /* __HYBRID_PP_VA_OVERLOAD */
#define Malloca __Malloca
#define Calloca __Calloca
#endif /* !__HYBRID_PP_VA_OVERLOAD */

#ifdef __MallocaHeap
#ifdef __HYBRID_PP_VA_OVERLOAD
#define __PRIVATE_MallocaHeap_1(num_bytes)             __MallocaHeap(num_bytes)
#define __PRIVATE_MallocaHeap_2(elem_count, elem_size) __MallocaHeap((elem_count) * (elem_size))
#define __PRIVATE_CallocaHeap_1(num_bytes)             __CallocaHeap(num_bytes)
#define __PRIVATE_CallocaHeap_2(elem_count, elem_size) __CallocaHeap((elem_count) * (elem_size))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define MallocaHeap(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_MallocaHeap_, (__VA_ARGS__))(__VA_ARGS__)
#define CallocaHeap(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_CallocaHeap_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define MallocaHeap(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_MallocaHeap_, (args))(args)
#define CallocaHeap(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_CallocaHeap_, (args))(args)
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#else /* __HYBRID_PP_VA_OVERLOAD */
#define MallocaHeap __MallocaHeap
#define CallocaHeap __CallocaHeap
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#else /* __MallocaHeap */
#define MallocaHeap Malloca
#define CallocaHeap Calloca
#endif /* !__MallocaHeap */

#endif /* !__INTELLISENSE__ */

#endif /* !_KOS_MALLOCA_H */
