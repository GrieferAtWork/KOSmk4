/* HASH CRC-32:0x6e838806 */
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
#ifndef __local_pow10f_defined
#if defined(__CRT_HAVE_pow10) || defined(__CRT_HAVE___pow10)
#define __local_pow10f_defined 1
/* Dependency: "pow10" */
#ifndef ____localdep_pow10_defined
#define ____localdep_pow10_defined 1
#if __has_builtin(__builtin_pow10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__FORCELOCAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __localdep_pow10)(double __x) { return __builtin_pow10(__x); }
#elif defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_pow10,(double __x),pow10,(__x))
#elif defined(__CRT_HAVE___pow10)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_pow10,(double __x),__pow10,(__x))
#else /* LIBC: pow10 */
#undef ____localdep_pow10_defined
#endif /* pow10... */
#endif /* !____localdep_pow10_defined */

__NAMESPACE_LOCAL_BEGIN
/* Another name occasionally used */
__LOCAL_LIBC(pow10f) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(pow10f))(float __x) {
#line 775 "kos/src/libc/magic/math.c"
	return (float)__localdep_pow10((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_pow10) || defined(__CRT_HAVE___pow10) */
#endif /* !__local_pow10f_defined */
