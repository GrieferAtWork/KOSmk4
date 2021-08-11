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
#ifndef GUARD_LIBICONV_CONVERT_H
#define GUARD_LIBICONV_CONVERT_H 1

#include "api.h"
/**/

#include <format-printer.h>
#include <kos/types.h>

DECL_BEGIN

/************************************************************************/
/* ASCII                                                                */
/************************************************************************/
INTDEF NONNULL((1, 2)) ssize_t
NOTHROW_NCX(FORMATPRINTER_CC libiconv_ascii_decode_errchk)(struct iconv_decode *__restrict self,
                                                           /*ASCII*/ char const *__restrict data,
                                                           size_t size);


/************************************************************************/
/* UTF-16                                                               */
/************************************************************************/
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf16le_encode)(struct iconv_encode *__restrict self, /*utf-8*/ char const *__restrict data, size_t size);
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf16be_encode)(struct iconv_encode *__restrict self, /*utf-8*/ char const *__restrict data, size_t size);
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf16le_decode)(struct iconv_decode *__restrict self, /*utf-16*/ void const *__restrict data, size_t size);
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf16be_decode)(struct iconv_decode *__restrict self, /*utf-16*/ void const *__restrict data, size_t size);


/************************************************************************/
/* UTF-32                                                               */
/************************************************************************/
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf32le_encode)(struct iconv_encode *__restrict self, /*utf-8*/ char const *__restrict data, size_t size);
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf32be_encode)(struct iconv_encode *__restrict self, /*utf-8*/ char const *__restrict data, size_t size);
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf32le_decode)(struct iconv_decode *__restrict self, /*utf-32*/ void const *__restrict data, size_t size);
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_utf32be_decode)(struct iconv_decode *__restrict self, /*utf-32*/ void const *__restrict data, size_t size);


/************************************************************************/
/* Generic code-page                                                    */
/************************************************************************/
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_cp_encode)(struct iconv_encode *__restrict self, /*utf-8*/ char const *__restrict data, size_t size);
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_NCX(FORMATPRINTER_CC libiconv_cp_decode)(struct iconv_decode *__restrict self, /*cp???*/ char const *__restrict data, size_t size);


DECL_END

#endif /* !GUARD_LIBICONV_CONVERT_H */
