/* HASH CRC-32:0x47cd308e */
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
#ifndef __local_argz_append_defined
#define __local_argz_append_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_realloc
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memcpyc from string */
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined 1
#ifdef __fast_memcpyc_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__NAMESPACE_FAST_USING(memcpyc)
#define __localdep_memcpyc __LIBC_FAST_NAME(memcpyc)
#elif defined(__CRT_HAVE_memcpyc)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !... */
#endif /* !__local___localdep_memcpyc_defined */
/* Dependency: realloc from stdlib */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined 1
#ifdef __realloc_defined
__NAMESPACE_GLB_USING(realloc)
#define __localdep_realloc realloc
#elif defined(__std_realloc_defined)
__NAMESPACE_STD_USING(realloc)
#define __localdep_realloc realloc
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
__NAMESPACE_LOCAL_END
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__LOCAL_LIBC(argz_append) __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_append))(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __buf, __SIZE_TYPE__ __buf_len) {
	__SIZE_TYPE__ __oldlen = *__pargz_len;
	__SIZE_TYPE__ __newlen = __oldlen + __buf_len;
	char *__newargz = (char *)__localdep_realloc(*__pargz, __newlen * sizeof(char));
	if __unlikely(!__newargz) {
#ifdef ENOMEM
		return __ENOMEM;
#else /* ENOMEM */
		return 1;
#endif /* !ENOMEM */
	}
	__localdep_memcpyc(__newargz + __oldlen, __buf, __buf_len, sizeof(char));
	*__pargz     = __newargz;
	*__pargz_len = __newlen;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argz_append_defined
#define __local___localdep_argz_append_defined 1
#define __localdep_argz_append __LIBC_LOCAL_NAME(argz_append)
#endif /* !__local___localdep_argz_append_defined */
#else /* __CRT_HAVE_realloc */
#undef __local_argz_append_defined
#endif /* !__CRT_HAVE_realloc */
#endif /* !__local_argz_append_defined */
