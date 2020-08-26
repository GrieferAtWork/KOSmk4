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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_MISC_ATOMIC_REF_H
#define GUARD_KERNEL_INCLUDE_MISC_ATOMIC_REF_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/__atomic.h>
#include <hybrid/__assert.h>

#ifdef __CC__
DECL_BEGIN

#ifdef __cplusplus
extern "C++" {


/* Atomic reference pointer.
 * This is a special type of pointer that allows for a non-blocking, atomic read+incref
 * operation, while still implementing an atomic-exchange, as well as atomic-compare-exchange,
 * while all-the-while allowing for references to be traced correctly.
 * Kernel-space + CONFIG_NO_SMP:
 *  - Simple implementation that uses PREEMPTION_PUSHOFF()
 * Kernel-space + !CONFIG_NO_SMP:
 *  - read+incref:
 *    >> PREEMPTION_PUSHOFF();
 *    >> COMPILER_WRITE_BARRIER();
 *    >> ATOMIC_FETCHING(in_use);
 *    >> result = incref(pointer);
 *    >> ATOMIC_FETCHDEG(in_use);
 *    >> COMPILER_WRITE_BARRIER();
 *    >> PREEMPTION_POP();
 *    >> return result;
 *  - atomic-exchange:
 *    >> if (PREEMPTION_ENABLED()) {
 *    >>     old_ptr = ATOMIC_XCH(pointer, incref(new_pointer));
 *    >>     while (ATOMIC_READ(in_use) != 0)
 *    >>         task_yield(); // task_yield is guarantied to be NOEXCEPT in this case, because
 *    >>                       // we already confirmed that preemption is enabled, meaning that
 *    >>                       // it will never throw an E_WOULDBLOCK exception.
 *    >>                       // By waiting until `in_use' drops to 0 here, we ensure that any
 *    >>                       // thread that may have potentially read the old pointer before
 *    >>                       // we were able to exchange it was still able to incref() it
 *    >>                       // before we decref it below, guarantying consistency.
 *    >>     decref(old_ptr);
 *    >> } else {
 *    >>     // Because we're always disabling preemption before reading, we are guarantied
 *    >>     // that no other thread on the same CPU is holding a lock to `in_use', so that
 *    >>     // field being non-zero _has_ to mean some other CPU accessing the pointer.
 *    >>     old_ptr = ATOMIC_XCH(pointer, incref(new_pointer));
 *    >>     while (ATOMIC_READ(in_use) != 0)
 *    >>         task_pause(); // Once this turns 0, we know that no other CPU is still
 *    >>                       // within the read-block, yet to incref() the old pointer
 *    >>     decref(old_ptr);
 *    >> }
 *    Because of the similarity of the PREEMPTION_ENABLED() true/false branches, we can also
 *    simply use a single path that uses `task_tryyield_or_pause()' to synchronize, which
 *    is essentially the same as `PREEMPTION_ENABLED() ? task_yield() : task_pause()'
 *    >> old_ptr = ATOMIC_XCH(pointer,incref(new_pointer));
 *    >> while (ATOMIC_READ(in_use) != 0)
 *    >>     task_tryyield_or_pause();
 *    >> decref(old_ptr);
 */
#define ATOMIC_REF(...)  atomic_ref< __VA_ARGS__ >
template<class T> struct atomic_ref {

#ifndef CONFIG_NO_SMP
#define atomic_ref_init(self, p)  ((self)->m_pointer = (p), (self)->m_inuse = 0)
#define atomic_ref_cinit(self, p) ((self)->m_pointer = (p), __hybrid_assert((self)->m_inuse == 0))
#define ATOMIC_REF_INIT(p)        { p, 0}
#else /* !CONFIG_NO_SMP */
#define atomic_ref_init(self, p)  ((self)->m_pointer = (p))
#define atomic_ref_cinit(self, p) ((self)->m_pointer = (p))
#define ATOMIC_REF_INIT(p)        { p }
#endif /* CONFIG_NO_SMP */
#define atomic_ref_fini(self)       decref((self)->m_pointer)

	WEAK REF T      *m_pointer; /* [1..1][lock(COMPLEX(m_inuse))] The pointed-to object. */
#ifndef CONFIG_NO_SMP
	WEAK uintptr_t   m_inuse;   /* Cross-CPU is-in-use tracking */
#endif /* !CONFIG_NO_SMP */

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER ATTR_LEAF NOBLOCK ATTR_RETNONNULL WUNUSED REF T *KCALL get() __CXX_NOEXCEPT {
		REF T *result;
		pflag_t was;
		was = PREEMPTION_PUSHOFF();
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchinc(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		COMPILER_READ_BARRIER();
		result = this->m_pointer;
		COMPILER_READ_BARRIER();
		REFCNT_METHODS(T)::incref(result);
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchdec(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
		return result;
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER NOPREEMPT ATTR_LEAF NOBLOCK ATTR_RETNONNULL WUNUSED REF T *KCALL get_nopr() __CXX_NOEXCEPT {
		REF T *result;
		__hybrid_assert(!PREEMPTION_ENABLED());
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchinc(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		COMPILER_READ_BARRIER();
		result = this->m_pointer;
		COMPILER_READ_BARRIER();
		REFCNT_METHODS(T)::incref(result);
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchdec(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		return result;
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER NONNULL_CXX((1)) NOBLOCK_IF(!PREEMPTION_ENABLED())
	void KCALL set(T *__restrict new_pointer) __CXX_NOEXCEPT {
		REF T *old_pointer;
		old_pointer = this->exchange(new_pointer);
		REFCNT_METHODS(T)::decref(old_pointer);
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER NONNULL_CXX((1)) NOBLOCK_IF(!PREEMPTION_ENABLED())
	void KCALL set_inherit_new(REF T *__restrict new_pointer) __CXX_NOEXCEPT {
		REF T *old_pointer;
		old_pointer = this->exchange_inherit_new(new_pointer);
		REFCNT_METHODS(T)::decref(old_pointer);
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER ATTR_LEAF ATTR_RETNONNULL WUNUSED NONNULL_CXX((1)) NOBLOCK_IF(!PREEMPTION_ENABLED())
	REF T *KCALL exchange(T *__restrict new_pointer) __CXX_NOEXCEPT {
		REFCNT_METHODS(T)::incref(new_pointer);
		return exchange_inherit_new(new_pointer);
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER ATTR_LEAF ATTR_RETNONNULL WUNUSED NONNULL_CXX((1)) NOBLOCK_IF(!PREEMPTION_ENABLED())
	REF T *KCALL exchange_inherit_new(REF T *__restrict new_pointer) __CXX_NOEXCEPT {
		REF T *old_pointer;
#ifdef CONFIG_NO_SMP
		pflag_t was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		old_pointer = __hybrid_atomic_xch(this->m_pointer,
		                                  new_pointer,
		                                  __ATOMIC_SEQ_CST);
#ifndef CONFIG_NO_SMP
		while (__hybrid_atomic_load(this->m_inuse, __ATOMIC_ACQUIRE))
			task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
		return old_pointer;
	}

	/* Atomic compare-exchange */
	__CXX_CLASSMEMBER NONNULL_CXX((1, 2)) NOBLOCK_IF(!PREEMPTION_ENABLED())
	bool KCALL cmpxch(T *__restrict old_pointer,
	                  T *__restrict new_pointer) __CXX_NOEXCEPT {
#ifdef CONFIG_NO_SMP
		pflag_t was;
#endif /* CONFIG_NO_SMP */
		REFCNT_METHODS(T)::incref(new_pointer);
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		if (!__hybrid_atomic_cmpxch(this->m_pointer,
		                            old_pointer,
		                            new_pointer,
		                            __ATOMIC_SEQ_CST,
		                            __ATOMIC_SEQ_CST)) {
#ifdef CONFIG_NO_SMP
			PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
			REFCNT_METHODS(T)::decref_nokill(new_pointer);
			return false;
		}
#ifndef CONFIG_NO_SMP
		while (__hybrid_atomic_load(this->m_inuse, __ATOMIC_ACQUIRE))
			task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
		REFCNT_METHODS(T)::decref(old_pointer);
		return true;
	}

	/* Atomic compare-exchange */
	__CXX_CLASSMEMBER NONNULL_CXX((1, 2)) NOBLOCK_IF(!PREEMPTION_ENABLED())
	bool KCALL cmpxch_inherit_new(T *__restrict old_pointer,
	                              /*inherit(on_success)*/ REF T *__restrict new_pointer) __CXX_NOEXCEPT {
#ifdef CONFIG_NO_SMP
		pflag_t was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		if (!__hybrid_atomic_cmpxch(this->m_pointer,
		                            old_pointer,
		                            new_pointer,
		                            __ATOMIC_SEQ_CST,
		                            __ATOMIC_SEQ_CST)) {
#ifdef CONFIG_NO_SMP
			PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
			return false;
		}
#ifndef CONFIG_NO_SMP
		while (__hybrid_atomic_load(this->m_inuse, __ATOMIC_ACQUIRE))
			task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
		REFCNT_METHODS(T)::decref(old_pointer);
		return true;
	}
};

#define XATOMIC_REF_STRUCT(...) xatomic_ref_struct< __VA_ARGS__ >
#define XATOMIC_REF(...)        xatomic_ref< __VA_ARGS__ >
template<class T> struct xatomic_ref_struct {
	WEAK REF T      *m_pointer; /* [0..1][lock(COMPLEX(m_inuse))] The pointed-to object. */
#ifndef CONFIG_NO_SMP
	WEAK uintptr_t   m_inuse;   /* Cross-CPU is-in-use tracking */
#endif /* !CONFIG_NO_SMP */
};

template<class T> struct xatomic_ref {

#ifndef CONFIG_NO_SMP
#define xatomic_ref_init(self, p)  ((self)->m_pointer = (p), (self)->m_inuse = 0)
#define xatomic_ref_cinit(self, p) ((self)->m_pointer = (p), __hybrid_assert((self)->m_inuse == 0))
#define XATOMIC_REF_INIT(p)        { p, 0}
#else /* !CONFIG_NO_SMP */
#define xatomic_ref_init(self, p)  ((self)->m_pointer = (p))
#define xatomic_ref_cinit(self, p) ((self)->m_pointer = (p))
#define XATOMIC_REF_INIT(p)        { p }
#endif /* CONFIG_NO_SMP */
#define xatomic_ref_fini(self)      xdecref((self)->m_pointer)

	WEAK REF T      *m_pointer; /* [0..1][lock(COMPLEX(m_inuse))] The pointed-to object. */
#ifndef CONFIG_NO_SMP
	WEAK uintptr_t   m_inuse;   /* Cross-CPU is-in-use tracking */
#endif /* !CONFIG_NO_SMP */

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER NOBLOCK void KCALL clear() __CXX_NOEXCEPT {
		set_inherit_new(__NULLPTR);
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER ATTR_LEAF NOBLOCK WUNUSED REF T *KCALL get() __CXX_NOEXCEPT {
		REF T *result;
		pflag_t was;
		was = PREEMPTION_PUSHOFF();
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchinc(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		COMPILER_READ_BARRIER();
		result = this->m_pointer;
		COMPILER_READ_BARRIER();
		if (result)
			REFCNT_METHODS(T)::incref(result);
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchdec(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
		return result;
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER ATTR_LEAF NOBLOCK WUNUSED REF T *KCALL get_nopr() __CXX_NOEXCEPT {
		REF T *result;
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchinc(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		COMPILER_READ_BARRIER();
		result = this->m_pointer;
		COMPILER_READ_BARRIER();
		if (result)
			REFCNT_METHODS(T)::incref(result);
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchdec(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		return result;
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER NOBLOCK_IF(!PREEMPTION_ENABLED())
	void KCALL set(T *new_pointer) __CXX_NOEXCEPT {
		REF T *old_pointer;
		old_pointer = this->exchange(new_pointer);
		if (old_pointer)
			REFCNT_METHODS(T)::decref(old_pointer);
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER NOBLOCK_IF(!PREEMPTION_ENABLED())
	void KCALL set_inherit_new(REF T *new_pointer) __CXX_NOEXCEPT {
		REF T *old_pointer;
		old_pointer = this->exchange_inherit_new(new_pointer);
		if (old_pointer)
			REFCNT_METHODS(T)::decref(old_pointer);
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER ATTR_LEAF WUNUSED NOBLOCK_IF(!PREEMPTION_ENABLED())
	REF T *KCALL exchange(T *new_pointer) __CXX_NOEXCEPT {
		if (new_pointer)
			REFCNT_METHODS(T)::incref(new_pointer);
		return exchange_inherit_new(new_pointer);
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER ATTR_LEAF WUNUSED NOBLOCK_IF(!PREEMPTION_ENABLED())
	REF T *KCALL exchange_inherit_new(REF T *new_pointer) __CXX_NOEXCEPT {
		REF T *old_pointer;
#ifdef CONFIG_NO_SMP
		pflag_t was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		old_pointer = __hybrid_atomic_xch(this->m_pointer,
		                                  new_pointer,
		                                  __ATOMIC_SEQ_CST);
#ifndef CONFIG_NO_SMP
		while (__hybrid_atomic_load(this->m_inuse, __ATOMIC_ACQUIRE))
			task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
		return old_pointer;
	}

	/* Atomic compare-exchange */
	__CXX_CLASSMEMBER NOBLOCK_IF(!PREEMPTION_ENABLED())
	bool KCALL cmpxch(T *old_pointer,
	                  T *new_pointer) __CXX_NOEXCEPT {
#ifdef CONFIG_NO_SMP
		pflag_t was;
#endif /* CONFIG_NO_SMP */
		if (new_pointer)
			REFCNT_METHODS(T)::incref(new_pointer);
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		if (!__hybrid_atomic_cmpxch(this->m_pointer,
		                            old_pointer,
		                            new_pointer,
		                            __ATOMIC_SEQ_CST,
		                            __ATOMIC_SEQ_CST)) {
#ifdef CONFIG_NO_SMP
			PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
			if (new_pointer)
				REFCNT_METHODS(T)::decref_nokill(new_pointer);
			return false;
		}
#ifndef CONFIG_NO_SMP
		while (__hybrid_atomic_load(this->m_inuse, __ATOMIC_ACQUIRE))
			task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
		if (old_pointer)
			REFCNT_METHODS(T)::decref(old_pointer);
		return true;
	}

	/* Atomic compare-exchange */
	__CXX_CLASSMEMBER NOBLOCK_IF(!PREEMPTION_ENABLED())
	bool KCALL cmpxch_inherit_new(T *old_pointer,
	                              /*inherit(on_success)*/ REF T *new_pointer) __CXX_NOEXCEPT {
#ifdef CONFIG_NO_SMP
		pflag_t was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		if (!__hybrid_atomic_cmpxch(this->m_pointer,
		                            old_pointer,
		                            new_pointer,
		                            __ATOMIC_SEQ_CST,
		                            __ATOMIC_SEQ_CST)) {
#ifdef CONFIG_NO_SMP
			PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
			return false;
		}
#ifndef CONFIG_NO_SMP
		while (__hybrid_atomic_load(this->m_inuse, __ATOMIC_ACQUIRE))
			task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
		if (old_pointer)
			REFCNT_METHODS(T)::decref(old_pointer);
		return true;
	}
};

#define XATOMIC_WEAKLYREF_STRUCT(...) xatomic_weaklyref_struct< __VA_ARGS__ >
#ifdef CONFIG_NO_SMP
#define xatomic_weaklyref_set(self, v)                                   \
	do {                                                                 \
		pflag_t _pf_was = PREEMPTION_PUSHOFF();                          \
		__hybrid_atomic_store((self)->m_pointer, (v), __ATOMIC_SEQ_CST); \
		PREEMPTION_POP(_pf_was);                                         \
	} __WHILE0
#else /* CONFIG_NO_SMP */
#define xatomic_weaklyref_set(self, v)                                   \
	do {                                                                 \
		__hybrid_atomic_store((self)->m_pointer, (v), __ATOMIC_SEQ_CST); \
		while (__hybrid_atomic_load((self)->m_inuse, __ATOMIC_ACQUIRE))  \
			task_tryyield_or_pause();                                    \
	} __WHILE0
#endif /* CONFIG_NO_SMP */
#define xatomic_weaklyref_clear(self) xatomic_weaklyref_set(self, __NULLPTR)

template<class T> struct xatomic_weaklyref_struct {
	WEAK T          *m_pointer; /* [0..1][lock(COMPLEX(m_inuse))] The pointed-to object.
	                             * NOTE: This isn't an actual reference! */
#ifndef CONFIG_NO_SMP
	WEAK uintptr_t   m_inuse;   /* Cross-CPU is-in-use tracking */
#endif /* !CONFIG_NO_SMP */
};


/* A weakly held reference (must be cleared by the associated object once that object gets destroyed) */
#define XATOMIC_WEAKLYREF(...) xatomic_weaklyref< __VA_ARGS__ >
template<class T> struct xatomic_weaklyref {

#ifndef CONFIG_NO_SMP
#define xatomic_weaklyref_init(self, p)  ((self)->m_pointer = (p), (self)->m_inuse = 0)
#define xatomic_weaklyref_cinit(self, p) ((self)->m_pointer = (p), __hybrid_assert((self)->m_inuse == 0))
#define XATOMIC_WEAKLYREF_INIT(p)        { p, 0 }
#else /* !CONFIG_NO_SMP */
#define xatomic_weaklyref_init(self, p)  ((self)->m_pointer = (p))
#define xatomic_weaklyref_cinit(self, p) ((self)->m_pointer = (p))
#define XATOMIC_WEAKLYREF_INIT(p)        { p }
#endif /* CONFIG_NO_SMP */

	WEAK T          *m_pointer; /* [0..1][lock(COMPLEX(m_inuse))] The pointed-to object.
	                             * NOTE: This isn't an actual reference! */
#ifndef CONFIG_NO_SMP
	WEAK uintptr_t   m_inuse;   /* Cross-CPU is-in-use tracking */
#endif /* !CONFIG_NO_SMP */

	/* Clear the pointed-to value. */
	__CXX_CLASSMEMBER ATTR_LEAF NOBLOCK void KCALL clear() __CXX_NOEXCEPT {
		set(__NULLPTR);
	}

	__CXX_CLASSMEMBER ATTR_LEAF WUNUSED NOBLOCK bool KCALL is_nonnull() __CXX_NOEXCEPT {
		return __hybrid_atomic_load(m_pointer, __ATOMIC_ACQUIRE) != __NULLPTR;
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER ATTR_LEAF NOBLOCK WUNUSED REF T *KCALL get() __CXX_NOEXCEPT {
		REF T *result;
		pflag_t was;
		was = PREEMPTION_PUSHOFF();
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchinc(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		COMPILER_READ_BARRIER();
		result = this->m_pointer;
		COMPILER_READ_BARRIER();
		if (result && !REFCNT_METHODS(T)::tryincref(result))
			result = __NULLPTR;
#ifndef CONFIG_NO_SMP
		__hybrid_atomic_fetchdec(this->m_inuse, __ATOMIC_SEQ_CST);
#endif /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
		return result;
	}

	__CXX_CLASSMEMBER NOBLOCK_IF(!PREEMPTION_ENABLED())
	void KCALL set(T *new_pointer) __CXX_NOEXCEPT {
#ifdef CONFIG_NO_SMP
		pflag_t was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		__hybrid_atomic_store(this->m_pointer,
		                      new_pointer,
		                      __ATOMIC_SEQ_CST);
#ifndef CONFIG_NO_SMP
		while (__hybrid_atomic_load(this->m_inuse, __ATOMIC_ACQUIRE))
			task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
	}

	/* Return a reference to the current pointed-to value */
	__CXX_CLASSMEMBER ATTR_LEAF WUNUSED NOBLOCK_IF(!PREEMPTION_ENABLED())
	REF T *KCALL exchange(T *new_pointer) __CXX_NOEXCEPT {
		REF T *old_pointer;
#ifdef CONFIG_NO_SMP
		pflag_t was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		old_pointer = __hybrid_atomic_xch(this->m_pointer,
		                                  new_pointer,
		                                  __ATOMIC_SEQ_CST);
		if (old_pointer && !REFCNT_METHODS(T)::tryincref(old_pointer))
			old_pointer = __NULLPTR;
#ifndef CONFIG_NO_SMP
		while (__hybrid_atomic_load(this->m_inuse, __ATOMIC_ACQUIRE))
			task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
		return old_pointer;
	}

	/* Atomic compare-exchange */
	__CXX_CLASSMEMBER NOBLOCK_IF(!PREEMPTION_ENABLED())
	bool KCALL cmpxch(T *old_pointer, T *new_pointer) __CXX_NOEXCEPT {
#ifdef CONFIG_NO_SMP
		pflag_t was;
#endif /* CONFIG_NO_SMP */
#ifdef CONFIG_NO_SMP
		was = PREEMPTION_PUSHOFF();
#endif /* CONFIG_NO_SMP */
		if (!__hybrid_atomic_cmpxch(this->m_pointer,
		                            old_pointer,
		                            new_pointer,
		                            __ATOMIC_SEQ_CST,
		                            __ATOMIC_SEQ_CST)) {
#ifdef CONFIG_NO_SMP
			PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
			return false;
		}
#ifndef CONFIG_NO_SMP
		while (__hybrid_atomic_load(this->m_inuse, __ATOMIC_ACQUIRE))
			task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
		return true;
	}
};

} /* extern "c++" */
#else /* __cplusplus */

#ifndef CONFIG_NO_SMP
#define ATOMIC_REF(...)                                                                              \
	struct {                                                                                         \
		WEAK REF __VA_ARGS__ *m_pointer; /* [1..1][lock(COMPLEX(m_inuse))] The pointed-to object. */ \
		WEAK uintptr_t        m_inuse;   /* Cross-CPU is-in-use tracking */                          \
	}
#else /* !CONFIG_NO_SMP */
#define ATOMIC_REF(...)                                                                              \
	struct {                                                                                         \
		WEAK REF __VA_ARGS__ *m_pointer; /* [1..1][lock(COMPLEX(m_inuse))] The pointed-to object. */ \
	}
#endif /* CONFIG_NO_SMP */

#ifndef CONFIG_NO_SMP
#define atomic_ref_init(self, p)  ((self)->m_pointer = (p), (self)->m_inuse = 0)
#define atomic_ref_cinit(self, p) ((self)->m_pointer = (p), __hybrid_assert((self)->m_inuse == 0))
#define ATOMIC_REF_INIT(p)        { p, 0 }
#else /* !CONFIG_NO_SMP */
#define atomic_ref_init(self, p)  ((self)->m_pointer = (p))
#define atomic_ref_cinit(self, p) ((self)->m_pointer = (p))
#define ATOMIC_REF_INIT(p)        { p }
#endif /* CONFIG_NO_SMP */
#define atomic_ref_fini(self)     decref((self)->m_pointer)

#define XATOMIC_REF_STRUCT ATOMIC_REF
#define XATOMIC_REF        ATOMIC_REF
#ifndef CONFIG_NO_SMP
#define xatomic_ref_init(self, p)  ((self)->m_pointer = (p), (self)->m_inuse = 0)
#define xatomic_ref_cinit(self, p) ((self)->m_pointer = (p), __hybrid_assert((self)->m_inuse == 0))
#define XATOMIC_REF_INIT(p)        { p, 0 }
#else /* !CONFIG_NO_SMP */
#define xatomic_ref_init(self, p)  ((self)->m_pointer = (p))
#define xatomic_ref_cinit(self, p) ((self)->m_pointer = (p))
#define XATOMIC_REF_INIT(p)        { p }
#endif /* CONFIG_NO_SMP */
#define xatomic_ref_fini(self)     xdecref((self)->m_pointer)

/* A weakly held reference (must be cleared by the associated object once that object gets destroyed) */
#define XATOMIC_WEAKLYREF   ATOMIC_REF
#ifndef CONFIG_NO_SMP
#define xatomic_weaklyref_init(self, p)  ((self)->m_pointer = (p), (self)->m_inuse = 0)
#define xatomic_weaklyref_cinit(self, p) ((self)->m_pointer = (p), __hybrid_assert((self)->m_inuse == 0))
#define XATOMIC_WEAKLYREF_INIT(p)        { p, 0 }
#else /* !CONFIG_NO_SMP */
#define xatomic_weaklyref_init(self, p)  ((self)->m_pointer = (p))
#define xatomic_weaklyref_cinit(self, p) ((self)->m_pointer = (p))
#define XATOMIC_WEAKLYREF_INIT(p)        { p }
#endif /* CONFIG_NO_SMP */

#endif /* !__cplusplus */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_MISC_ATOMIC_REF_H */
