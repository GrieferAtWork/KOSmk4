/* HASH CRC-32:0x110403a1 */
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
#ifndef __local_UTimensAt64_defined
#ifdef __CRT_HAVE_UTimensAt
#define __local_UTimensAt64_defined 1
#include <kos/anno.h>
/* Dependency: "UTimensAt32" from "kos.sys.stat" */
#ifndef ____localdep_UTimensAt32_defined
#define ____localdep_UTimensAt32_defined 1
#ifdef __CRT_HAVE_UTimensAt
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CREDIRECT_VOID(__ATTR_NONNULL((2)),,__localdep_UTimensAt32,(__fd_t __dirfd, char const *__filename, struct __TM_TYPE(timespec) const __times[2 /*or:3*/], __atflag_t __flags),UTimensAt,(__dirfd,__filename,__times,__flags)) __THROWS(...)
#else /* LIBC: UTimensAt */
#undef ____localdep_UTimensAt32_defined
#endif /* UTimensAt32... */
#endif /* !____localdep_UTimensAt32_defined */

__NAMESPACE_LOCAL_BEGIN
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__LOCAL_LIBC(UTimensAt64) __ATTR_NONNULL((2)) void
(__LIBCCALL __LIBC_LOCAL_NAME(UTimensAt64))(__fd_t __dirfd,
                                            char const *__filename,
                                            struct __timespec64 const __times[2 /*or:3*/],
                                            __atflag_t __flags) __THROWS(...) {
#line 228 "kos/src/libc/magic/kos.sys.stat.c"
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct __timespec32 __tms[3];
	if (!__times) {
		__localdep_UTimensAt32(__dirfd, __filename, __NULLPTR, __flags);
	} else {
		__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
		__tms[0].tv_nsec = __times[0].tv_nsec;
		__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
		__tms[1].tv_nsec = __times[1].tv_nsec;
		if (__flags & 0x0200) /* AT_CHANGE_CTIME */ {
			__tms[2].tv_sec  = (__time32_t)__times[2].tv_sec;
			__tms[2].tv_nsec = __times[2].tv_nsec;
		}
		__localdep_UTimensAt32(__dirfd, __filename, __tms, __flags);
	}
#else
	struct __timespec32 __tms[2];
	if (!__times) {
		__localdep_UTimensAt32(__dirfd, __filename, __NULLPTR, __flags);
	} else {
		__tms[0].tv_sec  = (__time32_t)__times[0].tv_sec;
		__tms[0].tv_nsec = __times[0].tv_nsec;
		__tms[1].tv_sec  = (__time32_t)__times[1].tv_sec;
		__tms[1].tv_nsec = __times[1].tv_nsec;
		__localdep_UTimensAt32(__dirfd, __filename, __tms, __flags);
	}
#endif
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_UTimensAt) */
#endif /* !__local_UTimensAt64_defined */
