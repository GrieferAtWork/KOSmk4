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
#ifndef _KOS_REFCNT_NONATOMIC_H
#define _KOS_REFCNT_NONATOMIC_H 1

#include <__stdinc.h>
#include <features.h>
#include <kos/refcnt.h>

#if defined(__cplusplus) && defined(__CC__)
#include <__stdcxx.h>
#include <hybrid/__assert.h>

#include <kos/anno.h>

#if (defined(__USE_KOS) || defined(__USE_KOS_KERNEL) || \
     (defined(__KOS__) && defined(__KERNEL__)))
#ifdef __INTELLISENSE__
#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS        __DEFINE_REFCNT_FUNCTIONS
#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS_EX     __DEFINE_REFCNT_FUNCTIONS_EX
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS    __DEFINE_WEAKREFCNT_FUNCTIONS
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS_EX __DEFINE_WEAKREFCNT_FUNCTIONS_EX
#endif /* __INTELLISENSE__ */
#endif /* __USE_KOS || __USE_KOS_KERNEL || (__KOS__ && __KERNEL__) */

#ifndef __DEFINE_NONATOMIC_REFCNT_FUNCTIONS
/* [weak]incref() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, function, destroy_, refcnt_field)                     \
	__hybrid_assertf(refcnt_field > 0, #T "::" #function "(%p): Object was already destroyed", __self); \
	++refcnt_field;
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF */

/* [weak]decref() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, function, destroy_, refcnt_field, destroy_likelyhood) \
	__hybrid_assertf(refcnt_field > 0, #T "::" #function "(%p): Object was already destroyed", __self); \
	if destroy_likelyhood(!(--refcnt_field > 0))                                                        \
		destroy_(__self);
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF */

/* [weak]decref_nokill() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, function, destroy_, refcnt_field)                   \
	__hybrid_assertf(refcnt_field > 0, #T "::" #function "(%p): Object was already destroyed", __self);      \
	__hybrid_assertf(refcnt_field > 1, #T "::" #function "(%p): Object should have been destroyed", __self); \
	--refcnt_field;
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL */

/* [weak]destroy() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY
#ifdef NDEBUG
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, function, destroy_, refcnt_field) \
	destroy_(__self);
#else /* NDEBUG */
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, function, destroy_, refcnt_field) \
	refcnt_field = 0; /* Satisfy refcnt assertions within `destroy_()' */            \
	destroy_(__self);
#endif /* !NDEBUG */
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY */

/* try[weak]incref() */
#ifndef __PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF
#define __PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, function, destroy_, refcnt_field) \
	if (!(refcnt_field > 0))                                                           \
		return false;                                                                  \
	++refcnt_field;                                                                    \
	return true;
#endif /* !__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF */


#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS(T, field, destroy_)                                             \
	extern "C++" {                                                                                          \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                         \
	template<> class __PRIVATE_REFCNT_NAME(refcnt_methods)< T > {                                           \
	public:                                                                                                 \
		typedef __PRIVATE_REFCNT_TYPE(T, field) __PRIVATE_REFCNT_NAME(refcnt_t);                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                          \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                           \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {        \
			return __self->field;                                                                           \
		}                                                                                                   \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                       \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                 \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, incref, destroy_, __self->field)                      \
		}                                                                                                   \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                     \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, tryincref, destroy_, __self->field)                \
		}                                                                                                   \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                       \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                 \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref, destroy_, __self->field, /**/)                \
		}                                                                                                   \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                       \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, destroy, destroy_, __self->field)                    \
		}                                                                                                   \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                       \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {          \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __self->field)        \
		}                                                                                                   \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                       \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {          \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __self->field, __likely)     \
		}                                                                                                   \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                       \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {        \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __self->field, __unlikely) \
		}                                                                                                   \
	};                                                                                                      \
	}
#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS_EX(T, getfield, destroy_)                                          \
	extern "C++" {                                                                                             \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                            \
	template<> class __PRIVATE_REFCNT_NAME(refcnt_methods)< T > {                                              \
	public:                                                                                                    \
		typedef __PRIVATE_REFCNT_TYPE_EX(T, getfield) __PRIVATE_REFCNT_NAME(refcnt_t);                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                             \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {           \
			return getfield(__self);                                                                           \
		}                                                                                                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                          \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                    \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, incref, destroy_, getfield(__self))                      \
		}                                                                                                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                        \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                 \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, tryincref, destroy_, getfield(__self))                \
		}                                                                                                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                          \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                    \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref, destroy_, getfield(__self), /**/)                \
		}                                                                                                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                          \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                   \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, destroy, destroy_, getfield(__self))                    \
		}                                                                                                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                          \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {             \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, getfield(__self))        \
		}                                                                                                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                          \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {             \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, getfield(__self), __likely)     \
		}                                                                                                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                          \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {           \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, getfield(__self), __unlikely) \
		}                                                                                                      \
	};                                                                                                         \
	}
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS(T, field, destroy_)                                             \
	extern "C++" {                                                                                              \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                                         \
	template<> class weakrefcnt_methods< T > {                                                                  \
	public:                                                                                                     \
		typedef __PRIVATE_REFCNT_TYPE(T, field) __PRIVATE_REFCNT_NAME(refcnt_t);                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                              \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                               \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {            \
			return __self->field;                                                                               \
		}                                                                                                       \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                           \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                     \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __self->field)                      \
		}                                                                                                       \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                         \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                  \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, tryweakincref, destroy_, __self->field)                \
		}                                                                                                       \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                           \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                     \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __self->field, /**/)                \
		}                                                                                                       \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                           \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                    \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, weakdestroy, destroy_, __self->field)                    \
		}                                                                                                       \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                           \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __self->field)        \
		}                                                                                                       \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                           \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {              \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __self->field, __likely)     \
		}                                                                                                       \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                           \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {            \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __self->field, __unlikely) \
		}                                                                                                       \
	};                                                                                                          \
	}
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS_EX(T, getfield, destroy_)                                          \
	extern "C++" {                                                                                                 \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                                            \
	template<> class weakrefcnt_methods< T > {                                                                     \
	public:                                                                                                        \
		typedef __PRIVATE_REFCNT_TYPE_EX(T, getfield) __PRIVATE_REFCNT_NAME(refcnt_t);                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                                 \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                                  \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {               \
			return getfield(__self);                                                                               \
		}                                                                                                          \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                        \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_INCREF(T, weakincref, destroy_, getfield(__self))                      \
		}                                                                                                          \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                            \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                     \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_TRYINCREF(T, tryweakincref, destroy_, getfield(__self))                \
		}                                                                                                          \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                        \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, getfield(__self), /**/)                \
		}                                                                                                          \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                       \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DESTROY(T, weakdestroy, destroy_, getfield(__self))                    \
		}                                                                                                          \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                 \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, getfield(__self))        \
		}                                                                                                          \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                 \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, getfield(__self), __likely)     \
		}                                                                                                          \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {               \
			__PRIVATE_NONATOMIC_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, getfield(__self), __unlikely) \
		}                                                                                                          \
	};                                                                                                             \
	}
#endif /* !__DEFINE_NONATOMIC_REFCNT_FUNCTIONS */

#else /* __cplusplus && __CC__ */

#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS(T, field, destroy_)           /* nothing */
#define __DEFINE_NONATOMIC_REFCNT_FUNCTIONS_EX(T, getfield, destroy_)     /* nothing */
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS(T, field, destroy_)       /* nothing */
#define __DEFINE_NONATOMIC_WEAKREFCNT_FUNCTIONS_EX(T, getfield, destroy_) /* nothing */

#endif /* !__cplusplus || !__CC__ */


#endif /* !_KOS_REFCNT_NONATOMIC_H */
