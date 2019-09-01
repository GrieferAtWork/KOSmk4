/* HASH 0xb245bdda */
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
#ifndef __local_Memdup_defined
#if defined(__CRT_HAVE_Malloc)
#define __local_Memdup_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "Malloc" */
#ifndef ____localdep_Malloc_defined
#define ____localdep_Malloc_defined 1
#if defined(__CRT_HAVE_Malloc)
/* @throws: E_BADALLOC: ... */
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_Malloc,(__SIZE_TYPE__ __n_bytes),Malloc,(__n_bytes))
#else /* LIBC: Malloc */
#undef ____localdep_Malloc_defined
#endif /* Malloc... */
#endif /* !____localdep_Malloc_defined */

/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#if defined(__fast_memcpy_defined)
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

__NAMESPACE_LOCAL_BEGIN
/* @throws: E_BADALLOC: ... */
__LOCAL_LIBC(Memdup) __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)) __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(Memdup))(void const *__restrict __ptr,
                                                    __SIZE_TYPE__ __n_bytes) {
#line 77 "kos/src/libc/magic/kos.malloc.c"
	void *__result;
	__result = __localdep_Malloc(__n_bytes);
	__localdep_memcpy(__result, __ptr, __n_bytes);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_Malloc) */
#endif /* !__local_Memdup_defined */
