/* HASH CRC-32:0x8554bd60 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_xrealloc_defined
#define __local_xrealloc_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_xmalloc_failed)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
#ifndef __local___localdep_xmalloc_failed_defined
#define __local___localdep_xmalloc_failed_defined
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_xmalloc_failed,(__SIZE_TYPE__ __num_bytes),xmalloc_failed,(__num_bytes))
#endif /* !__local___localdep_xmalloc_failed_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/malloc.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(xrealloc) __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(xrealloc))(void *__ptr, __SIZE_TYPE__ __num_bytes) {
	void *__result;
#ifdef __REALLOC_ZERO_IS_NONNULL
	__result = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(__ptr, __num_bytes);
#else /* __REALLOC_ZERO_IS_NONNULL */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(__ptr, __num_bytes ? __num_bytes : 1);
#endif /* !__REALLOC_ZERO_IS_NONNULL */
	if (__result == __NULLPTR)
		(__NAMESPACE_LOCAL_SYM __localdep_xmalloc_failed)(__num_bytes);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_xrealloc_defined
#define __local___localdep_xrealloc_defined
#define __localdep_xrealloc __LIBC_LOCAL_NAME(xrealloc)
#endif /* !__local___localdep_xrealloc_defined */
#else /* (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __CRT_HAVE_xmalloc_failed */
#undef __local_xrealloc_defined
#endif /* (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || !__CRT_HAVE_xmalloc_failed */
#endif /* !__local_xrealloc_defined */
