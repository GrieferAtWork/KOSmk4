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
#ifndef GUARD_LIBDEBUGINFO_REPR_H
#define GUARD_LIBDEBUGINFO_REPR_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libdebuginfo/dwarf.h>
#include <libdebuginfo/repr.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Return the name of a given constant, or NULL if the constant isn't recognized.
 *  - debug_repr_DW_TAG():   Returns the `*' portion for one of `DW_TAG_*' (iow. excluding the `DW_TAG_' prefix)
 *  - debug_repr_DW_AT():    Returns the `*' portion for one of `DW_AT_*' (iow. excluding the `DW_AT_' prefix)
 *  - debug_repr_DW_FORM():  Returns the `*' portion for one of `DW_FORM_*' (iow. excluding the `DW_FORM_' prefix)
 *  - debug_repr_DW_ATE():   Returns the `*' portion for one of `DW_ATE_*' (iow. excluding the `DW_ATE_' prefix)
 *  - debug_repr_DW_OP():    Returns the `*' portion for one of `DW_OP_*' (iow. excluding the `DW_OP_' prefix)
 *  - debug_repr_DW_CFA():   Returns the `*' portion for one of `DW_CFA_*' (iow. excluding the `DW_CFA_' prefix)
 *  - debug_repr_DW_EH_PE(): Returns the `*' portion for one of `DW_EH_PE_*' (iow. excluding the `DW_EH_PE_' prefix)
 */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(CC libdi_debug_repr_DW_TAG)(dwarf_uleb128_t value);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(CC libdi_debug_repr_DW_AT)(dwarf_uleb128_t value);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(CC libdi_debug_repr_DW_FORM)(dwarf_uleb128_t value);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(CC libdi_debug_repr_DW_ATE)(dwarf_uleb128_t value);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(CC libdi_debug_repr_DW_OP)(uint8_t value);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(CC libdi_debug_repr_DW_CFA)(uint8_t value);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(CC libdi_debug_repr_DW_EH_PE)(uint8_t value);

/* Dump the given debug information in a human-readable format to `printer'
 * >>  {
 * >>   void *m = dlopen(LIBDEBUGINFO_LIBRARY_NAME,RTLD_LOCAL);
 * >> #define LOAD(T,x) T x; *(void **)&x = dlsym(m,#x); assertf(x,"Error: %s",dlerror());
 * >>   LOAD(PDEBUG_REPR_DUMP,debug_repr_dump)
 * >>   struct dl_section *debug_info   = dllocksection(dlgetmodule("c"), ".debug_info");
 * >>   struct dl_section *debug_abbrev = dllocksection(dlgetmodule("c"), ".debug_abbrev");
 * >>   struct dl_section *debug_loc    = dllocksection(dlgetmodule("c"), ".debug_loc");
 * >>   struct dl_section *debug_str    = dllocksection(dlgetmodule("c"), ".debug_str");
 * >>   debug_repr_dump(&file_printer, stdout,
 * >>                   (byte_t *)(debug_info ? debug_info->ds_data : NULL),
 * >>                   (byte_t *)(debug_info ? debug_info->ds_data + debug_info->ds_size : 0),
 * >>                   (byte_t *)(debug_abbrev ? debug_abbrev->ds_data : NULL),
 * >>                   (byte_t *)(debug_abbrev ? debug_abbrev->ds_data + debug_abbrev->ds_size : 0),
 * >>                   (byte_t *)(debug_str ? debug_str->ds_data : NULL),
 * >>                   (byte_t *)(debug_str ? debug_str->ds_data + debug_str->ds_size : 0),
 * >>                   (byte_t *)(debug_loc ? debug_loc->ds_data : NULL),
 * >>                   (byte_t *)(debug_loc ? debug_loc->ds_data + debug_loc->ds_size : 0));
 * >>  }
*/
INTDEF NONNULL((1)) ssize_t CC
libdi_debug_repr_dump(pformatprinter printer, void *arg,
                      byte_t *debug_info_start, byte_t *debug_info_end,
                      byte_t *debug_abbrev_start, byte_t *debug_abbrev_end,
                      byte_t *debug_loc_start, byte_t *debug_loc_end,
                      byte_t *debug_str_start, byte_t *debug_str_end);

#endif /* __KERNEL__ */


DECL_END

#endif /* !GUARD_LIBDEBUGINFO_REPR_H */
