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
#ifndef _LIBUNWIND_DWARF_H
#define _LIBUNWIND_DWARF_H 1

#include "api.h"
/**/

#include <bits/types.h>
#include <kos/anno.h>

/* Absolute pointer encoding formats (s.a. `DW_EH_PE_OFF()') */
#define DW_EH_PE_absptr   0x00
#define DW_EH_PE_uleb128  0x01
#define DW_EH_PE_udata2   0x02
#define DW_EH_PE_udata4   0x03
#define DW_EH_PE_udata8   0x04
#define DW_EH_PE_signed   0x08
#define DW_EH_PE_sleb128  0x09
#define DW_EH_PE_sdata2   0x0a
#define DW_EH_PE_sdata4   0x0b
#define DW_EH_PE_sdata8   0x0c
/* Relative pointer encoding formats (s.a. `DW_EH_PE_BASE()') */
#define DW_EH_PE_pcrel    0x10
#define DW_EH_PE_textrel  0x20
#define DW_EH_PE_datarel  0x30
#define DW_EH_PE_funcrel  0x40
#define DW_EH_PE_aligned  0x50
/* Special */
#define DW_EH_PE_omit     0xff /* Omit the pointer. */
#define DW_EH_PE_indirect 0x80 /* FLAG */

/* Extract information from a DWARF pointer encoding format field. */
#define DW_EH_PE_OFFMASK  0x0f /* Mask for offset format */
#define DW_EH_PE_BASEMASK 0x70 /* Mask for base format */
#define DW_EH_PE_OFF(x)  ((x) & DW_EH_PE_OFFMASK)
#define DW_EH_PE_BASE(x) ((x) & DW_EH_PE_BASEMASK)


#ifdef __CC__
__DECL_BEGIN

typedef __intptr_t  dwarf_sleb128_t;
typedef __uintptr_t dwarf_uleb128_t;

/* Decode a signed/unsigned LEB128 integer and advance `*preader' */
typedef __ATTR_NONNULL_T((1)) dwarf_sleb128_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PDWARF_DECODE_SLEB128)(__CHECKED __byte_t const **__restrict preader);
typedef __ATTR_NONNULL_T((1)) dwarf_uleb128_t
__NOTHROW_NCX_T(LIBUNWIND_CC *PDWARF_DECODE_ULEB128)(__CHECKED __byte_t const **__restrict preader);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1)) dwarf_sleb128_t
__NOTHROW_NCX(LIBUNWIND_CC dwarf_decode_sleb128)(__CHECKED __byte_t const **__restrict preader);
LIBUNWIND_DECL __ATTR_NONNULL((1)) dwarf_uleb128_t
__NOTHROW_NCX(LIBUNWIND_CC dwarf_decode_uleb128)(__CHECKED __byte_t const **__restrict preader);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

struct unwind_bases;

typedef __ATTR_NONNULL_T((1)) __CHECKED __byte_t *
__NOTHROW_NCX_T(LIBUNWIND_CC *PDWARF_DECODE_POINTER)(__CHECKED __byte_t const **__restrict preader,
                                                     __uint8_t encoding, __uint8_t addrsize,
                                                     struct unwind_bases *dw_bases);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1)) __CHECKED __byte_t *
__NOTHROW_NCX(LIBUNWIND_CC dwarf_decode_pointer)(__CHECKED __byte_t const **__restrict preader,
                                                 __uint8_t encoding, __uint8_t addrsize,
                                                 struct unwind_bases *dw_bases);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBUNWIND_DWARF_H */
