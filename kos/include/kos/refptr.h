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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_REFPTR_H
#define _KOS_REFPTR_H 1

#include <__stdinc.h>

#include <kos/refcnt.h>

#if defined(__cplusplus) && defined(__CC__)
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
	__NOBLOCK __CXX_CLASSMEMBER __inheritptr() __CXX_NOEXCEPT: __m_ptr(__NULLPTR) {}
	__NOBLOCK __CXX_CLASSMEMBER __inheritptr(__REF __T *__ptr) __CXX_NOEXCEPT: __m_ptr(__ptr) {}
	__CXX_DEFAULT_COPY_NOEXCEPT(__inheritptr, __other,
	                            : __m_ptr(__other.__m_ptr) {});
};

template<class __T>
__CXX_FORCEINLINE __ATTR_CONST __inheritptr<__T> inherit(__REF __T *__ptr) __CXX_NOEXCEPT {
	return __inheritptr<__T>(__ptr);
}


template<class __T>
class refptr {
private:
	typedef __REFCNT_METHODS(__T) __refctrl;
	__REF __T *__m_ptr; /* [0..1] Referenced object. */
public: /* Helper functions */
	__NOBLOCK __CXX_CLASSMEMBER __ATTR_WUNUSED __T *get() const __CXX_NOEXCEPT {
		return __m_ptr;
	}
	__NOBLOCK __CXX_CLASSMEMBER __ATTR_WUNUSED __REF __T *incref() const __CXX_NOEXCEPT {
		__REF __T *__res = __m_ptr;
		if (__res)
			__refctrl::incref(__res);
		return __res;
	}
	__NOBLOCK __CXX_CLASSMEMBER __ATTR_WUNUSED __REF __T *release() __CXX_NOEXCEPT {
		__REF __T *__res = __m_ptr;
		__m_ptr = __NULLPTR;
		return __res;
	}
	__NOBLOCK __CXX_CLASSMEMBER void clear() __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __NULLPTR;
		if (__optr)
			__refctrl::decref(__optr);
	}
	__NOBLOCK __CXX_CLASSMEMBER void clear_likely() __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __NULLPTR;
		if (__optr)
			__refctrl::decref_likely(__optr);
	}
	__NOBLOCK __CXX_CLASSMEMBER void clear_unlikely() __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __NULLPTR;
		if (__optr)
			__refctrl::decref_unlikely(__optr);
	}
public: /* Deref */
	__NOBLOCK __CXX_CLASSMEMBER __T &operator*() const __CXX_NOEXCEPT {
		return *__m_ptr;
	}
	__NOBLOCK __CXX_CLASSMEMBER __T *operator->() const __CXX_NOEXCEPT {
		return __m_ptr;
	}
public: /* Assignment */
	template<class __SCT> __NOBLOCK __CXX_CLASSMEMBER
	typename std::enable_if<std::is_base_of<__T, __SCT>::value, refptr &>::type
	operator = (__inheritptr<__SCT> const &__other) {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.__m_ptr;
		if (__optr)
			__refctrl::decref(__optr);
		return *this;
	}
	template<class __SCT> __NOBLOCK __CXX_CLASSMEMBER
	typename std::enable_if<std::is_base_of<__T, __SCT>::value, refptr &>::type
	operator = (__SCT *__other) {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other;
		if (__optr)
			__refctrl::decref(__optr);
		return *this;
	}
	__NOBLOCK __CXX_CLASSMEMBER refptr &operator = (refptr const &__other) __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.incref();
		if (__optr)
			__refctrl::decref(__optr);
		return *this;
	}
	template<class __SCT> __NOBLOCK __CXX_CLASSMEMBER
	typename std::enable_if<std::is_base_of<__T, __SCT>::value, refptr &>::type
	operator = (refptr<__SCT> const &__other) {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.incref();
		if (__optr)
			__refctrl::decref(__optr);
		return *this;
	}
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__NOBLOCK __CXX_CLASSMEMBER refptr &operator = (refptr &&__other) __CXX_NOEXCEPT {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.release();
		if (__optr)
			__refctrl::decref(__optr);
		return *this;
	}
	template<class __SCT> __NOBLOCK __CXX_CLASSMEMBER
	typename std::enable_if<std::is_base_of<__T, __SCT>::value, refptr &>::type
	operator = (refptr<__SCT> &&__other) {
		__REF __T *__optr = __m_ptr;
		__m_ptr = __other.release();
		if (__optr)
			__refctrl::decref(__optr);
		return *this;
	}
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
public: /* Constructor / Destructor */
	__NOBLOCK __CXX_CLASSMEMBER ~refptr() __CXX_NOEXCEPT {
		if (__m_ptr)
			__refctrl::decref(__m_ptr);
	}
	__NOBLOCK __CXX_CLASSMEMBER refptr() __CXX_NOEXCEPT: __m_ptr(__NULLPTR) {}
	__NOBLOCK __CXX_CLASSMEMBER refptr(refptr const &__other) __CXX_NOEXCEPT: __m_ptr(__other.incref()) {}
	template<class __SCT>
	__NOBLOCK __CXX_CLASSMEMBER refptr(__inheritptr<__SCT> const &__other,
	                                   typename std::enable_if<std::is_base_of<__T, __SCT>::value, void>::type * = 0)
	__CXX_NOEXCEPT: __m_ptr(__other.__m_ptr) {}
	template<class __SCT>
	__NOBLOCK __CXX_CLASSMEMBER refptr(__SCT *__other,
	                                   typename std::enable_if<std::is_base_of<__T, __SCT>::value, void>::type * = 0)
	__CXX_NOEXCEPT: __m_ptr(__other) {
		if (__other)
			__refctrl::incref(__other);
	}
	template<class __SCT>
	__NOBLOCK __CXX_CLASSMEMBER refptr(refptr<__SCT> const &__other,
	                                   typename std::enable_if<std::is_base_of<__T, __SCT>::value, void>::type * = 0)
	__CXX_NOEXCEPT: __m_ptr(__other.incref()) {}
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__NOBLOCK __CXX_CLASSMEMBER refptr(refptr &&__other) __CXX_NOEXCEPT: __m_ptr(__other.release()) {}
	template<class __SCT>
	__NOBLOCK __CXX_CLASSMEMBER refptr(refptr<__SCT> &&__other,
	                                   typename std::enable_if<std::is_base_of<__T, __SCT>::value, void>::type * = 0)
	__CXX_NOEXCEPT: __m_ptr(__other.release()) {}
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
};

}

} /* extern "C++" */

#endif /* !__cplusplus || !__CC__ */


#endif /* !_KOS_REFPTR_H */
