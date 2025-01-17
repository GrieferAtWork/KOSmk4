/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _CXX_BITS_ALLOCATOR_H
#define _CXX_BITS_ALLOCATOR_H 1

#include <__stdcxx.h>
#include <features.h>

#include <bits/types.h>

#include "__addressof.h"
#include "crt_exceptions.h"
#include "forward.h"
#include "operator_new.h"
#ifdef __USE_ISOCXX11
#include "traits/integral_constant.h"
#endif /* __USE_ISOCXX11 */

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN
__NAMESPACE_INT_BEGIN
template<class __T>
class __allocator_base {
public:
	typedef __size_t    size_type;
	typedef __ptrdiff_t difference_type;
	typedef __T        *pointer;
	typedef __T const  *const_pointer;
	typedef __T        &reference;
	typedef __T const  &const_reference;
	typedef __T         value_type;
	template<typename __T2>
	struct rebind { typedef __allocator_base<__T2> other; };
#ifdef __USE_ISOCXX11
	typedef true_type propagate_on_container_move_assignment;
	typedef true_type is_always_equal;
#endif /* __USE_ISOCXX11 */
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL __allocator_base() __CXX_NOEXCEPT {}
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL __allocator_base(__allocator_base const &) __CXX_NOEXCEPT {}
	template<class __T2> __CXX_CLASSMEMBER __ATTR_ARTIFICIAL __allocator_base(__allocator_base<__T2> const &) __CXX_NOEXCEPT {}
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL ~__allocator_base() __CXX_NOEXCEPT {}
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL pointer address(reference __x) const __CXX_NOEXCEPT {
		return __NAMESPACE_INT_SYM __addressof(__x);
	}
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL const_pointer address(const_reference __x) const __CXX_NOEXCEPT {
		return __NAMESPACE_INT_SYM __addressof(__x);
	}
	__CXX_CLASSMEMBER pointer allocate(size_type __count, void const * = 0) {
		if (__count > this->max_size())
			__CXX_THROW_BAD_ALLOC();
		return (__T *)(::operator new(__count * sizeof(__T)));
	}
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL __ATTR_NONNULL_CXX((1)) void deallocate(pointer __p, size_type __UNUSED(__count)) {
		::operator delete(__p);
	}
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL size_type max_size() const __CXX_NOEXCEPT {
		return size_type(-1) / sizeof(__T);
	}
#if defined(__USE_ISOCXX11) && \
	defined(__COMPILER_HAVE_CXX_RVALUE_REFERENCE) && \
	defined(__COMPILER_HAVE_CXX_VARIABLE_TEMPLATES)
	template<class __Tp, class... __Args> __CXX_CLASSMEMBER __ATTR_NONNULL_CXX((1))
	__ATTR_ARTIFICIAL void construct(__Tp *__p, __Args &&... __args) {
		::new ((void *)__p) __Tp(std::forward<__Args>(__args)...);
	}
	template<class __Tp> __CXX_CLASSMEMBER __ATTR_ARTIFICIAL __ATTR_NONNULL_CXX((1)) void destroy(__Tp *__p) {
		__p->~__Tp();
	}
#else
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL __ATTR_NONNULL_CXX((1)) void construct(pointer __p, __T const &__val) {
		::new ((void *)__p) __T(__val);
	}
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL __ATTR_NONNULL_CXX((1)) void destroy(pointer __p) {
		__p->~__T();
	}
#endif
	__CXX_CLASSMEMBER __ATTR_CONST __ATTR_ARTIFICIAL bool operator==(__allocator_base<__T> const &) const __CXX_NOEXCEPT {
		return true;
	}
	__CXX_CLASSMEMBER __ATTR_CONST __ATTR_ARTIFICIAL bool operator!=(__allocator_base<__T> const &) const __CXX_NOEXCEPT {
		return false;
	}
	template<class __T2> __CXX_CLASSMEMBER __ATTR_CONST __ATTR_ARTIFICIAL bool operator==(__allocator_base<__T2> const &) const __CXX_NOEXCEPT {
		return true;
	}
	template<class __T2> __CXX_CLASSMEMBER __ATTR_CONST __ATTR_ARTIFICIAL bool operator!=(__allocator_base<__T2> const &) const __CXX_NOEXCEPT {
		return false;
	}
};
__NAMESPACE_INT_END

template<class __T>
class allocator
	: public __intern::__allocator_base<__T>
{
public:
	template<typename __T2>
	struct rebind { typedef allocator<__T2> other; };
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL allocator() __CXX_NOEXCEPT: __intern::__allocator_base<__T>() {}
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL allocator(allocator const &__other) __CXX_NOEXCEPT: __intern::__allocator_base<__T>(__other) {}
	template<typename __T2> __CXX_CLASSMEMBER __ATTR_ARTIFICIAL allocator(allocator<__T2> const &__other) __CXX_NOEXCEPT: __intern::__allocator_base<__T>(__other) {}
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL ~allocator() __CXX_NOEXCEPT {}
};

template<>
class allocator<void> {
public:
	typedef __size_t    size_type;
	typedef __ptrdiff_t difference_type;
	typedef void       *pointer;
	typedef void const *const_pointer;
	typedef void        value_type;
	template<typename __T2>
	struct rebind { typedef allocator<__T2> other; };
#ifdef __USE_ISOCXX11
	typedef true_type propagate_on_container_move_assignment;
	typedef true_type is_always_equal;
#endif
#if defined(__USE_ISOCXX11) && \
	defined(__COMPILER_HAVE_CXX_RVALUE_REFERENCE) && \
	defined(__COMPILER_HAVE_CXX_VARIABLE_TEMPLATES)
	template<typename __Tp, typename... __Args> __CXX_CLASSMEMBER
	__ATTR_ARTIFICIAL void construct(__Tp *__p, __Args &&... __args) {
		::new ((void *)__p) __Tp(std::forward<__Args>(__args)...);
	}
	template<typename __Tp> __CXX_CLASSMEMBER
	__ATTR_ARTIFICIAL void destroy(__Tp *__p) {
		__p->~__Tp();
	}
#endif
};

template<class __T> __CXX_CLASSMEMBER __ATTR_ARTIFICIAL bool
operator==(allocator<__T> const &, allocator<__T> const &) __CXX_NOEXCEPT {
	return true;
}
template<class __T> __CXX_CLASSMEMBER __ATTR_ARTIFICIAL bool
operator!=(allocator<__T> const &, allocator<__T> const &) __CXX_NOEXCEPT {
	return false;
}
template<class __T1, class __T2> __CXX_CLASSMEMBER __ATTR_ARTIFICIAL bool
operator==(allocator<__T1> const &, allocator<__T2> const &) __CXX_NOEXCEPT {
	return true;
}
template<class __T1, class __T2> __CXX_CLASSMEMBER __ATTR_ARTIFICIAL bool
operator!=(allocator<__T1> const &, allocator<__T2> const &) __CXX_NOEXCEPT {
	return false;
}


__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_ALLOCATOR_H */
