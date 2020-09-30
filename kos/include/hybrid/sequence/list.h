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
#ifndef __GUARD_HYBRID_SEQUENCE_LIST_H
#define __GUARD_HYBRID_SEQUENCE_LIST_H 1

#include "../../__stdinc.h"
#include "../__assert.h"

#ifdef __CC__
__DECL_BEGIN

/* ========================================================================
 *          LIST OVERVIEW
 * ========================================================================
 * SLIST -- Singly linked list (single direction; remove/insert required self-pointer)
 *          - O(1) Insert / remove at front
 *          - O(1) Insert after another element
 * LLIST -- Linked list (double direction; single-ended)
 *          - O(1) Insert / remove anywhere
 *          - O(1) Insert before / after another element
 *          - O(1) Check if element is apart of list
 *          - Elements can be removed without needing to know their associated list
 * ========================================================================
 *  T   -- The type for which the list is being used
 *  key -- The name of a simple attribute `T::key', detailing the name of nodes
 * ========================================================================
 *  FUNCTIONS (SL -- Availability)
 * [SL][-------------------------------------------------------------------]
 * [++][     ?LIST(T)        ->  struct { ... } // type expression for the list controller
 * [++][     ?LIST_NODE(T)   ->  struct { ... } // type expression for list nodes
 * [++][     ?LIST_INIT      ->  { ... }        // __NULLPTR-Initializer for `LIST(T)'
 * [++][     ?LIST_INITNODE  ->  { ... }        // __NULLPTR-Initializer for `LIST_NODE(T)'
 * [++][bool ?LIST_EMPTY(LIST &l);
 * [++][bool ?LIST_NONEMPTY(LIST &l);
 * [ +][T   *?LIST_PREV(T, T *elem, key);
 * [++][T  *&?LIST_NEXT(T *elem, key);
 * [++][bool ?LIST_HASNEXT(T *elem, key);
 * [ +][bool ?LIST_HASPREV(LIST &l, T *elem, key);
 * [++][T  *&?LIST_XNEXT(T *elem, key);             // Same as `LIST_NEXT()', but return `__NULLPTR' when there is no successor
 * [ +][T   *?LIST_XPREV(T, LIST &l, T *elem, key); // Same as `LIST_PREV()', but return `__NULLPTR' when there is no successor
 * [++][T  *&?LIST_HEAD(LIST &l);
 * [++][     ?LIST_FOREACH(T *elem, LIST &l, key) { ... }
 * [ +][     ?LIST_RFOREACH(T, T *elem, LIST &l, T *start, key) { ... }
 * [+ ][     ?LIST_PFOREACH(T **pelem, T *elem, LIST &l, key) { ... }
 * [++][void ?LIST_INSERT(LIST &l, T *elem, key);                             // Insert in the front
 * [+ ][void ?LIST_INSERT_BEFORE(T *elem, T **psuccessor, T *successor, key); // Insert before `successor'
 * [ +][void ?LIST_INSERT_BEFORE(T *elem, T *successor, key);                 // Insert before `successor'
 * [++][void ?LIST_INSERT_AFTER(T *predecessor, T *elem, key);                // Insert after `predecessor'
 * [+ ][void ?LIST_REPLACE(T **pelem, T *elem, T *new_elem, key); // `elem' will not be marked as unbound
 * [ +][void ?LIST_REPLACE(T *elem, T *new_elem, key);            // `elem' will not be marked as unbound
 * [+ ][void ?LIST_REMOVE(T **pelem, T *elem, key);
 * [ +][void ?LIST_REMOVE(T *elem, key);        // Remove `elem' from its list, but don't mark it as unbound
 * [ +][void ?LIST_UNLINK(T *elem, key);        // Same as `REMOVE()', but also mark `elem' as unbound
 * [ +][void ?LIST_UNBIND(T *elem, key);        // Mark `elem' as unbound
 * [ +][bool ?LIST_ISBOUND(T *elem, key);       // Check if `elem' is bound (part of a list)
 * ========================================================================
 * Function variants:
 * >> *_P(..., PREDICATE getpath)
 *    Instead of a member-key, call `getpath()' which should behave as:
 *    >> LIST_NODE(T) &getpath(T &elem);
 *    The key-variants are identical to `#define getpath(elem) elem->key'
 * ========================================================================
 * >> struct item {
 * >> 	SLIST_NODE(struct item) i_node;
 * >> 	int                     i_value;
 * >> };
 * >> PRIVATE SLIST(struct item) items;
 * >> void insert(struct item *i) {
 * >> 	SLIST_INSERT(items,i,i_node);
 * >> }
 * >> struct item *remove(int value) {
 * >> 	struct item **pi,*i;
 * >> 	SLIST_PFOREACH(pi,i,items,i_node) {
 * >> 		if (i->i_value == value) {
 * >> 			SLIST_REMOVE(pi,i,i_node);
 * >> 			return i;
 * >> 		}
 * >> 	}
 * >> 	return __NULLPTR;
 * >> }
 */



/* SLIST */
#define SLIST(T) T * /* [0..1] List head */
#define SLIST_NODE(T)                         \
	struct {                                  \
		T *sn_next; /* [0..1] Next pointer */ \
	}
#define SLIST_INIT __NULLPTR
#define SLIST_INITNODE \
	{ __NULLPTR }
#define SLIST_EMPTY(l)                                              ((l) == __NULLPTR)
#define SLIST_NONEMPTY(l)                                           ((l) != __NULLPTR)
#define SLIST_NEXT(elem, key)                                       ((elem)->key.sn_next)
#define SLIST_NEXT_P(elem, getpath)                                 (getpath(elem).sn_next)
#define SLIST_HASNEXT(elem, key)                                    ((elem)->key.sn_next != __NULLPTR)
#define SLIST_HASNEXT_P(elem, getpath)                              (getpath(elem).sn_next != __NULLPTR)
#define SLIST_XNEXT(elem, key)                                      ((elem)->key.sn_next)
#define SLIST_XNEXT_P(elem, getpath)                                (getpath(elem).sn_next)
#define SLIST_HEAD(l)                                               ((l))
#define SLIST_FOREACH(elem, l, key)                                 for ((elem) = (l); (elem); (elem) = (elem)->key.sn_next)
#define SLIST_FOREACH_P(elem, l, getpath)                           for ((elem) = (l); (elem); (elem) = getpath(elem).sn_next)
#define SLIST_PFOREACH(pelem, elem, l, key)                         for ((pelem) = &(l); (elem) = *(pelem); (pelem) = &(elem)->key.sn_next)
#define SLIST_PFOREACH_P(pelem, elem, l, getpath)                   for ((pelem) = &(l); (elem) = *(pelem); (pelem) = &getpath(elem).sn_next)
#define SLIST_INSERT(l, elem, key)                                  (void)((elem)->key.sn_next = (l), (l) = (elem))
#define SLIST_INSERT_P(l, elem, getpath)                            (void)(getpath(elem).sn_next = (l), (l) = (elem))
#define SLIST_INSERT_BEFORE(elem, psuccessor, successor, key)       (void)(__hybrid_assert(*(psuccessor) == (successor)), (elem)->key.sn_next = (successor), *(psuccessor) = (elem))
#define SLIST_INSERT_BEFORE_P(elem, psuccessor, successor, getpath) (void)(__hybrid_assert(*(psuccessor) == (successor)), getpath(elem).sn_next = (successor), *(psuccessor) = (elem))
#define SLIST_INSERT_AFTER(predecessor, elem, key)                  (void)((elem)->key.sn_next = (predecessor)->key.sn_next, (predecessor)->key.sn_next = (elem))
#define SLIST_INSERT_AFTER_P(predecessor, elem, getpath)            (void)(getpath(elem).sn_next = getpath(predecessor).sn_next, getpath(predecessor).sn_next = (elem))
#define SLIST_REPLACE(pelem, elem, new_elem, key)                   (void)(__hybrid_assert(*(pelem) == (elem)), (new_elem)->key.sn_next = (elem)->key.sn_next, *(pelem) = (new_elem))
#define SLIST_REPLACE_P(pelem, elem, new_elem, getpath)             (void)(__hybrid_assert(*(pelem) == (elem)), getpath(new_elem).sn_next = getpath(elem).sn_next, *(pelem) = (new_elem))
#define SLIST_REMOVE(pelem, elem, key)                              (void)(__hybrid_assert(*(pelem) == (elem)), *(pelem) = (elem)->key.sn_next)
#define SLIST_REMOVE_P(pelem, elem, getpath)                        (void)(__hybrid_assert(*(pelem) == (elem)), *(pelem) = getpath(elem).sn_next)

/* LLIST */
#define LLIST(T) T * /* [0..1] List head */
#define LLIST_NODE(T)                                                                               \
	struct {                                                                                        \
		T *ln_next /* [0..1] Next pointer */,                                                       \
		**ln_pself; /* [1..1][?..1] Self pointer (When `__NULLPTR', element isn't apart of list) */ \
	}
#define LLIST_INIT __NULLPTR
#define LLIST_INITNODE \
	{ __NULLPTR, __NULLPTR }
#define LLIST_EMPTY(l)                         ((l) == __NULLPTR)
#define LLIST_NONEMPTY(l)                      ((l) != __NULLPTR)
#define LLIST_NEXT(elem, key)                  ((elem)->key.ln_next)
#define LLIST_NEXT_P(elem, getpath)            (getpath(elem).ln_next)
#define LLIST_PREV(T, elem, key)               __COMPILER_CONTAINER_OF((elem)->key.ln_pself, T, key.ln_next)
#define LLIST_HASNEXT(elem, key)               ((elem)->key.ln_next != __NULLPTR)
#define LLIST_HASNEXT_P(elem, getpath)         (getpath(elem).ln_next != __NULLPTR)
#define LLIST_HASPREV(l, elem, key)            ((elem)->key.ln_pself != &(l))
#define LLIST_HASPREV_P(l, elem, getpath)      (getpath(elem).ln_pself != &(l))
#define LLIST_XNEXT(elem, key)                 ((elem)->key.ln_next)
#define LLIST_XNEXT_P(elem, getpath)           (getpath(elem).ln_next)
#define LLIST_XPREV(T, l, elem, key)           (LLIST_HASPREV(l, elem, key) ? LLIST_PREV(T, elem, key) : __NULLPTR)
#define LLIST_HEAD(l)                          (l)
#define LLIST_FOREACH(elem, l, key)            for ((elem) = (l); (elem); (elem) = (elem)->key.ln_next)
#define LLIST_FOREACH_P(elem, l, getpath)      for ((elem) = (l); (elem); (elem) = getpath(elem).ln_next)
#define LLIST_RFOREACH(T, elem, l, start, key) for ((elem) = (start); (elem); (elem) = LLIST_XPREV(T, l, elem, key))
#define LLIST_INSERT(l, elem, key)                            \
	(void)(((elem)->key.ln_next = (l)) != __NULLPTR           \
	       ? (void)((l)->key.ln_pself = &(elem)->key.ln_next) \
	       : (void)0,                                         \
	       *((elem)->key.ln_pself = &(l)) = (elem))
#define LLIST_INSERT_P(l, elem, getpath)                            \
	(void)((getpath(elem).ln_next = (l)) != __NULLPTR               \
	       ? (void)(getpath((l)).ln_pself = &getpath(elem).ln_next) \
	       : (void)0,                                               \
	       *(getpath(elem).ln_pself = &(l)) = (elem))
#define LLIST_INSERT_BEFORE(elem, successor, key)                        \
	(void)(*((elem)->key.ln_pself = (successor)->key.ln_pself) = (elem), \
	       *((successor)->key.ln_pself = &(elem)->key.ln_next) = (successor))
#define LLIST_INSERT_BEFORE_P(elem, successor, getpath)                      \
	(void)(*(getpath(elem).ln_pself = getpath(successor).ln_pself) = (elem), \
	       *(getpath(successor).ln_pself = &getpath(elem).ln_next) = (successor))
#define LLIST_INSERT_AFTER(predecessor, elem, key)                                                    \
	(void)(((elem)->key.ln_next = *((elem)->key.ln_pself = &(predecessor)->key.ln_next)) != __NULLPTR \
	       ? (void)((elem)->key.ln_next->key.ln_pself = &(elem)->key.ln_next)                         \
	       : (void)0,                                                                                 \
	       (predecessor)->key.ln_next = (elem))
#define LLIST_INSERT_AFTER_P(predecessor, elem, getpath)                                                    \
	(void)((getpath(elem).ln_next = *(getpath(elem).ln_pself = &getpath(predecessor).ln_next)) != __NULLPTR \
	       ? (void)(getpath(getpath(elem).ln_next).ln_pself = &getpath(elem).ln_next)                       \
	       : (void)0,                                                                                       \
	       getpath(predecessor).ln_next = (elem))
#define LLIST_REPLACE(elem, new_elem, key)                                            \
	(void)(*((new_elem)->key.ln_pself = (elem)->key.ln_pself) = (new_elem),           \
	       ((new_elem)->key.ln_next = (elem)->key.ln_next) != __NULLPTR               \
	       ? (void)((new_elem)->key.ln_next->key.ln_pself = &(new_elem)->key.ln_next) \
	       : (void)0)
#define LLIST_REPLACE_P(elem, new_elem, getpath)                                              \
	(void)(*(getpath(new_elem).ln_pself = getpath(elem).ln_pself) = (new_elem),               \
	       (getpath(new_elem).ln_next = getpath(elem).ln_next) != __NULLPTR                   \
	       ? (void)(getpath(getpath(new_elem).ln_next).ln_pself = &getpath(new_elem).ln_next) \
	       : (void)0)
#define LLIST_REMOVE(elem, key)                                         \
	((*(elem)->key.ln_pself = (elem)->key.ln_next) != __NULLPTR         \
	 ? (void)((elem)->key.ln_next->key.ln_pself = (elem)->key.ln_pself) \
	 : (void)0)
#define LLIST_REMOVE_P(elem, getpath)                                           \
	((*getpath(elem).ln_pself = getpath(elem).ln_next) != __NULLPTR             \
	 ? (void)(getpath(getpath(elem).ln_next).ln_pself = getpath(elem).ln_pself) \
	 : (void)0)
#define LLIST_UNBIND(elem, key)        (void)((elem)->key.ln_pself = __NULLPTR)
#define LLIST_UNBIND_P(elem, getpath)  (void)(getpath(elem).ln_pself = __NULLPTR)
#define LLIST_ISBOUND(elem, key)       ((elem)->key.ln_pself != __NULLPTR)
#define LLIST_ISBOUND_P(elem, getpath) (getpath(elem).ln_pself != __NULLPTR)
#define LLIST_UNLINK(elem, key)        (LLIST_REMOVE(elem, key), LLIST_UNBIND(elem, key))
#define LLIST_UNLINK_P(elem, getpath)  (LLIST_REMOVE_P(elem, getpath), LLIST_UNBIND_P(elem, getpath))

__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_SEQUENCE_LIST_H */
