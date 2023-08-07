/* HASH CRC-32:0xab37c726 */
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
#ifndef GUARD_LIBC_AUTO_FORMAT_PRINTER_H
#define GUARD_LIBC_AUTO_FORMAT_PRINTER_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <format-printer.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
INTDEF NONNULL((1)) ssize_t NOTHROW_CB(LIBDCALL libd_format_repeat)(pformatprinter printer, void *arg, char ch, size_t num_repetitions);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> format_repeat(3)
 * Repeat  `ch'  a   number  of  `num_repetitions'   times
 * The usual format-printer rules apply, and this function
 * is  allowed to  call `printer'  as often  as it chooses */
INTDEF NONNULL((1)) ssize_t NOTHROW_CB(LIBCCALL libc_format_repeat)(pformatprinter printer, void *arg, char ch, size_t num_repetitions);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_INS(3, 4) NONNULL((1)) ssize_t NOTHROW_CB(LIBDCALL libd_format_escape)(pformatprinter printer, void *arg, char const *__restrict text, size_t textlen, unsigned int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF ATTR_INS(3, 4) NONNULL((1)) ssize_t NOTHROW_CB(LIBCCALL libc_format_escape)(pformatprinter printer, void *arg, char const *__restrict text, size_t textlen, unsigned int flags);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_INS(3, 4) NONNULL((1)) ssize_t NOTHROW_CB(LIBDCALL libd_format_hexdump)(pformatprinter printer, void *arg, void const *__restrict data, size_t size, size_t linesize, unsigned int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF ATTR_INS(3, 4) NONNULL((1)) ssize_t NOTHROW_CB(LIBCCALL libc_format_hexdump)(pformatprinter printer, void *arg, void const *__restrict data, size_t size, size_t linesize, unsigned int flags);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) NONNULL((1)) ssize_t NOTHROW_CB(LIBDCALL libd_format_vprintf)(pformatprinter printer, void *arg, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF ATTR_IN(3) ATTR_LIBC_PRINTF(3, 0) NONNULL((1)) ssize_t NOTHROW_CB(LIBCCALL libc_format_vprintf)(pformatprinter printer, void *arg, char const *__restrict format, va_list args);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) NONNULL((1)) ssize_t NOTHROW_CB(VLIBDCALL libd_format_printf)(pformatprinter printer, void *arg, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF ATTR_IN(3) ATTR_LIBC_PRINTF(3, 4) NONNULL((1)) ssize_t NOTHROW_CB(VLIBCCALL libc_format_printf)(pformatprinter printer, void *arg, char const *__restrict format, ...);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_IN(4) ATTR_LIBC_SCANF(4, 0) NONNULL((1, 2)) ssize_t NOTHROW_CB(LIBDCALL libd_format_vscanf)(pformatgetc pgetc, pformatungetc pungetc, void *arg, char const *__restrict format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF ATTR_IN(4) ATTR_LIBC_SCANF(4, 0) NONNULL((1, 2)) ssize_t NOTHROW_CB(LIBCCALL libc_format_vscanf)(pformatgetc pgetc, pformatungetc pungetc, void *arg, char const *__restrict format, va_list args);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_IN(4) ATTR_LIBC_SCANF(4, 5) NONNULL((1, 2)) ssize_t NOTHROW_CB(VLIBDCALL libd_format_scanf)(pformatgetc pgetc, pformatungetc pungetc, void *arg, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
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
INTDEF ATTR_IN(4) ATTR_LIBC_SCANF(4, 5) NONNULL((1, 2)) ssize_t NOTHROW_CB(VLIBCCALL libc_format_scanf)(pformatgetc pgetc, pformatungetc pungetc, void *arg, char const *__restrict format, ...);
/* >> format_sprintf_printer(3)
 * Format-printer implementation for printing to a string buffer like `sprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
INTDEF ATTR_INS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__FORMATPRINTER_CC libc_format_sprintf_printer)(void *arg, char const *__restrict data, size_t datalen);
/* >> format_snprintf_printer(3)
 * Format-printer implementation for printing to a string buffer like `snprintf(3)' would
 * NOTES:
 *  - No trailing NUL-character is implicitly appended !!!
 *  - The number of written characters is `<orig_bufsize> - arg->sd_bufsiz'
 *  - The number  of required  characters is  `arg->sd_buffer - <orig_buf>', and  is
 *    equal to the sum of return values of all calls to `format_snprintf_printer(3)'
 *  - There is no error-case, so this function never returns a negative result */
INTDEF ATTR_INS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__FORMATPRINTER_CC libc_format_snprintf_printer)(void *arg, char const *__restrict data, size_t datalen);
/* >> format_width(3)
 * Returns the width (number of characters; not bytes) of the given unicode string
 * The  `arg'   argument   is   ignored,   and  you   may   safely   pass   `NULL' */
INTDEF ATTR_PURE ATTR_INS(2, 3) NONNULL((2)) ssize_t NOTHROW_NCX(__FORMATPRINTER_CC libc_format_width)(void *arg, char const *__restrict data, size_t datalen);
/* >> format_length(3)
 * Always re-return `datalen' and ignore all other arguments
 * Both the `arg'  and `data' arguments  are simply  ignored */
INTDEF ATTR_CONST ATTR_INS(2, 3) NONNULL((2)) ssize_t NOTHROW(__FORMATPRINTER_CC libc_format_length)(void *arg, char const *__restrict data, size_t datalen);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2) char *NOTHROW_NCX(LIBDCALL libd_format_aprintf_pack)(struct format_aprintf_data *__restrict self, size_t *pstrlen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INOUT(1) ATTR_OUT_OPT(2) char *NOTHROW_NCX(LIBCCALL libc_format_aprintf_pack)(struct format_aprintf_data *__restrict self, size_t *pstrlen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> format_aprintf_alloc(3)
 * Allocate  a   buffer  of   `num_chars'  characters   at  the   end  of   `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd_format_aprintf_alloc)(struct format_aprintf_data *__restrict self, size_t num_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> format_aprintf_alloc(3)
 * Allocate  a   buffer  of   `num_chars'  characters   at  the   end  of   `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized,  or some other function is  used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory (errno is set of `ENOMEM') */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc_format_aprintf_alloc)(struct format_aprintf_data *__restrict self, size_t num_chars);
/* >> format_aprintf_printer(3)
 * Print data to  a dynamically  allocated heap buffer.  On error,  -1 is  returned
 * This function is intended to be used as a pformatprinter-compatible printer sink
 * @return: datalen: Success.
 * @return: -1: [errno=ENOMEM] Insufficient memory. */
INTDEF WUNUSED ATTR_INS(2, 3) NONNULL((1)) ssize_t NOTHROW_NCX(__FORMATPRINTER_CC libc_format_aprintf_printer)(void *arg, char const *__restrict data, size_t datalen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FORMAT_PRINTER_H */
