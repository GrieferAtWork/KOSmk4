/* HASH CRC-32:0xe0f73953 */
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
#ifndef __local_wcstold_l_defined
#define __local_wcstold_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstold_defined
#define __local___localdep_wcstold_defined
#ifdef __CRT_HAVE_wcstold
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,__localdep_wcstold,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr),wcstold,(__nptr,__endptr))
#else /* __CRT_HAVE_wcstold */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstold.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstold __LIBC_LOCAL_NAME(wcstold)
#endif /* !__CRT_HAVE_wcstold */
#endif /* !__local___localdep_wcstold_defined */
__LOCAL_LIBC(wcstold_l) __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstold_l))(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_wcstold)(__nptr, __endptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcstold_l_defined
#define __local___localdep_wcstold_l_defined
#define __localdep_wcstold_l __LIBC_LOCAL_NAME(wcstold_l)
#endif /* !__local___localdep_wcstold_l_defined */
#endif /* !__local_wcstold_l_defined */
