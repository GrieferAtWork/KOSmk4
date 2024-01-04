/* HASH CRC-32:0xb4dd8309 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _FORMAT_PRINTER_H
#define _FORMAT_PRINTER_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/__assert.h>

#include <bits/crt/format-printer.h>
#include <bits/types.h>

#include <libc/malloc.h>
#include <kos/anno.h>

/*
 * ===================================================================
 *   format-printer overview
 * ===================================================================
 *
 * The  format-printer system is the low-level, general-purpose, fits-
 * all base  for everything  that  is printf  (printf(3),  sprintf(3),
 * snprintf(3), dprintf(3), asprintf(3), ...).  At its core, the  idea
 * is to define so-called `pformatprinter'-compatible functions, which
 * look like this:
 *
 * >> PRIVATE ssize_t FORMATPRINTER_CC
 * >> my_printer(void *arg, char const *__restrict data, size_t datalen) {
 * >>     ...
 * >> }
 *
 * These functions are used to process incoming strings one chunk at  a
 * time, that chunk being the string `[data, data + datalen - 1]'. They
 * then return a printer-specific value with the following semantics:
 *  - return < 0:  An error occurred during printing. In this case,  the
 *                 caller won't be trying to feed more chunks and simply
 *                 return too, using the same (negative) return value.
 *  - return >= 0: The  caller will add  this value to  an internal sum of
 *                 return  values from previous calls. Once everything has
 *                 been printed (and the printer never returned a negative
 *                 value), the caller returns this sum.
 *
 * The  `arg'  argument passed  to printers  is an  opaque pointer  that is
 * passed alongside the `pformatprinter printer' argument to format-printer
 * functions (like  `format_printf()'). It  can be  used to  keep track  of
 * meta-data used by the printer function, meaning that it's actual meaning
 * and contents are dependent on the printer being used. Examples might be:
 *  - `arg' is `char **':                 `sprintf(3)'
 *  - `arg' is `{ char *p; size_t n; }*': `snprintf(3)'
 *  - `arg' is `fd_t':                    `dprintf(3)'
 *  - `arg' is `FILE *':                  `fprintf(3)'
 *
 * Since chunks are variable-sized, and are always fed to printer functions
 * in  the order in which they should  be concatenated in the final output,
 * all  details regarding what should happen to generated data are entirely
 * left to the  printer functions, including  when/how to indicate  errors,
 * how to keep track of how much data was already printed, etc...
 *
 *
 *
 * ===================================================================
 *   format_printf() features / extensions
 * ===================================================================
 *
 * The most notable format-printer is `format_printf()' itself, since this
 * is the format-printer that implements "%s"-like format strings. On KOS,
 * we support the following features / extensions:
 *
 *  - All STDC-mandated features:
 *    - "%%": simply output a singular "%"
 *    - Field width:     "%42", "%*"
 *    - Field precision: "%.42", "%.*"
 *    - Flags:           "%#", "%-", "%+", "% ", "%0"
 *    - Width modifiers: "%hh", "%h", "%l", "l%l", "%L", "%z", "%t", "%j"
 *    - Output codes:    "%d", "%i", "%u", "%x", "%X", "%o", "%s", "%p",
 *                       "%c",  "%n", "%f", "%F", "%e", "%E", "%g", "%G"
 *
 *  - MSVC-style fixed-length integer width modifiers: "%I", "%I8", "%I16", "%I32", "%I64"
 *    (Note that "%I8", "%I16" are KOS extensions)
 *
 *  - MSVC-style control for "%n" (s.a. `_set_printf_count_output(3)'; defaults to enabled)
 *
 *  - Glibc-style "%m" (print string returned by `strerror(errno)')
 *
 *  - Positional arguments: printf("<%4$d %3$d %2$d %1$d>", 10, 20, 30, 40); // "<40 30 20 10>"
 *    Including support for using them as flexible width/precision:
 *    >> printf("%1$*3$.*2$d", 10, 20, 30);  // decimal=10; width=30; precision=20
 *    >> printf("%*.*d", 30, 20, 10);        // decimal=10; width=30; precision=20
 *    Note that we impose no upper limit on how many arguments be used like this.
 *
 *  - KOS-specific extensions:
 *    - "%?" can be used to specify a size_t-sized width field (rather than int-sized "%*")
 *    - "%.?" can be used to specify a size_t-sized precision field (rather than int-sized "%.*")
 *    - fixed-precision: when used for "%s", specifies  the exact length of  the
 *      string to be printed, rather than the upper limit of a `strnlen()' call.
 *      Using this, you can print "\0" characters from strings.
 *      - "%:" can be used in place of "%." to introduce a fixed-precision field
 *      - "%$" can be used as an alias for "%:?"
 *    - "%q" can be used similar to "\"%s\"", only that control characters are escaped:
 *      >> printf("%q", "Hello\nWorld"); // "\"Hello\\nWorld\""
 *      "%#q" does the same, but omits include leading/trailing "-characters
 *    - "%b": like "%o", but print in base-2
 *    - "%Q": to "%c" what "%q" is to "%s" (print an escaped, single character)
 *    - "%I8s":  print a utf-8 string (`char const *')
 *    - "%I16s": print a utf-16 string (`char16_t const *')
 *    - "%I32s": print a utf-32 string (`char32_t const *')
 *    - "%I8c":  print a utf-8 character (`char'; s.a. `PRIc8')
 *    - "%I16c": print a utf-16 character (`char16_t'; s.a. `PRIc16')
 *    - "%I32c": print a utf-32 character (`char32_t'; s.a. `PRIc32')
 *    - "%[command]", "%[command:options]": Extended printf requests
 *      - "%$[hex]" / "%$[hex:lLoOpPaAhH]"
 *        - Invoke `format_hexdump(..., va_arg(args, void *))'
 *        - Integer-length (`%$I32[hex]') flags affect `FORMAT_HEXDUMP_(BYTES|WORDS|DWORDS|QWORDS)'
 *        - The argument string affect flags (defaults to `FORMAT_HEXDUMP_FNORMAL')
 *           - `FORMAT_HEXDUMP_FHEXLOWER':  yes:l, no:L
 *           - `FORMAT_HEXDUMP_FOFFSETS':   yes:o, no:O
 *           - `FORMAT_HEXDUMP_FNOADDRESS': yes:P, no:p
 *           - `FORMAT_HEXDUMP_FNOASCII':   yes:A, no:a
 *           - `FORMAT_HEXDUMP_FNOHEX':     yes:H, no:h
 *      - `%[gen]'
 *          - Invoke a custom format printer function pointer passed through args
 *            >> typedef ssize_t (*PGEN)(pformatprinter printer, void *arg);
 *            >> PGEN g = va_arg(args, PGEN);
 *            >> DO((*g)(printer, arg));
 *      - `%[gen:c]'
 *          - Same as `%[gen]', but insert an additional argument `T' that depends
 *            on the integer size prefix (`%I32[gen:c]') and defaults to  `void *'
 *            >> typedef ssize_t (*PGEN)(T a, pformatprinter printer, void *arg);
 *            >> PGEN g = va_arg(args, PGEN);
 *            >> T    a = va_arg(args, T);
 *            >> DO((*g)(a, printer, arg));
 *      - `%[disasm]' / `%$[disasm]'
 *          - Print the  mnemonic and  operands of  a single  native  assembly
 *            instruction given via `va_arg(args, void *)' (using `libdisasm')
 *            s.a. `disasm_single()'
 *          - When the second form (with  a fixed buffer size)  is used, do a  full
 *            disassembly of that number of bytes, following `DISASSEMBLER_FNORMAL'
 *            s.a. `disasm()'
 *      - `%[vinfo]' / `%[vinfo:%f(%l,%c) : %n]'
 *          - Print addr2line information for a text address given via `va_arg(args, void *)'
 *          - The given `format' string is a special printf-like format declaration
 *            that accepts the following substitutions:
 *            - `%%'   Print a single `%'-character (used for escaping `%')
 *            - `%p'   Output the queried text address the same way `format_printf(..., "%q", addr)' would (as `sizeof(void *) * 2' uppercase hex characters)
 *            - `%n'   Symbol name of the surrounding symbol (managed), or `???'   `di_debug_addr2line_t::al_name'
 *            - `%N'   Raw name of the surrounding symbol, or `???'                `di_debug_addr2line_t::al_rawname'
 *            - `%l'   Source line number (1-based; 0 if unknown)                  `di_debug_addr2line_t::al_srcline'
 *            - `%c'   Source column number (1-based; 0 if unknown)                `di_debug_addr2line_t::al_srccol'
 *            - `%f'   Source filename (with path prefix)                          `di_debug_addr2line_t::(al_cubase|al_srcpath|al_srcfile)'
 *            - `%Rf'  Source filename (without path prefix)                       `di_debug_addr2line_t::al_srcfile'
 *            - `%<'   Absolute starting address of the associated source location `di_debug_addr2line_t::al_linestart'
 *            - `%>'   Absolute end address of the associated source location      `di_debug_addr2line_t::al_lineend'
 *            - `%1>'  Absolute end address of the associated source location - 1  `di_debug_addr2line_t::al_lineend'
 *            - `%S'   Absolute starting address of the surrounding symbol         `di_debug_addr2line_t::al_symstart'
 *            - `%E'   Absolute end address of the surrounding symbol              `di_debug_addr2line_t::al_symend'
 *            - `%1E'  Absolute end address of the surrounding symbol - 1          `di_debug_addr2line_t::al_symend'
 *            - `%Dl'  Declaration line number (1-based; 0 if unknown)             `di_debug_addr2line_t::al_dclline'
 *            - `%Dc'  Declaration column number (1-based; 0 if unknown)           `di_debug_addr2line_t::al_dclcol'
 *            - `%Df'  Declaration filename (with path prefix)                     `di_debug_addr2line_t::(al_cubase|al_dclpath|al_dclfile)'
 *            - `%RDf' Declaration filename (without path prefix)                  `di_debug_addr2line_t::al_dclfile'
 *            - Any other character[-sequence] is forwarded as-is
 *      - `%[...]' Other sequences are reserved for future usage
 *
 *  - Interaction between '%$' for fixed-precision, and positional arguments:
 *    >> printf("fixed-precision: %$1$2$q", (size_t)4, "foo"); // prints: 'fixed-precision: "foo\0"'
 *    >> printf("positional-arg:  %1$q", "foo");               // prints: 'positional-arg:  "foo"'
 *    When '$' is encountered in a position where it isn't preceded by a number,
 *    it is interpreted as introducing a fixed-precision modifier (iow: "%$" has
 *    now been processed). When the format string also uses positional arguments,
 *    that fixed-precision modifier is then loaded from a positional argument.
 *    (iow: "%$1$"  has now been processed, indicating that the first argument is
 *    of  type `size_t', and  shall be used as  the fixed-precision modifier). At
 *    this  point, regular string processing continues, and "2$" is now processed
 *    as the argument selector for the data object that will be printed. Finally,
 *    the trailing "q" is processed to mean "Quoted string".
 *
 *    It should be obvious that a format-encoded width-argument cannot be used  with
 *    such a format-string  "%200$1$2$s", because  the parser would  think that  the
 *    leading "200$" was a request for a positional argument. Instead, you can write
 *    "%200:?1$2$s" (remember: "$" for fixed-precision is an alias for ":?").
 *
 *    When not using positional arguments, but still want to use '$' together with a
 *    format-encoded width-argument, you can use the fact that KOS doesn't enforce a
 *    mandatory ordering between format flags, precision, and width:
 *        >> printf("a%$25sb", (size_t)2, "foo"); // prints: 'a                       fob'
 *    Because the '$' doesn't follow a number here, this will not trigger positional
 *    argument  mode,  but  still  load  a  fixed-precision  argument  from varargs.
 *
 *  - Our format_printf()  implementation treats  all  invalid uses  as  weak
 *    undefined behavior. This means that when facing invalid printf  control
 *    sequences, it will never produce  any errors (return a negative  value)
 *    on its own, meaning the only reason `format_printf()' might ever return
 *    a  negative value,  is because a  call to its  given `printer' returned
 *    that same negative value.
 */

#ifdef __CC__
__SYSDECL_BEGIN

/* Calling convention used by `pformatprinter' */
#ifndef FORMATPRINTER_CC
#define FORMATPRINTER_CC __FORMATPRINTER_CC
#endif /* !FORMATPRINTER_CC */

#ifndef __pformatprinter_defined
#define __pformatprinter_defined
/* Callback functions prototypes provided to format functions.
 * NOTE: 'pformatprinter' usually returns the number of characters printed, but isn't required to.
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
typedef __pformatprinter pformatprinter;
#endif /* !__pformatprinter_defined */

#ifndef __pformatgetc_defined
#define __pformatgetc_defined
/* Read or unread 1 byte/word/dword of input data
 * @param: arg:    The user-defined closure parameter passed alongside this function pointer.
 * @return: >= 0:  The character that was read.
 * @return: EOF:   The input stream has ended.
 * @return: < EOF: An error occurred (Return the same value to the caller) */
typedef __pformatgetc pformatgetc;
typedef __pformatungetc pformatungetc;
typedef __format_word_t format_word_t;
#endif /* !__pformatgetc_defined */

#ifdef __CRT_HAVE_format_repeat
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_repeat,(pformatprinter __printer, void *__arg, char __ch, __SIZE_TYPE__ __num_repetitions),(__printer,__arg,__ch,__num_repetitions))
#else /* __CRT_HAVE_format_repeat */
#include <libc/local/format-printer/format_repeat.h>
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_repeat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBCCALL format_repeat)(pformatprinter __printer, void *__arg, char __ch, __SIZE_TYPE__ __num_repetitions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_repeat))(__printer, __arg, __ch, __num_repetitions); })
#endif /* !__CRT_HAVE_format_repeat */

/* TODO: These constants should go into <asm/crt/format-printer.h> */
#define FORMAT_ESCAPE_FNORMAL   0x0000 /* Normal quote flags. */
#define FORMAT_ESCAPE_FPRINTRAW 0x0001 /* Don't surround the quoted text with "..."; */
#define FORMAT_ESCAPE_FFORCEHEX 0x0002 /* Force hex encoding of all control characters without special strings (`"\n"', etc.). */
#define FORMAT_ESCAPE_FFORCEOCT 0x0004 /* Force octal encoding of all non-ascii characters. */
#define FORMAT_ESCAPE_FNOCTRL   0x0008 /* Disable special encoding strings such as `"\r"', `"\n"' or `"\e"' */
#define FORMAT_ESCAPE_FNOASCII  0x0010 /* Disable regular ascii-characters and print everything using special encodings. */
#define FORMAT_ESCAPE_FUPPERHEX 0x0020 /* Use uppercase characters for hex (e.g.: `"\xAB"'). */

#ifdef __CRT_HAVE_format_escape
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
__CDECLARE(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_escape,(pformatprinter __printer, void *__arg, char const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),(__printer,__arg,__text,__textlen,__flags))
#elif defined(__CRT_HAVE_format_quote)
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
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_escape,(pformatprinter __printer, void *__arg, char const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags),format_quote,(__printer,__arg,__text,__textlen,__flags))
#else /* ... */
#include <libc/local/format-printer/format_escape.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_escape, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBCCALL format_escape)(pformatprinter __printer, void *__arg, char const *__restrict __text, __SIZE_TYPE__ __textlen, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_escape))(__printer, __arg, __text, __textlen, __flags); })
#endif /* !... */
/* TODO: These constants should go into <asm/crt/format-printer.h> */
#define FORMAT_HEXDUMP_FNORMAL    0x0000 /* Normal hexdump flags. */
#define FORMAT_HEXDUMP_FHEXLOWER  0x0001 /* Print hex text of the dump in lowercase (does not affect address/offset). */
#define FORMAT_HEXDUMP_FNOADDRESS 0x0002 /* Don't include the absolute address at the start of every line. */
#define FORMAT_HEXDUMP_FOFFSETS   0x0004 /* Include offsets from the base address at the start of every line (after the address when also shown). */
#define FORMAT_HEXDUMP_FNOHEX     0x0008 /* Don't print the actual hex dump (hex data representation). */
#define FORMAT_HEXDUMP_FNOASCII   0x0010 /* Don't print ascii representation of printable characters at the end of lines. */
#define FORMAT_HEXDUMP_BYTES      0x0000 /* Dump data as bytes. */
#define FORMAT_HEXDUMP_WORDS      0x1000 /* Dump data as words (uint16_t). */
#define FORMAT_HEXDUMP_DWORDS     0x2000 /* Dump data as dwords (uint32_t). */
#define FORMAT_HEXDUMP_QWORDS     0x3000 /* Dump data as qwords (uint64_t). */
#define FORMAT_HEXDUMP_SIZEMASK   0x3000 /* Mask for the dump size. */

#ifdef __CRT_HAVE_format_hexdump
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
__CDECLARE(__ATTR_INS(3, 4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_hexdump,(pformatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags),(__printer,__arg,__data,__size,__linesize,__flags))
#else /* __CRT_HAVE_format_hexdump */
#include <libc/local/format-printer/format_hexdump.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_hexdump, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBCCALL format_hexdump)(pformatprinter __printer, void *__arg, void const *__restrict __data, __SIZE_TYPE__ __size, __SIZE_TYPE__ __linesize, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_hexdump))(__printer, __arg, __data, __size, __linesize, __flags); })
#endif /* !__CRT_HAVE_format_hexdump */




#ifdef __CRT_HAVE_format_vprintf
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
__CDECLARE(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,format_vprintf,(pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
#include <libc/local/format-printer/format_vprintf.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_vprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBCCALL format_vprintf)(pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vprintf))(__printer, __arg, __format, __args); })
#endif /* !__CRT_HAVE_format_vprintf */
#ifdef __CRT_HAVE_format_printf
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
__LIBC __ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__VLIBCCALL format_printf)(pformatprinter __printer, void *__arg, char const *__restrict __format, ...) __CASMNAME_SAME("format_printf");
#else /* __CRT_HAVE_format_printf */
#include <libc/local/format-printer/format_printf.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_CB(__VLIBCCALL format_printf)(pformatprinter __printer, void *__arg, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_printf))(__printer, __arg, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define format_printf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_printf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE_format_printf */




#ifdef __CRT_HAVE_format_vscanf
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
__CDECLARE(__ATTR_IN(4) __ATTR_LIBC_SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_CB,format_vscanf,(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char const *__restrict __format, __builtin_va_list __args),(__pgetc,__pungetc,__arg,__format,__args))
#else /* __CRT_HAVE_format_vscanf */
#include <libc/local/format-printer/format_vscanf.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_vscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_LIBC_SCANF(4, 0) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__LIBCCALL format_vscanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vscanf))(__pgetc, __pungetc, __arg, __format, __args); })
#endif /* !__CRT_HAVE_format_vscanf */
#ifdef __CRT_HAVE_format_scanf
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
__LIBC __ATTR_IN(4) __ATTR_LIBC_SCANF(4, 5) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__VLIBCCALL format_scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char const *__restrict __format, ...) __CASMNAME_SAME("format_scanf");
#else /* __CRT_HAVE_format_scanf */
#include <libc/local/format-printer/format_scanf.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(format_scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_LIBC_SCANF(4, 5) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_CB(__VLIBCCALL format_scanf)(pformatgetc __pgetc, pformatungetc __pungetc, void *__arg, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_scanf))(__pgetc, __pungetc, __arg, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define format_scanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_scanf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE_format_scanf */



#ifdef __CRT_HAVE_format_sprintf_printer
/* >> format_sprintf_printer(3)
 * Format-printer implementation for printing to a string buffer like `sprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__LIBC __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_sprintf_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __CASMNAME_SAME("format_sprintf_printer");
#else /* __CRT_HAVE_format_sprintf_printer */
#include <libc/local/format-printer/format_sprintf_printer.h>
/* >> format_sprintf_printer(3)
 * Format-printer implementation for printing to a string buffer like `sprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_sprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_sprintf_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_sprintf_printer))(__arg, __data, __datalen); })
#endif /* !__CRT_HAVE_format_sprintf_printer */


#ifndef __format_snprintf_data_defined
#define __format_snprintf_data_defined
/* Data structure for implementing snprintf() */
struct format_snprintf_data {
	char         *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !__format_snprintf_data_defined */
#define FORMAT_SNPRINTF_INIT(buf, bufsize) { buf, bufsize }
#define format_snprintf_init(self, buf, bufsize) \
	(void)((self)->sd_buffer = (buf), (self)->sd_bufsiz = (bufsize))

#ifdef __CRT_HAVE_format_snprintf_printer
/* >> format_snprintf_printer(3)
 * Format-printer implementation for printing to a string buffer like `snprintf(3)' would
 * NOTES:
 *  - No trailing NUL-character is implicitly appended !!!
 *  - The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 *  - The number  of required  characters is  `arg->sd_buffer - <orig_buf>', and  is
 *    equal to the sum of return values of all calls to `format_snprintf_printer(3)'
 *  - There is no error-case, so this function never returns a negative result */
__LIBC __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_snprintf_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __CASMNAME_SAME("format_snprintf_printer");
#else /* __CRT_HAVE_format_snprintf_printer */
#include <libc/local/format-printer/format_snprintf_printer.h>
/* >> format_snprintf_printer(3)
 * Format-printer implementation for printing to a string buffer like `snprintf(3)' would
 * NOTES:
 *  - No trailing NUL-character is implicitly appended !!!
 *  - The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 *  - The number  of required  characters is  `arg->sd_buffer - <orig_buf>', and  is
 *    equal to the sum of return values of all calls to `format_snprintf_printer(3)'
 *  - There is no error-case, so this function never returns a negative result */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_snprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_snprintf_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_snprintf_printer))(__arg, __data, __datalen); })
#endif /* !__CRT_HAVE_format_snprintf_printer */
#ifdef __CRT_HAVE_format_width
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__LIBC __ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_width)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __CASMNAME_SAME("format_width");
#else /* __CRT_HAVE_format_width */
#include <libc/local/format-printer/format_width.h>
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_width, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_width)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_width))(__arg, __data, __datalen); })
#endif /* !__CRT_HAVE_format_width */
#ifdef __CRT_HAVE_format_length
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__LIBC __ATTR_CONST __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW(__FORMATPRINTER_CC format_length)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __CASMNAME_SAME("format_length");
#elif defined(__CRT_HAVE_format_wwidth) && !defined(__KERNEL__)
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__COMPILER_CREDIRECT(__LIBC,__ATTR_CONST __ATTR_INS(2, 3) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW,__FORMATPRINTER_CC,format_length,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),format_wwidth,(__arg,__data,__datalen))
#else /* ... */
#include <libc/local/format-printer/format_length.h>
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_length, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_INS(2, 3) __ATTR_NONNULL((2)) __SSIZE_TYPE__ __NOTHROW(__FORMATPRINTER_CC format_length)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_length))(__arg, __data, __datalen); })
#endif /* !... */

#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */

#define FORMAT_APRINTF_DATA_INIT { __NULLPTR, 0, 0 }
#define format_aprintf_data_init(self) \
	(void)((self)->ap_base = __NULLPTR, (self)->ap_avail = (self)->ap_used = 0)
#define format_aprintf_data_cinit(self)             \
	(__hybrid_assert((self)->ap_base == __NULLPTR), \
	 __hybrid_assert((self)->ap_avail == 0),        \
	 __hybrid_assert((self)->ap_used == 0))
#if defined(NDEBUG) || defined(NDEBUG_FINI)
#define format_aprintf_data_fini(self)  (__libc_free((self)->ap_base))
#elif __SIZEOF_POINTER__ == 4
#define format_aprintf_data_fini(self)                  \
	(__libc_free((self)->ap_base),                      \
	 (self)->ap_base  = (char *)__UINT32_C(0xcccccccc), \
	 (self)->ap_avail = __UINT32_C(0xcccccccc),         \
	 (self)->ap_used  = __UINT32_C(0xcccccccc))
#elif __SIZEOF_POINTER__ == 8
#define format_aprintf_data_fini(self)                          \
	(__libc_free((self)->ap_base),                              \
	 (self)->ap_base  = (char *)__UINT64_C(0xcccccccccccccccc), \
	 (self)->ap_avail = __UINT64_C(0xcccccccccccccccc),         \
	 (self)->ap_used  = __UINT64_C(0xcccccccccccccccc))
#else /* ... */
#define format_aprintf_data_fini(self) (__libc_free((self)->ap_base))
#endif /* !... */

#ifdef __CRT_HAVE_format_aprintf_pack
/* >> format_aprintf_pack(3)
 * Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_aprintf_printer(3)', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_aprintf_data p = FORMAT_APRINTF_DATA_INIT;
 * >> error = format_printf(&format_aprintf_printer, &p, "%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_aprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_aprintf_pack(&p, NULL);
 * >> // `return' is an malloc()'d string "Hello World"
 * >> return result;
 * WARNING: Note that `format_aprintf_pack(3)' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free(3)'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `strlen(return)' when NUL characters  were
 *                  printed to the aprintf-printer at one point.
 *                  (e.g. `format_aprintf_printer(&my_printer, "\0", 1)') */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),char *,__NOTHROW_NCX,format_aprintf_pack,(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen),(__self,__pstrlen))
#else /* __CRT_HAVE_format_aprintf_pack */
#include <libc/local/format-printer/format_aprintf_pack.h>
/* >> format_aprintf_pack(3)
 * Pack  and  finalize  a  given  aprintf  format printer
 * Together with `format_aprintf_printer(3)', the aprintf
 * format  printer sub-system should  be used as follows:
 * >> char *result;
 * >> ssize_t error;
 * >> struct format_aprintf_data p = FORMAT_APRINTF_DATA_INIT;
 * >> error = format_printf(&format_aprintf_printer, &p, "%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_aprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_aprintf_pack(&p, NULL);
 * >> // `return' is an malloc()'d string "Hello World"
 * >> return result;
 * WARNING: Note that `format_aprintf_pack(3)' is able to return `NULL' as well,
 *          but  will  finalize  the  given   aprintf  printer  an  all   cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free(3)'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `strlen(return)' when NUL characters  were
 *                  printed to the aprintf-printer at one point.
 *                  (e.g. `format_aprintf_printer(&my_printer, "\0", 1)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_aprintf_pack, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2) char *__NOTHROW_NCX(__LIBCCALL format_aprintf_pack)(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ *__pstrlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_aprintf_pack))(__self, __pstrlen); })
#endif /* !__CRT_HAVE_format_aprintf_pack */
#ifdef __CRT_HAVE_format_aprintf_alloc
/* >> format_aprintf_alloc(3)
 * Allocate  a   buffer  of   `num_chars'  characters   at  the   end  of   `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INOUT(1),char *,__NOTHROW_NCX,format_aprintf_alloc,(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ __num_chars),(__self,__num_chars))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/format-printer/format_aprintf_alloc.h>
/* >> format_aprintf_alloc(3)
 * Allocate  a   buffer  of   `num_chars'  characters   at  the   end  of   `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_aprintf_alloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INOUT(1) char *__NOTHROW_NCX(__LIBCCALL format_aprintf_alloc)(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_aprintf_alloc))(__self, __num_chars); })
#endif /* ... */
#ifdef __CRT_HAVE_format_aprintf_printer
/* >> format_aprintf_printer(3)
 * Print data to  a dynamically  allocated heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__LIBC __ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_aprintf_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __CASMNAME_SAME("format_aprintf_printer");
#elif defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/format-printer/format_aprintf_printer.h>
/* >> format_aprintf_printer(3)
 * Print data to  a dynamically  allocated heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
__NAMESPACE_LOCAL_USING_OR_IMPL(format_aprintf_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ __NOTHROW_NCX(__FORMATPRINTER_CC format_aprintf_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_aprintf_printer))(__arg, __data, __datalen); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_FORMAT_PRINTER_H)
#include <parts/wchar/format-printer.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_FORMAT_PRINTER_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_FORMAT_PRINTER_H)
#include <parts/uchar/format-printer.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_FORMAT_PRINTER_H */
#endif /* __USE_UTF */

#endif /* !_FORMAT_PRINTER_H */
