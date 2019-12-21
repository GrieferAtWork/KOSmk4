/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBDEBUGINFO_ADDR2LINE_C
#define GUARD_LIBDEBUGINFO_ADDR2LINE_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include "addr2line.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/exec/library.h>

#include <ctype.h>
#include <elf.h>
#include <string.h>

#include <libdebuginfo/addr2line.h>
#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/debug_line.h>
#include <libdebuginfo/dwarf.h>
#include <libdebuginfo/symtab.h>

#include "debug_aranges.h"
#include "debug_info.h"
#include "debug_line.h"
#include "symtab.h"

#ifdef __KERNEL__
#include <kernel/driver.h>
#endif /* __KERNEL__ */


DECL_BEGIN

LOCAL TEXTSECTION NONNULL((1)) void
NOTHROW_NCX(CC fill_error_state)(di_debug_addr2line_t *__restrict result,
                                 uintptr_t module_relative_pc) {
	memset(result, 0, sizeof(*result));
	result->al_symstart  = module_relative_pc;
	result->al_symend    = module_relative_pc;
	result->al_linestart = module_relative_pc;
	result->al_lineend   = module_relative_pc;
}

#ifdef __KERNEL__
INTDEF byte_t __kernel_debug_line_start[];
#endif /* __KERNEL__ */


/* Search .symtab for the nearest symbol and fill in:
 *   - result->al_rawname
 *   - result->al_symstart  (only if `fill_symstart_symend' is true)
 *   - result->al_symend    (only if `fill_symstart_symend' is true)
 */
PRIVATE TEXTSECTION NONNULL((1, 2)) void
NOTHROW_NCX(CC search_symtab)(di_debug_sections_t const *__restrict sections,
                              di_debug_addr2line_t *__restrict result,
                              uintptr_t module_relative_pc,
                              bool fill_symstart_symend) {
	byte_t const *symaddr;
	symaddr = libdi_symtab_scantable(sections->ds_symtab_start,
	                                 sections->ds_symtab_end,
	                                 sections->ds_symtab_ent,
	                                 module_relative_pc);
	if (symaddr) {
		uint32_t name_offset;
		if (sections->ds_symtab_ent == sizeof(Elf32_Sym)) {
			name_offset = ((Elf32_Sym const *)symaddr)->st_name;
			if (fill_symstart_symend) {
				result->al_symstart = (uintptr_t)((Elf32_Sym const *)symaddr)->st_value;
				result->al_symend   = result->al_symstart + (size_t)((Elf32_Sym const *)symaddr)->st_size;
			}
		} else {
			name_offset = ((Elf64_Sym const *)symaddr)->st_name;
			if (fill_symstart_symend) {
				result->al_symstart = (uintptr_t)((Elf64_Sym const *)symaddr)->st_value;
				result->al_symend   = result->al_symstart + (size_t)((Elf64_Sym const *)symaddr)->st_size;
			}
		}
		if (name_offset < (size_t)((char *)sections->ds_strtab_end -
		                           (char *)sections->ds_strtab_start))
			result->al_rawname = (char *)sections->ds_strtab_start + name_offset;
	}
	/* Special case: The kernel core doesn't include its internal `.symtab' as part of its binary
	 *               image. This, combined with the fact that the kernel uses a custom protocol for
	 *               declaring its exported symbols requires special handling if the caller is requesting
	 *               information about the core itself.
	 *               In this case, we can use the driver-api function `driver_symbol_at()', which includes
	 *               special handling for reversing the names of public functions exported by the kernel
	 *               core (However, this doesn't work for private/internal functions...)
	 * TODO: A similar special case should exist for `libdl.so'! */
#ifdef __KERNEL__
	else if (sections->ds_debug_line_start == __kernel_debug_line_start) {
		char const *name;
		size_t sym_size;
		name = driver_symbol_at(&kernel_driver, module_relative_pc,
		                        &result->al_symstart, &sym_size);
		if (name) {
			result->al_symend  = result->al_symstart + sym_size;
			result->al_rawname = (char *)name;
		}
	}
#endif /* __KERNEL__ */
}

#define DEBUG_INFO_ERROR_NOLEVEL 3 /* No information is associated with the given level. */

PRIVATE TEXTSECTION NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC scan_cu_stmt_list)(di_debuginfo_compile_unit_t const *__restrict cu,
                                  di_debug_sections_t const *__restrict sections,
                                  di_debug_addr2line_t *__restrict result,
                                  uintptr_t module_relative_pc,
                                  uintptr_t level) {
	if (cu->cu_stmt_list < (size_t)(sections->ds_debug_line_end - sections->ds_debug_line_start)) {
		unsigned int error;
		di_debugline_unit_t unit;
		di_debugline_info_t info;
		byte_t *debug_line_reader;
		debug_line_reader = sections->ds_debug_line_start + cu->cu_stmt_list;
		error = libdi_debugline_loadunit(&debug_line_reader,
		                                 sections->ds_debug_line_end,
		                                 &unit);
		if (error == DEBUG_INFO_ERROR_SUCCESS) {
			error = libdi_debugline_scanunit(&unit, &info, module_relative_pc);
			if (error == DEBUG_INFO_ERROR_SUCCESS) {
				if (level != 0 &&
				    level != DEBUG_ADDR2LINE_LEVEL_SOURCE) {
					fill_error_state(result, module_relative_pc);
					result->al_levelcnt = 1;
					return DEBUG_INFO_ERROR_NOLEVEL;
				}
				result->al_levelcnt  = 1;
				result->al_symstart  = info.dl_linestart;
				result->al_symend    = info.dl_lineend;
				result->al_linestart = info.dl_linestart;
				result->al_lineend   = info.dl_lineend;
				result->al_linediscr = info.dl_discriminator;
				result->al_rawname   = NULL;
				result->al_name      = NULL;
				result->al_cuname    = cu->cu_name;
				result->al_cubase    = cu->cu_comp_dir;
				result->al_srcline   = info.dl_srcline;
				result->al_srccol    = info.dl_srccol;
				result->al_dclpath   = NULL;
				result->al_dclfile   = NULL;
				result->al_dclline   = 0;
				result->al_dclcol    = 0;
				debugline_loadfile(&unit,
				                   info.dl_srcfile,
				                   &result->al_srcpath,
				                   &result->al_srcfile);
				/* Try to substitute symbol name information by searching through .symtab */
				search_symtab(sections, result, module_relative_pc, true);
				return DEBUG_INFO_ERROR_SUCCESS;
			}
		}
	}
	return DEBUG_INFO_ERROR_NOFRAME;
}


PRIVATE ATTR_NOINLINE TEXTSECTION NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC search_cu)(di_debuginfo_cu_parser_t *__restrict self,
                          di_debug_sections_t const *__restrict sections,
                          di_debug_addr2line_t *__restrict result,
                          uintptr_t module_relative_pc,
                          uintptr_t level,
                          bool assume_correct_cu) {
	unsigned int error;
again:
	switch (self->dup_comp.dic_tag) {

	case DW_TAG_compile_unit: {
		di_debuginfo_compile_unit_t cu;
		uintptr_t cu_depth;
		/* Load attributes of the compilation unit. */
		if (!libdi_debuginfo_cu_parser_loadattr_compile_unit(self, &cu))
			goto err_corrupt;
		if (!assume_correct_cu) {
			error = debuginfo_ranges_contains(&cu.cu_ranges, self,
			                                  cu.cu_ranges.r_startpc,
			                                  module_relative_pc,
			                                  sections->ds_debug_ranges_start,
			                                  sections->ds_debug_ranges_end);
			if (error == DEBUG_INFO_ERROR_NOFRAME)
				goto next_root;
		}
		cu_depth = self->dup_child_depth;
		if (!libdi_debuginfo_cu_parser_next(self))
			goto done_scan_cu_stmt_list;
again_cu_component:
		while (self->dup_child_depth > cu_depth) {
			/* Scan components of this CU. */
			switch (self->dup_comp.dic_tag) {

			case DW_TAG_subprogram: {
				di_debuginfo_subprogram_t sp;
				di_debuginfo_inlined_subroutine_t is;
				di_debugline_unit_t unit;
				di_debugline_info_t info;
				byte_t *debug_line_reader;
				byte_t *subprogram_child_start;
				byte_t *innermost_is_subprogram;
				size_t inline_recursion;
				uintptr_t subprogram_depth;
				if (!libdi_debuginfo_cu_parser_loadattr_subprogram(self, &sp))
					goto err_corrupt;
				subprogram_depth = self->dup_child_depth;

				/* Check if the given pointer is apart of this sub-program. */
				error = debuginfo_ranges_contains_ex(&sp.sp_ranges, self,
				                                     cu.cu_ranges.r_startpc,
				                                     module_relative_pc,
				                                     sections->ds_debug_ranges_start,
				                                     sections->ds_debug_ranges_end,
				                                     &result->al_symstart,
				                                     &result->al_symend);
				if (error != DEBUG_INFO_ERROR_SUCCESS) {
					/* Must be apart of a different sub-program. */
					for (;;) {
						if (!libdi_debuginfo_cu_parser_next(self))
							goto done_scan_cu_stmt_list;
						if (self->dup_child_depth <= subprogram_depth)
							goto again_cu_component;
						libdi_debuginfo_cu_parser_skipattr(self);
					}
				}
				/* >> inline __attribute__((always_inline)) void inline_function(void) {
				 * >> 	__asm__("nop");
				 * >> }
				 * >> inline __attribute__((always_inline)) void inline_function2(void) {
				 * >> 	inline_function();
				 * >> }
				 * >> 
				 * >> extern __attribute__((visibility("hidden"))) void *test_function(void) {
				 * >> 	void *result;
				 * >> 	__asm__ __volatile__("mov %1, %0" : "=g" (result) : "r" (&&foo));
				 * >> foo:
				 * >> 	inline_function2();
				 * >> 	return result;
				 * >> }
				 * LEVEL(0,test_function()) --> inline_function
				 * LEVEL(1,test_function()) --> inline_function2
				 * LEVEL(2,test_function()) --> test_function
				 */
				/* Search for inlined sub-programs */
				if (!self->dup_comp.dic_haschildren) {
					/* No children --> no sub-programs! */
					if (level != DEBUG_ADDR2LINE_LEVEL_SOURCE && level != 0) {
						fill_error_state(result, module_relative_pc);
						result->al_levelcnt = 1;
						return DEBUG_INFO_ERROR_NOLEVEL;
					}
					result->al_levelcnt = 1;
fill_result_sp:
					result->al_rawname = sp.sp_rawname;
					result->al_name    = sp.sp_name;
					/* Scan the symbol tables for names. */
					if (!sp.sp_rawname && !sp.sp_name)
						search_symtab(sections, result, module_relative_pc, false);
					result->al_cuname  = cu.cu_name;
					result->al_cubase  = cu.cu_comp_dir;
					result->al_dclline = sp.sp_decl_line;
					result->al_dclcol  = sp.sp_decl_column;
					if (cu.cu_stmt_list < (size_t)(sections->ds_debug_line_end - sections->ds_debug_line_start)) {
						debug_line_reader = sections->ds_debug_line_start + cu.cu_stmt_list;
						error = libdi_debugline_loadunit(&debug_line_reader,
						                                 sections->ds_debug_line_end,
						                                 &unit);
						if (error != DEBUG_INFO_ERROR_SUCCESS)
							goto fill_result_sp_any_cu;
						debugline_loadfile(&unit, sp.sp_decl_file,
						                   &result->al_dclpath,
						                   &result->al_dclfile);
						/* Scan this CU for source-level information. */
						error = libdi_debugline_scanunit(&unit, &info, module_relative_pc);
						if (error == DEBUG_INFO_ERROR_SUCCESS) {
fill_result_debugline_success:
							result->al_linestart = info.dl_linestart;
							result->al_lineend   = info.dl_lineend;
							result->al_linediscr = (uintptr_t)info.dl_discriminator;
							debugline_loadfile(&unit, info.dl_srcfile,
							                   &result->al_srcpath,
							                   &result->al_srcfile);
							result->al_srcline = info.dl_srcline;
							result->al_srccol  = info.dl_srccol;
						} else {
fill_result_debugline_failure:
							result->al_linestart = module_relative_pc;
							result->al_lineend   = module_relative_pc;
							result->al_linediscr = 0;
							result->al_srcpath   = NULL;
							result->al_srcfile   = NULL;
							result->al_srcline   = 0;
							result->al_srccol    = 0;
						}
						return DEBUG_INFO_ERROR_SUCCESS;
					}
fill_result_sp_any_cu:
					result->al_dclpath = NULL;
					result->al_dclfile = NULL;
					debug_line_reader  = sections->ds_debug_line_start;
					for (;;) {
						error = libdi_debugline_loadunit(&debug_line_reader, sections->ds_debug_line_end, &unit);
						if (error != DEBUG_INFO_ERROR_SUCCESS)
							break;
						error = libdi_debugline_scanunit(&unit, &info, module_relative_pc);
						if (error == DEBUG_INFO_ERROR_SUCCESS)
							goto fill_result_debugline_success;
					}
					goto fill_result_debugline_failure;
				}
				/* Figure out how many levels of line function recursion are present at this location. */
				inline_recursion        = 1;
				subprogram_child_start  = self->dup_cu_info_pos;
				innermost_is_subprogram = NULL;
				for (;;) {
					if (!libdi_debuginfo_cu_parser_next(self))
						break;
					if (self->dup_child_depth <= subprogram_depth)
						break;
					if (self->dup_comp.dic_tag == DW_TAG_inlined_subroutine) {
						uintptr_t innermost_inline_symstart;
						uintptr_t innermost_inline_symend;
						if (!libdi_debuginfo_cu_parser_loadattr_inlined_subroutine(self, &is))
							break;
						/* Check if our PC is apart of the inline-function's body. */
						error = debuginfo_ranges_contains_ex(&is.is_ranges, self,
						                                     cu.cu_ranges.r_startpc,
						                                     module_relative_pc,
						                                     sections->ds_debug_ranges_start,
						                                     sections->ds_debug_ranges_end,
						                                     &innermost_inline_symstart,
						                                     &innermost_inline_symend);
						if (error == DEBUG_INFO_ERROR_SUCCESS) {
							innermost_is_subprogram = is.is_subprogram;
							++inline_recursion; /* Yet, it is! (this inline function makes up one of the known levels!) */
							if (level == 0) {
								result->al_symstart = innermost_inline_symstart;
								result->al_symend   = innermost_inline_symend;
							}
						}
					} else {
						libdi_debuginfo_cu_parser_skipattr(self);
					}
				}
				if (level == DEBUG_ADDR2LINE_LEVEL_SOURCE)
					level = inline_recursion - 1;
				if unlikely(level >= inline_recursion) {
					fill_error_state(result, module_relative_pc);
					result->al_levelcnt = inline_recursion;
					return DEBUG_INFO_ERROR_NOLEVEL;
				}
				result->al_levelcnt = inline_recursion;
				if (level == 0) {
					if (inline_recursion > 1) {
						/* Top-level source information (aka. return information about the top-most
						 * inline function). NOTE: Re-use the SP-loader code, but override the SP
						 * values to instead refer to information about the inline function. */
						if (!innermost_is_subprogram ||
						    (self->dup_cu_info_pos = innermost_is_subprogram,
						     !libdi_debuginfo_cu_parser_next(self)) ||
						    !libdi_debuginfo_cu_parser_loadattr_subprogram(self, &sp)) {
							/* Failed to load information about the inline function -> Just post NULL-info for it. */
							sp.sp_rawname     = NULL;
							sp.sp_name        = NULL;
							sp.sp_decl_line   = 0;
							sp.sp_decl_column = 0;
							sp.sp_decl_file   = 0;
						}
					}
					goto fill_result_sp;
				}
				/* Request for source information about an inline function call-site.
				 * For this, we must gather information from 2 locations:
				 *   The addr2line file/line/col information must be taken from the
				 *   first inline function encountered after `(inline_recursion - level) - 1'
				 *   others have been skipped, where it is specified through the inline
				 *   call-site-location attributes.
				 *   The addr2line name/decl information must be taken from the
				 *   first inline function encountered after `(inline_recursion - level) - 2'
				 *   others have been skipped, where it is available through the SP pointed
				 *   to by the information. - However, when `level == inline_recursion - 1',
				 *   this information must instead be taken directly from the original `SP'!
				 */
				inline_recursion = (inline_recursion - level) - 1;
				/* `inline_recursion' now specifies the number of inline functions to skip
				 * before the one containing the call-site source location information required
				 * to fill in the file/line/col information of the result is reached.
				 * Additionally, when `inline_recursion == 1', the then-loaded inline function
				 * must be loaded into `sp', since it is the one from where the call actually
				 * happens. */

				/* Rewind to the start of child components of this sub-program. */
				self->dup_cu_info_pos          = subprogram_child_start;
				self->dup_child_depth          = subprogram_depth;
				self->dup_comp.dic_haschildren = DW_CHILDREN_yes;
				for (;;) {
					if (!libdi_debuginfo_cu_parser_next(self))
						break;
					if (self->dup_child_depth <= subprogram_depth)
						break;
					if (self->dup_comp.dic_tag == DW_TAG_inlined_subroutine) {
						if (!libdi_debuginfo_cu_parser_loadattr_inlined_subroutine(self, &is))
							break;
						/* Check if our PC is apart of the inline-function's body. */
						error = debuginfo_ranges_contains_ex(&is.is_ranges, self,
						                                     cu.cu_ranges.r_startpc,
						                                     module_relative_pc,
						                                     sections->ds_debug_ranges_start,
						                                     sections->ds_debug_ranges_end,
						                                     &result->al_linestart,
						                                     &result->al_lineend);
						if (error == DEBUG_INFO_ERROR_SUCCESS) {
							/* This is one of ours */
							if (inline_recursion == 1) {
								uint8_t old_has_children;
								/* This is the level that dictates the containing SP */
								subprogram_child_start = self->dup_cu_info_pos;
								subprogram_depth       = self->dup_child_depth;
								old_has_children       = self->dup_comp.dic_haschildren;
								if (!is.is_subprogram ||
								    (self->dup_cu_info_pos = is.is_subprogram,
								     !libdi_debuginfo_cu_parser_next(self)) ||
								    !libdi_debuginfo_cu_parser_loadattr_subprogram(self, &sp)) {
									sp.sp_rawname     = NULL;
									sp.sp_name        = NULL;
									sp.sp_decl_line   = 0;
									sp.sp_decl_column = 0;
									sp.sp_decl_file   = 0;
								}
								self->dup_cu_info_pos          = subprogram_child_start;
								self->dup_child_depth          = subprogram_depth;
								self->dup_comp.dic_haschildren = old_has_children;
							} else if (inline_recursion == 0) {
								break;
							}
							--inline_recursion;
						}
					} else {
						libdi_debuginfo_cu_parser_skipattr(self);
					}
				}
				/* At this point, the resulting file/line/col information
				 * is available via the call-site fields of `is', while
				 * information about the containing function is stored
				 * within `sp' */
				result->al_linediscr = 0;
				result->al_rawname   = sp.sp_rawname;
				result->al_name      = sp.sp_name;
				/* Scan the symbol tables for names. */
				if (!sp.sp_rawname && !sp.sp_name)
					search_symtab(sections, result, module_relative_pc, false);
				result->al_cuname  = cu.cu_name;
				result->al_cubase  = cu.cu_comp_dir;
				result->al_srcline = is.is_call_line;
				result->al_srccol  = is.is_call_column;
				result->al_dclline = sp.sp_decl_line;
				result->al_dclcol  = sp.sp_decl_column;
				result->al_srcpath = NULL;
				result->al_srcfile = NULL;
				result->al_dclpath = NULL;
				result->al_dclfile = NULL;
				/* Load the debug_line program so we can decode file names. */
				if (cu.cu_stmt_list < (size_t)(sections->ds_debug_line_end - sections->ds_debug_line_start)) {
					debug_line_reader = sections->ds_debug_line_start + cu.cu_stmt_list;
					error             = libdi_debugline_loadunit(&debug_line_reader, sections->ds_debug_line_end, &unit);
					if (error == DEBUG_INFO_ERROR_SUCCESS) {
						debugline_loadfile(&unit, sp.sp_decl_file, &result->al_dclpath, &result->al_dclfile);
						debugline_loadfile(&unit, is.is_call_file, &result->al_srcpath, &result->al_srcfile);
					}
				}
				return DEBUG_INFO_ERROR_SUCCESS;
			}	break;

			default:
				libdi_debuginfo_cu_parser_skipattr(self);
/*next_cu_component:*/
				if (!libdi_debuginfo_cu_parser_next(self))
					goto done_scan_cu_stmt_list;
				break;
			}
		}
		/* We're supposed to be apart of this CU, but couldn't find the associated function.
		 * -> In any case, manually scan through the .debug_line tab (if it exists) */
		error = scan_cu_stmt_list(&cu, sections, result, module_relative_pc, level);
		if unlikely(error != DEBUG_INFO_ERROR_NOFRAME)
			return error;
		goto again;
done_scan_cu_stmt_list:
		error = scan_cu_stmt_list(&cu, sections, result, module_relative_pc, level);
		if unlikely(error != DEBUG_INFO_ERROR_NOFRAME)
			return error;
		goto done;
	}	break;


	default:
/*next_root_skipattr:*/
		libdi_debuginfo_cu_parser_skipattr(self);
next_root:
		if (libdi_debuginfo_cu_parser_next(self))
			goto again;
		break;
	}
done:
	return DEBUG_INFO_ERROR_NOFRAME;
err_corrupt:
	return DEBUG_INFO_ERROR_CORRUPT;
}

/* Analyze data from the given `sections' to locate source-level information about `module_relative_pc'.
 * @param: sections: The mapping locations for the different debug sections associated with the program.
 *                   This structure must be initialized with available section information by the caller,
 *                   although for minimal functionality, only the .debug_line section is required.
 *                   Note however that other sections are mandatory (and recommended) in order to
 *                   provide full support of available features.
 * @param: level:    Inline function indirection depth for the location to query.
 *                   Level #0 always refers to the exact source location, as retrievable
 *                   via the .debug_line program, while all levels greater than this refer
 *                   to the call-sites of inlined functions found at that location.
 *                   Alternatively, you may also pass `DEBUG_ADDR2LINE_LEVEL_SOURCE', which
 *                   always refers to the top-most, non-inlined source location.
 * @param: flags:    Set of `DEBUG_ADDR2LINE_F*'
 * >> di_debug_addr2line_t info;
 * >> addr2line_errno_t error;
 * >> uintptr_t level = 0;
 * >> do {
 * >>     error = debug_sections_addr2line((uintptr_t)ptr,&info,level);
 * >>     if (error != DEBUG_INFO_ERROR_SUCCESS)
 * >>         break;
 * >>     printk("%s(%Iu) : %s : HERE\n",
 * >>            info.al_srcfile,
 * >>            info.al_srcline,
 * >>            info.al_name);
 * >> } while (++level < info.al_levelcnt);
 * @return: DEBUG_INFO_ERROR_SUCCESS: Successfully retrieved information.
 * @return: DEBUG_INFO_ERROR_NOFRAME: Either no information is known about `module_relative_pc',
 *                                    or the given `level >= OUT(result->al_levelcnt)', and also
 *                                    isn't equal to `DEBUG_ADDR2LINE_LEVEL_SOURCE', where
 *                                    `result->al_levelcnt' is set to 0 if no information is
 *                                    known at all, or whatever the total number of information
 *                                    levels know is.
 * @return: DEBUG_INFO_ERROR_CORRUPT: Debug information is corrupted. */
INTERN TEXTSECTION NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libdi_debug_sections_addr2line)(di_debug_sections_t const *__restrict sections,
                                               di_debug_addr2line_t *__restrict result,
                                               uintptr_t module_relative_pc,
                                               uintptr_t level,
                                               uintptr_t flags) {
	unsigned int error;
	if unlikely(sections->ds_debug_line_end <= sections->ds_debug_line_start) {
		/* Scan the symbol tables. */
		fill_error_state(result, module_relative_pc);
		search_symtab(sections, result, module_relative_pc, true);
		if (result->al_rawname) {
			result->al_levelcnt = 1;
			return DEBUG_INFO_ERROR_SUCCESS;
		}
		return DEBUG_INFO_ERROR_NOFRAME; /* No information available... */
	}
	if (sections->ds_debug_info_start < sections->ds_debug_info_end &&
	    sections->ds_debug_abbrev_start < sections->ds_debug_abbrev_end) {
		di_debuginfo_cu_parser_t cu;
		di_debuginfo_cu_abbrev_t abbrev;
		di_debuginfo_cu_parser_sections_t cu_sections;
		uintptr_t debuginfo_cu_offset;
		byte_t *cu_start;
		bool has_corruptions;
		cu_sections.cps_debug_abbrev_start = sections->ds_debug_abbrev_start;
		cu_sections.cps_debug_abbrev_end   = sections->ds_debug_abbrev_end;
		cu_sections.cps_debug_loc_start    = NULL;
		cu_sections.cps_debug_loc_end      = NULL;
		cu_sections.cps_debug_str_start    = sections->ds_debug_str_start;
		cu_sections.cps_debug_str_end      = sections->ds_debug_str_end;

		/* Use .debug_aranges to narrow down the search to a single CU. */
		if (sections->ds_debug_aranges_start < sections->ds_debug_aranges_end) {
			error = libdi_debugaranges_locate(sections->ds_debug_aranges_start,
			                                  sections->ds_debug_aranges_end,
			                                  &debuginfo_cu_offset,
			                                  module_relative_pc);
			if (error == DEBUG_INFO_ERROR_SUCCESS) {
				if (debuginfo_cu_offset < (size_t)(sections->ds_debug_info_end - sections->ds_debug_info_start)) {
					cu_start = sections->ds_debug_info_start + debuginfo_cu_offset;
					error = libdi_debuginfo_cu_parser_loadunit(&cu_start, sections->ds_debug_info_end,
					                                           &cu_sections, &cu, &abbrev, NULL);
					if (error == DEBUG_INFO_ERROR_SUCCESS) {
						/* Search the specified CU */
						error = search_cu(&cu, sections, result, module_relative_pc, level, true);
						libdi_debuginfo_cu_abbrev_fini(&abbrev);
						if (error == DEBUG_INFO_ERROR_SUCCESS)
							goto done_success;
						if (error == DEBUG_INFO_ERROR_NOLEVEL)
							goto err_nodata;
						/* If the CU doesn't contain information and we're not supposed to try
						 * hard, trust the contents of the .debug_aranges section and assume
						 * that no information for the specified address exists. */
						if (error == DEBUG_INFO_ERROR_NOFRAME &&
						    !(flags & DEBUG_ADDR2LINE_FTRYHARD))
							goto err_nodata_nolevel;
					}
				}
			} else if (error == DEBUG_INFO_ERROR_NOFRAME) {
				/* Trust the .debug_aranges section and assume that no information exists. */
				if (!(flags & DEBUG_ADDR2LINE_FTRYHARD))
					goto err_nodata_nolevel;
			}
		}
		/* Search every CU for the specified location. */
		has_corruptions = false;
		cu_start        = sections->ds_debug_info_start;
		for (;;) {
			error = libdi_debuginfo_cu_parser_loadunit(&cu_start, sections->ds_debug_info_end,
			                                           &cu_sections, &cu, &abbrev, NULL);
			if (error != DEBUG_INFO_ERROR_SUCCESS)
				break;
			/* Search the CU */
			error = search_cu(&cu, sections, result, module_relative_pc, level, false);
			libdi_debuginfo_cu_abbrev_fini(&abbrev);
			if (error == DEBUG_INFO_ERROR_SUCCESS)
				goto done_success;
			if (error == DEBUG_INFO_ERROR_NOLEVEL)
				goto err_nodata;
			if (error == DEBUG_INFO_ERROR_CORRUPT)
				has_corruptions = true;
			/* Continue searching the next CU... */
		}

		/* If there were no corruptions, and we're not supposed to try hard,
		 * fail now so we don't have to scan every single addr2line CU. */
		if (!has_corruptions && !(flags & DEBUG_ADDR2LINE_FTRYHARD))
			goto err_nodata_nolevel;
	}

	/* Fallback: Scan the .debug_line section in its entirety. */
	{
		byte_t *reader;
		reader = sections->ds_debug_line_start;
		for (;;) {
			di_debugline_unit_t unit;
			di_debugline_info_t info;
			error = libdi_debugline_loadunit(&reader, sections->ds_debug_line_end, &unit);
			if unlikely(error != DEBUG_INFO_ERROR_SUCCESS)
				goto err_forward;
			/* Scan this CU for source-level information. */
			error = libdi_debugline_scanunit(&unit, &info, module_relative_pc);
			if unlikely(error == DEBUG_INFO_ERROR_CORRUPT)
				goto err_forward;
			if (error == DEBUG_INFO_ERROR_SUCCESS) {
				/* Found it! -> Fill in information */
				if (level != DEBUG_ADDR2LINE_LEVEL_SOURCE && level != 0) {
					fill_error_state(result, module_relative_pc);
					result->al_levelcnt = 1;
					return DEBUG_INFO_ERROR_NOFRAME;
				}
				result->al_levelcnt  = 1;
				result->al_symstart  = info.dl_linestart;
				result->al_symend    = info.dl_lineend;
				result->al_linestart = info.dl_linestart;
				result->al_lineend   = info.dl_lineend;
				result->al_linediscr = (uintptr_t)info.dl_discriminator;
				result->al_rawname   = NULL;
				result->al_name      = NULL;
				/* Scan the symbol tables for names. */
				search_symtab(sections, result, module_relative_pc, false);
				result->al_cuname = NULL;
				result->al_cubase = NULL;
				debugline_loadfile(&unit, info.dl_srcfile,
				                   &result->al_srcpath,
				                   &result->al_srcfile);
				result->al_srcline = info.dl_srcline;
				result->al_srccol  = info.dl_srccol;
				result->al_dclpath = NULL;
				result->al_dclfile = NULL;
				result->al_dclline = 0;
				result->al_dclcol  = 0;
done_success:
				return DEBUG_INFO_ERROR_SUCCESS;
			}
		}
	}
err_nodata_nolevel:
	fill_error_state(result, module_relative_pc);
err_nodata:
	return DEBUG_INFO_ERROR_NOFRAME;
err_forward:
	fill_error_state(result, module_relative_pc);
	return error;
}


PRIVATE STRINGSECTION char const str_forward_slash[] = { '/' };
PRIVATE STRINGSECTION char const str_backward_slash[] = { '\\' };
INTDEF STRINGSECTION char const unknown_string[]; /* "???" */

INTERN TEXTSECTION NONNULL((1)) ssize_t CC
libdi_debug_print_filename(pformatprinter printer, void *arg,
                           char const *cubase, char const *pathname,
                           char const *filename) {
	ssize_t temp, result = 0;
	unsigned int strid;
	if (pathname && (pathname[0] == '/' ||
	                 (pathname[1] == ':' && isupper(pathname[0])))) {
		cubase = NULL; /* `pathname' is an absolute path (can happen for
		                *  system include paths such as /usr/include) */
	}
	for (strid = 0; strid < 2; ++strid) {
		char const *str;
		size_t slen;
		str = strid ? pathname : cubase;
		if (!str)
			continue;
		if (strid != 0 && cubase != NULL) {
			while (*str == '/' || *str == '\\')
				++str;
		}
		slen = strlen(str);
		while (slen &&
		       (str[slen - 1] == '/' ||
		        str[slen - 1] == '\\'))
			--slen;
		if (str[slen] == '/' ||
		    str[slen] == '\\') {
			temp = (*printer)(arg, str, slen + 1);
		} else {
			temp = (*printer)(arg, str, slen);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			if ((cubase && strchr(cubase, '\\')) ||
			    (pathname && strchr(pathname, '\\')) ||
			    (filename && strchr(filename, '\\'))) {
				temp = (*printer)(arg, str_backward_slash, 1);
			} else {
				temp = (*printer)(arg, str_forward_slash, 1);
			}
		}
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	temp = filename
	       ? (*printer)(arg, filename, strlen(filename))
	       : (*printer)(arg, unknown_string, 3);
	if unlikely(temp < 0)
		goto err;
	result += temp;
	return result;
err:
	return temp;
}



PRIVATE STRINGSECTION char const secname_debug_line[]    = ".debug_line";
PRIVATE STRINGSECTION char const secname_debug_info[]    = ".debug_info";
PRIVATE STRINGSECTION char const secname_debug_abbrev[]  = ".debug_abbrev";
PRIVATE STRINGSECTION char const secname_debug_aranges[] = ".debug_aranges";
PRIVATE STRINGSECTION char const secname_debug_str[]     = ".debug_str";
PRIVATE STRINGSECTION char const secname_debug_ranges[]  = ".debug_ranges";
PRIVATE STRINGSECTION char const secname_symtab[]        = ".symtab";
PRIVATE STRINGSECTION char const secname_strtab[]        = ".strtab";
PRIVATE STRINGSECTION char const secname_dynsym[]        = ".dynsym";
PRIVATE STRINGSECTION char const secname_dynstr[]        = ".dynstr";


/* Load debug sections, given a handle to a module, as returned by dlopen()
 * >> These functions are simply light-weight wrappers around `library_locksection()',
 *    taking the job of locking debug information sections into memory off of
 *    the user. */
INTERN TEXTSECTION NONNULL((2, 3)) unsigned int
NOTHROW_NCX(CC libdi_debug_dllocksections)(void *dl_handle,
                                           di_debug_sections_t *__restrict sections,
                                           di_dl_debug_sections_t *__restrict dl_sections) {
	memset(sections, 0, sizeof(*sections));
	if unlikely(!dl_handle)
		goto err_no_data;
	dl_sections->dl_debug_line = library_locksection((library_handle_t)dl_handle,
	                                                 secname_debug_line,
	                                                 LIBRARY_LOCKSECTION_FNORMAL);
	if (!dl_sections->dl_debug_line) {
		/* No debug information sections */
		dl_sections->dl_debug_info = NULL;
set_no_extened_debug_info_2:
		dl_sections->dl_debug_abbrev = NULL;
set_no_extened_debug_info:
		dl_sections->dl_debug_aranges = NULL;
		dl_sections->dl_debug_str     = NULL;
		dl_sections->dl_debug_ranges  = NULL;
	} else {
		/* Load .debug_info and .dl_debug_abbrev */
		dl_sections->dl_debug_info = library_locksection((library_handle_t)dl_handle, secname_debug_info, LIBRARY_LOCKSECTION_FNORMAL);
		if (!dl_sections->dl_debug_info)
			goto set_no_extened_debug_info_2;
		dl_sections->dl_debug_abbrev = library_locksection((library_handle_t)dl_handle, secname_debug_abbrev, LIBRARY_LOCKSECTION_FNORMAL);
		if (!dl_sections->dl_debug_abbrev) {
			library_unlocksection(dl_sections->dl_debug_info);
			goto set_no_extened_debug_info;
		}
		/* All all of the remaining debug information sections (which are optional, though) */
		dl_sections->dl_debug_aranges = library_locksection((library_handle_t)dl_handle, secname_debug_aranges, LIBRARY_LOCKSECTION_FNORMAL);
		dl_sections->dl_debug_str     = library_locksection((library_handle_t)dl_handle, secname_debug_str, LIBRARY_LOCKSECTION_FNORMAL);
		dl_sections->dl_debug_ranges  = library_locksection((library_handle_t)dl_handle, secname_debug_ranges, LIBRARY_LOCKSECTION_FNORMAL);
	}
	dl_sections->dl_symtab = library_locksection((library_handle_t)dl_handle, secname_symtab, LIBRARY_LOCKSECTION_FNORMAL);
	if (dl_sections->dl_symtab) {
		dl_sections->dl_strtab = library_locksection((library_handle_t)dl_handle, secname_strtab, LIBRARY_LOCKSECTION_FNORMAL);
		if unlikely(!dl_sections->dl_strtab) {
			library_unlocksection(dl_sections->dl_symtab);
			goto try_load_dynsym;
		}
	} else {
		dl_sections->dl_strtab = NULL;
try_load_dynsym:
		dl_sections->dl_symtab = library_locksection((library_handle_t)dl_handle, secname_dynsym, LIBRARY_LOCKSECTION_FNORMAL);
		if (dl_sections->dl_symtab) {
			dl_sections->dl_strtab = library_locksection((library_handle_t)dl_handle, secname_dynstr, LIBRARY_LOCKSECTION_FNORMAL);
			if unlikely(!dl_sections->dl_strtab) {
				library_unlocksection(dl_sections->dl_symtab);
				goto handle_missing_symbol_tables;
			}
		} else {
handle_missing_symbol_tables:
			/* Check if we've got anything at all... */
			if (!dl_sections->dl_debug_line) {
err_no_data:
				memset(dl_sections, 0, sizeof(*dl_sections));
				return DEBUG_INFO_ERROR_NOFRAME; /* Nope; nothing... */
			}
		}
	}
#define SECSRT(x) ((byte_t *)(x)->ds_data)
#define SECEND(x) ((byte_t *)(x)->ds_data + (x)->ds_size)
	/* Fill in section mapping information. */
	if (dl_sections->dl_debug_line) {
		sections->ds_debug_line_start = SECSRT(dl_sections->dl_debug_line);
		sections->ds_debug_line_end   = SECEND(dl_sections->dl_debug_line);
	}
	if (dl_sections->dl_debug_info) {
		sections->ds_debug_info_start = SECSRT(dl_sections->dl_debug_info);
		sections->ds_debug_info_end   = SECEND(dl_sections->dl_debug_info);
	}
	if (dl_sections->dl_debug_abbrev) {
		sections->ds_debug_abbrev_start = SECSRT(dl_sections->dl_debug_abbrev);
		sections->ds_debug_abbrev_end   = SECEND(dl_sections->dl_debug_abbrev);
	}
	if (dl_sections->dl_debug_aranges) {
		sections->ds_debug_aranges_start = SECSRT(dl_sections->dl_debug_aranges);
		sections->ds_debug_aranges_end   = SECEND(dl_sections->dl_debug_aranges);
	}
	if (dl_sections->dl_debug_str) {
		sections->ds_debug_str_start = SECSRT(dl_sections->dl_debug_str);
		sections->ds_debug_str_end   = SECEND(dl_sections->dl_debug_str);
	}
	if (dl_sections->dl_debug_ranges) {
		sections->ds_debug_ranges_start = SECSRT(dl_sections->dl_debug_ranges);
		sections->ds_debug_ranges_end   = SECEND(dl_sections->dl_debug_ranges);
	}
	if (dl_sections->dl_symtab) {
		sections->ds_symtab_start = SECSRT(dl_sections->dl_symtab);
		sections->ds_symtab_end   = SECEND(dl_sections->dl_symtab);
		sections->ds_symtab_ent   = dl_sections->dl_symtab->ds_entsize;
		if (!sections->ds_symtab_ent)
			sections->ds_symtab_ent = sizeof(Elf_Sym);
	}
	if (dl_sections->dl_strtab) {
		sections->ds_strtab_start = SECSRT(dl_sections->dl_strtab);
		sections->ds_strtab_end   = SECEND(dl_sections->dl_strtab);
	}
	return DEBUG_INFO_ERROR_SUCCESS;
}

INTERN TEXTSECTION NONNULL((1)) void
NOTHROW_NCX(CC libdi_debug_dlunlocksections)(di_dl_debug_sections_t *__restrict dl_sections) {
	if (dl_sections->dl_strtab)
		library_unlocksection(dl_sections->dl_strtab);
	if (dl_sections->dl_symtab)
		library_unlocksection(dl_sections->dl_symtab);
	if (dl_sections->dl_debug_ranges)
		library_unlocksection(dl_sections->dl_debug_ranges);
	if (dl_sections->dl_debug_str)
		library_unlocksection(dl_sections->dl_debug_str);
	if (dl_sections->dl_debug_aranges)
		library_unlocksection(dl_sections->dl_debug_aranges);
	if (dl_sections->dl_debug_abbrev)
		library_unlocksection(dl_sections->dl_debug_abbrev);
	if (dl_sections->dl_debug_info)
		library_unlocksection(dl_sections->dl_debug_info);
	if (dl_sections->dl_debug_line)
		library_unlocksection(dl_sections->dl_debug_line);
#ifndef NDEBUG
	memset(dl_sections, 0xcc, sizeof(*dl_sections));
#endif
}

DEFINE_PUBLIC_ALIAS(debug_sections_addr2line, libdi_debug_sections_addr2line);
DEFINE_PUBLIC_ALIAS(debug_print_filename, libdi_debug_print_filename);
DEFINE_PUBLIC_ALIAS(debug_dllocksections, libdi_debug_dllocksections);
DEFINE_PUBLIC_ALIAS(debug_dlunlocksections, libdi_debug_dlunlocksections);


DECL_END

#endif /* !GUARD_LIBDEBUGINFO_ADDR2LINE_C */
