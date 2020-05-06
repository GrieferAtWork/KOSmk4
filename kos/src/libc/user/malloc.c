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



/*[[[start:implementation]]]*/

/*[[[skip:valloc]]]*/
/*[[[skip:realloc_in_place]]]*/
/*[[[skip:posix_memalign]]]*/
/*[[[skip:memalign]]]*/
/*[[[skip:pvalloc]]]*/
/*[[[skip:malloc_usable_size]]]*/
/*[[[skip:cfree]]]*/

/*[[[head:_heapmin,hash:CRC-32=0x85c22195]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.heap.utility._heapmin") int
NOTHROW_NCX(LIBCCALL libc__heapmin)(void)
/*[[[body:_heapmin]]]*/
{
	return malloc_trim(0);
}
/*[[[end:_heapmin]]]*/


/*[[[head:memcdup,hash:CRC-32=0xbad869c1]]]*/
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.rare_helpers.memcdup") void *
NOTHROW_NCX(LIBCCALL libc_memcdup)(void const *__restrict ptr,
                                   int needle,
                                   size_t n_bytes)
/*[[[body:memcdup]]]*/
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
/*[[[end:memcdup]]]*/

/*[[[head:memdup,hash:CRC-32=0x1f6fe48c]]]*/
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.rare_helpers.memdup") void *
NOTHROW_NCX(LIBCCALL libc_memdup)(void const *__restrict ptr,
                                  size_t n_bytes)
/*[[[body:memdup]]]*/
{
	void *result;
	result = malloc(n_bytes);
	if likely(result)
		memcpy(result, ptr, n_bytes);
	return result;
}
/*[[[end:memdup]]]*/

/*[[[head:malloc_trim,hash:CRC-32=0xff7232d0]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.heap.utility.malloc_trim") int
NOTHROW_NCX(LIBCCALL libc_malloc_trim)(size_t pad)
/*[[[body:malloc_trim]]]*/
/*AUTO*/{
	/* NO-OP (indicate failure to release memory) */
	COMPILER_IMPURE();
	(void)pad;
	return 0;
}
/*[[[end:malloc_trim]]]*/

/*[[[head:mallopt,hash:CRC-32=0x90b86537]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.heap.utility.mallopt") int
NOTHROW_NCX(LIBCCALL libc_mallopt)(int parameter_number,
                                   int parameter_value)
/*[[[body:mallopt]]]*/
/*AUTO*/{
	/* NO-OP */
	COMPILER_IMPURE();
	(void)parameter_number;
	(void)parameter_value;
	return 0;
}
/*[[[end:mallopt]]]*/

/*[[[head:reallocarray,hash:CRC-32=0xe6b2d3bc]]]*/
INTERN ATTR_MALL_DEFAULT_ALIGNED ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_ALLOC_SIZE((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.rare_helpers.reallocarray") void *
NOTHROW_NCX(LIBCCALL libc_reallocarray)(void *ptr,
                                        size_t elem_count,
                                        size_t elem_size)
/*[[[body:reallocarray]]]*/
/*AUTO*/{
	size_t total_bytes;
	if (__hybrid_overflow_umul(elem_count, elem_size, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	return libc_realloc(ptr, total_bytes);
}
/*[[[end:reallocarray]]]*/

/*[[[head:recalloc,hash:CRC-32=0xad7e5859]]]*/
INTERN ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.rare_helpers.recalloc") void *
NOTHROW_NCX(LIBCCALL libc_recalloc)(void *mallptr,
                                    size_t num_bytes)
/*[[[body:recalloc]]]*/
/*AUTO*/{
	void *result;
	size_t oldsize;
	oldsize = libc_malloc_usable_size(mallptr);
	result  = libc_realloc(mallptr, num_bytes);
	if likely(result) {
		if (num_bytes > oldsize)
			memset((byte_t *)result + oldsize, 0, num_bytes - oldsize);
	}
	return result;
}
/*[[[end:recalloc]]]*/

/*[[[head:recallocv,hash:CRC-32=0x1b8a1d16]]]*/
INTERN ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.rare_helpers.recallocv") void *
NOTHROW_NCX(LIBCCALL libc_recallocv)(void *mallptr,
                                     size_t elem_count,
                                     size_t elem_size)
/*[[[body:recallocv]]]*/
/*AUTO*/{
	void *result;
	size_t total_bytes, oldsize;
	oldsize = libc_malloc_usable_size(mallptr);
	if unlikely(__hybrid_overflow_umul(elem_count, elem_size, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	result = libc_realloc(mallptr, total_bytes);
	if likely(result) {
		if (total_bytes > oldsize)
			memset((byte_t *)result + oldsize, 0, total_bytes - oldsize);
	}
	return result;
}
/*[[[end:recallocv]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xfeb8448e]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(_heapmin, libc__heapmin);
DEFINE_PUBLIC_WEAK_ALIAS(malloc_trim, libc_malloc_trim);
DEFINE_PUBLIC_WEAK_ALIAS(mallopt, libc_mallopt);
DEFINE_PUBLIC_WEAK_ALIAS(memdup, libc_memdup);
DEFINE_PUBLIC_WEAK_ALIAS(__memdup, libc_memdup);
DEFINE_PUBLIC_WEAK_ALIAS(memcdup, libc_memcdup);
DEFINE_PUBLIC_WEAK_ALIAS(__memcdup, libc_memcdup);
DEFINE_PUBLIC_WEAK_ALIAS(reallocarray, libc_reallocarray);
DEFINE_PUBLIC_WEAK_ALIAS(recalloc, libc_recalloc);
DEFINE_PUBLIC_WEAK_ALIAS(recallocv, libc_recallocv);
DEFINE_PUBLIC_WEAK_ALIAS(_recalloc, libc_recallocv);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MALLOC_C */
