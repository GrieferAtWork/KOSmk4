/* HASH CRC-32:0x6dca91f6 */
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
#ifndef __local_hasmntopt_defined
#define __local_hasmntopt_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#if defined(__CRT_HAVE_strlen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

/* Dependency: "memcmp" from "string" */
#ifndef ____localdep_memcmp_defined
#define ____localdep_memcmp_defined 1
#if defined(__fast_memcmp_defined)
/* Compare memory buffers and return the difference of the first non-matching byte */
#define __localdep_memcmp (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))
#elif defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* LIBC: memcmp */
#include <local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte */
#define __localdep_memcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))
#endif /* memcmp... */
#endif /* !____localdep_memcmp_defined */

/* Dependency: "strchrnul" from "string" */
#ifndef ____localdep_strchrnul_defined
#define ____localdep_strchrnul_defined 1
#if defined(__CRT_HAVE_strchrnul)
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
#else /* LIBC: strchrnul */
#include <local/string/strchrnul.h>
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchrnul))
#endif /* strchrnul... */
#endif /* !____localdep_strchrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Search MNT->mnt_opts for an option matching OPT.
 * Returns the address of the substring, or null if none found */
__LOCAL_LIBC(hasmntopt) __ATTR_WUNUSED __ATTR_PURE char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hasmntopt))(struct mntent const *__mnt,
                                                       char const *__opt) {
#line 120 "kos/src/libc/magic/mntent.c"
	char *__str;
	if __likely(__mnt && __opt && (__str = __mnt->mnt_opts) != __NULLPTR) {
		__SIZE_TYPE__ __optlen = __localdep_strlen(__opt);
		while (*__str) {
			if (__localdep_memcmp(__str, __opt, __optlen * sizeof(char)) == 0 &&
			   (__str[__optlen] == ',' || __str[__optlen] == '\0'))
				return __str;
			__str = __localdep_strchrnul(__str, ',');
		}
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_hasmntopt_defined */
