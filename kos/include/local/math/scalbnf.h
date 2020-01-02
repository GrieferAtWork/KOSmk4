/* HASH CRC-32:0x22fc2d0d */
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
#ifndef __local_scalbnf_defined
#if defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn)
#define __local_scalbnf_defined 1
/* Dependency: "scalbn" */
#ifndef ____localdep_scalbn_defined
#define ____localdep_scalbn_defined 1
#if __has_builtin(__builtin_scalbn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbn)
/* Return X times (2 to the Nth power) */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_scalbn)(double __x, int __n) { return __builtin_scalbn(__x, __n); }
#elif defined(__CRT_HAVE_scalbn)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalbn,(double __x, int __n),scalbn,(__x,__n))
#elif defined(__CRT_HAVE___scalbn)
/* Return X times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalbn,(double __x, int __n),__scalbn,(__x,__n))
#else /* LIBC: scalbn */
#undef ____localdep_scalbn_defined
#endif /* scalbn... */
#endif /* !____localdep_scalbn_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return X times (2 to the Nth power) */
__LOCAL_LIBC(scalbnf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(scalbnf))(float __x,
                                                 int __n) {
#line 562 "kos/src/libc/magic/math.c"
	return (float)__localdep_scalbn((double)__x, __n);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_scalbn || __CRT_HAVE___scalbn */
#endif /* !__local_scalbnf_defined */
