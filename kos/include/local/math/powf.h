/* HASH CRC-32:0x2982db14 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_powf_defined
#if defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow)
#define __local_powf_defined 1
#include <bits/math-vector.h>
#include <bits/math-vector.h>
/* Dependency: "pow" */
#ifndef ____localdep_pow_defined
#define ____localdep_pow_defined 1
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__FORCELOCAL __DECL_SIMD_pow __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_pow)(double __x, double __y) { return __builtin_pow(__x, __y); }
#elif defined(__CRT_HAVE_pow)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,(__x,__y))
#elif defined(__CRT_HAVE___pow)
/* Return X to the Y power */
__CREDIRECT(__DECL_SIMD_pow __ATTR_WUNUSED,double,__NOTHROW,__localdep_pow,(double __x, double __y),__pow,(__x,__y))
#else /* LIBC: pow */
#undef ____localdep_pow_defined
#endif /* pow... */
#endif /* !____localdep_pow_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return X to the Y power */
__LOCAL_LIBC(powf) __DECL_SIMD_powf __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(powf))(float __x,
                                              float __y) {
#line 312 "kos/src/libc/magic/math.c"
	return (float)__localdep_pow((double)__x, (double)__y);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) */
#endif /* !__local_powf_defined */
