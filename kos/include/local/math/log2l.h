/* HASH CRC-32:0x9d5ccfa8 */
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
#ifndef __local_log2l_defined
#if defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
#define __local_log2l_defined 1
/* Dependency: "log2" */
#ifndef ____localdep_log2_defined
#define ____localdep_log2_defined 1
#if __has_builtin(__builtin_log2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2)
/* Compute base-2 logarithm of X */
__EXTERNINLINE __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_log2)(double __x) { return __builtin_log2(__x); }
#elif defined(__CRT_HAVE_log2)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log2,(double __x),log2,(__x))
#elif defined(__CRT_HAVE___log2)
/* Compute base-2 logarithm of X */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log2,(double __x),__log2,(__x))
#else /* LIBC: log2 */
#undef ____localdep_log2_defined
#endif /* log2... */
#endif /* !____localdep_log2_defined */

__NAMESPACE_LOCAL_BEGIN
/* Compute base-2 logarithm of X */
__LOCAL_LIBC(log2l) __ATTR_WUNUSED long double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(log2l))(long double __x) {
#line 299 "kos/src/libc/magic/math.c"
	return (long double)__localdep_log2((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_log2 || __CRT_HAVE___log2 */
#endif /* !__local_log2l_defined */
