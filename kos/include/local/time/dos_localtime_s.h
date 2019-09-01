/* HASH 0x3d036b24 */
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
#ifndef __local_dos_localtime_s_defined
#if (defined(__CRT_HAVE__localtime32_s) || defined(__CRT_HAVE__localtime64_s))
#define __local_dos_localtime_s_defined 1
/* Dependency: "dos_localtime64_s" from "time" */
#ifndef ____localdep_dos_localtime64_s_defined
#define ____localdep_dos_localtime64_s_defined 1
#if defined(__CRT_HAVE__localtime64_s)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime64_s,(struct tm *__restrict __tp, __time64_t const *__restrict __timer),_localtime64_s,(__tp,__timer))
#elif defined(__CRT_HAVE__gmtime32_s)
#include <local/time/dos_localtime64_s.h>
#define __localdep_dos_localtime64_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dos_localtime64_s))
#else /* CUSTOM: dos_localtime64_s */
#undef ____localdep_dos_localtime64_s_defined
#endif /* dos_localtime64_s... */
#endif /* !____localdep_dos_localtime64_s_defined */

/* Dependency: "dos_localtime32_s" from "time" */
#ifndef ____localdep_dos_localtime32_s_defined
#define ____localdep_dos_localtime32_s_defined 1
#if defined(__CRT_HAVE__localtime32_s)
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime32_s,(struct tm *__restrict __tp, __time32_t const *__restrict __timer),_localtime32_s,(__tp,__timer))
#else /* LIBC: _localtime32_s */
#undef ____localdep_dos_localtime32_s_defined
#endif /* dos_localtime32_s... */
#endif /* !____localdep_dos_localtime32_s_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__LOCAL_LIBC(dos_localtime_s) __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dos_localtime_s))(struct tm *__restrict __tp,
                                                             __TM_TYPE(time) const *__restrict __timer) {
#line 274 "kos/src/libc/magic/time.c"
#ifdef __CRT_HAVE__localtime64_s
	__time64_t __tm64 = *__timer;
	return __localdep_dos_localtime64_s(__tp, &__tm64);
#else
	__time32_t __tm32 = *__timer;
	return __localdep_dos_localtime32_s(__tp, &__tm32);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE__localtime32_s) || defined(__CRT_HAVE__localtime64_s)) */
#endif /* !__local_dos_localtime_s_defined */
