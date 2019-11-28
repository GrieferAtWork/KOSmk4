/* HASH CRC-32:0x53a44902 */
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
#ifndef __local_lgammaf_defined
#if defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma) || defined(__CRT_HAVE_gamma)
#define __local_lgammaf_defined 1
/* Dependency: "lgamma" */
#ifndef ____localdep_lgamma_defined
#define ____localdep_lgamma_defined 1
#if __has_builtin(__builtin_lgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma)
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_lgamma)(double __x) { return __builtin_lgamma(__x); }
#elif defined(__CRT_HAVE_lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),lgamma,(__x))
#elif defined(__CRT_HAVE___lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),__gamma,(__x))
#elif defined(__CRT_HAVE_gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_lgamma,(double __x),gamma,(__x))
#else /* LIBC: lgamma */
#undef ____localdep_lgamma_defined
#endif /* lgamma... */
#endif /* !____localdep_lgamma_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(lgammaf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lgammaf))(float __x) {
#line 422 "kos/src/libc/magic/math.c"
	return (float)__localdep_lgamma((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_lgamma || __CRT_HAVE___lgamma || __CRT_HAVE___gamma || __CRT_HAVE_gamma */
#endif /* !__local_lgammaf_defined */
