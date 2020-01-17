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

/*[[[head:Malloc,hash:CRC-32=0x9063a437]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.malloc.Malloc") void *
(LIBCCALL libc_Malloc)(size_t num_bytes)
		__THROWS(E_BADALLOC)
/*[[[body:Malloc]]]*/
{
	void *result;
	result = malloc(num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:Malloc]]]*/

/*[[[head:Calloc,hash:CRC-32=0x15fc407e]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.malloc.Calloc") void *
(LIBCCALL libc_Calloc)(size_t count,
                       size_t num_bytes)
		__THROWS(E_BADALLOC)
/*[[[body:Calloc]]]*/
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
/*[[[end:Calloc]]]*/

/*[[[head:Realloc,hash:CRC-32=0x2c3082e7]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.malloc.Realloc") void *
(LIBCCALL libc_Realloc)(void *mallptr,
                        size_t num_bytes)
		__THROWS(E_BADALLOC)
/*[[[body:Realloc]]]*/
{
	void *result;
	result = realloc(mallptr, num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:Realloc]]]*/

/*[[[head:Memalign,hash:CRC-32=0x885b700a]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_MALLOC ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_ALLOC_ALIGN(1)
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.malloc.Memalign") void *
(LIBCCALL libc_Memalign)(size_t alignment,
                         size_t num_bytes)
		__THROWS(E_BADALLOC)
/*[[[body:Memalign]]]*/
{
	void *result;
	result = memalign(alignment, num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:Memalign]]]*/

/*[[[head:PValloc,hash:CRC-32=0xfe5a199]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_MALLOC ATTR_MALL_PAGEALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.rare_helpers.PValloc") void *
(LIBCCALL libc_PValloc)(size_t num_bytes)
		__THROWS(E_BADALLOC)
/*[[[body:PValloc]]]*/
{
	void *result;
	result = pvalloc(num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:PValloc]]]*/

/*[[[head:Valloc,hash:CRC-32=0x6a5d2657]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_MALLOC ATTR_MALL_PAGEALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.rare_helpers.Valloc") void *
(LIBCCALL libc_Valloc)(size_t num_bytes)
		__THROWS(E_BADALLOC)
/*[[[body:Valloc]]]*/
{
	void *result;
	result = valloc(num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:Valloc]]]*/

/*[[[head:Memdup,hash:CRC-32=0x6eaa466a]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED NONNULL((1)) ATTR_ALLOC_SIZE((2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.rare_helpers.Memdup") void *
(LIBCCALL libc_Memdup)(void const *__restrict ptr,
                       size_t num_bytes)
		__THROWS(E_BADALLOC)
/*[[[body:Memdup]]]*/
{
	void *result;
	result = memdup(ptr, num_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
	return result;
}
/*[[[end:Memdup]]]*/

/*[[[head:Memcdup,hash:CRC-32=0x9252cbec]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.rare_helpers.Memcdup") void *
(LIBCCALL libc_Memcdup)(void const *__restrict ptr,
                        int needle,
                        size_t num_bytes)
		__THROWS(E_BADALLOC)
/*[[[body:Memcdup]]]*/
{
	if likely(num_bytes) {
		void const *endaddr;
		endaddr = memchr(ptr, needle, num_bytes - 1);
		if (endaddr)
			num_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
	}
	return Memdup(ptr, num_bytes);
}
/*[[[end:Memcdup]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x1e5e31f6]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(Malloc, libc_Malloc);
DEFINE_PUBLIC_WEAK_ALIAS(Calloc, libc_Calloc);
DEFINE_PUBLIC_WEAK_ALIAS(Realloc, libc_Realloc);
DEFINE_PUBLIC_WEAK_ALIAS(Memalign, libc_Memalign);
DEFINE_PUBLIC_WEAK_ALIAS(PValloc, libc_PValloc);
DEFINE_PUBLIC_WEAK_ALIAS(Valloc, libc_Valloc);
DEFINE_PUBLIC_WEAK_ALIAS(Memdup, libc_Memdup);
DEFINE_PUBLIC_WEAK_ALIAS(Memcdup, libc_Memcdup);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_MALLOC_C */
