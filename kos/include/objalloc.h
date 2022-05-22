/* HASH CRC-32:0x8a692733 */
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
/* (#) Portability: EMX kLIBC (/libc/include/objalloc.h) */
/* (#) Portability: libiberty (/include/objalloc.h) */
#ifndef _OBJALLOC_H
#define _OBJALLOC_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/crt/objalloc.h>

/* Alignment guarantied for memory allocated by objalloc objects. */
#ifndef OBJALLOC_ALIGN
#define OBJALLOC_ALIGN __LIBC_MALLOC_ALIGNMENT
#endif /* !OBJALLOC_ALIGN */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_objalloc_create
/* >> objalloc_create(3)
 * Allocate and initialize a new objalloc object.
 * @return: * :   The new objalloc object
 * @return: NULL: Out of memory */
__CDECLARE(,struct objalloc *,__NOTHROW_NCX,objalloc_create,(void),())
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/objalloc/objalloc_create.h>
/* >> objalloc_create(3)
 * Allocate and initialize a new objalloc object.
 * @return: * :   The new objalloc object
 * @return: NULL: Out of memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(objalloc_create, __FORCELOCAL __ATTR_ARTIFICIAL struct objalloc *__NOTHROW_NCX(__LIBCCALL objalloc_create)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(objalloc_create))(); })
#endif /* ... */
#ifdef __CRT_HAVE__objalloc_alloc
/* >> _objalloc_alloc(3)
 * Allocate `num_bytes' of memory from `self'
 * @return: * :   The `num_bytes'-large data-blob
 * @return: NULL: Out of memory */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RW(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_objalloc_alloc,(struct objalloc *__self, __ULONGPTR_TYPE__ __num_bytes),(__self,__num_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/objalloc/_objalloc_alloc.h>
/* >> _objalloc_alloc(3)
 * Allocate `num_bytes' of memory from `self'
 * @return: * :   The `num_bytes'-large data-blob
 * @return: NULL: Out of memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(_objalloc_alloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RW(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL _objalloc_alloc)(struct objalloc *__self, __ULONGPTR_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_objalloc_alloc))(__self, __num_bytes); })
#endif /* ... */
#ifdef __CRT_HAVE_objalloc_free
/* >> objalloc_free(3)
 * Free all memory allocated by `self', before also freeing `self' */
__CDECLARE_VOID(__ATTR_ACCESS_RW(1),__NOTHROW_NCX,objalloc_free,(struct objalloc *__self),(__self))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/objalloc/objalloc_free.h>
/* >> objalloc_free(3)
 * Free all memory allocated by `self', before also freeing `self' */
__NAMESPACE_LOCAL_USING_OR_IMPL(objalloc_free, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RW(1) void __NOTHROW_NCX(__LIBCCALL objalloc_free)(struct objalloc *__self) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(objalloc_free))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_objalloc_free_block
/* >> objalloc_free_block(3)
 * Free a given `ptr', as well as everything allocated since. */
__CDECLARE_VOID(__ATTR_ACCESS_RW(1) __ATTR_NONNULL((2)),__NOTHROW_NCX,objalloc_free_block,(struct objalloc *__self, void *__ptr),(__self,__ptr))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/objalloc/objalloc_free_block.h>
/* >> objalloc_free_block(3)
 * Free a given `ptr', as well as everything allocated since. */
__NAMESPACE_LOCAL_USING_OR_IMPL(objalloc_free_block, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RW(1) __ATTR_NONNULL((2)) void __NOTHROW_NCX(__LIBCCALL objalloc_free_block)(struct objalloc *__self, void *__ptr) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(objalloc_free_block))(__self, __ptr); })
#endif /* ... */
#if defined(__CRT_HAVE__objalloc_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#ifndef __NO_XBLOCK
#define objalloc_alloc(self, num_bytes)                                                 \
	__XBLOCK({                                                                          \
		struct objalloc *__oa_self       = (self);                                      \
		__ULONGPTR_TYPE__ __oa_num_bytes = (num_bytes);                                 \
		if (__oa_num_bytes == 0)                                                        \
			__oa_num_bytes = 1;                                                         \
		__oa_num_bytes = (__oa_num_bytes + OBJALLOC_ALIGN - 1) & ~(OBJALLOC_ALIGN - 1); \
		__XRETURN __oa_num_bytes != 0 && __oa_num_bytes <= __oa_self->current_space     \
		          ? (__oa_self->current_ptr += __oa_num_bytes,                          \
		             __oa_self->current_space -= __oa_num_bytes,                        \
		             (void *)(__oa_self->current_ptr - __oa_num_bytes))                 \
		          : _objalloc_alloc(__oa_self, __oa_num_bytes);                         \
	})
#else /* !__NO_XBLOCK */
#define objalloc_alloc(self, num_bytes) _objalloc_alloc(self, num_bytes)
#endif /* __NO_XBLOCK */
#endif /* __CRT_HAVE__objalloc_alloc || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_OBJALLOC_H */
