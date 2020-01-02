/* HASH CRC-32:0x724918d3 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_envz_strip_defined
#define __local_envz_strip_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "strchrnul" from "string" */
#ifndef ____localdep_strchrnul_defined
#define ____localdep_strchrnul_defined 1
#ifdef __CRT_HAVE_strchrnul
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
#else /* LIBC: strchrnul */
#include <local/string/strchrnul.h>
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))
#endif /* strchrnul... */
#endif /* !____localdep_strchrnul_defined */

/* Dependency: "strend" from "string" */
#ifndef ____localdep_strend_defined
#define ____localdep_strend_defined 1
#ifdef __CRT_HAVE_strend
/* Same as `STR + strlen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __string),strend,(__string))
#else /* LIBC: strend */
#include <local/string/strend.h>
/* Same as `STR + strlen(STR)' */
#define __localdep_strend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))
#endif /* strend... */
#endif /* !____localdep_strend_defined */

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

__NAMESPACE_LOCAL_BEGIN
/* Remove entries that have no value attached */
__LOCAL_LIBC(envz_strip) __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_strip))(char **__restrict __penvz,
                                                        __SIZE_TYPE__ *__restrict __penvz_len) {
#line 165 "kos/src/libc/magic/envz.c"
	char *__start, *__ptr, *__end;
	__SIZE_TYPE__ __oldlen, __newlen;
	__ptr = __start = *__penvz;
	__end = __ptr + (__oldlen = *__penvz_len);
	while (__ptr < __end) {
		char *__next;
		__SIZE_TYPE__ __partlen;
		__next = __localdep_strchrnul(__ptr, '=');
		if (*__next) {
			__ptr = __localdep_strend(__next) + 1;
			continue;
		}
		/* Remove this entry. */
		__next = __localdep_strend(__next) + 1;
		__partlen = (__SIZE_TYPE__)(__end - __next);
		__localdep_memmovedownc(__ptr, __next, __partlen, sizeof(char));
		__end -= __partlen;
	}
	__newlen = (__SIZE_TYPE__)(__end - __start);
	if (__newlen < __oldlen) {
		*__penvz_len = __newlen;
#ifdef __CRT_HAVE_realloc
		__start = (char *)__localdep_realloc(__start, __newlen);
		if __likely(__start)
			*__penvz = __start;
#endif /* __CRT_HAVE_realloc */
	}
}
__NAMESPACE_LOCAL_END
#endif /* !__local_envz_strip_defined */
