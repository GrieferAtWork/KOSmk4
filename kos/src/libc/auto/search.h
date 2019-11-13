/* HASH CRC-32:0x5ffa473a */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

#ifndef __KERNEL__
/* Insert ELEM into a doubly-linked list, after PREV */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_insque)(void *__restrict elem, void *prev);
/* Unlink ELEM from the doubly-linked list that it is in */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_remque)(void *__restrict elem);
/* For the used double hash method the table size has to be a prime. To
 * correct the user given table size we need a prime test.  This trivial
 * algorithm is adequate because
 * a)  the code is (most probably) called a few times per program run and
 * b)  the number is small because the table must fit in the core */
INTDEF ATTR_CONST int NOTHROW_NCX(LIBCCALL libc_isprime)(unsigned int number);
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTDEF int NOTHROW_NCX(LIBCCALL libc_hsearch_r)(ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab);
/* Possibly "split" a node with two red successors, and/or fix up two red
 * edges in a row. ROOTP is a pointer to the lowest node we visited, PARENTP
 * and GPARENTP pointers to its parent/grandparent. P_R and GP_R contain the
 * comparison values that determined which way was taken in the tree to reach
 * ROOTP. MODE is 1 if we need not do the split, but must check for two red
 * edges between GPARENTP and ROOTP */
INTDEF void NOTHROW_NCX(LIBCCALL libc_maybe_split_for_insert)(void **rootp, void **parentp, void **gparentp, int p_r, int gp_r, int mode);
/* Search for an entry matching the given KEY in the tree pointed
 * to by *ROOTP. If no matching entry is available return NULL */
INTDEF void *NOTHROW_NCX(LIBCCALL libc_tfind)(void const *key, void *const *vrootp, __compar_fn_t compar);
/* Walk the nodes of a tree.
 * ROOT is the root of the tree to be walked, ACTION the function to be
 * called at each node. LEVEL is the level of ROOT in the whole tree */
INTDEF void NOTHROW_NCX(LIBCCALL libc_trecurse)(void const *root, __action_fn_t action, int level);
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
INTDEF void NOTHROW_NCX(LIBCCALL libc_twalk)(void const *root, __action_fn_t action);
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
INTDEF void *NOTHROW_NCX(LIBCCALL libc_lfind)(void const *key, void const *base, size_t *nmemb, size_t size, __compar_fn_t compar);
/* Perform linear search for KEY by comparing by COMPAR function
 * in array [BASE, BASE+NMEMB*SIZE) and insert entry if not found */
INTDEF void *NOTHROW_NCX(LIBCCALL libc_lsearch)(void const *key, void *base, size_t *nmemb, size_t size, __compar_fn_t compar);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SEARCH_H */
