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
/* (#) Portability: OpenSolaris (/usr/src/head/nan.h) */
/* (#) Portability: libc4/5     (/include/nan.h) */
#ifndef _NAN_H
#define _NAN_H 1

#include <__stdinc.h>

#include <hybrid/__bitfield.h>
#include <hybrid/byteorder.h>

#include <sys/isa_defs.h>

#include <values.h>

#ifdef _IEEE_754
#ifdef __CC__
#include <asm/os/signal.h>

#include <libc/signal.h>

__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("fraction_low")
#pragma push_macro("bits")
#pragma push_macro("exponent")
#pragma push_macro("sign")
#pragma push_macro("inf_parts")
#pragma push_macro("bits")
#pragma push_macro("nan_parts")
#pragma push_macro("dnan")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef fraction_low
#undef bits
#undef exponent
#undef sign
#undef inf_parts
#undef bits
#undef nan_parts
#undef dnan

/* Same as `union ieee754_double' (from <ieee754.h>), but fields
 * have somewhat different names, and the struct itself is  used
 * by the macros below. */
typedef union __ATTR_ALIGNED(8) __ATTR_PACKED {
	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T sign : 1;      /* s.a. `union ieee754_double::ieee::negative' */
		__HYBRID_BITFIELD32_T exponent : 11; /* s.a. `union ieee754_double::ieee::exponent' */
		__HYBRID_BITFIELD32_T bits : 20;     /* s.a. `union ieee754_double::ieee::mantissa0' */
		__UINT32_TYPE__       fraction_low;  /* s.a. `union ieee754_double::ieee::mantissa1' */
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T bits : 20;     /* s.a. `union ieee754_double::ieee::mantissa0' */
		__HYBRID_BITFIELD32_T exponent : 11; /* s.a. `union ieee754_double::ieee::exponent' */
		__HYBRID_BITFIELD32_T sign : 1;      /* s.a. `union ieee754_double::ieee::negative' */
		__UINT32_TYPE__       fraction_low;  /* s.a. `union ieee754_double::ieee::mantissa1' */
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		__UINT32_TYPE__       fraction_low;  /* s.a. `union ieee754_double::ieee::mantissa1' */
		__HYBRID_BITFIELD32_T bits : 20;     /* s.a. `union ieee754_double::ieee::mantissa0' */
		__HYBRID_BITFIELD32_T exponent : 11; /* s.a. `union ieee754_double::ieee::exponent' */
		__HYBRID_BITFIELD32_T sign : 1;      /* s.a. `union ieee754_double::ieee::negative' */
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif /* ... */
	} inf_parts;

	struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T sign : 1;      /* s.a. `union ieee754_double::ieee_nan::negative' */
		__HYBRID_BITFIELD32_T exponent : 11; /* s.a. `union ieee754_double::ieee_nan::exponent' */
		__HYBRID_BITFIELD32_T qnan_bit : 1;  /* s.a. `union ieee754_double::ieee_nan::quiet_nan' */
		__HYBRID_BITFIELD32_T bits : 19;     /* s.a. `union ieee754_double::ieee_nan::mantissa0' */
		__UINT32_TYPE__       fraction_low;  /* s.a. `union ieee754_double::ieee_nan::mantissa1' */
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
		__HYBRID_BITFIELD32_T bits : 19;     /* s.a. `union ieee754_double::ieee_nan::mantissa0' */
		__HYBRID_BITFIELD32_T qnan_bit : 1;  /* s.a. `union ieee754_double::ieee_nan::quiet_nan' */
		__HYBRID_BITFIELD32_T exponent : 11; /* s.a. `union ieee754_double::ieee_nan::exponent' */
		__HYBRID_BITFIELD32_T sign : 1;      /* s.a. `union ieee754_double::ieee_nan::negative' */
		__UINT32_TYPE__       fraction_low;  /* s.a. `union ieee754_double::ieee_nan::mantissa1' */
#else /* __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__ */
		__UINT32_TYPE__       fraction_low;  /* s.a. `union ieee754_double::ieee_nan::mantissa1' */
		__HYBRID_BITFIELD32_T bits : 19;     /* s.a. `union ieee754_double::ieee_nan::mantissa0' */
		__HYBRID_BITFIELD32_T qnan_bit : 1;  /* s.a. `union ieee754_double::ieee_nan::quiet_nan' */
		__HYBRID_BITFIELD32_T exponent : 11; /* s.a. `union ieee754_double::ieee_nan::exponent' */
		__HYBRID_BITFIELD32_T sign : 1;      /* s.a. `union ieee754_double::ieee_nan::negative' */
#endif /* __FLOAT_WORD_ORDER__ != __ORDER_BIG_ENDIAN__ */
#endif /* ... */
	} nan_parts;

#ifdef __IEEE754_DOUBLE_TYPE__
	__IEEE754_DOUBLE_TYPE__ d;
#endif /* __IEEE754_DOUBLE_TYPE__ */
} dnan;

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("dnan")
#pragma pop_macro("nan_parts")
#pragma pop_macro("bits")
#pragma pop_macro("inf_parts")
#pragma pop_macro("sign")
#pragma pop_macro("exponent")
#pragma pop_macro("bits")
#pragma pop_macro("fraction_low")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


/* Re-interpret `x' as a dnan-structure. */
#define __PRIVATE_ASDNAN(x) (*(dnan const *)&(x))

/* Helper macros. */
#define IsNANorINF(x)  (__PRIVATE_ASDNAN(x).nan_parts.exponent == 0x7ff)
#define IsINF(x)       (__PRIVATE_ASDNAN(x).inf_parts.bits == 0 && __PRIVATE_ASDNAN(x).inf_parts.fraction_low == 0)
#define IsPosNAN(x)    (__PRIVATE_ASDNAN(x).nan_parts.sign == 0)
#define IsNegNAN(x)    (__PRIVATE_ASDNAN(x).nan_parts.sign == 1)
#define GETNaNPC(dval) (__PRIVATE_ASDNAN(dval).inf_parts.bits << 12 | __PRIVATE_ASDNAN(dval).nan_parts.fraction_low >> 20)
#define NaN(x)         (__PRIVATE_ASDNAN(x).nan_parts.exponent == 0x7ff)
#if defined(____libc_raise_defined) && defined(__SIGFPE)
#define KILLFPE()      (void)__libc_raise(__SIGFPE)
#define KILLNaN(x)     (NaN(x) ? KILLFPE() : (void)0)
#endif /* ____libc_raise_defined && __SIGFPE */

__DECL_END
#endif /* __CC__ */

/* From libc4/5 */
#include <bits/math-constants.h>
#if !defined(NAN) && defined(__NANF)
#define NAN __NANF /* float NAN; */
#endif /* !NAN && __NANF */
#include <hybrid/host.h>
#if defined(__i386__) || defined(__x86_64__)
/* TODO: double _SNAN;  // signaling NAN */
/* TODO: double _QNAN;  // quiet NAN */
/* TODO: float  _SNANF; // signaling NAN */
/* TODO: float  _QNANF; // quiet NAN */
#endif /* __i386__ || __x86_64__ */


#else /* _IEEE_754 */
#error "Unsupported floating-mode data model"
#endif /* !_IEEE_754 */

#endif /* !_NAN_H */
