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
#ifndef GUARD_LIBDEBUGINFO_DWARF_H
#define GUARD_LIBDEBUGINFO_DWARF_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <int128.h>

#include <libdebuginfo/dwarf.h>

DECL_BEGIN

/* Similar to the functions from `libunwind(3)', but decode into a 64-bit integer! */
INTDEF ATTR_RETNONNULL NONNULL((2)) NCX byte_t const *
NOTHROW_NCX(CC libdi_dwarf_decode_sleb128_64)(NCX byte_t const *reader,
                                              int64_t *__restrict p_result);
INTDEF ATTR_RETNONNULL NONNULL((2)) NCX byte_t const *
NOTHROW_NCX(CC libdi_dwarf_decode_uleb128_64)(NCX byte_t const *reader,
                                              uint64_t *__restrict p_result);

/* Similar to the functions from `libunwind(3)', but these actually decode into a 128-bit integer! */
INTDEF ATTR_RETNONNULL NONNULL((2)) NCX byte_t const *
NOTHROW_NCX(CC libdi_dwarf_decode_sleb128_128)(NCX byte_t const *reader,
                                               int128_t *__restrict p_result);
INTDEF ATTR_RETNONNULL NONNULL((2)) NCX byte_t const *
NOTHROW_NCX(CC libdi_dwarf_decode_uleb128_128)(NCX byte_t const *reader,
                                               uint128_t *__restrict p_result);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DWARF_H */
