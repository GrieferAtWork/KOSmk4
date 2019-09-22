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

/*[[[head:Malloc,hash:CRC-32=0x31d4b58a]]]*/
/* @throws: E_BADALLOC: ... */
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_RETNONNULL ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.malloc.Malloc") void *
NOTHROW_NCX(LIBCCALL libc_Malloc)(size_t n_bytes)
/*[[[body:Malloc]]]*/
{
	void *result;
	result = malloc(n_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes);
	return result;
}
/*[[[end:Malloc]]]*/

/*[[[head:Calloc,hash:CRC-32=0x90fef843]]]*/
/* @throws: E_BADALLOC: ... */
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_RETNONNULL ATTR_ALLOC_SIZE((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.malloc.Calloc") void *
NOTHROW_NCX(LIBCCALL libc_Calloc)(size_t count,
                                  size_t n_bytes)
/*[[[body:Calloc]]]*/
{
	void *result;
	result = calloc(count, n_bytes);
	if unlikely(!result) {
		size_t total;
		if (OVERFLOW_UMUL(count, n_bytes, &total))
			total = (size_t)-1;
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, total);
	}
	return result;
}
/*[[[end:Calloc]]]*/

/*[[[head:Realloc,hash:CRC-32=0xbe67005]]]*/
/* @throws: E_BADALLOC: ... */
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_ALLOC_SIZE((2)) ATTR_RETNONNULL
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.malloc.Realloc") void *
NOTHROW_NCX(LIBCCALL libc_Realloc)(void *mallptr,
                                   size_t n_bytes)
/*[[[body:Realloc]]]*/
{
	void *result;
	result = realloc(mallptr, n_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes);
	return result;
}
/*[[[end:Realloc]]]*/

/*[[[head:Memalign,hash:CRC-32=0xd0ff00c3]]]*/
/* @throws: E_BADALLOC: ... */
INTERN WUNUSED ATTR_ALLOC_ALIGN(1) ATTR_ALLOC_SIZE((2)) ATTR_MALLOC ATTR_RETNONNULL
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.malloc.Memalign") void *
NOTHROW_NCX(LIBCCALL libc_Memalign)(size_t alignment,
                                    size_t n_bytes)
/*[[[body:Memalign]]]*/
{
	void *result;
	result = memalign(alignment, n_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes);
	return result;
}
/*[[[end:Memalign]]]*/

/*[[[head:PValloc,hash:CRC-32=0x656689a4]]]*/
/* @throws: E_BADALLOC: ... */
INTERN WUNUSED ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) ATTR_MALLOC ATTR_RETNONNULL
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.rare_helpers.PValloc") void *
NOTHROW_NCX(LIBCCALL libc_PValloc)(size_t n_bytes)
/*[[[body:PValloc]]]*/
{
	void *result;
	result = pvalloc(n_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes);
	return result;
}
/*[[[end:PValloc]]]*/

/*[[[head:Valloc,hash:CRC-32=0x3b861b8c]]]*/
/* @throws: E_BADALLOC: ... */
INTERN ATTR_RETNONNULL WUNUSED ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.rare_helpers.Valloc") void *
NOTHROW_NCX(LIBCCALL libc_Valloc)(size_t n_bytes)
/*[[[body:Valloc]]]*/
{
	void *result;
	result = valloc(n_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes);
	return result;
}
/*[[[end:Valloc]]]*/

/*[[[head:Memdup,hash:CRC-32=0x6584d5d8]]]*/
/* @throws: E_BADALLOC: ... */
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2)) ATTR_MALLOC ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.rare_helpers.Memdup") void *
NOTHROW_NCX(LIBCCALL libc_Memdup)(void const *__restrict ptr,
                                  size_t n_bytes)
/*[[[body:Memdup]]]*/
{
	void *result;
	result = memdup(ptr, n_bytes);
	if unlikely(!result)
		THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, n_bytes);
	return result;
}
/*[[[end:Memdup]]]*/

/*[[[head:Memcdup,hash:CRC-32=0x6670eeea]]]*/
/* @throws: E_BADALLOC: ... */
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2)) ATTR_MALLOC ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.heap.rare_helpers.Memcdup") void *
NOTHROW_NCX(LIBCCALL libc_Memcdup)(void const *__restrict ptr,
                                   int needle,
                                   size_t n_bytes)
/*[[[body:Memcdup]]]*/
{
	if likely(n_bytes) {
		void const *endaddr;
		endaddr = memchr(ptr, needle, n_bytes - 1);
		if (endaddr)
			n_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
	}
	return Memdup(ptr, n_bytes);
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
