/* HASH CRC-32:0xf7e6b6a0 */
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
#ifndef __local_mbstowcs_s_defined
#define __local_mbstowcs_s_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mbstowcs_defined
#define __local___localdep_mbstowcs_defined
#ifdef __CRT_HAVE_mbstowcs
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbstowcs,(__WCHAR_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen),mbstowcs,(__dst,__src,__dstlen))
#else /* __CRT_HAVE_mbstowcs */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/mbstowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbstowcs __LIBC_LOCAL_NAME(mbstowcs)
#endif /* !__CRT_HAVE_mbstowcs */
#endif /* !__local___localdep_mbstowcs_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mbstowcs_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbstowcs_s))(__SIZE_TYPE__ *__presult, __WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __dstlen) {
	__SIZE_TYPE__ __error;
	if (__dstlen >= __dstsize) {
		if (!__dstsize)
			return 0;
		__dstlen = __dstsize - 1;
	}
	__error = (__NAMESPACE_LOCAL_SYM __localdep_mbstowcs)(__dst, __src, __dstlen);
	if (__presult)
		*__presult = __error;
#ifdef __EILSEQ
	if (__error == (__SIZE_TYPE__)-1)
		return __EILSEQ;
#endif /* __EILSEQ */
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbstowcs_s_defined
#define __local___localdep_mbstowcs_s_defined
#define __localdep_mbstowcs_s __LIBC_LOCAL_NAME(mbstowcs_s)
#endif /* !__local___localdep_mbstowcs_s_defined */
#endif /* !__local_mbstowcs_s_defined */
