/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: EMX kLIBC     (/libc/include/ieee754.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/ieee754.h) */
/* (#) Portability: libc4/5       (/include/ieee754.h) */
/* (#) Portability: mintlib       (/include/ieee754.h) */
/* (#) Portability: uClibc        (/include/ieee754.h) */
#ifndef _IEEE754_H
#define _IEEE754_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__bitfield.h>
#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __USE_GLIBC_BLOAT
#include <endian.h>
#endif /* __USE_GLIBC_BLOAT */

/* For `union ieee754_float' */
#define IEEE754_FLOAT_MAXEXP 0xff
#define IEEE754_FLOAT_BIAS   0x7f /* Added to exponent. */
#define IEEE754_FLOAT_SHIFT  23

/* For `union ieee754_double' */
#define IEEE754_DOUBLE_MAXEXP 0x7ff
#define IEEE754_DOUBLE_BIAS   0x3ff /* Added to exponent. */
#define IEEE754_DOUBLE_SHIFT  20
#define _IEEE754_DOUBLE_BIAS  IEEE754_DOUBLE_BIAS

/* For `union ieee854_long_double' */
#define IEEE854_LONG_DOUBLE_MAXEXP 0x7fff
#define IEEE854_LONG_DOUBLE_BIAS   0x3fff /* Added to exponent. */
#define IEEE854_LONG_DOUBLE_SHIFT  0

#if defined(__i386__) || defined(__x86_64__)
#undef i387_float
#define i387_float       ieee754_float
#define _I387_FLOAT_BIAS IEEE754_FLOAT_BIAS
#endif /* __i387__ || __x86_64__ */


#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("f")
#pragma push_macro("d")
#pragma push_macro("ieee")
#pragma push_macro("ieee_nan")
#pragma push_macro("mantissa")
#pragma push_macro("quiet_nan")
#pragma push_macro("exponent")
#pragma push_macro("negative")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef f
#undef d
#undef ieee
#undef ieee_nan
#undef mantissa
#undef quiet_nan
#undef exponent
#undef negative

#ifndef __IEEE754_FLOAT_TYPE__
#if __SIZEOF_FLOAT__ == 4
#define __IEEE754_FLOAT_TYPE__ float
#define __IEEE754_FLOAT_TYPE_IS_FLOAT__ 1
#define __IEEE754_FLOAT_C(x) x##f
#if __SIZEOF_DOUBLE__ == 4
#define __IEEE754_FLOAT_TYPE_IS_DOUBLE__ 1
#endif /* __SIZEOF_DOUBLE__ == 4 */
#if defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 4
#define __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ 1
#endif /* defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 4 */
#elif __SIZEOF_DOUBLE__ == 4
#define __IEEE754_FLOAT_TYPE__ double
#define __IEEE754_FLOAT_TYPE_IS_DOUBLE__ 1
#define __IEEE754_FLOAT_C(x) x
#if defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 4
#define __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ 1
#endif /* defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 4 */
#elif defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 4
#define __IEEE754_FLOAT_TYPE__ __LONGDOUBLE
#define __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ 1
#define __IEEE754_FLOAT_C(x) x##L
#endif
#endif /* !__IEEE754_FLOAT_TYPE__ */

#ifndef __IEEE754_DOUBLE_TYPE__
#if __SIZEOF_FLOAT__ == 8
#define __IEEE754_DOUBLE_TYPE__ float
#define __IEEE754_DOUBLE_TYPE_IS_FLOAT__ 1
#define __IEEE754_DOUBLE_C(x) x##f
#if __SIZEOF_DOUBLE__ == 8
#define __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ 1
#endif /* __SIZEOF_DOUBLE__ == 8 */
#if defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 8
#define __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ 1
#endif /* defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 8 */
#elif __SIZEOF_DOUBLE__ == 8
#define __IEEE754_DOUBLE_TYPE__ double
#define __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ 1
#define __IEEE754_DOUBLE_C(x) x
#if defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 8
#define __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ 1
#endif /* defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 8 */
#elif defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 8
#define __IEEE754_DOUBLE_TYPE__ __LONGDOUBLE
#define __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ 1
#define __IEEE754_DOUBLE_C(x) x##L
#endif
#endif /* !__IEEE754_DOUBLE_TYPE__ */

#ifndef __IEEE854_LONG_DOUBLE_TYPE__
#if __SIZEOF_FLOAT__ == 12 || __SIZEOF_FLOAT__ == 16
#define __IEEE854_LONG_DOUBLE_TYPE__ float
#define __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ 1
#define __IEEE854_LONG_DOUBLE_C(x) x##f
#if __SIZEOF_DOUBLE__ == 12 || __SIZEOF_DOUBLE__ == 16
#define __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ 1
#endif /* __SIZEOF_DOUBLE__ == 12 || __SIZEOF_DOUBLE__ == 16 */
#if defined(__COMPILER_HAVE_LONGDOUBLE) && (__SIZEOF_LONG_DOUBLE__ == 12 || __SIZEOF_LONG_DOUBLE__ == 16)
#define __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ 1
#endif /* defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 16 */
#elif __SIZEOF_DOUBLE__ == 12 || __SIZEOF_DOUBLE__ == 16
#define __IEEE854_LONG_DOUBLE_TYPE__ double
#define __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ 1
#define __IEEE854_LONG_DOUBLE_C(x) x
#if defined(__COMPILER_HAVE_LONGDOUBLE) && (__SIZEOF_LONG_DOUBLE__ == 12 || __SIZEOF_LONG_DOUBLE__ == 16)
#define __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ 1
#endif /* defined(__COMPILER_HAVE_LONGDOUBLE) && (__SIZEOF_LONG_DOUBLE__ == 12 || __SIZEOF_LONG_DOUBLE__ == 16) */
#elif defined(__COMPILER_HAVE_LONGDOUBLE) && (__SIZEOF_LONG_DOUBLE__ == 12 || __SIZEOF_LONG_DOUBLE__ == 16)
#define __IEEE854_LONG_DOUBLE_TYPE__ __LONGDOUBLE
#define __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ 1
#define __IEEE854_LONG_DOUBLE_C(x) x##L
#endif
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */


union __ATTR_ALIGNED(4) __ATTR_PACKED ieee754_float {
#ifdef __IEEE754_FLOAT_TYPE__
	__IEEE754_FLOAT_TYPE__ f; /* 32-bit */
#endif /* __IEEE754_FLOAT_TYPE__ */

	/* IEEE 754 single-precision. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T negative : 1;
		__HYBRID_BITFIELD32_T exponent : 8;
		__HYBRID_BITFIELD32_T mantissa : 23;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		__HYBRID_BITFIELD32_T mantissa : 23;
		__HYBRID_BITFIELD32_T exponent : 8;
		__HYBRID_BITFIELD32_T negative : 1;
#endif
	} ieee;

	/* Same, but `quiet_nan' makes it easier to
	 * tell non-signaling-  and signaling  NaN. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T negative : 1;
		__HYBRID_BITFIELD32_T exponent : 8;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		__HYBRID_BITFIELD32_T mantissa : 22;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		__HYBRID_BITFIELD32_T mantissa : 22;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		__HYBRID_BITFIELD32_T exponent : 8;
		__HYBRID_BITFIELD32_T negative : 1;
#endif
	} ieee_nan;

#if defined(__i386__) || defined(__x86_64__)
	/* i387 single-precision. */
	struct {
		__HYBRID_BITFIELD32_T mantissa : 23;
		__HYBRID_BITFIELD32_T exponent : 8;
		__HYBRID_BITFIELD32_T negative : 1;
	} i387;
#endif /* __i387__ || __x86_64__ */
};


union __ATTR_ALIGNED(8) __ATTR_PACKED ieee754_double {
#ifdef __IEEE754_DOUBLE_TYPE__
	__IEEE754_DOUBLE_TYPE__ d; /* 64-bit */
#endif /* __IEEE754_DOUBLE_TYPE__ */

	/* IEEE 754 double-precision. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T negative : 1;
		__HYBRID_BITFIELD32_T exponent : 11;
		/* Together these comprise the mantissa. */
		__HYBRID_BITFIELD32_T mantissa0 : 20;
		__UINT32_TYPE__       mantissa1;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T mantissa0 : 20;
		__HYBRID_BITFIELD32_T exponent : 11;
		__HYBRID_BITFIELD32_T negative : 1;
		__UINT32_TYPE__       mantissa1;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		/* Together these comprise the mantissa. */
		__UINT32_TYPE__       mantissa1;
		__HYBRID_BITFIELD32_T mantissa0 : 20;
		__HYBRID_BITFIELD32_T exponent : 11;
		__HYBRID_BITFIELD32_T negative : 1;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif /* ... */
	} ieee;

	/* Same, but `quiet_nan' makes it easier to
	 * tell non-signaling-  and signaling  NaN. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T negative : 1;
		__HYBRID_BITFIELD32_T exponent : 11;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		/* Together these comprise the mantissa. */
		__HYBRID_BITFIELD32_T mantissa0 : 19;
		__UINT32_TYPE__       mantissa1;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T mantissa0 : 19;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		__HYBRID_BITFIELD32_T exponent : 11;
		__HYBRID_BITFIELD32_T negative : 1;
		__UINT32_TYPE__       mantissa1;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		/* Together these comprise the mantissa. */
		__UINT32_TYPE__       mantissa1;
		__HYBRID_BITFIELD32_T mantissa0 : 19;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		__HYBRID_BITFIELD32_T exponent : 11;
		__HYBRID_BITFIELD32_T negative : 1;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif /* ... */
	} ieee_nan;
};


union __ATTR_ALIGNED(16) __ATTR_PACKED ieee854_long_double {
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
	__IEEE854_LONG_DOUBLE_TYPE__ d; /* 96-bit */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

#if 1 /* Ensure a size of 16 bytes. */
	__BYTE_TYPE__ __pad[16];
#endif

	/* IEEE 854 double-extended-precision. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD16_T negative : 1;
		__HYBRID_BITFIELD16_T exponent : 15;
		__UINT16_TYPE__       empty;
		__UINT32_TYPE__       mantissa0;
		__UINT32_TYPE__       mantissa1;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD16_T exponent : 15;
		__HYBRID_BITFIELD16_T negative : 1;
		__UINT16_TYPE__       empty;
		__UINT32_TYPE__       mantissa0;
		__UINT32_TYPE__       mantissa1;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		__UINT32_TYPE__       mantissa1;
		__UINT32_TYPE__       mantissa0;
		__HYBRID_BITFIELD16_T exponent : 15;
		__HYBRID_BITFIELD16_T negative : 1;
		__UINT16_TYPE__       empty;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif
	} ieee;

	/* Same, but `quiet_nan' makes it easier to
	 * tell non-signaling-  and signaling  NaN. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD16_T negative : 1;
		__HYBRID_BITFIELD16_T exponent : 15;
		__UINT16_TYPE__       empty;
		__HYBRID_BITFIELD32_T one : 1;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		__HYBRID_BITFIELD32_T mantissa0 : 30;
		__UINT32_TYPE__       mantissa1;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD16_T exponent : 15;
		__HYBRID_BITFIELD16_T negative : 1;
		__UINT16_TYPE__       empty;
		__HYBRID_BITFIELD32_T mantissa0 : 30;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		__HYBRID_BITFIELD32_T one : 1;
		__UINT32_TYPE__       mantissa1;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		__UINT32_TYPE__       mantissa1;
		__HYBRID_BITFIELD32_T mantissa0 : 30;
		__HYBRID_BITFIELD32_T quiet_nan : 1; /* Called the M-bit in the Intel manual */
		__HYBRID_BITFIELD32_T one : 1;       /* Called the Integer bit, or J-bit in the Intel manual */
		__HYBRID_BITFIELD16_T exponent : 15;
		__HYBRID_BITFIELD16_T negative : 1;
		__UINT16_TYPE__       empty;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif
	} ieee_nan;
};



/* 80-bit long double format (this one simply excludes the 16-bit empty field) */
union __ATTR_PACKED ieee854_float80 {

	/* IEEE 854 double-extended-precision */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD16_T negative : 1;
		__HYBRID_BITFIELD16_T exponent : 15;
		__UINT32_TYPE__       mantissa0;
		__UINT32_TYPE__       mantissa1;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD16_T exponent : 15;
		__HYBRID_BITFIELD16_T negative : 1;
		__UINT32_TYPE__       mantissa0;
		__UINT32_TYPE__       mantissa1;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		__UINT32_TYPE__       mantissa1;
		__UINT32_TYPE__       mantissa0;
		__HYBRID_BITFIELD16_T exponent : 15;
		__HYBRID_BITFIELD16_T negative : 1;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif
	} ieee;

	/* Same, but `quiet_nan' makes it easier to
	 * tell non-signaling-  and signaling  NaN. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD16_T negative : 1;
		__HYBRID_BITFIELD16_T exponent : 15;
		__HYBRID_BITFIELD32_T one : 1;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		__HYBRID_BITFIELD32_T mantissa0 : 30;
		__UINT32_TYPE__       mantissa1;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD16_T exponent : 15;
		__HYBRID_BITFIELD16_T negative : 1;
		__HYBRID_BITFIELD32_T mantissa0 : 30;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		__HYBRID_BITFIELD32_T one : 1;
		__UINT32_TYPE__       mantissa1;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		__UINT32_TYPE__       mantissa1;
		__HYBRID_BITFIELD32_T mantissa0 : 30;
		__HYBRID_BITFIELD32_T quiet_nan : 1;
		__HYBRID_BITFIELD32_T one : 1;
		__HYBRID_BITFIELD16_T exponent : 15;
		__HYBRID_BITFIELD16_T negative : 1;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif
	} ieee_nan;
};


#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("negative")
#pragma pop_macro("exponent")
#pragma pop_macro("quiet_nan")
#pragma pop_macro("mantissa")
#pragma pop_macro("ieee_nan")
#pragma pop_macro("ieee")
#pragma pop_macro("d")
#pragma pop_macro("f")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_IEEE754_H */
