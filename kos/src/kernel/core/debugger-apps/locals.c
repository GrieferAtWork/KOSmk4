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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_LOCALS_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_LOCALS_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/printk.h>
#include <sched/task.h>

#include <hybrid/overflow.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <alloca.h>
#include <format-printer.h>
#include <stddef.h>
#include <string.h>

#include <libdebuginfo/debug_info.h>
#include <libunwind/cfi.h>
#include <libunwind/unwind.h>

DECL_BEGIN

INTDEF byte_t __kernel_debug_line_start[];
INTDEF byte_t __kernel_debug_line_end[];
INTDEF byte_t __kernel_debug_line_size[];
INTDEF byte_t __kernel_debug_info_start[];
INTDEF byte_t __kernel_debug_info_end[];
INTDEF byte_t __kernel_debug_info_size[];
INTDEF byte_t __kernel_debug_aranges_start[];
INTDEF byte_t __kernel_debug_aranges_end[];
INTDEF byte_t __kernel_debug_aranges_size[];
INTDEF byte_t __kernel_debug_abbrev_start[];
INTDEF byte_t __kernel_debug_abbrev_end[];
INTDEF byte_t __kernel_debug_abbrev_size[];
INTDEF byte_t __kernel_debug_str_start[];
INTDEF byte_t __kernel_debug_str_end[];
INTDEF byte_t __kernel_debug_str_size[];
INTDEF byte_t __kernel_debug_ranges_start[];
INTDEF byte_t __kernel_debug_ranges_end[];
INTDEF byte_t __kernel_debug_ranges_size[];
INTDEF byte_t __kernel_debug_loc_start[];
INTDEF byte_t __kernel_debug_loc_end[];
INTDEF byte_t __kernel_debug_loc_size[];
INTDEF byte_t __kernel_eh_frame_start[];
INTDEF byte_t __kernel_eh_frame_end[];
INTDEF byte_t __kernel_eh_frame_size[];



PRIVATE di_enum_locals_sections_t const kernel_enum_locals_sections = {
	/* .el_eh_frame_start      = */ __kernel_eh_frame_start,
	/* .el_eh_frame_end        = */ __kernel_eh_frame_end,
	/* .el_debug_info_start    = */ __kernel_debug_info_start,
	/* .el_debug_info_end      = */ __kernel_debug_info_end,
	/* .el_debug_abbrev_start  = */ __kernel_debug_abbrev_start,
	/* .el_debug_abbrev_end    = */ __kernel_debug_abbrev_end,
	/* .el_debug_loc_start     = */ __kernel_debug_loc_start,
	/* .el_debug_loc_end       = */ __kernel_debug_loc_end,
	/* .el_debug_str_start     = */ __kernel_debug_str_start,
	/* .el_debug_str_end       = */ __kernel_debug_str_end,
	/* .el_debug_aranges_start = */ __kernel_debug_aranges_start,
	/* .el_debug_aranges_end   = */ __kernel_debug_aranges_end,
	/* .el_debug_ranges_start  = */ __kernel_debug_ranges_start,
	/* .el_debug_ranges_end    = */ __kernel_debug_ranges_end
};

PRIVATE ATTR_DBGTEXT ssize_t LIBDEBUGINFO_CC
locals_format_printer(void *UNUSED(format_arg),
                      pformatprinter printer, void *arg,
                      unsigned int format_option) {
	char const *format;
	if (format_option & 1)
		format = DF_RESETATTR;
	else {
		switch (format_option) {

		case DEBUGINFO_PRINT_FORMAT_KEYWORD_PREFIX:  /* Prefix for `struct', `class', `union', `enum' */
		case DEBUGINFO_PRINT_FORMAT_MODIFIER_PREFIX: /* Prefix for `const', `volatile', `atomic', `restrict' */
		case DEBUGINFO_PRINT_FORMAT_BOOL_PREFIX:     /* Prefix for `true' / `false' */
			format = DF_SETFGCOLOR(DBG_COLOR_AQUA);
			break;

		case DEBUGINFO_PRINT_FORMAT_STRING_PREFIX:    /* Prefix for `"foobar"' */
		case DEBUGINFO_PRINT_FORMAT_CHARACTER_PREFIX: /* Prefix for `'f'' */
			format = DF_SETFGCOLOR(DBG_COLOR_YELLOW);
			break;

		case DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX: /* Prefix for type names */
			format = DF_SETFGCOLOR(DBG_COLOR_GREEN);
			break;

		case DEBUGINFO_PRINT_FORMAT_FIELD_PREFIX:   /* Prefix for `.field_name' (in struct initializers) */
		case DEBUGINFO_PRINT_FORMAT_VARNAME_PREFIX: /* Prefix for variable names */
		case DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX: /* Prefix for `1234' */
		case DEBUGINFO_PRINT_FORMAT_FLOAT_PREFIX:   /* Prefix for `1234.5678' */
			format = DF_SETFGCOLOR(DBG_COLOR_WHITE);
			break;

		case DEBUGINFO_PRINT_FORMAT_UNKNOWN_PREFIX: /* Prefix for unknown (raw) data */
			format = DF_SETCOLOR(DBG_COLOR_LIGHT_GRAY, DBG_COLOR_MAROON);
			break;

		default: return 0;
		}
	}
	return (*printer)(arg, format, strlen(format));
}


/* @return: * : UNWIND_* */
PRIVATE ATTR_DBGTEXT ATTR_NOINLINE unsigned int LIBDEBUGINFO_CC
do_print_local(void *UNUSED(arg),
               di_debuginfo_cu_parser_t const *__restrict parser,
               di_enum_locals_sections_t const *__restrict sections,
               di_debuginfo_compile_unit_t *__restrict cu,
               di_debuginfo_subprogram_t *__restrict sp,
               di_debuginfo_variable_t *__restrict var,
               di_debuginfo_type_t *__restrict type,
               uintptr_t module_relative_pc,
               size_t bufsize) {
	unsigned int error;
	void *value_buffer;
	size_t num_bits;
	if (get_stack_avail() < ((256 * sizeof(void *)) + bufsize))
		return UNWIND_BADALLOC;
	value_buffer = alloca(bufsize);
	/* Read the value of this local variable. */
	error = debuginfo_location_getvalue(&var->v_location,
	                                    di_enum_locals_sections_as_unwind_emulator_sections(sections),
	                                    &dbg_getreg,
	                                    (void *)(uintptr_t)DBG_REGLEVEL_VIEW,
	                                    cu->cu_ranges.r_startpc,
	                                    module_relative_pc,
	                                    value_buffer,
	                                    bufsize,
	                                    &num_bits,
	                                    &sp->sp_frame_base,
	                                    NULL,
	                                    parser->dup_addrsize);
	if unlikely(error == UNWIND_SUCCESS) {
		/* Print the local variable. */
		debuginfo_print_value(&dbg_printer,
		                      NULL,
		                      parser,
		                      type,
		                      var->v_name,
		                      value_buffer,
		                      (num_bits + 7) / 8,
		                      0,
		                      &locals_format_printer,
		                      NULL,
		                      var->v_name ? DEBUGINFO_PRINT_VALUE_FNORMAL
		                                  : DEBUGINFO_PRINT_VALUE_FCASTALL);
		dbg_putc('\n');
	}
	return error;
}

PRIVATE ATTR_DBGTEXT void KCALL
var_fixname(di_debuginfo_variable_t *__restrict var) {
	if (var->v_name && !*var->v_name)
		var->v_name = NULL;
	if (var->v_rawname && !*var->v_rawname)
		var->v_rawname = NULL;
	if (!var->v_name) {
		var->v_name = var->v_rawname;
		if (!var->v_name)
			var->v_name = (char *)DBGSTR("??" "?");
	}
}

PRIVATE ATTR_DBGTEXT ssize_t LIBDEBUGINFO_CC
print_local(void *arg,
            di_debuginfo_cu_parser_t const *__restrict parser,
            di_enum_locals_sections_t const *__restrict sections,
            di_debuginfo_compile_unit_t *__restrict cu,
            di_debuginfo_subprogram_t *__restrict sp,
            di_debuginfo_variable_t *__restrict var,
            di_debuginfo_type_t *__restrict type,
            uintptr_t module_relative_pc) {
	unsigned int error;
	size_t bufsize = type->t_sizeof;
	var_fixname(var);
	if (arg) {
		dbg_printf(DBGSTR(DF_WHITE("%?-s") ": "), *(size_t *)arg, var->v_name);
		var->v_name = NULL;
	}
again:
	error = do_print_local(arg,
	                       parser,
	                       sections,
	                       cu,
	                       sp,
	                       var,
	                       type,
	                       module_relative_pc,
	                       bufsize);
	if (error == UNWIND_EMULATOR_BUFFER_TOO_SMALL) {
		/* Try again with more memory. */
		bufsize += sizeof(void *);
		goto again;
	}
	if (error != UNWIND_SUCCESS) {
		dbg_putc('(');
		debuginfo_print_typename(&dbg_printer,
		                         NULL,
		                         parser,
		                         type,
		                         var->v_name,
		                         &locals_format_printer,
		                         NULL);
		dbg_putc(')');
		if (error == UNWIND_EMULATOR_NO_FUNCTION) {
			/* `UNWIND_EMULATOR_NO_FUNCTION' means that the variable is undefined
			 * for the current source location, which happens when the compiler
			 * decides to optimize the variable away before its scope ends. */
			dbg_print(DBGSTR(DF_COLOR(DBG_COLOR_LIGHT_GRAY,
			                          DBG_COLOR_MAROON,
			                          "<deleted>") "\n"));
		} else {
			dbg_printf(DBGSTR(": Unwind error #%u\n"), error);
		}
	}
	return 0;
}



DEFINE_DEBUG_FUNCTION(
		"locals",
		"locals\n"
		"List the names, types and values of locally defined C variables at the current source location\n"
		, argc, argv) {
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	/* Enumerate location variables. */
	debuginfo_enum_locals(&kernel_enum_locals_sections,
	                      dbg_getpcreg(DBG_REGLEVEL_VIEW),
	                      &print_local,
	                      NULL);
	return 0;
}


PRIVATE ATTR_DBGTEXT ssize_t LIBDEBUGINFO_CC
locals_maxlen(void *arg,
              di_debuginfo_cu_parser_t const *__restrict UNUSED(parser),
              di_enum_locals_sections_t const *__restrict UNUSED(sections),
              di_debuginfo_compile_unit_t *__restrict UNUSED(cu),
              di_debuginfo_subprogram_t *__restrict UNUSED(sp),
              di_debuginfo_variable_t *__restrict var,
              di_debuginfo_type_t *__restrict UNUSED(type),
              uintptr_t UNUSED(module_relative_pc)) {
	size_t len;
	size_t *pmaxlen = (size_t *)arg;
	var_fixname(var);
	len = strlen(var->v_name);
	if (*pmaxlen < len)
		*pmaxlen = len;
	return 0;
}

DEFINE_DEBUG_FUNCTION(
		"l",
		"l\n"
		"\tSimilar to " DF_WHITE("locals") ", however the presentation layout is somewhat "
		"different, in that instead of following C syntax, variable names are written "
		"first, and are also aligned alongside each other\n"
		, argc, argv) {
	size_t maxlen = 0;
	if (argc != 1)
		return DBG_FUNCTION_INVALID_ARGUMENTS;
	(void)argv;
	/* Enumerate location variables. */
	debuginfo_enum_locals(&kernel_enum_locals_sections,
	                      dbg_getpcreg(DBG_REGLEVEL_VIEW),
	                      &locals_maxlen,
	                      &maxlen);
	debuginfo_enum_locals(&kernel_enum_locals_sections,
	                      dbg_getpcreg(DBG_REGLEVEL_VIEW),
	                      &print_local,
	                      &maxlen);
	return 0;
}

DECL_END

#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_LOCALS_C */
