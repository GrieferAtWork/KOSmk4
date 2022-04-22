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
#ifndef __CHAR_TYPE
#define __CHAR_TYPE       char
#endif /* !__CHAR_TYPE */
#ifndef __CHAR_SIZE
#define __CHAR_SIZE       __SIZEOF_CHAR__
#endif /* !__CHAR_SIZE */
#ifndef __FORMAT_PGETC
#define __FORMAT_PGETC    pgetc
#endif /* !__FORMAT_PGETC */
#ifndef __FORMAT_PUNGETC
#define __FORMAT_PUNGETC  pungetc
#endif /* !__FORMAT_PUNGETC */
#ifndef __FORMAT_ARG
#define __FORMAT_ARG      arg
#endif /* !__FORMAT_ARG */
#ifndef __FORMAT_FORMAT
#define __FORMAT_FORMAT   format
#endif /* !__FORMAT_FORMAT */
#ifndef __FORMAT_ARGS
#define __FORMAT_ARGS     args
#endif /* !__FORMAT_ARGS */

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <asm/crt/stdio.h> /* __EOF */

#ifdef __INTELLISENSE__
#include <bits/crt/format-printer.h>
#include <bits/math-constants.h>

#include <libc/string.h>
#include <libc/unicode.h>

extern "C" __SSIZE_TYPE__
format_vscanf(__pformatgetc __FORMAT_PGETC,
              __pformatungetc __FORMAT_PUNGETC,
              void *__FORMAT_ARG,
              __CHAR_TYPE const *__restrict __FORMAT_FORMAT,
              __builtin_va_list __FORMAT_ARGS)
#endif /* __INTELLISENSE__ */
{
#if __CHAR_SIZE == __SIZEOF_CHAR__
#define __PRIVATE_FORMAT_SCANF_READUNI(p_iter, end) __libc_unicode_readutf8_n((char const **)(p_iter), end)
#elif __CHAR_SIZE == 2
#define __PRIVATE_FORMAT_SCANF_READUNI(p_iter, end) __libc_unicode_readutf16_n((__CHAR16_TYPE__ const **)(p_iter), end)
#else /* __CHAR_SIZE == ... */
#define __PRIVATE_FORMAT_SCANF_READUNI(p_iter, end) (*(p_iter) >= (end) ? 0 : *((*(p_iter))++))
#endif /* __CHAR_SIZE != ... */
	__SIZE_TYPE__ __read_count = 0;
	__SSIZE_TYPE__ __result = 0;
	__format_word_t __temp = 0; /* XXX: Unused init! */
	__BOOL __has_temp = 0;
	__CHAR_TYPE __ch;
__next:
	__ch = *__FORMAT_FORMAT++;

	/* TODO: Re-work this function to deal with the fact that `__FORMAT_PGETC()'
	 *       returns BYTE/WORD/DWORD, rather than unicode characters! */
	switch (__ch) {

	case '\0':
		goto __end_maybe_unget;

	case '\n':
		/* Skip any kind of linefeed */
		if (!__has_temp) {
			__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
			if __unlikely(__temp < 0)
				goto __err_or_eof;
		}
		++__read_count;
		if (__temp == '\r') {
			__has_temp = 0;
			__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
			if __unlikely(__temp < 0)
				goto __err_or_eof;
			if (__temp != '\n') {
				__has_temp = 1;
			} else {
				++__read_count;
			}
		} else if (__libc_unicode_islf((__CHAR32_TYPE__)__temp)) {
			__has_temp = 0;
			/* ... */
		} else {
			goto __end_unget;
		}
		break;

	case ' ': /* Skip whitespace */
		if (__has_temp)
			goto __skip_whitespace_has_temp;
		for (;;) {
			__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
			if __unlikely(__temp < 0)
				goto __err_or_eof;
__skip_whitespace_has_temp:
			if (!__libc_unicode_isspace((__CHAR32_TYPE__)__temp)) {
				__has_temp = 1;
				goto __next;
			}
			++__read_count;
		}
		__builtin_unreachable();

	case '%': {
#undef __SCANF_FLAG_L
#define __SCANF_FLAG_SIGNED   0x0001
#define __SCANF_FLAG_UNSIGNED 0x0002
#define __SCANF_FLAG_INVERT   0x0004
#define __SCANF_FLAG_ISEOF    0x0020
#define __SCANF_FLAG_IGNORED  0x0040
#define __SCANF_FLAG_INSIDE   0x0080
#if (defined(__COMPILER_HAVE_LONGDOUBLE) &&   \
     (!defined(__NO_FPU) &&                   \
      !defined(__NO_SCANF_FLOATING_POINT)) && \
     (defined(__SIZEOF_LONG_LONG__)           \
      ? __SIZEOF_LONG_LONG__                  \
      : __SIZEOF_LONG_DOUBLE__) == __SIZEOF_LONG__)
#define __SCANF_FLAG_L        0x0100 /* 'L' was used */
#endif /* ... */


		__SIZE_TYPE__ __type_size;
		__SIZE_TYPE__ __width;
		__SIZE_TYPE__ __bufsize;
		unsigned int __flags;
		__type_size = 0;
		__width     = (__SIZE_TYPE__)-1;
		__bufsize   = (__SIZE_TYPE__)-1;
		__flags     = 0;
__next_mod:
		__ch = *__FORMAT_FORMAT++;
__next_mod_curr:
		switch (__ch) {
		case '\0':
			goto __end_maybe_unget;
		case '%':
			goto __match_ch;
		case '*':
			__flags |= __SCANF_FLAG_IGNORED;
			goto __next_mod;
		case '$':
			__bufsize = __builtin_va_arg(__FORMAT_ARGS, __SIZE_TYPE__);
			goto __next_mod;
		case 'h':
			__ch = *__FORMAT_FORMAT++;
			if (__ch == 'h') {
				__type_size = sizeof(char);
				__ch = *__FORMAT_FORMAT++;
			} else {
				__type_size = sizeof(short);
			}
			goto __next_mod_curr;
		case 'l':
			__ch = *__FORMAT_FORMAT++;
#if (defined(__LONGLONG) ||                  \
     (defined(__COMPILER_HAVE_LONGDOUBLE) && \
      (!defined(__NO_FPU) &&                 \
       !defined(__NO_SCANF_FLOATING_POINT))))
			if (__ch == 'l') {
		case 'L':
#ifdef __SIZEOF_LONG_LONG__
				__type_size = sizeof(__LONGLONG);
#else /* __SIZEOF_LONG_LONG__ */
				__type_size = __SIZEOF_LONG_DOUBLE__;
#endif /* !__SIZEOF_LONG_LONG__ */
#ifdef __SCANF_FLAG_L
				__flags |= __SCANF_FLAG_L;
#endif /* __SCANF_FLAG_L */
				__ch = *__FORMAT_FORMAT++;
			} else
#endif /* __LONGLONG || ... */
			{
				__type_size = sizeof(long);
			}
			goto __next_mod_curr;
		case 'j':
			__type_size = sizeof(__INTMAX_TYPE__);
			goto __next_mod;
		case 't':
			__flags |= __SCANF_FLAG_SIGNED;
			__type_size = sizeof(__PTRDIFF_TYPE__);
			goto __next_mod;
		case 'z':
			__flags |= __SCANF_FLAG_UNSIGNED;
			__type_size = sizeof(__SIZE_TYPE__);
			goto __next_mod;
		case 'I':
			__ch = *__FORMAT_FORMAT++;
			if (__ch == '8') {
				__type_size = 1;
				goto __next_mod;
			}
			if (__ch == '1' && *__FORMAT_FORMAT == '6') {
				__type_size = 2;
				++__FORMAT_FORMAT;
				goto __next_mod;
			}
			if (__ch == '3' && *__FORMAT_FORMAT == '2') {
				__type_size = 4;
				++__FORMAT_FORMAT;
				goto __next_mod;
			}
#ifdef __UINT64_TYPE__
			if (__ch == '6' && *__FORMAT_FORMAT == '4') {
				__type_size = 8;
				++__FORMAT_FORMAT;
				goto __next_mod;
			}
#endif /* __UINT64_TYPE__ */
			__type_size = sizeof(void *);
			goto __next_mod_curr;

		case 'n': {
			void *__dest;
			++__result;
			if (__flags & __SCANF_FLAG_IGNORED)
				break;
			__dest = __builtin_va_arg(__FORMAT_ARGS, void *);
			switch (__type_size) {
#if __SIZEOF_INT__ != 1
			case 1:
				*(__UINT8_TYPE__ *)__dest = (__UINT8_TYPE__)__read_count;
				break;
#endif /* __SIZEOF_INT__ != 1 */
#if __SIZEOF_INT__ != 2
			case 2:
				*(__UINT16_TYPE__ *)__dest = (__UINT16_TYPE__)__read_count;
				break;
#endif /* __SIZEOF_INT__ != 2 */
#if __SIZEOF_INT__ != 4
			case 4:
				*(__UINT32_TYPE__ *)__dest = (__UINT32_TYPE__)__read_count;
				break;
#endif /* __SIZEOF_INT__ != 4 */
#if defined(__UINT64_TYPE__) && __SIZEOF_INT__ != 8
			case 8:
				*(__UINT64_TYPE__ *)__dest = (__UINT64_TYPE__)__read_count;
				break;
#endif /* __UINT64_TYPE__ && __SIZEOF_INT__ != 8 */
			default:
				*(unsigned int *)__dest = (unsigned int)__read_count;
				break;
			}
		}	break;


		{
			unsigned int __radix;
#ifdef __UINT64_TYPE__
			__UINT64_TYPE__ __val;
#else /* __UINT64_TYPE__ */
			__UINT32_TYPE__ __val;
#endif /* !__UINT64_TYPE__ */
		case 'p':
			__radix = 16;
			if (__type_size == 0)
				__type_size = sizeof(void *);
			goto __do_scanf_integer_unsigned;
		case 'i':
			__radix = 0; /* Automatically determine radix */
			goto __do_scanf_integer_signed;
		case 'U': /* KOS Extension: auto-radix unsigned */
			__radix = 0;
			goto __do_scanf_integer_unsigned;
		case 'd':
			__radix = 10;
__do_scanf_integer_signed:
			if (!(__flags & __SCANF_FLAG_UNSIGNED))
				__flags |= __SCANF_FLAG_SIGNED;
			goto __do_scanf_integer;
		case 'o':
			__radix = 8;
			goto __do_scanf_integer_unsigned;
		case 'x':
		case 'X':
			__radix = 16;
			goto __do_scanf_integer_unsigned;
		case 'u':
			__radix = 10;
__do_scanf_integer_unsigned:
			if (!(__flags & __SCANF_FLAG_SIGNED))
				__flags |= __SCANF_FLAG_UNSIGNED;
__do_scanf_integer:
			if __unlikely(!__width) {
				__val = 0;
				goto __store_integer_val;
			}
			if (!__has_temp) {
__do_scanf_integer_read_initial:
				__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
				if __unlikely(__temp < 0)
					goto __err_or_eof;
			}
			if (__libc_unicode_isspace((__CHAR32_TYPE__)__temp)) {
				++__read_count;
				goto __do_scanf_integer_read_initial; /* Skip leading space */
			}
			if (!(__flags & __SCANF_FLAG_UNSIGNED)) {
				__flags &= ~__SCANF_FLAG_SIGNED;
				/* Process sign prefixes. */
				for (;;) {
					if (__temp == '-') {
						__flags ^= __SCANF_FLAG_SIGNED;
					} else if (__temp != '+') {
						break;
					}
					if __unlikely(!__width)
						goto __end;
					__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp < 0)
						goto __err_or_eof;
					++__read_count;
					--__width;
				}
			}
			__val = 0;
			if (__radix == 0) {
				/* Automatically determine the radix. */
				__radix = 10;
				if (__temp == '0') {
					if __unlikely(!__width)
						goto __store_integer_val_has_temp_no;
					__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp < 0) {
						if (__temp == __EOF) {
__store_integer_val_has_temp_no:
							__has_temp = 0;
							goto __store_integer_val; /* Store `0' */
						}
						goto __err;
					}
					++__read_count;
					--__width;
					__radix = 8;
					if (__temp == 'x' || __temp == 'X') {
						__radix = 16;
						goto __read_chr_after_radix_prefix;
					} else if (__temp == 'b' || __temp == 'B') {
						__radix = 2;
__read_chr_after_radix_prefix:
						if __unlikely(!__width)
							goto __end;
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0)
							goto __err_or_eof;
						++__read_count;
						--__width;
					} else {
						/* Remember that we've already parsed a `0' */
						__flags |= __SCANF_FLAG_INSIDE;
					}
				}
			}
			/* Parse the integer. */
			while (__width) {
				__UINT8_TYPE__ __digit;
				if (!__libc_unicode_asdigit((__CHAR32_TYPE__)__temp, __radix, &__digit))
					break; /* Invalid number for radix. */
				__val *= __radix; /* XXX: Overflow? */
				__val += __digit; /* XXX: Overflow? */
				__flags |= __SCANF_FLAG_INSIDE;
				__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
				if __unlikely(__temp < 0) {
					/* Special handling for EOF */
					if (__temp == __EOF) {
						__flags |= __SCANF_FLAG_ISEOF;
						if (__flags & __SCANF_FLAG_INSIDE)
							goto __store_integer_val;
						goto __end;
					}
					goto __err;
				}
				++__read_count;
				--__width;
			}
			__has_temp = 1;
			if (!(__flags & __SCANF_FLAG_INSIDE))
				goto __end_unget;
__store_integer_val:
			if (!(__flags & __SCANF_FLAG_IGNORED)) {
				void *__dest = __builtin_va_arg(__FORMAT_ARGS, void *);
				switch (__type_size) {
#if __SIZEOF_INT__ != 1
				case 1:
					if (__flags & __SCANF_FLAG_SIGNED)
						*(__INT8_TYPE__ *)__dest = -(__INT8_TYPE__)(__UINT8_TYPE__)__val;
					else {
						*(__UINT8_TYPE__ *)__dest = (__UINT8_TYPE__)__val;
					}
					break;
#endif /* __SIZEOF_INT__ != 1 */
#if __SIZEOF_INT__ != 2
				case 2:
					if (__flags & __SCANF_FLAG_SIGNED)
						*(__INT16_TYPE__ *)__dest = -(__INT16_TYPE__)(__UINT16_TYPE__)__val;
					else {
						*(__UINT16_TYPE__ *)__dest = (__UINT16_TYPE__)__val;
					}
					break;
#endif /* __SIZEOF_INT__ != 2 */
#if __SIZEOF_INT__ != 4
				case 4:
					if (__flags & __SCANF_FLAG_SIGNED)
						*(__INT32_TYPE__ *)__dest = -(__INT32_TYPE__)(__UINT32_TYPE__)__val;
					else {
						*(__UINT32_TYPE__ *)__dest = (__UINT32_TYPE__)__val;
					}
					break;
#endif /* __SIZEOF_INT__ != 4 */
#if defined(__UINT64_TYPE__) && __SIZEOF_INT__ != 8
				case 8:
					if (__flags & __SCANF_FLAG_SIGNED)
						*(__INT64_TYPE__ *)__dest = -(__INT64_TYPE__)(__UINT64_TYPE__)__val;
					else {
						*(__UINT64_TYPE__ *)__dest = (__UINT64_TYPE__)__val;
					}
					break;
#endif /* __UINT64_TYPE__ && __SIZEOF_INT__ != 8 */
				default:
					if (__flags & __SCANF_FLAG_SIGNED)
						*(int *)__dest = -(int)(unsigned int)__val;
					else {
						*(unsigned int *)__dest = (unsigned int)__val;
					}
					break;
				}
			}
			++__result;
			if (__flags & __SCANF_FLAG_ISEOF)
				goto __end;
		}	break;


		case 's': {
			char *__dst;
			/* [OPT] bufsize = va_arg(size_t)
			 * READ_NON_WHITESPACE(maxchars: __width)
			 * WRITE_UTF8(dst: va_arg(char *), maxbytes: bufsize)
			 * >> char buf[128];
			 * >> char const *data = "name = foobar";
			 * >> sscanf(data, "name = %$s", sizeof(buf), buf);
			 * >> printf("buf = %s\n", buf);
			 * NOTE: If the given buffer is of insufficient size, a match failure is indicated!
			 * NOTE: We also NUL-terminate the given buffer (with the given bufsize including memory required for that) */
			if (__flags & __SCANF_FLAG_IGNORED) {
				if (__width) {
					if (!__has_temp) {
__do_scanf_string_ignored_read_initial:
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0)
							goto __err_or_eof;
					}
					if (__libc_unicode_isspace((__CHAR32_TYPE__)__temp)) {
						++__read_count;
						goto __do_scanf_string_ignored_read_initial; /* Skip leading space */
					}
					for (;;) {
						if (!__width)
							break;
						if (__libc_unicode_isspace((__CHAR32_TYPE__)__temp))
							break;
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0)
							goto __err_or_eof;
						++__read_count;
						--__width;
					}
					__has_temp = 1;
				}
			} else {
				/* TODO: `%$I16s' --> Store into a utf-16 target buffer */
				/* TODO: `%$I32s' --> Store into a utf-32 target buffer */
				__dst = __builtin_va_arg(__FORMAT_ARGS,char *);
				if (!__bufsize)
					break;
				if (__width) {
					if (!__has_temp) {
__do_scanf_string_read_initial:
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0) {
							if (__temp != __EOF)
								goto __err;
__done_string_terminate_eof:
							*__dst = '\0'; /* Terminate the target buffer. */
							++__result;
							goto __end;
						}
					}
					if (__libc_unicode_isspace((__CHAR32_TYPE__)__temp)) {
						++__read_count;
						goto __do_scanf_string_read_initial; /* Skip leading space */
					}
					for (;;) {
						char __buf[__LIBC_UNICODE_UTF8_CURLEN];
						__SIZE_TYPE__ __cnt;
						if (!__width)
							break;
						if (__libc_unicode_isspace((__CHAR32_TYPE__)__temp))
							break;
						__cnt = (__SIZE_TYPE__)(__libc_unicode_writeutf8(__buf, (__CHAR32_TYPE__)__temp) - __buf);
						if (__cnt >= __bufsize) /* >=, so we always keep some space for the trailing `\0' */
							goto __end_unget; /* Buffer too small... */
						__libc_memcpyc(__dst, __buf, __cnt, sizeof(char));
						__dst += __cnt;
						__bufsize -= __cnt;
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0) {
							if __likely(__temp == __EOF)
								goto __done_string_terminate_eof;
							goto __err;
						}
						++__read_count;
						--__width;
					}
					__has_temp = 1;
				}
				*__dst = '\0'; /* Terminate the target buffer. */
			}
			++__result;
		}	break;

		case '[': {
			char *__dst;
			__CHAR_TYPE const *__pattern_start;
			__CHAR_TYPE const *__iter;
			__CHAR32_TYPE__ __pat_ch, __pat_ch2;
			/* [OPT] bufsize = va_arg(size_t)
			 * READ_MATCHING_CHARACTERS(maxchars: __width)
			 * WRITE_UTF8(dst: va_arg(char *), maxbytes: bufsize) */
			while (*__FORMAT_FORMAT == '^') {
				__flags ^= __SCANF_FLAG_INVERT;
				++__FORMAT_FORMAT;
			}
			__pattern_start = __FORMAT_FORMAT;
			while (*__FORMAT_FORMAT && *__FORMAT_FORMAT != ']')
				++__FORMAT_FORMAT;
			if (__flags & __SCANF_FLAG_IGNORED) {
				if (__width) {
					if (!__has_temp) {
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0)
							goto __err_or_eof;
					}
					for (;;) {
						if (!__width)
							break;
						for (__iter = __pattern_start; __iter < __FORMAT_FORMAT;) {
							__pat_ch = __PRIVATE_FORMAT_SCANF_READUNI(&__iter, __FORMAT_FORMAT);
							if ((__CHAR32_TYPE__)__temp == __pat_ch)
								goto __pattern_skip_has_char;
							if (*__iter == '-') {
								++__iter;
								__pat_ch2 = __PRIVATE_FORMAT_SCANF_READUNI(&__iter, __FORMAT_FORMAT);
								if ((__CHAR32_TYPE__)__temp >= __pat_ch && (__CHAR32_TYPE__)__temp <= __pat_ch2)
									goto __pattern_skip_has_char;
							}
						}
						break;
__pattern_skip_has_char:
						if (__libc_unicode_isspace((__CHAR32_TYPE__)__temp))
							break;
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0)
							goto __err_or_eof;
						++__read_count;
						--__width;
					}
					__has_temp = 1;
				}
			} else {
				/* TODO: `%$I16s' --> Store into a utf-16 target buffer */
				/* TODO: `%$I32s' --> Store into a utf-32 target buffer */
				__dst = __builtin_va_arg(__FORMAT_ARGS, char *);
				if (!__bufsize)
					break;
				if (__width) {
					if (!__has_temp) {
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0) {
							if (__temp != __EOF)
								goto __err;
__done_pattern_terminate_eof:
							*__dst = '\0'; /* Terminate the target buffer. */
							++__result;
							goto __end;
						}
					}
					for (;;) {
						char __buf[__LIBC_UNICODE_UTF8_CURLEN];
						__SIZE_TYPE__ __cnt;
						if (!__width)
							break;
						for (__iter = __pattern_start; __iter < __FORMAT_FORMAT;) {
							__pat_ch = __PRIVATE_FORMAT_SCANF_READUNI(&__iter, __FORMAT_FORMAT);
							if ((__CHAR32_TYPE__)__temp == __pat_ch)
								goto __pattern_has_char;
							if (*__iter == '-') {
								++__iter;
								__pat_ch2 = __PRIVATE_FORMAT_SCANF_READUNI(&__iter, __FORMAT_FORMAT);
								if ((__CHAR32_TYPE__)__temp >= __pat_ch && (__CHAR32_TYPE__)__temp <= __pat_ch2)
									goto __pattern_has_char;
							}
						}
						break;
__pattern_has_char:
						__cnt = (__SIZE_TYPE__)(__libc_unicode_writeutf8(__buf, (__CHAR32_TYPE__)__temp) - __buf);
						if (__cnt >= __bufsize) /* >=, so we always keep some space for the trailing `\0' */
							goto __end_unget; /* Buffer too small... */
						__libc_memcpy(__dst, __buf, __cnt);
						__dst += __cnt;
						__bufsize -= __cnt;
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0) {
							if __likely(__temp == __EOF)
								goto __done_pattern_terminate_eof;
							goto __err;
						}
						++__read_count;
						--__width;
					}
					__has_temp = 1;
				}
				*__dst = '\0'; /* Terminate the target buffer. */
			}
			++__result;
			if (*__FORMAT_FORMAT)
				++__FORMAT_FORMAT; /* Skip `]' */
		}	break;


		case 'c': {
			if (__width == (__SIZE_TYPE__)-1)
				__width = 1;
			if (__flags & __SCANF_FLAG_IGNORED) {
				if __unlikely(!__width)
					break;
				if (!__has_temp)
					goto __read_temp_for_ignored_format_c;
				for (;;) {
					++__read_count;
					--__width;
					if (!__width)
						break;
__read_temp_for_ignored_format_c:
					__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp < 0)
						goto __err_or_eof;
				}
			} else {
				unsigned char *__dest;
				__dest = __builtin_va_arg(__FORMAT_ARGS, unsigned char *);
				if __unlikely(!__width)
					break;
				if (!__has_temp)
					goto __read_temp_for_format_c;
				/* TODO: If given, limit the max # of bytes written to `__dest'
				 *       when  `__type_size != 0' to at most `__bufsize' bytes!
				 *       Stop scanning if the buffer size would be exceeded. */
				for (;;) {
					/* Truncate read characters */
					if (__type_size == 0) {
__write_temp_for_format_c:
						*__dest++ = (unsigned char)(__CHAR32_TYPE__)__temp;
					} else if (__type_size == 1) {
						/* `%I8c' (store UTF-8 characters into a `uint8_t *') */
						__dest = (unsigned char *)__libc_unicode_writeutf8((char *)__dest, (__CHAR32_TYPE__)__temp);
					} else if (__type_size == 2) {
						/* `%I16c' (store UTF-16 characters into a `uint16_t *') */
						__dest = (unsigned char *)__libc_unicode_writeutf16((__CHAR16_TYPE__ *)__dest, (__CHAR32_TYPE__)__temp);
					} else if (__type_size == 4 || __type_size == 8) {
						/* `%I32c' (store UTF-32 characters into a `uint32_t *') */
						/* `%I64c' (store UTF-32 characters into a `uint64_t *') */
						*(__CHAR32_TYPE__ *)__dest = (__CHAR32_TYPE__)__temp;
						__dest += 4;
						if (__type_size == 8) {
							*(__CHAR32_TYPE__ *)__dest = 0;
							__dest += 4;
						}
					} else {
						goto __write_temp_for_format_c;
					}
					++__read_count;
					--__width;
					if (!__width)
						break;
__read_temp_for_format_c:
					__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp < 0)
						goto __err_or_eof;
				}
			}
			__has_temp = 0;
			++__result;
		}	break;



#if (!defined(__NO_FPU) && \
     !defined(__NO_SCANF_FLOATING_POINT))
		case 'f':
		case 'e':
		case 'g':
		case 'E':
		case 'a': {
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FP_VAL_TYPE __LONGDOUBLE
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FP_VAL_TYPE double
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
			__FP_VAL_TYPE __val = 0;
			__BOOL __isneg = 0;
			if (!__has_temp) {
__fp_do_read_initial:
				__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
				if __unlikely(__temp < 0)
					goto __err_or_eof;
			}
			if (__libc_unicode_isspace((__CHAR32_TYPE__)__temp)) {
				++__read_count;
				goto __fp_do_read_initial; /* Skip leading space */
			}
			if (__temp == '-') {
				__isneg = 1;
				goto __do_consume_fp_sign;
			} else if (__temp == '+') {
__do_consume_fp_sign:
				++__read_count;
				__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
				if __unlikely(__temp < 0)
					goto __err_or_eof;
			}
#ifdef __NANL
			if (__temp == 'n' || __temp == 'N') {
				__SSIZE_TYPE__ __temp2, __temp3;
				__temp2 = (*__FORMAT_PGETC)(__FORMAT_ARG);
				if __unlikely(__temp2 < 0) {
					if (__temp2 != __EOF)
						return __temp2;
					__temp = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp);
					if __unlikely(__temp < 0)
						goto __err;
					goto __end;
				}
				if (__temp2 == 'a' || __temp == 'A') {
					__temp3 = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp3 < 0) {
						if (__temp3 != __EOF)
							return __temp3;
						__temp2 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp2);
						if __unlikely(__temp2 < 0)
							return __temp2;
						__temp = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp);
						if __unlikely(__temp < 0)
							goto __err;
						goto __end;
					}
					if (__temp3 == 'n' || __temp3 == 'N') {
						__val = __NANL;
						__has_temp = 0;
						__read_count += 3;
					} else {
						__temp3 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp3);
						if __unlikely(__temp3 < 0)
							return __temp3;
						__temp2 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp2);
						if __unlikely(__temp2 < 0)
							return __temp2;
						__has_temp = 1;
					}
				} else {
					__temp2 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp2);
					if __unlikely(__temp2 < 0)
						return __temp2;
					__has_temp = 1;
				}
			} else
#endif /* __NANL */
#ifdef __INFINITYL
			if (__temp == 'i' || __temp == 'I') {
				__SSIZE_TYPE__ __temp2, __temp3;
				__temp2 = (*__FORMAT_PGETC)(__FORMAT_ARG);
				if __unlikely(__temp2 < 0) {
					if (__temp2 != __EOF)
						return __temp2;
					__temp = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp);
					if __unlikely(__temp < 0)
						goto __err;
					goto __end;
				}
				if (__temp2 == 'n' || __temp == 'N') {
					__temp3 = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp3 < 0) {
						if (__temp3 != __EOF)
							return __temp3;
						__temp2 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp2);
						if __unlikely(__temp2 < 0)
							return __temp2;
						__temp = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp);
						if __unlikely(__temp < 0)
							goto __err;
						goto __end;
					}
					if (__temp3 == 'f' || __temp3 == 'F') {
						__val = __INFINITYL;
						__has_temp = 0;
						__read_count += 3;
					} else {
						__temp3 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp3);
						if __unlikely(__temp3 < 0)
							return __temp3;
						__temp2 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp2);
						if __unlikely(__temp2 < 0)
							return __temp2;
						__has_temp = 1;
					}
				} else {
					__temp2 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp2);
					if __unlikely(__temp2 < 0)
						return __temp2;
					__has_temp = 1;
				}
			} else
#endif /* __INFINITYL */
			{
				__CHAR_TYPE __fp_expch = 'e';
				__CHAR_TYPE __fp_expch2 = 'E';
				__FP_VAL_TYPE __fp_basef = 10;
				unsigned int __fp_basei = 10;
				__SIZE_TYPE__ __fp_start;
				__INTMAX_TYPE__ __exp_power = 0;
				__has_temp = 1;
				if (__temp == '0') {
					/* Check for hex floating point values. */
					++__read_count;
					__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp < 0)
						goto __err_or_eof;
					if (__temp == 'x' || __temp == 'X') {
						__fp_basef = 16;
						__fp_basei = 16;
						__fp_expch = 'p';
						__fp_expch2 = 'P';
						++__read_count;
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0)
							goto __err_or_eof;
					}
				}
__fp_loop:
				__fp_start = __read_count;
				for (;;) {
					__UINT8_TYPE__ __digit;
					if (!__libc_unicode_asdigit((__CHAR32_TYPE__)__temp, __fp_basei, &__digit))
						break;
					__val = __val * __fp_basef + (__FP_VAL_TYPE)__digit;
					++__read_count;
					__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp < 0) {
						/* Special handling for EOF */
						if (__temp == __EOF) {
							__has_temp = 0;
							break;
						}
						goto __err_or_eof;
					}
				}
				if (!__exp_power && __temp == '.') {
					++__read_count; /* Consume the '.' */
					__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp < 0)
						goto __err_or_eof;
					__exp_power = 1;
					goto __fp_loop;
				}
				if (__exp_power)
					__exp_power = __read_count - __fp_start;
				if (__temp == __fp_expch || __temp == __fp_expch2) {
					__SSIZE_TYPE__ __temp2;
					__BOOL __exp_negative = 0;
					__INTMAX_TYPE__ __exp_addend;
					/* An explicit exponent may have been given. */
					__temp2 = (*__FORMAT_PGETC)(__FORMAT_ARG);
					if __unlikely(__temp2 < 0) {
						if (__temp2 != __EOF)
							return __temp2;
						__temp = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp);
						if __unlikely(__temp < 0)
							goto __err;
						goto __end;
					}
					if (__temp2 == '-' || __temp2 == '+') {
						__SSIZE_TYPE__ __temp3;
						__exp_negative = __temp2 == '-';
						__temp3 = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp3 < 0) {
							if (__temp3 != __EOF)
								return __temp3;
							__temp2 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp2);
							if __unlikely(__temp2 < 0)
								return __temp2;
							__temp = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp);
							if __unlikely(__temp < 0)
								goto __err;
							goto __end;
						}
						if (!(__temp3 >= '0' && __temp3 <= '9')) {
							__temp3 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp3);
							if __unlikely(__temp3 < 0)
								return __temp3;
							__temp2 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp2);
							if __unlikely(__temp2 < 0)
								return __temp2;
							goto __fp_no_exp_addend;
						}
						++__read_count; /* Consume the '+' or '-' */
						__temp2 = __temp3;
					} else {
						if (!(__temp2 >= '0' && __temp2 <= '9')) {
							__temp2 = (*__FORMAT_PUNGETC)(__FORMAT_ARG, __temp2);
							if __unlikely(__temp2 < 0)
								return __temp2;
							goto __fp_no_exp_addend;
						}
					}
					__temp = __temp2;
					++__read_count; /* Consume the '.' */
					__exp_addend = 0;
					for (;;) {
						if (__temp >= '0' && __temp <= '9') {
							__exp_addend = (__exp_addend * 10) +
							               (__temp - '0');
						} else {
							break;
						}
						++__read_count; /* Consume digit */
						__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
						if __unlikely(__temp < 0) {
							/* Special handling for EOF */
							if (__temp == __EOF) {
								__has_temp = 0;
								break;
							}
							goto __err;
						}
					}
					if (__exp_negative)
						__exp_addend = -__exp_addend;
					__exp_power -= __exp_addend;
				}
__fp_no_exp_addend:
				if (__exp_power != 0) {
					__UINTMAX_TYPE__ __exp_abs;
					/* >> result = __val / (__fp_basef ^ __exp_power) */
					__exp_abs = (__UINTMAX_TYPE__)__exp_power;
					if (__exp_power < 0)
						__exp_abs = (__UINTMAX_TYPE__)0 - __exp_abs;
					while (__exp_abs) {
						if (__exp_abs & 1) {
							if (__exp_power < 0) {
								__val = __val * __fp_basef;
							} else {
								__val = __val / __fp_basef;
							}
						}
						__exp_abs >>= 1;
						__fp_basef = __fp_basef * __fp_basef;
					}
				}
			}
			if (__isneg)
				__val = -__val;
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __SCANF_FLAG_L
			if (__flags & __SCANF_FLAG_L)
#elif defined(__SIZEOF_LONG_LONG__)
			if (__type_size == __SIZEOF_LONG_LONG__)
#else /* ... */
			if (__type_size == __SIZEOF_LONG_DOUBLE__)
#endif /* !... */
			{
				/* Result pointer is a long-double */
				__LONGDOUBLE *__dst;
				__dst = __builtin_va_arg(__FORMAT_ARGS, __LONGDOUBLE *);
				*__dst = (__LONGDOUBLE)__val;
			} else
#endif /* __COMPILER_HAVE_LONGDOUBLE */
			if (__type_size == __SIZEOF_LONG__) {
				/* Result pointer is a double */
				double *__dst;
				__dst = __builtin_va_arg(__FORMAT_ARGS, double *);
				*__dst = (double)__val;
			} else {
				/* Result pointer is a float */
				float *__dst;
				__dst = __builtin_va_arg(__FORMAT_ARGS, float *);
				*__dst = (float)__val;
			}
			++__result;
		}	break;
#endif /* !__NO_FPU && !__NO_SCANF_FLOATING_POINT */



		default:
			if (__ch >= '0' && __ch <= '9') {
				__width = (__SIZE_TYPE__)(__ch - '0');
				for (;;) {
					__ch = *__FORMAT_FORMAT++;
					if (__ch < '0' || __ch > '9')
						goto __next_mod_curr;
					__width *= 10;
					__width += (__SIZE_TYPE__)(__ch - '0');
				}
			}
			break;
		}
#undef __SCANF_FLAG_L
#undef __SCANF_FLAG_INSIDE
#undef __SCANF_FLAG_IGNORED
#undef __SCANF_FLAG_ISEOF
#undef __SCANF_FLAG_UNSIGNED
#undef __SCANF_FLAG_INVERT
#undef __SCANF_FLAG_SIGNED
	}	break;

	default:
		/* Default: match characters exactly. */
__match_ch:
		if (!__has_temp) {
			__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
			if __unlikely(__temp < 0)
				goto __err_or_eof;
		}
		if (__temp != __ch)
			goto __end_unget;
		++__read_count;
		__has_temp = 0;
		break;
	}
	goto __next;
__end_maybe_unget:
	if (__has_temp) {
__end_unget:
		__temp = (*__FORMAT_PUNGETC)(__FORMAT_ARG, (__CHAR32_TYPE__)__temp);
		if (__temp < 0)
			goto __err;
	}
__end:
	return __result;
__err_or_eof:
	if (__temp == __EOF)
		goto __end;
__err:
	return __temp;
#undef __PRIVATE_FORMAT_SCANF_READUNI
}


#undef __FORMAT_ARGS
#undef __FORMAT_FORMAT
#undef __FORMAT_ARG
#undef __FORMAT_PUNGETC
#undef __FORMAT_PGETC
#undef __CHAR_SIZE
#undef __CHAR_TYPE
