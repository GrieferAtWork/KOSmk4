/* HASH CRC-32:0x376a4263 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_remquof_defined
#define __local_remquof_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: remquo from math */
#ifndef __local___localdep_remquo_defined
#define __local___localdep_remquo_defined 1
#if __has_builtin(__builtin_remquo) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remquo,(double __x, double __y, int *__pquo),remquo,{ return __builtin_remquo(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remquo,(double __x, double __y, int *__pquo),remquo,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquo)
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_remquo,(double __x, double __y, int *__pquo),__remquo,(__x,__y,__pquo))
#else /* ... */
#undef __local___localdep_remquo_defined
#endif /* !... */
#endif /* !__local___localdep_remquo_defined */
/* Compute remainder of X and Y and put in *QUO a value with sign
 * of x/y and magnitude congruent `mod 2^n' to the magnitude of
 * the integral quotient x/y, with n >= 3 */
__LOCAL_LIBC(remquof) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(remquof))(float __x, float __y, int *__pquo) {
	return (float)__localdep_remquo((double)__x, (double)__y, __pquo);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_remquof_defined
#define __local___localdep_remquof_defined 1
#define __localdep_remquof __LIBC_LOCAL_NAME(remquof)
#endif /* !__local___localdep_remquof_defined */
#else /* __CRT_HAVE_remquo || __CRT_HAVE___remquo */
#undef __local_remquof_defined
#endif /* !__CRT_HAVE_remquo && !__CRT_HAVE___remquo */
#endif /* !__local_remquof_defined */
