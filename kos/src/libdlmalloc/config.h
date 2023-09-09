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


#define NO_MALLOC_FOOTPRINT 1
#define NO_INDEPENDENT_ALLOC 1
#define NO_BULK_FREE 1
#ifdef __BUILDING_LIBDL
/* Disable various functions not needed by libdl */
#undef NO_MALLINFO
#define NO_MALLINFO 1
#undef NO_MALLOPT
#define NO_MALLOPT 1
#undef NO_POSIX_MEMALIGN
#define NO_POSIX_MEMALIGN 1
#undef NO_VALLOC
#define NO_VALLOC 1
#undef NO_PVALLOC
#define NO_PVALLOC 1

/* Indicate to headers that libdl is providing its own, internal __afail */
#define __CRT_HAVE___afail 1
#define __CRT_HAVE___afailf 1
#endif /* __BUILDING_LIBDL */



/* Configure for a free-standing environment in
 * which system  calls  are  directly  invoked. */
#ifdef __BUILTIN_LIBDL
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
#endif /* __BUILTIN_LIBDL */

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
#ifndef NO_POSIX_MEMALIGN
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") int dlposix_memalign(void **pp, size_t alignment, size_t bytes);
#endif /* !NO_POSIX_MEMALIGN */
#ifndef NO_VALLOC
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void *dlvalloc(size_t bytes);
#endif /* !NO_VALLOC */
#ifndef NO_PVALLOC
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") void *dlpvalloc(size_t bytes);
#endif /* !NO_PVALLOC */
#ifndef NO_MALLOPT
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") int dlmallopt(int param_number, int value);
#endif /* !NO_MALLOPT */
#if !NO_MALLINFO
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") struct mallinfo2 dlmallinfo(void);
#endif /* !NO_MALLINFO */
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") int dlmalloc_trim(size_t pad);
DLMALLOC_EXPORT ATTR_SECTION(".text.crt.heap.malloc") size_t dlmalloc_usable_size(void *mem);

#ifdef __BUILDING_LIBC
INTDEF int NOTHROW_NCX(LIBCCALL libc_init_malloc_hooks)(void);
#define MALLOC_INIT_EXTRA_HOOK() if (libc_init_malloc_hooks()) return 0

/* Special handling needed for the initial call after hooks were installed. */
#include "../libc/user/malloc.h"
#include "../libc/user/stdlib.h"
#define HOOK_AFTER_INIT_MALLOPT(param_number, value)         libc_mallopt(param_number, value)
#define HOOK_AFTER_INIT_MALLINFO()                           libc_mallinfo2()
#define HOOK_AFTER_INIT_MALLOC(bytes)                        libc_malloc(bytes)
#define HOOK_AFTER_INIT_REALLOC(oldmem, bytes)               libc_realloc(oldmem, bytes)
#define HOOK_AFTER_INIT_MEMALIGN(alignment, bytes)           libc_memalign(alignment, bytes)
#define HOOK_AFTER_INIT_POSIX_MEMALIGN(pp, alignment, bytes) libc_posix_memalign(pp, alignment, bytes)
#define HOOK_AFTER_INIT_VALLOC(bytes)                        libc_valloc(bytes)
#define HOOK_AFTER_INIT_PVALLOC(bytes)                       libc_pvalloc(bytes)
#define HOOK_AFTER_INIT_MALLOC_TRIM(pad)                     libc_malloc_trim(pad)
#endif /* __BUILDING_LIBC */

#ifdef DL_REGISTER_CACHE
DL_REGISTER_CACHE(dl_clear_caches) {
	return dlmalloc_trim(0);
}
#endif /* DL_REGISTER_CACHE */

/* Create public exports */
#ifndef DEFINE_DL_EXPORT_ALIAS
#ifdef __BUILTIN_LIBDL
#define DEFINE_DL_EXPORT_ALIAS DEFINE_INTERN_ALIAS
#else /* __BUILTIN_LIBDL */
#define DEFINE_DL_EXPORT_ALIAS DEFINE_PUBLIC_ALIAS
#endif /* !__BUILTIN_LIBDL */
#endif /* !DEFINE_DL_EXPORT_ALIAS */

DEFINE_DL_EXPORT_ALIAS(malloc, dlmalloc);
DEFINE_DL_EXPORT_ALIAS(free, dlfree);
DEFINE_DL_EXPORT_ALIAS(calloc, dlcalloc);
DEFINE_DL_EXPORT_ALIAS(realloc, dlrealloc);
DEFINE_DL_EXPORT_ALIAS(realloc_in_place, dlrealloc_in_place);
DEFINE_DL_EXPORT_ALIAS(memalign, dlmemalign);
#ifndef NO_POSIX_MEMALIGN
DEFINE_DL_EXPORT_ALIAS(posix_memalign, dlposix_memalign);
#endif /* !NO_POSIX_MEMALIGN */
#ifndef NO_VALLOC
DEFINE_DL_EXPORT_ALIAS(valloc, dlvalloc);
#endif /* !NO_VALLOC */
#ifndef NO_PVALLOC
DEFINE_DL_EXPORT_ALIAS(pvalloc, dlpvalloc);
#endif /* !NO_PVALLOC */
#ifndef NO_MALLOPT
DEFINE_DL_EXPORT_ALIAS(mallopt, dlmallopt);
#endif /* !NO_MALLOPT */
#if !NO_MALLINFO
DEFINE_DL_EXPORT_ALIAS(mallinfo2, dlmallinfo);
#endif /* !NO_MALLINFO */
DEFINE_DL_EXPORT_ALIAS(malloc_trim, dlmalloc_trim);
DEFINE_DL_EXPORT_ALIAS(malloc_usable_size, dlmalloc_usable_size);

#ifdef __BUILDING_LIBC
#undef __libc_malloc
#undef __libc_calloc
#undef __builtin_delete
#undef __libc_free
#undef __libc_realloc
#undef __libc_memalign
#undef __libc_valloc
DEFINE_DL_EXPORT_ALIAS(cfree, dlfree);
DEFINE_DL_EXPORT_ALIAS(aligned_alloc, dlmemalign);
DEFINE_DL_EXPORT_ALIAS(__libc_malloc, dlmalloc);
DEFINE_DL_EXPORT_ALIAS(__builtin_delete, dlfree);
DEFINE_DL_EXPORT_ALIAS(__libc_free, dlfree);
DEFINE_DL_EXPORT_ALIAS(__libc_calloc, dlcalloc);
DEFINE_DL_EXPORT_ALIAS(__libc_realloc, dlrealloc);
DEFINE_DL_EXPORT_ALIAS(__libc_memalign, dlmemalign);
DEFINE_DL_EXPORT_ALIAS(__libc_valloc, dlvalloc);
DEFINE_DL_EXPORT_ALIAS(__libc_mallopt, dlmallopt);
DEFINE_DL_EXPORT_ALIAS(__libc_pvalloc, dlpvalloc);
DEFINE_DL_EXPORT_ALIAS(_msize, dlmalloc_usable_size);
DEFINE_DL_EXPORT_ALIAS(_msize_debug, dlmalloc_usable_size);

#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
DEFINE_DL_EXPORT_ALIAS(__libc_mallinfo, dlmallinfo);
DEFINE_DL_EXPORT_ALIAS(mallinfo, dlmallinfo);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
DEFINE_DL_EXPORT_ALIAS(__libc_mallinfo, libc_mallinfo_int);
DEFINE_DL_EXPORT_ALIAS(mallinfo, libc_mallinfo_int);
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#endif /* __BUILDING_LIBC */
#undef DEFINE_DL_EXPORT_ALIAS


/* Also create libc-overrides exports
 * -> This allows libc internals to use our malloc functions
 *    if libc happens to be combined with our library within
 *    a static link (such as  is the case when building  the
 *    dynamic linker binary blobs) */
#ifdef __BUILDING_LIBC
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
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
DEFINE_INTERN_ALIAS(libc_mallinfo, dlmallinfo);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
DEFINE_INTERN_ALIAS(libc_mallinfo, libc_mallinfo_int);
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
DEFINE_INTERN_ALIAS(libc_mallinfo2, dlmallinfo);
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

/* Old aliases from Glibc 2.0.4 */
DEFINE_PUBLIC_ALIAS(__free, libc_free);
DEFINE_PUBLIC_ALIAS(__cfree, libc_free);
DEFINE_PUBLIC_ALIAS(__malloc, libc_malloc);
DEFINE_PUBLIC_ALIAS(__calloc, libc_calloc);
DEFINE_PUBLIC_ALIAS(__realloc, libc_realloc);
DEFINE_PUBLIC_ALIAS(__malloc_usable_size, libc_malloc_usable_size);
DEFINE_PUBLIC_ALIAS(__pvalloc, libc_pvalloc);
DEFINE_PUBLIC_ALIAS(__valloc, libc_valloc);
DEFINE_PUBLIC_ALIAS(__mallinfo, libc_mallinfo);
DEFINE_PUBLIC_ALIAS(__mallopt, libc_mallopt);
DEFINE_PUBLIC_ALIAS(__malloc_trim, libc_malloc_trim);
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

__pragma_GCC_diagnostic_ignored(Wsuggest_attribute_pure)
__pragma_GCC_diagnostic_ignored(Wsuggest_attribute_const)
__pragma_GCC_diagnostic_ignored(Wsuggest_attribute_cold)

#endif /* !GUARD_LIBDLMALLOC_CONFIG_H */
