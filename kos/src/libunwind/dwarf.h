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
#ifndef GUARD_LIBUNWIND_DWARF_H
#define GUARD_LIBUNWIND_DWARF_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <libunwind/dwarf.h>

DECL_BEGIN

/* Decode a signed/unsigned LEB128 integer and advance `*preader' */
INTDEF NONNULL((1)) dwarf_sleb128_t
NOTHROW_NCX(CC libuw_dwarf_decode_sleb128)(CHECKED byte_t const **__restrict preader);
INTDEF NONNULL((1)) dwarf_uleb128_t
NOTHROW_NCX(CC libuw_dwarf_decode_uleb128)(CHECKED byte_t const **__restrict preader);

INTDEF NONNULL((1)) CHECKED byte_t *
NOTHROW_NCX(CC libuw_dwarf_decode_pointer)(CHECKED byte_t const **__restrict preader,
                                           uint8_t encoding, uint8_t addrsize,
                                           struct unwind_bases *dw_bases);

#undef dwarf_decode_sleb128
#undef dwarf_decode_uleb128
#undef dwarf_decode_pointer
#define dwarf_decode_sleb128 libuw_dwarf_decode_sleb128
#define dwarf_decode_uleb128 libuw_dwarf_decode_uleb128
#define dwarf_decode_pointer libuw_dwarf_decode_pointer

DECL_END

#endif /* !GUARD_LIBUNWIND_DWARF_H */
