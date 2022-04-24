/* HASH CRC-32:0xfc07db47 */
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
#ifndef __local__mbstowcs_l_defined
#define __local__mbstowcs_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mbstowcs_defined
#define __local___localdep_mbstowcs_defined
#ifdef __CRT_HAVE_mbstowcs
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbstowcs,(__WCHAR_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen),mbstowcs,(__dst,__src,__dstlen))
#else /* __CRT_HAVE_mbstowcs */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/mbstowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbstowcs __LIBC_LOCAL_NAME(mbstowcs)
#endif /* !__CRT_HAVE_mbstowcs */
#endif /* !__local___localdep_mbstowcs_defined */
__LOCAL_LIBC(_mbstowcs_l) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstowcs_l))(__WCHAR_TYPE__ *__dst, char const *__src, __SIZE_TYPE__ __dstlen, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_mbstowcs)(__dst, __src, __dstlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbstowcs_l_defined
#define __local___localdep__mbstowcs_l_defined
#define __localdep__mbstowcs_l __LIBC_LOCAL_NAME(_mbstowcs_l)
#endif /* !__local___localdep__mbstowcs_l_defined */
#endif /* !__local__mbstowcs_l_defined */
