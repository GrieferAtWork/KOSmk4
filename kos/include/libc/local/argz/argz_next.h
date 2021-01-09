/* HASH CRC-32:0x224ebb06 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_argz_next_defined
#define __local_argz_next_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strend from string */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined 1
#ifdef __CRT_HAVE_strend
/* Same as `STR + strlen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __string),strend,(__string))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR + strlen(STR)' */
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__LOCAL_LIBC(argz_next) __ATTR_PURE __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_next))(char const *__restrict __argz, __SIZE_TYPE__ __argz_len, char const *__restrict __entry) {
	char const *__argz_end;
	if (!__entry)
		return __argz_len ? (char *)__argz : __NULLPTR;
	__argz_end = __argz + __argz_len;
	if (__entry < __argz_end)
		__entry = __localdep_strend(__entry) + 1;
	if (__entry >= __argz_end)
		return __NULLPTR;
	return (char *)__entry;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argz_next_defined
#define __local___localdep_argz_next_defined 1
#define __localdep_argz_next __LIBC_LOCAL_NAME(argz_next)
#endif /* !__local___localdep_argz_next_defined */
#endif /* !__local_argz_next_defined */
