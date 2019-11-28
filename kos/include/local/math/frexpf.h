/* HASH CRC-32:0x30d7b354 */
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
#ifndef __local_frexpf_defined
#if defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp)
#define __local_frexpf_defined 1
/* Dependency: "frexp" */
#ifndef ____localdep_frexp_defined
#define ____localdep_frexp_defined 1
#if __has_builtin(__builtin_frexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL __localdep_frexp)(double __x, int *__pexponent) { return __builtin_frexp(__x, __pexponent); }
#elif defined(__CRT_HAVE_frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_frexp,(double __x, int *__pexponent),frexp,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexp)
/* Break VALUE into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_frexp,(double __x, int *__pexponent),__frexp,(__x,__pexponent))
#else /* LIBC: frexp */
#undef ____localdep_frexp_defined
#endif /* frexp... */
#endif /* !____localdep_frexp_defined */

__NAMESPACE_LOCAL_BEGIN
/* Break VALUE into a normalized fraction and an integral power of 2 */
__LOCAL_LIBC(frexpf) __ATTR_WUNUSED float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(frexpf))(float __x,
                                                    int *__pexponent) {
#line 230 "kos/src/libc/magic/math.c"
	return (float)__localdep_frexp((double)__x, __pexponent);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_frexp || __CRT_HAVE___frexp */
#endif /* !__local_frexpf_defined */
