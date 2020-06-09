/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%{
#include <features.h>
#include <malloc.h>
#include <kos/anno.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

%[default_impl_section(.text.crt.except.heap.malloc)]

[throws(E_BADALLOC)] Malloc:(size_t num_bytes) -> [nonnull, malloc(num_bytes)] void *;
[throws(E_BADALLOC)] Calloc:(size_t count, size_t num_bytes) -> [nonnull, malloc(count * num_bytes)] void *;
[throws(E_BADALLOC)] Realloc:(void *mallptr, size_t num_bytes) -> [nonnull, realloc(mallptr, num_bytes)] void *;
[throws(E_BADALLOC)] Memalign:(size_t alignment, size_t num_bytes) -> [nonnull, memalign(alignment, num_bytes)] void *;

[throws(E_BADALLOC)][section(.text.crt.except.heap.rare_helpers)]
PValloc:(size_t num_bytes) -> [nonnull, memalign(getpagesize(), num_bytes)] void *;

[throws(E_BADALLOC)][noexport][requires($has_function(Memalign))]
[section(.text.crt.except.heap.rare_helpers)]
Valloc:(size_t num_bytes) -> [nonnull, memalign(getpagesize(), num_bytes)] void * {
	return Memalign(getpagesize(), num_bytes);
}


%
%#ifdef __USE_KOS
[throws(E_BADALLOC)][requires($has_function(Malloc))][section(.text.crt.except.heap.rare_helpers)]
Memdup:([[nonnull]] void const *__restrict ptr, size_t num_bytes) -> [nonnull, malloc(num_bytes)] void * {
	void *result;
	result = Malloc(num_bytes);
	memcpy(result, ptr, num_bytes);
	return result;
}

@@@throws: E_BADALLOC: ...
[throws(E_BADALLOC)][requires($has_function(Memdup))][section(.text.crt.except.heap.rare_helpers)]
Memcdup:([[nonnull]] void const *__restrict ptr, int needle, size_t num_bytes) -> [nonnull, malloc] void * {
	if likely(num_bytes) {
		void const *endaddr;
		endaddr = memchr(ptr, needle, num_bytes - 1);
		if (endaddr)
			num_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
	}
	return Memdup(ptr, num_bytes);
}
%#endif /* __USE_KOS */


%{

#endif /* __CC__ */

__SYSDECL_END

}