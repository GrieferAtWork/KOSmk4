/* HASH CRC-32:0x91e81998 */
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
#ifndef __local_c16ndup_defined
#if defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#define __local_c16ndup_defined 1
/* Dependency: "wcsnlen" from "wchar" */
#ifndef ____localdep_c16nlen_defined
#define ____localdep_c16nlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16nlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16nlen,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16nlen(string, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c16nlen */
#include <local/wchar/c16nlen.h>
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_c16nlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nlen))
#endif /* c16nlen... */
#endif /* !____localdep_c16nlen_defined */

/* Dependency: "malloc" from "stdlib" */
#ifndef ____localdep_malloc_defined
#define ____localdep_malloc_defined 1
#ifdef __std___localdep_malloc_defined
__NAMESPACE_STD_USING(__localdep_malloc)
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#include <local/stdlib/malloc.h>
#define __localdep_malloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))
#else /* CUSTOM: malloc */
#undef ____localdep_malloc_defined
#endif /* malloc... */
#endif /* !____localdep_malloc_defined */

/* Dependency: "wmempcpy" from "wchar" */
#ifndef ____localdep_c16mempcpy_defined
#define ____localdep_c16mempcpy_defined 1
#if defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16mempcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyw)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16mempcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_DOS$wmempcpy)
__CREDIRECT_DOS(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16mempcpy,(__CHAR16_TYPE__ *__restrict __dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wmempcpy.h>
#define __localdep_c16mempcpy(dst, src, num_chars) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy))((__WCHAR_TYPE__ *)(dst), (__WCHAR_TYPE__ const *)(src), num_chars)
#else /* LIBC: c16mempcpy */
#include <local/wchar/c16mempcpy.h>
#define __localdep_c16mempcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16mempcpy))
#endif /* c16mempcpy... */
#endif /* !____localdep_c16mempcpy_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16ndup) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16ndup))(__CHAR16_TYPE__ const *__restrict __string,
                                                     __SIZE_TYPE__ __max_chars) {
#line 528 "kos/src/libc/magic/string.c"
	__SIZE_TYPE__ __resultlen = __localdep_c16nlen(__string, __max_chars);
	__CHAR16_TYPE__ *__result = (__CHAR16_TYPE__ *)__localdep_malloc((__resultlen + 1) * sizeof(__CHAR16_TYPE__));
	if __likely(__result)

		*__localdep_c16mempcpy(__result, __string, __resultlen) = '\0';



	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_posix_memalign || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_malloc */
#endif /* !__local_c16ndup_defined */
