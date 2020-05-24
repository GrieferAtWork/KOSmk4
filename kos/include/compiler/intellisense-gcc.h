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
#ifndef ____INTELLISENSE_STDINC_SYNTAX_GCC_H
#define ____INTELLISENSE_STDINC_SYNTAX_GCC_H 1
#undef clang
#undef __clang
#undef __clang__

/*
 * While the `linux-gcc-x86' intellisense driver is _extremely_ welcome if you ask me,
 * there are still a couple of things that it does wrong when compared against the real
 * deal. - Fix those in here!.
 * Also: Implement the common intellisense types used to implement alternate integral
 *       types, as well as endian-restricted integers.
 */

#include "intellisense-common.h"

/* Native GCC support in intellisense */
#define __INTELLISENSE_GCC__ 1

#ifdef __KOS__
#undef linux
#undef __linux
#undef __linux__
#undef _WIN32
#undef _WIN64
#undef _M_AMD64
#undef _M_X64
#undef _M_IX86

#undef __GNUC__
#undef __GNUC_MINOR__
#undef __GNUC_PATCH__
#define __GNUC__        9
#define __GNUC_MINOR__  1
#define __GNUC_PATCH__  0
#endif /* __KOS__ */

#ifndef __x86_64__ /* WARNING: This breaks `operator ""s' and `operator new()' for intellisense */
#undef __SIZE_TYPE__
#define __SIZE_TYPE__  unsigned long int
#endif /* !__x86_64__ */

#ifdef __x86_64__
#if 0 /* How can Intellisense be this stupid? - I mean: this is linux 101! */
static_assert(sizeof(long) == 8, "WTF Intellisense?");
static_assert(sizeof(__INT64_TYPE__) == 8, "WTF Intellisense?");
static_assert(sizeof(__UINT64_TYPE__) == 8, "WTF Intellisense?");
static_assert(sizeof(__INTPTR_TYPE__) == 8, "WTF Intellisense?");
static_assert(sizeof(__UINTPTR_TYPE__) == 8, "WTF Intellisense?");
static_assert(sizeof(__INTMAX_TYPE__) >= 8, "WTF Intellisense?");
static_assert(sizeof(__UINTMAX_TYPE__) >= 8, "WTF Intellisense?");
static_assert(sizeof(__INT_LEAST64_TYPE__) >= 8, "WTF Intellisense?");
static_assert(sizeof(__UINT_LEAST64_TYPE__) >= 8, "WTF Intellisense?");
static_assert(sizeof(__INT_FAST16_TYPE__) == __SIZEOF_FAST16_TYPE__, "WTF Intellisense?");
static_assert(sizeof(__INT_FAST32_TYPE__) == __SIZEOF_FAST32_TYPE__, "WTF Intellisense?");
static_assert(sizeof(__INT_FAST64_TYPE__) == __SIZEOF_FAST64_TYPE__, "WTF Intellisense?");
static_assert(sizeof(__UINT_FAST16_TYPE__) == __SIZEOF_FAST16_TYPE__, "WTF Intellisense?");
static_assert(sizeof(__UINT_FAST32_TYPE__) == __SIZEOF_FAST32_TYPE__, "WTF Intellisense?");
static_assert(sizeof(__UINT_FAST64_TYPE__) == __SIZEOF_FAST64_TYPE__, "WTF Intellisense?");
#else
#undef __SIZEOF_LONG__
#define __SIZEOF_LONG__ 4

#undef __INT64_TYPE__
#define __INT64_TYPE__   signed long long int
#undef __UINT64_TYPE__
#define __UINT64_TYPE__  unsigned long long int

#undef __INTPTR_TYPE__
#define __INTPTR_TYPE__  signed long long int
#undef __UINTPTR_TYPE__
#define __UINTPTR_TYPE__ unsigned long long int

#undef __INTMAX_TYPE__
#define __INTMAX_TYPE__  signed long long int
#undef __UINTMAX_TYPE__
#define __UINTMAX_TYPE__ unsigned long long int

#undef __INT_LEAST64_TYPE__
#define __INT_LEAST64_TYPE__  signed long long int
#undef __UINT_LEAST64_TYPE__
#define __UINT_LEAST64_TYPE__ unsigned long long int

#undef __INT_FAST16_TYPE__
#define __INT_FAST16_TYPE__  signed long long int
#undef __UINT_FAST16_TYPE__
#define __UINT_FAST16_TYPE__ unsigned long long int

#undef __INT_FAST32_TYPE__
#define __INT_FAST32_TYPE__  signed long long int
#undef __UINT_FAST32_TYPE__
#define __UINT_FAST32_TYPE__ unsigned long long int

#undef __INT_FAST64_TYPE__
#define __INT_FAST64_TYPE__  signed long long int
#undef __UINT_FAST64_TYPE__
#define __UINT_FAST64_TYPE__ unsigned long long int

#endif
#elif defined(__i386__)
/* Intellisense incorrectly indicates that gcc for i386 defaults
 * to having SSE math enabled. */
#undef __SSE2_MATH__
#undef __SSE2__
#undef __SSE_MATH__
#undef __SSE__
#endif /* __x86_64__ */


#if 0 /* How can Intellisense be this stupid? - I mean: this is linux 101! */
static_assert(sizeof(wchar_t) == __SIZEOF_WCHAR_T__, "WTF Intellisense?");
#else
/* This isn't really correct, either. wchar_t on linux is 4 bytes, however we
 * can't really change sizeof(xxx) using preprocessor directives, to the best
 * we _can_ do is change intellisense to at least be consistent with itself... */
#undef __SIZEOF_WCHAR_T__
#define __SIZEOF_WCHAR_T__ 2
#endif

#undef _GNU_SOURCE /* For some reason, this gets pre-defined... */

#define _Thread_local __thread

#define __seg_fs /* nothing */
#define __seg_gs /* nothing */
#define __SEG_FS 1
#define __SEG_GS 1

#if __cplusplus == 201406L
#undef __cplusplus
#define __cplusplus 201402L
#endif

#if __cplusplus == 201402L
#undef __cpp_deduction_guides
#endif


namespace __intern {

/* Intellisense doesn't emulate `__int128' properly (or rather: at all; it only
 * defines the `__SIZEOF_INT128__' feature test macro, but don't actually care to
 * implement the actual feature it is used to test for... ~ugh~)
 * -> So try to fix that _BUG_! Because that's totally what it is, and not
 *    just the vs developers being lazy. Oh no, it totally isn't that they
 *    probably just copied a list of gcc's predefined macros and called it
 *    a day without actually going through all of them and checking that they're
 *    actually doing what they're supposed to do.
 * I mean: How else do you think not only something like this happened, but
 * also something like `__INT64_TYPE__' not actually being 64-bit because its
 * default definition is (just like it is in gcc) `signed long int' (again:
 * Intellisense continues to define `long int' as 32-bit, instead of defining
 * it as pointer-sized) */
#ifdef __SIZEOF_INT128__
class __intellisense_int128;
class __intellisense_uint128;
template<> struct ____INTELLISENSE_issigned<__intellisense_int128> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isunsigned<__intellisense_uint128> { enum { __value = true }; };
class __attribute__((__aligned__(16))) __intellisense_int128 {
private:
	signed char __data[__SIZEOF_INT128__];
public:
	__intellisense_int128() throw() = default;
	__intellisense_int128(__intellisense_int128 const &) throw() = default;
	__intellisense_int128(__intellisense_int128 &&) throw() = default;
	__intellisense_int128(bool) throw();
	__intellisense_int128(char) throw();
	__intellisense_int128(signed char) throw();
	__intellisense_int128(unsigned char) throw();
	__intellisense_int128(short) throw();
	__intellisense_int128(unsigned short) throw();
	__intellisense_int128(int) throw();
	__intellisense_int128(unsigned int) throw();
	__intellisense_int128(long) throw();
	__intellisense_int128(unsigned long) throw();
	__intellisense_int128(long long) throw();
	__intellisense_int128(unsigned long long) throw();
	__intellisense_int128(wchar_t) throw();
	__intellisense_int128(__intellisense_uint128) throw();
	__intellisense_int128 &operator = (__intellisense_int128 const &) throw();
	__intellisense_int128 &operator = (__intellisense_int128 &&) throw();
	__intellisense_int128 &operator = (bool) throw();
	__intellisense_int128 &operator = (char) throw();
	__intellisense_int128 &operator = (signed char) throw();
	__intellisense_int128 &operator = (unsigned char) throw();
	__intellisense_int128 &operator = (short) throw();
	__intellisense_int128 &operator = (unsigned short) throw();
	__intellisense_int128 &operator = (int) throw();
	__intellisense_int128 &operator = (unsigned int) throw();
	__intellisense_int128 &operator = (long) throw();
	__intellisense_int128 &operator = (unsigned long) throw();
	__intellisense_int128 &operator = (long long) throw();
	__intellisense_int128 &operator = (unsigned long long) throw();
	__intellisense_int128 &operator = (wchar_t) throw();
	__intellisense_int128 &operator = (__intellisense_uint128) throw();
	__intellisense_int128 &operator++() throw();
	__intellisense_int128 &operator--() throw();
	__intellisense_int128 operator++(int) throw();
	__intellisense_int128 operator--(int) throw();
	__intellisense_int128 operator<<(unsigned int) const throw();
	__intellisense_int128 operator>>(unsigned int) const throw();
	__intellisense_int128 operator-() const throw();
	__intellisense_int128 operator~() const throw();
	__intellisense_int128 &operator<<=(unsigned int) throw();
	__intellisense_int128 &operator>>=(unsigned int) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128>::__type operator + (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128>::__type operator - (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128>::__type operator * (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128>::__type operator / (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128>::__type operator % (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128>::__type operator & (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128>::__type operator | (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128>::__type operator ^ (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128 &>::__type operator += (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128 &>::__type operator -= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128 &>::__type operator *= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128 &>::__type operator /= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128 &>::__type operator %= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128 &>::__type operator &= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128 &>::__type operator |= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_int128 &>::__type operator ^= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator == (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator != (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator < (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator > (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator <= (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator >= (__VT const &) const throw();
	bool operator!() const throw();
	operator bool() const throw();
	operator char() const throw();
	operator signed char() const throw();
	operator unsigned char() const throw();
	operator short() const throw();
	operator unsigned short() const throw();
	operator int() const throw();
	operator unsigned int() const throw();
	operator long() const throw();
	operator unsigned long() const throw();
	operator long long() const throw();
	operator unsigned long long() const throw();
	operator wchar_t() const throw();
	operator __intellisense_uint128() const throw();
#if defined(_WCHAR_T_DEFINED) || defined(__GNUC__)
	__intellisense_int128(char16_t) throw();
	__intellisense_int128(char32_t) throw();
	operator char16_t() const throw();
	operator char32_t() const throw();
#endif /* _WCHAR_T_DEFINED || __GNUC__ */
};

class __attribute__((__aligned__(16))) __intellisense_uint128 {
private:
	unsigned char __data[__SIZEOF_INT128__];
public:
	__intellisense_uint128() throw() = default;
	__intellisense_uint128(__intellisense_uint128 const &) throw() = default;
	__intellisense_uint128(__intellisense_uint128 &&) throw() = default;
	__intellisense_uint128(bool) throw();
	__intellisense_uint128(char) throw();
	__intellisense_uint128(signed char) throw();
	__intellisense_uint128(unsigned char) throw();
	__intellisense_uint128(short) throw();
	__intellisense_uint128(unsigned short) throw();
	__intellisense_uint128(int) throw();
	__intellisense_uint128(unsigned int) throw();
	__intellisense_uint128(long) throw();
	__intellisense_uint128(unsigned long) throw();
	__intellisense_uint128(long long) throw();
	__intellisense_uint128(unsigned long long) throw();
	__intellisense_uint128(wchar_t) throw();
	__intellisense_uint128(__intellisense_int128) throw();
	__intellisense_uint128 &operator = (__intellisense_uint128 const &) throw();
	__intellisense_uint128 &operator = (__intellisense_uint128 &&) throw();
	__intellisense_uint128 &operator = (bool) throw();
	__intellisense_uint128 &operator = (char) throw();
	__intellisense_uint128 &operator = (signed char) throw();
	__intellisense_uint128 &operator = (unsigned char) throw();
	__intellisense_uint128 &operator = (short) throw();
	__intellisense_uint128 &operator = (unsigned short) throw();
	__intellisense_uint128 &operator = (int) throw();
	__intellisense_uint128 &operator = (unsigned int) throw();
	__intellisense_uint128 &operator = (long) throw();
	__intellisense_uint128 &operator = (unsigned long) throw();
	__intellisense_uint128 &operator = (long long) throw();
	__intellisense_uint128 &operator = (unsigned long long) throw();
	__intellisense_uint128 &operator = (wchar_t) throw();
	__intellisense_uint128 &operator = (__intellisense_int128) throw();
	__intellisense_uint128 &operator++() throw();
	__intellisense_uint128 &operator--() throw();
	__intellisense_uint128 operator++(int) throw();
	__intellisense_uint128 operator--(int) throw();
	__intellisense_uint128 operator<<(unsigned int) const throw();
	__intellisense_uint128 operator>>(unsigned int) const throw();
	__intellisense_uint128 operator~() const throw();
	__intellisense_uint128 &operator<<=(unsigned int) throw();
	__intellisense_uint128 &operator>>=(unsigned int) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128>::__type operator + (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128>::__type operator - (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128>::__type operator * (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128>::__type operator / (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128>::__type operator % (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128>::__type operator & (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128>::__type operator | (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128>::__type operator ^ (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128 &>::__type operator += (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128 &>::__type operator -= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128 &>::__type operator *= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128 &>::__type operator /= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128 &>::__type operator %= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128 &>::__type operator &= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128 &>::__type operator |= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, __intellisense_uint128 &>::__type operator ^= (__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator == (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator != (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator < (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator > (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator <= (__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value, bool>::__type operator >= (__VT const &) const throw();
	bool operator!() const throw();
	operator bool() const throw();
	operator char() const throw();
	operator signed char() const throw();
	operator unsigned char() const throw();
	operator short() const throw();
	operator unsigned short() const throw();
	operator int() const throw();
	operator unsigned int() const throw();
	operator long() const throw();
	operator unsigned long() const throw();
	operator long long() const throw();
	operator unsigned long long() const throw();
	operator wchar_t() const throw();
	operator __intellisense_int128() const throw();
#if defined(_WCHAR_T_DEFINED) || defined(__GNUC__)
	__intellisense_uint128(char16_t) throw();
	__intellisense_uint128(char32_t) throw();
	operator char16_t() const throw();
	operator char32_t() const throw();
#endif /* _WCHAR_T_DEFINED || __GNUC__ */
};
} /* namespace __intern */
#define __INT128_TYPE__  ::__intern::__intellisense_int128
#define __UINT128_TYPE__ ::__intern::__intellisense_uint128
template<class __T> __T *operator+(__T *, __INT128_TYPE__ const &) throw();
template<class __T> __T *operator-(__T *, __INT128_TYPE__ const &) throw();
template<class __T> __T *operator+(__T *, __UINT128_TYPE__ const &) throw();
template<class __T> __T *operator-(__T *, __UINT128_TYPE__ const &) throw();
namespace __intern {
#endif /* __SIZEOF_INT128__ */

unsigned short __override_builtin_bswap16(unsigned short);
____intellisense_endianint<4321, unsigned short> __override_builtin_bswap16(____intellisense_endianint<1234, unsigned short>);
____intellisense_endianint<1234, unsigned short> __override_builtin_bswap16(____intellisense_endianint<4321, unsigned short>);
unsigned int __override_builtin_bswap32(unsigned int);
____intellisense_endianint<4321, unsigned int> __override_builtin_bswap32(____intellisense_endianint<1234, unsigned int>);
____intellisense_endianint<1234, unsigned int> __override_builtin_bswap32(____intellisense_endianint<4321, unsigned int>);
#if defined(__i386__) || defined(__arm__)
unsigned long __override_builtin_bswap32(unsigned long);
____intellisense_endianint<4321, unsigned long> __override_builtin_bswap32(____intellisense_endianint<1234, unsigned long>);
____intellisense_endianint<1234, unsigned long> __override_builtin_bswap32(____intellisense_endianint<4321, unsigned long>);
#else
unsigned long __override_builtin_bswap64(unsigned long);
____intellisense_endianint<4321, unsigned long> __override_builtin_bswap64(____intellisense_endianint<1234, unsigned long>);
____intellisense_endianint<1234, unsigned long> __override_builtin_bswap64(____intellisense_endianint<4321, unsigned long>);
#endif
unsigned long long __override_builtin_bswap64(unsigned long long);
____intellisense_endianint<4321, unsigned long long> __override_builtin_bswap64(____intellisense_endianint<1234, unsigned long long>);
____intellisense_endianint<1234, unsigned long long> __override_builtin_bswap64(____intellisense_endianint<4321, unsigned long long>);
#define __builtin_bswap16 ::__intern::__override_builtin_bswap16
#define __builtin_bswap32 ::__intern::__override_builtin_bswap32
#define __builtin_bswap32 ::__intern::__override_builtin_bswap32
#define __builtin_bswap64 ::__intern::__override_builtin_bswap64



template<class T> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value, T>::__type __intellisense_atomic_load_n(T const volatile *ptr, int memorder);
template<class T> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value, void>::__type __intellisense_atomic_load(T const volatile *ptr, T *ret, int memorder);
template<class T> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value, void>::__type __intellisense_atomic_load(T const volatile *ptr, T volatile *ret, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, void>::__type __intellisense_atomic_store_n(T volatile *ptr, S val, int memorder);
template<class T> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value, void>::__type __intellisense_atomic_store(T volatile *ptr, T *val, int memorder);
template<class T> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value, void>::__type __intellisense_atomic_store(T volatile *ptr, T volatile *val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_exchange_n(T volatile *ptr, S val, int memorder);
template<class T> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value, void>::__type __intellisense_atomic_exchange(T volatile *ptr, T *val, T *ret, int memorder);
template<class T> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value, void>::__type __intellisense_atomic_exchange(T volatile *ptr, T volatile *val, T volatile *ret, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, bool>::__type __intellisense_atomic_compare_exchange_n(T volatile *ptr, T *expected, S desired, bool weak, int success_memorder, int failure_memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, bool>::__type __intellisense_atomic_compare_exchange_n(T volatile *ptr, T volatile *expected, S desired, bool weak, int success_memorder, int failure_memorder);
template<class T> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value, bool>::__type __intellisense_atomic_compare_exchange(T volatile *ptr, T *expected, T *desired, bool weak, int success_memorder, int failure_memorder);
template<class T> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value, bool>::__type __intellisense_atomic_compare_exchange(T volatile *ptr, T volatile *expected, T volatile *desired, bool weak, int success_memorder, int failure_memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_add_fetch(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_sub_fetch(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_and_fetch(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_xor_fetch(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_or_fetch(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_nand_fetch(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_fetch_add(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_fetch_sub(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_fetch_and(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_fetch_xor(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_fetch_or(T volatile *ptr, S val, int memorder);
template<class T, class S> typename ____INTELLISENSE_enableif<____INTELLISENSE_isarith<T>::__value && ____INTELLISENSE_isarith<S>::__value, T>::__type __intellisense_atomic_fetch_nand(T volatile *ptr, S val, int memorder);

#define __atomic_load_n             ::__intern::__intellisense_atomic_load_n
#define __atomic_load               ::__intern::__intellisense_atomic_load
#define __atomic_store_n            ::__intern::__intellisense_atomic_store_n
#define __atomic_store              ::__intern::__intellisense_atomic_store
#define __atomic_exchange_n         ::__intern::__intellisense_atomic_exchange_n
#define __atomic_exchange           ::__intern::__intellisense_atomic_exchange
#define __atomic_compare_exchange_n ::__intern::__intellisense_atomic_compare_exchange_n
#define __atomic_compare_exchange   ::__intern::__intellisense_atomic_compare_exchange
#define __atomic_add_fetch          ::__intern::__intellisense_atomic_add_fetch
#define __atomic_sub_fetch          ::__intern::__intellisense_atomic_sub_fetch
#define __atomic_and_fetch          ::__intern::__intellisense_atomic_and_fetch
#define __atomic_xor_fetch          ::__intern::__intellisense_atomic_xor_fetch
#define __atomic_or_fetch           ::__intern::__intellisense_atomic_or_fetch
#define __atomic_nand_fetch         ::__intern::__intellisense_atomic_nand_fetch
#define __atomic_fetch_add          ::__intern::__intellisense_atomic_fetch_add
#define __atomic_fetch_sub          ::__intern::__intellisense_atomic_fetch_sub
#define __atomic_fetch_and          ::__intern::__intellisense_atomic_fetch_and
#define __atomic_fetch_xor          ::__intern::__intellisense_atomic_fetch_xor
#define __atomic_fetch_or           ::__intern::__intellisense_atomic_fetch_or
#define __atomic_fetch_nand         ::__intern::__intellisense_atomic_fetch_nand


#if 0 /* How can Intellisense be this stupid? - I mean: this is linux 101! */
static_assert(sizeof(long double) == __SIZEOF_LONG_DOUBLE__, "WTF Intellisense?");
#elif 1

#ifndef __SIZEOF_LONG_DOUBLE__
#ifdef __i386__
#define __SIZEOF_LONG_DOUBLE__ 12
#elif defined(__x86_64__)
#define __SIZEOF_LONG_DOUBLE__ 16
#elif defined(__arm__)
#define __SIZEOF_LONG_DOUBLE__ 8
#else
#define __SIZEOF_LONG_DOUBLE__ 12
#endif
#endif /* !__SIZEOF_LONG_DOUBLE__ */

class __intellisense_long_double;
template<> struct ____INTELLISENSE_isfloat<__intellisense_long_double> { enum { __value = true }; };

#define __LONGDOUBLE ::__intern::__intellisense_long_double
#if __SIZEOF_LONG_DOUBLE__ == 12
class __attribute__((__aligned__(16))) __intellisense_long_double
#else /* __SIZEOF_LONG_DOUBLE__ == 12 */
class __attribute__((__aligned__(__SIZEOF_LONG_DOUBLE__))) __intellisense_long_double
#endif /* __SIZEOF_LONG_DOUBLE__ != 12 */
{
private:
	unsigned char __ld_data[__SIZEOF_LONG_DOUBLE__];
public:
	__intellisense_long_double() throw() = default;
	__intellisense_long_double(__intellisense_long_double const &) throw() = default;
	__intellisense_long_double(__intellisense_long_double &&) throw() = default;
	__intellisense_long_double(bool) throw();
	__intellisense_long_double(char) throw();
	__intellisense_long_double(signed char) throw();
	__intellisense_long_double(unsigned char) throw();
	__intellisense_long_double(short) throw();
	__intellisense_long_double(unsigned short) throw();
	__intellisense_long_double(int) throw();
	__intellisense_long_double(unsigned int) throw();
	__intellisense_long_double(long) throw();
	__intellisense_long_double(unsigned long) throw();
	__intellisense_long_double(long long) throw();
	__intellisense_long_double(unsigned long long) throw();
	__intellisense_long_double(wchar_t) throw();
	__intellisense_long_double(float) throw();
	__intellisense_long_double(double) throw();
	__intellisense_long_double(long double) throw();
	__intellisense_long_double(__intellisense_int128) throw();
	__intellisense_long_double(__intellisense_uint128) throw();
	__intellisense_long_double &operator=(__intellisense_long_double const &) throw();
	__intellisense_long_double &operator=(__intellisense_long_double &&) throw();
	__intellisense_long_double &operator=(bool) throw();
	__intellisense_long_double &operator=(char) throw();
	__intellisense_long_double &operator=(signed char) throw();
	__intellisense_long_double &operator=(unsigned char) throw();
	__intellisense_long_double &operator=(short) throw();
	__intellisense_long_double &operator=(unsigned short) throw();
	__intellisense_long_double &operator=(int) throw();
	__intellisense_long_double &operator=(unsigned int) throw();
	__intellisense_long_double &operator=(long) throw();
	__intellisense_long_double &operator=(unsigned long) throw();
	__intellisense_long_double &operator=(long long) throw();
	__intellisense_long_double &operator=(unsigned long long) throw();
	__intellisense_long_double &operator=(wchar_t) throw();
	__intellisense_long_double &operator=(float) throw();
	__intellisense_long_double &operator=(double) throw();
	__intellisense_long_double &operator=(long double) throw();
	__intellisense_long_double &operator=(__intellisense_int128) throw();
	__intellisense_long_double &operator=(__intellisense_uint128) throw();
	__intellisense_long_double operator-() const throw();
	__intellisense_long_double operator+(__intellisense_long_double const &) const throw();
	__intellisense_long_double operator-(__intellisense_long_double const &) const throw();
	__intellisense_long_double operator*(__intellisense_long_double const &)const throw();
	__intellisense_long_double operator/(__intellisense_long_double const &) const throw();
	__intellisense_long_double &operator+=(__intellisense_long_double const &) throw();
	__intellisense_long_double &operator-=(__intellisense_long_double const &) throw();
	__intellisense_long_double &operator*=(__intellisense_long_double const &) throw();
	__intellisense_long_double &operator/=(__intellisense_long_double const &) throw();
	bool operator==(__intellisense_long_double const &) const throw();
	bool operator!=(__intellisense_long_double const &) const throw();
	bool operator<(__intellisense_long_double const &) const throw();
	bool operator>(__intellisense_long_double const &) const throw();
	bool operator<=(__intellisense_long_double const &) const throw();
	bool operator>=(__intellisense_long_double const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double>::__type operator+(__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double>::__type operator-(__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double>::__type operator*(__VT const &)const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double>::__type operator/(__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double &>::__type operator+=(__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double &>::__type operator-=(__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double &>::__type operator*=(__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double &>::__type operator/=(__VT const &) throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator==(__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator!=(__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator<(__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator>(__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator<=(__VT const &) const throw();
	template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator>=(__VT const &) const throw();
	bool operator!() const throw();
	operator bool() const throw();
	operator char() const throw();
	operator signed char() const throw();
	operator unsigned char() const throw();
	operator short() const throw();
	operator unsigned short() const throw();
	operator int() const throw();
	operator unsigned int() const throw();
	operator long() const throw();
	operator unsigned long() const throw();
	operator long long() const throw();
	operator unsigned long long() const throw();
	operator wchar_t() const throw();
	operator float() const throw();
	operator double() const throw();
	operator long double() const throw();
	operator __intellisense_int128() const throw();
	operator __intellisense_uint128() const throw();
#if defined(_WCHAR_T_DEFINED) || defined(__GNUC__)
	__intellisense_long_double(char16_t) throw();
	__intellisense_long_double(char32_t) throw();
	operator char16_t() const throw();
	operator char32_t() const throw();
#endif /* _WCHAR_T_DEFINED || __GNUC__ */
};

template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double>::__type operator+(__VT const &, __intellisense_long_double const &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double>::__type operator-(__VT const &, __intellisense_long_double const &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double>::__type operator*(__VT const &, __intellisense_long_double const &)throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double>::__type operator/(__VT const &, __intellisense_long_double const &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double &>::__type operator+=(__VT const &, __intellisense_long_double &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double &>::__type operator-=(__VT const &, __intellisense_long_double &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double &>::__type operator*=(__VT const &, __intellisense_long_double &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, __intellisense_long_double &>::__type operator/=(__VT const &, __intellisense_long_double &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator==(__VT const &, __intellisense_long_double const &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator!=(__VT const &, __intellisense_long_double const &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator<(__VT const &, __intellisense_long_double const &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator>(__VT const &, __intellisense_long_double const &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator<=(__VT const &, __intellisense_long_double const &) throw();
template<class __VT> typename ____INTELLISENSE_enableif<____INTELLISENSE_issigned<__VT>::__value || ____INTELLISENSE_isunsigned<__VT>::__value || ____INTELLISENSE_isfloat<__VT>::__value, bool>::__type operator>=(__VT const &, __intellisense_long_double const &) throw();


#else
#undef __SIZEOF_LONG_DOUBLE__
#define __SIZEOF_LONG_DOUBLE__ __SIZEOF_DOUBLE__
#endif

} /* namespace __intern */


/* Intellisense forgets about a whole bunch of builtin functions defined by GCC: */
// __builtin_drem();
// __builtin_dremf();
// __builtin_dreml();
// __builtin_exp10();
// __builtin_exp10f();
// __builtin_exp10l();
// __builtin_gamma();
// __builtin_gammaf();
// __builtin_gammal();
// __builtin_j0();
// __builtin_j0f();
// __builtin_j0l();
// __builtin_j1();
// __builtin_j1f();
// __builtin_j1l();
// __builtin_jn();
// __builtin_jnf();
// __builtin_jnl();
// __builtin_lceil();
// __builtin_lceilf();
// __builtin_lceill();
// __builtin_lfloor();
// __builtin_lfloorf();
// __builtin_lfloorl();
// __builtin_llceil();
// __builtin_llceilf();
// __builtin_llceill();
// __builtin_llfloor();
// __builtin_llfloorf();
// __builtin_llfloorl();
// __builtin_pow10();
// __builtin_pow10f();
// __builtin_pow10l();
// __builtin_scalb();
// __builtin_scalbf();
// __builtin_scalbl();
// __builtin_significand();
// __builtin_significandf();
// __builtin_significandl();
// __builtin_sincos();
// __builtin_sincosf();
// __builtin_sincosl();
// __builtin_y0();
// __builtin_y0f();
// __builtin_y0l();
// __builtin_y1();
// __builtin_y1f();
// __builtin_y1l();
// __builtin_yn();
// __builtin_ynf();
// __builtin_ynl();
// __builtin_clog10();
// __builtin_clog10f();
// __builtin_clog10l();
// __builtin_fprintf();
// __builtin_fprintf_unlocked();
// __builtin_fputc();
// __builtin_fputc_unlocked();
// __builtin_fputs();
// __builtin_fputs_unlocked();
// __builtin_fscanf();
// __builtin_fwrite();
// __builtin_fwrite_unlocked();
// __builtin_printf_unlocked();
// __builtin_putchar();
// __builtin_putchar_unlocked();
// __builtin_puts();
// __builtin_puts_unlocked();
// __builtin_scanf();
// __builtin_sprintf();
// __builtin_sscanf();
// __builtin_vfprintf();
// __builtin_vfscanf();
// __builtin_vprintf();
// __builtin_vscanf();
// __builtin_vsscanf();
// __builtin_isalnum();
// __builtin_isalpha();
// __builtin_isascii();
// __builtin_isblank();
// __builtin_iscntrl();
// __builtin_isdigit();
// __builtin_isgraph();
// __builtin_islower();
// __builtin_isprint();
// __builtin_ispunct();
// __builtin_isspace();
// __builtin_isupper();
// __builtin_isxdigit();
// __builtin_toascii();
// __builtin_tolower();
// __builtin_toupper();
// __builtin_iswalnum();
// __builtin_iswalpha();
// __builtin_iswblank();
// __builtin_iswcntrl();
// __builtin_iswdigit();
// __builtin_iswgraph();
// __builtin_iswlower();
// __builtin_iswprint();
// __builtin_iswpunct();
// __builtin_iswspace();
// __builtin_iswupper();
// __builtin_iswxdigit();
// __builtin_towlower();
// __builtin_towupper();
// __builtin_aggregate_incoming_address();
// __builtin_apply();
// __builtin_apply_args();
// __builtin_calloc();
// __builtin_clzimax();
// __builtin_ctzimax();
// __builtin_dcgettext();
// __builtin_dgettext();
// __builtin_execl();
// __builtin_execlp();
// __builtin_execle();
// __builtin_execv();
// __builtin_execvp();
// __builtin_execve();
// __builtin_exit();
// __builtin_ffsimax();
// __builtin_fork();
// __builtin_gettext();
// __builtin_imaxabs();
// __builtin_finite();
// __builtin_finitef();
// __builtin_finitel();
// __builtin_isinff();
// __builtin_isinfl();
// __builtin_isnanf();
// __builtin_isnanl();
// __builtin_malloc();
// __builtin_next_arg();
// __builtin_parityimax();
// __builtin_popcountimax();
// __builtin_return();
// __builtin_saveregs();
// __builtin_strfmon();
// __builtin_strftime();
// __builtin_update_setjmp_buf();
// __builtin__exit();
// __builtin__Exit();
// __builtin_init_trampoline();
// __builtin_adjust_trampoline();
// __builtin_nonlocal_goto();
// __builtin_stack_save();
// __builtin_stack_restore();
// __builtin___fprintf_chk();
// __builtin___vfprintf_chk();
// __builtin_infd32();
// __builtin_infd64();
// __builtin_infd128();
// __builtin_nand32();
// __builtin_nand64();
// __builtin_nand128();
// __builtin_putc();
// __builtin_putc_unlocked();
// __builtin_finited32();
// __builtin_finited64();
// __builtin_finited128();
// __builtin_isinfd32();
// __builtin_isinfd64();
// __builtin_isinfd128();
// __builtin_isnand32();
// __builtin_isnand64();
// __builtin_isnand128();
// __builtin_setjmp_setup();
// __builtin_setjmp_receiver();
// __sync_fetch_and_add_16();
// __sync_fetch_and_sub_16();
// __sync_fetch_and_or_16();
// __sync_fetch_and_and_16();
// __sync_fetch_and_xor_16();
// __sync_fetch_and_nand_16();
// __sync_add_and_fetch_16();
// __sync_sub_and_fetch_16();
// __sync_or_and_fetch_16();
// __sync_and_and_fetch_16();
// __sync_xor_and_fetch_16();
// __sync_nand_and_fetch_16();
// __sync_bool_compare_and_swap_16();
// __sync_val_compare_and_swap_16();
// __sync_lock_test_and_set_16();
// __builtin_gamma_r();
// __builtin_gammaf_r();
// __builtin_gammal_r();
// __builtin_lgamma_r();
// __builtin_lgammaf_r();
// __builtin_lgammal_r();
// __builtin_signbitd32();
// __builtin_signbitd64();
// __builtin_signbitd128();
// __builtin_cexpi();
// __builtin_cexpif();
// __builtin_cexpil();
// __builtin_free();
// __builtin_realloc();
// __builtin_va_arg_pack();
// __builtin_va_arg_pack_len();
// __builtin___emutls_get_address();
// __builtin_unwind_resume();
// __builtin_eh_pointer();
// __builtin_eh_filter();
// __builtin_eh_copy_values();
// __builtin_iceil();
// __builtin_iceilf();
// __builtin_iceill();
// __builtin_ifloor();
// __builtin_ifloorf();
// __builtin_ifloorl();
// __builtin_irint();
// __builtin_irintf();
// __builtin_irintl();
// __builtin_iround();
// __builtin_iroundf();
// __builtin_iroundl();
// __builtin_clrsb();
// __builtin_clrsbimax();
// __builtin_clrsbl();
// __builtin_clrsbll();
// __builtin_init_heap_trampoline();
// __builtin_alloca_with_align();
// __builtin__ITM_beginTransaction();
// __builtin__ITM_commitTransaction();
// __builtin__ITM_commitTransactionEH();
// __builtin__ITM_abortTransaction();
// __builtin__ITM_changeTransactionMode();
// __builtin__ITM_memcpyRtWt();
// __builtin__ITM_memmoveRtWt();
// __builtin__ITM_memsetW();
// __builtin__ITM_getTMCloneOrIrrevocable();
// __builtin__ITM_getTMCloneSafe();
// __builtin__ITM_malloc();
// __builtin__ITM_calloc();
// __builtin__ITM_free();
// __builtin__ITM_LU1();
// __builtin__ITM_LU2();
// __builtin__ITM_LU4();
// __builtin__ITM_LU8();
// __builtin__ITM_LF();
// __builtin__ITM_LD();
// __builtin__ITM_LE();
// __builtin__ITM_LB();
// __builtin__ITM_WU1();
// __builtin__ITM_WaRU1();
// __builtin__ITM_WaWU1();
// __builtin__ITM_WU2();
// __builtin__ITM_WaRU2();
// __builtin__ITM_WaWU2();
// __builtin__ITM_WU4();
// __builtin__ITM_WaRU4();
// __builtin__ITM_WaWU4();
// __builtin__ITM_WU8();
// __builtin__ITM_WaRU8();
// __builtin__ITM_WaWU8();
// __builtin__ITM_WF();
// __builtin__ITM_WaRF();
// __builtin__ITM_WaWF();
// __builtin__ITM_WD();
// __builtin__ITM_WaRD();
// __builtin__ITM_WaWD();
// __builtin__ITM_WE();
// __builtin__ITM_WaRE();
// __builtin__ITM_WaWE();
// __builtin__ITM_RU1();
// __builtin__ITM_RaRU1();
// __builtin__ITM_RaWU1();
// __builtin__ITM_RfWU1();
// __builtin__ITM_RU2();
// __builtin__ITM_RaRU2();
// __builtin__ITM_RaWU2();
// __builtin__ITM_RfWU2();
// __builtin__ITM_RU4();
// __builtin__ITM_RaRU4();
// __builtin__ITM_RaWU4();
// __builtin__ITM_RfWU4();
// __builtin__ITM_RU8();
// __builtin__ITM_RaRU8();
// __builtin__ITM_RaWU8();
// __builtin__ITM_RfWU8();
// __builtin__ITM_RF();
// __builtin__ITM_RaRF();
// __builtin__ITM_RaWF();
// __builtin__ITM_RfWF();
// __builtin__ITM_RD();
// __builtin__ITM_RaRD();
// __builtin__ITM_RaWD();
// __builtin__ITM_RfWD();
// __builtin__ITM_RE();
// __builtin__ITM_RaRE();
// __builtin__ITM_RaWE();
// __builtin__ITM_RfWE();
// __builtin_fabsd32();
// __builtin_fabsd64();
// __builtin_fabsd128();
// __builtin_posix_memalign();
// __atomic_feraiseexcept();
// __builtin_aligned_alloc();
// __builtin_acc_get_device_type();
// __builtin_GOACC_data_start();
// __builtin_GOACC_data_end();
// __builtin_GOACC_enter_exit_data();
// __builtin_GOACC_update();
// __builtin_GOACC_wait();
// __builtin_acc_on_device();
// __builtin_GOACC_parallel_keyed();
// __builtin_GOACC_declare();
// __builtin__ITM_memcpyRnWt();
// __builtin__ITM_memcpyRtWn();
// __builtin_copysignf16();
// __builtin_copysignf32();
// __builtin_copysignf64();
// __builtin_copysignf128();
// __builtin_copysignf32x();
// __builtin_copysignf64x();
// __builtin_copysignf128x();
// __builtin_fabsf16();
// __builtin_fabsf32();
// __builtin_fabsf64();
// __builtin_fabsf128();
// __builtin_fabsf32x();
// __builtin_fabsf64x();
// __builtin_fabsf128x();
// __builtin_huge_valf16();
// __builtin_huge_valf32();
// __builtin_huge_valf64();
// __builtin_huge_valf128();
// __builtin_huge_valf32x();
// __builtin_huge_valf64x();
// __builtin_huge_valf128x();
// __builtin_inff16();
// __builtin_inff32();
// __builtin_inff64();
// __builtin_inff128();
// __builtin_inff32x();
// __builtin_inff64x();
// __builtin_inff128x();
// __builtin_nanf16();
// __builtin_nanf32();
// __builtin_nanf64();
// __builtin_nanf128();
// __builtin_nanf32x();
// __builtin_nanf64x();
// __builtin_nanf128x();
// __builtin_nansf16();
// __builtin_nansf32();
// __builtin_nansf64();
// __builtin_nansf128();
// __builtin_nansf32x();
// __builtin_nansf64x();
// __builtin_nansf128x();
// __builtin_add_overflow_p();
// __builtin_sub_overflow_p();
// __builtin_mul_overflow_p();
// __builtin_init_descriptor();
// __builtin_adjust_descriptor();
// __builtin_memcmp_eq();
// __builtin_ceilf16();
// __builtin_ceilf32();
// __builtin_ceilf64();
// __builtin_ceilf128();
// __builtin_ceilf32x();
// __builtin_ceilf64x();
// __builtin_ceilf128x();
// __builtin_feclearexcept();
// __builtin_fegetenv();
// __builtin_fegetexceptflag();
// __builtin_fegetround();
// __builtin_feholdexcept();
// __builtin_feraiseexcept();
// __builtin_fesetenv();
// __builtin_fesetexceptflag();
// __builtin_fesetround();
// __builtin_fetestexcept();
// __builtin_feupdateenv();
// __builtin_floorf16();
// __builtin_floorf32();
// __builtin_floorf64();
// __builtin_floorf128();
// __builtin_floorf32x();
// __builtin_floorf64x();
// __builtin_floorf128x();
// __builtin_fmaf16();
// __builtin_fmaf32();
// __builtin_fmaf64();
// __builtin_fmaf128();
// __builtin_fmaf32x();
// __builtin_fmaf64x();
// __builtin_fmaf128x();
// __builtin_fmaxf16();
// __builtin_fmaxf32();
// __builtin_fmaxf64();
// __builtin_fmaxf128();
// __builtin_fmaxf32x();
// __builtin_fmaxf64x();
// __builtin_fmaxf128x();
// __builtin_fminf16();
// __builtin_fminf32();
// __builtin_fminf64();
// __builtin_fminf128();
// __builtin_fminf32x();
// __builtin_fminf64x();
// __builtin_fminf128x();
// __builtin_nearbyintf16();
// __builtin_nearbyintf32();
// __builtin_nearbyintf64();
// __builtin_nearbyintf128();
// __builtin_nearbyintf32x();
// __builtin_nearbyintf64x();
// __builtin_nearbyintf128x();
// __builtin_rintf16();
// __builtin_rintf32();
// __builtin_rintf64();
// __builtin_rintf128();
// __builtin_rintf32x();
// __builtin_rintf64x();
// __builtin_rintf128x();
// __builtin_roundf16();
// __builtin_roundf32();
// __builtin_roundf64();
// __builtin_roundf128();
// __builtin_roundf32x();
// __builtin_roundf64x();
// __builtin_roundf128x();
// __builtin_sqrtf16();
// __builtin_sqrtf32();
// __builtin_sqrtf64();
// __builtin_sqrtf128();
// __builtin_sqrtf32x();
// __builtin_sqrtf64x();
// __builtin_sqrtf128x();
// __builtin_truncf16();
// __builtin_truncf32();
// __builtin_truncf64();
// __builtin_truncf128();
// __builtin_truncf32x();
// __builtin_truncf64x();
// __builtin_truncf128x();
// __builtin_alloca_with_align_and_max();
// __builtin_omp_get_thread_num();
// __builtin_omp_get_num_threads();
// __builtin_omp_get_team_num();
// __builtin_omp_get_num_teams();
// __builtin_GOMP_atomic_start();
// __builtin_GOMP_atomic_end();
// __builtin_GOMP_barrier();
// __builtin_GOMP_barrier_cancel();
// __builtin_GOMP_taskwait();
// __builtin_GOMP_taskyield();
// __builtin_GOMP_taskgroup_start();
// __builtin_GOMP_taskgroup_end();
// __builtin_GOMP_cancel();
// __builtin_GOMP_cancellation_point();
// __builtin_GOMP_critical_start();
// __builtin_GOMP_critical_end();
// __builtin_GOMP_critical_name_start();
// __builtin_GOMP_critical_name_end();
// __builtin_GOMP_loop_static_start();
// __builtin_GOMP_loop_dynamic_start();
// __builtin_GOMP_loop_guided_start();
// __builtin_GOMP_loop_runtime_start();
// __builtin_GOMP_loop_nonmonotonic_dynamic_start();
// __builtin_GOMP_loop_nonmonotonic_guided_start();
// __builtin_GOMP_loop_ordered_static_start();
// __builtin_GOMP_loop_ordered_dynamic_start();
// __builtin_GOMP_loop_ordered_guided_start();
// __builtin_GOMP_loop_ordered_runtime_start();
// __builtin_GOMP_loop_doacross_static_start();
// __builtin_GOMP_loop_doacross_dynamic_start();
// __builtin_GOMP_loop_doacross_guided_start();
// __builtin_GOMP_loop_doacross_runtime_start();
// __builtin_GOMP_loop_static_next();
// __builtin_GOMP_loop_dynamic_next();
// __builtin_GOMP_loop_guided_next();
// __builtin_GOMP_loop_runtime_next();
// __builtin_GOMP_loop_nonmonotonic_dynamic_next();
// __builtin_GOMP_loop_nonmonotonic_guided_next();
// __builtin_GOMP_loop_ordered_static_next();
// __builtin_GOMP_loop_ordered_dynamic_next();
// __builtin_GOMP_loop_ordered_guided_next();
// __builtin_GOMP_loop_ordered_runtime_next();
// __builtin_GOMP_loop_ull_static_start();
// __builtin_GOMP_loop_ull_dynamic_start();
// __builtin_GOMP_loop_ull_guided_start();
// __builtin_GOMP_loop_ull_runtime_start();
// __builtin_GOMP_loop_ull_nonmonotonic_dynamic_start();
// __builtin_GOMP_loop_ull_nonmonotonic_guided_start();
// __builtin_GOMP_loop_ull_ordered_static_start();
// __builtin_GOMP_loop_ull_ordered_dynamic_start();
// __builtin_GOMP_loop_ull_ordered_guided_start();
// __builtin_GOMP_loop_ull_ordered_runtime_start();
// __builtin_GOMP_loop_ull_doacross_static_start();
// __builtin_GOMP_loop_ull_doacross_dynamic_start();
// __builtin_GOMP_loop_ull_doacross_guided_start();
// __builtin_GOMP_loop_ull_doacross_runtime_start();
// __builtin_GOMP_loop_ull_static_next();
// __builtin_GOMP_loop_ull_dynamic_next();
// __builtin_GOMP_loop_ull_guided_next();
// __builtin_GOMP_loop_ull_runtime_next();
// __builtin_GOMP_loop_ull_nonmonotonic_dynamic_next();
// __builtin_GOMP_loop_ull_nonmonotonic_guided_next();
// __builtin_GOMP_loop_ull_ordered_static_next();
// __builtin_GOMP_loop_ull_ordered_dynamic_next();
// __builtin_GOMP_loop_ull_ordered_guided_next();
// __builtin_GOMP_loop_ull_ordered_runtime_next();
// __builtin_GOMP_parallel_loop_static();
// __builtin_GOMP_parallel_loop_dynamic();
// __builtin_GOMP_parallel_loop_guided();
// __builtin_GOMP_parallel_loop_runtime();
// __builtin_GOMP_parallel_loop_nonmonotonic_dynamic();
// __builtin_GOMP_parallel_loop_nonmonotonic_guided();
// __builtin_GOMP_loop_end();
// __builtin_GOMP_loop_end_cancel();
// __builtin_GOMP_loop_end_nowait();
// __builtin_GOMP_ordered_start();
// __builtin_GOMP_ordered_end();
// __builtin_GOMP_doacross_post();
// __builtin_GOMP_doacross_wait();
// __builtin_GOMP_doacross_ull_post();
// __builtin_GOMP_doacross_ull_wait();
// __builtin_GOMP_parallel();
// __builtin_GOMP_task();
// __builtin_GOMP_taskloop();
// __builtin_GOMP_taskloop_ull();
// __builtin_GOMP_sections_start();
// __builtin_GOMP_sections_next();
// __builtin_GOMP_parallel_sections();
// __builtin_GOMP_sections_end();
// __builtin_GOMP_sections_end_cancel();
// __builtin_GOMP_sections_end_nowait();
// __builtin_GOMP_single_start();
// __builtin_GOMP_single_copy_start();
// __builtin_GOMP_single_copy_end();
// __builtin_GOMP_offload_register_ver();
// __builtin_GOMP_offload_unregister_ver();
// __builtin_GOMP_target_ext();
// __builtin_GOMP_target_data_ext();
// __builtin_GOMP_target_end_data();
// __builtin_GOMP_target_update_ext();
// __builtin_GOMP_target_enter_exit_data();
// __builtin_GOMP_teams();
// __builtin_strnlen();
// __builtin_expect_with_probability();
// __builtin_strcmp_eq();
// __builtin_strncmp_eq();
// __builtin_speculation_safe_value();
// __builtin_speculation_safe_value_ptr();
// __builtin_speculation_safe_value_1();
// __builtin_speculation_safe_value_2();
// __builtin_speculation_safe_value_4();
// __builtin_speculation_safe_value_8();
// __builtin_speculation_safe_value_16();
// __builtin_goacc_parlevel_id();
// __builtin_goacc_parlevel_size();
// __builtin_GOMP_taskwait_depend();
// __builtin_GOMP_loop_nonmonotonic_runtime_start();
// __builtin_GOMP_loop_maybe_nonmonotonic_runtime_start();
// __builtin_GOMP_loop_start();
// __builtin_GOMP_loop_ordered_start();
// __builtin_GOMP_loop_doacross_start();
// __builtin_GOMP_loop_nonmonotonic_runtime_next();
// __builtin_GOMP_loop_maybe_nonmonotonic_runtime_next();
// __builtin_GOMP_loop_ull_nonmonotonic_runtime_start();
// __builtin_GOMP_loop_ull_maybe_nonmonotonic_runtime_start();
// __builtin_GOMP_loop_ull_start();
// __builtin_GOMP_loop_ull_ordered_start();
// __builtin_GOMP_loop_ull_doacross_start();
// __builtin_GOMP_loop_ull_nonmonotonic_runtime_next();
// __builtin_GOMP_loop_ull_maybe_nonmonotonic_runtime_next();
// __builtin_GOMP_parallel_loop_nonmonotonic_runtime();
// __builtin_GOMP_parallel_loop_maybe_nonmonotonic_runtime();
// __builtin_GOMP_parallel_reductions();
// __builtin_GOMP_sections2_start();
// __builtin_GOMP_teams_reg();
// __builtin_GOMP_taskgroup_reduction_register();
// __builtin_GOMP_taskgroup_reduction_unregister();
// __builtin_GOMP_task_reduction_remap();
// __builtin_GOMP_workshare_task_reduction_unregister();


/* For some weird reason, intellisense defines these builtins as macros,
 * on-top of already defining them as functions... (there may be more of
 * these, but these are all that I've encountered thus far) */
#undef __builtin_acosf
#undef __builtin_acoshf
#undef __builtin_acoshl
#undef __builtin_acosl
#undef __builtin_asinf
#undef __builtin_asinhf
#undef __builtin_asinhl
#undef __builtin_asinl
#undef __builtin_atan2f
#undef __builtin_atan2l
#undef __builtin_atanf
#undef __builtin_atanhf
#undef __builtin_atanhl
#undef __builtin_atanl
#undef __builtin_cbrtf
#undef __builtin_cbrtl
#undef __builtin_ceilf
#undef __builtin_ceill
#undef __builtin_copysignf
#undef __builtin_copysignl
#undef __builtin_cosf
#undef __builtin_coshf
#undef __builtin_coshl
#undef __builtin_cosl
#undef __builtin_erfcf
#undef __builtin_erfcl
#undef __builtin_erff
#undef __builtin_erfl
#undef __builtin_exp2f
#undef __builtin_exp2l
#undef __builtin_expf
#undef __builtin_expl
#undef __builtin_expm1f
#undef __builtin_expm1l
#undef __builtin_fdimf
#undef __builtin_fdiml
#undef __builtin_floorf
#undef __builtin_floorl
#undef __builtin_fmaf
#undef __builtin_fmal
#undef __builtin_fmaxf
#undef __builtin_fmaxl
#undef __builtin_fminf
#undef __builtin_fminl
#undef __builtin_fmodf
#undef __builtin_fmodl
#undef __builtin_hypotf
#undef __builtin_hypotl
#undef __builtin_ilogbf
#undef __builtin_ilogbl
#undef __builtin_ldexpf
#undef __builtin_ldexpl
#undef __builtin_lgammaf
#undef __builtin_lgammal
#undef __builtin_llrintf
#undef __builtin_llrintl
#undef __builtin_llroundf
#undef __builtin_llroundl
#undef __builtin_log10f
#undef __builtin_log10l
#undef __builtin_log1pf
#undef __builtin_log1pl
#undef __builtin_log2f
#undef __builtin_log2l
#undef __builtin_logb
#undef __builtin_logbf
#undef __builtin_logbl
#undef __builtin_logf
#undef __builtin_logl
#undef __builtin_lrintf
#undef __builtin_lrintl
#undef __builtin_lroundf
#undef __builtin_lroundl
#undef __builtin_nearbyint
#undef __builtin_nearbyintf
#undef __builtin_nearbyintl
#undef __builtin_nextafterf
#undef __builtin_nextafterl
#undef __builtin_nexttowardf
#undef __builtin_nexttowardl
#undef __builtin_remainderf
#undef __builtin_remainderl
#undef __builtin_remquof
#undef __builtin_remquol
#undef __builtin_rint
#undef __builtin_rintf
#undef __builtin_rintl
#undef __builtin_round
#undef __builtin_roundf
#undef __builtin_roundl
#undef __builtin_scalbln
#undef __builtin_scalblnf
#undef __builtin_scalblnl
#undef __builtin_scalbn
#undef __builtin_scalbnf
#undef __builtin_scalbnl
#undef __builtin_signbit
#undef __builtin_signbitf
#undef __builtin_signbitl
#undef __builtin_sinf
#undef __builtin_sinhf
#undef __builtin_sinhl
#undef __builtin_sinl
#undef __builtin_sqrtf
#undef __builtin_sqrtl
#undef __builtin_tanf
#undef __builtin_tanhf
#undef __builtin_tanhl
#undef __builtin_tanl
#undef __builtin_tgamma
#undef __builtin_tgammaf
#undef __builtin_tgammal
#undef __builtin_trunc
#undef __builtin_truncf
#undef __builtin_truncl
#undef __builtin_isgreater
#undef __builtin_isgreaterequal
#undef __builtin_isless
#undef __builtin_islessequal
#undef __builtin_islessgreater
#undef __builtin_isunordered

#endif /* !____INTELLISENSE_STDINC_SYNTAX_GCC_H */
