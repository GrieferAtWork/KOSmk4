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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_CALLBACKS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_CALLBACKS_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/host.h>

#include <kos/aref.h>

DECL_BEGIN

#ifdef __CC__

/* API for defining/managing  atomic callback lists  of hooks  to-be
 * invoked during some abstract event, such that driver can register
 * callbacks from constructors/destructors. */

struct driver;

#ifndef __drv_self_defined
#define __drv_self_defined
DATDEF struct driver drv_self
#ifdef BUILDING_KERNEL_CORE
	ASMNAME("kernel_driver")
#endif /* BUILDING_KERNEL_CORE */
;
#endif /* !__drv_self_defined */


/* Driver-enabled callback lists */
struct callback_node_struct {
	void             (*cn_func)();  /* [1..1][const] The callback function that should be invoked. */
	REF struct driver *cn_orig;     /* [1..1][const] A reference to the driver from which the callback originates. */
};
struct callback_list_struct {
	WEAK refcnt_t                                       cl_refcnt; /* Reference counter. */
	size_t                                              cl_count;  /* [const] Number of registered callbacks. */
	COMPILER_FLEXIBLE_ARRAY(struct callback_node_struct,cl_list);  /* [cl_count] List of registered callbacks */
};
FUNDEF NOBLOCK void NOTHROW(KCALL callback_list_detroy)(struct callback_list_struct *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct callback_list_struct, cl_refcnt, callback_list_detroy);

typedef ARREF(__callback_list, callback_list_struct) __callback_list_t;
FUNDEF __BOOL KCALL __callback_list_insert(__callback_list_t *__restrict self, void (*func)(), struct driver *__restrict orig) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("callback_list_insert");
FUNDEF __BOOL KCALL __callback_list_remove(__callback_list_t *__restrict self, void (*func)()) THROWS(E_BADALLOC, E_WOULDBLOCK) ASMNAME("callback_list_remove");
DATDEF struct callback_list_struct __callback_list_empty ASMNAME("callback_list_empty");

#if defined(__cplusplus) && defined(__COMPILER_HAVE_CXX_VARIABLE_TEMPLATES)
#define CALLBACK_LIST(PROTOTYPE)        callback_list< PROTOTYPE >
#define CALLBACK_LIST_INIT              { ARREF_INIT(&__callback_list_empty) }
#define callback_list_insert(self, ...) ((self)->insert(__VA_ARGS__))
#define callback_list_remove(self, ...) ((self)->remove(__VA_ARGS__))

extern "C++" {
template<class CallbackPrototype> struct callback_list;
template<class ReturnType, class ...ArgumenTypes>
struct callback_list<ReturnType KCALL(ArgumenTypes...)> {
	__callback_list_t __m_list;
	typedef ReturnType (KCALL *__function_pointer)(ArgumenTypes...);

	/* NOTE: invocation is NOBLOCK/NOEXCEPT only if callbacks themself are, too. */
	__CXX_CLASSMEMBER void KCALL operator()(ArgumenTypes... args) {
		size_t i;
		REF struct callback_list_struct *state;
		state = arref_get(&this->__m_list);
		FINALLY_DECREF_UNLIKELY(state);
		for (i = 0; i < state->cl_count; ++i) {
			(*(__function_pointer)state->cl_list[i].cn_func)(args...);
		}
	}

	__CXX_CLASSMEMBER bool KCALL insert(__function_pointer func,
	                                    struct driver *__restrict orig DFL(&drv_self))
			THROWS(E_BADALLOC, E_WOULDBLOCK) {
		return __callback_list_insert(&this->__m_list, (void (*)())func, orig);
	}
	__CXX_CLASSMEMBER bool KCALL remove(__function_pointer func) THROWS(E_BADALLOC, E_WOULDBLOCK) {
		return __callback_list_remove(&this->__m_list, (void (*)())func);
	}
};

#if !defined(__x86_64__) && defined(__i386__) && !defined(__clang_tidy__)
template<class ReturnType, class ...ArgumenTypes>
struct callback_list<ReturnType FCALL(ArgumenTypes...)> {
	__callback_list_t __m_list;
	typedef ReturnType (FCALL *__function_pointer)(ArgumenTypes...);

	/* NOTE: invocation is NOBLOCK/NOEXCEPT only if callbacks themself are, too. */
	__CXX_CLASSMEMBER void FCALL operator()(ArgumenTypes... args) {
		size_t i;
		REF struct callback_list_struct *state;
		state = arref_get(&this->__m_list);
		FINALLY_DECREF_UNLIKELY(state);
		for (i = 0; i < state->cl_count; ++i) {
			(*(__function_pointer)state->cl_list[i].cn_func)(args...);
		}
	}

	__CXX_CLASSMEMBER bool KCALL insert(__function_pointer func,
	                                    struct driver *__restrict orig DFL(&drv_self))
			THROWS(E_BADALLOC, E_WOULDBLOCK) {
		return __callback_list_insert(&this->__m_list, (void (*)())func, orig);
	}
	__CXX_CLASSMEMBER bool KCALL remove(__function_pointer func) THROWS(E_BADALLOC, E_WOULDBLOCK) {
		return __callback_list_remove(&this->__m_list, (void (*)())func);
	}
};
#endif /* !__x86_64__ && __i386__ */

}
#else /* __cplusplus */
#define CALLBACK_LIST(PROTOTYPE)                           __callback_list_t
#define CALLBACK_LIST_INIT                                 ARREF_INIT(&__callback_list_empty)
#define __PRIVATE_callback_list_insert_2(self, func)       __callback_list_insert(self, (void (*)())(func), &drv_self)
#define __PRIVATE_callback_list_insert_3(self, func, orig) __callback_list_insert(self, (void (*)())(func), orig)
#define __PRIVATE_callback_list_remove_2(self, func)       __callback_list_remove(self, (void (*)())(func), &drv_self)
#define __PRIVATE_callback_list_remove_3(self, func, orig) __callback_list_remove(self, (void (*)())(func))
#define callback_list_insert(...)                          __HYBRID_PP_VA_OVERLOAD(__PRIVATE_callback_list_insert_, __VA_ARGS__)(__VA_ARGS__)
#define callback_list_remove(...)                          __HYBRID_PP_VA_OVERLOAD(__PRIVATE_callback_list_remove_, __VA_ARGS__)(__VA_ARGS__)
#endif /* !__cplusplus */


/* Helper macros for hooking driver-callbacks to-be invoked for certain events. */
#ifndef BUILDING_KERNEL_CORE
#ifndef DRIVER_INIT
#define DRIVER_INIT     __attribute__((__constructor__))
#define DRIVER_FINI     __attribute__((__destructor__))
#endif /* !DRIVER_INIT */
#define __REGISTER_CALLBACK_UNIQUE2(x, y) x##y
#define __REGISTER_CALLBACK_UNIQUE(x, y) __REGISTER_CALLBACK_UNIQUE2(x, y)
#define REGISTER_CALLBACK_EX(id, list, func)             \
	PRIVATE DRIVER_INIT void                             \
	__REGISTER_CALLBACK_UNIQUE(id##_i, __LINE__)(void) { \
		callback_list_insert(&(list), &(func));          \
	}                                                    \
	PRIVATE DRIVER_FINI void                             \
	__REGISTER_CALLBACK_UNIQUE(id##_f, __LINE__)(void) { \
		callback_list_remove(&(list), &(func));          \
	}
#define REGISTER_CALLBACK(list, func) REGISTER_CALLBACK_EX(_driver_cb_, list, func)
#endif /* !BUILDING_KERNEL_CORE */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_CALLBACKS_H */
