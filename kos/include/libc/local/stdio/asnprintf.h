/* HASH CRC-32:0x71212f1e */
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
#ifndef __local_asnprintf_defined
#define __local_asnprintf_defined
#include <__crt.h>
#if defined(__CRT_HAVE_vasnprintf) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vasnprintf_defined
#define __local___localdep_vasnprintf_defined
#ifdef __CRT_HAVE_vasnprintf
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_LIBC_PRINTF(3, 0),char *,__NOTHROW_NCX,__localdep_vasnprintf,(char *__heapbuf, __SIZE_TYPE__ *__p_buflen, char const *__format, __builtin_va_list __args),vasnprintf,(__heapbuf,__p_buflen,__format,__args))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vasnprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vasnprintf __LIBC_LOCAL_NAME(vasnprintf)
#else /* ... */
#undef __local___localdep_vasnprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vasnprintf_defined */
__LOCAL_LIBC(asnprintf) __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_LIBC_PRINTF(3, 4) char *
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(asnprintf))(char *__restrict __heapbuf, __SIZE_TYPE__ *__restrict __p_buflen, char const *__restrict __format, ...) {
	char *__result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vasnprintf)(__heapbuf, __p_buflen, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_asnprintf_defined
#define __local___localdep_asnprintf_defined
#define __localdep_asnprintf __LIBC_LOCAL_NAME(asnprintf)
#endif /* !__local___localdep_asnprintf_defined */
#else /* __CRT_HAVE_vasnprintf || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local_asnprintf_defined
#endif /* !__CRT_HAVE_vasnprintf && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local_asnprintf_defined */
