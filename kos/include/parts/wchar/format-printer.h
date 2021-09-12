/* HASH CRC-32:0x6425f1c1 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _PARTS_WCHAR_FORMAT_PRINTER_H
#define _PARTS_WCHAR_FORMAT_PRINTER_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _FORMAT_PRINTER_H
#include <format-printer.h>
#endif /* !_FORMAT_PRINTER_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#include <hybrid/__assert.h>

#include <bits/crt/wformat-printer.h>
#include <kos/anno.h>

#include <libc/malloc.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* Calling convention used by `pwformatprinter' */
#ifndef WFORMATPRINTER_CC
#define WFORMATPRINTER_CC __WFORMATPRINTER_CC
#endif /* !WFORMATPRINTER_CC */

#ifndef __pwformatprinter_defined
#define __pwformatprinter_defined 1
/* Callback functions prototypes provided to format functions.
 * NOTE: 'pwformatprinter' usually returns the number of characters printed, but isn't required to.
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
typedef __pwformatprinter pwformatprinter;
#endif /* !__pwformatprinter_defined */

#ifdef __CRT_HAVE_format_wrepeat
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,format_wrepeat,(pwformatprinter __printer, void *__arg, wchar_t __ch, __SIZE_TYPE__ __num_repetitions),(__printer,__arg,__ch,__num_repetitions))
#else /* __CRT_HAVE_format_wrepeat */
#include <libc/local/parts.wchar.format-printer/format_wrepeat.h>
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_wrepeat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ (__LIBCCALL format_wrepeat)(pwformatprinter __printer, void *__arg, wchar_t __ch, __SIZE_TYPE__ __num_repetitions) __THROWS(...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wrepeat)(__printer, __arg, __ch, __num_repetitions); })
#endif /* !__CRT_HAVE_format_wrepeat */
#ifdef __CRT_HAVE_format_wescape
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2:  >> Hello  \"World\"  W\nhat a  great  day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This   function  escapes  all   control  and  non-ascii  characters,
 * preferring octal encoding  for control  characters and  hex-encoding
 * for other  non-ascii characters,  a behavior  that may  be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,format_wescape,(pwformatprinter __printer, void *__arg, wchar_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),(__printer,__arg,__text,__textlen,__flags))
#else /* __CRT_HAVE_format_wescape */
#include <libc/local/parts.wchar.format-printer/format_wescape.h>
/* >> format_escape(3)
 * Do C-style escape on the given text, printing it to the given printer.
 * Input:
 * >> Hello "World" W
 * >> hat a great day.
 * Output #1: >> \"Hello \"World\" W\nhat a great day.\"
 * Output #2:  >> Hello  \"World\"  W\nhat a  great  day
 * NOTE: Output #2 is generated if the `FORMAT_ESCAPE_FPRINTRAW' is set
 * This   function  escapes  all   control  and  non-ascii  characters,
 * preferring octal encoding  for control  characters and  hex-encoding
 * for other  non-ascii characters,  a behavior  that may  be  modified
 * with the `FORMAT_ESCAPE_FFORCE*' flags
 * @param: printer: A function called for all quoted portions of the text
 * @param: textlen: The total number of bytes to escape, starting at `text' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_wescape, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ (__LIBCCALL format_wescape)(pwformatprinter __printer, void *__arg, wchar_t const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) __THROWS(...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wescape)(__printer, __arg, __text, __textlen, __flags); })
#endif /* !__CRT_HAVE_format_wescape */
#ifdef __CRT_HAVE_format_whexdump
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
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,format_whexdump,(pwformatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),(__printer,__arg,__data,__size,__linesize,__flags))
#else /* __CRT_HAVE_format_whexdump */
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_whexdump, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ (__LIBCCALL format_whexdump)(pwformatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) __THROWS(...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_whexdump)(__printer, __arg, __data, __size, __linesize, __flags); })
#endif /* !__CRT_HAVE_format_whexdump */




#ifdef __CRT_HAVE_format_vwprintf
/* >> format_printf(3), format_vprintf(3)
 * Generic     printf      implementation
 * Taking a  regular printf-style  format  string and  arguments,  these
 * functions will call the given `printer' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        - `format_escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        - `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
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
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to  `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the  mnemonic and  operands of  a single  native  assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with  a fixed buffer size)  is used, do a  full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<format=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given `format' string is a special printf-like format declaration
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
 *  - strdupf:          Output  into  dynamically   allocated  heap   memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more...
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__CDECLARE(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)),__SSIZE_TYPE__,__THROWING,format_vwprintf,(pwformatprinter __printer, void *__arg, wchar_t const *__restrict __format, __builtin_va_list __args),(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vwprintf */
#include <libc/local/parts.wchar.format-printer/format_vwprintf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic     printf      implementation
 * Taking a  regular printf-style  format  string and  arguments,  these
 * functions will call the given `printer' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        - `format_escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        - `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
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
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to  `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the  mnemonic and  operands of  a single  native  assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with  a fixed buffer size)  is used, do a  full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<format=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given `format' string is a special printf-like format declaration
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
 *  - strdupf:          Output  into  dynamically   allocated  heap   memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more...
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_vwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ (__LIBCCALL format_vwprintf)(pwformatprinter __printer, void *__arg, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vwprintf)(__printer, __arg, __format, __args); })
#endif /* !__CRT_HAVE_format_vwprintf */
#ifdef __CRT_HAVE_format_wprintf
/* >> format_printf(3), format_vprintf(3)
 * Generic     printf      implementation
 * Taking a  regular printf-style  format  string and  arguments,  these
 * functions will call the given `printer' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        - `format_escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        - `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
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
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to  `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the  mnemonic and  operands of  a single  native  assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with  a fixed buffer size)  is used, do a  full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<format=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given `format' string is a special printf-like format declaration
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
 *  - strdupf:          Output  into  dynamically   allocated  heap   memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more...
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
__LIBC __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ (__LIBCCALL format_wprintf)(pwformatprinter __printer, void *__arg, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("format_wprintf");
#else /* __CRT_HAVE_format_wprintf */
#include <libc/local/parts.wchar.format-printer/format_wprintf.h>
/* >> format_printf(3), format_vprintf(3)
 * Generic     printf      implementation
 * Taking a  regular printf-style  format  string and  arguments,  these
 * functions will call the given `printer' callback with various strings
 * that, when put together, result in the desired formated text.
 *  - `printer' obviously is called with the text parts in their correct order
 *  - If `printer' returns '<  0', the function returns  immediately,
 *    yielding that same value. Otherwise, `format_printf(3)' returns
 *    the sum of all return values from `printer'.
 *  - The strings passed to `printer'  may not necessarily be zero-terminated,  and
 *    a second argument is passed that indicates the absolute length in characters.
 * Supported extensions:
 *  - `%q'-format mode: Semantics equivalent to `%s', this modifier escapes the string using
 *                        - `format_escape' with flags set of 'FORMAT_ESCAPE_FNONE', or
 *                        - `PRINTF_FLAG_PREFIX' when the '#' flag was used (e.g.: `%#q').
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
 *                   on the integer size prefix (`%I32[gen:c]') and defaults to  `void *'
 *                   >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *                   >> PGEN g = va_arg(args, PGEN);
 *                   >> T    a = va_arg(args, T);
 *                   >> DO((*g)(a, printer, arg));
 *             - `%[disasm]' / `%$[disasm]'
 *                 - Print the  mnemonic and  operands of  a single  native  assembly
 *                   instruction read from `va_arg(args, void *)' (using `libdisasm')
 *                   s.a. `disasm_single()'
 *                 - When the second form (with  a fixed buffer size)  is used, do a  full
 *                   disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *                   s.a. `disasm()'
 *             - `%[vinfo]' / `%[vinfo:<format=%f(%l,%c) : %n>]'
 *                 - Print addr2line information for a text address read from `va_arg(args, void *)'
 *                 - The given `format' string is a special printf-like format declaration
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
 *  - strdupf:          Output  into  dynamically   allocated  heap   memory,
 *                      increasing the buffer when it gets filled completely.
 *  - syslog:           Unbuffered system-log output.
 *  - ...               There are a _lot_ more...
 * @return: >= 0: The sum of all values returned by `printer'
 * @return: < 0:  The first negative value ever returned by `printer' (if any) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(format_wprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)) __SSIZE_TYPE__ (__LIBCCALL format_wprintf)(pwformatprinter __printer, void *__arg, wchar_t const *__restrict __format, ...) __THROWS(...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wprintf)(__printer, __arg, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define format_wprintf __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wprintf)
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE_format_wprintf */



#ifdef __CRT_HAVE_format_wsprintf_printer
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__CDECLARE(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_wsprintf_printer,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_wsprintf_printer */
#include <libc/local/parts.wchar.format-printer/format_wsprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_wsprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_wsprintf_printer)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsprintf_printer)(__arg, __data, __datalen); })
#endif /* !__CRT_HAVE_format_wsprintf_printer */


#ifndef __format_wsnprintf_data_defined
#define __format_wsnprintf_data_defined 1
/* Data structure for implementing waprintf() */
struct format_wsnprintf_data {
	wchar_t      *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !__format_wsnprintf_data_defined */
#define FORMAT_WSNPRINTF_INIT(buf, bufsize) \
	{ buf, bufsize }
#define format_wsnprintf_init(self, buf, bufsize) \
	((self)->sd_buffer = (buf),                   \
	 (self)->sd_bufsiz = (bufsize))

#ifdef __CRT_HAVE_format_wsnprintf_printer
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_wsnprintf_printer,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_wsnprintf_printer */
#include <libc/local/parts.wchar.format-printer/format_wsnprintf_printer.h>
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 * NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',   or
 *       alternatively the sum of return values of all calls to `format_wsnprintf_printer(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_wsnprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_wsnprintf_printer)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wsnprintf_printer)(__arg, __data, __datalen); })
#endif /* !__CRT_HAVE_format_wsnprintf_printer */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_format_length) && __SIZEOF_WCHAR_T__ == 4
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_wwidth,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth)
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_wwidth,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#else /* ... */
#include <libc/local/parts.wchar.format-printer/format_wwidth.h>
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_wwidth, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_wwidth)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_wwidth)(__arg, __data, __datalen); })
#endif /* !... */
#ifdef __CRT_HAVE_format_length
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__COMPILER_REDIRECT(__LIBC,__ATTR_CONST,__SSIZE_TYPE__,__NOTHROW_NCX,__WFORMATPRINTER_CC,format_wlength,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_length,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_wwidth) && !defined(__KERNEL__)
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__COMPILER_REDIRECT(__LIBC,__ATTR_CONST,__SSIZE_TYPE__,__NOTHROW_NCX,__WFORMATPRINTER_CC,format_wlength,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#else /* ... */
#include <libc/local/format-printer/format_length.h>
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __SSIZE_TYPE__ __NOTHROW_NCX(__WFORMATPRINTER_CC format_wlength)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_length)(__arg, (char const *)__data, __datalen); }
#endif /* !... */

#ifndef __format_waprintf_data_defined
#define __format_waprintf_data_defined 1
struct format_waprintf_data {
	wchar_t      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_waprintf_data_defined */

#define FORMAT_WAPRINTF_DATA_INIT \
	{ __NULLPTR, 0, 0 }
#define format_waprintf_data_init(self) \
	((self)->ap_base  = __NULLPTR,      \
	 (self)->ap_avail = (self)->ap_used = 0)
#define format_waprintf_data_cinit(self)            \
	(__hybrid_assert((self)->ap_base == __NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),        \
	 __hybrid_assert((self)->ap_used == 0))
#ifdef NDEBUG
#define format_waprintf_data_fini(self) __libc_free((self)->ap_base)
#else /* NDEBUG */
#if __SIZEOF_POINTER__ == 4
#define format_waprintf_data_fini(self)                 \
	(__libc_free((self)->ap_base),                      \
	 (self)->ap_base  = (char *)__UINT32_C(0xcccccccc), \
	 (self)->ap_avail = __UINT32_C(0xcccccccc),         \
	 (self)->ap_used  = __UINT32_C(0xcccccccc))
#elif __SIZEOF_POINTER__ == 8
#define format_waprintf_data_fini(self)                         \
	(__libc_free((self)->ap_base),                              \
	 (self)->ap_base  = (char *)__UINT64_C(0xcccccccccccccccc), \
	 (self)->ap_avail = __UINT64_C(0xcccccccccccccccc),         \
	 (self)->ap_used  = __UINT64_C(0xcccccccccccccccc))
#else /* __SIZEOF_POINTER__ == ... */
#define format_waprintf_data_fini(self) __libc_free((self)->ap_base)
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* !NDEBUG */

#ifdef __CRT_HAVE_format_waprintf_pack
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
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,format_waprintf_pack,(struct format_waprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen),(__self,__pstrlen))
#elif defined(__CRT_HAVE_realloc)
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_waprintf_pack, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL format_waprintf_pack)(struct format_waprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_pack)(__self, __pstrlen); })
#endif /* ... */
#ifdef __CRT_HAVE_format_waprintf_alloc
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,format_waprintf_alloc,(struct format_waprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars),(__self,__num_wchars))
#elif defined(__CRT_HAVE_realloc)
#include <libc/local/parts.wchar.format-printer/format_waprintf_alloc.h>
/* >> format_waprintf_alloc(3)
 * Allocate  a  buffer  of  `num_wchars'  wide-characters  at  the  end  of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_waprintf_alloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL format_waprintf_alloc)(struct format_waprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_alloc)(__self, __num_wchars); })
#endif /* ... */
#ifdef __CRT_HAVE_format_waprintf_printer
/* >> format_waprintf_printer(3)
 * Print data to a dynamically allocated heap buffer. On error, `-1' is returned */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,format_waprintf_printer,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc)
#include <libc/local/parts.wchar.format-printer/format_waprintf_printer.h>
/* >> format_waprintf_printer(3)
 * Print data to a dynamically allocated heap buffer. On error, `-1' is returned */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_waprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL format_waprintf_printer)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_printer)(__arg, __data, __datalen); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_WCHAR_FORMAT_PRINTER_H */
