/* HASH CRC-32:0x6af7e771 */
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
#ifndef __local_ldexpl_defined
#if defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp)
#define __local_ldexpl_defined 1
/* Dependency: "ldexp" */
#ifndef ____localdep_ldexp_defined
#define ____localdep_ldexp_defined 1
#if __has_builtin(__builtin_ldexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexp)
/* X times (two to the EXP power) */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_ldexp)(double __x, int __exponent) { return __builtin_ldexp(__x, __exponent); }
#elif defined(__CRT_HAVE_ldexp)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_ldexp,(double __x, int __exponent),ldexp,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexp)
/* X times (two to the EXP power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_ldexp,(double __x, int __exponent),__ldexp,(__x,__exponent))
#else /* LIBC: ldexp */
#undef ____localdep_ldexp_defined
#endif /* ldexp... */
#endif /* !____localdep_ldexp_defined */

__NAMESPACE_LOCAL_BEGIN
/* X times (two to the EXP power) */
__LOCAL_LIBC(ldexpl) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ldexpl))(long double __x,
                                                int __exponent) {
#line 248 "kos/src/libc/magic/math.c"
	return (long double)__localdep_ldexp((double)__x, __exponent);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_ldexp || __CRT_HAVE___ldexp */
#endif /* !__local_ldexpl_defined */
