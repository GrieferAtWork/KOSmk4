/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Windows Kits (/ucrt/corecrt_malloc.h) */
/*!always_includes <crtdefs.h>*/
}

%[default:section(".text.crt.dos.heap")]

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <crtdefs.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

}

/* Standard heap functions */
%[insert:std]

%[insert:guarded_std_function(malloc)]
%[insert:guarded_std_function(calloc)]
%[insert:guarded_std_function(realloc)]
%[insert:guarded_std_function(free)]

/* DOS malloc extensions */

%[insert:function(_recalloc = recallocv)]

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(malloc)]]
_aligned_malloc:($size_t num_bytes, $size_t min_alignment)
	-> [[memalign(min_alignment, num_bytes)]] void *
{
	void *result = malloc(num_bytes + 2 * sizeof(void *) + min_alignment - 1);
	if (result) {
		void *base = (void *)(((uintptr_t)result + (min_alignment - 1)) & ~(min_alignment - 1));
		((void **)base)[-1] = result;
		((void **)base)[-2] = (void *)num_bytes;
		result = base;
	}
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(malloc)]]
_aligned_offset_malloc:($size_t num_bytes, $size_t min_alignment, $size_t offset)
	-> [[malloc_unaligned(num_bytes)]] void *
{
	void *result;
	offset &= (min_alignment - 1);
	result = malloc(num_bytes + 2 * sizeof(void *) + min_alignment - 1 + (min_alignment - offset));
	if (result) {
		void *base = (void *)((((uintptr_t)result + (min_alignment - 1)) & ~(min_alignment - 1)) + offset);
		((void **)base)[-1] = result;
		((void **)base)[-2] = (void *)num_bytes;
		result = base;
	}
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(_aligned_malloc, _aligned_free, _aligned_msize)]]
_aligned_realloc:(void *aligned_mallptr, $size_t newsize, $size_t min_alignment)
	-> [[realign(aligned_mallptr, min_alignment, newsize)]] void *
{
	void *result;
	result = _aligned_malloc(newsize, min_alignment);
	if (result && aligned_mallptr) {
		$size_t temp = _aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > newsize)
			temp = newsize;
		memcpy(result, aligned_mallptr, temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(_aligned_malloc, _aligned_free, _aligned_msize)]]
_aligned_recalloc:(void *aligned_mallptr, $size_t count, $size_t num_bytes, $size_t min_alignment)
	-> [[realign(aligned_mallptr, min_alignment, count * num_bytes)]] void *
{
	void *result;
	num_bytes *= count;
	result = _aligned_malloc(num_bytes, min_alignment);
	if (result) {
		$size_t temp = _aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > num_bytes)
			temp = num_bytes;
		memcpy(result, aligned_mallptr, temp);
		bzero((byte_t *)result + temp, num_bytes - temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(_aligned_offset_malloc, _aligned_free, _aligned_msize)]]
_aligned_offset_realloc:(void *aligned_mallptr, $size_t newsize, $size_t min_alignment, $size_t offset)
	-> [[realloc_unaligned(aligned_mallptr, newsize)]] void *
{
	void *result;
	result = _aligned_offset_malloc(newsize, min_alignment, offset);
	if (result) {
		$size_t temp = _aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > newsize)
			temp = newsize;
		memcpy(result, aligned_mallptr, temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(_aligned_offset_malloc, _aligned_free, _aligned_msize)]]
_aligned_offset_recalloc:(void *aligned_mallptr, $size_t count, $size_t num_bytes, $size_t min_alignment, $size_t offset)
	-> [[realloc_unaligned(aligned_mallptr, count * num_bytes)]] void *
{
	void *result;
	num_bytes *= count;
	result = _aligned_offset_malloc(num_bytes, min_alignment, offset);
	if (result) {
		$size_t temp = _aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > num_bytes)
			temp = num_bytes;
		memcpy(result, aligned_mallptr, temp);
		bzero((byte_t *)result + temp, num_bytes - temp);
		_aligned_free(aligned_mallptr);
	}
	return result;
}

[[pure, wunused, decl_include("<hybrid/typecore.h>")]]
$size_t _aligned_msize(void *aligned_mallptr, $size_t min_alignment, $size_t offset) {
	(void)min_alignment;
	(void)offset;
	if (!aligned_mallptr)
		return 0;
	return ($size_t)(uintptr_t)((void **)aligned_mallptr)[-2];
}

[[requires_function(free)]]
void _aligned_free(void *aligned_mallptr) {
	if (aligned_mallptr)
		free(((void **)aligned_mallptr)[-1]);
}

%[insert:function(_expand = realloc_in_place)]
%[insert:function(_msize = malloc_usable_size)]

// TODO: int _callnewh(size_t num_bytes);
// TODO: void *_malloc_base(size_t num_bytes);
// TODO: void *_calloc_base(size_t elem_count, size_t elem_size);
// TODO: void _free_base(void *ptr);
// TODO: size_t _msize_base(void *ptr);
// TODO: void *_realloc_base(void *ptr, size_t num_bytes);
// TODO: void *_recalloc_base(void *ptr, size_t elem_count, elem_size);

%{

__SYSDECL_END
#endif /* __CC__ */

}
