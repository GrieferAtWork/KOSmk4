/* HASH CRC-32:0x1f5fac7d */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: ISO C23 (ISO/IEC 9899:2024) */
/* (#) Portability: GNU C Library (/stdlib/stdbit.h) */
/* (#) Portability: GNU Hurd      (/usr/include/stdbit.h) */
#ifndef _STDBIT_H
#define _STDBIT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
#include <hybrid/byteorder.h>
#include <bits/types.h>

#define __STDC_VERSION_STDBIT_H__ 202311L
#define __STDC_ENDIAN_LITTLE__    __ORDER_LITTLE_ENDIAN__
#define __STDC_ENDIAN_BIG__       __ORDER_BIG_ENDIAN__
#define __STDC_ENDIAN_NATIVE__    __BYTE_ORDER__

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_stdc_leading_zeros_uc
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_uc,(unsigned char __x),{ return __x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#else /* __CRT_HAVE_stdc_leading_zeros_uc */
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_zeros_uc)(unsigned char __x) { return __x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_clz(__x); }
#endif /* !__CRT_HAVE_stdc_leading_zeros_uc */
#ifdef __CRT_HAVE_stdc_leading_zeros_us
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_us,(unsigned short __x),{ return __x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#else /* __CRT_HAVE_stdc_leading_zeros_us */
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_zeros_us)(unsigned short __x) { return __x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_clz(__x); }
#endif /* !__CRT_HAVE_stdc_leading_zeros_us */
#ifdef __CRT_HAVE_stdc_leading_zeros_ui
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_ui,(unsigned int __x),{ return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_leading_zeros_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_ui,(unsigned int __x),stdc_leading_zeros_ul,{ return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_leading_zeros_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_ui,(unsigned int __x),stdc_leading_zeros_ull,{ return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#else /* ... */
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_zeros_ui)(unsigned int __x) { return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_leading_zeros_ul
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_ul,(unsigned long __x),{ return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_leading_zeros_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_ul,(unsigned long __x),stdc_leading_zeros_ui,{ return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_leading_zeros_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_ul,(unsigned long __x),stdc_leading_zeros_ull,{ return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#else /* ... */
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_zeros_ul)(unsigned long __x) { return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_leading_ones_uc
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_uc,(unsigned char __x),{ return __x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_clz((unsigned char)~__x); })
#else /* __CRT_HAVE_stdc_leading_ones_uc */
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_ones_uc)(unsigned char __x) { return __x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_clz((unsigned char)~__x); }
#endif /* !__CRT_HAVE_stdc_leading_ones_uc */
#ifdef __CRT_HAVE_stdc_leading_ones_us
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_us,(unsigned short __x),{ return __x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_clz((unsigned short)~__x); })
#else /* __CRT_HAVE_stdc_leading_ones_us */
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_ones_us)(unsigned short __x) { return __x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_clz((unsigned short)~__x); }
#endif /* !__CRT_HAVE_stdc_leading_ones_us */
#ifdef __CRT_HAVE_stdc_leading_ones_ui
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_ui,(unsigned int __x),{ return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_leading_ones_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_ui,(unsigned int __x),stdc_leading_ones_ul,{ return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_leading_ones_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_ui,(unsigned int __x),stdc_leading_ones_ull,{ return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz((unsigned int)~__x); })
#else /* ... */
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_ones_ui)(unsigned int __x) { return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz((unsigned int)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_leading_ones_ul
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_ul,(unsigned long __x),{ return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_leading_ones_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_ul,(unsigned long __x),stdc_leading_ones_ui,{ return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_leading_ones_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_ul,(unsigned long __x),stdc_leading_ones_ull,{ return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz((unsigned long)~__x); })
#else /* ... */
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_ones_ul)(unsigned long __x) { return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz((unsigned long)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_trailing_zeros_uc
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_uc,(unsigned char __x),{ return __x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* __CRT_HAVE_stdc_trailing_zeros_uc */
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_zeros_uc)(unsigned char __x) { return __x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !__CRT_HAVE_stdc_trailing_zeros_uc */
#ifdef __CRT_HAVE_stdc_trailing_zeros_us
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_us,(unsigned short __x),{ return __x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* __CRT_HAVE_stdc_trailing_zeros_us */
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_zeros_us)(unsigned short __x) { return __x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !__CRT_HAVE_stdc_trailing_zeros_us */
#ifdef __CRT_HAVE_stdc_trailing_zeros_ui
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_ui,(unsigned int __x),{ return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_trailing_zeros_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_ui,(unsigned int __x),stdc_trailing_zeros_ul,{ return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_trailing_zeros_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_ui,(unsigned int __x),stdc_trailing_zeros_ull,{ return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* ... */
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_zeros_ui)(unsigned int __x) { return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_trailing_zeros_ul
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_ul,(unsigned long __x),{ return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_trailing_zeros_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_ul,(unsigned long __x),stdc_trailing_zeros_ui,{ return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_trailing_zeros_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_ul,(unsigned long __x),stdc_trailing_zeros_ull,{ return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* ... */
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_zeros_ul)(unsigned long __x) { return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_trailing_ones_uc
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_uc,(unsigned char __x),{ return __x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz((unsigned char)~__x); })
#else /* __CRT_HAVE_stdc_trailing_ones_uc */
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_ones_uc)(unsigned char __x) { return __x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz((unsigned char)~__x); }
#endif /* !__CRT_HAVE_stdc_trailing_ones_uc */
#ifdef __CRT_HAVE_stdc_trailing_ones_us
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_us,(unsigned short __x),{ return __x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned short)~__x); })
#else /* __CRT_HAVE_stdc_trailing_ones_us */
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_ones_us)(unsigned short __x) { return __x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned short)~__x); }
#endif /* !__CRT_HAVE_stdc_trailing_ones_us */
#ifdef __CRT_HAVE_stdc_trailing_ones_ui
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_ui,(unsigned int __x),{ return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_trailing_ones_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_ui,(unsigned int __x),stdc_trailing_ones_ul,{ return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_trailing_ones_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_ui,(unsigned int __x),stdc_trailing_ones_ull,{ return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~__x); })
#else /* ... */
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_ones_ui)(unsigned int __x) { return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_trailing_ones_ul
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_ul,(unsigned long __x),{ return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_trailing_ones_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_ul,(unsigned long __x),stdc_trailing_ones_ui,{ return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_trailing_ones_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_ul,(unsigned long __x),stdc_trailing_ones_ull,{ return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~__x); })
#else /* ... */
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_ones_ul)(unsigned long __x) { return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_leading_one_uc
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_one_uc,(unsigned char __x),{ return __hybrid_ffs(__x); })
#else /* __CRT_HAVE_stdc_first_leading_one_uc */
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_leading_one_uc)(unsigned char __x) { return __hybrid_ffs(__x); }
#endif /* !__CRT_HAVE_stdc_first_leading_one_uc */
#ifdef __CRT_HAVE_stdc_first_leading_one_us
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_one_us,(unsigned short __x),{ return __hybrid_ffs(__x); })
#else /* __CRT_HAVE_stdc_first_leading_one_us */
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_leading_one_us)(unsigned short __x) { return __hybrid_ffs(__x); }
#endif /* !__CRT_HAVE_stdc_first_leading_one_us */
#if __has_builtin(__builtin_ffs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffs)
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ui,(unsigned int __i),ffs,{ return __builtin_ffs(__i); })
#elif defined(__CRT_HAVE_ffs)
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ui,(unsigned int __i),ffs,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)__i); })
#elif defined(__CRT_HAVE_ffsl) && __SIZEOF_INT__ == __SIZEOF_LONG__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ui,(unsigned int __i),ffsl,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)__i); })
#elif defined(__CRT_HAVE_stdc_first_leading_one_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ui,(unsigned int __i),stdc_first_leading_one_ul,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)__i); })
#elif defined(__CRT_HAVE_ffsll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ui,(unsigned int __i),ffsll,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)__i); })
#elif defined(__CRT_HAVE_stdc_first_leading_one_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ui,(unsigned int __i),stdc_first_leading_one_ull,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)__i); })
#elif defined(__CRT_HAVE___ffs)
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ui,(unsigned int __i),__ffs,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)__i); })
#elif defined(__CRT_HAVE_stdc_first_leading_one_ui)
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIDECLARE(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ui,(unsigned int __i),{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)__i); })
#else /* ... */
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__LOCAL unsigned int __NOTHROW_NCX(__LIBCCALL stdc_first_leading_one_ui)(unsigned int __i) { return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)__i); }
#endif /* !... */
#if __has_builtin(__builtin_ffsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffsl)
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ul,(unsigned long __i),ffsl,{ return __builtin_ffsl(__i); })
#elif defined(__CRT_HAVE_ffsl)
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ul,(unsigned long __i),ffsl,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)__i); })
#elif defined(__CRT_HAVE_ffs) && __SIZEOF_LONG__ == __SIZEOF_INT__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ul,(unsigned long __i),ffs,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)__i); })
#elif defined(__CRT_HAVE___ffs) && __SIZEOF_LONG__ == __SIZEOF_INT__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ul,(unsigned long __i),__ffs,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)__i); })
#elif defined(__CRT_HAVE_stdc_first_leading_one_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ul,(unsigned long __i),stdc_first_leading_one_ui,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)__i); })
#elif defined(__CRT_HAVE_ffsll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ul,(unsigned long __i),ffsll,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)__i); })
#elif defined(__CRT_HAVE_stdc_first_leading_one_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ul,(unsigned long __i),stdc_first_leading_one_ull,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)__i); })
#elif defined(__CRT_HAVE_stdc_first_leading_one_ul)
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIDECLARE(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ul,(unsigned long __i),{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)__i); })
#else /* ... */
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__LOCAL unsigned int __NOTHROW_NCX(__LIBCCALL stdc_first_leading_one_ul)(unsigned long __i) { return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)__i); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_leading_zero_uc
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_uc,(unsigned char __x),{ return __hybrid_ffs((unsigned char)~__x); })
#else /* __CRT_HAVE_stdc_first_leading_zero_uc */
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_leading_zero_uc)(unsigned char __x) { return __hybrid_ffs((unsigned char)~__x); }
#endif /* !__CRT_HAVE_stdc_first_leading_zero_uc */
#ifdef __CRT_HAVE_stdc_first_leading_zero_us
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_us,(unsigned short __x),{ return __hybrid_ffs((unsigned short)~__x); })
#else /* __CRT_HAVE_stdc_first_leading_zero_us */
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_leading_zero_us)(unsigned short __x) { return __hybrid_ffs((unsigned short)~__x); }
#endif /* !__CRT_HAVE_stdc_first_leading_zero_us */
#ifdef __CRT_HAVE_stdc_first_leading_zero_ui
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_ui,(unsigned int __x),{ return __hybrid_ffs((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_first_leading_zero_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_ui,(unsigned int __x),stdc_first_leading_zero_ul,{ return __hybrid_ffs((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_first_leading_zero_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_ui,(unsigned int __x),stdc_first_leading_zero_ull,{ return __hybrid_ffs((unsigned int)~__x); })
#else /* ... */
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_leading_zero_ui)(unsigned int __x) { return __hybrid_ffs((unsigned int)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_leading_zero_ul
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_ul,(unsigned long __x),{ return __hybrid_ffs((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_first_leading_zero_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_ul,(unsigned long __x),stdc_first_leading_zero_ui,{ return __hybrid_ffs((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_first_leading_zero_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_ul,(unsigned long __x),stdc_first_leading_zero_ull,{ return __hybrid_ffs((unsigned long)~__x); })
#else /* ... */
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_leading_zero_ul)(unsigned long __x) { return __hybrid_ffs((unsigned long)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_trailing_zero_uc
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_uc,(unsigned char __x),{ return __x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* __CRT_HAVE_stdc_first_trailing_zero_uc */
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_zero_uc)(unsigned char __x) { return __x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !__CRT_HAVE_stdc_first_trailing_zero_uc */
#ifdef __CRT_HAVE_stdc_first_trailing_zero_us
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_us,(unsigned short __x),{ return __x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* __CRT_HAVE_stdc_first_trailing_zero_us */
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_zero_us)(unsigned short __x) { return __x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !__CRT_HAVE_stdc_first_trailing_zero_us */
#ifdef __CRT_HAVE_stdc_first_trailing_zero_ui
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_ui,(unsigned int __x),{ return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_zero_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_ui,(unsigned int __x),stdc_first_trailing_zero_ul,{ return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_zero_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_ui,(unsigned int __x),stdc_first_trailing_zero_ull,{ return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* ... */
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_zero_ui)(unsigned int __x) { return __x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_trailing_zero_ul
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_ul,(unsigned long __x),{ return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_zero_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_ul,(unsigned long __x),stdc_first_trailing_zero_ui,{ return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_zero_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_ul,(unsigned long __x),stdc_first_trailing_zero_ull,{ return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* ... */
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_zero_ul)(unsigned long __x) { return __x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_trailing_one_uc
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_uc,(unsigned char __x),{ return __x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz((unsigned char)~__x); })
#else /* __CRT_HAVE_stdc_first_trailing_one_uc */
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_one_uc)(unsigned char __x) { return __x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz((unsigned char)~__x); }
#endif /* !__CRT_HAVE_stdc_first_trailing_one_uc */
#ifdef __CRT_HAVE_stdc_first_trailing_one_us
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_us,(unsigned short __x),{ return __x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned short)~__x); })
#else /* __CRT_HAVE_stdc_first_trailing_one_us */
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_one_us)(unsigned short __x) { return __x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned short)~__x); }
#endif /* !__CRT_HAVE_stdc_first_trailing_one_us */
#ifdef __CRT_HAVE_stdc_first_trailing_one_ui
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_ui,(unsigned int __x),{ return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_one_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_ui,(unsigned int __x),stdc_first_trailing_one_ul,{ return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_one_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_ui,(unsigned int __x),stdc_first_trailing_one_ull,{ return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~__x); })
#else /* ... */
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_one_ui)(unsigned int __x) { return __x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_trailing_one_ul
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_ul,(unsigned long __x),{ return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_one_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_ul,(unsigned long __x),stdc_first_trailing_one_ui,{ return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_one_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_ul,(unsigned long __x),stdc_first_trailing_one_ull,{ return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~__x); })
#else /* ... */
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_one_ul)(unsigned long __x) { return __x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_count_ones_uc
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_ones_uc,(unsigned char __x),{ return __hybrid_popcount(__x); })
#else /* __CRT_HAVE_stdc_count_ones_uc */
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_count_ones_uc)(unsigned char __x) { return __hybrid_popcount(__x); }
#endif /* !__CRT_HAVE_stdc_count_ones_uc */
#ifdef __CRT_HAVE_stdc_count_ones_us
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_ones_us,(unsigned short __x),{ return __hybrid_popcount(__x); })
#else /* __CRT_HAVE_stdc_count_ones_us */
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_count_ones_us)(unsigned short __x) { return __hybrid_popcount(__x); }
#endif /* !__CRT_HAVE_stdc_count_ones_us */
#if __has_builtin(__builtin_popcount) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcount)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ui,(unsigned int __i),popcount,{ return __builtin_popcount(__i); })
#elif defined(__CRT_HAVE_popcount)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ui,(unsigned int __i),popcount,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcount32) && __SIZEOF_INT__ == 4
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ui,(unsigned int __i),popcount32,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcount64) && __SIZEOF_INT__ == 8
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ui,(unsigned int __i),popcount64,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ui,(unsigned int __i),popcountl,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_stdc_count_ones_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ui,(unsigned int __i),stdc_count_ones_ul,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ui,(unsigned int __i),popcountll,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_stdc_count_ones_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ui,(unsigned int __i),stdc_count_ones_ull,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_stdc_count_ones_ui)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIDECLARE(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ui,(unsigned int __i),{ return __hybrid_popcount(__i); })
#else /* ... */
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__LOCAL unsigned int __NOTHROW_NCX(__LIBCCALL stdc_count_ones_ui)(unsigned int __i) { return __hybrid_popcount(__i); }
#endif /* !... */
#if __has_builtin(__builtin_popcountl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcountl)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ul,(unsigned long __i),popcountl,{ return __builtin_popcountl(__i); })
#elif defined(__CRT_HAVE_popcountl)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ul,(unsigned long __i),popcountl,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcount32) && __SIZEOF_LONG__ == 4
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ul,(unsigned long __i),popcount32,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcount64) && __SIZEOF_LONG__ == 8
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ul,(unsigned long __i),popcount64,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ul,(unsigned long __i),popcount,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_stdc_count_ones_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ul,(unsigned long __i),stdc_count_ones_ui,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ul,(unsigned long __i),popcountll,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_stdc_count_ones_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ul,(unsigned long __i),stdc_count_ones_ull,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_stdc_count_ones_ul)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIDECLARE(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ul,(unsigned long __i),{ return __hybrid_popcount(__i); })
#else /* ... */
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__LOCAL unsigned int __NOTHROW_NCX(__LIBCCALL stdc_count_ones_ul)(unsigned long __i) { return __hybrid_popcount(__i); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_count_zeros_uc
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_uc,(unsigned char __x),{ return __hybrid_popcount((unsigned char)~__x); })
#else /* __CRT_HAVE_stdc_count_zeros_uc */
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_count_zeros_uc)(unsigned char __x) { return __hybrid_popcount((unsigned char)~__x); }
#endif /* !__CRT_HAVE_stdc_count_zeros_uc */
#ifdef __CRT_HAVE_stdc_count_zeros_us
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_us,(unsigned short __x),{ return __hybrid_popcount((unsigned short)~__x); })
#else /* __CRT_HAVE_stdc_count_zeros_us */
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_count_zeros_us)(unsigned short __x) { return __hybrid_popcount((unsigned short)~__x); }
#endif /* !__CRT_HAVE_stdc_count_zeros_us */
#ifdef __CRT_HAVE_stdc_count_zeros_ui
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_ui,(unsigned int __x),{ return __hybrid_popcount((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_count_zeros_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_ui,(unsigned int __x),stdc_count_zeros_ul,{ return __hybrid_popcount((unsigned int)~__x); })
#elif defined(__CRT_HAVE_stdc_count_zeros_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_ui,(unsigned int __x),stdc_count_zeros_ull,{ return __hybrid_popcount((unsigned int)~__x); })
#else /* ... */
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_count_zeros_ui)(unsigned int __x) { return __hybrid_popcount((unsigned int)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_count_zeros_ul
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_ul,(unsigned long __x),{ return __hybrid_popcount((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_count_zeros_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_ul,(unsigned long __x),stdc_count_zeros_ui,{ return __hybrid_popcount((unsigned long)~__x); })
#elif defined(__CRT_HAVE_stdc_count_zeros_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_ul,(unsigned long __x),stdc_count_zeros_ull,{ return __hybrid_popcount((unsigned long)~__x); })
#else /* ... */
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_count_zeros_ul)(unsigned long __x) { return __hybrid_popcount((unsigned long)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_has_single_bit_uc
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_uc,(unsigned char __x),{ return (unsigned char)(__x ^ (__x - 1)) > (unsigned char)(__x - 1); })
#else /* __CRT_HAVE_stdc_has_single_bit_uc */
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(__LIBCCALL stdc_has_single_bit_uc)(unsigned char __x) { return (unsigned char)(__x ^ (__x - 1)) > (unsigned char)(__x - 1); }
#endif /* !__CRT_HAVE_stdc_has_single_bit_uc */
#ifdef __CRT_HAVE_stdc_has_single_bit_us
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_us,(unsigned short __x),{ return (unsigned short)(__x ^ (__x - 1)) > (unsigned short)(__x - 1); })
#else /* __CRT_HAVE_stdc_has_single_bit_us */
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(__LIBCCALL stdc_has_single_bit_us)(unsigned short __x) { return (unsigned short)(__x ^ (__x - 1)) > (unsigned short)(__x - 1); }
#endif /* !__CRT_HAVE_stdc_has_single_bit_us */
#ifdef __CRT_HAVE_stdc_has_single_bit_ui
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_ui,(unsigned int __x),{ return (unsigned int)(__x ^ (__x - 1)) > (unsigned int)(__x - 1); })
#elif defined(__CRT_HAVE_stdc_has_single_bit_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_ui,(unsigned int __x),stdc_has_single_bit_ul,{ return (unsigned int)(__x ^ (__x - 1)) > (unsigned int)(__x - 1); })
#elif defined(__CRT_HAVE_stdc_has_single_bit_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_ui,(unsigned int __x),stdc_has_single_bit_ull,{ return (unsigned int)(__x ^ (__x - 1)) > (unsigned int)(__x - 1); })
#else /* ... */
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(__LIBCCALL stdc_has_single_bit_ui)(unsigned int __x) { return (unsigned int)(__x ^ (__x - 1)) > (unsigned int)(__x - 1); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_has_single_bit_ul
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_ul,(unsigned long __x),{ return (unsigned long)(__x ^ (__x - 1)) > (unsigned long)(__x - 1); })
#elif defined(__CRT_HAVE_stdc_has_single_bit_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_ul,(unsigned long __x),stdc_has_single_bit_ui,{ return (unsigned long)(__x ^ (__x - 1)) > (unsigned long)(__x - 1); })
#elif defined(__CRT_HAVE_stdc_has_single_bit_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_ul,(unsigned long __x),stdc_has_single_bit_ull,{ return (unsigned long)(__x ^ (__x - 1)) > (unsigned long)(__x - 1); })
#else /* ... */
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(__LIBCCALL stdc_has_single_bit_ul)(unsigned long __x) { return (unsigned long)(__x ^ (__x - 1)) > (unsigned long)(__x - 1); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_bit_width_uc
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_uc,(unsigned char __x),{ return __x == 0 ? 0 : (__SIZEOF_CHAR__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#else /* __CRT_HAVE_stdc_bit_width_uc */
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_bit_width_uc)(unsigned char __x) { return __x == 0 ? 0 : (__SIZEOF_CHAR__ * __CHAR_BIT__) - __hybrid_clz(__x); }
#endif /* !__CRT_HAVE_stdc_bit_width_uc */
#ifdef __CRT_HAVE_stdc_bit_width_us
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_us,(unsigned short __x),{ return __x == 0 ? 0 : (__SIZEOF_SHORT__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#else /* __CRT_HAVE_stdc_bit_width_us */
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_bit_width_us)(unsigned short __x) { return __x == 0 ? 0 : (__SIZEOF_SHORT__ * __CHAR_BIT__) - __hybrid_clz(__x); }
#endif /* !__CRT_HAVE_stdc_bit_width_us */
#ifdef __CRT_HAVE_stdc_bit_width_ui
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_ui,(unsigned int __x),{ return __x == 0 ? 0 : (__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_bit_width_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_ui,(unsigned int __x),stdc_bit_width_ul,{ return __x == 0 ? 0 : (__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_bit_width_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_ui,(unsigned int __x),stdc_bit_width_ull,{ return __x == 0 ? 0 : (__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#else /* ... */
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_bit_width_ui)(unsigned int __x) { return __x == 0 ? 0 : (__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_bit_width_ul
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_ul,(unsigned long __x),{ return __x == 0 ? 0 : (__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_bit_width_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_ul,(unsigned long __x),stdc_bit_width_ui,{ return __x == 0 ? 0 : (__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_bit_width_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_ul,(unsigned long __x),stdc_bit_width_ull,{ return __x == 0 ? 0 : (__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#else /* ... */
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_bit_width_ul)(unsigned long __x) { return __x == 0 ? 0 : (__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_bit_floor_uc
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned char,__NOTHROW,stdc_bit_floor_uc,(unsigned char __x),{ return __x == 0 ? 0 : ((unsigned char)1 << (((__SIZEOF_CHAR__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#else /* __CRT_HAVE_stdc_bit_floor_uc */
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned char __NOTHROW(__LIBCCALL stdc_bit_floor_uc)(unsigned char __x) { return __x == 0 ? 0 : ((unsigned char)1 << (((__SIZEOF_CHAR__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); }
#endif /* !__CRT_HAVE_stdc_bit_floor_uc */
#ifdef __CRT_HAVE_stdc_bit_floor_us
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned short,__NOTHROW,stdc_bit_floor_us,(unsigned short __x),{ return __x == 0 ? 0 : ((unsigned short)1 << (((__SIZEOF_SHORT__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#else /* __CRT_HAVE_stdc_bit_floor_us */
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned short __NOTHROW(__LIBCCALL stdc_bit_floor_us)(unsigned short __x) { return __x == 0 ? 0 : ((unsigned short)1 << (((__SIZEOF_SHORT__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); }
#endif /* !__CRT_HAVE_stdc_bit_floor_us */
#ifdef __CRT_HAVE_stdc_bit_floor_ui
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_floor_ui,(unsigned int __x),{ return __x == 0 ? 0 : ((unsigned int)1 << (((__SIZEOF_INT__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#elif defined(__CRT_HAVE_stdc_bit_floor_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_floor_ui,(unsigned int __x),stdc_bit_floor_ul,{ return __x == 0 ? 0 : ((unsigned int)1 << (((__SIZEOF_INT__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#elif defined(__CRT_HAVE_stdc_bit_floor_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_floor_ui,(unsigned int __x),stdc_bit_floor_ull,{ return __x == 0 ? 0 : ((unsigned int)1 << (((__SIZEOF_INT__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#else /* ... */
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_bit_floor_ui)(unsigned int __x) { return __x == 0 ? 0 : ((unsigned int)1 << (((__SIZEOF_INT__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_bit_floor_ul
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned long,__NOTHROW,stdc_bit_floor_ul,(unsigned long __x),{ return __x == 0 ? 0 : ((unsigned long)1 << (((__SIZEOF_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#elif defined(__CRT_HAVE_stdc_bit_floor_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned long,__NOTHROW,stdc_bit_floor_ul,(unsigned long __x),stdc_bit_floor_ui,{ return __x == 0 ? 0 : ((unsigned long)1 << (((__SIZEOF_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#elif defined(__CRT_HAVE_stdc_bit_floor_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned long,__NOTHROW,stdc_bit_floor_ul,(unsigned long __x),stdc_bit_floor_ull,{ return __x == 0 ? 0 : ((unsigned long)1 << (((__SIZEOF_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#else /* ... */
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned long __NOTHROW(__LIBCCALL stdc_bit_floor_ul)(unsigned long __x) { return __x == 0 ? 0 : ((unsigned long)1 << (((__SIZEOF_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_bit_ceil_uc
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned char,__NOTHROW,stdc_bit_ceil_uc,(unsigned char __x),{ return __x <= 1 ? 1 : ((unsigned char)1 << ((__SIZEOF_CHAR__ * __CHAR_BIT__) - __hybrid_clz((unsigned char)(__x - 1)))); })
#else /* __CRT_HAVE_stdc_bit_ceil_uc */
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned char __NOTHROW(__LIBCCALL stdc_bit_ceil_uc)(unsigned char __x) { return __x <= 1 ? 1 : ((unsigned char)1 << ((__SIZEOF_CHAR__ * __CHAR_BIT__) - __hybrid_clz((unsigned char)(__x - 1)))); }
#endif /* !__CRT_HAVE_stdc_bit_ceil_uc */
#ifdef __CRT_HAVE_stdc_bit_ceil_us
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned short,__NOTHROW,stdc_bit_ceil_us,(unsigned short __x),{ return __x <= 1 ? 1 : ((unsigned short)1 << ((__SIZEOF_SHORT__ * __CHAR_BIT__) - __hybrid_clz((unsigned short)(__x - 1)))); })
#else /* __CRT_HAVE_stdc_bit_ceil_us */
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned short __NOTHROW(__LIBCCALL stdc_bit_ceil_us)(unsigned short __x) { return __x <= 1 ? 1 : ((unsigned short)1 << ((__SIZEOF_SHORT__ * __CHAR_BIT__) - __hybrid_clz((unsigned short)(__x - 1)))); }
#endif /* !__CRT_HAVE_stdc_bit_ceil_us */
#ifdef __CRT_HAVE_stdc_bit_ceil_ui
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_ceil_ui,(unsigned int __x),{ return __x <= 1 ? 1 : ((unsigned int)1 << ((__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz((unsigned int)(__x - 1)))); })
#elif defined(__CRT_HAVE_stdc_bit_ceil_ul) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_ceil_ui,(unsigned int __x),stdc_bit_ceil_ul,{ return __x <= 1 ? 1 : ((unsigned int)1 << ((__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz((unsigned int)(__x - 1)))); })
#elif defined(__CRT_HAVE_stdc_bit_ceil_ull) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_ceil_ui,(unsigned int __x),stdc_bit_ceil_ull,{ return __x <= 1 ? 1 : ((unsigned int)1 << ((__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz((unsigned int)(__x - 1)))); })
#else /* ... */
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_bit_ceil_ui)(unsigned int __x) { return __x <= 1 ? 1 : ((unsigned int)1 << ((__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz((unsigned int)(__x - 1)))); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_bit_ceil_ul
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned long,__NOTHROW,stdc_bit_ceil_ul,(unsigned long __x),{ return __x <= 1 ? 1 : ((unsigned long)1 << ((__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz((unsigned long)(__x - 1)))); })
#elif defined(__CRT_HAVE_stdc_bit_ceil_ui) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned long,__NOTHROW,stdc_bit_ceil_ul,(unsigned long __x),stdc_bit_ceil_ui,{ return __x <= 1 ? 1 : ((unsigned long)1 << ((__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz((unsigned long)(__x - 1)))); })
#elif defined(__CRT_HAVE_stdc_bit_ceil_ull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned long,__NOTHROW,stdc_bit_ceil_ul,(unsigned long __x),stdc_bit_ceil_ull,{ return __x <= 1 ? 1 : ((unsigned long)1 << ((__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz((unsigned long)(__x - 1)))); })
#else /* ... */
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned long __NOTHROW(__LIBCCALL stdc_bit_ceil_ul)(unsigned long __x) { return __x <= 1 ? 1 : ((unsigned long)1 << ((__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz((unsigned long)(__x - 1)))); }
#endif /* !... */


#ifdef __COMPILER_HAVE_LONGLONG
#ifdef __CRT_HAVE_stdc_leading_zeros_ull
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_ull,(__ULONGLONG __x),{ return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_leading_zeros_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_ull,(__ULONGLONG __x),stdc_leading_zeros_ui,{ return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_leading_zeros_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_zeros_ull,(__ULONGLONG __x),stdc_leading_zeros_ul,{ return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz(__x); })
#else /* ... */
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_zeros_ull)(__ULONGLONG __x) { return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_leading_ones_ull
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_ull,(__ULONGLONG __x),{ return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_leading_ones_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_ull,(__ULONGLONG __x),stdc_leading_ones_ui,{ return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_leading_ones_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_leading_ones_ull,(__ULONGLONG __x),stdc_leading_ones_ul,{ return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz((__ULONGLONG)~__x); })
#else /* ... */
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_leading_ones_ull)(__ULONGLONG __x) { return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz((__ULONGLONG)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_trailing_zeros_ull
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_ull,(__ULONGLONG __x),{ return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_trailing_zeros_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_ull,(__ULONGLONG __x),stdc_trailing_zeros_ui,{ return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_trailing_zeros_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_zeros_ull,(__ULONGLONG __x),stdc_trailing_zeros_ul,{ return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* ... */
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_zeros_ull)(__ULONGLONG __x) { return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_trailing_ones_ull
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_ull,(__ULONGLONG __x),{ return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_trailing_ones_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_ull,(__ULONGLONG __x),stdc_trailing_ones_ui,{ return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_trailing_ones_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_trailing_ones_ull,(__ULONGLONG __x),stdc_trailing_ones_ul,{ return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~__x); })
#else /* ... */
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_trailing_ones_ull)(__ULONGLONG __x) { return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~__x); }
#endif /* !... */
#if __has_builtin(__builtin_ffsll) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffsll)
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ull,(__ULONGLONG __i),ffsll,{ return __builtin_ffsll(__i); })
#elif defined(__CRT_HAVE_ffsll)
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ull,(__ULONGLONG __i),ffsll,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)__i); })
#elif defined(__CRT_HAVE_ffs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ull,(__ULONGLONG __i),ffs,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)__i); })
#elif defined(__CRT_HAVE___ffs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ull,(__ULONGLONG __i),__ffs,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)__i); })
#elif defined(__CRT_HAVE_stdc_first_leading_one_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ull,(__ULONGLONG __i),stdc_first_leading_one_ui,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)__i); })
#elif defined(__CRT_HAVE_ffsl) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ull,(__ULONGLONG __i),ffsl,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)__i); })
#elif defined(__CRT_HAVE_stdc_first_leading_one_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ull,(__ULONGLONG __i),stdc_first_leading_one_ul,{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)__i); })
#elif defined(__CRT_HAVE_stdc_first_leading_one_ull)
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__CEIDECLARE(,unsigned int,__NOTHROW_NCX,stdc_first_leading_one_ull,(__ULONGLONG __i),{ return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)__i); })
#else /* ... */
#include <features.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
__LOCAL unsigned int __NOTHROW_NCX(__LIBCCALL stdc_first_leading_one_ull)(__ULONGLONG __i) { return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)__i); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_leading_zero_ull
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_ull,(__ULONGLONG __x),{ return __hybrid_ffs((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_first_leading_zero_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_ull,(__ULONGLONG __x),stdc_first_leading_zero_ui,{ return __hybrid_ffs((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_first_leading_zero_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_leading_zero_ull,(__ULONGLONG __x),stdc_first_leading_zero_ul,{ return __hybrid_ffs((__ULONGLONG)~__x); })
#else /* ... */
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_leading_zero_ull)(__ULONGLONG __x) { return __hybrid_ffs((__ULONGLONG)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_trailing_zero_ull
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_ull,(__ULONGLONG __x),{ return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_zero_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_ull,(__ULONGLONG __x),stdc_first_trailing_zero_ui,{ return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_zero_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_zero_ull,(__ULONGLONG __x),stdc_first_trailing_zero_ul,{ return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); })
#else /* ... */
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_zero_ull)(__ULONGLONG __x) { return __x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_first_trailing_one_ull
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_ull,(__ULONGLONG __x),{ return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_one_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_ull,(__ULONGLONG __x),stdc_first_trailing_one_ui,{ return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_first_trailing_one_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_first_trailing_one_ull,(__ULONGLONG __x),stdc_first_trailing_one_ul,{ return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~__x); })
#else /* ... */
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_first_trailing_one_ull)(__ULONGLONG __x) { return __x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~__x); }
#endif /* !... */
#if __has_builtin(__builtin_popcountll) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcountll)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ull,(__ULONGLONG __i),popcountll,{ return __builtin_popcountll(__i); })
#elif defined(__CRT_HAVE_popcountll)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ull,(__ULONGLONG __i),popcountll,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcount32) && __SIZEOF_LONG_LONG__ == 4
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ull,(__ULONGLONG __i),popcount32,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcount64) && __SIZEOF_LONG_LONG__ == 8
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ull,(__ULONGLONG __i),popcount64,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ull,(__ULONGLONG __i),popcount,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_stdc_count_ones_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ull,(__ULONGLONG __i),stdc_count_ones_ui,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ull,(__ULONGLONG __i),popcountl,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_stdc_count_ones_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIREDIRECT(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ull,(__ULONGLONG __i),stdc_count_ones_ul,{ return __hybrid_popcount(__i); })
#elif defined(__CRT_HAVE_stdc_count_ones_ull)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__CEIDECLARE(,unsigned int,__NOTHROW_NCX,stdc_count_ones_ull,(__ULONGLONG __i),{ return __hybrid_popcount(__i); })
#else /* ... */
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
__LOCAL unsigned int __NOTHROW_NCX(__LIBCCALL stdc_count_ones_ull)(__ULONGLONG __i) { return __hybrid_popcount(__i); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_count_zeros_ull
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_ull,(__ULONGLONG __x),{ return __hybrid_popcount((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_count_zeros_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_ull,(__ULONGLONG __x),stdc_count_zeros_ui,{ return __hybrid_popcount((__ULONGLONG)~__x); })
#elif defined(__CRT_HAVE_stdc_count_zeros_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_count_zeros_ull,(__ULONGLONG __x),stdc_count_zeros_ul,{ return __hybrid_popcount((__ULONGLONG)~__x); })
#else /* ... */
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_count_zeros_ull)(__ULONGLONG __x) { return __hybrid_popcount((__ULONGLONG)~__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_has_single_bit_ull
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_ull,(__ULONGLONG __x),{ return (__ULONGLONG)(__x ^ (__x - 1)) > (__ULONGLONG)(__x - 1); })
#elif defined(__CRT_HAVE_stdc_has_single_bit_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_ull,(__ULONGLONG __x),stdc_has_single_bit_ui,{ return (__ULONGLONG)(__x ^ (__x - 1)) > (__ULONGLONG)(__x - 1); })
#elif defined(__CRT_HAVE_stdc_has_single_bit_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__BOOL,__NOTHROW,stdc_has_single_bit_ull,(__ULONGLONG __x),stdc_has_single_bit_ul,{ return (__ULONGLONG)(__x ^ (__x - 1)) > (__ULONGLONG)(__x - 1); })
#else /* ... */
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(__LIBCCALL stdc_has_single_bit_ull)(__ULONGLONG __x) { return (__ULONGLONG)(__x ^ (__x - 1)) > (__ULONGLONG)(__x - 1); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_bit_width_ull
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_ull,(__ULONGLONG __x),{ return __x == 0 ? 0 : (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_bit_width_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_ull,(__ULONGLONG __x),stdc_bit_width_ui,{ return __x == 0 ? 0 : (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#elif defined(__CRT_HAVE_stdc_bit_width_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,stdc_bit_width_ull,(__ULONGLONG __x),stdc_bit_width_ul,{ return __x == 0 ? 0 : (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz(__x); })
#else /* ... */
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL stdc_bit_width_ull)(__ULONGLONG __x) { return __x == 0 ? 0 : (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz(__x); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_bit_floor_ull
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__ULONGLONG,__NOTHROW,stdc_bit_floor_ull,(__ULONGLONG __x),{ return __x == 0 ? 0 : ((__ULONGLONG)1 << (((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#elif defined(__CRT_HAVE_stdc_bit_floor_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__ULONGLONG,__NOTHROW,stdc_bit_floor_ull,(__ULONGLONG __x),stdc_bit_floor_ui,{ return __x == 0 ? 0 : ((__ULONGLONG)1 << (((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#elif defined(__CRT_HAVE_stdc_bit_floor_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__ULONGLONG,__NOTHROW,stdc_bit_floor_ull,(__ULONGLONG __x),stdc_bit_floor_ul,{ return __x == 0 ? 0 : ((__ULONGLONG)1 << (((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); })
#else /* ... */
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __ULONGLONG __NOTHROW(__LIBCCALL stdc_bit_floor_ull)(__ULONGLONG __x) { return __x == 0 ? 0 : ((__ULONGLONG)1 << (((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(__x))); }
#endif /* !... */
#ifdef __CRT_HAVE_stdc_bit_ceil_ull
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__ULONGLONG,__NOTHROW,stdc_bit_ceil_ull,(__ULONGLONG __x),{ return __x <= 1 ? 1 : ((__ULONGLONG)1 << ((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz((__ULONGLONG)(__x - 1)))); })
#elif defined(__CRT_HAVE_stdc_bit_ceil_ui) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__ULONGLONG,__NOTHROW,stdc_bit_ceil_ull,(__ULONGLONG __x),stdc_bit_ceil_ui,{ return __x <= 1 ? 1 : ((__ULONGLONG)1 << ((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz((__ULONGLONG)(__x - 1)))); })
#elif defined(__CRT_HAVE_stdc_bit_ceil_ul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__ULONGLONG,__NOTHROW,stdc_bit_ceil_ull,(__ULONGLONG __x),stdc_bit_ceil_ul,{ return __x <= 1 ? 1 : ((__ULONGLONG)1 << ((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz((__ULONGLONG)(__x - 1)))); })
#else /* ... */
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __ULONGLONG __NOTHROW(__LIBCCALL stdc_bit_ceil_ull)(__ULONGLONG __x) { return __x <= 1 ? 1 : ((__ULONGLONG)1 << ((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz((__ULONGLONG)(__x - 1)))); }
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGLONG */



/* Type-generic implementations */

#ifndef __PRIVATE_STDC_BIT_RECAST
#ifdef __COMPILER_HAVE_TYPEOF
#define __PRIVATE_STDC_BIT_RECAST(x, v) ((__typeof__(x))(v))
#elif defined(__COMPILER_HAVE_C11_GENERIC) && defined(__COMPILER_HAVE_LONGLONG)
#define __PRIVATE_STDC_BIT_RECAST(x, v) _Generic((x), unsigned char: (unsigned char)(v), unsigned short: (unsigned short)(v), unsigned int: (unsigned int)(v), unsigned long: (unsigned long)(v), __ULONGLONG: (__ULONGLONG)(v)default: v)
#elif defined(__COMPILER_HAVE_C11_GENERIC)
#define __PRIVATE_STDC_BIT_RECAST(x, v) _Generic((x), unsigned char: (unsigned char)(v), unsigned short: (unsigned short)(v), unsigned int: (unsigned int)(v), unsigned long: (unsigned long)(v), default: v)
#else /* ... */
#define __PRIVATE_STDC_BIT_RECAST(x, v) v
#endif /* !... */
#endif /* __PRIVATE_STDC_BIT_RECAST */

/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
#if __has_builtin(__builtin_stdc_leading_zeros)
#define stdc_leading_zeros(x) __builtin_stdc_leading_zeros(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_leading_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_leading_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_leading_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_leading_zeros_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_leading_zeros_ul((unsigned long)(x)),  \
	                                                  stdc_leading_zeros_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_leading_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_leading_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_leading_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_leading_zeros_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_leading_zeros_ul((unsigned long)(x))  : \
	                            : stdc_leading_zeros_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_leading_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_leading_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_leading_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_leading_zeros_ui((unsigned int)(x)),   \
	                                                  stdc_leading_zeros_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_leading_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_leading_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_leading_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_leading_zeros_ui((unsigned int)(x))   : \
	                            : stdc_leading_zeros_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
#if __has_builtin(__builtin_stdc_leading_ones)
#define stdc_leading_ones(x) __builtin_stdc_leading_ones(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_leading_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_leading_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_leading_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_leading_ones_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_leading_ones_ul((unsigned long)(x)),  \
	                                                  stdc_leading_ones_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_leading_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_leading_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_leading_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_leading_ones_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_leading_ones_ul((unsigned long)(x))  : \
	                            : stdc_leading_ones_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_leading_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_leading_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_leading_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_leading_ones_ui((unsigned int)(x)),   \
	                                                  stdc_leading_ones_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_leading_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_leading_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_leading_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_leading_ones_ui((unsigned int)(x))   : \
	                            : stdc_leading_ones_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
#if __has_builtin(__builtin_stdc_trailing_zeros)
#define stdc_trailing_zeros(x) __builtin_stdc_trailing_zeros(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_trailing_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_trailing_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_trailing_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_trailing_zeros_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_trailing_zeros_ul((unsigned long)(x)),  \
	                                                  stdc_trailing_zeros_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_trailing_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_trailing_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_trailing_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_trailing_zeros_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_trailing_zeros_ul((unsigned long)(x))  : \
	                            : stdc_trailing_zeros_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_trailing_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_trailing_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_trailing_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_trailing_zeros_ui((unsigned int)(x)),   \
	                                                  stdc_trailing_zeros_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_trailing_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_trailing_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_trailing_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_trailing_zeros_ui((unsigned int)(x))   : \
	                            : stdc_trailing_zeros_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
#if __has_builtin(__builtin_stdc_trailing_ones)
#define stdc_trailing_ones(x) __builtin_stdc_trailing_ones(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_trailing_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_trailing_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_trailing_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_trailing_ones_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_trailing_ones_ul((unsigned long)(x)),  \
	                                                  stdc_trailing_ones_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_trailing_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_trailing_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_trailing_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_trailing_ones_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_trailing_ones_ul((unsigned long)(x))  : \
	                            : stdc_trailing_ones_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_trailing_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_trailing_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_trailing_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_trailing_ones_ui((unsigned int)(x)),   \
	                                                  stdc_trailing_ones_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_trailing_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_trailing_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_trailing_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_trailing_ones_ui((unsigned int)(x))   : \
	                            : stdc_trailing_ones_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
#if __has_builtin(__builtin_stdc_first_leading_one)
#define stdc_first_leading_one(x) __builtin_stdc_first_leading_one(x)
#elif !defined(__OPTIMIZE_SIZE__)
#define stdc_first_leading_one(x) __hybrid_ffs(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_first_leading_one(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_leading_one_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_leading_one_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_leading_one_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_first_leading_one_ul((unsigned long)(x)),  \
	                                                  stdc_first_leading_one_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_first_leading_one(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_leading_one_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_leading_one_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_leading_one_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_first_leading_one_ul((unsigned long)(x))  : \
	                            : stdc_first_leading_one_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_first_leading_one(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_leading_one_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_leading_one_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_leading_one_ui((unsigned int)(x)),   \
	                                                  stdc_first_leading_one_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_first_leading_one(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_leading_one_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_leading_one_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_leading_one_ui((unsigned int)(x))   : \
	                            : stdc_first_leading_one_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
#if __has_builtin(__builtin_stdc_first_leading_zero)
#define stdc_first_leading_zero(x) __builtin_stdc_first_leading_zero(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_first_leading_zero(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_leading_zero_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_leading_zero_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_leading_zero_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_first_leading_zero_ul((unsigned long)(x)),  \
	                                                  stdc_first_leading_zero_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_first_leading_zero(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_leading_zero_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_leading_zero_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_leading_zero_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_first_leading_zero_ul((unsigned long)(x))  : \
	                            : stdc_first_leading_zero_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_first_leading_zero(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_leading_zero_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_leading_zero_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_leading_zero_ui((unsigned int)(x)),   \
	                                                  stdc_first_leading_zero_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_first_leading_zero(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_leading_zero_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_leading_zero_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_leading_zero_ui((unsigned int)(x))   : \
	                            : stdc_first_leading_zero_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
#if __has_builtin(__builtin_stdc_first_trailing_zero)
#define stdc_first_trailing_zero(x) __builtin_stdc_first_trailing_zero(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_first_trailing_zero(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_trailing_zero_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_trailing_zero_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_trailing_zero_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_first_trailing_zero_ul((unsigned long)(x)),  \
	                                                  stdc_first_trailing_zero_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_first_trailing_zero(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_trailing_zero_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_trailing_zero_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_trailing_zero_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_first_trailing_zero_ul((unsigned long)(x))  : \
	                            : stdc_first_trailing_zero_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_first_trailing_zero(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_trailing_zero_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_trailing_zero_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_trailing_zero_ui((unsigned int)(x)),   \
	                                                  stdc_first_trailing_zero_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_first_trailing_zero(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_trailing_zero_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_trailing_zero_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_trailing_zero_ui((unsigned int)(x))   : \
	                            : stdc_first_trailing_zero_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
#if __has_builtin(__builtin_stdc_first_trailing_one)
#define stdc_first_trailing_one(x) __builtin_stdc_first_trailing_one(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_first_trailing_one(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_trailing_one_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_trailing_one_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_trailing_one_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_first_trailing_one_ul((unsigned long)(x)),  \
	                                                  stdc_first_trailing_one_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_first_trailing_one(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_trailing_one_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_trailing_one_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_trailing_one_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_first_trailing_one_ul((unsigned long)(x))  : \
	                            : stdc_first_trailing_one_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_first_trailing_one(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_first_trailing_one_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_first_trailing_one_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_first_trailing_one_ui((unsigned int)(x)),   \
	                                                  stdc_first_trailing_one_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_first_trailing_one(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_first_trailing_one_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_first_trailing_one_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_first_trailing_one_ui((unsigned int)(x))   : \
	                            : stdc_first_trailing_one_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
#if __has_builtin(__builtin_stdc_count_ones)
#define stdc_count_ones(x) __builtin_stdc_count_ones(x)
#elif !defined(__OPTIMIZE_SIZE__)
#define stdc_count_ones(x) __hybrid_popcount(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_count_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_count_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_count_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_count_ones_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_count_ones_ul((unsigned long)(x)),  \
	                                                  stdc_count_ones_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_count_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_count_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_count_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_count_ones_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_count_ones_ul((unsigned long)(x))  : \
	                            : stdc_count_ones_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_count_ones(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_count_ones_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_count_ones_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_count_ones_ui((unsigned int)(x)),   \
	                                                  stdc_count_ones_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_count_ones(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_count_ones_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_count_ones_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_count_ones_ui((unsigned int)(x))   : \
	                            : stdc_count_ones_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
#if __has_builtin(__builtin_stdc_count_zeros)
#define stdc_count_zeros(x) __builtin_stdc_count_zeros(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_count_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_count_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_count_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_count_zeros_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_count_zeros_ul((unsigned long)(x)),  \
	                                                  stdc_count_zeros_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_count_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_count_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_count_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_count_zeros_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_count_zeros_ul((unsigned long)(x))  : \
	                            : stdc_count_zeros_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_count_zeros(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_count_zeros_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_count_zeros_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_count_zeros_ui((unsigned int)(x)),   \
	                                                  stdc_count_zeros_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_count_zeros(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_count_zeros_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_count_zeros_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_count_zeros_ui((unsigned int)(x))   : \
	                            : stdc_count_zeros_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
#if __has_builtin(__builtin_stdc_has_single_bit)
#define stdc_has_single_bit(x) __builtin_stdc_has_single_bit(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_has_single_bit(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_has_single_bit_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_has_single_bit_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_has_single_bit_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_has_single_bit_ul((unsigned long)(x)),  \
	                                                  stdc_has_single_bit_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_has_single_bit(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_has_single_bit_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_has_single_bit_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_has_single_bit_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_has_single_bit_ul((unsigned long)(x))  : \
	                            : stdc_has_single_bit_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_has_single_bit(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_has_single_bit_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_has_single_bit_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_has_single_bit_ui((unsigned int)(x)),   \
	                                                  stdc_has_single_bit_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_has_single_bit(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_has_single_bit_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_has_single_bit_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_has_single_bit_ui((unsigned int)(x))   : \
	                            : stdc_has_single_bit_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
#if __has_builtin(__builtin_stdc_bit_width)
#define stdc_bit_width(x) __builtin_stdc_bit_width(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_bit_width(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_width_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_width_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_width_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_bit_width_ul((unsigned long)(x)),  \
	                                                  stdc_bit_width_ull((__ULONGLONG)(x))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_bit_width(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_width_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_width_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_width_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_bit_width_ul((unsigned long)(x))  : \
	                            : stdc_bit_width_ull((__ULONGLONG)(x)))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_bit_width(x) \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_width_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_width_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_width_ui((unsigned int)(x)),   \
	                                                  stdc_bit_width_ul((unsigned long)(x)))))
#else /* ... */
#define stdc_bit_width(x) \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_width_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_width_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_width_ui((unsigned int)(x))   : \
	                            : stdc_bit_width_ul((unsigned long)(x)))
#endif /* !... */


/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
#if __has_builtin(__builtin_stdc_bit_floor)
#define stdc_bit_floor(x) __builtin_stdc_bit_floor(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_bit_floor(x) __PRIVATE_STDC_BIT_RECAST(x, \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_floor_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_floor_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_floor_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_bit_floor_ul((unsigned long)(x)),  \
	                                                  stdc_bit_floor_ull((__ULONGLONG)(x)))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_bit_floor(x) __PRIVATE_STDC_BIT_RECAST(x, \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_floor_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_floor_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_floor_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_bit_floor_ul((unsigned long)(x))  : \
	                            : stdc_bit_floor_ull((__ULONGLONG)(x))))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_bit_floor(x) __PRIVATE_STDC_BIT_RECAST(x, \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_floor_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_floor_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_floor_ui((unsigned int)(x)),   \
	                                                  stdc_bit_floor_ul((unsigned long)(x))))))
#else /* ... */
#define stdc_bit_floor(x) __PRIVATE_STDC_BIT_RECAST(x, \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_floor_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_floor_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_floor_ui((unsigned int)(x))   : \
	                            : stdc_bit_floor_ul((unsigned long)(x))))
#endif /* !... */


/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
#if __has_builtin(__builtin_stdc_bit_ceil)
#define stdc_bit_ceil(x) __builtin_stdc_bit_ceil(x)
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__ && !defined(__NO_builtin_choose_expr)
#define stdc_bit_ceil(x) __PRIVATE_STDC_BIT_RECAST(x, \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_ceil_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_ceil_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_ceil_ui((unsigned int)(x)),   \
	__builtin_choose_expr(sizeof(x) <= sizeof(long),  stdc_bit_ceil_ul((unsigned long)(x)),  \
	                                                  stdc_bit_ceil_ull((__ULONGLONG)(x)))))))
#elif defined(__COMPILER_HAVE_LONGLONG) && __SIZEOF_LONG_LONG__ > __SIZEOF_LONG__
#define stdc_bit_ceil(x) __PRIVATE_STDC_BIT_RECAST(x, \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_ceil_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_ceil_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_ceil_ui((unsigned int)(x))   : \
	 sizeof(x) <= sizeof(long)  ? stdc_bit_ceil_ul((unsigned long)(x))  : \
	                            : stdc_bit_ceil_ull((__ULONGLONG)(x))))
#elif !defined(__NO_builtin_choose_expr)
#define stdc_bit_ceil(x) __PRIVATE_STDC_BIT_RECAST(x, \
	__builtin_choose_expr(sizeof(x) <= sizeof(char),  stdc_bit_ceil_uc((unsigned char)(x)),  \
	__builtin_choose_expr(sizeof(x) <= sizeof(short), stdc_bit_ceil_us((unsigned short)(x)), \
	__builtin_choose_expr(sizeof(x) <= sizeof(int),   stdc_bit_ceil_ui((unsigned int)(x)),   \
	                                                  stdc_bit_ceil_ul((unsigned long)(x))))))
#else /* ... */
#define stdc_bit_ceil(x) __PRIVATE_STDC_BIT_RECAST(x, \
	(sizeof(x) <= sizeof(char)  ? stdc_bit_ceil_uc((unsigned char)(x))  : \
	 sizeof(x) <= sizeof(short) ? stdc_bit_ceil_us((unsigned short)(x)) : \
	 sizeof(x) <= sizeof(int)   ? stdc_bit_ceil_ui((unsigned int)(x))   : \
	                            : stdc_bit_ceil_ul((unsigned long)(x))))
#endif /* !... */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_STDBIT_H */
