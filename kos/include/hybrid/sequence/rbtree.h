/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_SEQUENCE_RBTREE_H
#define __GUARD_HYBRID_SEQUENCE_RBTREE_H 1

#include "../../__stdinc.h"

/*
 * ====== Red-Black tree specs ======
 *
 * Red-Black trees:
 *     O(rb.locate)     = O(log2(N))
 *     O(rb.insert)     = O(log2(N))
 *     O(rb.remove)     = O(log2(N))
 *     O(rb.nextnode)   = O(1)
 *     O(rb.prevnode)   = O(1)
 *       rb.memory      = (3 * sizeof(void *) + C)*N + 1BIT*N
 *
 * Left-leaning Red-Black trees:
 *     O(llrb.locate)   = O(log2(N)) == O(rb.locate)
 *     O(llrb.insert)   = O(log2(N)) >  O(rb.insert)
 *     O(llrb.remove)   = O(log2(N)) >  O(rb.remove)
 *     O(llrb.nextnode) = N/A
 *     O(llrb.prevnode) = N/A
 *       llrb.memory    = (2 * sizeof(void *) + C)*N + 1BIT*N
 *
 * Or in order words: Run times for both variants of red-black trees
 * grow logarithmically, with left-leaning trees having a slightly
 * slower insert/remove function (the removenode() function also has
 * to compare keys of nodes to-be removed, meaning that this function
 * also becomes slower when comparing keys is slow)
 */


#define RBTREE_NODE(T)                                                        \
	struct {                                                                  \
		T *rb_par; /* [0..1] Parent node, or NULL for the tree-root. */       \
		T *rb_lhs; /* [0..1] Child node with a key < the one of this node. */ \
		T *rb_rhs; /* [0..1] Child node with a key > the one of this node. */ \
	}

#define LLRBTREE_NODE(T)                                                      \
	struct {                                                                  \
		T *rb_lhs; /* [0..1] Child node with a key < the one of this node. */ \
		T *rb_rhs; /* [0..1] Child node with a key > the one of this node. */ \
	}

#define RBTREE_NODE_WITH_KEY(T, Tkey)                                           \
	struct {                                                                    \
		T   *rb_par; /* [0..1] Parent node, or NULL for the tree-root. */       \
		T   *rb_lhs; /* [0..1] Child node with a key < the one of this node. */ \
		T   *rb_rhs; /* [0..1] Child node with a key > the one of this node. */ \
		Tkey rb_min;                                                            \
		Tkey rb_max;                                                            \
	}

#define LLRBTREE_NODE_WITH_KEY(T, Tkey)                                         \
	struct {                                                                    \
		T   *rb_lhs; /* [0..1] Child node with a key < the one of this node. */ \
		T   *rb_rhs; /* [0..1] Child node with a key > the one of this node. */ \
		Tkey rb_min;                                                            \
		Tkey rb_max;                                                            \
	}

#define RBTREE_ROOT(T)   T *
#define LLRBTREE_ROOT(T) T *

#endif /* !__GUARD_HYBRID_SEQUENCE_RBTREE_H */
