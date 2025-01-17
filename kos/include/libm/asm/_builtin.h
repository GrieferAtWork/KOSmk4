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
#ifndef _LIBM_ASM__BUILTIN_H
#define _LIBM_ASM__BUILTIN_H 1

#include <__stdinc.h>

/* Define these macros if  the respective compiler builtin  function
 * both exists, and never generates code containing calls to library
 * functions.
 * When individual macros are defined, compiler intrinsics are used
 * to implement library functions, rather than much slower explicit
 * implementations.
 * Optionally, macros may not be defined if more (or equally) efficient
 * inline assembly variants are available as well. */


/* NOTE: Many of these builtins probably also worked this way before 9.1.0,
 *       however that's the version for  which I've checked the GCC  source
 *       to find those functions to which the above conditions apply. */
#if !defined(__CHECKER__) && defined(__GNUC__) && __GCC_VERSION_NUM >= 90100
#define __LIBM_HAVE_BUILTIN_ASM_FABS           1
#define __LIBM_HAVE_BUILTIN_ASM_FABSF          1
#define __LIBM_HAVE_BUILTIN_ASM_FABSL          1
#define __LIBM_HAVE_BUILTIN_ASM_INF            1
#define __LIBM_HAVE_BUILTIN_ASM_INFF           1
#define __LIBM_HAVE_BUILTIN_ASM_INFL           1
#define __LIBM_HAVE_BUILTIN_ASM_ISUNORDERED    1
#define __LIBM_HAVE_BUILTIN_ASM_ISGREATER      1
#define __LIBM_HAVE_BUILTIN_ASM_ISGREATEREQUAL 1
#define __LIBM_HAVE_BUILTIN_ASM_ISLESS         1
#define __LIBM_HAVE_BUILTIN_ASM_ISLESSEQUAL    1
#define __LIBM_HAVE_BUILTIN_ASM_ISLESSGREATER  1
#endif /* __GNUC__ ... */

#endif /* !_LIBM_ASM__BUILTIN_H */
