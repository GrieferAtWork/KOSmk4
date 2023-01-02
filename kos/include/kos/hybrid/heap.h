/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_HYBRID_HEAP_H
#define _KOS_HYBRID_HEAP_H 1

#include <__stdinc.h>

/* Hybrid heap functions. */

#ifdef __INTELLISENSE__
#include <bits/types.h>
#include <kos/anno.h>
#define OS_HEAP_HASGFP 1
#define _os_heap_gfparg(var_name)   , int var_name
#define _os_heap_gfppar(var_name)   , var_name
#define os_heap_gfparg_(var_name)   int var_name,
#define os_heap_gfppar_(var_name)   var_name,
#define os_heap_gfparg(var_name)    int var_name
#define os_heap_gfppar(var_name)    var_name
#define os_heap_gfpvar(var_name)    int var_name;
#define os_heap_gfpget(var_name)    var_name
#define os_heap_gfpset(var_name, v) var_name = (v)
#elif defined(__KERNEL__)
#include <kernel/malloc.h>
#define OS_HEAP_HASGFP 1
#define _os_heap_gfparg(var_name)   , gfp_t var_name
#define _os_heap_gfppar(var_name)   , var_name
#define os_heap_gfparg_(var_name)   gfp_t var_name,
#define os_heap_gfppar_(var_name)   var_name,
#define os_heap_gfparg(var_name)    gfp_t var_name
#define os_heap_gfppar(var_name)    var_name
#define os_heap_gfpvar(var_name)    gfp_t var_name;
#define os_heap_gfpget(var_name)    var_name
#define os_heap_gfpset(var_name, v) var_name = (v)
#else /* __KERNEL__ */
#include <malloc.h>
#include <kos/malloc.h>
#undef OS_HEAP_HASGFP
#define _os_heap_gfparg(var_name)   /* nothing */
#define _os_heap_gfppar(var_name)   /* nothing */
#define os_heap_gfparg_(var_name)   /* nothing */
#define os_heap_gfppar_(var_name)   /* nothing */
#define os_heap_gfparg(var_name)    void
#define os_heap_gfppar(var_name)    /* nothing */
#define os_heap_gfpvar(var_name)    /* nothing */
#define os_heap_gfpget(var_name)    0
#define os_heap_gfpset(var_name, v) (void)0
#endif /* !__KERNEL__ */

#ifdef __CC__
__DECL_BEGIN

/* NOTES (when running under KOS):
 *  - `os_heap_realloc(NULL, N)' returns a non-NULL, unique pointer for every N
 *  - `os_heap_realloc(ptr, 0)'  returns non-NULL and has a syntactic behavior identical to `os_heap_realloc(ptr, 1)'
 *  - `os_heap_usable_size(ptr)' may return  a  value larger  than  what  was allocated,  though  not  less.
 *                               All bytes of the indicated memory range are free for general-purpose usage. */

#ifdef __INTELLISENSE__
/* Allocate `num_bytes' of heap memory, or THROW(E_BADALLOC)
 *
 * When `num_bytes' is `0', allocate a minimal-size heap block that may
 * not actually contain any usable bytes, though is still distinct from
 * NULL, and must still be `os_heap_free()'d once no longer in use. */
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *
(os_heap_malloc)(__size_t __num_bytes, int __gfp) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *
(os_heap_calloc)(__size_t __num_bytes, int __gfp) __THROWS(E_BADALLOC);

/* Same as `os_heap_malloc()', but return `NULL' on error instead of throwing an exception.
 * In   user-space,  a  `NULL'  return  value  is  also  accompanied  by  `errno == ENOMEM' */
__ATTR_MALLOC __ATTR_WUNUSED void *
__NOTHROW(os_heap_malloc_nx)(__size_t __num_bytes, int __gfp);
__ATTR_MALLOC __ATTR_WUNUSED void *
__NOTHROW(os_heap_calloc_nx)(__size_t __num_bytes, int __gfp);

/* Re-allocate  `ptr:os_heap_usable_size(ptr)'  into a  `num_bytes'-large heap
 * block, and copy data from the old  block before freeing said old block.  If
 * the old block is smaller than the new block, cannot be extended, and no new
 * block can be allocated, throw an THROW(E_BADALLOC) exception
 *  - When `ptr' is `NULL', behave identical to `os_heap_malloc(num_bytes, GFP)'
 *  - When `num_bytes' is `0', re-size `ptr' to a */
__ATTR_RETNONNULL __ATTR_WUNUSED void *
(os_heap_realloc)(/*nullable*/ void *__ptr, __size_t __num_bytes, int __gfp) __THROWS(E_BADALLOC);

/* Same as `os_heap_realloc()', but return `NULL' on error instead of throwing an exception.
 * In  user-space,  a  `NULL'  return   value  is  also  accompanied  by   `errno == ENOMEM' */
__ATTR_WUNUSED void *
__NOTHROW(os_heap_realloc_nx)(/*nullable*/ void *__ptr, __size_t __num_bytes, int __gfp);

/* Same as `os_heap_realloc()',  but only  ever extend/truncate a  memory block  starting
 * at `ptr'. If `num_bytes' is less  than or equal to `os_heap_usable_size(ptr)',  simply
 * truncate the block and re-return `ptr'. Otherwise, try to allocate memory from  within
 * the  range `ptr+os_heap_usable_size(ptr) ... ptr+num_bytes-1' and associate that range
 * with the memory block described by `ptr'. If this isn't possible, simply return `NULL'
 * A `NULL' return value may or may not modify `errno' */
__ATTR_WUNUSED void *
__NOTHROW(os_heap_realloc_in_place_nx)(/*nullable*/ void *__ptr, __size_t __num_bytes, int __gfp);

/* Same as `os_heap_malloc()', but ensure that the returned heap block is aligned
 * by  at least `min_alignment' bytes, where `min_alignment' must be a power-of-2 */
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *
(os_heap_memalign)(__size_t __min_alignment, __size_t __num_bytes, int __gfp) __THROWS(E_BADALLOC);

/* Same as `os_heap_memalign()', but return `NULL' on error instead of throwing an exception.
 * In   user-space,  a  `NULL'   return  value  is   also  accompanied  by  `errno == ENOMEM' */
__ATTR_MALLOC __ATTR_WUNUSED void *
__NOTHROW(os_heap_memalign_nx)(__size_t __min_alignment, __size_t __num_bytes, int __gfp);

/* Returns  the # of usable bytes of memory  within the heap block indicated by `ptr'
 * This is the lower bound of bytes that is retained in a call to `os_heap_realloc()'
 * with a new `num_bytes' value >= the value returned by this function.
 *
 * When called on a freshly allocated heap block, the return value is guaranteed to
 * be  >=  the  `num_bytes'  used  during  allocation  of  the  same  heap   block.
 *
 * A special case exists when `ptr' is `NULL', in which case this function always
 * returns `0'. Note however that a minimal-length heap block is also allowed  to
 * have `0' usable bytes, but still be distinct from a `NULL'-pointer.
 * i.e. `os_heap_usable_size(os_heap_malloc(0))' is allowed to be `0', even
 *      though `os_heap_malloc()' had previously returned a non-NULL value. */
__ATTR_WUNUSED __size_t
__NOTHROW(os_heap_usable_size)(/*nullable*/ void *__ptr);

/* Free a heap block once it is no longer in use.
 * Note that this is the only way to fully clean up a heap block. realloc()ating a
 * block to 0-size will merely truncate the block to minimal-length. This function
 * will completely clean up the block such  that any further attempt to use  `ptr'
 * in  a call to  `os_heap_realloc()', `os_heap_usable_size()' or `os_heap_free()'
 * results in hard undefined behavior (i.e.  a likely application crash for  user-
 * space, or triggering kernel panic for kernel-space)
 * This function is guarantied not to modify `errno' */
void __NOTHROW(os_heap_free)(/*nullable*/ void *__ptr);

/* Same as the  functions above,  but behave as  NonExcept for  user-space,
 * and  exception-enabled  for  kernel-space  (useful  simply  the  general
 * expectation for user-space API functions is to return NULL/errno=ENOMEM,
 * while the general expectation for kernel-space is to throw an exception) */
#ifdef __KERNEL__
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(os_heap_malloc_unx)(__size_t __num_bytes, int __gfp) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(os_heap_calloc_unx)(__size_t __num_bytes, int __gfp) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_WUNUSED void *(os_heap_realloc_unx)(/*nullable*/ void *__ptr, __size_t __num_bytes, int __gfp) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_WUNUSED void *(os_heap_realloc_in_place_unx)(/*nullable*/ void *__ptr, __size_t __num_bytes, int __gfp) __THROWS(E_BADALLOC);
__ATTR_RETNONNULL __ATTR_MALLOC __ATTR_WUNUSED void *(os_heap_memalign_unx)(__size_t __min_alignment, __size_t __num_bytes, int __gfp) __THROWS(E_BADALLOC);
#else /* __KERNEL__ */
__ATTR_MALLOC __ATTR_WUNUSED void *__NOTHROW(os_heap_malloc_unx)(__size_t __num_bytes, int __gfp);
__ATTR_MALLOC __ATTR_WUNUSED void *__NOTHROW(os_heap_calloc_unx)(__size_t __num_bytes, int __gfp);
__ATTR_WUNUSED void *__NOTHROW(os_heap_realloc_unx)(/*nullable*/ void *__ptr, __size_t __num_bytes, int __gfp);
__ATTR_WUNUSED void *__NOTHROW(os_heap_realloc_in_place_unx)(/*nullable*/ void *__ptr, __size_t __num_bytes, int __gfp);
__ATTR_MALLOC __ATTR_WUNUSED void *__NOTHROW(os_heap_memalign_unx)(__size_t __min_alignment, __size_t __num_bytes, int __gfp);
#endif /* !__KERNEL__ */
#elif defined(__KERNEL__)
#define os_heap_malloc(num_bytes, gfp)                      kmalloc(num_bytes, gfp)
#define os_heap_malloc_unx(num_bytes, gfp)                  kmalloc(num_bytes, gfp)
#define os_heap_malloc_nx(num_bytes, gfp)                   kmalloc_nx(num_bytes, gfp)
#define os_heap_calloc(num_bytes, gfp)                      kcalloc(num_bytes, gfp)
#define os_heap_calloc_unx(num_bytes, gfp)                  kcalloc(num_bytes, gfp)
#define os_heap_calloc_nx(num_bytes, gfp)                   kcalloc_nx(num_bytes, gfp)
#define os_heap_realloc(ptr, num_bytes, gfp)                krealloc(ptr, num_bytes, gfp)
#define os_heap_realloc_unx(ptr, num_bytes, gfp)            krealloc(ptr, num_bytes, gfp)
#define os_heap_realloc_nx(ptr, num_bytes, gfp)             krealloc_nx(ptr, num_bytes, gfp)
#define os_heap_realloc_in_place_unx(ptr, num_bytes, gfp)   krealloc_in_place(ptr, num_bytes, gfp)
#define os_heap_realloc_in_place_nx(ptr, num_bytes, gfp)    krealloc_in_place_nx(ptr, num_bytes, gfp)
#define os_heap_memalign(min_alignment, num_bytes, gfp)     kmemalign(min_alignment, num_bytes, gfp)
#define os_heap_memalign_unx(min_alignment, num_bytes, gfp) kmemalign(min_alignment, num_bytes, gfp)
#define os_heap_memalign_nx(min_alignment, num_bytes, gfp)  kmemalign_nx(min_alignment, num_bytes, gfp)
#define os_heap_usable_size(ptr)                            kmalloc_usable_size(ptr)
#define os_heap_free(ptr)                                   kfree(ptr)
#else /* __KERNEL__ */
#define os_heap_malloc(num_bytes, ...)                      Malloc(num_bytes)
#define os_heap_malloc_unx(num_bytes, ...)                  malloc(num_bytes)
#define os_heap_malloc_nx(num_bytes, ...)                   malloc(num_bytes)
#define os_heap_calloc(num_bytes, ...)                      Calloc(1, num_bytes)
#define os_heap_calloc_unx(num_bytes, ...)                  calloc(1, num_bytes)
#define os_heap_calloc_nx(num_bytes, ...)                   calloc(1, num_bytes)
#define os_heap_realloc(ptr, num_bytes, ...)                Realloc(ptr, num_bytes)
#define os_heap_realloc_unx(ptr, num_bytes, ...)            realloc(ptr, num_bytes)
#define os_heap_realloc_nx(ptr, num_bytes, ...)             realloc(ptr, num_bytes)
#define os_heap_realloc_in_place_unx(ptr, num_bytes, ...)   realloc_in_place(ptr, num_bytes)
#define os_heap_realloc_in_place_nx(ptr, num_bytes, ...)    realloc_in_place(ptr, num_bytes)
#define os_heap_memalign(min_alignment, num_bytes, ...)     Memalign(min_alignment, num_bytes)
#define os_heap_memalign_unx(min_alignment, num_bytes, ...) memalign(min_alignment, num_bytes)
#define os_heap_memalign_nx(min_alignment, num_bytes, ...)  memalign(min_alignment, num_bytes)
#define os_heap_usable_size(ptr)                            malloc_usable_size(ptr)
#define os_heap_free(ptr)                                   free(ptr)
#endif /* !__KERNEL__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_HYBRID_HEAP_H */
