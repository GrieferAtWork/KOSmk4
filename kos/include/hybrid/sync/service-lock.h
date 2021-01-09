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

/* Helper functions for automatically generating lock wrapper functions for invoking
 * some service function whenever a lock is acquired (either for reading or writing).
 * This is useful in cases where cleanup operations would normally require a blocking
 * lock to be held, however using service-locks, this can be made non-blocking by first
 * trying to acquire the lock during finalization, and if doing so fails, using atomic
 * operations to build a linked list of objects that are pending destruction, and are
 * SERVICEd whenever the thread that was holding the lock which prevented the operation
 * from being non-blocking releases said lock. Additionally, to deal with some corner
 * cases where doing so improves performance, servicing is also checked when a lock is
 * acquired.
 *
 * >> struct foo;
 * >> PRIVATE struct atomic_rwlock foolock = ATOMIC_RWLOCK_INIT;
 * >> PRIVATE WEAK struct foo *dead_foo = NULL;
 * >>
 * >> // Perform finalization that can be done without `foolock'
 * >> PRIVATE void finalize_foo_without_foolock(struct foo *self);
 * >>
 * >> // Perform finalization that can only be done with `foolock' (write-mode)
 * >> PRIVATE void finalize_foo_with_foolock(struct foo *self);
 * >>
 * >> PRIVATE void service_dead_foo_objects(void) {
 * >>     struct foo *chain, *next;
 * >>     chain = ATOMIC_XCH(dead_foo, NULL);
 * >>     while (chain) {
 * >>         next = chain->NEXT_FIELD;
 * >>         finalize_foo_with_foolock(chain);
 * >>         chain = next;
 * >>     }
 * >> }
 * >>
 * >> #define SERLOCK(name)         foolock_##name
 * >> #define SERLOCK_LOCK          &foolock
 * >> #define SERLOCK_SERVICE()     service_dead_foo_objects()
 * >> #define SERLOCK_MUSTSERVICE() (ATOMIC_READ(dead_foo) != NULL)
 * >> #include <hybrid/sync/service-lock.h>
 * >>
 * >> // Finalize a foo-object without blocking (even though some parts
 * >> // of the finalization process may potentially require blocking)
 * >> PRIVATE NOBLOCK void finalize_foo(struct foo *self) {
 * >>     finalize_foo_without_foolock(self);
 * >>     if (foolock_trywrite()) {
 * >>         finalize_foo_with_foolock(self);
 * >>         foolock_endwrite();
 * >>     } else {
 * >>         struct foo *next;
 * >>         do {
 * >>             next = ATOMIC_READ(dead_foo);
 * >>             ATOMIC_WRITE(self->NEXT_FIELD, next);
 * >>         } while (!ATOMIC_CMPXCH_WEAK(dead_foo, next, self));
 * >>         // In case the lock became available since our attempt at `foolock_trywrite()'
 * >>         // above, try to service dead objects once again, thus ensuring that the chain
 * >>         // of dead foo-object is always empty when no thread is holding `dead_foo'
 * >>         foolock_service();
 * >>     }
 * >> }
 *
 * Assumptions that may be made by this implementation:
 *   - Any time that `SERLOCK_LOCK_READ()' or `SERLOCK_LOCK_WRITE()' would block,
 *     the thread that is currently holding the lock will always (try to) service
 *     dead objects using `SERLOCK_SERVICE()' when the lock is released.
 *     In the case of a read-lock, the holding thread will try to upgrade the lock
 *     and service dead objects if doing so succeeds.
 *   - Whenever no thread is holding a read- or write-lock, it may be assumed that
 *     the chain of dead objects is either empty, or about to become empty.
 *
 */


/* TODO: Update all of the cases where kernel-space already uses a mechanism
 *       such as this one, such that it uses this exact mechanism for providing
 *       the necessary implementations! */

#include <__stdinc.h>

#include <hybrid/sched/__yield.h>

/* Setup API configuration. */
#ifndef SERLOCK
#error "Must `#define SERLOCK(name) mylock_##name' before #including this file"
#endif /* !SERLOCK */
#ifndef SERLOCK_SERVICE
#error "Must `#define SERLOCK_SERVICE() <expr>' before #including this file"
#endif /* !SERLOCK_SERVICE */
#ifndef SERLOCK_MUSTSERVICE
#error "Must `#define SERLOCK_MUSTSERVICE() <expr>' before #including this file"
#endif /* !SERLOCK_MUSTSERVICE */
#ifndef SERLOCK_CC
#if defined(__ATTR_FASTCALL) && !defined(__NO_ATTR_FASTCALL)
#define SERLOCK_CC __ATTR_FASTCALL
#else /* __ATTR_FASTCALL */
#define SERLOCK_CC /* nothing */
#endif /* !__ATTR_FASTCALL */
#endif /* !SERLOCK_CC */
#ifndef SERLOCK_DECL
#define SERLOCK_DECL __LOCAL
#endif /* !SERLOCK_DECL */
#ifndef SERLOCK_SELF
#define SERLOCK_SELF      /* nothing */  /* (`self') */
#define SERLOCK_SELFPARAM void           /* (`struct foo *self') */
#endif /* !SERLOCK_SELF */
#ifdef SERLOCK_LOCK
#define SERLOCK_LOCK_TRYREAD()    sync_tryread(SERLOCK_LOCK)
#define SERLOCK_LOCK_READ()       sync_read(SERLOCK_LOCK)
#define SERLOCK_LOCK_ENDREAD()    sync_endread(SERLOCK_LOCK)
#define SERLOCK_LOCK_TRYWRITE()   sync_trywrite(SERLOCK_LOCK)
#define SERLOCK_LOCK_WRITE()      sync_write(SERLOCK_LOCK)
#define SERLOCK_LOCK_ENDWRITE()   sync_endwrite(SERLOCK_LOCK)
#define SERLOCK_LOCK_TRYUPGRADE() sync_tryupgrade(SERLOCK_LOCK)
#define SERLOCK_LOCK_UPGRADE()    sync_upgrade(SERLOCK_LOCK)
#define SERLOCK_LOCK_DOWNGRADE()  sync_downgrade(SERLOCK_LOCK)
#ifndef __NO_hybrid_yield_nx
#define SERLOCK_LOCK_READ_NX()    sync_read_nx(SERLOCK_LOCK)
#define SERLOCK_LOCK_WRITE_NX()   sync_write_nx(SERLOCK_LOCK)
#define SERLOCK_LOCK_UPGRADE_NX() sync_upgrade_nx(SERLOCK_LOCK)
#endif /* __NO_hybrid_yield_nx */
#endif /* !SERLOCK_LOCK */
#ifndef SERLOCK_LOCK_TRYREAD
#error "Must `#define SERLOCK_LOCK_TRYREAD()' before #including this file"
#endif /* !SERLOCK_LOCK_TRYREAD */
#ifndef SERLOCK_LOCK_TRYWRITE
#error "Must `#define SERLOCK_LOCK_TRYWRITE()' before #including this file"
#endif /* !SERLOCK_LOCK_TRYWRITE */
#ifndef SERLOCK_LOCK_ENDREAD
#error "Must `#define SERLOCK_LOCK_ENDREAD()' before #including this file"
#endif /* !SERLOCK_LOCK_ENDREAD */
#ifndef SERLOCK_LOCK_ENDWRITE
#error "Must `#define SERLOCK_LOCK_ENDWRITE()' before #including this file"
#endif /* !SERLOCK_LOCK_ENDWRITE */
#ifndef SERLOCK_LOCK_DOWNGRADE
#error "Must `#define SERLOCK_LOCK_DOWNGRADE()' before #including this file"
#endif /* !SERLOCK_LOCK_DOWNGRADE */
#ifndef SERLOCK_LOCK_TRYUPGRADE
#error "Must `#define SERLOCK_LOCK_TRYUPGRADE()' before #including this file"
#endif /* !SERLOCK_LOCK_TRYUPGRADE */
#ifndef SERLOCK_LOCK_WRITE
#define SERLOCK_LOCK_WRITE()             \
	do {                                 \
		while (!SERLOCK_LOCK_TRYWRITE()) \
			__hybrid_yield();            \
	} __WHILE0
#endif /* !SERLOCK_LOCK_WRITE */
#ifndef SERLOCK_LOCK_READ
#define SERLOCK_LOCK_READ()             \
	do {                                \
		while (!SERLOCK_LOCK_TRYREAD()) \
			__hybrid_yield();           \
	} __WHILE0
#endif /* !SERLOCK_LOCK_READ */

__DECL_BEGIN

/* Downgrade a write-lock to read-lock. */
SERLOCK_DECL __ATTR_WUNUSED void
__NOTHROW_NCX(SERLOCK_CC SERLOCK(downgrade))(SERLOCK_SELFPARAM) {
	if __unlikely(SERLOCK_MUSTSERVICE()) {
__again_service:
		SERLOCK_SERVICE();
	}
	SERLOCK_LOCK_DOWNGRADE();
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		if (SERLOCK_LOCK_TRYUPGRADE())
			goto __again_service;
	}
}

/* Try to upgrade a read-lock into a write-lock
 * @return: true:  Lock successfully upgraded
 * @return: false: The caller is still holding a read-lock */
SERLOCK_DECL __ATTR_WUNUSED __BOOL
__NOTHROW_NCX(SERLOCK_CC SERLOCK(tryupgrade))(SERLOCK_SELFPARAM) {
	if (!SERLOCK_LOCK_TRYUPGRADE())
		return 0;
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		SERLOCK_SERVICE();
	}
	return 1;
}

/* Try to acquire a read-lock
 * @return: true:  Lock successfully acquired
 * @return: false: Failed to acquire the lock */
SERLOCK_DECL __ATTR_WUNUSED __BOOL
__NOTHROW_NCX(SERLOCK_CC SERLOCK(tryread))(SERLOCK_SELFPARAM) {
	if (!SERLOCK_LOCK_TRYREAD())
		return 0;
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		if (SERLOCK_LOCK_TRYUPGRADE()) {
			SERLOCK_SERVICE();
			SERLOCK(downgrade)(SERLOCK_SELF);
		}
	}
	return 1;
}

/* Try to acquire a write-lock
 * @return: true:  Lock successfully acquired
 * @return: false: Failed to acquire the lock */
SERLOCK_DECL __ATTR_WUNUSED __BOOL
__NOTHROW_NCX(SERLOCK_CC SERLOCK(trywrite))(SERLOCK_SELFPARAM) {
	if (!SERLOCK_LOCK_TRYWRITE())
		return 0;
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		SERLOCK_SERVICE();
	}
	return 1;
}

/* Release a read-lock */
SERLOCK_DECL void
__NOTHROW_NCX(SERLOCK_CC SERLOCK(endread))(SERLOCK_SELFPARAM) {
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		if (SERLOCK_LOCK_TRYUPGRADE()) {
__again_service:
			SERLOCK_SERVICE();
			SERLOCK_LOCK_ENDWRITE();
			goto __check_service;
		}
	}
	SERLOCK_LOCK_ENDREAD();
__check_service:
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		if (SERLOCK_LOCK_TRYWRITE())
			goto __again_service;
	}
}

/* Release a write-lock */
SERLOCK_DECL void
__NOTHROW_NCX(SERLOCK_CC SERLOCK(endwrite))(SERLOCK_SELFPARAM) {
__again:
	/* Technically, we could check for service here, and doing so would improve
	 * performance in cases where in the majority of times there is something
	 * that needs to be serviced. However, in general, the most common case is
	 * that nothing needs to be serviced, and we still always have to check for
	 * service after having released the lock (in order to ensure interlocked
	 * semantics in regards to there never being objects left in the service-
	 * queue while no lock is held, and no thread is about to service them).
	 * So with this in mind, we _only_ service after releasing the lock. */
	SERLOCK_LOCK_ENDWRITE();
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		if (SERLOCK_LOCK_TRYWRITE()) {
			SERLOCK_SERVICE();
			goto __again;
		}
	}
}


/* Acquire a read-lock */
SERLOCK_DECL void
(SERLOCK_CC SERLOCK(read))(SERLOCK_SELFPARAM) {
	SERLOCK_LOCK_READ();
	if __unlikely(SERLOCK_MUSTSERVICE()) {
#ifdef SERLOCK_LOCK_UPGRADE
		if (SERLOCK_LOCK_UPGRADE() || SERLOCK_MUSTSERVICE())
#else /* SERLOCK_LOCK_UPGRADE */
		SERLOCK_LOCK_ENDREAD();
		SERLOCK_LOCK_WRITE();
		if (SERLOCK_MUSTSERVICE())
#endif /* !SERLOCK_LOCK_UPGRADE */
		{
			SERLOCK_SERVICE();
		}
		SERLOCK_LOCK_DOWNGRADE();
	}
}

/* Acquire a write-lock */
SERLOCK_DECL void
(SERLOCK_CC SERLOCK(write))(SERLOCK_SELFPARAM) {
	SERLOCK_LOCK_WRITE();
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		SERLOCK_SERVICE();
	}
}

/* Try to upgrade a read-lock into a write-lock
 * NOTE: When this function returns by throwing an exception, the
 *       previously acquired read-lock has already been released!
 * @return: true:  The lock was upgraded without having to release the read-lock
 * @return: false: The read-lock had to be released during the upgrade process. */
SERLOCK_DECL __ATTR_WUNUSED __BOOL
(SERLOCK_CC SERLOCK(upgrade))(SERLOCK_SELFPARAM) {
	__BOOL __result;
	__result = SERLOCK_LOCK_UPGRADE();
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		SERLOCK_SERVICE();
	}
	return __result;
}

#ifdef SERLOCK_LOCK_READ_NX
/* Acquire a read-lock while blocking, but without causing an `E_WOULDBLOCK' exception.
 * @return: true:  The lock was acquired successfully.
 * @return: false: An `E_WOULDBLOCK' exception would have been thrown. */
SERLOCK_DECL __ATTR_WUNUSED __BOOL
__NOTHROW(SERLOCK_CC SERLOCK(read_nx))(SERLOCK_SELFPARAM) {
	if (!SERLOCK_LOCK_READ_NX())
		return 0;
	if __unlikely(SERLOCK_MUSTSERVICE()) {
#ifdef SERLOCK_LOCK_UPGRADE_NX
		unsigned int __error;
		__error = SERLOCK_LOCK_UPGRADE_NX();
		if (__error == 0)
			return 0; /* Read-lock was lost and could not be re-acquired */
		if (__error == 1 || SERLOCK_MUSTSERVICE())
#else /* SERLOCK_LOCK_UPGRADE */
		SERLOCK_LOCK_ENDREAD();
		if (!SERLOCK_LOCK_WRITE_NX())
			return 0;
		if (SERLOCK_MUSTSERVICE())
#endif /* !SERLOCK_LOCK_UPGRADE */
		{
			SERLOCK_SERVICE();
		}
		SERLOCK_LOCK_DOWNGRADE();
	}
	return 1;
}
#endif /* SERLOCK_LOCK_READ_NX */

#ifdef SERLOCK_LOCK_WRITE_NX
/* Acquire a write-lock while blocking, but without causing an `E_WOULDBLOCK' exception.
 * @return: true:  The lock was acquired successfully.
 * @return: false: An `E_WOULDBLOCK' exception would have been thrown. */
SERLOCK_DECL __ATTR_WUNUSED __BOOL
__NOTHROW(SERLOCK_CC SERLOCK(write_nx))(SERLOCK_SELFPARAM) {
	if (!SERLOCK_LOCK_WRITE_NX())
		return 0;
	if __unlikely(SERLOCK_MUSTSERVICE()) {
		SERLOCK_SERVICE();
	}
	return 1;
}
#endif /* SERLOCK_LOCK_WRITE_NX */

#ifdef SERLOCK_LOCK_UPGRADE_NX
/* Upgrade a read-lock into a write-lock while blocking,
 * but without causing an `E_WOULDBLOCK' exception.
 * NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,
 *       no lock may have been held temporarily, meaning that the caller should
 *       re-load local copies of affected resources.
 * @return: 0 : A previously held read-lock was lost and could not be re-acquired.
 * @return: 1 : Successfully upgraded the read-only to a write-lock.
 * @return: 2 : Successfully upgraded the read-only to a write-lock,
 *              but at one point, no lock at all was being held. */
SERLOCK_DECL __ATTR_WUNUSED unsigned int
__NOTHROW(SERLOCK_CC SERLOCK(upgrade_nx))(SERLOCK_SELFPARAM) {
	unsigned int __res;
	__res = SERLOCK_LOCK_UPGRADE_NX();
	if (__res != 0) {
		if __unlikely(SERLOCK_MUSTSERVICE()) {
			SERLOCK_SERVICE();
		}
	}
	return __res;
}
#endif /* SERLOCK_LOCK_UPGRADE_NX */



/* Try to service pending tasks under the assumption that
 * at one point the caller either directly, or indirectly
 * caused a new service-request to be scheduled.
 * @return: true:  At least one task was serviced.
 * @return: false: Nothing had to be serviced. */
SERLOCK_DECL __BOOL
__NOTHROW(SERLOCK_CC SERLOCK(service))(SERLOCK_SELFPARAM) {
	__BOOL __res = 0;
	if __unlikely(SERLOCK_LOCK_TRYWRITE()) {
		if __likely(SERLOCK_MUSTSERVICE()) {
			SERLOCK_SERVICE();
		}
	}
	return __res;
}


__DECL_END

#undef SERLOCK_LOCK
#undef SERLOCK_LOCK_TRYREAD
#undef SERLOCK_LOCK_READ
#undef SERLOCK_LOCK_READ_NX
#undef SERLOCK_LOCK_ENDREAD
#undef SERLOCK_LOCK_TRYWRITE
#undef SERLOCK_LOCK_WRITE
#undef SERLOCK_LOCK_WRITE_NX
#undef SERLOCK_LOCK_ENDWRITE
#undef SERLOCK_LOCK_END
#undef SERLOCK_LOCK_TRYUPGRADE
#undef SERLOCK_LOCK_UPGRADE
#undef SERLOCK_LOCK_UPGRADE_NX
#undef SERLOCK_LOCK_DOWNGRADE
#undef SERLOCK_MUSTSERVICE
#undef SERLOCK_SERVICE
#undef SERLOCK_SELFPARAM
#undef SERLOCK_SELF
#undef SERLOCK_CC
#undef SERLOCK
