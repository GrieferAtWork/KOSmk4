/* HASH CRC-32:0x34a549ad */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strsenvisx_defined
#define __local_strsenvisx_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isalnum_defined
#define __local___localdep_isalnum_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isalnum) && defined(__CRT_HAVE_isalnum)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalnum,(int __ch),isalnum,{ return __crt_isalnum(__ch); })
#elif defined(__crt_isalnum)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isalnum)(int __ch) { return __crt_isalnum(__ch); }
#elif __has_builtin(__builtin_isalnum) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalnum)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalnum,(int __ch),isalnum,{ return __builtin_isalnum(__ch); })
#elif defined(__CRT_HAVE_isalnum)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isalnum,(int __ch),isalnum,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isalnum.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isalnum __LIBC_LOCAL_NAME(isalnum)
#endif /* !... */
#endif /* !__local___localdep_isalnum_defined */
#ifndef __local___localdep_iscntrl_defined
#define __local___localdep_iscntrl_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iscntrl) && defined(__CRT_HAVE_iscntrl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iscntrl,(int __ch),iscntrl,{ return __crt_iscntrl(__ch); })
#elif defined(__crt_iscntrl)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_iscntrl)(int __ch) { return __crt_iscntrl(__ch); }
#elif __has_builtin(__builtin_iscntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iscntrl)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iscntrl,(int __ch),iscntrl,{ return __builtin_iscntrl(__ch); })
#elif defined(__CRT_HAVE_iscntrl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iscntrl,(int __ch),iscntrl,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/iscntrl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iscntrl __LIBC_LOCAL_NAME(iscntrl)
#endif /* !... */
#endif /* !__local___localdep_iscntrl_defined */
#ifndef __local___localdep_isgraph_defined
#define __local___localdep_isgraph_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isgraph) && defined(__CRT_HAVE_isgraph)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph,(int __ch),isgraph,{ return __crt_isgraph(__ch); })
#elif defined(__crt_isgraph)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isgraph)(int __ch) { return __crt_isgraph(__ch); }
#elif __has_builtin(__builtin_isgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isgraph)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph,(int __ch),isgraph,{ return __builtin_isgraph(__ch); })
#elif defined(__CRT_HAVE_isgraph)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isgraph,(int __ch),isgraph,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isgraph.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isgraph __LIBC_LOCAL_NAME(isgraph)
#endif /* !... */
#endif /* !__local___localdep_isgraph_defined */
#ifndef __local___localdep_isspace_defined
#define __local___localdep_isspace_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isspace) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __crt_isspace(__ch); })
#elif defined(__crt_isspace)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isspace)(int __ch) { return __crt_isspace(__ch); }
#elif __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isspace __LIBC_LOCAL_NAME(isspace)
#endif /* !... */
#endif /* !__local___localdep_isspace_defined */
#ifndef __local___localdep_strchr_defined
#define __local___localdep_strchr_defined
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_index)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchr __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#endif /* !__local___localdep_strchr_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/vis.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strsenvisx) __ATTR_IN(6) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strsenvisx))(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __srclen, int __flags, char const *__mbextra, int *__cerr_ptr) {
	__BYTE_TYPE__ *__writer, *__dstend;
	char const *__src_end = __src + __srclen;
	(void)__cerr_ptr; /* Unused in this implementation (something about multi-byte characters?) */
	__writer = (__BYTE_TYPE__ *)__dst;
	__dstend = (__BYTE_TYPE__ *)__dst + __dstsize;
__handle_next_byte:
	while (__src < __src_end) {
		__BYTE_TYPE__ __byte = (__BYTE_TYPE__)*__src++;
		__BYTE_TYPE__ __next = (__src < __src_end || (__flags & __VIS_SRCEXTRA)) ? *__src : 0;
		if (__flags & __VIS_HTTPSTYLE) {
			if ((__NAMESPACE_LOCAL_SYM __localdep_isalnum)(__byte))
				goto __encode_byte;
			if ((__NAMESPACE_LOCAL_SYM __localdep_strchr)("$-_.+!*'(),", __byte))
				goto __encode_byte;
			/* Must encode as "%AB" */
			if __unlikely((__SIZE_TYPE__)(__dstend - __writer) < 3)
				goto __err_nospace;
			*__writer++ = '%';
			*__writer++ = __LOCAL_itoa_digit(0, (__byte & 0xf0) >> 4);
			*__writer++ = __LOCAL_itoa_digit(0, (__byte & 0x0f));
			goto __handle_next_byte;
		} else if (__flags & __VIS_MIMESTYLE) {
			if (__byte == '\n')
				goto __encode_byte;
			if ((__NAMESPACE_LOCAL_SYM __localdep_isspace)(__byte)) {
				/* Only have to escape space if followed by a line-feed */
				if (__next != '\r' && __next != '\n')
					goto __encode_byte;
			} else if ((__NAMESPACE_LOCAL_SYM __localdep_strchr)("#$@[\\]^`{|}~=", __byte) != __NULLPTR) {
				/* Always have to escape these. */
			} else {
				if (__byte >= 0x20 && __byte <= 0x7e)
					goto __encode_byte; /* Normal ASCII doesn't need to be escaped. */
			}
			*__writer++ = '=';
			*__writer++ = __LOCAL_itoa_digit(1, (__byte & 0xf0) >> 4);
			*__writer++ = __LOCAL_itoa_digit(1, (__byte & 0x0f));
			goto __handle_next_byte;
		}

__encode_byte:
		if __unlikely(__writer == __dstend)
			goto __err_nospace;
		/* Check if `byte' may not need to be escaped. */
		if ((__NAMESPACE_LOCAL_SYM __localdep_isgraph)(__byte) || (__NAMESPACE_LOCAL_SYM __localdep_strchr)("\t\n ", __byte) ||
		    ((__flags & __VIS_SAFE) && (__NAMESPACE_LOCAL_SYM __localdep_strchr)("\x08\x07\r", __byte))) {
			if ((__NAMESPACE_LOCAL_SYM __localdep_strchr)(__mbextra, __byte))
				goto __escape_byte;
			if ((__flags & __VIS_GLOB) && (__NAMESPACE_LOCAL_SYM __localdep_strchr)("*?[#", __byte))
				goto __escape_byte;
			if ((__flags & __VIS_SHELL) && (__NAMESPACE_LOCAL_SYM __localdep_strchr)("'`\";&<>()|{}]\\$!^~", __byte))
				goto __escape_byte;
			if ((__flags & __VIS_SP) && __byte == ' ')
				goto __escape_byte;
			if ((__flags & __VIS_TAB) && __byte == '\t')
				goto __escape_byte;
			if ((__flags & __VIS_NL) && __byte == '\n')
				goto __escape_byte;
			if ((__flags & __VIS_DQ) && __byte == '"')
				goto __escape_byte;
			if (!(__flags & __VIS_NOSLASH) && __byte == '\\')
				goto __escape_byte;

			/* Allowed to directly encode `byte' */
			*__writer++ = __byte;
			goto __handle_next_byte;
		}

__escape_byte:
		/* Must escape `byte' */
		if (__flags & __VIS_CSTYLE) {
			switch (__byte) {

			case 0x0a: __byte = 'n'; goto __escape_bk_byte;
			case 0x0d: __byte = 'r'; goto __escape_bk_byte;
			case 0x08: __byte = 'b'; goto __escape_bk_byte;
			case 0x07: __byte = 'a'; goto __escape_bk_byte;
			case 0x0b: __byte = 'v'; goto __escape_bk_byte;
			case 0x09: __byte = 't'; goto __escape_bk_byte;
			case 0x0c: __byte = 'f'; goto __escape_bk_byte;
			case 0x20: __byte = 's'; goto __escape_bk_byte;
			case 0x1b: __byte = 'E'; goto __escape_bk_byte;
			case 0x00:
				if __unlikely((__SIZE_TYPE__)(__dstend - __writer) < 2)
					goto __err_nospace;
				*__writer++ = '\\';
				*__writer++ = '0';
				if (__next >= '0' && __next <= '0') {
					if __unlikely((__SIZE_TYPE__)(__dstend - __writer) < 2)
						goto __err_nospace;
					*__writer++ = '0';
					*__writer++ = '0';
				}
				goto __handle_next_byte;

			case 'E': case 'e': case 'n': case 'r':
			case 'b': case 'a': case 'v': case 't':
			case 'f': case 's': case '0': case '1':
			case '2': case '3': case '4': case '5':
			case '6': case '7': case 'M': case '^':
			case '$':
				/* Can't do normal escaping for these characters. */
				break;

			default:
				if (!(__NAMESPACE_LOCAL_SYM __localdep_isgraph)(__byte))
					break;
__escape_bk_byte:
				if __unlikely((__SIZE_TYPE__)(__dstend - __writer) < 2)
					goto __err_nospace;
				*__writer++ = '\\';
				*__writer++ = __byte;
				goto __handle_next_byte;
			}
		}

		/* Escape using the octal representation */
		if ((__flags & __VIS_OCTAL) || (__NAMESPACE_LOCAL_SYM __localdep_strchr)("\x20\xA0", __byte) || (__NAMESPACE_LOCAL_SYM __localdep_strchr)(__mbextra, __byte)) {
			if __unlikely((__SIZE_TYPE__)(__dstend - __writer) < 4)
				goto __err_nospace;
			*__writer++ = '\\';
			*__writer++ = (__BYTE_TYPE__)('0' + ((__byte & 0700) >> 6));
			*__writer++ = (__BYTE_TYPE__)('0' + ((__byte & 0070) >> 3));
			*__writer++ = (__BYTE_TYPE__)('0' + ((__byte & 0007)));
			goto __handle_next_byte;
		}

		if (!(__flags & __VIS_NOSLASH)) {
			if __unlikely(__writer == __dstend)
				goto __err_nospace;
			*__writer++ = '\\';
		}

		if (__byte & 0x80) {
			if __unlikely(__writer == __dstend)
				goto __err_nospace;
			*__writer++ = 'M';
			__byte &= 0x7f;
		}

		if __unlikely((__SIZE_TYPE__)(__dstend - __writer) < 2)
			goto __err_nospace;
		if ((__NAMESPACE_LOCAL_SYM __localdep_iscntrl)(__byte)) {
			*__writer++ = '^';
			if (__byte == 0x7f) {
				*__writer++ = '?';
			} else {
				*__writer++ = '@' + __byte;
			}
		} else {
			*__writer++ = '-';
			*__writer++ = __byte;
		}
	}
	if __unlikely(__writer == __dstend)
		goto __err_nospace;
	*__writer = '\0';
	return (int)(unsigned int)(__SIZE_TYPE__)(__writer - (__BYTE_TYPE__ *)__dst);
__err_nospace:
#ifdef __ENOSPC
	return __libc_seterrno(__ENOSPC);
#else /* __ENOSPC */
	return __libc_seterrno(1);
#endif /* !__ENOSPC */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strsenvisx_defined
#define __local___localdep_strsenvisx_defined
#define __localdep_strsenvisx __LIBC_LOCAL_NAME(strsenvisx)
#endif /* !__local___localdep_strsenvisx_defined */
#endif /* !__local_strsenvisx_defined */
