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
#ifndef GUARD_KERNEL_SRC_SCHED_RWLOCK_C
#define GUARD_KERNEL_SRC_SCHED_RWLOCK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/panic.h> /* kernel_poisoned() */
#include <kernel/printk.h>
#include <kernel/selftest.h> /* DEFINE_TEST */
#include <kernel/types.h>
#include <sched/pertask.h>
#include <sched/rpc.h>
#include <sched/rwlock-intern.h>
#include <sched/rwlock.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

#define RWLOCK_STATE  __RWLOCK_STATE
#define RWLOCK_MODE   __RWLOCK_MODE
#define RWLOCK_IND    __RWLOCK_IND
#define RWLOCK_INCIND __RWLOCK_INCIND
#define RWLOCK_DECIND __RWLOCK_DECIND


#ifndef NDEBUG
/* Because R/W locks need to be working (and therefor  initialized)
 * while handling an assertion failure, fixup a missing init before
 * triggering the fault. */
#define ASSERT_VECTOR_INITIALIZED(locks)      \
	do {                                      \
		if likely((locks)->rls_vec)           \
			break;                            \
		(locks)->rls_vec = (locks)->rls_sbuf; \
	} while __untraced(__assertion_check(#locks "->rls_vec != NULL"))
#else /* !NDEBUG */
#define ASSERT_VECTOR_INITIALIZED(locks) (void)0
#endif /* NDEBUG */



#if !defined(NDEBUG) && 0
#define RWLOCK_TRACE(...) (printk(KERN_TRACE __VA_ARGS__))
#else /* !NDEBUG */
#define RWLOCK_TRACE(...) (void)0
#endif /* NDEBUG */
#define RWLOCK_TRACE_F(name)                             \
	RWLOCK_TRACE("%s(%p) (task:%p,pc:%p)\n", name, self, \
	             THIS_TASK, __builtin_return_address(0))
#define RWLOCK_TRACE_F2(name, p2)                               \
	RWLOCK_TRACE("%s(%p,%p) (task:%p,pc:%p)\n", name, self, p2, \
	             THIS_TASK, __builtin_return_address(0))


PUBLIC ATTR_PERTASK struct read_locks this_read_locks = {
	.rls_sbuf = { },
	.rls_use  = 0,
	.rls_cnt  = 0,
	.rls_msk  = CONFIG_TASK_STATIC_READLOCKS - 1,
	.rls_vec  = NULL /* Set in `readlocks_init()' */
};

DEFINE_PERTASK_INIT(pertask_readlocks_init);
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_readlocks_init)(struct task *__restrict thread) {
	struct read_locks *locks;
	locks          = &FORTASK(thread, this_read_locks);
	locks->rls_vec = locks->rls_sbuf;
}

INTDEF struct task pertask_template ASMNAME("__kernel_pertask_start");
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_readlocks_reinit)(struct task *__restrict thread) {
	/* Restore  read-locks from the per-task initialization template.
	 * The `pertask_readlocks_init()' initialization function expects
	 * its contents as the initial state. */
	memcpy(&FORTASK(thread, this_read_locks),
	       &FORTASK(&pertask_template, this_read_locks),
	       sizeof(this_read_locks));
	/* The the tast-level init. */
	pertask_readlocks_init(thread);
}


DEFINE_PERTASK_FINI(pertask_readlocks_fini);
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pertask_readlocks_fini)(struct task *__restrict thread) {
	struct read_locks *locks;
	locks = &FORTASK(thread, this_read_locks);
	ASSERT_VECTOR_INITIALIZED(locks);
	assertf(locks->rls_use == 0,
	        "Thread %p died with read locks still held\n"
	        "locks->rls_use = %" PRIuSIZ " (rls_cnt = %" PRIuSIZ ")\n"
	        "%$I[hex]",
	        thread,
	        locks->rls_use, locks->rls_cnt,
	        (locks->rls_msk + 1) * sizeof(struct read_lock),
	        locks->rls_vec);
	if (locks->rls_vec != locks->rls_sbuf)
		kfree(locks->rls_vec);
}

/* Find an existing read-lock descriptor for `lock', or return NULL. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct read_lock *
NOTHROW(FCALL rwlock_find_readlock)(struct rwlock const *__restrict lock) {
	uintptr_t i, perturb;
	struct read_locks *locks;
	struct read_lock *lockdesc;
	locks = &PERTASK(this_read_locks);
	ASSERT_VECTOR_INITIALIZED(locks);
	assert(locks->rls_use <= locks->rls_cnt);
	assert(locks->rls_cnt <= locks->rls_msk);
	perturb = i = RWLOCK_HASH(lock) & locks->rls_msk;
	for (;; i = ((i << 2) + i + perturb + 1), perturb >>= 5) {
		lockdesc = &locks->rls_vec[i & locks->rls_msk];
		if (lockdesc->rl_rwlock == lock)
			return lockdesc; /* Existing descriptor. */
		if (!lockdesc->rl_rwlock)
			break;
	}
	return NULL;
}

PRIVATE NONNULL((1, 3)) void
NOTHROW(FCALL read_lock_rehash)(struct read_lock *__restrict new_vector, size_t new_mask,
                                struct read_lock *__restrict old_vector, size_t old_mask) {
	size_t i;
	for (i = 0; i <= old_mask; ++i) {
		size_t perturb, j;
		struct rwlock *heldlock = old_vector[i].rl_rwlock;
		if (!heldlock || heldlock == READLOCK_DUMMYLOCK)
			continue;
		perturb = j = RWLOCK_HASH(heldlock) & new_mask;
		for (;; j = ((j << 2) + j + perturb + 1), perturb >>= 5) {
			struct read_lock *lockdesc;
			lockdesc = &new_vector[j & new_mask];
			if (lockdesc->rl_rwlock)
				continue;
			memcpy(lockdesc, &old_vector[i], sizeof(struct read_lock));
			break;
		}
	}
}

/* Rehash an empty read-locks hashmap. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rehash_empty)(struct read_locks *__restrict locks) {
	assert(locks->rls_use == 0);
	assert(locks->rls_cnt != 0);
	/* Clear the static buffer. */
	memset(locks->rls_sbuf, 0, sizeof(locks->rls_sbuf));
	/* Try to switch back to the static hashmap. */
	locks->rls_cnt = 0;
	if unlikely(locks->rls_vec != locks->rls_sbuf) {
		struct read_lock *heapmap;
		heapmap        = locks->rls_vec;
		locks->rls_vec = locks->rls_sbuf;
		locks->rls_msk = CONFIG_TASK_STATIC_READLOCKS - 1;
		kfree(heapmap);
	}
	assert(locks->rls_msk == CONFIG_TASK_STATIC_READLOCKS - 1);
}

/* Return a read-lock descriptor for `lock', or allocate a new one. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct read_lock *FCALL
rwlock_get_readlock(struct rwlock *__restrict lock) THROWS(E_BADALLOC) {
	uintptr_t j, perturb;
	struct read_locks *locks;
	struct read_lock *lockdesc;
	struct read_lock *result;
	locks = &PERTASK(this_read_locks);
again:
	ASSERT_VECTOR_INITIALIZED(locks);
	assert(locks->rls_use <= locks->rls_cnt);
	assert(locks->rls_cnt <= locks->rls_msk);
	result  = NULL;
	perturb = j = RWLOCK_HASH(lock) & locks->rls_msk;
	for (;; j = ((j << 2) + j + perturb + 1), perturb >>= 5) {
		lockdesc = &locks->rls_vec[j & locks->rls_msk];
		if (lockdesc->rl_rwlock == lock) {
			assert(locks->rls_use != 0);
			assert(!lockdesc->rl_recursion || lock->rw_mode != RWLOCK_MODE_FWRITING);
			assert(!lockdesc->rl_recursion || lock->rw_scnt != 0);
			return lockdesc; /* Existing descriptor. */
		}
		if (!lockdesc->rl_rwlock) {
			/* End of chain (if no dummy was found, use this entry). */
			if (!result) {
				if (locks->rls_cnt == locks->rls_msk) {
					struct read_lock *old_vector;
					struct read_lock *new_vector;
					size_t new_mask;
					if (!locks->rls_use) {
						/* Special case: When no locks  are actually  in use,  then
						 *               we can simply re-hash in-place by clearing
						 *               the memory of the hash-vector.
						 * Also: Try to revert to the original, static hash-vector. */
						rehash_empty(locks);
						goto again;
					}
					/* Must re-hash the readlock hash-vector. */
					new_mask = locks->rls_msk;
					/* Only increase the mask if all slots are actually in use.
					 * Otherwise, it's sufficient to rehash to a mask equal  to
					 * our current size, */
					if (locks->rls_use == locks->rls_cnt)
						new_mask = (new_mask << 1) | 1;

					/* Check for special case: Try to re-use the static vector. */
					old_vector = locks->rls_vec;
					if (new_mask <= (CONFIG_TASK_STATIC_READLOCKS - 1) &&
					    old_vector != locks->rls_sbuf) {
						new_mask   = CONFIG_TASK_STATIC_READLOCKS - 1;
						new_vector = (struct read_lock *)memset(locks->rls_sbuf, 0, sizeof(locks->rls_sbuf));
					} else {
						/* NOTE: Memory must be locked in-core, because otherwise the following loop can happen:
						 *   #1: #PF
						 *   #2: EXCEPTION
						 *   #3: EXCEPTION: tryread(VM) (To find the associated FDE)
						 *   #4: FIND_READLOCK(VM)
						 *   #5: #PF
						 */
						new_vector = (struct read_lock *)kmalloc((new_mask + 1) *
						                                         sizeof(struct read_lock),
						                                         GFP_CALLOC | GFP_LOCKED |
						                                         GFP_PREFLT);
					}
					read_lock_rehash(new_vector, new_mask,
					                 old_vector, locks->rls_msk);
					locks->rls_cnt = locks->rls_use; /* Dismiss dummy entries. */
					locks->rls_vec = new_vector;
					locks->rls_msk = new_mask;
					if (old_vector != locks->rls_sbuf)
						kfree(old_vector);
					goto again;
				}
				++locks->rls_cnt;
				result = lockdesc;
			}
			break;
		}
		if (lockdesc->rl_rwlock == READLOCK_DUMMYLOCK) {
			/* Re-use dummy locks. */
			if (!result)
				result = lockdesc;
		}
	}
	/* New descriptor. */
	assert(result->rl_rwlock == NULL ||
	       result->rl_rwlock == READLOCK_DUMMYLOCK);
	result->rl_recursion = 0;
	result->rl_rwlock    = lock;
	++locks->rls_use;
	return result;
}


/* Return a read-lock descriptor for `lock', or allocate a new one. */
PRIVATE WUNUSED NONNULL((1)) struct read_lock *
NOTHROW(FCALL rwlock_get_readlock_nx)(struct rwlock *__restrict lock) {
	uintptr_t j, perturb;
	struct read_locks *locks;
	struct read_lock *lockdesc;
	struct read_lock *result;
	locks = &PERTASK(this_read_locks);
again:
	ASSERT_VECTOR_INITIALIZED(locks);
	assert(locks->rls_use <= locks->rls_cnt);
	assert(locks->rls_cnt <= locks->rls_msk);
	result  = NULL;
	perturb = j = RWLOCK_HASH(lock) & locks->rls_msk;
	for (;; j = ((j << 2) + j + perturb + 1), perturb >>= 5) {
		lockdesc = &locks->rls_vec[j & locks->rls_msk];
		if (lockdesc->rl_rwlock == lock)
			return lockdesc; /* Existing descriptor. */
		if (!lockdesc->rl_rwlock) {
			/* End of chain (if no dummy was found, use this entry). */
			if (!result) {
				if (locks->rls_cnt == locks->rls_msk) {
					struct read_lock *old_vector;
					struct read_lock *new_vector;
					size_t new_mask;
					if (!locks->rls_use) {
						/* Special case: When no locks  are actually  in use,  then
						 *               we can simply re-hash in-place by clearing
						 *               the memory of the hash-vector.
						 * Also: Try to revert to the original, static hash-vector. */
						rehash_empty(locks);
						goto again;
					}
					/* Must re-hash the readlock hash-vector. */
					new_mask = locks->rls_msk;
					/* Only increase the mask if all slots are actually in use.
					 * Otherwise, it's sufficient to rehash to a mask equal  to
					 * our current size, */
					if (locks->rls_use == locks->rls_cnt)
						new_mask = (new_mask << 1) | 1;
					old_vector = locks->rls_vec;
					if (new_mask <= (CONFIG_TASK_STATIC_READLOCKS - 1) &&
					    old_vector != locks->rls_sbuf) {
						new_mask   = CONFIG_TASK_STATIC_READLOCKS - 1;
						new_vector = (struct read_lock *)memset(locks->rls_sbuf, 0, sizeof(locks->rls_sbuf));
					} else {
						/* NOTE: Memory must be locked in-core, because otherwise the following loop can happen:
						 *   #1: #PF
						 *   #2: EXCEPTION
						 *   #3: EXCEPTION: tryread(VM) (To find the associated FDE)
						 *   #4: FIND_READLOCK(VM)
						 *   #5: #PF
						 */
						new_vector = (struct read_lock *)kmalloc_nx((new_mask + 1) *
						                                            sizeof(struct read_lock),
						                                            GFP_CALLOC | GFP_LOCKED |
						                                            GFP_PREFLT);
					}
					if unlikely(!new_vector)
						return NULL;
					old_vector = locks->rls_vec;
					read_lock_rehash(new_vector, new_mask,
					                 old_vector, locks->rls_msk);
					locks->rls_cnt = locks->rls_use; /* Dismiss dummy entries. */
					locks->rls_vec = new_vector;
					locks->rls_msk = new_mask;
					if (old_vector != locks->rls_sbuf)
						kfree(old_vector);
					goto again;
				}
				++locks->rls_cnt;
				result = lockdesc;
			}
			break;
		}
		if (lockdesc->rl_rwlock == READLOCK_DUMMYLOCK) {
			/* Re-use dummy locks. */
			if (!result)
				result = lockdesc;
		}
	}
	/* New descriptor. */
	assert(result->rl_rwlock == NULL ||
	       result->rl_rwlock == READLOCK_DUMMYLOCK);
	result->rl_recursion = 0;
	result->rl_rwlock    = lock;
	++locks->rls_use;
	return result;
}


/* Delete the given rlock. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rwlock_delete_readlock)(struct read_lock *__restrict rlock) {
	assert(PERTASK_TEST(this_read_locks.rls_use));
	assert(PERTASK_TEST(this_read_locks.rls_cnt));
	assert(rlock >= PERTASK_GET(this_read_locks.rls_vec));
	assert(rlock <= PERTASK_GET(this_read_locks.rls_vec) + PERTASK_GET(this_read_locks.rls_msk));
	rlock->rl_rwlock = READLOCK_DUMMYLOCK;
	PERTASK_DEC(this_read_locks.rls_use);
}



PUBLIC ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_reading)(struct rwlock const *__restrict self) {
	struct read_lock *lock;
	if (self->rw_scnt == 0)
		return false;
	if (self->rw_mode == RWLOCK_MODE_FWRITING)
		return self->rw_xowner == THIS_TASK;
	lock = rwlock_find_readlock(self);
	assert(!lock || lock->rl_recursion != 0);
	return lock != NULL;
}

PUBLIC ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_writing)(struct rwlock const *__restrict self) {
	return (self->rw_mode == RWLOCK_MODE_FWRITING &&
	        self->rw_xowner == THIS_TASK);
}

PUBLIC ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL rwlock_reading_r)(struct rwlock const *__restrict self) {
	struct read_lock *lock;
	if (self->rw_scnt == 0)
		return 0;
	if (self->rw_mode == RWLOCK_MODE_FWRITING)
		return self->rw_xowner == THIS_TASK ? (uintptr_t)self->rw_xind : 0;
	lock = rwlock_find_readlock(self);
	assert(!lock || lock->rl_recursion != 0);
	return lock ? lock->rl_recursion : 0;
}

/* Return the total number of hold read-locks (or 0 if this is not tracked by the implementation) */
PUBLIC ATTR_PURE WUNUSED uintptr_t
NOTHROW(FCALL rwlock_reading_any)(void) {
	size_t i, result = 0;
	struct read_locks *locks;
	locks = &PERTASK(this_read_locks);
	ASSERT_VECTOR_INITIALIZED(locks);
	if (!locks->rls_use)
		return 0;
	for (i = 0; i <= locks->rls_msk; ++i) {
		struct read_lock *l;
		l = &locks->rls_vec[i];
		if (l->rl_rwlock == NULL)
			continue;
		if (l->rl_rwlock == READLOCK_DUMMYLOCK)
			continue;
		result += l->rl_recursion;
	}
	return result;
}


PUBLIC ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL rwlock_writing_r)(struct rwlock const *__restrict self) {
	return (self->rw_mode == RWLOCK_MODE_FWRITING &&
	        self->rw_xowner == THIS_TASK)
	       ? self->rw_xind
	       : 0;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL __os_rwlock_tryread)(struct rwlock *__restrict self) {
	struct read_lock *desc;
	u32 control_word;
	RWLOCK_TRACE_F("rwlock_tryread");
	if (self->rw_mode == RWLOCK_MODE_FWRITING) {
		if (self->rw_xowner == THIS_TASK) {
			/* Recursive read-after-write. */
			++self->rw_xind;
			return true;
		}
		assertf(!rwlock_find_readlock(self),
		        "You can't be holding read locks when another thread is writing\n"
		        "THIS_TASK       = %p\n"
		        "self->rw_xowner = %p\n"
		        "self->rw_xind   = %" PRIu16 "\n",
		        THIS_TASK, self->rw_xowner,
		        self->rw_xind);
		return false;
	}
	desc = rwlock_get_readlock_nx(self);
	if unlikely(!desc) /* Fail if we can't allocate a read-lock */
		return __os_rwlock_trywrite(self);

	if (desc->rl_recursion) {
		/* Recursive read-lock. */
		assert(self->rw_mode != RWLOCK_MODE_FWRITING);
		assert(self->rw_scnt != 0);
#if 0 /* Thread that already have a read-lock can still acquire \
       * more,  even  if  the  rw-lock  is  in  upgrade   mode. */
		if (self->rw_mode == RWLOCK_MODE_FUPGRADING)
			return false;
#endif
		++desc->rl_recursion;
		return true;
	}
	do {
		control_word = ATOMIC_READ(self->rw_state);
		/* Only allow acquisition when the lock is in read-mode.
		 * In upgrade or write-mode, we cannot allow more  locks
		 * to be acquired. */
		if (RWLOCK_MODE(control_word) != RWLOCK_MODE_FREADING) {
			/* This also deals with upgrade-mode. */
			rwlock_delete_readlock(desc);
			return false;
		}
	} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
	                             RWLOCK_INCIND(control_word)));
	/* Initial read-lock. */
	desc->rl_recursion = 1;
	return true;
}


PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL __os_rwlock_tryread_readonly)(struct rwlock *__restrict self) {
	struct read_lock *desc;
	u32 control_word;
	RWLOCK_TRACE_F("rwlock_tryread_readonly");
	if (self->rw_mode == RWLOCK_MODE_FWRITING) {
		if (self->rw_xowner == THIS_TASK) {
			/* Recursive read-after-write. */
			++self->rw_xind;
			return true;
		}
		assertf(!rwlock_find_readlock(self),
		        "You can't be holding read locks when another thread is writing\n"
		        "THIS_TASK       = %p\n"
		        "self->rw_xowner = %p\n"
		        "self->rw_xind   = %" PRIu16 "\n",
		        THIS_TASK, self->rw_xowner,
		        self->rw_xind);
		return false;
	}
	desc = rwlock_get_readlock_nx(self);
	if unlikely(!desc) /* Fail if we can't allocate a read-lock */
		return false;

	if (desc->rl_recursion) {
		/* Recursive read-lock. */
		assert(self->rw_mode != RWLOCK_MODE_FWRITING);
		assert(self->rw_scnt != 0);
#if 0 /* Thread that already have a read-lock can still acquire \
       * more,  even  if  the  rw-lock  is  in  upgrade   mode. */
		if (self->rw_mode == RWLOCK_MODE_FUPGRADING)
			return false;
#endif
		++desc->rl_recursion;
		return true;
	}
	do {
		control_word = ATOMIC_READ(self->rw_state);
		/* Only allow acquisition when the lock is in read-mode.
		 * In upgrade or write-mode, we cannot allow more  locks
		 * to be acquired. */
		if (RWLOCK_MODE(control_word) != RWLOCK_MODE_FREADING) {
			/* This also deals with upgrade-mode. */
			rwlock_delete_readlock(desc);
			return false;
		}
	} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
	                             RWLOCK_INCIND(control_word)));
	/* Initial read-lock. */
	desc->rl_recursion = 1;
	return true;
}



PUBLIC NONNULL((1)) bool
(FCALL __os_rwlock_read)(struct rwlock *__restrict self,
                         ktime_t abs_timeout) {
	struct read_lock *desc;
	u32 control_word;
	RWLOCK_TRACE_F2("rwlock_read", abs_timeout);
	assertf(!task_wasconnected() || kernel_poisoned(),
	        "You mustn't be connected when calling this function");
	if (self->rw_mode == RWLOCK_MODE_FWRITING) {
		if (self->rw_xowner == THIS_TASK) {
			/* Recursive read-after-write. */
			++self->rw_xind;
			return true;
		}
		assertf(!rwlock_find_readlock(self),
		        "You can't be holding read locks when another thread is writing");
		desc = rwlock_get_readlock(self);
	} else {
		desc = rwlock_get_readlock(self);
		if (desc->rl_recursion) {
			/* Recursive read-lock. */
			assert(self->rw_mode != RWLOCK_MODE_FWRITING);
			assert(self->rw_scnt != 0);
#if 0 /* Thread that already have a read-lock can still acquire \
       * more,  even  if  the  rw-lock  is  in  upgrade   mode. */
			if (self->rw_mode == RWLOCK_MODE_FUPGRADING)
				return false;
#endif
			++desc->rl_recursion;
			return true;
		}
	}
acquire_read_lock:
	assert(desc->rl_recursion == 0);
	do {
		control_word = ATOMIC_READ(self->rw_state);
		/* Only allow acquisition when the lock is in read-mode.
		 * In upgrade or write-mode, we cannot allow more  locks
		 * to be acquired. */
		if (RWLOCK_MODE(control_word) != RWLOCK_MODE_FREADING) {
			/* Connect to the chmode-signal. */
			task_connect(&self->rw_chmode);
			/* Wait for the lock to become available. */
			for (;;) {
				control_word = ATOMIC_READ(self->rw_state);
				/* Check if the lock switched to read-mode. */
				if unlikely(RWLOCK_MODE(control_word) == RWLOCK_MODE_FREADING) {
					if (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
					                        RWLOCK_INCIND(control_word)))
						continue;
					/* It actually did! */
					task_disconnectall();
					goto initial_lock;
				}
				break;
			}
			if (!task_waitfor(abs_timeout)) {
				/* Timeout... (delete the read-descriptor) */
				rwlock_delete_readlock(desc);
				return false;
			}
			goto acquire_read_lock;
		}
		/* Try to increment the read-indirection */
	} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
	                             RWLOCK_INCIND(control_word)));
initial_lock:
	/* Initial read-lock. */
	desc->rl_recursion = 1;
	return true;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(FCALL __os_rwlock_read_nx)(struct rwlock *__restrict self,
                                   ktime_t abs_timeout) {
	struct read_lock *desc;
	u32 control_word;
	RWLOCK_TRACE_F2("rwlock_read", abs_timeout);
	assertf(!task_wasconnected() || kernel_poisoned(),
	        "You mustn't be connected when calling this function");
	if (self->rw_mode == RWLOCK_MODE_FWRITING) {
		if (self->rw_xowner == THIS_TASK) {
			/* Recursive read-after-write. */
			++self->rw_xind;
			return true;
		}
		assertf(!rwlock_find_readlock(self),
		        "You can't be holding read locks when another thread is writing");
		desc = rwlock_get_readlock_nx(self);
		if unlikely(!desc)
			return false;
	} else {
		desc = rwlock_get_readlock_nx(self);
		if unlikely(!desc)
			return false;
		if (desc->rl_recursion) {
			/* Recursive read-lock. */
			assert(self->rw_mode != RWLOCK_MODE_FWRITING);
			assert(self->rw_scnt != 0);
#if 0 /* Thread that already have a read-lock can still acquire \
       * more,  even  if  the  rw-lock  is  in  upgrade   mode. */
			if (self->rw_mode == RWLOCK_MODE_FUPGRADING)
				return false;
#endif
			++desc->rl_recursion;
			return true;
		}
	}
acquire_read_lock:
	assert(desc->rl_recursion == 0);
	do {
		control_word = ATOMIC_READ(self->rw_state);
		/* Only allow acquisition when the lock is in read-mode.
		 * In upgrade or write-mode, we cannot allow more  locks
		 * to be acquired. */
		if (RWLOCK_MODE(control_word) != RWLOCK_MODE_FREADING) {
			/* Connect to the chmode-signal. */
			task_connect(&self->rw_chmode);
			/* Wait for the lock to become available. */
			for (;;) {
				control_word = ATOMIC_READ(self->rw_state);
				/* Check if the lock switched to read-mode. */
				if unlikely(RWLOCK_MODE(control_word) == RWLOCK_MODE_FREADING) {
					if (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
					                        RWLOCK_INCIND(control_word)))
						continue;
					/* It actually did! */
					task_disconnectall();
					goto initial_lock;
				}
				break;
			}
			if (!task_waitfor_nx(abs_timeout)) {
				/* Timeout... (delete the read-descriptor) */
				rwlock_delete_readlock(desc);
				return false;
			}
			goto acquire_read_lock;
		}
		/* Try to increment the read-indirection */
	} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
	                             RWLOCK_INCIND(control_word)));
initial_lock:
	/* Initial read-lock. */
	desc->rl_recursion = 1;
	return true;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL __os_rwlock_trywrite)(struct rwlock *__restrict self) {
	u32 control_word;
	RWLOCK_TRACE_F("rwlock_trywrite");
again:
	control_word = ATOMIC_READ(self->rw_state);
	switch (RWLOCK_MODE(control_word)) {

	case RWLOCK_MODE_FWRITING:
		if (self->rw_xowner == THIS_TASK) {
			/* Recursive read-after-write. */
			++self->rw_xind;
			return true;
		}
		assertf(!rwlock_find_readlock(self),
		        "You can't be holding read locks when another thread is writing");
		ATTR_FALLTHROUGH
	case RWLOCK_MODE_FUPGRADING:
		return false;

	default: break;
	}

	/* Read-mode. */
	if (RWLOCK_IND(control_word) == 0) {
		/* Direct switch to write-mode. */
		assertf(!rwlock_find_readlock(self), "Without any read-locks, how can you be holding any?");
		if (!ATOMIC_CMPXCH(self->rw_state, control_word,
		                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
			goto again;
got_lock:
		self->rw_xowner = THIS_TASK;
		return true;
	} else {
		bool caller_has_lock;
		assert(RWLOCK_IND(control_word) >= 1);
		caller_has_lock = rwlock_find_readlock(self) != NULL;
		/* Must use upgrade-mode to acquire the lock. */
		if (caller_has_lock && RWLOCK_IND(control_word) == 1) {
			/* We seem to be the only reader. - Try to do an atomic upgrade. */
			if (!ATOMIC_CMPXCH(self->rw_state, control_word,
			                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
				goto again;
			goto got_lock;
		}
		return false;
	}
}

PUBLIC NONNULL((1)) bool
(FCALL __os_rwlock_write)(struct rwlock *__restrict self,
                          ktime_t abs_timeout) {
#if 0
	return __os_rwlock_write_aggressive(self, abs_timeout);
#else
	u32 control_word;
	assertf(!task_wasconnected() || kernel_poisoned(),
	        "You mustn't be connected when calling this function");
	RWLOCK_TRACE_F2("rwlock_write", abs_timeout);
again:
	control_word = ATOMIC_READ(self->rw_state);
	switch (RWLOCK_MODE(control_word)) {

	case RWLOCK_MODE_FWRITING:
		if (self->rw_xowner == THIS_TASK) {
			/* Recursive read-after-write. */
			++self->rw_xind;
			return true;
		}
		assertf(!rwlock_find_readlock(self),
		        "You can't be holding read locks when another thread is writing");
		/* Wait for the write-mode to finish. */
wait_for_endwrite:
		TASK_POLL_BEFORE_CONNECT({
			COMPILER_READ_BARRIER();
			if (self->rw_mode == RWLOCK_MODE_FREADING)
				goto again;
		});
		task_connect(&self->rw_chmode);
		COMPILER_READ_BARRIER();
		if (self->rw_mode == RWLOCK_MODE_FREADING) {
			task_disconnectall();
			goto again;
		}
		/* Wait for the lock to become available. */
		if (!task_waitfor(abs_timeout))
			return false; /* Timeout... */
		goto again;

	case RWLOCK_MODE_FUPGRADING:
		/* Lock is in upgrade-mode. */

		/* The caller is holding read-locks, that must be removed to prevent
		 * a  deadlock  situation. For  this purposes,  the `E_RETRY_RWLOCK'
		 * exception exists. */
		if (rwlock_find_readlock(self))
			THROW(__E_RETRY_RWLOCK, self);
		goto wait_for_endwrite;


	default:
		/* Read-mode. */
		if (RWLOCK_IND(control_word) == 0) {
			/* Direct switch to write-mode. */
			assertf(!rwlock_find_readlock(self), "Without any read-locks, how can you be holding any?");
			if (!ATOMIC_CMPXCH(self->rw_state, control_word,
			                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
				goto again;
got_lock:
			self->rw_xowner = THIS_TASK;
			return true;
		} else {
			bool caller_has_lock;
			assert(RWLOCK_IND(control_word) >= 1);
			caller_has_lock = rwlock_find_readlock(self) != NULL;
			/* Must use upgrade-mode to acquire the lock. */
			if (caller_has_lock && RWLOCK_IND(control_word) == 1) {
				/* We seem to be the only reader. - Try to do an atomic upgrade. */
				if (!ATOMIC_CMPXCH(self->rw_state, control_word,
				                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
					goto again;
				goto got_lock;
			}
			/* Switch to upgrade-mode. */
			if (!ATOMIC_CMPXCH(self->rw_state, control_word,
			                   RWLOCK_STATE(RWLOCK_MODE_FUPGRADING,
			                                  RWLOCK_IND(control_word) -
			                                  (caller_has_lock ? 1 : 0))))
				goto again;
wait_for_unshare:
			TRY {
				/* Wait for the end of all readers to be signaled. */
				TASK_POLL_BEFORE_CONNECT({
					if unlikely(ATOMIC_CMPXCH(self->rw_state,
					                           RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
					                           RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
						goto got_lock;
				});
				/* Connect to the unshare-signal. */
				task_connect(&self->rw_unshare);
				/* Check if the upgrade already finished (unlikely) */
				if unlikely(ATOMIC_CMPXCH(self->rw_state,
				                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
				                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1))) {
					task_disconnectall();
					goto got_lock;
				}
				if (!task_waitfor(abs_timeout)) {
					/* Our timeout expired. - Re-acquire the read-lock (if we had one),
					 * switch back to read-mode, and return `false' */
					do {
						control_word = ATOMIC_READ(self->rw_state);
						assert(RWLOCK_MODE(control_word) == RWLOCK_MODE_FUPGRADING);
					} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
					                             RWLOCK_STATE(RWLOCK_MODE_FREADING,
					                                            RWLOCK_IND(control_word) +
					                                            (caller_has_lock ? 1 : 0))));
					return false;
				}
			}
			EXCEPT {
				/* Something went wrong. - Re-acquire the read-lock
				 * (if  we  had  one),  switch  back  to read-mode. */
				do {
					control_word = ATOMIC_READ(self->rw_state);
					assert(RWLOCK_MODE(control_word) == RWLOCK_MODE_FUPGRADING);
				} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
				                             RWLOCK_STATE(RWLOCK_MODE_FREADING,
				                                            RWLOCK_IND(control_word) +
				                                            (caller_has_lock ? 1 : 0))));
				RETHROW();
			}
			/* Signal received. - Check if the unshared is complete. */
			goto wait_for_unshare;
		}
		break;
	}
#endif
}


PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(FCALL __os_rwlock_write_nx)(struct rwlock *__restrict self,
                                    ktime_t abs_timeout) {
	u32 control_word;
	assertf(!task_wasconnected() || kernel_poisoned(),
	        "You mustn't be connected when calling this function");
	RWLOCK_TRACE_F2("rwlock_write", abs_timeout);
again:
	control_word = ATOMIC_READ(self->rw_state);
	switch (RWLOCK_MODE(control_word)) {

	case RWLOCK_MODE_FWRITING:
		if (self->rw_xowner == THIS_TASK) {
			/* Recursive read-after-write. */
			++self->rw_xind;
			return true;
		}
		assertf(!rwlock_find_readlock(self),
		        "You can't be holding read locks when another thread is writing");
		/* Wait for the write-mode to finish. */
wait_for_endwrite:
		TASK_POLL_BEFORE_CONNECT({
			COMPILER_READ_BARRIER();
			if (self->rw_mode == RWLOCK_MODE_FREADING)
				goto again;
		});
		task_connect(&self->rw_chmode);
		COMPILER_READ_BARRIER();
		if (self->rw_mode == RWLOCK_MODE_FREADING) {
			task_disconnectall();
			goto again;
		}
		/* Wait for the lock to become available. */
		if (!task_waitfor_nx(abs_timeout))
			return false; /* Timeout... */
		goto again;

	case RWLOCK_MODE_FUPGRADING:
		/* Lock is in upgrade-mode. */

		/* The caller is holding read-locks, that must be removed to prevent
		 * a  deadlock  situation. For  this purposes,  the `E_RETRY_RWLOCK'
		 * exception exists. */
		if (rwlock_find_readlock(self))
			return false;
		goto wait_for_endwrite;


	default:
		/* Read-mode. */
		if (RWLOCK_IND(control_word) == 0) {
			/* Direct switch to write-mode. */
			assertf(!rwlock_find_readlock(self), "Without any read-locks, how can you be holding any?");
			if (!ATOMIC_CMPXCH(self->rw_state, control_word,
			                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
				goto again;
got_lock:
			self->rw_xowner = THIS_TASK;
			return true;
		} else {
			bool caller_has_lock;
			assert(RWLOCK_IND(control_word) >= 1);
			caller_has_lock = rwlock_find_readlock(self) != NULL;
			/* Must use upgrade-mode to acquire the lock. */
			if (caller_has_lock && RWLOCK_IND(control_word) == 1) {
				/* We seem to be the only reader. - Try to do an atomic upgrade. */
				if (!ATOMIC_CMPXCH(self->rw_state, control_word,
				                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
					goto again;
				goto got_lock;
			}
			/* Switch to upgrade-mode. */
			if (!ATOMIC_CMPXCH(self->rw_state, control_word,
			                   RWLOCK_STATE(RWLOCK_MODE_FUPGRADING,
			                                  RWLOCK_IND(control_word) -
			                                  (caller_has_lock ? 1 : 0))))
				goto again;
wait_for_unshare:
			/* Wait for the end of all readers to be signaled. */
			TASK_POLL_BEFORE_CONNECT({
				if unlikely(ATOMIC_CMPXCH(self->rw_state,
				                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
				                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
					goto got_lock;
			});
			/* Connect to the unshare-signal. */
			task_connect(&self->rw_unshare);
			/* Check if the upgrade already finished (unlikely) */
			if unlikely(ATOMIC_CMPXCH(self->rw_state,
			                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
			                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1))) {
				task_disconnectall();
				goto got_lock;
			}
			if (!task_waitfor_nx(abs_timeout)) {
				/* Our timeout expired. - Re-acquire the read-lock (if we had one),
				 * switch back to read-mode, and return `false' */
				do {
					control_word = ATOMIC_READ(self->rw_state);
					assert(RWLOCK_MODE(control_word) == RWLOCK_MODE_FUPGRADING);
				} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
				                             RWLOCK_STATE(RWLOCK_MODE_FREADING,
				                                            RWLOCK_IND(control_word) +
				                                            (caller_has_lock ? 1 : 0))));
				return false;
			}
			/* Signal received. - Check if the unshared is complete. */
			goto wait_for_unshare;
		}
		break;
	}
}


PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
kill_reader_rpc(struct rpc_context *__restrict UNUSED(ctx), void *cookie) {
	struct rwlock *lock;
	lock = (struct rwlock *)cookie;

	/* Check if the calling thread has a read-lock on `lock',
	 * and throw an  `E_RETRY_RWLOCK' exception  if it  does. */
	if (!rwlock_find_readlock(lock))
		return;

	/* Apparently   we   are  using   that  lock   in  particular.
	 * So  as already mentioned, to deal with this we simply throw
	 * an exception that'll cause the read-lock to be re-acquired. */
	THROW(__E_RETRY_RWLOCK, lock);
}

PRIVATE NONNULL((1, 2)) bool KCALL
kill_rwlock_reader(struct task *__restrict thread,
                   struct rwlock *__restrict lock) {
	struct read_locks *locks;
	if (thread == THIS_TASK)
		goto done; /* Skip our own thread. */
	locks = &FORTASK(thread, this_read_locks);
	ASSERT_VECTOR_INITIALIZED(locks);
	if (!locks->rls_use)
		goto done; /* This thread isn't using any R/W-locks */
	if (FORTASK(thread, this_exception_code) == ERROR_CODEOF(__E_RETRY_RWLOCK) &&
	    FORTASK(thread, this_exception_args.__e_retry_rwlock._err_lock) == (uintptr_t)lock)
		goto done; /* This thread is already in the process of dropping this read-lock. */
	if (locks->rls_vec == locks->rls_sbuf) {
		unsigned int i;
		/* We can search the thread's static read-lock map. */
		for (i = 0; i < COMPILER_LENOF(locks->rls_sbuf); ++i) {
			/* Use an atomic read to reduce the chances of
			 * reading  an incomplete pointer in SMP mode. */
			if (ATOMIC_LOAD(locks->rls_sbuf[i].rl_rwlock) == lock)
				goto use_rpc;
		}
		/* Check again if the thread is still using its static buffer.
		 * NOTE: Event  if  the  thread temporarily  used  a dynamic
		 *       buffer while we  were checking  its static  buffer,
		 *       we're trying to look for threads that were  already
		 *       using our  R/W-lock when  we  changed the  lock  to
		 *       upgrade-mode. So with that  in mind, a thread  that
		 *       wasn't using our lock at  that point won't show  up
		 *       here either. An those that were using it and didn't
		 *       show up just now are of no interest to us, as those
		 *       are the ones  that already got  rid of their  locks
		 *       to our R/W-lock.
		 * This check is only required to ensure that the thread didn't
		 * migrate  its lock to our r/w-lock while we were checking its
		 * set of used locks. */
		if (locks->rls_vec == locks->rls_sbuf)
			goto use_rpc;
	} else {
use_rpc:
		/* Send an RPC to the thread to check if it's using our lock. */
		task_rpc_exec(thread,
		              RPC_CONTEXT_KERN | RPC_PRIORITY_F_HIGH,
		              &kill_reader_rpc, lock);
	}
done:
	return true;
}

PRIVATE NONNULL((1)) void FCALL
rwlock_kill_readers(struct rwlock *__restrict self) {
	/* Enumerate all running threads to find (and kill;  aka.
	 * `rwlock_endread()') those that are using our R/W-lock. */
	(void)kill_rwlock_reader;
	(void)self;
#if 0 /* TODO */
	task_foreach_weak_running((bool(KCALL *)(struct task *__restrict,void*))&kill_rwlock_reader, self);
#endif
}


PUBLIC NONNULL((1)) bool
(FCALL __os_rwlock_write_aggressive)(struct rwlock *__restrict self,
                                     ktime_t abs_timeout) {
	u32 control_word;
	assertf(!task_wasconnected() || kernel_poisoned(),
	        "You mustn't be connected when calling this function");
	RWLOCK_TRACE_F("rwlock_write_aggressive");
again:
	control_word = ATOMIC_READ(self->rw_state);
	switch (RWLOCK_MODE(control_word)) {

	case RWLOCK_MODE_FWRITING:
		if (self->rw_xowner == THIS_TASK) {
			/* Recursive read-after-write. */
			++self->rw_xind;
			return true;
		}
		assertf(!rwlock_find_readlock(self),
		        "You can't be holding read locks when another thread is writing");
		/* Wait for the write-mode to finish. */
wait_for_endwrite:
		TASK_POLL_BEFORE_CONNECT({
			COMPILER_READ_BARRIER();
			if (self->rw_mode == RWLOCK_MODE_FREADING)
				goto again;
		});
		task_connect(&self->rw_chmode);
		COMPILER_READ_BARRIER();
		if (self->rw_mode == RWLOCK_MODE_FREADING) {
			task_disconnectall();
			goto again;
		}
		/* Wait for the lock to become available. */
		if (!task_waitfor(abs_timeout))
			return false; /* Timeout... */
		goto again;

	case RWLOCK_MODE_FUPGRADING:
		/* Lock is in upgrade-mode. */

		/* The caller is holding read-locks, that must be removed to prevent
		 * a  deadlock  situation. For  this purposes,  the `E_RETRY_RWLOCK'
		 * exception exists. */
		if (rwlock_find_readlock(self))
			THROW(__E_RETRY_RWLOCK, self);
		goto wait_for_endwrite;


	default:
		/* Read-mode. */
		if (RWLOCK_IND(control_word) == 0) {
			/* Direct switch to write-mode. */
			assertf(!rwlock_find_readlock(self), "Without any read-locks, how can you be holding any?");
			if (!ATOMIC_CMPXCH(self->rw_state, control_word,
			                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
				goto again;
got_lock:
			self->rw_xowner = THIS_TASK;
			return true;
		} else {
			bool caller_has_lock;
			assert(RWLOCK_IND(control_word) >= 1);
			caller_has_lock = rwlock_find_readlock(self) != NULL;
			/* Must use upgrade-mode to acquire the lock. */
			if (caller_has_lock && RWLOCK_IND(control_word) == 1) {
				/* We seem to be the only reader. - Try to do an atomic upgrade. */
				if (!ATOMIC_CMPXCH(self->rw_state, control_word,
				                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
					goto again;
				goto got_lock;
			}
			/* Switch to upgrade-mode. */
			if (!ATOMIC_CMPXCH(self->rw_state, control_word,
			                   RWLOCK_STATE(RWLOCK_MODE_FUPGRADING,
			                                  RWLOCK_IND(control_word) -
			                                  (caller_has_lock ? 1 : 0))))
				goto again;
wait_for_unshare:
			TRY {
				/* Wait for the end of all readers to be signaled. */
				TASK_POLL_BEFORE_CONNECT({
					if unlikely(ATOMIC_CMPXCH(self->rw_state,
					                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
					                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
						goto got_lock;
				});
				rwlock_kill_readers(self);
				TASK_POLL_BEFORE_CONNECT({
					if unlikely(ATOMIC_CMPXCH(self->rw_state,
					                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
					                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
						goto got_lock;
				});

				/* Connect to the unshare-signal. */
				task_connect(&self->rw_unshare);
				/* Check if the upgrade already finished (unlikely) */
				if unlikely(ATOMIC_CMPXCH(self->rw_state,
				                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
				                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1))) {
					task_disconnectall();
					goto got_lock;
				}
				rwlock_kill_readers(self);
				if unlikely(ATOMIC_CMPXCH(self->rw_state,
				                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
				                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1))) {
					task_disconnectall();
					goto got_lock;
				}
				/* Wait  for  a while,  assuming that  readers  behave as  they should
				 * and release their locks before entering a wait-state when trying to
				 * reacquire  them, but noticing  that the lock  is in UPGRADING mode.
				 * NOTE: We use a small timeout so we can try again in case we missed something. */
				{
					ktime_t tmo = ktime();
					tmo += relktime_from_milliseconds(200);
					task_waitfor(tmo);
				}
			} EXCEPT {
				/* Something went wrong. - Re-acquire the read-lock
				 * (if  we  had  one),  switch  back  to read-mode. */
				do {
					control_word = ATOMIC_READ(self->rw_state);
					assert(RWLOCK_MODE(control_word) == RWLOCK_MODE_FUPGRADING);
				} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
				                             RWLOCK_STATE(RWLOCK_MODE_FREADING,
				                                            RWLOCK_IND(control_word) +
				                                            (caller_has_lock ? 1 : 0))));
				RETHROW();
			}
			/* Signal received. - Check if the unshared is complete. */
			goto wait_for_unshare;
		}
		break;
	}
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL __os_rwlock_tryupgrade)(struct rwlock *__restrict self) {
	/* Special handling to upgrade a non-shared
	 * read-lock to  an  exclusive  write-lock. */
	u32 control_word;
	RWLOCK_TRACE_F("rwlock_tryupgrade");
again:
	control_word = ATOMIC_READ(self->rw_state);
	switch (RWLOCK_MODE(control_word)) {

	case RWLOCK_MODE_FWRITING:
		assertf(self->rw_xowner == THIS_TASK,
		        "You can't be holding read-locks on a write-mode R/W-lock that you don't own");
#if 0 /* Can't be asserted. - The caller may be upgrading a write-lock  caused \
       * by `rwlock_tryread()' in actuality acquiring a write-lock when it was \
       * impossible to acquire a read-lock. */
		assertf(self->rw_xind >= 2,
		        "You're not upgrading a secondary read-lock, but your code "
		        "contains a single `rwlock_write()', followed by `rwlock_upgrade()'");
#endif
		/* Nothing to do here. The previous read-lock already counted as
		 * a write-lock because the R/W-lock is in recursive write-mode. */
		return true;

	case RWLOCK_MODE_FUPGRADING:
		return false;

	default: break;
	}
	/* Read-mode. */
	assertf(rwlock_find_readlock(self), "You're not holding any read-locks");
	assertf(RWLOCK_IND(control_word) >= 1,
	        "Inconsistent R/W-lock state: You're holding "
	        "read-locks that the lock knows nothing about");
	if (RWLOCK_IND(control_word) == 1) {
		/* We seem to be the only reader. - Try to do an atomic upgrade. */
		if (!ATOMIC_CMPXCH(self->rw_state, control_word,
		                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
			goto again;
		/* Atomically upgraded to write-mode. */
		self->rw_xowner = THIS_TASK;
		/* TODO: Decrement the recursion counter of our read-lock, and delete
		 *       it if that counter reaches  ZERO(0) (it's an upgrade, so  it
		 *       replaces the  last read-lock  with a  write-lock, meaning  a
		 *       non-recursive read-lock has to go away!) */
		return true;
	}
	return false;
}



PUBLIC NONNULL((1)) bool
(FCALL __os_rwlock_upgrade)(struct rwlock *__restrict self,
                            ktime_t abs_timeout) {
	/* Special handling to upgrade a non-shared
	 * read-lock to  an  exclusive  write-lock. */
	u32 control_word;
	RWLOCK_TRACE_F2("rwlock_upgrade", abs_timeout);
	assertf(!task_wasconnected() || kernel_poisoned(),
	        "You mustn't be connected when calling this function");
again:
	control_word = ATOMIC_READ(self->rw_state);
	switch (RWLOCK_MODE(control_word)) {

	case RWLOCK_MODE_FWRITING:
		assertf(self->rw_xowner == THIS_TASK,
		        "You can't be holding read-locks on a write-mode R/W-lock that you don't own");
#if 0 /* Can't be asserted. - The caller may be upgrading a write-lock  caused \
       * by `rwlock_tryread()' in actuality acquiring a write-lock when it was \
       * impossible to acquire a read-lock. */
		assertf(self->rw_xind >= 2,
		        "You're not upgrading a secondary read-lock, but your code "
		        "contains a single `rwlock_write()', followed by `rwlock_upgrade()'");
#endif
		/* Nothing to do here. The previous read-lock already counted as
		 * a write-lock because the R/W-lock is in recursive write-mode. */
		return true;

	case RWLOCK_MODE_FUPGRADING:
		/* Lock is in upgrade-mode. */
		assertf(rwlock_find_readlock(self), "You're not holding any read-locks");
		/* The caller is holding read-locks, that must be removed to prevent
		 * a  deadlock  situation. For  this purposes,  the `E_RETRY_RWLOCK'
		 * exception exists. */
		THROW(__E_RETRY_RWLOCK, self);

	default:
		/* Read-mode. */
		assertf(rwlock_find_readlock(self), "You're not holding any read-locks");
		assertf(RWLOCK_IND(control_word) >= 1,
		        "Inconsistent R/W-lock state: You're holding "
		        "read-locks that the lock knows nothing about");
		if (RWLOCK_IND(control_word) == 1) {
			struct read_lock *rlock;
			/* We seem to be the only reader. - Try to do an atomic upgrade. */
			if (!ATOMIC_CMPXCH(self->rw_state, control_word,
			                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
				goto again;
got_lock:
			/* Atomically upgraded to write-mode. */
			self->rw_xowner = THIS_TASK;
			/* Delete the original read-lock if this is a clean
			 * upgrade  (without  any  recursive   read-locks). */
			rlock = rwlock_find_readlock(self);
			assert(rlock);
			if (rlock->rl_recursion == 1)
				rwlock_delete_readlock(rlock);
			else {
				--rlock->rl_recursion;
			}
			return true;
		}
		/* Switch to upgrade-mode. */
		if (!ATOMIC_CMPXCH(self->rw_state, control_word,
		                   RWLOCK_STATE(RWLOCK_MODE_FUPGRADING,
		                                  RWLOCK_IND(control_word) - 1)))
			goto again;
wait_for_unshare:
		TRY {
			/* Wait for the end of all readers to be signaled. */
			TASK_POLL_BEFORE_CONNECT({
				if unlikely(ATOMIC_CMPXCH(self->rw_state,
				                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
				                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
					goto got_lock;
			});
			/* Connect to the unshare-signal. */
			task_connect(&self->rw_unshare);
			/* Check if the upgrade already finished (unlikely) */
			if unlikely(ATOMIC_CMPXCH(self->rw_state,
			                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
			                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1))) {
				task_disconnectall();
				goto got_lock;
			}
			if (!task_waitfor(abs_timeout)) {
				/* Our timeout expired. - Re-acquire the read-lock,
				 * switch  back  to read-mode,  and  return `false' */
				do {
					control_word = ATOMIC_READ(self->rw_state);
					assert(RWLOCK_MODE(control_word) == RWLOCK_MODE_FUPGRADING);
				} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
				                             RWLOCK_STATE(RWLOCK_MODE_FREADING,
				                                            RWLOCK_IND(control_word) + 1)));
				return false;
			}
		} EXCEPT {
			/* Something went wrong. - Re-acquire the read-lock and switch back to read-mode. */
			do {
				control_word = ATOMIC_READ(self->rw_state);
				assert(RWLOCK_MODE(control_word) == RWLOCK_MODE_FUPGRADING);
			} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
			                             RWLOCK_STATE(RWLOCK_MODE_FREADING,
			                                            RWLOCK_IND(control_word) + 1)));
			RETHROW();
		}
		/* Signal received. - Check if the unshared is complete. */
		goto wait_for_unshare;
	}
}



PUBLIC WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL __os_rwlock_upgrade_nx)(struct rwlock *__restrict self,
                                      ktime_t abs_timeout) {
	/* Special handling to upgrade a non-shared
	 * read-lock to  an  exclusive  write-lock. */
	u32 control_word;
	RWLOCK_TRACE_F2("rwlock_upgrade", abs_timeout);
	assertf(!task_wasconnected() || kernel_poisoned(),
	        "You mustn't be connected when calling this function");
again:
	control_word = ATOMIC_READ(self->rw_state);
	switch (RWLOCK_MODE(control_word)) {

	case RWLOCK_MODE_FWRITING:
		assertf(self->rw_xowner == THIS_TASK,
		        "You can't be holding read-locks on a write-mode R/W-lock that you don't own");
#if 0 /* Can't be asserted. - The caller may be upgrading a write-lock  caused \
       * by `rwlock_tryread()' in actuality acquiring a write-lock when it was \
       * impossible to acquire a read-lock. */
		assertf(self->rw_xind >= 2,
		        "You're not upgrading a secondary read-lock, but your code "
		        "contains a single `rwlock_write()', followed by `rwlock_upgrade()'");
#endif
		/* Nothing to do here. The previous read-lock already counted as
		 * a write-lock because the R/W-lock is in recursive write-mode. */
		return 1;

	{
		struct read_lock *desc;
		/* The caller is holding read-locks, that must be removed to prevent
		 * a  deadlock  situation. For  this purposes,  the `E_RETRY_RWLOCK'
		 * exception exists. */
	case RWLOCK_MODE_FUPGRADING:
		/* Lock is in upgrade-mode. */
		/* Drop a read-lock. */
		desc = rwlock_find_readlock(self);
		assertf(desc,
		        "You're not holding any read-locks\n"
		        "self                             = %p\n"
		        "PERTASK(this_read_locks).rls_use = %" PRIuSIZ "\n"
		        "PERTASK(this_read_locks).rls_cnt = %" PRIuSIZ,
		        self,
		        PERTASK_GET(this_read_locks.rls_use),
		        PERTASK_GET(this_read_locks.rls_cnt));
		assertf(self->rw_scnt >= 1,
		        "Noone is holding read-locks");
		assert(desc->rl_recursion != 0);
		if (desc->rl_recursion == 1) {
			u32 control_word;
			/* Last  read-lock  is  being  removed.  (decrement  the
			 * reader-counter of the lock and delete the descriptor) */
			rwlock_delete_readlock(desc);
			do {
				control_word = ATOMIC_READ(self->rw_state);
				assert(RWLOCK_MODE(control_word) != RWLOCK_MODE_FWRITING);
				assert(RWLOCK_IND(control_word) != 0);
			} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
			                             RWLOCK_DECIND(control_word)));
			/* If the last reader went away, send the downgrade signal.
			 * NOTE: Since the lock is now ready for exclusive locking,
			 *       only signal a single thread to improve its chances
			 *       of acquiring that lock. */
			if (RWLOCK_IND(control_word) == 1)
				sig_send(&self->rw_unshare);
		} else {
			/* Recursively release a read-lock, but don't signal the
			 * R/W-lock because it's not the last one we're holding. */
			--desc->rl_recursion;
		}
		return 0;
	}	break;

	default:
		/* Read-mode. */
		assertf(rwlock_find_readlock(self), "You're not holding any read-locks");
		assertf(RWLOCK_IND(control_word) >= 1,
		        "Inconsistent R/W-lock state: You're holding "
		        "read-locks that the lock knows nothing about");
		if (RWLOCK_IND(control_word) == 1) {
			/* We seem to be the only reader. - Try to do an atomic upgrade. */
			if (!ATOMIC_CMPXCH(self->rw_state, control_word,
			                   RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
				goto again;
got_lock:
			/* Atomically upgraded to write-mode. */
			self->rw_xowner = THIS_TASK;
			return true;
		}
		/* Switch to upgrade-mode. */
		if (!ATOMIC_CMPXCH(self->rw_state, control_word,
		                   RWLOCK_STATE(RWLOCK_MODE_FUPGRADING,
		                                  RWLOCK_IND(control_word) - 1)))
			goto again;
wait_for_unshare:
		/* Wait for the end of all readers to be signaled. */
		TASK_POLL_BEFORE_CONNECT({
			if unlikely(ATOMIC_CMPXCH(self->rw_state,
			                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
			                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1)))
				goto got_lock;
		});
		/* Connect to the unshare-signal. */
		task_connect(&self->rw_unshare);
		/* Check if the upgrade already finished (unlikely) */
		if unlikely(ATOMIC_CMPXCH(self->rw_state,
		                          RWLOCK_STATE(RWLOCK_MODE_FUPGRADING, 0),
		                          RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1))) {
			task_disconnectall();
			goto got_lock;
		}
		if (!task_waitfor_nx(abs_timeout)) {
			/* Our timeout expired. - Re-acquire the read-lock,
			 * switch  back  to read-mode,  and  return `false' */
			do {
				control_word = ATOMIC_READ(self->rw_state);
				assert(RWLOCK_MODE(control_word) == RWLOCK_MODE_FUPGRADING);
			} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
			                             RWLOCK_STATE(RWLOCK_MODE_FREADING,
			                                            RWLOCK_IND(control_word) + 1)));
			return false;
		}
		/* Signal received. - Check if the unshared is complete. */
		goto wait_for_unshare;
	}
}



PUBLIC NONNULL((1)) bool
NOTHROW(FCALL __os_rwlock_downgrade)(struct rwlock *__restrict self) {
	RWLOCK_TRACE_F("rwlock_downgrade");
	assertf(self->rw_mode == RWLOCK_MODE_FWRITING,
	        "Lock isn't in write-mode");
	assertf(self->rw_xowner == THIS_TASK,
	        "You're not the owner of this lock");
	assertf(self->rw_xind >= 1,
	        "Inconsistent R/W-lock state");
	if (self->rw_xind == 1) {
		/* Increment the read-recursion for the lock. */
		struct read_lock *lock;
		lock = rwlock_get_readlock_nx(self);
		if unlikely(!lock)
			return false; /* Downgrade failed... */
		lock->rl_recursion += 1;
		/* Do the downgrade (keep the level#1 indirection as reader-counter). */
		ATOMIC_WRITE(self->rw_mode, RWLOCK_MODE_FREADING);
		/* Signal the downgrade. */
		sig_broadcast(&self->rw_chmode);
	} else {
		/* downgrading a recursive read-after-write lock is a no-op. */
	}
	return true;
}

PUBLIC NONNULL((1)) void
(FCALL __os_rwlock_downgrade_readonly)(struct rwlock *__restrict self) {
	RWLOCK_TRACE_F("rwlock_downgrade_readonly");
	assertf(self->rw_mode == RWLOCK_MODE_FWRITING,
	        "Lock isn't in write-mode");
	assertf(self->rw_xowner == THIS_TASK,
	        "You're not the owner of this lock");
	assertf(self->rw_xind >= 1,
	        "Inconsistent R/W-lock state");
	if (self->rw_xind == 1) {
		/* Increment the read-recursion for the lock. */
		rwlock_get_readlock(self)->rl_recursion += 1;
		/* Do the downgrade (keep the level#1 indirection as reader-counter). */
		ATOMIC_WRITE(self->rw_mode, RWLOCK_MODE_FREADING);
		/* Signal the downgrade. */
		sig_broadcast(&self->rw_chmode);
	} else {
		/* downgrading a recursive read-after-write lock is a no-op. */
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL __os_rwlock_endwrite)(struct rwlock *__restrict self) {
	RWLOCK_TRACE_F("rwlock_endwrite");
	assertf(self->rw_mode == RWLOCK_MODE_FWRITING,
	        "Lock isn't in write-mode (%p:%p)",
	        self, self->rw_state);
	assertf(self->rw_xowner == THIS_TASK,
	        "You're not the owner of this lock");
	assertf(self->rw_xind >= 1,
	        "Inconsistent R/W-lock state");
	if (self->rw_xind == 1) {
		struct read_lock *desc;
		/* Clear the owner-field. */
		ATOMIC_WRITE(self->rw_xowner, NULL);
		/* If our thread has older read-locks, restore them. */
		desc = rwlock_find_readlock(self);
		assert(!desc || desc->rl_rwlock == self);
		if (desc) {
			assert(desc->rl_recursion != 0);
			/* Downgrade to read-mode (keep the indirection of `1'). */
			assert(self->rw_scnt == 1);
			ATOMIC_WRITE(self->rw_mode, RWLOCK_MODE_FREADING);
		} else {
			/* Last lock. */
			ATOMIC_WRITE(self->rw_state, RWLOCK_STATE(RWLOCK_MODE_FREADING, 0));
		}
		/* Signal the unlock. */
		sig_broadcast(&self->rw_chmode);
	} else {
		/* Recursively stop writing. */
		--self->rw_xind;
	}
}

/* endread() and end() cannot be differenciated
 * without   additional   debug   informations. */
DEFINE_PUBLIC_ALIAS(rwlock_endread, rwlock_end);

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL __os_rwlock_end)(struct rwlock *__restrict self) {
	RWLOCK_TRACE_F("rwlock_end");
	if (self->rw_mode == RWLOCK_MODE_FWRITING) {
		/* end-read after already writing */
		assertf(self->rw_xowner == THIS_TASK,
		        "You're not the owner of this lock");
		assertf(self->rw_xind >= 1,
		        "Inconsistent R/W-lock state");
		if (self->rw_xind == 1) {
			struct read_lock *desc;
			/* Clear the owner-field. */
			ATOMIC_WRITE(self->rw_xowner, NULL);
			/* If our thread has older read-locks, restore them. */
			desc = rwlock_find_readlock(self);
			if (desc) {
				assert(desc->rl_recursion != 0);
				/* Downgrade to read-mode (keep the indirection of `1'). */
				ATOMIC_WRITE(self->rw_mode, RWLOCK_MODE_FREADING);
			} else {
				/* Last lock. */
				ATOMIC_WRITE(self->rw_state, RWLOCK_STATE(RWLOCK_MODE_FREADING, 0));
			}
			/* Signal the unlock. */
			sig_broadcast(&self->rw_chmode);
		} else {
			/* Recursively stop writing. */
			--self->rw_xind;
		}
	} else {
		struct read_lock *desc;
		/* Drop a read-lock. */
		desc = rwlock_find_readlock(self);
		assertf(desc,
		        "You're not holding any read-locks\n"
		        "self                             = %p\n"
		        "PERTASK(this_read_locks).rls_use = %" PRIuSIZ "\n"
		        "PERTASK(this_read_locks).rls_cnt = %" PRIuSIZ,
		        self,
		        PERTASK_GET(this_read_locks.rls_use),
		        PERTASK_GET(this_read_locks.rls_cnt));
		assertf(self->rw_scnt >= 1,
		        "Noone is holding read-locks");
		assert(desc->rl_recursion != 0);
		if (desc->rl_recursion == 1) {
			u32 control_word;
			/* Last  read-lock  is  being  removed.  (decrement  the
			 * reader-counter of the lock and delete the descriptor) */
			rwlock_delete_readlock(desc);
			do {
				control_word = ATOMIC_READ(self->rw_state);
				assert(RWLOCK_MODE(control_word) != RWLOCK_MODE_FWRITING);
				assert(RWLOCK_IND(control_word) != 0);
			} while (!ATOMIC_CMPXCH_WEAK(self->rw_state, control_word,
			                             RWLOCK_DECIND(control_word)));
			/* If the last reader went away, send the downgrade signal.
			 * NOTE: Since the lock is now ready for exclusive locking,
			 *       only signal a single thread to improve its chances
			 *       of acquiring that lock. */
			if (RWLOCK_IND(control_word) == 1)
				sig_send(&self->rw_unshare);

			/* Deal with parallel-upgrade exceptions. */
			if (was_thrown(__E_RETRY_RWLOCK) &&
			    PERTASK_EQ(this_exception_args.__e_retry_rwlock._err_lock, (uintptr_t)self)) {
				/* Try to yield to the task that is waiting for the lock to become available.
				 * NOTE: By   using  `task_tryyield()'  here,  we  can  remain  non-blocking! */
				task_tryyield();
				/* Get the caller to re-try acquiring this lock. */
				return true;
			}
		} else {
			/* Recursively release a read-lock, but don't signal the
			 * R/W-lock because it's not the last one we're holding. */
			--desc->rl_recursion;
		}
	}
	return false;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_canwrite)(struct rwlock const *__restrict self) {
	u32 state;
	state = ATOMIC_READ(self->rw_state);
	if (RWLOCK_MODE(state) == RWLOCK_MODE_FREADING) {
		if (RWLOCK_IND(state) == 0 ||
		    (RWLOCK_IND(state) == 1 && rwlock_find_readlock(self)))
			return true; /* No [other] readers -> Write lock is available. */
	} else if (self->rw_xowner == THIS_TASK) {
		/* Caller is holding the write-lock. */
		return true;
	}
	return false;
}



#ifdef DEFINE_TEST
DEFINE_TEST(rwlock_recursion) {
	struct rwlock test = RWLOCK_INIT;
#define ASSERT_LOCKS(rlocks, wlocks)             \
	assertf(rwlock_reading_r(&test) == rlocks && \
	        rwlock_writing_r(&test) == wlocks,   \
	        "rwlock_reading_r: %" PRIuSIZ "\n"   \
	        "rwlock_writing_r: %" PRIuSIZ,       \
	        rwlock_reading_r(&test),             \
	        rwlock_writing_r(&test))

	rwlock_write(&test);       ASSERT_LOCKS(1, 1);
	rwlock_endwrite(&test);    ASSERT_LOCKS(0, 0); /* Release a simple write-lock */

	rwlock_write(&test);       ASSERT_LOCKS(1, 1);
	rwlock_end(&test);         ASSERT_LOCKS(0, 0); /* Auto-release a simple write-lock */

	rwlock_read(&test);        ASSERT_LOCKS(1, 0);
	rwlock_endread(&test);     ASSERT_LOCKS(0, 0); /* Release a simple read-lock */

	rwlock_read(&test);        ASSERT_LOCKS(1, 0);
	rwlock_end(&test);         ASSERT_LOCKS(0, 0); /* Auto-release a simple read-lock */

	rwlock_read(&test);        ASSERT_LOCKS(1, 0);
	rwlock_read(&test);        ASSERT_LOCKS(2, 0);
	rwlock_end(&test);         ASSERT_LOCKS(1, 0); /* Release recursive read-locks */
	rwlock_end(&test);         ASSERT_LOCKS(0, 0);

	rwlock_read(&test);        ASSERT_LOCKS(1, 0);
	rwlock_read(&test);        ASSERT_LOCKS(2, 0);
	rwlock_upgrade(&test);     ASSERT_LOCKS(1, 1);
	rwlock_endwrite(&test);    ASSERT_LOCKS(1, 0); /* Release an upgraded lock */
	rwlock_read(&test);        ASSERT_LOCKS(2, 0);
	rwlock_end(&test);         ASSERT_LOCKS(1, 0);
	rwlock_end(&test);         ASSERT_LOCKS(0, 0);

	rwlock_read(&test);        ASSERT_LOCKS(1, 0);
	rwlock_read(&test);        ASSERT_LOCKS(2, 0);
	rwlock_upgrade(&test);     ASSERT_LOCKS(1, 1);
	rwlock_downgrade(&test);   ASSERT_LOCKS(2, 0); /* Downgrade an upgraded lock */
	rwlock_endread(&test);     ASSERT_LOCKS(1, 0);
	rwlock_endread(&test);     ASSERT_LOCKS(0, 0);

	rwlock_read(&test);        ASSERT_LOCKS(1, 0);
	rwlock_write(&test);       ASSERT_LOCKS(1, 1); /* Write-after-read */
	rwlock_downgrade(&test);   ASSERT_LOCKS(2, 0); /* Downgrade an upgraded lock */
	rwlock_endread(&test);     ASSERT_LOCKS(1, 0);
	rwlock_endread(&test);     ASSERT_LOCKS(0, 0);

#undef ASSERT_LOCKS
}
#endif /* DEFINE_TEST */


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_RWLOCK_C */
