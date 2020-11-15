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
#ifndef GUARD_MODDBX_CSYMBOL_C
#define GUARD_MODDBX_CSYMBOL_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/input.h> /* dbg_awaituser */
#include <debugger/rt.h>

#include <stddef.h>
#include <string.h>

/**/
#include "include/cexpr.h"
#include "include/csymbol.h"
#include "include/ctype.h"

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN

/* Finalize the given C-symbol. */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL csymbol_fini)(struct csymbol *__restrict self) {
	STATIC_ASSERT(offsetof(struct csymbol, cs_expr.e_type) ==
	              offsetof(struct csymbol, cs_type));
	switch (self->cs_kind) {

	case CSYMBOL_KIND_EXPR:
		cvalue_cfiexpr_fini(&self->cs_expr.e_expr);
		ATTR_FALLTHROUGH
	case CSYMBOL_KIND_TYPE:
		ctyperef_fini(&self->cs_type);
		break;

	default:
		break;
	}
}

/* Initialize a c-symbol from c-symbol data. */
PUBLIC WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL csymbol_from_csymbol_data)(struct csymbol *__restrict self,
                                         struct csymbol_data const *__restrict data) {
	dbx_errno_t result;
	self->cs_kind = data->csd_symkind;
	switch (data->csd_symkind) {

	case CSYMBOL_KIND_NONE:
		result = DBX_EOK;
		break;

	case CSYMBOL_KIND_EXPR: {
		result = ctype_fromdw(data->csd_module, &data->csd_parser,
		                      data->csd_symexpr.se_type,
		                      &self->cs_expr.e_type);
		if unlikely(result != DBX_EOK)
			break;
		self->cs_expr.e_expr.v_module            = incref(data->csd_module);
		self->cs_expr.e_expr.v_expr              = data->csd_symexpr.se_expr;
		self->cs_expr.e_expr.v_framebase         = data->csd_symexpr.se_framebase;
		self->cs_expr.e_expr.v_cu_ranges_startpc = data->csd_cu.cu_ranges.r_startpc;
		self->cs_expr.e_expr.v_cu_addr_base      = data->csd_cu.cu_addr_base;
		self->cs_expr.e_expr.v_addrsize          = data->csd_parser.dup_addrsize;
		self->cs_expr.e_expr.v_ptrsize           = data->csd_parser.dup_ptrsize;
		self->cs_expr.e_expr.v_objaddr           = data->csd_symexpr.se_objaddr;
	}	break;

	case CSYMBOL_KIND_TYPE: {
		result = ctype_fromdw(data->csd_module, &data->csd_parser,
		                      data->csd_symtype, &self->cs_type);
	}	break;

	default:
		return DBX_EINTERN;
	}
	return result;
}

/* @param: module_relative_pc: Module-relative PC to use for the
 *                             purpose of scanning for local variables.
 * @param: symdat: Symbol data. Only the following fields have been initialized:
 *                  - csd_module
 *                  - csd_parser
 *                  - csd_cu
 * @param: scopes: Set of `CSYMBOL_SCOPE_LOCAL | CSYMBOL_SCOPE_CU' */
PRIVATE WUNUSED NONNULL((1, 3)) ssize_t
NOTHROW(FCALL enum_cu)(csymbol_enum_callback_t cb, void *arg,
                       struct csymbol_data *__restrict symdat,
                       uintptr_t module_relative_pc,
                       unsigned int scopes) {
	unsigned int error;
	ssize_t temp, result = 0;
	uintptr_t cu_depth;
	if (dbg_awaituser())
		goto done;
	cu_depth = symdat->csd_parser.dup_child_depth;
	if (!debuginfo_cu_parser_next(&symdat->csd_parser))
		goto done;
again_cu_component:
	while (symdat->csd_parser.dup_child_depth > cu_depth) {
		if (dbg_awaituser())
			goto done;
		/* Scan components of this CU. */
		switch (symdat->csd_parser.dup_comp.dic_tag) {

		case DW_TAG_subprogram: {
			di_debuginfo_subprogram_t sp;
			uintptr_t subprogram_depth;
			if (!(scopes & CSYMBOL_SCOPE_LOCAL))
				goto generic_cu_child;
			if (!debuginfo_cu_parser_loadattr_subprogram(&symdat->csd_parser, &sp))
				goto generic_cu_child;
			subprogram_depth = symdat->csd_parser.dup_child_depth;
			/* Check if the given pointer is apart of this sub-program. */
			error = debuginfo_ranges_contains(&sp.sp_ranges, &symdat->csd_parser,
			                                  symdat->csd_cu.cu_ranges.r_startpc,
			                                  module_relative_pc,
			                                  symdat->csd_module->dm_sections.ds_debug_ranges_start,
			                                  symdat->csd_module->dm_sections.ds_debug_ranges_end);
			if (error != DEBUG_INFO_ERROR_SUCCESS) {
				/* Must be apart of a different sub-program. */
				for (;;) {
					if (!debuginfo_cu_parser_next(&symdat->csd_parser))
						goto done;
					if (symdat->csd_parser.dup_child_depth <= subprogram_depth)
						goto again_cu_component;
					debuginfo_cu_parser_skipattr(&symdat->csd_parser);
				}
			}
			for (;;) {
				if (!debuginfo_cu_parser_next(&symdat->csd_parser))
					goto done_subprogram;
again_subprogram_component:
				if (symdat->csd_parser.dup_child_depth <= subprogram_depth)
					goto done_subprogram;
				if (dbg_awaituser())
					goto done_subprogram;
				switch (symdat->csd_parser.dup_comp.dic_tag) {

				case DW_TAG_variable:
				case DW_TAG_formal_parameter: {
					di_debuginfo_variable_t var;
					if (debuginfo_cu_parser_loadattr_variable(&symdat->csd_parser, &var)) {
						if (!var.v_name)
							var.v_name = var.v_rawname;
						if (var.v_name) {
							symdat->csd_symkind              = CSYMBOL_KIND_EXPR;
							symdat->csd_name                 = var.v_name;
							symdat->csd_symexpr.se_type      = var.v_type;
							symdat->csd_symexpr.se_expr      = var.v_location;
							symdat->csd_symexpr.se_framebase = sp.sp_frame_base;
							symdat->csd_symexpr.se_objaddr   = NULL;
							/* Enumerate this variable. */
							temp = (*cb)(arg, symdat);
							if unlikely(temp < 0)
								goto err;
							result += temp;
						}
					}
				}	break;

				case DW_TAG_inlined_subroutine:
				case DW_TAG_try_block:
				case DW_TAG_catch_block:
				case DW_TAG_lexical_block: {
					di_debuginfo_lexical_block_t block;
					if (debuginfo_cu_parser_loadattr_lexical_block(&symdat->csd_parser, &block)) {
						error = debuginfo_ranges_contains(&block.lb_ranges, &symdat->csd_parser,
						                                  symdat->csd_cu.cu_ranges.r_startpc,
						                                  module_relative_pc,
						                                  symdat->csd_module->dm_sections.ds_debug_ranges_start,
						                                  symdat->csd_module->dm_sections.ds_debug_ranges_end);
						if (error != DEBUG_INFO_ERROR_SUCCESS) {
							/* Must be apart of a different scope. */
							uintptr_t block_depth;
							block_depth = symdat->csd_parser.dup_child_depth;
							for (;;) {
								if (!debuginfo_cu_parser_next(&symdat->csd_parser))
									goto done;
								if (symdat->csd_parser.dup_child_depth <= block_depth)
									goto again_subprogram_component;
								debuginfo_cu_parser_skipattr(&symdat->csd_parser);
							}
						}
					}
				}	break;

				default:
					debuginfo_cu_parser_skipattr(&symdat->csd_parser);
					break;
				}
			}
done_subprogram:
			goto done;
		}	break;

		/* TODO: Enumerate types! */

		default:
generic_cu_child:
			debuginfo_cu_parser_skipattr(&symdat->csd_parser);
/*next_cu_component:*/
			if (!debuginfo_cu_parser_next(&symdat->csd_parser))
				goto done;
			break;
		}
	}
done:
	return result;
err:
	return temp;
}

/* @param: symdat: Symbol data. Only the following fields have been initialized:
 *                  - csd_module */
PRIVATE WUNUSED NONNULL((1, 3, 4, 5)) ssize_t
NOTHROW(FCALL enum_all_cus)(csymbol_enum_callback_t cb, void *arg,
                            struct csymbol_data *__restrict symdat,
                            di_debuginfo_cu_abbrev_t *__restrict abbrev,
                            di_debuginfo_ranges_t const *__restrict exclude) {
	ssize_t temp, result = 0;
	byte_t const *reader;
	di_debuginfo_compile_unit_t cu;
	reader = symdat->csd_module->dm_sections.ds_debug_info_start;
	while (debuginfo_cu_parser_loadunit(&reader, symdat->csd_module->dm_sections.ds_debug_info_end,
	                                    di_debug_sections_as_di_debuginfo_cu_parser_sections(&symdat->csd_module->dm_sections),
	                                    &symdat->csd_parser, abbrev, NULL) == DEBUG_INFO_ERROR_SUCCESS) {
		for (;;) {
			if (dbg_awaituser()) {
				debuginfo_cu_abbrev_fini(abbrev);
				return result;
			}
			switch (symdat->csd_parser.dup_comp.dic_tag) {

			case DW_TAG_compile_unit:
				if (!debuginfo_cu_parser_loadattr_compile_unit(&symdat->csd_parser, &cu))
					goto next_cu;
				if (memcmp(&cu.cu_ranges, exclude, sizeof(di_debuginfo_ranges_t)) == 0)
					goto next_cu;
				/* Enumerate this CU. */
				temp = enum_cu(cb, arg, symdat, (uintptr_t)-1, CSYMBOL_SCOPE_CU);
				if (temp < 0)
					goto err;
				result += temp;
				goto next_root;

			default:
				debuginfo_cu_parser_skipattr(&symdat->csd_parser);
next_root:
				if (!debuginfo_cu_parser_next(&symdat->csd_parser))
					goto next_cu;
				break;
			}
		}
next_cu:
		debuginfo_cu_abbrev_fini(abbrev);
		if (dbg_awaituser())
			break;
	}
	return result;
err:
	debuginfo_cu_abbrev_fini(abbrev);
	return temp;
}

/* Mask for scopes that can be enumerated. */
PUBLIC unsigned int csymbol_scopemask = 0;


/* Enumerate C-symbols from the current point-of-view:
 *   CSYMBOL_SCOPE_CU:   The scope of the current compilation unit
 *   CSYMBOL_SCOPE_MOD:  The PUBLIC/INTERN scope of the current module
 * if (ADDR_ISUSER(CURRENT_PC)) {
 *   CSYMBOL_SCOPE_USER: The PUBLIC/INTERN scope within any loaded user-space module
 *   CSYMBOL_SCOPE_KERN: The PUBLIC/INTERN scope within any loaded kernel-space module
 * } else {
 *   CSYMBOL_SCOPE_KERN: The PUBLIC/INTERN scope within any loaded kernel-space module
 *   CSYMBOL_SCOPE_USER: The PUBLIC/INTERN scope within any loaded user-space module
 * }
 * @return: * : The sum of return values of `cb'
 * @return: <0: The immediate propagation of the first negative return value of `cb' */
PUBLIC NONNULL((1)) ssize_t
NOTHROW(FCALL csymbol_enum)(csymbol_enum_callback_t cb, void *arg,
                            unsigned int scopes) {
	ssize_t temp, result = 0;
	struct csymbol_data symdat;
	di_debuginfo_cu_abbrev_t abbrev;
	di_debuginfo_ranges_t exclude;
	symdat.csd_module = NULL;
	scopes &= csymbol_scopemask;
	if (scopes & (CSYMBOL_SCOPE_LOCAL | CSYMBOL_SCOPE_CU | CSYMBOL_SCOPE_MOD)) {
		uintptr_t abs_pc, module_relative_pc;
		abs_pc            = dbg_getpcreg(DBG_REGLEVEL_VIEW);
		symdat.csd_module = debugmodule_get_from_pc(abs_pc);
		if (scopes & (CSYMBOL_SCOPE_LOCAL | CSYMBOL_SCOPE_CU)) {
			module_relative_pc = abs_pc - module_getloadaddr(symdat.csd_module->dm_module, symdat.csd_module->dm_modtyp);
			if (debugmodule_loadcu_ex(symdat.csd_module, &symdat.csd_parser, &abbrev,
			                          &symdat.csd_cu, module_relative_pc) != DBX_EOK)
				goto do_scan_all_cus_of_mod;
			result = enum_cu(cb, arg, &symdat, module_relative_pc, scopes);
			debuginfo_cu_abbrev_fini(&abbrev);
			if (result < 0)
				goto done;
			if (scopes & CSYMBOL_SCOPE_MOD) {
				memcpy(&exclude, &symdat.csd_cu, sizeof(exclude));
				temp = enum_all_cus(cb, arg, &symdat, &abbrev, &exclude);
				if (temp < 0)
					goto err;
				result += temp;
			}
		} else {
do_scan_all_cus_of_mod:
			memset(&exclude, 0, sizeof(exclude));
			result = enum_all_cus(cb, arg, &symdat, &abbrev, &exclude);
		}
	}
	/* TODO: Enumerate all user-space and kernel-space modules,
	 *       but exclude `mod' (if that one's non-NULL) */


done:
	xdecref(symdat.csd_module);
	return result;
err:
	xdecref(symdat.csd_module);
	return temp;
}



struct csymbol_lookup_data {
	char const             *cld_name;    /* [1..1] name */
	size_t                  cld_namelen; /* [1..1] namelen */
	/*out*/ struct csymbol *cld_result;  /* [1..1] result */
	unsigned int            cld_ns;      /* ns */
	dbx_errno_t             cld_errno;   /* error */
};

/* Check if `self' belongs to `ns'
 * @param: ns: One of `CSYMBOL_LOOKUP_*' */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL csymbol_data_isns)(struct csymbol_data const *__restrict self,
                                 unsigned int ns) {
	switch (ns) {

	case CSYMBOL_LOOKUP_TYPE:
		if (self->csd_symkind != CSYMBOL_KIND_TYPE)
			goto nope;
		break;

	case CSYMBOL_LOOKUP_STRUCT:
		if (self->csd_symkind != CSYMBOL_KIND_TYPE)
			goto nope;
		if (self->csd_parser.dup_comp.dic_tag != DW_TAG_structure_type)
			goto nope;
		break;

	case CSYMBOL_LOOKUP_UNION:
		if (self->csd_symkind != CSYMBOL_KIND_TYPE)
			goto nope;
		if (self->csd_parser.dup_comp.dic_tag != DW_TAG_union_type)
			goto nope;
		break;

	case CSYMBOL_LOOKUP_CLASS:
		if (self->csd_symkind != CSYMBOL_KIND_TYPE)
			goto nope;
		if (self->csd_parser.dup_comp.dic_tag != DW_TAG_class_type)
			goto nope;
		break;

	case CSYMBOL_LOOKUP_ENUM:
		if (self->csd_symkind != CSYMBOL_KIND_TYPE)
			goto nope;
		if (self->csd_parser.dup_comp.dic_tag != DW_TAG_enumeration_type)
			goto nope;
		break;

	default:
		break;
	}
	return true;
nope:
	return false;
}


PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW(FCALL csymbol_lookup_callback)(void *arg, struct csymbol_data const *__restrict data) {
	struct csymbol_lookup_data *cookie;
	cookie = (struct csymbol_lookup_data *)arg;
	if (strlen(data->csd_name) != cookie->cld_namelen)
		return 0;
	if (memcmp(data->csd_name, cookie->cld_name, cookie->cld_namelen) != 0)
		return 0;
	/* Found the symbol! Now check if it has the correct type. */
	if (!csymbol_data_isns(data, cookie->cld_ns))
		return 0;
	cookie->cld_errno = csymbol_from_csymbol_data(cookie->cld_result, data);
	return -1;
}

/* Lookup a C-symbol, given its name, as well as namespace association.
 * For this purpose, scan for types matching `name' in debug info
 * at the following locations (in order):
 *   CSYMBOL_SCOPE_CU:   The scope of the current compilation unit
 *   CSYMBOL_SCOPE_MOD:  The PUBLIC/INTERN scope of the current module
 * if (ADDR_ISUSER(CURRENT_PC)) {
 *   CSYMBOL_SCOPE_USER: The PUBLIC/INTERN scope within any loaded user-space module
 *   CSYMBOL_SCOPE_KERN: The PUBLIC/INTERN scope within any loaded kernel-space module
 * } else {
 *   CSYMBOL_SCOPE_KERN: The PUBLIC/INTERN scope within any loaded kernel-space module
 *   CSYMBOL_SCOPE_USER: The PUBLIC/INTERN scope within any loaded user-space module
 * }
 * @param: scopes:  Set of `CSYMBOL_SCOPE_*'
 * @param: ns:      One of `CSYMBOL_LOOKUP_*'
 * @return: DBX_EOK:    Success. (`result' was filled in)
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No symbol matches the given `name'. */
PUBLIC WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL csymbol_lookup)(char const *name, size_t namelen,
                              /*out*/ struct csymbol *__restrict result,
                              unsigned int scopes, unsigned int ns) {
	struct csymbol_lookup_data data;
	data.cld_name    = name;
	data.cld_namelen = namelen;
	data.cld_result  = result;
	data.cld_ns      = ns;
	if (!csymbol_enum(&csymbol_lookup_callback, &data, scopes))
		return DBX_ENOENT;
	return data.cld_errno;
}




DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_CSYMBOL_C */
