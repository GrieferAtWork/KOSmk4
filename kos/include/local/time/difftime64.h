/* HASH CRC-32:0xdedb75fe */
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
#ifndef __local_difftime64_defined
#define __local_difftime64_defined 1
/* Dependency: "difftime32" from "time" */
#ifndef ____localdep_difftime32_defined
#define ____localdep_difftime32_defined 1
#ifdef __CRT_HAVE_difftime
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_difftime32,(__time32_t __time1, __time32_t __time0),difftime,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime32)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_difftime32,(__time32_t __time1, __time32_t __time0),_difftime32,(__time1,__time0))
#else /* LIBC: difftime */
#undef ____localdep_difftime32_defined
#endif /* difftime32... */
#endif /* !____localdep_difftime32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the difference between TIME1 and TIME0 */
__LOCAL_LIBC(difftime64) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(difftime64))(__time64_t __time1,
                                                        __time64_t __time0) {
#line 641 "kos/src/libc/magic/time.c"
#if (defined(__CRT_HAVE_difftime) || defined(__CRT_HAVE__difftime32)) && !defined(__BUILDING_LIBC)
	return __localdep_difftime32((__time32_t)__time1, (__time32_t)__time0);
#else /* ... */
	return (double)__time1 - (double)__time0;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_difftime64_defined */
