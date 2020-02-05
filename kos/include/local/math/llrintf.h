/* HASH CRC-32:0xf7a08195 */
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
#ifndef __local_llrintf_defined
#if defined(__CRT_HAVE_llrint) || defined(__CRT_HAVE___llrint)
#define __local_llrintf_defined 1
/* Dependency: "llrint" */
#ifndef ____localdep_llrint_defined
#define ____localdep_llrint_defined 1
#if __has_builtin(__builtin_llrint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrint)
/* Round X to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__localdep_llrint,(double __x),llrint,{ return __builtin_llrint(__x); })
#elif defined(__CRT_HAVE_llrint)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__localdep_llrint,(double __x),llrint,(__x))
#elif defined(__CRT_HAVE___llrint)
/* Round X to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_WUNUSED,__LONGLONG,__NOTHROW,__localdep_llrint,(double __x),__llrint,(__x))
#else /* LIBC: llrint */
#undef ____localdep_llrint_defined
#endif /* llrint... */
#endif /* !____localdep_llrint_defined */

__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value according to current rounding direction */
__LOCAL_LIBC(llrintf) __ATTR_CONST __ATTR_WUNUSED __LONGLONG
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(llrintf))(float __x) {
#line 1615 "kos/src/libc/magic/math.c"
	return (__LONGLONG)__localdep_llrint((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_llrint || __CRT_HAVE___llrint */
#endif /* !__local_llrintf_defined */
