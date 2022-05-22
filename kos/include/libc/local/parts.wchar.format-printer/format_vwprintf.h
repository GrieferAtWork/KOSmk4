/* HASH CRC-32:0x63273283 */
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
#ifndef __local_format_vwprintf_defined
#define __local_format_vwprintf_defined
#include <__crt.h>
#include <kos/anno.h>
#include <bits/crt/wformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_16to32_defined
#define __local___localdep_format_16to32_defined
#if defined(__CRT_HAVE_format_wto32) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,__localdep_format_16to32,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto32,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wto32)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,__localdep_format_16to32,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),DOS$format_wto32,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
#include <libc/local/unicode/format_wto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_16to32 __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__C16FORMATPRINTER_CC*)(void *,__CHAR16_TYPE__ const *,__SIZE_TYPE__),__SSIZE_TYPE__(__C16FORMATPRINTER_CC&)(void *,__CHAR16_TYPE__ const *,__SIZE_TYPE__),format_wto32)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/format_16to32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_16to32 __LIBC_LOCAL_NAME(format_16to32)
#endif /* !... */
#endif /* !__local___localdep_format_16to32_defined */
#ifndef __local___localdep_format_32to16_defined
#define __local___localdep_format_32to16_defined
#if defined(__CRT_HAVE_format_wto16) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,__localdep_format_32to16,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto16,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wto16)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,__localdep_format_32to16,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),KOS$format_wto16,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
#include <libc/local/unicode/format_wto16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_32to16 __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__C32FORMATPRINTER_CC*)(void *,__CHAR32_TYPE__ const *,__SIZE_TYPE__),__SSIZE_TYPE__(__C32FORMATPRINTER_CC&)(void *,__CHAR32_TYPE__ const *,__SIZE_TYPE__),format_wto16)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/format_32to16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_32to16 __LIBC_LOCAL_NAME(format_32to16)
#endif /* !... */
#endif /* !__local___localdep_format_32to16_defined */
#ifndef __local___localdep_format_8tow_defined
#define __local___localdep_format_8tow_defined
#ifdef __CRT_HAVE_format_8tow
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_8tow,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8tow,(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_8tow */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/format_8tow.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_8tow __LIBC_LOCAL_NAME(format_8tow)
#endif /* !__CRT_HAVE_format_8tow */
#endif /* !__local___localdep_format_8tow_defined */
#ifndef __local___localdep_format_c16escape_defined
#define __local___localdep_format_c16escape_defined
#if defined(__CRT_HAVE_format_wescape) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c16escape,(__pc16formatprinter __printer, void *__arg, __CHAR16_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_DOS$format_wescape)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c16escape,(__pc16formatprinter __printer, void *__arg, __CHAR16_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
#include <libc/local/parts.wchar.format-printer/format_wescape.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c16escape __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__LIBDCALL*)(__pc16formatprinter,void *,__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__,unsigned int),__SSIZE_TYPE__(__LIBDCALL&)(__pc16formatprinter,void *,__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__,unsigned int),format_wescape)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_c16escape.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c16escape __LIBC_LOCAL_NAME(format_c16escape)
#endif /* !... */
#endif /* !__local___localdep_format_c16escape_defined */
#ifndef __local___localdep_format_c16width_defined
#define __local___localdep_format_c16width_defined
#if defined(__CRT_HAVE_format_wwidth) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,__localdep_format_c16width,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wwidth)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,__localdep_format_c16width,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),DOS$format_wwidth,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
#include <libc/local/parts.wchar.format-printer/format_wwidth.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c16width __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__C16FORMATPRINTER_CC*)(void *,__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__),__SSIZE_TYPE__(__C16FORMATPRINTER_CC&)(void *,__CHAR16_TYPE__ const *__restrict,__SIZE_TYPE__),format_wwidth)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_c16width.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c16width __LIBC_LOCAL_NAME(format_c16width)
#endif /* !... */
#endif /* !__local___localdep_format_c16width_defined */
#ifndef __local___localdep_format_c32escape_defined
#define __local___localdep_format_c32escape_defined
#if defined(__CRT_HAVE_format_wescape) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c32escape,(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_KOS$format_wescape)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c32escape,(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
#include <libc/local/parts.wchar.format-printer/format_wescape.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c32escape __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__LIBKCALL*)(__pc32formatprinter,void *,__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__,unsigned int),__SSIZE_TYPE__(__LIBKCALL&)(__pc32formatprinter,void *,__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__,unsigned int),format_wescape)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_c32escape.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c32escape __LIBC_LOCAL_NAME(format_c32escape)
#endif /* !... */
#endif /* !__local___localdep_format_c32escape_defined */
#ifndef __local___localdep_format_c32width_defined
#define __local___localdep_format_c32width_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_format_length) && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_length)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),KOS$format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wwidth)
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),KOS$format_wwidth,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <bits/crt/uformat-printer.h>
#include <libc/local/parts.wchar.format-printer/format_wwidth.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c32width __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__C32FORMATPRINTER_CC*)(void *,__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__),__SSIZE_TYPE__(__C32FORMATPRINTER_CC&)(void *,__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__),format_wwidth)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.format-printer/format_c32width.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_c32width __LIBC_LOCAL_NAME(format_c32width)
#endif /* !... */
#endif /* !__local___localdep_format_c32width_defined */
#ifndef __local___localdep_format_escape_defined
#define __local___localdep_format_escape_defined
#ifdef __CRT_HAVE_format_escape
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_escape,(__pformatprinter __printer, void *__arg, char const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_escape,(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_format_quote)
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_escape,(__pformatprinter __printer, void *__arg, char const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_quote,(__printer,__arg,__text,__textlen,__flags))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_escape.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_escape __LIBC_LOCAL_NAME(format_escape)
#endif /* !... */
#endif /* !__local___localdep_format_escape_defined */
#ifndef __local___localdep_format_wescape_defined
#define __local___localdep_format_wescape_defined
#ifdef __CRT_HAVE_format_wescape
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_wescape,(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#else /* __CRT_HAVE_format_wescape */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_wescape.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_wescape __LIBC_LOCAL_NAME(format_wescape)
#endif /* !__CRT_HAVE_format_wescape */
#endif /* !__local___localdep_format_wescape_defined */
#ifndef __local___localdep_format_whexdump_defined
#define __local___localdep_format_whexdump_defined
#ifdef __CRT_HAVE_format_whexdump
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_whexdump,(__pwformatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
#else /* __CRT_HAVE_format_whexdump */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_whexdump.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_whexdump __LIBC_LOCAL_NAME(format_whexdump)
#endif /* !__CRT_HAVE_format_whexdump */
#endif /* !__local___localdep_format_whexdump_defined */
#ifndef __local___localdep_format_width_defined
#define __local___localdep_format_width_defined
#ifdef __CRT_HAVE_format_width
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_width,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),format_width,(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_width */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_width.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_width __LIBC_LOCAL_NAME(format_width)
#endif /* !__CRT_HAVE_format_width */
#endif /* !__local___localdep_format_width_defined */
#ifndef __local___localdep_format_wrepeat_defined
#define __local___localdep_format_wrepeat_defined
#ifdef __CRT_HAVE_format_wrepeat
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_wrepeat,(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#else /* __CRT_HAVE_format_wrepeat */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_wrepeat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_wrepeat __LIBC_LOCAL_NAME(format_wrepeat)
#endif /* !__CRT_HAVE_format_wrepeat */
#endif /* !__local___localdep_format_wrepeat_defined */
#ifndef __local___localdep_format_wwidth_defined
#define __local___localdep_format_wwidth_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_format_length) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__WFORMATPRINTER_CC,__localdep_format_wwidth,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth)
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__WFORMATPRINTER_CC,__localdep_format_wwidth,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_wwidth.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_wwidth __LIBC_LOCAL_NAME(format_wwidth)
#endif /* !... */
#endif /* !__local___localdep_format_wwidth_defined */
#ifndef __local___localdep_strerror_defined
#define __local___localdep_strerror_defined
#ifdef __CRT_HAVE_strerror
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_strerror,(__errno_t __errnum),strerror,(__errnum))
#elif defined(__CRT_HAVE_xstrerror)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_strerror,(__errno_t __errnum),xstrerror,(__errnum))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strerror.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerror __LIBC_LOCAL_NAME(strerror)
#endif /* !... */
#endif /* !__local___localdep_strerror_defined */
#ifndef __local___localdep_unicode_writeutf16_defined
#define __local___localdep_unicode_writeutf16_defined
#ifdef __CRT_HAVE_unicode_writeutf16
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUT(1),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_unicode_writeutf16,(__CHAR16_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf16,(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf16 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_writeutf16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_writeutf16 __LIBC_LOCAL_NAME(unicode_writeutf16)
#endif /* !__CRT_HAVE_unicode_writeutf16 */
#endif /* !__local___localdep_unicode_writeutf16_defined */
__NAMESPACE_LOCAL_END
#include <parts/printf-config.h>
#include <bits/types.h>
#include <libc/template/itoa_digits.h>
#include <libc/parts.uchar.string.h>
#include <libc/string.h>
#include <libc/errno.h>
#include <hybrid/__assert.h>
#include <hybrid/__alloca.h>
#ifndef __NO_PRINTF_DISASM
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#endif /* !__KERNEL__ || !__KOS__ */
#include <libdisasm/disassembler.h>
#endif /* !__NO_PRINTF_DISASM */
#ifndef __NO_PRINTF_VINFO
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#include <libdebuginfo/addr2line.h>
#else /* !__KERNEL__ || !__KOS__ */
#include <kernel/addr2line.h>
#endif /* __KERNEL__ && __KOS__ */
#endif /* !__NO_PRINTF_VINFO */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(format_vwprintf) __ATTR_IN(3) __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(format_vwprintf))(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
#ifndef __INTELLISENSE__
#define __FORMAT_PRINTER            __printer
#define __FORMAT_ARG                __arg
#define __FORMAT_FORMAT             __format
#define __FORMAT_ARGS               __args
#define __CHAR_TYPE                 __WCHAR_TYPE__
#define __CHAR_SIZE                 __SIZEOF_WCHAR_T__
#define __FORMAT_STRERROR           (__NAMESPACE_LOCAL_SYM __localdep_strerror)
#define __FORMAT_REPEAT             (__NAMESPACE_LOCAL_SYM __localdep_format_wrepeat)
#define __FORMAT_HEXDUMP            (__NAMESPACE_LOCAL_SYM __localdep_format_whexdump)
#define __FORMAT_WIDTH              (__NAMESPACE_LOCAL_SYM __localdep_format_wwidth)
#define __FORMAT_ESCAPE             (__NAMESPACE_LOCAL_SYM __localdep_format_wescape)
#define __FORMAT_WIDTH8             (__NAMESPACE_LOCAL_SYM __localdep_format_width)
#define __FORMAT_ESCAPE8            (__NAMESPACE_LOCAL_SYM __localdep_format_escape)
#define __FORMAT_UNICODE_FORMAT8    (__NAMESPACE_LOCAL_SYM __localdep_format_8tow)
#if __SIZEOF_WCHAR_T__ == 2
#define __FORMAT_WIDTH32            (__NAMESPACE_LOCAL_SYM __localdep_format_c32width)
#define __FORMAT_ESCAPE32           (__NAMESPACE_LOCAL_SYM __localdep_format_c32escape)
#define __FORMAT_UNICODE_WRITECHAR  (__NAMESPACE_LOCAL_SYM __localdep_unicode_writeutf16)
#define __FORMAT_UNICODE_FORMAT32   (__NAMESPACE_LOCAL_SYM __localdep_format_32to16)
#else /* __SIZEOF_WCHAR_T__ == 2 */
#define __FORMAT_WIDTH16            (__NAMESPACE_LOCAL_SYM __localdep_format_c16width)
#define __FORMAT_ESCAPE16           (__NAMESPACE_LOCAL_SYM __localdep_format_c16escape)
#define __FORMAT_UNICODE_WRITECHAR(__dst, __ch) ((__dst)[0] = (__ch), (__dst) + 1)
#define __FORMAT_UNICODE_FORMAT16   (__NAMESPACE_LOCAL_SYM __localdep_format_16to32)
#endif /* __SIZEOF_WCHAR_T__ != 2 */
#include <libc/template/format-printf.h>
#endif /* !__INTELLISENSE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_vwprintf_defined
#define __local___localdep_format_vwprintf_defined
#define __localdep_format_vwprintf __LIBC_LOCAL_NAME(format_vwprintf)
#endif /* !__local___localdep_format_vwprintf_defined */
#endif /* !__local_format_vwprintf_defined */
