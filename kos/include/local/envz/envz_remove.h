/* HASH CRC-32:0xce69322 */
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
#ifndef __local_envz_remove_defined
#define __local_envz_remove_defined 1
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

/* Dependency: "argz_delete" from "argz" */
#ifndef ____localdep_argz_delete_defined
#define ____localdep_argz_delete_defined 1
#ifdef __CRT_HAVE_argz_delete
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,__localdep_argz_delete,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char *__entry),argz_delete,(__pargz,__pargz_len,__entry))
#elif defined(__CRT_HAVE___argz_add_sep)
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,__localdep_argz_delete,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char *__entry),__argz_add_sep,(__pargz,__pargz_len,__entry))
#else /* LIBC: argz_delete */
#include <local/argz/argz_delete.h>
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
#define __localdep_argz_delete (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_delete))
#endif /* argz_delete... */
#endif /* !____localdep_argz_delete_defined */

__NAMESPACE_LOCAL_BEGIN
/* Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any */
__LOCAL_LIBC(envz_remove) __ATTR_NONNULL((1, 2, 3)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_remove))(char **__restrict __penvz,
                                                         __SIZE_TYPE__ *__restrict __penvz_len,
                                                         char const *__restrict __name) {
#line 155 "kos/src/libc/magic/envz.c"
	char *__entry;
	__entry = __localdep_envz_entry(*__penvz, *__penvz_len, __name);
	if (__entry)
		__localdep_argz_delete(__penvz, __penvz_len, __entry);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_envz_remove_defined */
