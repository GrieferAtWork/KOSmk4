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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_RWLOCK_H
#define GUARD_KERNEL_INCLUDE_SCHED_RWLOCK_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

#include <sched/task.h>
#include <sched/signal.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/byteorder.h>

#ifdef __CC__
DECL_BEGIN

struct task;

/* NOTE: The read capabilities of this new R/W-lock primitive are
 *       fairly expensive due to the reason that all threads holding
 *       read-locks must be tracked in order to properly handle
 *       write-after-read recursion.
 *       For that reason, using a `mutex' (which would be equivalent
 *       to an rwlock that is only ever be used in write-lock), might
 *       be the better solution. */

/* Recursive, shared/mutually exclusive synchronization primitive
 * NOTE: This one must be capable of dealing with:
 * >> rwlock_read(x);
 * >> rwlock_read(x);  // Secondary read lock does not count to the total number of reading threads.
 * >> rwlock_write(x); // Upgrade lock by changing to a state that prevents new threads from being added,
 * >>                  // while also ensuring that the calling thread is the only one holding a lock.
 * >> rwlock_write(x);
 * >> rwlock_read(x);  // Once already holding a write-lock, this is the same as calling `rwlock_write()'
 * >> // .. Same as holding a single `rwlock_write(x)'
 * >> rwlock_endread(x);
 * >> rwlock_endwrite(x);
 * >> rwlock_endwrite(x);
 * >> rwlock_endread(x);
 * >> rwlock_endread(x);
 */


/* The `parallel-upgrade' problem:
 *   -- TODO
 */


#define RWLOCK_MODE_FREADING   0x00 /* MODE: ZERO, One or more threads are holding read locks. */
#define RWLOCK_MODE_FUPGRADING 0x01 /* MODE: A reader is being upgraded to a writer, or
                                     *       a writer is attempting to acquire a lock.
                                     *       New readers must wait until the rwlock
                                     *       has returned to `RWLOCK_MODE_FREADING'
                                     *       before acquiring a shared lock. */
#define RWLOCK_MODE_FWRITING   0x02 /* MODE: The rwlock is being owned
                                     *       exclusively by a single thread. */

#define RWLOCK_FNORMAL 0x00 /* Normal flags. */


#define __RWLOCK_STATE(mode, ind) ((ind) << 16 | (mode))
#define __RWLOCK_MODE(state)      ((state) & 0xff)
#define __RWLOCK_IND(state)       ((state) >> 16)
#define __RWLOCK_INCIND(state)    ((state) + (1 << 16))
#define __RWLOCK_DECIND(state)    ((state) - (1 << 16))


struct rwlock {
	union __ATTR_PACKED {
		WEAK u32         rw_state;       /* R/W-lock state. */
#if __SIZEOF_POINTER__ > 4
		uintptr_t        rw_pad;         /* Align by pointers. */
#endif
		struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			WEAK u8      rw_mode;        /* R/W-lock mode (one of `RWLOCK_MODE_F*') */
			u8           rw_flags;       /* R/W-lock flags (set of `RWLOCK_F*') */
			union __ATTR_PACKED {
				u16      rw_xind;        /* [valid_if(rw_mode == RWLOCK_MODE_FWRITING)]
				                          * [lock(rw_xowner == THIS_TASK)]
				                          * Indirection/Recursion of the exclusive lock. */
				WEAK u16 rw_scnt;        /* [valid_if(rw_mode == RWLOCK_MODE_FREADING)]
				                          * The total number of individual reader threads.
				                          * NOTE: Read-recursion is tracked internally
				                          *       using a per-thread hash-vector of R/W-lock
				                          *       structures to which that thread is currently
				                          *       holding a READ/WRITE lock. */
			};
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			union __ATTR_PACKED {
				u16      rw_xind;        /* [valid_if(rw_mode == RWLOCK_MODE_FWRITING)]
				                          * [lock(rw_xowner == THIS_TASK)]
				                          * Indirection/Recursion of the exclusive lock. */
				WEAK u16 rw_scnt;        /* [valid_if(rw_mode == RWLOCK_MODE_FREADING)]
				                          * The total number of individual reader threads.
				                          * NOTE: Read-recursion is tracked internally
				                          *       using a per-thread hash-vector of R/W-lock
				                          *       structures to which that thread is currently
				                          *       holding a READ/WRITE lock. */
			};
			u8           rw_flags;       /* R/W-lock flags (set of `RWLOCK_F*') */
			WEAK u8      rw_mode;        /* R/W-lock mode (one of `RWLOCK_MODE_F*') */
#endif
		};
	};
	struct sig           rw_chmode;      /* Signal boardcast when `rw_mode' is downgraded (write -> read / write -> none).
	                                      * (Usually connected to threads calling `rwlock_read' or `rwlock_write') */
	struct sig           rw_unshare;     /* Signal sent to a single thread when `rw_scnt' recursion drops to ZERO(0).
	                                      * (Usually connected to the thread that is calling `rwlock_upgrade()') */
	struct task         *rw_xowner;      /* [valid_if(rw_mode == RWLOCK_MODE_FWRITING)]
	                                      * [lock(rw_xowner == THIS_TASK)]
	                                      * Exclusive owner of this R/W lock. */
};

#define RWLOCK_INIT    {{0},SIG_INIT,SIG_INIT,NULL}
#define rwlock_init(x) \
	(void)((x)->rw_mode  = RWLOCK_MODE_FREADING, \
	       (x)->rw_flags = RWLOCK_FNORMAL,       \
	       sig_init(&(x)->rw_chmode),            \
	       sig_init(&(x)->rw_unshare),           \
	       (x)->rw_xind = 1)
#define rwlock_init_write(x) \
	(void)((x)->rw_mode  = RWLOCK_MODE_FWRITING, \
	       (x)->rw_flags = RWLOCK_FNORMAL,       \
	       sig_init(&(x)->rw_chmode),            \
	       sig_init(&(x)->rw_unshare),           \
	       (x)->rw_xind = 0,                     \
	       (x)->rw_xowner = THIS_TASK)
#define rwlock_cinit(x) \
	(void)(__hybrid_assert((x)->rw_mode == RWLOCK_MODE_FREADING), \
	       __hybrid_assert((x)->rw_flags == RWLOCK_FNORMAL),      \
	       sig_cinit(&(x)->rw_chmode),                            \
	       sig_cinit(&(x)->rw_unshare),                           \
	       __hybrid_assert((x)->rw_xind == 0))
#define rwlock_cinit_write(x)                                     \
	(void)(__hybrid_assert((x)->rw_mode == RWLOCK_MODE_FREADING), \
	       __hybrid_assert((x)->rw_flags == RWLOCK_FNORMAL),      \
	       sig_cinit(&(x)->rw_chmode),                            \
	       sig_cinit(&(x)->rw_unshare),                           \
	       __hybrid_assert((x)->rw_xind == 0),                    \
	       (x)->rw_xowner = THIS_TASK,                            \
	       (x)->rw_state  = __RWLOCK_STATE(RWLOCK_MODE_FWRITING, 1))

/* Check if the caller is holding a read- or write-lock on `self' */
FUNDEF WUNUSED ATTR_PURE NONNULL((1)) bool NOTHROW(FCALL rwlock_reading)(struct rwlock const *__restrict self);
FUNDEF WUNUSED ATTR_PURE NONNULL((1)) bool NOTHROW(FCALL rwlock_writing)(struct rwlock const *__restrict self);
/* Same as above, but return the effective access recursion */
FUNDEF WUNUSED ATTR_PURE NONNULL((1)) uintptr_t NOTHROW(FCALL rwlock_reading_r)(struct rwlock const *__restrict self);
FUNDEF WUNUSED ATTR_PURE NONNULL((1)) uintptr_t NOTHROW(FCALL rwlock_writing_r)(struct rwlock const *__restrict self);
#ifndef __INTELLISENSE__
#define rwlock_writing(self)                    \
	((self)->rw_mode == RWLOCK_MODE_FWRITING && \
	 (self)->rw_xowner == THIS_TASK)
#define rwlock_writing_r(self) \
	(rwlock_writing(self) ? (uintptr_t)(self)->rw_xind : 0)
#endif

/* Return the total number of hold read-locks (or 0 if this is not tracked by the implementation) */
FUNDEF WUNUSED ATTR_PURE uintptr_t NOTHROW(FCALL rwlock_reading_any)(void);

#define CONFIG_TASK_STATIC_READLOCKS 4 /* NOTE: Must be a power-of-2 (2, 4, 8, 16, etc...) */


/* Try to acquire a shared/exclusive lock, or try to
 * atomically (non-locking) upgrade a shared to an exclusive lock.
 * NOTE: When `rwlock_tryread()' fails to allocate a read-lock because the
 *       calling thread is already holding at least `CONFIG_TASK_STATIC_READLOCKS'
 *       read-locks to other rwlock objects, `kmalloc_nx()' with `GFP_ATOMIC'
 *       is called to allocate additional read-lock structure.
 *       Should this also fail, `rwlock_tryread()' will acquire a write-lock
 *       that should still be released by either calling `rwlock_endread()' or
 *      `rwlock_end()'. Acquisition of this write-lock is identical to a call
 *       to `rwlock_trywrite()'.
 *    -> If your code requires you to only be holding a read-lock,
 *       use `rwlock_tryread_readonly()' instead, which will not
 *       return `false' after a failure to `kmalloc_nx()' a new read-lock,
 *       rather than attempting to acquire a write-lock instead. */
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(FCALL rwlock_tryread)(struct rwlock *__restrict self);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(FCALL rwlock_trywrite)(struct rwlock *__restrict self);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(FCALL rwlock_tryupgrade)(struct rwlock *__restrict self);
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(FCALL rwlock_tryread_readonly)(struct rwlock *__restrict self);

#ifndef __INTELLISENSE__
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(FCALL __os_rwlock_tryread)(struct rwlock *__restrict self) ASMNAME("rwlock_tryread");
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(FCALL __os_rwlock_tryread_readonly)(struct rwlock *__restrict self) ASMNAME("rwlock_tryread_readonly");
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(FCALL __os_rwlock_trywrite)(struct rwlock *__restrict self) ASMNAME("rwlock_trywrite");
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(FCALL __os_rwlock_tryupgrade)(struct rwlock *__restrict self) ASMNAME("rwlock_tryupgrade");
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_tryread)(struct rwlock *__restrict self) {
	if (!__os_rwlock_tryread(self))
		return false;
	COMPILER_READ_BARRIER();
	return true;
}
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_tryread_readonly)(struct rwlock *__restrict self) {
	if (!__os_rwlock_tryread_readonly(self))
		return false;
	COMPILER_READ_BARRIER();
	return true;
}
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_trywrite)(struct rwlock *__restrict self) {
	if (!__os_rwlock_trywrite(self))
		return false;
	COMPILER_BARRIER();
	return true;
}
FORCELOCAL NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_tryupgrade)(struct rwlock *__restrict self) {
	if (!__os_rwlock_tryupgrade(self))
		return false;
	COMPILER_WRITE_BARRIER();
	return true;
}
#endif /* !__INTELLISENSE__ */

struct timespec;

/* Blocking-acquire a shared/exclusive lock.
 * NOTE: These functions clobber task connections.
 * @throw: * :                An exception was thrown by an RPC callback.
 * @throw: E_INTERRUPT:       The calling thread was interrupted.
 * @throw: E_BADALLOC:       [rwlock_read] Failed to allocate a read-descriptor.
 * @throw: __E_RETRY_RWLOCK: [rwlock_write]
 *                            The parallel-upgrade deadlock was detected and the calling
 *                            thread was chosen to unwind their stack, calling
 *                           `rwlock_endread()' or `rwlock_end()' until one of the
 *                            two functions returns `true', in which case said function
 *                            should jump back to the code that was originally used
 *                            to acquire a read-lock further up the execution tree.
 *                            See the section on `parallel-upgrade' above.
 * @return: true:  The operation was successful.
 * @return: false: The given timeout has expired. */
FORCELOCAL NONNULL((1)) bool FCALL rwlock_read(struct rwlock *__restrict self, struct timespec const *abs_timeout DFL(__NULLPTR)) THROWS(E_BADALLOC,E_INTERRUPT,...);
FORCELOCAL NONNULL((1)) bool FCALL rwlock_write(struct rwlock *__restrict self, struct timespec const *abs_timeout DFL(__NULLPTR)) THROWS(E_INTERRUPT,__E_RETRY_RWLOCK,...);
FORCELOCAL WUNUSED NONNULL((1)) bool NOTHROW(FCALL rwlock_read_nx)(struct rwlock *__restrict self, struct timespec const *abs_timeout DFL(__NULLPTR));
FORCELOCAL WUNUSED NONNULL((1)) bool NOTHROW(FCALL rwlock_write_nx)(struct rwlock *__restrict self, struct timespec const *abs_timeout DFL(__NULLPTR));
#ifndef __INTELLISENSE__
FUNDEF NONNULL((1)) bool FCALL __os_rwlock_read(struct rwlock *__restrict self, struct timespec const *abs_timeout) THROWS(E_BADALLOC,E_INTERRUPT,...) ASMNAME("rwlock_read");
FUNDEF NONNULL((1)) bool FCALL __os_rwlock_write(struct rwlock *__restrict self, struct timespec const *abs_timeout) THROWS(E_INTERRUPT,__E_RETRY_RWLOCK,...) ASMNAME("rwlock_write");
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL __os_rwlock_read_nx)(struct rwlock *__restrict self, struct timespec const *abs_timeout) ASMNAME("rwlock_read_nx");
FUNDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL __os_rwlock_write_nx)(struct rwlock *__restrict self, struct timespec const *abs_timeout) ASMNAME("rwlock_write_nx");
FORCELOCAL NONNULL((1)) bool FCALL
rwlock_read(struct rwlock *__restrict self, struct timespec const *abs_timeout)
		THROWS(E_BADALLOC,E_INTERRUPT,...) {
	if (!__os_rwlock_read(self, abs_timeout))
		return false;
	COMPILER_READ_BARRIER();
	return true;
}
FORCELOCAL NONNULL((1)) bool FCALL
rwlock_write(struct rwlock *__restrict self, struct timespec const *abs_timeout)
		THROWS(E_INTERRUPT,__E_RETRY_RWLOCK,...) {
	if (!__os_rwlock_write(self, abs_timeout))
		return false;
	COMPILER_BARRIER();
	return true;
}
FORCELOCAL WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_read_nx)(struct rwlock *__restrict self, struct timespec const *abs_timeout) {
	if (!__os_rwlock_read_nx(self, abs_timeout))
		return false;
	COMPILER_READ_BARRIER();
	return true;
}
FORCELOCAL WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_write_nx)(struct rwlock *__restrict self, struct timespec const *abs_timeout) {
	if (!__os_rwlock_write_nx(self, abs_timeout))
		return false;
	COMPILER_BARRIER();
	return true;
}
#endif /* !__INTELLISENSE__ */

/* An advanced variant of `rwlock_write()' which makes use of
 * the RETRY_RWLOCK mechanism to quickly acquire a write lock.
 * The difference between this and the regular write, is that
 * this function will explicitly go and hunt down threads that
 * are holding read-locks on `self', scheduling RPC callbacks
 * in their context and throwing `__E_RETRY_RWLOCK' with `self'
 * as associated r/w-lock.
 * This way, the calling thread is guarantied to be able to
 * eventually acquire a write-lock, even if there were other
 * threads holding read locks, which were also waiting for
 * some other kind of lock.
 * The `abs_timeout' only comes into effect when the r/w-lock
 * was already in write-mode, but the owner was some thread
 * other than the calling thread. In this case, a regular wait
 * will still be performed, and the function behaves just like
 * the regular `rwlock_timedwrite()'.
 * @throw: * :            [abs_timeout != JTIME_DONTWAIT] An exception was thrown by an RPC callback.
 * @throw: E_INTERRUPT:   [abs_timeout != JTIME_DONTWAIT] The calling thread was interrupted.
 * @throw: E_BADALLOC:     Failed to allocate an RPC callback for one of the reader threads.
 * @throw: __E_RETRY_RWLOCK: The parallel-upgrade deadlock was detected and the calling
 *                         thread was chosen to unwind their stack, calling
 *                        `rwlock_endread()' or `rwlock_end()' until one of the
 *                         two functions returns `true', in which case said function
 *                         should jump back to the code that was originally used
 *                         to acquire a read-lock further up the execution tree.
 *                         See the section on `parallel-upgrade' above.
 * @return: true:  Successfully acquire a write lock.
 * @return: false: The given timeout has expired. */
FORCELOCAL NONNULL((1)) bool FCALL
rwlock_write_aggressive(struct rwlock *__restrict self,
                                struct timespec const *abs_timeout DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, __E_RETRY_RWLOCK, ...);
#ifndef __INTELLISENSE__
FUNDEF NONNULL((1)) bool FCALL
__os_rwlock_write_aggressive(struct rwlock *__restrict self, struct timespec const *abs_timeout)
		THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, __E_RETRY_RWLOCK, ...)
		ASMNAME("rwlock_write_aggressive");
FORCELOCAL NONNULL((1)) bool FCALL
rwlock_write_aggressive(struct rwlock *__restrict self, struct timespec const *abs_timeout)
		THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, __E_RETRY_RWLOCK, ...) {
	if (!__os_rwlock_write_aggressive(self, abs_timeout))
		return false;
	COMPILER_BARRIER();
	return true;
}
#endif /* !__INTELLISENSE__ */


/* Update a read-lock to an exclusive write-lock.
 * @return: false:           The given timeout has expired. (a read-lock is still being held)
 * @return: true:            Successfully upgraded the lock. (you're now holding a write-lock)
 * @throw: __E_RETRY_RWLOCK: The parallel-upgrade deadlock was detected and the calling
 *                           thread was chosen to unwind their stack, calling
 *                          `rwlock_endread()' or `rwlock_end()' until one of the
 *                           two functions returns `true', in which case said function
 *                           should jump back to the code that was originally used
 *                           to acquire a read-lock further up the execution tree.
 *                           See the section on `parallel-upgrade' above.
 *                          (a read-lock is still being held) */
FORCELOCAL NONNULL((1)) bool FCALL
rwlock_upgrade(struct rwlock *__restrict self,
               struct timespec const *abs_timeout DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_INTERRUPT, __E_RETRY_RWLOCK, ...);
FORCELOCAL WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL rwlock_upgrade_nx)(struct rwlock *__restrict self,
                                 struct timespec const *abs_timeout DFL(__NULLPTR));
#ifndef __INTELLISENSE__
FUNDEF NONNULL((1)) bool FCALL
__os_rwlock_upgrade(struct rwlock *__restrict self, struct timespec const *abs_timeout)
		THROWS(E_WOULDBLOCK, E_INTERRUPT, __E_RETRY_RWLOCK, ...)
		ASMNAME("rwlock_upgrade");
FUNDEF WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL __os_rwlock_upgrade_nx)(struct rwlock *__restrict self, struct timespec const *abs_timeout)
		ASMNAME("rwlock_upgrade_nx");
FORCELOCAL NONNULL((1)) bool FCALL
rwlock_upgrade(struct rwlock *__restrict self,
               struct timespec const *abs_timeout)
		THROWS(E_WOULDBLOCK, E_INTERRUPT, __E_RETRY_RWLOCK, ...) {
	if (!__os_rwlock_upgrade(self, abs_timeout))
		return false;
	COMPILER_WRITE_BARRIER();
	return true;
}

FORCELOCAL WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL rwlock_upgrade_nx)(struct rwlock *__restrict self,
                                 struct timespec const *abs_timeout) {
	unsigned int result;
	result = __os_rwlock_upgrade_nx(self, abs_timeout);
	if (result != 0)
		COMPILER_WRITE_BARRIER();
	return result;
}
#endif /* !__INTELLISENSE__ */

/* Downgrade a write-lock to a read-lock.
 * NOTE: When multiple write-locks are being held recursively,
 *       this function does nothing and previous, recursive
 *       write-locks will remain active and keep the caller
 *       the lock's exclusive write-owner.
 * @return: true:  Successfully downgraded the R/W-lock
 * @return: false: Failed to allocate a read-lock descriptor (a write-lock was kept). */
FORCELOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL rwlock_downgrade)(struct rwlock *__restrict self);

/* Same as `rwlock_downgrade()', but use use `GFP_NORMAL' and
 * `kmalloc()' in order to allocate a missing read-lock descriptor. */
FORCELOCAL NONNULL((1)) void FCALL
rwlock_downgrade_readonly(struct rwlock *__restrict self)
		THROWS(E_BADALLOC);

#ifndef __INTELLISENSE__
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL __os_rwlock_downgrade)(struct rwlock *__restrict self)
		ASMNAME("rwlock_downgrade");
FUNDEF NONNULL((1)) void FCALL
__os_rwlock_downgrade_readonly(struct rwlock *__restrict self)
		THROWS(E_BADALLOC)
		ASMNAME("rwlock_downgrade_readonly");
FORCELOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL rwlock_downgrade)(struct rwlock *__restrict self) {
	COMPILER_WRITE_BARRIER();
	return __os_rwlock_downgrade(self);
}
FORCELOCAL NONNULL((1)) void FCALL
rwlock_downgrade_readonly(struct rwlock *__restrict self) THROWS(E_BADALLOC) {
	COMPILER_WRITE_BARRIER();
	__os_rwlock_downgrade_readonly(self);
}
#endif /* !__INTELLISENSE__ */

/* Release a shared/exclusive lock, or automatically the kind of lock last acquired.
 * NOTE: It is preferred that `rwlock_endwrite' or `rwlock_endread' are used
 *       to release locks. Not only because they are faster, but also because
 *       they allow for better detection of invalid uses, when it is known
 *       at runtime if the end of a read, or a write-lock is intended.
 * @return: false: The lock was released.
 * @return: true:  After another thread needed to upgrade `self', the calling
 *                 thread's own attempt to upgrade the same lock was halted
 *                 by throwing an `__E_RETRY_RWLOCK' exception.
 *                 This is usually returned when called from a FINALLY-block.
 * >> again:
 * >>     rwlock_read(&my_lock);
 * >>     TRY {
 * >>         ...
 * >>     } EXCEPT {
 * >>         if (rwlock_endread(&my_lock))
 * >>             goto again;
 * >>         RETHROW();
 * >>     }
 * >>     rwlock_endread(&my_lock);
 */
FORCELOCAL NOBLOCK NONNULL((1)) void NOTHROW(FCALL rwlock_endwrite)(struct rwlock *__restrict self);
FORCELOCAL NOBLOCK NONNULL((1)) bool NOTHROW(FCALL rwlock_endread)(struct rwlock *__restrict self);
FORCELOCAL NOBLOCK NONNULL((1)) bool NOTHROW(FCALL rwlock_end)(struct rwlock *__restrict self);
#ifndef __INTELLISENSE__
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL __os_rwlock_endwrite)(struct rwlock *__restrict self) ASMNAME("rwlock_endwrite");
FUNDEF NOBLOCK NONNULL((1)) bool NOTHROW(FCALL __os_rwlock_endread)(struct rwlock *__restrict self) ASMNAME("rwlock_endread");
FUNDEF NOBLOCK NONNULL((1)) bool NOTHROW(FCALL __os_rwlock_end)(struct rwlock *__restrict self) ASMNAME("rwlock_end");
FORCELOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rwlock_endwrite)(struct rwlock *__restrict self) {
	COMPILER_BARRIER();
	__os_rwlock_endwrite(self);
}
FORCELOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL rwlock_endread)(struct rwlock *__restrict self) {
	COMPILER_READ_BARRIER();
	return __os_rwlock_endread(self);
}
FORCELOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL rwlock_end)(struct rwlock *__restrict self) {
	COMPILER_BARRIER();
	return __os_rwlock_end(self);
}
#endif /* !__INTELLISENSE__ */

/* Asynchronously connect to the given R/W-lock for reading or writing.
 * @return: true:  The rwlock is currently available for reading or writing.
 * @return: false: The rwlock wasn't available, and a connection was made to the proper signal. */
FUNDEF WUNUSED NONNULL((1)) bool FCALL rwlock_pollread(struct rwlock *__restrict self) THROWS(E_BADALLOC);
FUNDEF WUNUSED NONNULL((1)) bool FCALL rwlock_pollwrite(struct rwlock *__restrict self) THROWS(E_BADALLOC);

/* Check if a read/write-lock can be acquired without blocking */
FORCELOCAL WUNUSED NONNULL((1)) bool NOTHROW(FCALL rwlock_canread)(struct rwlock const *__restrict self);
FUNDEF WUNUSED NOBLOCK NONNULL((1)) bool NOTHROW(FCALL rwlock_canwrite)(struct rwlock const *__restrict self);

#ifndef __INTELLISENSE__
FORCELOCAL WUNUSED NONNULL((1)) bool
NOTHROW(FCALL rwlock_canread)(struct rwlock const *__restrict self) {
	u32 state;
	state = __hybrid_atomic_load(self->rw_state, __ATOMIC_ACQUIRE);
	return (__RWLOCK_MODE(state) == RWLOCK_MODE_FREADING ||
	        self->rw_xowner == THIS_TASK);
}
#endif /* !__INTELLISENSE__ */




/* Define C++ sync API hooks. */
__DEFINE_SYNC_RWLOCK(struct rwlock,
                     rwlock_tryread,
                     rwlock_read,
                     rwlock_read_nx,
                     rwlock_endread,
                     rwlock_reading,
                     rwlock_canread,
                     rwlock_trywrite,
                     rwlock_write,
                     rwlock_write_nx,
                     rwlock_endwrite,
                     rwlock_writing,
                     rwlock_canwrite,
                     rwlock_end,
                     rwlock_tryupgrade,
                     rwlock_upgrade,
                     rwlock_upgrade_nx,
                     rwlock_downgrade)
__DEFINE_SYNC_POLL(struct rwlock,
                   rwlock_pollread,
                   rwlock_pollwrite)


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_RWLOCK_H */
