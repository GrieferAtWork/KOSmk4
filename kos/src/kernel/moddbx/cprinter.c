/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODDBX_CPRINTER_C
#define GUARD_MODDBX_CPRINTER_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <sys/param.h>

#include <assert.h>
#include <ctype.h>
#include <format-printer.h>
#include <int128.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unicode.h>

#include <libdebuginfo/addr2line.h>

/**/
#include "include/cprinter.h"
#include "include/ctype.h"
#include "include/malloc.h"
#include "include/obnote.h"

/* Support for `x86_phys2virt64_node' */
#undef HAVE_X86_PHYS2VIRT64_NODE
#if defined(__i386__) || defined(__x86_64__)
#include <kernel/x86/phys2virt64.h> /* x86_phys2virt64_node */
#ifdef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
#define HAVE_X86_PHYS2VIRT64_NODE
#endif /* CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC */
#endif /* __i386__ || __x86_64__ */

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
	for (i = 0; i < lengthof(c_typeflags); ++i) {
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
	char          btn_name[CEIL_ALIGN(20, sizeof(void *))]; /* Name */
	struct ctype *btn_type;                                 /* [1..1] Type. */
};

PRIVATE struct builtin_type_name const builtin_type_names[] = {
//	{ "bool", &ctype_bool }, /* Special handling... */
	{ "float", &ctype_ieee754_float },
	{ "double", &ctype_ieee754_double },
#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
	{ "long double", &ctype_ieee854_long_double },
#endif /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
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


PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printprefix)(struct ctyperef const *__restrict self,
                                        struct cprinter const *__restrict printer) {
	/* Check for simple case: the type has a name. */
	ssize_t temp, result = 0;
	char const *prefix;
	NCX char const *type_name;
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
			if (typ == &ctype_bool) {
				type_name = "bool";
			} else {
				/* Fallback: Variable-length-boolean type. */
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
				PRINTF("BOOL%" PRIuSIZ, (size_t)(CTYPE_KIND_SIZEOF(typ->ct_kind) * 8));
				FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
				goto after_name_prefix_printed;
			}
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
			if (CTYPE_KIND_ISENUM(typ->ct_kind)) {
				type_name = ""; /* Unnamed enum. */
			} else {
				/* Select names of known types. */
				unsigned int i;
				for (i = 0; i < lengthof(builtin_type_names); ++i) {
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
			static_assert(offsetof(struct ctype, ct_pointer.cp_base) ==
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

PRIVATE ATTR_CONST ATTR_RETNONNULL WUNUSED char const *
NOTHROW(FCALL cc_attribute)(uintptr_t cc) {
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


PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printsuffix_head)(struct ctyperef *__restrict self,
                                             struct cprinter const *__restrict printer,
                                             NCX char const *varname, size_t varname_len) {
	ssize_t temp, result = 0;
	struct ctype *typ;
again:
	if (self->ct_info.ci_name)
		goto do_print_varname_suffix;
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
do_print_varname_suffix:
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

PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printsuffix_tail)(struct ctyperef const *__restrict self,
                                             struct cprinter const *__restrict printer) {
	ssize_t temp, result = 0;
	struct ctype *me;
again:
	if (self->ct_info.ci_name)
		goto done;
	me = self->ct_typ;
again_me:
	switch (CTYPE_KIND_CLASSOF(me->ct_kind)) {

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR): {
		struct ctype *inner;
		inner = me->ct_pointer.cp_base.ct_typ;
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
		self = &me->ct_pointer.cp_base;
		goto again;
	}	break;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ARRAY):
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_PREFIX);
		PRINT("[");
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_SUFFIX);
		FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
		PRINTF("%" PRIuSIZ, me->ct_array.ca_count);
		FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_PREFIX);
		PRINT("]");
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_SUFFIX);
		if (me->ct_array.ca_eleminfo.ci_name)
			goto done;
		me = me->ct_array.ca_elem;
		goto again_me;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_FUNCTION):
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
		PRINT("(");
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		if (me->ct_function.cf_argc == 0) {
			if (me->ct_kind & CTYPE_KIND_FUNPROTO_VARARGS)
				goto do_print_dots;
			FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX);
			PRINT("void");
			FORMAT(DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX);
		} else {
			size_t i;
			for (i = 0; i < me->ct_function.cf_argc; ++i) {
				if (i != 0) {
					FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
					PRINT(",");
					FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
					PRINT(" ");
				}
				DO(ctyperef_printname(&me->ct_function.cf_argv[i],
				                      printer, NULL, 0));
			}
			if (me->ct_kind & CTYPE_KIND_FUNPROTO_VARARGS) {
				if (me->ct_function.cf_argc != 0) {
					FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
					PRINT(",");
					FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
					PRINT(" ");
do_print_dots:
					FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_PREFIX);
					PRINT("...");
					FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_SUFFIX);
				}
			}
		}
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX);
		PRINT(")");
		FORMAT(DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX);
		self = &me->ct_function.cf_base;
		goto again;

	default:
		break;
	}
done:
	return result;
err:
	return temp;
}


/* Print the correct representation of the given type, including
 * an optional, contained variable name that is also printed  at
 * the proper location. */
PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL ctyperef_printname)(struct ctyperef const *__restrict self,
                                         struct cprinter const *__restrict printer,
                                         NCX char const *varname, size_t varname_len) {
	ssize_t temp, result;
	struct ctyperef me;

	/* Print the type prefix. */
	result = ctype_printprefix(self, printer);
	if unlikely(result < 0)
		goto done;

	/* Print the type suffix head+tail. */
	memcpy(&me, self, sizeof(me));
	DO(ctype_printsuffix_head(&me, printer, varname, varname_len));
	DO(ctype_printsuffix_tail(self, printer));
done:
	return result;
err:
	return temp;
}

PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printname)(struct ctype const *__restrict self,
                                      struct cprinter const *__restrict printer,
                                      NCX char const *varname, size_t varname_len) {
	struct ctyperef ct;
	bzero(&ct, sizeof(ct));
	ct.ct_typ = (struct ctype *)self;
	return ctyperef_printname(&ct, printer, varname, varname_len);
}


struct indent_printer_data {
	size_t indent;
	bool *pcontains_newline;
	bool stop_after_newline;
};

PRIVATE ssize_t
NOTHROW_NCX(FORMATPRINTER_CC indent_printer)(void *arg, char const *__restrict data, size_t datalen) {
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

PRIVATE NONNULL((1)) size_t
NOTHROW_CB_NCX(KCALL ctype_printvalue_nextindent)(struct ctyperef const *__restrict self,
                                                  NCX void const *buf, unsigned int flags,
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
	 * If  so,  then  the  decimal  representation  should  be  used. */
	size_t threshold = (len * 5) / 3;
	char ch;
	for (ch = '0'; ch <= '9'; ++ch) {
		if (count_characters(decimal_repr, len, ch) >= threshold)
			return true;
	}
	return false;
}


PRIVATE struct cprinter const lenprinter = {
	.cp_printer = &format_length,
	.cp_format  = NULL,
};




#define CSTRING_KIND_NORMAL  0
#define CSTRING_KIND_CHAR16  1
#define CSTRING_KIND_CHAR32  2
#define CSTRING_KIND_INVALID ((unsigned int)-1)
PRIVATE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printcstring)(struct cprinter const *__restrict printer,
                                         NCX void const *buf, size_t len,
                                         unsigned int kind) {
	ssize_t temp, result = 0;
	char prefix[2], *ptr;
	NCX byte_t const *reader, *end;
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
		char unicode_buf[UNICODE_UTF8_MAXLEN], *ptr;
		switch (kind) {

		default: {
			size_t buflen;
			char *temp_reader;
			buflen = (size_t)(end - reader);
			if (buflen > sizeof(unicode_buf))
				buflen = sizeof(unicode_buf);
			if (dbg_readmemory(reader, unicode_buf, buflen) != 0)
				goto err_segfault;
			temp_reader = unicode_buf;
			ch = unicode_readutf8_n((char **)&temp_reader, unicode_buf + buflen);
			reader += (size_t)(temp_reader - unicode_buf);
		}	break;

		case CSTRING_KIND_CHAR16: {
			size_t buflen;
			char16_t temp_buf[2];
			char16_t *temp_reader;
			buflen = (size_t)((char16_t const *)end - (char16_t const *)reader);
			if (buflen > 2)
				buflen = 2;
			if (dbg_readmemory(reader, temp_buf, buflen * sizeof(char16_t)) != 0)
				goto err_segfault;
			temp_reader = temp_buf;
			ch = unicode_readutf16_n((char16_t **)&temp_reader, temp_buf + buflen);
			reader += (size_t)((byte_t const *)temp_reader - (byte_t const *)temp_buf);
		}	break;

		case CSTRING_KIND_CHAR32:
			if (dbg_readmemory(reader, &ch, sizeof(char32_t)) != 0)
				goto err_segfault;
			reader += 4;
			break;
		}
		ptr = unicode_writeutf8(unicode_buf, ch);
		DO(format_escape(P_PRINTER, P_ARG,
		                 unicode_buf, (size_t)(ptr - unicode_buf),
		                 FORMAT_ESCAPE_FPRINTRAW));
	}
	PRINT("\"");
	FORMAT(DEBUGINFO_PRINT_FORMAT_STRING_SUFFIX);
done:
	return result;
err:
	return temp;
err_segfault:
	PRINT("\"");
	FORMAT(DEBUGINFO_PRINT_FORMAT_STRING_SUFFIX);
	FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_PREFIX);
	PRINT("<segfault>");
	FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_SUFFIX);
	goto done;
}


struct ctype_printstruct_ismultiline_data {
	NCX void const *buf;              /* [const] */
	unsigned int        flags;            /* [const] Flags for printing the field */
	unsigned int        inner_flags;      /* [const] Flags for printing the pointed-to object */
	size_t              firstline_indent; /* [in|out] */
	size_t              newline_indent;   /* [const] */
	size_t              newline_tab;      /* [const] */
	size_t              maxlinelen;       /* [const] */
	size_t              out_field_count;  /* [out] Increment for every field encountered. */
	bool                out_contains_lf;  /* [out] Set to true if the output contains line-feeds */
};

PRIVATE NONNULL((1, 2, 3, 4, 5)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printstruct_ismultiline_callback)(void *cookie,
                                                             di_debuginfo_member_t const *__restrict member,
                                                             di_debuginfo_cu_parser_t const *__restrict parser,
                                                             struct cmodule *__restrict mod,
                                                             struct cmodunit *__restrict cu) {
	struct ctype_printstruct_ismultiline_data *arg;
	size_t prefix_length;
	arg = (struct ctype_printstruct_ismultiline_data *)cookie;
	prefix_length = 0;
	if (arg->out_field_count != 0)
		prefix_length += 2; /* ", " */
	if (arg->flags & CTYPE_PRINTVALUE_FLAG_NOSTRUCTFIELDS) {
		/* Don't print field names. */
	} else {
		if likely(member->m_name)
			prefix_length += strlen(member->m_name);
		if (arg->flags & CTYPE_PRINTVALUE_FLAG_CSTYLESTRUCTFIELDS) {
			/* '.name = '
			 *  ^    ^^^
			 *  +4 */
			prefix_length += 4;
		} else {
			/* 'name: '
			 *      ^^
			 *  +2 */
			prefix_length += 2;
		}
	}
	arg->firstline_indent += prefix_length;
	++arg->out_field_count;
	if (arg->firstline_indent >= arg->maxlinelen) {
		arg->out_contains_lf = true;
	} else {
		struct ctyperef member_type;
		NCX byte_t const *member_addr;

		/* Load type information for this member. */
		if (ctype_fromdw(mod, cu, parser, member->m_type, &member_type) != DBX_EOK)
			return 0;

		/* Check if printing this field causes a line-wrap, or exceeds the max line width */
		member_addr           = (byte_t const *)arg->buf + member->m_offset;
		arg->firstline_indent = ctype_printvalue_nextindent(&member_type, member_addr,
		                                                    arg->inner_flags,
		                                                    arg->firstline_indent,
		                                                    arg->newline_indent,
		                                                    arg->newline_tab,
		                                                    arg->maxlinelen,
		                                                    &arg->out_contains_lf,
		                                                    true);
		ctyperef_fini(&member_type);
	}
	if (arg->out_contains_lf)
		return -1; /* Stop enumeration */
	return 1;
}

PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW(KCALL ctype_struct_is_nonempty_callback)(void *UNUSED(cookie),
                                                 di_debuginfo_member_t const *__restrict UNUSED(member),
                                                 di_debuginfo_cu_parser_t const *__restrict UNUSED(parser),
                                                 struct cmodule *__restrict UNUSED(mod),
                                                 struct cmodunit *__restrict UNUSED(cu)) {
	return -1;
}



struct ctype_printstruct_data {
	struct cprinter const *printer;          /* [const][1..1] */
	NCX void const        *buf;              /* [const] */
	unsigned int           flags;            /* [const] Flags for printing the field */
	unsigned int           inner_flags;      /* [const] Flags for printing the pointed-to object */
	size_t                 firstline_indent; /* [in|out] */
	size_t                 newline_indent;   /* [const] */
	size_t                 newline_tab;      /* [const] */
	size_t                 maxlinelen;       /* [const] */
	size_t                 out_field_count;  /* [out] Increment for every field encountered. */
	bool                   do_multiline;     /* [const] True if printing in multi-line mode. */
};

PRIVATE NONNULL((1, 2, 3, 4, 5)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printstruct_callback)(void *cookie,
                                                 di_debuginfo_member_t const *__restrict member,
                                                 di_debuginfo_cu_parser_t const *__restrict parser,
                                                 struct cmodule *__restrict mod,
                                                 struct cmodunit *__restrict cu) {
	ssize_t temp, result = 0;
	struct ctype_printstruct_data *arg;
	struct ctyperef member_type;
	NCX byte_t const *member_addr;
	size_t prefix_length, next_indent;
	size_t elem_indent, name_length;
	struct cprinter const *printer;
	bool contains_newline;
	arg           = (struct ctype_printstruct_data *)cookie;
	printer       = arg->printer;
	member_addr   = (byte_t const *)arg->buf + member->m_offset;
	prefix_length = 0;

	/* Load type information for this member. */
	if (ctype_fromdw(mod, cu, parser, member->m_type, &member_type) != DBX_EOK)
		return 0;
	if (CTYPE_KIND_ISARRAY(member_type.ct_typ->ct_kind) &&
	    member_type.ct_typ->ct_array.ca_count == 0 && member->m_name) {
		size_t namelen = strlen(member->m_name);
		if (namelen >= 2 && member->m_name[namelen - 1] == 'v') {
			/* TODO: Special handling for variable-length arrays in structures:
			 * >> struct {
			 * >>     size_t      my_elemc;
			 * >>     struct elem my_elemv[];
			 * >> };
			 * In this case, we can guess the length of `my_elemv' to be equal
			 * to  `my_elemc', which  we could  access by-name  at this point.
			 * As such, special handling should be done here in order to print
			 * the correct # of elements for `my_elemv' */
		}
	}

	/* Print the leading "," */
	if (arg->out_field_count != 0) {
		FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
		PRINT(",");
		FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
		arg->firstline_indent += 1; /* "," */
		++prefix_length;            /* " " (following the ",") */
	}
	name_length = 0;
	if (arg->flags & CTYPE_PRINTVALUE_FLAG_NOSTRUCTFIELDS) {
		/* Don't print field names. */
	} else {
		if likely(member->m_name) {
			name_length = strlen(member->m_name);
			prefix_length += name_length;
			if (arg->flags & CTYPE_PRINTVALUE_FLAG_CSTYLESTRUCTFIELDS) {
				/* '.name = '
				 *  ^    ^^^
				 *  +4 */
				prefix_length += 4;
			} else {
				/* 'name: '
				 *      ^^
				 *  +2 */
				prefix_length += 2;
			}
		}
	}
	if (arg->flags & CTYPE_PRINTVALUE_FLAG_ONELINE) {
		elem_indent = 0;
		next_indent = 0;
		goto do_print_space_and_field;
	}

	/* Check how this member will end up being printed. */
	contains_newline = false;
	elem_indent = arg->firstline_indent + prefix_length;
	next_indent = ctype_printvalue_nextindent(&member_type, member_addr,
	                                          arg->inner_flags,
	                                          elem_indent,
	                                          arg->newline_indent,
	                                          arg->newline_tab,
	                                          arg->maxlinelen,
	                                          &contains_newline,
	                                          false);
	if (arg->out_field_count == 0) {
		/* Never print an additional linefeed before the first element. */
	} else
#if 1 /* Technically, this version should only  be used when there are  more
       * members within the struct after this one (since we'll end up having
       * to print another trailing ","  after our member). However we  don't
       * have an easy way of  knowing this ahead of  time, so to keep  stuff
       * a bit simpler, we just always check for this case. */
	if ((!contains_newline && (next_indent + 1) <= arg->maxlinelen) || !arg->do_multiline)
#else
	if ((!contains_newline && next_indent <= arg->maxlinelen) || !arg->do_multiline)
#endif
	{
		/* Print the field in-line. */
do_print_space_and_field:
		PRINT(" "); /* Add a space after the comma of the previous element. */
		/*--prefix_length;*/
	} else {
		size_t maybe_next_indent;
		--prefix_length; /* Discount the leading ' ' */

		/* Insert a line-feed before the element. */
		PRINT("\n");
		REPEAT(' ', arg->newline_indent); /* Print leading spaces. */
		elem_indent = arg->newline_indent + prefix_length;

		/* With the lowered indent, check if we can now print the member without
		 * any line-feeds, and if so,  use that new indent  for the rest of  the
		 * struct. */
		contains_newline = false;
		maybe_next_indent = ctype_printvalue_nextindent(&member_type, member_addr,
		                                                arg->inner_flags, elem_indent,
		                                                arg->newline_indent, arg->newline_tab,
		                                                arg->maxlinelen,
		                                                &contains_newline,
		                                                true);
		if (!contains_newline)
			next_indent = maybe_next_indent;
	}

	/* Actually print the prefix+member. */
	if (arg->flags & CTYPE_PRINTVALUE_FLAG_NOSTRUCTFIELDS) {
		/* Don't print field names. */
	} else {
		if likely(member->m_name) {
			FORMAT(DEBUGINFO_PRINT_FORMAT_FIELD_PREFIX);
			if (arg->flags & CTYPE_PRINTVALUE_FLAG_CSTYLESTRUCTFIELDS) {
				PRINT(".");
				DO((*P_PRINTER)(P_ARG, member->m_name, name_length));
				FORMAT(DEBUGINFO_PRINT_FORMAT_FIELD_SUFFIX);
				FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_PREFIX);
				PRINT(" = ");
				FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_SUFFIX);
			} else {
				DO((*P_PRINTER)(P_ARG, member->m_name, name_length));
				FORMAT(DEBUGINFO_PRINT_FORMAT_FIELD_SUFFIX);
				FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_PREFIX);
				PRINT(": ");
				FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_SUFFIX);
			}
		}
	}
	DO(ctype_printvalue(&member_type, arg->printer, member_addr,
	                    arg->inner_flags, elem_indent,
	                    arg->newline_indent, arg->newline_tab,
	                    arg->maxlinelen));
	ctyperef_fini(&member_type);
	arg->firstline_indent = next_indent;
	++arg->out_field_count;
	return result;
err:
	ctyperef_fini(&member_type);
	return temp;
}

PRIVATE bool
NOTHROW(KCALL dbg_strlen)(NCX void const *addr,
                          size_t *__restrict presult) {
	size_t result = 0;
	char buf[17];
	(COMPILER_ENDOF(buf)[-1]) = 0;
	for (;;) {
		size_t ok, temp;
		ok = (sizeof(buf) - sizeof(char)) -
		     dbg_readmemory(addr, buf, sizeof(buf) - sizeof(char));
		temp = strlen(buf);
		result += temp;
		if (temp < ok * sizeof(char))
			break;
		if (ok < sizeof(buf) - sizeof(char))
			return false;
		addr = (byte_t const *)addr + ok;
	}
	*presult = result;
	return true;
}

PRIVATE bool
NOTHROW(KCALL dbg_strlen16)(NCX void const *addr,
                            size_t *__restrict presult) {
	size_t result = 0;
	u16 buf[17];
	(COMPILER_ENDOF(buf)[-1]) = 0;
	for (;;) {
		size_t ok, temp;
		ok = (sizeof(buf) - sizeof(u16)) -
		     dbg_readmemory(addr, buf, sizeof(buf) - sizeof(u16));
		temp = rawmemlenw(buf, 0);
		result += temp;
		if (temp < ok * sizeof(u16))
			break;
		if (ok < sizeof(buf) - sizeof(u16))
			return false;
		addr = (byte_t const *)addr + ok;
	}
	*presult = result;
	return true;
}

PRIVATE bool
NOTHROW(KCALL dbg_strlen32)(NCX void const *addr,
                            size_t *__restrict presult) {
	size_t result = 0;
	u32 buf[17];
	(COMPILER_ENDOF(buf)[-1]) = 0;
	for (;;) {
		size_t ok, temp;
		ok = (sizeof(buf) - sizeof(u32)) -
		     dbg_readmemory(addr, buf, sizeof(buf) - sizeof(u32));
		temp = rawmemlenl(buf, 0);
		result += temp;
		if (temp < ok * sizeof(u32))
			break;
		if (ok < sizeof(buf) - sizeof(u32))
			return false;
		addr = (byte_t const *)addr + ok;
	}
	*presult = result;
	return true;
}


/* Compare memory for equality.
 * @return: true:  Memory is equal.
 * @return: false: Memory is not equal.
 * @return: false: Accessing memory failed. */
PRIVATE bool
NOTHROW(KCALL dbg_eqmemory)(NCX void const *a,
                            NCX void const *b,
                            size_t num_bytes) {
	byte_t a_buf[64];
	byte_t b_buf[64];
	while (num_bytes) {
		size_t temp;
		temp = num_bytes;
		if (temp > sizeof(a_buf))
			temp = sizeof(a_buf);
		if (dbg_readmemory(a, a_buf, temp) != 0 ||
		    dbg_readmemory(b, b_buf, temp) != 0)
			return false; /* Faulty memory */
		if (bcmp(a_buf, b_buf, temp) != 0)
			return false; /* Non-equal memory */
		a = (byte_t const *)a + temp;
		b = (byte_t const *)b + temp;
		num_bytes -= temp;
	}
	return true; /* Equal memory */
}

PRIVATE NONNULL((1, 5)) ssize_t
NOTHROW_CB_NCX(KCALL print_a2l_symbol)(struct cprinter const *__restrict printer,
                                       NCX void const *ptr,
                                       NCX char const *name,
                                       uintptr_t offset, module_t *__restrict mod) {
	ssize_t temp, result = 0;
	FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
	PRINTF("%#" PRIxPTR, ptr);
	FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
	PRINT(" ");
	FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX);
	PRINT("(");
	DO(module_hasname(mod) ? module_printname(mod, P_PRINTER, P_ARG)
	                       : (*P_PRINTER)(P_ARG, "?", 1));
	PRINT("!");
	DO((*P_PRINTER)(P_ARG, name, strlen(name)));
	if (offset != 0)
		PRINTF("+%#" PRIxPTR, offset);
	PRINT(")");
	FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_SUFFIX);
	return result;
err:
	return temp;
}

PRIVATE ssize_t
NOTHROW(FORMATPRINTER_CC is_nonempty_printer)(void *UNUSED(arg),
                                              char const *__restrict UNUSED(data),
                                              size_t datalen) {
	return datalen ? -1 : 0;
}


/* Try to determine the name of the section that `module_relative_addr'
 * is  apart of, and  return that name, whilst  storing the offset into
 * that section in `*psection_relative_addr'
 * If the section cannot be determined, return `NULL' instead. */
PRIVATE NONNULL((2, 3)) char const *
NOTHROW(KCALL get_name_and_offset_of_containing_sections)(uintptr_t module_relative_addr,
                                                          uintptr_t *__restrict psection_relative_addr,
                                                          module_t *__restrict mod) {
	TRY {
		struct module_sectinfo info;
		if (!module_sectinfo(mod, module_relative_addr, &info))
			return NULL;
		*psection_relative_addr = module_relative_addr - info.msi_addr;
		return info.msi_name;
	} EXCEPT {
	}
	return NULL;
}




PRIVATE ATTR_NOINLINE NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL print_object_note)(char const *__restrict name,
                                        struct cprinter const *__restrict printer,
                                        NCX void const *ptr) {
	ssize_t temp, result = 0;
	unsigned int status;
	/* Custom representations of pointers to objects from the kernel core. */
	status = OBNOTE_PRINT_STATUS_BADNAME;
	obnote_print(&is_nonempty_printer, NULL, ptr, name, &status);
	if (status == OBNOTE_PRINT_STATUS_BADOBJ) {
		/* Bad/Corrupt object */
		PRINT(" ");
		FORMAT(DEBUGINFO_PRINT_FORMAT_BADNOTES_PREFIX);
		PRINTF("(%s)", name);
		FORMAT(DEBUGINFO_PRINT_FORMAT_BADNOTES_SUFFIX);
	} else if (status == OBNOTE_PRINT_STATUS_SUCCESS) {
		/* Print a normal object note. */
		PRINT(" ");
		FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX);
		PRINTF("(%s ", name);
		DO(obnote_print(P_PRINTER, P_ARG, ptr, name, &status));
		PRINT(")");
		FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_SUFFIX);
	}
	return result;
err:
	return temp;
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL print_named_struct)(struct ctype *__restrict self,
                                         struct cprinter const *__restrict printer,
                                         NCX void const *ptr) {
	ssize_t temp, result = 0;
	struct cmodule *mod;
	mod = self->ct_struct.ct_info.cd_mod;
	if (cmodule_iskern(mod)) {
		if (mod->cm_module != (REF module_t *)&kernel_driver) {
			/* If the type was declared by a driver, it may actually
			 * originate from the kernel core. In this case, try  to
			 * load the pointed-to type. */
			ctype_struct_enumfields(self, &ctype_struct_is_nonempty_callback, NULL);
			mod = self->ct_struct.ct_info.cd_mod;
		}
		/*if (mod->cm_module == (REF module_t *)&kernel_driver)*/ {
			char const *name = ctype_struct_getname(self);
			if (name)
				DO(print_object_note(name, printer, ptr));
		}
	}
	return result;
err:
	return temp;
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2, 4)) ssize_t
NOTHROW_CB_NCX(KCALL print_named_pointer)(struct ctyperef const *__restrict self,
                                          struct cprinter const *__restrict printer,
                                          NCX void const *ptr,
                                          bool *__restrict pdid_print_something) {
	ssize_t temp, result = 0;
	bool is_void_pointer;

	if (ADDR_ISKERN(ptr)) {
		struct ctype *mytype = self->ct_typ;
		if (CTYPE_KIND_ISPOINTER(mytype->ct_kind)) {
			struct cmodule *mod;
			mytype = mytype->ct_pointer.cp_base.ct_typ;
			if (CTYPE_KIND_ISSTRUCT(mytype->ct_kind)) {
				mod = mytype->ct_struct.ct_info.cd_mod;
				if (cmodule_iskern(mod)) {
					if (mod->cm_module != (REF module_t *)&kernel_driver) {
						/* If the type was declared by a driver, it may actually
						 * originate from the kernel core. In this case, try  to
						 * load the pointed-to type. */
						ctype_struct_enumfields(mytype, &ctype_struct_is_nonempty_callback, NULL);
						mod = mytype->ct_struct.ct_info.cd_mod;
					}
					/*if (mod->cm_module == (REF module_t *)&kernel_driver)*/ {
						char const *name = ctype_struct_getname(mytype);
						if (name) {
							unsigned int status;
							/* Custom representations of pointers to objects from the kernel core. */
							status = OBNOTE_PRINT_STATUS_BADNAME;
							obnote_print(&is_nonempty_printer, NULL, ptr, name, &status);
							if (status == OBNOTE_PRINT_STATUS_BADOBJ) {
								/* Bad/Corrupt object */
								FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_PREFIX);
								PRINTF("%#" PRIxPTR, ptr);
								FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_SUFFIX);
								PRINT(" ");
								FORMAT(DEBUGINFO_PRINT_FORMAT_BADNOTES_PREFIX);
								PRINTF("(%s)", name);
								FORMAT(DEBUGINFO_PRINT_FORMAT_BADNOTES_SUFFIX);
								goto done;
							}
							if (status == OBNOTE_PRINT_STATUS_SUCCESS) {
								/* Print a normal object note. */
								FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
								PRINTF("%#" PRIxPTR, ptr);
								FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
								PRINT(" ");
								FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX);
								PRINTF("(%s ", name);
								DO(obnote_print(P_PRINTER, P_ARG, ptr, name, &status));
								PRINT(")");
								FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_SUFFIX);
								goto done;
							}
						}
					}
				}
			}
		}
	}

	/* Check if `ptr' is a text-/data-pointer. */
	{
		REF module_t *mod;
		if ((mod = module_fromaddr_nx(ptr)) != NULL) {
			uintptr_t module_relative_ptr;
			di_addr2line_sections_t sections;
			di_addr2line_dl_sections_t dl_sections;
			module_relative_ptr = (uintptr_t)ptr - module_getloadaddr(mod);
			/* Try to lookup  the name/base-address  of a  symbol
			 * that contains the given `ptr' and is part of `mod' */
			if (debug_addr2line_sections_lock(mod, &sections, &dl_sections) == DEBUG_INFO_ERROR_SUCCESS) {
				di_debug_addr2line_t a2l;
				if (debug_addr2line(&sections, &a2l, module_relative_ptr,
				                    DEBUG_ADDR2LINE_LEVEL_SOURCE,
				                    DEBUG_ADDR2LINE_FNORMAL) == DEBUG_INFO_ERROR_SUCCESS) {
					if (!a2l.al_rawname)
						a2l.al_rawname = a2l.al_name;
					if (a2l.al_rawname && !*a2l.al_rawname)
						a2l.al_rawname = NULL;
					if (a2l.al_rawname) {
						uintptr_t offset;
						offset = module_relative_ptr - a2l.al_symstart;
						temp = print_a2l_symbol(printer, ptr, a2l.al_rawname, offset, mod);
						debug_addr2line_sections_unlock(&dl_sections);
						module_decref_unlikely(mod);
						if unlikely(temp < 0)
							goto err;
						result += temp;
						goto done;
					}
				}
				debug_addr2line_sections_unlock(&dl_sections);
			}
			/* We know that the pointer (should) be located in one of the  module's
			 * sections. As such, try to check if we can determine the section that
			 * the pointer points into, so we can print a hint:
			 * >> 0x12345678 (libc.so!.text+0x54321) */
			{
				char const *section_name;
				uintptr_t section_offset;
				section_name = get_name_and_offset_of_containing_sections(module_relative_ptr,
				                                                          &section_offset, mod);
				if (section_name != NULL) {
					temp = print_a2l_symbol(printer, ptr, section_name,
					                        section_offset, mod);
					module_decref_unlikely(mod);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					goto done;
				}
			}
			module_decref_unlikely(mod);
		}
	}

	/* Check if `ptr'  is apart  of a  file mapping.  If it  is,
	 * print  the  absolute path  the  mapped file,  as  well as
	 * the offset into the file, alongside the original pointer:
	 * `0x12345678 ("/path/to/file"+offset_into_file)' */
	{
		struct mman *effective_mman;
		struct mnode *node;
		effective_mman = &mman_kernel;
		if (ADDR_ISUSER(ptr) && ADDR_ISKERN(dbg_current))
			effective_mman = dbg_current->t_mman;
		is_void_pointer = true;
		if ((effective_mman && ADDR_ISKERN(effective_mman)) &&
		    (node = mman_mappings_locate(effective_mman, ptr)) != NULL &&
		    (node->mn_mman == effective_mman)) {
			is_void_pointer = false;
#ifdef HAVE_X86_PHYS2VIRT64_NODE
			if (node == &x86_phys2virt64_node) {
				/* Special case: On x86_64, there  exists a mnode that  has
				 * some  special handling within  the #PF handler, allowing
				 * it to essentially implement a fast phys2virt translation
				 * mechanism.
				 * For this purpose, a portion of the virtual address space
				 * has  been designated  for the  purpose of  being made to
				 * hold lazily initialized mappings of physical memory. */
				physaddr_t paddr;
				paddr = (physaddr_t)((uintptr_t)ptr - (uintptr_t)KERNEL_PHYS2VIRT_MIN);
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
				PRINTF("%#" PRIxPTR, ptr);
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
				PRINT(" ");
				FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX);
				PRINTF("/dev/mem+%#" PRIxN(__SIZEOF_PHYSADDR_T__), paddr);
				FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_SUFFIX);
				goto done;
			} else
#endif /* HAVE_X86_PHYS2VIRT64_NODE */
			if (node->mn_part == NULL) {
				/* Pointer into reserved memory mapping. */
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
				PRINTF("%#" PRIxPTR, ptr);
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
				PRINT(" ");
				FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX);
				/* Print the pointed-to physical address (if the pointer is mapped) */
				if (pagedir_ismapped_p(effective_mman->mm_pagedir_p, ptr)) {
					physaddr_t paddr;
					paddr = pagedir_translate_p(effective_mman->mm_pagedir_p, ptr);
					PRINTF("rsvd:%#" PRIxN(__SIZEOF_PHYSADDR_T__), paddr);
				} else {
					PRINT("rsvd:void");
				}
				FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_SUFFIX);
				goto done;
			} else if (node->mn_fsname) {
				pos_t mapping_offset;
				mapping_offset = mpart_getminaddr(node->mn_part);
				mapping_offset += (uintptr_t)ptr - (uintptr_t)mnode_getaddr(node);
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
				PRINTF("%#" PRIxPTR, ptr);
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
				PRINT(" ");
				FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX);
				PRINT("(");
				if (node->mn_fspath) {
					temp = path_printent(node->mn_fspath,
					                     node->mn_fsname->fd_name,
					                     node->mn_fsname->fd_namelen,
					                     P_PRINTER, P_ARG);
				} else {
					temp = (*P_PRINTER)(P_ARG,
					                    node->mn_fsname->fd_name,
					                    node->mn_fsname->fd_namelen);
				}
				if unlikely(temp < 0)
					goto err;
				result += temp;
				PRINTF("+%#" PRIxN(__SIZEOF_POS_T__) ")", mapping_offset);
				FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_SUFFIX);
				goto done;
			} else if (ADDR_ISKERN(node->mn_part) &&
			           node->mn_part->mp_file == &mfile_phys) {
				physaddr_t paddr = (physaddr_t)mnode_getfileaddrat(node, ptr);
				/* Pointer into a physical memory mapping. */
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
				PRINTF("%#" PRIxPTR, ptr);
				FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
				PRINT(" ");
				/* Print the pointed-to physical address (if the pointer is mapped)
				 * For this purpose, assume that  an unmapped address simply  means
				 * that the pointer  hasn't been  loaded yet (which  we will  print
				 * just like any pointer that _has_ already been loaded)
				 *
				 * However, if the address _is_ mapped, then it _really_ should
				 * have the correct physical address loaded. If that's not  the
				 * case, the display the pointer with an error connotation. */
				if (!pagedir_ismapped_p(effective_mman->mm_pagedir_p, ptr)) {
print_normal_dev_mem_pointer:
					FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX);
					PRINTF("/dev/mem+%#" PRIxN(__SIZEOF_PHYSADDR_T__), paddr);
					FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_SUFFIX);
				} else {
					physaddr_t real_paddr;
					real_paddr = pagedir_translate_p(effective_mman->mm_pagedir_p, ptr);
					if likely(real_paddr == paddr)
						goto print_normal_dev_mem_pointer;
					FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_PREFIX);
					PRINTF("/dev/mem+%#" PRIxN(__SIZEOF_PHYSADDR_T__) " "
					       /*   */ "(%#" PRIxN(__SIZEOF_PHYSADDR_T__) "?)",
					       paddr, real_paddr);
					FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_SUFFIX);
				}
				goto done;
			} else {
				/* TODO: Check if `ptr' points into kernel heap memory.
				 *       If it is, then print it as `0x12345678 (heap)' */
			}
		}
	}


	/* If  nothing is  mapped where  `ptr' points  to, then we
	 * should print it in a different color (iow: use a custom
	 * prefix/suffix pair for unmapped pointers)
	 *
	 * That way, when debugging segmentation faults, it becomes easy
	 * to stop faulty pointers. */
	if (is_void_pointer) {
		FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_PREFIX);
		PRINTF("%#" PRIxPTR, ptr);
		FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_SUFFIX);
		goto done;
	}
	return result;
done:
	*pdid_print_something = true;
	return result;
err:
	return temp;
}



/* Print a  dereferenced function  at  `ptr'. Printing  is  first
 * attempted  to be performed by loading the name of the function
 * at the specified `ptr', and if that fails, or if `ptr' doesn't
 * point  at the exact start of a function, printing will instead
 * be done as though a function pointer had been given. */
PRIVATE ATTR_NOINLINE NONNULL((1)) ssize_t
NOTHROW_CB_NCX(KCALL print_function)(struct ctyperef const *__restrict self,
                                     struct cprinter const *__restrict printer,
                                     NCX void const *ptr, unsigned int flags,
                                     size_t firstline_indent, size_t newline_indent,
                                     size_t newline_tab, size_t maxlinelen) {
	/* Check if `ptr' is a text-/data-pointer. */
	{
		REF module_t *mod;
		if ((mod = module_fromaddr_nx(ptr)) != NULL) {
			uintptr_t module_relative_ptr;
			di_addr2line_sections_t sections;
			di_addr2line_dl_sections_t dl_sections;
			module_relative_ptr = (uintptr_t)ptr - module_getloadaddr(mod);
			/* Try to lookup  the name/base-address  of a  symbol
			 * that contains the given `ptr' and is part of `mod' */
			if (debug_addr2line_sections_lock(mod, &sections, &dl_sections) == DEBUG_INFO_ERROR_SUCCESS) {
				di_debug_addr2line_t a2l;
				if (debug_addr2line(&sections, &a2l, module_relative_ptr,
				                    DEBUG_ADDR2LINE_LEVEL_SOURCE,
				                    DEBUG_ADDR2LINE_FNORMAL) == DEBUG_INFO_ERROR_SUCCESS &&
				    module_relative_ptr == a2l.al_symstart) {
					if (!a2l.al_rawname)
						a2l.al_rawname = a2l.al_name;
					if (a2l.al_rawname && !*a2l.al_rawname)
						a2l.al_rawname = NULL;
					if (a2l.al_rawname) {
						ssize_t result, temp;
						/* Print a named type, using the symbol name from debug-info as varname. */
						result = ctyperef_printname(self, printer, a2l.al_rawname,
						                            strlen(a2l.al_rawname));
						debug_addr2line_sections_unlock(&dl_sections);
						module_decref_unlikely(mod);
						if likely(result >= 0) {
							/* Include the function module and address as a hint. */
							PRINT(" ");
							FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX);
							PRINT("(");
							DO(module_hasname(mod) ? module_printname(mod, P_PRINTER, P_ARG)
							                       : (*P_PRINTER)(P_ARG, "?", 1));
							PRINTF("!%#" PRIxPTR ")", ptr);
							FORMAT(DEBUGINFO_PRINT_FORMAT_NOTES_SUFFIX);
						}
						return result;
err:
						return temp;
					}
				}
				debug_addr2line_sections_unlock(&dl_sections);
			}
			module_decref_unlikely(mod);
		} /* if (mod) */
	} /* Scope */

	/* Fallback: Print as a function pointer */
	{
		ssize_t result;
		struct ctype pointer_type;
		struct ctyperef pointer_typeref;
		pointer_type.ct_refcnt = 0;
		pointer_type.ct_kind   = CTYPE_KIND_PTR;
		SLIST_INIT(&pointer_type.ct_children);
		memcpy(&pointer_type.ct_pointer.cp_base, self, sizeof(struct ctyperef));
		bzero(&pointer_type.ct_pointer._cp_sib, sizeof(pointer_type.ct_pointer._cp_sib));
		bzero(&pointer_typeref, sizeof(pointer_typeref));
		pointer_typeref.ct_typ = &pointer_type;
		/* Print the function object at `ptr' as a pointer-to-function. */
		result = ctype_printvalue(&pointer_typeref, printer, &ptr, flags,
		                          firstline_indent, newline_indent,
		                          newline_tab, maxlinelen);
		return result;
	} /* Scope */
}

/* Longest strings produced by 128-bit integer-to-string functions */
#define PRIMAXd128 "-170141183460469231731687303715884105728"
#define PRIMAXu128 "340282366920938463463374607431768211455"
#define PRIMAXx128 "0xffffffffffffffffffffffffffffffff"

PRIVATE WUNUSED NONNULL((1, 2)) char *KCALL
strbuf_print_decimal_uint128(char *p, uint128_t const *__restrict value) {
	char *endp = p + COMPILER_STRLEN(PRIMAXu128);
	char *iter = endp;
	uint128_t temp = *value;
	for (;;) {
		uint128_t new_temp;
		uint8_t digit;
		uint128_divmod8(temp, 10, new_temp, digit);
		*--iter = '0' + digit;
		temp = new_temp;
		if (uint128_iszero(temp))
			break;
	}
	p = (char *)mempmovedown(p, iter, (size_t)(endp - iter), sizeof(char));
	return p;
}

PRIVATE WUNUSED NONNULL((1, 2)) char *KCALL
strbuf_print_hex_uint128(char *p, uint128_t const *__restrict value) {
	uint8_t digit;
	size_t i = 15;
	*p++ = '0';
	*p++ = 'x';

	/* Skip leading 0-digits */
	for (;;) {
		digit = uint128_vec8_significand(*value, i);
		if (digit) {
			if (digit & 0xf0)
				*p++ = _itoa_lower_digits[(digit & 0xf0) >> 4];
			*p++ = _itoa_lower_digits[(digit & 0x0f)];
			break;
		}
		if (!i) {
			/* Special case: printing a literal number '0' */
			*p++ = '0';
			goto done;
		}
		--i;
	}

	/* Following the first non-zero digit, print everything. */
	while (i) {
		--i;
		digit = uint128_vec8_significand(*value, i);
		*p++  = _itoa_lower_digits[(digit & 0xf0) >> 4];
		*p++  = _itoa_lower_digits[(digit & 0x0f)];
	}
done:
	return p;
}

PRIVATE ATTR_NOINLINE NONNULL((1, 5)) dbx_errno_t
NOTHROW_CB_NCX(KCALL do_print_int128)(struct cprinter const *__restrict printer,
                                      NCX void const *ptr, bool is_unsigned,
                                      unsigned int flags, ssize_t *__restrict p_result) {
	ssize_t temp, result;
	union int128_union {
		uint128_t u;
		int128_t s;
	};
	char repr[MAX(MAX(COMPILER_STRLEN(PRIMAXd128),
	                  COMPILER_STRLEN(PRIMAXu128)),
	              COMPILER_STRLEN(PRIMAXx128)) +
	          COMPILER_STRLEN("iu128")];
	char *p = repr;
	union int128_union value;
	if unlikely(dbg_readmemory(ptr, &value.u, 16) != 0)
		return DBX_EFAULT;
	if (!is_unsigned && int128_isneg(value.s)) {
		*p++ = '-';
		int128_neg(value.s);
	}
	if (flags & CTYPE_PRINTVALUE_FLAG_FORCEHEX) {
do_print_hex:
		p = strbuf_print_hex_uint128(p, &value.u);
	} else if (p != repr || uint128_is8bit(value.u)) {
		p = strbuf_print_decimal_uint128(p, &value.u);
	} else {
		/* Determine later based on `use_decimal_representation()' */
		size_t len = (size_t)(strbuf_print_decimal_uint128(p, &value.u) - p);
		if (!use_decimal_representation(p, len))
			goto do_print_hex;
		p += len;
	}

	/* If the caller wants them, append a 128-bit integer suffix. */
	if (flags & CTYPE_PRINTVALUE_FLAG_INTSUFFIX) {
		*p++ = 'i';
		if (is_unsigned)
			*p++ = 'u';
		*p++ = '1';
		*p++ = '2';
		*p++ = '8';
	}

	/* Output the representation. */
	result = 0;
	FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
	DO((*P_PRINTER)(P_ARG, repr, (size_t)(p - repr)));
	FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
	*p_result = result;
	return DBX_EOK;
err:
	*p_result = temp;
	return DBX_EOK;
}


/* Print custom representations for special structs (like `int128_t')
 * @return: DBX_EOK:    A custom representation was printed.
 * @return: DBX_ENOENT: Given struct-type has no custom representation.
 * @return: DBX_EFAULT: Segmentation fault while trying to read from `ptr' */
PRIVATE WUNUSED NONNULL((1, 2, 4)) dbx_errno_t
NOTHROW_CB_NCX(KCALL print_special_struct)(struct ctyperef const *__restrict self,
                                           struct cprinter const *__restrict printer,
                                           NCX void const *ptr, ssize_t *__restrict p_result,
                                           unsigned int flags) {
	NCX char const *raw_name /*= NULL*/;
	struct ctype *typ = self->ct_typ;

	/* Caller should  have already  ensured  that this  is  a
	 * struct-type, but be fail-safe since we're the debugger */
	if unlikely(!CTYPE_KIND_ISSTRUCT(typ->ct_kind))
		return DBX_ENOENT;

	/* Special handling for `int128_t' and `uint128_t'. For
	 * this purpose, we (at least) want to match the types:
	 * - `int128_t'                 (from `<int128.h>')
	 * - `uint128_t'                (from `<int128.h>')
	 * - `__hybrid_int128_struct'   (from `<hybrid/int128.h>')
	 * - `__hybrid_uint128_struct'  (from `<hybrid/int128.h>')
	 * - `__hybrid_int128_t'        (from `<hybrid/int128.h>')
	 * - `__hybrid_uint128_t'       (from `<hybrid/int128.h>')
	 */
	if (typ->ct_struct.ct_sizeof == 16) {
		NCX char const *name;
		bool is_unsigned;
		/*if (raw_name == NULL)*/ {
			raw_name = ctype_struct_getname(typ);
			if (raw_name == NULL)
				raw_name = self->ct_info.ci_name;
		}
		name = raw_name;
		if (name != NULL) {
			for (;;) {
				if (*name == '_') {
					++name;
					continue;
				}
				if (memcmp(name, "hybrid_", COMPILER_STRLEN("hybrid_") * sizeof(char)) == 0) {
					name += COMPILER_STRLEN("hybrid_");
					continue;
				}
				break;
			}

			is_unsigned = false;
			if (*name == 'u') {
				is_unsigned = true;
				++name;
			}
			if (strcmp(name, "int128_struct") == 0 || strcmp(name, "int128_t") == 0)
				return do_print_int128(printer, ptr, is_unsigned, flags, p_result);
		}
	}

	/* Support for other special struct-types would go here. */
	return DBX_ENOENT;
}



/* Print a human-readable  representation of  the contents of  a given  data-buffer,
 * based on the C-typing of that buffer, which was likely extracted from debug info.
 * @param: self:             The typing of `buf'
 * @param: printer:          The printer used to output data.
 * @param: buf:              The data buffer that should be printed.
 *                           This should point to a block of `ctype_sizeof(self)' bytes.
 * @param: flags:            Printing flags (set of `CTYPE_PRINTVALUE_FLAG_*')
 * @param: firstline_indent: # of SPC (' ') characters already printed on the current line.
 * @param: newline_indent:   # of SPC (' ') characters to print after every \n-character.
 *                           Ignored  when   `CTYPE_PRINTVALUE_FLAG_ONELINE'  is   given.
 * @param: newline_tab:      Amount by which to increase `newline_indent' after a line-
 *                           feed  following  an  open-brace '{'  or  open-bracket '['.
 * @param: maxlinelen:       The max line  length that  should not be  exceeded by  when
 *                           placing   short  struct  initializers  on  the  same  line.
 *                           Ignored when `CTYPE_PRINTVALUE_FLAG_NOSHORTLINES' is given.
 *                           If insufficient space is available, do this:
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
 *                           Note that this limit isn't a guaranty, but only a hint. */
PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW_CB_NCX(KCALL ctype_printvalue)(struct ctyperef const *__restrict self,
                                       struct cprinter const *__restrict printer,
                                       NCX void const *buf, unsigned int flags,
                                       size_t firstline_indent, size_t newline_indent,
                                       size_t newline_tab, size_t maxlinelen) {
	/* TODO: This function is insanely inefficient for deeply nested
	 *       structures  such as printing libc's `current' (the main
	 *       problem being its `struct exception_info'-member)
	 * Solution:
	 *       Use  a virtual printer  that is limited by  the number of characters
	 *       it is is  allowed to print.  If one  tries to print  more than  that
	 *       amount, it will simply error out. On error, we know that a line-feed
	 *       needs to be  inserted, and on  success, we can  just use its  return
	 *       value  as the additional  indentation that will  be active after the
	 *       associated component is printed in-line.
	 *       Additionally,  when doing these checks we can always just pass the
	 *       `CTYPE_PRINTVALUE_FLAG_ONELINE' flag during the recursive calls to
	 *       `ctype_printvalue()', since we only care  if the next element  can
	 *       be printed  without any  line-feeds, and  without overflowing  the
	 *       horizontal display area.
	 */
	ssize_t temp, result = 0;
	struct ctype *me = self->ct_typ;
	uintptr_half_t kind = me->ct_kind;
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
			byte_t byte;
			if unlikely(dbg_readmemory((byte_t const *)buf + i, &byte, 1) != 0)
				goto err_segfault;
			if (byte != 0)
				is_nonzero = true;
		}
		FORMAT(DEBUGINFO_PRINT_FORMAT_TRUEFALSE_PREFIX);
		if (is_nonzero) {
			PRINT("true");
		} else {
			PRINT("false");
		}
		FORMAT(DEBUGINFO_PRINT_FORMAT_TRUEFALSE_SUFFIX);
	}	break;

	/* TODO: CTYPE_KIND_IEEE754_FLOAT */

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR):
		if ((CTYPE_KIND_SIZEOF(kind) <= sizeof(void *)) &&
		    ((flags & (CTYPE_PRINTVALUE_FLAG_NOSTRINGPOINTER | CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER)) !=
		    /*     */ (CTYPE_PRINTVALUE_FLAG_NOSTRINGPOINTER | CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER))) {
			void *ptr;
			bzero(&ptr, sizeof(ptr));
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			if unlikely(dbg_readmemory(buf, &ptr, CTYPE_KIND_SIZEOF(kind)) != 0)
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			if unlikely(dbg_readmemory(buf, (byte_t *)&ptr + sizeof(ptr) - CTYPE_KIND_SIZEOF(kind),
			                           CTYPE_KIND_SIZEOF(kind)) != 0)
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
			{
				goto err_segfault;
			}
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
				if (me->ct_pointer.cp_base.ct_typ == &ctype_char) {
					if (dbg_strlen(ptr, &buflen))
						kind = CSTRING_KIND_NORMAL;
				} else if (me->ct_pointer.cp_base.ct_typ == &ctype_char16_t) {
					if (dbg_strlen16(ptr, &buflen)) {
						buflen *= 2;
						kind = CSTRING_KIND_CHAR16;
					}
				} else if (me->ct_pointer.cp_base.ct_typ == &ctype_char32_t) {
					if (dbg_strlen32(ptr, &buflen)) {
						buflen *= 4;
						kind = CSTRING_KIND_CHAR32;
					}
				}
				if (kind != CSTRING_KIND_INVALID) {
					DO(ctype_printcstring(printer, ptr, buflen, kind));
					break;
				}
			}
			if (!(flags & CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER)) {
				bool did_print_something = false;
				DO(print_named_pointer(self, printer, ptr, &did_print_something));
				if (did_print_something)
					break;
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
			bzero(&value, sizeof(value));
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			if unlikely(dbg_readmemory(buf, &value, CTYPE_KIND_SIZEOF(kind)) != 0)
				goto err_segfault;
			if (!CTYPE_KIND_INT_ISUNSIGNED(kind)) {
				/* Check for sign-extension */
				if (((byte_t *)&value.u)[CTYPE_KIND_SIZEOF(kind) - 1] & 0x80)
					memset((byte_t *)&value + CTYPE_KIND_SIZEOF(kind), 0xff,
					       sizeof(value) - CTYPE_KIND_SIZEOF(kind));
			}
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			if unlikely(dbg_readmemory(buf, (byte_t *)&value + sizeof(value) - CTYPE_KIND_SIZEOF(kind),
			                           CTYPE_KIND_SIZEOF(kind)) != 0)
				goto err_segfault;
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
				char decimal_repr[lengthof(PRIMAXdMAX)];
				decimal_len = sprintf(decimal_repr, "%" PRIdMAX, value.u);
				if (value.u < 255 || use_decimal_representation(decimal_repr, decimal_len)) {
					DO((*P_PRINTER)(P_ARG, decimal_repr, decimal_len));
				} else {
					char hexbuf[2 + CEILDIV(sizeof(intmax_t) * NBBY, 4)], *ptr;
					size_t max_digits;
print_integer_value_as_hex:
					/* Figure out the max number of digits.
					 * Without  this, negative numbers would always be
					 * printed with all digits that would be needed to
					 * represent a uintmax_t with the most significant
					 * bit set. */
					max_digits = CEILDIV(CTYPE_KIND_SIZEOF(kind) * NBBY, 4);
					/* Convert to hex */
					ptr = COMPILER_ENDOF(hexbuf);
					while (value.u && max_digits) {
						*--ptr = _itoa_lower_digits[value.u & 0xf];
						value.u >>= 4;
						--max_digits;
					}
					*--ptr = 'x';
					*--ptr = '0';
					DO((*P_PRINTER)(P_ARG, ptr, (size_t)(COMPILER_ENDOF(hexbuf) - ptr)));
				}
			}
		} else
#if __SIZEOF_INTMAX_T__ < 16
		if (CTYPE_KIND_SIZEOF(kind) == 16 && !CTYPE_KIND_ISENUM(kind)) {
			/* Support for (compiler-native) 128-bit integers (if not already covered by `intmax_t'). */
			dbx_errno_t error;
			temp  = 0;
			error = do_print_int128(printer, buf, CTYPE_KIND_INT_ISUNSIGNED(kind), flags, &temp);
			if (error == DBX_EFAULT)
				goto err_segfault;
			if unlikely(temp < 0)
				goto err;
			result += temp;
		} else
#endif /* __SIZEOF_INTMAX_T__ < 16 */
		{
			/* Value too large to  load directly. - Instead,  write
			 * out its contents in HEX, using the native byteorder. */
			size_t i;
			FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
			PRINT("0x");
			if (!CTYPE_KIND_INT_ISUNSIGNED(kind)) {
				/* TODO: This needs support for signed, negative integers. */
			}
			for (i = 0; i < CTYPE_KIND_SIZEOF(kind); ++i) {
				char repr[2];
				byte_t b;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
				if unlikely(dbg_readmemory((byte_t const *)buf + (CTYPE_KIND_SIZEOF(kind) - i), &b, 1) != 0)
					goto err_segfault;
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
				if unlikely(dbg_readmemory((byte_t const *)buf + i, &b, 1) != 0)
					goto err_segfault;
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
				repr[0] = _itoa_lower_digits[b >> 4];
				repr[1] = _itoa_lower_digits[b & 0xf];
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
		if (!CTYPE_KIND_ISENUM(kind) && self->ct_info.ci_name != NULL &&
		    (self->ct_info.ci_nameref == NULL || cmodule_iskern(self->ct_info.ci_nameref))) {
			/* Certain integer types should be printed alongside custom
			 * object hints, such as  `fd_t', which should include  the
			 * associated  text  from `readlink  /proc/self/fd/$FD`, if
			 * any. */
			DO(print_object_note(self->ct_info.ci_name, printer, buf));
		}
	}	break;

	case CTYPE_KIND_STRUCT: {
		bool do_multiline;
		union {
			struct ctype_printstruct_ismultiline_data im;
			struct ctype_printstruct_data ps;
		} data;
		unsigned int inner_flags;
		if (!(flags & CTYPE_PRINTVALUE_FLAG_NOSPECSTRUCT)) {
			/* Special handling for structs that have custom representations (like `int128_t'). */
			dbx_errno_t error;
			error = print_special_struct(self, printer, buf, &temp, flags);
			if (error != DBX_ENOENT) {
				if unlikely(error == DBX_EFAULT)
					goto err_segfault;
				if (error == DBX_EOK) {
					if unlikely(temp < 0)
						goto err;
					result += temp;
					break;
				}
				/* NOTE: No other error codes are documented, but try
				 *       to  be fail-safe since we're the debugger ;) */
			}
		}

		inner_flags = flags;
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
		PRINT("{");
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
		++firstline_indent; /* Account for the leading '{' */
		if (flags & CTYPE_PRINTVALUE_FLAG_NORECURSION)
			goto do_print_no_recursion_dots_and_rbrace;
		/* First pass: Figure out if we want multi-line mode. */
		if (flags & CTYPE_PRINTVALUE_FLAG_ONELINE) {
			do_multiline = false;
		} else if (flags & CTYPE_PRINTVALUE_FLAG_NOSHORTLINES) {
			/* Check  if the struct has 0 fields. It this is the
			 * case, then don't print anything and continue with
			 * the closing '}' */
			if (ctype_struct_enumfields(me, &ctype_struct_is_nonempty_callback, NULL) == 0)
				goto done_struct;
			do_multiline = true;
		} else {
			data.im.buf              = buf;
			data.im.flags            = flags;
			data.im.inner_flags      = inner_flags;
			data.im.firstline_indent = firstline_indent;
			data.im.newline_indent   = newline_indent;
			data.im.newline_tab      = newline_tab;
			data.im.maxlinelen       = maxlinelen;
			data.im.out_field_count  = 0;
			data.im.out_contains_lf  = false;
			/* Enumerate fields for the initial pass. */
			ctype_struct_enumfields(me, &ctype_printstruct_ismultiline_callback, &data.im);
			if (!data.im.out_field_count)
				goto done_struct; /* Empty struct... */
			do_multiline = data.im.out_contains_lf;
			if (!do_multiline) {
				/* Check if the output fits into a single line. */
				/* NOTE: +1 for the trailing '}' that is always required. */
				if ((data.im.firstline_indent + 1) > data.im.maxlinelen) {
					/* Nope... */
					do_multiline = true;
					/* Check if we're allowed to omit the names of fields */
					if (data.im.out_field_count <= 2 &&
					    !(flags & (CTYPE_PRINTVALUE_FLAG_NOSTRUCTFIELDS |
					               CTYPE_PRINTVALUE_FLAG_NOOMITSHORTFIELDS))) {
						/* We're allowed to omit field names, so try to do that
						 * in order  to  fit  everything onto  a  single  line. */
						data.im.flags = flags | CTYPE_PRINTVALUE_FLAG_NOSTRUCTFIELDS;
						data.im.firstline_indent = firstline_indent;
						data.im.out_field_count  = 0;
						data.im.out_contains_lf  = false;
						ctype_struct_enumfields(me, &ctype_printstruct_ismultiline_callback, &data.im);
						/* NOTE: +1 for the trailing '}' that is always required. */
						if (!data.im.out_contains_lf && (data.im.firstline_indent + 1) <= maxlinelen) {
							/* Omit struct field names to save on space, which  in
							 * turn allows us to keep everything on a single line. */
							flags |= CTYPE_PRINTVALUE_FLAG_NOSTRUCTFIELDS;
							do_multiline = false;
						}
					}
				}
			}
		}
		if (do_multiline) {
			PRINT("\n");
			newline_indent += newline_tab;
			REPEAT(' ', newline_indent); /* Print leading spaces. */
			firstline_indent = newline_indent;
		}
		/* Actually print the struct proper. */
		data.ps.printer          = printer;
		data.ps.buf              = buf;
		data.ps.flags            = flags;
		data.ps.inner_flags      = inner_flags;
		data.ps.firstline_indent = firstline_indent;
		data.ps.newline_indent   = newline_indent;
		data.ps.newline_tab      = newline_tab;
		data.ps.maxlinelen       = maxlinelen;
		data.ps.out_field_count  = 0;
		data.ps.do_multiline     = do_multiline;
		DO(ctype_struct_enumfields(me, &ctype_printstruct_callback, &data.ps));
		if (do_multiline) {
			PRINT("\n");
			newline_indent -= newline_tab;
			REPEAT(' ', newline_indent); /* Print leading spaces. */
			/*firstline_indent = newline_indent;*/
		}
done_struct:
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX);
		PRINT("}");
		FORMAT(DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX);
		/* Also include obnote hints for `struct'-style objects. */
		if (!(flags & CTYPE_PRINTVALUE_FLAG_NONAMEDPOINTER) && ADDR_ISKERN(buf))
			DO(print_named_struct(me, printer, buf));
	}	break;

	case CTYPE_KIND_ARRAY: {
		size_t used_length, elem_size;
		unsigned int string_kind;
		used_length = me->ct_array.ca_count;
		string_kind = CSTRING_KIND_INVALID;
		/* Check if we can print this array as a string. */
		if (me->ct_array.ca_elem == &ctype_char) {
			/* Automatically derive length of a VLA */
			if (!used_length && !dbg_strlen(buf, &used_length))
				goto err_segfault;
			string_kind = CSTRING_KIND_NORMAL;
		} else if (me->ct_array.ca_elem == &ctype_char16_t) {
			if (!used_length && !dbg_strlen16(buf, &used_length))
				goto err_segfault;
			string_kind = CSTRING_KIND_CHAR16;
		} else if (me->ct_array.ca_elem == &ctype_char32_t) {
			if (!used_length && !dbg_strlen32(buf, &used_length))
				goto err_segfault;
			string_kind = CSTRING_KIND_CHAR32;
		}
		if (used_length) {
			/* Make sure that memory from `buf' doesn't fault. */
			byte_t b;
			if (dbg_readmemory(buf, &b, 1) != 0)
				goto err_segfault;
		}
		if (string_kind != CSTRING_KIND_INVALID) {
			size_t buflen = used_length;
			if (string_kind == CSTRING_KIND_CHAR32) {
				buflen *= 4;
			} else if (string_kind == CSTRING_KIND_CHAR16) {
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
do_print_no_recursion_dots_and_rbrace:
				FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_PREFIX);
				PRINT("...");
				FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_SUFFIX);
			} else {
				size_t i;
				bool do_multiline;
				struct ctyperef elem_type;
				firstline_indent += 1; /* Account for the leading '{' */
				bzero(&elem_type, sizeof(elem_type));
				elem_type.ct_flags = self->ct_flags;
				elem_type.ct_typ   = me->ct_array.ca_elem;
				elem_type.ct_info  = me->ct_array.ca_eleminfo;
				if (flags & CTYPE_PRINTVALUE_FLAG_ONELINE) {
					do_multiline = false;
				} else if (flags & CTYPE_PRINTVALUE_FLAG_NOSHORTLINES) {
					do_multiline = true;
				} else if (used_length <= 1) {
					/* No point; would just waste space! */
					do_multiline = false;
				} else {
					size_t peek_indent;
					peek_indent  = firstline_indent;
					do_multiline = false;
					/* Automatically determine if we need multi-line. */
					for (i = 0; i < used_length; ++i) {
						size_t index_hi;
						NCX byte_t const *elem_addr;
						elem_addr = (byte_t const *)buf + i * elem_size;
						index_hi  = i;
						if (!(flags & CTYPE_PRINTVALUE_FLAG_NOARRAYRANGE)) {
							/* Check ahead if upcoming elements are equal to our
							 * current element, and if they are, check if we can
							 * save  some screen space by compressing output via
							 * use of `[lo ... hi] = value',  instead of  having
							 * to use `value, value, value, ..., value, value' */
							while (index_hi + 1 < used_length) {
								NCX byte_t const *next_addr;
								next_addr = (byte_t const *)buf + (index_hi + 1) * elem_size;
								if (!dbg_eqmemory(elem_addr, next_addr, elem_size))
									break;
								++index_hi;
							}
							if (index_hi > i) {
								size_t range_length, range_prefix;
								size_t elem_length;
								range_prefix = COMPILER_STRLEN("[ ... ] = ");
								range_prefix += (size_t)snprintf(NULL, 0, "%" PRIuSIZ, i);
								range_prefix += (size_t)snprintf(NULL, 0, "%" PRIuSIZ, index_hi);
								elem_length = ctype_printvalue(&elem_type, &lenprinter, elem_addr,
								                               flags | CTYPE_PRINTVALUE_FLAG_ONELINE,
								                               0, 0, 0, (size_t)-1);
								range_length = range_prefix + elem_length; /* Account for the element */
								elem_length += 2;                          /* ", " */
								elem_length *= (index_hi - i) + 1;         /* Repeat */
								elem_length -= 2;                          /* Strip tailing ", " */
								if (elem_length <= range_length) {
									index_hi = i; /* Don't use a range-expression */
								} else {
									peek_indent += range_prefix;
								}
							}
						}
						peek_indent = ctype_printvalue_nextindent(&elem_type, elem_addr,
						                                          flags, peek_indent,
						                                          newline_indent, newline_tab,
						                                          maxlinelen, &do_multiline,
						                                          true);
						if (do_multiline)
							break;
						peek_indent += 1; /* ',' or '}' */
						if (index_hi < used_length - 1)
							peek_indent += 1; /* Space after ',' */
						if (peek_indent > maxlinelen) {
							do_multiline = true;
							break;
						}
						i = index_hi;
					}
				}
				if (do_multiline) {
					PRINT("\n");
					newline_indent += newline_tab;
					REPEAT(' ', newline_indent); /* Print leading spaces. */
					firstline_indent = newline_indent;
				}
				for (i = 0; i < used_length; ++i) {
					NCX byte_t const *elem_addr;
					size_t elem_indent = firstline_indent;
					size_t index_hi;
					elem_addr = (byte_t const *)buf + i * elem_size;
					index_hi  = i;
					if (i != 0)
						++elem_indent; /* For the leading space */
					if (!(flags & CTYPE_PRINTVALUE_FLAG_NOARRAYRANGE)) {
						/* Check ahead if upcoming elements are equal to our
						 * current element, and if they are, check if we can
						 * save  some screen space by compressing output via
						 * use of `[lo ... hi] = value',  instead of  having
						 * to use `value, value, value, ..., value, value' */
						while (index_hi + 1 < used_length) {
							NCX byte_t const *next_addr;
							next_addr = (byte_t const *)buf + (index_hi + 1) * elem_size;
							if (!dbg_eqmemory(elem_addr, next_addr, elem_size))
								break;
							++index_hi;
						}
						/* If we're supposed to print multiple elements, check if doing
						 * so can actually save space. */
						if (index_hi > i) {
							size_t range_length, range_prefix;
							size_t elem_length;
							range_prefix = COMPILER_STRLEN("[ ... ] = ");
							range_prefix += (size_t)snprintf(NULL, 0, "%" PRIuSIZ, i);
							range_prefix += (size_t)snprintf(NULL, 0, "%" PRIuSIZ, index_hi);
							elem_length = ctype_printvalue(&elem_type, &lenprinter, elem_addr,
							                               flags | CTYPE_PRINTVALUE_FLAG_ONELINE,
							                               0, 0, 0, (size_t)-1);
							range_length = range_prefix + elem_length; /* Account for the element */
							elem_length += 2;                          /* ", " */
							elem_length *= (index_hi - i) + 1;         /* Repeat */
							elem_length -= 2;                          /* Strip tailing ", " */
							if (elem_length <= range_length) {
								index_hi = i; /* Don't use a range-expression */
							} else {
								elem_indent += range_prefix;
							}
						}
					}
					if (do_multiline) {
						bool contains_newline;
						/* Check if we must insert a new-line before this element. */
						contains_newline = false;
						firstline_indent = ctype_printvalue_nextindent(&elem_type, elem_addr,
						                                               flags, elem_indent,
						                                               newline_indent, newline_tab,
						                                               maxlinelen, &contains_newline,
						                                               false);
						if (index_hi < used_length - 1)
							firstline_indent += 1; /* For the trailing comma */
						if (i == 0) {
							/* Never print an additional linefeed before the first element. */
						} else if (!contains_newline && firstline_indent <= maxlinelen) {
							PRINT(" "); /* Add a space after the comma of the previous element. */
						} else {
							/* Insert a line-feed before the element. */
							PRINT("\n");
							REPEAT(' ', newline_indent); /* Print leading spaces. */
							elem_indent = newline_indent;
							if (i < index_hi) {
								/* Account for the indent from the prefix. */
								elem_indent += COMPILER_STRLEN("[ ... ] = ");
								elem_indent += (size_t)snprintf(NULL, 0, "%" PRIuSIZ, i);
								elem_indent += (size_t)snprintf(NULL, 0, "%" PRIuSIZ, index_hi);
							}
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
						if (index_hi < used_length - 1)
							firstline_indent += 1; /* For the trailing comma */
					}
					if (i < index_hi) {
						FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_PREFIX);
						PRINT("[");
						FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_SUFFIX);
						FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
						PRINTF("%" PRIuSIZ, i);
						FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
						FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_PREFIX);
						PRINT(" ... ");
						FORMAT(DEBUGINFO_PRINT_FORMAT_DOTS_SUFFIX);
						FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX);
						PRINTF("%" PRIuSIZ, index_hi);
						FORMAT(DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX);
						FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_PREFIX);
						PRINT("]");
						FORMAT(DEBUGINFO_PRINT_FORMAT_BRACKET_SUFFIX);
						FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_PREFIX);
						PRINT(" = ");
						FORMAT(DEBUGINFO_PRINT_FORMAT_ASSIGN_SUFFIX);
					}
					/* Recursively print the array element. */
					DO(ctype_printvalue(&elem_type, printer, elem_addr,
					                    flags, elem_indent,
					                    newline_indent, newline_tab,
					                    maxlinelen));
					if (index_hi < used_length - 1) {
						FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX);
						PRINT(",");
						FORMAT(DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX);
					}
					i = index_hi;
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

	case CTYPE_KIND_FUNCTION:
		result = print_function(self, printer,
		                        buf, flags,
		                        firstline_indent,
		                        newline_indent,
		                        newline_tab,
		                        maxlinelen);
		break;

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
				byte_t b;
				if (dbg_readmemory((byte_t const *)buf + i, &b, 1) != 0) {
					PRINT("??");
				} else {
					PRINTF("%.2" PRIX8, b);
				}
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
done:
	return result;
err:
	return temp;
err_segfault:
	FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_PREFIX);
	PRINT("<segfault>");
	FORMAT(DEBUGINFO_PRINT_FORMAT_ERROR_SUFFIX);
	goto done;
}




DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_CPRINTER_C */
