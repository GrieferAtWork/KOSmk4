/* HASH CRC-32:0x4a890180 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_vfc16scanf_defined
#define __local_vfc16scanf_defined
#include <__crt.h>
#include <features.h>
#if ((defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$getwc) || (defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc_unlocked) || (defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$getwc_unlocked)) && ((defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc) || (defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc_unlocked))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc16_defined
#define __local___localdep_fgetc16_defined
#if defined(__CRT_HAVE_fgetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc_unlocked)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_fgetc16_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc16_defined */
#ifndef __local___localdep_format_vc16scanf_defined
#define __local___localdep_format_vc16scanf_defined
#if defined(__CRT_HAVE_format_vwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(4) __ATTR_LIBC_C16SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vc16scanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif defined(__CRT_HAVE_DOS$format_vwscanf)
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_IN(4) __ATTR_LIBC_C16SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vc16scanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_vwscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vc16scanf __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__LIBDCALL*)(__pformatgetc,__pformatungetc,void *,__CHAR16_TYPE__ const *__restrict,__builtin_va_list),__SSIZE_TYPE__(__LIBDCALL&)(__pformatgetc,__pformatungetc,void *,__CHAR16_TYPE__ const *__restrict,__builtin_va_list),format_vwscanf)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_vc16scanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vc16scanf __LIBC_LOCAL_NAME(format_vc16scanf)
#endif /* !... */
#endif /* !__local___localdep_format_vc16scanf_defined */
#ifndef __local___localdep_ungetc16_defined
#define __local___localdep_ungetc16_defined
#if defined(__CRT_HAVE_ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_NCX,__localdep_ungetc16,(__WINT16_TYPE__ __wc, __FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_NCX,__localdep_ungetc16,(__WINT16_TYPE__ __wc, __FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_NCX,__localdep_ungetc16,(__WINT16_TYPE__ __wc, __FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_NCX,__localdep_ungetc16,(__WINT16_TYPE__ __wc, __FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_NCX,__localdep_ungetc16,(__WINT16_TYPE__ __wc, __FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc_unlocked)
__CREDIRECT_DOS(__ATTR_INOUT(2),__WINT16_TYPE__,__NOTHROW_NCX,__localdep_ungetc16,(__WINT16_TYPE__ __wc, __FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __local___localdep_ungetc16_defined
#endif /* !... */
#endif /* !__local___localdep_ungetc16_defined */
__NAMESPACE_LOCAL_END
#ifndef ____vfc16scanf_getc_defined
#define ____vfc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBDCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != 2
__LOCAL_LIBC(vfc16scanf_getc) __format_word_t
(__FORMATPRINTER_CC __vfc16scanf_getc)(void *__arg) {
	return (__format_word_t)(__NAMESPACE_LOCAL_SYM __localdep_fgetc16)((__FILE *)__arg);
}
#endif /* !__LIBDCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 2 */
__LOCAL_LIBC(vfc16scanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __vfc16scanf_ungetc)(void *__arg, __format_word_t __word) {
	return (__NAMESPACE_LOCAL_SYM __localdep_ungetc16)((__WINT16_TYPE__)__word, (__FILE *)__arg);
}
__NAMESPACE_LOCAL_END
#endif /* !____vfc16scanf_getc_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vfc16scanf) __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SIZE_T
__NOTHROW_CB_NCX(__LIBDCALL __LIBC_LOCAL_NAME(vfc16scanf))(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args) {
#if defined(__LIBDCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == 2
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vc16scanf)((__pformatgetc)(void *)&(__NAMESPACE_LOCAL_SYM __localdep_fgetc16),
	                      &__NAMESPACE_LOCAL_SYM __vfc16scanf_ungetc,
	                      (void *)__stream,
	                      __format, __args);
#else /* __LIBDCALL_IS_FORMATPRINTER_CC && __SIZEOF_FORMAT_WORD_T__ == 2 */
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vc16scanf)(&__NAMESPACE_LOCAL_SYM __vfc16scanf_getc,
	                      &__NAMESPACE_LOCAL_SYM __vfc16scanf_ungetc,
	                      (void *)__stream,
	                      __format, __args);
#endif /* !__LIBDCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 2 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vfc16scanf_defined
#define __local___localdep_vfc16scanf_defined
#define __localdep_vfc16scanf __LIBC_LOCAL_NAME(vfc16scanf)
#endif /* !__local___localdep_vfc16scanf_defined */
#else /* ((__CRT_HAVE_fgetwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fgetwc || (__CRT_HAVE_getwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$getwc || (__CRT_HAVE_fgetwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fgetwc_unlocked || (__CRT_HAVE_getwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$getwc_unlocked) && ((__CRT_HAVE_ungetwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$ungetwc || (__CRT_HAVE_ungetwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$ungetwc_unlocked) */
#undef __local_vfc16scanf_defined
#endif /* ((!__CRT_HAVE_fgetwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fgetwc && (!__CRT_HAVE_getwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$getwc && (!__CRT_HAVE_fgetwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fgetwc_unlocked && (!__CRT_HAVE_getwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$getwc_unlocked) || ((!__CRT_HAVE_ungetwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$ungetwc && (!__CRT_HAVE_ungetwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$ungetwc_unlocked) */
#endif /* !__local_vfc16scanf_defined */
