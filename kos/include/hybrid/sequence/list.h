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
#include <stddef.h>

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
 * DLIST -- Double linked list (double direction; double-ended)
 *          - O(1) Insert / remove anywhere
 *          - O(1) Insert before / after another element
 *          - O(1) Check if element is apart of list
 *          - O(1) Access to the first & last element
 *          - Elements can be removed without needing to know their associated list
 * ========================================================================
 *  T   -- The type for which the list is being used
 *  key -- The name of a simple attribute `T::key', detailing the name of nodes
 * ========================================================================
 *  FUNCTIONS (SLD -- Availability)
 * [SLD][-------------------------------------------------------------------]
 * [+++][     ?LIST(T)        ->  struct { ... } // type expression for the list controller
 * [+++][     ?LIST_NODE(T)   ->  struct { ... } // type expression for list nodes
 * [+++][     ?LIST_INIT      ->  { ... }        // NULL-Initializer for `LIST(T)'
 * [+++][     ?LIST_INITNODE  ->  { ... }        // NULL-Initializer for `LIST_NODE(T)'
 * [+++][bool ?LIST_EMPTY(LIST &l);
 * [+++][bool ?LIST_NONEMPTY(LIST &l);
 * [ + ][T   *?LIST_PREV(T, T *elem, key);
 * [  +][T   *?LIST_PREV(T *elem, key);
 * [+++][T  *&?LIST_NEXT(T *elem, key);
 * [+++][bool ?LIST_HASNEXT(T *elem, key);
 * [ + ][bool ?LIST_HASPREV(LIST &l, T *elem, key);
 * [  +][bool ?LIST_HASPREV(T *elem, key);
 * [+++][T  *&?LIST_XNEXT(T *elem, key);             // Same as `LIST_NEXT()', but return `NULL' when there is no successor
 * [ + ][T   *?LIST_XPREV(T, LIST &l, T *elem, key); // Same as `LIST_PREV()', but return `NULL' when there is no successor
 * [  +][T   *?LIST_XPREV(LIST &l, T *elem, key);    // Same as `LIST_PREV()', but return `NULL' when there is no successor
 * [+++][T  *&?LIST_HEAD(LIST &l);
 * [  +][T  *&?LIST_BACK(LIST &l);
 * [+++][     ?LIST_FOREACH(T *elem, LIST &l, key) { ... }
 * [ + ][     ?LIST_RFOREACH(T, T *elem, LIST &l, T *start, key) { ... }
 * [  +][     ?LIST_RFOREACH(T *elem, LIST &l, key) { ... }
 * [+  ][     ?LIST_PFOREACH(T **pelem, T *elem, LIST &l, key) { ... }
 * [+++][void ?LIST_INSERT(LIST &l, T *elem, key);                             // Insert in the front
 * [  +][void ?LIST_INSERT_BACK(LIST &l, T *elem, key);                        // Insert in the back
 * [+  ][void ?LIST_INSERT_BEFORE(T *elem, T **psuccessor, T *successor, key); // Insert before `successor'
 * [ ++][void ?LIST_INSERT_BEFORE(T *elem, T *successor, key);                 // Insert before `successor'
 * [+++][void ?LIST_INSERT_AFTER(T *predecessor, T *elem, key);                // Insert after `predecessor'
 * [+  ][void ?LIST_REPLACE(T **pelem, T *elem, T *new_elem, key); // `elem' will not be marked as unbound
 * [ ++][void ?LIST_REPLACE(T *elem, T *new_elem, key);            // `elem' will not be marked as unbound
 * [+  ][void ?LIST_REMOVE(T **pelem, T *elem, key);
 * [ ++][void ?LIST_REMOVE(T *elem, key);        // Remove `elem' from its list, but don't mark it as unbound
 * [ ++][void ?LIST_UNLINK(T *elem, key);        // Same as `REMOVE()', but also mark `elem' as unbound
 * [ ++][void ?LIST_UNBIND(T *elem, key);        // Mark `elem' as unbound
 * [ ++][bool ?LIST_ISBOUND(T *elem, key);       // Check if `elem' is bound (part of a list)
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
 * >> 	return NULL;
 * >> }
 * >> 
 *
 */



/* SLIST */
#define SLIST(T)                               T *           /* [0..1] List head */
#define SLIST_NODE(T)                 struct { T *sn_next;   /* [0..1] Next pointer */ }
#define SLIST_INIT                           { NULL }
#define SLIST_INITNODE                       { NULL }
#define SLIST_EMPTY(l)                       ((l)==NULL)
#define SLIST_NONEMPTY(l)                    ((l)!=NULL)
#define SLIST_NEXT(elem,key)                 ((elem)->key.sn_next)
#define SLIST_NEXT_P(elem,getpath)           (getpath(elem).sn_next)
#define SLIST_HASNEXT(elem,key)              ((elem)->key.sn_next!=NULL)
#define SLIST_HASNEXT_P(elem,getpath)        (getpath(elem).sn_next!=NULL)
#define SLIST_XNEXT(elem,key)                ((elem)->key.sn_next)
#define SLIST_XNEXT_P(elem,getpath)          (getpath(elem).sn_next)
#define SLIST_HEAD(l)                        ((l))
#define SLIST_FOREACH(elem,l,key)            for((elem)=(l);(elem);(elem)=(elem)->key.sn_next)
#define SLIST_FOREACH_P(elem,l,getpath)      for((elem)=(l);(elem);(elem)=getpath(elem).sn_next)
#define SLIST_PFOREACH(pelem,elem,l,key)     for((pelem)=&(l);(elem)=*(pelem);(pelem)=&(elem)->key.sn_next)
#define SLIST_PFOREACH_P(pelem,elem,l,getpath) for((pelem)=&(l);(elem)=*(pelem);(pelem)=&getpath(elem).sn_next)
#define SLIST_INSERT(l,elem,key)             (void)((elem)->key.sn_next = (l),(l) = (elem))
#define SLIST_INSERT_P(l,elem,getpath)       (void)(getpath(elem).sn_next = (l),(l) = (elem))
#define SLIST_INSERT_BEFORE(elem,psuccessor,successor,key) (void)(assert(*(psuccessor)==(successor)),(elem)->key.sn_next=(successor),*(psuccessor)=(elem))
#define SLIST_INSERT_BEFORE_P(elem,psuccessor,successor,getpath) (void)(assert(*(psuccessor)==(successor)),getpath(elem).sn_next=(successor),*(psuccessor)=(elem))
#define SLIST_INSERT_AFTER(predecessor,elem,key) (void)((elem)->key.sn_next=(predecessor)->key.sn_next,(predecessor)->key.sn_next=(elem))
#define SLIST_INSERT_AFTER_P(predecessor,elem,getpath) (void)(getpath(elem).sn_next=getpath(predecessor).sn_next,getpath(predecessor).sn_next=(elem))
#define SLIST_REPLACE(pelem,elem,new_elem,key) (void)(assert(*(pelem)==(elem)),(new_elem)->key.sn_next=(elem)->key.sn_next,*(pelem)=(new_elem))
#define SLIST_REPLACE_P(pelem,elem,new_elem,getpath) (void)(assert(*(pelem)==(elem)),getpath(new_elem).sn_next=getpath(elem).sn_next,*(pelem)=(new_elem))
#define SLIST_REMOVE(pelem,elem,key)         (void)(assert(*(pelem)==(elem)),*(pelem)=(elem)->key.sn_next)
#define SLIST_REMOVE_P(pelem,elem,getpath)   (void)(assert(*(pelem)==(elem)),*(pelem)=getpath(elem).sn_next)

/* LLIST */
#define LLIST(T)                               T *           /* [0..1] List head */
#define LLIST_NODE(T)                 struct { T *ln_next    /* [0..1] Next pointer */, \
                                                **ln_pself;  /* [1..1][?..1] Self pointer (When `NULL', element isn't apart of list) */ }
#define LLIST_INIT                             NULL
#define LLIST_INITNODE                       { NULL, NULL }
#define LLIST_EMPTY(l)                       ((l)==NULL)
#define LLIST_NONEMPTY(l)                    ((l)!=NULL)
#define LLIST_NEXT(elem,key)                 ((elem)->key.ln_next)
#define LLIST_NEXT_P(elem,getpath)           (getpath(elem).ln_next)
#define LLIST_PREV(T,elem,key)                __COMPILER_CONTAINER_OF((elem)->key.ln_pself,T,key.ln_next)
#define LLIST_HASNEXT(elem,key)              ((elem)->key.ln_next!=NULL)
#define LLIST_HASNEXT_P(elem,getpath)        (getpath(elem).ln_next!=NULL)
#define LLIST_HASPREV(l,elem,key)            ((elem)->key.ln_pself!=&(l))
#define LLIST_HASPREV_P(l,elem,getpath)      (getpath(elem).ln_pself!=&(l))
#define LLIST_XNEXT(elem,key)                ((elem)->key.ln_next)
#define LLIST_XNEXT_P(elem,getpath)          (getpath(elem).ln_next)
#define LLIST_XPREV(T,l,elem,key)            (LLIST_HASPREV(l,elem,key) ? LLIST_PREV(T,elem,key) : NULL)
#define LLIST_HEAD(l)                        (l)
#define LLIST_FOREACH(elem,l,key)            for((elem)=(l);(elem);(elem)=(elem)->key.ln_next)
#define LLIST_FOREACH_P(elem,l,getpath)      for((elem)=(l);(elem);(elem)=getpath(elem).ln_next)
#define LLIST_RFOREACH(T,elem,l,start,key)   for((elem)=(start);(elem);(elem)=LLIST_XPREV(T,l,elem,key))
#define LLIST_INSERT(l,elem,key)             (void)(((elem)->key.ln_next=(l))!=NULL ? \
                                             (void)((l)->key.ln_pself=&(elem)->key.ln_next):(void)0, \
                                                    (elem)->key.ln_pself=&(l),(l)=(elem))
#define LLIST_INSERT_P(l,elem,getpath)       (void)((getpath(elem).ln_next=(l))!=NULL ? \
                                             (void)(getpath((l)).ln_pself=&getpath(elem).ln_next):(void)0, \
                                                    getpath(elem).ln_pself=&(l),(l)=(elem))
#define LLIST_INSERT_BEFORE(elem,successor,key) (void)(*((elem)->key.ln_pself=(successor)->key.ln_pself)=(elem), \
                                                       *((successor)->key.ln_pself=&(elem)->key.ln_next)=(successor))
#define LLIST_INSERT_BEFORE_P(elem,successor,getpath) (void)(*(getpath(elem).ln_pself=getpath(successor).ln_pself)=(elem), \
                                                       *(getpath(successor).ln_pself=&getpath(elem).ln_next)=(successor))
#define LLIST_INSERT_AFTER(predecessor,elem,key) (void)(((elem)->key.ln_next=*((elem)->key.ln_pself=&(predecessor)->key.ln_next))!=NULL ? \
                                                  (void)((elem)->key.ln_next->key.ln_pself=&(elem)->key.ln_next) : (void)0)
#define LLIST_INSERT_AFTER_P(predecessor,elem,getpath) (void)((getpath(elem).ln_next=*(getpath(elem).ln_pself=&getpath(predecessor).ln_next))!=NULL ? \
                                                        (void)(getpath(getpath(elem).ln_next).ln_pself=&getpath(elem).ln_next) : (void)0)
#define LLIST_REPLACE(elem,new_elem,key)     (void)(*((new_elem)->key.ln_pself=(elem)->key.ln_pself)=(new_elem), \
                                                     ((new_elem)->key.ln_next=(elem)->key.ln_next)!=NULL ? \
                                               (void)((new_elem)->key.ln_next->key.ln_pself=&(new_elem)->key.ln_next) : (void)0)
#define LLIST_REPLACE_P(elem,new_elem,getpath) (void)(*(getpath(new_elem).ln_pself=getpath(elem).ln_pself)=(new_elem), \
                                                       (getpath(new_elem).ln_next=getpath(elem).ln_next)!=NULL ? \
                                               (void)(getpath(getpath(new_elem).ln_next).ln_pself=&getpath(new_elem).ln_next) : (void)0)
#define LLIST_REMOVE(elem,key)               ((*(elem)->key.ln_pself=(elem)->key.ln_next)!=NULL ? \
                                                (void)((elem)->key.ln_next->key.ln_pself=(elem)->key.ln_pself) : (void)0)
#define LLIST_REMOVE_P(elem,getpath)         ((*getpath(elem).ln_pself=getpath(elem).ln_next)!=NULL ? \
                                                (void)(getpath(getpath(elem).ln_next).ln_pself=getpath(elem).ln_pself) : (void)0)
#define LLIST_UNBIND(elem,key)               (void)((elem)->key.ln_pself=NULL)
#define LLIST_UNBIND_P(elem,getpath)         (void)(getpath(elem).ln_pself=NULL)
#define LLIST_ISBOUND(elem,key)                    ((elem)->key.ln_pself!=NULL)
#define LLIST_ISBOUND_P(elem,getpath)              (getpath(elem).ln_pself!=NULL)
#define LLIST_UNLINK(elem,key)               (LLIST_REMOVE(elem,key),LLIST_UNBIND(elem,key))
#define LLIST_UNLINK_P(elem,getpath)         (LLIST_REMOVE_P(elem,getpath),LLIST_UNBIND_P(elem,getpath))




/* DLIST */
#define DLIST(T)                      struct { T *dl_head;   /* [0..1] List head */ \
                                               T *dl_tail;   /* [0..1][(!= NULL) == (dl_head != NULL)] List tail */ }
#define DLIST_NODE(T)                 struct { T **dn_pnext  /* [1..1][?..1] Self pointer in next */, \
                                                 **dn_pprev  /* [1..1][?..1] Self pointer in previous */, \
                                                  *dn_next   /* [0..1] Next node */, \
                                                  *dn_prev;  /* [0..1] Previous node */ }
#define DLIST_INIT                       { NULL, NULL }
#define DLIST_INITNODE                   { NULL, NULL, NULL, NULL }
#define DLIST_EMPTY(l)                   ((l).dl_head==NULL)
#define DLIST_NONEMPTY(l)                ((l).dl_head!=NULL)
#define DLIST_PREV(elem,key)             ((elem)->key.dn_prev)
#define DLIST_PREV_P(elem,getpath)       (getpath(elem).dn_prev)
#define DLIST_NEXT(elem,key)             ((elem)->key.dn_next)
#define DLIST_NEXT_P(elem,getpath)       (getpath(elem).dn_next)
#define DLIST_HASPREV(elem,key)          ((elem)->key.dn_prev!=NULL)
#define DLIST_HASPREV_P(elem,getpath)    (getpath(elem).dn_prev!=NULL)
#define DLIST_HASNEXT(elem,key)          ((elem)->key.dn_next!=NULL)
#define DLIST_HASNEXT_P(elem,getpath)    (getpath(elem).dn_next!=NULL)
#define DLIST_XPREV(elem,key)            ((elem)->key.dn_prev)
#define DLIST_XPREV_P(elem,getpath)      (getpath(elem).dn_prev)
#define DLIST_XNEXT(elem,key)            ((elem)->key.dn_next)
#define DLIST_XNEXT_P(elem,getpath)      (getpath(elem).dn_next)
#define DLIST_HEAD(l)                    ((l).dl_head)
#define DLIST_BACK(l)                    ((l).dl_tail)
#define DLIST_FOREACH(elem,l,key)        for((elem)=(l).dl_head;(elem);(elem)=(elem)->key.dn_next)
#define DLIST_FOREACH_P(elem,l,getpath)  for((elem)=(l).dl_head;(elem);(elem)=getpath(elem).dn_next)
#define DLIST_RFOREACH(elem,l,key)       for((elem)=(l).dl_tail;(elem);(elem)=(elem)->key.dn_prev)
#define DLIST_RFOREACH_P(elem,l,getpath) for((elem)=(l).dl_tail;(elem);(elem)=getpath(elem).dn_prev)
#define DLIST_INSERT(l,elem,key)         (void)(((elem)->key.dn_next=*((elem)->key.dn_pprev=&(l).dl_head))!=NULL ? \
                                         (void)(*((elem)->key.dn_pnext=&(l).dl_head->key.dn_prev)=(elem), \
                                                  (l).dl_head->key.dn_pprev=&(elem)->key.dn_next) : \
                                         (void)(*((elem)->key.dn_pnext=&(l).dl_tail)=(elem)), \
                                                  (l).dl_head=(elem),(elem)->key.dn_prev=NULL)
#define DLIST_INSERT_P(l,elem,getpath)   (void)((getpath(elem).dn_next=*(getpath(elem).dn_pprev=&(l).dl_head))!=NULL ? \
                                         (void)(*(getpath(elem).dn_pnext=&getpath((l).dl_head).dn_prev)=(elem), \
                                                  getpath((l).dl_head).dn_pprev=&getpath(elem).dn_next) : \
                                         (void)(*(getpath(elem).dn_pnext=&(l).dl_tail)=(elem)), \
                                                  (l).dl_head=(elem),getpath(elem).dn_prev=NULL)
#define DLIST_INSERT_BACK(l,elem,key)    (void)(((elem)->key.dn_prev=*((elem)->key.dn_pnext=&(l).dl_tail))!=NULL ? \
                                         (void)(*((elem)->key.dn_pprev=&(l).dl_tail->key.dn_next)=(elem), \
                                                  (l).dl_tail->key.dn_pnext=&(elem)->key.dn_prev) : \
                                         (void)(*((elem)->key.dn_pprev=&(l).dl_head)=(elem)), \
                                                  (l).dl_tail=(elem),(elem)->key.dn_next=NULL)
#define DLIST_INSERT_BACK_P(l,elem,getpath) (void)((getpath(elem).dn_prev=*(getpath(elem).dn_pnext=&(l).dl_tail))!=NULL ? \
                                            (void)(*(getpath(elem).dn_pprev=&getpath((l).dl_tail).dn_next)=(elem), \
                                                     getpath((l).dl_tail).dn_pnext=&getpath(elem).dn_prev) : \
                                            (void)(*(getpath(elem).dn_pprev=&(l).dl_head)=(elem)), \
                                                     (l).dl_tail=(elem),getpath(elem).dn_next=NULL)
#define DLIST_INSERT_BEFORE(elem,successor,key) (void)((elem)->key.dn_prev=(successor)->key.dn_prev, \
                                                     *((elem)->key.dn_pprev=(successor)->key.dn_pprev)=(elem), \
                                                       (elem)->key.dn_next=(successor), \
                                                       (successor)->key.dn_pprev = &(elem)->key.dn_next, \
                                                     *((elem)->key.dn_pnext=&(successor)->key.dn_prev)=(elem))
#define DLIST_INSERT_BEFORE_P(elem,successor,getpath) (void)(getpath(elem).dn_prev=getpath(successor).dn_prev, \
                                                           *(getpath(elem).dn_pprev=getpath(successor).dn_pprev)=(elem), \
                                                             getpath(elem).dn_next=(successor), \
                                                             getpath(successor).dn_pprev = &getpath(elem).dn_next, \
                                                           *(getpath(elem).dn_pnext=&getpath(successor).dn_prev)=(elem))
#define DLIST_INSERT_AFTER(predecessor,elem,key) (void)((elem)->key.dn_next=(predecessor)->key.dn_next, \
                                                      *((elem)->key.dn_pnext=(predecessor)->key.dn_pnext)=(elem), \
                                                        (elem)->key.dn_prev=(predecessor), \
                                                        (predecessor)->key.dn_pnext = &(elem)->key.dn_prev, \
                                                      *((elem)->key.dn_pprev=&(predecessor)->key.dn_next)=(elem))
#define DLIST_INSERT_AFTER_P(predecessor,elem,getpath) (void)(getpath(elem).dn_next=getpath(predecessor).dn_next, \
                                                            *(getpath(elem).dn_pnext=getpath(predecessor).dn_pnext)=(elem), \
                                                              getpath(elem).dn_prev=(predecessor), \
                                                              getpath(predecessor).dn_pnext = &getpath(elem).dn_prev, \
                                                            *(getpath(elem).dn_pprev=&getpath(predecessor).dn_next)=(elem))
#define DLIST_REPLACE(elem,new_elem,key) (void)(*((new_elem)->key.dn_pnext=(elem)->key.dn_pnext) = (new_elem), \
                                                *((new_elem)->key.dn_pprev=(elem)->key.dn_pprev) = (new_elem), \
                                                 ((new_elem)->key.dn_next=(elem)->key.dn_next)!=NULL ? (void)((new_elem)->key.dn_next->key.dn_pprev = &(new_elem)->key.dn_next): (void)0, \
                                                 ((new_elem)->key.dn_prev=(elem)->key.dn_prev)!=NULL ? (void)((new_elem)->key.dn_prev->key.dn_pnext = &(new_elem)->key.dn_prev): (void)0)
#define DLIST_REPLACE_P(elem,new_elem,getpath) (void)(*(getpath(new_elem).dn_pnext=getpath(elem).dn_pnext) = (new_elem), \
                                                      *(getpath(new_elem).dn_pprev=getpath(elem).dn_pprev) = (new_elem), \
                                                       (getpath(new_elem).dn_next=getpath(elem).dn_next)!=NULL ? (void)(getpath(getpath(new_elem).dn_next).dn_pprev = &getpath(new_elem).dn_next): (void)0, \
                                                       (getpath(new_elem).dn_prev=getpath(elem).dn_prev)!=NULL ? (void)(getpath(getpath(new_elem).dn_prev).dn_pnext = &getpath(new_elem).dn_prev): (void)0)
#define DLIST_REMOVE(elem,key)           ((*(elem)->key.dn_pnext=(elem)->key.dn_prev)!=NULL ? (void)((elem)->key.dn_prev->key.dn_pnext = (elem)->key.dn_pnext) : (void)0, \
                                          (*(elem)->key.dn_pprev=(elem)->key.dn_next)!=NULL ? (void)((elem)->key.dn_next->key.dn_pprev = (elem)->key.dn_pprev) : (void)0)
#define DLIST_REMOVE_P(elem,getpath)     ((*getpath(elem).dn_pnext=getpath(elem).dn_prev)!=NULL ? (void)(getpath(getpath(elem).dn_prev).dn_pnext = getpath(elem).dn_pnext) : (void)0, \
                                          (*getpath(elem).dn_pprev=getpath(elem).dn_next)!=NULL ? (void)(getpath(getpath(elem).dn_next).dn_pprev = getpath(elem).dn_pprev) : (void)0)
#define DLIST_UNBIND(elem,key)           ((elem)->key.dn_pprev=NULL)
#define DLIST_UNBIND_P(elem,getpath)     (getpath(elem).dn_pprev=NULL)
#define DLIST_ISBOUND(elem,key)          ((elem)->key.dn_pprev!=NULL)
#define DLIST_ISBOUND_P(elem,getpath)    (getpath(elem).dn_pprev!=NULL)
#define DLIST_UNLINK(elem,key)           (DLIST_REMOVE(elem,key),DLIST_UNBIND(elem,key))
#define DLIST_UNLINK_P(elem,getpath)     (DLIST_REMOVE_P(elem,getpath),DLIST_UNBIND_P(elem,getpath))


__DECL_END
#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_SEQUENCE_LIST_H */
