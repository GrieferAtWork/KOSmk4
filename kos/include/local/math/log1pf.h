/* HASH CRC-32:0x493d2167 */
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
#ifndef __local_log1pf_defined
#if defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
#define __local_log1pf_defined 1
/* Dependency: "log1p" */
#ifndef ____localdep_log1p_defined
#define ____localdep_log1p_defined 1
#if __has_builtin(__builtin_log1p) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1p)
/* Return log(1 + X) */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log1p,(double __x),log1p,{ return __builtin_log1p(__x); })
#elif defined(__CRT_HAVE_log1p)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log1p,(double __x),log1p,(__x))
#elif defined(__CRT_HAVE___log1p)
/* Return log(1 + X) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_log1p,(double __x),__log1p,(__x))
#else /* LIBC: log1p */
#undef ____localdep_log1p_defined
#endif /* log1p... */
#endif /* !____localdep_log1p_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return log(1 + X) */
__LOCAL_LIBC(log1pf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(log1pf))(float __x) {
#line 578 "kos/src/libc/magic/math.c"
	return (float)__localdep_log1p((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_log1p || __CRT_HAVE___log1p */
#endif /* !__local_log1pf_defined */
