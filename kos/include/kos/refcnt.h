/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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
#define __PRIVATE_REFCNT_TYPE(T, field)      __typeof__(((T *)0)->field)
#define __PRIVATE_REFCNT_TYPE_P(T, getfield) __typeof__(getfield((T *)0))
#elif defined(__COMPILER_HAVE_CXX_DECLTYPE)
#define __PRIVATE_REFCNT_TYPE(T, field)      decltype(((T *)0)->field)
#define __PRIVATE_REFCNT_TYPE_P(T, getfield) decltype(getfield((T *)0))
#else /* __COMPILER_HAVE_CXX_DECLTYPE */
#include <hybrid/typecore.h>
#define __PRIVATE_REFCNT_TYPE(T, field)      __UINTPTR_TYPE__
#define __PRIVATE_REFCNT_TYPE_P(T, getfield) __UINTPTR_TYPE__
#endif /* !__COMPILER_HAVE_CXX_DECLTYPE */

#ifndef __REFCNT_CC
#ifdef __KERNEL__
#define __REFCNT_CC __KCALL
#else /* __KERNEL__ */
#define __REFCNT_CC /* nothing */
#endif /* !__KERNEL__ */
#endif /* !__REFCNT_CC */

#ifndef __REFCNT_NOTHROW
#ifdef __KERNEL__
#define __REFCNT_NOTHROW __NOTHROW
#else /* __KERNEL__ */
#define __REFCNT_NOTHROW __NOTHROW_NCX
#endif /* !__KERNEL__ */
#endif /* !__REFCNT_NOTHROW */


extern "C++" {

__NAMESPACE_INT_BEGIN
class __refcnt_select_tag {};
class __weakrefcnt_select_tag {};
__NAMESPACE_INT_END

#if (defined(__USE_KOS) || defined(__USE_KOS_KERNEL) || \
     (defined(__KOS__) && defined(__KERNEL__)))
#define __PRIVATE_REFCNT_NAME(x) x
template<class __T> class refcnt_methods
#ifdef __INTELLISENSE__
{
public:
	typedef __UINTPTR_TYPE__ refcnt_t;
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC incref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryincref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC destroy)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_nokill)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_likely)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_unlikely)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) refcnt_t __REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(__T const *__restrict self);
}
#endif /* __INTELLISENSE__ */
;
template<class __T> class weakrefcnt_methods
#ifdef __INTELLISENSE__
{
public:
	typedef __UINTPTR_TYPE__ refcnt_t;
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC incref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryincref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC destroy)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_nokill)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_likely)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_unlikely)(__T *__restrict self);
	static __NOBLOCK __ATTR_NONNULL((1)) refcnt_t __REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(__T const *__restrict self);
}
#endif /* __INTELLISENSE__ */
;

#define REFCNT_METHODS(T)                  ::refcnt_methods<decltype(((*(T *)0), __NAMESPACE_INT_SYM __refcnt_select_tag()))>
#define REFCNT_METHODS_P(i)                ::refcnt_methods<decltype(((i), __NAMESPACE_INT_SYM __refcnt_select_tag()))>
#define REFCNT_METHODS_BASE(T)                              decltype(((*(T *)0), __NAMESPACE_INT_SYM __refcnt_select_tag()))
#define REFCNT_METHODS_BASE_P(i)                            decltype(((i), __NAMESPACE_INT_SYM __refcnt_select_tag()))
#define WEAKREFCNT_METHODS(T)          ::weakrefcnt_methods<decltype(((*(T *)0), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))>
#define WEAKREFCNT_METHODS_P(i)        ::weakrefcnt_methods<decltype(((i), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))>
#define WEAKREFCNT_METHODS_BASE(T)                          decltype(((*(T *)0), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))
#define WEAKREFCNT_METHODS_BASE_P(i)                        decltype(((i), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))
#define __REFCNT_METHODS(T)                ::refcnt_methods<decltype(((*(T *)0), __NAMESPACE_INT_SYM __refcnt_select_tag()))>
#define __REFCNT_METHODS_P(i)              ::refcnt_methods<decltype(((i), __NAMESPACE_INT_SYM __refcnt_select_tag()))>
#define __REFCNT_METHODS_BASE(T)                            decltype(((*(T *)0), __NAMESPACE_INT_SYM __refcnt_select_tag()))
#define __REFCNT_METHODS_BASE_P(i)                          decltype(((i), __NAMESPACE_INT_SYM __refcnt_select_tag()))
#define __WEAKREFCNT_METHODS(T)        ::weakrefcnt_methods<decltype(((*(T *)0), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))>
#define __WEAKREFCNT_METHODS_P(i)      ::weakrefcnt_methods<decltype(((i), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))>
#define __WEAKREFCNT_METHODS_BASE(T)                        decltype(((*(T *)0), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))
#define __WEAKREFCNT_METHODS_BASE_P(i)                      decltype(((i), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))

#ifdef __INTELLISENSE__
#define __DEFINE_REFCOUNT_FUNCTIONS(T, field, destroy_)                                                                                             \
	extern "C++" {                                                                                                                                  \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                                                                 \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __PRIVATE_REFCNT_TYPE(T, field) __REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(T const *__restrict self); \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC isshared)(T const *__restrict self);                           \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC wasdestroyed)(T const *__restrict self);                       \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryincref)(T *__restrict self);                                \
	__NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC xincref)(T *__restrict self);                                                                         \
	__NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *__REFCNT_NOTHROW(__REFCNT_CC incref)(T *__restrict self);                                    \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC destroy)(T *__restrict self);                                                   \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref)(T *__restrict self);                                                    \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_nokill)(T *__restrict self);                                             \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_likely)(T *__restrict self);                                             \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_unlikely)(T *__restrict self);                                           \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref)(T *self);                                                                                  \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_nokill)(T *self);                                                                           \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_likely)(T *self);                                                                           \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_unlikely)(T *self);                                                                         \
	}
#define __DEFINE_REFCOUNT_FUNCTIONS_P(T, getfield, destroy_)                                                                                             \
	extern "C++" {                                                                                                                                       \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                                                                      \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __PRIVATE_REFCNT_TYPE_P(T, getfield) __REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(T const *__restrict self); \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC isshared)(T const *__restrict self);                                \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC wasdestroyed)(T const *__restrict self);                            \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryincref)(T *__restrict self);                                     \
	__NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC xincref)(T *__restrict self);                                                                              \
	__NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *__REFCNT_NOTHROW(__REFCNT_CC incref)(T *__restrict self);                                         \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC destroy)(T *__restrict self);                                                        \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref)(T *__restrict self);                                                         \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_nokill)(T *__restrict self);                                                  \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_likely)(T *__restrict self);                                                  \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_unlikely)(T *__restrict self);                                                \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref)(T *self);                                                                                       \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_nokill)(T *self);                                                                                \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_likely)(T *self);                                                                                \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_unlikely)(T *self);                                                                              \
	}
#define __DEFINE_WEAKREFCOUNT_FUNCTIONS(T, field, destroy_)                                                                                             \
	extern "C++" {                                                                                                                                      \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                                                                                 \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __PRIVATE_REFCNT_TYPE(T, field) __REFCNT_NOTHROW(__REFCNT_CC getweakrefcnt)(T const *__restrict self); \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC isweakshared)(T const *__restrict self);                           \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC wasweakdestroyed)(T const *__restrict self);                       \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryweakincref)(T *__restrict self);                                \
	__NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC xweakincref)(T *__restrict self);                                                                         \
	__NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *__REFCNT_NOTHROW(__REFCNT_CC weakincref)(T *__restrict self);                                    \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdestroy)(T *__restrict self);                                                   \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref)(T *__restrict self);                                                    \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_nokill)(T *__restrict self);                                             \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_likely)(T *__restrict self);                                             \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_unlikely)(T *__restrict self);                                           \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref)(T *self);                                                                                  \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_nokill)(T *self);                                                                           \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_likely)(T *self);                                                                           \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_unlikely)(T *self);                                                                         \
	}
#define __DEFINE_WEAKREFCOUNT_FUNCTIONS_P(T, getfield, destroy_)                                                                                             \
	extern "C++" {                                                                                                                                           \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                                                                                      \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __PRIVATE_REFCNT_TYPE_P(T, getfield) __REFCNT_NOTHROW(__REFCNT_CC getweakrefcnt)(T const *__restrict self); \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC isweakshared)(T const *__restrict self);                                \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC wasweakdestroyed)(T const *__restrict self);                            \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryweakincref)(T *__restrict self);                                     \
	__NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC xweakincref)(T *__restrict self);                                                                              \
	__NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *__REFCNT_NOTHROW(__REFCNT_CC weakincref)(T *__restrict self);                                         \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdestroy)(T *__restrict self);                                                        \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref)(T *__restrict self);                                                         \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_nokill)(T *__restrict self);                                                  \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_likely)(T *__restrict self);                                                  \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_unlikely)(T *__restrict self);                                                \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref)(T *self);                                                                                       \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_nokill)(T *self);                                                                                \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_likely)(T *self);                                                                                \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_unlikely)(T *self);                                                                              \
	}
#endif /* __INTELLISENSE__ */
#else /* __USE_KOS || __USE_KOS_KERNEL || (__KOS__ && __KERNEL__) */
#define __PRIVATE_REFCNT_NAME(x) __##x
template<class __T> class __refcnt_methods
#ifdef __INTELLISENSE__
{
public:
	typedef __UINTPTR_TYPE__ __refcnt_t;
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __incref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC __tryincref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __destroy)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref_nokill)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref_likely)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref_unlikely)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) __refcnt_t __REFCNT_NOTHROW(__REFCNT_CC __getrefcnt)(__T const *__restrict __self);
}
#endif /* __INTELLISENSE__ */
;
template<class __T> class __weakrefcnt_methods
#ifdef __INTELLISENSE__
{
public:
	typedef __UINTPTR_TYPE__ __refcnt_t;
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __incref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC __tryincref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __destroy)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref_nokill)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref_likely)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC __decref_unlikely)(__T *__restrict __self);
	static __NOBLOCK __ATTR_NONNULL((1)) __refcnt_t __REFCNT_NOTHROW(__REFCNT_CC __getrefcnt)(__T const *__restrict __self);
}
#endif /* __INTELLISENSE__ */
;

#define __REFCNT_METHODS(T)                ::__refcnt_methods<decltype(((*(T *)0), __NAMESPACE_INT_SYM __refcnt_select_tag()))>
#define __REFCNT_METHODS_P(i)              ::__refcnt_methods<decltype(((i), __NAMESPACE_INT_SYM __refcnt_select_tag()))>
#define __REFCNT_METHODS_BASE(T)                              decltype(((*(T *)0), __NAMESPACE_INT_SYM __refcnt_select_tag()))
#define __REFCNT_METHODS_BASE_P(i)                            decltype(((i), __NAMESPACE_INT_SYM __refcnt_select_tag()))
#define __WEAKREFCNT_METHODS(T)        ::__weakrefcnt_methods<decltype(((*(T *)0), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))>
#define __WEAKREFCNT_METHODS_P(i)      ::__weakrefcnt_methods<decltype(((i), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))>
#define __WEAKREFCNT_METHODS_BASE(T)                          decltype(((*(T *)0), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))
#define __WEAKREFCNT_METHODS_BASE_P(i)                        decltype(((i), __NAMESPACE_INT_SYM __weakrefcnt_select_tag()))
#endif /* !__USE_KOS && !__USE_KOS_KERNEL && (!__KOS__ || !__KERNEL__) */


#ifndef __DEFINE_REFCOUNT_FUNCTIONS
} /* extern "C++" */
#include <hybrid/__assert.h>
extern "C++" {

/* [weak]incref() */
#ifndef __PRIVATE_REFCNT_IMPL_INCREF
#define __PRIVATE_REFCNT_IMPL_INCREF(T, function, destroy_, refcnt_field)                                    \
	__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchinc(refcnt_field, __ATOMIC_SEQ_CST); \
	__hybrid_assertf(__old_refcnt > 0, #T "::" #function "(%p): Object was already destroyed", __self);
#endif /* !__PRIVATE_REFCNT_IMPL_INCREF */

/* [weak]decref() */
#ifndef __PRIVATE_REFCNT_IMPL_DECREF
#ifdef NDEBUG
#define __PRIVATE_REFCNT_IMPL_DECREF(T, function, destroy_, refcnt_field, destroy_likelyhood) \
	if destroy_likelyhood(__hybrid_atomic_decfetch(refcnt_field, __ATOMIC_SEQ_CST) == 0)      \
		destroy_(__self);
#else /* NDEBUG */
#define __PRIVATE_REFCNT_IMPL_DECREF(T, function, destroy_, refcnt_field, destroy_likelyhood)                \
	__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(refcnt_field, __ATOMIC_SEQ_CST); \
	__hybrid_assertf(__old_refcnt > 0, #T "::" #function "(%p): Object was already destroyed", __self);      \
	if destroy_likelyhood(__old_refcnt == 1)                                                                 \
		destroy_(__self);
#endif /* !NDEBUG */
#endif /* !__PRIVATE_REFCNT_IMPL_DECREF */

/* [weak]decref_nokill() */
#ifndef __PRIVATE_REFCNT_IMPL_DECREF_NOKILL
#ifdef NDEBUG
#define __PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, function, destroy_, refcnt_field) \
	__hybrid_atomic_dec(refcnt_field, __ATOMIC_SEQ_CST);
#else /* NDEBUG */
#define __PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, function, destroy_, refcnt_field)                             \
	__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(refcnt_field, __ATOMIC_SEQ_CST); \
	__hybrid_assertf(__old_refcnt > 0, "decref_nokill(%p): Object was already destroyed", __self);           \
	__hybrid_assertf(__old_refcnt > 1, "decref_nokill(%p): Object should have been destroyed", __self);
#endif /* !NDEBUG */
#endif /* !__PRIVATE_REFCNT_IMPL_DECREF_NOKILL */

/* [weak]destroy() */
#ifndef __PRIVATE_REFCNT_IMPL_DESTROY
#ifdef NDEBUG
#define __PRIVATE_REFCNT_IMPL_DESTROY(T, function, destroy_, refcnt_field) \
	destroy_(self);
#else /* NDEBUG */
#define __PRIVATE_REFCNT_IMPL_DESTROY(T, function, destroy_, refcnt_field)                     \
	__hybrid_atomic_store(refcnt_field, (__PRIVATE_REFCNT_NAME(refcnt_t))0, __ATOMIC_RELEASE); \
	destroy_(__self);
#endif /* !NDEBUG */
#endif /* !__PRIVATE_REFCNT_IMPL_DESTROY */

/* try[weak]incref() */
#ifndef __PRIVATE_REFCNT_IMPL_TRYINCREF
#define __PRIVATE_REFCNT_IMPL_TRYINCREF(T, function, destroy_, refcnt_field)            \
	__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                       \
	do {                                                                                \
		__old_refcnt = __hybrid_atomic_load(refcnt_field, __ATOMIC_ACQUIRE);            \
		if (!(__old_refcnt > 0))                                                        \
			return false;                                                               \
	} while (!__hybrid_atomic_cmpxch_weak(refcnt_field, __old_refcnt, __old_refcnt + 1, \
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));         \
	return true;
#endif /* !__PRIVATE_REFCNT_IMPL_TRYINCREF */


#define __DEFINE_REFCOUNT_FUNCTIONS(T, field, destroy_)                                              \
	extern "C++" {                                                                                   \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                  \
	template<> class __PRIVATE_REFCNT_NAME(refcnt_methods)< T > {                                    \
	public:                                                                                          \
		typedef __PRIVATE_REFCNT_TYPE(T, field) __PRIVATE_REFCNT_NAME(refcnt_t);                     \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                   \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) { \
			return __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                            \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {          \
			__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, __self->field)                         \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {       \
			__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryincref, destroy_, __self->field)                   \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {          \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref, destroy_, __self->field, /**/)                   \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {         \
			__PRIVATE_REFCNT_IMPL_DESTROY(T, destroy, destroy_, __self->field)                       \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {   \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, __self->field)           \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {   \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, __self->field, __likely)        \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) { \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, __self->field, __unlikely)    \
		}                                                                                            \
	};                                                                                               \
	}
#define __DEFINE_REFCOUNT_FUNCTIONS_P(T, getfield, destroy_)                                         \
	extern "C++" {                                                                                   \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                  \
	template<> class __PRIVATE_REFCNT_NAME(refcnt_methods)< T > {                                    \
	public:                                                                                          \
		typedef __PRIVATE_REFCNT_TYPE_P(T, getfield) __PRIVATE_REFCNT_NAME(refcnt_t);                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                   \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) { \
			return __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);                         \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {          \
			__PRIVATE_REFCNT_IMPL_INCREF(T, incref, destroy_, getfield(__self))                      \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {       \
			__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryincref, destroy_, getfield(__self))                \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {          \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref, destroy_, getfield(__self), /**/)                \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {         \
			__PRIVATE_REFCNT_IMPL_DESTROY(T, destroy, destroy_, getfield(__self))                    \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {   \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, decref_nokill, destroy_, getfield(__self))        \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {   \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_likely, destroy_, getfield(__self), __likely)     \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) { \
			__PRIVATE_REFCNT_IMPL_DECREF(T, decref_unlikely, destroy_, getfield(__self), __unlikely) \
		}                                                                                            \
	};                                                                                               \
	}
#define __DEFINE_WEAKREFCOUNT_FUNCTIONS(T, field, destroy_)                                           \
	extern "C++" {                                                                                    \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                               \
	template<> class weakrefcnt_methods< T > {                                                        \
	public:                                                                                           \
		typedef __PRIVATE_REFCNT_TYPE(T, field) __PRIVATE_REFCNT_NAME(refcnt_t);                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                    \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                     \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {  \
			return __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                             \
		}                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {           \
			__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, __self->field)                      \
		}                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL               \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {        \
			__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryweakincref, destroy_, __self->field)                \
		}                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {           \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, __self->field, /**/)                \
		}                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {          \
			__PRIVATE_REFCNT_IMPL_DESTROY(T, weakdestroy, destroy_, __self->field)                    \
		}                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {    \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, __self->field)        \
		}                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {    \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, __self->field, __likely)     \
		}                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {  \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, __self->field, __unlikely) \
		}                                                                                             \
	};                                                                                                \
	}
#define __DEFINE_WEAKREFCOUNT_FUNCTIONS_P(T, getfield, destroy_)                                         \
	extern "C++" {                                                                                       \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                                  \
	template<> class weakrefcnt_methods< T > {                                                           \
	public:                                                                                              \
		typedef __PRIVATE_REFCNT_TYPE_P(T, getfield) __PRIVATE_REFCNT_NAME(refcnt_t);                    \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                       \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                        \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {     \
			return __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);                             \
		}                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {              \
			__PRIVATE_REFCNT_IMPL_INCREF(T, weakincref, destroy_, getfield(__self))                      \
		}                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                  \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {           \
			__PRIVATE_REFCNT_IMPL_TRYINCREF(T, tryweakincref, destroy_, getfield(__self))                \
		}                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {              \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref, destroy_, getfield(__self), /**/)                \
		}                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {             \
			__PRIVATE_REFCNT_IMPL_DESTROY(T, weakdestroy, destroy_, getfield(__self))                    \
		}                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {       \
			__PRIVATE_REFCNT_IMPL_DECREF_NOKILL(T, weakdecref_nokill, destroy_, getfield(__self))        \
		}                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {       \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_likely, destroy_, getfield(__self), __likely)     \
		}                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {     \
			__PRIVATE_REFCNT_IMPL_DECREF(T, weakdecref_unlikely, destroy_, getfield(__self), __unlikely) \
		}                                                                                                \
	};                                                                                                   \
	}
#endif /* !__DEFINE_REFCOUNT_FUNCTIONS */


#if !defined(__INTELLISENSE__) || (!defined(__USE_KOS) && !defined(__USE_KOS_KERNEL))
template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))
typename __REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(refcnt_t)
__REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(__T const *__restrict __self) {
	return (__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__REFCNT_NOTHROW(__REFCNT_CC isshared)(__T const *__restrict __self) {
	return (__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self) > 1;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__REFCNT_NOTHROW(__REFCNT_CC wasdestroyed)(__T const *__restrict __self) {
	return (__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self) == 0;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__REFCNT_NOTHROW(__REFCNT_CC tryincref)(__T *__restrict __self) {
	return (__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(tryincref))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) __T *
__REFCNT_NOTHROW(__REFCNT_CC incref)(__T *__restrict __self) {
	(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(incref))(__self);
	return __self;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __T *
__REFCNT_NOTHROW(__REFCNT_CC xincref)(__T *__restrict __self) {
	if (__self)
		(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(incref))(__self);
	return __self;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC destroy)(__T *__restrict __self) {
	(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(destroy))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC decref)(__T *__restrict __self) {
	(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC decref_nokill)(__T *__restrict __self) {
	(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_nokill))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC decref_likely)(__T *__restrict __self) {
	(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_likely))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC decref_unlikely)(__T *__restrict __self) {
	(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_unlikely))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void
__REFCNT_NOTHROW(__REFCNT_CC xdecref)(__T *__self) {
	if (__self)
		(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void
__REFCNT_NOTHROW(__REFCNT_CC xdecref_nokill)(__T *__self) {
	if (__self)
		(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_nokill))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void
__REFCNT_NOTHROW(__REFCNT_CC xdecref_likely)(__T *__self) {
	if (__self)
		(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_likely))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void
__REFCNT_NOTHROW(__REFCNT_CC xdecref_unlikely)(__T *__self) {
	if (__self)
		(__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_unlikely))(__self);
}


template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1))
typename __WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(refcnt_t)
__REFCNT_NOTHROW(__REFCNT_CC getweakrefcnt)(__T const *__restrict __self) {
	return (__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__REFCNT_NOTHROW(__REFCNT_CC isweakshared)(__T const *__restrict __self) {
	return (__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self) > 1;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__REFCNT_NOTHROW(__REFCNT_CC wasweakdestroyed)(__T const *__restrict __self) {
	return (__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self) == 0;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__REFCNT_NOTHROW(__REFCNT_CC tryweakincref)(__T *__restrict __self) {
	return (__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(tryincref))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) __T *
__REFCNT_NOTHROW(__REFCNT_CC weakincref)(__T *__restrict __self) {
	(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(incref))(__self);
	return __self;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __T *
__REFCNT_NOTHROW(__REFCNT_CC xweakincref)(__T *__restrict __self) {
	if (__self)
		(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(incref))(__self);
	return __self;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC weakdestroy)(__T *__restrict __self) {
	(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(destroy))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC weakdecref)(__T *__restrict __self) {
	(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC weakdecref_nokill)(__T *__restrict __self) {
	(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_nokill))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC weakdecref_likely)(__T *__restrict __self) {
	(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_likely))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void
__REFCNT_NOTHROW(__REFCNT_CC weakdecref_unlikely)(__T *__restrict __self) {
	(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_unlikely))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void
__REFCNT_NOTHROW(__REFCNT_CC xweakdecref)(__T *__self) {
	if (__self)
		(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void
__REFCNT_NOTHROW(__REFCNT_CC xweakdecref_nokill)(__T *__self) {
	if (__self)
		(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_nokill))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void
__REFCNT_NOTHROW(__REFCNT_CC xweakdecref_likely)(__T *__self) {
	if (__self)
		(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_likely))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK void
__REFCNT_NOTHROW(__REFCNT_CC xweakdecref_unlikely)(__T *__self) {
	if (__self)
		(__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(decref_unlikely))(__self);
}
#endif /* !__INTELLISENSE__ || (!__USE_KOS && !__USE_KOS_KERNEL) */

} /* extern "C++" */

#else /* __cplusplus && __CC__ */

#define __DEFINE_REFCOUNT_FUNCTIONS(T, field, destroy_)          /* nothing */
#define __DEFINE_REFCOUNT_FUNCTIONS_P(T, getfield, destroy_)     /* nothing */
#define __DEFINE_WEAKREFCOUNT_FUNCTIONS(T, field, destroy_)      /* nothing */
#define __DEFINE_WEAKREFCOUNT_FUNCTIONS_P(T, getfield, destroy_) /* nothing */

#endif /* !__cplusplus || !__CC__ */


#endif /* !_KOS_REFCNT_H */
