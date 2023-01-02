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
#ifndef _BITS_CRT_COMPLEX_H
#define _BITS_CRT_COMPLEX_H 1

#include <__stdinc.h>

#ifdef __CC__
#ifndef __NO_FPU
#ifdef _Complex_I
#ifdef __clang__
#define __CMPLX(x, y)  ((double _Complex){ x, y })
#define __CMPLXF(x, y) ((float _Complex){ x, y })
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __CMPLXL(x, y) ((long double _Complex){ x, y })
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#elif ((__has_builtin(__builtin_complex) ||                                                 \
        (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)))) && \
       (defined(__INTELLISENSE__)))
/* FIXME: "error : '__builtin_complex' was not declared in this scope; did you mean '__builtin_toupper'?" */
#define __CMPLX(x, y)  __builtin_complex((double)(x), (double)(y))
#define __CMPLXF(x, y) __builtin_complex((float)(x), (float)(y))
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __CMPLXL(x, y) __builtin_complex((long double)(x), (long double)(y))
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#else /* ... */
#define __CMPLX(x, y)  ((x) + (y) * _Complex_I)
#define __CMPLXF(x, y) ((x) + (y) * _Complex_I)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __CMPLXL(x, y) ((x) + (y) * _Complex_I)
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !... */
#endif /* _Complex_I */
#endif /* !__NO_FPU */
#endif /* __CC__ */

#endif /* !_BITS_CRT_COMPLEX_H */
