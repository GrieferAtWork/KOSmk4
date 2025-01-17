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
#ifndef GUARD_LIBCMDLINE_DECODE_H
#define GUARD_LIBCMDLINE_DECODE_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libcmdline/decode.h>

DECL_BEGIN



/* Similar  to `cmdline_decode()', however return a heap-allocated
 * vector of the individual argument strings, which itself is then
 * terminated by a NULL-entry.
 * When `pargc' is non-NULL, store the number of arguments leading
 * up  to  (but   not  including)   the  terminating   NULL-entry.
 * Upon error, NULL is returned. */
INTDEF ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **CC
libcmdline_decode_argv(/*utf-8*/ char *__restrict cmdline,
                       size_t *pargc _os_heap_gfparg(gfp));

/* Decode and transform a given `cmdline' (which must be a \0-terminated string),
 * and    invoke   `arg_printer'   with   each   individual   argument   segment.
 * NOTE: When `arg_printer' return an error ((*arg_printer)(...) < 0), that error
 *       is  propagated and re-returned by this function. In this case, `cmdline'
 *       is left in an undefined state.
 * This function recognizes the following commandline rules:
 *   - >\x<    can be used to escape a given character `x'
 *             This character can  be anything, and  in the leading  \-character
 *             is always removed, meaning that in order to include a \-character
 *             in the actual argument vector, \\ must be written
 *   - >a b<   Any sort of space characters (s.a. `unicode_isspace()') is recognized
 *             as a suitable separator between arguments.
 *             Multiple consecutive space characters are merged into a single one.
 *   - >"a b"< Write text in  space-escaped mode.  - In this  mode, space  characters
 *             do not mark separate arguments. Additionally, the leading and trailing
 *             "-characters are removed from the generated arguments
 *   - >'a b'< Same  as "a b", but with this, you can do >"How's it going"< or
 *             >'I said "Hello"'< instead of having to use >'How\'s it going'<
 *             and >"I said \"Hello\""<
 *   - >""<    Special case: When  >""< or  >''< is encountered,  but is  surrounded
 *             by whitespace, or the start/end of the commandline, an empty argument
 *             will be emit (see examples below)
 * Examples:
 *     >a b c<                  { "a", "b", "c" }
 *     >ls "New Folder"<        { "ls", "New Folder" }
 *     >ls New\ Folder<         { "ls", "New Folder" }
 *     >ls "" foo<              { "ls", "", "foo" }     // Empty argument!
 */
INTDEF NONNULL((1, 2)) ssize_t CC
libcmdline_decode(/*utf-8*/ char *__restrict cmdline,
                  pformatprinter arg_printer,
                  void *arg_printer_arg);

/* Split a given commandline into tightly-packed, NUL-terminated
 * strings,   and   return   the   total   number   of  strings.
 * NOTE:  Obviously, this function will modify `cmdline'
 * >> char *iter, *my_cmdline = get_cmdline();
 * >> size_t i, argc = cmdline_split(my_cmdline, NULL);
 * >> for (iter = my_cmdline, i = 0; i < argc; ++i, iter = strend(iter) + 1) {
 * >>     printf("argv[%" PRIuSIZ "] = %q\n", i, iter);
 * >> }
 * @param: pendptr: When non-NULL, store a pointer to one byte past the end of the last argument
 * @return: * :     The total number of individual argument strings. */
INTDEF NONNULL((1)) size_t CC
libcmdline_split(/*utf-8*/ char *__restrict cmdline, char **pendptr);



DECL_END

#endif /* !GUARD_LIBCMDLINE_DECODE_H */
