/* HASH CRC-32:0xebe6715a */
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
#ifndef __local_logbf_defined
#if defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb)
#define __local_logbf_defined 1
/* Dependency: "logb" */
#ifndef ____localdep_logb_defined
#define ____localdep_logb_defined 1
#if __has_builtin(__builtin_logb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logb)
/* Return the base 2 signed integral exponent of X */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_logb)(double __x) { return __builtin_logb(__x); }
#elif defined(__CRT_HAVE_logb)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_logb,(double __x),logb,(__x))
#elif defined(__CRT_HAVE___logb)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_logb,(double __x),__logb,(__x))
#elif defined(__CRT_HAVE__logb)
/* Return the base 2 signed integral exponent of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_logb,(double __x),_logb,(__x))
#else /* LIBC: logb */
#undef ____localdep_logb_defined
#endif /* logb... */
#endif /* !____localdep_logb_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the base 2 signed integral exponent of X */
__LOCAL_LIBC(logbf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(logbf))(float __x) {
#line 288 "kos/src/libc/magic/math.c"
	return (float)__localdep_logb((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_logb || __CRT_HAVE___logb || __CRT_HAVE__logb */
#endif /* !__local_logbf_defined */
