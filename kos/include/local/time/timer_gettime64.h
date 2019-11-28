/* HASH CRC-32:0xace8959f */
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
#ifndef __local_timer_gettime64_defined
#ifdef __CRT_HAVE_timer_gettime
#define __local_timer_gettime64_defined 1
/* Dependency: "timer_gettime32" from "time" */
#ifndef ____localdep_timer_gettime32_defined
#define ____localdep_timer_gettime32_defined 1
#ifdef __CRT_HAVE_timer_gettime
/* Get current value of timer TIMERID and store it in VALUE */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_timer_gettime32,(timer_t __timerid, struct itimerspec *__value),timer_gettime,(__timerid,__value))
#else /* LIBC: timer_gettime */
#undef ____localdep_timer_gettime32_defined
#endif /* timer_gettime32... */
#endif /* !____localdep_timer_gettime32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Get current value of timer TIMERID and store it in VALUE */
__LOCAL_LIBC(timer_gettime64) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timer_gettime64))(timer_t __timerid,
                                                             struct itimerspec64 *__value) {
#line 1272 "kos/src/libc/magic/time.c"
	int __result;
	struct __itimerspec32 __value32;
	__result = __localdep_timer_gettime32(__timerid, &__value32);
	if (!__result) {
		__value->__it_interval.tv_sec  = (__time64_t)__value32.__it_interval.tv_sec;
		__value->__it_interval.tv_nsec = __value32.__it_interval.tv_nsec;
		__value->__it_value.tv_sec     = (__time64_t)__value32.__it_value.tv_sec;
		__value->__it_value.tv_nsec    = __value32.__it_value.tv_nsec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_timer_gettime */
#endif /* !__local_timer_gettime64_defined */
