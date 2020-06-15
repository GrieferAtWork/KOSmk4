/* HASH CRC-32:0xef4e80ef */
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
#ifndef __local__wcstombs_l_defined
#define __local__wcstombs_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcstombs from stdlib */
#ifndef __local___localdep_wcstombs_defined
#define __local___localdep_wcstombs_defined 1
#ifdef __CRT_HAVE_wcstombs
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcstombs,(char *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __dstlen),wcstombs,(__dst,__src,__dstlen))
#else /* __CRT_HAVE_wcstombs */
__NAMESPACE_LOCAL_END
#include <local/stdlib/wcstombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstombs __LIBC_LOCAL_NAME(wcstombs)
#endif /* !__CRT_HAVE_wcstombs */
#endif /* !__local___localdep_wcstombs_defined */
__LOCAL_LIBC(_wcstombs_l) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wcstombs_l))(char *__dst, __WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __maxlen, __locale_t __locale) {
	(void)__locale;
	return __localdep_wcstombs(__dst, __src, __maxlen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wcstombs_l_defined
#define __local___localdep__wcstombs_l_defined 1
#define __localdep__wcstombs_l __LIBC_LOCAL_NAME(_wcstombs_l)
#endif /* !__local___localdep__wcstombs_l_defined */
#endif /* !__local__wcstombs_l_defined */
