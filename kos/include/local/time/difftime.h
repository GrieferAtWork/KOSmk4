/* HASH CRC-32:0x2e1d5672 */
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
#ifndef __local_difftime_defined
#define __local_difftime_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: difftime32 from time */
#ifndef __local___localdep_difftime32_defined
#define __local___localdep_difftime32_defined 1
#ifdef __CRT_HAVE_difftime
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_difftime32,(__time32_t __time1, __time32_t __time0),difftime,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime32)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_difftime32,(__time32_t __time1, __time32_t __time0),_difftime32,(__time1,__time0))
#else /* ... */
#undef __local___localdep_difftime32_defined
#endif /* !... */
#endif /* !__local___localdep_difftime32_defined */
/* Dependency: difftime64 from time */
#ifndef __local___localdep_difftime64_defined
#define __local___localdep_difftime64_defined 1
#ifdef __CRT_HAVE_difftime64
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_difftime64,(__time64_t __time1, __time64_t __time0),difftime64,(__time1,__time0))
#elif defined(__CRT_HAVE_difftime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_difftime64,(__time64_t __time1, __time64_t __time0),difftime,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime64)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_difftime64,(__time64_t __time1, __time64_t __time0),_difftime64,(__time1,__time0))
#elif defined(__CRT_HAVE___difftime64)
/* Return the difference between TIME1 and TIME0 */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_difftime64,(__time64_t __time1, __time64_t __time0),__difftime64,(__time1,__time0))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/time/difftime64.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the difference between TIME1 and TIME0 */
#define __localdep_difftime64 __LIBC_LOCAL_NAME(difftime64)
#endif /* !... */
#endif /* !__local___localdep_difftime64_defined */
/* Return the difference between TIME1 and TIME0 */
__LOCAL_LIBC(difftime) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(difftime))(__TM_TYPE(time) __time1, __TM_TYPE(time) __time0) {
#ifdef __BUILDING_LIBC
	return __time1 > __time0 ? __time1 - __time0 : __time0 - __time1;
#elif defined(__CRT_HAVE_difftime) || defined(__CRT_HAVE__difftime32)
	return __localdep_difftime32((__time32_t)__time1, (__time32_t)__time0);
#else /* ... */
	return __localdep_difftime64((__time32_t)__time1, (__time32_t)__time0);


#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_difftime_defined
#define __local___localdep_difftime_defined 1
#define __localdep_difftime __LIBC_LOCAL_NAME(difftime)
#endif /* !__local___localdep_difftime_defined */
#endif /* !__local_difftime_defined */
