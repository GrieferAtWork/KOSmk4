/* HASH CRC-32:0x1c2106b4 */
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
#ifndef __local_format_vwprintf_defined
#define __local_format_vwprintf_defined 1
#include <__crt.h>
#include <kos/anno.h>
#include <bits/wformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: format_16to32 from unicode */
#ifndef __local___localdep_format_16to32_defined
#define __local___localdep_format_16to32_defined 1
#if defined(__CRT_HAVE_format_wto32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-32 output */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_16to32,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto32,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wto32)
/* Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-32 output */
__CREDIRECT_DOS(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_16to32,(void *__arg, __CHAR16_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto32,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/unicode/format_wto32.h>
__NAMESPACE_LOCAL_BEGIN
/* Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-32 output */
#define __localdep_format_16to32 (*(__SSIZE_TYPE__(__LIBDCALL *)(void *, __CHAR16_TYPE__ const *, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(format_wto32))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/unicode/format_16to32.h>
__NAMESPACE_LOCAL_BEGIN
/* Format printer (compatible with `pc16formatprinter') for
 * converting UTF-16 unicode input data into a UTF-32 output */
#define __localdep_format_16to32 __LIBC_LOCAL_NAME(format_16to32)
#endif /* !... */
#endif /* !__local___localdep_format_16to32_defined */
/* Dependency: format_32to16 from unicode */
#ifndef __local___localdep_format_32to16_defined
#define __local___localdep_format_32to16_defined 1
#if defined(__CRT_HAVE_format_wto16) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16 output */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_32to16,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto16,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wto16)
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16 output */
__CREDIRECT_KOS(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_32to16,(void *__arg, __CHAR32_TYPE__ const *__data, __SIZE_TYPE__ __datalen),format_wto16,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/unicode/format_wto16.h>
__NAMESPACE_LOCAL_BEGIN
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16 output */
#define __localdep_format_32to16 (*(__SSIZE_TYPE__(__LIBKCALL *)(void *, __CHAR32_TYPE__ const *, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(format_wto16))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/unicode/format_32to16.h>
__NAMESPACE_LOCAL_BEGIN
/* Format printer (compatible with `__pc32formatprinter') for
 * converting UTF-32 unicode input data into a UTF-16 output */
#define __localdep_format_32to16 __LIBC_LOCAL_NAME(format_32to16)
#endif /* !... */
#endif /* !__local___localdep_format_32to16_defined */
/* Dependency: format_8to16 from unicode */
#ifndef __local___localdep_format_8to16_defined
#define __local___localdep_format_8to16_defined 1
#ifdef __CRT_HAVE_format_8to16
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-16 output */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_8to16,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8to16,(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_8to16 */
__NAMESPACE_LOCAL_END
#include <local/unicode/format_8to16.h>
__NAMESPACE_LOCAL_BEGIN
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-16 output */
#define __localdep_format_8to16 __LIBC_LOCAL_NAME(format_8to16)
#endif /* !__CRT_HAVE_format_8to16 */
#endif /* !__local___localdep_format_8to16_defined */
/* Dependency: format_8to32 from unicode */
#ifndef __local___localdep_format_8to32_defined
#define __local___localdep_format_8to32_defined 1
#ifdef __CRT_HAVE_format_8to32
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-32 output */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_8to32,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8to32,(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_8to32 */
__NAMESPACE_LOCAL_END
#include <local/unicode/format_8to32.h>
__NAMESPACE_LOCAL_BEGIN
/* Format printer (compatible with `__pformatprinter') for
 * converting UTF-8 unicode input data into a UTF-32 output */
#define __localdep_format_8to32 __LIBC_LOCAL_NAME(format_8to32)
#endif /* !__CRT_HAVE_format_8to32 */
#endif /* !__local___localdep_format_8to32_defined */
/* Dependency: format_c16escape from parts.uchar.format-printer */
#ifndef __local___localdep_format_c16escape_defined
#define __local___localdep_format_c16escape_defined 1
#if defined(__CRT_HAVE_format_wescape) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <bits/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c16escape,(__pc16formatprinter __printer, void *__arg, __CHAR16_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_DOS$format_wescape)
__NAMESPACE_LOCAL_END
#include <bits/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c16escape,(__pc16formatprinter __printer, void *__arg, __CHAR16_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <bits/uformat-printer.h>
#include <local/parts.wchar.format-printer/format_wescape.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
#define __localdep_format_c16escape (*(__SSIZE_TYPE__(__LIBDCALL *)(__pc16formatprinter, void *, __CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__, unsigned int))&__LIBC_LOCAL_NAME(format_wescape))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.format-printer/format_c16escape.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
#define __localdep_format_c16escape __LIBC_LOCAL_NAME(format_c16escape)
#endif /* !... */
#endif /* !__local___localdep_format_c16escape_defined */
/* Dependency: format_c16width from parts.uchar.format-printer */
#ifndef __local___localdep_format_c16width_defined
#define __local___localdep_format_c16width_defined 1
#if defined(__CRT_HAVE_format_wwidth) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c16width,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wwidth)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c16width,(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/parts.wchar.format-printer/format_wwidth.h>
__NAMESPACE_LOCAL_BEGIN
/* Returns the width (number of characters; not bytes) of the given unicode string */
#define __localdep_format_c16width (*(__SSIZE_TYPE__(__LIBDCALL *)(void *, __CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(format_wwidth))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.format-printer/format_c16width.h>
__NAMESPACE_LOCAL_BEGIN
/* Returns the width (number of characters; not bytes) of the given unicode string */
#define __localdep_format_c16width __LIBC_LOCAL_NAME(format_c16width)
#endif /* !... */
#endif /* !__local___localdep_format_c16width_defined */
/* Dependency: format_c32escape from parts.uchar.format-printer */
#ifndef __local___localdep_format_c32escape_defined
#define __local___localdep_format_c32escape_defined 1
#if defined(__CRT_HAVE_format_wescape) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c32escape,(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_KOS$format_wescape)
__NAMESPACE_LOCAL_END
#include <bits/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_c32escape,(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <bits/uformat-printer.h>
#include <local/parts.wchar.format-printer/format_wescape.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
#define __localdep_format_c32escape (*(__SSIZE_TYPE__(__LIBKCALL *)(__pc32formatprinter, void *, __CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__, unsigned int))&__LIBC_LOCAL_NAME(format_wescape))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.format-printer/format_c32escape.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
#define __localdep_format_c32escape __LIBC_LOCAL_NAME(format_c32escape)
#endif /* !... */
#endif /* !__local___localdep_format_c32escape_defined */
/* Dependency: format_c32width from parts.uchar.format-printer */
#ifndef __local___localdep_format_c32width_defined
#define __local___localdep_format_c32width_defined 1
#if defined(__CRT_HAVE_format_length) && defined(__LIBCCALL_IS_LIBKCALL)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_length)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wwidth)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <local/parts.wchar.format-printer/format_wwidth.h>
__NAMESPACE_LOCAL_BEGIN
/* Returns the width (number of characters; not bytes) of the given unicode string */
#define __localdep_format_c32width (*(__SSIZE_TYPE__(__LIBKCALL *)(void *, __CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(format_wwidth))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.format-printer/format_c32width.h>
__NAMESPACE_LOCAL_BEGIN
/* Returns the width (number of characters; not bytes) of the given unicode string */
#define __localdep_format_c32width __LIBC_LOCAL_NAME(format_c32width)
#endif /* !... */
#endif /* !__local___localdep_format_c32width_defined */
/* Dependency: format_escape from format-printer */
#ifndef __local___localdep_format_escape_defined
#define __local___localdep_format_escape_defined 1
#ifdef __CRT_HAVE_format_escape
__NAMESPACE_LOCAL_END
#include <bits/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_escape,(__pformatprinter __printer, void *__arg, char const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_escape,(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_format_quote)
__NAMESPACE_LOCAL_END
#include <bits/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_escape,(__pformatprinter __printer, void *__arg, char const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_quote,(__printer,__arg,__text,__textlen,__flags))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/format-printer/format_escape.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
#define __localdep_format_escape __LIBC_LOCAL_NAME(format_escape)
#endif /* !... */
#endif /* !__local___localdep_format_escape_defined */
/* Dependency: format_wescape from parts.wchar.format-printer */
#ifndef __local___localdep_format_wescape_defined
#define __local___localdep_format_wescape_defined 1
#ifdef __CRT_HAVE_format_wescape
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_wescape,(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#else /* __CRT_HAVE_format_wescape */
__NAMESPACE_LOCAL_END
#include <local/parts.wchar.format-printer/format_wescape.h>
__NAMESPACE_LOCAL_BEGIN
/* Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2: >> Hello \"World\" W\nhat a great day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This function escapes all control and non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a behavior that may be modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: PRINTER: A function called for all quoted portions of the text
 * @param: TEXTLEN: The total number of bytes to escape, starting at `text' */
#define __localdep_format_wescape __LIBC_LOCAL_NAME(format_wescape)
#endif /* !__CRT_HAVE_format_wescape */
#endif /* !__local___localdep_format_wescape_defined */
/* Dependency: format_whexdump from parts.wchar.format-printer */
#ifndef __local___localdep_format_whexdump_defined
#define __local___localdep_format_whexdump_defined 1
#ifdef __CRT_HAVE_format_whexdump
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_whexdump,(__pwformatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
#else /* __CRT_HAVE_format_whexdump */
__NAMESPACE_LOCAL_END
#include <local/parts.wchar.format-printer/format_whexdump.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
#define __localdep_format_whexdump __LIBC_LOCAL_NAME(format_whexdump)
#endif /* !__CRT_HAVE_format_whexdump */
#endif /* !__local___localdep_format_whexdump_defined */
/* Dependency: format_width from format-printer */
#ifndef __local___localdep_format_width_defined
#define __local___localdep_format_width_defined 1
#ifdef __CRT_HAVE_format_width
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_width,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),format_width,(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_width */
__NAMESPACE_LOCAL_END
#include <local/format-printer/format_width.h>
__NAMESPACE_LOCAL_BEGIN
/* Returns the width (number of characters; not bytes) of the given unicode string */
#define __localdep_format_width __LIBC_LOCAL_NAME(format_width)
#endif /* !__CRT_HAVE_format_width */
#endif /* !__local___localdep_format_width_defined */
/* Dependency: format_wrepeat from parts.wchar.format-printer */
#ifndef __local___localdep_format_wrepeat_defined
#define __local___localdep_format_wrepeat_defined 1
#ifdef __CRT_HAVE_format_wrepeat
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_wrepeat,(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#else /* __CRT_HAVE_format_wrepeat */
__NAMESPACE_LOCAL_END
#include <local/parts.wchar.format-printer/format_wrepeat.h>
__NAMESPACE_LOCAL_BEGIN
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
#define __localdep_format_wrepeat __LIBC_LOCAL_NAME(format_wrepeat)
#endif /* !__CRT_HAVE_format_wrepeat */
#endif /* !__local___localdep_format_wrepeat_defined */
/* Dependency: format_wwidth from parts.wchar.format-printer */
#ifndef __local___localdep_format_wwidth_defined
#define __local___localdep_format_wwidth_defined 1
#if defined(__CRT_HAVE_format_length) && __SIZEOF_WCHAR_T__ == 4
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_wwidth,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_wwidth,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.wchar.format-printer/format_wwidth.h>
__NAMESPACE_LOCAL_BEGIN
/* Returns the width (number of characters; not bytes) of the given unicode string */
#define __localdep_format_wwidth __LIBC_LOCAL_NAME(format_wwidth)
#endif /* !... */
#endif /* !__local___localdep_format_wwidth_defined */
/* Dependency: printf from stdio */
#ifndef __local___localdep_printf_defined
#define __local___localdep_printf_defined 1
#if __has_builtin(__builtin_printf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_printf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_printf,(char const *__restrict __format, ...),printf,{ return __builtin_printf(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_printf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_unlocked");
#elif defined(__CRT_HAVE_printf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf");
#elif defined(__CRT_HAVE__IO_printf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_printf");
#elif defined(__CRT_HAVE_printf_s)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_s");
#elif defined(__CRT_HAVE_printf_unlocked)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_unlocked");
#elif defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
__NAMESPACE_LOCAL_END
#include <local/stdio/printf.h>
__NAMESPACE_LOCAL_BEGIN
/* Print data to `stdout', following `FORMAT'
 * Return the number of successfully printed bytes */
#define __localdep_printf __LIBC_LOCAL_NAME(printf)
#else /* ... */
#undef __local___localdep_printf_defined
#endif /* !... */
#endif /* !__local___localdep_printf_defined */
/* Dependency: unicode_writeutf16 from unicode */
#ifndef __local___localdep_unicode_writeutf16_defined
#define __local___localdep_unicode_writeutf16_defined 1
#ifdef __CRT_HAVE_unicode_writeutf16
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF16_CURLEN' bytes to `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_unicode_writeutf16,(__CHAR16_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf16,(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf16 */
__NAMESPACE_LOCAL_END
#include <local/unicode/unicode_writeutf16.h>
__NAMESPACE_LOCAL_BEGIN
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF16_CURLEN' bytes to `dst' */
#define __localdep_unicode_writeutf16 __LIBC_LOCAL_NAME(unicode_writeutf16)
#endif /* !__CRT_HAVE_unicode_writeutf16 */
#endif /* !__local___localdep_unicode_writeutf16_defined */
__NAMESPACE_LOCAL_END
#include <parts/printf-config.h>
#include <libc/parts.uchar.string.h>
#include <libc/string.h>
#include <hybrid/__assert.h>
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
#endif
__NAMESPACE_LOCAL_BEGIN
/* Generic printf implementation
 * Taking a regular printf-style format string and arguments, these
 * functions will call the given `PRINTER' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `PRINTER' obviously is called with the text parts in their correct order
 *  - If `PRINTER' returns '< 0', the function returns immediately,
 *    yielding that same value. Otherwise, format_printf() returns
 *    the sum of all return values from `PRINTER'.
 *  - The strings passed to `PRINTER' may not necessarily be zero-terminated, and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        `format_escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
 *  - `%.*s'   Instead of reading an `int' and dealing with undefined behavior when negative, an `unsigned int' is read.
 *  - `%.?s'   Similar to `%.*s', but takes a `size_t' from the argument list instead of an `unsigned int', as well as define
 *             a fixed-length buffer size for string/quote formats (thus allowing you to print '\0' characters after quoting)
 *  - `%$s'    Same as `%.?s'
 *  - `%q'     Print an escaped string. (format_printf(..., "a%qb", "foo\nbar")) --> "a\"foo\\nbar\"b"
 *  - `%#q'    Same as %q, without quotes. (format_printf(..., "a%#qb", "foo\nbar")) --> "afoo\\nbarb"
 *  - `%Q'     Print an escaped character. (format_printf(..., "a%Qb", '\n')) --> "a\'\\n\'b"
 *  - `%#Q'    Same as %Q, without quotes. (format_printf(..., "a%#Qb", '\n')) --> "a\\nb"
 *  - `%I'     length modifier: Integral length equivalent to sizeof(size_t)/sizeof(uintptr_t).
 *  - `%I8'    length modifier: Integral length equivalent to sizeof(int8_t).
 *  - `%I16'   length modifier: Integral length equivalent to sizeof(int16_t).
 *  - `%I32'   length modifier: Integral length equivalent to sizeof(int32_t).
 *  - `%I64'   length modifier: Integral length equivalent to sizeof(int64_t).
 *  - `%[...]' Extended formating options, allowing for additional formating options:
 *             - `%$[hex]' / `%$[hex:lLoOpPaAhH]'
 *                 - Invoke `format_hexdump(..., va_arg(args, void *))'
 *                 - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *                 - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *                    - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *                    - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *                    - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *                    - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *                    - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *             - `%[gen]'
 *                 - Invoke a custom format printer function pointer passed through args
 *                   >> typedef ssize_t (*PGEN)(pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> DO((*g)(printer, arg));
 *             - `%[gen:c]'
 *                 - Same as `%[gen]', but insert an additional argument `T' that depends
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the mnemonic and operands of a single native assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with a fixed buffer size) is used, do a full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<FORMAT=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given FORMAT string is a special printf-like format declaration
 *                   that accepts the following substitutions:
 *                   - `%%'   Print a single `%'-character (used for escaping `%')
 *                   - `%p'   Output the queried text address the same way `format_printf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
 *                   - `%n'   Symbol name of the surrounding symbol (managed), or `???'   `di_debug_addr2line_t::al_name'
 *                   - `%N'   Raw name of the surrounding symbol, or `???'                `di_debug_addr2line_t::al_rawname'
 *                   - `%l'   Source line number (1-based; 0 if unknown)                  `di_debug_addr2line_t::al_srcline'
 *                   - `%c'   Source column number (1-based; 0 if unknown)                `di_debug_addr2line_t::al_srccol'
 *                   - `%f'   Source filename (with path prefix)                          `di_debug_addr2line_t::(al_cubase|al_srcpath|al_srcfile)'
 *                   - `%Rf'  Source filename (without path prefix)                       `di_debug_addr2line_t::al_srcfile'
 *                   - `%<'   Absolute starting address of the associated source location `di_debug_addr2line_t::al_linestart'
 *                   - `%>'   Absolute end address of the associated source location      `di_debug_addr2line_t::al_lineend'
 *                   - `%1>'  Absolute end address of the associated source location - 1  `di_debug_addr2line_t::al_lineend'
 *                   - `%S'   Absolute starting address of the surrounding symbol         `di_debug_addr2line_t::al_symstart'
 *                   - `%E'   Absolute end address of the surrounding symbol              `di_debug_addr2line_t::al_symend'
 *                   - `%1E'  Absolute end address of the surrounding symbol - 1          `di_debug_addr2line_t::al_symend'
 *                   - `%Dl'  Declaration line number (1-based; 0 if unknown)             `di_debug_addr2line_t::al_dclline'
 *                   - `%Dc'  Declaration column number (1-based; 0 if unknown)           `di_debug_addr2line_t::al_dclcol'
 *                   - `%Df'  Declaration filename (with path prefix)                     `di_debug_addr2line_t::(al_cubase|al_dclpath|al_dclfile)'
 *                   - `%RDf' Declaration filename (without path prefix)                  `di_debug_addr2line_t::al_dclfile'
 *                   - Any other character[-sequence] is forwarded as-is
 *             - `%[...]' Other sequences are resered for future usage
 * >>> Possible (and actual) uses:
 *  - printf:           Unbuffered output into any kind of stream/file.
 *  - sprintf/snprintf: Unsafe/Counted string formatting into a user-supplied buffer.
 *  - strdupf:          Output into dynamically allocated heap memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more... */
__LOCAL_LIBC(format_vwprintf) __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(format_vwprintf))(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args) __THROWS(...) {
#ifndef __INTELLISENSE__
#define __FORMAT_PRINTER            __printer
#define __FORMAT_ARG                __arg
#define __FORMAT_FORMAT             __format
#define __FORMAT_ARGS               __args
#define __CHAR_TYPE                 __WCHAR_TYPE__
#define __CHAR_SIZE                 __SIZEOF_WCHAR_T__
#define __FORMAT_REPEAT             __localdep_format_wrepeat
#define __FORMAT_HEXDUMP            __localdep_format_whexdump
#define __FORMAT_WIDTH              __localdep_format_wwidth
#define __FORMAT_ESCAPE             __localdep_format_wescape
#define __FORMAT_WIDTH8             __localdep_format_width
#define __FORMAT_ESCAPE8            __localdep_format_escape
#if __SIZEOF_WCHAR_T__ == 2
#define __FORMAT_WIDTH32            __localdep_format_c32width
#define __FORMAT_ESCAPE32           __localdep_format_c32escape
#define __FORMAT_UNICODE_WRITECHAR  __localdep_unicode_writeutf16
#define __FORMAT_UNICODE_FORMAT8    __localdep_format_8to16
#define __FORMAT_UNICODE_FORMAT32   __localdep_format_32to16
#else /* __SIZEOF_WCHAR_T__ == 2 */
#define __FORMAT_WIDTH16            __localdep_format_c16width
#define __FORMAT_ESCAPE16           __localdep_format_c16escape
#define __FORMAT_UNICODE_WRITECHAR(__dst, __ch) ((__dst)[0] = (__ch), (__dst) + 1)
#define __FORMAT_UNICODE_FORMAT8    __localdep_format_8to32
#define __FORMAT_UNICODE_FORMAT16   __localdep_format_16to32
#endif /* __SIZEOF_WCHAR_T__ != 2 */
#include <local/format-printf.h>
#endif /* !__INTELLISENSE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_vwprintf_defined
#define __local___localdep_format_vwprintf_defined 1
#define __localdep_format_vwprintf __LIBC_LOCAL_NAME(format_vwprintf)
#endif /* !__local___localdep_format_vwprintf_defined */
#endif /* !__local_format_vwprintf_defined */
