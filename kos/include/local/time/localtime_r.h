/* HASH CRC-32:0x1d30e312 */
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
#ifndef __local_localtime_r_defined
#define __local_localtime_r_defined 1
/* Dependency: "dos_localtime_s" from "time" */
#ifndef ____localdep_dos_localtime_s_defined
#define ____localdep_dos_localtime_s_defined 1
#if defined(__CRT_HAVE__localtime32_s) && (defined(__USE_TIME_BITS64))
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime_s,(struct tm *__restrict __tp, __TM_TYPE(time) const *__restrict __timer),_localtime32_s,(__tp,__timer))
#elif defined(__CRT_HAVE__localtime64_s) && (!defined(__USE_TIME_BITS64))
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime_s,(struct tm *__restrict __tp, __TM_TYPE(time) const *__restrict __timer),_localtime64_s,(__tp,__timer))
#elif (defined(__CRT_HAVE__localtime32_s) || defined(__CRT_HAVE__localtime64_s))
#include <local/time/dos_localtime_s.h>
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
#define __localdep_dos_localtime_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dos_localtime_s))
#else /* CUSTOM: dos_localtime_s */
#undef ____localdep_dos_localtime_s_defined
#endif /* dos_localtime_s... */
#endif /* !____localdep_dos_localtime_s_defined */

/* Dependency: "localtime64_r" from "time" */
#ifndef ____localdep_localtime64_r_defined
#define ____localdep_localtime64_r_defined 1
#if defined(__CRT_HAVE_localtime64_r)
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct tm *__restrict __tp),localtime64_r,(__timer,__tp))
#elif defined(__CRT_HAVE_localtime_r) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct tm *__restrict __tp),localtime_r,(__timer,__tp))
#else /* LIBC: localtime64_r */
#include <local/time/localtime64_r.h>
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
#define __localdep_localtime64_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64_r))
#endif /* localtime64_r... */
#endif /* !____localdep_localtime64_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__LOCAL_LIBC(localtime_r) __ATTR_NONNULL((1, 2)) struct tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(localtime_r))(__TM_TYPE(time) const *__restrict __timer,
                                                         struct tm *__restrict __tp) {
#line 1558 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE__localtime32_s) || defined(__CRT_HAVE__localtime64_s)
	return __localdep_dos_localtime_s(__tp, __timer) ? __NULLPTR : __tp;
#elif defined(__USE_TIME_BITS64)
	return __localdep_localtime64_r(__timer, __tp);
#else
	__time64_t __tm64 = (__time64_t)*__timer;
	return __localdep_localtime64_r(&__tm64, __tp);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_localtime_r_defined */
