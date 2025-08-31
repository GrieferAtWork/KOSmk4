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
%(c_prefix){
/* (#) Portability: GNU C Library (/mach/cthreads.h) */
/* (#) Portability: GNU Hurd      (/usr/include/cthreads.h) */
}

%[define_decl_include("<bits/crt/pthreadtypes.h>": ["__pthread_key_t"])]

%[default:section(".text.crt{|.dos}.compat.hurd.cthreads")]
%[default:nodos]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <machine-sp.h>
)]%[insert:prefix(
#include <spin-lock.h>
)]%[insert:prefix(
#include <libc/malloc.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <hybrid/host.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/crt/pthreadtypes.h>
)]%{

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

}

%[define_replacement(vm_offset_t = __ULONGPTR_TYPE__)]
%[define_replacement(vm_address_t = __ULONGPTR_TYPE__)]
%[define_replacement(any_t = "void *")]

[[decl_include("<hybrid/typecore.h>")]]
[[requires_function(pthread_self)]]
vm_offset_t cthread_init(void) {
	COMPILER_IMPURE();
	return (vm_offset_t)pthread_self();
}

%{

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
	char const          *name;   /* [0..1] Name (for debugging) */
	struct cthread_queue queue;  /* Unused */
#ifdef WAIT_FUNC_DEBUG
	char const          *fname;  /* Debugging? */
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

}

%[define_replacement(mutex_t = "struct mutex *")]
int mutex_try_lock([[inout]] mutex_t m) = __mutex_trylock; /* OSX function */
void mutex_wait_lock([[inout]] mutex_t m) = __mutex_lock;  /* OSX function */
void mutex_unlock([[inout]] mutex_t m) = __mutex_unlock;   /* OSX function */


%{


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

}

%[define_replacement(condition_t = "struct condition *")]

int cond_signal(condition_t self);
void cond_broadcast(condition_t self);
void condition_wait(condition_t self, mutex_t mutex);
void condition_implies(condition_t implicator, condition_t implicatand);
void condition_unimplies(condition_t implicator, condition_t implicatand);


%{


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

}

%[define_replacement(cthread_t = "struct cthread *")]
%[define_replacement(ur_cthread_t = "struct ur_cthread *")]
%[define_type_class(cthread_fn_t = "TP")]

/* This one we emulate not to return the current SP, but something such
 * that `ur_cthread_ptr(cthread_sp())' evaluates to `ur_cthread_self()' */
[[decl_include("<hybrid/typecore.h>")]]
vm_offset_t cthread_sp(void);

%{

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


}

[[decl_prefix(struct cthread;)]]
[[requires_function(pthread_create)]]
[[impl_include("<libc/errno.h>", "<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
cthread_t cthread_fork([[nonnull]] any_t (LIBCCALL *start_routine)(any_t arg), any_t arg) {
	pthread_t result;
	errno_t error;
	error = pthread_create(&result, NULL, start_routine, arg);
	if unlikely(error != 0) {
		__libc_seterrno(error);
		result = (pthread_t)NULL;
	}
	return (cthread_t)result;
}

[[decl_prefix(struct ur_cthread;)]]
ur_cthread_t ur_cthread_self(void);

[[decl_prefix(struct cthread;)]]
void cthread_detach(cthread_t self) = pthread_detach;

[[decl_prefix(struct cthread;)]]
[[requires_function(pthread_getresult_np)]]
[[impl_include("<bits/crt/pthreadtypes.h>")]]
any_t cthread_join(cthread_t self) {
	void *result;
	pthread_getresult_np((pthread_t)self, &result);
	return result;
}

void cthread_yield(void) = sched_yield;

[[noreturn]]
void cthread_exit(any_t result) = pthread_exit;

[[decl_prefix(struct cthread;)]]
[[requires_function(pthread_cancel)]]
[[impl_include("<bits/crt/pthreadtypes.h>")]]
int cthread_abort(cthread_t self) {
	return pthread_cancel((pthread_t)self) == 0 ? 0 : -1;
}


%{
#if 0 /* Is the case thanks to emulation, but is way slower than the library function */
#define cthread_self() (ur_cthread_self()->incarnation)
#endif
}

[[decl_prefix(struct cthread;), nonnull]]
cthread_t cthread_self() = pthread_self;

[[decl_prefix(struct cthread;)]]
void cthread_set_name([[inout]] cthread_t self, char const *_name) = pthread_setname_np;

/* This one returns a pointer into a thread-local storage containing the thread's name.
 * The  contents of this storage are updated every time this function is called, and if
 * an error happens, we return `NULL' instead. */
[[decl_prefix(struct cthread;)]]
char const *cthread_name([[in]] cthread_t self);

@@>> cthread_count(3)
@@Return the number of running threads (s.a. `DLAUXCTRL_GET_TLSSEG_COUNT')
int cthread_count(void);

@@>> cthread_set_limit(3)
@@No-op
void cthread_set_limit(int limit) {
	COMPILER_IMPURE();
	(void)limit;
}

@@>> cthread_limit(3)
@@No-op (always returns `INT_MAX')
[[wunused]]
[[impl_include("<hybrid/limitcore.h>")]]
int cthread_limit(void) {
	COMPILER_IMPURE();
	return INT_MAX;
}

@@>> cthread_set_data(3)
@@Set the value of a TLS variable for `self'
[[decl_prefix(struct cthread;)]]
int cthread_set_data(cthread_t self, [[access(none)]] void *value);

@@>> cthread_data(3)
@@Get the value of a TLS variable for `self'
[[decl_prefix(struct cthread;)]]
void *cthread_data(cthread_t self);

@@>> cthread_set_errno_self(3)
@@Set the value of `errno' to `val'
[[no_crt_impl]] /* Has a custom implementation in `libc/errno.c' */
[[decl_include("<bits/types.h>")]]
[[requires_include("<libc/errno.h>")]]
[[requires(defined(__libc_seterrno))]]
[[impl_include("<libc/errno.h>")]]
void cthread_set_errno_self($errno_t val) {
	(void)__libc_seterrno(val);
}

@@>> cthread_errno(3)
@@Return the value of `errno'
[[no_crt_impl]] /* Has a custom implementation in `libc/errno.c' */
[[wunused, pure]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
$errno_t cthread_errno(void) {
	COMPILER_IMPURE();
	return __libc_geterrno_or(0);
}


%{


/************************************************************************/
/* TLS Variables                                                        */
/************************************************************************/
typedef __pthread_key_t cthread_key_t;
#define CTHREAD_DATA_VALUE_NULL ((void *)__NULLPTR)
#define CTHREAD_KEY_INVALID     ((cthread_key_t)-1)

}

%[define_replacement(cthread_key_t = __pthread_key_t)]

[[decl_include("<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_key_create)]]
[[impl_include("<bits/crt/pthreadtypes.h>")]]
int cthread_keycreate([[out]] cthread_key_t *key) {
	return pthread_key_create((pthread_key_t *)key, NULL) == 0 ? 0 : -1;
}

[[decl_include("<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_getspecific)]]
[[impl_include("<bits/crt/pthreadtypes.h>")]]
int cthread_getspecific(cthread_key_t key, [[out]] void **p_value) {
	*p_value = pthread_getspecific((pthread_key_t)key);
	return 0;
}

[[decl_include("<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_setspecific)]]
[[impl_include("<bits/crt/pthreadtypes.h>", "<bits/types.h>")]]
int cthread_setspecific(cthread_key_t key, [[access(none)]] void *value) {
	errno_t error = pthread_setspecific((pthread_key_t)key, value);
	return error == 0 ? 0 : -1;
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
