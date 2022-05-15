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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MALLOC_DEFS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MALLOC_DEFS_H 1

#include <kernel/compiler.h>

DECL_BEGIN

//#define CONFIG_NO_DEBUG_HEAP             1
//#define CONFIG_NO_HEAP_RANDOMIZE_OFFSETS 1
//#define CONFIG_NO_HEAP_TRACE_DANGLE      1
//#define CONFIG_NO_TRACE_MALLOC           1


/* Enable heap memory  pre-initialization, as  well as  special
 * data patterns  for unallocated  memory, in  addition to  the
 * ability of tracking use-after-free through `heap_validate()'
 * Note  that `heap_validate()' attempts to optimize itself not
 * to check data  blocks that haven't  been modified since  the
 * previous check, making use of `pagedir_haschanged()', should
 * the host support that function (`ARCH_PAGEDIR_HAVE_CHANGED') */
#ifndef CONFIG_DEBUG_HEAP
#if !defined(CONFIG_NO_DEBUG_HEAP) && !defined(NDEBUG)
#define CONFIG_DEBUG_HEAP 1
#elif !defined(CONFIG_NO_DEBUG_HEAP)
#define CONFIG_NO_DEBUG_HEAP 1
#endif
#elif defined(CONFIG_NO_DEBUG_HEAP)
#undef CONFIG_DEBUG_HEAP
#endif


/* Randomize in-heap allocation offsets (using `rand()') when
 * less memory than the best  matching free slot contains  is
 * allocated:
 * >> slot(48 bytes):  FREEFREEFREEFREEFREEFREEFREEFREEFREEFREEFREEFREE
 * >> alloc(16 bytes): FREEFREEFREEFREE                                 (Without `CONFIG_HEAP_RANDOMIZE_OFFSETS')
 * >> alloc(16 bytes):                                 FREEFREEFREEFREE (With `CONFIG_HEAP_RANDOMIZE_OFFSETS')
 * >> alloc(16 bytes):                 FREEFREEFREEFREE                 (With `CONFIG_HEAP_RANDOMIZE_OFFSETS')
 * >> alloc(16 bytes): FREEFREEFREEFREE                                 (With `CONFIG_HEAP_RANDOMIZE_OFFSETS')
 * This configuration option affects the results of `heap_alloc()' and `heap_align()'
 * Reasoning:
 *   - Although even without this option, we are randomizing the kernel heap  location
 *     during early boot, once that's been established, no further randomization would
 *     be done without this option enabled.
 *     That  could lead to bugs going undetected  that depend on the relative offsets
 *     between allocated data blocks, something that this option prevents by ensuring
 *     that more randomization is added into the mix whenever memory is allocated.
 *   - Without this option, only address bits above `PAGESIZE' would be randomized
 *     for  the kernel's default heaps, while bits between it and `HEAP_ALIGNMENT'
 *     would   be    predictably   consistent    for   consecutive    allocations.
 *     That might be another cause for buggy code that might accidentally rely  on
 *     those bits never changing.
 */
#ifndef CONFIG_HEAP_RANDOMIZE_OFFSETS
#if !defined(CONFIG_NO_HEAP_RANDOMIZE_OFFSETS) && \
     defined(CONFIG_DEBUG_HEAP)
#define CONFIG_HEAP_RANDOMIZE_OFFSETS 1
#elif !defined(CONFIG_NO_HEAP_RANDOMIZE_OFFSETS)
#define CONFIG_NO_HEAP_RANDOMIZE_OFFSETS 1
#endif
#elif defined(CONFIG_NO_HEAP_RANDOMIZE_OFFSETS)
#undef CONFIG_HEAP_RANDOMIZE_OFFSETS
#endif


/* Trace dangling heap data in  order to minimize unnecessary  allocations:
 * Since the  introduction of  `CONFIG_ATOMIC_HEAP'  and it  having  become
 * mandatory shortly after, one problem arose that could potentially result
 * in unnecessary and excessive core allocations when there is still enough
 * heap memory available:
 *   - Say  you  want  to  allocate  64  bytes  of  memory.  However
 *     the  nearest   free  data   block  has   a  size   of   8Mib.
 *     Since the  heap  can't  know  how much  of  that  data  block
 *     has  already  been  faulted,  it  doesn't  want  to  run  the
 *     risk  of  keeping a  lock to  the  heap while  splitting that
 *     data block  in  2,  potentially causing  a  #PF  and  keeping
 *     a heap lock for an eternity (#PF still can happen regardless,
 *     but keeping them to a minimum is the best way to ensure heaps
 *     operating as lock-less as possible)
 *   - With that in mind, what `heap_alloc()' must do is allocate the entirety
 *     of that data  block before  releasing any portion  that isn't  actually
 *     being  used  (this is  also where  `CONFIG_HEAP_RANDOMIZE_OFFSETS' into
 *     play, as it  chooses a  random position in  that larger  data block  to
 *     return as  newly allocated  memory, rather  than always  returning  its
 *     starting address, which while be faster  as at most one remaining  data
 *     block will have to released to  the heap following the split,  degrades
 *     resilience to faulty code; see above...)
 *   - Yet  before your  thread has  finished splitting  the 8Mib data
 *     block, another  thread  wants  to allocate  more  memory,  too.
 *     Since there are  no other  data blocks sufficient  for what  it
 *     needs,  it  would have  to request  more  pages from  the core,
 *     despite the fact that ~7.995Mib are about to become free again.
 *  -> The  TRACE_DANGLE heap configuration  option fixes this problem
 *     by introducing a mechanism for tracing dangling heap allocation
 *     in the form of the  `h_dangle' dangle field of heap  structures
 *     containing  information  about those  ~7.995Mib and  allowing a
 *     thread  that wants to  allocate less than that  to wait for the
 *     first thread  to release  that  data, rather  than  immediately
 *     inquire the core for more memory.
 * NOTE: The situation described above is  quite rare, because of  which
 *       it could be argued that this option slows down heap allocations
 *       rather than speeding them up.
 *       However, since there really isn't a true upper limit to how large
 *       such  ~dangling~ blocks of memory can grow, having this turned on
 *       counteracts heap  fragmentation and  unnecessary restrictions  to
 *       system resources in situations where  large blocks of memory  are
 *       concurrently  being freed at the same time other large blocks are
 *       being allocated in other threads.
 *      (Such a situation could arise from excessive use of `fork()' and
 *       the consequentially required duplication of the caller's VM needing
 *       at  least  a   couple  of   pages  of  virtual   memory  at   once) */
#ifndef CONFIG_HEAP_TRACE_DANGLE
#ifndef CONFIG_NO_HEAP_TRACE_DANGLE
#define CONFIG_HEAP_TRACE_DANGLE 1
#endif
#elif defined(CONFIG_NO_HEAP_TRACE_DANGLE)
#undef CONFIG_HEAP_TRACE_DANGLE
#endif




/* Configuration option to enable/disable a debug functionality
 * of `kmalloc()', as well as make it much more robust than  it
 * would otherwise be:
 *   - Enable  GC-style  tracing  of  reachable  memory  blocks,  including  the   ability
 *     to  dump  the   kernel's  dynamic  memory   leaks  using  `mall_dump_leaks()',   or
 *     alternatively the user-space kernel control command `KERNEL_CONTROL_DBG_DUMP_LEAKS'
 *   - Disconnect the header containing the data block's size and allocation heap
 *     from  the data  block itself,  instead storing  that information elsewhere
 *     in  order to prevent it from being corrupted as the reuslt of invalid use.
 *   - Add a small header and tail data block surrounding every allocation
 *     that can be verified for modifications to detect array overruns, or
 *     data block underflows.
 *     Validation of the header and tail is automatically performed for a
 *     heap data  block  whenever  it  is passed  to  one  of  `kfree()',
 *    `krealloc()' (and friends) or `kmalloc_usable_size()'
 *     Alternatively, `mall_validate_padding()' or the user-space kernel
 *     control command `KERNEL_CONTROL_DBG_CHECK_PADDING' can be used to
 *     verify this ~padding~ for all allocated data blocks. */
#ifndef CONFIG_TRACE_MALLOC
#if !defined(CONFIG_NO_TRACE_MALLOC) && !defined(NDEBUG)
#define CONFIG_TRACE_MALLOC 1
#elif !defined(CONFIG_NO_TRACE_MALLOC)
#define CONFIG_NO_TRACE_MALLOC 1
#endif
#elif defined(CONFIG_NO_TRACE_MALLOC)
#undef CONFIG_TRACE_MALLOC
#endif


/* Minimum alignment of all heap pointers. */
#ifndef HEAP_ALIGNMENT
#ifdef CONFIG_HEAP_ALIGNMENT
#   define HEAP_ALIGNMENT  CONFIG_HEAP_ALIGNMENT
#elif 1
#   define HEAP_ALIGNMENT  __SIZEOF_POINTER__
#elif __SIZEOF_POINTER__ == 4/* && !defined(CONFIG_DEBUG_HEAP)*/
#   define HEAP_ALIGNMENT  8
#else
/* Using 16 allows a human to quickly notice heap pointers by realizing
 * that the  last digit  in a  hexadecimal representation  is  ZERO(0). */
#   define HEAP_ALIGNMENT 16
#endif
#endif
#if (HEAP_ALIGNMENT & (HEAP_ALIGNMENT-1))
#error "Invalid `HEAP_ALIGNMENT' must be a power-of-2 number"
#endif


/* Kernel-space dynamic memory management. */
#define __SIZEOF_GFP_T__ __SIZEOF_INT__
#ifdef __CC__
#ifndef __gfp_t_defined
#define __gfp_t_defined
typedef unsigned int gfp_t;
#endif /* !__gfp_t_defined */
#endif /* __CC__ */

#define __GFP_HEAPMASK  0x0001
#define __GFP_HEAPCOUNT 2

#define GFP_BARELY  0x0000 /* HINT: The allocated memory will barely ever be used. */

#ifndef GFP_NORMAL
#define GFP_NORMAL  0x0000 /* Allocate normal memory. */
#endif /* !GFP_NORMAL */
#define GFP_LOCKED  0x0001 /* FLAG: Allocate memory that has been locked in-core.
                            * WARNING: Do not  mix  locked  allocations  with  unlocked
                            *          ones  when  allocating   from  the  same   heap!
                            *          When  used  with  kmalloc(), this  flag  will be
                            *          used  to  choose  between  `kernel_default_heap'
                            *          and  `kernel_locked_heap',  though  when  custom
                            *          heaps are used,  or the  kernel heaps  directly,
                            *          make  sure  to always  set this  flag correctly,
                            *          as  failure to  do so  may result  in the locked
                            *          heap containing pre-allocated pages of  unlocked
                            *          memory, destroying the expectation of its memory
                            *          not  being subjugated to  the SWAP machinery, as
                            *          well as being atomic. */
#define GFP_PREFLT  0x0002 /* FLAG: Pre-fault newly allocated memory immediately, rather than upon first access.
                            * NOTE: This flag only affects newly allocated pages, but doesn't affect memory allocated from previous over-allocations! */
#define GFP_CALLOC  0x0004 /* FLAG: Allocate zero-initialized memory. (for krealloc(): only newly allocated memory is zero-initialized) */
#define GFP_NOCLRC  0x0008 /* FLAG: Don't clear kernel caches to free up memory. */
/*      GFP_        0x0010  * s.a. `GFP_MAP_FIXED' */
#define GFP_NOMMAP  0x0020 /* FLAG: Don't map more memory to serve the allocation. Only serve the request from pre-allocated pools / overallocations. */
#define GFP_NOTRIM  0x0020 /* FLAG: Don't unmap free memory blocks of sufficient size, but keep them as part of the preallocated cache. */
/*      GFP_        0x0040  * s.a. `GFP_MAP_32BIT' */
/*      GFP_        0x0080  * s.a. `GFP_MAP_PREPARED' */
/*      GFP_        0x0100  * s.a. `GFP_MAP_BELOW' */
/*      GFP_        0x0200  * s.a. `GFP_MAP_ABOVE' */
/*efine GFP_        0x0400  * ... */
#define GFP_ATOMIC  0x0800 /* FLAG: Don't block when waiting to  acquire any sort of  lock.
                            *       Instead,  failure to acquire  some required lock causes
                            *       the allocation to fail itself, either returning `NULL',
                            *       or throwing an error.
                            * NOTE: This flag is  implicitly set  during free  operations.
                            *       If a free operation then  fails to acquire some  lock,
                            *       the data-block that was meant to be freed will instead
                            *       be tracked as a pending  free, and be released at  the
                            *       nearest convenient point in time.
                            * NOTE: This flag is  very strictly enforced,  meaning that  when
                            *       passing  this flag,  you are  able to  allocate memory in
                            *       whatever situation you might find yourself in, regardless
                            *       of what locks may be  held, or whether or not  preemption
                            *       is enabled. -  If anything happens  that could cause  the
                            *       calling  thread to block, either through task_yield(), or
                            *       through `task_waitfor()', the  allocation will only  fail
                            *       by throwing an E_WOULDBLOCK  error, or returning NULL  in
                            *       NX mode. */
#define GFP_NOOVER  0x1000 /* FLAG: Don't   overallocate   memory  when   allocating   new  pages.
                            *       This  only  affects overallocation  of full  pages. Allocating
                            *       heap memory in such  a way that less  than 1 page of  overflow
                            *       remains will still produce some overflow that will be reserved
                            *       for future allocations. */
#define GFP_NOSWAP  0x2000 /* FLAG: Don't invoke the swap machinery to free up memory. */
#define GFP_MCHEAP  0x4000 /* FLAG: Allocate page controllers using the core-heap allocators. (MCoreHEAP) */
#define GFP_NOMOVE  0x8000 /* FLAG: Only for `heap_realloc()' / `heap_realign()': use `realloc_in_place()' semantics,
                            *       returning `NULL' (even  in exception-mode) when  the re-allocation is  impossible
                            *       due to an overlap with some other memory mapping. */

/* Mask of GFP flags that are inherited by recursive allocations for control structures. */
#define GFP_INHERIT                                      \
	(GFP_ATOMIC | GFP_NOOVER | GFP_NOMMAP | GFP_NOTRIM | \
	 GFP_NOSWAP | GFP_NOCLRC | GFP_MCHEAP)


#ifdef CONFIG_TRACE_MALLOC
#define GFP_NOLEAK 0x10000 /* Don't consider the data-blob a leak, even if it cannot be reached. */
#define GFP_NOWALK 0x20000 /* When searching for memory leaks, don't search the data-blob for
                            * pointers that may point to other heap-blocks. */
#else /* CONFIG_TRACE_MALLOC */
#define GFP_NOLEAK 0       /* Don't consider the data-blob a leak, even if it cannot be reached. */
#define GFP_NOWALK 0       /* When searching for memory leaks, don't search the data-blob for
                            * pointers that may point to other heap-blocks. */
#endif /* !CONFIG_TRACE_MALLOC */




#ifdef CONFIG_DEBUG_HEAP
#define SIZEOF_MFREE (__SIZE_C(5) * __SIZEOF_POINTER__ + __SIZE_C(2))
#else /* CONFIG_DEBUG_HEAP */
#define SIZEOF_MFREE (__SIZE_C(5) * __SIZEOF_POINTER__ + __SIZE_C(1))
#endif /* !CONFIG_DEBUG_HEAP */
#define HEAP_MINSIZE ((SIZEOF_MFREE + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1u))


#undef CONFIG_USE_SLAB_ALLOCATORS
#if 1
#define CONFIG_USE_SLAB_ALLOCATORS 1
#endif


#if 0 /* Only use slabs for allocations smaller than the minimum allowed allocation. */
#define SLAB_MAXSIZE   (HEAP_MINSIZE - HEAP_ALIGNMENT)
#else
#define SLAB_MAXSIZE   (__SIZE_C(8) * __SIZEOF_POINTER__)
#endif

#if SLAB_MAXSIZE < (HEAP_MINSIZE - HEAP_ALIGNMENT)
#undef SLAB_MAXSIZE
#define SLAB_MAXSIZE   (HEAP_MINSIZE - HEAP_ALIGNMENT)
#endif /* SLAB_MAXSIZE < (HEAP_MINSIZE - HEAP_ALIGNMENT) */



#if SLAB_MAXSIZE <= HEAP_ALIGNMENT
/* No point in using slab allocators now... */
#undef CONFIG_USE_SLAB_ALLOCATORS
#endif /* SLAB_MAXSIZE <= HEAP_ALIGNMENT */

#if defined(CONFIG_USE_SLAB_ALLOCATORS) || defined(__DEEMON__)
#define KERNEL_SLAB_COUNT      (SLAB_MAXSIZE / HEAP_ALIGNMENT)

/*[[[deemon
local is_first = true;
local limit = 16;
for (local align: [4, 8, 16]) {
	print is_first ? "#if" : "#elif", "HEAP_ALIGNMENT ==", align;
	is_first = false;
	print "#if KERNEL_SLAB_COUNT >=", limit + 1;
	print "#error Extend me";
	for (local x: [limit:0, -1]) {
		if (x == 1) {
			print "#else";
		} else {
			print "#elif KERNEL_SLAB_COUNT >=", x;
		}
		print "#define SLAB_FOREACH_SIZE(func, _)",;
		for (local y: [1:x + 1])
			print " func(" + (y * align) + ", _)",;
		print;
	}
	print "#endif";
}
print "#elif !defined(__DEEMON__)";
print "#error Unsupported alignment";
print "#endif";
]]]*/
#if HEAP_ALIGNMENT == 4
#if KERNEL_SLAB_COUNT >= 17
#error Extend me
#elif KERNEL_SLAB_COUNT >= 16
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _) func(32, _) func(36, _) func(40, _) func(44, _) func(48, _) func(52, _) func(56, _) func(60, _) func(64, _)
#elif KERNEL_SLAB_COUNT >= 15
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _) func(32, _) func(36, _) func(40, _) func(44, _) func(48, _) func(52, _) func(56, _) func(60, _)
#elif KERNEL_SLAB_COUNT >= 14
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _) func(32, _) func(36, _) func(40, _) func(44, _) func(48, _) func(52, _) func(56, _)
#elif KERNEL_SLAB_COUNT >= 13
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _) func(32, _) func(36, _) func(40, _) func(44, _) func(48, _) func(52, _)
#elif KERNEL_SLAB_COUNT >= 12
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _) func(32, _) func(36, _) func(40, _) func(44, _) func(48, _)
#elif KERNEL_SLAB_COUNT >= 11
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _) func(32, _) func(36, _) func(40, _) func(44, _)
#elif KERNEL_SLAB_COUNT >= 10
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _) func(32, _) func(36, _) func(40, _)
#elif KERNEL_SLAB_COUNT >= 9
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _) func(32, _) func(36, _)
#elif KERNEL_SLAB_COUNT >= 8
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _) func(32, _)
#elif KERNEL_SLAB_COUNT >= 7
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _) func(28, _)
#elif KERNEL_SLAB_COUNT >= 6
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _) func(24, _)
#elif KERNEL_SLAB_COUNT >= 5
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _) func(20, _)
#elif KERNEL_SLAB_COUNT >= 4
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _) func(16, _)
#elif KERNEL_SLAB_COUNT >= 3
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _) func(12, _)
#elif KERNEL_SLAB_COUNT >= 2
#define SLAB_FOREACH_SIZE(func, _) func(4, _) func(8, _)
#else
#define SLAB_FOREACH_SIZE(func, _) func(4, _)
#endif
#elif HEAP_ALIGNMENT == 8
#if KERNEL_SLAB_COUNT >= 17
#error Extend me
#elif KERNEL_SLAB_COUNT >= 16
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _) func(64, _) func(72, _) func(80, _) func(88, _) func(96, _) func(104, _) func(112, _) func(120, _) func(128, _)
#elif KERNEL_SLAB_COUNT >= 15
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _) func(64, _) func(72, _) func(80, _) func(88, _) func(96, _) func(104, _) func(112, _) func(120, _)
#elif KERNEL_SLAB_COUNT >= 14
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _) func(64, _) func(72, _) func(80, _) func(88, _) func(96, _) func(104, _) func(112, _)
#elif KERNEL_SLAB_COUNT >= 13
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _) func(64, _) func(72, _) func(80, _) func(88, _) func(96, _) func(104, _)
#elif KERNEL_SLAB_COUNT >= 12
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _) func(64, _) func(72, _) func(80, _) func(88, _) func(96, _)
#elif KERNEL_SLAB_COUNT >= 11
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _) func(64, _) func(72, _) func(80, _) func(88, _)
#elif KERNEL_SLAB_COUNT >= 10
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _) func(64, _) func(72, _) func(80, _)
#elif KERNEL_SLAB_COUNT >= 9
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _) func(64, _) func(72, _)
#elif KERNEL_SLAB_COUNT >= 8
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _) func(64, _)
#elif KERNEL_SLAB_COUNT >= 7
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _) func(56, _)
#elif KERNEL_SLAB_COUNT >= 6
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _) func(48, _)
#elif KERNEL_SLAB_COUNT >= 5
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _) func(40, _)
#elif KERNEL_SLAB_COUNT >= 4
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _) func(32, _)
#elif KERNEL_SLAB_COUNT >= 3
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _) func(24, _)
#elif KERNEL_SLAB_COUNT >= 2
#define SLAB_FOREACH_SIZE(func, _) func(8, _) func(16, _)
#else
#define SLAB_FOREACH_SIZE(func, _) func(8, _)
#endif
#elif HEAP_ALIGNMENT == 16
#if KERNEL_SLAB_COUNT >= 17
#error Extend me
#elif KERNEL_SLAB_COUNT >= 16
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _) func(128, _) func(144, _) func(160, _) func(176, _) func(192, _) func(208, _) func(224, _) func(240, _) func(256, _)
#elif KERNEL_SLAB_COUNT >= 15
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _) func(128, _) func(144, _) func(160, _) func(176, _) func(192, _) func(208, _) func(224, _) func(240, _)
#elif KERNEL_SLAB_COUNT >= 14
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _) func(128, _) func(144, _) func(160, _) func(176, _) func(192, _) func(208, _) func(224, _)
#elif KERNEL_SLAB_COUNT >= 13
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _) func(128, _) func(144, _) func(160, _) func(176, _) func(192, _) func(208, _)
#elif KERNEL_SLAB_COUNT >= 12
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _) func(128, _) func(144, _) func(160, _) func(176, _) func(192, _)
#elif KERNEL_SLAB_COUNT >= 11
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _) func(128, _) func(144, _) func(160, _) func(176, _)
#elif KERNEL_SLAB_COUNT >= 10
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _) func(128, _) func(144, _) func(160, _)
#elif KERNEL_SLAB_COUNT >= 9
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _) func(128, _) func(144, _)
#elif KERNEL_SLAB_COUNT >= 8
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _) func(128, _)
#elif KERNEL_SLAB_COUNT >= 7
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _) func(112, _)
#elif KERNEL_SLAB_COUNT >= 6
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _) func(96, _)
#elif KERNEL_SLAB_COUNT >= 5
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _) func(80, _)
#elif KERNEL_SLAB_COUNT >= 4
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _) func(64, _)
#elif KERNEL_SLAB_COUNT >= 3
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _) func(48, _)
#elif KERNEL_SLAB_COUNT >= 2
#define SLAB_FOREACH_SIZE(func, _) func(16, _) func(32, _)
#else
#define SLAB_FOREACH_SIZE(func, _) func(16, _)
#endif
#elif !defined(__DEEMON__)
#error Unsupported alignment
#endif
//[[[end]]]
#endif


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MALLOC_DEFS_H */
