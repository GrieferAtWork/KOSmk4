/* HASH CRC-32:0xd1484e5b */
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
#ifndef _SYS_TIMEB_H
#define _SYS_TIMEB_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __time_t_defined
#define __time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

#if __TM_SIZEOF(TIME) <= 4
#define __timeb64  __timeb_alt
#define __timeb32  timeb
#else
#define __timeb64  timeb
#define __timeb32  __timeb_alt
#endif

#ifdef __USE_TIME64
#ifndef __time64_t_defined
#define __time64_t_defined 1
typedef __time64_t time64_t;
#endif /* !__time64_t_defined */
#if __TM_SIZEOF(TIME) <= 4
#define __timeb_alt timeb64
#else
#define timeb64     timeb
#endif
#endif /* __USE_TIME64 */


#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("time")
#pragma push_macro("millitm")
#pragma push_macro("timezone")
#pragma push_macro("dstflag")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef time
#undef millitm
#undef timezone
#undef dstflag
struct timeb {
#if __TM_SIZEOF(TIME) <= 4
	__time32_t      time;     /* Seconds since epoch, as from `time'. */
#else
	__time64_t      time;     /* Seconds since epoch, as from `time'. */
#endif
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
};
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#if defined(__USE_TIME64) && __TM_SIZEOF(TIME) <= 4
#define timeb64     timeb
#else
#define __timeb_alt timeb
#endif
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __timeb_alt {
#if __TM_SIZEOF(TIME) <= 4
	__time64_t      time;     /* Seconds since epoch, as from `time'. */
#else
	__time32_t      time;     /* Seconds since epoch, as from `time'. */
#endif
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
};
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("dstflag")
#pragma pop_macro("timezone")
#pragma pop_macro("millitm")
#pragma pop_macro("time")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __USE_DOS
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */
#if defined(__CRT_HAVE__ftime32)
/* Fill in TIMEBUF with information about the current time */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_ftime32,(struct __timeb32 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime64)
#include <local/sys.timeb/_ftime32.h>
/* Fill in TIMEBUF with information about the current time */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ftime32, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _ftime32)(struct __timeb32 *__timebuf) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ftime32))(__timebuf); })
#endif /* _ftime32... */
#if defined(__CRT_HAVE__ftime64)
/* Fill in TIMEBUF with information about the current time */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_ftime64,(struct __timeb64 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE__ftime32) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Fill in TIMEBUF with information about the current time */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_ftime64,(struct __timeb64 *__timebuf),_ftime32,(__timebuf))
#elif defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32)
#include <local/sys.timeb/_ftime64.h>
/* Fill in TIMEBUF with information about the current time */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ftime64, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _ftime64)(struct __timeb64 *__timebuf) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ftime64))(__timebuf); })
#endif /* _ftime64... */
#if defined(__CRT_HAVE__ftime32_s)
/* Fill in TIMEBUF with information about the current time */
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_ftime32_s,(struct __timeb32 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64)
#include <local/sys.timeb/_ftime32_s.h>
/* Fill in TIMEBUF with information about the current time */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ftime32_s, __FORCELOCAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _ftime32_s)(struct __timeb32 *__timebuf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ftime32_s))(__timebuf); })
#endif /* _ftime32_s... */
#if defined(__CRT_HAVE__ftime64_s)
/* Fill in TIMEBUF with information about the current time */
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_ftime64_s,(struct __timeb64 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE__ftime32_s) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Fill in TIMEBUF with information about the current time */
__CREDIRECT(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_ftime64_s,(struct __timeb64 *__timebuf),_ftime32_s,(__timebuf))
#elif defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64)
#include <local/sys.timeb/_ftime64_s.h>
/* Fill in TIMEBUF with information about the current time */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ftime64_s, __FORCELOCAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _ftime64_s)(struct __timeb64 *__timebuf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ftime64_s))(__timebuf); })
#endif /* _ftime64_s... */
#endif /* __USE_DOS */



#if defined(__CRT_HAVE_ftime64) && (defined(__USE_TIME_BITS64))
/* Fill in TIMEBUF with information about the current time */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ftime,(struct timeb *__timebuf),ftime64,(__timebuf))
#elif defined(__CRT_HAVE_ftime) && (!defined(__USE_TIME_BITS64))
/* Fill in TIMEBUF with information about the current time */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ftime,(struct timeb *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s)
#include <local/sys.timeb/ftime.h>
/* Fill in TIMEBUF with information about the current time */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftime, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL ftime)(struct timeb *__timebuf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftime))(__timebuf); })
#endif /* ftime... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_ftime64)
/* Fill in TIMEBUF with information about the current time */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ftime64,(struct timeb64 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE_ftime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Fill in TIMEBUF with information about the current time */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,ftime64,(struct timeb64 *__timebuf),ftime,(__timebuf))
#elif defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s)
#include <local/sys.timeb/ftime64.h>
/* Fill in TIMEBUF with information about the current time */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftime64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL ftime64)(struct timeb64 *__timebuf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftime64))(__timebuf); })
#endif /* ftime64... */
#endif /* __USE_TIME64 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_TIMEB_H */
