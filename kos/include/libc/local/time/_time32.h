/* HASH CRC-32:0x2d48f86f */
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
#ifndef __local__time32_defined
#define __local__time32_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE___time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_time_defined
#define __local___localdep_time_defined
#if defined(__CRT_HAVE_time) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(1),__time_t,__NOTHROW_NCX,__localdep_time,(__time_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE___time) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(1),__time_t,__NOTHROW_NCX,__localdep_time,(__time_t *__timer),__time,(__timer))
#elif defined(__CRT_HAVE___libc_time) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(1),__time_t,__NOTHROW_NCX,__localdep_time,(__time_t *__timer),__libc_time,(__timer))
#elif defined(__CRT_HAVE__time32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(1),__time_t,__NOTHROW_NCX,__localdep_time,(__time_t *__timer),_time32,(__timer))
#elif defined(__CRT_HAVE_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(1),__time_t,__NOTHROW_NCX,__localdep_time,(__time_t *__timer),time64,(__timer))
#elif defined(__CRT_HAVE__time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(1),__time_t,__NOTHROW_NCX,__localdep_time,(__time_t *__timer),_time64,(__timer))
#elif defined(__CRT_HAVE___time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_OUT_OPT(1),__time_t,__NOTHROW_NCX,__localdep_time,(__time_t *__timer),__time64,(__timer))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/time.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_time __LIBC_LOCAL_NAME(time)
#endif /* !... */
#endif /* !__local___localdep_time_defined */
__LOCAL_LIBC(_time32) __time32_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_time32))(__time32_t *__timer) {
	__time32_t __result = (__time32_t)(__NAMESPACE_LOCAL_SYM __localdep_time)(__NULLPTR);
	if (__timer != __NULLPTR)
		*__timer = __result;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__time32_defined
#define __local___localdep__time32_defined
#define __localdep__time32 __LIBC_LOCAL_NAME(_time32)
#endif /* !__local___localdep__time32_defined */
#else /* __CRT_HAVE_time64 || __CRT_HAVE__time64 || __CRT_HAVE___time64 || __CRT_HAVE_time || __CRT_HAVE___time || __CRT_HAVE___libc_time || __CRT_HAVE__time32 */
#undef __local__time32_defined
#endif /* !__CRT_HAVE_time64 && !__CRT_HAVE__time64 && !__CRT_HAVE___time64 && !__CRT_HAVE_time && !__CRT_HAVE___time && !__CRT_HAVE___libc_time && !__CRT_HAVE__time32 */
#endif /* !__local__time32_defined */
