/* HASH CRC-32:0x4a04270f */
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
#ifndef __local_argz_create_sep_defined
#if (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#define __local_argz_create_sep_defined 1
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

/* Dependency: "malloc" from "stdlib" */
#ifndef ____localdep_malloc_defined
#define ____localdep_malloc_defined 1
#ifdef __std___localdep_malloc_defined
__NAMESPACE_STD_USING(__localdep_malloc)
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL __localdep_malloc)(__SIZE_TYPE__ __n_bytes) { return __builtin_malloc(__n_bytes); }
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __n_bytes),malloc,(__n_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#include <local/stdlib/malloc.h>
#define __localdep_malloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))
#else /* CUSTOM: malloc */
#undef ____localdep_malloc_defined
#endif /* malloc... */
#endif /* !____localdep_malloc_defined */

/* Dependency: "free" */
#ifndef ____localdep_free_defined
#define ____localdep_free_defined 1
#ifdef __std___localdep_free_defined
__NAMESPACE_STD_USING(__localdep_free)
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL __localdep_free)(void *__mallptr) { return __builtin_free(__mallptr); }
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* LIBC: free */
#undef ____localdep_free_defined
#endif /* free... */
#endif /* !____localdep_free_defined */

__NAMESPACE_LOCAL_BEGIN
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
__LOCAL_LIBC(argz_create_sep) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_create_sep))(char const *__restrict __string,
                                                             int __sep,
                                                             char **__restrict __pargz,
                                                             __SIZE_TYPE__ *__restrict __pargz_len) {
#line 125 "kos/src/libc/magic/argz.c"
	/* return string.replace(sep, "\0").replaceall("\0\0", "\0"); */
	char *__result_string, *__dst;
	__SIZE_TYPE__ __slen = __localdep_strlen(__string);
	if __unlikely(!__slen) {
__empty_argz:
		*__pargz     = __NULLPTR;
		*__pargz_len = 0;
		return 0;
	}
	__result_string = (char *)__localdep_malloc((__slen + 1) * sizeof(char));
	*__pargz = __result_string;
	if __unlikely(!__result_string) {
		*__pargz_len = 0;
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
	}
	__dst = __result_string;
	for (;;) {
		char __ch;
		__ch = *__string++;
__again_check_ch:
		if (!__ch)
			break;
		if (__ch != (char)(unsigned char)(unsigned int)__sep) {
			*__dst++ = __ch;
			continue;
		}
		/* Split the string. */
		*__dst++ = '\0';
		/* Skip consecutive `sep'-characters in `string' */
		do {
			__ch = *__string++;
		} while (__ch == (char)(unsigned char)(unsigned int)__sep);
		goto __again_check_ch;
	}
	if __unlikely(__dst == __result_string) {
		/* Empty string. (this can happen if `string' only consisted of `sep' characters) */
		__localdep_free(__result_string);
		goto __empty_argz;
	}
	/* Write the terminating NUL-byte (if there isn't one already) */
	if (__dst[-1] != '\0')
		*__dst++ = '\0';
	*__pargz_len = (__SIZE_TYPE__)(__dst - __result_string);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)) */
#endif /* !__local_argz_create_sep_defined */
