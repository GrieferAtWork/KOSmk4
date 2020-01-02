/* HASH CRC-32:0xd445b7b9 */
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
#ifndef __local_argz_create_defined
#if defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#define __local_argz_create_defined 1
#include <parts/errno.h>

#include <hybrid/__assert.h>
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

/* Dependency: "stpcpy" from "string" */
#ifndef ____localdep_stpcpy_defined
#define ____localdep_stpcpy_defined 1
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__FORCELOCAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL __localdep_stpcpy)(char *__restrict __buf, char const *__restrict __src) { return __builtin_stpcpy(__buf, __src); }
#elif defined(__CRT_HAVE_stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,(__buf,__src))
#elif defined(__CRT_HAVE___stpcpy)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),__stpcpy,(__buf,__src))
#else /* LIBC: stpcpy */
#include <local/string/stpcpy.h>
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
#define __localdep_stpcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stpcpy))
#endif /* stpcpy... */
#endif /* !____localdep_stpcpy_defined */

__NAMESPACE_LOCAL_BEGIN
/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
__LOCAL_LIBC(argz_create) __ATTR_NONNULL((1, 2, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_create))(char *const ___argv[],
                                                         char **__restrict __pargz,
                                                         __SIZE_TYPE__ *__restrict __pargz_len) {
#line 86 "kos/src/libc/magic/argz.c"
	__SIZE_TYPE__ __i, ___argc, __total_len = 0;
	for (___argc = 0; ___argv[___argc] != __NULLPTR; ++___argc)
		__total_len += __localdep_strlen(___argv[___argc]) + 1;
	if __unlikely(__total_len == 0) {
		*__pargz = __NULLPTR;
	} else {
		char *__argz_string;
		__argz_string = (char *)__localdep_malloc(__total_len * sizeof(char));
		if __unlikely(!__argz_string) {
			*__pargz = __NULLPTR;
			*__pargz_len  = 0;
#ifdef __ENOMEM
			return __ENOMEM;
#else /* __ENOMEM */
			return 1;
#endif /* !__ENOMEM */
		}
		*__pargz = __argz_string;
		for (__i = 0; __i < ___argc; ++__i) {
			__argz_string = __localdep_stpcpy(__argz_string, ___argv[___argc]) + 1;
		}
		__hybrid_assert(__argz_string == *__pargz + __total_len);
	}
	*__pargz_len = __total_len;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_posix_memalign || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_malloc */
#endif /* !__local_argz_create_defined */
