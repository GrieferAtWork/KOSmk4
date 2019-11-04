/* HASH CRC-32:0xc8499308 */
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
#ifndef __local_atanl_defined
#if defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan)
#define __local_atanl_defined 1
/* Dependency: "atan" */
#ifndef ____localdep_atan_defined
#define ____localdep_atan_defined 1
#if __has_builtin(__builtin_atan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_atan)(double __x) { return __builtin_atan(__x); }
#elif defined(__CRT_HAVE_atan)
/* Arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),atan,(__x))
#elif defined(__CRT_HAVE___atan)
/* Arc tangent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_atan,(double __x),__atan,(__x))
#else /* LIBC: atan */
#undef ____localdep_atan_defined
#endif /* atan... */
#endif /* !____localdep_atan_defined */

__NAMESPACE_LOCAL_BEGIN
/* Arc tangent of X */
__LOCAL_LIBC(atanl) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(atanl))(long double __x) {
#line 142 "kos/src/libc/magic/math.c"
	return (long double)__localdep_atan((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) */
#endif /* !__local_atanl_defined */
