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

%(c_prefix){
/* (#) Portability: libstdc++ (/include/bits/std_abs.h) */
}
%[define_replacement(errno_t = __errno_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <stdlib.h>
)]%[insert:prefix(
#include <math.h>
)]%{

/* NOTE: This file is needed for libstdc++ compatibility.
 *
 * It needs to define any possibly missing variant of `std::abs',
 * working  together with system headers <stdlib.h> and <math.h>.
 */

#ifdef __CC__
__SYSDECL_BEGIN

}

%[insert:std]

%(std)#ifdef __cplusplus
%(std)#ifndef __CORRECT_ISO_CPP_STDLIB_H_PROTO
%[insert:std_function_nousing(abs = labs, externLinkageOverride: "C++")]
%(std)#endif /* !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
%(std)#if (!defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO) || !defined(__USE_ISOC99)) && defined(__COMPILER_HAVE_LONGLONG)
%[insert:std_function_nousing(abs = llabs, externLinkageOverride: "C++")]
%(std)#endif /* (!__CORRECT_ISO_CPP_STDLIB_H_PROTO || !__USE_ISOC99) && __COMPILER_HAVE_LONGLONG */
%(std)#if !defined(__CORRECT_ISO_CPP_MATH_H_PROTO) && !defined(__NO_FPU)
%[insert:std_function_nousing(abs = fabsf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(abs = fabs, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(abs = fabsl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
//TODO: %(std)#ifdef __COMPILER_HAVE_FLOAT128
//TODO: %(std)__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __float128 __NOTHROW(__LIBCCALL abs)(__float128 __x) { return __x < 0 ? -__x : __x; }
//TODO: %(std)#endif /* __COMPILER_HAVE_FLOAT128 */
%(std)#endif /* !__CORRECT_ISO_CPP_MATH_H_PROTO && !__NO_FPU */
%(std)#endif /* __cplusplus */


%{

__SYSDECL_END
#endif /* __CC__ */

}
