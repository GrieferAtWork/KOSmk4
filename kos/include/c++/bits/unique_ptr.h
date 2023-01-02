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
#ifndef _CXX_BITS_UNIQUE_PTR_H
#define _CXX_BITS_UNIQUE_PTR_H 1

#include <__stdcxx.h>
#include "operator_new.h"
#include "traits/enable_if.h"
#include "traits/is_convertible.h"
#include "traits/remove_reference.h"
#include "traits/conditional.h"

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

template<class __T> struct default_delete {
	__CXX11_CONSTEXPR __CXX_DEFAULT_CTOR_NOEXCEPT(default_delete);
	template<class __U, class __Sel = typename enable_if<is_convertible<__U *, __T *>::value>::type>
	__CXX_CLASSMEMBER __LIBCCALL default_delete(default_delete<__U> const &) __CXX_NOEXCEPT {}
	__CXX_CLASSMEMBER void __LIBCCALL operator()(__T *__ptr) const
	__CXX_NOEXCEPT_IFNX(delete (__ptr)) { delete __ptr; }
};

#ifndef __clang_tidy__ /* FIXME */
template<class __T> struct default_delete<__T[]> {
public:
	__CXX11_CONSTEXPR __CXX_DEFAULT_CTOR_NOEXCEPT(default_delete);
	template<class __U, class __Sel = typename enable_if<is_convertible<__U (*)[], __T (*)[]>::value>::type>
	__CXX_CLASSMEMBER __LIBCCALL default_delete(default_delete<__U[]> const &) __CXX_NOEXCEPT {}
	template<class __U> typename enable_if<is_convertible<__U (*)[], __T (*)[]>::value>::type
	__CXX_CLASSMEMBER __LIBCCALL operator()(__U *__ptr) const
	__CXX_NOEXCEPT_IFNX(delete[](__ptr)) { delete[] __ptr; }
};
#endif /* !__clang_tidy__ */

#if 0
#ifndef __COMPILER_HAVE_CXX_DECLTYPE
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
struct __deleter_pointer_type_base {
	template<class __U> static int (&__test(typename __U::pointer *))[1];
	template<class __U> static int (&__test(...))[2];
};
template<class __T, class __Deleter, bool sel = sizeof(__deleter_pointer_type_base::__test<__Deleter>()) == sizeof(int[1])>
struct __deleter_pointer_type { typedef __T *__type; };
template<class __T, class __Deleter>
struct __deleter_pointer_type<__T,__Deleter,true> { typedef typename __Deleter::pointer __type; };
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
#endif /* !__COMPILER_HAVE_CXX_DECLTYPE */

template<class __T, class __Deleter = default_delete<__T> > class unique_ptr {
#ifdef __COMPILER_HAVE_CXX_DECLTYPE
	class _Pointer {
		template<class _Up> static typename _Up::pointer __test(typename _Up::pointer *);
		template<class _Up> static __T *__test(...);
	public:
		typedef decltype(__test<typename remove_reference<__Deleter>::type>(0)) type;
	};
public:
	typedef typename _Pointer::type pointer;
#else /* __COMPILER_HAVE_CXX_DECLTYPE */
public:
	typedef typename __NAMESPACE_INT_SYM __deleter_pointer_type<__T,__Deleter>::__type pointer;
#endif /* !__COMPILER_HAVE_CXX_DECLTYPE */
	typedef __T       element_type;
	typedef __Deleter deleter_type;
private:
	typedef std::tuple<pointer,__Deleter> __tuple_type;
	__tuple_type                          _M_t;
public:
	template<class _Up, class _Ep>
	using __safe_conversion_up = __and_<
				is_convertible<typename unique_ptr<_Up, _Ep>::pointer, pointer>,
				__not_<is_array<_Up>>,
				__or_<__and_<is_reference<deleter_type>,
								is_same<deleter_type, _Ep>>,
						__and_<__not_<is_reference<deleter_type>>,
								is_convertible<_Ep, deleter_type>>
				>
				>;

		// Constructors.

		/// Default constructor, creates a unique_ptr that owns nothing.
		constexpr unique_ptr() noexcept
		: _M_t()
		{ static_assert(!is_pointer<deleter_type>::value,
				"constructed with null function pointer deleter"); }

		/** Takes ownership of a pointer.
		*
		* @param __p  A pointer to an object of @c element_type
		*
		* The deleter will be value-initialized.
		*/
		explicit
		unique_ptr(pointer __p) noexcept
		: _M_t(__p, deleter_type())
		{ static_assert(!is_pointer<deleter_type>::value,
				"constructed with null function pointer deleter"); }

		/** Takes ownership of a pointer.
		*
		* @param __p  A pointer to an object of @c element_type
		* @param __d  A reference to a deleter.
		*
		* The deleter will be initialized with @p __d
		*/
		unique_ptr(pointer __p,
		typename conditional<is_reference<deleter_type>::value,
		deleter_type, const deleter_type&>::type __d) noexcept
		: _M_t(__p, __d) { }

		/** Takes ownership of a pointer.
		*
		* @param __p  A pointer to an object of @c element_type
		* @param __d  An rvalue reference to a deleter.
		*
		* The deleter will be initialized with @p std::move(__d)
		*/
		unique_ptr(pointer __p,
		typename remove_reference<deleter_type>::type&& __d) noexcept
		: _M_t(std::move(__p), std::move(__d))
		{ static_assert(!std::is_reference<deleter_type>::value,
				"rvalue deleter bound to reference"); }

		/// Creates a unique_ptr that owns nothing.
		constexpr unique_ptr(nullptr_t) noexcept : unique_ptr() { }

		// Move constructors.

		/// Move constructor.
		unique_ptr(unique_ptr&& __u) noexcept
		: _M_t(__u.release(), std::forward<deleter_type>(__u.get_deleter())) { }

		/** @brief Converting constructor from another type
		*
		* Requires that the pointer owned by @p __u is convertible to the
		* type of pointer owned by this object, @p __u does not own an array,
		* and @p __u has a compatible deleter type.
		*/
		template<class _Up, class _Ep, class = _Require<
				__safe_conversion_up<_Up, _Ep>,
			typename conditional<is_reference<__Deleter>::value,
					is_same<_Ep, __Deleter>,
					is_convertible<_Ep, __Deleter>>::type>>
	unique_ptr(unique_ptr<_Up, _Ep>&& __u) noexcept
	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	{ }

#if _GLIBCXX_USE_DEPRECATED
		/// Converting constructor from @c auto_ptr
		template<class _Up, class = _Require<
			is_convertible<_Up*, __T*>, is_same<__Deleter, default_delete<__T>>>>
	unique_ptr(auto_ptr<_Up>&& __u) noexcept;
#endif

		/// Destructor, invokes the deleter if the stored pointer is not null.
		~unique_ptr() noexcept
		{
	auto& __ptr = std::get<0>(_M_t);
	if (__ptr != nullptr)
		get_deleter()(__ptr);
	__ptr = pointer();
		}

		// Assignment.

		/** @brief Move assignment operator.
		*
		* @param __u  The object to transfer ownership from.
		*
		* Invokes the deleter first if this object owns a pointer.
		*/
		unique_ptr&
		operator=(unique_ptr&& __u) noexcept
		{
	reset(__u.release());
	get_deleter() = std::forward<deleter_type>(__u.get_deleter());
	return *this;
		}

		/** @brief Assignment from another type.
		*
		* @param __u  The object to transfer ownership from, which owns a
		*             convertible pointer to a non-array object.
		*
		* Invokes the deleter first if this object owns a pointer.
		*/
		template<class _Up, class _Ep>
		typename enable_if< __and_<
			__safe_conversion_up<_Up, _Ep>,
			is_assignable<deleter_type&, _Ep&&>
			>::value,
			unique_ptr&>::type
	operator=(unique_ptr<_Up, _Ep>&& __u) noexcept
	{
		reset(__u.release());
		get_deleter() = std::forward<_Ep>(__u.get_deleter());
		return *this;
	}

		/// Reset the %unique_ptr to empty, invoking the deleter if necessary.
		unique_ptr&
		operator=(nullptr_t) noexcept
		{
	reset();
	return *this;
		}

		// Observers.

		/// Dereference the stored pointer.
		typename add_lvalue_reference<element_type>::type
		operator*() const
		{
	__glibcxx_assert(get() != pointer());
	return *get();
		}

		/// Return the stored pointer.
		pointer
		operator->() const noexcept
		{
	_GLIBCXX_DEBUG_PEDASSERT(get() != pointer());
	return get();
		}

		/// Return the stored pointer.
		pointer
		get() const noexcept
		{ return std::get<0>(_M_t); }

		/// Return a reference to the stored deleter.
		deleter_type&
		get_deleter() noexcept
		{ return std::get<1>(_M_t); }

		/// Return a reference to the stored deleter.
		const deleter_type&
		get_deleter() const noexcept
		{ return std::get<1>(_M_t); }

		/// Return @c true if the stored pointer is not null.
		explicit operator bool() const noexcept
		{ return get() == pointer() ? false : true; }

		// Modifiers.

		/// Release ownership of any stored pointer.
		pointer
		release() noexcept
		{
	pointer __p = get();
	std::get<0>(_M_t) = pointer();
	return __p;
		}

		/** @brief Replace the stored pointer.
		*
		* @param __p  The new pointer to store.
		*
		* The deleter will be invoked if a pointer is already owned.
		*/
		void
		reset(pointer __p = pointer()) noexcept
		{
	using std::swap;
	swap(std::get<0>(_M_t), __p);
	if (__p != pointer())
		get_deleter()(__p);
		}

		/// Exchange the pointer and deleter with another object.
		void
		swap(unique_ptr& __u) noexcept
		{
	using std::swap;
	swap(_M_t, __u._M_t);
		}

		// Disable copy from lvalue.
		unique_ptr(const unique_ptr&) = delete;
		unique_ptr& operator=(const unique_ptr&) = delete;
	};

	/// 20.7.1.3 unique_ptr for array objects with a runtime length
	// [unique.ptr.runtime]
	// _GLIBCXX_RESOLVE_LIB_DEFECTS
	// DR 740 - omit specialization for array objects with a compile time length
	template<class __T, class __Deleter>
	class unique_ptr<__T[], __Deleter>
	{
		// use SFINAE to determine whether _Del::pointer exists
		class _Pointer
		{
	template<class _Up>
		static typename _Up::pointer __test(typename _Up::pointer*);

	template<class _Up>
		static __T* __test(...);

	typedef typename remove_reference<__Deleter>::type _Del;

		public:
	typedef decltype(__test<_Del>(0)) type;
		};

		typedef std::tuple<typename _Pointer::type, __Deleter>  __tuple_type;
		__tuple_type                                      _M_t;

		template<class _Up>
	using __remove_cv = typename remove_cv<_Up>::type;

		// like is_base_of<__T, _Up> but false if unqualified types are the same
		template<class _Up>
	using __is_derived_Tp
		= __and_< is_base_of<__T, _Up>,
			__not_<is_same<__remove_cv<__T>, __remove_cv<_Up>>> >;


	public:
		typedef typename _Pointer::type	pointer;
		typedef __T		 	element_type;
		typedef __Deleter                       deleter_type;

		// helper template for detecting a safe conversion from another
		// unique_ptr
		template<class _Up, class _Ep,
				typename _Up_up = unique_ptr<_Up, _Ep>,
			typename _Up_element_type = typename _Up_up::element_type>
	using __safe_conversion_up = __and_<
			is_array<_Up>,
			is_same<pointer, element_type*>,
			is_same<class _Up_up::pointer, _Up_element_type*>,
			is_convertible<_Up_element_type(*)[], element_type(*)[]>,
			__or_<__and_<is_reference<deleter_type>, is_same<deleter_type, _Ep>>,
				__and_<__not_<is_reference<deleter_type>>,
						is_convertible<_Ep, deleter_type>>>
		>;

		// helper template for detecting a safe conversion from a raw pointer
		template<class _Up>
		using __safe_conversion_raw = __and_<
			__or_<__or_<is_same<_Up, pointer>,
						is_same<_Up, nullptr_t>>,
				__and_<is_pointer<_Up>,
						is_same<pointer, element_type*>,
						is_convertible<
							typename remove_pointer<_Up>::type(*)[],
							element_type(*)[]>
				>
			>
		>;

		// Constructors.

		/// Default constructor, creates a unique_ptr that owns nothing.
		constexpr unique_ptr() noexcept
		: _M_t()
		{ static_assert(!std::is_pointer<deleter_type>::value,
				"constructed with null function pointer deleter"); }

		/** Takes ownership of a pointer.
		*
		* @param __p  A pointer to an array of a type safely convertible
		* to an array of @c element_type
		*
		* The deleter will be value-initialized.
		*/
		template<class _Up,
				typename = typename enable_if<
					__safe_conversion_raw<_Up>::value, bool>::type>
		explicit
		unique_ptr(_Up __p) noexcept
		: _M_t(__p, deleter_type())
		{ static_assert(!is_pointer<deleter_type>::value,
				"constructed with null function pointer deleter"); }

		/** Takes ownership of a pointer.
		*
		* @param __p  A pointer to an array of a type safely convertible
		* to an array of @c element_type
		* @param __d  A reference to a deleter.
		*
		* The deleter will be initialized with @p __d
		*/
		template<class _Up,
				typename = typename enable_if<
					__safe_conversion_raw<_Up>::value, bool>::type>
		unique_ptr(_Up __p,
					typename conditional<is_reference<deleter_type>::value,
					deleter_type, const deleter_type&>::type __d) noexcept
		: _M_t(__p, __d) { }

		/** Takes ownership of a pointer.
		*
		* @param __p  A pointer to an array of a type safely convertible
		* to an array of @c element_type
		* @param __d  A reference to a deleter.
		*
		* The deleter will be initialized with @p std::move(__d)
		*/
		template<class _Up,
				typename = typename enable_if<
					__safe_conversion_raw<_Up>::value, bool>::type>
		unique_ptr(_Up __p, class
			remove_reference<deleter_type>::type&& __d) noexcept
		: _M_t(std::move(__p), std::move(__d))
		{ static_assert(!is_reference<deleter_type>::value,
				"rvalue deleter bound to reference"); }

		/// Move constructor.
		unique_ptr(unique_ptr&& __u) noexcept
		: _M_t(__u.release(), std::forward<deleter_type>(__u.get_deleter())) { }

		/// Creates a unique_ptr that owns nothing.
		constexpr unique_ptr(nullptr_t) noexcept : unique_ptr() { }

		template<class _Up, class _Ep,
			typename = _Require<__safe_conversion_up<_Up, _Ep>>>
	unique_ptr(unique_ptr<_Up, _Ep>&& __u) noexcept
	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	{ }

		/// Destructor, invokes the deleter if the stored pointer is not null.
		~unique_ptr()
		{
	auto& __ptr = std::get<0>(_M_t);
	if (__ptr != nullptr)
		get_deleter()(__ptr);
	__ptr = pointer();
		}

		// Assignment.

		/** @brief Move assignment operator.
		*
		* @param __u  The object to transfer ownership from.
		*
		* Invokes the deleter first if this object owns a pointer.
		*/
		unique_ptr&
		operator=(unique_ptr&& __u) noexcept
		{
	reset(__u.release());
	get_deleter() = std::forward<deleter_type>(__u.get_deleter());
	return *this;
		}

		/** @brief Assignment from another type.
		*
		* @param __u  The object to transfer ownership from, which owns a
		*             convertible pointer to an array object.
		*
		* Invokes the deleter first if this object owns a pointer.
		*/
		template<class _Up, class _Ep>
	typename
	enable_if<__and_<__safe_conversion_up<_Up, _Ep>,
							is_assignable<deleter_type&, _Ep&&>
					>::value,
					unique_ptr&>::type
	operator=(unique_ptr<_Up, _Ep>&& __u) noexcept
	{
		reset(__u.release());
		get_deleter() = std::forward<_Ep>(__u.get_deleter());
		return *this;
	}

		/// Reset the %unique_ptr to empty, invoking the deleter if necessary.
		unique_ptr&
		operator=(nullptr_t) noexcept
		{
	reset();
	return *this;
		}

		// Observers.

		/// Access an element of owned array.
		typename std::add_lvalue_reference<element_type>::type
		operator[](size_t __i) const
		{
	__glibcxx_assert(get() != pointer());
	return get()[__i];
		}

		/// Return the stored pointer.
		pointer
		get() const noexcept
		{ return std::get<0>(_M_t); }

		/// Return a reference to the stored deleter.
		deleter_type&
		get_deleter() noexcept
		{ return std::get<1>(_M_t); }

		/// Return a reference to the stored deleter.
		const deleter_type&
		get_deleter() const noexcept
		{ return std::get<1>(_M_t); }

		/// Return @c true if the stored pointer is not null.
		explicit operator bool() const noexcept
		{ return get() == pointer() ? false : true; }

		// Modifiers.

		/// Release ownership of any stored pointer.
		pointer
		release() noexcept
		{
	pointer __p = get();
	std::get<0>(_M_t) = pointer();
	return __p;
		}

		/** @brief Replace the stored pointer.
		*
		* @param __p  The new pointer to store.
		*
		* The deleter will be invoked if a pointer is already owned.
		*/
		template<class _Up,
				typename = _Require<
					__or_<is_same<_Up, pointer>,
						__and_<is_same<pointer, element_type*>,
								is_pointer<_Up>,
								is_convertible<
									typename remove_pointer<_Up>::type(*)[],
									element_type(*)[]
								>
						>
					>
				>>
		void
		reset(_Up __p) noexcept
		{
	using std::swap;
	swap(std::get<0>(_M_t), __p);
	if (__p != nullptr)
		get_deleter()(__p);
		}

		void reset(nullptr_t = nullptr) noexcept
		{
		reset(pointer());
		}

		/// Exchange the pointer and deleter with another object.
		void
		swap(unique_ptr& __u) noexcept
		{
	using std::swap;
	swap(_M_t, __u._M_t);
		}

		// Disable copy from lvalue.
		unique_ptr(const unique_ptr&) = delete;
		unique_ptr& operator=(const unique_ptr&) = delete;
	};

	template<class __T, class __Deleter>
	inline void
	swap(unique_ptr<__T, __Deleter>& __x,
		unique_ptr<__T, __Deleter>& __y) noexcept
	{ __x.swap(__y); }

	template<class __T, class __Deleter,
		typename _Up, class _Ep>
	inline bool
	operator==(const unique_ptr<__T, __Deleter>& __x,
			const unique_ptr<_Up, _Ep>& __y)
	{ return __x.get() == __y.get(); }

	template<class __T, class __Deleter>
	inline bool
	operator==(const unique_ptr<__T, __Deleter>& __x, nullptr_t) noexcept
	{ return !__x; }

	template<class __T, class __Deleter>
	inline bool
	operator==(nullptr_t, const unique_ptr<__T, __Deleter>& __x) noexcept
	{ return !__x; }

	template<class __T, class __Deleter,
		typename _Up, class _Ep>
	inline bool
	operator!=(const unique_ptr<__T, __Deleter>& __x,
			const unique_ptr<_Up, _Ep>& __y)
	{ return __x.get() != __y.get(); }

	template<class __T, class __Deleter>
	inline bool
	operator!=(const unique_ptr<__T, __Deleter>& __x, nullptr_t) noexcept
	{ return (bool)__x; }

	template<class __T, class __Deleter>
	inline bool
	operator!=(nullptr_t, const unique_ptr<__T, __Deleter>& __x) noexcept
	{ return (bool)__x; }

	template<class __T, class __Deleter,
		typename _Up, class _Ep>
	inline bool
	operator<(const unique_ptr<__T, __Deleter>& __x,
			const unique_ptr<_Up, _Ep>& __y)
	{
		typedef typename
	std::common_type<class unique_ptr<__T, __Deleter>::pointer,
						typename unique_ptr<_Up, _Ep>::pointer>::type _CT;
		return std::less<_CT>()(__x.get(), __y.get());
	}

	template<class __T, class __Deleter>
	inline bool
	operator<(const unique_ptr<__T, __Deleter>& __x, nullptr_t)
	{ return std::less<class unique_ptr<__T, __Deleter>::pointer>()(__x.get(),
									nullptr); }

	template<class __T, class __Deleter>
	inline bool
	operator<(nullptr_t, const unique_ptr<__T, __Deleter>& __x)
	{ return std::less<class unique_ptr<__T, __Deleter>::pointer>()(nullptr,
									__x.get()); }

	template<class __T, class __Deleter,
		typename _Up, class _Ep>
	inline bool
	operator<=(const unique_ptr<__T, __Deleter>& __x,
			const unique_ptr<_Up, _Ep>& __y)
	{ return !(__y < __x); }

	template<class __T, class __Deleter>
	inline bool
	operator<=(const unique_ptr<__T, __Deleter>& __x, nullptr_t)
	{ return !(nullptr < __x); }

	template<class __T, class __Deleter>
	inline bool
	operator<=(nullptr_t, const unique_ptr<__T, __Deleter>& __x)
	{ return !(__x < nullptr); }

	template<class __T, class __Deleter,
		typename _Up, class _Ep>
	inline bool
	operator>(const unique_ptr<__T, __Deleter>& __x,
			const unique_ptr<_Up, _Ep>& __y)
	{ return (__y < __x); }

	template<class __T, class __Deleter>
	inline bool
	operator>(const unique_ptr<__T, __Deleter>& __x, nullptr_t)
	{ return std::less<class unique_ptr<__T, __Deleter>::pointer>()(nullptr,
									__x.get()); }

	template<class __T, class __Deleter>
	inline bool
	operator>(nullptr_t, const unique_ptr<__T, __Deleter>& __x)
	{ return std::less<class unique_ptr<__T, __Deleter>::pointer>()(__x.get(),
									nullptr); }

	template<class __T, class __Deleter,
		typename _Up, class _Ep>
	inline bool
	operator>=(const unique_ptr<__T, __Deleter>& __x,
			const unique_ptr<_Up, _Ep>& __y)
	{ return !(__x < __y); }

	template<class __T, class __Deleter>
	inline bool
	operator>=(const unique_ptr<__T, __Deleter>& __x, nullptr_t)
	{ return !(__x < nullptr); }

	template<class __T, class __Deleter>
	inline bool
	operator>=(nullptr_t, const unique_ptr<__T, __Deleter>& __x)
	{ return !(nullptr < __x); }

	/// std::hash specialization for unique_ptr.
	template<class __T, class __Deleter>
	struct hash<unique_ptr<__T, __Deleter>>
	: public __hash_base<size_t, unique_ptr<__T, __Deleter>>
	{
		size_t
		operator()(const unique_ptr<__T, __Deleter>& __u) const noexcept
		{
	typedef unique_ptr<__T, __Deleter> _UP;
	return std::hash<class _UP::pointer>()(__u.get());
		}
	};

#if __cplusplus > 201103L

#define __cpp_lib_make_unique 201304

	template<class __T>
	struct _MakeUniq
	{ typedef unique_ptr<__T> __single_object; };

	template<class __T>
	struct _MakeUniq<__T[]>
	{ typedef unique_ptr<__T[]> __array; };

	template<class __T, size_t _Bound>
	struct _MakeUniq<__T[_Bound]>
	{ struct __invalid_type { }; };

	/// std::make_unique for single objects
	template<class __T, class... _Args>
	inline typename _MakeUniq<__T>::__single_object
	make_unique(_Args&&... __args)
	{ return unique_ptr<__T>(new __T(std::forward<_Args>(__args)...)); }

	/// std::make_unique for arrays of unknown bound
	template<class __T>
	inline typename _MakeUniq<__T>::__array
	make_unique(size_t __num)
	{ return unique_ptr<__T>(new remove_extent_t<__T>[__num]()); }

	/// Disable std::make_unique for arrays of known bound
	template<class __T, class... _Args>
	inline typename _MakeUniq<__T>::__invalid_type
	make_unique(_Args&&...) = delete;
#endif
#endif



__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_UNIQUE_PTR_H */
