/* HASH CRC-32:0x398ec897 */
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
#ifndef GUARD_LIBC_AUTO_ENVZ_H
#define GUARD_LIBC_AUTO_ENVZ_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <envz.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> envz_entry(3)
 * Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to  this
 * position are actually compared! */
INTDEF ATTR_PURE WUNUSED ATTR_IN(3) ATTR_INS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_envz_entry)(char const *__restrict envz, size_t envz_len, char const *__restrict name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> envz_entry(3)
 * Find and return the entry for `name' in `envz', or `NULL' if not found.
 * If `name' contains a `=' character, only characters leading up to  this
 * position are actually compared! */
INTDEF ATTR_PURE WUNUSED ATTR_IN(3) ATTR_INS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_envz_entry)(char const *__restrict envz, size_t envz_len, char const *__restrict name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> envz_get(3)
 * Return the value in `envz'  attached to `name', or  `NULL'
 * if no such entry exists, or the entry doesn't have a value
 * portion (i.e. doesn't contain a `='-character) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(3) ATTR_INS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_envz_get)(char const *__restrict envz, size_t envz_len, char const *__restrict name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> envz_get(3)
 * Return the value in `envz'  attached to `name', or  `NULL'
 * if no such entry exists, or the entry doesn't have a value
 * portion (i.e. doesn't contain a `='-character) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(3) ATTR_INS(1, 2) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_envz_get)(char const *__restrict envz, size_t envz_len, char const *__restrict name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> envz_add(3)
 * Add an entry `name=value' to `penvz'. If another entry for `name'
 * already existed before, that entry is removed. If `name' is NULL,
 * the entry created  doesn't have a  value-portion (i.e. `name'  is
 * added to `penvz' as-is, without the trailing `=value') */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_IN_OPT(4) error_t NOTHROW_NCX(LIBDCALL libd_envz_add)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict name, char const *value);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> envz_add(3)
 * Add an entry `name=value' to `penvz'. If another entry for `name'
 * already existed before, that entry is removed. If `name' is NULL,
 * the entry created  doesn't have a  value-portion (i.e. `name'  is
 * added to `penvz' as-is, without the trailing `=value') */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) ATTR_IN_OPT(4) error_t NOTHROW_NCX(LIBCCALL libc_envz_add)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict name, char const *value);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> envz_merge(3)
 * Add all entries from `envz2' to `penvz', as though `envz_add()' was
 * called for each contained `name=value' pair (using `NULL' for value
 * on pairs that doesn't have a value-portion.
 * If individual entries already existed in `penvz', behavior  depends
 * on `override_', which if non-zero will cause existing entries to be
 * overwritten, and otherwise if zero, will cause them to stay. */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INS(3, 4) error_t NOTHROW_NCX(LIBDCALL libd_envz_merge)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict envz2, size_t envz2_len, int override_);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> envz_merge(3)
 * Add all entries from `envz2' to `penvz', as though `envz_add()' was
 * called for each contained `name=value' pair (using `NULL' for value
 * on pairs that doesn't have a value-portion.
 * If individual entries already existed in `penvz', behavior  depends
 * on `override_', which if non-zero will cause existing entries to be
 * overwritten, and otherwise if zero, will cause them to stay. */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) ATTR_INS(3, 4) error_t NOTHROW_NCX(LIBCCALL libc_envz_merge)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict envz2, size_t envz2_len, int override_);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> envz_remove(3)
 * Remove an entry matching `name' from `penvz',
 * or  do  nothing  if  no  such  entry  exists. */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW_NCX(LIBDCALL libd_envz_remove)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> envz_remove(3)
 * Remove an entry matching `name' from `penvz',
 * or  do  nothing  if  no  such  entry  exists. */
INTDEF ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW_NCX(LIBCCALL libc_envz_remove)(char **__restrict penvz, size_t *__restrict penvz_len, char const *__restrict name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> envz_strip(3)
 * Remove all entries from `penvz' that don't have a value-portion. */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW_NCX(LIBDCALL libd_envz_strip)(char **__restrict penvz, size_t *__restrict penvz_len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> envz_strip(3)
 * Remove all entries from `penvz' that don't have a value-portion. */
INTDEF ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW_NCX(LIBCCALL libc_envz_strip)(char **__restrict penvz, size_t *__restrict penvz_len);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ENVZ_H */
