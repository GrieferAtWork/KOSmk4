/* HASH CRC-32:0xe5e2d4ee */
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
#ifndef __local_argz_delete_defined
#if ((__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#define __local_argz_delete_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#if defined(__CRT_HAVE_strlen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

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

/* Dependency: "memmove" from "string" */
#ifndef ____localdep_memmove_defined
#define ____localdep_memmove_defined 1
#if defined(__fast_memmove_defined)
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memmove (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))
#elif defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* LIBC: memmove */
#include <local/string/memmove.h>
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memmove (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))
#endif /* memmove... */
#endif /* !____localdep_memmove_defined */

__NAMESPACE_LOCAL_BEGIN
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__LOCAL_LIBC(argz_delete) __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_delete))(char **__restrict __pargz,
                                                         __SIZE_TYPE__ *__restrict __pargz_len,
                                                         char *__entry) {
#line 357 "kos/src/libc/magic/argz.c"
	__SIZE_TYPE__ __entrylen, __newlen;
	if __unlikely(!__entry)
		return;
	__entrylen  = __localdep_strlen(__entry) + 1;
	__newlen    = *__pargz_len - __entrylen;
	*__pargz_len = __newlen;
	if __unlikely(__newlen == 0) {
		__localdep_free(*__pargz);
		*__pargz = __NULLPTR;
		return;
	}
	__localdep_memmove(__entry, __entry + __entrylen,
	        (__newlen - (__SIZE_TYPE__)(__entry - *__pargz)) *
	        sizeof(char));
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)) */
#endif /* !__local_argz_delete_defined */
