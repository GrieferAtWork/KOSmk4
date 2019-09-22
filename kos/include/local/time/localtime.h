/* HASH CRC-32:0x8ac5bedd */
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
#ifndef __local_localtime_defined
#define __local_localtime_defined 1
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
#if (!defined(__CRT_HAVE_gmtime64) && !defined(__CRT_HAVE__gmtime64) && \
     !defined(__CRT_HAVE_gmtime) && !defined(__CRT_HAVE__gmtime32)) || \
    (!defined(__CRT_HAVE_localtime64) && !defined(__CRT_HAVE__localtime64) && \
     !defined(__CRT_HAVE_localtime) && !defined(__CRT_HAVE__localtime32)) || \
     (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK struct tm __gmtime_buf = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY struct tm __gmtime_buf = {0};
#else
__PRIVATE __ATTR_UNUSED struct tm __gmtime_buf = {0};
#endif
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
/* Dependency: "localtime64" from "time" */
#ifndef ____localdep_localtime64_defined
#define ____localdep_localtime64_defined 1
#if defined(__CRT_HAVE_localtime64)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,__localdep_localtime64,(__time64_t const *__timer),localtime64,(__timer))
#elif defined(__CRT_HAVE_localtime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,__localdep_localtime64,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime64)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,__localdep_localtime64,(__time64_t const *__timer),_localtime64,(__timer))
#else /* LIBC: localtime64 */
#include <local/time/localtime64.h>
/* Return the `struct tm' representation of *TIMER in the local timezone */
#define __localdep_localtime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime64))
#endif /* localtime64... */
#endif /* !____localdep_localtime64_defined */

/* Dependency: "localtime32" from "time" */
#ifndef ____localdep_localtime32_defined
#define ____localdep_localtime32_defined 1
#if defined(__CRT_HAVE_localtime)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,__localdep_localtime32,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime32)
/* Return the `struct tm' representation of *TIMER in the local timezone */
__CREDIRECT(__ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)),struct tm *,__NOTHROW_NCX,__localdep_localtime32,(__time64_t const *__timer),_localtime32,(__timer))
#else /* LIBC: localtime */
#undef ____localdep_localtime32_defined
#endif /* localtime32... */
#endif /* !____localdep_localtime32_defined */

/* Dependency: "localtime_r" from "time" */
#ifndef ____localdep_localtime_r_defined
#define ____localdep_localtime_r_defined 1
#if defined(__CRT_HAVE_localtime_r)
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct tm *,__NOTHROW_NCX,__localdep_localtime_r,(__TM_TYPE(time) const *__restrict __timer, struct tm *__restrict __tp),localtime_r,(__timer,__tp))
#else /* LIBC: localtime_r */
#include <local/time/localtime_r.h>
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
#define __localdep_localtime_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime_r))
#endif /* localtime_r... */
#endif /* !____localdep_localtime_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in the local timezone */
__LOCAL_LIBC(localtime) __ATTR_WUNUSED __ATTR_RETNONNULL __ATTR_NONNULL((1)) struct tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(localtime))(__TM_TYPE(time) const *__timer) {
#line 546 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_localtime64) || defined(__CRT_HAVE__localtime64)
	__time64_t __tm64 = (__time64_t)*__timer;
	return __localdep_localtime64(&__tm64);
#elif defined(__CRT_HAVE_localtime) || defined(__CRT_HAVE__localtime32)
	__time32_t __tm32 = (__time32_t)*__timer;
	return __localdep_localtime32(&__tm32);
#else
	return __localdep_localtime_r(__timer, &__NAMESPACE_LOCAL_SYM __gmtime_buf);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_localtime_defined */
