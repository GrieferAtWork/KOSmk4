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
#ifndef _KOS_REFPTR_H
#define _KOS_REFPTR_H 1

#include <__stdinc.h>

#include <kos/refcnt.h>

#ifdef __cplusplus
#include <__stdcxx.h>
#include <features.h>

#include <kos/anno.h>

#include <type_traits>

extern "C++" {
namespace kos {

template<class __T>
class __inheritptr {
public:
	__REF __T *__m_ptr; /* [0..1] Referenced object. */
	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	__inheritptr() __CXX_NOEXCEPT: __m_ptr(__NULLPTR) {}
	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	__inheritptr(__REF __T *__ptr) __CXX_NOEXCEPT: __m_ptr(__ptr) {}
	__CXX_DEFAULT_COPY_NOEXCEPT(__inheritptr, __other,
	                            : __m_ptr(__other.__m_ptr) {});
};

template<class __T>
__CXX_FORCEINLINE __ATTR_ARTIFICIAL __ATTR_CONST __inheritptr<__T>
inherit(__REF __T *__ptr) __CXX_NOEXCEPT {
	return __inheritptr<__T>(__ptr);
}


template<class __T>
class refptr {
private:
	typedef __REFCNT_METHODS(__T) __refctrl;
	__REF __T *__m_ptr; /* [0..1] Referenced object. */
public: /* Helper functions */
	__CXX_CLASSMEMBER __ATTR_ARTIFICIAL
	__NOBLOCK __ATTR_WUNUSED __T *get() const __CXX_NOEXCEPT {
		return __m_ptr;
	}

	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED
	__REF __T *incref() const __CXX_NOEXCEPT {
		__REF __T *__res = __m_ptr;
		if (__res)
			__refctrl::__PRIVATE_REFCNT_NAME(incref)(__res);
		return __res;
	}

	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED
	__REF __T *release() __CXX_NOEXCEPT {
		__REF __T *__res = __m_ptr;
		__m_ptr = __NULLPTR;
		return __res;
	}

	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL void clear() __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __NULLPTR;
		if (__optr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref)(__optr);
	}

	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL void clear_likely() __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __NULLPTR;
		if (__optr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref_likely)(__optr);
	}

	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL void clear_unlikely() __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __NULLPTR;
		if (__optr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref_unlikely)(__optr);
	}

public: /* conversion */
	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL operator __T *() const __CXX_NOEXCEPT {
		return __m_ptr;
	}
public: /* Deref */
	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL __T &operator*() const __CXX_NOEXCEPT {
		return *__m_ptr;
	}
	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL __T *operator->() const __CXX_NOEXCEPT {
		return __m_ptr;
	}
public: /* Assignment */
	template<class __SCT> __CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	typename std::enable_if<std::is_base_of<__T, __SCT>::value, refptr &>::type
	operator = (__inheritptr<__SCT> const &__other) {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.__m_ptr;
		if (__optr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref)(__optr);
		return *this;
	}
	template<class __SCT> __CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	typename std::enable_if<std::is_base_of<__T, __SCT>::value, refptr &>::type
	operator = (__SCT *__other) {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other;
		if (__optr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref)(__optr);
		return *this;
	}
	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL refptr &operator = (refptr const &__other) __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.incref();
		if (__optr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref)(__optr);
		return *this;
	}
	template<class __SCT> __CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	typename std::enable_if<std::is_base_of<__T, __SCT>::value, refptr &>::type
	operator = (refptr<__SCT> const &__other) {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.incref();
		if (__optr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref)(__optr);
		return *this;
	}
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL refptr &
	operator = (refptr &&__other) __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.release();
		if (__optr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref)(__optr);
		return *this;
	}
	template<class __SCT> __CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	typename std::enable_if<std::is_base_of<__T, __SCT>::value, refptr &>::type
	operator = (refptr<__SCT> &&__other) {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.release();
		if (__optr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref)(__optr);
		return *this;
	}
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
public: /* Constructor / Destructor */
	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	~refptr() __CXX_NOEXCEPT {
		if (__m_ptr)
			__refctrl::__PRIVATE_REFCNT_NAME(decref)(__m_ptr);
	}

	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	refptr() __CXX_NOEXCEPT
	    : __m_ptr(__NULLPTR) { }

	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	refptr(refptr const &__other) __CXX_NOEXCEPT
	    : __m_ptr(__other.incref()) { }

	template<class __SCT> __CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	refptr(__inheritptr<__SCT> const &__other, typename std::enable_if<std::is_base_of<__T, __SCT>::value, void>::type * = 0) __CXX_NOEXCEPT
	    : __m_ptr(__other.__m_ptr) { }

	template<class __SCT> __CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	refptr(__SCT *__other, typename std::enable_if<std::is_base_of<__T, __SCT>::value, void>::type * = 0) __CXX_NOEXCEPT
	    : __m_ptr(__other) {
		if (__other)
			__refctrl::__PRIVATE_REFCNT_NAME(incref)(__other);
	}

	template<class __SCT> __CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	refptr(refptr<__SCT> const &__other, typename std::enable_if<std::is_base_of<__T, __SCT>::value, void>::type * = 0) __CXX_NOEXCEPT
	    : __m_ptr(__other.incref()) { }

#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	refptr(refptr &&__other) __CXX_NOEXCEPT
	    : __m_ptr(__other.release()) { }
	template<class __SCT> __CXX_CLASSMEMBER __NOBLOCK __ATTR_ARTIFICIAL
	refptr(refptr<__SCT> &&__other, typename std::enable_if<std::is_base_of<__T, __SCT>::value, void>::type * = 0) __CXX_NOEXCEPT
	    : __m_ptr(__other.release()) { }
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
};

} /* namespace kos */
} /* extern "C++" */
#endif /* __cplusplus */


#endif /* !_KOS_REFPTR_H */
