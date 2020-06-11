/* HASH CRC-32:0xbb21ede5 */
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
#ifndef __local__mbstowcs_s_defined
#define __local__mbstowcs_s_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mbstowcs from stdlib */
#ifndef __local___localdep_mbstowcs_defined
#define __local___localdep_mbstowcs_defined 1
#ifdef __CRT_HAVE_mbstowcs
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbstowcs,(__WCHAR_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_DOS$mbstowcs) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbstowcs,(__CHAR32_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen),mbstowcs,(__dst,__src,__dstlen))
#elif defined(__CRT_HAVE_DOS$mbstowcs) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbstowcs,(__CHAR16_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen),mbstowcs,(__dst,__src,__dstlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdlib/mbstowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbstowcs __LIBC_LOCAL_NAME(mbstowcs)
#endif /* !... */
#endif /* !__local___localdep_mbstowcs_defined */
__NAMESPACE_LOCAL_END
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbstowcs_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstowcs_s))(__SIZE_TYPE__ *__presult, __WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen) {
	__SIZE_TYPE__ __error;
	if (__dstlen >= __dstsize) {
		if (!__dstsize)
			return 0;
		__dstlen = __dstsize - 1;
	}
	__error = __localdep_mbstowcs(__dst, __src, __dstlen);
	if (__presult)
		*__presult = __error;
#ifdef EILSEQ
	if (__error == (__SIZE_TYPE__)-1)
		return __EILSEQ;
#endif /* EILSEQ */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbstowcs_s_defined
#define __local___localdep__mbstowcs_s_defined 1
#define __localdep__mbstowcs_s __LIBC_LOCAL_NAME(_mbstowcs_s)
#endif /* !__local___localdep__mbstowcs_s_defined */
#endif /* !__local__mbstowcs_s_defined */
