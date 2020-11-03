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
#ifndef GUARD_MODDBX_CPRINTER_C
#define GUARD_MODDBX_CPRINTER_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/except.h>
#include <kernel/types.h>

#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

/**/
#include "include/cprinter.h"
#include "include/ctype.h"
#include "include/malloc.h"

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN


#define DO(expr)                 \
	do {                         \
		if ((temp = (expr)) < 0) \
			goto err;            \
		result += temp;          \
	}	__WHILE0
#define P_PRINTER printer->cp_printer
#define P_ARG     printer->cp_arg

#define RAWPRINT(str) (*P_PRINTER)(P_ARG, str, COMPILER_STRLEN(str))
#define PRINT(str)    DO(RAWPRINT(str))
#define PRINTF(...)   DO(format_printf(P_PRINTER, P_ARG, __VA_ARGS__))
#define FORMAT(code)                                                  \
	do {                                                              \
		if (printer->cp_format) {                                     \
			if ((temp = (*printer->cp_format)(printer->cp_format_arg, \
			                                  printer->cp_printer,    \
			                                  printer->cp_arg,        \
			                                  code)) < 0)             \
				goto err;                                             \
			result += temp;                                           \
		}                                                             \
	}	__WHILE0

struct c_typeflag {
	char     tf_name[12]; /* Name */
	uint32_t tf_flag;     /* Flag value */
};

PRIVATE struct c_typeflag const c_typeflags[] = {
	{ "const",    CTYPEREF_FLAG_CONST },
	{ "volatile", CTYPEREF_FLAG_VOLATILE },
	{ "_Atomic",  CTYPEREF_FLAG_ATOMIC },
	{ "restrict", CTYPEREF_FLAG_RESTRICT },
#ifdef CTYPEREF_FLAG_SEG_FS
	{ "__seg_fs", CTYPEREF_FLAG_SEG_FS },
#endif /* CTYPEREF_FLAG_SEG_FS */
#ifdef CTYPEREF_FLAG_SEG_GS
	{ "__seg_gs", CTYPEREF_FLAG_SEG_GS },
#endif /* CTYPEREF_FLAG_SEG_GS */
};


PRIVATE NONNULL((1)) ssize_t KCALL
print_typeflags(struct cprinter const *__restrict printer,
                uintptr_t typeflags, bool include_leading_space) {
	ssize_t temp, result = 0;
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(c_typeflags); ++i) {
		if (typeflags & c_typeflags[i].tf_flag) {
			if (include_leading_space)
				PRINT(" ");
			FORMAT(DEBUGINFO_PRINT_FORMAT_MODIFIER_PREFIX);
			DO((*P_PRINTER)(P_ARG, c_typeflags[i].tf_name,
			                strlen(c_typeflags[i].tf_name)));
			FORMAT(DEBUGINFO_PRINT_FORMAT_MODIFIER_SUFFIX);
			include_leading_space = true;
		}
	}
	return result;
err:
	return temp;
}

struct builtin_type_name {
	char          btn_name[24]; /* Name */
	struct ctype *btn_type;     /* [1..1] Type. */
};

PRIVATE struct builtin_type_name const builtin_type_names[] = {
//	{ "bool", &ctype_bool }, /* Special handling... */
	{ "float", &ctype_ieee754_float },
	{ "double", &ctype_ieee754_double },
	{ "long double", &ctype_ieee854_long_double },
//	{ "void", &ctype_void }, /* Special handling... */
	{ "char", &ctype_char },
	{ "signed char", &ctype_signed_char },
	{ "unsigned char", &ctype_unsigned_char },
	{ "short", &ctype_short },
	{ "unsigned short", &ctype_unsigned_short },
	{ "int", &ctype_int },
	{ "unsigned int", &ctype_unsigned_int },
	{ "long", &ctype_long },
	{ "unsigned long", &ctype_unsigned_long },
	{ "long long", &ctype_long_long },
	{ "unsigned long long", &ctype_unsigned_long_long },
	{ "char16_t", &ctype_char16_t },
	{ "char32_t", &ctype_char32_t },
};


PRIVATE NONNULL((1, 2)) ssize_t KCALL
ctype_printprefix(struct ctyperef const *__restrict self,
                  struct cprinter const *__restrict printer) {
	/* Check for simple case: the type has a name. */
	ssize_t temp, result = 0;
	char const *prefix;
	char const *type_name;
	struct ctype *typ;
again:
	typ       = self->ct_typ;
	type_name = self->ct_info.ci_name;
	if (!type_name) {
		/* Check for known, named types */
		switch (CTYPE_KIND_CLASSOF(typ->ct_kind)) {

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_VOID):
			type_name = "void";
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL):
			if (typ == &ctype_bool)
				type_name = "bool";
			else {
				/* Fallback: Variable-length-boolean type. */
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
				PRINTF("BOOL%" PRIuSIZ, (size_t)(CTYPE_KIND_SIZEOF(typ->ct_kind) * 8));
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
				goto after_name_prefix_printed;
			}
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
			if (CTYPE_KIND_ISENUM(typ->ct_kind))
				type_name = ""; /* Unnamed enum. */
			else {
				/* Select names of known types. */
				unsigned int i;
				for (i = 0; i < COMPILER_LENOF(builtin_type_names); ++i) {
					if (typ == builtin_type_names[i].btn_type) {
						type_name = builtin_type_names[i].btn_name;
						goto got_type_name;
					}
				}
				/* Fallback: Variable-length-integer type. */
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
				PRINTF("%sINT%" PRIuSIZ,
				       CTYPE_KIND_INT_ISUNSIGNED(typ->ct_kind) ? "U" : "",
				       (size_t)(CTYPE_KIND_SIZEOF(typ->ct_kind) * 8));
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
				goto after_name_prefix_printed;
			}
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_STRUCT):
			type_name = ""; /* Unnamed struct/union. */
			break;

			/* Special case. For these, the type prefix is the base-type. */
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ARRAY): {
			struct ctyperef inner_type;
			inner_type.ct_typ   = typ->ct_array.ca_elem;
			inner_type.ct_info  = typ->ct_array.ca_eleminfo;
			inner_type.ct_flags = self->ct_flags;
			return ctype_printprefix(&inner_type, printer);
		}	break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR):
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_FUNCTION): {
			STATIC_ASSERT(offsetof(struct ctype, ct_pointer.cp_base) ==
			              offsetof(struct ctype, ct_function.cf_base));
			self = &typ->ct_pointer.cp_base;
			goto again;
		}	break;

		default:
			type_name = "?"; /* Unknown type... */
			break;
		}
	}
got_type_name:
	switch (CTYPE_KIND_CLASSOF(typ->ct_kind)) {

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
		if (!CTYPE_KIND_ISENUM(typ->ct_kind))
			goto print_name_without_prefix;
		prefix = "enum";
		break;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_STRUCT):
		prefix = "struct";
		if (CTYPE_KIND_STRUCT_ISUNION(typ->ct_kind))
			prefix = "union";
		break;

	default:
print_name_without_prefix:
		FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
		DO((*P_PRINTER)(P_ARG, type_name, strlen(type_name)));
		FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
		goto after_name_prefix_printed;
	}
	FORMAT(DEBUGINFO_PRINT_FORMAT_KEYWORD_PREFIX);
	DO((*P_PRINTER)(P_ARG, prefix, strlen(prefix)));
	FORMAT(DEBUGINFO_PRINT_FORMAT_KEYWORD_SUFFIX);
	if (*type_name) {
		PRINT(" ");
		FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
		DO((*P_PRINTER)(P_ARG, type_name, strlen(type_name)));
		FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
	}
after_name_prefix_printed:
	DO(print_typeflags(printer, self->ct_flags, true));
	return result;
err:
	return temp;
}

PRIVATE ATTR_RETNONNULL char const *KCALL
cc_attribute(uintptr_t cc) {
	char const *result = "";
	if (cc != CTYPE_KIND_FUNPROTO_CC_DEFAULT) {
		switch (cc) {

#ifdef CTYPE_KIND_FUNPROTO_CC_CDECL
		case CTYPE_KIND_FUNPROTO_CC_CDECL:
			result = "__cdecl";
			break;
#endif /* CTYPE_KIND_FUNPROTO_CC_CDECL */

#ifdef CTYPE_KIND_FUNPROTO_CC_FASTCALL
		case CTYPE_KIND_FUNPROTO_CC_FASTCALL:
			result = "__fastcall";
			break;
#endif /* CTYPE_KIND_FUNPROTO_CC_FASTCALL */

#ifdef CTYPE_KIND_FUNPROTO_CC_STDCALL
		case CTYPE_KIND_FUNPROTO_CC_STDCALL:
			result = "__stdcall";
			break;
#endif /* CTYPE_KIND_FUNPROTO_CC_STDCALL */

#ifdef CTYPE_KIND_FUNPROTO_CC_SYSVABI
		case CTYPE_KIND_FUNPROTO_CC_SYSVABI:
			result = "__sysv_abi";
			break;
#endif /* CTYPE_KIND_FUNPROTO_CC_SYSVABI */

#ifdef CTYPE_KIND_FUNPROTO_CC_MSABI
		case CTYPE_KIND_FUNPROTO_CC_MSABI:
			result = "__ms_abi";
			break;
#endif /* CTYPE_KIND_FUNPROTO_CC_MSABI */

		default:
			break;
		}
	}
	return result;
}


PRIVATE NONNULL((1, 2)) ssize_t KCALL
ctype_printsuffix_head(struct ctyperef *__restrict self,
                       struct cprinter const *__restrict printer,
                       char const *varname, size_t varname_len) {
	ssize_t temp, result = 0;
	struct ctype *typ;
again:
	typ = self->ct_typ;
	switch (CTYPE_KIND_CLASSOF(typ->ct_kind)) {

#define NEED_SPACE_BEFORE_POINTER(inner)               \
	(!CTYPE_KIND_ISPOINTER((inner).ct_typ->ct_kind) || \
	 (inner).ct_typ->ct_pointer.cp_base.ct_flags != 0)

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR): {
		struct ctyperef inner;
		memcpy(&inner, &typ->ct_pointer.cp_base, sizeof(struct ctyperef));
		/* Pointer to array or function requires additional parenthesis:
		 * >> int (*foo)[42];
		 * >> int (*bar)(int x, int y);
		 * >> int **baz;   // No paren needed here! */
		if (CTYPE_KIND_ISARRAY(inner.ct_typ->ct_kind)) {
			DO(ctype_printsuffix_head(&inner, printer, NULL, 0));
			if (NEED_SPACE_BEFORE_POINTER(inner))
				PRINT(" ");
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			PRINT("(");
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		} else if (CTYPE_KIND_ISFUNCTION(inner.ct_typ->ct_kind)) {
			uintptr_t old_kind, default_cc;
			char const *cc_attrib_name;
			old_kind   = inner.ct_typ->ct_kind;
			default_cc = CTYPE_KIND_FUNPROTO_CC_DEFAULT;
			inner.ct_typ->ct_kind = (old_kind & ~(CTYPE_KIND_FUNPROTO_CCMASK)) | default_cc;
			temp = ctype_printsuffix_head(&inner, printer, NULL, 0);
			typ->ct_pointer.cp_base.ct_typ->ct_kind = old_kind;
			if unlikely(temp < 0)
				goto err;
			result += temp;
			old_kind &= CTYPE_KIND_FUNPROTO_CCMASK;
			cc_attrib_name = cc_attribute(old_kind);
			/* Include the calling convention here. */
			if (NEED_SPACE_BEFORE_POINTER(inner))
				PRINT(" ");
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			PRINT("(");
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
			if (*cc_attrib_name) {
				FORMAT(DEBUGINFO_PRINT_FORMAT_ATTRIBUTE_PREFIX);
				DO((*P_PRINTER)(P_ARG, cc_attrib_name,
				                strlen(cc_attrib_name)));
				FORMAT(DEBUGINFO_PRINT_FORMAT_ATTRIBUTE_SUFFIX);
				PRINT(" ");
			}
		} else {
			DO(ctype_printsuffix_head(&inner, printer, NULL, 0));
			DO(print_typeflags(printer, self->ct_flags, false));
			if (NEED_SPACE_BEFORE_POINTER(inner))
				PRINT(" ");
		}
		FORMAT(DEBUGINFO_PRINT_FORMAT_POINTER_PREFIX);
		PRINT("*");
		FORMAT(DEBUGINFO_PRINT_FORMAT_POINTER_SUFFIX);
		if (varname_len)
			goto do_print_varname_without_space;
	}	break;
#undef NEED_SPACE_BEFORE_POINTER

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ARRAY):
		self->ct_typ  = typ->ct_array.ca_elem;
		self->ct_info = typ->ct_array.ca_eleminfo;
		goto again;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_FUNCTION):
		memcpy(self, &typ->ct_function.cf_base,
		       sizeof(struct ctyperef));
		goto again;

	default:
		break;
	}
	/* Print the variable name. */
	if (varname_len) {
		PRINT(" ");
do_print_varname_without_space:
		FORMAT(DEBUGINFO_PRINT_FORMAT_VARNAME_PREFIX);
		DO((*P_PRINTER)(P_ARG, varname, varname_len));
		FORMAT(DEBUGINFO_PRINT_FORMAT_VARNAME_SUFFIX);
	}
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1, 2)) ssize_t KCALL
ctype_printsuffix_tail(struct ctype const *__restrict self,
                       struct cprinter const *__restrict printer) {
	ssize_t temp, result = 0;
again:
	switch (CTYPE_KIND_CLASSOF(self->ct_kind)) {

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR): {
		struct ctype *inner;
		inner = self->ct_pointer.cp_base.ct_typ;
		/* Pointer to array or function requires additional parenthesis:
		 * >> int (*foo)[42];
		 * >> int (*bar)(int x, int y);
		 * >> int **baz;   // No paren needed here! */
		if (CTYPE_KIND_ISARRAY(inner->ct_kind) ||
		    CTYPE_KIND_ISFUNCTION(inner->ct_kind)) {
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			PRINT(")");
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		}
		self = inner;
		goto again;
	}	break;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ARRAY):
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_PREFIX);
		PRINT("[");
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_SUFFIX);
		FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
		PRINTF("%" PRIuSIZ, self->ct_array.ca_count);
		FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_PREFIX);
		PRINT("]");
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_SUFFIX);
		self = self->ct_array.ca_elem;
		goto again;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_FUNCTION):
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
		PRINT("(");
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		if (self->ct_function.cf_argc == 0) {
			FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
			PRINT("void");
			FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
		} else {
			size_t i;
			for (i = 0; i < self->ct_function.cf_argc; ++i) {
				if (i != 0) {
					FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
					PRINT(",");
					FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
					PRINT(" ");
				}
				DO(ctyperef_printname(&self->ct_function.cf_argv[i],
				                      printer, NULL, 0));
			}
		}
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
		PRINT(")");
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		self = self->ct_function.cf_base.ct_typ;
		goto again;

	default:
		break;
	}
	return result;
err:
	return temp;
}


/* Print the correct representation of the given type, including
 * an optional, contained variable name that is also printed at
 * the proper location. */
PUBLIC NONNULL((1, 2)) ssize_t KCALL
ctyperef_printname(struct ctyperef const *__restrict self,
                   struct cprinter const *__restrict printer,
                   char const *varname, size_t varname_len) {
	ssize_t temp, result;
	struct ctyperef me;
	/* Print the type prefix. */
	result = ctype_printprefix(self, printer);
	if unlikely(result < 0)
		goto done;
	/* Print the type suffix head+tail. */
	memcpy(&me, self, sizeof(me));
	DO(ctype_printsuffix_head(&me, printer, varname, varname_len));
	DO(ctype_printsuffix_tail(self->ct_typ, printer));
done:
	return result;
err:
	return temp;
}

PUBLIC NONNULL((1, 2)) ssize_t KCALL
ctype_printname(struct ctype const *__restrict self,
                struct cprinter const *__restrict printer,
                char const *varname, size_t varname_len) {
	struct ctyperef ct;
	memset(&ct, 0, sizeof(ct));
	ct.ct_typ = (struct ctype *)self;
	return ctyperef_printname(&ct, printer, varname, varname_len);
}



#if 0
/* Print a human-readable representation of the contents of a given data-buffer,
 * based on the C-typing of that buffer, which was likely extracted from debug info.
 * @param: self:           The typing of `buf'
 * @param: printer:        The printer used to output data.
 * @param: buf:            The data buffer that should be printed.
 *                         This should point to a block of `ctype_sizeof(self)' types.
 * @param: flags:          Printing flags (set of `CTYPE_PRINTVALUE_FLAG_*')
 * @param: newline_indent: # of SPC (' ') characters to print after every \n-character.
 *                         Ignored when `CTYPE_PRINTVALUE_FLAG_ONELINE' is given.
 * @param: newline_tab:    Amount by which to increase `newline_indent' after a line-
 *                         feed following an open-brace '{' or open-bracket '['.
 * @param: maxlinelen:     The max line length that should not be exceeded by when
 *                         placing short struct initializers on the same line.
 *                         Ignored when `CTYPE_PRINTVALUE_FLAG_NOSHORTLINES' is given.
 *                         If sufficient space is available, do this:
 *                         >> {foo: {x: 10, y: 20}}
 *                         or this:
 *                         >> {
 *                         >>     foo: {x: 10, y: 20}
 *                         >> }
 *                         Instead of this:
 *                         >> {
 *                         >>     foo: {
 *                         >>         x: 10,
 *                         >>         y: 20
 *                         >>     }
 *                         >> }
 *                         Note that this limit isn't a guaranty, but only a hint to
 *                         where */
PUBLIC NONNULL((1, 2, 3)) ssize_t KCALL
ctype_printvalue(struct ctype const *__restrict self,
                 struct cprinter const *__restrict printer,
                 void const *__restrict buf, unsigned int flags,
                 size_t firstline_indent, size_t newline_indent,
                 size_t newline_tab, size_t maxlinelen) {
	ssize_t temp, result;
	switch (CTYPE_KIND_CLASSOF(self->ct_kind)) {

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_VOID):
		result = RAWPRINT("(void)0");
		break;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL): {
		bool is_nonzero;
		TRY {
			is_nonzero = false;
		} EXCEPT {
		}

	}	break;

#define CTYPE_KIND_BOOL8                  0x1001
#define CTYPE_KIND_BOOL16                 0x1002
#define CTYPE_KIND_BOOL32                 0x1004
#define CTYPE_KIND_BOOL64                 0x1008
#define CTYPE_KIND_Sn(sizeof)            (0x2000 | (sizeof))
#define CTYPE_KIND_S8                     0x2001
#define CTYPE_KIND_S16                    0x2002
#define CTYPE_KIND_S32                    0x2004
#define CTYPE_KIND_S64                    0x2008
#define CTYPE_KIND_Un(sizeof)            (0x2100 | (sizeof))
#define CTYPE_KIND_U8                     0x2101
#define CTYPE_KIND_U16                    0x2102
#define CTYPE_KIND_U32                    0x2104
#define CTYPE_KIND_U64                    0x2108
#define CTYPE_KIND_ENUM8                  0x2201
#define CTYPE_KIND_ENUM16                 0x2202
#define CTYPE_KIND_ENUM32                 0x2204
#define CTYPE_KIND_ENUM64                 0x2208
#define CTYPE_KIND_IEEE754_FLOAT          0x3004
#define CTYPE_KIND_IEEE754_DOUBLE         0x3008
#define CTYPE_KIND_IEEE854_LONG_DOUBLE_12 0x300c
#define CTYPE_KIND_IEEE854_LONG_DOUBLE_16 0x3010
#define CTYPE_KIND_STRUCT                 0x4000
#define CTYPE_KIND_UNION                  0x4100
#define CTYPE_KIND_PTR32                  0x8004
#define CTYPE_KIND_PTR64                  0x8008
#define CTYPE_KIND_ARRAY                  0x9000
#define CTYPE_KIND_FUNCTION               0xa000
#define    CTYPE_KIND_FUNPROTO_CCMASK     0x0700 /* == CTYPE_KIND_FLAGMASK */
#define    CTYPE_KIND_FUNPROTO_VARARGS    0x0800 /* FLAG: var-args function */
#if defined(__x86_64__) || defined(__i386__)
#define    CTYPE_KIND_FUNPROTO_CC_CDECL    0x0000
#define    CTYPE_KIND_FUNPROTO_CC_FASTCALL 0x0100
#define    CTYPE_KIND_FUNPROTO_CC_STDCALL  0x0200
#ifdef __x86_64__
#define    CTYPE_KIND_FUNPROTO_CC_SYSVABI  0x0400
#define    CTYPE_KIND_FUNPROTO_CC_MSABI    0x0500
#define    CTYPE_KIND_FUNPROTO_CC_DEFAULT                                                \
	(__KOS64_IS_CS32BIT(x86_dbg_getregbyidp(DBG_REGLEVEL_VIEW, X86_REGISTER_SEGMENT_CS)) \
	 ? CTYPE_KIND_FUNPROTO_CC_CDECL                                                      \
	 : CTYPE_KIND_FUNPROTO_CC_SYSVABI)
#else /* __x86_64__ */
#define    CTYPE_KIND_FUNPROTO_CC_DEFAULT  CTYPE_KIND_FUNPROTO_CC_CDECL
#endif /* !__x86_64__ */
#else /* __x86_64__ || __i386__ */
#define    CTYPE_KIND_FUNPROTO_CC_DEFAULT 0x0000
#endif /* !__x86_64__ && !__i386__ */

	default:
		break;
	}
	return result;
err:
	return temp;
}
#endif




DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_CPRINTER_C */
