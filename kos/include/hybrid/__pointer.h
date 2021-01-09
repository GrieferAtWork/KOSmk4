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
#ifndef __GUARD_HYBRID___POINTER_H
#define __GUARD_HYBRID___POINTER_H 1

#include "../__stdinc.h"

#if defined(_MSC_VER) && !defined(__clang__)
/* MSVC already has this kind of functionality built into the compiler. */
#define __HYBRID_FUNCPTR32(return, cc, name, args) return (CC * __ptr32 name)args
#define __HYBRID_FUNCPTR64(return, cc, name, args) return (CC * __ptr64 name)args
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __HYBRID_PTR32(...) __VA_ARGS__ *__ptr32
#define __HYBRID_PTR64(...) __VA_ARGS__ *__ptr64
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_PTR32(T) T *__ptr32
#define __HYBRID_PTR64(T) T *__ptr64
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_PTR32_IN_TRANSPARENT_STRUCT
#define __HYBRID_PTR64_IN_TRANSPARENT_STRUCT
#elif defined(__cplusplus)
/* Use C++ features to implement fixed-length pointer types. */

#include "typecore.h"
#include "../__stdcxx.h"

__CXXDECL_BEGIN

#undef __POINTER_CXX_CV_QUAL
#undef __POINTER_CXX_IS_VOID

#define __POINTER_CXX_CV_QUAL /* nothing */
#include "__pointer-cxx-impl.h"
#define __POINTER_CXX_CV_QUAL const
#define __POINTER_CXX_CV_QUAL_IS_CONST 1
#include "__pointer-cxx-impl.h"
#define __POINTER_CXX_CV_QUAL volatile
#define __POINTER_CXX_CV_QUAL_IS_VOLATILE 1
#include "__pointer-cxx-impl.h"
#define __POINTER_CXX_CV_QUAL const volatile
#define __POINTER_CXX_CV_QUAL_IS_CONST 1
#define __POINTER_CXX_CV_QUAL_IS_VOLATILE 1
#include "__pointer-cxx-impl.h"

#define __POINTER_CXX_IS_VOID 1
#define __POINTER_CXX_CV_QUAL /* nothing */
#include "__pointer-cxx-impl.h"

/* Implement pointer difference operators for cases where the first operand is a regular pointer */
extern "C++" {
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T, __I> const &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T, __I> const volatile &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T const, __I> const &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T const, __I> const volatile &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T volatile, __I> const &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T volatile, __I> const volatile &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T const volatile, __I> const &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T const volatile, __I> const volatile &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T const *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T, __I> const &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T const *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T, __I> const volatile &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T volatile *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T, __I> const &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T volatile *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T, __I> const volatile &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T const volatile *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T, __I> const &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
template<class __T, class __I> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__T const volatile *__lhs, __NAMESPACE_INT_SYM __hybrid_ptr<__T, __I> const volatile &__rhs) __CXX_NOEXCEPT { return __lhs - (__T *)__rhs; }
}

#if __SIZEOF_POINTER__ != 4
#ifndef __COMPILER_HAVE_TRANSPARENT_NONCLASS
#define __HYBRID_PTR32_IN_TRANSPARENT_STRUCT
#endif /* !__COMPILER_HAVE_TRANSPARENT_NONCLASS */
#define __HYBRID_FUNCPTR32(return, cc, name, args) __HYBRID_PTR32(return (cc *)args) name
#ifdef __COMPILER_HAVE_CXX_TEMPLATE_USING
/* Try to use `template using' in order to prevent `__HYBRID_PTR32()' from containing
 * any comma tokens that might otherwise interfere with expansion when `__HYBRID_PTR32()'
 * is passed as an argument to another macro. */
__NAMESPACE_INT_BEGIN
template<class __T> using __hybrid_ptr32 = __hybrid_ptr<__T, __ULONG32_TYPE__>;
__NAMESPACE_INT_END
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __HYBRID_PTR32(...) __NAMESPACE_INT_SYM __hybrid_ptr32< __VA_ARGS__ >
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_PTR32(T) __NAMESPACE_INT_SYM __hybrid_ptr32< T >
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#else /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __HYBRID_PTR32(...) __NAMESPACE_INT_SYM __hybrid_ptr< __VA_ARGS__, __ULONG32_TYPE__>
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_PTR32(T) __NAMESPACE_INT_SYM __hybrid_ptr< T, __ULONG32_TYPE__>
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#endif /* !__COMPILER_HAVE_CXX_TEMPLATE_USING */
#else /* __SIZEOF_POINTER__ != 4 */
#define __HYBRID_PTR32_IN_TRANSPARENT_STRUCT
#define __HYBRID_FUNCPTR32(return, cc, name, args) return (cc *name)args
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __HYBRID_PTR32(...) __VA_ARGS__ *
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_PTR32(T) T *
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#endif /* __SIZEOF_POINTER__ == 4 */

#if __SIZEOF_POINTER__ != 8
#ifndef __COMPILER_HAVE_TRANSPARENT_NONCLASS
#define __HYBRID_PTR64_IN_TRANSPARENT_STRUCT
#endif /* !__COMPILER_HAVE_TRANSPARENT_NONCLASS */
#define __HYBRID_FUNCPTR64(return, cc, name, args) __HYBRID_PTR64(return (cc *)args) name
#ifdef __COMPILER_HAVE_CXX_TEMPLATE_USING
/* Try to use `template using' in order to prevent `__HYBRID_PTR64()' from containing
 * any comma tokens that might otherwise interfere with expansion when `__HYBRID_PTR64()'
 * is passed as an argument to another macro. */
__NAMESPACE_INT_BEGIN
template<class __T> using __hybrid_ptr64 = __hybrid_ptr<__T, __ULONG64_TYPE__>;
__NAMESPACE_INT_END
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __HYBRID_PTR64(...) __NAMESPACE_INT_SYM __hybrid_ptr64< __VA_ARGS__ >
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_PTR64(T) __NAMESPACE_INT_SYM __hybrid_ptr64< T >
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#else /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __HYBRID_PTR64(...) __NAMESPACE_INT_SYM __hybrid_ptr< __VA_ARGS__, __ULONG64_TYPE__>
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_PTR64(T) __NAMESPACE_INT_SYM __hybrid_ptr< T, __ULONG64_TYPE__>
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#endif /* !__COMPILER_HAVE_CXX_TEMPLATE_USING */
#else /* __SIZEOF_POINTER__ != 8 */
#define __HYBRID_PTR64_IN_TRANSPARENT_STRUCT
#define __HYBRID_FUNCPTR64(return, cc, name, args) return (cc *name)args
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __HYBRID_PTR64(...) __VA_ARGS__ *
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __HYBRID_PTR64(T) T *
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#endif /* __SIZEOF_POINTER__ == 8 */

__CXXDECL_END
#else /* ... */

/* Fallback: Just replace references to fixed-length pointers with
 *           lengths that don't match the host's with integer types
 *           of proper width. */
#include "typecore.h"

#define __HYBRID_PTR32_IN_TRANSPARENT_STRUCT
#define __HYBRID_PTR64_IN_TRANSPARENT_STRUCT
#if __SIZEOF_POINTER__ == 4
#define __HYBRID_FUNCPTR32(return, cc, name, args) return (cc *name)args
#define __HYBRID_FUNCPTR64(return, cc, name, args) __ULONG64_TYPE__ name
#define __HYBRID_PTR32(T) T *
#define __HYBRID_PTR64(T) __ULONG64_TYPE__
#elif __SIZEOF_POINTER__ == 8
#define __HYBRID_FUNCPTR32(return, cc, name, args) __ULONG32_TYPE__ name
#define __HYBRID_FUNCPTR64(return, cc, name, args) return (cc *name)args
#define __HYBRID_PTR32(T) __ULONG32_TYPE__
#define __HYBRID_PTR64(T) T *
#else /* __SIZEOF_POINTER__ == ... */
#define __HYBRID_FUNCPTR32(return, cc, name, args) __ULONG32_TYPE__ name
#define __HYBRID_FUNCPTR64(return, cc, name, args) __ULONG64_TYPE__ name
#define __HYBRID_PTR32(T) __ULONG32_TYPE__
#define __HYBRID_PTR64(T) __ULONG64_TYPE__
#endif /* __SIZEOF_POINTER__ != ... */

#endif /* !... */


#endif /* !__GUARD_HYBRID___POINTER_H */
