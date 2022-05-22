/* HASH CRC-32:0xfe1dc203 */
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
#ifndef __local_buildargv_defined
#define __local_buildargv_defined
#include <__crt.h>
#if defined(__CRT_HAVE_xrealloc) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_xmalloc_failed))
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_xrealloc_defined
#define __local___localdep_xrealloc_defined
#ifdef __CRT_HAVE_xrealloc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_xrealloc,(void *__ptr, __SIZE_TYPE__ __num_bytes),xrealloc,(__ptr,__num_bytes))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_xmalloc_failed)
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/xrealloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_xrealloc __LIBC_LOCAL_NAME(xrealloc)
#else /* ... */
#undef __local___localdep_xrealloc_defined
#endif /* !... */
#endif /* !__local___localdep_xrealloc_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(buildargv) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN_OPT(1) char **
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(buildargv))(char const *__cmdline) {
	char **___argv = __NULLPTR;
	__SIZE_TYPE__ ___argc = 0;
	if (!__cmdline)
		return __NULLPTR;
	while ((__NAMESPACE_LOCAL_SYM __localdep_isspace)(*__cmdline))
		++__cmdline;
	for (;;) {
		char const *__flush_start = __cmdline;
		char *__argcopy_str = __NULLPTR;
		__SIZE_TYPE__ __argcopy_len = 0;
		int __quote = 0; /* 0: foo; 1: "foo"; 2: 'foo' */
		for (;; ++__cmdline) {
			char __ch = *__cmdline;
			__SIZE_TYPE__ __flushlen;
			switch (__ch) {
			case '\0':
				break;
			case '\'':
				if (__quote == 1)
					goto __cmdline_advance;
				break;
			case '\"':
				if (__quote == 2)
					goto __cmdline_advance;
				break;
			case '\\':
				break;
			default:
				if (!(__NAMESPACE_LOCAL_SYM __localdep_isspace)(__ch)) {
__cmdline_advance:
					++__cmdline;
					continue;
				}
				if (__quote != 0)
					goto __cmdline_advance;
				break;
			}

			/* Flush until this position. */
			__flushlen    = (__SIZE_TYPE__)(__cmdline - __flush_start);
			__argcopy_str = (char *)(__NAMESPACE_LOCAL_SYM __localdep_xrealloc)(__argcopy_str, (__argcopy_len + __flushlen + 1) * sizeof(char));
			(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__argcopy_str + __argcopy_len, __flush_start, __flushlen);
			__argcopy_len += __flushlen;
			switch (__ch) {
			case '\0':
				goto __end_of_argument;
			case '\'':
				__quote ^= 2;
				__flush_start = ++__cmdline;
				break;
			case '\"':
				__quote ^= 1;
				__flush_start = ++__cmdline;
				break;
			case '\\':
				++__cmdline;
				__flush_start = __cmdline; /* Start flushing on escaped character. */
				if (*__cmdline)
					++__cmdline; /* Skip escaped character */
				break;
			default:
				__hybrid_assert((__NAMESPACE_LOCAL_SYM __localdep_isspace)(__ch));
				__hybrid_assert(__quote == 0);
				++__cmdline;
				goto __end_of_argument;
			}
			__flush_start = __cmdline;
		}
__end_of_argument:
		__argcopy_str[__argcopy_len] = '\0';

		/* Append the argument. */
		___argv = (char **)(__NAMESPACE_LOCAL_SYM __localdep_xrealloc)(___argv, (___argc + 2) * sizeof(char *));
		___argv[___argc++] = __argcopy_str;

		/* Skip space past the argument. */
		while ((__NAMESPACE_LOCAL_SYM __localdep_isspace)(*__cmdline))
			++__cmdline;
		if (!*__cmdline)
			break;
	}
	___argv[___argc] = __NULLPTR; /* Sentinel */
	return ___argv;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_buildargv_defined
#define __local___localdep_buildargv_defined
#define __localdep_buildargv __LIBC_LOCAL_NAME(buildargv)
#endif /* !__local___localdep_buildargv_defined */
#else /* __CRT_HAVE_xrealloc || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __CRT_HAVE_xmalloc_failed) */
#undef __local_buildargv_defined
#endif /* !__CRT_HAVE_xrealloc && ((!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || !__CRT_HAVE_xmalloc_failed) */
#endif /* !__local_buildargv_defined */
