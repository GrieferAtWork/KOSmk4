/* HASH CRC-32:0x47e9f8b2 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_argz_replace_defined
#if defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#define __local_argz_replace_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <parts/errno.h>
/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

/* Dependency: "memmem" from "string" */
#ifndef ____localdep_memmem_defined
#define ____localdep_memmem_defined 1
#if defined(__CRT_HAVE_memmem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,__localdep_memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem0,(__haystack,__haystacklen,__needle,__needlelen))
#elif defined(__CRT_HAVE_memmem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,__localdep_memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem,(__haystack,__haystacklen,__needle,__needlelen))
#else /* LIBC: memmem */
#include <local/string/memmem.h>
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
#define __localdep_memmem (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))
#endif /* memmem... */
#endif /* !____localdep_memmem_defined */

/* Dependency: "mempcpyc" from "string" */
#ifndef ____localdep_mempcpyc_defined
#define ____localdep_mempcpyc_defined 1
#ifdef __fast_mempcpyc_defined
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
#define __localdep_mempcpyc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyc))
#elif defined(__CRT_HAVE_mempcpyc)
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* LIBC: mempcpyc */
#include <local/string/mempcpyc.h>
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
#define __localdep_mempcpyc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyc))
#endif /* mempcpyc... */
#endif /* !____localdep_mempcpyc_defined */

/* Dependency: "memmovedownc" from "string" */
#ifndef ____localdep_memmovedownc_defined
#define ____localdep_memmovedownc_defined 1
#ifdef __fast_memmovedownc_defined
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmovedownc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownc))
#elif defined(__CRT_HAVE_memmovedownc)
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* LIBC: memmovedownc */
#include <local/string/memmovedownc.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmovedownc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownc))
#endif /* memmovedownc... */
#endif /* !____localdep_memmovedownc_defined */

/* Dependency: "realloc" */
#ifndef ____localdep_realloc_defined
#define ____localdep_realloc_defined 1
#ifdef __std___localdep_realloc_defined
__NAMESPACE_STD_USING(__localdep_realloc)
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__FORCELOCAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL __localdep_realloc)(void *__mallptr, __SIZE_TYPE__ __n_bytes) { return __builtin_realloc(__mallptr, __n_bytes); }
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __n_bytes),realloc,(__mallptr,__n_bytes))
#else /* LIBC: realloc */
#undef ____localdep_realloc_defined
#endif /* realloc... */
#endif /* !____localdep_realloc_defined */

/* Dependency: "memmoveupc" from "string" */
#ifndef ____localdep_memmoveupc_defined
#define ____localdep_memmoveupc_defined 1
#ifdef __fast_memmoveupc_defined
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmoveupc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupc))
#elif defined(__CRT_HAVE_memmoveupc)
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* LIBC: memmoveupc */
#include <local/string/memmoveupc.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmoveupc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupc))
#endif /* memmoveupc... */
#endif /* !____localdep_memmoveupc_defined */

__NAMESPACE_LOCAL_BEGIN
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
__LOCAL_LIBC(argz_replace) __ATTR_NONNULL((1, 2, 4)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_replace))(char **__restrict __pargz,
                                                          __SIZE_TYPE__ *__restrict __pargz_len,
                                                          char const *__restrict __str,
                                                          char const *__restrict __with,
                                                          unsigned int *__restrict __replace_count) {
#line 453 "kos/src/libc/magic/argz.c"
	__SIZE_TYPE__ __findlen, __repllen;
	__SIZE_TYPE__ __find_offset;
	if __unlikely(!__str)
		return 0; /* no-op */
	__findlen = __localdep_strlen(__str);
	if __unlikely(!__findlen)
		return 0; /* no-op */
	__repllen = __localdep_strlen(__with);
	__find_offset = 0;
	/* I have no idea what the GLibc implementation does here, and I'm not
	 * quite sure it knows either. - At first I though that this function
	 * was supposed to only replace entries of an ARGZ vector as a whole,
	 * but now I believe it's just supposed to do replacement of any match
	 * found. However, GLibc appears to be utterly afraid of using `memmem()'
	 * for this, and instead opt's to using `argz_next()' to iterate the
	 * ARGZ vector, and doing `strstr()' on each element, before doing some
	 * dark voodoo magic with `strndup()', temporary buffers, and god only
	 * knows why there are even delayed calls to `argz_add()' in there???
	 * If this implementation doesn't do exactly what GLibc does, don't fault
	 * me. Every function in this file was originally created as a GLibc
	 * extension, so there really isn't any official documentation on intended
	 * behavior other than GLibc reference implementation.
	 * Anyways... At least my version is readable... */
	while (__find_offset < *__pargz_len) {
		char *__pos;
		__pos = (char *)__localdep_memmem(*__pargz + __find_offset,
		                     *__pargz_len - __find_offset,
		                     __str, __findlen);
		if (!__pos)
			break; /* Nothing else to find! */
		if (__repllen < __findlen) {
			/* Simple case: The replacement string is smaller than the find-string */
			char *__old_argz, *__new_argz;
			__SIZE_TYPE__ __diff, __trailing_characters;
			__pos  = (char *)__localdep_mempcpyc(__pos, __with, __repllen, sizeof(char));
			__diff = __findlen - __repllen;
			*__pargz_len -= __diff;
			__old_argz = *__pargz;
			__trailing_characters = *__pargz_len - (__SIZE_TYPE__)(__pos - __old_argz);
			__localdep_memmovedownc(__pos, __pos + __diff, __trailing_characters, sizeof(char));
			__new_argz = (char *)__localdep_realloc(__old_argz, *__pargz_len * sizeof(char));
			if __likely(__new_argz) {
				__pos    = __new_argz + (__pos - __old_argz);
				*__pargz = __new_argz;
			}
		} else if (__repllen > __findlen) {
			char *__old_argz, *__new_argz;
			__SIZE_TYPE__ __old_argzlen, __new_argzlen;
			__SIZE_TYPE__ __diff, __trailing_characters;
			/* Difficult case: The replacement string is longer than the find-string */
			__diff = __repllen - __findlen;
			__old_argzlen = *__pargz_len;
			__new_argzlen = __old_argzlen + __diff;
			__old_argz = *__pargz;
			__new_argz = (char *)__localdep_realloc(__old_argz, __new_argzlen * sizeof(char));
			if __unlikely(!__new_argz) {
#ifdef __ENOMEM
				return __ENOMEM;
#else /* __ENOMEM */
				return 1;
#endif /* !__ENOMEM */
			}
			__pos = __new_argz + (__pos - __old_argz);
			/* Make space for extra data */
			__trailing_characters = __new_argzlen - ((__pos + __repllen) - __new_argz);
			__localdep_memmoveupc(__pos + __repllen,
			           __pos + __findlen,
			           __trailing_characters,
			           sizeof(char));
			/* Fill in the replacement string. */
			__pos = (char *)__localdep_mempcpyc(__pos, __with, __repllen, sizeof(char));
		} else {
			/* Simple case: The replacement string has the same length as the find-string */
			__pos = (char *)__localdep_mempcpyc(__pos, __with, __repllen, sizeof(char));
		}
		if (__replace_count)
			++*__replace_count;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_realloc && (__CRT_HAVE_free || __CRT_HAVE_cfree) */
#endif /* !__local_argz_replace_defined */
