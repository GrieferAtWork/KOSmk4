/* HASH CRC-32:0x22ed1cb4 */
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
#ifndef __local_nearbyintf_defined
#if defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___nearbyint)
#define __local_nearbyintf_defined 1
/* Dependency: "nearbyint" */
#ifndef ____localdep_nearbyint_defined
#define ____localdep_nearbyint_defined 1
#if __has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyint)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_nearbyint)(double __x) { return __builtin_nearbyint(__x); }
#elif defined(__CRT_HAVE_nearbyint)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_nearbyint,(double __x),nearbyint,(__x))
#elif defined(__CRT_HAVE___nearbyint)
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_nearbyint,(double __x),__nearbyint,(__x))
#else /* LIBC: nearbyint */
#undef ____localdep_nearbyint_defined
#endif /* nearbyint... */
#endif /* !____localdep_nearbyint_defined */

__NAMESPACE_LOCAL_BEGIN
/* Round X to integral value in floating-point format using current
 * rounding direction, but do not raise inexact exception */
__LOCAL_LIBC(nearbyintf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(nearbyintf))(float __x) {
#line 564 "kos/src/libc/magic/math.c"
	return (float)__localdep_nearbyint((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_nearbyint || __CRT_HAVE___nearbyint */
#endif /* !__local_nearbyintf_defined */
