/* HASH CRC-32:0x65aaf5a9 */
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
#ifndef __local_sl_find_defined
#define __local_sl_find_defined 1
#include <__crt.h>
#ifndef ___stringlist_defined
#define ___stringlist_defined 1
typedef struct _stringlist {
	char   **sl_str;
	__SIZE_TYPE__   sl_max;
	__SIZE_TYPE__   sl_cur;
} StringList;
#endif /* !___stringlist_defined */
/* Dependency: "strcmp" from "string" */
#ifndef ____localdep_strcmp_defined
#define ____localdep_strcmp_defined 1
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* LIBC: strcmp */
#include <local/string/strcmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_strcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcmp))
#endif /* strcmp... */
#endif /* !____localdep_strcmp_defined */

__NAMESPACE_LOCAL_BEGIN
/* Search for `NAME' within the given StringList. Upon success,
 * return a pointer to the equivalent string within `SL' (i.e. the
 * pointer originally passed to `sl_add()' to insert that string).
 * If `SL' doesn't contain an equivalent string, return `NULL' instead. */
__LOCAL_LIBC(sl_find) __ATTR_PURE __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sl_find))(struct _stringlist __KOS_FIXED_CONST *__sl,
                                                     char const *__name) {
#line 118 "kos/src/libc/magic/stringlist.c"
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < __sl->sl_cur; ++__i) {
		char *__s = __sl->sl_str[__i];
		if (__localdep_strcmp(__s, __name) == 0)
			return __s;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_sl_find_defined */
