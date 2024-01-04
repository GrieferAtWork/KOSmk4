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
#ifndef _LIBM_ASM_BUILTIN_H
#define _LIBM_ASM_BUILTIN_H 1

#include <ieee754.h>
#include <libm/asm/_builtin.h>

/*[[[deemon
local functions = {
	"fabs",
	"inf",
};

function mapBuiltinDefaultEx(name, suffix, typ) {
	local uName = (name + suffix).upper();
	print("#if defined(__LIBM_HAVE_BUILTIN_ASM_", uName, ") && __has_builtin(__builtin_", name, suffix, ")");
	print("#if !defined(__ieee754_", name, ") && defined(__IEEE754_DOUBLE_TYPE_IS_", typ, "__)");
	print("#define __ieee754_", name, " __builtin_", name, suffix);
	print("#endif /" "* !__ieee754_", name, " && __IEEE754_DOUBLE_TYPE_IS_", typ, "__ *" "/");
	print("#if !defined(__ieee754_", name, "f) && defined(__IEEE754_FLOAT_TYPE_IS_", typ, "__)");
	print("#define __ieee754_", name, "f __builtin_", name, suffix);
	print("#endif /" "* !__ieee754_", name, "f && __IEEE754_FLOAT_TYPE_IS_", typ, "__ *" "/");
	print("#if !defined(__ieee854_", name, "l) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_", typ, "__)");
	print("#define __ieee854_", name, "l __builtin_", name, suffix);
	print("#endif /" "* !__ieee854_", name, "l && __IEEE854_LONG_DOUBLE_TYPE_IS_", typ, "__ *" "/");
	print("#endif /" "* __LIBM_HAVE_BUILTIN_ASM_", uName, " && __has_builtin(__builtin_", name, suffix, ") *" "/");
	print("");
}
function mapBuiltinDefault(name) {
	mapBuiltinDefaultEx(name, "", "DOUBLE");
	mapBuiltinDefaultEx(name, "f", "FLOAT");
	mapBuiltinDefaultEx(name, "l", "LONG_DOUBLE");
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
#if !defined(__ieee854_fabsl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __ieee854_fabsl __builtin_fabs
#endif /* !__ieee854_fabsl && __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_FABS && __has_builtin(__builtin_fabs) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_FABSF) && __has_builtin(__builtin_fabsf)
#if !defined(__ieee754_fabs) && defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee754_fabs __builtin_fabsf
#endif /* !__ieee754_fabs && __IEEE754_DOUBLE_TYPE_IS_FLOAT__ */
#if !defined(__ieee754_fabsf) && defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
#define __ieee754_fabsf __builtin_fabsf
#endif /* !__ieee754_fabsf && __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
#if !defined(__ieee854_fabsl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee854_fabsl __builtin_fabsf
#endif /* !__ieee854_fabsl && __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_FABSF && __has_builtin(__builtin_fabsf) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_FABSL) && __has_builtin(__builtin_fabsl)
#if !defined(__ieee754_fabs) && defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee754_fabs __builtin_fabsl
#endif /* !__ieee754_fabs && __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee754_fabsf) && defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
#define __ieee754_fabsf __builtin_fabsl
#endif /* !__ieee754_fabsf && __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee854_fabsl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_fabsl __builtin_fabsl
#endif /* !__ieee854_fabsl && __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_FABSL && __has_builtin(__builtin_fabsl) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_INF) && __has_builtin(__builtin_inf)
#if !defined(__ieee754_inf) && defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__)
#define __ieee754_inf __builtin_inf
#endif /* !__ieee754_inf && __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ */
#if !defined(__ieee754_inff) && defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#define __ieee754_inff __builtin_inf
#endif /* !__ieee754_inff && __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#if !defined(__ieee854_infl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define __ieee854_infl __builtin_inf
#endif /* !__ieee854_infl && __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_INF && __has_builtin(__builtin_inf) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_INFF) && __has_builtin(__builtin_inff)
#if !defined(__ieee754_inf) && defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee754_inf __builtin_inff
#endif /* !__ieee754_inf && __IEEE754_DOUBLE_TYPE_IS_FLOAT__ */
#if !defined(__ieee754_inff) && defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
#define __ieee754_inff __builtin_inff
#endif /* !__ieee754_inff && __IEEE754_FLOAT_TYPE_IS_FLOAT__ */
#if !defined(__ieee854_infl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define __ieee854_infl __builtin_inff
#endif /* !__ieee854_infl && __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_INFF && __has_builtin(__builtin_inff) */

#if defined(__LIBM_HAVE_BUILTIN_ASM_INFL) && __has_builtin(__builtin_infl)
#if !defined(__ieee754_inf) && defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee754_inf __builtin_infl
#endif /* !__ieee754_inf && __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee754_inff) && defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
#define __ieee754_inff __builtin_infl
#endif /* !__ieee754_inff && __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
#if !defined(__ieee854_infl) && defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)
#define __ieee854_infl __builtin_infl
#endif /* !__ieee854_infl && __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ */
#endif /* __LIBM_HAVE_BUILTIN_ASM_INFL && __has_builtin(__builtin_infl) */
//[[[end]]]


/*[[[deemon
for (local x: {
	"isunordered",
	"isgreater",
	"isgreaterequal",
	"isless",
	"islessequal",
	"islessgreater"
}) {
	print("#ifdef __LIBM_HAVE_BUILTIN_ASM_", x.upper());
	print("#ifndef __ieee754_", x, "f");
	print("#define __ieee754_", x, "f __builtin_", x, "");
	print("#endif /" "* !__ieee754_", x, "f *" "/");
	print("#ifndef __ieee754_", x, "");
	print("#define __ieee754_", x, " __builtin_", x, "");
	print("#endif /" "* !__ieee754_", x, " *" "/");
	print("#ifndef __ieee854_", x, "l");
	print("#define __ieee854_", x, "l __builtin_", x, "");
	print("#endif /" "* !__ieee854_", x, "l *" "/");
	print("#endif /" "* __LIBM_HAVE_BUILTIN_ASM_", x.upper(), " *" "/");
}
]]]*/
#ifdef __LIBM_HAVE_BUILTIN_ASM_ISUNORDERED
#ifndef __ieee754_isunorderedf
#define __ieee754_isunorderedf __builtin_isunordered
#endif /* !__ieee754_isunorderedf */
#ifndef __ieee754_isunordered
#define __ieee754_isunordered __builtin_isunordered
#endif /* !__ieee754_isunordered */
#ifndef __ieee854_isunorderedl
#define __ieee854_isunorderedl __builtin_isunordered
#endif /* !__ieee854_isunorderedl */
#endif /* __LIBM_HAVE_BUILTIN_ASM_ISUNORDERED */
#ifdef __LIBM_HAVE_BUILTIN_ASM_ISGREATER
#ifndef __ieee754_isgreaterf
#define __ieee754_isgreaterf __builtin_isgreater
#endif /* !__ieee754_isgreaterf */
#ifndef __ieee754_isgreater
#define __ieee754_isgreater __builtin_isgreater
#endif /* !__ieee754_isgreater */
#ifndef __ieee854_isgreaterl
#define __ieee854_isgreaterl __builtin_isgreater
#endif /* !__ieee854_isgreaterl */
#endif /* __LIBM_HAVE_BUILTIN_ASM_ISGREATER */
#ifdef __LIBM_HAVE_BUILTIN_ASM_ISGREATEREQUAL
#ifndef __ieee754_isgreaterequalf
#define __ieee754_isgreaterequalf __builtin_isgreaterequal
#endif /* !__ieee754_isgreaterequalf */
#ifndef __ieee754_isgreaterequal
#define __ieee754_isgreaterequal __builtin_isgreaterequal
#endif /* !__ieee754_isgreaterequal */
#ifndef __ieee854_isgreaterequall
#define __ieee854_isgreaterequall __builtin_isgreaterequal
#endif /* !__ieee854_isgreaterequall */
#endif /* __LIBM_HAVE_BUILTIN_ASM_ISGREATEREQUAL */
#ifdef __LIBM_HAVE_BUILTIN_ASM_ISLESS
#ifndef __ieee754_islessf
#define __ieee754_islessf __builtin_isless
#endif /* !__ieee754_islessf */
#ifndef __ieee754_isless
#define __ieee754_isless __builtin_isless
#endif /* !__ieee754_isless */
#ifndef __ieee854_islessl
#define __ieee854_islessl __builtin_isless
#endif /* !__ieee854_islessl */
#endif /* __LIBM_HAVE_BUILTIN_ASM_ISLESS */
#ifdef __LIBM_HAVE_BUILTIN_ASM_ISLESSEQUAL
#ifndef __ieee754_islessequalf
#define __ieee754_islessequalf __builtin_islessequal
#endif /* !__ieee754_islessequalf */
#ifndef __ieee754_islessequal
#define __ieee754_islessequal __builtin_islessequal
#endif /* !__ieee754_islessequal */
#ifndef __ieee854_islessequall
#define __ieee854_islessequall __builtin_islessequal
#endif /* !__ieee854_islessequall */
#endif /* __LIBM_HAVE_BUILTIN_ASM_ISLESSEQUAL */
#ifdef __LIBM_HAVE_BUILTIN_ASM_ISLESSGREATER
#ifndef __ieee754_islessgreaterf
#define __ieee754_islessgreaterf __builtin_islessgreater
#endif /* !__ieee754_islessgreaterf */
#ifndef __ieee754_islessgreater
#define __ieee754_islessgreater __builtin_islessgreater
#endif /* !__ieee754_islessgreater */
#ifndef __ieee854_islessgreaterl
#define __ieee854_islessgreaterl __builtin_islessgreater
#endif /* !__ieee854_islessgreaterl */
#endif /* __LIBM_HAVE_BUILTIN_ASM_ISLESSGREATER */
//[[[end]]]


#endif /* !_LIBM_ASM_FABS_H */
