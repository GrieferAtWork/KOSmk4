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
#ifndef _LIBM_ASM_BUILTIN_H
#define _LIBM_ASM_BUILTIN_H 1

#include <ieee754.h>
#include <libm/asm/_builtin.h>

/*[[[deemon
local functions = {
	"fabs",
	"nan",
	"inf",
};

function mapBuiltinDefaultEx(prefix, name, suffix, typ) {
	local uName = (name + suffix).upper();
	print("#if defined(__LIBM_HAVE_BUILTIN_ASM_", uName, ") && __has_builtin(__builtin_", name, suffix, ")");
	print("#if !defined(", prefix, name, ") && defined(__IEEE754_DOUBLE_TYPE_IS_", typ, "__)");
	print("#define ", prefix, name, " __builtin_", name, suffix);
	print("#endif /" "* !", prefix, name, " && __IEEE754_DOUBLE_TYPE_IS_", typ, "__ *" "/");
	print("#if !defined(", prefix, name, "f) && defined(__IEEE754_FLOAT_TYPE_IS_", typ, "__)");
	print("#define ", prefix, name, "f __builtin_", name, suffix);
	print("#endif /" "* !", prefix, name, "f && __IEEE754_FLOAT_TYPE_IS_", typ, "__ *" "/");
	print("#if !defined(", prefix, name, "l) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_", typ, "__)");
	print("#define ", prefix, name, "l __builtin_", name, suffix);
	print("#endif /" "* !", prefix, name, "l && __IEEE854_LONG_DOUBLE_TYPE_IS_", typ, "__ *" "/");
	print("#endif /" "* __LIBM_HAVE_BUILTIN_ASM_", uName, " && __has_builtin(__builtin_", name, suffix, ") *" "/");
	print("");
}
function mapBuiltinDefault(name) {
	mapBuiltinDefaultEx("__ieee754_", name, "", "DOUBLE");
	mapBuiltinDefaultEx("__ieee754_", name, "f", "FLOAT");
	mapBuiltinDefaultEx("__ieee854_", name, "l", "LONG_DOUBLE");
}
for (local n: functions)
	mapBuiltinDefault(n);
]]]*/
#if defined(__LIBM_HAVE_BUILTIN_ASM_FABS) && __has_builtin(__builtin_fabs)
#if !defined(__ieee754_fabs) && defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__)
#define __ieee754_fabs __builtin_fabs
#endif /* !__ieee754_fabs && __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
#if !defined(__ieee754_fabsf) && defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#define __ieee754_fabsf __builtin_fabs
#endif /* !__ieee754_fabsf && __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#if !defined(__ieee754_fabsl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __ieee754_fabsl __builtin_fabs
#endif /* !__ieee754_fabsl && __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_FABS && __has_builtin(__builtin_fabs) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_FABSF) && __has_builtin(__builtin_fabsf)
#if !defined(__ieee754_fabs) && defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee754_fabs __builtin_fabsf
#endif /* !__ieee754_fabs && __IEEE754_DOUBLE_TYPE_IS_FLOAT__ */
#if !defined(__ieee754_fabsf) && defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
#define __ieee754_fabsf __builtin_fabsf
#endif /* !__ieee754_fabsf && __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
#if !defined(__ieee754_fabsl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee754_fabsl __builtin_fabsf
#endif /* !__ieee754_fabsl && __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_FABSF && __has_builtin(__builtin_fabsf) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_FABSL) && __has_builtin(__builtin_fabsl)
#if !defined(__ieee854_fabs) && defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_fabs __builtin_fabsl
#endif /* !__ieee854_fabs && __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee854_fabsf) && defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_fabsf __builtin_fabsl
#endif /* !__ieee854_fabsf && __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee854_fabsl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_fabsl __builtin_fabsl
#endif /* !__ieee854_fabsl && __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_FABSL && __has_builtin(__builtin_fabsl) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_NAN) && __has_builtin(__builtin_nan)
#if !defined(__ieee754_nan) && defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__)
#define __ieee754_nan __builtin_nan
#endif /* !__ieee754_nan && __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
#if !defined(__ieee754_nanf) && defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#define __ieee754_nanf __builtin_nan
#endif /* !__ieee754_nanf && __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#if !defined(__ieee754_nanl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __ieee754_nanl __builtin_nan
#endif /* !__ieee754_nanl && __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_NAN && __has_builtin(__builtin_nan) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_NANF) && __has_builtin(__builtin_nanf)
#if !defined(__ieee754_nan) && defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee754_nan __builtin_nanf
#endif /* !__ieee754_nan && __IEEE754_DOUBLE_TYPE_IS_FLOAT__ */
#if !defined(__ieee754_nanf) && defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
#define __ieee754_nanf __builtin_nanf
#endif /* !__ieee754_nanf && __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
#if !defined(__ieee754_nanl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee754_nanl __builtin_nanf
#endif /* !__ieee754_nanl && __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_NANF && __has_builtin(__builtin_nanf) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_NANL) && __has_builtin(__builtin_nanl)
#if !defined(__ieee854_nan) && defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_nan __builtin_nanl
#endif /* !__ieee854_nan && __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee854_nanf) && defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_nanf __builtin_nanl
#endif /* !__ieee854_nanf && __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee854_nanl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_nanl __builtin_nanl
#endif /* !__ieee854_nanl && __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_NANL && __has_builtin(__builtin_nanl) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_INF) && __has_builtin(__builtin_inf)
#if !defined(__ieee754_inf) && defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__)
#define __ieee754_inf __builtin_inf
#endif /* !__ieee754_inf && __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
#if !defined(__ieee754_inff) && defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#define __ieee754_inff __builtin_inf
#endif /* !__ieee754_inff && __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#if !defined(__ieee754_infl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __ieee754_infl __builtin_inf
#endif /* !__ieee754_infl && __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_INF && __has_builtin(__builtin_inf) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_INFF) && __has_builtin(__builtin_inff)
#if !defined(__ieee754_inf) && defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee754_inf __builtin_inff
#endif /* !__ieee754_inf && __IEEE754_DOUBLE_TYPE_IS_FLOAT__ */
#if !defined(__ieee754_inff) && defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
#define __ieee754_inff __builtin_inff
#endif /* !__ieee754_inff && __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
#if !defined(__ieee754_infl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee754_infl __builtin_inff
#endif /* !__ieee754_infl && __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_INFF && __has_builtin(__builtin_inff) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_INFL) && __has_builtin(__builtin_infl)
#if !defined(__ieee854_inf) && defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_inf __builtin_infl
#endif /* !__ieee854_inf && __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee854_inff) && defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_inff __builtin_infl
#endif /* !__ieee854_inff && __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee854_infl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_infl __builtin_infl
#endif /* !__ieee854_infl && __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_INFL && __has_builtin(__builtin_infl) */
//[[[end]]]

#endif /* !_LIBM_ASM_FABS_H */
