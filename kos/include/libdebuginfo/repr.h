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
#ifndef _LIBDEBUGINFO_DEBUG_REPR_H
#define _LIBDEBUGINFO_DEBUG_REPR_H 1

#include "api.h"
#include "dwarf.h"
#include <bits/types.h>
#include <bits/format-printer.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __KERNEL__
/* Return the name of a given constant, or NULL if the constant isn't recognized.
 *  - debug_repr_DW_TAG():   Returns the `*' portion for one of `DW_TAG_*' (i.e. excluding the `DW_TAG_' prefix)
 *  - debug_repr_DW_AT():    Returns the `*' portion for one of `DW_AT_*' (i.e. excluding the `DW_AT_' prefix)
 *  - debug_repr_DW_FORM():  Returns the `*' portion for one of `DW_FORM_*' (i.e. excluding the `DW_FORM_' prefix)
 *  - debug_repr_DW_ATE():   Returns the `*' portion for one of `DW_ATE_*' (i.e. excluding the `DW_ATE_' prefix)
 *  - debug_repr_DW_OP():    Returns the `*' portion for one of `DW_OP_*' (i.e. excluding the `DW_OP_' prefix)
 *  - debug_repr_DW_CFA():   Returns the `*' portion for one of `DW_CFA_*' (i.e. excluding the `DW_CFA_' prefix)
 *  - debug_repr_DW_EH_PE(): Returns the `*' portion for one of `DW_EH_PE_*' (i.e. excluding the `DW_EH_PE_' prefix)
 */
typedef __ATTR_CONST __ATTR_WUNUSED char const *(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_TAG)(dwarf_uleb128_t value);
typedef __ATTR_CONST __ATTR_WUNUSED char const *(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_AT)(dwarf_uleb128_t value);
typedef __ATTR_CONST __ATTR_WUNUSED char const *(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_FORM)(dwarf_uleb128_t value);
typedef __ATTR_CONST __ATTR_WUNUSED char const *(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_ATE)(dwarf_uleb128_t value);
typedef __ATTR_CONST __ATTR_WUNUSED char const *(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_OP)(__uint8_t value);
typedef __ATTR_CONST __ATTR_WUNUSED char const *(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_CFA)(__uint8_t value);
typedef __ATTR_CONST __ATTR_WUNUSED char const *(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_EH_PE)(__uint8_t value);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_TAG)(dwarf_uleb128_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_AT)(dwarf_uleb128_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_FORM)(dwarf_uleb128_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_ATE)(dwarf_uleb128_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_OP)(__uint8_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_CFA)(__uint8_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_EH_PE)(__uint8_t value);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Dump the given debug information in a human-readable format to `printer'
 * >>  {
 * >>  	void *m = dlopen(LIBDEBUGINFO_LIBRARY_NAME,RTLD_LOCAL);
 * >> #define LOAD(T,x) T x; *(void **)&x = dlsym(m,#x); assertf(x,"Error: %s",dlerror());
 * >>  	LOAD(PDEBUG_REPR_DUMP,debug_repr_dump)
 * >>  	struct dl_section *debug_info   = dllocksection(dlgetmodule("c"), ".debug_info");
 * >>  	struct dl_section *debug_abbrev = dllocksection(dlgetmodule("c"), ".debug_abbrev");
 * >>  	struct dl_section *debug_str    = dllocksection(dlgetmodule("c"), ".debug_str");
 * >>  	struct dl_section *debug_loc    = dllocksection(dlgetmodule("c"), ".debug_loc");
 * >>  	debug_repr_dump(&file_printer, stdout,
 * >>  	                (byte_t *)(debug_info ? debug_info->ds_data : NULL),
 * >>  	                (byte_t *)(debug_info ? debug_info->ds_data + debug_info->ds_size : 0),
 * >>  	                (byte_t *)(debug_abbrev ? debug_abbrev->ds_data : NULL),
 * >>  	                (byte_t *)(debug_abbrev ? debug_abbrev->ds_data + debug_abbrev->ds_size : 0),
 * >>  	                (byte_t *)(debug_loc ? debug_loc->ds_data : NULL),
 * >>  	                (byte_t *)(debug_loc ? debug_loc->ds_data + debug_loc->ds_size : 0),
 * >>  	                (byte_t *)(debug_str ? debug_str->ds_data : NULL),
 * >>  	                (byte_t *)(debug_str ? debug_str->ds_data + debug_str->ds_size : 0));
 * >>  }
*/
typedef __ATTR_NONNULL((1)) __ssize_t
(LIBDEBUGINFO_CC *PDEBUG_REPR_DUMP)(__pformatprinter printer, void *arg,
                                    __byte_t *debug_info_start, __byte_t *debug_info_end,
                                    __byte_t *debug_abbrev_start, __byte_t *debug_abbrev_end,
                                    __byte_t *debug_loc_start, __byte_t *debug_loc_end,
                                    __byte_t *debug_str_start, __byte_t *debug_str_end);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) __ssize_t
(LIBDEBUGINFO_CC debug_repr_dump)(__pformatprinter printer, void *arg,
                                  __byte_t *debug_info_start, __byte_t *debug_info_end,
                                  __byte_t *debug_abbrev_start, __byte_t *debug_abbrev_end,
                                  __byte_t *debug_loc_start, __byte_t *debug_loc_end,
                                  __byte_t *debug_str_start, __byte_t *debug_str_end);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

#endif /* __KERNEL__ */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DEBUG_REPR_H */
