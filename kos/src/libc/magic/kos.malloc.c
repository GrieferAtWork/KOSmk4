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

%{
#include <features.h>
#include <malloc.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

%[default_impl_section(.text.crt.except.heap.malloc)]


@@@throws: E_BADALLOC: ...
Malloc:(size_t n_bytes) -> [nonnull][malloc(n_bytes)] void *;

@@@throws: E_BADALLOC: ...
[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_MALLOC]
[ATTR_RETNONNULL][ATTR_ALLOC_SIZE((1, 2))]
Calloc:(size_t count, size_t n_bytes) -> void *;

@@@throws: E_BADALLOC: ...
[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED]
[ATTR_MALLOC][ATTR_ALLOC_SIZE((2))][ATTR_RETNONNULL]
Realloc:(void *mallptr, size_t n_bytes) -> void *;

@@@throws: E_BADALLOC: ...
[ATTR_WUNUSED][ATTR_ALLOC_ALIGN(1)][ATTR_ALLOC_SIZE((2))]
[ATTR_MALLOC][ATTR_RETNONNULL]
Memalign:(size_t alignment, size_t n_bytes) -> void *;

@@@throws: E_BADALLOC: ...
[ATTR_WUNUSED][ATTR_MALL_PAGEALIGNED][ATTR_ALLOC_SIZE((1))]
[ATTR_MALLOC][ATTR_RETNONNULL]
[section(.text.crt.except.heap.rare_helpers)]
PValloc:(size_t n_bytes) -> void *;

@@@throws: E_BADALLOC: ...
[noexport][ATTR_RETNONNULL]
[ATTR_WUNUSED][ATTR_MALL_PAGEALIGNED][ATTR_ALLOC_SIZE((1))]
[requires($has_function(Memalign))]
[dependency_include(<hybrid/__limits.h>)]
[section(.text.crt.except.heap.rare_helpers)]
Valloc:(size_t n_bytes) -> void * {
	return Memalign(getpagesize(), n_bytes);
}


%
%#ifdef __USE_KOS
@@@throws: E_BADALLOC: ...
[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_ALLOC_SIZE((2))]
[ATTR_MALLOC][requires($has_function(Malloc))][ATTR_RETNONNULL]
[section(.text.crt.except.heap.rare_helpers)]
Memdup:([nonnull] void const *__restrict ptr, size_t n_bytes) -> void * {
	void *result;
	result = Malloc(n_bytes);
	memcpy(result, ptr, n_bytes);
	return result;
}

@@@throws: E_BADALLOC: ...
[ATTR_WUNUSED][ATTR_MALL_DEFAULT_ALIGNED][ATTR_ALLOC_SIZE((2))]
[ATTR_MALLOC][alias(__memcdup)][requires($has_function(memdup))]
[section(.text.crt.except.heap.rare_helpers)][ATTR_RETNONNULL]
Memcdup:([nonnull] void const *__restrict ptr, int needle, size_t n_bytes) -> void * {
	if likely(n_bytes) {
		void const *endaddr;
		endaddr = memchr(ptr, needle, n_bytes - 1);
		if (endaddr)
			n_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
	}
	return Memdup(ptr, n_bytes);
}
%#endif /* __USE_KOS */


%{

#endif /* __CC__ */

__SYSDECL_END

}