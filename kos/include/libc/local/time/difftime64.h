/* HASH CRC-32:0xc2efc839 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_difftime64_defined
#define __local_difftime64_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_difftime32_defined
#define __local___localdep_crt_difftime32_defined
#ifdef __CRT_HAVE_difftime
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_crt_difftime32,(__time32_t __time1, __time32_t __time0),difftime,(__time1,__time0))
#elif defined(__CRT_HAVE__difftime32)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_crt_difftime32,(__time32_t __time1, __time32_t __time0),_difftime32,(__time1,__time0))
#else /* ... */
#undef __local___localdep_crt_difftime32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_difftime32_defined */
__LOCAL_LIBC(difftime64) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(difftime64))(__time64_t __time1, __time64_t __time0) {
#if defined(__CRT_HAVE_difftime) || defined(__CRT_HAVE__difftime32)
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_difftime32)((__time32_t)__time1, (__time32_t)__time0);
#else /* __CRT_HAVE_difftime || __CRT_HAVE__difftime32 */
	return __time1 > __time0 ? __time1 - __time0 : __time0 - __time1;
#endif /* !__CRT_HAVE_difftime && !__CRT_HAVE__difftime32 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_difftime64_defined
#define __local___localdep_difftime64_defined
#define __localdep_difftime64 __LIBC_LOCAL_NAME(difftime64)
#endif /* !__local___localdep_difftime64_defined */
#endif /* !__local_difftime64_defined */
