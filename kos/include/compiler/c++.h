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
#ifdef __NO_PROTOTYPES
#undef __NO_PROTOTYPES
#undef __P
#define __P(x) x
#endif /* __NO_PROTOTYPES */

/* TODO: Support for `#define ATTR_WUNUSED [[nodiscard]]' */

#ifndef __has_feature
#define __NO_has_feature 1
#define __has_feature(x) 0
#endif /* !__has_feature */
#ifndef __has_extension
#ifndef __NO_has_feature
#define __NO_has_extension 1
#endif /* !__NO_has_feature */
#define __has_extension  __has_feature
#endif /* !__has_extension */

#define __DECL_BEGIN extern "C" {
#define __DECL_END   }

#define __CXX11_EXPLICIT_OPERATOR explicit

// #define __COMPILER_HAVE_HAS_UNIQUE_OBJECT_REPRESENTATIONS 1 /* `bool __has_unique_object_representations(typename T)' */
// #define __COMPILER_HAVE_IS_AGGREGATE 1 /* `bool __is_aggregate(typename T)' */


#if (__has_feature(cxx_constexpr) ||                                                                      \
     (defined(__cpp_constexpr) && __cpp_constexpr >= 200704) ||                                           \
     (defined(__IBMCPP__) && defined(__IBMCPP_CONSTEXPR) && (__IBMCPP_CONSTEXPR + 0)) ||                  \
     (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5130) ||                                                   \
     (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GCC_VERSION_NUM >= 40600 && !defined(__INTELLISENSE__)) || \
     (defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190023026))
#ifdef _MSC_VER
/* Some stupid warning about adding `const' even though
 * we  already  differentiate  with  C++14   constexpr. */
#pragma warning(disable: 4814)
#endif /* _MSC_VER */
#define __COMPILER_HAVE_CXX11_CONSTEXPR
#define __CXX11_CONSTEXPR          constexpr
#define __CXX11_CONSTEXPR_OR_CONST constexpr
#else /* ... */
#define __CXX11_CONSTEXPR          /* Nothing */
#define __CXX11_CONSTEXPR_OR_CONST const
#endif /* !... */

#if ((defined(__clang__) && !(!__has_feature(cxx_generic_lambdas) ||         \
                              !(__has_feature(cxx_relaxed_constexpr) ||      \
                                __has_extension(cxx_relaxed_constexpr)))) || \
     (defined(__cpp_constexpr) && __cpp_constexpr >= 201304 && !defined(__clang__)))
#define __COMPILER_HAVE_CXX14_CONSTEXPR
#define __CXX14_CONSTEXPR          constexpr
#define __CXX14_CONSTEXPR_OR_CONST constexpr
#else /* ... */
#define __CXX14_CONSTEXPR          /* Nothing */
#define __CXX14_CONSTEXPR_OR_CONST const
#endif /* !... */


#if 0
#define __COMPILER_HAVE_CXX17_CONSTEXPR
#define __CXX17_CONSTEXPR          constexpr
#define __CXX17_CONSTEXPR_OR_CONST constexpr
#else /* ... */
#define __CXX17_CONSTEXPR          /* Nothing */
#define __CXX17_CONSTEXPR_OR_CONST const
#endif /* !... */

#if (__has_feature(cxx_noexcept) ||                                                                       \
     (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GCC_VERSION_NUM >= 40600 && !defined(__INTELLISENSE__)) || \
     (defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190021730))
#define __COMPILER_HAVE_CXX11_NOEXCEPT
#define __CXX_NOEXCEPT            noexcept
#define __CXX_NOEXCEPT_IF(expr)   noexcept(expr)
#define __CXX_NOEXCEPT_IS(expr)   noexcept(expr)
#define __CXX_NOEXCEPT_IFNX(expr) noexcept(noexcept(expr))
#else /* ... */
#define __CXX_NOEXCEPT            throw()
#define __CXX_NOEXCEPT_IF(expr)   /* Nothing */
#define __CXX_NOEXCEPT_IS(expr)   0
#define __CXX_NOEXCEPT_IFNX(expr) /* Nothing */
#endif /* !... */

#if (__has_feature(cxx_override_control) || \
     (defined(_MSC_VER) && _MSC_VER >= 1600) || \
     (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GCC_VERSION_NUM >= 40700))
#define __COMPILER_HAVE_CXX11_OVERRIDE
#define __CXX_OVERRIDE override
#else /* ... */
#define __CXX_OVERRIDE /* Nothing */
#endif /* !... */

#if !defined(__KOS__) || !defined(__KERNEL__)
#define __COMPILER_PREFERR_ENUMS
#endif /* !__KOS__ || !__KERNEL__ */

#ifndef __ELF__
#define __CXX_CLASSMEMBER        inline
#define __CXX_INLINE_CLASSMEMBER __ATTR_FORCEINLINE
#elif defined(__NO_ATTR_VISIBILITY)
#define __CXX_CLASSMEMBER        __ATTR_FORCEINLINE
#define __CXX_INLINE_CLASSMEMBER __ATTR_FORCEINLINE
#else /* ... */
#define __CXX_CLASSMEMBER        inline __ATTR_VISIBILITY("hidden")
#define __CXX_INLINE_CLASSMEMBER __ATTR_FORCEINLINE __ATTR_VISIBILITY("hidden")
#endif /* !... */


#ifndef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTELLISENSE__)
/* Enable work-arounds for c++'s `using' causing debug information bloat:
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=96417 */
#define __COMPILER_HAVE_BUG_BLOATY_CXX_USING 1
#else /* __GNUC__ && !__clang__ && !__INTELLISENSE__ */
#undef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
#endif /* !__GNUC__ || __clang__ || __INTELLISENSE__ */
#elif (__COMPILER_HAVE_BUG_BLOATY_CXX_USING + 0) == 0
#undef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING */

#ifdef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
#define __CXX_USING_TYPE(ns, x) typedef ns x x;
#else /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING */
#define __CXX_USING_TYPE(ns, x) using ns x;
#endif /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING */

#define __NAMESPACE_GLB_SYM ::
#ifdef __NO_NAMESPACE_STD
#define __NAMESPACE_STD_BEGIN               /* Nothing */
#define __NAMESPACE_STD_END                 /* Nothing */
#define __NAMESPACE_STD_SYM                 /* Nothing */
#define __NAMESPACE_STD_USING(x)            /* Nothing */
#define __NAMESPACE_GLB_USING(x)            /* Nothing */
#define __NAMESPACE_GLB_USING_OR_IMPL(x, i) /* Nothing */
#define __NAMESPACE_GLB_USING_TYPE(x)       /* Nothing */
#else /* __NO_NAMESPACE_STD */
#define __NAMESPACE_STD_BEGIN               namespace std {
#define __NAMESPACE_STD_END                 }
#define __NAMESPACE_STD_SYM                 ::std::
#ifdef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
namespace std { }
using namespace std; /* Overlay */
#define __NAMESPACE_STD_USING(x)            /* nothing (already done by the overlay) */
#define __NAMESPACE_GLB_USING(x)            using ::x;
#define __NAMESPACE_GLB_USING_TYPE(x)       __CXX_USING_TYPE(::, x)
#define __NAMESPACE_GLB_USING_OR_IMPL(x, i) extern "C" { i }
#else /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING */
#define __NAMESPACE_STD_USING(x)            using ::std::x;
#define __NAMESPACE_GLB_USING(x)            using ::x;
#define __NAMESPACE_GLB_USING_TYPE(x)       using ::x;
#define __NAMESPACE_GLB_USING_OR_IMPL(x, i) using ::x;
#endif /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING */
#endif /* !__NO_NAMESPACE_STD */


#define __NAMESPACE_INT_BEGIN namespace __intern {
#define __NAMESPACE_INT_END   }
#define __NAMESPACE_INT_SYM   ::__intern::
#define __NAMESPACE_INT_LSYM  __intern::
#define __BOOL                bool
#define __DFL(expr)           = expr

#ifndef __register
#ifdef __INTELLISENSE__
#define __register /* Nothing */
#elif defined(__cplusplus) && __cplusplus >= 201703L
#define __register /* nothing (warning : ISO C++17 does not allow 'register' storage class specifier [-Wregister]) */
#else /* ... */
#define __register register
#endif /* !... */
#endif /* !__register */

#ifdef __INTELLISENSE__
__NAMESPACE_INT_BEGIN
extern "C++" {
template<class __T> __T ____intellisense_requires_type(__T v);
}
__NAMESPACE_INT_END
#define __COMPILER_REQTYPE(T, v) (__NAMESPACE_INT_SYM ____intellisense_requires_type< T >(v))
#else /* __INTELLISENSE__ */
#define __COMPILER_REQTYPE(T, v) (v)
#endif /* !__INTELLISENSE__ */
