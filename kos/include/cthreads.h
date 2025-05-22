/* HASH CRC-32:0xa306ad94 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: GNU C Library (/mach/cthreads.h) */
/* (#) Portability: GNU Hurd      (/usr/include/cthreads.h) */
#ifndef _CTHREADS_H
#define _CTHREADS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <machine-sp.h>
#include <spin-lock.h>
#include <libc/malloc.h>
#include <hybrid/typecore.h>
#include <hybrid/host.h>
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>

#ifndef __USE_GLIBC_BLOAT
#include <stdlib.h>
#include <setjmp.h>
#endif /* !__USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __vm_offset_t_defined
#define __vm_offset_t_defined
typedef __ULONGPTR_TYPE__ vm_offset_t;
#endif /* !__vm_offset_t_defined */

#ifndef __vm_address_t_defined
#define __vm_address_t_defined
typedef __ULONGPTR_TYPE__ vm_address_t;
#endif /* !__vm_address_t_defined */

#ifndef __any_t_defined
#define __any_t_defined
typedef void *any_t;
#endif /* !__any_t_defined */

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif /* !TRUE */

#ifdef __NO_XBLOCK
#define MACRO_BEGIN do {
#define MACRO_END   } __WHILE0
#else /* __NO_XBLOCK */
#define MACRO_BEGIN __extension__({
#define MACRO_END   0; })
#endif /* !__NO_XBLOCK */

#ifdef __CRT_HAVE_cthread_init
__CDECLARE(,vm_offset_t,__NOTHROW_NCX,cthread_init,(void),())
#elif defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self)
#include <libc/local/cthreads/cthread_init.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_init, __FORCELOCAL __ATTR_ARTIFICIAL vm_offset_t __NOTHROW_NCX(__LIBCCALL cthread_init)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_init))(); })
#endif /* ... */

/************************************************************************/
/* Weird queue API (don't use this; use `<sys/queue.h>' instead)        */
/************************************************************************/
typedef struct cthread_queue_item *cthread_queue_item_t;
typedef struct cthread_queue *cthread_queue_t;
struct cthread_queue {
	cthread_queue_item_t head;
	cthread_queue_item_t tail;
};
struct cthread_queue_item {
	cthread_queue_item_t next;
};
#define NO_QUEUE_ITEM     ((cthread_queue_item_t)__NULLPTR)
#define QUEUE_INITIALIZER { NO_QUEUE_ITEM, NO_QUEUE_ITEM }
#define cthread_queue_alloc()    ((cthread_queue_t)__libc_calloc(1, sizeof(struct cthread_queue)))
#define cthread_queue_free(self) __libc_free(self)
#define cthread_queue_init(self) (void)((self)->head = (self)->tail = NO_QUEUE_ITEM)
#define cthread_queue_enq(self, item)                           \
	(void)((item)->next = NO_QUEUE_ITEM,                        \
	       (self)->tail == NO_QUEUE_ITEM                        \
	       ? (self)->head       = (cthread_queue_item_t)(item)  \
	       : (self)->tail->next = (cthread_queue_item_t)(item), \
	       (self)->tail = (cthread_queue_item_t)(item))
#define cthread_queue_preq(self, item)                           \
	(void)((self)->tail == NO_QUEUE_ITEM                         \
	       ? (void)((self)->tail = (cthread_queue_item_t)(item)) \
	       : (void)0,                                            \
	       ((cthread_queue_item_t)(item))->next = (self)->head,  \
	       (self)->head = (cthread_queue_item_t)(item))
#define cthread_queue_head(self, T) ((T)(self)->head)
#define cthread_queue_deq(self, T, lv_result)                                      \
	((((lv_result) = (T)(self)->head) != NO_QUEUE_ITEM &&                          \
	  ((self)->head = (cthread_queue_item_t)((lv_result)->next)) == NO_QUEUE_ITEM) \
	 ? (void)((self)->tail = NO_QUEUE_ITEM)                                        \
	 : (void)0)
#define cthread_queue_map(self, T, cb)                            \
	__XBLOCK({                                                    \
		cthread_queue_item_t _cqm_iter, _cqm_next;                \
		for (_cqm_iter = (cthread_queue_item_t)(self)->head;      \
		     _cqm_iter != NO_QUEUE_ITEM; _cqm_iter = _cqm_next) { \
			_cqm_next = _cqm_iter->next;                          \
			(*(cb))((T)_cqm_iter);                                \
		}                                                         \
	})


/************************************************************************/
/* Mutex                                                                */
/************************************************************************/
#ifndef __mutex_t_defined
#define __mutex_t_defined
typedef struct mutex *mutex_t;
#endif /* !__mutex_t_defined */
#ifndef __mutex_defined
#define __mutex_defined
struct mutex {
	spin_lock_t          held;   /* Underlying lock */
	spin_lock_t          lock;   /* Unused */
	const char          *name;   /* [0..1] Name (for debugging) */
	struct cthread_queue queue;  /* Unused */
#ifdef WAIT_FUNC_DEBUG
	const char          *fname;  /* Debugging? */
#else /* WAIT_FUNC_DEBUG */
	struct cthread      *holder; /* Debugging? */
#endif /* WAIT_FUNC_DEBUG */
};
#endif /* !__mutex_defined */

#ifdef WAIT_DEBUG
#ifdef WAIT_FUNC_DEBUG
#define WAIT_CLEAR_DEBUG(self) (self)->fname = __NULLPTR
#define WAIT_SET_DEBUG(self)   (self)->fname = __builtin_FUNCTION()
#else /* WAIT_FUNC_DEBUG */
#define WAIT_CLEAR_DEBUG(self) (self)->holder = __NULLPTR
#define WAIT_SET_DEBUG(self)   (self)->holder = cthread_self()
#endif /* WAIT_FUNC_DEBUG */
#else  /* WAIT_DEBUG */
#define WAIT_CLEAR_DEBUG(self) (void)0
#define WAIT_SET_DEBUG(self)   (void)0
#endif /* WAIT_DEBUG */

#define MUTEX_INITIALIZER             { SPIN_LOCK_INITIALIZER, SPIN_LOCK_INITIALIZER, __NULLPTR, QUEUE_INITIALIZER, __NULLPTR }
#define MUTEX_NAMED_INITIALIZER(name) { SPIN_LOCK_INITIALIZER, SPIN_LOCK_INITIALIZER, name, QUEUE_INITIALIZER, __NULLPTR }

#define mutex_alloc()    ((mutex_t)__libc_calloc(1, sizeof(struct mutex)))
#define mutex_free(self) __libc_free(self)
#define mutex_init(self)                 \
	(spin_lock_init(&(self)->lock),      \
	 cthread_queue_init(&(self)->queue), \
	 spin_lock_init(&(self)->held),      \
	 WAIT_CLEAR_DEBUG(self))
#define mutex_clear(self)       mutex_init(self)
#define mutex_set_name(self, x) (void)((self)->name = (x))
#define mutex_name(self)        (void)((self)->name != __NULLPTR ? (self)->name : "?")
#define mutex_try_lock(self)    (spin_try_lock(&(self)->held) ? (WAIT_SET_DEBUG(self), 1) : 0)
#define mutex_lock(m)           (void)(spin_try_lock(&(m)->held) || (__mutex_lock_solid(m), 0))
#if 0
/* Done by Hurd??? (I have no idea what this is about..., especially since
 * `WAIT_CLEAR_DEBUG()' happening after the unlock is a race condition...) */
#define mutex_unlock(m)                                \
	(spin_unlock(&(m)->held),                          \
	 cthread_queue_head(&(m)->queue, vm_offset_t) != 0 \
	 ? (void)__mutex_unlock_solid(m)                   \
	 : (void)0,                                        \
	 WAIT_CLEAR_DEBUG(m))
#else
#define mutex_unlock(m) \
	(WAIT_CLEAR_DEBUG(m), spin_unlock(&(m)->held))
#endif

#ifdef __CRT_HAVE___mutex_trylock
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,mutex_try_lock,(mutex_t __m),__mutex_trylock,(__m))
#elif defined(__CRT_HAVE___spin_try_lock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,mutex_try_lock,(mutex_t __m),__spin_try_lock,(__m))
#else /* ... */
#include <libc/local/lock-intern/__spin_try_lock.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL mutex_try_lock)(mutex_t __m) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_try_lock))((unsigned int *)__m); }
#endif /* !... */
#ifdef __CRT_HAVE___mutex_lock
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mutex_wait_lock,(mutex_t __m),__mutex_lock,(__m))
#elif defined(__CRT_HAVE___mutex_lock_solid)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mutex_wait_lock,(mutex_t __m),__mutex_lock_solid,(__m))
#elif defined(__CRT_HAVE_mutex_wait_lock)
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mutex_wait_lock,(mutex_t __m),(__m))
#elif defined(__CRT_HAVE___spin_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mutex_wait_lock,(mutex_t __m),__spin_lock,(__m))
#elif defined(__CRT_HAVE___spin_lock_solid)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mutex_wait_lock,(mutex_t __m),__spin_lock_solid,(__m))
#else /* ... */
#include <kos/bits/shared-lock.h>
#if defined(__CRT_HAVE_shared_lock_acquire) || defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#include <libc/local/lock-intern/__spin_lock_solid.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL mutex_wait_lock)(mutex_t __m) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_lock_solid))((unsigned int *)__m); }
#endif /* __CRT_HAVE_shared_lock_acquire || __KERNEL__ || __shared_lock_wait_impl */
#endif /* !... */
#ifdef __CRT_HAVE___mutex_unlock
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mutex_unlock,(mutex_t __m),__mutex_unlock,(__m))
#elif defined(__CRT_HAVE_mutex_unlock)
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mutex_unlock,(mutex_t __m),(__m))
#elif defined(__CRT_HAVE___spin_unlock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,mutex_unlock,(mutex_t __m),__spin_unlock,(__m))
#else /* ... */
#include <kos/bits/shared-lock.h>
#if defined(__CRT_HAVE_shared_lock_release_ex) || defined(__shared_lock_release_ex) || (defined(__shared_lock_sendone) && defined(__shared_lock_sendall))
#include <libc/local/lock-intern/__spin_unlock.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL mutex_unlock)(mutex_t __m) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_unlock))((unsigned int *)__m); }
#endif /* __CRT_HAVE_shared_lock_release_ex || __shared_lock_release_ex || (__shared_lock_sendone && __shared_lock_sendall) */
#endif /* !... */


/************************************************************************/
/* Condition variables                                                  */
/************************************************************************/
typedef struct condition *condition_t;
struct condition {
	spin_lock_t          lock;         /* Underlying lock */
	struct cthread_queue queue;        /* Unused */
	char const          *name;         /* [0..1] Name (for debugging) */
	struct cond_imp     *implications; /* Hurd-specific weirdness */
};
struct cond_imp {
	struct condition *implicatand; /* ??? */
	struct cond_imp  *next;        /* ??? */
};

#define CONDITION_INITIALIZER             { SPIN_LOCK_INITIALIZER, QUEUE_INITIALIZER, __NULLPTR, __NULLPTR }
#define CONDITION_NAMED_INITIALIZER(name) { SPIN_LOCK_INITIALIZER, QUEUE_INITIALIZER, name, __NULLPTR }
#define condition_alloc() ((condition_t)calloc(1, sizeof(struct condition)))
#define condition_init(self)                   \
	(void)(spin_lock_init(&(self)->lock),      \
	       cthread_queue_init(&(self)->queue), \
	       (self)->name         = __NULLPTR,   \
	       (self)->implications = __NULLPTR)
#define condition_free(self)           (condition_clear(self), __libc_free(self))
#define condition_clear(self)          (condition_broadcast(self), spin_lock(&(self)->lock))
#define condition_set_name(self, name) (void)((self)->name = (name))
#define condition_name(self)           ((self)->name != __NULLPTR ? (self)->name : "?")
#define condition_signal(self) \
	(((self)->queue.head || (self)->implications) ? (void)cond_signal(self) : (void)0)
#define condition_broadcast(self) \
	(((self)->queue.head || (self)->implications) ? cond_broadcast(self) : (void)0)

__CDECLARE_OPT(,int,__NOTHROW_NCX,cond_signal,(condition_t __self),(__self))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,cond_broadcast,(condition_t __self),(__self))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,condition_wait,(condition_t __self, mutex_t __mutex),(__self,__mutex))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,condition_implies,(condition_t __implicator, condition_t __implicatand),(__implicator,__implicatand))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,condition_unimplies,(condition_t __implicator, condition_t __implicatand),(__implicator,__implicatand))


/************************************************************************/
/* CThread                                                              */
/************************************************************************/

#ifndef __cthread_fn_t_defined
#define __cthread_fn_t_defined
typedef any_t (__LIBKCALL *cthread_fn_t)(any_t arg);
#endif /* !__cthread_fn_t_defined */
typedef struct cthread *cthread_t;
#define NO_CTHREAD ((cthread_t)__NULLPTR)

typedef struct ur_cthread *ur_cthread_t;
struct ur_cthread {
	ur_cthread_t next;        /* [0..1] Next pointer? (on KOS, always set to NULL) */
	cthread_t    incarnation; /* [1..1] The thread-self pointer (on KOS, this structure is emulated TLS memory) */
};

__CDECLARE_OPT(,vm_offset_t,__NOTHROW_NCX,cthread_sp,(void),())

#ifndef cthread_stack_mask
#ifdef __CRT_HAVE_cthread_stack_mask
__CSDECLARE(,vm_offset_t,cthread_stack_mask);
#define cthread_stack_mask cthread_stack_mask
#endif /* __CRT_HAVE_cthread_stack_mask */
#endif /* !cthread_stack_mask */

#ifdef cthread_stack_mask
#ifdef __ARCH_STACK_GROWS_UPWARDS
#define ur_cthread_ptr(sp) (*(ur_cthread_t *)((sp) & cthread_stack_mask))
#else /* __ARCH_STACK_GROWS_UPWARDS */
#define ur_cthread_ptr(sp) (*(ur_cthread_t *)(((sp) | cthread_stack_mask) + 1 - sizeof(ur_cthread_t *)))
#endif /* !__ARCH_STACK_GROWS_UPWARDS */
#if 0
#define ur_cthread_self() ur_cthread_ptr(cthread_sp())
#endif
#endif /* cthread_stack_mask */


#ifdef __CRT_HAVE_cthread_fork
__CDECLARE(__ATTR_NONNULL((1)),cthread_t,__NOTHROW_NCX,cthread_fork,(any_t (__LIBCCALL *__start_routine)(any_t __arg), any_t __arg),(__start_routine,__arg))
#elif defined(__CRT_HAVE_pthread_create)
#include <libc/local/cthreads/cthread_fork.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_fork, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) cthread_t __NOTHROW_NCX(__LIBCCALL cthread_fork)(any_t (__LIBCCALL *__start_routine)(any_t __arg), any_t __arg) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_fork))(__start_routine, __arg); })
#endif /* ... */
__CDECLARE_OPT(,ur_cthread_t,__NOTHROW_NCX,ur_cthread_self,(void),())
#ifdef __CRT_HAVE_pthread_detach
/* >> pthread_detach(3)
 * Indicate that the thread `self' is  never to be joined with  `pthread_join(3)'.
 * The resources of `self' will therefore be freed immediately when it terminates,
 * instead of waiting for another thread to perform `pthread_join(3)' on it
 * @return: EOK: Success */
__CREDIRECT_VOID(,__NOTHROW_NCX,cthread_detach,(cthread_t __self),pthread_detach,(__self))
#elif defined(__CRT_HAVE_cthread_detach)
/* >> pthread_detach(3)
 * Indicate that the thread `self' is  never to be joined with  `pthread_join(3)'.
 * The resources of `self' will therefore be freed immediately when it terminates,
 * instead of waiting for another thread to perform `pthread_join(3)' on it
 * @return: EOK: Success */
__CDECLARE_VOID(,__NOTHROW_NCX,cthread_detach,(cthread_t __self),(__self))
#endif /* ... */
#ifdef __CRT_HAVE_cthread_join
__CDECLARE(,any_t,__NOTHROW_NCX,cthread_join,(cthread_t __self),(__self))
#elif defined(__CRT_HAVE_pthread_getresult_np)
#include <libc/local/cthreads/cthread_join.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_join, __FORCELOCAL __ATTR_ARTIFICIAL any_t __NOTHROW_NCX(__LIBCCALL cthread_join)(cthread_t __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_join))(__self); })
#endif /* ... */
#ifdef __CRT_HAVE_sched_yield
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,cthread_yield,(void),sched_yield,())
#elif defined(__CRT_HAVE_thrd_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,cthread_yield,(void),thrd_yield,())
#elif defined(__CRT_HAVE_pthread_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,cthread_yield,(void),pthread_yield,())
#elif defined(__CRT_HAVE___sched_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,cthread_yield,(void),__sched_yield,())
#elif defined(__CRT_HAVE___libc_sched_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,cthread_yield,(void),__libc_sched_yield,())
#elif defined(__CRT_HAVE_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,cthread_yield,(void),yield,())
#elif defined(__CRT_HAVE_thr_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,cthread_yield,(void),thr_yield,())
#elif defined(__CRT_HAVE_cthread_yield)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CDECLARE_VOID(,__NOTHROW_NCX,cthread_yield,(void),())
#elif defined(__CRT_HAVE_pthread_yield_np)
/* >> sched_yield(2)
 * @return: 1: Another thread was  executed prior to  the function  returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
__CREDIRECT_VOID(,__NOTHROW_NCX,cthread_yield,(void),pthread_yield_np,())
#endif /* ... */
#ifdef __CRT_HAVE_pthread_exit
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CREDIRECT_VOID(__ATTR_NORETURN,__NOTHROW_NCX,cthread_exit,(any_t __result),pthread_exit,(__result))
#elif defined(__CRT_HAVE_thr_exit)
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CREDIRECT_VOID(__ATTR_NORETURN,__NOTHROW_NCX,cthread_exit,(any_t __result),thr_exit,(__result))
#elif defined(__CRT_HAVE_cthread_exit)
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,cthread_exit,(any_t __result),(__result))
#endif /* ... */
#ifdef __CRT_HAVE_cthread_abort
__CDECLARE(,int,__NOTHROW_NCX,cthread_abort,(cthread_t __self),(__self))
#elif defined(__CRT_HAVE_pthread_cancel)
#include <libc/local/cthreads/cthread_abort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_abort, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL cthread_abort)(cthread_t __self) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_abort))(__self); })
#endif /* ... */
#if 0 /* Is the case thanks to emulation, but is way slower than the library function */
#define cthread_self() (ur_cthread_self()->incarnation)
#endif
#ifdef __CRT_HAVE_pthread_self
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_RETNONNULL,cthread_t,__NOTHROW_NCX,cthread_self,(void),pthread_self,())
#elif defined(__CRT_HAVE_thrd_current)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_RETNONNULL,cthread_t,__NOTHROW_NCX,cthread_self,(void),thrd_current,())
#elif defined(__CRT_HAVE_thr_self)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CREDIRECT(__ATTR_RETNONNULL,cthread_t,__NOTHROW_NCX,cthread_self,(void),thr_self,())
#elif defined(__CRT_HAVE_cthread_self)
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
__CDECLARE(__ATTR_RETNONNULL,cthread_t,__NOTHROW_NCX,cthread_self,(void),())
#endif /* ... */
#ifdef __CRT_HAVE_pthread_setname_np
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,cthread_set_name,(cthread_t __self, char const *___name),pthread_setname_np,(__self,___name))
#elif defined(__CRT_HAVE_pthread_set_name_np)
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,cthread_set_name,(cthread_t __self, char const *___name),pthread_set_name_np,(__self,___name))
#elif defined(__CRT_HAVE_cthread_set_name)
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,cthread_set_name,(cthread_t __self, char const *___name),(__self,___name))
#endif /* ... */
__CDECLARE_OPT(__ATTR_IN(1),char const *,__NOTHROW_NCX,cthread_name,(cthread_t __self),(__self))
/* >> cthread_count(3)
 * Return the number of running threads (s.a. `DLAUXCTRL_GET_MAIN_TLSSEG') */
__CDECLARE_OPT(,int,__NOTHROW_NCX,cthread_count,(void),())
#ifdef __CRT_HAVE_cthread_set_limit
/* >> cthread_set_limit(3)
 * No-op */
__CDECLARE_VOID(,__NOTHROW_NCX,cthread_set_limit,(int __limit),(__limit))
#else /* __CRT_HAVE_cthread_set_limit */
#include <libc/local/cthreads/cthread_set_limit.h>
/* >> cthread_set_limit(3)
 * No-op */
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_set_limit, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL cthread_set_limit)(int __limit) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_set_limit))(__limit); })
#endif /* !__CRT_HAVE_cthread_set_limit */
#ifdef __CRT_HAVE_cthread_limit
/* >> cthread_limit(3)
 * No-op (always returns `INT_MAX') */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,cthread_limit,(void),())
#else /* __CRT_HAVE_cthread_limit */
#include <libc/local/cthreads/cthread_limit.h>
/* >> cthread_limit(3)
 * No-op (always returns `INT_MAX') */
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_limit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL cthread_limit)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_limit))(); })
#endif /* !__CRT_HAVE_cthread_limit */
/* >> cthread_set_data(3)
 * Set the value of a TLS variable for `self' */
__CDECLARE_OPT(__ATTR_ACCESS_NONE(2),int,__NOTHROW_NCX,cthread_set_data,(cthread_t __self, void *___value),(__self,___value))
/* >> cthread_data(3)
 * Get the value of a TLS variable for `self' */
__CDECLARE_OPT(,void *,__NOTHROW_NCX,cthread_data,(cthread_t __self),(__self))
#ifdef __CRT_HAVE_cthread_set_errno_self
/* >> cthread_set_errno_self(3)
 * Set the value of `errno' to `val' */
__CDECLARE_VOID(,__NOTHROW_NCX,cthread_set_errno_self,(__errno_t __val),(__val))
#else /* __CRT_HAVE_cthread_set_errno_self */
#include <libc/errno.h>
#ifdef __libc_seterrno
#include <libc/local/cthreads/cthread_set_errno_self.h>
/* >> cthread_set_errno_self(3)
 * Set the value of `errno' to `val' */
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_set_errno_self, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL cthread_set_errno_self)(__errno_t __val) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_set_errno_self))(__val); })
#endif /* __libc_seterrno */
#endif /* !__CRT_HAVE_cthread_set_errno_self */
#ifdef __CRT_HAVE_cthread_errno
/* >> cthread_errno(3)
 * Return the value of `errno' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__errno_t,__NOTHROW_NCX,cthread_errno,(void),())
#else /* __CRT_HAVE_cthread_errno */
#include <libc/local/cthreads/cthread_errno.h>
/* >> cthread_errno(3)
 * Return the value of `errno' */
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_errno, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __errno_t __NOTHROW_NCX(__LIBCCALL cthread_errno)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_errno))(); })
#endif /* !__CRT_HAVE_cthread_errno */


/************************************************************************/
/* TLS Variables                                                        */
/************************************************************************/
typedef __pthread_key_t cthread_key_t;
#define CTHREAD_DATA_VALUE_NULL ((void *)__NULLPTR)
#define CTHREAD_KEY_INVALID     ((cthread_key_t)-1)

#ifdef __CRT_HAVE_cthread_keycreate
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,cthread_keycreate,(cthread_key_t *__key),(__key))
#elif defined(__CRT_HAVE_pthread_key_create) || defined(__CRT_HAVE_thr_keycreate) || defined(__CRT_HAVE___pthread_key_create)
#include <libc/local/cthreads/cthread_keycreate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_keycreate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL cthread_keycreate)(cthread_key_t *__key) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_keycreate))(__key); })
#endif /* ... */
#ifdef __CRT_HAVE_cthread_getspecific
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_NCX,cthread_getspecific,(cthread_key_t __key, void **__p_value),(__key,__p_value))
#elif defined(__CRT_HAVE_pthread_getspecific) || defined(__CRT_HAVE_tss_get) || defined(__CRT_HAVE___pthread_getspecific) || defined(__CRT_HAVE_pthread_getspecificptr_np)
#include <libc/local/cthreads/cthread_getspecific.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_getspecific, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL cthread_getspecific)(cthread_key_t __key, void **__p_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_getspecific))(__key, __p_value); })
#endif /* ... */
#ifdef __CRT_HAVE_cthread_setspecific
__CDECLARE(__ATTR_ACCESS_NONE(2),int,__NOTHROW_NCX,cthread_setspecific,(cthread_key_t __key, void *___value),(__key,___value))
#elif defined(__CRT_HAVE_pthread_setspecific) || defined(__CRT_HAVE_thr_setspecific) || defined(__CRT_HAVE___pthread_setspecific)
#include <libc/local/cthreads/cthread_setspecific.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cthread_setspecific, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_NONE(2) int __NOTHROW_NCX(__LIBCCALL cthread_setspecific)(cthread_key_t __key, void *___value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cthread_setspecific))(__key, ___value); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CTHREADS_H */
