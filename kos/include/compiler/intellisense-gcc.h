/* Copyright (c) 2019 Griefer@Work                                            *
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
static_assert(sizeof(long double) == __SIZEOF_LONG_DOUBLE__, "WTF Intellisense?");
#else
#undef __SIZEOF_LONG_DOUBLE__
#define __SIZEOF_LONG_DOUBLE__ __SIZEOF_DOUBLE__
#endif


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

}

#endif /* !____INTELLISENSE_STDINC_SYNTAX_GCC_H */
