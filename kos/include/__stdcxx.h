/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef ___STDCXX_H
#define ___STDCXX_H 1

#include "__stdinc.h"

#ifndef __cplusplus
#error "A C++ compiler is required"
#endif /* !__cplusplus */

#ifndef __GCC_VERSION
#ifdef __GNUC__
#ifndef __GNUC_MINOR__
#define __GNUC_MINOR__ 0
#endif /* !__GNUC_MINOR__ */
#ifndef __GNUC_PATCH__
#ifdef __GNUC_PATCHLEVEL__
#define __GNUC_PATCH__ __GNUC_PATCHLEVEL__
#else /* __GNUC_PATCHLEVEL__ */
#define __GNUC_PATCH__ 0
#endif /* !__GNUC_PATCHLEVEL__ */
#endif /* !__GNUC_PATCH__ */
#ifndef __GCC_VERSION_NUM
#define __GCC_VERSION_NUM (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCH__)
#endif /* !__GCC_VERSION_NUM */
#define __GCC_VERSION(a, b, c) (__GCC_VERSION_NUM >= ((a)*10000 + (b)*100 + (c)))
#else /* __GNUC__ */
#define __GCC_VERSION(a, b, c) 0
#endif /* !__GNUC__ */
#endif /* !__GCC_VERSION */


//#define __COMPILER_HAVE_CXX_TEMPLATE_CONSTEXPR 1
#define __COMPILER_HAVE_CXX_PARTIAL_TPL_SPEC 1
#define __CXX_DEDUCE_TYPENAME typename

#if __has_feature(cxx_variadic_templates) || \
   (defined(__cpp_variadic_templates) && __cpp_variadic_templates >= 200704) || \
   (__GCC_VERSION(4, 3, 0) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)) || \
   (defined(_MSC_VER) && _MSC_VER >= 1800) || \
   (defined(__IBMCPP_VARIADIC_TEMPLATES) && __IBMCPP_VARIADIC_TEMPLATES)
#define __COMPILER_HAVE_CXX_VARIABLE_TEMPLATES 1
#endif /* ... */

#if __has_feature(cxx_alias_templates) || \
   (defined(__cpp_alias_templates) && __cpp_alias_templates >= 200704) || \
   (defined(__BORLANDC__) && __BORLANDC__ > 0x613) || \
   (defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 180020827)
#define __COMPILER_HAVE_CXX_TEMPLATE_USING 1
#endif /* ... */

#if __has_feature(cxx_rvalue_references) || \
   (defined(__cpp_rvalue_references) && __cpp_rvalue_references >= 200610) || \
   (defined(_MSC_VER) && _MSC_VER >= 1600) || \
   (__GCC_VERSION(4, 3, 0) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)) || \
   (defined(__BORLANDC__) && defined(__CODEGEAR_0X_SUPPORT__) && __BORLANDC__ >= 0x610) || \
   (defined(__IBMCPP_RVALUE_REFERENCES) && (__IBMCPP_RVALUE_REFERENCES+0))
#define __COMPILER_HAVE_CXX_RVALUE_REFERENCE 1
#endif /* ... */

#if __has_feature(cxx_strong_enums) || \
   (defined(_MSC_VER) && _MSC_VER >= 1700) || \
   (defined(__BORLANDC__) && defined(__CODEGEAR_0X_SUPPORT__) && __BORLANDC__ >= 0x610) ||\
   (__GCC_VERSION(4, 5, 1) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)) || \
   (defined(__IBMCPP_SCOPED_ENUM) && (__IBMCPP_SCOPED_ENUM+0))
#define __COMPILER_HAVE_CXX_ENUM_CLASSES 1
#endif  /* ... */

#if __has_feature(cxx_nullptr) || \
   (defined(__INTEL_VERSION__) && __INTEL_VERSION__ >= 1210) || \
   (defined(_MSC_VER) && _MSC_VER >= 1600) || \
   (__GCC_VERSION(4, 6, 0) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L))
#define __COMPILER_HAVE_CXX_NULLPTR 1
#endif /* ... */

#if __has_feature(cxx_decltype) || \
   (defined(__cpp_decltype) && __cpp_decltype >= 200707) || \
   (defined(_MSC_VER) && _MSC_VER >= 1600) || \
   (__GCC_VERSION(4, 3, 0) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)) || \
   (defined(__BORLANDC__) && defined(__CODEGEAR_0X_SUPPORT__) && __BORLANDC__ >= 0x610) || \
   (defined(__IBMCPP_DECLTYPE) && (__IBMCPP_DECLTYPE+0))
#define __COMPILER_HAVE_CXX_DECLTYPE 1
#endif /* ... */




#ifndef __CXX_FORCEINLINE
#ifndef __NO_ATTR_FORCEINLINE
#define __CXX_FORCEINLINE __ATTR_FORCEINLINE
#else /* !__NO_ATTR_FORCEINLINE */
#define __CXX_FORCEINLINE __CXX_CLASSMEMBER
#endif /* __NO_ATTR_FORCEINLINE */
#endif /* !__CXX_FORCEINLINE */

#ifndef __CXX_INLINE_CONSTEXPR
#ifdef __COMPILER_HAVE_CXX11_CONSTEXPR
#define __CXX_INLINE_CONSTEXPR __CXX11_CONSTEXPR
#elif !defined(__NO_ATTR_FORCEINLINE)
#define __CXX_INLINE_CONSTEXPR __ATTR_FORCEINLINE
#else
#define __CXX_INLINE_CONSTEXPR __CXX_CLASSMEMBER
#endif
#endif /* !__CXX_INLINE_CONSTEXPR */

#if __has_feature(defaulted_functions) || \
   (defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 180020827) || \
   (__GCC_VERSION(4, 4, 0) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L))
#define __CXX_HAVE_DEFAULT_FUNCTIONS 1
#define __CXX_DEFAULT_CTOR(T)                      T() = default
#define __CXX_DEFAULT_DTOR(T)                      ~T() = default
#define __CXX_DEFAULT_COPY(T, other, ...)          T(T const &) = default
#ifdef __COMPILER_HAVE_CXX11_NOEXCEPT
#define __CXX_DEFAULT_CTOR_NOEXCEPT(T)             T() __CXX_NOEXCEPT = default
#define __CXX_DEFAULT_DTOR_NOEXCEPT(T)             ~T() __CXX_NOEXCEPT = default
#define __CXX_DEFAULT_COPY_NOEXCEPT(T, other, ...) T(T const &) __CXX_NOEXCEPT = default
#else /* __COMPILER_HAVE_CXX11_NOEXCEPT */
#define __CXX_DEFAULT_CTOR_NOEXCEPT(T)             T() = default
#define __CXX_DEFAULT_DTOR_NOEXCEPT(T)             ~T() = default
#define __CXX_DEFAULT_COPY_NOEXCEPT(T, other, ...) T(T const &) = default
#endif /* !__COMPILER_HAVE_CXX11_NOEXCEPT */
#else
#define __CXX_DEFAULT_CTOR(T)                      T() {}
#define __CXX_DEFAULT_DTOR(T)                      ~T() {}
#define __CXX_DEFAULT_COPY(T, other, ...)          T(T const &other) __VA_ARGS__
#define __CXX_DEFAULT_CTOR_NOEXCEPT(T)             T() __CXX_NOEXCEPT {}
#define __CXX_DEFAULT_DTOR_NOEXCEPT(T)             ~T() __CXX_NOEXCEPT {}
#define __CXX_DEFAULT_COPY_NOEXCEPT(T, other, ...) T(T const &other) __CXX_NOEXCEPT __VA_ARGS__
#endif

#ifndef __CXX_STATIC_CONST
#ifdef __COMPILER_HAVE_CXX11_CONSTEXPR
#define __CXX_HAVE_STATIC_CONST 1
#define __CXX_STATIC_CONST(T,decl)   static __CXX11_CONSTEXPR T decl
#elif 1 /* XXX: What compilers support this? */
#define __CXX_HAVE_STATIC_CONST 1
#define __CXX_STATIC_CONST(T,decl)   static T const decl
#else
#define __CXX_STATIC_CONST(T,decl)   enum{decl}
#endif
#endif /* !__CXX_STATIC_CONST */


#if __has_feature(deleted_functions) || \
   (defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 180020827) || \
   (__GCC_VERSION(4, 4, 0) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L))
#define __CXX_HAVE_DELETE_FUNCTIONS 1
#define __CXX_DELETE_CTOR(T)                 T() = delete
#define __CXX_DELETE_DTOR(T)                 ~T() = delete
#define __CXX_DELETE_COPY(T)                 T(T const&) = delete
#define __CXX_DELETE_COPY_ASSIGN(T)          T &operator = (T const&) = delete
#ifdef _MSC_VER
#define __CXX_DELETE_VOLATILE_COPY_ASSIGN(T) /* Nothing */
#else /* _MSC_VER */
#define __CXX_DELETE_VOLATILE_COPY_ASSIGN(T) T &operator = (T const&) volatile = delete
#endif /* !_MSC_VER */
#else
#define __CXX_DELETE_CTOR(T)                 private: T()
#define __CXX_DELETE_DTOR(T)                 private: ~T()
#define __CXX_DELETE_COPY(T)                 private: T(T const&)
#define __CXX_DELETE_COPY_ASSIGN(T)          private: T &operator = (T const&)
#define __CXX_DELETE_VOLATILE_COPY_ASSIGN(T) private: T &operator = (T const&) volatile
#endif

#ifdef _MSC_VER
/* 4522: Incorrect warning about multiple assignment
 *       operators after `__CXX_DELETE_COPY_ASSIGN()' */
#define __CXXDECL_BEGIN __pragma(warning(push)) \
                        __pragma(warning(disable: 4522)) \
                        extern "C++" {
#define __CXXDECL_END   } \
                        __pragma(warning(pop))
#endif /* _MSC_VER */

#ifdef __COMPILER_HAVE_CXX11_NOEXCEPT
#define __CXX_THROWS(...) /* Nothing */
#elif defined(_MSC_VER) && !defined(__INTELLISENSE__)
#define __CXX_THROWS(...) /* Nothing */
#else
#define __CXX_THROWS(...) throw(__VA_ARGS__)
#endif

#ifndef __CXXDECL_BEGIN
#define __CXXDECL_BEGIN  extern "C++" {
#define __CXXDECL_END    }
#endif /* !__CXXDECL_BEGIN */

#endif /* !___STDCXX_H */
