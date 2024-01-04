/* HASH CRC-32:0x8b28b631 */
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
#ifndef __local_convert_wcstombsv_defined
#define __local_convert_wcstombsv_defined
#include <__crt.h>
#if defined(__CRT_HAVE_convert_wcstombsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_wcstombsvn_defined
#define __local___localdep_convert_wcstombsvn_defined
#ifdef __CRT_HAVE_convert_wcstombsvn
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_INS(1, 2),char **,__NOTHROW_NCX,__localdep_convert_wcstombsvn,(__WCHAR_TYPE__ const *const *__restrict __vector, __SIZE_TYPE__ __count),convert_wcstombsvn,(__vector,__count))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombsvn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_wcstombsvn __LIBC_LOCAL_NAME(convert_wcstombsvn)
#else /* ... */
#undef __local___localdep_convert_wcstombsvn_defined
#endif /* !... */
#endif /* !__local___localdep_convert_wcstombsvn_defined */
#ifndef __local___localdep_rawmemlenl_defined
#define __local___localdep_rawmemlenl_defined
#ifdef __CRT_HAVE_rawmemlenl
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_rawmemlenl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle),rawmemlenl,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemlenl */
__NAMESPACE_LOCAL_END
#include <libc/local/string/rawmemlenl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rawmemlenl __LIBC_LOCAL_NAME(rawmemlenl)
#endif /* !__CRT_HAVE_rawmemlenl */
#endif /* !__local___localdep_rawmemlenl_defined */
#ifndef __local___localdep_rawmemlenq_defined
#define __local___localdep_rawmemlenq_defined
#ifdef __CRT_HAVE_rawmemlenq
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_rawmemlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemlenq,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemlenq */
__NAMESPACE_LOCAL_END
#include <libc/local/string/rawmemlenq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rawmemlenq __LIBC_LOCAL_NAME(rawmemlenq)
#endif /* !__CRT_HAVE_rawmemlenq */
#endif /* !__local___localdep_rawmemlenq_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(convert_wcstombsv) __ATTR_MALLOC __ATTR_WUNUSED __ATTR_IN_OPT(1) char **
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(convert_wcstombsv))(__WCHAR_TYPE__ const *const *__restrict __vector) {
	__SIZE_TYPE__ __count;
	if __unlikely(!__vector) {
#ifdef __EINVAL
		(void)__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
		return __NULLPTR;
	}
#if __SIZEOF_POINTER__ == 4
	__count = (__NAMESPACE_LOCAL_SYM __localdep_rawmemlenl)(__vector, 0);
#elif __SIZEOF_POINTER__ == 8
	__count = (__NAMESPACE_LOCAL_SYM __localdep_rawmemlenq)(__vector, 0);
#else /* ... */
	for (__count = 0; __vector[__count]; ++__count)
		;
#endif /* !... */
	return (__NAMESPACE_LOCAL_SYM __localdep_convert_wcstombsvn)(__vector, __count);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_convert_wcstombsv_defined
#define __local___localdep_convert_wcstombsv_defined
#define __localdep_convert_wcstombsv __LIBC_LOCAL_NAME(convert_wcstombsv)
#endif /* !__local___localdep_convert_wcstombsv_defined */
#else /* __CRT_HAVE_convert_wcstombsvn || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)) */
#undef __local_convert_wcstombsv_defined
#endif /* !__CRT_HAVE_convert_wcstombsvn && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)) */
#endif /* !__local_convert_wcstombsv_defined */
