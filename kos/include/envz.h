/* HASH CRC-32:0x1476dc71 */
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
/* (#) Portability: Cygwin        (/newlib/libc/include/envz.h) */
/* (#) Portability: GNU C Library (/string/envz.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/envz.h) */
/* (#) Portability: libc6         (/include/envz.h) */
#ifndef _ENVZ_H
#define _ENVZ_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <argz.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_envz_entry
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ENVZ_H_PROTO)
extern "C++" {
/* >> envz_entry(3)
 * Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to  this
 * position are actually compared! */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,envz_entry,(char *__restrict __envz, size_t __envz_len, char const *__restrict __name),envz_entry,(__envz,__envz_len,__name))
/* >> envz_entry(3)
 * Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to  this
 * position are actually compared! */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char const *,__NOTHROW_NCX,envz_entry,(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name),envz_entry,(__envz,__envz_len,__name))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ENVZ_H_PROTO */
/* >> envz_entry(3)
 * Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to  this
 * position are actually compared! */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,envz_entry,(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name),(__envz,__envz_len,__name))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ENVZ_H_PROTO */
#else /* __CRT_HAVE_envz_entry */
#include <libc/local/envz/envz_entry.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ENVZ_H_PROTO)
extern "C++" {
/* >> envz_entry(3)
 * Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to  this
 * position are actually compared! */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL envz_entry)(char *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_entry))(__envz, __envz_len, __name); }
/* >> envz_entry(3)
 * Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to  this
 * position are actually compared! */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char const *__NOTHROW_NCX(__LIBCCALL envz_entry)(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_entry))(__envz, __envz_len, __name); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ENVZ_H_PROTO */
/* >> envz_entry(3)
 * Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to  this
 * position are actually compared! */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_entry, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL envz_entry)(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_entry))(__envz, __envz_len, __name); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ENVZ_H_PROTO */
#endif /* !__CRT_HAVE_envz_entry */
#ifdef __CRT_HAVE_envz_get
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ENVZ_H_PROTO)
extern "C++" {
/* >> envz_get(3)
 * Return the value in `envz'  attached to `name', or  `NULL'
 * if no such entry exists, or the entry doesn't have a value
 * portion (i.e. doesn't contain a `='-character) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,envz_get,(char *__restrict __envz, size_t __envz_len, char const *__restrict __name),envz_get,(__envz,__envz_len,__name))
/* >> envz_get(3)
 * Return the value in `envz'  attached to `name', or  `NULL'
 * if no such entry exists, or the entry doesn't have a value
 * portion (i.e. doesn't contain a `='-character) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char const *,__NOTHROW_NCX,envz_get,(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name),envz_get,(__envz,__envz_len,__name))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ENVZ_H_PROTO */
/* >> envz_get(3)
 * Return the value in `envz'  attached to `name', or  `NULL'
 * if no such entry exists, or the entry doesn't have a value
 * portion (i.e. doesn't contain a `='-character) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,envz_get,(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name),(__envz,__envz_len,__name))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ENVZ_H_PROTO */
#else /* __CRT_HAVE_envz_get */
#include <libc/local/envz/envz_get.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ENVZ_H_PROTO)
extern "C++" {
/* >> envz_get(3)
 * Return the value in `envz'  attached to `name', or  `NULL'
 * if no such entry exists, or the entry doesn't have a value
 * portion (i.e. doesn't contain a `='-character) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL envz_get)(char *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_get))(__envz, __envz_len, __name); }
/* >> envz_get(3)
 * Return the value in `envz'  attached to `name', or  `NULL'
 * if no such entry exists, or the entry doesn't have a value
 * portion (i.e. doesn't contain a `='-character) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char const *__NOTHROW_NCX(__LIBCCALL envz_get)(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_get))(__envz, __envz_len, __name); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ENVZ_H_PROTO */
/* >> envz_get(3)
 * Return the value in `envz'  attached to `name', or  `NULL'
 * if no such entry exists, or the entry doesn't have a value
 * portion (i.e. doesn't contain a `='-character) */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_get, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL envz_get)(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_get))(__envz, __envz_len, __name); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ENVZ_H_PROTO */
#endif /* !__CRT_HAVE_envz_get */
#ifdef __CRT_HAVE_envz_add
/* >> envz_add(3)
 * Add an entry `name=value' to `penvz'. If another entry for `name'
 * already existed before, that entry is removed. If `name' is NULL,
 * the entry created  doesn't have a  value-portion (i.e. `name'  is
 * added to `penvz' as-is, without the trailing `=value') */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,envz_add,(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __name, char const *___value),(__penvz,__penvz_len,__name,___value))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/envz/envz_add.h>
/* >> envz_add(3)
 * Add an entry `name=value' to `penvz'. If another entry for `name'
 * already existed before, that entry is removed. If `name' is NULL,
 * the entry created  doesn't have a  value-portion (i.e. `name'  is
 * added to `penvz' as-is, without the trailing `=value') */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_add, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL envz_add)(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __name, char const *___value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_add))(__penvz, __penvz_len, __name, ___value); })
#endif /* ... */
#ifdef __CRT_HAVE_envz_merge
/* >> envz_merge(3)
 * Add all entries from `envz2' to `penvz', as though `envz_add()' was
 * called for each contained `name=value' pair (using `NULL' for value
 * on pairs that doesn't have a value-portion.
 * If individual entries already existed in `penvz', behavior  depends
 * on `override_', which if non-zero will cause existing entries to be
 * overwritten, and otherwise if zero, will cause them to stay. */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,envz_merge,(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __envz2, size_t __envz2_len, int __override_),(__penvz,__penvz_len,__envz2,__envz2_len,__override_))
#elif defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/envz/envz_merge.h>
/* >> envz_merge(3)
 * Add all entries from `envz2' to `penvz', as though `envz_add()' was
 * called for each contained `name=value' pair (using `NULL' for value
 * on pairs that doesn't have a value-portion.
 * If individual entries already existed in `penvz', behavior  depends
 * on `override_', which if non-zero will cause existing entries to be
 * overwritten, and otherwise if zero, will cause them to stay. */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_merge, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL envz_merge)(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __envz2, size_t __envz2_len, int __override_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_merge))(__penvz, __penvz_len, __envz2, __envz2_len, __override_); })
#endif /* ... */
#ifdef __CRT_HAVE_envz_remove
/* >> envz_remove(3)
 * Remove an entry matching `name' from `penvz',
 * or  do  nothing  if  no  such  entry  exists. */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,envz_remove,(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __name),(__penvz,__penvz_len,__name))
#else /* __CRT_HAVE_envz_remove */
#include <libc/local/envz/envz_remove.h>
/* >> envz_remove(3)
 * Remove an entry matching `name' from `penvz',
 * or  do  nothing  if  no  such  entry  exists. */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_remove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_NCX(__LIBCCALL envz_remove)(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __name) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_remove))(__penvz, __penvz_len, __name); })
#endif /* !__CRT_HAVE_envz_remove */
#ifdef __CRT_HAVE_envz_strip
/* >> envz_strip(3)
 * Remove all entries from `penvz' that don't have a value-portion. */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,envz_strip,(char **__restrict __penvz, size_t *__restrict __penvz_len),(__penvz,__penvz_len))
#else /* __CRT_HAVE_envz_strip */
#include <libc/local/envz/envz_strip.h>
/* >> envz_strip(3)
 * Remove all entries from `penvz' that don't have a value-portion. */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_strip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL envz_strip)(char **__restrict __penvz, size_t *__restrict __penvz_len) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_strip))(__penvz, __penvz_len); })
#endif /* !__CRT_HAVE_envz_strip */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ENVZ_H */
