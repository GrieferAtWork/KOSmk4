/* HASH CRC-32:0x7729d6ae */
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
#ifndef __local_getitimer_defined
#if defined(__CRT_HAVE_getitimer) || defined(__CRT_HAVE_getitimer64)
#define __local_getitimer_defined 1
/* Dependency: "getitimer32" from "sys.time" */
#ifndef ____localdep_getitimer32_defined
#define ____localdep_getitimer32_defined 1
#ifdef __CRT_HAVE_getitimer
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_getitimer32,(__itimer_which_t __which, struct __itimerval32 *__curr_value),getitimer,(__which,__curr_value))
#else /* LIBC: getitimer */
#undef ____localdep_getitimer32_defined
#endif /* getitimer32... */
#endif /* !____localdep_getitimer32_defined */

/* Dependency: "getitimer64" from "sys.time" */
#ifndef ____localdep_getitimer64_defined
#define ____localdep_getitimer64_defined 1
#ifdef __CRT_HAVE_getitimer64
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_getitimer64,(__itimer_which_t __which, struct itimerval64 *__curr_value),getitimer64,(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_getitimer64,(__itimer_which_t __which, struct itimerval64 *__curr_value),getitimer,(__which,__curr_value))
#elif defined(__CRT_HAVE_getitimer)
#include <local/sys.time/getitimer64.h>
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
#define __localdep_getitimer64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getitimer64))
#else /* CUSTOM: getitimer64 */
#undef ____localdep_getitimer64_defined
#endif /* getitimer64... */
#endif /* !____localdep_getitimer64_defined */

__NAMESPACE_LOCAL_BEGIN
/* Set *VALUE to the current setting of timer WHICH.
 * Return 0 on success, -1 on errors */
__LOCAL_LIBC(getitimer) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getitimer))(__itimer_which_t __which,
                                                       struct itimerval *__curr_value) {
#line 177 "kos/src/libc/magic/sys.time.c"
#ifdef __CRT_HAVE_getitimer
	int __result;
	struct __itimerval32 __tv32;
	__result = __localdep_getitimer32(__which, &__tv32);
	if __likely(!__result) {
		__curr_value->it_interval.tv_sec  = (__time64_t)__tv32.it_interval.tv_sec;
		__curr_value->it_interval.tv_usec = __tv32.it_interval.tv_usec;
		__curr_value->it_value.tv_sec     = (__time64_t)__tv32.it_value.tv_sec;
		__curr_value->it_value.tv_usec    = __tv32.it_value.tv_usec;
	}
	return __result;
#else /* __CRT_HAVE_getitimer */
	int __result;
	struct __timeval64 __tv64;
	__result = __localdep_getitimer64(__which, &__tv64);
	if __likely(!__result) {
		__curr_value->it_interval.tv_sec  = (__time32_t)__tv64.it_interval.tv_sec;
		__curr_value->it_interval.tv_usec = __tv64.it_interval.tv_usec;
		__curr_value->it_value.tv_sec     = (__time32_t)__tv64.it_value.tv_sec;
		__curr_value->it_value.tv_usec    = __tv64.it_value.tv_usec;
	}
	return __result;
#endif /* !__CRT_HAVE_getitimer */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_getitimer || __CRT_HAVE_getitimer64 */
#endif /* !__local_getitimer_defined */
