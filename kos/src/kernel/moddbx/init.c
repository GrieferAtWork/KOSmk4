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
#ifndef GUARD_MODDBX_INIT_C
#define GUARD_MODDBX_INIT_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/debugger.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <format-printer.h>
#include <stddef.h>
#include <string.h>

/**/
#include "include/ceval.h"
#include "include/cexpr.h"
#include "include/cmodule.h"
#include "include/cprinter.h"
#include "include/ctype.h"
#include "include/malloc.h"

DECL_BEGIN

INTDEF void KCALL dbx_heap_init(void);
INTDEF void KCALL dbx_heap_reset(void);
INTDEF void KCALL dbx_heap_fini(void);

INTDEF struct cmodule *cmodule_list;
INTDEF REF struct cmodule *cmodule_cache;
INTDEF NONNULL((1)) void NOTHROW(FCALL cmodule_fini_for_reset)(struct cmodule *__restrict self);
INTDEF void NOTHROW(KCALL reset_builtin_types)(void);

PRIVATE void NOTHROW(KCALL drop_module_references)(void) {
	struct cmodule *mod;
	for (mod = cmodule_list; mod; mod = mod->cm_next)
		cmodule_fini_for_reset(mod);
}


DBG_INIT(init) {
	/* Initialize the DBX heap-system. */
	dbx_heap_init();
	/* Make sure the debug-module-list is empty. */
	cmodule_list  = NULL;
	cmodule_cache = NULL;
}


DBG_RESET(reset) {
	ceval_comma_is_select2nd = false;
	cexpr_readonly           = false;
	cexpr_typeonly           = false;
	cexpr_forcewrite         = false;

	/* Set-up `cexpr_stack' such that `cexpr_stacktop' could be used. */
	cexpr_stack     = cexpr_stack_stub + 1;
	cexpr_stacksize = 0;
	bzero(cexpr_stack_stub, sizeof(cexpr_stack_stub));
	cexpr_stack_stub[0].cv_type.ct_typ = &ctype_void;
#if CVALUE_KIND_VOID != 0
	cexpr_stack_stub[0].cv_kind = CVALUE_KIND_VOID;
#endif /* CVALUE_KIND_VOID != 0 */

	/* Drop all external references held by `cmodule_list' */
	drop_module_references();
	cmodule_list  = NULL;
	cmodule_cache = NULL;

	/* Re-initialize the debugger heap-system */
	dbx_heap_reset();

	/* Reset pointers within builtin C-types. */
	reset_builtin_types();
}

DBG_FINI(fini) {
	/* Drop references held to external libraries. */
	drop_module_references();

	/* Free all dynamically allocated heap-pages */
	dbx_heap_fini();
}


DBG_AUTOCOMPLETE(eval, argc, argv, cb, arg,
                 starts_with, starts_with_len) {
	(void)argc;
	(void)argv;
	if (starts_with_len) {
		struct cparser cp;
		bool old_cexpr_typeonly;
		size_t old_stacksize;
		/* Autocomplete sub-elements of the given C-expression. */
		cparser_init(&cp, starts_with, starts_with_len);
		cp.c_autocom       = cb;
		cp.c_autocom_arg   = arg;
		cp.c_autocom_start = starts_with;
		old_stacksize      = cexpr_stacksize;
		old_cexpr_typeonly = cexpr_typeonly;
		cexpr_typeonly     = true;
		cexpr_pushparse(&cp);
		cexpr_typeonly = old_cexpr_typeonly;
		while (cexpr_stacksize > old_stacksize) {
			if (cexpr_pop() != DBX_EOK)
				break;
		}
	}
}

PRIVATE ssize_t LIBDEBUGINFO_CC
locals_format_printer(void *UNUSED(format_arg),
                      pformatprinter printer, void *arg,
                      unsigned int format_option) {
	char const *format;
	if (DEBUGINFO_PRINT_FORMAT_ISSUFFIX(format_option)) {
		format = AC_DEFATTR;
	} else {
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
			format = AC_FG(ANSITTY_CL_LIGHT_GRAY);
			break;

		case DEBUGINFO_PRINT_FORMAT_VARNAME_PREFIX: /* Prefix for variable names */
		case DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX: /* Prefix for `1234' */
		case DEBUGINFO_PRINT_FORMAT_FLOAT_PREFIX:   /* Prefix for `1234.5678' */
			format = AC_FG(ANSITTY_CL_WHITE);
			break;

		case DEBUGINFO_PRINT_FORMAT_CONSTANT_PREFIX:
			format = AC_FG(ANSITTY_CL_PURPLE);
			break;

		case DEBUGINFO_PRINT_FORMAT_UNKNOWN_PREFIX: /* Prefix for unknown (raw) data */
			format = AC_COLOR(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_MAROON);
			break;

		case DEBUGINFO_PRINT_FORMAT_ERROR_PREFIX: /* Prefix for data-access error messages (e.g. `<segfault>') */
			format = AC_FG(ANSITTY_CL_RED);
			break;

		case DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX: /* Prefix for custom annotation notes. */
			format = AC_COLOR(ANSITTY_CL_BLACK, ANSITTY_CL_GREEN);
			break;

		case DEBUGINFO_PRINT_FORMAT_BADNOTES_PREFIX: /* Prefix for custom annotation notes. */
			format = AC_COLOR(ANSITTY_CL_BLACK, ANSITTY_CL_RED);
			break;

		default:
			return 0;
		}
	}
	return (*printer)(arg, format, strlen(format));
}



DBG_COMMAND_AUTO(eval,
                 "eval expr...\n",
                 argc, argv) {
	while (argc >= 2) {
		dbx_errno_t error;
		byte_t *data;
		cexpr_empty();
		error = cexpr_pusheval(argv[1]);
		if (error == DBX_EOK)
			error = cexpr_getdata(&data);
		if (error != DBX_EOK) {
			char const *message;
			message = dbx_strerror(error);
			dbg_savecolor();
			dbg_print(DBGSTR("\terror: "));
			dbg_setcolor(ANSITTY_CL_MAROON, ANSITTY_CL_LIGHT_GRAY);
			if (message) {
				dbg_print(message);
			} else {
				dbg_printf(DBGSTR("%d"), error);
			}
			dbg_loadcolor();
			dbg_putc('\n');
		} else {
			struct cprinter cp;
			cp.cp_printer = &dbg_printer;
			cp.cp_format  = &locals_format_printer;
			ctyperef_printname(&cexpr_stacktop.cv_type, &cp, NULL, 0);
			dbg_print(DBGSTR(":\n"));
			/* Display the value of the expression. */
			ctype_printvalue(&cexpr_stacktop.cv_type, &cp, data,
			                 CTYPE_PRINTVALUE_FLAG_NORMAL,
			                 0, 0, 2, dbg_screen_width);
			dbg_putc('\n');
			cexpr_pop();
		}
		--argc;
		++argv;
	}
	return 0;
}

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_INIT_C */
