/* HASH CRC-32:0xf94476ce */
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
#ifndef __local_scalbl_defined
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__CRT_HAVE_scalb) || defined(__CRT_HAVE___scalb) || defined(__CRT_HAVE__scalb)
#define __local_scalbl_defined 1
/* Dependency: "scalb" from "math" */
#ifndef ____localdep_scalb_defined
#define ____localdep_scalb_defined 1
#if __has_builtin(__builtin_scalb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalb)
/* Return X times (2 to the Nth power) */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_scalb)(double __x, double __fn) { return __builtin_scalb(__x, __fn); }
#elif defined(__CRT_HAVE_scalb)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalb,(double __x, double __fn),scalb,(__x,__fn))
#elif defined(__CRT_HAVE___scalb)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalb,(double __x, double __fn),__scalb,(__x,__fn))
#elif defined(__CRT_HAVE__scalb)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalb,(double __x, double __fn),_scalb,(__x,__fn))
#else /* LIBC: scalb */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#include <local/math/scalb.h>
/* Return X times (2 to the Nth power) */
#define __localdep_scalb (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalb))
#else /* CUSTOM: scalb */
#undef ____localdep_scalb_defined
#endif /* scalb... */
#endif /* scalb... */
#endif /* !____localdep_scalb_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return X times (2 to the Nth power) */
__LOCAL_LIBC(scalbl) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(scalbl))(__LONGDOUBLE __x,
                                                __LONGDOUBLE __n) {
#line 2228 "kos/src/libc/magic/math.c"
	return (__LONGDOUBLE)__localdep_scalb((double)__x, (double)__n);
}
__NAMESPACE_LOCAL_END
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __CRT_HAVE_scalb || __CRT_HAVE___scalb || __CRT_HAVE__scalb */
#endif /* !__local_scalbl_defined */
