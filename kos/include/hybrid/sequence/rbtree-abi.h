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

/* NOTE: This implementation is derived from information found on Wikipedia. */

#include "../../__stdinc.h"
#include "../__assert.h"
#include "../typecore.h"
#include "rbtree.h"

#ifndef RBTREE
#ifdef __INTELLISENSE__
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE(name) _rb_##name
#define RBTREE_T     struct my_node
#define RBTREE_Tkey  __UINTPTR_TYPE__

#define RBTREE_GETNODE(self)   (self)->_node
#define RBTREE_GETMINKEY(self) (self)->_minkey
#define RBTREE_GETMAXKEY(self) (self)->_maxkey
#define RBTREE_ISRED(self)     (self)->_isred
#define RBTREE_SETRED(self)    ((self)->_isred = 1)
#define RBTREE_SETBLACK(self)  ((self)->_isred = 0)

struct my_node {
	int                         _foo;
	RBTREE_NODE(struct my_node) _node;
	int                         _bar;
	RBTREE_Tkey                 _minkey;
	RBTREE_Tkey                 _maxkey;
	__BOOL                      _isred;
};

#endif /* __INTELLISENSE__ */
#endif /* !RBTREE */

#if (!defined(RBTREE_GETPAR) || !defined(RBTREE_GETLHS) || !defined(RBTREE_GETRHS) || \
     !defined(RBTREE_SETPAR) || !defined(RBTREE_SETLHS) || !defined(RBTREE_SETRHS))
#ifndef RBTREE_GETNODE
#ifdef RBTREE_NODEPATH
#define RBTREE_GETNODE(self) (self)->RBTREE_NODEPATH
#endif /* RBTREE_NODEPATH */
#endif /* !RBTREE_GETNODE */
#define RBTREE_GETPAR(self)    RBTREE_GETNODE(self).rb_par
#define RBTREE_GETLHS(self)    RBTREE_GETNODE(self).rb_lhs
#define RBTREE_GETRHS(self)    RBTREE_GETNODE(self).rb_rhs
#define RBTREE_SETPAR(self, v) (void)(RBTREE_GETNODE(self).rb_par = (v))
#define RBTREE_SETLHS(self, v) (void)(RBTREE_GETNODE(self).rb_lhs = (v))
#define RBTREE_SETRHS(self, v) (void)(RBTREE_GETNODE(self).rb_rhs = (v))
#endif /* !... */
/* #define RBTREE_MINKEY_EQ_MAXKEY */

#ifndef RBTREE_GETNODE
#error "Missing macro: `#define RBTREE_GETNODE(self)'"
#endif /* !RBTREE_GETNODE */
#ifndef RBTREE_GETMINKEY
#if defined(RBTREE_GETMAXKEY) && defined(RBTREE_MINKEY_EQ_MAXKEY)
#define RBTREE_GETMINKEY RBTREE_GETMAXKEY
#else /* RBTREE_GETMAXKEY && RBTREE_MINKEY_EQ_MAXKEY */
#error "Missing macro: `#define RBTREE_GETMINKEY(self)'"
#endif /* !RBTREE_GETMAXKEY || !RBTREE_MINKEY_EQ_MAXKEY */
#endif /* !RBTREE_GETMINKEY */
#ifndef RBTREE_GETMAXKEY
#if defined(RBTREE_GETMINKEY) && defined(RBTREE_MINKEY_EQ_MAXKEY)
#define RBTREE_GETMAXKEY RBTREE_GETMINKEY
#else /* RBTREE_GETMINKEY && RBTREE_MINKEY_EQ_MAXKEY */
#error "Missing macro: `#define RBTREE_GETMAXKEY(self)'"
#endif /* !RBTREE_GETMINKEY || !RBTREE_MINKEY_EQ_MAXKEY */
#endif /* !RBTREE_GETMAXKEY */
#ifndef RBTREE_ISRED
#error "Missing macro: `#define RBTREE_ISRED(self)'"
#endif /* !RBTREE_ISRED */
#ifndef RBTREE_SETRED
#error "Missing macro: `#define RBTREE_SETRED(self)'"
#endif /* !RBTREE_SETRED */
#ifndef RBTREE_SETBLACK
#error "Missing macro: `#define RBTREE_SETBLACK(self)'"
#endif /* !RBTREE_SETBLACK */
#ifndef RBTREE_T
#error "Missing macro: `#define RBTREE_T'"
#endif /* !RBTREE_T */
#ifndef RBTREE_Tkey
#error "Missing macro: `#define RBTREE_Tkey'"
#endif /* !RBTREE_Tkey */

#ifndef RBTREE_KEY_LO
#define RBTREE_KEY_LO(a, b) ((a) < (b))
#define RBTREE_KEY_EQ(a, b) ((a) == (b))
#endif /* !RBTREE_KEY_LO */

#ifndef RBTREE_KEY_EQ
#define RBTREE_KEY_EQ(a, b) (!RBTREE_KEY_LO(a, b) && !RBTREE_KEY_LO(b, a))
#endif /* !RBTREE_KEY_EQ */

#undef RBTREE_KEY_GR
#define RBTREE_KEY_GR(a, b) RBTREE_KEY_LO(b, a) /* a > b */

/* if defined, `RBTREE_NULL' can be dereferenced with:
 *    - Its color set to BLACK
 *    - Its parent field point back to itself
 *    - Its lhs/rhs fields point back to itself */
/* #define RBTREE_NULL_IS_IMPLICIT_BLACK */

#ifndef RBTREE_NULL
#undef RBTREE_NULL_IS_IMPLICIT_BLACK
#define RBTREE_NULL __NULLPTR
#endif /* !RBTREE_NULL */
#ifndef RBTREE_DECL
#define RBTREE_DECL __PRIVATE
#endif /* !RBTREE_DECL */
#ifndef RBTREE_IMPL
#define RBTREE_IMPL __PRIVATE
#endif /* !RBTREE_IMPL */
#ifndef RBTREE_CC
#define RBTREE_CC /* nothing */
#endif /* !RBTREE_CC */
#ifndef RBTREE_NOTHROW
#define RBTREE_NOTHROW __NOTHROW_NCX
#endif /* !RBTREE_NOTHROW */
#ifndef RBTREE_ASSERT
#define RBTREE_ASSERT __hybrid_assert
#endif /* !RBATREE_ASSERT */
#ifndef RBTREE_ASSERTF
#define RBTREE_ASSERTF __hybrid_assertf
#endif /* !RBTREE_ASSERTF */
#ifndef RBTREE_ISLHSRED
#ifdef RBTREE_NULL_IS_IMPLICIT_BLACK
#define RBTREE_ISLHSRED(node) RBTREE_ISRED(RBTREE_GETLHS(node))
#else /* RBTREE_NULL_IS_IMPLICIT_BLACK */
#define RBTREE_ISLHSRED(node) (RBTREE_GETLHS(node) != RBTREE_NULL && RBTREE_ISRED(RBTREE_GETLHS(node)))
#endif /* !RBTREE_NULL_IS_IMPLICIT_BLACK */
#endif /* !RBTREE_ISLHSRED */
#ifndef RBTREE_ISRHSRED
#ifdef RBTREE_NULL_IS_IMPLICIT_BLACK
#define RBTREE_ISRHSRED(node) RBTREE_ISRED(RBTREE_GETRHS(node))
#else /* RBTREE_NULL_IS_IMPLICIT_BLACK */
#define RBTREE_ISRHSRED(node) (RBTREE_GETRHS(node) != RBTREE_NULL && RBTREE_ISRED(RBTREE_GETRHS(node)))
#endif /* !RBTREE_NULL_IS_IMPLICIT_BLACK */
#endif /* !RBTREE_ISRHSRED */

__DECL_BEGIN

#ifndef RBTREE_IMPLEMENTATION_ONLY
/* Locate the node for the given key.
 * @return: RBTREE_NULL: No node exists for the given key. */
RBTREE_DECL __ATTR_WUNUSED RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(locate))(/*nullable*/ RBTREE_T *root,
                                         RBTREE_Tkey key);

#ifndef RBTREE_MINKEY_EQ_MAXKEY
/* Locate the first node overlapping with the given range.
 * @return: RBTREE_NULL: No node exists within the given range. */
RBTREE_DECL __ATTR_WUNUSED RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(rlocate))(/*nullable*/ RBTREE_T *root,
                                          RBTREE_Tkey minkey,
                                          RBTREE_Tkey maxkey);
#endif /* !RBTREE_MINKEY_EQ_MAXKEY */

/* Insert the given node into the given tree. The caller must ensure
 * that no already-existing node overlaps with the given `node' */
RBTREE_DECL __ATTR_NONNULL((1, 2)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(insert))(RBTREE_T **__restrict proot,
                                         RBTREE_T *__restrict node);

/* Remove and return the node node for `key'.
 * @return: RBTREE_NULL: No node exists for the given key. */
RBTREE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(remove))(RBTREE_T **__restrict proot,
                                         RBTREE_Tkey key);

#ifndef RBTREE_MINKEY_EQ_MAXKEY
/* Remove and return the node node for `minkey...maxkey'.
 * @return: RBTREE_NULL: No node exists within the given range. */
RBTREE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(rremove))(RBTREE_T **__restrict proot,
                                          RBTREE_Tkey minkey,
                                          RBTREE_Tkey maxkey);
#endif /* !RBTREE_MINKEY_EQ_MAXKEY */

/* Remove the given node from the given tree. */
RBTREE_DECL __ATTR_NONNULL((1, 2)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(removenode))(RBTREE_T **__restrict proot,
                                             RBTREE_T *__restrict node);

#ifdef RBTREE_WANT_PREV_NEXT_NODE
/* Return the next node with a key-range located below `node'
 * If no such node exists, return `RBTREE_NULL' instead. */
RBTREE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(prevnode))(RBTREE_T const *__restrict node);

/* Return the next node with a key-range located above `node'
 * If no such node exists, return `RBTREE_NULL' instead. */
RBTREE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(nextnode))(RBTREE_T const *__restrict node);
#endif /* RBTREE_WANT_PREV_NEXT_NODE */

#endif /* !RBTREE_IMPLEMENTATION_ONLY */

#ifndef RBTREE_HEADER_ONLY
#define _RBTREE_GETPARENT(self)  RBTREE_GETPAR(self)
#define _RBTREE_GETSIBLING(self) (RBTREE(_getsibling)(self))
#ifdef RBTREE_MINKEY_EQ_MAXKEY
#define _RBTREE_OVERLAPPING(a, b) \
	RBTREE_KEY_EQ(RBTREE_GETMINKEY(a), RBTREE_GETMINKEY(b))
#else /* RBTREE_MINKEY_EQ_MAXKEY */
#define _RBTREE_OVERLAPPING(a, b)                               \
	(RBTREE_KEY_LO(RBTREE_GETMINKEY(a), RBTREE_GETMAXKEY(b)) && \
	 RBTREE_KEY_GR(RBTREE_GETMAXKEY(a), RBTREE_GETMINKEY(b)))
#endif /* !RBTREE_MINKEY_EQ_MAXKEY */

#if !defined(RBTREE_NDEBUG) && defined(NDEBUG)
#define RBTREE_NDEBUG
#endif /* !RBTREE_NDEBUG && NDEBUG */

#undef RBTREE_WANT_INTERNAL_ASSERT
#if !defined(RBTREE_NDEBUG) && !defined(RBTREE_ASSERT_IS_NOOP)
#define RBTREE_WANT_INTERNAL_ASSERT
#endif /* !RBTREE_NDEBUG && !RBTREE_ASSERT_IS_NOOP */

#ifdef RBTREE_WANT_INTERNAL_ASSERT
/* @param: cur_black_nodes: The # of black nodes already encountered (excluding self)
 * @param: exp_black_nodes: The # of black nodes expected when NIL is reached.
 *                          For this purpose, the NIL-nodes themself (which are
 *                          technically also black) are also counted. */
__PRIVATE __ATTR_NONNULL((1)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(_intern_assert))(RBTREE_T const *__restrict self,
                                                 unsigned int cur_black_nodes,
                                                 unsigned int exp_black_nodes) {
	RBTREE_T const *lhs, *rhs;
	lhs = RBTREE_GETLHS(self);
	rhs = RBTREE_GETRHS(self);
	RBTREE_ASSERT(lhs == RBTREE_NULL || RBTREE_KEY_LO(RBTREE_GETMAXKEY(lhs), RBTREE_GETMINKEY(self)));
	RBTREE_ASSERT(rhs == RBTREE_NULL || RBTREE_KEY_GR(RBTREE_GETMINKEY(rhs), RBTREE_GETMAXKEY(self)));
	RBTREE_ASSERT(lhs == RBTREE_NULL || RBTREE_GETPAR(lhs) == self);
	RBTREE_ASSERT(rhs == RBTREE_NULL || RBTREE_GETPAR(rhs) == self);
	if (RBTREE_ISRED(self)) {
		/* If a node is red, then both its children are black. */
		RBTREE_ASSERT(!RBTREE_ISLHSRED(self));
		RBTREE_ASSERT(!RBTREE_ISRHSRED(self));
	} else {
		++cur_black_nodes;
	}
	RBTREE_ASSERT(cur_black_nodes < exp_black_nodes);
	if (lhs != RBTREE_NULL)
		(RBTREE(_intern_assert)(lhs, cur_black_nodes, exp_black_nodes));
	else {
		RBTREE_ASSERT(cur_black_nodes == exp_black_nodes - 1);
	}
	if (rhs != RBTREE_NULL)
		(RBTREE(_intern_assert)(rhs, cur_black_nodes, exp_black_nodes));
	else {
		RBTREE_ASSERT(cur_black_nodes == exp_black_nodes - 1);
	}
}

#define _RBTREE_VALIDATE(root) (RBTREE(_intern_assert_tree)(root))
__PRIVATE void
RBTREE_NOTHROW(RBTREE_CC RBTREE(_intern_assert_tree))(RBTREE_T const *root) {
	RBTREE_T const *iter;
	unsigned int exp_black_nodes;
	if (!root)
		return;
	RBTREE_ASSERT(!RBTREE_ISRED(root));                /* The root must be black. */
	RBTREE_ASSERT(RBTREE_GETPAR(root) == RBTREE_NULL); /* The root must not have a parent. */
	exp_black_nodes = 2; /* +1: root, +1: trailing NIL */
	iter = RBTREE_GETLHS(root);
	while (iter != RBTREE_NULL) {
		if (!RBTREE_ISRED(iter))
			++exp_black_nodes;
		iter = RBTREE_GETLHS(iter);
	}
	/* Verify the entire tree. */
	(RBTREE(_intern_assert)(root, 0, exp_black_nodes));
}
#else /* RBTREE_WANT_INTERNAL_ASSERT */
#define _RBTREE_VALIDATE(root) (void)0
#endif /* !RBTREE_WANT_INTERNAL_ASSERT */


__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_getsibling))(RBTREE_T *__restrict self) {
	RBTREE_T *parent = _RBTREE_GETPARENT(self);
	RBTREE_T *sibling;
	if (parent == RBTREE_NULL)
		return RBTREE_NULL;
	sibling = RBTREE_GETLHS(parent);
	if (sibling == self)
		sibling = RBTREE_GETRHS(parent);
	else {
		RBTREE_ASSERT(self == RBTREE_GETRHS(parent));
	}
	return sibling;
}


/* Locate the node for the given key.
 * @return: RBTREE_NULL: No node exists for the given key. */
RBTREE_IMPL __ATTR_WUNUSED RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(locate))(/*nullable*/ RBTREE_T *root,
                                         RBTREE_Tkey key) {
	_RBTREE_VALIDATE(root);
	while (root) {
		if (RBTREE_KEY_LO(key, RBTREE_GETMINKEY(root))) {
			root = RBTREE_GETLHS(root);
			continue;
		}
		if (RBTREE_KEY_GR(key, RBTREE_GETMAXKEY(root))) {
			root = RBTREE_GETRHS(root);
			continue;
		}
		break;
	}
	return root;
}

#ifndef RBTREE_MINKEY_EQ_MAXKEY
/* Locate the first node overlapping with the given range.
 * @return: RBTREE_NULL: No node exists within the given range. */
RBTREE_IMPL __ATTR_WUNUSED RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(rlocate))(/*nullable*/ RBTREE_T *root,
                                          RBTREE_Tkey minkey,
                                          RBTREE_Tkey maxkey) {
	_RBTREE_VALIDATE(root);
	while (root) {
		if (RBTREE_KEY_LO(maxkey, RBTREE_GETMINKEY(root))) {
			root = RBTREE_GETLHS(root);
			continue;
		}
		if (RBTREE_KEY_GR(minkey, RBTREE_GETMAXKEY(root))) {
			root = RBTREE_GETRHS(root);
			continue;
		}
		break;
	}
	return root;
}
#endif /* !RBTREE_MINKEY_EQ_MAXKEY */


/* Have `self' swap positions with its max-child. */
__LOCAL __ATTR_NONNULL((1)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(_rotl))(RBTREE_T *__restrict self) {
	RBTREE_T *rhs, *parent, *newrhs;
	rhs = RBTREE_GETRHS(self);
	RBTREE_ASSERT(rhs != RBTREE_NULL);
	parent = _RBTREE_GETPARENT(self);
	newrhs = RBTREE_GETLHS(rhs);
	RBTREE_SETRHS(self, newrhs);
	RBTREE_SETLHS(rhs, self);
	RBTREE_SETPAR(self, rhs);
	if (newrhs != RBTREE_NULL)
		RBTREE_SETPAR(newrhs, self);
	if (parent != RBTREE_NULL) {
		if (self == RBTREE_GETLHS(parent)) {
			RBTREE_SETLHS(parent, rhs);
		} else {
			RBTREE_ASSERT(self == RBTREE_GETRHS(parent));
			RBTREE_SETRHS(parent, rhs);
		}
	}
	RBTREE_SETPAR(rhs, parent);
}

/* Have `self' swap positions with its min-child. */
__LOCAL __ATTR_NONNULL((1)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(_rotr))(RBTREE_T *__restrict self) {
	RBTREE_T *lhs, *parent, *newlhs;
	lhs = RBTREE_GETLHS(self);
	RBTREE_ASSERT(lhs != RBTREE_NULL);
	parent = _RBTREE_GETPARENT(self);
	newlhs = RBTREE_GETRHS(lhs);
	RBTREE_SETLHS(self, newlhs);
	RBTREE_SETRHS(lhs, self);
	RBTREE_SETPAR(self, lhs);
	if (newlhs != RBTREE_NULL)
		RBTREE_SETPAR(newlhs, self);
	if (parent != RBTREE_NULL) {
		if (self == RBTREE_GETLHS(parent)) {
			RBTREE_SETLHS(parent, lhs);
		} else {
			RBTREE_ASSERT(self == RBTREE_GETRHS(parent));
			RBTREE_SETRHS(parent, lhs);
		}
	}
	RBTREE_SETPAR(lhs, parent);
}


/* @return: * : The newly set parent-node of `node' */
__LOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_insert_worker))(RBTREE_T *__restrict root,
                                                 RBTREE_T *__restrict node) {
again:
	RBTREE_ASSERT(!_RBTREE_OVERLAPPING(root, node));
	if (RBTREE_KEY_LO(RBTREE_GETMAXKEY(node), RBTREE_GETMINKEY(root))) {
		RBTREE_T *nextnode;
		nextnode = RBTREE_GETLHS(root);
		if (nextnode != RBTREE_NULL) {
			root = nextnode;
			goto again;
		}
		RBTREE_SETLHS(root, node);
	} else {
		RBTREE_T *nextnode;
		nextnode = RBTREE_GETRHS(root);
		if (nextnode != RBTREE_NULL) {
			root = nextnode;
			goto again;
		}
		RBTREE_SETRHS(root, node);
	}
	RBTREE_SETPAR(node, root);
	RBTREE_SETLHS(node, RBTREE_NULL);
	RBTREE_SETRHS(node, RBTREE_NULL);
	RBTREE_SETRED(node);
	return root;
}


/* Insert the given node into the given tree. The caller must ensure
 * that no already-existing node overlaps with the given `node' */
RBTREE_IMPL __ATTR_NONNULL((1, 2)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(insert))(RBTREE_T **__restrict proot,
                                         RBTREE_T *__restrict node) {
	RBTREE_T *root = *proot;
	RBTREE_T *parent;
	_RBTREE_VALIDATE(root);
	if __unlikely(!root) {
		/* Special case: First node. (Insert-case: #1) */
		*proot = node;
		RBTREE_SETPAR(node, RBTREE_NULL);
		RBTREE_SETLHS(node, RBTREE_NULL);
		RBTREE_SETRHS(node, RBTREE_NULL);
set_node_black_and_return:
		RBTREE_SETBLACK(node); /* The root node is black. */
		_RBTREE_VALIDATE(*proot);
		return;
	}
	parent = (RBTREE(_insert_worker)(root, node));
again_repair_node_impl:
	RBTREE_ASSERT(RBTREE_ISRED(node));
	RBTREE_ASSERT(parent != RBTREE_NULL);
	RBTREE_ASSERT(parent == _RBTREE_GETPARENT(node));
	if (!RBTREE_ISRED(parent)) { /* ISBLACK */
		/* Insert-case: #2 */
	} else {
		RBTREE_T *uncle;
		/* uncle = _RBTREE_GETUNCLE(node); */
		uncle = _RBTREE_GETSIBLING(parent);
		if (uncle != RBTREE_NULL && RBTREE_ISRED(uncle)) {
			/* Insert-case: #3
			 *             grandparent:BLACK
			 *                 /    \
			 *         parent:RED  uncle:RED
			 *           /
			 *       node:RED
			 *
			 * Change this to:
			 *             grandparent:RED
			 *                 /    \
			 *       parent:BLACK  uncle:BLACK
			 *           /
			 *       node:RED
			 *
			 * ... and fix-up the parent of `grandparent', which now
			 *     takes the place of `node', of the potentially
			 *     out-of-place RED node having to be fixed.
			 */
			RBTREE_SETBLACK(parent);
			RBTREE_SETBLACK(uncle);
			/* node = _RBTREE_GETGRANDPARENT(node); */
			node = _RBTREE_GETPARENT(parent);
			RBTREE_ASSERTF(node != RBTREE_NULL,
			               "We've got an uncle, so we should "
			               "also have a grandparent");
			RBTREE_SETRED(node);
/*again_repair_node:*/
			parent = _RBTREE_GETPARENT(node);
			if (parent == RBTREE_NULL)
				goto set_node_black_and_return;
			goto again_repair_node_impl;
		} else {
			/* Insert-case: #4 */
			RBTREE_T *grandparent;
			grandparent = _RBTREE_GETPARENT(parent);
			RBTREE_ASSERT(grandparent != RBTREE_NULL);
			if (node == RBTREE_GETRHS(parent)) {
				if (parent == RBTREE_GETLHS(grandparent)) {
					(RBTREE(_rotl)(parent));
					parent      = node;
					node        = RBTREE_GETLHS(node);
					grandparent = _RBTREE_GETPARENT(parent);
				}
			} else {
				RBTREE_ASSERT(node == RBTREE_GETLHS(parent));
				if (parent == RBTREE_GETRHS(grandparent)) {
					(RBTREE(_rotr)(parent));
					parent      = node;
					node        = RBTREE_GETRHS(node);
					grandparent = _RBTREE_GETPARENT(parent);
				}
			}
			if (node == RBTREE_GETLHS(parent)) {
				(RBTREE(_rotr)(grandparent));
			} else {
				RBTREE_ASSERT(node == RBTREE_GETRHS(parent));
				(RBTREE(_rotl)(grandparent));
			}
			RBTREE_SETBLACK(parent);
			RBTREE_SETRED(grandparent);

			/* Update the root node in case it got changed by the rotations above. */
			if (RBTREE_GETPAR(root)) {
				do {
					root = RBTREE_GETPAR(root);
				} while (RBTREE_GETPAR(root));
				*proot = root;
			}
		}
	}
	_RBTREE_VALIDATE(*proot);
}


__LOCAL __ATTR_NONNULL((1, 2, 3)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(_replace))(RBTREE_T **__restrict proot,
                                           RBTREE_T const *__restrict node,
                                           RBTREE_T *__restrict repl) {
	RBTREE_T *temp;
	RBTREE_SETBLACK(repl);
	if (RBTREE_ISRED(node))
		RBTREE_SETRED(repl);
	temp = RBTREE_GETPAR(node);
	RBTREE_SETPAR(repl, temp);
	if (temp != RBTREE_NULL) {
		RBTREE_ASSERT(*proot != node);
		if (RBTREE_GETLHS(temp) == node) {
			RBTREE_SETLHS(temp, repl);
		} else {
			RBTREE_ASSERT(RBTREE_GETRHS(temp) == node);
			RBTREE_SETRHS(temp, repl);
		}
	} else {
		RBTREE_ASSERT(*proot == node);
		*proot = repl;
	}
	temp = RBTREE_GETLHS(node);
	RBTREE_SETLHS(repl, temp);
	if (temp != RBTREE_NULL) {
		RBTREE_ASSERT(RBTREE_GETPAR(temp) == node);
		RBTREE_SETPAR(temp, repl);
	}
	temp = RBTREE_GETRHS(node);
	RBTREE_SETRHS(repl, temp);
	if (temp != RBTREE_NULL) {
		RBTREE_ASSERT(RBTREE_GETPAR(temp) == node);
		RBTREE_SETPAR(temp, repl);
	}
}

/* Remove the given node from the given tree. */
RBTREE_IMPL __ATTR_NONNULL((1, 2)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(removenode))(RBTREE_T **__restrict proot,
                                             RBTREE_T *__restrict node) {
	RBTREE_T *lhs, *rhs, *parent;
	RBTREE_T const *fixnode;
	_RBTREE_VALIDATE(*proot);
	RBTREE_ASSERT(*proot);
	RBTREE_ASSERT(node);
	lhs = RBTREE_GETLHS(node);
	rhs = RBTREE_GETRHS(node);
	RBTREE_ASSERT((RBTREE_GETPAR(node) == RBTREE_NULL) == (*proot == node));
	/* Find the node with which to replace the given `node'.
	 * This this purpose, when our node what 2 non-NULL children,
	 * then we must replace `node' with either the MAX-node from
	 * `lhs', or the MIN-node from `rhs' */
	if (lhs != RBTREE_NULL && rhs != RBTREE_NULL) {
		RBTREE_T *replacement;
#if 1
		replacement = lhs;
		while (RBTREE_GETRHS(replacement) != RBTREE_NULL)
			replacement = RBTREE_GETRHS(replacement);
#else
		replacement = rhs;
		while (RBTREE_GETLHS(replacement) != RBTREE_NULL)
			replacement = RBTREE_GETLHS(replacement);
#endif
		/* At this point we know that `node_to_remove' has <= 2
		 * child nodes, so when we call ourselves recursively,
		 * we know that we won't get here again. */
		(RBTREE(removenode)(proot, replacement));

		/* Replicate the original configuration of `node' in `node_to_remove' */
		(RBTREE(_replace)(proot, node, replacement));
		_RBTREE_VALIDATE(*proot);
		goto done;
	}
	RBTREE_ASSERT(lhs == RBTREE_NULL || rhs == RBTREE_NULL);
	/* Special case: both the children of `node' are NULL */
	if (lhs == RBTREE_NULL && rhs == RBTREE_NULL) {
		parent = RBTREE_GETPAR(node);
		if (parent == RBTREE_NULL) {
			*proot = RBTREE_NULL;
		} else {
			if (!RBTREE_ISRED(node)) {
				/* Special case: Removing a black leaf-node. */
				fixnode = node;
				goto do_delete_black_leaf_node;
			}
			/* Can just blindly remove this node! */
			if (RBTREE_GETLHS(parent) == node) {
				RBTREE_SETLHS(parent, RBTREE_NULL);
			} else {
				RBTREE_ASSERT(RBTREE_GETRHS(parent) == node);
				RBTREE_SETRHS(parent, RBTREE_NULL);
			}
		}
		_RBTREE_VALIDATE(*proot);
		goto done;
	}
	if (lhs == RBTREE_NULL)
		lhs = rhs;
	/* Replace `node' with `lhs' */
	parent = RBTREE_GETPAR(node);
	RBTREE_SETPAR(lhs, parent);
	if (parent == RBTREE_NULL) {
		/* Special case: Remove the root node. */
		*proot = lhs;
		RBTREE_SETBLACK(lhs);
		_RBTREE_VALIDATE(*proot);
		goto done;
	}
	if (node == RBTREE_GETLHS(parent)) {
		RBTREE_SETLHS(parent, lhs);
	} else {
		RBTREE_ASSERT(node == RBTREE_GETRHS(parent));
		RBTREE_SETRHS(parent, lhs);
	}
	if (!RBTREE_ISRED(node)) {
		if (RBTREE_ISRED(lhs)) {
			RBTREE_SETBLACK(lhs);
		} else {
			fixnode = lhs;
do_delete_black_leaf_node:
			parent = RBTREE_GETPAR(fixnode);
			if (parent != RBTREE_NULL) {
				RBTREE_T *sibling;
				__BOOL sibling_and_children_are_black;
				sibling = RBTREE_GETLHS(parent);
				if (sibling == fixnode)
					sibling = RBTREE_GETRHS(parent);
				RBTREE_ASSERT(sibling != fixnode);
				RBTREE_ASSERT(sibling != RBTREE_NULL);
				if (RBTREE_ISRED(sibling)) {
					RBTREE_SETRED(parent);
					RBTREE_SETBLACK(sibling);
					if (fixnode == RBTREE_GETLHS(parent)) {
						(RBTREE(_rotl)(parent));
					} else {
						(RBTREE(_rotr)(parent));
					}
					/* Update the root node in case it got changed by the rotations above. */
					while (RBTREE_GETPAR(*proot))
						*proot = RBTREE_GETPAR(*proot);
					parent  = RBTREE_GETPAR(fixnode);
					sibling = RBTREE_GETLHS(parent);
					if (sibling == fixnode)
						sibling = RBTREE_GETRHS(parent);
					RBTREE_ASSERT(sibling != fixnode);
					RBTREE_ASSERT(sibling != RBTREE_NULL);
				}
				sibling_and_children_are_black = !RBTREE_ISRED(sibling) &&
				                                 !RBTREE_ISLHSRED(sibling) &&
				                                 !RBTREE_ISRHSRED(sibling);
				if (!RBTREE_ISRED(parent) && sibling_and_children_are_black) {
					RBTREE_SETRED(sibling);
					fixnode = parent;
					goto do_delete_black_leaf_node;
				}
				if (RBTREE_ISRED(parent) && sibling_and_children_are_black) {
					RBTREE_SETRED(sibling);
					RBTREE_SETBLACK(parent);
				} else {
					if (!RBTREE_ISRED(sibling)) {
						if (fixnode == RBTREE_GETLHS(parent)) {
							if (!RBTREE_ISRHSRED(sibling) && RBTREE_ISLHSRED(sibling)) {
								RBTREE_SETRED(sibling);
								RBTREE_SETBLACK(RBTREE_GETLHS(sibling));
								(RBTREE(_rotr)(sibling));
							}
						} else {
							RBTREE_ASSERT(fixnode == RBTREE_GETRHS(parent));
							if (!RBTREE_ISLHSRED(sibling) && RBTREE_ISRHSRED(sibling)) {
								RBTREE_SETRED(sibling);
								RBTREE_SETBLACK(RBTREE_GETRHS(sibling));
								(RBTREE(_rotl)(sibling));
							}
						}
						parent  = RBTREE_GETPAR(fixnode);
						sibling = RBTREE_GETLHS(parent);
						if (sibling == fixnode)
							sibling = RBTREE_GETRHS(parent);
						RBTREE_ASSERT(sibling != fixnode);
						RBTREE_ASSERT(sibling != RBTREE_NULL);
					}
					RBTREE_SETBLACK(sibling);
					if (RBTREE_ISRED(parent))
						RBTREE_SETRED(sibling);
					RBTREE_SETBLACK(parent);
					if (fixnode == RBTREE_GETLHS(parent)) {
						RBTREE_T *temp;
						temp = RBTREE_GETRHS(sibling);
						if (temp != RBTREE_NULL)
							RBTREE_SETBLACK(temp);
						(RBTREE(_rotl)(parent));
					} else {
						RBTREE_T *temp;
						RBTREE_ASSERT(fixnode == RBTREE_GETRHS(parent));
						temp = RBTREE_GETLHS(sibling);
						if (temp != RBTREE_NULL)
							RBTREE_SETBLACK(temp);
						(RBTREE(_rotr)(parent));
					}
					/* Update the root-pointer due to all of the rotations above. */
					while (RBTREE_GETPAR(*proot))
						*proot = RBTREE_GETPAR(*proot);
				}
			}
			if (lhs == RBTREE_NULL && rhs == RBTREE_NULL) {
				/* Remove `node' from its parent. */
				parent = RBTREE_GETPAR(node);
				if (RBTREE_GETLHS(parent) == node) {
					RBTREE_SETLHS(parent, RBTREE_NULL);
				} else {
					RBTREE_ASSERT(RBTREE_GETRHS(parent) == node);
					RBTREE_SETRHS(parent, RBTREE_NULL);
				}
			}
		}
	}
	_RBTREE_VALIDATE(*proot);
done:;
#ifndef RBTREE_NDEBUG
#if __SIZEOF_POINTER__ == 4
	RBTREE_SETPAR(node, (RBTREE_T *)__UINT32_C(0xcccccccc));
	RBTREE_SETLHS(node, (RBTREE_T *)__UINT32_C(0xcccccccc));
	RBTREE_SETRHS(node, (RBTREE_T *)__UINT32_C(0xcccccccc));
#elif __SIZEOF_POINTER__ == 8
	RBTREE_SETPAR(node, (RBTREE_T *)__UINT64_C(0xcccccccccccccccc));
	RBTREE_SETLHS(node, (RBTREE_T *)__UINT64_C(0xcccccccccccccccc));
	RBTREE_SETRHS(node, (RBTREE_T *)__UINT64_C(0xcccccccccccccccc));
#endif /* __SIZEOF_POINTER__ == ... */
#endif /* !RBTREE_NDEBUG */
}

/* Remove and return the node node for `key'.
 * @return: RBTREE_NULL: No node exists for the given key. */
RBTREE_IMPL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(remove))(RBTREE_T **__restrict proot,
                                         RBTREE_Tkey key) {
	RBTREE_T *node;
	node = RBTREE(locate)(*proot, key);
	if (node)
		(RBTREE(removenode)(proot, node));
	return node;
}

#ifndef RBTREE_MINKEY_EQ_MAXKEY
/* Remove and return the node node for `minkey...maxkey'.
 * @return: RBTREE_NULL: No node exists within the given range. */
RBTREE_IMPL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(rremove))(RBTREE_T **__restrict proot,
                                          RBTREE_Tkey minkey,
                                          RBTREE_Tkey maxkey) {
	RBTREE_T *node;
	node = RBTREE(rlocate)(*proot, minkey, maxkey);
	if (node)
		(RBTREE(removenode)(proot, node));
	return node;
}
#endif /* !RBTREE_MINKEY_EQ_MAXKEY */

#ifdef RBTREE_WANT_PREV_NEXT_NODE
/* Return the next node with a key-range located below `node'
 * If no such node exists, return `RBTREE_NULL' instead. */
RBTREE_IMPL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(prevnode))(RBTREE_T const *__restrict node) {
	RBTREE_T *result;
	result = RBTREE_GETLHS(node);
	if (result == RBTREE_NULL) {
		/* Keep going up until we reach the ROOT (NULL),
		 * or reach a parent via its RHS-child-branch. */
		for (;;) {
			result = RBTREE_GETPAR(node);
			if (result == RBTREE_NULL)
				break;
			if (RBTREE_GETRHS(result) == node)
				break;
			node = result;
		}
	} else {
		/* Go down the right of `result' */
		while (RBTREE_GETRHS(result) != RBTREE_NULL)
			result = RBTREE_GETRHS(result);
	}
	return result;
}

/* Return the next node with a key-range located above `node'
 * If no such node exists, return `RBTREE_NULL' instead. */
RBTREE_IMPL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(nextnode))(RBTREE_T const *__restrict node) {
	RBTREE_T *result;
	result = RBTREE_GETRHS(node);
	if (result == RBTREE_NULL) {
		/* Keep going up until we reach the ROOT (NULL),
		 * or reach a parent via its LHS-child-branch. */
		for (;;) {
			result = RBTREE_GETPAR(node);
			if (result == RBTREE_NULL)
				break;
			if (RBTREE_GETLHS(result) == node)
				break;
			node = result;
		}
	} else {
		/* Go down the left of `result' */
		while (RBTREE_GETLHS(result) != RBTREE_NULL)
			result = RBTREE_GETLHS(result);
	}
	return result;
}
#endif /* RBTREE_WANT_PREV_NEXT_NODE */


#undef RBTREE_NDEBUG
#undef RBTREE_WANT_INTERNAL_ASSERT
#undef _RBTREE_OVERLAPPING
#undef _RBTREE_VALIDATE
#undef _RBTREE_GETPARENT
#undef _RBTREE_GETSIBLING
#endif /* !RBTREE_HEADER_ONLY */

__DECL_END

#undef RBTREE_IMPLEMENTATION_ONLY
#undef RBTREE_HEADER_ONLY

#undef RBTREE_NULL
#undef RBTREE_NULL_IS_IMPLICIT_BLACK
#undef RBTREE_DECL
#undef RBTREE_IMPL
#undef RBTREE_CC
#undef RBTREE_NOTHROW
#undef RBTREE_ASSERT
#undef RBTREE_ASSERTF

#undef RBTREE_MINKEY_EQ_MAXKEY

#undef RBTREE_KEY_LO
#undef RBTREE_KEY_EQ
#undef RBTREE_KEY_GR

#undef RBTREE_GETPAR
#undef RBTREE_GETLHS
#undef RBTREE_GETRHS
#undef RBTREE_SETPAR
#undef RBTREE_SETLHS
#undef RBTREE_SETRHS
#undef RBTREE_NODEPATH
#undef RBTREE_GETNODE
#undef RBTREE_GETMINKEY
#undef RBTREE_GETMAXKEY
#undef RBTREE_ISRED
#undef RBTREE_SETRED
#undef RBTREE_SETBLACK
#undef RBTREE_T
#undef RBTREE_Tkey

#undef RBTREE_WANT_PREV_NEXT_NODE
