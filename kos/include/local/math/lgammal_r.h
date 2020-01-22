/* HASH CRC-32:0x6ea9824b */
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
#ifndef __local_lgammal_r_defined
#if defined(__CRT_HAVE_lgamma_r) || defined(__CRT_HAVE___lgamma_r)
#define __local_lgammal_r_defined 1
/* Dependency: "lgamma_r" */
#ifndef ____localdep_lgamma_r_defined
#define ____localdep_lgamma_r_defined 1
#if __has_builtin(__builtin_lgamma_r) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL __localdep_lgamma_r)(double __x, int *__signgamp) { return __builtin_lgamma_r(__x, __signgamp); }
#elif defined(__CRT_HAVE_lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_lgamma_r,(double __x, int *__signgamp),lgamma_r,(__x,__signgamp))
#elif defined(__CRT_HAVE___lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_lgamma_r,(double __x, int *__signgamp),__lgamma_r,(__x,__signgamp))
#else /* LIBC: lgamma_r */
#undef ____localdep_lgamma_r_defined
#endif /* lgamma_r... */
#endif /* !____localdep_lgamma_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__LOCAL_LIBC(lgammal_r) __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lgammal_r))(__LONGDOUBLE __x,
                                                       int *__signgamp) {
#line 2191 "kos/src/libc/magic/math.c"
	return (__LONGDOUBLE)__localdep_lgamma_r((double)__x, __signgamp);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_lgamma_r || __CRT_HAVE___lgamma_r */
#endif /* !__local_lgammal_r_defined */
