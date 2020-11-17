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
#ifdef CONFIG_HAVE_DEBUGGER

#include <kernel/types.h>

#include <kos/exec/module.h>

#include <libdebuginfo/debug_info.h>

/**/
#include "error.h"

DECL_BEGIN

#define DW_MODULE_SYMBOL_KIND_NONE 0 /* Module does not contain this symbol. */
#define DW_MODULE_SYMBOL_KIND_TYPE 1 /* CFI Type. */
#define DW_MODULE_SYMBOL_KIND_EXPR 2 /* CFI Variable/register expression */

struct dw_module_symbol_type {
	byte_t const *t_cuaddr;   /* [1..1] Pointer into `.debug_info' to the start of the CU that defines this type.
	                           *        With this, you can initialize a debug-info parser/abbrev table through use
	                           *        of: `r = t_cuaddr; debuginfo_cu_parser_loadunit(&r, ...);' */
	byte_t const *t_typeinfo; /* [1..1] Type information. (s.a. `ctype_fromdw():type_debug_info') */
};

struct dw_module_symbol_expr {
	struct dw_module_symbol_type e_type; /* Expression type. */
	void                        *e_addr; /* Absolute address of this symbol. */
};

struct dw_module_cu {
};

struct dw_module_symbol {
	char const              *dms_name;  /* [1..1] Symbol name (points into `.debug_str') */
	uintptr_t                dms_hash;  /* Symbol name hash. */
	uintptr_t                dms_kind;  /* Symbol kind (one of `CSYMBOL_KIND_*') */
	union {
		struct dw_module_symbol_type dms_ctype; /* [valid_if(DW_MODULE_SYMBOL_KIND_TYPE)] C-Type. */
		struct dw_module_symbol_expr dms_cexpr; /* [valid_if(DW_MODULE_SYMBOL_KIND_EXPR)] C-expression. */
	};
};

struct dw_module_symcache {
	/* TODO: Cache in a linear, sorted vector, such that a symbol can be found
	 *       by doing BSEARCH, and startswith can be realized by finding the
	 *       first elements that starts with a given string, and enumerating
	 *       all until one is found that no longer starts with it. */
};


struct dw_module {
	struct dw_module        **dm_pself;    /* [1..1][1..1] Self-pointer */
	struct dw_module         *dm_next;     /* [0..1] Next module. */
	REF struct dw_module     *dm_cache;    /* [0..1] Next cached module. */
#if MODULE_TYPE_COUNT >= 2
	uintptr_half_t            dm_refcnt;   /* Reference counter. */
	uintptr_half_t            dm_modtyp;   /* Module type (one of `MODULE_TYPE_*'). */
#else /* MODULE_TYPE_COUNT >= 2 */
	uintptr_t                 dm_refcnt;   /* Reference counter. */
#endif /* MODULE_TYPE_COUNT < 2 */
	REF module_t             *dm_module;   /* Module handle. */
	di_debug_sections_t       dm_sections; /* Debug section mappings. */
	di_debug_dl_sections_t    dm_sectrefs; /* Debug section references. */
	struct dw_module_symcache dm_symbols;  /* Symbol cache. */
};

/* Destroy the given debug-module. */
FUNDEF NONNULL((1)) void NOTHROW(FCALL dw_module_destroy)(struct dw_module *__restrict self);
FUNDEF NONNULL((1)) void NOTHROW(FCALL dw_module_fini)(struct dw_module *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct dw_module, dm_refcnt, dw_module_destroy)

/* [0..1] Linked list of loaded debug-module objects (cleared during
 *        debugger reset; elements are lazily removed as they are
 *        destroyed) */
DATDEF struct dw_module *dw_module_list;

/* Clear the internal cache of pre-loaded DW modules (called
 * from `dbx_heap_alloc()' in an attempt to free memory).
 * @param: keep_loaded: When true, keep modules descriptors loaded if they
 *                      are apart of the kernel, or the `dbg_current->t_vm'
 *                      Otherwise, clear all modules from the cache.
 * @return: * : The # of modules that actually got destroyed (i.e. removing
 *              them from the cache caused their refcnt to drop to `0') */
FUNDEF size_t NOTHROW(FCALL dw_module_clearcache)(__BOOL keep_loaded DFL(0));

/* Lookup and return a reference to the debug-module descriptor for `mod'
 * @return: * :   A reference to the debug-module descriptor.
 * @return: NULL: Insufficient memory. */
FUNDEF WUNUSED NONNULL((1)) REF struct dw_module *
NOTHROW(FCALL dw_module_get)(module_t *__restrict mod module_type__param(modtype));
FUNDEF WUNUSED REF struct dw_module *
NOTHROW(FCALL dw_module_get_from_pc)(uintptr_t abs_pc);

struct dw_debugloc {
	REF struct dw_module *ddl_module; /* [1..1] Debug module. */
	byte_t const         *ddl_di_hdr; /* [1..1] Debug information header (in .debug_info) (s.a. `di_debuginfo_cu_parser_t::dup_cu_info_hdr') */
	byte_t const         *ddl_di_pos; /* [1..1] Debug information data (in .debug_info) (s.a. `di_debuginfo_cu_parser_t::dup_cu_info_pos') */
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
NOTHROW(KCALL dw_module_loadcu_ex)(struct dw_module const *__restrict self,
                                   /*out*/ di_debuginfo_cu_parser_t *__restrict parser,
                                   /*out*/ di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                   /*out*/ di_debuginfo_compile_unit_t *__restrict cu,
                                   /*in*/ uintptr_t module_relative_pc);

/* Same as `dw_module_loadcu_ex()', but use the current program
 * counter register, as selected by `dbg_getpcreg(DBG_REGLEVEL_VIEW)',
 * and return a reference to the associated module.
 * @return: * :   A reference to the associated module.
 * @return: NULL: Insufficient memory, or no module found. */
FUNDEF WUNUSED NONNULL((1, 2, 3)) REF struct dw_module *
NOTHROW(KCALL dw_module_loadcu)(/*out*/ di_debuginfo_cu_parser_t *__restrict parser,
                                /*out*/ di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                /*out*/ di_debuginfo_compile_unit_t *__restrict cu,
                                /*out_opt*/ uintptr_t *pmodule_relative_pc);


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_DW_H */
