/* HASH CRC-32:0x3f6444c */
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
#ifndef __local_tgammal_defined
#if defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
#define __local_tgammal_defined 1
/* Dependency: "tgamma" */
#ifndef ____localdep_tgamma_defined
#define ____localdep_tgamma_defined 1
#if __has_builtin(__builtin_tgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgamma)
/* True gamma function */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_tgamma)(double __x) { return __builtin_tgamma(__x); }
#elif defined(__CRT_HAVE_tgamma)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tgamma,(double __x),tgamma,(__x))
#elif defined(__CRT_HAVE___tgamma)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_tgamma,(double __x),__tgamma,(__x))
#else /* LIBC: tgamma */
#undef ____localdep_tgamma_defined
#endif /* tgamma... */
#endif /* !____localdep_tgamma_defined */

__NAMESPACE_LOCAL_BEGIN
/* True gamma function */
__LOCAL_LIBC(tgammal) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(tgammal))(long double __x) {
#line 642 "kos/src/libc/magic/math.c"
	return (long double)__localdep_tgamma((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_tgamma || __CRT_HAVE___tgamma */
#endif /* !__local_tgammal_defined */
