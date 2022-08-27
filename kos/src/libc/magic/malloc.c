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
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/malloc.h) */
/* (#) Portability: DJGPP         (/include/malloc.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/malloc.h) */
/* (#) Portability: FreeBSD       (/include/malloc.h) */
/* (#) Portability: GNU C Library (/malloc/malloc.h) */
/* (#) Portability: MSVC          (/include/malloc.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/malloc.h) */
/* (#) Portability: NetBSD        (/include/malloc.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/malloc.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/malloc.h) */
/* (#) Portability: Windows Kits  (/ucrt/malloc.h) */
/* (#) Portability: diet libc     (/include/malloc.h) */
/* (#) Portability: libc4/5       (/include/malloc.h) */
/* (#) Portability: libc6         (/include/malloc.h) */
/* (#) Portability: mintlib       (/include/malloc.h) */
/* (#) Portability: musl libc     (/include/malloc.h) */
/* (#) Portability: uClibc        (/include/malloc.h) */
}

%[default:section(".text.crt{|.dos}.heap.malloc")]

%[define_decl_include("<bits/crt/mallinfo.h>": [
	"struct mallinfo",
	"struct mallinfo2"
])]

%(libc_fast,libc_core){
#include "stdlib.h"
}

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/crt/malloc.h>
)]%[insert:prefix(
#include <bits/crt/mallinfo.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{
#if defined(__USE_KOS) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/__overflow.h>
#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */
#endif /* __USE_KOS && __USE_STRING_OVERLOADS */

/* Options for `mallopt(3)' */
#if !defined(M_MXFAST) && defined(__M_MXFAST)
#define M_MXFAST __M_MXFAST
#endif /* !M_MXFAST && __M_MXFAST */
#if !defined(M_NLBLKS) && defined(__M_NLBLKS)
#define M_NLBLKS __M_NLBLKS
#endif /* !M_NLBLKS && __M_NLBLKS */
#if !defined(M_GRAIN) && defined(__M_GRAIN)
#define M_GRAIN __M_GRAIN
#endif /* !M_GRAIN && __M_GRAIN */
#if !defined(M_KEEP) && defined(__M_KEEP)
#define M_KEEP __M_KEEP
#endif /* !M_KEEP && __M_KEEP */
#if !defined(M_TRIM_THRESHOLD) && defined(__M_TRIM_THRESHOLD)
#define M_TRIM_THRESHOLD __M_TRIM_THRESHOLD
#endif /* !M_TRIM_THRESHOLD && __M_TRIM_THRESHOLD */
#if !defined(M_GRANULARITY) && defined(__M_GRANULARITY)
#define M_GRANULARITY __M_GRANULARITY
#endif /* !M_GRANULARITY && __M_GRANULARITY */
#if !defined(M_MMAP_THRESHOLD) && defined(__M_MMAP_THRESHOLD)
#define M_MMAP_THRESHOLD __M_MMAP_THRESHOLD
#endif /* !M_MMAP_THRESHOLD && __M_MMAP_THRESHOLD */
#if !defined(M_TOP_PAD) && defined(__M_TOP_PAD)
#define M_TOP_PAD __M_TOP_PAD
#endif /* !M_TOP_PAD && __M_TOP_PAD */
#if !defined(M_MMAP_MAX) && defined(__M_MMAP_MAX)
#define M_MMAP_MAX __M_MMAP_MAX
#endif /* !M_MMAP_MAX && __M_MMAP_MAX */
#if !defined(M_CHECK_ACTION) && defined(__M_CHECK_ACTION)
#define M_CHECK_ACTION __M_CHECK_ACTION
#endif /* !M_CHECK_ACTION && __M_CHECK_ACTION */
#if !defined(M_PERTURB) && defined(__M_PERTURB)
#define M_PERTURB __M_PERTURB
#endif /* !M_PERTURB && __M_PERTURB */
#if !defined(M_ARENA_TEST) && defined(__M_ARENA_TEST)
#define M_ARENA_TEST __M_ARENA_TEST
#endif /* !M_ARENA_TEST && __M_ARENA_TEST */
#if !defined(M_ARENA_MAX) && defined(__M_ARENA_MAX)
#define M_ARENA_MAX __M_ARENA_MAX
#endif /* !M_ARENA_MAX && __M_ARENA_MAX */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}

%[insert:std]

%[insert:guarded_std_function(malloc)]
%[insert:guarded_std_function(calloc)]
%[insert:guarded_std_function(realloc)]
%[insert:guarded_std_function(free)]




@@>> realloc_in_place(3)
@@`realloc_in_place(3)' will return `NULL' if the reallocation isn't
@@possible due to the requested memory above `mallptr' already being
@@in use. However, NULL is also returned (and `errno=ENOMEM' is set)
@@if  insufficient  memory  (for  internal  control  structures)  is
@@available to complete the operation.
[[libc, guard, dos_only_export_alias("_expand")]]
[[ATTR_MALL_DEFAULT_ALIGNED, ATTR_ALLOC_SIZE((2))]]
[[section(".text.crt{|.dos}.heap.helpers"), decl_include("<hybrid/typecore.h>")]]
void *realloc_in_place(void *__restrict mallptr, size_t n_bytes);

[[ignore, nocrt, alias("posix_memalign"), decl_include("<hybrid/typecore.h>")]]
int crt_posix_memalign([[out]] void **__restrict pp,
                       size_t alignment, size_t n_bytes);

[[guard, wunused, ATTR_ALLOC_ALIGN(1), ATTR_ALLOC_SIZE((2))]]
[[ATTR_MALLOC, export_alias("aligned_alloc", "__libc_memalign"), decl_include("<hybrid/typecore.h>")]]
[[if(__has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("aligned_alloc", { return __builtin_aligned_alloc(alignment, n_bytes); })]]
[[userimpl, requires_function(crt_posix_memalign)]]
void *memalign(size_t alignment, size_t n_bytes) {
	void *result;
	if (crt_posix_memalign(&result, alignment, n_bytes))
		return NULL;
	return result;
}


[[wunused, ATTR_MALL_PAGEALIGNED, ATTR_ALLOC_SIZE((1)), ATTR_MALLOC]]
[[section(".text.crt{|.dos}.heap.rare_helpers"), decl_include("<hybrid/typecore.h>")]]
void *pvalloc(size_t n_bytes);

[[decl_include("<hybrid/typecore.h>"), export_alias("__libc_valloc")]]
[[guard, wunused, ATTR_MALL_PAGEALIGNED, ATTR_ALLOC_SIZE((1))]]
[[section(".text.crt{|.dos}.heap.rare_helpers"), userimpl, requires($has_function(memalign))]]
void *valloc($size_t n_bytes) {
	return memalign(getpagesize(), n_bytes);
}

[[guard, crtbuiltin, decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.heap.rare_helpers"), impl_include("<libc/errno.h>")]]
[[userimpl, requires_function(memalign)]]
$errno_t posix_memalign([[out]] void **__restrict pp,
                        $size_t alignment, $size_t n_bytes) {
	void *result;
	size_t d = alignment / sizeof(void *);
	size_t r = alignment % sizeof(void *);
	if (r != 0 || !d || (d & (d - 1)) != 0) {
@@pp_ifdef EINVAL@@
		return EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	result = memalign(alignment, n_bytes);
	if (!result) {
@@pp_ifdef ENOMEM@@
		return ENOMEM;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	*pp = result;
	return 0;
}

[[guard]]
cfree(*) = free;


[[ignore, nocrt, alias("_heapmin")]]
int _heapmin();


[[decl_include("<hybrid/typecore.h>")]]
[[userimpl, section(".text.crt{|.dos}.heap.utility")]]
int malloc_trim(size_t pad) {
@@pp_ifdef __BUILDING_LIBC@@
	/* NO-OP (indicate failure to release memory) */
	COMPILER_IMPURE();
	(void)pad;
	return 0;
@@pp_elif $has_function(_heapmin)@@
	(void)pad;
	return _heapmin() ? 1 : 0;
@@pp_else@@
	/* NO-OP (indicate failure to release memory) */
	COMPILER_IMPURE();
	(void)pad;
	return 0;
@@pp_endif@@
}

[[libc, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[guard, dos_only_export_alias("_msize")]]
/* NOTE: `_msize_debug()' only appears in `msvcrt.dll', but disassembly shows it
 *       just calls forward to the regular `_msize()'. I'm guessing the idea was
 *       to set a breakpoint on `_msize_debug()'s entry, and only code that uses
 *       that function trigger said breakpoint?
 * However, for safety we still only export this symbol, but don't bind it in headers. */
[[dos_only_export_as("_msize_debug")]]
[[section(".text.crt{|.dos}.heap.helpers")]]
size_t malloc_usable_size(void *__restrict mallptr);

[[userimpl, section(".text.crt{|.dos}.heap.utility")]]
int mallopt(int parameter_number, int parameter_value) {
	/* NO-OP */
	COMPILER_IMPURE();
	(void)parameter_number;
	(void)parameter_value;
	return 0;
}

%[insert:function(__memdup = memdup)]
%[insert:function(__memcdup = memcdup)]

%
%#ifdef __USE_KOS
[[export_alias("__memdup"), decl_include("<hybrid/typecore.h>")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((2))]]
[[section(".text.crt{|.dos}.heap.rare_helpers"), userimpl, requires_function(malloc)]]
void *memdup([[in(n_bytes)]] void const *__restrict ptr, size_t n_bytes) {
	void *result;
	result = malloc(n_bytes);
	if likely(result)
		memcpy(result, ptr, n_bytes);
	return result;
}

[[export_alias("__memcdup"), decl_include("<hybrid/typecore.h>")]]
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC, ATTR_ALLOC_SIZE((2))]]
[[section(".text.crt{|.dos}.heap.rare_helpers"), userimpl, requires_function(memdup)]]
void *memcdup([[in(? <= n_bytes)]] void const *__restrict ptr, int needle, size_t n_bytes) {
	if likely(n_bytes) {
		void const *endaddr;
		endaddr = memchr(ptr, needle, n_bytes - 1);
		if (endaddr)
			n_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
	}
	return memdup(ptr, n_bytes);
}

[[guard, wunused, ATTR_MALL_DEFAULT_ALIGNED]]
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("reallocarr")]]
[[userimpl, requires_function(realloc)]]
[[impl_include("<hybrid/__overflow.h>")]]
[[section(".text.crt{|.dos}.heap.rare_helpers")]]
reallocarray(void *ptr, $size_t elem_count, $size_t elem_size)
		-> [[realloc(mallptr, elem_count * elem_size)]] void * {
	size_t total_bytes;
	if unlikely(__hybrid_overflow_umul(elem_count, elem_size, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	return realloc(ptr, total_bytes);
}

[[guard]] reallocv(*) = reallocarray;

[[guard, decl_include("<hybrid/typecore.h>")]]
[[userimpl, requires_function(realloc, malloc_usable_size)]]
[[section(".text.crt{|.dos}.heap.rare_helpers")]]
recalloc(void *mallptr, $size_t num_bytes)
		-> [[realloc(mallptr, num_bytes)]] void * {
	void *result;
	size_t oldsize;
	oldsize = malloc_usable_size(mallptr);
	result  = realloc(mallptr, num_bytes);
	if likely(result) {
		if (num_bytes > oldsize)
			bzero((byte_t *)result + oldsize, num_bytes - oldsize);
	}
	return result;
}


[[guard, export_alias("_recalloc"), decl_include("<hybrid/typecore.h>")]]
[[userimpl, requires_function(realloc, malloc_usable_size)]]
[[section(".text.crt{|.dos}.heap.rare_helpers"), impl_include("<hybrid/__overflow.h>")]]
recallocv(void *mallptr, $size_t elem_count, $size_t elem_size)
		-> [[realloc(mallptr, elem_count * elem_size)]] void * {
	void *result;
	size_t total_bytes, oldsize;
	oldsize = malloc_usable_size(mallptr);
	if unlikely(__hybrid_overflow_umul(elem_count, elem_size, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	result = realloc(mallptr, total_bytes);
	if likely(result) {
		if (total_bytes > oldsize)
			bzero((byte_t *)result + oldsize, total_bytes - oldsize);
	}
	return result;
}


%
%#ifdef __USE_STRING_OVERLOADS
%#ifndef __MALLOC_OVERLOADS_DEFINED
%#define __MALLOC_OVERLOADS_DEFINED 1
%{
#ifdef __malloc_defined
__NAMESPACE_LOCAL_BEGIN
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2))
void *__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mallocv))(size_t __elem_count, size_t __elem_size) {
	size_t __total_size;
	if __unlikely(__hybrid_overflow_umul(__elem_count, __elem_size, &__total_size))
		__total_size = (size_t)-1; /* Force down-stream failure */
	return (malloc)(__total_size);
}
__NAMESPACE_LOCAL_END
#endif /* __malloc_defined */
}
%#ifdef __cplusplus
%extern "C++" {
%{
#ifdef __malloc_defined
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2))
void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __elem_count, size_t __elem_size) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallocv)(__elem_count, __elem_size); }
#endif /* __malloc_defined */
#ifdef __calloc_defined
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1))
void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __num_bytes) { return (calloc)(1, __num_bytes); }
#endif /* __calloc_defined */
}
%} /* extern "C++" */
%[insert:function(realloc = reallocarray, externLinkageOverride: "C++")]
%[insert:function(recalloc = recallocv, externLinkageOverride: "C++")]
%#elif defined(__HYBRID_PP_VA_OVERLOAD)
%{
#ifdef __malloc_defined
#define __PRIVATE_malloc_1 (malloc)
#define __PRIVATE_malloc_2 __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallocv)
#undef malloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define malloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define malloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloc_, (args))(args)
#endif /* ... */
#endif /* __malloc_defined */
#ifdef __calloc_defined
#define __PRIVATE_calloc_1(num_bytes) (calloc)(1, num_bytes)
#define __PRIVATE_calloc_2            (calloc)
#undef calloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define calloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define calloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloc_, (args))(args)
#endif /* ... */
#endif /* __calloc_defined */
#if defined(__realloc_defined) && defined(__reallocarray_defined)
#define __PRIVATE_realloc_2 (realloc)
#define __PRIVATE_realloc_3 (reallocarray)
#undef realloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define realloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_realloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define realloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_realloc_, (args))(args)
#endif /* ... */
#endif /* __realloc_defined && __reallocarray_defined */
#if defined(__recalloc_defined) && defined(__recallocv_defined)
#define __PRIVATE_recalloc_2 (recalloc)
#define __PRIVATE_recalloc_3 (recallocv)
#undef recalloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define recalloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_recalloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define recalloc(aargs...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_recalloc_, (args))(args)
#endif /* ... */
#endif /* __recalloc_defined && __recallocv_defined */
}
%#endif /* ... */
%#endif /* !__MALLOC_OVERLOADS_DEFINED */
%#endif /* __USE_STRING_OVERLOADS */
%#endif /* __USE_KOS */



[[decl_include("<bits/crt/mallinfo.h>")]]
[[ignore, nocrt, alias("mallinfo")]]
struct mallinfo crt_mallinfo(void);

[[decl_include("<bits/crt/mallinfo.h>")]]
[[ignore, nocrt, alias("mallinfo2")]]
struct mallinfo2 crt_mallinfo2(void);


[[decl_include("<bits/crt/mallinfo.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_SIZE_T__), alias("mallinfo2")]]
[[userimpl, requires_function(crt_mallinfo2)]]
struct mallinfo mallinfo(void) {
	struct mallinfo result;
	struct mallinfo2 info = crt_mallinfo2();
	result.@arena@    = (int)(unsigned int)info.@arena@;
	result.@ordblks@  = (int)(unsigned int)info.@ordblks@;
	result.@smblks@   = (int)(unsigned int)info.@smblks@;
	result.@hblks@    = (int)(unsigned int)info.@hblks@;
	result.@hblkhd@   = (int)(unsigned int)info.@hblkhd@;
	result.@usmblks@  = (int)(unsigned int)info.@usmblks@;
	result.@fsmblks@  = (int)(unsigned int)info.@fsmblks@;
	result.@uordblks@ = (int)(unsigned int)info.@uordblks@;
	result.@fordblks@ = (int)(unsigned int)info.@fordblks@;
	result.@keepcost@ = (int)(unsigned int)info.@keepcost@;
	return result;
}

[[decl_include("<bits/crt/mallinfo.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_SIZE_T__), preferred_alias("mallinfo")]]
[[userimpl, requires_function(crt_mallinfo)]]
struct mallinfo2 mallinfo2(void) {
	struct mallinfo2 result;
	struct mallinfo info = crt_mallinfo();
	result.@arena@    = (size_t)(unsigned int)info.@arena@;
	result.@ordblks@  = (size_t)(unsigned int)info.@ordblks@;
	result.@smblks@   = (size_t)(unsigned int)info.@smblks@;
	result.@hblks@    = (size_t)(unsigned int)info.@hblks@;
	result.@hblkhd@   = (size_t)(unsigned int)info.@hblkhd@;
	result.@usmblks@  = (size_t)(unsigned int)info.@usmblks@;
	result.@fsmblks@  = (size_t)(unsigned int)info.@fsmblks@;
	result.@uordblks@ = (size_t)(unsigned int)info.@uordblks@;
	result.@fordblks@ = (size_t)(unsigned int)info.@fordblks@;
	result.@keepcost@ = (size_t)(unsigned int)info.@keepcost@;
	return result;
}





%(user){
#ifdef __clang_tidy__
#define libc_realloc_in_place(mallptr, n_bytes)        __builtin_realloc_in_place(mallptr, n_bytes)
#define libc_memalign(alignment, n_bytes)              __builtin_memalign(alignment, n_bytes)
#define libc_pvalloc(n_bytes)                          __builtin_pvalloc(n_bytes)
#define libc_valloc(n_bytes)                           __builtin_valloc(n_bytes)
#define libc_posix_memalign(pp, alignment, n_bytes)    ((*(pp) = __builtin_memalign(alignment, n_bytes)) != 0 ? 0 : ENOMEM)
#define libc_malloc_usable_size(ptr)                   __builtin_malloc_usable_size(ptr)
#define libc_memdup(ptr, n_bytes)                      __builtin_memdup(ptr, n_bytes)
#define libc_reallocarray(ptr, elem_count, elem_size)  __builtin_reallocarray(ptr, elem_count, elem_size)
#define libc_recalloc(mallptr, num_bytes)              __builtin_recalloc(mallptr, num_bytes)
#define libc_recallocv(mallptr, elem_count, elem_size) __builtin_recallocv(mallptr, elem_count, elem_size)
#endif /* __clang_tidy__ */
}
%{
#ifdef __clang_tidy__
#ifdef __memalign_defined
#undef memalign
#define memalign(alignment, n_bytes) __builtin_memalign(alignment, n_bytes)
#endif /* __memalign_defined */
#ifdef __pvalloc_defined
#undef pvalloc
#define pvalloc(n_bytes) __builtin_pvalloc(n_bytes)
#endif /* __pvalloc_defined */
#ifdef __valloc_defined
#undef valloc
#define valloc(n_bytes) __builtin_valloc(n_bytes)
#endif /* __valloc_defined */
#ifdef __posix_memalign_defined
#include <asm/os/errno.h>
#undef posix_memalign
#define posix_memalign(pp, alignment, n_bytes) ((*(pp) = __builtin_memalign(alignment, n_bytes)) != 0 ? 0 : __ENOMEM)
#endif /* __posix_memalign_defined */
}%[insert:pp_if($has_function(memdup))]%{
#undef memdup
#define memdup(ptr, n_bytes) __builtin_memdup(ptr, n_bytes)
}%[insert:pp_endif]%{
#ifdef __reallocarray_defined
#undef reallocarray
#define reallocarray(ptr, elem_count, elem_size) __builtin_reallocarray(ptr, elem_count, elem_size)
#undef recallocv
#define recallocv reallocarray
#endif /* __reallocarray_defined */
#ifdef __realloc_defined
#undef recalloc
#define recalloc realloc
#endif /* __realloc_defined */
#endif /* __clang_tidy__ */
}


%{

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_DOS
#include <corecrt_malloc.h>
#endif /* __USE_DOS */

}
