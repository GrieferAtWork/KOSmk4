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

#include "typecore.h"
#include "../__stdcxx.h"

extern "C++" {
__NAMESPACE_INT_BEGIN

#ifndef __POINTER_CXX_CV_QUAL
#define __POINTER_CXX_CV_QUAL /* nothing */
#endif /* !__POINTER_CXX_CV_QUAL */


template<
#ifndef __POINTER_CXX_IS_VOID
	class __PTR_T,
#endif /* !__POINTER_CXX_IS_VOID */
	class __I
>
class __hybrid_ptr
#ifdef __POINTER_CXX_IS_VOID
#define __PTR_T void
	<void __POINTER_CXX_CV_QUAL, __I>
#elif (defined(__POINTER_CXX_CV_QUAL_IS_CONST) || \
       defined(__POINTER_CXX_CV_QUAL_IS_VOLATILE))
	<__PTR_T __POINTER_CXX_CV_QUAL, __I>
#endif
{
private:
	__I __m_ptr;
public:
	/* Construct as uninitialized */
	__CXX_CLASSMEMBER __CXX_DEFAULT_CTOR_NOEXCEPT(__hybrid_ptr);

	/* Default copy/move constructor/assign */
#ifdef __COMPILER_HAVE_CXX_DEFAULT_FUNCTIONS
	__CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr const &__val) __CXX_NOEXCEPT = default;
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr const &__val) __CXX_NOEXCEPT = default;
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr &&__val) __CXX_NOEXCEPT = default;
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr &&__val) __CXX_NOEXCEPT = default;
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#else /* __COMPILER_HAVE_CXX_DEFAULT_FUNCTIONS */
	__CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr const &__val) __CXX_NOEXCEPT: __m_ptr(__val.__m_ptr) {}
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr const &__val) __CXX_NOEXCEPT { __m_ptr = __val.__m_ptr; return *this; }
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr &&__val) __CXX_NOEXCEPT: __m_ptr(__val.__m_ptr) {}
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr &&__val) __CXX_NOEXCEPT { __m_ptr = __val.__m_ptr; return *this; }
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#endif /* !__COMPILER_HAVE_CXX_DEFAULT_FUNCTIONS */

	/* Construct from integer (explicit) */
	__CXX_CLASSMEMBER explicit __hybrid_ptr(signed char __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(unsigned char __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(short __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(unsigned short __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(int __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(unsigned int __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(long __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(unsigned long __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
#ifdef __COMPILER_HAVE_LONGLONG
	__CXX_CLASSMEMBER explicit __hybrid_ptr(long long __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(unsigned long long __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
	__CXX_CLASSMEMBER explicit __hybrid_ptr(__int8 __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(unsigned __int8 __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
	__CXX_CLASSMEMBER explicit __hybrid_ptr(__int16 __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(unsigned __int16 __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
	__CXX_CLASSMEMBER explicit __hybrid_ptr(__int32 __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(unsigned __int32 __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
	__CXX_CLASSMEMBER explicit __hybrid_ptr(__int64 __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
	__CXX_CLASSMEMBER explicit __hybrid_ptr(unsigned __int64 __val) __CXX_NOEXCEPT: __m_ptr((__I)__val) {}
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

	/* Convert to integer (explicit) */
	__CXX_CLASSMEMBER explicit operator signed char() const __CXX_NOEXCEPT { return (signed char)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator unsigned char() const __CXX_NOEXCEPT { return (unsigned char)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator short() const __CXX_NOEXCEPT { return (short)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator unsigned short() const __CXX_NOEXCEPT { return (unsigned short)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator int() const __CXX_NOEXCEPT { return (int)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator unsigned int() const __CXX_NOEXCEPT { return (unsigned int)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator long() const __CXX_NOEXCEPT { return (long)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator unsigned long() const __CXX_NOEXCEPT { return (unsigned long)__m_ptr; }
#ifdef __COMPILER_HAVE_LONGLONG
	__CXX_CLASSMEMBER explicit operator long long() const __CXX_NOEXCEPT { return (long long)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator unsigned long long() const __CXX_NOEXCEPT { return (unsigned long long)__m_ptr; }
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
	__CXX_CLASSMEMBER explicit operator __int8() const __CXX_NOEXCEPT { return (__int8)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator unsigned __int8() const __CXX_NOEXCEPT { return (unsigned __int8)__m_ptr; }
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
	__CXX_CLASSMEMBER explicit operator __int16() const __CXX_NOEXCEPT { return (__int16)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator unsigned __int16() const __CXX_NOEXCEPT { return (unsigned __int16)__m_ptr; }
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
	__CXX_CLASSMEMBER explicit operator __int32() const __CXX_NOEXCEPT { return (__int32)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator unsigned __int32() const __CXX_NOEXCEPT { return (unsigned __int32)__m_ptr; }
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
	__CXX_CLASSMEMBER explicit operator __int64() const __CXX_NOEXCEPT { return (__int64)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator unsigned __int64() const __CXX_NOEXCEPT { return (unsigned __int64)__m_ptr; }
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

	/* Convert to normal pointer (explicit when casting away const/volatile) */
	__CXX_CLASSMEMBER operator __PTR_T __POINTER_CXX_CV_QUAL *() const __CXX_NOEXCEPT { return (__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr; }
	__CXX_CLASSMEMBER operator __PTR_T __POINTER_CXX_CV_QUAL *() const volatile __CXX_NOEXCEPT { return (__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr; }
#if defined(__POINTER_CXX_CV_QUAL_IS_CONST) && defined(__POINTER_CXX_CV_QUAL_IS_VOLATILE)
	__CXX_CLASSMEMBER explicit operator __PTR_T *() const __CXX_NOEXCEPT { return (__PTR_T *)(__UINTPTR_TYPE__)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator __PTR_T *() const volatile __CXX_NOEXCEPT { return (__PTR_T *)(__UINTPTR_TYPE__)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator __PTR_T const *() const __CXX_NOEXCEPT { return (__PTR_T const *)(__UINTPTR_TYPE__)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator __PTR_T const *() const volatile __CXX_NOEXCEPT { return (__PTR_T const *)(__UINTPTR_TYPE__)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator __PTR_T volatile *() const __CXX_NOEXCEPT { return (__PTR_T volatile *)(__UINTPTR_TYPE__)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator __PTR_T volatile *() const volatile __CXX_NOEXCEPT { return (__PTR_T volatile *)(__UINTPTR_TYPE__)__m_ptr; }
#elif defined(__POINTER_CXX_CV_QUAL_IS_CONST) || defined(__POINTER_CXX_CV_QUAL_IS_VOLATILE)
	__CXX_CLASSMEMBER explicit operator __PTR_T *() const __CXX_NOEXCEPT { return (__PTR_T *)(__UINTPTR_TYPE__)__m_ptr; }
	__CXX_CLASSMEMBER explicit operator __PTR_T *() const volatile __CXX_NOEXCEPT { return (__PTR_T *)(__UINTPTR_TYPE__)__m_ptr; }
#endif /* ... */

#ifdef __POINTER_CXX_IS_VOID
#ifdef __COMPILER_HAVE_VOID_ARITHMETIC
	/* Emulate a size of 1 for `void' when the compiler support pointer arithmetic */
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator+(__PTRDIFF_TYPE__ __index) const __CXX_NOEXCEPT { return (__PTR_T __POINTER_CXX_CV_QUAL *)((__UINTPTR_TYPE__)__m_ptr + __index); }
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator+(__PTRDIFF_TYPE__ __index) const volatile __CXX_NOEXCEPT { return (__PTR_T __POINTER_CXX_CV_QUAL *)((__UINTPTR_TYPE__)__m_ptr + __index); }
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator-(__PTRDIFF_TYPE__ __index) const __CXX_NOEXCEPT { return (__PTR_T __POINTER_CXX_CV_QUAL *)((__UINTPTR_TYPE__)__m_ptr - __index); }
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator-(__PTRDIFF_TYPE__ __index) const volatile __CXX_NOEXCEPT { return (__PTR_T __POINTER_CXX_CV_QUAL *)((__UINTPTR_TYPE__)__m_ptr - __index); }
	__CXX_CLASSMEMBER __hybrid_ptr &operator+=(__PTRDIFF_TYPE__ __index) __CXX_NOEXCEPT { __m_ptr += __index; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator+=(__PTRDIFF_TYPE__ __index) volatile __CXX_NOEXCEPT { __m_ptr += __index; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr &operator-=(__PTRDIFF_TYPE__ __index) __CXX_NOEXCEPT { __m_ptr -= __index; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator-=(__PTRDIFF_TYPE__ __index) volatile __CXX_NOEXCEPT { __m_ptr -= __index; return *this; }
#endif /* __COMPILER_HAVE_VOID_ARITHMETIC */
#else /* __POINTER_CXX_IS_VOID */
	/* Arrow-operator */
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator->() const __CXX_NOEXCEPT { return (__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr; }
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator->() const volatile __CXX_NOEXCEPT { return (__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr; }

	/* Pointer dereferencing */
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL &operator*() const __CXX_NOEXCEPT { return *(__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr; }
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL &operator*() const volatile __CXX_NOEXCEPT { return *(__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr; }

	/* Array operator */
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL &operator[](__PTRDIFF_TYPE__ __index) const __CXX_NOEXCEPT { return ((__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr)[__index]; }
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL &operator[](__PTRDIFF_TYPE__ __index) const volatile __CXX_NOEXCEPT { return ((__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr)[__index]; }

	/* Pointer element add/subtract */
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator+(__PTRDIFF_TYPE__ __index) const __CXX_NOEXCEPT { return ((__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr) + __index; }
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator+(__PTRDIFF_TYPE__ __index) const volatile __CXX_NOEXCEPT { return ((__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr) + __index; }
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator-(__PTRDIFF_TYPE__ __index) const __CXX_NOEXCEPT { return ((__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr) - __index; }
	__CXX_CLASSMEMBER __PTR_T __POINTER_CXX_CV_QUAL *operator-(__PTRDIFF_TYPE__ __index) const volatile __CXX_NOEXCEPT { return ((__PTR_T __POINTER_CXX_CV_QUAL *)(__UINTPTR_TYPE__)__m_ptr) - __index; }

	/* Inplace pointer element add/subtract */
	__CXX_CLASSMEMBER __hybrid_ptr &operator+=(__PTRDIFF_TYPE__ __index) __CXX_NOEXCEPT { __m_ptr += __index * sizeof(__PTR_T); return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator+=(__PTRDIFF_TYPE__ __index) volatile __CXX_NOEXCEPT { __m_ptr += __index * sizeof(__PTR_T); return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr &operator-=(__PTRDIFF_TYPE__ __index) __CXX_NOEXCEPT { __m_ptr -= __index * sizeof(__PTR_T); return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator-=(__PTRDIFF_TYPE__ __index) volatile __CXX_NOEXCEPT { __m_ptr -= __index * sizeof(__PTR_T); return *this; }
#endif /* !__POINTER_CXX_IS_VOID */

	/* Construct/Assign from pointer (explicit/disallowed when const/volatile is lost) */
#if defined(__POINTER_CXX_CV_QUAL_IS_CONST) && defined(__POINTER_CXX_CV_QUAL_IS_VOLATILE)
	__CXX_CLASSMEMBER __hybrid_ptr(__PTR_T *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	__CXX_CLASSMEMBER __hybrid_ptr(__PTR_T const *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	__CXX_CLASSMEMBER __hybrid_ptr(__PTR_T volatile *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	__CXX_CLASSMEMBER __hybrid_ptr(__PTR_T const volatile *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T const, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T const, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T volatile, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T const volatile, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__PTR_T *__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__PTR_T const *__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__PTR_T volatile *__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__PTR_T const volatile *__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__PTR_T *__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__PTR_T const *__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__PTR_T volatile *__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__PTR_T const volatile *__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T, __I2> const &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T const, __I2> const &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T const, __I2> const volatile &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T volatile, __I2> const &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T const volatile, __I2> const &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T, __I2> const &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T const, __I2> const &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T const, __I2> const volatile &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T volatile, __I2> const &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T const volatile, __I2> const &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
#elif defined(__POINTER_CXX_CV_QUAL_IS_CONST)
	__CXX_CLASSMEMBER __hybrid_ptr(__PTR_T *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	__CXX_CLASSMEMBER __hybrid_ptr(__PTR_T const *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	explicit __CXX_CLASSMEMBER __hybrid_ptr(__PTR_T volatile *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	explicit __CXX_CLASSMEMBER __hybrid_ptr(__PTR_T const volatile *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T const, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T const, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T volatile, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const volatile, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__PTR_T *__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__PTR_T const *__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__PTR_T *__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__PTR_T const *__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T, __I2> const &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T const, __I2> const &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T const, __I2> const volatile &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T, __I2> const &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T const, __I2> const &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T const, __I2> const volatile &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
#elif defined(__POINTER_CXX_CV_QUAL_IS_VOLATILE)
	__CXX_CLASSMEMBER __hybrid_ptr(__PTR_T *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	explicit __CXX_CLASSMEMBER __hybrid_ptr(__PTR_T const *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	__CXX_CLASSMEMBER __hybrid_ptr(__PTR_T volatile *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	explicit __CXX_CLASSMEMBER __hybrid_ptr(__PTR_T const volatile *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T volatile, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const volatile, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__PTR_T *__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__PTR_T volatile *__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__PTR_T *__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__PTR_T volatile *__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T, __I2> const &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T volatile, __I2> const &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T, __I2> const &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T volatile, __I2> const &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
#else /* ... */
	__CXX_CLASSMEMBER __hybrid_ptr(__PTR_T *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	explicit __CXX_CLASSMEMBER __hybrid_ptr(__PTR_T const *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	explicit __CXX_CLASSMEMBER __hybrid_ptr(__PTR_T volatile *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	explicit __CXX_CLASSMEMBER __hybrid_ptr(__PTR_T const volatile *__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T volatile, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const volatile, __I2> const &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	template<class __I2> __CXX_CLASSMEMBER explicit __hybrid_ptr(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__val) __CXX_NOEXCEPT: __m_ptr((__I)(__UINTPTR_TYPE__)(__PTR_T *)__val) {}
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(__PTR_T *__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__PTR_T *__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T, __I2> const &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr &operator=(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T, __I2> const &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
	template<class __I2> __CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(__hybrid_ptr<__PTR_T, __I2> const volatile &__val) volatile __CXX_NOEXCEPT { __m_ptr = (__I)(__UINTPTR_TYPE__)(__PTR_T *)__val; return *this; }
#endif /* !... */

	/* Pointer difference operators */
#ifdef __POINTER_CXX_IS_VOID
#ifdef __COMPILER_HAVE_VOID_ARITHMETIC
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T *__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)__rhs); }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T const *__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)__rhs); }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T volatile *__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)__rhs); }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T const volatile *__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)__rhs); }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T *__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)__rhs); }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T const *__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)__rhs); }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T volatile *__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)__rhs); }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T const volatile *__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T, __I2> const &__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T, __I2> const volatile &__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T, __I2> const &__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T, __I2> const volatile &__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const, __I2> const &__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const, __I2> const volatile &__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const, __I2> const &__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const, __I2> const volatile &__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T volatile, __I2> const &__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T volatile, __I2> const &__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const volatile, __I2> const &__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__rhs) const __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const volatile, __I2> const &__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__rhs) const volatile __CXX_NOEXCEPT { return (__PTRDIFF_TYPE__)((__UINTPTR_TYPE__)__m_ptr - (__UINTPTR_TYPE__)(__PTR_T *)__rhs); }
#endif /* __COMPILER_HAVE_VOID_ARITHMETIC */
#else /* __POINTER_CXX_IS_VOID */
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T *__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - __rhs; }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T const *__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - __rhs; }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T volatile *__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - __rhs; }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T const volatile *__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - __rhs; }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T *__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - __rhs; }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T const *__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - __rhs; }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T volatile *__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - __rhs; }
	__CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__PTR_T const volatile *__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - __rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T, __I2> const &__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T, __I2> const volatile &__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T, __I2> const &__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T, __I2> const volatile &__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const, __I2> const &__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const, __I2> const volatile &__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const, __I2> const &__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const, __I2> const volatile &__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T volatile, __I2> const &__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T volatile, __I2> const &__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T volatile, __I2> const volatile &__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const volatile, __I2> const &__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__rhs) const __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const volatile, __I2> const &__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
	template<class __I2> __CXX_CLASSMEMBER __PTRDIFF_TYPE__ operator-(__hybrid_ptr<__PTR_T const volatile, __I2> const volatile &__rhs) const volatile __CXX_NOEXCEPT { return ((__PTR_T *)(__UINTPTR_TYPE__)__m_ptr) - (__PTR_T *)__rhs; }
#endif /* !__POINTER_CXX_IS_VOID */

#if defined(__COMPILER_HAVE_CXX_NULLPTR) && defined(__COMPILER_HAVE_CXX_DECLTYPE)
	/* Operate with nullptr_t */
	__CXX_CLASSMEMBER __hybrid_ptr(decltype(nullptr)) __CXX_NOEXCEPT: __m_ptr(0) {}
	__CXX_CLASSMEMBER __hybrid_ptr &operator=(decltype(nullptr)) __CXX_NOEXCEPT { __m_ptr = 0; return *this; }
	__CXX_CLASSMEMBER __hybrid_ptr volatile &operator=(decltype(nullptr)) volatile __CXX_NOEXCEPT { __m_ptr = 0; return *this; }
#endif /* __COMPILER_HAVE_CXX_NULLPTR && __COMPILER_HAVE_CXX_DECLTYPE */
};


__NAMESPACE_INT_END
} /* extern "C++" */

#undef __PTR_T
#undef __POINTER_CXX_IS_VOID
#undef __POINTER_CXX_CV_QUAL_IS_VOLATILE
#undef __POINTER_CXX_CV_QUAL_IS_CONST
#undef __POINTER_CXX_CV_QUAL

