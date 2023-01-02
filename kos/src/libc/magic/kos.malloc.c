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
%[default:section(".text.crt{|.dos}.except.heap.malloc")]
%[default:nodos]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <kos/anno.h>
)]%{

}%[insert:prefix(
#include <malloc.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}


[[libc, throws(E_BADALLOC), decl_include("<hybrid/typecore.h>")]]
Malloc:(size_t num_bytes) -> [[nonnull, malloc(num_bytes)]] void *;

[[libc, throws(E_BADALLOC), decl_include("<hybrid/typecore.h>")]]
Calloc:(size_t count, size_t num_bytes) -> [[nonnull, malloc(count * num_bytes)]] void *;

[[libc, throws(E_BADALLOC), decl_include("<hybrid/typecore.h>")]]
Realloc:(void *mallptr, size_t num_bytes) -> [[nonnull, realloc(mallptr, num_bytes)]] void *;

[[throws(E_BADALLOC), decl_include("<hybrid/typecore.h>")]]
Memalign:(size_t alignment, size_t num_bytes) -> [[nonnull, memalign(alignment, num_bytes)]] void *;

[[throws(E_BADALLOC), decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.except.heap.rare_helpers")]]
PValloc:(size_t num_bytes) -> [[nonnull, memalign(getpagesize(), num_bytes)]] void *;

[[throws(E_BADALLOC), decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.except.heap.rare_helpers")]]
[[userimpl, requires($has_function(Memalign))]]
Valloc:(size_t num_bytes) -> [[nonnull, memalign(getpagesize(), num_bytes)]] void * {
	return Memalign(getpagesize(), num_bytes);
}


%
%#ifdef __USE_KOS
[[throws(E_BADALLOC), decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.except.heap.rare_helpers")]]
[[userimpl, requires_function(Malloc)]]
Memdup:([[in(num_bytes)]] void const *__restrict ptr, size_t num_bytes) -> [[nonnull, malloc(num_bytes)]] void * {
	void *result;
	result = Malloc(num_bytes);
	memcpy(result, ptr, num_bytes);
	return result;
}

@@@throws: E_BADALLOC: ...
[[throws(E_BADALLOC), decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.except.heap.rare_helpers")]]
[[userimpl, requires_function(Memdup)]]
Memcdup:([[in(? <= num_bytes)]] void const *__restrict ptr, int needle, size_t num_bytes) -> [[nonnull, malloc]] void * {
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

__SYSDECL_END
#endif /* __CC__ */

}
