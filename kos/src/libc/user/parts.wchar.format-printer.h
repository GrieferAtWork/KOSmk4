/* HASH CRC-32:0xb84ee81f */
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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_FORMAT_PRINTER_H
#define GUARD_LIBC_USER_PARTS_WCHAR_FORMAT_PRINTER_H 1

#include "../api.h"
#include "../auto/parts.wchar.format-printer.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/format-printer.h>

DECL_BEGIN

/* Pack and finalize a given aprintf format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format printer sub-system should be used as follows:
 * >> char *result; ssize_t error;
 * >> struct format_aprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but will finalize the given aprintf printer an all cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *NOTHROW_NCX(LIBCCALL libc_format_waprintf_pack)(struct format_c32aprintf_data *__restrict self, size_t *pstrlen);
/* Pack and finalize a given aprintf format printer
 * Together with `format_waprintf_printer()', the aprintf
 * format printer sub-system should be used as follows:
 * >> char *result; ssize_t error;
 * >> struct format_aprintf_data p = FORMAT_WAPRINTF_DATA_INIT;
 * >> error = format_wprintf(&format_waprintf_printer, &p, L"%s %s", "Hello", "World");
 * >> if unlikely(error < 0) {
 * >>     format_waprintf_data_fini(&p);
 * >>     return NULL;
 * >> }
 * >> result = format_waprintf_pack(&p, NULL);
 * >> return result;
 * WARNING: Note that `format_waprintf_pack()' is able to return `NULL' as well,
 *          but will finalize the given aprintf printer an all cases.
 * NOTE:    The caller must destroy the returned string by passing it to `free()'
 * @param: pstrlen: When non-NULL, store the length of the constructed string here
 *                  Note that this is the actual length if the constructed string,
 *                  but may differ from `wcslen(return)' when NUL characters were
 *                  printed to the waprintf-printer at one point.
 *                  (e.g. `format_waprintf_printer(&my_printer, L"\0", 1)') */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *NOTHROW_NCX(LIBDCALL libd_format_waprintf_pack)(struct format_c16aprintf_data *__restrict self, size_t *pstrlen);
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned */
INTDEF WUNUSED NONNULL((1, 2)) ssize_t NOTHROW_NCX(LIBCCALL libc_format_waprintf_printer)(/*struct format_waprintf_data **/void *arg, char32_t const *__restrict data, size_t datalen);
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned */
INTDEF WUNUSED NONNULL((1, 2)) ssize_t NOTHROW_NCX(LIBDCALL libd_format_waprintf_printer)(/*struct format_waprintf_data **/void *arg, char16_t const *__restrict data, size_t datalen);

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_FORMAT_PRINTER_H */
