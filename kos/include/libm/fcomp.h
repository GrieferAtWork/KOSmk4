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
#ifndef _LIBM_FCOMP_H
#define _LIBM_FCOMP_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/asm/fcomp.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_isunorderedf
__DECL_END
#include <libm/isnan.h>
__DECL_BEGIN
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isunorderedf)(__IEEE754_FLOAT_TYPE__ __u,
                                    __IEEE754_FLOAT_TYPE__ __v) {
	return __ieee754_isnanf(__u) || __ieee754_isnanf(__v);
}
#endif /* !__ieee754_isunorderedf */
#ifndef __ieee754_isgreaterf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isgreaterf)(__IEEE754_FLOAT_TYPE__ __x,
                                  __IEEE754_FLOAT_TYPE__ __y) {
	return !__ieee754_isunorderedf(__x, __y) && __x > __y;
}
#endif /* !__ieee754_isgreaterf */
#ifndef __ieee754_isgreaterequalf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isgreaterequalf)(__IEEE754_FLOAT_TYPE__ __x,
                                       __IEEE754_FLOAT_TYPE__ __y) {
	return !__ieee754_isunorderedf(__x, __y) && __x >= __y;
}
#endif /* !__ieee754_isgreaterequalf */
#ifndef __ieee754_islessf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_islessf)(__IEEE754_FLOAT_TYPE__ __x,
                               __IEEE754_FLOAT_TYPE__ __y) {
	return !__ieee754_isunorderedf(__x, __y) && __x < __y;
}
#endif /* !__ieee754_islessf */
#ifndef __ieee754_islessequalf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_islessequalf)(__IEEE754_FLOAT_TYPE__ __x,
                                    __IEEE754_FLOAT_TYPE__ __y) {
	return !__ieee754_isunorderedf(__x, __y) && __x <= __y;
}
#endif /* !__ieee754_islessequalf */
#ifndef __ieee754_islessgreaterf
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_islessgreaterf)(__IEEE754_FLOAT_TYPE__ __x,
                                      __IEEE754_FLOAT_TYPE__ __y) {
	return !__ieee754_isunorderedf(__x, __y) && (__x < __y || __y < __x);
}
#endif /* !__ieee754_islessgreaterf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_isunordered
__DECL_END
#include <libm/isnan.h>
__DECL_BEGIN
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isunordered)(__IEEE754_DOUBLE_TYPE__ __u,
                                   __IEEE754_DOUBLE_TYPE__ __v) {
	return __ieee754_isnan(__u) || __ieee754_isnan(__v);
}
#endif /* !__ieee754_isunordered */
#ifndef __ieee754_isgreater
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isgreater)(__IEEE754_DOUBLE_TYPE__ __x,
                                 __IEEE754_DOUBLE_TYPE__ __y) {
	return !__ieee754_isunordered(__x, __y) && __x > __y;
}
#endif /* !__ieee754_isgreater */
#ifndef __ieee754_isgreaterequal
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isgreaterequal)(__IEEE754_DOUBLE_TYPE__ __x,
                                      __IEEE754_DOUBLE_TYPE__ __y) {
	return !__ieee754_isunordered(__x, __y) && __x >= __y;
}
#endif /* !__ieee754_isgreaterequal */
#ifndef __ieee754_isless
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isless)(__IEEE754_DOUBLE_TYPE__ __x,
                              __IEEE754_DOUBLE_TYPE__ __y) {
	return !__ieee754_isunordered(__x, __y) && __x < __y;
}
#endif /* !__ieee754_isless */
#ifndef __ieee754_islessequal
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_islessequal)(__IEEE754_DOUBLE_TYPE__ __x,
                                   __IEEE754_DOUBLE_TYPE__ __y) {
	return !__ieee754_isunordered(__x, __y) && __x <= __y;
}
#endif /* !__ieee754_islessequal */
#ifndef __ieee754_islessgreater
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_islessgreater)(__IEEE754_DOUBLE_TYPE__ __x,
                                     __IEEE754_DOUBLE_TYPE__ __y) {
	return !__ieee754_isunordered(__x, __y) && (__x < __y || __y < __x);
}
#endif /* !__ieee754_islessgreater */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_isunorderedl
__DECL_END
#include <libm/isnan.h>
__DECL_BEGIN
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_isunorderedl)(__IEEE854_LONG_DOUBLE_TYPE__ __u,
                                    __IEEE854_LONG_DOUBLE_TYPE__ __v) {
	return __ieee854_isnanf(__u) || __ieee854_isnanf(__v);
}
#endif /* !__ieee854_isunorderedl */
#ifndef __ieee854_isgreaterl
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_isgreaterl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                  __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedf(__x, __y) && __x > __y;
}
#endif /* !__ieee854_isgreaterl */
#ifndef __ieee854_isgreaterequall
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_isgreaterequall)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                       __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedf(__x, __y) && __x >= __y;
}
#endif /* !__ieee854_isgreaterequall */
#ifndef __ieee854_islessl
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_islessl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                               __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedf(__x, __y) && __x < __y;
}
#endif /* !__ieee854_islessl */
#ifndef __ieee854_islessequall
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_islessequall)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                    __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedf(__x, __y) && __x <= __y;
}
#endif /* !__ieee854_islessequall */
#ifndef __ieee854_islessgreaterl
__LOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_islessgreaterl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                      __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedf(__x, __y) && (__x < __y || __y < __x);
}
#endif /* !__ieee854_islessgreaterl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_FCOMP_H */
