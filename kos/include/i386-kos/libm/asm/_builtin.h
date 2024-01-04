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
#ifndef _I386_KOS_LIBM_ASM__BUILTIN_H
#define _I386_KOS_LIBM_ASM__BUILTIN_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include "../../../libm/asm/_builtin.h"

/* Define these macros if  the respective compiler builtin  function
 * both exists, and never generates code containing calls to library
 * functions.
 * When individual macros are defined, compiler intrinsics are used
 * to implement library functions, rather than much slower explicit
 * implementations. */


#ifndef __SSE__
#undef __LIBM_HAVE_BUILTIN_ASM_FABS
#undef __LIBM_HAVE_BUILTIN_ASM_FABSF
#endif /* !__SSE__ */
#undef __LIBM_HAVE_BUILTIN_ASM_FABSL


#endif /* !_I386_KOS_LIBM_ASM__BUILTIN_H */
