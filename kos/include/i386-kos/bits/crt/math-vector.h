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
#ifndef _I386_KOS_BITS_CRT_MATH_VECTOR_H
#define _I386_KOS_BITS_CRT_MATH_VECTOR_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

#if defined(__x86_64__) && defined(__FAST_MATH__)
#if defined(_OPENMP) && _OPENMP >= 201307
#define __DECL_SIMD_x86_64 _Pragma("omp declare simd notinbranch")
#elif defined(__GNUC__) && __GCC_VERSION_NUM >= 60000
#define __DECL_SIMD_x86_64 __attribute__((__simd__("notinbranch")))
#endif
#ifdef __DECL_SIMD_x86_64
#define __DECL_SIMD_cos     __DECL_SIMD_x86_64
#define __DECL_SIMD_cosf    __DECL_SIMD_x86_64
#define __DECL_SIMD_sin     __DECL_SIMD_x86_64
#define __DECL_SIMD_sinf    __DECL_SIMD_x86_64
#define __DECL_SIMD_sincos  __DECL_SIMD_x86_64
#define __DECL_SIMD_sincosf __DECL_SIMD_x86_64
#define __DECL_SIMD_log     __DECL_SIMD_x86_64
#define __DECL_SIMD_logf    __DECL_SIMD_x86_64
#define __DECL_SIMD_exp     __DECL_SIMD_x86_64
#define __DECL_SIMD_expf    __DECL_SIMD_x86_64
#define __DECL_SIMD_pow     __DECL_SIMD_x86_64
#define __DECL_SIMD_powf    __DECL_SIMD_x86_64
#endif /* __DECL_SIMD_x86_64 */
#endif /* __x86_64__ && __FAST_MATH__ */

#include "../../../bits/crt/math-vector.h"

#endif /* !_I386_KOS_BITS_CRT_MATH_VECTOR_H */
