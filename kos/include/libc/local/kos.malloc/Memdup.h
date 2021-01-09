/* HASH CRC-32:0x9bdbdf3d */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_Memdup_defined
#define __local_Memdup_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_Malloc
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: Malloc from kos.malloc */
#ifndef __local___localdep_Malloc_defined
#define __local___localdep_Malloc_defined 1
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__THROWING,__localdep_Malloc,(__SIZE_TYPE__ __num_bytes),Malloc,(__num_bytes))
#endif /* !__local___localdep_Malloc_defined */
/* Dependency: memcpy from string */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined 1
#ifdef __CRT_HAVE_memcpy
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
__LOCAL_LIBC(Memdup) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_NONNULL((1)) void *
(__LIBCCALL __LIBC_LOCAL_NAME(Memdup))(void const *__restrict __ptr, __SIZE_TYPE__ __num_bytes) __THROWS(__E_BADALLOC) {
	void *__result;
	__result = __localdep_Malloc(__num_bytes);
	__localdep_memcpy(__result, __ptr, __num_bytes);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Memdup_defined
#define __local___localdep_Memdup_defined 1
#define __localdep_Memdup __LIBC_LOCAL_NAME(Memdup)
#endif /* !__local___localdep_Memdup_defined */
#else /* __CRT_HAVE_Malloc */
#undef __local_Memdup_defined
#endif /* !__CRT_HAVE_Malloc */
#endif /* !__local_Memdup_defined */
