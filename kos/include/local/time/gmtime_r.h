/* HASH 0xce1f4ec1 */
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
#ifndef __local_gmtime_r_defined
#define __local_gmtime_r_defined 1
/* Dependency: "dos_gmtime_s" from "time" */
#ifndef ____localdep_dos_gmtime_s_defined
#define ____localdep_dos_gmtime_s_defined 1
#if defined(__CRT_HAVE__gmtime32_s) && (defined(__USE_TIME_BITS64))
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_gmtime_s,(struct tm *__restrict __tp, __TM_TYPE(time) const *__restrict __timer),_gmtime32_s,(__tp,__timer))
#elif defined(__CRT_HAVE__gmtime64_s) && (!defined(__USE_TIME_BITS64))
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_gmtime_s,(struct tm *__restrict __tp, __TM_TYPE(time) const *__restrict __timer),_gmtime64_s,(__tp,__timer))
#elif (defined(__CRT_HAVE__gmtime32_s) || defined(__CRT_HAVE__gmtime64_s))
#include <local/time/dos_gmtime_s.h>
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
#define __localdep_dos_gmtime_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dos_gmtime_s))
#else /* CUSTOM: dos_gmtime_s */
#undef ____localdep_dos_gmtime_s_defined
#endif /* dos_gmtime_s... */
#endif /* !____localdep_dos_gmtime_s_defined */

/* Dependency: "gmtime64_r" from "time" */
#ifndef ____localdep_gmtime64_r_defined
#define ____localdep_gmtime64_r_defined 1
#if defined(__CRT_HAVE_gmtime64_r)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct tm *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, struct tm *__restrict __tp),gmtime64_r,(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime_r) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct tm *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, struct tm *__restrict __tp),gmtime_r,(__timer,__tp))
#else /* LIBC: gmtime64_r */
#include <local/time/gmtime64_r.h>
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
#define __localdep_gmtime64_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64_r))
#endif /* gmtime64_r... */
#endif /* !____localdep_gmtime64_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__LOCAL_LIBC(gmtime_r) __ATTR_NONNULL((1, 2)) struct tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gmtime_r))(__TM_TYPE(time) const *__restrict __timer,
                                                      struct tm *__restrict __tp) {
#line 1537 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE__gmtime32_s) || defined(__CRT_HAVE__gmtime64_s)
	return __localdep_dos_gmtime_s(__tp, __timer) ? __NULLPTR : __tp;
#elif defined(__USE_TIME_BITS64)
	return __localdep_gmtime64_r(__timer, __tp);
#else
	__time64_t __tm64 = (__time64_t)*__timer;
	return __localdep_gmtime64_r(&__tm64, __tp);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_gmtime_r_defined */
