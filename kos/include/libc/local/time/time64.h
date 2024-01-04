/* HASH CRC-32:0xb7f10c24 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_time64_defined
#define __local_time64_defined
#include <__crt.h>
#if defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_time32_defined
#define __local___localdep_crt_time32_defined
#ifdef __CRT_HAVE_time
__CREDIRECT(__ATTR_OUT_OPT(1),__time32_t,__NOTHROW_NCX,__localdep_crt_time32,(__time32_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE___time)
__CREDIRECT(__ATTR_OUT_OPT(1),__time32_t,__NOTHROW_NCX,__localdep_crt_time32,(__time32_t *__timer),__time,(__timer))
#elif defined(__CRT_HAVE___libc_time)
__CREDIRECT(__ATTR_OUT_OPT(1),__time32_t,__NOTHROW_NCX,__localdep_crt_time32,(__time32_t *__timer),__libc_time,(__timer))
#elif defined(__CRT_HAVE__time32)
__CREDIRECT(__ATTR_OUT_OPT(1),__time32_t,__NOTHROW_NCX,__localdep_crt_time32,(__time32_t *__timer),_time32,(__timer))
#else /* ... */
#undef __local___localdep_crt_time32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_time32_defined */
__LOCAL_LIBC(time64) __ATTR_OUT_OPT(1) __time64_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(time64))(__time64_t *__timer) {
	__time32_t __tm32 = (__NAMESPACE_LOCAL_SYM __localdep_crt_time32)(__NULLPTR);
	if (__timer)
		*__timer = (__time64_t)__tm32;
	return (__time64_t)__tm32;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_time64_defined
#define __local___localdep_time64_defined
#define __localdep_time64 __LIBC_LOCAL_NAME(time64)
#endif /* !__local___localdep_time64_defined */
#else /* __CRT_HAVE_time || __CRT_HAVE___time || __CRT_HAVE___libc_time || __CRT_HAVE__time32 */
#undef __local_time64_defined
#endif /* !__CRT_HAVE_time && !__CRT_HAVE___time && !__CRT_HAVE___libc_time && !__CRT_HAVE__time32 */
#endif /* !__local_time64_defined */
