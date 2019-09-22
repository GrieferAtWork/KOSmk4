/* HASH CRC-32:0x75f4bdca */
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
#ifndef __local_atan2l_defined
#if ((__has_builtin(__builtin_atan2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2)) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2))
#define __local_atan2l_defined 1
/* Dependency: "atan2" */
#ifndef ____localdep_atan2_defined
#define ____localdep_atan2_defined 1
#if __has_builtin(__builtin_atan2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2)
/* Arc tangent of Y/X */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_atan2)(double __y, double __x) { return __builtin_atan2(__y, __x); }
#elif defined(__CRT_HAVE_atan2)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan2,(double __y, double __x),atan2,(__y,__x))
#elif defined(__CRT_HAVE___atan2)
/* Arc tangent of Y/X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan2,(double __y, double __x),__atan2,(__y,__x))
#else /* LIBC: atan2 */
#undef ____localdep_atan2_defined
#endif /* atan2... */
#endif /* !____localdep_atan2_defined */

__NAMESPACE_LOCAL_BEGIN
/* Arc tangent of Y/X */
__LOCAL_LIBC(atan2l) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atan2l))(long double __y,
                                                long double __x) {
#line 143 "kos/src/libc/magic/math.c"
	return (long double)__localdep_atan2((double)__y, (double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_atan2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2)) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2)) */
#endif /* !__local_atan2l_defined */
