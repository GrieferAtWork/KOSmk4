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

#include <stddef.h>
#include <string.h>

/**/
#include "include/ceval.h"
#include "include/cexpr.h"
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
}

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
	/* Re-initialize the debugger heap-system */
	dbx_heap_reset();
}

DBG_FINI(fini) {
	/* Drop all external references held by `debugmodule_list' */
	while (debugmodule_list) {
		struct debugmodule *next;
		next = debugmodule_list->dm_next;
		debugmodule_fini(debugmodule_list);
		debugmodule_list = next;
	}
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

DBG_COMMAND_AUTO(eval,
                 "eval expr...\n",
                 argc, argv) {
	while (argc >= 2) {
		dbx_errno_t error;
		dbg_printf("eval: %q\n", argv[1]);
		cexpr_empty();
		error = cexpr_pusheval(argv[1]);
		if (error != DBX_EOK) {
			dbg_printf("\terror: %d\n", error);
		} else {
			/* TODO: Display result */
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
