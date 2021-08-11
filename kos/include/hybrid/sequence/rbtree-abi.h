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

/* NOTE: This implementation is derived from information found on Wikipedia:
 *       https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
 * The implementation used when `RBTREE_LEFT_LEANING' is defined is based
 * on   that   same  article,   as   well  as   the   following  sources:
 *  - https://en.wikipedia.org/wiki/Left-leaning_red%E2%80%93black_tree
 *  - https://github.com/sebastiencs/red-black-tree/blob/master/rbtree.c
 */

#include "../../__stdinc.h"
#include "../typecore.h"
#include "rbtree.h"

/*
 * Configure options/macros:
 *
 * >> #define RBTREE_DECL                FUNDEF
 * >> #define RBTREE_IMPL                PUBLIC
 * >> #define RBTREE(name)               myrbtree_api_##name
 * >> #define RBTREE_T                   struct myrbtree_node
 * >> #define RBTREE_Tkey                uintptr_t
 * >> #define RBTREE_CC                  LIBCCALL
 * >> #define RBTREE_NOTHROW             NOTHROW_NCX
 * >> #define RBTREE_KEY_LO(a, b)        ((a) < (b))    // Compare keys
 * >> #define RBTREE_KEY_EQ(a, b)        ((a) == (b))   // Compare keys
 * >> #define RBTREE_NULL                NULL           // Null-branch
 * >> #define RBTREE_NODEPATH            rb_node
 * >> #define RBTREE_ISRED(self)         ((self)->color == RED)
 * >> #define RBTREE_XISRED(self)        ((self) != NULL && (self)->color == RED)
 * >> #define RBTREE_SETRED(self)        (void)((self)->color = RED)
 * >> #define RBTREE_SETBLACK(self)      (void)((self)->color = BLACK)
 * >> #define RBTREE_FLIPCOLOR(self)     (void)((self)->color = (self)->color == RED ? BLACK : RED)
 * >> #define RBTREE_COPYCOLOR(dst, src) (void)((dst)->color = (src)->color)
 * >> #define RBTREE_GETNODE(self)       (self)->rb_node
 * >> #define RBTREE_GETKEY(node)        (node)->rb_key    // Implies `RBTREE_MINKEY_EQ_MAXKEY'
 * >> #define RBTREE_GETMINKEY(node)     (node)->rb_minkey
 * >> #define RBTREE_GETMAXKEY(node)     (node)->rb_maxkey
 * >> #define RBTREE_GETLHS(self)        (self)->rb_node.rb_lhs
 * >> #define RBTREE_GETRHS(self)        (self)->rb_node.rb_rhs
 * >> #define RBTREE_SETLHS(self, v)     (void)((self)->rb_node.rb_lhs = (v))
 * >> #define RBTREE_SETRHS(self, v)     (void)((self)->rb_node.rb_rhs = (v))
 * >> #ifndef RBTREE_LEFT_LEANING
 * >> #define RBTREE_GETPAR(self)        (self)->rb_node.rb_par
 * >> #define RBTREE_SETPAR(self, v)     (void)((self)->rb_node.rb_par = (v))
 * >> #endif // !RBTREE_LEFT_LEANING
 * >> #define RBTREE_ASSERT(expr)        assert(expr)
 * >> #define RBTREE_ASSERTF(expr, ...)  assertf(expr, __VA_ARGS__)
 *
 * Features:
 * >> #define RBTREE_MINKEY_EQ_MAXKEY         // Indicate that nodes don't take up key-ranges, but only a single key
 * >> #define RBTREE_WANT_MINMAXLOCATE        // Declare `RBTREE(minmaxlocate)'
 * >> #define RBTREE_WANT_PREV_NEXT_NODE      // Declare `RBTREE(prevnode)' and `RBTREE(nextnode)'
 * >> #define RBTREE_WANT_RREMOVE             // Declare `RBTREE(rremove)'
 * >> #define RBTREE_WANT_RLOCATE             // Declare `RBTREE(rlocate)'
 * >> #define RBTREE_WANT_TRYINSERT           // Declare `RBTREE(tryinsert)'
 * >> #define RBTREE_OMIT_REMOVE              // Omit    `RBTREE(remove)'
 * >> #define RBTREE_OMIT_REMOVENODE          // Omit    `RBTREE(removenode)'
 * >> #define RBTREE_OMIT_INSERT              // Omit    `RBTREE(insert)'
 * >> #define RBTREE_DEBUG                    // Enable internal debug assertions and verification
 * >> #define RBTREE_NDEBUG                   // Disable internal debug assertions and verification
 * >> #define RBTREE_LEFT_LEANING             // Define ABI for a left-leaning tree, which doesn't require a parent
 *                                            // pointer, but has a slightly slower, but still O(log(N)) worst-case
 *                                            // insert/remove time
 * >> #define RBTREE_NULL_IS_IMPLICIT_BLACK   // if defined, `RBTREE_NULL' can be dereferenced with:
 *                                            //  - Its color set to BLACK
 *                                            //  - Its parent field point back to itself
 *                                            //  - Its lhs/rhs fields point back to itself
 * >> #define RBTREE_ASSERT_IS_NOOP           // RBTREE_ASSERT is a no-op
 *
 * Exposure options:
 * >> #define RBTREE_IMPLEMENTATION_ONLY      // Don't include header declarations
 * >> #define RBTREE_HEADER_ONLY              // Don't include source implementations
 *
 */


#ifdef __INTELLISENSE__
#ifndef RBTREE
#define RBTREE_WANT_MINMAXLOCATE
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
	int                  _foo;
	RBTREE_NODE(my_node) _node;
	int                  _bar;
	RBTREE_Tkey          _minkey;
	RBTREE_Tkey          _maxkey;
	__BOOL               _isred;
};

#endif /* !RBTREE */
#endif /* __INTELLISENSE__ */

#ifndef RBTREE_T
#error "Missing macro: `#define RBTREE_T'"
#endif /* !RBTREE_T */
#ifndef RBTREE_Tkey
#error "Missing macro: `#define RBTREE_Tkey'"
#endif /* !RBTREE_Tkey */

#ifndef RBTREE_CC
#define RBTREE_CC /* nothing */
#endif /* !RBTREE_CC */

#ifndef RBTREE_NOTHROW
#define RBTREE_NOTHROW __NOTHROW_NCX
#endif /* !RBTREE_NOTHROW */

#if defined(RBTREE_GETKEY) && !defined(RBTREE_GETMINKEY) && !defined(RBTREE_GETMAXKEY)
#undef RBTREE_MINKEY_EQ_MAXKEY
#define RBTREE_MINKEY_EQ_MAXKEY
#define RBTREE_GETMINKEY RBTREE_GETKEY
#define RBTREE_GETMAXKEY RBTREE_GETKEY
#endif /* RBTREE_GETKEY && !RBTREE_GETMINKEY && !RBTREE_GETMAXKEY */

/* Prevent illegal combinations */
#if defined(RBTREE_WANT_PREV_NEXT_NODE) && defined(RBTREE_LEFT_LEANING)
#error "`RBTREE_WANT_PREV_NEXT_NODE' cannot be used with \
        `RBTREE_LEFT_LEANING', due to the missing parent-pointer"
#endif /* RBTREE_WANT_PREV_NEXT_NODE && RBTREE_LEFT_LEANING */



/* ===== Optional features ===== */
/* #define RBTREE_MINKEY_EQ_MAXKEY        (Indicate that nodes don't take up key-ranges, but only a single key) */
/* #define RBTREE_WANT_MINMAXLOCATE       (Declare `RBTREE(minmaxlocate)') */
/* #define RBTREE_WANT_PREV_NEXT_NODE     (Declare `RBTREE(prevnode)' and `RBTREE(nextnode)') */
/* #define RBTREE_WANT_RREMOVE            (Declare `RBTREE(rremove)') */
/* #define RBTREE_WANT_RLOCATE            (Declare `RBTREE(rlocate)') */
/* #define RBTREE_WANT_TRYINSERT          (Declare `RBTREE(tryinsert)') */
/* #define RBTREE_OMIT_REMOVE             (Omit    `RBTREE(remove)') */
/* #define RBTREE_OMIT_REMOVENODE         (Omit    `RBTREE(removenode)') */
/* #define RBTREE_OMIT_INSERT             (Omit    `RBTREE(insert)') */
/* #define RBTREE_DEBUG                   (Enable internal debug assertions and verification) */
/* #define RBTREE_NDEBUG                  (Disable internal debug assertions and verification) */
/* #define RBTREE_LEFT_LEANING            (Define ABI for a left-leaning tree, which doesn't require a parent
 *                                         pointer, but has a slightly slower, but still O(log(N)) worst-case
 *                                         insert/remove time) */



/* 0================================================================0 */
/* 0                             HEADER                             0 */
/* 0================================================================0 */
#ifndef RBTREE_IMPLEMENTATION_ONLY
__DECL_BEGIN

#ifndef RBTREE_DECL
#define RBTREE_DECL __PRIVATE
#endif /* !RBTREE_DECL */

/* Locate the node for the given key.
 * @return: RBTREE_NULL: No node exists for the given key. */
RBTREE_DECL __ATTR_PURE __ATTR_WUNUSED RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(locate))(/*nullable*/ RBTREE_T *root,
                                         RBTREE_Tkey key);

#ifdef RBTREE_WANT_RLOCATE
/* Locate the first node overlapping with the given range.
 * @return: RBTREE_NULL: No node exists within the given range. */
RBTREE_DECL __ATTR_PURE __ATTR_WUNUSED RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(rlocate))(/*nullable*/ RBTREE_T *root,
                                          RBTREE_Tkey minkey,
                                          RBTREE_Tkey maxkey);
#endif /* RBTREE_WANT_RLOCATE */

#ifndef RBTREE_OMIT_INSERT
/* Insert the given node into the given tree. The caller must ensure
 * that no  already-existing node  overlaps  with the  given  `node' */
RBTREE_DECL __ATTR_NONNULL((1, 2)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(insert))(RBTREE_T **__restrict proot,
                                         RBTREE_T *__restrict node);
#endif /* !RBTREE_OMIT_INSERT */

#ifdef RBTREE_WANT_TRYINSERT
/* Same as `RBTREE(insert)', but gracefully fail (by returning `false')
 * when  some other node already exists that is overlapping with `node' */
RBTREE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL
RBTREE_NOTHROW(RBTREE_CC RBTREE(tryinsert))(RBTREE_T **__restrict proot,
                                            RBTREE_T *__restrict node);
#endif /* RBTREE_WANT_TRYINSERT */

#ifndef RBTREE_OMIT_REMOVE
/* Remove and return the node node for `key'.
 * @return: RBTREE_NULL: No node exists for the given key. */
RBTREE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(remove))(RBTREE_T **__restrict proot,
                                         RBTREE_Tkey key);
#endif /* !RBTREE_OMIT_REMOVE */

#ifdef RBTREE_WANT_RREMOVE
/* Remove and return the node node for `minkey...maxkey'.
 * @return: RBTREE_NULL: No node exists within the given range. */
RBTREE_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(rremove))(RBTREE_T **__restrict proot,
                                          RBTREE_Tkey minkey,
                                          RBTREE_Tkey maxkey);
#endif /* RBTREE_WANT_RREMOVE */

#ifndef RBTREE_OMIT_REMOVENODE
/* Remove the given node from the given tree. */
RBTREE_DECL __ATTR_NONNULL((1, 2)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(removenode))(RBTREE_T **__restrict proot,
                                             RBTREE_T *__restrict node);
#endif /* !RBTREE_OMIT_REMOVENODE */


#ifdef RBTREE_WANT_PREV_NEXT_NODE
/* Return the next node with a key-range located below `node'
 * If  no  such  node exists,  return  `RBTREE_NULL' instead.
 * NOTE: This function takes O(log(N)) to execute. */
RBTREE_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(prevnode))(RBTREE_T const *__restrict node);

/* Return the next node with a key-range located above `node'
 * If  no  such  node exists,  return  `RBTREE_NULL' instead.
 * NOTE: This function takes O(log(N)) to execute. */
RBTREE_DECL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(nextnode))(RBTREE_T const *__restrict node);
#endif /* RBTREE_WANT_PREV_NEXT_NODE */


#ifdef RBTREE_WANT_MINMAXLOCATE
#ifndef RBTREE_MINMAX_T_DEFINED
typedef struct {
	RBTREE_T *mm_min; /* [0..1] Lowest branch. */
	RBTREE_T *mm_max; /* [0..1] Greatest branch. */
} RBTREE(minmax_t);
#else /* !RBTREE_MINMAX_T_DEFINED */
#undef RBTREE_MINMAX_T_DEFINED
#endif /* RBTREE_MINMAX_T_DEFINED */

/* Find the lowest and greatest nodes that are overlapping with the given key-range. */
RBTREE_DECL __ATTR_NONNULL((4)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(minmaxlocate))(RBTREE_T *root, RBTREE_Tkey minkey, RBTREE_Tkey maxkey,
                                               RBTREE(minmax_t) *__restrict result);
#endif /* RBTREE_WANT_MINMAXLOCATE */

__DECL_END
#endif /* !RBTREE_IMPLEMENTATION_ONLY */









/* 0================================================================0 */
/* 0                         IMPLEMENTATION                         0 */
/* 0================================================================0 */
#ifndef RBTREE_HEADER_ONLY

#ifndef RBTREE_KEY_LO
#define RBTREE_KEY_LO(a, b) ((a) < (b))
#define RBTREE_KEY_EQ(a, b) ((a) == (b))
#endif /* !RBTREE_KEY_LO */

#ifndef RBTREE_KEY_EQ
#define RBTREE_KEY_EQ(a, b) (!RBTREE_KEY_LO(a, b) && !RBTREE_KEY_LO(b, a))
#endif /* !RBTREE_KEY_EQ */

#undef RBTREE_KEY_NE
#undef RBTREE_KEY_GR
#undef RBTREE_KEY_GE
#undef RBTREE_KEY_LE
#define RBTREE_KEY_NE(a, b) (!RBTREE_KEY_EQ(a, b)) /* a != b  <==>  !(a == b) */
#define RBTREE_KEY_GR(a, b) RBTREE_KEY_LO(b, a)    /* a > b   <==>  b < a */
#define RBTREE_KEY_GE(a, b) (!RBTREE_KEY_LO(a, b)) /* a >= b  <==>  !(a < b) */
#define RBTREE_KEY_LE(a, b) (!RBTREE_KEY_GR(a, b)) /* a <= b  <==>  !(a > b) */

/* if defined, `RBTREE_NULL' can be dereferenced with:
 *    - Its color set to BLACK
 *    - Its parent field point back to itself
 *    - Its lhs/rhs fields point back to itself */
/* #define RBTREE_NULL_IS_IMPLICIT_BLACK */

#ifndef RBTREE_NULL
#undef RBTREE_NULL_IS_IMPLICIT_BLACK
#define RBTREE_NULL __NULLPTR
#endif /* !RBTREE_NULL */

#ifndef RBTREE_IMPL
#define RBTREE_IMPL __PRIVATE
#endif /* !RBTREE_IMPL */

#if (!defined(RBTREE_GETLHS) || !defined(RBTREE_GETRHS) ||         \
     !defined(RBTREE_SETLHS) || !defined(RBTREE_SETRHS) ||         \
     (!defined(RBTREE_LEFT_LEANING) && (!defined(RBTREE_GETPAR) || \
                                        !defined(RBTREE_SETPAR))))
#ifndef RBTREE_GETNODE
#ifdef RBTREE_NODEPATH
#define RBTREE_GETNODE(self) (self)->RBTREE_NODEPATH
#else /* RBTREE_NODEPATH */
#error "Missing macro: `#define RBTREE_GETNODE(self)'"
#endif /* !RBTREE_NODEPATH */
#endif /* !RBTREE_GETNODE */
#ifndef RBTREE_GETLHS
#define RBTREE_GETLHS(self)    RBTREE_GETNODE(self).rb_lhs
#endif /* !RBTREE_GETLHS */
#ifndef RBTREE_GETRHS
#define RBTREE_GETRHS(self)    RBTREE_GETNODE(self).rb_rhs
#endif /* !RBTREE_GETRHS */
#ifndef RBTREE_SETLHS
#define RBTREE_SETLHS(self, v) (void)(RBTREE_GETNODE(self).rb_lhs = (v))
#endif /* !RBTREE_SETLHS */
#ifndef RBTREE_SETRHS
#define RBTREE_SETRHS(self, v) (void)(RBTREE_GETNODE(self).rb_rhs = (v))
#endif /* !RBTREE_SETRHS */
#ifndef RBTREE_LEFT_LEANING
#ifndef RBTREE_GETPAR
#define RBTREE_GETPAR(self)    RBTREE_GETNODE(self).rb_par
#endif /* !RBTREE_GETPAR */
#ifndef RBTREE_SETPAR
#define RBTREE_SETPAR(self, v) (void)(RBTREE_GETNODE(self).rb_par = (v))
#endif /* !RBTREE_SETPAR */
#endif /* !RBTREE_LEFT_LEANING */
#endif /* !... */

#ifndef RBTREE_ISRED
#error "Missing macro: `#define RBTREE_ISRED(self)'"
#endif /* !RBTREE_ISRED */
#ifndef RBTREE_SETRED
#error "Missing macro: `#define RBTREE_SETRED(self)'"
#endif /* !RBTREE_SETRED */
#ifndef RBTREE_SETBLACK
#error "Missing macro: `#define RBTREE_SETBLACK(self)'"
#endif /* !RBTREE_SETBLACK */

#ifndef RBTREE_FLIPCOLOR
#define RBTREE_FLIPCOLOR(self)                  \
	(RBTREE_ISRED(self) ? RBTREE_SETBLACK(self) \
	                    : RBTREE_SETRED(self))
#endif /* !RBTREE_FLIPCOLOR */

#ifndef RBTREE_COPYCOLOR
#define RBTREE_COPYCOLOR(dst, src)                \
	(RBTREE_SETBLACK(dst),                        \
	 RBTREE_ISRED(src) ? (void)RBTREE_SETRED(dst) \
	                   : (void)0)
#endif /* !RBTREE_COPYCOLOR */

#ifndef RBTREE_GETMINKEY
#if defined(RBTREE_GETMAXKEY) && defined(RBTREE_MINKEY_EQ_MAXKEY)
#define RBTREE_GETMINKEY RBTREE_GETMAXKEY
#elif defined(RBTREE_GETNODE) && !defined(RBTREE_MINKEY_EQ_MAXKEY)
#define RBTREE_GETMINKEY(self) RBTREE_GETNODE(self).rb_min
#else /* ... */
#error "Missing macro: `#define RBTREE_GETMINKEY(self)'"
#endif /* !... */
#endif /* !RBTREE_GETMINKEY */
#ifndef RBTREE_GETMAXKEY
#if defined(RBTREE_GETMINKEY) && defined(RBTREE_MINKEY_EQ_MAXKEY)
#define RBTREE_GETMAXKEY RBTREE_GETMINKEY
#elif defined(RBTREE_GETNODE) && !defined(RBTREE_MINKEY_EQ_MAXKEY)
#define RBTREE_GETMAXKEY(self) RBTREE_GETNODE(self).rb_max
#else /* ... */
#error "Missing macro: `#define RBTREE_GETMAXKEY(self)'"
#endif /* !... */
#endif /* !RBTREE_GETMAXKEY */

#ifndef RBTREE_XISRED
#ifdef RBTREE_NULL_IS_IMPLICIT_BLACK
#define RBTREE_XISRED(node) RBTREE_ISRED(node)
#else /* RBTREE_NULL_IS_IMPLICIT_BLACK */
#define RBTREE_XISRED(node) ((node) != RBTREE_NULL && RBTREE_ISRED(node))
#endif /* !RBTREE_NULL_IS_IMPLICIT_BLACK */
#endif /* !RBTREE_XISRED */





#ifdef RBTREE_DEBUG
#undef RBTREE_NDEBUG
#elif !defined(RBTREE_NDEBUG) && defined(NDEBUG)
#define RBTREE_NDEBUG
#elif defined(RBTREE_ASSERT_IS_NOOP)
#define RBTREE_NDEBUG
#elif 1 /* Default RB-tree internal debug checks enabled:
         *   0:  Perform debug checks by default (very slot, and add O(N) to pretty much every operation)
         *   1: Disable internal debug checks by default (operations take their promised lengths of time)
         */
#define RBTREE_NDEBUG
#endif /* !RBTREE_NDEBUG && NDEBUG */


#ifdef RBTREE_NDEBUG
#undef RBTREE_ASSERT
#undef RBTREE_ASSERTF
#define RBTREE_ASSERT(expr)       (void)0
#define RBTREE_ASSERTF(expr, ...) (void)0
#endif /* RBTREE_NDEBUG */

#ifndef RBTREE_ASSERT
#include "../__assert.h"
#define RBTREE_ASSERT __hybrid_assert
#endif /* !RBATREE_ASSERT */
#ifndef RBTREE_ASSERTF
#include "../__assert.h"
#define RBTREE_ASSERTF __hybrid_assertf
#endif /* !RBTREE_ASSERTF */


#ifdef RBTREE_MINKEY_EQ_MAXKEY
#define _RBTREE_OVERLAPPING(a, b) \
	RBTREE_KEY_EQ(RBTREE_GETMINKEY(a), RBTREE_GETMINKEY(b))
#else /* RBTREE_MINKEY_EQ_MAXKEY */
#define _RBTREE_OVERLAPPING(a, b)                               \
	(RBTREE_KEY_LO(RBTREE_GETMINKEY(a), RBTREE_GETMAXKEY(b)) && \
	 RBTREE_KEY_GR(RBTREE_GETMAXKEY(a), RBTREE_GETMINKEY(b)))
#endif /* !RBTREE_MINKEY_EQ_MAXKEY */

__DECL_BEGIN

#ifndef RBTREE_NDEBUG
/* @param: cur_black_nodes: The # of black nodes already encountered (excluding self)
 * @param: exp_black_nodes: The # of black nodes expected when NIL is  reached.
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
#ifndef RBTREE_LEFT_LEANING
	RBTREE_ASSERT(lhs == RBTREE_NULL || RBTREE_GETPAR(lhs) == self);
	RBTREE_ASSERT(rhs == RBTREE_NULL || RBTREE_GETPAR(rhs) == self);
#endif /* !RBTREE_LEFT_LEANING */
	if (RBTREE_ISRED(self)) {
		/* If a node is red, then both its children are black. */
		RBTREE_ASSERT(!RBTREE_XISRED(RBTREE_GETLHS(self)));
		RBTREE_ASSERT(!RBTREE_XISRED(RBTREE_GETRHS(self)));
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
	RBTREE_ASSERT(!RBTREE_ISRED(root)); /* The root must be black. */
#ifndef RBTREE_LEFT_LEANING
	RBTREE_ASSERT(RBTREE_GETPAR(root) == RBTREE_NULL); /* The root must not have a parent. */
#endif /* !RBTREE_LEFT_LEANING */
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
#else /* !RBTREE_NDEBUG */
#define _RBTREE_VALIDATE(root) (void)0
#endif /* RBTREE_NDEBUG */


#ifndef RBTREE_LEFT_LEANING
#define _RBTREE_GETSIBLING(self) (RBTREE(_getsibling)(self))
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_getsibling))(RBTREE_T *__restrict self) {
	RBTREE_T *parent = RBTREE_GETPAR(self);
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
#endif /* !RBTREE_LEFT_LEANING */


/* Locate the node for the given key.
 * @return: RBTREE_NULL: No node exists for the given key. */
RBTREE_IMPL __ATTR_PURE __ATTR_WUNUSED RBTREE_T *
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

#if defined(RBTREE_WANT_RLOCATE) || defined(RBTREE_WANT_RREMOVE)
/* Locate the first node overlapping with the given range.
 * @return: RBTREE_NULL: No node exists within the given range. */
#ifdef RBTREE_WANT_RLOCATE
RBTREE_IMPL __ATTR_PURE __ATTR_WUNUSED RBTREE_T *
#else /* RBTREE_WANT_RLOCATE */
__PRIVATE __ATTR_PURE __ATTR_WUNUSED RBTREE_T *
#endif /* !RBTREE_WANT_RLOCATE */
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
#endif /* RBTREE_WANT_RLOCATE || RBTREE_WANT_RREMOVE */


#ifdef RBTREE_LEFT_LEANING
/************************************************************************/
/* LEFT-LEANING                                                         */
/************************************************************************/

#if (defined(RBTREE_WANT_TRYINSERT) || !defined(RBTREE_OMIT_INSERT) ||   \
     !defined(RBTREE_OMIT_REMOVENODE) || !defined(RBTREE_OMIT_REMOVE) || \
     defined(RBTREE_WANT_RREMOVE))
__PRIVATE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_rotl))(RBTREE_T *__restrict lhs) {
	RBTREE_T *rhs;
	rhs = RBTREE_GETRHS(lhs);
	RBTREE_ASSERT(lhs != rhs);
	RBTREE_SETRHS(lhs, RBTREE_GETLHS(rhs));
	RBTREE_SETLHS(rhs, lhs);
	RBTREE_COPYCOLOR(rhs, lhs);
	RBTREE_SETRED(lhs);
	return rhs;
}

__PRIVATE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_rotr))(RBTREE_T *__restrict rhs) {
	RBTREE_T *lhs;
	lhs = RBTREE_GETLHS(rhs);
	RBTREE_SETLHS(rhs, RBTREE_GETRHS(lhs));
	RBTREE_SETRHS(lhs, rhs);
	RBTREE_COPYCOLOR(lhs, rhs);
	RBTREE_SETRED(rhs);
	return lhs;
}
#endif /* ... */

#ifndef RBTREE_OMIT_INSERT
__PRIVATE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((2)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_insert_impl))(RBTREE_T *root,
                                               RBTREE_T *__restrict node) {
	RBTREE_T *lhs, *rhs;
	if (root == RBTREE_NULL) {
		RBTREE_SETRED(node);
		RBTREE_SETLHS(node, RBTREE_NULL);
		RBTREE_SETRHS(node, RBTREE_NULL);
		return node;
	}
	RBTREE_ASSERT(!_RBTREE_OVERLAPPING(root, node));
	lhs = RBTREE_GETLHS(root);
	rhs = RBTREE_GETRHS(root);
	if (RBTREE_KEY_LO(RBTREE_GETMAXKEY(node), RBTREE_GETMINKEY(root))) {
		lhs = RBTREE(_insert_impl)(lhs, node);
		RBTREE_SETLHS(root, lhs);
	} else {
		rhs = RBTREE(_insert_impl)(rhs, node);
		RBTREE_SETRHS(root, rhs);
	}
	if (RBTREE_XISRED(rhs) && !RBTREE_XISRED(lhs)) {
		root = RBTREE(_rotl)(root);
		lhs = RBTREE_GETLHS(root);
		rhs = RBTREE_GETRHS(root);
	}
	if (RBTREE_XISRED(lhs) && RBTREE_XISRED(RBTREE_GETLHS(lhs))) {
		root = RBTREE(_rotr)(root);
		lhs = RBTREE_GETLHS(root);
		rhs = RBTREE_GETRHS(root);
	}
	if (RBTREE_XISRED(lhs) && RBTREE_XISRED(rhs)) {
		RBTREE_FLIPCOLOR(root);
		RBTREE_SETBLACK(lhs);
		RBTREE_SETBLACK(rhs);
	}
	return root;
}

/* Insert the given node into the given tree. The caller must ensure
 * that no  already-existing node  overlaps  with the  given  `node' */
RBTREE_IMPL __ATTR_NONNULL((1, 2)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(insert))(RBTREE_T **__restrict proot,
                                         RBTREE_T *__restrict node) {
	RBTREE_T *root;
	_RBTREE_VALIDATE(*proot);
	root = *proot;
	root = RBTREE(_insert_impl)(root, node);
	RBTREE_SETBLACK(root);
	*proot = root;
	_RBTREE_VALIDATE(root);
}
#endif /* !RBTREE_OMIT_INSERT */


#ifdef RBTREE_WANT_TRYINSERT
__PRIVATE __ATTR_WUNUSED __ATTR_NONNULL((2)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_tryinsert_impl))(RBTREE_T *root,
                                                  RBTREE_T *node) {
	RBTREE_T *lhs, *rhs;
	if (root == RBTREE_NULL) {
		RBTREE_SETRED(node);
		RBTREE_SETLHS(node, RBTREE_NULL);
		RBTREE_SETRHS(node, RBTREE_NULL);
		return node;
	}
	if (_RBTREE_OVERLAPPING(root, node))
		return RBTREE_NULL;
	lhs = RBTREE_GETLHS(root);
	rhs = RBTREE_GETRHS(root);
	if (RBTREE_KEY_LO(RBTREE_GETMAXKEY(node), RBTREE_GETMINKEY(root))) {
		lhs = RBTREE(_tryinsert_impl)(lhs, node);
		if (lhs == RBTREE_NULL)
			return RBTREE_NULL;
		RBTREE_SETLHS(root, lhs);
	} else {
		rhs = RBTREE(_tryinsert_impl)(rhs, node);
		if (rhs == RBTREE_NULL)
			return RBTREE_NULL;
		RBTREE_SETRHS(root, rhs);
	}
	if (RBTREE_XISRED(rhs) && !RBTREE_XISRED(lhs)) {
		root = RBTREE(_rotl)(root);
		lhs = RBTREE_GETLHS(root);
		rhs = RBTREE_GETRHS(root);
	}
	if (RBTREE_XISRED(lhs) && RBTREE_XISRED(RBTREE_GETLHS(lhs))) {
		root = RBTREE(_rotr)(root);
		lhs = RBTREE_GETLHS(root);
		rhs = RBTREE_GETRHS(root);
	}
	if (RBTREE_XISRED(lhs) && RBTREE_XISRED(rhs)) {
		RBTREE_FLIPCOLOR(root);
		RBTREE_SETBLACK(lhs);
		RBTREE_SETBLACK(rhs);
	}
	return root;
}


/* Same as `RBTREE(insert)', but gracefully fail (by returning `false')
 * when  some other node already exists that is overlapping with `node' */
RBTREE_IMPL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL
RBTREE_NOTHROW(RBTREE_CC RBTREE(tryinsert))(RBTREE_T **__restrict proot,
                                            RBTREE_T *__restrict node) {
	RBTREE_T *root;
	_RBTREE_VALIDATE(*proot);
	root = *proot;
	root = RBTREE(_tryinsert_impl)(root, node);
	if (!root) {
		_RBTREE_VALIDATE(*proot);
		return 0;
	}
	RBTREE_SETBLACK(root);
	*proot = root;
	_RBTREE_VALIDATE(root);
	return 1;
}
#endif /* RBTREE_WANT_TRYINSERT */

#if !defined(RBTREE_OMIT_REMOVENODE) || !defined(RBTREE_OMIT_REMOVE) || defined(RBTREE_WANT_RREMOVE)
__PRIVATE __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_move_red_to_left))(RBTREE_T *__restrict node) {
	RBTREE_T *lhs, *rhs;
	RBTREE_FLIPCOLOR(node);
	lhs = RBTREE_GETLHS(node);
	rhs = RBTREE_GETRHS(node);
	if (lhs != RBTREE_NULL)
		RBTREE_FLIPCOLOR(lhs);
	if (rhs != RBTREE_NULL) {
		RBTREE_FLIPCOLOR(rhs);
		if (RBTREE_XISRED(RBTREE_GETLHS(rhs))) {
			rhs = RBTREE(_rotr)(rhs);
			RBTREE_SETRHS(node, rhs);
			node = RBTREE(_rotl)(node);
			RBTREE_FLIPCOLOR(node);
			lhs = RBTREE_GETLHS(node);
			rhs = RBTREE_GETRHS(node);
			if (lhs != RBTREE_NULL)
				RBTREE_FLIPCOLOR(lhs);
			if (rhs != RBTREE_NULL)
				RBTREE_FLIPCOLOR(rhs);
		}
	}
	return node;
}

__PRIVATE __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_move_red_to_right))(RBTREE_T *__restrict node) {
	RBTREE_T *lhs, *rhs;
	RBTREE_FLIPCOLOR(node);
	lhs = RBTREE_GETLHS(node);
	rhs = RBTREE_GETRHS(node);
	if (rhs != RBTREE_NULL)
		RBTREE_FLIPCOLOR(rhs);
	if (lhs != RBTREE_NULL) {
		RBTREE_FLIPCOLOR(lhs);
		if (RBTREE_XISRED(RBTREE_GETLHS(lhs))) {
			node = RBTREE(_rotr)(node);
			RBTREE_FLIPCOLOR(node);
			lhs = RBTREE_GETLHS(node);
			rhs = RBTREE_GETRHS(node);
			if (lhs != RBTREE_NULL)
				RBTREE_FLIPCOLOR(lhs);
			if (rhs != RBTREE_NULL)
				RBTREE_FLIPCOLOR(rhs);
		}
	}
	return node;
}

__PRIVATE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_balance_after_remove))(RBTREE_T *__restrict node) {
	RBTREE_T *lhs;
	if (RBTREE_XISRED(RBTREE_GETRHS(node)))
		node = RBTREE(_rotl)(node);
	lhs = RBTREE_GETLHS(node);
	if (RBTREE_XISRED(lhs) &&
	    RBTREE_XISRED(RBTREE_GETLHS(lhs)))
		node = RBTREE(_rotr)(node);
	if (RBTREE_XISRED(RBTREE_GETLHS(node)) &&
	    RBTREE_XISRED(RBTREE_GETRHS(node))) {
		RBTREE_FLIPCOLOR(node);
		RBTREE_SETBLACK(RBTREE_GETLHS(node));
		RBTREE_SETBLACK(RBTREE_GETRHS(node));
	}
	return node;
}

__PRIVATE __ATTR_NONNULL((1)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_remove_min))(RBTREE_T *__restrict node,
                                              RBTREE_T **__restrict pmin_node) {
	RBTREE_T *lhs;
	if (RBTREE_GETLHS(node) == RBTREE_NULL) {
		/* Found it! */
		*pmin_node = node;
		return RBTREE_NULL;
	}
	lhs = RBTREE_GETLHS(node);
	if (lhs != RBTREE_NULL && !RBTREE_ISRED(lhs) &&
	    !RBTREE_XISRED(RBTREE_GETLHS(lhs))) {
		node = RBTREE(_move_red_to_left)(node);
		lhs  = RBTREE_GETLHS(node);
	}
	lhs = RBTREE(_remove_min)(lhs, pmin_node);
	RBTREE_SETLHS(node, lhs);
	return RBTREE(_balance_after_remove)(node);
}

__PRIVATE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) RBTREE_T *
RBTREE_NOTHROW(RBTREE_CC RBTREE(_remove_impl))(RBTREE_T *root,
                                               RBTREE_T const *node) {
	RBTREE_T *lhs, *rhs;
	lhs = RBTREE_GETLHS(root);
	rhs = RBTREE_GETRHS(root);
	if (RBTREE_KEY_LO(RBTREE_GETMAXKEY(node), RBTREE_GETMINKEY(root))) {
		if (lhs != RBTREE_NULL && !RBTREE_ISRED(lhs) && !RBTREE_XISRED(RBTREE_GETLHS(lhs))) {
			root = RBTREE(_move_red_to_left)(root);
			lhs  = RBTREE_GETLHS(root);
			/*rhs = RBTREE_GETRHS(root);*/ /* Unused! */
		}
		lhs = RBTREE(_remove_impl)(lhs, node);
		RBTREE_SETLHS(root, lhs);
	} else {
		if (RBTREE_XISRED(lhs) && !RBTREE_XISRED(rhs)) {
			root = RBTREE(_rotr)(root);
			/*lhs = RBTREE_GETLHS(root);*/ /* Unused! */
			rhs = RBTREE_GETRHS(root);
		}
		if (root == node && rhs == RBTREE_NULL)
			return RBTREE_NULL; /* Found it! */
		if (rhs != RBTREE_NULL && !RBTREE_ISRED(rhs) && !RBTREE_XISRED(RBTREE_GETLHS(rhs))) {
			root = RBTREE(_move_red_to_right)(root);
			/*lhs = RBTREE_GETLHS(root);*/ /* Unused! */
			rhs = RBTREE_GETRHS(root);
		}
		if (root == node) {
			RBTREE_T *min_node;
			RBTREE_ASSERT(rhs != RBTREE_NULL);

			/* Remove the left-most node from our sub-tree, and have it take the place of `root' */
			rhs = RBTREE(_remove_min)(rhs, &min_node);

			/* Copy attributes from `root' to `min_node' */
			RBTREE_COPYCOLOR(min_node, root);
			RBTREE_SETLHS(min_node, RBTREE_GETLHS(root));
			/*RBTREE_SETRHS(min_node, RBTREE_GETRHS(root));*/ /* Unnecessary; s.a. `RBTREE_SETRHS(root, rhs);' below! */
#ifndef RBTREE_NDEBUG
#if __SIZEOF_POINTER__ == 4
			RBTREE_SETLHS(root, (RBTREE_T *)__UINT32_C(0xcccccccc));
			RBTREE_SETRHS(root, (RBTREE_T *)__UINT32_C(0xcccccccc));
#elif __SIZEOF_POINTER__ == 8
			RBTREE_SETLHS(root, (RBTREE_T *)__UINT64_C(0xcccccccccccccccc));
			RBTREE_SETRHS(root, (RBTREE_T *)__UINT64_C(0xcccccccccccccccc));
#endif /* __SIZEOF_POINTER__ == ... */
#endif /* !RBTREE_NDEBUG */

			/* Continue using `min_node' as the new root. */
			root = min_node;
		} else {
			rhs = RBTREE(_remove_impl)(rhs, node);
		}
		RBTREE_SETRHS(root, rhs);
	}
	return RBTREE(_balance_after_remove)(root);
}


/* Remove the given node from the given tree. */
#ifdef RBTREE_OMIT_REMOVENODE
__PRIVATE __ATTR_NONNULL((1, 2)) void
#else /* RBTREE_OMIT_REMOVENODE */
RBTREE_IMPL __ATTR_NONNULL((1, 2)) void
#endif /* !RBTREE_OMIT_REMOVENODE */
RBTREE_NOTHROW(RBTREE_CC RBTREE(removenode))(RBTREE_T **__restrict proot,
                                             RBTREE_T *__restrict node) {
	RBTREE_T *root;
	_RBTREE_VALIDATE(*proot);
	root = *proot;
	root = RBTREE(_remove_impl)(root, node);
#ifdef RBTREE_XSETBLACK
	RBTREE_XSETBLACK(root);
#else /* RBTREE_XSETBLACK */
	if (root != RBTREE_NULL)
		RBTREE_SETBLACK(root);
#endif /* !RBTREE_XSETBLACK */
	*proot = root;
#ifndef RBTREE_NDEBUG
#if __SIZEOF_POINTER__ == 4
	RBTREE_SETLHS(node, (RBTREE_T *)__UINT32_C(0xcccccccc));
	RBTREE_SETRHS(node, (RBTREE_T *)__UINT32_C(0xcccccccc));
#elif __SIZEOF_POINTER__ == 8
	RBTREE_SETLHS(node, (RBTREE_T *)__UINT64_C(0xcccccccccccccccc));
	RBTREE_SETRHS(node, (RBTREE_T *)__UINT64_C(0xcccccccccccccccc));
#endif /* __SIZEOF_POINTER__ == ... */
#endif /* !RBTREE_NDEBUG */
	_RBTREE_VALIDATE(root);
}

/* TODO: RBTREE(remove) and RBTREE(rremove) can be implemented more efficiently
 *       for  left-leaning RBTREEs by merging the node lookup with building the
 *       parent-path to that same node. */
#endif /* !RBTREE_OMIT_REMOVENODE || !RBTREE_OMIT_REMOVE || RBTREE_WANT_RREMOVE */

#else /* RBTREE_LEFT_LEANING */
/************************************************************************/
/* NORMAL                                                               */
/************************************************************************/

#ifndef RBTREE_REPPAR
#define RBTREE_REPPAR(self, oldv, newv) RBTREE_SETPAR(self, newv)
#endif /* !RBTREE_REPPAR */


#if (defined(RBTREE_WANT_TRYINSERT) || !defined(RBTREE_OMIT_INSERT) ||   \
     !defined(RBTREE_OMIT_REMOVENODE) || !defined(RBTREE_OMIT_REMOVE) || \
     defined(RBTREE_WANT_RREMOVE))
/* Have `self' swap positions with its rhs-child.
 *
 *          parent         >>        parent
 *             |           >>           |
 *           self          >>          rhs
 *          /    \         >>         /   \
 *        BBB     rhs      >>      self    AAA
 *               /   \     >>     /   \
 *           newrhs   AAA  >>   BBB    newrhs
 *
 * Modified nodes:                     parent, self, rhs
 * Modified nodes (parent-field only): newrhs */
__LOCAL __ATTR_NONNULL((1)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(_rotl))(RBTREE_T *__restrict self) {
	RBTREE_T *rhs, *parent, *newrhs;
	rhs = RBTREE_GETRHS(self);
	RBTREE_ASSERT(rhs != RBTREE_NULL);
	parent = RBTREE_GETPAR(self);
	newrhs = RBTREE_GETLHS(rhs);
	RBTREE_SETRHS(self, newrhs);
	RBTREE_SETLHS(rhs, self);
	RBTREE_SETPAR(self, rhs);
	if (newrhs != RBTREE_NULL)
		RBTREE_REPPAR(newrhs, rhs, self);
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

/* Have `self' swap positions with its lhs-child.
 *
 *          parent         >>        parent
 *             |           >>           |
 *           self          >>          lhs
 *          /    \         >>         /   \
 *        lhs     BBB      >>      AAA    self
 *       /   \             >>            /    \
 *     AAA    newlhs       >>         newlhs   BBB
 *
 * Modified nodes:                     parent, self, lhs
 * Modified nodes (parent-field only): newlhs */
__LOCAL __ATTR_NONNULL((1)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(_rotr))(RBTREE_T *__restrict self) {
	RBTREE_T *lhs, *parent, *newlhs;
	lhs = RBTREE_GETLHS(self);
	RBTREE_ASSERT(lhs != RBTREE_NULL);
	parent = RBTREE_GETPAR(self);
	newlhs = RBTREE_GETRHS(lhs);
	RBTREE_SETLHS(self, newlhs);
	RBTREE_SETRHS(lhs, self);
	RBTREE_SETPAR(self, lhs);
	if (newlhs != RBTREE_NULL)
		RBTREE_REPPAR(newlhs, lhs, self);
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
#endif /* ... */


#if defined(RBTREE_WANT_TRYINSERT) || !defined(RBTREE_OMIT_INSERT)
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

RBTREE_IMPL __ATTR_NONNULL((1, 2, 3)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(_insert_repair))(RBTREE_T **__restrict proot,
                                                 RBTREE_T *__restrict node,
                                                 RBTREE_T *__restrict parent) {
again:
	RBTREE_ASSERT(RBTREE_ISRED(node));
	RBTREE_ASSERT(parent != RBTREE_NULL);
	RBTREE_ASSERT(parent == RBTREE_GETPAR(node));
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
			 *     takes  the  place of  `node', of  the potentially
			 *     out-of-place RED node having to be fixed.
			 */
			RBTREE_SETBLACK(parent);
			RBTREE_SETBLACK(uncle);
			/* node = _RBTREE_GETGRANDPARENT(node); */
			node = RBTREE_GETPAR(parent);
			RBTREE_ASSERTF(node != RBTREE_NULL,
			               "We've got an uncle, so we should "
			               "also have a grandparent");
			RBTREE_SETRED(node);
/*again_repair_node:*/
			parent = RBTREE_GETPAR(node);
			if (parent == RBTREE_NULL) {
/*set_node_black_and_return:*/
				RBTREE_SETBLACK(node); /* The root node is black. */
				_RBTREE_VALIDATE(*proot);
				return;
			}
			goto again;
		} else {
			/* Insert-case: #4 */
			RBTREE_T *grandparent;
			grandparent = RBTREE_GETPAR(parent);
			RBTREE_ASSERT(grandparent != RBTREE_NULL);
			if (node == RBTREE_GETRHS(parent)) {
				if (parent == RBTREE_GETLHS(grandparent)) {
					(RBTREE(_rotl)(parent));
					parent      = node;
					node        = RBTREE_GETLHS(parent);
					grandparent = RBTREE_GETPAR(parent);
				}
			} else {
				RBTREE_ASSERT(node == RBTREE_GETLHS(parent));
				if (parent == RBTREE_GETRHS(grandparent)) {
					(RBTREE(_rotr)(parent));
					parent      = node;
					node        = RBTREE_GETRHS(parent);
					grandparent = RBTREE_GETPAR(parent);
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
			if (RBTREE_GETPAR(*proot)) {
				do {
					*proot = RBTREE_GETPAR(*proot);
				} while (RBTREE_GETPAR(*proot));
			}
		}
	}
	_RBTREE_VALIDATE(*proot);
}
#endif /* RBTREE_WANT_TRYINSERT || !RBTREE_OMIT_INSERT */

#ifndef RBTREE_OMIT_INSERT
/* Insert the given node into the given tree. The caller must ensure
 * that no  already-existing node  overlaps  with the  given  `node' */
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
/*set_node_black_and_return:*/
		RBTREE_SETBLACK(node); /* The root node is black. */
		_RBTREE_VALIDATE(*proot);
		return;
	}
	parent = (RBTREE(_insert_worker)(root, node));
	/* Repair the RB-tree. */
	(RBTREE(_insert_repair)(proot, node, parent));
}
#endif /* !RBTREE_OMIT_INSERT */


#ifdef RBTREE_WANT_TRYINSERT
/* Same as `RBTREE(insert)', but gracefully fail (by returning `false')
 * when  some other node already exists that is overlapping with `node' */
RBTREE_IMPL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __BOOL
RBTREE_NOTHROW(RBTREE_CC RBTREE(tryinsert))(RBTREE_T **__restrict proot,
                                            RBTREE_T *__restrict node) {
	RBTREE_T *root = *proot;
	_RBTREE_VALIDATE(root);
	if __unlikely(!root) {
		/* Special case: First node. (Insert-case: #1) */
		*proot = node;
		RBTREE_SETPAR(node, RBTREE_NULL);
		RBTREE_SETLHS(node, RBTREE_NULL);
		RBTREE_SETRHS(node, RBTREE_NULL);
/*set_node_black_and_return:*/
		RBTREE_SETBLACK(node); /* The root node is black. */
		_RBTREE_VALIDATE(*proot);
		return 1;
	}
again:
	/* Gracefully fail if the given range is already mapped. */
	if (_RBTREE_OVERLAPPING(root, node)) {
		_RBTREE_VALIDATE(*proot);
		return 0;
	}
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
	/* Repair the RB-tree. */
	(RBTREE(_insert_repair)(proot, node, root));
	return 1;
}
#endif /* RBTREE_WANT_TRYINSERT */

#if !defined(RBTREE_OMIT_REMOVENODE) || !defined(RBTREE_OMIT_REMOVE) || defined(RBTREE_WANT_RREMOVE)
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
#ifdef RBTREE_HASPAR
		RBTREE_ASSERT(RBTREE_HASPAR(temp, node));
#else /* RBTREE_HASPAR */
		RBTREE_ASSERT(RBTREE_GETPAR(temp) == node);
#endif /* !RBTREE_HASPAR */
		RBTREE_REPPAR(temp, node, repl);
	}
	temp = RBTREE_GETRHS(node);
	RBTREE_SETRHS(repl, temp);
	if (temp != RBTREE_NULL) {
#ifdef RBTREE_HASPAR
		RBTREE_ASSERT(RBTREE_HASPAR(temp, node));
#else /* RBTREE_HASPAR */
		RBTREE_ASSERT(RBTREE_GETPAR(temp) == node);
#endif /* !RBTREE_HASPAR */
		RBTREE_REPPAR(temp, node, repl);
	}
}

/* Remove the given node from the given tree. */
#ifdef RBTREE_OMIT_REMOVENODE
__PRIVATE __ATTR_NONNULL((1, 2)) void
#else /* RBTREE_OMIT_REMOVENODE */
RBTREE_IMPL __ATTR_NONNULL((1, 2)) void
#endif /* !RBTREE_OMIT_REMOVENODE */
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
	/* Find the  node with  which to  replace the  given  `node'.
	 * This this purpose, when our node what 2 non-NULL children,
	 * then we must replace `node' with either the MAX-node  from
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
		 * child  nodes, so when we call ourselves recursively,
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
#ifdef RBTREE_REPPAR_MAYBE_NULL
	RBTREE_REPPAR_MAYBE_NULL(lhs, node, parent, proot);
#else /* RBTREE_REPPAR_MAYBE_NULL */
	RBTREE_SETPAR(lhs, parent);
#endif /* !RBTREE_REPPAR_MAYBE_NULL */
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
				                                 !RBTREE_XISRED(RBTREE_GETLHS(sibling)) &&
				                                 !RBTREE_XISRED(RBTREE_GETRHS(sibling));
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
							if (!RBTREE_XISRED(RBTREE_GETRHS(sibling)) && RBTREE_XISRED(RBTREE_GETLHS(sibling))) {
								RBTREE_SETRED(sibling);
								RBTREE_SETBLACK(RBTREE_GETLHS(sibling));
								(RBTREE(_rotr)(sibling));
							}
						} else {
							RBTREE_ASSERT(fixnode == RBTREE_GETRHS(parent));
							if (!RBTREE_XISRED(RBTREE_GETLHS(sibling)) && RBTREE_XISRED(RBTREE_GETRHS(sibling))) {
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
#endif /* !RBTREE_OMIT_REMOVENODE || !RBTREE_OMIT_REMOVE || RBTREE_WANT_RREMOVE */
#endif /* !RBTREE_LEFT_LEANING */


#ifndef RBTREE_OMIT_REMOVE
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
#endif /* !RBTREE_OMIT_REMOVE */


#ifdef RBTREE_WANT_RREMOVE
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
#endif /* RBTREE_WANT_RREMOVE */

#if defined(RBTREE_WANT_PREV_NEXT_NODE) || defined(RBTREE_WANT_MINMAXLOCATE)
/* Return the next node with a key-range located below `node'
 * If  no  such  node exists,  return  `RBTREE_NULL' instead.
 * NOTE: This function takes O(log(N)) to execute. */
#ifdef RBTREE_WANT_PREV_NEXT_NODE
RBTREE_IMPL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
#else /* RBTREE_WANT_PREV_NEXT_NODE */
__PRIVATE __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
#endif /* !RBTREE_WANT_PREV_NEXT_NODE */
RBTREE_NOTHROW(RBTREE_CC RBTREE(prevnode))(RBTREE_T const *__restrict node) {
	RBTREE_T *result;
	result = RBTREE_GETLHS(node);
	if (result == RBTREE_NULL) {
		/* Keep going up until we reach the ROOT (NULL),
		 * or reach a  parent via its  RHS-child-branch. */
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
 * If  no  such  node exists,  return  `RBTREE_NULL' instead.
 * NOTE: This function takes O(log(N)) to execute. */
#ifdef RBTREE_WANT_PREV_NEXT_NODE
RBTREE_IMPL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
#else /* RBTREE_WANT_PREV_NEXT_NODE */
__PRIVATE __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) RBTREE_T *
#endif /* !RBTREE_WANT_PREV_NEXT_NODE */
RBTREE_NOTHROW(RBTREE_CC RBTREE(nextnode))(RBTREE_T const *__restrict node) {
	RBTREE_T *result;
	result = RBTREE_GETRHS(node);
	if (result == RBTREE_NULL) {
		/* Keep going up until we reach the ROOT (NULL),
		 * or reach a  parent via its  LHS-child-branch. */
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
#endif /* RBTREE_WANT_PREV_NEXT_NODE || RBTREE_WANT_MINMAXLOCATE */


#ifdef RBTREE_WANT_MINMAXLOCATE
#ifndef RBTREE_KEY_SETMIN
#define RBTREE_KEY_SETMIN(v) ((v) = (RBTREE_Tkey)0)
#endif /* !RBTREE_KEY_SETMIN */
#ifndef RBTREE_KEY_SETMAX
#define RBTREE_KEY_SETMAX(v) ((v) = (RBTREE_Tkey)-1)
#endif /* !RBTREE_KEY_SETMAX */

/* Find the lowest and greatest nodes that are overlapping with the given key-range. */
RBTREE_IMPL __ATTR_NONNULL((4)) void
RBTREE_NOTHROW(RBTREE_CC RBTREE(minmaxlocate))(RBTREE_T *root,
                                               RBTREE_Tkey minkey, RBTREE_Tkey maxkey,
                                               RBTREE(minmax_t) *__restrict result) {
	_RBTREE_VALIDATE(root);
	while (root) {
		RBTREE_T *min_node, *max_node, *iter;
		if (RBTREE_KEY_LO(maxkey, RBTREE_GETMINKEY(root))) {
			root = RBTREE_GETLHS(root);
			continue;
		}
		if (RBTREE_KEY_GR(minkey, RBTREE_GETMAXKEY(root))) {
			root = RBTREE_GETRHS(root);
			continue;
		}
		/* Found an overlapping node:
		 *               13
		 *              /  \
		 *             /    \
		 *            /      \
		 *           8        17
		 *          / \      /  \
		 *         1   11  15    25
		 *          \           /  \
		 *           6        22    27
		 *
		 * Imagine minkey=9, maxkey=25
		 * - Right now, `root' is `13'
		 * - The expected min-node is `11', and
		 *   the  expected  max-node  is   `25'
		 *
		 * As such, we can find the min-node:
		 *   >> MIN_NODE = root;
		 *   >> for (;;) {
		 *   >>     ITER = MIN_NODE->LHS;
		 *   >>     if (ITER == NULL)
		 *   >>         break;
		 *   >>     if (MAX_KEY(ITER) >= minkey) {
		 *   >>         MIN_NODE = ITER;
		 *   >>         continue;
		 *   >>     }
		 *   >>     // Check if we can find an in-range key in ITER->RHS[->RHS...]
		 *   >>     ITER = ITER->RHS;
		 *   >>     while (ITER != NULL) {
		 *   >>         if (MAX_KEY(ITER) >= minkey) {
		 *   >>             MIN_NODE = ITER;
		 *   >>             break;
		 *   >>         }
		 *   >>         ITER = ITER->RHS;
		 *   >>     }
		 *   >>     break;
		 *   >> }
		 * To  find the max-node, we do the same,
		 * but with mirrored LHS/RHS and MIN/MAX. */
		min_node = root;
		for (;;) {
			iter = RBTREE_GETLHS(min_node);
			if (iter == RBTREE_NULL)
				break;
			if (RBTREE_KEY_GE(RBTREE_GETMAXKEY(iter), minkey)) {
				min_node = iter;
				continue;
			}
			/* Check if we can find an in-range key in iter->RHS[->RHS...] */
			iter = RBTREE_GETRHS(iter);
			while (iter != RBTREE_NULL) {
				if (RBTREE_KEY_GE(RBTREE_GETMAXKEY(iter), minkey)) {
					min_node = iter;
					break;
				}
				iter = RBTREE_GETRHS(iter);
			}
			break;
		}
		max_node = root;
		for (;;) {
			iter = RBTREE_GETRHS(max_node);
			if (iter == RBTREE_NULL)
				break;
			if (RBTREE_KEY_LE(RBTREE_GETMINKEY(iter), maxkey)) {
				max_node = iter;
				continue;
			}
			/* Check if we can find an in-range key in iter->LHS[->LHS...] */
			iter = RBTREE_GETLHS(iter);
			while (iter != RBTREE_NULL) {
				if (RBTREE_KEY_LE(RBTREE_GETMINKEY(iter), maxkey)) {
					max_node = iter;
					break;
				}
				iter = RBTREE_GETLHS(iter);
			}
			break;
		}
		/* Because the min/max-range may be spread across different sub-trees,
		 * we must still  check for the  case where the  predecessor/successor
		 * the min/max node continues to be in-bounds! */
		for (;;) {
			iter = RBTREE(prevnode)(min_node);
			if (!iter)
				break;
			if (RBTREE_KEY_LO(RBTREE_GETMAXKEY(iter), minkey))
				break;
			min_node = iter;
		}
		for (;;) {
			iter = RBTREE(nextnode)(max_node);
			if (!iter)
				break;
			if (RBTREE_KEY_GR(RBTREE_GETMINKEY(iter), maxkey))
				break;
			max_node = iter;
		}
		/* Write-back our results. */
		result->mm_min = min_node;
		result->mm_max = max_node;
		return;
	}
	/* There aren't any node that are in-bounds. */
	result->mm_min = RBTREE_NULL;
	result->mm_max = RBTREE_NULL;
}
#endif /* RBTREE_WANT_MINMAXLOCATE */

#undef _RBTREE_OVERLAPPING
#undef _RBTREE_GETSIBLING
#undef _RBTREE_VALIDATE

__DECL_END
#endif /* !RBTREE_HEADER_ONLY */


#undef RBTREE_IMPLEMENTATION_ONLY
#undef RBTREE_HEADER_ONLY

#undef RBTREE_DEBUG
#undef RBTREE_NDEBUG
#undef RBTREE_NULL
#undef RBTREE_NULL_IS_IMPLICIT_BLACK
#undef RBTREE_DECL
#undef RBTREE_IMPL
#undef RBTREE_CC
#undef RBTREE_NOTHROW
#undef RBTREE_ASSERT
#undef RBTREE_ASSERTF
#undef RBTREE_ASSERT_IS_NOOP

#undef RBTREE_MINKEY_EQ_MAXKEY
#undef RBTREE_LEFT_LEANING

#undef RBTREE_KEY_LO
#undef RBTREE_KEY_EQ
#undef RBTREE_KEY_NE
#undef RBTREE_KEY_GR
#undef RBTREE_KEY_GE
#undef RBTREE_KEY_LE
#undef RBTREE_KEY_SETMIN
#undef RBTREE_KEY_SETMAX

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
#undef RBTREE_GETKEY
#undef RBTREE_ISRED
#undef RBTREE_XISRED
#undef RBTREE_SETRED
#undef RBTREE_SETBLACK
#undef RBTREE_FLIPCOLOR
#undef RBTREE_COPYCOLOR
#undef RBTREE_T
#undef RBTREE_Tkey
#undef RBTREE

#undef RBTREE_WANT_MINMAXLOCATE
#undef RBTREE_WANT_PREV_NEXT_NODE
#undef RBTREE_WANT_RREMOVE
#undef RBTREE_WANT_RLOCATE
#undef RBTREE_WANT_TRYINSERT
#undef RBTREE_OMIT_REMOVE
