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
#ifndef GUARD_MODDBX_INIT_C
#define GUARD_MODDBX_INIT_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/debugger.h>

#include <format-printer.h>
#include <stddef.h>
#include <string.h>

/**/
#include "include/ceval.h"
#include "include/cexpr.h"
#include "include/cprinter.h"
#include "include/csymbol.h"
#include "include/ctype.h"
#include "include/malloc.h"

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN

INTDEF void KCALL dbx_heap_init(void);
INTDEF void KCALL dbx_heap_reset(void);
INTDEF void KCALL dbx_heap_fini(void);

DBG_INIT(init) {
	/* Initialize the DBX heap-system. */
	dbx_heap_init();
	/* Make sure that debug-module-list is empty. */
	debugmodule_list = NULL;
}

INTDEF void NOTHROW(KCALL reset_builtin_types)(void);

DBG_RESET(reset) {
	csymbol_scopemask           = CSYMBOL_SCOPE_ALL;
	ceval_comma_is_select2nd    = false;
	cexpr_readonly              = false;
	cexpr_typeonly              = false;
	/* Set-up `cexpr_stack' that `cexpr_stacktop' could be used. */
	cexpr_stack     = cexpr_stack_stub + 1;
	cexpr_stacksize = 0;
	memset(cexpr_stack_stub, 0, sizeof(cexpr_stack_stub));
	cexpr_stack_stub[0].cv_type.ct_typ = &ctype_void;
#if CVALUE_KIND_VOID != 0
	cexpr_stack_stub[0].cv_kind = CVALUE_KIND_VOID;
#endif /* CVALUE_KIND_VOID != 0 */
	/* Drop all external references held by `debugmodule_list' */
	while (debugmodule_list) {
		struct debugmodule *next;
		next = debugmodule_list->dm_next;
		debugmodule_fini(debugmodule_list);
		debugmodule_list = next;
	}
	/* Re-initialize the debugger heap-system */
	dbx_heap_reset();
	/* Reset pointers within builtin C-types. */
	reset_builtin_types();
}

DBG_FINI(fini) {
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
		unsigned int old_csymbol_scopemask;
		size_t old_stacksize;
		/* Autocomplete sub-elements of the given C-expression. */
		cparser_init(&cp, starts_with, starts_with_len);
		cp.c_autocom          = cb;
		cp.c_autocom_arg      = arg;
		cp.c_autocom_start    = starts_with;
		old_stacksize         = cexpr_stacksize;
		old_cexpr_typeonly    = cexpr_typeonly;
		old_csymbol_scopemask = csymbol_scopemask;
		cexpr_typeonly        = true;
		csymbol_scopemask     = CSYMBOL_SCOPE_LOCAL;
		cexpr_pushparse(&cp);
		cexpr_typeonly    = old_cexpr_typeonly;
		csymbol_scopemask = old_csymbol_scopemask;
		while (cexpr_stacksize > old_stacksize) {
			if (cexpr_pop() != DBX_EOK)
				break;
		}
	}
}

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



DBG_COMMAND_AUTO(eval,
                 "eval expr...\n",
                 argc, argv) {
	while (argc >= 2) {
		dbx_errno_t error;
		cexpr_empty();
		error = cexpr_pusheval(argv[1]);
		if (error != DBX_EOK) {
			dbg_printf("\terror: %d\n", error);
		} else {
			struct cprinter cp;
			cp.cp_printer = &dbg_printer;
			cp.cp_format  = &locals_format_printer;
			ctyperef_printname(&cexpr_stacktop.cv_type, &cp, "var", 3);
			/* TODO: Display result value properly. */
			dbg_printf("\n%$[hex]",
			           cexpr_getsize(),
			           cexpr_getdata());
			dbg_putc('\n');
			cexpr_pop();
		}
		--argc;
		++argv;
	}
	return 0;
}

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INIT_C */
