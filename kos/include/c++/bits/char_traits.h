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
#ifndef _BITS_CHAR_TRAITS_H
#define _BITS_CHAR_TRAITS_H 1

#include <__stdcxx.h>

#include <hybrid/typecore.h>

#include <asm/crt/stdio.h>
#include <bits/types.h>

#include <libc/string.h>

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

template<typename __CharT>
struct char_traits {
	typedef __CharT char_type;
	typedef unsigned long int_type;
	typedef __pos_t pos_type;
	typedef __off_t off_type;
	typedef std::mbstate_t state_type;

	static __CXX_CLASSMEMBER __CXX14_CONSTEXPR void
	assign(__CharT &__dst, __CharT const &__src) __CXX_NOEXCEPT_NCX {
		__dst = __src;
	}

	static __CXX_CLASSMEMBER __CXX11_CONSTEXPR bool
	eq(__CharT const &__lhs, __CharT const &__rhs) __CXX_NOEXCEPT_NCX {
		return __lhs == __rhs;
	}

	static __CXX_CLASSMEMBER __CXX11_CONSTEXPR bool
	lt(__CharT const &__lhs, __CharT const &__rhs) __CXX_NOEXCEPT_NCX {
		return __lhs < __rhs;
	}

	static __CXX_CLASSMEMBER __CXX14_CONSTEXPR int
	compare(__CharT const *__lhs, __CharT const *__rhs, __SIZE_TYPE__ __num_chars) __CXX_NOEXCEPT_NCX {
		return __libc_memcmpc(__lhs, __rhs, __num_chars, sizeof(__CharT));
	}

	static __CXX_CLASSMEMBER __ATTR_PURE __CXX14_CONSTEXPR __SIZE_TYPE__
	length(__CharT const *__string) __CXX_NOEXCEPT_NCX {
		__STATIC_IF(sizeof(__CharT) == 1) {
			return (__SIZE_TYPE__)__libc_strlen((char const *)__string);
		}
		__STATIC_ELSE(sizeof(__CharT) == 1) {
			__SIZE_TYPE__ __i = 0;
			while (!eq(__string[__i], __CharT()))
				++__i;
			return __i;
		}
	}

	static __CXX_CLASSMEMBER __ATTR_PURE __CXX14_CONSTEXPR __CharT const *
	find(__CharT const *__haystack, __SIZE_TYPE__ __num_chars, __CharT const &__needle) __CXX_NOEXCEPT_NCX {
		__STATIC_IF(sizeof(__CharT) == 8) {
			return (__CharT *)__libc_memchrq((__UINT64_TYPE__ *)__haystack, (__UINT64_TYPE__)__needle, __num_chars);
		}
		__STATIC_ELSE(sizeof(__CharT) == 8) {
			__STATIC_IF(sizeof(__CharT) == 4) {
				return (__CharT *)__libc_memchrl((__UINT32_TYPE__ *)__haystack, (__UINT32_TYPE__)__needle, __num_chars);
			}
			__STATIC_ELSE(sizeof(__CharT) == 4) {
				__STATIC_IF(sizeof(__CharT) == 2) {
					return (__CharT *)__libc_memchrw((__UINT16_TYPE__ *)__haystack, (__UINT16_TYPE__)__needle, __num_chars);
				}
				__STATIC_ELSE(sizeof(__CharT) == 2) {
					__STATIC_IF(sizeof(__CharT) == 1) {
						return (__CharT *)__libc_memchr(__haystack, (int)__needle, __num_chars);
					}
					__STATIC_ELSE(sizeof(__CharT) == 1) {
						for (__SIZE_TYPE__ __i = 0; __i < __num_chars; ++__i) {
							if (eq(__haystack[__i], __needle))
								return __haystack + __i;
						}
						return 0;
					}
				}
			}
		}
	}

	static __CXX_CLASSMEMBER __CharT *
	move(__CharT *__dst, __CharT const *__src, __SIZE_TYPE__ __num_chars) __CXX_NOEXCEPT_NCX {
		__STATIC_IF(sizeof(__CharT) == 8) {
			return (__CharT *)__libc_memmoveq(__dst, __src, __num_chars);
		}
		__STATIC_ELSE(sizeof(__CharT) == 8) {
			__STATIC_IF(sizeof(__CharT) == 4) {
				return (__CharT *)__libc_memmovel(__dst, __src, __num_chars);
			}
			__STATIC_ELSE(sizeof(__CharT) == 4) {
				__STATIC_IF(sizeof(__CharT) == 2) {
					return (__CharT *)__libc_memmovew(__dst, __src, __num_chars);
				}
				__STATIC_ELSE(sizeof(__CharT) == 2) {
					return (__CharT *)__libc_memmove(__dst, __src, __num_chars * sizeof(__CharT));
				}
			}
		}
	}

	static __CXX_CLASSMEMBER __CharT *
	copy(__CharT *__dst, __CharT const *__src, __SIZE_TYPE__ __num_chars) __CXX_NOEXCEPT_NCX {
		__STATIC_IF(sizeof(__CharT) == 8) {
			return (__CharT *)__libc_memcpyq(__dst, __src, __num_chars);
		}
		__STATIC_ELSE(sizeof(__CharT) == 8) {
			__STATIC_IF(sizeof(__CharT) == 4) {
				return (__CharT *)__libc_memcpyl(__dst, __src, __num_chars);
			}
			__STATIC_ELSE(sizeof(__CharT) == 4) {
				__STATIC_IF(sizeof(__CharT) == 2) {
					return (__CharT *)__libc_memcpyw(__dst, __src, __num_chars);
				}
				__STATIC_ELSE(sizeof(__CharT) == 2) {
					return (__CharT *)__libc_memcpy(__dst, __src, __num_chars * sizeof(__CharT));
				}
			}
		}
	}

	static __CXX_CLASSMEMBER __CharT *
	assign(__CharT *__dst, __SIZE_TYPE__ __num_chars, __CharT __ch) {
		__STATIC_IF(sizeof(__CharT) == 8) {
			return (__CharT *)__libc_memsetq((__UINT64_TYPE__ *)__dst, (__UINT64_TYPE__)__ch, __num_chars);
		}
		__STATIC_ELSE(sizeof(__CharT) == 8) {
			__STATIC_IF(sizeof(__CharT) == 4) {
				return (__CharT *)__libc_memsetl((__UINT32_TYPE__ *)__dst, (__UINT32_TYPE__)__ch, __num_chars);
			}
			__STATIC_ELSE(sizeof(__CharT) == 4) {
				__STATIC_IF(sizeof(__CharT) == 2) {
					return (__CharT *)__libc_memsetw((__UINT16_TYPE__ *)__dst, (__UINT16_TYPE__)__ch, __num_chars);
				}
				__STATIC_ELSE(sizeof(__CharT) == 2) {
					__STATIC_IF(sizeof(__CharT) == 1) {
						return (__CharT *)__libc_memset(__dst, (int)__ch, __num_chars);
					}
					__STATIC_ELSE(sizeof(__CharT) == 1) {
						for (__SIZE_TYPE__ __i = 0; __i < __num_chars; ++__i)
							__dst[__i] = __ch;
						return __dst;
					}
				}
			}
		}
	}

	static __CXX_CLASSMEMBER __CXX11_CONSTEXPR __CharT
	to_char_type(int_type const &__val) __CXX_NOEXCEPT_NCX {
		return (__CharT)__val;
	}

	static __CXX_CLASSMEMBER __CXX11_CONSTEXPR int_type
	to_int_type(__CharT const &__ch) __CXX_NOEXCEPT_NCX {
		return (int_type)__ch;
	}

	static __CXX_CLASSMEMBER __CXX11_CONSTEXPR bool
	eq_int_type(int_type const &__ch, int_type const &__val) __CXX_NOEXCEPT_NCX {
		return __ch == __val;
	}

	static __CXX_CLASSMEMBER __CXX11_CONSTEXPR int_type eof() __CXX_NOEXCEPT {
#ifdef __EOF
		return (int_type)__EOF;
#else /* __EOF */
		return (int_type)-1;
#endif /* !__EOF */
	}

	static __CXX_CLASSMEMBER __CXX11_CONSTEXPR int_type
	not_eof(int_type const &__val) __CXX_NOEXCEPT_NCX {
		return !eq_int_type(__val, eof()) ? __val : to_int_type(__CharT());
	}
};

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_BITS_CHAR_TRAITS_H */
