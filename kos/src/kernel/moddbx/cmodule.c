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
#ifndef GUARD_MODDBX_CMODULE_C
#define GUARD_MODDBX_CMODULE_C 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

#include <debugger/rt.h>
#include <kernel/driver.h>
#include <kernel/types.h>
#include <kernel/vm/usermod.h>

#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/unaligned.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_info.h>

/**/
#include "include/cmodule.h"
#include "include/malloc.h"

DECL_BEGIN

/* Initialize a debug information CU parser from a given CModule CompilationUnit
 * @param: dip: A pointer to the first component to load, or `NULL' to simply load
 *              the first component following the start of the associated CU descriptor.
 *              When non-NULL, this pointer must be located somewhere between
 *              `cmodunit_di_start(self)' and `cmodunit_di_end(self)'.
 *              If it isn't, then the parser will be initialized to always indicate EOF. */
PUBLIC NONNULL((1, 2, 3)) void
NOTHROW(FCALL cmodunit_parser_from_dip)(struct cmodunit const *__restrict self,
                                        struct cmodule const *__restrict mod,
                                        di_debuginfo_cu_parser_t *__restrict result,
                                        byte_t const *dip) {
	uintptr_t temp;
	byte_t const *reader;
	reader = cmodunit_di_start(self);
	result->dup_cu_info_hdr = reader;
	/* 7.5.1.1   Compilation Unit Header */
	temp = UNALIGNED_GET32((uint32_t const *)reader); /* unit_length */
	reader += 4;
	result->dup_ptrsize = 4;
	if (temp == UINT32_C(0xffffffff)) {
		/* 7.4 32-Bit and 64-Bit DWARF Formats
		 * In the 64-bit DWARF format, an initial length field is 96 bits in size, and has two parts:
		 *  - The first 32-bits have the value 0xffffffff.
		 *  - The following 64-bits contain the actual length represented as an unsigned 64-bit integer. */
		result->dup_ptrsize = 8;
		reader += 8;
	}
	result->dup_cu_info_end = cmodunit_di_end(self);
	result->dup_version = UNALIGNED_GET16((uint16_t const *)reader); /* version */
	reader += 2;
	temp = UNALIGNED_GET32((uint32_t const *)reader); /* debug_abbrev_offset */
	reader += 4;
	if (temp == 0xffffffff)
		reader += 8;
	result->dup_addrsize = *(uint8_t const *)reader; /* address_size */
	reader += 1;
	result->dup_cu_info_pos = reader;
	if (dip) {
		/* If the given pointer is outside the valid range, setup the parser for EOF. */
		if (dip < result->dup_cu_info_hdr ||
		    dip > result->dup_cu_info_end)
			dip = result->dup_cu_info_end;
		result->dup_cu_info_pos = dip;
	}
	reader                = result->dup_cu_info_end;
	result->dup_sections  = di_debug_sections_as_di_debuginfo_cu_parser_sections(&mod->cm_sections);
	result->dup_cu_abbrev = (di_debuginfo_cu_abbrev_t *)&self->cu_abbrev;
	/* Load the first component of the compilation unit. */
	if (!debuginfo_cu_parser_next(result)) {
		/* Fill in a stub/EOF component. */
		result->dup_comp.dic_tag          = 0; /* DW_TAG_... */
		result->dup_comp.dic_haschildren  = DW_CHILDREN_no;
		result->dup_comp.dic_attrib_start = (di_debuginfo_component_attrib_t const *)self->cu_abbrev.dua_abbrev_end;
		result->dup_comp.dic_attrib_end   = (di_debuginfo_component_attrib_t const *)self->cu_abbrev.dua_abbrev_end;
	}
	result->dup_child_depth = 0;
}




PRIVATE NONNULL((1)) void
NOTHROW(FCALL cmodsymtab_fini)(struct cmodsymtab *__restrict self) {
	dbx_free(self->mst_symv);
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL cmodunit_fini)(struct cmodunit *__restrict self) {
	if (self->cu_symbols.mst_symv != (struct cmodsym *)-1)
		cmodsymtab_fini(&self->cu_symbols);
	debuginfo_cu_abbrev_fini(&self->cu_abbrev);
}

/* Destroy the given CModule. (called when its reference counter hits `0') */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL cmodule_destroy)(struct cmodule *__restrict self) {
	size_t i;
	if (self->cm_pself) {
		if ((*self->cm_pself = self->cm_next) != NULL)
			self->cm_next->cm_pself = self->cm_pself;
	}
	debug_sections_unlock(&self->cm_sectrefs module_type__arg(self->cm_modtyp));
	module_decref(self->cm_module, self->cm_modtyp);
	cmodsymtab_fini(&self->cm_symbols);
	for (i = 0; i < self->cm_cuc; ++i)
		cmodunit_fini(&self->cm_cuv[i]);
	dbx_free(self);
}


PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmodule_enum_uservm_except)(struct vm *__restrict self,
                                          cmodule_enum_callback_t cb,
                                          void *cookie,
                                          struct cmodule *skipme) {
#ifdef CONFIG_HAVE_USERMOD
	ssize_t temp, result = 0;
	REF struct usermod *um;
	TRY {
		um = vm_getusermod_above(self, NULL);
	} EXCEPT {
		goto done;
	}
	if likely(um) {
		/* Enumerate modules. */
		do {
			REF struct cmodule *cm;
			cm = cmodule_locate((module_t *)um
			                    module_type__arg(MODULE_TYPE_USRMOD));
			if likely(cm) {
				temp = 0;
				if (cm != skipme)
					temp = (*cb)(cookie, cm);
				decref(cm);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			/* Load the next user-space module. */
			{
				REF struct usermod *next_um;
				TRY {
					next_um = vm_getusermod_next(self, um);
				} EXCEPT {
					decref(um);
					goto done;
				}
				decref(um);
				um = next_um;
			}
		} while (um != NULL);
	}
done:
	return result;
err:
	result = temp;
	goto done;
#else /* CONFIG_HAVE_USERMOD */
	(void)self;
	(void)cb;
	(void)cookie;
	(void)skipme;
	return 0;
#endif /* !CONFIG_HAVE_USERMOD */
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(FCALL cmodule_enum_drivers_except)(cmodule_enum_callback_t cb,
                                           void *cookie,
                                           struct cmodule *skipme) {
	size_t i;
	ssize_t temp, result = 0;
	REF struct driver_state *ds;
	ds = driver_get_state();
	for (i = 0; i < ds->ds_count; ++i) {
		REF struct cmodule *cm;
		cm = cmodule_locate((module_t *)ds->ds_drivers[i]
		                    module_type__arg(MODULE_TYPE_DRIVER));
		if likely(cm) {
			temp = 0;
			if (cm != skipme)
				temp = (*cb)(cookie, cm);
			decref(cm);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
done:
	decref(ds);
	return result;
err:
	result = temp;
	goto done;
}

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
PUBLIC NONNULL((1)) ssize_t
NOTHROW(FCALL cmodule_enum)(cmodule_enum_callback_t cb,
                            void *cookie) {
	ssize_t temp, result = 0;
	REF struct cmodule *pcmodule;
	void *pc = (void *)dbg_getpcreg(DBG_REGLEVEL_VIEW);
	pcmodule = cmodule_ataddr(pc);
	if (pcmodule) {
		result = (*cb)(cookie, pcmodule);
		if (result < 0)
			goto done;
	}
	/* Enumerate other modules in the documented order. */
	if (ADDR_ISKERN(pc)) {
		temp = cmodule_enum_drivers(cb, cookie);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	/* Enumerate user-space modules. */
	if (dbg_current && dbg_current->t_self == dbg_current &&
	    dbg_current->t_vm != NULL && dbg_current->t_vm != &vm_kernel) {
		temp = cmodule_enum_uservm_except(dbg_current->t_vm, cb, cookie, pcmodule);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	if (!ADDR_ISKERN(pc)) {
		temp = cmodule_enum_drivers(cb, cookie);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	xdecref(pcmodule);
	return result;
err:
	result = temp;
	goto done;
}

/* Enumerate all user-space modules mapped within the given vm
 * `self' as CModule objects, and invoke `cb' on each of them. */
PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW(FCALL cmodule_enum_uservm)(struct vm *__restrict self,
                                   cmodule_enum_callback_t cb,
                                   void *cookie) {
	return cmodule_enum_uservm_except(self, cb, cookie, NULL);
}

/* Enumerate all kernel-space drivers as CModule objects, and
 * invoke `cb' on each of them. */
PUBLIC NONNULL((1)) ssize_t
NOTHROW(FCALL cmodule_enum_drivers)(cmodule_enum_callback_t cb,
                                    void *cookie) {
	return cmodule_enum_drivers_except(cb, cookie, NULL);
}






/* Lookup or create the CModule for the given `mod:modtype'
 * If the module has already been loaded, return a reference to
 * the pre-loaded CModule. Otherwise, create and remember a new
 * module which is then kept in-cache. If this step fails due to
 * lack of memory, `NULL' is returned instead. */
PUBLIC WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_locate)(module_t *__restrict mod
                              module_type__param(modtype)) {
	/* TODO */
	COMPILER_IMPURE();
	(void)mod;
	return NULL;
}

/* Return the CModule descriptor for a given `addr', which should be a program counter, or data-pointer.
 * If no such module exists, or its descriptor could not be allocated, return `NULL' instead.
 * This function is a thin wrapper around `module_ataddr_nx()' + `cmodule_locate()' */
PUBLIC WUNUSED NONNULL((1)) REF struct cmodule *
NOTHROW(FCALL cmodule_ataddr)(void const *addr) {
	REF struct cmodule *result;
	REF module_t *mod;
	module_type_var(modtype);
	mod = module_ataddr_nx(addr, modtype);
	if (!mod)
		return NULL;
	/* Lookup the CModule for the `mod' that we've found. */
	result = cmodule_locate(mod module_type__arg(modtype));
	module_decref(mod, modtype);
	return result;
}

/* Return the CModule for `dbg_getpcreg(DBG_REGLEVEL_VIEW)'
 * Same as `cmodule_ataddr(dbg_getpcreg(DBG_REGLEVEL_VIEW))' */
PUBLIC WUNUSED REF struct cmodule *
NOTHROW(FCALL cmodule_current)(void) {
	void const *pc;
	REF struct cmodule *result;
	pc     = (void const *)dbg_getpcreg(DBG_REGLEVEL_VIEW);
	result = cmodule_ataddr(pc);
	return result;
}


/* Lookup the given `name' within `self' */
PRIVATE WUNUSED NONNULL((1, 2)) struct cmodsym *
NOTHROW(FCALL cmodsymtab_lookup)(struct cmodsymtab const *__restrict self,
                                 char const *__restrict name, size_t namelen,
                                 uintptr_t ns) {
	struct cmodsym *result;
	size_t lo, hi;
	lo = 0, hi = self->mst_symc;
	while (lo < hi) {
		size_t index;
		int cmp;
		index  = (lo + hi) / 2;
		result = &self->mst_symv[index];
		/* FIXME: compare right here assumes that `name...+=namelen'
		 *        does not contain any NUL characters!
		 * -> There really needs to be a function `strcmpl(a, b, blen)'
		 *    that ensures `strlen(a) == blen && memcmp(a, b, blen) == 0',
		 *    but still returns -1,0,+1 like memcmp(), while assuming that
		 *    any character from b outside of b...+=blen is equal to NUL. */
		cmp = memcmp(name, result->cms_name, namelen * sizeof(char));
		if (cmp == 0 && result->cms_name[namelen] != 0)
			cmp = -1; /* key < symbol */
		if (cmp < 0) {
			hi = index;
		} else if (cmp > 0) {
			lo = index + 1;
		} else {
			/* Found it! */
			/* TODO: Deal with multiple symbols of the same name by looking at `ns'!
			 *       Note that right now, other symbols with the same name may both
			 *       be located before and after `result'! */
			(void)ns; /* TODO */
			return result;
		}
	}
	/* Not found... */
	return NULL;
}


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
PUBLIC WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cmodule_loadsyms)(struct cmodule *__restrict self) {
	/* TODO */
	COMPILER_IMPURE();
	(void)self;
	return DBX_EINTR;
}

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
PUBLIC WUNUSED NONNULL((1, 2)) struct cmodsym const *
NOTHROW(FCALL cmodule_getsym)(struct cmodule *__restrict self,
                              char const *__restrict name,
                              size_t namelen, uintptr_t ns) {
	struct cmodsym const *result;

	/* First up: Make sure that module symbols have been loaded. */
	if (cmodule_loadsyms(self) != DBX_EOK)
		return NULL;

	/* Now check the per-module (global) symbol table for `name' */
	result = cmodsymtab_lookup(&self->cm_symbols, name, namelen, ns);

	/* Check if the symbol we've found is in conflict with other,
	 * per-CU symbols. If this is the case, then we must lookup the symbol
	 * once again within the table associated with the currently viewed PC
	 * pointer, as returned by `dbg_getpcreg(DBG_REGLEVEL_VIEW)' */
	if (result && (cmodsym_getns(result) & CMODSYM_DIP_NS_FCONFLICT)) {
		void const *pc;
		pc = (void const *)dbg_getpcreg(DBG_REGLEVEL_VIEW);
		if (pc >= (void const *)cmodule_getloadstart(self) &&
		    pc <  (void const *)cmodule_getloadend(self)) {
			uintptr_t module_relative_pc;
			struct cmodunit *cu;
			module_relative_pc = (uintptr_t)pc - cmodule_getloadaddr(self);
			cu = cmodule_findunit_from_pc(self, module_relative_pc);
			if (cu != NULL) {
				struct cmodsym const *cu_symbol;
				cu_symbol = cmodsymtab_lookup(&cu->cu_symbols, name, namelen, ns);
				if (cu_symbol != NULL)
					return cu_symbol;
			}
		}
	}
	return result;
}



struct cmodule_getsym_global_data {
	struct cmodsym const *result;
	char const           *name;
	size_t                namelen;
	REF struct cmodule  **presult_module;
	uintptr_t             ns;
};

PRIVATE NONNULL((2)) ssize_t
NOTHROW(FCALL cmodule_getsym_global_callback)(void *cookie,
                                              struct cmodule *__restrict mod) {
	struct cmodsym const *sym;
	struct cmodule_getsym_global_data *arg;
	arg = (struct cmodule_getsym_global_data *)cookie;
	/* Lookup a symbol within the given `mod' */
	sym = cmodule_getsym(mod, arg->name, arg->namelen, arg->ns);
	if (sym != NULL) {
		/* Found it! (write-back results) */
		*arg->presult_module = incref(mod);
		arg->result          = sym;
		return -1; /* Stop enumeration */
	}
	return 0;
}


/* Resolve a global symbol by finding its containing module, and returning
 * a pointer to the associated symbol object. This function is implemented
 * as a combination of `cmodule_enum()' + `cmodule_getsym()', meaning that
 * symbol resolution order matches what is done by `cmodule_enum()'
 * @return: * :   Success. (`*presult_module' was populated with a reference)
 * @return: NULL: Error: Insufficient memory.
 * @return: NULL: Error: No such symbol.
 * @return: NULL: Error: Operation was interrupted. */
PUBLIC WUNUSED NONNULL((1, 3)) struct cmodsym const *
NOTHROW(FCALL cmodule_getsym_global)(char const *__restrict name, size_t namelen,
                                     REF struct cmodule **__restrict presult_module,
                                     uintptr_t ns) {
	struct cmodule_getsym_global_data data;
	data.result         = NULL;
	data.name           = name;
	data.namelen        = namelen;
	data.presult_module = presult_module;
	data.ns             = ns;
	cmodule_enum(&cmodule_getsym_global_callback, &data);
	return data.result;
}




/* Initialize a debug information CU parser to load debug information for a component
 * located at `dip' within the `.debug_info' mapping of `self'. For this
 * purpose, this function will locate the CU that contains `dip', and proceed
 * to call `cmodunit_parser()' to initialize `result'. If the given `dip'
 * is not apart of any of the CUs of `self', then `result' will be initialized
 * to always indicate EOF.
 * @param: dip: DebugInfoPointer. (s.a. `cmodunit_parser_from_dip()') */
PUBLIC NONNULL((1, 2, 3)) void
NOTHROW(FCALL cmodule_parser_from_dip)(struct cmodule const *__restrict self,
                                       di_debuginfo_cu_parser_t *__restrict result,
                                       byte_t const *__restrict dip) {
	struct cmodunit *cu;
	/* Try to find the CU associated with `dip' */
	cu = cmodule_findunit_from_dip(self, dip);
	if unlikely(!cu) {
		/* Special case: Bad DIP pointer. */
		memset(result, 0, sizeof(*result));
		return;
	}
	/* Initialize the parser from `cu' and `dip'. */
	cmodunit_parser_from_dip(cu, self, result, dip);
}


PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_pc_fallback)(struct cmodule const *__restrict self,
                                                 uintptr_t module_relative_pc) {
	size_t i;
	/* Fallback: Manually search through all CUs and find one that
	 *           has a `DW_TAG_compile_unit' with a range-list which
	 *           in turn contains `module_relative_pc' */
	for (i = 0; i < self->cm_cuc; ++i) {
		unsigned int error;
		di_debuginfo_cu_parser_t parser;
		di_debuginfo_compile_unit_t cu;
		cmodunit_parser_from_dip(&self->cm_cuv[i], self, &parser, NULL);
		/* Find the nearest CU. */
		if (parser.dup_comp.dic_tag != DW_TAG_compile_unit) {
			debuginfo_cu_parser_skipattr(&parser);
			if (!debuginfo_cu_parser_next(&parser))
				goto next_cu;
		}
		/* Load attributes of this CU. */
		if (!debuginfo_cu_parser_loadattr_compile_unit(&parser, &cu))
			goto next_cu;
		/* Check if the given `module_relative_pc' is contained by this CU. */
		error = debuginfo_ranges_contains(&cu.cu_ranges, &parser,
		                                  cu.cu_ranges.r_startpc, module_relative_pc,
		                                  self->cm_sections.ds_debug_ranges_start,
		                                  self->cm_sections.ds_debug_ranges_end);
		if (error == DEBUG_INFO_ERROR_SUCCESS)
			return (struct cmodunit *)&self->cm_cuv[i]; /* Found it! */
next_cu:
		;
	}
	return NULL;
}

/* Try to find the compilation unit that contains `module_relative_pc'
 * If no such unit can be located, `NULL' will be returned instead. */
PUBLIC WUNUSED NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_pc)(struct cmodule const *__restrict self,
                                        uintptr_t module_relative_pc) {
	struct cmodunit *result;
	/* Try to make use of .debug_aranges to find the proper CU. */
	if (self->cm_sections.ds_debug_aranges_start < self->cm_sections.ds_debug_aranges_end) {
		uintptr_t debuginfo_cu_offset;
		unsigned int error;
		error = debugaranges_locate(self->cm_sections.ds_debug_aranges_start,
		                            self->cm_sections.ds_debug_aranges_end,
		                            &debuginfo_cu_offset,
		                            module_relative_pc);
		if (error == DEBUG_INFO_ERROR_SUCCESS) {
			byte_t const *cu_start;
			cu_start = self->cm_sections.ds_debug_info_start + debuginfo_cu_offset;
			result = cmodule_findunit_from_dip(self, cu_start);
		}
	}
	/* Fallback */
	result = cmodule_findunit_from_pc_fallback(self, module_relative_pc);
	return result;
}


/* Try to find the compilation unit that contains `dip'
 * If no such unit can be located, `NULL' will be returned instead. */
PUBLIC WUNUSED ATTR_PURE NONNULL((1)) struct cmodunit *
NOTHROW(FCALL cmodule_findunit_from_dip)(struct cmodule const *__restrict self,
                                         byte_t const *__restrict dip) {
	struct cmodunit const *result;
	size_t lo, hi;
	lo = 0, hi = self->cm_cuc;
	while (lo < hi) {
		size_t index;
		index  = (lo + hi) / 2;
		result = &self->cm_cuv[index];
		if (dip < cmodunit_di_start(result))
			hi = index;
		else if (dip >= cmodunit_di_end(result))
			lo = index + 1;
		else {
			/* Found it! */
			return (struct cmodunit *)result;
		}
	}
	return NULL;
}

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_CMODULE_C */
