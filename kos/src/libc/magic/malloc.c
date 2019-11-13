/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[default_impl_section(.text.crt.heap.malloc)]

%(libc_fast){
#include "stdlib.h"
}
%(libc_slow){
#include "stdlib.h"
}

%{
#include <features.h>

__SYSDECL_BEGIN

#ifdef __CRT_KOS
/* malloc behavior attributes. */
#define __MALLOC_ZERO_IS_NONNULL  1
#define __REALLOC_ZERO_IS_NONNULL 1
#endif

#define M_TRIM_THRESHOLD     (-1)
#define M_GRANULARITY        (-2)
#define M_MMAP_THRESHOLD     (-3)

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}

%[insert:std]
%[insert:extern(malloc)]
%[insert:extern(calloc)]
%[insert:extern(realloc)]
%[insert:extern(free)]



@@@EXCEPT: `realloc_in_place()' will return `NULL' if the reallocation isn't
@@          possible due to the requested memory above `MALLPTR' already being
@@          in use. However, an `E_BADALLOC' exception is thrown if insufficient
@@          memory (for internal control structures) is available to complete
@@          the operation
[alias(_expand)][ATTR_MALL_DEFAULT_ALIGNED][ATTR_ALLOC_SIZE((2))]
[section(.text.crt.heap.helpers)]
realloc_in_place:(void *__restrict mallptr, size_t n_bytes) -> void *;

[section(.text.crt.heap.rare_helpers)]
crt_posix_memalign:([nonnull] void **__restrict pp, size_t alignment, size_t n_bytes) -> int = posix_memalign?;

%
[ATTR_WUNUSED][ATTR_ALLOC_ALIGN(1)][ATTR_ALLOC_SIZE((2))]
[ATTR_MALLOC][alias(aligned_alloc)]
[requires(defined(__CRT_HAVE_posix_memalign))]
memalign:(size_t alignment, size_t n_bytes) -> void * {
	void *result;
	if (crt_posix_memalign(&result, alignment, n_bytes))
		return NULL;
	return result;
}


%
[ATTR_WUNUSED][ATTR_MALL_PAGEALIGNED][ATTR_ALLOC_SIZE((1))][ATTR_MALLOC]
[section(.text.crt.heap.rare_helpers)]
pvalloc:(size_t n_bytes) -> void *;

[noexport][guard]
[ATTR_WUNUSED][ATTR_MALL_PAGEALIGNED][ATTR_ALLOC_SIZE((1))]
[requires($has_function(memalign))]
[dependency_include(<hybrid/__limits.h>)]
[section(.text.crt.heap.rare_helpers)]
valloc:($size_t n_bytes) -> void * {
	return memalign(getpagesize(), n_bytes);
}

[dependency_include(<parts/errno.h>)]
[requires($has_function(memalign))][noexport][guard]
[section(.text.crt.heap.rare_helpers)][crtbuiltin]
posix_memalign:([nonnull] void **__restrict pp, $size_t alignment, $size_t n_bytes) -> int {
	void *result;
	size_t d = alignment / sizeof(void *);
	size_t r = alignment % sizeof(void *);
	if (r != 0 || !d || (d & (d - 1)) != 0)
		return @__EINVAL@;
	result = memalign(alignment, n_bytes);
	if (!result)
		return @__ENOMEM@;
	*pp = result;
	return 0;
}

[guard][preferred_alias(free)]
[section(.text.crt.heap.rare_helpers)]
cfree:(void *__restrict mallptr);

%
[section(.text.crt.dos.heap)][ignore]
[section(.text.crt.heap.utility)]
_heapmin:() -> int;

[section(.text.crt.heap.utility)]
[libc_impl({
	/* NO-OP (indicate failure to release memory) */
	COMPILER_IMPURE();
	(void)pad;
	return 0;
})] malloc_trim:(size_t pad) -> int {
#ifdef __CRT_HAVE__heapmin
	(void)pad;
	return _heapmin() ? 1 : 0;
#else
	/* NO-OP (indicate failure to release memory) */
	COMPILER_IMPURE();
	(void)pad;
	return 0;
#endif
}

%
[ATTR_PURE][ATTR_WUNUSED][alias(_msize)]
[section(.text.crt.heap.helpers)]
malloc_usable_size:(void *__restrict mallptr) -> size_t;

[section(.text.crt.heap.utility)]
mallopt:(int parameter_number, int parameter_value) -> int {
	/* NO-OP */
	COMPILER_IMPURE();
	(void)parameter_number;
	(void)parameter_value;
	return 0;
}

[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_ALLOC_SIZE((2))]
[ATTR_MALLOC][section(.text.crt.heap.rare_helpers)]
__memdup:([nonnull] void const *__restrict ptr, size_t n_bytes) -> void * = memdup;

[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_ALLOC_SIZE((2))]
[ATTR_MALLOC][section(.text.crt.heap.rare_helpers)]
__memcdup:([nonnull] void const *__restrict ptr, int needle, size_t n_bytes) -> void * = memcdup;

%
%#ifdef __USE_KOS
[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_ALLOC_SIZE((2))]
[ATTR_MALLOC][alias(__memdup)][requires($has_function(malloc))]
[section(.text.crt.heap.rare_helpers)]
memdup:([nonnull] void const *__restrict ptr, size_t n_bytes) -> void * {
	void *result;
	result = malloc(n_bytes);
	if likely(result)
		memcpy(result, ptr, n_bytes);
	return result;
}

[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_ALLOC_SIZE((2))]
[ATTR_MALLOC][alias(__memcdup)][requires($has_function(memdup))]
[section(.text.crt.heap.rare_helpers)]
memcdup:([nonnull] void const *__restrict ptr, int needle, size_t n_bytes) -> void * {
	if likely(n_bytes) {
		void const *endaddr;
		endaddr = memchr(ptr, needle, n_bytes - 1);
		if (endaddr)
			n_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
	}
	return memdup(ptr, n_bytes);
}
%#endif /* __USE_KOS */



%#ifdef __USE_DOS
[ATTR_PURE][ATTR_WUNUSED][section(.text.crt.dos.heap)]
[section(.text.crt.heap.rare_helpers)]
_msize:(void *__restrict mallptr) -> size_t = malloc_usable_size;
%#endif /* __USE_DOS */

%{

#endif /* __CC__ */

__SYSDECL_END

}