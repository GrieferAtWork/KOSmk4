/* HASH CRC-32:0xfa15be1 */
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
#ifndef __local_gettimeofday64_defined
#if defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday)
#define __local_gettimeofday64_defined 1
/* Dependency: "gettimeofday32" from "sys.time" */
#ifndef ____localdep_gettimeofday32_defined
#define ____localdep_gettimeofday32_defined 1
#ifdef __CRT_HAVE_gettimeofday
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday32,(struct __timeval32 *__restrict __tv, __timezone_ptr_t __tz),gettimeofday,(__tv,__tz))
#elif defined(__CRT_HAVE___gettimeofday)
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_gettimeofday32,(struct __timeval32 *__restrict __tv, __timezone_ptr_t __tz),__gettimeofday,(__tv,__tz))
#else /* LIBC: gettimeofday */
#undef ____localdep_gettimeofday32_defined
#endif /* gettimeofday32... */
#endif /* !____localdep_gettimeofday32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Get the current time of day and timezone information,
 * putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
 * Returns 0 on success, -1 on errors.
 * NOTE: This form of timezone information is obsolete.
 * Use the functions and variables declared in <time.h> instead */
__LOCAL_LIBC(gettimeofday64) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gettimeofday64))(struct __timeval64 *__restrict __tv,
                                                            __timezone_ptr_t __tz) {
#line 429 "kos/src/libc/magic/sys.time.c"
	int __result;
	struct __timeval32 __tv32;
	if (!__tv)
		return __localdep_gettimeofday32(__NULLPTR, __tz);
	__result = __localdep_gettimeofday32(&__tv32, __tz);
	if __likely(!__result) {
		__tv->__tv_sec  = (__time64_t)__tv32.__tv_sec;
		__tv->__tv_usec = __tv32.__tv_usec;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_gettimeofday || __CRT_HAVE___gettimeofday */
#endif /* !__local_gettimeofday64_defined */
