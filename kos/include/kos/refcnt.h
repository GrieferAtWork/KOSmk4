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
#ifndef _KOS_REFCNT_H
#define _KOS_REFCNT_H 1

#include <__stdinc.h>
#include <features.h>

#if defined(__cplusplus) && defined(__CC__)
#include <__stdcxx.h>

#include <hybrid/__atomic.h>

#include <kos/anno.h>

#if defined(__COMPILER_HAVE_TYPEOF) && 0
#define __PRIVATE_REFCNT_TYPE(T, field)       __typeof__(((T *)0)->field)
#define __PRIVATE_REFCNT_TYPE_EX(T, getfield) __typeof__(getfield((T *)0))
#elif defined(__COMPILER_HAVE_CXX_DECLTYPE)
#define __PRIVATE_REFCNT_TYPE(T, field)       decltype(((T *)0)->field)
#define __PRIVATE_REFCNT_TYPE_EX(T, getfield) decltype(getfield((T *)0))
#else /* __COMPILER_HAVE_CXX_DECLTYPE */
#include <hybrid/typecore.h>
#define __PRIVATE_REFCNT_TYPE(T, field)       __UINTPTR_TYPE__
#define __PRIVATE_REFCNT_TYPE_EX(T, getfield) __UINTPTR_TYPE__
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

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
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
#define __DEFINE_REFCNT_FUNCTIONS(T, field, destroy_)                                                                                               \
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
#define __DEFINE_REFCNT_FUNCTIONS_EX(T, getfield, destroy_)                                                                                               \
	extern "C++" {                                                                                                                                        \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                                                                       \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __PRIVATE_REFCNT_TYPE_EX(T, getfield) __REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(T const *__restrict self); \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC isshared)(T const *__restrict self);                                 \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC wasdestroyed)(T const *__restrict self);                             \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryincref)(T *__restrict self);                                      \
	__NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC xincref)(T *__restrict self);                                                                               \
	__NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *__REFCNT_NOTHROW(__REFCNT_CC incref)(T *__restrict self);                                          \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC destroy)(T *__restrict self);                                                         \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref)(T *__restrict self);                                                          \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_nokill)(T *__restrict self);                                                   \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_likely)(T *__restrict self);                                                   \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC decref_unlikely)(T *__restrict self);                                                 \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref)(T *self);                                                                                        \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_nokill)(T *self);                                                                                 \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_likely)(T *self);                                                                                 \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xdecref_unlikely)(T *self);                                                                               \
	}
#define __DEFINE_WEAKREFCNT_FUNCTIONS(T, field, destroy_)                                                                                               \
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
#define __DEFINE_WEAKREFCNT_FUNCTIONS_EX(T, getfield, destroy_)                                                                                               \
	extern "C++" {                                                                                                                                            \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                                                                                       \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __PRIVATE_REFCNT_TYPE_EX(T, getfield) __REFCNT_NOTHROW(__REFCNT_CC getweakrefcnt)(T const *__restrict self); \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC isweakshared)(T const *__restrict self);                                 \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC wasweakdestroyed)(T const *__restrict self);                             \
	__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL __REFCNT_NOTHROW(__REFCNT_CC tryweakincref)(T *__restrict self);                                      \
	__NOBLOCK T *__REFCNT_NOTHROW(__REFCNT_CC xweakincref)(T *__restrict self);                                                                               \
	__NOBLOCK __ATTR_RETNONNULL __ATTR_NONNULL((1)) T *__REFCNT_NOTHROW(__REFCNT_CC weakincref)(T *__restrict self);                                          \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdestroy)(T *__restrict self);                                                         \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref)(T *__restrict self);                                                          \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_nokill)(T *__restrict self);                                                   \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_likely)(T *__restrict self);                                                   \
	__NOBLOCK __ATTR_NONNULL((1)) void __REFCNT_NOTHROW(__REFCNT_CC weakdecref_unlikely)(T *__restrict self);                                                 \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref)(T *self);                                                                                        \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_nokill)(T *self);                                                                                 \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_likely)(T *self);                                                                                 \
	__NOBLOCK void __REFCNT_NOTHROW(__REFCNT_CC xweakdecref_unlikely)(T *self);                                                                               \
	}
#endif /* __INTELLISENSE__ */
#else /* __USE_KOS || __USE_KOS_KERNEL */
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
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */


#ifndef __DEFINE_REFCNT_FUNCTIONS
#ifdef NDEBUG
#define __DEFINE_REFCNT_FUNCTIONS(T, field, destroy_)                                                \
	extern "C++" {                                                                                   \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                  \
	template<> class refcnt_methods< T > {                                                           \
	public:                                                                                          \
		typedef __PRIVATE_REFCNT_TYPE(T, field) __PRIVATE_REFCNT_NAME(refcnt_t);                     \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                   \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) { \
			return __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                            \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {          \
			__hybrid_atomic_fetchinc(__self->field, __ATOMIC_SEQ_CST);                               \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {       \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                            \
			do {                                                                                     \
				__old_refcnt = __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                \
				if unlikely(__old_refcnt == 0)                                                       \
					return false;                                                                    \
			} while (!__hybrid_atomic_cmpxch_weak(__self->field, __old_refcnt, __old_refcnt + 1,     \
			                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));              \
			return true;                                                                             \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {          \
			if (__hybrid_atomic_decfetch(__self->field, __ATOMIC_SEQ_CST) == 0)                      \
				destroy_(__self);                                                                    \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {         \
			destroy_(__self);                                                                        \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {   \
			__hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST);                               \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {   \
			if __likely(__hybrid_atomic_decfetch(__self->field, __ATOMIC_SEQ_CST) == 0)              \
				destroy_(__self);                                                                    \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) { \
			if __unlikely(__hybrid_atomic_decfetch(__self->field, __ATOMIC_SEQ_CST) == 0)            \
				destroy_(__self);                                                                    \
		}                                                                                            \
	};                                                                                               \
	}
#define __DEFINE_REFCNT_FUNCTIONS_EX(T, getfield, destroy_)                                          \
	extern "C++" {                                                                                   \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                  \
	template<> class refcnt_methods< T > {                                                           \
	public:                                                                                          \
		typedef __PRIVATE_REFCNT_TYPE_EX(T, getfield) __PRIVATE_REFCNT_NAME(refcnt_t);               \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                   \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) { \
			return __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);                         \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {          \
			__hybrid_atomic_fetchinc(getfield(__self), __ATOMIC_SEQ_CST);                            \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {       \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                            \
			do {                                                                                     \
				__old_refcnt = __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);             \
				if unlikely(__old_refcnt == 0)                                                       \
					return false;                                                                    \
			} while (!__hybrid_atomic_cmpxch_weak(getfield(__self), __old_refcnt, __old_refcnt + 1,  \
			                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));              \
			return true;                                                                             \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {          \
			if (__hybrid_atomic_decfetch(getfield(__self), __ATOMIC_SEQ_CST) == 0)                   \
				destroy_(__self);                                                                    \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {         \
			destroy_(__self);                                                                        \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {   \
			__hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST);                            \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {   \
			if __likely(__hybrid_atomic_decfetch(getfield(__self), __ATOMIC_SEQ_CST) == 0)           \
				destroy_(__self);                                                                    \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) { \
			if __unlikely(__hybrid_atomic_decfetch(getfield(__self), __ATOMIC_SEQ_CST) == 0)         \
				destroy_(__self);                                                                    \
		}                                                                                            \
	};                                                                                               \
	}
#define __DEFINE_WEAKREFCNT_FUNCTIONS(T, field, destroy_)                                            \
	extern "C++" {                                                                                   \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                              \
	template<> class weakrefcnt_methods< T > {                                                       \
	public:                                                                                          \
		typedef __PRIVATE_REFCNT_TYPE(T, field) __PRIVATE_REFCNT_NAME(refcnt_t);                     \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                   \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) { \
			return __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                            \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {          \
			__hybrid_atomic_fetchinc(__self->field, __ATOMIC_SEQ_CST);                               \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {       \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                            \
			do {                                                                                     \
				__old_refcnt = __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                \
				if unlikely(__old_refcnt == 0)                                                       \
					return false;                                                                    \
			} while (!__hybrid_atomic_cmpxch_weak(__self->field, __old_refcnt,__old_refcnt + 1,      \
			                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));              \
			return true;                                                                             \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {          \
			if (__hybrid_atomic_decfetch(__self->field, __ATOMIC_SEQ_CST) == 0)                      \
				destroy_(__self);                                                                    \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {         \
			destroy_(__self);                                                                        \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {   \
			__hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST);                               \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {   \
			if __likely(__hybrid_atomic_decfetch(__self->field, __ATOMIC_SEQ_CST) == 0)              \
				destroy_(__self);                                                                    \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) { \
			if __unlikely(__hybrid_atomic_decfetch(__self->field, __ATOMIC_SEQ_CST) == 0)            \
				destroy_(__self);                                                                    \
		}                                                                                            \
	};                                                                                               \
	}
#define __DEFINE_WEAKREFCNT_FUNCTIONS_EX(T, getfield, destroy_)                                      \
	extern "C++" {                                                                                   \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                              \
	template<> class weakrefcnt_methods< T > {                                                       \
	public:                                                                                          \
		typedef __PRIVATE_REFCNT_TYPE_EX(T, getfield) __PRIVATE_REFCNT_NAME(refcnt_t);               \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                   \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) { \
			return __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);                         \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {          \
			__hybrid_atomic_fetchinc(getfield(__self), __ATOMIC_SEQ_CST);                            \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL              \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {       \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                            \
			do {                                                                                     \
				__old_refcnt = __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);             \
				if unlikely(__old_refcnt == 0)                                                       \
					return false;                                                                    \
			} while (!__hybrid_atomic_cmpxch_weak(getfield(__self), __old_refcnt,__old_refcnt + 1,   \
			                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));              \
			return true;                                                                             \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {          \
			if (__hybrid_atomic_decfetch(getfield(__self), __ATOMIC_SEQ_CST) == 0)                   \
				destroy_(__self);                                                                    \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {         \
			destroy_(__self);                                                                        \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {   \
			__hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST);                            \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {   \
			if __likely(__hybrid_atomic_decfetch(getfield(__self), __ATOMIC_SEQ_CST) == 0)           \
				destroy_(__self);                                                                    \
		}                                                                                            \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) { \
			if __unlikely(__hybrid_atomic_decfetch(getfield(__self), __ATOMIC_SEQ_CST) == 0)         \
				destroy_(__self);                                                                    \
		}                                                                                            \
	};                                                                                               \
	}
#else /* NDEBUG */
} /* extern "C++" */
#include <hybrid/__assert.h>
extern "C++" {

#define __DEFINE_REFCNT_FUNCTIONS(T, field, destroy_)                                                                 \
	extern "C++" {                                                                                                    \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                                   \
	template<> class __PRIVATE_REFCNT_NAME(refcnt_methods)< T > {                                                     \
	public:                                                                                                           \
		typedef __PRIVATE_REFCNT_TYPE(T, field) __PRIVATE_REFCNT_NAME(refcnt_t);                                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                                    \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                                     \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {                  \
			return __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                                             \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                           \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchinc(__self->field, __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "incref(%p): Object was already destroyed", __self);                   \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                               \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                        \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                                             \
			do {                                                                                                      \
				__old_refcnt = __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                                 \
				if unlikely(__old_refcnt == 0)                                                                        \
					return false;                                                                                     \
			} while (!__hybrid_atomic_cmpxch_weak(__self->field, __old_refcnt, __old_refcnt + 1,                      \
			                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));                               \
			return true;                                                                                              \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                           \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                                             \
			__old_refcnt = __hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST);                                 \
			__hybrid_assertf(__old_refcnt > 0, "decref(%p): Object was already destroyed", __self);                   \
			if (__old_refcnt == 1)                                                                                    \
				destroy_(__self);                                                                                     \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                          \
			__hybrid_atomic_store(__self->field, (__PRIVATE_REFCNT_NAME(refcnt_t))0, __ATOMIC_RELEASE);               \
			destroy_(__self);                                                                                         \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                    \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "decref_nokill(%p): Object was already destroyed", __self);            \
			__hybrid_assertf(__old_refcnt > 1, "decref_nokill(%p): Object should have been destroyed", __self);       \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                    \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "decref_likely(%p): Object was already destroyed", __self);            \
			if __likely(__old_refcnt == 1)                                                                            \
				destroy_(__self);                                                                                     \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                  \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "decref_unlikely(%p): Object was already destroyed", __self);          \
			if __unlikely(__old_refcnt == 1)                                                                          \
				destroy_(__self);                                                                                     \
		}                                                                                                             \
	};                                                                                                                \
	}
#define __DEFINE_REFCNT_FUNCTIONS_EX(T, getfield, destroy_)                                                              \
	extern "C++" {                                                                                                       \
	T operator,(T const&, __NAMESPACE_INT_SYM __refcnt_select_tag);                                                      \
	template<> class __PRIVATE_REFCNT_NAME(refcnt_methods)< T > {                                                        \
	public:                                                                                                              \
		typedef __PRIVATE_REFCNT_TYPE_EX(T, getfield) __PRIVATE_REFCNT_NAME(refcnt_t);                                   \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                                       \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                                        \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {                     \
			return __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);                                             \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                              \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchinc(getfield(__self), __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "incref(%p): Object was already destroyed", __self);                      \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                  \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                           \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                                                \
			do {                                                                                                         \
				__old_refcnt = __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);                                 \
				if unlikely(__old_refcnt == 0)                                                                           \
					return false;                                                                                        \
			} while (!__hybrid_atomic_cmpxch_weak(getfield(__self), __old_refcnt, __old_refcnt + 1,                      \
			                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));                                  \
			return true;                                                                                                 \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                              \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                                                \
			__old_refcnt = __hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST);                                 \
			__hybrid_assertf(__old_refcnt > 0, "decref(%p): Object was already destroyed", __self);                      \
			if (__old_refcnt == 1)                                                                                       \
				destroy_(__self);                                                                                        \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                             \
			__hybrid_atomic_store(getfield(__self), (__PRIVATE_REFCNT_NAME(refcnt_t))0, __ATOMIC_RELEASE);               \
			destroy_(__self);                                                                                            \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                       \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "decref_nokill(%p): Object was already destroyed", __self);               \
			__hybrid_assertf(__old_refcnt > 1, "decref_nokill(%p): Object should have been destroyed", __self);          \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                       \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "decref_likely(%p): Object was already destroyed", __self);               \
			if __likely(__old_refcnt == 1)                                                                               \
				destroy_(__self);                                                                                        \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                     \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "decref_unlikely(%p): Object was already destroyed", __self);             \
			if __unlikely(__old_refcnt == 1)                                                                             \
				destroy_(__self);                                                                                        \
		}                                                                                                                \
	};                                                                                                                   \
	}
#define __DEFINE_WEAKREFCNT_FUNCTIONS(T, field, destroy_)                                                             \
	extern "C++" {                                                                                                    \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                                               \
	template<> class weakrefcnt_methods< T > {                                                                        \
	public:                                                                                                           \
		typedef __PRIVATE_REFCNT_TYPE(T, field) __PRIVATE_REFCNT_NAME(refcnt_t);                                      \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                                    \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                                     \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {                  \
			return __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                                             \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                           \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchinc(__self->field, __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "weakincref(%p): Object was already destroyed", __self);               \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                               \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                        \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                                             \
			do {                                                                                                      \
				__old_refcnt = __hybrid_atomic_load(__self->field, __ATOMIC_ACQUIRE);                                 \
				if unlikely(__old_refcnt == 0)                                                                        \
					return false;                                                                                     \
			} while (!__hybrid_atomic_cmpxch_weak(__self->field, __old_refcnt,__old_refcnt + 1,                       \
			                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));                               \
			return true;                                                                                              \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                           \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                                             \
			__old_refcnt = __hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST);                                 \
			__hybrid_assertf(__old_refcnt > 0, "weakdecref(%p): Object was already destroyed", __self);               \
			if (__old_refcnt == 1)                                                                                    \
				destroy_(__self);                                                                                     \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                          \
			__hybrid_atomic_store(__self->field, (__PRIVATE_REFCNT_NAME(refcnt_t))0, __ATOMIC_RELEASE);               \
			destroy_(__self);                                                                                         \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                    \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "weakdecref_nokill(%p): Object was already destroyed", __self);        \
			__hybrid_assertf(__old_refcnt > 1, "weakdecref_nokill(%p): Object should have been destroyed", __self);   \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                    \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "weakdecref_likely(%p): Object was already destroyed", __self);        \
			if __likely(__old_refcnt == 1)                                                                            \
				destroy_(__self);                                                                                     \
		}                                                                                                             \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                 \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                  \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(__self->field, __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "weakdecref_unlikely(%p): Object was already destroyed", __self);      \
			if __unlikely(__old_refcnt == 1)                                                                          \
				destroy_(__self);                                                                                     \
		}                                                                                                             \
	};                                                                                                                \
	}
#define __DEFINE_WEAKREFCNT_FUNCTIONS_EX(T, getfield, destroy_)                                                          \
	extern "C++" {                                                                                                       \
	T operator,(T const&, __NAMESPACE_INT_SYM __weakrefcnt_select_tag);                                                  \
	template<> class weakrefcnt_methods< T > {                                                                           \
	public:                                                                                                              \
		typedef __PRIVATE_REFCNT_TYPE_EX(T, getfield) __PRIVATE_REFCNT_NAME(refcnt_t);                                   \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL                                                                       \
		__NOBLOCK __ATTR_PURE __ATTR_NONNULL((1)) __PRIVATE_REFCNT_NAME(refcnt_t)                                        \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(getrefcnt))(T const *__restrict __self) {                     \
			return __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);                                             \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(incref))(T *__restrict __self) {                              \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchinc(getfield(__self), __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "weakincref(%p): Object was already destroyed", __self);                  \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) __BOOL                                  \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(tryincref))(T *__restrict __self) {                           \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                                                \
			do {                                                                                                         \
				__old_refcnt = __hybrid_atomic_load(getfield(__self), __ATOMIC_ACQUIRE);                                 \
				if unlikely(__old_refcnt == 0)                                                                           \
					return false;                                                                                        \
			} while (!__hybrid_atomic_cmpxch_weak(getfield(__self), __old_refcnt,__old_refcnt + 1,                       \
			                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));                                  \
			return true;                                                                                                 \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref))(T *__restrict __self) {                              \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt;                                                                \
			__old_refcnt = __hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST);                                 \
			__hybrid_assertf(__old_refcnt > 0, "weakdecref(%p): Object was already destroyed", __self);                  \
			if (__old_refcnt == 1)                                                                                       \
				destroy_(__self);                                                                                        \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(destroy))(T *__restrict __self) {                             \
			__hybrid_atomic_store(getfield(__self), (__PRIVATE_REFCNT_NAME(refcnt_t))0, __ATOMIC_RELEASE);               \
			destroy_(__self);                                                                                            \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_nokill))(T *__restrict __self) {                       \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "weakdecref_nokill(%p): Object was already destroyed", __self);           \
			__hybrid_assertf(__old_refcnt > 1, "weakdecref_nokill(%p): Object should have been destroyed", __self);      \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_likely))(T *__restrict __self) {                       \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "weakdecref_likely(%p): Object was already destroyed", __self);           \
			if __likely(__old_refcnt == 1)                                                                               \
				destroy_(__self);                                                                                        \
		}                                                                                                                \
		static __CXX_FORCEINLINE __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void                                    \
		__REFCNT_NOTHROW(__REFCNT_CC __PRIVATE_REFCNT_NAME(decref_unlikely))(T *__restrict __self) {                     \
			__PRIVATE_REFCNT_NAME(refcnt_t) __old_refcnt = __hybrid_atomic_fetchdec(getfield(__self), __ATOMIC_SEQ_CST); \
			__hybrid_assertf(__old_refcnt > 0, "weakdecref_unlikely(%p): Object was already destroyed", __self);         \
			if __unlikely(__old_refcnt == 1)                                                                             \
				destroy_(__self);                                                                                        \
		}                                                                                                                \
	};                                                                                                                   \
	}
#endif /* !NDEBUG */
#endif /* !__DEFINE_REFCNT_FUNCTIONS */


#if !defined(__INTELLISENSE__) || (!defined(__USE_KOS) && !defined(__USE_KOS_KERNEL))
template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1))
typename __REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(refcnt_t)
__REFCNT_NOTHROW(__REFCNT_CC getrefcnt)(__T const *__restrict __self) {
	return (__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __BOOL
__REFCNT_NOTHROW(__REFCNT_CC isshared)(__T const *__restrict __self) {
	return (__REFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self) > 1;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __BOOL
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
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1))
typename __WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(refcnt_t)
__REFCNT_NOTHROW(__REFCNT_CC getweakrefcnt)(__T const *__restrict __self) {
	return (__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self);
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __BOOL
__REFCNT_NOTHROW(__REFCNT_CC isweakshared)(__T const *__restrict __self) {
	return (__WEAKREFCNT_METHODS(__T)::__PRIVATE_REFCNT_NAME(getrefcnt))(__self) > 1;
}

template<class __T>
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __BOOL
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

#define __DEFINE_REFCNT_FUNCTIONS(T, field, destroy_)           /* nothing */
#define __DEFINE_REFCNT_FUNCTIONS_EX(T, getfield, destroy_)     /* nothing */
#define __DEFINE_WEAKREFCNT_FUNCTIONS(T, field, destroy_)       /* nothing */
#define __DEFINE_WEAKREFCNT_FUNCTIONS_EX(T, getfield, destroy_) /* nothing */

#endif /* !__cplusplus || !__CC__ */


#endif /* !_KOS_REFCNT_H */
