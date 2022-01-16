/* HASH CRC-32:0xfc81134e */
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
#ifndef __local_file_wprinter_defined
#define __local_file_wprinter_defined
#include <__crt.h>
#if defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fputwc_defined
#define __local___localdep_fputwc_defined
#ifdef __CRT_HAVE_fputwc
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputwc,(__WCHAR_TYPE__ __wc, __FILE *__stream),putwc,(__wc,__stream))
#else /* ... */
#undef __local___localdep_fputwc_defined
#endif /* !... */
#endif /* !__local___localdep_fputwc_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(file_wprinter) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(file_wprinter))(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) {
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < __datalen; ++__i) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_fputwc)(__data[__i], (__FILE *)__arg) == __WEOF)
			break;
	}
	return (__SSIZE_TYPE__)__i;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_file_wprinter_defined
#define __local___localdep_file_wprinter_defined
#define __localdep_file_wprinter __LIBC_LOCAL_NAME(file_wprinter)
#endif /* !__local___localdep_file_wprinter_defined */
#else /* __CRT_HAVE_fputwc || __CRT_HAVE_putwc */
#undef __local_file_wprinter_defined
#endif /* !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc */
#endif /* !__local_file_wprinter_defined */
