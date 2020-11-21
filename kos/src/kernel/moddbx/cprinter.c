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
#ifdef CONFIG_HAVE_DEBUGGER

#include <kernel/except.h>
#include <kernel/types.h>

#include <hybrid/align.h>

#include <sys/mmio.h>
#include <sys/param.h>

#include <ctype.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unicode.h>

/**/
#include "include/cprinter.h"
#include "include/ctype.h"
#include "include/malloc.h"

DECL_BEGIN


#define DO(expr)                 \
	do {                         \
		if ((temp = (expr)) < 0) \
			goto err;            \
		result += temp;          \
	}	__WHILE0
#define P_PRINTER printer->cp_printer
#define P_ARG     printer->cp_arg

#define RAWPRINT(str)     (*P_PRINTER)(P_ARG, str, COMPILER_STRLEN(str))
#define PRINT(str)        DO(RAWPRINT(str))
#define REPEAT(ch, count) DO(format_repeat(P_PRINTER, P_ARG, ch, count))
#define PRINTF(...)       DO(format_printf(P_PRINTER, P_ARG, __VA_ARGS__))
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


struct indent_printer_data {
	size_t indent;
	bool *pcontains_newline;
	bool stop_after_newline;
};

PRIVATE ssize_t FORMATPRINTER_CC
indent_printer(void *arg, char const *__restrict data, size_t datalen) {
	struct indent_printer_data *cookie;
	char const *last_linefeed;
	cookie = (struct indent_printer_data *)arg;
	last_linefeed = (char *)memrchr(data, '\n', datalen);
	if (last_linefeed) {
		++last_linefeed;
		cookie->indent = (size_t)((data + datalen) - last_linefeed);
		if (cookie->pcontains_newline)
			*cookie->pcontains_newline = true;
		if (cookie->stop_after_newline)
			return -1; /* Stop printing! */
	} else {
		cookie->indent += datalen;
	}
	return datalen;
}

PRIVATE NONNULL((1)) size_t KCALL
ctype_printvalue_nextindent(struct ctyperef const *__restrict self,
                            void const *__restrict buf, unsigned int flags,
                            size_t firstline_indent, size_t newline_indent,
                            size_t newline_tab, size_t maxlinelen,
                            bool *pcontains_newline,
                            bool stop_after_newline) {
	struct cprinter p;
	struct indent_printer_data data;
	data.indent             = firstline_indent;
	data.pcontains_newline  = pcontains_newline;
	data.stop_after_newline = stop_after_newline;
	p.cp_printer            = &indent_printer;
	p.cp_arg                = &data;
	p.cp_format             = NULL;
	ctype_printvalue(self, &p, buf, flags,
	                 firstline_indent, newline_indent,
	                 newline_tab, maxlinelen);
	return data.indent;
}


/* Count the # of times that `ch' appears in `str' */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL count_characters)(char const *str, size_t len, char ch) {
	size_t i, result = 0;
	for (i = 0; i < len; ++i) {
		if (str[i] == ch)
			++result;
	}
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL use_decimal_representation)(char const *decimal_repr, size_t len) {
	/* Check if more than 3/5th of `decimal_repr' use the same digit.
	 * If so, then the decimal representation should be used. */
	size_t threshold = (len * 5) / 3;
	char ch;
	for (ch = '0'; ch <= '9'; ++ch) {
		if (count_characters(decimal_repr, len, ch) >= threshold)
			return true;
	}
	return false;
}

PRIVATE ATTR_CONST WUNUSED char
NOTHROW(FCALL tohex)(byte_t nibble) {
	if (nibble <= 9)
		return '0' + nibble;
	return 'a' + (nibble - 10);
}


PRIVATE struct cprinter const lenprinter = {
	/* .cp_printer    = */ &format_length,
	/* .cp_arg        = */ NULL,
	/* .cp_format     = */ NULL,
	/* .cp_format_arg = */ NULL,
};



#define CSTRING_KIND_NORMAL  0
#define CSTRING_KIND_CHAR16  1
#define CSTRING_KIND_CHAR32  2
#define CSTRING_KIND_INVALID ((unsigned int)-1)
PRIVATE NONNULL((1)) ssize_t KCALL
ctype_printcstring(struct cprinter const *__restrict printer,
                   void const *buf, size_t len, unsigned int kind) {
	ssize_t temp, result = 0;
	char prefix[2], *ptr;
	byte_t const *reader, *end;
	FORMAT(DEBUGINFO_PRINT_FORMAT_STRING_PREFIX);
	ptr = prefix;
	switch (kind) {
	default: /*            */ break;
	case CSTRING_KIND_CHAR16: *ptr++ = 'u'; break;
	case CSTRING_KIND_CHAR32: *ptr++ = 'U'; break;
	}
	*ptr++ = '\"';
	DO((*P_PRINTER)(P_ARG, prefix, (size_t)(ptr - prefix)));
	reader = (byte_t const *)buf;
	end    = (byte_t const *)buf + len;
	while (reader < end) {
		char32_t ch;
		char buf[UNICODE_UTF8_MAXLEN], *ptr;
		switch (kind) {
		default: /*            */ ch = unicode_readutf8_n((char **)&reader, (char *)end); break;
		case CSTRING_KIND_CHAR16: ch = unicode_readutf16_n((char16_t **)&reader, (char16_t *)end); break;
		case CSTRING_KIND_CHAR32: ch = unicode_readutf32_n((char32_t **)&reader, (char32_t *)end); break;
		}
		ptr = unicode_writeutf8(buf, ch);
		DO(format_escape(P_PRINTER, P_ARG,
		                 buf, (size_t)(ptr - buf),
		                 FORMAT_ESCAPE_FPRINTRAW));
	}
	PRINT("\"");
	FORMAT(DEBUGINFO_PRINT_FORMAT_STRING_SUFFIX);
	return result;
err:
	return temp;
}

/* Print a human-readable representation of the contents of a given data-buffer,
 * based on the C-typing of that buffer, which was likely extracted from debug info.
 * @param: self:             The typing of `buf'
 * @param: printer:          The printer used to output data.
 * @param: buf:              The data buffer that should be printed.
 *                           This should point to a block of `ctype_sizeof(self)' types.
 * @param: flags:            Printing flags (set of `CTYPE_PRINTVALUE_FLAG_*')
 * @param: firstline_indent: # of SPC (' ') characters already printed on the current line.
 * @param: newline_indent:   # of SPC (' ') characters to print after every \n-character.
 *                           Ignored when `CTYPE_PRINTVALUE_FLAG_ONELINE' is given.
 * @param: newline_tab:      Amount by which to increase `newline_indent' after a line-
 *                           feed following an open-brace '{' or open-bracket '['.
 * @param: maxlinelen:       The max line length that should not be exceeded by when
 *                           placing short struct initializers on the same line.
 *                           Ignored when `CTYPE_PRINTVALUE_FLAG_NOSHORTLINES' is given.
 *                           If sufficient space is available, do this:
 *                           >> {foo: {x: 10, y: 20}}
 *                           or this:
 *                           >> {
 *                           >>     foo: {x: 10, y: 20}
 *                           >> }
 *                           Instead of this:
 *                           >> {
 *                           >>     foo: {
 *                           >>         x: 10,
 *                           >>         y: 20
 *                           >>     }
 *                           >> }
 *                           Note that this limit isn't a guaranty, but only a hint.*/
PUBLIC NONNULL((1, 2)) ssize_t KCALL
ctype_printvalue(struct ctyperef const *__restrict self,
                 struct cprinter const *__restrict printer,
                 void const *buf, unsigned int flags,
                 size_t firstline_indent, size_t newline_indent,
                 size_t newline_tab, size_t maxlinelen) {
	ssize_t temp, result = 0;
	struct ctype const *me = self->ct_typ;
	uintptr_half_t kind = me->ct_kind;
	TRY {
		switch (CTYPE_KIND_CLASSOF(kind)) {
	
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_VOID):
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			PRINT("(");
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
			FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
			PRINT("void");
			FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			PRINT(")");
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
			PRINT("0");
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
			break;
	
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL): {
			bool is_nonzero = false;
			size_t i;
			for (i = 0; i < CTYPE_KIND_SIZEOF(kind); ++i) {
				if (((byte_t *)buf)[i] != 0)
					is_nonzero = true;
			}
			result = is_nonzero ? RAWPRINT("true")
			                    : RAWPRINT("false");
		}	break;
	
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR):
			if ((CTYPE_KIND_SIZEOF(kind) <= sizeof(void *)) &&
			    ((flags & (CTYPE_PRINTVALUE_FLAG_NOSTRINGPOINTER | CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER)) !=
			    /*     */ (CTYPE_PRINTVALUE_FLAG_NOSTRINGPOINTER | CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER))) {
				void *ptr;
				memset(&ptr, 0, sizeof(ptr));
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
				memcpy(&ptr, buf, CTYPE_KIND_SIZEOF(kind));
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
				memcpy((byte_t *)&ptr + sizeof(ptr) - CTYPE_KIND_SIZEOF(kind),
				       buf, CTYPE_KIND_SIZEOF(kind));
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
				/* Check for special pointers. */
				if (!(flags & CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER) && ptr == (void *)0) {
					FORMAT(DEBUGINFO_PRINT_FORMAT_CONSTANT_PREFIX);
					PRINT("NULL");
					FORMAT(DEBUGINFO_PRINT_FORMAT_CONSTANT_SUFFIX);
					break;
				}
				/* Check if we may print this as a string. */
				if (!(flags & CTYPE_PRINTVALUE_FLAG_NOSTRINGPOINTER)) {
					size_t buflen     = 0;
					unsigned int kind = CSTRING_KIND_INVALID;
					TRY {
						if (me->ct_pointer.cp_base.ct_typ == &ctype_char) {
							buflen = strlen((char const *)ptr);
							kind   = CSTRING_KIND_NORMAL;
						} else if (me->ct_pointer.cp_base.ct_typ == &ctype_char16_t) {
							buflen = rawmemlenw(ptr, 0) * 2;
							kind   = CSTRING_KIND_CHAR16;
						} else if (me->ct_pointer.cp_base.ct_typ == &ctype_char32_t) {
							buflen = rawmemlenl(ptr, 0) * 4;
							kind   = CSTRING_KIND_CHAR32;
						}
					} EXCEPT {
					}
					if (kind != CSTRING_KIND_INVALID) {
						DO(ctype_printcstring(printer, ptr, buflen, kind));
						break;
					}
				}
				if (!(flags & CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER)) {
					/* Check if `ptr' is a text-/data-pointer. */
					{
						REF module_t *mod;
						module_type_var(modtyp);
						mod = module_ataddr(ptr, modtyp);
						if (mod) {
							/* TODO: Try to lookup the name/base-address of a symbol
							 *       that contains the given `ptr' and is part of `mod' */
							module_decref(mod, modtyp);
						}
					}
					/* TODO: Check if `ptr' is apart of a file mapping. If it is,
					 *       print the absolute path the mapped file, as well as
					 *       the offset into the file, alongside the original pointer:
					 *       `0x12345678 ("/path/to/file"+offset_into_file)' */
	
					/* TODO: Check if `ptr' points into kernel heap memory. If it
					 *       is, then print it as `0x12345678 (heap)' */
	
					/* TODO: If nothing is mapped where `ptr' points to, then we
					 *       should print it in a different color (iow: use a custom
					 *       prefix/suffix pair for unmapped pointers)
					 * That way, when debugging segmentation faults, it becomes easy
					 * to stop faulty pointers. */
				}
			}
			ATTR_FALLTHROUGH
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM): {
			/* Enum or integer */
			if (CTYPE_KIND_SIZEOF(kind) <= sizeof(intmax_t)) {
				union {
					intmax_t s;
					uintmax_t u;
				} value;
				memset(&value, 0, sizeof(value));
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
				memcpy(&value, buf, CTYPE_KIND_SIZEOF(kind));
				if (!CTYPE_KIND_INT_ISUNSIGNED(kind)) {
					/* Check for sign-extension */
					if (((byte_t *)&value.u)[CTYPE_KIND_SIZEOF(kind) - 1] & 0x80)
						memset((byte_t *)&value + CTYPE_KIND_SIZEOF(kind), 0xff,
						       sizeof(value) - CTYPE_KIND_SIZEOF(kind));
				}
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
				memcpy((byte_t *)&value + sizeof(value) - CTYPE_KIND_SIZEOF(kind),
				       buf, CTYPE_KIND_SIZEOF(kind));
				if (!CTYPE_KIND_INT_ISUNSIGNED(kind)) {
					/* Check for sign-extension */
					if (((byte_t *)&value.u)[sizeof(value) - CTYPE_KIND_SIZEOF(kind)] & 0x80)
						memset((byte_t *)&value, 0xff, sizeof(value) - CTYPE_KIND_SIZEOF(kind));
				}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
				if (CTYPE_KIND_ISENUM(kind)) {
					dbx_errno_t error;
					struct ctypeenumname name;
					/* Try to lookup an enum constant name. */
					error = ctype_enumname(me, &name, value.s);
					if (error == DBX_EOK) {
						temp = 0;
						if (printer->cp_format) {
							temp = (*printer->cp_format)(printer->cp_format_arg,
							                             printer->cp_printer, printer->cp_arg,
							                             DEBUGINFO_PRINT_FORMAT_CONSTANT_PREFIX);
						}
						if likely(temp >= 0) {
							result += temp;
							temp = (*P_PRINTER)(P_ARG, name.en_name, strlen(name.en_name));
						}
						ctypeenumname_fini(&name);
						if unlikely(temp < 0)
							goto err;
						result += temp;
						FORMAT(DEBUGINFO_PRINT_FORMAT_CONSTANT_SUFFIX);
						break;
					}
				}
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
				if (flags & CTYPE_PRINTVALUE_FLAG_FORCEHEX)
					goto print_integer_value_as_hex;
				if (!CTYPE_KIND_ISINT(kind))
					goto print_integer_value_as_hex; /* Always print pointers as HEX */
				if (!CTYPE_KIND_ISENUM(kind) &&
				    !CTYPE_KIND_INT_ISUNSIGNED(kind) &&
				    value.s < 0) {
					/* Always print negative numbers as decimals. */
					PRINTF("%" PRIdMAX, value.s);
				} else {
					/* Fallback: Print an unsigned integer value, either as decimal, or as hex. */
					size_t decimal_len;
					char decimal_repr[CEILDIV(sizeof(value.u) * NBBY, 3) + 1];
					decimal_len = sprintf(decimal_repr, "%" PRIdMAX, value.u);
					if (value.u < 255 || use_decimal_representation(decimal_repr, decimal_len)) {
						DO((*P_PRINTER)(P_ARG, decimal_repr, decimal_len));
					} else {
						char buf[2 + CEILDIV(sizeof(intmax_t) * NBBY, 4)], *ptr;
						size_t max_digits;
print_integer_value_as_hex:
						/* Figure out the max number of digits.
						 * Without this, negative numbers would always be
						 * printed with all digits that would be needed to
						 * represent a uintmax_t with the most significant
						 * bit set. */
						max_digits = CEILDIV(CTYPE_KIND_SIZEOF(kind) * NBBY, 4);
						/* Convert to hex */
						ptr = COMPILER_ENDOF(buf);
						while (value.u && max_digits) {
							*--ptr = tohex(value.u & 0xf);
							value.u >>= 4;
							--max_digits;
						}
						*--ptr = 'x';
						*--ptr = '0';
						DO((*P_PRINTER)(P_ARG, ptr, (size_t)(COMPILER_ENDOF(buf) - ptr)));
					}
				}
			} else {
				/* Value too large to load directly. - Instead, write
				 * out its contents in HEX, using the native byteorder. */
				size_t i;
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
				PRINT("0x");
				for (i = 0; i < CTYPE_KIND_SIZEOF(kind); ++i) {
					char repr[2];
					byte_t b;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					b = ((byte_t *)buf)[CTYPE_KIND_SIZEOF(kind) - i];
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
					b = ((byte_t *)buf)[i];
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
					repr[0] = tohex(b >> 4);
					repr[1] = tohex(b & 0xf);
					DO((*P_PRINTER)(P_ARG, repr, 2));
				}
			}
			if ((flags & CTYPE_PRINTVALUE_FLAG_INTSUFFIX) &&
			    CTYPE_KIND_ISINT(kind)) {
				/* Print the proper integer type suffix. */
				char const *suffix = NULL;
				if (me == &ctype_unsigned_int) {
					suffix = "u";
				} else if (me == &ctype_long) {
					suffix = "l";
				} else if (me == &ctype_unsigned_long) {
					suffix = "ul";
				} else if (me == &ctype_long_long) {
					suffix = "ll";
				} else if (me == &ctype_unsigned_long_long) {
					suffix = "ull";
				} else if (CTYPE_KIND_SIZEOF(kind) > sizeof(int)) {
					/* Generic, fixed-width integer type suffix. */
					PRINTF("i%s%" PRIuSIZ,
					       !CTYPE_KIND_ISENUM(kind) &&
					       CTYPE_KIND_INT_ISUNSIGNED(kind)
					       ? "u"
					       : "",
					       (size_t)CTYPE_KIND_SIZEOF(kind) * NBBY);
				}
				if (suffix)
					DO((*P_PRINTER)(P_ARG, suffix, strlen(suffix)));
			}
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
		}	break;

		/* TODO: CTYPE_KIND_STRUCT */

		case CTYPE_KIND_ARRAY: {
			size_t used_length, elem_size;
			unsigned int string_kind;
			used_length = me->ct_array.ca_count;
			string_kind = CSTRING_KIND_INVALID;
			/* Check if we can print this array as a string. */
			if (me->ct_array.ca_elem == &ctype_char) {
				/* Automatically derive length of a VLA */
				if (!used_length)
					used_length = strlen((char const *)buf);
				string_kind = CSTRING_KIND_NORMAL;
			} else if (me->ct_array.ca_elem == &ctype_char16_t) {
				if (!used_length)
					used_length = rawmemlenw(buf, 0);
				string_kind = CSTRING_KIND_CHAR16;
			} else if (me->ct_array.ca_elem == &ctype_char32_t) {
				if (!used_length)
					used_length = rawmemlenl(buf, 0);
				string_kind = CSTRING_KIND_CHAR32;
			}
			if (used_length)
				peekb(buf); /* Make sure that memory from `buf' doesn't fault. */
			if (string_kind != CSTRING_KIND_INVALID) {
				size_t buflen = used_length;
				if (string_kind == CSTRING_KIND_CHAR32)
					buflen *= 4;
				else if (string_kind == CSTRING_KIND_CHAR16) {
					buflen *= 2;
				}
				/* Print as a string. */
				DO(ctype_printcstring(printer, buf, buflen, string_kind));
				break;
			}
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
			PRINT("{");
			elem_size = ctype_sizeof(me->ct_array.ca_elem);
			if (!used_length || !elem_size) {
				/* Empty array... */
			} else {
				FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
				if (flags & CTYPE_PRINTVALUE_FLAG_NORECURSION) {
					FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_PREFIX);
					PRINT("...");
					FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_SUFFIX);
				} else {
					size_t i;
					bool do_multiline;
					struct ctyperef elem_type;
					firstline_indent += 1; /* Account for the leading '{' */
					memset(&elem_type, 0, sizeof(elem_type));
					elem_type.ct_flags = self->ct_flags;
					elem_type.ct_typ   = me->ct_array.ca_elem;
					elem_type.ct_info  = me->ct_array.ca_eleminfo;
					if (flags & CTYPE_PRINTVALUE_FLAG_ONELINE) {
						do_multiline = false;
					} else if (flags & CTYPE_PRINTVALUE_FLAG_NOSHORTLINES) {
						do_multiline = true;
					} else {
						size_t peek_indent;
						peek_indent  = firstline_indent;
						do_multiline = false;
						/* Automatically determine if we need multi-line. */
						for (i = 0; i < used_length; ++i) {
							byte_t const *elem_addr;
							elem_addr = (byte_t const *)buf + i * elem_size;
							peek_indent = ctype_printvalue_nextindent(&elem_type, elem_addr,
							                                          flags, peek_indent,
							                                          newline_indent, newline_tab,
							                                          maxlinelen, &do_multiline,
							                                          true);
							if (do_multiline)
								break;
							peek_indent += 1; /* ',' or '}' */
							if (i < used_length - 1)
								peek_indent += 1; /* Space after ',' */
							if (peek_indent > maxlinelen) {
								do_multiline = true;
								break;
							}
						}
					}
					if (do_multiline) {
						PRINT("\n");
						newline_indent += newline_tab;
						REPEAT(' ', newline_indent); /* Print leading spaces. */
						firstline_indent = newline_indent;
					}
					for (i = 0; i < used_length; ++i) {
						byte_t const *elem_addr;
						size_t elem_indent = firstline_indent;
						elem_addr = (byte_t const *)buf + i * elem_size;
						if (i != 0)
							++elem_indent; /* For the leading space */
						if (do_multiline) {
							bool contains_newline;
							/* Check if we must insert a new-line before this element. */
							contains_newline = false;
							firstline_indent = ctype_printvalue_nextindent(&elem_type, elem_addr,
							                                               flags, elem_indent,
							                                               newline_indent, newline_tab,
							                                               maxlinelen, &contains_newline,
							                                               false);
							if (i < used_length - 1)
								firstline_indent += 1; /* For the trailing comma */
							if (contains_newline || firstline_indent <= maxlinelen) {
								if (i != 0)
									PRINT(" "); /* Add a space after the comma of the previous element. */
							} else {
								/* Insert a line-feed before the element. */
								PRINT("\n");
								REPEAT(' ', newline_indent); /* Print leading spaces. */
								elem_indent = newline_indent;
								goto do_calculate_next_indent;
							}
						} else {
							if (i != 0)
								PRINT(" "); /* Add a space after the comma of the previous element. */
do_calculate_next_indent:
							firstline_indent = ctype_printvalue_nextindent(&elem_type, elem_addr,
							                                               flags, elem_indent,
							                                               newline_indent, newline_tab,
							                                               maxlinelen, NULL, false);
						}
						/* Recursively print the array element. */
						DO(ctype_printvalue(&elem_type, printer, elem_addr,
						                    flags, elem_indent,
						                    newline_indent, newline_tab,
						                    maxlinelen));
						if (i < used_length - 1) {
							FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
							PRINT(",");
							FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
						}
					}
					if (do_multiline) {
						PRINT("\n");
						newline_indent -= newline_tab;
						REPEAT(' ', newline_indent); /* Print leading spaces. */
						/*firstline_indent = newline_indent;*/
					}
				}
				FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
			}
			PRINT("}");
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
		}	break;

		default: {
			size_t i, size;
			bool do_multiline;
			/* Fallback: Print as `(TYPE){BUF[0] BUF[1] ... BUF[N-1]}' */
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			PRINT("(");
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
			DO(ctyperef_printname(self, printer, NULL, 0));
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
			PRINT(")");
			FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
			PRINT("{");
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
			size = ctype_sizeof(me);
			if (size != 0) {
				if (flags & CTYPE_PRINTVALUE_FLAG_ONELINE) {
					do_multiline = false;
				} else if (flags & CTYPE_PRINTVALUE_FLAG_NOSHORTLINES) {
					do_multiline = true;
				} else {
					firstline_indent += (size_t)ctyperef_printname(self, &lenprinter, NULL, 0);
					firstline_indent += 3;
					firstline_indent += size * 3;
					do_multiline = firstline_indent > maxlinelen;
				}
				if (do_multiline) {
					PRINT("\n");
					newline_indent += newline_tab;
					REPEAT(' ', newline_indent); /* Print leading spaces. */
					firstline_indent = newline_indent;
				}
				FORMAT(DEBUGINFO_PRINT_FORMAT_UNKNOWN_PREFIX);
				for (i = 0;; ++i) {
					byte_t b = ((byte_t *)buf)[i];
					PRINTF("%.2" PRIX8, b);
					if (i >= size - 1)
						break;
					if (do_multiline) {
						firstline_indent += 3;
						if (firstline_indent > maxlinelen) {
							FORMAT(DEBUGINFO_PRINT_FORMAT_UNKNOWN_SUFFIX);
							PRINT("\n");
							REPEAT(' ', newline_indent); /* Print leading spaces. */
							FORMAT(DEBUGINFO_PRINT_FORMAT_UNKNOWN_PREFIX);
							firstline_indent = newline_indent;
							continue;
						}
					}
					PRINT(" ");
				}
				FORMAT(DEBUGINFO_PRINT_FORMAT_UNKNOWN_SUFFIX);
				if (do_multiline) {
					PRINT("\n");
					newline_indent -= newline_tab;
					REPEAT(' ', newline_indent); /* Print leading spaces. */
					/*firstline_indent = newline_indent;*/
				}
			}
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
			PRINT("}");
			FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
		}	break;
		}
	} EXCEPT {
		PRINT("<segfault>");
	}
	return result;
err:
	return temp;
}




DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_CPRINTER_C */
