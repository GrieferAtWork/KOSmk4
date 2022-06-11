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
#ifndef GUARD_MODDBX_INCLUDE_OBNOTE_H
#define GUARD_MODDBX_INCLUDE_OBNOTE_H 1

/* DeBug eXtensions: OBjectNOTEs.
 *
 * Using these functions, you can print extended, yet still compact information
 * about  certain   objects,  given   the  (struct-)name   of  those   objects.
 *
 * For example: "task" will give extended information for `struct task'
 *
 * These functions are used by `ctype_printvalue()' when printing pointers
 * to  kernel objects, and the `CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER' flag
 * hasn't been given.
 */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

#include <kernel/types.h>

#include <bits/crt/format-printer.h>

DECL_BEGIN

/* Status codes for `obnote_print::pstatus' */
#define OBNOTE_PRINT_STATUS_SUCCESS 0 /* Success */
#define OBNOTE_PRINT_STATUS_BADNAME 1 /* Unrecognized `name' */
#define OBNOTE_PRINT_STATUS_BADOBJ  2 /* Corrupt/invalid/bad object */

/* Callback for object note printers.
 * @param: pstatus: Already set to `OBNOTE_PRINT_STATUS_SUCCESS'  before
 *                  this function is called. May be changed to something
 *                  like `OBNOTE_PRINT_STATUS_BADOBJ'  to indicate  that
 *                  the given `pointer'  isn't a valid  instance of  the
 *                  expected object.
 * @return: * :     The usual pformatprinter return value. */
typedef NONNULL_T((1, 4)) ssize_t
(KCALL *obnote_callback_t)(__pformatprinter printer, void *arg,
                           CHECKED void const *pointer,
                           unsigned int *__restrict pstatus);

struct obnote_entry {
	char const       *one_name; /* [1..1] Object name. */
	obnote_callback_t one_cb;   /* [1..1] Note printer callback. */
};

/* Print extended information (if available)
 * that   related   to  the   given  `name'.
 * @param: pstatus: [out] Set to one of `OBNOTE_PRINT_STATUS_*'.
 * @return: * :     The usual pformatprinter return value. */
FUNDEF NONNULL((1, 4, 5)) ssize_t
NOTHROW(KCALL obnote_print)(__pformatprinter printer, void *arg,
                            CHECKED void const *pointer,
                            char const *__restrict name,
                            unsigned int *__restrict pstatus);

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_OBNOTE_H */
