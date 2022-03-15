/* HASH CRC-32:0x39261686 */
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
#ifndef __local_gmtime_r_defined
#define __local_gmtime_r_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_crt_gmtime32_r_defined) && defined(__CRT_HAVE_gmtime_r)
#define __local___localdep_crt_gmtime32_r_defined
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_crt_gmtime32_r,(__time32_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime_r,(__timer,__tp))
#endif /* !__local___localdep_crt_gmtime32_r_defined && __CRT_HAVE_gmtime_r */
#if !defined(__local___localdep_crt_gmtime32_s_defined) && defined(__CRT_HAVE__gmtime32_s)
#define __local___localdep_crt_gmtime32_s_defined
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_crt_gmtime32_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time32_t const *__restrict __timer),_gmtime32_s,(__tp,__timer))
#endif /* !__local___localdep_crt_gmtime32_s_defined && __CRT_HAVE__gmtime32_s */
#if !defined(__local___localdep_crt_gmtime64_s_defined) && defined(__CRT_HAVE__gmtime64_s)
#define __local___localdep_crt_gmtime64_s_defined
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_crt_gmtime64_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time64_t const *__restrict __timer),_gmtime64_s,(__tp,__timer))
#endif /* !__local___localdep_crt_gmtime64_s_defined && __CRT_HAVE__gmtime64_s */
#ifndef __local___localdep_gmtime64_r_defined
#define __local___localdep_gmtime64_r_defined
#if defined(__CRT_HAVE_gmtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime64_r)
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/gmtime64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_gmtime64_r __LIBC_LOCAL_NAME(gmtime64_r)
#endif /* !... */
#endif /* !__local___localdep_gmtime64_r_defined */
__NAMESPACE_LOCAL_END
#if defined(__BUILDING_LIBC) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#ifndef ____TIME_MONTHSTART_YDAY_DEFINED
#define ____TIME_MONTHSTART_YDAY_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__time_monthstart_yday)
__UINT16_TYPE__ const __time_monthstart_yday[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};
__NAMESPACE_LOCAL_END
#endif /* !____TIME_MONTHSTART_YDAY_DEFINED */

#ifndef __isleap
#define __isleap(__year) ((__year) % 4 == 0 && ((__year) % 100 != 0 || (__year) % 400 == 0))
#endif /* !__isleap */

#ifndef __daystoyears
#define __daystoyears(__n_days) ((400 * ((__n_days) + 1)) / 146097)
#endif /* !__daystoyears */

#ifndef __yearstodays
#define __yearstodays(__n_years) (((146097 * (__n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */

#endif /* __BUILDING_LIBC && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(gmtime_r) __ATTR_NONNULL((1, 2)) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gmtime_r))(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) {
#if defined(__CRT_HAVE__gmtime32_s) && !defined(__USE_TIME_BITS64)
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_gmtime32_s)(__tp, __timer) ? __NULLPTR : __tp;
#elif defined(__CRT_HAVE__gmtime64_s) && defined(__USE_TIME_BITS64)
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_gmtime64_s)(__tp, __timer) ? __NULLPTR : __tp;
#elif defined(__CRT_HAVE_gmtime_r)
	__time32_t __timer2 = (__time32_t)*__timer;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_gmtime32_r)(&__timer2, __tp);









































#else /* ... */
	__time64_t __timer2 = (__time64_t)*__timer;
	return (__NAMESPACE_LOCAL_SYM __localdep_gmtime64_r)(&__timer2, __tp);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gmtime_r_defined
#define __local___localdep_gmtime_r_defined
#define __localdep_gmtime_r __LIBC_LOCAL_NAME(gmtime_r)
#endif /* !__local___localdep_gmtime_r_defined */
#endif /* !__local_gmtime_r_defined */
