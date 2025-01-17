/* HASH CRC-32:0x351e0220 */
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
#ifndef __local__wcsdup_dbg_defined
#define __local__wcsdup_dbg_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wcsdup) || (defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wcsdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16dup_defined
#define __local___localdep_c16dup_defined
#if defined(__CRT_HAVE_wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16dup,(__CHAR16_TYPE__ const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$wcsdup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16dup,(__CHAR16_TYPE__ const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16dup,(__CHAR16_TYPE__ const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_DOS$_wcsdup)
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16dup,(__CHAR16_TYPE__ const *__restrict __string),_wcsdup,(__string))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsdup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16dup __NAMESPACE_LOCAL_TYPEHAX(__CHAR16_TYPE__ *(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict),__CHAR16_TYPE__ *(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict),wcsdup)
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16dup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16dup __LIBC_LOCAL_NAME(c16dup)
#else /* ... */
#undef __local___localdep_c16dup_defined
#endif /* !... */
#endif /* !__local___localdep_c16dup_defined */
__LOCAL_LIBC(_wcsdup_dbg) __ATTR_MALLOC __ATTR_WUNUSED __WCHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_wcsdup_dbg))(__WCHAR16_TYPE__ const *__string, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__WCHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_c16dup)((__CHAR16_TYPE__ const *)__string);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wcsdup_dbg_defined
#define __local___localdep__wcsdup_dbg_defined
#define __localdep__wcsdup_dbg __LIBC_LOCAL_NAME(_wcsdup_dbg)
#endif /* !__local___localdep__wcsdup_dbg_defined */
#else /* (__CRT_HAVE_wcsdup && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wcsdup || (__CRT_HAVE__wcsdup && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wcsdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local__wcsdup_dbg_defined
#endif /* (!__CRT_HAVE_wcsdup || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wcsdup && (!__CRT_HAVE__wcsdup || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wcsdup && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local__wcsdup_dbg_defined */
