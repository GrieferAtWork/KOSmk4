/* HASH CRC-32:0xd050b635 */
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
#ifndef __local_mbsrtowcs_defined
#define __local_mbsrtowcs_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mbsnrtowcs_defined
#define __local___localdep_mbsnrtowcs_defined
#ifdef __CRT_HAVE_mbsnrtowcs
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsnrtowcs,(__WCHAR_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsnrtowcs,(__dst,__psrc,__nmc,__dstlen,__mbs))
#else /* __CRT_HAVE_mbsnrtowcs */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/mbsnrtowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsnrtowcs __LIBC_LOCAL_NAME(mbsnrtowcs)
#endif /* !__CRT_HAVE_mbsnrtowcs */
#endif /* !__local___localdep_mbsnrtowcs_defined */
__LOCAL_LIBC(mbsrtowcs) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbsrtowcs))(__WCHAR_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) {
	return (__NAMESPACE_LOCAL_SYM __localdep_mbsnrtowcs)(__dst, __psrc, (__SIZE_TYPE__)-1, __dstlen, __mbs);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbsrtowcs_defined
#define __local___localdep_mbsrtowcs_defined
#define __localdep_mbsrtowcs __LIBC_LOCAL_NAME(mbsrtowcs)
#endif /* !__local___localdep_mbsrtowcs_defined */
#endif /* !__local_mbsrtowcs_defined */
