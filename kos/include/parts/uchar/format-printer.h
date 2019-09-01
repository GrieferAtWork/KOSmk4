/* HASH 0x530ea3c3 */
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
#ifndef _PARTS_UCHAR_FORMAT_PRINTER_H
#define _PARTS_UCHAR_FORMAT_PRINTER_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _FORMAT_PRINTER_H
#include <format-printer.h>
#endif /* !_FORMAT_PRINTER_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */
#include <bits/uformat-printer.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __pc16formatprinter_defined
#define __pc16formatprinter_defined 1
/* Callback functions prototypes provided to format functions.
 * NOTE: '__pformatprinter' usually returns the number of characters printed, but isn't required to.
 * @param: DATA:    The base address of a DATALEN bytes long character vector that should be printed.
 * @param: DATALEN: The amount of characters that should be printed, starting at `data'.
 *                  Note that this is an exact value, meaning that a NUL-character appearing
 *                  before then should not terminate printing prematurely, but be printed as well.
 * @param: CLOSURE: The user-defined closure parameter passed alongside this function pointer.
 * @return: < 0:    An error occurred and the calling function shall return with this same value.
 * @return: >= 0:   The print was successful.
 *                  Usually, the return value is added to a sum of values which is then
 *                  returned by the calling function upon success, also meaning that the
 *                  usual return value used to indicate success in 'DATALEN'. */
typedef __pc16formatprinter pc16formatprinter;
typedef __pc32formatprinter pc32formatprinter;
#endif /* !__pc16formatprinter_defined */


#if defined(__CRT_HAVE_format_wrepeat) && (__SIZEOF_WCHAR_T__ == 2)
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16repeat,(pc16formatprinter __printer, void *__arg, char16_t __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif defined(__CRT_HAVE_DOS$format_wrepeat)
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16repeat,(pc16formatprinter __printer, void *__arg, char16_t __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.format-printer/format_wrepeat.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16repeat)(pc16formatprinter __printer, void *__arg, char16_t __ch, __SIZE_TYPE__ __num_repetitions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wrepeat))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__)__ch, __num_repetitions); }
#else /* LIBC: format_c16repeat */
#include <local/parts.wchar.format-printer/format_c16repeat.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16repeat, __FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16repeat)(pc16formatprinter __printer, void *__arg, char16_t __ch, __SIZE_TYPE__ __num_repetitions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16repeat))(__printer, __arg, __ch, __num_repetitions); })
#endif /* format_c16repeat... */
#if defined(__CRT_HAVE_format_wrepeat) && (__SIZEOF_WCHAR_T__ == 4)
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c32repeat,(pc32formatprinter __printer, void *__arg, char32_t __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_wrepeat.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32repeat)(pc32formatprinter __printer, void *__arg, char32_t __ch, __SIZE_TYPE__ __num_repetitions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wrepeat))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__)__ch, __num_repetitions); }
#else /* LIBC: format_c32repeat */
#include <local/parts.wchar.format-printer/format_c32repeat.h>
/* Repeat `CH' a number of `NUM_REPETITIONS' times
 * The usual format-printer rules apply, and this function
 * is allowed to call `PRINTER' as often as it chooses */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32repeat, __FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32repeat)(pc32formatprinter __printer, void *__arg, char32_t __ch, __SIZE_TYPE__ __num_repetitions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32repeat))(__printer, __arg, __ch, __num_repetitions); })
#endif /* format_c32repeat... */
#if defined(__CRT_HAVE_format_wescape) && (__SIZEOF_WCHAR_T__ == 2)
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
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16escape,(pc16formatprinter __printer, void *__arg, /*utf-8*/char16_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_DOS$format_wescape)
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
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16escape,(pc16formatprinter __printer, void *__arg, /*utf-8*/char16_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif __SIZEOF_WCHAR_T__ == 2
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
__FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16escape)(pc16formatprinter __printer, void *__arg, /*utf-8*/char16_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wescape))((__pwformatprinter)__printer, __arg, (/*utf-8*/__WCHAR_TYPE__ const *)__text, __textlen, __flags); }
#else /* LIBC: format_c16escape */
#include <local/parts.wchar.format-printer/format_c16escape.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16escape, __FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16escape)(pc16formatprinter __printer, void *__arg, /*utf-8*/char16_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16escape))(__printer, __arg, __text, __textlen, __flags); })
#endif /* format_c16escape... */
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
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c32escape,(pc32formatprinter __printer, void *__arg, /*utf-8*/char32_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
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
__FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32escape)(pc32formatprinter __printer, void *__arg, /*utf-8*/char32_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wescape))((__pwformatprinter)__printer, __arg, (/*utf-8*/__WCHAR_TYPE__ const *)__text, __textlen, __flags); }
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32escape, __FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32escape)(pc32formatprinter __printer, void *__arg, /*utf-8*/char32_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32escape))(__printer, __arg, __text, __textlen, __flags); })
#endif /* format_c32escape... */
#if defined(__CRT_HAVE_format_whexdump) && (__SIZEOF_WCHAR_T__ == 2)
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16hexdump,(pc16formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
#elif defined(__CRT_HAVE_DOS$format_whexdump)
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16hexdump,(pc16formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
#elif __SIZEOF_WCHAR_T__ == 2
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
__FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16hexdump)(pc16formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_whexdump))((__pwformatprinter)__printer, __arg, __data, __size, __linesize, __flags); }
#else /* LIBC: format_c16hexdump */
#include <local/parts.wchar.format-printer/format_c16hexdump.h>
/* Print a hex dump of the given data using the provided format printer
 * @param: PRINTER:  A function called for all quoted portions of the text
 * @param: DATA:     A pointer to the data that should be dumped
 * @param: SIZE:     The amount of bytes read starting at DATA
 * @param: LINESIZE: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: FLAGS:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: 0: The given data was successfully hex-dumped
 * @return: *: The first non-ZERO(0) return value of PRINTER */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16hexdump, __FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16hexdump)(pc16formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16hexdump))(__printer, __arg, __data, __size, __linesize, __flags); })
#endif /* format_c16hexdump... */
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
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c32hexdump,(pc32formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
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
__FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32hexdump)(pc32formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_whexdump))((__pwformatprinter)__printer, __arg, __data, __size, __linesize, __flags); }
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32hexdump, __FORCELOCAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32hexdump)(pc32formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32hexdump))(__printer, __arg, __data, __size, __linesize, __flags); })
#endif /* format_c32hexdump... */



#if defined(__CRT_HAVE_format_vwprintf) && (__SIZEOF_WCHAR_T__ == 2)
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
 *                        `format_c16escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
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
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3)),__SSIZE_TYPE__,__NOTHROW_NCX,format_vc16printf,(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#elif defined(__CRT_HAVE_DOS$format_vwprintf)
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
 *                        `format_c16escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
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
__CREDIRECT_DOS(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3)),__SSIZE_TYPE__,__NOTHROW_NCX,format_vc16printf,(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.format-printer/format_vwprintf.h>
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
 *                        `format_c16escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
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
__FORCELOCAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_vc16printf)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vwprintf))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: format_vc16printf */
#include <local/parts.wchar.format-printer/format_vc16printf.h>
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
 *                        `format_c16escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_vc16printf, __FORCELOCAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_vc16printf)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vc16printf))(__printer, __arg, __format, __args); })
#endif /* format_vc16printf... */
#if defined(__CRT_HAVE_format_vwprintf) && (__SIZEOF_WCHAR_T__ == 4)
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
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3)),__SSIZE_TYPE__,__NOTHROW_NCX,format_vc32printf,(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_vwprintf.h>
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
__FORCELOCAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_vc32printf)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vwprintf))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: format_vc32printf */
#include <local/parts.wchar.format-printer/format_vc32printf.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_vc32printf, __FORCELOCAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_vc32printf)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vc32printf))(__printer, __arg, __format, __args); })
#endif /* format_vc32printf... */
#if defined(__CRT_HAVE_format_wprintf) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
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
 *                        `format_c16escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
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
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ __NOTHROW_NCX(__VLIBCCALL format_c16printf)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, ...) __CASMNAME("format_wprintf");
#elif defined(__CRT_HAVE_DOS$format_wprintf) && !defined(__NO_ASMNAME)
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
 *                        `format_c16escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
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
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ __NOTHROW_NCX(__VLIBDCALL format_c16printf)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, ...) __CASMNAME_DOS("format_wprintf");
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.format-printer/format_wprintf.h>
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
 *                        `format_c16escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
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
#define format_c16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wprintf))
#else /* LIBC: format_c16printf */
#include <local/parts.wchar.format-printer/format_c16printf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(format_c16printf)
#else /* __cplusplus */
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
 *                        `format_c16escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
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
#define format_c16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16printf))
#endif /* !__cplusplus */
#endif /* format_c16printf... */
#if defined(__CRT_HAVE_format_wprintf) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
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
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ __NOTHROW_NCX(__VLIBCCALL format_c32printf)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, ...) __CASMNAME("format_wprintf");
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_wprintf.h>
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
#define format_c32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wprintf))
#else /* LIBC: format_c32printf */
#include <local/parts.wchar.format-printer/format_c32printf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(format_c32printf)
#else /* __cplusplus */
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
#define format_c32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32printf))
#endif /* !__cplusplus */
#endif /* format_c32printf... */



#if defined(__CRT_HAVE_format_wsprintf_printer) && (__SIZEOF_WCHAR_T__ == 2)
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16sprintf_printer,(/*char16_t ***/void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wsprintf_printer)
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16sprintf_printer,(/*char16_t ***/void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsprintf_printer,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.format-printer/format_wsprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16sprintf_printer)(/*char16_t ***/void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsprintf_printer))((/*wchar_t ***/void *)__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: format_c16sprintf_printer */
#include <local/parts.wchar.format-printer/format_c16sprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16sprintf_printer, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16sprintf_printer)(/*char16_t ***/void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16sprintf_printer))((/*wchar_t ***/void *)__arg, __data, __datalen); })
#endif /* format_c16sprintf_printer... */
#if defined(__CRT_HAVE_format_wsprintf_printer) && (__SIZEOF_WCHAR_T__ == 4)
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c32sprintf_printer,(/*char32_t ***/void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsprintf_printer,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_wsprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32sprintf_printer)(/*char32_t ***/void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsprintf_printer))((/*wchar_t ***/void *)__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: format_c32sprintf_printer */
#include <local/parts.wchar.format-printer/format_c32sprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32sprintf_printer, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32sprintf_printer)(/*char32_t ***/void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32sprintf_printer))((/*wchar_t ***/void *)__arg, __data, __datalen); })
#endif /* format_c32sprintf_printer... */


#ifndef __format_c16snprintf_data_defined
#define __format_c16snprintf_data_defined 1
/* Data structure for implementing c16snprintf() */
struct format_c16snprintf_data {
	char16_t     *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
};
/* Data structure for implementing c32snprintf() */
struct format_c32snprintf_data {
	char32_t     *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !__format_c16snprintf_data_defined */
#define FORMAT_C16SNPRINTF_INIT(buf,bufsize)       { buf, bufsize }
#define FORMAT_C32SNPRINTF_INIT(buf,bufsize)       { buf, bufsize }
#define format_c16snprintf_init(self,buf,bufsize) ((self)->sd_buffer = (buf),(self)->sd_bufsiz = (bufsize))
#define format_c32snprintf_init(self,buf,bufsize) ((self)->sd_buffer = (buf),(self)->sd_bufsiz = (bufsize))

#if defined(__CRT_HAVE_format_wsnprintf_printer) && (__SIZEOF_WCHAR_T__ == 2)
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16snprintf_printer,(/*struct format_wsnprintf_data**/void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsnprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wsnprintf_printer)
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16snprintf_printer,(/*struct format_wsnprintf_data**/void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsnprintf_printer,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.format-printer/format_wsnprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16snprintf_printer)(/*struct format_wsnprintf_data**/void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsnprintf_printer))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: format_c16snprintf_printer */
#include <local/parts.wchar.format-printer/format_c16snprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16snprintf_printer, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16snprintf_printer)(/*struct format_wsnprintf_data**/void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16snprintf_printer))(__arg, __data, __datalen); })
#endif /* format_c16snprintf_printer... */
#if defined(__CRT_HAVE_format_wsnprintf_printer) && (__SIZEOF_WCHAR_T__ == 4)
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c32snprintf_printer,(/*struct format_wsnprintf_data**/void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsnprintf_printer,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_wsnprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32snprintf_printer)(/*struct format_wsnprintf_data**/void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsnprintf_printer))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: format_c32snprintf_printer */
#include <local/parts.wchar.format-printer/format_c32snprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32snprintf_printer, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32snprintf_printer)(/*struct format_wsnprintf_data**/void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32snprintf_printer))(__arg, __data, __datalen); })
#endif /* format_c32snprintf_printer... */
#if defined(__CRT_HAVE_format_wwidth) && (__SIZEOF_WCHAR_T__ == 2)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16width,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wwidth)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c16width,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.format-printer/format_wwidth.h>
/* Returns the width (number of characters; not bytes) of the given unicode string */
__FORCELOCAL __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16width)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wwidth))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: format_c16width */
#include <local/parts.wchar.format-printer/format_c16width.h>
/* Returns the width (number of characters; not bytes) of the given unicode string */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16width, __FORCELOCAL __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16width)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16width))(__arg, __data, __datalen); })
#endif /* format_c16width... */
#if defined(__CRT_HAVE_format_length)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c32width,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth) && (__SIZEOF_WCHAR_T__ == 4)
/* Returns the width (number of characters; not bytes) of the given unicode string */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_c32width,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.format-printer/format_wwidth.h>
/* Returns the width (number of characters; not bytes) of the given unicode string */
__FORCELOCAL __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32width)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wwidth))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: format_c32width */
#include <local/parts.wchar.format-printer/format_c32width.h>
/* Returns the width (number of characters; not bytes) of the given unicode string */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32width, __FORCELOCAL __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32width)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32width))(__arg, __data, __datalen); })
#endif /* format_c32width... */
#if defined(__CRT_HAVE_format_length)
/* Always re-return `datalen' and ignore all other arguments */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,format_c16length,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#else /* LIBC: format_length */
#include <local/format-printer/format_length.h>
/* Always re-return `datalen' and ignore all other arguments */
__FORCELOCAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c16length)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_length))(__arg, (/*utf-8*/char const *)__data, __datalen); }
#endif /* format_c16length... */
#if defined(__CRT_HAVE_format_length)
/* Always re-return `datalen' and ignore all other arguments */
__CREDIRECT(,__SSIZE_TYPE__,__NOTHROW_NCX,format_c32length,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#else /* LIBC: format_length */
#include <local/format-printer/format_length.h>
/* Always re-return `datalen' and ignore all other arguments */
__FORCELOCAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_c32length)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_length))(__arg, (/*utf-8*/char const *)__data, __datalen); }
#endif /* format_c32length... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_FORMAT_PRINTER_H */
