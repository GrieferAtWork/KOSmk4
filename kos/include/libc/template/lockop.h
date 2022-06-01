/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#ifndef _KOS_LOCKOP_H
#include <kos/lockop.h>
#endif /* !_KOS_LOCKOP_H */
#include <hybrid/__atomic.h>
#include <hybrid/sched/atomic-lock.h>

#undef __LOCAL_obj
#define __LOCAL_trylock() atomic_lock_tryacquire(__lock)
#define __LOCAL_unlock()  atomic_lock_release(__lock)
static void
__intellisense_lockop_template(struct lockop_slist *__restrict __LOCAL_self,
                               struct atomic_lock *__restrict __lock
#ifdef __LOCAL_obj
                               ,
                               void *__restrict __LOCAL_obj
#endif /* __LOCAL_obj */
                               )
#endif /* __INTELLISENSE__ */
{
#ifndef __LOCAL_lo_link
#ifdef __LOCAL_obj
#define __LOCAL_lo_link olo_link
#else /* __LOCAL_obj */
#define __LOCAL_lo_link lo_link
#endif /* !__LOCAL_obj */
#endif /* !__LOCAL_lo_link */

#ifndef __LOCAL_plo_link
#ifdef __LOCAL_obj
#define __LOCAL_plo_link oplo_link
#else /* __LOCAL_obj */
#define __LOCAL_plo_link plo_link
#endif /* !__LOCAL_obj */
#endif /* !__LOCAL_plo_link */

#ifdef __LOCAL_obj
#ifdef __LOCAL_type
	Toblockop_slist(__LOCAL_type) __lops_list;
	Tobpostlockop_slist(__LOCAL_type) __post_list;
	Toblockop(__LOCAL_type) *__iter;
#else /* __LOCAL_type */
	struct oblockop_slist __lops_list;
	struct obpostlockop_slist __post_list;
	struct oblockop *__iter;
#endif /* !__LOCAL_type */
#else /* __LOCAL_obj */
	struct lockop_slist __lops_list;
	struct postlockop_slist __post_list;
	struct lockop *__iter;
#endif /* !__LOCAL_obj */
	if (!__LOCAL_trylock())
		return;
	__post_list.slh_first = __NULLPTR; /*SLIST_INIT(&__post_list);*/

again_steal_and_service_lops:
	__lops_list.slh_first = __hybrid_atomic_xch(__LOCAL_self->slh_first, __NULLPTR, __ATOMIC_SEQ_CST); /* SLIST_ATOMIC_CLEAR(__LOCAL_self) */
again_service_lops:
	__iter = __lops_list.slh_first; /* SLIST_FIRST(&__lops_list) */
	while (__iter != __NULLPTR) {
#ifdef __LOCAL_obj
#ifdef __LOCAL_type
		Toblockop(__LOCAL_type) *__next;
		Tobpostlockop(__LOCAL_type) *__later;
#else /* __LOCAL_type */
		struct oblockop *__next;
		struct obpostlockop *__later;
#endif /* !__LOCAL_type */
#else /* __LOCAL_obj */
		struct lockop *__next;
		struct postlockop *__later;
#endif /* !__LOCAL_obj */
		__next = __iter->__LOCAL_lo_link.sle_next; /* SLIST_NEXT(__iter, __LOCAL_lo_link) */
		/* Invoke the lock operation. */
#ifdef __LOCAL_obj
		__later = (*__iter->olo_func)(__iter, __LOCAL_obj);
#else /* __LOCAL_obj */
		__later = (*__iter->lo_func)(__iter);
#endif /* !__LOCAL_obj */
		/* Enqueue operations for later execution. */
		if (__later != __NULLPTR) {
			/* SLIST_INSERT(&__post_list, later, __LOCAL_plo_link) */
			__later->__LOCAL_plo_link.sle_next = __post_list.slh_first;
			__post_list.slh_first              = __later;
		}
		__iter = __next;
	}
	__LOCAL_unlock();

	/* Check for more operations. */
	__lops_list.slh_first = __hybrid_atomic_xch(__LOCAL_self->slh_first, __NULLPTR, __ATOMIC_SEQ_CST); /* SLIST_ATOMIC_CLEAR(__LOCAL_self) */
	if __unlikely(__lops_list.slh_first != __NULLPTR) { /* !SLIST_EMPTY(&__lops_list) */
		if __likely(__LOCAL_trylock())
			goto again_service_lops;

		/* re-queue all stolen lops. */
		__iter = __lops_list.slh_first;                /* SLIST_FIRST(&__lops_list) */
		while (__iter->__LOCAL_lo_link.sle_next)       /* SLIST_NEXT(__iter, __LOCAL_lo_link) */
			__iter = __iter->__LOCAL_lo_link.sle_next; /* SLIST_NEXT(__iter, __LOCAL_lo_link) */

		/* SLIST_ATOMIC_INSERT_R(__LOCAL_self, SLIST_FIRST(&__lops_list), __iter, __LOCAL_lo_link) */
		do {
			__iter->__LOCAL_lo_link.sle_next = __hybrid_atomic_load(__LOCAL_self->slh_first, __ATOMIC_ACQUIRE);
			__COMPILER_WRITE_BARRIER();
		} while (!__hybrid_atomic_cmpxch(__LOCAL_self->slh_first, __iter->__LOCAL_lo_link.sle_next,
		                                 __lops_list.slh_first, __ATOMIC_RELEASE, __ATOMIC_RELAXED));

		if __unlikely(__LOCAL_trylock())
			goto again_steal_and_service_lops;
	}

	/* Run all enqueued __post_list-operations. */
	while (__post_list.slh_first != __NULLPTR) { /* SLIST_EMPTY(&__post_list) */
#ifdef __LOCAL_obj
#ifdef __LOCAL_type
		Tobpostlockop(__LOCAL_type) *__postop;
#else /* __LOCAL_type */
		struct obpostlockop *__postop;
#endif /* !__LOCAL_type */
#else /* __LOCAL_obj */
		struct postlockop *__postop;
#endif /* !__LOCAL_obj */
		__postop              = __post_list.slh_first;               /* SLIST_FIRST(&__post_list) */
		__post_list.slh_first = __postop->__LOCAL_plo_link.sle_next; /* SLIST_REMOVE_HEAD(&__post_list, __LOCAL_plo_link) */
#ifdef __LOCAL_obj
		(*__postop->oplo_func)(__postop, __LOCAL_obj);
#else /* __LOCAL_obj */
		(*__postop->plo_func)(__postop);
#endif /* !__LOCAL_obj */
	}
}



#undef __LOCAL_lo_link
#undef __LOCAL_plo_link

#undef __LOCAL_trylock
#undef __LOCAL_unlock
#undef __LOCAL_type
#undef __LOCAL_obj
#undef __LOCAL_self
