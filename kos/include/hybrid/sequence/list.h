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
#ifndef __GUARD_HYBRID_SEQUENCE_LIST_H
#define __GUARD_HYBRID_SEQUENCE_LIST_H 1

#include "../../__stdinc.h"
#ifdef __CC__
#ifndef __HYBRID_LIST_RESTRICT_API
#include "../__atomic.h"
#include "../pp/__va_nargs.h"
#endif /* !__HYBRID_LIST_RESTRICT_API */

#if defined(NDEBUG) || defined(NDEBUG_QUEUE)
#define __HYBRID_Q_ASSERT_(expr) /* nothing */
#else /* NDEBUG || NDEBUG_QUEUE */
#include "../__assert.h"
#define __HYBRID_Q_ASSERT_(expr) __hybrid_assert(expr),
#endif /* !NDEBUG && !NDEBUG_QUEUE */

/*
 * General purpose macros to defining various types of intrusive linked lists.
 * NOTE: On KOS, this header is also used to implement <sys/queue.h>, with all
 *       macros from  `__HYBRID_LIST_RESTRICT_API' only  getting exposed  when
 *       `_KOS_SOURCE' is enabled. Functions not restricted to this  extension
 *       namespace are those  declared by the  union of <sys/queue.h>  headers
 *       found in NetBSD, OpenBSD, OpenSolaris, uClibc, GLibC, and libbsd.
 *       iow: Any macro provided by any of these systems is always defined as
 *            far as possible!)
 *
 *  +--------------- LIST_*:     Single-head, doubly-linked list (via element self-pointers)
 *  | +------------- SLIST_*:    Single-head, singly-linked list
 *  | | +----------- STAILQ_*:   Double-head, singly-linked tail queue. (same as "Simple queue" (SIMPLEQ_*))
 *  | | | +--------- TAILQ_*:    Double-head, doubly-linked tail queue.
 *  | | | | +------- CIRCLEQ_*:  Circular queue
 *  | | | | | +----- RINGQ_*:    Ring queue (KOS extension)
 *  | | | | | | +--- DLIST_*:    Single-head, doubly-linked list (with direct prev-pointer; completely
 *  | | | | | | |                inferior to LIST_*, so don't use except when needed for binary compat!
 *  | | | | | | |                Also can't be made to support the bound-elem API, either...))
 *  | | | | | | | +- XSIMPLEQ_*: TODO
 *  | | | | | | | |
 * [===============]
 * [1 1 2 2 2   1  ]  -- Pointers per *_HEAD([name], type) aka. *_HEAD_P(T)
 * [2 1 1 2 2 2 2  ]  -- Pointers per *_ENTRY(type)        aka. *_ENTRY_P(T)
 * [===============]
 * [1 1 1 1 1   1  ]  CODE [*]_HEAD_INITIALIZER(self)
 * [---------------]
 * [1 1 1 1 1   1  ]  void [*]_INIT(self)
 * [          1    ]  void [*]_INIT(elem, key)
 * [---------------]
 * [  1 1       1  ]  void [*]_MOVE(dst, src)                                 (C++-style move-constructor)
 * [1     1 1      ]  void [*]_MOVE(dst, src, key)                            (C++-style move-constructor)
 * [---------------]
 * [  1 1       1  ]  void [*]_SWAP(l1, l2, [type])                           (C++-style std::swap())
 * [1     1 1      ]  void [*]_SWAP(l1, l2, [type], key)                      (C++-style std::swap())
 * [---------------]
 * [1 1 1 1 1   1  ]  void [*]_CLEAR(self)
 * [---------------]
 * [    1          ]  void [*]_CONCAT(dst, src)
 * [      1 1      ]  void [*]_CONCAT(dst, src, key)
 * [N N         N  ]  void [*]_CONCAT(dst, src, [type], key)
 * [---------------]
 * [1 1 1 1 1   1  ]  PTR  [*]_END(self)                                      (Pointer to 1 past the last elem; NULL-pointer, since all of these are linked lists)
 * [---------------]
 * [1 1 1 1 1   1  ]  bool [*]_EMPTY(self)
 * [---------------]
 * [1 1 1 1 1   1  ]  T*   [*]_FIRST(self)
 * [1 1 1          ]  T**  [*]_PFIRST(self)                                   (Return pointer to the pointer to the first item; use with *_P_* functions)
 * [---------------]
 * [      1 1      ]  T*   [*]_LAST(self)
 * [    1          ]  T*   [*]_LAST(self, [type], key)
 * [      1        ]  T*   [*]_LAST_FAST(self, [type], key)
 * [---------------]
 * [1 1 1 1 1 1 1  ]  T*   [*]_NEXT(elem, key)                                (Return successor (NULL if no prev-elem exists))
 * [1 1 1          ]  T**  [*]_PNEXT(elem, key)                               (Return pointer to the pointer to the next item; use with *_P_* functions)
 * [        1      ]  T*   [*]_LOOP_NEXT(self, elem, key)                     (NOTE: *_NEXT(elem, key) for RINGQ)
 * [---------------]
 * [        1 1 1  ]  T*   [*]_PREV(elem, key)                                (Return predecessor (NULL if no prev-elem exists))
 * [1              ]  T*   [*]_PREV(elem, self, [type], key)                  (Return predecessor (NULL if no prev-elem exists))
 * [      1        ]  T*   [*]_PREV(elem, [headname], key)                    (Return predecessor (NULL if no prev-elem exists))
 * [      1        ]  T*   [*]_PREV_FAST(elem, self, [type], key)             (Return predecessor (NULL if no prev-elem exists))
 * [1              ]  T*   [*]_PREV_UNSAFE(elem, self, [type], key)           (Return predecessor (undef if no prev-elem exists))
 * [        1      ]  T*   [*]_LOOP_PREV(self, elem, key)                     (NOTE: *_PREV(elem, key) for RINGQ)
 * [---------------]
 * [N              ]  void [*]_COUNT(self, [presult], [type], key)  # TODO: Implement for all sequence types
 * [---------------]
 * [1 1 1     1 1  ]  void [*]_INSERT_AFTER(predecessor, elem, key)
 * [      1 1      ]  void [*]_INSERT_AFTER(self, predecessor, elem, key)
 * [1 1 1     1 1  ]  void [*]_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, key)      { ..., predecessor, lo_elem...hi_elem, predecessor.next, ... }
 * [---------------]
 * [1     1   1    ]  void [*]_INSERT_BEFORE(successor, elem, key)
 * [        1   1  ]  void [*]_INSERT_BEFORE(self, successor, elem, key)
 * [1     1   1    ]  void [*]_INSERT_BEFORE_R(successor, lo_elem, hi_elem, key)       { ..., successor.prev, lo_elem...hi_elem, successor, ... }
 * [        1   1  ]  void [*]_INSERT_BEFORE_R(self, successor, lo_elem, hi_elem, key)
 * [---------------]
 * [1 1 1 1 1   1  ]  void [*]_INSERT[_HEAD](self, elem, key)
 * [1 1 1 1 1   1  ]  void [*]_INSERT[_HEAD]_R(self, lo_elem, hi_elem, key)
 * [---------------]
 * [    1 1 1      ]  void [*]_INSERT_TAIL(self, elem, key)
 * [N N         N  ]  void [*]_INSERT_TAIL(self, elem, [type], key)
 * [    1 1 1      ]  void [*]_INSERT_TAIL_R(self, lo_elem, hi_elem, key)
 * [N N         N  ]  void [*]_INSERT_TAIL_R(self, lo_elem, hi_elem, [type], key)
 * [---------------]
 * [1 1 1 1 1   1  ]  void [*]_REMOVE_HEAD(self, key)
 * [1         1    ]  void [*]_REMOVE(elem, key)
 * [      1 1   1  ]  void [*]_REMOVE(self, elem, key)
 * [  N N          ]  void [*]_REMOVE(self, elem, [type], key)
 * [1         1    ]  void [*]_REMOVE_R(lo_elem, hi_elem, key)                (Remove all elements `lo_elem...hi_elem' inclusively; links between removed elements remain valid)
 * [      1 1   1  ]  void [*]_REMOVE_R(self, lo_elem, hi_elem, key)
 * [1 1         1  ]  void [*]_REMOVE_AFTER(elem, key)                        (Remove successor of `elem'; undef if no successor)
 * [    1 1 1      ]  void [*]_REMOVE_AFTER(self, elem, key)
 * [  1            ]  void [*]_REMOVE_PREVPTR(p_elem, elem, key)              (libbsd-specific; for use with `SLIST_FOREACH_PREVPTR()')
 * [---------------]
 * [N N N N N   N  ]  void [*]_REMOVE_IF(self, out_pelem, [type], key, condition)
 * |               |             NOTE: `*out_pelem' is written to before `condition' is
 * |               |                   evaluated to test if `*out_pelem' should be removed
 * |               |             Assumes that `condition' is true for at least 1 element.
 * [  N N          ]  void [*]_TRYREMOVE(self, elem, [type], key, on_failure)
 * [N N N N N   N  ]  void [*]_TRYREMOVE_IF(self, out_pelem, [type], key, condition, on_failure)
 * |               |             Same as *_REMOVE_IF, but allow `condition' to be false for all elements, or
 * |               |             the list itself to be empty. (if this happens, `on_failure' is evaluated)
 * [N N N N N   N  ]  void [*]_REMOVEALL(self, out_pelem, [type], key, condition, on_match)
 * |               |             Remove all elements for which `condition' is true, and evaluate `on_match'
 * |               |             every time such a match is confirmed. The associated element is `*out_pelem'
 * [---------------]
 * [  N N          ]  void [*]_CONTAINS(self, elem, [type], key, on_success)
 * [---------------]
 * [1         1    ]  void [*]_REPLACE(old_elem, new_elem, key)
 * [            1  ]  void [*]_REPLACE(self, old_elem, new_elem, key)
 * [  N N 1 1      ]  void [*]_REPLACE(self, old_elem, new_elem, [type], key)
 * [1         1    ]  void [*]_REPLACE_R(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)
 * [            1  ]  void [*]_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)
 * [  N N 1 1      ]  void [*]_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key)
 * [  N N          ]  void [*]_TRYREPLACE(self, old_elem, new_elem, [type], key, on_failure)
 * [  N N          ]  void [*]_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key, on_failure)
 * [---------------]
 * [N N N N N   N  ]  CODE [*]_FOREACH(elem, self, key)
 * [N N N N N   N  ]  CODE [*]_FOREACH_FROM(elem, self, key)                  (If non-NULL, start enumeration with `IN(elem)'; else start w/ `[*]_FIRST(self)')
 * [N N N N N   N  ]  CODE [*]_FOREACH_SAFE(elem, self, key, [tvar])          (Same as [*]_FOREACH, but the loop body may safely remove `elem')
 * [N N N N N   N  ]  CODE [*]_FOREACH_FROM_SAFE(elem, self, key, [tvar])     (Same as [*]_FOREACH_FROM, but the loop body may safely remove `elem')
 * [        N      ]  CODE [*]_FOREACH_REVERSE(elem, self, key)
 * [        N      ]  CODE [*]_FOREACH_REVERSE_FROM(elem, self, key)
 * [      N        ]  CODE [*]_FOREACH_REVERSE(elem, self, [headname], key)
 * [      N        ]  CODE [*]_FOREACH_REVERSE_FROM(elem, self, [headname], key)
 * [      N        ]  CODE [*]_FOREACH_REVERSE_SAFE(elem, self, [headname], key, [tvar])
 * [      N        ]  CODE [*]_FOREACH_REVERSE_FROM_SAFE(elem, self, [headname], key, [tvar])
 * [  N            ]  CODE [*]_FOREACH_PREVPTR(elem, p_elem, self, key)
 * [===============]
 * [===============]  -- Sub-API: Atomic operations
 * [  1            ]  void [*]_ATOMIC_INSERT(self, elem, key)
 * [  1            ]  void [*]_ATOMIC_INSERT_R(self, lo_elem, hi_elem, key)
 * [  1            ]  T*   [*]_ATOMIC_CLEAR(self)
 * [===============]
 * [===============]  -- Sub-API: Pointer-to-element (allows for a number of otherwise impossible O(1) operations)
 * [1 1 1          ]  T*   [*]_P_PREV(p_elem, self, [type], key)              (Return predecessor (NULL if no prev-elem exists))
 * [1 1 1          ]  T*   [*]_P_PREV_UNSAFE(p_elem, [type], key)             (Return predecessor (undef if no prev-elem exists))
 * [---------------]
 * [1 1            ]  void [*]_P_INSERT_BEFORE(p_successor, elem, key)
 * [1 1            ]  void [*]_P_INSERT_BEFORE_R(p_successor, lo_elem, hi_elem, key)   { ..., (*p_successor).prev, lo_elem...hi_elem, (*p_successor), ... }
 * [---------------]
 * [1 1            ]  void [*]_P_REMOVE(p_elem, key)
 * [    1          ]  void [*]_P_REMOVE(self, p_elem, key)
 * [1 1            ]  void [*]_P_REMOVE_R(p_lo_elem, hi_elem, key)
 * [    1          ]  void [*]_P_REMOVE_R(self, p_lo_elem, hi_elem, key)
 * [---------------]
 * [1 1            ]  void [*]_P_REPLACE(p_old_elem, new_elem, key)
 * [    1          ]  void [*]_P_REPLACE(self, p_old_elem, new_elem, key)
 * [1 1            ]  void [*]_P_REPLACE_R(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)
 * [    1          ]  void [*]_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)
 * [---------------]
 * [N N N          ]  CODE [*]_P_FOREACH(p_elem, self, key)
 * [===============]
 * [===============]  -- Sub-API: Check if an element is contained within a list, but removal requires *_UNBIND instead of *_REMOVE
 * [1     1 1 1    ]  CODE [*]_ENTRY_UNBOUND_INITIALIZER         -- Static initializer for unbound elements
 * [1     1 1 1    ]  void [*]_ENTRY_UNBOUND_INIT(entry)         -- Runtime initializer for unbound elements
 * [1     1 1 1    ]  bool [*]_ISBOUND(elem, key)                -- Returns non-zero if element is bound (to a list)
 * [1         1    ]  void [*]_UNBIND(elem, key)                 -- Remove element and mark as unbound
 * [      1 1      ]  void [*]_UNBIND(self, elem, key)           -- *ditto*
 * [N     N N      ]  void [*]_UNBIND_IF(self, out_pelem, [type], key, condition)
 * [N     N N      ]  void [*]_TRYUNBIND_IF(self, out_pelem, [type], key, condition, on_failure)
 * [N     N N      ]  void [*]_UNBINDALL(self, out_pelem, [type], key, condition, on_match)
 * \---------------/
 *      Runtime
 *     (in O(x))
 *
 * NOTE: [foo]-arguments are optional and may be omitted when `__HYBRID_LIST_RESTRICT_API'
 *       is   disabled,   and  sufficient   compiler/preprocessor-support   is  available. */


#define __HYBRID_Q_KEY(key, item)     (item)->key
#define __HYBRID_Q_PTH(getpath, item) getpath(item)
#undef __HYBRID_Q_BADPTR
#if defined(NDEBUG) || defined(NDEBUG_QUEUE)
#define __HYBRID_Q_BADPTR(field) (void)0
#else /* NDEBUG || NDEBUG_QUEUE */
#include "../typecore.h"
#if __SIZEOF_POINTER__ == 4
#define __HYBRID_Q_BADPTR(field) (void)(*(void **)&(field) = (void *)__UINT32_C(0xcccccccc))
#elif __SIZEOF_POINTER__ == 8
#define __HYBRID_Q_BADPTR(field) (void)(*(void **)&(field) = (void *)__UINT64_C(0xcccccccccccccccc))
#elif __SIZEOF_POINTER__ == 2
#define __HYBRID_Q_BADPTR(field) (void)(*(void **)&(field) = (void *)__UINT16_C(0xcccc))
#elif __SIZEOF_POINTER__ == 1
#define __HYBRID_Q_BADPTR(field) (void)(*(void **)&(field) = (void *)__UINT8_C(0xcc))
#elif defined(__KOS_SYSTEM_HEADERS__)
#include <libc/string.h>
#define __HYBRID_Q_BADPTR(field) (void)__libc_memset(&(field), 0xcc, __SIZEOF_POINTER__)
#else /* __SIZEOF_POINTER__ == ... */
#define __HYBRID_Q_BADPTR(field) (void)0
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* !NDEBUG && !NDEBUG_QUEUE */
#if defined(__cplusplus) && !defined(__HYBRID_LIST_RESTRICT_API)
#undef __HYBRID_Q_STRUCT
#undef __HYBRID_Q_CLASS
#define __HYBRID_Q_STRUCT /* nothing */
#define __HYBRID_Q_CLASS  /* nothing */
#else /* __cplusplus && !__HYBRID_LIST_RESTRICT_API */
#define __HYBRID_Q_STRUCT struct
#define __HYBRID_Q_CLASS  class
#endif /* !__cplusplus || __HYBRID_LIST_RESTRICT_API */





/************************************************************************/
/* LIST: Single-head, doubly-linked list (via element self-pointers)    */
/************************************************************************/
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_LIST_HEAD_1(type)             struct      { __HYBRID_Q_STRUCT type *lh_first; /* [0..1] List head */ }
#define __HYBRID_LIST_HEAD_2(name, type)       struct name { __HYBRID_Q_STRUCT type *lh_first; /* [0..1] List head */ }
#define __HYBRID_LIST_CLASS_HEAD_1(type)       struct      { __HYBRID_Q_CLASS  type *lh_first; /* [0..1] List head */ }
#define __HYBRID_LIST_CLASS_HEAD_2(name, type) struct name { __HYBRID_Q_CLASS  type *lh_first; /* [0..1] List head */ }
#undef LIST_HEAD
#undef LIST_CLASS_HEAD
#define LIST_HEAD(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_HEAD_, (__VA_ARGS__))(__VA_ARGS__)       /* LIST_HEAD([name], type) */
#define LIST_CLASS_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_CLASS_HEAD_, (__VA_ARGS__))(__VA_ARGS__) /* LIST_CLASS_HEAD([name], type) */
#else /* !__HYBRID_LIST_RESTRICT_API && __HYBRID_PP_VA_OVERLOAD */
#define LIST_HEAD(name, type)       struct name { __HYBRID_Q_STRUCT type *lh_first; /* [0..1] List head */ }
#define LIST_CLASS_HEAD(name, type) struct name { __HYBRID_Q_CLASS  type *lh_first; /* [0..1] List head */ }
#endif /* __HYBRID_LIST_RESTRICT_API || !__HYBRID_PP_VA_OVERLOAD */
#define LIST_ENTRY(type)                                                             \
	struct {                                                                         \
		__HYBRID_Q_STRUCT type *le_next, /* [0..1] Next item */                      \
		**le_prev;                       /* [1..1][1..1] This item's self-pointer */ \
	}
#define LIST_CLASS_ENTRY(type)                                                       \
	struct {                                                                         \
		__HYBRID_Q_STRUCT type *le_next, /* [0..1] Next item */                      \
		**le_prev;                       /* [1..1][1..1] This item's self-pointer */ \
	}
#define LIST_EMPTY(self)                          ((self)->lh_first == __NULLPTR)
#define LIST_END(self)                            __NULLPTR
#define LIST_FOREACH(elem, self, key)             __HYBRID_LIST_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define LIST_FOREACH_FROM(elem, self, key)        __HYBRID_LIST_FOREACH_FROM(elem, self, __HYBRID_Q_KEY, key)
#define LIST_HEAD_INITIALIZER(self)               { __NULLPTR }
#define LIST_INIT(self)                           (void)((self)->lh_first = __NULLPTR)
#define LIST_INSERT_AFTER(predecessor, elem, key) __HYBRID_LIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_KEY, key)
#define LIST_INSERT_BEFORE(successor, elem, key)  __HYBRID_LIST_INSERT_BEFORE(successor, elem, __HYBRID_Q_KEY, key)
#define LIST_INSERT_HEAD(self, elem, key)         __HYBRID_LIST_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define LIST_MOVE(dst, src, key)                  __HYBRID_LIST_MOVE(dst, src, __HYBRID_Q_KEY, key)
#define LIST_NEXT(elem, key)                      (elem)->key.le_next
#define LIST_REMOVE(elem, key)                    __HYBRID_LIST_REMOVE(elem, __HYBRID_Q_KEY, key)
#if defined(__INTELLISENSE__) && defined(__COMPILER_HAVE_TYPEOF) /* Prevent code like `&LIST_FIRST()' (use `LIST_PFIRST()' instead) */
#define LIST_FIRST(self)                          ((__typeof__((self)->lh_first))(self)->lh_first)
#else /* __INTELLISENSE__ && __COMPILER_HAVE_TYPEOF */
#define LIST_FIRST(self)                          (self)->lh_first
#endif /* !__INTELLISENSE__ || !__COMPILER_HAVE_TYPEOF */
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_LIST_CONCAT_3(dst, src, key)                    __HYBRID_LIST_CONCAT(dst, src, __typeof__(*(src)->lh_first), __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_CONCAT_4(dst, src, type, key)              __HYBRID_LIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_FOREACH_FROM_SAFE_3(elem, self, key)       __HYBRID_LIST_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_FOREACH_FROM_SAFE_4(elem, self, key, tvar) __HYBRID_LIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_LIST_FOREACH_SAFE_3(elem, self, key)            __HYBRID_LIST_FOREACH_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_FOREACH_SAFE_4(elem, self, key, tvar)      __HYBRID_LIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_LIST_SWAP_3(l1, l2, key)                        __HYBRID_LIST_SWAP(l1, l2, __typeof__(*(l2)->lh_first), __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_SWAP_4(l1, l2, type, key)                  __HYBRID_LIST_SWAP(l1, l2, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#undef LIST_CONCAT
#undef LIST_FOREACH_FROM_SAFE
#undef LIST_FOREACH_SAFE
#undef LIST_SWAP
#define LIST_CONCAT(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_CONCAT_, (__VA_ARGS__))(__VA_ARGS__)            /* LIST_CONCAT(dst, src, [type], key) */
#define LIST_FOREACH_FROM_SAFE(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_FOREACH_FROM_SAFE_, (__VA_ARGS__))(__VA_ARGS__) /* LIST_FOREACH_FROM_SAFE(elem, self, key, [tvar]) */
#define LIST_FOREACH_SAFE(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_FOREACH_SAFE_, (__VA_ARGS__))(__VA_ARGS__)      /* LIST_FOREACH_SAFE(elem, self, key, [tvar]) */
#define LIST_SWAP(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_SWAP_, (__VA_ARGS__))(__VA_ARGS__)              /* LIST_SWAP(l1, l2, [type], key) */
#else /* ... */
#define LIST_CONCAT(dst, src, type, key)              __HYBRID_LIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define LIST_FOREACH_FROM_SAFE(elem, self, key, tvar) __HYBRID_LIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define LIST_FOREACH_SAFE(elem, self, key, tvar)      __HYBRID_LIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define LIST_SWAP(l1, l2, type, key)                  __HYBRID_LIST_SWAP(l1, l2, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#endif /* !... */
#ifndef __HYBRID_LIST_RESTRICT_API
#define LIST_HEAD_P(T) struct { T *lh_first; /* [0..1] List head */ }
#define LIST_ENTRY_P(T)                                   \
	struct {                                              \
		T *le_next, /* [0..1] Next item */                \
		**le_prev;  /* [1..1] This item's self-pointer */ \
	}
#define LIST_CLEAR(self)                                                                  (void)((self)->lh_first = __NULLPTR)
#define LIST_ENTRY_UNBOUND_INIT(entry)                                                    (void)(__HYBRID_Q_BADPTR((entry)->le_next), (entry)->le_prev = __NULLPTR)
#define LIST_ENTRY_UNBOUND_INITIALIZER                                                    { __NULLPTR, __NULLPTR }
#define LIST_ENTRY_UNBOUND_INITIALIZER_IS_ZERO
#define LIST_FOREACH_FROM_P(elem, self, getpath)                                          __HYBRID_LIST_FOREACH_FROM(elem, self, __HYBRID_Q_PTH, getpath)
#define LIST_FOREACH_P(elem, self, getpath)                                               __HYBRID_LIST_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define LIST_INSERT_AFTER_P(predecessor, elem, getpath)                                   __HYBRID_LIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_PTH, getpath)
#define LIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, key)                           __HYBRID_LIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define LIST_INSERT_AFTER_R_P(predecessor, lo_elem, hi_elem, getpath)                     __HYBRID_LIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define LIST_INSERT_BEFORE_P(successor, elem, getpath)                                    __HYBRID_LIST_INSERT_BEFORE(successor, elem, __HYBRID_Q_PTH, getpath)
#define LIST_INSERT_BEFORE_R(successor, lo_elem, hi_elem, key)                            __HYBRID_LIST_INSERT_BEFORE_R(successor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define LIST_INSERT_BEFORE_R_P(successor, lo_elem, hi_elem, getpath)                      __HYBRID_LIST_INSERT_BEFORE_R(successor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define LIST_INSERT_HEAD_P(self, elem, getpath)                                           __HYBRID_LIST_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define LIST_INSERT_HEAD_R(self, lo_elem, hi_elem, getpath)                               __HYBRID_LIST_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define LIST_INSERT_HEAD_R_P(self, lo_elem, hi_elem, getpath)                             __HYBRID_LIST_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define LIST_ISBOUND(elem, key)                                                           ((elem)->key.le_prev != __NULLPTR)
#define LIST_ISBOUND_P(elem, getpath)                                                     (getpath(elem).le_prev != __NULLPTR)
#define LIST_MOVE_P(dst, src, getpath)                                                    __HYBRID_LIST_MOVE(dst, src, __HYBRID_Q_PTH, getpath)
#define LIST_NEXT_P(elem, getpath)                                                        getpath(elem).le_next
#define LIST_PFIRST(self)                                                                 (&(self)->lh_first)
#define LIST_P_FOREACH(p_elem, self, key)                                                 __HYBRID_LIST_P_FOREACH(p_elem, self, __HYBRID_Q_KEY, key)
#define LIST_P_FOREACH_P(p_elem, self, getpath)                                           __HYBRID_LIST_P_FOREACH(p_elem, self, __HYBRID_Q_PTH, getpath)
#define LIST_P_INSERT_BEFORE(p_successor, elem, key)                                      __HYBRID_LIST_P_INSERT_BEFORE(p_successor, elem, __HYBRID_Q_KEY, key)
#define LIST_P_INSERT_BEFORE_P(p_successor, elem, getpath)                                __HYBRID_LIST_P_INSERT_BEFORE(p_successor, elem, __HYBRID_Q_PTH, getpath)
#define LIST_P_INSERT_BEFORE_R(p_successor, lo_elem, hi_elem, key)                        __HYBRID_LIST_P_INSERT_BEFORE_R(p_successor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define LIST_P_INSERT_BEFORE_R_P(p_successor, lo_elem, hi_elem, getpath)                  __HYBRID_LIST_P_INSERT_BEFORE_R(p_successor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define LIST_PNEXT(elem, key)                                                             (&(elem)->key.le_next)
#define LIST_PNEXT_P(elem, getpath)                                                       (&getpath(elem).le_next)
#define LIST_P_REMOVE(p_elem, key)                                                        __HYBRID_LIST_P_REMOVE(p_elem, __HYBRID_Q_KEY, key)
#define LIST_P_REMOVE_P(p_elem, getpath)                                                  __HYBRID_LIST_P_REMOVE(p_elem, __HYBRID_Q_PTH, getpath)
#define LIST_P_REMOVE_R(p_lo_elem, hi_elem, key)                                          __HYBRID_LIST_P_REMOVE_R(p_lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define LIST_P_REMOVE_R_P(p_lo_elem, hi_elem, getpath)                                    __HYBRID_LIST_P_REMOVE_R(p_lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define LIST_P_REPLACE(p_old_elem, new_elem, key)                                         __HYBRID_LIST_P_REPLACE(p_old_elem, new_elem, __HYBRID_Q_KEY, key)
#define LIST_P_REPLACE_P(p_old_elem, new_elem, getpath)                                   __HYBRID_LIST_P_REPLACE(p_old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define LIST_P_REPLACE_R(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)       __HYBRID_LIST_P_REPLACE_R(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_KEY, key)
#define LIST_P_REPLACE_R_P(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath) __HYBRID_LIST_P_REPLACE_R(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_PTH, getpath)
#define LIST_REMOVE_AFTER(elem, key)                                                      __HYBRID_LIST_REMOVE_AFTER(elem, __HYBRID_Q_KEY, key)
#define LIST_REMOVE_AFTER_P(elem, getpath)                                                __HYBRID_LIST_REMOVE_AFTER(elem, __HYBRID_Q_PTH, getpath)
#define LIST_REMOVE_HEAD(self, key)                                                       __HYBRID_LIST_REMOVE_HEAD(self, __HYBRID_Q_KEY, key)
#define LIST_REMOVE_HEAD_P(self, getpath)                                                 __HYBRID_LIST_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#define LIST_REMOVE_P(elem, getpath)                                                      __HYBRID_LIST_REMOVE(elem, __HYBRID_Q_PTH, getpath)
#define LIST_REMOVE_R(lo_elem, hi_elem, key)                                              __HYBRID_LIST_REMOVE_R(lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define LIST_REMOVE_R_P(lo_elem, hi_elem, getpath)                                        __HYBRID_LIST_REMOVE_R(lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define LIST_REPLACE(old_elem, new_elem, key)                                             __HYBRID_LIST_REPLACE(old_elem, new_elem, __HYBRID_Q_KEY, key)
#define LIST_REPLACE_P(old_elem, new_elem, getpath)                                       __HYBRID_LIST_REPLACE(old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define LIST_REPLACE_R(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)           __HYBRID_LIST_REPLACE_R(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_KEY, key)
#define LIST_REPLACE_R_P(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath)     __HYBRID_LIST_REPLACE_R(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_PTH, getpath)
#define LIST_UNBIND(elem, key)                                                            __HYBRID_LIST_UNBIND(elem, __HYBRID_Q_KEY, key)
#define LIST_UNBIND_P(elem, getpath)                                                      __HYBRID_LIST_UNBIND(elem, __HYBRID_Q_PTH, getpath)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_LIST_CONCAT_P_3(dst, src, getpath)                                        __HYBRID_LIST_CONCAT(dst, src, __typeof__(*(src)->lh_first), __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_CONCAT_P_4(dst, src, type, getpath)                                  __HYBRID_LIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_FOREACH_FROM_SAFE_P_3(elem, self, getpath)                           __HYBRID_LIST_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_FOREACH_FROM_SAFE_P_4(elem, self, getpath, tvar)                     __HYBRID_LIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_LIST_FOREACH_SAFE_P_3(elem, self, getpath)                                __HYBRID_LIST_FOREACH_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_FOREACH_SAFE_P_4(elem, self, getpath, tvar)                          __HYBRID_LIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_LIST_INSERT_TAIL_3(self, elem, key)                                       __HYBRID_LIST_INSERT_TAIL(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_INSERT_TAIL_4(self, elem, type, key)                                 __HYBRID_LIST_INSERT_TAIL(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_INSERT_TAIL_P_3(self, elem, getpath)                                 __HYBRID_LIST_INSERT_TAIL(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_INSERT_TAIL_P_4(self, elem, T, getpath)                              __HYBRID_LIST_INSERT_TAIL(self, elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_INSERT_TAIL_R_4(self, lo_elem, hi_elem, key)                         __HYBRID_LIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __typeof__(*(lo_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_INSERT_TAIL_R_5(self, lo_elem, hi_elem, type, key)                   __HYBRID_LIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_INSERT_TAIL_R_P_4(self, lo_elem, hi_elem, getpath)                   __HYBRID_LIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __typeof__(*(lo_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_INSERT_TAIL_R_P_5(self, lo_elem, hi_elem, T, getpath)                __HYBRID_LIST_INSERT_TAIL_R(self, lo_elem, hi_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_PREV_3(elem, self, key)                                              __HYBRID_LIST_PREV3(elem, self, __typeof__(*(elem)), key)
#define __HYBRID_LIST_PREV_4(elem, self, type, key)                                        __HYBRID_LIST_PREV3(elem, self, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_PREV_P_3(elem, self, key)                                            __HYBRID_LIST_PREV4(elem, self, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_PREV_P_4(elem, self, T, getpath)                                     __HYBRID_LIST_PREV4(elem, self, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_PREV_UNSAFE_2(elem, key)                                             __HYBRID_LIST_PREV_UNSAFE3(elem, __typeof__(*(elem)), key)
#define __HYBRID_LIST_PREV_UNSAFE_3(elem, type, key)                                       __HYBRID_LIST_PREV_UNSAFE3(elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_PREV_UNSAFE_P_2(elem, key)                                           __HYBRID_LIST_PREV_UNSAFE4(elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_PREV_UNSAFE_P_3(elem, T, getpath)                                    __HYBRID_LIST_PREV_UNSAFE4(elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_REMOVEALL_5(self, out_pelem, key, condition, on_match)               __HYBRID_LIST_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_LIST_REMOVEALL_6(self, out_pelem, type, key, condition, on_match)         __HYBRID_LIST_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_LIST_REMOVEALL_P_5(self, out_pelem, getpath, condition, on_match)         __HYBRID_LIST_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_LIST_REMOVEALL_P_6(self, out_pelem, T, getpath, condition, on_match)      __HYBRID_LIST_REMOVEALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_LIST_REMOVE_IF_4(self, out_pelem, key, condition)                         __HYBRID_LIST_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_LIST_REMOVE_IF_5(self, out_pelem, type, key, condition)                   __HYBRID_LIST_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_LIST_REMOVE_IF_P_4(self, out_pelem, getpath, condition)                   __HYBRID_LIST_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_LIST_REMOVE_IF_P_5(self, out_pelem, T, getpath, condition)                __HYBRID_LIST_REMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_LIST_SWAP_P_3(l1, l2, getpath)                                            __HYBRID_LIST_SWAP(l1, l2, __typeof__(*(l2)->lh_first), __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_SWAP_P_4(l1, l2, T, getpath)                                         __HYBRID_LIST_SWAP(l1, l2, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_TRYREMOVE_IF_5(self, out_pelem, key, condition, on_failure)          __HYBRID_LIST_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_LIST_TRYREMOVE_IF_6(self, out_pelem, type, key, condition, on_failure)    __HYBRID_LIST_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_LIST_TRYREMOVE_IF_P_5(self, out_pelem, getpath, condition, on_failure)    __HYBRID_LIST_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_LIST_TRYREMOVE_IF_P_6(self, out_pelem, T, getpath, condition, on_failure) __HYBRID_LIST_TRYREMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_LIST_TRYUNBIND_IF_5(self, out_pelem, key, condition, on_failure)          __HYBRID_LIST_TRYUNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_LIST_TRYUNBIND_IF_6(self, out_pelem, type, key, condition, on_failure)    __HYBRID_LIST_TRYUNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_LIST_TRYUNBIND_IF_P_5(self, out_pelem, getpath, condition, on_failure)    __HYBRID_LIST_TRYUNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_LIST_TRYUNBIND_IF_P_6(self, out_pelem, T, getpath, condition, on_failure) __HYBRID_LIST_TRYUNBIND_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_LIST_UNBINDALL_5(self, out_pelem, key, condition, on_match)               __HYBRID_LIST_UNBINDALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_LIST_UNBINDALL_6(self, out_pelem, type, key, condition, on_match)         __HYBRID_LIST_UNBINDALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_LIST_UNBINDALL_P_5(self, out_pelem, getpath, condition, on_match)         __HYBRID_LIST_UNBINDALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_LIST_UNBINDALL_P_6(self, out_pelem, T, getpath, condition, on_match)      __HYBRID_LIST_UNBINDALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_LIST_UNBIND_IF_4(self, out_pelem, key, condition)                         __HYBRID_LIST_UNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_LIST_UNBIND_IF_5(self, out_pelem, type, key, condition)                   __HYBRID_LIST_UNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_LIST_UNBIND_IF_P_4(self, out_pelem, getpath, condition)                   __HYBRID_LIST_UNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_LIST_UNBIND_IF_P_5(self, out_pelem, T, getpath, condition)                __HYBRID_LIST_UNBIND_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_LIST_P_PREV_3(p_elem, self, key)                                          ((p_elem) == &(self)->lh_first ? __NULLPTR : __COMPILER_CONTAINER_OF(p_elem, __typeof__(**(p_elem)), key.le_next))
#define __HYBRID_LIST_P_PREV_4(p_elem, self, type, key)                                    ((p_elem) == &(self)->lh_first ? __NULLPTR : __COMPILER_CONTAINER_OF(p_elem, __HYBRID_Q_STRUCT type, key.le_next))
#define __HYBRID_LIST_P_PREV_P_3(p_elem, self, getpath)                                    ((p_elem) == &(self)->lh_first ? __NULLPTR : (__typeof__(*(p_elem)))((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&getpath((T *)0).le_next))
#define __HYBRID_LIST_P_PREV_P_4(p_elem, self, T, getpath)                                 ((p_elem) == &(self)->lh_first ? __NULLPTR : (T *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&getpath((T *)0).le_next))
#define __HYBRID_LIST_P_PREV_UNSAFE_2(p_elem, key)                                         __COMPILER_CONTAINER_OF(p_elem, __typeof__(**(p_elem)), key.le_next)
#define __HYBRID_LIST_P_PREV_UNSAFE_3(p_elem, type, key)                                   __COMPILER_CONTAINER_OF(p_elem, __HYBRID_Q_STRUCT type, key.le_next)
#define __HYBRID_LIST_P_PREV_UNSAFE_P_2(p_elem, getpath)                                   (__typeof__(*(p_elem)))((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&getpath((T *)0).le_next)
#define __HYBRID_LIST_P_PREV_UNSAFE_P_3(p_elem, T, getpath)                                (T *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&getpath((T *)0).le_next)
#define LIST_CONCAT_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_CONCAT_P_, (__VA_ARGS__))(__VA_ARGS__)            /* LIST_CONCAT_P(dst, src, [type], getpath) */
#define LIST_FOREACH_FROM_SAFE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_FOREACH_FROM_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__) /* LIST_FOREACH_FROM_SAFE_P(elem, self, getpath, [tvar]) */
#define LIST_FOREACH_SAFE_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_FOREACH_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)      /* LIST_FOREACH_SAFE_P(elem, self, getpath, [tvar]) */
#define LIST_INSERT_TAIL(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_INSERT_TAIL_, (__VA_ARGS__))(__VA_ARGS__)         /* LIST_INSERT_TAIL(self, elem, [type], key) */
#define LIST_INSERT_TAIL_P(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_INSERT_TAIL_P_, (__VA_ARGS__))(__VA_ARGS__)       /* LIST_INSERT_TAIL_P(self, elem, [T], getpath) */
#define LIST_INSERT_TAIL_R(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_INSERT_TAIL_R_, (__VA_ARGS__))(__VA_ARGS__)       /* LIST_INSERT_TAIL_R(self, lo_elem, hi_elem, [type], key) */
#define LIST_INSERT_TAIL_R_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_INSERT_TAIL_R_P_, (__VA_ARGS__))(__VA_ARGS__)     /* LIST_INSERT_TAIL_R_P(self, lo_elem, hi_elem, [T], getpath) */
#define LIST_PREV(...)                __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_PREV_, (__VA_ARGS__))(__VA_ARGS__)                /* LIST_PREV(elem, self, [type], key) */
#define LIST_PREV_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_PREV_P_, (__VA_ARGS__))(__VA_ARGS__)              /* LIST_PREV_P(elem, self, [T], getpath) */
#define LIST_PREV_UNSAFE(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_PREV_UNSAFE_, (__VA_ARGS__))(__VA_ARGS__)         /* LIST_PREV_UNSAFE(elem, [type], key) */
#define LIST_PREV_UNSAFE_P(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_PREV_UNSAFE_P_, (__VA_ARGS__))(__VA_ARGS__)       /* LIST_PREV_UNSAFE_P(elem, [T], getpath) */
#define LIST_REMOVEALL(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)        /* LIST_REMOVEALL(self, out_pelem, [type], key, condition, on_match) */
#define LIST_REMOVEALL_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)      /* LIST_REMOVEALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define LIST_REMOVE_IF(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_REMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)           /* LIST_REMOVE_IF(self, out_pelem, [type], key, condition) */
#define LIST_REMOVE_IF_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_REMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)         /* LIST_REMOVE_IF_P(self, out_pelem, [T], getpath, condition) */
#define LIST_SWAP_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_SWAP_P_, (__VA_ARGS__))(__VA_ARGS__)              /* LIST_SWAP_P(l1, l2, [T], getpath) */
#define LIST_TRYREMOVE_IF(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)        /* LIST_TRYREMOVE_IF(self, out_pelem, [type], key, condition, on_failure) */
#define LIST_TRYREMOVE_IF_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)      /* LIST_TRYREMOVE_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#define LIST_TRYUNBIND_IF(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_TRYUNBIND_IF_, (__VA_ARGS__))(__VA_ARGS__)        /* LIST_TRYUNBIND_IF(self, out_pelem, [type], key, condition, on_failure) */
#define LIST_TRYUNBIND_IF_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_TRYUNBIND_IF_P_, (__VA_ARGS__))(__VA_ARGS__)      /* LIST_TRYUNBIND_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#define LIST_UNBINDALL(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_UNBINDALL_, (__VA_ARGS__))(__VA_ARGS__)           /* LIST_UNBINDALL(self, out_pelem, [type], key, condition, on_match) */
#define LIST_UNBINDALL_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_UNBINDALL_P_, (__VA_ARGS__))(__VA_ARGS__)         /* LIST_UNBINDALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define LIST_UNBIND_IF(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_UNBIND_IF_, (__VA_ARGS__))(__VA_ARGS__)           /* LIST_UNBIND_IF(self, out_pelem, [type], key, condition) */
#define LIST_UNBIND_IF_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_UNBIND_IF_P_, (__VA_ARGS__))(__VA_ARGS__)         /* LIST_UNBIND_IF_P(self, out_pelem, [T], getpath, condition) */
#define LIST_P_PREV(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_P_PREV_, (__VA_ARGS__))(__VA_ARGS__)              /* LIST_P_PREV(p_elem, self, [type], key) */
#define LIST_P_PREV_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_P_PREV_P_, (__VA_ARGS__))(__VA_ARGS__)            /* LIST_P_PREV_P(p_elem, self, [T], getpath) */
#define LIST_P_PREV_UNSAFE(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_P_PREV_UNSAFE_, (__VA_ARGS__))(__VA_ARGS__)       /* LIST_P_PREV_UNSAFE(p_elem, [type], key) */
#define LIST_P_PREV_UNSAFE_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_P_PREV_UNSAFE_P_, (__VA_ARGS__))(__VA_ARGS__)     /* LIST_P_PREV_UNSAFE_P(p_elem, [T], getpath) */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define LIST_CONCAT_P(dst, src, type, getpath)                                     __HYBRID_LIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define LIST_FOREACH_FROM_SAFE_P(elem, self, getpath, tvar)                        __HYBRID_LIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define LIST_FOREACH_SAFE_P(elem, self, getpath, tvar)                             __HYBRID_LIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define LIST_INSERT_TAIL(self, elem, type, key)                                    __HYBRID_LIST_INSERT_TAIL(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define LIST_INSERT_TAIL_P(self, elem, T, getpath)                                 __HYBRID_LIST_INSERT_TAIL(self, elem, T, __HYBRID_Q_KEY, getpath)
#define LIST_INSERT_TAIL_R(self, lo_elem, hi_elem, type, key)                      __HYBRID_LIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define LIST_INSERT_TAIL_R_P(self, lo_elem, hi_elem, T, getpath)                   __HYBRID_LIST_INSERT_TAIL_R(self, lo_elem, hi_elem, T, __HYBRID_Q_KEY, getpath)
#define LIST_PREV(elem, self, type, key)                                           __HYBRID_LIST_PREV3(elem, self, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define LIST_PREV_P(elem, self, type, getpath)                                     __HYBRID_LIST_PREV4(elem, self, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define LIST_PREV_UNSAFE(elem, type, key)                                          __HYBRID_LIST_PREV_UNSAFE3(elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define LIST_PREV_UNSAFE_P(elem, type, getpath)                                    __HYBRID_LIST_PREV_UNSAFE4(elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define LIST_REMOVEALL(self, out_pelem, type, key, condition, on_match)            __HYBRID_LIST_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define LIST_REMOVEALL_P(self, out_pelem, type, getpath, condition, on_match)      __HYBRID_LIST_REMOVEALL(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_match)
#define LIST_REMOVE_IF(self, out_pelem, type, key, condition)                      __HYBRID_LIST_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define LIST_REMOVE_IF_P(self, out_pelem, type, getpath, condition)                __HYBRID_LIST_REMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition)
#define LIST_SWAP_P(l1, l2, type, getpath)                                         __HYBRID_LIST_SWAP(l1, l2, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define LIST_TRYREMOVE_IF(self, out_pelem, type, key, condition, on_failure)       __HYBRID_LIST_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define LIST_TRYREMOVE_IF_P(self, out_pelem, type, getpath, condition, on_failure) __HYBRID_LIST_TRYREMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define LIST_TRYUNBIND_IF(self, out_pelem, type, key, condition, on_failure)       __HYBRID_LIST_TRYUNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define LIST_TRYUNBIND_IF_P(self, out_pelem, type, getpath, condition, on_failure) __HYBRID_LIST_TRYUNBIND_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define LIST_UNBINDALL(self, out_pelem, type, key, condition, on_match)            __HYBRID_LIST_UNBINDALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define LIST_UNBINDALL_P(self, out_pelem, type, getpath, condition, on_match)      __HYBRID_LIST_UNBINDALL(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_match)
#define LIST_UNBIND_IF(self, out_pelem, type, key, condition)                      __HYBRID_LIST_UNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define LIST_UNBIND_IF_P(self, out_pelem, type, getpath, condition)                __HYBRID_LIST_UNBIND_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition)
#define LIST_P_PREV(p_elem, self, type, key)                                       ((p_elem) == &(self)->lh_first ? __NULLPTR : __COMPILER_CONTAINER_OF(p_elem, __HYBRID_Q_STRUCT type, key.le_next))
#define LIST_P_PREV_UNSAFE(p_elem, type, key)                                      __COMPILER_CONTAINER_OF(p_elem, __HYBRID_Q_STRUCT type, key.le_next)
#define LIST_P_PREV_P(p_elem, self, type, getpath)                                 ((p_elem) == &(self)->lh_first ? __NULLPTR : (__HYBRID_Q_STRUCT type *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&getpath((T *)0).le_next))
#define LIST_P_PREV_UNSAFE_P(p_elem, type, getpath)                                (__HYBRID_Q_STRUCT type *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&getpath((T *)0).le_next)
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_LIST_COUNT_2(self, key)                                                   __XBLOCK({ __SIZE_TYPE__ __hlc_res; __HYBRID_LIST_COUNT_3(self, &__hlc_res, key); __XRETURN __hlc_res; })
#define __HYBRID_LIST_COUNT_3(self, presult, key)                                          __HYBRID_LIST_COUNT(self, presult, __typeof__(*(self)->lh_first), __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_COUNT_4(self, presult, type, key)                                    __HYBRID_LIST_COUNT(self, presult, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_COUNT_P_2(self, getpath)                                             __XBLOCK({ __SIZE_TYPE__ __hlc_res; __HYBRID_LIST_COUNT_P_3(self, &__hlc_res, getpath); __XRETURN __hlc_res; })
#define __HYBRID_LIST_COUNT_P_3(self, presult, getpath)                                    __HYBRID_LIST_COUNT(self, presult, __typeof__(*(self)->lh_first), __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_COUNT_P_4(self, presult, type, getpath)                              __HYBRID_LIST_COUNT(self, presult, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define LIST_COUNT(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_COUNT_, (__VA_ARGS__))(__VA_ARGS__)   /* LIST_COUNT(self, [presult], [type], key) */
#define LIST_COUNT_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_COUNT_P_, (__VA_ARGS__))(__VA_ARGS__) /* LIST_COUNT_P(self, [presult], [type], getpath) */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define LIST_COUNT(self, presult, type, key)       __HYBRID_LIST_COUNT(self, presult, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define LIST_COUNT_P(self, presult, type, getpath) __HYBRID_LIST_COUNT(self, presult, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#endif /* !__HYBRID_LIST_RESTRICT_API */
#define __HYBRID_LIST_COUNT(self, presult, T, X, _)     \
	/* Sorry, this one must be a statement */           \
	do {                                                \
		T *__hlc_iter;                                  \
		*(presult) = 0;                                 \
		for (__hlc_iter = (self)->lh_first; __hlc_iter; \
		     __hlc_iter = X(_, __hlc_iter).le_next)     \
			++*(presult);                               \
	}	__WHILE0
#define __HYBRID_LIST_CONCAT(dst, src, T, X, _)                               \
	/* Sorry, this one must be a statement */                                 \
	do {                                                                      \
		if ((src)->lh_first != __NULLPTR) {                                   \
			T **__hlc_dst_last = &(dst)->lh_first;                            \
			while (*__hlc_dst_last)                                           \
				__hlc_dst_last = &X(_, *__hlc_dst_last).le_next;              \
			X(_, *__hlc_dst_last = (src)->lh_first).le_prev = __hlc_dst_last; \
			(src)->lh_first = __NULLPTR;                                      \
		}                                                                     \
	}	__WHILE0
#define __HYBRID_LIST_SWAP(l1, l2, T, X, _)                 \
	/* Sorry, this one must be a statement */               \
	do {                                                    \
		T *__hls_tmp = (l1)->lh_first;                      \
		if (((l1)->lh_first = (l2)->lh_first) != __NULLPTR) \
			X(_, (l1)->lh_first).le_prev = &(l1)->lh_first; \
		if (((l2)->lh_first = __hls_tmp) != __NULLPTR)      \
			X(_, __hls_tmp).le_prev = &(l2)->lh_first;      \
	}	__WHILE0
#define __HYBRID_LIST_MOVE(dst, src, X, _)                      \
	(((dst)->lh_first = (src)->lh_first) != __NULLPTR           \
	 ? (void)(X(_, (dst)->lh_first).le_prev = &(dst)->lh_first, \
	          (src)->lh_first               = __NULLPTR)        \
	 : (void)0)
#define __HYBRID_LIST_Q_ASSERT_NEXTLINK_(elem, X, _) \
	__HYBRID_Q_ASSERT_(X(_, X(_, elem).le_next).le_prev == &X(_, elem).le_next)
#define __HYBRID_LIST_Q_ASSERT_PREVLINK_(elem, X, _) \
	__HYBRID_Q_ASSERT_(*X(_, elem).le_prev == (elem))
#define __HYBRID_LIST_Q_ASSERT_P_PREVLINK_(p_elem, X, _) \
	__HYBRID_Q_ASSERT_(X(_, *(p_elem)).le_prev == (p_elem))
#define __HYBRID_LIST_Q_ASSERT_FIRSTLINK_(self, X, _) \
	__HYBRID_Q_ASSERT_(X(_, (self)->lh_first).le_prev == &(self)->lh_first)
#define __HYBRID_LIST_PREV3(elem, self, T, key)   ((elem) == (self)->lh_first ? __NULLPTR : __COMPILER_CONTAINER_OF((elem)->key.le_prev, T, key.le_next))
#define __HYBRID_LIST_PREV4(elem, self, T, X, _)  ((elem) == (self)->lh_first ? __NULLPTR : (T *)((__SIZE_TYPE__)X(_, elem).le_prev - (__SIZE_TYPE__)&X(_, (T *)0).le_next))
#define __HYBRID_LIST_PREV_UNSAFE3(elem, T, key)  __COMPILER_CONTAINER_OF((elem)->key.le_prev, T, key.le_next)
#define __HYBRID_LIST_PREV_UNSAFE4(elem, T, X, _) ((T *)((__SIZE_TYPE__)X(_, elem).le_prev - (__SIZE_TYPE__)&X(_, (T *)0).le_next))
#define __HYBRID_LIST_INSERT_AFTER(predecessor, elem, X, _) \
	__HYBRID_LIST_INSERT_AFTER_R(predecessor, elem, elem, X, _)
#define __HYBRID_LIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, X, _)                               \
	(void)((X(_, hi_elem).le_next = *(X(_, lo_elem).le_prev = &X(_, predecessor).le_next)) != __NULLPTR \
	       ? (void)(__HYBRID_LIST_Q_ASSERT_NEXTLINK_(predecessor, X, _)                                 \
	                X(_, X(_, hi_elem).le_next).le_prev = &X(_, hi_elem).le_next)                       \
	       : (void)0,                                                                                   \
	       X(_, predecessor).le_next = (lo_elem))
#define __HYBRID_LIST_INSERT_BEFORE(successor, elem, X, _) \
	__HYBRID_LIST_INSERT_BEFORE_R(successor, elem, elem, X, _)
#define __HYBRID_LIST_INSERT_BEFORE_R(successor, lo_elem, hi_elem, X, _)    \
	(void)(__HYBRID_LIST_Q_ASSERT_PREVLINK_(successor, X, _)                \
	       *(X(_, lo_elem).le_prev = X(_, successor).le_prev)  = (lo_elem), \
	       *(X(_, successor).le_prev = &X(_, hi_elem).le_next) = (successor))
#define __HYBRID_LIST_INSERT_HEAD(self, elem, X, _) \
	__HYBRID_LIST_INSERT_HEAD_R(self, elem, elem, X, _)
#define __HYBRID_LIST_INSERT_HEAD_R(self, lo_elem, hi_elem, X, _)            \
	(void)((X(_, hi_elem).le_next = (self)->lh_first) != __NULLPTR           \
	       ? (void)(__HYBRID_LIST_Q_ASSERT_FIRSTLINK_(self, X, _)            \
	                X(_, (self)->lh_first).le_prev = &X(_, hi_elem).le_next) \
	       : (void)0,                                                        \
	       *(X(_, lo_elem).le_prev = &(self)->lh_first) = (lo_elem))
#define __HYBRID_LIST_P_INSERT_BEFORE(p_successor, elem, X, _) \
	__HYBRID_LIST_P_INSERT_BEFORE_R(p_successor, elem, elem, X, _)
#define __HYBRID_LIST_P_INSERT_BEFORE_R(p_successor, lo_elem, hi_elem, X, _)               \
	(void)((X(_, hi_elem).le_next = *(X(_, lo_elem).le_prev = (p_successor))) != __NULLPTR \
	       ? (void)(__HYBRID_LIST_Q_ASSERT_P_PREVLINK_(p_successor, X, _)                  \
	                X(_, X(_, hi_elem).le_next).le_prev = &X(_, hi_elem).le_next)          \
	       : (void)0,                                                                      \
	       *(p_successor) = (lo_elem))
#define __HYBRID_LIST_P_REMOVE(p_elem, X, _) \
	__HYBRID_LIST_P_REMOVE_R(p_elem, *(p_elem), X, _)
#define __HYBRID_LIST_P_REMOVE_R(p_lo_elem, hi_elem, X, _)       \
	((*(p_lo_elem) = X(_, hi_elem).le_next) != __NULLPTR         \
	 ? (void)(__HYBRID_LIST_Q_ASSERT_NEXTLINK_(hi_elem, X, _)    \
	          X(_, X(_, hi_elem).le_next).le_prev = (p_lo_elem)) \
	 : (void)0,                                                  \
	 __HYBRID_Q_BADPTR(X(_, hi_elem).le_next),                   \
	 __HYBRID_Q_BADPTR(X(_, (*p_lo_elem)).le_prev))
#define __HYBRID_LIST_P_REPLACE(p_old_elem, new_elem, X, _) \
	__HYBRID_LIST_P_REPLACE_R(p_old_elem, *(p_old_elem), new_elem, new_elem, X, _)
#define __HYBRID_LIST_P_REPLACE_R(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, X, _) \
	(*(X(_, new_lo_elem).le_prev = p_old_lo_elem) = (new_lo_elem),                            \
	 (X(_, new_hi_elem).le_next = X(_, old_hi_elem).le_next) != __NULLPTR                     \
	 ? (void)(__HYBRID_LIST_Q_ASSERT_NEXTLINK_(old_hi_elem, X, _)                             \
	          X(_, X(_, new_hi_elem).le_next).le_prev = &X(_, new_hi_elem).le_next)           \
	 : (void)0,                                                                               \
	 __HYBRID_Q_BADPTR(X(_, *(p_old_lo_elem)).le_prev),                                       \
	 __HYBRID_Q_BADPTR(X(_, old_hi_elem).le_next))
#define __HYBRID_LIST_REMOVE_AFTER(elem, X, _)                            \
	(__HYBRID_Q_BADPTR(X(_, X(_, elem).le_next).le_prev),                 \
	 (X(_, elem).le_next = X(_, X(_, elem).le_next).le_next) != __NULLPTR \
	 ? (void)(__HYBRID_LIST_Q_ASSERT_NEXTLINK_(elem, X, _)                \
	          X(_, X(_, elem).le_next).le_prev = &X(_, elem).le_next)     \
	 : (void)0)
#define __HYBRID_LIST_REMOVE_HEAD(self, X, _)                         \
	(__HYBRID_Q_BADPTR(X(_, (self)->lh_first).le_prev),               \
	 ((self)->lh_first = X(_, (self)->lh_first).le_next) != __NULLPTR \
	 ? (void)(__HYBRID_LIST_Q_ASSERT_FIRSTLINK_(self, X, _)           \
	          X(_, (self)->lh_first).le_prev = &(self)->lh_first)     \
	 : (void)0)
#define __HYBRID_LIST_REMOVE(elem, X, _) \
	__HYBRID_LIST_REMOVE_R(elem, elem, X, _)
#define __HYBRID_LIST_REMOVE_R(lo_elem, hi_elem, X, _)                     \
	((*X(_, lo_elem).le_prev = X(_, hi_elem).le_next) != __NULLPTR         \
	 ? (void)(__HYBRID_LIST_Q_ASSERT_NEXTLINK_(hi_elem, X, _)              \
	          X(_, X(_, hi_elem).le_next).le_prev = X(_, lo_elem).le_prev) \
	 : (void)0,                                                            \
	 __HYBRID_Q_BADPTR(X(_, hi_elem).le_next),                             \
	 __HYBRID_Q_BADPTR(X(_, lo_elem).le_prev))
#define __HYBRID_LIST_UNBIND(elem, X, _)                                   \
	(void)((*X(_, elem).le_prev = X(_, elem).le_next) != __NULLPTR         \
	       ? (void)(__HYBRID_LIST_Q_ASSERT_NEXTLINK_(elem, X, _)           \
	                X(_, X(_, elem).le_next).le_prev = X(_, elem).le_prev) \
	       : (void)0,                                                      \
	       __HYBRID_Q_BADPTR(X(_, elem).le_next),                          \
	       X(_, elem).le_prev = __NULLPTR)
#define __HYBRID_LIST_REPLACE(old_elem, new_elem, X, _) \
	__HYBRID_LIST_REPLACE_R(old_elem, old_elem, new_elem, new_elem, X, _)
#define __HYBRID_LIST_REPLACE_R(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, X, _) \
	(*(X(_, new_lo_elem).le_prev = X(_, old_lo_elem).le_prev) = (new_lo_elem),            \
	 (X(_, new_hi_elem).le_next = X(_, old_hi_elem).le_next) != __NULLPTR                 \
	 ? (void)(__HYBRID_LIST_Q_ASSERT_NEXTLINK_(old_hi_elem, X, _)                         \
	          X(_, X(_, new_hi_elem).le_next).le_prev = &X(_, new_hi_elem).le_next)       \
	 : (void)0,                                                                           \
	 __HYBRID_Q_BADPTR(X(_, old_lo_elem).le_prev),                                        \
	 __HYBRID_Q_BADPTR(X(_, old_hi_elem).le_next))
#define __HYBRID_LIST_INSERT_TAIL(self, elem, T, X, _) \
	__HYBRID_LIST_INSERT_TAIL_R(self, elem, elem, T, X, _)
#define __HYBRID_LIST_INSERT_TAIL_R(self, lo_elem, hi_elem, T, X, _) \
	/* Sorry, this one must be a statement */                        \
	do {                                                             \
		T **__hlitr_piter = &(self)->lh_first;                       \
		while (*__hlitr_piter != __NULLPTR)                          \
			__hlitr_piter = &X(_, *__hlitr_piter).le_next;           \
		*(X(_, lo_elem).le_prev = __hlitr_piter) = (lo_elem);        \
		X(_, hi_elem).le_next   = __NULLPTR;                         \
	}	__WHILE0
#define __HYBRID_LIST_REMOVE_IF(self, out_pelem, T, X, _, condition)   \
	/* Sorry, this one must be a statement */                          \
	do {                                                               \
		T **__hlri_piter = &(self)->lh_first;                          \
		for (;;) {                                                     \
			*(out_pelem) = *__hlri_piter;                              \
			if (condition)                                             \
				break;                                                 \
			__hlri_piter = &X(_, *(out_pelem)).le_next;                \
		}                                                              \
		if ((*__hlri_piter = X(_, *(out_pelem)).le_next) != __NULLPTR) \
			X(_, X(_, *(out_pelem)).le_next).le_prev = __hlri_piter;   \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).le_next);                 \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).le_prev);                 \
	}	__WHILE0
#define __HYBRID_LIST_TRYREMOVE_IF(self, out_pelem, T, X, _, condition, on_failure) \
	/* Sorry, this one must be a statement */                                       \
	do {                                                                            \
		T **__hltri_piter = &(self)->lh_first;                                      \
		for (;;) {                                                                  \
			if ((*(out_pelem) = *__hltri_piter) == __NULLPTR) {                     \
				on_failure;                                                         \
				break;                                                              \
			}                                                                       \
			if (condition) {                                                        \
				if ((*__hltri_piter = X(_, *(out_pelem)).le_next) != __NULLPTR)     \
					X(_, X(_, *(out_pelem)).le_next).le_prev = __hltri_piter;       \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).le_next);                      \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).le_prev);                      \
				break;                                                              \
			}                                                                       \
			__hltri_piter = &X(_, *(out_pelem)).le_next;                            \
		}                                                                           \
	}	__WHILE0
#define __HYBRID_LIST_UNBIND_IF(self, out_pelem, T, X, _, condition)   \
	/* Sorry, this one must be a statement */                          \
	do {                                                               \
		T **__hlui_piter = &(self)->lh_first;                          \
		for (;;) {                                                     \
			*(out_pelem) = *__hlui_piter;                              \
			if (condition)                                             \
				break;                                                 \
			__hlui_piter = &X(_, *(out_pelem)).le_next;                \
		}                                                              \
		if ((*__hlui_piter = X(_, *(out_pelem)).le_next) != __NULLPTR) \
			X(_, X(_, *(out_pelem)).le_next).le_prev = __hlui_piter;   \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).le_next);                 \
		X(_, *(out_pelem)).le_prev = __NULLPTR;                        \
	}	__WHILE0
#define __HYBRID_LIST_TRYUNBIND_IF(self, out_pelem, T, X, _, condition, on_failure) \
	/* Sorry, this one must be a statement */                                       \
	do {                                                                            \
		T **__hltui_piter = &(self)->lh_first;                                      \
		for (;;) {                                                                  \
			if ((*(out_pelem) = *__hltui_piter) == __NULLPTR) {                     \
				on_failure;                                                         \
				break;                                                              \
			}                                                                       \
			if (condition) {                                                        \
				if ((*__hltui_piter = X(_, *(out_pelem)).le_next) != __NULLPTR)     \
					X(_, X(_, *(out_pelem)).le_next).le_prev = __hltui_piter;       \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).le_next);                      \
				X(_, *(out_pelem)).le_prev = __NULLPTR;                             \
				break;                                                              \
			}                                                                       \
			__hltui_piter = &X(_, *(out_pelem)).le_next;                            \
		}                                                                           \
	}	__WHILE0
#define __HYBRID_LIST_REMOVEALL(self, out_pelem, T, X, _, condition, on_match) \
	/* Sorry, this one must be a statement */                                  \
	do {                                                                       \
		T **__hlra_piter = &(self)->lh_first;                                  \
		while ((*(out_pelem) = *__hlra_piter) != __NULLPTR) {                  \
			if (condition) {                                                   \
				if ((*__hlra_piter = X(_, *(out_pelem)).le_next) != __NULLPTR) \
					X(_, X(_, *(out_pelem)).le_next).le_prev = __hlra_piter;   \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).le_next);                 \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).le_prev);                 \
				on_match;                                                      \
			} else {                                                           \
				__hlra_piter = &X(_, *(out_pelem)).le_next;                    \
			}                                                                  \
		}                                                                      \
	}	__WHILE0
#define __HYBRID_LIST_UNBINDALL(self, out_pelem, T, X, _, condition, on_match) \
	/* Sorry, this one must be a statement */                                  \
	do {                                                                       \
		T **__hlua_piter = &(self)->lh_first;                                  \
		while ((*(out_pelem) = *__hlua_piter) != __NULLPTR) {                  \
			if (condition) {                                                   \
				if ((*__hlua_piter = X(_, *(out_pelem)).le_next) != __NULLPTR) \
					X(_, X(_, *(out_pelem)).le_next).le_prev = __hlua_piter;   \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).le_next);                 \
				X(_, *(out_pelem)).le_prev = __NULLPTR;                        \
				on_match;                                                      \
			} else {                                                           \
				__hlua_piter = &X(_, *(out_pelem)).le_next;                    \
			}                                                                  \
		}                                                                      \
	}	__WHILE0
#define __HYBRID_LIST_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->lh_first; (elem); (elem) = X(_, elem).le_next)
#define __HYBRID_LIST_FOREACH_FROM(elem, self, X, _) \
	for ((elem) ? (void)0 : (void)((elem) = (self)->lh_first); (elem); (elem) = X(_, elem).le_next)
#define __HYBRID_LIST_P_FOREACH(p_elem, self, X, _) \
	for ((p_elem) = &(self)->lh_first; *(p_elem); (p_elem) = &X(_, *(p_elem)).le_next)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_LIST_FOREACH_SAFE3(elem, self, X, _)         \
	if (((elem) = (self)->lh_first, 0))                       \
		;                                                     \
	else                                                      \
		for (__typeof__(elem) __hlfs_tvar;                    \
		     (elem) && (__hlfs_tvar = X(_, elem).le_next, 1); \
		     (elem) = __hlfs_tvar)
#define __HYBRID_LIST_FOREACH_FROM_SAFE3(elem, self, X, _)         \
	if (((elem) ? (void)0 : (void)((elem) = (self)->lh_first), 0)) \
		;                                                          \
	else                                                           \
		for (__typeof__(elem) __hlfs_tvar;                         \
		     (elem) && (__hlfs_tvar = X(_, elem).le_next, 1);      \
		     (elem) = __hlfs_tvar)
#endif /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define __HYBRID_LIST_FOREACH_SAFE4(elem, self, X, _, tvar) \
	for ((elem) = (self)->lh_first;                         \
	     (elem) && ((tvar) = X(_, elem).le_next, 1);        \
	     (elem) = (tvar))
#define __HYBRID_LIST_FOREACH_FROM_SAFE4(elem, self, X, _, tvar) \
	for ((elem) ? (void)0 : (void)((elem) = (self)->lh_first);   \
	     (elem) && ((tvar) = X(_, elem).le_next, 1);             \
	     (elem) = (tvar))





/************************************************************************/
/* SLIST: Single-head, singly-linked list                               */
/************************************************************************/
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_SLIST_HEAD_1(type)             struct      { __HYBRID_Q_STRUCT type *slh_first; /* [0..1] List head */ }
#define __HYBRID_SLIST_HEAD_2(name, type)       struct name { __HYBRID_Q_STRUCT type *slh_first; /* [0..1] List head */ }
#define __HYBRID_SLIST_CLASS_HEAD_1(type)       struct      { __HYBRID_Q_CLASS  type *slh_first; /* [0..1] List head */ }
#define __HYBRID_SLIST_CLASS_HEAD_2(name, type) struct name { __HYBRID_Q_CLASS  type *slh_first; /* [0..1] List head */ }
#undef SLIST_HEAD
#undef SLIST_CLASS_HEAD
#define SLIST_HEAD(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_HEAD_, (__VA_ARGS__))(__VA_ARGS__)       /* SLIST_HEAD([name], type) */
#define SLIST_CLASS_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_CLASS_HEAD_, (__VA_ARGS__))(__VA_ARGS__) /* SLIST_CLASS_HEAD([name], type) */
#else /* !__HYBRID_LIST_RESTRICT_API && __HYBRID_PP_VA_OVERLOAD */
#define SLIST_HEAD(name, type)       struct name { __HYBRID_Q_STRUCT type *slh_first; /* [0..1] List head */ }
#define SLIST_CLASS_HEAD(name, type) struct name { __HYBRID_Q_CLASS  type *slh_first; /* [0..1] List head */ }
#endif /* __HYBRID_LIST_RESTRICT_API || !__HYBRID_PP_VA_OVERLOAD */
#define SLIST_ENTRY(type)       struct { __HYBRID_Q_STRUCT type *sle_next; /* [0..1] Next-link */ }
#define SLIST_CLASS_ENTRY(type) struct { __HYBRID_Q_CLASS  type *sle_next; /* [0..1] Next-link */ }
#define SLIST_EMPTY(self)                              ((self)->slh_first == __NULLPTR)
#define SLIST_END(self)                                __NULLPTR
#define SLIST_FIRST(self)                              (self)->slh_first
#define SLIST_FOREACH(elem, self, key)                 __HYBRID_SLIST_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define SLIST_FOREACH_FROM(elem, self, key)            __HYBRID_SLIST_FOREACH_FROM(elem, self, __HYBRID_Q_KEY, key)
#define SLIST_FOREACH_PREVPTR(elem, p_elem, self, key) __HYBRID_SLIST_FOREACH_PREVPTR(elem, p_elem, self, __HYBRID_Q_KEY, key)
#define SLIST_HEAD_INITIALIZER(self)                   { __NULLPTR }
#define SLIST_INIT(self)                               (void)((self)->slh_first = __NULLPTR)
#define SLIST_INSERT(self, elem, key)                  __HYBRID_SLIST_INSERT(self, elem, __HYBRID_Q_KEY, key)
#define SLIST_INSERT_AFTER(predecessor, elem, key)     __HYBRID_SLIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_KEY, key)
#define SLIST_INSERT_HEAD(self, elem, key)             __HYBRID_SLIST_INSERT(self, elem, __HYBRID_Q_KEY, key)
#define SLIST_NEXT(elem, key)                          (elem)->key.sle_next
#define SLIST_REMOVE_AFTER(elem, key)                  __HYBRID_SLIST_REMOVE_AFTER(elem, __HYBRID_Q_KEY, key)
#define SLIST_REMOVE_HEAD(self, key)                   __HYBRID_SLIST_REMOVE_HEAD(self, __HYBRID_Q_KEY, key)
#define SLIST_REMOVE_PREVPTR(p_elem, elem, key)        __HYBRID_SLIST_REMOVE_PREVPTR(p_elem, elem, __HYBRID_Q_KEY, key)
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_SLIST_CONCAT_3(dst, src, key)                    __HYBRID_SLIST_CONCAT(dst, src, __typeof__(*(src)->lh_first), __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_CONCAT_4(dst, src, type, key)              __HYBRID_SLIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_FOREACH_FROM_SAFE_3(elem, self, key)       __HYBRID_SLIST_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_FOREACH_FROM_SAFE_4(elem, self, key, tvar) __HYBRID_SLIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_SLIST_FOREACH_SAFE_3(elem, self, key)            __HYBRID_SLIST_FOREACH_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_FOREACH_SAFE_4(elem, self, key, tvar)      __HYBRID_SLIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_SLIST_REMOVE_3(self, elem, key)                  __HYBRID_SLIST_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_REMOVE_4(self, elem, type, key)            __HYBRID_SLIST_REMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_SWAP_2(l1, l2)                             __HYBRID_SLIST_SWAP(l1, l2, __typeof__(*(l1)->slh_first))
#define __HYBRID_SLIST_SWAP_3(l1, l2, type)                       __HYBRID_SLIST_SWAP(l1, l2, __HYBRID_Q_STRUCT type)
#undef SLIST_CONCAT
#undef SLIST_FOREACH_FROM_SAFE
#undef SLIST_FOREACH_SAFE
#undef SLIST_REMOVE
#undef SLIST_SWAP
#define SLIST_CONCAT(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_CONCAT_, (__VA_ARGS__))(__VA_ARGS__)            /* SLIST_CONCAT(dst, src, [type], key) */
#define SLIST_FOREACH_FROM_SAFE(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_FOREACH_FROM_SAFE_, (__VA_ARGS__))(__VA_ARGS__) /* SLIST_FOREACH_FROM_SAFE(elem, self, key, [tvar]) */
#define SLIST_FOREACH_SAFE(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_FOREACH_SAFE_, (__VA_ARGS__))(__VA_ARGS__)      /* SLIST_FOREACH_SAFE(elem, self, key, [tvar]) */
#define SLIST_REMOVE(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REMOVE_, (__VA_ARGS__))(__VA_ARGS__)            /* SLIST_REMOVE(self, elem, [type], key) */
#define SLIST_SWAP(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_SWAP_, (__VA_ARGS__))(__VA_ARGS__)              /* SLIST_SWAP(l1, l2, [type]) */
#else /* !__HYBRID_LIST_RESTRICT_API && __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define SLIST_CONCAT(dst, src, type, key)              __HYBRID_SLIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SLIST_FOREACH_FROM_SAFE(elem, self, key, tvar) __HYBRID_SLIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define SLIST_FOREACH_SAFE(elem, self, key, tvar)      __HYBRID_SLIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define SLIST_REMOVE(self, elem, type, key)            __HYBRID_SLIST_REMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SLIST_SWAP(l1, l2, type)                       __HYBRID_SLIST_SWAP(l1, l2, __HYBRID_Q_STRUCT type)
#endif /* !... */
#ifndef __HYBRID_LIST_RESTRICT_API
#define SLIST_HEAD_P(T)  struct { T *slh_first; /* [0..1] List head */ }
#define SLIST_ENTRY_P(T) struct { T *sle_next; /* [0..1] Next-link */ }
#define SLIST_ATOMIC_CLEAR(self)                                                           __hybrid_atomic_xch((self)->slh_first, __NULLPTR, __ATOMIC_SEQ_CST)
#define SLIST_ATOMIC_INSERT(self, elem, key)                                               __HYBRID_SLIST_ATOMIC_INSERT(self, elem, __HYBRID_Q_KEY, key)
#define SLIST_ATOMIC_INSERT_P(self, elem, getpath)                                         __HYBRID_SLIST_ATOMIC_INSERT(self, elem, __HYBRID_Q_PTH, getpath)
#define SLIST_ATOMIC_INSERT_R(self, lo_elem, hi_elem, key)                                 __HYBRID_SLIST_ATOMIC_INSERT_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define SLIST_ATOMIC_INSERT_R_P(self, lo_elem, hi_elem, getpath)                           __HYBRID_SLIST_ATOMIC_INSERT_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define SLIST_MOVE(dst, src)                                                               (void)((dst)->slh_first = (src)->slh_first, (src)->slh_first = __NULLPTR)
#define SLIST_CLEAR(self)                                                                  (void)((self)->slh_first = __NULLPTR)
#define SLIST_FOREACH_FROM_P(elem, self, getpath)                                          __HYBRID_SLIST_FOREACH_FROM(elem, self, __HYBRID_Q_PTH, getpath)
#define SLIST_FOREACH_PREVPTR_P(elem, p_elem, self, getpath)                               __HYBRID_SLIST_FOREACH_PREVPTR(elem, p_elem, self, __HYBRID_Q_PTH, getpath)
#define SLIST_FOREACH_P(elem, self, getpath)                                               __HYBRID_SLIST_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define SLIST_INSERT_AFTER_P(predecessor, elem, getpath)                                   __HYBRID_SLIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_PTH, getpath)
#define SLIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, key)                           __HYBRID_SLIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define SLIST_INSERT_AFTER_R_P(predecessor, lo_elem, hi_elem, getpath)                     __HYBRID_SLIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define SLIST_INSERT_P(self, elem, getpath)                                                __HYBRID_SLIST_INSERT(self, elem, __HYBRID_Q_PTH, getpath)
#define SLIST_INSERT_R(self, lo_elem, hi_elem, key)                                        __HYBRID_SLIST_INSERT_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define SLIST_INSERT_R_P(self, lo_elem, hi_elem, getpath)                                  __HYBRID_SLIST_INSERT_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define SLIST_NEXT_P(elem, getpath)                                                        getpath(elem).sle_next
#define SLIST_PFIRST(self)                                                                 (&(self)->slh_first)
#define SLIST_P_FOREACH(p_elem, self, key)                                                 __HYBRID_SLIST_P_FOREACH(p_elem, self, __HYBRID_Q_KEY, key)
#define SLIST_P_FOREACH_P(p_elem, self, getpath)                                           __HYBRID_SLIST_P_FOREACH(p_elem, self, __HYBRID_Q_PTH, getpath)
#define SLIST_P_INSERT_BEFORE(p_successor, elem, key)                                      __HYBRID_SLIST_P_INSERT_BEFORE(p_successor, elem, __HYBRID_Q_KEY, key)
#define SLIST_P_INSERT_BEFORE_P(p_successor, elem, getpath)                                __HYBRID_SLIST_P_INSERT_BEFORE(p_successor, elem, __HYBRID_Q_PTH, getpath)
#define SLIST_P_INSERT_BEFORE_R(p_successor, lo_elem, hi_elem, key)                        __HYBRID_SLIST_P_INSERT_BEFORE_R(p_successor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define SLIST_P_INSERT_BEFORE_R_P(p_successor, lo_elem, hi_elem, getpath)                  __HYBRID_SLIST_P_INSERT_BEFORE_R(p_successor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define SLIST_PNEXT(elem, key)                                                             (&(elem)->key.sle_next)
#define SLIST_PNEXT_P(elem, getpath)                                                       (&getpath(elem).sle_next)
#define SLIST_P_REMOVE(p_elem, key)                                                        __HYBRID_SLIST_P_REMOVE(p_elem, __HYBRID_Q_KEY, key)
#define SLIST_P_REMOVE_P(p_elem, getpath)                                                  __HYBRID_SLIST_P_REMOVE(p_elem, __HYBRID_Q_PTH, getpath)
#define SLIST_P_REMOVE_R(p_lo_elem, hi_elem, key)                                          __HYBRID_SLIST_P_REMOVE_R(p_lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define SLIST_P_REMOVE_R_P(p_lo_elem, hi_elem, getpath)                                    __HYBRID_SLIST_P_REMOVE_R(p_lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define SLIST_P_REPLACE(p_old_elem, new_elem, key)                                         __HYBRID_SLIST_P_REPLACE(p_old_elem, new_elem, __HYBRID_Q_KEY, key)
#define SLIST_P_REPLACE_P(p_old_elem, new_elem, getpath)                                   __HYBRID_SLIST_P_REPLACE(p_old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define SLIST_P_REPLACE_R(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)       __HYBRID_SLIST_P_REPLACE_R(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_KEY, key)
#define SLIST_P_REPLACE_R_P(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath) __HYBRID_SLIST_P_REPLACE_R(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_PTH, getpath)
#define SLIST_REMOVE_AFTER_P(elem, getpath)                                                __HYBRID_SLIST_REMOVE_AFTER(elem, __HYBRID_Q_PTH, getpath)
#define SLIST_REMOVE_HEAD_P(self, getpath)                                                 __HYBRID_SLIST_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#define SLIST_REMOVE_PREVPTR_P(p_elem, elem, getpath)                                      __HYBRID_SLIST_REMOVE_PREVPTR(p_elem, elem, __HYBRID_Q_PTH, getpath)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_SLIST_CONCAT_P_3(dst, src, getpath)                                                                      __HYBRID_SLIST_CONCAT(dst, src, __typeof__(*(src)->lh_first), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_CONCAT_P_4(dst, src, type, getpath)                                                                __HYBRID_SLIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_CONTAINS_4(self, elem, key, on_success)                                                            __HYBRID_SLIST_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SLIST_CONTAINS_5(self, elem, type, key, on_success)                                                      __HYBRID_SLIST_CONTAINS(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SLIST_CONTAINS_P_4(self, elem, getpath, on_success)                                                      __HYBRID_SLIST_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_SLIST_CONTAINS_P_5(self, elem, T, getpath, on_success)                                                   __HYBRID_SLIST_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_SLIST_FOREACH_FROM_SAFE_P_3(elem, self, getpath)                                                         __HYBRID_SLIST_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_FOREACH_FROM_SAFE_P_4(elem, self, getpath, tvar)                                                   __HYBRID_SLIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_SLIST_FOREACH_SAFE_P_3(elem, self, getpath)                                                              __HYBRID_SLIST_FOREACH_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_FOREACH_SAFE_P_4(elem, self, getpath, tvar)                                                        __HYBRID_SLIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_SLIST_INSERT_TAIL_3(self, elem, key)                                                                     __HYBRID_SLIST_INSERT_TAIL(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_INSERT_TAIL_4(self, elem, type, key)                                                               __HYBRID_SLIST_INSERT_TAIL(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_INSERT_TAIL_P_3(self, elem, getpath)                                                               __HYBRID_SLIST_INSERT_TAIL(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_INSERT_TAIL_P_4(self, elem, T, getpath)                                                            __HYBRID_SLIST_INSERT_TAIL(self, elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_INSERT_TAIL_R_3(self, lo_elem, hi_elem, key)                                                       __HYBRID_SLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_INSERT_TAIL_R_4(self, lo_elem, hi_elem, type, key)                                                 __HYBRID_SLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_INSERT_TAIL_R_P_3(self, lo_elem, hi_elem, getpath)                                                 __HYBRID_SLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_INSERT_TAIL_R_P_4(self, lo_elem, hi_elem, T, getpath)                                              __HYBRID_SLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_P_PREV_2(p_elem, self, key)                                                                        __HYBRID_SLIST_P_PREV3(p_elem, self, __typeof__(*(elem)), key)
#define __HYBRID_SLIST_P_PREV_3(p_elem, self, type, key)                                                                  __HYBRID_SLIST_P_PREV3(p_elem, self, __HYBRID_Q_STRUCT type, key)
#define __HYBRID_SLIST_P_PREV_P_2(p_elem, self, getpath)                                                                  __HYBRID_SLIST_P_PREV4(p_elem, self, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_P_PREV_P_3(p_elem, self, T, getpath)                                                               __HYBRID_SLIST_P_PREV4(p_elem, self, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_P_PREV_UNSAFE_2(p_elem, key)                                                                       __HYBRID_SLIST_P_PREV_UNSAFE3(p_elem, __typeof__(*(elem)), key)
#define __HYBRID_SLIST_P_PREV_UNSAFE_3(p_elem, type, key)                                                                 __HYBRID_SLIST_P_PREV_UNSAFE3(p_elem, __HYBRID_Q_STRUCT type, key)
#define __HYBRID_SLIST_P_PREV_UNSAFE_P_2(p_elem, getpath)                                                                 __HYBRID_SLIST_P_PREV_UNSAFE4(p_elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_P_PREV_UNSAFE_P_3(p_elem, T, getpath)                                                              __HYBRID_SLIST_P_PREV_UNSAFE4(p_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_REMOVEALL_5(self, out_pelem, key, condition, on_match)                                             __HYBRID_SLIST_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_SLIST_REMOVEALL_6(self, out_pelem, type, key, condition, on_match)                                       __HYBRID_SLIST_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_SLIST_REMOVEALL_P_5(self, out_pelem, getpath, condition, on_match)                                       __HYBRID_SLIST_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_SLIST_REMOVEALL_P_6(self, out_pelem, T, getpath, condition, on_match)                                    __HYBRID_SLIST_REMOVEALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_SLIST_REMOVE_IF_4(self, out_pelem, key, condition)                                                       __HYBRID_SLIST_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_SLIST_REMOVE_IF_5(self, out_pelem, type, key, condition)                                                 __HYBRID_SLIST_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_SLIST_REMOVE_IF_P_4(self, out_pelem, getpath, condition)                                                 __HYBRID_SLIST_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_SLIST_REMOVE_IF_P_5(self, out_pelem, T, getpath, condition)                                              __HYBRID_SLIST_REMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_SLIST_REMOVE_P_3(self, elem, getpath)                                                                    __HYBRID_SLIST_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_REMOVE_P_4(self, elem, T, getpath)                                                                 __HYBRID_SLIST_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_REPLACE_4(self, old_elem, new_elem, key)                                                           __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_REPLACE_5(self, old_elem, new_elem, type, key)                                                     __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_REPLACE_P_4(self, old_elem, new_elem, getpath)                                                     __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_REPLACE_P_5(self, old_elem, new_elem, T, getpath)                                                  __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_REPLACE_R_4(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)                         __HYBRID_SLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_REPLACE_R_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key)                   __HYBRID_SLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_REPLACE_R_P_4(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath)                   __HYBRID_SLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_REPLACE_R_P_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)                __HYBRID_SLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_SWAP_P_2(l1, l2)                                                                                   __HYBRID_SLIST_SWAP(l1, l2, __typeof__(*(l1)->slh_first))
#define __HYBRID_SLIST_SWAP_P_3(l1, l2, T)                                                                                __HYBRID_SLIST_SWAP(l1, l2, T)
#define __HYBRID_SLIST_TRYREMOVE_4(self, elem, key, on_failure)                                                           __HYBRID_SLIST_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_TRYREMOVE_5(self, elem, type, key, on_failure)                                                     __HYBRID_SLIST_TRYREMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_TRYREMOVE_IF_5(self, out_pelem, key, condition, on_failure)                                        __HYBRID_SLIST_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_SLIST_TRYREMOVE_IF_6(self, out_pelem, type, key, condition, on_failure)                                  __HYBRID_SLIST_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_SLIST_TRYREMOVE_IF_P_5(self, out_pelem, getpath, condition, on_failure)                                  __HYBRID_SLIST_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_SLIST_TRYREMOVE_IF_P_6(self, out_pelem, T, getpath, condition, on_failure)                               __HYBRID_SLIST_TRYREMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_SLIST_TRYREMOVE_P_4(self, elem, getpath, on_failure)                                                     __HYBRID_SLIST_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SLIST_TRYREMOVE_P_5(self, elem, T, getpath, on_failure)                                                  __HYBRID_SLIST_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_5(self, old_elem, new_elem, key, on_failure)                                            __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_6(self, old_elem, new_elem, type, key, on_failure)                                      __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_P_5(self, old_elem, new_elem, getpath, on_failure)                                      __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_P_6(self, old_elem, new_elem, T, getpath, on_failure)                                   __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_R_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key, on_failure)          __HYBRID_SLIST_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_R_6(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key, on_failure)    __HYBRID_SLIST_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_R_P_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath, on_failure)    __HYBRID_SLIST_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_R_P_6(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath, on_failure) __HYBRID_SLIST_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SLIST_CONCAT_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_CONCAT_P_, (__VA_ARGS__))(__VA_ARGS__)            /* SLIST_CONCAT_P(dst, src, [type], getpath) */
#define SLIST_CONTAINS(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_CONTAINS_, (__VA_ARGS__))(__VA_ARGS__)            /* SLIST_CONTAINS(self, elem, [type], key, on_success) */
#define SLIST_CONTAINS_P(...)          __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_CONTAINS_P_, (__VA_ARGS__))(__VA_ARGS__)          /* SLIST_CONTAINS_P(self, elem, [T], getpath, on_success) */
#define SLIST_FOREACH_FROM_SAFE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_FOREACH_FROM_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__) /* SLIST_FOREACH_FROM_SAFE_P(elem, self, getpath, [tvar]) */
#define SLIST_FOREACH_SAFE_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_FOREACH_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)      /* SLIST_FOREACH_SAFE_P(elem, self, getpath, [tvar]) */
#define SLIST_INSERT_TAIL(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_INSERT_TAIL_, (__VA_ARGS__))(__VA_ARGS__)         /* SLIST_INSERT_TAIL(self, elem, [type], key) */
#define SLIST_INSERT_TAIL_P(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_INSERT_TAIL_P_, (__VA_ARGS__))(__VA_ARGS__)       /* SLIST_INSERT_TAIL_P(self, elem, [T], getpath) */
#define SLIST_INSERT_TAIL_R(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_INSERT_TAIL_R_, (__VA_ARGS__))(__VA_ARGS__)       /* SLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, [type], key) */
#define SLIST_INSERT_TAIL_R_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_INSERT_TAIL_R_P_, (__VA_ARGS__))(__VA_ARGS__)     /* SLIST_INSERT_TAIL_R_P(self, lo_elem, hi_elem, [T], getpath) */
#define SLIST_P_PREV(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_P_PREV_, (__VA_ARGS__))(__VA_ARGS__)              /* SLIST_P_PREV(p_elem, self, [type], key) */
#define SLIST_P_PREV_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_P_PREV_P_, (__VA_ARGS__))(__VA_ARGS__)            /* SLIST_P_PREV_P(p_elem, self, [T], getpath) */
#define SLIST_P_PREV_UNSAFE(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_P_PREV_UNSAFE_, (__VA_ARGS__))(__VA_ARGS__)       /* SLIST_P_PREV_UNSAFE(p_elem, [type], key) */
#define SLIST_P_PREV_UNSAFE_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_P_PREV_UNSAFE_P_, (__VA_ARGS__))(__VA_ARGS__)     /* SLIST_P_PREV_UNSAFE_P(p_elem, [T], getpath) */
#define SLIST_REMOVEALL(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REMOVEALL_, (__VA_ARGS__))(__VA_ARGS__)           /* SLIST_REMOVEALL(self, out_pelem, [type], key, condition, on_match) */
#define SLIST_REMOVEALL_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REMOVEALL_P_, (__VA_ARGS__))(__VA_ARGS__)         /* SLIST_REMOVEALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define SLIST_REMOVE_IF(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)           /* SLIST_REMOVE_IF(self, out_pelem, [type], key, condition) */
#define SLIST_REMOVE_IF_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)         /* SLIST_REMOVE_IF_P(self, out_pelem, [T], getpath, condition) */
#define SLIST_REMOVE_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)            /* SLIST_REMOVE_P(self, elem, [T], getpath) */
#define SLIST_REPLACE(...)             __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REPLACE_, (__VA_ARGS__))(__VA_ARGS__)             /* SLIST_REPLACE(self, old_elem, new_elem, [type], key) */
#define SLIST_REPLACE_P(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)           /* SLIST_REPLACE_P(self, old_elem, new_elem, [T], getpath) */
#define SLIST_REPLACE_R(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REPLACE_R_, (__VA_ARGS__))(__VA_ARGS__)           /* SLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key) */
#define SLIST_REPLACE_R_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REPLACE_R_P_, (__VA_ARGS__))(__VA_ARGS__)         /* SLIST_REPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [T], getpath) */
#define SLIST_SWAP_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_SWAP_P_, (__VA_ARGS__))(__VA_ARGS__)              /* SLIST_SWAP_P(l1, l2, [T]) */
#define SLIST_TRYREMOVE(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREMOVE_, (__VA_ARGS__))(__VA_ARGS__)           /* SLIST_TRYREMOVE(self, elem, [type], key, on_failure) */
#define SLIST_TRYREMOVE_IF(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)        /* SLIST_TRYREMOVE_IF(self, out_pelem, [type], key, condition, on_failure) */
#define SLIST_TRYREMOVE_IF_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)      /* SLIST_TRYREMOVE_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#define SLIST_TRYREMOVE_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)         /* SLIST_TRYREMOVE_P(self, elem, [T], getpath, on_failure) */
#define SLIST_TRYREPLACE(...)          __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREPLACE_, (__VA_ARGS__))(__VA_ARGS__)          /* SLIST_TRYREPLACE(self, old_elem, new_elem, [type], key, on_success) */
#define SLIST_TRYREPLACE_P(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)        /* SLIST_TRYREPLACE_P(self, old_elem, new_elem, [T], getpath, on_success) */
#define SLIST_TRYREPLACE_R(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREPLACE_R_, (__VA_ARGS__))(__VA_ARGS__)        /* SLIST_TRYREPLACE(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key, on_success) */
#define SLIST_TRYREPLACE_R_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREPLACE_R_P_, (__VA_ARGS__))(__VA_ARGS__)      /* SLIST_TRYREPLACE_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [T], getpath, on_success) */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define SLIST_CONCAT_P(dst, src, type, getpath)                                                                __HYBRID_SLIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define SLIST_CONTAINS(self, elem, type, key, on_success)                                                      __HYBRID_SLIST_CONTAINS(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath, on_success)
#define SLIST_CONTAINS_P(self, elem, T, getpath, on_success)                                                   __HYBRID_SLIST_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define SLIST_FOREACH_FROM_SAFE_P(elem, self, getpath, tvar)                                                   __HYBRID_SLIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define SLIST_FOREACH_SAFE_P(elem, self, getpath, tvar)                                                        __HYBRID_SLIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define SLIST_INSERT_TAIL(self, elem, type, key)                                                               __HYBRID_SLIST_INSERT_TAIL(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SLIST_INSERT_TAIL_P(self, elem, T, getpath)                                                            __HYBRID_SLIST_INSERT_TAIL(self, elem, T, __HYBRID_Q_PTH, getpath)
#define SLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, type, key)                                                 __HYBRID_SLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SLIST_INSERT_TAIL_R_P(self, lo_elem, hi_elem, T, getpath)                                              __HYBRID_SLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, T, __HYBRID_Q_PTH, getpath)
#define SLIST_P_PREV(p_elem, self, T, key)                                                                     __HYBRID_SLIST_P_PREV3(p_elem, self, __HYBRID_Q_STRUCT type, key)
#define SLIST_P_PREV_P(p_elem, self, T, getpath)                                                               __HYBRID_SLIST_P_PREV4(p_elem, self, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define SLIST_P_PREV_UNSAFE(p_elem, T, key)                                                                    __HYBRID_SLIST_P_PREV_UNSAFE3(p_elem, __HYBRID_Q_STRUCT type, key)
#define SLIST_P_PREV_UNSAFE_P(p_elem, T, getpath)                                                              __HYBRID_SLIST_P_PREV_UNSAFE4(p_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define SLIST_REMOVEALL(self, out_pelem, type, key, condition, on_match)                                       __HYBRID_SLIST_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define SLIST_REMOVEALL_P(self, out_pelem, type, getpath, condition, on_match)                                 __HYBRID_SLIST_REMOVEALL(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_match)
#define SLIST_REMOVE_IF(self, out_pelem, type, key, condition)                                                 __HYBRID_SLIST_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define SLIST_REMOVE_IF_P(self, out_pelem, type, getpath, condition)                                           __HYBRID_SLIST_REMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition)
#define SLIST_REMOVE_P(self, elem, T, getpath)                                                                 __HYBRID_SLIST_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define SLIST_REPLACE(self, old_elem, new_elem, type, key)                                                     __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SLIST_REPLACE_P(self, old_elem, new_elem, T, getpath)                                                  __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define SLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key)                   __HYBRID_SLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SLIST_REPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)                __HYBRID_SLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define SLIST_SWAP_P(l1, l2, T)                                                                                __HYBRID_SLIST_SWAP(l1, l2, T)
#define SLIST_TRYREMOVE(self, elem, type, key, on_failure)                                                     __HYBRID_SLIST_TRYREMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath, on_failure)
#define SLIST_TRYREMOVE_IF(self, out_pelem, type, key, condition, on_failure)                                  __HYBRID_SLIST_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define SLIST_TRYREMOVE_IF_P(self, out_pelem, type, getpath, condition, on_failure)                            __HYBRID_SLIST_TRYREMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define SLIST_TRYREMOVE_P(self, elem, T, getpath, on_failure)                                                  __HYBRID_SLIST_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SLIST_TRYREPLACE(self, old_elem, new_elem, type, key, on_failure)                                      __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define SLIST_TRYREPLACE_P(self, old_elem, new_elem, T, getpath, on_failure)                                   __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SLIST_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key, on_failure)    __HYBRID_SLIST_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define SLIST_TRYREPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath, on_failure) __HYBRID_SLIST_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_SLIST_CONCAT(dst, src, T, X, _)                     \
	/* Sorry, this one must be a statement */                        \
	do {                                                             \
		if ((src)->slh_first != __NULLPTR) {                         \
			T **__hslc_dst_last = &(dst)->slh_first;                 \
			while (*__hslc_dst_last)                                 \
				__hslc_dst_last = &X(_, *__hslc_dst_last)->sle_next; \
			*__hslc_dst_last  = (src)->slh_first;                    \
			(src)->slh_first = __NULLPTR;                            \
		}                                                            \
	}	__WHILE0
#define __HYBRID_SLIST_SWAP(l1, l2, T)        \
	/* Sorry, this one must be a statement */ \
	do {                                      \
		T *__hsls_tmp   = (l1)->slh_first;    \
		(l1)->slh_first = (l2)->slh_first;    \
		(l2)->slh_first = __hsls_tmp;         \
	}	__WHILE0
#define __HYBRID_SLIST_INSERT_AFTER(predecessor, elem, X, _) \
	__HYBRID_SLIST_INSERT_AFTER_R(predecessor, elem, elem, X, _)
#define __HYBRID_SLIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, X, _) \
	(void)(X(_, hi_elem).sle_next     = X(_, predecessor).sle_next,        \
	       X(_, predecessor).sle_next = (lo_elem))
#define __HYBRID_SLIST_INSERT(self, elem, X, _) \
	__HYBRID_SLIST_INSERT_R(self, elem, elem, X, _)
#define __HYBRID_SLIST_INSERT_R(self, lo_elem, hi_elem, X, _) \
	(void)(X(_, hi_elem).sle_next = (self)->slh_first,        \
	       (self)->slh_first      = (lo_elem))
#define __HYBRID_SLIST_ATOMIC_INSERT(self, elem, X, _) \
	__HYBRID_SLIST_ATOMIC_INSERT_R(self, elem, elem, X, _)
#define __HYBRID_SLIST_ATOMIC_INSERT_R(self, lo_elem, hi_elem, X, _)                        \
	/* Sorry, this one must be a statement */                                               \
	do {                                                                                    \
		X(_, hi_elem).sle_next = __hybrid_atomic_load((self)->slh_first, __ATOMIC_ACQUIRE); \
		__COMPILER_WRITE_BARRIER();                                                         \
	} while (!__hybrid_atomic_cmpxch((self)->slh_first, X(_, hi_elem).sle_next, lo_elem,    \
	                                 __ATOMIC_RELEASE, __ATOMIC_RELAXED))
#define __HYBRID_SLIST_REMOVE_HEAD(self, X, _) \
	(void)((self)->slh_first = X(_, (self)->slh_first).sle_next)
#define __HYBRID_SLIST_REMOVE_PREVPTR(p_elem, elem, X, _) \
	(void)(__HYBRID_Q_ASSERT_(*(p_elem) == (elem)) *(p_elem) = X(_, elem).sle_next)
#define __HYBRID_SLIST_REMOVE_AFTER(elem, X, _) \
	(void)(X(_, elem).sle_next = X(_, X(_, elem).sle_next).sle_next)
#define __HYBRID_SLIST_REMOVE(self, elem, T, X, _)        \
	/* Sorry, this one must be a statement */             \
	do {                                                  \
		T **__hslr_piter = &(self)->slh_first;            \
		while (*__hslr_piter != (elem))                   \
			__hslr_piter = &X(_, *__hslr_piter).sle_next; \
		*__hslr_piter = X(_, elem).sle_next;              \
		__HYBRID_Q_BADPTR(X(_, elem).sle_next);           \
	}	__WHILE0
#define __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, T, X, _) \
	__HYBRID_SLIST_REPLACE_R(self, old_elem, old_elem, new_elem, new_elem, T, X, _)
#define __HYBRID_SLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, X, _) \
	/* Sorry, this one must be a statement */                                                       \
	do {                                                                                            \
		T **__hslrr_piter = &(self)->slh_first;                                                     \
		while (*__hslrr_piter != (old_lo_elem))                                                     \
			__hslrr_piter = &X(_, *__hslrr_piter).sle_next;                                         \
		X(_, new_hi_elem).sle_next = X(_, old_hi_elem).sle_next;                                    \
		*__hslrr_piter                   = (new_lo_elem);                                           \
		__HYBRID_Q_BADPTR(X(_, old_hi_elem).sle_next);                                              \
	}	__WHILE0
#define __HYBRID_SLIST_TRYREMOVE(self, elem, T, X, _, on_failure)       \
	/* Sorry, this one must be a statement */                           \
	do {                                                                \
		T **__hsltr_piter = &(self)->slh_first;                         \
		while (*__hsltr_piter != __NULLPTR && *__hsltr_piter != (elem)) \
			__hsltr_piter = &X(_, *__hsltr_piter).sle_next;             \
		if (*__hsltr_piter != __NULLPTR) {                              \
			*__hsltr_piter = X(_, elem).sle_next;                       \
			__HYBRID_Q_BADPTR(X(_, elem).sle_next);                     \
		} else {                                                        \
			on_failure;                                                 \
		}                                                               \
	}	__WHILE0
#define __HYBRID_SLIST_CONTAINS(self, elem, T, X, _, on_success) \
	/* Sorry, this one must be a statement */                    \
	do {                                                         \
		T *__hslc_iter = (self)->slh_first;                      \
		while (__hslc_iter != __NULLPTR) {                       \
			if (__hslc_iter == (elem)) {                         \
				on_success;                                      \
				break;                                           \
			}                                                    \
			__hslc_iter = X(_, __hslc_iter).sle_next;            \
		}                                                        \
	}	__WHILE0
#define __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, T, X, _, on_failure) \
	__HYBRID_SLIST_TRYREPLACE_R(self, old_elem, old_elem, new_elem, new_elem, T, X, _, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, X, _, on_failure) \
	/* Sorry, this one must be a statement */                                                                      \
	do {                                                                                                           \
		T **__hsltrr_piter = &(self)->slh_first;                                                                   \
		for (;;) {                                                                                                 \
			if (*__hsltrr_piter == __NULLPTR) {                                                                    \
				on_failure;                                                                                        \
				break;                                                                                             \
			}                                                                                                      \
			if (*__hsltrr_piter == (old_lo_elem)) {                                                                \
				X(_, new_hi_elem).sle_next = X(_, old_hi_elem).sle_next;                                           \
				*__hsltrr_piter            = (new_lo_elem);                                                        \
				__HYBRID_Q_BADPTR(X(_, old_hi_elem).sle_next);                                                     \
				break;                                                                                             \
			}                                                                                                      \
		}                                                                                                          \
	}	__WHILE0
#define __HYBRID_SLIST_INSERT_TAIL(self, elem, T, X, _) \
	__HYBRID_SLIST_INSERT_TAIL_R(self, elem, elem, T, X, _)
#define __HYBRID_SLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, T, X, _) \
	/* Sorry, this one must be a statement */                         \
	do {                                                              \
		T **__hslitr_piter = &(self)->slh_first;                      \
		while (*__hslitr_piter != __NULLPTR)                          \
			__hslitr_piter = &X(_, *__hslitr_piter).sle_next;         \
		*__hslitr_piter              = (lo_elem);                     \
		X(_, hi_elem).le_next = __NULLPTR;                            \
	}	__WHILE0
#define __HYBRID_SLIST_REMOVE_IF(self, out_pelem, T, X, _, condition) \
	/* Sorry, this one must be a statement */                         \
	do {                                                              \
		T **__hslri_piter = &(self)->slh_first;                       \
		for (;;) {                                                    \
			*(out_pelem) = *__hslri_piter;                            \
			if (condition)                                            \
				break;                                                \
			__hslri_piter = &X(_, *(out_pelem)).sle_next;             \
		}                                                             \
		*__hslri_piter = X(_, *(out_pelem)).sle_next;                 \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).sle_next);               \
	}	__WHILE0
#define __HYBRID_SLIST_TRYREMOVE_IF(self, out_pelem, T, X, _, condition, on_failure) \
	/* Sorry, this one must be a statement */                                        \
	do {                                                                             \
		T **__hsltri_piter = &(self)->slh_first;                                     \
		for (;;) {                                                                   \
			if ((*(out_pelem) = *__hsltri_piter) == __NULLPTR) {                     \
				on_failure;                                                          \
				break;                                                               \
			}                                                                        \
			if (condition) {                                                         \
				*__hsltri_piter = X(_, *(out_pelem)).sle_next;                       \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).sle_next);                      \
				break;                                                               \
			}                                                                        \
			__hsltri_piter = &X(_, *(out_pelem)).sle_next;                           \
		}                                                                            \
	}	__WHILE0
#define __HYBRID_SLIST_REMOVEALL(self, out_pelem, T, X, _, condition, on_match) \
	/* Sorry, this one must be a statement */                                   \
	do {                                                                        \
		T **__hslra_piter = &(self)->slh_first;                                 \
		while ((*(out_pelem) = *__hslra_piter) != __NULLPTR) {                  \
			if (condition) {                                                    \
				*__hslra_piter = X(_, *(out_pelem)).sle_next;                   \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).sle_next);                 \
				on_match;                                                       \
			} else {                                                            \
				__hslra_piter = &X(_, *(out_pelem)).sle_next;                   \
			}                                                                   \
		}                                                                       \
	}	__WHILE0
#if (defined(NDEBUG) || defined(NDEBUG_QUEUE) || \
     !defined(__COMPILER_HAVE_TYPEOF) || defined(__NO_XBLOCK))
#define __HYBRID_SLIST_P_REMOVE(p_elem, X, _) \
	(void)(*(p_elem) = X(_, *(p_elem)).sle_next)
#else /* ... */
#define __HYBRID_SLIST_P_REMOVE(p_elem, X, _)                  \
	__XBLOCK({                                                 \
		__typeof__(*(p_elem)) __hslpr_elem = *(p_elem);        \
		__HYBRID_SLIST_P_REMOVE_R(p_elem, __hslpr_elem, X, _); \
	})
#endif /* !... */
#define __HYBRID_SLIST_P_REMOVE_R(p_lo_elem, hi_elem, X, _) \
	(void)(*(p_lo_elem) = X(_, hi_elem).sle_next,           \
	       __HYBRID_Q_BADPTR(X(_, hi_elem).sle_next))
#define __HYBRID_SLIST_P_INSERT_BEFORE(p_successor, elem, X, _) \
	__HYBRID_SLIST_P_INSERT_BEFORE_R(p_successor, elem, elem, X, _)
#define __HYBRID_SLIST_P_INSERT_BEFORE_R(p_successor, lo_elem, hi_elem, X, _) \
	(void)(X(_, hi_elem).sle_next = *(p_successor), *(p_successor) = (lo_elem))
#define __HYBRID_SLIST_P_REPLACE(p_old_elem, new_elem, X, _) \
	__HYBRID_SLIST_P_REPLACE_R(p_old_elem, *(p_old_elem), new_elem, new_elem, X, _)
#define __HYBRID_SLIST_P_REPLACE_R(p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, X, _) \
	(void)(X(_, new_hi_elem).sle_next = X(_, old_hi_elem).sle_next,                            \
	       *(p_old_lo_elem)           = (new_lo_elem))
#define __HYBRID_SLIST_P_PREV3(p_elem, self, T, key) \
	((p_elem) == &(self)->slh_first ? __NULLPTR : __COMPILER_CONTAINER_OF(p_elem, T, key.sle_next))
#define __HYBRID_SLIST_P_PREV4(p_elem, self, T, X, _) \
	((p_elem) == &(self)->slh_first ? __NULLPTR : (T *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&X(_, (T *)0).sle_next))
#define __HYBRID_SLIST_P_PREV_UNSAFE3(p_elem, T, key) \
	__COMPILER_CONTAINER_OF(p_elem, T, key.sle_next)
#define __HYBRID_SLIST_P_PREV_UNSAFE4(p_elem, T, X, _) \
	((T *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&X(_, (T *)0).sle_next))
#define __HYBRID_SLIST_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->slh_first; (elem); (elem) = X(_, elem).sle_next)
#define __HYBRID_SLIST_FOREACH_FROM(elem, self, X, _) \
	for ((elem) ? (void)0 : (void)((elem) = (self)->slh_first); (elem); (elem) = X(_, elem).sle_next)
#define __HYBRID_SLIST_FOREACH_PREVPTR(elem, p_elem, self, X, _) \
	for ((p_elem) = &(self); ((elem) = *(p_elem)) != __NULLPTR;  \
	     (p_elem) = &X(_, elem).sle_next)
#define __HYBRID_SLIST_P_FOREACH(p_elem, self, X, _) \
	for ((p_elem) = &(self)->slh_first; *(p_elem); (p_elem) = &X(_, *(p_elem)).sle_next)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_SLIST_FOREACH_SAFE3(elem, self, X, _)          \
	if (((elem) = (self)->slh_first, 0))                        \
		;                                                       \
	else                                                        \
		for (__typeof__(elem) __hslfs_tvar;                     \
		     (elem) && (__hslfs_tvar = X(_, elem).sle_next, 1); \
		     (elem) = __hslfs_tvar)
#define __HYBRID_SLIST_FOREACH_FROM_SAFE3(elem, self, X, _)         \
	if (((elem) ? (void)0 : (void)((elem) = (self)->slh_first), 0)) \
		;                                                           \
	else                                                            \
		for (__typeof__(elem) __hslfs_tvar;                         \
		     (elem) && (__hslfs_tvar = X(_, elem).sle_next, 1);     \
		     (elem) = __hslfs_tvar)
#endif /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define __HYBRID_SLIST_FOREACH_SAFE4(elem, self, X, _, tvar) \
	for ((elem) = (head)->slh_first;                         \
	     (elem) && ((tvar) = X(_, elem).sle_next, 1);        \
	     (elem) = (tvar))
#define __HYBRID_SLIST_FOREACH_FROM_SAFE4(elem, self, X, _, tvar) \
	for ((elem) ? (void)0 : (void)((elem) = (head)->slh_first);   \
	     (elem) && ((tvar) = X(_, elem).sle_next, 1);             \
	     (elem) = (tvar))






/************************************************************************/
/* Double-head, singly-linked Tail queue.                               */
/************************************************************************/
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef STAILQ_HEAD
#undef STAILQ_CLASS_HEAD
#define __HYBRID_STAILQ_HEAD_1(type)                                                            \
	struct {                                                                                    \
		__HYBRID_Q_STRUCT type *stqh_first, /* [0..1] List head */                              \
		**stqh_last;                        /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_STAILQ_HEAD_2(name, type)                                                      \
	struct name {                                                                               \
		__HYBRID_Q_STRUCT type *stqh_first, /* [0..1] List head */                              \
		**stqh_last;                        /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_STAILQ_CLASS_HEAD_1(type)                                                     \
	struct {                                                                                   \
		__HYBRID_Q_CLASS type *stqh_first, /* [0..1] List head */                              \
		**stqh_last;                       /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_STAILQ_CLASS_HEAD_2(name, type)                                               \
	struct name {                                                                              \
		__HYBRID_Q_CLASS type *stqh_first, /* [0..1] List head */                              \
		**stqh_last;                       /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define STAILQ_HEAD(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_HEAD_, (__VA_ARGS__))(__VA_ARGS__)       /* STAILQ_HEAD([name], type) */
#define STAILQ_CLASS_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_CLASS_HEAD_, (__VA_ARGS__))(__VA_ARGS__) /* STAILQ_CLASS_HEAD([name], type) */
#else /* ... */
#define STAILQ_HEAD(name, type)                                                                 \
	struct name {                                                                               \
		__HYBRID_Q_STRUCT type *stqh_first, /* [0..1] List head */                              \
		**stqh_last;                        /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define STAILQ_CLASS_HEAD(name, type)                                                          \
	struct name {                                                                              \
		__HYBRID_Q_CLASS type *stqh_first, /* [0..1] List head */                              \
		**stqh_last;                       /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#endif /* !__HYBRID_LIST_RESTRICT_API */
#define STAILQ_ENTRY(type)       struct { __HYBRID_Q_STRUCT type *stqe_next; /* [0..1] Next element */ }
#define STAILQ_CLASS_ENTRY(type) struct { __HYBRID_Q_CLASS  type *stqe_next; /* [0..1] Next element */ }
#define STAILQ_CONCAT(dst, src)                      \
	((src)->stqh_first != __NULLPTR                  \
	 ? (void)(*(dst)->stqh_last = (src)->stqh_first, \
	          (dst)->stqh_last  = (src)->stqh_last,  \
	          STAILQ_INIT(src))                      \
	 : (void)0)
#define STAILQ_EMPTY(self)                                ((self)->stqh_first == __NULLPTR)
#define STAILQ_END(self)                                  __NULLPTR
#define STAILQ_FIRST(self)                                (self)->stqh_first
#define STAILQ_FOREACH(elem, self, key)                   __HYBRID_STAILQ_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define STAILQ_FOREACH_FROM(elem, self, key)              __HYBRID_STAILQ_FOREACH_FROM(elem, self, __HYBRID_Q_KEY, key)
#define STAILQ_HEAD_INITIALIZER(self)                     { __NULLPTR, &(self).stqh_first }
#define STAILQ_INIT(self)                                 (void)(*((self)->stqh_last = &(self)->stqh_first) = __NULLPTR)
#define STAILQ_INSERT_AFTER(self, predecessor, elem, key) __HYBRID_STAILQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_KEY, key)
#define STAILQ_INSERT_HEAD(self, elem, key)               __HYBRID_STAILQ_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define STAILQ_INSERT_TAIL(self, elem, key)               __HYBRID_STAILQ_INSERT_TAIL(self, elem, __HYBRID_Q_KEY, key)
#define STAILQ_NEXT(elem, key)                            (elem)->key.stqe_next
#define STAILQ_REMOVE_AFTER(self, elem, key)              __HYBRID_STAILQ_REMOVE_AFTER(self, elem, __HYBRID_Q_KEY, key)
#define STAILQ_REMOVE_HEAD(self, key)                     __HYBRID_STAILQ_REMOVE_HEAD(self, __HYBRID_Q_KEY, key)
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_STAILQ_FOREACH_FROM_SAFE_3(elem, self, key)       __HYBRID_STAILQ_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_FOREACH_FROM_SAFE_4(elem, self, key, tvar) __HYBRID_STAILQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_STAILQ_FOREACH_SAFE_3(elem, self, key)            __HYBRID_STAILQ_FOREACH_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_FOREACH_SAFE_4(elem, self, key, tvar)      __HYBRID_STAILQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_STAILQ_LAST_2(self, key)                          __HYBRID_STAILQ_LAST(self, __typeof__(*(self)->stqh_first), key)
#define __HYBRID_STAILQ_LAST_3(self, type, key)                    __HYBRID_STAILQ_LAST(self, __HYBRID_Q_STRUCT type, key)
#define __HYBRID_STAILQ_REMOVE_3(self, elem, key)                  __HYBRID_STAILQ_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_REMOVE_4(self, elem, type, key)            __HYBRID_STAILQ_REMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_SWAP_2(l1, l2)                             __HYBRID_STAILQ_SWAP(l1, l2, __typeof__(*(l1)->stqh_first))
#define __HYBRID_STAILQ_SWAP_3(l1, l2, type)                       __HYBRID_STAILQ_SWAP(l1, l2, __HYBRID_Q_STRUCT type)
#undef STAILQ_FOREACH_FROM_SAFE
#undef STAILQ_FOREACH_SAFE
#undef STAILQ_LAST
#undef STAILQ_REMOVE
#undef STAILQ_SWAP
#define STAILQ_FOREACH_FROM_SAFE(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_FOREACH_FROM_SAFE_, (__VA_ARGS__))(__VA_ARGS__) /* STAILQ_FOREACH_FROM_SAFE(elem, self, key, [tvar]) */
#define STAILQ_FOREACH_SAFE(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_FOREACH_SAFE_, (__VA_ARGS__))(__VA_ARGS__)      /* STAILQ_FOREACH_SAFE(elem, self, key, [tvar]) */
#define STAILQ_LAST(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_LAST_, (__VA_ARGS__))(__VA_ARGS__)              /* STAILQ_LAST(self, [type], key) */
#define STAILQ_REMOVE(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REMOVE_, (__VA_ARGS__))(__VA_ARGS__)            /* STAILQ_REMOVE(self, elem, [type], key) */
#define STAILQ_SWAP(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_SWAP_, (__VA_ARGS__))(__VA_ARGS__)              /* STAILQ_SWAP(l1, l2, [type]) */
#else /* !__HYBRID_LIST_RESTRICT_API && __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define STAILQ_FOREACH_FROM_SAFE(elem, self, key, tvar) __HYBRID_STAILQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define STAILQ_FOREACH_SAFE(elem, self, key, tvar)      __HYBRID_STAILQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define STAILQ_LAST(self, type, key)                    __HYBRID_STAILQ_LAST(self, __HYBRID_Q_STRUCT type, key)
#define STAILQ_REMOVE(self, elem, type, key)            __HYBRID_STAILQ_REMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define STAILQ_SWAP(l1, l2, type)                       __HYBRID_STAILQ_SWAP(l1, l2, __HYBRID_Q_STRUCT type)
#endif /* __HYBRID_LIST_RESTRICT_API || !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#ifndef __HYBRID_LIST_RESTRICT_API
#define STAILQ_ENTRY_P(T) struct { T *stqe_next; /* [0..1] Next element */ }
#define STAILQ_HEAD_P(T)                                                   \
	struct {                                                               \
		T *stqh_first, /* [0..1] List head */                              \
		**stqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define STAILQ_CLEAR(self)                                                    (void)(*((self)->stqh_last = &(self)->stqh_first) = __NULLPTR)
#define STAILQ_FOREACH_FROM_P(elem, self, getpath)                            __HYBRID_STAILQ_FOREACH_FROM(elem, self, __HYBRID_Q_PTH, getpath)
#define STAILQ_FOREACH_P(elem, self, getpath)                                 __HYBRID_STAILQ_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define STAILQ_INSERT_AFTER_P(self, predecessor, elem, getpath)               __HYBRID_STAILQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, getpath)   __HYBRID_STAILQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define STAILQ_INSERT_AFTER_R_P(self, predecessor, lo_elem, hi_elem, getpath) __HYBRID_STAILQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_INSERT_HEAD_P(self, elem, getpath)                             __HYBRID_STAILQ_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_INSERT_HEAD_R(self, lo_elem, hi_elem, key)                     __HYBRID_STAILQ_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define STAILQ_INSERT_HEAD_R_P(self, lo_elem, hi_elem, getpath)               __HYBRID_STAILQ_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_INSERT_TAIL_P(self, elem, getpath)                             __HYBRID_STAILQ_INSERT_TAIL(self, elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_INSERT_TAIL_R(self, lo_elem, hi_elem, key)                     __HYBRID_STAILQ_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define STAILQ_INSERT_TAIL_R_P(self, lo_elem, hi_elem, getpath)               __HYBRID_STAILQ_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_NEXT_P(elem, getpath)                                          getpath(elem).stqe_next
#define STAILQ_PFIRST(self)                                                   (&(self)->stqh_first)
#define STAILQ_P_FOREACH(p_elem, self, key)                                   __HYBRID_STAILQ_P_FOREACH(p_elem, self, __HYBRID_Q_KEY, key)
#define STAILQ_P_FOREACH_P(p_elem, self, getpath)                             __HYBRID_STAILQ_P_FOREACH(p_elem, self, __HYBRID_Q_PTH, getpath)
#define STAILQ_PNEXT(elem, key)                                               (&(elem)->key.stqe_next)
#define STAILQ_PNEXT_P(elem, key)                                             (&getpath(elem).stqe_next)
#define STAILQ_P_REMOVE(self, p_elem, key)                                    __HYBRID_STAILQ_P_REMOVE(self, p_elem, __HYBRID_Q_KEY, key)
#define STAILQ_P_REMOVE_P(self, p_elem, getpath)                              __HYBRID_STAILQ_P_REMOVE(self, p_elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_P_REMOVE_R(self, p_lo_elem, hi_elem, key)                      __HYBRID_STAILQ_P_REMOVE_R(self, p_lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define STAILQ_P_REMOVE_R_P(self, p_lo_elem, hi_elem, getpath)                __HYBRID_STAILQ_P_REMOVE_R(self, p_lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_REMOVE_AFTER_P(self, elem, getpath)                            __HYBRID_STAILQ_REMOVE_AFTER(self, elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_REMOVE_HEAD_P(self, getpath)                                   __HYBRID_STAILQ_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#define STAILQ_MOVE(dst, src)                                   \
	(void)((dst)->stqh_last = (src)->stqh_last,                 \
	       ((dst)->stqh_first = (src)->stqh_first) == __NULLPTR \
	       ? (void)((dst)->stqh_last = &(dst)->stqh_first)      \
	       : (void)0,                                           \
	       (src)->stqh_first = __NULLPTR,                       \
	       (src)->stqh_last  = &(src)->stqh_first)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_STAILQ_CONTAINS_4(self, elem, key, on_success)                                                            __HYBRID_STAILQ_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_STAILQ_CONTAINS_5(self, elem, type, key, on_success)                                                      __HYBRID_STAILQ_CONTAINS(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_STAILQ_CONTAINS_P_4(self, elem, getpath, on_success)                                                      __HYBRID_STAILQ_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_STAILQ_CONTAINS_P_5(self, elem, T, getpath, on_success)                                                   __HYBRID_STAILQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_STAILQ_FOREACH_FROM_SAFE_P_3(elem, self, getpath)                                                         __HYBRID_STAILQ_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_FOREACH_FROM_SAFE_P_4(elem, self, getpath, tvar)                                                   __HYBRID_STAILQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_STAILQ_FOREACH_SAFE_P_3(elem, self, getpath)                                                              __HYBRID_STAILQ_FOREACH_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_FOREACH_SAFE_P_4(elem, self, getpath, tvar)                                                        __HYBRID_STAILQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_STAILQ_LAST_P_2(self, getpath)                                                                            __HYBRID_STAILQ_LAST_P(self, __typeof__(*(self)->stqh_first), getpath)
#define __HYBRID_STAILQ_LAST_P_3(self, T, getpath)                                                                         __HYBRID_STAILQ_LAST_P(self, T, getpath)
#define __HYBRID_STAILQ_P_PREV_2(p_elem, self, key)                                                                        __HYBRID_STAILQ_P_PREV3(p_elem, self, __typeof__(*(elem)), key)
#define __HYBRID_STAILQ_P_PREV_3(p_elem, self, type, key)                                                                  __HYBRID_STAILQ_P_PREV3(p_elem, self, __HYBRID_Q_STRUCT type, key)
#define __HYBRID_STAILQ_P_PREV_P_2(p_elem, self, getpath)                                                                  __HYBRID_STAILQ_P_PREV4(p_elem, self, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_P_PREV_P_3(p_elem, self, T, getpath)                                                               __HYBRID_STAILQ_P_PREV4(p_elem, self, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_P_PREV_UNSAFE_2(p_elem, key)                                                                       __HYBRID_STAILQ_P_PREV_UNSAFE3(p_elem, __typeof__(*(elem)), key)
#define __HYBRID_STAILQ_P_PREV_UNSAFE_3(p_elem, type, key)                                                                 __HYBRID_STAILQ_P_PREV_UNSAFE3(p_elem, __HYBRID_Q_STRUCT type, key)
#define __HYBRID_STAILQ_P_PREV_UNSAFE_P_2(p_elem, getpath)                                                                 __HYBRID_STAILQ_P_PREV_UNSAFE4(p_elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_P_PREV_UNSAFE_P_3(p_elem, T, getpath)                                                              __HYBRID_STAILQ_P_PREV_UNSAFE4(p_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_P_REPLACE_4(self, p_old_elem, new_elem, key)                                                       __HYBRID_STAILQ_P_REPLACE(self, p_old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_P_REPLACE_P_4(self, p_old_elem, new_elem, getpath)                                                 __HYBRID_STAILQ_P_REPLACE(self, p_old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_P_REPLACE_P_5(self, p_old_elem, new_elem, T, getpath)                                              __HYBRID_STAILQ_P_REPLACE(self, p_old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_P_REPLACE_R_4(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)                     __HYBRID_STAILQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_P_REPLACE_R_P_4(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath)               __HYBRID_STAILQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_P_REPLACE_R_P_5(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)            __HYBRID_STAILQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_REMOVEALL_5(self, out_pelem, key, condition, on_match)                                             __HYBRID_STAILQ_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_STAILQ_REMOVEALL_6(self, out_pelem, type, key, condition, on_match)                                       __HYBRID_STAILQ_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_STAILQ_REMOVEALL_P_5(self, out_pelem, getpath, condition, on_match)                                       __HYBRID_STAILQ_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_STAILQ_REMOVEALL_P_6(self, out_pelem, T, getpath, condition, on_match)                                    __HYBRID_STAILQ_REMOVEALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_STAILQ_REMOVE_IF_4(self, out_pelem, key, condition)                                                       __HYBRID_STAILQ_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_STAILQ_REMOVE_IF_5(self, out_pelem, type, key, condition)                                                 __HYBRID_STAILQ_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_STAILQ_REMOVE_IF_P_4(self, out_pelem, getpath, condition)                                                 __HYBRID_STAILQ_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_STAILQ_REMOVE_IF_P_5(self, out_pelem, T, getpath, condition)                                              __HYBRID_STAILQ_REMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_STAILQ_REMOVE_P_3(self, elem, getpath)                                                                    __HYBRID_STAILQ_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_REMOVE_P_4(self, elem, T, getpath)                                                                 __HYBRID_STAILQ_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_REPLACE_4(self, old_elem, new_elem, key)                                                           __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_REPLACE_5(self, old_elem, new_elem, type, key)                                                     __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_REPLACE_P_4(self, old_elem, new_elem, getpath)                                                     __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_REPLACE_P_5(self, old_elem, new_elem, T, getpath)                                                  __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_REPLACE_R_4(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)                         __HYBRID_STAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_REPLACE_R_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key)                   __HYBRID_STAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_REPLACE_R_P_4(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath)                   __HYBRID_STAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_REPLACE_R_P_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)                __HYBRID_STAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_SWAP_P_2(l1, l2)                                                                                   __HYBRID_STAILQ_SWAP(l1, l2, __typeof__(*(l1)->stqh_first))
#define __HYBRID_STAILQ_SWAP_P_3(l1, l2, T)                                                                                __HYBRID_STAILQ_SWAP(l1, l2, T)
#define __HYBRID_STAILQ_TRYREMOVE_4(self, elem, key, on_failure)                                                           __HYBRID_STAILQ_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_TRYREMOVE_5(self, elem, type, key, on_failure)                                                     __HYBRID_STAILQ_TRYREMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_TRYREMOVE_IF_5(self, out_pelem, key, condition, on_failure)                                        __HYBRID_STAILQ_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_STAILQ_TRYREMOVE_IF_6(self, out_pelem, type, key, condition, on_failure)                                  __HYBRID_STAILQ_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_STAILQ_TRYREMOVE_IF_P_5(self, out_pelem, getpath, condition, on_failure)                                  __HYBRID_STAILQ_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_STAILQ_TRYREMOVE_IF_P_6(self, out_pelem, T, getpath, condition, on_failure)                               __HYBRID_STAILQ_TRYREMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_STAILQ_TRYREMOVE_P_4(self, elem, getpath, on_failure)                                                     __HYBRID_STAILQ_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_STAILQ_TRYREMOVE_P_5(self, elem, T, getpath, on_failure)                                                  __HYBRID_STAILQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_5(self, old_elem, new_elem, key, on_failure)                                            __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_6(self, old_elem, new_elem, type, key, on_failure)                                      __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_P_5(self, old_elem, new_elem, getpath, on_failure)                                      __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_P_6(self, old_elem, new_elem, T, getpath, on_failure)                                   __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_R_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key, on_failure)          __HYBRID_STAILQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_R_6(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key, on_failure)    __HYBRID_STAILQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_R_P_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath, on_failure)    __HYBRID_STAILQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_R_P_6(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath, on_failure) __HYBRID_STAILQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define STAILQ_CONTAINS(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_CONTAINS_, (__VA_ARGS__))(__VA_ARGS__)            /* STAILQ_CONTAINS(self, elem, [type], key, on_success) */
#define STAILQ_CONTAINS_P(...)          __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_CONTAINS_P_, (__VA_ARGS__))(__VA_ARGS__)          /* STAILQ_CONTAINS_P(self, elem, [T], getpath, on_success) */
#define STAILQ_FOREACH_FROM_SAFE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_FOREACH_FROM_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__) /* STAILQ_FOREACH_FROM_SAFE_P(elem, self, getpath, [tvar]) */
#define STAILQ_FOREACH_SAFE_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_FOREACH_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)      /* STAILQ_FOREACH_SAFE_P(elem, self, getpath, [tvar]) */
#define STAILQ_LAST_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_LAST_P_, (__VA_ARGS__))(__VA_ARGS__)              /* STAILQ_LAST_P(self, [T], getpath) */
#define STAILQ_P_PREV(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_P_PREV_, (__VA_ARGS__))(__VA_ARGS__)              /* STAILQ_P_PREV(p_elem, self, [type], key) */
#define STAILQ_P_PREV_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_P_PREV_P_, (__VA_ARGS__))(__VA_ARGS__)            /* STAILQ_P_PREV_P(p_elem, self, [T], getpath) */
#define STAILQ_P_PREV_UNSAFE(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_P_PREV_UNSAFE_, (__VA_ARGS__))(__VA_ARGS__)       /* STAILQ_P_PREV_UNSAFE(p_elem, [type], key) */
#define STAILQ_P_PREV_UNSAFE_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_P_PREV_UNSAFE_P_, (__VA_ARGS__))(__VA_ARGS__)     /* STAILQ_P_PREV_UNSAFE_P(p_elem, [T], getpath) */
#define STAILQ_P_REPLACE(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_P_REPLACE_, (__VA_ARGS__))(__VA_ARGS__)           /* STAILQ_P_REPLACE(self, p_old_elem, new_elem, [type], key) */
#define STAILQ_P_REPLACE_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_P_REPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)         /* STAILQ_P_REPLACE_P(self, p_old_elem, new_elem, [T], getpath) */
#define STAILQ_P_REPLACE_R(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_P_REPLACE_R_, (__VA_ARGS__))(__VA_ARGS__)         /* STAILQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key) */
#define STAILQ_P_REPLACE_R_P(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_P_REPLACE_R_P_, (__VA_ARGS__))(__VA_ARGS__)       /* STAILQ_P_REPLACE_R_P(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [T], getpath) */
#define STAILQ_REMOVEALL(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REMOVEALL_, (__VA_ARGS__))(__VA_ARGS__)           /* STAILQ_REMOVEALL(self, out_pelem, [type], key, condition, on_match) */
#define STAILQ_REMOVEALL_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REMOVEALL_P_, (__VA_ARGS__))(__VA_ARGS__)         /* STAILQ_REMOVEALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define STAILQ_REMOVE_IF(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)           /* STAILQ_REMOVE_IF(self, out_pelem, [type], key, condition) */
#define STAILQ_REMOVE_IF_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)         /* STAILQ_REMOVE_IF_P(self, out_pelem, [T], getpath, condition) */
#define STAILQ_REMOVE_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)            /* STAILQ_REMOVE_P(self, elem, [T], getpath) */
#define STAILQ_REPLACE(...)             __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REPLACE_, (__VA_ARGS__))(__VA_ARGS__)             /* STAILQ_REPLACE(self, old_elem, new_elem, [type], key) */
#define STAILQ_REPLACE_P(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)           /* STAILQ_REPLACE_P(self, old_elem, new_elem, [T], getpath) */
#define STAILQ_REPLACE_R(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REPLACE_R_, (__VA_ARGS__))(__VA_ARGS__)           /* STAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key) */
#define STAILQ_REPLACE_R_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REPLACE_R_P_, (__VA_ARGS__))(__VA_ARGS__)         /* STAILQ_REPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [T], getpath) */
#define STAILQ_SWAP_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_SWAP_P_, (__VA_ARGS__))(__VA_ARGS__)              /* STAILQ_SWAP_P(l1, l2, [T]) */
#define STAILQ_TRYREMOVE(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREMOVE_, (__VA_ARGS__))(__VA_ARGS__)           /* STAILQ_TRYREMOVE(self, elem, [type], key, on_failure) */
#define STAILQ_TRYREMOVE_IF(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)        /* STAILQ_TRYREMOVE_IF(self, out_pelem, [type], key, condition, on_failure) */
#define STAILQ_TRYREMOVE_IF_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)      /* STAILQ_TRYREMOVE_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#define STAILQ_TRYREMOVE_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)         /* STAILQ_TRYREMOVE_P(self, elem, [T], getpath, on_failure) */
#define STAILQ_TRYREPLACE(...)          __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREPLACE_, (__VA_ARGS__))(__VA_ARGS__)          /* STAILQ_TRYREPLACE(self, old_elem, new_elem, [type], key, on_success) */
#define STAILQ_TRYREPLACE_P(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)        /* STAILQ_TRYREPLACE_P(self, old_elem, new_elem, [T], getpath, on_success) */
#define STAILQ_TRYREPLACE_R(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREPLACE_R_, (__VA_ARGS__))(__VA_ARGS__)        /* STAILQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key, on_success) */
#define STAILQ_TRYREPLACE_R_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREPLACE_R_P_, (__VA_ARGS__))(__VA_ARGS__)      /* STAILQ_TRYREPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [T], getpath, on_success) */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define STAILQ_CONTAINS(self, elem, type, key, on_success)                                                      __HYBRID_STAILQ_CONTAINS(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath, on_success)
#define STAILQ_CONTAINS_P(self, elem, T, getpath, on_success)                                                   __HYBRID_STAILQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define STAILQ_FOREACH_FROM_SAFE_P(elem, self, getpath, tvar)                                                   __HYBRID_STAILQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define STAILQ_FOREACH_SAFE_P(elem, self, getpath, tvar)                                                        __HYBRID_STAILQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define STAILQ_LAST_P(self, T, getpath)                                                                         __HYBRID_STAILQ_LAST_P(self, T, getpath)
#define STAILQ_P_PREV(p_elem, self, T, key)                                                                     __HYBRID_STAILQ_P_PREV3(p_elem, self, __HYBRID_Q_STRUCT type, key)
#define STAILQ_P_PREV_P(p_elem, self, T, getpath)                                                               __HYBRID_STAILQ_P_PREV4(p_elem, self, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define STAILQ_P_PREV_UNSAFE(p_elem, T, key)                                                                    __HYBRID_STAILQ_P_PREV_UNSAFE3(p_elem, __HYBRID_Q_STRUCT type, key)
#define STAILQ_P_PREV_UNSAFE_P(p_elem, T, getpath)                                                              __HYBRID_STAILQ_P_PREV_UNSAFE4(p_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define STAILQ_P_REPLACE(self, p_old_elem, new_elem, type, key)                                                 __HYBRID_STAILQ_P_REPLACE(self, p_old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define STAILQ_P_REPLACE_P(self, p_old_elem, new_elem, T, getpath)                                              __HYBRID_STAILQ_REPLACE(self, p_old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define STAILQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key)               __HYBRID_STAILQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define STAILQ_P_REPLACE_R_P(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)            __HYBRID_STAILQ_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define STAILQ_REMOVEALL(self, out_pelem, type, key, condition, on_match)                                       __HYBRID_STAILQ_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define STAILQ_REMOVEALL_P(self, out_pelem, type, getpath, condition, on_match)                                 __HYBRID_STAILQ_REMOVEALL(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_match)
#define STAILQ_REMOVE_IF(self, out_pelem, type, key, condition)                                                 __HYBRID_STAILQ_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define STAILQ_REMOVE_IF_P(self, out_pelem, type, getpath, condition)                                           __HYBRID_STAILQ_REMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition)
#define STAILQ_REMOVE_P(self, elem, T, getpath)                                                                 __HYBRID_STAILQ_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define STAILQ_REPLACE(self, old_elem, new_elem, type, key)                                                     __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define STAILQ_REPLACE_P(self, old_elem, new_elem, T, getpath)                                                  __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define STAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key)                   __HYBRID_STAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define STAILQ_REPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)                __HYBRID_STAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define STAILQ_SWAP_P(l1, l2, T)                                                                                __HYBRID_STAILQ_SWAP(l1, l2, T)
#define STAILQ_TRYREMOVE(self, elem, type, key, on_failure)                                                     __HYBRID_STAILQ_TRYREMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath, on_failure)
#define STAILQ_TRYREMOVE_IF(self, out_pelem, type, key, condition, on_failure)                                  __HYBRID_STAILQ_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define STAILQ_TRYREMOVE_IF_P(self, out_pelem, type, getpath, condition, on_failure)                            __HYBRID_STAILQ_TRYREMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define STAILQ_TRYREMOVE_P(self, elem, T, getpath, on_failure)                                                  __HYBRID_STAILQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define STAILQ_TRYREPLACE(self, old_elem, new_elem, type, key, on_failure)                                      __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define STAILQ_TRYREPLACE_P(self, old_elem, new_elem, T, getpath, on_failure)                                   __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define STAILQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key, on_failure)    __HYBRID_STAILQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define STAILQ_TRYREPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath, on_failure) __HYBRID_STAILQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_STAILQ_P_PREV3(p_elem, self, T, key) \
	((p_elem) == &(self)->stqh_first ? __NULLPTR : __COMPILER_CONTAINER_OF(p_elem, T, key.stqe_next))
#define __HYBRID_STAILQ_P_PREV4(p_elem, self, T, X, _) \
	((p_elem) == &(self)->stqh_first ? __NULLPTR : (T *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&X(_, (T *)0).stqe_next))
#define __HYBRID_STAILQ_P_PREV_UNSAFE3(p_elem, T, key) \
	__COMPILER_CONTAINER_OF(p_elem, T, key.stqe_next)
#define __HYBRID_STAILQ_P_PREV_UNSAFE4(p_elem, T, X, _) \
	((T *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&X(_, (T *)0).stqe_next))
#define __HYBRID_STAILQ_SWAP(l1, l2, T)          \
	/* Sorry, this one must be a statement */    \
	do {                                         \
		T *__hstqs_first = (l1)->stqh_first,     \
		  **__hstqs_last = (l1)->stqh_last;      \
		(l1)->stqh_first = (l2)->stqh_first;     \
		(l1)->stqh_last  = (l2)->stqh_last;      \
		(l2)->stqh_first = __hstqs_first;        \
		(l2)->stqh_last  = __hstqs_last;         \
		if ((l1)->stqh_first == __NULLPTR)       \
			(l1)->stqh_last = &(l1)->stqh_first; \
		if ((l2)->stqh_first == __NULLPTR)       \
			(l2)->stqh_last = &(l2)->stqh_first; \
	}	__WHILE0
#define __HYBRID_STAILQ_INSERT_HEAD(self, elem, X, _) \
	__HYBRID_STAILQ_INSERT_HEAD_R(self, elem, elem, X, _)
#define __HYBRID_STAILQ_INSERT_HEAD_R(self, lo_elem, hi_elem, X, _) \
	((X(_, hi_elem).stqe_next = (self)->stqh_first) == __NULLPTR    \
	 ? (void)((self)->stqh_last = &X(_, hi_elem).stqe_next)         \
	 : (void)0,                                                     \
	 (void)((self)->stqh_first = (lo_elem)))
#define __HYBRID_STAILQ_INSERT_TAIL(self, elem, X, _) \
	__HYBRID_STAILQ_INSERT_TAIL_R(self, elem, elem, X, _)
#define __HYBRID_STAILQ_INSERT_TAIL_R(self, lo_elem, hi_elem, X, _)     \
	(void)(*(self)->stqh_last                              = (lo_elem), \
	       *((self)->stqh_last = &X(_, hi_elem).stqe_next) = __NULLPTR)
#define __HYBRID_STAILQ_INSERT_AFTER(self, predecessor, elem, X, _) \
	__HYBRID_STAILQ_INSERT_AFTER_R(self, predecessor, elem, elem, X, _)
#define __HYBRID_STAILQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, X, _) \
	(void)((X(_, hi_elem).stqe_next = X(_, predecessor).stqe_next) == __NULLPTR   \
	       ? (void)((self)->stqh_last = &X(_, hi_elem).stqe_next)                 \
	       : (void)0,                                                             \
	       X(_, predecessor).stqe_next = (lo_elem))
#define __HYBRID_STAILQ_P_REMOVE_R(self, p_lo_elem, hi_elem, X, _) \
	((*(p_lo_elem) = X(_, hi_elem).stqe_next) == __NULLPTR         \
	 ? (void)((self)->stqh_last = (p_lo_elem))                     \
	 : (void)0)
#define __HYBRID_STAILQ_P_REMOVE(self, p_elem, X, _) \
	__HYBRID_STAILQ_P_REMOVE_R(self, p_elem, *(p_elem), X, _)
#define __HYBRID_STAILQ_REMOVE_AFTER(self, elem, X, _) \
	__HYBRID_STAILQ_P_REMOVE_R(self, &X(_, elem).stqe_next, X(_, elem).stqe_next, X, _)
#define __HYBRID_STAILQ_REMOVE_HEAD(self, X, _)                             \
	(((self)->stqh_first = X(_, (self)->stqh_first).stqe_next) == __NULLPTR \
	 ? (void)((self)->stqh_last = &(self)->stqh_first)                      \
	 : (void)0)
#define __HYBRID_STAILQ_LAST(self, T, key) \
	(STAILQ_EMPTY(self) ? __NULLPTR : __COMPILER_CONTAINER_OF((head)->stqh_last, T, key.stqe_next))
#define __HYBRID_STAILQ_LAST_P(self, T, getpath) \
	(STAILQ_EMPTY(self) ? __NULLPTR : ((T *)((__SIZE_TYPE__)(head)->stqh_last - (__SIZE_TYPE__)&X(_, (T *)0).stqe_next)))
#define __HYBRID_STAILQ_REMOVE(self, elem, T, X, _)               \
	/* Sorry, this one must be a statement */                     \
	do {                                                          \
		T **__hstqr_piter = &(self)->stqh_first;                  \
		while (*__hstqr_piter != (elem))                          \
			__hstqr_piter = &X(_, *__hstqr_piter).stqe_next;      \
		if ((*__hstqr_piter = X(_, elem).stqe_next) == __NULLPTR) \
			(self)->stqh_last = __hstqr_piter;                    \
		__HYBRID_Q_BADPTR(X(_, elem).stqe_next);                  \
	}	__WHILE0
#define __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, T, X, _) \
	__HYBRID_STAILQ_REPLACE_R(self, old_elem, old_elem, new_elem, new_elem, T, X, _)
#define __HYBRID_STAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, X, _) \
	/* Sorry, this one must be a statement */                                                        \
	do {                                                                                             \
		T **__hstqrr_piter = &(self)->stqh_first;                                                    \
		while (*__hstqrr_piter != (old_lo_elem))                                                     \
			__hstqrr_piter = &X(_, *__hstqrr_piter).stqe_next;                                       \
		*__hstqrr_piter = (new_lo_elem);                                                             \
		if ((X(_, new_hi_elem).stqe_next = X(_, old_hi_elem).stqe_next) == __NULLPTR)                \
			(self)->stqh_last = &X(_, new_hi_elem).stqe_next;                                        \
		__HYBRID_Q_BADPTR(X(_, old_hi_elem).stqe_next);                                              \
	}	__WHILE0
#define __HYBRID_STAILQ_P_REPLACE(self, p_old_elem, new_elem, T, X, _) \
	__HYBRID_STAILQ_P_REPLACE_R(self, p_old_elem, *(p_old_elem), new_elem, new_elem, T, X, _)
#define __HYBRID_STAILQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, X, _) \
	(void)(*(p_old_lo_elem) = (new_lo_elem),                                                             \
	       ((X(_, new_hi_elem).stqe_next = X(_, old_hi_elem).stqe_next) == __NULLPTR)                    \
	       ? (void)((self)->stqh_last = &X(_, new_hi_elem).stqe_next)                                    \
	       : (void)0,                                                                                    \
	       __HYBRID_Q_BADPTR(X(_, old_hi_elem).stqe_next))
#define __HYBRID_STAILQ_TRYREMOVE(self, elem, T, X, _, on_failure)         \
	/* Sorry, this one must be a statement */                              \
	do {                                                                   \
		T **__hstqtr_piter = &(self)->stqh_first;                          \
		for (;;) {                                                         \
			if (*__hstqtr_piter == __NULLPTR) {                            \
				on_failure;                                                \
				break;                                                     \
			}                                                              \
			if (*__hstqtr_piter == (elem)) {                               \
				if ((*__hstqtr_piter = X(_, elem).stqe_next) == __NULLPTR) \
					(self)->stqh_last = __hstqtr_piter;                    \
				__HYBRID_Q_BADPTR(X(_, elem).stqe_next);                   \
				break;                                                     \
			}                                                              \
			__hstqtr_piter = &X(_, *__hstqtr_piter).stqe_next;             \
		}                                                                  \
	}	__WHILE0
#define __HYBRID_STAILQ_CONTAINS(self, elem, T, X, _, on_success) \
	/* Sorry, this one must be a statement */                     \
	do {                                                          \
		T *__hstqc_iter = (self)->stqh_first;                     \
		while (__hstqc_iter != __NULLPTR) {                       \
			if (__hstqc_iter == (elem)) {                         \
				on_success;                                       \
				break;                                            \
			}                                                     \
			__hstqc_iter = X(_, __hstqc_iter).stqe_next;          \
		}                                                         \
	}	__WHILE0
#define __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, T, X, _, on_failure) \
	__HYBRID_STAILQ_TRYREPLACE_R(self, old_elem, old_elem, new_elem, new_elem, T, X, _, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, X, _, on_failure) \
	/* Sorry, this one must be a statement */                                                                       \
	do {                                                                                                            \
		T **__hstqtrr_piter = &(self)->stqh_first;                                                                  \
		for (;;) {                                                                                                  \
			if (*__hstqtrr_piter == __NULLPTR)                                                                      \
				break;                                                                                              \
			if (*__hstqtrr_piter == (old_lo_elem)) {                                                                \
				*__hstqtrr_piter = (new_lo_elem);                                                                   \
				if ((X(_, new_hi_elem).stqe_next = X(_, old_hi_elem).stqe_next) == __NULLPTR)                       \
					(self)->stqh_last = &X(_, new_hi_elem).stqe_next;                                               \
				__HYBRID_Q_BADPTR(X(_, old_hi_elem).stqe_next);                                                     \
				break;                                                                                              \
			}                                                                                                       \
			__hstqtrr_piter = &X(_, *__hstqtrr_piter).stqe_next;                                                    \
		}                                                                                                           \
	}	__WHILE0
#define __HYBRID_STAILQ_REMOVE_IF(self, out_pelem, T, X, _, condition) \
	/* Sorry, this one must be a statement */                          \
	do {                                                               \
		T **__hstqri_piter = &(self)->stqh_first;                      \
		for (;;) {                                                     \
			*(out_pelem) = *__hstqri_piter;                            \
			if (condition)                                             \
				break;                                                 \
			__hstqri_piter = &X(_, *__hstqri_piter).stqe_next;         \
		}                                                              \
		if ((*__hstqri_piter = X(_, elem).stqe_next) == __NULLPTR)     \
			(self)->stqh_last = __hstqri_piter;                        \
		__HYBRID_Q_BADPTR(X(_, elem).stqe_next);                       \
	}	__WHILE0
#define __HYBRID_STAILQ_TRYREMOVE_IF(self, out_pelem, T, X, _, condition, on_failure) \
	/* Sorry, this one must be a statement */                                         \
	do {                                                                              \
		T **__hstqtri_piter = &(self)->stqh_first;                                    \
		for (;;) {                                                                    \
			if ((*(out_pelem) = *__hstqtri_piter) == __NULLPTR) {                     \
				on_failure;                                                           \
				break;                                                                \
			}                                                                         \
			if (condition) {                                                          \
				if ((*__hstqtri_piter = X(_, elem).stqe_next) == __NULLPTR)           \
					(self)->stqh_last = __hstqtri_piter;                              \
				__HYBRID_Q_BADPTR(X(_, elem).stqe_next);                              \
				break;                                                                \
			}                                                                         \
			__hstqtri_piter = &X(_, *__hstqtri_piter).stqe_next;                      \
		}                                                                             \
	}	__WHILE0
#define __HYBRID_STAILQ_REMOVEALL(self, out_pelem, T, X, _, condition, on_match) \
	/* Sorry, this one must be a statement */                                    \
	do {                                                                         \
		T **__hstqra_piter = &(self)->stqh_first;                                \
		while ((*(out_pelem) = *__hstqra_piter) != __NULLPTR) {                  \
			if (condition) {                                                     \
				if ((*__hstqra_piter = X(_, elem).stqe_next) == __NULLPTR)       \
					(self)->stqh_last = __hstqra_piter;                          \
				__HYBRID_Q_BADPTR(X(_, elem).stqe_next);                         \
				on_match;                                                        \
			} else {                                                             \
				__hstqra_piter = &X(_, *__hstqra_piter).stqe_next;               \
			}                                                                    \
		}                                                                        \
	}	__WHILE0
#define __HYBRID_STAILQ_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->stqh_first; (elem); (elem) = X(_, elem).stqe_next)
#define __HYBRID_STAILQ_FOREACH_FROM(elem, self, X, _) \
	for ((elem) ? (void)0 : (void)((elem) = (self)->stqh_first); (elem); (elem) = X(_, elem).stqe_next)
#define __HYBRID_STAILQ_P_FOREACH(p_elem, self, X, _) \
	for ((p_elem) = &(self)->stqh_first; *(p_elem); (p_elem) = &X(_, *(p_elem)).stqe_next)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_STAILQ_FOREACH_SAFE3(elem, self, X, _)           \
	if (((elem) = (self)->stqh_first, 0))                         \
		;                                                         \
	else                                                          \
		for (__typeof__(elem) __hstqfs_tvar;                      \
		     (elem) && (__hstqfs_tvar = X(_, elem).stqe_next, 1); \
		     (elem) = __hstqfs_tvar)
#define __HYBRID_STAILQ_FOREACH_FROM_SAFE3(elem, self, X, _)         \
	if (((elem) ? (void)0 : (void)((elem) = (self)->stqh_first), 0)) \
		;                                                            \
	else                                                             \
		for (__typeof__(elem) __hstqfs_tvar;                         \
		     (elem) && (__hstqfs_tvar = X(_, elem).stqe_next, 1);    \
		     (elem) = __hstqfs_tvar)
#endif /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define __HYBRID_STAILQ_FOREACH_SAFE4(elem, self, X, _, tvar) \
	for ((elem) = (head)->stqh_first;                         \
	     (elem) && ((tvar) = X(_, elem).stqe_next, 1);        \
	     (elem) = (tvar))
#define __HYBRID_STAILQ_FOREACH_FROM_SAFE4(elem, self, X, _, tvar) \
	for ((elem) ? (void)0 : (void)((elem) = (head)->stqh_first);   \
	     (elem) && ((tvar) = X(_, elem).stqe_next, 1);             \
	     (elem) = (tvar))






/************************************************************************/
/* Simple queue. (Alias for `Double-head, singly-linked Tail queue', with different field names) */
/************************************************************************/
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef SIMPLEQ_HEAD
#undef SIMPLEQ_CLASS_HEAD
#define __HYBRID_SIMPLEQ_HEAD_1(type)                                                          \
	struct {                                                                                   \
		__HYBRID_Q_STRUCT type *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;                        /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_SIMPLEQ_HEAD_2(name, type)                                                    \
	struct name {                                                                              \
		__HYBRID_Q_STRUCT type *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;                        /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_SIMPLEQ_CLASS_HEAD_1(type)                                                   \
	struct {                                                                                  \
		__HYBRID_Q_CLASS type *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;                       /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_SIMPLEQ_CLASS_HEAD_2(name, type)                                             \
	struct name {                                                                             \
		__HYBRID_Q_CLASS type *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;                       /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define SIMPLEQ_HEAD(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_HEAD_, (__VA_ARGS__))(__VA_ARGS__)       /* SIMPLEQ_HEAD([name], type) */
#define SIMPLEQ_CLASS_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_CLASS_HEAD_, (__VA_ARGS__))(__VA_ARGS__) /* SIMPLEQ_CLASS_HEAD([name], type) */
#else /* !__HYBRID_LIST_RESTRICT_API && __HYBRID_PP_VA_OVERLOAD */
#define SIMPLEQ_HEAD(name, type)                                                               \
	struct name {                                                                              \
		__HYBRID_Q_STRUCT type *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;                        /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define SIMPLEQ_CLASS_HEAD(name, type)                                                        \
	struct name {                                                                             \
		__HYBRID_Q_CLASS type *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;                       /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__HYBRID_PP_VA_OVERLOAD */
#define SIMPLEQ_ENTRY(type)       struct { __HYBRID_Q_STRUCT type *sqe_next; /* [0..1] Next element */ }
#define SIMPLEQ_CLASS_ENTRY(type) struct { __HYBRID_Q_CLASS  type *sqe_next; /* [0..1] Next element */ }
#define SIMPLEQ_CONCAT(dst, src)                   \
	((src)->sqh_first != __NULLPTR                 \
	 ? (void)(*(dst)->sqh_last = (src)->sqh_first, \
	          (dst)->sqh_last  = (src)->sqh_last,  \
	          STAILQ_INIT(src))                    \
	 : (void)0)
#define SIMPLEQ_EMPTY(self)                                ((self)->sqh_first == __NULLPTR)
#define SIMPLEQ_END(self)                                  __NULLPTR
#define SIMPLEQ_FIRST(self)                                (self)->sqh_first
#define SIMPLEQ_FOREACH(elem, self, key)                   __HYBRID_SIMPLEQ_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define SIMPLEQ_HEAD_INITIALIZER(self)                     { __NULLPTR, &(self).sqh_first }
#define SIMPLEQ_INIT(self)                                 (void)(*((self)->sqh_last = &(self)->sqh_first) = __NULLPTR)
#define SIMPLEQ_INSERT_AFTER(self, predecessor, elem, key) __HYBRID_SIMPLEQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_INSERT_HEAD(self, elem, key)               __HYBRID_SIMPLEQ_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_INSERT_TAIL(self, elem, key)               __HYBRID_SIMPLEQ_INSERT_TAIL(self, elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_NEXT(elem, key)                            (elem)->key.sqe_next
#define SIMPLEQ_REMOVE_AFTER(self, elem, key)              __HYBRID_SIMPLEQ_REMOVE_AFTER(self, elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_REMOVE_HEAD(self, key)                     __HYBRID_SIMPLEQ_REMOVE_HEAD(self, __HYBRID_Q_KEY, key)
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_SIMPLEQ_FOREACH_SAFE_3(elem, self, key)        __HYBRID_SIMPLEQ_FOREACH_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_FOREACH_SAFE_4(elem, self, key, tvar)  __HYBRID_SIMPLEQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_SIMPLEQ_LAST_2(self, key)               __HYBRID_SIMPLEQ_LAST(self, __typeof__(*(self)->sqh_first), key)
#define __HYBRID_SIMPLEQ_LAST_3(self, type, key)         __HYBRID_SIMPLEQ_LAST(self, __HYBRID_Q_STRUCT type, key)
#define __HYBRID_SIMPLEQ_REMOVE_3(self, elem, key)       __HYBRID_SIMPLEQ_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_REMOVE_4(self, elem, type, key) __HYBRID_SIMPLEQ_REMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_SWAP_2(l1, l2)                  __HYBRID_SIMPLEQ_SWAP(l1, l2, __typeof__(*(l1)->stqh_first))
#define __HYBRID_SIMPLEQ_SWAP_3(l1, l2, type)            __HYBRID_SIMPLEQ_SWAP(l1, l2, __HYBRID_Q_STRUCT type)
#undef SIMPLEQ_FOREACH_SAFE
#undef SIMPLEQ_LAST
#undef SIMPLEQ_REMOVE
#undef SIMPLEQ_SWAP
#define SIMPLEQ_FOREACH_SAFE(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_FOREACH_SAFE_, (__VA_ARGS__))(__VA_ARGS__) /* SIMPLEQ_FOREACH_SAFE(elem, self, key, [tvar]) */
#define SIMPLEQ_LAST(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_LAST_, (__VA_ARGS__))(__VA_ARGS__)         /* SIMPLEQ_LAST(self, [type], key) */
#define SIMPLEQ_REMOVE(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REMOVE_, (__VA_ARGS__))(__VA_ARGS__)       /* SIMPLEQ_REMOVE(self, elem, [type], key) */
#define SIMPLEQ_SWAP(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_SWAP_, (__VA_ARGS__))(__VA_ARGS__)         /* SIMPLEQ_SWAP(l1, l2, [type]) */
#else /* !__HYBRID_LIST_RESTRICT_API && __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define SIMPLEQ_FOREACH_SAFE(elem, self, key, tvar) __HYBRID_SIMPLEQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define SIMPLEQ_LAST(self, type, key)               __HYBRID_SIMPLEQ_LAST(self, __HYBRID_Q_STRUCT type, key)
#define SIMPLEQ_REMOVE(self, elem, type, key)       __HYBRID_SIMPLEQ_REMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SIMPLEQ_SWAP(l1, l2, type)                  __HYBRID_SIMPLEQ_SWAP(l1, l2, __HYBRID_Q_STRUCT type)
#endif /* __HYBRID_LIST_RESTRICT_API || !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#ifndef __HYBRID_LIST_RESTRICT_API
#define SIMPLEQ_ENTRY_P(T) struct { T *sqe_next; /* [0..1] Next element */ }
#define SIMPLEQ_HEAD_P(T)                                                 \
	struct {                                                              \
		T *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define SIMPLEQ_CLEAR(self)                                                    (void)(*((self)->sqh_last = &(self)->sqh_first) = __NULLPTR)
#define SIMPLEQ_FOREACH_FROM(elem, self, key)                                  __HYBRID_SIMPLEQ_FOREACH_FROM(elem, self, __HYBRID_Q_KEY, key)
#define SIMPLEQ_FOREACH_FROM_P(elem, self, getpath)                            __HYBRID_SIMPLEQ_FOREACH_FROM(elem, self, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_FOREACH_P(elem, self, getpath)                                 __HYBRID_SIMPLEQ_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_INSERT_AFTER_P(self, predecessor, elem, getpath)               __HYBRID_SIMPLEQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, getpath)   __HYBRID_SIMPLEQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_INSERT_AFTER_R_P(self, predecessor, lo_elem, hi_elem, getpath) __HYBRID_SIMPLEQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_INSERT_HEAD_P(self, elem, getpath)                             __HYBRID_SIMPLEQ_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_INSERT_HEAD_R(self, lo_elem, hi_elem, key)                     __HYBRID_SIMPLEQ_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_INSERT_HEAD_R_P(self, lo_elem, hi_elem, getpath)               __HYBRID_SIMPLEQ_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_INSERT_TAIL_P(self, elem, getpath)                             __HYBRID_SIMPLEQ_INSERT_TAIL(self, elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_INSERT_TAIL_R(self, lo_elem, hi_elem, key)                     __HYBRID_SIMPLEQ_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_INSERT_TAIL_R_P(self, lo_elem, hi_elem, getpath)               __HYBRID_SIMPLEQ_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_NEXT_P(elem, getpath)                                          getpath(elem).sqe_next
#define SIMPLEQ_PFIRST(self)                                                   (&(self)->sqh_first)
#define SIMPLEQ_P_FOREACH(p_elem, self, key)                                   __HYBRID_SIMPLEQ_P_FOREACH(p_elem, self, __HYBRID_Q_KEY, key)
#define SIMPLEQ_P_FOREACH_P(p_elem, self, getpath)                             __HYBRID_SIMPLEQ_P_FOREACH(p_elem, self, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_PNEXT(elem, key)                                               (&(elem)->key.sqe_next)
#define SIMPLEQ_PNEXT_P(elem, getpath)                                         (&getpath(elem).sqe_next)
#define SIMPLEQ_P_REMOVE(self, p_elem, key)                                    __HYBRID_SIMPLEQ_P_REMOVE(self, p_elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_P_REMOVE_P(self, p_elem, getpath)                              __HYBRID_SIMPLEQ_P_REMOVE(self, p_elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_P_REMOVE_R(self, p_lo_elem, hi_elem, key)                      __HYBRID_SIMPLEQ_P_REMOVE_R(self, p_lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_P_REMOVE_R_P(self, p_lo_elem, hi_elem, getpath)                __HYBRID_SIMPLEQ_P_REMOVE_R(self, p_lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_REMOVE_AFTER_P(self, elem, getpath)                            __HYBRID_SIMPLEQ_REMOVE_AFTER(self, elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_REMOVE_HEAD_P(self, getpath)                                   __HYBRID_SIMPLEQ_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_MOVE(dst, src)                                \
	(void)((dst)->sqh_last = (src)->sqh_last,                 \
	       ((dst)->sqh_first = (src)->sqh_first) == __NULLPTR \
	       ? (void)((dst)->sqh_last = &(dst)->sqh_first)      \
	       : (void)0,                                         \
	       (src)->sqh_first = __NULLPTR,                      \
	       (src)->sqh_last  = &(src)->sqh_first)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_SIMPLEQ_CONTAINS_4(self, elem, key, on_success)                                                            __HYBRID_SIMPLEQ_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SIMPLEQ_CONTAINS_5(self, elem, type, key, on_success)                                                      __HYBRID_SIMPLEQ_CONTAINS(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SIMPLEQ_CONTAINS_P_4(self, elem, getpath, on_success)                                                      __HYBRID_SIMPLEQ_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_SIMPLEQ_CONTAINS_P_5(self, elem, T, getpath, on_success)                                                   __HYBRID_SIMPLEQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE_3(elem, self, key)                                                               __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE_4(elem, self, key, tvar)                                                         __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE_P_3(elem, self, getpath)                                                         __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE_P_4(elem, self, getpath, tvar)                                                   __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_SIMPLEQ_FOREACH_SAFE_P_3(elem, self, getpath)                                                              __HYBRID_SIMPLEQ_FOREACH_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_FOREACH_SAFE_P_4(elem, self, getpath, tvar)                                                        __HYBRID_SIMPLEQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_SIMPLEQ_LAST_P_2(self, getpath)                                                                            __HYBRID_SIMPLEQ_LAST_P(self, __typeof__(*(self)->sqh_first), getpath)
#define __HYBRID_SIMPLEQ_LAST_P_3(self, T, getpath)                                                                         __HYBRID_SIMPLEQ_LAST_P(self, T, getpath)
#define __HYBRID_SIMPLEQ_P_PREV_2(p_elem, self, key)                                                                        __HYBRID_SIMPLEQ_P_PREV3(p_elem, self, __typeof__(*(elem)), key)
#define __HYBRID_SIMPLEQ_P_PREV_3(p_elem, self, type, key)                                                                  __HYBRID_SIMPLEQ_P_PREV3(p_elem, self, __HYBRID_Q_STRUCT type, key)
#define __HYBRID_SIMPLEQ_P_PREV_P_2(p_elem, self, getpath)                                                                  __HYBRID_SIMPLEQ_P_PREV4(p_elem, self, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_P_PREV_P_3(p_elem, self, T, getpath)                                                               __HYBRID_SIMPLEQ_P_PREV4(p_elem, self, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_P_PREV_UNSAFE_2(p_elem, key)                                                                       __HYBRID_SIMPLEQ_P_PREV_UNSAFE3(p_elem, __typeof__(*(elem)), key)
#define __HYBRID_SIMPLEQ_P_PREV_UNSAFE_3(p_elem, type, key)                                                                 __HYBRID_SIMPLEQ_P_PREV_UNSAFE3(p_elem, __HYBRID_Q_STRUCT type, key)
#define __HYBRID_SIMPLEQ_P_PREV_UNSAFE_P_2(p_elem, getpath)                                                                 __HYBRID_SIMPLEQ_P_PREV_UNSAFE4(p_elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_P_PREV_UNSAFE_P_3(p_elem, T, getpath)                                                              __HYBRID_SIMPLEQ_P_PREV_UNSAFE4(p_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_P_REPLACE_4(self, p_old_elem, new_elem, key)                                                       __HYBRID_SIMPLEQ_P_REPLACE(self, p_old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_P_REPLACE_P_4(self, p_old_elem, new_elem, getpath)                                                 __HYBRID_SIMPLEQ_P_REPLACE(self, p_old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_P_REPLACE_P_5(self, p_old_elem, new_elem, T, getpath)                                              __HYBRID_SIMPLEQ_P_REPLACE(self, p_old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_P_REPLACE_R_4(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)                     __HYBRID_SIMPLEQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_P_REPLACE_R_P_4(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath)               __HYBRID_SIMPLEQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_P_REPLACE_R_P_5(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)            __HYBRID_SIMPLEQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_REMOVEALL_5(self, out_pelem, key, condition, on_match)                                             __HYBRID_SIMPLEQ_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_SIMPLEQ_REMOVEALL_6(self, out_pelem, type, key, condition, on_match)                                       __HYBRID_SIMPLEQ_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_SIMPLEQ_REMOVEALL_P_5(self, out_pelem, getpath, condition, on_match)                                       __HYBRID_SIMPLEQ_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_SIMPLEQ_REMOVEALL_P_6(self, out_pelem, T, getpath, condition, on_match)                                    __HYBRID_SIMPLEQ_REMOVEALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_SIMPLEQ_REMOVE_IF_4(self, out_pelem, key, condition)                                                       __HYBRID_SIMPLEQ_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_SIMPLEQ_REMOVE_IF_5(self, out_pelem, type, key, condition)                                                 __HYBRID_SIMPLEQ_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_SIMPLEQ_REMOVE_IF_P_4(self, out_pelem, getpath, condition)                                                 __HYBRID_SIMPLEQ_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_SIMPLEQ_REMOVE_IF_P_5(self, out_pelem, T, getpath, condition)                                              __HYBRID_SIMPLEQ_REMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_SIMPLEQ_REMOVE_P_3(self, elem, getpath)                                                                    __HYBRID_SIMPLEQ_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_REMOVE_P_4(self, elem, T, getpath)                                                                 __HYBRID_SIMPLEQ_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_REPLACE_4(self, old_elem, new_elem, key)                                                           __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_REPLACE_5(self, old_elem, new_elem, type, key)                                                     __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_REPLACE_P_4(self, old_elem, new_elem, getpath)                                                     __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_REPLACE_P_5(self, old_elem, new_elem, T, getpath)                                                  __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_REPLACE_R_4(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)                         __HYBRID_SIMPLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_REPLACE_R_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key)                   __HYBRID_SIMPLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_REPLACE_R_P_4(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath)                   __HYBRID_SIMPLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_REPLACE_R_P_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)                __HYBRID_SIMPLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_SWAP_P_2(l1, l2)                                                                                   __HYBRID_SIMPLEQ_SWAP(l1, l2, __typeof__(*(l1)->stqh_first))
#define __HYBRID_SIMPLEQ_SWAP_P_3(l1, l2, T)                                                                                __HYBRID_SIMPLEQ_SWAP(l1, l2, T)
#define __HYBRID_SIMPLEQ_TRYREMOVE_4(self, elem, key, on_failure)                                                           __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_TRYREMOVE_5(self, elem, type, key, on_failure)                                                     __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_TRYREMOVE_IF_5(self, out_pelem, key, condition, on_failure)                                        __HYBRID_SIMPLEQ_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_SIMPLEQ_TRYREMOVE_IF_6(self, out_pelem, type, key, condition, on_failure)                                  __HYBRID_SIMPLEQ_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_SIMPLEQ_TRYREMOVE_IF_P_5(self, out_pelem, getpath, condition, on_failure)                                  __HYBRID_SIMPLEQ_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_SIMPLEQ_TRYREMOVE_IF_P_6(self, out_pelem, T, getpath, condition, on_failure)                               __HYBRID_SIMPLEQ_TRYREMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_SIMPLEQ_TRYREMOVE_P_4(self, elem, getpath, on_failure)                                                     __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SIMPLEQ_TRYREMOVE_P_5(self, elem, T, getpath, on_failure)                                                  __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_5(self, old_elem, new_elem, key, on_failure)                                            __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_6(self, old_elem, new_elem, type, key, on_failure)                                      __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_P_5(self, old_elem, new_elem, getpath, on_failure)                                      __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_P_6(self, old_elem, new_elem, T, getpath, on_failure)                                   __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_R_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key, on_failure)          __HYBRID_SIMPLEQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_R_6(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key, on_failure)    __HYBRID_SIMPLEQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_R_P_5(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath, on_failure)    __HYBRID_SIMPLEQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_R_P_6(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath, on_failure) __HYBRID_SIMPLEQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SIMPLEQ_CONTAINS(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_CONTAINS_, (__VA_ARGS__))(__VA_ARGS__)            /* SIMPLEQ_CONTAINS(self, elem, [type], key, on_success) */
#define SIMPLEQ_CONTAINS_P(...)          __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_CONTAINS_P_, (__VA_ARGS__))(__VA_ARGS__)          /* SIMPLEQ_CONTAINS_P(self, elem, [T], getpath, on_success) */
#define SIMPLEQ_FOREACH_FROM_SAFE(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_FOREACH_FROM_SAFE_, (__VA_ARGS__))(__VA_ARGS__)   /* SIMPLEQ_FOREACH_FROM_SAFE(elem, self, key, [tvar]) */
#define SIMPLEQ_FOREACH_FROM_SAFE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_FOREACH_FROM_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__) /* SIMPLEQ_FOREACH_FROM_SAFE_P(elem, self, getpath, [tvar]) */
#define SIMPLEQ_FOREACH_SAFE_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_FOREACH_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)      /* SIMPLEQ_FOREACH_SAFE_P(elem, self, getpath, [tvar]) */
#define SIMPLEQ_LAST_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_LAST_P_, (__VA_ARGS__))(__VA_ARGS__)              /* SIMPLEQ_LAST_P(self, [T], getpath) */
#define SIMPLEQ_P_PREV(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_P_PREV_, (__VA_ARGS__))(__VA_ARGS__)              /* SIMPLEQ_P_PREV(p_elem, self, [type], key) */
#define SIMPLEQ_P_PREV_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_P_PREV_P_, (__VA_ARGS__))(__VA_ARGS__)            /* SIMPLEQ_P_PREV_P(p_elem, self, [T], getpath) */
#define SIMPLEQ_P_PREV_UNSAFE(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_P_PREV_UNSAFE_, (__VA_ARGS__))(__VA_ARGS__)       /* SIMPLEQ_P_PREV_UNSAFE(p_elem, [type], key) */
#define SIMPLEQ_P_PREV_UNSAFE_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_P_PREV_UNSAFE_P_, (__VA_ARGS__))(__VA_ARGS__)     /* SIMPLEQ_P_PREV_UNSAFE_P(p_elem, [T], getpath) */
#define SIMPLEQ_P_REPLACE(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_P_REPLACE_, (__VA_ARGS__))(__VA_ARGS__)           /* SIMPLEQ_P_REPLACE(self, p_old_elem, new_elem, [type], key) */
#define SIMPLEQ_P_REPLACE_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_P_REPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)         /* SIMPLEQ_P_REPLACE_P(self, p_old_elem, new_elem, [T], getpath) */
#define SIMPLEQ_P_REPLACE_R(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_P_REPLACE_R_, (__VA_ARGS__))(__VA_ARGS__)         /* SIMPLEQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key) */
#define SIMPLEQ_P_REPLACE_R_P(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_P_REPLACE_R_P_, (__VA_ARGS__))(__VA_ARGS__)       /* SIMPLEQ_P_REPLACE_R_P(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [T], getpath) */
#define SIMPLEQ_REMOVEALL(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REMOVEALL_, (__VA_ARGS__))(__VA_ARGS__)           /* SIMPLEQ_REMOVEALL(self, out_pelem, [type], key, condition, on_match) */
#define SIMPLEQ_REMOVEALL_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REMOVEALL_P_, (__VA_ARGS__))(__VA_ARGS__)         /* SIMPLEQ_REMOVEALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define SIMPLEQ_REMOVE_IF(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)           /* SIMPLEQ_REMOVE_IF(self, out_pelem, [type], key, condition) */
#define SIMPLEQ_REMOVE_IF_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)         /* SIMPLEQ_REMOVE_IF_P(self, out_pelem, [T], getpath, condition) */
#define SIMPLEQ_REMOVE_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)            /* SIMPLEQ_REMOVE_P(self, elem, [T], getpath) */
#define SIMPLEQ_REPLACE(...)             __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REPLACE_, (__VA_ARGS__))(__VA_ARGS__)             /* SIMPLEQ_REPLACE(self, old_elem, new_elem, [type], key) */
#define SIMPLEQ_REPLACE_P(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)           /* SIMPLEQ_REPLACE_P(self, old_elem, new_elem, [T], getpath) */
#define SIMPLEQ_REPLACE_R(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REPLACE_R_, (__VA_ARGS__))(__VA_ARGS__)           /* SIMPLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key) */
#define SIMPLEQ_REPLACE_R_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REPLACE_R_P_, (__VA_ARGS__))(__VA_ARGS__)         /* SIMPLEQ_REPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [T], getpath) */
#define SIMPLEQ_SWAP_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_SWAP_P_, (__VA_ARGS__))(__VA_ARGS__)              /* SIMPLEQ_SWAP_P(l1, l2, [T]) */
#define SIMPLEQ_TRYREMOVE(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREMOVE_, (__VA_ARGS__))(__VA_ARGS__)           /* SIMPLEQ_TRYREMOVE(self, elem, [type], key, on_failure) */
#define SIMPLEQ_TRYREMOVE_IF(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)        /* SIMPLEQ_TRYREMOVE_IF(self, out_pelem, [type], key, condition, on_failure) */
#define SIMPLEQ_TRYREMOVE_IF_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)      /* SIMPLEQ_TRYREMOVE_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#define SIMPLEQ_TRYREMOVE_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)         /* SIMPLEQ_TRYREMOVE_P(self, elem, [T], getpath, on_failure) */
#define SIMPLEQ_TRYREPLACE(...)          __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREPLACE_, (__VA_ARGS__))(__VA_ARGS__)          /* SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, [type], key, on_success) */
#define SIMPLEQ_TRYREPLACE_P(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)        /* SIMPLEQ_TRYREPLACE_P(self, old_elem, new_elem, [T], getpath, on_success) */
#define SIMPLEQ_TRYREPLACE_R(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREPLACE_R_, (__VA_ARGS__))(__VA_ARGS__)        /* SIMPLEQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [type], key, on_success) */
#define SIMPLEQ_TRYREPLACE_R_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREPLACE_R_P_, (__VA_ARGS__))(__VA_ARGS__)      /* SIMPLEQ_TRYREPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, [T], getpath, on_success) */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define SIMPLEQ_CONTAINS(self, elem, type, key, on_success)                                                      __HYBRID_SIMPLEQ_CONTAINS(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath, on_success)
#define SIMPLEQ_CONTAINS_P(self, elem, T, getpath, on_success)                                                   __HYBRID_SIMPLEQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define SIMPLEQ_FOREACH_FROM_SAFE(elem, self, key, tvar)                                                         __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define SIMPLEQ_FOREACH_FROM_SAFE_P(elem, self, getpath, tvar)                                                   __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define SIMPLEQ_FOREACH_SAFE_P(elem, self, getpath, tvar)                                                        __HYBRID_SIMPLEQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define SIMPLEQ_LAST_P(self, T, getpath)                                                                         __HYBRID_SIMPLEQ_LAST_P(self, T, getpath)
#define SIMPLEQ_P_PREV(p_elem, self, T, key)                                                                     __HYBRID_SIMPLEQ_P_PREV3(p_elem, self, __HYBRID_Q_STRUCT type, key)
#define SIMPLEQ_P_PREV_P(p_elem, self, T, getpath)                                                               __HYBRID_SIMPLEQ_P_PREV4(p_elem, self, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_P_PREV_UNSAFE(p_elem, T, key)                                                                    __HYBRID_SIMPLEQ_P_PREV_UNSAFE3(p_elem, __HYBRID_Q_STRUCT type, key)
#define SIMPLEQ_P_PREV_UNSAFE_P(p_elem, T, getpath)                                                              __HYBRID_SIMPLEQ_P_PREV_UNSAFE4(p_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_P_REPLACE(self, p_old_elem, new_elem, type, key)                                                 __HYBRID_SIMPLEQ_P_REPLACE(self, p_old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SIMPLEQ_P_REPLACE_P(self, p_old_elem, new_elem, T, getpath)                                              __HYBRID_SIMPLEQ_REPLACE(self, p_old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key)               __HYBRID_SIMPLEQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SIMPLEQ_P_REPLACE_R_P(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)            __HYBRID_SIMPLEQ_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_REMOVEALL(self, out_pelem, type, key, condition, on_match)                                       __HYBRID_SIMPLEQ_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define SIMPLEQ_REMOVEALL_P(self, out_pelem, type, getpath, condition, on_match)                                 __HYBRID_SIMPLEQ_REMOVEALL(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_match)
#define SIMPLEQ_REMOVE_IF(self, out_pelem, type, key, condition)                                                 __HYBRID_SIMPLEQ_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define SIMPLEQ_REMOVE_IF_P(self, out_pelem, type, getpath, condition)                                           __HYBRID_SIMPLEQ_REMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition)
#define SIMPLEQ_REMOVE_P(self, elem, T, getpath)                                                                 __HYBRID_SIMPLEQ_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_REPLACE(self, old_elem, new_elem, type, key)                                                     __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SIMPLEQ_REPLACE_P(self, old_elem, new_elem, T, getpath)                                                  __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key)                   __HYBRID_SIMPLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define SIMPLEQ_REPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath)                __HYBRID_SIMPLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_SWAP_P(l1, l2, T)                                                                                __HYBRID_SIMPLEQ_SWAP(l1, l2, T)
#define SIMPLEQ_TRYREMOVE(self, elem, type, key, on_failure)                                                     __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_PTH, getpath, on_failure)
#define SIMPLEQ_TRYREMOVE_IF(self, out_pelem, type, key, condition, on_failure)                                  __HYBRID_SIMPLEQ_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define SIMPLEQ_TRYREMOVE_IF_P(self, out_pelem, type, getpath, condition, on_failure)                            __HYBRID_SIMPLEQ_TRYREMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define SIMPLEQ_TRYREMOVE_P(self, elem, T, getpath, on_failure)                                                  __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, type, key, on_failure)                                      __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define SIMPLEQ_TRYREPLACE_P(self, old_elem, new_elem, T, getpath, on_failure)                                   __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SIMPLEQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, type, key, on_failure)    __HYBRID_SIMPLEQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, on_failure)
#define SIMPLEQ_TRYREPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, getpath, on_failure) __HYBRID_SIMPLEQ_TRYREPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_SIMPLEQ_P_PREV3(p_elem, self, T, key) \
	((p_elem) == &(self)->sqh_first ? __NULLPTR : __COMPILER_CONTAINER_OF(p_elem, T, key.sqe_next))
#define __HYBRID_SIMPLEQ_P_PREV4(p_elem, self, T, X, _) \
	((p_elem) == &(self)->sqh_first ? __NULLPTR : (T *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&X(_, (T *)0).sqe_next))
#define __HYBRID_SIMPLEQ_P_PREV_UNSAFE3(p_elem, T, key) \
	__COMPILER_CONTAINER_OF(p_elem, T, key.sqe_next)
#define __HYBRID_SIMPLEQ_P_PREV_UNSAFE4(p_elem, T, X, _) \
	((T *)((__SIZE_TYPE__)(p_elem) - (__SIZE_TYPE__)&X(_, (T *)0).sqe_next))
#define __HYBRID_SIMPLEQ_SWAP(l1, l2, T)       \
	/* Sorry, this one must be a statement */  \
	do {                                       \
		T *__hsqs_first = (l1)->sqh_first;     \
		T **__hsqs_last = (l1)->sqh_last;      \
		(l1)->sqh_first = (l2)->sqh_first;     \
		(l1)->sqh_last  = (l2)->sqh_last;      \
		(l2)->sqh_first = __hsqs_first;        \
		(l2)->sqh_last  = __hsqs_last;         \
		if ((l1)->sqh_first == __NULLPTR)      \
			(l1)->sqh_last = &(l1)->sqh_first; \
		if ((l2)->sqh_first == __NULLPTR)      \
			(l2)->sqh_last = &(l2)->sqh_first; \
	}	__WHILE0
#define __HYBRID_SIMPLEQ_INSERT_HEAD(self, elem, X, _) \
	__HYBRID_SIMPLEQ_INSERT_HEAD_R(self, elem, elem, X, _)
#define __HYBRID_SIMPLEQ_INSERT_HEAD_R(self, lo_elem, hi_elem, X, _) \
	((X(_, hi_elem).sqe_next = (self)->sqh_first) == __NULLPTR       \
	 ? (void)((self)->sqh_last = &X(_, hi_elem).sqe_next)            \
	 : (void)0,                                                      \
	 (void)((self)->sqh_first = (lo_elem)))
#define __HYBRID_SIMPLEQ_INSERT_TAIL(self, elem, X, _) \
	__HYBRID_SIMPLEQ_INSERT_TAIL_R(self, elem, elem, X, _)
#define __HYBRID_SIMPLEQ_INSERT_TAIL_R(self, lo_elem, hi_elem, X, _)  \
	(void)(*(self)->sqh_last                             = (lo_elem), \
	       *((self)->sqh_last = &X(_, hi_elem).sqe_next) = __NULLPTR)
#define __HYBRID_SIMPLEQ_INSERT_AFTER(self, predecessor, elem, X, _) \
	__HYBRID_SIMPLEQ_INSERT_AFTER_R(self, predecessor, elem, elem, X, _)
#define __HYBRID_SIMPLEQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, X, _) \
	(void)((X(_, hi_elem).sqe_next = X(_, predecessor).sqe_next) == __NULLPTR      \
	       ? (void)((self)->sqh_last = &X(_, hi_elem).sqe_next)                    \
	       : (void)0,                                                              \
	       X(_, predecessor).sqe_next = (lo_elem))
#define __HYBRID_SIMPLEQ_REMOVE_HEAD(self, X, _)                         \
	(((self)->sqh_first = X(_, (self)->sqh_first).sqe_next) == __NULLPTR \
	 ? (void)((self)->sqh_last = &(self)->sqh_first)                     \
	 : (void)0)
#define __HYBRID_SIMPLEQ_P_REMOVE_R(self, p_lo_elem, hi_elem, X, _) \
	((*(p_lo_elem) = X(_, hi_elem).sqe_next) == __NULLPTR           \
	 ? (void)((self)->sqh_last = (p_lo_elem))                       \
	 : (void)0)
#define __HYBRID_SIMPLEQ_P_REMOVE(self, p_elem, X, _) \
	__HYBRID_SIMPLEQ_P_REMOVE_R(self, p_elem, *(p_elem), X, _)
#define __HYBRID_SIMPLEQ_REMOVE_AFTER(self, elem, X, _) \
	__HYBRID_SIMPLEQ_P_REMOVE_R(self, &X(_, elem).sqe_next, X(_, elem).sqe_next, X, _)
#define __HYBRID_SIMPLEQ_LAST(self, T, key) \
	(SIMPLEQ_EMPTY(self) ? __NULLPTR : __COMPILER_CONTAINER_OF((head)->sqh_last, T, key.sqe_next))
#define __HYBRID_SIMPLEQ_LAST_P(self, T, getpath) \
	(SIMPLEQ_EMPTY(self) ? __NULLPTR : ((T *)((__SIZE_TYPE__)(head)->sqh_last - (__SIZE_TYPE__)&X(_, (T *)0).sqe_next)))
#define __HYBRID_SIMPLEQ_REMOVE(self, elem, T, X, _)            \
	/* Sorry, this one must be a statement */                   \
	do {                                                        \
		T **__hsqr_piter = &(self)->sqh_first;                  \
		while (*__hsqr_piter != (elem))                         \
			__hsqr_piter = &X(_, *__hsqr_piter).sqe_next;       \
		if ((*__hsqr_piter = X(_, elem).sqe_next) == __NULLPTR) \
			(self)->sqh_last = __hsqr_piter;                    \
		__HYBRID_Q_BADPTR(X(_, elem).sqe_next);                 \
	}	__WHILE0
#define __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, T, X, _) \
	__HYBRID_SIMPLEQ_REPLACE_R(self, old_elem, old_elem, new_elem, new_elem, T, X, _)
#define __HYBRID_SIMPLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, X, _) \
	/* Sorry, this one must be a statement */                                                         \
	do {                                                                                              \
		T **__h_sqrr_piter = &(self)->sqh_first;                                                      \
		while (*__h_sqrr_piter != (old_lo_elem))                                                      \
			__h_sqrr_piter = &X(_, *__h_sqrr_piter).sqe_next;                                         \
		*__h_sqrr_piter = (new_lo_elem);                                                              \
		if ((X(_, new_hi_elem).sqe_next = X(_, old_hi_elem).sqe_next) == __NULLPTR)                   \
			(self)->sqh_last = &X(_, new_hi_elem).sqe_next;                                           \
		__HYBRID_Q_BADPTR(X(_, old_hi_elem).sqe_next);                                                \
	}	__WHILE0
#define __HYBRID_SIMPLEQ_P_REPLACE(self, p_old_elem, new_elem, T, X, _) \
	__HYBRID_SIMPLEQ_P_REPLACE_R(self, p_old_elem, *(p_old_elem), new_elem, new_elem, T, X, _)
#define __HYBRID_SIMPLEQ_P_REPLACE_R(self, p_old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, T, X, _) \
	(void)(*(p_old_lo_elem) = (new_lo_elem),                                                              \
	       ((X(_, new_hi_elem).sqe_next = X(_, old_hi_elem).sqe_next) == __NULLPTR)                       \
	       ? (void)((self)->sqh_last = &X(_, new_hi_elem).sqe_next)                                       \
	       : (void)0,                                                                                     \
	       __HYBRID_Q_BADPTR(X(_, old_hi_elem).sqe_next))
#define __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, T, X, _, on_failure)     \
	/* Sorry, this one must be a statement */                           \
	do {                                                                \
		T **__hsqtr_piter = &(self)->sqh_first;                         \
		while (*__hsqtr_piter != __NULLPTR && *__hsqtr_piter != (elem)) \
			__hsqtr_piter = &X(_, *__hsqtr_piter).sqe_next;             \
		if (*__hsqtr_piter != __NULLPTR) {                              \
			if ((*__hsqtr_piter = X(_, elem).sqe_next) == __NULLPTR)    \
				(self)->sqh_last = __hsqtr_piter;                       \
			__HYBRID_Q_BADPTR(X(_, elem).sqe_next);                     \
		} else {                                                        \
			on_failure;                                                 \
		}                                                               \
	}	__WHILE0
#define __HYBRID_SIMPLEQ_CONTAINS(self, elem, T, X, _, on_success) \
	/* Sorry, this one must be a statement */                      \
	do {                                                           \
		T *__hsqc_iter = (self)->sqh_first;                        \
		while (__hsqc_iter != __NULLPTR) {                         \
			if (__hsqc_iter == (elem)) {                           \
				on_success;                                        \
				break;                                             \
			}                                                      \
			__hsqc_iter = X(_, __hsqc_iter).sqe_next;              \
		}                                                          \
	}	__WHILE0
#define __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, T, X, _, on_failure) \
	/* Sorry, this one must be a statement */                                      \
	do {                                                                           \
		T **__hsqtrp_piter = &(self)->sqh_first;                                   \
		while (*__hsqtrp_piter != __NULLPTR && *__hsqtrp_piter != (old_elem))      \
			__hsqtrp_piter = &X(_, *__hsqtrp_piter).sqe_next;                      \
		if (*__hsqtrp_piter != __NULLPTR) {                                        \
			X(_, new_elem).sqe_next = *__hsqtrp_piter;                             \
			*__hsqtrp_piter                = (new_elem);                           \
			__HYBRID_Q_BADPTR(X(_, old_elem).sqe_next);                            \
		} else {                                                                   \
			on_failure;                                                            \
		}                                                                          \
	}	__WHILE0
#define __HYBRID_SIMPLEQ_REMOVE_IF(self, out_pelem, T, X, _, condition) \
	/* Sorry, this one must be a statement */                           \
	do {                                                                \
		T **__hsqri_piter = &(self)->sqh_first;                         \
		for (;;) {                                                      \
			*(out_pelem) = *__hsqri_piter;                              \
			if (condition)                                              \
				break;                                                  \
			__hsqri_piter = &X(_, *__hsqri_piter).sqe_next;             \
		}                                                               \
		if ((*__hsqri_piter = X(_, elem).sqe_next) == __NULLPTR)        \
			(self)->sqh_last = __hsqri_piter;                           \
		__HYBRID_Q_BADPTR(X(_, elem).sqe_next);                         \
	}	__WHILE0
#define __HYBRID_SIMPLEQ_TRYREMOVE_IF(self, out_pelem, T, X, _, condition, on_failure) \
	/* Sorry, this one must be a statement */                                          \
	do {                                                                               \
		T **__hsqtri_piter = &(self)->sqh_first;                                       \
		for (;;) {                                                                     \
			if ((*(out_pelem) = *__hsqtri_piter) == __NULLPTR) {                       \
				on_failure;                                                            \
				break;                                                                 \
			}                                                                          \
			if (condition) {                                                           \
				if ((*__hsqtri_piter = X(_, elem).sqe_next) == __NULLPTR)              \
					(self)->sqh_last = __hsqtri_piter;                                 \
				__HYBRID_Q_BADPTR(X(_, elem).sqe_next);                                \
				break;                                                                 \
			}                                                                          \
			__hsqtri_piter = &X(_, *__hsqtri_piter).sqe_next;                          \
		}                                                                              \
	}	__WHILE0
#define __HYBRID_SIMPLEQ_REMOVEALL(self, out_pelem, T, X, _, condition, on_match) \
	/* Sorry, this one must be a statement */                                     \
	do {                                                                          \
		T **__hsqra_piter = &(self)->sqh_first;                                   \
		while ((*(out_pelem) = *__hsqra_piter) != __NULLPTR) {                    \
			if (condition) {                                                      \
				if ((*__hsqra_piter = X(_, elem).sqe_next) == __NULLPTR)          \
					(self)->sqh_last = __hsqra_piter;                             \
				__HYBRID_Q_BADPTR(X(_, elem).sqe_next);                           \
				on_match;                                                         \
			} else {                                                              \
				__hsqra_piter = &X(_, *__hsqra_piter).sqe_next;                   \
			}                                                                     \
		}                                                                         \
	}	__WHILE0
#define __HYBRID_SIMPLEQ_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->sqh_first; (elem); (elem) = X(_, elem).sqe_next)
#define __HYBRID_SIMPLEQ_FOREACH_FROM(elem, self, X, _) \
	for ((elem) ? (void)0 : (void)((elem) = (self)->sqh_first); (elem); (elem) = X(_, elem).sqe_next)
#define __HYBRID_SIMPLEQ_P_FOREACH(p_elem, self, X, _) \
	for ((p_elem) = &(self)->sqh_first; *(p_elem); (p_elem) = &X(_, *(p_elem)).sqe_next)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_SIMPLEQ_FOREACH_SAFE3(elem, self, X, _)        \
	if (((elem) = (self)->sqh_first, 0))                        \
		;                                                       \
	else                                                        \
		for (__typeof__(elem) __hsqfs_tvar;                     \
		     (elem) && (__hsqfs_tvar = X(_, elem).sqe_next, 1); \
		     (elem) = __hsqfs_tvar)
#define __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE3(elem, self, X, _)       \
	if (((elem) ? (void)0 : (void)((elem) = (self)->sqh_first), 0)) \
		;                                                           \
	else                                                            \
		for (__typeof__(elem) __hsqfs_tvar;                         \
		     (elem) && (__hsqfs_tvar = X(_, elem).sqe_next, 1);     \
		     (elem) = __hsqfs_tvar)
#endif /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define __HYBRID_SIMPLEQ_FOREACH_SAFE4(elem, self, X, _, tvar) \
	for ((elem) = (head)->sqh_first;                           \
	     (elem) && ((tvar) = X(_, elem).sqe_next, 1);          \
	     (elem) = (tvar))
#define __HYBRID_SIMPLEQ_FOREACH_FROM_SAFE4(elem, self, X, _, tvar) \
	for ((elem) ? (void)0 : (void)((elem) = (head)->sqh_first);     \
	     (elem) && ((tvar) = X(_, elem).sqe_next, 1);               \
	     (elem) = (tvar))





/************************************************************************/
/* Double-head, doubly-linked tail queue                                */
/************************************************************************/
#define _TAILQ_HEAD(name, T, qual)                                             \
	struct name {                                                              \
		T qual *tqh_first, /* [0..1] Head element */                           \
		*qual *tqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define _TAILQ_ENTRY(T, qual)                                          \
	struct {                                                           \
		T qual *tqe_next, /* [1..1] Next element */                    \
		*qual *tqe_prev;  /* [1..1][1..1] This item's self-pointer. */ \
	}
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef TAILQ_HEAD
#undef TAILQ_CLASS_HEAD
#define __HYBRID_TAILQ_HEAD_1(type)             _TAILQ_HEAD(, __HYBRID_Q_STRUCT type, )
#define __HYBRID_TAILQ_HEAD_2(name, type)       _TAILQ_HEAD(name, __HYBRID_Q_STRUCT type, )
#define __HYBRID_TAILQ_CLASS_HEAD_1(type)       _TAILQ_HEAD(, __HYBRID_Q_CLASS type, )
#define __HYBRID_TAILQ_CLASS_HEAD_2(name, type) _TAILQ_HEAD(name, __HYBRID_Q_CLASS type, )
#define TAILQ_HEAD(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_HEAD_, (__VA_ARGS__))(__VA_ARGS__)       /* TAILQ_HEAD([name], type) */
#define TAILQ_CLASS_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_CLASS_HEAD_, (__VA_ARGS__))(__VA_ARGS__) /* TAILQ_CLASS_HEAD([name], type) */
#else /* !__HYBRID_LIST_RESTRICT_API && __HYBRID_PP_VA_OVERLOAD */
#define TAILQ_HEAD(name, type)       _TAILQ_HEAD(name, __HYBRID_Q_STRUCT type, )
#define TAILQ_CLASS_HEAD(name, type) _TAILQ_HEAD(name, __HYBRID_Q_CLASS type, )
#endif /* __HYBRID_LIST_RESTRICT_API || !__HYBRID_PP_VA_OVERLOAD */
#define TAILQ_CLASS_ENTRY(type)                          _TAILQ_ENTRY(__HYBRID_Q_CLASS type, )
#define TAILQ_CONCAT(dst, src, key)                      __HYBRID_TAILQ_CONCAT(dst, src, __HYBRID_Q_KEY, key)
#define TAILQ_EMPTY(self)                                ((self)->tqh_first == __NULLPTR)
#define TAILQ_END(self)                                  __NULLPTR
#define TAILQ_ENTRY(type)                                _TAILQ_ENTRY(__HYBRID_Q_STRUCT type, )
#define TAILQ_FIRST(self)                                (self)->tqh_first
#define TAILQ_FOREACH(elem, self, key)                   __HYBRID_TAILQ_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define TAILQ_FOREACH_FROM(elem, self, key)              __HYBRID_TAILQ_FOREACH_FROM(elem, self, __HYBRID_Q_KEY, key)
#define TAILQ_HEAD_INITIALIZER(self)                     { __NULLPTR, &(self).tqh_first }
#define TAILQ_INIT(self)                                 (void)(*((self)->tqh_last = &(self)->tqh_first) = __NULLPTR)
#define TAILQ_INSERT_AFTER(self, predecessor, elem, key) __HYBRID_TAILQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_BEFORE(successor, elem, key)        __HYBRID_TAILQ_INSERT_BEFORE(successor, elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_HEAD(self, elem, key)               __HYBRID_TAILQ_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_TAIL(self, elem, key)               __HYBRID_TAILQ_INSERT_TAIL(self, elem, __HYBRID_Q_KEY, key)
#define TAILQ_NEXT(elem, key)                            (elem)->key.tqe_next
#define TAILQ_REMOVE(self, elem, key)                    __HYBRID_TAILQ_REMOVE(self, elem, __HYBRID_Q_KEY, key)
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_TAILQ_FOREACH_FROM_SAFE_3(elem, self, key)                         __HYBRID_TAILQ_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_FROM_SAFE_4(elem, self, key, tvar)                   __HYBRID_TAILQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_TAILQ_FOREACH_REVERSE_3(elem, self, key)                           __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, __typeof__(*(self)), __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_REVERSE_4(elem, self, headname, key)                 __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_3(elem, self, key)                      __HYBRID_TAILQ_FOREACH_REVERSE_FROM(elem, self, __typeof__(*(self)), __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_4(elem, self, headname, key)            __HYBRID_TAILQ_FOREACH_REVERSE_FROM(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE_3(elem, self, key)                 __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE3T(elem, self, __typeof__(*(self)), __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE_4(elem, self, headname, key)       __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE3(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE_5(elem, self, headname, key, tvar) __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE4(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_TAILQ_FOREACH_REVERSE_SAFE_3(elem, self, key)                      __HYBRID_TAILQ_FOREACH_REVERSE_SAFE3T(elem, self, __typeof__(*(self)), __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_REVERSE_SAFE_4(elem, self, headname, key)            __HYBRID_TAILQ_FOREACH_REVERSE_SAFE3(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_REVERSE_SAFE_5(elem, self, headname, key, tvar)      __HYBRID_TAILQ_FOREACH_REVERSE_SAFE4(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_TAILQ_FOREACH_SAFE_3(elem, self, key)                              __HYBRID_TAILQ_FOREACH_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_FOREACH_SAFE_4(elem, self, key, tvar)                        __HYBRID_TAILQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_TAILQ_LAST_1(self)                                                 (*(((__typeof__(*(self)) *)((self)->tqh_last))->tqh_last))
#define __HYBRID_TAILQ_LAST_2(self, headname)                                       (*(((__HYBRID_Q_STRUCT headname *)((self)->tqh_last))->tqh_last))
#define __HYBRID_TAILQ_LAST_FAST_2(self, key)                                       (TAILQ_EMPTY(self) ? __NULLPTR : __COMPILER_CONTAINER_OF((self)->tqh_last, __typeof__(*(self)->tqh_first), key.tqe_next))
#define __HYBRID_TAILQ_LAST_FAST_3(self, type, key)                                 (TAILQ_EMPTY(self) ? __NULLPTR : __COMPILER_CONTAINER_OF((self)->tqh_last, __HYBRID_Q_STRUCT type, key.tqe_next))
#define __HYBRID_TAILQ_PREV_2(elem, key)                                            __HYBRID_TAILQ_PREV4(elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_PREV_3(elem, headname, key)                                  __HYBRID_TAILQ_PREV(elem, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_PREV_FAST_3(elem, self, key)                                 ((elem)->key.tqe_prev == &(self)->tqh_first ? __NULLPTR : __COMPILER_CONTAINER_OF((elem)->key.tqe_prev, __typeof__((self)->tqh_first), key.tqe_next))
#define __HYBRID_TAILQ_PREV_FAST_4(elem, self, type, key)                           ((elem)->key.tqe_prev == &(self)->tqh_first ? __NULLPTR : __COMPILER_CONTAINER_OF((elem)->key.tqe_prev, __HYBRID_Q_STRUCT type, key.tqe_next))
#define __HYBRID_TAILQ_SWAP_3(l1, l2, key)                                          __HYBRID_TAILQ_SWAP(l1, l2, __typeof__(*(l1)->tqh_first), __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_SWAP_4(l1, l2, type, key)                                    __HYBRID_TAILQ_SWAP(l1, l2, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#undef TAILQ_FOREACH_FROM_SAFE
#undef TAILQ_FOREACH_REVERSE
#undef TAILQ_FOREACH_REVERSE_FROM
#undef TAILQ_FOREACH_REVERSE_FROM_SAFE
#undef TAILQ_FOREACH_REVERSE_SAFE
#undef TAILQ_FOREACH_SAFE
#undef TAILQ_LAST
#undef TAILQ_LAST_FAST
#undef TAILQ_PREV
#undef TAILQ_PREV_FAST
#undef TAILQ_SWAP
#define TAILQ_FOREACH_FROM_SAFE(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_FROM_SAFE_, (__VA_ARGS__))(__VA_ARGS__)         /* TAILQ_FOREACH_FROM_SAFE(elem, self, key, [tvar]) */
#define TAILQ_FOREACH_REVERSE(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_REVERSE_, (__VA_ARGS__))(__VA_ARGS__)           /* TAILQ_FOREACH_REVERSE(elem, self, [headname], key) */
#define TAILQ_FOREACH_REVERSE_FROM(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_REVERSE_FROM_, (__VA_ARGS__))(__VA_ARGS__)      /* TAILQ_FOREACH_REVERSE_FROM(elem, self, [headname], key) */
#define TAILQ_FOREACH_REVERSE_FROM_SAFE(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE_, (__VA_ARGS__))(__VA_ARGS__) /* TAILQ_FOREACH_REVERSE_FROM_SAFE(elem, self, [headname], key, [tvar]) */
#define TAILQ_FOREACH_REVERSE_SAFE(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_REVERSE_SAFE_, (__VA_ARGS__))(__VA_ARGS__)      /* TAILQ_FOREACH_REVERSE_SAFE(elem, self, [headname], key, [tvar]) */
#define TAILQ_FOREACH_SAFE(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_SAFE_, (__VA_ARGS__))(__VA_ARGS__)              /* TAILQ_FOREACH_SAFE(elem, self, key, [tvar]) */
#define TAILQ_LAST(...)                      __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_LAST_, (__VA_ARGS__))(__VA_ARGS__)                      /* TAILQ_LAST(self, [headname]) */
#define TAILQ_LAST_FAST(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_LAST_FAST_, (__VA_ARGS__))(__VA_ARGS__)                 /* TAILQ_LAST_FAST(self, [type], key) */
#define TAILQ_PREV(...)                      __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_PREV_, (__VA_ARGS__))(__VA_ARGS__)                      /* TAILQ_PREV(elem, [headname], key) */
#define TAILQ_PREV_FAST(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_PREV_FAST_, (__VA_ARGS__))(__VA_ARGS__)                 /* TAILQ_PREV_FAST(elem, self, [type], key) */
#define TAILQ_SWAP(...)                      __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_SWAP_, (__VA_ARGS__))(__VA_ARGS__)                      /* TAILQ_SWAP(l1, l2, [type], key) */
#else /* !__HYBRID_LIST_RESTRICT_API && __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define TAILQ_FOREACH_FROM_SAFE(elem, self, key, tvar)                   __HYBRID_TAILQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define TAILQ_FOREACH_REVERSE(elem, self, headname, key)                 __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key)
#define TAILQ_FOREACH_REVERSE_FROM(elem, self, headname, key)            __HYBRID_TAILQ_FOREACH_REVERSE_FROM(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key)
#define TAILQ_FOREACH_REVERSE_FROM_SAFE(elem, self, headname, key, tvar) __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE4(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key, tvar)
#define TAILQ_FOREACH_REVERSE_SAFE(elem, self, headname, key, tvar)      __HYBRID_TAILQ_FOREACH_REVERSE_SAFE4(elem, self, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key, tvar)
#define TAILQ_FOREACH_SAFE(elem, self, key, tvar)                        __HYBRID_TAILQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define TAILQ_LAST(self, headname)                                       (*(((__HYBRID_Q_STRUCT headname *)((self)->tqh_last))->tqh_last))
#define TAILQ_LAST_FAST(self, type, key)                                 (TAILQ_EMPTY(self) ? __NULLPTR : __COMPILER_CONTAINER_OF((self)->tqh_last, __HYBRID_Q_STRUCT type, key.tqe_next))
#define TAILQ_PREV(elem, headname, key)                                  __HYBRID_TAILQ_PREV(elem, __HYBRID_Q_STRUCT headname, __HYBRID_Q_KEY, key)
#define TAILQ_PREV_FAST(elem, self, type, key)                           ((elem)->key.tqe_prev == &(self)->tqh_first ? __NULLPTR : __COMPILER_CONTAINER_OF((elem)->key.tqe_prev, __HYBRID_Q_STRUCT type, key.tqe_next))
#define TAILQ_SWAP(l1, l2, type, key)                                    __HYBRID_TAILQ_SWAP(l1, l2, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#endif /* __HYBRID_LIST_RESTRICT_API || !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#ifndef __HYBRID_LIST_RESTRICT_API
#define _TAILQ_HEAD_P(T, qual)                                                 \
	struct {                                                                   \
		T qual *tqh_first, /* [0..1] Head element */                           \
		*qual *tqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define _TAILQ_ENTRY_P(T, qual)                                        \
	struct {                                                           \
		T qual *tqe_next, /* [1..1] Next element */                    \
		*qual *tqe_prev;  /* [1..1][1..1] This item's self-pointer. */ \
	}
#define TAILQ_HEAD_P(T)  _TAILQ_HEAD_P(T, )
#define TAILQ_ENTRY_P(T) _TAILQ_ENTRY_P(T, )
#define TAILQ_CLEAR(self)                                                                    (void)(*((self)->tqh_last = &(self)->tqh_first) = __NULLPTR)
#define TAILQ_CONCAT_P(dst, src, getpath)                                                    __HYBRID_TAILQ_CONCAT(dst, src, __HYBRID_Q_PTH, getpath)
#define TAILQ_ENTRY_UNBOUND_INIT(entry)                                                      (void)(__HYBRID_Q_BADPTR((entry)->tqe_next), (entry)->tqe_prev = __NULLPTR)
#define TAILQ_ENTRY_UNBOUND_INITIALIZER                                                      { __NULLPTR, __NULLPTR }
#define TAILQ_ENTRY_UNBOUND_INITIALIZER_IS_ZERO
#define TAILQ_FOREACH_FROM_P(elem, self, getpath)                                            __HYBRID_TAILQ_FOREACH_FROM(elem, self, __HYBRID_Q_PTH, getpath)
#define TAILQ_FOREACH_P(elem, self, getpath)                                                 __HYBRID_TAILQ_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define TAILQ_FOREACH_REVERSE_FROM_P(elem, self, HEAD_T, getpath)                            __HYBRID_TAILQ_FOREACH_REVERSE_FROM(elem, self, HEAD_T, __HYBRID_Q_PTH, getpath)
#define TAILQ_FOREACH_REVERSE_P(elem, self, HEAD_T, getpath)                                 __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, HEAD_T, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_AFTER_P(self, predecessor, elem, getpath)                               __HYBRID_TAILQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, key)                       __HYBRID_TAILQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_AFTER_R_P(self, predecessor, lo_elem, hi_elem, getpath)                 __HYBRID_TAILQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_BEFORE_P(successor, elem, getpath)                                      __HYBRID_TAILQ_INSERT_BEFORE(successor, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_BEFORE_R(successor, lo_elem, hi_elem, key)                              __HYBRID_TAILQ_INSERT_BEFORE_R(successor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_BEFORE_R_P(successor, lo_elem, hi_elem, getpath)                        __HYBRID_TAILQ_INSERT_BEFORE_R(successor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_HEAD_P(self, elem, getpath)                                             __HYBRID_TAILQ_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_HEAD_R(self, lo_elem, hi_elem, key)                                     __HYBRID_TAILQ_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_HEAD_R_P(self, lo_elem, hi_elem, getpath)                               __HYBRID_TAILQ_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_TAIL_P(self, elem, getpath)                                             __HYBRID_TAILQ_INSERT_TAIL(self, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_TAIL_R(self, lo_elem, hi_elem, key)                                     __HYBRID_TAILQ_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_TAIL_R_P(self, lo_elem, hi_elem, getpath)                               __HYBRID_TAILQ_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_ISBOUND(elem, key)                                                             ((elem)->key.tqe_prev != __NULLPTR)
#define TAILQ_ISBOUND_P(elem, getpath)                                                       (getpath(elem).tqe_prev != __NULLPTR)
#define TAILQ_LAST_P(self, HEAD_T)                                                           (*(((HEAD_T *)((self)->tqh_last))->tqh_last))
#define TAILQ_MOVE(dst, src, key)                                                            __HYBRID_TAILQ_MOVE(dst, src, __HYBRID_Q_KEY, key)
#define TAILQ_MOVE_P(dst, src, getpath)                                                      __HYBRID_TAILQ_MOVE(dst, src, __HYBRID_Q_PTH, getpath)
#define TAILQ_NEXT_P(elem, getpath)                                                          getpath(elem).tqe_next
#define TAILQ_REMOVE_AFTER(self, elem, key)                                                  __HYBRID_TAILQ_REMOVE_AFTER(self, elem, __HYBRID_Q_KEY, key)
#define TAILQ_REMOVE_AFTER_P(self, elem, getpath)                                            __HYBRID_TAILQ_REMOVE_AFTER(self, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_REMOVE_HEAD(self, key)                                                         __HYBRID_TAILQ_REMOVE_HEAD(self, __HYBRID_Q_KEY, key)
#define TAILQ_REMOVE_HEAD_P(self, getpath)                                                   __HYBRID_TAILQ_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#define TAILQ_REMOVE_P(self, elem, getpath)                                                  __HYBRID_TAILQ_REMOVE(self, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_REMOVE_R(self, lo_elem, hi_elem, key)                                          __HYBRID_TAILQ_REMOVE_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define TAILQ_REMOVE_R_P(self, lo_elem, hi_elem, getpath)                                    __HYBRID_TAILQ_REMOVE_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_REPLACE(self, old_elem, new_elem, key)                                         __HYBRID_TAILQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_KEY, key)
#define TAILQ_REPLACE_P(self, old_elem, new_elem, getpath)                                   __HYBRID_TAILQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)       __HYBRID_TAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_KEY, key)
#define TAILQ_REPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath) __HYBRID_TAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_UNBIND(self, elem, key)                                                        __HYBRID_TAILQ_UNBIND(self, elem, __HYBRID_Q_KEY, key)
#define TAILQ_UNBIND_P(self, elem, getpath)                                                  __HYBRID_TAILQ_UNBIND(self, elem, __HYBRID_Q_PTH, getpath)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_TAILQ_FOREACH_FROM_SAFE_P_3(elem, self, getpath)                           __HYBRID_TAILQ_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_FOREACH_FROM_SAFE_P_4(elem, self, getpath, tvar)                     __HYBRID_TAILQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE_P_3(elem, self, getpath)                   __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE3T(elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE_P_4(elem, self, HEAD_T, getpath)           __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE3(elem, self, HEAD_T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE_P_5(elem, self, HEAD_T, getpath, tvar)     __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE4(elem, self, HEAD_T, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_TAILQ_FOREACH_REVERSE_SAFE_P_3(elem, self, getpath)                        __HYBRID_TAILQ_FOREACH_REVERSE_SAFE3T(elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_FOREACH_REVERSE_SAFE_P_4(elem, self, HEAD_T, getpath)                __HYBRID_TAILQ_FOREACH_REVERSE_SAFE3(elem, self, HEAD_T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_FOREACH_REVERSE_SAFE_P_5(elem, self, HEAD_T, getpath, tvar)          __HYBRID_TAILQ_FOREACH_REVERSE_SAFE4(elem, self, HEAD_T, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_TAILQ_FOREACH_SAFE_P_3(elem, self, getpath)                                __HYBRID_TAILQ_FOREACH_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_FOREACH_SAFE_P_4(elem, self, getpath, tvar)                          __HYBRID_TAILQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_TAILQ_LAST_FAST_P_2(self, getpath)                                         (TAILQ_EMPTY(self) ? __NULLPTR : (__typeof__((self)->tqh_first))((__SIZE_TYPE__)(self)->tqh_last - (__SIZE_TYPE__)&getpath((__typeof__((self)->tqh_first))0).tqe_next))
#define __HYBRID_TAILQ_LAST_FAST_P_3(self, T, getpath)                                      (TAILQ_EMPTY(self) ? __NULLPTR : (T *)((__SIZE_TYPE__)(self)->tqh_last - (__SIZE_TYPE__)&getpath((T *)0).tqe_next))
#define __HYBRID_TAILQ_PREV_FAST_P_3(elem, self, getpath)                                   ((elem)->field.tqe_prev == &(self)->tqh_first ? __NULLPTR : (__typeof__((self)->tqh_first))((__SIZE_TYPE__)(elem)->field.tqe_prev - (__SIZE_TYPE__)&getpath((__typeof__((self)->tqh_first))0).tqe_next))
#define __HYBRID_TAILQ_PREV_FAST_P_4(elem, self, T, getpath)                                ((elem)->field.tqe_prev == &(self)->tqh_first ? __NULLPTR : (T *)((__SIZE_TYPE__)(elem)->field.tqe_prev - (__SIZE_TYPE__)&getpath((T *)0).tqe_next))
#define __HYBRID_TAILQ_PREV_P_2(elem, getpath)                                              __HYBRID_TAILQ_PREV4(elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_PREV_P_3(elem, HEAD_T, getpath)                                      __HYBRID_TAILQ_PREV(elem, HEAD_T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_REMOVEALL_5(self, out_pelem, key, condition, on_match)               __HYBRID_TAILQ_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_TAILQ_REMOVEALL_6(self, out_pelem, type, key, condition, on_match)         __HYBRID_TAILQ_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_TAILQ_REMOVEALL_P_5(self, out_pelem, getpath, condition, on_match)         __HYBRID_TAILQ_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_TAILQ_REMOVEALL_P_6(self, out_pelem, T, getpath, condition, on_match)      __HYBRID_TAILQ_REMOVEALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_TAILQ_REMOVE_IF_4(self, out_pelem, key, condition)                         __HYBRID_TAILQ_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_TAILQ_REMOVE_IF_5(self, out_pelem, type, key, condition)                   __HYBRID_TAILQ_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_TAILQ_REMOVE_IF_P_4(self, out_pelem, getpath, condition)                   __HYBRID_TAILQ_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_TAILQ_REMOVE_IF_P_5(self, out_pelem, T, getpath, condition)                __HYBRID_TAILQ_REMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_TAILQ_SWAP_P_2(l1, l2, getpath)                                            __HYBRID_TAILQ_SWAP(l1, l2, __typeof__(*(l1)->tqh_first), __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_SWAP_P_3(l1, l2, T, getpath)                                         __HYBRID_TAILQ_SWAP(l1, l2, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_TAILQ_TRYREMOVE_IF_5(self, out_pelem, key, condition, on_failure)          __HYBRID_TAILQ_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_TAILQ_TRYREMOVE_IF_6(self, out_pelem, type, key, condition, on_failure)    __HYBRID_TAILQ_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_TAILQ_TRYREMOVE_IF_P_5(self, out_pelem, getpath, condition, on_failure)    __HYBRID_TAILQ_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_TAILQ_TRYREMOVE_IF_P_6(self, out_pelem, T, getpath, condition, on_failure) __HYBRID_TAILQ_TRYREMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_TAILQ_TRYUNBIND_IF_5(self, out_pelem, key, condition, on_failure)          __HYBRID_TAILQ_TRYUNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_TAILQ_TRYUNBIND_IF_6(self, out_pelem, type, key, condition, on_failure)    __HYBRID_TAILQ_TRYUNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_TAILQ_TRYUNBIND_IF_P_5(self, out_pelem, getpath, condition, on_failure)    __HYBRID_TAILQ_TRYUNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_TAILQ_TRYUNBIND_IF_P_6(self, out_pelem, T, getpath, condition, on_failure) __HYBRID_TAILQ_TRYUNBIND_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_TAILQ_UNBINDALL_5(self, out_pelem, key, condition, on_match)               __HYBRID_TAILQ_UNBINDALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_TAILQ_UNBINDALL_6(self, out_pelem, type, key, condition, on_match)         __HYBRID_TAILQ_UNBINDALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_TAILQ_UNBINDALL_P_5(self, out_pelem, getpath, condition, on_match)         __HYBRID_TAILQ_UNBINDALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_TAILQ_UNBINDALL_P_6(self, out_pelem, T, getpath, condition, on_match)      __HYBRID_TAILQ_UNBINDALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_TAILQ_UNBIND_IF_4(self, out_pelem, key, condition)                         __HYBRID_TAILQ_UNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_TAILQ_UNBIND_IF_5(self, out_pelem, type, key, condition)                   __HYBRID_TAILQ_UNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_TAILQ_UNBIND_IF_P_4(self, out_pelem, getpath, condition)                   __HYBRID_TAILQ_UNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_TAILQ_UNBIND_IF_P_5(self, out_pelem, T, getpath, condition)                __HYBRID_TAILQ_UNBIND_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define TAILQ_FOREACH_FROM_SAFE_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_FROM_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)         /* TAILQ_FOREACH_FROM_SAFE_P(elem, self, getpath, [tvar]) */
#define TAILQ_FOREACH_REVERSE_FROM_SAFE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__) /* TAILQ_FOREACH_REVERSE_FROM_SAFE_P(elem, self, [HEAD_T], getpath, [tvar]) */
#define TAILQ_FOREACH_REVERSE_SAFE_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_REVERSE_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)      /* TAILQ_FOREACH_REVERSE_SAFE_P(elem, self, [HEAD_T], getpath, [tvar]) */
#define TAILQ_FOREACH_SAFE_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)              /* TAILQ_FOREACH_SAFE_P(elem, self, getpath, [tvar]) */
#define TAILQ_LAST_FAST_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_LAST_FAST_P_, (__VA_ARGS__))(__VA_ARGS__)                 /* TAILQ_LAST_FAST_P(self, [T], getpath) */
#define TAILQ_PREV_FAST_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_PREV_FAST_P_, (__VA_ARGS__))(__VA_ARGS__)                 /* TAILQ_PREV_FAST_P(elem, self, [T], getpath) */
#define TAILQ_PREV_P(...)                      __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_PREV_P_, (__VA_ARGS__))(__VA_ARGS__)                      /* TAILQ_PREV_P(elem, [HEAD_T], getpath) */
#define TAILQ_REMOVEALL(...)                   __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)                /* TAILQ_REMOVEALL(self, out_pelem, [type], key, condition, on_match) */
#define TAILQ_REMOVEALL_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)              /* TAILQ_REMOVEALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define TAILQ_REMOVE_IF(...)                   __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_REMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)                   /* TAILQ_REMOVE_IF(self, out_pelem, [type], key, condition) */
#define TAILQ_REMOVE_IF_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_REMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)                 /* TAILQ_REMOVE_IF_P(self, out_pelem, [T], getpath, condition) */
#define TAILQ_SWAP_P(...)                      __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_SWAP_P_, (__VA_ARGS__))(__VA_ARGS__)                      /* TAILQ_SWAP_P(l1, l2, [T], getpath) */
#define TAILQ_TRYREMOVE_IF(...)                __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)                /* TAILQ_TRYREMOVE_IF(self, out_pelem, [type], key, condition, on_failure) */
#define TAILQ_TRYREMOVE_IF_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)              /* TAILQ_TRYREMOVE_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#define TAILQ_TRYUNBIND_IF(...)                __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_TRYUNBIND_IF_, (__VA_ARGS__))(__VA_ARGS__)                /* TAILQ_TRYUNBIND_IF(self, out_pelem, [type], key, condition, on_failure) */
#define TAILQ_TRYUNBIND_IF_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_TRYUNBIND_IF_P_, (__VA_ARGS__))(__VA_ARGS__)              /* TAILQ_TRYUNBIND_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#define TAILQ_UNBINDALL(...)                   __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_UNBINDALL_, (__VA_ARGS__))(__VA_ARGS__)                   /* TAILQ_UNBINDALL(self, out_pelem, [type], key, condition, on_match) */
#define TAILQ_UNBINDALL_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_UNBINDALL_P_, (__VA_ARGS__))(__VA_ARGS__)                 /* TAILQ_UNBINDALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define TAILQ_UNBIND_IF(...)                   __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_UNBIND_IF_, (__VA_ARGS__))(__VA_ARGS__)                   /* TAILQ_UNBIND_IF(self, out_pelem, [type], key, condition) */
#define TAILQ_UNBIND_IF_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_UNBIND_IF_P_, (__VA_ARGS__))(__VA_ARGS__)                 /* TAILQ_UNBIND_IF_P(self, out_pelem, [T], getpath, condition) */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define TAILQ_FOREACH_FROM_SAFE_P(elem, self, getpath, tvar)                        __HYBRID_TAILQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define TAILQ_FOREACH_REVERSE_FROM_SAFE_P(elem, self, HEAD_T, getpath, tvar)        __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE4(elem, self, HEAD_T, __HYBRID_Q_PTH, getpath, tvar)
#define TAILQ_FOREACH_REVERSE_SAFE_P(elem, self, HEAD_T, getpath, tvar)             __HYBRID_TAILQ_FOREACH_REVERSE_SAFE4(elem, self, HEAD_T, __HYBRID_Q_PTH, getpath, tvar)
#define TAILQ_FOREACH_SAFE_P(elem, self, getpath, tvar)                             __HYBRID_TAILQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define TAILQ_LAST_FAST_P(self, T, getpath)                                         (TAILQ_EMPTY(self) ? __NULLPTR : (T *)((__SIZE_TYPE__)(self)->tqh_last - (__SIZE_TYPE__)&getpath((T *)0).tqe_next))
#define TAILQ_PREV_FAST_P(elem, self, T, getpath)                                   ((elem)->field.tqe_prev == &(self)->tqh_first ? __NULLPTR : (T *)((__SIZE_TYPE__)(elem)->field.tqe_prev - (__SIZE_TYPE__)&getpath((T *)0).tqe_next))
#define TAILQ_PREV_P(elem, HEAD_T, getpath)                                         __HYBRID_TAILQ_PREV(elem, HEAD_T, __HYBRID_Q_PTH, getpath)
#define TAILQ_REMOVEALL(self, out_pelem, type, key, condition, on_match)            __HYBRID_TAILQ_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define TAILQ_REMOVEALL_P(self, out_pelem, type, getpath, condition, on_match)      __HYBRID_TAILQ_REMOVEALL(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_match)
#define TAILQ_REMOVE_IF(self, out_pelem, type, key, condition)                      __HYBRID_TAILQ_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define TAILQ_REMOVE_IF_P(self, out_pelem, type, getpath, condition)                __HYBRID_TAILQ_REMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition)
#define TAILQ_SWAP_P(l1, l2, T, getpath)                                            __HYBRID_TAILQ_SWAP(l1, l2, T, __HYBRID_Q_PTH, getpath)
#define TAILQ_TRYREMOVE_IF(self, out_pelem, type, key, condition, on_failure)       __HYBRID_TAILQ_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define TAILQ_TRYREMOVE_IF_P(self, out_pelem, type, getpath, condition, on_failure) __HYBRID_TAILQ_TRYREMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define TAILQ_TRYUNBIND_IF(self, out_pelem, type, key, condition, on_failure)       __HYBRID_TAILQ_TRYUNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define TAILQ_TRYUNBIND_IF_P(self, out_pelem, type, getpath, condition, on_failure) __HYBRID_TAILQ_TRYUNBIND_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define TAILQ_UNBINDALL(self, out_pelem, type, key, condition, on_match)            __HYBRID_TAILQ_UNBINDALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define TAILQ_UNBINDALL_P(self, out_pelem, type, getpath, condition, on_match)      __HYBRID_TAILQ_UNBINDALL(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_match)
#define TAILQ_UNBIND_IF(self, out_pelem, type, key, condition)                      __HYBRID_TAILQ_UNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define TAILQ_UNBIND_IF_P(self, out_pelem, type, getpath, condition)                __HYBRID_TAILQ_UNBIND_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition)
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_TAILQ_INSERT_HEAD(self, elem, X, _) \
	__HYBRID_TAILQ_INSERT_HEAD_R(self, elem, elem, X, _)
#define __HYBRID_TAILQ_INSERT_HEAD_R(self, lo_elem, hi_elem, X, _)              \
	(void)((X(_, hi_elem).tqe_next = (self)->tqh_first) != __NULLPTR            \
	       ? (void)(X(_, (self)->tqh_first).tqe_prev = &X(_, hi_elem).tqe_next) \
	       : (void)((self)->tqh_last = &X(_, hi_elem).tqe_next),                \
	       X(_, (self)->tqh_first = (lo_elem)).tqe_prev = &(self)->tqh_first)
#define __HYBRID_TAILQ_INSERT_TAIL(self, elem, X, _) \
	__HYBRID_TAILQ_INSERT_TAIL_R(self, elem, elem, X, _)
#define __HYBRID_TAILQ_INSERT_TAIL_R(self, lo_elem, hi_elem, X, _)    \
	(void)(*(X(_, lo_elem).tqe_prev = (self)->tqh_last)  = (lo_elem), \
	       *((self)->tqh_last = &X(_, hi_elem).tqe_next) = __NULLPTR)
#define __HYBRID_TAILQ_INSERT_AFTER(self, predecessor, elem, X, _) \
	__HYBRID_TAILQ_INSERT_AFTER_R(self, predecessor, elem, elem, X, _)
#define __HYBRID_TAILQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, X, _) \
	((X(_, hi_elem).tqe_next = X(_, predecessor).tqe_next) != __NULLPTR          \
	 ? (void)(X(_, X(_, hi_elem).tqe_next).tqe_prev = &X(_, hi_elem).tqe_next)   \
	 : (void)((self)->tqh_last = &X(_, hi_elem).tqe_next),                       \
	 (void)(*(X(_, lo_elem).tqe_prev = &X(_, predecessor).tqe_next) = (lo_elem)))
#define __HYBRID_TAILQ_INSERT_BEFORE(successor, elem, X, _) \
	__HYBRID_TAILQ_INSERT_BEFORE_R(successor, elem, elem, X, _)
#define __HYBRID_TAILQ_INSERT_BEFORE_R(successor, lo_elem, hi_elem, X, _)     \
	(void)(*(X(_, lo_elem).tqe_prev = X(_, successor).tqe_prev)  = (lo_elem), \
	       *(X(_, successor).tqe_prev = &X(_, hi_elem).tqe_next) = (successor))
#define __HYBRID_TAILQ_REPLACE(self, old_elem, new_elem, X, _) \
	__HYBRID_TAILQ_REPLACE_R(self, old_elem, old_elem, new_elem, new_elem, X, _)
#define __HYBRID_TAILQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, X, _) \
	((X(_, new_hi_elem).tqe_next = X(_, old_hi_elem).tqe_next) != __NULLPTR                      \
	 ? (void)(X(_, X(_, old_hi_elem).tqe_next).tqe_prev = (new_hi_elem))                         \
	 : (void)((self)->tqh_last = &X(_, new_hi_elem).tqe_next),                                   \
	 *(X(_, new_lo_elem).tqe_prev = X(_, old_lo_elem).tqe_prev) = (new_lo_elem),                 \
	 __HYBRID_Q_BADPTR(X(_, old_hi_elem).tqe_next),                                              \
	 __HYBRID_Q_BADPTR(X(_, old_lo_elem).tqe_prev))
#define __HYBRID_TAILQ_REMOVE_AFTER(self, elem, X, _)                        \
	((X(_, elem).tqe_next = X(_, X(_, elem).tqe_next).tqe_next) != __NULLPTR \
	 ? (void)(X(_, X(_, elem).tqe_next).tqe_prev = &X(_, elem).tqe_next)     \
	 : (void)((self)->tqh_last = &X(_, elem).tqe_next))
#define __HYBRID_TAILQ_REMOVE_HEAD(self, X, _)                           \
	(__HYBRID_Q_BADPTR(X(_, (self)->tqh_first).tqe_prev),                \
	 ((self)->tqh_first = X(_, (self)->tqh_first).tqe_next) != __NULLPTR \
	 ? (void)(X(_, (self)->tqh_first).tqe_prev = &(self)->tqh_first)     \
	 : (void)((self)->tqh_last = &(self)->tqh_first))
#define __HYBRID_TAILQ_REMOVE(self, elem, X, _) \
	__HYBRID_TAILQ_REMOVE_R(self, elem, elem, X, _)
#define __HYBRID_TAILQ_REMOVE_R(self, lo_elem, hi_elem, X, _)                 \
	((*X(_, lo_elem).tqe_prev = X(_, hi_elem).tqe_next) != __NULLPTR          \
	 ? (void)(X(_, X(_, hi_elem).tqe_next).tqe_prev = X(_, lo_elem).tqe_prev) \
	 : (void)((self)->tqh_last = X(_, lo_elem).tqe_prev),                     \
	 __HYBRID_Q_BADPTR(X(_, hi_elem).tqe_next),                               \
	 __HYBRID_Q_BADPTR(X(_, lo_elem).tqe_prev))
#define __HYBRID_TAILQ_UNBIND(self, elem, X, _)                               \
	(void)(X(_, elem).tqe_next != __NULLPTR                                   \
	       ? (void)(X(_, X(_, elem).tqe_next).tqe_prev = X(_, elem).tqe_prev) \
	       : (void)((self)->tqh_last = X(_, elem).tqe_prev),                  \
	       *X(_, elem).tqe_prev = X(_, elem).tqe_next,                        \
	       __HYBRID_Q_BADPTR(X(_, elem).tqe_next),                            \
	       X(_, elem).tqe_prev = __NULLPTR)
#define __HYBRID_TAILQ_REMOVEALL(self, out_pelem, T, X, _, condition, on_match)  \
	/* Sorry, this one must be a statement */                                    \
	do {                                                                         \
		T **__htqra_piter = &(self)->tqh_first;                                  \
		while ((*(out_pelem) = *__htqra_piter) != __NULLPTR) {                   \
			if (condition) {                                                     \
				if ((*__htqra_piter = X(_, *(out_pelem)).tqe_next) != __NULLPTR) \
					X(_, X(_, *(out_pelem)).tqe_next).tqe_prev = __htqra_piter;  \
				else {                                                           \
					(self)->tqh_last = __htqra_piter;                            \
				}                                                                \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).tqe_next);                  \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).tqe_prev);                  \
				on_match;                                                        \
			} else {                                                             \
				__htqra_piter = &X(_, *(out_pelem)).tqe_next;                    \
			}                                                                    \
		}                                                                        \
	}	__WHILE0
#define __HYBRID_TAILQ_UNBINDALL(self, out_pelem, T, X, _, condition, on_match)  \
	/* Sorry, this one must be a statement */                                    \
	do {                                                                         \
		T **__htqra_piter = &(self)->tqh_first;                                  \
		while ((*(out_pelem) = *__htqra_piter) != __NULLPTR) {                   \
			if (condition) {                                                     \
				if ((*__htqra_piter = X(_, *(out_pelem)).tqe_next) != __NULLPTR) \
					X(_, X(_, *(out_pelem)).tqe_next).tqe_prev = __htqra_piter;  \
				else {                                                           \
					(self)->tqh_last = __htqra_piter;                            \
				}                                                                \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).tqe_next);                  \
				X(_, *(out_pelem)).tqe_prev = __NULLPTR;                         \
				on_match;                                                        \
			} else {                                                             \
				__htqra_piter = &X(_, *(out_pelem)).tqe_next;                    \
			}                                                                    \
		}                                                                        \
	}	__WHILE0
#define __HYBRID_TAILQ_REMOVE_IF(self, out_pelem, T, X, _, condition)    \
	/* Sorry, this one must be a statement */                            \
	do {                                                                 \
		T **__htqri_piter = &(self)->tqh_first;                          \
		for (;;) {                                                       \
			*(out_pelem) = *__htqri_piter;                               \
			if (condition)                                               \
				break;                                                   \
			__htqri_piter = &X(_, *(out_pelem)).tqe_next;                \
		}                                                                \
		if ((*__htqri_piter = X(_, *(out_pelem)).tqe_next) != __NULLPTR) \
			X(_, X(_, *(out_pelem)).tqe_next).tqe_prev = __htqri_piter;  \
		else {                                                           \
			(self)->tqh_last = __htqri_piter;                            \
		}                                                                \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).tqe_next);                  \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).tqe_prev);                  \
	}	__WHILE0
#define __HYBRID_TAILQ_UNBIND_IF(self, out_pelem, T, X, _, condition)    \
	/* Sorry, this one must be a statement */                            \
	do {                                                                 \
		T **__htqri_piter = &(self)->tqh_first;                          \
		for (;;) {                                                       \
			*(out_pelem) = *__htqri_piter;                               \
			if (condition)                                               \
				break;                                                   \
			__htqri_piter = &X(_, *(out_pelem)).tqe_next;                \
		}                                                                \
		if ((*__htqri_piter = X(_, *(out_pelem)).tqe_next) != __NULLPTR) \
			X(_, X(_, *(out_pelem)).tqe_next).tqe_prev = __htqri_piter;  \
		else {                                                           \
			(self)->tqh_last = __htqri_piter;                            \
		}                                                                \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).tqe_next);                  \
		X(_, *(out_pelem)).tqe_prev = __NULLPTR;                         \
	}	__WHILE0
#define __HYBRID_TAILQ_TRYREMOVE_IF(self, out_pelem, T, X, _, condition, on_failure) \
	/* Sorry, this one must be a statement */                                        \
	do {                                                                             \
		T **__htqtri_piter = &(self)->tqh_first;                                     \
		for (;;) {                                                                   \
			if ((*(out_pelem) = *__htqtri_piter) == __NULLPTR) {                     \
				on_failure;                                                          \
				break;                                                               \
			}                                                                        \
			if (condition) {                                                         \
				if ((*__htqtri_piter = X(_, *(out_pelem)).tqe_next) != __NULLPTR)    \
					X(_, X(_, *(out_pelem)).tqe_next).tqe_prev = __htqtri_piter;     \
				else {                                                               \
					(self)->tqh_last = __htqtri_piter;                               \
				}                                                                    \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).tqe_next);                      \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).tqe_prev);                      \
				break;                                                               \
			}                                                                        \
			__htqtri_piter = &X(_, *(out_pelem)).tqe_next;                           \
		}                                                                            \
	}	__WHILE0
#define __HYBRID_TAILQ_TRYUNBIND_IF(self, out_pelem, T, X, _, condition, on_failure) \
	/* Sorry, this one must be a statement */                                        \
	do {                                                                             \
		T **__htqtri_piter = &(self)->tqh_first;                                     \
		for (;;) {                                                                   \
			if ((*(out_pelem) = *__htqtri_piter) == __NULLPTR) {                     \
				on_failure;                                                          \
				break;                                                               \
			}                                                                        \
			if (condition) {                                                         \
				if ((*__htqtri_piter = X(_, *(out_pelem)).tqe_next) != __NULLPTR)    \
					X(_, X(_, *(out_pelem)).tqe_next).tqe_prev = __htqtri_piter;     \
				else {                                                               \
					(self)->tqh_last = __htqtri_piter;                               \
				}                                                                    \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).tqe_next);                      \
				X(_, *(out_pelem)).tqe_prev = __NULLPTR;                             \
				break;                                                               \
			}                                                                        \
			__htqtri_piter = &X(_, *(out_pelem)).tqe_next;                           \
		}                                                                            \
	}	__WHILE0
#define __HYBRID_TAILQ_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->tqh_first; (elem); (elem) = X(_, elem).tqe_next)
#define __HYBRID_TAILQ_FOREACH_FROM(elem, self, X, _) \
	for ((elem) ? (void)0 : (void)((elem) = (self)->tqh_first); (elem); (elem) = X(_, elem).tqe_next)
#define __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, HEAD_T, X, _)       \
	for ((elem) = *(((HEAD_T *)((self)->tqh_last))->tqh_last); (elem); \
	     (elem) = *(((HEAD_T *)(X(_, elem).tqe_prev))->tqh_last))
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM(elem, self, HEAD_T, X, _)                     \
	for ((elem) ? (void)0 : (void)((elem) = *(((HEAD_T *)((self)->tqh_last))->tqh_last)); \
	     (elem); (elem) = *(((HEAD_T *)(X(_, elem).tqe_prev))->tqh_last))
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_TAILQ_FOREACH_SAFE3(elem, self, X, _)          \
	if (((elem) = (self)->tqh_first, 0))                        \
		;                                                       \
	else                                                        \
		for (__typeof__(elem) __htqfs_tvar;                     \
		     (elem) && (__htqfs_tvar = X(_, elem).tqe_next, 1); \
		     (elem) = __htqfs_tvar)
#define __HYBRID_TAILQ_FOREACH_FROM_SAFE3(elem, self, X, _)         \
	if (((elem) ? (void)0 : (void)((elem) = (self)->tqh_first), 0)) \
		;                                                           \
	else                                                            \
		for (__typeof__(elem) __htqfs_tvar;                         \
		     (elem) && (__htqfs_tvar = X(_, elem).tqe_next, 1);     \
		     (elem) = __htqfs_tvar)
#define __HYBRID_TAILQ_FOREACH_REVERSE_SAFE3T(elem, self, T, X, _)            \
	if (((elem) = *((T ***)(self)->tqh_last[1]), 0))                          \
		;                                                                     \
	else                                                                      \
		for (__typeof__(elem) __htqfrs_tvar;                                  \
		     (elem) && (__htqfrs_tvar = *((T ***)X(_, elem).tqe_prev)[1], 1); \
		     (elem) = __htqfrs_tvar)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE3T(elem, self, T, X, _)         \
	if (((elem) ? (void)0 : (void)((elem) = *((T ***)(self)->tqh_last[1])), 0)) \
		;                                                                       \
	else                                                                        \
		for (__typeof__(elem) __htqfrs_tvar;                                    \
		     (elem) && (__htqfrs_tvar = *((T ***)X(_, elem).tqe_prev)[1], 1);   \
		     (elem) = __htqfrs_tvar)
#define __HYBRID_TAILQ_FOREACH_REVERSE_SAFE3(elem, self, HEAD_T, X, _)                    \
	if (((elem) = *(((HEAD_T *)((self)->tqh_last))->tqh_last), 0))                        \
		;                                                                                 \
	else                                                                                  \
		for (__typeof__(elem) __htqfrs_tvar;                                              \
		     (elem) && (__htqfrs_tvar = *(((HEAD_T *)X(_, elem).tqe_prev)->tqh_last), 1); \
		     (elem) = __htqfrs_tvar)
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE3(elem, self, HEAD_T, X, _)                   \
	if (((elem) ? (void)0 : (void)((elem) = *(((HEAD_T *)((self)->tqh_last))->tqh_last), 0))) \
		;                                                                                     \
	else                                                                                      \
		for (__typeof__(elem) __htqfrs_tvar;                                                  \
		     (elem) && (__htqfrs_tvar = *(((HEAD_T *)X(_, elem).tqe_prev)->tqh_last), 1);     \
		     (elem) = __htqfrs_tvar)
#endif /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define __HYBRID_TAILQ_FOREACH_SAFE4(elem, self, X, _, tvar) \
	for ((elem) = (head)->tqh_first;                         \
	     (elem) && ((tvar) = X(_, elem).tqe_next, 1);        \
	     (elem) = (tvar))
#define __HYBRID_TAILQ_FOREACH_FROM_SAFE4(elem, self, X, _, tvar) \
	for ((elem) ? (void)0 : (void)((elem) = (head)->tqh_first);   \
	     (elem) && ((tvar) = X(_, elem).tqe_next, 1);             \
	     (elem) = (tvar))
#define __HYBRID_TAILQ_FOREACH_REVERSE_SAFE4(elem, self, HEAD_T, X, _, tvar)   \
	for ((elem) = *(((HEAD_T *)((self)->tqh_last))->tqh_last);                 \
	     (elem) && ((tvar) = *(((HEAD_T *)X(_, elem).tqe_prev)->tqh_last), 1); \
	     (elem) = (tvar))
#define __HYBRID_TAILQ_FOREACH_REVERSE_FROM_SAFE4(elem, self, HEAD_T, X, _, tvar)         \
	for ((elem) ? (void)0 : (void)((elem) = *(((HEAD_T *)((self)->tqh_last))->tqh_last)); \
	     (elem) && ((tvar) = *(((HEAD_T *)X(_, elem).tqe_prev)->tqh_last), 1);            \
	     (elem) = (tvar))
#define __HYBRID_TAILQ_CONCAT(dst, src, X, _)                                       \
	((src)->tqh_first != __NULLPTR                                                  \
	 ? (void)(X(_, *(dst)->tqh_last = (src)->tqh_first).tqe_prev = (dst)->tqh_last, \
	          (dst)->tqh_last                                    = (src)->tqh_last, \
	          TAILQ_INIT(src))                                                      \
	 : (void)0)
#define __HYBRID_TAILQ_MOVE(dst, src, X, _)                                         \
	(void)((*((dst)->tqh_last = &(dst)->tqh_first) = (src)->tqh_first) != __NULLPTR \
	       ? (void)((dst)->tqh_last                 = (src)->tqh_last,              \
	                X(_, (dst)->tqh_first).tqe_prev = &(dst)->tqh_first)            \
	       : (void)0,                                                               \
	       *((src)->tqh_last = &(src)->tqh_first) = __NULLPTR)
#define __HYBRID_TAILQ_SWAP(l1, l2, T, X, _)                    \
	/* Sorry, this one must be a statement */                   \
	do {                                                        \
		T *__htqs_first = (l1)->tqh_first,                      \
		  **__htqs_last = (l1)->tqh_last;                       \
		(l1)->tqh_last  = (l2)->tqh_last;                       \
		(l2)->tqh_last  = __htqs_last;                          \
		if (((l1)->tqh_first = (l2)->tqh_first) != __NULLPTR) { \
			X(_, (l1)->tqh_first).tqe_prev = &(l1)->tqh_first;  \
		} else {                                                \
			(l1)->tqh_last = &(l1)->tqh_first;                  \
		}                                                       \
		if (((l2)->tqh_first = __htqs_first) != __NULLPTR) {    \
			X(_, __htqs_first).tqe_prev = &(l2)->tqh_first;     \
		} else {                                                \
			(l2)->tqh_last = &(l2)->tqh_first;                  \
		}                                                       \
	}	__WHILE0
#define __HYBRID_TAILQ_PREV(elem, HEAD_T, X, _) (*(((HEAD_T *)X(_, elem).tqe_prev)->tqh_last))
#define __HYBRID_TAILQ_PREV4(elem, T, X, _)     (*((T ***)X(_, elem).tqe_prev)[1])





/************************************************************************/
/* CIRCLEQ: Circular queue                                              */
/************************************************************************/
#ifdef __cplusplus
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef CIRCLEQ_HEAD
#undef CIRCLEQ_CLASS_HEAD
#define __HYBRID_CIRCLEQ_HEAD_1(type)                                     \
	struct {                                                              \
		union {                                                           \
			void *__cqh_first_ptr;             /* [1..1] First element */ \
			__HYBRID_Q_STRUCT type *cqh_first; /* [1..1] First element */ \
		};                                                                \
		union {                                                           \
			void *__cqh_last_ptr;             /* [1..1] Last element */   \
			__HYBRID_Q_STRUCT type *cqh_last; /* [1..1] Last element */   \
		};                                                                \
	}
#define __HYBRID_CIRCLEQ_HEAD_2(name, type)                               \
	struct name {                                                         \
		union {                                                           \
			void *__cqh_first_ptr;             /* [1..1] First element */ \
			__HYBRID_Q_STRUCT type *cqh_first; /* [1..1] First element */ \
		};                                                                \
		union {                                                           \
			void *__cqh_last_ptr;             /* [1..1] Last element */   \
			__HYBRID_Q_STRUCT type *cqh_last; /* [1..1] Last element */   \
		};                                                                \
	}
#define __HYBRID_CIRCLEQ_CLASS_HEAD_1(type)                              \
	struct {                                                             \
		union {                                                          \
			void *__cqh_first_ptr;            /* [1..1] First element */ \
			__HYBRID_Q_CLASS type *cqh_first; /* [1..1] First element */ \
		};                                                               \
		union {                                                          \
			void *__cqh_last_ptr;            /* [1..1] Last element */   \
			__HYBRID_Q_CLASS type *cqh_last; /* [1..1] Last element */   \
		};                                                               \
	}
#define __HYBRID_CIRCLEQ_CLASS_HEAD_2(name, type)                        \
	struct name {                                                        \
		union {                                                          \
			void *__cqh_first_ptr;            /* [1..1] First element */ \
			__HYBRID_Q_CLASS type *cqh_first; /* [1..1] First element */ \
		};                                                               \
		union {                                                          \
			void *__cqh_last_ptr;            /* [1..1] Last element */   \
			__HYBRID_Q_CLASS type *cqh_last; /* [1..1] Last element */   \
		};                                                               \
	}
#define CIRCLEQ_HEAD(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_HEAD_, (__VA_ARGS__))(__VA_ARGS__)       /* CIRCLEQ_HEAD([name], type) */
#define CIRCLEQ_CLASS_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_CLASS_HEAD_, (__VA_ARGS__))(__VA_ARGS__) /* CIRCLEQ_CLASS_HEAD([name], type) */
#else /* __HYBRID_PP_VA_OVERLOAD */
#define CIRCLEQ_HEAD(name, type)                                          \
	struct name {                                                         \
		union {                                                           \
			void *__cqh_first_ptr;             /* [1..1] First element */ \
			__HYBRID_Q_STRUCT type *cqh_first; /* [1..1] First element */ \
		};                                                                \
		union {                                                           \
			void *__cqh_last_ptr;             /* [1..1] Last element */   \
			__HYBRID_Q_STRUCT type *cqh_last; /* [1..1] Last element */   \
		};                                                                \
	}
#define CIRCLEQ_CLASS_HEAD(name, type)                                   \
	struct name {                                                        \
		union {                                                          \
			void *__cqh_first_ptr;            /* [1..1] First element */ \
			__HYBRID_Q_CLASS type *cqh_first; /* [1..1] First element */ \
		};                                                               \
		union {                                                          \
			void *__cqh_last_ptr;            /* [1..1] Last element */   \
			__HYBRID_Q_CLASS type *cqh_last; /* [1..1] Last element */   \
		};                                                               \
	}
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#define CIRCLEQ_HEAD_INITIALIZER(self) { { (void *)&(self) }, { (void *)&(self) } }
#else /* __cplusplus */
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_CIRCLEQ_HEAD_1(type)                                 \
	struct {                                                          \
		__HYBRID_Q_STRUCT type *cqh_first, /* [1..1] First element */ \
		*cqh_last;                         /* [1..1] Last element */  \
	}
#define __HYBRID_CIRCLEQ_HEAD_2(name, type)                           \
	struct name {                                                     \
		__HYBRID_Q_STRUCT type *cqh_first, /* [1..1] First element */ \
		*cqh_last;                         /* [1..1] Last element */  \
	}
#define __HYBRID_CIRCLEQ_CLASS_HEAD_1(type)                          \
	struct {                                                         \
		__HYBRID_Q_CLASS type *cqh_first, /* [1..1] First element */ \
		*cqh_last;                        /* [1..1] Last element */  \
	}
#define __HYBRID_CIRCLEQ_CLASS_HEAD_2(name, type)                    \
	struct name {                                                    \
		__HYBRID_Q_CLASS type *cqh_first, /* [1..1] First element */ \
		*cqh_last;                        /* [1..1] Last element */  \
	}
#undef CIRCLEQ_HEAD
#undef CIRCLEQ_CLASS_HEAD
#define CIRCLEQ_HEAD(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_HEAD_, (__VA_ARGS__))(__VA_ARGS__)
#define CIRCLEQ_CLASS_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_CLASS_HEAD_, (__VA_ARGS__))(__VA_ARGS__)
#else /* !__HYBRID_LIST_RESTRICT_API && __HYBRID_PP_VA_OVERLOAD */
#define CIRCLEQ_HEAD(name, type)                                      \
	struct name {                                                     \
		__HYBRID_Q_STRUCT type *cqh_first, /* [1..1] First element */ \
		*cqh_last;                         /* [1..1] Last element */  \
	}
#define CIRCLEQ_CLASS_HEAD(name, type)                               \
	struct name {                                                    \
		__HYBRID_Q_CLASS type *cqh_first, /* [1..1] First element */ \
		*cqh_last;                        /* [1..1] Last element */  \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__HYBRID_PP_VA_OVERLOAD */
#define CIRCLEQ_HEAD_INITIALIZER(self) { (void *)&self, (void *)&self }
#endif /* !__cplusplus */
#define CIRCLEQ_ENTRY(type)                                         \
	struct {                                                        \
		__HYBRID_Q_STRUCT type *cqe_next, /* [1..1] Next element */ \
		*cqe_prev;                        /* [1..1] Prev element */ \
	}
#define CIRCLEQ_CLASS_ENTRY(type)                                  \
	struct {                                                       \
		__HYBRID_Q_CLASS type *cqe_next, /* [1..1] Next element */ \
		*cqe_prev;                       /* [1..1] Prev element */ \
	}
#ifdef __cplusplus
#define CIRCLEQ_INIT(self)                                 (void)((self)->__cqh_first_ptr = (self)->__cqh_last_ptr = (void *)(self))
#else /* __cplusplus */
#define CIRCLEQ_INIT(self)                                 (void)((self)->cqh_first = (self)->cqh_last = (void *)(self))
#endif /* !__cplusplus */
#define CIRCLEQ_EMPTY(self)                                ((void const *)(self)->cqh_first == (void const *)(self))
#define CIRCLEQ_FIRST(self)                                (self)->cqh_first
#define CIRCLEQ_FOREACH(elem, self, key)                   __HYBRID_CIRCLEQ_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define CIRCLEQ_FOREACH_REVERSE(elem, self, key)           __HYBRID_CIRCLEQ_FOREACH_REVERSE(elem, self, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_AFTER(self, predecessor, elem, key) __HYBRID_CIRCLEQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_BEFORE(self, successor, elem, key)  __HYBRID_CIRCLEQ_INSERT_BEFORE(self, successor, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_HEAD(self, elem, key)               __HYBRID_CIRCLEQ_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_TAIL(self, elem, key)               __HYBRID_CIRCLEQ_INSERT_TAIL(self, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_LAST(self)                                 (self)->cqh_last
#define CIRCLEQ_LOOP_NEXT(self, elem, key)                 __HYBRID_CIRCLEQ_LOOP_NEXT(self, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_LOOP_PREV(self, elem, key)                 __HYBRID_CIRCLEQ_LOOP_PREV(self, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_NEXT(elem, key)                            (elem)->key.cqe_next
#define CIRCLEQ_PREV(elem, key)                            (elem)->key.cqe_prev
#define CIRCLEQ_REMOVE(self, elem, key)                    __HYBRID_CIRCLEQ_REMOVE(self, elem, __HYBRID_Q_KEY, key)
#ifndef __HYBRID_LIST_RESTRICT_API
#ifdef __cplusplus
#define CIRCLEQ_HEAD_P(T)                                     \
	struct {                                                  \
		union {                                               \
			void *__cqh_first_ptr; /* [1..1] First element */ \
			T *cqh_first;          /* [1..1] First element */ \
		};                                                    \
		union {                                               \
			void *__cqh_last_ptr; /* [1..1] Last element */   \
			T *cqh_last;          /* [1..1] Last element */   \
		};                                                    \
	}
#else /* __cplusplus */
#define CIRCLEQ_HEAD_P(T)                        \
	struct {                                     \
		T *cqh_first, /* [1..1] First element */ \
		*cqh_last;    /* [1..1] Last element */  \
	}
#endif /* !__cplusplus */
#define CIRCLEQ_ENTRY_P(T)                     \
	struct {                                   \
		T *cqe_next, /* [1..1] Next element */ \
		*cqe_prev;   /* [1..1] Prev element */ \
	}
#ifdef __cplusplus
#define CIRCLEQ_CLEAR(self) (void)((self)->__cqh_first_ptr = (self)->__cqh_last_ptr = (void *)(self))
#else /* __cplusplus */
#define CIRCLEQ_CLEAR(self) (void)((self)->cqh_first = (self)->cqh_last = (void *)(self))
#endif /* !__cplusplus */
#define CIRCLEQ_CONCAT(dst, src, key)                                                          __HYBRID_CIRCLEQ_CONCAT(dst, src, __HYBRID_Q_KEY, key)
#define CIRCLEQ_CONCAT_P(dst, src, getpath)                                                    __HYBRID_CIRCLEQ_CONCAT(dst, src, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_ENTRY_UNBOUND_INIT(entry)                                                      (void)(__HYBRID_Q_BADPTR((entry)->cqe_next), (entry)->cqe_prev = __NULLPTR)
#define CIRCLEQ_ENTRY_UNBOUND_INITIALIZER                                                      { __NULLPTR, __NULLPTR }
#define CIRCLEQ_ENTRY_UNBOUND_INITIALIZER_IS_ZERO
#define CIRCLEQ_FOREACH_FROM(elem, self, key)                                                  __HYBRID_CIRCLEQ_FOREACH_FROM(elem, self, __HYBRID_Q_KEY, key)
#define CIRCLEQ_FOREACH_FROM_P(elem, self, getpath)                                            __HYBRID_CIRCLEQ_FOREACH_FROM(elem, self, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_FOREACH_P(elem, self, getpath)                                                 __HYBRID_CIRCLEQ_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_FOREACH_REVERSE_FROM(elem, self, key)                                          __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM(elem, self, __HYBRID_Q_KEY, key)
#define CIRCLEQ_FOREACH_REVERSE_FROM_P(elem, self, getpath)                                    __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM(elem, self, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_FOREACH_REVERSE_P(elem, self, getpath)                                         __HYBRID_CIRCLEQ_FOREACH_REVERSE(elem, self, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_AFTER_P(self, predecessor, elem, getpath)                               __HYBRID_CIRCLEQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, key)                       __HYBRID_CIRCLEQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_AFTER_R_P(self, predecessor, lo_elem, hi_elem, getpath)                 __HYBRID_CIRCLEQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_BEFORE_P(self, successor, elem, getpath)                                __HYBRID_CIRCLEQ_INSERT_BEFORE(self, successor, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_BEFORE_R(self, successor, lo_elem, hi_elem, key)                        __HYBRID_CIRCLEQ_INSERT_BEFORE_R(self, successor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_BEFORE_R_P(self, successor, lo_elem, hi_elem, getpath)                  __HYBRID_CIRCLEQ_INSERT_BEFORE_R(self, successor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_HEAD_P(self, elem, getpath)                                             __HYBRID_CIRCLEQ_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_HEAD_R(self, lo_elem, hi_elem, key)                                     __HYBRID_CIRCLEQ_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_HEAD_R_P(self, lo_elem, hi_elem, getpath)                               __HYBRID_CIRCLEQ_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_TAIL_P(self, elem, getpath)                                             __HYBRID_CIRCLEQ_INSERT_TAIL(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_TAIL_R(self, lo_elem, hi_elem, key)                                     __HYBRID_CIRCLEQ_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_TAIL_R_P(self, lo_elem, hi_elem, getpath)                               __HYBRID_CIRCLEQ_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_ISBOUND(elem, key)                                                             ((elem)->key.cqe_prev != __NULLPTR)
#define CIRCLEQ_ISBOUND_P(elem, getpath)                                                       (getpath(elem).cqe_prev != __NULLPTR)
#define CIRCLEQ_LOOP_NEXT_P(self, elem, getpath)                                               __HYBRID_CIRCLEQ_LOOP_NEXT(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_LOOP_PREV_P(self, elem, getpath)                                               __HYBRID_CIRCLEQ_LOOP_PREV(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_MOVE(dst, src, key)                                                            __HYBRID_CIRCLEQ_MOVE(dst, src, __HYBRID_Q_KEY, key)
#define CIRCLEQ_MOVE_P(dst, src, getpath)                                                      __HYBRID_CIRCLEQ_MOVE(dst, src, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_NEXT_P(elem, getpath)                                                          getpath(elem).cqe_next
#define CIRCLEQ_PREV_P(elem, getpath)                                                          getpath(elem).cqe_prev
#define CIRCLEQ_REMOVE_AFTER(self, elem, key)                                                  __HYBRID_CIRCLEQ_REMOVE_AFTER(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_REMOVE_AFTER_P(self, elem, getpath)                                            __HYBRID_CIRCLEQ_REMOVE_AFTER(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_REMOVE_HEAD(self, key)                                                         __HYBRID_CIRCLEQ_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_REMOVE_HEAD_P(self, getpath)                                                   __HYBRID_CIRCLEQ_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_REMOVE_P(self, elem, getpath)                                                  __HYBRID_CIRCLEQ_REMOVE(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_REMOVE_R(self, lo_elem, hi_elem, key)                                          __HYBRID_CIRCLEQ_REMOVE_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_REMOVE_R_P(self, lo_elem, hi_elem, getpath)                                    __HYBRID_CIRCLEQ_REMOVE_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_REPLACE(self, old_elem, new_elem, key)                                         __HYBRID_CIRCLEQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_REPLACE_P(self, old_elem, new_elem, getpath)                                   __HYBRID_CIRCLEQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)       __HYBRID_CIRCLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_REPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath) __HYBRID_CIRCLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_UNBIND(self, elem, key)                                                        __HYBRID_CIRCLEQ_UNBIND(self, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_UNBIND_P(self, elem, getpath)                                                  __HYBRID_CIRCLEQ_UNBIND(self, elem, __HYBRID_Q_PTH, getpath)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE_3(elem, self, key)                                 __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE_4(elem, self, key, tvar)                           __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE_P_3(elem, self, getpath)                           __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE_P_4(elem, self, getpath, tvar)                     __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE_3(elem, self, key)                         __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE_4(elem, self, key, tvar)                   __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE_P_3(elem, self, getpath)                   __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE_P_4(elem, self, getpath, tvar)             __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE_3(elem, self, key)                              __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE_4(elem, self, key, tvar)                        __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE_P_3(elem, self, getpath)                        __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE_P_4(elem, self, getpath, tvar)                  __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_CIRCLEQ_FOREACH_SAFE_3(elem, self, key)                                      __HYBRID_CIRCLEQ_FOREACH_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_CIRCLEQ_FOREACH_SAFE_4(elem, self, key, tvar)                                __HYBRID_CIRCLEQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_CIRCLEQ_FOREACH_SAFE_P_3(elem, self, getpath)                                __HYBRID_CIRCLEQ_FOREACH_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_CIRCLEQ_FOREACH_SAFE_P_4(elem, self, getpath, tvar)                          __HYBRID_CIRCLEQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_CIRCLEQ_REMOVEALL_5(self, out_pelem, key, condition, on_match)               __HYBRID_CIRCLEQ_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_CIRCLEQ_REMOVEALL_6(self, out_pelem, type, key, condition, on_match)         __HYBRID_CIRCLEQ_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_CIRCLEQ_REMOVEALL_P_5(self, out_pelem, getpath, condition, on_match)         __HYBRID_CIRCLEQ_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_CIRCLEQ_REMOVEALL_P_6(self, out_pelem, T, getpath, condition, on_match)      __HYBRID_CIRCLEQ_REMOVEALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_CIRCLEQ_REMOVE_IF_4(self, out_pelem, key, condition)                         __HYBRID_CIRCLEQ_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_CIRCLEQ_REMOVE_IF_5(self, out_pelem, type, key, condition)                   __HYBRID_CIRCLEQ_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_CIRCLEQ_REMOVE_IF_P_4(self, out_pelem, getpath, condition)                   __HYBRID_CIRCLEQ_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_CIRCLEQ_REMOVE_IF_P_5(self, out_pelem, T, getpath, condition)                __HYBRID_CIRCLEQ_REMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_CIRCLEQ_SWAP_3(l1, l2, key)                                                  __HYBRID_CIRCLEQ_SWAP(l1, l2, __typeof__(*(l1)->cqh_first), __HYBRID_Q_KEY, key)
#define __HYBRID_CIRCLEQ_SWAP_4(l1, l2, type, key)                                            __HYBRID_CIRCLEQ_SWAP(l1, l2, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_CIRCLEQ_SWAP_P_3(l1, l2, getpath)                                            __HYBRID_CIRCLEQ_SWAP(l1, l2, __typeof__(*(l1)->cqh_first), __HYBRID_Q_PTH, getpath)
#define __HYBRID_CIRCLEQ_SWAP_P_4(l1, l2, T, getpath)                                         __HYBRID_CIRCLEQ_SWAP(l1, l2, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_CIRCLEQ_TRYREMOVE_IF_5(self, out_pelem, key, condition, on_failure)          __HYBRID_CIRCLEQ_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_CIRCLEQ_TRYREMOVE_IF_6(self, out_pelem, type, key, condition, on_failure)    __HYBRID_CIRCLEQ_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_CIRCLEQ_TRYREMOVE_IF_P_5(self, out_pelem, getpath, condition, on_failure)    __HYBRID_CIRCLEQ_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_CIRCLEQ_TRYREMOVE_IF_P_6(self, out_pelem, T, getpath, condition, on_failure) __HYBRID_CIRCLEQ_TRYREMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_CIRCLEQ_TRYUNBIND_IF_5(self, out_pelem, key, condition, on_failure)          __HYBRID_CIRCLEQ_TRYUNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_CIRCLEQ_TRYUNBIND_IF_6(self, out_pelem, type, key, condition, on_failure)    __HYBRID_CIRCLEQ_TRYUNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_CIRCLEQ_TRYUNBIND_IF_P_5(self, out_pelem, getpath, condition, on_failure)    __HYBRID_CIRCLEQ_TRYUNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_CIRCLEQ_TRYUNBIND_IF_P_6(self, out_pelem, T, getpath, condition, on_failure) __HYBRID_CIRCLEQ_TRYUNBIND_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_CIRCLEQ_UNBINDALL_5(self, out_pelem, key, condition, on_match)               __HYBRID_CIRCLEQ_UNBINDALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_CIRCLEQ_UNBINDALL_6(self, out_pelem, type, key, condition, on_match)         __HYBRID_CIRCLEQ_UNBINDALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_CIRCLEQ_UNBINDALL_P_5(self, out_pelem, getpath, condition, on_match)         __HYBRID_CIRCLEQ_UNBINDALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_CIRCLEQ_UNBINDALL_P_6(self, out_pelem, T, getpath, condition, on_match)      __HYBRID_CIRCLEQ_UNBINDALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_CIRCLEQ_UNBIND_IF_4(self, out_pelem, key, condition)                         __HYBRID_CIRCLEQ_UNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_CIRCLEQ_UNBIND_IF_5(self, out_pelem, type, key, condition)                   __HYBRID_CIRCLEQ_UNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_CIRCLEQ_UNBIND_IF_P_4(self, out_pelem, getpath, condition)                   __HYBRID_CIRCLEQ_UNBIND_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_CIRCLEQ_UNBIND_IF_P_5(self, out_pelem, T, getpath, condition)                __HYBRID_CIRCLEQ_UNBIND_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define CIRCLEQ_FOREACH_FROM_SAFE(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_FOREACH_FROM_SAFE_, (__VA_ARGS__))(__VA_ARGS__)           /* CIRCLEQ_FOREACH_FROM_SAFE(elem, self, key, [tvar]) */
#define CIRCLEQ_FOREACH_FROM_SAFE_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_FOREACH_FROM_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)         /* CIRCLEQ_FOREACH_FROM_SAFE_P(elem, self, getpath, [tvar]) */
#define CIRCLEQ_FOREACH_REVERSE_FROM_SAFE(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE_, (__VA_ARGS__))(__VA_ARGS__)   /* CIRCLEQ_FOREACH_REVERSE_FROM_SAFE(elem, self, key, [tvar]) */
#define CIRCLEQ_FOREACH_REVERSE_FROM_SAFE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__) /* CIRCLEQ_FOREACH_REVERSE_FROM_SAFE_P(elem, self, getpath, [tvar]) */
#define CIRCLEQ_FOREACH_REVERSE_SAFE(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE_, (__VA_ARGS__))(__VA_ARGS__)        /* CIRCLEQ_FOREACH_REVERSE_SAFE(elem, self, key, [tvar]) */
#define CIRCLEQ_FOREACH_REVERSE_SAFE_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)      /* CIRCLEQ_FOREACH_REVERSE_SAFE_P(elem, self, getpath, [tvar]) */
#define CIRCLEQ_FOREACH_SAFE(...)                __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_FOREACH_SAFE_, (__VA_ARGS__))(__VA_ARGS__)                /* CIRCLEQ_FOREACH_SAFE(elem, self, key, [tvar]) */
#define CIRCLEQ_FOREACH_SAFE_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_FOREACH_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)              /* CIRCLEQ_FOREACH_SAFE_P(elem, self, getpath, [tvar]) */
#define CIRCLEQ_REMOVEALL(...)                   __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)                /* CIRCLEQ_REMOVEALL(self, out_pelem, [type], key, condition, on_match) */
#define CIRCLEQ_REMOVEALL_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)              /* CIRCLEQ_REMOVEALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define CIRCLEQ_REMOVE_IF(...)                   __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_REMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)                   /* CIRCLEQ_REMOVE_IF(self, out_pelem, [type], key, condition) */
#define CIRCLEQ_REMOVE_IF_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_REMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)                 /* CIRCLEQ_REMOVE_IF_P(self, out_pelem, [T], getpath, condition) */
#define CIRCLEQ_SWAP(...)                        __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_SWAP_, (__VA_ARGS__))(__VA_ARGS__)                        /* CIRCLEQ_SWAP(l1, l2, [type], key) */
#define CIRCLEQ_SWAP_P(...)                      __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_SWAP_P_, (__VA_ARGS__))(__VA_ARGS__)                      /* CIRCLEQ_SWAP_P(l1, l2, [T], key) */
#define CIRCLEQ_TRYREMOVE_IF(...)                __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)                /* CIRCLEQ_TRYREMOVE_IF(self, out_pelem, [type], key, condition, on_failure) */
#define CIRCLEQ_TRYREMOVE_IF_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)              /* CIRCLEQ_TRYREMOVE_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#define CIRCLEQ_TRYUNBIND_IF(...)                __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_TRYUNBIND_IF_, (__VA_ARGS__))(__VA_ARGS__)                /* CIRCLEQ_TRYUNBIND_IF(self, out_pelem, [type], key, condition, on_failure) */
#define CIRCLEQ_TRYUNBIND_IF_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_TRYUNBIND_IF_P_, (__VA_ARGS__))(__VA_ARGS__)              /* CIRCLEQ_TRYUNBIND_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#define CIRCLEQ_UNBINDALL(...)                   __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_UNBINDALL_, (__VA_ARGS__))(__VA_ARGS__)                   /* CIRCLEQ_UNBINDALL(self, out_pelem, [type], key, condition, on_match) */
#define CIRCLEQ_UNBINDALL_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_UNBINDALL_P_, (__VA_ARGS__))(__VA_ARGS__)                 /* CIRCLEQ_UNBINDALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define CIRCLEQ_UNBIND_IF(...)                   __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_UNBIND_IF_, (__VA_ARGS__))(__VA_ARGS__)                   /* CIRCLEQ_UNBIND_IF(self, out_pelem, [type], key, condition) */
#define CIRCLEQ_UNBIND_IF_P(...)                 __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_UNBIND_IF_P_, (__VA_ARGS__))(__VA_ARGS__)                 /* CIRCLEQ_UNBIND_IF_P(self, out_pelem, [T], getpath, condition) */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define CIRCLEQ_FOREACH_FROM_SAFE(elem, self, key, tvar)                              __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define CIRCLEQ_FOREACH_FROM_SAFE_P(elem, self, getpath, tvar)                        __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define CIRCLEQ_FOREACH_REVERSE_FROM_SAFE(elem, self, key, tvar)                      __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define CIRCLEQ_FOREACH_REVERSE_FROM_SAFE_P(elem, self, getpath, tvar)                __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define CIRCLEQ_FOREACH_REVERSE_SAFE(elem, self, key, tvar)                           __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define CIRCLEQ_FOREACH_REVERSE_SAFE_P(elem, self, getpath, tvar)                     __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define CIRCLEQ_FOREACH_SAFE(elem, self, key, tvar)                                   __HYBRID_CIRCLEQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define CIRCLEQ_FOREACH_SAFE_P(elem, self, getpath, tvar)                             __HYBRID_CIRCLEQ_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define CIRCLEQ_REMOVEALL(self, out_pelem, type, key, condition, on_match)            __HYBRID_CIRCLEQ_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define CIRCLEQ_REMOVEALL_P(self, out_pelem, type, getpath, condition, on_match)      __HYBRID_CIRCLEQ_REMOVEALL(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_match)
#define CIRCLEQ_REMOVE_IF(self, out_pelem, type, key, condition)                      __HYBRID_CIRCLEQ_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define CIRCLEQ_REMOVE_IF_P(self, out_pelem, type, getpath, condition)                __HYBRID_CIRCLEQ_REMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition)
#define CIRCLEQ_SWAP(l1, l2, type, key)                                               __HYBRID_CIRCLEQ_SWAP(l1, l2, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define CIRCLEQ_SWAP_P(l1, l2, T, getpath)                                            __HYBRID_CIRCLEQ_SWAP(l1, l2, T, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_TRYREMOVE_IF(self, out_pelem, type, key, condition, on_failure)       __HYBRID_CIRCLEQ_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define CIRCLEQ_TRYREMOVE_IF_P(self, out_pelem, type, getpath, condition, on_failure) __HYBRID_CIRCLEQ_TRYREMOVE_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define CIRCLEQ_TRYUNBIND_IF(self, out_pelem, type, key, condition, on_failure)       __HYBRID_CIRCLEQ_TRYUNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define CIRCLEQ_TRYUNBIND_IF_P(self, out_pelem, type, getpath, condition, on_failure) __HYBRID_CIRCLEQ_TRYUNBIND_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define CIRCLEQ_UNBINDALL(self, out_pelem, type, key, condition, on_match)            __HYBRID_CIRCLEQ_UNBINDALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define CIRCLEQ_UNBINDALL_P(self, out_pelem, type, getpath, condition, on_match)      __HYBRID_CIRCLEQ_UNBINDALL(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition, on_match)
#define CIRCLEQ_UNBIND_IF(self, out_pelem, type, key, condition)                      __HYBRID_CIRCLEQ_UNBIND_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define CIRCLEQ_UNBIND_IF_P(self, out_pelem, type, getpath, condition)                __HYBRID_CIRCLEQ_UNBIND_IF(self, out_pelem, type, __HYBRID_Q_PTH, getpath, condition)
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_CIRCLEQ_CONCAT(dst, src, X, _)                                         \
	(CIRCLEQ_EMPTY(src)                                                                 \
	 ? (void)0                                                                          \
	 : (CIRCLEQ_EMPTY(dst)                                                              \
	    ? (void)(*(void **)&X(_, (dst)->cqh_first = (src)->cqh_first).cqe_prev = (dst), \
	             *(void **)&X(_, (dst)->cqh_last = (src)->cqh_last).cqe_next   = (dst)) \
	    : (void)(X(_, (src)->cqh_first).cqe_prev = (dst)->cqh_last,                     \
	             X(_, (dst)->cqh_last).cqe_next  = (src)->cqh_first,                    \
	             (dst)->cqh_last                 = (src)->cqh_last),                    \
	    CIRCLEQ_INIT(src)))
#define __HYBRID_CIRCLEQ_SWAP(l1, l2, T, X, _)                                  \
	/* Sorry, this one must be a statement */                                   \
	do {                                                                        \
		T *__hcqs_first = (l1)->cqh_first,                                      \
		  *__hcqs_last  = (l1)->cqh_last;                                       \
		if (CIRCLEQ_EMPTY(l2)) {                                                \
			CIRCLEQ_INIT(l1);                                                   \
		} else {                                                                \
			*(void **)&X(_, (l1)->cqh_first = (l2)->cqh_first).cqe_prev = (l1); \
			*(void **)&X(_, (l1)->cqh_last = (l2)->cqh_last).cqe_next   = (l1); \
		}                                                                       \
		if ((void const *)__hcqs_first == (void const *)(l1)) {                 \
			CIRCLEQ_INIT(l2);                                                   \
		} else {                                                                \
			*(void **)&X(_, (l2)->cqh_first = __hcqs_first).cqe_prev = (l2);    \
			*(void **)&X(_, (l2)->cqh_last = __hcqs_last).cqe_next   = (l2);    \
		}                                                                       \
	}	__WHILE0
#define __HYBRID_CIRCLEQ_MOVE(dst, src, X, _)                                        \
	(CIRCLEQ_EMPTY(src)                                                              \
	 ? CIRCLEQ_INIT(dst)                                                             \
	 : (void)(*(void **)&X(_, (dst)->cqh_first = (src)->cqh_first).cqe_prev = (dst), \
	          *(void **)&X(_, (dst)->cqh_last = (src)->cqh_last).cqe_next   = (dst), \
	          CIRCLEQ_INIT(src)))
#define __HYBRID_CIRCLEQ_INSERT_AFTER(self, predecessor, elem, X, _) \
	__HYBRID_CIRCLEQ_INSERT_AFTER_R(self, predecessor, elem, elem, X, _)
#define __HYBRID_CIRCLEQ_INSERT_AFTER_R(self, predecessor, lo_elem, hi_elem, X, _) \
	(void)((void *)X(_, predecessor).cqe_next == (void *)(self)                    \
	       ? (void)((self)->cqh_last = (hi_elem))                                  \
	       : (void)(X(_, X(_, predecessor).cqe_next).cqe_prev = (hi_elem)),        \
	       X(_, hi_elem).cqe_next     = X(_, predecessor).cqe_next,                \
	       X(_, lo_elem).cqe_prev     = (predecessor),                             \
	       X(_, predecessor).cqe_next = (lo_elem))
#define __HYBRID_CIRCLEQ_INSERT_BEFORE(self, successor, elem, X, _) \
	__HYBRID_CIRCLEQ_INSERT_BEFORE_R(self, successor, elem, elem, X, _)
#define __HYBRID_CIRCLEQ_INSERT_BEFORE_R(self, successor, lo_elem, hi_elem, X, _) \
	(void)((void *)X(_, successor).cqe_prev == (void *)(self)                     \
	       ? (void)((self)->cqh_first = (lo_elem))                                \
	       : (void)(X(_, X(_, successor).cqe_prev).cqe_next = (lo_elem)),         \
	       X(_, successor).cqe_prev = (hi_elem),                                  \
	       X(_, hi_elem).cqe_next   = (successor),                                \
	       X(_, lo_elem).cqe_prev   = X(_, successor).cqe_prev)
#define __HYBRID_CIRCLEQ_INSERT_HEAD(self, elem, X, _) \
	__HYBRID_CIRCLEQ_INSERT_HEAD_R(self, elem, elem, X, _)
#define __HYBRID_CIRCLEQ_INSERT_HEAD_R(self, lo_elem, hi_elem, X, _) \
	(void)((void *)(self)->cqh_last == (void *)(self)                \
	       ? (void)((self)->cqh_last = (hi_elem))                    \
	       : (void)(X(_, (self)->cqh_first).cqe_prev = (hi_elem)),   \
	       X(_, hi_elem).cqe_next            = (self)->cqh_first,    \
	       (self)->cqh_first                 = (lo_elem),            \
	       *(void **)&X(_, lo_elem).cqe_prev = (void *)(self))
#define __HYBRID_CIRCLEQ_INSERT_TAIL(self, elem, X, _) \
	__HYBRID_CIRCLEQ_INSERT_TAIL_R(self, elem, elem, X, _)
#define __HYBRID_CIRCLEQ_INSERT_TAIL_R(self, lo_elem, hi_elem, X, _) \
	(void)((void *)(self)->cqh_first == (void *)(self)               \
	       ? (void)((self)->cqh_first = (lo_elem))                   \
	       : (void)(X(_, (self)->cqh_last).cqe_next = (lo_elem)),    \
	       X(_, lo_elem).cqe_prev            = (self)->cqh_last,     \
	       (self)->cqh_last                  = (hi_elem),            \
	       *(void **)&X(_, hi_elem).cqe_next = (void *)(self))
#define __HYBRID_CIRCLEQ_REPLACE(self, old_elem, new_elem, X, _) \
	__HYBRID_CIRCLEQ_REPLACE_R(self, old_elem, old_elem, new_elem, new_elem, X, _)
#define __HYBRID_CIRCLEQ_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, X, _) \
	((void *)(X(_, new_lo_elem).cqe_prev = X(_, old_lo_elem).cqe_prev) == (void *)(self)           \
	 ? (void)((self)->cqh_first = (new_lo_elem))                                                   \
	 : (void)(X(_, X(_, new_lo_elem).cqe_prev).cqe_next = (new_lo_elem)),                          \
	 (void *)(X(_, new_hi_elem).cqe_next = X(_, old_hi_elem).cqe_next) == (void *)(self)           \
	 ? (void)((self)->cqh_last = (new_hi_elem))                                                    \
	 : (void)(X(_, X(_, new_hi_elem).cqe_next).cqe_prev = (new_hi_elem)),                          \
	 __HYBRID_Q_BADPTR(X(_, old_hi_elem).cqe_next),                                                \
	 __HYBRID_Q_BADPTR(X(_, old_lo_elem).cqe_prev))
#define __HYBRID_CIRCLEQ_REMOVE_AFTER(self, elem, X, _)                                   \
	(__HYBRID_Q_BADPTR(X(_, X(_, elem).cqe_next).cqe_prev),                               \
	 (void *)(X(_, elem).cqe_next = X(_, X(_, elem).cqe_next).cqe_next) == (void *)(self) \
	 ? (void)((self)->cqh_last = (elem))                                                  \
	 : (void)(X(_, X(_, elem).cqe_next).cqe_prev = (elem)))
#define __HYBRID_CIRCLEQ_REMOVE_HEAD(self, X, _)                        \
	(__HYBRID_Q_BADPTR(X(_, (self)->cqh_first).cqe_prev),               \
	 (self)->cqh_first == (self)->cqh_last /* Only 1 elem remains... */ \
	 ? CIRCLEQ_INIT(self)                  /* Last elem removed */      \
	 : (void)(*(void **)&X(_, (self)->cqh_first = X(_, (self)->cqh_first).cqe_next).cqe_prev = (void *)(self))
#define __HYBRID_CIRCLEQ_REMOVE(self, elem, X, _) \
	__HYBRID_CIRCLEQ_REMOVE_R(self, elem, elem, X, _)
#define __HYBRID_CIRCLEQ_REMOVE_R(self, lo_elem, hi_elem, X, _)                \
	((void *)X(_, lo_elem).cqe_prev == (void *)(self)                          \
	 ? (void)((self)->cqh_first = X(_, hi_elem).cqe_next)                      \
	 : (void)(X(_, X(_, lo_elem).cqe_prev).cqe_next = X(_, hi_elem).cqe_next), \
	 (void *)X(_, hi_elem).cqe_next == (void *)(self)                          \
	 ? (void)((self)->cqh_last = X(_, lo_elem).cqe_prev)                       \
	 : (void)(X(_, X(_, hi_elem).cqe_next).cqe_prev = X(_, lo_elem).cqe_prev), \
	 __HYBRID_Q_BADPTR(X(_, hi_elem).cqe_next),                                \
	 __HYBRID_Q_BADPTR(X(_, lo_elem).cqe_prev))
#define __HYBRID_CIRCLEQ_UNBIND(self, elem, X, _)                              \
	(void)((void *)X(_, elem).cqe_prev == (void *)(self)                       \
	       ? (void)((self)->cqh_first = X(_, elem).cqe_next)                   \
	       : (void)(X(_, X(_, elem).cqe_prev).cqe_next = X(_, elem).cqe_next), \
	       (void *)X(_, elem).cqe_next == (void *)(self)                       \
	       ? (void)((self)->cqh_last = X(_, elem).cqe_prev)                    \
	       : (void)(X(_, X(_, elem).cqe_next).cqe_prev = X(_, elem).cqe_prev), \
	       __HYBRID_Q_BADPTR(X(_, elem).cqe_next),                             \
	       X(_, elem).cqe_prev = __NULLPTR)
#define __HYBRID_CIRCLEQ_REMOVEALL(self, out_pelem, T, X, _, condition, on_match)             \
	/* Sorry, this one must be a statement */                                                 \
	do {                                                                                      \
		T **__htqra_piter = &(self)->cqh_first;                                               \
		while ((*(out_pelem) = *__htqra_piter) != (void *)(self)) {                           \
			if (condition) {                                                                  \
				if ((void *)(*__htqra_piter = X(_, *(out_pelem)).cqe_next) != (void *)(self)) \
					X(_, X(_, *(out_pelem)).cqe_next).cqe_prev = __htqra_piter;               \
				else if (__htqra_piter == &(self)->cqh_first)                                 \
					*(void **)&(self)->cqh_last = (void *)(self);                             \
				else {                                                                        \
					(self)->cqh_last = __htqra_piter;                                         \
				}                                                                             \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).cqe_next);                               \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).cqe_prev);                               \
				on_match;                                                                     \
			} else {                                                                          \
				__htqra_piter = &X(_, *(out_pelem)).cqe_next;                                 \
			}                                                                                 \
		}                                                                                     \
	}	__WHILE0
#define __HYBRID_CIRCLEQ_UNBINDALL(self, out_pelem, T, X, _, condition, on_match)             \
	/* Sorry, this one must be a statement */                                                 \
	do {                                                                                      \
		T **__htqra_piter = &(self)->cqh_first;                                               \
		while ((*(out_pelem) = *__htqra_piter) != (void *)(self)) {                           \
			if (condition) {                                                                  \
				if ((void *)(*__htqra_piter = X(_, *(out_pelem)).cqe_next) != (void *)(self)) \
					X(_, X(_, *(out_pelem)).cqe_next).cqe_prev = __htqra_piter;               \
				else if (__htqra_piter == &(self)->cqh_first)                                 \
					*(void **)&(self)->cqh_last = (void *)(self);                             \
				else {                                                                        \
					(self)->cqh_last = __htqra_piter;                                         \
				}                                                                             \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).cqe_next);                               \
				X(_, *(out_pelem)).cqe_prev = __NULLPTR;                                      \
				on_match;                                                                     \
			} else {                                                                          \
				__htqra_piter = &X(_, *(out_pelem)).cqe_next;                                 \
			}                                                                                 \
		}                                                                                     \
	}	__WHILE0
#define __HYBRID_CIRCLEQ_REMOVE_IF(self, out_pelem, T, X, _, condition)               \
	/* Sorry, this one must be a statement */                                         \
	do {                                                                              \
		T **__htqri_piter = &(self)->cqh_first;                                       \
		for (;;) {                                                                    \
			*(out_pelem) = *__htqri_piter;                                            \
			if (condition)                                                            \
				break;                                                                \
			__htqri_piter = &X(_, *(out_pelem)).cqe_next;                             \
		}                                                                             \
		if ((void *)(*__htqri_piter = X(_, *(out_pelem)).cqe_next) != (void *)(self)) \
			X(_, X(_, *(out_pelem)).cqe_next).cqe_prev = __htqri_piter;               \
		else if (__htqri_piter == &(self)->cqh_first)                                 \
			*(void **)&(self)->cqh_last = (void *)(self);                             \
		else {                                                                        \
			(self)->cqh_last = __htqri_piter;                                         \
		}                                                                             \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).cqe_next);                               \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).cqe_prev);                               \
	}	__WHILE0
#define __HYBRID_CIRCLEQ_UNBIND_IF(self, out_pelem, T, X, _, condition)               \
	/* Sorry, this one must be a statement */                                         \
	do {                                                                              \
		T **__htqri_piter = &(self)->cqh_first;                                       \
		for (;;) {                                                                    \
			*(out_pelem) = *__htqri_piter;                                            \
			if (condition)                                                            \
				break;                                                                \
			__htqri_piter = &X(_, *(out_pelem)).cqe_next;                             \
		}                                                                             \
		if ((void *)(*__htqri_piter = X(_, *(out_pelem)).cqe_next) != (void *)(self)) \
			X(_, X(_, *(out_pelem)).cqe_next).cqe_prev = __htqri_piter;               \
		else if (__htqri_piter == &(self)->cqh_first)                                 \
			*(void **)&(self)->cqh_last = (void *)(self);                             \
		else {                                                                        \
			(self)->cqh_last = __htqri_piter;                                         \
		}                                                                             \
		__HYBRID_Q_BADPTR(X(_, *(out_pelem)).cqe_next);                               \
		X(_, *(out_pelem)).cqe_prev = __NULLPTR;                                      \
	}	__WHILE0
#define __HYBRID_CIRCLEQ_TRYREMOVE_IF(self, out_pelem, T, X, _, condition, on_failure)         \
	/* Sorry, this one must be a statement */                                                  \
	do {                                                                                       \
		T **__htqtri_piter = &(self)->cqh_first;                                               \
		for (;;) {                                                                             \
			if ((*(out_pelem) = *__htqtri_piter) == __NULLPTR) {                               \
				on_failure;                                                                    \
				break;                                                                         \
			}                                                                                  \
			if (condition) {                                                                   \
				if ((void *)(*__htqtri_piter = X(_, *(out_pelem)).cqe_next) != (void *)(self)) \
					X(_, X(_, *(out_pelem)).cqe_next).cqe_prev = __htqtri_piter;               \
				else if (__htqtri_piter == &(self)->cqh_first)                                 \
					*(void **)&(self)->cqh_last = (void *)(self);                              \
				else {                                                                         \
					(self)->cqh_last = __htqtri_piter;                                         \
				}                                                                              \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).cqe_next);                                \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).cqe_prev);                                \
				break;                                                                         \
			}                                                                                  \
			__htqtri_piter = &X(_, *(out_pelem)).cqe_next;                                     \
		}                                                                                      \
	}	__WHILE0
#define __HYBRID_CIRCLEQ_TRYUNBIND_IF(self, out_pelem, T, X, _, condition, on_failure)         \
	/* Sorry, this one must be a statement */                                                  \
	do {                                                                                       \
		T **__htqtri_piter = &(self)->cqh_first;                                               \
		for (;;) {                                                                             \
			if ((*(out_pelem) = *__htqtri_piter) == __NULLPTR) {                               \
				on_failure;                                                                    \
				break;                                                                         \
			}                                                                                  \
			if (condition) {                                                                   \
				if ((void *)(*__htqtri_piter = X(_, *(out_pelem)).cqe_next) != (void *)(self)) \
					X(_, X(_, *(out_pelem)).cqe_next).cqe_prev = __htqtri_piter;               \
				else if (__htqtri_piter == &(self)->cqh_first)                                 \
					*(void **)&(self)->cqh_last = (void *)(self);                              \
				else {                                                                         \
					(self)->cqh_last = __htqtri_piter;                                         \
				}                                                                              \
				__HYBRID_Q_BADPTR(X(_, *(out_pelem)).cqe_next);                                \
				X(_, *(out_pelem)).cqe_prev = __NULLPTR;                                       \
				break;                                                                         \
			}                                                                                  \
			__htqtri_piter = &X(_, *(out_pelem)).cqe_next;                                     \
		}                                                                                      \
	}	__WHILE0
#define __HYBRID_CIRCLEQ_LOOP_NEXT(self, elem, X, _)           \
	((void const *)X(_, elem).cqe_next == (void const *)(self) \
	 ? (self)->cqh_first                                       \
	 : X(_, elem).cqe_next)
#define __HYBRID_CIRCLEQ_LOOP_PREV(self, elem, X, _)           \
	((void const *)X(_, elem).cqe_prev == (void const *)(self) \
	 ? (self)->cqh_last                                        \
	 : X(_, elem).cqe_prev)
#define __HYBRID_CIRCLEQ_FOREACH(elem, self, X, _)     \
	for ((elem) = (self)->cqh_first;                   \
	     (void const *)(elem) != (void const *)(self); \
	     (elem) = X(_, elem).cqe_next)
#define __HYBRID_CIRCLEQ_FOREACH_FROM(elem, self, X, _)         \
	for ((elem) ? (void)0 : (void)((elem) = (self)->cqh_first); \
	     (void const *)(elem) != (void const *)(self);          \
	     (elem) = X(_, elem).cqe_next)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE(elem, self, X, _) \
	for ((elem) = (self)->cqh_last;                        \
	     (void const *)(elem) != (void const *)(self);     \
	     (elem) = (X(_, elem).cqe_prev))
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM(elem, self, X, _) \
	for ((elem) ? (void)0 : (void)((elem) = (self)->cqh_last);  \
	     (void const *)(elem) != (void const *)(self);          \
	     (elem) = (X(_, elem).cqe_prev))
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_CIRCLEQ_FOREACH_SAFE3(elem, self, X, _)        \
	if (((elem) = (self)->cqh_first, 0))                        \
		;                                                       \
	else                                                        \
		for (__typeof__(elem) __hcqfs_tvar;                     \
		     (elem) && (__hcqfs_tvar = X(_, elem).cqe_next, 1); \
		     (elem) = __hcqfs_tvar)
#define __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE3(elem, self, X, _)       \
	if (((elem) ? (void)0 : (void)((elem) = (self)->cqh_first), 0)) \
		;                                                           \
	else                                                            \
		for (__typeof__(elem) __hcqfs_tvar;                         \
		     (elem) && (__hcqfs_tvar = X(_, elem).cqe_next, 1);     \
		     (elem) = __hcqfs_tvar)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE3(elem, self, HEAD_T, X, _) \
	if (((elem) = (self)->cqh_last, 0))                                  \
		;                                                                \
	else                                                                 \
		for (__typeof__(elem) __hcqfrs_tvar;                             \
		     (elem) && (__hcqfrs_tvar = X(_, elem).cqe_prev, 1);         \
		     (elem) = __hcqfrs_tvar)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_FROM_SAFE3(elem, self, HEAD_T, X, _) \
	if (((elem) ? (void)0 : (void)((elem) = (self)->cqh_last), 0))            \
		;                                                                     \
	else                                                                      \
		for (__typeof__(elem) __hcqfrs_tvar;                                  \
		     (elem) && (__hcqfrs_tvar = X(_, elem).cqe_prev, 1);              \
		     (elem) = __hcqfrs_tvar)
#endif /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define __HYBRID_CIRCLEQ_FOREACH_SAFE4(elem, self, X, _, tvar) \
	for ((elem) = (head)->cqh_first;                           \
	     (elem) && ((tvar) = X(_, elem).cqe_next, 1);          \
	     (elem) = (tvar))
#define __HYBRID_CIRCLEQ_FOREACH_FROM_SAFE4(elem, self, X, _, tvar) \
	for ((elem) ? (void)0 : (void)((elem) = (head)->cqh_first);     \
	     (elem) && ((tvar) = X(_, elem).cqe_next, 1);               \
	     (elem) = (tvar))
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE_SAFE4(elem, self, HEAD_T, X, _, tvar) \
	for ((elem) = (head)->cqh_last;                                            \
	     (elem) && ((tvar) = X(_, elem).cqe_prev, 1);                          \
	     (elem) = (tvar))
#define __HYBRID_CIRCLEQ_FOREACH_FROM_REVERSE_SAFE4(elem, self, HEAD_T, X, _, tvar) \
	for ((elem) ? (void)0 : (void)((elem) = (head)->cqh_last);                      \
	     (elem) && ((tvar) = X(_, elem).cqe_prev, 1);                               \
	     (elem) = (tvar))





#ifndef __HYBRID_LIST_RESTRICT_API
/************************************************************************/
/* RINGQ: Head-less Ring-Queue                                          */
/************************************************************************/
#define RINGQ_ENTRY(type)                                           \
	struct {                                                        \
		__HYBRID_Q_STRUCT type *rqe_next, /* [1..1] Next element */ \
		*rqe_prev;                        /* [1..1] Prev element */ \
	}
#define RINGQ_CLASS_ENTRY(type)                                    \
	struct {                                                       \
		__HYBRID_Q_CLASS type *rqe_next, /* [1..1] Next element */ \
		*rqe_prev;                       /* [1..1] Prev element */ \
	}
#define RINGQ_ENTRY_P(T)                       \
	struct {                                   \
		T *rqe_next, /* [1..1] Next element */ \
		*rqe_prev;   /* [1..1] Prev element */ \
	}
#define RINGQ_ENTRY_UNBOUND_INIT(entry) (void)(__HYBRID_Q_BADPTR((entry)->rqe_next), (entry)->rqe_prev = __NULLPTR)
#define RINGQ_ENTRY_UNBOUND_INITIALIZER { __NULLPTR, __NULLPTR }
#define RINGQ_ENTRY_UNBOUND_INITIALIZER_IS_ZERO
#define RINGQ_ISBOUND(elem, key)        ((elem)->key.rqe_prev != __NULLPTR)
#define RINGQ_ISBOUND_P(elem, getpath)  (getpath(elem).rqe_prev != __NULLPTR)
#define RINGQ_UNBIND(elem, key)         __HYBRID_RINGQ_UNBIND(elem, __HYBRID_Q_KEY, key)
#define RINGQ_UNBIND_P(elem, getpath)   __HYBRID_RINGQ_UNBIND(elem, __HYBRID_Q_PTH, getpath)

/* RINGQ_INIT:          Initialize `elem' as the only element of a new ring.
 * RINGQ_NEXT:          Return the successor of `elem' within its ring.
 * RINGQ_PREV:          Return the predecessor of `elem' within its ring.
 * RINGQ_INSERT_AFTER:  Insert `elem' after `predecessor'
 * RINGQ_INSERT_BEFORE: Insert `elem' before `successor'
 * RINGQ_REMOVE:        Remove `elem' from its ring.
 * RINGQ_REPLACE:       Replace `old_elem' with `new_elem' from its ring. */
#define RINGQ_INIT(elem, key)                                                          __HYBRID_RINGQ_INIT(elem, __HYBRID_Q_KEY, key)
#define RINGQ_INIT_P(elem, getpath)                                                    __HYBRID_RINGQ_INIT(elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_INSERT_AFTER(predecessor, elem, key)                                     __HYBRID_RINGQ_INSERT_AFTER(predecessor, elem, __HYBRID_Q_KEY, key)
#define RINGQ_INSERT_AFTER_P(predecessor, elem, getpath)                               __HYBRID_RINGQ_INSERT_AFTER(predecessor, elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, key)                       __HYBRID_RINGQ_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define RINGQ_INSERT_AFTER_R_P(predecessor, lo_elem, hi_elem, getpath)                 __HYBRID_RINGQ_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_INSERT_BEFORE(successor, elem, key)                                      __HYBRID_RINGQ_INSERT_BEFORE(successor, elem, __HYBRID_Q_KEY, key)
#define RINGQ_INSERT_BEFORE_P(successor, elem, getpath)                                __HYBRID_RINGQ_INSERT_BEFORE(successor, elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_INSERT_BEFORE_R(successor, lo_elem, hi_elem, key)                        __HYBRID_RINGQ_INSERT_BEFORE_R(successor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define RINGQ_INSERT_BEFORE_R_P(successor, lo_elem, hi_elem, getpath)                  __HYBRID_RINGQ_INSERT_BEFORE_R(successor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_NEXT(elem, key)                                                          __HYBRID_RINGQ_NEXT(elem, __HYBRID_Q_KEY, key)
#define RINGQ_NEXT_P(elem, getpath)                                                    __HYBRID_RINGQ_NEXT(elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_PREV(elem, key)                                                          __HYBRID_RINGQ_PREV(elem, __HYBRID_Q_KEY, key)
#define RINGQ_PREV_P(elem, getpath)                                                    __HYBRID_RINGQ_PREV(elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_REMOVE(elem, key)                                                        __HYBRID_RINGQ_REMOVE(elem, __HYBRID_Q_KEY, key)
#define RINGQ_REMOVE_P(elem, getpath)                                                  __HYBRID_RINGQ_REMOVE(elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_REMOVE_R(lo_elem, hi_elem, key)                                          __HYBRID_RINGQ_REMOVE_R(lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define RINGQ_REMOVE_R_P(lo_elem, hi_elem, getpath)                                    __HYBRID_RINGQ_REMOVE_R(lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_REPLACE(old_elem, new_elem, key)                                         __HYBRID_RINGQ_REPLACE(old_elem, new_elem, __HYBRID_Q_KEY, key)
#define RINGQ_REPLACE_P(old_elem, new_elem, getpath)                                   __HYBRID_RINGQ_REPLACE(old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_REPLACE_R(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)       __HYBRID_RINGQ_REPLACE_R(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_KEY, key)
#define RINGQ_REPLACE_R_P(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath) __HYBRID_RINGQ_REPLACE_R(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_PTH, getpath)

#define __HYBRID_RINGQ_INIT(elem, X, _) (void)(X(_, elem).rqe_next = X(_, elem).rqe_prev = (elem))
#define __HYBRID_RINGQ_NEXT(elem, X, _) X(_, elem).rqe_next
#define __HYBRID_RINGQ_PREV(elem, X, _) X(_, elem).rqe_prev
#define __HYBRID_RINGQ_INSERT_AFTER(predecessor, elem, X, _) \
	__HYBRID_RINGQ_INSERT_AFTER_R(predecessor, elem, elem, X, _)
#define __HYBRID_RINGQ_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, X, _)                   \
	(void)(X(_, (X(_, hi_elem).rqe_next = X(_, predecessor).rqe_next)).rqe_prev = (hi_elem), \
	       X(_, (X(_, lo_elem).rqe_prev = (predecessor))).rqe_next              = (lo_elem))
#define __HYBRID_RINGQ_INSERT_BEFORE(successor, elem, X, _) \
	__HYBRID_RINGQ_INSERT_BEFORE_R(successor, elem, elem, X, _)
#define __HYBRID_RINGQ_INSERT_BEFORE_R(successor, lo_elem, hi_elem, X, _)                  \
	(void)(X(_, (X(_, lo_elem).rqe_prev = X(_, successor).rqe_prev)).rqe_next = (lo_elem), \
	       X(_, (X(_, hi_elem).rqe_next = (successor))).rqe_prev              = (hi_elem))
#define __HYBRID_RINGQ_REPLACE(old_elem, new_elem, X, _) \
	__HYBRID_RINGQ_REPLACE_R(old_elem, old_elem, new_elem, new_elem, X, _)
#define __HYBRID_RINGQ_REPLACE_R(old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, X, _)     \
	(X(_, (X(_, new_lo_elem).rqe_prev = X(_, old_lo_elem).rqe_prev)).rqe_next = (new_lo_elem), \
	 X(_, (X(_, new_hi_elem).rqe_next = X(_, old_hi_elem).rqe_next)).rqe_prev = (new_hi_elem), \
	 __HYBRID_Q_BADPTR(X(_, old_hi_elem).rqe_next),                                            \
	 __HYBRID_Q_BADPTR(X(_, old_lo_elem).rqe_prev))
#define __HYBRID_RINGQ_REMOVE(elem, X, _) \
	__HYBRID_RINGQ_REMOVE_R(elem, elem, X, _)
#define __HYBRID_RINGQ_REMOVE_R(lo_elem, hi_elem, X, _)              \
	(X(_, X(_, lo_elem).rqe_prev).rqe_next = X(_, hi_elem).rqe_next, \
	 X(_, X(_, hi_elem).rqe_next).rqe_prev = X(_, lo_elem).rqe_prev, \
	 __HYBRID_Q_BADPTR(X(_, hi_elem).rqe_next),                      \
	 __HYBRID_Q_BADPTR(X(_, lo_elem).rqe_prev))
#define __HYBRID_RINGQ_UNBIND(elem, X, _)                            \
	(void)(X(_, X(_, elem).rqe_prev).rqe_next = X(_, elem).rqe_next, \
	       X(_, X(_, elem).rqe_next).rqe_prev = X(_, elem).rqe_prev, \
	       __HYBRID_Q_BADPTR(X(_, elem).rqe_next),                   \
	       X(_, elem).rqe_prev = __NULLPTR)





/************************************************************************/
/* DLIST: Single-head, doubly-linked list (with direct prev-pointer)    */
/************************************************************************/
#ifdef __HYBRID_PP_VA_OVERLOAD
#define __HYBRID_DLIST_HEAD_1(type)             struct      { __HYBRID_Q_STRUCT type *dlh_first; /* [0..1] List head element. */ }
#define __HYBRID_DLIST_HEAD_2(name, type)       struct name { __HYBRID_Q_STRUCT type *dlh_first; /* [0..1] List head element. */ }
#define __HYBRID_DLIST_CLASS_HEAD_1(type)       struct      { __HYBRID_Q_CLASS  type *dlh_first; /* [0..1] List head element. */ }
#define __HYBRID_DLIST_CLASS_HEAD_2(name, type) struct name { __HYBRID_Q_CLASS  type *dlh_first; /* [0..1] List head element. */ }
#define DLIST_HEAD(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_HEAD_, (__VA_ARGS__))(__VA_ARGS__)       /* DLIST_HEAD([name], type) */
#define DLIST_CLASS_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_CLASS_HEAD_, (__VA_ARGS__))(__VA_ARGS__) /* DLIST_CLASS_HEAD([name], type) */
#else /* ... */
#define DLIST_HEAD(name, type)       struct name { __HYBRID_Q_STRUCT type *dlh_first; /* [0..1] List head element. */ }
#define DLIST_CLASS_HEAD(name, type) struct name { __HYBRID_Q_CLASS  type *dlh_first; /* [0..1] List head element. */ }
#endif /* !... */
#define DLIST_ENTRY(type)                                                  \
	struct {                                                               \
		__HYBRID_Q_STRUCT type *dle_next, /* [0..1] Successor element */   \
		*dle_prev;                        /* [0..1] Predecessor element */ \
	}
#define DLIST_CLASS_ENTRY(type)                                           \
	struct {                                                              \
		__HYBRID_Q_CLASS type *dle_next, /* [0..1] Successor element */   \
		*dle_prev;                       /* [0..1] Predecessor element */ \
	}
#define DLIST_ENTRY_P(T)                              \
	struct {                                          \
		T *dle_next, /* [0..1] Successor element */   \
		*dle_prev;   /* [0..1] Predecessor element */ \
	}
#define DLIST_CLEAR(self)                                                                    (void)((self)->dlh_first = __NULLPTR)
#define DLIST_EMPTY(self)                                                                    ((self)->dlh_first == __NULLPTR)
#define DLIST_END(self)                                                                      __NULLPTR
#define DLIST_FIRST(self)                                                                    (self)->dlh_first
#define DLIST_FOREACH(elem, self, key)                                                       __HYBRID_DLIST_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define DLIST_FOREACH_FROM(elem, self, key)                                                  __HYBRID_DLIST_FOREACH_FROM(elem, self, __HYBRID_Q_KEY, key)
#define DLIST_FOREACH_FROM_P(elem, self, getpath)                                            __HYBRID_DLIST_FOREACH_FROM(elem, self, __HYBRID_Q_PTH, getpath)
#define DLIST_FOREACH_P(elem, self, getpath)                                                 __HYBRID_DLIST_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define DLIST_HEAD_INITIALIZER(self)                                                         { __NULLPTR }
#define DLIST_HEAD_INITIALIZER_IS_NULL
#define DLIST_INIT(self)                                                                     (void)((self)->dlh_first = __NULLPTR)
#define DLIST_INSERT_AFTER(predecessor, elem, key)                                           __HYBRID_DLIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_KEY, key)
#define DLIST_INSERT_AFTER_P(predecessor, elem, getpath)                                     __HYBRID_DLIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_PTH, getpath)
#define DLIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, key)                             __HYBRID_DLIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define DLIST_INSERT_AFTER_R_P(predecessor, lo_elem, hi_elem, getpath)                       __HYBRID_DLIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define DLIST_INSERT_BEFORE(self, successor, elem, key)                                      __HYBRID_DLIST_INSERT_BEFORE(self, successor, elem, __HYBRID_Q_KEY, key)
#define DLIST_INSERT_BEFORE_P(self, successor, elem, getpath)                                __HYBRID_DLIST_INSERT_BEFORE(self, successor, elem, __HYBRID_Q_PTH, getpath)
#define DLIST_INSERT_BEFORE_R(self, successor, lo_elem, hi_elem, key)                        __HYBRID_DLIST_INSERT_BEFORE_R(self, successor, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define DLIST_INSERT_BEFORE_R_P(self, successor, lo_elem, hi_elem, getpath)                  __HYBRID_DLIST_INSERT_BEFORE_R(self, successor, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define DLIST_INSERT_HEAD(self, elem, key)                                                   __HYBRID_DLIST_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define DLIST_INSERT_HEAD_P(self, elem, getpath)                                             __HYBRID_DLIST_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define DLIST_INSERT_HEAD_R(self, lo_elem, hi_elem, key)                                     __HYBRID_DLIST_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define DLIST_INSERT_HEAD_R_P(self, lo_elem, hi_elem, getpath)                               __HYBRID_DLIST_INSERT_HEAD_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define DLIST_MOVE(dst, src)                                                                 (void)((dst)->dlh_first = (src)->dlh_first, (src)->dlh_first = __NULLPTR)
#define DLIST_NEXT(elem, key)                                                                (elem)->key.dle_next
#define DLIST_NEXT_P(elem, getpath)                                                          getpath(elem).dle_next
#define DLIST_PREV(elem, key)                                                                (elem)->key.dle_prev
#define DLIST_PREV_P(elem, getpath)                                                          getpath(elem).dle_prev
#define DLIST_REMOVE_AFTER(elem, key)                                                        __HYBRID_DLIST_REMOVE_AFTER(elem, __HYBRID_Q_KEY, key)
#define DLIST_REMOVE_AFTER_P(elem, getpath)                                                  __HYBRID_DLIST_REMOVE_AFTER(elem, __HYBRID_Q_PTH, getpath)
#define DLIST_REMOVE_HEAD(self, key)                                                         __HYBRID_DLIST_REMOVE_HEAD(self, __HYBRID_Q_KEY, key)
#define DLIST_REMOVE_HEAD_P(self, getpath)                                                   __HYBRID_DLIST_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#define DLIST_REMOVE(self, elem, key)                                                        __HYBRID_DLIST_REMOVE(self, elem, __HYBRID_Q_KEY, key)
#define DLIST_REMOVE_P(self, elem, getpath)                                                  __HYBRID_DLIST_REMOVE(self, elem, __HYBRID_Q_PTH, getpath)
#define DLIST_REMOVE_R(self, lo_elem, hi_elem, key)                                          __HYBRID_DLIST_REMOVE_R(self, lo_elem, hi_elem, __HYBRID_Q_KEY, key)
#define DLIST_REMOVE_R_P(self, lo_elem, hi_elem, getpath)                                    __HYBRID_DLIST_REMOVE_R(self, lo_elem, hi_elem, __HYBRID_Q_PTH, getpath)
#define DLIST_REPLACE(self, old_elem, new_elem, key)                                         __HYBRID_DLIST_REPLACE(self, old_elem, new_elem, __HYBRID_Q_KEY, key)
#define DLIST_REPLACE_P(self, old_elem, new_elem, getpath)                                   __HYBRID_DLIST_REPLACE(self, old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define DLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, key)       __HYBRID_DLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_KEY, key)
#define DLIST_REPLACE_R_P(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, getpath) __HYBRID_DLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, __HYBRID_Q_PTH, getpath)
#if defined(__HYBRID_PP_VA_OVERLOAD) && defined(__COMPILER_HAVE_TYPEOF)
#define __HYBRID_DLIST_CONCAT_3(dst, src, key)                                              __HYBRID_DLIST_CONCAT(dst, src, __typeof__(*(src)->lh_first), __HYBRID_Q_KEY, key)
#define __HYBRID_DLIST_CONCAT_4(dst, src, type, key)                                        __HYBRID_DLIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_DLIST_CONCAT_P_3(dst, src, getpath)                                        __HYBRID_DLIST_CONCAT(dst, src, __typeof__(*(src)->lh_first), __HYBRID_Q_PTH, getpath)
#define __HYBRID_DLIST_CONCAT_P_4(dst, src, T, getpath)                                     __HYBRID_DLIST_CONCAT(dst, src, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_DLIST_FOREACH_FROM_SAFE_3(elem, self, key)                                 __HYBRID_DLIST_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_DLIST_FOREACH_FROM_SAFE_4(elem, self, key, tvar)                           __HYBRID_DLIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_DLIST_FOREACH_FROM_SAFE_P_3(elem, self, getpath)                           __HYBRID_DLIST_FOREACH_FROM_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_DLIST_FOREACH_FROM_SAFE_P_4(elem, self, getpath, tvar)                     __HYBRID_DLIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_DLIST_FOREACH_SAFE_3(elem, self, key)                                      __HYBRID_DLIST_FOREACH_SAFE3(elem, self, __HYBRID_Q_KEY, key)
#define __HYBRID_DLIST_FOREACH_SAFE_4(elem, self, key, tvar)                                __HYBRID_DLIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define __HYBRID_DLIST_FOREACH_SAFE_P_3(elem, self, getpath)                                __HYBRID_DLIST_FOREACH_SAFE3(elem, self, __HYBRID_Q_PTH, getpath)
#define __HYBRID_DLIST_FOREACH_SAFE_P_4(elem, self, getpath, tvar)                          __HYBRID_DLIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define __HYBRID_DLIST_INSERT_TAIL_3(self, elem, key)                                       __HYBRID_DLIST_INSERT_TAIL(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_DLIST_INSERT_TAIL_4(self, elem, type, key)                                 __HYBRID_DLIST_INSERT_TAIL(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_DLIST_INSERT_TAIL_P_3(self, elem, getpath)                                 __HYBRID_DLIST_INSERT_TAIL(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_DLIST_INSERT_TAIL_P_4(self, elem, T, getpath)                              __HYBRID_DLIST_INSERT_TAIL(self, elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_DLIST_INSERT_TAIL_R_4(self, lo_elem, hi_elem, key)                         __HYBRID_DLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __typeof__(*(lo_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_DLIST_INSERT_TAIL_R_5(self, lo_elem, hi_elem, type, key)                   __HYBRID_DLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define __HYBRID_DLIST_INSERT_TAIL_R_P_4(self, lo_elem, hi_elem, getpath)                   __HYBRID_DLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __typeof__(*(lo_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_DLIST_INSERT_TAIL_R_P_5(self, lo_elem, hi_elem, T, getpath)                __HYBRID_DLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_DLIST_REMOVEALL_5(self, out_pelem, key, condition, on_match)               __HYBRID_DLIST_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_DLIST_REMOVEALL_6(self, out_pelem, type, key, condition, on_match)         __HYBRID_DLIST_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define __HYBRID_DLIST_REMOVEALL_P_5(self, out_pelem, getpath, condition, on_match)         __HYBRID_DLIST_REMOVEALL(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_DLIST_REMOVEALL_P_6(self, out_pelem, T, getpath, condition, on_match)      __HYBRID_DLIST_REMOVEALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define __HYBRID_DLIST_REMOVE_IF_4(self, out_pelem, key, condition)                         __HYBRID_DLIST_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition)
#define __HYBRID_DLIST_REMOVE_IF_5(self, out_pelem, type, key, condition)                   __HYBRID_DLIST_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define __HYBRID_DLIST_REMOVE_IF_P_4(self, out_pelem, getpath, condition)                   __HYBRID_DLIST_REMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_DLIST_REMOVE_IF_P_5(self, out_pelem, T, getpath, condition)                __HYBRID_DLIST_REMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define __HYBRID_DLIST_SWAP_2(dst, src)                                                     __HYBRID_DLIST_SWAP(dst, src, __typeof__(*(dst)->dlh_first))
#define __HYBRID_DLIST_SWAP_3(dst, src, type)                                               __HYBRID_DLIST_SWAP(dst, src, __HYBRID_Q_STRUCT type)
#define __HYBRID_DLIST_SWAP_P_2(dst, src)                                                   __HYBRID_DLIST_SWAP(dst, src, __typeof__(*(dst)->dlh_first))
#define __HYBRID_DLIST_SWAP_P_3(dst, src, T)                                                __HYBRID_DLIST_SWAP(dst, src, T)
#define __HYBRID_DLIST_TRYREMOVE_IF_5(self, out_pelem, key, condition, on_failure)          __HYBRID_DLIST_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_DLIST_TRYREMOVE_IF_6(self, out_pelem, type, key, condition, on_failure)    __HYBRID_DLIST_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define __HYBRID_DLIST_TRYREMOVE_IF_P_5(self, out_pelem, getpath, condition, on_failure)    __HYBRID_DLIST_TRYREMOVE_IF(self, out_pelem, __typeof__(**(out_pelem)), __HYBRID_Q_PTH, getpath, condition, on_failure)
#define __HYBRID_DLIST_TRYREMOVE_IF_P_6(self, out_pelem, T, getpath, condition, on_failure) __HYBRID_DLIST_TRYREMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#define DLIST_CONCAT(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_CONCAT_, (__VA_ARGS__))(__VA_ARGS__)              /* DLIST_CONCAT(dst, src, [type], key) */
#define DLIST_CONCAT_P(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_CONCAT_P_, (__VA_ARGS__))(__VA_ARGS__)            /* DLIST_CONCAT_P(dst, src, [type], getpath) */
#define DLIST_FOREACH_FROM_SAFE(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_FOREACH_FROM_SAFE_, (__VA_ARGS__))(__VA_ARGS__)   /* DLIST_FOREACH_FROM_SAFE(elem, self, key, [tvar]) */
#define DLIST_FOREACH_FROM_SAFE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_FOREACH_FROM_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__) /* DLIST_FOREACH_FROM_SAFE_P(elem, self, getpath, [tvar]) */
#define DLIST_FOREACH_SAFE(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_FOREACH_SAFE_, (__VA_ARGS__))(__VA_ARGS__)        /* DLIST_FOREACH_SAFE(elem, self, key, [tvar]) */
#define DLIST_FOREACH_SAFE_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_FOREACH_SAFE_P_, (__VA_ARGS__))(__VA_ARGS__)      /* DLIST_FOREACH_SAFE_P(elem, self, getpath, [tvar]) */
#define DLIST_INSERT_TAIL(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_INSERT_TAIL_, (__VA_ARGS__))(__VA_ARGS__)         /* DLIST_INSERT_TAIL(self, elem, [type], key) */
#define DLIST_INSERT_TAIL_P(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_INSERT_TAIL_P_, (__VA_ARGS__))(__VA_ARGS__)       /* DLIST_INSERT_TAIL_P(self, elem, [T], getpath) */
#define DLIST_INSERT_TAIL_R(...)       __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_INSERT_TAIL_R_, (__VA_ARGS__))(__VA_ARGS__)       /* DLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, [type], key) */
#define DLIST_INSERT_TAIL_R_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_INSERT_TAIL_R_P_, (__VA_ARGS__))(__VA_ARGS__)     /* DLIST_INSERT_TAIL_R_P(self, lo_elem, hi_elem, [T], getpath) */
#define DLIST_REMOVEALL(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)        /* DLIST_REMOVEALL(self, out_pelem, [type], key, condition, on_match) */
#define DLIST_REMOVEALL_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)      /* DLIST_REMOVEALL_P(self, out_pelem, [T], getpath, condition, on_match) */
#define DLIST_REMOVE_IF(...)           __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_REMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)           /* DLIST_REMOVE_IF(self, out_pelem, [type], key, condition) */
#define DLIST_REMOVE_IF_P(...)         __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_REMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)         /* DLIST_REMOVE_IF_P(self, out_pelem, [T], getpath, condition) */
#define DLIST_SWAP(...)                __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_SWAP_, (__VA_ARGS__))(__VA_ARGS__)                /* DLIST_SWAP(l1, l2, [type]) */
#define DLIST_SWAP_P(...)              __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_SWAP_P_, (__VA_ARGS__))(__VA_ARGS__)              /* DLIST_SWAP_P(l1, l2, [T]) */
#define DLIST_TRYREMOVE_IF(...)        __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_TRYREMOVE_IF_, (__VA_ARGS__))(__VA_ARGS__)        /* DLIST_TRYREMOVE_IF(self, out_pelem, [type], key, condition, on_failure) */
#define DLIST_TRYREMOVE_IF_P(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_DLIST_TRYREMOVE_IF_P_, (__VA_ARGS__))(__VA_ARGS__)      /* DLIST_TRYREMOVE_IF_P(self, out_pelem, [T], getpath, condition, on_failure) */
#else /* __HYBRID_PP_VA_OVERLOAD && __COMPILER_HAVE_TYPEOF */
#define DLIST_CONCAT(dst, src, type, key)                                        __HYBRID_DLIST_CONCAT(dst, src, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define DLIST_CONCAT_P(dst, src, T, getpath)                                     __HYBRID_DLIST_CONCAT(dst, src, T, __HYBRID_Q_PTH, getpath)
#define DLIST_FOREACH_FROM_SAFE(elem, self, key, tvar)                           __HYBRID_DLIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define DLIST_FOREACH_FROM_SAFE_P(elem, self, getpath, tvar)                     __HYBRID_DLIST_FOREACH_FROM_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define DLIST_FOREACH_SAFE(elem, self, key, tvar)                                __HYBRID_DLIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_KEY, key, tvar)
#define DLIST_FOREACH_SAFE_P(elem, self, getpath, tvar)                          __HYBRID_DLIST_FOREACH_SAFE4(elem, self, __HYBRID_Q_PTH, getpath, tvar)
#define DLIST_INSERT_TAIL(self, elem, type, key)                                 __HYBRID_DLIST_INSERT_TAIL(self, elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define DLIST_INSERT_TAIL_P(self, elem, T, getpath)                              __HYBRID_DLIST_INSERT_TAIL(self, elem, T, __HYBRID_Q_PTH, getpath)
#define DLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, type, key)                   __HYBRID_DLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key)
#define DLIST_INSERT_TAIL_R_P(self, lo_elem, hi_elem, T, getpath)                __HYBRID_DLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, T, __HYBRID_Q_PTH, getpath)
#define DLIST_REMOVEALL(self, out_pelem, type, key, condition, on_match)         __HYBRID_DLIST_REMOVEALL(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_match)
#define DLIST_REMOVEALL_P(self, out_pelem, T, getpath, condition, on_match)      __HYBRID_DLIST_REMOVEALL(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_match)
#define DLIST_REMOVE_IF(self, out_pelem, type, key, condition)                   __HYBRID_DLIST_REMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition)
#define DLIST_REMOVE_IF_P(self, out_pelem, T, getpath, condition)                __HYBRID_DLIST_REMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition)
#define DLIST_SWAP(dst, src, type)                                               __HYBRID_DLIST_SWAP(dst, src, __HYBRID_Q_STRUCT type)
#define DLIST_SWAP_P(dst, src, T)                                                __HYBRID_DLIST_SWAP(dst, src, T)
#define DLIST_TRYREMOVE_IF(self, out_pelem, type, key, condition, on_failure)    __HYBRID_DLIST_TRYREMOVE_IF(self, out_pelem, __HYBRID_Q_STRUCT type, __HYBRID_Q_KEY, key, condition, on_failure)
#define DLIST_TRYREMOVE_IF_P(self, out_pelem, T, getpath, condition, on_failure) __HYBRID_DLIST_TRYREMOVE_IF(self, out_pelem, T, __HYBRID_Q_PTH, getpath, condition, on_failure)
#endif /* !__HYBRID_PP_VA_OVERLOAD || !__COMPILER_HAVE_TYPEOF */

#define __HYBRID_DLIST_CONCAT(dst, src, T, X, _)                                                    \
	/* Sorry, this one must be a statement */                                                       \
	do {                                                                                            \
		if ((src)->dlh_first != __NULLPTR) {                                                        \
			if ((dst)->dlh_first == __NULLPTR) {                                                    \
				(dst)->dlh_first = (src)->dlh_first;                                                \
			} else {                                                                                \
				T *__hdlc_dst_last = (dst)->dlh_first;                                              \
				while (X(_, __hdlc_dst_last).dle_next)                                              \
					__hdlc_dst_last = X(_, __hdlc_dst_last).dle_next;                               \
				X(_, X(_, __hdlc_dst_last).dle_next = (src)->dlh_first).dle_prev = __hdlc_dst_last; \
			}                                                                                       \
			(src)->dlh_first = __NULLPTR;                                                           \
		}                                                                                           \
	}	__WHILE0
#define __HYBRID_DLIST_SWAP(dst, src, T)      \
	/* Sorry, this one must be a statement */ \
	do {                                      \
		T *__hdls_tmp    = (dst)->dlh_first;  \
		(dst)->dlh_first = (src)->dlh_first;  \
		(src)->dlh_first = __hdls_tmp;        \
	}	__WHILE0
#define __HYBRID_DLIST_INSERT_AFTER(predecessor, elem, X, _) \
	__HYBRID_DLIST_INSERT_AFTER_R(predecessor, elem, elem, X, _)
#define __HYBRID_DLIST_INSERT_AFTER_R(predecessor, lo_elem, hi_elem, X, _)    \
	(void)((X(_, hi_elem).dle_next = X(_, predecessor).dle_next) != __NULLPTR \
	       ? (void)(X(_, X(_, hi_elem).dle_next).dle_prev = (hi_elem))        \
	       : (void)0,                                                         \
	       X(_, X(_, predecessor).dle_next = (lo_elem)).dle_prev = (predecessor))
#define __HYBRID_DLIST_INSERT_BEFORE(self, successor, elem, X, _) \
	__HYBRID_DLIST_INSERT_BEFORE_R(self, successor, elem, elem, X, _)
#define __HYBRID_DLIST_INSERT_BEFORE_R(self, successor, lo_elem, hi_elem, X, _) \
	(void)((X(_, lo_elem).dle_prev = X(_, successor).dle_prev) != __NULLPTR,    \
	       ? (void)(X(_, X(_, lo_elem).dle_prev).dle_next = (lo_elem))          \
	       : (void)((self)->dlh_first = (lo_elem)),                             \
	       X(_, X(_, hi_elem).dle_next = (successor)).dle_prev = (hi_elem))
#define __HYBRID_DLIST_INSERT_HEAD(self, elem, X, _) \
	__HYBRID_DLIST_INSERT_HEAD_R(self, elem, elem, X, _)
#define __HYBRID_DLIST_INSERT_HEAD_R(self, lo_elem, hi_elem, X, _)     \
	(void)((X(_, hi_elem).dle_next = (self)->dlh_first) != __NULLPTR   \
	       ? (void)(X(_, X(_, hi_elem).dle_next).dle_prev = (hi_elem)) \
	       : (void)0,                                                  \
	       X(_, (self)->dlh_first = X(_, lo_elem)).dle_prev = __NULLPTR)
#define __HYBRID_DLIST_INSERT_TAIL(self, elem, T, X, _) \
	__HYBRID_DLIST_INSERT_TAIL_R(self, elem, elem, T, X, _)
#define __HYBRID_DLIST_INSERT_TAIL_R(self, lo_elem, hi_elem, T, X, _) \
	/* Sorry, this one must be a statement */                         \
	do {                                                              \
		T *__hdlitr_prev;                                             \
		X(_, hi_elem).dle_next = __NULLPTR;                           \
		if ((__hdlitr_prev = (self)->dlh_first) == __NULLPTR) {       \
			X(_, lo_elem).dle_prev = __NULLPTR;                       \
			(self)->dlh_first      = (lo_elem);                       \
		} else {                                                      \
			while (X(_, __hdlitr_prev).dle_next != __NULLPTR)         \
				__hdlitr_prev = X(_, __hdlitr_prev).dle_next;         \
			X(_, __hdlitr_prev).dle_next  = (lo_elem);                \
			X(_, lo_elem).dle_prev = __hdlitr_prev;                   \
		}                                                             \
	}	__WHILE0
#define __HYBRID_DLIST_REMOVE_IF(self, out_pelem, T, X, _, condition) \
	/* Sorry, this one must be a statement */                         \
	do {                                                              \
		*(out_pelem) = (self)->dlh_first;                             \
		for (;;) {                                                    \
			if (condition) {                                          \
				__HYBRID_DLIST_REMOVE(self, *(out_pelem), X, _);      \
				break;                                                \
			}                                                         \
			*(out_pelem) = X(_, *(out_pelem)).dle_next;               \
		}                                                             \
	}	__WHILE0
#define __HYBRID_DLIST_TRYREMOVE_IF(self, out_pelem, T, X, _, condition, on_failure) \
	/* Sorry, this one must be a statement */                                        \
	do {                                                                             \
		*(out_pelem) = (self)->dlh_first;                                            \
		for (;;) {                                                                   \
			if (*(out_pelem) == __NULLPTR) {                                         \
				on_failure;                                                          \
				break;                                                               \
			}                                                                        \
			if (condition) {                                                         \
				__HYBRID_DLIST_REMOVE(self, *(out_pelem), X, _);                     \
				break;                                                               \
			}                                                                        \
			*(out_pelem) = X(_, *(out_pelem)).dle_next;                              \
		}                                                                            \
	}	__WHILE0
#define __HYBRID_DLIST_REMOVEALL(self, out_pelem, T, X, _, condition, on_match) \
	/* Sorry, this one must be a statement */                                   \
	do {                                                                        \
		*(out_pelem) = (self)->dlh_first;                                       \
		for (;;) {                                                              \
			if (*(out_pelem) == __NULLPTR)                                      \
				break;                                                          \
			if (condition) {                                                    \
				T *__next = X(_, *(out_pelem)).dle_next;                        \
				__HYBRID_DLIST_REMOVE(self, *(out_pelem), X, _);                \
				on_match;                                                       \
				*(out_pelem) = __next;                                          \
			} else {                                                            \
				*(out_pelem) = X(_, *(out_pelem)).dle_next;                     \
			}                                                                   \
		}                                                                       \
	}	__WHILE0
#define __HYBRID_DLIST_REMOVE_AFTER(elem, X, _)                              \
	(__HYBRID_Q_BADPTR(X(_, X(_, elem).dle_next).dle_prev),                  \
	 (X(_, elem).dle_next = X(_, X(_, elem).dle_next).dle_next) != __NULLPTR \
	 ? (void)(X(_, X(_, elem).dle_next).dle_prev = (elem))                   \
	 : (void)0)
#define __HYBRID_DLIST_REMOVE_HEAD(self, X, _)                           \
	(__HYBRID_Q_BADPTR(X(_, (self)->dlh_first).dle_prev),                \
	 ((self)->dlh_first = X(_, (self)->dlh_first).dle_next) != __NULLPTR \
	 ? (void)(X(_, (self)->dlh_first).dle_prev = __NULLPTR)              \
	 : (void)0)
#define __HYBRID_DLIST_REMOVE(self, elem, X, _) \
	__HYBRID_DLIST_REMOVE_R(self, elem, elem, X, _)
#define __HYBRID_DLIST_REMOVE_R(self, lo_elem, hi_elem, X, _)                       \
	(void)(X(_, hi_elem).dle_next != __NULLPTR                                      \
	       ? (void)(X(_, X(_, hi_elem).dle_next).dle_prev = X(_, lo_elem).dle_prev) \
	       : (void)0,                                                               \
	       X(_, lo_elem).dle_prev != __NULLPTR                                      \
	       ? (void)(X(_, X(_, lo_elem).dle_prev).dle_next = X(_, hi_elem).dle_next) \
	       : (void)((self)->dlh_first = X(_, hi_elem).dle_next),                    \
	       __HYBRID_Q_BADPTR(X(_, lo_elem).dle_prev),                               \
	       __HYBRID_Q_BADPTR(X(_, hi_elem).dle_next))
#define __HYBRID_DLIST_REPLACE(self, old_elem, new_elem, X, _) \
	__HYBRID_DLIST_REPLACE_R(self, old_elem, old_elem, new_elem, new_elem, X, _)
#define __HYBRID_DLIST_REPLACE_R(self, old_lo_elem, old_hi_elem, new_lo_elem, new_hi_elem, X, _) \
	(void)((X(_, new_hi_elem).dle_next = X(_, old_hi_elem).dle_next) != __NULLPTR                \
	       ? (void)(X(_, X(_, old_hi_elem).dle_next).dle_prev = (new_hi_elem))                   \
	       : (void)0,                                                                            \
	       (X(_, new_lo_elem).dle_prev = X(_, old_lo_elem).dle_prev) != __NULLPTR                \
	       ? (void)(X(_, X(_, old_lo_elem).dle_prev).dle_next = (new_lo_elem))                   \
	       : (void)((self)->dlh_first = (new_lo_elem)),                                          \
	       __HYBRID_Q_BADPTR(X(_, old_lo_elem).dle_prev),                                        \
	       __HYBRID_Q_BADPTR(X(_, old_hi_elem).dle_next))
#define __HYBRID_DLIST_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->dlh_first; (elem); (elem) = X(_, elem).dle_next)
#define __HYBRID_DLIST_FOREACH_FROM(elem, self, X, _) \
	for ((elem) ? (void)0 : (void)((elem) = (self)->dlh_first); (elem); (elem) = X(_, elem).dle_next)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_DLIST_FOREACH_SAFE3(elem, self, X, _)          \
	if (((elem) = (self)->dlh_first, 0))                        \
		;                                                       \
	else                                                        \
		for (__typeof__(elem) __hdlfs_tvar;                     \
		     (elem) && (__hdlfs_tvar = X(_, elem).dle_next, 1); \
		     (elem) = __hdlfs_tvar)
#define __HYBRID_DLIST_FOREACH_FROM_SAFE3(elem, self, X, _)         \
	if (((elem) ? (void)0 : (void)((elem) = (self)->dlh_first), 0)) \
		;                                                           \
	else                                                            \
		for (__typeof__(elem) __hdlfs_tvar;                         \
		     (elem) && (__hdlfs_tvar = X(_, elem).dle_next, 1);     \
		     (elem) = __hdlfs_tvar)
#endif /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define __HYBRID_DLIST_FOREACH_SAFE4(elem, self, X, _, tvar) \
	for ((elem) = (head)->dlh_first;                         \
	     (elem) && ((tvar) = X(_, elem).dle_next, 1);        \
	     (elem) = (tvar))
#define __HYBRID_DLIST_FOREACH_FROM_SAFE4(elem, self, X, _, tvar) \
	for ((elem) ? (void)0 : (void)((elem) = (head)->dlh_first);   \
	     (elem) && ((tvar) = X(_, elem).dle_next, 1);             \
	     (elem) = (tvar))
#endif /* !__HYBRID_LIST_RESTRICT_API */








/************************************************************************/
/* DEPRECATED API (or what remains there-of; to be removed eventually)  */
/************************************************************************/
#ifndef __HYBRID_LIST_WITHOUT_DEPRECATED
/* LLIST */
#define LLIST_INSERT(l, elem, key)                           \
	(void)(((elem)->key.le_next = (l)) != __NULLPTR          \
	       ? (void)((l)->key.le_prev = &(elem)->key.le_next) \
	       : (void)0,                                        \
	       *((elem)->key.le_prev = &(l)) = (elem))
#define LLIST_INSERT_AFTER(predecessor, elem, key)                                                   \
	(void)(((elem)->key.le_next = *((elem)->key.le_prev = &(predecessor)->key.le_next)) != __NULLPTR \
	       ? (void)((elem)->key.le_next->key.le_prev = &(elem)->key.le_next)                         \
	       : (void)0,                                                                                \
	       (predecessor)->key.le_next = (elem))
#define LLIST_REMOVE(elem, key)                                       \
	((*(elem)->key.le_prev = (elem)->key.le_next) != __NULLPTR        \
	 ? (void)((elem)->key.le_next->key.le_prev = (elem)->key.le_prev) \
	 : (void)0)
#endif /* !__HYBRID_LIST_WITHOUT_DEPRECATED */

#endif /* __CC__ */

/* TODO: KOS-specific extension macros */
//TODO:*_REMOVE_TAIL() ?


/* TODO: Missing macros from OpenBSD: */
//TODO:#define XSIMPLEQ_HEAD(name, type)
//TODO:#define XSIMPLEQ_ENTRY(type)
//TODO:#define XSIMPLEQ_XOR(self, ptr)
//TODO:#define XSIMPLEQ_FIRST(self)
//TODO:#define XSIMPLEQ_END(self)
//TODO:#define XSIMPLEQ_EMPTY(self)
//TODO:#define XSIMPLEQ_NEXT(self, elem, key)
//TODO:#define XSIMPLEQ_FOREACH(elem, self, key)
//TODO:#define XSIMPLEQ_FOREACH_SAFE(elem, self, key, tvar)
//TODO:#define XSIMPLEQ_INIT(self)
//TODO:#define XSIMPLEQ_INSERT_HEAD(self, elem, key)
//TODO:#define XSIMPLEQ_INSERT_TAIL(self, elem, key)
//TODO:#define XSIMPLEQ_INSERT_AFTER(self, predecessor, elem, key)
//TODO:#define XSIMPLEQ_REMOVE_HEAD(self, key)
//TODO:#define XSIMPLEQ_REMOVE_AFTER(self, elem, key)


#endif /* !__GUARD_HYBRID_SEQUENCE_LIST_H */
