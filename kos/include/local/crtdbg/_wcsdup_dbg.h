/* HASH CRC-32:0xb1e54dd3 */
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
#ifndef __local__wcsdup_dbg_defined
#if (defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_c16dup) || (defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wcsdup) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#define __local__wcsdup_dbg_defined 1
#include <__crt.h>
/* Dependency: "c16dup" from "parts.uchar.string" */
#ifndef ____localdep_c16dup_defined
#define ____localdep_c16dup_defined 1
#if defined(__CRT_HAVE_wcsdup) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16dup,(__CHAR16_TYPE__ const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16dup,(__CHAR16_TYPE__ const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$_wcsdup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16dup,(__CHAR16_TYPE__ const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$_wcsdup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16dup,(__CHAR16_TYPE__ const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsdup.h>
#define __localdep_c16dup (*(__CHAR16_TYPE__ *(__LIBCCALL*)(__CHAR16_TYPE__ const *__restrict))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup)))
#else /* LIBC: c16dup */
#include <local/wchar/c16dup.h>
#define __localdep_c16dup (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16dup))
#endif /* LIBC: c16dup */
#else /* CUSTOM: wcsdup */
#undef ____localdep_c16dup_defined
#endif /* c16dup... */
#endif /* !____localdep_c16dup_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wcsdup_dbg) __ATTR_MALLOC __ATTR_WUNUSED __WCHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wcsdup_dbg))(__WCHAR16_TYPE__ const *__string,
                                                         int __block_type,
                                                         char const *__filename,
                                                         int __line) {
#line 424 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__WCHAR16_TYPE__ *)__localdep_c16dup((__CHAR16_TYPE__ const *)__string);
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_wcsdup && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_c16dup || (__CRT_HAVE__wcsdup && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$_wcsdup || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_posix_memalign || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_malloc */
#endif /* !__local__wcsdup_dbg_defined */
