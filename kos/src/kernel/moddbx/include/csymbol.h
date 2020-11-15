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
#ifndef GUARD_MODDBX_INCLUDE_SYMBOL_H
#define GUARD_MODDBX_INCLUDE_SYMBOL_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/types.h>

#include <kos/exec/module.h>

#include <libdebuginfo/debug_info.h>

/**/
#include "cexpr.h"
#include "ctype.h"
#include "dw.h"
#include "error.h"

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN

#define CSYMBOL_KIND_NONE 0 /* None/unused */
#define CSYMBOL_KIND_EXPR 1 /* CFI Variable/register expression */
#define CSYMBOL_KIND_TYPE 2 /* CFI Type. */

struct csymbol {
	uintptr_t cs_kind; /* Symbol kind (one of `CSYMBOL_KIND_*') */
	union {
		struct {
			struct ctyperef       e_type; /* Expression type. */
			struct cvalue_cfiexpr e_expr; /* The actual expression. */
		}               cs_expr; /* [valid_if(CSYMBOL_KIND_EXPR)] Variable/register expression. */
		struct ctyperef cs_type; /* [valid_if(CSYMBOL_KIND_TYPE)] C-Type. */
	};
};

/* Finalize the given C-symbol. */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL csymbol_fini)(struct csymbol *__restrict self);


struct csymbol_data {
	REF struct debugmodule     *csd_module;  /* [0..1] The current module. */
	di_debuginfo_cu_parser_t    csd_parser;  /* Dwarf debug information parser. */
	di_debuginfo_compile_unit_t csd_cu;      /* Current compilation unit. */
	uintptr_t                   csd_symkind; /* Symbol kind (one of `CSYMBOL_KIND_*') */
	char const                 *csd_name;    /* [1..1] Symbol name. */
	union {
		struct {
			byte_t const           *se_type;      /* [1..1] C-Type. */
			di_debuginfo_location_t se_expr;      /* CFI expression. */
			di_debuginfo_location_t se_framebase; /* Frame-base expression. */
			void                   *se_objaddr;   /* [0..1] Object address. */
		}             csd_symexpr; /* [valid_if(CSYMBOL_KIND_EXPR)] Variable/register expression. */
		byte_t const *csd_symtype; /* [valid_if(CSYMBOL_KIND_TYPE)][1..1] C-Type. */
	};
};

/* Initialize a c-symbol from c-symbol data. */
FUNDEF WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL csymbol_from_csymbol_data)(struct csymbol *__restrict self,
                                         struct csymbol_data const *__restrict data);

/* Check if `self' belongs to `ns'
 * @param: ns: One of `CSYMBOL_LOOKUP_' */
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL csymbol_data_isns)(struct csymbol_data const *__restrict self,
                                 unsigned int ns);


/* Callback for C-symbol enumeration.
 * @return: * : Format-printer-like return value. */
typedef WUNUSED NONNULL((2)) ssize_t
/*NOTHROW*/ (FCALL *csymbol_enum_callback_t)(void *arg, struct csymbol_data const *__restrict data);

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
FUNDEF NONNULL((1)) ssize_t
NOTHROW(FCALL csymbol_enum)(csymbol_enum_callback_t cb, void *arg,
                            unsigned int scopes);
#define CSYMBOL_SCOPE_ALL   0xff /* Enumerate all scopes */
#define CSYMBOL_SCOPE_LOCAL 0x01 /* Enumerate local variables */
#define CSYMBOL_SCOPE_CU    0x02 /* Enumerate the current compilation unit */
#define CSYMBOL_SCOPE_MOD   0x04 /* Enumerate the current module */
#define CSYMBOL_SCOPE_USER  0x08 /* Enumerate user-space modules */
#define CSYMBOL_SCOPE_KERN  0x10 /* Enumerate kernel-space modules */

/* Mask for scopes that can be enumerated. */
DATDEF unsigned int csymbol_scopemask;



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
FUNDEF WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL csymbol_lookup)(char const *name, size_t namelen,
                              /*out*/ struct csymbol *__restrict result,
                              unsigned int scopes, unsigned int ns);
#define CSYMBOL_LOOKUP_ANY    0x00 /* Find all symbols */
#define CSYMBOL_LOOKUP_TYPE   0x01 /* Only find type-symbols. */
#define CSYMBOL_LOOKUP_STRUCT 0x02 /* Only find struct-types */
#define CSYMBOL_LOOKUP_UNION  0x03 /* Only find union-types */
#define CSYMBOL_LOOKUP_CLASS  0x04 /* Only find class-types */
#define CSYMBOL_LOOKUP_ENUM   0x05 /* Only find enum-types */

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_SYMBOL_H */
