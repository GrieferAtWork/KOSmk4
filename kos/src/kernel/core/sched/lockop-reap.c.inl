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
#ifdef __INTELLISENSE__
#include "lockop.c"
#endif /* __INTELLISENSE__ */

#include <hybrid/sync/atomic-lock.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <stddef.h>

DECL_BEGIN

#ifndef LOCAL_oblockop
#define LOCAL_oblockop 0
#endif /* !LOCAL_oblockop */

#ifndef LOCAL_name
#define LOCAL_name _lockop_reap_atomic_lock
#endif /* !LOCAL_name */

#ifndef LOCAL_attr
#define LOCAL_attr NONNULL((1, 2))
#endif /* !LOCAL_attr */

#ifndef LOCAL_args
#define LOCAL_args struct atomic_lock *__restrict lock
#endif /* !LOCAL_args */

#ifndef LOCAL_trylock
#define LOCAL_trylock() atomic_lock_tryacquire(lock)
#endif /* !LOCAL_trylock */

#ifndef LOCAL_unlock
#define LOCAL_unlock() atomic_lock_release(lock)
#endif /* !LOCAL_unlock */

#ifndef LOCAL_lockop_slist
#if LOCAL_oblockop
#define LOCAL_lockop_slist oblockop_slist
#else /* LOCAL_oblockop */
#define LOCAL_lockop_slist lockop_slist
#endif /* !LOCAL_oblockop */
#endif /* !LOCAL_lockop_slist */

#ifndef LOCAL_lockop
#if LOCAL_oblockop
#define LOCAL_lockop oblockop
#else /* LOCAL_oblockop */
#define LOCAL_lockop lockop
#endif /* !LOCAL_oblockop */
#endif /* !LOCAL_lockop */

#ifndef LOCAL_postlockop_slist
#if LOCAL_oblockop
#define LOCAL_postlockop_slist obpostlockop_slist
#ifndef __obpostlockop_slist_defined
#define __obpostlockop_slist_defined 1
SLIST_HEAD(obpostlockop_slist, obpostlockop);
#endif /* !__obpostlockop_slist_defined */
#else /* LOCAL_oblockop */
#define LOCAL_postlockop_slist postlockop_slist
#ifndef __postlockop_slist_defined
#define __postlockop_slist_defined 1
SLIST_HEAD(postlockop_slist, postlockop);
#endif /* !__postlockop_slist_defined */
#endif /* !LOCAL_oblockop */
#endif /* !LOCAL_postlockop_slist */

#ifndef LOCAL_postlockop
#if LOCAL_oblockop
#define LOCAL_postlockop obpostlockop
#else /* LOCAL_oblockop */
#define LOCAL_postlockop postlockop
#endif /* !LOCAL_oblockop */
#endif /* !LOCAL_postlockop */

FUNDEF NOBLOCK LOCAL_attr void
NOTHROW(FCALL PP_CAT2(_impl_, LOCAL_name))(struct LOCAL_lockop_slist *__restrict self,
                                           LOCAL_args
#if LOCAL_oblockop
                                           ,
                                           void *obj
#endif /* LOCAL_oblockop */
                                           )
	ASMNAME(PP_STR(LOCAL_name));

PUBLIC NOBLOCK LOCAL_attr void
NOTHROW(FCALL PP_CAT2(_impl_, LOCAL_name))(struct LOCAL_lockop_slist *__restrict self,
                                           LOCAL_args
#if LOCAL_oblockop
                                           ,
                                           void *obj
#endif /* LOCAL_oblockop */
                                           ) {
	struct LOCAL_lockop_slist lops;
	struct LOCAL_postlockop_slist post;
	struct LOCAL_lockop *iter;
	if (!LOCAL_trylock())
		return;
	SLIST_INIT(&post);
again_steal_and_service_lops:
	lops.slh_first = SLIST_ATOMIC_CLEAR(self);
again_service_lops:
	iter = SLIST_FIRST(&lops);
	while (iter != NULL) {
		struct LOCAL_lockop *next;
		struct LOCAL_postlockop *later;
		next = SLIST_NEXT(iter, lo_link);
		/* Invoke the lock operation. */
#if LOCAL_oblockop
		later = (*iter->lo_func)(iter, obj);
#else /* LOCAL_oblockop */
		later = (*iter->lo_func)(iter);
#endif /* !LOCAL_oblockop */
		/* Enqueue operations for later execution. */
		if (later != NULL)
			SLIST_INSERT(&post, later, plo_link);
		iter = next;
	}
	LOCAL_unlock();

	/* Check for more operations. */
	lops.slh_first = SLIST_ATOMIC_CLEAR(self);
	if unlikely(!SLIST_EMPTY(&lops)) {
		if likely(LOCAL_trylock())
			goto again_service_lops;

		/* re-queue all stolen lops. */
		iter = SLIST_FIRST(&lops);
		while (SLIST_NEXT(iter, lo_link))
			iter = SLIST_NEXT(iter, lo_link);
		SLIST_ATOMIC_INSERT_R(self, SLIST_FIRST(&lops), iter, lo_link);
		if unlikely(LOCAL_trylock())
			goto again_steal_and_service_lops;
	}

	/* Run all enqueued post-operations. */
	while (!SLIST_EMPTY(&post)) {
		struct LOCAL_postlockop *op;
		op = SLIST_FIRST(&post);
		SLIST_REMOVE_HEAD(&post, plo_link);
#if LOCAL_oblockop
		(*op->plo_func)(op, obj);
#else /* LOCAL_oblockop */
		(*op->plo_func)(op);
#endif /* !LOCAL_oblockop */
	}
}

#undef LOCAL_oblockop
#undef LOCAL_name
#undef LOCAL_attr
#undef LOCAL_args
#undef LOCAL_trylock
#undef LOCAL_unlock
#undef LOCAL_lockop_slist
#undef LOCAL_lockop
#undef LOCAL_postlockop_slist
#undef LOCAL_postlockop

DECL_END
