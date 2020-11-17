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
#ifndef GUARD_MODDBX_DW_C
#define GUARD_MODDBX_DW_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/rt.h>
#include <kernel/types.h>

#include <hybrid/overflow.h>
#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>

#include <kos/exec/module.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_info.h>

/**/
#include "include/ctype.h"
#include "include/malloc.h"

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN

/* [0..1] Linked list of loaded debug-module objects (cleared during
 *        debugger reset; elements are lazily removed as they are
 *        destroyed) */
PUBLIC struct dw_module *dw_module_list = NULL;

/* [0..1] Cache of already-loaded DW modules. */
INTERN REF struct dw_module *dw_module_cache = NULL;

PRIVATE NONNULL((1)) void
NOTHROW(FCALL cache_module)(struct dw_module *__restrict self) {
	self->dm_cache  = dw_module_cache;
	dw_module_cache = incref(self);
}

/* Clear the internal cache of pre-loaded DW modules (called
 * from `dbx_heap_alloc()' in an attempt to free memory).
 * @param: keep_loaded: When true, keep modules descriptors loaded if they
 *                      are apart of the kernel, or the `dbg_current->t_vm'
 *                      Otherwise, clear all modules from the cache.
 * @return: * : The # of modules that actually got destroyed (i.e. removing
 *              them from the cache caused their refcnt to drop to `0') */
PUBLIC size_t NOTHROW(FCALL dw_module_clearcache)(bool keep_loaded) {
	size_t result = 0;
	struct dw_module **piter, *iter;
	piter = &dw_module_cache;
	while ((iter = *piter) != NULL) {
		if (keep_loaded) {
			/* Check if we should keep this module. */
			struct vm *modvm;
			modvm = module_vm(iter->dm_module,
			                  iter->dm_modtyp);
			if (modvm == &vm_kernel ||
			    modvm == dbg_current->t_vm) {
				/* Don't remove this one. */
				piter = &iter->dm_cache;
				continue;
			}
		}
		/* Remove this one! */
		*piter = iter->dm_cache; /* Unlink */
		/* Drop the cache reference. */
		if (--iter->dm_refcnt == 0) {
			destroy(iter);
			++result;
		}
	}
	return result;
}

/* Destroy the given debug-module. */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL dw_module_fini)(struct dw_module *__restrict self) {
	debug_sections_unlock(&self->dm_sectrefs module_type__arg(self->dm_modtyp));
	module_xdecref(self->dm_module, self->dm_modtyp);
}

PUBLIC NONNULL((1)) void
NOTHROW(FCALL dw_module_destroy)(struct dw_module *__restrict self) {
	if (self->dm_pself) {
		if ((*self->dm_pself = self->dm_next) != NULL)
			self->dm_next->dm_pself = self->dm_pself;
	}
	dw_module_fini(self);
	dbx_free(self);
}


/* Lookup and return a reference to the debug-module descriptor for `mod'
 * @return: * :   A reference to the debug-module descriptor.
 * @return: NULL: Insufficient memory. */
FUNDEF WUNUSED NONNULL((1)) REF struct dw_module *
NOTHROW(FCALL dw_module_get)(module_t *__restrict mod module_type__param(modtype)) {
	REF struct dw_module *result;
	/* Search for an already-loaded module. */
	for (result = dw_module_list; result; result = result->dm_next) {
		if (result->dm_module == mod)
			return incref(result);
	}
	/* Create a new module. */
	result = (REF struct dw_module *)dbx_malloc(sizeof(struct dw_module));
	if unlikely(!result)
		goto done;
	memset(result, 0, sizeof(*result));
	result->dm_next  = dw_module_list;
	result->dm_pself = &dw_module_list;
	if (dw_module_list)
		dw_module_list->dm_pself = &result->dm_next;
	dw_module_list = result;

	result->dm_refcnt = 1;
#if MODULE_TYPE_COUNT >= 2
	result->dm_modtyp = modtype;
#endif /* MODULE_TYPE_COUNT >= 2 */
	module_incref(mod, modtype);
	result->dm_module = mod;
	debug_sections_lock(mod,
	                    &result->dm_sections,
	                    &result->dm_sectrefs
	                    module_type__arg(modtype));
	/* Cache the module so we can find it faster the next time around! */
	cache_module(result);
done:
	return result;
}


FUNDEF WUNUSED REF struct dw_module *
NOTHROW(FCALL dw_module_get_from_pc)(uintptr_t abs_pc) {
	REF struct dw_module *result;
	REF module_t *mod;
	module_type_var(modtype);
	mod = module_ataddr_nx((void const *)abs_pc, modtype);
	if unlikely(!mod)
		return NULL;
	result = dw_module_get(mod module_type__arg(modtype));
	module_decref(mod, modtype);
	return result;
}




/* Initialize a parser from the given debug location. */
PUBLIC NONNULL((1, 2, 3)) dbx_errno_t
NOTHROW(FCALL dw_debugloc_load)(struct dw_debugloc const *__restrict self,
                                di_debuginfo_cu_parser_t *__restrict parser,
                                di_debuginfo_cu_abbrev_t *__restrict abbrev) {
	unsigned int error;
	byte_t const *reader    = self->ddl_di_hdr;
	struct dw_module *mod = self->ddl_module;
	error = debuginfo_cu_parser_loadunit(&reader, mod->dm_sections.ds_debug_info_end,
	                                     di_debug_sections_as_di_debuginfo_cu_parser_sections(&mod->dm_sections),
	                                     parser, abbrev, self->ddl_di_pos);
	if unlikely(error != DEBUG_INFO_ERROR_SUCCESS)
		return DBX_ENOENT;
	return DBX_EOK;
}

/* Initialize the given `parser' for the compilation unit at `module_relative_pc'
 * If this fails, then this function returns `DBX_ENOENT'. Upon success, `parser'
 * will point at the `DW_TAG_compile_unit' component that was loaded into `cu',
 * and the caller should remember `parser->dup_child_depth', and make use of
 * `debuginfo_cu_parser_next()' to advance & load child elements of the compilation unit.
 * @return: DBX_EOK:    Successfully initialized the parser/abbrev.
 * @return: DBX_ENOENT: Failed to initialize the parser/abbrev. */
PUBLIC NONNULL((1, 2, 3, 4)) dbx_errno_t
NOTHROW(KCALL dw_module_loadcu_ex)(struct dw_module const *__restrict self,
                                   /*out*/ di_debuginfo_cu_parser_t *__restrict parser,
                                   /*out*/ di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                   /*out*/ di_debuginfo_compile_unit_t *__restrict cu,
                                   /*in*/ uintptr_t module_relative_pc) {
	unsigned int error;
	uintptr_t cu_offset;
	byte_t const *debug_info_reader;
	error = debugaranges_locate(self->dm_sections.ds_debug_aranges_start,
	                            self->dm_sections.ds_debug_aranges_end,
	                            &cu_offset, module_relative_pc);
	if (error == DEBUG_INFO_ERROR_SUCCESS &&
	    self->dm_sections.ds_debug_info_end > self->dm_sections.ds_debug_info_start &&
	    (size_t)cu_offset < (size_t)(self->dm_sections.ds_debug_info_end -
	                                 self->dm_sections.ds_debug_info_start)) {
		debug_info_reader = self->dm_sections.ds_debug_info_start + cu_offset;
		error = debuginfo_cu_parser_loadunit(&debug_info_reader, self->dm_sections.ds_debug_info_end,
		                                     di_debug_sections_as_di_debuginfo_cu_parser_sections(&self->dm_sections),
		                                     parser, abbrev, NULL);
		if (error == DEBUG_INFO_ERROR_SUCCESS) {
			for (;;) {
				switch (parser->dup_comp.dic_tag) {

				case DW_TAG_compile_unit:
					if (!debuginfo_cu_parser_loadattr_compile_unit(parser, cu)) {
fini_abbrev_and_tryhard:
						debuginfo_cu_abbrev_fini(abbrev);
						goto tryhard;
					}
					return DBX_EOK;

				default:
					debuginfo_cu_parser_skipattr(parser);
					if (!debuginfo_cu_parser_next(parser))
						goto fini_abbrev_and_tryhard;
					break;
				}
			}
		}
	}
	/* Try hard to find the correct compilation unit. */
tryhard:
	debug_info_reader = self->dm_sections.ds_debug_info_start;
	while (debuginfo_cu_parser_loadunit(&debug_info_reader,
	                                    self->dm_sections.ds_debug_info_end,
	                                    di_debug_sections_as_di_debuginfo_cu_parser_sections(&self->dm_sections),
	                                    parser, abbrev, NULL) == DEBUG_INFO_ERROR_SUCCESS) {
		for (;;) {
			switch (parser->dup_comp.dic_tag) {

			case DW_TAG_compile_unit:
				if (!debuginfo_cu_parser_loadattr_compile_unit(parser, cu))
					goto next_cu;
				error = debuginfo_ranges_contains(&cu->cu_ranges, parser,
				                                  cu->cu_ranges.r_startpc,
				                                  module_relative_pc,
				                                  self->dm_sections.ds_debug_ranges_start,
				                                  self->dm_sections.ds_debug_ranges_end);
				if (error == DEBUG_INFO_ERROR_SUCCESS)
					return DBX_EOK;
				break;

			default:
				debuginfo_cu_parser_skipattr(parser);
				if (!debuginfo_cu_parser_next(parser))
					goto next_cu;
				break;
			}
		}
next_cu:
		debuginfo_cu_abbrev_fini(abbrev);
	}
	return DBX_ENOENT;
}


/* Same as `dw_module_loadcu_ex()', but use the current program
 * counter register, as selected by `dbg_getpcreg(DBG_REGLEVEL_VIEW)',
 * and return a reference to the associated module.
 * @return: * :   A reference to the associated module.
 * @return: NULL: Insufficient memory, or no module found. */
PUBLIC WUNUSED NONNULL((1, 2, 3)) REF struct dw_module *
NOTHROW(KCALL dw_module_loadcu)(/*out*/ di_debuginfo_cu_parser_t *__restrict parser,
                                /*out*/ di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                /*out*/ di_debuginfo_compile_unit_t *__restrict cu,
                                /*out_opt*/ uintptr_t *pmodule_relative_pc) {
	REF struct dw_module *result;
	uintptr_t module_relative_pc, abs_pc;
	dbx_errno_t error;
	abs_pc = dbg_getpcreg(DBG_REGLEVEL_VIEW);
	result = dw_module_get_from_pc(abs_pc);
	if unlikely(!result)
		goto done;
	module_relative_pc = abs_pc - module_getloadaddr(result->dm_module, result->dm_modtyp);
	if (pmodule_relative_pc)
		*pmodule_relative_pc = module_relative_pc;
	error = dw_module_loadcu_ex(result, parser, abbrev, cu, module_relative_pc);
	if unlikely(error != DBX_EOK) {
		decref(result);
		result = NULL;
	}
done:
	return result;
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_DW_C */
