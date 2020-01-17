/* HASH CRC-32:0xf0fcaf32 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_FORMAT_PRINTER_H
#define GUARD_LIBC_USER_FORMAT_PRINTER_H 1

#include "../api.h"
#include "../auto/format-printer.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <format-printer.h>

DECL_BEGIN

/* Pack and finalize a given aprintf format printer
 * Together with `format_aprintf_printer()', the aprintf
 * format printer sub-system should be used as follows:
 * >> char *result; ssize_t error;
 * >> struct format_aprintf_data p = FORMAT_APRINTF_DATA_INIT;
 * >> error = format_printf(&format_aprintf_printer, &p, "%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_aprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_aprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_aprintf_pack()' is able to return `NULL' as well,
 *          but will finalize the given aprintf printer an all cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `strlen(return)' when NUL characters were
 *                  printed to the aprintf-printer at one point.
 *                  (e.g. `format_aprintf_printer(&my_printer, "\0", 1)') */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_format_aprintf_pack)(struct format_aprintf_data *__restrict self, size_t *pstrlen);
/* Allocate a buffer of `num_chars' characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) ATTR_ALLOC_SIZE((2)) char *NOTHROW_NCX(LIBCCALL libc_format_aprintf_alloc)(struct format_aprintf_data *__restrict self, size_t num_chars);
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned
 * This function is intended to be used as a pformatprinter-compatibile printer sink */
INTDEF WUNUSED NONNULL((1, 2)) ssize_t NOTHROW_NCX(LIBCCALL libc_format_aprintf_printer)(/*struct format_aprintf_data **/ void *arg, /*utf-8*/ char const *__restrict data, size_t datalen);

DECL_END

#endif /* !GUARD_LIBC_USER_FORMAT_PRINTER_H */
