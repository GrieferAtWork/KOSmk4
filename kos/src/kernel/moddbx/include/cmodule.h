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
#ifndef GUARD_MODDBX_INCLUDE_CMODULE_H
#define GUARD_MODDBX_INCLUDE_CMODULE_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/types.h>

#include <hybrid/typecore.h>

#include <kos/exec/module.h>

#include <libdebuginfo/debug_info.h>

/**/
#include "error.h"

DECL_BEGIN


struct cmodsym {
	/* Module symbols are cached in 1+N sorted vectors (where N is the number of CUs)
	 *  - The first and most important table is the module-global table. This table
	 *    contains the first found instance of any symbol, given its name, with the
	 *    guaranty that any symbol name only exists once within the table.
	 *  - Note that collisions between symbols form differing namespaces (s.a.
	 *    `CMODSYM_DIP_NSMASK') are allowed and simply ignored, such that these
	 *    symbols will simply co-exist within the same sorted vector.
	 *  - The other N vectors exist on a per-CU basis, and contain _only_ those
	 *    symbols that already exist within the primary per-module symbol table.
	 *    For this purpose, some internal optimizations are performed to catch
	 *    per-CU re-definitions of types, as is common in C where each unit would
	 *    define its own version of e.g. `struct tm'.
	 *    In this case, an attempt is made to only store a single instance of
	 *    `struct tm', which will appear within the per-module symbol table. */
	char const   *cms_name; /* [1..1] Symbol name (usually points into `.debug_str', and
	                         * owned by the referenced held by `cmodule::cm_sectrefs')
	                         * By default, this name is the string pointed-to by the
	                         * `DW_AT_linkage_name' attribute, but uses `DW_AT_name'
	                         * as a fallback. */
	/* TODO: Add a config option where `cms_name' isn't cached, but is instead lazily
	 *       re-calculated every time it is needed (by loading the DIP and parsing its
	 *       attributes for an `DW_AT_linkage_name' or `DW_AT_name' field) */
	uintptr_t     cms_dip;  /* [1..1] Debug information pointer for this symbol & namespace.
	                         * Use this pointer to load the associated DWARF debug info by passing
	                         * it to `cmodunit_parser_from_dip()' or `cmodule_parser_from_dip()'
	                         * The resulting parser's `dup_comp.dic_tag' will then be one of:
	                         *   - DW_TAG_structure_type
	                         *      - Namespace collisions with 
	                         *   - DW_TAG_namespace   // TODO: Handling of namespace members
	                         *   - DW_TAG_subprogram
	                         *      - Only if a `DW_AT_entry_pc' or `DW_AT_low_pc' tag is contained (which in
	                         *        turn translates to the symbol's address at runtime)
	                         *   - DW_TAG_label
	                         *   - DW_TAG_variable  (with a `DW_AT_location' that is expected to
	                         *                       contain `DW_OP_addr' or `DW_OP_form_tls_address')
	                         *   - DW_TAG_enumerator
	                         * NOTE: Recursive components are _NOT_ included if they originate
	                         *       from within `DW_TAG_subprogram', `DW_TAG_inlined_subroutine'
	                         *       are not scanned. In general, only globally visible symbols
	                         *       are included, as would be accessible from within an unnamed
	                         *       function placed at the end of the associated CU.
	                         *
	                         * Load debug info for this symbol by:
	                         * >> di_debuginfo_cu_parser_t parser;
	                         * >> cmodule_parser_from_dip(mod, cmodsym_getdip(sym), &parser);
	                         * >> switch (parser.dup_comp.dic_tag) {
	                         * >>
	                         * >> case DW_TAG_structure_type:
	                         * >>     ...
	                         * >>
	                         * >> case DW_TAG_subprogram:
	                         * >>     ...
	                         * >>
	                         * >> case ...:
	                         * >>     ...
	                         * >>
	                         * >> default: break;
	                         * >> } */
};

#if __SIZEOF_POINTER__ == 4
#define CMODSYM_DIP_DIPMASK __UINT32_C(0x0fffffff)
#define CMODSYM_DIP_NSMASK  __UINT32_C(0xf0000000)
#define CMODSYM_DIP_NSSHIFT 28
#elif __SIZEOF_POINTER__ == 8
#define CMODSYM_DIP_DIPMASK __UINT64_C(0x0fffffffffffffff)
#define CMODSYM_DIP_NSMASK  __UINT64_C(0xf000000000000000)
#define CMODSYM_DIP_NSSHIFT 60
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */
#define cmodsym_getns(self)  ((self)->cms_dip & CMODSYM_DIP_NSMASK)
#define cmodsym_getdip(self) ((byte_t const *)((self)->cms_dip & CMODSYM_DIP_DIPMASK))

/* CModSym namespaces. */
#define CMODSYM_DIP_NS_NORMAL    (__UINTPTR_C(0) << CMODSYM_DIP_NSSHIFT) /* Normal (global) namespace. */
#define CMODSYM_DIP_NS_STRUCT    (__UINTPTR_C(1) << CMODSYM_DIP_NSSHIFT) /* struct-name-namespace. */
#define CMODSYM_DIP_NS_UNION     (__UINTPTR_C(2) << CMODSYM_DIP_NSSHIFT) /* union-name-namespace. */
#define CMODSYM_DIP_NS_ENUM      (__UINTPTR_C(3) << CMODSYM_DIP_NSSHIFT) /* enum-name-namespace. */
#define CMODSYM_DIP_NS_FCONFLICT (__UINTPTR_C(4) << CMODSYM_DIP_NSSHIFT) /* FLAG: There is another, PER-CU symbol with the same name. */



struct cmodsymtab {
	size_t          mst_symc; /* # of symbols. */
	struct cmodsym *mst_symv; /* [0..mst_symc][owned][lock(WRITE_ONCE)]
	                           * Vector of symbols (lazily initialized). */
};

struct cmodunit {
	/* CModule CompilationUnit */
	byte_t const            *cu_di_start; /* [1..1] .debug_info start (s.a. `di_debuginfo_cu_parser_t::dup_cu_info_hdr'). */
	di_debuginfo_cu_abbrev_t cu_abbrev;   /* DWARF Debug-info abbreviation codes used by this CU. */
	struct cmodsymtab        cu_symbols;  /* Per-unit symbols (who's names collide with other per-module symbols).
	                                       * NOTE: `.mst_symv == (struct cmodsym *)-1' if symbols from this CU have
	                                       *       yet to be loaded. Also note that when symbols are loaded, this
	                                       *       is done for all CUs, such that one can easily check if symbols
	                                       *       for a given module have been fully loaded by doing a check
	                                       * `mod->cm_cuv[mod->cm_cuc-1].cu_symbols.mst_symv != (struct cmodsym *)-1' */
};

#define cmodunit_di_start(self) ((self)[0].cu_di_start)
#define cmodunit_di_end(self)   ((self)[1].cu_di_start) /* One unit ends where the next one begins. */

/* Initialize a debug information CU parser from a given CModule CompilationUnit
 * @param: dip: A pointer to the first component to load, or `NULL' to simply load
 *              the first component following the start of the associated CU descriptor.
 *              When non-NULL, this pointer must be located somewhere between
 *              `cmodunit_di_start(self)' and `cmodunit_di_end(self)'.
 *              If it isn't, then the parser will be initialized to always indicate EOF. */
FUNDEF NONNULL((1, 2, 3)) void
NOTHROW(FCALL cmodunit_parser_from_dip)(struct cmodunit const *__restrict self,
                                        struct cmodule const *__restrict mod,
                                        di_debuginfo_cu_parser_t *__restrict result,
                                        byte_t const *dip);

struct cmodule {
	struct cmodule                         **cm_pself;     /* [1..1][1..1] Self-pointer */
	struct cmodule                          *cm_next;      /* [0..1] Next module. */
	REF struct cmodule                      *cm_cache;     /* [0..1] Next cached module. */
#if MODULE_TYPE_COUNT >= 2
	uintptr_half_t                           cm_refcnt;    /* Reference counter. */
	uintptr_half_t                           cm_modtyp;    /* [const] Module type (one of `MODULE_TYPE_*'). */
#else /* MODULE_TYPE_COUNT >= 2 */
	uintptr_t                                cm_refcnt;    /* Reference counter. */
#endif /* MODULE_TYPE_COUNT < 2 */
	REF module_t                            *cm_module;   /* [1..1][const] Module handle. */
	di_debug_sections_t                      cm_sections; /* [const] Debug section mappings. */
	di_debug_dl_sections_t                   cm_sectrefs; /* [const] Debug section references. */
	struct cmodsymtab                        cm_symbols;  /* Per-module debug symbol. */
	size_t                                   cm_cuc;      /* [const] # of compilation units. */
	COMPILER_FLEXIBLE_ARRAY(struct cmodunit, cm_cuv);     /* Complication units. (sorted by `cu_di_start')
	                                                       * Note that `cm_cuv[cm_cuc]' exists only partially, such
	                                                       * that only its `cu_di_start' may be accessed, which will
	                                                       * usually be equal to `cm_sections.ds_debug_info_end' */
};
#define cmodule_getloadaddr(self)  module_getloadaddr((self)->cm_module, (self)->cm_modtyp)
#define cmodule_getloadstart(self) module_getloadstart((self)->cm_module, (self)->cm_modtyp)
#define cmodule_getloadend(self)   module_getloadend((self)->cm_module, (self)->cm_modtyp)

/* Destroy the given CModule. (called when its reference counter hits `0') */
FUNDEF NONNULL((1)) void NOTHROW(FCALL cmodule_destroy)(struct cmodule *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct cmodule, cm_refcnt, cmodule_destroy) /* TODO: Define non-atomic refcnt functions! */

/* Callback for `cmodule_enum()'
 * @return: * : pformatprinter-compatible return value. */
typedef NONNULL((2)) ssize_t
/*NOTHROW*/ (FCALL *cmodule_enum_callback_t)(void *cookie, struct cmodule *__restrict mod);

/* Enumerate all CModules that are currently visible in the following order:
 * >> void *pc = dbg_getpcreg(DBG_REGLEVEL_VIEW);
 * >> ENUM(cmodule_ataddr(pc));
 * >> if (ADDR_ISKERN(pc)) {
 * >>     cmodule_enum_drivers();                 // Excluding `cmodule_ataddr(pc)'
 * >>     cmodule_enum_uservm(dbg_current->t_vm);
 * >> } else {
 * >>     cmodule_enum_uservm(dbg_current->t_vm); // Excluding `cmodule_ataddr(pc)'
 * >>     cmodule_enum_drivers();
 * >> }
 * @return: * : pformatprinter-compatible return value. */
FUNDEF NONNULL((1)) ssize_t
NOTHROW(FCALL cmodule_enum)(cmodule_enum_callback_t cb,
                            void *cookie);

struct vm;

/* Enumerate all user-space modules mapped within the given vm
 * `self' as CModule objects, and invoke `cb' on each of them. */
FUNDEF NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmodule_enum_uservm)(struct vm *__restrict self,
                                   cmodule_enum_callback_t cb,
                                   void *cookie);

/* Enumerate all kernel-space drivers as CModule objects, and
 * invoke `cb' on each of them. */
FUNDEF NONNULL((1)) ssize_t
NOTHROW(FCALL cmodule_enum_drivers)(cmodule_enum_callback_t cb,
                                    void *cookie);


/* Lookup or create the CModule for the given `mod:modtype'
 * If the module has already been loaded, return a reference to
 * the pre-loaded CModule. Otherwise, create and remember a new
 * module which is then kept in-cache. If this step fails due to
 * lack of memory, `NULL' is returned instead. */
FUNDEF WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_locate)(module_t *__restrict mod
                              module_type__param(modtype));

/* Return the CModule descriptor for a given `addr', which should be a program counter, or data-pointer.
 * If no such module exists, or its descriptor could not be allocated, return `NULL' instead.
 * This function is a thin wrapper around `module_ataddr_nx()' + `cmodule_locate()' */
FUNDEF WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_ataddr)(void const *addr);

/* Return the CModule for `dbg_getpcreg(DBG_REGLEVEL_VIEW)'
 * Same as `cmodule_ataddr(dbg_getpcreg(DBG_REGLEVEL_VIEW))' */
FUNDEF WUNUSED REF struct cmodule *
NOTHROW(FCALL cmodule_current)(void);

/* Load debug symbols for the give CModule. Since doing this may
 * take quite a while, this function is equipped to make use of
 * `dbg_awaituser()' to allow it to be interrupted prior to being
 * completed. If this happens, then this function returns `DBX_EINTR',
 * and the caller must assume that not all symbols have been loaded.
 * In this case, the caller is allowed to continue as through that
 * the symbol they were looking for doesn't exist, or no symbols
 * exist at all.
 * @return: DBX_EOK:   Success.
 * @return: DBX_EINTR: Operation was interrupted. */
FUNDEF WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cmodule_loadsyms)(struct cmodule *__restrict self);

/* Lookup the a symbol within `self', given its `name'. If debug
 * symbols had yet to be loaded, then this function will make a
 * call to `cmodule_loadsyms()'. If that call fails, this function
 * will simply return `NULL'.
 * To do its job, this function will first look at the per-module
 * symbol table of `self' (iow: `self->cm_symbols').
 * If this table contains a symbol matching `name', that symbol
 * is then returned, unless it has the `CMODSYM_DIP_NS_FCONFLICT'
 * flag set, in which case `dbg_getpcreg(DBG_REGLEVEL_VIEW)' is
 * check for being apart of `self'. If it is, try to find the CU
 * associated with that address. If such a CU exists, check that
 * CU's symbol table for `name' once again. If that table contains
 * the given `name' also, return that symbol. Otherwise (if any
 * of the above failed), simply return the symbol already found
 * within the module's global symbol table.
 * @param: ns: When different from `CMODSYM_DIP_NS_NORMAL', restrict
 *             the search to only return symbols from the indicated
 *             namespace. Otherwise, ~try~ to return symbols from the
 *             given namespace, but when (at least 1) symbol is found
 *             that is apart of a different namespace, return that
 *             symbol instead. */
FUNDEF WUNUSED NONNULL((1, 2)) struct cmodsym const *
NOTHROW(FCALL cmodule_getsym)(struct cmodule *__restrict self,
                              char const *__restrict name, size_t namelen,
                              uintptr_t ns DFL(CMODSYM_DIP_NS_NORMAL));


/* Resolve a global symbol by finding its containing module, and returning
 * a pointer to the associated symbol object. This function is implemented
 * as a combination of `cmodule_enum()' + `cmodule_getsym()', meaning that
 * symbol resolution order matches what is done by `cmodule_enum()'
 * @return: * :   Success. (`*presult_module' was populated with a reference)
 * @return: NULL: Error: Insufficient memory.
 * @return: NULL: Error: No such symbol.
 * @return: NULL: Error: Operation was interrupted. */
FUNDEF WUNUSED NONNULL((1, 3)) struct cmodsym const *
NOTHROW(FCALL cmodule_getsym_global)(char const *__restrict name, size_t namelen,
                                     REF struct cmodule **__restrict presult_module,
                                     uintptr_t ns DFL(CMODSYM_DIP_NS_NORMAL));


/* Initialize a debug information CU parser to load debug information for a component
 * located at `dip' within the `.debug_info' mapping of `self'. For this
 * purpose, this function will locate the CU that contains `dip', and proceed
 * to call `cmodunit_parser()' to initialize `result'. If the given `dip'
 * is not apart of any of the CUs of `self', then `result' will be initialized
 * to always indicate EOF.
 * @param: dip: DebugInfoPointer. (s.a. `cmodunit_parser_from_dip()') */
FUNDEF NONNULL((1, 2, 3)) void
NOTHROW(FCALL cmodule_parser_from_dip)(struct cmodule const *__restrict self,
                                       di_debuginfo_cu_parser_t *__restrict result,
                                       byte_t const *__restrict dip);

/* Try to find the compilation unit that contains `module_relative_pc'
 * If no such unit can be located, `NULL' will be returned instead. */
FUNDEF WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_pc)(struct cmodule const *__restrict self,
                                        uintptr_t module_relative_pc);

/* Try to find the compilation unit that contains `dip'
 * If no such unit can be located, `NULL' will be returned instead. */
FUNDEF WUNUSED ATTR_PURE NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_dip)(struct cmodule const *__restrict self,
                                         byte_t const *__restrict dip);

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_CMODULE_H */
