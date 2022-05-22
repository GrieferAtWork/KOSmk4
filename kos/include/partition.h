/* HASH CRC-32:0xc1c90389 */
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
/* (#) Portability: libiberty (/include/partition.h) */
#ifndef _PARTITION_H
#define _PARTITION_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/crt/partition.h>

#ifdef __CC__
__SYSDECL_BEGIN

typedef struct partition_def *partition;

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

/*
 * Example usage:
 *
 * >> partition part = partition_new(42);
 * >> assert(partition_find(part, 10) == 10);
 * >> assert(partition_find(part, 20) == 20);
 * >> assert(partition_find(part, 30) == 30);
 * >> partition_union(part, 10, 20);
 * >> partition_union(part, 10, 30);
 * >> assert(partition_find(part, 10) == partition_find(part, 20));
 * >> assert(partition_find(part, 10) == partition_find(part, 30));
 */

#ifdef __CRT_HAVE_partition_new
/* >> partition_new(3)
 * Create a new partition for `num_elements' elements.
 *  - Uses `xmalloc(3)', so never returns `NULL'! */
__CDECLARE(__ATTR_RETNONNULL,struct partition_def *,__NOTHROW_NCX,partition_new,(__STDC_INT_AS_UINT_T __num_elements),(__num_elements))
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/partition/partition_new.h>
/* >> partition_new(3)
 * Create a new partition for `num_elements' elements.
 *  - Uses `xmalloc(3)', so never returns `NULL'! */
__NAMESPACE_LOCAL_USING_OR_IMPL(partition_new, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL struct partition_def *__NOTHROW_NCX(__LIBCCALL partition_new)(__STDC_INT_AS_UINT_T __num_elements) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(partition_new))(__num_elements); })
#endif /* ... */
#ifdef __CRT_HAVE_partition_delete
/* >> partition_delete(3)
 * Destroy a given partition */
__CDECLARE_VOID(,__NOTHROW_NCX,partition_delete,(struct partition_def *__self),(__self))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/partition/partition_delete.h>
/* >> partition_delete(3)
 * Destroy a given partition */
__NAMESPACE_LOCAL_USING_OR_IMPL(partition_delete, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL partition_delete)(struct partition_def *__self) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(partition_delete))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_partition_union
/* >> partition_union(3)
 * Join the classes containing elements `a' and `b' into the same class
 * For  this, choose one  of the class's canonical  elements as the new
 * canonical element of the total  class, which is then also  returned. */
__CDECLARE(__ATTR_INOUT(1),__STDC_INT_AS_UINT_T,__NOTHROW_NCX,partition_union,(struct partition_def *__self, __STDC_INT_AS_UINT_T __a, __STDC_INT_AS_UINT_T __b),(__self,__a,__b))
#else /* __CRT_HAVE_partition_union */
#include <libc/local/partition/partition_union.h>
/* >> partition_union(3)
 * Join the classes containing elements `a' and `b' into the same class
 * For  this, choose one  of the class's canonical  elements as the new
 * canonical element of the total  class, which is then also  returned. */
__NAMESPACE_LOCAL_USING_OR_IMPL(partition_union, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __STDC_INT_AS_UINT_T __NOTHROW_NCX(__LIBCCALL partition_union)(struct partition_def *__self, __STDC_INT_AS_UINT_T __a, __STDC_INT_AS_UINT_T __b) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(partition_union))(__self, __a, __b); })
#endif /* !__CRT_HAVE_partition_union */
#ifdef __CRT_HAVE_partition_print
/* >> partition_print(3)
 * Print classes (and  their elements) of  `self' to  `fp'
 * The format used is: '[' ['(' [0 1 2 3 4]... ')']... ']'
 * Example: "[(0 1 2 4 8)(3 6)(5 7)]" */
__CDECLARE_VOID(__ATTR_IN(1) __ATTR_INOUT(2),__NOTHROW_NCX,partition_print,(struct partition_def __KOS_FIXED_CONST *__self, FILE *__fp),(__self,__fp))
#elif defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/partition/partition_print.h>
/* >> partition_print(3)
 * Print classes (and  their elements) of  `self' to  `fp'
 * The format used is: '[' ['(' [0 1 2 3 4]... ')']... ']'
 * Example: "[(0 1 2 4 8)(3 6)(5 7)]" */
__NAMESPACE_LOCAL_USING_OR_IMPL(partition_print, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT(2) void __NOTHROW_NCX(__LIBCCALL partition_print)(struct partition_def __KOS_FIXED_CONST *__self, FILE *__fp) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(partition_print))(__self, __fp); })
#endif /* ... */

/* Return the canonical element for the class containing `element' */
#define partition_find(self, element) \
	((self)->elements[element].class_element)

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTITION_H */
