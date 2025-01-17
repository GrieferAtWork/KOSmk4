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
#ifndef _BITS_STL_ITERATOR_H
#define _BITS_STL_ITERATOR_H 1

#include <__stdcxx.h>

#include <hybrid/typecore.h>

#include "__addressof.h"
#include "traits/declval.h"

#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
#include "move.h"
#include "traits/is_reference.h"
#include "traits/remove_reference.h"
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};

template<class __Category,
         class __T,
         class __Distance  = __PTRDIFF_TYPE__,
         class __Pointer   = __T *,
         class __Reference = __T &>
struct iterator {
	typedef __T         value_type;
	typedef __Distance  difference_type;
	typedef __Pointer   pointer;
	typedef __Reference reference;
	typedef __Category  iterator_category;
};

template<class __Iterator>
struct iterator_traits {
	typedef typename __Iterator::iterator_category iterator_category;
	typedef typename __Iterator::value_type        value_type;
	typedef typename __Iterator::difference_type   difference_type;
	typedef typename __Iterator::pointer           pointer;
	typedef typename __Iterator::reference         reference;
};

template<class __T>
struct iterator_traits<__T *> {
	typedef random_access_iterator_tag iterator_category;
	typedef __T                        value_type;
	typedef __PTRDIFF_TYPE__           difference_type;
	typedef __T                       *pointer;
	typedef __T                       &reference;
};

template<class __T>
struct iterator_traits<__T const *> {
	typedef random_access_iterator_tag iterator_category;
	typedef __T                        value_type;
	typedef __PTRDIFF_TYPE__           difference_type;
	typedef const __T                 *pointer;
	typedef const __T                 &reference;
};


template<class __Iterator>
class reverse_iterator
	: public iterator<typename iterator_traits<__Iterator>::iterator_category,
	                  typename iterator_traits<__Iterator>::value_type,
	                  typename iterator_traits<__Iterator>::difference_type,
	                  typename iterator_traits<__Iterator>::pointer,
	                  typename iterator_traits<__Iterator>::reference> {
protected:
	__Iterator current;
public:
	typedef __Iterator                                            iterator_type;
	typedef typename iterator_traits<__Iterator>::difference_type difference_type;
	typedef typename iterator_traits<__Iterator>::pointer         pointer;
	typedef typename iterator_traits<__Iterator>::reference       reference;
	__CXX_CLASSMEMBER __CXX17_CONSTEXPR __LIBCCALL reverse_iterator()
	    : current() {}
	explicit __CXX_CLASSMEMBER __CXX17_CONSTEXPR __LIBCCALL reverse_iterator(iterator_type __iter)
	    : current(__iter) {}
	__CXX_CLASSMEMBER __CXX17_CONSTEXPR __LIBCCALL reverse_iterator(reverse_iterator const &__other)
	    : current(__other.current) {}
	template<class __Iter> __CXX_CLASSMEMBER __CXX17_CONSTEXPR __LIBCCALL
	reverse_iterator(reverse_iterator<__Iter> const &__other)
	    : current(__other.base()) {}
	__CXX_CLASSMEMBER __CXX17_CONSTEXPR iterator_type __LIBCCALL base() const {
		return current;
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reference __LIBCCALL
	operator*() const {
		__Iterator __res = current;
		return *--__res;
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR pointer __LIBCCALL
	operator->() const {
		return __NAMESPACE_INT_SYM __addressof(this->operator*());
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator &__LIBCCALL
	operator++() {
		--current;
		return *this;
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator __LIBCCALL
	operator++(int) {
		reverse_iterator __res = *this;
		--current;
		return __res;
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator &__LIBCCALL
	operator--() {
		++current;
		return *this;
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator __LIBCCALL
	operator--(int) {
		reverse_iterator __res = *this;
		++current;
		return __res;
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator __LIBCCALL
	operator+(difference_type __offset) const {
		return reverse_iterator(current - __offset);
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator &__LIBCCALL
	operator+=(difference_type __offset) {
		current -= __offset;
		return *this;
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator __LIBCCALL
	operator-(difference_type __offset) const {
		return reverse_iterator(current + __offset);
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator &__LIBCCALL
	operator-=(difference_type __offset) {
		current += __offset;
		return *this;
	}

	__CXX_CLASSMEMBER __CXX17_CONSTEXPR reference __LIBCCALL
	operator[](difference_type __offset) const {
		return *(*this + __offset);
	}
};

template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator==(reverse_iterator<__Iterator> const &__lhs, reverse_iterator<__Iterator> const &__rhs) {
	return __lhs.base() == __rhs.base();
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator<(reverse_iterator<__Iterator> const &__lhs, reverse_iterator<__Iterator> const &__rhs) {
	return __rhs.base() < __lhs.base();
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator!=(reverse_iterator<__Iterator> const &__lhs, reverse_iterator<__Iterator> const &__rhs) {
	return !(__lhs == __rhs);
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator>(reverse_iterator<__Iterator> const &__lhs, reverse_iterator<__Iterator> const &__rhs) {
	return __rhs < __lhs;
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator<=(reverse_iterator<__Iterator> const &__lhs, reverse_iterator<__Iterator> const &__rhs) {
	return !(__rhs < __lhs);
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator>=(reverse_iterator<__Iterator> const &__lhs, reverse_iterator<__Iterator> const &__rhs) {
	return !(__lhs < __rhs);
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator==(reverse_iterator<__IteratorL> const &__lhs, reverse_iterator<__IteratorR> const &__rhs) {
	return __lhs.base() == __rhs.base();
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator<(reverse_iterator<__IteratorL> const &__lhs, reverse_iterator<__IteratorR> const &__rhs) {
	return __rhs.base() < __lhs.base();
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator!=(reverse_iterator<__IteratorL> const &__lhs, reverse_iterator<__IteratorR> const &__rhs) {
	return !(__lhs == __rhs);
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator>(reverse_iterator<__IteratorL> const &__lhs, reverse_iterator<__IteratorR> const &__rhs) {
	return __rhs < __lhs;
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator<=(reverse_iterator<__IteratorL> const &__lhs, reverse_iterator<__IteratorR> const &__rhs) {
	return !(__rhs < __lhs);
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator>=(reverse_iterator<__IteratorL> const &__lhs, reverse_iterator<__IteratorR> const &__rhs) {
	return !(__lhs < __rhs);
}


#if __cplusplus < 201103L || !defined(__COMPILER_HAVE_CXX_DECLTYPE)
template<class __Iterator> __CXX_CLASSMEMBER
typename reverse_iterator<__Iterator>::difference_type __LIBCCALL
operator-(reverse_iterator<__Iterator> const &__lhs, reverse_iterator<__Iterator> const &__rhs) {
	return __rhs.base() - __lhs.base();
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER
typename reverse_iterator<__IteratorL>::difference_type __LIBCCALL
operator-(reverse_iterator<__IteratorL> const &__lhs, reverse_iterator<__IteratorR> const &__rhs) {
	return __rhs.base() - __lhs.base();
}
#else
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR
decltype(declval<__IteratorR>() - declval<__IteratorL>()) __LIBCCALL
operator-(reverse_iterator<__IteratorL> const &__lhs, reverse_iterator<__IteratorR> const &__rhs) {
	return __rhs.base() - __lhs.base();
}
#endif

template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator<__Iterator> __LIBCCALL
operator+(typename reverse_iterator<__Iterator>::difference_type __n, reverse_iterator<__Iterator> const &__x) {
	return reverse_iterator<__Iterator>(__x.base() - __n);
}

#if __cplusplus > 201103L
#define __cpp_lib_make_reverse_iterator 201402
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR reverse_iterator<__Iterator> __LIBCCALL
make_reverse_iterator(__Iterator __iter) {
	return reverse_iterator<__Iterator>(__CXX_MOVE(__iter));
}
#endif


template<class __Container>
class back_insert_iterator
	: public iterator<output_iterator_tag, void, void, void, void>
{
protected:
	__Container        *container;
public:
	typedef __Container container_type;
	__CXX_CLASSMEMBER explicit __LIBCCALL back_insert_iterator(__Container &__container) __CXX_NOEXCEPT
	    : container(__NAMESPACE_INT_SYM __addressof(__container)) {}
	__CXX_CLASSMEMBER back_insert_iterator &__LIBCCALL operator=(typename __Container::const_reference __val) {
		container->push_back(__val);
		return *this;
	}
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__CXX_CLASSMEMBER back_insert_iterator &__LIBCCALL operator=(typename __Container::value_type &&__val) {
		container->push_back(__CXX_MOVE(__val));
		return *this;
	}
#endif
	__CXX_CLASSMEMBER __ATTR_CONST back_insert_iterator &__LIBCCALL operator*() __CXX_NOEXCEPT {
		return *this;
	}
	__CXX_CLASSMEMBER __ATTR_CONST back_insert_iterator &__LIBCCALL operator++() __CXX_NOEXCEPT {
		return *this;
	}
	__CXX_CLASSMEMBER __ATTR_CONST back_insert_iterator __LIBCCALL operator++(int) __CXX_NOEXCEPT {
		return *this;
	}
};

template<class __Container>
class front_insert_iterator
	: public iterator<output_iterator_tag,void,void,void,void>
{
protected:
	__Container *container;
public:
	typedef __Container container_type;
	explicit __CXX_CLASSMEMBER __LIBCCALL front_insert_iterator(__Container &__container) __CXX_NOEXCEPT
	    : container(__NAMESPACE_INT_SYM __addressof(__container)) {}
	__CXX_CLASSMEMBER front_insert_iterator &__LIBCCALL operator=(typename __Container::const_reference __val) {
		container->push_front(__val);
		return *this;
	}
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__CXX_CLASSMEMBER front_insert_iterator &__LIBCCALL operator=(typename __Container::value_type &&__val) {
		container->push_front(__CXX_MOVE(__val));
		return *this;
	}
#endif
	__CXX_CLASSMEMBER __ATTR_CONST front_insert_iterator &__LIBCCALL operator*() __CXX_NOEXCEPT {
		return *this;
	}
	__CXX_CLASSMEMBER __ATTR_CONST front_insert_iterator &__LIBCCALL operator++() __CXX_NOEXCEPT {
		return *this;
	}
	__CXX_CLASSMEMBER __ATTR_CONST front_insert_iterator __LIBCCALL operator++(int) __CXX_NOEXCEPT {
		return *this;
	}
};

template<class __Container>
class insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void> {
protected:
	__Container                   *container;
	typename __Container::iterator iter;
public:
	typedef __Container            container_type;
	__CXX_CLASSMEMBER __LIBCCALL insert_iterator(__Container &__container, class __Container::iterator __index)
	    : container(__NAMESPACE_INT_SYM __addressof(__container))
	    , iter(__CXX_MOVE(__index)) {}
	__CXX_CLASSMEMBER insert_iterator &__LIBCCALL operator=(typename __Container::const_reference __val) {
		container->insert(this->iter, __val);
		return *this;
	}
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__CXX_CLASSMEMBER insert_iterator &__LIBCCALL operator=(typename __Container::value_type &&__val) {
		container->insert(this->iter, __CXX_MOVE(__val));
		return *this;
	}
#endif
	__CXX_CLASSMEMBER __ATTR_CONST insert_iterator &__LIBCCALL operator*() __CXX_NOEXCEPT {
		return *this;
	}
	__CXX_CLASSMEMBER __ATTR_CONST insert_iterator &__LIBCCALL operator++() __CXX_NOEXCEPT {
		return *this;
	}
	__CXX_CLASSMEMBER __ATTR_CONST insert_iterator __LIBCCALL operator++(int) __CXX_NOEXCEPT {
		return *this;
	}
};


template<class __Container> __CXX_CLASSMEMBER back_insert_iterator<__Container>
__LIBCCALL back_inserter(__Container &__container) __CXX_NOEXCEPT {
	return back_insert_iterator<__Container>(__container);
}
template<class __Container> __CXX_CLASSMEMBER front_insert_iterator<__Container>
__LIBCCALL front_inserter(__Container &__container) __CXX_NOEXCEPT {
	return front_insert_iterator<__Container>(__container);
}
template<class __Container, class __Iterator> __CXX_CLASSMEMBER insert_iterator<__Container>
__LIBCCALL inserter(__Container &__container, __Iterator __index) {
	return insert_iterator<__Container>(__container, typename __Container::iterator(__CXX_MOVE(__index)));
}

#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __Iterator>
class move_iterator
{
protected:
	__Iterator                          __m_current;
	typedef iterator_traits<__Iterator> __traits_type;
	typedef typename iterator_traits<__Iterator>::reference __trait_ref;
public:
	typedef __Iterator                                              iterator_type;
	typedef typename iterator_traits<__Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<__Iterator>::value_type        value_type;
	typedef typename iterator_traits<__Iterator>::difference_type   difference_type;
	typedef __Iterator                                              pointer;
	typedef typename conditional<is_reference<__trait_ref>::value,
	                             typename remove_reference<__trait_ref>::type &&,
	                             __trait_ref>::type reference;
	__CXX17_CONSTEXPR __LIBCCALL move_iterator() __CXX_NOEXCEPT_IFNX(__Iterator())
	    : __m_current() {}
	explicit __CXX17_CONSTEXPR __LIBCCALL move_iterator(iterator_type __i) __CXX_NOEXCEPT_IFNX(__Iterator(__i))
	    : __m_current(__i) {}
	template<class __Iter> __CXX17_CONSTEXPR __LIBCCALL
	move_iterator(move_iterator<__Iter> const &__i) __CXX_NOEXCEPT_IFNX(__Iterator(__i.base()))
	    : __m_current(__i.base()) {}
	__CXX17_CONSTEXPR iterator_type __LIBCCALL base() const {
		return this->__m_current;
	}
	__CXX17_CONSTEXPR reference __LIBCCALL operator*() const {
		return move(*this->__m_current);
	}
	__CXX17_CONSTEXPR pointer __LIBCCALL operator->() const {
		return this->__m_current;
	}
	__CXX17_CONSTEXPR move_iterator &__LIBCCALL operator++() {
		++this->__m_current;
		return *this;
	}
	__CXX17_CONSTEXPR move_iterator __LIBCCALL operator++(int) {
		move_iterator __tmp(*this);
		++this->__m_current;
		return __tmp;
	}
	__CXX17_CONSTEXPR move_iterator &__LIBCCALL operator--() {
		--this->__m_current;
		return *this;
	}
	__CXX17_CONSTEXPR move_iterator __LIBCCALL operator--(int) {
		move_iterator __tmp(*this);
		--this->__m_current;
		return __tmp;
	}
	__CXX17_CONSTEXPR move_iterator __LIBCCALL operator+(difference_type __n) const {
		return move_iterator(this->__m_current + __n);
	}
	__CXX17_CONSTEXPR move_iterator &__LIBCCALL operator+=(difference_type __n) {
		this->__m_current += __n;
		return *this;
	}
	__CXX17_CONSTEXPR move_iterator __LIBCCALL operator-(difference_type __n) const {
		return move_iterator(this->__m_current - __n);
	}
	__CXX17_CONSTEXPR move_iterator &__LIBCCALL operator-=(difference_type __n) {
		this->__m_current -= __n;
		return *this;
	}
	__CXX17_CONSTEXPR reference __LIBCCALL operator[](difference_type __n) const {
		return move(this->__m_current[__n]);
	}
};

template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator==(move_iterator<__Iterator> const &__lhs, move_iterator<__Iterator> const &__rhs) {
	return __lhs.base() == __rhs.base();
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator<(move_iterator<__Iterator> const &__lhs, move_iterator<__Iterator> const &__rhs) {
	return __lhs.base() < __rhs.base();
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator!=(move_iterator<__Iterator> const &__lhs, move_iterator<__Iterator> const &__rhs) {
	return !(__lhs == __rhs);
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator>(move_iterator<__Iterator> const &__lhs, move_iterator<__Iterator> const &__rhs) {
	return __rhs < __lhs;
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator<=(move_iterator<__Iterator> const &__lhs, move_iterator<__Iterator> const &__rhs) {
	return !(__rhs < __lhs);
}
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator>=(move_iterator<__Iterator> const &__lhs, move_iterator<__Iterator> const &__rhs) {
	return !(__lhs < __rhs);
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator==(move_iterator<__IteratorL> const &__lhs, move_iterator<__IteratorR> const &__rhs) {
	return __lhs.base() == __rhs.base();
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator<(move_iterator<__IteratorL> const &__lhs, move_iterator<__IteratorR> const &__rhs) {
	return __lhs.base() < __rhs.base();
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator!=(move_iterator<__IteratorL> const &__lhs, move_iterator<__IteratorR> const &__rhs) {
	return !(__lhs == __rhs);
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator>(move_iterator<__IteratorL> const &__lhs, move_iterator<__IteratorR> const &__rhs) {
	return __rhs < __lhs;
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator<=(move_iterator<__IteratorL> const &__lhs, move_iterator<__IteratorR> const &__rhs) {
	return !(__rhs < __lhs);
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR bool __LIBCCALL
operator>=(move_iterator<__IteratorL> const &__lhs, move_iterator<__IteratorR> const &__rhs) {
	return !(__lhs < __rhs);
}


#if !defined(__USE_ISOCXX11) || !defined(__COMPILER_HAVE_CXX_DECLTYPE)
template<class __Iterator> __CXX_CLASSMEMBER
typename move_iterator<__Iterator>::difference_type __LIBCCALL
operator-(move_iterator<__Iterator> const &__lhs, move_iterator<__Iterator> const &__rhs) {
	return __lhs.base() - __rhs.base();
}
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER
typename move_iterator<__IteratorL>::difference_type __LIBCCALL
operator-(move_iterator<__IteratorL> const &__lhs, move_iterator<__IteratorR> const &__rhs) {
	return __lhs.base() - __rhs.base();
}
#else
template<class __IteratorL, class __IteratorR> __CXX_CLASSMEMBER __CXX17_CONSTEXPR
decltype(declval<__IteratorR>() - declval<__IteratorL>()) __LIBCCALL
operator-(move_iterator<__IteratorL> const &__lhs, move_iterator<__IteratorR> const &__rhs) {
	return __lhs.base() - __rhs.base();
}
#endif
template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR move_iterator<__Iterator> __LIBCCALL
operator+(typename move_iterator<__Iterator>::difference_type __n, move_iterator<__Iterator> const &__x) {
	return move_iterator<__Iterator>(__x.base() + __n);
}

template<class __Iterator> __CXX_CLASSMEMBER __CXX17_CONSTEXPR move_iterator<__Iterator>
__LIBCCALL make_move_iterator(__Iterator __iter) {
	return move_iterator<__Iterator>(__CXX_MOVE(__iter));
}
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_BITS_STL_ITERATOR_H */
