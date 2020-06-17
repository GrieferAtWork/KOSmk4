/* HASH CRC-32:0x4b09a090 */
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
#ifndef GUARD_LIBC_AUTO_ENVZ_H
#define GUARD_LIBC_AUTO_ENVZ_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <envz.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
INTDEF ATTR_PURE WUNUSED NONNULL((3)) char *NOTHROW_NCX(LIBDCALL libd_envz_entry)(char const *__restrict envz, size_t envz_len, char const *__restrict name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns a pointer to the entry in `ENVZ' for `NAME', or `NULL' if there is none
 * Note that if `name' contains a `=' character, only characters leading up to this
 * position are actually compared! */
INTDEF ATTR_PURE WUNUSED NONNULL((3)) char *NOTHROW_NCX(LIBCCALL libc_envz_entry)(char const *__restrict envz, size_t envz_len, char const *__restrict name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
INTDEF ATTR_PURE WUNUSED NONNULL((3)) char *NOTHROW_NCX(LIBDCALL libd_envz_get)(char const *__restrict envz, size_t envz_len, char const *__restrict name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Returns a pointer to the value portion of the entry
 * in `ENVZ' for `NAME', or `NULL' if there is none. */
INTDEF ATTR_PURE WUNUSED NONNULL((3)) char *NOTHROW_NCX(LIBCCALL libc_envz_get)(char const *__restrict envz, size_t envz_len, char const *__restrict name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Adds an entry for `NAME' with value `VALUE' to `ENVZ & ENVZ_LEN'. If an entry
 * with the same name already exists in `ENVZ', it is removed. If `VALUE' is
 * `NULL', then the new entry will not have a value portion, meaning that `envz_get()'
 * will return `NULL', although `envz_entry()' will still return an entry. This is handy
 * because when merging with another envz, the null entry can override an
 * entry in the other one. Such entries can be removed with `envz_strip()' */
INTDEF NONNULL((1, 2, 3)) error_t NOTHROW_NCX(LIBDCALL libd_envz_add)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict name, char const *value);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Adds an entry for `NAME' with value `VALUE' to `ENVZ & ENVZ_LEN'. If an entry
 * with the same name already exists in `ENVZ', it is removed. If `VALUE' is
 * `NULL', then the new entry will not have a value portion, meaning that `envz_get()'
 * will return `NULL', although `envz_entry()' will still return an entry. This is handy
 * because when merging with another envz, the null entry can override an
 * entry in the other one. Such entries can be removed with `envz_strip()' */
INTDEF NONNULL((1, 2, 3)) error_t NOTHROW_NCX(LIBCCALL libc_envz_add)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict name, char const *value);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Adds each entry in `ENVZ2' to `ENVZ & ENVZ_LEN', as if with `envz_add()'.
 * If `OVERRIDE' is true, then values in `ENVZ2' will supersede those
 * with the same name in `ENV', otherwise they don't */
INTDEF NONNULL((1, 2, 3)) error_t NOTHROW_NCX(LIBDCALL libd_envz_merge)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict envz2, size_t envz2_len, int override_);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Adds each entry in `ENVZ2' to `ENVZ & ENVZ_LEN', as if with `envz_add()'.
 * If `OVERRIDE' is true, then values in `ENVZ2' will supersede those
 * with the same name in `ENV', otherwise they don't */
INTDEF NONNULL((1, 2, 3)) error_t NOTHROW_NCX(LIBCCALL libc_envz_merge)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict envz2, size_t envz2_len, int override_);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any */
INTDEF NONNULL((1, 2, 3)) void NOTHROW_NCX(LIBDCALL libd_envz_remove)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any */
INTDEF NONNULL((1, 2, 3)) void NOTHROW_NCX(LIBCCALL libc_envz_remove)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Remove entries that have no value attached */
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(LIBDCALL libd_envz_strip)(char **__restrict penvz, size_t *__restrict penvz_len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Remove entries that have no value attached */
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(LIBCCALL libc_envz_strip)(char **__restrict penvz, size_t *__restrict penvz_len);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ENVZ_H */
