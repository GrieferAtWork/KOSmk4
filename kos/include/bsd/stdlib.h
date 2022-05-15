/* HASH CRC-32:0xf3317d87 */
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
/* (#) Portability: libbsd  (/include/bsd/stdlib.h) */
/* (#) Portability: libc4/5 (/include/bsd/stdlib.h) */
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
#include <kos/anno.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if !defined(__dehumanize_number_defined) && defined(__CRT_HAVE_dehumanize_number)
#define __dehumanize_number_defined
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
__CDECLARE(,int,__NOTHROW_NCX,dehumanize_number,(char const *__str, __INT64_TYPE__ *__size),(__str,__size))
#endif /* !__dehumanize_number_defined && __CRT_HAVE_dehumanize_number */
#ifndef __getprogname_defined
#define __getprogname_defined
#ifdef __CRT_HAVE_getprogname
/* >> getprogname(3), setprogname(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,getprogname,(void),())
#else /* __CRT_HAVE_getprogname */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_short_name
#include <libc/local/stdlib/getprogname.h>
/* >> getprogname(3), setprogname(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getprogname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL getprogname)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getprogname))(); })
#else /* __LOCAL_program_invocation_short_name */
#undef __getprogname_defined
#endif /* !__LOCAL_program_invocation_short_name */
#endif /* !__CRT_HAVE_getprogname */
#endif /* !__getprogname_defined */
#ifndef __setprogname_defined
#define __setprogname_defined
#ifdef __CRT_HAVE_setprogname
/* >> getprogname(3), setprogname(3) */
__CDECLARE_VOID(,__NOTHROW_NCX,setprogname,(char const *__name),(__name))
#else /* __CRT_HAVE_setprogname */
#include <libc/template/program_invocation_name.h>
#ifdef __LOCAL_program_invocation_short_name_p
#include <libc/local/stdlib/setprogname.h>
/* >> getprogname(3), setprogname(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(setprogname, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL setprogname)(char const *__name) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setprogname))(__name); })
#else /* __LOCAL_program_invocation_short_name_p */
#undef __setprogname_defined
#endif /* !__LOCAL_program_invocation_short_name_p */
#endif /* !__CRT_HAVE_setprogname */
#endif /* !__setprogname_defined */
#ifndef __heapsort_defined
#define __heapsort_defined
#ifdef __CRT_HAVE_heapsort
__CDECLARE(__ATTR_NONNULL((1, 4)),int,__THROWING,heapsort,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__pbase,__item_count,__item_size,__compar))
#else /* __CRT_HAVE_heapsort */
#include <libc/local/stdlib/heapsort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(heapsort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) int (__LIBCCALL heapsort)(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(heapsort))(__pbase, __item_count, __item_size, __compar); })
#endif /* !__CRT_HAVE_heapsort */
#endif /* !__heapsort_defined */
#ifndef __mergesort_defined
#define __mergesort_defined
#ifdef __CRT_HAVE_mergesort
__CDECLARE(__ATTR_NONNULL((1, 4)),int,__THROWING,mergesort,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),(__pbase,__item_count,__item_size,__compar))
#else /* __CRT_HAVE_mergesort */
#include <libc/local/stdlib/mergesort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mergesort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) int (__LIBCCALL mergesort)(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mergesort))(__pbase, __item_count, __item_size, __compar); })
#endif /* !__CRT_HAVE_mergesort */
#endif /* !__mergesort_defined */
#if !defined(__radixsort_defined) && defined(__CRT_HAVE_radixsort)
#define __radixsort_defined
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,radixsort,(unsigned char const **__base, int __item_count, unsigned char const *__table, unsigned __endbyte),(__base,__item_count,__table,__endbyte))
#endif /* !__radixsort_defined && __CRT_HAVE_radixsort */
#if !defined(__sradixsort_defined) && defined(__CRT_HAVE_sradixsort)
#define __sradixsort_defined
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sradixsort,(unsigned char const **__base, int __item_count, unsigned char const *__table, unsigned __endbyte),(__base,__item_count,__table,__endbyte))
#endif /* !__sradixsort_defined && __CRT_HAVE_sradixsort */
#ifndef __reallocf_defined
#define __reallocf_defined
#ifdef __CRT_HAVE_reallocf
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,reallocf,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/stdlib/reallocf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(reallocf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL reallocf)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocf))(__mallptr, __num_bytes); })
#else /* ... */
#undef __reallocf_defined
#endif /* !... */
#endif /* !__reallocf_defined */
#ifndef __reallocarray_defined
#define __reallocarray_defined
#ifdef __CRT_HAVE_reallocarray
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_reallocarr)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarr,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/malloc/reallocarray.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(reallocarray, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL reallocarray)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); })
#else /* ... */
#undef __reallocarray_defined
#endif /* !... */
#endif /* !__reallocarray_defined */
#ifndef __recallocarray_defined
#define __recallocarray_defined
#ifdef __CRT_HAVE_recallocarray
/* >> recallocarray(3)
 * Same   as    `recallocv(mallptr, new_elem_count, elem_size)',   but    also   ensure    that
 * when `mallptr != NULL', memory pointed to by the old  `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3, 4)),void *,__NOTHROW_NCX,recallocarray,(void *__mallptr, __SIZE_TYPE__ __old_elem_count, __SIZE_TYPE__ __new_elem_count, __SIZE_TYPE__ __elem_size),(__mallptr,__old_elem_count,__new_elem_count,__elem_size))
#elif (defined(__CRT_HAVE_recallocv) || defined(__CRT_HAVE__recalloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <libc/local/stdlib/recallocarray.h>
/* >> recallocarray(3)
 * Same   as    `recallocv(mallptr, new_elem_count, elem_size)',   but    also   ensure    that
 * when `mallptr != NULL', memory pointed to by the old  `mallptr...+=old_elem_count*elem_size'
 * is explicitly freed to zero (s.a. `freezero()') when reallocation must move the memory block */
__NAMESPACE_LOCAL_USING_OR_IMPL(recallocarray, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3, 4)) void *__NOTHROW_NCX(__LIBCCALL recallocarray)(void *__mallptr, __SIZE_TYPE__ __old_elem_count, __SIZE_TYPE__ __new_elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocarray))(__mallptr, __old_elem_count, __new_elem_count, __elem_size); })
#else /* ... */
#undef __recallocarray_defined
#endif /* !... */
#endif /* !__recallocarray_defined */
#ifndef __freezero_defined
#define __freezero_defined
#ifdef __CRT_HAVE_freezero
/* >> freezero(3)
 * Same as  `free(mallptr)', but  also ensure  that the  memory  region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned  to the  OS, rather  than being  left in  cache
 * while still containing its previous contents. */
__CDECLARE_VOID(,__NOTHROW_NCX,freezero,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/stdlib/freezero.h>
/* >> freezero(3)
 * Same as  `free(mallptr)', but  also ensure  that the  memory  region
 * described by `mallptr...+=num_bytes' is explicitly freed to zero, or
 * immediately returned  to the  OS, rather  than being  left in  cache
 * while still containing its previous contents. */
__NAMESPACE_LOCAL_USING_OR_IMPL(freezero, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL freezero)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(freezero))(__mallptr, __num_bytes); })
#else /* ... */
#undef __freezero_defined
#endif /* !... */
#endif /* !__freezero_defined */
#ifndef __strtonum_defined
#define __strtonum_defined
#ifdef __CRT_HAVE_strtonum
/* >> strtonum(3)
 * Similar to `strtoi()'  with `base=10',  but return  human-
 * readable error messages in `*p_errstr' on error (alongside
 * `return==0') (or `NULL' on success).
 * The following messages are defined:
 *   - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
 *   - "too small": Numeric value is too small (`ERANGE' && less than `lo')
 *   - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
 * @return: 0 : [*p_errstr != NULL] Error
 * @return: 0 : [*p_errstr == NULL] Success
 * @return: * : [*p_errstr == NULL] Success */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__LONGLONG,__NOTHROW_NCX,strtonum,(char const *__nptr, __LONGLONG __lo, __LONGLONG __hi, char const **__p_errstr),(__nptr,__lo,__hi,__p_errstr))
#else /* __CRT_HAVE_strtonum */
#include <libc/local/stdlib/strtonum.h>
/* >> strtonum(3)
 * Similar to `strtoi()'  with `base=10',  but return  human-
 * readable error messages in `*p_errstr' on error (alongside
 * `return==0') (or `NULL' on success).
 * The following messages are defined:
 *   - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
 *   - "too small": Numeric value is too small (`ERANGE' && less than `lo')
 *   - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
 * @return: 0 : [*p_errstr != NULL] Error
 * @return: 0 : [*p_errstr == NULL] Success
 * @return: * : [*p_errstr == NULL] Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtonum, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtonum)(char const *__nptr, __LONGLONG __lo, __LONGLONG __hi, char const **__p_errstr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtonum))(__nptr, __lo, __hi, __p_errstr); })
#endif /* !__CRT_HAVE_strtonum */
#endif /* !__strtonum_defined */
#if !defined(__getbsize_defined) && defined(__CRT_HAVE_getbsize)
#define __getbsize_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,getbsize,(int *__headerlenp, __LONGPTR_TYPE__ *__blocksizep),(__headerlenp,__blocksizep))
#endif /* !__getbsize_defined && __CRT_HAVE_getbsize */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_STDLIB_H */
