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
__LIBM_LOCAL_FUNC(isunorderedf) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isunorderedf)(__IEEE754_FLOAT_TYPE__ __u,
                                    __IEEE754_FLOAT_TYPE__ __v) {
	return __ieee754_isnanf(__u) || __ieee754_isnanf(__v);
}
#endif /* !__ieee754_isunorderedf */
#ifndef __ieee754_isgreaterf
__LIBM_LOCAL_FUNC(isgreaterf) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isgreaterf)(__IEEE754_FLOAT_TYPE__ __x,
                                  __IEEE754_FLOAT_TYPE__ __y) {
	return !__ieee754_isunorderedf(__x, __y) && __x > __y;
}
#endif /* !__ieee754_isgreaterf */
#ifndef __ieee754_isgreaterequalf
__LIBM_LOCAL_FUNC(isgreaterequalf) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isgreaterequalf)(__IEEE754_FLOAT_TYPE__ __x,
                                       __IEEE754_FLOAT_TYPE__ __y) {
	return !__ieee754_isunorderedf(__x, __y) && __x >= __y;
}
#endif /* !__ieee754_isgreaterequalf */
#ifndef __ieee754_islessf
__LIBM_LOCAL_FUNC(islessf) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_islessf)(__IEEE754_FLOAT_TYPE__ __x,
                               __IEEE754_FLOAT_TYPE__ __y) {
	return !__ieee754_isunorderedf(__x, __y) && __x < __y;
}
#endif /* !__ieee754_islessf */
#ifndef __ieee754_islessequalf
__LIBM_LOCAL_FUNC(islessequalf) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_islessequalf)(__IEEE754_FLOAT_TYPE__ __x,
                                    __IEEE754_FLOAT_TYPE__ __y) {
	return !__ieee754_isunorderedf(__x, __y) && __x <= __y;
}
#endif /* !__ieee754_islessequalf */
#ifndef __ieee754_islessgreaterf
__LIBM_LOCAL_FUNC(islessgreaterf) __ATTR_WUNUSED __ATTR_CONST __BOOL
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
__LIBM_LOCAL_FUNC(isunordered) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isunordered)(__IEEE754_DOUBLE_TYPE__ __u,
                                   __IEEE754_DOUBLE_TYPE__ __v) {
	return __ieee754_isnan(__u) || __ieee754_isnan(__v);
}
#endif /* !__ieee754_isunordered */
#ifndef __ieee754_isgreater
__LIBM_LOCAL_FUNC(isgreater) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isgreater)(__IEEE754_DOUBLE_TYPE__ __x,
                                 __IEEE754_DOUBLE_TYPE__ __y) {
	return !__ieee754_isunordered(__x, __y) && __x > __y;
}
#endif /* !__ieee754_isgreater */
#ifndef __ieee754_isgreaterequal
__LIBM_LOCAL_FUNC(isgreaterequal) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isgreaterequal)(__IEEE754_DOUBLE_TYPE__ __x,
                                      __IEEE754_DOUBLE_TYPE__ __y) {
	return !__ieee754_isunordered(__x, __y) && __x >= __y;
}
#endif /* !__ieee754_isgreaterequal */
#ifndef __ieee754_isless
__LIBM_LOCAL_FUNC(isless) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_isless)(__IEEE754_DOUBLE_TYPE__ __x,
                              __IEEE754_DOUBLE_TYPE__ __y) {
	return !__ieee754_isunordered(__x, __y) && __x < __y;
}
#endif /* !__ieee754_isless */
#ifndef __ieee754_islessequal
__LIBM_LOCAL_FUNC(islessequal) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee754_islessequal)(__IEEE754_DOUBLE_TYPE__ __x,
                                   __IEEE754_DOUBLE_TYPE__ __y) {
	return !__ieee754_isunordered(__x, __y) && __x <= __y;
}
#endif /* !__ieee754_islessequal */
#ifndef __ieee754_islessgreater
__LIBM_LOCAL_FUNC(islessgreater) __ATTR_WUNUSED __ATTR_CONST __BOOL
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
__LIBM_LOCAL_FUNC(isunorderedl) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_isunorderedl)(__IEEE854_LONG_DOUBLE_TYPE__ __u,
                                    __IEEE854_LONG_DOUBLE_TYPE__ __v) {
	return __ieee854_isnanl(__u) || __ieee854_isnanl(__v);
}
#endif /* !__ieee854_isunorderedl */
#ifndef __ieee854_isgreaterl
__LIBM_LOCAL_FUNC(isgreaterl) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_isgreaterl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                  __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedl(__x, __y) && __x > __y;
}
#endif /* !__ieee854_isgreaterl */
#ifndef __ieee854_isgreaterequall
__LIBM_LOCAL_FUNC(isgreaterequall) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_isgreaterequall)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                       __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedl(__x, __y) && __x >= __y;
}
#endif /* !__ieee854_isgreaterequall */
#ifndef __ieee854_islessl
__LIBM_LOCAL_FUNC(islessl) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_islessl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                               __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedl(__x, __y) && __x < __y;
}
#endif /* !__ieee854_islessl */
#ifndef __ieee854_islessequall
__LIBM_LOCAL_FUNC(islessequall) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_islessequall)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                    __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedl(__x, __y) && __x <= __y;
}
#endif /* !__ieee854_islessequall */
#ifndef __ieee854_islessgreaterl
__LIBM_LOCAL_FUNC(islessgreaterl) __ATTR_WUNUSED __ATTR_CONST __BOOL
(__LIBCCALL __ieee854_islessgreaterl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                      __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	return !__ieee854_isunorderedl(__x, __y) && (__x < __y || __y < __x);
}
#endif /* !__ieee854_islessgreaterl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_FCOMP_H */
