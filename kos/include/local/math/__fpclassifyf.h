/* HASH CRC-32:0xe78c46aa */
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
#ifndef __local___fpclassifyf_defined
#if defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE__dclass)
#define __local___fpclassifyf_defined 1
/* Dependency: "__fpclassify" */
#ifndef ____localdep___fpclassify_defined
#define ____localdep___fpclassify_defined 1
#ifdef __CRT_HAVE___fpclassify
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),__fpclassify,(__x))
#elif defined(__CRT_HAVE__dclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___fpclassify,(double __x),_dclass,(__x))
#else /* LIBC: __fpclassify */
#undef ____localdep___fpclassify_defined
#endif /* __fpclassify... */
#endif /* !____localdep___fpclassify_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__fpclassifyf) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__fpclassifyf))(float __x) {
#line 1948 "kos/src/libc/magic/math.c"
	return (int)__localdep___fpclassify((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE___fpclassify || __CRT_HAVE__dclass */
#endif /* !__local___fpclassifyf_defined */
