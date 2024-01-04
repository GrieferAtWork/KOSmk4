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
#ifndef GUARD_MODDBX_INCLUDE_CPRINTER_H
#define GUARD_MODDBX_INCLUDE_CPRINTER_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <bits/crt/format-printer.h>

#include <libdebuginfo/debug_info.h> /* debuginfo_print_format_t */

/**/
#include "error.h"
#include "ctype.h"

DECL_BEGIN

struct cprinter {
	__pformatprinter         cp_printer;    /* [1..1] Pointer */
	void                    *cp_arg;        /* [?..?] Pointer cookie */
	debuginfo_print_format_t cp_format;     /* [0..1] Format-pointer */
	void                    *cp_format_arg; /* [?..?] Format-pointer cookie */
};

/* Print the correct representation of the given type, including
 * an optional, contained variable name that is also printed  at
 * the proper location. */
FUNDEF NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL ctyperef_printname)(struct ctyperef const *__restrict self,
                                         struct cprinter const *__restrict printer,
                                         NCX char const *varname DFL(__NULLPTR),
                                         size_t varname_len DFL(0));
FUNDEF NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printname)(struct ctype const *__restrict self,
                                      struct cprinter const *__restrict printer,
                                      NCX char const *varname DFL(__NULLPTR),
                                      size_t varname_len DFL(0));


/* Print a human-readable  representation of  the contents of  a given  data-buffer,
 * based on the C-typing of that buffer, which was likely extracted from debug info.
 * @param: self:             The typing of `buf'
 * @param: printer:          The printer used to output data.
 * @param: buf:              The data buffer that should be printed.
 *                           This should point to a block of `ctype_sizeof(self)' bytes.
 * @param: flags:            Printing flags (set of `CTYPE_PRINTVALUE_FLAG_*')
 * @param: firstline_indent: # of SPC (' ') characters already printed on the current line.
 * @param: newline_indent:   # of SPC (' ') characters to print after every \n-character.
 *                           Ignored  when   `CTYPE_PRINTVALUE_FLAG_ONELINE'  is   given.
 * @param: newline_tab:      Amount by which to increase `newline_indent' after a line-
 *                           feed  following  an  open-brace '{'  or  open-bracket '['.
 * @param: maxlinelen:       The max line  length that  should not be  exceeded by  when
 *                           placing   short  struct  initializers  on  the  same  line.
 *                           Ignored when `CTYPE_PRINTVALUE_FLAG_NOSHORTLINES' is given.
 *                           If insufficient space is available, do this:
 *                           >> {foo: {x: 10, y: 20}}
 *                           or this:
 *                           >> {
 *                           >>     foo: {x: 10, y: 20}
 *                           >> }
 *                           Instead of this:
 *                           >> {
 *                           >>     foo: {
 *                           >>         x: 10,
 *                           >>         y: 20
 *                           >>     }
 *                           >> }
 *                           Note that this limit isn't a guaranty, but only a hint. */
FUNDEF NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printvalue)(struct ctyperef const *__restrict self,
                                       struct cprinter const *__restrict printer,
                                       NCX void const *buf, unsigned int flags,
                                       size_t firstline_indent, size_t newline_indent,
                                       size_t newline_tab, size_t maxlinelen);
#define CTYPE_PRINTVALUE_FLAG_NORMAL             0x0000 /* Normal flags. */
#define CTYPE_PRINTVALUE_FLAG_ONELINE            0x0001 /* Print everything on a single line. (`maxlinelen' is ignored) */
#define CTYPE_PRINTVALUE_FLAG_NOSHORTLINES       0x0002 /* Don't put short struct initializers on a single line. (`maxlinelen' is ignored) */
#define CTYPE_PRINTVALUE_FLAG_NOSTRUCTFIELDS     0x0004 /* Don't include struct fields. (`{x: 10, y: 20}' becomes `{10, 20}') */
#define CTYPE_PRINTVALUE_FLAG_NOOMITSHORTFIELDS  0x0008 /* Don't allow field names to be omitted for short structs (this is
                                                         * normally  done when the struct has <=  2 fields in total, and an
                                                         * attempt is made to put it on  a single line, but the line  would
                                                         * become too long) */
#define CTYPE_PRINTVALUE_FLAG_CSTYLESTRUCTFIELDS 0x0010 /* Print struct field names as `.name = 42', rather than `name: 42'. */
#define CTYPE_PRINTVALUE_FLAG_NOSTRINGPOINTER    0x0020 /* Don't print `char *' or `char const *' types (repeat for `char16_t'
                                                         * and  `char32_t') as strings,  but treat them  as any other pointer.
                                                         * This does not affect the printing of arrays of such elements. */
#define CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER     0x0040 /* Don't  try to give names to pointers, but print pointers as-is
                                                         * in a manner that is supported by the C standard. Normally, the
                                                         * following types of pointers get assigned special names:
                                                         *   #1 The 0-pointer is printed as `NULL'
                                                         *   #2 Text/data pointers  (pointers into  static memory  segments)
                                                         *      are attempted to be reversed  by looking at debug info,  and
                                                         *      will  be printed as `&base_symbol' or `&base_symbol+offset',
                                                         *      when `offset' can be cleanly divided by the pointed-to type,
                                                         *      or `(void *)&base_symbol+offset' when not.
                                                         *   #3 User-space  pointers   into   disk-to-file   memory   mappings
                                                         *      excluding anonymous  memory,  aka  `MAP_ANON'  or  `/dev/null'
                                                         *      are printed as `0x12345678 ("/path/to/file"+offset_into_file)'
                                                         *      But note that this isn't done  if case #2 managed to  identify
                                                         *      the associated file mapping as an executable file!
                                                         *   #4 Kernel-space pointers that point into heap segments are
                                                         *      printed as: `0x12345678 (heap)'
                                                         * But also note `CTYPE_PRINTVALUE_FLAG_NOSTRINGPOINTER', meaning
                                                         * that  this flag is only used if the pointed-to location wasn't
                                                         * already interpreted as a string. */
#define CTYPE_PRINTVALUE_FLAG_NORECURSION        0x0080 /* Don't print  fields of  recursive structs.  Only print  fields
                                                         * of a (potential) initial struct as given as `self', but if one
                                                         * of those fields is another structure, print it as `{...}' */
#define CTYPE_PRINTVALUE_FLAG_NOARRAYRANGE       0x0100 /* Don't print array range `[lo ... hi] = value' expressions. */
#define CTYPE_PRINTVALUE_FLAG_NOSPECSTRUCT       0x0200 /* Don't print special struct types (like `int128_t') by using a custom representation */
#define CTYPE_PRINTVALUE_FLAG_INTSUFFIX          0x4000 /* Include integer type suffixes (`u', `ul', `ll', etc...) */
#define CTYPE_PRINTVALUE_FLAG_FORCEHEX           0x8000 /* Always  use  hex  for  everything.  When  not  given,  small integer
                                                         * values are  instead  printed  in decimal,  and  larger  numbers  are
                                                         * printed in hex, unless at least 3/5thof their decimal representation
                                                         * consists of the same digit (i.e. 100001, but not 123456) */




DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_CPRINTER_H */
