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
/*!replace_with_include <fenv.h>*/
#ifndef _BITS_CRT_FENV_H
#define _BITS_CRT_FENV_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#define __fexcept_t __UINTPTR_TYPE__
#define __femode_t  __UINTPTR_TYPE__

struct __fenv_struct {
	__UINTPTR_TYPE__ __opaque[64];
};

__DECL_END
#endif /* __CC__ */

#define __FE_DFL_ENV    (__CCAST(struct __fenv_struct const *)-1) /* If the default argument is used we use this value. */
#define __FE_NOMASK_ENV (__CCAST(struct __fenv_struct const *)-2) /* Floating-point environment where none of the exception is masked. */
#define __FE_DFL_MODE   ((__femode_t const *)-1)

#endif /* !_BITS_CRT_FENV_H */
