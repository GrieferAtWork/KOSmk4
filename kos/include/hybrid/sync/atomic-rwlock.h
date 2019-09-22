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
#ifndef __GUARD_HYBRID_SYNC_ATOMIC_RWLOCK_H
#define __GUARD_HYBRID_SYNC_ATOMIC_RWLOCK_H 1

#include "../../__stdinc.h"
#include "../typecore.h"
#include "../__atomic.h"
#include "../__assert.h"
#ifndef __INTELLISENSE__
#include "../sched/__yield.h"
#endif /* !__INTELLISENSE__ */

__DECL_BEGIN

#if __SIZEOF_POINTER__ == 4
#define __ATOMIC_RWLOCK_RMASK __UINT32_C(0x7fffffff)
#define __ATOMIC_RWLOCK_WFLAG __UINT32_C(0x80000000)
#elif __SIZEOF_POINTER__ == 8
#define __ATOMIC_RWLOCK_RMASK __UINT64_C(0x7fffffffffffffff)
#define __ATOMIC_RWLOCK_WFLAG __UINT64_C(0x8000000000000000)
#else
#error "Unsupported sizeof(void *)"
#endif
#define __ATOMIC_RWLOCK_SIZE  __SIZEOF_POINTER__

#ifdef __CC__
struct __ATTR_PACKED atomic_rwlock {
	__UINTPTR_TYPE__   arw_lock;
};

#define ATOMIC_RWLOCK_INIT              {0}
#define ATOMIC_RWLOCK_INIT_READ         {1}
#define ATOMIC_RWLOCK_INIT_WRITE        {__ATOMIC_RWLOCK_WFLAG}
#define atomic_rwlock_cinit(self)       (void)__hybrid_assert((self)->arw_lock == 0)
#define atomic_rwlock_cinit_read(self)  (void)(__hybrid_assert((self)->arw_lock == 0),(self)->arw_lock = 1)
#define atomic_rwlock_cinit_write(self) (void)(__hybrid_assert((self)->arw_lock == 0),(self)->arw_lock = __ATOMIC_RWLOCK_WFLAG)
#define atomic_rwlock_init(self)        (void)((self)->arw_lock = 0)
#define atomic_rwlock_init_read(self)   (void)((self)->arw_lock = 1)
#define atomic_rwlock_init_write(self)  (void)((self)->arw_lock = __ATOMIC_RWLOCK_WFLAG)
#define DEFINE_ATOMIC_RWLOCK(name)       struct atomic_rwlock name = ATOMIC_RWLOCK_INIT

#define atomic_rwlock_reading(self)    (__hybrid_atomic_load((self)->arw_lock,__ATOMIC_ACQUIRE) != 0)
#define atomic_rwlock_writing(self)    (__hybrid_atomic_load((self)->arw_lock,__ATOMIC_ACQUIRE) & __ATOMIC_RWLOCK_WFLAG)
#define atomic_rwlock_canread(self)  (!(__hybrid_atomic_load((self)->arw_lock,__ATOMIC_ACQUIRE) & __ATOMIC_RWLOCK_WFLAG))
#define atomic_rwlock_canwrite(self)   (__hybrid_atomic_load((self)->arw_lock,__ATOMIC_ACQUIRE) == 0)

/* Acquire an exclusive read/write lock. */
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_tryread)(struct atomic_rwlock *__restrict __self);
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_trywrite)(struct atomic_rwlock *__restrict __self);
__LOCAL void (atomic_rwlock_read)(struct atomic_rwlock *__restrict __self);
__LOCAL void (atomic_rwlock_write)(struct atomic_rwlock *__restrict __self);
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_read_nx)(struct atomic_rwlock *__restrict __self);
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_write_nx)(struct atomic_rwlock *__restrict __self);
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

/* Try to upgrade a read-lock to a write-lock. Return `FALSE' upon failure. */
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_tryupgrade)(struct atomic_rwlock *__restrict __self);

/* NOTE: The lock is always upgraded, but when `FALSE' is returned, no lock
 *       may have been held temporarily, meaning that the caller should
 *       re-load local copies of affected resources. */
__LOCAL __ATTR_WUNUSED __BOOL (atomic_rwlock_upgrade)(struct atomic_rwlock *__restrict __self);

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
/* NOTE: The lock is always upgraded for `return != 0', but when `2' is returned,
 *       no lock may have been held temporarily, meaning that the caller should
 *       re-load local copies of affected resources.
 * NOTE: When `0' is returned, the original read-lock created by the caller has
 *       already been released. */
__LOCAL __ATTR_WUNUSED unsigned int __NOTHROW(atomic_rwlock_upgrade_nx)(struct atomic_rwlock *__restrict __self);
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

/* Downgrade a write-lock to a read-lock (Always succeeds). */
__LOCAL void __NOTHROW(atomic_rwlock_downgrade)(struct atomic_rwlock *__restrict __self);

/* End reading/writing/either.
 * @return: true:  The lock has become free.
 * @return: false: The lock is still held by something. */
__LOCAL void __NOTHROW(atomic_rwlock_endwrite)(struct atomic_rwlock *__restrict __self);
__LOCAL __BOOL __NOTHROW(atomic_rwlock_endread)(struct atomic_rwlock *__restrict __self);
__LOCAL __BOOL __NOTHROW(atomic_rwlock_end)(struct atomic_rwlock *__restrict __self);




#ifndef __INTELLISENSE__
__LOCAL void __NOTHROW(atomic_rwlock_endwrite)(struct atomic_rwlock *__restrict __self) {
	__COMPILER_BARRIER();
#ifdef NDEBUG
	__hybrid_atomic_store(__self->arw_lock, 0, __ATOMIC_RELEASE);
#else /* NDEBUG */
	__UINTPTR_TYPE__ __f;
	do {
		__f = __hybrid_atomic_load(__self->arw_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(__f & __ATOMIC_RWLOCK_WFLAG, "Lock isn't in write-mode (%x)", __f);
	} while (!__hybrid_atomic_cmpxch_weak(__self->arw_lock, __f, 0, __ATOMIC_RELEASE, __ATOMIC_RELAXED));
#endif /* !NDEBUG */
}

__LOCAL __BOOL __NOTHROW(atomic_rwlock_endread)(struct atomic_rwlock *__restrict __self) {
	__COMPILER_READ_BARRIER();
#ifdef NDEBUG
	return __hybrid_atomic_decfetch(__self->arw_lock, __ATOMIC_RELEASE) == 0;
#else /* NDEBUG */
	__UINTPTR_TYPE__ __f;
	do {
		__f = __hybrid_atomic_load(__self->arw_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(!(__f & __ATOMIC_RWLOCK_WFLAG),"Lock is in write-mode (%x)",__f);
		__hybrid_assertf(__f != 0, "Lock isn't held by anyone");
	} while (!__hybrid_atomic_cmpxch_weak(__self->arw_lock, __f, __f - 1, __ATOMIC_RELEASE, __ATOMIC_RELAXED));
	return __f == 1;
#endif /* !NDEBUG */
}

__LOCAL __BOOL __NOTHROW(atomic_rwlock_end)(struct atomic_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __temp, __newval;
	__COMPILER_BARRIER();
	do {
		__temp = __hybrid_atomic_load(__self->arw_lock, __ATOMIC_ACQUIRE);
		if __untraced(__temp & __ATOMIC_RWLOCK_WFLAG) {
			__hybrid_assert(!(__temp&__ATOMIC_RWLOCK_RMASK));
			__newval = 0;
		} else {
			__hybrid_assertf(__temp != 0, "No remaining read-locks");
			__newval = __temp-1;
		}
	} while (!__hybrid_atomic_cmpxch_weak(__self->arw_lock, __temp, __newval, __ATOMIC_RELEASE, __ATOMIC_RELAXED));
	return __newval == 0;
}

__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_tryread)(struct atomic_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __temp;
	do {
		__temp = __hybrid_atomic_load(__self->arw_lock, __ATOMIC_ACQUIRE);
		if __untraced(__temp & __ATOMIC_RWLOCK_WFLAG)
			return 0;
		__hybrid_assert((__temp&__ATOMIC_RWLOCK_RMASK) != __ATOMIC_RWLOCK_RMASK);
	} while (!__hybrid_atomic_cmpxch_weak(__self->arw_lock, __temp, __temp + 1, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	__COMPILER_READ_BARRIER();
	return 1;
}

__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_trywrite)(struct atomic_rwlock *__restrict __self) {
	if __untraced(!__hybrid_atomic_cmpxch(__self->arw_lock, 0, __ATOMIC_RWLOCK_WFLAG, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
}

__LOCAL void (atomic_rwlock_read)(struct atomic_rwlock *__restrict __self) {
	while (!atomic_rwlock_tryread(__self))
		__hybrid_yield();
	__COMPILER_READ_BARRIER();
}

__LOCAL void (atomic_rwlock_write)(struct atomic_rwlock *__restrict __self) {
	while (!atomic_rwlock_trywrite(__self))
		__hybrid_yield();
	__COMPILER_BARRIER();
}

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_read_nx)(struct atomic_rwlock *__restrict __self) {
	while (!atomic_rwlock_tryread(__self)) {
		if __unlikely(!__hybrid_yield_nx())
			return 0;
	}
	__COMPILER_READ_BARRIER();
	return 1;
}

__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_write_nx)(struct atomic_rwlock *__restrict __self) {
	while (!atomic_rwlock_trywrite(__self)) {
		if __unlikely(!__hybrid_yield_nx())
			return 0;
	}
	__COMPILER_READ_BARRIER();
	return 1;
}
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

__LOCAL __ATTR_WUNUSED __BOOL __NOTHROW(atomic_rwlock_tryupgrade)(struct atomic_rwlock *__restrict __self) {
	__UINTPTR_TYPE__ __temp;
	do {
		__temp = __hybrid_atomic_load(__self->arw_lock, __ATOMIC_ACQUIRE);
		if __untraced(__temp != 1)
			return 0;
	} while (!__hybrid_atomic_cmpxch_weak(__self->arw_lock, __temp, __ATOMIC_RWLOCK_WFLAG,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
	__COMPILER_WRITE_BARRIER();
	return 1;
}

__LOCAL __ATTR_WUNUSED __BOOL (atomic_rwlock_upgrade)(struct atomic_rwlock *__restrict __self) {
	if __untraced(atomic_rwlock_tryupgrade(__self))
		return 1;
	atomic_rwlock_endread(__self);
	atomic_rwlock_write(__self);
	return 0;
}

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_WUNUSED unsigned int
__NOTHROW(atomic_rwlock_upgrade_nx)(struct atomic_rwlock *__restrict __self) {
	if __untraced(atomic_rwlock_tryupgrade(__self))
		return 1;
	atomic_rwlock_endread(__self);
	if __unlikely(!atomic_rwlock_write_nx(__self))
		return 0;
	return 2;
}
#endif /* __KERNEL__ && __KOS_VERSION__ >= 400 */

__LOCAL void __NOTHROW(atomic_rwlock_downgrade)(struct atomic_rwlock *__restrict __self) {
#ifdef NDEBUG
	__COMPILER_WRITE_BARRIER();
	__hybrid_atomic_store(__self->arw_lock, 1, __ATOMIC_ACQ_REL);
#else /* NDEBUG */
	__UINTPTR_TYPE__ __f;
	__COMPILER_WRITE_BARRIER();
	do {
		__f = __hybrid_atomic_load(__self->arw_lock, __ATOMIC_ACQUIRE);
		__hybrid_assertf(__f == __ATOMIC_RWLOCK_WFLAG, "Lock not in write-mode (%x)", __f);
	} while (!__hybrid_atomic_cmpxch_weak(__self->arw_lock, __f, 1,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_RELAXED));
#endif /* !NDEBUG */
}
#endif /* !__INTELLISENSE__ */
#endif /* __CC__ */

#ifdef __ASSEMBLER__
#if defined(__x86_64__)

#ifndef LOCK_PREFIX
#define LOCK_PREFIX lock;
#endif /* !LOCK_PREFIX */

/* Clobber: \clobber, %rax
 * @return: true:  ZF=1
 * @return: false: ZF=0 */
.macro atomic_rwlock_trywrite __self, clobber=%rcx, rax_is_zero=0
.if \rax_is_zero == 0
	xorq  %rax, %rax
.endif
	movq  $(__ATOMIC_RWLOCK_WFLAG), \clobber
	LOCK_PREFIX cmpxchgq \clobber, \__self
.endm

/* WARNING: Clobber: \clobber, %rax
 * @return: true:  ZF=1
 * @return: false: ZF=0 */
.macro atomic_rwlock_tryread __self, clobber=%rcx
995:
	movq  \__self, %rax
	testq $(__ATOMIC_RWLOCK_WFLAG), %rax
	jnz   994f
	leaq  1(%rax), \clobber
	LOCK_PREFIX cmpxchgq \clobber, \__self
	jnz   995b
994:
.endm


/* WARNING: Clobber: \clobber, %eax */
.macro atomic_rwlock_write __self, clobber=%rcx, rax_is_zero=0, yield=''
996:
	atomic_rwlock_trywrite \__self, \clobber, \rax_is_zero
.ifc \yield,''
	jnz    996b
.else
	jz     997f
	call   \yield
	jmp    996b
997:
.endif
.endm

/* WARNING: Clobber: \clobber, %rax */
.macro atomic_rwlock_read __self, clobber=%rcx, yield=''
996:
	atomic_rwlock_tryread \__self, \clobber
.ifc \yield,''
	jnz    996b
.else
	jz     997f
	call   \yield
	jmp    996b
997:
.endif
.endm

.macro atomic_rwlock_endread __self
	LOCK_PREFIX decq \__self
.endm
.macro atomic_rwlock_endwrite __self
	movq   $0, \__self
.endm

#elif defined(__i386__)

#ifndef LOCK_PREFIX
#define LOCK_PREFIX lock;
#endif /* !LOCK_PREFIX */


/* Clobber: \clobber, %eax
 * @return: true:  ZF=1
 * @return: false: ZF=0 */
.macro atomic_rwlock_trywrite __self, clobber=%ecx, eax_is_zero=0
.if \eax_is_zero == 0
	xorl  %eax, %eax
.endif
	movl  $(__ATOMIC_RWLOCK_WFLAG), \clobber
	LOCK_PREFIX cmpxchgl \clobber, \__self
.endm

/* WARNING: Clobber: \clobber, %eax
 * @return: true:  ZF=1
 * @return: false: ZF=0 */
.macro atomic_rwlock_tryread __self, clobber=%ecx
995:
	movl  \__self, %eax
	testl $(__ATOMIC_RWLOCK_WFLAG), %eax
	jnz   994f
	leal  1(%eax), \clobber
	LOCK_PREFIX cmpxchgl \clobber, \__self
	jnz   995b
994:
.endm


/* WARNING: Clobber: \clobber, %eax */
.macro atomic_rwlock_write __self, clobber=%ecx, eax_is_zero=0, yield=''
996:
	atomic_rwlock_trywrite \__self, \clobber, \eax_is_zero
.ifc \yield,''
	jnz    996b
.else
	jz     997f
	call   \yield
	jmp    996b
997:
.endif
.endm

/* WARNING: Clobber: \clobber, %eax */
.macro atomic_rwlock_read __self, clobber=%ecx, yield=''
996:
	atomic_rwlock_tryread \__self, \clobber
.ifc \yield,''
	jnz    996b
.else
	jz     997f
	call   \yield
	jmp    996b
997:
.endif
.endm

.macro atomic_rwlock_endread __self
	LOCK_PREFIX decl \__self
.endm
.macro atomic_rwlock_endwrite __self
	movl   $0, \__self
.endm
#endif
#endif /* __ASSEMBLER__ */

#if !defined(__INTELLISENSE__) && !defined(__NO_builtin_expect)
#define atomic_rwlock_tryread(__self)    __builtin_expect(atomic_rwlock_tryread(__self), 1)
#define atomic_rwlock_trywrite(__self)   __builtin_expect(atomic_rwlock_trywrite(__self), 1)
#define atomic_rwlock_tryupgrade(__self) __builtin_expect(atomic_rwlock_tryupgrade(__self), 1)
#define atomic_rwlock_upgrade(__self)    __builtin_expect(atomic_rwlock_upgrade(__self), 1)
#endif /* !__INTELLISENSE__ && !__NO_builtin_expect */

#ifdef __DEFINE_SYNC_RWLOCK
__DEFINE_SYNC_RWLOCK(struct atomic_rwlock,
                     atomic_rwlock_tryread,
                     atomic_rwlock_read,
                     atomic_rwlock_read_nx,
                     atomic_rwlock_endread,
                     atomic_rwlock_reading,
                     atomic_rwlock_canread,
                     atomic_rwlock_trywrite,
                     atomic_rwlock_write,
                     atomic_rwlock_write_nx,
                     atomic_rwlock_endwrite,
                     atomic_rwlock_writing,
                     atomic_rwlock_canwrite,
                     atomic_rwlock_end,
                     atomic_rwlock_tryupgrade,
                     atomic_rwlock_upgrade,
                     atomic_rwlock_upgrade_nx,
                     atomic_rwlock_downgrade)
#endif /* __DEFINE_SYNC_RWLOCK */

__DECL_END

#endif /* !__GUARD_HYBRID_SYNC_ATOMIC_RWLOCK_H */
