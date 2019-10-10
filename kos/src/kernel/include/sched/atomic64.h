/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ATOMIC64_H
#define GUARD_KERNEL_INCLUDE_SCHED_ATOMIC64_H 1

#include <kernel/compiler.h>

#include <kernel/arch/atomic64.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

/* An API for 64-bit atomics that defines a u64+atomic_rwlock data structure,
 * where the lock is used when the host doesn't support the cmpxchg8b instruction
 * on i386, always uses the lock when the host never supports 64-bit atomics, and
 * doesn't even define the lock, and always just defines the raw 64-bit value if
 * the host always supports 64-bit atomics (such as on x86_64)
 * These are 3 configuration modes:
 *   - CONFIG_ATOMIC64_SUPPORT_NEVER:
 *         64-bit atomics are never supported and always have to be emulated
 *   - CONFIG_ATOMIC64_SUPPORT_ALWAYS:
 *         64-bit atomics are always supported and never have to be emulated
 *   - CONFIG_ATOMIC64_SUPPORT_DYNAMIC:
 *         64-bit atomic operations must go through api functions that
 *         dynamically get re-written based on native support determined
 *         at runtime.
 */


/* TODO: Also use `struct atomic64' for `struct fs::f_mode'
 *       Then gcc can stop generating fpu-instructions to facilitate atomic reads/writes */

#if (defined(CONFIG_ATOMIC64_SUPPORT_ALWAYS) + \
     defined(CONFIG_ATOMIC64_SUPPORT_NEVER) +  \
     defined(CONFIG_ATOMIC64_SUPPORT_DYNAMIC)) != 1
#error "Invalid arch-specific atomic64 support configuration"
#endif


#ifndef CONFIG_ATOMIC64_SUPPORT_ALWAYS
#include <hybrid/sync/atomic-rwlock.h>
#endif /* !CONFIG_ATOMIC64_SUPPORT_ALWAYS */

#ifdef CONFIG_ATOMIC64_SUPPORT_NEVER
#include <sched/task.h> /* PREEMPTION_PUSHOFF() */
#endif /* !CONFIG_ATOMIC64_SUPPORT_NEVER */

DECL_BEGIN

#ifdef __CC__
struct atomic64 {
	WEAK u64             a_value; /* The atomic value */
#ifndef CONFIG_ATOMIC64_SUPPORT_ALWAYS
	struct atomic_rwlock a_lock;  /* Lock for `a_value'. */
#endif /* !CONFIG_ATOMIC64_SUPPORT_ALWAYS */
};

#ifndef CONFIG_ATOMIC64_SUPPORT_ALWAYS
#define atomic64_init(self, v) \
	((self)->a_value = (v),    \
	 atomic_rwlock_init(&(self)->a_lock))
#define atomic64_cinit(self, v)             \
	(__hybrid_assert((self)->a_value == 0), \
	 (__builtin_constant_p(v) && (v) == 0)  \
	 ? (void)0                              \
	 : (void)((self)->a_value = (v)),       \
	 atomic_rwlock_cinit(&(self)->a_lock))
#define ATOMIC64_INIT(v) { v, ATOMIC_RWLOCK_INIT }
#else /* !CONFIG_ATOMIC64_SUPPORT_ALWAYS */
#define atomic64_init(self, v) \
	((self)->a_value = (v))
#define atomic64_cinit(self, v)             \
	(__hybrid_assert((self)->a_value == 0), \
	 (__builtin_constant_p(v) && (v) == 0)  \
	 ? (void)0                              \
	 : (void)((self)->a_value = (v)))
#define ATOMIC64_INIT(v) { v }
#endif /* !CONFIG_ATOMIC64_SUPPORT_ALWAYS */

/* NOTE: The *_r variants must (consistently) be used with some given atomic64
 *       value when that value has to be accessible from interrupt handlers,
 *       meaning that these variants are re-entrant.
 *       This is done by disabling preemption before locking the internal lock
 *       when this has to be done, thus preventing interrupts from happening
 *       while modifying the atomic value.
 *       As such, if you know that preemption is currently disabled, you may
 *       also use the non-reentrant variants, and still be guarantied that the
 *       code will end up being reentrant.
 * NOTE: The read/write functions may be used to guaranty that reads/writes
 *       always return whole values in regards to other reads/writes to the
 *       same memory location. */

#if defined(CONFIG_ATOMIC64_SUPPORT_ALWAYS)

#define atomic64_read(self)                         __hybrid_atomic_load((self)->a_value, __ATOMIC_SEQ_CST)
#define atomic64_write(self, value)                 __hybrid_atomic_store((self)->a_value, value, __ATOMIC_SEQ_CST)
#define atomic64_cmpxch(self, oldval, newval)       __hybrid_atomic_cmpxch((self)->a_value, oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic64_cmpxch_val(self, oldval, newval)   __hybrid_atomic_cmpxch_val((self)->a_value, oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic64_xch(self, value)                   __hybrid_atomic_xch((self)->a_value, value, __ATOMIC_SEQ_CST)
#define atomic64_fetchadd(self, value)              __hybrid_atomic_fetchadd((self)->a_value, value, __ATOMIC_SEQ_CST)
#define atomic64_fetchand(self, value)              __hybrid_atomic_fetchand((self)->a_value, value, __ATOMIC_SEQ_CST)
#define atomic64_fetchor(self, value)               __hybrid_atomic_fetchor((self)->a_value, value, __ATOMIC_SEQ_CST)
#define atomic64_fetchxor(self, value)              __hybrid_atomic_fetchxor((self)->a_value, value, __ATOMIC_SEQ_CST)
#define atomic64_read_r(self)                       atomic64_read(self)
#define atomic64_write_r(self, value)               atomic64_write(self, value)
#define atomic64_cmpxch_r(self, oldval, newval)     atomic64_cmpxch(self, oldval, newval)
#define atomic64_cmpxch_val_r(self, oldval, newval) atomic64_cmpxch_val(self, oldval, newval)
#define atomic64_xch_r(self, value)                 atomic64_xch(self, value)
#define atomic64_fetchadd_r(self, value)            atomic64_fetchadd(self, value)
#define atomic64_fetchand_r(self, value)            atomic64_fetchand(self, value)
#define atomic64_fetchor_r(self, value)             atomic64_fetchor(self, value)
#define atomic64_fetchxor_r(self, value)            atomic64_fetchxor(self, value)

#elif defined(CONFIG_ATOMIC64_SUPPORT_NEVER)

FORCELOCAL NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64
NOTHROW(FCALL atomic64_read)(struct atomic64 *__restrict self) {
	u64 result;
	atomic_rwlock_read(&self->a_lock);
	result = self->a_value;
	atomic_rwlock_endread(&self->a_lock);
	return result;
}
FORCELOCAL NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64
NOTHROW(FCALL atomic64_read_r)(struct atomic64 *__restrict self) {
	u64 result;
	pflag_t was = PREEMPTION_PUSHOFF();
	atomic_rwlock_read(&self->a_lock);
	result = self->a_value;
	atomic_rwlock_endread(&self->a_lock);
	PREEMPTION_POP(was);
	return result;
}

#define atomic64_lock(self)     atomic_rwlock_write(&(self)->a_lock)
#define atomic64_unlock(self)   atomic_rwlock_endwrite(&(self)->a_lock)
FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) void
NOTHROW(FCALL atomic64_write)(struct atomic64 *__restrict self, u64 value) {
	atomic64_lock(self);
	self->a_value = value;
	atomic64_unlock(self);
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) __BOOL
NOTHROW(FCALL atomic64_cmpxch)(struct atomic64 *__restrict self,
                               u64 oldval, u64 newval) {
	__BOOL result;
	atomic64_lock(self);
	result = self->a_value == oldval;
	if (result)
		self->a_value = newval;
	atomic64_unlock(self);
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_cmpxch_val)(struct atomic64 *__restrict self,
                                   u64 oldval, u64 newval) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	if (result == oldval)
		self->a_value = newval;
	atomic64_unlock(self);
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_xch)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = value;
	atomic64_unlock(self);
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchadd)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result + value;
	atomic64_unlock(self);
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchand)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result & value;
	atomic64_unlock(self);
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchor)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result | value;
	atomic64_unlock(self);
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchxor)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result ^ value;
	atomic64_unlock(self);
	return result;
}

#undef atomic64_unlock
#undef atomic64_lock

#define REENTRANT_BEGIN \
	{                   \
		pflag_t _was = PREEMPTION_PUSHOFF();
#define REENTRANT_END         \
		PREEMPTION_POP(_was); \
	}
FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) void
NOTHROW(FCALL atomic64_write_r)(struct atomic64 *__restrict self, u64 value) {
	REENTRANT_BEGIN
	atomic64_write(self, value);
	REENTRANT_END
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) __BOOL
NOTHROW(FCALL atomic64_cmpxch_r)(struct atomic64 *__restrict self,
                                 u64 oldval, u64 newval) {
	__BOOL result;
	REENTRANT_BEGIN
	result = atomic64_cmpxch(self, oldval, newval);
	REENTRANT_END
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_cmpxch_val_r)(struct atomic64 *__restrict self,
                                     u64 oldval, u64 newval) {
	u64 result;
	REENTRANT_BEGIN
	result = atomic64_cmpxch_val(self, oldval, newval);
	REENTRANT_END
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_xch_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	result = atomic64_xch(self, value);
	REENTRANT_END
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchadd_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	result = atomic64_fetchadd(self, value);
	REENTRANT_END
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchand_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	result = atomic64_fetchand(self, value);
	REENTRANT_END
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchor_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	result = atomic64_fetchor(self, value);
	REENTRANT_END
	return result;
}

FORCELOCAL NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchxor_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	result = atomic64_fetchxor(self, value);
	REENTRANT_END
	return result;
}
#undef REENTRANT_BEGIN
#undef REENTRANT_END

#elif defined(CONFIG_ATOMIC64_SUPPORT_DYNAMIC)

FUNDEF NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64 NOTHROW(FCALL atomic64_read)(struct atomic64 *__restrict self);
FUNDEF NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64 NOTHROW(FCALL atomic64_read_r)(struct atomic64 *__restrict self);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) void NOTHROW(FCALL atomic64_write)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) void NOTHROW(FCALL atomic64_write_r)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) __BOOL NOTHROW(FCALL atomic64_cmpxch)(struct atomic64 *__restrict self, u64 oldval, u64 newval);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) __BOOL NOTHROW(FCALL atomic64_cmpxch_r)(struct atomic64 *__restrict self, u64 oldval, u64 newval);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_cmpxch_val)(struct atomic64 *__restrict self, u64 oldval, u64 newval);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_cmpxch_val_r)(struct atomic64 *__restrict self, u64 oldval, u64 newval);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_xch)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_xch_r)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_fetchadd)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_fetchadd_r)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_fetchand)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_fetchand_r)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_fetchor)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_fetchor_r)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_fetchxor)(struct atomic64 *__restrict self, u64 value);
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL atomic64_fetchxor_r)(struct atomic64 *__restrict self, u64 value);

#else
#error "Invalid arch-specific atomic64 support configuration"
#endif

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ATOMIC64_H */
