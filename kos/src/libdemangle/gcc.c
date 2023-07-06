/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBDEMANGLE_GCC_C
#define GUARD_LIBDEMANGLE_GCC_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <format-printer.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <libdemangle/api.h>
#include <libdemangle/gcc.h>

#include "gcc.h"

DECL_BEGIN

LOCAL void CC
itanium_print(struct itanium_printer *self,
              char const *__restrict str) {
	if (self && likely(self->ip_result >= 0)) {
		ssize_t temp;
		temp            = (*self->ip_printer)(self->ip_arg, str, strlen(str));
		self->ip_result = (likely(temp >= 0))
		                  ? self->ip_result + temp
		                  : temp;
	}
}
LOCAL void CC
itanium_printn(struct itanium_printer *self,
               char const *__restrict str, size_t len) {
	if (self && likely(self->ip_result >= 0)) {
		ssize_t temp;
		temp            = (*self->ip_printer)(self->ip_arg, str, len);
		self->ip_result = (likely(temp >= 0))
		                  ? self->ip_result + temp
		                  : temp;
	}
}
LOCAL void CC
itanium_vprintf(struct itanium_printer *self,
                char const *__restrict format,
                va_list args) {
	if (self && likely(self->ip_result >= 0)) {
		ssize_t temp;
		temp = format_vprintf(self->ip_printer,
		                      self->ip_arg,
		                      format,
		                      args);
		self->ip_result = (likely(temp >= 0))
		                  ? self->ip_result + temp
		                  : temp;
	}
}

LOCAL void
itanium_printf(struct itanium_printer *self,
               char const *__restrict format,
               ...) {
	va_list args;
	va_start(args, format);
	itanium_vprintf(self, format, args);
	va_end(args);
}

PRIVATE char const *CC
itanium_demangle_number(char const *__restrict text,
                        ssize_t *presult) {
	bool neg = false;
	if (text[0] == 'n') {
		neg = true;
		++text;
	}
	if (text[0] >= '0' && text[0] <= '9') {
		size_t temp;
		temp = (size_t)(text[0] - '0');
		++text;
		if (temp)
			for (;;) {
				char ch = text[0];
				if (ch < '0' || ch > '9')
					break;
				temp *= 10;
				temp += ch - '0';
				++text;
			}
		if (presult) {
			*presult = neg
			           ? -(ssize_t)temp
			           : (ssize_t)temp;
		}
	} else {
		text = NULL;
	}
	return text;
}

PRIVATE char const *CC
itanium_demangle_unsigned_number(char const *__restrict text,
                                 size_t *presult) {
	if (text[0] >= '0' && text[0] <= '9') {
		size_t temp;
		temp = (size_t)(text[0] - '0');
		++text;
		if (temp)
			for (;;) {
				char ch = text[0];
				if (ch < '0' || ch > '9')
					break;
				temp *= 10;
				temp += ch - '0';
				++text;
			}
		if (presult)
			*presult = temp;
	} else {
		text = NULL;
	}
	return text;
}


PRIVATE char const *CC itanium_demangle_type(struct itanium_printer *self, char const *__restrict text);
PRIVATE char const *CC itanium_demangle_unqualified_name(struct itanium_printer *self, char const *__restrict text);
PRIVATE char const *CC itanium_demangle_prefix(struct itanium_printer *self, char const *__restrict text);
PRIVATE char const *CC itanium_demangle_template_prefix(struct itanium_printer *self, char const *__restrict text);
PRIVATE char const *CC itanium_demangle_template_args(struct itanium_printer *self, char const *__restrict text);
PRIVATE char const *CC itanium_demangle_template_arg(struct itanium_printer *self, char const *__restrict text);
PRIVATE char const *CC itanium_demangle_name(struct itanium_printer *self, char const *__restrict text);
PRIVATE char const *CC itanium_demangle_expression(struct itanium_printer *self, char const *__restrict text);
PRIVATE char const *CC itanium_demangle_expr_primary(struct itanium_printer *self, char const *__restrict text);
PRIVATE char const *CC itanium_demangle_encoding(struct itanium_printer *self, char const *__restrict text);



PRIVATE char const *CC
itanium_demangle_source_name(struct itanium_printer *self,
                             char const *__restrict text) {
	size_t length;
	text = itanium_demangle_unsigned_number(text, &length);
	if unlikely(!text)
		goto err;
	if unlikely(length > strnlen(text, length))
		goto err;
	itanium_printn(self, text, length);
	text += length;
	return text;
err:
	return NULL;
}

PRIVATE char const *CC
itanium_demangle_unqualified_name(struct itanium_printer *self,
                                  char const *__restrict text) {
	/* ```
	 * <unqualified-name> ::= <operator-name> [<abi-tags>]
	 *                    ::= <ctor-dtor-name>
	 *                    ::= <source-name>
	 *                    ::= <unnamed-type-name>
	 *                    ::= DC <source-name>+ E      # structured binding declaration
	 * ``` */
	switch (text[0]) {

	case 'a':
		/* ```
		 * N        # &=
		 * S        # =
		 * a        # &&
		 * d        # & (unary)
		 * n        # &
		 * ``` */
		switch (text[1]) {
		case 'N':
			text += 2;
			itanium_print(self, "operator &=");
			break;
		case 'S':
			text += 2;
			itanium_print(self, "operator =");
			break;
		case 'a':
			text += 2;
			itanium_print(self, "operator &&");
			break;
		case 'd':
			text += 2;
			itanium_print(self, "operator & /*ref*/");
			break;
		case 'n':
			text += 2;
			itanium_print(self, "operator & /*and*/");
			break;
		default: goto err;
		}
check_abi_tags:
		if (text[0] == 'B') {
			++text;
			itanium_print(self, "[[gnu::abi_tag(\"");
			for (;;) {
				//source-name;
				text = itanium_demangle_source_name(self, text);
				if unlikely(!text)
					goto err;
				if (*text != 'B')
					break;
				itanium_print(self, "\",\"");
			}
			itanium_print(self, "\")]]");
		}
		break;
	case 'c':
		/* ```
		 * l        # ()
		 * m        # ,
		 * o        # ~
		 * v <type> # (cast)
		 * ``` */
		switch (text[1]) {
		case 'l':
			text += 2;
			itanium_print(self, "operator ()");
			break;
		case 'm':
			text += 2;
			itanium_print(self, "operator ,");
			break;
		case 'o':
			text += 2;
			itanium_print(self, "operator ~");
			break;
		case 'v':
			text += 2;
			itanium_print(self, "operator ");
			text = itanium_demangle_type(self, text);
			break;
		default: goto err;
		}
		goto check_abi_tags;

	case 'd':
		/* ```
		 * V        # /=
		 * a        # delete[]
		 * e        # * (unary)
		 * l        # delete
		 * v        # /
		 * ``` */
		switch (text[1]) {
		case 'V':
			text += 2;
			itanium_print(self, "operator /=");
			break;
		case 'a':
			text += 2;
			itanium_print(self, "operator delete[]");
			break;
		case 'e':
			text += 2;
			itanium_print(self, "operator * /*ind*/");
			break;
		case 'l':
			text += 2;
			itanium_print(self, "operator delete");
			break;
		case 'v':
			text += 2;
			itanium_print(self, "operator /");
			break;
		default: goto err;
		}
		goto check_abi_tags;

	case 'e':
		/* ```
		 * O        # ^=
		 * o        # ^
		 * q        # ==
		 * ``` */
		switch (text[1]) {
		case 'O':
			text += 2;
			itanium_print(self, "operator ^=");
			break;
		case 'o':
			text += 2;
			itanium_print(self, "operator ^");
			break;
		case 'q':
			text += 2;
			itanium_print(self, "operator ==");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'g':
		/* ```
		 * e        # >=
		 * t        # >
		 * ``` */
		switch (text[1]) {
		case 'e':
			text += 2;
			itanium_print(self, "operator >=");
			break;
		case 't':
			text += 2;
			itanium_print(self, "operator >");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'i':
		/* ```
		 * x        # []
		 * ``` */
		switch (text[1]) {
		case 'x':
			text += 2;
			itanium_print(self, "operator []");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'l':
		/* ```
		 * S        # <<=
		 * e        # <=
		 * i <source-name>          # operator ""
		 * s        # <<
		 * t        # <
		 * ``` */
		switch (text[1]) {
		case 'S':
			text += 2;
			itanium_print(self, "operator <<=");
			break;
		case 'e':
			text += 2;
			itanium_print(self, "operator <=");
			break;
		case 'i':
			text += 2;
			itanium_print(self, "operator ");
			text = itanium_demangle_source_name(self, text);
			itanium_print(self, "\"\"");
			break;
		case 's':
			text += 2;
			itanium_print(self, "operator <<");
			break;
		case 't':
			text += 2;
			itanium_print(self, "operator <");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'm':
		/* ```
		 * I        # -=
		 * L        # *=
		 * i        # -
		 * l        # *
		 * m        # -- (postfix in <expression> context)
		 * ``` */
		switch (text[1]) {
		case 'I':
			text += 2;
			itanium_print(self, "operator -=");
			break;
		case 'L':
			text += 2;
			itanium_print(self, "operator *=");
			break;
		case 'i':
			text += 2;
			itanium_print(self, "operator -");
			break;
		case 'l':
			text += 2;
			itanium_print(self, "operator *");
			break;
		case 'm':
			text += 2;
			itanium_print(self, "operator --");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'n':
		/* ```
		 * a        # new[]
		 * e        # !=
		 * g        # - (unary)
		 * t        # !
		 * w        # new
		 * ``` */
		switch (text[1]) {
		case 'a':
			text += 2;
			itanium_print(self, "operator new[]");
			break;
		case 'e':
			text += 2;
			itanium_print(self, "operator !=");
			break;
		case 'g':
			text += 2;
			itanium_print(self, "operator - /*neg*/");
			break;
		case 't':
			text += 2;
			itanium_print(self, "operator !");
			break;
		case 'w':
			text += 2;
			itanium_print(self, "operator new");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'o':
		/* ```
		 * R        # |=
		 * o        # ||
		 * r        # |
		 * ``` */
		switch (text[1]) {
		case 'R':
			text += 2;
			itanium_print(self, "operator |=");
			break;
		case 'o':
			text += 2;
			itanium_print(self, "operator ||");
			break;
		case 'r':
			text += 2;
			itanium_print(self, "operator |");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'p':
		/* ```
		 * L        # +=
		 * l        # +
		 * m        # ->*
		 * p        # ++ (postfix in <expression> context)
		 * s        # + (unary)
		 * t        # ->
		 * ``` */
		switch (text[1]) {
		case 'L':
			text += 2;
			itanium_print(self, "operator +=");
			break;
		case 'l':
			text += 2;
			itanium_print(self, "operator +");
			break;
		case 'm':
			text += 2;
			itanium_print(self, "operator ->*");
			break;
		case 'p':
			text += 2;
			itanium_print(self, "operator ++");
			break;
		case 's':
			text += 2;
			itanium_print(self, "operator +");
			break;
		case 't':
			text += 2;
			itanium_print(self, "operator ->");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'q':
		/* ```
		 * u        # ?
		 * ``` */
		switch (text[1]) {
		case 'u':
			text += 2;
			itanium_print(self, "operator ?");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'r':
		/* ```
		 * M        # %=
		 * S        # >>=
		 * m        # %
		 * s        # >>
		 * ``` */
		switch (text[1]) {
		case 'M':
			text += 2;
			itanium_print(self, "operator %=");
			break;
		case 'S':
			text += 2;
			itanium_print(self, "operator >>=");
			break;
		case 'm':
			text += 2;
			itanium_print(self, "operator %");
			break;
		case 's':
			text += 2;
			itanium_print(self, "operator >>");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 's':
		/* ```
		 * s        # <=>
		 * ``` */
		switch (text[1]) {
		case 's':
			text += 2;
			itanium_print(self, "operator <=>");
			break;
		default: goto err;
		}
		goto check_abi_tags;
	case 'v':
		/* ```
		 *  <digit> <source-name>   # vendor extended operator
		 * ``` */
		if (text[1] < '0' || text[1] > '9')
			goto err;
		text += 2;
		itanium_print(self, "operator ");
		text = itanium_demangle_source_name(self, text);
		goto check_abi_tags;

	case 'C':
		switch (text[1]) {
		case '1':
			text += 2;
			itanium_print(self, "<constructor>");
			break;
		case '2':
			text += 2;
			itanium_print(self, "<base-constructor>");
			break;
		case '3':
			text += 2;
			itanium_print(self, "<allocator>");
			break;
		default: goto err;
		}
		break;
	case 'D':
		switch (text[1]) {
		case '0':
			text += 2;
			itanium_print(self, "<delete>");
			break;
		case '1':
			text += 2;
			itanium_print(self, "<destructor>");
			break;
		case '2':
			text += 2;
			itanium_print(self, "<base-destructor>");
			break;
		case 'C':
			text += 2;
			itanium_print(self, "<bind(");
			text = itanium_demangle_source_name(self, text);
			if unlikely(!text)
				goto err;
			while (text[0] != 'E' && (!self || self->ip_result >= 0)) {
				itanium_print(self, ",");
				text = itanium_demangle_source_name(self, text);
				if unlikely(!text)
					goto err;
			}
			++text;
			itanium_print(self, ")>");
			break;
		default: goto err;
		}
		break;

	case 'U':
		/* ```
		 * <unnamed-type-name> ::= Ut [ <non-negative<number>> ] _
		 *                     ::= Ul <lambda-sig> E [ <non-negative<number>> ] _
		 * ``` */
		if (text[1] == 't') {
			text += 2;
			itanium_print(self, "<anonymous type>");
		} else if (text[1] == 'l') {
			text += 2;
			itanium_print(self, "<anonymous lambda");
			if (text[0] == 'v') {
				++text;
			} else {
				itanium_print(self, "(");
				text = itanium_demangle_type(self, text);
				if unlikely(!text)
					goto err;
				while (text[0] != 'E' && (!self || self->ip_result >= 0)) {
					itanium_print(self, ",");
					text = itanium_demangle_type(self, text);
					if unlikely(!text)
						goto err;
				}
				++text; /* 'E' */
				itanium_print(self, ")");
			}
			itanium_print(self, ">");
		} else
			goto err;
		if (text[0] != '_') {
			size_t num;
			text = itanium_demangle_unsigned_number(text, &num);
			if unlikely(!text || text[0] != '_')
				goto err;
			itanium_printf(self, " (discriminator %Iu)", num);
		}
		++text;
		break;

	default:
		text = itanium_demangle_source_name(self, text);
		break;
	}
	return text;
err:
	return NULL;
}


PRIVATE char const *CC
itanium_demangle_type(struct itanium_printer *self,
                      char const *__restrict text) {
	/* ```
	 * <type> ::= <builtin-type>
	 *        ::= [<extended-qualifier>*] [<CV-qualifiers>] <type>                                         # <qualified-type>
	 *        ::= [<CV-qualifiers>] [<exception-spec>] [Dx] F [Y] <bare-function-type> [<ref-qualifier>] E # <function-type>
	 *        ::= <class-enum-type>
	 *        ::= <array-type>
	 *        ::= M <class<type>> <member<type>>  # <pointer-to-member-type>
	 *        ::= <template-param>
	 *        ::= <template-template-param> <template-args>
	 *        ::= <decltype>
	 *        ::= P <type>        # pointer
	 *        ::= R <type>        # l-value reference
	 *        ::= O <type>        # r-value reference (C++11)
	 *        ::= C <type>        # complex pair (C99)
	 *        ::= G <type>        # imaginary (C99)
	 *        ::= Dp <type>       # pack expansion (C++0x)
	 *        ::= <substitution>  # See Compression below
	 * ``` */
	switch (text[0]) {

	case 'v':
		text += 1;
		itanium_print(self, "void");
		break; /* # void */
	case 'w':
		text += 1;
		itanium_print(self, "wchar_t");
		break; /* # wchar_t */
	case 'b':
		text += 1;
		itanium_print(self, "bool");
		break; /* # bool */
	case 'c':
		text += 1;
		itanium_print(self, "char");
		break; /* # char */
	case 'a':
		text += 1;
		itanium_print(self, "signed char");
		break; /* # signed char */
	case 'h':
		text += 1;
		itanium_print(self, "unsigned char");
		break; /* # unsigned char */
	case 's':
		text += 1;
		itanium_print(self, "short");
		break; /* # short */
	case 't':
		text += 1;
		itanium_print(self, "unsigned short");
		break; /* # unsigned short */
	case 'i':
		text += 1;
		itanium_print(self, "int");
		break; /* # int */
	case 'j':
		text += 1;
		itanium_print(self, "unsigned int");
		break; /* # unsigned int */
	case 'l':
		text += 1;
		itanium_print(self, "long");
		break; /* # long */
	case 'm':
		text += 1;
		itanium_print(self, "unsigned long");
		break; /* # unsigned long */
	case 'x':
		text += 1;
		itanium_print(self, "long long");
		break; /* # long long, __int64 */
	case 'y':
		text += 1;
		itanium_print(self, "unsigned long long");
		break; /* # unsigned long long, __int64 */
	case 'n':
		text += 1;
		itanium_print(self, "__int128");
		break; /* # __int128 */
	case 'o':
		text += 1;
		itanium_print(self, "unsigned __int128");
		break; /* # unsigned __int128 */
	case 'f':
		text += 1;
		itanium_print(self, "float");
		break; /* # float */
	case 'd':
		text += 1;
		itanium_print(self, "double");
		break; /* # double */
	case 'e':
		text += 1;
		itanium_print(self, "long double");
		break; /* # long double, __float80 */
	case 'g':
		text += 1;
		itanium_print(self, "__float128");
		break; /* # __float128 */
	case 'z':
		text += 1;
		itanium_print(self, "<ellipsis>");
		break; /* # ellipsis */
	case 'D':
		/* ```
		 * d # IEEE 754r decimal floating point (64 bits)
		 * e # IEEE 754r decimal floating point (128 bits)
		 * f # IEEE 754r decimal floating point (32 bits)
		 * h # IEEE 754r half-precision floating point (16 bits)
		 * F <number> _ # ISO/IEC TS 18661 binary floating point type _FloatN (N bits)
		 * i # char32_t
		 * s # char16_t
		 * a # auto
		 * c # decltype(auto)
		 * n # std::nullptr_t (i.e., decltype(nullptr))
		 * ``` */
		switch (text[1]) {

		case 'd':
			text += 2;
			itanium_print(self, "decimal64");
			break;

		case 'e':
			text += 2;
			itanium_print(self, "decimal128");
			break;

		case 'f':
			text += 2;
			itanium_print(self, "decimal32");
			break;

		case 'h':
			text += 2;
			itanium_print(self, "decimal16");
			break;

		case 'F':
			text += 2;
			{
				size_t count;
				text = itanium_demangle_unsigned_number(text, &count);
				if unlikely(!text)
					goto err;
				itanium_printf(self, "decimal%Iu", count);
			}
			break;

		case 'i':
			text += 2;
			itanium_print(self, "char32_t");
			break;

		case 's':
			text += 2;
			itanium_print(self, "char16_t");
			break;

		case 'a':
			text += 2;
			itanium_print(self, "auto");
			break;

		case 'c':
			text += 2;
			itanium_print(self, "decltype(auto)");
			break;

		case 'n':
			text += 2;
			itanium_print(self, "std::nullptr_t");
			break;

		case 'o':
			text = itanium_demangle_type(self, text + 2);
			if unlikely(!text)
				goto err;
			itanium_print(self, " noexcept");
			break;

		case 'x':
			text = itanium_demangle_type(self, text + 2);
			if unlikely(!text)
				goto err;
			itanium_print(self, " transaction_safe");
			break;

		case 'p':
			text = itanium_demangle_type(self, text + 1);
			if unlikely(!text)
				goto err;
			itanium_print(self, "...");
			break;

		case 'O': {
			char const *expr_start;
			text += 2;
			expr_start = text;
			text       = itanium_demangle_expression(NULL, text);
			if unlikely(!text || *text != 'E')
				goto err;
			++text;
			text = itanium_demangle_type(self, text + 2);
			if unlikely(!text)
				goto err;
			itanium_print(self, " noexcept(");
			if unlikely(!itanium_demangle_expression(self, expr_start))
				goto err;
			itanium_print(self, ")");
		}	break;

		case 'w': {
			char const *types_start;
			text += 2;
			types_start = text;
			do {
				text = itanium_demangle_type(NULL, text);
				if unlikely(!text)
					goto err;
			} while (*text != 'E');
			++text;
			text = itanium_demangle_type(self, text);
			if unlikely(!text)
				goto err;
			itanium_print(self, " throw(");
			do {
				types_start = itanium_demangle_type(NULL, types_start);
				if unlikely(!types_start)
					goto err;
			} while (*types_start != 'E');
			itanium_print(self, ")");
		}	break;

		default: goto err;
		}
		break;

	case 'u':
		/* ```
		 *  <source-name>        # vendor extended type
		 * ``` */
		++text;
		text = itanium_demangle_source_name(self, text);
		break;

	case 'U': {
		/* ```
		 * <extended-qualifier> ::= U <source-name> [<template-args>] # vendor extended type qualifier
		 * ``` */
		char const *name_start;
		char const *template_args_start;
		++text;
		name_start = text;
		text       = itanium_demangle_source_name(NULL, text);
		if unlikely(!text)
			goto err;
		template_args_start = itanium_demangle_template_args(NULL, text);
		if (template_args_start) {
			char const *temp    = text;
			text                = template_args_start;
			template_args_start = temp;
		}
		text = itanium_demangle_type(self, text);
		if unlikely(!text)
			goto err;
		itanium_print(self, " ");
		if unlikely(!itanium_demangle_source_name(self, name_start))
			goto err;
		if (template_args_start &&
		    unlikely(!itanium_demangle_template_args(self, template_args_start)))
			goto err;
	}	break;

	{
		char const *qual;
		/* ```
		 * <CV-qualifiers>      ::= [r] [V] [K]                       # restrict (C99), volatile, const
		 * ``` */
		__IF0 { case 'r': qual = " restrict"; }
		__IF0 { case 'V': qual = " volatile"; }
		__IF0 { case 'K': qual = " const"; }
		text = itanium_demangle_type(self, text + 1);
		if unlikely(!text)
			goto err;
		itanium_print(self, qual);
	}	break;

	case 'F':
		/* ```
		 * F [Y] <bare-function-type> [<ref-qualifier>] E # <function-type>
		 * ``` */
		++text;
		if (text[0] == 'Y') {
			itanium_print(self, "extern \"C\" ");
			++text;
		}
		text = itanium_demangle_type(self, text); /* return type */
		if unlikely(!text)
			goto err;
		itanium_print(self, "(");
		{
			bool is_first = true;
			while (*text != 'E' && *text != 'R' && *text != 'O') {
				if (!is_first)
					itanium_print(self, ",");
				is_first = false;
				text     = itanium_demangle_type(self, text); /* return type */
				if unlikely(!text)
					goto err;
			}
		}
		if (*text == 'R' || *text == 'O') {
			itanium_printn(self, " &&", *text == 'R' ? 2 : 3);
			++text;
			if unlikely(*text != 'E')
				goto err;
		}
		++text;
		itanium_print(self, ")");
		break;

	case 'T':
		switch (text[1]) {
		case 's':
			text += 2;
			itanium_print(self, "struct ");
			goto do_print_name;
		case 'u':
			text += 2;
			itanium_print(self, "union ");
			goto do_print_name;
		case 'e':
			text += 2;
			itanium_print(self, "enum ");
			goto do_print_name;
		default: goto err;
		}
		break;

	case 'P':
		text = itanium_demangle_type(self, text + 1);
		if unlikely(!text)
			goto err;
		itanium_print(self, " *");
		break;

	case 'R':
		text = itanium_demangle_type(self, text + 1);
		if unlikely(!text)
			goto err;
		itanium_print(self, " &");
		break;

	case 'O':
		text = itanium_demangle_type(self, text + 1);
		if unlikely(!text)
			goto err;
		itanium_print(self, " &&");
		break;

	case 'C':
		itanium_print(self, "complex ");
		text = itanium_demangle_type(self, text + 1);
		break;

	case 'G':
		itanium_print(self, "imaginary ");
		text = itanium_demangle_type(self, text + 1);
		break;

	case 'A':
		/* ```
		 * <array-type> ::= A <positive dimension<number>> _ <element<type>>
		 *              ::= A [<dimension expression>] _ <element<type>>
		 * ``` */
		++text;
		if (*text == '_') {
			text = itanium_demangle_type(self, text + 1);
			if unlikely(!text)
				goto err;
			itanium_print(self, "[]");
		} else {
			size_t length;
			char const *temp;
			temp = itanium_demangle_unsigned_number(text, &length);
			if (temp) {
				text = temp;
				if unlikely(*text != '_')
					goto err;
				++text;
				text = itanium_demangle_type(self, text);
				if unlikely(!text)
					goto err;
				itanium_printf(self, "[%Iu]", (size_t)length);
			} else {
				temp = text;
				text = itanium_demangle_expression(NULL, text);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				text = itanium_demangle_type(self, text);
				if unlikely(!text)
					goto err;
				itanium_printf(self, "[");
				if unlikely(!itanium_demangle_expression(self, temp))
					goto err;
				itanium_printf(self, "]");
			}
		}
		break;

	case 'M': {
		char const *temp;
		temp = text + 1;
		text = itanium_demangle_type(NULL, temp);
		if unlikely(!text)
			goto err;
		text = itanium_demangle_type(self, text);
		if unlikely(!text)
			goto err;
		itanium_print(self, " ");
		if unlikely(!itanium_demangle_type(self, temp))
			goto err;
		itanium_print(self, "::*");
	}	break;

	//TODO: <template-param>
	//TODO: <template-template-param> <template-args>
	//TODO: <decltype>
	//TODO: <substitution>

	default:
do_print_name:
		text = itanium_demangle_name(self, text);
		goto err;
	}
	return text;
err:
	return NULL;
}


PRIVATE char const *CC
itanium_demangle_prefix(struct itanium_printer *self,
                        char const *__restrict text) {
	/* TODO */
	(void)self;
	(void)text;
	return NULL;
}

PRIVATE char const *CC
itanium_demangle_template_prefix(struct itanium_printer *self,
                                 char const *__restrict text) {
	/* TODO */
	(void)self;
	(void)text;
	return NULL;
}

PRIVATE char const *CC
itanium_demangle_expression(struct itanium_printer *self,
                            char const *__restrict text) {
	/* TODO */
	(void)self;
	(void)text;
	return NULL;
}

PRIVATE char const *CC
itanium_demangle_expr_primary(struct itanium_printer *self,
                              char const *__restrict text) {
	/* TODO */
	(void)self;
	(void)text;
	return NULL;
}


PRIVATE char const *CC
itanium_demangle_template_args(struct itanium_printer *self,
                               char const *__restrict text) {
	/* ```
	 * <template-args> :: = I <template-arg>+ E
	 * ``` */
	if unlikely(text[0] != 'I')
		goto err;
	++text;
	itanium_print(self, "<");
	if (*text != 'E') {
		text = itanium_demangle_template_arg(self, text);
		if unlikely(!text)
			goto err;
		while (*text != 'E' && (!self || self->ip_result >= 0)) {
			itanium_print(self, ",");
			text = itanium_demangle_template_arg(self, text);
			if unlikely(!text)
				goto err;
		}
	}
	++text;
	itanium_print(self, ">");
	return text;
err:
	return NULL;
}


PRIVATE char const *CC
itanium_demangle_template_arg(struct itanium_printer *self,
                              char const *__restrict text) {
	/* ```
	 * <template-arg> ::= <type>                                             # type or template
	 *                ::= X <expression> E                                   # expression
	 *                ::= <expr-primary>                                     # simple expressions
	 *                ::= J <template-arg>* E                                # argument pack
	 * ``` */
	switch (*text) {

	case 'X':
		++text;
		text = itanium_demangle_expression(self, text);
		if unlikely(!text || text[0] != 'E')
			goto err;
		++text;
		break;

	case 'J':
		itanium_print(self, "[");
		++text;
		{
			bool is_first = true;
			while (*text != 'E' &&
			       (!self || self->ip_result >= 0)) {
				if (!is_first)
					itanium_print(self, ",");
				is_first = false;
				text     = itanium_demangle_template_arg(self, text);
				if unlikely(!text)
					goto err;
			}
		}
		++text;
		itanium_print(self, "]...");
		break;

	default: {
		char const *temp;
		temp = itanium_demangle_expr_primary(self, text);
		if (!temp)
			temp = itanium_demangle_type(self, text);
		text = temp;
	}	break;

	}
	return text;
err:
	return NULL;
}

PRIVATE char const *CC
itanium_demangle_name(struct itanium_printer *self,
                      char const *__restrict text) {
	/* ```
	 * <name> ::= <nested-name>
	 *        ::= <unscoped-name>
	 *        ::= <unscoped-template-name> <template-args>
	 *        ::= <local-name>          # See Scope Encoding below
	 *        ::= St <unqualified-name> # std::
	 * ``` */
again:
	switch (text[0]) {

	case 'S':
		if (text[1] == 't') {
			itanium_print(self, "std::");
			return itanium_demangle_unqualified_name(self, text + 2);
		}
		goto err;

	case 'N':
		/* ```
		 * <nested-name> ::= N [<CV-qualifiers>] [<ref-qualifier>] <prefix> <unqualified-name> E
		 *               ::= N [<CV-qualifiers>] [<ref-qualifier>] <template-prefix> <template-args> E
		 * <CV-qualifiers>      ::= [r] [V] [K]  # restrict (C99), volatile, const
		 * <ref-qualifier>      ::= R            # & ref-qualifier
		 *                      ::= O            # && ref-qualifier
		 * ``` */
		++text;
		if (*text == 'r') {
			itanium_print(self, "restrict ");
			++text;
		}
		if (*text == 'V') {
			itanium_print(self, "volatile ");
			++text;
		}
		if (*text == 'K') {
			itanium_print(self, "const ");
			++text;
		}
		if (*text == 'R') {
			itanium_print(self, "&");
			++text;
		} else if (*text == 'O') {
			itanium_print(self, "&&");
			++text;
		}
		if (itanium_demangle_prefix(NULL, text)) {
			text = itanium_demangle_prefix(self, text);
			if unlikely(!text)
				goto err;
			text = itanium_demangle_unqualified_name(self, text);
			if unlikely(!text || *text != 'E')
				goto err;
			++text;
		} else if (itanium_demangle_template_prefix(NULL, text)) {
			text = itanium_demangle_template_prefix(self, text);
			/* ```
			 * <template - args> :: = I <template-arg>+ E
			 * ``` */
			if unlikely(!text || text[0] != 'I')
				goto err;
			itanium_print(self, "<");
			++text;
			if (itanium_demangle_template_arg(NULL, text)) {
				text = itanium_demangle_template_arg(self, text);
				if unlikely(!text)
					goto err;
				while (itanium_demangle_template_arg(NULL, text) &&
				       (!self || self->ip_result >= 0)) {
					itanium_print(self, ",");
					text = itanium_demangle_template_arg(self, text);
					if unlikely(!text)
						goto err;
				}
			}
			if unlikely(!text || text[0] != 'E' || text[1] != 'E')
				goto err;
			text += 2;
			itanium_print(self, ">");
		} else {
			goto err;
		}
		break;

	case 'Z':
		/* ```
		 * <local-name> ::= Z <function<encoding>> E <entity<name>> [<discriminator>]
		 *              ::= Z <function<encoding>> E s [<discriminator>]
		 *              ::= Z <function<encoding>> Ed [ <parameter<number>> ] _ <entity<name>>
		 * ``` */
		++text;
		text = itanium_demangle_encoding(self, text);
		if unlikely(!text || *text != 'E')
			goto err;
		itanium_print(self, "::");
		++text;
		if (text[0] == 's') {
			itanium_print(self, "<anonymous>");
			goto check_discriminator;
		} else if (text[0] == 'd') {
			ssize_t num;
			char const *temp;
			itanium_print(self, "default");
			++text;
			temp = itanium_demangle_number(text, &num);
			if (temp) {
				itanium_printf(self, "[arg=%Id]", num);
				text = temp;
			}
			if unlikely(text[0] != '_')
				goto err;
			++text;
			itanium_print(self, "::");
			goto again;
		} else {
			text = itanium_demangle_name(self, text);
			if unlikely(!text)
				goto err;
			/* Check for a discriminator */
check_discriminator:
			/* ```
			 * <discriminator> ::= _ <non-negative<number>>      # when number < 10
			 *                 ::= __ <non-negative<number>> _   # when number >= 10
			 * ``` */
			if (text[0] == '_') {
				size_t num;
				++text;
				if (text[0] == '_') {
					text = itanium_demangle_unsigned_number(text, &num);
					if unlikely(!text || text[0] != '_')
						goto err;
					++text;
				} else if (text[0] >= '0' && text[0] <= '9') {
					num = text[0] - '0';
				} else {
					goto err;
				}
				itanium_printf(self, " (discriminator %Iu)", num);
			}
		}
		break;

	default:
		text = itanium_demangle_unqualified_name(self, text);
		break;
	}

	return text;
err:
	return NULL;
}

PRIVATE char const *CC
itanium_demangle_encoding(struct itanium_printer *self,
                          char const *__restrict text) {
	/* ```
	 * <encoding> ::= <function<name>> <bare-function-type>
	 *            ::= <data<name>>
	 *            ::= TV <type>        # virtual table
	 *            ::= TT <type>        # VTT structure (construction vtable index)
	 *            ::= TI <type>        # typeinfo structure
	 *            ::= TS <type>        # typeinfo name (null-terminated byte string)
	 *            ::= T <call-offset> <base<encoding>>           # base is the nominal target function of thunk
	 *            ::= Tc <call-offset> <call-offset> <base<encoding>>
	 *                                 # base is the nominal target function of thunk
	 *                                 # first call-offset is 'this' adjustment
	 *                                 # second call-offset is result adjustment
	 *            ::= GV <object<name>>  # Guard variable for one-time initialization
	 *                                   # No <type>
	 *            ::= GR <object<name>> _             # First temporary
	 *            ::= GR <object<name>> <seq-id> _    # Subsequent temporaries
	 *            ::= GTt <encoding>
	 * <call-offset> ::= h <nv-offset> _
	 *               ::= v <v-offset> _
	 * <nv-offset> ::= <offset<number>>                              # non-virtual base override
	 * <v-offset>  ::= <offset<number>> _ <virtual offset<number>>   # virtual base override, with vcall offset
	 * ``` */
again:
	if (text[0] == 'T') {
		switch (text[1]) {

		case 'V': /* Virtual table */
			itanium_print(self, "vtable for ");
			text = itanium_demangle_type(self, text + 2);
			break;

		case 'T': /* VTT structure (construction vtable index) */
			itanium_print(self, "VTT for ");
			text = itanium_demangle_type(self, text + 2);
			break;

		case 'I': /* typeinfo */
			itanium_print(self, "typeinfo for ");
			text = itanium_demangle_type(self, text + 2);
			break;

		case 'S': /* typeinfo name */
			itanium_print(self, "typeinfo name for ");
			text = itanium_demangle_type(self, text + 2);
			break;

		case 'h':
			text += 2;
			{
				ssize_t nv_offset;
				text = itanium_demangle_number(text, &nv_offset);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				itanium_printf(self, "thunk [this%+Id] for ", nv_offset);
			}
			goto again;

		case 'v':
			text += 2;
			{
				ssize_t offset;
				ssize_t v_offset;
				text = itanium_demangle_number(text, &offset);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				text = itanium_demangle_number(text, &v_offset);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				itanium_printf(self, "thunk [this%+Id:%+Id] for ", offset, v_offset);
			}
			goto again;

		case 'c':
			text += 2;
			if (*text == 'h') {
				ssize_t nv_offset;
				text = itanium_demangle_number(text, &nv_offset);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				itanium_printf(self, "thunk [this%+Id", nv_offset);
			} else if (*text == 'v') {
				ssize_t offset;
				ssize_t v_offset;
				text = itanium_demangle_number(text, &offset);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				text = itanium_demangle_number(text, &v_offset);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				itanium_printf(self, "thunk [this%+Id:%+Id", offset, v_offset);
			} else {
				goto err;
			}
			if (*text == 'h') {
				ssize_t nv_offset;
				text = itanium_demangle_number(text, &nv_offset);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				itanium_printf(self, ",result%+Id] for ", nv_offset);
			} else if (*text == 'v') {
				ssize_t offset;
				ssize_t v_offset;
				text = itanium_demangle_number(text, &offset);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				text = itanium_demangle_number(text, &v_offset);
				if unlikely(!text || *text != '_')
					goto err;
				++text;
				itanium_printf(self, ",result%+Id:%+Id] for ", offset, v_offset);
			} else {
				goto err;
			}
			goto again;

		default:
			goto err;
		}
	} else if (text[0] == 'G') {
		switch (text[1]) {

		case 'V':
			itanium_print(self, "guard for ");
			text = itanium_demangle_name(self, text + 2);
			break;

		case 'R':
			itanium_print(self, "temporary for ");
			text = itanium_demangle_name(self, text + 2);
			if unlikely(!text)
				goto err;
			{
				size_t num = 0;
				for (;;) {
					char ch;
					ch = *text++;
					if (ch == '_')
						break;
					num *= 36;
					if (ch >= '0' && ch <= '9') {
						num += ch - '0';
					} else if (ch >= 'A' && ch <= 'Z') {
						num += 10 + (ch - 'A');
					} else {
						goto err;
					}
				}
				if (num == 0) {
					itanium_print(self, " (1st)");
				} else if (num == 1) {
					itanium_print(self, " (2nd)");
				} else if (num == 2) {
					itanium_print(self, " (3rd)");
				} else {
					itanium_printf(self, " (%Iuth)", num + 1);
				}
			}
			break;

		case 'T':
			if (text[2] == 't') {
				itanium_print(self, "transaction safe ");
				text += 3;
				goto again;
			}
			goto err;

		default:
			goto err;
		}
	} else {
		/* ```
		 * <encoding> ::= <function<name>> <bare-function-type>
		 *            ::= <data<name>>
		 * ``` */
		text = itanium_demangle_name(self, text);
		if unlikely(!text)
			goto err;
		/* Check for function */
		if (*text == 'v') {
			/* void-function */
			itanium_print(self, "()");
			++text;
		} else if (itanium_demangle_type(NULL, text)) {
			itanium_print(self, "(");
			text = itanium_demangle_type(self, text);
			while (text && itanium_demangle_type(NULL, text) &&
			       (!self || self->ip_result >= 0)) {
				itanium_print(self, ",");
				text = itanium_demangle_type(self, text);
			}
			itanium_print(self, ")");
		}
	}
	return text;
err:
	return NULL;
}


INTERN ssize_t CC
libdm_demangle_gcc(pformatprinter printer, void *arg,
                   char const *__restrict text) {
	struct itanium_printer it;
	char const *result;
	it.ip_printer = printer;
	it.ip_arg     = arg;
	it.ip_result  = 0;
	if (text[0] == '_' && text[1] == 'Z')
		text += 2;
	result = itanium_demangle_encoding(&it, text);
	if (result && *result && *result != '.')
		result = NULL;
	if (unlikely(!result) && likely(it.ip_result == 0))
		it.ip_result = (*printer)(arg, text, strlen(text));
	return it.ip_result;
}

DEFINE_PUBLIC_ALIAS(demangle_gcc, libdm_demangle_gcc);

DECL_END

#endif /* !GUARD_LIBDEMANGLE_GCC_C */
