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
#ifndef _KOS_ATOMIC_REF_H
#define _KOS_ATOMIC_REF_H 1

#include <__stdinc.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/pp/__va_nargs.h>
#include <hybrid/typecore.h>

#include <kos/anno.h>

/* Atomic reference pointer.
 * This is a  special type  of pointer  that allows  for a  non-blocking, atomic  read+incref
 * operation, while still implementing an atomic-exchange, as well as atomic-compare-exchange
 * operation, all-the-while still allowing for references to be traced correctly, as well  as
 * be entirety reentrant-safe.
 *
 * >> get() {
 * >>     __PRIVATE_AR_INTR_PUSHOFF();
 * >>     ATOMIC_INC(arr_cnt);
 * >>     result = arr_obj;
 * >>     incref(result);
 * >>     ATOMIC_DEC(arr_cnt);
 * >>     __PRIVATE_AR_INTR_POP();
 * >>     return result;
 * >> }
 *
 * >> cmpxch(old, new) {
 * >>     incref(new);
 * >>     __PRIVATE_AR_INTR_PUSHOFF();
 * >>     if (!ATOMIC_CMPXCH(arr_obj, old, new)) {
 * >>         decref_nokill(new);
 * >>         __PRIVATE_AR_INTR_BREAK();
 * >>         return false;
 * >>     }
 * >>     while (arr_cnt != 0)
 * >>         sched_yield();
 * >>     __PRIVATE_AR_INTR_POP();
 * >>     decref(old);
 * >>     return true;
 * >> }
 *
 * There are 3 different variants of atomic references:
 *
 *   - ARREF(T): AtomicRealReference:
 *     Used to describe a field `REF T *field; // [1..1]'
 *
 *   - AXREF(T): AtomicReference (nullable):
 *     Used to describe a field `REF T *field; // [0..1]'
 *
 *   - AWREF(T): AtomicWeakReference:
 *     Used to describe a field `T *field; // [0..1]'
 *     With the special property that `T::destroy()' will do `field = NULL',
 *     which in is done through `awref_set(..., NULL)'
 *
 * In all 3 cases, it is possible to atomically (in an re-entrant-safe way)
 * get, set, exchange, compare-exchange, etc... the pointed-to field,  such
 * that all transactions are performed atomically.
 *
 * >> T     *arref_ptr                     (ARREF(T) const *self);
 * >> REF T *arref_get                     (ARREF(T) *self);
 * >> REF T *arref_get_nopr                (ARREF(T) *self);
 * >> void   arref_get                     (ARREF(T) *self, REF T **p_result);
 * >> void   arref_get_nopr                (ARREF(T) *self, REF T **p_result);
 * >> void   arref_get                     (ARREF(T) *self, REF T **p_result, void incref(T *));
 * >> void   arref_get_nopr                (ARREF(T) *self, REF T **p_result, void incref(T *));
 * >> REF T *arref_xch_inherit             (ARREF(T) *self, REF T *newobj);
 * >> REF T *arref_xch_inherit_nopr        (ARREF(T) *self, REF T *newobj);
 * >> void   arref_xch_inherit             (ARREF(T) *self, REF T *newobj, REF T **p_oldobj);
 * >> void   arref_xch_inherit_nopr        (ARREF(T) *self, REF T *newobj, REF T **p_oldobj);
 * >> REF T *arref_xch                     (ARREF(T) *self, T *newobj);
 * >> REF T *arref_xch_nopr                (ARREF(T) *self, T *newobj);
 * >> void   arref_xch                     (ARREF(T) *self, T *newobj, REF T **p_oldobj);
 * >> void   arref_xch_nopr                (ARREF(T) *self, T *newobj, REF T **p_oldobj);
 * >> void   arref_xch                     (ARREF(T) *self, T *newobj, REF T **p_oldobj, void incref(T *));
 * >> void   arref_xch_nopr                (ARREF(T) *self, T *newobj, REF T **p_oldobj, void incref(T *));
 * >> void   arref_set_inherit             (ARREF(T) *self, REF T *newobj);
 * >> void   arref_set_inherit_nopr        (ARREF(T) *self, REF T *newobj);
 * >> void   arref_set_inherit             (ARREF(T) *self, REF T *newobj, typename T);
 * >> void   arref_set_inherit_nopr        (ARREF(T) *self, REF T *newobj, typename T);
 * >> void   arref_set_inherit             (ARREF(T) *self, REF T *newobj, typename T, void decref(T *));
 * >> void   arref_set_inherit_nopr        (ARREF(T) *self, REF T *newobj, typename T, void decref(T *));
 * >> void   arref_set                     (ARREF(T) *self, REF T *newobj);
 * >> void   arref_set_nopr                (ARREF(T) *self, REF T *newobj);
 * >> void   arref_set                     (ARREF(T) *self, REF T *newobj, typename T);
 * >> void   arref_set_nopr                (ARREF(T) *self, REF T *newobj, typename T);
 * >> void   arref_set                     (ARREF(T) *self, REF T *newobj, typename T, void incref(T *), void decref(T *));
 * >> void   arref_set_nopr                (ARREF(T) *self, REF T *newobj, typename T, void incref(T *), void decref(T *));
 * >> bool   arref_cmpxch_inherit          (ARREF(T) *self, REF T *oldobj, REF T *newobj);
 * >> bool   arref_cmpxch_inherit_nopr     (ARREF(T) *self, REF T *oldobj, REF T *newobj);
 * >> void   arref_cmpxch_inherit          (ARREF(T) *self, REF T *oldobj, REF T *newobj, bool *p_ok);
 * >> void   arref_cmpxch_inherit_nopr     (ARREF(T) *self, REF T *oldobj, REF T *newobj, bool *p_ok);
 * >> bool   arref_cmpxch_inherit_new      (ARREF(T) *self, T *oldobj, REF T *newobj);
 * >> bool   arref_cmpxch_inherit_new_nopr (ARREF(T) *self, T *oldobj, REF T *newobj);
 * >> void   arref_cmpxch_inherit_new      (ARREF(T) *self, T *oldobj, REF T *newobj, bool *p_ok);
 * >> void   arref_cmpxch_inherit_new_nopr (ARREF(T) *self, T *oldobj, REF T *newobj, bool *p_ok);
 * >> void   arref_cmpxch_inherit_new      (ARREF(T) *self, T *oldobj, REF T *newobj, bool *p_ok, void decref(T *));
 * >> void   arref_cmpxch_inherit_new_nopr (ARREF(T) *self, T *oldobj, REF T *newobj, bool *p_ok, void decref(T *));
 * >> bool   arref_cmpxch                  (ARREF(T) *self, T *oldobj, T *newobj);
 * >> bool   arref_cmpxch_nopr             (ARREF(T) *self, T *oldobj, T *newobj);
 * >> void   arref_cmpxch                  (ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void   arref_cmpxch_nopr             (ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void   arref_cmpxch                  (ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void   arref_cmpxch_nopr             (ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void   arref_cmpxch                  (ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *));
 * >> void   arref_cmpxch_nopr             (ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *));
 *
 * >> T     *axref_ptr                     (AXREF(T) const *self);
 * >> REF T *axref_get                     (AXREF(T) *self);
 * >> REF T *axref_get_nopr                (AXREF(T) *self);
 * >> void   axref_get                     (AXREF(T) *self, REF T **p_result);
 * >> void   axref_get_nopr                (AXREF(T) *self, REF T **p_result);
 * >> void   axref_get                     (AXREF(T) *self, REF T **p_result, void incref(T *));
 * >> void   axref_get_nopr                (AXREF(T) *self, REF T **p_result, void incref(T *));
 * >> REF T *axref_xch_inherit             (AXREF(T) *self, REF T *newobj);
 * >> REF T *axref_xch_inherit_nopr        (AXREF(T) *self, REF T *newobj);
 * >> void   axref_xch_inherit             (AXREF(T) *self, REF T *newobj, REF T **p_oldobj);
 * >> void   axref_xch_inherit_nopr        (AXREF(T) *self, REF T *newobj, REF T **p_oldobj);
 * >> REF T *axref_xch                     (AXREF(T) *self, T *newobj);
 * >> REF T *axref_xch_nopr                (AXREF(T) *self, T *newobj);
 * >> void   axref_xch                     (AXREF(T) *self, T *newobj, REF T **p_oldobj);
 * >> void   axref_xch_nopr                (AXREF(T) *self, T *newobj, REF T **p_oldobj);
 * >> void   axref_xch                     (AXREF(T) *self, T *newobj, REF T **p_oldobj, void incref(T *));
 * >> void   axref_xch_nopr                (AXREF(T) *self, T *newobj, REF T **p_oldobj, void incref(T *));
 * >> REF T *axref_steal                   (AXREF(T) *self);
 * >> REF T *axref_steal_nopr              (AXREF(T) *self);
 * >> void   axref_steal                   (AXREF(T) *self, REF T **p_oldobj);
 * >> void   axref_steal_nopr              (AXREF(T) *self, REF T **p_oldobj);
 * >> void   axref_set_inherit             (AXREF(T) *self, REF T *newobj);
 * >> void   axref_set_inherit_nopr        (AXREF(T) *self, REF T *newobj);
 * >> void   axref_set_inherit             (AXREF(T) *self, REF T *newobj, typename T);
 * >> void   axref_set_inherit_nopr        (AXREF(T) *self, REF T *newobj, typename T);
 * >> void   axref_set_inherit             (AXREF(T) *self, REF T *newobj, typename T, void decref(T *));
 * >> void   axref_set_inherit_nopr        (AXREF(T) *self, REF T *newobj, typename T, void decref(T *));
 * >> void   axref_set                     (AXREF(T) *self, REF T *newobj);
 * >> void   axref_set_nopr                (AXREF(T) *self, REF T *newobj);
 * >> void   axref_set                     (AXREF(T) *self, REF T *newobj, typename T);
 * >> void   axref_set_nopr                (AXREF(T) *self, REF T *newobj, typename T);
 * >> void   axref_set                     (AXREF(T) *self, REF T *newobj, typename T, void incref(T *), void decref(T *));
 * >> void   axref_set_nopr                (AXREF(T) *self, REF T *newobj, typename T, void incref(T *), void decref(T *));
 * >> void   axref_clear                   (AXREF(T) *self);
 * >> void   axref_clear_nopr              (AXREF(T) *self);
 * >> void   axref_clear                   (AXREF(T) *self, typename T);
 * >> void   axref_clear_nopr              (AXREF(T) *self, typename T);
 * >> void   axref_clear                   (AXREF(T) *self, typename T, void decref(T *));
 * >> void   axref_clear_nopr              (AXREF(T) *self, typename T, void decref(T *));
 * >> bool   axref_cmpxch_inherit          (AXREF(T) *self, REF T *oldobj, REF T *newobj);
 * >> bool   axref_cmpxch_inherit_nopr     (AXREF(T) *self, REF T *oldobj, REF T *newobj);
 * >> void   axref_cmpxch_inherit          (AXREF(T) *self, REF T *oldobj, REF T *newobj, bool *p_ok);
 * >> void   axref_cmpxch_inherit_nopr     (AXREF(T) *self, REF T *oldobj, REF T *newobj, bool *p_ok);
 * >> bool   axref_cmpxch_inherit_new      (AXREF(T) *self, T *oldobj, REF T *newobj);
 * >> bool   axref_cmpxch_inherit_new_nopr (AXREF(T) *self, T *oldobj, REF T *newobj);
 * >> void   axref_cmpxch_inherit_new      (AXREF(T) *self, T *oldobj, REF T *newobj, bool *p_ok);
 * >> void   axref_cmpxch_inherit_new_nopr (AXREF(T) *self, T *oldobj, REF T *newobj, bool *p_ok);
 * >> void   axref_cmpxch_inherit_new      (AXREF(T) *self, T *oldobj, REF T *newobj, bool *p_ok, void decref(T *));
 * >> void   axref_cmpxch_inherit_new_nopr (AXREF(T) *self, T *oldobj, REF T *newobj, bool *p_ok, void decref(T *));
 * >> bool   axref_cmpxch                  (AXREF(T) *self, T *oldobj, T *newobj);
 * >> bool   axref_cmpxch_nopr             (AXREF(T) *self, T *oldobj, T *newobj);
 * >> void   axref_cmpxch                  (AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void   axref_cmpxch_nopr             (AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void   axref_cmpxch                  (AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void   axref_cmpxch_nopr             (AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void   axref_cmpxch                  (AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *));
 * >> void   axref_cmpxch_nopr             (AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *));
 *
 * >> T     *awref_ptr                     (AWREF(T) const *self);
 * >> REF T *awref_get                     (AWREF(T) *self);
 * >> REF T *awref_get_nopr                (AWREF(T) *self);
 * >> void   awref_get                     (AWREF(T) *self, REF T **p_result);
 * >> void   awref_get_nopr                (AWREF(T) *self, REF T **p_result);
 * >> void   awref_get                     (AWREF(T) *self, REF T **p_result, bool tryincref(T *));
 * >> void   awref_get_nopr                (AWREF(T) *self, REF T **p_result, bool tryincref(T *));
 * >> void   awref_set                     (AWREF(T) *self, T *newobj);
 * >> void   awref_set_nopr                (AWREF(T) *self, T *newobj);
 * >> REF T *awref_xch                     (AWREF(T) *self, T *newobj);
 * >> REF T *awref_xch_nopr                (AWREF(T) *self, T *newobj);
 * >> void   awref_xch                     (AWREF(T) *self, T *newobj, REF T **p_oldobj);
 * >> void   awref_xch_nopr                (AWREF(T) *self, T *newobj, REF T **p_oldobj);
 * >> void   awref_xch                     (AWREF(T) *self, T *newobj, REF T **p_oldobj, bool tryincref(T *));
 * >> void   awref_xch_nopr                (AWREF(T) *self, T *newobj, REF T **p_oldobj, bool tryincref(T *));
 * >> void   awref_clear                   (AWREF(T) *self);
 * >> void   awref_clear_nopr              (AWREF(T) *self);
 * >> bool   awref_cmpxch                  (AWREF(T) *self, T *oldobj, T *newobj);
 * >> bool   awref_cmpxch_nopr             (AWREF(T) *self, T *oldobj, T *newobj);
 * >> void   awref_cmpxch                  (AWREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void   awref_cmpxch_nopr             (AWREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> bool   awref_replacedead             (AWREF(T) *self, T *newobj); // Replace an already-destroyed object
 * >> bool   awref_replacedead_nopr        (AWREF(T) *self, T *newobj);
 * >> void   awref_replacedead             (AWREF(T) *self, T *newobj, bool *p_ok);
 * >> void   awref_replacedead_nopr        (AWREF(T) *self, T *newobj, bool *p_ok);
 * >> void   awref_replacedead             (AWREF(T) *self, T *newobj, bool *p_ok, typename T);
 * >> void   awref_replacedead_nopr        (AWREF(T) *self, T *newobj, bool *p_ok, typename T);
 * >> void   awref_replacedead             (AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *));
 * >> void   awref_replacedead_nopr        (AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *));
 *
 * If not given, refcnt operators default to those which may be defined by `<kos/refcnt.h>'
 */


#ifdef __CC__
#ifdef __INTELLISENSE__
#define __PRIVATE_AR_YIELD()        (void)0
#define __PRIVATE_AR_INTR_PUSHOFF() do {
#define __PRIVATE_AR_INTR_BREAK()   (void)0
#define __PRIVATE_AR_INTR_POP()     } __WHILE0
#define __PRIVATE_AR_INTR_END()     } __WHILE0
#elif defined(__KERNEL__) && defined(__KOS__)
/* Kernel-space version */
#include <sched/task.h>
#define __PRIVATE_AR_YIELD() task_tryyield_or_pause()
#define __PRIVATE_AR_INTR_PUSHOFF() \
	do {                            \
		pflag_t __aip_was = PREEMPTION_PUSHOFF()
#define __PRIVATE_AR_INTR_BREAK() \
		PREEMPTION_POP(__aip_was)
#define __PRIVATE_AR_INTR_POP()    \
		__PRIVATE_AR_INTR_BREAK(); \
	}	__WHILE0
#define __PRIVATE_AR_INTR_END() \
	}	__WHILE0
#undef __ARCH_HAVE_AR_NOSMP
#ifdef CONFIG_NO_SMP
#define __ARCH_HAVE_AR_NOSMP
#endif /* CONFIG_NO_SMP */
#else  /* __KERNEL__ && __KOS__ */

/* User-space version */
#include <hybrid/sched/__yield.h>

#include <libc/signal.h>
#define __PRIVATE_AR_YIELD() __hybrid_yield()
#undef __ARCH_HAVE_AR_NOSMP
#if defined(__libc_setsigmaskfullptr) && defined(__libc_setsigmaskptr)
#define __PRIVATE_AR_INTR_PUSHOFF() \
	do {                            \
		struct __sigset_struct *__aip_oss = __libc_setsigmaskfullptr()
#define __PRIVATE_AR_INTR_BREAK() \
		__libc_setsigmaskptr(__aip_oss)
#define __PRIVATE_AR_INTR_POP()    \
		__PRIVATE_AR_INTR_BREAK(); \
	}	__WHILE0
#define __PRIVATE_AR_INTR_END() \
	}	__WHILE0
#elif defined(__libc_sigprocmask)
#include <asm/os/signal.h>
#define __PRIVATE_AR_INTR_PUSHOFF()                                    \
	do {                                                               \
		struct __sigset_struct __aip_oss;                              \
		do {                                                           \
			struct __sigset_struct __aip_nss;                          \
			__libc_sigfillset(&__aip_nss);                             \
			__libc_sigprocmask(__SIG_SETMASK, &__aip_nss, &__aip_oss); \
		}	__WHILE0
#define __PRIVATE_AR_INTR_BREAK() \
	__libc_sigprocmask(__SIG_SETMASK, &__aip_oss, __NULLPTR)
#define __PRIVATE_AR_INTR_POP()    \
		__PRIVATE_AR_INTR_BREAK(); \
	}	__WHILE0
#define __PRIVATE_AR_INTR_END() \
	}	__WHILE0
#else /* ... */
/* Just hope for the best... */
#define __PRIVATE_AR_INTR_PUSHOFF() do {
#define __PRIVATE_AR_INTR_BREAK()   (void)0
#define __PRIVATE_AR_INTR_POP() \
	}	__WHILE0
#define __PRIVATE_AR_INTR_END() \
	}	__WHILE0
#endif /* !... */
#endif /* !__KERNEL__ || !__KOS__ */

#define __PRIVATE_AR_INTR_PUSHOFF_NOPR() do {
#define __PRIVATE_AR_INTR_BREAK_NOPR()   (void)0
#define __PRIVATE_AR_INTR_POP_NOPR() \
	}	__WHILE0
#define __PRIVATE_AR_INTR_END_NOPR() \
	}	__WHILE0


#ifdef __ARCH_HAVE_AR_NOSMP
#ifdef __cplusplus
#define __PRIVATE_ARREF_1(type)                              \
	struct {                                                 \
		__REF type *arr_obj; /* [1..1] Referenced object. */ \
	}
#define __PRIVATE_ARREF_2(name, type)                        \
	struct name {                                            \
		__REF type *arr_obj; /* [1..1] Referenced object. */ \
	}
#define __PRIVATE_AXREF_1(type)                              \
	struct {                                                 \
		__REF type *axr_obj; /* [0..1] Referenced object. */ \
	}
#define __PRIVATE_AXREF_2(name, type)                        \
	struct name {                                            \
		__REF type *axr_obj; /* [0..1] Referenced object. */ \
	}
#define __PRIVATE_AWREF_1(type)                        \
	struct {                                           \
		type *awr_obj; /* [0..1] Referenced object. */ \
	}
#define __PRIVATE_AWREF_2(name, type)                  \
	struct name {                                      \
		type *awr_obj; /* [0..1] Referenced object. */ \
	}
#else /* __cplusplus */
#define __PRIVATE_ARREF_1(type)                                     \
	struct {                                                        \
		__REF struct type *arr_obj; /* [1..1] Referenced object. */ \
	}
#define __PRIVATE_ARREF_2(name, type)                               \
	struct name {                                                   \
		__REF struct type *arr_obj; /* [1..1] Referenced object. */ \
	}
#define __PRIVATE_AXREF_1(type)                                     \
	struct {                                                        \
		__REF struct type *axr_obj; /* [0..1] Referenced object. */ \
	}
#define __PRIVATE_AXREF_2(name, type)                               \
	struct name {                                                   \
		__REF struct type *axr_obj; /* [0..1] Referenced object. */ \
	}
#define __PRIVATE_AWREF_1(type)                               \
	struct {                                                  \
		struct type *awr_obj; /* [0..1] Referenced object. */ \
	}
#define __PRIVATE_AWREF_2(name, type)                         \
	struct name {                                             \
		struct type *awr_obj; /* [0..1] Referenced object. */ \
	}
#endif /* !__cplusplus */
#else  /* __ARCH_HAVE_AR_NOSMP */
#ifdef __cplusplus
#define __PRIVATE_ARREF_1(type)                                                             \
	struct {                                                                                \
		__REF type      *arr_obj; /* [*valid_if(arr_cnt != 0)][1..1] Referenced object. */  \
		__UINTPTR_TYPE__ arr_cnt; /* In-use counter (when non-zero, `*arr_obj' is valid) */ \
	}
#define __PRIVATE_ARREF_2(name, type)                                                       \
	struct name {                                                                           \
		__REF type      *arr_obj; /* [*valid_if(arr_cnt != 0)][1..1] Referenced object. */  \
		__UINTPTR_TYPE__ arr_cnt; /* In-use counter (when non-zero, `*arr_obj' is valid) */ \
	}
#define __PRIVATE_AXREF_1(type)                                                            \
	struct {                                                                               \
		__REF type      *axr_obj; /* [*valid_if(axr_cnt != 0)][0..1] Referenced object. */ \
		__UINTPTR_TYPE__ axr_cnt; /* In-use counter (when non-zero, `axr_obj' is NULL,     \
		                           * or `*axr_obj' is valid) */                            \
	}
#define __PRIVATE_AXREF_2(name, type)                                                      \
	struct name {                                                                          \
		__REF type      *axr_obj; /* [*valid_if(axr_cnt != 0)][0..1] Referenced object. */ \
		__UINTPTR_TYPE__ axr_cnt; /* In-use counter (when non-zero, `axr_obj' is NULL,     \
		                           * or `*axr_obj' is valid) */                            \
	}
#define __PRIVATE_AWREF_1(type)                                                            \
	struct {                                                                               \
		type            *awr_obj; /* [*valid_if(awr_cnt != 0)][0..1] Referenced object. */ \
		__UINTPTR_TYPE__ awr_cnt; /* In-use counter (when non-zero, `awr_obj' is NULL,     \
		                           * or `*awr_obj' is valid) */                            \
	}
#define __PRIVATE_AWREF_2(name, type)                                                      \
	struct name {                                                                          \
		type            *awr_obj; /* [*valid_if(awr_cnt != 0)][0..1] Referenced object. */ \
		__UINTPTR_TYPE__ awr_cnt; /* In-use counter (when non-zero, `awr_obj' is NULL,     \
		                           * or `*awr_obj' is valid) */                            \
	}
#else /* __cplusplus */
#define __PRIVATE_ARREF_1(type)                                                               \
	struct {                                                                                  \
		__REF struct type *arr_obj; /* [*valid_if(arr_cnt != 0)][1..1] Referenced object. */  \
		__UINTPTR_TYPE__   arr_cnt; /* In-use counter (when non-zero, `*arr_obj' is valid) */ \
	}
#define __PRIVATE_ARREF_2(name, type)                                                         \
	struct name {                                                                             \
		__REF struct type *arr_obj; /* [*valid_if(arr_cnt != 0)][1..1] Referenced object. */  \
		__UINTPTR_TYPE__   arr_cnt; /* In-use counter (when non-zero, `*arr_obj' is valid) */ \
	}
#define __PRIVATE_AXREF_1(type)                                                              \
	struct {                                                                                 \
		__REF struct type *axr_obj; /* [*valid_if(axr_cnt != 0)][0..1] Referenced object. */ \
		__UINTPTR_TYPE__   axr_cnt; /* In-use counter (when non-zero, `axr_obj' is NULL,     \
		                             * or `*axr_obj' is valid) */                            \
	}
#define __PRIVATE_AXREF_2(name, type)                                                        \
	struct name {                                                                            \
		__REF struct type *axr_obj; /* [*valid_if(axr_cnt != 0)][0..1] Referenced object. */ \
		__UINTPTR_TYPE__   axr_cnt; /* In-use counter (when non-zero, `axr_obj' is NULL,     \
		                             * or `*axr_obj' is valid) */                            \
	}
#define __PRIVATE_AWREF_1(type)                                                            \
	struct {                                                                               \
		struct type     *awr_obj; /* [*valid_if(awr_cnt != 0)][0..1] Referenced object. */ \
		__UINTPTR_TYPE__ awr_cnt; /* In-use counter (when non-zero, `awr_obj' is NULL,     \
		                           * or `*awr_obj' is valid) */                            \
	}
#define __PRIVATE_AWREF_2(name, type)                                                      \
	struct name {                                                                          \
		struct type     *awr_obj; /* [*valid_if(awr_cnt != 0)][0..1] Referenced object. */ \
		__UINTPTR_TYPE__ awr_cnt; /* In-use counter (when non-zero, `awr_obj' is NULL,     \
		                           * or `*awr_obj' is valid) */                            \
	}
#endif /* !__cplusplus */
#endif /* !__ARCH_HAVE_AR_NOSMP */


#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> ARREF([name], type); */
#define ARREF(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_ARREF_, (__VA_ARGS__))(__VA_ARGS__)
/* >> AXREF([name], type); */
#define AXREF(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_AXREF_, (__VA_ARGS__))(__VA_ARGS__)
/* >> AWREF([name], type); */
#define AWREF(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_AWREF_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> ARREF(name, type); */
#define ARREF __PRIVATE_ARREF_2
/* >> AXREF(name, type); */
#define AXREF __PRIVATE_AXREF_2
/* >> AWREF(name, type); */
#define AWREF __PRIVATE_AWREF_2
#endif /* !__HYBRID_PP_VA_OVERLOAD */

#define __PRIVATE_arref_fini_1(self)         __PRIVATE_arref_fini_2(self, decref)
#define __PRIVATE_arref_fini_2(self, decref) decref((self)->arr_obj)
#define __PRIVATE_axref_fini_1(self)         __PRIVATE_axref_fini_2(self, decref)
#define __PRIVATE_axref_fini_2(self, decref) ((self)->axr_obj ? decref((self)->axr_obj) : (void)0)
#ifdef __ARCH_HAVE_AR_NOSMP
#define __PRIVATE_arref_init_smp(self)  /* nothing */
#define __PRIVATE_arref_cinit_smp(self) /* nothing */
#define __PRIVATE_arref_inccnt(self)    /* nothing */
#define __PRIVATE_arref_deccnt(self)    /* nothing */
#define __PRIVATE_arref_waitfor(self)   /* nothing */
#define __PRIVATE_axref_init_smp(self)  /* nothing */
#define __PRIVATE_axref_cinit_smp(self) /* nothing */
#define __PRIVATE_axref_inccnt(self)    /* nothing */
#define __PRIVATE_axref_deccnt(self)    /* nothing */
#define __PRIVATE_axref_waitfor(self)   /* nothing */
#define __PRIVATE_awref_init_smp(self)  /* nothing */
#define __PRIVATE_awref_cinit_smp(self) /* nothing */
#define __PRIVATE_awref_inccnt(self)    /* nothing */
#define __PRIVATE_awref_deccnt(self)    /* nothing */
#define __PRIVATE_awref_waitfor(self)   /* nothing */
#else /* __ARCH_HAVE_AR_NOSMP */
#define __PRIVATE_arref_init_smp(self)  , (self)->arr_cnt = 0
#define __PRIVATE_arref_cinit_smp(self) , __hybrid_assert((self)->arr_cnt == 0)
#define __PRIVATE_arref_inccnt(self)    __hybrid_atomic_inc((self)->arr_cnt, __ATOMIC_ACQUIRE);
#define __PRIVATE_arref_deccnt(self)    __hybrid_atomic_dec((self)->arr_cnt, __ATOMIC_RELEASE);
#define __PRIVATE_arref_waitfor(self)   while (__hybrid_atomic_load((self)->arr_cnt, __ATOMIC_ACQUIRE) != 0) __PRIVATE_AR_YIELD();
#define __PRIVATE_axref_init_smp(self)  , (self)->axr_cnt = 0
#define __PRIVATE_axref_cinit_smp(self) , __hybrid_assert((self)->axr_cnt == 0)
#define __PRIVATE_axref_inccnt(self)    __hybrid_atomic_inc((self)->axr_cnt, __ATOMIC_ACQUIRE);
#define __PRIVATE_axref_deccnt(self)    __hybrid_atomic_dec((self)->axr_cnt, __ATOMIC_RELEASE);
#define __PRIVATE_axref_waitfor(self)   while (__hybrid_atomic_load((self)->axr_cnt, __ATOMIC_ACQUIRE) != 0) __PRIVATE_AR_YIELD();
#define __PRIVATE_awref_init_smp(self)  , (self)->awr_cnt = 0
#define __PRIVATE_awref_cinit_smp(self) , __hybrid_assert((self)->awr_cnt == 0)
#define __PRIVATE_awref_inccnt(self)    __hybrid_atomic_inc((self)->awr_cnt, __ATOMIC_ACQUIRE);
#define __PRIVATE_awref_deccnt(self)    __hybrid_atomic_dec((self)->awr_cnt, __ATOMIC_RELEASE);
#define __PRIVATE_awref_waitfor(self)   while (__hybrid_atomic_load((self)->awr_cnt, __ATOMIC_ACQUIRE) != 0) __PRIVATE_AR_YIELD();
#endif /* !__ARCH_HAVE_AR_NOSMP */

/************************************************************************/
/* ARREF Api                                                            */
/************************************************************************/

/* >> T *arref_ptr(ARREF(T) *self); */
#define arref_ptr(self) \
	__hybrid_atomic_load((self)->arr_obj, __ATOMIC_ACQUIRE)

/* ========== arref_get ========== */
#define __PRIVATE_arref_get_2(self, p_result) \
	__PRIVATE_arref_get_3(self, p_result, incref)
#define __PRIVATE_arref_get_nopr_2(self, p_result) \
	__PRIVATE_arref_get_nopr_3(self, p_result, incref)
#define __PRIVATE_arref_get_3(self, p_result, incref)                      \
	__PRIVATE_AR_INTR_PUSHOFF();                                           \
	__PRIVATE_arref_inccnt(self)                                           \
	*(p_result) = __hybrid_atomic_load((self)->arr_obj, __ATOMIC_SEQ_CST); \
	incref(*(p_result));                                                   \
	__PRIVATE_arref_deccnt(self)                                           \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_arref_get_nopr_3(self, p_result, incref)                 \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                      \
	__PRIVATE_arref_inccnt(self)                                           \
	*(p_result) = __hybrid_atomic_load((self)->arr_obj, __ATOMIC_SEQ_CST); \
	incref(*(p_result));                                                   \
	__PRIVATE_arref_deccnt(self)                                           \
	__PRIVATE_AR_INTR_POP_NOPR()
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_arref_get_1(self)                 \
	__XBLOCK({                                      \
		__typeof__((self)->arr_obj) __arg_result;   \
		__PRIVATE_arref_get_2(self, &__arg_result); \
		__XRETURN __arg_result;                     \
	})
#define __PRIVATE_arref_get_nopr_1(self)                 \
	__XBLOCK({                                           \
		__typeof__((self)->arr_obj) __arg_result;        \
		__PRIVATE_arref_get_nopr_2(self, &__arg_result); \
		__XRETURN __arg_result;                          \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> REF T *arref_get(ARREF(T) *self);
 * >> void   arref_get(ARREF(T) *self, [[out]] REF T **p_result);
 * >> void   arref_get(ARREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define arref_get(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_get_, (__VA_ARGS__))(__VA_ARGS__)
/* >> REF T *arref_get_nopr(ARREF(T) *self);
 * >> void   arref_get_nopr(ARREF(T) *self, [[out]] REF T **p_result);
 * >> void   arref_get_nopr(ARREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define arref_get_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_get_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void arref_get(ARREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define arref_get __PRIVATE_arref_get_3
/* >> void arref_get_nopr(ARREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define arref_get_nopr __PRIVATE_arref_get_nopr_3
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void arref_get(ARREF(T) *self, [[out]] REF T **p_result);
 * >> void arref_get(ARREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define arref_get(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_get_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void arref_get_nopr(ARREF(T) *self, [[out]] REF T **p_result);
 * >> void arref_get_nopr(ARREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define arref_get_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_get_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void arref_get(ARREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define arref_get __PRIVATE_arref_get_3
/* >> void arref_get_nopr(ARREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define arref_get_nopr __PRIVATE_arref_get_nopr_3
#endif /* !... */

/* ========== arref_xch_inherit ========== */
#define __PRIVATE_arref_xch_inherit_3(self, newobj, p_oldobj)  \
	__PRIVATE_AR_INTR_PUSHOFF();                               \
	*(p_oldobj) = __hybrid_atomic_xch((self)->arr_obj, newobj, \
	                                  __ATOMIC_SEQ_CST);       \
	__PRIVATE_arref_waitfor(self)                              \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_arref_xch_inherit_nopr_3(self, newobj, p_oldobj) \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                              \
	*(p_oldobj) = __hybrid_atomic_xch((self)->arr_obj, newobj,     \
	                                  __ATOMIC_SEQ_CST);           \
	__PRIVATE_arref_waitfor(self)                                  \
	__PRIVATE_AR_INTR_POP_NOPR()
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_arref_xch_inherit_2(self, newobj)                  \
	__XBLOCK({                                                       \
		__typeof__((self)->arr_obj) __arxi_oldobj;                   \
		__PRIVATE_arref_xch_inherit_3(self, newobj, &__arxi_oldobj); \
		__XRETURN __arxi_oldobj;                                     \
	})
#define __PRIVATE_arref_xch_inherit_nopr_2(self, newobj)                  \
	__XBLOCK({                                                            \
		__typeof__((self)->arr_obj) __arxi_oldobj;                        \
		__PRIVATE_arref_xch_inherit_nopr_3(self, newobj, &__arxi_oldobj); \
		__XRETURN __arxi_oldobj;                                          \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> REF T *arref_xch_inherit(ARREF(T) *self, [[in]] REF T *newobj);
 * >> void   arref_xch_inherit(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define arref_xch_inherit(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_xch_inherit_, (__VA_ARGS__))(__VA_ARGS__)
/* >> REF T *arref_xch_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj);
 * >> void   arref_xch_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define arref_xch_inherit_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_xch_inherit_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void arref_xch_inherit(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define arref_xch_inherit __PRIVATE_arref_xch_inherit_3
/* >> void arref_xch_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define arref_xch_inherit_nopr __PRIVATE_arref_xch_inherit_nopr_3
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#else  /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
/* >> void arref_xch_inherit(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define arref_xch_inherit __PRIVATE_arref_xch_inherit_3
/* >> void arref_xch_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define arref_xch_inherit_nopr __PRIVATE_arref_xch_inherit_nopr_3
#endif /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */

/* ========== arref_xch ========== */
#define __PRIVATE_arref_xch_3(self, newobj, p_oldobj) \
	__PRIVATE_arref_xch_4(self, newobj, p_oldobj, incref)
#define __PRIVATE_arref_xch_nopr_3(self, newobj, p_oldobj) \
	__PRIVATE_arref_xch_nopr_4(self, newobj, p_oldobj, incref)
#define __PRIVATE_arref_xch_4(self, newobj, p_oldobj, incref)  \
	do {                                                       \
		incref(newobj);                                        \
		__PRIVATE_arref_xch_inherit_3(self, newobj, p_oldobj); \
	}	__WHILE0
#define __PRIVATE_arref_xch_nopr_4(self, newobj, p_oldobj, incref)  \
	do {                                                            \
		incref(newobj);                                             \
		__PRIVATE_arref_xch_inherit_nopr_3(self, newobj, p_oldobj); \
	}	__WHILE0
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_arref_xch_2(self, newobj)                         \
	__XBLOCK({                                                      \
		__typeof__((self)->arr_obj) __arx_oldobj;                   \
		incref(newobj);                                             \
		__PRIVATE_arref_xch_inherit_3(self, newobj, &__arx_oldobj); \
		__XRETURN __arx_oldobj;                                     \
	})
#define __PRIVATE_arref_xch_nopr_2(self, newobj)                         \
	__XBLOCK({                                                           \
		__typeof__((self)->arr_obj) __arx_oldobj;                        \
		incref(newobj);                                                  \
		__PRIVATE_arref_xch_inherit_nopr_3(self, newobj, &__arx_oldobj); \
		__XRETURN __arx_oldobj;                                          \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> REF T *arref_xch(ARREF(T) *self, [[in]] REF T *newobj);
 * >> void   arref_xch(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj);
 * >> void   arref_xch(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define arref_xch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_xch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> REF T *arref_xch_nopr(ARREF(T) *self, [[in]] REF T *newobj);
 * >> void   arref_xch_nopr(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj);
 * >> void   arref_xch_nopr(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define arref_xch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_xch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void arref_xch(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define arref_xch __PRIVATE_arref_xch_4
/* >> void arref_xch_nopr(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define arref_xch_nopr __PRIVATE_arref_xch_nopr_4
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void   arref_xch(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj);
 * >> void   arref_xch(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define arref_xch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_xch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void   arref_xch_nopr(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj);
 * >> void   arref_xch_nopr(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define arref_xch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_xch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void arref_xch(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define arref_xch __PRIVATE_arref_xch_4
/* >> void arref_xch_nopr(ARREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define arref_xch_nopr __PRIVATE_arref_xch_nopr_4
#endif /* !... */

/* ========== arref_set_inherit ========== */
#define __PRIVATE_arref_set_inherit_4(self, newobj, T, decref)       \
	do {                                                             \
		T *__arsi_oldobj;                                            \
		__PRIVATE_arref_xch_inherit_3(self, newobj, &__arsi_oldobj); \
		decref(__arsi_oldobj);                                       \
	}	__WHILE0
#define __PRIVATE_arref_set_inherit_nopr_4(self, newobj, T, decref)       \
	do {                                                                  \
		T *__arsi_oldobj;                                                 \
		__PRIVATE_arref_xch_inherit_nopr_3(self, newobj, &__arsi_oldobj); \
		decref(__arsi_oldobj);                                            \
	}	__WHILE0
#define __PRIVATE_arref_set_inherit_3(self, newobj, T) \
	__PRIVATE_arref_set_inherit_4(self, newobj, T, decref)
#define __PRIVATE_arref_set_inherit_nopr_3(self, newobj, T) \
	__PRIVATE_arref_set_inherit_nopr_4(self, newobj, T, decref)
#ifdef __COMPILER_HAVE_TYPEOF
#define __PRIVATE_arref_set_inherit_2(self, newobj) \
	__PRIVATE_arref_set_inherit_3(self, newobj, __typeof__(*(self)->arr_obj))
#define __PRIVATE_arref_set_inherit_nopr_2(self, newobj) \
	__PRIVATE_arref_set_inherit_nopr_3(self, newobj, __typeof__(*(self)->arr_obj))
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> void arref_set_inherit(ARREF(T) *self, [[in]] REF T *newobj);
 * >> void arref_set_inherit(ARREF(T) *self, [[in]] REF T *newobj, typename T);
 * >> void arref_set_inherit(ARREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define arref_set_inherit(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_set_inherit_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void arref_set_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj);
 * >> void arref_set_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj, typename T);
 * >> void arref_set_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define arref_set_inherit_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_set_inherit_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void arref_set_inherit(ARREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define arref_set_inherit __PRIVATE_arref_set_inherit_4
/* >> void arref_set_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define arref_set_inherit_nopr __PRIVATE_arref_set_inherit_nopr_4
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void arref_set_inherit(ARREF(T) *self, [[in]] REF T *newobj, typename T);
 * >> void arref_set_inherit(ARREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define arref_set_inherit(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_set_inherit_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void arref_set_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj, typename T);
 * >> void arref_set_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define arref_set_inherit_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_set_inherit_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void arref_set_inherit(ARREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define arref_set_inherit __PRIVATE_arref_set_inherit_4
/* >> void arref_set_inherit_nopr(ARREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define arref_set_inherit_nopr __PRIVATE_arref_set_inherit_nopr_4
#endif /* !... */

/* ========== arref_set ========== */
#define __PRIVATE_arref_set_5(self, newobj, T, incref, decref)       \
	do {                                                             \
		T *__arsi_oldobj;                                            \
		incref(newobj);                                              \
		__PRIVATE_arref_xch_inherit_3(self, newobj, &__arsi_oldobj); \
		decref(__arsi_oldobj);                                       \
	}	__WHILE0
#define __PRIVATE_arref_set_nopr_5(self, newobj, T, incref, decref)       \
	do {                                                                  \
		T *__arsi_oldobj;                                                 \
		incref(newobj);                                                   \
		__PRIVATE_arref_xch_inherit_nopr_3(self, newobj, &__arsi_oldobj); \
		decref(__arsi_oldobj);                                            \
	}	__WHILE0
#define __PRIVATE_arref_set_3(self, newobj, T) \
	__PRIVATE_arref_set_5(self, newobj, T, incref, decref)
#define __PRIVATE_arref_set_nopr_3(self, newobj, T) \
	__PRIVATE_arref_set_nopr_5(self, newobj, T, incref, decref)
#ifdef __COMPILER_HAVE_TYPEOF
#define __PRIVATE_arref_set_2(self, newobj) \
	__PRIVATE_arref_set_3(self, newobj, __typeof__(*(self)->arr_obj))
#define __PRIVATE_arref_set_nopr_2(self, newobj) \
	__PRIVATE_arref_set_nopr_3(self, newobj, __typeof__(*(self)->arr_obj))
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> void arref_set(ARREF(T) *self, T *newobj);
 * >> void arref_set(ARREF(T) *self, T *newobj, typename T);
 * >> void arref_set(ARREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define arref_set(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_set_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void arref_set_nopr(ARREF(T) *self, T *newobj);
 * >> void arref_set_nopr(ARREF(T) *self, T *newobj, typename T);
 * >> void arref_set_nopr(ARREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define arref_set_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_set_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void arref_set(ARREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define arref_set __PRIVATE_arref_set_5
/* >> void arref_set_nopr(ARREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define arref_set_nopr __PRIVATE_arref_set_nopr_5
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void arref_set(ARREF(T) *self, T *newobj, typename T);
 * >> void arref_set(ARREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define arref_set(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_set_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void arref_set_nopr(ARREF(T) *self, T *newobj, typename T);
 * >> void arref_set_nopr(ARREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define arref_set_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_set_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void arref_set(ARREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define arref_set __PRIVATE_arref_set_5
/* >> void arref_set_nopr(ARREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define arref_set_nopr __PRIVATE_arref_set_nopr_5
#endif /* !... */

/* ========== arref_cmpxch_inherit ==========
 * NOTE: References are only inherited on success! */
#ifdef __ARCH_HAVE_AR_NOSMP
#define __PRIVATE_arref_cmpxch_inherit_4(self, oldobj, newobj, p_ok)      \
	__PRIVATE_AR_INTR_PUSHOFF();                                          \
	*(p_ok) = __hybrid_atomic_cmpxch((self)->arr_obj, oldobj, newobj,     \
	                                 __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_arref_cmpxch_inherit_nopr_4(self, oldobj, newobj, p_ok)  \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                      \
	*(p_ok) = __hybrid_atomic_cmpxch((self)->arr_obj, oldobj, newobj,      \
	                                 __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);  \
	__PRIVATE_AR_INTR_POP_NOPR()
#else /* __ARCH_HAVE_AR_NOSMP */
#define __PRIVATE_arref_cmpxch_inherit_4(self, oldobj, newobj, p_ok)                   \
	__PRIVATE_AR_INTR_PUSHOFF();                                                       \
	if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->arr_obj, oldobj, newobj,             \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) { \
		__PRIVATE_arref_waitfor(self)                                                  \
	}                                                                                  \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_arref_cmpxch_inherit_nopr_4(self, oldobj, newobj, p_ok)              \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                                  \
	if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->arr_obj, oldobj, newobj,             \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) { \
		__PRIVATE_arref_waitfor(self)                                                  \
	}                                                                                  \
	__PRIVATE_AR_INTR_POP_NOPR()
#endif /* !__ARCH_HAVE_AR_NOSMP */
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_arref_cmpxch_inherit_3(self, oldobj, newobj)               \
	__XBLOCK({                                                               \
		__BOOL __arcxi_ok;                                                   \
		__PRIVATE_arref_cmpxch_inherit_4(self, oldobj, newobj, &__arcxi_ok); \
		__XRETURN __arcxi_ok;                                                \
	})
#define __PRIVATE_arref_cmpxch_inherit_nopr_3(self, oldobj, newobj)               \
	__XBLOCK({                                                                    \
		__BOOL __arcxi_ok;                                                        \
		__PRIVATE_arref_cmpxch_inherit_nopr_4(self, oldobj, newobj, &__arcxi_ok); \
		__XRETURN __arcxi_ok;                                                     \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> bool arref_cmpxch_inherit(ARREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj);
 * >> void arref_cmpxch_inherit(ARREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define arref_cmpxch_inherit(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_inherit_, (__VA_ARGS__))(__VA_ARGS__)
/* >> bool arref_cmpxch_inherit_nopr(ARREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj);
 * >> void arref_cmpxch_inherit_nopr(ARREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define arref_cmpxch_inherit_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_inherit_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void arref_cmpxch_inherit(ARREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define arref_cmpxch_inherit __PRIVATE_arref_cmpxch_inherit_4
/* >> void arref_cmpxch_inherit_nopr(ARREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define arref_cmpxch_inherit_nopr __PRIVATE_arref_cmpxch_inherit_nopr_4
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#else  /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
/* >> void arref_cmpxch_inherit(ARREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define arref_cmpxch_inherit __PRIVATE_arref_cmpxch_inherit_4
/* >> void arref_cmpxch_inherit_nopr(ARREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define arref_cmpxch_inherit_nopr __PRIVATE_arref_cmpxch_inherit_nopr_4
#endif /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */

/* ========== arref_cmpxch_inherit_new ==========
 * NOTE: The reference to `newobj' is only inherited on success! */
#define __PRIVATE_arref_cmpxch_inherit_new_5(self, oldobj, newobj, p_ok, decref)       \
	__PRIVATE_AR_INTR_PUSHOFF();                                                       \
	if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->arr_obj, oldobj, newobj,             \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) { \
		__PRIVATE_arref_waitfor(self)                                                  \
		__PRIVATE_AR_INTR_BREAK();                                                     \
		decref(oldobj);                                                                \
	} else {                                                                           \
		__PRIVATE_AR_INTR_BREAK();                                                     \
	}                                                                                  \
	__PRIVATE_AR_INTR_END()
#define __PRIVATE_arref_cmpxch_inherit_new_nopr_5(self, oldobj, newobj, p_ok, decref)  \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                                  \
	if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->arr_obj, oldobj, newobj,             \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) { \
		__PRIVATE_arref_waitfor(self)                                                  \
		__PRIVATE_AR_INTR_BREAK();                                                     \
		decref(oldobj);                                                                \
	} else {                                                                           \
		__PRIVATE_AR_INTR_BREAK();                                                     \
	}                                                                                  \
	__PRIVATE_AR_INTR_END_NOPR()
#define __PRIVATE_arref_cmpxch_inherit_new_4(self, oldobj, newobj, p_ok) \
	__PRIVATE_arref_cmpxch_inherit_new_5(self, oldobj, newobj, p_ok, decref)
#define __PRIVATE_arref_cmpxch_inherit_new_nopr_4(self, oldobj, newobj, p_ok) \
	__PRIVATE_arref_cmpxch_inherit_new_nopr_5(self, oldobj, newobj, p_ok, decref)
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_arref_cmpxch_inherit_new_3(self, oldobj, newobj)                \
	__XBLOCK({                                                                    \
		__BOOL __arcxin_ok;                                                       \
		__PRIVATE_arref_cmpxch_inherit_new_4(self, oldobj, newobj, &__arcxin_ok); \
		__XRETURN __arcxin_ok;                                                    \
	})
#define __PRIVATE_arref_cmpxch_inherit_new_nopr_3(self, oldobj, newobj)                \
	__XBLOCK({                                                                         \
		__BOOL __arcxin_ok;                                                            \
		__PRIVATE_arref_cmpxch_inherit_new_nopr_4(self, oldobj, newobj, &__arcxin_ok); \
		__XRETURN __arcxin_ok;                                                         \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> bool arref_cmpxch_inherit_new(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj);
 * >> void arref_cmpxch_inherit_new(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok);
 * >> void arref_cmpxch_inherit_new(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define arref_cmpxch_inherit_new(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_inherit_new_, (__VA_ARGS__))(__VA_ARGS__)
/* >> bool arref_cmpxch_inherit_new_nopr(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj);
 * >> void arref_cmpxch_inherit_new_nopr(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok);
 * >> void arref_cmpxch_inherit_new_nopr(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define arref_cmpxch_inherit_new_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_inherit_new_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void arref_cmpxch_inherit_new(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define arref_cmpxch_inherit_new __PRIVATE_arref_cmpxch_inherit_new_5
/* >> void arref_cmpxch_inherit_new_nopr(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define arref_cmpxch_inherit_new_nopr __PRIVATE_arref_cmpxch_inherit_new_nopr_5
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void arref_cmpxch_inherit_new(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok);
 * >> void arref_cmpxch_inherit_new(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define arref_cmpxch_inherit_new(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_inherit_new_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void arref_cmpxch_inherit_new_nopr(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok);
 * >> void arref_cmpxch_inherit_new_nopr(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define arref_cmpxch_inherit_new_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_inherit_new_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void arref_cmpxch_inherit_new(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define arref_cmpxch_inherit_new __PRIVATE_arref_cmpxch_inherit_new_5
/* >> void arref_cmpxch_inherit_new_nopr(ARREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define arref_cmpxch_inherit_new_nopr __PRIVATE_arref_cmpxch_inherit_new_nopr_5
#endif /* !... */

/* ========== arref_cmpxch ========== */
#define __PRIVATE_arref_cmpxch_7(self, oldobj, newobj, p_ok, incref, decref, decref_nokill) \
	do {                                                                                    \
		incref(newobj);                                                                     \
		__PRIVATE_AR_INTR_PUSHOFF();                                                        \
		if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->arr_obj, oldobj, newobj,              \
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) {  \
			__PRIVATE_AR_INTR_BREAK();                                                      \
			decref(oldobj);                                                                 \
		} else {                                                                            \
			__PRIVATE_AR_INTR_BREAK();                                                      \
			decref_nokill(newobj);                                                          \
		}                                                                                   \
		__PRIVATE_AR_INTR_END();                                                            \
	}	__WHILE0
#define __PRIVATE_arref_cmpxch_nopr_7(self, oldobj, newobj, p_ok, incref, decref, decref_nokill) \
	do {                                                                                         \
		incref(newobj);                                                                          \
		__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                                        \
		if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->arr_obj, oldobj, newobj,                   \
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) {       \
			__PRIVATE_AR_INTR_BREAK_NOPR();                                                      \
			decref(oldobj);                                                                      \
		} else {                                                                                 \
			__PRIVATE_AR_INTR_BREAK_NOPR();                                                      \
			decref_nokill(newobj);                                                               \
		}                                                                                        \
		__PRIVATE_AR_INTR_END_NOPR();                                                            \
	}	__WHILE0
#define __PRIVATE_arref_cmpxch_6(self, oldobj, newobj, p_ok, incref, decref) \
	__PRIVATE_arref_cmpxch_7(self, oldobj, newobj, p_ok, incref, decref, decref)
#define __PRIVATE_arref_cmpxch_nopr_6(self, oldobj, newobj, p_ok, incref, decref) \
	__PRIVATE_arref_cmpxch_nopr_7(self, oldobj, newobj, p_ok, incref, decref, decref)
#define __PRIVATE_arref_cmpxch_4(self, oldobj, newobj, p_ok) \
	__PRIVATE_arref_cmpxch_7(self, oldobj, newobj, p_ok, incref, decref, decref_nokill)
#define __PRIVATE_arref_cmpxch_nopr_4(self, oldobj, newobj, p_ok) \
	__PRIVATE_arref_cmpxch_nopr_7(self, oldobj, newobj, p_ok, incref, decref, decref_nokill)
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_arref_cmpxch_3(self, oldobj, newobj)                \
	__XBLOCK({                                                        \
		__BOOL __arcxin_ok;                                           \
		__PRIVATE_arref_cmpxch_4(self, oldobj, newobj, &__arcxin_ok); \
		__XRETURN __arcxin_ok;                                        \
	})
#define __PRIVATE_arref_cmpxch_nopr_3(self, oldobj, newobj)                \
	__XBLOCK({                                                             \
		__BOOL __arcxin_ok;                                                \
		__PRIVATE_arref_cmpxch_nopr_4(self, oldobj, newobj, &__arcxin_ok); \
		__XRETURN __arcxin_ok;                                             \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> bool arref_cmpxch(ARREF(T) *self, T *oldobj, T *newobj);
 * >> void arref_cmpxch(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void arref_cmpxch(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void arref_cmpxch(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define arref_cmpxch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> bool arref_cmpxch_nopr(ARREF(T) *self, T *oldobj, T *newobj);
 * >> void arref_cmpxch_nopr(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void arref_cmpxch_nopr(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void arref_cmpxch_nopr(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define arref_cmpxch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void arref_cmpxch(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define arref_cmpxch __PRIVATE_arref_cmpxch_7
/* >> void arref_cmpxch_nopr(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define arref_cmpxch_nopr __PRIVATE_arref_cmpxch_nopr_7
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void arref_cmpxch(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void arref_cmpxch(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void arref_cmpxch(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define arref_cmpxch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void arref_cmpxch_nopr(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void arref_cmpxch_nopr(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void arref_cmpxch_nopr(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define arref_cmpxch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_cmpxch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void arref_cmpxch(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define arref_cmpxch __PRIVATE_arref_cmpxch_7
/* >> void arref_cmpxch_nopr(ARREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define arref_cmpxch_nopr __PRIVATE_arref_cmpxch_nopr_7
#endif /* !... */

/************************************************************************/



/************************************************************************/
/* AXREF Api                                                            */
/************************************************************************/

/* >> T *axref_ptr(AXREF(T) *self); */
#define axref_ptr(self) \
	__hybrid_atomic_load((self)->axr_obj, __ATOMIC_ACQUIRE)

/* ========== axref_get ========== */
#define __PRIVATE_axref_get_2(self, p_result) \
	__PRIVATE_axref_get_3(self, p_result, incref)
#define __PRIVATE_axref_get_nopr_2(self, p_result) \
	__PRIVATE_axref_get_nopr_3(self, p_result, incref)
#define __PRIVATE_axref_get_3(self, p_result, incref)                      \
	__PRIVATE_AR_INTR_PUSHOFF();                                           \
	__PRIVATE_axref_inccnt(self)                                           \
	*(p_result) = __hybrid_atomic_load((self)->axr_obj, __ATOMIC_SEQ_CST); \
	if (*(p_result) != __NULLPTR)                                          \
		incref(*(p_result));                                               \
	__PRIVATE_axref_deccnt(self)                                           \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_axref_get_nopr_3(self, p_result, incref)                 \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                      \
	__PRIVATE_axref_inccnt(self)                                           \
	*(p_result) = __hybrid_atomic_load((self)->axr_obj, __ATOMIC_SEQ_CST); \
	if (*(p_result) != __NULLPTR)                                          \
		incref(*(p_result));                                               \
	__PRIVATE_axref_deccnt(self)                                           \
	__PRIVATE_AR_INTR_POP_NOPR()
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_axref_get_1(self)                 \
	__XBLOCK({                                      \
		__typeof__((self)->axr_obj) __arg_result;   \
		__PRIVATE_axref_get_2(self, &__arg_result); \
		__XRETURN __arg_result;                     \
	})
#define __PRIVATE_axref_get_nopr_1(self)                 \
	__XBLOCK({                                           \
		__typeof__((self)->axr_obj) __arg_result;        \
		__PRIVATE_axref_get_nopr_2(self, &__arg_result); \
		__XRETURN __arg_result;                          \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> REF T *axref_get(AXREF(T) *self);
 * >> void   axref_get(AXREF(T) *self, [[out]] REF T **p_result);
 * >> void   axref_get(AXREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define axref_get(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_get_, (__VA_ARGS__))(__VA_ARGS__)
/* >> REF T *axref_get_nopr(AXREF(T) *self);
 * >> void   axref_get_nopr(AXREF(T) *self, [[out]] REF T **p_result);
 * >> void   axref_get_nopr(AXREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define axref_get_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_get_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_get(AXREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define axref_get __PRIVATE_axref_get_3
/* >> void axref_get_nopr(AXREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define axref_get_nopr __PRIVATE_axref_get_nopr_3
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void axref_get(AXREF(T) *self, [[out]] REF T **p_result);
 * >> void axref_get(AXREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define axref_get(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_get_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void axref_get_nopr(AXREF(T) *self, [[out]] REF T **p_result);
 * >> void axref_get_nopr(AXREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define axref_get_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_get_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void axref_get(AXREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define axref_get __PRIVATE_axref_get_3
/* >> void axref_get_nopr(AXREF(T) *self, [[out]] REF T **p_result, void incref(T *)); */
#define axref_get_nopr __PRIVATE_axref_get_nopr_3
#endif /* !... */

/* ========== axref_xch_inherit ========== */
#define __PRIVATE_axref_xch_inherit_3(self, newobj, p_oldobj)  \
	__PRIVATE_AR_INTR_PUSHOFF();                               \
	*(p_oldobj) = __hybrid_atomic_xch((self)->axr_obj, newobj, \
	                                  __ATOMIC_SEQ_CST);       \
	__PRIVATE_axref_waitfor(self)                              \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_axref_xch_inherit_nopr_3(self, newobj, p_oldobj) \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                              \
	*(p_oldobj) = __hybrid_atomic_xch((self)->axr_obj, newobj,     \
	                                  __ATOMIC_SEQ_CST);           \
	__PRIVATE_axref_waitfor(self)                                  \
	__PRIVATE_AR_INTR_POP_NOPR()
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_axref_xch_inherit_2(self, newobj)                  \
	__XBLOCK({                                                       \
		__typeof__((self)->axr_obj) __arxi_oldobj;                   \
		__PRIVATE_axref_xch_inherit_3(self, newobj, &__arxi_oldobj); \
		__XRETURN __arxi_oldobj;                                     \
	})
#define __PRIVATE_axref_xch_inherit_nopr_2(self, newobj)                  \
	__XBLOCK({                                                            \
		__typeof__((self)->axr_obj) __arxi_oldobj;                        \
		__PRIVATE_axref_xch_inherit_nopr_3(self, newobj, &__arxi_oldobj); \
		__XRETURN __arxi_oldobj;                                          \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> REF T *axref_xch_inherit(AXREF(T) *self, [[in]] REF T *newobj);
 * >> void   axref_xch_inherit(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define axref_xch_inherit(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_xch_inherit_, (__VA_ARGS__))(__VA_ARGS__)
/* >> REF T *axref_xch_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj);
 * >> void   axref_xch_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define axref_xch_inherit_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_xch_inherit_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_xch_inherit(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define axref_xch_inherit __PRIVATE_axref_xch_inherit_3
/* >> void axref_xch_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define axref_xch_inherit_nopr __PRIVATE_axref_xch_inherit_nopr_3
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#else  /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
/* >> void axref_xch_inherit(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define axref_xch_inherit __PRIVATE_axref_xch_inherit_3
/* >> void axref_xch_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj); */
#define axref_xch_inherit_nopr __PRIVATE_axref_xch_inherit_nopr_3
#endif /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */

/* ========== axref_steal ========== */
#define __PRIVATE_axref_steal_2(self, p_oldobj)                   \
	__PRIVATE_AR_INTR_PUSHOFF();                                  \
	*(p_oldobj) = __hybrid_atomic_xch((self)->axr_obj, __NULLPTR, \
	                                  __ATOMIC_SEQ_CST);          \
	__PRIVATE_axref_waitfor(self)                                 \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_axref_steal_nopr_2(self, p_oldobj)              \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                             \
	*(p_oldobj) = __hybrid_atomic_xch((self)->axr_obj, __NULLPTR, \
	                                  __ATOMIC_SEQ_CST);          \
	__PRIVATE_axref_waitfor(self)                                 \
	__PRIVATE_AR_INTR_POP_NOPR()
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_axref_steal_1(self)                  \
	__XBLOCK({                                         \
		__typeof__((self)->axr_obj) __arxi_oldobj;     \
		__PRIVATE_axref_steal_2(self, &__arxi_oldobj); \
		__XRETURN __arxi_oldobj;                       \
	})
#define __PRIVATE_axref_steal_nopr_1(self)                  \
	__XBLOCK({                                              \
		__typeof__((self)->axr_obj) __arxi_oldobj;          \
		__PRIVATE_axref_steal_nopr_2(self, &__arxi_oldobj); \
		__XRETURN __arxi_oldobj;                            \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> REF T *axref_steal(AXREF(T) *self);
 * >> void   axref_steal(AXREF(T) *self, [[out]] REF T **p_oldobj); */
#define axref_steal(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_steal_, (__VA_ARGS__))(__VA_ARGS__)
/* >> REF T *axref_steal_nopr(AXREF(T) *self);
 * >> void   axref_steal_nopr(AXREF(T) *self, [[out]] REF T **p_oldobj); */
#define axref_steal_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_steal_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_steal(AXREF(T) *self, [[out]] REF T **p_oldobj); */
#define axref_steal __PRIVATE_axref_steal_2
/* >> void axref_steal_nopr(AXREF(T) *self, [[out]] REF T **p_oldobj); */
#define axref_steal_nopr __PRIVATE_axref_steal_nopr_2
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#else  /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
/* >> void axref_steal(AXREF(T) *self, [[out]] REF T **p_oldobj); */
#define axref_steal __PRIVATE_axref_steal_2
/* >> void axref_steal_nopr(AXREF(T) *self, [[out]] REF T **p_oldobj); */
#define axref_steal_nopr __PRIVATE_axref_steal_nopr_2
#endif /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */

#ifdef __COMPILER_HAVE_TYPEOF
#define __PRIVATE_axref_cast(self, obj) (__typeof__((self)->axr_obj))(obj)
#else /* __COMPILER_HAVE_TYPEOF */
#define __PRIVATE_axref_cast(self, obj) obj
#endif /* !__COMPILER_HAVE_TYPEOF */

/* ========== axref_xch ========== */
#define __PRIVATE_axref_xch_3(self, newobj, p_oldobj) \
	__PRIVATE_axref_xch_4(self, newobj, p_oldobj, incref)
#define __PRIVATE_axref_xch_nopr_3(self, newobj, p_oldobj) \
	__PRIVATE_axref_xch_nopr_4(self, newobj, p_oldobj, incref)
#define __PRIVATE_axref_xch_4(self, newobj, p_oldobj, incref)  \
	do {                                                       \
		if ((newobj) != __NULLPTR)                             \
			incref(__PRIVATE_axref_cast(self, newobj));        \
		__PRIVATE_axref_xch_inherit_3(self, newobj, p_oldobj); \
	}	__WHILE0
#define __PRIVATE_axref_xch_nopr_4(self, newobj, p_oldobj, incref)  \
	do {                                                            \
		if ((newobj) != __NULLPTR)                                  \
			incref(__PRIVATE_axref_cast(self, newobj));             \
		__PRIVATE_axref_xch_inherit_nopr_3(self, newobj, p_oldobj); \
	}	__WHILE0
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_axref_xch_2(self, newobj)                         \
	__XBLOCK({                                                      \
		__typeof__((self)->axr_obj) __arx_oldobj;                   \
		if ((newobj) != __NULLPTR)                                  \
			incref(__PRIVATE_axref_cast(self, newobj));             \
		__PRIVATE_axref_xch_inherit_3(self, newobj, &__arx_oldobj); \
		__XRETURN __arx_oldobj;                                     \
	})
#define __PRIVATE_axref_xch_nopr_2(self, newobj)                         \
	__XBLOCK({                                                           \
		__typeof__((self)->axr_obj) __arx_oldobj;                        \
		if ((newobj) != __NULLPTR)                                       \
			incref(__PRIVATE_axref_cast(self, newobj));                  \
		__PRIVATE_axref_xch_inherit_nopr_3(self, newobj, &__arx_oldobj); \
		__XRETURN __arx_oldobj;                                          \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> REF T *axref_xch(AXREF(T) *self, [[in]] REF T *newobj);
 * >> void   axref_xch(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj);
 * >> void   axref_xch(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define axref_xch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_xch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> REF T *axref_xch_nopr(AXREF(T) *self, [[in]] REF T *newobj);
 * >> void   axref_xch_nopr(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj);
 * >> void   axref_xch_nopr(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define axref_xch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_xch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_xch(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define axref_xch __PRIVATE_axref_xch_4
/* >> void axref_xch_nopr(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define axref_xch_nopr __PRIVATE_axref_xch_nopr_4
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void   axref_xch(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj);
 * >> void   axref_xch(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define axref_xch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_xch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void   axref_xch_nopr(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj);
 * >> void   axref_xch_nopr(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define axref_xch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_xch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void   axref_xch(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define axref_xch __PRIVATE_axref_xch_4
/* >> void   axref_xch_nopr(AXREF(T) *self, [[in]] REF T *newobj, [[out]] REF T **p_oldobj, void incref(T *)); */
#define axref_xch_nopr __PRIVATE_axref_xch_nopr_4
#endif /* !... */

/* ========== axref_set_inherit ========== */
#define __PRIVATE_axref_set_inherit_4(self, newobj, T, decref)       \
	do {                                                             \
		T *__arsi_oldobj;                                            \
		__PRIVATE_axref_xch_inherit_3(self, newobj, &__arsi_oldobj); \
		if (__arsi_oldobj != __NULLPTR)                              \
			decref(__arsi_oldobj);                                   \
	}	__WHILE0
#define __PRIVATE_axref_set_inherit_nopr_4(self, newobj, T, decref)       \
	do {                                                                  \
		T *__arsi_oldobj;                                                 \
		__PRIVATE_axref_xch_inherit_nopr_3(self, newobj, &__arsi_oldobj); \
		if (__arsi_oldobj != __NULLPTR)                                   \
			decref(__arsi_oldobj);                                        \
	}	__WHILE0
#define __PRIVATE_axref_set_inherit_3(self, newobj, T) \
	__PRIVATE_axref_set_inherit_4(self, newobj, T, decref)
#define __PRIVATE_axref_set_inherit_nopr_3(self, newobj, T) \
	__PRIVATE_axref_set_inherit_nopr_4(self, newobj, T, decref)
#ifdef __COMPILER_HAVE_TYPEOF
#define __PRIVATE_axref_set_inherit_2(self, newobj) \
	__PRIVATE_axref_set_inherit_3(self, newobj, __typeof__(*(self)->axr_obj))
#define __PRIVATE_axref_set_inherit_nopr_2(self, newobj) \
	__PRIVATE_axref_set_inherit_nopr_3(self, newobj, __typeof__(*(self)->axr_obj))
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> void axref_set_inherit(AXREF(T) *self, [[in]] REF T *newobj);
 * >> void axref_set_inherit(AXREF(T) *self, [[in]] REF T *newobj, typename T);
 * >> void axref_set_inherit(AXREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define axref_set_inherit(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_set_inherit_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void axref_set_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj);
 * >> void axref_set_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj, typename T);
 * >> void axref_set_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define axref_set_inherit_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_set_inherit_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_set_inherit(AXREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define axref_set_inherit __PRIVATE_axref_set_inherit_4
/* >> void axref_set_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define axref_set_inherit_nopr __PRIVATE_axref_set_inherit_nopr_4
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void axref_set_inherit(AXREF(T) *self, [[in]] REF T *newobj, typename T);
 * >> void axref_set_inherit(AXREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define axref_set_inherit(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_set_inherit_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void axref_set_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj, typename T);
 * >> void axref_set_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define axref_set_inherit_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_set_inherit_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void axref_set_inherit(AXREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define axref_set_inherit __PRIVATE_axref_set_inherit_4
/* >> void axref_set_inherit_nopr(AXREF(T) *self, [[in]] REF T *newobj, typename T, void decref(T *)); */
#define axref_set_inherit_nopr __PRIVATE_axref_set_inherit_nopr_4
#endif /* !... */

/* ========== axref_set ========== */
#define __PRIVATE_axref_set_5(self, newobj, T, incref, decref)       \
	do {                                                             \
		T *__arsi_oldobj;                                            \
		if ((newobj) != __NULLPTR)                                   \
			incref(__PRIVATE_axref_cast(self, newobj));              \
		__PRIVATE_axref_xch_inherit_3(self, newobj, &__arsi_oldobj); \
		if (__arsi_oldobj != __NULLPTR)                              \
			decref(__arsi_oldobj);                                   \
	}	__WHILE0
#define __PRIVATE_axref_set_nopr_5(self, newobj, T, incref, decref)       \
	do {                                                                  \
		T *__arsi_oldobj;                                                 \
		if ((newobj) != __NULLPTR)                                        \
			incref(__PRIVATE_axref_cast(self, newobj));                   \
		__PRIVATE_axref_xch_inherit_nopr_3(self, newobj, &__arsi_oldobj); \
		if (__arsi_oldobj != __NULLPTR)                                   \
			decref(__arsi_oldobj);                                        \
	}	__WHILE0
#define __PRIVATE_axref_set_3(self, newobj, T) \
	__PRIVATE_axref_set_5(self, newobj, T, incref, decref)
#define __PRIVATE_axref_set_nopr_3(self, newobj, T) \
	__PRIVATE_axref_set_nopr_5(self, newobj, T, incref, decref)
#ifdef __COMPILER_HAVE_TYPEOF
#define __PRIVATE_axref_set_2(self, newobj) \
	__PRIVATE_axref_set_3(self, newobj, __typeof__(*(self)->axr_obj))
#define __PRIVATE_axref_set_nopr_2(self, newobj) \
	__PRIVATE_axref_set_nopr_3(self, newobj, __typeof__(*(self)->axr_obj))
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> void axref_set(AXREF(T) *self, T *newobj);
 * >> void axref_set(AXREF(T) *self, T *newobj, typename T);
 * >> void axref_set(AXREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define axref_set(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_set_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void axref_set_nopr(AXREF(T) *self, T *newobj);
 * >> void axref_set_nopr(AXREF(T) *self, T *newobj, typename T);
 * >> void axref_set_nopr(AXREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define axref_set_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_set_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_set(AXREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define axref_set __PRIVATE_axref_set_5
/* >> void axref_set_nopr(AXREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define axref_set_nopr __PRIVATE_axref_set_nopr_5
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void axref_set(AXREF(T) *self, T *newobj, typename T);
 * >> void axref_set(AXREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define axref_set(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_set_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void axref_set_nopr(AXREF(T) *self, T *newobj, typename T);
 * >> void axref_set_nopr(AXREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define axref_set_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_set_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void axref_set(AXREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define axref_set __PRIVATE_axref_set_5
/* >> void axref_set_nopr(AXREF(T) *self, T *newobj, typename T, void incref(T *), void decref(T *)); */
#define axref_set_nopr __PRIVATE_axref_set_nopr_5
#endif /* !... */

/* ========== axref_clear ========== */
#define __PRIVATE_axref_clear_3(self, T, decref)                        \
	do {                                                                \
		T *__arsi_oldobj;                                               \
		__PRIVATE_axref_xch_inherit_3(self, __NULLPTR, &__arsi_oldobj); \
		if (__arsi_oldobj != __NULLPTR)                                 \
			decref(__arsi_oldobj);                                      \
	}	__WHILE0
#define __PRIVATE_axref_clear_nopr_3(self, T, decref)                        \
	do {                                                                     \
		T *__arsi_oldobj;                                                    \
		__PRIVATE_axref_xch_inherit_nopr_3(self, __NULLPTR, &__arsi_oldobj); \
		if (__arsi_oldobj != __NULLPTR)                                      \
			decref(__arsi_oldobj);                                           \
	}	__WHILE0
#define __PRIVATE_axref_clear_2(self, T) \
	__PRIVATE_axref_clear_3(self, T, decref)
#define __PRIVATE_axref_clear_nopr_2(self, T) \
	__PRIVATE_axref_clear_nopr_3(self, T, decref)
#ifdef __COMPILER_HAVE_TYPEOF
#define __PRIVATE_axref_clear_1(self) \
	__PRIVATE_axref_clear_2(self, __typeof__(*(self)->axr_obj))
#define __PRIVATE_axref_clear_nopr_1(self) \
	__PRIVATE_axref_clear_nopr_2(self, __typeof__(*(self)->axr_obj))
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> void axref_clear(AXREF(T) *self);
 * >> void axref_clear(AXREF(T) *self, typename T);
 * >> void axref_clear(AXREF(T) *self, typename T, void decref(T *)); */
#define axref_clear(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_clear_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void axref_clear_nopr(AXREF(T) *self);
 * >> void axref_clear_nopr(AXREF(T) *self, typename T);
 * >> void axref_clear_nopr(AXREF(T) *self, typename T, void decref(T *)); */
#define axref_clear_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_clear_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_clear(AXREF(T) *self, typename T, void decref(T *)); */
#define axref_clear __PRIVATE_axref_clear_3
/* >> void axref_clear_nopr(AXREF(T) *self, typename T, void decref(T *)); */
#define axref_clear_nopr __PRIVATE_axref_clear_nopr_3
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void axref_clear(AXREF(T) *self, typename T);
 * >> void axref_clear(AXREF(T) *self, typename T, void decref(T *)); */
#define axref_clear(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_clear_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void axref_clear_nopr(AXREF(T) *self, typename T);
 * >> void axref_clear_nopr(AXREF(T) *self, typename T, void decref(T *)); */
#define axref_clear_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_clear_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void axref_clear(AXREF(T) *self, typename T, void decref(T *)); */
#define axref_clear __PRIVATE_axref_clear_3
/* >> void axref_clear_nopr(AXREF(T) *self, typename T, void decref(T *)); */
#define axref_clear_nopr __PRIVATE_axref_clear_nopr_3
#endif /* !... */

/* ========== axref_cmpxch_inherit ==========
 * NOTE: References are only inherited on success! */
#ifdef __ARCH_HAVE_AR_NOSMP
#define __PRIVATE_axref_cmpxch_inherit_4(self, oldobj, newobj, p_ok)      \
	__PRIVATE_AR_INTR_PUSHOFF();                                          \
	*(p_ok) = __hybrid_atomic_cmpxch((self)->axr_obj, oldobj, newobj,     \
	                                 __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_axref_cmpxch_inherit_nopr_4(self, oldobj, newobj, p_ok) \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                     \
	*(p_ok) = __hybrid_atomic_cmpxch((self)->axr_obj, oldobj, newobj,     \
	                                 __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); \
	__PRIVATE_AR_INTR_POP_NOPR()
#else /* __ARCH_HAVE_AR_NOSMP */
#define __PRIVATE_axref_cmpxch_inherit_4(self, oldobj, newobj, p_ok)                   \
	__PRIVATE_AR_INTR_PUSHOFF();                                                       \
	if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->axr_obj, oldobj, newobj,             \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) { \
		__PRIVATE_axref_waitfor(self)                                                  \
	}                                                                                  \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_axref_cmpxch_inherit_nopr_4(self, oldobj, newobj, p_ok)              \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                                  \
	if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->axr_obj, oldobj, newobj,             \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) { \
		__PRIVATE_axref_waitfor(self)                                                  \
	}                                                                                  \
	__PRIVATE_AR_INTR_POP_NOPR()
#endif /* !__ARCH_HAVE_AR_NOSMP */
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_axref_cmpxch_inherit_3(self, oldobj, newobj)               \
	__XBLOCK({                                                               \
		__BOOL __arcxi_ok;                                                   \
		__PRIVATE_axref_cmpxch_inherit_4(self, oldobj, newobj, &__arcxi_ok); \
		__XRETURN __arcxi_ok;                                                \
	})
#define __PRIVATE_axref_cmpxch_inherit_nopr_3(self, oldobj, newobj)               \
	__XBLOCK({                                                                    \
		__BOOL __arcxi_ok;                                                        \
		__PRIVATE_axref_cmpxch_inherit_nopr_4(self, oldobj, newobj, &__arcxi_ok); \
		__XRETURN __arcxi_ok;                                                     \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> bool axref_cmpxch_inherit(AXREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj);
 * >> void axref_cmpxch_inherit(AXREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define axref_cmpxch_inherit(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_inherit_, (__VA_ARGS__))(__VA_ARGS__)
/* >> bool axref_cmpxch_inherit_nopr(AXREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj);
 * >> void axref_cmpxch_inherit_nopr(AXREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define axref_cmpxch_inherit_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_inherit_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_cmpxch_inherit(AXREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define axref_cmpxch_inherit __PRIVATE_axref_cmpxch_inherit_4
/* >> void axref_cmpxch_inherit_nopr(AXREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define axref_cmpxch_inherit_nopr __PRIVATE_axref_cmpxch_inherit_nopr_4
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#else  /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
/* >> void axref_cmpxch_inherit(AXREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define axref_cmpxch_inherit __PRIVATE_axref_cmpxch_inherit_4
/* >> void axref_cmpxch_inherit_nopr(AXREF(T) *self, [[out]] REF T *oldobj, [[in]] REF T *newobj, bool *p_ok); */
#define axref_cmpxch_inherit_nopr __PRIVATE_axref_cmpxch_inherit_nopr_4
#endif /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */

/* ========== axref_cmpxch_inherit_new ==========
 * NOTE: The reference to `newobj' is only inherited on success! */
#define __PRIVATE_axref_cmpxch_inherit_new_5(self, oldobj, newobj, p_ok, decref)       \
	__PRIVATE_AR_INTR_PUSHOFF();                                                       \
	if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->axr_obj, oldobj, newobj,             \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) { \
		__PRIVATE_axref_waitfor(self)                                                  \
		__PRIVATE_AR_INTR_BREAK();                                                     \
		if ((oldobj) != __NULLPTR)                                                     \
			decref(__PRIVATE_axref_cast(self, oldobj));                                \
	} else {                                                                           \
		__PRIVATE_AR_INTR_BREAK();                                                     \
	}                                                                                  \
	__PRIVATE_AR_INTR_END()
#define __PRIVATE_axref_cmpxch_inherit_new_nopr_5(self, oldobj, newobj, p_ok, decref)  \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                                  \
	if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->axr_obj, oldobj, newobj,             \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) { \
		__PRIVATE_axref_waitfor(self)                                                  \
		__PRIVATE_AR_INTR_BREAK();                                                     \
		if ((oldobj) != __NULLPTR)                                                     \
			decref(__PRIVATE_axref_cast(self, oldobj));                                \
	} else {                                                                           \
		__PRIVATE_AR_INTR_BREAK();                                                     \
	}                                                                                  \
	__PRIVATE_AR_INTR_END_NOPR()
#define __PRIVATE_axref_cmpxch_inherit_new_4(self, oldobj, newobj, p_ok) \
	__PRIVATE_axref_cmpxch_inherit_new_5(self, oldobj, newobj, p_ok, decref)
#define __PRIVATE_axref_cmpxch_inherit_new_nopr_4(self, oldobj, newobj, p_ok) \
	__PRIVATE_axref_cmpxch_inherit_new_nopr_5(self, oldobj, newobj, p_ok, decref)
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_axref_cmpxch_inherit_new_3(self, oldobj, newobj)                \
	__XBLOCK({                                                                    \
		__BOOL __arcxin_ok;                                                       \
		__PRIVATE_axref_cmpxch_inherit_new_4(self, oldobj, newobj, &__arcxin_ok); \
		__XRETURN __arcxin_ok;                                                    \
	})
#define __PRIVATE_axref_cmpxch_inherit_new_nopr_3(self, oldobj, newobj)                \
	__XBLOCK({                                                                         \
		__BOOL __arcxin_ok;                                                            \
		__PRIVATE_axref_cmpxch_inherit_new_nopr_4(self, oldobj, newobj, &__arcxin_ok); \
		__XRETURN __arcxin_ok;                                                         \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> bool axref_cmpxch_inherit_new(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj);
 * >> void axref_cmpxch_inherit_new(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok);
 * >> void axref_cmpxch_inherit_new(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define axref_cmpxch_inherit_new(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_inherit_new_, (__VA_ARGS__))(__VA_ARGS__)
/* >> bool axref_cmpxch_inherit_new_nopr(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj);
 * >> void axref_cmpxch_inherit_new_nopr(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok);
 * >> void axref_cmpxch_inherit_new_nopr(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define axref_cmpxch_inherit_new_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_inherit_new_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_cmpxch_inherit_new(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define axref_cmpxch_inherit_new __PRIVATE_axref_cmpxch_inherit_new_5
/* >> void axref_cmpxch_inherit_new_nopr(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define axref_cmpxch_inherit_new_nopr __PRIVATE_axref_cmpxch_inherit_new_nopr_5
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void axref_cmpxch_inherit_new(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok);
 * >> void axref_cmpxch_inherit_new(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define axref_cmpxch_inherit_new(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_inherit_new_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void axref_cmpxch_inherit_new_nopr(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok);
 * >> void axref_cmpxch_inherit_new_nopr(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define axref_cmpxch_inherit_new_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_inherit_new_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void axref_cmpxch_inherit_new(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define axref_cmpxch_inherit_new __PRIVATE_axref_cmpxch_inherit_new_5
/* >> void axref_cmpxch_inherit_new_nopr(AXREF(T) *self, T *oldobj, [[in]] REF T *newobj, bool *p_ok, void decref(T *)); */
#define axref_cmpxch_inherit_new_nopr __PRIVATE_axref_cmpxch_inherit_new_nopr_5
#endif /* !... */

/* ========== axref_cmpxch ========== */
#define __PRIVATE_axref_cmpxch_7(self, oldobj, newobj, p_ok, incref, decref, decref_nokill) \
	do {                                                                                    \
		if ((newobj) != __NULLPTR)                                                          \
			incref(__PRIVATE_axref_cast(self, newobj));                                     \
		__PRIVATE_AR_INTR_PUSHOFF();                                                        \
		if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->axr_obj, oldobj, newobj,              \
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) {  \
			__PRIVATE_AR_INTR_BREAK();                                                      \
			if ((oldobj) != __NULLPTR)                                                      \
				decref(__PRIVATE_axref_cast(self, oldobj));                                 \
		} else {                                                                            \
			__PRIVATE_AR_INTR_BREAK();                                                      \
			if ((newobj) != __NULLPTR)                                                      \
				decref_nokill(__PRIVATE_axref_cast(self, newobj));                          \
		}                                                                                   \
		__PRIVATE_AR_INTR_END();                                                            \
	}	__WHILE0
#define __PRIVATE_axref_cmpxch_nopr_7(self, oldobj, newobj, p_ok, incref, decref, decref_nokill) \
	do {                                                                                         \
		if ((newobj) != __NULLPTR)                                                               \
			incref(__PRIVATE_axref_cast(self, newobj));                                          \
		__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                                        \
		if ((*(p_ok) = __hybrid_atomic_cmpxch((self)->axr_obj, oldobj, newobj,                   \
		                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) != 0) {       \
			__PRIVATE_AR_INTR_BREAK_NOPR();                                                      \
			if ((oldobj) != __NULLPTR)                                                           \
				decref(__PRIVATE_axref_cast(self, oldobj));                                      \
		} else {                                                                                 \
			__PRIVATE_AR_INTR_BREAK_NOPR();                                                      \
			if ((newobj) != __NULLPTR)                                                           \
				decref_nokill(__PRIVATE_axref_cast(self, newobj));                               \
		}                                                                                        \
		__PRIVATE_AR_INTR_END_NOPR();                                                            \
	}	__WHILE0
#define __PRIVATE_axref_cmpxch_6(self, oldobj, newobj, p_ok, incref, decref) \
	__PRIVATE_axref_cmpxch_7(self, oldobj, newobj, p_ok, incref, decref, decref)
#define __PRIVATE_axref_cmpxch_nopr_6(self, oldobj, newobj, p_ok, incref, decref) \
	__PRIVATE_axref_cmpxch_nopr_7(self, oldobj, newobj, p_ok, incref, decref, decref)
#define __PRIVATE_axref_cmpxch_4(self, oldobj, newobj, p_ok) \
	__PRIVATE_axref_cmpxch_7(self, oldobj, newobj, p_ok, incref, decref, decref_nokill)
#define __PRIVATE_axref_cmpxch_nopr_4(self, oldobj, newobj, p_ok) \
	__PRIVATE_axref_cmpxch_nopr_7(self, oldobj, newobj, p_ok, incref, decref, decref_nokill)
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_axref_cmpxch_3(self, oldobj, newobj)                \
	__XBLOCK({                                                        \
		__BOOL __arcxin_ok;                                           \
		__PRIVATE_axref_cmpxch_4(self, oldobj, newobj, &__arcxin_ok); \
		__XRETURN __arcxin_ok;                                        \
	})
#define __PRIVATE_axref_cmpxch_nopr_3(self, oldobj, newobj)                \
	__XBLOCK({                                                             \
		__BOOL __arcxin_ok;                                                \
		__PRIVATE_axref_cmpxch_nopr_4(self, oldobj, newobj, &__arcxin_ok); \
		__XRETURN __arcxin_ok;                                             \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> bool axref_cmpxch(AXREF(T) *self, T *oldobj, T *newobj);
 * >> void axref_cmpxch(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void axref_cmpxch(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void axref_cmpxch(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define axref_cmpxch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> bool axref_cmpxch_nopr(AXREF(T) *self, T *oldobj, T *newobj);
 * >> void axref_cmpxch_nopr(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void axref_cmpxch_nopr(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void axref_cmpxch_nopr(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define axref_cmpxch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void axref_cmpxch(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define axref_cmpxch __PRIVATE_axref_cmpxch_7
/* >> void axref_cmpxch_nopr(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define axref_cmpxch_nopr __PRIVATE_axref_cmpxch_nopr_7
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void axref_cmpxch(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void axref_cmpxch(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void axref_cmpxch(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define axref_cmpxch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void axref_cmpxch_nopr(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok);
 * >> void axref_cmpxch_nopr(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *));
 * >> void axref_cmpxch_nopr(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define axref_cmpxch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_cmpxch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void axref_cmpxch(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define axref_cmpxch __PRIVATE_axref_cmpxch_7
/* >> void axref_cmpxch_nopr(AXREF(T) *self, T *oldobj, T *newobj, bool *p_ok, void incref(T *), void decref(T *), void decref_nokill(T *)); */
#define axref_cmpxch_nopr __PRIVATE_axref_cmpxch_nopr_7
#endif /* !... */

/************************************************************************/



/************************************************************************/
/* AWREF Api                                                            */
/************************************************************************/
/* >> T *awref_ptr(AWREF(T) *self); */
#define awref_ptr(self) \
	__hybrid_atomic_load((self)->awr_obj, __ATOMIC_ACQUIRE)

#define __PRIVATE_awref_get_3(self, p_result, tryincref)                   \
	__PRIVATE_AR_INTR_PUSHOFF();                                           \
	__PRIVATE_awref_inccnt(self)                                           \
	*(p_result) = __hybrid_atomic_load((self)->awr_obj, __ATOMIC_SEQ_CST); \
	if (*(p_result) != __NULLPTR && !tryincref(*(p_result)))               \
		*(p_result) = __NULLPTR;                                           \
	__PRIVATE_awref_deccnt(self)                                           \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_awref_get_nopr_3(self, p_result, tryincref)              \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                      \
	__PRIVATE_awref_inccnt(self)                                           \
	*(p_result) = __hybrid_atomic_load((self)->awr_obj, __ATOMIC_SEQ_CST); \
	if (*(p_result) != __NULLPTR && !tryincref(*(p_result)))               \
		*(p_result) = __NULLPTR;                                           \
	__PRIVATE_awref_deccnt(self)                                           \
	__PRIVATE_AR_INTR_POP_NOPR()
#define __PRIVATE_awref_get_2(self, p_result) \
	__PRIVATE_awref_get_3(self, p_result, tryincref)
#define __PRIVATE_awref_get_nopr_2(self, p_result) \
	__PRIVATE_awref_get_nopr_3(self, p_result, tryincref)
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_awref_get_1(self)                  \
	__XBLOCK({                                       \
		__typeof__((self)->awr_obj) __awrg_result;   \
		__PRIVATE_awref_get_2(self, &__awrg_result); \
		__XRETURN __awrg_result;                     \
	})
#define __PRIVATE_awref_get_nopr_1(self)                  \
	__XBLOCK({                                            \
		__typeof__((self)->awr_obj) __awrg_result;        \
		__PRIVATE_awref_get_nopr_2(self, &__awrg_result); \
		__XRETURN __awrg_result;                          \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> REF T *awref_get(AWREF(T) *self);
 * >> void   awref_get(AWREF(T) *self, [[out]] REF T **p_result);
 * >> void   awref_get(AWREF(T) *self, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_get(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_get_, (__VA_ARGS__))(__VA_ARGS__)
/* >> REF T *awref_get_nopr(AWREF(T) *self);
 * >> void   awref_get_nopr(AWREF(T) *self, [[out]] REF T **p_result);
 * >> void   awref_get_nopr(AWREF(T) *self, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_get_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_get_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void   awref_get(AWREF(T) *self, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_get __PRIVATE_awref_get_3
/* >> void   awref_get_nopr(AWREF(T) *self, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_get_nopr __PRIVATE_awref_get_nopr_3
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void   awref_get(AWREF(T) *self, [[out]] REF T **p_result);
 * >> void   awref_get(AWREF(T) *self, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_get(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_get_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void   awref_get_nopr(AWREF(T) *self, [[out]] REF T **p_result);
 * >> void   awref_get_nopr(AWREF(T) *self, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_get_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_get_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void   awref_get(AWREF(T) *self, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_get __PRIVATE_awref_get_3
/* >> void   awref_get_nopr(AWREF(T) *self, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_get_nopr __PRIVATE_awref_get_nopr_3
#endif /* !... */

/* >> void awref_set(AWREF(T) *self, T *newobj); */
#define awref_set(self, newobj)                                       \
	__PRIVATE_AR_INTR_PUSHOFF();                                      \
	__hybrid_atomic_store((self)->awr_obj, newobj, __ATOMIC_SEQ_CST); \
	__PRIVATE_awref_waitfor(self)                                     \
	__PRIVATE_AR_INTR_POP()
#define awref_set_nopr(self, newobj)                                  \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                 \
	__hybrid_atomic_store((self)->awr_obj, newobj, __ATOMIC_SEQ_CST); \
	__PRIVATE_awref_waitfor(self)                                     \
	__PRIVATE_AR_INTR_POP_NOPR()
#define __PRIVATE_awref_xch_4(self, newobj, p_oldobj, tryincref) \
	__PRIVATE_AR_INTR_PUSHOFF();                                 \
	*(p_oldobj) = __hybrid_atomic_xch((self)->awr_obj, newobj,   \
	                                  __ATOMIC_SEQ_CST);         \
	if (*(p_oldobj) != __NULLPTR && !tryincref(*(p_oldobj)))     \
		*(p_oldobj) = __NULLPTR;                                 \
	__PRIVATE_awref_waitfor(self)                                \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_awref_xch_nopr_4(self, newobj, p_oldobj, tryincref) \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                 \
	*(p_oldobj) = __hybrid_atomic_xch((self)->awr_obj, newobj,        \
	                                  __ATOMIC_SEQ_CST);              \
	if (*(p_oldobj) != __NULLPTR && !tryincref(*(p_oldobj)))          \
		*(p_oldobj) = __NULLPTR;                                      \
	__PRIVATE_awref_waitfor(self)                                     \
	__PRIVATE_AR_INTR_POP_NOPR()
#define __PRIVATE_awref_xch_3(self, newobj, p_oldobj) \
	__PRIVATE_awref_xch_4(self, newobj, p_oldobj, tryincref)
#define __PRIVATE_awref_xch_nopr_3(self, newobj, p_oldobj) \
	__PRIVATE_awref_xch_nopr_4(self, newobj, p_oldobj, tryincref)
#if !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_awref_xch_2(self, newobj)                  \
	__XBLOCK({                                               \
		__typeof__((self)->awr_obj) __awrx_oldobj;           \
		__PRIVATE_awref_xch_3(self, newobj, &__awrx_oldobj); \
		__XRETURN __awrx_oldobj;                             \
	})
#define __PRIVATE_awref_xch_nopr_2(self, newobj)                  \
	__XBLOCK({                                                    \
		__typeof__((self)->awr_obj) __awrx_oldobj;                \
		__PRIVATE_awref_xch_nopr_3(self, newobj, &__awrx_oldobj); \
		__XRETURN __awrx_oldobj;                                  \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> REF T *awref_xch(AWREF(T) *self, T *newobj);
 * >> void   awref_xch(AWREF(T) *self, T *newobj, [[out]] REF T **p_result);
 * >> void   awref_xch(AWREF(T) *self, T *newobj, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_xch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_xch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> REF T *awref_xch_nopr(AWREF(T) *self, T *newobj);
 * >> void   awref_xch_nopr(AWREF(T) *self, T *newobj, [[out]] REF T **p_result);
 * >> void   awref_xch_nopr(AWREF(T) *self, T *newobj, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_xch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_xch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void   awref_xch(AWREF(T) *self, T *newobj, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_xch __PRIVATE_awref_xch_4
/* >> void   awref_xch_nopr(AWREF(T) *self, T *newobj, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_xch_nopr __PRIVATE_awref_xch_nopr_4
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
/* >> void   awref_xch(AWREF(T) *self, T *newobj, [[out]] REF T **p_result);
 * >> void   awref_xch(AWREF(T) *self, T *newobj, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_xch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_xch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void   awref_xch_nopr(AWREF(T) *self, T *newobj, [[out]] REF T **p_result);
 * >> void   awref_xch_nopr(AWREF(T) *self, T *newobj, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_xch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_xch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* ... */
/* >> void   awref_xch(AWREF(T) *self, T *newobj, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_xch __PRIVATE_awref_xch_4
/* >> void   awref_xch_nopr(AWREF(T) *self, T *newobj, [[out]] REF T **p_result, bool tryincref(T *)); */
#define awref_xch_nopr __PRIVATE_awref_xch_nopr_4
#endif /* !... */

/* >> void awref_clear(AWREF(T) *self); */
#define awref_clear(self)                                                \
	__PRIVATE_AR_INTR_PUSHOFF();                                         \
	__hybrid_atomic_store((self)->awr_obj, __NULLPTR, __ATOMIC_SEQ_CST); \
	__PRIVATE_awref_waitfor(self)                                        \
	__PRIVATE_AR_INTR_POP()

/* >> void awref_clear_nopr(AWREF(T) *self); */
#define awref_clear_nopr(self)                                           \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                    \
	__hybrid_atomic_store((self)->awr_obj, __NULLPTR, __ATOMIC_SEQ_CST); \
	__PRIVATE_awref_waitfor(self)                                        \
	__PRIVATE_AR_INTR_POP_NOPR()

#define __PRIVATE_awref_cmpxch_4(self, oldobj, newobj, p_ok)              \
	__PRIVATE_AR_INTR_PUSHOFF();                                          \
	*(p_ok) = __hybrid_atomic_cmpxch((self)->awr_obj, oldobj, newobj,     \
	                                 __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); \
	__PRIVATE_awref_waitfor(self)                                         \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_awref_cmpxch_nopr_4(self, oldobj, newobj, p_ok)         \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                     \
	*(p_ok) = __hybrid_atomic_cmpxch((self)->awr_obj, oldobj, newobj,     \
	                                 __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); \
	__PRIVATE_awref_waitfor(self)                                         \
	__PRIVATE_AR_INTR_POP_NOPR()
#ifndef __NO_XBLOCK
#define __PRIVATE_awref_cmpxch_3(self, oldobj, newobj)               \
	__XBLOCK({                                                       \
		__BOOL __awrcx_ok;                                           \
		__PRIVATE_awref_cmpxch_4(self, oldobj, newobj, &__awrcx_ok); \
		__XRETURN __awrcx_ok;                                        \
	})
#define __PRIVATE_awref_cmpxch_nopr_3(self, oldobj, newobj)               \
	__XBLOCK({                                                            \
		__BOOL __awrcx_ok;                                                \
		__PRIVATE_awref_cmpxch_nopr_4(self, oldobj, newobj, &__awrcx_ok); \
		__XRETURN __awrcx_ok;                                             \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> bool awref_cmpxch(AWREF(T) *self, T *oldobj, T *newobj);
 * >> void awref_cmpxch(AWREF(T) *self, T *oldobj, T *newobj, bool *p_ok); */
#define awref_cmpxch(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
/* >> bool awref_cmpxch_nopr(AWREF(T) *self, T *oldobj, T *newobj);
 * >> void awref_cmpxch_nopr(AWREF(T) *self, T *oldobj, T *newobj, bool *p_ok); */
#define awref_cmpxch_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_cmpxch_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void awref_cmpxch(AWREF(T) *self, T *oldobj, T *newobj, bool *p_ok); */
#define awref_cmpxch __PRIVATE_awref_cmpxch_4
/* >> void awref_cmpxch_nopr(AWREF(T) *self, T *oldobj, T *newobj, bool *p_ok); */
#define awref_cmpxch_nopr __PRIVATE_awref_cmpxch_nopr_4
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#else /* ... */
/* >> void awref_cmpxch(AWREF(T) *self, T *oldobj, T *newobj, bool *p_ok); */
#define awref_cmpxch __PRIVATE_awref_cmpxch_4
/* >> void awref_cmpxch_nopr(AWREF(T) *self, T *oldobj, T *newobj, bool *p_ok); */
#define awref_cmpxch_nopr __PRIVATE_awref_cmpxch_nopr_4
#endif /* !... */

#define __PRIVATE_awref_replacedead_5(self, newobj, p_ok, T, wasdestroyed)        \
	__PRIVATE_AR_INTR_PUSHOFF();                                                  \
	T *__awrrd_oldobj;                                                            \
	for (;;) {                                                                    \
		__awrrd_oldobj = __hybrid_atomic_load((self)->awr_obj, __ATOMIC_ACQUIRE); \
		if (!(*(p_ok) = (!__awrrd_oldobj || wasdestroyed(__awrrd_oldobj))))       \
			break;                                                                \
		if (__hybrid_atomic_cmpxch((self)->awr_obj, __awrrd_oldobj, newobj,       \
		                           __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))           \
			break;                                                                \
	}                                                                             \
	__PRIVATE_awref_waitfor(self)                                                 \
	__PRIVATE_AR_INTR_POP()
#define __PRIVATE_awref_replacedead_nopr_5(self, newobj, p_ok, T, wasdestroyed)   \
	__PRIVATE_AR_INTR_PUSHOFF_NOPR();                                             \
	T *__awrrd_oldobj;                                                            \
	for (;;) {                                                                    \
		__awrrd_oldobj = __hybrid_atomic_load((self)->awr_obj, __ATOMIC_ACQUIRE); \
		if (!(*(p_ok) = (!__awrrd_oldobj || wasdestroyed(__awrrd_oldobj))))       \
			break;                                                                \
		if (__hybrid_atomic_cmpxch((self)->awr_obj, __awrrd_oldobj, newobj,       \
		                           __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))           \
			break;                                                                \
	}                                                                             \
	__PRIVATE_awref_waitfor(self)                                                 \
	__PRIVATE_AR_INTR_POP_NOPR()
#define __PRIVATE_awref_replacedead_4(self, newobj, p_ok, T) \
	__PRIVATE_awref_replacedead_5(self, newobj, p_ok, T, wasdestroyed)
#define __PRIVATE_awref_replacedead_nopr_4(self, newobj, p_ok, T) \
	__PRIVATE_awref_replacedead_5(self, newobj, p_ok, T, wasdestroyed)
#ifdef __COMPILER_HAVE_TYPEOF
#define __PRIVATE_awref_replacedead_3(self, newobj, p_ok) \
	__PRIVATE_awref_replacedead_5(self, newobj, p_ok, __typeof__(*(self)->awr_obj), wasdestroyed)
#define __PRIVATE_awref_replacedead_nopr_3(self, newobj, p_ok) \
	__PRIVATE_awref_replacedead_5(self, newobj, p_ok, __typeof__(*(self)->awr_obj), wasdestroyed)
#ifndef __NO_XBLOCK
#define __PRIVATE_awref_replacedead_2(self, newobj)               \
	__XBLOCK({                                                    \
		__BOOL __awrrd_ok;                                        \
		__PRIVATE_awref_replacedead_3(self, newobj, &__awrrd_ok); \
		__XRETURN __awrrd_ok;                                     \
	})
#define __PRIVATE_awref_replacedead_nopr_2(self, newobj)               \
	__XBLOCK({                                                         \
		__BOOL __awrrd_ok;                                             \
		__PRIVATE_awref_replacedead_nopr_3(self, newobj, &__awrrd_ok); \
		__XRETURN __awrrd_ok;                                          \
	})
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> bool awref_replacedead(AWREF(T) *self, T *newobj);
 * >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok);
 * >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok, typename T);
 * >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_replacedead_, (__VA_ARGS__))(__VA_ARGS__)
/* >> bool awref_replacedead_nopr(AWREF(T) *self, T *newobj);
 * >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok);
 * >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok, typename T);
 * >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_replacedead_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead __PRIVATE_awref_replacedead_5
/* >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead_nopr __PRIVATE_awref_replacedead_nopr_5
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#else /* !__NO_XBLOCK */
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok);
 * >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok, typename T);
 * >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_replacedead_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok);
 * >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok, typename T);
 * >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_replacedead_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead __PRIVATE_awref_replacedead_5
/* >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead_nopr __PRIVATE_awref_replacedead_nopr_5
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#endif /* __NO_XBLOCK */
#else /* __COMPILER_HAVE_TYPEOF */
#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok, typename T);
 * >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_replacedead_, (__VA_ARGS__))(__VA_ARGS__)
/* >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok, typename T);
 * >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead_nopr(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_awref_replacedead_nopr_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> void awref_replacedead(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead __PRIVATE_awref_replacedead_5
/* >> void awref_replacedead_nopr(AWREF(T) *self, T *newobj, bool *p_ok, typename T, bool wasdestroyed(T *)); */
#define awref_replacedead_nopr __PRIVATE_awref_replacedead_nopr_5
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#endif /* !__COMPILER_HAVE_TYPEOF */
/************************************************************************/






/************************************************************************/
/* Initialization / finalization                                        */
/************************************************************************/

/* Static initializers */
#ifdef __ARCH_HAVE_AR_NOSMP
#ifdef __INTELLISENSE_GCC__
#define ARREF_INIT(ptr) { .arr_obj = ptr }
#define AXREF_INIT(ptr) { .axr_obj = ptr }
#define AWREF_INIT(ptr) { .awr_obj = ptr }
#else /* __INTELLISENSE_GCC__ */
#define ARREF_INIT(ptr) { ptr }
#define AXREF_INIT(ptr) { ptr }
#define AWREF_INIT(ptr) { ptr }
#endif /* !__INTELLISENSE_GCC__ */
#else /* __ARCH_HAVE_AR_NOSMP */
#ifdef __INTELLISENSE_GCC__
#define ARREF_INIT(ptr) { .arr_obj = ptr, .arr_cnt = 0 }
#define AXREF_INIT(ptr) { .axr_obj = ptr, .axr_cnt = 0 }
#define AWREF_INIT(ptr) { .awr_obj = ptr, .awr_cnt = 0 }
#else /* __INTELLISENSE_GCC__ */
#define ARREF_INIT(ptr) { ptr, 0 }
#define AXREF_INIT(ptr) { ptr, 0 }
#define AWREF_INIT(ptr) { ptr, 0 }
#endif /* !__INTELLISENSE_GCC__ */
#endif /* !__ARCH_HAVE_AR_NOSMP */

/* >> arref_init(ARREF(T) *self, [[nonnull]] REF T *ptr); */
#define arref_init(self, /*inherit(always)*/ ptr) \
	(void)((self)->arr_obj = (ptr) __PRIVATE_arref_init_smp(self))

/* >> arref_cinit(ARREF(T) *self, [[nonnull]] REF T *ptr); */
#define arref_cinit(self, /*inherit(always)*/ ptr) \
	(void)((self)->arr_obj = (ptr) __PRIVATE_arref_cinit_smp(self))

#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> arref_fini(ARREF(T) *self);
 * >> arref_fini(ARREF(T) *self, void decref(T *)); */
#define arref_fini(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_arref_fini_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> arref_fini(ARREF(T) *self, void decref(T *)); */
#define arref_fini __PRIVATE_arref_fini_2
#endif /* !__HYBRID_PP_VA_OVERLOAD */

/* >> axref_init(AXREF(T) *self, [[nullable]] REF T *ptr); */
#define axref_init(self, /*inherit(always)*/ ptr) \
	(void)((self)->axr_obj = (ptr)__PRIVATE_axref_init_smp(self))

/* >> axref_cinit(AXREF(T) *self, [[nullable]] REF T *ptr); */
#define axref_cinit(self, /*inherit(always)*/ ptr) \
	(void)((self)->axr_obj = (ptr) __PRIVATE_axref_cinit_smp(self))

#ifdef __HYBRID_PP_VA_OVERLOAD
/* >> arref_fini(AxREF(T) *self);
 * >> arref_fini(AxREF(T) *self, void decref(T *)); */
#define axref_fini(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_axref_fini_, (__VA_ARGS__))(__VA_ARGS__)
#else /* __HYBRID_PP_VA_OVERLOAD */
/* >> arref_fini(AxREF(T) *self, void decref(T *)); */
#define axref_fini __PRIVATE_axref_fini_2
#endif /* !__HYBRID_PP_VA_OVERLOAD */

/* >> awref_init(AWREF(T) *self, [[nullable]] T *ptr); */
#define awref_init(self, /*inherit(always)*/ ptr) \
	(void)((self)->awr_obj = (ptr) __PRIVATE_awref_init_smp(self))

/* >> awref_cinit(AWREF(T) *self, [[nullable]] T *ptr); */
#define awref_cinit(self, /*inherit(always)*/ ptr) \
	(void)((self)->awr_obj = (ptr) __PRIVATE_awref_cinit_smp(self))

#endif /* __CC__ */

#endif /* !_KOS_ATOMIC_REF_H */
