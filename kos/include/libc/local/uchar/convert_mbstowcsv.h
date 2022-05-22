/* HASH CRC-32:0x2db86a02 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_convert_mbstowcsv_defined
#define __local_convert_mbstowcsv_defined
#include <__crt.h>
#if defined(__CRT_HAVE_convert_mbstowcsvn) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_mbstowcsvn_defined
#define __local___localdep_convert_mbstowcsvn_defined
#ifdef __CRT_HAVE_convert_mbstowcsvn
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 2),__WCHAR_TYPE__ **,__NOTHROW_NCX,__localdep_convert_mbstowcsvn,(char const *const *__restrict __vector, __SIZE_TYPE__ __count),convert_mbstowcsvn,(__vector,__count))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_mbstowcsvn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_mbstowcsvn __LIBC_LOCAL_NAME(convert_mbstowcsvn)
#else /* ... */
#undef __local___localdep_convert_mbstowcsvn_defined
#endif /* !... */
#endif /* !__local___localdep_convert_mbstowcsvn_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(convert_mbstowcsv) __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ACCESS_RO_OPT(1) __WCHAR_TYPE__ **
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(convert_mbstowcsv))(char const *const *__restrict __vector) {
	__SIZE_TYPE__ __count = 0;
	if __unlikely(!__vector) {
#ifdef __EINVAL
		(void)__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
		return __NULLPTR;
	}
	for (__count = 0; __vector[__count]; ++__count)
		;
	return (__NAMESPACE_LOCAL_SYM __localdep_convert_mbstowcsvn)(__vector, __count);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_convert_mbstowcsv_defined
#define __local___localdep_convert_mbstowcsv_defined
#define __localdep_convert_mbstowcsv __LIBC_LOCAL_NAME(convert_mbstowcsv)
#endif /* !__local___localdep_convert_mbstowcsv_defined */
#else /* __CRT_HAVE_convert_mbstowcsvn || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))) */
#undef __local_convert_mbstowcsv_defined
#endif /* !__CRT_HAVE_convert_mbstowcsvn && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_convert_mbstowcs && !__CRT_HAVE_convert_mbstowcsn && ((!__CRT_HAVE_format_waprintf_printer && !__CRT_HAVE_format_waprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_format_waprintf_pack && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc)))) */
#endif /* !__local_convert_mbstowcsv_defined */
