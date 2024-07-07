/* HASH CRC-32:0xb3ead2ba */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CORECRT_MALLOC_C
#define GUARD_LIBC_AUTO_CORECRT_MALLOC_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "corecrt_malloc.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_malloc)(size_t num_bytes,
                                           size_t min_alignment) {
	void *result = libc_malloc(num_bytes + 2 * sizeof(void *) + min_alignment - 1);
	if (result) {
		void *base = (void *)(((uintptr_t)result + (min_alignment - 1)) & ~(min_alignment - 1));
		((void **)base)[-1] = result;
		((void **)base)[-2] = (void *)num_bytes;
		result = base;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc)(size_t num_bytes,
                                                  size_t min_alignment,
                                                  size_t offset) {
	void *result;
	offset &= (min_alignment - 1);
	result = libc_malloc(num_bytes + 2 * sizeof(void *) + min_alignment - 1 + (min_alignment - offset));
	if (result) {
		void *base = (void *)((((uintptr_t)result + (min_alignment - 1)) & ~(min_alignment - 1)) + offset);
		((void **)base)[-1] = result;
		((void **)base)[-2] = (void *)num_bytes;
		result = base;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_realloc)(void *aligned_mallptr,
                                            size_t newsize,
                                            size_t min_alignment) {
	void *result;
	result = libc__aligned_malloc(newsize, min_alignment);
	if (result && aligned_mallptr) {
		size_t temp = libc__aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > newsize)
			temp = newsize;
		libc_memcpy(result, aligned_mallptr, temp);
		libc__aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_recalloc)(void *aligned_mallptr,
                                             size_t count,
                                             size_t num_bytes,
                                             size_t min_alignment) {
	void *result;
	num_bytes *= count;
	result = libc__aligned_malloc(num_bytes, min_alignment);
	if (result) {
		size_t temp = libc__aligned_msize(aligned_mallptr, min_alignment, 0);
		if (temp > num_bytes)
			temp = num_bytes;
		libc_memcpy(result, aligned_mallptr, temp);
		libc_bzero((byte_t *)result + temp, num_bytes - temp);
		libc__aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc)(void *aligned_mallptr,
                                                   size_t newsize,
                                                   size_t min_alignment,
                                                   size_t offset) {
	void *result;
	result = libc__aligned_offset_malloc(newsize, min_alignment, offset);
	if (result) {
		size_t temp = libc__aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > newsize)
			temp = newsize;
		libc_memcpy(result, aligned_mallptr, temp);
		libc__aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc)(void *aligned_mallptr,
                                                    size_t count,
                                                    size_t num_bytes,
                                                    size_t min_alignment,
                                                    size_t offset) {
	void *result;
	num_bytes *= count;
	result = libc__aligned_offset_malloc(num_bytes, min_alignment, offset);
	if (result) {
		size_t temp = libc__aligned_msize(aligned_mallptr, min_alignment, offset);
		if (temp > num_bytes)
			temp = num_bytes;
		libc_memcpy(result, aligned_mallptr, temp);
		libc_bzero((byte_t *)result + temp, num_bytes - temp);
		libc__aligned_free(aligned_mallptr);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.heap") ATTR_PURE WUNUSED size_t
NOTHROW_NCX(LIBCCALL libc__aligned_msize)(void *aligned_mallptr,
                                          size_t min_alignment,
                                          size_t offset) {
	(void)min_alignment;
	(void)offset;
	if (!aligned_mallptr)
		return 0;
	return (size_t)(uintptr_t)((void **)aligned_mallptr)[-2];
}
INTERN ATTR_SECTION(".text.crt.dos.heap") void
NOTHROW_NCX(LIBCCALL libc__aligned_free)(void *aligned_mallptr) {
	if (aligned_mallptr)
		libc_free(((void **)aligned_mallptr)[-1]);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(_aligned_malloc,libc__aligned_malloc,ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)),void *,NOTHROW_NCX,LIBCCALL,(size_t num_bytes, size_t min_alignment),(num_bytes,min_alignment));
DEFINE_PUBLIC_ALIAS_P(_aligned_offset_malloc,libc__aligned_offset_malloc,ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)),void *,NOTHROW_NCX,LIBCCALL,(size_t num_bytes, size_t min_alignment, size_t offset),(num_bytes,min_alignment,offset));
DEFINE_PUBLIC_ALIAS_P(_aligned_realloc,libc__aligned_realloc,WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)),void *,NOTHROW_NCX,LIBCCALL,(void *aligned_mallptr, size_t newsize, size_t min_alignment),(aligned_mallptr,newsize,min_alignment));
DEFINE_PUBLIC_ALIAS_P(_aligned_recalloc,libc__aligned_recalloc,WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)),void *,NOTHROW_NCX,LIBCCALL,(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment),(aligned_mallptr,count,num_bytes,min_alignment));
DEFINE_PUBLIC_ALIAS_P(_aligned_offset_realloc,libc__aligned_offset_realloc,WUNUSED ATTR_ALLOC_SIZE((2)),void *,NOTHROW_NCX,LIBCCALL,(void *aligned_mallptr, size_t newsize, size_t min_alignment, size_t offset),(aligned_mallptr,newsize,min_alignment,offset));
DEFINE_PUBLIC_ALIAS_P(_aligned_offset_recalloc,libc__aligned_offset_recalloc,WUNUSED ATTR_ALLOC_SIZE((2, 3)),void *,NOTHROW_NCX,LIBCCALL,(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset),(aligned_mallptr,count,num_bytes,min_alignment,offset));
DEFINE_PUBLIC_ALIAS_P(_aligned_msize,libc__aligned_msize,ATTR_PURE WUNUSED,size_t,NOTHROW_NCX,LIBCCALL,(void *aligned_mallptr, size_t min_alignment, size_t offset),(aligned_mallptr,min_alignment,offset));
DEFINE_PUBLIC_ALIAS_P_VOID(_aligned_free,libc__aligned_free,,NOTHROW_NCX,LIBCCALL,(void *aligned_mallptr),(aligned_mallptr));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_MALLOC_C */
