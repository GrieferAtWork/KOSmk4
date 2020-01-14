/* HASH CRC-32:0xa25c8e3a */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__recalloc_defined
#if defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#define __local__recalloc_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/__overflow.h>
/* Dependency: "malloc_usable_size" */
#ifndef ____localdep_malloc_usable_size_defined
#define ____localdep_malloc_usable_size_defined 1
#ifdef __CRT_HAVE_malloc_usable_size
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#elif defined(__CRT_HAVE__msize)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#else /* LIBC: malloc_usable_size */
#undef ____localdep_malloc_usable_size_defined
#endif /* malloc_usable_size... */
#endif /* !____localdep_malloc_usable_size_defined */

/* Dependency: "realloc" */
#ifndef ____localdep_realloc_defined
#define ____localdep_realloc_defined 1
#ifdef __std___localdep_realloc_defined
__NAMESPACE_STD_USING(__localdep_realloc)
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__EXTERNINLINE __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL __localdep_realloc)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { return __builtin_realloc(__mallptr, __num_bytes); }
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#else /* LIBC: realloc */
#undef ____localdep_realloc_defined
#endif /* realloc... */
#endif /* !____localdep_realloc_defined */

/* Dependency: "memset" from "string" */
#ifndef ____localdep_memset_defined
#define ____localdep_memset_defined 1
#ifdef __fast_memset_defined
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* LIBC: memset */
#include <local/string/memset.h>
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))
#endif /* memset... */
#endif /* !____localdep_memset_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_recalloc) __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_recalloc))(void *__mallptr,
                                                       __SIZE_TYPE__ __count,
                                                       __SIZE_TYPE__ __num_bytes) {
#line 2581 "kos/src/libc/magic/stdlib.c"
	void *__result;
	__SIZE_TYPE__ __total_bytes, __oldsize = __localdep_malloc_usable_size(__mallptr);
	if __unlikely(__hybrid_overflow_umul(__count, __num_bytes, &__total_bytes))
		__total_bytes = (__SIZE_TYPE__)-1; /* Force down-stream failure */
	__result = __localdep_realloc(__mallptr, __total_bytes);
	if __likely(__result) {
		if (__total_bytes > __oldsize)
			__localdep_memset((__BYTE_TYPE__ *)__result + __oldsize, 0, __total_bytes - __oldsize);
	}
	return __result;

}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_realloc && (__CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize) */
#endif /* !__local__recalloc_defined */
