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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/queue.h) */
/* (#) Portability: GNU C Library (/misc/sys/queue.h) */
/* (#) Portability: NetBSD        (/sys/sys/queue.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/queue.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/queue.h) */
/* (#) Portability: uClibc        (/include/sys/queue.h) */
#ifndef _SYS_QUEUE_H
#define _SYS_QUEUE_H 1

#include <__stdinc.h>
#include <features.h>

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
 * [        1 1]   *_LOOP_NEXT(elem, key)                          (or *_NEXT(elem, key) for RINGQ)
 * [        1 1]   *_LOOP_PREV(elem, key)                          (or *_PREV(elem, key) for RINGQ)
 * [1 1 1     1]   *_INSERT_AFTER(predecessor, elem, key)
 * [      1 1  ]   *_INSERT_AFTER(self, predecessor, elem, key)
 * [1     1   1]   *_INSERT_BEFORE(successor, elem, key)
 * [        1  ]   *_INSERT_BEFORE(self, successor, elem, key)
 * [1 1 1 1 1  ]   *_INSERT[_HEAD](self, elem, key)
 * [    1 1 1  ]   *_INSERT_TAIL(self, elem, key)
 * [  1 1      ]   *_REMOVE_HEAD(elem, key)
 * [1         1]   *_REMOVE(elem, key)
 * [  N N 1 1  ]   *_REMOVE(self, elem, key)
 * [1         1]   *_REPLACE(old_elem, new_elem, key)              (requires _KOS_SOURCE or _KOS_KERNEL_SOURCE)
 * [  N N 1 1  ]   *_REPLACE(self, old_elem, new_elem, type, key)  (requires _KOS_SOURCE or _KOS_KERNEL_SOURCE)
 * [N N N N N  ]   *_FOREACH(elem, self, key)
 * [        N  ]   *_FOREACH_REVERSE(elem, self, key)
 * [      N    ]   *_FOREACH_REVERSE(elem, self, headname, key)
 * \-----------/
 *    Runtime
 *   (in O(x))
 */




#define __Q_KEY(key, item)     (item)->key
#define __Q_PTH(getpath, item) getpath(item)
#ifdef NDEBUG
#define __Q_ASSERT(expr)  (void)0
#define __Q_BADPTR(field) (void)0
#else /* NDEBUG */
#include <hybrid/typecore.h>
#if __SIZEOF_POINTER__ == 4
#define __Q_BADPTR(field) (void)(*(void **)&(field) = (void *)__UINT32_C(0xcccccccc))
#elif __SIZEOF_POINTER__ == 8
#define __Q_BADPTR(field) (void)(*(void **)&(field) = (void *)__UINT64_C(0xcccccccccccccccc))
#elif __SIZEOF_POINTER__ == 2
#define __Q_BADPTR(field) (void)(*(void **)&(field) = (void *)__UINT16_C(0xcccc))
#elif __SIZEOF_POINTER__ == 1
#define __Q_BADPTR(field) (void)(*(void **)&(field) = (void *)__UINT8_C(0xcc))
#else /* __SIZEOF_POINTER__ == ... */
#include <libc/string.h>
#define __Q_BADPTR(field) (void)__libc_memset(&(field), 0xcc, __SIZEOF_POINTER__)
#endif /* __SIZEOF_POINTER__ != ... */
#endif /* !NDEBUG */



/* LIST: Single-head, doubly-linked list (via element self-pointers) */
#define LIST_HEAD(name, type)                         \
	struct name {                                     \
		struct type *lh_first; /* [0..1] List head */ \
	}
#define LIST_HEAD_INITIALIZER(self) \
	{ __NULLPTR }
#define LIST_ENTRY(type)                                             \
	struct {                                                         \
		struct type *le_next;  /* [0..1] Next item */                \
		struct type **le_prev; /* [1..1] This item's self-pointer */ \
	}
#define LIST_INIT(self)                           (void)((self)->lh_first = __NULLPTR)
#define LIST_EMPTY(self)                          ((self)->lh_first == __NULLPTR)
#define LIST_FIRST(self)                          (self)->lh_first
#define LIST_INSERT_AFTER(predecessor, elem, key) __X_LIST_INSERT_AFTER(predecessor, elem, __Q_KEY, key)
#define LIST_INSERT_BEFORE(successor, elem, key)  __X_LIST_INSERT_BEFORE(successor, elem, __Q_KEY, key)
#define LIST_INSERT_HEAD(self, elem, key)         __X_LIST_INSERT_HEAD(self, elem, __Q_KEY, key)
#define LIST_REMOVE(elem, key)                    __X_LIST_REMOVE(elem, __Q_KEY, key)
#define LIST_FOREACH(elem, self, key)             __X_LIST_FOREACH(elem, self, __Q_KEY, key)
#define LIST_NEXT(elem, key)                      __X_LIST_NEXT(elem, __Q_KEY, key)
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#define LIST_HEAD_P(T)                      \
	struct {                                \
		T *lh_first; /* [0..1] List head */ \
	}
#define LIST_ENTRY_P(T)                                    \
	struct {                                               \
		T *le_next;  /* [0..1] Next item */                \
		T **le_prev; /* [1..1] This item's self-pointer */ \
	}
#define LIST_INSERT_AFTER_P(predecessor, elem, getpath) __X_LIST_INSERT_AFTER(predecessor, elem, __Q_PTH, getpath)
#define LIST_INSERT_BEFORE_P(successor, elem, getpath)  __X_LIST_INSERT_BEFORE(successor, elem, __Q_PTH, getpath)
#define LIST_INSERT_HEAD_P(self, elem, getpath)         __X_LIST_INSERT_HEAD(self, elem, __Q_PTH, getpath)
#define LIST_REPLACE(old_elem, new_elem, key)           __X_LIST_REPLACE(old_elem, new_elem, __Q_KEY, key)
#define LIST_REPLACE_P(old_elem, new_elem, getpath)     __X_LIST_REPLACE(old_elem, new_elem, __Q_PTH, getpath)
#define LIST_REMOVE_P(elem, getpath)                    __X_LIST_REMOVE(elem, __Q_PTH, getpath)
#define LIST_FOREACH_P(elem, self, getpath)             __X_LIST_FOREACH(elem, self, __Q_PTH, getpath)
#define LIST_NEXT_P(elem, getpath)                      __X_LIST_NEXT(elem, __Q_PTH, getpath)
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#define __X_LIST_INSERT_AFTER(predecessor, elem, X, _)                                            \
	(void)((X(_, elem).le_next = *(X(_, elem).le_prev = &X(_, predecessor).le_next)) != __NULLPTR \
	       ? (void)(X(_, X(_, elem).le_next).le_prev = &X(_, elem).le_next)                       \
	       : (void)0,                                                                             \
	       X(_, predecessor).le_next = (elem))
#define __X_LIST_INSERT_BEFORE(successor, elem, X, _)                 \
	(void)(*(X(_, elem).le_prev = X(_, successor).le_prev)  = (elem), \
	       *(X(_, successor).le_prev = &X(_, elem).le_next) = (successor))
#define __X_LIST_INSERT_HEAD(self, elem, X, _)                            \
	(void)((X(_, elem).le_next = (self)->lh_first) != __NULLPTR           \
	       ? (void)(X(_, (self)->lh_first).le_prev = &X(_, elem).le_next) \
	       : (void)0,                                                     \
	       *(X(_, elem).le_prev = &(self)->lh_first) = (elem))
#define __X_LIST_REMOVE(elem, X, _)                                  \
	((*X(_, elem).le_prev = X(_, elem).le_next) != __NULLPTR         \
	 ? (void)(X(_, X(_, elem).le_next).le_prev = X(_, elem).le_prev) \
	 : (void)0,                                                      \
	 __Q_BADPTR(X(_, elem).le_next),                                 \
	 __Q_BADPTR(X(_, elem).le_prev))
#define __X_LIST_REPLACE(old_elem, new_elem, X, _)                            \
	(*(X(_, new_elem).le_prev = X(_, old_elem).le_prev) = (new_elem),         \
	 (X(_, new_elem).le_next = X(_, old_elem).le_next) != __NULLPTR           \
	 ? (void)(X(_, X(_, new_elem).le_next).le_prev = &X(_, new_elem).le_next) \
	 : (void)0,                                                               \
	 __Q_BADPTR(X(_, old_elem).le_prev),                                      \
	 __Q_BADPTR(X(_, old_elem).le_next))
#define __X_LIST_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->lh_first; (elem); (elem) = X(_, elem).le_next)
#define __X_LIST_EMPTY(self)      ((self)->lh_first == __NULLPTR)
#define __X_LIST_FIRST(self)      ((self)->lh_first)
#define __X_LIST_NEXT(elem, X, _) (X(_, elem).le_next)




/* SLIST: Single-head, singly-linked list */
#define SLIST_HEAD(name, type)                         \
	struct name {                                      \
		struct type *slh_first; /* [0..1] List head */ \
	}
#define SLIST_HEAD_INITIALIZER(self) \
	{ __NULLPTR }
#define SLIST_ENTRY(type)                             \
	struct {                                          \
		struct type *sle_next; /* [0..1] Next-link */ \
	}
#define SLIST_INIT(self) \
	(void)((self)->slh_first = __NULLPTR)
#define SLIST_EMPTY(self)                          ((self)->slh_first == __NULLPTR)
#define SLIST_FIRST(self)                          ((self)->slh_first)
#define SLIST_INSERT_AFTER(predecessor, elem, key) __X_SLIST_INSERT_AFTER(predecessor, elem, __Q_KEY, key)
#define SLIST_INSERT(l, elem, key)                 __X_SLIST_INSERT(l, elem, __Q_KEY, key)
#define SLIST_REMOVE_HEAD(self, key)               __X_SLIST_REMOVE_HEAD(self, __Q_KEY, key)
#define SLIST_REMOVE(self, elem, type, key)        __X_SLIST_REMOVE(self, elem, struct type, __Q_KEY, key)
#define SLIST_FOREACH(elem, self, key)             __X_SLIST_FOREACH(elem, self, __Q_KEY, key)
#define SLIST_NEXT(elem, key)                      __X_SLIST_NEXT(elem, __Q_KEY, key)
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#define SLIST_HEAD_P(T)                      \
	struct {                                 \
		T *slh_first; /* [0..1] List head */ \
	}
#define SLIST_ENTRY_P(T)                    \
	struct {                                \
		T *sle_next; /* [0..1] Next-link */ \
	}
#define SLIST_INSERT_AFTER_P(predecessor, elem, getpath)       __X_SLIST_INSERT_AFTER(predecessor, elem, __Q_PTH, getpath)
#define SLIST_INSERT_P(l, elem, getpath)                       __X_SLIST_INSERT(l, elem, __Q_PTH, getpath)
#define SLIST_REMOVE_HEAD_P(self, getpath)                     __X_SLIST_REMOVE_HEAD(self, __Q_PTH, getpath)
#define SLIST_REMOVE_P(self, elem, T, getpath)                 __X_SLIST_REMOVE(self, elem, T, __Q_PTH, getpath)
#define SLIST_REPLACE(self, old_elem, new_elem, type, key)     __X_SLIST_REPLACE(self, old_elem, new_elem, struct type, __Q_KEY, key)
#define SLIST_REPLACE_P(self, old_elem, new_elem, T, kgetpath) __X_SLIST_REPLACE(self, old_elem, new_elem, T, __Q_PTH, getpath)
#define SLIST_FOREACH_P(elem, self, getpath)                   __X_SLIST_FOREACH(elem, self, __Q_PTH, getpath)
#define SLIST_NEXT_P(elem, getpath)                            __X_SLIST_NEXT(elem, __Q_PTH, getpath)
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#define __X_SLIST_INSERT_AFTER(predecessor, elem, X, _)           \
	(void)(X(_, elem).sn_next        = X(_, predecessor).sn_next, \
	       X(_, predecessor).sn_next = (elem))
#define __X_SLIST_INSERT(l, elem, X, _)         \
	(void)(X(_, elem).sn_next = (l)->slh_first, \
	       (l)->slh_first     = (elem))
#define __X_SLIST_REMOVE_HEAD(self, X, _) \
	(void)((self)->slh_first = X(_, (self)->slh_first).sle_next)
#define __X_SLIST_REMOVE(self, elem, T, X, _)     \
	/* Sorry, this one must be state statement */ \
	do {                                          \
		T **__piter = &(self)->slh_first;         \
		while (*__piter != (elem))                \
			__piter = &X(_, *__piter).sle_next;   \
		*__piter = X(_, elem).sle_next;           \
		__Q_BADPTR(X(_, elem).sle_next);          \
	}                                             \
	__WHILE0
#define __X_SLIST_REPLACE(self, old_elem, new_elem, T, X, _) \
	/* Sorry, this one must be state statement */            \
	do {                                                     \
		T **__piter = &(self)->slh_first;                    \
		while (*__piter != (old_elem))                       \
			__piter = &X(_, *__piter).sle_next;              \
		X(_, new_elem).sle_next = X(_, old_elem).sle_next;   \
		*__piter                = (new_elem);                \
		__Q_BADPTR(X(_, old_elem).sle_next);                 \
	}                                                        \
	__WHILE0
#define __X_SLIST_FOREACH(elem, self, X, _) \
	for ((elem) = (self)->slh_first;        \
	     (elem);                            \
	     (elem) = X(_, elem).sle_next)
#define __X_SLIST_NEXT(elem, X, _) X(_, elem).sle_next


/* Double-head, singly-linked Tail queue. */
#define STAILQ_HEAD(name, type)                                                      \
	struct name {                                                                    \
		struct type *stqh_first; /* [0..1] List head */                              \
		struct type **stqh_last; /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define STAILQ_HEAD_INITIALIZER(self) \
	{ __NULLPTR, &(self).stqh_first }
#define STAILQ_ENTRY(type)                                \
	struct {                                              \
		struct type *stqe_next; /* [0..1] Next element */ \
	}
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
#define STAILQ_INSERT_HEAD(self, elem, key)               __X_STAILQ_INSERT_HEAD(self, elem, __Q_KEY, key)
#define STAILQ_INSERT_TAIL(self, elem, key)               __X_STAILQ_INSERT_TAIL(self, elem, __Q_KEY, key)
#define STAILQ_INSERT_AFTER(self, predecessor, elem, key) __X_STAILQ_INSERT_AFTER(self, predecessor, elem, __Q_KEY, key)
#define STAILQ_REMOVE_HEAD(self, key)                     __X_STAILQ_REMOVE_HEAD(self, __Q_KEY, key)
#define STAILQ_REMOVE(self, elem, type, key)              __X_STAILQ_REMOVE(self, elem, struct type, __Q_KEY, key)
#define STAILQ_FOREACH(elem, self, key)                   __X_STAILQ_FOREACH(elem, self, __Q_KEY, key)
#define STAILQ_NEXT(elem, key)                            __X_STAILQ_NEXT(elem, __Q_KEY, key)
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#define STAILQ_HEAD_P(T)                                                   \
	struct {                                                               \
		T *stqh_first; /* [0..1] List head */                              \
		T **stqh_last; /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define STAILQ_ENTRY_P(T)                       \
	struct {                                    \
		T *stqe_next; /* [0..1] Next element */ \
	}
#define STAILQ_INSERT_HEAD_P(self, elem, getpath)               __X_STAILQ_INSERT_HEAD(self, elem, __Q_PTH, getpath)
#define STAILQ_INSERT_TAIL_P(self, elem, getpath)               __X_STAILQ_INSERT_TAIL(self, elem, __Q_PTH, getpath)
#define STAILQ_INSERT_AFTER_P(self, predecessor, elem, getpath) __X_STAILQ_INSERT_AFTER(self, predecessor, elem, __Q_PTH, getpath)
#define STAILQ_REMOVE_HEAD_P(self, getpath)                     __X_STAILQ_REMOVE_HEAD(self, __Q_PTH, getpath)
#define STAILQ_REMOVE_P(self, elem, T, getpath)                 __X_STAILQ_REMOVE(self, elem, T, __Q_PTH, getpath)
#define STAILQ_REPLACE(self, old_elem, new_elem, type, key)     __X_STAILQ_REPLACE(self, elem, struct type, __Q_KEY, key)
#define STAILQ_REPLACE_P(self, old_elem, new_elem, T, getpath)  __X_STAILQ_REMOVE(self, elem, T, __Q_PTH, getpath)
#define STAILQ_FOREACH_P(elem, self, getpath)                   __X_STAILQ_FOREACH(elem, self, __Q_PTH, getpath)
#define STAILQ_NEXT_P(elem, getpath)                            __X_STAILQ_NEXT(elem, __Q_PTH, getpath)
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#define __X_STAILQ_INSERT_HEAD(self, elem, X, _)              \
	((X(_, elem).stqe_next = (self)->stqh_first) == __NULLPTR \
	 ? (void)((self)->stqh_last = &X(_, elem).stqe_next)      \
	 : (void)0,                                               \
	 (void)((self)->stqh_first = (elem)))
#define __X_STAILQ_INSERT_TAIL(self, elem, X, _)         \
	(void)(*(self)->stqh_last   = (elem),                \
	       (self)->stqh_last    = &X(_, elem).stqe_next, \
	       X(_, elem).stqe_next = __NULLPTR)
#define __X_STAILQ_INSERT_AFTER(self, predecessor, elem, X, _)         \
	((X(_, elem).stqe_next = X(_, predecessor).stqe_next) == __NULLPTR \
	 ? (void)((self)->stqh_last = &X(_, elem).stqe_next)               \
	 : (void)0,                                                        \
	 X(_, predecessor).stqe_next = (elem))
#define __X_STAILQ_REMOVE_HEAD(self, X, _)                                  \
	(((self)->stqh_first = X(_, (self)->stqh_first).stqe_next) == __NULLPTR \
	 ? (void)((self)->stqh_last = &(self)->stqh_first)                      \
	 : (void)0)
#define __X_STAILQ_REMOVE(self, elem, T, X, _)              \
	/* Sorry, this one must be state statement */           \
	do {                                                    \
		T **__piter = &(self)->stqh_first;                  \
		while (*__piter != (elem))                          \
			__piter = &X(_, *__piter).stqe_next;            \
		if ((*__piter = X(_, elem).stqe_next) == __NULLPTR) \
			(self)->stqh_last = __piter;                    \
		__Q_BADPTR(X(_, elem).stqe_next);                   \
	}                                                       \
	__WHILE0
#define __X_STAILQ_REPLACE(self, old_elem, new_elem, T, X, _) \
	/* Sorry, this one must be state statement */             \
	do {                                                      \
		T **__piter = &(self)->stqh_first;                    \
		while (*__piter != (old_elem))                        \
			__piter = &X(_, *__piter).stqe_next;              \
		X(_, new_elem).stqe_next = *__piter;                  \
		*__piter                 = (new_elem);                \
		__Q_BADPTR(X(_, old_elem).stqe_next);                 \
	}                                                         \
	__WHILE0
#define __X_STAILQ_FOREACH(elem, self, X, _) \
	for ((elem) = ((self)->stqh_first);      \
	     (elem);                             \
	     (elem) = (X(_, elem).stqe_next))
#define __X_STAILQ_NEXT(elem, X, _) (X(_, elem).stqe_next)




/* Simple queue. (Alias for `Double-head, singly-linked Tail queue', with different field names) */
#define SIMPLEQ_HEAD(name, type)                                                    \
	struct name {                                                                   \
		struct type *sqh_first; /* [0..1] Head element */                           \
		struct type **sqh_last; /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define SIMPLEQ_HEAD_INITIALIZER(self) \
	{ __NULLPTR, &(self).sqh_first }
#define SIMPLEQ_ENTRY(type)                              \
	struct {                                             \
		struct type *sqe_next; /* [0..1] Next element */ \
	}
#define SIMPLEQ_INIT(self) \
	(void)(*((self)->sqh_last = &(self)->sqh_first) = __NULLPTR)
#define SIMPLEQ_EMPTY(self)                                ((self)->sqh_first == __NULLPTR)
#define SIMPLEQ_FIRST(self)                                ((self)->sqh_first)
#define SIMPLEQ_INSERT_HEAD(self, elem, key)               __X_SIMPLEQ_INSERT_HEAD(self, elem, __Q_KEY, key)
#define SIMPLEQ_INSERT_TAIL(self, elem, key)               __X_SIMPLEQ_INSERT_TAIL(self, elem, __Q_KEY, key)
#define SIMPLEQ_INSERT_AFTER(self, predecessor, elem, key) __X_SIMPLEQ_INSERT_AFTER(self, predecessor, elem, __Q_KEY, key)
#define SIMPLEQ_REMOVE_HEAD(self, key)                     __X_SIMPLEQ_REMOVE_HEAD(self, __Q_KEY, key)
#define SIMPLEQ_REMOVE(self, elem, type, key)              __X_SIMPLEQ_REMOVE(self, elem, type, __Q_KEY, key)
#define SIMPLEQ_FOREACH(elem, self, key)                   __X_SIMPLEQ_FOREACH(elem, self, __Q_KEY, key)
#define SIMPLEQ_NEXT(elem, key)                            __X_SIMPLEQ_NEXT(elem, __Q_KEY, key)
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#define SIMPLEQ_HEAD_P(T)                                                 \
	struct {                                                              \
		T *sqh_first; /* [0..1] Head element */                           \
		T **sqh_last; /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define SIMPLEQ_ENTRY_P(T)                     \
	struct {                                   \
		T *sqe_next; /* [0..1] Next element */ \
	}
#define SIMPLEQ_INSERT_HEAD_P(self, elem, getpath)               __X_SIMPLEQ_INSERT_HEAD(self, elem, __Q_PTH, getpath)
#define SIMPLEQ_INSERT_TAIL_P(self, elem, getpath)               __X_SIMPLEQ_INSERT_TAIL(self, elem, __Q_PTH, getpath)
#define SIMPLEQ_INSERT_AFTER_P(self, predecessor, elem, getpath) __X_SIMPLEQ_INSERT_AFTER(self, predecessor, elem, __Q_PTH, getpath)
#define SIMPLEQ_REMOVE_HEAD_P(self, getpath)                     __X_SIMPLEQ_REMOVE_HEAD(self, __Q_PTH, getpath)
#define SIMPLEQ_REMOVE_P(self, elem, type, getpath)              __X_SIMPLEQ_REMOVE(self, elem, type, __Q_PTH, getpath)
#define SIMPLEQ_REPLACE(self, old_elem, new_elem, type, key)     __X_SIMPLEQ_REPLACE(self, elem, struct type, __Q_KEY, key)
#define SIMPLEQ_REPLACE_P(self, old_elem, new_elem, T, getpath)  __X_SIMPLEQ_REMOVE(self, elem, T, __Q_PTH, getpath)
#define SIMPLEQ_FOREACH_P(elem, self, getpath)                   __X_SIMPLEQ_FOREACH(elem, self, __Q_PTH, getpath)
#define SIMPLEQ_NEXT_P(elem, getpath)                            __X_SIMPLEQ_NEXT(elem, __Q_PTH, getpath)
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#define __X_SIMPLEQ_INSERT_HEAD(self, elem, X, _)           \
	((X(_, elem).sqe_next = (self)->sqh_first) == __NULLPTR \
	 ? (void)((self)->sqh_last = &X(_, elem).sqe_next)      \
	 : (void)0,                                             \
	 (void)((self)->sqh_first = (elem)))
#define __X_SIMPLEQ_INSERT_TAIL(self, elem, X, _)      \
	(void)(*(self)->sqh_last   = (elem),               \
	       (self)->sqh_last    = &X(_, elem).sqe_next, \
	       X(_, elem).sqe_next = __NULLPTR)
#define __X_SIMPLEQ_INSERT_AFTER(self, predecessor, elem, X, _)      \
	((X(_, elem).sqe_next = X(_, predecessor).sqe_next) == __NULLPTR \
	 ? (void)((self)->sqh_last = &X(_, elem).sqe_next)               \
	 : (void)0,                                                      \
	 (void)(X(_, predecessor).sqe_next = (elem)))
#define __X_SIMPLEQ_REMOVE_HEAD(self, X, _)                              \
	(((self)->sqh_first = X(_, (self)->sqh_first).sqe_next) == __NULLPTR \
	 ? (void)((self)->sqh_last = &(self)->sqh_first)                     \
	 : (void)0)
#define __X_SIMPLEQ_REMOVE(self, elem, type, X, _)         \
	/* Sorry, this one must be state statement */          \
	do {                                                   \
		struct type **__piter = &(self)->sqh_first;        \
		while (*__piter != (elem))                         \
			__piter = &X(_, *__piter).sqe_next;            \
		if ((*__piter = X(_, elem).sqe_next) == __NULLPTR) \
			(self)->sqh_last = __piter;                    \
		__Q_BADPTR(X(_, elem).sqe_next);                   \
	}                                                      \
	__WHILE0
#define __X_SIMPLEQ_REPLACE(self, old_elem, new_elem, T, X, _) \
	/* Sorry, this one must be state statement */              \
	do {                                                       \
		T **__piter = &(self)->sqh_first;                      \
		while (*__piter != (old_elem))                         \
			__piter = &X(_, *__piter).sqe_next;                \
		X(_, new_elem).sqe_next = *__piter;                    \
		*__piter                = (new_elem);                  \
		__Q_BADPTR(X(_, old_elem).sqe_next);                   \
	}                                                          \
	__WHILE0
#define __X_SIMPLEQ_FOREACH(elem, self, X, _) \
	for ((elem) = ((self)->sqh_first);        \
	     (elem);                              \
	     (elem) = (X(_, elem).sqe_next))
#define __X_SIMPLEQ_NEXT(elem, X, _) (X(_, elem).sqe_next)



/* Double-head, doubly-linked tail queue */
#define _TAILQ_HEAD(name, T, qual)                                                  \
	struct name {                                                                   \
		T qual *tqh_first;      /* [0..1] Head element */                           \
		T qual *qual *tqh_last; /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define TAILQ_HEAD(name, type) _TAILQ_HEAD(name, struct type, )
#define TAILQ_HEAD_INITIALIZER(self) \
	{ __NULLPTR, &(self).tqh_first }
#define _TAILQ_ENTRY(T, qual)              \
	struct {                               \
		T qual *tqe_next;       /* TODO */ \
		T qual *qual *tqe_prev; /* TODO */ \
	}
#define TAILQ_ENTRY(type) _TAILQ_ENTRY(struct type, )
#define TAILQ_INIT(self) \
	(void)(*((self)->tqh_last = &(self)->tqh_first) = __NULLPTR)
#define TAILQ_EMPTY(self)                                ((self)->tqh_first == __NULLPTR)
#define TAILQ_FIRST(self)                                ((self)->tqh_first)
#define TAILQ_LAST(self, headname)                       (*(((struct headname *)((self)->tqh_last))->tqh_last))
#define TAILQ_INSERT_HEAD(self, elem, key)               __X_TAILQ_INSERT_HEAD(self, elem, __Q_KEY, key)
#define TAILQ_INSERT_TAIL(self, elem, key)               __X_TAILQ_INSERT_TAIL(self, elem, __Q_KEY, key)
#define TAILQ_INSERT_AFTER(self, predecessor, elem, key) __X_TAILQ_INSERT_AFTER(self, predecessor, elem, __Q_KEY, key)
#define TAILQ_INSERT_BEFORE(successor, elem, key)        __X_TAILQ_INSERT_BEFORE(successor, elem, __Q_KEY, key)
#define TAILQ_REMOVE(self, elem, key)                    __X_TAILQ_REMOVE(self, elem, __Q_KEY, key)
#define TAILQ_FOREACH(elem, self, key)                   __X_TAILQ_FOREACH(elem, self, __Q_KEY, key)
#define TAILQ_FOREACH_REVERSE(elem, self, headname, key) __X_TAILQ_FOREACH_REVERSE(elem, self, struct headname, __Q_KEY, key)
#define TAILQ_CONCAT(dst, src, key)                      __X_TAILQ_CONCAT(dst, src, __Q_KEY, key)
#define TAILQ_NEXT(elem, key)                            __X_TAILQ_NEXT(elem, __Q_KEY, key)
#define TAILQ_PREV(elem, headname, key)                  __X_TAILQ_PREV(elem, struct headname, __Q_KEY, key)
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#define _TAILQ_HEAD_P(T, qual)                                                      \
	struct {                                                                        \
		T qual *tqh_first;      /* [0..1] Head element */                           \
		T qual *qual *tqh_last; /* [0..1][1..1] Pointer to last-element-pointer. */ \
	}
#define TAILQ_HEAD_P(T) _TAILQ_HEAD_P(T, )
#define _TAILQ_ENTRY_P(T, qual)            \
	struct {                               \
		T qual *tqe_next;       /* TODO */ \
		T qual *qual *tqe_prev; /* TODO */ \
	}
#define TAILQ_ENTRY_P(T)                                       _TAILQ_ENTRY_P(T, )
#define TAILQ_LAST_P(self, HEAD_T)                             (*(((HEAD_T *)((self)->tqh_last))->tqh_last))
#define TAILQ_INSERT_HEAD_P(self, elem, getpath)               __X_TAILQ_INSERT_HEAD(self, elem, __Q_PTH, getpath)
#define TAILQ_INSERT_TAIL_P(self, elem, getpath)               __X_TAILQ_INSERT_TAIL(self, elem, __Q_PTH, getpath)
#define TAILQ_INSERT_AFTER_P(self, predecessor, elem, getpath) __X_TAILQ_INSERT_AFTER(self, predecessor, elem, __Q_PTH, getpath)
#define TAILQ_INSERT_BEFORE_P(successor, elem, getpath)        __X_TAILQ_INSERT_BEFORE(successor, elem, __Q_PTH, getpath)
#define TAILQ_REPLACE(self, old_elem, new_elem, key)           __X_TAILQ_REPLACE(self, old_elem, new_elem, __Q_KEY, key)
#define TAILQ_REPLACE_P(self, old_elem, new_elem, getpath)     __X_TAILQ_REPLACE(self, old_elem, new_elem, __Q_PTH, getpath)
#define TAILQ_REMOVE_P(self, elem, getpath)                    __X_TAILQ_REMOVE(self, elem, __Q_PTH, getpath)
#define TAILQ_FOREACH_P(elem, self, getpath)                   __X_TAILQ_FOREACH(elem, self, __Q_PTH, getpath)
#define TAILQ_FOREACH_REVERSE_P(elem, self, HEAD_T, getpath)   __X_TAILQ_FOREACH_REVERSE(elem, self, HEAD_T, __Q_PTH, getpath)
#define TAILQ_CONCAT_P(dst, src, getpath)                      __X_TAILQ_CONCAT(dst, src, __Q_PTH, getpath)
#define TAILQ_NEXT_P(elem, getpath)                            __X_TAILQ_NEXT(elem, __Q_PTH, getpath)
#define TAILQ_PREV_P(elem, HEAD_T, getpath)                    __X_TAILQ_PREV(elem, HEAD_T, __Q_PTH, getpath)
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#define __X_TAILQ_INSERT_HEAD(self, elem, X, _)                              \
	(void)((X(_, elem).tqe_next = (self)->tqh_first) != __NULLPTR            \
	       ? (void)(X(_, (self)->tqh_first).tqe_prev = &X(_, elem).tqe_next) \
	       : (void)((self)->tqh_last = &X(_, elem).tqe_next),                \
	       X(_, (self)->tqh_first = (elem)).tqe_prev = &(self)->tqh_first)
#define __X_TAILQ_INSERT_TAIL(self, elem, X, _)                 \
	(void)(*(X(_, elem).tqe_prev = (self)->tqh_last)  = (elem), \
	       *((self)->tqh_last = &X(_, elem).tqe_next) = __NULLPTR)
#define __X_TAILQ_INSERT_AFTER(self, predecessor, elem, X, _)            \
	((X(_, elem).tqe_next = X(_, predecessor).tqe_next) != __NULLPTR     \
	 ? (void)(X(_, X(_, elem).tqe_next).tqe_prev = &X(_, elem).tqe_next) \
	 : (void)((self)->tqh_last = &X(_, elem).tqe_next),                  \
	 (void)(*(X(_, elem).tqe_prev = &X(_, predecessor).tqe_next) = (elem)))
#define __X_TAILQ_INSERT_BEFORE(successor, elem, X, _)                  \
	(void)(*(X(_, elem).tqe_prev = X(_, successor).tqe_prev)  = (elem), \
	       *(X(_, successor).tqe_prev = &X(_, elem).tqe_next) = (successor))
#define __X_TAILQ_REPLACE(self, old_elem, new_elem, X, _)               \
	((X(_, new_elem).tqe_next = X(_, old_elem).tqe_next) != __NULLPTR   \
	 ? (void)(X(_, X(_, old_elem).tqe_next).tqe_prev = (new_elem))      \
	 : (void)((self)->tqh_last = (new_elem)),                           \
	 *(X(_, new_elem).tqe_prev = X(_, old_elem).tqe_prev) = (new_elem), \
	 __Q_BADPTR(X(_, old_elem).tqe_next),                               \
	 __Q_BADPTR(X(_, old_elem).tqe_prev))
#define __X_TAILQ_REMOVE(self, elem, X, _)                              \
	(X(_, elem).tqe_next != __NULLPTR                                   \
	 ? (void)(X(_, X(_, elem).tqe_next).tqe_prev = X(_, elem).tqe_prev) \
	 : (void)((self)->tqh_last = X(_, elem).tqe_prev),                  \
	 *X(_, elem).tqe_prev = X(_, elem).tqe_next,                        \
	 __Q_BADPTR(X(_, elem).tqe_next),                                   \
	 __Q_BADPTR(X(_, elem).tqe_prev))
#define __X_TAILQ_FOREACH(elem, self, X, _) \
	for ((elem) = ((self)->tqh_first);      \
	     (elem);                            \
	     (elem) = (X(_, elem).tqe_next))
#define __X_TAILQ_FOREACH_REVERSE(elem, self, HEAD_T, X, _)      \
	for ((elem) = (*(((HEAD_T *)((self)->tqh_last))->tqh_last)); \
	     (elem);                                                 \
	     (elem) = (*(((HEAD_T *)(X(_, elem).tqe_prev))->tqh_last)))
#define __X_TAILQ_CONCAT(dst, src, X, _)                                            \
	((src)->tqh_first != __NULLPTR                                                  \
	 ? (void)(X(_, *(dst)->tqh_last = (src)->tqh_first).tqe_prev = (dst)->tqh_last, \
	          (dst)->tqh_last                                    = (src)->tqh_last, \
	          TAILQ_INIT(src))                                                      \
	 : (void)0)
#define __X_TAILQ_NEXT(elem, X, _)         (X(_, elem).tqe_next)
#define __X_TAILQ_PREV(elem, HEAD_T, X, _) (*(((HEAD_T *)(X(_, elem).tqe_prev))->tqh_last))



/* Circular queue */
#ifdef __cplusplus
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
#define CIRCLEQ_HEAD(name, type)                           \
	struct name {                                          \
		struct type *cqh_first; /* [1..1] First element */ \
		struct type *cqh_last;  /* [1..1] Last element */  \
	}
#define CIRCLEQ_HEAD_INITIALIZER(self) \
	{ (void *)&self, (void *)&self }
#endif /* !__cplusplus */
#define CIRCLEQ_ENTRY(type)                              \
	struct {                                             \
		struct type *cqe_next; /* [1..1] Next element */ \
		struct type *cqe_prev; /* [1..1] Prev element */ \
	}

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
#define CIRCLEQ_INSERT_AFTER(self, predecessor, elem, key) __X_CIRCLEQ_INSERT_AFTER(self, predecessor, elem, __Q_KEY, key)
#define CIRCLEQ_INSERT_BEFORE(self, successor, elem, key)  __X_CIRCLEQ_INSERT_BEFORE(self, successor, elem, __Q_KEY, key)
#define CIRCLEQ_INSERT_HEAD(self, elem, key)               __X_CIRCLEQ_INSERT_HEAD(self, elem, __Q_KEY, key)
#define CIRCLEQ_INSERT_TAIL(self, elem, key)               __X_CIRCLEQ_INSERT_TAIL(self, elem, __Q_KEY, key)
#define CIRCLEQ_REMOVE(self, elem, key)                    __X_CIRCLEQ_REMOVE(self, elem, __Q_KEY, key)
#define CIRCLEQ_FOREACH(elem, self, key)                   __X_CIRCLEQ_FOREACH(elem, self, __Q_KEY, key)
#define CIRCLEQ_FOREACH_REVERSE(elem, self, key)           __X_CIRCLEQ_FOREACH_REVERSE(elem, self, __Q_KEY, key)
#define CIRCLEQ_NEXT(elem, key)                            __X_CIRCLEQ_NEXT(elem, __Q_KEY, key)
#define CIRCLEQ_PREV(elem, key)                            __X_CIRCLEQ_PREV(elem, __Q_KEY, key)
#define CIRCLEQ_LOOP_NEXT(self, elem, key)                 __X_CIRCLEQ_LOOP_NEXT(self, elem, __Q_KEY, key)
#define CIRCLEQ_LOOP_PREV(self, elem, key)                 __X_CIRCLEQ_LOOP_PREV(self, elem, __Q_KEY, key)
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
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
		T *cqh_first; /* [1..1] First element */ \
		T *cqh_last;  /* [1..1] Last element */  \
	}
#endif /* !__cplusplus */
#define CIRCLEQ_ENTRY_P(T)                     \
	struct {                                   \
		T *cqe_next; /* [1..1] Next element */ \
		T *cqe_prev; /* [1..1] Prev element */ \
	}
#define CIRCLEQ_INSERT_AFTER_P(self, predecessor, elem, getpath) __X_CIRCLEQ_INSERT_AFTER(self, predecessor, elem, __Q_PTH, getpath)
#define CIRCLEQ_INSERT_BEFORE_P(self, successor, elem, getpath)  __X_CIRCLEQ_INSERT_BEFORE(self, successor, elem, __Q_PTH, getpath)
#define CIRCLEQ_INSERT_HEAD_P(self, elem, getpath)               __X_CIRCLEQ_INSERT_HEAD(self, elem, __Q_PTH, getpath)
#define CIRCLEQ_INSERT_TAIL_P(self, elem, getpath)               __X_CIRCLEQ_INSERT_TAIL(self, elem, __Q_PTH, getpath)
#define CIRCLEQ_REPLACE(self, old_elem, new_elem, key)           __X_CIRCLEQ_REPLACE(self, old_elem, new_elem, __Q_KEY, key)
#define CIRCLEQ_REPLACE_P(self, old_elem, new_elem, getpath)     __X_CIRCLEQ_REPLACE(self, old_elem, new_elem, __Q_PTH, getpath)
#define CIRCLEQ_REMOVE_P(self, elem, getpath)                    __X_CIRCLEQ_REMOVE(self, elem, __Q_PTH, getpath)
#define CIRCLEQ_FOREACH_P(elem, self, getpath)                   __X_CIRCLEQ_FOREACH(elem, self, __Q_PTH, getpath)
#define CIRCLEQ_FOREACH_REVERSE_P(elem, self, getpath)           __X_CIRCLEQ_FOREACH_REVERSE(elem, self, __Q_PTH, getpath)
#define CIRCLEQ_NEXT_P(elem, getpath)                            __X_CIRCLEQ_NEXT(elem, __Q_PTH, getpath)
#define CIRCLEQ_PREV_P(elem, getpath)                            __X_CIRCLEQ_PREV(elem, __Q_PTH, getpath)
#define CIRCLEQ_LOOP_NEXT_P(self, elem, getpath)                 __X_CIRCLEQ_LOOP_NEXT(self, elem, __Q_PTH, getpath)
#define CIRCLEQ_LOOP_PREV_P(self, elem, getpath)                 __X_CIRCLEQ_LOOP_PREV(self, elem, __Q_PTH, getpath)
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#define __X_CIRCLEQ_INSERT_AFTER(self, predecessor, elem, X, _)          \
	(void)((void *)X(_, predecessor).cqe_next == (void *)(self)          \
	       ? (void)((self)->cqh_last = (elem))                           \
	       : (void)(X(_, X(_, predecessor).cqe_next).cqe_prev = (elem)), \
	       X(_, elem).cqe_next        = X(_, predecessor).cqe_next,      \
	       X(_, elem).cqe_prev        = (predecessor),                   \
	       X(_, predecessor).cqe_next = (elem))
#define __X_CIRCLEQ_INSERT_BEFORE(self, successor, elem, X, _)         \
	(void)((void *)X(_, successor).cqe_prev == (void *)(self)          \
	       ? (void)((self)->cqh_first = (elem))                        \
	       : (void)(X(_, X(_, successor).cqe_prev).cqe_next = (elem)), \
	       X(_, successor).cqe_prev = (elem),                          \
	       X(_, elem).cqe_next      = (successor),                     \
	       X(_, elem).cqe_prev      = X(_, successor).cqe_prev)
#define __X_CIRCLEQ_INSERT_HEAD(self, elem, X, _)               \
	(void)((void *)(self)->cqh_last == (void *)(self)           \
	       ? (void)((self)->cqh_last = (elem))                  \
	       : (void)(X(_, (self)->cqh_first).cqe_prev = (elem)), \
	       (self)->cqh_first              = (elem),             \
	       X(_, elem).cqe_next            = (self)->cqh_first,  \
	       *(void **)&X(_, elem).cqe_prev = (void *)(self))
#define __X_CIRCLEQ_INSERT_TAIL(self, elem, X, _)              \
	(void)((void *)(self)->cqh_first == (void *)(self)         \
	       ? (void)((self)->cqh_first = (elem))                \
	       : (void)(X(_, (self)->cqh_last).cqe_next = (elem)), \
	       (self)->cqh_last               = (elem),            \
	       *(void **)&X(_, elem).cqe_next = (void *)(self),    \
	       X(_, elem).cqe_prev            = (self)->cqh_last)
#define __X_CIRCLEQ_REPLACE(self, old_elem, new_elem, X, _)                        \
	((void *)(X(_, new_elem).cqe_prev = X(_, old_elem).cqe_prev) == (void *)(self) \
	 ? (void)((self)->cqh_first = (new_elem))                                      \
	 : (void)(X(_, X(_, new_elem).cqe_prev).cqe_next = (new_elem)),                \
	 (void *)(X(_, new_elem).cqe_next = X(_, old_elem).cqe_next) == (void *)(self) \
	 ? (void)((self)->cqh_last = (new_elem))                                       \
	 : (void)(X(_, X(_, new_elem).cqe_next).cqe_prev = (new_elem)),                \
	 __Q_BADPTR(X(_, old_elem).cqe_next),                                          \
	 __Q_BADPTR(X(_, old_elem).cqe_prev))
#define __X_CIRCLEQ_REMOVE(self, elem, X, _)                             \
	((void *)X(_, elem).cqe_prev == (void *)(self)                       \
	 ? (void)((self)->cqh_first = X(_, elem).cqe_next)                   \
	 : (void)(X(_, X(_, elem).cqe_prev).cqe_next = X(_, elem).cqe_next), \
	 (void *)X(_, elem).cqe_next == (void *)(self)                       \
	 ? (void)((self)->cqh_last = X(_, elem).cqe_prev)                    \
	 : (void)(X(_, X(_, elem).cqe_next).cqe_prev = X(_, elem).cqe_prev), \
	 __Q_BADPTR(X(_, elem).cqe_next),                                    \
	 __Q_BADPTR(X(_, elem).cqe_prev))
#define __X_CIRCLEQ_FOREACH(elem, self, X, _)          \
	for ((elem) = ((self)->cqh_first);                 \
	     (void const *)(elem) != (void const *)(self); \
	     (elem) = X(_, elem).cqe_next)
#define __X_CIRCLEQ_FOREACH_REVERSE(elem, self, X, _)  \
	for ((elem) = ((self)->cqh_last);                  \
	     (void const *)(elem) != (void const *)(self); \
	     (elem) = (X(_, elem).cqe_prev))
#define __X_CIRCLEQ_NEXT(elem, X, _) (X(_, elem).cqe_next)
#define __X_CIRCLEQ_PREV(elem, X, _) (X(_, elem).cqe_prev)
#define __X_CIRCLEQ_LOOP_NEXT(self, elem, X, _)                \
	((void const *)X(_, elem).cqe_next == (void const *)(self) \
	 ? (self)->cqh_first                                       \
	 : X(_, elem).cqe_next)
#define __X_CIRCLEQ_LOOP_PREV(self, elem, X, _)                \
	((void const *)X(_, elem).cqe_prev == (void const *)(self) \
	 ? (self)->cqh_last                                        \
	 : X(_, elem).cqe_prev)



/* Head-less Ring-Queue */
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#define RINGQ_ENTRY(T)                         \
	struct {                                   \
		T *rqe_next; /* [1..1] Next element */ \
		T *rqe_prev; /* [1..1] Prev element */ \
	}
/* RINGQ_INIT:          Initialize `elem' as the only element of a new ring.
 * RINGQ_NEXT:          Return the successor of `elem' within its ring.
 * RINGQ_PREV:          Return the predecessor of `elem' within its ring.
 * RINGQ_INSERT_AFTER:  Insert `elem' after `predecessor'
 * RINGQ_INSERT_BEFORE: Insert `elem' before `successor'
 * RINGQ_REMOVE:        Remove `elem' from its ring.
 * RINGQ_REPLACE:       Replace `old_elem' with `new_elem' from its ring. */
#define RINGQ_INIT(elem, key)                            __X_RINGQ_INIT(elem, __Q_KEY, key)
#define RINGQ_INIT_P(elem, getpath)                      __X_RINGQ_INIT(elem, __Q_PTH, getpath)
#define RINGQ_NEXT(elem, key)                            __X_RINGQ_NEXT(elem, __Q_KEY, key)
#define RINGQ_NEXT_P(elem, getpath)                      __X_RINGQ_NEXT(elem, __Q_PTH, getpath)
#define RINGQ_PREV(elem, key)                            __X_RINGQ_PREV(elem, __Q_KEY, key)
#define RINGQ_PREV_P(elem, getpath)                      __X_RINGQ_PREV(elem, __Q_PTH, getpath)
#define RINGQ_INSERT_AFTER(predecessor, elem, key)       __X_RINGQ_INSERT_AFTER(predecessor, elem, __Q_KEY, key)
#define RINGQ_INSERT_AFTER_P(predecessor, elem, getpath) __X_RINGQ_INSERT_AFTER(predecessor, elem, __Q_PTH, getpath)
#define RINGQ_INSERT_BEFORE(successor, elem, key)        __X_RINGQ_INSERT_BEFORE(successor, elem, __Q_KEY, key)
#define RINGQ_INSERT_BEFORE_P(successor, elem, getpath)  __X_RINGQ_INSERT_BEFORE(successor, elem, __Q_PTH, getpath)
#define RINGQ_REPLACE(old_elem, new_elem, key)           __X_RINGQ_REPLACE(old_elem, new_elem, __Q_KEY, key)
#define RINGQ_REPLACE_P(old_elem, new_elem, getpath)     __X_RINGQ_REPLACE(old_elem, new_elem, __Q_PTH, getpath)
#define RINGQ_REMOVE(elem, key)                          __X_RINGQ_REMOVE(elem, __Q_KEY, key)
#define RINGQ_REMOVE_P(elem, getpath)                    __X_RINGQ_REMOVE(elem, __Q_PTH, getpath)

#define __X_RINGQ_INIT(elem, X, _) (X(_, elem).rqe_next = X(_, elem).rqe_prev = (elem))
#define __X_RINGQ_NEXT(elem, X, _) X(_, elem).rqe_next
#define __X_RINGQ_PREV(elem, X, _) X(_, elem).rqe_prev
#define __X_RINGQ_INSERT_AFTER(predecessor, elem, X, _)                                \
	(void)(X(_, (X(_, elem).rqe_next = X(_, predecessor).rqe_next)).rqe_prev = (elem), \
	       X(_, (X(_, elem).rqe_prev = (predecessor))).rqe_next              = (elem))
#define __X_RINGQ_INSERT_BEFORE(successor, elem, X, _)                               \
	(void)(X(_, (X(_, elem).rqe_prev = X(_, successor).rqe_prev)).rqe_next = (elem), \
	       X(_, (X(_, elem).rqe_next = (successor))).rqe_prev              = (elem))
#define __X_RINGQ_REPLACE(old_elem, new_elem, X, _)                                   \
	(X(_, (X(_, new_elem).rqe_prev = X(_, old_elem).rqe_prev)).rqe_next = (new_elem), \
	 X(_, (X(_, new_elem).rqe_next = X(_, old_elem).rqe_next)).rqe_prev = (new_elem), \
	 __Q_BADPTR(X(_, old_elem).rqe_next),                                             \
	 __Q_BADPTR(X(_, old_elem).rqe_prev))
#define __X_RINGQ_REMOVE(elem, X, _)                           \
	(X(_, X(_, elem).rqe_prev).rqe_next = X(_, elem).rqe_next, \
	 X(_, X(_, elem).rqe_next).rqe_prev = X(_, elem).rqe_prev, \
	 __Q_BADPTR(X(_, elem).rqe_next),                          \
	 __Q_BADPTR(X(_, elem).rqe_prev))
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#endif /* !_SYS_QUEUE_H */
