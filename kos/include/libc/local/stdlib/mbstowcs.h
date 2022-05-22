/* HASH CRC-32:0xadb1b9b1 */
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
#ifndef __local_mbstowcs_defined
#define __local_mbstowcs_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mbsrtowcs_defined
#define __local___localdep_mbsrtowcs_defined
#ifdef __CRT_HAVE_mbsrtowcs
__NAMESPACE_LOCAL_END
#include <bits/crt/mbstate.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsrtowcs,(__WCHAR_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#else /* __CRT_HAVE_mbsrtowcs */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/mbsrtowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsrtowcs __LIBC_LOCAL_NAME(mbsrtowcs)
#endif /* !__CRT_HAVE_mbsrtowcs */
#endif /* !__local___localdep_mbsrtowcs_defined */
__LOCAL_LIBC(mbstowcs) __ATTR_IN(2) __ATTR_OUTS(1, 3) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbstowcs))(__WCHAR_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_mbsrtowcs)(__dst, (char const **)&__src, __dstlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbstowcs_defined
#define __local___localdep_mbstowcs_defined
#define __localdep_mbstowcs __LIBC_LOCAL_NAME(mbstowcs)
#endif /* !__local___localdep_mbstowcs_defined */
#endif /* !__local_mbstowcs_defined */
