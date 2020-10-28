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
#ifndef GUARD_MODDBX_INCLUDE_DW_H
#define GUARD_MODDBX_INCLUDE_DW_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/types.h>

#include <kos/exec/module.h>

#include <libdebuginfo/debug_info.h>

/**/
#include "error.h"

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN

struct debugmodule {
	struct debugmodule   **dm_pself;    /* [1..1][1..1] Self-pointer */
	struct debugmodule    *dm_next;     /* [0..1] Next module. */
#if MODULE_TYPE_COUNT >= 2
	uintptr_half_t         dm_refcnt;   /* Reference counter. */
	uintptr_half_t         dm_modtyp;   /* Module type (one of `MODULE_TYPE_*'). */
#else /* MODULE_TYPE_COUNT >= 2 */
	uintptr_t              dm_refcnt;   /* Reference counter. */
#endif /* MODULE_TYPE_COUNT < 2 */
	REF module_t          *dm_module;   /* Module handle. */
	di_debug_sections_t    dm_sections; /* Debug section mappings. */
	di_debug_dl_sections_t dm_sectrefs; /* Debug section references. */
};

/* Destroy the given debug-module. */
FUNDEF NONNULL((1)) void NOTHROW(FCALL debugmodule_destroy)(struct debugmodule *__restrict self);
FUNDEF NONNULL((1)) void NOTHROW(FCALL debugmodule_fini)(struct debugmodule *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct debugmodule, dm_refcnt, debugmodule_destroy)

/* [0..1] Linked list of loaded debug-module objects (cleared during
 *        debugger reset; elements are lazily removed as they are
 *        destroyed) */
DATDEF struct debugmodule *debugmodule_list;

/* Lookup and return a reference to the debug-module descriptor for `mod'
 * @return: * :   A reference to the debug-module descriptor.
 * @return: NULL: Insufficient memory. */
FUNDEF WUNUSED NONNULL((1)) REF struct debugmodule *
NOTHROW(FCALL debugmodule_get)(module_t *__restrict mod module_type__param(modtype));
FUNDEF WUNUSED REF struct debugmodule *
NOTHROW(FCALL debugmodule_get_from_pc)(uintptr_t abs_pc);

struct dw_debugloc {
	REF struct debugmodule *ddl_module; /* [1..1] Debug module. */
	byte_t const           *ddl_di_hdr; /* [1..1] Debug information header (in .debug_info) (s.a. `di_debuginfo_cu_parser_t::dup_cu_info_hdr') */
	byte_t const           *ddl_di_pos; /* [1..1] Debug information data (in .debug_info) (s.a. `di_debuginfo_cu_parser_t::dup_cu_info_pos') */
};
#define dw_debugloc_fini(self) decref((self)->ddl_module)


/* Initialize a parser from the given debug location. */
FUNDEF NONNULL((1, 2, 3)) dbx_errno_t
NOTHROW(FCALL dw_debugloc_load)(struct dw_debugloc const *__restrict loc,
                                di_debuginfo_cu_parser_t *__restrict parser,
                                di_debuginfo_cu_abbrev_t *__restrict abbrev);

/* Initialize the given `parser' for the compilation unit at `module_relative_pc'
 * If this fails, then this function returns `DBX_ENOENT'. Upon success, `parser'
 * will point at the `DW_TAG_compile_unit' component that was loaded into `cu',
 * and the caller should remember `parser->dup_child_depth', and make use of
 * `debuginfo_cu_parser_next()' to advance & load child elements of the compilation unit.
 * @return: DBX_EOK:    Successfully initialized the parser/abbrev.
 * @return: DBX_ENOENT: Failed to initialize the parser/abbrev. */
FUNDEF NONNULL((1, 2, 3, 4)) dbx_errno_t
NOTHROW(KCALL debugmodule_loadcu_ex)(struct debugmodule const *__restrict self,
                                     /*out*/ di_debuginfo_cu_parser_t *__restrict parser,
                                     /*out*/ di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                     /*out*/ di_debuginfo_compile_unit_t *__restrict cu,
                                     /*in*/ uintptr_t module_relative_pc);

/* Same as `debugmodule_loadcu_ex()', but use the current program
 * counter register, as selected by `dbg_getpcreg(DBG_REGLEVEL_VIEW)',
 * and return a reference to the associated module.
 * @return: * :   A reference to the associated module.
 * @return: NULL: Insufficient memory, or no module found. */
FUNDEF WUNUSED NONNULL((1, 2, 3)) REF struct debugmodule *
NOTHROW(KCALL debugmodule_loadcu)(/*out*/ di_debuginfo_cu_parser_t *__restrict parser,
                                  /*out*/ di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                  /*out*/ di_debuginfo_compile_unit_t *__restrict cu,
                                  /*out_opt*/ uintptr_t *pmodule_relative_pc);


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_DW_H */
