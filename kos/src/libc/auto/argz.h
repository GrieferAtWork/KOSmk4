/* HASH CRC-32:0x6d653c78 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_ARGZ_H
#define GUARD_LIBC_AUTO_ARGZ_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <argz.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_create(3)
 * Construct  an  argz-string  from  a  given  NULL-terminated  `argv'-vector,
 * as is also passed to main(), and accepted by the exec() family of functions
 * An  argz-string is imply a string of '\0'-seperated sub-strings, where each
 * sub-string represents one of the original strings from `argv'
 *
 * The base-pointer to this string is stored in `*pargz'
 *
 * The overall length of the argz-string is  tracked at the offset from its  base
 * pointer, to the first  byte after a trailing  '\0' character that follows  the
 * last of the many sub-strings. An empty argz-string is thus represented as  any
 * base-pointer in conjunction with `*pargz_len=0'. (But note that GLibc seems to
 * suggest that certain APIs  should be used under  the assumption that an  empty
 * argz-string  can also be represented with the base pointer `*pargz=NULL'. This
 * kind of behavior is _NOT_ actually supported  by the API, and only implied  by
 * some (apparently) badly worded documentation of `argz_next(3)')
 *
 * When an argz-string is no longer needed, it can be destroyed by passing its
 * base pointer (as filled in at `*pargz' by this function, and updated by the
 * many other functions in this header) to `free(3)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) error_t NOTHROW_NCX(LIBDCALL libd_argz_create)(char *const argv[], char **__restrict pargz, size_t *__restrict pargz_len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_create(3)
 * Construct  an  argz-string  from  a  given  NULL-terminated  `argv'-vector,
 * as is also passed to main(), and accepted by the exec() family of functions
 * An  argz-string is imply a string of '\0'-seperated sub-strings, where each
 * sub-string represents one of the original strings from `argv'
 *
 * The base-pointer to this string is stored in `*pargz'
 *
 * The overall length of the argz-string is  tracked at the offset from its  base
 * pointer, to the first  byte after a trailing  '\0' character that follows  the
 * last of the many sub-strings. An empty argz-string is thus represented as  any
 * base-pointer in conjunction with `*pargz_len=0'. (But note that GLibc seems to
 * suggest that certain APIs  should be used under  the assumption that an  empty
 * argz-string  can also be represented with the base pointer `*pargz=NULL'. This
 * kind of behavior is _NOT_ actually supported  by the API, and only implied  by
 * some (apparently) badly worded documentation of `argz_next(3)')
 *
 * When an argz-string is no longer needed, it can be destroyed by passing its
 * base pointer (as filled in at `*pargz' by this function, and updated by the
 * many other functions in this header) to `free(3)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) error_t NOTHROW_NCX(LIBCCALL libc_argz_create)(char *const argv[], char **__restrict pargz, size_t *__restrict pargz_len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_create_sep(3)
 * Create an argz-string from `string' by splitting that string at each
 * occurrence of `sep'. This function behaves the same as the following
 * pseudo-code:
 *     [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
 * As can be seen in the pseudo-code, duplicate, successive instance of
 * `sep' are merged, such that no empty sub-strings will be present  in
 * the resulting argz-string.
 * For more information on the semantics of argz-strings, see the
 * documentation of `argz_create()'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_IN(1) ATTR_OUT(3) ATTR_OUT(4) error_t NOTHROW_NCX(LIBDCALL libd_argz_create_sep)(char const *__restrict string, int sep, char **__restrict pargz, size_t *__restrict pargz_len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_create_sep(3)
 * Create an argz-string from `string' by splitting that string at each
 * occurrence of `sep'. This function behaves the same as the following
 * pseudo-code:
 *     [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
 * As can be seen in the pseudo-code, duplicate, successive instance of
 * `sep' are merged, such that no empty sub-strings will be present  in
 * the resulting argz-string.
 * For more information on the semantics of argz-strings, see the
 * documentation of `argz_create()'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_IN(1) ATTR_OUT(3) ATTR_OUT(4) error_t NOTHROW_NCX(LIBCCALL libc_argz_create_sep)(char const *__restrict string, int sep, char **__restrict pargz, size_t *__restrict pargz_len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_count(3)
 * Count and return the # of strings in `argz'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
INTDEF ATTR_PURE ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBDCALL libd_argz_count)(char const *argz, size_t argz_len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_count(3)
 * Count and return the # of strings in `argz'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
INTDEF ATTR_PURE ATTR_INS(1, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_argz_count)(char const *argz, size_t argz_len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_extract(3)
 * Extend pointers to  individual string  from `argz',  and sequentially  write them  to
 * `argv',  for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
INTDEF ATTR_INS(1, 2) ATTR_OUT(3) void NOTHROW_NCX(LIBDCALL libd_argz_extract)(char const *__restrict argz, size_t argz_len, char **__restrict argv);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_extract(3)
 * Extend pointers to  individual string  from `argz',  and sequentially  write them  to
 * `argv',  for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
INTDEF ATTR_INS(1, 2) ATTR_OUT(3) void NOTHROW_NCX(LIBCCALL libc_argz_extract)(char const *__restrict argz, size_t argz_len, char **__restrict argv);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_stringify(3)
 * Convert  an  `argz' string  into a  NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all of
 * the NUL-characters separating  the individual  argz-strings
 * with `sep'. */
INTDEF ATTR_INOUTS(1, 2) void NOTHROW_NCX(LIBDCALL libd_argz_stringify)(char *argz, size_t len, int sep);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_stringify(3)
 * Convert  an  `argz' string  into a  NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all of
 * the NUL-characters separating  the individual  argz-strings
 * with `sep'. */
INTDEF ATTR_INOUTS(1, 2) void NOTHROW_NCX(LIBCCALL libc_argz_stringify)(char *argz, size_t len, int sep);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_append(3)
 * Increase allocated memory of `*pargz' and append `buf...+=buf_len'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INS(3, 4) error_t NOTHROW_NCX(LIBDCALL libd_argz_append)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict buf, size_t buf_len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_append(3)
 * Increase allocated memory of `*pargz' and append `buf...+=buf_len'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INS(3, 4) error_t NOTHROW_NCX(LIBCCALL libc_argz_append)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict buf, size_t buf_len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_add(3)
 * Append `str' (including its trailing NUL) to the argz string in `*pargz...+=pargz_len'
 * This    is    the   same    as   `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) error_t NOTHROW_NCX(LIBDCALL libd_argz_add)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_add(3)
 * Append `str' (including its trailing NUL) to the argz string in `*pargz...+=pargz_len'
 * This    is    the   same    as   `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) error_t NOTHROW_NCX(LIBCCALL libc_argz_add)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_add_sep(3)
 * A  combination of `argz_create_sep()'  and `argz_append()' that will
 * append a duplication of `string' onto `*pargz', whilst replacing all
 * instances of `sep' with NUL-characters,  thus turning them into  the
 * markers  between  separate  strings.  Note  however  that duplicate,
 * successive instance of  `sep' are  merged, such that  no empty  sub-
 * strings will be present in the resulting argz-string.
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) error_t NOTHROW_NCX(LIBDCALL libd_argz_add_sep)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict string, int sep);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_add_sep(3)
 * A  combination of `argz_create_sep()'  and `argz_append()' that will
 * append a duplication of `string' onto `*pargz', whilst replacing all
 * instances of `sep' with NUL-characters,  thus turning them into  the
 * markers  between  separate  strings.  Note  however  that duplicate,
 * successive instance of  `sep' are  merged, such that  no empty  sub-
 * strings will be present in the resulting argz-string.
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) error_t NOTHROW_NCX(LIBCCALL libc_argz_add_sep)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict string, int sep);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_delete(3)
 * Find the index  of `entry' inside  of `pargz...+=pargz_len', and,  if
 * found, remove that entry by shifting all following elements downwards
 * by one, as well as decrementing `*pargz_len' by one.
 * Note that `entry' must  be the actual pointer  to one of the  elements
 * of the given `pargz...+=pargz_len', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) ATTR_IN_OPT(3) void NOTHROW_NCX(LIBDCALL libd_argz_delete)(char **__restrict pargz, size_t *__restrict pargz_len, char *entry);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_delete(3)
 * Find the index  of `entry' inside  of `pargz...+=pargz_len', and,  if
 * found, remove that entry by shifting all following elements downwards
 * by one, as well as decrementing `*pargz_len' by one.
 * Note that `entry' must  be the actual pointer  to one of the  elements
 * of the given `pargz...+=pargz_len', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) ATTR_IN_OPT(3) void NOTHROW_NCX(LIBCCALL libc_argz_delete)(char **__restrict pargz, size_t *__restrict pargz_len, char *entry);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_insert(3)
 * When `before' is  `NULL', do the  same as  `argz_add(pargz, pargz_len, entry)'
 * Otherwise,  `before' should point  somewhere into the middle,  or to the start
 * of an existing argument entry, who's  beginning will first be located,  before
 * this function will then allocate additional memory to insert a copy of `entry'
 * such that the copy will appear before the entry pointed to by `before'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory
 * @return: EINVAL: The given `before' is either `NULL', or apart of `*pargz' */
INTDEF ATTR_IN(4) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_IN_OPT(3) error_t NOTHROW_NCX(LIBDCALL libd_argz_insert)(char **__restrict pargz, size_t *__restrict pargz_len, char *before, char const *__restrict entry);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_insert(3)
 * When `before' is  `NULL', do the  same as  `argz_add(pargz, pargz_len, entry)'
 * Otherwise,  `before' should point  somewhere into the middle,  or to the start
 * of an existing argument entry, who's  beginning will first be located,  before
 * this function will then allocate additional memory to insert a copy of `entry'
 * such that the copy will appear before the entry pointed to by `before'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory
 * @return: EINVAL: The given `before' is either `NULL', or apart of `*pargz' */
INTDEF ATTR_IN(4) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_IN_OPT(3) error_t NOTHROW_NCX(LIBCCALL libc_argz_insert)(char **__restrict pargz, size_t *__restrict pargz_len, char *before, char const *__restrict entry);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_replace(3)
 * Replace all matches of `str' inside of every string or sub-string from `pargz...+=pargz_len'
 * with `with', and resize the  argz-string if necessary. For  every replacement that is  done,
 * the given `replace_count' is incremented by one (if `replace_count' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but  note  that  the GLibc  implementation  of this  function  is completely
 *                  unreadable and may be able to return this for other cases as well...) */
INTDEF ATTR_IN(4) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_IN_OPT(3) error_t NOTHROW_NCX(LIBDCALL libd_argz_replace)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict str, char const *__restrict with, unsigned int *__restrict replace_count);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_replace(3)
 * Replace all matches of `str' inside of every string or sub-string from `pargz...+=pargz_len'
 * with `with', and resize the  argz-string if necessary. For  every replacement that is  done,
 * the given `replace_count' is incremented by one (if `replace_count' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but  note  that  the GLibc  implementation  of this  function  is completely
 *                  unreadable and may be able to return this for other cases as well...) */
INTDEF ATTR_IN(4) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_IN_OPT(3) error_t NOTHROW_NCX(LIBCCALL libc_argz_replace)(char **__restrict pargz, size_t *__restrict pargz_len, char const *__restrict str, char const *__restrict with, unsigned int *__restrict replace_count);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> argz_next(3)
 * Iterate the individual strings that make up a given argz-vector.
 * This function  is  intended  to  be  used  in  one  of  2  ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note  that  GLibc documents  the second  usage  case slightly  different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty argz-string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL'  (which isn't something consistently enforced,  or
 * required  by any of  the other APIs, so  I'd just suggest  you always use the
 * first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of `argz', return `NULL'
 *  - If the successor of `entry' points at, or past the end of `argz', return `NULL'
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_IN_OPT(3) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_argz_next)(char const *__restrict argz, size_t argz_len, char const *__restrict entry);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> argz_next(3)
 * Iterate the individual strings that make up a given argz-vector.
 * This function  is  intended  to  be  used  in  one  of  2  ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note  that  GLibc documents  the second  usage  case slightly  different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty argz-string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL'  (which isn't something consistently enforced,  or
 * required  by any of  the other APIs, so  I'd just suggest  you always use the
 * first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of `argz', return `NULL'
 *  - If the successor of `entry' points at, or past the end of `argz', return `NULL'
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
INTDEF ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_IN_OPT(3) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_argz_next)(char const *__restrict argz, size_t argz_len, char const *__restrict entry);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ARGZ_H */
