/* HASH CRC-32:0x2a45b4c0 */
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
#ifndef __local_convert_mbstowcsvn_defined
#define __local_convert_mbstowcsvn_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_mbstowcs_defined
#define __local___localdep_convert_mbstowcs_defined
#ifdef __CRT_HAVE_convert_mbstowcs
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_convert_mbstowcs,(char const *__restrict __str),convert_mbstowcs,(__str))
#elif defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_mbstowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_mbstowcs __LIBC_LOCAL_NAME(convert_mbstowcs)
#else /* ... */
#undef __local___localdep_convert_mbstowcs_defined
#endif /* !... */
#endif /* !__local___localdep_convert_mbstowcs_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
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
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(convert_mbstowcsvn) __ATTR_MALLOC __ATTR_WUNUSED __ATTR_INS(1, 2) __WCHAR_TYPE__ **
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(convert_mbstowcsvn))(char const *const *__restrict __vector, __SIZE_TYPE__ __count) {
	__SIZE_TYPE__ __i;
	__WCHAR_TYPE__ **__result;
	__result = (__WCHAR_TYPE__ **)(__NAMESPACE_LOCAL_SYM __localdep_malloc)((__count + 1) * sizeof(__WCHAR_TYPE__ *));
	if __likely(__result) {
		for (__i = 0; __i < __count; ++__i) {
			__WCHAR_TYPE__ *__temp;
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_convert_mbstowcs)(__vector[__i]);
			if __unlikely(!__temp)
				goto __err;
			__result[__i] = __temp;
		}
		__result[__i] = __NULLPTR;
	}
	return __result;
__err:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	while (__i--)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__result[__i]);
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_convert_mbstowcsvn_defined
#define __local___localdep_convert_mbstowcsvn_defined
#define __localdep_convert_mbstowcsvn __LIBC_LOCAL_NAME(convert_mbstowcsvn)
#endif /* !__local___localdep_convert_mbstowcsvn_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
#undef __local_convert_mbstowcsvn_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_convert_mbstowcs && !__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc))) */
#endif /* !__local_convert_mbstowcsvn_defined */
