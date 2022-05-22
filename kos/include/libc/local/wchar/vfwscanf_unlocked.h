/* HASH CRC-32:0x3c42fb06 */
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
#ifndef __local_vfwscanf_unlocked_defined
#define __local_vfwscanf_unlocked_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc))
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetwc_unlocked_defined
#define __local___localdep_fgetwc_unlocked_defined
#ifdef __CRT_HAVE_fgetwc_unlocked
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,__localdep_fgetwc_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked)
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,__localdep_fgetwc_unlocked,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getwc_nolock)
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,__localdep_fgetwc_unlocked,(__FILE *__restrict __stream),_getwc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,__localdep_fgetwc_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_getwc)
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,__localdep_fgetwc_unlocked,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_fgetwc)
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,__localdep_fgetwc_unlocked,(__FILE *__restrict __stream),fgetwc,(__stream))
#else /* ... */
#undef __local___localdep_fgetwc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fgetwc_unlocked_defined */
#ifndef __local___localdep_format_vwscanf_defined
#define __local___localdep_format_vwscanf_defined
#ifdef __CRT_HAVE_format_vwscanf
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(4) __ATTR_LIBC_WSCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_format_vwscanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#else /* __CRT_HAVE_format_vwscanf */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_vwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vwscanf __LIBC_LOCAL_NAME(format_vwscanf)
#endif /* !__CRT_HAVE_format_vwscanf */
#endif /* !__local___localdep_format_vwscanf_defined */
#ifndef __local___localdep_ungetwc_unlocked_defined
#define __local___localdep_ungetwc_unlocked_defined
#ifdef __CRT_HAVE_ungetwc_unlocked
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc)
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_NCX,__localdep_ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#else /* ... */
#undef __local___localdep_ungetwc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_ungetwc_unlocked_defined */
__NAMESPACE_LOCAL_END
#ifndef ____vfwscanf_unlocked_getc_defined
#define ____vfwscanf_unlocked_getc_defined
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__
__LOCAL_LIBC(vfwscanf_unlocked_getc) __format_word_t
(__FORMATPRINTER_CC __vfwscanf_unlocked_getc)(void *__arg) {
	return (__format_word_t)(__NAMESPACE_LOCAL_SYM __localdep_fgetwc_unlocked)((__FILE *)__arg);
}
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__ */
__LOCAL_LIBC(vfwscanf_unlocked_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vfwscanf_unlocked_ungetc)(void *__arg, __format_word_t __word) {
	return (__NAMESPACE_LOCAL_SYM __localdep_ungetwc_unlocked)((__WINT_TYPE__)__word, (__FILE *)__arg);
}
__NAMESPACE_LOCAL_END
#endif /* !____vfwscanf_unlocked_getc_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vfwscanf_unlocked) __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(vfwscanf_unlocked))(__FILE *__restrict __stream, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
#if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == __SIZEOF_INT__
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vwscanf)((__pformatgetc)(void *)&(__NAMESPACE_LOCAL_SYM __localdep_fgetwc_unlocked),
	                      &__NAMESPACE_LOCAL_SYM __vfwscanf_unlocked_ungetc,
	                      (void *)__stream,
	                      __format, __args);
#else /* __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_FORMAT_WORD_T__ == __SIZEOF_INT__ */
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vwscanf)(&__NAMESPACE_LOCAL_SYM __vfwscanf_unlocked_getc,
	                      &__NAMESPACE_LOCAL_SYM __vfwscanf_unlocked_ungetc,
	                      (void *)__stream,
	                      __format, __args);
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vfwscanf_unlocked_defined
#define __local___localdep_vfwscanf_unlocked_defined
#define __localdep_vfwscanf_unlocked __LIBC_LOCAL_NAME(vfwscanf_unlocked)
#endif /* !__local___localdep_vfwscanf_unlocked_defined */
#else /* (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_ungetwc_unlocked || __CRT_HAVE__ungetwc_nolock || __CRT_HAVE_ungetwc) */
#undef __local_vfwscanf_unlocked_defined
#endif /* (!__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked && !__CRT_HAVE__getwc_nolock && !__CRT_HAVE__fgetwc_nolock && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc) || (!__CRT_HAVE_ungetwc_unlocked && !__CRT_HAVE__ungetwc_nolock && !__CRT_HAVE_ungetwc) */
#endif /* !__local_vfwscanf_unlocked_defined */
