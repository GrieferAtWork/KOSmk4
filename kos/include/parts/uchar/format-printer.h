/* HASH CRC-32:0x67f1a3a4 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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

#include <bits/crt/uformat-printer.h>
#include <kos/anno.h>

#include <libc/malloc.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* Calling convention used by `pc16formatprinter' */
#ifndef C16FORMATPRINTER_CC
#define C16FORMATPRINTER_CC __C16FORMATPRINTER_CC
#endif /* !C16FORMATPRINTER_CC */

/* Calling convention used by `pc32formatprinter' */
#ifndef C32FORMATPRINTER_CC
#define C32FORMATPRINTER_CC __C32FORMATPRINTER_CC
#endif /* !C32FORMATPRINTER_CC */

#ifndef __pc16formatprinter_defined
#define __pc16formatprinter_defined
/* Callback functions prototypes provided to format functions.
 * NOTE: 'pc(16|32)formatprinter' usually returns the number of characters printed, but isn't required to.
 * @param: arg:     The user-defined closure parameter passed alongside this function pointer.
 * @param: data:    The base address of a `datalen' bytes long character vector that should be printed.
 * @param: datalen: The  amount  of  characters  that  should  be  printed,  starting  at  `data'.
 *                  Note  that  this is  an exact  value, meaning  that a  NUL-character appearing
 *                  before then should not terminate printing prematurely, but be printed as well.
 * @return: < 0:    An error occurred and the calling function shall return with this same value.
 * @return: >= 0:   The print was successful.
 *                  Usually,  the return value is added to a sum of values which is then
 *                  returned by the calling function upon success, also meaning that the
 *                  usual return value used to indicate success is `datalen'. */
typedef __pc16formatprinter pc16formatprinter;
typedef __pc32formatprinter pc32formatprinter;
#endif /* !__pc16formatprinter_defined */


#if defined(__CRT_HAVE_format_wrepeat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c16repeat,(pc16formatprinter __printer, void *__arg, char16_t __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif defined(__CRT_HAVE_DOS$format_wrepeat)
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c16repeat,(pc16formatprinter __printer, void *__arg, char16_t __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_wrepeat.h>
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16repeat)(pc16formatprinter __printer, void *__arg, char16_t __ch, __SIZE_TYPE__ __num_repetitions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wrepeat))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__)__ch, __num_repetitions); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c16repeat.h>
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16repeat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16repeat)(pc16formatprinter __printer, void *__arg, char16_t __ch, __SIZE_TYPE__ __num_repetitions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16repeat))(__printer, __arg, __ch, __num_repetitions); })
#endif /* !... */
#if defined(__CRT_HAVE_format_wrepeat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c32repeat,(pc32formatprinter __printer, void *__arg, char32_t __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif defined(__CRT_HAVE_KOS$format_wrepeat)
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c32repeat,(pc32formatprinter __printer, void *__arg, char32_t __ch, __SIZE_TYPE__ __num_repetitions),format_wrepeat,(__printer,__arg,__ch,__num_repetitions))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_wrepeat.h>
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32repeat)(pc32formatprinter __printer, void *__arg, char32_t __ch, __SIZE_TYPE__ __num_repetitions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wrepeat))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__)__ch, __num_repetitions); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c32repeat.h>
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32repeat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32repeat)(pc32formatprinter __printer, void *__arg, char32_t __ch, __SIZE_TYPE__ __num_repetitions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32repeat))(__printer, __arg, __ch, __num_repetitions); })
#endif /* !... */
#if defined(__CRT_HAVE_format_wescape) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: "\"Hello \"World\" W\nhat a great day.\""
 * Output #2:   "Hello \"World\" W\nhat a great day"
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c16escape,(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_DOS$format_wescape)
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: "\"Hello \"World\" W\nhat a great day.\""
 * Output #2:   "Hello \"World\" W\nhat a great day"
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__CREDIRECT_DOS(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c16escape,(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_wescape.h>
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: "\"Hello \"World\" W\nhat a great day.\""
 * Output #2:   "Hello \"World\" W\nhat a great day"
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16escape)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wescape))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__ const *)__text, __textlen, __flags); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c16escape.h>
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: "\"Hello \"World\" W\nhat a great day.\""
 * Output #2:   "Hello \"World\" W\nhat a great day"
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16escape, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16escape)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16escape))(__printer, __arg, __text, __textlen, __flags); })
#endif /* !... */
#if defined(__CRT_HAVE_format_wescape) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: "\"Hello \"World\" W\nhat a great day.\""
 * Output #2:   "Hello \"World\" W\nhat a great day"
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c32escape,(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_KOS$format_wescape)
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: "\"Hello \"World\" W\nhat a great day.\""
 * Output #2:   "Hello \"World\" W\nhat a great day"
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__CREDIRECT_KOS(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c32escape,(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_wescape,(__printer,__arg,__text,__textlen,__flags))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_wescape.h>
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: "\"Hello \"World\" W\nhat a great day.\""
 * Output #2:   "Hello \"World\" W\nhat a great day"
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32escape)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wescape))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__ const *)__text, __textlen, __flags); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c32escape.h>
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: "\"Hello \"World\" W\nhat a great day.\""
 * Output #2:   "Hello \"World\" W\nhat a great day"
 * NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
 * This  function  escapes  all  control  and  non-ascii characters,
 * preferring octal encoding for control characters and hex-encoding
 * for other non-ascii characters, a  behavior that may be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32escape, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32escape)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32escape))(__printer, __arg, __text, __textlen, __flags); })
#endif /* !... */
#if defined(__CRT_HAVE_format_whexdump) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c16hexdump,(pc16formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
#elif defined(__CRT_HAVE_DOS$format_whexdump)
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__CREDIRECT_DOS(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c16hexdump,(pc16formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_whexdump.h>
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16hexdump)(pc16formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_whexdump))((__pwformatprinter)__printer, __arg, __data, __size, __linesize, __flags); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c16hexdump.h>
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16hexdump, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16hexdump)(pc16formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16hexdump))(__printer, __arg, __data, __size, __linesize, __flags); })
#endif /* !... */
#if defined(__CRT_HAVE_format_whexdump) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c32hexdump,(pc32formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
#elif defined(__CRT_HAVE_KOS$format_whexdump)
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__CREDIRECT_KOS(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_c32hexdump,(pc32formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),format_whexdump,(__printer,__arg,__data,__size,__linesize,__flags))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_whexdump.h>
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32hexdump)(pc32formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_whexdump))((__pwformatprinter)__printer, __arg, __data, __size, __linesize, __flags); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c32hexdump.h>
/* >> format_hexdump(3)
 * Print a hex dump of the given data using the provided format printer
 * @param: printer:  The format printer callback
 * @param: data:     A pointer to the data that should be dumped
 * @param: size:     The amount of bytes read starting at data
 * @param: linesize: The max amount of bytes to include per-line
 *                   HINT: Pass ZERO(0) to use a default size (16)
 * @param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32hexdump, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32hexdump)(pc32formatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32hexdump))(__printer, __arg, __data, __size, __linesize, __flags); })
#endif /* !... */



#if defined(__CRT_HAVE_format_vwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_C16PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_vc16printf,(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#elif defined(__CRT_HAVE_DOS$format_vwprintf)
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__CREDIRECT_DOS(__ATTR_IN(3) __ATTR_LIBC_C16PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_vc16printf,(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_vwprintf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_C16PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_vc16printf)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vwprintf))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_vc16printf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_vc16printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_C16PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_vc16printf)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vc16printf))(__printer, __arg, __format, __args); })
#endif /* !... */
#if defined(__CRT_HAVE_format_vwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_vc32printf,(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#elif defined(__CRT_HAVE_KOS$format_vwprintf)
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__CREDIRECT_KOS(__ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_vc32printf,(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_vwprintf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_vc32printf)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vwprintf))((__pwformatprinter)__printer, __arg, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_vc32printf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_vc32printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_vc32printf)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vc32printf))(__printer, __arg, __format, __args); })
#endif /* !... */
#if defined(__CRT_HAVE_format_wprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__LIBC __ATTR_IN(3) __ATTR_LIBC_C16PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBCCALL format_c16printf)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, ...) __CASMNAME("format_wprintf");
#elif defined(__CRT_HAVE_DOS$format_wprintf)
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__LIBC __ATTR_IN(3) __ATTR_LIBC_C16PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16printf)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, ...) __CASMNAME_DOS("format_wprintf");
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_wprintf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
#define format_c16printf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wprintf))(__VA_ARGS__)
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c16printf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_C16PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16printf)(pc16formatprinter __printer, void *__arg, char16_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16printf))(__printer, __arg, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define format_c16printf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16printf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !... */
#if defined(__CRT_HAVE_format_wprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__LIBC __ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBCCALL format_c32printf)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, ...) __CASMNAME("format_wprintf");
#elif defined(__CRT_HAVE_KOS$format_wprintf)
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__LIBC __ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32printf)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, ...) __CASMNAME_KOS("format_wprintf");
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_wprintf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
#define format_c32printf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wprintf))(__VA_ARGS__)
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c32printf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic printf implementation. Taking a regular printf-style format string and arguments,
 * this  function will call the given `printer' callback with various strings that, when put
 * together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_C32PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32printf)(pc32formatprinter __printer, void *__arg, char32_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32printf))(__printer, __arg, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define format_c32printf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32printf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !... */
#if defined(__CRT_HAVE_format_vwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__CREDIRECT(__ATTR_IN(4) __ATTR_LIBC_C16SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_CB,format_vc16scanf,(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif defined(__CRT_HAVE_DOS$format_vwscanf)
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__CREDIRECT_DOS(__ATTR_IN(4) __ATTR_LIBC_C16SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_CB,format_vc16scanf,(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_vwscanf.h>
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_LIBC_C16SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_vc16scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vwscanf))(__pgetc, __pungetc, __arg, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_vc16scanf.h>
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_vc16scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_LIBC_C16SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_vc16scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vc16scanf))(__pgetc, __pungetc, __arg, __format, __args); })
#endif /* !... */
#if defined(__CRT_HAVE_format_vwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__CREDIRECT(__ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_CB,format_vc32scanf,(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif defined(__CRT_HAVE_KOS$format_vwscanf)
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__CREDIRECT_KOS(__ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_CB,format_vc32scanf,(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args),format_vwscanf,(__pgetc,__pungetc,__arg,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_vwscanf.h>
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_vc32scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vwscanf))(__pgetc, __pungetc, __arg, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_vc32scanf.h>
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_vc32scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_vc32scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vc32scanf))(__pgetc, __pungetc, __arg, __format, __args); })
#endif /* !... */
#if defined(__CRT_HAVE_format_wscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__LIBC __ATTR_IN(4) __ATTR_LIBC_C16SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBCCALL format_c16scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char16_t const *__restrict __format, ...) __CASMNAME("format_wscanf");
#elif defined(__CRT_HAVE_DOS$format_wscanf)
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__LIBC __ATTR_IN(4) __ATTR_LIBC_C16SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char16_t const *__restrict __format, ...) __CASMNAME_DOS("format_wscanf");
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_wscanf.h>
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
#define format_c16scanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wscanf))(__VA_ARGS__)
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c16scanf.h>
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_LIBC_C16SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBDCALL format_c16scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char16_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16scanf))(__pgetc, __pungetc, __arg, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define format_c16scanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16scanf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !... */
#if defined(__CRT_HAVE_format_wscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__LIBC __ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBCCALL format_c32scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char32_t const *__restrict __format, ...) __CASMNAME("format_wscanf");
#elif defined(__CRT_HAVE_KOS$format_wscanf)
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
__LIBC __ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char32_t const *__restrict __format, ...) __CASMNAME_KOS("format_wscanf");
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_wscanf.h>
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
#define format_c32scanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wscanf))(__VA_ARGS__)
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c32scanf.h>
/* >> format_scanf(3), format_vscanf(3)
 * Generic     scanf     implementation
 * Taking a regular scanf-style format string and argument, these
 * functions will  call  the  given  `pgetc'  function  which  in
 * return should successively  yield a character  at a time  from
 * some kind of input source.
 *  - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
 *    Otherwise, the function returns the amount of successfully parsed arguments.
 *  - The user may  use `pgetc' to  track the last  read character to  get
 *    additional information about what character caused the scan to fail.
 *  - The given `pgetc' should also indicate EOF by returning `NUL'
 *  - This implementation supports the following extensions:
 *    - `%[A-Z]'   -- Character ranges in scan patterns
 *    - `%[^abc]'  -- Inversion of a scan pattern
 *    - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
 *    - `%$s'      -- `$'-modifier, available for any format outputting a string.
 *                    This modifier  reads a  `size_t'  from the  argument  list,
 *                    that specifies  the size  of the  following string  buffer:
 *                 >> char buffer[64];
 *                 >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
 * format -> %[*|?][width][length]specifier
 * @return: 0 :  No data could be scanned.
 * @return: * :  The total number of successfully scanned arguments.
 * @return: EOF: `PGETC' returned EOF the first time an attempt at reading was made */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_LIBC_C32SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBKCALL format_c32scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char32_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32scanf))(__pgetc, __pungetc, __arg, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define format_c32scanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32scanf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !... */



#if defined(__CRT_HAVE_format_wsprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_c16sprintf_printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wsprintf_printer)
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_c16sprintf_printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),DOS$format_wsprintf_printer,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_wsprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_c16sprintf_printer)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsprintf_printer))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c16sprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16sprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_c16sprintf_printer)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16sprintf_printer))(__arg, __data, __datalen); })
#endif /* !... */
#if defined(__CRT_HAVE_format_wsprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32sprintf_printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wsprintf_printer)
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32sprintf_printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),KOS$format_wsprintf_printer,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_wsprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_c32sprintf_printer)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsprintf_printer))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c32sprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32sprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_c32sprintf_printer)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32sprintf_printer))(__arg, __data, __datalen); })
#endif /* !... */


#ifndef __format_c16snprintf_data_defined
#define __format_c16snprintf_data_defined
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

#define FORMAT_C16SNPRINTF_INIT(buf, bufsize) \
	{ buf, bufsize }
#define FORMAT_C32SNPRINTF_INIT(buf, bufsize) \
	{ buf, bufsize }
#define format_c16snprintf_init(self, buf, bufsize) \
	((self)->sd_buffer = (buf), (self)->sd_bufsiz = (bufsize))
#define format_c32snprintf_init(self, buf, bufsize) \
	((self)->sd_buffer = (buf), (self)->sd_bufsiz = (bufsize))

#if defined(__CRT_HAVE_format_wsnprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_c16snprintf_printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsnprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wsnprintf_printer)
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_c16snprintf_printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),DOS$format_wsnprintf_printer,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_wsnprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_c16snprintf_printer)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsnprintf_printer))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c16snprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16snprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_c16snprintf_printer)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16snprintf_printer))(__arg, __data, __datalen); })
#endif /* !... */
#if defined(__CRT_HAVE_format_wsnprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32snprintf_printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsnprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wsnprintf_printer)
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32snprintf_printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),KOS$format_wsnprintf_printer,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_wsnprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_c32snprintf_printer)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsnprintf_printer))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c32snprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32snprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_c32snprintf_printer)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32snprintf_printer))(__arg, __data, __datalen); })
#endif /* !... */
#if defined(__CRT_HAVE_format_wwidth) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_c16width,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_wwidth)
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_c16width,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),DOS$format_wwidth,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_wwidth.h>
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_c16width)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wwidth))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c16width.h>
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16width, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_c16width)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16width))(__arg, __data, __datalen); })
#endif /* !... */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_format_length) && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32width,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_length)
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32width,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),KOS$format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32width,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_wwidth)
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32width,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),KOS$format_wwidth,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_wwidth.h>
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_c32width)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wwidth))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* ... */
#include <libc/local/parts.uchar.format-printer/format_c32width.h>
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32width, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_c32width)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32width))(__arg, __data, __datalen); })
#endif /* !... */
#ifdef __CRT_HAVE_format_length
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__COMPILER_CREDIRECT(__LIBC,__ATTR_CONST __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW,__C16FORMATPRINTER_CC,format_c16length,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth) && !defined(__KERNEL__)
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__COMPILER_CREDIRECT(__LIBC,__ATTR_CONST __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW,__C16FORMATPRINTER_CC,format_c16length,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#else /* ... */
#include <libc/local/format-printer/format_length.h>
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW(__C16FORMATPRINTER_CC format_c16length)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_length))(__arg, (char const *)__data, __datalen); }
#endif /* !... */
#ifdef __CRT_HAVE_format_length
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__COMPILER_CREDIRECT(__LIBC,__ATTR_CONST __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW,__C32FORMATPRINTER_CC,format_c32length,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth) && !defined(__KERNEL__)
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__COMPILER_CREDIRECT(__LIBC,__ATTR_CONST __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW,__C32FORMATPRINTER_CC,format_c32length,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#else /* ... */
#include <libc/local/format-printer/format_length.h>
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW(__C32FORMATPRINTER_CC format_c32length)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_length))(__arg, (char const *)__data, __datalen); }
#endif /* !... */

#ifndef __format_c16aprintf_data_defined
#define __format_c16aprintf_data_defined
struct format_c16aprintf_data {
	char16_t     *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_c16aprintf_data_defined */
#ifndef __format_c32aprintf_data_defined
#define __format_c32aprintf_data_defined
struct format_c32aprintf_data {
	char32_t     *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_c32aprintf_data_defined */
#define FORMAT_C16APRINTF_DATA_INIT \
	{ (char16_t *)__NULLPTR, 0, 0 }
#define FORMAT_C32APRINTF_DATA_INIT \
	{ (char32_t *)__NULLPTR, 0, 0 }
#define format_c16aprintf_data_init(self)      \
	((self)->ap_base  = (char16_t *)__NULLPTR, \
	 (self)->ap_avail = (self)->ap_used = 0)
#define format_c32aprintf_data_init(self)      \
	((self)->ap_base  = (char32_t *)__NULLPTR, \
	 (self)->ap_avail = (self)->ap_used = 0)
#define format_c16aprintf_data_cinit(self)                      \
	(__hybrid_assert((self)->ap_base == (char16_t *)__NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),                    \
	 __hybrid_assert((self)->ap_used == 0))
#define format_c32aprintf_data_cinit(self)                      \
	(__hybrid_assert((self)->ap_base == (char32_t *)__NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),                    \
	 __hybrid_assert((self)->ap_used == 0))
#if defined(NDEBUG) || defined(NDEBUG_FINI)
#define format_c16aprintf_data_fini(self) __libc_free((self)->ap_base)
#define format_c32aprintf_data_fini(self) __libc_free((self)->ap_base)
#elif __SIZEOF_POINTER__ == 4
#define format_c16aprintf_data_fini(self)                   \
	(__libc_free((self)->ap_base),                          \
	 (self)->ap_base  = (char16_t *)__UINT32_C(0xcccccccc), \
	 (self)->ap_avail = __UINT32_C(0xcccccccc),             \
	 (self)->ap_used  = __UINT32_C(0xcccccccc))
#define format_c32aprintf_data_fini(self)                   \
	(__libc_free((self)->ap_base),                          \
	 (self)->ap_base  = (char32_t *)__UINT32_C(0xcccccccc), \
	 (self)->ap_avail = __UINT32_C(0xcccccccc),             \
	 (self)->ap_used  = __UINT32_C(0xcccccccc))
#elif __SIZEOF_POINTER__ == 8
#define format_c16aprintf_data_fini(self)                           \
	(__libc_free((self)->ap_base),                                  \
	 (self)->ap_base  = (char16_t *)__UINT64_C(0xcccccccccccccccc), \
	 (self)->ap_avail = __UINT64_C(0xcccccccccccccccc),             \
	 (self)->ap_used  = __UINT64_C(0xcccccccccccccccc))
#define format_c32aprintf_data_fini(self)                           \
	(__libc_free((self)->ap_base),                                  \
	 (self)->ap_base  = (char32_t *)__UINT64_C(0xcccccccccccccccc), \
	 (self)->ap_avail = __UINT64_C(0xcccccccccccccccc),             \
	 (self)->ap_used  = __UINT64_C(0xcccccccccccccccc))
#else /* ... */
#define format_c16aprintf_data_fini(self) __libc_free((self)->ap_base)
#define format_c32aprintf_data_fini(self) __libc_free((self)->ap_base)
#endif /* !... */

#if defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char16_t *,__NOTHROW_NCX,format_c16aprintf_pack,(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen),format_waprintf_pack,(__self,__pstrlen))
#elif defined(__CRT_HAVE_DOS$format_waprintf_pack)
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char16_t *,__NOTHROW_NCX,format_c16aprintf_pack,(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen),format_waprintf_pack,(__self,__pstrlen))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_waprintf_pack.h>
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2) char16_t *__NOTHROW_NCX(__LIBDCALL format_c16aprintf_pack)(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_pack))((struct format_waprintf_data *)__self, __pstrlen); }
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/parts.uchar.format-printer/format_c16aprintf_pack.h>
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16aprintf_pack, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2) char16_t *__NOTHROW_NCX(__LIBDCALL format_c16aprintf_pack)(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16aprintf_pack))(__self, __pstrlen); })
#endif /* ... */
#if defined(__CRT_HAVE_format_waprintf_pack) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char32_t *,__NOTHROW_NCX,format_c32aprintf_pack,(struct format_c32aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen),format_waprintf_pack,(__self,__pstrlen))
#elif defined(__CRT_HAVE_KOS$format_waprintf_pack)
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char32_t *,__NOTHROW_NCX,format_c32aprintf_pack,(struct format_c32aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen),format_waprintf_pack,(__self,__pstrlen))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_waprintf_pack.h>
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2) char32_t *__NOTHROW_NCX(__LIBKCALL format_c32aprintf_pack)(struct format_c32aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_pack))((struct format_waprintf_data *)__self, __pstrlen); }
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/parts.uchar.format-printer/format_c32aprintf_pack.h>
/* Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_waprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters  were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32aprintf_pack, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2) char32_t *__NOTHROW_NCX(__LIBKCALL format_c32aprintf_pack)(struct format_c32aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32aprintf_pack))(__self, __pstrlen); })
#endif /* ... */
#if defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,format_c16aprintf_alloc,(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars),format_waprintf_alloc,(__self,__num_wchars))
#elif defined(__CRT_HAVE_DOS$format_waprintf_alloc)
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1),char16_t *,__NOTHROW_NCX,format_c16aprintf_alloc,(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars),format_waprintf_alloc,(__self,__num_wchars))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_waprintf_alloc.h>
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL format_c16aprintf_alloc)(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_alloc))((struct format_waprintf_data *)__self, __num_wchars); }
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/parts.uchar.format-printer/format_c16aprintf_alloc.h>
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16aprintf_alloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) char16_t *__NOTHROW_NCX(__LIBDCALL format_c16aprintf_alloc)(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16aprintf_alloc))(__self, __num_wchars); })
#endif /* ... */
#if defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,format_c32aprintf_alloc,(struct format_c32aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars),format_waprintf_alloc,(__self,__num_wchars))
#elif defined(__CRT_HAVE_KOS$format_waprintf_alloc)
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1),char32_t *,__NOTHROW_NCX,format_c32aprintf_alloc,(struct format_c32aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars),format_waprintf_alloc,(__self,__num_wchars))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_waprintf_alloc.h>
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL format_c32aprintf_alloc)(struct format_c32aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_alloc))((struct format_waprintf_data *)__self, __num_wchars); }
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/parts.uchar.format-printer/format_c32aprintf_alloc.h>
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32aprintf_alloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) char32_t *__NOTHROW_NCX(__LIBKCALL format_c32aprintf_alloc)(struct format_c32aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32aprintf_alloc))(__self, __num_wchars); })
#endif /* ... */
#if defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 2 && defined(__C16FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_c16aprintf_printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_waprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_waprintf_printer)
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C16FORMATPRINTER_CC,format_c16aprintf_printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),DOS$format_waprintf_printer,(__arg,__data,__datalen))
#elif (defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.format-printer/format_waprintf_printer.h>
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_c16aprintf_printer)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_printer))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#elif (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/parts.uchar.format-printer/format_c16aprintf_printer.h>
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c16aprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C16FORMATPRINTER_CC format_c16aprintf_printer)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c16aprintf_printer))(__arg, __data, __datalen); })
#endif /* ... */
#if defined(__CRT_HAVE_format_waprintf_printer) && __SIZEOF_WCHAR_T__ == 4 && defined(__C32FORMATPRINTER_CC_IS_WFORMATPRINTER_CC)
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32aprintf_printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_waprintf_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$format_waprintf_printer)
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__C32FORMATPRINTER_CC,format_c32aprintf_printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),KOS$format_waprintf_printer,(__arg,__data,__datalen))
#elif (defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.format-printer/format_waprintf_printer.h>
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_c32aprintf_printer)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_printer))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#elif (defined(__CRT_HAVE_format_waprintf_alloc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/parts.uchar.format-printer/format_c32aprintf_printer.h>
/* >> format_waprintf_printer(3)
 * Print data  to a  dynamically allocated  heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pwformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_c32aprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__C32FORMATPRINTER_CC format_c32aprintf_printer)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_c32aprintf_printer))(__arg, __data, __datalen); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_FORMAT_PRINTER_H */
