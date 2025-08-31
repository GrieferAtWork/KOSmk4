/* HASH CRC-32:0x36a94eb5 */
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
#ifndef GUARD_LIBC_AUTO_STDBIT_C
#define GUARD_LIBC_AUTO_STDBIT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "stdbit.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_zeros_uc)(unsigned char x) {
	return x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_clz(x);
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_zeros_us)(unsigned short x) {
	return x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_clz(x);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_leading_zeros_ui,libc_stdc_leading_zeros_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_leading_zeros_ui,libc_stdc_leading_zeros_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
#include <hybrid/__bit.h>
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_zeros_ui)(unsigned int x) {
	return x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz(x);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_leading_zeros_ul,libc_stdc_leading_zeros_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_zeros_ul)(unsigned long x) {
	return x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz(x);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_ones_uc)(unsigned char x) {
	return x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_clz((unsigned char)~x);
}
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_ones_us)(unsigned short x) {
	return x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_clz((unsigned short)~x);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_leading_ones_ui,libc_stdc_leading_ones_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_leading_ones_ui,libc_stdc_leading_ones_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_ones_ui)(unsigned int x) {
	return x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_clz((unsigned int)~x);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_leading_ones_ul,libc_stdc_leading_ones_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_ones_ul)(unsigned long x) {
	return x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_clz((unsigned long)~x);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_zeros_uc)(unsigned char x) {
	return x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_zeros_us)(unsigned short x) {
	return x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_trailing_zeros_ui,libc_stdc_trailing_zeros_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_trailing_zeros_ui,libc_stdc_trailing_zeros_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
#include <hybrid/__bit.h>
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_zeros_ui)(unsigned int x) {
	return x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_trailing_zeros_ul,libc_stdc_trailing_zeros_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_zeros_ul)(unsigned long x) {
	return x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_ones_uc)(unsigned char x) {
	return x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz((unsigned char)~x);
}
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_ones_us)(unsigned short x) {
	return x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned short)~x);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_trailing_ones_ui,libc_stdc_trailing_ones_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_trailing_ones_ui,libc_stdc_trailing_ones_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_ones_ui)(unsigned int x) {
	return x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~x);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_trailing_ones_ul,libc_stdc_trailing_ones_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_ones_ul)(unsigned long x) {
	return x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~x);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_leading_one_uc)(unsigned char x) {
	return __hybrid_ffs(x);
}
#include <hybrid/__bit.h>
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_leading_one_us)(unsigned short x) {
	return __hybrid_ffs(x);
}
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_leading_zero_uc)(unsigned char x) {
	return __hybrid_ffs((unsigned char)~x);
}
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_leading_zero_us)(unsigned short x) {
	return __hybrid_ffs((unsigned short)~x);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_first_leading_zero_ui,libc_stdc_first_leading_zero_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_first_leading_zero_ui,libc_stdc_first_leading_zero_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_leading_zero_ui)(unsigned int x) {
	return __hybrid_ffs((unsigned int)~x);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_first_leading_zero_ul,libc_stdc_first_leading_zero_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_leading_zero_ul)(unsigned long x) {
	return __hybrid_ffs((unsigned long)~x);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_uc)(unsigned char x) {
	return x == 0 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_us)(unsigned short x) {
	return x == 0 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_first_trailing_zero_ui,libc_stdc_first_trailing_zero_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_first_trailing_zero_ui,libc_stdc_first_trailing_zero_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
#include <hybrid/__bit.h>
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_ui)(unsigned int x) {
	return x == 0 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_first_trailing_zero_ul,libc_stdc_first_trailing_zero_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_ul)(unsigned long x) {
	return x == 0 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_one_uc)(unsigned char x) {
	return x == (unsigned char)-1 ? (__SIZEOF_CHAR__ * __CHAR_BIT__) : __hybrid_ctz((unsigned char)~x);
}
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_one_us)(unsigned short x) {
	return x == (unsigned short)-1 ? (__SIZEOF_SHORT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned short)~x);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_first_trailing_one_ui,libc_stdc_first_trailing_one_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_first_trailing_one_ui,libc_stdc_first_trailing_one_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_one_ui)(unsigned int x) {
	return x == (unsigned int)-1 ? (__SIZEOF_INT__ * __CHAR_BIT__) : __hybrid_ctz((unsigned int)~x);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_first_trailing_one_ul,libc_stdc_first_trailing_one_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_one_ul)(unsigned long x) {
	return x == (unsigned long)-1 ? (__SIZEOF_LONG__ * __CHAR_BIT__) : __hybrid_ctz((unsigned long)~x);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_count_ones_uc)(unsigned char x) {
	return __hybrid_popcount(x);
}
#include <hybrid/__bit.h>
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_count_ones_us)(unsigned short x) {
	return __hybrid_popcount(x);
}
#include <hybrid/__bit.h>
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_count_zeros_uc)(unsigned char x) {
	return __hybrid_popcount((unsigned char)~x);
}
#include <hybrid/__bit.h>
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_count_zeros_us)(unsigned short x) {
	return __hybrid_popcount((unsigned short)~x);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_count_zeros_ui,libc_stdc_count_zeros_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_count_zeros_ui,libc_stdc_count_zeros_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
#include <hybrid/__bit.h>
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_count_zeros_ui)(unsigned int x) {
	return __hybrid_popcount((unsigned int)~x);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_count_zeros_ul,libc_stdc_count_zeros_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_count_zeros_ul)(unsigned long x) {
	return __hybrid_popcount((unsigned long)~x);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED bool
NOTHROW(LIBCCALL libc_stdc_has_single_bit_uc)(unsigned char x) {
	return (unsigned char)(x ^ (x - 1)) > (unsigned char)(x - 1);
}
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED bool
NOTHROW(LIBCCALL libc_stdc_has_single_bit_us)(unsigned short x) {
	return (unsigned short)(x ^ (x - 1)) > (unsigned short)(x - 1);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_has_single_bit_ui,libc_stdc_has_single_bit_ul,ATTR_CONST WUNUSED,bool,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_has_single_bit_ui,libc_stdc_has_single_bit_ull,ATTR_CONST WUNUSED,bool,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED bool
NOTHROW(LIBCCALL libc_stdc_has_single_bit_ui)(unsigned int x) {
	return (unsigned int)(x ^ (x - 1)) > (unsigned int)(x - 1);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_has_single_bit_ul,libc_stdc_has_single_bit_ull,ATTR_CONST WUNUSED,bool,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED bool
NOTHROW(LIBCCALL libc_stdc_has_single_bit_ul)(unsigned long x) {
	return (unsigned long)(x ^ (x - 1)) > (unsigned long)(x - 1);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_bit_width_uc)(unsigned char x) {
	return x == 0 ? 0 : (__SIZEOF_CHAR__ * __CHAR_BIT__) - __hybrid_clz(x);
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_bit_width_us)(unsigned short x) {
	return x == 0 ? 0 : (__SIZEOF_SHORT__ * __CHAR_BIT__) - __hybrid_clz(x);
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_bit_width_ui,libc_stdc_bit_width_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_bit_width_ui,libc_stdc_bit_width_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
#include <hybrid/__bit.h>
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_bit_width_ui)(unsigned int x) {
	return x == 0 ? 0 : (__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz(x);
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_bit_width_ul,libc_stdc_bit_width_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_bit_width_ul)(unsigned long x) {
	return x == 0 ? 0 : (__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz(x);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned char
NOTHROW(LIBCCALL libc_stdc_bit_floor_uc)(unsigned char x) {
	return x == 0 ? 0 : ((unsigned char)1 << (((__SIZEOF_CHAR__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned short
NOTHROW(LIBCCALL libc_stdc_bit_floor_us)(unsigned short x) {
	return x == 0 ? 0 : ((unsigned short)1 << (((__SIZEOF_SHORT__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_bit_floor_ui,libc_stdc_bit_floor_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_bit_floor_ui,libc_stdc_bit_floor_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
#include <hybrid/__bit.h>
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_bit_floor_ui)(unsigned int x) {
	return x == 0 ? 0 : ((unsigned int)1 << (((__SIZEOF_INT__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_bit_floor_ul,libc_stdc_bit_floor_ull,ATTR_CONST WUNUSED,unsigned long,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned long
NOTHROW(LIBCCALL libc_stdc_bit_floor_ul)(unsigned long x) {
	return x == 0 ? 0 : ((unsigned long)1 << (((__SIZEOF_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned char
NOTHROW(LIBCCALL libc_stdc_bit_ceil_uc)(unsigned char x) {
	return x <= 1 ? 1 : ((unsigned char)1 << ((__SIZEOF_CHAR__ * __CHAR_BIT__) - __hybrid_clz((unsigned char)(x - 1))));
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned short
NOTHROW(LIBCCALL libc_stdc_bit_ceil_us)(unsigned short x) {
	return x <= 1 ? 1 : ((unsigned short)1 << ((__SIZEOF_SHORT__ * __CHAR_BIT__) - __hybrid_clz((unsigned short)(x - 1))));
}
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_bit_ceil_ui,libc_stdc_bit_ceil_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_bit_ceil_ui,libc_stdc_bit_ceil_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
#else /* ... */
#include <hybrid/__bit.h>
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_bit_ceil_ui)(unsigned int x) {
	return x <= 1 ? 1 : ((unsigned int)1 << ((__SIZEOF_INT__ * __CHAR_BIT__) - __hybrid_clz((unsigned int)(x - 1))));
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
DEFINE_INTERN_ALIAS_P(libc_stdc_bit_ceil_ul,libc_stdc_bit_ceil_ull,ATTR_CONST WUNUSED,unsigned long,NOTHROW,LIBCCALL,(unsigned long x),(x));
#else /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned long
NOTHROW(LIBCCALL libc_stdc_bit_ceil_ul)(unsigned long x) {
	return x <= 1 ? 1 : ((unsigned long)1 << ((__SIZEOF_LONG__ * __CHAR_BIT__) - __hybrid_clz((unsigned long)(x - 1))));
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_LONG_LONG__ */
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_zeros_ull)(__ULONGLONG x) {
	return x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz(x);
}
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_leading_ones_ull)(__ULONGLONG x) {
	return x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_clz((__ULONGLONG)~x);
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_zeros_ull)(__ULONGLONG x) {
	return x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_trailing_ones_ull)(__ULONGLONG x) {
	return x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~x);
}
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_leading_zero_ull)(__ULONGLONG x) {
	return __hybrid_ffs((__ULONGLONG)~x);
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_ull)(__ULONGLONG x) {
	return x == 0 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz(x);
}
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_first_trailing_one_ull)(__ULONGLONG x) {
	return x == (__ULONGLONG)-1 ? (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) : __hybrid_ctz((__ULONGLONG)~x);
}
#include <hybrid/__bit.h>
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_count_zeros_ull)(__ULONGLONG x) {
	return __hybrid_popcount((__ULONGLONG)~x);
}
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED bool
NOTHROW(LIBCCALL libc_stdc_has_single_bit_ull)(__ULONGLONG x) {
	return (__ULONGLONG)(x ^ (x - 1)) > (__ULONGLONG)(x - 1);
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_stdc_bit_width_ull)(__ULONGLONG x) {
	return x == 0 ? 0 : (__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz(x);
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED __ULONGLONG
NOTHROW(LIBCCALL libc_stdc_bit_floor_ull)(__ULONGLONG x) {
	return x == 0 ? 0 : ((__ULONGLONG)1 << (((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - 1) - __hybrid_clz(x)));
}
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTERN ATTR_SECTION(".text.crt.stdbit") ATTR_CONST WUNUSED __ULONGLONG
NOTHROW(LIBCCALL libc_stdc_bit_ceil_ull)(__ULONGLONG x) {
	return x <= 1 ? 1 : ((__ULONGLONG)1 << ((__SIZEOF_LONG_LONG__ * __CHAR_BIT__) - __hybrid_clz((__ULONGLONG)(x - 1))));
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(stdc_leading_zeros_uc,libc_stdc_leading_zeros_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_leading_zeros_us,libc_stdc_leading_zeros_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_leading_zeros_ui,libc_stdc_leading_zeros_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_leading_zeros_ul,libc_stdc_leading_zeros_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_leading_ones_uc,libc_stdc_leading_ones_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_leading_ones_us,libc_stdc_leading_ones_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_leading_ones_ui,libc_stdc_leading_ones_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_leading_ones_ul,libc_stdc_leading_ones_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_zeros_uc,libc_stdc_trailing_zeros_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_zeros_us,libc_stdc_trailing_zeros_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_zeros_ui,libc_stdc_trailing_zeros_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_zeros_ul,libc_stdc_trailing_zeros_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_ones_uc,libc_stdc_trailing_ones_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_ones_us,libc_stdc_trailing_ones_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_ones_ui,libc_stdc_trailing_ones_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_ones_ul,libc_stdc_trailing_ones_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_leading_one_uc,libc_stdc_first_leading_one_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_leading_one_us,libc_stdc_first_leading_one_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_leading_zero_uc,libc_stdc_first_leading_zero_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_leading_zero_us,libc_stdc_first_leading_zero_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_leading_zero_ui,libc_stdc_first_leading_zero_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_leading_zero_ul,libc_stdc_first_leading_zero_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_zero_uc,libc_stdc_first_trailing_zero_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_zero_us,libc_stdc_first_trailing_zero_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_zero_ui,libc_stdc_first_trailing_zero_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_zero_ul,libc_stdc_first_trailing_zero_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_one_uc,libc_stdc_first_trailing_one_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_one_us,libc_stdc_first_trailing_one_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_one_ui,libc_stdc_first_trailing_one_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_one_ul,libc_stdc_first_trailing_one_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_count_ones_uc,libc_stdc_count_ones_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_count_ones_us,libc_stdc_count_ones_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_count_zeros_uc,libc_stdc_count_zeros_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_count_zeros_us,libc_stdc_count_zeros_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_count_zeros_ui,libc_stdc_count_zeros_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_count_zeros_ul,libc_stdc_count_zeros_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_has_single_bit_uc,libc_stdc_has_single_bit_uc,ATTR_CONST WUNUSED,bool,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_has_single_bit_us,libc_stdc_has_single_bit_us,ATTR_CONST WUNUSED,bool,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_has_single_bit_ui,libc_stdc_has_single_bit_ui,ATTR_CONST WUNUSED,bool,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_has_single_bit_ul,libc_stdc_has_single_bit_ul,ATTR_CONST WUNUSED,bool,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_width_uc,libc_stdc_bit_width_uc,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_width_us,libc_stdc_bit_width_us,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_width_ui,libc_stdc_bit_width_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_width_ul,libc_stdc_bit_width_ul,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_floor_uc,libc_stdc_bit_floor_uc,ATTR_CONST WUNUSED,unsigned char,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_floor_us,libc_stdc_bit_floor_us,ATTR_CONST WUNUSED,unsigned short,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_floor_ui,libc_stdc_bit_floor_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_floor_ul,libc_stdc_bit_floor_ul,ATTR_CONST WUNUSED,unsigned long,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_ceil_uc,libc_stdc_bit_ceil_uc,ATTR_CONST WUNUSED,unsigned char,NOTHROW,LIBCCALL,(unsigned char x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_ceil_us,libc_stdc_bit_ceil_us,ATTR_CONST WUNUSED,unsigned short,NOTHROW,LIBCCALL,(unsigned short x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_ceil_ui,libc_stdc_bit_ceil_ui,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_ceil_ul,libc_stdc_bit_ceil_ul,ATTR_CONST WUNUSED,unsigned long,NOTHROW,LIBCCALL,(unsigned long x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_leading_zeros_ull,libc_stdc_leading_zeros_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_leading_ones_ull,libc_stdc_leading_ones_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_zeros_ull,libc_stdc_trailing_zeros_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_trailing_ones_ull,libc_stdc_trailing_ones_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_leading_zero_ull,libc_stdc_first_leading_zero_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_zero_ull,libc_stdc_first_trailing_zero_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_first_trailing_one_ull,libc_stdc_first_trailing_one_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_count_zeros_ull,libc_stdc_count_zeros_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_has_single_bit_ull,libc_stdc_has_single_bit_ull,ATTR_CONST WUNUSED,bool,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_width_ull,libc_stdc_bit_width_ull,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_floor_ull,libc_stdc_bit_floor_ull,ATTR_CONST WUNUSED,__ULONGLONG,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
DEFINE_PUBLIC_ALIAS_P(stdc_bit_ceil_ull,libc_stdc_bit_ceil_ull,ATTR_CONST WUNUSED,__ULONGLONG,NOTHROW,LIBCCALL,(__ULONGLONG x),(x));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STDBIT_C */
