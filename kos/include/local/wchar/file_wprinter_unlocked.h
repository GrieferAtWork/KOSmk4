/* HASH CRC-32:0xc94d9431 */
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
#ifndef __local_file_wprinter_unlocked_defined
#define __local_file_wprinter_unlocked_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fputwc_unlocked) || (defined(__CRT_HAVE_DOS$fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fputwc_unlocked from wchar */
#ifndef __local___localdep_fputwc_unlocked_defined
#define __local___localdep_fputwc_unlocked_defined 1
#ifdef __CRT_HAVE_fputwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputwc_unlocked,(__WCHAR_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputwc_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputwc_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#else /* ... */
#undef __local___localdep_fputwc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fputwc_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <asm/stdio.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__LOCAL_LIBC(file_wprinter_unlocked) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(file_wprinter_unlocked))(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) {
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < __datalen; ++__i) {
		if (__localdep_fputwc_unlocked(__data[__i], (__FILE *)__arg) == __WEOF)
			break;
	}
	return (__SSIZE_TYPE__)__i;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_file_wprinter_unlocked_defined
#define __local___localdep_file_wprinter_unlocked_defined 1
#define __localdep_file_wprinter_unlocked __LIBC_LOCAL_NAME(file_wprinter_unlocked)
#endif /* !__local___localdep_file_wprinter_unlocked_defined */
#else /* __CRT_HAVE_fputwc_unlocked || (__CRT_HAVE_DOS$fputwc_unlocked && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$_fputwc_nolock && __SIZEOF_WCHAR_T__ == 2) */
#undef __local_file_wprinter_unlocked_defined
#endif /* !__CRT_HAVE_fputwc_unlocked && (!__CRT_HAVE_DOS$fputwc_unlocked || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$_fputwc_nolock || !__SIZEOF_WCHAR_T__ == 2) */
#endif /* !__local_file_wprinter_unlocked_defined */
