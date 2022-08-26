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
#ifndef GUARD_LIBC_USER_MALLOC_C
#define GUARD_LIBC_USER_MALLOC_C 1

#include "../api.h"
/**/

#include <hybrid/overflow.h>

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "malloc.h"
#include "stdlib.h"

DECL_BEGIN

/*[[[skip:libc_valloc]]]*/
/*[[[skip:libc_realloc_in_place]]]*/
/*[[[skip:libc_posix_memalign]]]*/
/*[[[skip:libc_memalign]]]*/
/*[[[skip:libc_pvalloc]]]*/
/*[[[skip:libc_malloc_usable_size]]]*/
/*[[[skip:libc_malloc_trim]]]*/
/*[[[skip:libc_mallopt]]]*/
/*[[[skip:libc_mallinfo]]]*/
/*[[[skip:libc_mallinfo2]]]*/


/*[[[head:libc_memcdup,hash:CRC-32=0xe2f0ddeb]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INS(1, 3) void *
NOTHROW_NCX(LIBCCALL libc_memcdup)(void const *__restrict ptr,
                                   int needle,
                                   size_t n_bytes)
/*[[[body:libc_memcdup]]]*/
{
	if likely(n_bytes) {
		void const *endaddr;
		endaddr = memchr(ptr,
		                 needle,
		                 n_bytes - 1);
		if (endaddr)
			n_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
	}
	return memdup(ptr, n_bytes);
}
/*[[[end:libc_memcdup]]]*/

/*[[[head:libc_memdup,hash:CRC-32=0xcbec1ab6]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INS(1, 2) void *
NOTHROW_NCX(LIBCCALL libc_memdup)(void const *__restrict ptr,
                                  size_t n_bytes)
/*[[[body:libc_memdup]]]*/
{
	void *result;
	result = malloc(n_bytes);
	if likely(result)
		memcpy(result, ptr, n_bytes);
	return result;
}
/*[[[end:libc_memdup]]]*/

/*[[[head:libc_reallocarray,hash:CRC-32=0xff244eca]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc_reallocarray)(void *ptr,
                                        size_t elem_count,
                                        size_t elem_size)
/*[[[body:libc_reallocarray]]]*/
/*AUTO*/{
	size_t total_bytes;
	if unlikely(__hybrid_overflow_umul(elem_count, elem_size, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	return realloc(ptr, total_bytes);
}
/*[[[end:libc_reallocarray]]]*/

/*[[[head:libc_recalloc,hash:CRC-32=0x6198e8db]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc_recalloc)(void *mallptr,
                                    size_t num_bytes)
/*[[[body:libc_recalloc]]]*/
/*AUTO*/{
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
/*[[[end:libc_recalloc]]]*/

/*[[[head:libc_recallocv,hash:CRC-32=0x5fcdcb24]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc_recallocv)(void *mallptr,
                                     size_t elem_count,
                                     size_t elem_size)
/*[[[body:libc_recallocv]]]*/
/*AUTO*/{
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
/*[[[end:libc_recallocv]]]*/





/*[[[start:exports,hash:CRC-32=0x68d44ccd]]]*/
DEFINE_PUBLIC_ALIAS(__memdup, libc_memdup);
DEFINE_PUBLIC_ALIAS(memdup, libc_memdup);
DEFINE_PUBLIC_ALIAS(__memcdup, libc_memcdup);
DEFINE_PUBLIC_ALIAS(memcdup, libc_memcdup);
DEFINE_PUBLIC_ALIAS(reallocarr, libc_reallocarray);
DEFINE_PUBLIC_ALIAS(reallocarray, libc_reallocarray);
DEFINE_PUBLIC_ALIAS(recalloc, libc_recalloc);
DEFINE_PUBLIC_ALIAS(_recalloc, libc_recallocv);
DEFINE_PUBLIC_ALIAS(recallocv, libc_recallocv);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MALLOC_C */
