/* HASH CRC-32:0x2b5a6e56 */
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
/* (#) Portability: libbsd (/include/bsd/stdlib.h) */
#ifndef _BSD_STDLIB_H
#define _BSD_STDLIB_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <stdlib.h>
#include <features.h>
#include <bits/types.h>
#include <sys/stat.h>
#include <stdint.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __reallocf_defined
#define __reallocf_defined 1
#ifdef __CRT_HAVE_reallocf
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,reallocf,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_realloc)
#include <libc/local/stdlib/reallocf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(reallocf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL reallocf)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocf))(__mallptr, __num_bytes); })
#else /* ... */
#undef __reallocf_defined
#endif /* !... */
#endif /* !__reallocf_defined */
#ifndef __reallocarray_defined
#define __reallocarray_defined 1
#ifdef __CRT_HAVE_reallocarray
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc)
#include <libc/local/malloc/reallocarray.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(reallocarray, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL reallocarray)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); })
#else /* ... */
#undef __reallocarray_defined
#endif /* !... */
#endif /* !__reallocarray_defined */
#ifndef __recallocarray_defined
#define __recallocarray_defined 1
#ifdef __CRT_HAVE_recallocarray
/* Same as `recallocv(mallptr, new_elem_count, elem_size)', but also ensure that
 * when `mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3, 4)),void *,__NOTHROW_NCX,recallocarray,(void *__mallptr, __SIZE_TYPE__ __old_elem_count, __SIZE_TYPE__ __new_elem_count, __SIZE_TYPE__ __elem_size),(__mallptr,__old_elem_count,__new_elem_count,__elem_size))
#elif (defined(__CRT_HAVE_recallocv) || defined(__CRT_HAVE__recalloc) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <libc/local/stdlib/recallocarray.h>
/* Same as `recallocv(mallptr, new_elem_count, elem_size)', but also ensure that
 * when `mallptr != NULL', memory pointed to by the old `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
__NAMESPACE_LOCAL_USING_OR_IMPL(recallocarray, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3, 4)) void *__NOTHROW_NCX(__LIBCCALL recallocarray)(void *__mallptr, __SIZE_TYPE__ __old_elem_count, __SIZE_TYPE__ __new_elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocarray))(__mallptr, __old_elem_count, __new_elem_count, __elem_size); })
#else /* ... */
#undef __recallocarray_defined
#endif /* !... */
#endif /* !__recallocarray_defined */
#ifndef __freezero_defined
#define __freezero_defined 1
#ifdef __CRT_HAVE_freezero
/* Same as `free(mallptr)', but also ensure that the memory region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned to the OS, rather than being left in cache
 * while still containing its previous contents. */
__CDECLARE_VOID(,__NOTHROW_NCX,freezero,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <libc/local/stdlib/freezero.h>
/* Same as `free(mallptr)', but also ensure that the memory region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned to the OS, rather than being left in cache
 * while still containing its previous contents. */
__NAMESPACE_LOCAL_USING_OR_IMPL(freezero, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL freezero)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(freezero))(__mallptr, __num_bytes); })
#else /* ... */
#undef __freezero_defined
#endif /* !... */
#endif /* !__freezero_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_STDLIB_H */
