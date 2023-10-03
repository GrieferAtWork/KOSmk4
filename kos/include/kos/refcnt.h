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
#ifndef _KOS_REFCNT_H
#define _KOS_REFCNT_H 1

#include <__stdinc.h>

#if defined(__cplusplus) && defined(__CC__)
#include <__stdcxx.h>
#include <features.h>

#include <hybrid/__atomic.h>

#include <kos/anno.h>

#if defined(__COMPILER_HAVE_TYPEOF) && 0
#define __PRIVATE_REFCNT_TYPE_X(T, X, _)     __typeof__(X(_, (T *)0))
#elif defined(__COMPILER_HAVE_CXX_DECLTYPE)
#define __PRIVATE_REFCNT_TYPE_X(T, X, _)     decltype(X(_, (T *)0))
#else /* __COMPILER_HAVE_CXX_DECLTYPE */
#include <hybrid/typecore.h>
#define __PRIVATE_REFCNT_TYPE_X(T, X, _)     __UINTPTR_TYPE__
#endif /* !__COMPILER_HAVE_CXX_DECLTYPE */
#define __PRIVATE_REFCNT_Xfld(field, x)      (x)->field
#define __PRIVATE_REFCNT_Xpth(getfield, x)   getfield(x)
#define __PRIVATE_REFCNT_TYPE(T, field)      __PRIVATE_REFCNT_TYPE_X(T, __PRIVATE_REFCNT_Xfld, field)
#define __PRIVATE_REFCNT_TYPE_P(T, getfield) __PRIVATE_REFCNT_TYPE_X(T, __PRIVATE_REFCNT_Xpth, getfield)

#if defined(__KOS__) && defined(__KERNEL__)
#ifndef __REFCNT_CC
#include <__crt.h> /* __KCALL */
#define __REFCNT_CC __KCALL
#endif /* !__REFCNT_CC */
#ifndef __REFCNT_NOTHROW
#define __REFCNT_NOTHROW __NOTHROW
#endif /* !__REFCNT_NOTHROW */
#else /* __KOS__ && __KERNEL__ */
#ifndef __REFCNT_CC
#define __REFCNT_CC /* nothing */
#endif /* !__REFCNT_CC */
#ifndef __REFCNT_NOTHROW
#define __REFCNT_NOTHROW __NOTHROW_NCX
#endif /* !__REFCNT_NOTHROW */
#endif /* !__KOS__ || !__KERNEL__ */

#ifndef __REFCNT_DESTROY_NOTHROW
#define __REFCNT_DESTROY_NOTHROW __REFCNT_NOTHROW
#endif /* !__REFCNT_DESTROY_NOTHROW */

#if (defined(__USE_KOS) || defined(__USE_KOS_KERNEL) || \
     (defined(__KOS__) && defined(__KERNEL__)))
#define __PRIVATE_REFCNT_NAME(x)                            x
#define REFCNT_METHODS(T)                  ::refcnt_methods<decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (*(T *)0))>
#define REFCNT_METHODS_P(i)                ::refcnt_methods<decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (i))>
#define REFCNT_METHODS_BASE(T)                              decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (*(T *)0))
#define REFCNT_METHODS_BASE_P(i)                            decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (i))
#define WEAKREFCNT_METHODS(T)          ::weakrefcnt_methods<decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (*(T *)0))>
#define WEAKREFCNT_METHODS_P(i)        ::weakrefcnt_methods<decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (i))>
#define WEAKREFCNT_METHODS_BASE(T)                          decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (*(T *)0))
#define WEAKREFCNT_METHODS_BASE_P(i)                        decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (i))
#define __REFCNT_METHODS_R(T)              ::refcnt_methods<T>
#define __REFCNT_METHODS(T)                ::refcnt_methods<decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (*(T *)0))>
#define __REFCNT_METHODS_P(i)              ::refcnt_methods<decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (i))>
#define __REFCNT_METHODS_BASE(T)                            decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (*(T *)0))
#define __REFCNT_METHODS_BASE_P(i)                          decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (i))
#define __WEAKREFCNT_METHODS_R(T)      ::weakrefcnt_methods<T>
#define __WEAKREFCNT_METHODS(T)        ::weakrefcnt_methods<decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (*(T *)0))>
#define __WEAKREFCNT_METHODS_P(i)      ::weakrefcnt_methods<decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (i))>
#define __WEAKREFCNT_METHODS_BASE(T)                        decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (*(T *)0))
#define __WEAKREFCNT_METHODS_BASE_P(i)                      decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (i))
#else /* __USE_KOS || __USE_KOS_KERNEL || (__KOS__ && __KERNEL__) */
#define __PRIVATE_REFCNT_NAME(x)                            __##x
#define __REFCNT_METHODS_R(T)            ::__refcnt_methods<T>
#define __REFCNT_METHODS(T)              ::__refcnt_methods<decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (*(T *)0))>
#define __REFCNT_METHODS_P(i)            ::__refcnt_methods<decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (i))>
#define __REFCNT_METHODS_BASE(T)                            decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (*(T *)0))
#define __REFCNT_METHODS_BASE_P(i)                          decltype(__NAMESPACE_INT_SYM __refcnt_select_tag() + (i))
#define __WEAKREFCNT_METHODS_R(T)    ::__weakrefcnt_methods<T>
#define __WEAKREFCNT_METHODS(T)      ::__weakrefcnt_methods<decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (*(T *)0))>
#define __WEAKREFCNT_METHODS_P(i)    ::__weakrefcnt_methods<decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (i))>
#define __WEAKREFCNT_METHODS_BASE(T)                        decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (*(T *)0))
#define __WEAKREFCNT_METHODS_BASE_P(i)                      decltype(__NAMESPACE_INT_SYM __weakrefcnt_select_tag() + (i))
#endif /* __USE_KOS || __USE_KOS_KERNEL || (__KOS__ && __KERNEL__) */


#ifdef __CHECKER__
#define __PRIVATE_REFCNT_INCREF_RT(From, To) To *
#else /* __CHECKER__ */
extern "C++" {
__NAMESPACE_INT_BEGIN
class __refcnt_select_tag {};
class __weakrefcnt_select_tag {};
template<class __To> int __private_is_refcnt_convertible_test(__To);
template<class __To> int (&__private_is_refcnt_convertible_test(...))[2];
template<class __From, class __To> struct __private_is_refcnt_convertible_probe {
	enum{__is = sizeof(__private_is_refcnt_convertible_test<__To>(*(__From *)0)) == sizeof(int)};
};
template<bool __Enable, class __Type> struct __private_is_refcnt_enable_if { typedef __Type __type; };
template<class __Type> struct __private_is_refcnt_enable_if<false, __Type> { };
template<class __From, class __To> struct __private_is_refcnt_convertible:
	__private_is_refcnt_enable_if<__private_is_refcnt_convertible_probe<__From, __To>::__is, __To> {};
#define __PRIVATE_REFCNT_INCREF_RT(From, To) \
	__CXX_DEDUCE_TYPENAME __NAMESPACE_INT_SYM __private_is_refcnt_convertible<From *, To *>::__type
__NAMESPACE_INT_END
} /* extern "C++" */
#endif /* !__CHECKER__ */


#ifdef __INTELLISENSE__
#if (defined(__USE_KOS) || defined(__USE_KOS_KERNEL) || \
     (defined(__KOS__) && defined(__KERNEL__)))
extern "C++" {
template<class __T> class refcnt_methods {
public:
	typedef __UINTPTR_TYPE__ refcnt_t;
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC incref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryincref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC decref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC destroy)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_nokill)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC decref_likely)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC decref_unlikely)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) refcnt_t __REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(__T const *__restrict self);
};
template<class __T> class weakrefcnt_methods {
public:
	typedef __UINTPTR_TYPE__ refcnt_t;
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC incref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryincref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC decref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC destroy)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_nokill)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC decref_likely)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC decref_unlikely)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) refcnt_t __REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(__T const *__restrict self);
};
} /* extern "C++" */

#define __DEFINE_REFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _)                                                                                        \
	extern "C++" {                                                                                                                                   \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __PRIVATE_REFCNT_TYPE_X(T, X, _) __REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(T const *__restrict self); \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC isshared)(T const *__restrict self);                            \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC wasdestroyed)(T const *__restrict self);                        \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryincref)(T *__restrict self);                                 \
	__NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC xincref)(T *__restrict self);                                                                          \
	__NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *__REFCNT_NOTHROW(__REFCNT_CC incref)(T *__restrict self);                                     \
	template<class __T> __NOBLOCK __PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC xincref)(__T *__restrict self);                    \
	template<class __T> __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) __PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC incref)(__T *__restrict self); \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC destroy)(T *__restrict self);                                            \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC decref)(T *__restrict self);                                             \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC decref_likely)(T *__restrict self);                                      \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC decref_unlikely)(T *__restrict self);                                    \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_nokill)(T *__restrict self);                                              \
	__NOBLOCK void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC xdecref)(T *self);                                                                           \
	__NOBLOCK void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC xdecref_likely)(T *self);                                                                    \
	__NOBLOCK void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC xdecref_unlikely)(T *self);                                                                  \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_nokill)(T *self);                                                                            \
	}
#define __DEFINE_WEAKREFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _)                                                                                        \
	extern "C++" {                                                                                                                                       \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __PRIVATE_REFCNT_TYPE_X(T, X, _) __REFCNT_NOTHROW(__REFCNT_CC getweakrefcnt)(T const *__restrict self); \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC isweakshared)(T const *__restrict self);                            \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC wasweakdestroyed)(T const *__restrict self);                        \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryweakincref)(T *__restrict self);                                 \
	__NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC xweakincref)(T *__restrict self);                                                                          \
	__NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *__REFCNT_NOTHROW(__REFCNT_CC weakincref)(T *__restrict self);                                     \
	template<class __T> __NOBLOCK __PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC xweakincref)(__T *__restrict self);                    \
	template<class __T> __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) __PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC weakincref)(__T *__restrict self); \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC weakdestroy)(T *__restrict self);                                            \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC weakdecref)(T *__restrict self);                                             \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC weakdecref_likely)(T *__restrict self);                                      \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC weakdecref_unlikely)(T *__restrict self);                                    \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_nokill)(T *__restrict self);                                              \
	__NOBLOCK void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC xweakdecref)(T *self);                                                                           \
	__NOBLOCK void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC xweakdecref_likely)(T *self);                                                                    \
	__NOBLOCK void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC xweakdecref_unlikely)(T *self);                                                                  \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_nokill)(T *self);                                                                            \
	}
#else /* __USE_KOS || __USE_KOS_KERNEL || (__KOS__ && __KERNEL__) */
template<class __T> class __refcnt_methods {
public:
	typedef __UINTPTR_TYPE__ __refcnt_t;
	static __NOBLOCK __ATTR_NONNULL((1)) __refcnt_t __REFCNT_NOTHROW(__REFCNT_CC __getrefcnt)(__T const *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __incref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC __tryincref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC __decref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC __destroy)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC __decref_likely)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC __decref_unlikely)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref_nokill)(__T *__restrict __self);
};
template<class __T> class __weakrefcnt_methods {
public:
	typedef __UINTPTR_TYPE__ __refcnt_t;
	static __NOBLOCK __ATTR_NONNULL((1)) __refcnt_t __REFCNT_NOTHROW(__REFCNT_CC __getrefcnt)(__T const *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __incref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC __tryincref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC __decref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC __destroy)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC __decref_likely)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_DESTROY_NOTHROW(__REFCNT_CC __decref_unlikely)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref_nokill)(__T *__restrict __self);
};
#define __DEFINE_REFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _)     /* nothing */
#define __DEFINE_WEAKREFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _) /* nothing */
#endif /* !__USE_KOS && !__USE_KOS_KERNEL && (!__KOS__ || !__KERNEL__) */
#define __DEFINE_REFCNT_TEMPLATE_X(T, destroy_, X, _) \
	T operator+(__NAMESPACE_INT_SYM __refcnt_select_tag, T const&);
#define __DEFINE_WEAKREFCNT_TEMPLATE_X(T, destroy_, X, _) \
	T operator+(__NAMESPACE_INT_SYM __weakrefcnt_select_tag, T const&);
#else /* __INTELLISENSE__ */

#ifndef __CHECKER__
extern "C++" {
template<class __T> class __PRIVATE_REFCNT_NAME(refcnt_methods);
template<class __T> class __PRIVATE_REFCNT_NAME(weakrefcnt_methods);
} /* extern "C++" */
#endif /* !__CHECKER__ */

#include <hybrid/__assert.h>

/* [weak]incref() */
#ifndef __PRIVATE_REFCNT_IMPL_INCREF
#define __PRIVATE_REFCNT_IMPL_INCREF(T, function, destroy_, refcnt_t, refcnt_field)    \
	refcnt_t __old_refcnt = __hybrid_atomic_fetchinc(&refcnt_field, __ATOMIC_SEQ_CST); \
	__hybrid_assertf(__old_refcnt > 0, #T "::" #function "(%p): Object was already destroyed", __self);
#endif /* !__PRIVATE_REFCNT_IMPL_INCREF */

/* [weak]decref() */
#ifndef __PRIVATE_REFCNT_IMPL_DECREF
#if defined(NDEBUG) || defined(NDEBUG_REFCNT)
#define __PRIVATE_REFCNT_IMPL_DECREF(T, function, destroy_, refcnt_t, refcnt_field, destroy_likelyhood) \
	if destroy_likelyhood(__hybrid_atomic_decfetch(&refcnt_field, __ATOMIC_SEQ_CST) == 0)               \
		destroy_(__self);
#else /* NDEBUG || NDEBUG_REFCNT */
#define __PRIVATE_REFCNT_IMPL_DECREF(T, function, destroy_, refcnt_t, refcnt_field, destroy_likelyhood) \
	refcnt_t __old_refcnt = __hybrid_atomic_fetchdec(&refcnt_field, __ATOMIC_SEQ_CST);                  \
	__hybrid_assertf(__old_refcnt > 0, #T "::" #function "(%p): Object was already destroyed", __self); \
	if destroy_likelyhood(__old_refcnt == 1)                                                            \
		destroy_(__self);
#endif /* !NDEBUG && !NDEBUG_REFCNT */
#endif /* !__PRIVATE_REFCNT_IMPL_DECREF */

/* [weak]decref_nokill() */
#ifndef __PRIVATE_REFCNT_IMPL_DECREF_NOKILL
#if defined(NDEBUG) || defined(NDEBUG_REFCNT)
#define __PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, function, destroy_, refcnt_t, refcnt_field) \
	__hybrid_atomic_dec(&refcnt_field, __ATOMIC_SEQ_CST);
#else /* NDEBUG || NDEBUG_REFCNT */
#define __PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, function, destroy_, refcnt_t, refcnt_field)              \
	refcnt_t __old_refcnt = __hybrid_atomic_fetchdec(&refcnt_field, __ATOMIC_SEQ_CST);                  \
	__hybrid_assertf(__old_refcnt > 0, #T "::" #function "(%p): Object was already destroyed", __self); \
	__hybrid_assertf(__old_refcnt > 1, #T "::" #function "(%p): Object should have been destroyed", __self);
#endif /* !NDEBUG && !NDEBUG_REFCNT */
#endif /* !__PRIVATE_REFCNT_IMPL_DECREF_NOKILL */

/* [weak]destroy() */
#ifndef __PRIVATE_REFCNT_IMPL_DESTROY
#if defined(NDEBUG) || defined(NDEBUG_REFCNT)
#define __PRIVATE_REFCNT_IMPL_DESTROY(T, function, destroy_, refcnt_t, refcnt_field) \
	destroy_(__self);
#else /* NDEBUG || NDEBUG_REFCNT */
#define __PRIVATE_REFCNT_IMPL_DESTROY(T, function, destroy_, refcnt_t, refcnt_field) \
	/* Satisfy refcnt assertions within `destroy_()' */                              \
	__hybrid_atomic_store(&refcnt_field, (refcnt_t)0, __ATOMIC_RELEASE);             \
	destroy_(__self);
#endif /* !NDEBUG && !NDEBUG_REFCNT */
#endif /* !__PRIVATE_REFCNT_IMPL_DESTROY */

/* try[weak]incref() */
#ifndef __PRIVATE_REFCNT_IMPL_TRYINCREF
#define __PRIVATE_REFCNT_IMPL_TRYINCREF(T, function, destroy_, refcnt_t, refcnt_field)   \
	refcnt_t __old_refcnt;                                                               \
	do {                                                                                 \
		__old_refcnt = __hybrid_atomic_load(&refcnt_field, __ATOMIC_ACQUIRE);            \
		if (!(__old_refcnt > 0))                                                         \
			return false;                                                                \
	} while (!__hybrid_atomic_cmpxch_weak(&refcnt_field, __old_refcnt, __old_refcnt + 1, \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));          \
	return true;
#endif /* !__PRIVATE_REFCNT_IMPL_TRYINCREF */

#ifdef __CHECKER__
#define __DEFINE_REFCNT_TEMPLATE_X(T, destroy_, X, _)     /* Nothing */
#define __DEFINE_WEAKREFCNT_TEMPLATE_X(T, destroy_, X, _) /* Nothing */
#define __DEFINE_REFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _)                                                                      \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                        \
	__PRIVATE_REFCNT_TYPE_X(T, X, _) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {  \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE);                                                              \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                        \
	bool __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(isshared))(T const *__restrict __self) {                               \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE) > 1;                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                        \
	bool __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(wasdestroyed))(T const *__restrict __self) {                           \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE) == 0;                                                         \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1))                                                 \
	T *__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                                         \
		__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK                                                                                       \
	T *__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xincref))(T *__self) {                                                   \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *                                             \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                                            \
		__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK T *                                                                                   \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xincref))(T *__self) {                                                      \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                                            \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                                         \
		__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                    \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                                   \
		__PRIVATE_REFCNT_IMPL_DESTROY(T, destroy, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                        \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                                    \
		__PRIVATE_REFCNT_IMPL_DECREF(T, decref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                    \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                             \
		__PRIVATE_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)         \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                           \
		__PRIVATE_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely)     \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                                     \
		__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))            \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref))(T *__self) {                                              \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                \
		}                                                                                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref_likely))(T *__self) {                                       \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)     \
		}                                                                                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref_unlikely))(T *__self) {                                     \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely) \
		}                                                                                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref_nokill))(T *__self) {                                               \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))        \
		}                                                                                                                          \
	}
#define __DEFINE_WEAKREFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _)                                                                      \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                            \
	__PRIVATE_REFCNT_TYPE_X(T, X, _) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getweakrefcnt))(T const *__restrict __self) {  \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE);                                                                  \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                            \
	bool __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(isweakshared))(T const *__restrict __self) {                               \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE) > 1;                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                            \
	bool __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(wasweakdestroyed))(T const *__restrict __self) {                           \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE) == 0;                                                             \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1))                                                     \
	T *__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakincref))(T *__restrict __self) {                                         \
		__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK                                                                                           \
	T *__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakincref))(T *__self) {                                                   \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                              \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *                                                 \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakincref))(T *__restrict __self) {                                            \
		__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK T *                                                                                       \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakincref))(T *__self) {                                                      \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                              \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                                                \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryweakincref))(T *__restrict __self) {                                         \
		__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryweakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                    \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdestroy))(T *__restrict __self) {                                   \
		__PRIVATE_REFCNT_IMPL_DESTROY(T, weakdestroy, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                        \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref))(T *__restrict __self) {                                    \
		__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                    \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref_likely))(T *__restrict __self) {                             \
		__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)         \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref_unlikely))(T *__restrict __self) {                           \
		__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely)     \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref_nokill))(T *__restrict __self) {                                     \
		__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))            \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref))(T *__self) {                                              \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                \
		}                                                                                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref_likely))(T *__self) {                                       \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)     \
		}                                                                                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref_unlikely))(T *__self) {                                     \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely) \
		}                                                                                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref_nokill))(T *__self) {                                               \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))        \
		}                                                                                                                              \
	}
#else /* __CHECKER__ */
#define __DEFINE_REFCNT_TEMPLATE_X(T, destroy_, X, _)                                                                             \
	T operator+(__NAMESPACE_INT_SYM __refcnt_select_tag, T const&);                                                               \
	template<> class __PRIVATE_REFCNT_NAME(refcnt_methods)< T > {                                                                 \
	public:                                                                                                                       \
		typedef __PRIVATE_REFCNT_TYPE_X(T, X, _) __PRIVATE_REFCNT_NAME(refcnt_t);                                                 \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                                                \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {                              \
			return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE);                                                         \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                                       \
			__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                      \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                           \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                                    \
			__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryincref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                               \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), /**/)                \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                              \
			__PRIVATE_REFCNT_IMPL_DESTROY(T, destroy, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                    \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                        \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), __likely)     \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                      \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), __unlikely) \
		}                                                                                                                         \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                             \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                                \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))        \
		}                                                                                                                         \
	};
#define __DEFINE_WEAKREFCNT_TEMPLATE_X(T, destroy_, X, _)                                                                            \
	T operator+(__NAMESPACE_INT_SYM __weakrefcnt_select_tag, T const&);                                                              \
	template<> class __PRIVATE_REFCNT_NAME(weakrefcnt_methods)< T > {                                                                \
	public:                                                                                                                          \
		typedef __PRIVATE_REFCNT_TYPE_X(T, X, _) __PRIVATE_REFCNT_NAME(refcnt_t);                                                    \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                                                   \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {                                 \
			return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE);                                                            \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                                          \
			__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                     \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                                       \
			__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryweakincref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))               \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                                  \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), /**/)               \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                                 \
			__PRIVATE_REFCNT_IMPL_DESTROY(T, weakdestroy, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))                   \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                           \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), __likely)    \
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                         \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self), __unlikely)\
		}                                                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                                   \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __PRIVATE_REFCNT_NAME(refcnt_t), X(_, __self))       \
		}                                                                                                                            \
	};
#define __DEFINE_REFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _)                                                                      \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                        \
	__PRIVATE_REFCNT_TYPE_X(T, X, _) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {  \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE);                                                              \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                        \
	bool __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(isshared))(T const *__restrict __self) {                               \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE) > 1;                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                        \
	bool __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(wasdestroyed))(T const *__restrict __self) {                           \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE) == 0;                                                         \
	}                                                                                                                              \
	template<class __T> __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1))                             \
	__PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(__T *__restrict __self) {       \
		__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	template<class __T> __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK                                                                   \
	__PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xincref))(__T *__self) {                 \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *                                             \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                                            \
		__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK T *                                                                                   \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xincref))(T *__self) {                                                      \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                          \
		return __self;                                                                                                             \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                                            \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                                         \
		__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                    \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                                   \
		__PRIVATE_REFCNT_IMPL_DESTROY(T, destroy, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                        \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                                    \
		__PRIVATE_REFCNT_IMPL_DECREF(T, decref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                    \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                             \
		__PRIVATE_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)         \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                           \
		__PRIVATE_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely)     \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                              \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                                     \
		__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))            \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref))(T *__self) {                                              \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                \
		}                                                                                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref_likely))(T *__self) {                                       \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)     \
		}                                                                                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref_unlikely))(T *__self) {                                     \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely) \
		}                                                                                                                          \
	}                                                                                                                              \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xdecref_nokill))(T *__self) {                                               \
		if (__self) {                                                                                                              \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))        \
		}                                                                                                                          \
	}
#define __DEFINE_WEAKREFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _)                                                                      \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                            \
	__PRIVATE_REFCNT_TYPE_X(T, X, _) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getweakrefcnt))(T const *__restrict __self) {  \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE);                                                                  \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                            \
	bool __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(isweakshared))(T const *__restrict __self) {                               \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE) > 1;                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))                                            \
	bool __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(wasweakdestroyed))(T const *__restrict __self) {                           \
		return __hybrid_atomic_load(&X(_, __self), __ATOMIC_ACQUIRE) == 0;                                                             \
	}                                                                                                                                  \
	template<class __T> __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1))                                 \
	__PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakincref))(__T *__restrict __self) {       \
		__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	template<class __T> __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK                                                                       \
	__PRIVATE_REFCNT_INCREF_RT(__T, T) __REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakincref))(__T *__self) {                 \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                              \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *                                                 \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakincref))(T *__restrict __self) {                                            \
		__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                          \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK T *                                                                                       \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakincref))(T *__self) {                                                      \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                      \
		}                                                                                                                              \
		return __self;                                                                                                                 \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                                                \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryweakincref))(T *__restrict __self) {                                         \
		__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryweakincref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                    \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdestroy))(T *__restrict __self) {                                   \
		__PRIVATE_REFCNT_IMPL_DESTROY(T, weakdestroy, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))                        \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref))(T *__restrict __self) {                                    \
		__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                    \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref_likely))(T *__restrict __self) {                             \
		__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)         \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref_unlikely))(T *__restrict __self) {                           \
		__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely)     \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                                                  \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(weakdecref_nokill))(T *__restrict __self) {                                     \
		__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))            \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref))(T *__self) {                                              \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), /**/)                \
		}                                                                                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref_likely))(T *__self) {                                       \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __likely)     \
		}                                                                                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_DESTROY_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref_unlikely))(T *__self) {                                     \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self), __unlikely) \
		}                                                                                                                              \
	}                                                                                                                                  \
	__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void                                                                                      \
	__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(xweakdecref_nokill))(T *__self) {                                               \
		if (__self) {                                                                                                                  \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __PRIVATE_REFCNT_TYPE_X(T, X, _), X(_, __self))        \
		}                                                                                                                              \
	}
#endif /* !__CHECKER__ */
#endif /* !__INTELLISENSE__ */

#define __DEFINE_REFCNT_FUNCTIONS_X(T, destroy_, X, _)    \
	extern "C++" {                                        \
	__DEFINE_REFCNT_TEMPLATE_X(T, destroy_, X, _)         \
	__DEFINE_REFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _) \
	} /* extern "C++" */
#define __DEFINE_WEAKREFCNT_FUNCTIONS_X(T, destroy_, X, _)    \
	extern "C++" {                                            \
	__DEFINE_WEAKREFCNT_TEMPLATE_X(T, destroy_, X, _)         \
	__DEFINE_WEAKREFCNT_GLOBAL_FUNCTIONS_X(T, destroy_, X, _) \
	} /* extern "C++" */
#else /* __cplusplus && __CC__ */
#define __DEFINE_REFCNT_FUNCTIONS_X(T, destroy_, X, _)     /* nothing */
#define __DEFINE_WEAKREFCNT_FUNCTIONS_X(T, destroy_, X, _) /* nothing */
#endif /* !__cplusplus || !__CC__ */

#define __DEFINE_REFCNT_FUNCTIONS(T, field, destroy_) \
	__DEFINE_REFCNT_FUNCTIONS_X(T, destroy_, __PRIVATE_REFCNT_Xfld, field)
#define __DEFINE_REFCNT_FUNCTIONS_P(T, getfield, destroy_) \
	__DEFINE_REFCNT_FUNCTIONS_X(T, destroy_, __PRIVATE_REFCNT_Xpth, getfield)
#define __DEFINE_WEAKREFCNT_FUNCTIONS(T, field, destroy_) \
	__DEFINE_WEAKREFCNT_FUNCTIONS_X(T, destroy_, __PRIVATE_REFCNT_Xfld, field)
#define __DEFINE_WEAKREFCNT_FUNCTIONS_P(T, getfield, destroy_) \
	__DEFINE_WEAKREFCNT_FUNCTIONS_X(T, destroy_, __PRIVATE_REFCNT_Xpth, getfield)

#endif /* !_KOS_REFCNT_H */
