/* HASH 0xc1be8816 */
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
#ifndef __local_utimensat_defined
#if (defined(__CRT_HAVE_utimensat) || defined(__CRT_HAVE_utimensat64))
#define __local_utimensat_defined 1
/* Dependency: "utimensat64" from "sys.stat" */
#ifndef ____localdep_utimensat64_defined
#define ____localdep_utimensat64_defined 1
#if defined(__CRT_HAVE_utimensat64)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_utimensat64,(__fd_t __dirfd, char const *__filename, struct __timespec64 const __times[2/*or:3*/], __atflag_t __flags),utimensat64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_utimensat64,(__fd_t __dirfd, char const *__filename, struct __timespec64 const __times[2/*or:3*/], __atflag_t __flags),utimensat,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat)
#include <local/sys.stat/utimensat64.h>
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
#define __localdep_utimensat64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utimensat64))
#else /* CUSTOM: utimensat64 */
#undef ____localdep_utimensat64_defined
#endif /* utimensat64... */
#endif /* !____localdep_utimensat64_defined */

/* Dependency: "utimensat32" from "sys.stat" */
#ifndef ____localdep_utimensat32_defined
#define ____localdep_utimensat32_defined 1
#if defined(__CRT_HAVE_utimensat)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_utimensat32,(__fd_t __dirfd, char const *__filename, struct __TM_TYPE(timespec) const __times[2/*or:3*/], __atflag_t __flags),utimensat,(__dirfd,__filename,__times,__flags))
#else /* LIBC: utimensat */
#undef ____localdep_utimensat32_defined
#endif /* utimensat32... */
#endif /* !____localdep_utimensat32_defined */

__NAMESPACE_LOCAL_BEGIN
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__LOCAL_LIBC(utimensat) __ATTR_NONNULL((2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(utimensat))(__fd_t __dirfd,
                                                       char const *__filename,
                                                       struct __TM_TYPE(timespec) const __times[2/*or:3*/],
                                                       __atflag_t __flags) {
#line 551 "kos/src/libc/magic/sys.stat.c"
#ifdef __CRT_HAVE_utimensat64
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct __timespec64 __tms[3];
	if (!__times)
		return __localdep_utimensat64(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time64_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time64_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	if (__flags & 0x0200) /* AT_CHANGE_CTIME */ {
		__tms[2].tv_sec  = (__time64_t)__times[2].tv_sec;
		__tms[2].tv_nsec = __times[2].tv_nsec;
	}
	return __localdep_utimensat64(__dirfd, __filename, __tms, __flags);
#else
	struct __timespec64 __tms[2];
	if (!__times)
		return __localdep_utimensat64(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time64_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time64_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	return __localdep_utimensat64(__dirfd, __filename, __tms, __flags);
#endif
#else /* __CRT_HAVE_utimensat64 */
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct __timespec32 __tms[3];
	if (!__times)
		return __localdep_utimensat32(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	if (__flags & 0x0200) /* AT_CHANGE_CTIME */ {
		__tms[2].tv_sec  = (__time32_t)__times[2].tv_sec;
		__tms[2].tv_nsec = __times[2].tv_nsec;
	}
	return __localdep_utimensat32(__dirfd, __filename, __tms, __flags);
#else
	struct __timespec32 __tms[2];
	if (!__times)
		return __localdep_utimensat32(__dirfd, __filename, __NULLPTR, __flags);
	__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
	__tms[0].tv_nsec = __times[0].tv_nsec;
	__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
	__tms[1].tv_nsec = __times[1].tv_nsec;
	return __localdep_utimensat32(__dirfd, __filename, __tms, __flags);
#endif
#endif /* !__CRT_HAVE_utimensat64 */
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_utimensat) || defined(__CRT_HAVE_utimensat64)) */
#endif /* !__local_utimensat_defined */
