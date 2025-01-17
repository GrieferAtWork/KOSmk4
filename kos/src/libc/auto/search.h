/* HASH CRC-32:0xdb9c6913 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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
/* >> insque(3)
 * Insert ELEM into a doubly-linked list, after PREV */
INTDEF ATTR_INOUT_OPT(2) ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd_insque)(void *__restrict elem, void *prev);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> insque(3)
 * Insert ELEM into a doubly-linked list, after PREV */
INTDEF ATTR_INOUT_OPT(2) ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc_insque)(void *__restrict elem, void *prev);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> remque(3)
 * Unlink ELEM from the doubly-linked list that it is in */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd_remque)(void *__restrict elem);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> remque(3)
 * Unlink ELEM from the doubly-linked list that it is in */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc_remque)(void *__restrict elem);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> hsearch(3)
 * Search for entry matching `item.key' in internal hash table.
 * If `action' is `FIND' return found entry or signal error by returning `NULL'.
 * If  `action'  is  `ENTER' replace  existing  data (if  any)  with `item.data' */
INTDEF ENTRY *NOTHROW_NCX(LIBDCALL libd_hsearch)(ENTRY item, ACTION action);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> hsearch(3)
 * Search for entry matching `item.key' in internal hash table.
 * If `action' is `FIND' return found entry or signal error by returning `NULL'.
 * If  `action'  is  `ENTER' replace  existing  data (if  any)  with `item.data' */
INTDEF ENTRY *NOTHROW_NCX(LIBCCALL libc_hsearch)(ENTRY item, ACTION action);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> hcreate(3)
 * Create a new hashing table which will at most contain `nel' elements */
INTDEF int NOTHROW_NCX(LIBDCALL libd_hcreate)(size_t nel);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> hcreate(3)
 * Create a new hashing table which will at most contain `nel' elements */
INTDEF int NOTHROW_NCX(LIBCCALL libc_hcreate)(size_t nel);
/* >> hdestroy(3)
 * Destroy current internal hashing table */
INTDEF void NOTHROW_NCX(LIBCCALL libc_hdestroy)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> hsearch_r(3)
 * Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF ATTR_INOUT(4) ATTR_OUT(3) int NOTHROW_NCX(LIBDCALL libd_hsearch_r)(ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> hsearch_r(3)
 * Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF ATTR_INOUT(4) ATTR_OUT(3) int NOTHROW_NCX(LIBCCALL libc_hsearch_r)(ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> hcreate_r(3) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_hcreate_r)(size_t nel, struct hsearch_data *htab);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> hcreate_r(3) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_hcreate_r)(size_t nel, struct hsearch_data *htab);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> hdestroy_r(3) */
INTDEF void NOTHROW_NCX(LIBDCALL libd_hdestroy_r)(struct hsearch_data *htab);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> hdestroy_r(3) */
INTDEF void NOTHROW_NCX(LIBCCALL libc_hdestroy_r)(struct hsearch_data *htab);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tsearch(3), tsearch_r(3)
 * Search for an  entry matching  the given `key'  in the  tree
 * pointed to by `*rootp' and insert a new element if not found */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) NONNULL((3)) void *NOTHROW_CB_NCX(LIBDCALL libd_tsearch_r)(void const *key, void **vrootp, int (LIBDCALL *compar)(void const *a, void const *b, void *arg), void *arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tsearch(3), tsearch_r(3)
 * Search for an  entry matching  the given `key'  in the  tree
 * pointed to by `*rootp' and insert a new element if not found */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) NONNULL((3)) void *NOTHROW_CB_NCX(LIBCCALL libc_tsearch_r)(void const *key, void **vrootp, int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tfind(3), tfind_r(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to  by `*rootp'. If no matching entry is available return `NULL' */
INTDEF ATTR_IN_OPT(1) ATTR_IN_OPT(2) NONNULL((3)) void *NOTHROW_CB_NCX(LIBDCALL libd_tfind_r)(void const *key, void *const *vrootp, int (LIBDCALL *compar)(void const *a, void const *b, void *arg), void *arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tfind(3), tfind_r(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to  by `*rootp'. If no matching entry is available return `NULL' */
INTDEF ATTR_IN_OPT(1) ATTR_IN_OPT(2) NONNULL((3)) void *NOTHROW_CB_NCX(LIBCCALL libc_tfind_r)(void const *key, void *const *vrootp, int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tdelete(3), tdelete_r(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) NONNULL((3)) void *NOTHROW_CB_NCX(LIBDCALL libd_tdelete_r)(void const *__restrict key, void **__restrict vrootp, int (LIBDCALL *compar)(void const *a, void const *b, void *arg), void *arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tdelete(3), tdelete_r(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) NONNULL((3)) void *NOTHROW_CB_NCX(LIBCCALL libc_tdelete_r)(void const *__restrict key, void **__restrict vrootp, int (LIBCCALL *compar)(void const *a, void const *b, void *arg), void *arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> twalk(3), twalk_r(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
INTDEF ATTR_IN_OPT(1) void NOTHROW_CB_NCX(LIBDCALL libd_twalk_r)(void const *root, void (LIBDCALL *action)(void const *nodep, VISIT value, int level, void *arg), void *arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> twalk(3), twalk_r(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
INTDEF ATTR_IN_OPT(1) void NOTHROW_CB_NCX(LIBCCALL libc_twalk_r)(void const *root, void (LIBCCALL *action)(void const *nodep, VISIT value, int level, void *arg), void *arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tdestroy(3), tdestroy_r(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
INTDEF ATTR_INOUT_OPT(1) NONNULL((2)) void NOTHROW_CB_NCX(LIBDCALL libd_tdestroy_r)(void *root, void (LIBDCALL *freefct)(void *nodep, void *arg), void *arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tdestroy(3), tdestroy_r(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
INTDEF ATTR_INOUT_OPT(1) NONNULL((2)) void NOTHROW_CB_NCX(LIBCCALL libc_tdestroy_r)(void *root, void (LIBCCALL *freefct)(void *nodep, void *arg), void *arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tsearch(3), tsearch_r(3)
 * Search for an  entry matching  the given `key'  in the  tree
 * pointed to by `*rootp' and insert a new element if not found */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) NONNULL((3)) void *NOTHROW_CB_NCX(LIBDCALL libd_tsearch)(void const *key, void **vrootp, int (LIBDCALL *compar)(void const *a, void const *b));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tsearch(3), tsearch_r(3)
 * Search for an  entry matching  the given `key'  in the  tree
 * pointed to by `*rootp' and insert a new element if not found */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) NONNULL((3)) void *NOTHROW_CB_NCX(LIBCCALL libc_tsearch)(void const *key, void **vrootp, int (LIBCCALL *compar)(void const *a, void const *b));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tfind(3), tfind_r(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to  by `*rootp'. If no matching entry is available return `NULL' */
INTDEF ATTR_IN_OPT(1) ATTR_IN_OPT(2) NONNULL((3)) void *NOTHROW_CB_NCX(LIBDCALL libd_tfind)(void const *key, void *const *vrootp, int (LIBDCALL *compar)(void const *a, void const *b));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tfind(3), tfind_r(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to  by `*rootp'. If no matching entry is available return `NULL' */
INTDEF ATTR_IN_OPT(1) ATTR_IN_OPT(2) NONNULL((3)) void *NOTHROW_CB_NCX(LIBCCALL libc_tfind)(void const *key, void *const *vrootp, int (LIBCCALL *compar)(void const *a, void const *b));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tdelete(3), tdelete_r(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) NONNULL((3)) void *NOTHROW_CB_NCX(LIBDCALL libd_tdelete)(void const *__restrict key, void **__restrict vrootp, int (LIBDCALL *compar)(void const *a, void const *b));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tdelete(3), tdelete_r(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
INTDEF ATTR_INOUT_OPT(2) ATTR_IN_OPT(1) NONNULL((3)) void *NOTHROW_CB_NCX(LIBCCALL libc_tdelete)(void const *__restrict key, void **__restrict vrootp, int (LIBCCALL *compar)(void const *a, void const *b));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> twalk(3), twalk_r(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
INTDEF ATTR_IN_OPT(1) void NOTHROW_CB_NCX(LIBDCALL libd_twalk)(void const *root, void (LIBDCALL *action)(void const *nodep, VISIT value, int level));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> twalk(3), twalk_r(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
INTDEF ATTR_IN_OPT(1) void NOTHROW_CB_NCX(LIBCCALL libc_twalk)(void const *root, void (LIBCCALL *action)(void const *nodep, VISIT value, int level));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tdestroy(3), tdestroy_r(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
INTDEF ATTR_INOUT_OPT(1) NONNULL((2)) void NOTHROW_CB_NCX(LIBDCALL libd_tdestroy)(void *root, void (LIBDCALL *freefct)(void *nodep));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tdestroy(3), tdestroy_r(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
INTDEF ATTR_INOUT_OPT(1) NONNULL((2)) void NOTHROW_CB_NCX(LIBCCALL libc_tdestroy)(void *root, void (LIBCCALL *freefct)(void *nodep));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
INTDEF WUNUSED ATTR_IN(3) ATTR_IN_OPT(1) ATTR_IN_OPT(2) NONNULL((5)) void *NOTHROW_CB_NCX(LIBDCALL libd_lfind)(void const *key, void const *pbase, size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size) */
INTDEF WUNUSED ATTR_IN(3) ATTR_IN_OPT(1) ATTR_IN_OPT(2) NONNULL((5)) void *NOTHROW_CB_NCX(LIBCCALL libc_lfind)(void const *key, void const *pbase, size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> lsearch(3)
 * Perform  linear  search  for  `key'  by  comparing  by  `compar'   function
 * in array [pbase, pbase+pitem_count*item_size) and insert entry if not found */
INTDEF ATTR_INOUT(2) ATTR_INOUT(3) ATTR_IN_OPT(1) NONNULL((5)) void *NOTHROW_CB_NCX(LIBDCALL libd_lsearch)(void const *key, void *pbase, size_t *pitem_count, size_t item_size, int (LIBDCALL *compar)(void const *a, void const *b));
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> lsearch(3)
 * Perform  linear  search  for  `key'  by  comparing  by  `compar'   function
 * in array [pbase, pbase+pitem_count*item_size) and insert entry if not found */
INTDEF ATTR_INOUT(2) ATTR_INOUT(3) ATTR_IN_OPT(1) NONNULL((5)) void *NOTHROW_CB_NCX(LIBCCALL libc_lsearch)(void const *key, void *pbase, size_t *pitem_count, size_t item_size, int (LIBCCALL *compar)(void const *a, void const *b));
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(3) ATTR_IN_OPT(1) ATTR_IN_OPT(2) NONNULL((5)) void *NOTHROW_CB_NCX(LIBDCALL libd__lfind_s)(void const *key, void const *pbase, size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, int (LIBDCALL *compar)(void *arg, void const *a, void const *b), void *arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(3) ATTR_IN_OPT(1) ATTR_IN_OPT(2) NONNULL((5)) void *NOTHROW_CB_NCX(LIBCCALL libc__lfind_s)(void const *key, void const *pbase, size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, int (LIBCCALL *compar)(void *arg, void const *a, void const *b), void *arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_INOUT(2) ATTR_INOUT(3) ATTR_IN_OPT(1) NONNULL((5)) void *NOTHROW_CB_NCX(LIBDCALL libd__lsearch_s)(void const *key, void *pbase, size_t *pitem_count, size_t item_size, int (LIBDCALL *compar)(void *arg, void const *a, void const *b), void *arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_INOUT(2) ATTR_INOUT(3) ATTR_IN_OPT(1) NONNULL((5)) void *NOTHROW_CB_NCX(LIBCCALL libc__lsearch_s)(void const *key, void *pbase, size_t *pitem_count, size_t item_size, int (LIBCCALL *compar)(void *arg, void const *a, void const *b), void *arg);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SEARCH_H */
