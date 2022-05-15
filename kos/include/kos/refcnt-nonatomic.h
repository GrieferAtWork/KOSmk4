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
#ifndef _KOS_REFCNT_NONATOMIC_H
#define _KOS_REFCNT_NONATOMIC_H 1

#include <__stdinc.h>
#include <features.h>

#include <kos/refcnt.h>

#if defined(__cplusplus) && defined(__CC__)
#if defined(__INTELLISENSE__) && 0
#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS_X     __DEFINE_REFCNT_FUNCTIONS_X
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS_X __DEFINE_WEAKREFCNT_FUNCTIONS_X
#else /* __INTELLISENSE__ */
#include <__stdcxx.h>

#include <hybrid/__assert.h>

#include <kos/anno.h>

/* [weak]incref() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, function, destroy_, refcnt_t, refcnt_field)           \
	__hybrid_assertf(refcnt_field > 0, #T "::" #function "(%p): Object was already destroyed", __self); \
	++refcnt_field;
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF */

/* [weak]decref() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, function, destroy_, refcnt_t, refcnt_field, destroy_likelyhood) \
	__hybrid_assertf(refcnt_field > 0, #T "::" #function "(%p): Object was already destroyed", __self);           \
	if destroy_likelyhood(!(--refcnt_field > 0))                                                                  \
		destroy_(__self);
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF */

/* [weak]decref_nokill() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, function, destroy_, refcnt_t, refcnt_field)         \
	__hybrid_assertf(refcnt_field > 0, #T "::" #function "(%p): Object was already destroyed", __self);      \
	__hybrid_assertf(refcnt_field > 1, #T "::" #function "(%p): Object should have been destroyed", __self); \
	--refcnt_field;
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL */

/* [weak]destroy() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY
#if defined(NDEBUG) || defined(NDEBUG_REFCNT)
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, function, destroy_, refcnt_t, refcnt_field) \
	destroy_(__self);
#else /* NDEBUG || NDEBUG_REFCNT */
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, function, destroy_, refcnt_t, refcnt_field) \
	refcnt_field = 0; /* Satisfy refcnt assertions within `destroy_()' */                      \
	destroy_(__self);
#endif /* !NDEBUG && !NDEBUG_REFCNT */
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY */

/* try[weak]incref() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, function, destroy_, refcnt_t, refcnt_field) \
	if (!(refcnt_field > 0))                                                                     \
		return false;                                                                            \
	++refcnt_field;                                                                              \
	return true;
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF */


#define __DEFINE_NONATOMIC_REFCNT_TEMPLATE_X(T, destroy_, X, _)                                                                             \
	T operator+(__NAMESPACE_INT_SYM __refcnt_select_tag, T const&);                                                               \
	template<> class __PRIVATE_REFCNT_NAME(refcnt_methods)< T > {                                                                 \
	public:                                                                                                                       \
		typedef __PRIVATE_REFCNT_TYPE_X(T, X, _) __PRIVATE_REFCNT_NAME(refcnt_t);                                                 \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                                                \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {                              \
			return __hybrid_atomic_load(X(_, __self), __ATOMIC_ACQUIRE);                                                          \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                                       \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                      \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                           \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                                    \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, tryincref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                                       \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), /**/)                \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                                      \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, destroy, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                    \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                                \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))        \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                                \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), __likely)     \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), __unlikely) \
		}                                                                                                                         \
	};
#define __DEFINE_NONATOMIC_WEAKREFCNT_TEMPLATE_X(T, destroy_, X, _)                                                                            \
	T operator+(__NAMESPACE_INT_SYM __weakrefcnt_select_tag, T const&);                                                              \
	template<> class __PRIVATE_REFCNT_NAME(weakrefcnt_methods)< T > {                                                                \
	public:                                                                                                                          \
		typedef __PRIVATE_REFCNT_TYPE_X(T, X, _) __PRIVATE_REFCNT_NAME(refcnt_t);                                                    \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                                                   \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {                                 \
			return __hybrid_atomic_load(X(_, __self), __ATOMIC_ACQUIRE);                                                             \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                                          \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                     \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                                       \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, tryweakincref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))               \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                                          \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), /**/)               \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                                         \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, weakdestroy, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                   \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                                   \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))       \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                                   \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), __likely)    \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                                 \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), __unlikely)\
		}                                                                                                                            \
	};
#define __DEFINE_NONATOMIC_REFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _)                                                                      \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                        \
	__PRIVATE_REFCNT_TYPE_X(T, X, _) __REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(T const *__restrict __self) {                         \
		return __hybrid_atomic_load(X(_, __self), __ATOMIC_ACQUIRE);                                                               \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                        \
	bool __REFCNT_NOTHROW(__REFCNT_CC isshared)(T const *__restrict __self) {                                                      \
		return __hybrid_atomic_load(X(_, __self), __ATOMIC_ACQUIRE) > 1;                                                           \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                        \
	bool __REFCNT_NOTHROW(__REFCNT_CC wasdestroyed)(T const *__restrict __self) {                                                  \
		return __hybrid_atomic_load(X(_, __self), __ATOMIC_ACQUIRE) == 0;                                                          \
	}                                                                                                                              \
	template<class __T> __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1))                             \
	__PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(__T *__restrict __self) {       \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	template<class __T> __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK                                                                   \
	__PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xincref))(__T *__self) {                 \
		if (__self) {                                                                                                              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *                                             \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                                            \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xincref))(T *__self) {          \
		if (__self) {                                                                                                              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                                            \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                                         \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, tryincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                    \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                                           \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, destroy, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                        \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                                            \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                    \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                                     \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)         \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                                   \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely)     \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                                     \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))            \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref))(T *__self) {                                                      \
		if (__self) {                                                                                                              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                \
		}                                                                                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref_likely))(T *__self) {                                               \
		if (__self) {                                                                                                              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)     \
		}                                                                                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref_unlikely))(T *__self) {                                             \
		if (__self) {                                                                                                              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely) \
		}                                                                                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref_nokill))(T *__self) {                                               \
		if (__self) {                                                                                                              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))        \
		}                                                                                                                          \
	}
#define __DEFINE_NONATOMIC_WEAKREFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _)                                                                      \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                            \
	__PRIVATE_REFCNT_TYPE_X(T, X, _) __REFCNT_NOTHROW(__REFCNT_CC getweakrefcnt)(T const *__restrict __self) {                         \
		return __hybrid_atomic_load(X(_, __self), __ATOMIC_ACQUIRE);                                                                   \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                            \
	bool __REFCNT_NOTHROW(__REFCNT_CC isweakshared)(T const *__restrict __self) {                                                      \
		return __hybrid_atomic_load(X(_, __self), __ATOMIC_ACQUIRE) > 1;                                                               \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                            \
	bool __REFCNT_NOTHROW(__REFCNT_CC wasweakdestroyed)(T const *__restrict __self) {                                                  \
		return __hybrid_atomic_load(X(_, __self), __ATOMIC_ACQUIRE) == 0;                                                              \
	}                                                                                                                                  \
	template<class __T> __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1))                                 \
	__PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakincref))(__T *__restrict __self) {       \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	template<class __T> __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK                                                                       \
	__PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakincref))(__T *__self) {                 \
		if (__self) {                                                                                                                  \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                              \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *                                                 \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakincref))(T *__restrict __self) {                                            \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakincref))(T *__self) {          \
		if (__self) {                                                                                                                  \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                              \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                                                \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryweakincref))(T *__restrict __self) {                                         \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, tryweakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                    \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdestroy))(T *__restrict __self) {                                           \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, weakdestroy, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                        \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref))(T *__restrict __self) {                                            \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                    \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref_likely))(T *__restrict __self) {                                     \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)         \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref_unlikely))(T *__restrict __self) {                                   \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely)     \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref_nokill))(T *__restrict __self) {                                     \
		__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))            \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref))(T *__self) {                                                      \
		if (__self) {                                                                                                                  \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                \
		}                                                                                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref_likely))(T *__self) {                                               \
		if (__self) {                                                                                                                  \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)     \
		}                                                                                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref_unlikely))(T *__self) {                                             \
		if (__self) {                                                                                                                  \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely) \
		}                                                                                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref_nokill))(T *__self) {                                               \
		if (__self) {                                                                                                                  \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))        \
		}                                                                                                                              \
	}
#endif /* !__INTELLISENSE__ */
#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS_X(T, destroy_, X, _)    \
	extern "C++" {                                                  \
	__DEFINE_NONATOMIC_REFCNT_TEMPLATE_X(T, destroy_, X, _)         \
	__DEFINE_NONATOMIC_REFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _) \
	}
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS_X(T, destroy_, X, _)    \
	extern "C++" {                                                      \
	__DEFINE_NONATOMIC_WEAKREFCNT_TEMPLATE_X(T, destroy_, X, _)         \
	__DEFINE_NONATOMIC_WEAKREFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _) \
	}
#else /* __cplusplus && __CC__ */
#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS_X(T, destroy_, X, _)     /* nothing */
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS_X(T, destroy_, X, _) /* nothing */
#endif /* !__cplusplus || !__CC__ */

#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS(T, field, destroy_) \
	__DEFINE_NONATOMIC_REFCNT_FUNCTIONS_X(T, destroy_, __PRIVATE_REFCNT_Xfld, field)
#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS_P(T, getfield, destroy_) \
	__DEFINE_NONATOMIC_REFCNT_FUNCTIONS_X(T, destroy_, __PRIVATE_REFCNT_Xpth, getfield)
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS(T, field, destroy_) \
	__DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS_X(T, destroy_, __PRIVATE_REFCNT_Xfld, field)
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS_P(T, getfield, destroy_) \
	__DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS_X(T, destroy_, __PRIVATE_REFCNT_Xpth, getfield)

#endif /* !_KOS_REFCNT_NONATOMIC_H */
