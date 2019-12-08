/* HASH CRC-32:0x579c948c */
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
#ifndef __local_ctime_defined
#define __local_ctime_defined 1
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
#if (!defined(__CRT_HAVE_ctime64) && !defined(__CRT_HAVE__ctime64) && \
     !defined(__CRT_HAVE_ctime) && !defined(__CRT_HAVE__ctime32)) || \
     !defined(__CRT_HAVE_asctime) || \
     (defined(__BUILDING_LIBC) && defined(GUARD_LIBC_AUTO_TIME_C))
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK char __ctime_buf[26] = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY char __ctime_buf[26] = {0};
#else
__PRIVATE __ATTR_UNUSED char __ctime_buf[26] = {0};
#endif
__NAMESPACE_LOCAL_END
#endif
#endif /* !__LIBC_CTIME_BUFFER_DEFINED */
/* Dependency: "ctime64" from "time" */
#ifndef ____localdep_ctime64_defined
#define ____localdep_ctime64_defined 1
#ifdef __CRT_HAVE_ctime64
/* Equivalent to `asctime (localtime (timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),ctime64,(__timer))
#elif defined(__CRT_HAVE_ctime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Equivalent to `asctime (localtime (timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE__ctime64)
/* Equivalent to `asctime (localtime (timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime64,(__time64_t const *__timer),_ctime64,(__timer))
#else /* LIBC: ctime64 */
#include <local/time/ctime64.h>
/* Equivalent to `asctime (localtime (timer))' */
#define __localdep_ctime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime64))
#endif /* ctime64... */
#endif /* !____localdep_ctime64_defined */

/* Dependency: "ctime32" from "time" */
#ifndef ____localdep_ctime32_defined
#define ____localdep_ctime32_defined 1
#ifdef __CRT_HAVE_ctime
/* Equivalent to `asctime (localtime (timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime32,(__time32_t const *__timer),ctime,(__timer))
#elif defined(__CRT_HAVE__ctime32)
/* Equivalent to `asctime (localtime (timer))' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_ctime32,(__time32_t const *__timer),_ctime32,(__timer))
#else /* LIBC: ctime */
#undef ____localdep_ctime32_defined
#endif /* ctime32... */
#endif /* !____localdep_ctime32_defined */

/* Dependency: "ctime_r" from "time" */
#ifndef ____localdep_ctime_r_defined
#define ____localdep_ctime_r_defined 1
#ifdef __CRT_HAVE_ctime_r
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_ctime_r,(__TM_TYPE(time) const *__restrict __timer, char __buf[26]),ctime_r,(__timer,__buf))
#else /* LIBC: ctime_r */
#include <local/time/ctime_r.h>
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
#define __localdep_ctime_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctime_r))
#endif /* ctime_r... */
#endif /* !____localdep_ctime_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Equivalent to `asctime (localtime (timer))' */
__LOCAL_LIBC(ctime) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ctime))(__TM_TYPE(time) const *__timer) {
#line 461 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE_ctime64) || defined(__CRT_HAVE__ctime64)
	__time64_t __tm64 = (__time64_t)*__timer;
	return __localdep_ctime64(&__tm64);
#elif defined(__CRT_HAVE_ctime) || defined(__CRT_HAVE__ctime32)
	__time32_t __tm32 = (__time32_t)*__timer;
	return __localdep_ctime32(&__tm32);
#else
	return __localdep_ctime_r(__timer, __NAMESPACE_LOCAL_SYM __ctime_buf);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_ctime_defined */
