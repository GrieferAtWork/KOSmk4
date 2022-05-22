/* HASH CRC-32:0x5ad4bfb9 */
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
#ifndef __local_wcstombs_s_defined
#define __local_wcstombs_s_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstombs_defined
#define __local___localdep_wcstombs_defined
#ifdef __CRT_HAVE_wcstombs
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcstombs,(char *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __dstlen),wcstombs,(__dst,__src,__dstlen))
#else /* __CRT_HAVE_wcstombs */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/wcstombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstombs __LIBC_LOCAL_NAME(wcstombs)
#endif /* !__CRT_HAVE_wcstombs */
#endif /* !__local___localdep_wcstombs_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcstombs_s) __ATTR_INS(4, 5) __ATTR_OUTS(2, 3) __ATTR_OUT_OPT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstombs_s))(__SIZE_TYPE__ *__presult, char *__buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __maxlen) {
	if (!__presult || !__buf || !__src) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	if (__buflen > __maxlen)
		__buflen = __maxlen;
	*__presult = (__NAMESPACE_LOCAL_SYM __localdep_wcstombs)(__buf, __src, __buflen);
	/* TODO: if (buflen < *presult) return ERANGE; */
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcstombs_s_defined
#define __local___localdep_wcstombs_s_defined
#define __localdep_wcstombs_s __LIBC_LOCAL_NAME(wcstombs_s)
#endif /* !__local___localdep_wcstombs_s_defined */
#endif /* !__local_wcstombs_s_defined */
