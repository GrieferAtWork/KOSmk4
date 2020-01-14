/* HASH CRC-32:0xdc432c2e */
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
#ifndef __local_envz_get_defined
#define __local_envz_get_defined 1
/* Dependency: "envz_entry" from "envz" */
#ifndef ____localdep_envz_entry_defined
#define ____localdep_envz_entry_defined 1
#ifdef __CRT_HAVE_envz_entry
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,__localdep_envz_entry,(char const *__restrict __envz, __SIZE_TYPE__ __envz_len, char const *__restrict __name),envz_entry,(__envz,__envz_len,__name))
#else /* LIBC: envz_entry */
#include <local/envz/envz_entry.h>
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
#define __localdep_envz_entry (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_entry))
#endif /* envz_entry... */
#endif /* !____localdep_envz_entry_defined */

/* Dependency: "strchr" from "string" */
#ifndef ____localdep_strchr_defined
#define ____localdep_strchr_defined 1
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__EXTERNINLINE __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL __localdep_strchr)(char const *__restrict __haystack, int __needle) { return __builtin_strchr(__haystack, __needle); }
#elif defined(__CRT_HAVE_strchr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#else /* LIBC: strchr */
#include <local/string/strchr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))
#endif /* strchr... */
#endif /* !____localdep_strchr_defined */

__NAMESPACE_LOCAL_BEGIN
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
__LOCAL_LIBC(envz_get) __ATTR_PURE __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_get))(char const *__restrict __envz,
                                                      __SIZE_TYPE__ __envz_len,
                                                      char const *__restrict __name) {
#line 82 "kos/src/libc/magic/envz.c"
	char *__result;
	__result = (char *)__localdep_envz_entry(__envz, __envz_len, __name);
	if (__result) {
		__result = __localdep_strchr(__result, '=');
		if (__result)
			++__result; /* Point to the value-portion */
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_envz_get_defined */
