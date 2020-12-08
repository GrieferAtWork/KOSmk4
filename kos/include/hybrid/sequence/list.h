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
#ifdef __CC__
#ifndef __HYBRID_LIST_RESTRICT_API
#include "../pp/__va_nargs.h"
#endif /* !__HYBRID_LIST_RESTRICT_API */

/*
 * General purpose macros to defining various types of intrusive linked lists.
 *
 *  +----------- LIST_*:    Single-head, doubly-linked list (via element self-pointers)
 *  | +--------- SLIST_*:   Single-head, singly-linked list
 *  | | +------- STAILQ_*:  Double-head, singly-linked tail queue. (same as "Simple queue" (SIMPLEQ_*))
 *  | | | +----- TAILQ_*:   Double-head, doubly-linked tail queue.
 *  | | | | +--- CIRCLEQ_*: Circular queue
 *  | | | | | +- RINGQ_*:   Ring queue (KOS extension)
 *  | | | | | |
 * [===========]
 * [1 1 2 2 2  ]   Pointers per *_HEAD
 * [2 1 1 2 2 2]   Pointers per *_ENTRY
 * [===========]
 * [1 1 1 1 1  ]   *_HEAD_INITIALIZER(self)
 * [1 1 1 1 1  ]   *_INIT(self)
 * [          1]   *_INIT(elem, key)
 * [    1      ]   *_CONCAT(dst, src)
 * [      1    ]   *_CONCAT(dst, src, key)
 * [1 1 1 1 1  ]   *_EMPTY(self)
 * [1 1 1 1 1  ]   *_FIRST(self)
 * [      1 1  ]   *_LAST(self)
 * [1 1 1 1 1  ]   *_NEXT(elem, key)
 * [      1    ]   *_PREV(elem, headname, key)
 * [        1  ]   *_PREV(elem, key)
 * [1          ]   *_XPREV(elem, type, key)                        (Return predecessor (undef if no pred exists))
 * [        1 1]   *_LOOP_NEXT(elem, key)                          (or *_NEXT(elem, key) for RINGQ)
 * [        1 1]   *_LOOP_PREV(elem, key)                          (or *_PREV(elem, key) for RINGQ)
 * [1 1 1     1]   *_INSERT_AFTER(predecessor, elem, key)
 * [      1 1  ]   *_INSERT_AFTER(self, predecessor, elem, key)
 * [1     1   1]   *_INSERT_BEFORE(successor, elem, key)
 * [        1  ]   *_INSERT_BEFORE(self, successor, elem, key)
 * [1 1 1 1 1  ]   *_INSERT[_HEAD](self, elem, key)
 * [    1 1 1  ]   *_INSERT_TAIL(self, elem, key)
 * [N          ]   *_INSERT_TAIL(self, elem, type, key)
 * [  1 1      ]   *_REMOVE_HEAD(elem, key)
 * [1         1]   *_REMOVE(elem, key)
 * [  N N 1 1  ]   *_REMOVE(self, elem, type, key)
 * [  N N      ]   *_TRYREMOVE(self, elem, type, key, on_failure)
 * [  N N      ]   *_CONTAINS(self, elem, type, key, on_success)
 * [1         1]   *_REPLACE(old_elem, new_elem, key)
 * [  N N 1 1  ]   *_REPLACE(self, old_elem, new_elem, type, key)
 * [  N N      ]   *_TRYREPLACE(self, old_elem, new_elem, type, key, on_failure)
 * [N N N N N  ]   *_FOREACH(elem, self, key)
 * [        N  ]   *_FOREACH_REVERSE(elem, self, key)
 * [      N    ]   *_FOREACH_REVERSE(elem, self, headname, key)
 * \-----------/
 *    Runtime
 *   (in O(x))
 */


#define __HYBRID_Q_KEY(key, item)     (item)->key
#define __HYBRID_Q_PTH(getpath, item) getpath(item)
#undef __HYBRID_Q_BADPTR
#ifdef NDEBUG
#define __HYBRID_Q_BADPTR(field) (void)0
#else /* NDEBUG */
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
#endif /* !NDEBUG */





/************************************************************************/
/* LIST: Single-head, doubly-linked list (via element self-pointers)    */
/************************************************************************/
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef LIST_HEAD
#undef LIST_ENTRY
#define LIST_HEAD(name, T)                  \
	struct name {                           \
		T *lh_first; /* [0..1] List head */ \
	}
#define LIST_ENTRY(T)                                           \
	struct {                                                    \
		T *le_next, /* [0..1] Next item */                      \
		**le_prev;  /* [1..1][?..1] This item's self-pointer */ \
	}
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define LIST_HEAD(name, type)                         \
	struct name {                                     \
		struct type *lh_first; /* [0..1] List head */ \
	}
#define LIST_ENTRY(type)                                                  \
	struct {                                                              \
		struct type *le_next, /* [0..1] Next item */                      \
		**le_prev;            /* [1..1][?..1] This item's self-pointer */ \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#define LIST_HEAD_INITIALIZER(self) \
	{ __NULLPTR }
#define LIST_INIT(self)                           (void)((self)->lh_first = __NULLPTR)
#define LIST_EMPTY(self)                          ((self)->lh_first == __NULLPTR)
#define LIST_FIRST(self)                          (self)->lh_first
#define LIST_INSERT_AFTER(predecessor, elem, key) __HYBRID_LIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_KEY, key)
#define LIST_INSERT_BEFORE(successor, elem, key)  __HYBRID_LIST_INSERT_BEFORE(successor, elem, __HYBRID_Q_KEY, key)
#define LIST_INSERT_HEAD(self, elem, key)         __HYBRID_LIST_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define LIST_REMOVE(elem, key)                    __HYBRID_LIST_REMOVE(elem, __HYBRID_Q_KEY, key)
#define LIST_FOREACH(elem, self, key)             __HYBRID_LIST_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define LIST_NEXT(elem, key)                      __HYBRID_LIST_NEXT(elem, __HYBRID_Q_KEY, key)
#ifndef __HYBRID_LIST_RESTRICT_API
#define LIST_HEAD_P(T)                      \
	struct {                                \
		T *lh_first; /* [0..1] List head */ \
	}
#define LIST_ENTRY_P(T)                                   \
	struct {                                              \
		T *le_next, /* [0..1] Next item */                \
		**le_prev;  /* [1..1] This item's self-pointer */ \
	}
#define LIST_ENTRY_INITIALIZER \
	{ __NULLPTR, __NULLPTR }
#define LIST_INSERT_AFTER_P(predecessor, elem, getpath) __HYBRID_LIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_PTH, getpath)
#define LIST_INSERT_BEFORE_P(successor, elem, getpath)  __HYBRID_LIST_INSERT_BEFORE(successor, elem, __HYBRID_Q_PTH, getpath)
#define LIST_INSERT_HEAD_P(self, elem, getpath)         __HYBRID_LIST_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_LIST_XPREV_2(elem, key)                      __HYBRID_LIST_XPREV3(elem, __typeof__(*(elem)), key)
#define __HYBRID_LIST_XPREV_P_2(elem, key)                    __HYBRID_LIST_XPREV4(elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_INSERT_TAIL_3(self, elem, key)          __HYBRID_LIST_INSERT_TAIL(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_INSERT_TAIL_P_3(self, elem, getpath)    __HYBRID_LIST_INSERT_TAIL(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_INSERT_TAIL_P_4(self, elem, T, getpath) __HYBRID_LIST_INSERT_TAIL(self, elem, T, __HYBRID_Q_PTH, getpath)
#ifdef __cplusplus
#define __HYBRID_LIST_XPREV_3(elem, T, key)             __HYBRID_LIST_XPREV3(elem, T, key)
#define __HYBRID_LIST_XPREV_P_3(elem, T, getpath)       __HYBRID_LIST_XPREV4(elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_INSERT_TAIL_4(self, elem, T, key) __HYBRID_LIST_INSERT_TAIL(self, elem, T, __HYBRID_Q_KEY, key)
#else /* __cplusplus */
#define __HYBRID_LIST_XPREV_3(elem, type, key)             __HYBRID_LIST_XPREV(elem, struct type, __HYBRID_Q_KEY, key)
#define __HYBRID_LIST_XPREV_P_3(elem, type, getpath)       __HYBRID_LIST_XPREV4(elem, struct type, __HYBRID_Q_PTH, getpath)
#define __HYBRID_LIST_INSERT_TAIL_4(self, elem, type, key) __HYBRID_LIST_INSERT_TAIL(self, elem, struct type, __HYBRID_Q_KEY, key)
#endif /* !__cplusplus */
/* clang-format off */
/* LIST_INSERT_TAIL(self, elem, key)
 * LIST_INSERT_TAIL(self, elem, type, key) */
#define LIST_INSERT_TAIL(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_INSERT_TAIL_, (__VA_ARGS__))(__VA_ARGS__)
/* LIST_INSERT_TAIL_P(self, elem, getpath)
 * LIST_INSERT_TAIL_P(self, elem, type, getpath) */
#define LIST_INSERT_TAIL_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_INSERT_TAIL_P_, (__VA_ARGS__))(__VA_ARGS__)
/* LIST_XPREV(elem, key)
 * LIST_XPREV(elem, type, key) */
#define LIST_XPREV(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_XPREV_, (__VA_ARGS__))(__VA_ARGS__)
/* LIST_XPREV_P(elem, getpath)
 * LIST_XPREV_P(elem, type, getpath) */
#define LIST_XPREV_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_LIST_XPREV_P_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#ifdef __cplusplus
#define LIST_INSERT_TAIL(self, elem, T, key) __HYBRID_SLIST_REMOVE(self, elem, T, __HYBRID_Q_KEY, key)
#else /* __cplusplus */
#define LIST_INSERT_TAIL(self, elem, type, key) __HYBRID_SLIST_REMOVE(self, elem, struct type, __HYBRID_Q_KEY, key)
#endif /* !__cplusplus */
#define LIST_INSERT_TAIL_P(self, elem, T, getpath) __HYBRID_SLIST_REMOVE(self, elem, T, __HYBRID_Q_KEY, getpath)
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#define LIST_REPLACE(old_elem, new_elem, key)       __HYBRID_LIST_REPLACE(old_elem, new_elem, __HYBRID_Q_KEY, key)
#define LIST_REPLACE_P(old_elem, new_elem, getpath) __HYBRID_LIST_REPLACE(old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define LIST_REMOVE_P(elem, getpath)                __HYBRID_LIST_REMOVE(elem, __HYBRID_Q_PTH, getpath)
#define LIST_FOREACH_P(elem, self, getpath)         __HYBRID_LIST_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define LIST_NEXT_P(elem, getpath)                  __HYBRID_LIST_NEXT(elem, __HYBRID_Q_PTH, getpath)
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_LIST_XPREV3(elem, T, key)  __COMPILER_CONTAINER_OF((elem)->key.le_prev, T, key.le_next)
#define __HYBRID_LIST_XPREV4(elem, T, X, _) ((T *)((__SIZE_TYPE__)(ptr) - (__SIZE_TYPE__)(&X(_, (T *)0).le_next)))
#define __HYBRID_LIST_INSERT_AFTER(predecessor, elem, X, _)                                       \
	(void)((X(_, elem).le_next = *(X(_, elem).le_prev = &X(_, predecessor).le_next)) != __NULLPTR \
	       ? (void)(X(_, X(_, elem).le_next).le_prev = &X(_, elem).le_next)                       \
	       : (void)0,                                                                             \
	       X(_, predecessor).le_next = (elem))
#define __HYBRID_LIST_INSERT_BEFORE(successor, elem, X, _)            \
	(void)(*(X(_, elem).le_prev = X(_, successor).le_prev)  = (elem), \
	       *(X(_, successor).le_prev = &X(_, elem).le_next) = (successor))
#define __HYBRID_LIST_INSERT_HEAD(self, elem, X, _)                       \
	(void)((X(_, elem).le_next = (self)->lh_first) != __NULLPTR           \
	       ? (void)(X(_, (self)->lh_first).le_prev = &X(_, elem).le_next) \
	       : (void)0,                                                     \
	       *(X(_, elem).le_prev = &(self)->lh_first) = (elem))
#define __HYBRID_LIST_REMOVE(elem, X, _)                             \
	((*X(_, elem).le_prev = X(_, elem).le_next) != __NULLPTR         \
	 ? (void)(X(_, X(_, elem).le_next).le_prev = X(_, elem).le_prev) \
	 : (void)0,                                                      \
	 __HYBRID_Q_BADPTR(X(_, elem).le_next),                          \
	 __HYBRID_Q_BADPTR(X(_, elem).le_prev))
#define __HYBRID_LIST_REPLACE(old_elem, new_elem, X, _)                       \
	(*(X(_, new_elem).le_prev = X(_, old_elem).le_prev) = (new_elem),         \
	 (X(_, new_elem).le_next = X(_, old_elem).le_next) != __NULLPTR           \
	 ? (void)(X(_, X(_, new_elem).le_next).le_prev = &X(_, new_elem).le_next) \
	 : (void)0,                                                               \
	 __HYBRID_Q_BADPTR(X(_, old_elem).le_prev),                               \
	 __HYBRID_Q_BADPTR(X(_, old_elem).le_next))
#define __HYBRID_LIST_INSERT_TAIL(self, elem, T, X, _) \
	/* Sorry, this one must be state statement */      \
	do {                                               \
		T **__piter = &(self)->lh_first;               \
		while (*__piter != __NULLPTR)                  \
			__piter = &X(_, *__piter).le_next;         \
		*(X(_, elem).le_prev = __piter) = (elem);      \
		X(_, elem).le_next              = __NULLPTR;   \
	}                                                  \
	__WHILE0
#define __HYBRID_LIST_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->lh_first; (elem); (elem) = X(_, elem).le_next)
#define __HYBRID_LIST_EMPTY(self)      ((self)->lh_first == __NULLPTR)
#define __HYBRID_LIST_FIRST(self)      ((self)->lh_first)
#define __HYBRID_LIST_NEXT(elem, X, _) (X(_, elem).le_next)





/************************************************************************/
/* SLIST: Single-head, singly-linked list                               */
/************************************************************************/
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef SLIST_HEAD
#ifdef __cplusplus
#define __HYBRID_SLIST_HEAD_1(T)             \
	struct {                                 \
		T *slh_first; /* [0..1] List head */ \
	}
#define __HYBRID_SLIST_HEAD_2(name, T)       \
	struct name {                            \
		T *slh_first; /* [0..1] List head */ \
	}
#else /* __cplusplus */
#define __HYBRID_SLIST_HEAD_1(type)                    \
	struct {                                           \
		struct type *slh_first; /* [0..1] List head */ \
	}
#define __HYBRID_SLIStype_HEAD_2(name, type)           \
	struct name {                                      \
		struct type *slh_first; /* [0..1] List head */ \
	}
#endif /* !__cplusplus */
/* clang-format off */
#define SLIST_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_HEAD_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#elif !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef SLIST_HEAD
#define SLIST_HEAD(name, T)                  \
	struct name {                            \
		T *slh_first; /* [0..1] List head */ \
	}
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define SLIST_HEAD(name, type)                         \
	struct name {                                      \
		struct type *slh_first; /* [0..1] List head */ \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef SLIST_ENTRY
#define SLIST_ENTRY(T)                      \
	struct {                                \
		T *sle_next; /* [0..1] Next-link */ \
	}
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define SLIST_ENTRY(type)                             \
	struct {                                          \
		struct type *sle_next; /* [0..1] Next-link */ \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#define SLIST_HEAD_INITIALIZER(self) \
	{ __NULLPTR }
#define SLIST_INIT(self) \
	(void)((self)->slh_first = __NULLPTR)
#define SLIST_EMPTY(self)                          ((self)->slh_first == __NULLPTR)
#define SLIST_FIRST(self)                          ((self)->slh_first)
#define SLIST_INSERT_AFTER(predecessor, elem, key) __HYBRID_SLIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_KEY, key)
#define SLIST_INSERT(l, elem, key)             __HYBRID_SLIST_INSERT(l, elem, __HYBRID_Q_KEY, key)
#define SLIST_REMOVE_HEAD(self, key)               __HYBRID_SLIST_REMOVE_HEAD(self, __HYBRID_Q_KEY, key)
#define SLIST_FOREACH(elem, self, key)             __HYBRID_SLIST_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define SLIST_NEXT(elem, key)                      __HYBRID_SLIST_NEXT(elem, __HYBRID_Q_KEY, key)
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef SLIST_REMOVE
#define __HYBRID_SLIST_REMOVE_3(self, elem, key) __HYBRID_SLIST_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#ifdef __cplusplus
#define __HYBRID_SLIST_REMOVE_4(self, elem, T, key) __HYBRID_SLIST_REMOVE(self, elem, T, __HYBRID_Q_KEY, key)
#else /* __cplusplus */
#define __HYBRID_SLIST_REMOVE_4(self, elem, type, key) __HYBRID_SLIST_REMOVE(self, elem, struct type, __HYBRID_Q_KEY, key)
#endif /* !__cplusplus */
/* clang-format off */
/* SLIST_REMOVE(self, elem, key)
 * SLIST_REMOVE(self, elem, type, key) */
#define SLIST_REMOVE(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REMOVE_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#elif !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef SLIST_REMOVE
#define SLIST_REMOVE(self, elem, T, key) __HYBRID_SLIST_REMOVE(self, elem, T, __HYBRID_Q_KEY, key)
#else /* ... */
#define SLIST_REMOVE(self, elem, type, key) __HYBRID_SLIST_REMOVE(self, elem, struct type, __HYBRID_Q_KEY, key)
#endif /* !... */
#ifndef __HYBRID_LIST_RESTRICT_API
#define SLIST_HEAD_P(T)                      \
	struct {                                 \
		T *slh_first; /* [0..1] List head */ \
	}
#define SLIST_ENTRY_P(T)                    \
	struct {                                \
		T *sle_next; /* [0..1] Next-link */ \
	}
#define SLIST_ENTRY_INITIALIZER \
	{ __NULLPTR }
#define SLIST_INSERT_AFTER_P(predecessor, elem, getpath) __HYBRID_SLIST_INSERT_AFTER(predecessor, elem, __HYBRID_Q_PTH, getpath)
#define SLIST_INSERT_P(l, elem, getpath)                 __HYBRID_SLIST_INSERT(l, elem, __HYBRID_Q_PTH, getpath)
#define SLIST_REMOVE_HEAD_P(self, getpath)               __HYBRID_SLIST_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_SLIST_REMOVE_P_3(self, elem, getpath)                                  __HYBRID_SLIST_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_REMOVE_P_4(self, elem, T, getpath)                               __HYBRID_SLIST_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_REPLACE_4(self, old_elem, new_elem, key)                         __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_REPLACE_P_4(self, old_elem, new_elem, getpath)                   __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_REPLACE_P_5(self, old_elem, new_elem, T, getpath)                __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SLIST_TRYREMOVE_4(self, elem, key, on_failure)                         __HYBRID_SLIST_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_TRYREMOVE_P_4(self, elem, getpath, on_failure)                   __HYBRID_SLIST_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SLIST_TRYREMOVE_P_5(self, elem, T, getpath, on_failure)                __HYBRID_SLIST_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SLIST_CONTAINS_4(self, elem, key, on_success)                          __HYBRID_SLIST_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SLIST_CONTAINS_P_4(self, elem, getpath, on_success)                    __HYBRID_SLIST_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_SLIST_CONTAINS_P_5(self, elem, T, getpath, on_success)                 __HYBRID_SLIST_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_SLIST_TRYREPLACE_5(self, old_elem, new_elem, key, on_failure)          __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_P_5(self, old_elem, new_elem, getpath, on_failure)    __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SLIST_TRYREPLACE_P_6(self, old_elem, new_elem, T, getpath, on_failure) __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#ifdef __cplusplus
#define __HYBRID_SLIST_REPLACE_5(self, old_elem, new_elem, T, key)                __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_TRYREMOVE_5(self, elem, T, key, on_failure)                __HYBRID_SLIST_TRYREMOVE(self, elem, T, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_CONTAINS_5(self, elem, T, key, on_success)                 __HYBRID_SLIST_CONTAINS(self, elem, T, __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SLIST_TRYREPLACE_6(self, old_elem, new_elem, T, key, on_failure) __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key, on_failure)
#else /* __cplusplus */
#define __HYBRID_SLIST_REPLACE_5(self, old_elem, new_elem, type, key)                __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key)
#define __HYBRID_SLIST_TRYREMOVE_5(self, elem, type, key, on_failure)                __HYBRID_SLIST_TRYREMOVE(self, elem, struct type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SLIST_CONTAINS_5(self, elem, type, key, on_success)                 __HYBRID_SLIST_CONTAINS(self, elem, struct type, __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SLIST_TRYREPLACE_6(self, old_elem, new_elem, type, key, on_failure) __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key, on_failure)
#endif /* !__cplusplus */
/* clang-format off */
/* SLIST_REMOVE_P(self, elem, getpath)
 * SLIST_REMOVE_P(self, elem, type, getpath) */
#define SLIST_REMOVE_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* SLIST_REPLACE_P(self, old_elem, new_elem, key)
 * SLIST_REPLACE_P(self, old_elem, new_elem, type, key) */
#define SLIST_REPLACE(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REPLACE_, (__VA_ARGS__))(__VA_ARGS__)
/* SLIST_REPLACE_P(self, old_elem, new_elem, getpath)
 * SLIST_REPLACE_P(self, old_elem, new_elem, type, getpath) */
#define SLIST_REPLACE_P(...)    __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_REPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* SLIST_TRYREMOVE(self, elem, key, on_failure)
 * SLIST_TRYREMOVE(self, elem, type, key, on_failure) */
#define SLIST_TRYREMOVE(...)    __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREMOVE_, (__VA_ARGS__))(__VA_ARGS__)
/* SLIST_TRYREMOVE_P(self, elem, getpath, on_failure)
 * SLIST_TRYREMOVE_P(self, elem, type, getpath, on_failure) */
#define SLIST_TRYREMOVE_P(...)  __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* SLIST_CONTAINS(self, elem, key, on_success)
 * SLIST_CONTAINS(self, elem, type, key, on_success) */
#define SLIST_CONTAINS(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_CONTAINS_, (__VA_ARGS__))(__VA_ARGS__)
/* SLIST_CONTAINS_P(self, elem, getpath, on_success)
 * SLIST_CONTAINS_P(self, elem, type, getpath, on_success) */
#define SLIST_CONTAINS_P(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_CONTAINS_P_, (__VA_ARGS__))(__VA_ARGS__)
/* SLIST_TRYREPLACE(self, old_elem, new_elem, key, on_success)
 * SLIST_TRYREPLACE(self, old_elem, new_elem, type, key, on_success) */
#define SLIST_TRYREPLACE(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREPLACE_, (__VA_ARGS__))(__VA_ARGS__)
/* SLIST_TRYREPLACE_P(self, old_elem, new_elem, getpath, on_success)
 * SLIST_TRYREPLACE_P(self, old_elem, new_elem, type, getpath, on_success) */
#define SLIST_TRYREPLACE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SLIST_TRYREPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define SLIST_REMOVE_P(self, elem, T, getpath)                               __HYBRID_SLIST_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define SLIST_REPLACE_P(self, old_elem, new_elem, T, getpath)                __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define SLIST_TRYREMOVE_P(self, elem, T, getpath, on_failure)                __HYBRID_SLIST_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SLIST_CONTAINS_P(self, elem, T, getpath, on_success)                 __HYBRID_SLIST_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define SLIST_TRYREPLACE_P(self, old_elem, new_elem, T, getpath, on_failure) __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#ifdef __cplusplus
#define SLIST_REPLACE(self, old_elem, new_elem, T, key)                __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key)
#define SLIST_TRYREMOVE(self, elem, T, key, on_failure)                __HYBRID_SLIST_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SLIST_CONTAINS(self, elem, T, key, on_success)                 __HYBRID_SLIST_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define SLIST_TRYREPLACE(self, old_elem, new_elem, T, key, on_failure) __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key, on_failure)
#else /* __cplusplus */
#define SLIST_REPLACE(self, old_elem, new_elem, type, key)                __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key)
#define SLIST_TRYREMOVE(self, elem, type, key, on_failure)                __HYBRID_SLIST_TRYREMOVE(self, elem, struct type, __HYBRID_Q_PTH, getpath, on_failure)
#define SLIST_CONTAINS(self, elem, type, key, on_success)                 __HYBRID_SLIST_CONTAINS(self, elem, struct type, __HYBRID_Q_PTH, getpath, on_success)
#define SLIST_TRYREPLACE(self, old_elem, new_elem, type, key, on_failure) __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key, on_failure)
#endif /* !__cplusplus */
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#define SLIST_FOREACH_P(elem, self, getpath) __HYBRID_SLIST_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define SLIST_NEXT_P(elem, getpath)          __HYBRID_SLIST_NEXT(elem, __HYBRID_Q_PTH, getpath)
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_SLIST_INSERT_AFTER(predecessor, elem, X, _)        \
	(void)(X(_, elem).sle_next        = X(_, predecessor).sle_next, \
	       X(_, predecessor).sle_next = (elem))
#define __HYBRID_SLIST_INSERT(l, elem, X, _)     \
	(void)(X(_, elem).sle_next = (l)->slh_first, \
	       (l)->slh_first      = (elem))
#define __HYBRID_SLIST_REMOVE_HEAD(self, X, _) \
	(void)((self)->slh_first = X(_, (self)->slh_first).sle_next)
#define __HYBRID_SLIST_REMOVE(self, elem, T, X, _) \
	/* Sorry, this one must be state statement */  \
	do {                                           \
		T **__piter = &(self)->slh_first;          \
		while (*__piter != (elem))                 \
			__piter = &X(_, *__piter).sle_next;    \
		*__piter = X(_, elem).sle_next;            \
		__HYBRID_Q_BADPTR(X(_, elem).sle_next);    \
	}                                              \
	__WHILE0
#define __HYBRID_SLIST_REPLACE(self, old_elem, new_elem, T, X, _) \
	/* Sorry, this one must be state statement */                 \
	do {                                                          \
		T **__piter = &(self)->slh_first;                         \
		while (*__piter != (old_elem))                            \
			__piter = &X(_, *__piter).sle_next;                   \
		X(_, new_elem).sle_next = X(_, old_elem).sle_next;        \
		*__piter                = (new_elem);                     \
		__HYBRID_Q_BADPTR(X(_, old_elem).sle_next);               \
	}                                                             \
	__WHILE0
#define __HYBRID_SLIST_TRYREMOVE(self, elem, T, X, _, on_failure) \
	/* Sorry, this one must be state statement */                 \
	do {                                                          \
		T **__piter = &(self)->slh_first;                         \
		while (*__piter != __NULLPTR && *__piter != (elem))       \
			__piter = &X(_, *__piter).sle_next;                   \
		if (*__piter != __NULLPTR) {                              \
			*__piter = X(_, elem).sle_next;                       \
			__HYBRID_Q_BADPTR(X(_, elem).sle_next);               \
		} else {                                                  \
			on_failure;                                           \
		}                                                         \
	}                                                             \
	__WHILE0
#define __HYBRID_SLIST_CONTAINS(self, elem, T, X, _, on_success) \
	/* Sorry, this one must be state statement */                \
	do {                                                         \
		T *__iter = (self)->slh_first;                           \
		while (__iter != __NULLPTR) {                            \
			if (__iter == (elem)) {                              \
				on_success;                                      \
				break;                                           \
			}                                                    \
			__iter = X(_, __iter).sle_next;                      \
		}                                                        \
	}                                                            \
	__WHILE0
#define __HYBRID_SLIST_TRYREPLACE(self, old_elem, new_elem, T, X, _, on_failure) \
	/* Sorry, this one must be state statement */                                \
	do {                                                                         \
		T **__piter = &(self)->slh_first;                                        \
		while (*__piter != __NULLPTR && *__piter != (old_elem))                  \
			__piter = &X(_, *__piter).sle_next;                                  \
		if (*__piter != __NULLPTR) {                                             \
			X(_, new_elem).sle_next = X(_, old_elem).sle_next;                   \
			*__piter                = (new_elem);                                \
			__HYBRID_Q_BADPTR(X(_, old_elem).sle_next);                          \
		} else {                                                                 \
			on_failure;                                                          \
		}                                                                        \
	}                                                                            \
	__WHILE0
#define __HYBRID_SLIST_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->slh_first;             \
	     (elem);                                 \
	     (elem) = X(_, elem).sle_next)
#define __HYBRID_SLIST_NEXT(elem, X, _) X(_, elem).sle_next





/************************************************************************/
/* Double-head, singly-linked Tail queue.                               */
/************************************************************************/
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef STAILQ_HEAD
#ifdef __cplusplus
#define __HYBRID_STAILQ_HEAD_1(T)                                          \
	struct {                                                               \
		T *stqh_first, /* [0..1] List head */                              \
		**stqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_STAILQ_HEAD_2(name, T)                                    \
	struct name {                                                          \
		T *stqh_first, /* [0..1] List head */                              \
		**stqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#else /* __cplusplus */
#define __HYBRID_STAILQ_HEAD_1(type)                                                 \
	struct {                                                                         \
		struct type *stqh_first, /* [0..1] List head */                              \
		**stqh_last;             /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_STAILQ_HEAD_2(name, type)                                           \
	struct name {                                                                    \
		struct type *stqh_first, /* [0..1] List head */                              \
		**stqh_last;             /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#endif /* !__cplusplus */
/* clang-format off */
#define STAILQ_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_HEAD_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#elif !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#define STAILQ_HEAD(name, T)                                               \
	struct name {                                                          \
		T *stqh_first, /* [0..1] List head */                              \
		**stqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#else /* ... */
#define STAILQ_HEAD(name, type)                                                      \
	struct name {                                                                    \
		struct type *stqh_first, /* [0..1] List head */                              \
		**stqh_last;             /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#endif /* !__HYBRID_LIST_RESTRICT_API */

#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef STAILQ_ENTRY
#define STAILQ_ENTRY(T)                         \
	struct {                                    \
		T *stqe_next; /* [0..1] Next element */ \
	}
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define STAILQ_ENTRY(type)                                \
	struct {                                              \
		struct type *stqe_next; /* [0..1] Next element */ \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */

#define STAILQ_HEAD_INITIALIZER(self) \
	{ __NULLPTR, &(self).stqh_first }
#define STAILQ_INIT(self) \
	(void)(*((self)->stqh_last = &(self)->stqh_first) = __NULLPTR)
#define STAILQ_CONCAT(dst, src)                      \
	((src)->stqh_first != __NULLPTR                  \
	 ? (void)(*(dst)->stqh_last = (src)->stqh_first, \
	          (dst)->stqh_last  = (src)->stqh_last,  \
	          STAILQ_INIT(src))                      \
	 : (void)0)
#define STAILQ_EMPTY(self)                                ((self)->stqh_first == __NULLPTR)
#define STAILQ_FIRST(self)                                ((self)->stqh_first)
#define STAILQ_INSERT_HEAD(self, elem, key)               __HYBRID_STAILQ_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define STAILQ_INSERT_TAIL(self, elem, key)               __HYBRID_STAILQ_INSERT_TAIL(self, elem, __HYBRID_Q_KEY, key)
#define STAILQ_INSERT_AFTER(self, predecessor, elem, key) __HYBRID_STAILQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_KEY, key)
#define STAILQ_REMOVE_HEAD(self, key)                     __HYBRID_STAILQ_REMOVE_HEAD(self, __HYBRID_Q_KEY, key)
#define STAILQ_FOREACH(elem, self, key)                   __HYBRID_STAILQ_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define STAILQ_NEXT(elem, key)                            __HYBRID_STAILQ_NEXT(elem, __HYBRID_Q_KEY, key)
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef STAILQ_REMOVE
#define __HYBRID_STAILQ_REMOVE_3(self, elem, key) __HYBRID_STAILQ_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#ifdef __cplusplus
#define __HYBRID_STAILQ_REMOVE_4(self, elem, T, key) __HYBRID_STAILQ_REMOVE(self, elem, T, __HYBRID_Q_KEY, key)
#else /* __cplusplus */
#define __HYBRID_STAILQ_REMOVE_4(self, elem, type, key) __HYBRID_STAILQ_REMOVE(self, elem, struct type, __HYBRID_Q_KEY, key)
#endif /* !__cplusplus */
/* clang-format off */
/* STAILQ_REMOVE(self, elem, key)
 * STAILQ_REMOVE(self, elem, type, key) */
#define STAILQ_REMOVE(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REMOVE_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#elif !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef STAILQ_REMOVE
#define STAILQ_REMOVE(self, elem, T, key) __HYBRID_STAILQ_REMOVE(self, elem, T, __HYBRID_Q_KEY, key)
#else /* ... */
#define STAILQ_REMOVE(self, elem, type, key) __HYBRID_STAILQ_REMOVE(self, elem, struct type, __HYBRID_Q_KEY, key)
#endif /* !... */
#ifndef __HYBRID_LIST_RESTRICT_API
#define STAILQ_HEAD_P(T)                                                   \
	struct {                                                               \
		T *stqh_first, /* [0..1] List head */                              \
		**stqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define STAILQ_ENTRY_P(T)                       \
	struct {                                    \
		T *stqe_next; /* [0..1] Next element */ \
	}
#define STAILQ_ENTRY_INITIALIZER \
	{ __NULLPTR }
#define STAILQ_INSERT_HEAD_P(self, elem, getpath)               __HYBRID_STAILQ_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_INSERT_TAIL_P(self, elem, getpath)               __HYBRID_STAILQ_INSERT_TAIL(self, elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_INSERT_AFTER_P(self, predecessor, elem, getpath) __HYBRID_STAILQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_PTH, getpath)
#define STAILQ_REMOVE_HEAD_P(self, getpath)                     __HYBRID_STAILQ_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_STAILQ_REMOVE_P_3(self, elem, getpath)                                  __HYBRID_STAILQ_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_REMOVE_P_4(self, elem, T, getpath)                               __HYBRID_STAILQ_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_REPLACE_4(self, old_elem, new_elem, key)                         __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_REPLACE_P_4(self, old_elem, new_elem, getpath)                   __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_REPLACE_P_5(self, old_elem, new_elem, T, getpath)                __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_STAILQ_TRYREMOVE_4(self, elem, key, on_failure)                         __HYBRID_STAILQ_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_TRYREMOVE_P_4(self, elem, getpath, on_failure)                   __HYBRID_STAILQ_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_STAILQ_TRYREMOVE_P_5(self, elem, T, getpath, on_failure)                __HYBRID_STAILQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_STAILQ_CONTAINS_4(self, elem, key, on_success)                          __HYBRID_STAILQ_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_STAILQ_CONTAINS_P_4(self, elem, getpath, on_success)                    __HYBRID_STAILQ_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_STAILQ_CONTAINS_P_5(self, elem, T, getpath, on_success)                 __HYBRID_STAILQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_STAILQ_TRYREPLACE_5(self, old_elem, new_elem, key, on_failure)          __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_P_5(self, old_elem, new_elem, getpath, on_failure)    __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_STAILQ_TRYREPLACE_P_6(self, old_elem, new_elem, T, getpath, on_failure) __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#ifdef __cplusplus
#define __HYBRID_STAILQ_REPLACE_5(self, old_elem, new_elem, T, key)                __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_TRYREMOVE_5(self, elem, T, key, on_failure)                __HYBRID_STAILQ_TRYREMOVE(self, elem, T, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_CONTAINS_5(self, elem, T, key, on_success)                 __HYBRID_STAILQ_CONTAINS(self, elem, T, __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_STAILQ_TRYREPLACE_6(self, old_elem, new_elem, T, key, on_failure) __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key, on_failure)
#else /* __cplusplus */
#define __HYBRID_STAILQ_REPLACE_5(self, old_elem, new_elem, type, key)                __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key)
#define __HYBRID_STAILQ_TRYREMOVE_5(self, elem, type, key, on_failure)                __HYBRID_STAILQ_TRYREMOVE(self, elem, struct type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_STAILQ_CONTAINS_5(self, elem, type, key, on_success)                 __HYBRID_STAILQ_CONTAINS(self, elem, struct type, __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_STAILQ_TRYREPLACE_6(self, old_elem, new_elem, type, key, on_failure) __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key, on_failure)
#endif /* !__cplusplus */
/* clang-format off */
/* STAILQ_REMOVE_P(self, elem, getpath)
 * STAILQ_REMOVE_P(self, elem, type, getpath) */
#define STAILQ_REMOVE_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* STAILQ_REPLACE_P(self, old_elem, new_elem, key)
 * STAILQ_REPLACE_P(self, old_elem, new_elem, type, key) */
#define STAILQ_REPLACE(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REPLACE_, (__VA_ARGS__))(__VA_ARGS__)
/* STAILQ_REPLACE_P(self, old_elem, new_elem, getpath)
 * STAILQ_REPLACE_P(self, old_elem, new_elem, type, getpath) */
#define STAILQ_REPLACE_P(...)    __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_REPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* STAILQ_TRYREMOVE(self, elem, key, on_failure)
 * STAILQ_TRYREMOVE(self, elem, type, key, on_failure) */
#define STAILQ_TRYREMOVE(...)    __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREMOVE_, (__VA_ARGS__))(__VA_ARGS__)
/* STAILQ_TRYREMOVE_P(self, elem, getpath, on_failure)
 * STAILQ_TRYREMOVE_P(self, elem, type, getpath, on_failure) */
#define STAILQ_TRYREMOVE_P(...)  __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* STAILQ_CONTAINS(self, elem, key, on_success)
 * STAILQ_CONTAINS(self, elem, type, key, on_success) */
#define STAILQ_CONTAINS(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_CONTAINS_, (__VA_ARGS__))(__VA_ARGS__)
/* STAILQ_CONTAINS_P(self, elem, getpath, on_success)
 * STAILQ_CONTAINS_P(self, elem, type, getpath, on_success) */
#define STAILQ_CONTAINS_P(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_CONTAINS_P_, (__VA_ARGS__))(__VA_ARGS__)
/* STAILQ_TRYREPLACE(self, old_elem, new_elem, key, on_success)
 * STAILQ_TRYREPLACE(self, old_elem, new_elem, type, key, on_success) */
#define STAILQ_TRYREPLACE(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREPLACE_, (__VA_ARGS__))(__VA_ARGS__)
/* STAILQ_TRYREPLACE_P(self, old_elem, new_elem, getpath, on_success)
 * STAILQ_TRYREPLACE_P(self, old_elem, new_elem, type, getpath, on_success) */
#define STAILQ_TRYREPLACE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_STAILQ_TRYREPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define STAILQ_REMOVE_P(self, elem, T, getpath)                               __HYBRID_STAILQ_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define STAILQ_REPLACE_P(self, old_elem, new_elem, T, getpath)                __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define STAILQ_TRYREMOVE_P(self, elem, T, getpath, on_failure)                __HYBRID_STAILQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define STAILQ_CONTAINS_P(self, elem, T, getpath, on_success)                 __HYBRID_STAILQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define STAILQ_TRYREPLACE_P(self, old_elem, new_elem, T, getpath, on_failure) __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#ifdef __cplusplus
#define STAILQ_REPLACE(self, old_elem, new_elem, T, key)                __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key)
#define STAILQ_TRYREMOVE(self, elem, T, key, on_failure)                __HYBRID_STAILQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define STAILQ_CONTAINS(self, elem, T, key, on_success)                 __HYBRID_STAILQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define STAILQ_TRYREPLACE(self, old_elem, new_elem, T, key, on_failure) __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key, on_failure)
#else /* __cplusplus */
#define STAILQ_REPLACE(self, old_elem, new_elem, type, key)                __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key)
#define STAILQ_TRYREMOVE(self, elem, type, key, on_failure)                __HYBRID_STAILQ_TRYREMOVE(self, elem, struct type, __HYBRID_Q_PTH, getpath, on_failure)
#define STAILQ_CONTAINS(self, elem, type, key, on_success)                 __HYBRID_STAILQ_CONTAINS(self, elem, struct type, __HYBRID_Q_PTH, getpath, on_success)
#define STAILQ_TRYREPLACE(self, old_elem, new_elem, type, key, on_failure) __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key, on_failure)
#endif /* !__cplusplus */
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#define STAILQ_FOREACH_P(elem, self, getpath) __HYBRID_STAILQ_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define STAILQ_NEXT_P(elem, getpath)          __HYBRID_STAILQ_NEXT(elem, __HYBRID_Q_PTH, getpath)
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_STAILQ_INSERT_HEAD(self, elem, X, _)         \
	((X(_, elem).stqe_next = (self)->stqh_first) == __NULLPTR \
	 ? (void)((self)->stqh_last = &X(_, elem).stqe_next)      \
	 : (void)0,                                               \
	 (void)((self)->stqh_first = (elem)))
#define __HYBRID_STAILQ_INSERT_TAIL(self, elem, X, _)    \
	(void)(*(self)->stqh_last   = (elem),                \
	       (self)->stqh_last    = &X(_, elem).stqe_next, \
	       X(_, elem).stqe_next = __NULLPTR)
#define __HYBRID_STAILQ_INSERT_AFTER(self, predecessor, elem, X, _)    \
	((X(_, elem).stqe_next = X(_, predecessor).stqe_next) == __NULLPTR \
	 ? (void)((self)->stqh_last = &X(_, elem).stqe_next)               \
	 : (void)0,                                                        \
	 X(_, predecessor).stqe_next = (elem))
#define __HYBRID_STAILQ_REMOVE_HEAD(self, X, _)                             \
	(((self)->stqh_first = X(_, (self)->stqh_first).stqe_next) == __NULLPTR \
	 ? (void)((self)->stqh_last = &(self)->stqh_first)                      \
	 : (void)0)
#define __HYBRID_STAILQ_REMOVE(self, elem, T, X, _)         \
	/* Sorry, this one must be state statement */           \
	do {                                                    \
		T **__piter = &(self)->stqh_first;                  \
		while (*__piter != (elem))                          \
			__piter = &X(_, *__piter).stqe_next;            \
		if ((*__piter = X(_, elem).stqe_next) == __NULLPTR) \
			(self)->stqh_last = __piter;                    \
		__HYBRID_Q_BADPTR(X(_, elem).stqe_next);            \
	}                                                       \
	__WHILE0
#define __HYBRID_STAILQ_REPLACE(self, old_elem, new_elem, T, X, _) \
	/* Sorry, this one must be state statement */                  \
	do {                                                           \
		T **__piter = &(self)->stqh_first;                         \
		while (*__piter != (old_elem))                             \
			__piter = &X(_, *__piter).stqe_next;                   \
		X(_, new_elem).stqe_next = *__piter;                       \
		*__piter                 = (new_elem);                     \
		__HYBRID_Q_BADPTR(X(_, old_elem).stqe_next);               \
	}                                                              \
	__WHILE0
#define __HYBRID_STAILQ_TRYREMOVE(self, elem, T, X, _, on_failure) \
	/* Sorry, this one must be state statement */                  \
	do {                                                           \
		T **__piter = &(self)->stqh_first;                         \
		while (*__piter != __NULLPTR && *__piter != (elem))        \
			__piter = &X(_, *__piter).stqe_next;                   \
		if (*__piter != __NULLPTR) {                               \
			if ((*__piter = X(_, elem).stqe_next) == __NULLPTR)    \
				(self)->stqh_last = __piter;                       \
			__HYBRID_Q_BADPTR(X(_, elem).stqe_next);               \
		} else {                                                   \
			on_failure;                                            \
		}                                                          \
	}                                                              \
	__WHILE0
#define __HYBRID_STAILQ_CONTAINS(self, elem, T, X, _, on_success) \
	/* Sorry, this one must be state statement */                 \
	do {                                                          \
		T *__iter = (self)->stqh_first;                           \
		while (__iter != __NULLPTR) {                             \
			if (__iter == (elem)) {                               \
				on_success;                                       \
				break;                                            \
			}                                                     \
			__iter = X(_, __iter).stqe_next;                      \
		}                                                         \
	}                                                             \
	__WHILE0
#define __HYBRID_STAILQ_TRYREPLACE(self, old_elem, new_elem, T, X, _, on_failure) \
	/* Sorry, this one must be state statement */                                 \
	do {                                                                          \
		T **__piter = &(self)->stqh_first;                                        \
		while (*__piter != __NULLPTR && *__piter != (old_elem))                   \
			__piter = &X(_, *__piter).stqe_next;                                  \
		if (*__piter != __NULLPTR) {                                              \
			X(_, new_elem).stqe_next = *__piter;                                  \
			*__piter                 = (new_elem);                                \
			__HYBRID_Q_BADPTR(X(_, old_elem).stqe_next);                          \
		} else {                                                                  \
			on_failure;                                                           \
		}                                                                         \
	}                                                                             \
	__WHILE0
#define __HYBRID_STAILQ_FOREACH(elem, self, X, _) \
	for ((elem) = ((self)->stqh_first);           \
	     (elem);                                  \
	     (elem) = (X(_, elem).stqe_next))
#define __HYBRID_STAILQ_NEXT(elem, X, _) (X(_, elem).stqe_next)





/************************************************************************/
/* Simple queue. (Alias for `Double-head, singly-linked Tail queue', with different field names) */
/************************************************************************/
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef SIMPLEQ_HEAD
#ifdef __cplusplus
#define __HYBRID_SIMPLEQ_HEAD_1(T)                                        \
	struct {                                                              \
		T *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_SIMPLEQ_HEAD_2(name, T)                                  \
	struct name {                                                         \
		T *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#else /* __cplusplus */
#define __HYBRID_SIMPLEQ_HEAD_1(type)                                               \
	struct {                                                                        \
		struct type *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;             /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define __HYBRID_SIMPLEQ_HEAD_2(name, type)                                         \
	struct name {                                                                   \
		struct type *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;             /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#endif /* !__cplusplus */
/* clang-format off */
#define SIMPLEQ_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_HEAD_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#elif !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef SIMPLEQ_HEAD
#define SIMPLEQ_HEAD(name, T)                                             \
	struct name {                                                         \
		T *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define SIMPLEQ_HEAD(name, type)                                                    \
	struct name {                                                                   \
		struct type *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;             /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef SIMPLEQ_ENTRY
#define SIMPLEQ_ENTRY(T)                       \
	struct {                                   \
		T *sqe_next; /* [0..1] Next element */ \
	}
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define SIMPLEQ_ENTRY(type)                              \
	struct {                                             \
		struct type *sqe_next; /* [0..1] Next element */ \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#define SIMPLEQ_HEAD_INITIALIZER(self) \
	{ __NULLPTR, &(self).sqh_first }
#define SIMPLEQ_INIT(self) \
	(void)(*((self)->sqh_last = &(self)->sqh_first) = __NULLPTR)
#define SIMPLEQ_EMPTY(self)                                ((self)->sqh_first == __NULLPTR)
#define SIMPLEQ_FIRST(self)                                ((self)->sqh_first)
#define SIMPLEQ_INSERT_HEAD(self, elem, key)               __HYBRID_SIMPLEQ_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_INSERT_TAIL(self, elem, key)               __HYBRID_SIMPLEQ_INSERT_TAIL(self, elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_INSERT_AFTER(self, predecessor, elem, key) __HYBRID_SIMPLEQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_KEY, key)
#define SIMPLEQ_REMOVE_HEAD(self, key)                     __HYBRID_SIMPLEQ_REMOVE_HEAD(self, __HYBRID_Q_KEY, key)
#define SIMPLEQ_FOREACH(elem, self, key)                   __HYBRID_SIMPLEQ_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define SIMPLEQ_NEXT(elem, key)                            __HYBRID_SIMPLEQ_NEXT(elem, __HYBRID_Q_KEY, key)
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef SIMPLEQ_REMOVE
#define __HYBRID_SIMPLEQ_REMOVE_3(self, elem, key) __HYBRID_SIMPLEQ_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key)
#ifdef __cplusplus
#define __HYBRID_SIMPLEQ_REMOVE_4(self, elem, T, key) __HYBRID_SIMPLEQ_REMOVE(self, elem, T, __HYBRID_Q_KEY, key)
#else /* __cplusplus */
#define __HYBRID_SIMPLEQ_REMOVE_4(self, elem, type, key) __HYBRID_SIMPLEQ_REMOVE(self, elem, struct type, __HYBRID_Q_KEY, key)
#endif /* !__cplusplus */
/* clang-format off */
/* SIMPLEQ_REMOVE(self, elem, key)
 * SIMPLEQ_REMOVE(self, elem, type, key) */
#define SIMPLEQ_REMOVE(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REMOVE_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#elif !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef SIMPLEQ_REMOVE
#define SIMPLEQ_REMOVE(self, elem, T, key) __HYBRID_SIMPLEQ_REMOVE(self, elem, T, __HYBRID_Q_KEY, key)
#else /* ... */
#define SIMPLEQ_REMOVE(self, elem, type, key) __HYBRID_SIMPLEQ_REMOVE(self, elem, struct type, __HYBRID_Q_KEY, key)
#endif /* !... */
#ifndef __HYBRID_LIST_RESTRICT_API
#define SIMPLEQ_HEAD_P(T)                                                 \
	struct {                                                              \
		T *sqh_first, /* [0..1] Head element */                           \
		**sqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define SIMPLEQ_ENTRY_P(T)                     \
	struct {                                   \
		T *sqe_next; /* [0..1] Next element */ \
	}
#define SIMPLEQ_ENTRY_INITIALIZER \
	{ __NULLPTR }
#define SIMPLEQ_INSERT_HEAD_P(self, elem, getpath)               __HYBRID_SIMPLEQ_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_INSERT_TAIL_P(self, elem, getpath)               __HYBRID_SIMPLEQ_INSERT_TAIL(self, elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_INSERT_AFTER_P(self, predecessor, elem, getpath) __HYBRID_SIMPLEQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_REMOVE_HEAD_P(self, getpath)                     __HYBRID_SIMPLEQ_REMOVE_HEAD(self, __HYBRID_Q_PTH, getpath)
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_SIMPLEQ_REMOVE_P_3(self, elem, getpath)                                  __HYBRID_SIMPLEQ_REMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_REMOVE_P_4(self, elem, T, getpath)                               __HYBRID_SIMPLEQ_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_REPLACE_4(self, old_elem, new_elem, key)                         __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_REPLACE_P_4(self, old_elem, new_elem, getpath)                   __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_REPLACE_P_5(self, old_elem, new_elem, T, getpath)                __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define __HYBRID_SIMPLEQ_TRYREMOVE_4(self, elem, key, on_failure)                         __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_TRYREMOVE_P_4(self, elem, getpath, on_failure)                   __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SIMPLEQ_TRYREMOVE_P_5(self, elem, T, getpath, on_failure)                __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SIMPLEQ_CONTAINS_4(self, elem, key, on_success)                          __HYBRID_SIMPLEQ_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SIMPLEQ_CONTAINS_P_4(self, elem, getpath, on_success)                    __HYBRID_SIMPLEQ_CONTAINS(self, elem, __typeof__(*(elem)), __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_SIMPLEQ_CONTAINS_P_5(self, elem, T, getpath, on_success)                 __HYBRID_SIMPLEQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define __HYBRID_SIMPLEQ_TRYREPLACE_5(self, old_elem, new_elem, key, on_failure)          __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_P_5(self, old_elem, new_elem, getpath, on_failure)    __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, __typeof__(*(old_elem)), __HYBRID_Q_PTH, getpath, on_failure)
#define __HYBRID_SIMPLEQ_TRYREPLACE_P_6(self, old_elem, new_elem, T, getpath, on_failure) __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#ifdef __cplusplus
#define __HYBRID_SIMPLEQ_REPLACE_5(self, old_elem, new_elem, T, key)                __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_TRYREMOVE_5(self, elem, T, key, on_failure)                __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, T, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_CONTAINS_5(self, elem, T, key, on_success)                 __HYBRID_SIMPLEQ_CONTAINS(self, elem, T, __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SIMPLEQ_TRYREPLACE_6(self, old_elem, new_elem, T, key, on_failure) __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key, on_failure)
#else /* __cplusplus */
#define __HYBRID_SIMPLEQ_REPLACE_5(self, old_elem, new_elem, type, key)                __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key)
#define __HYBRID_SIMPLEQ_TRYREMOVE_5(self, elem, type, key, on_failure)                __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, struct type, __HYBRID_Q_KEY, key, on_failure)
#define __HYBRID_SIMPLEQ_CONTAINS_5(self, elem, type, key, on_success)                 __HYBRID_SIMPLEQ_CONTAINS(self, elem, struct type, __HYBRID_Q_KEY, key, on_success)
#define __HYBRID_SIMPLEQ_TRYREPLACE_6(self, old_elem, new_elem, type, key, on_failure) __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key, on_failure)
#endif /* !__cplusplus */
/* clang-format off */
/* SIMPLEQ_REMOVE_P(self, elem, getpath)
 * SIMPLEQ_REMOVE_P(self, elem, type, getpath) */
#define SIMPLEQ_REMOVE_P(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* SIMPLEQ_REPLACE_P(self, old_elem, new_elem, key)
 * SIMPLEQ_REPLACE_P(self, old_elem, new_elem, type, key) */
#define SIMPLEQ_REPLACE(...)      __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REPLACE_, (__VA_ARGS__))(__VA_ARGS__)
/* SIMPLEQ_REPLACE_P(self, old_elem, new_elem, getpath)
 * SIMPLEQ_REPLACE_P(self, old_elem, new_elem, type, getpath) */
#define SIMPLEQ_REPLACE_P(...)    __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_REPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* SIMPLEQ_TRYREMOVE(self, elem, key, on_failure)
 * SIMPLEQ_TRYREMOVE(self, elem, type, key, on_failure) */
#define SIMPLEQ_TRYREMOVE(...)    __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREMOVE_, (__VA_ARGS__))(__VA_ARGS__)
/* SIMPLEQ_TRYREMOVE_P(self, elem, getpath, on_failure)
 * SIMPLEQ_TRYREMOVE_P(self, elem, type, getpath, on_failure) */
#define SIMPLEQ_TRYREMOVE_P(...)  __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREMOVE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* SIMPLEQ_CONTAINS(self, elem, key, on_success)
 * SIMPLEQ_CONTAINS(self, elem, type, key, on_success) */
#define SIMPLEQ_CONTAINS(...)     __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_CONTAINS_, (__VA_ARGS__))(__VA_ARGS__)
/* SIMPLEQ_CONTAINS_P(self, elem, getpath, on_success)
 * SIMPLEQ_CONTAINS_P(self, elem, type, getpath, on_success) */
#define SIMPLEQ_CONTAINS_P(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_CONTAINS_P_, (__VA_ARGS__))(__VA_ARGS__)
/* SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, key, on_success)
 * SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, type, key, on_success) */
#define SIMPLEQ_TRYREPLACE(...)   __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREPLACE_, (__VA_ARGS__))(__VA_ARGS__)
/* SIMPLEQ_TRYREPLACE_P(self, old_elem, new_elem, getpath, on_success)
 * SIMPLEQ_TRYREPLACE_P(self, old_elem, new_elem, type, getpath, on_success) */
#define SIMPLEQ_TRYREPLACE_P(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_SIMPLEQ_TRYREPLACE_P_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#else /* __COMPILER_HAVE_TYPEOF && __HYBRID_PP_VA_OVERLOAD */
#define SIMPLEQ_REMOVE_P(self, elem, T, getpath)                               __HYBRID_SIMPLEQ_REMOVE(self, elem, T, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_REPLACE_P(self, old_elem, new_elem, T, getpath)                __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_TRYREMOVE_P(self, elem, T, getpath, on_failure)                __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SIMPLEQ_CONTAINS_P(self, elem, T, getpath, on_success)                 __HYBRID_SIMPLEQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define SIMPLEQ_TRYREPLACE_P(self, old_elem, new_elem, T, getpath, on_failure) __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#ifdef __cplusplus
#define SIMPLEQ_REPLACE(self, old_elem, new_elem, T, key)                __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key)
#define SIMPLEQ_TRYREMOVE(self, elem, T, key, on_failure)                __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, T, __HYBRID_Q_PTH, getpath, on_failure)
#define SIMPLEQ_CONTAINS(self, elem, T, key, on_success)                 __HYBRID_SIMPLEQ_CONTAINS(self, elem, T, __HYBRID_Q_PTH, getpath, on_success)
#define SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, T, key, on_failure) __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, T, __HYBRID_Q_KEY, key, on_failure)
#else /* __cplusplus */
#define SIMPLEQ_REPLACE(self, old_elem, new_elem, type, key)                __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key)
#define SIMPLEQ_TRYREMOVE(self, elem, type, key, on_failure)                __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, struct type, __HYBRID_Q_PTH, getpath, on_failure)
#define SIMPLEQ_CONTAINS(self, elem, type, key, on_success)                 __HYBRID_SIMPLEQ_CONTAINS(self, elem, struct type, __HYBRID_Q_PTH, getpath, on_success)
#define SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, type, key, on_failure) __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, struct type, __HYBRID_Q_KEY, key, on_failure)
#endif /* !__cplusplus */
#endif /* !__COMPILER_HAVE_TYPEOF || !__HYBRID_PP_VA_OVERLOAD */
#define SIMPLEQ_FOREACH_P(elem, self, getpath) __HYBRID_SIMPLEQ_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define SIMPLEQ_NEXT_P(elem, getpath)          __HYBRID_SIMPLEQ_NEXT(elem, __HYBRID_Q_PTH, getpath)
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_SIMPLEQ_INSERT_HEAD(self, elem, X, _)      \
	((X(_, elem).sqe_next = (self)->sqh_first) == __NULLPTR \
	 ? (void)((self)->sqh_last = &X(_, elem).sqe_next)      \
	 : (void)0,                                             \
	 (void)((self)->sqh_first = (elem)))
#define __HYBRID_SIMPLEQ_INSERT_TAIL(self, elem, X, _) \
	(void)(*(self)->sqh_last   = (elem),               \
	       (self)->sqh_last    = &X(_, elem).sqe_next, \
	       X(_, elem).sqe_next = __NULLPTR)
#define __HYBRID_SIMPLEQ_INSERT_AFTER(self, predecessor, elem, X, _) \
	((X(_, elem).sqe_next = X(_, predecessor).sqe_next) == __NULLPTR \
	 ? (void)((self)->sqh_last = &X(_, elem).sqe_next)               \
	 : (void)0,                                                      \
	 (void)(X(_, predecessor).sqe_next = (elem)))
#define __HYBRID_SIMPLEQ_REMOVE_HEAD(self, X, _)                         \
	(((self)->sqh_first = X(_, (self)->sqh_first).sqe_next) == __NULLPTR \
	 ? (void)((self)->sqh_last = &(self)->sqh_first)                     \
	 : (void)0)
#define __HYBRID_SIMPLEQ_REMOVE(self, elem, T, X, _)       \
	/* Sorry, this one must be state statement */          \
	do {                                                   \
		T **__piter = &(self)->sqh_first;                  \
		while (*__piter != (elem))                         \
			__piter = &X(_, *__piter).sqe_next;            \
		if ((*__piter = X(_, elem).sqe_next) == __NULLPTR) \
			(self)->sqh_last = __piter;                    \
		__HYBRID_Q_BADPTR(X(_, elem).sqe_next);            \
	}                                                      \
	__WHILE0
#define __HYBRID_SIMPLEQ_REPLACE(self, old_elem, new_elem, T, X, _) \
	/* Sorry, this one must be state statement */                   \
	do {                                                            \
		T **__piter = &(self)->sqh_first;                           \
		while (*__piter != (old_elem))                              \
			__piter = &X(_, *__piter).sqe_next;                     \
		X(_, new_elem).sqe_next = *__piter;                         \
		*__piter                = (new_elem);                       \
		__HYBRID_Q_BADPTR(X(_, old_elem).sqe_next);                 \
	}                                                               \
	__WHILE0
#define __HYBRID_SIMPLEQ_TRYREMOVE(self, elem, T, X, _, on_failure) \
	/* Sorry, this one must be state statement */                   \
	do {                                                            \
		T **__piter = &(self)->sqh_first;                           \
		while (*__piter != __NULLPTR && *__piter != (elem))         \
			__piter = &X(_, *__piter).sqe_next;                     \
		if (*__piter != __NULLPTR) {                                \
			if ((*__piter = X(_, elem).sqe_next) == __NULLPTR)      \
				(self)->sqh_last = __piter;                         \
			__HYBRID_Q_BADPTR(X(_, elem).sqe_next);                 \
		} else {                                                    \
			on_failure;                                             \
		}                                                           \
	}                                                               \
	__WHILE0
#define __HYBRID_SIMPLEQ_CONTAINS(self, elem, T, X, _, on_success) \
	/* Sorry, this one must be state statement */                  \
	do {                                                           \
		T *__iter = (self)->sqh_first;                             \
		while (__iter != __NULLPTR) {                              \
			if (__iter == (elem)) {                                \
				on_success;                                        \
				break;                                             \
			}                                                      \
			__iter = X(_, __iter).sqe_next;                        \
		}                                                          \
	}                                                              \
	__WHILE0
#define __HYBRID_SIMPLEQ_TRYREPLACE(self, old_elem, new_elem, T, X, _, on_failure) \
	/* Sorry, this one must be state statement */                                  \
	do {                                                                           \
		T **__piter = &(self)->sqh_first;                                          \
		while (*__piter != __NULLPTR && *__piter != (old_elem))                    \
			__piter = &X(_, *__piter).sqe_next;                                    \
		if (*__piter != __NULLPTR) {                                               \
			X(_, new_elem).sqe_next = *__piter;                                    \
			*__piter                = (new_elem);                                  \
			__HYBRID_Q_BADPTR(X(_, old_elem).sqe_next);                            \
		} else {                                                                   \
			on_failure;                                                            \
		}                                                                          \
	}                                                                              \
	__WHILE0
#define __HYBRID_SIMPLEQ_FOREACH(elem, self, X, _) \
	for ((elem) = ((self)->sqh_first);             \
	     (elem);                                   \
	     (elem) = (X(_, elem).sqe_next))
#define __HYBRID_SIMPLEQ_NEXT(elem, X, _) (X(_, elem).sqe_next)





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
#ifdef __cplusplus
#define __HYBRID_TAILQ_HEAD_1(T)       _TAILQ_HEAD(, T, )
#define __HYBRID_TAILQ_HEAD_2(name, T) _TAILQ_HEAD(name, T, )
#else /* __cplusplus */
#define __HYBRID_TAILQ_HEAD_1(type)       _TAILQ_HEAD(, struct type, )
#define __HYBRID_TAILQ_HEAD_2(name, type) _TAILQ_HEAD(name, struct type, )
#endif /* !__cplusplus */
/* clang-format off */
#define TAILQ_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_HEAD_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#elif !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef TAILQ_HEAD
#define TAILQ_HEAD(name, T) _TAILQ_HEAD(name, T, )
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define TAILQ_HEAD(name, type) _TAILQ_HEAD(name, struct type, )
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef TAILQ_ENTRY
#define TAILQ_ENTRY(T) _TAILQ_ENTRY(T, )
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define TAILQ_ENTRY(type) _TAILQ_ENTRY(struct type, )
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#define TAILQ_HEAD_INITIALIZER(self) \
	{ __NULLPTR, &(self).tqh_first }
#define TAILQ_INIT(self) \
	(void)(*((self)->tqh_last = &(self)->tqh_first) = __NULLPTR)
#define TAILQ_EMPTY(self) ((self)->tqh_first == __NULLPTR)
#define TAILQ_FIRST(self) ((self)->tqh_first)
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef TAILQ_LAST
#define __HYBRID_TAILQ_LAST_1(self) (*(((__typeof__(*(self)) *)((self)->tqh_last))->tqh_last))
#ifdef __cplusplus
#define __HYBRID_TAILQ_LAST_2(self, HEAD_T) (*(((HEAD_T *)((self)->tqh_last))->tqh_last))
#else /* __cplusplus */
#define __HYBRID_TAILQ_LAST_2(self, headname) (*(((struct headname *)((self)->tqh_last))->tqh_last))
#endif /* !__cplusplus */
/* clang-format off */
#define TAILQ_LAST(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_LAST_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#elif !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef TAILQ_LAST
#define TAILQ_LAST(self, HEAD_T) (*(((HEAD_T *)((self)->tqh_last))->tqh_last))
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define TAILQ_LAST(self, headname) (*(((struct headname *)((self)->tqh_last))->tqh_last))
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__COMPILER_HAVE_TYPEOF) && defined(__HYBRID_PP_VA_OVERLOAD)
#undef TAILQ_FOREACH_REVERSE
#undef TAILQ_PREV
#define __HYBRID_TAILQ_FOREACH_REVERSE_3(elem, self, key) __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, __typeof__(*(self)), __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_PREV_2(elem, key)                  __HYBRID_TAILQ_PREV(elem, __typeof__(*(self)), __HYBRID_Q_KEY, key)
#ifdef __cplusplus
#define __HYBRID_TAILQ_FOREACH_REVERSE_4(elem, self, HEAD_T, key) __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, HEAD_T, __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_PREV_3(elem, HEAD_T, key)                  __HYBRID_TAILQ_PREV(elem, HEAD_T, __HYBRID_Q_KEY, key)
#else /* __cplusplus */
#define __HYBRID_TAILQ_FOREACH_REVERSE_4(elem, self, headname, key) __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, struct headname, __HYBRID_Q_KEY, key)
#define __HYBRID_TAILQ_PREV_3(elem, headname, key)                  __HYBRID_TAILQ_PREV(elem, struct headname, __HYBRID_Q_KEY, key)
#endif /* !__cplusplus */
/* clang-format off */
#define TAILQ_FOREACH_REVERSE(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_FOREACH_REVERSE_, (__VA_ARGS__))(__VA_ARGS__)
#define TAILQ_PREV(...)            __HYBRID_PP_VA_OVERLOAD(__HYBRID_TAILQ_PREV_, (__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#elif !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef TAILQ_FOREACH_REVERSE
#undef TAILQ_PREV
#define TAILQ_FOREACH_REVERSE(elem, self, HEAD_T, key) __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, HEAD_T, __HYBRID_Q_KEY, key)
#define TAILQ_PREV(elem, HEAD_T, key)                  __HYBRID_TAILQ_PREV(elem, HEAD_T, __HYBRID_Q_KEY, key)
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define TAILQ_FOREACH_REVERSE(elem, self, headname, key) __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, struct headname, __HYBRID_Q_KEY, key)
#define TAILQ_PREV(elem, headname, key)                  __HYBRID_TAILQ_PREV(elem, struct headname, __HYBRID_Q_KEY, key)
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#define TAILQ_INSERT_HEAD(self, elem, key)               __HYBRID_TAILQ_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_TAIL(self, elem, key)               __HYBRID_TAILQ_INSERT_TAIL(self, elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_AFTER(self, predecessor, elem, key) __HYBRID_TAILQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_KEY, key)
#define TAILQ_INSERT_BEFORE(successor, elem, key)        __HYBRID_TAILQ_INSERT_BEFORE(successor, elem, __HYBRID_Q_KEY, key)
#define TAILQ_REMOVE(self, elem, key)                    __HYBRID_TAILQ_REMOVE(self, elem, __HYBRID_Q_KEY, key)
#define TAILQ_FOREACH(elem, self, key)                   __HYBRID_TAILQ_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define TAILQ_CONCAT(dst, src, key)                      __HYBRID_TAILQ_CONCAT(dst, src, __HYBRID_Q_KEY, key)
#define TAILQ_NEXT(elem, key)                            __HYBRID_TAILQ_NEXT(elem, __HYBRID_Q_KEY, key)
#ifndef __HYBRID_LIST_RESTRICT_API
#define _TAILQ_HEAD_P(T, qual)                                                 \
	struct {                                                                   \
		T qual *tqh_first, /* [0..1] Head element */                           \
		*qual *tqh_last;   /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define TAILQ_HEAD_P(T) _TAILQ_HEAD_P(T, )
#define _TAILQ_ENTRY_P(T, qual)                                        \
	struct {                                                           \
		T qual *tqe_next, /* [1..1] Next element */                    \
		*qual *tqe_prev;  /* [1..1][1..1] This item's self-pointer. */ \
	}
#define TAILQ_ENTRY_P(T) _TAILQ_ENTRY_P(T, )
#define TAILQ_ENTRY_INITIALIZER \
	{ __NULLPTR, __NULLPTR }
#define TAILQ_LAST_P(self, HEAD_T)                             (*(((HEAD_T *)((self)->tqh_last))->tqh_last))
#define TAILQ_INSERT_HEAD_P(self, elem, getpath)               __HYBRID_TAILQ_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_TAIL_P(self, elem, getpath)               __HYBRID_TAILQ_INSERT_TAIL(self, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_AFTER_P(self, predecessor, elem, getpath) __HYBRID_TAILQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_INSERT_BEFORE_P(successor, elem, getpath)        __HYBRID_TAILQ_INSERT_BEFORE(successor, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_REPLACE(self, old_elem, new_elem, key)           __HYBRID_TAILQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_KEY, key)
#define TAILQ_REPLACE_P(self, old_elem, new_elem, getpath)     __HYBRID_TAILQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_REMOVE_P(self, elem, getpath)                    __HYBRID_TAILQ_REMOVE(self, elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_FOREACH_P(elem, self, getpath)                   __HYBRID_TAILQ_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define TAILQ_FOREACH_REVERSE_P(elem, self, HEAD_T, getpath)   __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, HEAD_T, __HYBRID_Q_PTH, getpath)
#define TAILQ_CONCAT_P(dst, src, getpath)                      __HYBRID_TAILQ_CONCAT(dst, src, __HYBRID_Q_PTH, getpath)
#define TAILQ_NEXT_P(elem, getpath)                            __HYBRID_TAILQ_NEXT(elem, __HYBRID_Q_PTH, getpath)
#define TAILQ_PREV_P(elem, HEAD_T, getpath)                    __HYBRID_TAILQ_PREV(elem, HEAD_T, __HYBRID_Q_PTH, getpath)
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_TAILQ_INSERT_HEAD(self, elem, X, _)                         \
	(void)((X(_, elem).tqe_next = (self)->tqh_first) != __NULLPTR            \
	       ? (void)(X(_, (self)->tqh_first).tqe_prev = &X(_, elem).tqe_next) \
	       : (void)((self)->tqh_last = &X(_, elem).tqe_next),                \
	       X(_, (self)->tqh_first = (elem)).tqe_prev = &(self)->tqh_first)
#define __HYBRID_TAILQ_INSERT_TAIL(self, elem, X, _)            \
	(void)(*(X(_, elem).tqe_prev = (self)->tqh_last)  = (elem), \
	       *((self)->tqh_last = &X(_, elem).tqe_next) = __NULLPTR)
#define __HYBRID_TAILQ_INSERT_AFTER(self, predecessor, elem, X, _)       \
	((X(_, elem).tqe_next = X(_, predecessor).tqe_next) != __NULLPTR     \
	 ? (void)(X(_, X(_, elem).tqe_next).tqe_prev = &X(_, elem).tqe_next) \
	 : (void)((self)->tqh_last = &X(_, elem).tqe_next),                  \
	 (void)(*(X(_, elem).tqe_prev = &X(_, predecessor).tqe_next) = (elem)))
#define __HYBRID_TAILQ_INSERT_BEFORE(successor, elem, X, _)             \
	(void)(*(X(_, elem).tqe_prev = X(_, successor).tqe_prev)  = (elem), \
	       *(X(_, successor).tqe_prev = &X(_, elem).tqe_next) = (successor))
#define __HYBRID_TAILQ_REPLACE(self, old_elem, new_elem, X, _)          \
	((X(_, new_elem).tqe_next = X(_, old_elem).tqe_next) != __NULLPTR   \
	 ? (void)(X(_, X(_, old_elem).tqe_next).tqe_prev = (new_elem))      \
	 : (void)((self)->tqh_last = (new_elem)),                           \
	 *(X(_, new_elem).tqe_prev = X(_, old_elem).tqe_prev) = (new_elem), \
	 __HYBRID_Q_BADPTR(X(_, old_elem).tqe_next),                        \
	 __HYBRID_Q_BADPTR(X(_, old_elem).tqe_prev))
#define __HYBRID_TAILQ_REMOVE(self, elem, X, _)                         \
	(X(_, elem).tqe_next != __NULLPTR                                   \
	 ? (void)(X(_, X(_, elem).tqe_next).tqe_prev = X(_, elem).tqe_prev) \
	 : (void)((self)->tqh_last = X(_, elem).tqe_prev),                  \
	 *X(_, elem).tqe_prev = X(_, elem).tqe_next,                        \
	 __HYBRID_Q_BADPTR(X(_, elem).tqe_next),                            \
	 __HYBRID_Q_BADPTR(X(_, elem).tqe_prev))
#define __HYBRID_TAILQ_FOREACH(elem, self, X, _) \
	for ((elem) = ((self)->tqh_first);           \
	     (elem);                                 \
	     (elem) = (X(_, elem).tqe_next))
#define __HYBRID_TAILQ_FOREACH_REVERSE(elem, self, HEAD_T, X, _) \
	for ((elem) = (*(((HEAD_T *)((self)->tqh_last))->tqh_last)); \
	     (elem);                                                 \
	     (elem) = (*(((HEAD_T *)(X(_, elem).tqe_prev))->tqh_last)))
#define __HYBRID_TAILQ_CONCAT(dst, src, X, _)                                       \
	((src)->tqh_first != __NULLPTR                                                  \
	 ? (void)(X(_, *(dst)->tqh_last = (src)->tqh_first).tqe_prev = (dst)->tqh_last, \
	          (dst)->tqh_last                                    = (src)->tqh_last, \
	          TAILQ_INIT(src))                                                      \
	 : (void)0)
#define __HYBRID_TAILQ_NEXT(elem, X, _)         (X(_, elem).tqe_next)
#define __HYBRID_TAILQ_PREV(elem, HEAD_T, X, _) (*(((HEAD_T *)(X(_, elem).tqe_prev))->tqh_last))





/************************************************************************/
/* CIRCLEQ: Circular queue                                              */
/************************************************************************/
#ifdef __cplusplus
#ifndef __HYBRID_LIST_RESTRICT_API
#undef CIRCLEQ_HEAD
#ifdef __HYBRID_PP_VA_OVERLOAD
#define __HYBRID_CIRCLEQ_HEAD_1(T)                            \
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
#define __HYBRID_CIRCLEQ_HEAD_2(name, T)                      \
	struct name {                                             \
		union {                                               \
			void *__cqh_first_ptr; /* [1..1] First element */ \
			T *cqh_first;          /* [1..1] First element */ \
		};                                                    \
		union {                                               \
			void *__cqh_last_ptr; /* [1..1] Last element */   \
			T *cqh_last;          /* [1..1] Last element */   \
		};                                                    \
	}
/* clang-format off */
#define CIRCLEQ_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_HEAD_(__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#else /* __HYBRID_PP_VA_OVERLOAD */
#define CIRCLEQ_HEAD(name, T)                                 \
	struct name {                                             \
		union {                                               \
			void *__cqh_first_ptr; /* [1..1] First element */ \
			T *cqh_first;          /* [1..1] First element */ \
		};                                                    \
		union {                                               \
			void *__cqh_last_ptr; /* [1..1] Last element */   \
			T *cqh_last;          /* [1..1] Last element */   \
		};                                                    \
	}
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#else  /* !__HYBRID_LIST_RESTRICT_API */
#define CIRCLEQ_HEAD(name, type)                               \
	struct name {                                              \
		union {                                                \
			void *__cqh_first_ptr;  /* [1..1] First element */ \
			struct type *cqh_first; /* [1..1] First element */ \
		};                                                     \
		union {                                                \
			void *__cqh_last_ptr;  /* [1..1] Last element */   \
			struct type *cqh_last; /* [1..1] Last element */   \
		};                                                     \
	}
#endif /* __HYBRID_LIST_RESTRICT_API */
#define CIRCLEQ_HEAD_INITIALIZER(self) \
	{                                  \
		{                              \
			(void *)&(self)            \
		},                             \
		{                              \
			(void *)&(self)            \
		}                              \
	}
#else /* __cplusplus */
#undef CIRCLEQ_HEAD
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__HYBRID_PP_VA_OVERLOAD)
#define __HYBRID_CIRCLEQ_HEAD_1(type)                      \
	struct {                                               \
		struct type *cqh_first, /* [1..1] First element */ \
		*cqh_last;              /* [1..1] Last element */  \
	}
#define __HYBRID_CIRCLEQ_HEAD_2(name, type)                \
	struct name {                                          \
		struct type *cqh_first, /* [1..1] First element */ \
		*cqh_last;              /* [1..1] Last element */  \
	}
/* clang-format off */
#define CIRCLEQ_HEAD(...) __HYBRID_PP_VA_OVERLOAD(__HYBRID_CIRCLEQ_HEAD_(__VA_ARGS__))(__VA_ARGS__)
/* clang-format on */
#else /* !__HYBRID_LIST_RESTRICT_API && __HYBRID_PP_VA_OVERLOAD */
#define CIRCLEQ_HEAD(name, type)                           \
	struct name {                                          \
		struct type *cqh_first, /* [1..1] First element */ \
		*cqh_last;              /* [1..1] Last element */  \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__HYBRID_PP_VA_OVERLOAD */
#define CIRCLEQ_HEAD_INITIALIZER(self) \
	{ (void *)&self, (void *)&self }
#endif /* !__cplusplus */
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#define CIRCLEQ_ENTRY(T)                       \
	struct {                                   \
		T *cqe_next, /* [1..1] Next element */ \
		*cqe_prev;   /* [1..1] Prev element */ \
	}
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define CIRCLEQ_ENTRY(type)                              \
	struct {                                             \
		struct type *cqe_next, /* [1..1] Next element */ \
		*cqe_prev;             /* [1..1] Prev element */ \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#ifdef __cplusplus
#define CIRCLEQ_INIT(self) \
	((self)->__cqh_first_ptr = (self)->__cqh_last_ptr = (void *)(self))
#else /* __cplusplus */
#define CIRCLEQ_INIT(self) \
	((self)->cqh_first = (self)->cqh_last = (void *)(self))
#endif /* !__cplusplus */
#define CIRCLEQ_EMPTY(self)                                ((void const *)(self)->cqh_first == (void const *)(self))
#define CIRCLEQ_FIRST(self)                                ((self)->cqh_first)
#define CIRCLEQ_LAST(self)                                 ((self)->cqh_last)
#define CIRCLEQ_INSERT_AFTER(self, predecessor, elem, key) __HYBRID_CIRCLEQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_BEFORE(self, successor, elem, key)  __HYBRID_CIRCLEQ_INSERT_BEFORE(self, successor, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_HEAD(self, elem, key)               __HYBRID_CIRCLEQ_INSERT_HEAD(self, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_INSERT_TAIL(self, elem, key)               __HYBRID_CIRCLEQ_INSERT_TAIL(self, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_REMOVE(self, elem, key)                    __HYBRID_CIRCLEQ_REMOVE(self, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_FOREACH(elem, self, key)                   __HYBRID_CIRCLEQ_FOREACH(elem, self, __HYBRID_Q_KEY, key)
#define CIRCLEQ_FOREACH_REVERSE(elem, self, key)           __HYBRID_CIRCLEQ_FOREACH_REVERSE(elem, self, __HYBRID_Q_KEY, key)
#define CIRCLEQ_NEXT(elem, key)                            __HYBRID_CIRCLEQ_NEXT(elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_PREV(elem, key)                            __HYBRID_CIRCLEQ_PREV(elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_LOOP_NEXT(self, elem, key)                 __HYBRID_CIRCLEQ_LOOP_NEXT(self, elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_LOOP_PREV(self, elem, key)                 __HYBRID_CIRCLEQ_LOOP_PREV(self, elem, __HYBRID_Q_KEY, key)
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
#define CIRCLEQ_ENTRY_INITIALIZER \
	{ __NULLPTR, __NULLPTR }
#define CIRCLEQ_INSERT_AFTER_P(self, predecessor, elem, getpath) __HYBRID_CIRCLEQ_INSERT_AFTER(self, predecessor, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_BEFORE_P(self, successor, elem, getpath)  __HYBRID_CIRCLEQ_INSERT_BEFORE(self, successor, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_HEAD_P(self, elem, getpath)               __HYBRID_CIRCLEQ_INSERT_HEAD(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_INSERT_TAIL_P(self, elem, getpath)               __HYBRID_CIRCLEQ_INSERT_TAIL(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_REPLACE(self, old_elem, new_elem, key)           __HYBRID_CIRCLEQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_KEY, key)
#define CIRCLEQ_REPLACE_P(self, old_elem, new_elem, getpath)     __HYBRID_CIRCLEQ_REPLACE(self, old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_REMOVE_P(self, elem, getpath)                    __HYBRID_CIRCLEQ_REMOVE(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_FOREACH_P(elem, self, getpath)                   __HYBRID_CIRCLEQ_FOREACH(elem, self, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_FOREACH_REVERSE_P(elem, self, getpath)           __HYBRID_CIRCLEQ_FOREACH_REVERSE(elem, self, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_NEXT_P(elem, getpath)                            __HYBRID_CIRCLEQ_NEXT(elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_PREV_P(elem, getpath)                            __HYBRID_CIRCLEQ_PREV(elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_LOOP_NEXT_P(self, elem, getpath)                 __HYBRID_CIRCLEQ_LOOP_NEXT(self, elem, __HYBRID_Q_PTH, getpath)
#define CIRCLEQ_LOOP_PREV_P(self, elem, getpath)                 __HYBRID_CIRCLEQ_LOOP_PREV(self, elem, __HYBRID_Q_PTH, getpath)
#endif /* !__HYBRID_LIST_RESTRICT_API */

#define __HYBRID_CIRCLEQ_INSERT_AFTER(self, predecessor, elem, X, _)     \
	(void)((void *)X(_, predecessor).cqe_next == (void *)(self)          \
	       ? (void)((self)->cqh_last = (elem))                           \
	       : (void)(X(_, X(_, predecessor).cqe_next).cqe_prev = (elem)), \
	       X(_, elem).cqe_next        = X(_, predecessor).cqe_next,      \
	       X(_, elem).cqe_prev        = (predecessor),                   \
	       X(_, predecessor).cqe_next = (elem))
#define __HYBRID_CIRCLEQ_INSERT_BEFORE(self, successor, elem, X, _)    \
	(void)((void *)X(_, successor).cqe_prev == (void *)(self)          \
	       ? (void)((self)->cqh_first = (elem))                        \
	       : (void)(X(_, X(_, successor).cqe_prev).cqe_next = (elem)), \
	       X(_, successor).cqe_prev = (elem),                          \
	       X(_, elem).cqe_next      = (successor),                     \
	       X(_, elem).cqe_prev      = X(_, successor).cqe_prev)
#define __HYBRID_CIRCLEQ_INSERT_HEAD(self, elem, X, _)          \
	(void)((void *)(self)->cqh_last == (void *)(self)           \
	       ? (void)((self)->cqh_last = (elem))                  \
	       : (void)(X(_, (self)->cqh_first).cqe_prev = (elem)), \
	       (self)->cqh_first              = (elem),             \
	       X(_, elem).cqe_next            = (self)->cqh_first,  \
	       *(void **)&X(_, elem).cqe_prev = (void *)(self))
#define __HYBRID_CIRCLEQ_INSERT_TAIL(self, elem, X, _)         \
	(void)((void *)(self)->cqh_first == (void *)(self)         \
	       ? (void)((self)->cqh_first = (elem))                \
	       : (void)(X(_, (self)->cqh_last).cqe_next = (elem)), \
	       (self)->cqh_last               = (elem),            \
	       *(void **)&X(_, elem).cqe_next = (void *)(self),    \
	       X(_, elem).cqe_prev            = (self)->cqh_last)
#define __HYBRID_CIRCLEQ_REPLACE(self, old_elem, new_elem, X, _)                   \
	((void *)(X(_, new_elem).cqe_prev = X(_, old_elem).cqe_prev) == (void *)(self) \
	 ? (void)((self)->cqh_first = (new_elem))                                      \
	 : (void)(X(_, X(_, new_elem).cqe_prev).cqe_next = (new_elem)),                \
	 (void *)(X(_, new_elem).cqe_next = X(_, old_elem).cqe_next) == (void *)(self) \
	 ? (void)((self)->cqh_last = (new_elem))                                       \
	 : (void)(X(_, X(_, new_elem).cqe_next).cqe_prev = (new_elem)),                \
	 __HYBRID_Q_BADPTR(X(_, old_elem).cqe_next),                                   \
	 __HYBRID_Q_BADPTR(X(_, old_elem).cqe_prev))
#define __HYBRID_CIRCLEQ_REMOVE(self, elem, X, _)                        \
	((void *)X(_, elem).cqe_prev == (void *)(self)                       \
	 ? (void)((self)->cqh_first = X(_, elem).cqe_next)                   \
	 : (void)(X(_, X(_, elem).cqe_prev).cqe_next = X(_, elem).cqe_next), \
	 (void *)X(_, elem).cqe_next == (void *)(self)                       \
	 ? (void)((self)->cqh_last = X(_, elem).cqe_prev)                    \
	 : (void)(X(_, X(_, elem).cqe_next).cqe_prev = X(_, elem).cqe_prev), \
	 __HYBRID_Q_BADPTR(X(_, elem).cqe_next),                             \
	 __HYBRID_Q_BADPTR(X(_, elem).cqe_prev))
#define __HYBRID_CIRCLEQ_FOREACH(elem, self, X, _)     \
	for ((elem) = ((self)->cqh_first);                 \
	     (void const *)(elem) != (void const *)(self); \
	     (elem) = X(_, elem).cqe_next)
#define __HYBRID_CIRCLEQ_FOREACH_REVERSE(elem, self, X, _) \
	for ((elem) = ((self)->cqh_last);                      \
	     (void const *)(elem) != (void const *)(self);     \
	     (elem) = (X(_, elem).cqe_prev))
#define __HYBRID_CIRCLEQ_NEXT(elem, X, _) (X(_, elem).cqe_next)
#define __HYBRID_CIRCLEQ_PREV(elem, X, _) (X(_, elem).cqe_prev)
#define __HYBRID_CIRCLEQ_LOOP_NEXT(self, elem, X, _)           \
	((void const *)X(_, elem).cqe_next == (void const *)(self) \
	 ? (self)->cqh_first                                       \
	 : X(_, elem).cqe_next)
#define __HYBRID_CIRCLEQ_LOOP_PREV(self, elem, X, _)           \
	((void const *)X(_, elem).cqe_prev == (void const *)(self) \
	 ? (self)->cqh_last                                        \
	 : X(_, elem).cqe_prev)





/************************************************************************/
/* RINGQ: Head-less Ring-Queue                                          */
/************************************************************************/
#ifndef __HYBRID_LIST_RESTRICT_API
#if !defined(__HYBRID_LIST_RESTRICT_API) && defined(__cplusplus)
#undef RINGQ_ENTRY
#define RINGQ_ENTRY(T)                         \
	struct {                                   \
		T *rqe_next, /* [1..1] Next element */ \
		*rqe_prev;   /* [1..1] Prev element */ \
	}
#else /* !__HYBRID_LIST_RESTRICT_API && __cplusplus */
#define RINGQ_ENTRY(type)                                \
	struct {                                             \
		struct type *rqe_next, /* [1..1] Next element */ \
		*rqe_prev;             /* [1..1] Prev element */ \
	}
#endif /* __HYBRID_LIST_RESTRICT_API || !__cplusplus */
#define RINGQ_ENTRY_P(T)                       \
	struct {                                   \
		T *rqe_next, /* [1..1] Next element */ \
		*rqe_prev;   /* [1..1] Prev element */ \
	}
#define RINGQ_ENTRY_INITIALIZER \
	{ __NULLPTR, __NULLPTR }
/* RINGQ_INIT:          Initialize `elem' as the only element of a new ring.
 * RINGQ_NEXT:          Return the successor of `elem' within its ring.
 * RINGQ_PREV:          Return the predecessor of `elem' within its ring.
 * RINGQ_INSERT_AFTER:  Insert `elem' after `predecessor'
 * RINGQ_INSERT_BEFORE: Insert `elem' before `successor'
 * RINGQ_REMOVE:        Remove `elem' from its ring.
 * RINGQ_REPLACE:       Replace `old_elem' with `new_elem' from its ring. */
#define RINGQ_INIT(elem, key)                            __HYBRID_RINGQ_INIT(elem, __HYBRID_Q_KEY, key)
#define RINGQ_INIT_P(elem, getpath)                      __HYBRID_RINGQ_INIT(elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_NEXT(elem, key)                            __HYBRID_RINGQ_NEXT(elem, __HYBRID_Q_KEY, key)
#define RINGQ_NEXT_P(elem, getpath)                      __HYBRID_RINGQ_NEXT(elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_PREV(elem, key)                            __HYBRID_RINGQ_PREV(elem, __HYBRID_Q_KEY, key)
#define RINGQ_PREV_P(elem, getpath)                      __HYBRID_RINGQ_PREV(elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_INSERT_AFTER(predecessor, elem, key)       __HYBRID_RINGQ_INSERT_AFTER(predecessor, elem, __HYBRID_Q_KEY, key)
#define RINGQ_INSERT_AFTER_P(predecessor, elem, getpath) __HYBRID_RINGQ_INSERT_AFTER(predecessor, elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_INSERT_BEFORE(successor, elem, key)        __HYBRID_RINGQ_INSERT_BEFORE(successor, elem, __HYBRID_Q_KEY, key)
#define RINGQ_INSERT_BEFORE_P(successor, elem, getpath)  __HYBRID_RINGQ_INSERT_BEFORE(successor, elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_REPLACE(old_elem, new_elem, key)           __HYBRID_RINGQ_REPLACE(old_elem, new_elem, __HYBRID_Q_KEY, key)
#define RINGQ_REPLACE_P(old_elem, new_elem, getpath)     __HYBRID_RINGQ_REPLACE(old_elem, new_elem, __HYBRID_Q_PTH, getpath)
#define RINGQ_REMOVE(elem, key)                          __HYBRID_RINGQ_REMOVE(elem, __HYBRID_Q_KEY, key)
#define RINGQ_REMOVE_P(elem, getpath)                    __HYBRID_RINGQ_REMOVE(elem, __HYBRID_Q_PTH, getpath)

#define __HYBRID_RINGQ_INIT(elem, X, _) (X(_, elem).rqe_next = X(_, elem).rqe_prev = (elem))
#define __HYBRID_RINGQ_NEXT(elem, X, _) X(_, elem).rqe_next
#define __HYBRID_RINGQ_PREV(elem, X, _) X(_, elem).rqe_prev
#define __HYBRID_RINGQ_INSERT_AFTER(predecessor, elem, X, _)                           \
	(void)(X(_, (X(_, elem).rqe_next = X(_, predecessor).rqe_next)).rqe_prev = (elem), \
	       X(_, (X(_, elem).rqe_prev = (predecessor))).rqe_next              = (elem))
#define __HYBRID_RINGQ_INSERT_BEFORE(successor, elem, X, _)                          \
	(void)(X(_, (X(_, elem).rqe_prev = X(_, successor).rqe_prev)).rqe_next = (elem), \
	       X(_, (X(_, elem).rqe_next = (successor))).rqe_prev              = (elem))
#define __HYBRID_RINGQ_REPLACE(old_elem, new_elem, X, _)                              \
	(X(_, (X(_, new_elem).rqe_prev = X(_, old_elem).rqe_prev)).rqe_next = (new_elem), \
	 X(_, (X(_, new_elem).rqe_next = X(_, old_elem).rqe_next)).rqe_prev = (new_elem), \
	 __HYBRID_Q_BADPTR(X(_, old_elem).rqe_next),                                      \
	 __HYBRID_Q_BADPTR(X(_, old_elem).rqe_prev))
#define __HYBRID_RINGQ_REMOVE(elem, X, _)                      \
	(X(_, X(_, elem).rqe_prev).rqe_next = X(_, elem).rqe_next, \
	 X(_, X(_, elem).rqe_next).rqe_prev = X(_, elem).rqe_prev, \
	 __HYBRID_Q_BADPTR(X(_, elem).rqe_next),                   \
	 __HYBRID_Q_BADPTR(X(_, elem).rqe_prev))
#endif /* !__HYBRID_LIST_RESTRICT_API */



#ifndef __HYBRID_LIST_WITHOUT_DEPRECATED
/* OLD_SLIST */
#define OLD_SLIST(T) T * /* [0..1] List head */
#define OLD_SLIST_NODE(T)                     \
	struct {                                  \
		T *sn_next; /* [0..1] Next pointer */ \
	}
#define OLD_SLIST_INITNODE \
	{ __NULLPTR }
#define OLD_SLIST_INSERT(l, elem, key) \
	(void)((elem)->key.sn_next = (l), (l) = (elem))

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
#define LLIST_NEXT(elem, key)    ((elem)->key.ln_next)
#define LLIST_PREV(T, elem, key) __COMPILER_CONTAINER_OF((elem)->key.ln_pself, T, key.ln_next)
#define LLIST_HEAD(l)            (l)
#define LLIST_FOREACH(elem, l, key) \
	for ((elem) = (l); (elem); (elem) = (elem)->key.ln_next)
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
#define LLIST_REMOVE(elem, key)                                         \
	((*(elem)->key.ln_pself = (elem)->key.ln_next) != __NULLPTR         \
	 ? (void)((elem)->key.ln_next->key.ln_pself = (elem)->key.ln_pself) \
	 : (void)0)
#define LLIST_REMOVE_P(elem, getpath)                                           \
	((*getpath(elem).ln_pself = getpath(elem).ln_next) != __NULLPTR             \
	 ? (void)(getpath(getpath(elem).ln_next).ln_pself = getpath(elem).ln_pself) \
	 : (void)0)
#define LLIST_UNBIND(elem, key)  (void)((elem)->key.ln_pself = __NULLPTR)
#define LLIST_ISBOUND(elem, key) ((elem)->key.ln_pself != __NULLPTR)
#define LLIST_UNLINK(elem, key)  (LLIST_REMOVE(elem, key), LLIST_UNBIND(elem, key))
#endif /* !__HYBRID_LIST_WITHOUT_DEPRECATED */

#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_SEQUENCE_LIST_H */
