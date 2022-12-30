/* HASH CRC-32:0x83c9a445 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/timerfd.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/timerfd.h) */
/* (#) Portability: diet libc     (/include/sys/timerfd.h) */
/* (#) Portability: musl libc     (/include/sys/timerfd.h) */
#ifndef _SYS_TIMERFD_H
#define _SYS_TIMERFD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/timerfd.h>
#include <bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <time.h>
#endif /* __USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

/* Values for the `flags' argument of `timerfd_create(2)'. */
#if ((!defined(TFD_NONBLOCK) && defined(__TFD_NONBLOCK)) || \
     (!defined(TFD_CLOEXEC) && defined(__TFD_CLOEXEC)) ||   \
     (defined(__USE_KOS) && (!defined(TFD_CLOFORK) && defined(__TFD_CLOFORK))))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(TFD_NONBLOCK) && defined(__TFD_NONBLOCK)
	TFD_NONBLOCK      = __TFD_NONBLOCK, /* Set the `IO_NONBLOCK' flag for the returned */
#endif /* !TFD_NONBLOCK && __TFD_NONBLOCK */
#if !defined(TFD_CLOEXEC) && defined(__TFD_CLOEXEC)
	TFD_CLOEXEC       = __TFD_CLOEXEC,  /* Set the `IO_CLOEXEC' flag for the returned */
#endif /* !TFD_CLOEXEC && __TFD_CLOEXEC */
#if defined(__USE_KOS) && !defined(TFD_CLOFORK) && defined(__TFD_CLOFORK)
	TFD_CLOFORK       = __TFD_CLOFORK,  /* Set the `IO_CLOFORK' flag for the returned */
#endif /* __USE_KOS && !TFD_CLOFORK && __TFD_CLOFORK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(TFD_NONBLOCK) && defined(__TFD_NONBLOCK)
#define TFD_NONBLOCK TFD_NONBLOCK /* Set the `IO_NONBLOCK' flag for the returned */
#endif /* !TFD_NONBLOCK && __TFD_NONBLOCK */
#if !defined(TFD_CLOEXEC) && defined(__TFD_CLOEXEC)
#define TFD_CLOEXEC  TFD_CLOEXEC  /* Set the `IO_CLOEXEC' flag for the returned */
#endif /* !TFD_CLOEXEC && __TFD_CLOEXEC */
#if defined(__USE_KOS) && !defined(TFD_CLOFORK) && defined(__TFD_CLOFORK)
#define TFD_CLOFORK  TFD_CLOFORK  /* Set the `IO_CLOFORK' flag for the returned */
#endif /* __USE_KOS && !TFD_CLOFORK && __TFD_CLOFORK */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(TFD_NONBLOCK) && defined(__TFD_NONBLOCK)
#define TFD_NONBLOCK __TFD_NONBLOCK /* Set the `IO_NONBLOCK' flag for the returned */
#endif /* !TFD_NONBLOCK && __TFD_NONBLOCK */
#if !defined(TFD_CLOEXEC) && defined(__TFD_CLOEXEC)
#define TFD_CLOEXEC  __TFD_CLOEXEC  /* Set the `IO_CLOEXEC' flag for the returned */
#endif /* !TFD_CLOEXEC && __TFD_CLOEXEC */
#if defined(__USE_KOS) && !defined(TFD_CLOFORK) && defined(__TFD_CLOFORK)
#define TFD_CLOFORK  __TFD_CLOFORK  /* Set the `IO_CLOFORK' flag for the returned */
#endif /* __USE_KOS && !TFD_CLOFORK && __TFD_CLOFORK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Values for the `flags' argument of `timerfd_settime(2)'. */
#if !defined(TFD_TIMER_ABSTIME) && defined(__TFD_TIMER_ABSTIME)
/*[[[enum]]]*/
#ifdef __CC__
enum {
	TFD_TIMER_ABSTIME = __TFD_TIMER_ABSTIME /* Work with absolute timestamps. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define TFD_TIMER_ABSTIME TFD_TIMER_ABSTIME /* Work with absolute timestamps. */
#else /* __COMPILER_PREFERR_ENUMS */
#define TFD_TIMER_ABSTIME __TFD_TIMER_ABSTIME /* Work with absolute timestamps. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* !TFD_TIMER_ABSTIME && __TFD_TIMER_ABSTIME */


#ifdef __CC__

/* >> timerfd_create(2)
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
__CDECLARE_OPT(,__fd_t,__NOTHROW,timerfd_create,(clockid_t __clock_id, __STDC_INT_AS_UINT_T __flags),(__clock_id,__flags))
#if defined(__CRT_HAVE_timerfd_settime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
__CDECLARE(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,timerfd_settime,(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr),(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
__CREDIRECT(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,timerfd_settime,(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr),timerfd_settime64,(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime64) || defined(__CRT_HAVE_timerfd_settime)
#include <libc/local/sys.timerfd/timerfd_settime.h>
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timerfd_settime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUT_OPT(4) int __NOTHROW_NCX(__LIBCCALL timerfd_settime)(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct itimerspec const *__utmr, struct itimerspec *__otmr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timerfd_settime))(__ufd, __flags, __utmr, __otmr); })
#endif /* ... */
#if defined(__CRT_HAVE_timerfd_gettime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_NCX,timerfd_gettime,(__fd_t __ufd, struct itimerspec *__restrict __otmr),(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,timerfd_gettime,(__fd_t __ufd, struct itimerspec *__restrict __otmr),timerfd_gettime64,(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime64) || defined(__CRT_HAVE_timerfd_gettime)
#include <libc/local/sys.timerfd/timerfd_gettime.h>
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(timerfd_gettime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL timerfd_gettime)(__fd_t __ufd, struct itimerspec *__restrict __otmr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timerfd_gettime))(__ufd, __otmr); })
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_timerfd_settime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
__CREDIRECT(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,timerfd_settime64,(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__utmr, struct itimerspec64 *__otmr),timerfd_settime,(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime64)
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
__CDECLARE(__ATTR_IN(3) __ATTR_OUT_OPT(4),int,__NOTHROW_NCX,timerfd_settime64,(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__utmr, struct itimerspec64 *__otmr),(__ufd,__flags,__utmr,__otmr))
#elif defined(__CRT_HAVE_timerfd_settime)
#include <libc/local/sys.timerfd/timerfd_settime64.h>
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
__NAMESPACE_LOCAL_USING_OR_IMPL(timerfd_settime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUT_OPT(4) int __NOTHROW_NCX(__LIBCCALL timerfd_settime64)(__fd_t __ufd, __STDC_INT_AS_UINT_T __flags, struct itimerspec64 const *__utmr, struct itimerspec64 *__otmr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timerfd_settime64))(__ufd, __flags, __utmr, __otmr); })
#endif /* ... */
#if defined(__CRT_HAVE_timerfd_gettime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,timerfd_gettime64,(__fd_t __ufd, struct itimerspec64 *__restrict __otmr),timerfd_gettime,(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime64)
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
__CDECLARE(__ATTR_OUT(2),int,__NOTHROW_NCX,timerfd_gettime64,(__fd_t __ufd, struct itimerspec64 *__restrict __otmr),(__ufd,__otmr))
#elif defined(__CRT_HAVE_timerfd_gettime)
#include <libc/local/sys.timerfd/timerfd_gettime64.h>
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(timerfd_gettime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL timerfd_gettime64)(__fd_t __ufd, struct itimerspec64 *__restrict __otmr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(timerfd_gettime64))(__ufd, __otmr); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_TIMERFD_H */
