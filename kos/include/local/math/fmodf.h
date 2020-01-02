/* HASH CRC-32:0xd5efbad5 */
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
#ifndef __local_fmodf_defined
#if defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod)
#define __local_fmodf_defined 1
/* Dependency: "fmod" */
#ifndef ____localdep_fmod_defined
#define ____localdep_fmod_defined 1
#if __has_builtin(__builtin_fmod) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of X/Y */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_fmod)(double __x, double __y) { return __builtin_fmod(__x, __y); }
#elif defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of X/Y */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_fmod,(double __x, double __y),fmod,(__x,__y))
#elif defined(__CRT_HAVE___fmod)
/* Floating-point modulo remainder of X/Y */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_fmod,(double __x, double __y),__fmod,(__x,__y))
#else /* LIBC: fmod */
#undef ____localdep_fmod_defined
#endif /* fmod... */
#endif /* !____localdep_fmod_defined */

__NAMESPACE_LOCAL_BEGIN
/* Floating-point modulo remainder of X/Y */
__LOCAL_LIBC(fmodf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fmodf))(float __x,
                                               float __y) {
#line 378 "kos/src/libc/magic/math.c"
	return (float)__localdep_fmod((double)__x, (double)__y);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_fmod || __CRT_HAVE___fmod */
#endif /* !__local_fmodf_defined */
