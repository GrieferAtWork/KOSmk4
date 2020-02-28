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
//[[[end]]]

#endif /* !_LIBM_ASM_FABS_H */
