/* HASH CRC-32:0xe8db0bbd */
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
#ifndef __local_erff_defined
#if defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
#define __local_erff_defined 1
/* Dependency: "erf" */
#ifndef ____localdep_erf_defined
#define ____localdep_erf_defined 1
#if __has_builtin(__builtin_erf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erf)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_erf,(double __x),erf,{ return __builtin_erf(__x); })
#elif defined(__CRT_HAVE_erf)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_erf,(double __x),erf,(__x))
#elif defined(__CRT_HAVE___erf)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_erf,(double __x),__erf,(__x))
#else /* LIBC: erf */
#undef ____localdep_erf_defined
#endif /* erf... */
#endif /* !____localdep_erf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(erff) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(erff))(float __x) {
#line 768 "kos/src/libc/magic/math.c"
	return (float)__localdep_erf((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_erf || __CRT_HAVE___erf */
#endif /* !__local_erff_defined */
