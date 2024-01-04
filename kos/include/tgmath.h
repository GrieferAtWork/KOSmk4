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
/* (#) Portability: Cygwin        (/newlib/libc/include/tgmath.h) */
/* (#) Portability: FreeBSD       (/include/tgmath.h) */
/* (#) Portability: GNU C Library (/math/tgmath.h) */
/* (#) Portability: GNU Hurd      (/usr/include/tgmath.h) */
/* (#) Portability: NetBSD        (/include/tgmath.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/tgmath.h) */
/* (#) Portability: OpenBSD       (/include/tgmath.h) */
/* (#) Portability: Windows Kits  (/ucrt/tgmath.h) */
/* (#) Portability: libc6         (/include/tgmath.h) */
/* (#) Portability: musl libc     (/include/tgmath.h) */
/* (#) Portability: uClibc        (/include/tgmath.h) */
#ifndef _TGMATH_H
#define _TGMATH_H 1

#include <__stdinc.h>

#ifdef _Complex_I
#include <complex.h>
#endif /* _Complex_I */

#include <math.h>

/* In c++, both <complex.h> and <math.h> already define all of the necessary
 * overloads to facilitate type-generic use  of all of the functions  below! */
#ifndef __cplusplus
#if !defined(__NO_builtin_types_compatible_p) && defined(__COMPILER_HAVE_TYPEOF)
#define __PRIVATE_TG_ISTYPE(x, T) __builtin_types_compatible_p(__typeof__(x), T)
#else /* !__NO_builtin_types_compatible_p && __COMPILER_HAVE_TYPEOF */
#define __PRIVATE_TG_ISTYPE(x, T) (sizeof(x) == sizeof(T))
#endif /* __NO_builtin_types_compatible_p || !__COMPILER_HAVE_TYPEOF */
#define __PRIVATE_TG_COMMON(x, y)        (x) + (y)
#define __PRIVATE_TG_COMMON3(x, y, z)    (x) + (y) + (z)
#define __PRIVATE_TG_ISTYPE2(x, y, T)    __PRIVATE_TG_ISTYPE(__PRIVATE_TG_COMMON(x, y), T)
#define __PRIVATE_TG_ISTYPE3(x, y, z, T) __PRIVATE_TG_ISTYPE(__PRIVATE_TG_COMMON3(x, y, z), T)

/* tg-selector macros (non-complex only) */
#ifdef __COMPILER_HAVE_C11_GENERIC
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __PRIVATE_TGF1(x, mathf, math, mathl) \
	_Generic(x,                               \
	         float:        mathf(x),          \
	         __LONGDOUBLE: mathl(x),          \
	         default:      math(x))
#define __PRIVATE_TGF3xxi(x, y, z, mathf, math, mathl) \
	_Generic(x,                                        \
	         float:        mathf(x, y, z),             \
	         __LONGDOUBLE: mathl(x, y, z),             \
	         default:      math(x, y, z))
#define __PRIVATE_TGF2(x, y, mathf, math, mathl) \
	_Generic(__PRIVATE_TG_COMMON(x, y),          \
	         float:        mathf(x, y),          \
	         __LONGDOUBLE: mathl(x, y),          \
	         default:      math(x, y))
#define __PRIVATE_TGF3(x, y, z, mathf, math, mathl) \
	_Generic(__PRIVATE_TG_COMMON3(x, y, z),         \
	         float:        mathf(x, y, z),          \
	         __LONGDOUBLE: mathl(x, y, z),          \
	         default:      math(x, y, z))
#define __PRIVATE_TGF2x(x, y, arg3, mathf, math, mathl) \
	_Generic(__PRIVATE_TG_COMMON(x, y),                 \
	         float:        mathf(x, y, arg3),           \
	         __LONGDOUBLE: mathl(x, y, arg3),           \
	         default:      math(x, y, arg3))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __PRIVATE_TGF1(x, mathf, math, mathl) \
	_Generic(x,                               \
	         float:   mathf(x),               \
	         default: math(x))
#define __PRIVATE_TGF3xxi(x, y, z, mathf, math, mathl) \
	_Generic(x,                                        \
	         float:   mathf(x, y, z),                  \
	         default: math(x, y, z))
#define __PRIVATE_TGF2(x, y, mathf, math, mathl) \
	_Generic(__PRIVATE_TG_COMMON(x, y),          \
	         float:   mathf(x, y),               \
	         default: math(x, y))
#define __PRIVATE_TGF3(x, y, z, mathf, math, mathl) \
	_Generic(__PRIVATE_TG_COMMON3(x, y, z),         \
	         float:   mathf(x, y, z),               \
	         default: math(x, y, z))
#define __PRIVATE_TGF2x(x, y, arg3, mathf, math, mathl) \
	_Generic(__PRIVATE_TG_COMMON(x, y),                 \
	         float:   mathf(x, y, arg3),                \
	         default: math(x, y, arg3))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif !defined(__NO_builtin_choose_expr)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __PRIVATE_TGF1(x, mathf, math, mathl)                             \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float),        mathf(x), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, __LONGDOUBLE), mathl(x), \
	                                                            math(x)))
#define __PRIVATE_TGF3xxi(x, y, z, mathf, math, mathl)                          \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float),        mathf(x, y, z), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, __LONGDOUBLE), mathl(x, y, z), \
	                                                            math(x, y, z)))
#define __PRIVATE_TGF2(x, y, mathf, math, mathl)                                 \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, float),        mathf(x, y), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE), mathl(x, y), \
	                                                                math(x, y)))
#define __PRIVATE_TGF3(x, y, z, mathf, math, mathl)                                    \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE3(x, y, z, float),        mathf(x, y, z), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE3(x, y, z, __LONGDOUBLE), mathl(x, y, z), \
	                                                                   math(x, y, z)))
#define __PRIVATE_TGF2x(x, y, arg3, mathf, math, mathl)                                \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, float),        mathf(x, y, arg3), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE), mathl(x, y, arg3), \
	                                                                math(x, y, arg3)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __PRIVATE_TGF1(x, mathf, math, mathl) \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float), mathf(x), math(x))
#define __PRIVATE_TGF3xxi(x, y, z, mathf, math, mathl) \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float), mathf(x, y, z), math(x, y, z))
#define __PRIVATE_TGF2(x, y, mathf, math, mathl) \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, float), mathf(x, y), math(x, y))
#define __PRIVATE_TGF3(x, y, z, mathf, math, mathl) \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE3(x, y, z, float), mathf(x, y, z), math(x, y, z))
#define __PRIVATE_TGF2x(x, y, arg3, mathf, math, mathl) \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, float), mathf(x, y, arg3), math(x, y, arg3))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif defined(__COMPILER_HAVE_TYPEOF)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __PRIVATE_TGF1(x, mathf, math, mathl)                                         \
	(__PRIVATE_TG_ISTYPE(x, float)        ? (__typeof__(x))mathf((float)(x)) :        \
	 __PRIVATE_TG_ISTYPE(x, __LONGDOUBLE) ? (__typeof__(x))mathl((__LONGDOUBLE)(x)) : \
	                                        (__typeof__(x))math((double)(x)))
#define __PRIVATE_TGF1i(x, mathf, math, mathl)                         \
	(__PRIVATE_TG_ISTYPE(x, float)        ? mathf((float)(x)) :        \
	 __PRIVATE_TG_ISTYPE(x, __LONGDOUBLE) ? mathl((__LONGDOUBLE)(x)) : \
	                                        math((double)(x)))
#define __PRIVATE_TGF3xxi(x, y, z, mathf, math, mathl)                       \
	(__PRIVATE_TG_ISTYPE(x, float)        ? mathf((float)(x), y, z) :        \
	 __PRIVATE_TG_ISTYPE(x, __LONGDOUBLE) ? mathl((__LONGDOUBLE)(x), y, z) : \
	                                        math((double)(x), y, z))
#define __PRIVATE_TGF2(x, y, mathf, math, mathl)                                                                                     \
	(__PRIVATE_TG_ISTYPE2(x, y, float)        ? (__typeof__(__PRIVATE_TG_COMMON(x, y)))mathf((float)(x), (float)(y)) :               \
	 __PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE) ? (__typeof__(__PRIVATE_TG_COMMON(x, y)))mathl((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)) : \
	                                            (__typeof__(__PRIVATE_TG_COMMON(x, y)))math((double)(x), (double)(y)))
#define __PRIVATE_TGF3(x, y, z, mathf, math, mathl)                                                                                                            \
	(__PRIVATE_TG_ISTYPE3(x, y, z, float)        ? (__typeof__(__PRIVATE_TG_COMMON3(x, y, z)))mathf((float)(x), (float)(y), (float)(z)) :                      \
	 __PRIVATE_TG_ISTYPE3(x, y, z, __LONGDOUBLE) ? (__typeof__(__PRIVATE_TG_COMMON3(x, y, z)))mathl((__LONGDOUBLE)(x), (__LONGDOUBLE)(y), (__LONGDOUBLE)(z)) : \
	                                               (__typeof__(__PRIVATE_TG_COMMON3(x, y, z)))math((double)(x), (double)(y), (double)(z)))
#define __PRIVATE_TGF2x(x, y, arg3, mathf, math, mathl)                                                                                    \
	(__PRIVATE_TG_ISTYPE2(x, y, float)        ? (__typeof__(__PRIVATE_TG_COMMON(x, y)))mathf((float)(x), (float)(y), arg3) :               \
	 __PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE) ? (__typeof__(__PRIVATE_TG_COMMON(x, y)))mathl((__LONGDOUBLE)(x), (__LONGDOUBLE)(y), arg3) : \
	                                            (__typeof__(__PRIVATE_TG_COMMON(x, y)))math((double)(x), (double)(y), arg3))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __PRIVATE_TGF1(x, mathf, math, mathl) \
	(__PRIVATE_TG_ISTYPE(x, float)            \
	 ? (__typeof__(x))mathf((float)(x))       \
	 : (__typeof__(x))math((double)(x)))
#define __PRIVATE_TGF1i(x, mathf, math, mathl) \
	(__PRIVATE_TG_ISTYPE(x, float)             \
	 ? mathf((float)(x))                       \
	 : math((double)(x)))
#define __PRIVATE_TGF3xxi(x, y, z, mathf, math, mathl) \
	(__PRIVATE_TG_ISTYPE(x, float)                     \
	 ? mathf((float)(x), y, z)                         \
	 : math((double)(x), y, z))
#define __PRIVATE_TGF2(x, y, mathf, math, mathl)                            \
	(__PRIVATE_TG_ISTYPE2(x, y, float)                                      \
	 ? (__typeof__(__PRIVATE_TG_COMMON(x, y)))mathf((float)(x), (float)(y)) \
	 : (__typeof__(__PRIVATE_TG_COMMON(x, y)))math((double)(x), (double)(y)))
#define __PRIVATE_TGF3(x, y, z, mathf, math, mathl)                                         \
	(__PRIVATE_TG_ISTYPE3(x, y, z, float)                                                   \
	 ? (__typeof__(__PRIVATE_TG_COMMON3(x, y, z)))mathf((float)(x), (float)(y), (float)(z)) \
	 : (__typeof__(__PRIVATE_TG_COMMON3(x, y, z)))math((double)(x), (double)(y), (double)(z)))
#define __PRIVATE_TGF2x(x, y, arg3, mathf, math, mathl)                           \
	(__PRIVATE_TG_ISTYPE2(x, y, float)                                            \
	 ? (__typeof__(__PRIVATE_TG_COMMON(x, y)))mathf((float)(x), (float)(y), arg3) \
	 : (__typeof__(__PRIVATE_TG_COMMON(x, y)))math((double)(x), (double)(y), arg3))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#else /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __PRIVATE_TGF1(x, mathf, math, mathl)                          \
	(__PRIVATE_TG_ISTYPE(x, float)        ? mathf((float)(x)) :        \
	 __PRIVATE_TG_ISTYPE(x, __LONGDOUBLE) ? mathl((__LONGDOUBLE)(x)) : \
	                                        math((double)(x)))
#define __PRIVATE_TGF3xxi(x, mathf, math, mathl)                             \
	(__PRIVATE_TG_ISTYPE(x, float)        ? mathf((float)(x), y, z) :        \
	 __PRIVATE_TG_ISTYPE(x, __LONGDOUBLE) ? mathl((__LONGDOUBLE)(x), y, z) : \
	                                        math((double)(x), y, z))
#define __PRIVATE_TGF2(x, y, mathf, math, mathl)                                              \
	(__PRIVATE_TG_ISTYPE2(x, y, float)        ? mathf((float)(x), (float)(y)) :               \
	 __PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE) ? mathl((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)) : \
	                                            math((double)(x), (double)(y)))
#define __PRIVATE_TGF3(x, y, z, mathf, math, mathl)                                                                 \
	(__PRIVATE_TG_ISTYPE3(x, y, z, float)        ? mathf((float)(x), (float)(y), (float)(z)) :                      \
	 __PRIVATE_TG_ISTYPE3(x, y, z, __LONGDOUBLE) ? mathl((__LONGDOUBLE)(x), (__LONGDOUBLE)(y), (__LONGDOUBLE)(z)) : \
	                                               math((double)(x), (double)(y), (double)(z)))
#define __PRIVATE_TGF2x(x, y, arg3, mathf, math, mathl)                                             \
	(__PRIVATE_TG_ISTYPE2(x, y, float)        ? mathf((float)(x), (float)(y), arg3) :               \
	 __PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE) ? mathl((__LONGDOUBLE)(x), (__LONGDOUBLE)(y), arg3) : \
	                                            math((double)(x), (double)(y), arg3))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __PRIVATE_TGF1(x, mathf, math, mathl) \
	(__PRIVATE_TG_ISTYPE(x, float) ? mathf((float)(x)) : math((double)(x)))
#define __PRIVATE_TGF3xxi(x, y, z, mathf, math, mathl) \
	(__PRIVATE_TG_ISTYPE(x, float) ? mathf((float)(x), y, z) : math((double)(x), y, z))
#define __PRIVATE_TGF2(x, y, mathf, math, mathl) \
	(__PRIVATE_TG_ISTYPE2(x, y, float) ? mathf((float)(x), (float)(y)) : math((double)(x), (double)(y)))
#define __PRIVATE_TGF3(x, y, z, mathf, math, mathl) \
	(__PRIVATE_TG_ISTYPE3(x, y, z, float) ? mathf((float)(x), (float)(y), (float)(z)) : math((double)(x), (double)(y), (double)(z)))
#define __PRIVATE_TGF2x(x, y, arg3, mathf, math, mathl) \
	(__PRIVATE_TG_ISTYPE2(x, y, float) ? mathf((float)(x), (float)(y), arg3) : math((double)(x), (double)(y), arg3))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#endif /* !... */


#ifndef __PRIVATE_TGF1i
#define __PRIVATE_TGF1i __PRIVATE_TGF1
#endif /* !__PRIVATE_TGF1i */


/* (optional) integration of <complex.h> functions (if supposed by the compiler). */
#ifdef _Complex_I
#ifdef __COMPILER_HAVE_C11_GENERIC
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __PRIVATE_TGC1(x, cmathf, cmath, cmathl) \
	_Generic(x,                                  \
	         float _Complex:       cmathf(x),    \
	         long double _Complex: cmathl(x),    \
	         default:              cmath(x))
#define __PRIVATE_TGCF1(x, mathf, math, mathl, cmathf, cmath, cmathl) \
	_Generic(x,                                                       \
	         float _Complex:       cmathf(x),                         \
	         long double _Complex: cmathl(x),                         \
	         double _Complex:      cmath(x),                          \
	         float:                mathf(x),                          \
	         __LONGDOUBLE:         mathl(x),                          \
	         default:              math(x))
#define __PRIVATE_TGCF2(x, y, mathf, math, mathl, cmathf, cmath, cmathl) \
	_Generic(__PRIVATE_TG_COMMON(x, y),                                  \
	         float _Complex:       cmathf(x, y),                         \
	         long double _Complex: cmathl(x, y),                         \
	         double _Complex:      cmath(x, y),                          \
	         float:                mathf(x, y),                          \
	         __LONGDOUBLE:         mathl(x, y),                          \
	         default:              math(x, y))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __PRIVATE_TGC1(x, cmathf, cmath, cmathl) \
	_Generic(x,                                  \
	         float _Complex: cmathf(x),          \
	         default:        cmath(x))
#define __PRIVATE_TGCF1(x, mathf, math, mathl, cmathf, cmath, cmathl) \
	_Generic(x,                                                       \
	         float _Complex:  cmathf(x),                              \
	         double _Complex: cmath(x),                               \
	         float:           mathf(x),                               \
	         default:         math(x))
#define __PRIVATE_TGCF2(x, y, mathf, math, mathl, cmathf, cmath, cmathl) \
	_Generic(__PRIVATE_TG_COMMON(x, y),                                  \
	         float _Complex:  cmathf(x, y),                              \
	         double _Complex: cmath(x, y),                               \
	         float:           mathf(x, y),                               \
	         default:         math(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif !defined(__NO_builtin_choose_expr)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __PRIVATE_TGC1(x, cmathf, cmath, cmathl)                                   \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float _Complex),       cmathf(x), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, long double _Complex), cmathl(x), \
	                                                                    cmath(x)))
#define __PRIVATE_TGCF1(x, mathf, math, mathl, cmathf, cmath, cmathl)              \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float _Complex),       cmathf(x), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, long double _Complex), cmathl(x), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, double _Complex),      cmath(x),  \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float),                mathf(x),  \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, __LONGDOUBLE),         mathl(x),  \
	                                                                    math(x))))))
#define __PRIVATE_TGCF2(x, y, mathf, math, mathl, cmathf, cmath, cmathl)                  \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, float _Complex),       cmathf(x, y), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, long double _Complex), cmathl(x, y), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, double _Complex),      cmath(x, y),  \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, float),                mathf(x, y),  \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE),         mathl(x, y),  \
	                                                                        math(x, y))))))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __PRIVATE_TGC1(x, cmathf, cmath, cmathl) \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float _Complex), cmathf(x), cmath(x))
#define __PRIVATE_TGCF1(x, mathf, math, mathl, cmathf, cmath, cmathl)         \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float _Complex),  cmathf(x), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, double _Complex), cmath(x),  \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE(x, float),           mathf(x),  \
	                                                               math(x))))
#define __PRIVATE_TGCF2(x, y, mathf, math, mathl, cmathf, cmath, cmathl)             \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, float _Complex),  cmathf(x, y), \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, double _Complex), cmath(x, y),  \
	__builtin_choose_expr(__PRIVATE_TG_ISTYPE2(x, y, float),           mathf(x, y),  \
	                                                                   math(x, y))))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif defined(__COMPILER_HAVE_TYPEOF)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __PRIVATE_TGC1(x, cmathf, cmath, cmathl)                                                     \
	(__PRIVATE_TG_ISTYPE(x, float _Complex)       ? (__typeof(x))cmathf((float _Complex)(x)) :       \
	 __PRIVATE_TG_ISTYPE(x, long double _Complex) ? (__typeof(x))cmathl((long double _Complex)(x)) : \
	                                                (__typeof(x))cmath((double _Complex)(x)))
#define __PRIVATE_TGCF1(x, mathf, math, mathl, cmathf, cmath, cmathl)                                \
	(__PRIVATE_TG_ISTYPE(x, float _Complex)       ? (__typeof(x))cmathf((float _Complex)(x)) :       \
	 __PRIVATE_TG_ISTYPE(x, long double _Complex) ? (__typeof(x))cmathl((long double _Complex)(x)) : \
	 __PRIVATE_TG_ISTYPE(x, double _Complex)      ? (__typeof(x))cmath((double _Complex)(x)) :       \
	 __PRIVATE_TG_ISTYPE(x, float)                ? (__typeof(x))mathf((float)(x)) :                 \
	 __PRIVATE_TG_ISTYPE(x, __LONGDOUBLE)         ? (__typeof(x))mathl((__LONGDOUBLE)(x)) :          \
	                                                (__typeof(x))math((double)(x)))
#define __PRIVATE_TGCF2(x, y, mathf, math, mathl, cmathf, cmath, cmathl)                                                                                    \
	(__PRIVATE_TG_ISTYPE2(x, y, float _Complex)       ? (__typeof(__PRIVATE_TG_COMMON(x, y)))cmathf((float _Complex)(x), (float _Complex)(y)) :             \
	 __PRIVATE_TG_ISTYPE2(x, y, long double _Complex) ? (__typeof(__PRIVATE_TG_COMMON(x, y)))cmathl((long double _Complex)(x), (long double _Complex)(y)) : \
	 __PRIVATE_TG_ISTYPE2(x, y, double _Complex)      ? (__typeof(__PRIVATE_TG_COMMON(x, y)))cmath((double _Complex)(x), (double _Complex)(y)) :            \
	 __PRIVATE_TG_ISTYPE2(x, y, float)                ? (__typeof(__PRIVATE_TG_COMMON(x, y)))mathf((float)(x), (float)(y)) :                                \
	 __PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE)         ? (__typeof(__PRIVATE_TG_COMMON(x, y)))mathl((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)) :                  \
	                                                    (__typeof(__PRIVATE_TG_COMMON(x, y)))math((double)(x), (double)(y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __PRIVATE_TGC1(x, cmathf, cmath, cmathl) \
	(__PRIVATE_TG_ISTYPE(x, float _Complex)      \
	 ? (__typeof(x))cmathf((float _Complex)(x))  \
	 : (__typeof(x))cmath((double _Complex)(x)))
#define __PRIVATE_TGCF1(x, mathf, math, mathl, cmathf, cmath, cmathl)                     \
	(__PRIVATE_TG_ISTYPE(x, float _Complex)  ? (__typeof(x))cmathf((float _Complex)(x)) : \
	 __PRIVATE_TG_ISTYPE(x, double _Complex) ? (__typeof(x))cmath((double _Complex)(x)) : \
	 __PRIVATE_TG_ISTYPE(x, float)           ? (__typeof(x))mathf((float)(x)) :           \
	                                           (__typeof(x))math((double)(x)))
#define __PRIVATE_TGCF2(x, y, mathf, math, mathl, cmathf, cmath, cmathl)                                                                    \
	(__PRIVATE_TG_ISTYPE2(x, y, float _Complex)  ? (__typeof(__PRIVATE_TG_COMMON(x, y)))cmathf((float _Complex)(x), (float _Complex)(y)) :  \
	 __PRIVATE_TG_ISTYPE2(x, y, double _Complex) ? (__typeof(__PRIVATE_TG_COMMON(x, y)))cmath((double _Complex)(x), (double _Complex)(y)) : \
	 __PRIVATE_TG_ISTYPE2(x, y, float)           ? (__typeof(__PRIVATE_TG_COMMON(x, y)))mathf((float)(x), (float)(y)) :                     \
	                                               (__typeof(__PRIVATE_TG_COMMON(x, y)))math((double)(x), (double)(y)))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#else /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __PRIVATE_TGC1(x, cmathf, cmath, cmathl)                                        \
	(__PRIVATE_TG_ISTYPE(x, float _Complex)       ? cmathf((float _Complex)(x)) :       \
	 __PRIVATE_TG_ISTYPE(x, long double _Complex) ? cmathl((long double _Complex)(x)) : \
	                                                cmath((double _Complex)(x)))
#define __PRIVATE_TGCF1(x, mathf, math, mathl, cmathf, cmath, cmathl)                   \
	(__PRIVATE_TG_ISTYPE(x, float _Complex)       ? cmathf((float _Complex)(x)) :       \
	 __PRIVATE_TG_ISTYPE(x, long double _Complex) ? cmathl((long double _Complex)(x)) : \
	 __PRIVATE_TG_ISTYPE(x, double _Complex)      ? cmath((double _Complex)(x)) :       \
	 __PRIVATE_TG_ISTYPE(x, float)                ? mathf((float)(x)) :                 \
	 __PRIVATE_TG_ISTYPE(x, __LONGDOUBLE)         ? mathl((__LONGDOUBLE)(x)) :          \
	                                                math((double)(x)))
#define __PRIVATE_TGCF2(x, y, mathf, math, mathl, cmathf, cmath, cmathl)                                               \
	(__PRIVATE_TG_ISTYPE2(x, y, float _Complex)       ? cmathf((float _Complex)(x), (float _Complex)(y)) :             \
	 __PRIVATE_TG_ISTYPE2(x, y, long double _Complex) ? cmathl((long double _Complex)(x), (long double _Complex)(y)) : \
	 __PRIVATE_TG_ISTYPE2(x, y, double _Complex)      ? cmath((double _Complex)(x), (double _Complex)(y)) :            \
	 __PRIVATE_TG_ISTYPE2(x, y, float)                ? mathf((float)(x), (float)(y)) :                                \
	 __PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE)         ? mathl((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)) :                  \
	                                                    math((double)(x), (double)(y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __PRIVATE_TGC1(x, cmathf, cmath, cmathl) \
	(__PRIVATE_TG_ISTYPE(x, float _Complex) ? cmathf((float _Complex)(x)) : cmath((double _Complex)(x)))
#define __PRIVATE_TGCF1(x, mathf, math, mathl, cmathf, cmath, cmathl)        \
	(__PRIVATE_TG_ISTYPE(x, float _Complex)  ? cmathf((float _Complex)(x)) : \
	 __PRIVATE_TG_ISTYPE(x, double _Complex) ? cmath((double _Complex)(x)) : \
	 __PRIVATE_TG_ISTYPE(x, float)           ? mathf((float)(x)) :           \
	                                           math((double)(x)))
#define __PRIVATE_TGCF2(x, y, mathf, math, mathl, cmathf, cmath, cmathl)                               \
	(__PRIVATE_TG_ISTYPE2(x, y, float _Complex)  ? cmathf((float _Complex)(x), (float _Complex)(y)) :  \
	 __PRIVATE_TG_ISTYPE2(x, y, double _Complex) ? cmath((double _Complex)(x), (double _Complex)(y)) : \
	 __PRIVATE_TG_ISTYPE2(x, y, float)           ? mathf((float)(x), (float)(y)) :                     \
	                                               math((double)(x), (double)(y)))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#endif /* !... */


/* Complex-only functions */
#define carg(x)  __PRIVATE_TGC1(x, cargf, carg, cargl)
#define conj(x)  __PRIVATE_TGC1(x, conjf, conj, conjl)
#define creal(x) __PRIVATE_TGC1(x, crealf, creal, creall)
#define cimag(x) __PRIVATE_TGC1(x, cimagf, cimag, cimagl)
#define cproj(x) __PRIVATE_TGC1(x, cprojf, cproj, cprojl)

/* Complex/non-complex hybrid functions */
#define fabs(x)   __PRIVATE_TGCF1(x, fabsf, fabs, fabsl, cabsf, cabs, cabsl)
#define exp(x)    __PRIVATE_TGCF1(x, expf, exp, expl, cexpf, cexp, cexpl)
#define log(x)    __PRIVATE_TGCF1(x, logf, log, logl, clogf, clog, clogl)
#define pow(x, y) __PRIVATE_TGCF2(x, y, powf, pow, powl, cpowf, cpow, cpowl)
#define sqrt(x)   __PRIVATE_TGCF1(x, sqrtf, sqrt, sqrtl, csqrtf, csqrt, csqrtl)
#define sin(x)    __PRIVATE_TGCF1(x, sinf, sin, sinl, csinf, csin, csinl)
#define cos(x)    __PRIVATE_TGCF1(x, cosf, cos, cosl, ccosf, ccos, ccosl)
#define tan(x)    __PRIVATE_TGCF1(x, tanf, tan, tanl, ctanf, ctan, ctanl)
#define asin(x)   __PRIVATE_TGCF1(x, asinf, asin, asinl, casinf, casin, casinl)
#define acos(x)   __PRIVATE_TGCF1(x, acosf, acos, acosl, cacosf, cacos, cacosl)
#define atan(x)   __PRIVATE_TGCF1(x, atanf, atan, atanl, catanf, catan, catanl)
#define sinh(x)   __PRIVATE_TGCF1(x, sinhf, sinh, sinhl, csinhf, csinh, csinhl)
#define cosh(x)   __PRIVATE_TGCF1(x, coshf, cosh, coshl, ccoshf, ccosh, ccoshl)
#define tanh(x)   __PRIVATE_TGCF1(x, tanhf, tanh, tanhl, ctanhf, ctanh, ctanhl)
#define asinh(x)  __PRIVATE_TGCF1(x, asinhf, asinh, asinhl, casinhf, casinh, casinhl)
#define acosh(x)  __PRIVATE_TGCF1(x, acoshf, acosh, acoshl, cacoshf, cacosh, cacoshl)
#define atanh(x)  __PRIVATE_TGCF1(x, atanhf, atanh, atanhl, catanhf, catanh, catanhl)
#else /* _Complex_I */
/* Complex/non-complex hybrid functions */
#define fabs(x)   __PRIVATE_TGF1(x, fabsf, fabs, fabsl)
#define exp(x)    __PRIVATE_TGF1(x, expf, exp, expl)
#define log(x)    __PRIVATE_TGF1(x, logf, log, logl)
#define pow(x, y) __PRIVATE_TGF2(x, y, powf, pow, powl)
#define sqrt(x)   __PRIVATE_TGF1(x, sqrtf, sqrt, sqrtl)
#define sin(x)    __PRIVATE_TGF1(x, sinf, sin, sinl)
#define cos(x)    __PRIVATE_TGF1(x, cosf, cos, cosl)
#define tan(x)    __PRIVATE_TGF1(x, tanf, tan, tanl)
#define asin(x)   __PRIVATE_TGF1(x, asinf, asin, asinl)
#define acos(x)   __PRIVATE_TGF1(x, acosf, acos, acosl)
#define atan(x)   __PRIVATE_TGF1(x, atanf, atan, atanl)
#define sinh(x)   __PRIVATE_TGF1(x, sinhf, sinh, sinhl)
#define cosh(x)   __PRIVATE_TGF1(x, coshf, cosh, coshl)
#define tanh(x)   __PRIVATE_TGF1(x, tanhf, tanh, tanhl)
#define asinh(x)  __PRIVATE_TGF1(x, asinhf, asinh, asinhl)
#define acosh(x)  __PRIVATE_TGF1(x, acoshf, acosh, acoshl)
#define atanh(x)  __PRIVATE_TGF1(x, atanhf, atanh, atanhl)
#endif /* !_Complex_I */

/* Pure, non-complex functions */
#define atan2(y, x)         __PRIVATE_TGF2(y, x, atan2f, atan2, atan2l)
#define cbrt(x)             __PRIVATE_TGF1(x, cbrtf, cbrt, cbrtl)
#define ceil(x)             __PRIVATE_TGF1(x, ceilf, ceil, ceill)
#define copysign(num, sign) __PRIVATE_TGF2(num, sign, copysignf, copysign, copysignl)
#define erf(x)              __PRIVATE_TGF1(x, erff, erf, erfl)
#define erfc(x)             __PRIVATE_TGF1(x, erfcf, erfc, erfcl)
#define exp2(x)             __PRIVATE_TGF1(x, exp2f, exp2, exp2l)
#define expm1(x)            __PRIVATE_TGF1(x, expm1f, expm1, expm1l)
#define fdim(x, y)          __PRIVATE_TGF2(x, y, fdimf, fdim, fdiml)
#define floor(x)            __PRIVATE_TGF1(x, floorf, floor, floorl)
#define fma(x, y, z)        __PRIVATE_TGF3(x, y, z, fmaf, fma, fmal)
#define fmax(x, y)          __PRIVATE_TGF2(x, y, fmaxf, fmax, fmaxl)
#define fmin(x, y)          __PRIVATE_TGF2(x, y, fminf, fmin, fminl)
#define fmod(x, y)          __PRIVATE_TGF2(x, y, fmodf, fmod, fmodl)
#define frexp(x)            __PRIVATE_TGF1(x, frexpf, frexp, frexpl)
#define hypot(x, y)         __PRIVATE_TGF2(x, y, hypotf, hypot, hypotl)
#define ilogb(x)            __PRIVATE_TGF1i(x, ilogbf, ilogb, ilogbl)
#define ldexp(x)            __PRIVATE_TGF1(x, ldexpf, ldexp, ldexpl)
#define lgamma(x)           __PRIVATE_TGF1(x, lgammaf, lgamma, lgammal)
#define llrint(x)           __PRIVATE_TGF1i(x, llrintf, llrint, llrintl)
#define llround(x)          __PRIVATE_TGF1i(x, llroundf, llround, llroundl)
#define log10(x)            __PRIVATE_TGF1(x, log10f, log10, log10l)
#define log1p(x)            __PRIVATE_TGF1(x, log1pf, log1p, log1pl)
#define log2(x)             __PRIVATE_TGF1(x, log2f, log2, log2l)
#define logb(x)             __PRIVATE_TGF1(x, logbf, logb, logbl)
#define lrint(x)            __PRIVATE_TGF1i(x, lrintf, lrint, lrintl)
#define lround(x)           __PRIVATE_TGF1i(x, lroundf, lround, lroundl)
#define nearbyint(x)        __PRIVATE_TGF1(x, nearbyintf, nearbyint, nearbyintl)
#define nextafter(x, y)     __PRIVATE_TGF2(x, y, nextafterf, nextafter, nextafterl)
#define nexttoward(x, y)    __PRIVATE_TGF2(x, y, nexttowardf, nexttoward, nexttowardl)
#define remainder(x, y)     __PRIVATE_TGF2(x, y, remainderf, remainder, remainderl)
#define remquo(x, y, pquo)  __PRIVATE_TGF2x(x, y, pquo, remquof, remquo, remquol)
#define rint(x)             __PRIVATE_TGF1(x, rintf, rint, rintl)
#define round(x)            __PRIVATE_TGF1(x, roundf, round, roundl)
#define scalbln(x, y)       __PRIVATE_TGF2x(x, y, scalblnf, scalbln, scalblnl)
#define scalbn(x, y)        __PRIVATE_TGF2x(x, y, scalbnf, scalbn, scalbnl)
#define tgamma(x)           __PRIVATE_TGF1(x, tgammaf, tgamma, tgammal)
#define trunc(x)            __PRIVATE_TGF1(x, truncf, trunc, truncl)

#if defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__)
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#define nextdown(x)               __PRIVATE_TGF1(x, nextdownf, nextdown, nextdownl)
#define nextup(x)                 __PRIVATE_TGF1(x, nextupf, nextup, nextupl)
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#define roundeven(x)              __PRIVATE_TGF1(x, roundevenf, roundeven, roundevenl)
#define llogb(x)                  __PRIVATE_TGF1i(x, llogbf, llogb, llogbl)
#define fmaxmag(x, y)             __PRIVATE_TGF2(x, y, fmaxmagf, fmaxmag, fmaxmagl)
#define fminmag(x, y)             __PRIVATE_TGF2(x, y, fminmagf, fminmag, fminmagl)
#define fromfp(x, round, width)   __PRIVATE_TGF3xxi(x, round, width, fromfpf, fromfp, fromfpl)
#define ufromfp(x, round, width)  __PRIVATE_TGF3xxi(x, round, width, ufromfpf, ufromfp, ufromfpl)
#define fromfpx(x, round, width)  __PRIVATE_TGF3xxi(x, round, width, fromfpxf, fromfpx, fromfpxl)
#define ufromfpx(x, round, width) __PRIVATE_TGF3xxi(x, round, width, ufromfpxf, ufromfpx, ufromfpxl)

#define __PRIVATE_TGdlF2(x, y, math, mathl)        \
	(__PRIVATE_TG_ISTYPE2(x, y, __LONGDOUBLE)      \
	 ? mathl((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)) \
	 : math((double)(x), (double)(y)))
#define fadd(x, y) __PRIVATE_TGdlF2(x, y, fadd, faddl)
#define dadd(x, y) daddl(x, y)
#define fdiv(x, y) __PRIVATE_TGdlF2(x, y, fdiv, fdivl)
#define ddiv(x, y) ddivl(x, y)
#define fmul(x, y) __PRIVATE_TGdlF2(x, y, fmul, fmull)
#define dmul(x, y) dmull(x, y)
#define fsub(x, y) __PRIVATE_TGdlF2(x, y, fsub, fsubl)
#define dsub(x, y) dsubl(x, y)
#endif /* __USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__ */

#endif /* !__cplusplus */

#endif /* !_TGMATH_H */
