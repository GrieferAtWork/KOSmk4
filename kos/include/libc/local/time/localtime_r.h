/* HASH CRC-32:0x61ae485b */
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
#ifndef __local_localtime_r_defined
#define __local_localtime_r_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dos_localtime_s_defined
#define __local___localdep_dos_localtime_s_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE__localtime32_s) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __TM_TYPE(time) const *__restrict __timer),_localtime32_s,(__tp,__timer))
#elif defined(__CRT_HAVE__localtime64_s) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __TM_TYPE(time) const *__restrict __timer),_localtime64_s,(__tp,__timer))
#elif defined(__CRT_HAVE__localtime64_s) || defined(__CRT_HAVE__localtime32_s)
__NAMESPACE_LOCAL_END
#include <libc/local/time/dos_localtime_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dos_localtime_s __LIBC_LOCAL_NAME(dos_localtime_s)
#else /* ... */
#undef __local___localdep_dos_localtime_s_defined
#endif /* !... */
#endif /* !__local___localdep_dos_localtime_s_defined */
#ifndef __local___localdep_gmtime_r_defined
#define __local___localdep_gmtime_r_defined
#ifdef __CRT_HAVE_gmtime_r
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),gmtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE___gmtime_r)
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_gmtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),__gmtime_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/gmtime_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_gmtime_r __LIBC_LOCAL_NAME(gmtime_r)
#endif /* !... */
#endif /* !__local___localdep_gmtime_r_defined */
#ifndef __local___localdep_localtime64_r_defined
#define __local___localdep_localtime64_r_defined
#if defined(__CRT_HAVE_localtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_localtime64_r)
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_localtime64_r __LIBC_LOCAL_NAME(localtime64_r)
#endif /* !... */
#endif /* !__local___localdep_localtime64_r_defined */
__LOCAL_LIBC(localtime_r) __ATTR_NONNULL((1, 2)) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(localtime_r))(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) {



#if defined(__CRT_HAVE__localtime64_s) || defined(__CRT_HAVE__localtime32_s)
	return (__NAMESPACE_LOCAL_SYM __localdep_dos_localtime_s)(__tp, __timer) ? __NULLPTR : __tp;
#elif defined(__USE_TIME_BITS64)
	return (__NAMESPACE_LOCAL_SYM __localdep_localtime64_r)(__timer, __tp);
#else /* ... */
	__time64_t __tm64 = (__time64_t)*__timer;
	return (__NAMESPACE_LOCAL_SYM __localdep_localtime64_r)(&__tm64, __tp);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_localtime_r_defined
#define __local___localdep_localtime_r_defined
#define __localdep_localtime_r __LIBC_LOCAL_NAME(localtime_r)
#endif /* !__local___localdep_localtime_r_defined */
#endif /* !__local_localtime_r_defined */
