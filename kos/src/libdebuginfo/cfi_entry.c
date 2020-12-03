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
#ifndef GUARD_LIBDEBUGINFO_CFI_ENTRY_C
#define GUARD_LIBDEBUGINFO_CFI_ENTRY_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/unaligned.h>

#include <kos/except.h>
#include <kos/exec/module.h>
#include <kos/types.h>
#include <sys/param.h>

#include <alloca.h>
#include <stddef.h>
#include <string.h>

#include <libdebuginfo/cfi_entry.h>
#include <libunwind/cfi.h>

#include "cfi_entry.h"
#include "debug_aranges.h"
#include "debug_info.h"
#include "unwind.h"

DECL_BEGIN

#ifndef __KERNEL__
PRIVATE void *libunwind = NULL;
INTERN WUNUSED void *CC dlopen_libunwind(void) {
	void *lu = ATOMIC_READ(libunwind);
	if (!lu) {
		void *real_lu;
		lu = dlopen(LIBUNWIND_LIBRARY_NAME, RTLD_LOCAL);
		if unlikely(!lu)
			goto done;
		real_lu = ATOMIC_CMPXCH_VAL(libunwind, NULL, lu);
		if unlikely(real_lu) {
			dlclose(lu);
			lu = real_lu;
		}
	}
done:
	return lu;
}

PRIVATE PUNWIND_EMULATOR_EXEC /*     */ pdyn_unwind_emulator_exec           = NULL;
PRIVATE PUNWIND_EMULATOR_EXEC_AUTOSTACK pdyn_unwind_emulator_exec_autostack = NULL;
PRIVATE PUNWIND_INSTRUCTION_SUCC /*  */ pdyn_unwind_instruction_succ        = NULL;
PRIVATE PDEBUGINFO_LOCATION_SELECT /**/ pdyn_debuginfo_location_select      = NULL;
PRIVATE PUNWIND_STE_ADDR /*          */ pdyn_unwind_ste_addr                = NULL;
PRIVATE PUNWIND_STE_READ /*          */ pdyn_unwind_ste_read                = NULL;
#define unwind_emulator_exec           (*pdyn_unwind_emulator_exec)
#define unwind_emulator_exec_autostack (*pdyn_unwind_emulator_exec_autostack)
#define unwind_instruction_succ        (*pdyn_unwind_instruction_succ)
#define debuginfo_location_select      (*pdyn_debuginfo_location_select)
#define unwind_ste_addr                (*pdyn_unwind_ste_addr)
#define unwind_ste_read                (*pdyn_unwind_ste_read)

PRIVATE bool CC load_libunwind(void) {
	void *lu;
	if (pdyn_unwind_emulator_exec)
		return true;
	COMPILER_BARRIER();
	lu = dlopen_libunwind();
	if unlikely(!lu)
		goto nope;
	COMPILER_BARRIER();
#define LOAD(ptr, name)                               \
	if ((*(void **)&(ptr) = dlsym(lu, name)) == NULL) \
		goto nope

	/* Lazily load functions from libunwind. */
	LOAD(pdyn_unwind_ste_read, "unwind_ste_read");
	LOAD(pdyn_unwind_ste_addr, "unwind_ste_addr");
	LOAD(pdyn_debuginfo_location_select, "debuginfo_location_select");
	LOAD(pdyn_unwind_instruction_succ, "unwind_instruction_succ");
	LOAD(pdyn_unwind_emulator_exec_autostack, "unwind_emulator_exec_autostack");
	COMPILER_BARRIER();
	LOAD(pdyn_unwind_emulator_exec, "unwind_emulator_exec");

	COMPILER_WRITE_BARRIER();
#undef LOAD
	return true;
nope:
	return false;
}

#endif /* !__KERNEL__ */

struct unwind_register {
	unwind_regno_t ur_regno;                             /* Register number. */
	union {
		byte_t     ur_data[CFI_UNWIND_REGISTER_MAXSIZE]; /* Unwind register data. */
		uintptr_t  ur_word;                              /* Unwind register data word. */
	};
};

struct cfientry_sections {
	/*BEGIN:compat(unwind_emulator_sections_t)*/
	__byte_t const *ds_eh_frame_start;      /* [0..1][valid_if(:ce_s_eh_frame)] `.eh_frame' start */
	__byte_t const *ds_eh_frame_end;        /* [0..1][valid_if(:ce_s_eh_frame)] `.eh_frame' end */
	__byte_t const *ds_debug_frame_start;   /* [0..1][valid_if(:ce_s_debug_frame)] `.debug_frame' start */
	__byte_t const *ds_debug_frame_end;     /* [0..1][valid_if(:ce_s_debug_frame)] `.debug_frame' end */
	__byte_t const *ds_debug_addr_start;    /* [0..1][valid_if(:ce_s_debug_addr)] `.debug_addr' start */
	__byte_t const *ds_debug_addr_end;      /* [0..1][valid_if(:ce_s_debug_addr)] `.debug_addr' end */
	/*BEGIN:compat(di_debuginfo_cu_parser_sections_t)*/
	__byte_t const *ds_debug_loc_start;     /* [0..1][valid_if(:ce_s_debug_loc)] `.debug_loc' start */
	__byte_t const *ds_debug_loc_end;       /* [0..1][valid_if(:ce_s_debug_loc)] `.debug_loc' end */
	__byte_t const *ds_debug_abbrev_start;  /* [0..1][const] `.debug_abbrev' start */
	__byte_t const *ds_debug_abbrev_end;    /* [0..1][const] `.debug_abbrev' end */
	__byte_t const *ds_debug_info_start;    /* [0..1][const] `.debug_info' start */
	__byte_t const *ds_debug_info_end;      /* [0..1][const] `.debug_info' end */
	/*END:compat(unwind_emulator_sections_t)*/
	__byte_t const *ds_debug_str_start;     /* [0..0][const] Always NULL */
	__byte_t const *ds_debug_str_end;       /* [0..0][const] Always NULL */
	/*END:compat(di_debuginfo_cu_parser_sections_t)*/
	__byte_t const *ds_debug_aranges_start; /* [0..1][const] `.debug_aranges' start */
	__byte_t const *ds_debug_aranges_end;   /* [0..1][const] `.debug_aranges' end */
	__byte_t const *ds_debug_ranges_start;  /* [0..1][valid_if(:ce_s_debug_ranges)] `.debug_ranges' start */
	__byte_t const *ds_debug_ranges_end;    /* [0..1][valid_if(:ce_s_debug_ranges)] `.debug_ranges' end */
};
#define cfientry_sections_as_unwind_emulator_sections_t(self)        ((unwind_emulator_sections_t *)&(self)->ds_eh_frame_start)
#define cfientry_sections_as_di_debuginfo_cu_parser_sections_t(self) ((di_debuginfo_cu_parser_sections_t *)&(self)->ds_debug_loc_start)

struct cfientry {
	unwind_getreg_t ce_regget;     /* [1..1][const] Callback for reading out the value of a register.
	                                * This function is provided by the caller, and should return register
	                                * values as they'd appear at the position where the request is made
	                                * from. This function is then used internally to perform the initial
	                                * step of unwinding to the current function's call-site, at which
	                                * point libcfientry(3) will make an attempt to reverse-engineer the
	                                * values of requested registers. */
	union {
		void const *ce_regget_arg;  /* [?..?][const] Argument passed to `ce_regget'. */
		size_t     _ce_unwind_rega; /* # of allocated slots in `ce_unwind_regv' (used during start-up) */
	};
	unwind_emulator_t                 *ce_emulator;              /* [1..1][const] The instruction emulator that is being used. */
	REF module_t                      *ce_module;                /* [0..1][lock(WRITE_ONCE)] The module associated with the PC-register from `ce_unwind_regv' */
	module_type_var                   (ce_modtyp);               /* [valid_if(ce_module)][const] Module type for `ce_module' */
	uintptr_t                          ce_modrelpc;              /* [valid_if(ce_module)][const] Module-relative PC-offset (of the PC-register from `ce_unwind_regv') */
	REF module_section_t              *ce_s_eh_frame;            /* [0..1][valid_if(ce_module)] The .eh_frame section of `ce_module' */
	REF module_section_t              *ce_s_debug_frame;         /* [0..1][valid_if(ce_module)] The .debug_frame section of `ce_module' */
	REF module_section_t              *ce_s_debug_addr;          /* [0..1][valid_if(ce_module)] The .debug_addr section of `ce_module' */
	REF module_section_t              *ce_s_debug_loc;           /* [0..1][valid_if(ce_module)] The .debug_loc section of `ce_module' */
	REF module_section_t              *ce_s_debug_abbrev;        /* [1..1][valid_if(ce_module)][const] The .debug_abbrev section of `ce_module' */
	REF module_section_t              *ce_s_debug_info;          /* [1..1][valid_if(ce_module)][const] The .debug_info section of `ce_module' */
	REF module_section_t              *ce_s_debug_aranges;       /* [0..1][valid_if(ce_module)][const] The .debug_info section of `ce_module' */
	REF module_section_t              *ce_s_debug_ranges;        /* [0..1][valid_if(ce_module)] The .debug_info section of `ce_module' */
	struct cfientry_sections           ce_sections;              /* [valid_if(ce_module)] Mappings for relevant .debug_* sections.
	                                                              * Note that the mapping for `cps_debug_loc_start' is loaded lazily, and on a as-needed basis. */
	di_debuginfo_cu_abbrev_t           ce_abbrev;                /* [valid_if(ce_module)] Debug-info abbreviation information. */
	di_debuginfo_cu_parser_t           ce_parser;                /* [valid_if(ce_module)] Debug-info parser. */
	di_debuginfo_location_t            ce_subprogram_frame_base; /* [valid_if(ce_module)] Frame base expression of the sub-program containing `ce_modrelpc'. */
	di_debuginfo_compile_unit_simple_t cr_cu;                    /* [valid_if(ce_module)] Information on the containing compilation unit information. */

	/* Unwind register information: These descriptors override register values
	 * for the purpose of masking registers with new values as they'd appear at
	 * the respective call-sites following a call to `unwind(3)'
	 * As such, any arbitrary register from the call-site of the function containing
	 * an DW_OP_entry_value instruction is contained here-in, and is mainly intended
	 * to be used for evaluating expression of `DW_AT_GNU_call_site_value' and friends
	 * which are found from .debug_info of the module found at the PC-register (who's
	 * value should also be apart of this vector of overrides)
	 * As such, `DW_OP_entry_value' is evaluated by:
	 *   - unwind(3) with modified registers written to entries in `ce_unwind_regv'
	 *   - Execute code from the DW_OP_entry_value-block
	 *   - Register accesses first check if the requested register can be found
	 *     as part of the `ce_unwind_regv' vector. If it's inside, use that value.
	 *   - If the register cannot be found, scan .debug_info for call-site parameter
	 *     information on that register, and (if found) use that info.
	 *   - Memory accesses are always dispatched by searching for call-site parameter
	 *     information. */
	size_t                                          ce_unwind_regc;  /* # of register overrides found. */
	COMPILER_FLEXIBLE_ARRAY(struct unwind_register, ce_unwind_regv); /* [ce_unwind_regc] Vector of register overrides.
	                                                                  * Note that this vector is ascendingly sorted by
	                                                                  * an entry's `ur_regno', meaning you can use bsearch
	                                                                  * to find a specific entry within. */
};
#define cfientry_as_unwind_emulator_sections_t(self)        cfientry_sections_as_unwind_emulator_sections_t(&(self)->ce_sections)
#define cfientry_as_di_debuginfo_cu_parser_sections_t(self) cfientry_sections_as_di_debuginfo_cu_parser_sections_t(&(self)->ce_sections)

#define cfientry_alloc(unwind_rega)                                        \
	((struct cfientry *)alloca(offsetof(struct cfientry, ce_unwind_regv) + \
	                           (unwind_rega) *                             \
	                           sizeof(struct unwind_register)))

/* Finalize the given cfientry controller. */
PRIVATE NONNULL((1)) void
NOTHROW_NCX(CC cfientry_fini)(struct cfientry *__restrict self) {
	if (self->ce_module && self->ce_module != (REF module_t *)-1) {
		if (self->ce_s_eh_frame != (REF module_section_t *)-1)
			module_section_xdecref(self->ce_s_eh_frame, self->ce_modtyp);
		if (self->ce_s_debug_frame != (REF module_section_t *)-1)
			module_section_xdecref(self->ce_s_debug_frame, self->ce_modtyp);
		if (self->ce_s_debug_addr != (REF module_section_t *)-1)
			module_section_xdecref(self->ce_s_debug_addr, self->ce_modtyp);
		if (self->ce_s_debug_loc != (REF module_section_t *)-1)
			module_section_xdecref(self->ce_s_debug_loc, self->ce_modtyp);
		module_section_decref(self->ce_s_debug_abbrev, self->ce_modtyp);
		module_section_decref(self->ce_s_debug_info, self->ce_modtyp);
		module_section_xdecref(self->ce_s_debug_aranges, self->ce_modtyp);
		if (self->ce_s_debug_ranges != (REF module_section_t *)-1)
			module_section_xdecref(self->ce_s_debug_ranges, self->ce_modtyp);
		module_decref(self->ce_module, self->ce_modtyp);
		libdi_debuginfo_cu_abbrev_fini(&self->ce_abbrev);
	}
}

/* Lookup the register override entry for `dw_regno'
 * If no such entry exists, return `NULL' */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) struct unwind_register *
NOTHROW_NCX(CC find_register)(struct cfientry *__restrict self,
                              unwind_regno_t dw_regno) {
	size_t i;
	/* Check if the register can be found as part of unwind information. */
	BSEARCH(i, self->ce_unwind_regv, self->ce_unwind_regc, .ur_regno, dw_regno) {
		return &self->ce_unwind_regv[i];
	}
	return NULL;
}

/* Read the contents of a register after unwinding. When the value of `dw_regno'
 * wasn't specified by unwind information, then return its contents as they are
 * at the moment. iow: check `ce_unwind_regv', and if that doesn't mention `dw_regno',
 * simply forward the request to `arg->ce_regget'.
 * This function is used to facilitate register access inside of call-site parameter
 * expressions found in `DW_TAG_GNU_call_site_parameter:DW_AT_GNU_call_site_value'. */
PRIVATE NONNULL((1, 3)) bool
NOTHROW_NCX(LIBUNWIND_CC after_unwind_getreg)(/*struct cfientry **/ void const *arg,
                                              unwind_regno_t dw_regno,
                                              void *__restrict dst) {
	struct cfientry *self;
	size_t i;
	self = (struct cfientry *)arg;
	/* Check if the register can be found as part of unwind information. */
	BSEARCH(i, self->ce_unwind_regv, self->ce_unwind_regc, .ur_regno, dw_regno) {
		/* Found it! */
		memcpy(dst, self->ce_unwind_regv[i].ur_data,
		       CFI_REGISTER_SIZE(dw_regno));
		return true;
	}
	/* Forward the request to the underlying register accessor function. */
	return (*self->ce_regget)(self->ce_regget_arg, dw_regno, dst);
}

INTDEF char const secname_debug_aranges[];
INTDEF char const secname_debug_info[];
INTDEF char const secname_debug_abbrev[];
INTDEF char const secname_debug_loc[];
INTDEF char const secname_debug_ranges[];
INTDEF char const secname_eh_frame[];
INTDEF char const secname_debug_frame[];
INTDEF char const secname_debug_addr[];

#define LOAD_SECTION(sect, module_type, lv_start, lv_end)                             \
	do {                                                                              \
		size_t size;                                                                  \
		(lv_start) = (byte_t const *)module_section_inflate(sect, module_type, size); \
		(lv_end)   = (lv_start) + size;                                               \
	}	__WHILE0


/* Bind the .debug_ranges section. */
PRIVATE void
NOTHROW_NCX(CC cfientry_bind_debug_ranges)(struct cfientry *__restrict self) {
	if (self->ce_s_debug_ranges)
		return;
	self->ce_s_debug_ranges = module_locksection(self->ce_module, self->ce_modtyp,
	                                             secname_debug_ranges, MODULE_LOCKSECTION_FNORMAL);
	if (!self->ce_s_debug_ranges) {
		self->ce_s_debug_ranges = (REF module_section_t *)-1;
		return;
	}
	LOAD_SECTION(self->ce_s_debug_ranges,
	             self->ce_modtyp,
	             self->ce_sections.ds_debug_ranges_start,
	             self->ce_sections.ds_debug_ranges_end);
}

/* Parse attributes of `self' in order to fill in `range'
 * Optionally, also parse frame-base location information.
 * @return: * : One of `DEBUG_INFO_ERROR_*' */
PRIVATE NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC parse_attributes_for_ranges)(di_debuginfo_cu_parser_t *__restrict self,
                                            di_debuginfo_ranges_t *__restrict range,
                                            di_debuginfo_location_t *pframe_base) {
	di_debuginfo_component_attrib_t attr;
	unsigned int error       = DEBUG_INFO_ERROR_NOFRAME;
	bool high_pc_is_relative = false;
	range->r_ranges_offset   = (uintptr_t)-1;
	range->r_startpc         = (uintptr_t)-1;
	range->r_endpc           = 0;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self) {
		switch (attr.dica_name) {

		case DW_AT_ranges:
			if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
			                                                &range->r_ranges_offset))
				ERROR(err);
			error = DEBUG_INFO_ERROR_SUCCESS;
			break;

		case DW_AT_low_pc:
			if unlikely(!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form,
			                                               &range->r_startpc))
				ERROR(err);
			error = DEBUG_INFO_ERROR_SUCCESS;
			break;

		case DW_AT_high_pc:
			if (!libdi_debuginfo_cu_parser_getaddr(self, attr.dica_form, &range->r_endpc)) {
				if unlikely(!libdi_debuginfo_cu_parser_getconst(self, attr.dica_form,
				                                                &range->r_endpc))
					ERROR(err);
				high_pc_is_relative = true;
			}
			error = DEBUG_INFO_ERROR_SUCCESS;
			break;

		case DW_AT_frame_base:
			if (pframe_base) {
				if unlikely(!libdi_debuginfo_cu_parser_getexpr(self, attr.dica_form, pframe_base))
					ERROR(err);
			}
			break;

		default: break;
		}
	}
	if (high_pc_is_relative)
		range->r_endpc += range->r_startpc;
	return error;
err:
	return DEBUG_INFO_ERROR_CORRUPT;
}


/* Try to locate the relevant `DW_TAG_GNU_call_site' component,
 * where the caller has already loaded up the parser to point
 * at the initial DW_TAG_compile_unit element of the (probably)
 * correct CU.
 * @return: * : One of `CFIENTRY_LOCATE_CALLSITE_*' */
#define CFIENTRY_LOCATE_CALLSITE_SUCCESS                 0 /* Success */
#define CFIENTRY_LOCATE_CALLSITE_FUNCTION_NOT_FOUND      1 /* Containing function not found in this CU */
#define CFIENTRY_LOCATE_CALLSITE_NO_CALLSITE_IN_FUNCTION 2 /* No relevant `DW_TAG_GNU_call_site' within the containing function */
PRIVATE NONNULL((1)) unsigned int
NOTHROW_NCX(CC cfientry_locate_callsite)(struct cfientry *__restrict self,
                                         bool assume_correct_cu) {
	size_t cu_depth;
	unsigned int error;
	/* Scan ahead to the first DW_TAG_compile_unit component. */
	for (;;) {
		if (self->ce_parser.dup_comp.dic_tag == DW_TAG_compile_unit) {
			/* Check if this is the correct CU, or if what we're looking for might be elsewhere. */
			if (libdi_debuginfo_cu_parser_loadattr_compile_unit_simple(&self->ce_parser,
			                                                           &self->cr_cu)) {
				if (assume_correct_cu)
					break;
				if (self->cr_cu.cu_ranges.r_ranges_offset != (uintptr_t)-1)
					cfientry_bind_debug_ranges(self);
				error = debuginfo_ranges_contains(&self->cr_cu.cu_ranges, &self->ce_parser,
				                                  self->cr_cu.cu_ranges.r_startpc,
				                                  self->ce_modrelpc,
				                                  self->ce_sections.ds_debug_ranges_start,
				                                  self->ce_sections.ds_debug_ranges_end);
				if (error != DEBUG_INFO_ERROR_SUCCESS)
					ERROR(err_function_not_found);
				break;
			}
			ERROR(err_function_not_found);
		}
		libdi_debuginfo_cu_parser_skipattr(&self->ce_parser);
		if (!libdi_debuginfo_cu_parser_next(&self->ce_parser))
			ERROR(err_function_not_found);
	}
	cu_depth = self->ce_parser.dup_child_depth;
	if (!libdi_debuginfo_cu_parser_nextchild(&self->ce_parser))
		ERROR(err_function_not_found);

	/* At this point, we know that we (should be) within the correct CU.
	 * With this in mind, scan for DW_TAG_subprogram entries, and check
	 * for one that contains the module-relative-pc we're looking for. */
	while (self->ce_parser.dup_child_depth > cu_depth) {
		if (self->ce_parser.dup_comp.dic_tag == DW_TAG_subprogram) {
			/* Parse attributes of the sub-program */
			di_debuginfo_ranges_t ranges;
			self->ce_subprogram_frame_base.l_expr  = NULL;
			self->ce_subprogram_frame_base.l_llist = NULL;
			error = parse_attributes_for_ranges(&self->ce_parser, &ranges,
			                                    &self->ce_subprogram_frame_base);
			if (error == DEBUG_INFO_ERROR_SUCCESS) {
				/* Check if this might be the function we're looking for. */
				if (ranges.r_ranges_offset != (uintptr_t)-1)
					cfientry_bind_debug_ranges(self);
				error = debuginfo_ranges_contains(&ranges, &self->ce_parser,
				                                  ranges.r_startpc,
				                                  self->ce_modrelpc,
				                                  self->ce_sections.ds_debug_ranges_start,
				                                  self->ce_sections.ds_debug_ranges_end);
				if (error == DEBUG_INFO_ERROR_SUCCESS) {
					size_t sp_element_depth;
					/* Found the relevant containing function! */
					if (!libdi_debuginfo_cu_parser_nextchild(&self->ce_parser))
						ERROR(err_no_callsite_in_function);
					sp_element_depth = self->ce_parser.dup_child_depth;
					/* Search for `DW_TAG_GNU_call_site' entries. */
					while (self->ce_parser.dup_child_depth >= sp_element_depth) {
						if (DW_IS_TAG_call_site(self->ce_parser.dup_comp.dic_tag)) {
							uintptr_t low_pc;
							di_debuginfo_component_attrib_t attr;
							low_pc = (uintptr_t)-1;
							DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &self->ce_parser) {
								if (attr.dica_name == DW_AT_low_pc) {
									if unlikely(!libdi_debuginfo_cu_parser_getaddr(&self->ce_parser,
									                                               attr.dica_form,
									                                               &low_pc))
										ERROR(err_no_callsite_in_function);
								}
							}
							if (low_pc == self->ce_modrelpc)
								return CFIENTRY_LOCATE_CALLSITE_SUCCESS; /* Found it! */
						} else {
							libdi_debuginfo_cu_parser_skipattr(&self->ce_parser);
						}
						if (!libdi_debuginfo_cu_parser_next(&self->ce_parser))
							break;
					}
err_no_callsite_in_function:
					return CFIENTRY_LOCATE_CALLSITE_NO_CALLSITE_IN_FUNCTION;
				}
			}
			if (error != DEBUG_INFO_ERROR_NOFRAME)
				ERROR(err_function_not_found);
		} else {
			libdi_debuginfo_cu_parser_skipattr(&self->ce_parser);
		}
		if (!libdi_debuginfo_cu_parser_next(&self->ce_parser))
			break;
	}
err_function_not_found:
	return CFIENTRY_LOCATE_CALLSITE_FUNCTION_NOT_FOUND;
}

/* Try to load module information for `self', as well as bind basic sections:
 *   - ce_s_debug_aranges
 *   - ce_s_debug_info
 *   - ce_s_debug_abbrev
 * Also map each of these sections into memory, filling in section range pointers.
 * Sections that can't be loaded are simply set to `NULL'.
 *
 * Finally, initialize and navigate the debug information parser to point
 * after the attributes of `DW_TAG_GNU_call_site' component that represents
 * the expected return address, meaning that the caller may then proceed
 * to load child-DW_TAG_GNU_call_site_parameter components by saving the
 * current parser position for later, and calling
 * `libdi_debuginfo_cu_parser_nextchild()' in order to load the first of a
 * variable number of should-be `DW_TAG_GNU_call_site_parameter'-components. */
PRIVATE NONNULL((1)) bool
NOTHROW_NCX(CC cfientry_loadmodule)(struct cfientry *__restrict self) {
	struct unwind_register *pc_register;

	if (self->ce_module)
		return self->ce_module != (REF module_t *)-1; /* Already loaded, or cannot be loaded! */
	/* Lookup an override for the PC register. */
	pc_register = find_register(self, CFI_UNWIND_REGISTER_PC);
	if unlikely(!pc_register)
		goto fail;
	self->ce_module = module_ataddr_nx((void const *)pc_register->ur_word, self->ce_modtyp);
	if unlikely(!self->ce_module)
		goto fail;
	/* Fill in data that becomes valid once a module's been loaded. */
	self->ce_modrelpc = pc_register->ur_word - module_getloadaddr(self->ce_module, self->ce_modtyp);
#define lock_section(name)                               \
	module_locksection(self->ce_module, self->ce_modtyp, \
	                   name, MODULE_LOCKSECTION_FNORMAL)
	self->ce_s_debug_info = lock_section(secname_debug_info);
	if unlikely(!self->ce_s_debug_info) /* We absolutely _need_ the .debug_info section! */
		goto fail_module;
	self->ce_s_debug_abbrev = lock_section(secname_debug_abbrev);
	if unlikely(!self->ce_s_debug_abbrev) /* We absolutely _need_ the .debug_abbrev section! */
		goto fail_module_debug_info;
	self->ce_s_debug_aranges = lock_section(secname_debug_aranges);
#undef lock_section
	self->ce_s_eh_frame     = NULL; /* Loaded lazily. */
	self->ce_s_debug_frame  = NULL; /* Loaded lazily. */
	self->ce_s_debug_addr   = NULL; /* Loaded lazily. */
	self->ce_s_debug_loc    = NULL; /* Loaded lazily. */
	self->ce_s_debug_ranges = NULL; /* Loaded lazily. */
	memset(&self->ce_sections, 0, sizeof(self->ce_sections));
	/* Bind sections. */
	if (self->ce_s_debug_aranges) {
		LOAD_SECTION(self->ce_s_debug_aranges,
		             self->ce_modtyp,
		             self->ce_sections.ds_debug_aranges_start,
		             self->ce_sections.ds_debug_aranges_end);
	}
	LOAD_SECTION(self->ce_s_debug_abbrev,
	             self->ce_modtyp,
	             self->ce_sections.ds_debug_abbrev_start,
	             self->ce_sections.ds_debug_abbrev_end);
	LOAD_SECTION(self->ce_s_debug_info,
	             self->ce_modtyp,
	             self->ce_sections.ds_debug_info_start,
	             self->ce_sections.ds_debug_info_end);
	/* Find the proper compilation-unit for `self->ce_modrelpc' */
	{
		unsigned int error;
		uintptr_t debuginfo_cu_offset;
		byte_t const *reader;
		error = libdi_debugaranges_locate(self->ce_sections.ds_debug_aranges_start,
		                                  self->ce_sections.ds_debug_aranges_end,
		                                  &debuginfo_cu_offset,
		                                  self->ce_modrelpc);
		if (error == DEBUG_INFO_ERROR_SUCCESS) {
			/* Load the relevant CU */
			reader = self->ce_sections.ds_debug_info_start + debuginfo_cu_offset;

			/* Load the relevant CU. */
			error = libdi_debuginfo_cu_parser_loadunit(&reader, self->ce_sections.ds_debug_info_end,
			                                           cfientry_as_di_debuginfo_cu_parser_sections_t(self),
			                                           &self->ce_parser,
			                                           &self->ce_abbrev,
			                                           NULL);
			if unlikely(error != DEBUG_INFO_ERROR_SUCCESS)
				goto fail_module_sections;

			/* Load the relevant call-site. */
			error = cfientry_locate_callsite(self, true);
			if unlikely(error != CFIENTRY_LOCATE_CALLSITE_SUCCESS)
				goto fail_module_sections;
		} else {
			/* This can happen if the .debug_aranges section is missing.
			 * In this case, scan _all_ CUs for the call-site function. */
			reader = self->ce_sections.ds_debug_info_start;
			for (;;) {
				error = libdi_debuginfo_cu_parser_loadunit(&reader, self->ce_sections.ds_debug_info_end,
				                                           cfientry_as_di_debuginfo_cu_parser_sections_t(self),
				                                           &self->ce_parser,
				                                           &self->ce_abbrev,
				                                           NULL);
				if (error != DEBUG_INFO_ERROR_SUCCESS)
					goto fail_module_sections;
				/* Load the relevant call-site. */
				error = cfientry_locate_callsite(self, false);
				if unlikely(error == CFIENTRY_LOCATE_CALLSITE_SUCCESS)
					break; /* Found it! */
				if unlikely(error == CFIENTRY_LOCATE_CALLSITE_NO_CALLSITE_IN_FUNCTION)
					goto fail_module_sections; /* There isn't any call-site information */
			}
		}
	}
	return true;
fail_module_sections:
	module_section_xdecref(self->ce_s_debug_aranges, self->ce_modtyp);
	module_section_decref(self->ce_s_debug_abbrev, self->ce_modtyp);
fail_module_debug_info:
	module_section_decref(self->ce_s_debug_info, self->ce_modtyp);
fail_module:
	module_decref(self->ce_module, self->ce_modtyp);
fail:
	self->ce_module = (REF module_t *)-1;
	return false;
}

#ifdef __GNUC__
/* GCC claims that "length" in the below function is uninitialized, when
 * clearly it is very much getting initialized by `debuginfo_location_select()' */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif /* __GNUC__ */

/* Check if the given `expr' is a simple push-register instruction for `dw_regno' */
PRIVATE WUNUSED ATTR_PURE NONNULL((1, 2)) bool
NOTHROW_NCX(CC is_cfi_expression_a_simple_register_push)(struct cfientry *__restrict self,
                                                         di_debuginfo_location_t const *__restrict loc,
                                                         unwind_regno_t dw_regno) {
	size_t length;
	byte_t const *expr;
	expr = debuginfo_location_select(loc, self->cr_cu.cu_ranges.r_startpc,
	                                 self->ce_modrelpc,
	                                 self->ce_parser.dup_addrsize, &length);
	if unlikely(!expr)
		return false;
	switch (length) {

	case 0:
		break;

	case 1: {
		/* Check for DW_OP_regXX */
		uint8_t opcode;
		opcode = expr[0];
		return opcode == DW_OP_reg0 + dw_regno;
	}	break;

	default: {
		/* case length >= 2: */
		uint8_t opcode;
		opcode = expr[0];
		if (opcode == DW_OP_regx) {
			unwind_regno_t expr_regno;
			byte_t const *reader = expr + 1;
			expr_regno = dwarf_decode_uleb128((byte_t const **)&reader);
			if (reader == expr + length) { /* Ensure that this is the only instruction! */
				return expr_regno == dw_regno;
			}
		}
	}	break;

	}
	return false;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */


PRIVATE NONNULL((1, 3)) bool
NOTHROW_NCX(LIBUNWIND_CC cfi_getreg)(/*struct cfientry **/ void const *arg,
                                     unwind_regno_t dw_regno,
                                     void *__restrict dst);

PRIVATE NONNULL((1, 3)) void CC
copy_bits(void *__restrict dst_base, unsigned int dst_bit_offset,
          void const *__restrict src_base, unsigned int src_bit_offset,
          size_t num_bits) {
	while (num_bits) {
		byte_t remaining, src_value, remaining_temp;
		src_base = (byte_t const *)src_base + (src_bit_offset / NBBY);
		src_bit_offset %= NBBY;
		remaining = NBBY - src_bit_offset;
		if (remaining > num_bits)
			remaining = num_bits;
		src_value      = *(byte_t const *)src_base >> src_bit_offset;
		remaining_temp = remaining;
		while (remaining_temp) {
			byte_t avail, dst_value;
			dst_base = (byte_t *)dst_base + (dst_bit_offset / NBBY);
			dst_bit_offset %= NBBY;
			avail = NBBY - dst_bit_offset;
			if (avail > remaining_temp)
				avail = remaining_temp;
			dst_value = *(byte_t *)dst_base;
			dst_value &= ~(((1 << avail) - 1) << dst_bit_offset);
			dst_value |= (src_value & ((1 << avail) - 1)) << dst_bit_offset;
			*(byte_t *)dst_base = dst_value;
			dst_bit_offset += avail;
			remaining_temp -= avail;
			src_value >>= avail;
		}
		src_bit_offset += remaining;
		num_bits -= remaining;
	}
}


#ifdef __GNUC__
/* GCC claims that "expr_length" in the below function is uninitialized, when
 * clearly it is very much getting initialized by `debuginfo_location_select()' */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif /* __GNUC__ */

/* @param: deref_expression_result: When true, dereference the expression result, and
 *                                  copy the pointed-to memory contents into `dst' */
PRIVATE ATTR_NOINLINE NONNULL((1, 2, 4)) unsigned int
NOTHROW_NCX(LIBUNWIND_CC evaluate_call_site_expression)(struct cfientry *__restrict self,
                                                        di_debuginfo_location_t const *__restrict location,
                                                        unwind_regno_t dw_regno, void *__restrict dst,
                                                        bool deref_expression_result) {
	unwind_emulator_t emulator;
	size_t expr_length;
	byte_t const *expr;
	byte_t const *expr_end;
	unwind_ste_t top;
	unsigned int error;
	/* Select the proper expression. */
	expr = debuginfo_location_select(location,
	                                 self->cr_cu.cu_ranges.r_startpc,
	                                 self->ce_modrelpc,
	                                 self->ce_parser.dup_addrsize,
	                                 &expr_length);
	if unlikely(!expr)
		return UNWIND_NO_FRAME;
	expr_end = expr + expr_length;
	if unlikely(expr >= expr_end)
		return UNWIND_NO_FRAME;
	if unlikely(expr < self->ce_sections.ds_debug_info_start)
		return UNWIND_NO_FRAME;

	/* Construct an emulator for execution of the call-site-expression. */
again_runexpr:
	emulator.ue_pc                 = expr;
	emulator.ue_pc_start           = expr;
	emulator.ue_pc_end             = expr_end;
	emulator.ue_sectinfo           = cfientry_as_unwind_emulator_sections_t(self);
	emulator.ue_regget             = &after_unwind_getreg;
	emulator.ue_regset             = NULL;
	emulator.ue_regget_arg         = self;
	/*ulator.ue_regset_arg         = NULL;*/ /* Unused */
	emulator.ue_framebase          = &self->ce_subprogram_frame_base;
	emulator.ue_addroffset         = module_getloadaddr(self->ce_module, self->ce_modtyp);
	emulator.ue_objaddr            = NULL;
	emulator.ue_bjmprem            = UNWIND_EMULATOR_BJMPREM_DEFAULT;
	emulator.ue_addrsize           = self->ce_parser.dup_addrsize;
	emulator.ue_ptrsize            = self->ce_parser.dup_ptrsize;
	emulator.ue_piecewrite         = 0;
	emulator.ue_piecebuf           = (byte_t *)dst;
	emulator.ue_piecesiz           = CFI_REGISTER_SIZE(dw_regno);
	emulator.ue_piecebits          = 0;
	emulator.ue_call_frame_cfa     = 0;
	emulator.ue_cu                 = &self->cr_cu;
	emulator.ue_module_relative_pc = self->ce_modrelpc;
	emulator.ue_tlsbase            = (byte_t *)-1;
	memset(dst, 0, emulator.ue_piecesiz);
	if (deref_expression_result)
		emulator.ue_piecesiz = 0;

	/* Execute the expression. */
	error = unwind_emulator_exec_autostack(&emulator, NULL, &top, NULL);
	if (error == UNWIND_SUCCESS) {
		if (deref_expression_result) {
			/* Read from the pointed-to memory location of stack-top to fill in the rest. */
			error = unwind_ste_read(&top, &after_unwind_getreg, self, dst,
			                        CFI_REGISTER_SIZE(dw_regno) * NBBY,
			                        emulator.ue_piecebits, 0);
		} else {
			void *addr;
			error = unwind_ste_addr(&top, &after_unwind_getreg, self, &addr);
			if (error == UNWIND_SUCCESS) {
				/* Load missing bits with from the address itself (but don't deref it!) */
				size_t missing_bits;
				missing_bits = (emulator.ue_piecesiz * NBBY) - emulator.ue_piecebits;
				if (missing_bits > sizeof(addr) * NBBY)
					missing_bits = sizeof(addr) * NBBY;
				copy_bits(dst, emulator.ue_piecebits, &addr, 0, missing_bits);
			}
		}
		return error;
	} else if (error == UNWIND_EMULATOR_NO_RETURN_VALUE && !deref_expression_result) {
		/* If we're not supposed to deref the result, it's OK if the
		 * expression didn't leave anything within the top stack-element. */
		return  UNWIND_SUCCESS;
	}

	/* Check if we might be able to fix the error by loading some missing section. */
	if unlikely(error == UNWIND_EMULATOR_UNKNOWN_INSTRUCTION ||
	            error == UNWIND_EMULATOR_INVALID_FUNCTION ||
	            error == UNWIND_EMULATOR_NO_CFA) {
		if (!self->ce_s_eh_frame && !self->ce_s_debug_frame &&
		    !self->ce_s_debug_addr && !self->ce_s_debug_loc) {
#define lock_section(name)                                       \
			module_locksection(self->ce_module, self->ce_modtyp, \
			                   name, MODULE_LOCKSECTION_FNORMAL)
			self->ce_s_eh_frame    = lock_section(secname_eh_frame);
			self->ce_s_debug_frame = lock_section(secname_debug_frame);
			self->ce_s_debug_addr  = lock_section(secname_debug_addr);
			self->ce_s_debug_loc   = lock_section(secname_debug_loc);
#undef lock_section
			if (!self->ce_s_eh_frame)
				self->ce_s_eh_frame = (REF module_section_t *)-1;
			else {
				LOAD_SECTION(self->ce_s_eh_frame,
				             self->ce_modtyp,
				             self->ce_sections.ds_eh_frame_start,
				             self->ce_sections.ds_eh_frame_end);
			}
			if (!self->ce_s_debug_frame)
				self->ce_s_debug_frame = (REF module_section_t *)-1;
			else {
				LOAD_SECTION(self->ce_s_debug_frame,
				             self->ce_modtyp,
				             self->ce_sections.ds_debug_frame_start,
				             self->ce_sections.ds_debug_frame_end);
			}
			if (!self->ce_s_debug_addr)
				self->ce_s_debug_addr = (REF module_section_t *)-1;
			else {
				LOAD_SECTION(self->ce_s_debug_addr,
				             self->ce_modtyp,
				             self->ce_sections.ds_debug_addr_start,
				             self->ce_sections.ds_debug_addr_end);
			}
			if (!self->ce_s_debug_loc)
				self->ce_s_debug_loc = (REF module_section_t *)-1;
			else {
				LOAD_SECTION(self->ce_s_debug_loc,
				             self->ce_modtyp,
				             self->ce_sections.ds_debug_loc_start,
				             self->ce_sections.ds_debug_loc_end);
			}
			goto again_runexpr;
		}
	}
	return error;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */


PRIVATE NONNULL((1, 3)) bool
NOTHROW_NCX(LIBUNWIND_CC cfi_getreg)(/*struct cfientry **/ void const *arg,
                                     unwind_regno_t dw_regno,
                                     void *__restrict dst) {
	struct cfientry *self;
	size_t i;
	byte_t const *saved_dip;
	self = (struct cfientry *)arg;

	/* First up: Check if the register can be found as part of unwind information.
	 *           It it can, then pretty much all of the hard work's already been
	 *           done and we can just read from there. */
	BSEARCH(i, self->ce_unwind_regv, self->ce_unwind_regc, .ur_regno, dw_regno) {
		/* Found it! */
		memcpy(dst, self->ce_unwind_regv[i].ur_data,
		       CFI_REGISTER_SIZE(dw_regno));
		return true;
	}

	/* Can't find register information from unwind data. As such, check
	 * if we can find information about the requested register as part
	 * of call-site parameter information. */

	/* #1: Lazily load .debug_info (and related sections) for the module
	 *     currently loaded at `CFI_UNWIND_REGISTER_PC' (which should be
	 *     the value of one of the entries of `ce_unwind_regv')
	 * #2: Search for the DW_TAG_subprogram entry containing the call-site
	 *     program counter, and scan that component for `DW_TAG_GNU_call_site'
	 *     with a `DW_AT_location'-attribute that matches the register
	 *     expression currently being described by `dw_regno'.
	 *     Once found, load a different attribute `DW_AT_GNU_call_site_value'
	 *     from that same `DW_TAG_GNU_call_site'-component, which then contains
	 *     a CFI-expression that can be evaluated in order to calculate the
	 *     value that the requested register had at the time of the current
	 *     function being called.
	 *     NOTE: Register access from inside of this expression is performed
	 *           through use of `after_unwind_getreg()'. */
	if (!cfientry_loadmodule(self))
		return false; /* Load module information */
	saved_dip = self->ce_parser.dup_cu_info_pos;
	/* Scan the call-site we've discovered for `DW_TAG_GNU_call_site_parameter' children */
	if (libdi_debuginfo_cu_parser_nextchild(&self->ce_parser)) {
		size_t callsite_depth = self->ce_parser.dup_child_depth;
		while (self->ce_parser.dup_child_depth >= callsite_depth) {
			if (DW_IS_TAG_call_site_parameter(self->ce_parser.dup_comp.dic_tag)) {
				di_debuginfo_component_attrib_t attr;
				di_debuginfo_location_t location, call_site_value;
				bool deref_result       = false;
				location.l_expr         = NULL;
				location.l_llist        = NULL;
				call_site_value.l_expr  = NULL;
				call_site_value.l_llist = NULL;
				DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &self->ce_parser) {
					if (attr.dica_name == DW_AT_location) {
						if unlikely(!libdi_debuginfo_cu_parser_getexpr(&self->ce_parser, attr.dica_form,
						                                               &location))
							ERROR(err);
					} else if (attr.dica_name == DW_AT_GNU_call_site_value ||
					           attr.dica_name == DW_AT_call_value) {
						if unlikely(!libdi_debuginfo_cu_parser_getexpr(&self->ce_parser, attr.dica_form,
						                                               &call_site_value))
							ERROR(err);
						deref_result = false;
					} else if (attr.dica_name == DW_AT_GNU_call_site_data_value ||
					           attr.dica_name == DW_AT_call_data_value) {
						if unlikely(!libdi_debuginfo_cu_parser_getexpr(&self->ce_parser, attr.dica_form,
						                                               &call_site_value))
							ERROR(err);
						deref_result = true;
					}
				}
				/* Check if `location' references the register that we're looking for. */
				if (is_cfi_expression_a_simple_register_push(self, &location, dw_regno)) {
					unsigned int error;
					self->ce_parser.dup_cu_info_pos = saved_dip;
					/* Found it! -> Evaluate the call-site-value expression,
					 * and write the expression result into the `dst' buffer. */
					error = evaluate_call_site_expression(self, &call_site_value,
					                                      dw_regno, dst, deref_result);
					return error == UNWIND_SUCCESS;
				}
			} else {
				libdi_debuginfo_cu_parser_skipattr(&self->ce_parser);
			}
			if (!libdi_debuginfo_cu_parser_next(&self->ce_parser))
				break;
		}
	}
err:
	self->ce_parser.dup_cu_info_pos = saved_dip;
	return false;
}




/* Convert the given stack-entry into an R-value:
 *    - UNWIND_STE_REGISTER   -> UNWIND_STE_CONSTANT
 *    - UNWIND_STE_REGPOINTER -> UNWIND_STE_STACKVALUE */
PRIVATE NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC make_rvalue)(unwind_emulator_t *__restrict self,
                            unwind_ste_t *__restrict ste) {
	union {
		uintptr_t p;
		byte_t buf[CFI_UNWIND_REGISTER_MAXSIZE];
	} regval;
	switch (ste->s_type) {

	case UNWIND_STE_REGISTER:
	case UNWIND_STE_REGPOINTER: {
		if unlikely(!cfi_getreg(self->ue_regget_arg, ste->s_register, regval.buf))
			goto err_invalid_register;
		/* Convert the stack-entry. */
		if (ste->s_type == UNWIND_STE_REGISTER) {
			ste->s_uconst = regval.p + ste->s_regoffset;
			ste->s_type   = UNWIND_STE_CONSTANT;
		} else {
			ste->s_uconst = regval.p;
			ste->s_type   = UNWIND_STE_STACKVALUE;
		}
	}	break;

	default:
		break;
	}
	return UNWIND_SUCCESS;
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
}

PRIVATE NONNULL((1, 3)) bool LIBUNWIND_CC
cfi_entry_init_setreg(void *arg,
                      unwind_regno_t dw_regno,
                      void const *__restrict src) {
	struct cfientry *self;
	size_t index, lo, hi;
	self = (struct cfientry *)arg;
	lo   = 0;
	hi   = self->ce_unwind_regc;
	/* First up: Check if we've already seen this register. */
	for (;;) {
		index = (lo + hi) / 2;
		if (lo >= hi)
			break;
		if (dw_regno < self->ce_unwind_regv[index].ur_regno) {
			hi = index;
		} else if (dw_regno > self->ce_unwind_regv[index].ur_regno) {
			lo = index + 1;
		} else {
			/* Register had been set before. - Just override its old data-entry. */
			memcpy(self->ce_unwind_regv[index].ur_data,
			       src, CFI_REGISTER_SIZE(dw_regno));
			return true;
		}
	}
	/* Need another register override entry. */
	if (self->ce_unwind_regc < self->_ce_unwind_rega) {
		/* Must insert at `index' */
		memmoveup(&self->ce_unwind_regv[index + 1],
		          &self->ce_unwind_regv[index],
		          self->ce_unwind_regc - index,
		          sizeof(struct unwind_register));
		self->ce_unwind_regv[index].ur_regno = dw_regno;
		memcpy(self->ce_unwind_regv[index].ur_data,
		       src, CFI_REGISTER_SIZE(dw_regno));
	}
	/* Track the # of unwind registers. */
	++self->ce_unwind_regc;
	return true;
}


/* Initialize the given cfientry controller `self' by performing an `unwind_for_debug(3)'
 * from the point-of-view of the register state described by `regget' and `regget_arg'.
 * The caller must check if all registers overrides could be allocated, as this function
 * will simply set `self->ce_unwind_regc' to the exact # of overrides required, but will
 * only fill in the first `self->_ce_unwind_rega' of them! */
PRIVATE WUNUSED ATTR_NOINLINE NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC cfientry_init)(struct cfientry *__restrict self,
                              unwind_getreg_t regget,
                              void const *regget_arg) {
	unsigned int result;
	union {
		byte_t buf[CFI_REGISTER_SIZE(CFI_UNWIND_REGISTER_PC)];
		void *pc;
	} pc_buf;
	/* Lookup the origin PC (which we need for unwinding to the call-site) */
	if (!(*regget)(regget_arg, CFI_UNWIND_REGISTER_PC, pc_buf.buf)) {
		result = UNWIND_INVALID_REGISTER;
		goto done;
	}
	/* Use unwind_for_debug(3) because we can. */
	result = libdi_unwind_for_debug(pc_buf.pc, regget, regget_arg,
	                                &cfi_entry_init_setreg, self);
done:
	return result;
}

/* Special error-return value for `run_entry_value_emulator()' */
#define _UNWIND_TOO_FEW_UNWIND_REGISTER_OVERRIDE_SLOTS ((unsigned int)-10)

/* Worker-function for emulating instruction in entry-value context.
 * @param: unwind_rega:      The # of slots to allocate for unwind register overrides.
 * @param: preq_unwind_rega: When `_UNWIND_TOO_FEW_UNWIND_REGISTER_OVERRIDE_SLOTS' is
 *                           returned, write-back the # of required into this slot. */
PRIVATE WUNUSED ATTR_NOINLINE NONNULL((1)) unsigned int
NOTHROW_NCX(CC run_entry_value_emulator)(unwind_emulator_t *__restrict self,
                                         size_t unwind_rega,
                                         size_t *__restrict preq_unwind_rega) {
	unsigned int result;
	size_t old_stacksize;
	struct cfientry *ce;

	/* Allocate the CFI-entry controller. */
	ce = cfientry_alloc(unwind_rega);
	ce->_ce_unwind_rega = unwind_rega;
	ce->ce_unwind_regc  = 0;

	/* Initialize the CFI-entry controller. */
	result = cfientry_init(ce, self->ue_regget, self->ue_regget_arg);
	if (result != UNWIND_SUCCESS)
		goto done;

	/* Check if we need more space to hold all of the register overrides. */
	if (ce->ce_unwind_regc > ce->_ce_unwind_rega) {
		result            = _UNWIND_TOO_FEW_UNWIND_REGISTER_OVERRIDE_SLOTS;
		*preq_unwind_rega = ce->ce_unwind_regc;
		goto done;
	}

	/* Fill in the callee-register accessor callback of `ce' */
	ce->ce_regget     = self->ue_regget;
	ce->ce_regget_arg = self->ue_regget_arg;
	ce->ce_emulator   = self;
	ce->ce_module     = NULL;

	/* Re-configure `self' for execution. */
	old_stacksize       = self->ue_stacksz;
	self->ue_regget     = &cfi_getreg;
	self->ue_regget_arg = ce;

	/* Actually execution DW_OP_*-code. */
	result = unwind_emulator_exec(self);

	/* Convert all newly pushed register values into r-values! */
	if (result == UNWIND_SUCCESS && self->ue_stacksz > old_stacksize) {
		size_t i;
		for (i = old_stacksize; i < self->ue_stacksz; ++i) {
			unwind_ste_t *ste;
			ste    = &self->ue_stack[i];
			result = make_rvalue(self, ste);
			if unlikely(result != UNWIND_SUCCESS)
				break;
		}
	}

	/* Finalize the CFI-entry controller. */
	cfientry_fini(ce);

	/* Restore the old configuration of `self' */
	self->ue_regget     = ce->ce_regget;
	self->ue_regget_arg = ce->ce_regget_arg;
done:
	return result;
}


/* Run a sequence of DW_OP_* instructions as though they were being
 * invoked at the start of the current function. After this, any
 * stack-value left on the internal stack of `self' that was pushed
 * by the given instruction stream, wasn't there before, and refers
 * to a register location, will be replaced with a stack-local R-value
 * copy of that location, thus ensuring that any register accessed is
 * loaded by-value
 *
 * NOTE: This function will preserve and restore the original values of:
 *        - ue_pc         (Altered to point to the given `cfi_start_pc...cfi_end_pc' range)
 *        - ue_pc_start   (*ditto*)
 *        - ue_pc_end     (*ditto*)
 *        - ue_regget     (Register access is dispatched to register states as they were on function entry)
 *        - ue_regget_arg (*ditto*)
 *        - ue_regset     (Temporarily set to NULL to prevent register writes)
 *       ... before returning, regardless of what ends up being returned.
 *
 * @return: UNWIND_SUCCESS:          ...
 * @return: UNWIND_INVALID_REGISTER: ... (May also be returned if a register counter not be reversed)
 * @return: UNWIND_SEGFAULT:         ...
 * @return: UNWIND_BADALLOC:         ...
 * @return: UNWIND_EMULATOR_*:       ... */
INTERN WUNUSED NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC libdi_debuginfo_run_entry_value_emulator)(unwind_emulator_t *__restrict self,
                                                         byte_t const *cfi_start_pc,
                                                         byte_t const *cfi_end_pc) {
	unsigned int result;
	byte_t const *saved_pc;
	byte_t const *saved_pc_start;
	byte_t const *saved_pc_end;
	unwind_setreg_t saved_regset;

#ifndef __KERNEL__
	/* Ensure that we've loaded the necessary symbols from libunwind.so */
	if unlikely(!load_libunwind())
		return UNWIND_EMULATOR_UNKNOWN_INSTRUCTION;
#endif /* !__KERNEL__ */

	/* Preserve the old emulator state. */
	saved_pc       = self->ue_pc;
	saved_pc_start = self->ue_pc_start;
	saved_pc_end   = self->ue_pc_end;
	saved_regset   = self->ue_regset;

	/* Set-up the emulator to do our bidding. */
	self->ue_pc       = cfi_start_pc;
	self->ue_pc_start = cfi_start_pc;
	self->ue_pc_end   = cfi_end_pc;
	self->ue_regset   = NULL; /* Prevent register writes */

	/* And invoke the emulator proper. */
	{
		size_t req_unwind_rega = 8; /* XXX: Allow for an arch-specific hint for this value! */
		for (;;) {
			result = run_entry_value_emulator(self, req_unwind_rega, &req_unwind_rega);
			if (result != _UNWIND_TOO_FEW_UNWIND_REGISTER_OVERRIDE_SLOTS)
				break;
		}
	}

	/* Restore the old emulator state. */
	self->ue_pc       = saved_pc;
	self->ue_pc_start = saved_pc_start;
	self->ue_pc_end   = saved_pc_end;
	self->ue_regset   = saved_regset;

	return result;
}


DEFINE_PUBLIC_ALIAS(debuginfo_run_entry_value_emulator, libdi_debuginfo_run_entry_value_emulator);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_CFI_ENTRY_C */
