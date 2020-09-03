/* HASH CRC-32:0xac5c19c7 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_localtime64_r_defined
#define __local_localtime64_r_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: dos_localtime64_s from time */
#ifndef __local___localdep_dos_localtime64_s_defined
#define __local___localdep_dos_localtime64_s_defined 1
#ifdef __CRT_HAVE__localtime64_s
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime64_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time64_t const *__restrict __timer),_localtime64_s,(__tp,__timer))
#elif defined(__CRT_HAVE__localtime32_s)
__NAMESPACE_LOCAL_END
#include <libc/local/time/dos_localtime64_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dos_localtime64_s __LIBC_LOCAL_NAME(dos_localtime64_s)
#else /* ... */
#undef __local___localdep_dos_localtime64_s_defined
#endif /* !... */
#endif /* !__local___localdep_dos_localtime64_s_defined */
/* Dependency: gmtime64_r from time */
#ifndef __local___localdep_gmtime64_r_defined
#define __local___localdep_gmtime64_r_defined 1
#ifdef __CRT_HAVE_gmtime64_r
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime64_r,(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/gmtime64_r.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
#define __localdep_gmtime64_r __LIBC_LOCAL_NAME(gmtime64_r)
#endif /* !... */
#endif /* !__local___localdep_gmtime64_r_defined */
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__LOCAL_LIBC(localtime64_r) __ATTR_NONNULL((1, 2)) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(localtime64_r))(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) {



#if defined(__CRT_HAVE__localtime64_s) || defined(__CRT_HAVE__localtime32_s)
	return __localdep_dos_localtime64_s(__tp, __timer) ? __NULLPTR : __tp;
#else /* __CRT_HAVE__localtime64_s || __CRT_HAVE__localtime32_s */
	/* XXX: Timezone support? */
	return __localdep_gmtime64_r(__timer, __tp);
#endif /* !__CRT_HAVE__localtime64_s && !__CRT_HAVE__localtime32_s */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_localtime64_r_defined
#define __local___localdep_localtime64_r_defined 1
#define __localdep_localtime64_r __LIBC_LOCAL_NAME(localtime64_r)
#endif /* !__local___localdep_localtime64_r_defined */
#endif /* !__local_localtime64_r_defined */
