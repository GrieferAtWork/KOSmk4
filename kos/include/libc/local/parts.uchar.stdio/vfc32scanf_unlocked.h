/* HASH CRC-32:0x447460e */
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
#ifndef __local_vfc32scanf_unlocked_defined
#define __local_vfc32scanf_unlocked_defined
#include <__crt.h>
#if ((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc_unlocked) || (defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc_unlocked) || (defined(__CRT_HAVE__getwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_getwc_nolock) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fgetwc_nolock) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc) || (defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc)) && ((defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc_unlocked) || (defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_ungetwc_nolock) || (defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc))
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc32_unlocked_defined
#define __local___localdep_fgetc32_unlocked_defined
#if defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_KOS$fgetwc_unlocked)
__CREDIRECT_KOS(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_KOS$getwc_unlocked)
__CREDIRECT_KOS(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_getwc_nolock,(__stream))
#elif defined(__CRT_HAVE_KOS$_getwc_nolock)
__CREDIRECT_KOS(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_getwc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_KOS$_fgetwc_nolock)
__CREDIRECT_KOS(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_KOS$getwc)
__CREDIRECT_KOS(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_KOS$fgetwc)
__CREDIRECT_KOS(__ATTR_ACCESS_RW(1),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc,(__stream))
#else /* ... */
#undef __local___localdep_fgetc32_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc32_unlocked_defined */
#ifndef __local___localdep_format_vc32scanf_defined
#define __local___localdep_format_vc32scanf_defined
#if defined(__CRT_HAVE_format_vwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__localdep_format_vc32scanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif defined(__CRT_HAVE_KOS$format_vwscanf)
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__localdep_format_vc32scanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_vwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vc32scanf __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__LIBKCALL*)(__pformatgetc,__pformatungetc,void *,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),__SSIZE_TYPE__(__LIBKCALL&)(__pformatgetc,__pformatungetc,void *,__CHAR32_TYPE__ const *__restrict,__builtin_va_list),format_vwscanf)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_vc32scanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vc32scanf __LIBC_LOCAL_NAME(format_vc32scanf)
#endif /* !... */
#endif /* !__local___localdep_format_vc32scanf_defined */
#ifndef __local___localdep_ungetc32_unlocked_defined
#define __local___localdep_ungetc32_unlocked_defined
#if defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RW(2),__WINT32_TYPE__,__NOTHROW_NCX,__localdep_ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc_unlocked)
__CREDIRECT_KOS(__ATTR_ACCESS_RW(2),__WINT32_TYPE__,__NOTHROW_NCX,__localdep_ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RW(2),__WINT32_TYPE__,__NOTHROW_NCX,__localdep_ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_KOS$_ungetwc_nolock)
__CREDIRECT_KOS(__ATTR_ACCESS_RW(2),__WINT32_TYPE__,__NOTHROW_NCX,__localdep_ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RW(2),__WINT32_TYPE__,__NOTHROW_NCX,__localdep_ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc)
__CREDIRECT_KOS(__ATTR_ACCESS_RW(2),__WINT32_TYPE__,__NOTHROW_NCX,__localdep_ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#else /* ... */
#undef __local___localdep_ungetc32_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_ungetc32_unlocked_defined */
__NAMESPACE_LOCAL_END
#ifndef ____vfc32scanf_unlocked_getc_defined
#define ____vfc32scanf_unlocked_getc_defined
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBKCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__
__LOCAL_LIBC(vfc32scanf_unlocked_getc) __format_word_t
(__FORMATPRINTER_CC __vfc32scanf_unlocked_getc)(void *__arg) {
	return (__format_word_t)(__NAMESPACE_LOCAL_SYM __localdep_fgetc32_unlocked)((__FILE *)__arg);
}
#endif /* !__LIBKCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__ */
__LOCAL_LIBC(vfc32scanf_unlocked_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vfc32scanf_unlocked_ungetc)(void *__arg, __format_word_t __word) {
	return (__NAMESPACE_LOCAL_SYM __localdep_ungetc32_unlocked)((__WINT32_TYPE__)__word, (__FILE *)__arg);
}
__NAMESPACE_LOCAL_END
#endif /* !____vfc32scanf_unlocked_getc_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vfc32scanf_unlocked) __ATTR_WUNUSED __ATTR_ACCESS_RW(1) __ATTR_LIBC_C32SCANF(2, 0) __ATTR_NONNULL((2)) __STDC_INT_AS_SIZE_T
(__LIBKCALL __LIBC_LOCAL_NAME(vfc32scanf_unlocked))(__FILE *__restrict __stream, __CHAR32_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
#if defined(__LIBKCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == __SIZEOF_INT__
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vc32scanf)((__pformatgetc)(void *)&(__NAMESPACE_LOCAL_SYM __localdep_fgetc32_unlocked),
	                      &__NAMESPACE_LOCAL_SYM __vfc32scanf_unlocked_ungetc,
	                      (void *)__stream,
	                      __format, __args);
#else /* __LIBKCALL_IS_FORMATPRINTER_CC && __SIZEOF_FORMAT_WORD_T__ == __SIZEOF_INT__ */
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vc32scanf)(&__NAMESPACE_LOCAL_SYM __vfc32scanf_unlocked_getc,
	                      &__NAMESPACE_LOCAL_SYM __vfc32scanf_unlocked_ungetc,
	                      (void *)__stream,
	                      __format, __args);
#endif /* !__LIBKCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_INT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vfc32scanf_unlocked_defined
#define __local___localdep_vfc32scanf_unlocked_defined
#define __localdep_vfc32scanf_unlocked __LIBC_LOCAL_NAME(vfc32scanf_unlocked)
#endif /* !__local___localdep_vfc32scanf_unlocked_defined */
#else /* ((__CRT_HAVE_fgetwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fgetwc_unlocked || (__CRT_HAVE_getwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$getwc_unlocked || (__CRT_HAVE__getwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_getwc_nolock || (__CRT_HAVE__fgetwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_fgetwc_nolock || (__CRT_HAVE_getwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$getwc || (__CRT_HAVE_fgetwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fgetwc) && ((__CRT_HAVE_ungetwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$ungetwc_unlocked || (__CRT_HAVE__ungetwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_ungetwc_nolock || (__CRT_HAVE_ungetwc && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$ungetwc) */
#undef __local_vfc32scanf_unlocked_defined
#endif /* ((!__CRT_HAVE_fgetwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fgetwc_unlocked && (!__CRT_HAVE_getwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$getwc_unlocked && (!__CRT_HAVE__getwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_getwc_nolock && (!__CRT_HAVE__fgetwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_fgetwc_nolock && (!__CRT_HAVE_getwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$getwc && (!__CRT_HAVE_fgetwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fgetwc) || ((!__CRT_HAVE_ungetwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$ungetwc_unlocked && (!__CRT_HAVE__ungetwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_ungetwc_nolock && (!__CRT_HAVE_ungetwc || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$ungetwc) */
#endif /* !__local_vfc32scanf_unlocked_defined */
