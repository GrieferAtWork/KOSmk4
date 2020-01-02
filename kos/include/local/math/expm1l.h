/* HASH CRC-32:0xea9878e6 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_expm1l_defined
#if defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1)
#define __local_expm1l_defined 1
/* Dependency: "expm1" */
#ifndef ____localdep_expm1_defined
#define ____localdep_expm1_defined 1
#if __has_builtin(__builtin_expm1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1)
/* Return exp(X) - 1 */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_expm1)(double __x) { return __builtin_expm1(__x); }
#elif defined(__CRT_HAVE_expm1)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_expm1,(double __x),expm1,(__x))
#elif defined(__CRT_HAVE___expm1)
/* Return exp(X) - 1 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_expm1,(double __x),__expm1,(__x))
#else /* LIBC: expm1 */
#undef ____localdep_expm1_defined
#endif /* expm1... */
#endif /* !____localdep_expm1_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return exp(X) - 1 */
__LOCAL_LIBC(expm1l) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(expm1l))(long double __x) {
#line 280 "kos/src/libc/magic/math.c"
	return (long double)__localdep_expm1((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_expm1 || __CRT_HAVE___expm1 */
#endif /* !__local_expm1l_defined */
