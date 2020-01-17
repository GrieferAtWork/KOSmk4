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
#ifndef _IEEE754_H
#define _IEEE754_H 1

#include <__stdinc.h>
#include <hybrid/__byteorder.h>
#include <hybrid/typecore.h>

/* Partially derived from GNU C /usr/include/i386-linux-gnu/ieee754.h */

/* Copyright (C) 1992-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>. */


#define IEEE754_FLOAT_BIAS       0x7f   /* Added to exponent. */
#define IEEE754_DOUBLE_BIAS      0x3ff  /* Added to exponent. */
#define IEEE854_LONG_DOUBLE_BIAS 0x3fff /* Added to exponent. */

__SYSDECL_BEGIN

#ifdef __CC__

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
#elif __SIZEOF_DOUBLE__ == 4
#define __IEEE754_FLOAT_TYPE__ double
#elif defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 4
#define __IEEE754_FLOAT_TYPE__ long double
#endif
#endif /* !__IEEE754_FLOAT_TYPE__ */

#ifndef __IEEE754_DOUBLE_TYPE__
#if __SIZEOF_FLOAT__ == 8
#define __IEEE754_DOUBLE_TYPE__ float
#elif __SIZEOF_DOUBLE__ == 8
#define __IEEE754_DOUBLE_TYPE__ double
#elif defined(__COMPILER_HAVE_LONGDOUBLE) && __SIZEOF_LONG_DOUBLE__ == 8
#define __IEEE754_DOUBLE_TYPE__ long double
#endif
#endif /* !__IEEE754_DOUBLE_TYPE__ */

#ifndef __IEEE854_LONG_DOUBLE_TYPE__
#if __SIZEOF_FLOAT__ == 12
#define __IEEE854_LONG_DOUBLE_TYPE__ float
#elif __SIZEOF_DOUBLE__ == 12
#define __IEEE854_LONG_DOUBLE_TYPE__ double
#elif __SIZEOF_LONG_DOUBLE__ == 12
#define __IEEE854_LONG_DOUBLE_TYPE__ long double
#endif
#endif /* !__IEEE854_LONG_DOUBLE_TYPE__ */


union __ATTR_ALIGNED(4) __ATTR_PACKED ieee754_float {
#ifdef __IEEE754_FLOAT_TYPE__
	__IEEE754_FLOAT_TYPE__ f; /* 32-bit */
#endif /* __IEEE754_FLOAT_TYPE__ */

	/* This is the IEEE 754 single-precision format. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int negative : 1;
		unsigned int exponent : 8;
		unsigned int mantissa : 23;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		unsigned int mantissa : 23;
		unsigned int exponent : 8;
		unsigned int negative : 1;
#endif
	} ieee;

	/* This format makes it easier to see if a NaN is a signaling NaN. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int negative : 1;
		unsigned int exponent : 8;
		unsigned int quiet_nan : 1;
		unsigned int mantissa : 22;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		unsigned int mantissa : 22;
		unsigned int quiet_nan : 1;
		unsigned int exponent : 8;
		unsigned int negative : 1;
#endif
	} ieee_nan;
};


union __ATTR_ALIGNED(8) __ATTR_PACKED ieee754_double {
#ifdef __IEEE754_DOUBLE_TYPE__
	__IEEE754_DOUBLE_TYPE__ d; /* 64-bit */
#endif /* __IEEE754_DOUBLE_TYPE__ */

	/* This is the IEEE 754 double-precision format. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int negative : 1;
		unsigned int exponent : 11;
		/* Together these comprise the mantissa. */
		unsigned int mantissa0 : 20;
		unsigned int mantissa1 : 32;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int mantissa0 : 20;
		unsigned int exponent : 11;
		unsigned int negative : 1;
		unsigned int mantissa1 : 32;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		/* Together these comprise the mantissa. */
		unsigned int mantissa1 : 32;
		unsigned int mantissa0 : 20;
		unsigned int exponent : 11;
		unsigned int negative : 1;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif /* Little endian. */
	} ieee;

	/* This format makes it easier to see if a NaN is a signaling NaN. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int negative : 1;
		unsigned int exponent : 11;
		unsigned int quiet_nan : 1;
		/* Together these comprise the mantissa. */
		unsigned int mantissa0 : 19;
		unsigned int mantissa1 : 32;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int mantissa0 : 19;
		unsigned int quiet_nan : 1;
		unsigned int exponent : 11;
		unsigned int negative : 1;
		unsigned int mantissa1 : 32;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		/* Together these comprise the mantissa. */
		unsigned int mantissa1 : 32;
		unsigned int mantissa0 : 19;
		unsigned int quiet_nan : 1;
		unsigned int exponent : 11;
		unsigned int negative : 1;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif
	} ieee_nan;
};


union __ATTR_ALIGNED(16) __ATTR_PACKED ieee854_long_double {
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
	__IEEE854_LONG_DOUBLE_TYPE__ d; /* 96-bit */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

#if 1 /* Ensure a size of 16 bytes. */
	__BYTE_TYPE__ __pad[16];
#endif

	/* This is the IEEE 854 double-extended-precision format. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int negative : 1;
		unsigned int exponent : 15;
		unsigned int empty : 16;
		unsigned int mantissa0 : 32;
		unsigned int mantissa1 : 32;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int exponent : 15;
		unsigned int negative : 1;
		unsigned int empty : 16;
		unsigned int mantissa0 : 32;
		unsigned int mantissa1 : 32;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		unsigned int mantissa1 : 32;
		unsigned int mantissa0 : 32;
		unsigned int exponent : 15;
		unsigned int negative : 1;
		unsigned int empty : 16;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif
	} ieee;

	/* This is for NaNs in the IEEE 854 double-extended-precision format. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int negative : 1;
		unsigned int exponent : 15;
		unsigned int empty : 16;
		unsigned int one : 1;
		unsigned int quiet_nan : 1;
		unsigned int mantissa0 : 30;
		unsigned int mantissa1 : 32;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int exponent : 15;
		unsigned int negative : 1;
		unsigned int empty : 16;
		unsigned int mantissa0 : 30;
		unsigned int quiet_nan : 1;
		unsigned int one : 1;
		unsigned int mantissa1 : 32;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		unsigned int mantissa1 : 32;
		unsigned int mantissa0 : 30;
		unsigned int quiet_nan : 1; /* Called the M-bit in the Intel manual */
		unsigned int one : 1;       /* Called the Integer bit, or J-bit in the Intel manual */
		unsigned int exponent : 15;
		unsigned int negative : 1;
		unsigned int empty : 16;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif
	} ieee_nan;
};



/* 80-bit long double format (this one simply excludes the 16-bit empty field) */
union __ATTR_PACKED ieee854_float80 {

	/* This is the IEEE 854 double-extended-precision format. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int negative : 1;
		unsigned int exponent : 15;
		unsigned int mantissa0 : 32;
		unsigned int mantissa1 : 32;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int exponent : 15;
		unsigned int negative : 1;
		unsigned int mantissa0 : 32;
		unsigned int mantissa1 : 32;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		unsigned int mantissa1 : 32;
		unsigned int mantissa0 : 32;
		unsigned int exponent : 15;
		unsigned int negative : 1;
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif
	} ieee;

	/* This is for NaNs in the IEEE 854 double-extended-precision format. */
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int negative : 1;
		unsigned int exponent : 15;
		unsigned int one : 1;
		unsigned int quiet_nan : 1;
		unsigned int mantissa0 : 30;
		unsigned int mantissa1 : 32;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		unsigned int exponent : 15;
		unsigned int negative : 1;
		unsigned int mantissa0 : 30;
		unsigned int quiet_nan : 1;
		unsigned int one : 1;
		unsigned int mantissa1 : 32;
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		unsigned int mantissa1 : 32;
		unsigned int mantissa0 : 30;
		unsigned int quiet_nan : 1;
		unsigned int one : 1;
		unsigned int exponent : 15;
		unsigned int negative : 1;
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

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_IEEE754_H */
