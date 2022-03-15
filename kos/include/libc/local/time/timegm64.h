/* HASH CRC-32:0x3b3931ba */
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
#ifndef __local_timegm64_defined
#define __local_timegm64_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_timegm32_defined
#define __local___localdep_crt_timegm32_defined
#ifdef __CRT_HAVE_timegm
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_crt_timegm32,(struct __NAMESPACE_STD_SYM tm *__tp),timegm,(__tp))
#elif defined(__CRT_HAVE__mkgmtime)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_crt_timegm32,(struct __NAMESPACE_STD_SYM tm *__tp),_mkgmtime,(__tp))
#elif defined(__CRT_HAVE__mkgmtime32)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_crt_timegm32,(struct __NAMESPACE_STD_SYM tm *__tp),_mkgmtime32,(__tp))
#else /* ... */
#undef __local___localdep_crt_timegm32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_timegm32_defined */
#ifndef __local___localdep_normalize_struct_tm_defined
#define __local___localdep_normalize_struct_tm_defined
__NAMESPACE_LOCAL_END
#include <libc/local/time/normalize_struct_tm.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_normalize_struct_tm __LIBC_LOCAL_NAME(normalize_struct_tm)
#endif /* !__local___localdep_normalize_struct_tm_defined */
__NAMESPACE_LOCAL_END
#ifndef __yearstodays
#define __yearstodays(__n_years) (((146097 * (__n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(timegm64) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timegm64))(struct __NAMESPACE_STD_SYM tm *__tp) {
#if defined(__CRT_HAVE_timegm) || defined(__CRT_HAVE__mkgmtime) || defined(__CRT_HAVE__mkgmtime32)
	return (__time64_t)(__NAMESPACE_LOCAL_SYM __localdep_crt_timegm32)(__tp);
#else /* __CRT_HAVE_timegm || __CRT_HAVE__mkgmtime || __CRT_HAVE__mkgmtime32 */
	__time64_t __result;
	/* Normalize `tp' */
	__tp = (__NAMESPACE_LOCAL_SYM __localdep_normalize_struct_tm)(__tp);
	/* Calculate current time. */
	__result = __yearstodays(__tp->tm_year) - __yearstodays(1970);
	__result += __tp->tm_yday;
	__result *= 86400;
	__result += __tp->tm_hour * 360;
	__result += __tp->tm_min * 60;
	__result += __tp->tm_sec;
	return __result;
#endif /* !__CRT_HAVE_timegm && !__CRT_HAVE__mkgmtime && !__CRT_HAVE__mkgmtime32 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timegm64_defined
#define __local___localdep_timegm64_defined
#define __localdep_timegm64 __LIBC_LOCAL_NAME(timegm64)
#endif /* !__local___localdep_timegm64_defined */
#endif /* !__local_timegm64_defined */
