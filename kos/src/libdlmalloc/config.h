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
#ifndef GUARD_LIBDLMALLOC_CONFIG_H
#define GUARD_LIBDLMALLOC_CONFIG_H 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

/* Configure dlmalloc.c */
#undef WIN32
#undef _WIN32
#undef _WIN32_WCE
#define DLMALLOC_EXPORT INTDEF
#define MALLOC_ALIGNMENT __LIBC_MALLOC_ALIGNMENT
#undef MSPACES
#undef ONLY_MSPACES
#define USE_LOCKS 1
#define USE_SPIN_LOCKS 1
/* FIXME: Recursion is possible in:
 *        locked:malloc()
 *        mmap()
 *        dlclearcaches()
 *        DL_REGISTER_CACHE(my_cache_free_function)
 *        my_cache_free_function()
 *        locked:free()    <--- Deadlock here
 * NOTE: A proper fix  for this  would implement  a free()  that is  non-blocking
 *       and reentrant, however  dlmalloc cannot be  bend to do  this for us,  so
 *       Another would be  enabling `USE_RECURSIVE_LOCKS'  and somehow  providing
 *       a custom lock implementation that  doesn't make use of  `pthread_self()'
 *       (which can't be used since `pthread_self()' itself might call `malloc()'
 *       to  allocate the thread-self  descriptor of a  thread created via direct
 *       invocation of the  clone() system call,  or via use  of a threading  API
 *       not built ontop of pthreads).  However, given how useful a  non-blocking
 *       free function is  in kernel-space,  it only seems  fair that  user-space
 *       should eventually  get its  own  hand-written heap  implementation  that
 *       also  contains such a free function, alongside some more neat extension.
 */
#undef USE_RECURSIVE_LOCKS
#undef LOCK_AT_FORK
#undef FOOTERS
#ifdef NDEBUG
#define INSECURE 1
#else /* NDEBUG */
#undef INSECURE
#endif /* !NDEBUG */
#define USE_DL_PREFIX 1
#undef MALLOC_INSPECT_ALL
#undef ABORT
#define MALLOC_FAILURE_ACTION (void)0; /* nothing... */
#define HAVE_MORECORE 0
#undef MORECORE
#undef MORECORE_CONTIGUOUS
#undef MORECORE_CANNOT_TRIM
#undef NO_SEGMENT_TRAVERSAL
#define HAVE_MMAP 1
#define HAVE_MREMAP 1
#define MMAP_CLEARS 1
#define USE_BUILTIN_FFS 1
#define USE_DEV_RANDOM 0
#define NO_MALLINFO 0
#define MALLINFO_FIELD_TYPE size_t
#define NO_MALLOC_STATS 1 /* Disable to prevent relocation against `stderr' */
#define ABORT __assertion_failed("abort()")
#undef REALLOC_ZERO_BYTES_FREES
#undef DEFAULT_GRANULARITY
#undef DEFAULT_TRIM_THRESHOLD
#undef DEFAULT_MMAP_THRESHOLD
#undef MAX_RELEASE_CHECK_RATE

/* We've got all of these! */
#undef LACKS_UNISTD_H
#undef LACKS_FCNTL_H
#undef LACKS_SYS_PARAM_H
#undef LACKS_SYS_MMAN_H
#undef LACKS_STRINGS_H
#undef LACKS_STRING_H
#undef LACKS_SYS_TYPES_H
#undef LACKS_ERRNO_H
#undef LACKS_STDLIB_H
#undef LACKS_SCHED_H
#undef LACKS_TIME_H

#define FORCEINLINE   FORCELOCAL
#define NOINLINE      ATTR_NOINLINE



/* Configure for a free-standing environment in
 * which system  calls  are  directly  invoked. */
#ifdef CONFIG_DLMALLOC_FREESTANDING_SYSTEM_CALLS
#undef __CRT_FREESTANDING
#undef __WANT_INLINE_SYSCALLS
#define __CRT_FREESTANDING     1
#define __WANT_INLINE_SYSCALLS 1
#include <kos/syscalls.h>
#if __CRT_HAVE_SC(time)
#define time(p) sys_time(p)
#else /* time */
#define time(p) ((p) ? (*(p) = 42) : 42)
#endif /* !time */
#if __CRT_HAVE_SC(sched_yield)
#define sched_yield() sys_sched_yield()
#else /* sched_yield */
#define sched_yield() (void)0
#endif /* !sched_yield */
#define mmap(hint, size, prot, flags, fd, offset) sys_mmap(hint, size, prot, flags, fd, offset)
#define munmap(addr, size)                        sys_munmap(addr, size)
#define mremap(addr, osz, nsz, mv)                sys_mremap(addr, osz, nsz, mv, 0)
#endif /* CONFIG_DLMALLOC_FREESTANDING_SYSTEM_CALLS */

#include <__crt.h>
#include <hybrid/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <asm/crt/malloc.h>
#include <asm/pagesize.h>
#include <bits/crt/mallinfo.h>
#include <kos/config/config.h> /* Pull in config-specific macro overrides */

#include <assert.h>
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>

/* Configure dlmalloc to be a lot more tame in regards to allocations */
#define DEFAULT_GRANULARITY    (2048 * __SIZEOF_POINTER__)
#define DEFAULT_TRIM_THRESHOLD 4096
#define DEFAULT_MMAP_THRESHOLD 16384
#define MAX_RELEASE_CHECK_RATE 511

#ifdef __ARCH_PAGESIZE
#define MALLOC_PAGESIZE    __ARCH_PAGESIZE
#define malloc_getpagesize __ARCH_PAGESIZE
#if DEFAULT_GRANULARITY < __ARCH_PAGESIZE
#undef DEFAULT_GRANULARITY
#define DEFAULT_GRANULARITY __ARCH_PAGESIZE
#endif /* DEFAULT_GRANULARITY < __ARCH_PAGESIZE */
#if DEFAULT_TRIM_THRESHOLD < __ARCH_PAGESIZE
#undef DEFAULT_TRIM_THRESHOLD
#define DEFAULT_TRIM_THRESHOLD __ARCH_PAGESIZE
#endif /* DEFAULT_TRIM_THRESHOLD < __ARCH_PAGESIZE */
#else /* __ARCH_PAGESIZE */
#define malloc_getpagesize getpagesize()
#endif /* !__ARCH_PAGESIZE */

#if MALLOC_ALIGNMENT < 8
#undef MALLOC_ALIGNMENT
#define MALLOC_ALIGNMENT 8
#endif /* MALLOC_ALIGNMENT < 8 */

DECL_BEGIN

/* Declare exported functions within individual sections. */

DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void *dlmalloc(size_t bytes);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void dlfree(void *mem);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void *dlcalloc(size_t n_elements, size_t elem_size);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void *dlrealloc(void *oldmem, size_t bytes);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void *dlrealloc_in_place(void *oldmem, size_t bytes);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void *dlmemalign(size_t alignment, size_t bytes);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") int dlposix_memalign(void **pp, size_t alignment, size_t bytes);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void *dlvalloc(size_t bytes);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") int dlmallopt(int param_number, int value);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") size_t dlmalloc_footprint(void);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") size_t dlmalloc_max_footprint(void);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") size_t dlmalloc_footprint_limit(void);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") size_t dlmalloc_set_footprint_limit(size_t bytes);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") struct mallinfo2 dlmallinfo(void);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void **dlindependent_calloc(size_t n_elements, size_t elem_size, void *chunks[]);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void **dlindependent_comalloc(size_t n_elements, size_t sizes[], void *chunks[]);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") size_t dlbulk_free(void *array[], size_t nelem);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void *dlpvalloc(size_t bytes);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") int dlmalloc_trim(size_t pad);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") size_t dlmalloc_usable_size(void *mem);

#ifdef DL_REGISTER_CACHE
DL_REGISTER_CACHE(dl_clear_caches) {
	return dlmalloc_trim(0);
}
#endif /* DL_REGISTER_CACHE */

/* Create public exports */
#ifndef DEFINE_DL_EXPORT_ALIAS
#ifdef CONFIG_DLMALLOC_EXPORT_AS_INTERN
#define DEFINE_DL_EXPORT_ALIAS DEFINE_INTERN_ALIAS
#else /* CONFIG_DLMALLOC_EXPORT_AS_INTERN */
#define DEFINE_DL_EXPORT_ALIAS DEFINE_PUBLIC_ALIAS
#endif /* !CONFIG_DLMALLOC_EXPORT_AS_INTERN */
#endif /* !DEFINE_DL_EXPORT_ALIAS */

#undef __libc_malloc
#undef __libc_calloc
#undef __builtin_delete
#undef __libc_free
#undef __libc_realloc
#undef __libc_memalign
#undef __libc_valloc
DEFINE_DL_EXPORT_ALIAS(__libc_malloc, dlmalloc);
DEFINE_DL_EXPORT_ALIAS(malloc, dlmalloc);
DEFINE_DL_EXPORT_ALIAS(__builtin_delete, dlfree);
DEFINE_DL_EXPORT_ALIAS(__libc_free, dlfree);
DEFINE_DL_EXPORT_ALIAS(free, dlfree);
DEFINE_DL_EXPORT_ALIAS(cfree, dlfree);
DEFINE_DL_EXPORT_ALIAS(__libc_calloc, dlcalloc);
DEFINE_DL_EXPORT_ALIAS(calloc, dlcalloc);
DEFINE_DL_EXPORT_ALIAS(__libc_realloc, dlrealloc);
DEFINE_DL_EXPORT_ALIAS(realloc, dlrealloc);
DEFINE_DL_EXPORT_ALIAS(realloc_in_place, dlrealloc_in_place);
DEFINE_DL_EXPORT_ALIAS(__libc_memalign, dlmemalign);
DEFINE_DL_EXPORT_ALIAS(memalign, dlmemalign);
DEFINE_DL_EXPORT_ALIAS(aligned_alloc, dlmemalign);
DEFINE_DL_EXPORT_ALIAS(posix_memalign, dlposix_memalign);
DEFINE_DL_EXPORT_ALIAS(__libc_valloc, dlvalloc);
DEFINE_DL_EXPORT_ALIAS(valloc, dlvalloc);
DEFINE_DL_EXPORT_ALIAS(__libc_mallopt, dlmallopt);
DEFINE_DL_EXPORT_ALIAS(mallopt, dlmallopt);
DEFINE_DL_EXPORT_ALIAS(malloc_footprint, dlmalloc_footprint);
DEFINE_DL_EXPORT_ALIAS(malloc_max_footprint, dlmalloc_max_footprint);
DEFINE_DL_EXPORT_ALIAS(malloc_footprint_limit, dlmalloc_footprint_limit);
DEFINE_DL_EXPORT_ALIAS(malloc_set_footprint_limit, dlmalloc_set_footprint_limit);
#ifdef __BUILDING_LIBC
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
DEFINE_DL_EXPORT_ALIAS(__libc_mallinfo, dlmallinfo);
DEFINE_DL_EXPORT_ALIAS(mallinfo, dlmallinfo);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
DEFINE_DL_EXPORT_ALIAS(__libc_mallinfo, libc_mallinfo_int);
DEFINE_DL_EXPORT_ALIAS(mallinfo, libc_mallinfo_int);
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#endif /* __BUILDING_LIBC */
DEFINE_DL_EXPORT_ALIAS(mallinfo2, dlmallinfo);
DEFINE_DL_EXPORT_ALIAS(independent_calloc, dlindependent_calloc);
DEFINE_DL_EXPORT_ALIAS(independent_comalloc, dlindependent_comalloc);
DEFINE_DL_EXPORT_ALIAS(bulk_free, dlbulk_free);
DEFINE_DL_EXPORT_ALIAS(__libc_pvalloc, dlpvalloc);
DEFINE_DL_EXPORT_ALIAS(pvalloc, dlpvalloc);
DEFINE_DL_EXPORT_ALIAS(malloc_trim, dlmalloc_trim);
DEFINE_DL_EXPORT_ALIAS(malloc_usable_size, dlmalloc_usable_size);
DEFINE_DL_EXPORT_ALIAS(_msize, dlmalloc_usable_size);
#undef DEFINE_DL_EXPORT_ALIAS

/* Also create libc-overrides exports
 * -> This allows libc internals to use our malloc functions
 *    if libc happens to be combined with our library within
 *    a static link (such as  is the case when building  the
 *    dynamic linker binary blobs) */
DEFINE_INTERN_ALIAS(libc_malloc, dlmalloc);
DEFINE_INTERN_ALIAS(libc_free, dlfree);
DEFINE_INTERN_ALIAS(libc_cfree, dlfree);
DEFINE_INTERN_ALIAS(libc_calloc, dlcalloc);
DEFINE_INTERN_ALIAS(libc_realloc, dlrealloc);
DEFINE_INTERN_ALIAS(libc_realloc_in_place, dlrealloc_in_place);
DEFINE_INTERN_ALIAS(libc_memalign, dlmemalign);
DEFINE_INTERN_ALIAS(libc_posix_memalign, dlposix_memalign);
DEFINE_INTERN_ALIAS(libc_valloc, dlvalloc);
DEFINE_INTERN_ALIAS(libc_mallopt, dlmallopt);
DEFINE_INTERN_ALIAS(libc_malloc_footprint, dlmalloc_footprint);
DEFINE_INTERN_ALIAS(libc_malloc_max_footprint, dlmalloc_max_footprint);
DEFINE_INTERN_ALIAS(libc_malloc_footprint_limit, dlmalloc_footprint_limit);
DEFINE_INTERN_ALIAS(libc_malloc_set_footprint_limit, dlmalloc_set_footprint_limit);
#ifdef __BUILDING_LIBC
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
DEFINE_INTERN_ALIAS(libc_mallinfo, dlmallinfo);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
DEFINE_INTERN_ALIAS(libc_mallinfo, libc_mallinfo_int);
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#endif /* __BUILDING_LIBC */
DEFINE_INTERN_ALIAS(libc_mallinfo2, dlmallinfo);
DEFINE_INTERN_ALIAS(libc_independent_calloc, dlindependent_calloc);
DEFINE_INTERN_ALIAS(libc_independent_comalloc, dlindependent_comalloc);
DEFINE_INTERN_ALIAS(libc_bulk_free, dlbulk_free);
DEFINE_INTERN_ALIAS(libc_pvalloc, dlpvalloc);
DEFINE_INTERN_ALIAS(libc_malloc_trim, dlmalloc_trim);
DEFINE_INTERN_ALIAS(libc_malloc_usable_size, dlmalloc_usable_size);

#if __SIZEOF_INT__ != __SIZEOF_SIZE_T__
INTERN ATTR_SECTION(".text.crt.heap.malloc")
struct mallinfo libc_mallinfo_int(void) {
	struct mallinfo2 info = dlmallinfo();
	struct mallinfo result;
	result.arena    = (int)(unsigned int)info.arena;
	result.ordblks  = (int)(unsigned int)info.ordblks;
	result.smblks   = (int)(unsigned int)info.smblks;
	result.hblks    = (int)(unsigned int)info.hblks;
	result.hblkhd   = (int)(unsigned int)info.hblkhd;
	result.usmblks  = (int)(unsigned int)info.usmblks;
	result.fsmblks  = (int)(unsigned int)info.fsmblks;
	result.uordblks = (int)(unsigned int)info.uordblks;
	result.fordblks = (int)(unsigned int)info.fordblks;
	result.keepcost = (int)(unsigned int)info.keepcost;
	return result;
}
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#ifdef __BUILDING_LIBC
#endif /* __BUILDING_LIBC */


/* Have dlmalloc implement `mallinfo2(3)' */
#undef mallinfo
#define mallinfo mallinfo2
#define STRUCT_MALLINFO_DECLARED
#define MALLINFO_FIELD_TYPE size_t

/* Override the command IDs used by `mallopt(3)' */
#define M_TRIM_THRESHOLD __M_TRIM_THRESHOLD
#define M_GRANULARITY    __M_GRANULARITY
#define M_MMAP_THRESHOLD __M_MMAP_THRESHOLD

DECL_END

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wsuggest-attribute=pure"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=const"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=cold"
#endif /* __GNUC__ */

#endif /* !GUARD_LIBDLMALLOC_CONFIG_H */
