/* HASH CRC-32:0x177cb879 */
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
#ifndef __local_reallocarray_defined
#ifdef __CRT_HAVE_realloc
#define __local_reallocarray_defined 1
#include <__crt.h>
#include <hybrid/__overflow.h>
/* Dependency: "realloc" */
#ifndef ____localdep_realloc_defined
#define ____localdep_realloc_defined 1
#ifdef __std___localdep_realloc_defined
__NAMESPACE_STD_USING(__localdep_realloc)
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#else /* LIBC: realloc */
#undef ____localdep_realloc_defined
#endif /* realloc... */
#endif /* !____localdep_realloc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(reallocarray) __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_SIZE((2, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(reallocarray))(void *__ptr,
                                                          __SIZE_TYPE__ __elem_count,
                                                          __SIZE_TYPE__ __elem_size) {
#line 206 "kos/src/libc/magic/malloc.c"
	__SIZE_TYPE__ __total_bytes;
	if (__hybrid_overflow_umul(__elem_count, __elem_size, &__total_bytes))
		__total_bytes = (__SIZE_TYPE__)-1; /* Force down-stream failure */
	return __localdep_realloc(__ptr, __total_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_realloc */
#endif /* !__local_reallocarray_defined */
