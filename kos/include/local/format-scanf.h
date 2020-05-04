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
#ifndef __FORMAT_UNICODE_WRITEUTF8
#define __FORMAT_UNICODE_WRITEUTF8 unicode_writeutf8
#endif /* !__FORMAT_UNICODE_WRITEUTF8 */
#ifndef __FORMAT_UNICODE_WRITEUTF16
#define __FORMAT_UNICODE_WRITEUTF16 unicode_writeutf16
#endif /* !__FORMAT_UNICODE_WRITEUTF16 */

#include <hybrid/typecore.h>

#ifndef __EOF
#ifdef EOF
#define __EOF  EOF
#else /* EOF */
#define __EOF (-1)
#endif /* !EOF */
#endif /* !__EOF */

#include <hybrid/typecore.h>

{
	__size_t __read_count = 0;
	__ssize_t __result = 0;
	__ssize_t __temp = 0; /* XXX: Unused init! */
	__BOOL __has_temp = 0;
	__CHAR_TYPE __ch;
__next:
	__ch = *__FORMAT_FORMAT++;
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
#define __SCANF_FLAG_SIGNED   0x01
#define __SCANF_FLAG_UNSIGNED 0x02
#define __SCANF_FLAG_INVERT   0x04
#define __SCANF_FLAG_ISEOF    0x20
#define __SCANF_FLAG_IGNORED  0x40
#define __SCANF_FLAG_INSIDE   0x80
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
			__bufsize = __builtin_va_arg(__FORMAT_ARGS,__SIZE_TYPE__);
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
#ifdef __LONGLONG
			if (__ch == 'l') {
				__type_size = sizeof(__LONGLONG);
				__ch = *__FORMAT_FORMAT++;
			} else
#endif /* __LONGLONG */
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
		case 'L':
			/* NOTE: Also functions as `long long' for d,i,o,u or x */
			__type_size = (__SIZE_TYPE__)__ch;
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
				__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
				if __unlikely(__temp < 0)
					goto __err_or_eof;
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
				if (__libc_unicode_isdecimal((__CHAR32_TYPE__)__temp))
					__digit = __libc_unicode_asdigit((__CHAR32_TYPE__)__temp);
				else if ((__CHAR32_TYPE__)__temp >= 'A' && (__CHAR32_TYPE__)__temp <= 'F')
					__digit = 10 + ((__UINT8_TYPE__)__temp - 'A');
				else if ((__CHAR32_TYPE__)__temp >= 'a' && (__CHAR32_TYPE__)__temp <= 'f')
					__digit = 10 + ((__UINT8_TYPE__)__temp - 'a');
				else {
					break;
				}
				if (__digit >= __radix)
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
			 * WRITE_UTF8(dst: va_arg(char *),maxbytes: bufsize)
			 * >> char buf[128];
			 * >> char const *data = "name = foobar";
			 * >> sscanf(data,"name = %$s",sizeof(buf),buf);
			 * >> printf("buf = %s\n",buf);
			 * NOTE: If the given buffer is of insufficient size, a match failure is indicated!
			 * NOTE: We also NUL-terminate the given buffer (with the given bufsize including memory required for that) */
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
				/* XXX: `%$I16s' --> Store into a utf-16 target buffer */
				/* XXX: `%$I32s' --> Store into a utf-32 target buffer */
				__dst = __builtin_va_arg(__FORMAT_ARGS,char *);
				if (!__bufsize)
					break;
				if (__width) {
					if (!__has_temp) {
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
					for (;;) {
						char __buf[__LIBC_UNICODE_UTF8_CURLEN];
						__SIZE_TYPE__ __cnt;
						if (!__width)
							break;
						if (__libc_unicode_isspace((__CHAR32_TYPE__)__temp))
							break;
						__cnt = (__SIZE_TYPE__)(__libc_unicode_writeutf8(__buf,(__CHAR32_TYPE__)__temp) - __buf);
						if (__cnt >= __bufsize) /* >=, so we always keep some space for the trailing `\0' */
							goto __end_unget; /* Buffer too small... */
						__libc_memcpy(__dst,__buf,__cnt);
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
			__CHAR32_TYPE__ __pat_ch,__pat_ch2;
			/* [OPT] bufsize = va_arg(size_t)
			 * READ_MATCHING_CHARACTERS(maxchars: __width)
			 * WRITE_UTF8(dst: va_arg(char *),maxbytes: bufsize) */
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
							__pat_ch = __libc_unicode_readutf8_n((char const **)&__iter,__FORMAT_FORMAT);
							if ((__CHAR32_TYPE__)__temp == __pat_ch)
								goto __pattern_skip_has_char;
							if (*__iter == '-') {
								++__iter;
								__pat_ch2 = __libc_unicode_readutf8_n((char const **)&__iter,__FORMAT_FORMAT);
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
				/* XXX: `%$I16s' --> Store into a utf-16 target buffer */
				/* XXX: `%$I32s' --> Store into a utf-32 target buffer */
				__dst = __builtin_va_arg(__FORMAT_ARGS,char *);
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
							__pat_ch = __libc_unicode_readutf8_n((char const **)&__iter,__FORMAT_FORMAT);
							if ((__CHAR32_TYPE__)__temp == __pat_ch)
								goto __pattern_has_char;
							if (*__iter == '-') {
								++__iter;
								__pat_ch2 = __libc_unicode_readutf8_n((char const **)&__iter,__FORMAT_FORMAT);
								if ((__CHAR32_TYPE__)__temp >= __pat_ch && (__CHAR32_TYPE__)__temp <= __pat_ch2)
									goto __pattern_has_char;
							}
						}
						break;
__pattern_has_char:
						__cnt = (__SIZE_TYPE__)(__libc_unicode_writeutf8(__buf,(__CHAR32_TYPE__)__temp) - __buf);
						if (__cnt >= __bufsize) /* >=, so we always keep some space for the trailing `\0' */
							goto __end_unget; /* Buffer too small... */
						__libc_memcpy(__dst,__buf,__cnt);
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
			unsigned char *__dest;
			if (__width == (__SIZE_TYPE__)-1)
				__width = 1;
			__dest = __builtin_va_arg(__FORMAT_ARGS, unsigned char *);
			if __unlikely(!__width)
				break;
			if (!__has_temp)
				goto __read_temp_for_format_c;
			/* TODO: If given, limit the max # of bytes written to `__dest'
			 *       when `__type_size != 0' to at most `__bufsize' bytes!
			 *       Stop scanning if the buffer size would be exceeded. */
			for (;;) {
				/* Truncate read characters */
				if (__type_size == 0) {
__write_temp_for_format_c:
					*__dest++ = (unsigned char)(__CHAR32_TYPE__)__temp;
				} else if (__type_size == 1) {
					/* `%I8c' (store UTF-8 characters into a `uint8_t *') */
					__dest = (unsigned char *)__FORMAT_UNICODE_WRITEUTF8((char *)__dest, (__CHAR32_TYPE__)__temp);
				} else if (__type_size == 2) {
					/* `%I16c' (store UTF-16 characters into a `uint16_t *') */
					__dest = (unsigned char *)__FORMAT_UNICODE_WRITEUTF16((__CHAR16_TYPE__ *)__dest, (__CHAR32_TYPE__)__temp);
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
				--__width;
				if (!__width)
					break;
__read_temp_for_format_c:
				__temp = (*__FORMAT_PGETC)(__FORMAT_ARG);
				if __unlikely(__temp < 0)
					goto __err_or_eof;
			}
			__has_temp = 0;
			++__result;
		}	break;

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
	}	break;
#undef __SCANF_FLAG_INSIDE
#undef __SCANF_FLAG_IGNORED
#undef __SCANF_FLAG_ISEOF
#undef __SCANF_FLAG_UNSIGNED
#undef __SCANF_FLAG_INVERT
#undef __SCANF_FLAG_SIGNED

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
		__temp = (*__FORMAT_PUNGETC)(__FORMAT_ARG,(__CHAR32_TYPE__)__temp);
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
}


#undef __FORMAT_UNICODE_WRITEUTF8
#undef __FORMAT_UNICODE_WRITEUTF16
#undef __FORMAT_ARGS
#undef __FORMAT_FORMAT
#undef __FORMAT_ARG
#undef __FORMAT_PUNGETC
#undef __FORMAT_PGETC
#undef __CHAR_SIZE
#undef __CHAR_TYPE
