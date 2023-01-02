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
#ifndef _CXX_COMPILER_ENUM_CLASS_H
#define _CXX_COMPILER_ENUM_CLASS_H 1

#include <__stdcxx.h>

#ifdef __COMPILER_HAVE_CXX_ENUM_CLASSES
#define __CXX_ENUM_CLASS_BEGIN(name)          enum class name
#define __CXX_ENUM_CLASS_BEGIN_EX(name, base) enum class name : base
#define __CXX_ENUM_CLASS_END(name)            /* nothing */
#else /* __COMPILER_HAVE_CXX_ENUM_CLASSES */
#define __CXX_ENUM_CLASS_BEGIN(name) __CXX_ENUM_CLASS_BEGIN_EX(name, int)
#define __CXX_ENUM_CLASS_BEGIN_EX(name, base)                                                             \
	struct name {                                                                                         \
	public:                                                                                               \
		typedef base __enum_class_base_t;                                                                 \
                                                                                                          \
	private:                                                                                              \
		__enum_class_base_t __m_val;                                                                      \
                                                                                                          \
	public:                                                                                               \
		__CXX_DEFAULT_CTOR_NOEXCEPT(name)                                                                 \
		__CXX_CLASSMEMBER __CXX11_CONSTEXPR name(__enum_class_base_t __v) __CXX_NOEXCEPT: __m_val(__v) {} \
		enum __enum_class_enum_t
#define __PRIVATE_CXX_ENUM_CLASS_DEFINE_COMPARE(name, op)                      \
	friend __CXX_CLASSMEMBER __CXX11_CONSTEXPR bool                            \
	operator op(name const &__lhs, name const &__rhs) __CXX_NOEXCEPT {         \
		return __lhs.__m_val op __rhs.__m_val;                                 \
	}                                                                          \
	friend __CXX_CLASSMEMBER __CXX11_CONSTEXPR bool                            \
	operator op(name const &__lhs, __enum_class_enum_t __rhs) __CXX_NOEXCEPT { \
		return __lhs.__m_val op(__enum_class_base_t) __rhs;                    \
	}                                                                          \
	friend __CXX_CLASSMEMBER __CXX11_CONSTEXPR bool                            \
	operator op(__enum_class_enum_t __lhs, name const &__rhs) __CXX_NOEXCEPT { \
		return (__enum_class_base_t)__lhs op __rhs.__m_val;                    \
	}
#define __CXX_ENUM_CLASS_END(name)                                                            \
	;                                                                                         \
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR name(__enum_class_enum_t __v) __CXX_NOEXCEPT          \
	    : __m_val((__enum_class_base_t)__v) {}                                                \
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR explicit name(__enum_class_base_t __v) __CXX_NOEXCEPT \
	    : __m_val(__v) {}                                                                     \
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR operator __enum_class_enum_t() const __CXX_NOEXCEPT { \
		return (__enum_class_enum_t)__m_val;                                                  \
	}                                                                                         \
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __CXX11_EXPLICIT_OPERATOR                             \
	operator __enum_class_base_t() const __CXX_NOEXCEPT {                                     \
		return __m_val;                                                                       \
	}                                                                                         \
	__PRIVATE_CXX_ENUM_CLASS_DEFINE_COMPARE(name, <)                                          \
	__PRIVATE_CXX_ENUM_CLASS_DEFINE_COMPARE(name, <=)                                         \
	__PRIVATE_CXX_ENUM_CLASS_DEFINE_COMPARE(name, >)                                          \
	__PRIVATE_CXX_ENUM_CLASS_DEFINE_COMPARE(name, >=)                                         \
	__PRIVATE_CXX_ENUM_CLASS_DEFINE_COMPARE(name, ==)                                         \
	__PRIVATE_CXX_ENUM_CLASS_DEFINE_COMPARE(name, !=)                                         \
	}                                                                                         \
	name
#endif /* !__COMPILER_HAVE_CXX_ENUM_CLASSES */


#endif /* !_CXX_COMPILER_ENUM_CLASS_H */
