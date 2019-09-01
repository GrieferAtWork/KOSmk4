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
#ifndef GUARD_LIBC_USER_MALLOC_C
#define GUARD_LIBC_USER_MALLOC_C 1

#include "../api.h"
#include "malloc.h"

#include <string.h>
#include <malloc.h>

DECL_BEGIN



/*[[[start:implementation]]]*/

/*[[[head:valloc,hash:0xf50d1285]]]*/
INTERN WUNUSED ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.rare_helpers.valloc") void *
NOTHROW_NCX(LIBCCALL libc_valloc)(size_t n_bytes)
/*[[[body:valloc]]]*/
{
	CRT_UNIMPLEMENTED("valloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:valloc]]]*/

/*[[[head:realloc_in_place,hash:0x785e7e03]]]*/
/* @EXCEPT: `realloc_in_place()' will return `NULL' if the reallocation isn't
 *           possible due to the requested memory above `MALLPTR' already being
 *           in use. However, an `E_BADALLOC' exception is thrown if insufficient
 *           memory (for internal control structures) is available to complete
 *           the operation */
INTERN ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.helpers.realloc_in_place") void *
NOTHROW_NCX(LIBCCALL libc_realloc_in_place)(void *__restrict mallptr,
                                            size_t n_bytes)
/*[[[body:realloc_in_place]]]*/
{
	CRT_UNIMPLEMENTED("realloc_in_place"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:realloc_in_place]]]*/

/*[[[head:posix_memalign,hash:0x26fe881d]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.rare_helpers.posix_memalign") int
NOTHROW_NCX(LIBCCALL libc_posix_memalign)(void **__restrict pp,
                                          size_t alignment,
                                          size_t n_bytes)
/*[[[body:posix_memalign]]]*/
{
	CRT_UNIMPLEMENTED("posix_memalign"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_memalign]]]*/

/*[[[head:malloc,hash:0x6f045e0a]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_ALLOC_SIZE((1))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.malloc.malloc") void *
NOTHROW_NCX(LIBCCALL libc_malloc)(size_t n_bytes)
/*[[[body:malloc]]]*/
{
	CRT_UNIMPLEMENTED("malloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:malloc]]]*/

/*[[[head:free,hash:0xf40e9b66]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.heap.malloc.free") void
NOTHROW_NCX(LIBCCALL libc_free)(void *mallptr)
/*[[[body:free]]]*/
{
	CRT_UNIMPLEMENTED("free"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:free]]]*/

/*[[[head:memalign,hash:0xdf16e413]]]*/
INTERN WUNUSED ATTR_ALLOC_ALIGN(1) ATTR_ALLOC_SIZE((2)) ATTR_MALLOC
ATTR_WEAK ATTR_SECTION(".text.crt.heap.malloc.memalign") void *
NOTHROW_NCX(LIBCCALL libc_memalign)(size_t alignment,
                                    size_t n_bytes)
/*[[[body:memalign]]]*/
{
	CRT_UNIMPLEMENTED("memalign"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:memalign]]]*/

/*[[[head:calloc,hash:0xc80b22d6]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_ALLOC_SIZE((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.malloc.calloc") void *
NOTHROW_NCX(LIBCCALL libc_calloc)(size_t count,
                                  size_t n_bytes)
/*[[[body:calloc]]]*/
{
	CRT_UNIMPLEMENTED("calloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:calloc]]]*/

/*[[[head:pvalloc,hash:0x51de8a40]]]*/
INTERN WUNUSED ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) ATTR_MALLOC
ATTR_WEAK ATTR_SECTION(".text.crt.heap.rare_helpers.pvalloc") void *
NOTHROW_NCX(LIBCCALL libc_pvalloc)(size_t n_bytes)
/*[[[body:pvalloc]]]*/
{
	CRT_UNIMPLEMENTED("pvalloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:pvalloc]]]*/

/*[[[head:realloc,hash:0x4de52547]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_ALLOC_SIZE((2))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.malloc.realloc") void *
NOTHROW_NCX(LIBCCALL libc_realloc)(void *mallptr,
                                   size_t n_bytes)
/*[[[body:realloc]]]*/
{
	CRT_UNIMPLEMENTED("realloc"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:realloc]]]*/

/*[[[head:memcdup,hash:0x35740ef0]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2)) ATTR_MALLOC NONNULL((1))
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

/*[[[head:memdup,hash:0x9b373046]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2)) ATTR_MALLOC NONNULL((1))
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

/*[[[head:malloc_usable_size,hash:0xb8ae959e]]]*/
INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.heap.helpers.malloc_usable_size") size_t
NOTHROW_NCX(LIBCCALL libc_malloc_usable_size)(void *__restrict mallptr)
/*[[[body:malloc_usable_size]]]*/
{
	CRT_UNIMPLEMENTED("malloc_usable_size"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:malloc_usable_size]]]*/

/*[[[impl:cfree]]]*/
DEFINE_INTERN_WEAK_ALIAS(libc_cfree,libc_free);

/*[[[head:_heapmin,hash:0xdfa93f35]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.heap.utility._heapmin") int
NOTHROW_NCX(LIBCCALL libc__heapmin)(void)
/*[[[body:_heapmin]]]*/
{
	CRT_UNIMPLEMENTED("_heapmin"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:_heapmin]]]*/
/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xe9eac4fb]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(malloc, libc_malloc);
DEFINE_PUBLIC_WEAK_ALIAS(calloc, libc_calloc);
DEFINE_PUBLIC_WEAK_ALIAS(realloc, libc_realloc);
DEFINE_PUBLIC_WEAK_ALIAS(free, libc_free);
DEFINE_PUBLIC_WEAK_ALIAS(realloc_in_place, libc_realloc_in_place);
DEFINE_PUBLIC_WEAK_ALIAS(memalign, libc_memalign);
DEFINE_PUBLIC_WEAK_ALIAS(aligned_alloc, libc_memalign);
DEFINE_PUBLIC_WEAK_ALIAS(pvalloc, libc_pvalloc);
DEFINE_PUBLIC_WEAK_ALIAS(valloc, libc_valloc);
DEFINE_PUBLIC_WEAK_ALIAS(posix_memalign, libc_posix_memalign);
DEFINE_PUBLIC_WEAK_ALIAS(cfree, libc_cfree);
DEFINE_PUBLIC_WEAK_ALIAS(malloc_usable_size, libc_malloc_usable_size);
DEFINE_PUBLIC_WEAK_ALIAS(_msize, libc_malloc_usable_size);
DEFINE_PUBLIC_WEAK_ALIAS(memdup, libc_memdup);
DEFINE_PUBLIC_WEAK_ALIAS(__memdup, libc_memdup);
DEFINE_PUBLIC_WEAK_ALIAS(memcdup, libc_memcdup);
DEFINE_PUBLIC_WEAK_ALIAS(__memcdup, libc_memcdup);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MALLOC_C */
