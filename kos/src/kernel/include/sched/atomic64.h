/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_ATOMIC64_H
#define GUARD_KERNEL_INCLUDE_SCHED_ATOMIC64_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/arch/atomic64.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

/* An API for  64-bit atomics  that defines a  u64+atomic_rwlock data  structure,
 * where the lock is used when the host doesn't support the cmpxchg8b instruction
 * on i386, always uses the lock when the host never supports 64-bit atomics, and
 * doesn't  even define the lock, and always just defines the raw 64-bit value if
 * the   host   always   supports   64-bit   atomics   (such   as   on    x86_64)
 * These are 3 configuration modes:
 *   - ARCH_HAVE_ATOMIC64_SUPPORT_NEVER:
 *         64-bit atomics are never supported and always have to be emulated
 *   - ARCH_HAVE_ATOMIC64_SUPPORT_ALWAYS:
 *         64-bit atomics are always supported and never have to be emulated
 *   - ARCH_HAVE_ATOMIC64_SUPPORT_DYNAMIC:
 *         64-bit atomic operations must  go through api functions  that
 *         dynamically get re-written based on native support determined
 *         at runtime.
 */


/* TODO: Also use `atomic64_t' for `struct fs::f_mode'
 *       Then gcc can stop generating fpu-instructions to facilitate atomic reads/writes */

#if (defined(ARCH_HAVE_ATOMIC64_SUPPORT_ALWAYS) + \
     defined(ARCH_HAVE_ATOMIC64_SUPPORT_NEVER) +  \
     defined(ARCH_HAVE_ATOMIC64_SUPPORT_DYNAMIC)) != 1
#error "Invalid arch-specific atomic64 support configuration"
#endif

DECL_BEGIN

#ifdef __CC__

#ifndef __atomic64_t_defined
#define __atomic64_t_defined
#ifdef __INTELLISENSE__
typedef struct {
	u64 _a_val;
} atomic64_t;
#define _atomic64_val(self) (self)._a_val
#define ATOMIC64_INIT(v)    { v }
#else /* __INTELLISENSE__ */
typedef u64 atomic64_t;
#define _atomic64_val(self) self
#define ATOMIC64_INIT(v)    v
#endif /* !__INTELLISENSE__ */

#define atomic64_init(self, v) (void)(_atomic64_val(*(self)) = (v))
#define atomic64_cinit(self, v)                    \
	(__hybrid_assert(_atomic64_val(*(self)) == 0), \
	 (__builtin_constant_p(v) && (v) == 0)         \
	 ? (void)0                                     \
	 : (void)(_atomic64_val(*(self)) = (v)))
#endif /* !__atomic64_t_defined */

/* NOTE: The read/write functions may be used to guaranty that reads/writes
 *       always return whole values in regards to other reads/writes to the
 *       same memory location that are also made using the atomic64* APIs. */

#ifndef ARCH_HAVE_ATOMIC64_PROTOTYPES
#ifdef ARCH_HAVE_ATOMIC64_SUPPORT_ALWAYS

/* Atomically read a 64-bit data word from `self' */
#define atomic64_read(self) \
	__hybrid_atomic_load(_atomic64_val(*(self)), __ATOMIC_SEQ_CST)

/* Atomically write a 64-bit data word to `self' */
#define atomic64_write(self, value) \
	__hybrid_atomic_store(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically compare-exchange a 64-bit data word from `self' */
#define atomic64_cmpxch(self, oldval, newval) \
	__hybrid_atomic_cmpxch(_atomic64_val(*(self)), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

/* Atomically compare-exchange a 64-bit data word from `self' */
#define atomic64_cmpxch_weak(self, oldval, newval) \
	__hybrid_atomic_cmpxch_weak(_atomic64_val(*(self)), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

/* Atomically compare-exchange a 64-bit data word from `self' */
#define atomic64_cmpxch_val(self, oldval, newval) \
	__hybrid_atomic_cmpxch_val(_atomic64_val(*(self)), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

/* Atomically exchange a 64-bit data word from `self' */
#define atomic64_xch(self, value) \
	__hybrid_atomic_xch(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically fetch-and-add a 64-bit data word from `self' */
#define atomic64_fetchadd(self, value) \
	__hybrid_atomic_fetchadd(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically fetch-and-and a 64-bit data word from `self' */
#define atomic64_fetchand(self, value) \
	__hybrid_atomic_fetchand(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically fetch-and-or a 64-bit data word from `self' */
#define atomic64_fetchor(self, value) \
	__hybrid_atomic_fetchor(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically fetch-and-xor a 64-bit data word from `self' */
#define atomic64_fetchxor(self, value) \
	__hybrid_atomic_fetchxor(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically add a 64-bit data word from `self' */
#define atomic64_add(self, value) \
	__hybrid_atomic_add(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically and a 64-bit data word from `self' */
#define atomic64_and(self, value) \
	__hybrid_atomic_and(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically or a 64-bit data word from `self' */
#define atomic64_or(self, value) \
	__hybrid_atomic_or(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

/* Atomically xor a 64-bit data word from `self' */
#define atomic64_xor(self, value) \
	__hybrid_atomic_xor(_atomic64_val(*(self)), value, __ATOMIC_SEQ_CST)

#else /* ARCH_HAVE_ATOMIC64_SUPPORT_ALWAYS */

/* Atomically read a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) u64
NOTHROW(FCALL atomic64_read)(atomic64_t const *__restrict self);

/* Atomically write a 64-bit data word to `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) void
NOTHROW(FCALL atomic64_write)(atomic64_t *__restrict self, u64 value);

/* Atomically compare-exchange a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) __BOOL
NOTHROW(FCALL atomic64_cmpxch)(atomic64_t *__restrict self,
                               u64 oldval, u64 newval);

/* Atomically compare-exchange a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_cmpxch_val)(atomic64_t *__restrict self,
                                   u64 oldval, u64 newval);

/* Atomically exchange a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64
NOTHROW(FCALL atomic64_xch)(atomic64_t *__restrict self, u64 value);

/* Atomically fetch-and-add a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchadd)(atomic64_t *__restrict self, u64 value);

/* Atomically fetch-and-and a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchand)(atomic64_t *__restrict self, u64 value);

/* Atomically fetch-and-or a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchor)(atomic64_t *__restrict self, u64 value);

/* Atomically fetch-and-xor a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64
NOTHROW(FCALL atomic64_fetchxor)(atomic64_t *__restrict self, u64 value);

/* Atomically add a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) void
NOTHROW(FCALL atomic64_add)(atomic64_t *__restrict self, u64 value);

/* Atomically and a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) void
NOTHROW(FCALL atomic64_and)(atomic64_t *__restrict self, u64 value);

/* Atomically or a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) void
NOTHROW(FCALL atomic64_or)(atomic64_t *__restrict self, u64 value);

/* Atomically xor a 64-bit data word from `self' */
FUNDEF NOBLOCK ATTR_LEAF NONNULL((1)) void
NOTHROW(FCALL atomic64_xor)(atomic64_t *__restrict self, u64 value);
#endif /* !ARCH_HAVE_ATOMIC64_SUPPORT_ALWAYS */
#endif /* !ARCH_HAVE_ATOMIC64_PROTOTYPES */

#ifndef atomic64_cmpxch_weak
#define atomic64_cmpxch_weak atomic64_cmpxch
#endif /* !atomic64_cmpxch_weak */

#ifndef atomic64_cmpxch_weak_val
#define atomic64_cmpxch_weak_val atomic64_cmpxch_val
#endif /* !atomic64_cmpxch_weak_val */


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_ATOMIC64_H */
