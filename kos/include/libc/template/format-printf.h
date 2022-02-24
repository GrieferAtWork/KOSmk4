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
#ifdef __INTELLISENSE__
#ifndef _FORMAT_PRINTER_H
#include <format-printer.h>
#endif /* !_FORMAT_PRINTER_H */
#include <hybrid/__alloca.h>
#include <hybrid/__assert.h>

#include <bits/crt/format-printer.h>
#include <bits/crt/uformat-printer.h>
#include <bits/types.h>
#include <parts/uchar/format-printer.h>

#include <string.h>
#include <unicode.h>

#include <libc/errno.h>
#include <libc/parts.uchar.string.h>
#include <libc/string.h>
#include <libc/template/itoa_digits.h>
#define __CHAR_TYPE                char
#define __CHAR_SIZE                __SIZEOF_CHAR__
#define __FORMAT_ESCAPE            format_escape
#define __FORMAT_ESCAPE16          format_c16escape
#define __FORMAT_ESCAPE32          format_c32escape
#define __FORMAT_REPEAT            format_repeat
#define __FORMAT_HEXDUMP           format_hexdump
#define __FORMAT_UNICODE_WRITECHAR unicode_writeutf8
#define __FORMAT_UNICODE_FORMAT16  format_16to8
#define __FORMAT_UNICODE_FORMAT32  format_32to8
#define __FORMAT_STRERROR          strerror
#define __FORMAT_WIDTH             format_width
#define __FORMAT_WIDTH16           format_c16width
#define __FORMAT_WIDTH32           format_c32width
#define __FORMAT_FORMAT            format
#define __FORMAT_PRINTER           printer
#define __FORMAT_ARG               arg
#define __FORMAT_ARGS              args
#endif /* __INTELLISENSE__ */

#include <hybrid/typecore.h>
#include <hybrid/__va_size.h>

#if __VA_SIZE >= 8
#   define __PRINTF_LENGTH_R64  0
#   define __PRINTF_LENGTH_R32  0
#   define __PRINTF_LENGTH_R16  0
#   define __PRINTF_LENGTH_R8   0
#elif __VA_SIZE >= 4
#   define __PRINTF_LENGTH_R64  1
#   define __PRINTF_LENGTH_R32  0
#   define __PRINTF_LENGTH_R16  0
#   define __PRINTF_LENGTH_R8   0
#elif __VA_SIZE >= 2
#   define __PRINTF_LENGTH_R64  2
#   define __PRINTF_LENGTH_R32  1
#   define __PRINTF_LENGTH_R16  0
#   define __PRINTF_LENGTH_R8   0
#elif __VA_SIZE >= 1
#   define __PRINTF_LENGTH_R64  3
#   define __PRINTF_LENGTH_R32  2
#   define __PRINTF_LENGTH_R16  1
#   define __PRINTF_LENGTH_R8   0
#else
#   error "Error: Unsupported `__VA_SIZE'"
#endif
#define __PRINTF_LENGTH_I64  (0x130|__PRINTF_LENGTH_R64)
#define __PRINTF_LENGTH_I32  (0x120|__PRINTF_LENGTH_R32)
#define __PRINTF_LENGTH_I16  (0x110|__PRINTF_LENGTH_R16)
#define __PRINTF_LENGTH_I8   (0x100|__PRINTF_LENGTH_R8)

#if __SIZEOF_WCHAR_T__ == 2
#define __PRINTF_LENGTH_L    (0x210|__PRINTF_LENGTH_R16)
#else /* __SIZEOF_WCHAR_T__ == 2 */
#define __PRINTF_LENGTH_L    (0x220|__PRINTF_LENGTH_R32)
#endif /* __SIZEOF_WCHAR_T__ != 2 */
#if __SIZEOF_SIZE_T__ == 4
#define __PRINTF_LENGTH_Z    (0x320|__PRINTF_LENGTH_R32)
#elif __SIZEOF_SIZE_T__ == 8
#define __PRINTF_LENGTH_Z    (0x330|__PRINTF_LENGTH_R64)
#elif __SIZEOF_SIZE_T__ == 2
#define __PRINTF_LENGTH_Z    (0x310|__PRINTF_LENGTH_R16)
#else
#define __PRINTF_LENGTH_Z    (0x300|__PRINTF_LENGTH_R8)
#endif
#if __SIZEOF_PTRDIFF_T__ == 4
#define __PRINTF_LENGTH_T    (0x420|__PRINTF_LENGTH_R32)
#elif __SIZEOF_PTRDIFF_T__ == 8
#define __PRINTF_LENGTH_T    (0x430|__PRINTF_LENGTH_R64)
#elif __SIZEOF_PTRDIFF_T__ == 2
#define __PRINTF_LENGTH_T    (0x410|__PRINTF_LENGTH_R16)
#else
#define __PRINTF_LENGTH_T    (0x400|__PRINTF_LENGTH_R8)
#endif
#define __PRINTF_LENGTH_J    __PRINTF_LENGTH_I64 /* intmax_t */
#define __PRINTF_LENGTH_SIZE __PP_CAT2(__PRINTF_LENGTH_I, __PP_MUL8(__SIZEOF_POINTER__))
#define __PRINTF_LENGTH_HH   __PP_CAT2(__PRINTF_LENGTH_I, __PP_MUL8(__SIZEOF_CHAR__))
#define __PRINTF_LENGTH_H    __PP_CAT2(__PRINTF_LENGTH_I, __PP_MUL8(__SIZEOF_SHORT__))
#ifdef __NO_PRINTF_UNICODE_STRING
#define __PRINTF_LENGTH_l    __PP_CAT2(__PRINTF_LENGTH_I, __PP_MUL8(__SIZEOF_LONG__))
#else /* __NO_PRINTF_UNICODE_STRING */
#define __PRINTF_LENGTH_l    (__PP_CAT2(__PRINTF_LENGTH_I, __PP_MUL8(__SIZEOF_LONG__)) | 0x1000)
#endif /* !__NO_PRINTF_UNICODE_STRING */
#ifdef __SIZEOF_LONG_LONG__
#define __PRINTF_LENGTH_LL   __PP_CAT2(__PRINTF_LENGTH_I, __PP_MUL8(__SIZEOF_LONG_LONG__))
#else /* __SIZEOF_LONG_LONG__ */
#define __PRINTF_LENGTH_LL   __PRINTF_LENGTH_I64
#endif /* !__SIZEOF_LONG_LONG__ */

#define __PRINTF_F_NONE     0x0000
#define __PRINTF_F_PREFIX   0x0001 /* `%#'. */
#define __PRINTF_F_UPPER    0x0002 /* Print upper-case hex-characters. */
#define __PRINTF_F_LJUST    0x0004 /* `%-'. */
#define __PRINTF_F_SIGN     0x0008 /* `%+'. */
#define __PRINTF_F_SPACE    0x0010 /* `% '. */
#define __PRINTF_F_PADZERO  0x0020 /* `%0'. */
#define __PRINTF_F_HASWIDTH 0x0040 /* `%123'. */
#define __PRINTF_F_HASPREC  0x0080 /* `%.123'. */
#define __PRINTF_F_SIGNED   0x0100
#define __PRINTF_F_FIXBUF   0x0200 /* `%$'. */
#define __PRINTF_F_UPPER2   0x0400 /* Print the `x' and `b' in `0x123' and `0b010' as uppercase. */


#ifndef __FORMAT_ESCAPE_FNORMAL
#define __FORMAT_ESCAPE_FNORMAL   0x0000 /* Normal quote flags. */
#define __FORMAT_ESCAPE_FPRINTRAW 0x0001 /* Don't surround the quoted text with "..."; */
#define __FORMAT_ESCAPE_FFORCEHEX 0x0002 /* Force hex encoding of all control characters without special strings (`"\n"', etc.). */
#define __FORMAT_ESCAPE_FFORCEOCT 0x0004 /* Force octal encoding of all non-ascii characters. */
#define __FORMAT_ESCAPE_FNOCTRL   0x0008 /* Disable special encoding strings such as `"\r"', `"\n"' or `"\e"' */
#define __FORMAT_ESCAPE_FNOASCII  0x0010 /* Disable regular ascii-characters and print everything using special encodings. */
#define __FORMAT_ESCAPE_FUPPERHEX 0x0020 /* Use uppercase characters for hex (e.g.: `"\xAB"'). */
#endif /* !__FORMAT_ESCAPE_FNORMAL */


#ifdef __INTELLISENSE__
extern "C" __SSIZE_TYPE__
format_vprintf(__pformatprinter __FORMAT_PRINTER,
               void *__FORMAT_ARG,
               __CHAR_TYPE const *__restrict __FORMAT_FORMAT,
               __builtin_va_list __FORMAT_ARGS)
#endif /* __INTELLISENSE__ */
{
#ifndef __NO_PRINTF_POSITIONAL
#ifndef __hybrid_alloca
#define __NO_PRINTF_POSITIONAL /* We need alloca for this one :( */
#endif /* !__hybrid_alloca */
#endif /* !__NO_PRINTF_POSITIONAL */
#ifndef __NO_PRINTF_POSITIONAL
	union __p_arg_union {
		void *__p_ptr;
		void (*__p_fun)(void);
		int __p_int;
		unsigned __p_unsigned;
		__uint8_t __p___uint8_t;
		__uint16_t __p___uint16_t;
		__uint32_t __p___uint32_t;
		__size_t __p___size_t;
		__ssize_t __p___ssize_t;
		__uint64_t __p___uint64_t;
#if (!defined(__NO_PRINTF_FLOATING_POINT) && !defined(__NO_FPU))
		double __p_double;
#ifdef __COMPILER_HAVE_LONGDOUBLE
		__LONGDOUBLE __p___LONGDOUBLE;
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_PRINTF_FLOATING_POINT && !__NO_FPU) */
	};
	union __p_arg_union *__p_args = __NULLPTR; /* [0..n] Vector of positional arguments */
	union __p_arg_union *__p_arg  = __NULLPTR; /* [0..1] Current positional argument */
#define __PRINTF_VARG(T)   (__p_arg ? __p_arg->__p_##T : __builtin_va_arg(__FORMAT_ARGS, T))
#define __PRINTF_VARGPTR() (__p_arg ? __p_arg->__p_ptr : __builtin_va_arg(__FORMAT_ARGS, void *))
#else /* !__NO_PRINTF_POSITIONAL */
#define __PRINTF_VARG(T)   __builtin_va_arg(__FORMAT_ARGS, T)
#define __PRINTF_VARGPTR() __builtin_va_arg(__FORMAT_ARGS, void *)
#endif /* __NO_PRINTF_POSITIONAL */
	__SSIZE_TYPE__ __temp, __result = 0;
	__size_t __width, __precision;
	__CHAR_TYPE const *__flush_start;
	__CHAR_TYPE __ch;
	unsigned int __flags;
	unsigned int __length;
	__flush_start = __FORMAT_FORMAT;
__next:
	__ch = *__FORMAT_FORMAT++;
	if __unlikely(!__ch)
		goto __end;
	if (__ch != '%')
		goto __next;
	if (__FORMAT_FORMAT - 1 != __flush_start) {
		__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __flush_start,
		                             (__size_t)((__FORMAT_FORMAT - 1) -
		                                             __flush_start));
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
	}
	__flush_start = __FORMAT_FORMAT;

	/* Format option. */
	__flags     = __PRINTF_F_NONE;
	__length    = 0;
	__width     = 0;
	__precision = 0;
__nextfmt:
	__ch = *__FORMAT_FORMAT++;
	switch (__ch) {

	case '%':
		__flush_start = __FORMAT_FORMAT-1;
		goto __next;

	case '\0':
		goto __end;
	case '-':
		__flags |= __PRINTF_F_LJUST;
		goto __nextfmt;
	case '+':
		__flags |= __PRINTF_F_SIGN;
		goto __nextfmt;
	case ' ':
		__flags |= __PRINTF_F_SPACE;
		goto __nextfmt;
	case '#':
		__flags |= __PRINTF_F_PREFIX;
		goto __nextfmt;
	case '0':
		__flags |= __PRINTF_F_PADZERO;
		goto __nextfmt;

#ifdef __NO_PRINTF_POSITIONAL
	case '?':
#if __SIZEOF_POINTER__ > __VA_SIZE
		__width = __PRINTF_VARG(__size_t);
		__flags |= __PRINTF_F_HASWIDTH;
		goto __nextfmt;
#endif /* __SIZEOF_POINTER__ > __VA_SIZE */
	case '*':
		__width = (__size_t)__PRINTF_VARG(unsigned);
		__flags |= __PRINTF_F_HASWIDTH;
		goto __nextfmt;

	case ':': /* Precision. */
		__flags |= __PRINTF_F_FIXBUF;
		__ATTR_FALLTHROUGH
	case '.': /* Precision. */
		__ch = *__FORMAT_FORMAT++;
#if __SIZEOF_POINTER__ > __VA_SIZE
		if (__ch == '*') {
			__precision = (__size_t)__PRINTF_VARG(unsigned);
		} else if (__ch == '?')
#else /* __SIZEOF_POINTER__ > __VA_SIZE */
		if (__ch == '*' || __ch == '?')
#endif /* __SIZEOF_POINTER__ <= __VA_SIZE */
		{
			__IF0 {
	case '$':
				__flags |= __PRINTF_F_FIXBUF;
			}
			__precision = __PRINTF_VARG(__size_t);
		} else if __likely(__ch >= '0' && __ch <= '9') {
			/* decimal-encoded __precision modifier. */
			__precision = (__size_t)(__ch - '0');
			while ((__ch = *__FORMAT_FORMAT, __ch >= '0' && __ch <= '9')) {
				__precision = __precision * 10 + (__size_t)(__ch - '0');
				++__FORMAT_FORMAT;
			}
		} else {
			goto __broken_format;
		}
		__flags |= __PRINTF_F_HASPREC;
		goto __nextfmt;
#else /* __NO_PRINTF_POSITIONAL */
	case ':':
		__flags |= __PRINTF_F_FIXBUF;
		__ATTR_FALLTHROUGH
	case '.':
		__ch = *__FORMAT_FORMAT++;
		if (__ch == '*' || __ch == '?') {
			__IF0 { case '$':  __flags |= __PRINTF_F_FIXBUF; } /* size_t precision */
			if (*__FORMAT_FORMAT >= '0' && *__FORMAT_FORMAT <= '9') {
				__size_t __posidx;
				__CHAR_TYPE __posch;
				if (!__p_args) {
					__FORMAT_FORMAT -= 2;
					goto __begin_positional_for_width_or_precision;
				}
				__posch = *__FORMAT_FORMAT++;
				__posidx = (__size_t)(__posch - '0');
				while ((__posch = *__FORMAT_FORMAT, __posch >= '0' && __posch <= '9')) {
					__posidx = __posidx * 10 + (__size_t)(__posch - '0');
					++__FORMAT_FORMAT;
				}
				if __unlikely(__posch != '$')
					goto __broken_format;
				++__FORMAT_FORMAT;
#if __SIZEOF_POINTER__ > __VA_SIZE
				if (__ch == '*') {
					__precision = (__size_t)__p_args[__posidx - 1].__p_unsigned;
				} else
#endif /* __SIZEOF_POINTER__ > __VA_SIZE */
				{
					__precision = __p_args[__posidx - 1].__p___size_t;
				}
			} else {
#if __SIZEOF_POINTER__ > __VA_SIZE
				if (__ch == '*') {
					__precision = (__size_t)__builtin_va_arg(__FORMAT_ARGS, unsigned);
				} else
#endif /* __SIZEOF_POINTER__ > __VA_SIZE */
				{
					__precision = __builtin_va_arg(__FORMAT_ARGS, __size_t);
				}
			}
		} else if __likely(__ch >= '0' && __ch <= '9') {
			/* decimal-encoded __precision modifier. */
			__precision = (__size_t)(__ch - '0');
			while ((__ch = *__FORMAT_FORMAT, __ch >= '0' && __ch <= '9')) {
				__precision = __precision * 10 + (__size_t)(__ch - '0');
				++__FORMAT_FORMAT;
			}
		} else {
			goto __broken_format;
		}
		__flags |= __PRINTF_F_HASPREC;
		goto __nextfmt;

	case '?':   /* size_t width */
	case '*': { /* unsigned int width */
		if (*__FORMAT_FORMAT >= '0' && *__FORMAT_FORMAT <= '9') {
			__size_t __posidx;
			__CHAR_TYPE __posch;
			if (!__p_args) {
				--__FORMAT_FORMAT;
				goto __begin_positional_for_width_or_precision;
			}
			__posch = *__FORMAT_FORMAT++;
			__posidx = (__size_t)(__posch - '0');
			while ((__posch = *__FORMAT_FORMAT, __posch >= '0' && __posch <= '9')) {
				__posidx = __posidx * 10 + (__size_t)(__posch - '0');
				++__FORMAT_FORMAT;
			}
			if __unlikely(__posch != '$')
				goto __broken_format;
			++__FORMAT_FORMAT;
#if __SIZEOF_POINTER__ > __VA_SIZE
			if (__ch == '*') {
				__width = (__size_t)__p_args[__posidx - 1].__p_unsigned;
			} else
#endif /* __SIZEOF_POINTER__ > __VA_SIZE */
			{
				__width = __p_args[__posidx - 1].__p___size_t;
			}
		} else {
#if __SIZEOF_POINTER__ > __VA_SIZE
			if (__ch == '*') {
				__width = (__size_t)__builtin_va_arg(__FORMAT_ARGS, unsigned);
			} else
#endif /* __SIZEOF_POINTER__ > __VA_SIZE */
			{
				__width = __builtin_va_arg(__FORMAT_ARGS, __size_t);
			}
		}
		__flags |= __PRINTF_F_HASWIDTH;
		goto __nextfmt;
	}	break;
#endif /* !__NO_PRINTF_POSITIONAL */

	case 'h':
		if (*__FORMAT_FORMAT != 'h')
			__length = __PRINTF_LENGTH_H;
		else {
			++__FORMAT_FORMAT;
			__length = __PRINTF_LENGTH_HH;
		}
		goto __nextfmt;

	case 'l':
		if (*__FORMAT_FORMAT != 'l')
			__length = __PRINTF_LENGTH_l;
		else {
			++__FORMAT_FORMAT;
			__length = __PRINTF_LENGTH_LL;
		}
		goto __nextfmt;

	case 'z':
		__length = __PRINTF_LENGTH_Z;
		goto __nextfmt;

	case 't':
		__length = __PRINTF_LENGTH_T;
		goto __nextfmt;

	case 'L':
		__length = __PRINTF_LENGTH_L;
		goto __nextfmt;

	case 'I':
		__ch = *__FORMAT_FORMAT++;
		if (__ch == '8')
			__length = __PRINTF_LENGTH_I8;
		else if (__ch == '1' && *__FORMAT_FORMAT == '6') {
			++__FORMAT_FORMAT;
			__length = __PRINTF_LENGTH_I16;
		} else if (__ch == '3' && *__FORMAT_FORMAT == '2') {
			++__FORMAT_FORMAT;
			__length = __PRINTF_LENGTH_I32;
		} else if (__ch == '6' && *__FORMAT_FORMAT == '4') {
			++__FORMAT_FORMAT;
	case 'j':
			__length = __PRINTF_LENGTH_I64;
		} else {
			--__FORMAT_FORMAT;
			__length = __PRINTF_LENGTH_SIZE;
		}
		goto __nextfmt;

	{
		unsigned int __numsys;
		__BOOL __is_neg;
		union {
#ifdef __UINT64_TYPE__
			__uint64_t __u;
			__int64_t __i;
#else /* __UINT64_TYPE__ */
			__uint32_t __u;
			__int32_t __i;
#endif /* !__UINT64_TYPE__ */
		} __data;
		__size_t __print_width, __space_width;
		__CHAR_TYPE *__iter, __buffer[67]; /* 64-bit binary, w/prefix + sign */
		__IF0 {
	case 'b':
			__numsys = 2;
		}
		__IF0 {
	case 'o':
			__numsys = 8;
		}
		__IF0 {
	case 'u':
			__numsys = 10;
			if __unlikely((__length & 0xf00) == 0x400) /* == __PRINTF_LENGTH_T */
				__flags |= __PRINTF_F_SIGNED;
		}
		__IF0 {
	case 'd':
	case 'i':
			__numsys = 10;
			if __likely((__length & 0xf00) != 0x300) /* != __PRINTF_LENGTH_Z */
				__flags |= __PRINTF_F_SIGNED;
		}
		__IF0 {
	case 'p':
			if (!__length)
				__length = __PRINTF_LENGTH_SIZE;
			if (!(__flags & __PRINTF_F_HASPREC)) {
				__precision = sizeof(void *) * 2;
#if __SIZEOF_POINTER__ != 8
				if ((__length & 0xf0) == 0x30)
					__precision = 16;
#endif /* __SIZEOF_POINTER__ != 8 */
#if __SIZEOF_POINTER__ != 4
				if ((__length & 0xf0) == 0x20)
					__precision = 8;
#endif /* __SIZEOF_POINTER__ != 4 */
#if __SIZEOF_POINTER__ != 2
				if ((__length & 0xf0) == 0x10)
					__precision = 4;
#endif /* __SIZEOF_POINTER__ != 2 */
				__flags |= __PRINTF_F_HASPREC;
			}
			__IF0 {
	case 'X':
				__flags |= __PRINTF_F_UPPER2;
			}
			__flags |= __PRINTF_F_UPPER;
			__ATTR_FALLTHROUGH
	case 'x':
			__numsys = 16;
			if __unlikely((__length & 0xf00) == 0x400) /* == __PRINTF_LENGTH_T */
				__flags |= __PRINTF_F_SIGNED;
		}
#ifdef __UINT64_TYPE__
#if __VA_SIZE < 2
		if __likely((__length & 0xf) == __PRINTF_LENGTH_R8) {
			__data.__u = (__UINT64_TYPE__)__PRINTF_VARG(__uint8_t);
			if (__flags & __PRINTF_F_SIGNED)
				__data.__i = (__INT64_TYPE__)(__int8_t)(__uint8_t)__data.__u;
		} else
#endif /* __VA_SIZE < 2 */
#if __VA_SIZE < 4
		if __likely((__length & 0xf) == __PRINTF_LENGTH_R16) {
			__data.__u = (__UINT64_TYPE__)__PRINTF_VARG(__uint16_t);
			if (__flags & __PRINTF_F_SIGNED)
				__data.__i = (__INT64_TYPE__)(__int16_t)(__uint16_t)__data.__u;
		} else
#endif /* __VA_SIZE < 4 */
#if __VA_SIZE < 8
		if __likely((__length & 0xf) == __PRINTF_LENGTH_R32) {
			__data.__u = (__UINT64_TYPE__)__PRINTF_VARG(__uint32_t);
			if (__flags & __PRINTF_F_SIGNED)
				__data.__i = (__INT64_TYPE__)(__int32_t)(__uint32_t)__data.__u;
		} else
#endif /* __VA_SIZE < 8 */
		{
			__data.__u = __PRINTF_VARG(__uint64_t);
		}
#else /* __UINT64_TYPE__ */
#if __VA_SIZE < 2
		if ((__length & 0xf) == __PRINTF_LENGTH_R8) {
			__data.__u = (__uint32_t)__PRINTF_VARG(__uint8_t);
			if (__flags & __PRINTF_F_SIGNED)
				__data.__i = (__int32_t)(__int8_t)(__uint8_t)__data.__u;
		} else
#endif /* __VA_SIZE < 2 */
#if __VA_SIZE < 4
		if ((__length & 0xf) == __PRINTF_LENGTH_R16) {
			__data.__u = (__uint32_t)__PRINTF_VARG(__uint16_t);
			if (__flags & __PRINTF_F_SIGNED)
				__data.__i = (__int32_t)(__int16_t)(__uint16_t)__data.__u;
		} else
#endif /* __VA_SIZE < 4 */
		{
			__data.__u = __PRINTF_VARG(__uint32_t);
		}
#endif /* !__UINT64_TYPE__ */
		__is_neg = 0;
		if ((__flags & __PRINTF_F_SIGNED) && __data.__i < 0) {
			__is_neg = 1;
			__data.__i = -__data.__i;
		}
		__iter = __COMPILER_ENDOF(__buffer);
		/* Actually translate the given input integer. */
		do {
			__hybrid_assert(__iter > __buffer);
			*--__iter = __LOCAL_itoa_digit(__flags & __PRINTF_F_UPPER, __data.__u % __numsys);
		} while ((__data.__u /= __numsys) != 0);
		__space_width = 0;
		__print_width = (__size_t)(__COMPILER_ENDOF(__buffer) - __iter);
		if ((__flags & __PRINTF_F_HASPREC) && __precision > __print_width)
			__print_width = __precision;
		if (__is_neg || (__flags & (__PRINTF_F_SIGN | __PRINTF_F_SPACE)))
			++__print_width;
		if ((__flags & __PRINTF_F_PREFIX) && __numsys != 10) {
			if (__numsys == 16 || __numsys == 2) {
				__print_width += 2;
			} else if (__numsys == 8 && __data.__u != 0) {
				__print_width += 1;
			}
		}
		if __unlikely((__flags & __PRINTF_F_HASWIDTH) && __width > __print_width) {
			__space_width = __width - __print_width;
			if (!(__flags & __PRINTF_F_LJUST)) {
				__CHAR_TYPE __padch = ' ';
				if (__flags & __PRINTF_F_PADZERO)
					__padch = '0';
				__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, __padch, __space_width);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				__space_width = 0;
			}
		}
		{
			__CHAR_TYPE __sign[3];
			__CHAR_TYPE *__dst = __sign;
			if (__is_neg)
				*__dst++ = '-';
			else if (__flags & __PRINTF_F_SIGN)
				*__dst++ = '+';
			else if (__flags & __PRINTF_F_SPACE)
				*__dst++ = ' ';
			if ((__flags & __PRINTF_F_PREFIX) && __numsys != 10) {
				if (__numsys == 16) {
					*__dst++ = '0';
					*__dst++ = __flags & __PRINTF_F_UPPER2 ? 'X' : 'x';
				} else if (__numsys == 2) {
					*__dst++ = '0';
					*__dst++ = __LOCAL_itoa_digit(__flags & __PRINTF_F_UPPER, 11); /* B/b */
				} else if (__numsys == 8 && __data.__u != 0) {
					*__dst++ = '0';
				}
			}
			if (__dst > __sign) {
				__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __sign, (__size_t)(__dst - __sign));
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
		}
		__print_width = (__size_t)(__COMPILER_ENDOF(__buffer) - __iter);
		if ((__flags & __PRINTF_F_HASPREC) && __precision > __print_width) {
			__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, '0', __precision - __print_width);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
		__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __iter, __print_width);
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
		if __unlikely(__space_width) {
			__CHAR_TYPE __padch = ' ';
			if (__flags & __PRINTF_F_PADZERO)
				__padch = '0';
			__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, __padch, __space_width);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
	}	break;

#ifndef __NO_PRINTF_ESCAPE
	case 'Q': /* Quote a single character */
		__ch = 'q';
		__ATTR_FALLTHROUGH
#endif /* !__NO_PRINTF_ESCAPE */
	case 'c': {
		__CHAR_TYPE const *__string;
		__size_t __string_length;
		__size_t __string_width;
#ifdef __NO_PRINTF_UNICODE_CHARS
		__CHAR_TYPE __given_char[1];
		__string_length = 1;
		__string        = __given_char;
		__given_char[0] = (__CHAR_TYPE)__PRINTF_VARG(int);
#else /* __NO_PRINTF_UNICODE_CHARS */
#if __CHAR_SIZE == __SIZEOF_CHAR__
		__CHAR_TYPE __given_char[7];
#elif __CHAR_SIZE == 2
		__CHAR_TYPE __given_char[2];
#else
		__CHAR_TYPE __given_char[1];
#endif
		__CHAR32_TYPE__ __ch32;
		/* `%c'    --> print ascii character */
		/* `%I16c' --> print utf-16 character (not surrogate support...) */
		/* `%I32c' --> print utf-32 character */
		/* `%lc'   --> print utf-16/32 character (same width as `wchar_t') */
		if (!__length)
			__ch32 = __PRINTF_VARG(unsigned) & 0x7f;
#if __VA_SIZE >= 4
		else {
			__ch32 = (__CHAR32_TYPE__)__PRINTF_VARG(__uint32_t);
		}
#elif __VA_SIZE >= 2
		else if __likely((__length & 0xf) == __PRINTF_LENGTH_R32)
			__ch32 = (__CHAR32_TYPE__)__PRINTF_VARG(__uint32_t);
		else {
			__ch32 = (__CHAR32_TYPE__)(__CHAR16_TYPE__)__PRINTF_VARG(__uint16_t);
		}
#else
		else if __likely((__length & 0xf) == __PRINTF_LENGTH_R32)
			__ch32 = (__CHAR32_TYPE__)__PRINTF_VARG(__uint32_t);
		else if __likely((__length & 0xf) == __PRINTF_LENGTH_R16)
			__ch32 = (__CHAR32_TYPE__)(__CHAR16_TYPE__)__PRINTF_VARG(__uint16_t);
		else {
			__ch32 = (__CHAR32_TYPE__)__PRINTF_VARG(__uint8_t);
		}
#endif
		__string = __given_char;
#if __CHAR_SIZE == 4
		__given_char[0] = __ch32;
		__string_length = 1;
#else /* __CHAR_SIZE == 4 */
		__string_length = (__size_t)(__FORMAT_UNICODE_WRITECHAR(__given_char, __ch32) - __given_char);
#endif /* __CHAR_SIZE != 4 */
#endif /* !__NO_PRINTF_UNICODE_CHARS */
		goto print_string;
#ifndef __NO_PRINTF_ESCAPE
	case 'q':
#if __PRINTF_F_PREFIX == __FORMAT_ESCAPE_FPRINTRAW
#define __FORMAT_ESCAPE_FLAGS __flags & __PRINTF_F_PREFIX
#else /* __PRINTF_F_PREFIX == __FORMAT_ESCAPE_FPRINTRAW */
#define __FORMAT_ESCAPE_FLAGS (__flags & __PRINTF_F_PREFIX ? __FORMAT_ESCAPE_FPRINTRAW : __FORMAT_ESCAPE_FNORMAL)
#endif /* __PRINTF_F_PREFIX != __FORMAT_ESCAPE_FPRINTRAW */
#endif /* !__NO_PRINTF_ESCAPE */
	case 's':
		__string = (__CHAR_TYPE *)__PRINTF_VARGPTR();
#if ((!defined(__NO_PRINTF_UNICODE_STRING) || __CHAR_SIZE == 1) &&   \
     !defined(__NO_PRINTF_STRERROR) && defined(__FORMAT_STRERROR) && \
     defined(__libc_geterrno))
		__IF0 {
	case 'm':
			__string = (__CHAR_TYPE const *)__FORMAT_STRERROR(__libc_geterrno());
#if __CHAR_SIZE != 1
			__length = __PRINTF_LENGTH_I8;
#endif /* __CHAR_SIZE != 1 */
		}
#endif /* ... */
#ifndef __NO_PRINTF_UNICODE_STRING
		/* Support for `%ls'   --> print wide-string */
		/* Support for `%I8s'  --> print utf-8 string */
		/* Support for `%I16s' --> print utf-16 string */
		/* Support for `%I32s' --> print utf-32 string */
		if ((__length & 0xf0) == 0x20) {
			/* utf-32 string */
#ifdef __FORMAT_WCSIZE
__do_utf32_string:;
#elif __SIZEOF_WCHAR_T__ == 4
__do_wchar:;
#endif /* ... */
#if __CHAR_SIZE != 4
			{
				static __uint32_t const __null_str32[] = { '(', 'n', 'u', 'l', 'l', ')', 0 };
#if __CHAR_SIZE == 2
				/* __FORMAT_UNICODE_FORMAT32: format_32to16 */
				struct /*format_32to16_data*/ {
					__pc16formatprinter __fd_printer; /* [1..1] Inner printer */
					void               *__fd_arg;     /* Argument for `fd_printer' */
				} __format_data;
				__format_data.__fd_printer = (__pc16formatprinter)__FORMAT_PRINTER;
#else /* __CHAR_SIZE == 2 */
				/* __FORMAT_UNICODE_FORMAT32: format_32to8 */
				struct /*format_32to8_data*/ {
					__pformatprinter __fd_printer; /* [1..1] Inner printer */
					void            *__fd_arg;     /* Argument for `fd_printer' */
				} __format_data;
				__format_data.__fd_printer = __FORMAT_PRINTER;
#endif /* __CHAR_SIZE != 2 */
				__format_data.__fd_arg = __FORMAT_ARG;
				if __unlikely(!__string)
					__string = (__CHAR_TYPE *)__null_str32;
				if (__flags & __PRINTF_F_FIXBUF)
					__string_length = __precision;
				else if (__flags & __PRINTF_F_HASPREC)
					__string_length = __libc_c32nlen((__CHAR32_TYPE__ const *)__string, __precision);
				else {
					__string_length = __libc_c32len((__CHAR32_TYPE__ const *)__string);
				}
				__string_width = __string_length;
				if (__width != 0) {
#ifndef __NO_PRINTF_ESCAPE
					if (__ch == 'q') {
						__string_width = (__size_t)__FORMAT_ESCAPE32(&__FORMAT_WIDTH32, __NULLPTR,
						                                             (__CHAR32_TYPE__ const *)__string,
						                                             __string_length,
						                                             __FORMAT_ESCAPE_FLAGS);
					} /*else*/
#endif /* !__NO_PRINTF_ESCAPE */
					/*{
						__string_width = __string_length;
					}*/
					if ((__width > __string_width) && !(__flags & __PRINTF_F_LJUST)) {
						__CHAR_TYPE __padch = ' ';
						if __unlikely(__flags & __PRINTF_F_PADZERO)
							__padch = '0';
						__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, __padch, __width - __string_width);
						if __unlikely(__temp < 0)
							goto __err;
						__result += __temp;
					}
				}
#ifndef __NO_PRINTF_ESCAPE
				if (__ch == 'q') {
					__temp = __FORMAT_ESCAPE32(&__FORMAT_UNICODE_FORMAT32, &__format_data,
					                           (__CHAR32_TYPE__ const *)__string, __string_length,
					                           __FORMAT_ESCAPE_FLAGS);
				} else
#endif /* !__NO_PRINTF_ESCAPE */
				{
					__temp = __FORMAT_UNICODE_FORMAT32(&__format_data,
					                                   (__CHAR32_TYPE__ const *)__string,
					                                   __string_length);
				}
			}
			goto __check_string_error_and_print_tail;
#endif /* __CHAR_SIZE != 4 */
		} else if ((__length & 0xf0) == 0x10) {
			/* utf-16 string */
#ifdef __FORMAT_WCSIZE
__do_utf16_string:;
#elif __SIZEOF_WCHAR_T__ == 2
__do_wchar:;
#endif /* ... */
#if __CHAR_SIZE != 2
			{
				static __uint16_t const __null_str16[] = { '(', 'n', 'u', 'l', 'l', ')', 0 };
#if __CHAR_SIZE == 4
				/* __FORMAT_UNICODE_FORMAT16: format_16to32 */
				struct /*format_16to32_data*/ {
					__pc32formatprinter __fd_printer;   /* [1..1] Inner printer */
					void               *__fd_arg;       /* Argument for `fd_printer' */
					__CHAR16_TYPE__     __fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
				} __format_data;
				__format_data.__fd_printer = (__pc32formatprinter)__FORMAT_PRINTER;
#else /* __CHAR_SIZE == 4 */
				/* __FORMAT_UNICODE_FORMAT16: format_16to8 */
				struct /*format_16to8_data*/ {
					__pformatprinter __fd_printer;   /* [1..1] Inner printer */
					void            *__fd_arg;       /* Argument for `fd_printer' */
					__CHAR16_TYPE__  __fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
				} __format_data;
				__format_data.__fd_printer = __FORMAT_PRINTER;
#endif /* __CHAR_SIZE != 4 */
				__format_data.__fd_arg       = __FORMAT_ARG;
				__format_data.__fd_surrogate = 0;
				if __unlikely(!__string)
					__string = (__CHAR_TYPE *)__null_str16;
				if (__flags & __PRINTF_F_FIXBUF)
					__string_length = __precision;
				else if (__flags & __PRINTF_F_HASPREC)
					__string_length = __libc_c16nlen((__CHAR16_TYPE__ const *)__string, __precision);
				else {
					__string_length = __libc_c16len((__CHAR16_TYPE__ const *)__string);
				}
				__string_width = __string_length;
				if (__width != 0) {
#ifndef __NO_PRINTF_ESCAPE
					if (__ch == 'q') {
						__string_width = (__size_t)__FORMAT_ESCAPE16(&__FORMAT_WIDTH16, __NULLPTR,
						                                             (__CHAR16_TYPE__ const *)__string,
						                                             __string_length,
						                                             __FORMAT_ESCAPE_FLAGS);
					} else
#endif /* !__NO_PRINTF_ESCAPE */
					{
						__string_width = (__size_t)__FORMAT_WIDTH16(__NULLPTR, (__CHAR16_TYPE__ const *)__string, __string_length);
					}
					if ((__width > __string_width) && !(__flags & __PRINTF_F_LJUST)) {
						__CHAR_TYPE __padch = ' ';
						if __unlikely(__flags & __PRINTF_F_PADZERO)
							__padch = '0';
						__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, __padch, __width - __string_width);
						if __unlikely(__temp < 0)
							goto __err;
						__result += __temp;
					}
				}
#ifndef __NO_PRINTF_ESCAPE
				if (__ch == 'q') {
					__temp = __FORMAT_ESCAPE16(&__FORMAT_UNICODE_FORMAT16, &__format_data,
					                           (__CHAR16_TYPE__ const *)__string, __string_length,
					                           __FORMAT_ESCAPE_FLAGS);
				} else
#endif /* !__NO_PRINTF_ESCAPE */
				{
					__temp = __FORMAT_UNICODE_FORMAT16(&__format_data,
					                                   (__CHAR16_TYPE__ const *)__string,
					                                   __string_length);
				}
			}
			goto __check_string_error_and_print_tail;
#endif /* __CHAR_SIZE != 2 */
		} else if ((__length & 0xf0) == 0x00) {
			/* utf-8 string */
#ifdef __FORMAT_WCSIZE
__do_utf8_string:;
#elif __SIZEOF_WCHAR_T__ == 1
__do_wchar:;
#endif /* ... */
#if __CHAR_SIZE != 1
			{
				static __uint8_t const __null_str8[] = { '(', 'n', 'u', 'l', 'l', ')', 0 };
#if __CHAR_SIZE == 4
				/* __FORMAT_UNICODE_FORMAT8: format_8to32 */
				struct /*format_8to32_data*/ {
					__pc32formatprinter __fd_printer;    /* [1..1] Inner printer */
					void               *__fd_arg;        /* Argument for `fd_printer' */
					__uint32_t     __fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
				} __format_data;
				__format_data.__fd_printer = (__pc32formatprinter)__FORMAT_PRINTER;
#else /* __CHAR_SIZE == 4 */
				/* __FORMAT_UNICODE_FORMAT8: format_8to16 */
				struct /*format_8to16_data*/ {
					__pc16formatprinter __fd_printer;    /* [1..1] Inner printer */
					void               *__fd_arg;        /* Argument for `fd_printer' */
					__uint32_t     __fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
				} __format_data;
				__format_data.__fd_printer = (__pc16formatprinter)__FORMAT_PRINTER;
#endif /* __CHAR_SIZE != 4 */
				__format_data.__fd_arg        = __FORMAT_ARG;
				__format_data.__fd_incomplete = 0;
				if __unlikely(!__string)
					__string = (__CHAR_TYPE *)__null_str8;
				if (__flags & __PRINTF_F_FIXBUF)
					__string_length = __precision;
				else if (__flags & __PRINTF_F_HASPREC)
					__string_length = __libc_strnlen((char const *)__string, __precision);
				else {
					__string_length = __libc_strlen((char const *)__string);
				}
				__string_width = __string_length;
				if (__width != 0) {
#ifndef __NO_PRINTF_ESCAPE
					if (__ch == 'q') {
						__string_width = (__size_t)__FORMAT_ESCAPE8(&__FORMAT_WIDTH8, __NULLPTR,
						                                                 (char const *)__string,
						                                                 __string_length,
						                                                 __FORMAT_ESCAPE_FLAGS);
					} else
#endif /* !__NO_PRINTF_ESCAPE */
					{
						__string_width = (__size_t)__FORMAT_WIDTH8(__NULLPTR, (char const *)__string, __string_length);
					}
					if ((__width > __string_width) && !(__flags & __PRINTF_F_LJUST)) {
						__CHAR_TYPE __padch = ' ';
						if __unlikely(__flags & __PRINTF_F_PADZERO)
							__padch = '0';
						__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, __padch, __width - __string_width);
						if __unlikely(__temp < 0)
							goto __err;
						__result += __temp;
					}
				}
#ifndef __NO_PRINTF_ESCAPE
				if (__ch == 'q') {
					__temp = __FORMAT_ESCAPE8(&__FORMAT_UNICODE_FORMAT8, &__format_data,
					                          (char const *)__string, __string_length,
					                          __FORMAT_ESCAPE_FLAGS);
				} else
#endif /* !__NO_PRINTF_ESCAPE */
				{
					__temp = __FORMAT_UNICODE_FORMAT8(&__format_data,
					                                  (char const *)__string,
					                                  __string_length);
				}
			}
			goto __check_string_error_and_print_tail;
#endif /* __CHAR_SIZE != 1 */
		} else if ((__length & 0x1000) == 0x1000) {
#ifdef __FORMAT_WCSIZE
			/* wchar-string */
			if (__FORMAT_WCSIZE == 4)
				goto __do_utf32_string;
			if (__FORMAT_WCSIZE == 2)
				goto __do_utf16_string;
			goto __do_utf8_string;
#else /* __FORMAT_WCSIZE */
			goto __do_wchar;
#endif /* !__FORMAT_WCSIZE */
		}
#endif /* !__NO_PRINTF_UNICODE_STRING */

#if __CHAR_SIZE == __SIZEOF_CHAR__
		if __unlikely(!__string)
			__string = "(null)";
#else /* __CHAR_SIZE == __SIZEOF_CHAR__ */
		if __unlikely(!__string) {
			static __CHAR_TYPE const __null_str[] = { '(', 'n', 'u', 'l', 'l', ')', 0 };
			__string = __null_str;
		}
#endif /* __CHAR_SIZE != __SIZEOF_CHAR__ */
		if (__flags & __PRINTF_F_FIXBUF)
			__string_length = __precision;
#if __CHAR_SIZE == __SIZEOF_CHAR__
		else if (__flags & __PRINTF_F_HASPREC)
			__string_length = __libc_strnlen(__string, __precision);
		else {
			__string_length = __libc_strlen(__string);
		}
#elif __CHAR_SIZE == 2
		else if (__flags & __PRINTF_F_HASPREC)
			__string_length = __libc_c16nlen((__CHAR16_TYPE__ *)__string, __precision);
		else {
			__string_length = __libc_c16len((__CHAR16_TYPE__ *)__string);
		}
#else
		else if (__flags & __PRINTF_F_HASPREC)
			__string_length = __libc_c32nlen((__CHAR32_TYPE__ *)__string, __precision);
		else {
			__string_length = __libc_c32len((__CHAR32_TYPE__ *)__string);
		}
#endif
print_string:
		__string_width = __string_length;
		if (__width != 0) {
#ifndef __NO_PRINTF_ESCAPE
			if (__ch == 'q') {
				__string_width = (__size_t)__FORMAT_ESCAPE(&__FORMAT_WIDTH, __NULLPTR,
				                                                __string, __string_length,
				                                                __FORMAT_ESCAPE_FLAGS);
			} else
#endif /* !__NO_PRINTF_ESCAPE */
			{
#if __CHAR_SIZE != 4
				__string_width = (__size_t)__FORMAT_WIDTH(__NULLPTR, __string, __string_length);
#endif /* __CHAR_SIZE != 4 */
			}
			if ((__width > __string_width) && !(__flags & __PRINTF_F_LJUST)) {
				__CHAR_TYPE __padch = ' ';
				if __unlikely(__flags & __PRINTF_F_PADZERO)
					__padch = '0';
				__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, __padch, __width - __string_width);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
		}
#ifndef __NO_PRINTF_ESCAPE
		if (__ch == 'q') {
			__temp = __FORMAT_ESCAPE(__FORMAT_PRINTER, __FORMAT_ARG,
			                         __string, __string_length,
			                         __FORMAT_ESCAPE_FLAGS);
		} else
#undef __FORMAT_ESCAPE_FLAGS
#endif /* !__NO_PRINTF_ESCAPE */
		{
			__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __string, __string_length);
		}
#ifndef __NO_PRINTF_UNICODE_STRING
__check_string_error_and_print_tail:
#endif /* !__NO_PRINTF_UNICODE_STRING */
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
		if ((__width > __string_width) && (__flags & __PRINTF_F_LJUST)) {
			__CHAR_TYPE __padch = ' ';
			if __unlikely(__flags & __PRINTF_F_PADZERO)
				__padch = '0';
			__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, __padch, __width - __string_width);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
	}	break;

#if (!defined(__NO_PRINTF_HEX) || !defined(__NO_PRINTF_GEN) || \
     !defined(__NO_PRINTF_DISASM) || !defined(__NO_PRINTF_VINFO))
	case '[': {
#define __PRINTF_HAVE_LBRACKET
		__CHAR_TYPE const *__xformat_start;
		__CHAR_TYPE const *__xformat_arg;
		__size_t __xformat_size;
		__size_t __xformat_argsize;
		unsigned int __i;
		__xformat_start = __FORMAT_FORMAT;
		__xformat_arg = __NULLPTR;
		__i = 1;
		while ((__ch = *__FORMAT_FORMAT) != 0) {
			++__FORMAT_FORMAT;
			if (__ch == '\033' && *__FORMAT_FORMAT == '[')
				++__FORMAT_FORMAT; /* Don't count ANSI escape sequences! */
			else if (__ch == '[')
				++__i;
			else if (__ch == ']') {
				if (!--__i)
					break;
			} else if (__ch == ':' && __i == 1 && !__xformat_arg) {
				__xformat_arg = __FORMAT_FORMAT;
			}
		}
		if (__xformat_arg) {
			__xformat_size = (__size_t)((__xformat_arg - 1) - __xformat_start);
			__xformat_argsize = __FORMAT_FORMAT - __xformat_arg;
			if (__ch) --__xformat_argsize;
		} else {
			__xformat_argsize = 0;
			__xformat_size = (__size_t)(__FORMAT_FORMAT - __xformat_start);
			if (__ch)
				--__xformat_size;
		}
		(void)__xformat_start;
		(void)__xformat_size;
		(void)__xformat_arg;
		(void)__xformat_argsize;
#define __COMPARE_NAME(x) (__COMPILER_STRLEN(x) == __xformat_size && __libc_memcmp(x, __xformat_start, __COMPILER_STRLEN(x)*sizeof(char)) == 0)
#ifndef __NO_PRINTF_HEX
		if (__COMPARE_NAME("hex")) {
#ifndef __FORMAT_HEXDUMP_FNORMAL
#define __FORMAT_HEXDUMP_FNORMAL    0x0000 /* Normal hexdump flags. */
#define __FORMAT_HEXDUMP_FHEXLOWER  0x0001 /* Print hex text of the dump in lowercase (does not affect address/offset). */
#define __FORMAT_HEXDUMP_FNOADDRESS 0x0002 /* Don't include the absolute address at the start of every line. */
#define __FORMAT_HEXDUMP_FOFFSETS   0x0004 /* Include offsets from the base address at the start of every line (after the address when also shown). */
#define __FORMAT_HEXDUMP_FNOHEX     0x0008 /* Don't print the actual hex dump (hex data representation). */
#define __FORMAT_HEXDUMP_FNOASCII   0x0010 /* Don't print ascii representation of printable characters at the end of lines. */
#define __FORMAT_HEXDUMP_BYTES      0x0000 /* Dump data as bytes. */
#define __FORMAT_HEXDUMP_WORDS      0x1000 /* Dump data as words (uint16_t). */
#define __FORMAT_HEXDUMP_DWORDS     0x2000 /* Dump data as dwords (uint32_t). */
#define __FORMAT_HEXDUMP_QWORDS     0x3000 /* Dump data as qwords (uint64_t). */
#define __FORMAT_HEXDUMP_SIZEMASK   0x3000 /* Mask for the dump size. */
#endif /* !__FORMAT_HEXDUMP_FNORMAL */
			void *__p = __PRINTF_VARGPTR();
			unsigned int __hex_flags = (__length & 0xf0) << 8;
			while (__xformat_argsize--) {
				__ch = *__xformat_arg++;
				/* lower-case: enable
				 * upper-case: disable
				 *   `l' -- Use lower-case for hex characters     (l-lowercase)
				 *   `o' -- Print offsets from the hex base       (o-offsets)
				 *   `p' -- Print the address of each line        (p-pointer)
				 *   `a' -- Print the line's ascii representation (a-ascii)
				 *   `h' -- Print each byte's hex representation  (h-hex)
				 */
				switch (__ch) {
				case 'l': __hex_flags |= __FORMAT_HEXDUMP_FHEXLOWER; break;
				case 'L': __hex_flags &= ~__FORMAT_HEXDUMP_FHEXLOWER; break;
				case 'o': __hex_flags |= __FORMAT_HEXDUMP_FOFFSETS; break;
				case 'O': __hex_flags &= ~__FORMAT_HEXDUMP_FOFFSETS; break;
				case 'p': __hex_flags &= ~__FORMAT_HEXDUMP_FNOADDRESS; break;
				case 'P': __hex_flags |= __FORMAT_HEXDUMP_FNOADDRESS; break;
				case 'a': __hex_flags &= ~__FORMAT_HEXDUMP_FNOASCII; break;
				case 'A': __hex_flags |= __FORMAT_HEXDUMP_FNOASCII; break;
				case 'h': __hex_flags &= ~__FORMAT_HEXDUMP_FNOHEX; break;
				case 'H': __hex_flags |= __FORMAT_HEXDUMP_FNOHEX; break;
				default: goto __broken_format;
				}
			}
			__hex_flags |= (__length & 0xf0) << 8;
			if (!(__flags & __PRINTF_F_FIXBUF))
				__precision = __libc_strnlen((char *)__p, __precision);
			__temp = __FORMAT_HEXDUMP(__FORMAT_PRINTER, __FORMAT_ARG, __p, __precision, 0, __hex_flags);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
			break;
		}
#endif /* !__NO_PRINTF_HEX */
#ifndef __NO_PRINTF_GEN
		if (__COMPARE_NAME("gen")) {
#if __CHAR_SIZE == __SIZEOF_CHAR__
#define __PFORMATPRINTER_TYPE  __pformatprinter
#define __PFORMATPRINTER_GENCC __FORMATPRINTER_CC
#elif __CHAR_SIZE == __SIZEOF_WCHAR_T__
#define __PFORMATPRINTER_TYPE  __pwformatprinter
#define __PFORMATPRINTER_GENCC __WFORMATPRINTER_CC
#elif __CHAR_SIZE == 2
#define __PFORMATPRINTER_TYPE  __pc16formatprinter
#define __PFORMATPRINTER_GENCC __C16FORMATPRINTER_CC
#else /* __CHAR_SIZE == ... */
#define __PFORMATPRINTER_TYPE  __pc32formatprinter
#define __PFORMATPRINTER_GENCC __C32FORMATPRINTER_CC
#endif /* __CHAR_SIZE != ... */
			if (!__xformat_argsize) {
				/* Generator without closure */
				typedef __ssize_t (__PFORMATPRINTER_GENCC *__gen_t)(__PFORMATPRINTER_TYPE, void *);
				__gen_t __gen = (__gen_t)__PRINTF_VARGPTR();
				__temp = (*__gen)((__PFORMATPRINTER_TYPE)__FORMAT_PRINTER, __FORMAT_ARG);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				break;
			}
			if (__xformat_argsize == 1 && __xformat_arg[0] == 'c') {
				/* Generator with closure */
				switch (__length & 0x1f0) {
#define __DEFINE_GENERATOR_IMPLEMENTATION(__T, __va_arg)                                                     \
				{                                                                                            \
					typedef __ssize_t (__PFORMATPRINTER_GENCC *__gen_t)(__T, __PFORMATPRINTER_TYPE, void *); \
					__gen_t __gen;                                                                           \
					__T __genarg;                                                                            \
					__gen    = (__gen_t)__PRINTF_VARGPTR();                                                  \
					__genarg = (__T)__va_arg;                                                                \
					__temp   = (*__gen)(__genarg, (__PFORMATPRINTER_TYPE)__FORMAT_PRINTER, __FORMAT_ARG);    \
				}                                                                                            \
				break;
#if __SIZEOF_POINTER__ < 2
				default:
#endif /* __SIZEOF_POINTER__ < 2 */
				case __PRINTF_LENGTH_I8 & 0x1f0:
					__DEFINE_GENERATOR_IMPLEMENTATION(__uint8_t, __PRINTF_VARG(unsigned))
#if __SIZEOF_POINTER__ >= 2 && __SIZEOF_POINTER__ < 4
				default:
#endif /* __SIZEOF_POINTER__ >= 2 && __SIZEOF_POINTER__ < 4 */
				case __PRINTF_LENGTH_I16 & 0x1f0:
#if __SIZEOF_INT__ > 2
					__DEFINE_GENERATOR_IMPLEMENTATION(__uint16_t, __PRINTF_VARG(unsigned))
#else /* __SIZEOF_INT__ > 2 */
					__DEFINE_GENERATOR_IMPLEMENTATION(__uint16_t, __PRINTF_VARG(__uint16_t))
#endif /* __SIZEOF_INT__ <= 2 */
#if __SIZEOF_POINTER__ >= 4 && __SIZEOF_POINTER__ < 8
				default:
#endif /* __SIZEOF_POINTER__ >= 4 && __SIZEOF_POINTER__ < 8 */
				case __PRINTF_LENGTH_I32 & 0x1f0:
#if __SIZEOF_INT__ > 4
					__DEFINE_GENERATOR_IMPLEMENTATION(__uint32_t, __PRINTF_VARG(unsigned))
#else /* __SIZEOF_INT__ > 4 */
					__DEFINE_GENERATOR_IMPLEMENTATION(__uint32_t, __PRINTF_VARG(__uint32_t))
#endif /* __SIZEOF_INT__ <= 4 */
#if __SIZEOF_POINTER__ >= 8
				default:
#endif /* __SIZEOF_POINTER__ >= 8 */
				case __PRINTF_LENGTH_I64 & 0x1f0:
					__DEFINE_GENERATOR_IMPLEMENTATION(__uint64_t, __PRINTF_VARG(__uint64_t))
#undef __DEFINE_GENERATOR_IMPLEMENTATION
				}
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				break;
			}
#undef __PFORMATPRINTER_GENCC
#undef __PFORMATPRINTER_TYPE
			goto __broken_format;
		}
#endif /* !__NO_PRINTF_GEN */
#ifndef __NO_PRINTF_DISASM
		if (__COMPARE_NAME("disasm")) {
			void *__p = __PRINTF_VARGPTR();
			{
				/* Load `libdisasm.so' to implement disassembler support. */
#if !defined(__KERNEL__) || !defined(__KOS__)
				static void *__p_libdisasm = __NULLPTR;
				static PDISASM __p_disasm = __NULLPTR;
				static PDISASM_SINGLE __p_disasm_single = __NULLPTR;
				if (!__p_libdisasm) {
					void *__m = dlopen(LIBDISASM_LIBRARY_NAME, RTLD_LOCAL);
					if __unlikely(!__m) {
						__p_libdisasm = (void *)-1;
						goto __broken_format;
					}
					*(void **)&__p_disasm        = dlsym(__m, "disasm");
					*(void **)&__p_disasm_single = dlsym(__m, "disasm_single");
					if (!__p_disasm || !__p_disasm_single) {
						__p_libdisasm = (void *)-1;
						goto __broken_format;
					}
					__p_libdisasm = __m;
				} else {
					if (__p_libdisasm == (void *)-1)
						goto __broken_format;
				}
#endif /* !__KERNEL__ || !__KOS__ */
#if __CHAR_SIZE == __SIZEOF_CHAR__
				if (!(__flags & __PRINTF_F_FIXBUF)) {
#if defined(__KERNEL__) && defined(__KOS__)
					__temp = disasm_single(__FORMAT_PRINTER, __FORMAT_ARG, __p, DISASSEMBLER_TARGET_CURRENT, DISASSEMBLER_FNORMAL);
#else /* __KERNEL__ && __KOS__ */
					__temp = (*__p_disasm_single)(__FORMAT_PRINTER, __FORMAT_ARG, __p, DISASSEMBLER_TARGET_CURRENT, DISASSEMBLER_FNORMAL);
#endif /* !__KERNEL__ || !__KOS__ */
				} else {
#if defined(__KERNEL__) && defined(__KOS__)
					__temp = disasm(__FORMAT_PRINTER, __FORMAT_ARG, __p, __precision, DISASSEMBLER_TARGET_CURRENT, DISASSEMBLER_FNORMAL);
#else /* __KERNEL__ && __KOS__ */
					__temp = (*__p_disasm)(__FORMAT_PRINTER, __FORMAT_ARG, __p, __precision, DISASSEMBLER_TARGET_CURRENT, DISASSEMBLER_FNORMAL);
#endif /* !__KERNEL__ || !__KOS__ */
				}
#else /* __CHAR_SIZE == __SIZEOF_CHAR__ */
				__temp = 0; /* TODO */
#endif /* __CHAR_SIZE != __SIZEOF_CHAR__ */
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
			break;
		}
#endif /* !__NO_PRINTF_DISASM */
#ifndef __NO_PRINTF_VINFO
#if __CHAR_SIZE == __SIZEOF_CHAR__ /* TODO: Other char sizes! */
#if 1 /* USE_LIBDEBUGINFO */
		if (__COMPARE_NAME("vinfo")) {
			__PRIVATE char const __vinfo_default_format[] = "%f(%l,%c) : %n";
			void *__p = __PRINTF_VARGPTR();
			if (!__xformat_arg) {
				__xformat_arg     = __vinfo_default_format;
				__xformat_argsize = __COMPILER_STRLEN(__vinfo_default_format);
			}
			{
				char __buf[32], *__bufiter;
				di_debug_addr2line_t __info;
				char const *__xiter, *__xend, *__xflush;
				__uintptr_t __val, __modrel;
#if !defined(__KERNEL__) || !defined(__KOS__)
				di_addr2line_sections_t __debug_sections;
				di_addr2line_dl_sections_t __dl_debug_sections;
				/* Load `libdebuginfo.so' to implement addr2line support. */
				static void *__p_libdebuginfo = __NULLPTR;
				static PDEBUG_ADDR2LINE_SECTIONS_LOCK __p_debug_addr2line_sections_lock;
				static PDEBUG_ADDR2LINE_SECTIONS_UNLOCK __p_debug_addr2line_sections_unlock;
				static PDEBUG_ADDR2LINE __p_debug_addr2line;
				static PDEBUG_ADDR2LINE_PRINT_FILENAME __p_debug_addr2line_print_filename;
				void *__ptr_module;
				if (!__p_libdebuginfo) {
					void *__m = dlopen(LIBDEBUGINFO_LIBRARY_NAME, RTLD_LOCAL);
					if __unlikely(!__m) {
						__p_libdebuginfo = (void *)-1;
						goto __broken_format;
					}
					*(void **)&__p_debug_addr2line_sections_lock   = dlsym(__m, "debug_addr2line_sections_lock");
					*(void **)&__p_debug_addr2line_sections_unlock = dlsym(__m, "debug_addr2line_sections_unlock");
					*(void **)&__p_debug_addr2line                 = dlsym(__m, "debug_addr2line");
					*(void **)&__p_debug_addr2line_print_filename  = dlsym(__m, "debug_addr2line_print_filename");
					if (!__p_debug_addr2line_sections_lock || !__p_debug_addr2line_sections_unlock ||
					    !__p_debug_addr2line || !__p_debug_addr2line_print_filename) {
						__p_libdebuginfo = (void *)-1;
						goto __broken_format;
					}
					__p_libdebuginfo = __m;
				} else {
					if (__p_libdebuginfo == (void *)-1)
						goto __broken_format;
				}
				__ptr_module = dlgethandle(__p, DLGETHANDLE_FNORMAL);
				__modrel = (__uintptr_t)dlmodulebase(__ptr_module);
				(*__p_debug_addr2line_sections_lock)(__ptr_module, &__debug_sections, &__dl_debug_sections);
				(*__p_debug_addr2line)(&__debug_sections, &__info,
				                       (__uintptr_t)__p - __modrel,
				                       DEBUG_ADDR2LINE_LEVEL_SOURCE,
				                       DEBUG_ADDR2LINE_FNORMAL);
#else /* !__KERNEL__ || !__KOS__ */
				struct addr2line_buf __dl_debug_sections;
				__uintptr_t __rel;
				__rel = addr2line_begin(&__dl_debug_sections, __p);
				__modrel = (__uintptr_t)__p - __rel;
				addr2line(&__dl_debug_sections, __rel, &__info, DEBUG_ADDR2LINE_LEVEL_SOURCE);
#endif /* __KERNEL__ && __KOS__ */
				__xiter = __xflush = __xformat_arg;
				__xend = __xformat_arg + __xformat_argsize;
__again_vinfo_xiter:
				if (__xiter >= __xend)
					goto __end_vinfo_xiter;
				__ch = *__xiter++;
				if (__ch != '%')
					goto __again_vinfo_xiter;
				if (__xiter > __xflush) {
					__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __xflush, (__size_t)(__xiter - __xflush) - 1);
					if __unlikely(__temp < 0)
						goto __err_vinfo;
					__result += __temp;
				}
				__ch = *__xiter++;
				switch (__ch) {

				case '<':
					__val = __modrel + __info.al_linestart;
__do_vinfo_hex:
					__bufiter = __COMPILER_ENDOF(__buf);
					do {
						*--__bufiter = __LOCAL_itoa_upper_digits[__val % 16];
					} while ((__val /= 16) != 0);
					__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __bufiter, (__size_t)(__COMPILER_ENDOF(__buf) - __bufiter));
					if __unlikely(__temp < 0)
						goto __err_vinfo;
					__result += __temp;
					break;

				case 'n':
					if (!__info.al_name)
						__info.al_name = (char *)"??" "?";
					__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __info.al_name, __libc_strlen(__info.al_name));
					if __unlikely(__temp < 0)
						goto __err_vinfo;
					__result += __temp;
					break;

				case 'N':
					if (!__info.al_rawname)
						__info.al_rawname = (char *)"??" "?";
					__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __info.al_rawname, __libc_strlen(__info.al_rawname));
					if __unlikely(__temp < 0)
						goto __err_vinfo;
					__result += __temp;
					break;

				case 'R': /* R -- Raw */
					if __unlikely(__xiter >= __xend)
						goto __default_vinfo_xiter;
					__ch = *__xiter++;
					if (__ch == 'f') {
						/* 'Rf'  (Same as `%f', but exclude the `al_cubase' prefix) */
						__temp = __info.al_srcfile
						       ? (*__FORMAT_PRINTER)(__FORMAT_ARG, __info.al_srcfile, __libc_strlen(__info.al_srcfile))
						       : (*__FORMAT_PRINTER)(__FORMAT_ARG, "??" "?", 3)
						       ;
					} else if (__ch == 'D') {
						if __unlikely(__xiter >= __xend)
							goto __default_vinfo_xiter;
						__ch = *__xiter++;
						if (__ch == 'f') {
							/* 'RDf' (Same as `%Df', but exclude the `al_cubase' prefix) */
							__temp = __info.al_dclfile
							       ? (*__FORMAT_PRINTER)(__FORMAT_ARG, __info.al_dclfile, __libc_strlen(__info.al_dclfile))
							       : (*__FORMAT_PRINTER)(__FORMAT_ARG, "??" "?", 3)
							       ;
						} else {
							__xiter -= 2;
							goto __default_vinfo_xiter;
						}
					} else {
						--__xiter;
						goto __default_vinfo_xiter;
					}
					if __unlikely(__temp < 0)
						goto __err_vinfo;
					__result += __temp;
					break;

				case '1':
					if __unlikely(__xiter >= __xend)
						goto __default_vinfo_xiter;
					__ch = *__xiter++;
					if (__ch == '>') {
						/* '1>'  (Same as `>', but decrement by one) */
						__val = __modrel + __info.al_lineend - 1;
						goto __do_vinfo_hex;
					} else if (__ch == 'E') {
						/* '1E'  (Same as `E', but decrement by one) */
						__val = __modrel + __info.al_symend - 1;
						goto __do_vinfo_hex;
					} else {
						--__xiter;
						goto __default_vinfo_xiter;
					}
					break;

				case '>':
					__val = __modrel + __info.al_lineend;
					goto __do_vinfo_hex;

				case 'S':
					__val = __modrel + __info.al_symstart;
					goto __do_vinfo_hex;

				case 'E':
					__val = __modrel + __info.al_symend;
					goto __do_vinfo_hex;

				case 'p':
					__val = (__uintptr_t)__p;
					goto __do_vinfo_hex;

				case 'l':
					__val = __info.al_srcline;
__do_vinfo_decimal:
					__bufiter = __COMPILER_ENDOF(__buf);
					do {
						*--__bufiter = __LOCAL_itoa_decimal(__val % 10);
					} while ((__val /= 10) != 0);
					__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __bufiter, (__size_t)(__COMPILER_ENDOF(__buf) - __bufiter));
					if __unlikely(__temp < 0)
						goto __err_vinfo;
					__result += __temp;
					break;

				case 'c':
					__val = __info.al_srccol;
					goto __do_vinfo_decimal;

				case 'f':
#if !defined(__KERNEL__) || !defined(__KOS__)
					__temp = (*__p_debug_addr2line_print_filename)(__FORMAT_PRINTER, __FORMAT_ARG, __info.al_cubase, __info.al_srcpath, __info.al_srcfile);
#else /* !__KERNEL__ || !__KOS__ */
					__temp = debug_addr2line_print_filename(__FORMAT_PRINTER, __FORMAT_ARG, __info.al_cubase, __info.al_srcpath, __info.al_srcfile);
#endif /* __KERNEL__ && __KOS__ */
					if __unlikely(__temp < 0)
						goto __err_vinfo;
					__result += __temp;
					break;

				case 'D':
					if __unlikely(__xiter >= __xend)
						goto __default_vinfo_xiter;
					__ch = *__xiter++;
					switch (__ch) {

					case 'l':
						__val = __info.al_dclline;
						goto __do_vinfo_decimal;

					case 'c':
						__val = __info.al_dclcol;
						goto __do_vinfo_decimal;

					case 'f':
#if !defined(__KERNEL__) || !defined(__KOS__)
						__temp = (*__p_debug_addr2line_print_filename)(__FORMAT_PRINTER, __FORMAT_ARG, __info.al_cubase, __info.al_dclpath, __info.al_dclfile);
#else /* !__KERNEL__ || !__KOS__ */
						__temp = debug_addr2line_print_filename(__FORMAT_PRINTER, __FORMAT_ARG, __info.al_cubase, __info.al_dclpath, __info.al_dclfile);
#endif /* __KERNEL__ && __KOS__ */
						if __unlikely(__temp < 0)
							goto __err_vinfo;
						__result += __temp;
						break;

					default:
						--__xiter;
						goto __default_vinfo_xiter;
					}
					break;

				case '%':
					__xflush = __xiter - 1;
					goto __again_vinfo_xiter;

				default:
__default_vinfo_xiter:
					__xflush = __xiter - 2;
					goto __again_vinfo_xiter;
				}
				__xflush = __xiter;
				goto __again_vinfo_xiter;
__end_vinfo_xiter:
				if (__xend > __xflush) {
					__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __xflush, (__size_t)(__xend - __xflush));
					if __unlikely(__temp < 0)
						goto __err_vinfo;
					__result += __temp;
				}
#if !defined(__KERNEL__) || !defined(__KOS__)
				(*__p_debug_addr2line_sections_unlock)(&__dl_debug_sections);
#else /* !__KERNEL__ || !__KOS__ */
				addr2line_end(&__dl_debug_sections);
#endif /* __KERNEL__ && __KOS__ */
				break;
__err_vinfo:
#if !defined(__KERNEL__) || !defined(__KOS__)
				(*__p_debug_addr2line_sections_unlock)(&__dl_debug_sections);
#else /* !__KERNEL__ || !__KOS__ */
				addr2line_end(&__dl_debug_sections);
#endif /* !__KERNEL__ || !__KOS__ */
				goto __err;
			}
		}
#elif defined(__KOS__)
		if (__COMPARE_NAME("vinfo")) {
			__PRIVATE char const __vinfo_default_format[] = "%f(%l,%c) : %n";
			void *__p = __PRINTF_VARG(void *);
			if (!__xformat_arg) {
				__xformat_arg = __vinfo_default_format;
				__xformat_argsize = __COMPILER_STRLEN(__vinfo_default_format);
			}
#if defined(__KERNEL__)
			__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, "%{vinfo:/os/kernel.bin:",
			                             __COMPILER_STRLEN("%{vinfo:/os/kernel.bin:"));
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
			{
				char __ptr_buffer[2*sizeof(void *)], *__bufdst;
				__uintptr_t __val;
				__bufdst = __COMPILER_ENDOF(__ptr_buffer);
				__val = (__uintptr_t)__p;
				do {
					*--__bufdst = __LOCAL_itoa_upper_digits[__val & 0xf];
					__val >>= 4;
				} while (__bufdst > __ptr_buffer);
				__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __ptr_buffer, __COMPILER_LENOF(__ptr_buffer));
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, ":", 1);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				__bufdst = __COMPILER_ENDOF(__ptr_buffer);
				__val = (__uintptr_t)__p;
				do {
					*--__bufdst = __LOCAL_itoa_upper_digits[__val & 0xf];
					__val >>= 4;
				} while (__bufdst > __ptr_buffer);
				__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __ptr_buffer, __COMPILER_LENOF(__ptr_buffer));
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
			__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, ":", 1);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
			__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __xformat_arg, __xformat_argsize);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
			__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, "}", 1);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
#else /* __KERNEL__ */
			(void)__xformat_arg;
			(void)__p;
#endif /* !__KERNEL__ */
			break;
		}
#endif
#endif /* __CHAR_SIZE == __SIZEOF_CHAR__ */ /* TODO: Other char sizes! */
#endif /* !__NO_PRINTF_VINFO */
		goto __broken_format;
#undef __COMPARE_NAME
	}	break;
#endif


	/* Floating point to string conversion */
#if (!defined(__NO_PRINTF_FLOATING_POINT) && \
     !defined(__NO_FPU))
	case 'f': case 'F':
	case 'e': case 'E':
	case 'g': case 'G':
	{
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __USED_FLOAT_TYPE __LONGDOUBLE
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __USED_FLOAT_TYPE double
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
		__PRIVATE __USED_FLOAT_TYPE const __pow10[10] = {
			1, 10, 100, 1000, 10000, 100000, 1000000,
			10000000, 100000000, 1000000000 };
		__USED_FLOAT_TYPE __val, __tmpval, __diff;
		__CHAR_TYPE __buf[32]; /* Must be able to hold a decimal-encoded UINT64_MAX +1 more character */
		__size_t __len, __total_len;
		__BOOL __is_negative;
		unsigned int __max_prec, __min_prec;
#ifdef __UINT64_TYPE__
		__uint64_t __whole, __frac;
#else /* __UINT64_TYPE__ */
		__uint32_t __whole, __frac;
#endif /* !__UINT64_TYPE__ */
#ifdef __COMPILER_HAVE_LONGDOUBLE
		if (__length == __PRINTF_LENGTH_L) {
			__val = __PRINTF_VARG(__LONGDOUBLE);
		} else
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
		{
			__val = (__USED_FLOAT_TYPE)__PRINTF_VARG(double);
		}
		/* TODO: Don't use builtins directly. - Add a hybrid API for this!
		 * TODO: When  enabling this  code, GCC generates  code to load  the special INF
		 *       floating point constants at the start of the function. Unconditionally!
		 *       I can't have that!  - Switching FPU context  is expensive, and I  don't
		 *       want it to happen _every_ _time_ user-code makes use of a printf()-like
		 *       function. That's just wasteful!
		 *    -> I hope  that by  using dedicated  functions instead  of builtins,  that
		 *       problem can be solved, but until then, let's just keep this disabled... */
#if (__has_builtin(__builtin_isinf) && __has_builtin(__builtin_isnan)) && 0
		if (__builtin_isinf(__val)) {
			__buf[1] = 'I';
			__buf[2] = 'N';
			__buf[3] = 'F';
__do_special_float:
			__total_len = 3;
			__is_negative = 0;
			if (__val < 0)
				__is_negative = 1;
			if (__is_negative || (__flags & (__PRINTF_F_SIGN | __PRINTF_F_SPACE)))
				++__total_len;
			if ((__flags & (__PRINTF_F_HASWIDTH | __PRINTF_F_LJUST)) ==
			               (__PRINTF_F_HASWIDTH | __PRINTF_F_LJUST) &&
			    (__width > __total_len)) {
				__CHAR_TYPE __padch = ' ';
				if __unlikely(__flags & __PRINTF_F_PADZERO)
					__padch = '0';
				__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, __padch, __width - __total_len);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
			if (__total_len == 4) {
				if (__is_negative)
					__buf[0] = '-';
				else if (__flags & __PRINTF_F_SIGN)
					__buf[0] = '+';
				else
					__buf[0] = ' ';
				__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __buf, 4);
			} else {
				__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __buf + 1, 3);
			}
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
			if ((__flags & (__PRINTF_F_HASWIDTH | __PRINTF_F_LJUST)) ==
			               (__PRINTF_F_HASWIDTH) &&
			    (__width > __total_len)) {
				__CHAR_TYPE __padch = ' ';
				if __unlikely(__flags & __PRINTF_F_PADZERO)
					__padch = '0';
				__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, __padch, __width - __total_len);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
			break;
		} else if (__builtin_isnan(__val)) {
			__buf[1] = 'N';
			__buf[2] = 'a';
			__buf[3] = 'N';
			goto __do_special_float;
		}
#endif /* Special floating point values... */
		__is_negative = 0;
		if (__val < 0) {
			__is_negative = 1;
			__val = -__val;
		}
		/* Determine the intended precision. */
		__max_prec = (unsigned int)__precision;
		__min_prec = (unsigned int)__precision;
		if (!(__flags & __PRINTF_F_HASPREC))
			__max_prec = 6, __min_prec = 0;
		else if (__max_prec > 9)
			__max_prec = __min_prec = 9;
		/* XXX: This cast can overflow */
#ifdef __UINT64_TYPE__
		__whole = (__UINT64_TYPE__)__val;
#else /* __UINT64_TYPE__ */
		__whole = (__uint32_t)__val;
#endif /* !__UINT64_TYPE__ */
		__tmpval = (__val - __whole) * __pow10[__max_prec];
#ifdef __UINT64_TYPE__
		__frac = (__UINT64_TYPE__)__tmpval;
#else /* __UINT64_TYPE__ */
		__frac = (__uint32_t)__tmpval;
#endif /* !__UINT64_TYPE__ */
		__diff = __tmpval - __frac;
		/* Round to the closest fraction. */
		if (__diff > 0.5) {
			++__frac;
			if (__frac > __pow10[__max_prec]) {
				__frac = 0;
				++__whole;
			}
		} else if (__diff == 0.5 && (__frac == 0 || __frac & 1)) {
			++__frac;
		}
		/* Special case: no fraction wanted. - Round the whole-part. */
		if (__max_prec == 0) {
			__diff = __val - (__USED_FLOAT_TYPE)__whole;
			if (__diff > 0.5) {
				++__whole;
			} else if (__diff == 0.5 && (__whole & 1)) {
				++__whole;
			}
		}
		/* Print the whole part. */
		__len = __COMPILER_LENOF(__buf);
		for (;;) {
			__buf[--__len] = (__CHAR_TYPE)(48 + (__whole % 10));
			__whole /= 10;
			if (!__whole)
				break;
		}
		/* Trim unused fraction digits. (should precision or
		 * width require  them, they'll  be re-added  later) */
		while (__frac && (__frac % 10) == 0)
			__frac /= 10;
		__total_len = __COMPILER_LENOF(__buf) - __len;
		if ((__flags & (__PRINTF_F_HASWIDTH | __PRINTF_F_LJUST)) ==
		               (__PRINTF_F_HASWIDTH | __PRINTF_F_LJUST)) {
			/* Pad with with leading zeroes. */
			if (__is_negative || (__flags & (__PRINTF_F_SIGN | __PRINTF_F_SPACE)))
				++__total_len;
			if (__max_prec != 0) {
				unsigned int __temp_min = __min_prec;
				__whole = __frac;
				++__total_len; /* . */
				for (;;) {
					if (__temp_min)
						--__temp_min;
					++__total_len;
					__whole /= 10;
					if (!__whole)
						break;
				}
				__total_len += __min_prec;
			}
			if (__width <= __total_len)
				goto __do_float_normal_width;
			if (!(__flags & __PRINTF_F_PADZERO)) {
				__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, ' ', __width - __total_len);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				goto __do_float_normal_width;
			}
			if (__is_negative || (__flags & (__PRINTF_F_SIGN | __PRINTF_F_SPACE))) {
				/* print the sign */
				__buf[0] = __is_negative ? '-' : (__flags & __PRINTF_F_SIGN) ? '+' : ' ';
				__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __buf, 1);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
			}
			/* Insert leading zeroes for padding. */
			__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, '0', __width - __total_len);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		} else {
__do_float_normal_width:
			if (__is_negative)
				__buf[--__len] = '-';
			else if (__flags & __PRINTF_F_SIGN)
				__buf[--__len] = '+';
			else if (__flags & __PRINTF_F_SPACE) {
				__buf[--__len] = ' ';
			}
		}
		__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __buf + __len, __COMPILER_LENOF(__buf) - __len);
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;

		/* Fractional part. */
		if (__max_prec != 0) {
			__len = __COMPILER_LENOF(__buf);
			for (;;) {
				if (__min_prec)
					--__min_prec;
				__buf[--__len] = (__CHAR_TYPE)(48 + (__frac % 10));
				__frac /= 10;
				if (!__frac)
					break;
			}
			__buf[--__len] = '.';
			__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __buf + __len, __COMPILER_LENOF(__buf) - __len);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
			__total_len += __COMPILER_LENOF(__buf) - __len;
			if (__min_prec) {
				__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG, '0', __min_prec);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				__total_len += __min_prec;
			}
		}
		if ((__flags & (__PRINTF_F_HASWIDTH | __PRINTF_F_LJUST)) == (__PRINTF_F_HASWIDTH) &&
		    (__width > __total_len)) {
			/* Insert a missing decimal separator. */
			if (__flags & __PRINTF_F_PADZERO && __max_prec == 0) {
				__buf[0] = '.';
				__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __buf, 1);
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				--__total_len;
			}
			/* Add trailing zeroes to pad out our length the requested width. */
			__temp = __FORMAT_REPEAT(__FORMAT_PRINTER, __FORMAT_ARG,
			                         __flags & __PRINTF_F_PADZERO ? '0' : ' ',
			                         __width - __total_len);
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
#undef __USED_FLOAT_TYPE
	}	break;
#endif /* !__NO_PRINTF_FLOATING_POINT && !__NO_FPU */


	default:
		if (__ch >= '0' && __ch <= '9') {
#ifdef __NO_PRINTF_POSITIONAL
			/* decimal-encoded width modifier. */
			__width = (__size_t)(__ch - '0');
			while ((__ch = *__FORMAT_FORMAT, __ch >= '0' && __ch <= '9')) {
				__width = __width * 10 + (__size_t)(__ch - '0');
				++__FORMAT_FORMAT;
			}
			__flags |= __PRINTF_F_HASWIDTH;
#else /* __NO_PRINTF_POSITIONAL */
			/* decimal-encoded width modifier, or positional argument. */
			__size_t __posidx;
			__CHAR_TYPE const *__old_format_format;
			__old_format_format = __FORMAT_FORMAT - 1;
			__IF0 {
__begin_positional_for_width_or_precision:
				__old_format_format = __FORMAT_FORMAT;
				do {
					__ch = *__FORMAT_FORMAT++;
				} while (!(__ch >= '0' && __ch <= '9'));
			}

			__posidx = (__size_t)(__ch - '0');
			while ((__ch = *__FORMAT_FORMAT, __ch >= '0' && __ch <= '9')) {
				__posidx = __posidx * 10 + (__size_t)(__ch - '0');
				++__FORMAT_FORMAT;
			}
			if (__ch == '$') {
				/* Positional argument selector. */
				if (!__p_args) {
					/* Figure out the greatest positional argument index. */
					__CHAR_TYPE const *__iter;
					__iter = __old_format_format;
					goto __again_posscan1_infmt;
					for (;;) {
						__size_t __posidx2;
						__ch = *__iter++;
						if (__ch == '\0')
							goto __after_posscan1_infmt;
						if (__ch != '%')
							continue;
__again_posscan1_infmt:
						__ch = *__iter++;
						switch (__ch) {
						case '\0':
							goto __after_posscan1_infmt;

						case '-':
						case '+':
						case ' ':
						case '#':
						case '0':
						case '.':
						case ':':
						case '*': /* Followed by operand: `unsigned int' */
						case '?': /* Followed by operand: `size_t' */
						case '$': /* Followed by operand: `size_t' */
							goto __again_posscan1_infmt;

#ifdef __PRINTF_HAVE_LBRACKET
						case '[': {
							/* Special handling for %[...] extended format codes. */
							unsigned int __i = 1;
							while ((__ch = *__iter) != 0) {
								++__iter;
								if (__ch == '\033' && *__iter == '[')
									++__iter; /* Don't count ANSI escape sequences! */
								else if (__ch == '[')
									++__i;
								else if (__ch == ']') {
									if (!--__i)
										break;
								}
							}
							continue;
						}	break;
#endif /* __PRINTF_HAVE_LBRACKET */

						default:
							if (!(__ch >= '0' && __ch <= '9'))
								continue;
							__posidx2 = __ch - '0';
							while ((__ch = *__iter, __ch >= '0' && __ch <= '9')) {
								__posidx2 = __posidx2 * 10 + (__size_t)(__ch - '0');
								++__iter;
							}
							if (__ch == '$') {
								if (__posidx < __posidx2)
									__posidx = __posidx2;
							}
							goto __again_posscan1_infmt;
						}
					}
__after_posscan1_infmt:

					/* Allocate space for positional arguments. */
					__p_args = (union __p_arg_union *)__hybrid_alloca(__posidx * sizeof(union __p_arg_union));
					{
						__size_t __posi;
						for (__posi = 0; __posi < __posidx; ++__posi)
							__p_args[__posi].__p_unsigned = 0;
					}

					/* Determine positional argument types. */
					__iter = __old_format_format;
					goto __begin_posscan2_infmt;
					for (;;) {
						__size_t __type_idx;
						unsigned int __type_code;
						unsigned int __type_length;
						__ch = *__iter++;
						if (__ch == '\0')
							goto __after_posscan2_infmt;
						if (__ch != '%')
							continue;
__begin_posscan2_infmt:
						__type_idx    = 0;
						__type_code   = 0;
						__type_length = 0;
__again_posscan2_infmt:
						__ch = *__iter++;
						switch (__ch) {
						case '\0':
							goto __after_posscan2_infmt;

						case '-':
						case '+':
						case ' ':
						case '#':
						case '0':
						case '.':
						case ':':
							goto __again_posscan2_infmt;

						case '*':   /* Followed by operand: `unsigned int' */
						case '?':   /* Followed by operand: `size_t' */
						case '$': { /* Followed by operand: `size_t' */
							__CHAR_TYPE __pos_ch;
							__pos_ch = *__iter++;
							if (__pos_ch >= '0' && __pos_ch <= '9') {
								__size_t __posidx3;
								__posidx3 = __pos_ch - '0';
								while ((__pos_ch = *__iter, __pos_ch >= '0' && __pos_ch <= '9')) {
									__posidx3 = __posidx3 * 10 + (__size_t)(__pos_ch - '0');
									++__iter;
								}
								if (__pos_ch == '$') {
#if (__PRINTF_LENGTH_SIZE & 0xf) != 0
									if (__pos_ch == '*') {
										__p_args[__posidx3 - 1].__p_unsigned = 0;
									} else
#endif /* (__PRINTF_LENGTH_SIZE & 0xf) != 0 */
									{
										__p_args[__posidx3 - 1].__p_unsigned = __PRINTF_LENGTH_SIZE & 0xf;
									}
									++__iter;
								}
							}
							goto __again_posscan2_infmt;
						}	break;

						case 'h':
							if (*__iter != 'h')
								__type_length = __PRINTF_LENGTH_H;
							else {
								++__iter;
								__type_length = __PRINTF_LENGTH_HH;
							}
							goto __again_posscan2_infmt;
						case 'l':
							if (*__iter != 'l')
								__type_length = __PRINTF_LENGTH_l;
							else {
								++__iter;
								__type_length = __PRINTF_LENGTH_LL;
							}
							goto __again_posscan2_infmt;
						case 'z':
							__type_length = __PRINTF_LENGTH_Z;
							goto __again_posscan2_infmt;

						case 't':
							__type_length = __PRINTF_LENGTH_T;
							goto __again_posscan2_infmt;

						case 'L':
							__type_length = __PRINTF_LENGTH_L;
							goto __again_posscan2_infmt;

						case 'I':
							__ch = *__iter++;
							if (__ch == '8')
								__type_length = __PRINTF_LENGTH_I8;
							else if (__ch == '1' && *__iter == '6') {
								++__iter;
								__type_length = __PRINTF_LENGTH_I16;
							} else if (__ch == '3' && *__iter == '2') {
								++__iter;
								__type_length = __PRINTF_LENGTH_I32;
							} else if (__ch == '6' && *__iter == '4') {
								++__iter;
						case 'j':
								__type_length = __PRINTF_LENGTH_I64;
							} else {
								--__iter;
								__type_length = __PRINTF_LENGTH_SIZE;
							}
							goto __again_posscan2_infmt;

						/* Determine type code:
						 * e.g. `%I64d' --> `__type_code = __PRINTF_LENGTH_R64'
						 * e.g. `%s'    --> `__type_code = __PRINTF_LENGTH_R32|64' (pointer-size) */
						case 'p':
							if (!__type_length)
								__type_length = __PRINTF_LENGTH_SIZE;
							__ATTR_FALLTHROUGH
						case 'b':
						case 'o':
						case 'u':
						case 'd':
						case 'i':
						case 'X':
						case 'x':
#ifndef __NO_PRINTF_ESCAPE
						case 'Q':
#endif /* !__NO_PRINTF_ESCAPE */
						case 'c':
							__type_code = __type_length & 0xf;
							break;

#ifdef __PRINTF_HAVE_LBRACKET
						case '[': {
							/* Special handling for %[...] extended format codes. */
							unsigned int __i = 1;
							while ((__ch = *__iter) != 0) {
								++__iter;
								if (__ch == '\033' && *__iter == '[')
									++__iter; /* Don't count ANSI escape sequences! */
								else if (__ch == '[')
									++__i;
								else if (__ch == ']') {
									if (!--__i)
										break;
								}
							}
						}	ATTR_FALLTHROUGH
#endif /* __PRINTF_HAVE_LBRACKET */
#ifndef __NO_PRINTF_ESCAPE
						case 'q':
#endif /* !__NO_PRINTF_ESCAPE */
						case 's':
							__type_code = __PRINTF_LENGTH_Z & 0xf;
							break;

#if (!defined(__NO_PRINTF_FLOATING_POINT) && !defined(__NO_FPU))
						case 'f': case 'F':
						case 'e': case 'E':
						case 'g': case 'G':
#ifdef __COMPILER_HAVE_LONGDOUBLE
							if (__type_length == __PRINTF_LENGTH_L) {
								__type_code = 9; /* long double */
							} else
#endif /* __COMPILER_HAVE_LONGDOUBLE */
							{
								__type_code = 8; /* double */
							}
							break;
#endif /* !__NO_PRINTF_FLOATING_POINT && !__NO_FPU */

						default:
							if (!(__ch >= '0' && __ch <= '9'))
								continue;
							__type_idx = __ch - '0';
							while ((__ch = *__iter, __ch >= '0' && __ch <= '9')) {
								__type_idx = __type_idx * 10 + (__size_t)(__ch - '0');
								++__iter;
							}
							if (__ch != '$')
								continue;
							++__iter;
							goto __again_posscan2_infmt;
						}
						if __unlikely(!__type_idx) {
#if 1
							/* Completely  abort printing, since  use of positional  arguments requires that _all_
							 * varargs use positional arguments. Note that on KOS this already is kind-of relaxed,
							 * in that we still accept normal varargs up until the first position argument, though
							 * this detail is neither officially documented, nor an intended feature. -- It's just
							 * a consequence on how positional argument support was implemented.
							 *
							 * So with all of that  in mind: rather than simply  skipping the current format  token,
							 * we skip the entire format string when the user attempts to mix varargs specifies with
							 * positional arguments. */
							while (*__FORMAT_FORMAT++)
								;
							goto __end;
#else
							goto __broken_format;
#endif
						}
						__p_args[__type_idx - 1].__p_unsigned = __type_code;
					}

__after_posscan2_infmt:
					/* Load positional arguments from varargs. */
					{
						__size_t __posi;
						for (__posi = 0; __posi < __posidx; ++__posi) {
							unsigned int __type_code;
							__type_code = __p_args[__posi].__p_unsigned;
							switch (__type_code) {

#if (!defined(__NO_PRINTF_FLOATING_POINT) && !defined(__NO_FPU))
							case 8:
								__p_args[__posi].__p_unsigned = __builtin_va_arg(__FORMAT_ARGS, double);
								break;
#ifdef __COMPILER_HAVE_LONGDOUBLE
							case 9:
								__p_args[__posi].__p_unsigned = __builtin_va_arg(__FORMAT_ARGS, __LONGDOUBLE);
								break;
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_PRINTF_FLOATING_POINT && !__NO_FPU) */

#if __PRINTF_LENGTH_R64 != 0
							case __PRINTF_LENGTH_R64:
								__p_args[__posi].__p___uint64_t = __builtin_va_arg(__FORMAT_ARGS, __uint64_t);
								break;
#endif /* __PRINTF_LENGTH_R64 != 0 */

#if __PRINTF_LENGTH_R32 != 0
							case __PRINTF_LENGTH_R32:
								__p_args[__posi].__p___uint32_t = __builtin_va_arg(__FORMAT_ARGS, __uint32_t);
								break;
#endif /* __PRINTF_LENGTH_R32 != 0 */

#if __PRINTF_LENGTH_R16 != 0
							case __PRINTF_LENGTH_R16:
								__p_args[__posi].__p___uint16_t = __builtin_va_arg(__FORMAT_ARGS, __uint16_t);
								break;
#endif /* __PRINTF_LENGTH_R16 != 0 */

							default:
								__p_args[__posi].__p_unsigned = __builtin_va_arg(__FORMAT_ARGS, unsigned);
								break;
							}
						}
					}
					__FORMAT_FORMAT = __old_format_format;
					goto __nextfmt;
				}
				++__FORMAT_FORMAT; /* Skip the '$' */
				__p_arg = &__p_args[__posidx - 1];
			} else {
				__width = __posidx;
				__flags |= __PRINTF_F_HASWIDTH;
			}
#endif /* !__NO_PRINTF_POSITIONAL */
			goto __nextfmt;
		}
__broken_format:
		__FORMAT_FORMAT = __flush_start;
		--__flush_start;
		goto __next;
	}
	__flush_start = __FORMAT_FORMAT;
	goto __next;
__end:
	--__FORMAT_FORMAT;
	__hybrid_assert(!*__FORMAT_FORMAT);
	if (__flush_start != __FORMAT_FORMAT) {
		__temp = (*__FORMAT_PRINTER)(__FORMAT_ARG, __flush_start, (__size_t)(__FORMAT_FORMAT - __flush_start));
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
	}
	return __result;
__err:
	return __temp;
#undef __PRINTF_HAVE_LBRACKET
#undef __PRINTF_VARGPTR
#undef __PRINTF_VARG
}

#undef __FORMAT_ESCAPE
#undef __FORMAT_REPEAT
#undef __PRINTF_LENGTH_I64
#undef __PRINTF_LENGTH_I32
#undef __PRINTF_LENGTH_I16
#undef __PRINTF_LENGTH_I8
#undef __PRINTF_LENGTH_R64
#undef __PRINTF_LENGTH_R32
#undef __PRINTF_LENGTH_R16
#undef __PRINTF_LENGTH_R8
#undef __PRINTF_LENGTH_L
#undef __PRINTF_LENGTH_Z
#undef __PRINTF_LENGTH_T
#undef __PRINTF_LENGTH_J
#undef __PRINTF_LENGTH_SIZE
#undef __PRINTF_LENGTH_HH
#undef __PRINTF_LENGTH_H
#undef __PRINTF_LENGTH_l
#undef __PRINTF_LENGTH_LL
#undef __PRINTF_F_NONE
#undef __PRINTF_F_UPPER2
#undef __PRINTF_F_UPPER
#undef __PRINTF_F_LJUST
#undef __PRINTF_F_SIGN
#undef __PRINTF_F_SPACE
#undef __PRINTF_F_PADZERO
#undef __PRINTF_F_HASWIDTH
#undef __PRINTF_F_HASPREC
#undef __PRINTF_F_PREFIX
#undef __PRINTF_F_SIGNED
#undef __PRINTF_F_FIXBUF

#undef __FORMAT_ARGS
#undef __FORMAT_ARG
#undef __FORMAT_PRINTER
#undef __FORMAT_FORMAT
#undef __FORMAT_WIDTH
#undef __FORMAT_WIDTH8
#undef __FORMAT_WIDTH16
#undef __FORMAT_WIDTH32
#undef __FORMAT_UNICODE_FORMAT8
#undef __FORMAT_UNICODE_FORMAT16
#undef __FORMAT_UNICODE_FORMAT32
#undef __FORMAT_UNICODE_WRITECHAR
#undef __FORMAT_HEXDUMP
#undef __FORMAT_REPEAT
#undef __FORMAT_STRERROR
#undef __FORMAT_ESCAPE
#undef __FORMAT_ESCAPE8
#undef __FORMAT_ESCAPE16
#undef __FORMAT_ESCAPE32
#undef __CHAR_SIZE
#undef __CHAR_TYPE
