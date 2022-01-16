/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef ____INTELLISENSE_STDINC_COMMON_H
#define ____INTELLISENSE_STDINC_COMMON_H 1

#ifndef __INTELLISENSE__
#error "This header is only meant for syntax highlighting. - Don't let your real compiler see it!"
#endif /* !__INTELLISENSE__ */

#ifndef __cplusplus
#error "Syntax highlighting depends on C++ features being available"
#endif /* !__cplusplus */

#undef __event

namespace __intern {

template<class __UID, bool __ALLOW_INT_OPS, class __T>
class ____intellisense_altint {
	__T __v;

public:
	bool operator!() const;
	explicit operator bool() const throw();
	explicit operator char() const throw();
	explicit operator short() const throw();
	explicit operator int() const throw();
	explicit operator long() const throw();
	explicit operator long long() const throw();
	explicit operator signed char() const throw();
	explicit operator unsigned char() const throw();
	explicit operator unsigned short() const throw();
	explicit operator unsigned int() const throw();
	explicit operator unsigned long() const throw();
	explicit operator unsigned long long() const throw();
	template<class __S> explicit operator __S *() const throw();
	____intellisense_altint operator+() const throw();
	____intellisense_altint operator-() const throw();
	____intellisense_altint operator~() const throw();
	____intellisense_altint &operator++() throw();
	____intellisense_altint &operator--() throw();
	____intellisense_altint operator++(int) throw();
	____intellisense_altint operator--(int) throw();
	____intellisense_altint operator+(____intellisense_altint const &) const throw();
	____intellisense_altint operator+(__T) const throw();
	____intellisense_altint operator-(____intellisense_altint const &) const throw();
	____intellisense_altint operator-(__T) const throw();
	____intellisense_altint operator*(____intellisense_altint const &)const throw();
	____intellisense_altint operator*(__T) const throw();
	____intellisense_altint operator/(____intellisense_altint const &) const throw();
	____intellisense_altint operator/(__T) const throw();
	____intellisense_altint operator%(____intellisense_altint const &) const throw();
	____intellisense_altint operator%(__T) const throw();
	____intellisense_altint operator|(____intellisense_altint const &) const throw();
	____intellisense_altint operator|(__T) const throw();
	____intellisense_altint operator&(____intellisense_altint const &)const throw();
	____intellisense_altint operator&(__T) const throw();
	____intellisense_altint operator^(____intellisense_altint const &) const throw();
	____intellisense_altint operator^(__T) const throw();
	____intellisense_altint operator<<(unsigned int) const throw();
	____intellisense_altint operator>>(unsigned int) const throw();
	____intellisense_altint &operator+=(____intellisense_altint const &) throw();
	____intellisense_altint &operator+=(__T) throw();
	____intellisense_altint &operator-=(____intellisense_altint const &) throw();
	____intellisense_altint &operator-=(__T) throw();
	____intellisense_altint &operator*=(____intellisense_altint const &) throw();
	____intellisense_altint &operator*=(__T) throw();
	____intellisense_altint &operator/=(____intellisense_altint const &) throw();
	____intellisense_altint &operator/=(__T) throw();
	____intellisense_altint &operator%=(____intellisense_altint const &) throw();
	____intellisense_altint &operator%=(__T) throw();
	____intellisense_altint &operator|=(____intellisense_altint const &) throw();
	____intellisense_altint &operator|=(__T) throw();
	____intellisense_altint &operator&=(____intellisense_altint const &) throw();
	____intellisense_altint &operator&=(__T) throw();
	____intellisense_altint &operator^=(____intellisense_altint const &) throw();
	____intellisense_altint &operator^=(__T) throw();
	____intellisense_altint &operator<<=(unsigned int) throw();
	____intellisense_altint &operator>>=(unsigned int) throw();
	bool operator<(____intellisense_altint const &) const throw();
	bool operator<(__T const &) const throw();
	bool operator<=(____intellisense_altint const &) const throw();
	bool operator<=(__T const &) const throw();
	bool operator==(____intellisense_altint const &) const throw();
	bool operator==(__T const &) const throw();
	bool operator!=(____intellisense_altint const &) const throw();
	bool operator!=(__T const &) const throw();
	bool operator>(____intellisense_altint const &) const throw();
	bool operator>(__T const &) const throw();
	bool operator>=(____intellisense_altint const &) const throw();
	bool operator>=(__T const &) const throw();

	____intellisense_altint()                                = default;
	____intellisense_altint(____intellisense_altint const &) = default;
	____intellisense_altint &operator=(____intellisense_altint const &) throw()                                                = default;
	template<class __UID2, bool __ALLOW_INT_OPS2, class __T2> explicit ____intellisense_altint(____intellisense_altint<__UID2, __ALLOW_INT_OPS2, __T2> &&) throw()      = default;
	template<class __UID2, bool __ALLOW_INT_OPS2, class __T2> explicit ____intellisense_altint(____intellisense_altint<__UID2, __ALLOW_INT_OPS2, __T2> const &) throw() = default;
	template<class __S> explicit ____intellisense_altint(__S *) throw()                                                            = default;

	____intellisense_altint(decltype(nullptr)); /* Allow direct conversion from `0' */
	____intellisense_altint(char) throw();
	____intellisense_altint(short) throw();
	____intellisense_altint(int) throw();
	____intellisense_altint(long) throw();
	____intellisense_altint(long long) throw();
	____intellisense_altint(signed char) throw();
	____intellisense_altint(unsigned char) throw();
	____intellisense_altint(unsigned short) throw();
	____intellisense_altint(unsigned int) throw();
	____intellisense_altint(unsigned long) throw();
	____intellisense_altint(unsigned long long) throw();
#if 0
	____intellisense_altint(wchar_t) throw();
#endif
#if 0
	____intellisense_altint(char16_t) throw();
	____intellisense_altint(char32_t) throw();
#endif
};

template<class __UID, class __T>
class ____intellisense_altint<__UID, false, __T> {
	__T __v;

public:
	bool operator!() const;
	explicit operator bool() const throw();
	explicit operator char() const throw();
	explicit operator short() const throw();
	explicit operator int() const throw();
	explicit operator long() const throw();
	explicit operator long long() const throw();
	explicit operator signed char() const throw();
	explicit operator unsigned char() const throw();
	explicit operator unsigned short() const throw();
	explicit operator unsigned int() const throw();
	explicit operator unsigned long() const throw();
	explicit operator unsigned long long() const throw();
	template<class __S> explicit operator __S *() const throw();
	____intellisense_altint operator+() const throw();
	____intellisense_altint operator-() const throw();
	____intellisense_altint operator~() const throw();
	____intellisense_altint &operator++() throw();
	____intellisense_altint &operator--() throw();
	____intellisense_altint operator++(int) throw();
	____intellisense_altint operator--(int) throw();
	____intellisense_altint operator+(____intellisense_altint const &) const throw();
	____intellisense_altint operator+(__T) const throw();
	____intellisense_altint operator-(____intellisense_altint const &) const throw();
	____intellisense_altint operator-(__T) const throw();
	____intellisense_altint operator*(____intellisense_altint const &)const throw();
	____intellisense_altint operator*(__T) const throw();
	____intellisense_altint operator/(____intellisense_altint const &) const throw();
	____intellisense_altint operator/(__T) const throw();
	____intellisense_altint operator%(____intellisense_altint const &) const throw();
	____intellisense_altint operator%(__T) const throw();
	____intellisense_altint operator|(____intellisense_altint const &) const throw();
	____intellisense_altint operator|(__T) const throw();
	____intellisense_altint operator&(____intellisense_altint const &)const throw();
	____intellisense_altint operator&(__T) const throw();
	____intellisense_altint operator^(____intellisense_altint const &) const throw();
	____intellisense_altint operator^(__T) const throw();
	____intellisense_altint operator<<(unsigned int) const throw();
	____intellisense_altint operator>>(unsigned int) const throw();
	____intellisense_altint &operator+=(____intellisense_altint const &) throw();
	____intellisense_altint &operator+=(__T) throw();
	____intellisense_altint &operator-=(____intellisense_altint const &) throw();
	____intellisense_altint &operator-=(__T) throw();
	____intellisense_altint &operator*=(____intellisense_altint const &) throw();
	____intellisense_altint &operator*=(__T) throw();
	____intellisense_altint &operator/=(____intellisense_altint const &) throw();
	____intellisense_altint &operator/=(__T) throw();
	____intellisense_altint &operator%=(____intellisense_altint const &) throw();
	____intellisense_altint &operator%=(__T) throw();
	____intellisense_altint &operator|=(____intellisense_altint const &) throw();
	____intellisense_altint &operator|=(__T) throw();
	____intellisense_altint &operator&=(____intellisense_altint const &) throw();
	____intellisense_altint &operator&=(__T) throw();
	____intellisense_altint &operator^=(____intellisense_altint const &) throw();
	____intellisense_altint &operator^=(__T) throw();
	____intellisense_altint &operator<<=(unsigned int) throw();
	____intellisense_altint &operator>>=(unsigned int) throw();
	bool operator<(____intellisense_altint const &) const throw();
	bool operator<=(____intellisense_altint const &) const throw();
	bool operator==(____intellisense_altint const &) const throw();
	bool operator!=(____intellisense_altint const &) const throw();
	bool operator>(____intellisense_altint const &) const throw();
	bool operator>=(____intellisense_altint const &) const throw();

	____intellisense_altint()                                = default;
	____intellisense_altint(____intellisense_altint const &) = default;
	____intellisense_altint &operator=(____intellisense_altint const &) throw()                                                = default;
	template<class __UID2, bool __ALLOW_INT_OPS2, class __T2> explicit ____intellisense_altint(____intellisense_altint<__UID2, __ALLOW_INT_OPS2, __T2> &&) throw()      = default;
	template<class __UID2, bool __ALLOW_INT_OPS2, class __T2> explicit ____intellisense_altint(____intellisense_altint<__UID2, __ALLOW_INT_OPS2, __T2> const &) throw() = default;
	template<class __S> explicit ____intellisense_altint(__S *) throw()                                                            = default;

	____intellisense_altint(decltype(nullptr)); /* Allow direct conversion from `0' */
	explicit ____intellisense_altint(char) throw();
	explicit ____intellisense_altint(short) throw();
	explicit ____intellisense_altint(int) throw();
	explicit ____intellisense_altint(long) throw();
	explicit ____intellisense_altint(long long) throw();
	explicit ____intellisense_altint(signed char) throw();
	explicit ____intellisense_altint(unsigned char) throw();
	explicit ____intellisense_altint(unsigned short) throw();
	explicit ____intellisense_altint(unsigned int) throw();
	explicit ____intellisense_altint(unsigned long) throw();
	explicit ____intellisense_altint(unsigned long long) throw();
#if 0
	explicit ____intellisense_altint(wchar_t) throw();
#endif
#if 0
	explicit ____intellisense_altint(char16_t) throw();
	explicit ____intellisense_altint(char32_t) throw();
#endif
};


template<class __T> struct ____INTELLISENSE_isarith { enum { __value = false }; };
template<class __T> struct ____INTELLISENSE_issigned { enum { __value = false }; };
template<class __T> struct ____INTELLISENSE_isunsigned { enum { __value = false }; };
template<class __T> struct ____INTELLISENSE_isfloat { enum { __value = false }; };
template<> struct ____INTELLISENSE_isarith<bool> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<wchar_t> { enum { __value = true }; };
#if defined(_WCHAR_T_DEFINED) || defined(__GNUC__)
template<> struct ____INTELLISENSE_isarith<char16_t> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<char32_t> { enum { __value = true }; };
#endif /* _WCHAR_T_DEFINED || __GNUC__ */
template<> struct ____INTELLISENSE_isarith<char> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<signed char> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<unsigned char> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<short> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<unsigned short> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<int> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<unsigned int> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<long> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<unsigned long> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<long long> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<unsigned long long> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isarith<decltype(nullptr)> { enum { __value = true }; };
template<class __T> struct ____INTELLISENSE_isarith<__T *> { enum { __value = true }; };

template<> struct ____INTELLISENSE_issigned<signed char> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isunsigned<unsigned char> { enum { __value = true }; };
template<> struct ____INTELLISENSE_issigned<short> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isunsigned<unsigned short> { enum { __value = true }; };
template<> struct ____INTELLISENSE_issigned<int> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isunsigned<unsigned int> { enum { __value = true }; };
template<> struct ____INTELLISENSE_issigned<long> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isunsigned<unsigned long> { enum { __value = true }; };
template<> struct ____INTELLISENSE_issigned<long long> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isunsigned<unsigned long long> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isfloat<float> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isfloat<double> { enum { __value = true }; };
template<> struct ____INTELLISENSE_isfloat<long double> { enum { __value = true }; };

template<class __UID, bool __ALLOW_INT_OPS, class __T> struct ____INTELLISENSE_isarith<____intellisense_altint<__UID, __ALLOW_INT_OPS, __T> > { enum{__value=____INTELLISENSE_isarith<__T>::__value}; };
template<class __UID, bool __ALLOW_INT_OPS, class __T> struct ____INTELLISENSE_issigned<____intellisense_altint<__UID, __ALLOW_INT_OPS, __T> > { enum{__value=____INTELLISENSE_issigned<__T>::__value}; };
template<class __UID, bool __ALLOW_INT_OPS, class __T> struct ____INTELLISENSE_isunsigned<____intellisense_altint<__UID, __ALLOW_INT_OPS, __T> > { enum{__value=____INTELLISENSE_isunsigned<__T>::__value}; };

template<bool __V, class __T> struct ____INTELLISENSE_enableif { typedef __T __type; };
template<class __T> struct ____INTELLISENSE_enableif<false, __T> {};

template<class __TA, class __TB, class __TR>
typename ____INTELLISENSE_enableif<
	____INTELLISENSE_isarith<__TA>::__value &&
	____INTELLISENSE_isarith<__TB>::__value &&
	____INTELLISENSE_issigned<__TR>::__value,
bool>::__type __intellisense_overflow_sadd(__TA __lhs, __TB __rhs, __TR *__res);
template<class __TA, class __TB, class __TR>
typename ____INTELLISENSE_enableif<
	____INTELLISENSE_isarith<__TA>::__value &&
	____INTELLISENSE_isarith<__TB>::__value &&
	____INTELLISENSE_isunsigned<__TR>::__value,
bool>::__type __intellisense_overflow_uadd(__TA __lhs, __TB __rhs, __TR *__res);


template<class __TA, class __TB, class __TR>
typename ____INTELLISENSE_enableif<
	____INTELLISENSE_isarith<__TA>::__value &&
	____INTELLISENSE_isarith<__TB>::__value &&
	____INTELLISENSE_issigned<__TR>::__value,
bool>::__type __intellisense_overflow_ssub(__TA __lhs, __TB __rhs, __TR *__res);
template<class __TA, class __TB, class __TR>
typename ____INTELLISENSE_enableif<
	____INTELLISENSE_isarith<__TA>::__value &&
	____INTELLISENSE_isarith<__TB>::__value &&
	____INTELLISENSE_isunsigned<__TR>::__value,
bool>::__type __intellisense_overflow_usub(__TA __lhs, __TB __rhs, __TR *__res);

template<class __TA, class __TB, class __TR>
typename ____INTELLISENSE_enableif<
	____INTELLISENSE_isarith<__TA>::__value &&
	____INTELLISENSE_isarith<__TB>::__value &&
	____INTELLISENSE_issigned<__TR>::__value,
bool>::__type __intellisense_overflow_smul(__TA __lhs, __TB __rhs, __TR *__res);
template<class __TA, class __TB, class __TR>
typename ____INTELLISENSE_enableif<
	____INTELLISENSE_isarith<__TA>::__value &&
	____INTELLISENSE_isarith<__TB>::__value &&
	____INTELLISENSE_isunsigned<__TR>::__value,
bool>::__type __intellisense_overflow_umul(__TA __lhs, __TB __rhs, __TR *__res);



template<class __T> struct ____INTELLISENSE_promote;
template<> struct ____INTELLISENSE_promote<char> { typedef int __type; };
template<> struct ____INTELLISENSE_promote<signed char> { typedef int __type; };
template<> struct ____INTELLISENSE_promote<unsigned char> { typedef int __type; };
template<> struct ____INTELLISENSE_promote<short> { typedef int __type; };
template<> struct ____INTELLISENSE_promote<unsigned short> { typedef int __type; };
template<> struct ____INTELLISENSE_promote<int> { typedef int __type; };
template<> struct ____INTELLISENSE_promote<unsigned int> { typedef unsigned int __type; };
template<> struct ____INTELLISENSE_promote<long> { typedef long __type; };
template<> struct ____INTELLISENSE_promote<unsigned long> { typedef unsigned long __type; };
template<> struct ____INTELLISENSE_promote<long long> { typedef long long __type; };
template<> struct ____INTELLISENSE_promote<unsigned long long> { typedef unsigned long long __type; };

#pragma pack(push,1)
/* Used to implement endian-specific integers capable of
 * emitting  warnings  when  attempted  to  be  used  as
 * regular  integers  without prior  casting  using the.
 * (le|be)swap_(16|32|64)  functions  from  <byteswap.h>
 * >> Again: Only meant to highlight usage errors in visual studio. */
template<int endian,class __T> class ____intellisense_endianint {
	__T __v;

public:
	/*	bool operator ! () const; */
	explicit operator bool() const throw();
	explicit operator char() const throw();
	explicit operator short() const throw();
	explicit operator int() const throw();
	explicit operator long() const throw();
	explicit operator long long() const throw();
	explicit operator signed char() const throw();
	explicit operator unsigned char() const throw();
	explicit operator unsigned short() const throw();
	explicit operator unsigned int() const throw();
	explicit operator unsigned long() const throw();
	explicit operator unsigned long long() const throw();
	//____intellisense_endianint &operator = (__T) throw();
	____intellisense_endianint &operator=(____intellisense_endianint const &) throw() = default;
	template<class __S> bool operator<(____intellisense_endianint<endian, __S> const &) const throw();
	template<class __S> bool operator<=(____intellisense_endianint<endian, __S> const &) const throw();
	template<class __S> bool operator==(____intellisense_endianint<endian, __S> const &) const throw();
	template<class __S> bool operator!=(____intellisense_endianint<endian, __S> const &) const throw();
	template<class __S> bool operator>(____intellisense_endianint<endian, __S> const &) const throw();
	template<class __S> bool operator>=(____intellisense_endianint<endian, __S> const &) const throw();
	template<class __S> ____intellisense_endianint operator|(____intellisense_endianint<endian, __S> const &) const throw();
	template<class __S> ____intellisense_endianint operator&(____intellisense_endianint<endian, __S> const &) const throw();
	template<class __S> ____intellisense_endianint operator^(____intellisense_endianint<endian, __S> const &) const throw();
	template<class __S> ____intellisense_endianint &operator|=(____intellisense_endianint<endian, __S> const &) throw();
	template<class __S> ____intellisense_endianint &operator&=(____intellisense_endianint<endian, __S> const &) throw();
	template<class __S> ____intellisense_endianint &operator^=(____intellisense_endianint<endian, __S> const &) throw();
	____intellisense_endianint() = default;
	____intellisense_endianint(____intellisense_endianint const &) = default;
	explicit ____intellisense_endianint(char) throw();
	explicit ____intellisense_endianint(short) throw();
	explicit ____intellisense_endianint(int) throw();
	explicit ____intellisense_endianint(long) throw();
	explicit ____intellisense_endianint(long long) throw();
	explicit ____intellisense_endianint(signed char) throw();
	explicit ____intellisense_endianint(unsigned char) throw();
	explicit ____intellisense_endianint(unsigned short) throw();
	explicit ____intellisense_endianint(unsigned int) throw();
	explicit ____intellisense_endianint(unsigned long) throw();
	explicit ____intellisense_endianint(unsigned long long) throw();
};

#pragma pack(pop)

__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned short> __intellisense_htole16(unsigned short);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned short> __intellisense_htobe16(unsigned short);
__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned int> __intellisense_htole32(int);
__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned int> __intellisense_htole32(unsigned int);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned int> __intellisense_htobe32(int);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned int> __intellisense_htobe32(unsigned int);
__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned long> __intellisense_htole32(long);
__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned long> __intellisense_htole32(unsigned long);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long> __intellisense_htobe32(long);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long> __intellisense_htobe32(unsigned long);
__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned long long> __intellisense_htole64(unsigned long long);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long long> __intellisense_htobe64(unsigned long long);
unsigned short __intellisense_letoh16(unsigned short);
unsigned short __intellisense_letoh16(__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned short>);
unsigned short __intellisense_betoh16(unsigned short);
unsigned short __intellisense_betoh16(__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned short>);
unsigned int __intellisense_letoh32(int);
unsigned int __intellisense_letoh32(unsigned int);
unsigned int __intellisense_letoh32(__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned int>);
unsigned int __intellisense_betoh32(int);
unsigned int __intellisense_betoh32(unsigned int);
unsigned int __intellisense_betoh32(__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned int>);
unsigned long __intellisense_letoh32(long);
unsigned long __intellisense_letoh32(unsigned long);
unsigned long __intellisense_letoh32(__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned long>);
unsigned long __intellisense_betoh32(long);
unsigned long __intellisense_betoh32(unsigned long);
unsigned long __intellisense_betoh32(__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long>);
unsigned long long __intellisense_letoh64(unsigned long long);
unsigned long long __intellisense_letoh64(__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned long long>);
unsigned long long __intellisense_betoh64(unsigned long long);
unsigned long long __intellisense_betoh64(__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long long>);

unsigned short __intellisense_leswap16(__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned short>);
unsigned short __intellisense_beswap16(__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned short>);
unsigned int __intellisense_leswap32(__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned int>);
unsigned int __intellisense_beswap32(__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned int>);
unsigned long __intellisense_leswap32(__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned long>);
unsigned long __intellisense_beswap32(__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long>);
unsigned long long __intellisense_leswap64(__intern::____intellisense_endianint</*__ORDER_LITTLE_ENDIAN__*/ 1234, unsigned long long>);
unsigned long long __intellisense_beswap64(__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long long>);
#if __BYTE_ORDER__ == /*__ORDER_LITTLE_ENDIAN__*/ 1234
unsigned short __intellisense_leswap16(unsigned short);
unsigned int __intellisense_leswap32(unsigned int);
unsigned long __intellisense_leswap32(unsigned long);
unsigned long long __intellisense_leswap64(unsigned long long);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned short> __intellisense_beswap16(unsigned short);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned int> __intellisense_beswap32(unsigned int);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long> __intellisense_beswap32(unsigned long);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long long> __intellisense_beswap64(unsigned long long);
#else /* __BYTE_ORDER__ == /*__ORDER_LITTLE_ENDIAN__*/ 1234 */
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned short> __intellisense_leswap16(unsigned short);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned int> __intellisense_leswap32(unsigned int);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long> __intellisense_leswap32(unsigned long);
__intern::____intellisense_endianint</*__ORDER_BIG_ENDIAN__*/ 4321, unsigned long long> __intellisense_leswap64(unsigned long long);
unsigned short __intellisense_beswap16(unsigned short);
unsigned int __intellisense_beswap32(unsigned int);
unsigned long __intellisense_beswap32(unsigned long);
unsigned long long __intellisense_beswap64(unsigned long long);
#endif /* __BYTE_ORDER__ != /*__ORDER_LITTLE_ENDIAN__*/ 1234 */

}

#ifndef __INTELLISENSE_GCC__
unsigned short __builtin_bswap16(unsigned short);
unsigned int __builtin_bswap32(unsigned int);
unsigned long __builtin_bswap32(unsigned long);
unsigned long long __builtin_bswap64(unsigned long long);
#endif /* !__INTELLISENSE_GCC__ */

template<class __UID, bool __ALLOW_INT_OPS, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator + (__S,__intern::____intellisense_altint<__UID, __ALLOW_INT_OPS, __T>);
template<class __UID, bool __ALLOW_INT_OPS, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator - (__S,__intern::____intellisense_altint<__UID, __ALLOW_INT_OPS, __T>);
template<class __UID, bool __ALLOW_INT_OPS, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator * (__S,__intern::____intellisense_altint<__UID, __ALLOW_INT_OPS, __T>);
template<class __UID, bool __ALLOW_INT_OPS, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator / (__S,__intern::____intellisense_altint<__UID, __ALLOW_INT_OPS, __T>);
template<class __UID, bool __ALLOW_INT_OPS, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator % (__S,__intern::____intellisense_altint<__UID, __ALLOW_INT_OPS, __T>);
template<class __UID, bool __ALLOW_INT_OPS, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator & (__S,__intern::____intellisense_altint<__UID, __ALLOW_INT_OPS, __T>);
template<class __UID, bool __ALLOW_INT_OPS, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator | (__S,__intern::____intellisense_altint<__UID, __ALLOW_INT_OPS, __T>);
template<class __UID, bool __ALLOW_INT_OPS, class __T, class __S> typename __intern::____INTELLISENSE_promote<__S>::__type operator ^ (__S,__intern::____intellisense_altint<__UID, __ALLOW_INT_OPS, __T>);



template<class __TA, class __TB, class __TR>
typename __intern::____INTELLISENSE_enableif<
	__intern::____INTELLISENSE_isarith<__TA>::__value &&
	__intern::____INTELLISENSE_isarith<__TB>::__value &&
	__intern::____INTELLISENSE_isarith<__TR>::__value,
bool>::__type __builtin_add_overflow(__TA __lhs, __TB __rhs, __TR *__res);

template<class __TA, class __TB, class __TR>
typename __intern::____INTELLISENSE_enableif<
	__intern::____INTELLISENSE_isarith<__TA>::__value &&
	__intern::____INTELLISENSE_isarith<__TB>::__value &&
	__intern::____INTELLISENSE_isarith<__TR>::__value,
bool>::__type __builtin_sub_overflow(__TA __lhs, __TB __rhs, __TR *__res);

template<class __TA, class __TB, class __TR>
typename __intern::____INTELLISENSE_enableif<
	__intern::____INTELLISENSE_isarith<__TA>::__value &&
	__intern::____INTELLISENSE_isarith<__TB>::__value &&
	__intern::____INTELLISENSE_isarith<__TR>::__value,
bool>::__type __builtin_mul_overflow(__TA __lhs, __TB __rhs, __TR *__res);


template<class __TA, class __TB, class __TR>
typename __intern::____INTELLISENSE_enableif<
	__intern::____INTELLISENSE_isarith<__TA>::__value &&
	__intern::____INTELLISENSE_isarith<__TB>::__value &&
	__intern::____INTELLISENSE_isarith<__TR>::__value,
bool>::__type __builtin_add_overflow_p(__TA __lhs, __TB __rhs, __TR __res_type);

template<class __TA, class __TB, class __TR>
typename __intern::____INTELLISENSE_enableif<
	__intern::____INTELLISENSE_isarith<__TA>::__value &&
	__intern::____INTELLISENSE_isarith<__TB>::__value &&
	__intern::____INTELLISENSE_isarith<__TR>::__value,
bool>::__type __builtin_sub_overflow_p(__TA __lhs, __TB __rhs, __TR __res_type);

template<class __TA, class __TB, class __TR>
typename __intern::____INTELLISENSE_enableif<
	__intern::____INTELLISENSE_isarith<__TA>::__value &&
	__intern::____INTELLISENSE_isarith<__TB>::__value &&
	__intern::____INTELLISENSE_isarith<__TR>::__value,
bool>::__type __builtin_mul_overflow_p(__TA __lhs, __TB __rhs, __TR __res_type);


bool __builtin_sadd_overflow(int __a, int __b, int *__res);
bool __builtin_saddl_overflow(long __a, long __b, long *__res);
bool __builtin_saddll_overflow(long long __a, long long __b, long long *__res);
bool __builtin_uadd_overflow(unsigned int __a, unsigned int __b, unsigned int *__res);
bool __builtin_uaddl_overflow(unsigned long __a, unsigned long __b, unsigned long *__res);
bool __builtin_uaddll_overflow(unsigned long long __a, unsigned long long __b, unsigned long long *__res);
bool __builtin_ssub_overflow(int __a, int __b, int *__res);
bool __builtin_ssubl_overflow(long __a, long __b, long *__res);
bool __builtin_ssubll_overflow(long long __a, long long __b, long long *__res);
bool __builtin_usub_overflow(unsigned int __a, unsigned int __b, unsigned int *__res);
bool __builtin_usubl_overflow(unsigned long __a, unsigned long __b, unsigned long *__res);
bool __builtin_usubll_overflow(unsigned long long __a, unsigned long long __b, unsigned long long *__res);
bool __builtin_smul_overflow(int __a, int __b, int *__res);
bool __builtin_smull_overflow(long __a, long __b, long *__res);
bool __builtin_smulll_overflow(long long __a, long long __b, long long *__res);
bool __builtin_umul_overflow(unsigned int __a, unsigned int __b, unsigned int *__res);
bool __builtin_umull_overflow(unsigned long __a, unsigned long __b, unsigned long *__res);
bool __builtin_umulll_overflow(unsigned long long __a, unsigned long long __b, unsigned long long *__res);


/* Fix some broken c++ feature macros */
#ifdef __cplusplus
#if __cplusplus >= 201406L
#undef __cpp_static_assert
#define __cpp_static_assert 201411
#endif
#endif /* __cplusplus */


#endif /* !____INTELLISENSE_STDINC_COMMON_H */
