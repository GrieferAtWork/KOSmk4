/* HASH CRC-32:0xb5863a74 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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
#ifndef __local___localdep_mktime64_defined
#define __local___localdep_mktime64_defined
#if defined(__CRT_HAVE_mktime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE_mktime64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),mktime64,(__tp))
#elif defined(__CRT_HAVE__mktime64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),_mktime64,(__tp))
#elif defined(__CRT_HAVE_timelocal64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time64_t,__NOTHROW_NCX,__localdep_mktime64,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),timelocal64,(__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/mktime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mktime64 __LIBC_LOCAL_NAME(mktime64)
#endif /* !... */
#endif /* !__local___localdep_mktime64_defined */
#if !defined(__local___localdep_timegm32_defined) && defined(__CRT_HAVE_timegm)
#define __local___localdep_timegm32_defined
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_timegm32,(struct __NAMESPACE_STD_SYM tm *__tp),timegm,(__tp))
#endif /* !__local___localdep_timegm32_defined && __CRT_HAVE_timegm */
__LOCAL_LIBC(timegm64) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(timegm64))(struct __NAMESPACE_STD_SYM tm *__tp) {
#ifdef __CRT_HAVE_timegm
	return (__time64_t)(__NAMESPACE_LOCAL_SYM __localdep_timegm32)(__tp);
#else /* __CRT_HAVE_timegm */
	/* TODO: Timezones */
	return (__NAMESPACE_LOCAL_SYM __localdep_mktime64)(__tp);
#endif /* !__CRT_HAVE_timegm */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_timegm64_defined
#define __local___localdep_timegm64_defined
#define __localdep_timegm64 __LIBC_LOCAL_NAME(timegm64)
#endif /* !__local___localdep_timegm64_defined */
#endif /* !__local_timegm64_defined */
