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

%[default:section(".text.crt{|.dos}.string.format")]

%[define_decl_include_implication("<bits/crt/format-printer.h>" => [
	"<hybrid/typecore.h>",
])]

%[define_replacement(pformatprinter   = __pformatprinter)]
%[define_replacement(pformatgetc      = __pformatgetc)]
%[define_replacement(pformatungetc    = __pformatungetc)]
%[define_replacement(FORMATPRINTER_CC = __FORMATPRINTER_CC)]

%[define_type_class(__pformatprinter    = "TP")]
%[define_type_class(__pformatgetc       = "TP")]
%[define_type_class(__pformatungetc     = "TP")]
%[define_type_class(__pwformatprinter   = "TP")]
%[define_type_class(__pc16formatprinter = "TP")]
%[define_type_class(__pc32formatprinter = "TP")]

%[define_str2wcs_replacement(pformatprinter          = pwformatprinter)]
%[define_str2wcs_replacement(__pformatprinter        = __pwformatprinter)]
%[define_str2wcs_replacement(format_repeat           = format_wrepeat)]
%[define_str2wcs_replacement(format_escape           = format_wescape)]
%[define_str2wcs_replacement(format_hexdump          = format_whexdump)]
%[define_str2wcs_replacement(format_printf           = format_wprintf)]
%[define_str2wcs_replacement(format_vprintf          = format_vwprintf)]
%[define_str2wcs_replacement(format_sprintf_printer  = format_wsprintf_printer)]
%[define_str2wcs_replacement(format_snprintf_data    = format_wsnprintf_data)]
%[define_str2wcs_replacement(format_snprintf_printer = format_wsnprintf_printer)]
%[define_str2wcs_replacement(FORMATPRINTER_CC        = WFORMATPRINTER_CC)]
%[define_str2wcs_replacement(__FORMATPRINTER_CC      = __WFORMATPRINTER_CC)]

%[define_str2wcs_replacement(ATTR_LIBC_PRINTF     = ATTR_LIBC_WPRINTF)]
%[define_str2wcs_replacement(ATTR_LIBC_PRINTF_P   = ATTR_LIBC_WPRINTF_P)]
%[define_str2wcs_replacement(ATTR_LIBC_SCANF      = ATTR_LIBC_WSCANF)]
%[define_str2wcs_replacement(__ATTR_LIBC_PRINTF   = __ATTR_LIBC_WPRINTF)]
%[define_str2wcs_replacement(__ATTR_LIBC_PRINTF_P = __ATTR_LIBC_WPRINTF_P)]
%[define_str2wcs_replacement(__ATTR_LIBC_SCANF    = __ATTR_LIBC_WSCANF)]

%[define_str2wcs_header_replacement("<format-printer.h>"          = "<parts/wchar/format-printer.h>")]
%[define_str2wcs_header_replacement("<bits/crt/format-printer.h>" = "<bits/crt/wformat-printer.h>")]


%[assume_undefined_in_kos_userspace(__NO_PRINTF_ESCAPE)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_UNICODE_CHARS)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_UNICODE_STRING)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_STRERROR)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_HEX)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_GEN)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_DISASM)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_VINFO)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_FLOATING_POINT)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_POSITIONAL)]
%[assume_undefined_in_kos_userspace(__NO_PRINTF_PERCENT_N)]
%[assume_undefined_in_kos_userspace(__NO_SCANF_FLOATING_POINT)]


%(auto_source){
#include "../libc/dl.h"      /* Use libc's relocation-optimized dl* functions. */
#include "../libc/string.h"  /* Dependency of `#include <libc/template/format-printf.h>' */
#include "../libc/unicode.h" /* Dependency of `#include <libc/template/format-scanf.h>' */
/**/
#include <hybrid/__assert.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <hybrid/__alloca.h> /* Dependency of `#include <libc/template/format-printf.h>' */

#include <bits/math-constants.h>
#include <bits/types.h> /* Dependency of `#include <libc/template/format-printf.h>' */

#include <libc/template/itoa_digits.h> /* Dependency of `#include <libc/template/format-printf.h>' */
#include <libdisasm/disassembler.h>    /* Dependency of `#include <libc/template/format-printf.h>' */
#ifdef __KERNEL__
#include <kernel/addr2line.h>
#else /* __KERNEL__ */
#include <libdebuginfo/addr2line.h>
#endif /* !__KERNEL__ */
}

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/__assert.h>
)]%{

}%[insert:prefix(
#include <bits/crt/format-printer.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

}%[insert:prefix(
#include <libc/malloc.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

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
 *  - gLibc-style "%m" (print string returned by `strerror(errno)')
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

}

%[define(FORMAT_REPEAT_BUFSIZE = 64)]


@@>> format_repeat(3)
@@Repeat  `ch'  a   number  of  `num_repetitions'   times
@@The usual format-printer rules apply, and this function
@@is  allowed to  call `printer'  as often  as it chooses
[[kernel, throws, decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[impl_include("<hybrid/__alloca.h>", "<libc/string.h>")]]
$ssize_t format_repeat([[nonnull]] pformatprinter printer, void *arg,
                       char ch, $size_t num_repetitions) {
	ssize_t result, temp;
@@pp_ifdef __hybrid_alloca@@
	char *buffer;
	if likely(num_repetitions <= FORMAT_REPEAT_BUFSIZE) {
		buffer = (char *)__hybrid_alloca(num_repetitions);
		__libc_memsetc(buffer, ch, num_repetitions, __SIZEOF_CHAR__);
		return (*printer)(arg, buffer, num_repetitions);
	}
	buffer = (char *)__hybrid_alloca(FORMAT_REPEAT_BUFSIZE);
	__libc_memsetc(buffer, ch, FORMAT_REPEAT_BUFSIZE, __SIZEOF_CHAR__);
@@pp_else@@
	char buffer[FORMAT_REPEAT_BUFSIZE];
	if likely(num_repetitions <= FORMAT_REPEAT_BUFSIZE) {
		__libc_memsetc(buffer, ch, num_repetitions, __SIZEOF_CHAR__);
		return (*printer)(arg, buffer, num_repetitions);
	}
	__libc_memsetc(buffer, ch, FORMAT_REPEAT_BUFSIZE, __SIZEOF_CHAR__);
@@pp_endif@@
	result = (*printer)(arg, buffer, FORMAT_REPEAT_BUFSIZE);
	if unlikely(result < 0)
		goto done;
	for (;;) {
		num_repetitions -= FORMAT_REPEAT_BUFSIZE;
		if (num_repetitions < FORMAT_REPEAT_BUFSIZE)
			break;
		temp = (*printer)(arg, buffer, FORMAT_REPEAT_BUFSIZE);
		if unlikely(temp < 0)
			goto done;
		result += temp;
	}
	if (num_repetitions) {
		temp = (*printer)(arg, buffer, num_repetitions);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}




%[define(FORMAT_ESCAPE_FNORMAL   = 0x0000)] /* Normal quote flags. */
%[define(FORMAT_ESCAPE_FPRINTRAW = 0x0001)] /* Don't surround the quoted text with "..."; */
%[define(FORMAT_ESCAPE_FFORCEHEX = 0x0002)] /* Force hex encoding of all control characters without special strings (`"\n"', etc.). */
%[define(FORMAT_ESCAPE_FFORCEOCT = 0x0004)] /* Force octal encoding of all non-ascii characters. */
%[define(FORMAT_ESCAPE_FNOCTRL   = 0x0008)] /* Disable special encoding strings such as `"\r"', `"\n"' or `"\e"' */
%[define(FORMAT_ESCAPE_FNOASCII  = 0x0010)] /* Disable regular ascii-characters and print everything using special encodings. */
%[define(FORMAT_ESCAPE_FUPPERHEX = 0x0020)] /* Use uppercase characters for hex (e.g.: `"\xAB"'). */

%{

/* TODO: These constants should go into <asm/crt/format-printer.h> */
#define FORMAT_ESCAPE_FNORMAL   0x0000 /* Normal quote flags. */
#define FORMAT_ESCAPE_FPRINTRAW 0x0001 /* Don't surround the quoted text with "..."; */
#define FORMAT_ESCAPE_FFORCEHEX 0x0002 /* Force hex encoding of all control characters without special strings (`"\n"', etc.). */
#define FORMAT_ESCAPE_FFORCEOCT 0x0004 /* Force octal encoding of all non-ascii characters. */
#define FORMAT_ESCAPE_FNOCTRL   0x0008 /* Disable special encoding strings such as `"\r"', `"\n"' or `"\e"' */
#define FORMAT_ESCAPE_FNOASCII  0x0010 /* Disable regular ascii-characters and print everything using special encodings. */
#define FORMAT_ESCAPE_FUPPERHEX 0x0020 /* Use uppercase characters for hex (e.g.: `"\xAB"'). */

}

@@>> format_escape(3)
@@Do C-style escape on the given text, printing it to the given printer.
@@Input:
@@>> Hello "World" W
@@>> hat a great day.
@@Output #1: "\"Hello \"World\" W\nhat a great day.\""
@@Output #2:   "Hello \"World\" W\nhat a great day"
@@NOTE: Output  #2 is generated if `FORMAT_ESCAPE_FPRINTRAW' is set
@@This  function  escapes  all  control  and  non-ascii characters,
@@preferring octal encoding for control characters and hex-encoding
@@for other non-ascii characters, a  behavior that may be  modified
@@with the `FORMAT_ESCAPE_FFORCE*' flags
@@@param: printer: A function called for all quoted portions of the text
@@@param: textlen: The total number of bytes to escape, starting at `text'
[[kernel, throws, alias("format_quote")]]
[[if(!defined(__KERNEL__)), export_as("format_quote")]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/template/itoa_digits.h>", "<libc/template/hex.h>")]]
$ssize_t format_escape([[nonnull]] pformatprinter printer, void *arg,
                       [[in(textlen)]] /*utf-8*/ char const *__restrict text,
                       $size_t textlen, unsigned int flags) {
	__PRIVATE char const quote[1] = { '\"' };
	char encoded_text[12]; size_t encoded_text_size;
	ssize_t result = 0, temp;
	char const *textend = text + textlen;
	char const *flush_start = text;
	encoded_text[0] = '\\';
	if likely(!(flags & FORMAT_ESCAPE_FPRINTRAW)) {
		temp = (*printer)(arg, quote, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	while (text < textend) {
		char const *old_text = text;
		uint32_t ch;
@@pp_if __SIZEOF_CHAR__ == 1@@
		ch = unicode_readutf8_n((char const **)&text, textend);
@@pp_elif __SIZEOF_CHAR__ == 2@@
		ch = unicode_readutf16_n((char16_t const **)&text,
		                         (char16_t const *)textend);
@@pp_else@@
		ch = (uint32_t)*text++;
@@pp_endif@@
		if unlikely(ch < 32 || ch >= 127  || ch == '\'' ||
		              ch == '\"' || ch == '\\' ||
		             (flags & FORMAT_ESCAPE_FNOASCII)) {
			/* Flush unwritten direct-copy text. */
			if (flush_start < old_text) {
				temp = (*printer)(arg, flush_start, (size_t)(old_text - flush_start));
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			/* Character requires special encoding. */
			if (ch < 32) {
				/* Control character. */
				if (flags & FORMAT_ESCAPE_FNOCTRL) {
default_ctrl:
					if (flags & FORMAT_ESCAPE_FFORCEHEX)
						goto encode_hex;
encode_oct:
					if (text < textend) {
						char const *new_text = text;
						uint32_t next_ch;
@@pp_if __SIZEOF_CHAR__ == 1@@
						next_ch = unicode_readutf8_n((char const **)&new_text, textend);
@@pp_elif __SIZEOF_CHAR__ == 2@@
						next_ch = unicode_readutf16_n((char16_t const **)&new_text,
						                              (char16_t const *)textend);
@@pp_else@@
						next_ch = (uint32_t)*new_text++;
@@pp_endif@@
						if (next_ch >= '0' && next_ch <= '7')
							goto encode_hex;
					}
					if (ch <= 0x07) {
						encoded_text[1] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 2;
					} else if (ch <= 0x3f) {
						encoded_text[1] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[2] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 3;
					} else if (ch <= 0x1ff) {
						encoded_text[1] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[2] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[3] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 4;
					} else if (ch <= 0xfff) {
						encoded_text[1] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[2] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[3] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[4] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 5;
					} else if (ch <= 0x7fff) {
						encoded_text[1] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[2] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[3] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[4] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[5] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 6;
					} else if (ch <= 0x3ffff) {
						encoded_text[1] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[2] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[3] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[4] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[5] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[6] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 7;
					} else if (ch <= 0x1fffff) {
						encoded_text[1] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[2] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[3] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[4] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[5] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[6] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[7] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 8;
					} else if (ch <= 0xffffff) {
						encoded_text[1] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[2] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[3] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[4] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[5] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[6] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[7] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[8] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 9;
					} else if (ch <= 0x7ffffff) {
						encoded_text[1] = itoa_decimal((ch & 0x07000000) >> 24);
						encoded_text[2] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[3] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[4] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[5] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[6] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[7] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[8] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[9] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 10;
					} else if (ch <= 0x3fffffff) {
						encoded_text[1] = itoa_decimal((ch & 0x38000000) >> 27);
						encoded_text[2] = itoa_decimal((ch & 0x07000000) >> 24);
						encoded_text[3] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[4] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[5] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[6] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[7] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[8] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[9] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[10] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 11;
					} else {
						encoded_text[1] = itoa_decimal((ch & 0xc0000000) >> 30);
						encoded_text[2] = itoa_decimal((ch & 0x38000000) >> 27);
						encoded_text[3] = itoa_decimal((ch & 0x07000000) >> 24);
						encoded_text[4] = itoa_decimal((ch & 0x00e00000) >> 21);
						encoded_text[5] = itoa_decimal((ch & 0x001c0000) >> 18);
						encoded_text[6] = itoa_decimal((ch & 0x00038000) >> 15);
						encoded_text[7] = itoa_decimal((ch & 0x00007000) >> 12);
						encoded_text[8] = itoa_decimal((ch & 0x00000e00) >> 9);
						encoded_text[9] = itoa_decimal((ch & 0x000000c0) >> 6);
						encoded_text[10] = itoa_decimal((ch & 0x00000038) >> 3);
						encoded_text[11] = itoa_decimal((ch & 0x00000007));
						encoded_text_size = 12;
					}
					goto print_encoded;
				}
special_control:
				switch (ch) {

				case 7:  ch = 'a'; break;
				case 8:  ch = 'b'; break;
				case 9:  ch = 't'; break;
				case 10: ch = 'n'; break;
				case 11: ch = 'v'; break;
				case 12: ch = 'f'; break;
				case 13: ch = 'r'; break;
				case 27: ch = 'e'; break;

				case '\\':
				case '\'':
				case '\"':
					break;

				default:
					goto default_ctrl;
				}
				encoded_text[1] = (char)ch;
				encoded_text_size = 2;
				goto print_encoded;
			} else if ((ch == '\\' || ch == '\'' || ch == '\"') &&
			           !(flags & FORMAT_ESCAPE_FNOCTRL)) {
				goto special_control;
			} else {
				/* Non-ascii character. */
/*default_nonascii:*/
				if (flags & FORMAT_ESCAPE_FFORCEOCT)
					goto encode_oct;
encode_hex:
				if (text < textend) {
					char const *new_text = text;
					char32_t next_ch;
@@pp_if __SIZEOF_CHAR__ == 1@@
					next_ch = unicode_readutf8_n((char const **)&new_text, textend);
@@pp_elif __SIZEOF_CHAR__ == 2@@
					next_ch = unicode_readutf16_n((char16_t const **)&new_text,
					                              (char16_t const *)textend);
@@pp_else@@
					next_ch = (char32_t)*new_text++;
@@pp_endif@@
					if (__libc_ishex(next_ch))
						goto encode_uni;
				}
				if (ch <= 0xf) {
					encoded_text[1] = 'x';
					encoded_text[2] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, ch);
					encoded_text_size = 3;
				} else if (ch <= 0x7f) {
					encoded_text[1] = 'x';
					encoded_text[2] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x000000f0) >> 4);
					encoded_text[3] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, ch & 0x0000000f);
					encoded_text_size = 4;
				} else {
encode_uni:
					if (ch <= 0xffff) {
						encoded_text[1] = 'u';
						encoded_text[2] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x0000f000) >> 12);
						encoded_text[3] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x00000f00) >> 8);
						encoded_text[4] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x000000f0) >> 4);
						encoded_text[5] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, ch & 0x0000000f);
						encoded_text_size = 6;
					} else {
						encoded_text[1] = 'U';
						encoded_text[2] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0xf0000000) >> 28);
						encoded_text[3] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x0f000000) >> 24);
						encoded_text[4] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x00f00000) >> 20);
						encoded_text[5] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x000f0000) >> 16);
						encoded_text[6] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x0000f000) >> 12);
						encoded_text[7] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x00000f00) >> 8);
						encoded_text[8] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, (ch & 0x000000f0) >> 4);
						encoded_text[9] = itoa_digit(flags & FORMAT_ESCAPE_FUPPERHEX, ch & 0x0000000f);
						encoded_text_size = 10;
					}
				}
print_encoded:
				temp = (*printer)(arg, encoded_text, encoded_text_size);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			flush_start = text;
		}
	}
/*done:*/
	if (flush_start < text) {
		temp = (*printer)(arg, flush_start, (size_t)(text - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	if likely(!(flags & FORMAT_ESCAPE_FPRINTRAW)) {
		temp = (*printer)(arg, quote, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	return result;
err:
	return temp;
}




%[define(FORMAT_HEXDUMP_FNORMAL    = 0x0000)] /* Normal hexdump flags. */
%[define(FORMAT_HEXDUMP_FHEXLOWER  = 0x0001)] /* Print hex text of the dump in lowercase (does not affect address/offset). */
%[define(FORMAT_HEXDUMP_FNOADDRESS = 0x0002)] /* Don't include the absolute address at the start of every line. */
%[define(FORMAT_HEXDUMP_FOFFSETS   = 0x0004)] /* Include offsets from the base address at the start of every line (after the address when also shown). */
%[define(FORMAT_HEXDUMP_FNOHEX     = 0x0008)] /* Don't print the actual hex dump (hex data representation). */
%[define(FORMAT_HEXDUMP_FNOASCII   = 0x0010)] /* Don't print ascii representation of printable characters at the end of lines. */
%[define(FORMAT_HEXDUMP_BYTES      = 0x0000)] /* Dump data as bytes. */
%[define(FORMAT_HEXDUMP_WORDS      = 0x1000)] /* Dump data as words (uint16_t). */
%[define(FORMAT_HEXDUMP_DWORDS     = 0x2000)] /* Dump data as dwords (uint32_t). */
%[define(FORMAT_HEXDUMP_QWORDS     = 0x3000)] /* Dump data as qwords (uint64_t). */
%[define(FORMAT_HEXDUMP_SIZEMASK   = 0x3000)] /* Mask for the dump size. */

%{
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

}


@@>> format_hexdump(3)
@@Print a hex dump of the given data using the provided format printer
@@@param: printer:  The format printer callback
@@@param: data:     A pointer to the data that should be dumped
@@@param: size:     The amount of bytes read starting at data
@@@param: linesize: The max amount of bytes to include per-line
@@                  HINT: Pass ZERO(0) to use a default size (16)
@@@param: flags:    A set of `"FORMAT_HEXDUMP_FLAG_*"'
@@@return: >= 0: The sum of all values returned by `printer'
@@@return: < 0:  The first negative value ever returned by `printer' (if any)
[[kernel, throws, decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[impl_include("<hybrid/__alloca.h>", "<hybrid/__unaligned.h>", "<hybrid/byteorder.h>")]]
[[impl_include("<libc/template/itoa_digits.h>")]]
$ssize_t format_hexdump([[nonnull]] pformatprinter printer, void *arg,
                        [[in(size)]] void const *__restrict data, $size_t size,
                        $size_t linesize, unsigned int flags) {
	__PRIVATE char const lf[1] = { '\n' };
	byte_t const *line_data;
	char buffer[
		(1 + (sizeof(void *) * 2) + 1) < 17 ? 17 :
		(1 + (sizeof(void *) * 2) + 1)], *dst;
	ssize_t temp, result = 0;
	unsigned int i; uintptr_t value;
	unsigned int offset_digits = 0;
	if (!size) goto done;
	if (!linesize) linesize = 16;
	if (flags & FORMAT_HEXDUMP_FOFFSETS) {
		value = size;
		do {
			++offset_digits;
		} while ((value >>= 4) != 0);
	}
	line_data = (byte_t const *)data;
	for (;;) {
		size_t line_len = linesize;
		if (line_len > size)
			line_len = size;
		if (!(flags & FORMAT_HEXDUMP_FNOADDRESS)) {
			value = (uintptr_t)line_data;
			dst = buffer + sizeof(void *) * 2;
			*dst = ' ';
			while (dst > buffer) {
				*--dst = itoa_digit(!(flags & FORMAT_HEXDUMP_FHEXLOWER), value & 0xf);
				value >>= 4;
			}
			temp = (*printer)(arg, buffer, (sizeof(void *) * 2) + 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (flags & FORMAT_HEXDUMP_FOFFSETS) {
			dst = buffer + 1 + offset_digits;
			*dst = ' ';
			value = (line_data - (byte_t const *)data);
			while (dst > buffer + 1) {
				*--dst = itoa_digit(!(flags & FORMAT_HEXDUMP_FHEXLOWER), value & 0xf);
				value >>= 4;
			}
			buffer[0] = '+';
			temp = (*printer)(arg, buffer, (size_t)2 + offset_digits);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		if (!(flags & FORMAT_HEXDUMP_FNOHEX)) {
			size_t i = 0;
			size_t tailspace_count;
			switch (flags & FORMAT_HEXDUMP_SIZEMASK) {

			default:
				tailspace_count = linesize * 3;
				break;

			case FORMAT_HEXDUMP_WORDS:
				tailspace_count = (linesize / 2) * 5 + (linesize % 2) * 3;
				buffer[4] = ' ';
				for (; i + 2 <= line_len; i += 2) {
					u16 w = __hybrid_unaligned_get16((u16 *)(line_data + i));
					dst = buffer + 4;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & FORMAT_HEXDUMP_FHEXLOWER), w & 0xf);
						w >>= 4;
					}
					temp = (*printer)(arg, buffer, 5);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 5;
				}
				break;

			case FORMAT_HEXDUMP_DWORDS:
				tailspace_count = (linesize / 4) * 9 + (linesize % 4) * 3;
				buffer[8] = ' ';
				for (; i + 4 <= line_len; i += 4) {
					u32 l = __hybrid_unaligned_get32((u32 *)(line_data + i));
					dst = buffer + 8;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & FORMAT_HEXDUMP_FHEXLOWER), l & 0xf);
						l >>= 4;
					}
					temp = (*printer)(arg, buffer, 9);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 9;
				}
				break;

			case FORMAT_HEXDUMP_QWORDS:
				tailspace_count = (linesize / 8) * 17 + (linesize % 8) * 3;
				buffer[16] = ' ';
				for (; i + 8 <= line_len; i += 8) {
@@pp_if __SIZEOF_POINTER__ >= 8@@
					u64 q = __hybrid_unaligned_get64((u64 *)(line_data + i));
					dst = buffer + 16;
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & FORMAT_HEXDUMP_FHEXLOWER), q & 0xf);
						q >>= 4;
					}
@@pp_else@@
					u32 a, b;
@@pp_if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__@@
					a = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
					b = __hybrid_unaligned_get32((u32 *)(line_data + i));
@@pp_else@@
					a = __hybrid_unaligned_get32((u32 *)(line_data + i));
					b = __hybrid_unaligned_get32((u32 *)(line_data + i + 4));
@@pp_endif@@
					dst = buffer + 16;
					while (dst > buffer + 8) {
						*--dst = itoa_digit(!(flags & FORMAT_HEXDUMP_FHEXLOWER), b & 0xf);
						b >>= 4;
					}
					while (dst > buffer) {
						*--dst = itoa_digit(!(flags & FORMAT_HEXDUMP_FHEXLOWER), a & 0xf);
						a >>= 4;
					}
@@pp_endif@@
					temp = (*printer)(arg, buffer, 17);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					tailspace_count -= 17;
				}
				break;
			}
			buffer[2] = ' ';
			for (; i < line_len; ++i) {
				byte_t b = line_data[i];
				buffer[0] = itoa_digit(!(flags & FORMAT_HEXDUMP_FHEXLOWER), b >> 4);
				buffer[1] = itoa_digit(!(flags & FORMAT_HEXDUMP_FHEXLOWER), b & 0xf);
				temp = (*printer)(arg, buffer, 3);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				tailspace_count -= 3;
			}
			if (tailspace_count) {
				temp = format_repeat(printer, arg, ' ', tailspace_count);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (!(flags & FORMAT_HEXDUMP_FNOASCII)) {
			for (i = 0; i < line_len; ++i) {
				byte_t b = line_data[i];
				if (!isprint(b))
					b = '.';
				temp = (*printer)(arg, (char const *)&b, 1);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		if (line_len >= size)
			break;
		line_data += line_len;
		size      -= line_len;
		temp = (*printer)(arg, lf, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}



%
%
%
%


@@>> format_printf(3), format_vprintf(3)
@@Generic printf implementation. Taking a regular printf-style format string and arguments,
@@this  function will call the given `printer' callback with various strings that, when put
@@together, result in the desired formated text.
@@ - `printer' obviously is called with the text parts in their correct order
@@ - If `printer' returns '<  0', the function returns  immediately,
@@   yielding that same value. Otherwise, `format_printf(3)' returns
@@   the sum of all return values from `printer'.
@@ - The strings passed to `printer'  may not necessarily be zero-terminated,  and
@@   a second argument is passed that indicates the absolute length in characters.
@@@return: >= 0: The sum of all values returned by `printer'
@@@return: < 0:  The first negative value ever returned by `printer' (if any)
[[kernel, libc, throws]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[impl_include("<parts/printf-config.h>", "<bits/types.h>")]]
[[impl_include("<libc/template/itoa_digits.h>")]]
[[impl_include("<libc/parts.uchar.string.h>")]]
[[impl_include("<libc/string.h>", "<libc/errno.h>")]]
[[impl_include("<hybrid/__assert.h>", "<hybrid/__alloca.h>")]]
[[impl_prefix(
@@pp_ifndef __NO_PRINTF_DISASM@@
@@pp_if !defined(__KERNEL__) || !defined(__KOS__)@@
@#include <dlfcn.h>@
@@pp_endif@@
@#include <libdisasm/disassembler.h>@
@@pp_endif@@
@@pp_ifndef __NO_PRINTF_VINFO@@
@@pp_if !defined(__KERNEL__) || !defined(__KOS__)@@
@#include <dlfcn.h>@
@#include <libdebuginfo/addr2line.h>@
@@pp_else@@
@#include <kernel/addr2line.h>@
@@pp_endif@@
@@pp_endif@@
)]]
$ssize_t format_vprintf([[nonnull]] pformatprinter printer, void *arg,
                        [[in, format]] char const *__restrict format,
                        $va_list args) {
#ifndef __INTELLISENSE__
#define __FORMAT_PRINTER           printer
#define __FORMAT_ARG               arg
#define __FORMAT_FORMAT            format
#define __FORMAT_ARGS              args
#define __CHAR_TYPE                char
#define __CHAR_SIZE                __SIZEOF_CHAR__
#define __FORMAT_STRERROR          strerror
#define __FORMAT_REPEAT            format_repeat
#define __FORMAT_HEXDUMP           format_hexdump
#define __FORMAT_WIDTH             format_width
#define __FORMAT_ESCAPE            format_escape
#define __FORMAT_WIDTH16           format_c16width
#define __FORMAT_WIDTH32           format_c32width
#define __FORMAT_ESCAPE16          format_c16escape
#define __FORMAT_ESCAPE32          format_c32escape
#define __FORMAT_UNICODE_WRITECHAR unicode_writeutf8
#define __FORMAT_UNICODE_FORMAT16  format_16to8
#define __FORMAT_UNICODE_FORMAT32  format_32to8
@#include <libc/template/format-printf.h>@
#endif /* !__INTELLISENSE__ */
}

[[kernel, libc, throws]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>"), doc_alias("format_vprintf")]]
$ssize_t format_printf([[nonnull]] pformatprinter printer, void *arg,
                       [[in, format]] char const *__restrict format, ...) {
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = format_vprintf(printer, arg, format, args);
	va_end(args);
	return result;
}

%
%
%
%
@@>> format_scanf(3), format_vscanf(3)
@@Generic     scanf     implementation
@@Taking a regular scanf-style format string and argument, these
@@functions will  call  the  given  `pgetc'  function  which  in
@@return should successively  yield a character  at a time  from
@@some kind of input source.
@@ - If  `pgetc'  returns  `< 0', scanning  aborts  and that  value  is returned.
@@   Otherwise, the function returns the amount of successfully parsed arguments.
@@ - The user may  use `pgetc' to  track the last  read character to  get
@@   additional information about what character caused the scan to fail.
@@ - The given `pgetc' should also indicate EOF by returning `NUL'
@@ - This implementation supports the following extensions:
@@   - `%[A-Z]'   -- Character ranges in scan patterns
@@   - `%[^abc]'  -- Inversion of a scan pattern
@@   - `"\n"'     -- Skip any kind of linefeed (`"\n"', `"\r"', `"\r\n"')
@@   - `%$s'      -- `$'-modifier, available for any format outputting a string.
@@                   This modifier  reads a  `size_t'  from the  argument  list,
@@                   that specifies  the size  of the  following string  buffer:
@@                >> char buffer[64];
@@                >> sscanf(data, "My name is %.?s\n", sizeof(buffer), buffer);
@@format -> %[*|?][width][length]specifier
@@@return: 0 :  No data could be scanned.
@@@return: * :  The total number of successfully scanned arguments.
@@@return: EOF: `PGETC' returned EOF the first time an attempt at reading was made
[[throws, kernel]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/string.h>", "<libc/unicode.h>")]]
[[impl_include("<parts/printf-config.h>")]]
[[impl_include("<bits/math-constants.h>")]]
$ssize_t format_vscanf([[nonnull]] pformatgetc pgetc,
                       [[nonnull]] pformatungetc pungetc, void *arg,
                       [[in, format]] char const *__restrict format, $va_list args) {
#ifndef __INTELLISENSE__
#define __CHAR_TYPE      char
#define __CHAR_SIZE      __SIZEOF_CHAR__
#define __FORMAT_PGETC   pgetc
#define __FORMAT_PUNGETC pungetc
#define __FORMAT_ARG     arg
#define __FORMAT_FORMAT  format
#define __FORMAT_ARGS    args
@#include <libc/template/format-scanf.h>@
#endif /* !__INTELLISENSE__ */
}

[[throws]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[doc_alias("format_vscanf"), kernel]]
$ssize_t format_scanf([[nonnull]] pformatgetc pgetc,
                      [[nonnull]] pformatungetc pungetc, void *arg,
                      [[in, format]] char const *__restrict format, ...) {
	ssize_t result;
	va_list args;
	va_start(args, format);
	result = format_vscanf(pgetc, pungetc, arg, format, args);
	va_end(args);
	return result;
}


%
%
%
@@>> format_sprintf_printer(3)
@@Format-printer implementation for printing to a string buffer like `sprintf' would
@@WARNING: No trailing NUL-character is implicitly appended
[[kernel, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
$ssize_t format_sprintf_printer([[nonnull]] /*char ***/ void *arg,
                                [[in(datalen)]] /*utf-8*/ char const *__restrict data,
                                $size_t datalen) {
	*(char **)arg = (char *)mempcpyc(*(char **)arg, data, datalen, sizeof(char));
	return (ssize_t)datalen;
}

%{


#ifndef __format_snprintf_data_defined
#define __format_snprintf_data_defined
/* Data structure for implementing snprintf() */
struct format_snprintf_data {
	char         *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !__format_snprintf_data_defined */
#define FORMAT_SNPRINTF_INIT(buf, bufsize)       { buf, bufsize }
#define format_snprintf_init(self, buf, bufsize) ((self)->sd_buffer = (buf), (self)->sd_bufsiz = (bufsize))

}


@@>> format_snprintf_printer(3)
@@Format-printer implementation for printing to a string buffer like `snprintf(3)' would
@@WARNING: No trailing NUL-character is implicitly appended
@@NOTE: The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
@@NOTE: The   number   of   required   characters   is   `arg->sd_buffer - <orig_buf>',  or
@@      alternatively the sum of return values of all calls to `format_snprintf_printer(3)'
[[kernel, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
$ssize_t format_snprintf_printer([[nonnull]] /*struct format_snprintf_data**/ void *arg,
                                 [[in(datalen)]] /*utf-8*/ char const *__restrict data, $size_t datalen) {
	struct __local_format_snprintf_data {
		char  *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		size_t sd_bufsiz; /* Remaining buffer size. */
	};
	struct __local_format_snprintf_data *ctrl;
	size_t result = datalen;
	ctrl = (struct __local_format_snprintf_data *)arg;
	if (result > ctrl->sd_bufsiz)
		result = ctrl->sd_bufsiz;
	memcpyc(ctrl->sd_buffer, data, result, sizeof(char));
	ctrl->sd_buffer += datalen;
	ctrl->sd_bufsiz -= result;
	return (ssize_t)datalen;
}


@@>> format_width(3)
@@Returns the width (number of characters; not bytes) of the given unicode string
@@The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL'
[[kernel, pure, impl_include("<libc/template/unicode_utf8seqlen.h>")]]
[[kernel, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
$ssize_t format_width(void *arg,
                      [[in(datalen)]] /*utf-8*/ char const *__restrict data,
                      $size_t datalen) {
	size_t result = 0;
	char const *iter, *end;
	(void)arg;
	end = (iter = data) + datalen;
	while (iter < end) {
		u8 len;
		len = unicode_utf8seqlen[(u8)*iter];
		if unlikely(!len)
			len = 1;
		iter += len;
		++result;
	}
	return (ssize_t)result;
}

@@>> format_length(3)
@@Always re-return `datalen' and ignore all other arguments
@@Both the `arg'  and `data' arguments  are simply  ignored
[[kernel, const, no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[if(!defined(__KERNEL__)), kos_export_alias("format_wwidth")]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
$ssize_t format_length(void *arg,
                       [[in(datalen)]] /*utf-8*/ char const *__restrict data,
                       $size_t datalen) {
	(void)arg;
	(void)data;
	return (ssize_t)datalen;
}


%{

#ifndef __format_aprintf_data_defined
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif /* !__format_aprintf_data_defined */

#define FORMAT_APRINTF_DATA_INIT        { __NULLPTR, 0, 0 }
#define format_aprintf_data_init(self)  ((self)->ap_base = __NULLPTR, (self)->ap_avail = (self)->ap_used = 0)
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

}

%[define(DEFINE_FORMAT_APRINTF_DATA =
@@pp_ifndef __format_aprintf_data_defined@@
#define __format_aprintf_data_defined
struct format_aprintf_data {
	char         *@ap_base@;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ @ap_avail@; /* Unused buffer size */
	__SIZE_TYPE__ @ap_used@;  /* Used buffer size */
};
@@pp_endif@@
)]


@@>> format_aprintf_pack(3)
@@Pack  and  finalize  a  given  aprintf  format printer
@@Together with `format_aprintf_printer(3)', the aprintf
@@format  printer sub-system should  be used as follows:
@@>> char *result;
@@>> ssize_t error;
@@>> struct format_aprintf_data p = FORMAT_APRINTF_DATA_INIT;
@@>> error = format_printf(&format_aprintf_printer, &p, "%s %s", "Hello", "World");
@@>> if unlikely(error < 0) {
@@>>     format_aprintf_data_fini(&p);
@@>>     return NULL;
@@>> }
@@>> result = format_aprintf_pack(&p, NULL);
@@>> // `return' is an malloc()'d string "Hello World"
@@>> return result;
@@WARNING: Note that `format_aprintf_pack(3)' is able to return `NULL' as well,
@@         but  will  finalize  the  given   aprintf  printer  an  all   cases.
@@NOTE:    The caller must destroy the returned string by passing it to `free(3)'
@@@param: pstrlen: When non-NULL, store the length of the constructed string here
@@                 Note that this is the actual length if the constructed string,
@@                 but may differ from `strlen(return)' when NUL characters  were
@@                 printed to the aprintf-printer at one point.
@@                 (e.g. `format_aprintf_printer(&my_printer, "\0", 1)')
[[wunused, ATTR_MALL_DEFAULT_ALIGNED, ATTR_MALLOC]]
[[decl_prefix(struct format_aprintf_data;), decl_include("<hybrid/typecore.h>")]]
[[impl_include("<hybrid/__assert.h>"), impl_prefix(DEFINE_FORMAT_APRINTF_DATA)]]
char *format_aprintf_pack([[inout]] struct format_aprintf_data *__restrict self,
                          [[out_opt]] $size_t *pstrlen) {
	/* Free unused buffer memory. */
	char *result;
	if (self->@ap_avail@ != 0) {
@@pp_if $has_function(realloc)@@
		char *newbuf;
		newbuf = (char *)realloc(self->@ap_base@,
		                         (self->@ap_used@ + 1) *
		                         sizeof(char));
		if likely(newbuf)
			self->@ap_base@ = newbuf;
@@pp_endif@@
	} else {
		if unlikely(!self->@ap_used@) {
			/* Special case: Nothing was printed. */
			__hybrid_assert(!self->@ap_base@);
@@pp_if $has_function(malloc)@@
			self->@ap_base@ = (char *)malloc(1 * sizeof(char));
			if unlikely(!self->@ap_base@)
				return NULL;
@@pp_elif $has_function(realloc)@@
			self->@ap_base@ = (char *)realloc(NULL, 1 * sizeof(char));
			if unlikely(!self->@ap_base@)
				return NULL;
@@pp_else@@
			return NULL;
@@pp_endif@@
		}
	}
	result = self->@ap_base@;
	__hybrid_assert(result);
	result[self->@ap_used@] = '\0'; /* NUL-terminate */
	if (pstrlen)
		*pstrlen = self->@ap_used@;
@@pp_if !defined(NDEBUG) && !defined(NDEBUG_FINI)@@
@@pp_if __SIZEOF_POINTER__ == 4@@
	self->@ap_base@  = (char *)__UINT32_C(0xcccccccc);
	self->@ap_avail@ = __UINT32_C(0xcccccccc);
	self->@ap_used@  = __UINT32_C(0xcccccccc);
@@pp_elif __SIZEOF_POINTER__ == 8@@
	self->@ap_base@  = (char *)__UINT64_C(0xcccccccccccccccc);
	self->@ap_avail@ = __UINT64_C(0xcccccccccccccccc);
	self->@ap_used@  = __UINT64_C(0xcccccccccccccccc);
@@pp_endif@@
@@pp_endif@@
	return result;
}



@@>> format_aprintf_alloc(3)
@@Allocate  a   buffer  of   `num_chars'  characters   at  the   end  of   `self'
@@The returned pointer remains valid until the next time this function is called,
@@the format_aprintf buffer `self' is finalized,  or some other function is  used
@@to append additional data to the end of `self'
@@@return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM')
[[impl_include("<hybrid/__assert.h>"), wunused]]
[[decl_prefix(struct format_aprintf_data;), decl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_FORMAT_APRINTF_DATA)]]
[[requires_function(realloc)]]
format_aprintf_alloc:([[inout]] struct format_aprintf_data *__restrict self,
                      $size_t num_chars) -> [[malloc(num_chars)]] char * {
	char *result;
	if (self->@ap_avail@ < num_chars) {
		char *newbuf;
		size_t min_alloc = self->@ap_used@ + num_chars;
		size_t new_alloc = self->@ap_used@ + self->@ap_avail@;
		if (!new_alloc)
			new_alloc = 8;
		while (new_alloc < min_alloc)
			new_alloc *= 2;
		newbuf = (char *)realloc(self->@ap_base@, (new_alloc + 1) * sizeof(char));
		if unlikely(!newbuf) {
			new_alloc = min_alloc;
			newbuf    = (char *)realloc(self->@ap_base@, (new_alloc + 1) * sizeof(char));
			if unlikely(!newbuf)
				goto err;
		}
		__hybrid_assert(new_alloc >= self->@ap_used@ + num_chars);
		self->@ap_base@  = newbuf;
		self->@ap_avail@ = new_alloc - self->@ap_used@;
	}
	result = self->@ap_base@ + self->@ap_used@;
	self->@ap_avail@ -= num_chars;
	self->@ap_used@  += num_chars;
	return result;
err:
	return NULL;
}


@@>> format_aprintf_printer(3)
@@Print data to  a dynamically  allocated heap buffer.  On error,  -1 is  returned
@@This function is intended to be used as a pformatprinter-compatible printer sink
@@@return: datalen: Success.
@@@return: -1: [errno=ENOMEM] Insufficient memory.
[[wunused, requires_function(format_aprintf_alloc)]]
[[no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
$ssize_t format_aprintf_printer([[nonnull]] /*struct format_aprintf_data **/ void *arg,
                                [[in(datalen)]] /*utf-8*/ char const *__restrict data, $size_t datalen) {
	char *buf;
	buf = format_aprintf_alloc((struct format_aprintf_data *)arg,
	                           datalen);
	if unlikely(!buf)
		goto err;
	memcpyc(buf, data, datalen, sizeof(char));
	return (ssize_t)datalen;
err:
	return -1;
}


%{

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

}
