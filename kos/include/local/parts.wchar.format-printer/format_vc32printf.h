/* HASH 0xfe3afd5b */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_format_vc32printf_defined
#define __local_format_vc32printf_defined 1
#include <bits/format-printer.h>

#include <bits/wformat-printer.h>
#include <bits/uformat-printer.h>




#include <libc/parts.uchar.string.h>



#include <hybrid/__assert.h>
#if !defined(CONFIG_USE_LIBDISASM) && !defined(CONFIG_NO_USE_LIBDISASM) && \
  ((defined(__KERNEL__) && defined(__KOS__)) || ((defined(CONFIG_HAVE_LIBDISASM_DISASSEMBLER_H) || \
    defined(HAVE_LIBDISASM_DISASSEMBLER_H) || __has_include(<libdisasm/disassembler.h>)) && \
    defined(__CRT_HAVE_dlopen) && defined(__CRT_HAVE_dlsym)))
#define CONFIG_USE_LIBDISASM 1
#endif
#if !defined(CONFIG_USE_LIBDEBUGINFO) && !defined(CONFIG_NO_USE_LIBDEBUGINFO) && \
  ((defined(__KERNEL__) && defined(__KOS__)) || ((defined(CONFIG_HAVE_LIBDEBUGINFO_ADDR2LINE_H) || \
    defined(HAVE_LIBDEBUGINFO_ADDR2LINE_H) || __has_include(<libdebuginfo/addr2line.h>)) && \
    defined(__CRT_HAVE_dlopen) && defined(__CRT_HAVE_dlsym) && defined(__CRT_HAVE_dlgetmodule) && defined(__CRT_HAVE_dlmodulebase)))
#define CONFIG_USE_LIBDEBUGINFO 1
#endif
#ifdef CONFIG_USE_LIBDISASM
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#endif
#include <libdisasm/disassembler.h>
#endif
#ifdef CONFIG_USE_LIBDEBUGINFO
#if !defined(__KERNEL__) || !defined(__KOS__)
#include <dlfcn.h>
#endif
#include <libdebuginfo/addr2line.h>
#endif
/* Dependency: "format_wrepeat" from "parts.wchar.format-printer" */
#ifndef ____localdep_format_c32repeat_defined
#define ____localdep_format_c32repeat_defined 1
#if defined(__CRT_HAVE_format_wrepeat) && (__SIZEOF_WCHAR_T__ == 4)
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32repeat,(__pc32formatprinter __printer, void *__arg, __CHAR32_TYPE__ __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_wrepeat.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
#define __localdep_format_c32repeat(printer, arg, ch, num_repetitions) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wrepeat))((__pwformatprinter)(printer), arg, (__WCHAR_TYPE__)(ch), num_repetitions)
#else /* LIBC: format_c32repeat */
#include <local/parts.wchar.format-printer/format_c32repeat.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
#define __localdep_format_c32repeat (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32repeat))
#endif /* format_c32repeat... */
#endif /* !____localdep_format_c32repeat_defined */

/* Dependency: "format_wescape" from "parts.wchar.format-printer" */
#ifndef ____localdep_format_c32escape_defined
#define ____localdep_format_c32escape_defined 1
#if defined(__CRT_HAVE_format_wescape) && (__SIZEOF_WCHAR_T__ == 4)
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
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32escape,(__pc32formatprinter __printer, void *__arg, /*utf-8*/__CHAR32_TYPE__ const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_wescape.h>
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
#define __localdep_format_c32escape(printer, arg, text, textlen, flags) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wescape))((__pwformatprinter)(printer), arg, (/*utf-8*/__WCHAR_TYPE__ const *)(text), textlen, flags)
#else /* LIBC: format_c32escape */
#include <local/parts.wchar.format-printer/format_c32escape.h>
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
#define __localdep_format_c32escape (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32escape))
#endif /* format_c32escape... */
#endif /* !____localdep_format_c32escape_defined */

/* Dependency: "format_whexdump" from "parts.wchar.format-printer" */
#ifndef ____localdep_format_c32hexdump_defined
#define ____localdep_format_c32hexdump_defined 1
#if defined(__CRT_HAVE_format_whexdump) && (__SIZEOF_WCHAR_T__ == 4)
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32hexdump,(__pc32formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_whexdump.h>
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
#define __localdep_format_c32hexdump(printer, arg, data, size, linesize, flags) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_whexdump))((__pwformatprinter)(printer), arg, data, size, linesize, flags)
#else /* LIBC: format_c32hexdump */
#include <local/parts.wchar.format-printer/format_c32hexdump.h>
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
#define __localdep_format_c32hexdump (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32hexdump))
#endif /* format_c32hexdump... */
#endif /* !____localdep_format_c32hexdump_defined */

/* Dependency: "unicode_writeutf16" from "unicode" */
#ifndef ____localdep_unicode_writeutf16_defined
#define ____localdep_unicode_writeutf16_defined 1
#if defined(__CRT_HAVE_unicode_writeutf16)
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF16_CURLEN' bytes to `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_unicode_writeutf16,(/*utf-16*/__CHAR16_TYPE__ *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf16,(__dst,__ch))
#else /* LIBC: unicode_writeutf16 */
#include <local/unicode/unicode_writeutf16.h>
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF16_CURLEN' bytes to `dst' */
#define __localdep_unicode_writeutf16 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf16))
#endif /* unicode_writeutf16... */
#endif /* !____localdep_unicode_writeutf16_defined */

/* Dependency: "format_wwidth" from "parts.wchar.format-printer" */
#ifndef ____localdep_format_c32width_defined
#define ____localdep_format_c32width_defined 1
#if defined(__CRT_HAVE_format_length)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth) && (__SIZEOF_WCHAR_T__ == 4)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_c32width,(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_wwidth.h>
/* Returns the width (number of characters; not bytes) of the given unicode string */
#define __localdep_format_c32width(arg, data, datalen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wwidth))(arg, (__WCHAR_TYPE__ const *)(data), datalen)
#else /* LIBC: format_c32width */
#include <local/parts.wchar.format-printer/format_c32width.h>
/* Returns the width (number of characters; not bytes) of the given unicode string */
#define __localdep_format_c32width (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32width))
#endif /* format_c32width... */
#endif /* !____localdep_format_c32width_defined */

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
 *                        `format_c32escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
 *  - `%~s'    [KERNEL-ONLY] Print a string from a user-space pointer (may be combined to something like `%~.?s')
 *  - `%.*s'   Instead of reading an `int' and dealing with undefined behavior when negative, an `unsigned int' is read.
 *  - `%.?s'   Similar to `%.*s', but takes an `size_t' from the argument list instead of an `unsigned int', as well as define
 *             a fixed-length buffer size for string/quote formats (thus allowing you to print '\0' characters after quoting)
 *  - `%$s'    Same as `%.?s'
 *  - `%Qs'    Same as `%q'
 *  - `%Qc'    Print an escaped character.
 *  - `%I'     length modifier: Integral length equivalent to sizeof(size_t).
 *  - `%I8'    length modifier: Integral length equivalent to sizeof(int8_t).
 *  - `%I16'   length modifier: Integral length equivalent to sizeof(int16_t).
 *  - `%I32'   length modifier: Integral length equivalent to sizeof(int32_t).
 *  - `%I64'   length modifier: Integral length equivalent to sizeof(int64_t).
 *  - `%[...]' Extended formating options, allowing for additional formating options:
 *             - `%[errno]': printf("%[errno]", EAGAIN); // Print human-readable information about the error 'EAGAIN'
 * >>> Possible (and actual) uses:
 *  - printf:           Unbuffered output into any kind of stream/file.
 *  - sprintf/snprintf: Unsafe/Counted string formatting into a user-supplied buffer.
 *  - strdupf:          Output into dynamically allocated heap memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more... */
__LOCAL_LIBC(format_vc32printf) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_vc32printf))(__pc32formatprinter __printer,
                                                               void *__arg,
                                                               __CHAR32_TYPE__ const *__restrict __format,
                                                               __builtin_va_list __args) {
#line 782 "kos/src/libc/magic/format-printer.c"
#define __CHAR_TYPE                 __CHAR32_TYPE__
#define __CHAR_SIZE                 4
#define __FORMAT_REPEAT             __localdep_format_c32repeat
#define __FORMAT_ESCAPE             __localdep_format_c32escape
#define __FORMAT_HEXDUMP            __localdep_format_c32hexdump

#if 4 == 2
#define __FORMAT_UNICODE_WRITEUTF8  __localdep_unicode_writeutf16
#else
#define __FORMAT_UNICODE_WRITEUTF8(__dst, __ch) ((__dst)[0] = (__ch), (__dst) + 1)
#endif
#define __FORMAT_WIDTH              __localdep_format_c32width




#define __FORMAT_PRINTER            __printer
#define __FORMAT_ARG                __arg
#define __FORMAT_FORMAT             __format
#define __FORMAT_ARGS               __args
#include <local/format-printf.h>
}
__NAMESPACE_LOCAL_END
#endif /* !__local_format_vc32printf_defined */
