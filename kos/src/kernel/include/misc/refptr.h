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
#ifndef GUARD_KERNEL_INCLUDE_MISC_REFPTR_H
#define GUARD_KERNEL_INCLUDE_MISC_REFPTR_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kernel/malloc.h>

#ifdef __CC__
DECL_BEGIN

#ifndef __cplusplus
#error "refptr<T> is only availble in C++"
#endif

extern "C++" {

template<class T> class inherited_reference {
private:
	T *m_ptr;
public:
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL
	operator T *() const __CXX_NOEXCEPT {
		return m_ptr;
	}

	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL
	inherited_reference(T *ptr) __CXX_NOEXCEPT
	    : m_ptr(ptr) { }
};


struct __inherited_reference_tag {
public:
	template<class T> __CXX_FORCEINLINE ATTR_ARTIFICIAL
	inherited_reference<T> operator ->* (T *ptr) __CXX_NOEXCEPT {
		return ptr;
	}
};

/* Indicates that a raw pointer should be inherited by a `refptr' object
 * >> refptr<struct vm> p;
 * >> p = inherit vm_alloc();
 */
#define inherit    __inherited_reference_tag()->*


template<class T> class refptr {
private:
	T *m_ptr; /* [0..1][const] The pointed-to object. */
public:
    typedef REFCNT_METHODS(T) rm;
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL ~refptr() __CXX_NOEXCEPT { if (m_ptr) rm::decref(m_ptr); }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL refptr() __CXX_NOEXCEPT: m_ptr(__NULLPTR) {}
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL refptr(T *ptr) __CXX_NOEXCEPT: m_ptr(ptr) { if (ptr) rm::incref(ptr); }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL refptr(inherited_reference<T> ptr) __CXX_NOEXCEPT: m_ptr(ptr) {}
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL refptr(refptr const &other) __CXX_NOEXCEPT: m_ptr(other.m_ptr) { if (this->m_ptr) rm::incref(this->m_ptr); }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL refptr(refptr &&other) __CXX_NOEXCEPT: m_ptr(other.m_ptr) { other.m_ptr = __NULLPTR; }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL T *ptr() const __CXX_NOEXCEPT { return this->m_ptr; }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL T **operator & () __CXX_NOEXCEPT { return &this->m_ptr; }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL T *const *operator & () const __CXX_NOEXCEPT { return &this->m_ptr; }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL T &operator * () const __CXX_NOEXCEPT { return *this->m_ptr; }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL T *operator -> () const __CXX_NOEXCEPT { return this->m_ptr; }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL operator T *() const __CXX_NOEXCEPT { return this->m_ptr; }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL bool operator !() const __CXX_NOEXCEPT { return this->m_ptr == __NULLPTR; }
	__CXX_FORCEINLINE NOBLOCK ATTR_ARTIFICIAL operator bool() const __CXX_NOEXCEPT { return this->m_ptr != __NULLPTR; }
	__CXX_FORCEINLINE NOBLOCK T *release() __CXX_NOEXCEPT {
		T *result   = this->m_ptr;
		this->m_ptr = __NULLPTR;
		return result;
	}
	__CXX_FORCEINLINE NOBLOCK void clear() __CXX_NOEXCEPT {
		T *oldptr   = this->m_ptr;
		this->m_ptr = __NULLPTR;
		if (oldptr)
			rm::decref(oldptr);
	}
	__CXX_FORCEINLINE NOBLOCK refptr &operator = (decltype(nullptr)) __CXX_NOEXCEPT {
		T *oldptr   = this->m_ptr;
		this->m_ptr = __NULLPTR;
		if (oldptr)
			rm::decref(oldptr);
		return *this;
	}
	__CXX_FORCEINLINE NOBLOCK refptr &operator = (T *ptr) __CXX_NOEXCEPT {
		T *oldptr = this->m_ptr;
		if (ptr)
			rm::incref(ptr);
		this->m_ptr = ptr;
		if (oldptr)
			rm::decref(oldptr);
		return *this;
	}
	__CXX_FORCEINLINE NOBLOCK refptr &operator = (inherited_reference<T> ptr) __CXX_NOEXCEPT {
		T *oldptr   = this->m_ptr;
		this->m_ptr = ptr;
		if (oldptr)
			rm::decref(oldptr);
		return *this;
	}
	__CXX_FORCEINLINE NOBLOCK refptr &operator = (refptr const &other) __CXX_NOEXCEPT {
		T *oldptr   = this->m_ptr;
		this->m_ptr = other.m_ptr;
		if (this->m_ptr)
			rm::incref(this->m_ptr);
		if (oldptr)
			rm::decref(oldptr);
		return *this;
	}
	__CXX_FORCEINLINE NOBLOCK refptr &operator = (refptr &&other) __CXX_NOEXCEPT {
		T *oldptr, *newptr;
		newptr      = other.m_ptr;
		other.m_ptr = __NULLPTR;
		oldptr      = this->m_ptr;
		this->m_ptr = newptr;
		if (oldptr)
			rm::decref(oldptr);
		return *this;
	}
};


#define ERROR_MESSAGE_AUTOPTR(funcname) "Don't use " funcname "() with refptr<T>"
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("decref")) void decref(refptr<T> const&);
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("decref_nokill")) void decref_nokill(refptr<T> const&);
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("decref_likely")) void decref_likely(refptr<T> const&);
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("decref_unlikely")) void decref_unlikely(refptr<T> const&);
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("xdecref")) void xdecref(refptr<T> const&);
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("xdecref_likely")) void xdecref_likely(refptr<T> const&);
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("xdecref_unlikely")) void xdecref_unlikely(refptr<T> const&);
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("incref")) T *incref(refptr<T> const&);
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("xincref")) T *xincref(refptr<T> const&);
template<class T> ATTR_ERROR(ERROR_MESSAGE_AUTOPTR("tryincref")) __BOOL tryincref(refptr<T> const&);
#undef ERROR_MESSAGE_AUTOPTR
template<class T> void destroy(refptr<T> &self) {
	refptr<T>::rm::destroy(self.release());
}





}

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_MISC_REFPTR_H */
