/* HASH CRC-32:0x13b70ce7 */
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
#ifndef GUARD_LIBC_AUTO_DYN_STRING_H
#define GUARD_LIBC_AUTO_DYN_STRING_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <dyn-string.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_init(3)
 * Initialize a given `struct dyn_string'
 * @param: min_chars: Minimum value for `self->allocated'
 * @return: 1: Always returns `1' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_dyn_string_init)(struct dyn_string *self, __STDC_INT_AS_SIZE_T min_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_init(3)
 * Initialize a given `struct dyn_string'
 * @param: min_chars: Minimum value for `self->allocated'
 * @return: 1: Always returns `1' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_dyn_string_init)(struct dyn_string *self, __STDC_INT_AS_SIZE_T min_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_init(3)
 * Allocate+initialize a new `dyn_string_t'
 * @param: min_chars: Minimum value for `return->allocated'
 * @return: * : The new dyn_string object (free using `dyn_string_delete(3)')
 *              -> uses `xmalloc(3)', so no error-return-value */
INTDEF ATTR_RETNONNULL struct dyn_string *NOTHROW_NCX(LIBDCALL libd_dyn_string_new)(__STDC_INT_AS_SIZE_T min_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_init(3)
 * Allocate+initialize a new `dyn_string_t'
 * @param: min_chars: Minimum value for `return->allocated'
 * @return: * : The new dyn_string object (free using `dyn_string_delete(3)')
 *              -> uses `xmalloc(3)', so no error-return-value */
INTDEF ATTR_RETNONNULL struct dyn_string *NOTHROW_NCX(LIBCCALL libc_dyn_string_new)(__STDC_INT_AS_SIZE_T min_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_delete(3)
 * Delete a `dyn_string_t' previously allocated by `dyn_string_new(3)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_dyn_string_delete)(struct dyn_string *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_delete(3)
 * Delete a `dyn_string_t' previously allocated by `dyn_string_new(3)' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_dyn_string_delete)(struct dyn_string *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_release(3)
 * Steal the  internal string  buffer  of `self'  and  free(self)
 * The returned pointer must be `free(3)'d once no longer needed. */
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_dyn_string_release)(struct dyn_string *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_release(3)
 * Steal the  internal string  buffer  of `self'  and  free(self)
 * The returned pointer must be `free(3)'d once no longer needed. */
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_dyn_string_release)(struct dyn_string *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_release(3)
 * Ensure that  `self' has  sufficient  space for  at  least
 * `min_chars' total characters (excluding the trailing NUL)
 * @return: * : Always re-returns `self'
 *              -> uses `xmalloc(3)', so no error-return-value */
INTDEF ATTR_RETNONNULL NONNULL((1)) struct dyn_string *NOTHROW_NCX(LIBDCALL libd_dyn_string_resize)(struct dyn_string *self, __STDC_INT_AS_SIZE_T min_chars);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_release(3)
 * Ensure that  `self' has  sufficient  space for  at  least
 * `min_chars' total characters (excluding the trailing NUL)
 * @return: * : Always re-returns `self'
 *              -> uses `xmalloc(3)', so no error-return-value */
INTDEF ATTR_RETNONNULL NONNULL((1)) struct dyn_string *NOTHROW_NCX(LIBCCALL libc_dyn_string_resize)(struct dyn_string *self, __STDC_INT_AS_SIZE_T min_chars);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_clear(3)
 * Set the length of `self' to `0' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_dyn_string_clear)(struct dyn_string *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_clear(3)
 * Set the length of `self' to `0' */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_dyn_string_clear)(struct dyn_string *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_copy(3)
 * Assign `src' to `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_copy)(struct dyn_string *dst, struct dyn_string __KOS_FIXED_CONST *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_copy(3)
 * Assign `src' to `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_copy)(struct dyn_string *dst, struct dyn_string __KOS_FIXED_CONST *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_copy_cstr(3)
 * Assign   `src'   to  `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_copy_cstr)(struct dyn_string *dst, char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_copy_cstr(3)
 * Assign   `src'   to  `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_copy_cstr)(struct dyn_string *dst, char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_prepend(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_prepend)(struct dyn_string *dst, struct dyn_string __KOS_FIXED_CONST *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_prepend(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_prepend)(struct dyn_string *dst, struct dyn_string __KOS_FIXED_CONST *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_prepend_cstr(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_prepend_cstr)(struct dyn_string *dst, char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_prepend_cstr(3)
 * Insert `src' at the start of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_prepend_cstr)(struct dyn_string *dst, char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_insert(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 3)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_insert)(struct dyn_string *dst, __STDC_INT_AS_SIZE_T index, struct dyn_string __KOS_FIXED_CONST *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_insert(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 3)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_insert)(struct dyn_string *dst, __STDC_INT_AS_SIZE_T index, struct dyn_string __KOS_FIXED_CONST *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_insert_cstr(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 3)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_insert_cstr)(struct dyn_string *dst, __STDC_INT_AS_SIZE_T index, char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_insert_cstr(3)
 * Insert `src' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 3)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_insert_cstr)(struct dyn_string *dst, __STDC_INT_AS_SIZE_T index, char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_insert_char(3)
 * Insert `ch' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_insert_char)(struct dyn_string *dst, __STDC_INT_AS_SIZE_T index, int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_insert_char(3)
 * Insert `ch' into `dst' at position `index'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_insert_char)(struct dyn_string *dst, __STDC_INT_AS_SIZE_T index, int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_append(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_append)(struct dyn_string *dst, struct dyn_string __KOS_FIXED_CONST *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_append(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_append)(struct dyn_string *dst, struct dyn_string __KOS_FIXED_CONST *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_append_cstr(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_append_cstr)(struct dyn_string *dst, char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_append_cstr(3)
 * Append `src' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_append_cstr)(struct dyn_string *dst, char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_append_char(3)
 * Append `ch' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_append_char)(struct dyn_string *dst, int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_append_char(3)
 * Append `ch' to the end of `dst'
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_append_char)(struct dyn_string *dst, int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_substring(3)
 * Assign  the substring `src[start:end]'  to `dst'. Note that
 * the given indices _must_ be properly ordered, and in-range!
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_dyn_string_substring)(struct dyn_string *dst, struct dyn_string __KOS_FIXED_CONST *src, __STDC_INT_AS_SIZE_T start, __STDC_INT_AS_SIZE_T end);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_substring(3)
 * Assign  the substring `src[start:end]'  to `dst'. Note that
 * the given indices _must_ be properly ordered, and in-range!
 * @return: 1 : Always returned (uses `xmalloc(3)', so no error-return-value) */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dyn_string_substring)(struct dyn_string *dst, struct dyn_string __KOS_FIXED_CONST *src, __STDC_INT_AS_SIZE_T start, __STDC_INT_AS_SIZE_T end);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dyn_string_eq(3)
 * Return `1' if the contents of the given strings are equal; `0' otherwise.
 * @return: 0 : Strings differ
 * @return: 1 : Strings are identical */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBDCALL libd_dyn_string_eq)(struct dyn_string __KOS_FIXED_CONST *lhs, struct dyn_string __KOS_FIXED_CONST *rhs);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> dyn_string_eq(3)
 * Return `1' if the contents of the given strings are equal; `0' otherwise.
 * @return: 0 : Strings differ
 * @return: 1 : Strings are identical */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_dyn_string_eq)(struct dyn_string __KOS_FIXED_CONST *lhs, struct dyn_string __KOS_FIXED_CONST *rhs);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_DYN_STRING_H */
