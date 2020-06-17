/* HASH CRC-32:0x137db81c */
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
#ifndef GUARD_LIBC_AUTO_SEARCH_H
#define GUARD_LIBC_AUTO_SEARCH_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <search.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Insert ELEM into a doubly-linked list, after PREV */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_insque)(void *__restrict elem, void *prev);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Insert ELEM into a doubly-linked list, after PREV */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_insque)(void *__restrict elem, void *prev);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Unlink ELEM from the doubly-linked list that it is in */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_remque)(void *__restrict elem);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Unlink ELEM from the doubly-linked list that it is in */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_remque)(void *__restrict elem);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Search for entry matching ITEM.key in internal hash table.
 * If ACTION is `FIND' return found entry or signal error by returning NULL.
 * If ACTION is `ENTER' replace existing data (if any) with ITEM.data */
INTDEF ENTRY *NOTHROW_NCX(LIBDCALL libd_hsearch)(ENTRY item, ACTION action);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Search for entry matching ITEM.key in internal hash table.
 * If ACTION is `FIND' return found entry or signal error by returning NULL.
 * If ACTION is `ENTER' replace existing data (if any) with ITEM.data */
INTDEF ENTRY *NOTHROW_NCX(LIBCCALL libc_hsearch)(ENTRY item, ACTION action);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Create a new hashing table which will at most contain NEL elements */
INTDEF int NOTHROW_NCX(LIBDCALL libd_hcreate)(size_t nel);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Create a new hashing table which will at most contain NEL elements */
INTDEF int NOTHROW_NCX(LIBCCALL libc_hcreate)(size_t nel);
/* Destroy current internal hashing table */
INTDEF void NOTHROW_NCX(LIBCCALL libc_hdestroy)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF NONNULL((3, 4)) int NOTHROW_NCX(LIBDCALL libd_hsearch_r)(ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF NONNULL((3, 4)) int NOTHROW_NCX(LIBCCALL libc_hsearch_r)(ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF int NOTHROW_NCX(LIBDCALL libd_hcreate_r)(size_t nel, struct hsearch_data *htab);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF int NOTHROW_NCX(LIBCCALL libc_hcreate_r)(size_t nel, struct hsearch_data *htab);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF void NOTHROW_NCX(LIBDCALL libd_hdestroy_r)(struct hsearch_data *htab);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF void NOTHROW_NCX(LIBCCALL libc_hdestroy_r)(struct hsearch_data *htab);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Search for an entry matching the given KEY in the tree
 * pointed to by *ROOTP and insert a new element if not found */
INTDEF NONNULL((3)) void *NOTHROW_NCX(LIBDCALL libd_tsearch)(void const *key, void **vrootp, __compar_fn_t compar);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Search for an entry matching the given KEY in the tree
 * pointed to by *ROOTP and insert a new element if not found */
INTDEF NONNULL((3)) void *NOTHROW_NCX(LIBCCALL libc_tsearch)(void const *key, void **vrootp, __compar_fn_t compar);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Search for an entry matching the given KEY in the tree pointed
 * to by *ROOTP. If no matching entry is available return NULL */
INTDEF NONNULL((3)) void *NOTHROW_NCX(LIBDCALL libd_tfind)(void const *key, void *const *vrootp, __compar_fn_t compar);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Search for an entry matching the given KEY in the tree pointed
 * to by *ROOTP. If no matching entry is available return NULL */
INTDEF NONNULL((3)) void *NOTHROW_NCX(LIBCCALL libc_tfind)(void const *key, void *const *vrootp, __compar_fn_t compar);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Remove the element matching KEY from the tree pointed to by *ROOTP */
INTDEF NONNULL((3)) void *NOTHROW_NCX(LIBDCALL libd_tdelete)(void const *__restrict key, void **__restrict vrootp, __compar_fn_t compar);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Remove the element matching KEY from the tree pointed to by *ROOTP */
INTDEF NONNULL((3)) void *NOTHROW_NCX(LIBCCALL libc_tdelete)(void const *__restrict key, void **__restrict vrootp, __compar_fn_t compar);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
INTDEF void NOTHROW_NCX(LIBDCALL libd_twalk)(void const *root, __action_fn_t action);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
INTDEF void NOTHROW_NCX(LIBCCALL libc_twalk)(void const *root, __action_fn_t action);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Destroy the whole tree, call FREEFCT for each node or leaf */
INTDEF NONNULL((2)) void NOTHROW_NCX(LIBDCALL libd_tdestroy)(void *root, __free_fn_t freefct);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Destroy the whole tree, call FREEFCT for each node or leaf */
INTDEF NONNULL((2)) void NOTHROW_NCX(LIBCCALL libc_tdestroy)(void *root, __free_fn_t freefct);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
INTDEF NONNULL((2, 3, 5)) void *NOTHROW_NCX(LIBDCALL libd_lfind)(void const *key, void const *base, size_t __KOS_FIXED_CONST *nmemb, size_t size, __compar_fn_t compar);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
INTDEF NONNULL((2, 3, 5)) void *NOTHROW_NCX(LIBCCALL libc_lfind)(void const *key, void const *base, size_t __KOS_FIXED_CONST *nmemb, size_t size, __compar_fn_t compar);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Perform linear search for KEY by comparing by COMPAR function
 * in array [BASE, BASE+NMEMB*SIZE) and insert entry if not found */
INTDEF NONNULL((2, 3, 5)) void *NOTHROW_NCX(LIBDCALL libd_lsearch)(void const *key, void *base, size_t *nmemb, size_t size, __compar_fn_t compar);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Perform linear search for KEY by comparing by COMPAR function
 * in array [BASE, BASE+NMEMB*SIZE) and insert entry if not found */
INTDEF NONNULL((2, 3, 5)) void *NOTHROW_NCX(LIBCCALL libc_lsearch)(void const *key, void *base, size_t *nmemb, size_t size, __compar_fn_t compar);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SEARCH_H */
