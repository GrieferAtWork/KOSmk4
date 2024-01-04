/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _CXX_BITS_MAKE_SIGN_H
#define _CXX_BITS_MAKE_SIGN_H 1

#include <__stdcxx.h>

#include <hybrid/typecore.h>

#include "conditional.h"
#include "integral_constant.h"
#include "is_enum.h"
#include "is_integral.h"
#include "remove_cv.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<class __T> struct __make_signed { typedef __T type; };
template<class __T> struct __make_unsigned { typedef __T type; };
#ifdef __CHAR_UNSIGNED__
template<> struct __make_signed<char> { typedef signed char type; };
#else /* __CHAR_UNSIGNED__ */
template<> struct __make_unsigned<char> { typedef unsigned char type; };
#endif /* !__CHAR_UNSIGNED__ */
template<> struct __make_signed<unsigned char> { typedef signed char type; };
template<> struct __make_signed<unsigned short> { typedef short type; };
template<> struct __make_signed<unsigned int> { typedef int type; };
template<> struct __make_signed<unsigned long> { typedef long type; };
template<> struct __make_unsigned<signed char> { typedef unsigned char type; };
template<> struct __make_unsigned<short> { typedef unsigned short type; };
template<> struct __make_unsigned<int> { typedef unsigned int type; };
template<> struct __make_unsigned<long> { typedef unsigned long type; };
#ifdef __native_wchar_t_defined
#ifdef __WCHAR_UNSIGNED__
template<> struct __make_signed<wchar_t> { typedef __TYPEFOR_INTIB(__SIZEOF_WCHAR_T__) type; };
#else /* __WCHAR_UNSIGNED__ */
template<> struct __make_unsigned<wchar_t> { typedef __TYPEFOR_UINTIB(__SIZEOF_WCHAR_T__) type; };
#endif /* !__WCHAR_UNSIGNED__ */
#endif /* __native_wchar_t_defined */
#ifdef __native_char16_t_defined
template<> struct __make_signed<char16_t> { typedef __INT_LEAST16_TYPE__ type; };
template<> struct __make_signed<char32_t> { typedef __INT_LEAST32_TYPE__ type; };
#endif /* __native_char16_t_defined */
#ifdef __COMPILER_HAVE_LONGLONG
template<> struct __make_signed<__ULONGLONG> { typedef __LONGLONG type; };
template<> struct __make_unsigned<__LONGLONG> { typedef __ULONGLONG type; };
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
template<> struct __make_signed<unsigned __int8> { typedef __int8 type; };
template<> struct __make_unsigned<__int8> { typedef unsigned __int8 type; };
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
template<> struct __make_signed<unsigned __int16> { typedef __int16 type; };
template<> struct __make_unsigned<__int16> { typedef unsigned __int16 type; };
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
template<> struct __make_signed<unsigned __int32> { typedef __int32 type; };
template<> struct __make_unsigned<__int32> { typedef unsigned __int32 type; };
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
template<> struct __make_signed<unsigned __int64> { typedef __int64 type; };
template<> struct __make_unsigned<__int64> { typedef unsigned __int64 type; };
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */
template<class __T, bool __IsInt, bool __IsEnum> struct __make_signed_sel {};
template<class __T, bool __IsInt, bool __IsEnum> struct __make_unsigned_sel {};
template<class __T> struct __make_signed_sel<__T, true, false>
    : public __make_signed<typename __NAMESPACE_STD_SYM remove_cv<__T>::type> {};
template<class __T> struct __make_unsigned_sel<__T, true, false>
    : public __make_unsigned<typename __NAMESPACE_STD_SYM remove_cv<__T>::type> {};
template<class __T> struct __make_signed_sel<__T,false,true>
	: public __NAMESPACE_STD_SYM conditional<(sizeof(__T) <= sizeof(char)), signed char,
    typename __NAMESPACE_STD_SYM conditional<(sizeof(__T) <= sizeof(short)), signed short,
    typename __NAMESPACE_STD_SYM conditional<(sizeof(__T) <= sizeof(int)), signed int,
#ifdef __COMPILER_HAVE_LONGLONG
    typename __NAMESPACE_STD_SYM conditional<(sizeof(__T) <= sizeof(long)),signed long,__LONGLONG>::type
#else /* __COMPILER_HAVE_LONGLONG */
    signed long
#endif /* !__COMPILER_HAVE_LONGLONG */
>::type>::type> {};
template<class __T> struct __make_unsigned_sel<__T,false,true>
    : public __NAMESPACE_STD_SYM conditional<(sizeof(__T) <= sizeof(char)), unsigned char,
    typename __NAMESPACE_STD_SYM conditional<(sizeof(__T) <= sizeof(short)),unsigned short,
    typename __NAMESPACE_STD_SYM conditional<(sizeof(__T) <= sizeof(int)),unsigned int,
#ifdef __COMPILER_HAVE_LONGLONG
    typename __NAMESPACE_STD_SYM conditional<(sizeof(__T) <= sizeof(long)),unsigned long,__ULONGLONG>::type
#else /* __COMPILER_HAVE_LONGLONG */
    signed long
#endif /* !__COMPILER_HAVE_LONGLONG */
>::type>::type> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct make_signed {
	typedef typename __NAMESPACE_INT_SYM __make_signed_sel<__T, is_integral<__T>::value, is_enum<__T>::value>::type type;
};
template<class __T> struct make_unsigned {
	typedef typename __NAMESPACE_INT_SYM __make_unsigned_sel<__T, is_integral<__T>::value, is_enum<__T>::value>::type type;
};
__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_MAKE_SIGN_H */
