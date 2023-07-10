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
#ifndef GUARD_MODDBX_INCLUDE_CMODULE_H
#define GUARD_MODDBX_INCLUDE_CMODULE_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/typecore.h>

#include <kos/exec/module.h>
#include <kos/refcnt-nonatomic.h>

#include <elf.h>

#include <libdebuginfo/debug_info.h>

/**/
#include "error.h"

DECL_BEGIN

/*
 * Module symbols come in 1 of 3 forms:
 *
 *  - Pure .debug_info variable/function  (cmodsym_isdip)
 *     - Use `cmodunit_parser_from_dip()' and `cmodsym_getdip()'
 *       to   init  a  parser  for  loading  debug  information.
 *     - Address/value information for the  symbol (unless it's a  type)
 *       can also be found by parsing debug information and interpreting
 *       its tags:
 *         - DW_AT_low_pc
 *         - DW_AT_entry_pc
 *         - DW_AT_const_value
 *         - DW_AT_location
 *         - DW_AT_sibling or DW_AT_specification (pointing to one of the above)
 *
 *  - Pure .symtab symbol  (cmodsym_issip)
 *     - This symbol has no debug information attached to it (gdb would
 *       call this type of symbol a "text variable"). However, it  does
 *       have  an address, as well as a  name, meaning that there is at
 *       least ~some~ useful information to this symbol.
 *     - This kind of symbol only appears if scanning of .debug_info does
 *       not  reveal any additional information in regards to a symbol of
 *       the same name. If  a symbol with the  same name is found  during
 *       loading of debug information, 1 of 4 things happens:
 *         - If the symbol from .debug_info has no type information,
 *           then the .debug_info  entry for the  symbol is  ignored
 *         - If the symbol from .debug_info has type, but no  location
 *           information, then the symbol becomes a mixed symbol which
 *           is represented as  CMODSYM_DIP_NS_MIXED, where type  info
 *           for  the symbol originates  from .debug_info, but address
 *           information originates from .symtab
 *         - If the symbol from .debug_info has a type and a location,  that
 *           location is (attempted to be) evaluated. If the location  isn't
 *           an address, the address cannot be calculated (e.g. because it's
 *           TLS),  or if its address differs from the symbol's address from
 *           .symtab,  then  the symbol  from  .debug_info is  added  to the
 *           current per-CU symbol  table, and the  original .symtab  symbol
 *           is marked with `CMODSYM_DIP_NS_FCONFLICT'
 *         - If the address from .debug_info could be evaluated, and  that
 *           address matches the symbol's  address from .symtab, then  the
 *           symbol entry simply becomes a normal `CMODSYM_DIP_NS_NORMAL',
 *           since all relevant information can be loaded from .debug_info
 *
 *  - Mixed .debug_info/.symtab symbol  (cmodsym_ismip)
 *     - Like described above, this type of symbol pulls its information
 *       from the combination of type information from .debug_info,  and
 *       address information from .symtab
 */



/* Internal structures for used by `kernel_symbol_table' (from `/kos/kernel/core/fs/driver.c') */
struct kernel_syment {
	char const *ks_name; /* [0..1] Symbol name (NULL for sentinel) */
	void       *ks_addr; /* Symbol address */
	u32         ks_size; /* Symbol size */
	u32         ks_hash; /* Symbol hash (s.a. `elf_symhash()') */
};
struct kernel_symtab {
	uintptr_t                                     ds_mask;  /* Hash mask. */
	COMPILER_FLEXIBLE_ARRAY(struct kernel_syment, ds_list); /* Symbol map. */
};
/* The kernel symbol table (containing everything marked as PUBLIC) */
DATDEF struct kernel_symtab kernel_symbol_table;


typedef union {
	struct kernel_syment cls_kern;  /* [valid_if(:cm_module == &kernel_driver)]
	                                 * NOTE: In this case, SIP offsets are relative to `&kernel_symbol_table',
	                                 *       and         `cm_sections.ds_symtab_start == &kernel_symbol_table' */
	Elf32_Sym            cls_elf32; /* [valid_if(:cm_sections.ds_symtab_ent == sizeof(Elf32_Sym))] */
	Elf64_Sym            cls_elf64; /* [valid_if(:cm_sections.ds_symtab_ent == sizeof(Elf64_Sym))] */
} CLinkerSymbol;
#define CLinkerSymbol_IsKern(mod)  ((mod)->cm_module == (module_t *)&kernel_driver)
#define CLinkerSymbol_IsElf32(mod) ((mod)->cm_sections.ds_symtab_ent == sizeof(Elf32_Sym))
#define CLinkerSymbol_IsElf64(mod) ((mod)->cm_sections.ds_symtab_ent == sizeof(Elf64_Sym))


struct cmodsym {
	/* Module symbols are cached in 1+N sorted vectors (where N is the number of CUs)
	 *  - The first and most important table is the module-global table. This table
	 *    contains the first found instance of any symbol, given its name, with the
	 *    guaranty that any symbol name only exists once within the table.
	 *  - Note that collisions between symbols form differing namespaces  (s.a.
	 *    `CMODSYM_DIP_NSMASK') are allowed and simply ignored, such that these
	 *    symbols will simply co-exist within the same sorted vector.
	 *  - The  other N vectors exist on a  per-CU basis, and contain _only_ those
	 *    symbols that already exist within the primary per-module symbol  table.
	 *    For this purpose,  some internal optimizations  are performed to  catch
	 *    per-CU re-definitions of types, as is common in C where each unit would
	 *    define its own version of e.g. `struct tm'.
	 *    In this case, an attempt is made to only store a single instance of
	 *    `struct tm', which will appear within the per-module symbol  table. */
	CHECKED char const *cms_name; /* [1..1] Symbol name (usually points into `.debug_str', and
	                               * owned by  the reference  held by  `cmodule::cm_sectrefs')
	                               * By  default, this  name is  the string  pointed-to by the
	                               * `DW_AT_linkage_name'  attribute,  but  uses  `DW_AT_name'
	                               * as a fallback. */
	uintptr_t           cms_dip;  /* [1..1] Debug  information  pointer  for  this  symbol  & namespace.
	                               * Use this pointer to load the associated DWARF debug info by passing
	                               * it to  `cmodunit_parser_from_dip()' or  `cmodule_parser_from_dip()'
	                               * The resulting  parser's `dup_comp.dic_tag'  will  then be  one  of:
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
	                               * NOTE: Recursive  components  are _NOT_  included if  they originate
	                               *       from inside `DW_TAG_subprogram', `DW_TAG_inlined_subroutine'.
	                               *       In general, only  globally visible symbols  are included,  as
	                               *       would be accessible from within an unnamed function placed at
	                               *       the end of the associated CU.
	                               *
	                               * Load debug info for this symbol by:
	                               * >> di_debuginfo_cu_parser_t parser;
	                               * >> cmodule_parser_from_dip(mod, cmodsym_getdip(sym, mod), &parser);
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
#define CMODSYM_DIP_DIPMASK __UINT32_C(0x07ffffff)
#define CMODSYM_DIP_NSMASK  __UINT32_C(0xf8000000)
#define CMODSYM_DIP_NSSHIFT 27
#elif __SIZEOF_POINTER__ == 8
#define CMODSYM_DIP_DIPMASK __UINT64_C(0x07ffffffffffffff)
#define CMODSYM_DIP_NSMASK  __UINT64_C(0xf800000000000000)
#define CMODSYM_DIP_NSSHIFT 59
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */
/* NOTE: sip = SymbolInfoPointer  (offset to Elf(32|64)_Sym in .symtab or .dynsym)
 *       dip = DebugInfoPointer   (offset into .debug_info)
 *       mip = MixedInfoPointer   (offset into MODULE.cm_mixed.mss_symv) */
#define cmodsym_getdip(self, mod)     ((mod)->cm_sections.ds_debug_info_start + ((self)->cms_dip & CMODSYM_DIP_DIPMASK))
#define cmodsym_getsip(self, mod)     ((CLinkerSymbol const *)((mod)->cm_sections.ds_symtab_start + ((self)->cms_dip & CMODSYM_DIP_DIPMASK)))
#define cmodsym_getmip(self, mod)     ((struct cmodmixsym const *)((byte_t const *)(mod)->cm_mixed.mss_symv + ((self)->cms_dip & CMODSYM_DIP_DIPMASK)))
#define cmodsym_makedip(mod, dip, ns) ((uintptr_t)((dip) - (mod)->cm_sections.ds_debug_info_start) | (ns))
#define cmodsym_makesip(mod, sip)     ((uintptr_t)((sip) - (mod)->cm_sections.ds_symtab_start) | CMODSYM_DIP_NS_SYMTAB)
#define cmodsym_makemip(mod, mip)     ((uintptr_t)((byte_t const *)(mip) - (byte_t const *)(mod)->cm_mixed.mss_symv) | CMODSYM_DIP_NS_MIXED)
#define cmodsym_getns(self)           ((self)->cms_dip & CMODSYM_DIP_NSMASK)
#define cmodsym_istype(self)          CMODSYM_DIP_NS_ISTYPE(cmodsym_getns(self))
#define cmodsym_isdip(self)           CMODSYM_DIP_NS_ISDIP(cmodsym_getns(self))
#define cmodsym_issip(self)           CMODSYM_DIP_NS_ISSIP(cmodsym_getns(self))
#define cmodsym_ismip(self)           CMODSYM_DIP_NS_ISMIP(cmodsym_getns(self))
#define cmodsym_name(self, mod)       ((self)->cms_name)
#undef CMODSYM_NAME_NEEDS_MODULE

/* CModSym namespaces. */
#define CMODSYM_DIP_NS_SYMTAB    (__UINTPTR_C(0) << CMODSYM_DIP_NSSHIFT) /* Normal (global) namespace. (but this one comes from `.symtab') */
#define CMODSYM_DIP_NS_MIXED     (__UINTPTR_C(1) << CMODSYM_DIP_NSSHIFT) /* Normal (global) namespace. (but this one is a mixed `.symtab' / `.debug_info' symbol)
                                                                          * Note  that  this type  of symbol  can only  appear in  the per-module,  global symbol
                                                                          * table,  but not in the per-CU symbol tables.  However, it can still stand in conflict
                                                                          * with other per-CU symbols. */
#define CMODSYM_DIP_NS_NORMAL    (__UINTPTR_C(2) << CMODSYM_DIP_NSSHIFT) /* Normal (global) namespace. */
#define CMODSYM_DIP_NS_TYPEDEF   (__UINTPTR_C(3) << CMODSYM_DIP_NSSHIFT) /* Normal  (global) namespace. (but  this one's a type)
                                                                          * When passed to lookup functions, only consider types
                                                                          * as  suitable symbols, and skip all non-type symbols. */
#define CMODSYM_DIP_NS_STRUCT    (__UINTPTR_C(4) << CMODSYM_DIP_NSSHIFT) /* struct-name-namespace. */
#define CMODSYM_DIP_NS_UNION     (__UINTPTR_C(5) << CMODSYM_DIP_NSSHIFT) /* union-name-namespace. */
#define CMODSYM_DIP_NS_CLASS     (__UINTPTR_C(6) << CMODSYM_DIP_NSSHIFT) /* class-name-namespace. */
#define CMODSYM_DIP_NS_ENUM      (__UINTPTR_C(7) << CMODSYM_DIP_NSSHIFT) /* enum-name-namespace. */
#define CMODSYM_DIP_NS_FCONFLICT (__UINTPTR_C(8) << CMODSYM_DIP_NSSHIFT) /* FLAG: There is another, PER-CU symbol with the same name. */
#define CMODSYM_DIP_NS_ISTYPE(x)   (((x) & ~CMODSYM_DIP_NS_FCONFLICT) >= CMODSYM_DIP_NS_TYPEDEF)
#define CMODSYM_DIP_NS_ISNORMAL(x) ((x) <= CMODSYM_DIP_NS_SYMTAB)
#define CMODSYM_DIP_NS_ISGLOBAL(x) ((x) <= CMODSYM_DIP_NS_TYPEDEF)
#define CMODSYM_DIP_NS_ISDIP(x)    (((x) & ~CMODSYM_DIP_NS_FCONFLICT) >= CMODSYM_DIP_NS_NORMAL)
#define CMODSYM_DIP_NS_ISSIP(x)    (((x) & ~CMODSYM_DIP_NS_FCONFLICT) == CMODSYM_DIP_NS_SYMTAB)
#define CMODSYM_DIP_NS_ISMIP(x)    (((x) & ~CMODSYM_DIP_NS_FCONFLICT) == CMODSYM_DIP_NS_MIXED)

/* Special value which may be passed  as `ns' argument to functions  below.
 * When given, don't accept type symbols, and only enumerate/return symbols
 * that aren't types. */
#define CMODSYM_DIP_NS_NONTYPE CMODSYM_DIP_NS_SYMTAB



struct cmodsymtab {
	size_t          mst_symc; /* # of symbols. */
	struct cmodsym *mst_symv; /* [0..mst_symc][owned][lock(WRITE_ONCE)]
	                           * Vector of symbols (lazily initialized). */
};
#define cmodsymtab_syma(self) (dbx_malloc_usable_size((self)->mst_symv) / sizeof(struct cmodsym))

struct cmodmixsym {
	byte_t        const *ms_dip; /* [1..1] Absolute pointer (apart of .debug_info) for debug information. */
	CLinkerSymbol const *ms_sip; /* [1..1] Absolute pointer (apart of .symtab/.dynsym) for address information. */
};

struct cmodmixsymtab {
	size_t             mss_symc; /* # of mixed symbols in use. */
	struct cmodmixsym *mss_symv; /* [0..1][owned] Mixed symbol information.
	                              * NOTE: This list is sorted ascendingly by `ms_dip' */
};


struct cmodunit {
	/* CModule CompilationUnit */
	byte_t CHECKED const    *cu_di_start; /* [1..1] .debug_info start (s.a. `di_debuginfo_cu_parser_t::dup_cu_info_hdr'). */
	struct cmodsymtab        cu_symbols;  /* Per-unit symbols (who's names collide with other per-module symbols).
	                                       * NOTE: `.mst_symv == (struct cmodsym *)-1' if symbols from this CU have
	                                       *       yet to be loaded. Also note  that when symbols are loaded,  this
	                                       *       is  done for all CUs, such that  one can easily check if symbols
	                                       *       for a given module have been fully loaded by doing a check
	                                       * `mod->cm_cuv[mod->cm_cuc-1].cu_symbols.mst_symv != (struct cmodsym *)-1' */
	di_debuginfo_cu_abbrev_t cu_abbrev;   /* DWARF Debug-info abbreviation codes used by this CU. */
};

#define cmodunit_di_start(self)  ((self)[0].cu_di_start)
#define cmodunit_di_maxend(self) ((self)[1].cu_di_start) /* One unit has to end before the next one begins. */

/* Initialize a debug information CU parser from a given CModule CompilationUnit
 * @param: dip: A pointer  to the  first component  to load,  or `NULL'  to simply  load
 *              the first component following the start of the associated CU descriptor.
 *              When  non-NULL,  this   pointer  must  be   located  somewhere   between
 *              `cmodunit_di_start(self)' and `cmodunit_di_maxend(self)'.
 *              If it isn't, then the parser will be initialized to always indicate EOF. */
FUNDEF NONNULL((1, 2, 3)) void
NOTHROW_NCX(FCALL cmodunit_parser_from_dip)(struct cmodunit const *__restrict self,
                                            struct cmodule const *__restrict mod,
                                            di_debuginfo_cu_parser_t *__restrict result,
                                            byte_t CHECKED const *dip);


struct cmodule {
	LIST_ENTRY(cmodule)                      cm_link;     /* [0..1] Link in list of modules (`cmodule_list') */
	SLIST_ENTRY(REF cmodule)                 cm_cache;    /* [0..1] Link in list of cached module. */
	uintptr_t                                cm_refcnt;   /* Reference counter. */
	REF module_t                            *cm_module;   /* [1..1][const] Module handle. */
	di_debug_sections_t                      cm_sections; /* [const] Debug section mappings. */
	di_debug_dl_sections_t                   cm_sectrefs; /* [const] Debug section references. */
	struct cmodsymtab                        cm_symbols;  /* Per-module debug symbol. */
	struct cmodmixsymtab                     cm_mixed;    /* Information about mixed symbols. */
	size_t                                   cm_cuc;      /* [const] # of compilation units. */
	COMPILER_FLEXIBLE_ARRAY(struct cmodunit, cm_cuv);     /* Complication units. (sorted by `cu_di_start'). Note that
	                                                       * `cm_cuv[cm_cuc]' exists only  partially, such that  only
	                                                       * its `cu_di_start' may be accessed, which will usually be
	                                                       * equal to `cm_sections.ds_debug_info_end' */
};
#define cmodule_getloadaddr(self) (self)->cm_module->md_loadaddr
#define cmodule_getloadmin(self)  (self)->cm_module->md_loadmin
#define cmodule_getloadmax(self)  (self)->cm_module->md_loadmax
#define cmodule_mman(self)        (self)->cm_module->md_mman
#define cmodule_isuser(self)      (!module_isdriver((self)->cm_module))
#define cmodule_iskern(self)      module_isdriver((self)->cm_module)

#define cmodule_di_debug_sections(self)               (&(self)->cm_sections)
#define cmodule_unwind_emulator_sections(self)        di_debug_sections_as_unwind_emulator_sections(&(self)->cm_sections)
#define cmodule_di_enum_locals_sections(self)         di_debug_sections_as_di_enum_locals_sections(&(self)->cm_sections)
#define cmodule_di_debuginfo_cu_parser_sections(self) di_debug_sections_as_di_debuginfo_cu_parser_sections(&(self)->cm_sections)
#define cmodule_di_addr2line_sections(self)           di_debug_sections_as_di_addr2line_sections(&(self)->cm_sections)

/* Destroy the given CModule. (called when its reference counter hits `0') */
FUNDEF NONNULL((1)) void NOTHROW(FCALL cmodule_destroy)(struct cmodule *__restrict self);
__DEFINE_NONATOMIC_REFCNT_FUNCTIONS(struct cmodule, cm_refcnt, cmodule_destroy)

/* Callback for `cmodule_enum()'
 * @return: * : pformatprinter-compatible return value. */
typedef NONNULL_T((2)) ssize_t
(FCALL *cmodule_enum_callback_t)(void *cookie, struct cmodule *__restrict mod);

/* Enumerate all CModules that are currently visible in the following order:
 * >> void const *pc = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);
 * >> ENUM(cmodule_ataddr(pc));
 * >> if (ADDR_ISKERN(pc)) {
 * >>     cmodule_enum_drivers();                     // Excluding `cmodule_ataddr(pc)'
 * >>     cmodule_enum_usermman(dbg_current->t_mman);
 * >> } else {
 * >>     cmodule_enum_usermman(dbg_current->t_mman); // Excluding `cmodule_ataddr(pc)'
 * >>     cmodule_enum_drivers();
 * >> }
 * @return: * :        pformatprinter-compatible return value.
 * @return: DBX_EINTR: Operation was interrupted. */
FUNDEF NONNULL((1)) ssize_t FCALL
cmodule_enum(cmodule_enum_callback_t cb, void *cookie);
/* Same as `cmodule_enum()', but use `start_module' (if non-NULL) instead of `cmodule_ataddr(pc)' */
FUNDEF NONNULL((2)) ssize_t FCALL
cmodule_enum_with_hint(struct cmodule *start_module,
                       cmodule_enum_callback_t cb,
                       void *cookie);

struct mman;

/* Enumerate all user-space modules mapped within the given mman
 * `self' as CModule objects, and  invoke `cb' on each of  them.
 * @return: * :        pformatprinter-compatible return value.
 * @return: DBX_EINTR: Operation was interrupted. */
FUNDEF NONNULL((1, 2)) ssize_t FCALL
cmodule_enum_usermman(struct mman *__restrict self,
                      cmodule_enum_callback_t cb,
                      void *cookie);

/* Enumerate all kernel-space drivers as CModule objects, and
 * invoke `cb' on each of them.
 * @return: * :        pformatprinter-compatible return value.
 * @return: DBX_EINTR: Operation was interrupted. */
FUNDEF NONNULL((1)) ssize_t FCALL
cmodule_enum_drivers(cmodule_enum_callback_t cb, void *cookie);

/* Clear the internal cache of pre-loaded CModules (called
 * from  `dbx_heap_alloc()' in an attempt to free memory).
 * @param: keep_loaded: When true, keep  modules descriptors  loaded if  they
 *                      are apart of the kernel, or the `dbg_current->t_mman'
 *                      Otherwise, clear all modules from the cache.
 * @return: * : The # of modules that actually got destroyed (i.e. removing
 *              them from the  cache caused  their refcnt to  drop to  `0') */
FUNDEF size_t NOTHROW(FCALL cmodule_clearcache)(__BOOL keep_loaded DFL(0));

/* Lookup or create the CModule for the given `mod'
 * If  the module has already been loaded, return a reference to
 * the pre-loaded CModule. Otherwise, create and remember a  new
 * module which is then kept in-cache. If this step fails due to
 * lack of memory, `NULL' is returned instead. */
FUNDEF WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW_NCX(FCALL cmodule_locate)(module_t *__restrict mod);

/* Return the CModule descriptor for  a given `addr', which  should
 * be a program counter, or data-pointer. If no such module exists,
 * or its descriptor could not be allocated, return `NULL' instead.
 * This function is a thin wrapper around `module_fromaddr_nx()' + `cmodule_locate()' */
FUNDEF WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW_NCX(FCALL cmodule_ataddr)(void const *addr);

/* Return the CModule for  `dbg_getpcreg(DBG_RT_REGLEVEL_VIEW)'
 * Same as `cmodule_ataddr(dbg_getpcreg(DBG_RT_REGLEVEL_VIEW))' */
FUNDEF WUNUSED REF struct cmodule *
NOTHROW_NCX(FCALL cmodule_current)(void);

/* Load debug symbols for the give CModule. Since doing this may take quite
 * a while, this function is equipped  to make use of `dbg_awaituser()'  to
 * allow  it to be  interrupted prior to being  completed. If this happens,
 * then  this function returns `DBX_EINTR', and the caller must assume that
 * not all symbols have been loaded.
 *
 * In this case,  the caller is  allowed to continue  as through that  the
 * symbol they were looking for doesn't exist, or no symbols exist at all.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_EINTR:  Operation was interrupted. */
FUNDEF WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW_NCX(FCALL cmodule_loadsyms)(struct cmodule *__restrict self);

/* Lookup the a symbol within  `self', given its `name'. If  debug
 * symbols  had yet to  be loaded, then this  function will make a
 * call to `cmodule_loadsyms()'. If that call fails, this function
 * will simply return `NULL'.
 * To do its job, this function  will first look at the  per-module
 * symbol table of `self' (iow: `self->cm_symbols'). If this  table
 * contains a symbol matching `name', that symbol is then returned,
 * unless it has the `CMODSYM_DIP_NS_FCONFLICT' flag set, in  which
 * case `dbg_getpcreg(DBG_RT_REGLEVEL_VIEW)' is  checked for  being
 * apart of `self'. If  it is, try to  find the CU associated  with
 * that address. If such a CU exists, check that CU's symbol  table
 * for `name' once again. If  that table contains the given  `name'
 * also,  return  that  symbol.  Otherwise  (if  any  of  the above
 * failed), simply  return  the  symbol already  found  within  the
 * module's global symbol table.
 * @param: ns: When different from `CMODSYM_DIP_NS_NORMAL',  restrict
 *             the search to only  return symbols from the  indicated
 *             namespace. Otherwise, ~try~ to return symbols from the
 *             given namespace, but when (at least 1) symbol is found
 *             that is apart  of a different  namespace, return  that
 *             symbol instead. */
FUNDEF WUNUSED NONNULL((1)) struct cmodsym const *
NOTHROW_NCX(FCALL cmodule_getsym)(struct cmodule *__restrict self,
                                  char CHECKED const *name, size_t namelen,
                                  uintptr_t ns DFL(CMODSYM_DIP_NS_NORMAL));


/* Resolve a global symbol by finding its containing module, and returning
 * a pointer to the associated symbol object. This function is implemented
 * as a combination of `cmodule_enum()' + `cmodule_getsym()', meaning that
 * symbol resolution order matches what is done by `cmodule_enum()'
 * @return: * :   Success. (`*presult_module' was populated with a reference)
 * @return: NULL: Error: Insufficient memory.
 * @return: NULL: Error: No such symbol.
 * @return: NULL: Error: Operation was interrupted. */
FUNDEF WUNUSED NONNULL((3)) struct cmodsym const *
NOTHROW_NCX(FCALL cmodule_getsym_global)(char CHECKED const *name, size_t namelen,
                                         REF struct cmodule **__restrict presult_module,
                                         uintptr_t ns DFL(CMODSYM_DIP_NS_NORMAL));

/* Same as `cmodule_getsym_global()',  but search for  symbols starting  with
 * `start_module', and continuing the search within related modules. For this
 * purpose,  start by searching `start_module' itself, and moving on to other
 * modules within its address space, before finally search through modules in
 * different address spaces. */
FUNDEF WUNUSED NONNULL((4)) struct cmodsym const *
NOTHROW_NCX(FCALL cmodule_getsym_withhint)(struct cmodule *start_module,
                                           char CHECKED const *name, size_t namelen,
                                           REF struct cmodule **__restrict presult_module,
                                           uintptr_t ns DFL(CMODSYM_DIP_NS_NORMAL));

/* Initialize a debug information CU parser to load debug information for a
 * component located at `dip' within  the `.debug_info' mapping of  `self'.
 * For this purpose, this function will locate the CU that contains  `dip',
 * and proceed to call `cmodunit_parser()'  to initialize `result'. If  the
 * given `dip' is not apart of any of the CUs of `self', then `result' will
 * be initialized to always indicate EOF.
 * @param: dip: DebugInfoPointer. (s.a. `cmodunit_parser_from_dip()') */
FUNDEF NONNULL((1, 2)) void
NOTHROW_NCX(FCALL cmodule_parser_from_dip)(struct cmodule const *__restrict self,
                                           di_debuginfo_cu_parser_t *__restrict result,
                                           byte_t CHECKED const *dip);

/* Try to find the compilation unit that contains `module_relative_pc'
 * If  no such unit  can be located, `NULL'  will be returned instead. */
FUNDEF WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW_NCX(FCALL cmodule_findunit_from_pc)(struct cmodule const *__restrict self,
                                            uintptr_t module_relative_pc);

/* Try  to   find  the   compilation  unit   that  contains   `dip'
 * If no such unit can be located, `NULL' will be returned instead. */
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW_NCX(FCALL cmodule_findunit_from_dip)(struct cmodule const *__restrict self,
                                             byte_t CHECKED const *dip);

/* Simple wrapper for a pair `REF struct cmodule *mod' + `byte_t const *dip'
 * that can be  used to  reference and store  arbitrary debug-info  objects. */
struct cmoduledip {
	REF struct cmodule *cd_mod; /* [1..1] CModule. */
	byte_t const       *cd_dip; /* [1..1] DIP pointer. */
};
#define cmoduledip_fini(self)           decref((self)->cd_mod)
#define cmoduledip_parser(self, result) cmodule_parser_from_dip((self)->cd_mod, result, (self)->cd_dip)




/************************************************************************/
/* Mixed global/local symbol enumeration/lookup functions               */
/************************************************************************/

struct cmodsyminfo {
	REF struct cmodule         *clv_mod;       /* [1..1] Containing module. */
	struct cmodunit const      *clv_unit;      /* [0..1] Containing module unit. (if available) */
	uintptr_t                   clv_modrel_pc; /* [const] Module-relative PC. */
	struct cmodsym              clv_symbol;    /* Symbol name, namespace, and DIP. */
	/* From inside of  `cmod_symenum_callback_t' callbacks, none  of the  following
	 * fields  have yet  to be  initialized when  `info_loaded == false'. When this
	 * is the case, these fields can be loaded lazily via `cmod_symenum_loadinfo()' */
	di_debuginfo_compile_unit_t clv_cu;        /* Compilation unit debug-info. */
	di_debuginfo_cu_parser_t    clv_parser;    /* Parser. */
	byte_t const               *clv_dip;       /* [0..1] Debug information pointer. */
	union {
		/* The following are selected based upon `clv_parser.dup_comp.dic_tag' */
		struct {                               /* Variable */
			union {
				struct {
					di_debuginfo_location_t v_framebase; /* [valid_if(v_objaddr != _v_objdata)] Frame-base expression. (from the containing `DW_TAG_subprogram', if any) */
					di_debuginfo_location_t v_location;  /* [valid_if(v_objaddr != _v_objdata)] Location expression */
				};
				byte_t _v_objdata[sizeof(di_debuginfo_location_t) * 2]; /* Inline buffer for object data. */
			};
			byte_t const       *v_typeinfo;    /* [0..1] Type information. */
			void               *v_objaddr;     /* [?..?] Object address (or `NULL' when `!v_gotaddr') */
			bool                v_gotaddr;     /* Set to true if `v_gotaddr' is valid. */
		} s_var;                               /* [!cmodsyminfo_istype] Variable or parameter. */
	} clv_data;
};
#define cmodsyminfo_istype(self) cmodsym_istype(&(self)->clv_symbol)
#define cmodsyminfo_isdip(self)  cmodsym_isdip(&(self)->clv_symbol)
#define cmodsyminfo_issip(self)  cmodsym_issip(&(self)->clv_symbol)
#define cmodsyminfo_ismip(self)  cmodsym_ismip(&(self)->clv_symbol)
#define cmodsyminfo_getns(self)  cmodsym_getns(&(self)->clv_symbol)
#define cmodsyminfo_getdip(self) cmodsym_getdip(&(self)->clv_symbol, (self)->clv_mod)
#define cmodsyminfo_getsip(self) cmodsym_getsip(&(self)->clv_symbol, (self)->clv_mod)
#define cmodsyminfo_getmip(self) cmodsym_getmip(&(self)->clv_symbol, (self)->clv_mod)
#define cmodsyminfo_name(self)   cmodsym_name(&(self)->clv_symbol, (self)->clv_mod)



/* Lookup information about a local/global symbol matching the given name.
 * @param: info: [in]  The caller must fill in `clv_mod', `clv_unit' and `clv_modrel_pc'
 *                     NOTE: If not available, you may fill `clv_mod' and `clv_unit' with
 *                           `NULL', and leave `clv_modrel_pc' undefined.
 *               [out] Upon success, all non-[const] fields may have been modified.
 * @param: name: The symbol name that should be searched for.
 * @param: ns:   Symbol namespace (one of `CMODSYM_DIP_NS_*')
 * @return: DBX_EOK:    Success
 * @return: DBX_ENOENT: No local variable `name' exists at `module_relative_pc'
 * @return: DBX_EINTR:  Operation was interrupted. */
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW_NCX(FCALL cmod_syminfo)(/*in|out*/ struct cmodsyminfo *__restrict info,
                                char CHECKED const *name, size_t namelen,
                                uintptr_t ns DFL(CMODSYM_DIP_NS_NORMAL));

/* Same as `cmod_syminfo()', but  the caller is not  required to fill in  information
 * about  any symbol at  all, which are automatically  loaded based on `dbg_current',
 * as well as `dbg_getpcreg(DBG_RT_REGLEVEL_VIEW)'. However, upon success, the caller
 * is  required  to  call `cmod_syminfo_local_fini(info)'  once  returned information
 * is no longer being used.
 * @param: ns: Symbol namespace (one of `CMODSYM_DIP_NS_*')
 * @return: DBX_EOK:    Success
 * @return: DBX_ENOENT: No local variable `name' exists at `module_relative_pc'
 * @return: DBX_EINTR:  Operation was interrupted. */
FUNDEF NONNULL((1)) dbx_errno_t
NOTHROW_NCX(FCALL cmod_syminfo_local)(/*out*/ struct cmodsyminfo *__restrict info,
                                      char CHECKED const *name, size_t namelen,
                                      uintptr_t ns DFL(CMODSYM_DIP_NS_NORMAL));
#define cmod_syminfo_local_fini(info) decref((info)->clv_mod)




/* Symbol enumeration callback prototype (see functions below)
 * NOTE: This callback must not modify `info->clv_parser' before returning.
 *       If  it needs to  parse additional debug  information, this must be
 *       done via a different parser, which may be constructed by doing:
 * >> cmodunit_parser_from_dip(info->clv_unit, info->clv_mod, &NEW_PARSER, DIP);
 * NOTE: This callback must not modify `info->clv_mod' before returning.
 * NOTE: This callback must not modify `info->clv_unit' before returning,
 *       unless `info_loaded' was  false when then  callback was  called.
 * @param: info:        The same info-pointer also passed to `cmod_symenum()',
 *                      which will have  been extended  to include  additional
 *                      information about the symbol being enumerated.
 * @param: info_loaded: Specifies  if  extended  symbol info  has  already been
 *                      loaded, or if this info  (should it be needed) must  be
 *                      loaded manually via a call to `cmod_symenum_loadinfo()'
 * @return: * :         pformatprinter-compatible return value. */
typedef NONNULL_T((1)) ssize_t
(FCALL *cmod_symenum_callback_t)(struct cmodsyminfo *__restrict info,
                                 __BOOL info_loaded);

/* To-be called from inside of `cmod_symenum_callback_t' when
 * `info_loaded == false', and extended symbol information is
 * needed. */
FUNDEF NONNULL((1)) void
NOTHROW_NCX(FCALL cmod_symenum_loadinfo)(struct cmodsyminfo *__restrict info);


/* Flags for `cmod_symenum:scope' */
#define CMOD_SYMENUM_SCOPE_FNORMAL    0x0000
#define CMOD_SYMENUM_SCOPE_FNOLOCAL   0x0001 /* Don't enumerate local variables. */
#define CMOD_SYMENUM_SCOPE_FNOGLOBAL  0x0002 /* Don't enumerate global variables from the current module. */
#define CMOD_SYMENUM_SCOPE_FNOFOREIGN 0x0004 /* Don't enumerate global variables from other modules. */

/* From the point  of view  of `cmod_syminfo()',  enumerate all  symbols who's  names
 * start with `startswith_name...+=startswith_namelen'. When `startswith_namelen==0',
 * all symbols are enumerated.
 * Also note that this function may sporadically stop enumeration before being finished,
 * even when `cb' didn't indicate a negative return value when `dbg_awaituser()' returns
 * true, which is handled the same as enumeration completing normally.
 * NOTE: The `out(undef)' that all non-[const]  fields are undefined upon  return,
 *       with the exception of out-of-band fields (if any), who's contents depends
 *       on what `cb' may or may not have done.
 * @param: info:  Specifications for where to look for symbols, as well as a  cookie-pointer
 *                that is passed to `cb' during invocation (the caller may embed the  symbol
 *                info descriptor inside of a larger structure which can then be re-accessed
 *                via `container_of' from inside of `cb', thus allowing additional arguments
 *                to be passed to the callback function)
 *                The  caller  must fill  in  `clv_mod', `clv_unit'  and  `clv_modrel_pc' before
 *                calling this function. If not available, you may fill `clv_mod' and `clv_unit'
 *                with `NULL', and leave `clv_modrel_pc' undefined.
 * @param: cb:    Callback to invoke for every symbol found.
 * @param: ns:    Symbol namespace (one of `CMODSYM_DIP_NS_*')
 * @param: scope: The scope of symbols that should be enumerated (set of `CMOD_SYMENUM_SCOPE_F*')
 * @return: * :        pformatprinter-compatible accumulation of return values from `cb'
 * @return: DBX_EINTR: Operation was interrupted. */
FUNDEF NONNULL((1, 2)) ssize_t FCALL
cmod_symenum(/*in|out(undef)*/ struct cmodsyminfo *__restrict info,
             cmod_symenum_callback_t cb,
             char CHECKED const *startswith_name,
             size_t startswith_namelen,
             uintptr_t ns DFL(CMODSYM_DIP_NS_NORMAL),
             uintptr_t scope DFL(CMOD_SYMENUM_SCOPE_FNORMAL));

/* Same as `cmod_symenum()', except  this function automatically manages  the
 * input fields of `info' which must normally be filled in by the caller, and
 * will instead fill them in itself, as well as clean them up afterwards.
 * NOTE: _DONT_ call `cmod_syminfo_local_fini(info)' after this function returns!
 *       Any cleanup will  have already  been done internally  by this  function!
 * NOTE: The `in(oob_only)' means that only out-of-band data that is used
 *       by `cb' must be initialized prior to this function being called.
 * NOTE: The `out(undef)' that all non-[const]  fields are undefined upon  return,
 *       with the exception of out-of-band fields (if any), who's contents depends
 *       on what `cb' may or may not have done.
 * @return: * :        pformatprinter-compatible accumulation of return values from `cb'
 * @return: DBX_EINTR: Operation was interrupted. */
FUNDEF NONNULL((1, 2)) ssize_t FCALL
cmod_symenum_local(/*in(oob_only)|out(undef)*/ struct cmodsyminfo *__restrict info,
                   cmod_symenum_callback_t cb,
                   char CHECKED const *startswith_name,
                   size_t startswith_namelen,
                   uintptr_t ns DFL(CMODSYM_DIP_NS_NORMAL),
                   uintptr_t scope DFL(CMOD_SYMENUM_SCOPE_FNORMAL));

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_CMODULE_H */
