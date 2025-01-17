/* HASH CRC-32:0xc845ab49 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wctime64_defined
#define __local__wctime64_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__wctime64_s_defined
#define __local___localdep__wctime64_s_defined
#ifdef __CRT_HAVE__wctime64_s
__CREDIRECT(__ATTR_IN(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,__localdep__wctime64_s,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __time64_t const *__timer),_wctime64_s,(__buf,__buflen,__timer))
#else /* __CRT_HAVE__wctime64_s */
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wtime/_wctime64_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__wctime64_s __LIBC_LOCAL_NAME(_wctime64_s)
#endif /* !__CRT_HAVE__wctime64_s */
#endif /* !__local___localdep__wctime64_s_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
__LOCAL_LIBC(_wctime64) __ATTR_WUNUSED __ATTR_IN(1) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wctime64))(__time64_t const *__timer) {














	static __WCHAR_TYPE__ __wctime_buf[26];




	return (__NAMESPACE_LOCAL_SYM __localdep__wctime64_s)(__wctime_buf, 26, __timer) ? __NULLPTR : __wctime_buf;


}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wctime64_defined
#define __local___localdep__wctime64_defined
#define __localdep__wctime64 __LIBC_LOCAL_NAME(_wctime64)
#endif /* !__local___localdep__wctime64_defined */
#endif /* !__local__wctime64_defined */
