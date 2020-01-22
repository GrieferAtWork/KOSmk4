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

#if 0 /* This breaks `operator ""s' and `operator new()' for intellisense */
#undef __SIZE_TYPE__
#define __SIZE_TYPE__  unsigned long int
#endif

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
#endif /* __x86_64__ */


#if 0 /* How can Intellisense be this stupid? - I mean: this is linux 101! */
static_assert(sizeof(wchar_t) == __SIZEOF_WCHAR_T__, "WTF Intellisense?");
#else
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

#endif /* !____INTELLISENSE_STDINC_SYNTAX_GCC_H */
