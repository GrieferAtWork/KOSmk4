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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_POISON_HEAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_POISON_HEAP_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/arch/poison-heap.h>
#include <kernel/malloc-defs.h>
/**/

/*[[[config CONFIG_HAVE_KERNEL_POISON_HEAP: bool = defined(CONFIG_HAVE_KERNEL_DEBUGGER)
 * Config option:  When the  kernel becomes  poisoned, re-direct  all
 * of the following functions to  use a small, secondary heap  system
 * that  is  designed for  simplicity,  being as  robust  as possible
 * against further corruption, whilst ignoring any noticeable illegal
 * API  use. This heap is not meant to be used forever, since the way
 * that it  is designed  has it  lacking an  actual free()  function,
 * meaning  that  once enabled,  the kernel  will  run out  of memory
 * sooner or later.
 * This poison-heap is simply meant to  be used as a drop-in  replacement
 * when the ship is  already sinking, at  which point it  is meant to  be
 * used for allocating memory needed for holding decompressed .debug_info
 * and  the  like, when  not being  able to  allocate such  buffers would
 * normally mean  that the  kernel would  be unable  to (safely)  display
 * tracebacks following a crash.
 * List of functions that get overwritten/re-directed:
 *   - heap_alloc
 *   - heap_alloc_untraced
 *   - heap_alloc_nx
 *   - heap_alloc_untraced_nx
 *   - heap_align
 *   - heap_align_untraced
 *   - heap_align_nx
 *   - heap_align_untraced_nx
 *   - heap_allat
 *   - heap_allat_untraced
 *   - heap_allat_nx
 *   - heap_allat_untraced_nx
 *   - heap_realloc
 *   - heap_realloc_untraced
 *   - heap_realloc_nx
 *   - heap_realloc_untraced_nx
 *   - heap_realign
 *   - heap_realign_untraced
 *   - heap_realign_nx
 *   - heap_realign_untraced_nx
 *   - heap_free
 *   - heap_free_untraced
 *   - heap_truncate
 *   - heap_truncate_untraced
 *   - heap_trim
 * #ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
 *   - heap_validate
 *   - heap_validate_all
 * #endif
 * #ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
 *   - slab_free
 *   - slab_ffree
 *   - slab_malloc[NNN]         (SLAB_FOREACH_SIZE)
 *   - slab_kmalloc[NNN]        (SLAB_FOREACH_SIZE)
 *   - slab_kmalloc_nx[NNN]     (SLAB_FOREACH_SIZE)
 *   - slab_malloc
 *   - slab_kmalloc
 *   - slab_kmalloc_nx
 * #endif
 *   - kmalloc
 *   - kmalloc_nx
 * #ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
 *   - kmalloc_noslab
 *   - kmalloc_noslab_nx
 * #endif
 *   - kmemalign
 *   - kmemalign_nx
 *   - kmemalign_offset
 *   - kmemalign_offset_nx
 *   - krealloc
 *   - krealloc_nx
 *   - krealign
 *   - krealign_nx
 *   - krealign_offset
 *   - krealign_offset_nx
 *   - krealloc_in_place
 *   - krealloc_in_place_nx
 *   - kmalloc_usable_size
 *   - kfree
 *   - kffree
 * #ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
 *   - mall_dump_leaks
 *   - mall_trace
 *   - mall_validate_padding
 *   - mall_print_traceback
 *   - mall_untrace
 *   - mall_untrace_n
 * #endif
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_POISON_HEAP
#undef CONFIG_HAVE_KERNEL_POISON_HEAP
#elif !defined(CONFIG_HAVE_KERNEL_POISON_HEAP)
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#define CONFIG_HAVE_KERNEL_POISON_HEAP
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
#define CONFIG_NO_KERNEL_POISON_HEAP
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */
#elif (-CONFIG_HAVE_KERNEL_POISON_HEAP - 1) == -1
#undef CONFIG_HAVE_KERNEL_POISON_HEAP
#define CONFIG_NO_KERNEL_POISON_HEAP
#endif /* ... */
/*[[[end]]]*/



#ifdef CONFIG_HAVE_KERNEL_POISON_HEAP
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
#define __PH_IF_DEBUG_HEAP(x) x
#else /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
#define __PH_IF_DEBUG_HEAP(x) /* nothing */
#endif /* !CONFIG_HAVE_KERNEL_DEBUG_HEAP */

#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#define __PH_IF_DEBUG_MALLOC(x) x
#else /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
#define __PH_IF_DEBUG_MALLOC(x) /* nothing */
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */

#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
#define __PH_IF_USE_SLAB_ALLOCATORS(x) x
#define __PH_IF_USE_SLAB_ALLOCATORS_FOREACH1(sz, _) \
	_(slab_malloc##sz, /*    */ ph_slab_malloc##sz, 1)
#define __PH_IF_USE_SLAB_ALLOCATORS_FOREACH2(sz, _)  \
	_(slab_kmalloc##sz, /*   */ ph_slab_kmalloc##sz) \
	_(slab_kmalloc_nx##sz, /**/ ph_slab_kmalloc_nx##sz)
#else /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */
#define __PH_IF_USE_SLAB_ALLOCATORS(x)             /* nothing */
#define __PH_IF_USE_SLAB_ALLOCATORS_FOREACH1(i, _) /* nothing */
#define __PH_IF_USE_SLAB_ALLOCATORS_FOREACH2(i, _) /* nothing */
#endif /* !CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

#ifndef SLAB_FOREACH_SIZE
#define SLAB_FOREACH_SIZE(func, _) /* nothing */
#endif /* !SLAB_FOREACH_SIZE */


 /* Enumerate poison binding overrides:
 * >> bind_func(SymbolName heap_symbol, SymbolName ph_heap_symbol)
 * >> bind_void(SymbolName heap_symbol, SymbolName ph_heap_symbol, uint argc)
 * >> bind_zero(SymbolName heap_symbol, SymbolName ph_heap_symbol, uint argc)
 * Where `bind_func()' should simply re-direct `heap_symbol' to `ph_heap_symbol',
 * `bind_void' should do the same, or have `heap_symbol' return immediately whilst
 * potentially adjust the stack for `argc' arguments, and `bind_zero' should also
 * do the same, but also have the function return `0' or `NULL' */
#define KERNEL_POISON_HEAP_ENUMERATE_BINDINGS(bind_func, bind_void, bind_zero)               \
	bind_func(heap_alloc, /*              */ ph_heap_alloc)                                  \
	bind_func(heap_alloc_untraced, /*     */ ph_heap_alloc)                                  \
	bind_func(heap_alloc_nx, /*           */ ph_heap_alloc_nx)                               \
	bind_func(heap_alloc_untraced_nx, /*  */ ph_heap_alloc_nx)                               \
	bind_func(heap_align, /*              */ ph_heap_align)                                  \
	bind_func(heap_align_untraced, /*     */ ph_heap_align)                                  \
	bind_func(heap_align_nx, /*           */ ph_heap_align_nx)                               \
	bind_func(heap_align_untraced_nx, /*  */ ph_heap_align_nx)                               \
	bind_zero(heap_allat, /*              */ ph_heap_allat, 4)                               \
	bind_zero(heap_allat_untraced, /*     */ ph_heap_allat, 4)                               \
	bind_zero(heap_allat_nx, /*           */ ph_heap_allat_nx, 4)                            \
	bind_zero(heap_allat_untraced_nx, /*  */ ph_heap_allat_nx, 4)                            \
	bind_func(heap_realloc, /*            */ ph_heap_realloc)                                \
	bind_func(heap_realloc_untraced, /*   */ ph_heap_realloc)                                \
	bind_func(heap_realloc_nx, /*         */ ph_heap_realloc_nx)                             \
	bind_func(heap_realloc_untraced_nx, /**/ ph_heap_realloc_nx)                             \
	bind_func(heap_realign, /*            */ ph_heap_realign)                                \
	bind_func(heap_realign_untraced, /*   */ ph_heap_realign)                                \
	bind_func(heap_realign_nx, /*         */ ph_heap_realign_nx)                             \
	bind_func(heap_realign_untraced_nx, /**/ ph_heap_realign_nx)                             \
	bind_void(heap_free, /*               */ ph_heap_free, 4)                                \
	bind_void(heap_free_untraced, /*      */ ph_heap_free, 4)                                \
	bind_zero(heap_truncate, /*           */ ph_heap_truncate, 5)                            \
	bind_zero(heap_truncate_untraced, /*  */ ph_heap_truncate, 5)                            \
	bind_zero(heap_trim, /*               */ ph_heap_trim, 2)                                \
	__PH_IF_DEBUG_HEAP(bind_void(heap_validate, ph_heap_validate, 1))                        \
	__PH_IF_DEBUG_HEAP(bind_void(heap_validate_all, ph_heap_validate_all, 0))                \
	SLAB_FOREACH_SIZE(__PH_IF_USE_SLAB_ALLOCATORS_FOREACH1, bind_zero)                       \
	SLAB_FOREACH_SIZE(__PH_IF_USE_SLAB_ALLOCATORS_FOREACH2, bind_func)                       \
	__PH_IF_USE_SLAB_ALLOCATORS(bind_void(slab_free, /*      */ ph_kfree, 1))                \
	__PH_IF_USE_SLAB_ALLOCATORS(bind_void(slab_ffree, /*     */ ph_kffree, 2))               \
	__PH_IF_USE_SLAB_ALLOCATORS(bind_func(slab_malloc, /*    */ ph_kmalloc_nx))              \
	__PH_IF_USE_SLAB_ALLOCATORS(bind_func(slab_kmalloc, /*   */ ph_kmalloc))                 \
	__PH_IF_USE_SLAB_ALLOCATORS(bind_func(slab_kmalloc_nx, /**/ ph_kmalloc_nx))              \
	bind_func(kmalloc, /*                  */ ph_kmalloc)                                    \
	bind_func(kmalloc_nx, /*               */ ph_kmalloc_nx)                                 \
	__PH_IF_USE_SLAB_ALLOCATORS(bind_func(kmalloc_noslab, ph_kmalloc))                       \
	__PH_IF_USE_SLAB_ALLOCATORS(bind_func(kmalloc_noslab_nx, ph_kmalloc_nx))                 \
	bind_func(kmemalign, /*            */ ph_kmemalign)                                      \
	bind_func(kmemalign_nx, /*         */ ph_kmemalign_nx)                                   \
	bind_func(kmemalign_offset, /*     */ ph_kmemalign_offset)                               \
	bind_func(kmemalign_offset_nx, /*  */ ph_kmemalign_offset_nx)                            \
	bind_func(krealloc, /*             */ ph_krealloc)                                       \
	bind_func(krealloc_nx, /*          */ ph_krealloc_nx)                                    \
	bind_func(krealign, /*             */ ph_krealign)                                       \
	bind_func(krealign_nx, /*          */ ph_krealign_nx)                                    \
	bind_func(krealign_offset, /*      */ ph_krealign_offset)                                \
	bind_func(krealign_offset_nx, /*   */ ph_krealign_offset_nx)                             \
	bind_func(krealloc_in_place, /*    */ ph_krealloc_in_place)                              \
	bind_func(krealloc_in_place_nx, /* */ ph_krealloc_in_place)                              \
	bind_func(kmalloc_usable_size, /*  */ ph_kmalloc_usable_size)                            \
	bind_void(kfree, /*                */ ph_kfree, 1)                                       \
	bind_void(kffree, /*               */ ph_kffree, 2)                                      \
	__PH_IF_DEBUG_MALLOC(bind_void(kmalloc_validate, /*     */ ph_kmalloc_validate, 0))      \
	__PH_IF_DEBUG_MALLOC(bind_zero(kmalloc_leaks, /*        */ ph_kmalloc_leaks, 0))         \
	__PH_IF_DEBUG_MALLOC(bind_zero(kmalloc_leaks_collect, /**/ ph_kmalloc_leaks_collect, 0)) \
	__PH_IF_DEBUG_MALLOC(bind_zero(kmalloc_leaks_print, /*  */ ph_kmalloc_leaks_print, 4))   \
	__PH_IF_DEBUG_MALLOC(bind_zero(kmalloc_leaks_count, /*  */ ph_kmalloc_leaks_count, 1))   \
	__PH_IF_DEBUG_MALLOC(bind_void(kmalloc_leaks_release, /**/ ph_kmalloc_leaks_release, 2)) \
	__PH_IF_DEBUG_MALLOC(bind_zero(memleak_next, /*         */ ph_memleak_next, 2))          \
	__PH_IF_DEBUG_MALLOC(bind_zero(memleak_getattr, /*      */ ph_memleak_getattr, 2))       \
	__PH_IF_DEBUG_MALLOC(bind_func(kmalloc_trace_nx, /*     */ ph_kmalloc_trace_nx))         \
	__PH_IF_DEBUG_MALLOC(bind_void(kmalloc_untrace, /*      */ ph_kmalloc_untrace, 1))       \
	__PH_IF_DEBUG_MALLOC(bind_void(kmalloc_untrace_n, /*    */ ph_kmalloc_untrace_n, 2))     \
	__PH_IF_DEBUG_MALLOC(bind_zero(kmalloc_traceback, /*    */ ph_kmalloc_traceback, 4))

#ifdef __CC__
#ifdef BUILDING_KERNEL_CORE
DECL_BEGIN

/* Install poison heap overrides.
 * NOTE: This function must be called immediately
 *       after `_kernel_poisoned' is set to true. */
INTDEF NOBLOCK void NOTHROW(KCALL ph_install)(void);

DECL_END
#endif /* BUILDING_KERNEL_CORE */
#endif /* __CC__ */

#endif /* CONFIG_HAVE_KERNEL_POISON_HEAP */


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_POISON_HEAP_H */
