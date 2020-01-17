/* HASH CRC-32:0xc86758e2 */
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
#ifndef GUARD_LIBC_USER_SEARCH_H
#define GUARD_LIBC_USER_SEARCH_H 1

#include "../api.h"
#include "../auto/search.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <search.h>

DECL_BEGIN

/* Search for entry matching ITEM.key in internal hash table.
 * If ACTION is `FIND' return found entry or signal error by returning NULL.
 * If ACTION is `ENTER' replace existing data (if any) with ITEM.data */
INTDEF ENTRY *NOTHROW_NCX(LIBCCALL libc_hsearch)(ENTRY item, ACTION action);
/* Create a new hashing table which will at most contain NEL elements */
INTDEF int NOTHROW_NCX(LIBCCALL libc_hcreate)(size_t nel);
/* Destroy current internal hashing table */
INTDEF void NOTHROW_NCX(LIBCCALL libc_hdestroy)(void);
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF int NOTHROW_NCX(LIBCCALL libc_hcreate_r)(size_t nel, struct hsearch_data *htab);
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF void NOTHROW_NCX(LIBCCALL libc_hdestroy_r)(struct hsearch_data *htab);
/* Search for an entry matching the given KEY in the tree
 * pointed to by *ROOTP and insert a new element if not found */
INTDEF void *NOTHROW_NCX(LIBCCALL libc_tsearch)(void const *key, void **vrootp, __compar_fn_t compar);
/* Remove the element matching KEY from the tree pointed to by *ROOTP */
INTDEF void *NOTHROW_NCX(LIBCCALL libc_tdelete)(void const *__restrict key, void **__restrict vrootp, __compar_fn_t compar);
/* Destroy the whole tree, call FREEFCT for each node or leaf */
INTDEF void NOTHROW_NCX(LIBCCALL libc_tdestroy)(void *root, __free_fn_t freefct);

DECL_END

#endif /* !GUARD_LIBC_USER_SEARCH_H */
