/* HASH CRC-32:0x247aacd5 */
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
#ifndef __local_nexttowardf_defined
#if defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nexttoward)
#define __local_nexttowardf_defined 1
/* Dependency: "nexttoward" */
#ifndef ____localdep_nexttoward_defined
#define ____localdep_nexttoward_defined 1
#if __has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttoward)
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_nexttoward)(double __x, __LONGDOUBLE __y) { return __builtin_nexttoward(__x, __y); }
#elif defined(__CRT_HAVE_nexttoward)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_nexttoward,(double __x, __LONGDOUBLE __y),nexttoward,(__x,__y))
#elif defined(__CRT_HAVE___nexttoward)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_nexttoward,(double __x, __LONGDOUBLE __y),__nexttoward,(__x,__y))
#else /* LIBC: nexttoward */
#undef ____localdep_nexttoward_defined
#endif /* nexttoward... */
#endif /* !____localdep_nexttoward_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(nexttowardf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(nexttowardf))(float __x,
                                                     __LONGDOUBLE __y) {
#line 1121 "kos/src/libc/magic/math.c"
	return (float)__localdep_nexttoward((double)__x, __y);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_nexttoward || __CRT_HAVE___nexttoward */
#endif /* !__local_nexttowardf_defined */
