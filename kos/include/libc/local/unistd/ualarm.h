/* HASH CRC-32:0x51fd8998 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ualarm_defined
#define __local_ualarm_defined
#include <__crt.h>
#include <asm/os/itimer.h>
#include <features.h>
#include <bits/types.h>
#if defined(__ITIMER_REAL) && (defined(__CRT_HAVE_setitimer64) || defined(__CRT_HAVE_setitimer) || defined(__CRT_HAVE___setitimer) || defined(__CRT_HAVE___libc_setitimer))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setitimer_defined
#define __local___localdep_setitimer_defined
#if defined(__CRT_HAVE_setitimer) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/itimerval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer,(int __which, struct itimerval const *__newval, struct itimerval *__oldval),setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___setitimer) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/itimerval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer,(int __which, struct itimerval const *__newval, struct itimerval *__oldval),__setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE___libc_setitimer) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/itimerval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer,(int __which, struct itimerval const *__newval, struct itimerval *__oldval),__libc_setitimer,(__which,__newval,__oldval))
#elif defined(__CRT_HAVE_setitimer64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__NAMESPACE_LOCAL_END
#include <bits/os/itimerval.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_setitimer,(int __which, struct itimerval const *__newval, struct itimerval *__oldval),setitimer64,(__which,__newval,__oldval))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/setitimer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_setitimer __LIBC_LOCAL_NAME(setitimer)
#endif /* !... */
#endif /* !__local___localdep_setitimer_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/itimerval.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ualarm) __useconds_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ualarm))(__useconds_t ___value, __useconds_t __interval) {
	struct itimerval __timer, __otimer;
	__timer.it_value.tv_sec     = ___value / 1000000;
	__timer.it_value.tv_usec    = ___value % 1000000;
	__timer.it_interval.tv_sec  = __interval / 1000000;
	__timer.it_interval.tv_usec = __interval % 1000000;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_setitimer)((int)__ITIMER_REAL, &__timer, &__otimer) < 0)
		goto __err;
	return (__otimer.it_value.tv_sec * 1000000) +
	       (__otimer.it_value.tv_usec);
__err:
	return (__useconds_t)-1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ualarm_defined
#define __local___localdep_ualarm_defined
#define __localdep_ualarm __LIBC_LOCAL_NAME(ualarm)
#endif /* !__local___localdep_ualarm_defined */
#else /* __ITIMER_REAL && (__CRT_HAVE_setitimer64 || __CRT_HAVE_setitimer || __CRT_HAVE___setitimer || __CRT_HAVE___libc_setitimer) */
#undef __local_ualarm_defined
#endif /* !__ITIMER_REAL || (!__CRT_HAVE_setitimer64 && !__CRT_HAVE_setitimer && !__CRT_HAVE___setitimer && !__CRT_HAVE___libc_setitimer) */
#endif /* !__local_ualarm_defined */
