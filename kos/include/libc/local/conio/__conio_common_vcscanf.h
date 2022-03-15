/* HASH CRC-32:0xbfdd02e4 */
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
#ifndef __local___conio_common_vcscanf_defined
#define __local___conio_common_vcscanf_defined
#include <__crt.h>
#include <features.h>
#if ((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche)) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__getwche_defined
#define __local___localdep__getwche_defined
#if defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep__getwche,(void),_getwche_nolock,())
#elif defined(__CRT_HAVE__getwche)
__CREDIRECT(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep__getwche,(void),_getwche,())
#else /* ... */
#undef __local___localdep__getwche_defined
#endif /* !... */
#endif /* !__local___localdep__getwche_defined */
#ifndef __local___localdep__ungetwch_defined
#define __local___localdep__ungetwch_defined
#if defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,__WINT_TYPE__,__NOTHROW_NCX,__localdep__ungetwch,(__WINT_TYPE__ __ch),_ungetwch_nolock,(__ch))
#elif defined(__CRT_HAVE__ungetwch)
__CREDIRECT(,__WINT_TYPE__,__NOTHROW_NCX,__localdep__ungetwch,(__WINT_TYPE__ __ch),_ungetwch,(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wconio/_ungetwch.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ungetwch __LIBC_LOCAL_NAME(_ungetwch)
#else /* ... */
#undef __local___localdep__ungetwch_defined
#endif /* !... */
#endif /* !__local___localdep__ungetwch_defined */
#ifndef __local___localdep_format_vscanf_defined
#define __local___localdep_format_vscanf_defined
#ifdef __CRT_HAVE_format_vscanf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LIBC_SCANF(4, 0) __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__localdep_format_vscanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vscanf,(__pgetc,__pungetc,__arg,__format,__args))
#else /* __CRT_HAVE_format_vscanf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vscanf __LIBC_LOCAL_NAME(format_vscanf)
#endif /* !__CRT_HAVE_format_vscanf */
#endif /* !__local___localdep_format_vscanf_defined */
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__conio_common_vcscanf_getc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __conio_common_vcscanf_getc)(void *__UNUSED(__arg)) {
	return (__SSIZE_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep__getwche)();
}
__LOCAL_LIBC(__conio_common_vcscanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __conio_common_vcscanf_ungetc)(void *__arg, __CHAR32_TYPE__ __ch) {
	return (__NAMESPACE_LOCAL_SYM __localdep__ungetwch)((int)(unsigned int)__ch);
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__conio_common_vcscanf) __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__conio_common_vcscanf))(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args) {
	(void)__options;
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vscanf)(&__NAMESPACE_LOCAL_SYM __conio_common_vcscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM __conio_common_vcscanf_ungetc,
	                     __NULLPTR, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___conio_common_vcscanf_defined
#define __local___localdep___conio_common_vcscanf_defined
#define __localdep___conio_common_vcscanf __LIBC_LOCAL_NAME(__conio_common_vcscanf)
#endif /* !__local___localdep___conio_common_vcscanf_defined */
#else /* ((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked))) */
#undef __local___conio_common_vcscanf_defined
#endif /* ((!__CRT_HAVE__getwche_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__getwche) || ((!__CRT_HAVE__ungetwch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__ungetwch && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked))) */
#endif /* !__local___conio_common_vcscanf_defined */
