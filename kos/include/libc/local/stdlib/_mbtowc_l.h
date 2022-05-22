/* HASH CRC-32:0xdd88d74c */
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
#ifndef __local__mbtowc_l_defined
#define __local__mbtowc_l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mbtowc_defined
#define __local___localdep_mbtowc_defined
#ifdef __CRT_HAVE_mbtowc
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),int,__NOTHROW_NCX,__localdep_mbtowc,(__WCHAR_TYPE__ *__restrict __pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen),mbtowc,(__pwc,__str,__maxlen))
#else /* __CRT_HAVE_mbtowc */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/mbtowc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbtowc __LIBC_LOCAL_NAME(mbtowc)
#endif /* !__CRT_HAVE_mbtowc */
#endif /* !__local___localdep_mbtowc_defined */
__LOCAL_LIBC(_mbtowc_l) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbtowc_l))(__WCHAR_TYPE__ *__dst, char const *__src, __SIZE_TYPE__ __srclen, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_mbtowc)(__dst, __src, __srclen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbtowc_l_defined
#define __local___localdep__mbtowc_l_defined
#define __localdep__mbtowc_l __LIBC_LOCAL_NAME(_mbtowc_l)
#endif /* !__local___localdep__mbtowc_l_defined */
#endif /* !__local__mbtowc_l_defined */
