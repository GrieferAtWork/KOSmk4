/* HASH CRC-32:0x8bd00410 */
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

/* Documentation is derived from GLibc: /usr/include/envz.h */
/* Routines for dealing with '\0' separated environment vectors
   Copyright (C) 1995-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__

#ifdef __CRT_HAVE_envz_entry
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ENVZ_H_PROTO)
extern "C++" {
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,envz_entry,(char *__restrict __envz, size_t __envz_len, char const *__restrict __name),envz_entry,(__envz,__envz_len,__name))
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char const *,__NOTHROW_NCX,envz_entry,(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name),envz_entry,(__envz,__envz_len,__name))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ENVZ_H_PROTO */
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,envz_entry,(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name),(__envz,__envz_len,__name))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ENVZ_H_PROTO */
#else /* __CRT_HAVE_envz_entry */
#include <libc/local/envz/envz_entry.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ENVZ_H_PROTO)
extern "C++" {
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL envz_entry)(char *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_entry))(__envz, __envz_len, __name); }
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char const *__NOTHROW_NCX(__LIBCCALL envz_entry)(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_entry))(__envz, __envz_len, __name); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ENVZ_H_PROTO */
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_entry, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL envz_entry)(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_entry))(__envz, __envz_len, __name); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ENVZ_H_PROTO */
#endif /* !__CRT_HAVE_envz_entry */
#ifdef __CRT_HAVE_envz_get
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ENVZ_H_PROTO)
extern "C++" {
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,envz_get,(char *__restrict __envz, size_t __envz_len, char const *__restrict __name),envz_get,(__envz,__envz_len,__name))
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char const *,__NOTHROW_NCX,envz_get,(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name),envz_get,(__envz,__envz_len,__name))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ENVZ_H_PROTO */
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,envz_get,(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name),(__envz,__envz_len,__name))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ENVZ_H_PROTO */
#else /* __CRT_HAVE_envz_get */
#include <libc/local/envz/envz_get.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ENVZ_H_PROTO)
extern "C++" {
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL envz_get)(char *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_get))(__envz, __envz_len, __name); }
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char const *__NOTHROW_NCX(__LIBCCALL envz_get)(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_get))(__envz, __envz_len, __name); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ENVZ_H_PROTO */
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_get, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((3)) char *__NOTHROW_NCX(__LIBCCALL envz_get)(char const *__restrict __envz, size_t __envz_len, char const *__restrict __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_get))(__envz, __envz_len, __name); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ENVZ_H_PROTO */
#endif /* !__CRT_HAVE_envz_get */
#ifdef __CRT_HAVE_envz_add
/* Adds an entry for `NAME' with value `VALUE' to `ENVZ & ENVZ_LEN'. If an entry
 * with the same name already exists in `ENVZ', it is removed. If `VALUE' is
 * `NULL', then the new entry will not have a value portion, meaning that `envz_get()'
 * will return `NULL', although `envz_entry()' will still return an entry. This is handy
 * because when merging with another envz, the null entry can override an
 * entry in the other one. Such entries can be removed with `envz_strip()' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,envz_add,(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __name, char const *__value),(__penvz,__penvz_len,__name,__value))
#elif defined(__CRT_HAVE_realloc)
#include <libc/local/envz/envz_add.h>
/* Adds an entry for `NAME' with value `VALUE' to `ENVZ & ENVZ_LEN'. If an entry
 * with the same name already exists in `ENVZ', it is removed. If `VALUE' is
 * `NULL', then the new entry will not have a value portion, meaning that `envz_get()'
 * will return `NULL', although `envz_entry()' will still return an entry. This is handy
 * because when merging with another envz, the null entry can override an
 * entry in the other one. Such entries can be removed with `envz_strip()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_add, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL envz_add)(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __name, char const *__value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_add))(__penvz, __penvz_len, __name, __value); })
#endif /* ... */
#ifdef __CRT_HAVE_envz_merge
/* Adds each entry in `ENVZ2' to `ENVZ & ENVZ_LEN', as if with `envz_add()'.
 * If `OVERRIDE' is true, then values in `ENVZ2' will supersede those
 * with the same name in `ENV', otherwise they don't */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,envz_merge,(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __envz2, size_t __envz2_len, int __override_),(__penvz,__penvz_len,__envz2,__envz2_len,__override_))
#elif defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep) || defined(__CRT_HAVE_realloc)
#include <libc/local/envz/envz_merge.h>
/* Adds each entry in `ENVZ2' to `ENVZ & ENVZ_LEN', as if with `envz_add()'.
 * If `OVERRIDE' is true, then values in `ENVZ2' will supersede those
 * with the same name in `ENV', otherwise they don't */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_merge, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL envz_merge)(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __envz2, size_t __envz2_len, int __override_) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_merge))(__penvz, __penvz_len, __envz2, __envz2_len, __override_); })
#endif /* ... */
#ifdef __CRT_HAVE_envz_remove
/* Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,envz_remove,(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __name),(__penvz,__penvz_len,__name))
#else /* __CRT_HAVE_envz_remove */
#include <libc/local/envz/envz_remove.h>
/* Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_remove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_NCX(__LIBCCALL envz_remove)(char **__restrict __penvz, size_t *__restrict __penvz_len, char const *__restrict __name) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_remove))(__penvz, __penvz_len, __name); })
#endif /* !__CRT_HAVE_envz_remove */
#ifdef __CRT_HAVE_envz_strip
/* Remove entries that have no value attached */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,envz_strip,(char **__restrict __penvz, size_t *__restrict __penvz_len),(__penvz,__penvz_len))
#else /* __CRT_HAVE_envz_strip */
#include <libc/local/envz/envz_strip.h>
/* Remove entries that have no value attached */
__NAMESPACE_LOCAL_USING_OR_IMPL(envz_strip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL envz_strip)(char **__restrict __penvz, size_t *__restrict __penvz_len) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(envz_strip))(__penvz, __penvz_len); })
#endif /* !__CRT_HAVE_envz_strip */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_ENVZ_H */
