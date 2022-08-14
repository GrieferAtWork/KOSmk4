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
#ifndef GUARD_KERNEL_SRC_SCHED_ATOMIC64_C
#define GUARD_KERNEL_SRC_SCHED_ATOMIC64_C 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <sched/atomic64.h>

#ifndef ARCH_HAVE_ATOMIC64_SUPPORT_ALWAYS
#ifndef ARCH_HAVE_ATOMIC64_PROTOTYPES
#include <sched/cpu.h>
#include <sched/task.h>

#include <hybrid/sched/atomic-rwlock.h>

#include <stdbool.h>

DECL_BEGIN

#ifdef ARCH_HAVE_ATOMIC64_SUPPORT_DYNAMIC
#define DECL       INTERN
#define FUNC(name) emulated_##name
#else /* ARCH_HAVE_ATOMIC64_SUPPORT_DYNAMIC */
#define DECL       PUBLIC
#define FUNC(name) name
#endif /* !ARCH_HAVE_ATOMIC64_SUPPORT_DYNAMIC */



#ifndef CONFIG_NO_SMP
/*[[[config CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT! = 4
 * >> CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT == log2(LOCK_COUNT)
 * ]]]*/
#ifndef CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT
#define CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT 4
#endif /* !CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT */
/*[[[end]]]*/

PRIVATE struct atomic_rwlock locks[1 << CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT] = {
	ATOMIC_RWLOCK_INIT,
};

PRIVATE NOBLOCK ATTR_CONST WUNUSED struct atomic_rwlock *
NOTHROW(FCALL lockfor)(atomic64_t const *__restrict self) {
#if CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT == 4
	u16 index;
	/* Only use the bottom 16 bits for indexing. */
	index = (u16)(uintptr_t)self;
	index = index >> 8;
	index = index >> 4;
#else /* CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT == ... */
#error "Unsupported `CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT'"
#endif /* CONFIG_KERNEL_ATOMIC64_LOG2_LOCKCNT != ... */
	return &locks[index];
}
#endif /* !CONFIG_NO_SMP */


#ifdef CONFIG_NO_SMP
#define _LOCK_EX(...)           \
	do {                        \
		preemption_flag_t _was; \
		preemption_pushoff(&_was)
#define _UNLOCK_EX(...)        \
		preemption_pop(&_was); \
	}	__WHILE0
#else /* CONFIG_NO_SMP */
#define _LOCK_EX(self, tryacquire)                   \
	do {                                             \
		struct atomic_rwlock *_lock = lockfor(self); \
		preemption_flag_t _was;                      \
		for (;;) {                                   \
			preemption_pushoff(&_was);               \
			if likely_untraced (tryacquire(_lock))   \
				break;                               \
			preemption_pop(&_was);                   \
			task_tryyield_or_pause();                \
		}
#define _UNLOCK_EX(release)    \
		release(_lock);        \
		preemption_pop(&_was); \
	}	__WHILE0
#endif /* !CONFIG_NO_SMP */

#define LOCK_RD(self)                      \
	_LOCK_EX(self, atomic_rwlock_tryread); \
	COMPILER_READ_BARRIER()
#define LOCK_WR(self)                       \
	_LOCK_EX(self, atomic_rwlock_trywrite); \
	COMPILER_WRITE_BARRIER()
#define UNLOCK_RD()          \
	COMPILER_READ_BARRIER(); \
	_UNLOCK_EX(atomic_rwlock_endread)
#define UNLOCK_WR()           \
	COMPILER_WRITE_BARRIER(); \
	_UNLOCK_EX(atomic_rwlock_endwrite)


DECL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) u64
NOTHROW(FCALL FUNC(atomic64_read))(atomic64_t const *__restrict self) {
	u64 result;
	LOCK_RD(self);
	result = _atomic64_val(*self);
	UNLOCK_RD();
	return result;
}

DECL NOBLOCK ATTR_LEAF NONNULL((1)) void
NOTHROW(FCALL FUNC(atomic64_write))(atomic64_t *__restrict self,
                                    u64 value) {
	LOCK_WR(self);
	_atomic64_val(*self) = value;
	UNLOCK_WR();
}

DECL NOBLOCK ATTR_LEAF NONNULL((1)) bool
NOTHROW(FCALL FUNC(atomic64_cmpxch))(atomic64_t *__restrict self,
                                     u64 oldval, u64 newval) {
	bool result;
	LOCK_WR(self);
	result = _atomic64_val(*self) == oldval;
	if (result)
		_atomic64_val(*self) = newval;
	UNLOCK_WR();
	return result;
}

DECL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL FUNC(atomic64_cmpxch_val))(atomic64_t *__restrict self,
                                         u64 oldval, u64 newval) {
	u64 result;
	LOCK_WR(self);
	result = _atomic64_val(*self);
	if (result == oldval)
		_atomic64_val(*self) = newval;
	UNLOCK_WR();
	return result;
}

DECL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL FUNC(atomic64_xch))(atomic64_t *__restrict self,
                                  u64 value) {
	u64 result;
	LOCK_WR(self);
	result        = _atomic64_val(*self);
	_atomic64_val(*self) = value;
	UNLOCK_WR();
	return result;
}

DECL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL FUNC(atomic64_fetchadd))(atomic64_t *__restrict self,
                                       u64 value) {
	u64 result;
	LOCK_WR(self);
	result        = _atomic64_val(*self);
	_atomic64_val(*self) = result + value;
	UNLOCK_WR();
	return result;
}

DECL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL FUNC(atomic64_fetchand))(atomic64_t *__restrict self,
                                       u64 value) {
	u64 result;
	LOCK_WR(self);
	result        = _atomic64_val(*self);
	_atomic64_val(*self) = result & value;
	UNLOCK_WR();
	return result;
}

DECL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL FUNC(atomic64_fetchor))(atomic64_t *__restrict self,
                                      u64 value) {
	u64 result;
	LOCK_WR(self);
	result        = _atomic64_val(*self);
	_atomic64_val(*self) = result | value;
	UNLOCK_WR();
	return result;
}

DECL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL FUNC(atomic64_fetchxor))(atomic64_t *__restrict self,
                                       u64 value) {
	u64 result;
	LOCK_WR(self);
	result        = _atomic64_val(*self);
	_atomic64_val(*self) = result ^ value;
	UNLOCK_WR();
	return result;
}

DECL_END

#endif /* !ARCH_HAVE_ATOMIC64_PROTOTYPES */
#endif /* !ARCH_HAVE_ATOMIC64_SUPPORT_ALWAYS */

#endif /* !GUARD_KERNEL_SRC_SCHED_ATOMIC64_C */
