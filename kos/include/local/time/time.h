/* HASH CRC-32:0xa15b729e */
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
#ifndef __local_time_defined
#if defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32)
#define __local_time_defined 1
/* Dependency: "time32" from "time" */
#ifndef ____localdep_time32_defined
#define ____localdep_time32_defined 1
#if defined(__CRT_HAVE_time)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,__time32_t,__NOTHROW_NCX,__localdep_time32,(__time32_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE__time32)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,__time32_t,__NOTHROW_NCX,__localdep_time32,(__time32_t *__timer),_time32,(__timer))
#else /* LIBC: time */
#undef ____localdep_time32_defined
#endif /* time32... */
#endif /* !____localdep_time32_defined */

/* Dependency: "time64" from "time" */
#ifndef ____localdep_time64_defined
#define ____localdep_time64_defined 1
#if defined(__CRT_HAVE_time64)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,__time64_t,__NOTHROW_NCX,__localdep_time64,(__time64_t *__timer),time64,(__timer))
#elif defined(__CRT_HAVE_time) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,__time64_t,__NOTHROW_NCX,__localdep_time64,(__time64_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE__time64)
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__CREDIRECT(,__time64_t,__NOTHROW_NCX,__localdep_time64,(__time64_t *__timer),_time64,(__timer))
#elif defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32)
#include <local/time/time64.h>
/* Return the current time and put it in *TIMER if TIMER is not NULL */
#define __localdep_time64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(time64))
#else /* CUSTOM: time64 */
#undef ____localdep_time64_defined
#endif /* time64... */
#endif /* !____localdep_time64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the current time and put it in *TIMER if TIMER is not NULL */
__LOCAL_LIBC(time) __TM_TYPE(time)
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(time))(__TM_TYPE(time) *__timer) {
#line 394 "kos/src/libc/magic/time.c"
#ifdef __USE_TIME_BITS64
	__time32_t __tm32 = __localdep_time32(__NULLPTR);
	if (__timer)
		*__timer = (__TM_TYPE(time))__tm32;
	return (__TM_TYPE(time))__tm32;
#else /* __USE_TIME_BITS64 */
	__time64_t __tm64 = __localdep_time64(__NULLPTR);
	if (__timer)
		*__timer = (__TM_TYPE(time))__tm64;
	return (__TM_TYPE(time))__tm64;
#endif /* !__USE_TIME_BITS64 */
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE__time32) */
#endif /* !__local_time_defined */
