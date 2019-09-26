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
#ifndef GUARD_KERNEL_SRC_SCHED_ATOMIC64_C
#define GUARD_KERNEL_SRC_SCHED_ATOMIC64_C 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <sched/atomic64.h>

#ifdef CONFIG_ATOMIC64_SUPPORT_DYNAMIC
#include <stdbool.h>
#include <sched/task.h>

DECL_BEGIN

INTERN NOBLOCK ATTR_LEAF WUNUSED ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_read)(struct atomic64 *__restrict self) {
	u64 result;
	atomic_rwlock_read(&self->a_lock);
	result = self->a_value;
	atomic_rwlock_endread(&self->a_lock);
	return result;
}

INTERN NOBLOCK ATTR_LEAF WUNUSED ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_read_r)(struct atomic64 *__restrict self) {
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

#define REENTRANT_BEGIN \
	{                   \
		pflag_t _was = PREEMPTION_PUSHOFF();
#define REENTRANT_END         \
		PREEMPTION_POP(_was); \
	}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) void
NOTHROW(FCALL emulated_atomic64_write)(struct atomic64 *__restrict self, u64 value) {
	atomic64_lock(self);
	self->a_value = value;
	atomic64_unlock(self);
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) void
NOTHROW(FCALL emulated_atomic64_write_r)(struct atomic64 *__restrict self, u64 value) {
	REENTRANT_BEGIN
	atomic64_lock(self);
	self->a_value = value;
	atomic64_unlock(self);
	REENTRANT_END
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) bool
NOTHROW(FCALL emulated_atomic64_cmpxch)(struct atomic64 *__restrict self,
                                        u64 oldval, u64 newval) {
	bool result;
	atomic64_lock(self);
	result = self->a_value == oldval;
	if (result)
		self->a_value = newval;
	atomic64_unlock(self);
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) bool
NOTHROW(FCALL emulated_atomic64_cmpxch_r)(struct atomic64 *__restrict self,
                                          u64 oldval, u64 newval) {
	bool result;
	REENTRANT_BEGIN
	atomic64_lock(self);
	result = self->a_value == oldval;
	if (result)
		self->a_value = newval;
	atomic64_unlock(self);
	REENTRANT_END
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_cmpxch_val)(struct atomic64 *__restrict self,
                                            u64 oldval, u64 newval) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	if (result == oldval)
		self->a_value = newval;
	atomic64_unlock(self);
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_cmpxch_val_r)(struct atomic64 *__restrict self,
                                              u64 oldval, u64 newval) {
	u64 result;
	REENTRANT_BEGIN
	atomic64_lock(self);
	result = self->a_value;
	if (result == oldval)
		self->a_value = newval;
	atomic64_unlock(self);
	REENTRANT_END
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_xch)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = value;
	atomic64_unlock(self);
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_xch_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = value;
	atomic64_unlock(self);
	REENTRANT_END
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_fetchadd)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result + value;
	atomic64_unlock(self);
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_fetchadd_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result + value;
	atomic64_unlock(self);
	REENTRANT_END
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_fetchand)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result & value;
	atomic64_unlock(self);
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_fetchand_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result & value;
	atomic64_unlock(self);
	REENTRANT_END
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_fetchor)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result | value;
	atomic64_unlock(self);
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_fetchor_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result | value;
	atomic64_unlock(self);
	REENTRANT_END
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_fetchxor)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result ^ value;
	atomic64_unlock(self);
	return result;
}

INTERN NOBLOCK ATTR_LEAF ATTR_NOINLINE NONNULL((1)) u64
NOTHROW(FCALL emulated_atomic64_fetchxor_r)(struct atomic64 *__restrict self, u64 value) {
	u64 result;
	REENTRANT_BEGIN
	atomic64_lock(self);
	result = self->a_value;
	self->a_value = result ^ value;
	atomic64_unlock(self);
	REENTRANT_END
	return result;
}





DECL_END

#endif /* CONFIG_ATOMIC64_SUPPORT_DYNAMIC */

#endif /* !GUARD_KERNEL_SRC_SCHED_ATOMIC64_C */
