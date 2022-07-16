/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_LOCALS_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_LOCALS_C 1
#define DISABLE_BRANCH_PROFILING

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/mman.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <sched/task.h>

#include <hybrid/overflow.h>

#include <compat/config.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <alloca.h>
#include <format-printer.h>
#include <stddef.h>
#include <string.h>

#include <libdebuginfo/debug_info.h>
#include <libunwind/cfi.h>
#include <libunwind/unwind.h>

#ifdef __ARCH_HAVE_COMPAT
#include <libunwind/arch-register.h> /* unwind_getreg_compat() */
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN


PRIVATE ATTR_DBGTEXT ssize_t LIBDEBUGINFO_CC
locals_format_printer(void *UNUSED(format_arg),
                      pformatprinter printer, void *arg,
                      unsigned int format_option) {
	char const *format;
	if (DEBUGINFO_PRINT_FORMAT_ISSUFFIX(format_option))
		format = AC_DEFATTR;
	else {
		switch (format_option) {

		case DEBUGINFO_PRINT_FORMAT_KEYWORD_PREFIX:  /* Prefix for `struct', `class', `union', `enum' */
		case DEBUGINFO_PRINT_FORMAT_MODIFIER_PREFIX: /* Prefix for `const', `volatile', `atomic', `restrict' */
		case DEBUGINFO_PRINT_FORMAT_BOOL_PREFIX:     /* Prefix for `true' / `false' */
			format = AC_FG(ANSITTY_CL_AQUA);
			break;

		case DEBUGINFO_PRINT_FORMAT_STRING_PREFIX:    /* Prefix for `"foobar"' */
		case DEBUGINFO_PRINT_FORMAT_CHARACTER_PREFIX: /* Prefix for `'f'' */
			format = AC_FG(ANSITTY_CL_YELLOW);
			break;

		case DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX: /* Prefix for type names */
			format = AC_FG(ANSITTY_CL_GREEN);
			break;

		case DEBUGINFO_PRINT_FORMAT_FIELD_PREFIX:   /* Prefix for `.field_name' (in struct initializers) */
		case DEBUGINFO_PRINT_FORMAT_VARNAME_PREFIX: /* Prefix for variable names */
		case DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX: /* Prefix for `1234' */
		case DEBUGINFO_PRINT_FORMAT_FLOAT_PREFIX:   /* Prefix for `1234.5678' */
			format = AC_FG(ANSITTY_CL_WHITE);
			break;

		case DEBUGINFO_PRINT_FORMAT_UNKNOWN_PREFIX: /* Prefix for unknown (raw) data */
			format = AC_COLOR(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_MAROON);
			break;

		default:
			return 0;
		}
	}
	return (*printer)(arg, format, strlen(format));
}

PRIVATE uintptr_t _locals_current_module_loadaddr;


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
	di_debug_sections_t const *debug_sections;
	if (get_stack_avail() < ((256 * sizeof(void *)) + bufsize))
		return UNWIND_BADALLOC;
	value_buffer   = alloca(bufsize);
	debug_sections = di_debug_sections_from_di_enum_locals_sections(sections);
	/* Read the value of this local variable. */
#ifdef __ARCH_HAVE_COMPAT
	if (dbg_current_iscompat()) {
		struct unwind_getreg_compat_data compat_data;
		unwind_getreg_compat_data_init(&compat_data, &dbg_getreg, (void *)(uintptr_t)DBG_REGLEVEL_VIEW);
		error = debuginfo_location_getvalue(&var->v_location,
		                                    di_debug_sections_as_unwind_emulator_sections(debug_sections),
		                                    &unwind_getreg_compat,
		                                    &compat_data,
		                                    di_debuginfo_compile_unit_as_simple(cu),
		                                    module_relative_pc,
		                                    _locals_current_module_loadaddr,
		                                    value_buffer,
		                                    bufsize,
		                                    &num_bits,
		                                    &sp->sp_frame_base,
		                                    NULL,
		                                    parser->dsp_addrsize,
		                                    parser->dsp_ptrsize);
	} else
#endif /* __ARCH_HAVE_COMPAT */
	{
		error = debuginfo_location_getvalue(&var->v_location,
		                                    di_debug_sections_as_unwind_emulator_sections(debug_sections),
		                                    &dbg_getreg,
		                                    (void *)(uintptr_t)DBG_REGLEVEL_VIEW,
		                                    di_debuginfo_compile_unit_as_simple(cu),
		                                    module_relative_pc,
		                                    _locals_current_module_loadaddr,
		                                    value_buffer,
		                                    bufsize,
		                                    &num_bits,
		                                    &sp->sp_frame_base,
		                                    NULL,
		                                    parser->dsp_addrsize,
		                                    parser->dsp_ptrsize);
	}
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
		dbg_printf(DBGSTR(AC_WHITE("%?-s") ": "),
		           *(size_t *)arg,
		           var->v_name);
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
			 * for the current source location,  which happens when the  compiler
			 * decides to optimize the variable away before its scope ends. */
			dbg_print(DBGSTR(AC_WITHCOLOR(ANSITTY_CL_LIGHT_GRAY,
			                              ANSITTY_CL_MAROON,
			                              "<deleted>")
			                 "\n"));
		} else {
			dbg_printf(DBGSTR(": Unwind error #%u\n"),
			           error);
		}
	}
	return 0;
}


PRIVATE ATTR_DBGTEXT ssize_t KCALL
enum_locals_at_with_debug_sections_impl(void const *absolute_pc,
                                        debuginfo_enum_locals_callback_t callback,
                                        void *arg) {
	ssize_t result;
	di_debug_sections_t sections;
	di_debug_dl_sections_t dl_sections;
	REF module_t *mod;
	uintptr_t module_relative_pc;
	if unlikely((mod = module_fromaddr_nx(absolute_pc)) == NULL)
		return 0; /* Nothing here! */
	/* Lock debug sections into memory. */
	debug_sections_lock(mod, &sections, &dl_sections);
	RAII_FINALLY {
		/* Unlock data. */
		debug_sections_unlock(&dl_sections);
		module_decref_unlikely(mod);
	};
	_locals_current_module_loadaddr = module_getloadaddr(mod);
	module_relative_pc = (uintptr_t)absolute_pc - _locals_current_module_loadaddr;
	/* Enumerate variables with debug sections. */
	result = debuginfo_enum_locals(di_debug_sections_as_di_enum_locals_sections(&sections),
	                               module_relative_pc, callback, arg);
	return result;
}

PRIVATE ATTR_DBGTEXT ssize_t KCALL
enum_locals_at_with_debug_sections(void const *absolute_pc,
                                   debuginfo_enum_locals_callback_t callback,
                                   void *arg) {
	ssize_t result;
	struct mman *required_mm = &mman_kernel;
	if (ADDR_ISUSER(absolute_pc))
		required_mm = dbg_current->t_mman;
	if (required_mm == THIS_MMAN) {
		result = enum_locals_at_with_debug_sections_impl(absolute_pc,
		                                                 callback,
		                                                 arg);
	} else {
		/* Switch to the foreign VM, so we can directly access user-space memory. */
		REF struct mman *oldmm = task_xchmman(required_mm);
		RAII_FINALLY { task_setmman_inherit(oldmm); };
		result = enum_locals_at_with_debug_sections_impl(absolute_pc,
		                                                 callback,
		                                                 arg);
	}
	return result;
}



DBG_COMMAND(locals,
            "locals\n"
            "List the names, types and values of locally defined C variables at the current source location\n") {
	/* Enumerate location variables. */
	void const *pc = dbg_getpcreg(DBG_REGLEVEL_VIEW);
	enum_locals_at_with_debug_sections(pc, &print_local, NULL);
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
	size_t len, *pmaxlen;
	pmaxlen = (size_t *)arg;
	var_fixname(var);
	len = strlen(var->v_name);
	if (*pmaxlen < len)
		*pmaxlen = len;
	return 0;
}

DBG_COMMAND(l,
            "l\n"
            "\tSimilar to " AC_WHITE("locals") ", however the presentation layout is somewhat "
            "different, in that instead of following C syntax, variable names are written "
            "first, and are also aligned alongside each other\n") {
	size_t maxlen  = 0;
	void const *pc = dbg_getpcreg(DBG_REGLEVEL_VIEW);
	/* Enumerate location variables. */
	enum_locals_at_with_debug_sections(pc, &locals_maxlen, &maxlen);
	enum_locals_at_with_debug_sections(pc, &print_local, &maxlen);
	return 0;
}

DECL_END

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_LOCALS_C */
