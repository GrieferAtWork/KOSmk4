/* HASH CRC-32:0x5e7fb657 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SEARCH_C
#define GUARD_LIBC_AUTO_DOSABI_SEARCH_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../search.h"

DECL_BEGIN

/* Insert ELEM into a doubly-linked list, after PREV */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_insque)(void *__restrict elem,
                                  void *prev) {
	libc_insque(elem, prev);
}
/* Unlink ELEM from the doubly-linked list that it is in */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_remque)(void *__restrict elem) {
	libc_remque(elem);
}
/* Search for entry matching ITEM.key in internal hash table.
 * If ACTION is `FIND' return found entry or signal error by returning NULL.
 * If ACTION is `ENTER' replace existing data (if any) with ITEM.data */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") ENTRY *
NOTHROW_NCX(LIBDCALL libd_hsearch)(ENTRY item,
                                   ACTION action) {
	return libc_hsearch(item, action);
}
/* Create a new hashing table which will at most contain NEL elements */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") int
NOTHROW_NCX(LIBDCALL libd_hcreate)(size_t nel) {
	return libc_hcreate(nel);
}
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") NONNULL((3, 4)) int
NOTHROW_NCX(LIBDCALL libd_hsearch_r)(ENTRY item,
                                     ACTION action,
                                     ENTRY **retval,
                                     struct hsearch_data *htab) {
	return libc_hsearch_r(item, action, retval, htab);
}
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") int
NOTHROW_NCX(LIBDCALL libd_hcreate_r)(size_t nel,
                                     struct hsearch_data *htab) {
	return libc_hcreate_r(nel, htab);
}
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") void
NOTHROW_NCX(LIBDCALL libd_hdestroy_r)(struct hsearch_data *htab) {
	libc_hdestroy_r(htab);
}
/* Search for an entry matching the given KEY in the tree
 * pointed to by *ROOTP and insert a new element if not found */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") NONNULL((3)) void *
NOTHROW_NCX(LIBDCALL libd_tsearch)(void const *key,
                                   void **vrootp,
                                   __compar_fn_t compar) {
	return libc_tsearch(key, vrootp, compar);
}
/* Search for an entry matching the given KEY in the tree pointed
 * to by *ROOTP. If no matching entry is available return NULL */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") NONNULL((3)) void *
NOTHROW_NCX(LIBDCALL libd_tfind)(void const *key,
                                 void *const *vrootp,
                                 __compar_fn_t compar) {
	return libc_tfind(key, vrootp, compar);
}
/* Remove the element matching KEY from the tree pointed to by *ROOTP */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") NONNULL((3)) void *
NOTHROW_NCX(LIBDCALL libd_tdelete)(void const *__restrict key,
                                   void **__restrict vrootp,
                                   __compar_fn_t compar) {
	return libc_tdelete(key, vrootp, compar);
}
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") void
NOTHROW_NCX(LIBDCALL libd_twalk)(void const *root,
                                 __action_fn_t action) {
	libc_twalk(root, action);
}
/* Destroy the whole tree, call FREEFCT for each node or leaf */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") NONNULL((2)) void
NOTHROW_NCX(LIBDCALL libd_tdestroy)(void *root,
                                    __free_fn_t freefct) {
	libc_tdestroy(root, freefct);
}
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") NONNULL((2, 3, 5)) void *
NOTHROW_NCX(LIBDCALL libd_lfind)(void const *key,
                                 void const *base,
                                 size_t __KOS_FIXED_CONST *nmemb,
                                 size_t size,
                                 __compar_fn_t compar) {
	return libc_lfind(key, base, nmemb, size, compar);
}
/* Perform linear search for KEY by comparing by COMPAR function
 * in array [BASE, BASE+NMEMB*SIZE) and insert entry if not found */
INTERN ATTR_SECTION(".text.crt.dos.utility.search") NONNULL((2, 3, 5)) void *
NOTHROW_NCX(LIBDCALL libd_lsearch)(void const *key,
                                   void *base,
                                   size_t *nmemb,
                                   size_t size,
                                   __compar_fn_t compar) {
	return libc_lsearch(key, base, nmemb, size, compar);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$insque, libd_insque);
DEFINE_PUBLIC_ALIAS(DOS$remque, libd_remque);
DEFINE_PUBLIC_ALIAS(DOS$hsearch, libd_hsearch);
DEFINE_PUBLIC_ALIAS(DOS$hcreate, libd_hcreate);
DEFINE_PUBLIC_ALIAS(DOS$hsearch_r, libd_hsearch_r);
DEFINE_PUBLIC_ALIAS(DOS$hcreate_r, libd_hcreate_r);
DEFINE_PUBLIC_ALIAS(DOS$hdestroy_r, libd_hdestroy_r);
DEFINE_PUBLIC_ALIAS(DOS$__tsearch, libd_tsearch);
DEFINE_PUBLIC_ALIAS(DOS$tsearch, libd_tsearch);
DEFINE_PUBLIC_ALIAS(DOS$__tfind, libd_tfind);
DEFINE_PUBLIC_ALIAS(DOS$tfind, libd_tfind);
DEFINE_PUBLIC_ALIAS(DOS$__tdelete, libd_tdelete);
DEFINE_PUBLIC_ALIAS(DOS$tdelete, libd_tdelete);
DEFINE_PUBLIC_ALIAS(DOS$__twalk, libd_twalk);
DEFINE_PUBLIC_ALIAS(DOS$twalk, libd_twalk);
DEFINE_PUBLIC_ALIAS(DOS$tdestroy, libd_tdestroy);
DEFINE_PUBLIC_ALIAS(DOS$lfind, libd_lfind);
DEFINE_PUBLIC_ALIAS(DOS$lsearch, libd_lsearch);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SEARCH_C */
