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
#include "malloc.h"

#include <string.h>
#include <malloc.h>

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

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xbb0f392f]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(memdup, libc_memdup);
DEFINE_PUBLIC_WEAK_ALIAS(__memdup, libc_memdup);
DEFINE_PUBLIC_WEAK_ALIAS(memcdup, libc_memcdup);
DEFINE_PUBLIC_WEAK_ALIAS(__memcdup, libc_memcdup);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MALLOC_C */
