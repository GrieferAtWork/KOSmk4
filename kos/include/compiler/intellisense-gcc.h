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
#ifndef ____INTELLISENSE_STDINC_SYNTAX_GCC_H
#define ____INTELLISENSE_STDINC_SYNTAX_GCC_H 1
#undef clang
#undef __clang
#undef __clang__

/*
 * While the `linux-gcc-x86' intellisense driver is _extremely_ welcome if you ask  me,
 * there are still a couple of things that it does wrong when compared against the real
 * deal. - Fix those in here!.
 * Also: Implement the common intellisense types used to implement alternate integral
 *       types, as well as endian-restricted integers.
 */

#include "intellisense-common.h"

/* Native GCC support in intellisense */
#define __INTELLISENSE_GCC__ 1

#define __GNUC__                           9
#define __GNUG__                           9
#define __GNUC_MINOR__                     1
#define __GNUC_PATCHLEVEL__                0
#define __GXX_ABI_VERSION                  1013
#define __GXX_EXPERIMENTAL_CXX0X__         1
#define __GXX_RTTI                         1
#define __GXX_WEAK__                       1
#define __DEPRECATED                       1
#define __VERSION__                        "9.1.0"
#define __STDC_UTF_16__                    1
#define __STDC_UTF_32__                    1
#define __STDC__                           1
#define __GNUC_STDC_INLINE__               1
#define __HAVE_SPECULATION_SAFE_VALUE      1
#define __GCC_IEC_559                      2
#define __GCC_IEC_559_COMPLEX              2
#define __GCC_ASM_FLAG_OUTPUTS__           1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 1
#define __ATOMIC_RELAXED                   0
#define __ATOMIC_CONSUME                   1
#define __ATOMIC_ACQUIRE                   2
#define __ATOMIC_RELEASE                   3
#define __ATOMIC_ACQ_REL                   4
#define __ATOMIC_SEQ_CST                   5

#ifdef __KOS__
#undef linux
#undef __linux
#undef __linux__
#undef _WIN32
#undef _WIN64
#undef _M_AMD64
#undef _M_X64
#undef _M_IX86
#define __unix   1
#define __unix__ 1
#endif /* __KOS__ */

#ifdef __unix__
#define __ELF__                   1
#define __GCC_HAVE_DWARF2_CFI_ASM 1
#endif /* __unix__ */

#ifdef __x86_64__
#define __x86_64                    1
#define __k8                        1
#define __k8__                      1
#define __amd64                     1
#define __amd64__                   1
#define __code_model_small__        1
#define _LP64                       1
#define __LP64__                    1
#define __MMX__                     1
#define __SSE2_MATH__               1
#define __SSE2__                    1
#define __SSE_MATH__                1
#define __SSE__                     1
#define __SIZEOF_LONG__             4
#define __SIZEOF_INT128__           16
#define __INTELLISENSE_SIZE_TYPE__  unsigned long long int
#define __INTELLISENSE_SSIZE_TYPE__ signed long long int
#define __ATOMIC_HLE_ACQUIRE        65536
#define __ATOMIC_HLE_RELEASE        131072
#define __FXSR__                    1
#elif defined(__i386__)
#define __i386   1
#define __i686   1
#define __i686__ 1
#define __INTELLISENSE_SIZE_TYPE__  unsigned int /* Should be `long' for elf, but isn't */
#define __INTELLISENSE_SSIZE_TYPE__ signed int
#undef __SSE2_MATH__
#undef __SSE2__
#undef __SSE_MATH__
#undef __SSE__
#endif /* Arch... */

#ifndef __INTELLISENSE_SIZE_TYPE__
#define __INTELLISENSE_SIZE_TYPE__ __SIZE_TYPE__
#endif /* !__INTELLISENSE_SIZE_TYPE__ */

#ifndef __INTELLISENSE_SSIZE_TYPE__
#define __INTELLISENSE_SSIZE_TYPE__ __SSIZE_TYPE__
#endif /* !__INTELLISENSE_SSIZE_TYPE__ */


#if 0 /* How can Intellisense be this stupid? - I mean: this is linux 101! */
static_assert(sizeof(wchar_t) == __SIZEOF_WCHAR_T__, "WTF Intellisense?");
#else
/* This isn't really correct, either. wchar_t on linux is 4 bytes, however  we
 * can't really change sizeof(xxx) using preprocessor directives, so the  best
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

#if __cplusplus >= 201402L
#undef __cpp_deduction_guides
#define __cpp_constexpr               201304
#define __cpp_digit_separators        201309
#define __cpp_inheriting_constructors 201511
#define __cpp_range_based_for         200907
#define __cpp_runtime_arrays          198712
#define __cpp_rvalue_reference        200610
#define __cpp_static_assert           201411
#endif /* __cplusplus == 201402L */


namespace __intern {

/* Intellisense doesn't emulate `__int128' properly  (or rather: at all; it  only
 * defines the `__SIZEOF_INT128__' feature test macro, but don't actually care to
 * implement the actual feature it is used to test for... ~ugh~)
 * -> So try to  fix that  _BUG_! Because  that's totally  what it  is, and  not
 *    just the  vs developers  being lazy.  Oh no,  it totally  isn't that  they
 *    probably  just  copied a  list of  gcc's predefined  macros and  called it
 *    a day without actually going through all of them and checking that they're
 *    actually doing what they're supposed to do.
 * I mean: How else do you think  not only something like this happened,  but
 * also something like `__INT64_TYPE__' not actually being 64-bit because its
 * default definition is (just like  it is in gcc) `signed long int'  (again:
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

#ifndef __INTELLISENSE_SIZEOF_LONG_DOUBLE__
#ifdef __i386__
#define __INTELLISENSE_SIZEOF_LONG_DOUBLE__ 12
#elif defined(__x86_64__)
#define __INTELLISENSE_SIZEOF_LONG_DOUBLE__ 16
#elif defined(__arm__)
#define __INTELLISENSE_SIZEOF_LONG_DOUBLE__ 8
#else
#define __INTELLISENSE_SIZEOF_LONG_DOUBLE__ 12
#endif
#endif /* !__INTELLISENSE_SIZEOF_LONG_DOUBLE__ */


#if 0 /* How can Intellisense be this stupid? - I mean: this is linux 101! */
static_assert(sizeof(long double) == __INTELLISENSE_SIZEOF_LONG_DOUBLE__, "WTF Intellisense?");
#elif 1

class __intellisense_long_double;
template<> struct ____INTELLISENSE_isfloat<__intellisense_long_double> { enum { __value = true }; };

#define __LONGDOUBLE ::__intern::__intellisense_long_double
#if __INTELLISENSE_SIZEOF_LONG_DOUBLE__ == 12
class __attribute__((__aligned__(4))) __intellisense_long_double
#else /* __INTELLISENSE_SIZEOF_LONG_DOUBLE__ == 12 */
class __attribute__((__aligned__(__INTELLISENSE_SIZEOF_LONG_DOUBLE__))) __intellisense_long_double
#endif /* __INTELLISENSE_SIZEOF_LONG_DOUBLE__ != 12 */
{
private:
	unsigned char __ld_data[__INTELLISENSE_SIZEOF_LONG_DOUBLE__];
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
#ifdef __SIZEOF_INT128__
	__intellisense_long_double(__INT128_TYPE__) throw();
	__intellisense_long_double(__UINT128_TYPE__) throw();
#endif /* __SIZEOF_INT128__ */
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
#ifdef __SIZEOF_INT128__
	__intellisense_long_double &operator=(__INT128_TYPE__) throw();
	__intellisense_long_double &operator=(__UINT128_TYPE__) throw();
#endif /* __SIZEOF_INT128__ */
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
#ifdef __SIZEOF_INT128__
	operator __intellisense_int128() const throw();
	operator __intellisense_uint128() const throw();
#endif /* __SIZEOF_INT128__ */
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
#undef __INTELLISENSE_SIZEOF_LONG_DOUBLE__
#define __INTELLISENSE_SIZEOF_LONG_DOUBLE__ __SIZEOF_DOUBLE__
#endif

} /* namespace __intern */


/* Intellisense forgets about a whole bunch of builtin functions defined by GCC: */
double __builtin_drem(double, double);
float __builtin_dremf(float, float);
__LONGDOUBLE __builtin_dreml(__LONGDOUBLE, __LONGDOUBLE);
double __builtin_exp10(double);
float __builtin_exp10f(float);
__LONGDOUBLE __builtin_exp10l(__LONGDOUBLE);
double __builtin_gamma(double);
float __builtin_gammaf(float);
__LONGDOUBLE __builtin_gammal(__LONGDOUBLE);
double __builtin_j0(double);
float __builtin_j0f(float);
__LONGDOUBLE __builtin_j0l(__LONGDOUBLE);
double __builtin_j1(double);
float __builtin_j1f(float);
__LONGDOUBLE __builtin_j1l(__LONGDOUBLE);
double __builtin_jn(int, double);
float __builtin_jnf(int, float);
__LONGDOUBLE __builtin_jnl(int, __LONGDOUBLE);
long __builtin_lceil(double);
long __builtin_lceilf(float);
long __builtin_lceill(__LONGDOUBLE);
long __builtin_lfloor(double);
long __builtin_lfloorf(float);
long __builtin_lfloorl(__LONGDOUBLE);
long long __builtin_llceil(double);
long long __builtin_llceilf(float);
long long __builtin_llceill(__LONGDOUBLE);
long long __builtin_llfloor(double);
long long __builtin_llfloorf(float);
long long __builtin_llfloorl(__LONGDOUBLE);
double __builtin_pow10(double);
float __builtin_pow10f(float);
__LONGDOUBLE __builtin_pow10l(__LONGDOUBLE);
double __builtin_scalb(double, double);
float __builtin_scalbf(float, float);
__LONGDOUBLE __builtin_scalbl(__LONGDOUBLE, __LONGDOUBLE);
double __builtin_significand(double);
float __builtin_significandf(float);
__LONGDOUBLE __builtin_significandl(__LONGDOUBLE);
void __builtin_sincos(double, double *, double *);
void __builtin_sincosf(float, float *, float *);
void __builtin_sincosl(__LONGDOUBLE, __LONGDOUBLE *, __LONGDOUBLE *);
double __builtin_y0(double);
float __builtin_y0f(float);
__LONGDOUBLE __builtin_y0l(__LONGDOUBLE);
double __builtin_y1(double);
float __builtin_y1f(float);
__LONGDOUBLE __builtin_y1l(__LONGDOUBLE);
double __builtin_yn(int, double);
float __builtin_ynf(int, float);
__LONGDOUBLE __builtin_ynl(int, __LONGDOUBLE);
__complex__ double __builtin_clog10(__complex__ double);
__complex__ float __builtin_clog10f(__complex__ float);
__complex__ long double __builtin_clog10l(__complex__ long double);
int __builtin_fprintf(void *, char const *, ...);
int __builtin_fprintf_unlocked(void *, char const *, ...);
int __builtin_fputc(int, void *);
int __builtin_fputc_unlocked(int, void *);
int __builtin_fputs(char const *, void *);
int __builtin_fputs_unlocked(char const *, void *);
int __builtin_fscanf(void *, char const *, ...);
int __builtin_fwrite(void const *, __INTELLISENSE_SIZE_TYPE__, __INTELLISENSE_SIZE_TYPE__, void *);
int __builtin_fwrite_unlocked(void const *, __INTELLISENSE_SIZE_TYPE__, __INTELLISENSE_SIZE_TYPE__, void *);
int __builtin_printf_unlocked(char const *, ...);
int __builtin_putchar(int);
int __builtin_putchar_unlocked(int);
int __builtin_puts(char const *);
int __builtin_puts_unlocked(char const *);
int __builtin_scanf(char const *, ...);
int __builtin_sprintf(char *, char const *, ...);
int __builtin_sscanf(char const *, char const *, ...);
int __builtin_vfprintf(void *, char const *, __builtin_va_list);
int __builtin_vfscanf(void *, char const *, __builtin_va_list);
int __builtin_vprintf(char const *, __builtin_va_list);
int __builtin_vscanf(char const *, __builtin_va_list);
int __builtin_vsscanf(char const *, char const *, __builtin_va_list);
int __builtin_isalnum(int);
int __builtin_isalpha(int);
int __builtin_isascii(int);
int __builtin_isblank(int);
int __builtin_iscntrl(int);
int __builtin_isdigit(int);
int __builtin_isgraph(int);
int __builtin_islower(int);
int __builtin_isprint(int);
int __builtin_ispunct(int);
int __builtin_isspace(int);
int __builtin_isupper(int);
int __builtin_isxdigit(int);
int __builtin_toascii(int);
int __builtin_tolower(int);
int __builtin_toupper(int);
int __builtin_iswalnum(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswalpha(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswblank(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswcntrl(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswdigit(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswgraph(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswlower(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswprint(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswpunct(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswspace(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswupper(/*__WINT_TYPE__*/ unsigned int);
int __builtin_iswxdigit(/*__WINT_TYPE__*/ unsigned int);
int __builtin_towlower(/*__WINT_TYPE__*/ unsigned int);
int __builtin_towupper(/*__WINT_TYPE__*/ unsigned int);
void *__builtin_aggregate_incoming_address(...);
void *__builtin_apply(void (*)(...), void *, __INTELLISENSE_SIZE_TYPE__);
void *__builtin_apply_args(...);
void *__builtin_calloc(__INTELLISENSE_SIZE_TYPE__, __INTELLISENSE_SIZE_TYPE__);
int __builtin_clzimax(/*__UINTMAX_TYPE__*/ unsigned long long);
int __builtin_ctzimax(/*__UINTMAX_TYPE__*/ unsigned long long);
char *__builtin_dcgettext(char const *, char const *, int);
char *__builtin_dgettext(char const *, char const *);
int __builtin_execl(char const *, ...);
int __builtin_execlp(char const *, ...);
int __builtin_execle(char const *, ...);
int __builtin_execv(char const *, char *const *);
int __builtin_execvp(char const *, char *const *);
int __builtin_execve(char const *, char *const *, char *const *);
__attribute__((__noreturn__)) void __builtin_exit(int);
int __builtin_ffsimax(/*__INTMAX_TYPE__*/ long long);
int __builtin_fork();
char *__builtin_gettext(char const *);
/*__INTMAX_TYPE__*/ long long __builtin_imaxabs(/*__INTMAX_TYPE__*/ long long);
int __builtin_finite(double);
int __builtin_finitef(float);
int __builtin_finitel(__LONGDOUBLE);
int __builtin_isinff(float);
int __builtin_isinfl(__LONGDOUBLE);
int __builtin_isnanf(float);
int __builtin_isnanl(__LONGDOUBLE);
void *__builtin_malloc(__INTELLISENSE_SIZE_TYPE__);
template<class __T> void *__builtin_next_arg(__T const &);
int __builtin_parityimax(/*__UINTMAX_TYPE__*/ unsigned long long);
int __builtin_popcountimax(/*__UINTMAX_TYPE__*/ unsigned long long);
void __builtin_return(void *);
void *__builtin_saveregs(...);
long int __builtin_strfmon(char *, __INTELLISENSE_SIZE_TYPE__, char const *, ...);
__INTELLISENSE_SIZE_TYPE__ __builtin_strftime(char *, __INTELLISENSE_SIZE_TYPE__, char const *, void const *);
void __builtin_update_setjmp_buf(void *);
__attribute__((__noreturn__)) void __builtin__exit(int);
__attribute__((__noreturn__)) void __builtin__Exit(int);
void __builtin_init_trampoline(void *, void *, void *);
void *__builtin_adjust_trampoline(void *);
void __builtin_nonlocal_goto(void *, void *);
void *__builtin_stack_save();
void __builtin_stack_restore(void *);
int __builtin___fprintf_chk(void *, int, char const *, ...);
int __builtin___vfprintf_chk(void *, int, char const *, __builtin_va_list);
int __builtin_putc(int, void *);
int __builtin_putc_unlocked(int, void *);
void __builtin_setjmp_setup(void *, void *);
void __builtin_setjmp_receiver(void *);
double __builtin_gamma_r(double, int *);
float __builtin_gammaf_r(float, int *);
__LONGDOUBLE __builtin_gammal_r(__LONGDOUBLE, int *);
double __builtin_lgamma_r(double, int *);
float __builtin_lgammaf_r(float, int *);
__LONGDOUBLE __builtin_lgammal_r(__LONGDOUBLE, int *);
__complex__ double __builtin_cexpi(double);
__complex__ float __builtin_cexpif(float);
__complex__ long double __builtin_cexpil(long double);
void __builtin_free(void *);
void *__builtin_realloc(void *, __INTELLISENSE_SIZE_TYPE__);
int __builtin_va_arg_pack();
int __builtin_va_arg_pack_len();
__attribute__((__noreturn__)) void __builtin_unwind_resume(void *);
void *__builtin_eh_pointer(int);
long int __builtin_eh_filter(int);
void __builtin_eh_copy_values(int, int);
int __builtin_iceil(double);
int __builtin_iceilf(float);
int __builtin_iceill(__LONGDOUBLE);
int __builtin_ifloor(double);
int __builtin_ifloorf(float);
int __builtin_ifloorl(__LONGDOUBLE);
int __builtin_irint(double);
int __builtin_irintf(float);
int __builtin_irintl(__LONGDOUBLE);
int __builtin_iround(double);
int __builtin_iroundf(float);
int __builtin_iroundl(__LONGDOUBLE);
int __builtin_clrsb(int);
int __builtin_clrsbimax(/*__INTMAX_TYPE__*/ long long);
int __builtin_clrsbl(long);
int __builtin_clrsbll(long long);
void __builtin_init_heap_trampoline(void *, void *, void *);
void *__builtin_alloca_with_align(__INTELLISENSE_SIZE_TYPE__, __INTELLISENSE_SIZE_TYPE__);
int __builtin_posix_memalign(void **, __INTELLISENSE_SIZE_TYPE__, __INTELLISENSE_SIZE_TYPE__);
void __atomic_feraiseexcept(int);
void *__builtin_aligned_alloc(__INTELLISENSE_SIZE_TYPE__, __INTELLISENSE_SIZE_TYPE__);
int __builtin_acc_on_device(int);
void __builtin_init_descriptor(void *, void *, void *);
void *__builtin_adjust_descriptor(void *);
int __builtin_memcmp_eq(void const *, void const *, __INTELLISENSE_SIZE_TYPE__);
int __builtin_feclearexcept(int);
int __builtin_fegetenv(void *);
int __builtin_fegetexceptflag(void *, int);
int __builtin_fegetround();
int __builtin_feholdexcept(void *);
int __builtin_feraiseexcept(int);
int __builtin_fesetenv(void const *);
int __builtin_fesetexceptflag(void const *, int);
int __builtin_fesetround(int);
int __builtin_fetestexcept(int);
int __builtin_feupdateenv(void const *);
void *__builtin_alloca_with_align_and_max(__INTELLISENSE_SIZE_TYPE__, __INTELLISENSE_SIZE_TYPE__, __INTELLISENSE_SIZE_TYPE__);
__INTELLISENSE_SIZE_TYPE__ __builtin_strnlen(char const *, __INTELLISENSE_SIZE_TYPE__);
long __builtin_expect_with_probability(long __exp, long __c, double __probability);
int __builtin_strcmp_eq(void const *, void const *, __INTELLISENSE_SIZE_TYPE__); /* Yes, that's the prototype... */
int __builtin_strncmp_eq(void const *, void const *, __INTELLISENSE_SIZE_TYPE__);
template<class __T> __T __builtin_speculation_safe_value(__T __val, __T __failval = 0);
void *__builtin_speculation_safe_value_ptr(void *, void * = nullptr);
/*__UINT8_TYPE__*/ unsigned char __builtin_speculation_safe_value_1(/*__UINT8_TYPE__*/ unsigned char, /*__UINT8_TYPE__*/ unsigned char = 0);
/*__UINT16_TYPE__*/ unsigned short __builtin_speculation_safe_value_2(/*__UINT16_TYPE__*/ unsigned short, /*__UINT16_TYPE__*/ unsigned short = 0);
/*__UINT32_TYPE__*/ unsigned int __builtin_speculation_safe_value_4(/*__UINT32_TYPE__*/ unsigned int, /*__UINT32_TYPE__*/ unsigned int = 0);
/*__UINT64_TYPE__*/ unsigned long long __builtin_speculation_safe_value_8(/*__UINT64_TYPE__*/ unsigned long long, /*__UINT64_TYPE__*/ unsigned long long = 0);
void __cyg_profile_func_enter(void *, void *);
void __cyg_profile_func_exit(void *, void *);
#ifdef __SIZEOF_INT128__
/* For some reason, intellisense seems to ?somewhat? know of these functions?
 * Even though it doesn't know about them from the get-go, manually  defining
 * them by their actual names will cause intellisense to still not know about
 * them, and  act  as though  they  hadn't  actually be  declared  at  all...
 * Work around this bug by defining these as macro aliases */
#define __sync_fetch_and_add_16         __builtin_sync_fetch_and_add_16
#define __sync_fetch_and_sub_16         __builtin_sync_fetch_and_sub_16
#define __sync_fetch_and_or_16          __builtin_sync_fetch_and_or_16
#define __sync_fetch_and_and_16         __builtin_sync_fetch_and_and_16
#define __sync_fetch_and_xor_16         __builtin_sync_fetch_and_xor_16
#define __sync_fetch_and_nand_16        __builtin_sync_fetch_and_nand_16
#define __sync_add_and_fetch_16         __builtin_sync_add_and_fetch_16
#define __sync_sub_and_fetch_16         __builtin_sync_sub_and_fetch_16
#define __sync_or_and_fetch_16          __builtin_sync_or_and_fetch_16
#define __sync_and_and_fetch_16         __builtin_sync_and_and_fetch_16
#define __sync_xor_and_fetch_16         __builtin_sync_xor_and_fetch_16
#define __sync_nand_and_fetch_16        __builtin_sync_nand_and_fetch_16
#define __sync_bool_compare_and_swap_16 __builtin_sync_bool_compare_and_swap_16
#define __sync_val_compare_and_swap_16  __builtin_sync_val_compare_and_swap_16
#define __sync_lock_test_and_set_16     __builtin_sync_lock_test_and_set_16
__UINT128_TYPE__ __builtin_sync_fetch_and_add_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_fetch_and_sub_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_fetch_and_or_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_fetch_and_and_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_fetch_and_xor_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_fetch_and_nand_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_add_and_fetch_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_sub_and_fetch_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_or_and_fetch_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_and_and_fetch_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_xor_and_fetch_16(void volatile *, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_nand_and_fetch_16(void volatile *, __UINT128_TYPE__);
bool __builtin_sync_bool_compare_and_swap_16(void volatile *, __UINT128_TYPE__, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_val_compare_and_swap_16(void volatile *, __UINT128_TYPE__, __UINT128_TYPE__);
__UINT128_TYPE__ __builtin_sync_lock_test_and_set_16(void volatile *, __UINT128_TYPE__);
#define __atomic_load_16             __builtin_atomic_load_16
#define __atomic_exchange_16         __builtin_atomic_exchange_16
#define __atomic_compare_exchange_16 __builtin_atomic_compare_exchange_16
#define __atomic_store_16            __builtin_atomic_store_16
#define __atomic_add_fetch_16        __builtin_atomic_add_fetch_16
#define __atomic_sub_fetch_16        __builtin_atomic_sub_fetch_16
#define __atomic_and_fetch_16        __builtin_atomic_and_fetch_16
#define __atomic_nand_fetch_16       __builtin_atomic_nand_fetch_16
#define __atomic_xor_fetch_16        __builtin_atomic_xor_fetch_16
#define __atomic_or_fetch_16         __builtin_atomic_or_fetch_16
#define __atomic_fetch_add_16        __builtin_atomic_fetch_add_16
#define __atomic_fetch_sub_16        __builtin_atomic_fetch_sub_16
#define __atomic_fetch_and_16        __builtin_atomic_fetch_and_16
#define __atomic_fetch_nand_16       __builtin_atomic_fetch_nand_16
#define __atomic_fetch_xor_16        __builtin_atomic_fetch_xor_16
#define __atomic_fetch_or_16         __builtin_atomic_fetch_or_16
__UINT128_TYPE__ __builtin_atomic_load_16(void const volatile *, int);
__UINT128_TYPE__ __builtin_atomic_exchange_16(void volatile *, __UINT128_TYPE__, int);
bool __builtin_atomic_compare_exchange_16(void volatile *, void *, __UINT128_TYPE__, bool, int, int);
void __builtin_atomic_store_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_add_fetch_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_sub_fetch_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_and_fetch_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_nand_fetch_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_xor_fetch_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_or_fetch_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_fetch_add_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_fetch_sub_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_fetch_and_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_fetch_nand_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_fetch_xor_16(void volatile *, __UINT128_TYPE__, int);
__UINT128_TYPE__ __builtin_atomic_fetch_or_16(void volatile *, __UINT128_TYPE__, int);

/* This  one works though, which I presume is  because it was created after the version of
 * intellisense that I'm using, so intellisense couldn't possibly have known about it back
 * then... */
__UINT128_TYPE__ __builtin_speculation_safe_value_16(__UINT128_TYPE__, __UINT128_TYPE__ = 0);
#endif /* __UINT128_TYPE__ */

// __builtin_infd32();
// __builtin_infd64();
// __builtin_infd128();
// __builtin_nand32();
// __builtin_nand64();
// __builtin_nand128();
// __builtin_finited32();
// __builtin_finited64();
// __builtin_finited128();
// __builtin_isinfd32();
// __builtin_isinfd64();
// __builtin_isinfd128();
// __builtin_isnand32();
// __builtin_isnand64();
// __builtin_isnand128();
// __builtin_signbitd32();
// __builtin_signbitd64();
// __builtin_signbitd128();
// __builtin_fabsd32();
// __builtin_fabsd64();
// __builtin_fabsd128();
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
// __builtin_ceilf16();
// __builtin_ceilf32();
// __builtin_ceilf64();
// __builtin_ceilf128();
// __builtin_ceilf32x();
// __builtin_ceilf64x();
// __builtin_ceilf128x();
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

#ifdef __cpp_transactional_memory
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
// __builtin__ITM_memcpyRnWt();
// __builtin__ITM_memcpyRtWn();
#endif /* __cpp_transactional_memory */

#ifdef _OPENACC
// __builtin_acc_get_device_type()
// __builtin_GOACC_data_start()
// __builtin_GOACC_data_end()
// __builtin_GOACC_enter_exit_data()
// __builtin_GOACC_parallel()
// __builtin_GOACC_update()
// __builtin_GOACC_wait()
// __builtin_GOACC_get_thread_num()
// __builtin_GOACC_get_num_threads()
// __builtin_GOACC_parallel_keyed();
// __builtin_GOACC_declare();
// __builtin_goacc_parlevel_id();
// __builtin_goacc_parlevel_size();
#endif /* _OPENACC */

#if defined(_OPENACC) || defined(_OPENMP)
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
#endif /* _OPENACC || _OPENMP */


/* For some weird reason, intellisense defines these builtins as macros,
 * on-top of already defining them as functions... (there may be more of
 * these, but these are all the ones I've encountered thus far) */
#ifdef __builtin_acosf
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
#endif /* __builtin_acosf */

#endif /* !____INTELLISENSE_STDINC_SYNTAX_GCC_H */
