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
#ifndef GUARD_LIBC_USER_KOS_MALLOC_C
#define GUARD_LIBC_USER_KOS_MALLOC_C 1

#include "../api.h"
#include "kos.malloc.h"
#include <hybrid/overflow.h>
#include <kos/except.h>
#include <string.h>
#include <malloc.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_Malloc,hash:CRC-32=0x1d1e4071]]]*/
INTERN ATTR_SECTION(".text.crt.except.heap.malloc") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1)) void *
(LIBCCALL libc_Malloc)(size_t num_bytes) THROWS(E_BADALLOC)
/*[[[body:libc_Malloc]]]*/
{
	void *result;
	result = malloc(num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:libc_Malloc]]]*/

/*[[[head:libc_Calloc,hash:CRC-32=0xf88a9ecf]]]*/
INTERN ATTR_SECTION(".text.crt.except.heap.malloc") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *
(LIBCCALL libc_Calloc)(size_t count,
                       size_t num_bytes) THROWS(E_BADALLOC)
/*[[[body:libc_Calloc]]]*/
{
	void *result;
	result = calloc(count, num_bytes);
	if unlikely(!result) {
		size_t total;
		if (OVERFLOW_UMUL(count, num_bytes, &total))
			total = (size_t)-1;
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, total);
	}
	return result;
}
/*[[[end:libc_Calloc]]]*/

/*[[[head:libc_Realloc,hash:CRC-32=0x8a517edf]]]*/
INTERN ATTR_SECTION(".text.crt.except.heap.malloc") ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) void *
(LIBCCALL libc_Realloc)(void *mallptr,
                        size_t num_bytes) THROWS(E_BADALLOC)
/*[[[body:libc_Realloc]]]*/
{
	void *result;
	result = realloc(mallptr, num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:libc_Realloc]]]*/

/*[[[head:libc_Memalign,hash:CRC-32=0x86a07a71]]]*/
INTERN ATTR_SECTION(".text.crt.except.heap.malloc") ATTR_MALLOC ATTR_RETNONNULL WUNUSED ATTR_ALLOC_ALIGN(1) ATTR_ALLOC_SIZE((2)) void *
(LIBCCALL libc_Memalign)(size_t alignment,
                         size_t num_bytes) THROWS(E_BADALLOC)
/*[[[body:libc_Memalign]]]*/
{
	void *result;
	result = memalign(alignment, num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:libc_Memalign]]]*/

/*[[[head:libc_PValloc,hash:CRC-32=0xa7b75305]]]*/
INTERN ATTR_SECTION(".text.crt.except.heap.rare_helpers") ATTR_MALLOC ATTR_RETNONNULL WUNUSED __ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) void *
(LIBCCALL libc_PValloc)(size_t num_bytes) THROWS(E_BADALLOC)
/*[[[body:libc_PValloc]]]*/
{
	void *result;
	result = pvalloc(num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:libc_PValloc]]]*/

/*[[[head:libc_Valloc,hash:CRC-32=0xd09a829e]]]*/
INTERN ATTR_SECTION(".text.crt.except.heap.rare_helpers") ATTR_MALLOC ATTR_RETNONNULL WUNUSED __ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) void *
(LIBCCALL libc_Valloc)(size_t num_bytes) THROWS(E_BADALLOC)
/*[[[body:libc_Valloc]]]*/
{
	void *result;
	result = valloc(num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:libc_Valloc]]]*/

/*[[[head:libc_Memdup,hash:CRC-32=0x6692dc85]]]*/
INTERN ATTR_SECTION(".text.crt.except.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) NONNULL((1)) void *
(LIBCCALL libc_Memdup)(void const *__restrict ptr,
                       size_t num_bytes) THROWS(E_BADALLOC)
/*[[[body:libc_Memdup]]]*/
{
	void *result;
	result = memdup(ptr, num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:libc_Memdup]]]*/

/*[[[head:libc_Memcdup,hash:CRC-32=0x61260375]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_SECTION(".text.crt.except.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
(LIBCCALL libc_Memcdup)(void const *__restrict ptr,
                        int needle,
                        size_t num_bytes) THROWS(E_BADALLOC)
/*[[[body:libc_Memcdup]]]*/
{
	if likely(num_bytes) {
		void const *endaddr;
		endaddr = memchr(ptr, needle, num_bytes - 1);
		if (endaddr)
			num_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
	}
	return Memdup(ptr, num_bytes);
}
/*[[[end:libc_Memcdup]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xebd79f79]]]*/
DEFINE_PUBLIC_ALIAS(Malloc, libc_Malloc);
DEFINE_PUBLIC_ALIAS(Calloc, libc_Calloc);
DEFINE_PUBLIC_ALIAS(Realloc, libc_Realloc);
DEFINE_PUBLIC_ALIAS(Memalign, libc_Memalign);
DEFINE_PUBLIC_ALIAS(PValloc, libc_PValloc);
DEFINE_PUBLIC_ALIAS(Valloc, libc_Valloc);
DEFINE_PUBLIC_ALIAS(Memdup, libc_Memdup);
DEFINE_PUBLIC_ALIAS(Memcdup, libc_Memcdup);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_MALLOC_C */
